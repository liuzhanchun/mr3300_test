#pragma once
#include "afxcmn.h"
#include <iostream>
#include <vector>
#include "afxwin.h"
#include "Common.h"
#include "DialogScroll.h"
using namespace std;

// CDlgInterPhone �Ի���

class CDlgInterPhone : public CDialogScroll
{
	DECLARE_DYNAMIC(CDlgInterPhone)

public:
	CDlgInterPhone(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInterPhone();

	void DTMessage(STRUCT_DT_FRAME DT,bool IsSwitch);

// �Ի�������
	enum { IDD = IDD_INTERPHONE };

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCkMessage();
};

extern CDlgInterPhone *g_pDlgInterPhone;
