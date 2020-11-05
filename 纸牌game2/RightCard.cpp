#include "RightCard.h"



RightCard::RightCard()
{
}


RightCard::~RightCard()
{
}
#include "RightCard.h"


void RightCard::GetCards(vector<Card>& vAllCrads)
{

}//不用发牌

//展示右牌
void RightCard::ShowCards(HDC hMemDC, HBITMAP bmpCardBack)
{
	HDC tempDC = CreateCompatibleDC(hMemDC);

	for (int i = 0; i < 4; i++)
	{
		if (m_lRightCardList[i].empty())
			SelectObject(tempDC, bmpCardBack);
		else
			SelectObject(tempDC, m_lRightCardList[i].back().m_vCard.m_bmpCard);
		BitBlt(hMemDC, 413 + 121 * i, 30, 71, 96, tempDC, 0, 0, SRCCOPY);
	}

	DeleteDC(tempDC);
}
