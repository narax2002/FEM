#pragma once
#include "element.h"

/// <summary>
/// 초기 앨리먼트 설정
/// </summary>


// 글로벌 변수
// extern ElementArray* this;

void ElementVector::MakeUp(const int& nv)
{
	// 노드 포인트 수, 앨리먼트 수 설정
	int num_p = (nv + 1) * (nv + 1);
	int num_e = 2 * nv * nv;

	// 노드 포인트
	this->pv.clear();
	this->pv.resize(num_p);

	double step = 1.0 / nv;

	for (int i = 0; i <= nv; ++i) {
		for (int j = 0; j <= nv; ++j) {
			int pn = i * (nv + 1) + j;
			this->pv[pn] = new Point(pn, 0, j*step, i*step);
			if (i == 0 || i == nv || j == 0 || j == nv)
				this->pv[pn]->k = 1;
		}
	}

	// 앨리먼트
	this->ev.clear();
	this->ev.resize(num_e);

	// 포인트 번호
	for (int i = 0;i < nv; ++i) {
		for (int j = 0; j < nv; ++j) {
			int en = 2 * nv * i + 2 * j;
			int pn = (nv + 1) * i + j;

			this->ev[en] = new Element(en);
			this->ev[en + 1] = new Element(en + 1);
			
			this->ev[en]->p[0] = this->pv[pn];
			this->ev[en]->p[1] = this->pv[pn + 1];
			this->ev[en]->p[2] = this->pv[pn + nv + 1];

			this->ev[en + 1]->p[0] = this->pv[pn + 1];
			this->ev[en + 1]->p[1] = this->pv[pn + nv + 2];
			this->ev[en + 1]->p[2] = this->pv[pn + nv + 1];
		}
	}

	// 접하는 앨리먼트 번호
	for (int i = 0; i < nv; ++i) {
		for (int j = 0; j < nv; ++j) {
			int en = 2 * nv * i + 2 * j;
			this->ev[en]->e[0] = this->ev[en + 1];
			this->ev[en]->e[1] = (j == 0) ? nullptr : this->ev[en - 1];
			this->ev[en]->e[2] = (i == 0) ? nullptr : this->ev[en + 1 - 2 * nv];

			this->ev[en + 1]->e[0] = (i == nv - 1) ? nullptr : this->ev[en + 2 * nv];
			this->ev[en + 1]->e[1] = this->ev[en];
			this->ev[en + 1]->e[2] = (j == nv - 1) ? nullptr : this->ev[en + 2];
		}
	}
}
