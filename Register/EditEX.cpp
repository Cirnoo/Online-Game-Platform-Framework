// EditEX.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "EditEX.h"


// CEditEX

IMPLEMENT_DYNAMIC(CEditEX, CWnd)

CEditEX::CEditEX()
{

}

CEditEX::~CEditEX()
{
}


void CEditEX::Show(Graphics* & g)
{
	if(is_tracked)
	{
		g->DrawImage(vec_bg[HOVER],mRect); 
	}
	else
	{
		g->DrawImage(vec_bg[NORMAL],mRect); 
	}
}



BEGIN_MESSAGE_MAP(CEditEX, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CEditEX 消息处理程序


