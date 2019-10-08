#include "stdafx.h"
#include "Common.h"

CString g_IP;
BOOL g_bIsRunning = false;
volatile bool g_bIsRun =FALSE;
int g_nCount = 0;
CString g_sMed=L"Spectrum";
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
