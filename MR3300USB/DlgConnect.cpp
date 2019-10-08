// DlgConnect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgConnect.h"
#include "afxdialogex.h"


// CDlgConnect �Ի���

IMPLEMENT_DYNAMIC(CDlgConnect, CDialogEx)

CDlgConnect::CDlgConnect(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConnect::IDD, pParent)
{

}

CDlgConnect::~CDlgConnect()
{
}

void CDlgConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCPADDRESS, m_TCPIPADDRESS);
	DDX_Control(pDX, IDC_UDPADDRESS, m_UDPIPADDRESS);
}


BEGIN_MESSAGE_MAP(CDlgConnect, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgConnect::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgConnect ��Ϣ�������

BOOL CDlgConnect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString upd;  
	CString tcp; 
	tcp = L"192.168.0.138";
	upd = L"192.168.0.226";

	LONG lValue = 0;  
	//�ȶ�ȡ���ݵĳ���  
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTest"), nullptr, &lValue);  
	TCHAR *pBuf = new TCHAR[lValue];  
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTest"), pBuf, &lValue);  

	HKEY hKey = nullptr;  
	DWORD dwTpye = REG_SZ;  
	DWORD dwValue = MAX_PATH;//�����Сһ��Ҫ�������,��������(234)  
	TCHAR data[MAX_PATH];
	LONG lRet = 0;  
	//��ע���  
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTest"),0, KEY_ALL_ACCESS,&hKey);  
	//��ע���                                          //valuename      //����value���� //���ݻ����� //��������С  
	if (ERROR_SUCCESS == (lRet = RegQueryValueEx(hKey, TEXT("tcp_ip"), 0, &dwTpye, (LPBYTE)data, &dwValue)))  
	{  
		tcp.Format(data);
	
	}  
	if (ERROR_SUCCESS == (lRet = RegQueryValueEx(hKey, TEXT("udp_ip"), 0, &dwTpye, (LPBYTE)data, &dwValue)))  
	{  
		upd.Format(data);

	}  
	GetDlgItem(IDC_NETPORT)->SetWindowText(L"5025");
	GetDlgItem(IDC_TCPADDRESS)->SetWindowText(tcp);
	GetDlgItem(IDC_UDPADDRESS)->SetWindowText(upd);
	m_nPort = 5025;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgConnect::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_TCPIPADDRESS.GetWindowText(m_szTcpIP);
	m_UDPIPADDRESS.GetWindowText(m_szUdpIP);

	CString sz;
	GetDlgItem(IDC_NETPORT)->GetWindowText(sz);

	m_nPort = _ttoi(sz);

	HKEY hKey = nullptr;  
	//�����ɹ�,���õ�hKey,һ��ע�����,�����������ע���  
	if (ERROR_SUCCESS != RegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTest"), &hKey))  
	{   
		goto end;
	}  
	//д��ע���                                  //����  //���� //�ַ�����  
	//ֻ��д��һ��value  
	if (ERROR_SUCCESS != RegSetValue(hKey,nullptr,REG_SZ,TEXT("Test"),4))  
	{  
		goto end;  
	}  
	if (hKey ==nullptr)  
	{  
		goto end;  
	}  

	LONG lRet = 0;  
	LPSTR lpPath = (LPSTR)(LPCTSTR)m_szTcpIP;  
	//�����������д������Value                      //����            //����        //����  
	if (ERROR_SUCCESS != (lRet = RegSetValueEx(hKey, TEXT("tcp_ip"), 0, REG_SZ, (CONST BYTE *)lpPath, m_szTcpIP.GetLength()*2)))  
	{  
		goto end;  
	}  

	lRet = 0;  
	lpPath = (LPSTR)(LPCTSTR)m_szUdpIP;  
	//�����������д������Value                      //����            //����        //����  
	if (ERROR_SUCCESS != (lRet = RegSetValueEx(hKey, TEXT("udp_ip"), 0, REG_SZ, (CONST BYTE *)lpPath, m_szUdpIP.GetLength()*2)))  
	{  
		goto end;  
	}  
	RegCloseKey(hKey);  
end:

	CDialogEx::OnOK();
}
