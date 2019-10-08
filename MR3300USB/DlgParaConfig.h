#pragma once
#include "afxwin.h"
#include "NumEdit.h"
#include "DialogScroll.h"
// CDlgParaConfig 对话框
class CMR3300USBView;
class CDlgParaConfig : public CDialogScroll
{
	DECLARE_DYNAMIC(CDlgParaConfig)

public:
	CDlgParaConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgParaConfig();

// 对话框数据
	enum { IDD = DLG_PARACONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	CMR3300USBView* m_pView;


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);  
	virtual BOOL OnInitDialog();
	void SetViewPtr(CMR3300USBView* pView);
	void Detection(BOOL bMode);
	virtual void OnOK();

private:
	CNumEdit m_CenterFre;
	void SetSignal(double signalFre,double signalAmp,int MedMode);
public:
	void ChangeDispForMode(int nMode);
	afx_msg void OnBnClickedBtbCenterfre();
	afx_msg void OnBnClickedNormal();
	afx_msg void OnBnClickedMax();
	afx_msg void OnBnClickedMin();
	afx_msg void OnBnClickedAvg();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedBtnRef();
	afx_msg void OnCbnSelchangeCmbSpan();
	CComboBox m_ComSpan;
	afx_msg void OnBnClickedCkSpec();
	afx_msg void OnBnClickedCkAud();
	CComboBox m_Com_RFMode;
	afx_msg void OnCbnSelchangeComRfmode();
	afx_msg void OnCbnSelchangeComDem();
	CComboBox m_Com_BW;
	afx_msg void OnCbnSelchangeComBw();
	CComboBox m_Com_Step;
	afx_msg void OnCbnSelchangeComStep();
	afx_msg void OnBnClickedBtnStartfre();
	afx_msg void OnBnClickedBtnStopfre();
	CComboBox m_ComAttRF;
	CComboBox m_ComAttIF;
	afx_msg void OnCbnSelchangeComAttrf();
	afx_msg void OnCbnSelchangeComAttif();
	afx_msg void OnBnClickedCkSpectro();
	CComboBox m_Com_Dem;
};
extern CDlgParaConfig *g_pDlgParaConfig;
