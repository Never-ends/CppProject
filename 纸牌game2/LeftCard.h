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

	//翻开和扣上的两个链表（牌）
public:
	void GetCards(vector<Card> & vAllCrads);
	void ShowCards(HDC hMemDC, HBITMAP bmpCardBack);

};

