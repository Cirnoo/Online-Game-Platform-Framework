#include "stdafx.h"
#include "Sys.h"
#include "Mediator.h"
#include "PictureFrame.h"
#include "TextButton.h"
#include "EditEX.h"
#include "PNGButton.h"
#include "CheckBox.h"
#include "LinkButton.h"
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
/*							 控件初始化                                  */
/************************************************************************/

	CBaseControl * pControlBase=nullptr;
	#define  GetControl(x)   pControlBase = new x; 
	#define  AddTheControl   vec_control.push_back(pControlBase);
	#define  pPNGButton	    (  (CPNGButton*)      pControlBase  )  
	#define  pPictureFrame  (  (CPictureFrame*)   pControlBase 	)  
	#define  pTextButton    (  (CTextButton*)     pControlBase  ) 
	#define  pCheckBox		(  (CCheckBox*)       pControlBase  )
	#define  pLinkButton		(  (CLinkButton*)     pControlBase  )
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
	pTextButton->SetText(L"登录",sys.font);
	AddTheControl

	rec=Rect(16,mHeight-27,c_width,c_height);
	GetControl(CTextButton)
	pTextButton->Create(rec,pParentWnd,IDC_NET,sys.vec_bt_default);
	pTextButton->SetText(L"设置",sys.font);
	AddTheControl	

	rec=Rect(112,213,sys.vec_checkbox[0]->GetWidth(),sys.vec_checkbox[0]->GetHeight());
	GetControl(CCheckBox)
	pCheckBox->Create(rec,pParentWnd,IDC_CHECK_1,sys.vec_checkbox);
	pCheckBox->SetText(L"记住我",sys.font);
	AddTheControl
	
	CStringW str=L"注册账号";
	rec=Rect(310,145,str.GetLength()*16,30);
	GetControl(CLinkButton)
	pLinkButton->Create(rec,pParentWnd,IDC_LINK_1);
	pLinkButton->SetText(str,sys.font);
	AddTheControl

/************************************************************************/
/*                          Edit                                        */
/************************************************************************/

	CEditEX * my_edit;
	rec=Rect(112,142,191,28);
	my_edit=new CEditEX;
	my_edit->CreateEditEx(rec,pParentWnd,IDC_EDIT_USER,sys.vec_edit);
	vec_edit.push_back(my_edit);

	rec=Rect(112,142+34,191,28);
	my_edit=new CEditEX;
	my_edit->CreateEditEx(rec,pParentWnd,IDC_EDIT_KEY,sys.vec_edit);
	vec_edit.push_back(my_edit);

}

void Mediator::ShowControl(Graphics* & p)
{
	for (auto i:vec_control)
	{
		i->Show(p);
	}
	for (auto i:vec_edit)
	{
		i->Show(p);
	}
}


bool Mediator::GetTask()
{
	return task_flag;
}

