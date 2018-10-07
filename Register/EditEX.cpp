// EditEX.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "EditEX.h"
#include "Sys.h"

const int ID_EDIT_TEXT = 12000;
// CEditEX

IMPLEMENT_DYNAMIC(CEditEX, CWnd)

CEditEX::CEditEX()
{
	is_password=false;
}

CEditEX::~CEditEX()
{
}


void CEditEX::Show(Graphics* & g)
{
	if(is_tracked)
	{
		g->DrawImage(vec_bg[HOVER],mRect.GetLeft(),mRect.GetTop()); 
	}
	else
	{
		g->DrawImage(vec_bg[NORMAL],mRect.GetLeft(),mRect.GetTop()); 
	}
}



BOOL CEditEX::Create(Rect rect,CWnd * pParentWnd,UINT nID, std::vector<Image*> & vec_img)
{
	CPNGButton::Create(rect,pParentWnd,nID,vec_img);

	return TRUE;
}

void CEditEX::ShowEdit()
{
	auto id_temp=GetDlgItem(ID_EDIT_TEXT);
	if (id_temp!=NULL)
	{
		id_temp->DestroyWindow();
	}
	mEdit->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, RectTransform(mRect),this,ID_EDIT_TEXT);
	mEdit->SetFont(sys.cfont);
	mEdit->SetWindowTextW(mText.GetStr());
}

void CEditEX::HideEdit()
{

}

BEGIN_MESSAGE_MAP(CEditEX, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CEditEX 消息处理程序


