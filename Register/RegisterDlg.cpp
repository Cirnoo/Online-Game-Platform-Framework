
// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "Sys.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRegisterDlg 对话框


CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegisterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	is_in_drag=false;
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_SIZE()
//	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOVE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序

BOOL CRegisterDlg::OnInitDialog()
{
	ModifyStyleEx(WS_EX_CLIENTEDGE, NULL, SWP_DRAWFRAME);
	mWidth=380*RESOLUTION;
	mHeight=280*RESOLUTION;
	::SetWindowPos(AfxGetMainWnd()->m_hWnd, HWND_TOPMOST, 0, 0,mWidth,mHeight , SWP_SHOWWINDOW | SWP_NOMOVE);
	CenterWindow();

	// IDM_ABOUTBOX 必须在系统命令范围内。

	InitControl();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	buttonUncom = new CMFCButton;
	buttonUncom->Create(_T("Uncomplete"),
		  WS_VISIBLE,
		  CRect(5, 5, 300, 300),
		  this,
		  2000);
	return TRUE;
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRegisterDlg::OnPaint()
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
		//CDialogEx::OnPaint();

		HDC hdc = ::GetDC(this->m_hWnd);
		Graphics graphics(hdc);
		Bitmap bmp(this->mWidth,this->mHeight);
		Graphics* gBuf=Graphics::FromImage(&bmp);
		
		gBuf->DrawImage(sys.back,0,0);
		gBuf->DrawImage(sys.mask,0,0);
		bt_min.Show(bmp,gBuf);
		bt_close.Show(bmp,gBuf);
		graphics.DrawImage(&bmp,0,0);
		::ReleaseDC(m_hWnd,hdc);
	}
	
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRegisterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRegisterDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnClose();
}


void CRegisterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn rgn;
	CRect rc;
	GetWindowRect(&rc); //获得窗口矩形
	rc -= rc.TopLeft();
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 15, 15); //根据窗口矩形创建一个圆角矩形最后两个是形成圆角的大小
	SetWindowRgn(rgn, TRUE);
	// TODO: 在此处添加消息处理程序代码
}



void CRegisterDlg::InitControl()
{
	//min_control
	auto & min_ctrl=sys.vec_bt_min[0];
	CRect window_rect;
	
	int  c_width=min_ctrl->GetWidth();
	int  c_height=min_ctrl->GetHeight();


	//min_control
	auto  rec=Rect(mWidth-38-28,0,c_width,c_height);
	bt_min.Create(rec,this,IDC_MIN,sys.vec_bt_min[0],sys.vec_bt_min[1],CMD_MINSIZE);

	rec=Rect(mWidth-38,0,c_width+10,c_height);
	bt_close.Create(rec,this,IDC_CLOSE,sys.vec_bt_close[0],sys.vec_bt_close[1],CMD_CLOSE);

	auto temp=new CButton();
	temp->Create(_T("Start"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,	CRect(mWidth-76,mHeight-29,69,22), this, 10100);
	temp->ShowWindow(true);
}





void CRegisterDlg::SwichControl(bool flag)
{
	bt_close.task_flag=flag;
	bt_min.task_flag=flag;
}



void CRegisterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x, point.y));
		SwichControl(false);
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CRegisterDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return FALSE;
}


void CRegisterDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	is_in_drag=false;
	SwichControl(true);
	CDialogEx::OnLButtonUp(nFlags, point);
}




void CRegisterDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	SwichControl(true);
	// TODO: 在此处添加消息处理程序代码
}


void CRegisterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnSysCommand(nID, lParam);
}
