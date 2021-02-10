#include "matrix.h"

void MatrixSystem::MakeUpA(const ElementVector& g_elements, const double& t_step_size)
{
	int maxpt = (int)g_elements.pv.size();
	this->InitialA(g_elements.pv);

	// 로컬 매트릭스
	Functions F;
	MatrixLocal mat_loc;
	
	for (auto& it : g_elements.ev) {
		// 로컬 MakeUp
		mat_loc.MakeUpA(*it, this->sol, t_step_size);

		// 테스트 함수 v
		for (int i = 0; i < 3; ++i) {
			int cpn = it->p[i]->n;
			
			if (it->p[i]->k == 1) continue;
			StiffRow& c_mat_row = this->stiff[cpn];

			// 솔루션 함수 u
			for (int j = 0; j < 3; ++j) {
				if (it->p[j]->k == 0) {
					// c_element->p[j]가 boundary 포인트가 아니라면
					int c_col = it->p[j]->n;
					int temp = 0;
					for (; temp < max_adj; ++temp) {
						if (c_mat_row.col[temp] == c_col) break;
						if (c_mat_row.col[temp] == -1) {
							c_mat_row.col[temp] = c_col;
							break;
						}
					}
					c_mat_row.stiff[temp] += mat_loc.stiff[i][j];
				}
			}
		}
	}
}


void MatrixSystem::MakeUp(const ElementVector& g_elements, const int& t_step, const double& t_step_size)
{
	int maxpt = (int)g_elements.pv.size();
	this->Initial();

	double tv = t_step * t_step_size;

	// 로컬 매트릭스
	MatrixLocal mat_loc;
	Functions F;

	for (auto& it : g_elements.ev) {
		// 로컬 MakeUp
		mat_loc.MakeUp(*it, this->sol, t_step, t_step_size);

		// 테스트 함수 v
		for (int i = 0; i < 3; ++i) {
			int cpn = it->p[i]->n;

			if (it->p[i]->k == 1) continue;

			// 솔루션 함수 u
			for (int j = 0; j < 3; ++j) {
				if (it->p[j]->k == 1) {
					// c_element->p[j]가 boundary 포인트라면
					this->load[0][cpn] -= F.exact_u1(it->p[j]->x, it->p[j]->y, tv) * mat_loc.stiff[i][j];
					this->load[1][cpn] -= F.exact_u2(it->p[j]->x, it->p[j]->y, tv) * mat_loc.stiff[i][j];
				}
			}

			// 로드 벡터
			this->load[0][cpn] += mat_loc.load[i][0];
			this->load[1][cpn] += mat_loc.load[i][0];
		}
	}
}