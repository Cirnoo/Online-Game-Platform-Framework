// EditEX.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "EditEX.h"
#include "Sys.h"

const int ID_EDIT_TEXT = 12000;
// CEditEX
CEdit * CEditEX::mEdit=nullptr;
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
		DrawEdit(g,vec_cut[HOVER]);
	}
	else
	{
		DrawEdit(g,vec_cut[NORMAL]);
	}
}



BOOL CEditEX::Create(Rect rect,CWnd * pParentWnd,UINT nID, std::vector<Image*> & vec_img)
{
	
	CPNGButton::Create(rect,pParentWnd,nID,vec_img);
	vec_cut.push_back(GetImageGroup(vec_img[NORMAL],1,3));
	vec_cut.push_back(GetImageGroup(vec_img[HOVER],1,3));
	return TRUE;
}

void CEditEX::ShowEditCursor()
{
	if (mEdit!=nullptr)
	{
		delete mEdit;
	}
	mEdit=new CEdit;
	mEdit->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, RectTransform(mRect),this,ID_EDIT_TEXT);
	mEdit->SetFont(sys.cfont);
	mEdit->SetWindowTextW(L"1233");
	mEdit->SetSel(0, -1);
	mEdit->SetFocus();
}

void CEditEX::HideEditCursor()
{

}


void CEditEX::DrawEdit(Graphics* & g,std::vector<Image*> img)
{
	int step=mRect.GetLeft();
	auto & l=img[0],& c=img[1],& r=img[2];
	auto rec=RectF(mRect.GetLeft(),mRect.GetTop(),l->GetWidth(),l->GetHeight());
	int img_width=l->GetWidth(),img_hight=l->GetHeight();
	g->DrawImage(l,rec);
	rec.X+=img_width;
	while (rec.X<mRect.GetRight()-img_width)
	{
		g->DrawImage(c,rec);
		rec.X+=img_width;
	}
	g->DrawImage(r,rec);
}

void CEditEX::ClickCmd()
{
	ShowEditCursor();
}

BEGIN_MESSAGE_MAP(CEditEX, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CEditEX 消息处理程序




void CEditEX::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CPNGButton::OnLButtonDown(nFlags, point);
}


void CEditEX::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CPNGButton::OnLButtonUp(nFlags, point);
}
