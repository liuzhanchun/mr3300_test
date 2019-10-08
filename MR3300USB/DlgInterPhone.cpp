// DlgInterPhone.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgInterPhone.h"
#include "afxdialogex.h"

CDlgInterPhone *g_pDlgInterPhone= NULL; 
// CDlgInterPhone 对话框

IMPLEMENT_DYNAMIC(CDlgInterPhone, CDialogScroll)

CDlgInterPhone::CDlgInterPhone(CWnd* pParent /*=NULL*/)
	: CDialogScroll(CDlgInterPhone::IDD, pParent)
{

}

CDlgInterPhone::~CDlgInterPhone()
{
}

void CDlgInterPhone::DoDataExchange(CDataExchange* pDX)
{
	CDialogScroll::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgInterPhone, CDialogScroll)
	ON_BN_CLICKED(IDC_CK_MESSAGE, &CDlgInterPhone::OnBnClickedCkMessage)
END_MESSAGE_MAP()


// CDlgInterPhone 消息处理程序
BOOL CDlgInterPhone::OnInitDialog()
{
	__super::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgInterPhone::OnOK()
{
	return;
}


void CDlgInterPhone::DTMessage(STRUCT_DT_FRAME DT,bool IsSwitch)
{
	//	DT
	if (DT.nLen>512)
	{
		return;
	}
	if (DT.nLen<2)
	{
		return;
	}
	CString Message;
	CString Called;
	CString Calling;
	CString Clour;

	if (DT.type==0x00)
	{
		wchar_t* pUnicode;
		pUnicode = new wchar_t[1024];
		memset(pUnicode, 0, 1024);
		memcpy(pUnicode, DT.sMSGContent, DT.nLen);
		pUnicode[DT.nLen] = '\0';
		Message = (wchar_t*)pUnicode;
		delete pUnicode;
		GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowText(Message);  //显示汉字等字符串信息
	}
	if (DT.type==0x01)
	{
		char acsi[1024];
		memcpy(acsi, DT.sMSGContent, DT.nLen);
		acsi[DT.nLen] = '\0';

		int num = MultiByteToWideChar(0, 0,acsi, -1, NULL, 0);
		wchar_t *wide = new wchar_t[num];
		MultiByteToWideChar(0, 0,acsi, -1, wide, num);
		GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowText(wide);  //显示汉字等字符串信息
	}
	Calling.Format(_T("%d"),DT.nCallingNum);
	GetDlgItem(IDC_EDIT_CALLING)->SetWindowText(Calling);

	Clour.Format(_T("%d"),DT.nColourCode);
	GetDlgItem(IDC_EDIT_CLOUR)->SetWindowText(Clour);

	Called.Format(_T("%d"),DT.nCalledNum);
	GetDlgItem(IDC_EDIT_CALLED)->SetWindowText(Called);

}



void CDlgInterPhone::OnBnClickedCkMessage()
{
	// TODO: 在此添加控件通知处理程序代码

	//g_pDlgParaConfig->OnBnClickedMess
}
