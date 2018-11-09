
// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Sys.h"
#include "PictureFrame.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLoginDlg 对话框


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


afx_msg LRESULT CLoginDlg::OnLogin(WPARAM wParam, LPARAM lParam)
{
	/********************登陆成功***********************************/
	USER_INFO && info=mMediator.GetUserInfo();
	theApp.sys.client_info.player_name=info.name.GetStr();
	theApp.sys.client_info.password=info.password.GetStr();
	EndDialog(WM_LOGIN);
	return 0;
}
BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_LOGIN, &CLoginDlg::OnLogin)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);
	ModifyStyle(0,WS_CLIPCHILDREN);
	mWidth=380*RESOLUTION;
	mHeight=280*RESOLUTION;
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOPMOST, 0, 0,mWidth,mHeight , SWP_NOMOVE);
	CenterWindow();
	
	// IDM_ABOUTBOX 必须在系统命令范围内。
	mMediator.InitControl(this);
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	return TRUE;
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		HDC hdc = ::GetDC(this->m_hWnd);
		Graphics graphics(hdc);
		Bitmap bmp(this->mWidth,this->mHeight);
		Graphics* gBuf=Graphics::FromImage(&bmp);
		
		gBuf->DrawImage(theApp.sys.back,0,0);
		gBuf->DrawImage(theApp.sys.mask,0,0);
		mMediator.ShowControl(gBuf);
		graphics.DrawImage(&bmp,0,0);
		::ReleaseDC(m_hWnd,hdc);
		delete gBuf;
		CDialogEx::OnPaint();
	}
	
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnClose();
}


void CLoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn rgn;
	CRect rc;
	GetWindowRect(&rc); //获得窗口矩形
	rc -= rc.TopLeft();
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 20, 20); //根据窗口矩形创建一个圆角矩形最后两个是形成圆角的大小
	SetWindowRgn(rgn, TRUE);
	// TODO: 在此处添加消息处理程序代码
}



void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CLoginDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return FALSE;
}









BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: TAB键切换编辑框光标 响应回车键
	if((pMsg->message == WM_KEYDOWN) && (VK_TAB == pMsg->wParam ||pMsg->wParam ==VK_RETURN))
	{
		CWnd *mwnd =  GetFocus();
		if( NULL != mwnd )
		{
			auto edit_name=GetDlgItem(IDC_EDIT_USER);
			auto edit_key=GetDlgItem(IDC_EDIT_KEY);
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
				mMediator.OnLogin();
				return TRUE;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
