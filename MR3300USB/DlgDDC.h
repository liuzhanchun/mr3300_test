#pragma once
#include "afxwin.h"
#include "NumEdit.h"
#include "DialogScroll.h"
// CDlgDDC �Ի���

class CMR3300USBView;

class CDlgDDC : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDDC)

public:
	CDlgDDC(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDDC();

// �Ի�������
	enum { IDD = IDD_DDC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
};
extern CDlgDDC *g_pDlgDDC;

