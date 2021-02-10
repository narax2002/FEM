#include "functions.h"

double Functions::funct1(double xv, double yv, double tv)
{
	//return 2.0 * tv * (xv - xv * xv) * (yv - yv * yv) + 2.0 * this->nu * tv * tv * (xv - xv * xv + yv - yv * yv);
	return 0.0;
}

double Functions::exact_u(double xv, double yv, double tv)
{
	//return tv * tv * (xv - xv * xv) * (yv - yv * yv);
	double tn = this->t_init + tv;
	return exp(-(xv * xv + yv * yv) / (4.0 * this->nu * tn)) / (4.0 * this->pi * tn);
}

double Functions::exact_u_x(double xv, double yv, double tv)
{
	//return tv * tv * (1.0 - 2.0 * xv) * (yv - yv * yv);
	double tn = this->t_init + tv;
	return -exp(-(xv * xv + yv * yv) / (4.0 * this->nu * tn)) * xv / (8.0 * this->nu * this->pi * tn * tn);
}

double Functions::exact_u_y(double xv, double yv, double tv)
{
	//return tv * tv * (xv - xv * xv) * (1.0 - 2.0 * yv);
	double tn = this->t_init + tv;
	return -exp(-(xv * xv + yv * yv) / (4.0 * this->nu * tn)) * yv / (8.0 * this->nu * this->pi * tn * tn);
}

double Functions::exact_u_t(double xv, double yv, double tv)
{
	//return 2.0 * tv * (xv - xv * xv) * (yv - yv * yv);
	double tn = this->t_init + tv;
	return exp(-(xv * xv + yv * yv) / (4.0 * this->nu * tn)) * (xv * xv + yv * yv - 4.0 * this->nu * tn) / (16.0 * this->nu * this->pi * tn * tn * tn);
}