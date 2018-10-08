// EditEX.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "EditEX.h"
#include "Sys.h"

// CEditEX
IMPLEMENT_DYNAMIC(CEditEX, CWnd)

CEditEX::CEditEX()
{
	is_password=false;
	is_tracked	=	false; 
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



BOOL CEditEX::CreateEditEx(Rect rc,CWnd * pParentWnd,UINT nID, std::vector<Image*> & vec_img)
{
	
	vec_cut.push_back(GetImageGroup(vec_img[NORMAL],1,3));
	vec_cut.push_back(GetImageGroup(vec_img[HOVER],1,3));
	mRect=rc;
	this->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP, 
		CRect(112+5,142+34+5,112+191,142+34+24),pParentWnd,100+nID);
	this->SetFont(sys.cfont);
	this->SetSel(0, -1);
	this->SetFocus();
	return TRUE;
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



BEGIN_MESSAGE_MAP(CEditEX, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CEditEX 消息处理程序


void CEditEX::ControlRepaint()
{
	CRect   rect;
	GetWindowRect(&rect); 
	GetParent()-> ScreenToClient(&rect); 
	GetParent()-> InvalidateRect(&rect);
}

void CEditEX::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!is_tracked) 
	{ 
		TRACKMOUSEEVENT   tme; 
		tme.cbSize		=   sizeof(TRACKMOUSEEVENT); 
		tme.dwFlags		=   TME_LEAVE|TME_HOVER; //
		tme.hwndTrack   =   GetSafeHwnd(); 
		tme.dwHoverTime	=   80; 
		_TrackMouseEvent(&tme);  
		is_tracked   =   true;
		ControlRepaint();
	}
	CEdit::OnMouseMove(nFlags, point);
}

void CEditEX::OnMouseLeave()
{
	is_tracked=false;
	ControlRepaint();
	CEdit::OnMouseLeave();
}

