#pragma once
enum OPT_RET
{
	OPT_UNKNOW_ERROR = -1,		// 未知错误
	OPT_SUCCESS = 0,			// 操作成功执行
	OPT_DEV_CONNECT_FAIL,		// 设备连接失败
	OPT_DEV_NOT_CONNECTED,		// 设备尚未连接
	OPT_SEND_COMMAND_FAIL,		// 发送指令失败
	OPT_RECV_ECHO_TIMEOUT,		// 接收回传超时
	OPT_INDEX_OUT_OF_RANGE,		// 下标越界
	OPT_SAVE_FILE_FALL,
	OPT_USB_DATA_FAIL,
	OPT_USB_POINT_ERROR,
	OPT_RBW_PARA_FAIL,			// RBW参数错误
	OPT_POINT_PARA_FAIL,		// 点数参数错误
	OPT_ATT_PARA_FAIL,			// 衰减器参数错误
};

class CSocketSA;
class RemoteBase
{
public:
	RemoteBase(char* szIP, int nPort);
	virtual ~RemoteBase(void);


public:
	// 连接设备
	OPT_RET ConnectDev();
	// 断开设备连接
	void DisconnectDev();
	// 发送控制指令
	OPT_RET SendCmd(char* szCmd, int nTimeOut = 3000, bool IsEcho = true);
	// 查询状态
	OPT_RET QueryStatus(char* szCmd, char* szRet, int nTimeOut = 3000, bool IsEcho = true);

	// 快速发送控制指令
	// 短连接，每次发送指令前进行连接，发送之后，断开连接
	OPT_RET FastSendCmd(char* szCmd, int nTimeOut = 3000, bool IsEcho = true);
	// 快速查询
	// 短连接，每次发送指令前进行连接，发送之后，断开连接
	OPT_RET FastQueryStatus(char* szCmd, char* szRet, int nTimeOut = 3000, bool IsEcho = true);

	char m_IP[100];
	int m_nPort;
protected:

	CSocketSA* m_pSocket;
};

