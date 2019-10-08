#pragma once


// CDlgSystemPara 对话框

class CDlgSystemPara : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSystemPara)

public:
	CDlgSystemPara(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSystemPara();

// 对话框数据
	enum { IDD = IDD_SYSTEMPARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnTemp();
	virtual  BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnTools();
	virtual BOOL PreTranslateMessage(MSG* pMsg);  
};
