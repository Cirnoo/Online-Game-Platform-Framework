// GameRoom.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "GameRoom.h"
#include "afxdialogex.h"
#include "Sys.h"



class RoomName : public CDialogEx
{
	DECLARE_DYNAMIC(RoomName)

public:
	RoomName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RoomName();

	// 对话框数据
	enum { IDD = IDD_INPUT_ROOM_NAME };

protected:
	//HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CString m_str;
};



IMPLEMENT_DYNAMIC(RoomName, CDialogEx)

	RoomName::RoomName(CWnd* pParent /*=NULL*/)
	: CDialogEx(RoomName::IDD, pParent)
	, m_str(_T(""))
{

}

RoomName::~RoomName()
{
}

void RoomName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str);
}


BEGIN_MESSAGE_MAP(RoomName, CDialogEx)
END_MESSAGE_MAP()


// RoomName 消息处理程序


BOOL RoomName::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

void RoomName::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData();
	if (m_str.IsEmpty())
	{
		Warning("请输入房间名");
		return ;
	}
	theApp.sys.client_info.room.name=m_str;
	EndDialog(WM_ENTER_ROOM);
	CDialogEx::OnOK();
}


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
	const auto & room_info=::GetPackBufData<ROOM_LIST_INFO>(wParam);
	char num=room_info.num;
	const CString str=room_info.name.GetStr().c_str();
	for(int i=0;i<m_room_list.GetItemCount();i++)
	{
		if(str==m_room_list.GetItemText(i,0))
		{
			if (num==0)
			{
				m_room_list.DeleteItem(i);
			}
			else
			{
				CString num_str;
				num_str.Format(_T("%d"),num);
				m_room_list.SetItemText(i,1,num_str);
			}
			return TRUE;
		}
	}
	OnAddRoom(wParam,NULL);		//房间没在列表中
	return TRUE;
}





BEGIN_MESSAGE_MAP(CGameRoom, CDialogEx)
	ON_BN_CLICKED(IDC_CREATE_ROOM, &CGameRoom::OnBnClickedCreateRoom)
	ON_MESSAGE(WM_ADD_ROOM, &CGameRoom::OnAddRoom)
	ON_MESSAGE(WM_UPDATE_ROOM, &CGameRoom::OnUpdateRoom)
	ON_MESSAGE(WM_ENTER_ROOM, &CGameRoom::OnEnterRoom)
	ON_NOTIFY(NM_DBLCLK, IDC_ROOM_LIST, &CGameRoom::OnNMDblclkRoomList)
END_MESSAGE_MAP()


// CGameRoom 消息处理程序


BOOL CGameRoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_room_list.InsertColumn(0,_T("房间名"),0,120);
	m_room_list.InsertColumn(1,_T("房间人数"),0,80);
	m_room_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	GetRoomList();
	return TRUE;
}



LRESULT CGameRoom::OnAddRoom(WPARAM wParam, LPARAM lParam)
{
	const auto & room_info=::GetPackBufData<ROOM_LIST_INFO>(wParam);
	m_room_list.InsertItem(0,L"");
	m_room_list.SetItemText(0,0,room_info.name.GetStr().c_str());
	CString num;
	num.Format(_T("%d"),room_info.num);
	m_room_list.SetItemText(0,1,num);
	return TRUE;
}


void CGameRoom::OnBnClickedCreateRoom()
{
	// TODO: 在此添加控件通知处理程序代码
	RoomName room_name;
	if(room_name.DoModal()!=IDOK)
	{
		return ;
	}
	auto & client=theApp.sys.client_info;
	client.room.num=1;
	client.room.mate_arr[0]=client.player_name;
	SendEnterRoomMs(MS_TYPE::CREATE_ROOM);
}





void CGameRoom::OnNMDblclkRoomList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	auto room_name=m_room_list.GetItemText(pNMItemActivate->iItem,0);	
	if (room_name.IsEmpty())
	{
		return;
	}
	auto num_str=m_room_list.GetItemText(pNMItemActivate->iItem,1);
	auto & sys_room=theApp.sys.client_info.room;
	int num=_ttoi(num_str);

	sys_room.name=room_name;  //房间名字
	sys_room.mate_arr[num-1]=theApp.sys.client_info.player_name; //用户名字
	sys_room.num=num-1;
	SendEnterRoomMs(MS_TYPE::ENTER_ROOM);
}


LRESULT CGameRoom::OnEnterRoom(WPARAM wParam, LPARAM lParam)
{
	//进入房间成功
	auto info=(DATA_PACKAGE *)wParam;
	const ENTER_ROOM_RE & buf = info->buf;
	auto & client_info=theApp.sys.client_info;
	if (info->ms_type==MS_TYPE::ENTER_ROOM_RE_T)		//如果是新加入房间 则接收当前房间玩家信息
	{
		for (int i=0;i<3;i++)
		{
			client_info.room.mate_arr[i]=buf.mate_name[i].GetStr();
		}
	}
	else	//如果是直接创建房间 第一个玩家名为自己
	{
		client_info.room.mate_arr[0]=client_info.player_name;
	}
	client_info.player_pos=buf.player_pos;
	theApp.CloseMainWnd();	//重要 勿删
	EndDialog(WM_ENTER_ROOM);
	return 0;
}

void CGameRoom::SendEnterRoomMs(const MS_TYPE type) 
{
	auto & client=theApp.sys.client_info;
	DATA_PACKAGE pack;
	pack.ms_type=type;
	PLAYER_INFO info;
	info.name=client.player_name;
	info.room_name=client.room.name;
	info.pos=client.room.num-1;
	pack.buf=info;
	theApp.tools.DealData(pack);

}

bool CGameRoom::GetRoomList()
{
	theApp.tools.ConnectServer();
	m_room_list.DeleteAllItems();
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GET_ROOM_LIST;
	if(!theApp.tools.DealData(pack))
	{
		Warning("房间信息获取失败");
		return false;
	}
	return true;
}
