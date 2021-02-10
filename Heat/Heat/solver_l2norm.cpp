#include "solver.h"

void Error::L2norm(const ElementVector& g_elements, const double* c_solution, const int h_ref, const int t_ref, const double tv)
{
	// ÃÊ±âÈ­
	this->L2error[h_ref][t_ref] = 0.0;

	LocalBase l_base;
	Functions F;

	for (auto& it : g_elements.ev) {
		double err_u = 0.0;
		for (int k = 0; k < 7; ++k) {
			l_base.MakeUp(*it, hx[k], hy[k]);
			// xÁÂÇ¥ = (x_1 - x_0) * hx + (x_2 - x_0) * hy + x_0
			// yÁÂÇ¥ = (y_1 - y_0) * hx + (y_2 - y_0) * hy + y_0
			double xv = (it->p[1]->x - it->p[0]->x) * hx[k] + (it->p[2]->x - it->p[0]->x) * hy[k] + it->p[0]->x;
			double yv = (it->p[1]->y - it->p[0]->y) * hx[k] + (it->p[2]->y - it->p[0]->y) * hy[k] + it->p[0]->y;

			double uval = 0.0;
			for (int i = 0;i < 3; ++i) {
				uval += c_solution[it->p[i]->n] * l_base.base[i][0];
			}

			err_u += (F.exact_u(xv, yv, tv) - uval) * (F.exact_u(xv, yv, tv) - uval) * wt[k] * l_base.det;
		}
		this->L2error[h_ref][t_ref] += err_u;
	}
	double norm_u = 0.0;
	for (auto& it : g_elements.ev) {
		double err_u = 0.0;
		for (int k = 0; k < 7; ++k) {
			l_base.MakeUp(*it, hx[k], hy[k]);
			// xÁÂÇ¥ = (x_1 - x_0) * hx + (x_2 - x_0) * hy + x_0
			// yÁÂÇ¥ = (y_1 - y_0) * hx + (y_2 - y_0) * hy + y_0
			double xv = (it->p[1]->x - it->p[0]->x) * hx[k] + (it->p[2]->x - it->p[0]->x) * hy[k] + it->p[0]->x;
			double yv = (it->p[1]->y - it->p[0]->y) * hx[k] + (it->p[2]->y - it->p[0]->y) * hy[k] + it->p[0]->y;

			err_u += F.exact_u(xv, yv, tv) * F.exact_u(xv, yv, tv) * wt[k] * l_base.det;
		}
		norm_u += err_u;
	}

	//cout << "L2error: " << this->L2error[t_iter] << " " << norm_u << endl;

	this->L2error[h_ref][t_ref] = sqrt(this->L2error[h_ref][t_ref] / norm_u);
}