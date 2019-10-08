#pragma once
#include "DataDef.h"
#define _SECOND ((ULONGLONG) 10000000)  
#define _MSECOND (_SECOND/1000)
#define _MINUTE (60 * _SECOND)  
#define _HOUR   (60 * _MINUTE)  
#define _DAY    (24 * _HOUR)  

class CTools
{
public:
	CTools(void);
	~CTools(void);

public:
	static double Freq2Str( CString& szFreq, int& nUnit, INT64 lFreq, TCHAR* tcFormat = _T("%.3lf") );
	static CString Time2Str( CString& szTime, int& nUnit, INT64 time, TCHAR* tcFormat = _T("%.1lf") );
	static void PVUnitCalculate( const double &dIn, double &dOut, int iInUnit, int iOutUnit, int iR );

	static int Split( CString str, TCHAR sp, CStringArray& sArray);
	static int Split( CString str, CString sp, CStringArray& sArray);
	static CString GetExePath();
	static HBITMAP CopyScreenToBitmap(LPRECT lpRect);
	static CString LoadString(UINT uID);
	static CString GetFileVer(LPCTSTR lpszFileName = NULL);
	static BOOL RunExec(CString strCmd, DWORD& dwExitCode, BOOL IsWait = FALSE , UINT nWaitTime = INFINITE, UINT IsShowWindow = SW_SHOW);
	static BOOL RunExecEx(CString strCmd, DWORD& dwExitCode, BOOL IsWait, UINT nWaitTime, UINT IsShowWindow, HANDLE& hRead, HANDLE& hWrite);
	static BOOL GetProcessParam(int& argc, LPWSTR* lpszArgv);
	static BOOL IsThreadRunning(CWinThread* pThread);
	static SYSTEMTIME SystemTimeMath(const SYSTEMTIME& tm, ULONGLONG uSub );
	static void FileTimeToTime_t( FILETIME ft, time_t *t );
	static DWORD GetDiffTimes( SYSTEMTIME t1, SYSTEMTIME t2 );
	
};

