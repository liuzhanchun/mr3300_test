// DlgResponse.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgResponse.h"
#include "afxdialogex.h"
#include "RemoteData.h"

// CDlgResponse 对话框

IMPLEMENT_DYNAMIC(CDlgResponse, CDialogEx)

CDlgResponse::CDlgResponse(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgResponse::IDD, pParent)
{

}

CDlgResponse::~CDlgResponse()
{
}

void CDlgResponse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STARTRESP, m_StartResp);
	DDX_Control(pDX, IDC_STOPRESP, m_StopResp);
	DDX_Control(pDX, IDC_COM_RADIO, m_Com_Radio);
}


BEGIN_MESSAGE_MAP(CDlgResponse, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_RESP, &CDlgResponse::OnBnClickedBtnResp)
	ON_BN_CLICKED(IDC_BTN_ALLRESP, &CDlgResponse::OnBnClickedBtnAllresp)
	ON_BN_CLICKED(IDC_BTN_IFRESP, &CDlgResponse::OnBnClickedBtnIfresp)
	ON_BN_CLICKED(IDOK, &CDlgResponse::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COM_RADIO, &CDlgResponse::OnCbnSelchangeComRadio)
	ON_BN_CLICKED(IDC_BTN_CAL, &CDlgResponse::OnBnClickedBtnCal)
END_MESSAGE_MAP()


// CDlgResponse 消息处理程序




void CDlgResponse::OnBnClickedBtnResp()
{
	// TODO: 在此添加控件通知处理程序代码

	char Cmd[150];
	CString sz;

	GetDlgItem(IDC_STARTRESP)->GetWindowText(sz); 
	int nResp = _ttoi(sz);
	sprintf(Cmd, "SYSTem:RESPonse:STARt %d",(int)(nResp-1));
	g_pRemote->FastSendCmd(Cmd);

	GetDlgItem(IDC_STOPRESP)->GetWindowText(sz); 

	nResp = _ttoi(sz);
	sprintf(Cmd, "SYSTem:RESPonse:STOP %d",(int)(nResp-1));
	g_pRemote->FastSendCmd(Cmd);
}


void CDlgResponse::OnBnClickedBtnAllresp()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	sprintf(Cmd, "SYSTem:RESPonse:ALL");
	g_pRemote->FastSendCmd(Cmd);
}


void CDlgResponse::OnBnClickedBtnIfresp()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	sprintf(Cmd, "SYSTem:RESPonse:FAST");
	g_pRemote->FastSendCmd(Cmd);
}
BOOL CDlgResponse::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_StartResp.SetCurSel(0);
	m_StopResp.SetCurSel(23);

	return TRUE; 
}


void CDlgResponse::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CDlgResponse::OnCbnSelchangeComRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sz;
	char Cmd[50];
	UINT RFPN = 0;

	int nSelect = m_Com_Radio.GetCurSel();
	switch (nSelect)
	{
	case 0:
		RFPN = 1;
		break;
	case 1:
		RFPN = 2;
		break;
	case 2:
		RFPN = 3;
		break;
	case 3:
		RFPN = 4;
		break;
	}

	sprintf(Cmd, "SYSTem:RFPN %d",(int)(RFPN));
	g_pRemote->FastSendCmd(Cmd);
}


void CDlgResponse::OnBnClickedBtnCal()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	sprintf(Cmd, "SYSTem:RESPonse:CAL");
	g_pRemote->FastSendCmd(Cmd);
}
