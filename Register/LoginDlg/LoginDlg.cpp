
// LoginDlg.cpp : ʵ���ļ�
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

// CLoginDlg �Ի���


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
	/********************��½�ɹ�***********************************/
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


// CLoginDlg ��Ϣ�������

BOOL CLoginDlg::OnInitDialog()
{
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);
	ModifyStyle(0,WS_CLIPCHILDREN);
	mWidth=380*RESOLUTION;
	mHeight=280*RESOLUTION;
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOPMOST, 0, 0,mWidth,mHeight , SWP_NOMOVE);
	CenterWindow();
	
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	mMediator.InitControl(this);
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	return TRUE;
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLoginDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialogEx::OnClose();
}


void CLoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn rgn;
	CRect rc;
	GetWindowRect(&rc); //��ô��ھ���
	rc -= rc.TopLeft();
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 20, 20); //���ݴ��ھ��δ���һ��Բ�Ǿ�������������γ�Բ�ǵĴ�С
	SetWindowRgn(rgn, TRUE);
	// TODO: �ڴ˴������Ϣ����������
}



void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CLoginDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return FALSE;
}









BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: TAB���л��༭���� ��Ӧ�س���
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
			else //�س���¼
			{
				mMediator.OnLogin();
				return TRUE;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
