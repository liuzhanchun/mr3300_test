#include "StdAfx.h"
#include "RXPSCAN.h"
#include "RemoteData.h"
#include "UdpServer.h"
//int ntestMode=0;
CRXPSCAN *g_pRXPSCAN= NULL; 

	//STRUCT_GENERIC_DATA teswwtgeneric_data;
	//STRUCT_SCAN_HEAD testwwscan_data;
CRXPSCAN::CRXPSCAN(void)
{
	 m_nMeasID = RXPSCAN;

	 char Cmd[50];
	 //sprintf(Cmd, "TRAC OFF");
	 //g_pRemote->FastSendCmd(Cmd);
	 
	 sprintf(Cmd, "FREQ:MODE PSC");
	 g_pRemote->FastSendCmd(Cmd);


	sprintf(Cmd, "FREQ:PSC:MODE Normal");
	// sprintf(Cmd, "FREQ:MODE:PSC ON");
	 g_pRemote->FastSendCmd(Cmd);


	 

	 sprintf(Cmd, "FREQ:START 20 MHz");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "FREQ:STOP 1000 MHz");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "FREQ:STEP 25 kHz");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "BAND 120 kHz");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "ATT:RF:MODE Normal");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "ATT:AUT ON");
	 g_pRemote->FastSendCmd(Cmd);



	 //sprintf(Cmd, "MEAS:TIME:MODE ON");
	 //pRemoteData->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:DET POS");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:DWEL 0");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:HOLD 0");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "TRAC:MED SCAN");
	 g_pRemote->FastSendCmd(Cmd);



	 sprintf(Cmd, "TRAC ON");
	 g_pRemote->FastSendCmd(Cmd);
	 scan_data.total=0;
}


CRXPSCAN::~CRXPSCAN(void)
{
	char Cmd[50];
	sprintf(Cmd, "TRAC OFF");
	g_pRemote->FastSendCmd(Cmd);

}

void CRXPSCAN::ReadData ( void )
{
	UINT nPoint = 0;
	char cBuffer[65536];
	int num = 0;
	int dot_num = 0;
	short *pData = new short[1000000];
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
		//	memcpy(&teswwtgeneric_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));
			
			if (generic_data.tag == DATA_TYPE_SCAN)
			{
				num += sizeof(STRUCT_GENERIC_DATA);

				memcpy(&scan_data, &cBuffer[num], sizeof(STRUCT_SCAN_HEAD));
			//	memcpy(&testwwscan_data, &cBuffer[num], sizeof(STRUCT_SCAN_HEAD));
				
				num += sizeof(STRUCT_SCAN_HEAD);

				dot_num= (generic_data.length- sizeof(STRUCT_GENERIC_DATA) - sizeof(STRUCT_SCAN_HEAD));
				if ((dot_num>0)&&(dot_num<65536)&&(scan_data.pdloc<319200)&&(scan_data.pdpt<65536))
				{
					//CString str;
					//str.Format(_T("pdloc=%d\r\n "),scan_data.pdloc);
					//m_pfile.Write(str.GetBuffer(), str.GetLength()+10);
					//str.ReleaseBuffer();
					//str.Format(_T("pdpt=%d\r\n "),scan_data.pdpt);
					//m_pfile.Write(str.GetBuffer(), str.GetLength()+10);
					//str.ReleaseBuffer();


					memcpy(&pData[scan_data.pdloc], &cBuffer[num], dot_num);

					for (UINT j = scan_data.pdloc; j < (scan_data.pdloc + scan_data.pdpt); j++)
					{
						sections.fData[j] = pData[j]/10.0;
					}


				}

			}

		}
		m_pCSData->Unlock();
	}
	delete pData;
}
int CRXPSCAN:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
{
	m_pCSData->Lock();
	data = sections.fData;
	nLen = scan_data.total;
	//freq = 0;
	//level = 0;
	//itu = itu_data;
	Status.StartFreq = scan_data.start;
	Status.StopFreq =  scan_data.stop;
	Status.total = scan_data.total;
	m_pCSData->Unlock();
	return 0;
}
int CRXPSCAN:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
	return 0;
}

