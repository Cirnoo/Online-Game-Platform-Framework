#pragma once
#include "afxcmn.h"


// CGameRoom �Ի���

class CGameRoom : public CDialogEx
{
	DECLARE_DYNAMIC(CGameRoom)

public:
	CGameRoom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameRoom();

// �Ի�������
	enum { IDD = IDD_GAMEROOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnUpdateRoom(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_room_list;
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnAddRoom(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCreateRoom();
};
