#pragma once
#include <memory>
#include "Packdef.h"
#include "MySocket.h"
class CTool
{
public:
	bool ConnectServer();
	void Disconnect();
	void Registe(USER_BUF name,USER_BUF password);
	void DealData(MS_TYPE type,DATA_BUF & data);
	void DealData(const DATA_PACKAGE & pack);
	int  RecieveData(void * buf,int size);
public:
	CTool(void);
	~CTool(void);
	CMySocket mysocket;
	//std::unique_ptr<CData> data_deal;
};

