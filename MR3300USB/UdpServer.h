#pragma once
class CUdpServer
{
public:
	CUdpServer(int nPort);
	~CUdpServer();

	//int UdpInit(int nPort, const char *IP);
	int UdpInit();
	int ReceiveData(char * pBuffer, UINT & nRecv, UINT RecvSize);
	int ReceiveData(char * pBuffer, UINT & nRecv);

public:
	SOCKET m_ReceivingSocket;
	SOCKADDR_IN m_SenderAddr;
	int m_SenderAddrSize;

	int m_nPort;
};
extern CUdpServer *g_pData;
extern CUdpServer *g_pAud;
//extern CUdpServer *g_pResp;
extern CUdpServer *g_pIF;

