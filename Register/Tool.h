#pragma once
#include <memory>
#include "Packdef.h"
#include "MySocket.h"
class CTool
{
public:
	static CTool & GetInstance(); 
	bool ConnectServer();
	void Disconnect();
	bool DealData(const DATA_PACKAGE & pack);
	int  RecieveData(void * buf,int size,int peek_flag=0);
	~CTool();
private:
	CTool(void);
	CMySocket mysocket;
	void GetRoomInfo(const DATA_PACKAGE & pack);
private:
	static CTool* tool;//Singleton pattern
};

