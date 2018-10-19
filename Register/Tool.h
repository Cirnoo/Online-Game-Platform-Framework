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
	void DealData(MS_TYPE type,USER_INFO data);
	void DealData(const DATA_PACKAGE & pack);
public:
	CTool(void);
	~CTool(void);
	CMySocket mysocket;
	//std::unique_ptr<CData> data_deal;
};

