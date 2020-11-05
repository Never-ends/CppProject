#pragma once
//#include"Card.h"
#include "DownCard.h"
#include "LeftCard.h"
#include "RightCard.h"

//#include<Windows.h>
//#include"resource.h"
//#include<vector>


//头文件声明类CardsCtrl
class CardsCtrl
{

public:
	CardsCtrl();
	~CardsCtrl();
public:
	HINSTANCE m_hInstance;
	HWND m_hwnd;
	HBITMAP m_bmpback;//定义背景
	HBITMAP m_bmpCardBack;//定义背景牌1
	HBITMAP m_bmpCardRecv;//定义背景牌2
	vector<Card>m_vAllCards; //所有52张牌，不可直接初始化，移步至初始化列表
public:
	DownCard m_oDownCard;//定义DownCard类的一个对象
	LeftCard m_oLeftCard;//左牌
	RightCard m_oRightCard;//右牌
public:
	//五个基本操作函数声明
	void OnInit();//游戏资源加载初始化
	void GameInit();//游戏数据化
	void OnPaint(HDC hDc);//画图
	void OnLButtonDown(int x ,int y);//鼠标左键按下
	void OnLButtonup();
	void OnMouseMove(int x,int y);//鼠标移动
public:
	list<Node> m_lMouseList;
	bool MouseGetCard(int x, int y);//鼠标拿牌
	int m_nX;
	int m_nY;

	void ShowMouseCard(HDC hMemDC);
};


