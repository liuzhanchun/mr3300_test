#pragma once
#include "afxcmn.h"

// CDlgHelp �Ի���

class CDlgHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHelp)

public:
	CDlgHelp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHelp();

// �Ի�������
	enum { IDD = IDD_Help };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();



};
