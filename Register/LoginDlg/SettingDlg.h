#pragma once
#include "afxcmn.h"
#include "resource.h"

// CSettingdlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
	enum { IDD = IDD_SETTINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_port;
	afx_msg void OnBnClickedOk();
	CIPAddressCtrl m_ipctrl;
	virtual BOOL OnInitDialog();
};
