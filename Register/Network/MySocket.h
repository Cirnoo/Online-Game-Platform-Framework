#pragma once

// CMySocket ÃüÁîÄ¿±ê
#include "Packdef.h"
class CMySocket : public CSocket 
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	bool TestConnect(); //²â½»
	bool IsConnet();
	void SocketInit();
	void KeepAlive();
	static  unsigned _stdcall HeartBeatThreadProc(LPVOID lpParam);
	int SendMS(const DATA_PACKAGE & data);
	HANDLE mHeartBeat;
private:
	HANDLE  heart_thread;
	bool is_connect;
	bool is_init;
};



