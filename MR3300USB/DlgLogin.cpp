// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// CDlgLogin �Ի���

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


// CDlgLogin ��Ϣ�������


void CDlgLogin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox(L"�û��������벻��ȷ��");
		return ;
	}

	CDialogEx::OnOK();
}
BOOL CDlgLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

