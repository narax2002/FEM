#include "solver.h"
#include <time.h>

// Global variables
ElementVector g_elements;
DepartOperator g_depart_op;
Solver g_solver;
Error g_error;


int main()
{
	cout << "Convection diffusion solver" << endl;


	for (int h_ref = 0; h_ref < max_h_ref; ++h_ref) {
		g_elements.MakeUp(1 << (h_ref + 1));

		clock_t start = clock();

		MatrixSystem c_matrix(g_elements.pv.size());

		for (int t_ref = 0; t_ref < max_t_ref; ++t_ref) {

			clock_t sub_start = clock();
			
			int max_t_step = 1 << (t_ref + 1);
			double t_step_size = max_time / max_t_step;

			c_matrix.InitialA(g_elements.pv);
			c_matrix.MakeUpA(g_elements, t_step_size);

			for (int t_step = 1; t_step <= max_t_step; ++t_step) {
				g_depart_op.FindPoints(g_elements.pv, c_matrix.sol, t_step_size);
				c_matrix.MakeUp(g_elements, t_step, t_step_size);

				g_solver.Solve_bcg(g_elements.pv, c_matrix, t_step * t_step_size);
			}
			g_error.L2norm(g_elements, c_matrix.sol[0], h_ref, t_ref, max_time);
			g_error.H1norm(g_elements, c_matrix.sol[0], h_ref, t_ref, max_time);
			
			g_error.Write();

			clock_t sub_end = clock();

			cout << "Time taken for " << t_ref + 1 << "-th time refinment on " << h_ref + 1 << "-th space refinement running: " << sub_end - sub_start << endl;
		}
		
		if (h_ref == max_h_ref - 1) c_matrix.Write(g_elements.pv, max_time);

		clock_t end = clock();
		cout << "Time taken for " << h_ref + 1 << "-th space refinement running: " << end - start << endl;
	}

	g_elements.Write();
	

	return 0;
}