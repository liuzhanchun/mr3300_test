// DlgSystemPara.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgSystemPara.h"
#include "afxdialogex.h"
#include "RemoteData.h"

// CDlgSystemPara 对话框

IMPLEMENT_DYNAMIC(CDlgSystemPara, CDialogEx)

CDlgSystemPara::CDlgSystemPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSystemPara::IDD, pParent)
{

}

CDlgSystemPara::~CDlgSystemPara()
{
}

void CDlgSystemPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSystemPara, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSystemPara::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_TEMP, &CDlgSystemPara::OnBnClickedBtnTemp)
	ON_BN_CLICKED(IDC_BTN_TOOLS, &CDlgSystemPara::OnBnClickedBtnTools)
END_MESSAGE_MAP()


// CDlgSystemPara 消息处理程序
BOOL CDlgSystemPara::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int nValue = CCommon::ReadRegQueryValue();
	CString Valuesz;
	Valuesz.Format(_T("%d"),nValue);
	GetDlgItem(IDC_EDIT_SYS_TOOLS)->SetWindowText(Valuesz);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSystemPara::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDlgSystemPara::OnBnClickedBtnTemp()
{
	// TODO: 在此添加控件通知处理程序代码

	char cBuf[200] = { 0 };
	int temp =0;
	g_pRemote->FastQueryStatus("HARDware:TEMPerature?", cBuf, 5000);



	int num = MultiByteToWideChar(0, 0,cBuf, -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0,cBuf, -1, wide, num);
	

	GetDlgItem(IDC_EDIT_TEMP)->SetWindowText(wide);
}


void CDlgSystemPara::OnBnClickedBtnTools()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sz;
	GetDlgItem(IDC_EDIT_SYS_TOOLS)->GetWindowText(sz);

	int nValue = _ttoi(sz);
	if((nValue<801)&&(nValue>399))
	{
		CCommon::WriteRegQueryValue(nValue);
	}

}
BOOL CDlgSystemPara::PreTranslateMessage(MSG* pMsg)  
{  
	if(WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)     
	{       
		if(GetFocus()== GetDlgItem(IDC_EDIT_SYS_TOOLS)) 
		{  
			UpdateData(TRUE);
			OnBnClickedBtnTools();
			UpdateData(FALSE);

		}  

		return true;
	} 
	return CDialogEx::PreTranslateMessage(pMsg);
}