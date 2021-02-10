#include "matrix.h"

// 글로벌 상수
//extern const double nu;
//extern const double hx[7], hy[7], wt[7];

void MatrixLocal::MakeUp(const Element& c_element, double* c_solution[3], const int t_step, const double t_step_size) {

	Functions F;

	//초기화
	this->initial();
	double tv = t_step * t_step_size;
	double lambda = 1.0 / t_step_size;

	// 로컬 기저 생성
	LocalBase l_base;

	if (t_step <= 1) {
		for (int k = 0; k < 7; ++k) {
			l_base.MakeUp(c_element, hx[k], hy[k]);
			// x좌표 = (x_1 - x_0) * hx + (x_2 - x_0) * hy + x_0
			// y좌표 = (y_1 - y_0) * hx + (y_2 - y_0) * hy + y_0
			double xv = (c_element.p[1]->x - c_element.p[0]->x) * hx[k] + (c_element.p[2]->x - c_element.p[0]->x) * hy[k] + c_element.p[0]->x;
			double yv = (c_element.p[1]->y - c_element.p[0]->y) * hx[k] + (c_element.p[2]->y - c_element.p[0]->y) * hy[k] + c_element.p[0]->y;

			// 첫 번째 테스트 함수 v1
			for (int i = 0; i < 3; ++i) {
				// 매트릭스
				// 첫 번째 솔루션 함수 u1
				for (int j = 0; j < 3; ++j) {
					this->stiff[i][j] += F.nu * l_base.base[i][1] * l_base.base[j][1] * wt[k] * l_base.det \
						+ F.nu * l_base.base[i][2] * l_base.base[j][2] * wt[k] * l_base.det \
						+ lambda * l_base.base[i][0] * l_base.base[j][0] * wt[k] * l_base.det;
					this->load[i] += lambda * l_base.base[i][0] * l_base.base[j][0] * c_solution[0][c_element.p[j]->n] * wt[k] * l_base.det;
				}
				// 로드 벡터
				this->load[i] += l_base.base[i][0] * F.funct1(xv, yv, tv) * wt[k] * l_base.det;
			}
		}
	}
	else {
		for (int k = 0; k < 7; ++k) {
			l_base.MakeUp(c_element, hx[k], hy[k]);
			// x좌표 = (x_1 - x_0) * hx + (x_2 - x_0) * hy + x_0
			// y좌표 = (y_1 - y_0) * hx + (y_2 - y_0) * hy + y_0
			double xv = (c_element.p[1]->x - c_element.p[0]->x) * hx[k] + (c_element.p[2]->x - c_element.p[0]->x) * hy[k] + c_element.p[0]->x;
			double yv = (c_element.p[1]->y - c_element.p[0]->y) * hx[k] + (c_element.p[2]->y - c_element.p[0]->y) * hy[k] + c_element.p[0]->y;

			// 첫 번째 테스트 함수 v1
			for (int i = 0; i < 3; ++i) {
				// 매트릭스
				// 첫 번째 솔루션 함수 u1
				for (int j = 0; j < 3; ++j) {
					this->stiff[i][j] += F.nu * l_base.base[i][1] * l_base.base[j][1] * wt[k] * l_base.det \
						+ F.nu * l_base.base[i][2] * l_base.base[j][2] * wt[k] * l_base.det \
						+ (3.0 / 2.0) * lambda * l_base.base[i][0] * l_base.base[j][0] * wt[k] * l_base.det;
					this->load[i] += 2.0 * lambda * l_base.base[i][0] * l_base.base[j][0] * c_solution[0][c_element.p[j]->n] * wt[k] * l_base.det \
						- (1.0 / 2.0) * lambda * l_base.base[i][0] * l_base.base[j][0] * c_solution[1][c_element.p[j]->n] * wt[k] * l_base.det;
				}
				// 로드 벡터
				this->load[i] += l_base.base[i][0] * F.funct1(xv, yv, tv) * wt[k] * l_base.det;
			}
		}
	}

	// Neumann boundary condition
	for (int i = 0; i < 3; ++i) {
		if (c_element.e[i] != nullptr) continue;
		// p[ip]--p[im]이 boundary edge라면
		int ip = (i + 1 < 3) ? i + 1 : i - 2;
		int im = (i + 2 < 3) ? i + 2 : i - 1;
		// tangent vector
		double tangent[2] = { c_element.p[im]->x - c_element.p[ip]->x, c_element.p[im]->y - c_element.p[ip]->y };

		for (int bk = 0; bk < 3; ++bk) {
			// bx = (x1 - x0) * bhx + x0;
			// by = (y1 - y0) * bhx + y0;
			double bxv = tangent[0] * bhx[bk] + c_element.p[ip]->x;
			double byv = tangent[1] * bhx[bk] + c_element.p[ip]->y;

			// p[im]에서 1이고 p[ip]에서 0인 테스트 함수 v1
			this->load[ip] += F.nu * (1.0 - bhx[bk]) * (F.exact_u_x(bxv, byv, tv) * tangent[1] - F.exact_u_y(bxv, byv, tv) * tangent[0]) * bwt[bk];
			this->load[im] += F.nu * bhx[bk] * (F.exact_u_x(bxv, byv, tv) * tangent[1] - F.exact_u_y(bxv, byv, tv) * tangent[0]) * bwt[bk];
		}
	}
}