#include "stdafx.h"
#include "GameCtrl.h"


CGameCtrl * CGameCtrl::self=nullptr;
CGameCtrl & CGameCtrl::GetInstance()  //饿汉式
{
	if (self==nullptr)
	{
		self = new CGameCtrl;
	}
	return *self;
}

CGameCtrl::CGameCtrl(void)
{
	auto vec_temp=::GetImageGroup(IDB_GAME_BUTTON,2,3);
	for (auto & i:vec_temp)
	{
		i=ResizeImg(i,0.4);
	}
	for (int i=0;i<3;i++)
	{
		vec_min.push_back(vec_temp[i]);
	}
	for (int i=3;i<6;i++)
	{
		vec_close.push_back(vec_temp[i]);
	}
}


CGameCtrl::~CGameCtrl(void)
{
	self=nullptr;
}

void CGameCtrl::Show(Gdiplus::Graphics * g)
{
	for (const auto i:vec_ctl_base)
	{
		i->Show(g);
	}
}

void CGameCtrl::InitCtrl(CWnd * parent)
{
	const int IDG_MIN   = 10000;
	const int IDG_CLOSE = 10001;
	const int bt_width  = vec_min[0]->GetWidth();
	const int bt_height = vec_min[0]->GetHeight();

	CRect rectDlg;
	parent->GetClientRect(rectDlg);//获得窗体的大小
	Rect rect=Rect(rectDlg.Width()-bt_width*1.6,5,bt_width,bt_height);

	bt_close.Create(rect,parent,IDG_CLOSE,vec_close);
	bt_close.SetCmd([parent]()
	{
		parent->PostMessageW(WM_CLOSE);
	});
	vec_ctl_base.push_back(&bt_close);

	rect.X-=bt_width*1.5;
	bt_min.Create(rect,parent,IDG_MIN,vec_min);
	bt_min.SetCmd([parent]()
	{
		parent->PostMessageW(WM_SYSCOMMAND ,SC_MINIMIZE, 0);
	});
	vec_ctl_base.push_back(&bt_min);
}
