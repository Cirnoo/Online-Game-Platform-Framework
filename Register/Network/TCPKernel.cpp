#include "TCPKernel.h"

TCPKernel::TCPKernel()
{
}

TCPKernel::~TCPKernel()
{
	
}




bool TCPKernel::Open()
{

}

void TCPKernel::Close()
{
	m_pTcpNet->UnInitNetWork();
	m_threadpool.DestroyThreadPool();
}

void TCPKernel::DealData(SOCKET sock,char* szbuf)
{
	 //��������---Э��ӳ���


}
