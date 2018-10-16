
// RegisterDlg.h : 头文件
//

#pragma once
#include "Mediator.h"

// CRegisterDlg 对话框
class CRegisterDlg : public CDialogEx
{
// 构造
public:
	CRegisterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	int mWidth;
	int mHeight;
private:
	std::vector<CButton *> vt_vec; 
	CWinThread * thread;
	Mediator mMediator;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMysocket(WPARAM wParam, LPARAM lParam);
};
