// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MR3300USBView.cpp : CMR3300USBView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MR3300USB.h"
#endif

#include "MR3300USBDoc.h"
#include "MR3300USBView.h"
#include "Measure.h"

#include "UdpServer.h"
#include "MeasSwitch.h"
#include "DlgParaConfig.h"
#include "DlgInterPhone.h"
#include "Common.h"
#include "RXFPSCAN.h"
#include "RemoteData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMR3300USBView

IMPLEMENT_DYNCREATE(CMR3300USBView, CView)

BEGIN_MESSAGE_MAP(CMR3300USBView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(PeakSearchOn, &CMR3300USBView::OnPeaksearchon)
	ON_COMMAND(PeakSearchOFF, &CMR3300USBView::OnPeaksearchoff)
	ON_COMMAND(ID_NormalMarkON, &CMR3300USBView::OnNormalmarkon)
	ON_COMMAND(ID_NormalMarkOFF, &CMR3300USBView::OnNormalmarkoff)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_NORDRAW, &CMR3300USBView::OnNordraw)
	ON_COMMAND(ID_FASTDRAW, &CMR3300USBView::OnFastdraw)
	ON_COMMAND(ID_HIGH_END_ON, &CMR3300USBView::OnHighEndOn)
	ON_COMMAND(ID_HIGH_END_OFF, &CMR3300USBView::OnHighEndOff)
	ON_COMMAND(ID_ENABLE_GRID, &CMR3300USBView::OnEnableGrid)
	ON_COMMAND(ID_DISABLE_GRID, &CMR3300USBView::OnDisableGrid)
END_MESSAGE_MAP()

// CMR3300USBView 构造/析构
bool bF1_F2 = false;
CMR3300USBView::CMR3300USBView()
{
	// TODO: 在此处添加构造代码
	m_pDevGDI = new CDevGDI();
	m_pThreadData = NULL;
	m_pThreadAud = NULL;
	m_pThreadWave = NULL;
	m_bFirst = TRUE;
	m_bDispITU = FALSE;
	m_bDispMESS =FALSE;
	m_bDispLevel = TRUE;
	m_bAud = FALSE;
	// 缓冲区初始化
	for (UINT i=0; i<WAVE_COUNT; i++) {
		memset(m_WaveBuf[i], 0, BUF_SIZE*sizeof(double));
		m_WaveLen[i] = 0;
		m_WaveHold[i] = false;
	}
	memset(m_dDataBuf, 0, BUF_SIZE*sizeof(double));

	m_IsPeakSearch = FALSE;
	m_IsNormalSearch = FALSE;
	g_bIsWave = FALSE;
	memset(m_fOldData, 10, BUF_SIZE*sizeof(double));

	m_pLock = new CCriticalSection();
	m_nSession = 0;

	player = new CPcmPlayer();
	playerD = new CPcmPlayer();


	player->Init(1, 50000, 16);
	playerD->Init(1, 24000, 16);

	ArrayFreqUnit.Add(_T("GHz"));
	ArrayFreqUnit.Add(_T("MHz"));
	ArrayFreqUnit.Add(_T("KHz"));
	ArrayFreqUnit.Add(_T("Hz"));

}

CMR3300USBView::~CMR3300USBView()
{
	if (m_pDevGDI != NULL)
	{
		delete m_pDevGDI;
		m_pDevGDI = NULL;
	}

	delete m_pLock;

	delete playerD;
	delete player;
}

BOOL CMR3300USBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMR3300USBView 绘制

void CMR3300USBView::OnDraw(CDC* /*pDC*/)
{
	CMR3300USBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CMR3300USBView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMR3300USBView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMR3300USBView 诊断

#ifdef _DEBUG
void CMR3300USBView::AssertValid() const
{
	CView::AssertValid();
}

void CMR3300USBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMR3300USBDoc* CMR3300USBView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMR3300USBDoc)));
	return (CMR3300USBDoc*)m_pDocument;
}
#endif //_DEBUG

// CMR3300USBView 消息处理程序
void CMR3300USBView::Start() 
{
	CRect rc;
	GetWindowRect(rc);
	InitGDI(m_hWnd, rc);

	m_AvgKey = 1;
	Status.Ref = 70;
	m_bDraw = FALSE;
	m_WaveHold[WAVE_NORMAL] = TRUE;

	m_pThreadAud = AfxBeginThread(ThreadAud, this);
	m_pThreadData = AfxBeginThread(ThreadData, this);
	m_pThreadWave = AfxBeginThread(ThreadWave, this);

}


UINT CMR3300USBView::ThreadAud(LPVOID lp)
{
	CMR3300USBView* pAud = (CMR3300USBView*)lp;

	UINT nPoint = 0;
	char cBuffer[65536];

	while(g_bIsRun) 
	{

		int num = 0;
		memset(cBuffer, 0, 65536);
		g_pAud->ReceiveData(cBuffer, nPoint,0);
		if (nPoint <= 0)
		{
			Sleep(1000);
			continue;
		}
		if (!g_bIsRun)
		{
			break;
		}
		memcpy(&pAud->m_Audfile_head, &cBuffer[num], sizeof(STRUCT_HEAD_DATA));
		num += sizeof(STRUCT_HEAD_DATA);
		if (pAud->m_Audfile_head.dgnum == 0)
		{
			continue;
		}
		memcpy(&pAud->m_Audgeneric_data, &cBuffer[num], sizeof(STRUCT_GENERIC_DATA));
		num += sizeof(STRUCT_GENERIC_DATA);
		if (pAud->m_Audgeneric_data.tag != DATA_TYPE_AUDIO)
		{
			continue;
		}

		memcpy(&pAud->m_audio_data, &cBuffer[num], sizeof(STRUCT_AUDIO_HEAD));
		num += sizeof(STRUCT_AUDIO_HEAD);
		if (pAud->m_audio_data.len<0)
		{
			continue;
		}
		if (pAud->m_bAud)
		{
			if (pAud->m_audio_data.samplerate==24000)
			{
				pAud->playerD->ToSpeaker(&cBuffer[num], pAud->m_audio_data.len * sizeof(short));
			} 
			else
			{
				pAud->player->ToSpeaker(&cBuffer[num], pAud->m_audio_data.len * sizeof(short));	
			}
		}
		Sleep(100);
	}	
	return 0;
}

UINT CMR3300USBView::ThreadWave(LPVOID lp)
{
	CMR3300USBView* pView = (CMR3300USBView*)lp;	
	while(g_bIsRun) 
	{
		if (g_bIsWave)
		{			
			g_MeasSwitch.EnterLock();
			pView->DrawWave();
			g_MeasSwitch.LeaveLock();
			Sleep(15);
		} 
		else
		{
			pView->DrawWave();
		}

#ifdef  _LOWCONFIGURE
		Sleep(15);
#else
		Sleep(1);
#endif

	}

	return S_OK;
}

UINT CMR3300USBView::ThreadData(LPVOID lp)
{
	CMR3300USBView* pData = (CMR3300USBView*)lp;	

	while(g_bIsRun) 
	{
		if (g_bIsWave)
		{			
			g_MeasSwitch.EnterLock();
			pData->DrawData();
			g_MeasSwitch.LeaveLock();
			Sleep(15);
		} 
		else
		{
			pData->DrawData();
		}
#ifdef  _LOWCONFIGURE
		Sleep(15);
#else
		Sleep(3);
#endif
		
	}
	return S_OK;
}
	
//int g_nTestMark;
void CMR3300USBView::DrawWave()
{
	static UINT64 nOldSession = 0;
	if (nOldSession!=m_nSession)
	{
		nOldSession = m_nSession;
		__int64 nfreq;
		float flevel;
		STRUCT_ITU_DATA ITU;
		int nDataLen=0;
		double *fData= new double[BUF_SIZE];

		if (g_bIsRun && g_pMea != NULL) 
		{
			CDevGDI& DevGDI = *m_pDevGDI;
			if (m_nPointNum>0)
			{
				// 加锁
				m_pLock->Lock();
				nfreq = m_nFreq;
				flevel = m_fLevel;
				memcpy(&ITU,&m_ITU,sizeof(STRUCT_ITU_DATA));
				memcpy(fData,m_dDataBuf,m_nPointNum*sizeof(double));
				nDataLen =  m_nPointNum;
				//解锁
				m_pLock->Unlock();

				if(g_pMea->GetMeasID()==SYSRESP)
				{
					double dStartY = Status.Ref - 100, dStopY = Status.Ref;

					DevGDI.GDI_SetSpanY(dStartY, dStopY);
					DevGDI.GDI_SetSpan(Status.StartFreq , Status.StopFreq , nDataLen);
					DevGDI.GDI_SetXFullSizeSpan(Status.StartFreq , Status.StopFreq , nDataLen);

					DevGDI.GDI_Draw(fData, nDataLen);

					CString szTemp = _T(""), szTemp1 = _T("");
					szTemp.Format(_T("%.6lf MHz"), 1.0*Status.StartFreq / N64_MHz);
					DevGDI.GDI_SetManualTextEx(0, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTLEFTBOTTOM, 15, UD_LARK_GREY);

					szTemp.Format(_T("%.6lf MHz"), 1.0*Status.StopFreq / N64_MHz);
					DevGDI.GDI_SetManualTextEx(1, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTBOTTOM, 15, UD_LARK_GREY);

					szTemp.Format(_T("%.1lf"), Status.Ref);
					DevGDI.GDI_SetManualTextEx(2, _T("Ref"), szTemp, _T(":"), true, DEVGDI_TEXT_OUTLEFTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T("Total:%d"), Status.total);
					DevGDI.GDI_SetManualTextEx(3, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T("level:%.3lf  atttype:%.3lf  att:%.3lf"), ITU.am, ITU.am_neg,ITU.am_pos);
					DevGDI.GDI_SetManualTextEx(4, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T("fieldcount:%d   nCount:%d"),(int) (nfreq+1),(int)(flevel));
					DevGDI.GDI_SetManualTextEx(5, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTBOTTOM, 15, UD_LARK_GREY);

				}
				else if(g_pMea->GetMeasID()==RXDFIND)
				{
					double dStartY = Status.Ref - 100, dStopY = Status.Ref;

					DevGDI.GDI_SetSpanY(dStartY, dStopY);
					DevGDI.GDI_SetSpan(Status.StartFreq, Status.StopFreq, nDataLen);
					DevGDI.GDI_SetXFullSizeSpan(Status.StartFreq , Status.StopFreq, nDataLen);

					DevGDI.GDI_Draw(fData, nDataLen);

					CString szTemp = _T(""), szTemp1 = _T("");
					szTemp.Format(_T("%d"), (int)Status.StartFreq);
					DevGDI.GDI_SetManualTextEx(0, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTLEFTBOTTOM, 15, UD_LARK_GREY);

					szTemp.Format(_T("%d"), (int)Status.StopFreq);
					DevGDI.GDI_SetManualTextEx(1, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTBOTTOM, 15, UD_LARK_GREY);

					szTemp.Format(_T("%.1lf"), Status.Ref);
					DevGDI.GDI_SetManualTextEx(2, _T("Ref"), szTemp, _T(":"), true, DEVGDI_TEXT_OUTLEFTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T("Total:%d"), Status.total);
					DevGDI.GDI_SetManualTextEx(3, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T(" "));
					DevGDI.GDI_SetManualTextEx(4, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T("Channum:%d   DataType:%d"),(int) (nfreq),(int)(flevel));
					DevGDI.GDI_SetManualTextEx(5, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTBOTTOM, 15, UD_LARK_GREY);

				}
				else if(g_pMea->GetMeasID()==RXIQ)
				{
					double dStartY = Status.Ref - 100, dStopY = Status.Ref;

					DevGDI.GDI_SetSpanY(dStartY, dStopY);
					DevGDI.GDI_SetSpan(Status.StartFreq, Status.StopFreq, nDataLen);
					DevGDI.GDI_SetXFullSizeSpan(Status.StartFreq , Status.StopFreq, nDataLen);

					DevGDI.GDI_Draw(fData, nDataLen);

					CString szTemp = _T(""), szTemp1 = _T("");
					szTemp.Format(_T("%d"), (int)Status.StartFreq);
					DevGDI.GDI_SetManualTextEx(0, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTLEFTBOTTOM, 15, UD_LARK_GREY);

					szTemp.Format(_T("%d"), (int)Status.StopFreq);
					DevGDI.GDI_SetManualTextEx(1, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTBOTTOM, 15, UD_LARK_GREY);

					szTemp.Format(_T("%.1lf"), Status.Ref);
					DevGDI.GDI_SetManualTextEx(2, _T("Ref"), szTemp, _T(":"), true, DEVGDI_TEXT_OUTLEFTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T("Total:%d"), Status.total);
					DevGDI.GDI_SetManualTextEx(3, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T(" "));
					DevGDI.GDI_SetManualTextEx(4, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T(" "));
					DevGDI.GDI_SetManualTextEx(5, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTBOTTOM, 15, UD_LARK_GREY);



				}
				else
				{
					double dStartY = Status.Ref - 100, dStopY = Status.Ref;
					for (size_t i=0; i<nDataLen; i++) 
					{
						double dData = fData[i];
						/////////////////////////////////////////////////////////////////
						bool bFre = FALSE;
						for (int ConfigCount = 0;ConfigCount<ConfigIni.nCount;ConfigCount++)
						{
							if ((Status.StartFreq+Status.StopFreq)==(ConfigIni.nFreq[ConfigCount]+ConfigIni.nFreqComp[ConfigCount])*2)
							{
								dData = dData+ConfigIni.fAmp[ConfigCount];
								m_StartFreq = Status.StartFreq -ConfigIni.nFreqComp[ConfigCount];
								m_StopFreq = Status.StopFreq -ConfigIni.nFreqComp[ConfigCount];
								bFre = TRUE;
							}
						}
						if(bFre == FALSE)
						{
							m_StartFreq = Status.StartFreq;
							m_StopFreq = Status.StopFreq;
						}

						m_WaveBuf[WAVE_NORMAL][i]=dData;

						// 计算最大值
						if (m_WaveHold[WAVE_MAX] && (m_WaveBuf[WAVE_MAX][i] < dData)) {
							m_WaveBuf[WAVE_MAX][i] = dData;
						}

						// 计算最小值
						if (m_WaveHold[WAVE_MIN] && (m_WaveBuf[WAVE_MIN][i] > dData)) {
							m_WaveBuf[WAVE_MIN][i] = dData;
						}

						if (m_WaveHold[WAVE_AVG] )
						{

							m_WaveBuf[WAVE_AVG][i]= (m_AvgKey - 1)*m_WaveBuf[WAVE_AVG][i] / m_AvgKey + dData /m_AvgKey;

						}		
					}
					DevGDI.GDI_SetSpanY(dStartY, dStopY);
					DevGDI.GDI_SetSpan(m_StartFreq , m_StopFreq , nDataLen);
					DevGDI.GDI_SetXFullSizeSpan(m_StartFreq , m_StopFreq , nDataLen);
					// 只执行一次
					if (m_bFirst)
					{
						m_WaveLen[WAVE_NORMAL] = m_nPointNum;

						ResetTrace();
						m_bFirst = FALSE;
					}
					if (m_WaveLen[WAVE_NORMAL]!=m_nPointNum)
					{
						m_bFirst = TRUE;

					}
					
					if (m_WaveHold[WAVE_AVG] )
					{
						m_AvgKey++;
					}		
					if (m_WaveHold[WAVE_NORMAL]!=TRUE)
					{
						//m_WaveLen[WAVE_NORMAL] = 0;
						DevGDI.GDI_Draw(m_WaveBuf[WAVE_NORMAL],0,
							m_WaveBuf[WAVE_MAX], m_WaveLen[WAVE_MAX],
							m_WaveBuf[WAVE_MIN], m_WaveLen[WAVE_MIN],
							m_WaveBuf[WAVE_AVG], m_WaveLen[WAVE_AVG]	
						);

					}
					else
					{
						DevGDI.GDI_Draw(m_WaveBuf[WAVE_NORMAL], m_WaveLen[WAVE_NORMAL],
							m_WaveBuf[WAVE_MAX], m_WaveLen[WAVE_MAX],
							m_WaveBuf[WAVE_MIN], m_WaveLen[WAVE_MIN],
							m_WaveBuf[WAVE_AVG], m_WaveLen[WAVE_AVG]	
						);
					}
				
					if (m_IsPeakSearch)
					{
						int nPos = 0;
						double dDataMax = m_WaveBuf[WAVE_NORMAL][nPos];
						for (int i = 0; i<m_WaveLen[WAVE_NORMAL]; i++)
						{
							if (m_WaveBuf[WAVE_NORMAL][i] > dDataMax)
							{
								nPos = i;
								dDataMax = m_WaveBuf[WAVE_NORMAL][i];
							}
						}
						CString sz;
						int nUnit = 0;
						double dValueY, dValueX;
						int nCurMarker = 0;
						nCurMarker = DevGDI.GDI_GetActiveMkr();
						int nPosX = DevGDI.GDI_GetMkrValue(dValueY, dValueX, nCurMarker, m_WaveBuf[WAVE_NORMAL], m_WaveLen[WAVE_NORMAL]);
					//	DevGDI.GDI_SetMkrVal(dValueY, nCurMarker);
					//	CCommon::Freq22Str( sz, nUnit, (INT64)dValueX, _T("%.6lf") );
						//DevGDI.GDI_SetActiveXMkrVal(sz+ArrayFreqUnit[nUnit]);
						DevGDI.GDI_SetMkrXPos(MARK_PEAK_SEARCH, nPos);

						if (g_pMea->GetMeasID()==RXFPSCAN)
						{

							CCommon::Freq22Str( sz, nUnit, (INT64)g_nFPSCAN[nPosX], _T("%.6lf") );
							DevGDI.GDI_SetActiveXMkrVal(sz+ArrayFreqUnit[nUnit]);
						} 
						else
						{
							CCommon::Freq22Str( sz, nUnit, (INT64)dValueX, _T("%.6lf") );
							DevGDI.GDI_SetActiveXMkrVal(sz+ArrayFreqUnit[nUnit]);
						}
					}
					if (m_IsNormalSearch)
					{
						double dValueY, dValueX;
						CString sz;
						int nUnit;
						int nCurMarker = 0;
						nCurMarker = DevGDI.GDI_GetActiveMkr();
						int nPosX = DevGDI.GDI_GetMkrValue(dValueY, dValueX, nCurMarker,m_WaveBuf[WAVE_NORMAL], m_WaveLen[WAVE_NORMAL]);
					//	DevGDI.GDI_SetMkrVal(dValueY, nCurMarker);
						//g_nTestMark = nPosX;
						if (g_pMea->GetMeasID()==RXFPSCAN)
						{
							
							CCommon::Freq22Str( sz, nUnit, (INT64)g_nFPSCAN[nPosX], _T("%.6lf") );
							DevGDI.GDI_SetActiveXMkrVal(sz+ArrayFreqUnit[nUnit]);
						} 
						else
						{
							CCommon::Freq22Str( sz, nUnit, (INT64)dValueX, _T("%.6lf") );
							DevGDI.GDI_SetActiveXMkrVal(sz+ArrayFreqUnit[nUnit]);
						}
					}
					CString szTemp = _T(""), szTemp1 = _T("");
					szTemp.Format(_T("%.6lf MHz"), 1.0*m_StartFreq / N64_MHz);
					DevGDI.GDI_SetManualTextEx(0, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTLEFTBOTTOM, 15, UD_LARK_GREY);

					szTemp.Format(_T("%.6lf MHz"), 1.0*m_StopFreq / N64_MHz);
					DevGDI.GDI_SetManualTextEx(1, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTBOTTOM, 15, UD_LARK_GREY);

					szTemp.Format(_T("%.1lf dBµV"), Status.Ref);
					DevGDI.GDI_SetManualTextEx(2, _T("Ref"), szTemp, _T(":"), true, DEVGDI_TEXT_OUTLEFTTOP, 15, UD_LARK_GREY);

					szTemp.Format(_T("Total:%d"), Status.total);
					DevGDI.GDI_SetManualTextEx(3, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTTOP, 15, UD_LARK_GREY);

					if (m_bDispITU)
					{
						szTemp.Format(_T("β带宽(kHz)%I64d XdB带宽(kHz)%I64d FM频偏(kHz)%.1lf FM正频偏(kHz)%.1lf FM负频偏(kHz)%.1lf AM调幅度(%%)%.1lf PM调制度(rad)%.1lf") , (INT64)ITU.betabw, (INT64)ITU.xdbbw,ITU.fm,ITU.fm_pos,ITU.fm_neg,ITU.am,ITU.pm);

						DevGDI.GDI_SetManualTextEx(4, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTTOP, 15, UD_LARK_GREY);

					}
					else
					{
						szTemp.Format(_T(""));
						DevGDI.GDI_SetManualTextEx(4, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTTOP, 15, UD_LARK_GREY);

					}

					szTemp.Format(_T(" "));
					DevGDI.GDI_SetManualTextEx(5, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTCENTBOTTOM, 15, UD_LARK_GREY);

				}
			}
		}
		delete [] fData;
	}
}
void CMR3300USBView::DrawData()
{
	double* fData = NULL;
	int nDataLen = 0;
	__int64 nfreq;
	float flevel;
	static int nCount = 0;
	STRUCT_ITU_DATA ITU;
	double DValueBuf[800];
	


	if (g_bIsRun && g_pMea != NULL) 
	{
		g_pMea->GetDataPro(fData, nDataLen, nfreq, flevel, ITU,Status);

		if (bF1_F2)
		{
			Status.StopFreq=Status.StopFreq+20000000;
			Status.StartFreq=Status.StartFreq-20000000;
			m_nPointNum= nDataLen+1600;
			Status.total=nDataLen+1600;
		}
		else
		{
			m_nPointNum= nDataLen;
			Status.total=nDataLen;
		}



		if (memcmp(fData, m_fOldData,nDataLen*sizeof(double)) != 0)
		{
			memcpy(m_fOldData, fData, nDataLen*sizeof(double));
			if ((fData != NULL)&&(nDataLen>0)) //&&(nDataLen<WAVE_NORMAL)
			{

			//	memcpy(m_NewValue,fData,nDataLen*sizeof(double));

				memset(m_NewValue,0,m_nPointNum*sizeof(double));

				if (bF1_F2)
				{
								//double DValue= 	(*max_element(&fData[0], fData + 200))	-(*min_element(&fData[0], fData + 200));
							//	if (DValue<5)
							//	{
									memcpy(DValueBuf,fData ,100*sizeof(double));
									for (int i =0;i<100;i++)
									{
										DValueBuf[i] = DValueBuf[i]-0.5;
									}
							//	} 
							//	else
							//	{
					
							//	}

									for (int i =0 ;i<8;i++)
									{
										memcpy(&m_NewValue[i*100],DValueBuf , 100*sizeof(double));
									}
				
								//memcpy(&m_NewValue[200],DValueBuf , 200*sizeof(double));
								//memcpy(&m_NewValue[400],DValueBuf , 200*sizeof(double));
								//memcpy(&m_NewValue[600],DValueBuf , 200*sizeof(double));

								memcpy(&m_NewValue[800],m_fOldData , nDataLen*sizeof(double));


								memcpy(DValueBuf,fData+1500 ,100*sizeof(double));
								for (int i =0;i<100;i++)
								{
									DValueBuf[i] = DValueBuf[i]+0.4;
								}



								for (int i =0 ;i<8;i++)
								{
									memcpy(&m_NewValue[i*100+800+nDataLen],DValueBuf , 100*sizeof(double));
								}

							//	memcpy(&m_NewValue[800+nDataLen] ,DValueBuf , 200*sizeof(double));
							//	memcpy(&m_NewValue[1000+nDataLen],DValueBuf , 200*sizeof(double));
							//	memcpy(&m_NewValue[1200+nDataLen],DValueBuf , 200*sizeof(double));
							//	memcpy(&m_NewValue[1400+nDataLen],DValueBuf , 200*sizeof(double));
	

								//for (int i=800;i<nDataLen;i+=800)
								//{
								//	
								//	if (DValue<4)
								//	{
								//		g_nTestMark=DValue;
								//		
								//		memcpy(fData,DValueBuf , 100*sizeof(double));

								//		break;
								//	}
								//}
				

								//m_nPointNum= nDataLen;
				}
				else
				{
					memcpy(&m_NewValue[0],m_fOldData , nDataLen*sizeof(double));
				}
				//数据压缩

				//if (m_bDraw)
				if (g_bDraw)
				{
					memcpy((BYTE*)m_pSpectDataPixel[nCount],(BYTE*)m_NewValue,sizeof(double)*m_nPointNum);
					nCount++;
					if (nCount>=5)
					{
						//加锁
						m_pLock->Lock();
						WaveAdjustRateY(nCount);
						nCount = 0;

						m_nFreq = nfreq;
						m_fLevel = flevel;
						memcpy(&m_ITU,&ITU,sizeof(STRUCT_ITU_DATA));
						//memcpy(m_dDataBuf,fData,m_nPointNum*sizeof(double));
						// 解锁
						m_pLock->Unlock();
						m_nSession ++;
					}
				} 
				else
				{
					//加锁
					m_pLock->Lock();
					m_nFreq = nfreq;
					m_fLevel = flevel;
					memcpy(&m_ITU,&ITU,sizeof(STRUCT_ITU_DATA));
					memcpy(m_dDataBuf,m_NewValue,m_nPointNum*sizeof(double));
					// 解锁
					m_pLock->Unlock();
					m_nSession ++;
				}

			//	WaveAdjustRateX(m_dDataBuf,m_nPointNum);

			}
		}
	}
}
void CMR3300USBView::WaveAdjustRateX(const double *pdData,int nDataLen)
{
	int pixel = 0;
	int Oldpixel = 0;
	int nWidth = 0;

	CRect rc;
	GetClientRect(rc);
	int nViewWidth = rc.right-rc.left-m_leftboard-m_rightboard;
	nWidth = nDataLen/nViewWidth; 

	for (int j=0; j<nDataLen; j++)
	{

		pixel = j/nWidth;

		if(pixel!=Oldpixel)
		{
			//Oldpixel = pixel;
			//m_Wave.m_dDataBuf[pixel]=pdData[j]; 
			//m_Wave.m_nFreq[pixel] = j;
			double m_dMarkDataBuf[3000];
			__int64 m_nMarkFreq[3000];
		}
		else
		{
			//if(m_Wave.m_dDataBuf[pixel]<pdData[j])
			//{
			//	m_Wave.m_dDataBuf[pixel]=pdData[j];
			//	m_Wave.m_nFreq[pixel] = j;
			//}

		}
	}
	//	m_nPointNum= pixel;
	//	m_nMode =1;

	
}

void CMR3300USBView::WaveAdjustRateY(int nCount)
{
	for(int i=0;i<m_nPointNum;i++)
	{
		m_dDataBuf[i]=-999;
		for(int j=0;j<nCount;j++)
		{
			if(m_dDataBuf[i]<m_pSpectDataPixel[j][i])
				m_dDataBuf[i]=m_pSpectDataPixel[j][i];
		}
	}
}

void CMR3300USBView::SetTraceVisable(UINT nTrace, BOOL IsVisable)
{
	if (nTrace == WAVE_MAX) {
		if (IsVisable) {
			// 复制当前波形
			memcpy( m_WaveBuf[WAVE_MAX], m_WaveBuf[WAVE_NORMAL], m_WaveLen[WAVE_NORMAL]*sizeof(double));
			m_WaveLen[WAVE_MAX] = m_nPointNum;
			m_WaveHold[WAVE_MAX] = TRUE;
		}
		else {
			m_WaveLen[WAVE_MAX] = 0;
			m_WaveHold[WAVE_MAX] = FALSE;
		}
	}
	else if (nTrace == WAVE_MIN) {
		if (IsVisable) {
			// 复制当前波形
			memcpy( m_WaveBuf[WAVE_MIN], m_WaveBuf[WAVE_NORMAL], m_WaveLen[WAVE_NORMAL]*sizeof(double));
			m_WaveLen[WAVE_MIN] = m_nPointNum;
			m_WaveHold[WAVE_MIN] = TRUE;
		}
		else {
			m_WaveLen[WAVE_MIN] = 0;
			m_WaveHold[WAVE_MIN] = FALSE;
		}

	}
	else if (nTrace == WAVE_AVG) {
		if (IsVisable) {
			// 复制当前波形
			memcpy( m_WaveBuf[WAVE_AVG], m_WaveBuf[WAVE_NORMAL], m_WaveLen[WAVE_NORMAL]*sizeof(double));
			m_WaveLen[WAVE_AVG] = m_nPointNum;
			m_WaveHold[WAVE_AVG] = TRUE;
			m_AvgKey = 1;
		}
		else {
			m_WaveLen[WAVE_AVG] = 0;
			m_WaveHold[WAVE_AVG] = FALSE;
		}
	}
	else {
		if (IsVisable) {
			m_WaveLen[WAVE_NORMAL] = m_nPointNum;
			m_WaveHold[WAVE_NORMAL] = TRUE;
		}
		else {
			m_WaveLen[WAVE_NORMAL] = 0;
			m_WaveHold[WAVE_NORMAL] = FALSE;
		}
	}

}
void CMR3300USBView::SetDataVisable(CString DataMode, BOOL IsVisable)
{

	if (DataMode == "Level")
	{
		m_bDispLevel = IsVisable;

		g_bLevel = m_bDispLevel ;
	}

	if (DataMode == "ITU")
	{
		m_bDispITU = IsVisable;
	}
	if (DataMode == "Audio")
	{
		m_bAud = IsVisable;
	}
	if (DataMode == "MESS")
	{
		m_bDispMESS = IsVisable;
	}
}
void CMR3300USBView::ResetTrace()
{
	memcpy( m_WaveBuf[WAVE_MAX], m_WaveBuf[WAVE_NORMAL], m_nPointNum*sizeof(double));
	memcpy( m_WaveBuf[WAVE_MIN], m_WaveBuf[WAVE_NORMAL], m_nPointNum*sizeof(double));
	memcpy( m_WaveBuf[WAVE_AVG], m_WaveBuf[WAVE_NORMAL], m_nPointNum*sizeof(double));
	if (m_WaveHold[WAVE_AVG])
	{
		m_WaveLen[WAVE_AVG]= m_nPointNum;
	} 
	else
	{
		m_WaveLen[WAVE_AVG]= 0;
	}


	if (m_WaveHold[WAVE_MAX])
	{
		m_WaveLen[WAVE_MAX]= m_nPointNum;
	} 
	else
	{
		m_WaveLen[WAVE_MAX]= 0;
	}

	if (m_WaveHold[WAVE_MIN])
	{
		m_WaveLen[WAVE_MIN]= m_nPointNum;
	} 
	else
	{
		m_WaveLen[WAVE_MIN]= 0;
	}

	m_AvgKey = 1;
}
void CMR3300USBView::SetRef(int ref)
{
	Status.Ref=ref;
}
void CMR3300USBView::SetRange(double range)
{
}
void CMR3300USBView::InitGDI(HWND& hWnd, const CRect& rc)
{
	CDevGDI& DevGDI = *m_pDevGDI;
	DevGDI.GDI_Init(rc, hWnd);
	DevGDI.GDI_SETViewPrecision(2);
	DevGDI.GDI_EnableMkrLine(true,false,true);
	DevGDI.GDI_SetTextEnable(FALSE, true);
//	DevGDI.GDI_ManualMkrVal(DEV_MKR_VALUE_MANUAL_DIGIT);
	DevGDI.GDI_SetXMrkEnable(TRUE);	
	DevGDI.GDI_EnableManualXText(TRUE);	
	DevGDI.GDI_SetBorderGridPos(CRect(40, 30, 20, 30));
	DevGDI.GDI_SetGridLineNum(10, 10);

	//DevGDI.GDI_SetBKColor(UD_WHITE);
	DevGDI.GDI_SetGridStyle(UD_EQUALIZER, 3, 1, DEV_GRID_SPECTRUM);
	DevGDI.GDI_SetLine(UD_YELLOW, 1,
		UD_RED, 1,
		UD_BLUE, 1,
		UD_BOTTLE_GREEN, 1,
		UD_LAVENDER, 1,
		UD_ROYAL_BLUE, 1,
		UD_MAROON, 1,
		UD_LIGHT_GREY, 1,
		UD_EQUALIZER, 1,
		UD_TAN, 1);

		m_right = 20;
}
void CMR3300USBView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);


	CRect rc;
	GetClientRect(rc);
	m_pDevGDI->GDI_SetRect(rc);

	m_leftboard = 40;
	m_rightboard = rc.right-m_right-1;
	// TODO: 在此处添加消息处理程序代码
}

void CMR3300USBView::OnPeaksearchon()
{
	// TODO: 在此添加命令处理程序代码
	m_IsPeakSearch = true;
	m_pDevGDI->GDI_EnableMkr(MARK_PEAK_SEARCH, m_IsPeakSearch);
	m_pDevGDI->GDI_SetActiveMkr(MARK_PEAK_SEARCH);
}


void CMR3300USBView::OnPeaksearchoff()
{
	// TODO: 在此添加命令处理程序代码
	m_IsPeakSearch = false;
	m_pDevGDI->GDI_EnableMkr(MARK_PEAK_SEARCH, m_IsPeakSearch);

	m_pDevGDI->GDI_EnableMkr(MARK_NORMAL, m_IsNormalSearch);
	m_pDevGDI->GDI_SetActiveMkr(MARK_NORMAL);

}

void CMR3300USBView::OnNormalmarkon()
{
	// TODO: 在此添加命令处理程序代码
	m_IsNormalSearch = true;
	m_pDevGDI->GDI_EnableMkr(MARK_NORMAL, true);
	m_pDevGDI->GDI_SetActiveMkr(MARK_NORMAL);

}
void CMR3300USBView::OnNormalmarkoff()
{
	// TODO: 在此添加命令处理程序代码

	m_IsNormalSearch = false;
	m_pDevGDI->GDI_EnableMkr(MARK_NORMAL, false);

	m_pDevGDI->GDI_EnableMkr(MARK_PEAK_SEARCH, m_IsPeakSearch);
	m_pDevGDI->GDI_SetActiveMkr(MARK_PEAK_SEARCH);
}
void CMR3300USBView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}
void CMR3300USBView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_IsNormalSearch)
	{
		m_MarPoint = point;

		if (m_MarPoint.x < m_leftboard)
		{
			m_MarPoint.x = m_leftboard;
		}
		if (m_MarPoint.x > m_rightboard)
		{
			m_MarPoint.x = m_rightboard;
		}

		double* nData = NULL;
		int nDataLen = 0;
		__int64 nfreq;
		float flevel;
		STRUCT_ITU_DATA ITU;
		
		if (g_bIsRun && g_pMea != NULL) 
		{
			CDevGDI& DevGDI = *m_pDevGDI;
			//g_pMea->GetDataPro(nData, nDataLen, nfreq, flevel, ITU,Status);
			DevGDI.GDI_SetActiveMkrByMouse(point.x, point.y, m_dDataBuf, m_nPointNum);
		}
	
	}
	CView::OnLButtonDown(nFlags, point);
}
void CMR3300USBView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if ((m_IsNormalSearch)&& (MK_LBUTTON == nFlags))
	{
		double* nData = NULL;
		int nDataLen = 0;
		__int64 nfreq;
		float flevel;
		STRUCT_ITU_DATA ITU;
		m_MarPoint = point;
		if (m_MarPoint.x < m_leftboard)
		{
			m_MarPoint.x = m_leftboard;
		}
		if (m_MarPoint.x > m_rightboard)
		{
			m_MarPoint.x = m_rightboard;
		}

		if (g_bIsRun && g_pMea != NULL) 
		{
			CDevGDI& DevGDI = *m_pDevGDI;
			//g_pMea->GetDataPro(nData, nDataLen, nfreq, flevel, ITU,Status);

			DevGDI.GDI_SetMkrX(point.x, point.y, m_dDataBuf, m_nPointNum);
			DevGDI.GDI_ScrollWaveByMouse(point.x, point.y, m_dDataBuf, m_nPointNum);
		}
	}
	CView::OnMouseMove(nFlags, point);
}



BOOL CMR3300USBView::PreTranslateMessage(MSG*pMsg)//Dlg为对话框类
{
	if (pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{

		case VK_F1:
			if(g_bSpan)
			{
				bF1_F2 = false;
				g_pRemote->FastSendCmd("FREQuency:SPAN 80000000");
			}
			break;
		case VK_F2:
			if(g_bSpan)
			{
				bF1_F2 = true;
				g_pRemote->FastSendCmd("FREQuency:SPAN 40000000");
			}
			break;
		case VK_LEFT:
			m_MarPoint.x=(m_MarPoint.x-1);

			if (m_MarPoint.x < m_leftboard)
			{
				m_MarPoint.x = m_leftboard;
			}
			break;
		case VK_RIGHT:
			m_MarPoint.x=(m_MarPoint.x+1);

			if (m_MarPoint.x > m_rightboard)
			{
				m_MarPoint.x = m_rightboard;
			}

			break;
		}
		if ((m_IsNormalSearch))
		{
			double* nData = NULL;
			int nDataLen = 0;
			__int64 nfreq;
			float flevel;
			STRUCT_ITU_DATA ITU;
			if (g_bIsRun && g_pMea != NULL) 
			{
				CDevGDI& DevGDI = *m_pDevGDI;
				//g_pMea->GetDataPro(nData, nDataLen, nfreq, flevel, ITU,Status);
				
				DevGDI.GDI_SetMkrX(m_MarPoint.x, m_MarPoint.y, m_dDataBuf, m_nPointNum);
				DevGDI.GDI_ScrollWaveByMouse(m_MarPoint.x, m_MarPoint.y, m_dDataBuf, m_nPointNum);

			}
		}
	}
	return CView::PreTranslateMessage(pMsg);
}

void CMR3300USBView::OnNordraw()
{
	// TODO: 在此添加命令处理程序代码
	m_bDraw = FALSE;
}


void CMR3300USBView::OnFastdraw()
{
	// TODO: 在此添加命令处理程序代码
	m_bDraw = TRUE;
}

void CMR3300USBView::OnHighEndOn()
{
	// TODO: 在此添加命令处理程序代码
	g_pDlgParaConfig->Detection(TRUE);


}

void CMR3300USBView::OnHighEndOff()
{
	// TODO: 在此添加命令处理程序代码
	g_pDlgParaConfig->Detection(FALSE);
	
}

void CMR3300USBView::OnEnableGrid()
{
	// TODO: 在此添加命令处理程序代码
	m_pDevGDI->GDI_EnableGrid(TRUE);
}

void CMR3300USBView::OnDisableGrid()
{
	// TODO: 在此添加命令处理程序代码
	m_pDevGDI->GDI_EnableGrid(FALSE);
}
