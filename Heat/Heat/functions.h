#pragma once
#include <math.h>
/// <summary>
/// 상수 선언
/// 함수 클래스 선언
/// </summary>

const int max_h_ref = 5;
const int max_t_ref = 10;
//const int max_t_iter = 10;
const double max_time = 1.0;


const double hx[7] = { 0.1012865073235, 0.7974269853531, 0.1012865073235, 0.4701420641051, 0.4701420641051, 0.0597158717898, 0.3333333333333 };
const double hy[7] = { 0.1012865073235, 0.1012865073235, 0.7974269853531, 0.0597158717898, 0.4701420641051, 0.4701420641051, 0.3333333333333 };
const double wt[7] = { 0.0629695902724, 0.0629695902724, 0.0629695902724, 0.0661970763942, 0.0661970763942, 0.0661970763942, 0.1125000000000 };

const double bhx[3] = { 0.1127016544342, 0.5000000000000, 0.8872983455658 };
const double bwt[3] = { 0.2777777777778, 0.4444444444444, 0.2777777777778 };

class Functions
{
public:
	double pi = 4.0 * atan(1.0);
	double nu = 1.0;
	double t_init = 10.0;

	double funct1(double xv, double yv, double tv);

	double exact_u(double xv, double yv, double tv);

	double exact_u_x(double xv, double yv, double tv);
	double exact_u_y(double xv, double yv, double tv);
	double exact_u_t(double xv, double yv, double tv);
};