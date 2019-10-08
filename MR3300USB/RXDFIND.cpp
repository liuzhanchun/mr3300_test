#include "StdAfx.h"
#include "RXDFIND.h"
#include "RemoteData.h"
#include "UdpServer.h"

CRXDFIND *g_pRXDFIND = NULL;
STRUCT_DFIND_IQ testdfiqHead;
STRUCT_GENERIC_DATA testgeneric_data;
int dotnum = 0;

CRXDFIND::CRXDFIND(void)
{
	m_nMeasID = RXDFIND;

	char Cmd[150];

	sprintf(Cmd,"FREQuency:MODE DFINd");
	g_pRemote->FastSendCmd(Cmd);

	CString csAnt;
	CString csAntPara;
	int nCount = 0;
	m_IniFile.SetFileName(L"antenna.ini");
	CString csCount=m_IniFile.GetString(L"Antenna",L"count",L"");
	int num1 = WideCharToMultiByte(CP_OEMCP, NULL,csCount, -1, NULL, 0, NULL, FALSE);
	char *pchar = new char[num1];
	WideCharToMultiByte(CP_OEMCP, NULL, csCount, -1, pchar, num1, NULL, FALSE);
	nCount=atoi(pchar);
	delete []pchar;

	sprintf(Cmd,"ANT:COUNt %d",nCount);
	g_pRemote->FastSendCmd(Cmd);

	for (int i=0;i<nCount;i++)
	{
		csAnt.Format(L"Antenna%d",i+1);
		csAntPara= m_IniFile.GetString(L"Antenna",csAnt,L"");
		int num1 = WideCharToMultiByte(CP_OEMCP, NULL,csAntPara, -1, NULL, 0, NULL, FALSE);
		char *pchar = new char[num1];
		WideCharToMultiByte(CP_OEMCP, NULL, csAntPara, -1, pchar, num1, NULL, FALSE);
		g_pRemote->FastSendCmd(pchar);
		delete []pchar;
	}

	sprintf(Cmd,"ANT:SEL:IND 2");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd,"MEASure:DFINd:MODE NORMal");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd,"MEASure:DFINd:THR 30");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd,"MEASure:DFINd:INTerval 10us");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd,"MEASure:DFINd:SWItch 10us");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd,"MEASure:DFINd:COUNT 1024");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "TRAC ON");
	g_pRemote->FastSendCmd(Cmd);

	Ibuf = new double[65536];
	Qbuf = new double[65536];

	m_fp = fopen("test_DF","wb");
}


CRXDFIND::~CRXDFIND(void)
{
	char Cmd[50];
	sprintf(Cmd, "TRAC OFF");
	g_pRemote->FastSendCmd(Cmd);
	fclose(m_fp);
	delete []Ibuf;
	delete []Qbuf;
}
void CRXDFIND::ReadData ( void )
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
			memcpy(&testgeneric_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));
			
			if (generic_data.tag == DATA_TYPE_DFIQ)
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				memcpy(&dfiqHead, &cBuffer[num], sizeof(STRUCT_DFIND_IQ));
				memcpy(&testdfiqHead, &cBuffer[num], sizeof(STRUCT_DFIND_IQ));
				
				num += sizeof(STRUCT_DFIND_IQ);
				if (dfiqHead.dotnum>0)
				{
					dotnum = generic_data.length - sizeof (STRUCT_GENERIC_DATA)- sizeof (STRUCT_DFIND_IQ);
				//	fwrite(cBuffer,1,generic_data.length,m_fp);
					
				//	memcpy(nData, &cBuffer[num], dotnum); //generic_data.length = sizeof (STRUCT_GENERIC_DATA)+ sizeof (STRUCT_DFIND_IQ)+ len;//data长度
				memcpy(cIQBuffer, &cBuffer[num], dotnum); //generic_data.length = sizeof (STRUCT_GENERIC_DATA)+ sizeof (STRUCT_DFIND_IQ)+ len;//data长度
				fwrite(cIQBuffer,1,dotnum,m_fp);
					for (int i = 0; i <dotnum-7; i += 8)
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

int CRXDFIND:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{
	//memset(sections.fData,30,1000);
	int nCount = generic_data.length - sizeof (STRUCT_GENERIC_DATA)- sizeof (STRUCT_DFIND_IQ);
	data =sections.fData;
	nLen = dotnum/sizeof(int);

	Status.StartFreq = 0;
	Status.StopFreq =  dotnum/sizeof(int);
	Status.total = dotnum/sizeof(int);

	freq = dfiqHead.channum; // 通道数
	level = dfiqHead.datatype;//-1代表所有通道一起发送,其他>=0代表通道号
	return 0;
}
int CRXDFIND:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
	return 0;
}
