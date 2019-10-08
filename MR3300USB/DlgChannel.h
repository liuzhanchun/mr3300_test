#pragma once
#include "afxcmn.h"
#include <iostream>
#include <vector>
#include "afxwin.h"
#include "Common.h"
#include "DialogScroll.h"
using namespace std;
// CDlgChannel 对话框

class CDlgChannel : public CDialogScroll
{
	DECLARE_DYNAMIC(CDlgChannel)

public:
	CDlgChannel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChannel();

// 对话框数据
	enum { IDD = IDD_CHANNEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

private:
	void InitTemplateList();
	void ReflushList();
	void GetTaskItem();
	void SetTaskItem(TASK_ITEM ti);
	int  GetSelectIndex();
	vector<TASK_ITEM> m_vtTask;
	TASK_ITEM m_TaskItem;
	__int64 m_nCenter;
	__int64 m_nBW;
	int m_nAtt;
	CString m_sMode;
	int m_nNoise;

public:
	CListCtrl m_ListTemplate;
	CComboBox m_COMTableBW;
	CComboBox m_COMTableAtt;
	CComboBox m_COMTableMode;
	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
	afx_msg void OnBnClickedTableSadd();



	afx_msg void OnBnClickedBtnSave();
	void SaveTask(CString szPath);
	afx_msg void OnBnClickedBtnImport();
	void LoadTask(CString szPath);
	afx_msg void OnBnClickedTableDelete();
	afx_msg void OnBnClickedTableEmpty();
	afx_msg void OnBnClickedTableSend();
	afx_msg void OnBnClickedTableAdd();
	afx_msg void OnBnClickedTableMod();
};

extern CDlgChannel *g_pDlgChannel;
