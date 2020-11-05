#pragma once
#include"Card.h"
class RightCard
{
public:
	RightCard();
	~RightCard();
public:
	list<Node> m_lRightCardList[4];

public:
	void GetCards(vector<Card>& vAllCrads);
	void ShowCards(HDC hMemDC, HBITMAP bmpCardBack);
};

