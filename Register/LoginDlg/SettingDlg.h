#pragma once
#include "afxcmn.h"
#include "resource.h"

// CSettingdlg �Ի���

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingDlg();

// �Ի�������
	enum { IDD = IDD_SETTINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_port;
	afx_msg void OnBnClickedOk();
	CIPAddressCtrl m_ipctrl;
	virtual BOOL OnInitDialog();
};
