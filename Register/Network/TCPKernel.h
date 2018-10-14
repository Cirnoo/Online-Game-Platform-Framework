#ifndef _TCPKERNEL_H
#define _TCPKERNEL_H

#include "TCPNet.h"
class TCPKernel 
{
public:
	TCPKernel();
	virtual ~TCPKernel();
public:
	bool Open();
	void Close();
	bool SendData(char* szbuf,int nlen);
	void DealData(SOCKET sock,char* szbuf);
private:
	
};

#endif