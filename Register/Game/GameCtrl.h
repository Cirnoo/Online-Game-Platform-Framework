#pragma once
#include "PNGButton.h"
class CGameCtrl
{
public:
	static CGameCtrl & GetInstance();
	~CGameCtrl(void);
	void Show(Gdiplus::Graphics * g);
	void InitCtrl(CWnd * parent);
private:
	CGameCtrl(void);
	static CGameCtrl * self;
	vector<pImage> vec_min,vec_close;
	CPNGButton bt_min,bt_close;
	vector<CBaseControl *> vec_ctl_base;
};

