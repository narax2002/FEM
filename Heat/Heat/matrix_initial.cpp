#include "matrix.h"

void MatrixLocal::initial()
{
	for (int i = 0; i < max_loc; ++i) {
		for (int j = 0; j < max_loc; ++j) stiff[i][j] = 0.0;
		load[i] = 0.0;
	}
}

MatrixStiff::MatrixStiff(int nv)
{
	size = nv;
	row = new MatrixRow[nv];
	for (int i = 0; i < nv; ++i) row[i].n = i;
}

void MatrixStiff::Initial()
{
	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < max_adj; ++j) {
			this->row[i].col[j] = -1;
			this->row[i].stiff[j] = 0.0;
		}
		this->row[i].load = 0.0;
	}
}