// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "MySocket.h"


// CMySocket

CMySocket::CMySocket():mData(this)
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

int CMySocket::SendMS(DATA_PACKAGE data)
{
	return Send(&data,sizeof(data),0);
}

// CMySocket 成员函数
