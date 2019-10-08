#include "StdAfx.h"
#include "RemoteBase.h"
#include "SocketSA.h"

//************************************
// Method:    RemoteBase
// FullName:  RemoteBase::RemoteBase
// Access:    public 
// Returns:   构造函数 
// Qualifier:
// Parameter: char * szIP
//            仪器地址
// Parameter: int nPort
//            仪器端口
//************************************
RemoteBase::RemoteBase(char* szIP, int nPort)
{
	strcpy(m_IP, szIP);
	m_nPort = nPort;
	m_pSocket = new CSocketSA();
}


//************************************
// Method:    ~RemoteBase
// FullName:  RemoteBase::~RemoteBase
// Access:    virtual public 
// Returns:   
// Qualifier: 析构
// Parameter: void
//************************************
RemoteBase::~RemoteBase(void)
{
	if (m_pSocket != NULL)
		delete m_pSocket;
}

//************************************
// Method:    ConnectDev
// FullName:  RemoteBase::ConnectDev
// Access:    public 
// Returns:   OPT_RET
// Qualifier: 连接仪器
//************************************
OPT_RET RemoteBase::ConnectDev()
{
	CString szPort;
	szPort.Format(_T("%d"), m_nPort);

	int num = MultiByteToWideChar(0, 0, m_IP, -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, m_IP, -1, wide, num);

	bool IsSucc = m_pSocket->ConnectTo(wide, szPort, PF_INET, SOCK_STREAM, true, 3, 1);
	if (IsSucc)
	{
		return OPT_SUCCESS;
	}
	return OPT_DEV_CONNECT_FAIL;
}

//************************************
// Method:    DisconnectDev
// FullName:  RemoteBase::DisconnectDev
// Access:    public 
// Returns:   void
// Qualifier: 断开连接
//************************************
void RemoteBase::DisconnectDev()
{
	m_pSocket->CloseComm();
}

//************************************
// Method:    DelStr
// FullName:  DelStr
// Access:    public 
// Returns:   void
// Qualifier: 从字符串中删除指定的字符串
// Parameter: const char * str
//            原始字符串字符串
// Parameter: const char * sub_str
//            要删除的字符串
// Parameter: char * result
//            删除后的结果
//************************************
void DelStr(const char *str, const char* sub_str, char *result)
{  
	int sublen = 0;         //获得子串的长度
	const char *t = sub_str;
	while(*t++ != '\0')
	{
		sublen++;
	}

	int pos = 0;
	int pp = 0;
	int repos = 0; // 结果子串的索引
	while(*(str + pos) != '\0')
	{
		char t = *(str + pos);
		if(t == *(sub_str + pp)) // 重复子串起始位置
		{
			*(result + repos) = t;
			repos++;

			if(pp < sublen - 1) // 还未完全重复
			{
				pp++;
			}
			else if(pp == sublen - 1) // 完全重复了
			{
				pp = 0;
				repos -= sublen; // 回溯下标位置
			}           
		}
		else{ // 不是一样的字符
			*(result + repos) = t;
			repos++;
		}
		pos++;
	}
	*(result + repos) = '\0';
}

//************************************
// Method:    SendCmd
// FullName:  RemoteBase::SendCmd
// Access:    public 
// Returns:   OPT_RET
// Qualifier: 发送控制指令
// Parameter: TCHAR * szCmd
//            控制指令
// Parameter: int nTimeOut
//            发送超时时间，该时间同时
//            也是指令发送成功的回读时间
// Parameter: bool IsEcho
//            是否使用原命令返回
//************************************
OPT_RET RemoteBase::SendCmd(char* szCmd, int nTimeOut /*= 3000*/, bool IsEcho /*= true*/)
{
	if ( m_pSocket->IsOpen() )
	{
		DWORD dwWrite = m_pSocket->WriteComm((LPBYTE)szCmd, strlen(szCmd), nTimeOut);
		
		if (dwWrite == -1)
			return OPT_SEND_COMMAND_FAIL;

		if (IsEcho)
		{
			const int RECV_BUF_SIZE = 5000;
			BYTE byRecv[RECV_BUF_SIZE] = {0};
			DWORD dwRecv = m_pSocket->ReadComm(byRecv, RECV_BUF_SIZE, nTimeOut);
			if (dwRecv == -1)
				return OPT_RECV_ECHO_TIMEOUT;
		}

		return OPT_SUCCESS;
	}

	return OPT_DEV_NOT_CONNECTED;
}

//************************************
// Method:    QueryStatus
// FullName:  RemoteBase::QueryStatus
// Access:    public 
// Returns:   OPT_RET
// Qualifier: 查询仪器某项状态
// Parameter: TCHAR * szCmd
//            查询指令
// Parameter: TCHAR * szRet
//            返回的数据
// Parameter: int nTimeOut
//            读取超时时间
// Parameter: bool IsEcho
//            是否是原命令返回
//************************************
OPT_RET RemoteBase::QueryStatus(char* szCmd, char* szRet, int nTimeOut /*= 3000*/, bool IsEcho /*= true*/)
{	
	if ( m_pSocket->IsOpen() )
	{
		const int RECV_BUF_SIZE = 5000;
		BYTE byRecv[RECV_BUF_SIZE] = {0};
		DWORD dwWrite = m_pSocket->WriteComm((LPBYTE)szCmd, strlen(szCmd), nTimeOut);

		if (dwWrite == -1)
			return OPT_SEND_COMMAND_FAIL;

		DWORD dwRecv = m_pSocket->ReadComm(byRecv, RECV_BUF_SIZE, nTimeOut);
		if (dwRecv == -1)
			return OPT_RECV_ECHO_TIMEOUT;
		
		strcpy(szRet, (char*)byRecv);

		if (IsEcho)
		{
			DelStr(szRet, szCmd, szRet);
		}
		DelStr(szRet, "\r\n", szRet);
		return OPT_SUCCESS;
	}
	return OPT_DEV_NOT_CONNECTED;
}

//************************************
// Method:    FastSendCmd
// FullName:  RemoteBase::FastSendCmd
// Access:    public 
// Returns:   OPT_RET
// Qualifier: 快速发送指令，使用短连接
// Parameter: TCHAR * szCmd
//            发送的指令
// Parameter: int nTimeOut
//            发送超时
// Parameter: bool IsEcho
//            仪器是否使用了原命令回传
//************************************
OPT_RET RemoteBase::FastSendCmd(char* szCmd, int nTimeOut /*= 3000*/, bool IsEcho /*= true*/)
{
	int nTime = 5;
	while (true)
	{
		if (ConnectDev() == OPT_SUCCESS)
		{
			OPT_RET Ret = SendCmd(szCmd, nTimeOut, IsEcho);
			DisconnectDev();
			return Ret;
		}
		nTime--;
		Sleep(1000);
		if (nTime == 0)
			return OPT_DEV_CONNECT_FAIL;
	}
}

//************************************
// Method:    FastQueryStatus
// FullName:  RemoteBase::FastQueryStatus
// Access:    public 
// Returns:   OPT_RET
// Qualifier: 快速查询某项指标状态，使用短链接
// Parameter: TCHAR * szCmd
//            查询命令
// Parameter: TCHAR * szRet
//            返回的结果
// Parameter: int nTimeOut
//            超时时间
// Parameter: bool IsEcho
//            仪器是否使用原命令回传
//************************************
OPT_RET RemoteBase::FastQueryStatus(char* szCmd, char* szRet, int nTimeOut /*= 3000*/, bool IsEcho /*= true*/)
{
	int nTime = 5;
	while (true)
	{
		if (ConnectDev() == OPT_SUCCESS)
		{
			OPT_RET Ret = QueryStatus(szCmd, szRet, nTimeOut, IsEcho);
			DisconnectDev();
			return Ret;
		}
		nTime--;
		Sleep(1000);
		if (nTime == 0)
			return OPT_DEV_CONNECT_FAIL;
	}
}
