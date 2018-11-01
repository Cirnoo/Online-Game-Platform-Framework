// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "Sys.h"

// CRegisterDlg 对话框

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
		Warning("不合法的输入");
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


// CRegisterDlg 消息处理程序


void CRegisterDlg::OnPaint()
{
	CRect rectDlg;
	GetClientRect(rectDlg);//获得窗体的大小
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
	GetDlgItem(IDS_USER)->GetWindowRect(&rect_user);//获取控件的屏幕坐标
	ScreenToClient(&rect_user);//转换为对话框上的客户坐标
	GetDlgItem(IDS_KEY)->GetWindowRect(&rect_key);
	ScreenToClient(&rect_key);

	int x=rectDlg.CenterPoint().x-80;
	Rect rec=Rect(x,rect_user.top-7,191,28);
	mName.CreateEditEx(rec,this,IDC_EDIT_LOGIN_USER,theApp.sys.vec_edit);
	mName.SetDefaultText(L"中英文或数字");
	rec=Rect(x,rect_key.top-7,191,28);
	mKey.CreateEditEx(rec,this,IDC_EDIT_LOGIN_KEY,theApp.sys.vec_edit);
	mKey.SetDefaultText(L"4位以上的字母或数字");
	return TRUE;
}


BOOL CRegisterDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return FALSE;
}


BOOL CRegisterDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// TODO: TAB键切换编辑框光标 响应回车键
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
			else //回车登录
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
	// TODO: 在此添加控件通知处理程序代码
	OnRegister();
}
