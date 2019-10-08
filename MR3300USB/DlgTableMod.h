#pragma once
#include "DataDef.h"
#include "afxwin.h"

// CDlgTableMod 对话框

class CDlgTableMod : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTableMod)

public:
	CDlgTableMod(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTableMod();


	void SetModItem(TASK_ITEM item);

	TASK_ITEM GetModItem();

// 对话框数据
	enum { IDD = IDD_TABLE_MOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


	TASK_ITEM m_ModItem;
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_ModBw;
	CComboBox m_ModMode;
	CComboBox m_ModAtt;
};

