// DlgHelp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgHelp.h"
#include "afxdialogex.h"


// CDlgHelp �Ի���

IMPLEMENT_DYNAMIC(CDlgHelp, CDialogEx)

CDlgHelp::CDlgHelp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgHelp::IDD, pParent)
{

}

CDlgHelp::~CDlgHelp()
{
}

void CDlgHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHelp, CDialogEx)
END_MESSAGE_MAP()

BOOL CDlgHelp::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;
}
// CDlgHelp ��Ϣ�������
