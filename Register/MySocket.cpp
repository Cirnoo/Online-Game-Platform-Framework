// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "MySocket.h"
#include "MySocket.h"

// CMySocket

CMySocket::CMySocket()
{
	is_connect=false;
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{
	is_connect=true;
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
	is_connect=false;
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	DATA_PACKAGE pack;
	this->Receive((char *)&pack,sizeof(pack),0);
	/*unsigned char size=GetBufSize(pack.ms_type);
	if(size>0)
	{
		this->Receive((char *)&pack,size,0);
	}*/
	sys.tools.DealData(pack);
}

bool CMySocket::IsConnet()
{
	return is_connect;
}

int CMySocket::SendMS(DATA_PACKAGE data)
{
	return Send(&data,sizeof(data),0);
}


// CMySocket 成员函数
