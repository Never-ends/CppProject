#include "CardsCtrl.h"

//CardsCtrl类
CardsCtrl::CardsCtrl() :m_vAllCards(52)//结构体类型不可直接int初始化，借助初始化列表
{
	m_hInstance = NULL;
	m_bmpback = NULL;
	m_bmpCardBack = NULL;//定义背景牌
	m_bmpCardRecv = NULL;
	HWND m_hwnd = NULL;
	m_nX = 0;
	m_nY = 0;

}


CardsCtrl::~CardsCtrl()
{
	//释放内核对象，防止内核泄漏
	DeleteObject(m_bmpback);
	DeleteObject(m_bmpCardBack);
	DeleteObject(m_bmpCardRecv);
	for (int i = 0; i < 52; i++)
	{
		DeleteObject(m_vAllCards[i].m_bmpCard);
	}
}


void CardsCtrl::OnInit()
{
	//加载背景图片
	m_bmpback = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP55));

	//加载52张牌

	//1加载梅花♣
	for (int i = 0; i < 13; i++)
	{
		m_vAllCards[i].m_suit = enum_card_Club;//第一个花色是梅花♣
		m_vAllCards[i].m_nNum = i + 1;//第一个是0+1，即A
		m_vAllCards[i].m_bmpCard = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
		//从第1张资源图片开始是梅花A
	}
	//2加载方块♦
	for (int i = 13; i < 26; i++)//也可修改此处条件
	{
		m_vAllCards[i].m_suit = enum_card_Diamond;//第一个花色是方块♦
		m_vAllCards[i].m_nNum = i-13 + 1;//第一个是0+1，即A
		m_vAllCards[i].m_bmpCard = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
		//从第14张资源图片开始是方块A

	}
	//3加载红桃
	for (int i = 26; i < 39; i++)
	{
		m_vAllCards[i].m_suit = enum_card_Heart;//第一个花色是红桃
		m_vAllCards[i].m_nNum = i-26 + 1;//第一个是0+1，即A
		m_vAllCards[i].m_bmpCard = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
		//从第27张资源图片开始是红桃A

	}
	//4加载黑桃
	for (int i = 39; i < 52; i++)
	{
		m_vAllCards[i].m_suit = enum_card_Spade;//第一个花色是黑桃
		m_vAllCards[i].m_nNum = i-39 + 1;//第一个是0+1，即A
		m_vAllCards[i].m_bmpCard = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 + i));
		//从第40张资源图片开始是黑桃A
		//一直到52结束
	}



	//加载扑克牌背景
	m_bmpCardBack = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP58));//左和下的背景牌
	m_bmpCardRecv = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP57));//右边背景牌

	srand( (unsigned int) time(NULL));//生成随机种子，只需要在初始化的时候调用一次即可


}


void CardsCtrl::GameInit()
{
	//洗牌
	random_shuffle(m_vAllCards.begin(), m_vAllCards.end());

	//发下牌
	m_oDownCard.GetCards(m_vAllCards);//28张

	//发左上角牌

	m_oLeftCard.GetCards(m_vAllCards);
	
	
	//右上角的牌不需要发
}

//显示窗口
void CardsCtrl::OnPaint(HDC hDc)
{
	//1创建内存DC(ID)
	HDC hMemDC = CreateCompatibleDC(hDc);

	//2创建兼容性位图
	HBITMAP bmpback = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IDB_BITMAP55));
	//每次重新加载背景图片，消除拖牌轨迹残留

	//CreateCompatibleBitmap(, );


	//3将DC与位图绑定在一起
	SelectObject(hMemDC, bmpback);

	//4展示下，左，右牌
	m_oDownCard.ShowCards(hMemDC, m_bmpCardBack);
	m_oLeftCard.ShowCards(hMemDC, m_bmpCardBack);
	m_oRightCard.ShowCards(hMemDC, m_bmpCardRecv);
	//5展示鼠标牌
	ShowMouseCard(hMemDC);


	//第六步必须在前几步之后否则会不显示牌！！！


	//6将内存DC传递到窗口dc
	BitBlt(hDc, 0, 0, 900,630, hMemDC, 0, 0, SRCCOPY);
	//窗口，起始坐标，宽度，高度，内存，起始坐标

	DeleteDC(hMemDC);//释放内存，资源问题，绘图一直运行
	DeleteObject(bmpback);
}
//相邻两牌的距离也为50，牌的宽度71，长度96
//鼠标按下
void CardsCtrl::OnLButtonDown(int x,int y)
{
	//窗口左边框到左上角牌的左边框距离为50，，
	//窗口上边框到牌的上边框距离为30

	//左上翻牌，确定左上区域坐标 X[50,200]  Y[30,126]
	if (x < 200 && x >= 50 && y <= 126 && y >= 30)
	{
		//点击指定区域，小窗口提示：MessageBox(NULL, L"Hello", L"左上角", MB_OK);

	}

	//右上牌操作
	//窗口左边框到牌的左边框距离为50
	else if (x >= 413 && y <= 126 && y >= 30)
	{
		

	}

	//下面的牌操作
	else if (y >= 156)
	{
		if (false == MouseGetCard(x, y))
		{
			MessageBox(NULL, L"提示",L"MOUSE get card false",MB_OK);
		}
	}
}

//是否可以拿牌
bool CardsCtrl::MouseGetCard(int x, int y) 
{
	//判断点的哪一列牌
	int nx = (x - 50) / 121;
	int ny = 0;

	//该列牌的数量
	int nCount = m_oDownCard.m_lDownCardList[nx].size();

	//点击那一列牌中尾巴那张牌坐标范围
	if (y >= (nCount - 1) * 30 + 156 && y < (nCount - 1) * 30 + 252)
	{
		ny = nCount -1;

	}

	//点压着的牌
	else if (y < (nCount - 1) * 30 + 156)
		{
		ny = (y - 156) / 30;

		}
	//得到牌了
	list<Node>::iterator ite1 = m_oDownCard.m_lDownCardList[nx].begin();
	for (int i = 0; i < ny; i++)
	{
		ite1++;

	}
	if (true == ite1->m_bShow)
	{
		//鼠标拿牌
		m_lMouseList.insert(m_lMouseList.begin(), ite1, m_oDownCard.m_lDownCardList[nx].end());
		//被拿的那一列牌删牌
		m_oDownCard.m_lDownCardList[nx].erase(ite1, m_oDownCard.m_lDownCardList[nx].end());
		//记录坐标
		m_nX = x;
		m_nY = y;
		return true;
	}
	return false;
}
void CardsCtrl::OnLButtonup()
{

}
void CardsCtrl::OnMouseMove(int x,int y)
{
	if (m_lMouseList.size() == 0)
	{
		return;
	}

	//改链表坐标
	//1计算相对移动位置
	int tempx = x - m_nX;
	int tempy = y - m_nY;
	//记录牌新的坐标
	for (list<Node>::iterator ite = m_lMouseList.begin(); ite != m_lMouseList.end(); ite++)
	{
		ite->m_nX = m_nX + tempx;
		ite->m_nY = m_nY + tempy;

	}
	//2将位置加载在牌的坐标上
	m_nX = x;
	m_nY = y;
	SendMessage(m_hwnd,WM_PAINT,0,0);//刷新窗口
	/*
	HDC hDc = GetDC(m_hwnd);
	OnPaint(hDc);
	ReleaseDC(m_hwnd, hDc);
	*/
}

//展示鼠标牌
void CardsCtrl::ShowMouseCard(HDC hMemDC)
{

	HDC tempDC = CreateCompatibleDC(hMemDC);

	

		for (list<Node>::iterator ite = m_lMouseList.begin(); ite != m_lMouseList.end(); ite++)
		{
		//鼠标牌不需要判断
			SelectObject(tempDC, (*ite).m_vCard.m_bmpCard);
			BitBlt(hMemDC, (*ite).m_nX, (*ite).m_nY, 71, 96, tempDC, 0, 0, SRCCOPY);
			
			//用下面的透明色函数替换，RGB(255,255,255)是将白色透明
			//TransparentBlt(hMemDC, (*ite).m_nX, (*ite).m_nY, 71, 96, tempDC, 0, 0, 71, 96,RGB(255,255,255));
		
		}

	
	DeleteDC(tempDC);
}
