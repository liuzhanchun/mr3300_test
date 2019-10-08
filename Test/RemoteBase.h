#pragma once
enum OPT_RET
{
	OPT_UNKNOW_ERROR = -1,		// δ֪����
	OPT_SUCCESS = 0,			// �����ɹ�ִ��
	OPT_DEV_CONNECT_FAIL,		// �豸����ʧ��
	OPT_DEV_NOT_CONNECTED,		// �豸��δ����
	OPT_SEND_COMMAND_FAIL,		// ����ָ��ʧ��
	OPT_RECV_ECHO_TIMEOUT,		// ���ջش���ʱ
	OPT_INDEX_OUT_OF_RANGE,		// �±�Խ��
	OPT_SAVE_FILE_FALL,
	OPT_USB_DATA_FAIL,
	OPT_USB_POINT_ERROR,
	OPT_RBW_PARA_FAIL,			// RBW��������
	OPT_POINT_PARA_FAIL,		// ������������
	OPT_ATT_PARA_FAIL,			// ˥������������
};

class CSocketSA;
class RemoteBase
{
public:
	RemoteBase(char* szIP, int nPort);
	virtual ~RemoteBase(void);


public:
	// �����豸
	OPT_RET ConnectDev();
	// �Ͽ��豸����
	void DisconnectDev();
	// ���Ϳ���ָ��
	OPT_RET SendCmd(char* szCmd, int nTimeOut = 3000, bool IsEcho = true);
	// ��ѯ״̬
	OPT_RET QueryStatus(char* szCmd, char* szRet, int nTimeOut = 3000, bool IsEcho = true);

	// ���ٷ��Ϳ���ָ��
	// �����ӣ�ÿ�η���ָ��ǰ�������ӣ�����֮�󣬶Ͽ�����
	OPT_RET FastSendCmd(char* szCmd, int nTimeOut = 3000, bool IsEcho = true);
	// ���ٲ�ѯ
	// �����ӣ�ÿ�η���ָ��ǰ�������ӣ�����֮�󣬶Ͽ�����
	OPT_RET FastQueryStatus(char* szCmd, char* szRet, int nTimeOut = 3000, bool IsEcho = true);

	char m_IP[100];
	int m_nPort;
protected:

	CSocketSA* m_pSocket;
};

