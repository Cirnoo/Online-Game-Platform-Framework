#include "stdafx.h"
#include "Mediator.h"
#include "PNGButton.h"
#include "PictureFrame.h"
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
	int mWidth=window_rect.Width();
	int  c_width=min_ctrl->GetWidth();
	int  c_height=min_ctrl->GetHeight();

/************************************************************************/
/*							 ¿Ø¼þ³õÊ¼»¯                                  */
/************************************************************************/

	typedef CBaseControl  * pCBaseControl	  ;
	typedef CPNGButton    *  pCPNGButton	      ;
	typedef CPictureFrame * pCPictureFrame	  ;

	CBaseControl * pControlBase=nullptr;

	//min_control
	auto  rec=Rect(mWidth-38-28,0,c_width,c_height);
	pControlBase = new CPNGButton;
	((pCPNGButton)pControlBase)->Create(rec,pParentWnd,IDC_MIN,sys.vec_bt_min[0],sys.vec_bt_min[1],sys.vec_bt_min[2],CMD_MINSIZE);
	vec_control.push_back(pControlBase);

	rec=Rect(mWidth-38,0,c_width+10,c_height);
	pControlBase = new CPNGButton;
	((pCPNGButton)pControlBase)->Create(rec,pParentWnd,IDC_CLOSE,sys.vec_bt_close[0],sys.vec_bt_close[1],sys.vec_bt_close[2],CMD_CLOSE);
	vec_control.push_back(pControlBase);

	rec=Rect(16,139,87,87);
	pControlBase = new CPictureFrame;
	((pCPictureFrame)pControlBase)->Create(rec,pParentWnd,IDC_PIC,sys.cirno);
	vec_control.push_back(pControlBase);

	rec=Rect(16-2,139,87+2,87+2);
	pControlBase = new CPictureFrame;
	((pCPictureFrame)pControlBase)->Create(rec,pParentWnd,ID_HEAD_BK,sys.head_bk);
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

