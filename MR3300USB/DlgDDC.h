#pragma once
#include "afxwin.h"
#include "NumEdit.h"
#include "DialogScroll.h"
// CDlgDDC 对话框

class CMR3300USBView;

class CDlgDDC : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDDC)

public:
	CDlgDDC(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDDC();

// 对话框数据
	enum { IDD = IDD_DDC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
};
extern CDlgDDC *g_pDlgDDC;

