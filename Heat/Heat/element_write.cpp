#include "element.h"
#include <fstream>

void ElementVector::Write()
{
    ofstream fout;
    fout.open("point.txt");    //파일 열기(파일이 없으면 만들어짐)

    for (auto& it : this->pv) {
        fout << it->x << " " << it->y << " " << it->k << endl;
    }
    fout.close();
    


    fout.open("element.txt");

    for (auto& it : this->ev) {
        fout << it->p[0]->n << " " << it->p[1]->n << " " << it->p[2]->n << " " << endl;
    }
    fout.close();



    fout.open("eltnum.txt");

    for (auto& it : this->ev) {
        for (int i = 0;i < 3; ++i) {
            if (it->e[i]) {
                fout << it->e[i]->n << " ";
            }
            else {
                fout << -1 << " ";
            }
        }
        fout << endl;
    }
    fout.close();
}