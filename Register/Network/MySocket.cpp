// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "MySocket.h"
#include "MySocket.h"

// CMySocket

CMySocket::CMySocket()
{
	is_init=false;
	mHeartBeat=CreateEvent(NULL,FALSE,FALSE,NULL);  //自动复位事件状态，初始状态未触发
	heart_thread=(HANDLE)_beginthreadex(NULL,0,&HeartBeatThreadProc,this,CREATE_SUSPENDED,0);
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnAccept(int nErrorCode)
{
	CAsyncSocket::OnAccept(nErrorCode);
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
	theApp.tools.DealData(pack);
}

bool CMySocket::TestConnect()
{
	DATA_PACKAGE test;
	if(SendMS(test)<0)
	{
		return false;
	}
	else
	{
		Sleep(100);
		Receive((char *)&test,sizeof(test),0);
		if(test.ms_type==MS_TYPE::HEARTBEAT)
		{
			is_connect=true;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool CMySocket::IsConnet()
{
	return is_connect;
}

void CMySocket::SocketInit()
{
	if (!is_init)
	{
		WSAData wsaData;
		if (!AfxSocketInit(&wsaData))
		{
			AfxMessageBox(_T("Failed to Initialize Sockets"), MB_OK | MB_ICONSTOP);
		}
		Create();
		is_init=true;
	}	

}

void CMySocket::KeepAlive()
{
	ResumeThread(heart_thread);
}

unsigned _stdcall CMySocket::HeartBeatThreadProc(LPVOID lpParam)
{
	CMySocket *pthis = (CMySocket*)lpParam;
	DATA_PACKAGE pack;
	pack.ms_type=MS_TYPE::HEARTBEAT;
	while (true)
	{
		if(pthis->SendMS(pack)<=0)
		{
			pthis->is_connect=false;
		}
		if (WaitForSingleObject(pthis->mHeartBeat,1000)==WAIT_TIMEOUT)
		{
			pthis->is_connect=false;
		}
		else
		{
			pthis->is_connect=true;
		}
		Sleep(3000);
	}
	return 0;
}

int CMySocket::SendMS(const DATA_PACKAGE & data)
{
	return Send(&data,sizeof(data),0);
}


// CMySocket 成员函数
