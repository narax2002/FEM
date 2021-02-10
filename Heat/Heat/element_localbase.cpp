#include "element.h"

void LocalBase::MakeUp(const Element& c_element, const double hx, const double hy)
{
	this->base[0][0] = 1.0 - hx - hy;
	this->base[0][1] = -1.0;
	this->base[0][2] = -1.0;

	this->base[1][0] = hx;
	this->base[1][1] = 1.0;
	this->base[1][2] = 0.0;

	this->base[2][0] = hy;
	this->base[2][1] = 0.0;
	this->base[2][2] = 1.0;


	// 레퍼런스 앨리먼트에서 현재 앨리먼트로의 함수 (X,Y) -> (x,y)
	// x좌표 = (x_1 - x_0)X + (x_2 - x_0)Y + x_0
	// y좌표 = (y_1 - y_0)X + (y_2 - y_0)Y + y_0
	// Jacoian = d(x,y) / d(X,Y)
	double jac[2][2];
	jac[0][0] = c_element.p[1]->x - c_element.p[0]->x;
	jac[0][1] = c_element.p[2]->x - c_element.p[0]->x;
	jac[1][0] = c_element.p[1]->y - c_element.p[0]->y;
	jac[1][1] = c_element.p[2]->y - c_element.p[0]->y;
	this->det = jac[0][0] * jac[1][1] - jac[0][1] * jac[1][0];

	
	for (int i = 0; i < 3; ++i) {
		double a = this->base[i][1];
		double b = this->base[i][2];

		this->base[i][1] = (a * jac[1][1] - b * jac[0][1]) / det;
		this->base[i][2] = (b * jac[0][0] - a * jac[1][0]) / det;
	}	
}