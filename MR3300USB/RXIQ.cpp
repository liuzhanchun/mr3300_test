#include "StdAfx.h"
#include "RXIQ.h"
#include "RemoteData.h"
#include "UdpServer.h"

CRXIQ *g_pRXIQ = NULL;
int dotIQnum = 0;
CRXIQ::CRXIQ(void)
{
	m_nMeasID = RXIQ;
	char Cmd[150];

	sprintf(Cmd,"FREQuency:MODE sd");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd,"TRACe:MED iq");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "TRAC ON");
	g_pRemote->FastSendCmd(Cmd);

	Ibuf = new double[65536];
	Qbuf = new double[65536];

	m_fp = fopen("test_IQ","wb");
}


CRXIQ::~CRXIQ(void)
{
	char Cmd[50];
	sprintf(Cmd, "TRAC OFF");
	g_pRemote->FastSendCmd(Cmd);

	fclose(m_fp);
	delete []Ibuf;
	delete []Qbuf;

}
void CRXIQ:: ReadData ( void )
{
	UINT nPoint = 0;
	char cBuffer[65536];
	char cIQBuffer[65536];
	short nData[32768];
	int num = 0;
	int IQnum = 0;
	memset(cBuffer, 0, 65536);
	memset(cIQBuffer,0,65536);
	memset(nData, 0, 32768 * sizeof(short));

	g_pIF->ReceiveData(cBuffer, nPoint, 0);
	if (nPoint > 0)
	{
		memcpy(&file_head, &cBuffer[num], sizeof(STRUCT_HEAD_DATA));
		num += sizeof(STRUCT_HEAD_DATA);

		if (file_head.version >= 0)
		{

			memcpy(&generic_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));

			if (generic_data.tag == DATA_TYPE_IQ)
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				memcpy(&IQData, &cBuffer[num], sizeof(STRUCT_IQ_HEAD));

				num += sizeof(STRUCT_IQ_HEAD);
				if (IQData.len>0)
				{
					dotIQnum = generic_data.length - sizeof (STRUCT_GENERIC_DATA)- sizeof (STRUCT_IQ_HEAD);
					//	fwrite(cBuffer,1,generic_data.length,m_fp);  // 带头

					//	memcpy(nData, &cBuffer[num], dotnum); //generic_data.length = sizeof (STRUCT_GENERIC_DATA)+ sizeof (STRUCT_DFIND_IQ)+ len;//data长度
					memcpy(cIQBuffer, &cBuffer[num], dotIQnum); //generic_data.length = sizeof (STRUCT_GENERIC_DATA)+ sizeof (STRUCT_DFIND_IQ)+ len;//data长度
					fwrite(cIQBuffer,1,dotIQnum,m_fp);
					for (int i = 0; i <dotIQnum-7; i += 8)
					{
						Ibuf[IQnum]=(((cIQBuffer[i + 4] <<24)+(cIQBuffer[i + 5]<<16)+(cIQBuffer[i+6]<<8) + (cIQBuffer[i + 7])));//IIIIIIIIII      
						Qbuf[IQnum] =   (((cIQBuffer[i] <<24)+(cIQBuffer[i + 1]<<16)+(cIQBuffer[i+2]<<8) + (cIQBuffer[i + 3])));//QQQQQQQQQQ
						IQnum++;
					}

					for (UINT j = 0; j < IQnum; j++)
					{
						sections.fData[j] = Ibuf[j]/250000.0;
					}
					for (UINT j = IQnum; j < (2*IQnum); j++)
					{
						sections.fData[j] = Qbuf[j-IQnum]/250000.0;
					}

				}

			}
		}

	}



}
int CRXIQ::GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{
	//memset(sections.fData,30,1000);
	int nCount = generic_data.length - sizeof (STRUCT_GENERIC_DATA)- sizeof (STRUCT_IQ_HEAD);
	data =sections.fData;
	nLen = dotIQnum/sizeof(int);

	Status.StartFreq = 0;
	Status.StopFreq =  dotIQnum/sizeof(int);
	Status.total = dotIQnum/sizeof(int);

	freq = dfiqHead.channum; // 通道数
	level = dfiqHead.datatype;//-1代表所有通道一起发送,其他>=0代表通道号
	return 0;
}
int CRXIQ::  GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
	return 0;
}


//IQData