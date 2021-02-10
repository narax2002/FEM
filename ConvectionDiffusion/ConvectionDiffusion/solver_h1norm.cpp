#include "solver.h"

void Error::H1norm(const ElementVector& g_elements, double* c_solution[2], const int h_ref, const int t_ref, const double tv)
{
	// ÃÊ±âÈ­
	this->H1error[h_ref][t_ref] = 0.0;

	LocalBase l_base;
	Functions F;


	for (auto& it : g_elements.ev) {
		double err_u = 0.0;
		for (int k = 0; k < 7; ++k) {
			l_base.MakeUp(it->p, hx[k], hy[k]);
			// xÁÂÇ¥ = (x_1 - x_0) * hx + (x_2 - x_0) * hy + x_0
			// yÁÂÇ¥ = (y_1 - y_0) * hx + (y_2 - y_0) * hy + y_0
			double xv = (it->p[1]->x - it->p[0]->x) * hx[k] + (it->p[2]->x - it->p[0]->x) * hy[k] + it->p[0]->x;
			double yv = (it->p[1]->y - it->p[0]->y) * hx[k] + (it->p[2]->y - it->p[0]->y) * hy[k] + it->p[0]->y;

			double u1xval = 0.0, u2xval = 0.0;
			double u1yval = 0.0, u2yval = 0.0;
			for (int i = 0;i < 3; ++i) {
				u1xval += c_solution[0][it->p[i]->n] * l_base.base[i][1];
				u1yval += c_solution[0][it->p[i]->n] * l_base.base[i][2];
				u2xval += c_solution[1][it->p[i]->n] * l_base.base[i][1];
				u2yval += c_solution[1][it->p[i]->n] * l_base.base[i][2];
			}

			err_u += (F.exact_u1_x(xv, yv, tv) - u1xval) * (F.exact_u1_x(xv, yv, tv) - u1xval) * wt[k] * l_base.det \
				+ (F.exact_u1_y(xv, yv, tv) - u1yval) * (F.exact_u1_y(xv, yv, tv) - u1yval) * wt[k] * l_base.det \
				+ (F.exact_u2_x(xv, yv, tv) - u2xval) * (F.exact_u2_x(xv, yv, tv) - u2xval) * wt[k] * l_base.det \
				+ (F.exact_u2_y(xv, yv, tv) - u2yval) * (F.exact_u2_y(xv, yv, tv) - u2yval) * wt[k] * l_base.det;
		}
		this->H1error[h_ref][t_ref] += err_u;
	}

	double norm_u = 0.0;
	for (auto& it : g_elements.ev) {
		double err_u = 0.0;
		for (int k = 0; k < 7; ++k) {
			l_base.MakeUp(it->p, hx[k], hy[k]);
			// xÁÂÇ¥ = (x_1 - x_0) * hx + (x_2 - x_0) * hy + x_0
			// yÁÂÇ¥ = (y_1 - y_0) * hx + (y_2 - y_0) * hy + y_0
			double xv = (it->p[1]->x - it->p[0]->x) * hx[k] + (it->p[2]->x - it->p[0]->x) * hy[k] + it->p[0]->x;
			double yv = (it->p[1]->y - it->p[0]->y) * hx[k] + (it->p[2]->y - it->p[0]->y) * hy[k] + it->p[0]->y;

			err_u += F.exact_u1_x(xv, yv, tv) * F.exact_u1_x(xv, yv, tv) * wt[k] * l_base.det \
				+ F.exact_u1_y(xv, yv, tv) * F.exact_u1_y(xv, yv, tv) * wt[k] * l_base.det \
				+ F.exact_u2_x(xv, yv, tv) * F.exact_u2_x(xv, yv, tv) * wt[k] * l_base.det \
				+ F.exact_u2_y(xv, yv, tv) * F.exact_u2_y(xv, yv, tv) * wt[k] * l_base.det;
		}
		norm_u += err_u;
	}

	//cout << "H1error: " << this->H1error[t_iter] << " " << norm_u << endl;

	this->H1error[h_ref][t_ref] = sqrt(this->H1error[h_ref][t_ref] / norm_u);
}