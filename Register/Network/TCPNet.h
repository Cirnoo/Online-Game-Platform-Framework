#ifndef  _TCPNET_H
#define _TCPNET_H
#include <process.h>
#include <list>
#include "Packdef.h"
#include <Winsock2.h>
#pragma comment(lib,"Ws2_32.lib")


//#define _DEFSIZE     1024

class TCPNet 
{
public:
	TCPNet();
	virtual ~TCPNet();
public:
	bool ConnectServer();
	void DisConnectServer();
	bool SendData(char* szbuf,int nlen);
public:
	static  unsigned _stdcall ThreadRecv( void * );
private:
	SOCKET m_sockClient;
	HANDLE m_hThreadRecv;
	static bool   m_bFlagQuit;
	
};





#endif
