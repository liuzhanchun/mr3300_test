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
	//strΪ���ָ��CString��splitΪ�ָ���磺�� ?��ո� strGetΪ�����������õ����ַ��������strGet��
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
		//���ʣ�µ��ַ�������û��split�����ʾ��������Ҫ��ô������
		//����Ҳ�������뵽strGet��
		strGet.Add(str);
	}
}
/*//////////////////////////////////////////////////////////////////////////////
Function:       Freq2Str
Description:    Ƶ��ת��Ϊ�ַ���
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

	//gettimeofday (&m_EpochTime, NULL); //��ȡʱ��
	//int t = m_EpochTime.tv_sec;


	////�Զ������ļ�ͷ
	//FILE_HEAD head;
	//head.nFileLen = Length;
	//head.nSaveTime = g_pSys->GetTime();
	//head.cVer = ver;
	//head.ucCRC = 0;


}
// ��HZ��������λ��ת��
// szFreq ת�������ַ���
// nUnit  ��λ���
// lFreq	 �����Ƶ��
double CCommon::Freq22Str( CString& szFreq, int& nUnit, INT64 lFreq, TCHAR* tcFormat )
{
	double dRet = 0.0;
	INT64 freqCmp = _abs64(lFreq);
	if( freqCmp >= 0L && freqCmp < N64_KHz  )		// Hz��
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
	if( freqCmp >= 0L && freqCmp < N64_KHz  )		// Hz��
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
	//�����ɹ�,���õ�hKey,һ��ע�����,�����������ע���  
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
	//�ȶ�ȡ���ݵĳ���  
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTools"), nullptr, &lValue);  
	TCHAR *pBuf = new TCHAR[lValue];  
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTools"), pBuf, &lValue);  

	HKEY hKey = nullptr;  
	DWORD dwTpye = REG_DWORD;  
	DWORD dwValue = sizeof(DWORD);//�����Сһ��Ҫ�������,��������(234)  
	LPDWORD dwData = new DWORD;//һ��Ҫ�����ڴ�,����Ҳ�����
	LONG lRet = 0;  
	int nValue = 500;
	//��ע���  
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTools"),0, KEY_ALL_ACCESS,&hKey);  
	//��ע���                                          //valuename      //����value���� //���ݻ����� //��������С  
	if (ERROR_SUCCESS == (lRet = RegQueryValueEx(hKey, TEXT("MyValue"), 0, &dwTpye, (LPBYTE)dwData, &dwValue)))  
	{  
		nValue = *dwData;
	}  
	delete dwData;
	return nValue ;
}