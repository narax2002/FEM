#include "solver.h"

Solver::Solver(int nv)
{
	this->size = nv;
	this->sol[0] = new double[nv];
	this->sol[1] = new double[nv];
	this->sol[2] = new double[nv];
}

void Solver::Initial(const ElementVector& g_elements)
{
	Functions F;
	for (int i = 0; i < this->size; ++i) {
		double xv = g_elements.pv[i]->x;
		double yv = g_elements.pv[i]->y;

		this->sol[0][i] = F.exact_u(xv, yv, 0.0);
	}
}

Error::Error()
{
	for (int h_ref = 0; h_ref < max_h_ref; ++h_ref) {
		L2error[h_ref] = new double[max_t_ref];
		H1error[h_ref] = new double[max_t_ref];
		for (int t_ref = 0; t_ref < max_t_ref; ++t_ref) {
			L2error[h_ref][t_ref] = 0.0;
			H1error[h_ref][t_ref] = 0.0;
		}
	}
}