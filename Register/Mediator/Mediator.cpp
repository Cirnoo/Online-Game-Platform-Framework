#include "stdafx.h"
#include "Sys.h"
#include "Mediator.h"
#include "PictureFrame.h"
#include "TextButton.h"
#include "EditEX.h"
#include "PNGButton.h"
Mediator::Mediator()
{
	task_flag=true;
	auto t=Rect(0,0,0,0);
}

Mediator::~Mediator()
{
	for (auto i:vec_control)
	{
		delete i;
	}
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

	CBaseControl * pControlBase=nullptr;
	#define  GetControl(x)   pControlBase = new x; 
	#define  AddTheControl   vec_control.push_back(pControlBase);
	#define  pPNGButton	    (  (CPNGButton*)      pControlBase  )  
	#define  pPictureFrame  (  (CPictureFrame*)   pControlBase 	)  
	#define  pTextButton    (  (CTextButton*)     pControlBase  )  
	#define  pEditEx			(  (CEditEX*)     pControlBase  )
	//min_control
	c_width=sys.vec_bt_min[0]->GetWidth();
	c_height=sys.vec_bt_min[0]->GetHeight();
	Rect  rec;
/**************************************************************************/
	GetControl(CPNGButton)
	rec=Rect(mWidth-38-28,0,c_width,c_height);
	pPNGButton->Create(rec,pParentWnd,IDC_MIN,sys.vec_bt_min);
	pPNGButton->SetCmd
	([=]()
	{
		pParentWnd->SendMessage(WM_SYSCOMMAND ,SC_MINIMIZE, 0);
	});
	AddTheControl
	
	rec=Rect(mWidth-38,0,c_width+10,c_height);
	GetControl(CPNGButton)
	pPNGButton->Create(rec,pParentWnd,IDC_CLOSE,sys.vec_bt_close);
	pPNGButton->SetCmd
		([=]()
	{
		pParentWnd->SendMessage(WM_CLOSE ,0, 0);
	});
	AddTheControl

	rec=Rect(16,139,87,87);
	GetControl(CPictureFrame)
	pPictureFrame->Create(rec,pParentWnd,IDC_PIC,sys.cirno);
	AddTheControl

	rec=Rect(16-2,139,87+2,87+2);
	GetControl(CPictureFrame)
	pPictureFrame->Create(rec,pParentWnd,ID_HEAD_BK,sys.head_bk);
	AddTheControl


	c_width=sys.vec_bt_default[0]->GetWidth();
	c_height=sys.vec_bt_default[0]->GetHeight();
	rec=Rect(mWidth-76,mHeight-27,c_width,c_height);
	GetControl(CTextButton)
	pTextButton->Create(rec,pParentWnd,IDC_REGISTER,sys.vec_bt_default);
	pTextButton->SetText(L"µÇÂ¼",sys.font);
	AddTheControl
	
	rec=Rect(112,142,191,28);
	GetControl(CEditEX)
	pEditEx->Create(rec,pParentWnd,IDC_EDIT_USER,sys.vec_edit);
	AddTheControl

	rec=Rect(112,142+34,191,28);
	GetControl(CEditEX)
	pEditEx->Create(rec,pParentWnd,IDC_EDIT_KEY,sys.vec_edit);
	AddTheControl
}

void Mediator::ShowControl(Graphics* & p)
{
	for (auto i:vec_control)
	{
		i->Show(p);
	}
}


bool Mediator::GetTask()
{
	return task_flag;
}

