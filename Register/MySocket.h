#pragma once

// CMySocket ÃüÁîÄ¿±ê
#include "Packdef.h"
class CMySocket : public CSocket 
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnConnect(int nErrorCode);
	bool is_connect;
	int SendMS(DATA_PACKAGE data);
private:
};


