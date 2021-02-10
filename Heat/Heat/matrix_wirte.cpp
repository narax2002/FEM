#include "matrix.h"
#include <fstream>

void MatrixStiff::Write()
{
    ofstream fout;
    fout.open("matrix.txt");    //파일 열기(파일이 없으면 만들어짐)

    for (int i = 0; i < this->size; ++i) {
        MatrixRow& c_mat_row = this->row[i];
        int temp = 0;
        for (; c_mat_row.col[temp] != -1; ++temp) {
            fout << i << " " << c_mat_row.col[temp] << " " << c_mat_row.stiff[temp] << endl;
        }
    }
    fout.close();

    fout.open("load.txt");

    for (int i = 0; i < this->size; ++i) {
        fout << this->row[i].load << endl;
    }
    fout.close();
}