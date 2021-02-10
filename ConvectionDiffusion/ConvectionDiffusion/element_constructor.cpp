#include "element.h"

/// <summary>
/// 举府刚飘 积己磊
/// </summary>

Point::Point(const int& nv)
{
	n = nv;
	k = 0;
	x = 0.0;
	y = 0.0;
	pp = nullptr;
}

Point::Point(const int& nv, const int& kv, const double& xv, const double& yv)
{
	n = nv;
	k = kv;
	x = xv;
	y = yv;
	pp = nullptr;
}

Element::Element(const int& nv)
{
	n = nv;

	p[0] = nullptr;
	p[1] = nullptr;
	p[2] = nullptr;

	e[0] = nullptr;
	e[1] = nullptr;
	e[2] = nullptr;
}

LocalBase::LocalBase()
{
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) base[i][j] = 0.0;
	}
	det = 0.0;
}

/*
DepartPoint::DepartPoint() : Point()
{
	e = nullptr;
}

DepartPoint::DepartPoint(const Point& node) : Point(node.n, 0, node.x, node.y)
{
	e = nullptr;
}

DepartVector::DepartVector(const int& nv)
{
	pv.clear();
	pv.resize(nv);
	for (auto& it : pv) {
		it = new DepartPoint[2];
	}
}
/**/