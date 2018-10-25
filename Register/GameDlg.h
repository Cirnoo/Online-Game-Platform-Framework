#pragma once

#include <vector>
#include "Text.h"
#include "Packdef.h"

// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CString master);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
	enum { IDD = IDD_GAMEDLG };
	
protected:
	HICON m_hIcon;
	CString m_master;
	int m_width,m_height;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	Cards m_card[54];//13*4+2=54����
	std::vector<Cards> poker_in_hand;
	void ShowCtrl(Gdiplus::Graphics *  g);
	CText m_text[3];
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitCtrl();
	void RandomShuffle();
	void SortHand();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
