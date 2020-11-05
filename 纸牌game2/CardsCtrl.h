#pragma once
//#include"Card.h"
#include "DownCard.h"
#include "LeftCard.h"
#include "RightCard.h"

//#include<Windows.h>
//#include"resource.h"
//#include<vector>


//ͷ�ļ�������CardsCtrl
class CardsCtrl
{

public:
	CardsCtrl();
	~CardsCtrl();
public:
	HINSTANCE m_hInstance;
	HWND m_hwnd;
	HBITMAP m_bmpback;//���屳��
	HBITMAP m_bmpCardBack;//���屳����1
	HBITMAP m_bmpCardRecv;//���屳����2
	vector<Card>m_vAllCards; //����52���ƣ�����ֱ�ӳ�ʼ�����Ʋ�����ʼ���б�
public:
	DownCard m_oDownCard;//����DownCard���һ������
	LeftCard m_oLeftCard;//����
	RightCard m_oRightCard;//����
public:
	//�������������������
	void OnInit();//��Ϸ��Դ���س�ʼ��
	void GameInit();//��Ϸ���ݻ�
	void OnPaint(HDC hDc);//��ͼ
	void OnLButtonDown(int x ,int y);//����������
	void OnLButtonup();
	void OnMouseMove(int x,int y);//����ƶ�
public:
	list<Node> m_lMouseList;
	bool MouseGetCard(int x, int y);//�������
	int m_nX;
	int m_nY;

	void ShowMouseCard(HDC hMemDC);
};


