#include "StdAfx.h"
#include "RXFFM.h"
#include "RemoteData.h"
#include "UdpServer.h"
CRXFFM *g_pRXFFM= NULL;
CRXFFM::CRXFFM(void)
{
	 m_nMeasID = RXFFM;

	 if (!m_qlevel.empty())
	 {
		 clear(m_qlevel);
	 }
	 
	 char Cmd[150];

	 sprintf(Cmd, "FREQ 106.8 MHz");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "FREQ:SPAN 80000 kHz");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "BAND 250 kHz");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "ATT:RF:MODE LowDistort");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "ATT:AUT OFF");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "DEM FM");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:THR 90");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "ATTenuation:RF %d",(int)(ConfigIni.nRF_LD));
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "ATTenuation:IF %d",(int)(ConfigIni.nIF_LD));
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:TIME %d ms",(int)(ConfigIni.nMeasureTime));
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:DET AVG");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:BAND:XDB 26");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:BAND:BETA 0.01");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:SQUelch OFF");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "FREQ:MODE FIX");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "TRAC:MED SPECTRUM,Level");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "TRAC ON");
	 g_pRemote->FastSendCmd(Cmd);

	 spec_data.pt=0;
	 clear(m_qlevel);
}


CRXFFM::~CRXFFM(void)
{

	char Cmd[50];
	sprintf(Cmd, "TRAC OFF");
	g_pRemote->FastSendCmd(Cmd);
}
void CRXFFM::ReadData ( void )
{
	UINT nPoint = 0;
	char cBuffer[65536];
	short nData[32768];
	int num = 0;
	memset(cBuffer, 0, 65536);
	memset(nData, 0, 32768 * sizeof(short));

	g_pData->ReceiveData(cBuffer, nPoint, 0);

	

	if (nPoint > 0)
	{
		m_pCSData->Lock();
		memcpy(&file_head, &cBuffer[num], sizeof(STRUCT_HEAD_DATA));
		num += sizeof(STRUCT_HEAD_DATA);

		if (file_head.version >= 0)
		{
		
			memcpy(&generic_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));
			if (generic_data.tag == DATA_TYPE_LEVEL)
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				memcpy(&level_data, &cBuffer[num], sizeof(STRUCT_LEVEL_DATA));
				num += sizeof(STRUCT_LEVEL_DATA);
				m_pLevel->Lock();
				if (m_qlevel.size()<LevelDot)
				{
					m_qlevel.push(level_data.level);
				}
				else
				{
					m_qlevel.pop();
					m_qlevel.push(level_data.level);

				}
				m_pLevel->Unlock();

			}
			memcpy(&generic_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));
			if (generic_data.tag == DATA_TYPE_SPECTRUM)
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				memcpy(&spec_data, &cBuffer[num], sizeof(STRUCT_SPECTRUM_HEAD));
				num += sizeof(STRUCT_SPECTRUM_HEAD);
				if (spec_data.pt>0)
				{
					memcpy(nData, &cBuffer[num], spec_data.pt*sizeof(short));
					num += spec_data.pt * sizeof(short);

					for (UINT j = 0; j < spec_data.pt; j++)
					{
						sections.fData[j] = nData[j]/ 10.0;
					}
				}

			}
			memcpy(&generic_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));
			if (generic_data.tag == DATA_TYPE_ITU)
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				memcpy(&itu_data, &cBuffer[num], sizeof(STRUCT_ITU_DATA));
				num += sizeof(STRUCT_ITU_DATA);
			}
			memcpy(&generic_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));

			if ((generic_data.tag == DATA_TYPE_MESS)||(generic_data.tag==512))
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				memcpy(&g_Mess, &cBuffer[num], sizeof(STRUCT_DT_FRAME));
				num += sizeof(STRUCT_DT_FRAME);
				g_bIsMess =TRUE;
			}
		}	
		m_pCSData->Unlock();
	}

}
int CRXFFM:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{
	m_pCSData->Lock();
	data = sections.fData;
	nLen = spec_data.pt;
	freq = level_data.freq;
	level = level_data.level;
	itu = itu_data;
	Status.StartFreq = spec_data.freq-spec_data.span/2.0;
	Status.StopFreq =  spec_data.freq+spec_data.span/2.0;
	Status.total = spec_data.pt;
	m_pCSData->Unlock();
	//Status.Ref = 70;
	return 0;
}
int CRXFFM:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{

	
	m_pLevel->Lock();

	if (g_bLevel == FALSE)
	{
		clear(m_qlevel);
	}
	data = m_qlevel;
	nLen = m_qlevel.size();
	freq = level_data.freq;
	//level = level_data.level;
	//itu = itu_data;
	//Status.StartFreq = spec_data.freq-spec_data.span/2.0;
	//Status.StopFreq =  spec_data.freq+spec_data.span/2.0;
	//Status.total = spec_data.pt;
	//Status.Ref = 70;
	m_pLevel->Unlock();
	return 0;
}