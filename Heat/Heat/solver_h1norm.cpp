#include "solver.h"

void Error::H1norm(const ElementVector& g_elements, const double* c_solution, const int h_ref, const int t_ref, const double tv)
{
	// ÃÊ±âÈ­
	this->H1error[h_ref][t_ref] = 0.0;

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

			double uxval = 0.0;
			double uyval = 0.0;
			for (int i = 0;i < 3; ++i) {
				uxval += c_solution[it->p[i]->n] * l_base.base[i][1];
				uyval += c_solution[it->p[i]->n] * l_base.base[i][2];
			}

			err_u += (F.exact_u_x(xv, yv, tv) - uxval) * (F.exact_u_x(xv, yv, tv) - uxval) * wt[k] * l_base.det \
				+ (F.exact_u_y(xv, yv, tv) - uyval) * (F.exact_u_y(xv, yv, tv) - uyval) * wt[k] * l_base.det;
		}
		this->H1error[h_ref][t_ref] += err_u;
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

			err_u += F.exact_u_x(xv, yv, tv) * F.exact_u_x(xv, yv, tv) * wt[k] * l_base.det \
				+ F.exact_u_y(xv, yv, tv) * F.exact_u_y(xv, yv, tv) * wt[k] * l_base.det;
		}
		norm_u += err_u;
	}

	//cout << "H1error: " << this->H1error[t_iter] << " " << norm_u << endl;

	this->H1error[h_ref][t_ref] = sqrt(this->H1error[h_ref][t_ref] / norm_u);
}