#pragma once
#include "afxcmn.h"

#include "Text.h"
// CGameRoom 对话框

class CGameRoom : public CDialogEx
{
	DECLARE_DYNAMIC(CGameRoom)

public:
	CGameRoom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameRoom();

// 对话框数据
	enum { IDD = IDD_GAMEROOM };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnUpdateRoom(WPARAM wParam=NULL, LPARAM lParam=NULL);
	void SendEnterRoomMs(const MS_TYPE type);
	bool GetRoomList();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_room_list;
	
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnAddRoom(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCreateRoom();
	afx_msg void OnNMDblclkRoomList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnterRoom(WPARAM wParam, LPARAM lParam);
};
