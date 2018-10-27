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
	is_empty=true;
	m_brush.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
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




BOOL CEditEX::CreateEditEx(Rect rc,CWnd * pParentWnd,UINT nID, std::vector<Image*> & vec_img,bool password/*=false*/)
{
	vec_cut.push_back(GetImageGroup(vec_img[NORMAL],1,3));
	vec_cut.push_back(GetImageGroup(vec_img[HOVER],1,3));
	mRect=rc;
	this->Create(WS_CHILD|WS_VISIBLE, 
		CRect(rc.GetLeft()+7,rc.GetTop()+6,rc.GetRight()-3,rc.GetBottom()-4),pParentWnd,nID);
	this->SetFont(theApp.sys.cfont);
	is_password=password;
	return TRUE;
}

void CEditEX::SetDefaultText(CStringW str)
{
	default_str=str;
	this->SetWindowTextW(str);
}



wstring CEditEX::GetEditText()
{
	CString str;
	GetWindowText(str);
	return (wstring)str;
}

bool CEditEX::IsEmpty()
{
	return is_empty;
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
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()



// CEditEX 消息处理程序


void CEditEX::ControlRepaint()
{
	//CRect   rect=RectTransform(mRect);
	//GetWindowRect(&rect);
	CRect   rect=RectTransform(mRect);
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
		tme.dwFlags		=   TME_LEAVE; //
		tme.hwndTrack   =   GetSafeHwnd(); 
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




HBRUSH CEditEX::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// TODO:  在此更改 DC 的任何特性
	pDC-> SetTextColor(is_empty?RGB(128,128,128):RGB(0,0,0));
	return   HBRUSH(m_brush);    
}


void CEditEX::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	if (is_empty)
	{
		return;
	}
	if (GetWindowTextLengthW()==0)
	{
		is_empty=true;
		SetPasswordChar(NULL);
		SetWindowTextW(default_str);
	}
	else
	{
		if (is_password)
		{
			SetPasswordChar('*');
		}
	}
	// TODO: 在此处添加消息处理程序代码
}


void CEditEX::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	if (is_empty)
	{
		SetSel(0,-1);
		Clear();
	}
	is_empty=false;
	if (is_password)
	{
		SetPasswordChar('*');
	}
	// TODO: 在此处添加消息处理程序代码
}
