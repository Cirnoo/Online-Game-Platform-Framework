#pragma once
#include "Packdef.h"
class CMySocket;
class CData
{
public:
	CData();
	CData(CMySocket * _socket);
	~CData(void);
	void Registe(USER_BUF name,USER_BUF password);
	void DealData(MS_TYPE type,USER_INFO data);
	void OnRegiste();
private:
	CMySocket * mSocket;
};
