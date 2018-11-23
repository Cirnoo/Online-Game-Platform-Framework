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
	const auto & addrServer=theApp.sys.client_info.addrServer;
	mysocket.SocketInit();
	mysocket.Connect((SOCKADDR*)&addrServer,sizeof(addrServer));
	if (GetLastError()==ERROR_SOCKET_ALREADE_CONNECT) //socket已经连接
	{
		return true;
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
	case MS_TYPE::ENTER_ROOM:
	case MS_TYPE::LEAVE_ROOM:
	case MS_TYPE::GAME_START:
	case MS_TYPE::CALL_LANDLORD_RQ:
	case MS_TYPE::ROB_LANDLORD_RQ:
	case MS_TYPE::NOT_CALL:
	case MS_TYPE::NOT_ROB:
	case MS_TYPE::PLAY_CARD:
		if(mysocket.SendMS(pack)<0)
		{
			return false;
		}
		break;
	case MS_TYPE::LOGIN_RE_T:
		AfxGetMainWnd()->PostMessageW(WM_LOGIN);
		break;
	case MS_TYPE::LOGIN_RE_F:
		Warning("用户名或密码错误")
			break;
	case MS_TYPE::REGISTER_RE_T:
		AfxGetMainWnd()->PostMessageW(WM_REGISETR);
		Warning("注册成功")
			break;
	case MS_TYPE::REGISTER_RE_F:
		Warning("用户已存在")
			break;
	case MS_TYPE::ADD_ROOM:
		AfxGetMainWnd()->SendMessageW(WM_ADD_ROOM,(WPARAM)&pack);
		break;
	case MS_TYPE::UPDATE_ROOM:
		AfxGetMainWnd()->SendMessageW(WM_UPDATE_ROOM,(WPARAM)&pack);
		break;
	case MS_TYPE::CREATE_ROOM_RE_T:
	case MS_TYPE::ENTER_ROOM_RE_T:
		AfxGetMainWnd()->SendMessage(WM_ENTER_ROOM,(WPARAM)&pack);
		break;
	case MS_TYPE::CREATE_ROOM_RE_F:
		Warning("已存在的房间名")
		break;
	case MS_TYPE::ENTER_ROOM_RE_F:
		Warning("未知错误,请重试")
		break;
	case MS_TYPE::MATE_INFO_UPDATE:
		AfxGetMainWnd()->SendMessage(WM_GET_ROOM_MATE,(WPARAM)&pack);
		break;
	case MS_TYPE::ALLOC_POKER:
		AfxGetMainWnd()->SendMessage(WM_GET_CARDS,(WPARAM)&pack);
		break;
	case MS_TYPE::IS_CALL_LANDLORD:
	case MS_TYPE::IS_ROB_LANDLORD:
	case MS_TYPE::IS_PALY_CARD:
		AfxGetMainWnd()->SendMessage(WM_GAME_PROCESS,(WPARAM)&pack);
		break;
	case MS_TYPE::SET_LANDLORD:
		AfxGetMainWnd()->SendMessage(WM_SET_LANDLORD,(WPARAM)&pack);
		break;
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
