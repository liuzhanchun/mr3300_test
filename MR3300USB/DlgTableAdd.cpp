// DlgTableAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgTableAdd.h"
#include "afxdialogex.h"


// CDlgTableAdd 对话框

IMPLEMENT_DYNAMIC(CDlgTableAdd, CDialogEx)

CDlgTableAdd::CDlgTableAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTableAdd::IDD, pParent)
{

}

CDlgTableAdd::~CDlgTableAdd()
{
}

void CDlgTableAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTableAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTableAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTableAdd 消息处理程序

BOOL CDlgTableAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	if (!m_vtTaskItem.empty())
	{
		m_vtTaskItem.clear();
	}
	



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTableAdd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码


	CString szTemp;

	GetDlgItem(IDC_TABLE_START)->GetWindowText(szTemp);
	__int64 startfre = _ttof(szTemp)*MHZ_1;

	GetDlgItem(IDC_TABLE_STOP)->GetWindowText(szTemp);
	__int64 stopfre = _ttof(szTemp)*MHZ_1;

	GetDlgItem(IDC_TABLE_STEP)->GetWindowText(szTemp);
	__int64 frestep = _ttof(szTemp)*KHZ_1;

	int nCount = (stopfre-startfre)/frestep;

	if (nCount>1000)
	{
		MessageBox(L"频道表大于1000");
	
	}
	else
	{
		for(int i=0;i<nCount;i++)
		{
			m_vtTaskItem.push_back(startfre);
			startfre = startfre+frestep;
		}
		
	}



	CDialogEx::OnOK();
}
