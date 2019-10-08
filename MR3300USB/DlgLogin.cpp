// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// CDlgLogin 对话框

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogin::IDD, pParent)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLogin 消息处理程序


void CDlgLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString szuser;
	CString szpass;
	GetDlgItem(IDC_USER)->GetWindowText(szuser);
	GetDlgItem(IDC_PASSWORD)->GetWindowText(szpass);

	if ((szuser == L"admin")&&(szpass == L"123456"))
	{

	} 
	else
	{
		AfxMessageBox(L"用户名或密码不正确！");
		return ;
	}

	CDialogEx::OnOK();
}
BOOL CDlgLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

