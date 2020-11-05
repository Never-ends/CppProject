#include "CardsCtrl.h"//必须包含
#include "Card.h"//可以不包含
#include<Windows.h>
#include<iostream>
#include<TCHAR.h>
using namespace std;

//将需要的头文件都封装在，"Card.h"中，其他只需要包含"Card.h"头文件即可
//主函数

//声明对象：全局对象g_+对象名，局部对象m_+对象名
CardsCtrl g_oCards;//声明一个全局对象
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam);//
//声明回调函数

/*
应用程序的实例句柄即当前程序的id号
//HINSTANCE本质是一个结构体的重命名
//hPreInstance前一个实例的id（目前不实用，保留为了保持向下兼容性）
//LPSTR:命令行参数,通过控制台cmd调用命令程序
//nShowCmd窗口显示方式默认传1

以上4种数据类型不能变，否则报错

//CALLBACK 调用约定，由系统main函数调用
调用约定的作用：
1决定函数名的编译方式（动态链接库）
2决定函数参数的入栈顺序，从左向右还是从右向左
3决定函数的调用时间

CALLBACK（回调函数） , _stdcall, WINAPI,三个约定本质都一样用哪个都行
*/

//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
//sal：微软源代码注释语言（本质辅助我们避免野指针）

int CALLBACK WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,// char*  LP开头一般是指针
	_In_ int nShowCmd    //窗口展示，最大最小化
)
{

	g_oCards.m_hInstance = hInstance;

	//1.定义窗口结构体
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);//结构体大小
	wc.cbWndExtra = NULL;//窗口额外大小
	wc.hbrBackground = (HBRUSH)COLOR_GRAYTEXT;//背景画刷，决定背景颜色，灰色
	wc.hCursor = NULL;//光标样式,系统默认，也可以自己画
	wc.hIcon = NULL;//图标样式，小图标
	wc.hIconSm = NULL;//任务栏图标
	wc.hInstance = hInstance;//实例化句柄，关联主窗口
	wc.lpfnWndProc = WndProc;//回调函数nullptr
	wc.lpszClassName = TEXT("CP3window");//窗口类名字
	/*报错修改方式：
	1前面加L，L"cp3window"
	2前面加_T自动识别,_T("cwp3window")和头文件#include<TCHAR.h>
	3前面加TEXT等同于_T自动识别功能,TEXT("cwp3window"),但不需要加头文件#include<TCHAR.h>
	4修改项目属性将默认的Unicode字符集改成多字节字符集（一般不改）
	*/
	wc.lpszMenuName = NULL;//菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;//垂直|水平拉伸，窗口重绘


	//2.注册窗口结构体
	RegisterClassEx(&wc);//参数是窗口类的地址
	//两种命名：RegisterClassEX/RegisterClass
	//取决于定义窗口类结构体 WNDCLASSEX 是否加Ex，配套使用


	//3.创建窗口
	HWND hWnd = CreateWindowEx
	(WS_EX_OVERLAPPEDWINDOW, TEXT("CP3window"), L"纸牌居佩佩🐖", WS_OVERLAPPEDWINDOW, 400, 200, 900, 630,
		NULL, NULL, hInstance, NULL);
	//父子窗口，菜单，,传数据给回调窗口
	if (NULL == hWnd)
	{
		//返回值为空，失败
		return 1;
	}

	g_oCards.m_hwnd = hWnd;
	//4.显示窗口
	ShowWindow(hWnd, nShowCmd);//nShowCmd等同于1

	//5.更新窗口
	UpdateWindow(hWnd);
	
	//6.消息循环：从消息队列拿消息,到回调函数处理
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))//接受所有范围内的消息
	{
		TranslateMessage(&msg);//虚拟消息翻译成字符消息
		DispatchMessage(&msg);//分发消息，调用回调函数

	}

	return 0;
}


//回调函数，操作系统调用
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
//Wpram传递整型数据， lParam传递非整形数据
{
	HDC hDc;
	PAINTSTRUCT ps;
	
	switch (msgID)
	{
		//WM：windows message 
	case WM_CREATE://只在窗口刚创建时执行一次，作初始化作用
		g_oCards.OnInit();
		g_oCards.GameInit();



		/*刷新窗口，否则我的编译器没反应*/
		/*
		hDc = BeginPaint(hWnd, &ps);
		g_oCards.OnPaint(hDc);
		EndPaint(hWnd, &ps);
		*/
		break;

	case WM_PAINT://绘图，窗口每次发生变化都会通过UpdateWindow(hWnd)函数产生这个消息，
		
		//下面的beginPaint函数使用有问题，得到dc属性不同，暂不使用
		
		hDc = BeginPaint(hWnd, &ps);
		g_oCards.OnPaint(hDc);
		EndPaint(hWnd, &ps);
		
		hDc = GetDC(hWnd);
		g_oCards.OnPaint(hDc);
		ReleaseDC(hWnd,hDc);
		
	
		break;

	case WM_LBUTTONDOWN://鼠标左键按下操作
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		g_oCards.OnLButtonDown(x, y);
		break;
	}//加{}或者将定义的x，y在与switch平齐的位置
	case WM_LBUTTONUP://鼠标左键抬起操作
		g_oCards.OnLButtonup();
		break;

		
	case WM_MOUSEMOVE://鼠标移动
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		g_oCards.OnMouseMove(x,y);
		break;
	}
		/*
	case WM_KEYDOWN://键盘按下
		break;
	case WM_KEYUP://键盘抬起
		break;
		*/
	case WM_DESTROY:
		PostQuitMessage(0);//非常关键，没有这个应用程序还在后台运行
		break;
	}
	//点击关闭窗口“x”,依次产生三个消息
	//1.wmclose消息，删除信息，定义的变量hWnd等，
	//2.wmdestroy消息，窗口销毁
	//3.wmquit消息，应用程序退出消息，不主动产生，由PostQuitMessage(0)调用产生
	return DefWindowProc(hWnd, msgID, wParam, lParam);
	//上面没处理的消息，默认处理操作
}