#include "stdafx.h"
#include "Tool.h"
#include "MySocket.h"
#include "Sys.h"
bool CTool::ConnectServer()
{
	mysocket.SocketInit();
	if (!mysocket.TestConnect()&&!mysocket.IsConnet())
	{
		mysocket.Connect((SOCKADDR*)&sys.addrServer,sizeof(sys.addrServer));
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


void CTool::Registe(USER_BUF name,USER_BUF password)
{

	DATA_PACKAGE pack(MS_TYPE::REGISTER_RQ,USER_INFO(name,password));
	mysocket.SendMS(pack);
	ShowError();

}

void CTool::DealData(MS_TYPE type,DATA_BUF & data)
{
	DATA_PACKAGE pack(type,data);
	switch (type)
	{
	case MS_TYPE::REGISTER_RQ:
	case MS_TYPE::LOGIN_RQ:
		{
			mysocket.SendMS(pack);
			break;
		}
	case MS_TYPE::LOGIN_RE_T:
		{
			AfxGetMainWnd()->PostMessageW(WM_LOGIN);
			break;
		}
		
	case MS_TYPE::LOGIN_RE_F:
		{
			Warning("用户名或密码错误");
			break;
		}
	case MS_TYPE::REGISTER_RE_T:
		{
			AfxGetMainWnd()->PostMessageW(WM_REGISETR);
			Warning("注册成功");
			break;
		}
	case MS_TYPE::REGISTER_RE_F:
		{
			Warning("用户已存在");
			break;
		}
	default:
		{
			SetEvent(mysocket.mHeartBeat);
			break;
		}
			
	}
}

void CTool::DealData(const DATA_PACKAGE & pack)
{
	switch (pack.ms_type)
	{
	case MS_TYPE::REGISTER_RQ:
	case MS_TYPE::LOGIN_RQ:
		{
			mysocket.SendMS(pack);
			break;
		}
	case MS_TYPE::LOGIN_RE_T:
		{
			AfxGetMainWnd()->PostMessageW(WM_LOGIN);
			break;
		}

	case MS_TYPE::LOGIN_RE_F:
		{
			Warning("用户名或密码错误");
			break;
		}
	case MS_TYPE::REGISTER_RE_T:
		{
			AfxGetMainWnd()->PostMessageW(WM_REGISETR);
			Warning("注册成功");
			break;
		}
	case MS_TYPE::REGISTER_RE_F:
		{
			Warning("用户已存在");
			break;
		}
	default:
		{
			SetEvent(mysocket.mHeartBeat);
			break;
		}

	}
}

int CTool::RecieveData(void * buf,int size)
{
	return mysocket.Receive(buf,size);
}
