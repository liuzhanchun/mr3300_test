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

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include"RemoteData.h"
#include "UdpServer.h"

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	void SetModeSelectContextVisiable(BOOL IsVisiable);
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
private:
	void SetConBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableConBtn = bEnable;
	}
	void SetDisConBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableDisConBtn = bEnable;
	}
	void SetRXFFMBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableRXFFMBtn = bEnable;
	}
	void SetRXPscanBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableRXPscanBtn = bEnable;
	}
	void SetRXFPSCANBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableRXFPSCANBtn = bEnable;
	}
	void SetHelpBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableHelpBtn = bEnable;
	}
	void SetMSBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableMSBtn = bEnable;
	}

	void SetFABtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableFABtn = bEnable;
	}

	void SetIP3BtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableIP3Btn = bEnable;
	}

	void SetIP2BtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableIP2Btn = bEnable;
	}

	void SetFIFRBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableFIFRBtn = bEnable;
	}

	void SetSIFRBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableSIFRBtn = bEnable;
	}

	void SetFIRBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableFIRBtn = bEnable;
	}

	void SetSIRBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableSIRBtn = bEnable;
	}

	void SetSSBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableSSBtn = bEnable;
	}

	void SetLMBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableLMBtn = bEnable;
	}

	void SetNFBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnableNFBtn = bEnable;
	}

	void SetPNBtnSatate(BOOL bEnable = FALSE)
	{
		m_bEnablePNBtn = bEnable;
	}

	BOOL m_bEnableConBtn;
	BOOL m_bEnableDisConBtn;
	BOOL m_bEnableRXFFMBtn;
	BOOL m_bEnableRXPscanBtn;
	BOOL m_bEnableRXFPSCANBtn;
	BOOL m_bEnableHelpBtn;
	BOOL m_bEnableMSBtn;
	BOOL m_bEnableFABtn;
	BOOL m_bEnableIP3Btn;
	BOOL m_bEnableIP2Btn;
	BOOL m_bEnableFIFRBtn;
	BOOL m_bEnableSIFRBtn;
	BOOL m_bEnableFIRBtn;
	BOOL m_bEnableSIRBtn;
	BOOL m_bEnableSSBtn;
	BOOL m_bEnableLMBtn;
	BOOL m_bEnableNFBtn;
	BOOL m_bEnablePNBtn;

	void ReadConfigIni();
public:

	afx_msg void OnClose();

	afx_msg void OnBtnConnect();
	afx_msg void OnUpdateBtnConnect(CCmdUI *pCmdUI);

	afx_msg void OnBtnDisconnect();
	afx_msg void OnUpdateBtnDisconnect(CCmdUI *pCmdUI);

	afx_msg void OnBtnRxffm();
	afx_msg void OnUpdateBtnRxffm(CCmdUI *pCmdUI);

	afx_msg void OnBtnRxpscan();
	afx_msg void OnUpdateBtnRxpscan(CCmdUI *pCmdUI);


	afx_msg void OnBtnFpscan();
	afx_msg void OnUpdateBtnFpscan(CCmdUI *pCmdUI);
	afx_msg void OnBtnHelp();
	afx_msg void OnUpdateBtnHelp(CCmdUI *pCmdUI);
	afx_msg void OnBtnMs();
	afx_msg void OnUpdateBtnMs(CCmdUI *pCmdUI);
	afx_msg void OnBtnFa();
	afx_msg void OnUpdateBtnFa(CCmdUI *pCmdUI);
	afx_msg void OnBtnIp3();
	afx_msg void OnUpdateBtnIp3(CCmdUI *pCmdUI);
	afx_msg void OnBtnIp2();
	afx_msg void OnUpdateBtnIp2(CCmdUI *pCmdUI);
	afx_msg void OnBtnFifr();
	afx_msg void OnUpdateBtnFifr(CCmdUI *pCmdUI);
	afx_msg void OnBtnSifr();
	afx_msg void OnUpdateBtnSifr(CCmdUI *pCmdUI);
	afx_msg void OnBtnFir();
	afx_msg void OnUpdateBtnFir(CCmdUI *pCmdUI);
	afx_msg void OnBtnSir();
	afx_msg void OnUpdateBtnSir(CCmdUI *pCmdUI);
	afx_msg void OnBtnSs();
	afx_msg void OnUpdateBtnSs(CCmdUI *pCmdUI);
	afx_msg void OnBtnLm();
	afx_msg void OnUpdateBtnLm(CCmdUI *pCmdUI);
	afx_msg void OnBtnNf();
	afx_msg void OnUpdateBtnNf(CCmdUI *pCmdUI);
	afx_msg void OnBtnPn();
	afx_msg void OnUpdateBtnPn(CCmdUI *pCmdUI);
};


