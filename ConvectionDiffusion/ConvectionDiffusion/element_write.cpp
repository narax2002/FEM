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


    fout.open("cpoint.txt");

    for (auto& it : this->pv) {
        Point* node = it->pp;
        fout << node->x << " " << node->y << " " << node->k << endl;
    }
    fout.close();

    fout.open("ppoint.txt");

    for (auto& it : this->pv) {
        Point* node = it->pp->pp;
        fout << node->x << " " << node->y << " " << node->k << endl;
    }

    fout.close();
}

/*
void DepartVector::Write()
{
    ofstream fout;
    fout.open("cpoint.txt");    //파일 열기(파일이 없으면 만들어짐)

    for (auto& it : this->pv) {
        fout << it[0].x << " " << it[0].y << " " << it[0].k << " " << it[0].e->n << endl;
    }
    fout.close();

    fout.open("ppoint.txt");    //파일 열기(파일이 없으면 만들어짐)

    for (auto& it : this->pv) {
        fout << it[1].x << " " << it[1].y << " " << it[1].k << " " << it[1].e->n << endl;
    }
    fout.close();
}
/**/