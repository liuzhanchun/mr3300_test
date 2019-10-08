#pragma once
#include <time.h>

#pragma pack ( push, 1 )
struct STRUCT_DT_FRAME
{
	__int64 Freq;
	int nCalledNum;//被叫号
	int nCallingNum;//主叫号
	int nColourCode;// 色码
	int type; //type 0--unicode  1--acsii                
	int nLen;
	UCHAR sMSGContent[540];//短信内容512个字
};
struct Config_INI
{
	int nCount;
	__int64 nFreq[20];
	double fAmp[20];
	__int64 nFreqComp[20];
	int nRF_LN;
	int nIF_LN;
	int nRF_NM;
	int nIF_NM;
	int nRF_LD;
	int nIF_LD;
	int nMeasureTime;
};
#pragma pack ( pop )

extern Config_INI ConfigIni;

class CCommon
{
public:
	CCommon();
	virtual ~CCommon();
	static double Freq22Str( CString& szFreq, int& nUnit, INT64 lFreq, TCHAR* tcFormat = _T("%.3lf") );
	static CString GetCurTimeString(CString szFormat);
	static void SplitString(CString str, CString split, CStringArray & strGet);
	static CString Freq2Str(INT64 nFreq, const TCHAR* tcFormat = _T("%.3lf %s"));
	static double FreqtoStr( CString& szFreq, int& nUnit, INT64 lFreq, TCHAR* tcFormat=_T("%.3lf %s") );
	
	static void WriteFileCRC(const char *fileName,const void *buf,INT64 Length,char ver);
	static void WriteRegQueryValue(int nValue);
	static int ReadRegQueryValue();
private:
	static timeval m_EpochTime;    //自1970年1月1日以来的秒数+毫秒
};
extern STRUCT_DT_FRAME g_Mess;
extern volatile bool g_bIsRun;
extern volatile bool g_bIsWave;
extern volatile bool g_bIsMess;
extern volatile bool g_bLevel;
extern bool g_bSpectroView;
extern bool g_bIsSpectroEN;
extern bool g_bSpan;
extern bool g_bDraw;
