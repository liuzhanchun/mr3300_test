#pragma once
#include "afxwin.h"


// CDlgResponse �Ի���

class CDlgResponse : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgResponse)

public:
	CDlgResponse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgResponse();

// �Ի�������
	enum { IDD = IDD_RESP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
