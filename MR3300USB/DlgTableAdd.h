#pragma once
#include "DataDef.h"

// CDlgTableAdd 对话框

class CDlgTableAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTableAdd)

public:
	CDlgTableAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTableAdd();

	vector<__int64> m_vtTaskItem;
	//TASK_ITEM m_TaskItem;

// 对话框数据
	enum { IDD = IDD_TABLE_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
