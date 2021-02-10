#include "matrix.h"

void MatrixLocal::initial()
{
	for (int i = 0; i < max_loc; ++i) {
		for (int j = 0; j < max_loc; ++j) this->stiff[i][j] = 0.0;
		this->load[i][0] = 0.0;
		this->load[i][1] = 0.0;
	}
}

void MatrixSystem::InitialA(const vector<Point*> nodes)
{
	Functions F;
	for (auto& it : nodes) {
		int i = it->n;
		for (int j = 0; j < max_adj; ++j) {
			this->stiff[i].col[j] = -1;
			this->stiff[i].stiff[j] = 0.0;
		}

		this->load[0][i] = 0.0;
		this->load[1][i] = 0.0;
		this->sol[0][0][i] = F.exact_u1(it->x, it->y, 0.0);
		this->sol[0][1][i] = F.exact_u2(it->x, it->y, 0.0);
		this->sol[1][0][i] = 0.0;
		this->sol[1][1][i] = 0.0;
		this->sol[2][0][i] = 0.0;
		this->sol[2][1][i] = 0.0;
	}
}

void MatrixSystem::Initial()
{
	Functions F;
	for (int i = 0; i < this->size; ++i) {
		this->load[0][i] = 0.0;
		this->load[1][i] = 0.0;
	}
}