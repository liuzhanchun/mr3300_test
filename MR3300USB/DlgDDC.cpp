// DlgDDC.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgDDC.h"
#include "afxdialogex.h"


// CDlgDDC �Ի���
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


// CDlgDDC ��Ϣ�������
//void CDlgInterPhone::OnOK()
//{
//	return;
//}
