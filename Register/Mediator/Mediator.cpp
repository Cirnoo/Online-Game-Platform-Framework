#include "stdafx.h"
#include "Mediator.h"
#include "PNGButton.h"
#include "PictureFrame.h"
#include "TextButton.h"
Mediator::Mediator()
{
}

Mediator::~Mediator()
{
}

void Mediator::InitControl(CWnd * pParentWnd)
{
	auto & min_ctrl=sys.vec_bt_min[0];
	CRect window_rect;
	AfxGetMainWnd()->GetWindowRect(&window_rect);
	const int mWidth=window_rect.Width();
	const int mHeight=window_rect.Height();
	int  c_width;
	int  c_height;

/************************************************************************/
/*							 ¿Ø¼þ³õÊ¼»¯                                  */
/************************************************************************/

	typedef CBaseControl  * pCBaseControl	  ;
	typedef CPNGButton    *  pCPNGButton	      ;
	typedef CPictureFrame * pCPictureFrame	  ;
	typedef CTextButton   *  pTextButton   	  ;
	CBaseControl * pControlBase=nullptr;

	//min_control
	c_width=sys.vec_bt_min[0]->GetWidth();
	c_height=sys.vec_bt_min[0]->GetHeight();
	auto  rec=Rect(mWidth-38-28,0,c_width,c_height);
	pControlBase = new CPNGButton;
	((pCPNGButton)pControlBase)->Create(rec,pParentWnd,IDC_MIN,sys.vec_bt_min);
	((pCPNGButton)pControlBase)->SetCmd
	([=]()
	{
		pParentWnd->SendMessage(WM_SYSCOMMAND ,SC_MINIMIZE, 0);
	});
	vec_control.push_back(pControlBase);
	
	rec=Rect(mWidth-38,0,c_width+10,c_height);
	pControlBase = new CPNGButton;
	((pCPNGButton)pControlBase)->Create(rec,pParentWnd,IDC_CLOSE,sys.vec_bt_close);
	((pCPNGButton)pControlBase)->SetCmd
		([=]()
	{
		pParentWnd->SendMessage(WM_CLOSE ,0, 0);
	});
	vec_control.push_back(pControlBase);

	rec=Rect(16,139,87,87);
	pControlBase = new CPictureFrame;
	((pCPictureFrame)pControlBase)->Create(rec,pParentWnd,IDC_PIC,sys.cirno);
	vec_control.push_back(pControlBase);

	rec=Rect(16-2,139,87+2,87+2);
	pControlBase = new CPictureFrame;
	((pCPictureFrame)pControlBase)->Create(rec,pParentWnd,ID_HEAD_BK,sys.head_bk);
	vec_control.push_back(pControlBase);


	c_width=sys.vec_bt_default[0]->GetWidth();
	c_height=sys.vec_bt_default[0]->GetHeight();
	rec=Rect(mWidth-76,mHeight-27,c_width,c_height);
	pControlBase = new CTextButton;
	((pTextButton)pControlBase)->Create(rec,L"µÇÂ¼",sys.font);
	((pTextButton)pControlBase)->SetButton(IDC_REGISTER,pParentWnd,sys.vec_bt_default);
	vec_control.push_back(pControlBase);
}

void Mediator::ShowControl(Graphics* & p)
{
	for (auto i:vec_control)
	{
		i->Show(p);
	}
}

void Mediator::SwichControl(bool flag)
{
	for (auto i:vec_control)
	{
		i->SwichControl(flag);
	}
}

