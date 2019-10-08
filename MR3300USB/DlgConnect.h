#pragma once
#include "afxcmn.h"


// CDlgConnect �Ի���

class CDlgConnect : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConnect)

public:
	CDlgConnect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgConnect();

// �Ի�������
	enum { IDD = IDD_CONNECT_NET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
