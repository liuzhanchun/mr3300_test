#include "StdAfx.h"
#include "Common.h"
#include <windows.h>

Config_INI ConfigIni;
volatile bool g_bIsRun =FALSE;
volatile bool g_bIsWave =FALSE;
volatile bool g_bIsMess =FALSE;
STRUCT_DT_FRAME g_Mess;
volatile bool g_bLevel = TRUE;
bool g_bSpectroView = false;
bool g_bIsSpectroEN = false;
bool g_bSpan = false;
bool g_bDraw = false;
CCommon::CCommon()
{
}
CCommon::~CCommon()
{
}
CString CCommon::GetCurTimeString(CString szFormat)
{
	time_t t = time(0);
	char tmp[64];

	int num1 = WideCharToMultiByte(CP_OEMCP, NULL, szFormat, -1, NULL, 0, NULL, FALSE);
	char *pchar = new char[num1];
	WideCharToMultiByte(CP_OEMCP, NULL, szFormat, -1, pchar, num1, NULL, FALSE);

	strftime(tmp, sizeof(tmp), pchar, localtime(&t));
	return CString(tmp);
}
void CCommon::SplitString(CString str, CString split, CStringArray& strGet)
{
	//str为待分割的CString，split为分割符如：， ?或空格 strGet为输出参数，你得到的字符串存放在strGet中
	int pos = -1;
	pos = str.Find(split);
	while (pos != -1)
	{
		CString strSun = _T("");
		strSun = str.Left(pos);
		strGet.Add(strSun);
		str.Delete(0, pos + split.GetLength());
		pos = str.Find(split);
	}
	if (str != "")
	{
		//最后剩下的字符串可能没有split这个标示，看你需要怎么处理了
		//这里也把他加入到strGet中
		strGet.Add(str);
	}
}
/*//////////////////////////////////////////////////////////////////////////////
Function:       Freq2Str
Description:    频率转化为字符串
Calls:          ---
Called By:      ---
Param:
INT64 nFreq :
TCHAR tcFormat :
Return:
CString
Access:         public
//////////////////////////////////////////////////////////////////////////////*/
CString CCommon::Freq2Str(INT64 nFreq, const TCHAR* tcFormat)
{
	CString str;
	CString strUnit;
	double dDiv = 0.0;
	if (abs(nFreq) >= GHZ_1)
	{
		strUnit = _T("GHz");
		dDiv = GHZ_1*1.0;
	}
	else if ((abs(nFreq) < GHZ_1) && (abs(nFreq) >= MHZ_1))
	{
		strUnit = _T("MHz");
		dDiv = MHZ_1*1.0;
	}
	else if ((abs(nFreq) < MHZ_1) && (abs(nFreq) >= KHZ_1))
	{
		strUnit = _T("KHz");
		dDiv = KHZ_1*1.0;
	}
	else {
		strUnit = _T("Hz");
		dDiv = HZ_1*1.0;
	}

	str.Format(tcFormat, nFreq / dDiv, strUnit);
	return str;
}
void CCommon::WriteFileCRC(const char *fileName,const void *buf,INT64 Length,char ver)
{

	//gettimeofday (&m_EpochTime, NULL); //读取时间
	//int t = m_EpochTime.tv_sec;


	////自动生成文件头
	//FILE_HEAD head;
	//head.nFileLen = Length;
	//head.nSaveTime = g_pSys->GetTime();
	//head.cVer = ver;
	//head.ucCRC = 0;


}
// 由HZ到其他单位的转化
// szFreq 转化出的字符串
// nUnit  单位编号
// lFreq	 输入的频率
double CCommon::Freq22Str( CString& szFreq, int& nUnit, INT64 lFreq, TCHAR* tcFormat )
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
double CCommon::FreqtoStr( CString& szFreq, int& nUnit, INT64 lFreq, TCHAR* tcFormat )
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

void CCommon::WriteRegQueryValue(int nValue)
{
	HKEY hKey = nullptr;  
	//创建成功,将得到hKey,一个注册表句柄,用于下面操作注册表  
	if (ERROR_SUCCESS != RegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTools"), &hKey))  
	{   
		goto end;
	}
	if (ERROR_SUCCESS != RegSetValue(hKey,nullptr,REG_SZ,TEXT("Test"),4))
	{
		goto end;
	}

	if (hKey ==nullptr)  
	{  
		goto end;  
	}  
	LONG lRet = 0;  
	DWORD  MyValue = nValue;

	if (ERROR_SUCCESS != (lRet = RegSetValueEx(hKey, TEXT("MyValue"), 0, REG_DWORD,(LPBYTE)&MyValue,sizeof(DWORD))))  
	{  
		goto end;  
	}  
	RegCloseKey(hKey);  
end:
	;
}
int CCommon::ReadRegQueryValue()
{


	LONG lValue = 0;  
	//先读取数据的长度  
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTools"), nullptr, &lValue);  
	TCHAR *pBuf = new TCHAR[lValue];  
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTools"), pBuf, &lValue);  

	HKEY hKey = nullptr;  
	DWORD dwTpye = REG_DWORD;  
	DWORD dwValue = sizeof(DWORD);//这个大小一定要先求出来,否则会出错(234)  
	LPDWORD dwData = new DWORD;//一定要分配内存,否则也会出错
	LONG lRet = 0;  
	int nValue = 500;
	//打开注册表  
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTools"),0, KEY_ALL_ACCESS,&hKey);  
	//读注册表                                          //valuename      //返回value类型 //数据缓存区 //缓存区大小  
	if (ERROR_SUCCESS == (lRet = RegQueryValueEx(hKey, TEXT("MyValue"), 0, &dwTpye, (LPBYTE)dwData, &dwValue)))  
	{  
		nValue = *dwData;
	}  
	delete dwData;
	return nValue ;
}