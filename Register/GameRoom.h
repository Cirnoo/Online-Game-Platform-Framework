#pragma once
#include "afxcmn.h"


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
	void GetRoomList();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_room_list;
	virtual BOOL OnInitDialog();
};
