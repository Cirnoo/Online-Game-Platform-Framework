#include "stdafx.h"
#include "Data.h"
#include "MySocket.h"

CData::CData(CMySocket * _socket)
{
	mSocket=_socket;
}

CData::~CData(void)
{
}

void CData::Registe(USER_BUF name,USER_BUF password)
{
	DATA_PACKAGE pack(MS_TYPE::REGISTE_RQ,name,password);
	mSocket->SendMS(pack);
}

void CData::DealData(MS_TYPE type,USER_INFO data)
{
	USER_BUF & name=data.name;
	USER_BUF & password=data.password;
	switch (type)
	{
	case MS_TYPE::REGISTE_RQ:
		{
			Registe(name,password);
			break;
		}
	default:
		break;
	}
}


