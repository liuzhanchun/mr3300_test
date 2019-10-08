#pragma once
#include "socketinterface.h"

class CSocketSA :
	public CSocketInterface
{
public:
	CSocketSA(void);
	virtual ~CSocketSA(void);

public:
	// ��װ������ ������ȡĳһ������
	BOOL RSCmd (const char* szCmd, DWORD dwTimeout, BYTE send[], BYTE recv[], DWORD& recs );
	BOOL LanSendCmd(const char* szCmd, DWORD dwTimeout, double &dVal );
	BOOL LanSendCmd(const char* szCmd, DWORD dwTimeout, long &lVal );
	BOOL LanSendCmd(const char* szCmd, DWORD dwTimeout, CString &szVal );
	BOOL LanSendCmd(const char* szCmd, DWORD dwTimeout, INT64 &dVal );
	BOOL LanSendCmd( const char* szCmd, DWORD dwTimeout, bool IsEcho );
	BOOL LanSendCmd( const char* szCmd, DWORD dwTimeout, int &iVal, CString szRet[], int iRet );
	BOOL LanSendCmd( const char* szCmd, DWORD dwTimeout, bool &bVal, CString szRet[], int iRet );
	BOOL LanSendCmd( const char* szCmd, DWORD dwTimeout, int &nVal );
	char* strrep(const char* src, const char* from, const char* to);
	BOOL ReceiveBinary( const char* strCmd, BYTE* pBuffer, UINT& nRecv, DWORD dwTimeout = 10000, UINT RecvSize = 10000 );
	BOOL CheckEchoAndType(CString& strType);
};
