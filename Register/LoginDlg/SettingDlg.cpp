// Settingdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "Settingdlg.h"
#include "afxdialogex.h"
#include "Sys.h"

// CSettingdlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
	, m_port(_T(""))
{
	m_port.Format(L"%d",ntohs(sys.addrServer.sin_port));
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SETTING_PORT, m_port);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipctrl);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSettingdlg 消息处理程序


void CSettingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	sys.addrServer.sin_addr.S_un.S_addr;
	DWORD dwIP;
	m_ipctrl.GetAddress(dwIP);
	sys.addrServer.sin_addr.S_un.S_addr=htonl(dwIP);
	CDialogEx::OnOK();
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DWORD dwIP=sys.addrServer.sin_addr.S_un.S_addr;
	unsigned char *pIP = (unsigned char*)&dwIP;
	m_ipctrl.SetAddress(*pIP, *(pIP+1), *(pIP+2), *(pIP+3));
	return TRUE;
}
