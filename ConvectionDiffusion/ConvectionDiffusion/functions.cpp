#include "functions.h"

double Functions::funct1(double xv, double yv, double tv)
{
	//return 0.0;
	return 2.0 * this->nu * tv * tv * (xv - xv * xv + yv - yv * yv) + 2.0 * tv * (xv - xv * xv) * (yv - yv * yv) \
		+ tv * tv * (xv - xv * xv) * (yv - yv * yv) * tv * tv * (1.0 - 2.0 * xv) * (yv - yv * yv) \
		+ exp(-tv) * sin(xv) * sin(yv) * tv * tv * (xv - xv * xv) * (1.0 - 2.0 * yv);
}

double Functions::funct2(double xv, double yv, double tv)
{
	//return 0.0;
	return 2 * this->nu * exp(-tv) * sin(xv) * sin(yv) - exp(-tv) * sin(xv) * sin(yv) \
		+ tv * tv * (xv - xv * xv) * (yv - yv * yv) * exp(-tv) * cos(tv) * sin(tv) \
		+ exp(-tv) * sin(xv) * sin(yv) * exp(-tv) * sin(xv) * cos(yv);
}

/// <summary>
/// function of u1
/// </summary>
double Functions::exact_u1(double xv, double yv, double tv)
{
	return tv * tv * (xv - xv * xv) * (yv - yv * yv);
}

double Functions::exact_u1_x(double xv, double yv, double tv)
{
	return tv * tv * (1.0 - 2.0 * xv) * (yv - yv * yv);
}

double Functions::exact_u1_y(double xv, double yv, double tv)
{
	return tv * tv * (xv - xv * xv) * (1.0 - 2.0 * yv);
}

double Functions::exact_u1_t(double xv, double yv, double tv)
{
	return 2.0 * tv * (xv - xv * xv) * (yv - yv * yv);
}

/// <summary>
/// function of u2
/// </summary>
double Functions::exact_u2(double xv, double yv, double tv)
{
	return exp(-tv) * sin(xv) * sin(yv);
}

double Functions::exact_u2_x(double xv, double yv, double tv)
{
	return exp(-tv) * cos(xv) * sin(yv);
}

double Functions::exact_u2_y(double xv, double yv, double tv)
{
	return exp(-tv) * sin(xv) * cos(yv);
}

double Functions::exact_u2_t(double xv, double yv, double tv)
{
	return -exp(-tv) * sin(xv) * sin(yv);
}