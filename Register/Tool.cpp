#include "stdafx.h"
#include "Tool.h"
#include "MySocket.h"
#include "Data.h"
#include "Sys.h"
bool CTool::ConnectServer()
{
	Disconnect();
	mysocket.Create();
	mysocket.Connect((SOCKADDR*)&sys.addrServer,sizeof(sys.addrServer));
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
	mysocket.Create();
}


CTool::~CTool(void)
{
}


void CTool::Registe(USER_BUF name,USER_BUF password)
{
	DATA_PACKAGE pack(MS_TYPE::REGISTE_RQ,name,password);
	mysocket.SendMS(pack);
	ShowError();

}

void CTool::DealData(MS_TYPE type,USER_INFO data)
{
	DATA_PACKAGE pack(type,data.name,data.password);
	switch (type)
	{
	case MS_TYPE::REGISTE_RQ:
	case MS_TYPE::LOGIN_RQ:
		{
			mysocket.SendMS(pack);
			break;
		}
	case MS_TYPE::LOGIN_RE_T:
		break;
	case MS_TYPE::LOGIN_RE_F:
		{
			ShowWarring("用户名或密码错误");
		}
	case MS_TYPE::REGISTE_RE_T:
		{
			AfxGetMainWnd()->PostMessageW(WM_LOGIN);
		}
	case MS_TYPE::REGISTE_RE_F:
		{
			ShowWarring("用户已存在");
		}
		default:
			break;
	}
}

void CTool::DealData(DATA_PACKAGE pack)
{
	DealData(pack.ms_type,pack.user);
}