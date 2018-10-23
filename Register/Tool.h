#pragma once
#include <memory>
#include "Packdef.h"
#include "MySocket.h"
class CTool
{
public:
	bool ConnectServer();
	void Disconnect();
	bool DealData(const DATA_PACKAGE & pack);
	int  RecieveData(void * buf,int size,int peek_flag=0);
public:
	CTool(void);
	~CTool(void);
	CMySocket mysocket;
	//std::unique_ptr<CData> data_deal;
};

