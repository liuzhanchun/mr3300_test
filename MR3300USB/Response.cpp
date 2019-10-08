#include "StdAfx.h"
#include "Response.h"
#include "RemoteData.h"
#include "UdpServer.h"
#include "Tools.h"

CResponse *g_pRes = NULL;
static int nCount =0;

STRUCT_RESP_LEVEL_DATA testRespLevel;
CResponse::CResponse(void)
{
	m_nMeasID = SYSRESP;

	memset(sections.fData,-100,1000000);
	memset ( &m_MemCorr, 0, sizeof(m_MemCorr) );
	ReadRespFile ( &m_MemCorr );
}


CResponse::~CResponse(void)
{
}

void CResponse::ReadData()
{
	UINT nPoint = 0;
	char cBuffer[65536];
	short nData[32768];
	int num = 0;
	static int OldFieldCount=-1;
	memset(cBuffer, 0, 65536);
	memset(nData, 0, 32768 * sizeof(short));

	g_pData->ReceiveData(cBuffer, nPoint, 0);
	if (nPoint > 0)
	{
		memcpy(&file_head, &cBuffer[num], sizeof(STRUCT_HEAD_DATA));
		num += sizeof(STRUCT_HEAD_DATA);

		if (file_head.version >= 0)
		{

			memcpy(&generic_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));
			if (generic_data.tag == DATA_TYPE_RESP)
			{
				num += sizeof(STRUCT_GENERIC_DATA);

				memcpy(&RespLevel, &cBuffer[num], sizeof(STRUCT_RESP_LEVEL_DATA));
				memcpy(&testRespLevel, &cBuffer[num], sizeof(STRUCT_RESP_LEVEL_DATA));
				
				if (OldFieldCount!=RespLevel.fieldcount)
				{
					for (int i = 0;i<sections.DATA_BUF;i++)
					{
						sections.fData[i] = -9999;  //清空上一场数据	      
					}                          
					OldFieldCount= RespLevel.fieldcount;
				}
				
				sections.fData[RespLevel.ncout] =RespLevel.level/ 10.0;

				if (RespLevel.nRespType == 2)
			//	if ((RespLevel.nRespType == 1)||(RespLevel.nRespType == 2))
				{
					//nCount = ((RespLevel.stopfreq-RespLevel.startfreq)/50000);
					nCount =  RespLevel.DotNumber;
					m_shField[RespLevel.ncout] = RespLevel.level;
					//if (RespLevel.ncout == nCount-1)
					if (RespLevel.ncout == nCount-2)
					{
						//保存数据
						STRUCT_FAST_RESP data;
						memset ( &data, 0, sizeof(data) );
						data.bSuccess = true;
						data.Head.cVer = 2;
						//short mid = m_shField[resp_ns::RESP_DOT_NUM_FAST/2]; //让中间的点变0
						//short shdB[resp_ns::RESP_DOT_NUM_FAST]; //常温的一场数据的ad值
						//for ( int i = 0; i < resp_ns::RESP_DOT_NUM_FAST; i++ )
						//	shdB[i] = m_shField[i] - mid ;

						short mid = m_shField[nCount/2]; //让中间的点变0
						short *shdB = new short[nCount]; //常温的一场数据的ad值

						for ( int i = 0; i < nCount; i++ )
							shdB[i] = m_shField[i] - mid ;


						memcpy ( data.shResp, &shdB[0], sizeof(short) *nCount);
						WriteFastRespFile( &data);
					}				
				}

				else if (RespLevel.nRespType == 1)
					//	if ((RespLevel.nRespType == 1)||(RespLevel.nRespType == 2))
				{
					//nCount = ((RespLevel.stopfreq-RespLevel.startfreq)/50000);
				//	nCount =  RespLevel.DotNumber;
					nCount =50;
					//m_shField[RespLevel.ncout] = RespLevel.level;
					//if (RespLevel.ncout == nCount-1)
					//if (RespLevel.ncout == nCount-2)
					//{
					//	//保存数据
					//	STRUCT_FAST_RESP data;
					//	memset ( &data, 0, sizeof(data) );
					//	data.bSuccess = true;
					//	data.Head.cVer = 2;
					//	//short mid = m_shField[resp_ns::RESP_DOT_NUM_FAST/2]; //让中间的点变0
					//	//short shdB[resp_ns::RESP_DOT_NUM_FAST]; //常温的一场数据的ad值
					//	//for ( int i = 0; i < resp_ns::RESP_DOT_NUM_FAST; i++ )
					//	//	shdB[i] = m_shField[i] - mid ;

					//	short mid = m_shField[nCount/2]; //让中间的点变0
					//	short *shdB = new short[nCount]; //常温的一场数据的ad值

					//	for ( int i = 0; i < nCount; i++ )
					//		shdB[i] = m_shField[i] - mid ;


					//	memcpy ( data.shResp, &shdB[0], sizeof(short) *nCount);
					//	WriteFastRespFile( &data);
					//}				
				}
				else if(RespLevel.nRespType == 0)
				{
					//nCount = ((RespLevel.stopfreq-RespLevel.startfreq)/5000000);	
					nCount = RespLevel.DotNumber;
					m_shField[RespLevel.ncout] = RespLevel.level;
					if (RespLevel.ncout == nCount-2)
					{
						memcpy ( m_MemCorr.shRespData[RespLevel.fieldcount].shRespData, m_shField, sizeof(short) *resp_ns::RESP_DOT_NUM );
						m_MemCorr.shRespData[RespLevel.fieldcount].bRespFinish = true;
						WriteRespFile ( &m_MemCorr );
					}
				}
			}
		}
	}
}
int CResponse:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{
	data = sections.fData;
	nLen = nCount;
//	nLen =0;
//	nLen=RespLevel.DotNumber;
	freq = RespLevel.fieldcount;
	level = RespLevel.ncout ;
	Status.StartFreq = RespLevel.startfreq;
	Status.StopFreq =  RespLevel.stopfreq;
	Status.total = nCount;
//	Status.total = 0;
//	Status.total =RespLevel.DotNumber;

	itu.am=RespLevel.level/ 10.0;
	itu.am_neg =RespLevel.atttype;
	itu.am_pos = RespLevel.att;
	//Status.Ref = 70;
	return 0;
}
int CResponse:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
	//m_pLevel->Lock();
	//data = m_qlevel;
	//nLen = ((trtrt.stopfreq-trtrt.startfreq)/5000000);
	//freq = level_data.freq;
	////level = level_data.level;
	////itu = itu_data;
	////Status.StartFreq = spec_data.freq-spec_data.span/2.0;
	////Status.StopFreq =  spec_data.freq+spec_data.span/2.0;
	////Status.total = spec_data.pt;
	////Status.Ref = 70;
	//m_pLevel->Unlock();
	return 0;
}
bool CResponse::ReadRespFile(STRUCT_RESP *data)
{
	CString strPath = CTools::GetExePath() + _T("\\Response.task");
	if ( PathFileExists(strPath) )
	{
		CFile pFile;
		pFile.Open(strPath,CFile::modeRead|CFile::typeBinary,NULL);
		if(pFile.GetLength()<2)
			return false; 
		pFile.Read(data,sizeof(STRUCT_RESP));
		pFile.Close(); 
		return true;
	}
	return false;
}

void CResponse::WriteRespFile ( STRUCT_RESP *data ) 
{
	CString strPath = CTools::GetExePath() + _T("\\Response.task");
	CFile pFile;
	pFile.Open(strPath, CFile::modeCreate | CFile::modeWrite |CFile::typeBinary , NULL);

	pFile.Write(data,sizeof(STRUCT_RESP));
	pFile .Close();
}
void CResponse::WriteFastRespFile ( const STRUCT_FAST_RESP *data ) 
{

//	CCommon::WriteFileCRC ( "\\FastResponse.task",data, sizeof(STRUCT_FAST_RESP), FILE_VER_RESP );


	CString strPath = CTools::GetExePath() + _T("\\FastResponse.task");
	CFile pFile;
	pFile.Open(strPath, CFile::modeCreate | CFile::modeWrite |CFile::typeBinary , NULL);

	pFile.Write(data,sizeof(STRUCT_FAST_RESP));
	pFile .Close();
}

void CResponse::WriteRespCalFile ( STRUCT_CAL *data ) 
{
	CString strPath = CTools::GetExePath() + _T("\\RespCal.task");
	CFile pFile;
	pFile.Open(strPath, CFile::modeCreate | CFile::modeWrite |CFile::typeBinary , NULL);

	pFile.Write(data,sizeof(STRUCT_CAL));
	pFile .Close();
}
