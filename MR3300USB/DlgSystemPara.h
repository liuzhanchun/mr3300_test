#pragma once


// CDlgSystemPara �Ի���

class CDlgSystemPara : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSystemPara)

public:
	CDlgSystemPara(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSystemPara();

// �Ի�������
	enum { IDD = IDD_SYSTEMPARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnTemp();
	virtual  BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnTools();
	virtual BOOL PreTranslateMessage(MSG* pMsg);  
};
