#include "element.h"

/// <summary>
/// 균일하게 앨리먼트 분할
/// </summary>


// 글로벌 변수
//extern ElementArray* this;


void ElementVector::Refinement()
{
	// 로컬 변수
	vector<Element*> c_ev = this->ev;
	vector<Element*> n_ev;
	int c_max = (int)c_ev.size();
	for (int i = 0; i < 4 * c_max; ++i) n_ev.push_back(new Element(i));

	int n_max = c_max;
	//  앨리먼트 추가
	for (auto& it : c_ev) {
		int c_n = (int) it->n;
		Element* n_e = n_ev[c_n];

		// 현재 앨리먼트에 접하는 앨리먼트 설정
		n_e->e[0] = n_ev[n_max];
		n_e->e[1] = n_ev[n_max + 1];
		n_e->e[2] = n_ev[n_max + 2];

		// 새로운 앨리먼트에 접하는 앨리먼트 설정 및
		// 현재 앨리먼트의 포인트 설정
		for (int i = 0; i < 3; ++i) {
			// 새로운 앨리먼트에 접하는 앨리먼트 설정
			int ip = (i + 1 < 3) ? i + 1 : i - 2;
			int im = (i + 2 < 3) ? i + 2 : i - 1;
			int j = 0;

			n_ev[n_max + i]->e[i] = n_e;


			Element* a_e = it->e[i];

			if (a_e == nullptr) {
				n_ev[n_max + ip]->e[i] = nullptr;
				n_ev[n_max + im]->e[i] = nullptr;
			}
			else {
				if (a_e->e[0] == it) j = 0;
				if (a_e->e[1] == it) j = 1;
				if (a_e->e[2] == it) j = 2;

				int jp = (j + 1 < 3) ? j + 1 : j - 2;
				int jm = (j + 2 < 3) ? j + 2 : j - 1;

				n_ev[n_max + ip]->e[i] = n_ev[c_max + 3 * a_e->n + jm];
				n_ev[n_max + im]->e[i] = n_ev[c_max + 3 * a_e->n + jp];
			}

			// 현재 앨리먼트의 포인트 설정
			if (a_e == nullptr) {
				// 새로운 포인트 추가
				double nx = (it->p[ip]->x + it->p[im]->x) / 2;
				double ny = (it->p[ip]->y + it->p[im]->y) / 2;
				
				n_e->p[i] = new Point((int)this->pv.size(), 1, nx, ny);
				this->pv.push_back(n_e->p[i]);
			}
			else if (c_n < a_e->n ) {
				// 새로운 포인트 추가
				double nx = (it->p[ip]->x + it->p[im]->x) / 2;
				double ny = (it->p[ip]->y + it->p[im]->y) / 2;

				n_e->p[i] = new Point((int)this->pv.size(), 0, nx, ny);
				this->pv.push_back(n_e->p[i]);
			}
			else {
				n_e->p[i] = n_ev[a_e->n]->p[j];
			}
		}

		// 새로운 앨리먼트의 포인트 설정
		n_ev[n_max]->p[0] = it->p[0];
		n_ev[n_max]->p[1] = n_e->p[2];
		n_ev[n_max]->p[2] = n_e->p[1];
		n_ev[n_max + 1]->p[0] = n_e->p[2];
		n_ev[n_max + 1]->p[1] = it->p[1];
		n_ev[n_max + 1]->p[2] = n_e->p[0];
		n_ev[n_max + 2]->p[0] = n_e->p[1];
		n_ev[n_max + 2]->p[1] = n_e->p[0];
		n_ev[n_max + 2]->p[2] = it->p[2];

		// 앨리먼트 수 업데이트
		n_max += 3;
	}

	// 앨리먼트 업데이트
	this->ev = n_ev;
	c_ev.clear();
}
