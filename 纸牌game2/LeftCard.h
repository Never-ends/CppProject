#pragma once
#include"Card.h"
class LeftCard
{
public:
	LeftCard();
	~LeftCard();
public:
	list<Node>m_lLeftCardListTrue;
	list<Node>m_lLeftCardListFalse;

	//�����Ϳ��ϵ����������ƣ�
public:
	void GetCards(vector<Card> & vAllCrads);
	void ShowCards(HDC hMemDC, HBITMAP bmpCardBack);

};

