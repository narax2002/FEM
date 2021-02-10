#include "element.h"

void DepartOperator::FindPoints(vector<Point*>& nodes, double* c_solution[3][2], const double& t_step_size)
{
	// departure point 찾기
	// dX/dt = u(X(t_{n+1},x;t),t)
	// X(t_{n+1},x;t_{n+1}) = x
	//
	// 1st order Euler method

	for (auto& it : nodes) {
		int cpn = it->n;

		it->pp = new Point(cpn);
		it->pp->pp = new Point(cpn);

		Point* cp = it->pp;
		Point* pp = cp->pp;

		pp->x = it->x - 2.0 * t_step_size * c_solution[0][0][cpn];
		pp->y = it->y - 2.0 * t_step_size * c_solution[0][1][cpn];

		if (pp->x < 0.0) pp->x = 0.0;
		if (pp->x > 1.0) pp->x = 1.0;
		if (pp->y < 0.0) pp->y = 0.0;
		if (pp->y > 1.0) pp->y = 1.0;

		cp->x = (it->x + pp->x) / 2.0;
		cp->y = (it->y + pp->y) / 2.0;

		if (cp->x == 0.0 || cp->x == 1.0 || cp->y == 0.0 || cp->y == 1.0) cp->k = 1;
		if (pp->x == 0.0 || pp->x == 1.0 || pp->y == 0.0 || pp->y == 1.0) pp->k = 1;
	}
}

void DepartOperator::CalculatePP(Element& c_element, const double& xt, const double& yt, double* c_solution[3][2], double c_sol[2])
{
	// departure point가 속해있는 앨리먼트 찾기
	Element* ce = &c_element;
	double temp;
	while (1) {
		temp = (yt - ce->p[0]->y) * (ce->p[1]->x - ce->p[0]->x) - (xt - ce->p[0]->x) * (ce->p[1]->y - ce->p[0]->y);
		if (temp < 0) {
			ce = ce->e[2];
			continue;
		}
		temp = (yt - ce->p[1]->y) * (ce->p[2]->x - ce->p[1]->x) - (xt - ce->p[1]->x) * (ce->p[2]->y - ce->p[1]->y);
		if (temp < 0) {
			ce = ce->e[0];
			continue;
		}
		temp = (yt - ce->p[2]->y) * (ce->p[0]->x - ce->p[2]->x) - (xt - ce->p[2]->x) * (ce->p[0]->y - ce->p[2]->y);
		if (temp < 0) {
			ce = ce->e[1];
			continue;
		}
		break;
	}

	// reference element에서의 좌표 찾기
	double xz = xt - ce->p[0]->x;
	double yz = yt - ce->p[0]->y;
	
	double jac[2][2];
	jac[0][0] = ce->p[1]->x - ce->p[0]->x;
	jac[0][1] = ce->p[2]->x - ce->p[0]->x;
	jac[1][0] = ce->p[1]->y - ce->p[0]->y;
	jac[1][1] = ce->p[2]->y - ce->p[0]->y;
	double det = jac[0][0] * jac[1][1] - jac[0][1] * jac[1][0];

	temp = (yz * jac[0][0] - xz * jac[1][0]) / det;
	xz = (xz * jac[1][1] - yz * jac[0][1]) / det;
	yz = temp;

	// c_sol 계산
	c_sol[0] = 0.0;
	c_sol[0] += c_solution[0][0][ce->p[0]->n] * (1.0 - xz - yz) + c_solution[0][0][ce->p[1]->n] * xz + c_solution[0][0][ce->p[2]->n] * yz;
	c_sol[1] = 0.0;
	c_sol[1] += c_solution[0][1][ce->p[0]->n] * (1.0 - xz - yz) + c_solution[0][1][ce->p[1]->n] * xz + c_solution[0][1][ce->p[2]->n] * yz;
}


/*
void DepartVector::FindPoints(const vector<Point*>& nodes, double* c_solution[3][2], const double& t_step_size)
{
	for (const auto& it : nodes) {
		int i = it->n;
		this->pv[i][0] = DepartPoint(*it);
		this->pv[i][1] = DepartPoint(*it);
	}

	// departure point 찾기
	// dX/dt = u(X(t_{n+1},x;t),t)
	// X(t_{n+1},x;t_{n+1}) = x
	//
	// 1st order Euler method
	
	for (auto& it : this->pv) {
		int cpn = it[0].n;

		it[1].x -= 2.0 * t_step_size * c_solution[0][0][cpn];
		it[1].y -= 2.0 * t_step_size * c_solution[0][1][cpn];

		if (it[1].x < 0.0) it[1].x = 0.0;
		if (it[1].x > 1.0) it[1].x = 1.0;
		if (it[1].y < 0.0) it[1].y = 0.0;
		if (it[1].y > 1.0) it[1].y = 1.0;
		
		it[0].x = (3.0 * it[0].x + it[1].x) / 4.0;
		it[0].y = (3.0 * it[0].y + it[1].y) / 4.0;


		if (it[0].x == 0.0 || it[0].x == 1.0 || it[0].y == 0.0 || it[0].y == 1.0) it[0].k = 1;
		if (it[1].x == 0.0 || it[1].x == 1.0 || it[1].y == 0.0 || it[1].y == 1.0) it[1].k = 1;
	}

}

void DepartVector::FindElements(const ElementVector& g_elements)
{
	// departure point가 속해있는 앨리먼트 찾기
	Element* ce = g_elements.ev[0];
	for (auto& it : this->pv) {
		double temp;
		while (1) {
			temp = (it[0].y - ce->p[0]->y) * (ce->p[1]->x - ce->p[0]->x) - (it[0].x - ce->p[0]->x) * (ce->p[1]->y - ce->p[0]->y);
			if (temp < 0) {
				ce = ce->e[2];
				continue;
			}
			temp = (it[0].y - ce->p[1]->y) * (ce->p[2]->x - ce->p[1]->x) - (it[0].x - ce->p[1]->x) * (ce->p[2]->y - ce->p[1]->y);
			if (temp < 0) {
				ce = ce->e[0];
				continue;
			}
			temp = (it[0].y - ce->p[2]->y) * (ce->p[0]->x - ce->p[2]->x) - (it[0].x - ce->p[2]->x) * (ce->p[0]->y - ce->p[2]->y);
			if (temp < 0) {
				ce = ce->e[1];
				continue;
			}
			it[0].e = ce;
			break;
		}

		while (1) {
			temp = (it[1].y - ce->p[0]->y) * (ce->p[1]->x - ce->p[0]->x) - (it[1].x - ce->p[0]->x) * (ce->p[1]->y - ce->p[0]->y);
			if (temp < 0) {
				ce = ce->e[2];
				continue;
			}
			temp = (it[1].y - ce->p[1]->y) * (ce->p[2]->x - ce->p[1]->x) - (it[1].x - ce->p[1]->x) * (ce->p[2]->y - ce->p[1]->y);
			if (temp < 0) {
				ce = ce->e[0];
				continue;
			}
			temp = (it[1].y - ce->p[2]->y) * (ce->p[0]->x - ce->p[2]->x) - (it[1].x - ce->p[2]->x) * (ce->p[0]->y - ce->p[2]->y);
			if (temp < 0) {
				ce = ce->e[1];
				continue;
			}
			it[1].e = ce;
			break;
		}
	}
}
/**/