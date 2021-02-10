#include "matrix.h"
#include <fstream>

void MatrixSystem::Write(const vector<Point*>& nodes, const double&  tv)
{
    ofstream fout;
    fout.open("matrix.txt");    //파일 열기(파일이 없으면 만들어짐)

    for (int i = 0; i < this->size; ++i) {
        StiffRow& c_mat_row = this->stiff[i];
        int temp = 0;
        for (; c_mat_row.col[temp] != -1; ++temp) {
            fout << i << " " << c_mat_row.col[temp] << " " << c_mat_row.stiff[temp] << endl;
        }
    }
    fout.close();

    fout.open("load.txt");

    for (int i = 0; i < this->size; ++i) {
        fout << this->load[0][i] << " " << this->load[1][i] << endl;
    }
    fout.close();

    fout.open("solution.txt");

    for (int i = 0; i < this->size; ++i) {
        fout << this->sol[0][0][i] << " " << this->sol[0][1][i] << endl;
    }
    fout.close();

    fout.open("exact.txt");
    Functions F;
    for (auto& it : nodes) {
        fout << F.exact_u1(it->x, it->y, tv) << " " << F.exact_u2(it->x, it->y, tv) << endl;
    }
    fout.close();
}