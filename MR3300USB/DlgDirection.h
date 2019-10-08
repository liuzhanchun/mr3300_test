#pragma once
#include "afxcmn.h"
#include <iostream>
#include <vector>
#include "afxwin.h"
#include "Common.h"
#include "DialogScroll.h"
using namespace std;
// CDlgDirection �Ի���

class CDlgDirection : public CDialogScroll
{
	DECLARE_DYNAMIC(CDlgDirection)

public:
	CDlgDirection(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDirection();

// �Ի�������
	enum { IDD = IDD_DIRECTION };

protected:

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSetant();
	afx_msg void OnCbnSelchangeComDfmode();
	CComboBox m_ComDFMode;
	afx_msg void OnCbnSelchangeComDfcount();
	CComboBox m_ComDFCount;
	afx_msg void OnBnClickedBtnInttime();
	afx_msg void OnBnClickedBtnSwtime();
	afx_msg void OnBnClickedBtnDfthr();
	virtual BOOL PreTranslateMessage(MSG* pMsg);  
};

extern CDlgDirection *g_pDlgDirection;

