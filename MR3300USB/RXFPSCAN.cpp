#include "StdAfx.h"
#include "RXFPSCAN.h"
#include "RemoteData.h"
#include "UdpServer.h"

CRXFPSCAN *g_pRXFPSCAN= NULL; 
//__int64 nDotlen;
STRUCT_SCAN_HEAD_FAST tfscan_data ;
STRUCT_PSCAN_DATA tfscan_lev;
double g_nFPSCAN[800];
CRXFPSCAN::CRXFPSCAN(void)
{
	m_nMeasID = RXFPSCAN;

	char Cmd[50];

	sprintf(Cmd, "ATT:RF:MODE Normal");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "ATT:AUT ON");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "ATT:RF 0 dB");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "ATT:IF 0 dB");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "MEAS:TIME:AUT OFF");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "MEAS:TIME 0.5 ms");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "MEAS:DET POS");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "MEAS:SQU ON");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "FREQ:MODE PSC");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "FREQ:PSC:MODE FAST");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "FREQ:START 20 MHz");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "FREQ:STOP 8000 MHz");
	g_pRemote->FastSendCmd(Cmd);

		g_pRemote->FastSendCmd("MEASure:DETector AVG");

	sprintf(Cmd, "FREQ:STEP 25 kHz");
	g_pRemote->FastSendCmd(Cmd);

	//sprintf(Cmd, "MEAS:DWEL 0");
	//g_pRemote->FastSendCmd(Cmd);

	//sprintf(Cmd, "MEAS:HOLD 0");
	//g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "TRAC:MED SCAN");
	g_pRemote->FastSendCmd(Cmd);

	sprintf(Cmd, "TRAC ON");
	g_pRemote->FastSendCmd(Cmd);
	fscan_data.pdpt=0;

//	nDotlen = 0;
}


CRXFPSCAN::~CRXFPSCAN(void)
{
	char Cmd[50];
	sprintf(Cmd, "TRAC OFF");
	g_pRemote->FastSendCmd(Cmd);
}
void CRXFPSCAN::ReadData ( void )
{
	UINT nPoint = 0;
	char cBuffer[65536];
	int num = 0;
//	static UINT uyuy=0;
	memset(cBuffer, 0, 65536);

	g_pData->ReceiveData(cBuffer, nPoint, 0);

	if (nPoint > 0)
	{
		m_pCSData->Lock();
		memcpy(&file_head, &cBuffer[num], sizeof(STRUCT_HEAD_DATA));
		num += sizeof(STRUCT_HEAD_DATA);

		if (file_head.version >= 0)
		{
			memcpy(&generic_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));

			if (generic_data.tag == DATA_TYPE_SCAN)
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				
				memcpy(&tfscan_data, &cBuffer[num], sizeof(STRUCT_SCAN_HEAD_FAST));/////
				memcpy(&fscan_data, &cBuffer[num], sizeof(STRUCT_SCAN_HEAD_FAST));
				num += sizeof(STRUCT_SCAN_HEAD_FAST);
				if ((fscan_data.pdpt>0)&&(fscan_data.pdpt<1000))
				{

					memcpy(&fscan_lev, &cBuffer[num], sizeof(STRUCT_PSCAN_DATA));
					memcpy(&tfscan_lev, &cBuffer[num], sizeof(STRUCT_PSCAN_DATA));//////
					num += sizeof(STRUCT_PSCAN_DATA);
					//nDotlen = (fscan_data.stop-fscan_data.start)/25000;


					////__int64 ndotlen=(fscan_data.stop-fscan_data.start)/25000;
					//srand((int)time(0));
					//for (UINT j = 0; j < nDotlen; j++)
					//{
					//	int test = rand_X(10);
					//	if ((test>5)&&(test<9))
					//	{
					//		test = 4;
					//	}
					//	
					//	 sections.fData[j] =test-8;
					//}
	
					for (UINT j = 0; j < fscan_data.pdpt; j++)
					{
						//sections.fData[fscan_lev.NNumber[j]] = fscan_lev.Lev[j]/10.0;
						sections.fData[j] = fscan_lev.Lev[j]/10.0;
						g_nFPSCAN[j] =  fscan_lev.NNumber[j]*fscan_data.step+20000000;
					}
				}
			}
		}
		m_pCSData->Unlock();
	}
}
int CRXFPSCAN:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{
	//nLen =0;
	m_pCSData->Lock();
	data = sections.fData;
	//__int64 ndotlen=(fscan_data.stop-fscan_data.start)/25000;
	nLen =fscan_data.pdpt;//ndotlen;
	//nLen = nDotlen;
	//freq = 0;
	//level = 0;
	//itu = itu_data;
	Status.StartFreq = fscan_data.start;
	Status.StopFreq =  fscan_data.stop;
	Status.total = fscan_data.pdpt;//ndotlen; nDotlen; 
	m_pCSData->Unlock();
	return 0;
}
int CRXFPSCAN:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
	return 0;
}

int CRXFPSCAN::rand_X(int x)
{

	return rand()%x;
}