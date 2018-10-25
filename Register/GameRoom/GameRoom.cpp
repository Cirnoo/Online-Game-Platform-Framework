// GameRoom.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "GameRoom.h"
#include "afxdialogex.h"


// CGameRoom 对话框



IMPLEMENT_DYNAMIC(CGameRoom, CDialogEx)

CGameRoom::CGameRoom(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameRoom::IDD, pParent)
{

}

CGameRoom::~CGameRoom()
{
}

void CGameRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROOM_LIST, m_room_list);
}


LRESULT CGameRoom::OnUpdateRoom(WPARAM wParam, LPARAM lParam)
{
	sys.tools.ConnectServer();
	m_room_list.DeleteAllItems();
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GET_ROOM_LIST;
	if(!sys.tools.DealData(pack))
	{
		Warning("房间信息获取失败");
	}
	return TRUE;
}



BEGIN_MESSAGE_MAP(CGameRoom, CDialogEx)
	ON_BN_CLICKED(IDC_CREATE_ROOM, &CGameRoom::OnBnClickedCreateRoom)
	ON_MESSAGE(WM_ADD_ROOM, &CGameRoom::OnAddRoom)
	ON_MESSAGE(WM_UPDATE_ROOM, &CGameRoom::OnUpdateRoom)
	ON_NOTIFY(NM_DBLCLK, IDC_ROOM_LIST, &CGameRoom::OnNMDblclkRoomList)
END_MESSAGE_MAP()


// CGameRoom 消息处理程序


BOOL CGameRoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_room_list.InsertColumn(0,_T("房间名"),0,100);
	m_room_list.InsertColumn(1,_T("房主ID"),0,100);
	m_room_list.InsertColumn(2,_T("房间人数"),0,100);
	m_room_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	OnUpdateRoom();
	return TRUE;
}



LRESULT CGameRoom::OnAddRoom(WPARAM wParam, LPARAM lParam)
{
	auto * pack=(DATA_PACKAGE *)wParam;
	ROOM_LIST_INFO * info=(ROOM_LIST_INFO *)&pack->buf;
	m_room_list.InsertItem(0,L"");
	m_room_list.SetItemText(0,0,info->name.GetStr().c_str());
	m_room_list.SetItemText(0,1,info->master.GetStr().c_str());
	WCHAR num[2];
	wsprintfW(num, L"%d", info->num);
	m_room_list.SetItemText(0,2,num);
	return TRUE;
}


void CGameRoom::OnBnClickedCreateRoom()
{
	// TODO: 在此添加控件通知处理程序代码
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::CREATE_ROOM;
	ROOM_LIST_INFO info;
	info.master=L"123";
	info.name=L"121";
	pack.buf=info;
	sys.tools.DealData(pack);
}





void CGameRoom::OnNMDblclkRoomList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	auto room_master=m_room_list.GetItemText(pNMItemActivate->iItem,1);
	//this->PostMessage(WM_CLOSE);
	exit(0);
}
