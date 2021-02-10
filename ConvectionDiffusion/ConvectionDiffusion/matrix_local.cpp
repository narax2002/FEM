#include "matrix.h"

// 글로벌 상수
//extern const double nu;
//extern const double hx[7], hy[7], wt[7];

void MatrixLocal::MakeUpA(Element& c_element, double* c_solution[3][2], const double& t_step_size) {

	Functions F;

	//초기화
	this->initial();
	double lambda = 1.0 / t_step_size;

	// 로컬 기저 생성
	LocalBase l_base;
		
	for (int k = 0; k < 7; ++k) {
		l_base.MakeUp(c_element.p, hx[k], hy[k]);

		// 테스트 함수 v
		for (int i = 0; i < 3; ++i) {
			// 매트릭스
			// 솔루션 함수 u
			for (int j = 0; j < 3; ++j) {
				this->stiff[i][j] += F.nu * l_base.base[i][1] * l_base.base[j][1] * wt[k] * l_base.det \
					+ F.nu * l_base.base[i][2] * l_base.base[j][2] * wt[k] * l_base.det \
					+ (3.0 / 2.0) * lambda * l_base.base[i][0] * l_base.base[j][0] * wt[k] * l_base.det;
			}				
		}
	}
}

void MatrixLocal::MakeUp(Element& c_element, double* c_solution[3][2], const int& t_step, const double& t_step_size) {

	Functions F;
	DepartOperator loc_operator;
	Element& ce = c_element;

	//초기화
	this->initial();
	double tv = t_step * t_step_size;
	double lambda = 1.0 / t_step_size;

	// 로컬 기저 생성
	LocalBase l_base, cp_base, pp_base;
	
	if (t_step <= 1) {
		for (int k = 0; k < 7; ++k) {
			l_base.MakeUp(ce.p, hx[k], hy[k]);
			// x좌표 = (x_1 - x_0) * hx + (x_2 - x_0) * hy + x_0
			// y좌표 = (y_1 - y_0) * hx + (y_2 - y_0) * hy + y_0
			double xv = (ce.p[1]->x - ce.p[0]->x) * hx[k] + (ce.p[2]->x - ce.p[0]->x) * hy[k] + ce.p[0]->x;
			double yv = (ce.p[1]->y - ce.p[0]->y) * hx[k] + (ce.p[2]->y - ce.p[0]->y) * hy[k] + ce.p[0]->y;

			// 테스트 함수 v
			for (int i = 0; i < 3; ++i) {
				// 로드 벡터				
				double c_sol[2];
				
				double xt = (ce.p[1]->pp->x - ce.p[0]->pp->x) * hx[k] + (ce.p[2]->pp->x - ce.p[0]->pp->x) * hy[k] + ce.p[0]->pp->x;
				double yt = (ce.p[1]->pp->y - ce.p[0]->pp->y) * hx[k] + (ce.p[2]->pp->y - ce.p[0]->pp->y) * hy[k] + ce.p[0]->pp->y;				
				loc_operator.CalculatePP(ce, xt, yt, c_solution, c_sol);
				this->load[0][i] += lambda * l_base.base[i][0] * c_sol[0] * wt[k] * l_base.det;
				this->load[1][i] += lambda * l_base.base[i][0] * c_sol[1] * wt[k] * l_base.det;

				this->load[0][i] += l_base.base[i][0] * F.funct1(xv, yv, tv) * wt[k] * l_base.det;
				this->load[1][i] += l_base.base[i][0] * F.funct2(xv, yv, tv) * wt[k] * l_base.det;
			}
		}
	}
	else {
		for (int k = 0; k < 7; ++k) {
			l_base.MakeUp(ce.p, hx[k], hy[k]);
			// x좌표 = (x_1 - x_0) * hx + (x_2 - x_0) * hy + x_0
			// y좌표 = (y_1 - y_0) * hx + (y_2 - y_0) * hy + y_0
			double xv = (ce.p[1]->x - ce.p[0]->x) * hx[k] + (ce.p[2]->x - ce.p[0]->x) * hy[k] + ce.p[0]->x;
			double yv = (ce.p[1]->y - ce.p[0]->y) * hx[k] + (ce.p[2]->y - ce.p[0]->y) * hy[k] + ce.p[0]->y;

			// 테스트 함수 v
			for (int i = 0; i < 3; ++i) {
				// 로드 벡터
				double c_sol[2];
				
				double xt = (ce.p[1]->pp->x - ce.p[0]->pp->x) * hx[k] + (ce.p[2]->pp->x - ce.p[0]->pp->x) * hy[k] + ce.p[0]->pp->x;
				double yt = (ce.p[1]->pp->y - ce.p[0]->pp->y) * hx[k] + (ce.p[2]->pp->y - ce.p[0]->pp->y) * hy[k] + ce.p[0]->pp->y;
				loc_operator.CalculatePP(ce, xt, yt, c_solution, c_sol);
				this->load[0][i] += 2.0 * lambda * l_base.base[i][0] * c_sol[0] * wt[k] * l_base.det;
				this->load[1][i] += 2.0 * lambda * l_base.base[i][0] * c_sol[1] * wt[k] * l_base.det;

				xt = (ce.p[1]->pp->pp->x - ce.p[0]->pp->pp->x) * hx[k] + (ce.p[2]->pp->pp->x - ce.p[0]->pp->pp->x) * hy[k] + ce.p[0]->pp->pp->x;
				yt = (ce.p[1]->pp->pp->y - ce.p[0]->pp->pp->y) * hx[k] + (ce.p[2]->pp->pp->y - ce.p[0]->pp->pp->y) * hy[k] + ce.p[0]->pp->pp->y;
				loc_operator.CalculatePP(ce, xt, yt, c_solution, c_sol);
				this->load[0][i] -= (1.0 / 2.0) * lambda * l_base.base[i][0] * c_sol[0] * wt[k] * l_base.det;
				this->load[1][i] -= (1.0 / 2.0) * lambda * l_base.base[i][0] * c_sol[1] * wt[k] * l_base.det;

				this->load[0][i] += l_base.base[i][0] * F.funct1(xv, yv, tv) * wt[k] * l_base.det;
				this->load[1][i] += l_base.base[i][0] * F.funct2(xv, yv, tv) * wt[k] * l_base.det;
			}
		}
	}
}