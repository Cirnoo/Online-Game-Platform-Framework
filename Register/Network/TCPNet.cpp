#include "stdafx.h"
#include "TCPNet.h"



TCPNet::TCPNet()
{
	m_sockClient = NULL;
	m_hThreadRecv = NULL;
}


TCPNet::~TCPNet(void)
{
}
bool TCPNet::ConnectServer()
{
	//1.选择种类 -- 
	 WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
       // printf("WSAStartup failed with error: %d\n", err);
        return false;
    }


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
       // printf("Could not find a usable version of Winsock.dll\n");
        DisConnectServer();
        return false;
    }
   
        

	//2.雇佣店长 -- socket 
	m_sockClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP );
	if(m_sockClient == INVALID_SOCKET )
	{
		 DisConnectServer();
        return false;
	}
	//3.选址 --- 
	sockaddr_in  addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr(_SERVER_IP);
	addrServer.sin_port = htons(_DEF_PORT);
	if(SOCKET_ERROR == connect(m_sockClient,(const sockaddr*)&addrServer,sizeof(addrServer)))
	{
		 DisConnectServer();
        return false;
	}
	 
	

	//5.创建线程
	m_hThreadRecv = (HANDLE)_beginthreadex(NULL,0,&ThreadRecv,this,0,0);
	
	return true;
}


unsigned _stdcall TCPNet::ThreadRecv( void * lpvoid)
{
	TCPNet *pthis = (TCPNet*)lpvoid ;
	
	char *pszbuf = NULL;
	int nRelReadNum;
    int nPackdefSize;
	
	while(TCPNet::m_bFlagQuit)
	{
		
		//接收包大小
		nRelReadNum =  recv(pthis->m_sockClient,(char*)&nPackdefSize,sizeof(int),0);
		if(nRelReadNum ==0)
		{
			//关闭socket,并且结束线程
			
			break;

		}
		else if(nRelReadNum == SOCKET_ERROR)
			continue;

		pszbuf = new char[nPackdefSize];
		int nOffset = 0;
		while(nPackdefSize)
		{
			//接收数据包
			 nRelReadNum =  recv(pthis->m_sockClient,pszbuf +nOffset ,nPackdefSize,0);
			 nOffset += nRelReadNum;
			 nPackdefSize -= nRelReadNum;
		}
		
	     //将数据包交给核心处理类处理
		m_pManager->DealData(pszbuf);

	    delete []pszbuf;
		pszbuf = NULL;
		


	}
	return 0;
}

void TCPNet::DisConnectServer()
{
	m_bFlagQuit = false;
	if(m_hThreadRecv )
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hThreadRecv,100))
			TerminateThread(m_hThreadRecv,-1);
		
		CloseHandle(m_hThreadRecv);
		m_hThreadRecv = NULL;

	
	}
	WSACleanup();
	if(m_sockClient)
	{
		closesocket(m_sockClient);
		m_sockClient = NULL;
	}
}

bool TCPNet::SendData(char* szbuf,int nlen)
{
	if( !szbuf|| nlen <=0 )
		return false;

    //发送包大小
	if(send(m_sockClient,(const char*)&nlen,sizeof(int),0)<=0)
		return false;

	//发送包内容
	if(send(m_sockClient,szbuf,nlen,0)<=0)
		return false;
	
	return true;
}