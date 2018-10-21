#pragma once
#include <memory>
#include "Packdef.h"
#include "MySocket.h"
class CTool
{
public:
	bool ConnectServer();
	void Disconnect();
	void DealData(MS_TYPE type,DATA_BUF & data);
	void DealData(const DATA_PACKAGE & pack);
	int  RecieveData(void * buf,int size,int peek_flag=0);
public:
	CTool(void);
	~CTool(void);
	CMySocket mysocket;
	//std::unique_ptr<CData> data_deal;
};

