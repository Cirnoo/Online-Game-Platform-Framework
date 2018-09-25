
// RegisterDlg.h : ͷ�ļ�
//

#pragma once
#include "Mediator.h"
// CRegisterDlg �Ի���
class CRegisterDlg : public CDialogEx
{
// ����
public:
	CRegisterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	ULONG_PTR           gdiplusToken;
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
//	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	int mWidth;
	int mHeight;
	bool is_in_drag;
private:
	std::vector<CButton *> vt_vec; 
	CWinThread * thread;
	CMFCButton *buttonUncom;
	Mediator mMediator;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
