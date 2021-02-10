#include "matrix.h"

void MatrixStiff::MakeUp(const ElementVector& g_elements, double* c_solution[3], const int t_step, const double t_step_size)
{
	int maxpt = (int)g_elements.pv.size();
	this->Initial();

	double tv = t_step * t_step_size;

	// 로컬 매트릭스
	MatrixLocal mat_loc;
	Functions F;
	
	for (auto& it : g_elements.ev) {
		// 로컬 MakeUp
		mat_loc.MakeUp(*it, c_solution, t_step, t_step_size);

		// 첫 번째 테스트 함수 v1
		for (int i = 0; i < 3; ++i) {
			MatrixRow& c_mat_row = this->row[it->p[i]->n];

			// 첫 번째 솔루션 함수 u1
			for (int j = 0; j < 3; ++j) {
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
			//
			c_mat_row.load += mat_loc.load[i];

			/*
			if (it->p[i]->k == 1) continue;
			MatrixRow& c_mat_row = this->row[it->p[i]->n];

			// 첫 번째 솔루션 함수 u1
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
				else {
					// c_element->p[j]가 boundary 포인트라면
					c_mat_row.load -= F.exact_u(it->p[j]->x, it->p[j]->y, tv) * mat_loc.stiff[i][j];
				}
			}
			//
			c_mat_row.load += mat_loc.load[i];
			/**/
		}
	}
}