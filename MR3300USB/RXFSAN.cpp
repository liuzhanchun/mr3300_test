#include "StdAfx.h"
#include "RXFSAN.h"
#include "RemoteData.h"
#include "UdpServer.h"

CRXFSAN *g_pRXFSCAN= NULL; 
//STRUCT_SCAN_HEAD  testscan_data;
CRXFSAN::CRXFSAN(void)
{
	m_nMeasID = RXFSCAN;

	char Cmd[150];
	//sprintf(Cmd, "TRAC OFF");
	//g_pRemote->FastSendCmd(Cmd);



	sprintf(Cmd, "FREQ:START 88 MHz");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "FREQ:STOP 108 MHz");
	g_pRemote->FastSendCmd(Cmd);


	sprintf(Cmd, "FREQ:STEP 25 kHz");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "FREQ:SPAN 500 kHz");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "BAND 120 kHz");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "ATT:RF:MODE Normal");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "ATT:AUT ON");
	g_pRemote->FastSendCmd(Cmd);


	sprintf(Cmd, "DEM FM");
	g_pRemote->FastSendCmd(Cmd);


	sprintf(Cmd, "MEAS:THR -30");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "MEAS:HOLD 500");
	//sprintf(Cmd, "MEAS:HOLD 20ms");
	g_pRemote->FastSendCmd(Cmd);

	//sprintf(Cmd, "MEAS:DWELl 500");
	//g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "MEAS:TIME:MODE ON");
//	sprintf(Cmd, "MEAS:TIME 20ms");
	g_pRemote->FastSendCmd(Cmd);

	//sprintf(Cmd, "FREQ:MODE:SWEep ON");
	//pRemoteData->FastSendCmd(Cmd);



	sprintf(Cmd, "MEAS:DET POS");
	g_pRemote->FastSendCmd(Cmd);


	sprintf(Cmd, "MEAS:BAND:XDB 26");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "MEAS:BAND:BETA 0.01");
	g_pRemote->FastSendCmd(Cmd);



	sprintf(Cmd, "MEASure:SQUelch ON");
	g_pRemote->FastSendCmd(Cmd);



	sprintf(Cmd, "FREQ:MODE SWEep");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "TRAC:MED SPECTRUM,SCAN");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "MEAS:DWELl 1ms");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "TRAC ON");
	g_pRemote->FastSendCmd(Cmd);
	spec_data.pt = 0;
	scan_data.total = 0;
}


CRXFSAN::~CRXFSAN(void)
{
	char Cmd[50];
	sprintf(Cmd, "TRAC OFF");
	g_pRemote->FastSendCmd(Cmd);
}
void CRXFSAN::ReadData ( void )
{
	UINT nPoint = 0;
	char cBuffer[65536];
	short nData[32768];
	int num = 0;

	int dot_num = 0;
	short *pData = new short[1000000];

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

				//if (m_qlevel.size()<500)
				//{
				//	m_qlevel.push(level_data.level);
				//}
				//else
				//{
				//	m_qlevel.pop();
				//	m_qlevel.push(level_data.level);

				//}

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
			if (generic_data.tag == DATA_TYPE_FSCAN)
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				//memcpy(&testscan_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));
				memcpy(&scan_data, &cBuffer[num], sizeof(STRUCT_SCAN_HEAD));
				num += sizeof(STRUCT_SCAN_HEAD);
				dot_num= (generic_data.length- sizeof(STRUCT_GENERIC_DATA) - sizeof(STRUCT_SCAN_HEAD));
				if (dot_num>0)
				{

					memcpy(&pData[scan_data.pdloc], &cBuffer[num], dot_num);

					m_pLevel->Lock();
					if (!m_qlevel.empty())
					{
						clear(m_qlevel);
					}

					if (scan_data.pdpt==1)
					{
						m_qlevel.push((pData[scan_data.pdloc]/10.0));
					}

					m_pLevel->Unlock();
					
					for (UINT j = scan_data.pdloc; j < (scan_data.pdloc + scan_data.pdpt); j++)
					{
						levelsections.fData[j] = pData[j]/10.0;
					}

				}
				
			}
		}
		m_pCSData->Unlock();
	}

	delete pData;
}
int CRXFSAN:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{
	m_pCSData->Lock();
	data = sections.fData;
	//nLen = scan_data.total;

	nLen = spec_data.pt;
	freq = level_data.freq;
	level = level_data.level;
	itu = itu_data;
	Status.StartFreq = spec_data.freq-spec_data.span/2.0;
	Status.StopFreq =  spec_data.freq+spec_data.span/2.0;
	Status.total = spec_data.pt;
		m_pCSData->Unlock();
	//freq = 0;
	//level = 0;
	//itu = itu_data;
	//Status.StartFreq = scan_data.start;
	//Status.StopFreq =  scan_data.stop;
	//Status.total = scan_data.total;
	return 0;
}
int CRXFSAN:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
	
	//data = m_qlevel;

	m_pLevel->Lock();
	data = m_qlevel;
	if (scan_data.pdpt==1)
	{
		freq = scan_data.start+scan_data.step*scan_data.pdloc;

	} 
	else
	{
		freq=0;
	}

	m_pLevel->Unlock();

	leveldata = levelsections.fData;
	nLen = scan_data.total;

//	nLen = m_qlevel.size();

	return 0;
}