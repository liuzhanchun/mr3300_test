#include "StdAfx.h"
#include "RemoteBase.h"
#include "SocketSA.h"

//************************************
// Method:    RemoteBase
// FullName:  RemoteBase::RemoteBase
// Access:    public 
// Returns:   ���캯�� 
// Qualifier:
// Parameter: char * szIP
//            ������ַ
// Parameter: int nPort
//            �����˿�
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
// Qualifier: ����
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
// Qualifier: ��������
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
// Qualifier: �Ͽ�����
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
// Qualifier: ���ַ�����ɾ��ָ�����ַ���
// Parameter: const char * str
//            ԭʼ�ַ����ַ���
// Parameter: const char * sub_str
//            Ҫɾ�����ַ���
// Parameter: char * result
//            ɾ����Ľ��
//************************************
void DelStr(const char *str, const char* sub_str, char *result)
{  
	int sublen = 0;         //����Ӵ��ĳ���
	const char *t = sub_str;
	while(*t++ != '\0')
	{
		sublen++;
	}

	int pos = 0;
	int pp = 0;
	int repos = 0; // ����Ӵ�������
	while(*(str + pos) != '\0')
	{
		char t = *(str + pos);
		if(t == *(sub_str + pp)) // �ظ��Ӵ���ʼλ��
		{
			*(result + repos) = t;
			repos++;

			if(pp < sublen - 1) // ��δ��ȫ�ظ�
			{
				pp++;
			}
			else if(pp == sublen - 1) // ��ȫ�ظ���
			{
				pp = 0;
				repos -= sublen; // �����±�λ��
			}           
		}
		else{ // ����һ�����ַ�
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
// Qualifier: ���Ϳ���ָ��
// Parameter: TCHAR * szCmd
//            ����ָ��
// Parameter: int nTimeOut
//            ���ͳ�ʱʱ�䣬��ʱ��ͬʱ
//            Ҳ��ָ��ͳɹ��Ļض�ʱ��
// Parameter: bool IsEcho
//            �Ƿ�ʹ��ԭ�����
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
// Qualifier: ��ѯ����ĳ��״̬
// Parameter: TCHAR * szCmd
//            ��ѯָ��
// Parameter: TCHAR * szRet
//            ���ص�����
// Parameter: int nTimeOut
//            ��ȡ��ʱʱ��
// Parameter: bool IsEcho
//            �Ƿ���ԭ�����
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
// Qualifier: ���ٷ���ָ�ʹ�ö�����
// Parameter: TCHAR * szCmd
//            ���͵�ָ��
// Parameter: int nTimeOut
//            ���ͳ�ʱ
// Parameter: bool IsEcho
//            �����Ƿ�ʹ����ԭ����ش�
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
// Qualifier: ���ٲ�ѯĳ��ָ��״̬��ʹ�ö�����
// Parameter: TCHAR * szCmd
//            ��ѯ����
// Parameter: TCHAR * szRet
//            ���صĽ��
// Parameter: int nTimeOut
//            ��ʱʱ��
// Parameter: bool IsEcho
//            �����Ƿ�ʹ��ԭ����ش�
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
