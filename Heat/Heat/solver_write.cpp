#include "solver.h"
#include <fstream>

void Solver::Write(const ElementVector& g_elements)
{
    int nv = this->size;
    int max_t_step = 1 << (max_t_ref - 1);
    double t_step_size = max_time / max_t_step;

    ofstream fout;
    fout.open("solution.txt");
    
    for (int i = 0; i < nv; ++i) {
        fout << this->sol[2][i] << " " << this->sol[1][i] << " " << this->sol[0][i] << endl;
    }
    fout.close();

    fout.open("exact_u.txt");
    Functions F;

    //int my_t_iter = max_t_iter;
    int my_t_iter = max_t_step;
    double tv = my_t_iter * t_step_size;

    for (auto& it : g_elements.pv) {
        fout << F.exact_u(it->x, it->y, 0.0) << " " << F.exact_u(it->x, it->y, tv) << endl;
    }
    fout.close();
}

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