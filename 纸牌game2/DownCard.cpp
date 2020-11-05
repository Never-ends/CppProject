#include "DownCard.h"



DownCard::DownCard()
{
}


DownCard::~DownCard()
{
}



void DownCard::GetCards(vector<Card>& vAllCrads)
{
	int n = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			Node temp(vAllCrads[n]);
			temp.m_bShow = false;  //
			temp.m_nX = 50 + (71 + 50)*i;
			temp.m_nY = 156 + 30 * j;

			m_lDownCardList[i].push_back(temp);
			n++;
		}
	}

	for (int i = 0; i < 7; i++)
	{
		m_lDownCardList[i].back().m_bShow = true;
	}
}

void DownCard::ShowCards(HDC hMemDC, HBITMAP bmpCardBack)
{
	HDC tempDC = CreateCompatibleDC(hMemDC);

	for (int i = 0; i < 7; i++)
	{
		
			for (list<Node>::iterator ite = m_lDownCardList[i].begin(); ite != m_lDownCardList[i].end(); ite++)
			{
				if (false == (*ite).m_bShow)
					SelectObject(tempDC, bmpCardBack);
				else
					SelectObject(tempDC, (*ite).m_vCard.m_bmpCard);
				BitBlt(hMemDC, (*ite).m_nX, (*ite).m_nY, 71, 96, tempDC, 0, 0, SRCCOPY);
			}
		
	}
	DeleteDC(tempDC);
}
