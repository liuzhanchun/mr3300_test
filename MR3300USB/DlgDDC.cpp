// DlgDDC.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgDDC.h"
#include "afxdialogex.h"


// CDlgDDC 对话框
CDlgDDC *g_pDlgDDC= NULL; 
IMPLEMENT_DYNAMIC(CDlgDDC, CDialogEx)

CDlgDDC::CDlgDDC(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDDC::IDD, pParent)
{

}

CDlgDDC::~CDlgDDC()
{
}

void CDlgDDC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDDC, CDialogEx)

END_MESSAGE_MAP()


// CDlgDDC 消息处理程序
//void CDlgInterPhone::OnOK()
//{
//	return;
//}
