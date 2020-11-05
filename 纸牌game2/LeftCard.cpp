#include "LeftCard.h"

void LeftCard::GetCards(vector<Card>& vAllCrads)
{
	int n = 0;
	for (int i = 28; i < 52; i++)
	{
		Node temp(vAllCrads[i]);
		temp.m_bShow = false;  //
		temp.m_nX = 50 + 3 * (i - 28);
		temp.m_nY = 30;

		m_lLeftCardListFalse.push_back(temp);
	}
}


void LeftCard::ShowCards(HDC hMemDC, HBITMAP bmpCardBack)
{
	HDC tempDC = CreateCompatibleDC(hMemDC);

	for (list<Node>::iterator ite = m_lLeftCardListFalse.begin(); ite != m_lLeftCardListFalse.end(); ite++)
	{
		if (false == (*ite).m_bShow)
			SelectObject(tempDC, bmpCardBack);
		else
			SelectObject(tempDC, (*ite).m_vCard.m_bmpCard);
		BitBlt(hMemDC, (*ite).m_nX, (*ite).m_nY, 71, 96, tempDC, 0, 0, SRCCOPY);
	}

	DeleteDC(tempDC);
}

LeftCard::LeftCard()
{
}


LeftCard::~LeftCard()
{
}

