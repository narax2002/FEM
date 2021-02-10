#include "element.h"

/// <summary>
/// 举府刚飘 积己磊
/// </summary>

Point::Point(const int nv, const int kv, const double xv, const double yv)
{
	n = nv;
	k = kv;
	x = xv;
	y = yv;
}

Element::Element(const int nv)
{
	n = nv;

	p[0] = nullptr;
	p[1] = nullptr;
	p[2] = nullptr;

	e[0] = nullptr;
	e[1] = nullptr;
	e[2] = nullptr;
}