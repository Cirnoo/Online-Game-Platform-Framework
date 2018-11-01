// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Register.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "Sys.h"

// CRegisterDlg �Ի���

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterDlg::IDD, pParent)
{
	
}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


void CRegisterDlg::OnRegister()
{
	
	auto name=mName.GetEditText();
	auto key=mKey.GetEditText();
	if (!IsLegal(key))
	{
		Warning("���Ϸ�������");
		return ;
	}
	if (!theApp.tools.ConnectServer())
	{
		return ;
	}
	DATA_PACKAGE pack(MS_TYPE::REGISTER_RQ,USER_INFO(name,key));
	theApp.tools.DealData(pack);
}



BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDS_BUTTON_REGISTER, &CRegisterDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CRegisterDlg ��Ϣ�������


void CRegisterDlg::OnPaint()
{
	CRect rectDlg;
	GetClientRect(rectDlg);//��ô���Ĵ�С
	HDC hdc = ::GetDC(this->m_hWnd);
	Graphics graphics(hdc);
	Bitmap bmp(rectDlg.Width(),rectDlg.Height());
	Graphics* gBuf=Graphics::FromImage(&bmp);
	SolidBrush blackBrush(Color(255, 240, 240, 240));
	gBuf->FillRectangle(&blackBrush,rectDlg.left,rectDlg.top,rectDlg.Width(),rectDlg.Height());
	mName.Show(gBuf);
	mKey.Show(gBuf);
	graphics.DrawImage(&bmp,0,0);
	::ReleaseDC(m_hWnd,hdc);
	delete gBuf;
	CDialogEx::OnPaint();
}


BOOL CRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rectDlg;
	GetClientRect(rectDlg);
	ModifyStyle(0,WS_CLIPCHILDREN);
	CenterWindow();

	CRect rect_user,rect_key;
	GetDlgItem(IDS_USER)->GetWindowRect(&rect_user);//��ȡ�ؼ�����Ļ����
	ScreenToClient(&rect_user);//ת��Ϊ�Ի����ϵĿͻ�����
	GetDlgItem(IDS_KEY)->GetWindowRect(&rect_key);
	ScreenToClient(&rect_key);

	int x=rectDlg.CenterPoint().x-80;
	Rect rec=Rect(x,rect_user.top-7,191,28);
	mName.CreateEditEx(rec,this,IDC_EDIT_LOGIN_USER,theApp.sys.vec_edit);
	mName.SetDefaultText(L"��Ӣ�Ļ�����");
	rec=Rect(x,rect_key.top-7,191,28);
	mKey.CreateEditEx(rec,this,IDC_EDIT_LOGIN_KEY,theApp.sys.vec_edit);
	mKey.SetDefaultText(L"4λ���ϵ���ĸ������");
	return TRUE;
}


BOOL CRegisterDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return FALSE;
}


BOOL CRegisterDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	// TODO: TAB���л��༭���� ��Ӧ�س���
	if((pMsg->message == WM_KEYDOWN) && (VK_TAB == pMsg->wParam ||pMsg->wParam ==VK_RETURN))
	{
		CWnd *mwnd =  GetFocus();
		if( NULL != mwnd )
		{
			auto edit_name=GetDlgItem(IDC_EDIT_LOGIN_USER);
			auto edit_key=GetDlgItem(IDC_EDIT_LOGIN_KEY);
			if(mwnd == edit_name)
			{
				edit_key->SetFocus();
				return TRUE;
			}
			else if(VK_TAB == pMsg->wParam)
			{
				edit_name->SetFocus();
				return TRUE;
			}
			else //�س���¼
			{
				OnRegister();
				return TRUE;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

bool CRegisterDlg::IsLegal(const wstring & str)
{
	if (str.length()<4)
	{
		return false;
	}
	for (auto i:str)
	{
		if (i>CHAR_MAX||(!isalpha(i)&&!isdigit(i)))
		{
			return false;
		}
	}
	return true;
}





void CRegisterDlg::OnBnClickedButtonRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnRegister();
}
