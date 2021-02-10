#pragma once
#include "element.h"
#include "functions.h"

/// <summary>
/// 로컬 매트릭스 클래스 선언
/// Initial, MakeUp
/// 매트릭스 클래스 선언
/// Initial, MakeUp, Assemble, Write
/// </summary>

const int max_adj = 10; // 인접한 앨리먼트 최대 = 7
const int max_loc = 3;

class MatrixLocal
{
public:
	double stiff[max_loc][max_loc];
	double load[max_loc];

	void initial();
	void MakeUp(const Element& c_element, double* c_solution[3], const int t_step, const double t_step_size);
};

class MatrixRow
{
public:
	int n;
	int col[max_adj];
	double stiff[max_adj];
	double load;
};

class MatrixStiff
{
public:
	int size;
	MatrixRow* row;

	MatrixStiff(const int nv);
	void Initial();
	void MakeUp(const ElementVector& g_elements, double* c_solution[3], const int t_step, const double t_step_size);

	void Write();
};