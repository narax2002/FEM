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
	double load[max_loc][2];

	//MatrixLocal();
	void initial();
	void MakeUpA(Element& c_element, double* c_solution[3][2], const double& t_step_size);
	void MakeUp(Element& c_element, double* c_solution[3][2], const int& t_step, const double& t_step_size);
};

class StiffRow
{
public:
	int n;
	int col[max_adj];
	double stiff[max_adj];
};

class MatrixSystem
{
public:
	int size;
	StiffRow* stiff;
	double* load[2];
	double* sol[3][2];

	MatrixSystem(const int& nv);
	void Initial();
	void InitialA(const vector<Point*> nodes);
	void MakeUpA(const ElementVector& g_elements, const double& t_step_size);
	void MakeUp(const ElementVector& g_elements, const int& t_step, const double& t_step_size);

	void Write(const vector<Point*>& nodes, const double& tv);
};

