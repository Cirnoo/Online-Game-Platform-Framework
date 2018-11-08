// Settingdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Register.h"
#include "Settingdlg.h"
#include "afxdialogex.h"
#include "Sys.h"

// CSettingdlg �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
	, m_port(_T(""))
{
	m_port.Format(L"%d",ntohs(theApp.sys.client_info.addrServer.sin_port));
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


// CSettingdlg ��Ϣ�������


void CSettingDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	auto & addrServer=theApp.sys.client_info.addrServer;
	UpdateData(TRUE);
	addrServer.sin_addr.S_un.S_addr;
	DWORD dwIP;
	m_ipctrl.GetAddress(dwIP);
	addrServer.sin_addr.S_un.S_addr=htonl(dwIP);
	addrServer.sin_port=htons(_ttoi(m_port));
	CDialogEx::OnOK();
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DWORD dwIP=theApp.sys.client_info.addrServer.sin_addr.S_un.S_addr;
	unsigned char *pIP = (unsigned char*)&dwIP;
	m_ipctrl.SetAddress(*pIP, *(pIP+1), *(pIP+2), *(pIP+3));
	return TRUE;
}
