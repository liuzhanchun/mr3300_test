#pragma once
#include "RemoteBase.h"


class CRemoteData: public RemoteBase
{
public:
	CRemoteData(char* szIP, int nPort);
	~CRemoteData();
	OPT_RET ConnectDataTunnel(int nTimeOut);
	void DisconnectDataTunnel();
//	OPT_RET ReadData();
//	OPT_RET GetSectDataByIndex(double*& fData, int& nDataLen);
//	OPT_RET GetSectDataByIndex(double * fData, int * nDataLen);
//	OPT_RET ConfTraceMode(int Mode);
	OPT_RET ReadFreScanParam(double & dStartFreq ,double &dStopFreq, double &dStep,CString &sRadioMode, CString &sDetectMode, CString &sMeatime, double &bw, CString &sRXFFMATTMode, int &nRXFFMATT, CString &sql, CString &dwel);
	OPT_RET ConfFreScanParam(double dStartFreq ,double dStopFreq, double dStep, CString sRadioMode, CString sDetectMode, CString sMeatime,double bw, CString sRXFFMATTMode, int nRXFFMATT,  CString sql, CString dwel);
	OPT_RET ReadRXFFMParam(CString &med, double &dCenter, double &dSpan, double &dbw, CString &sRadioMode, CString &sRXFFMATTMode, int &nRXFFMATT, CString &sDemo, int &nTHR, CString &sDetectMode, __int64 &time, int &xdb, int &beta);
	OPT_RET ConfRXFFMParam(CString med, double dCenter, double dSpan, double dbw, CString sRadioMode, CString sRXFFMATTMode, int nRXFFMATT, CString sDemo, int nTHR, CString sDetectMode, __int64 time, int xdb, int beta);
	//OPT_RET ReadSegmentParam(double& dCenterFreq, double& dSpan, double & BW, double & dRef, double & Att,int & nSweepPoints);
	//OPT_RET ConfSegmentParam(double dCenterFreq, double dSpan, double BW, double dRef, double Att,int nSweepPoints);
public:
	//// 波形显示标识
	//enum WAVE_OUTPUT
	//{
	//	WAVE_NORMAL = 0,
	//	WAVE_MAX = 4,
	//	WAVE_MIN = 5,
	//	WAVE_AVG = 2
	//};

	//struct Section
	//{
	//	// 无效标识符
	//	static const int NA = -20000;

	//	// 数据缓冲区大小
	//	static const int DATA_BUF = 100000;

	//	// 数据区有效数据长度
	//	int nDataLen;

	//	// 波形输出类型,最大保持，最小保持，平均等
	//	WAVE_OUTPUT OutPut;

	//	// 数据区指针
	//	double* fData;

	//	// 平均次数计数
	//	long long nAvgTimes;

	//	Section()
	//	{
	//		OutPut = WAVE_NORMAL;
	//		nDataLen = 0;
	//		nAvgTimes = 0;
	//		fData = new double[DATA_BUF];
	//	}

	//	~Section()
	//	{
	//		delete[] fData;
	//	}
	//};
protected:
	static const int BUF_SIZE = 32 + 10000 * 4;
	unsigned char* m_pByBuf;
	CSocketSA* m_pDataTunnel;
	int m_nTimeOut;
	//int m_SectionInfo;
	//Section m_Sections;
//	WAVE_OUTPUT m_OldOutPut;
};

extern CRemoteData *g_pRemote;
