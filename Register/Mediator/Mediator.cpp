#include "stdafx.h"
#include "Sys.h"
#include "Mediator.h"
#include "PictureFrame.h"
#include "TextButton.h"
#include "EditEX.h"
#include "PNGButton.h"
#include "CheckBox.h"
#include "LinkButton.h"
#include "Packdef.h"
Mediator::Mediator()
{
	task_flag=true;

}

Mediator::~Mediator()
{
	for (auto i:vec_control)
	{
		delete i;
	}
	for (auto i:vec_edit)
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
/*							 �ؼ���ʼ��                                  */
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
	rec=Rect(mWidth-(38+28)*RESOLUTION,0,c_width,c_height);
	pPNGButton->Create(rec,pParentWnd,IDC_MIN,sys.vec_bt_min);
	pPNGButton->SetCmd
	([=]()
	{
		pParentWnd->SendMessage(WM_SYSCOMMAND ,SC_MINIMIZE, 0);
	});
	AddTheControl
	
	rec=Rect(mWidth-38*RESOLUTION,0,c_width+10,c_height);
	GetControl(CPNGButton)
	pPNGButton->Create(rec,pParentWnd,IDC_CLOSE,sys.vec_bt_close);
	pPNGButton->SetCmd
		([=]()
	{
		pParentWnd->SendMessage(WM_CLOSE ,0, 0);
	});
	AddTheControl

	rec=Rect(16*RESOLUTION,139*RESOLUTION,87,87);
	GetControl(CPictureFrame)
	pPictureFrame->Create(rec,pParentWnd,IDC_PIC,sys.cirno);
	AddTheControl

	rec=Rect((16-2)*RESOLUTION,139*RESOLUTION,87+2,87+2);
	GetControl(CPictureFrame)
	pPictureFrame->Create(rec,pParentWnd,ID_HEAD_BK,sys.head_bk);
	AddTheControl


	c_width=sys.vec_bt_default[0]->GetWidth();
	c_height=sys.vec_bt_default[0]->GetHeight();
	rec=Rect(mWidth-79*RESOLUTION,mHeight-27*RESOLUTION,c_width,c_height);
	GetControl(CTextButton)
	pTextButton->Create(rec,pParentWnd,IDC_REGISTER,sys.vec_bt_default);
	pTextButton->SetText(L"��¼",sys.font);
	pTextButton->SetCmd([=]
	{
		OnLogin();
	});
	AddTheControl

	rec=Rect(16*RESOLUTION,mHeight-27*RESOLUTION,c_width,c_height);
	GetControl(CTextButton)
	pTextButton->Create(rec,pParentWnd,IDC_NET,sys.vec_bt_default);
	pTextButton->SetText(L"����",sys.font);
	AddTheControl	

	rec=Rect(112*RESOLUTION,213*RESOLUTION,sys.vec_checkbox[0]->GetWidth(),sys.vec_checkbox[0]->GetHeight());
	GetControl(CCheckBox)
	pCheckBox->Create(rec,pParentWnd,IDC_CHECK_1,sys.vec_checkbox);
	pCheckBox->SetText(L"��ס��",sys.font);
	AddTheControl
	
	CStringW str=L"ע���˺�";
	rec=Rect(mWidth-81*RESOLUTION,147*RESOLUTION,str.GetLength()*16*RESOLUTION,20);
	GetControl(CLinkButton)
	pLinkButton->Create(rec,pParentWnd,IDC_LINK_1);
	pLinkButton->SetText(str,sys.font);
	AddTheControl

	str=L"�һ�����";
	rec=Rect(mWidth-81*RESOLUTION,(147+37)*RESOLUTION,str.GetLength()*16*RESOLUTION,20);
	GetControl(CLinkButton)
	pLinkButton->Create(rec,pParentWnd,IDC_LINK_2);
	pLinkButton->SetText(str,sys.font);
	AddTheControl

	str=L"�ο͵�½";
	rec=Rect((112+117)*RESOLUTION,214*RESOLUTION,str.GetLength()*16*RESOLUTION,20);
	GetControl(CLinkButton)
	pLinkButton->Create(rec,pParentWnd,IDC_LINK_3);
	pLinkButton->SetText(str,sys.font);
	AddTheControl

/************************************************************************/
/*                          Edit                                        */
/************************************************************************/

	CEditEX * my_edit;
	rec=Rect(112*RESOLUTION,142*RESOLUTION,191,28);
	my_edit=new CEditEX;
	my_edit->CreateEditEx(rec,pParentWnd,IDC_EDIT_USER,sys.vec_edit);
	my_edit->SetDefaultText(L"�û���");
	vec_edit.push_back(my_edit);

	rec=Rect(112*RESOLUTION,(142+34)*RESOLUTION,191,28);
	my_edit=new CEditEX;
	my_edit->CreateEditEx(rec,pParentWnd,IDC_EDIT_KEY,sys.vec_edit,true);
	my_edit->SetDefaultText(L"����");
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


USER_INFO Mediator::GetUserInfo()
{
	USER_INFO info;
	auto name_ctl=GetEditCtl(IDC_EDIT_USER);
	auto pw_ctl=GetEditCtl(IDC_EDIT_KEY);
	if (name_ctl->IsEmpty()||pw_ctl->IsEmpty())
	{
		throw "empty";
		return info;
	}
	info.name=name_ctl->GetEditText();
	info.password=pw_ctl->GetEditText();
	return info;
}

CEditEX * Mediator::GetEditCtl(int nID)
{
	for (auto i:vec_edit)
	{
		if (i->GetDlgCtrlID()==nID)
		{
			return i;
		}
	}
	return nullptr;
}

void Mediator::OnLogin()
{
	try
	{
		USER_INFO info=GetUserInfo();
		DATA_BUF a(info);
		if(sys.tools.ConnectServer())
		{
			sys.tools.DealData(MS_TYPE::LOGIN_RQ,(DATA_BUF)info);
		}	
	}
	catch(...) 
	{
		Warning("�������û���������");
		sys.tools.Disconnect();
		return;
	}
}

