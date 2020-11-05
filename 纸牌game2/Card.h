#pragma once
#include<Windows.h>
#include<TCHAR.h>
//#include "CardsCtrl.h"
//上部头文件和此头文件重复包含
#include"resource.h"
#include<algorithm>
#include<ctime>
//#include"DownCard.h"
#include<list>
#include<vector>
#include <cstdlib>
#include<iostream>
using namespace std;

//包含透明函数库文件
#pragma comment(lib,"Msimg32.lib")

//将需要的头文件都封装在，"Card.h"中，其他只需要包含"Card.h"头文件即可

enum { enum_card_Club, enum_card_Diamond, enum_card_Spade, enum_card_Heart };
//枚举花色分别为：♣梅花，♦方块，♠黑桃，♥红桃，

struct Card
{
	int m_suit;//花色
	int m_nNum;//整形编号
	HBITMAP m_bmpCard;//牌
};
/*
struct Node
{
	Node(Card&vCard)
	{  
		bool m_bshow = true;
		int m_nX = 0;
		int m_nY = 0;
	}
	Card&m_vCard;


};*/
struct Node
{
public:
	Node(Card& vCard) :m_vCard(vCard)
	{
		m_bShow = true;
		m_nX = 0;
		m_nY = 0;
	}

	Card& m_vCard;
	bool m_bShow;
	int m_nX;
	int m_nY;
};