#pragma once
#include "DataDef.h"

// CDlgTableAdd �Ի���

class CDlgTableAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTableAdd)

public:
	CDlgTableAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTableAdd();

	vector<__int64> m_vtTaskItem;
	//TASK_ITEM m_TaskItem;

// �Ի�������
	enum { IDD = IDD_TABLE_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
