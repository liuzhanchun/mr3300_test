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

// MR3300USBView.h : CMR3300USBView 类的接口
//

#pragma once
#include "MR3300USBDoc.h"
#include "DevGDI.h"
#include "PcmPlayer.h"
#include <Map>
class CMR3300USBView : public CView
{
protected: // 仅从序列化创建
	CMR3300USBView();
	DECLARE_DYNCREATE(CMR3300USBView)

// 特性
public:
	CMR3300USBDoc* GetDocument() const;

// 操作
public:
	void Start();
	void SetTraceVisable(UINT nTrace, BOOL IsVisable);
	void SetDataVisable(CString DataMode, BOOL IsVisable);
	void ResetTrace();
	void SetRef(int ref);
	void SetRange(double range);
	BOOL m_bFirst;
	enum ENVM_WAVE {
		WAVE_NORMAL = 0,
		WAVE_MAX = 1,
		WAVE_MIN = 2,
		WAVE_AVG = 3,
		WAVE_COUNT,
	};

private:

	void InitGDI(HWND& hWnd, const CRect& rc);

	static UINT ThreadData(LPVOID lp);
	static UINT ThreadAud(LPVOID lp);
	static UINT ThreadWave(LPVOID lp);

	void DrawData();
	void DrawWave();
	void ReadConfigIni();
	CDevGDI* m_pDevGDI;
	CWinThread* m_pThreadData;
	CWinThread* m_pThreadAud;
	CWinThread* m_pThreadWave;

	WaveStatus Status;
	BOOL m_bDispITU;
	BOOL m_bDispMESS;
	BOOL m_bDispLevel;
	BOOL m_bAud;

	STRUCT_HEAD_DATA m_Audfile_head;
	STRUCT_GENERIC_DATA m_Audgeneric_data;
	STRUCT_AUDIO_HEAD m_audio_data;
	bool m_IsPeakSearch;
	bool m_IsNormalSearch;

	CPcmPlayer *player;
	CPcmPlayer *playerD;
	BOOL m_bDraw;
	CCriticalSection *m_pLock;

	UINT64 m_nSession;
	void WaveAdjustRateY(int nCount);
	void WaveAdjustRateX(const double *pdData,int nDataLen);
	CStringArray ArrayFreqUnit;

protected:
	static const int BUF_SIZE =350000;
	double m_WaveBuf[WAVE_COUNT][BUF_SIZE];

	double m_NewValue[BUF_SIZE];

	double m_dDataBuf[BUF_SIZE];
	int m_WaveLen[WAVE_COUNT];
	BOOL m_WaveHold[WAVE_COUNT];
	UINT m_AvgKey;	// 加权平均值
	int m_nPointNum;
	
	double m_fOldData[BUF_SIZE];

	double m_pSpectDataPixel[10][BUF_SIZE];
	__int64 m_nFreq;
	float m_fLevel;
	STRUCT_ITU_DATA m_ITU;


	double m_dMarkDataBuf[3000];
	__int64 m_nMarkFreq[3000];

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:

// 实现
public:
	virtual ~CMR3300USBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPoint m_MarPoint;
	int m_leftboard;
	int m_rightboard;
	int m_right;

	__int64 m_StartFreq;
	__int64 m_StopFreq;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPeaksearchon();
	afx_msg void OnPeaksearchoff();
	afx_msg void OnNormalmarkon();
	afx_msg void OnNormalmarkoff();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNordraw();
	afx_msg void OnFastdraw();
	afx_msg void OnHighEndOn();
	afx_msg void OnHighEndOff();
	afx_msg void OnEnableGrid();
	afx_msg void OnDisableGrid();
};

#ifndef _DEBUG  // MR3300USBView.cpp 中的调试版本
inline CMR3300USBDoc* CMR3300USBView::GetDocument() const
   { return reinterpret_cast<CMR3300USBDoc*>(m_pDocument); }
#endif

