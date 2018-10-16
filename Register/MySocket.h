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
	//virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	bool IsConnet();
	int SendMS(DATA_PACKAGE data);
private:
	bool is_connect;

};


