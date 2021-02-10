#include "solver.h"

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