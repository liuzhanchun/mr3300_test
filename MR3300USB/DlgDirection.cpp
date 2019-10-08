// DlgDirection.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgDirection.h"
#include "afxdialogex.h"
#include "RemoteData.h"
CDlgDirection *g_pDlgDirection= NULL; 

// CDlgDirection 对话框

IMPLEMENT_DYNAMIC(CDlgDirection, CDialogScroll)

CDlgDirection::CDlgDirection(CWnd* pParent /*=NULL*/)
	: CDialogScroll(CDlgDirection::IDD, pParent)
{

}

CDlgDirection::~CDlgDirection()
{
}

void CDlgDirection::DoDataExchange(CDataExchange* pDX)
{
	CDialogScroll::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_DFMODE, m_ComDFMode);
	DDX_Control(pDX, IDC_COM_DFCOUNT, m_ComDFCount);
}


BEGIN_MESSAGE_MAP(CDlgDirection, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SETANT, &CDlgDirection::OnBnClickedBtnSetant)
	ON_CBN_SELCHANGE(IDC_COM_DFMODE, &CDlgDirection::OnCbnSelchangeComDfmode)
	ON_CBN_SELCHANGE(IDC_COM_DFCOUNT, &CDlgDirection::OnCbnSelchangeComDfcount)
	ON_BN_CLICKED(IDC_BTN_INTTIME, &CDlgDirection::OnBnClickedBtnInttime)
	ON_BN_CLICKED(IDC_BTN_SWTIME, &CDlgDirection::OnBnClickedBtnSwtime)
	ON_BN_CLICKED(IDC_BTN_DFTHR, &CDlgDirection::OnBnClickedBtnDfthr)
END_MESSAGE_MAP()


// CDlgDirection 消息处理程序

BOOL CDlgDirection::OnInitDialog()
{
	__super::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgDirection::OnOK()
{
	return;
}


void CDlgDirection::OnBnClickedBtnSetant()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	CString sz;

	GetDlgItem(IDC_EDIT_SETANT)->GetWindowText(sz);
	int nAntSel = _ttoi(sz);

	sprintf(Cmd, "ANT:SEL:IND %d",nAntSel);
	g_pRemote->FastSendCmd(Cmd);

}


void CDlgDirection::OnCbnSelchangeComDfmode()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSelect = m_ComDFMode.GetCurSel();
	switch (nSelect)
	{
	case 0:
		g_pRemote->FastSendCmd("MEAS:DFIN:MODE NORMal");
		break;
	case 1:
		g_pRemote->FastSendCmd("MEAS:DFIN:MODE FEEBleness");
		break;
	case 2:
		g_pRemote->FastSendCmd("MEAS:DFIN:MODE GATe");
		break;
	}
}


void CDlgDirection::OnCbnSelchangeComDfcount()
{
	// TODO: 在此添加控件通知处理程序代码

	int nSelect = m_ComDFCount.GetCurSel();
	switch (nSelect)
	{
	case 0:
		g_pRemote->FastSendCmd("MEASure:DFINd:COUNt 64");
		break;
	case 1:
		g_pRemote->FastSendCmd("MEASure:DFINd:COUNt 128");
		break;
	case 2:
		g_pRemote->FastSendCmd("MEASure:DFINd:COUNt 256");
		break;
	case 3:
		g_pRemote->FastSendCmd("MEASure:DFINd:COUNt 512");
		break;
	case 4:
		g_pRemote->FastSendCmd("MEASure:DFINd:COUNt 1024");
		break;
	case 5:
		g_pRemote->FastSendCmd("MEASure:DFINd:COUNt 2048");
		break;
	}
}


void CDlgDirection::OnBnClickedBtnInttime()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	CString sz;

	GetDlgItem(IDC_EDIT_INTTIME)->GetWindowText(sz);
	int nIntTime = _ttoi(sz);

	sprintf(Cmd, "MEAS:DFIN:INT %dus",nIntTime);
	g_pRemote->FastSendCmd(Cmd);
}


void CDlgDirection::OnBnClickedBtnSwtime()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	CString sz;

	GetDlgItem(IDC_EDIT_SWTIME)->GetWindowText(sz);
	int nSWTime = _ttoi(sz);

	sprintf(Cmd, "MEAS:DFIN:SWI %dus",nSWTime);
	g_pRemote->FastSendCmd(Cmd);
}


void CDlgDirection::OnBnClickedBtnDfthr()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	CString sz;

	GetDlgItem(IDC_EDIT_DFTHR)->GetWindowText(sz);
	int nDFThr = _ttoi(sz);

	sprintf(Cmd, "MEAS:DFIN:THR %d",nDFThr);
	g_pRemote->FastSendCmd(Cmd);
}

BOOL CDlgDirection::PreTranslateMessage(MSG* pMsg)  
{  
	if(WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)     
	{       
		if(GetFocus()== GetDlgItem(IDC_EDIT_DFTHR)) 
		{  
			UpdateData(TRUE);
			OnBnClickedBtnDfthr();
			UpdateData(FALSE);

		}  

		if(GetFocus()== GetDlgItem(IDC_EDIT_SWTIME))  
		{
			UpdateData(TRUE);
			OnBnClickedBtnSwtime();
			UpdateData(FALSE);
		}
		if(GetFocus()== GetDlgItem(IDC_EDIT_INTTIME))  
		{
			UpdateData(TRUE);
			OnBnClickedBtnInttime();
			UpdateData(FALSE);
		}

		if(GetFocus()== GetDlgItem(IDC_EDIT_SETANT))  
		{
			UpdateData(TRUE);
			OnBnClickedBtnSetant();
			UpdateData(FALSE);
		}

		return true;
	} 
	return CDialogScroll::PreTranslateMessage(pMsg);
}