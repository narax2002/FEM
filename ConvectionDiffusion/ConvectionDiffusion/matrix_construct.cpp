#include "matrix.h"

/*
MatrixLocal::MatrixLocal()
{
	for (int i = 0; i < max_loc; ++i) {
		for (int j = 0; j < max_loc; ++j) stiff[i][j] = 0.0;
		load[i][0] = 0.0;
		load[i][1] = 0.0;
	}
}
/**/

MatrixSystem::MatrixSystem(const int& nv)
{
	size = nv;
	stiff = new StiffRow[nv];
	for (int i = 0; i < nv; ++i) stiff[i].n = i;
	load[0] = new double[nv];
	load[1] = new double[nv];
	sol[0][0] = new double[nv];
	sol[0][1] = new double[nv];
	sol[1][0] = new double[nv];
	sol[1][1] = new double[nv];
	sol[2][0] = new double[nv];
	sol[2][1] = new double[nv];
}

