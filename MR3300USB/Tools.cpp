#include "StdAfx.h"
#include "Tools.h"


CTools::CTools(void)
{
}


CTools::~CTools(void)
{
}

// dIn  输入
// dOut 转换之后的值
// iInUnit 输入数据的单位
// iOutUnit 输出数据的单位
// iR	电阻
void CTools::PVUnitCalculate( const double &dIn, double &dOut, int iInUnit, int iOutUnit, int iR )
{
	double dOhm = 0.0;

	if( iR == 75 )		// 75 
		dOhm = 18.75061;
	else if( iR == 50 )
		dOhm = 17;
	else
		return;

	if ( iInUnit == iOutUnit || iInUnit > 2 && iOutUnit > 2 )	
	{
		dOut = dIn;
	}

	if ( iInUnit < 3 && iOutUnit < 3 )
	{	
		if ( iInUnit == DBUV_FLAG )
			dOut = dIn - 90 - dOhm;
		else if ( iInUnit == DBMV_FLAG )
			dOut = dIn - 30 - dOhm;
		else if ( iInUnit == DBM_FLAG )
			dOut = dIn;	

		if ( iOutUnit == DBUV_FLAG )
			dOut = dOut + 90 + dOhm;
		else if ( iOutUnit == DBMV_FLAG )
			dOut = dOut + 30 + dOhm;
	}
	else
	{
		if ( iInUnit == DBUV_FLAG )
			dOut = dIn - 90 - dOhm;
		else if ( iInUnit == DBMV_FLAG )
			dOut = dIn - 30 - dOhm;
		else if ( iInUnit == DBM_FLAG )
			dOut = dIn;	
		else if ( iInUnit == NV_FLAG )
			dOut = 20*log10(dIn/(1000.0*1000.0)) - 30 - dOhm;
		else if ( iInUnit == UV_FLAG )
			dOut = 20*log10(dIn/1000.0) - 30 - dOhm;
		else if ( iInUnit == MV_FLAG )
			dOut = 20*log10(dIn) - 30 - dOhm;
		else if( iInUnit == V_FLAG )
			dOut = 20*log10(dIn*1000) - 30 - dOhm;

		if ( iOutUnit == DBUV_FLAG )
			dOut = dOut + 90 + dOhm;
		else if ( iOutUnit == DBMV_FLAG )
			dOut = dOut + 30 + dOhm;
		else if ( iOutUnit == V_FLAG )
			dOut = pow(10., ( dOut + 30 + dOhm ) / 20 )/1000.0;
		else if ( iOutUnit == MV_FLAG )
			dOut = pow(10., ( dOut + 30 + dOhm ) / 20 );
		else if ( iOutUnit == UV_FLAG )
			dOut = pow(10., ( dOut + 30 + dOhm ) / 20 )*1000.0;
		else if ( iOutUnit == NV_FLAG )
			dOut = pow(10., ( dOut + 30 + dOhm ) / 20 )*1000.0*1000.0;
	}
}

// 由HZ到其他单位的转化
// szFreq 转化出的字符串
// nUnit  单位编号
// lFreq	 输入的频率
double CTools::Freq2Str( CString& szFreq, int& nUnit, INT64 lFreq, TCHAR* tcFormat )
{
	double dRet = 0.0;
	INT64 freqCmp = _abs64(lFreq);
	if( freqCmp >= 0L && freqCmp < N64_KHz  )		// Hz级
	{
		szFreq.Format(_T("%lld"), lFreq);
		dRet = (double)lFreq;
		nUnit = 3;
	}
	else if( freqCmp >= N64_KHz && freqCmp < N64_MHz )	// KHz
	{
		dRet = 1.0*lFreq/(double)N64_KHz;
		nUnit = 2;
	}
	else if( freqCmp >= N64_MHz ) // MHz
	{
		dRet = 1.0*lFreq/(double)N64_MHz;
		nUnit = 1;
	}
	//else if( freqCmp >= N64_MHz && freqCmp < N64_GHz ) // MHz
	//{
	//	dRet = 1.0*lFreq/(double)N64_MHz;
	//	nUnit = 1;
	//}
	//else	// GHz
	//{
	//	dRet = 1.0*lFreq/(double)N64_GHz;
	//	nUnit = 0;
	//}

	szFreq.Format(tcFormat, dRet);

	return dRet;
}

CString CTools::Time2Str( CString& szTime, int& nUnit, INT64 time, TCHAR* tcFormat  )
{
	//CString szTime = NULL;
	if( time >= 0L && time < N64_KHz  )		// ns
	{
		szTime.Format(_T("%lld"), time);
		nUnit = 0;
	}
	else if( time >= N64_KHz && time < N64_MHz  )		// us
	{
		szTime.Format(_T("%lld"), time/N64_KHz);
		nUnit = 1;
	}
	else if( time >= N64_MHz && time < N64_GHz )	// ms
	{
		szTime.Format(tcFormat, 1.0*time/(N64_MHz));
		nUnit = 2;
	}
	else																	// s
	{
		szTime.Format(tcFormat, 1.0*time/(N64_GHz));
		nUnit = 3;
	}

	return szTime;
}

int CTools::Split( CString str, TCHAR sp, CStringArray& sArray)
{
	int nLen = str.GetLength(), nLastPos, nPos; 
	bool bContinue; 

	sArray.RemoveAll(); 
	nLastPos=0; 

	do 
	{ 
		bContinue=false; 
		nPos = str.Find(sp, nLastPos); 
		if(-1!=nPos) 
		{ 
			sArray.Add(str.Mid(nLastPos, nPos-nLastPos)); 
			nLastPos=nPos+1; 
			if(nLastPos != nLen)
				bContinue=true; 
		} 
	} while(bContinue); 

	if (nLastPos != nLen) 
		sArray.Add(str.Mid(nLastPos,   nLen-nLastPos)); 

	return sArray.GetSize(); 
}

int CTools::Split( CString str, CString sp, CStringArray& sArray)
{
	int nLen = str.GetLength(), nLastPos, nPos; 
	bool bContinue; 

	sArray.RemoveAll(); 
	nLastPos=0; 

	do 
	{ 
		bContinue=false; 
		nPos = str.Find(sp, nLastPos); 
		if(-1!=nPos) 
		{ 
			sArray.Add(str.Mid(nLastPos, nPos-nLastPos)); 
			nLastPos=nPos+sp.GetLength(); 
			if(nLastPos != nLen)
				bContinue=true; 
		} 
	} while(bContinue); 

	if (nLastPos != nLen) 
		sArray.Add(str.Mid(nLastPos,   nLen-nLastPos)); 

	return sArray.GetSize(); 
}

CString CTools::GetExePath()
{
	CString path; 
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	path.ReleaseBuffer(); 
	int pos = path.ReverseFind('\\'); 
	path = path.Left(pos); 
	return path;
}

HBITMAP CTools::CopyScreenToBitmap(LPRECT lpRect)
{
	HDC        hScrDC, hMemDC; 
	HBITMAP    hBitmap, hOldBitmap;
	int        nX, nY, nX2, nY2;     
	int        nWidth, nHeight;
	int        xScrn, yScrn;

	if (IsRectEmpty(lpRect))
		return NULL;
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	hMemDC = CreateCompatibleDC(hScrDC);
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	if (nX < 0)    nX = 0;
	if (nY < 0)   nY = 0;
	if (nX2 > xScrn)  nX2 = xScrn;
	if (nY2 > yScrn)  nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	BitBlt(hMemDC, 0, 0, nWidth, nHeight,hScrDC, nX, nY, SRCCOPY);
	hBitmap =(HBITMAP)SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	return hBitmap;
}

CString CTools::LoadString( UINT uID )
{
	CString str;
	str.LoadString(uID);
	return str;
}

//CString CTools::GetFileVer(LPCTSTR lpszFileName)
//{
//	CString strVersion;   
//
//	strVersion.Format(_T("%d.%d.%d"), MAIN_VERSION, MAJOR_VESION, MINI_VERSION);
//
//	return strVersion;   
//}

BOOL CTools::RunExec( CString strCmd, DWORD& dwExitCode, BOOL IsWait, UINT nWaitTime, UINT IsShowWindow )
{
	STARTUPINFO si;
	GetStartupInfo(&si);
	si.dwFlags=STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
	si.wShowWindow = IsShowWindow;
	PROCESS_INFORMATION PIAgent;

	BOOL ret = CreateProcess(NULL, strCmd.GetBuffer(0), NULL,NULL,1,0,NULL,NULL, &si,&PIAgent);
	strCmd.ReleaseBuffer();
	if (IsWait) {
		WaitForSingleObject(PIAgent.hProcess,nWaitTime);
		GetExitCodeProcess(PIAgent.hProcess, &dwExitCode);
	}	
	CloseHandle(PIAgent.hProcess);
	return ret;
}

BOOL CTools::RunExecEx(CString strCmd, DWORD& dwExitCode, BOOL IsWait, UINT nWaitTime, UINT IsShowWindow, HANDLE& hRead, HANDLE& hWrite)
{
	STARTUPINFO si;
	GetStartupInfo(&si);
	si.dwFlags=STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
	si.wShowWindow = IsShowWindow;
	si.hStdInput = hRead;
	si.hStdOutput = hWrite;
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	PROCESS_INFORMATION PIAgent;

	BOOL ret = CreateProcess(NULL, strCmd.GetBuffer(0), NULL,NULL,1,0,NULL,NULL, &si,&PIAgent);
	strCmd.ReleaseBuffer();

	if (!ret) {
		CloseHandle(hRead);
		CloseHandle(hWrite);
		hRead = NULL;
		hWrite = NULL;
	}

	if (IsWait) {
		WaitForSingleObject(PIAgent.hProcess,nWaitTime);
		GetExitCodeProcess(PIAgent.hProcess, &dwExitCode);
	}	
	CloseHandle(PIAgent.hProcess);
	return ret;
}

BOOL CTools::GetProcessParam(int& argc, LPWSTR* lpszArgv)
{
	LPTSTR szCmdLine = ::GetCommandLine(); //获取命令行参数；
	lpszArgv = CommandLineToArgvW(szCmdLine, &argc); //拆分命令行参数字符串；
	return TRUE;
}

BOOL CTools::IsThreadRunning(CWinThread* pThread) {
	DWORD dwCode;
	if (pThread == NULL) {
		return FALSE;
	}

	GetExitCodeThread(pThread->m_hThread, &dwCode);
	if(dwCode == STILL_ACTIVE)
	{  
		return TRUE;
	}
	return FALSE;
}

SYSTEMTIME CTools::SystemTimeMath( const SYSTEMTIME& tm, ULONGLONG uSub )
{
	SYSTEMTIME sysTime;
	FILETIME ft={0};   
	SystemTimeToFileTime(&tm, &ft);   

	ULONGLONG qwResult;  
	// Copy the time into a quadword.  
	qwResult = (((ULONGLONG) ft.dwHighDateTime) << 32) + ft.dwLowDateTime;  

	qwResult += uSub;  
	// Copy the result back into the FILETIME structure.  
	ft.dwLowDateTime  = (DWORD) (qwResult & 0xFFFFFFFF );  
	ft.dwHighDateTime = (DWORD) (qwResult >> 32 );  

	FileTimeToSystemTime(&ft, &sysTime);  
	return sysTime;
}

void CTools::FileTimeToTime_t( FILETIME ft, time_t *t ) 
{ 
	LONGLONG ll; 

	ULARGE_INTEGER ui; 
	ui.LowPart = ft.dwLowDateTime; 
	ui.HighPart = ft.dwHighDateTime; 

	ll = ft.dwHighDateTime << 32 + ft.dwLowDateTime; 

	*t = ((LONGLONG)(ui.QuadPart - 116444736000000000)/10000); // / 10000000
} 

DWORD CTools::GetDiffTimes( SYSTEMTIME t1, SYSTEMTIME t2 ) 
{ 
	FILETIME fTime1; 
	FILETIME fTime2; 

	time_t tt1; 
	time_t tt2; 

	SystemTimeToFileTime( &t1, &fTime1 ); 
	SystemTimeToFileTime( &t2, &fTime2 ); 

	FileTimeToTime_t( fTime1, &tt1 ); 
	FileTimeToTime_t( fTime2, &tt2 ); 

	time_t difftime = tt2 - tt1; 

	return difftime;
}