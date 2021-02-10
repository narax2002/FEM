#pragma once
#include "element.h"

/// <summary>
/// 초기 앨리먼트 설정
/// </summary>


// 글로벌 변수
// extern ElementArray* this;

void ElementVector::Initial()
{
	// 초기 노드 포인트
	this->pv.clear();

	this->pv.push_back(new Point(0, 1, -1.0, -1.0));
	this->pv.push_back(new Point(1, 1, 1.0, -1.0));

	this->pv.push_back(new Point(2, 1, -1.0, 1.0));
	this->pv.push_back(new Point(3, 1, 1.0, 1.0));

	// 초기 앨리먼트
	this->ev.clear();
	for(int i=0;i<2; ++i) this->ev.push_back(new Element(i));

	// 초기 포인트 번호
	this->ev[0]->p[0] = this->pv[0];
	this->ev[0]->p[1] = this->pv[1];
	this->ev[0]->p[2] = this->pv[2];

	this->ev[1]->p[0] = this->pv[1];
	this->ev[1]->p[1] = this->pv[3];
	this->ev[1]->p[2] = this->pv[2];

	// 초기 접하는 앨리먼트 번호
	this->ev[0]->e[0] = this->ev[1];
	this->ev[0]->e[1] = nullptr;
	this->ev[0]->e[2] = nullptr;

	this->ev[1]->e[0] = nullptr;
	this->ev[1]->e[1] = this->ev[0];
	this->ev[1]->e[2] = nullptr;
}