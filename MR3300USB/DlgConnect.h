#pragma once
#include "afxcmn.h"


// CDlgConnect 对话框

class CDlgConnect : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConnect)

public:
	CDlgConnect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgConnect();

// 对话框数据
	enum { IDD = IDD_CONNECT_NET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedOk();
	CIPAddressCtrl m_TCPIPADDRESS;
	CIPAddressCtrl m_UDPIPADDRESS;

	CString m_szTcpIP;
	CString m_szUdpIP;
	int m_nPort;
};
