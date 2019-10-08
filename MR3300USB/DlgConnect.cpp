// DlgConnect.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgConnect.h"
#include "afxdialogex.h"


// CDlgConnect 对话框

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


// CDlgConnect 消息处理程序

BOOL CDlgConnect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString upd;  
	CString tcp; 
	tcp = L"192.168.0.138";
	upd = L"192.168.0.226";

	LONG lValue = 0;  
	//先读取数据的长度  
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTest"), nullptr, &lValue);  
	TCHAR *pBuf = new TCHAR[lValue];  
	RegQueryValue(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTest"), pBuf, &lValue);  

	HKEY hKey = nullptr;  
	DWORD dwTpye = REG_SZ;  
	DWORD dwValue = MAX_PATH;//这个大小一定要先求出来,否则会出错(234)  
	TCHAR data[MAX_PATH];
	LONG lRet = 0;  
	//打开注册表  
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTest"),0, KEY_ALL_ACCESS,&hKey);  
	//读注册表                                          //valuename      //返回value类型 //数据缓存区 //缓存区大小  
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
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgConnect::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TCPIPADDRESS.GetWindowText(m_szTcpIP);
	m_UDPIPADDRESS.GetWindowText(m_szUdpIP);

	CString sz;
	GetDlgItem(IDC_NETPORT)->GetWindowText(sz);

	m_nPort = _ttoi(sz);

	HKEY hKey = nullptr;  
	//创建成功,将得到hKey,一个注册表句柄,用于下面操作注册表  
	if (ERROR_SUCCESS != RegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SoftWare\\MyTest"), &hKey))  
	{   
		goto end;
	}  
	//写入注册表                                  //类型  //名称 //字符个数  
	//只能写入一个value  
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
	//这个函数可以写入更多的Value                      //名称            //类型        //数据  
	if (ERROR_SUCCESS != (lRet = RegSetValueEx(hKey, TEXT("tcp_ip"), 0, REG_SZ, (CONST BYTE *)lpPath, m_szTcpIP.GetLength()*2)))  
	{  
		goto end;  
	}  

	lRet = 0;  
	lpPath = (LPSTR)(LPCTSTR)m_szUdpIP;  
	//这个函数可以写入更多的Value                      //名称            //类型        //数据  
	if (ERROR_SUCCESS != (lRet = RegSetValueEx(hKey, TEXT("udp_ip"), 0, REG_SZ, (CONST BYTE *)lpPath, m_szUdpIP.GetLength()*2)))  
	{  
		goto end;  
	}  
	RegCloseKey(hKey);  
end:

	CDialogEx::OnOK();
}
