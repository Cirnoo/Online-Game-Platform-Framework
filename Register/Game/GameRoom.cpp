// GameRoom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Register.h"
#include "GameRoom.h"
#include "afxdialogex.h"






class RoomName : public CDialogEx
{
	DECLARE_DYNAMIC(RoomName)

public:
	RoomName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RoomName();

	// �Ի�������
	enum { IDD = IDD_INPUT_ROOM_NAME };

protected:
	//HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_str;
	virtual void OnOK();
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
	//ON_BN_CLICKED(IDOK, &RoomName::OnBnClickedOk)
END_MESSAGE_MAP()


// RoomName ��Ϣ�������


BOOL RoomName::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	return TRUE;
}



void RoomName::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData();
	if (m_str.IsEmpty())
	{
		Warning("�����뷿����");
		return ;
	}
	theApp.sys.room.name=m_str;
	EndDialog(WM_ENTER_ROOM);
	CDialogEx::OnOK();
}


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
	m_room_list.InsertColumn(0,_T("������"),0,120);
	m_room_list.InsertColumn(1,_T("��������"),0,80);
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
	CString num;
	num.Format(_T("%d"),info->num);
	m_room_list.SetItemText(0,1,num);
	return TRUE;
}


void CGameRoom::OnBnClickedCreateRoom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RoomName room_name;
	if(room_name.DoModal()!=IDOK)
	{
		return ;
	}
	auto & sys=theApp.sys;
	sys.room.num=0;
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::CREATE_ROOM;
	PLAYER_INFO info;
	info.name=sys.user.name;
	info.room_name=sys.room.name;
	info.pos=sys.room.num;
	pack.buf=info;
	theApp.tools.DealData(pack);
	theApp.CloseMainWnd();	//��Ҫ ��ɾ
	EndDialog(WM_ENTER_ROOM);
}





void CGameRoom::OnNMDblclkRoomList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	auto room_name=m_room_list.GetItemText(pNMItemActivate->iItem,0);	
	auto num_str=m_room_list.GetItemText(pNMItemActivate->iItem,1);
	auto & sys_room=theApp.sys.room;
	int num=_ttoi(num_str);

	sys_room.name=room_name;  //��������
	sys_room.mate_arr[num-1]=theApp.sys.user.name.GetStr(); //�û�����
	sys_room.num=num-1;
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::ENTER_ROOM;
	theApp.tools.DealData(pack);
	theApp.CloseMainWnd();	//��Ҫ ��ɾ
	EndDialog(WM_ENTER_ROOM);
}


// RoomName �Ի���

