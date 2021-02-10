#include "solver.h"
#include <utility>

void Solver::Solve_bcg(const vector<Point*>& nodes, MatrixSystem& c_matrix, const double tv)
{
	const int MAXITER = 100000;
	const double TOL = 0.00000000000000000001;

	int nv = nodes.size();
	c_matrix.sol[2][0] = c_matrix.sol[1][0];
	c_matrix.sol[1][0] = c_matrix.sol[0][0];

	c_matrix.sol[2][1] = c_matrix.sol[1][1];
	c_matrix.sol[1][1] = c_matrix.sol[0][1];

	for (int m = 0; m < 2; ++m) {
		double* solhat = new double[nv];
		double* r = new double[nv];
		double* rhat = new double[nv];
		double* s = new double[nv];
		double* shat = new double[nv];
		double* w = new double[nv];
		double* what = new double[nv];

		for (int i = 0; i < nv; ++i) {
			c_matrix.sol[0][m][i] = 0.0;
			solhat[i] = 0.0;
			r[i] = c_matrix.load[m][i];
			rhat[i] = r[i];
			s[i] = r[i];
			shat[i] = rhat[i];
			w[i] = 0.0;
			what[i] = 0.0;
		}

		double rho = 0.0;
		for (int i = 0; i < nv; ++i) {
			rho += rhat[i] * r[i];
		}

		int iter = 0;
		for (; iter < MAXITER; ++iter) {
			for (int i = 0; i < nv; ++i) {
				w[i] = 0.0;
				what[i] = 0.0;
			}

			for (int i = 0; i < nv; ++i) {
				StiffRow& c_mat_row = c_matrix.stiff[i];
				int temp_k = 0;
				for (; c_mat_row.col[temp_k] != -1; ++temp_k) {
					int j = c_mat_row.col[temp_k];
					w[i] += c_mat_row.stiff[temp_k] * s[j];			// w_i = Stiff_{ij} * s_j
					what[j] += shat[i] * c_mat_row.stiff[temp_k];	// what_j = shat_i * Stif_{ij}
				}
			}

			double temp = 0.0;
			for (int i = 0; i < nv; ++i) {
				temp += shat[i] * w[i];
			}
			double alpha = rho / temp;

			double rho1 = 0.0;
			for (int i = 0; i < nv; ++i) {
				c_matrix.sol[0][m][i] += alpha * s[i];
				solhat[i] += alpha * shat[i];
				r[i] -= alpha * w[i];
				rhat[i] -= alpha * what[i];
				rho1 += rhat[i] * r[i];
			}

			/*
			if ((iter / 100) * 100 == iter) {
				cout << "Iteration: " << iter << " Error: " << sqrt(rho1) << endl;
			}
			/**/

			if (fabs(rho1) < TOL) break;

			double beta = rho1 / rho;
			for (int i = 0; i < nv; ++i) {
				s[i] = r[i] + beta * s[i];
				shat[i] = r[i] + beta * shat[i];
			}
			rho = rho1;
		}
	}

	/*
	cout << "The number of iteration for solving the matrix system - " << iter << " with error " << rho << endl;
	/**/

	Functions F;
	
	for (auto& it : nodes) {
		if (it->k == 1) {
			c_matrix.sol[0][0][it->n] = F.exact_u1(it->x, it->y, tv);
			c_matrix.sol[0][1][it->n] = F.exact_u2(it->x, it->y, tv);
		}
	}
}
