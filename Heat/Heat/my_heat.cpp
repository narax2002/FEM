#include "solver.h"
#include <time.h>

// Global variables
ElementVector g_elements;
Error g_error;

int main()
{
	cout << "Heat equation solver" << endl;

	g_elements.Initial();


	for (int h_ref = 0; h_ref < max_h_ref; ++h_ref) {

		clock_t start = clock();

		g_elements.Refinement(); // 앨리먼트 업데이트
		int nv = (int)g_elements.pv.size();
		MatrixStiff c_matrix(nv);
		Solver c_solution(nv);
		for (int t_ref = 0; t_ref < max_t_ref; ++t_ref) {
			int max_t_step = 2 << t_ref;
			double t_step_size = max_time / max_t_step;
			c_solution.Initial(g_elements);

			//int my_t_iter = max_t_iter;
			int my_t_iter = max_t_step;
			for (int t_step = 1; t_step <= my_t_iter; ++t_step) {
				c_matrix.MakeUp(g_elements, c_solution.sol, t_step, t_step_size);
				double tv = t_step * t_step_size;
				c_solution.Solve_bcg(g_elements, c_matrix, tv);
			}
			double tv = my_t_iter * t_step_size;
			g_error.L2norm(g_elements, c_solution.sol[0], h_ref, t_ref, tv);
			g_error.H1norm(g_elements, c_solution.sol[0], h_ref, t_ref, tv);
		}

		clock_t end = clock();
		cout << "Time taken for " << h_ref + 1 << "-th refinement running: " << end - start << endl;
		if (h_ref == max_h_ref - 1) {
			c_matrix.Write();
			c_solution.Write(g_elements);
		}
	}

	g_elements.Write();
	g_error.Write();


	return 0;
}