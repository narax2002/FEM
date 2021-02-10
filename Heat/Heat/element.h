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
	int k;
	double x;
	double y;
	Point(const int nv, const int k, const double xv, const double yv);
};

class Element
{
public:
	int n;
	Point* p[3];
	Element* e[3];
	Element(const int nv);
};

class ElementVector
{
public:
	vector<Point*> pv;
	vector<Element*> ev;

	void Initial();
	void Refinement();
	void Write();
};


class LocalBase
{
public:
	double base[3][3]; // 번호, (0:함수값, 1:x미분, 2:미분)
	double det;

	void MakeUp(const Element& c_element, const double xv, const double yv);
};