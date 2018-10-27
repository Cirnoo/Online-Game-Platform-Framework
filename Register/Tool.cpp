#include "stdafx.h"
#include "Tool.h"
#include "MySocket.h"
#include "Sys.h"


CTool & CTool::GetInstance()
{
	return *CTool::tool;
}
bool CTool::ConnectServer()
{
	mysocket.SocketInit();
	if (!mysocket.TestConnect())
	{
		mysocket.Connect((SOCKADDR*)&theApp.sys.addrServer,sizeof(theApp.sys.addrServer));
		if (GetLastError()==ERROR_SOCKET_ALREADE_CONNECT) //socket�Ѿ�����
		{
			mysocket.Close();
			mysocket.Create();
			return ConnectServer();
		}
	}
	if(ShowError())
	{
		Disconnect();
		return false;
	}
	return true;
}

void CTool::Disconnect()
{
	if (mysocket.IsConnet())
	{
		mysocket.Close();
	}	
}

CTool::CTool(void)
{
}


CTool::~CTool(void)
{
}






bool CTool::DealData(const DATA_PACKAGE & pack)
{
	switch (pack.ms_type)
	{
	case MS_TYPE::REGISTER_RQ:
	case MS_TYPE::LOGIN_RQ:
	case MS_TYPE::GET_ROOM_LIST:
	case MS_TYPE::CREATE_ROOM:
		if(mysocket.SendMS(pack)<0)
		{
			return false;
		}
	case MS_TYPE::LOGIN_RE_T:
		AfxGetMainWnd()->PostMessageW(WM_LOGIN);
		break;
	case MS_TYPE::LOGIN_RE_F:
		Warning("�û������������");
		break;
	case MS_TYPE::REGISTER_RE_T:
		AfxGetMainWnd()->PostMessageW(WM_REGISETR);
		Warning("ע��ɹ�");
		break;
	case MS_TYPE::REGISTER_RE_F:
		Warning("�û��Ѵ���");
		break;
	case MS_TYPE::ADD_ROOM:
		AfxGetMainWnd()->SendMessageW(WM_ADD_ROOM,(WPARAM)&pack);
		break;
	case MS_TYPE::UPDATE_ROOM:
		AfxGetMainWnd()->SendMessageW(WM_UPDATE_ROOM);
	default:
		SetEvent(mysocket.mHeartBeat);
		break;
	}
	return true;
}

int CTool::RecieveData(void * buf,int size,int peek_flag)
{
	return mysocket.Receive(buf,size,peek_flag);
}
