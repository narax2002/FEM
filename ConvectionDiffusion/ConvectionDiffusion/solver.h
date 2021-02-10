#pragma once
#include "matrix.h"

/// <summary>
/// 솔루션 클래스 선언
/// Initial, Solve_bcg, L2norm, H1norm, Write
/// </summary>


class Solver
{
public:
	void Solve_bcg(const vector<Point*>& nodes, MatrixSystem& c_matrix, const double tv);
};

class Error
{
public:
	double* L2error[max_h_ref];
	double* H1error[max_h_ref];

	Error();
	void L2norm(const ElementVector& g_elements, double* c_solution[2], const int h_ref, const int t_ref, const double tv);
	void H1norm(const ElementVector& g_elements, double* c_solution[2], const int h_ref, const int t_ref, const double tv);

	void Write();
};