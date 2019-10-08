#pragma once
#include "DevGDI.h"

// CSpectroView 视图

class CSpectroView : public CView
{
	DECLARE_DYNCREATE(CSpectroView)

protected:
	CSpectroView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSpectroView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	void Start();
	void SetDevGDI(BOOL mode);
	void SetSpectPlay( BOOL IsPlay );
	void SetUseMarker( BYTE ucType );
	SPECT_MARKER_DATA* ReadMark();

	SPECT_MARKER_DATA m_SpectMarker;
private:
	CWinThread* m_pSpetroThread;
	CWinThread* m_pSpetroDataThread;

	static UINT ThreadSpetro(LPVOID lp);
	static UINT ThreadSpetroData(LPVOID lp);


	void InitGDI(HWND& hWnd, const CRect& rc);
	WaveStatus m_Status;


	CDevGDI* m_pSpectroDevGDI;

	void DrawSpectro();
	void DataSpectro();
	CRect m_RectBorder;				// 边框大小
	CRect m_RectBorderDT;			// 边框大小修正

	static const int PALETTE_NUM = 128;  //调色板数
	double m_dzLevel[PALETTE_NUM];
	COLORREF m_ColorSpec[PALETTE_NUM];


	////////////////////////////////////////////
	SYSTEMTIME* m_pTMData;
	SYSTEMTIME* m_pTMDraw;

	double* m_pSpectMarker;
	double* m_pSpectData;
	double* m_pSpectDataPixelX;
	double* m_pSpectDataPixelY;
	//double* m_pSpectDataPixel;
	double* m_pSpectDraw;
	CRect m_LocalRect;
	UINT m_nCurTime;		// 当前为第几场
	UINT m_nTimes;			// 存储多少场波形
	BOOL m_IsPlay;			// 是否进行播放
	BOOL m_IsMark;			// 光标开关

	//////////////////////////////////////////////
	//CMutex m_Mutex;
	//CCriticalSection *m_pLock;
	void SetSpectTime( UINT nTime, BOOL IsUseLock );
	UINT m_nDataCount;			// 数据包长度

	void SetByStatus();
	BOOL	m_bMode;
	
	const static int m_nDotNum = 3000;
	const static int m_nTime = 500;
	double m_pSpectDataPixel[m_nTime][m_nDotNum];
	void WaveAdjustRateX(const double *pdData,int nDataLen);
	void WaveAdjustRateY(int nCount);
	CRect m_rc;

	double m_fOldData[319200];

	int m_nCount;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMarkon();
	afx_msg void OnMarkoff();
	afx_msg void OnMarkX();
	afx_msg void OnMarkY();
	afx_msg void OnSpectroStop();
	afx_msg void OnSpectroStart();
	afx_msg void OnFast();
	afx_msg void OnSlow();
	afx_msg void OnRefresh();
	afx_msg void OnBtnGray();
	afx_msg void OnBtnHot();
};


