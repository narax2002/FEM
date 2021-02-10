#pragma once
#include <math.h>
/// <summary>
/// 상수 선언
/// 함수 클래스 선언
/// </summary>

const int max_h_ref = 4;
const int max_t_ref = 7;
const double max_time = 1.0;

const double hx[7] = { 0.1012865073235, 0.7974269853531, 0.1012865073235, 0.4701420641051, 0.4701420641051, 0.0597158717898, 0.3333333333333 };
const double hy[7] = { 0.1012865073235, 0.1012865073235, 0.7974269853531, 0.0597158717898, 0.4701420641051, 0.4701420641051, 0.3333333333333 };
const double wt[7] = { 0.0629695902724, 0.0629695902724, 0.0629695902724, 0.0661970763942, 0.0661970763942, 0.0661970763942, 0.1125000000000 };

class Functions
{
public:
	double pi = 4.0 * atan(1.0);
	double nu = 0.05;	// 점성계수

	double funct1(double xv, double yv, double tv);
	double funct2(double xv, double yv, double tv);

	double exact_u1(double xv, double yv, double tv);

	double exact_u1_x(double xv, double yv, double tv);
	double exact_u1_y(double xv, double yv, double tv);
	double exact_u1_t(double xv, double yv, double tv);

	double exact_u2(double xv, double yv, double tv);

	double exact_u2_x(double xv, double yv, double tv);
	double exact_u2_y(double xv, double yv, double tv);
	double exact_u2_t(double xv, double yv, double tv);
};