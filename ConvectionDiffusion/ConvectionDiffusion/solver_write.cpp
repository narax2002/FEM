#include "solver.h"
#include <fstream>

void Error::Write()
{
    ofstream fout;
    fout.open("L2error_u.txt");

    for (int h_ref = 0; h_ref < max_h_ref; ++h_ref) {
        for (int t_ref = 0; t_ref < max_t_ref; ++t_ref) {
            fout << this->L2error[h_ref][t_ref] << " ";
        }
        fout << endl;
    }
    fout.close();

    fout.open("H1error_u.txt");

    for (int h_ref = 0; h_ref < max_h_ref; ++h_ref) {
        for (int t_ref = 0; t_ref < max_t_ref; ++t_ref) {
            fout << this->H1error[h_ref][t_ref] << " ";
        }
        fout << endl;
    }
    fout.close();
}