#pragma once
#include <vector>
#include <iostream>
using namespace std;
/// <summary>
/// 앨리먼트 클래스 선언
/// Initial, Refinement, Write
/// 로컬 기저 선언
/// MakeUp
/// </summary>

class Point
{
public:
	int n;
	int k; // point kind (0:interior point, 1:boundary point)
	double x;
	double y;

	Point* pp;

	Point(const int& nv);
	Point(const int& nv, const int& kv, const double& xv, const double& yv);
};

class Element
{
public:
	int n;
	Point* p[3]; // local point
	Element* e[3]; // adjoint element

	Element(const int& nv);
};

class ElementVector
{
public:
	vector<Point*> pv; // global point
	vector<Element*> ev;

	void MakeUp(const int& nv);
	//void Refinement();
	void Write();
};


class LocalBase
{
public:
	double base[3][3]; // local base bumber, (0:함수값, 1:x미분, 2:y미분)
	double det;

	LocalBase();
	//void MakeUp(const Element& c_element, const double xv, const double yv);
	void MakeUp(Point* nodes[3], const double& xv, const double& yv);
};

class DepartOperator
{
public:
	void FindPoints(vector<Point*>& nodes, double* c_solution[3][2], const double& t_step_size);
	void CalculatePP(Element& c_element, const double& xt, const double& yt, double* c_solution[3][2], double c_sol[2]);
};

/*
class DepartPoint : public Point
{
public:
	Element* e;

	DepartPoint();
	DepartPoint(const Point& node);
};

class DepartVector
{
public:
	vector<DepartPoint*> pv;

	DepartVector(const int& nv);
	void FindPoints(const vector<Point*>& nodes, double* c_solution[3][2], const double& t_step_size);
	void FindElements(const ElementVector& g_elements);
	void Write();
};
/**/