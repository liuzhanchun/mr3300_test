#pragma once
#include "afxwin.h"


// CDlgResponse 对话框

class CDlgResponse : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgResponse)

public:
	CDlgResponse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgResponse();

// 对话框数据
	enum { IDD = IDD_RESP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	CComboBox m_StartResp;
	CComboBox m_StopResp;
	afx_msg void OnBnClickedBtnResp();
	afx_msg void OnBnClickedBtnAllresp();
	afx_msg void OnBnClickedBtnIfresp();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComRadio();
	CComboBox m_Com_Radio;
	afx_msg void OnBnClickedBtnCal();
};
