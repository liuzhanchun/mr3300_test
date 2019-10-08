#pragma once
#include "DataDef.h"
#include "afxwin.h"

// CDlgTableMod �Ի���

class CDlgTableMod : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTableMod)

public:
	CDlgTableMod(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTableMod();


	void SetModItem(TASK_ITEM item);

	TASK_ITEM GetModItem();

// �Ի�������
	enum { IDD = IDD_TABLE_MOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


	TASK_ITEM m_ModItem;
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_ModBw;
	CComboBox m_ModMode;
	CComboBox m_ModAtt;
};

