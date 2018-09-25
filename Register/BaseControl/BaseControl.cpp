// BaseControl.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "BaseControl.h"


// CBaseControl

IMPLEMENT_DYNAMIC(CBaseControl, CWnd)

CBaseControl::CBaseControl()
{

}

CBaseControl::~CBaseControl()
{
}


void CBaseControl::SwichControl(bool flag)
{
	return ;
}

void CBaseControl::PaintParent()
{
	CRect   rect;
	GetWindowRect(&rect); 
	GetParent()-> ScreenToClient(&rect); 
	GetParent()-> InvalidateRect(&rect);
}

BEGIN_MESSAGE_MAP(CBaseControl, CWnd)
END_MESSAGE_MAP()



// CBaseControl 消息处理程序


