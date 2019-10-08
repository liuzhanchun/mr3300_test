#include "StdAfx.h"
#include "RXMSCAN.h"
#include "RemoteData.h"
#include "UdpServer.h"


CRXMSCAN *g_pRXMSCAN= NULL;
CRXMSCAN::CRXMSCAN(void)
{
	 m_nMeasID = RXMSCAN;
	 char Cmd[500];

	 sprintf(Cmd, "FREQ:MODE MSC");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "ATT:RF:MODE Normal");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:TIME:MODE ON");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:DET POS");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:DWEL 1s");
	 g_pRemote->FastSendCmd(Cmd);

	 sprintf(Cmd, "MEAS:HOLD 0");
	 g_pRemote->FastSendCmd(Cmd);

	 g_pRemote->FastSendCmd("MEASure:SQUelch ON");


	 CString  strPath;
	 GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	 strPath.ReleaseBuffer();
	 int nPos;
	 int nCount = 0;
	 nPos = strPath.ReverseFind('\\');
	 strPath = strPath.Left(nPos);
	 strPath += "\\default.task";
	 CFile file;
	 m_vtTask.clear();

	 if (file.Open(strPath, CFile::modeRead))
	 {
		 nCount = file.GetLength() / sizeof(TASK_ITEM);

		 sprintf(Cmd, "MSC:COUN %d", nCount);
		 g_pRemote->FastSendCmd(Cmd);
		 for (int i = 0; i < nCount; i++)
		 {
			 TASK_ITEM ti;
			 file.Read(&ti, sizeof(TASK_ITEM));
			 m_vtTask.push_back(ti);

			 //	sprintf(Cmd, "MEM:CONT 0,20000000,300000,FM,-30,-1");
			// sprintf(Cmd, "MEM:CONT %d,%I64d,%I64d,%s,%d,%d", i, m_vtTask[i].nCenter, m_vtTask[i].nBW, m_vtTask[i].sMode, m_vtTask[i].nNoise,m_vtTask[i].nAtt);
			  sprintf(Cmd, "MEM:CONT %d,%I64d,%I64d,%s", i, m_vtTask[i].nCenter, m_vtTask[i].nBW, m_vtTask[i].sMode);
			 g_pRemote->FastSendCmd(Cmd);
		 }

		file.Close();
	 }


	 //读频道表并发送
//	 g_pRemote->FastSendCmd("MEASure:TIME 100ms");

	 sprintf(Cmd, "TRAC:MED SCAN,SPECTRUM");
	 g_pRemote->FastSendCmd(Cmd);
	 sprintf(Cmd, "TRAC ON");
	 g_pRemote->FastSendCmd(Cmd);

	 spec_data.pt=0;
	 clear(m_qlevel);
	 scan_data.pdloc = 1024; //柱子位置
}


CRXMSCAN::~CRXMSCAN(void)
{
	char Cmd[100];
	sprintf(Cmd, "TRAC OFF");
	g_pRemote->FastSendCmd(Cmd);
}
void CRXMSCAN::ReadData ( void )
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
			if (generic_data.tag == DATA_TYPE_MSCAN)
			{
				num += sizeof(STRUCT_GENERIC_DATA);
				memcpy(&scan_data, &cBuffer[num], sizeof(STRUCT_SCAN_HEAD));
				num += sizeof(STRUCT_SCAN_HEAD);
				memcpy(nData, &cBuffer[num], scan_data.pdpt*sizeof(short));

				m_pLevel->Lock();
				if (!m_qlevel.empty())
				{
					clear(m_qlevel);
				}
				for(int i=0;i<scan_data.pdpt;i++)
				{

					m_qlevel.push((nData[i]/10.0));
				}
				m_pLevel->Unlock();
				
			}



		}
		m_pCSData->Unlock();
	}


}

int CRXMSCAN:: GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status)
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
	//Status.Ref = 70;
	m_pCSData->Unlock();
	return 0;
}
int CRXMSCAN:: GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata)
{
	m_pLevel->Lock();
	data = m_qlevel;


	nLen = m_qlevel.size();
	freq = level_data.freq;
	if (scan_data.start!=0)
	{
		nLen =1;
		freq=scan_data.pdloc; //柱子位置
	}
	m_pLevel->Unlock();
	return 0;
}