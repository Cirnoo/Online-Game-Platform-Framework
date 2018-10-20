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


void CGameRoom::GetRoomList()
{
	m_room_list.DeleteAllItems();
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::GET_ROOM_LIST;
	sys.tools.DealData(pack);
	Sleep(100);
	int cnt=0;
	if(sys.tools.RecieveData(&cnt,sizeof(int))<=0)
	{
		Warning("�������ݽ���ʧ��")
	}
	for (int i=0;i<cnt;i++)
	{
		ROOM_INFO info;
		sys.tools.RecieveData(&info,sizeof(info));
		m_room_list.InsertItem(i,L"");
		m_room_list.SetItemText(i,1,info.name.GetStr().c_str());
		m_room_list.SetItemText(i,1,info.master.GetStr().c_str());
		wchar_t num;
		_i64tow_s(info.num,&num,1,10);
		m_room_list.SetItemText(i,1,&num);
	}
}

BEGIN_MESSAGE_MAP(CGameRoom, CDialogEx)
END_MESSAGE_MAP()


// CGameRoom ��Ϣ�������


BOOL CGameRoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_room_list.InsertColumn(0,_T("������"),0,100);
	m_room_list.InsertColumn(1,_T("����ID"),0,100);
	m_room_list.InsertColumn(2,_T("��������"),0,100);
	m_room_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	return TRUE;
}
