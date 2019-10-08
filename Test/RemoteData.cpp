#include "stdafx.h"
#include "RemoteData.h"
#include "SocketSA.h"
#include "Common.h"

CRemoteData::CRemoteData(char * szIP, int nPort)
	:RemoteBase(szIP, nPort)
{
	m_pByBuf = new BYTE[BUF_SIZE];
	m_pDataTunnel = new CSocketSA();
	m_nTimeOut = 3000;
	//m_OldOutPut = WAVE_NORMAL;
}

CRemoteData::~CRemoteData()
{
	delete m_pByBuf;
	delete m_pDataTunnel;
}
//************************************
// Method:    ConnectDataTunnel
// FullName:  RemoteMulitScan::ConnectDataTunnel
// Access:    public 
// Returns:   OPT_RET
// Qualifier: 连接数据通道
// Parameter: int nTimeOut
//************************************
OPT_RET CRemoteData::ConnectDataTunnel(int nTimeOut /*= 3000*/)
{
	CString szPort;
	int dd = m_nPort;
	szPort.Format(_T("%d"), m_nPort);

	int num = MultiByteToWideChar(0, 0, m_IP, -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, m_IP, -1, wide, num);

	bool IsSucc = m_pDataTunnel->ConnectTo(wide, szPort, PF_INET, SOCK_STREAM, true, 3, 1);
	if (IsSucc)
	{
		return OPT_SUCCESS;
	}
	return OPT_DEV_CONNECT_FAIL;
}

//************************************
// Method:    DisconnectDataTunnel
// FullName:  RemoteMulitScan::DisconnectDataTunnel
// Access:    public 
// Returns:   void
// Qualifier: 断开数据通道
//************************************
void CRemoteData::DisconnectDataTunnel()
{
	m_pDataTunnel->CloseComm();
}


//OPT_RET CRemoteData::ReadData()
//{
//	if (m_pDataTunnel->IsOpen())
//	{
//		char szCmd[50] = { 0 };
//		float fData[100000];
//		sprintf(szCmd, "TRACe?");
//		UINT nRecv = 0;
//		// 接收数据
//		m_pDataTunnel->ReceiveBinary(szCmd, m_pByBuf, nRecv, 10000, BUF_SIZE);
//		if (nRecv > 0)
//		{
//			memcpy(fData, m_pByBuf, nRecv);
//
//			// 波形模式不一样了
//			if (m_Sections.OutPut != m_OldOutPut)
//			{
//				for (int j = 0; j<nRecv; j++)
//					m_Sections.fData[j] = fData[j];
//				m_OldOutPut = m_Sections.OutPut;
//				// 平均次数清空
//				m_Sections.nAvgTimes = 0;
//			}
//			// 如果当前模式是平均模式，开始计算平均次数
//			if (m_Sections.OutPut == WAVE_AVG)
//			{
//				m_Sections.nAvgTimes++;
//			}
//			// 计算当前值
//			if (m_Sections.OutPut == WAVE_NORMAL)
//			{
//				for (int j = 0; j < nRecv; j++)
//				{
//					m_Sections.fData[j] = fData[j];
//				}
//					
//			}
//			else if (m_Sections.OutPut == WAVE_MAX)
//			{
//				// 最大保持
//				for (int j = 0; j < nRecv; j++)
//				{
//					if (fData[j] > m_Sections.fData[j])
//						m_Sections.fData[j] = fData[j];
//				}
//			}
//			else if (m_Sections.OutPut == WAVE_MIN)
//			{
//				// 最小保持
//				for (int j = 0; j < nRecv; j++)
//				{
//					if (fData[j] < m_Sections.fData[j])
//						m_Sections.fData[j] = fData[j];
//				}
//			}
//			else if (m_Sections.OutPut == WAVE_AVG)
//			{
//				// 平均
//				for (int j = 0; j < nRecv; j++)
//				{
//					m_Sections.fData[j] = (m_Sections.nAvgTimes - 1)*m_Sections.fData[j] / m_Sections.nAvgTimes + fData[j] / m_Sections.nAvgTimes;//(m_Sections[i].fData[j] + fData[j]/m_Sections[i].nAvgTimes)/(m_Sections[i].nAvgTimes+1);
//				}
//			
//			}
//			m_Sections.nDataLen = nRecv / sizeof(float);
//		}
//		return OPT_SUCCESS;
//	}
//	return OPT_DEV_NOT_CONNECTED;
//}
//OPT_RET CRemoteData::GetSectDataByIndex(double*& fData, int& nDataLen)
//{
//
//
//	fData = m_Sections.fData;
//	nDataLen = m_Sections.nDataLen;
//	return OPT_SUCCESS;
//}
//
//OPT_RET CRemoteData::GetSectDataByIndex(double* fData, int* nDataLen)
//{
//
//	memcpy(fData, m_Sections.fData, m_Sections.nDataLen*sizeof(double));
//	*nDataLen = m_Sections.nDataLen;
//	return OPT_SUCCESS;
//}

//************************************
// Method:    ConfTraceMode
// FullName:  RemoteMulitScan::ConfTraceMode
// Access:    public 
// Returns:   OPT_RET
// Qualifier:
// Parameter: WAVE_OUTPUT Mode
//            波形输出模式
//************************************
//OPT_RET CRemoteData::ConfTraceMode(int Mode)
//{
//	m_Sections.OutPut = (WAVE_OUTPUT)Mode;
//	return OPT_SUCCESS;
//}
OPT_RET CRemoteData::ReadFreScanParam(double& dStartFreq,double &dStopFreq, double &dStep,CString &sRadioMode, CString &sDetectMode, CString &sMeatime, double &bw, CString &sRXFFMATTMode, int &nRXFFMATT,CString &sql,CString &dwel)
{
	const int MHZ_1 = 1000000;
	const int KHZ_1 = 1000;

	char cBuf[1000] = { 0 };
	char cRecv[1000] = { 0 };
	sprintf(cBuf, "FREQuency:STARt?;FREQuency:Stop?;FREQuency:STEP?;ATTenuation:RF:MODE?;MEASure:DETector?;MEASure:TIME?;BANDwidth?;ATTenuation:AUTomation?;ATTenuation?;MEASure:SQUelch?;MEASure:DWELl?");
	OPT_RET Ret = FastQueryStatus(cBuf, cRecv, 5000);

	if (Ret != OPT_SUCCESS)
		return Ret;

	CStringArray Array;

	int num = MultiByteToWideChar(0, 0, cRecv, -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, cRecv, -1, wide, num);

	CCommon::SplitString(wide, L";", Array);
	dStartFreq = 1.0*_ttoi64(Array[0]) / MHZ_1;
	dStopFreq = 1.0*_ttoi64(Array[1]) / MHZ_1;
	dStep = 1.0*_ttoi64(Array[2]) / KHZ_1;
	sRadioMode = Array[3];
	sDetectMode = Array[4];
	sMeatime = Array[5];
	bw = 1.0*_ttoi64(Array[6]) / KHZ_1;

	sRXFFMATTMode = Array[7];
	nRXFFMATT = _ttof(Array[8]);
	sql = Array[9];
	dwel = Array[10];
	return OPT_SUCCESS;
}

OPT_RET CRemoteData::ConfFreScanParam(double dStartFreq, double dStopFreq, double dStep, CString sRadioMode, CString sDetectMode, CString sMeatime, double bw, CString sRXFFMATTMode, int nRXFFMATT, CString sql, CString dwel)
{
	const INT64 MHZ_1 = 1000000;
	const INT64 KHZ_1 = 1000;
	char cBuf[1000] = { 0 };

	sprintf(cBuf, "FREQuency:STARt %I64d;FREQuency:STOP %I64d;FREQuency:STEP %I64d;ATTenuation:RF:MODE %s;MEASure:DETector %s;MEASure:TIME %s;BANDwidth %I64d;ATTenuation %d;ATTenuation:AUTomation %s;;MEASure:SQUelch %s;MEASure:DWELl %s",
		(INT64)(dStartFreq*MHZ_1), (INT64)(dStopFreq*MHZ_1), (INT64)(dStep*KHZ_1), sRadioMode, sDetectMode, sMeatime, (INT64)(bw*KHZ_1), nRXFFMATT, sRXFFMATTMode, sql, dwel);


	OPT_RET Ret = FastSendCmd(cBuf);
	return Ret;
}// 字符串拆分

OPT_RET CRemoteData::ReadRXFFMParam(CString &med, double &dCenter,double &dSpan,double &dbw,CString &sRadioMode, CString &sRXFFMATTMode, int &nRXFFMATT,CString &sDemo, int &nTHR ,CString &sDetectMode ,__int64 &time, int &xdb,int &beta)
{
	const int MHZ_1 = 1000000;
	const int KHZ_1 = 1000;

	char cBuf[1000] = { 0 };
	char cRecv[1000] = { 0 };
	sprintf(cBuf, "TRAC:MED?;FREQuency?;FREQuency:SPAN?;BANDwidth?;ATTenuation:RF:MODE?;ATTenuation:AUTomation?;ATTenuation?;DEModulation?;MEAS:THR?;MEASure:DETector?;MEASure:TIME?;BANDwidth:XDB?;BANDwidth:BETA?");
	OPT_RET Ret = FastQueryStatus(cBuf, cRecv, 5000);

	if (Ret != OPT_SUCCESS)
		return Ret;

	CStringArray Array;

	int num = MultiByteToWideChar(0, 0, cRecv, -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, cRecv, -1, wide, num);

	CCommon::SplitString(wide, L";", Array);
	med =Array[0];
	dCenter = 1.0*_ttoi64(Array[1]) / MHZ_1;
	dSpan = 1.0*_ttoi64(Array[2]) / KHZ_1;
	dbw = 1.0*_ttoi64(Array[3]) / KHZ_1;
	sRadioMode = Array[4];
	sRXFFMATTMode = Array[5];
	nRXFFMATT =_ttof(Array[6]);
	sDemo = Array[7];
	nTHR= _ttof(Array[8]);
	sDetectMode = Array[9];
	time= _ttoi(Array[10]);
	xdb = _ttof(Array[11]);
	beta= _ttof(Array[12]);
	//dStep = 1.0*_ttoi64(Array[2]) / KHZ_1;
	//sRadioMode = Array[3];
	//sDetectMode = Array[4];
	//sMeatime = Array[5];
	return OPT_SUCCESS;
}

OPT_RET CRemoteData::ConfRXFFMParam(CString med, double dCenter,double dSpan, double dbw, CString sRadioMode, CString sRXFFMATTMode, int nRXFFMATT, CString sDemo,int nTHR,  CString sDetectMode, __int64 time,int xdb,int beta)
{
	const INT64 MHZ_1 = 1000000;
	const INT64 KHZ_1 = 1000;
	char cBuf[1000] = { 0 };

	sprintf(cBuf, "TRAC:MED %s;FREQuency %I64d;FREQuency:SPAN %I64d;BANDwidth %I64d;ATTenuation:RF:MODE %s;ATTenuation %d;ATTenuation:AUTomation %s;DEModulation %s;MEAS:THR %d;MEASure:DETector %s;MEASure:TIME %I64d;BANDwidth:XDB %d;BANDwidth:BETA %d", med, (INT64)(dCenter*MHZ_1), (INT64)(dSpan*KHZ_1), (INT64)(dbw*KHZ_1), sRadioMode, nRXFFMATT, sRXFFMATTMode, sDemo, nTHR, sDetectMode, time, xdb, beta);


	OPT_RET Ret = FastSendCmd(cBuf);
	return Ret;
}// 字符串拆分




//OPT_RET CRemoteData::ReadSegmentParam(double& dCenterFreq, double& dSpan,
//	double& BW, double& dRef, double& Att, int& nSweepPoints)
//{
//	const int MHZ_1 = 1000000;
//	const int KHZ_1 = 1000;
//
//	char cBuf[1000] = { 0 };
//	char cRecv[1000] = { 0 };
//	sprintf(cBuf, "FREQuency:FFM?;FREQuency:SPAN?;BANDwidth?;DISPlay:WINDow:TRACe:Y:RLEVel?;INPut:ATTenuation:STATe?;SWEep:POINts?");
//	OPT_RET Ret = FastQueryStatus(cBuf, cRecv, 5000);
//
//	if (Ret != OPT_SUCCESS)
//		return Ret;
//
//	CStringArray Array;
//	CCommon::SplitString(cRecv, ";", Array);
//	dCenterFreq = 1.0*_ttoi64(Array[0]) / MHZ_1;
//	dSpan = 1.0*_ttoi64(Array[1]) / MHZ_1;
//
//	BW = 1.0*_ttoi(Array[2]) / KHZ_1;
//	dRef = _ttof(Array[3]);
//
//	if (Array[4].CompareNoCase(_T("NORMAL")) == 0)
//	{
//		Att = 0;
//	}
//
//	else if(Array[4].CompareNoCase(_T("LDISTORTION")) == 0)
//	{
//		Att = 1;
//	}
//	else
//	{
//		Att = 2;
//	}
//
//	nSweepPoints = _ttoi(Array[5]);
//
//	return OPT_SUCCESS;
//}
//
////************************************
//// Method:    ConfSegmentPra
//// FullName:  RemoteMulitScan::ConfSegmentPra
//// Access:    public 
//// Returns:   OPT_RET
//// Qualifier: 配置段参数
//// Parameter: int nIndex
////            段号 1-8
//// Parameter: double dStartFreq
////            起始频率
//// Parameter: double dStopFreq
////            终止频率
//// Parameter: double RBW
////            RBW 从960kHz到7.5kHz 2倍数递减
////            960，480，240，120，60，30，15，7.5
//// Parameter: double dRef
////            参考，单位dBuV
//// Parameter: double Att
////            衰减器 0到55，以5步进
//// Parameter: double Ampli
////			  放大器开关
//// Parameter: int nSweepPoints
////            扫描点数
////************************************
//OPT_RET CRemoteData::ConfSegmentParam(double dCenterFreq, double dSpan,
//	double RBW, double dRef, double Att, int nSweepPoints)
//{
//	const INT64 MHZ_1 = 1000000;
//	const INT64 KHZ_1 = 1000;
//	char cBuf[1000] = { 0 };
//	char cAtt[20] = { 0 };
//	if (Att == 0)
//	{
//		sprintf(cBuf, "FREQuency %I64d;FREQuency:SPAN %d;DISPlay:WINDow:TRACe:Y:RLEVel %.1lf;INPut:ATTenuation:STATe NORMAL;SWEep:POINts %d",
//			   (INT64)(dCenterFreq*MHZ_1), (int)dSpan, dRef, nSweepPoints);
//	}
//	if (Att == 1)
//	{
//		sprintf(cBuf, "FREQuency %I64d;FREQuency:SPAN %d;DISPlay:WINDow:TRACe:Y:RLEVel %.1lf;INPut:ATTenuation:STATe LDISTORTION;SWEep:POINts %d",
//			(INT64)(dCenterFreq*MHZ_1), (int)(dSpan), dRef, nSweepPoints);
//	}
//
//	if (Att == 2)
//	{
//		sprintf(cBuf, "FREQuency %I64d;FREQuency:SPAN %d;DISPlay:WINDow:TRACe:Y:RLEVel %.1lf;INPut:ATTenuation:STATe HSENS;SWEep:POINts %d",
//			(INT64)(dCenterFreq*MHZ_1), (int)(dSpan), dRef, nSweepPoints);
//	}
//	OPT_RET Ret = FastSendCmd(cBuf);
//	return Ret;
//}// 字符串拆分
//
//
//
