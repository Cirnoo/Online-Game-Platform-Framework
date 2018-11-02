// GameRoom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Register.h"
#include "GameRoom.h"
#include "afxdialogex.h"


// CGameRoom �Ի���



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
	theApp.tools.ConnectServer();
	m_room_list.DeleteAllItems();
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GET_ROOM_LIST;
	if(!theApp.tools.DealData(pack))
	{
		Warning("������Ϣ��ȡʧ��");
	}
	return TRUE;
}



BEGIN_MESSAGE_MAP(CGameRoom, CDialogEx)
	ON_BN_CLICKED(IDC_CREATE_ROOM, &CGameRoom::OnBnClickedCreateRoom)
	ON_MESSAGE(WM_ADD_ROOM, &CGameRoom::OnAddRoom)
	ON_MESSAGE(WM_UPDATE_ROOM, &CGameRoom::OnUpdateRoom)
	ON_NOTIFY(NM_DBLCLK, IDC_ROOM_LIST, &CGameRoom::OnNMDblclkRoomList)
END_MESSAGE_MAP()


// CGameRoom ��Ϣ�������


BOOL CGameRoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_room_list.InsertColumn(0,_T("������"),0,100);
	m_room_list.InsertColumn(1,_T("����ID"),0,100);
	m_room_list.InsertColumn(2,_T("��������"),0,100);
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
	CString num;
	num.Format(_T("%d"),info->num);
	m_room_list.SetItemText(0,2,num);
	return TRUE;
}


void CGameRoom::OnBnClickedCreateRoom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::CREATE_ROOM;
	ROOM_LIST_INFO info;
	info.master=L"123";
	info.name=L"121";
	pack.buf=info;
	theApp.tools.DealData(pack);
}





void CGameRoom::OnNMDblclkRoomList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	auto room_master=m_room_list.GetItemText(pNMItemActivate->iItem,1);
	auto num_str=m_room_list.GetItemText(pNMItemActivate->iItem,2);
	auto & sys_room=theApp.sys.room;
	int num=_ttoi(num_str);
	sys_room.name=room_master;  //��������
	sys_room.mate_arr[num]=theApp.sys.user.name.GetStr(); //�û�����
	sys_room.num=num;
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::ENTER_ROOM;
	theApp.tools.DealData(pack);
	EndDialog(WM_ENTER_ROOM);
}
