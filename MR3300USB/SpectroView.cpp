// SpectroView.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "SpectroView.h"
#include "MeasSwitch.h"
#include "Measure.h"

IMPLEMENT_DYNCREATE(CSpectroView, CView)


CSpectroView::CSpectroView()
{
	m_pSpetroThread = NULL;
	m_pSpetroDataThread = NULL;
	m_pSpectroDevGDI = new CDevGDI();

	m_RectBorder.top = 25;
	m_RectBorder.right = 20;
	m_RectBorder.left = 40;
	m_RectBorder.bottom = 20;
	m_RectBorderDT = CRect(0,0,0,0);

	m_IsPlay = TRUE;
	m_IsMark = FALSE;

	m_nTimes = 500;
	m_nCurTime = 0;
	m_nDataCount = 0;
	m_bMode = FALSE;
	m_SpectMarker.IsEnable = TRUE;
	m_nCount = 10;

	m_pSpectData = NULL;
	m_pSpectDraw = NULL;
	m_pSpectMarker = NULL;
	m_pSpectDataPixelX = NULL;
	m_pSpectDataPixelY = NULL;
	m_pTMData = NULL;
	m_pTMDraw = NULL;

	m_pSpectData = new double [m_nDotNum*m_nTime];
	m_pSpectDraw = new double [m_nDotNum*m_nTime];
	m_pSpectDataPixelX = new double [m_nDotNum];
	m_pSpectDataPixelY = new double [m_nDotNum];
	m_pSpectMarker = new double [m_nDotNum];
	m_pTMData = new SYSTEMTIME [m_nTime];
	m_pTMDraw = new SYSTEMTIME [m_nTime];

}

CSpectroView::~CSpectroView()
{
	if (m_pSpectroDevGDI != NULL)
	{
		delete m_pSpectroDevGDI;
		m_pSpectroDevGDI = NULL;
	}

	if (m_pSpectData != NULL) {
		delete [] m_pSpectData;
		m_pSpectData =NULL;
	}

	if (m_pSpectDraw != NULL) {
		delete [] m_pSpectDraw;
		m_pSpectDraw = NULL;
	}

	if (m_pSpectMarker != NULL) {
		delete [] m_pSpectMarker;
		m_pSpectMarker = NULL;
	}

	if (m_pTMData != NULL ) {
		delete [] m_pTMData;
		m_pTMData = NULL;
	}

	if (m_pTMDraw != NULL) {
		delete [] m_pTMDraw;
		m_pTMDraw = NULL;
	}

	if (m_pSpectDataPixelX != NULL) {
		delete [] m_pSpectDataPixelX;
		m_pSpectDataPixelX = NULL;
	}
	if (m_pSpectDataPixelY != NULL) {
		delete [] m_pSpectDataPixelY;
		m_pSpectDataPixelY = NULL;
	}
	
}

BEGIN_MESSAGE_MAP(CSpectroView, CView)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MarkON, &CSpectroView::OnMarkon)
	ON_COMMAND(ID_MarkOFF, &CSpectroView::OnMarkoff)
	ON_COMMAND(ID_Mark_X, &CSpectroView::OnMarkX)
	ON_COMMAND(ID_Mark_Y, &CSpectroView::OnMarkY)
	ON_COMMAND(ID_SPECTRO_STOP, &CSpectroView::OnSpectroStop)
	ON_COMMAND(ID_SPECTRO_START, &CSpectroView::OnSpectroStart)
	ON_COMMAND(ID_FAST, &CSpectroView::OnFast)
	ON_COMMAND(ID_SLOW, &CSpectroView::OnSlow)
	ON_COMMAND(ID_REFRESH, &CSpectroView::OnRefresh)
	ON_COMMAND(ID_BTN_GRAY, &CSpectroView::OnBtnGray)
	ON_COMMAND(ID_BTN_HOT, &CSpectroView::OnBtnHot)
END_MESSAGE_MAP()


// CSpectroView 绘图

void CSpectroView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CSpectroView 诊断

#ifdef _DEBUG
void CSpectroView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSpectroView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSpectroView 消息处理程序


void CSpectroView::Start() 
{
	CRect rc;
	GetWindowRect(rc);
	InitGDI(m_hWnd, rc);
	m_pSpetroThread = AfxBeginThread(ThreadSpetro, this);
	m_pSpetroDataThread = AfxBeginThread(ThreadSpetroData, this);
}

UINT CSpectroView::ThreadSpetroData(LPVOID lp)
{
	CSpectroView* pData = (CSpectroView*)lp;
	while(g_bIsRun) 
	{
		if (pData->m_bMode)
		{
			if (g_bIsWave)
			{	
				g_MeasSwitch.EnterLock();
				pData->DataSpectro();
				g_MeasSwitch.LeaveLock();
			} 
			else
			{
				pData->DataSpectro();
			}
#ifdef  _LOWCONFIGURE
			Sleep(15);
#else
			Sleep(5);
#endif
		} 
		else
		{
			Sleep(200);
		}
	}
	return S_OK;
}

UINT CSpectroView::ThreadSpetro(LPVOID lp)
{
	CSpectroView* pView = (CSpectroView*)lp;
	while(g_bIsRun) 
	{
		if (pView->m_bMode)
		{
			if (g_bIsWave)
			{	
				g_MeasSwitch.EnterLock();
				pView->DrawSpectro();
				g_MeasSwitch.LeaveLock();
			} 
			else
			{
				pView->DrawSpectro();
			}
#ifdef  _LOWCONFIGURE
			Sleep(15);
#else
			Sleep(5);
#endif
		} 
		else
		{
			Sleep(200);
		}
	}
	return S_OK;
}

void CSpectroView::DataSpectro()
{
	double* nData = NULL;
	int nDataLen = 0;
	static int nOldDataLen = 0;
	__int64 nfreq;
	float flevel;
	STRUCT_ITU_DATA ITU;
	WaveStatus status;
	static int nCount = 0;
	if (g_bIsRun && g_pMea != NULL) 
	{
		g_pMea->GetDataPro(nData, nDataLen, nfreq, flevel, ITU,status);


		if ((nData != NULL)&&(nDataLen>0)) 
		{
			if ((nDataLen!=nOldDataLen)||(m_Status.StartFreq!=status.StartFreq)||(m_Status.StopFreq!=status.StopFreq))
			{
				 nOldDataLen= nDataLen;
				memcpy(&m_Status,&status,sizeof(m_Status));
				SetSpectTime(m_nTimes,FALSE);
				SetByStatus();
			} 
			else
			{
				if (memcmp(nData, m_fOldData,nDataLen*sizeof(double)) != 0) {
					memcpy(m_fOldData, nData, nDataLen);


					WaveAdjustRateX(nData,nDataLen);
					

					memcpy((BYTE*)m_pSpectDataPixel[nCount],(BYTE*)m_pSpectDataPixelX,sizeof(double)*m_nDataCount);
					nCount++;
					if (nCount>=m_nCount)
					{
						
						WaveAdjustRateY(nCount);
						nCount = 0;

						if (m_nCurTime < m_nTimes)	// 数据区未满的时候
						{
							GetLocalTime(&(m_pTMData[m_nCurTime]));
							memmove((BYTE*)m_pSpectData+sizeof(double)*m_nDataCount, (BYTE*)m_pSpectData,  sizeof(double)*m_nDataCount*(m_nCurTime)); 
							for (UINT i=0; i<m_nDataCount; i++)
							{
								m_pSpectData[i] = m_pSpectDataPixelY[i];
							}
							m_nCurTime ++;
						}
						else 
						{	
							// 数据区已经满了的情况
							memmove((BYTE*)m_pTMData, (BYTE*)m_pTMData+sizeof(SYSTEMTIME), sizeof(SYSTEMTIME)*(m_nTimes-1)); //sizeof(double)*nDataLen*(N_SPECT_NUM-1));
							GetLocalTime(&(m_pTMData[m_nTimes-1]));
							memmove((BYTE*)m_pSpectData+sizeof(double)*m_nDataCount, (BYTE*)m_pSpectData,  sizeof(double)*m_nDataCount*(m_nTimes-1)); 
							for (UINT i=0; i<m_nDataCount; i++)
							{
								m_pSpectData[i] =  m_pSpectDataPixelY[i];
							}
						}
					}
				}
			}

		}
	}
}
void CSpectroView::SetByStatus()
{
	m_pSpectroDevGDI->GDI_SetSpan(m_Status.StartFreq,  m_Status.StopFreq);
	m_pSpectroDevGDI->GDI_SetXFullSizeSpan(m_Status.StartFreq, m_Status.StopFreq );

	CString strCent, strStart, strStop;
	strCent.Format(_T("%.6lf MHz"), 0.5*(m_Status.StartFreq+m_Status.StopFreq) / N64_MHz);
	
	strStart.Format(_T("%.6lf MHz"), 1.0*m_Status.StartFreq / N64_MHz);
	strStop.Format(_T("%.6lf MHz"), 1.0*m_Status.StopFreq / N64_MHz);


	m_pSpectroDevGDI->GDI_SetXValue(strStart, strCent,strStop);
}
void CSpectroView::DrawSpectro()
{
	CDevGDI& DevGDI = *m_pSpectroDevGDI;

	if ((m_nDataCount>0) && (g_pMea != NULL))
	{
		if (m_IsPlay) {
			memcpy((BYTE*)m_pSpectDraw, (BYTE*)m_pSpectData, sizeof(double)*m_nDataCount*m_nTimes );
			memcpy((BYTE*)m_pTMDraw, (BYTE*)m_pTMData, sizeof(SYSTEMTIME)*m_nTimes );
		}
		if (m_IsMark)
		{

			SPECT_MARKER_DATA *test=ReadMark();
			CString szTemp = _T(""), szTemp1 = _T("");
			szTemp.Format(_T("%d:%d:%d.%d %.6lfMHz %.1lfdBµV"),test->tm.wHour,test->tm.wMinute,test->tm.wSecond,test->tm.wMilliseconds,(double)test->nFreq/N64_MHz,test->dValue);

			DevGDI.GDI_SetManualTextEx(20, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTTOP, 15, UD_LARK_GREY);
		} 
		else
		{
			CString szTemp = _T(""), szTemp1 = _T("");
			szTemp.Format(_T(" "));
			DevGDI.GDI_SetManualTextEx(20, _T(""), szTemp, _T(""), true, DEVGDI_TEXT_OUTRIGHTTOP, 15, UD_LARK_GREY);
		}
		DevGDI.GDI_DrawSpectrogram(m_pSpectDraw, m_nTimes, m_nDataCount, m_ColorSpec, m_dzLevel, PALETTE_NUM);
	}
}

void CSpectroView::InitGDI(HWND& hWnd, const CRect& rc)
{
	CDevGDI& DevGDI = *m_pSpectroDevGDI;

	DevGDI.GDI_Init(rc, hWnd);
	DevGDI.GDI_SetXFullSizeSpan(5, 65);
	//DevGDI.GDI_SetBKColor(RGB(0,0,0));
	DevGDI.GDI_SetSpan(5, 65);
	DevGDI.GDI_SetSpanY(0, 24);
	DevGDI.GDI_SetGridLineNum(10, 8);
	DevGDI.GDI_SetLine(RGB(255,255,255), 1,		// current 0
		RGB(0,0,0), 1,		// max 1
		RGB(200,200,200), 1,		// min 2
		RGB(180,180,180), 1,		// Average 3
		RGB(255,0,0), 3,		// up limit 1 4
		RGB(0,255,0), 3,	// Down limit 1 5
		RGB(0,0,255), 3,		// up limit 2 6
		RGB(0,0,0), 3,		// Down limit 2 7
		RGB(255,0,255), 3,		// up limit 3 8
		RGB(0,255,255), 3,		// down limit 3 9
		RGB(255,255,0), 3,		// up limit 4 10
		RGB(150,224,233), 3,		// down limit 4 11
		RGB(255,0,0), 3,		// up limit 5 12
		RGB(0,0,255), 3);		// down limit 5 13
	DevGDI.GDI_SetYDepartment(_T(" "));
	DevGDI.GDI_SetXDepartment(_T("MHz"));
	DevGDI.GDI_EnableGrid(false);
	DevGDI.GDI_EnableSpectrogramMkrLine(true);

	DevGDI.GDI_SetBorderGridPos(m_RectBorder+m_RectBorderDT);
	DevGDI.GDI_UseSpectrogramMkr(SPECTROGRAM_MKR_Y);
	DevGDI.GDI_SetTextEnable(true, false);
	DevGDI.GDI_EnableManualXText(true);
	//m_pGDI[0].GDI_SetYDepartment(_T("dBuV"));



	int r = 255, g = 0, b = 0;
	int n = 256 / PALETTE_NUM * 4;
	int step = 0;
	for ( int i = 0 ; i < PALETTE_NUM; i++ )
	{
		m_ColorSpec[PALETTE_NUM-1-i] = RGB(r,g,b);

		switch ( step )
		{
		case 0:
			g += n;
			if ( g > 255 )
			{
				g = 255;
				step++;
			}
			break;
		case 1:
			r -= n;
			if ( r < 0 )
			{
				r = 0;
				step++;
			}
			break;
		case 2:
			b += n;
			if ( b > 255 )
			{
				b = 255;
				step++;
			}
			break;
		case 3:
			g -= n;
			if ( g < 0 )
				g = 0;
			break;
		}
		m_dzLevel[i] =(double) (-20+i*0.78125);
	}

	m_dzLevel[0] = -999999.0;

}

void CSpectroView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	//CRect rc;
	GetClientRect(m_rc);
	m_pSpectroDevGDI->GDI_SetRect(m_rc);

	m_nDataCount =  (static_cast<int>(m_rc.right-m_rc.left-m_RectBorder.right-m_RectBorder.left));
	UINT nTimes = (m_rc.Height()-m_RectBorder.top-m_RectBorder.bottom )/2;

	if ((m_nTimes != nTimes) && (nTimes < 5000)) {
		m_nTimes = nTimes;
		SetSpectTime(nTimes, FALSE);

	}
}

void CSpectroView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pSpectroDevGDI->GDI_SetSpectrogramMkrPos(point.x-1, point.y-1, m_nTimes, m_nDataCount);
	CView::OnLButtonDown(nFlags, point);
}

void CSpectroView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(MK_LBUTTON == nFlags)
	{
		m_pSpectroDevGDI->GDI_SetSpectrogramMkrPos(point.x-1, point.y-1, m_nTimes, m_nDataCount);
		CView::OnMouseMove(nFlags, point);
	}

}

void CSpectroView::SetUseMarker( BYTE ucType )
{
	m_pSpectroDevGDI->GDI_UseSpectrogramMkr(ucType);
}

void CSpectroView::SetSpectPlay( BOOL IsPlay )
{
	m_IsPlay = IsPlay;
}
void CSpectroView::SetSpectTime( UINT nTime, BOOL IsUseLock )
{
	m_nCurTime = 0;
	m_nTimes = nTime;

	for (UINT i=0; i<m_nDotNum*m_nTime; i++) {
		m_pSpectDraw[i] = m_pSpectData [i] = m_dzLevel[0];
	}
	m_pSpectroDevGDI->GDI_SetSpectrogramMkrPos(0,0,m_nTimes, m_nDataCount);
}

SPECT_MARKER_DATA* CSpectroView::ReadMark()
{
	CString sz;
	int nUnit;
	int nXid = 0;
	int nXid2 = 0;
	int nYid = 0;
	m_pSpectroDevGDI->GDI_GetSpectrogramMkrPos(SPECTROGRAM_MKR_X, nXid, nYid, m_pSpectMarker, m_pSpectDraw, m_nTimes, m_nDataCount);

	nXid2 = m_nDataCount*nYid+nXid;

	m_SpectMarker.dValue = m_pSpectDraw[nXid2];
	m_SpectMarker.tm = m_pTMDraw[nYid];

	// 计算频率值
	INT64 nStart = m_Status.StartFreq;
	m_SpectMarker.nFreq = nStart + 1.0*(m_Status.StopFreq-m_Status.StartFreq)*nXid/(m_nDataCount-1);

	return &m_SpectMarker;
}
void CSpectroView::SetDevGDI(BOOL mode)
{
	m_bMode=mode;
	if (m_bMode)
	{
		SetSpectTime(m_nTimes, FALSE);
	}
}


void CSpectroView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码

#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU_SPECTRO, point.x, point.y, this, TRUE);
#endif

}

void CSpectroView::OnMarkon()
{
	// TODO: 在此添加命令处理程序代码
	m_pSpectroDevGDI->GDI_EnableSpectrogramMkr(true, true);
	m_pSpectroDevGDI->GDI_EnableSpectrogramMkrLine(true);	
				
	m_pSpectroDevGDI->GDI_UseSpectrogramMkr(SPECTROGRAM_MKR_X);
	m_IsMark = TRUE;
}

void CSpectroView::OnMarkoff()
{
	// TODO: 在此添加命令处理程序代码
	m_pSpectroDevGDI->GDI_EnableSpectrogramMkr(false, false);
	m_pSpectroDevGDI->GDI_EnableSpectrogramMkrLine(false);

	m_IsMark = FALSE;
}

void CSpectroView::OnMarkX()
{
	// TODO: 在此添加命令处理程序代码
	m_pSpectroDevGDI->GDI_UseSpectrogramMkr(SPECTROGRAM_MKR_X);
}

void CSpectroView::OnMarkY()
{
	// TODO: 在此添加命令处理程序代码
	m_pSpectroDevGDI->GDI_UseSpectrogramMkr(SPECTROGRAM_MKR_Y);
}

void CSpectroView::OnSpectroStop()
{
	// TODO: 在此添加命令处理程序代码
	m_IsPlay = FALSE;
}

void CSpectroView::OnSpectroStart()
{
	// TODO: 在此添加命令处理程序代码
	m_IsPlay = TRUE;
}
void CSpectroView::WaveAdjustRateX(const double *pdData,int nDataLen)
{
	int pixel = 0;
	int Oldpixel = 0;
	double dWaveWidth = (static_cast<double>(m_rc.right-m_rc.left-m_RectBorder.right-m_RectBorder.left))/nDataLen;

	for (int j=0; j<nDataLen; j++)
	{
		
		pixel = static_cast<int>(dWaveWidth*(j+1));

		if(pixel!=Oldpixel)
		{
			Oldpixel = pixel;
			m_pSpectDataPixelX[pixel]=pdData[j]; 
			
		}
		else
		{
			if(m_pSpectDataPixelX[pixel]<pdData[j])
				m_pSpectDataPixelX[pixel]=pdData[j];
		}
	}
}
void CSpectroView::WaveAdjustRateY(int nCount)
{
	for(int i=0;i<m_nDataCount;i++)
	{
		m_pSpectDataPixelY[i]=-999;
		for(int j=0;j<nCount;j++)
		{
			if(m_pSpectDataPixelY[i]<m_pSpectDataPixel[j][i])
				m_pSpectDataPixelY[i]=m_pSpectDataPixel[j][i];
		}
	}
}

void CSpectroView::OnFast()
{
	// TODO: 在此添加命令处理程序代码
	m_nCount=m_nCount-10;

	if (m_nCount<0)
	{
		m_nCount =0;
	}
}


void CSpectroView::OnSlow()
{
	// TODO: 在此添加命令处理程序代码
	m_nCount=m_nCount+10;
	if(m_nCount>500)
	{
		m_nCount =500;
	}
}


void CSpectroView::OnRefresh()
{
	// TODO: 在此添加命令处理程序代码

	SetSpectTime(m_nTimes, FALSE);
}


void CSpectroView::OnBtnGray()
{
	// TODO: 在此添加命令处理程序代码

	int r= 0;
	int g=0;
	int b=0;
	for (int i=0;i<PALETTE_NUM;i++)
	{
		m_ColorSpec[i] = RGB(r,g,b);
		r=r+2;
		g=g+2;
		b=b+2;

		m_dzLevel[i] =(double) (-20+i*0.78125);
	}
	m_dzLevel[0] = -999999.0;
}
void CSpectroView::OnBtnHot()
{
	// TODO: 在此添加命令处理程序代码
	int r = 255, g = 0, b = 0;
	int n = 256 / PALETTE_NUM * 4;
	int step = 0;
	for ( int i = 0 ; i < PALETTE_NUM; i++ )
	{
		m_ColorSpec[PALETTE_NUM-1-i] = RGB(r,g,b);

		switch ( step )
		{
		case 0:
			g += n;
			if ( g > 255 )
			{
				g = 255;
				step++;
			}
			break;
		case 1:
			r -= n;
			if ( r < 0 )
			{
				r = 0;
				step++;
			}
			break;
		case 2:
			b += n;
			if ( b > 255 )
			{
				b = 255;
				step++;
			}
			break;
		case 3:
			g -= n;
			if ( g < 0 )
				g = 0;
			break;
		}
		m_dzLevel[i] =(double) (-20+i*0.78125);
	}
	m_dzLevel[0] = -999999.0;
}
