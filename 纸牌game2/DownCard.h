#pragma once
#include"Card.h"
//#include "CardsCtrl.h"
class DownCard
{
public:
	DownCard();
	~DownCard();
public:
	list<Node>m_lDownCardList[7];
public:
	void GetCards(vector<Card> & vAllCrads);
	void ShowCards(HDC hMemDC, HBITMAP bmpCardBack);
};

