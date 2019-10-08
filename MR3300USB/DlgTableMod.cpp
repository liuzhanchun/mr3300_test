// DlgTableMod.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgTableMod.h"
#include "afxdialogex.h"


// CDlgTableMod 对话框

IMPLEMENT_DYNAMIC(CDlgTableMod, CDialogEx)

CDlgTableMod::CDlgTableMod(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTableMod::IDD, pParent)
{

}

CDlgTableMod::~CDlgTableMod()
{
}

void CDlgTableMod::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOD_BW, m_ModBw);
	DDX_Control(pDX, IDC_MOD_MODE, m_ModMode);
	DDX_Control(pDX, IDC_MOD_ATT, m_ModAtt);
}


BEGIN_MESSAGE_MAP(CDlgTableMod, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTableMod::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTableMod 消息处理程序
BOOL CDlgTableMod::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString sz;
	sz.Format(_T("%.6lf"), 1.0*m_ModItem.nCenter / MHZ_1);
	GetDlgItem(IDC_MOD_CENTERFRE)->SetWindowText(sz);

	sz.Format(_T("%d"), m_ModItem.nNoise );
	GetDlgItem(IDC_MOD_NOISE)->SetWindowText(sz);


	if (m_ModItem.nAtt== -1) //自动
	{
		m_ModAtt.SetCurSel(0);
	}

	if (m_ModItem.nAtt== 0) 
	{
		m_ModAtt.SetCurSel(1);
	}

	if (m_ModItem.nAtt== 5) 
	{
		m_ModAtt.SetCurSel(2);
	}

	if (m_ModItem.nAtt== 10) 
	{
		m_ModAtt.SetCurSel(3);
	}

	if (m_ModItem.nAtt== 15) 
	{
		m_ModAtt.SetCurSel(4);
	}

	if (m_ModItem.nAtt== 20) 
	{
		m_ModAtt.SetCurSel(5);
	}

	if (m_ModItem.nAtt== 25) 
	{
		m_ModAtt.SetCurSel(6);
	}
	if (m_ModItem.nAtt== 30) 
	{
		m_ModAtt.SetCurSel(7);
	}

	if (m_ModItem.nAtt== 35) 
	{
		m_ModAtt.SetCurSel(8);
	}

	if (m_ModItem.nAtt== 40) 
	{
		m_ModAtt.SetCurSel(9);
	}

	if (m_ModItem.nAtt== 45) 
	{
		m_ModAtt.SetCurSel(10);
	}

	if (m_ModItem.nAtt== 50) 
	{
		m_ModAtt.SetCurSel(11);
	}


	if (m_ModItem.nBW == 500000)
	{
		m_ModBw.SetCurSel(0);
	}
	if (m_ModItem.nBW == 300000)
	{
		m_ModBw.SetCurSel(1);
	}
	if (m_ModItem.nBW == 250000)
	{
		m_ModBw.SetCurSel(2);
	}
	if (m_ModItem.nBW == 150000)
	{
		m_ModBw.SetCurSel(3);
	}
	if (m_ModItem.nBW == 120000)
	{
		m_ModBw.SetCurSel(4);
	}
	if (m_ModItem.nBW == 50000)
	{
		m_ModBw.SetCurSel(5);
	}
	if (m_ModItem.nBW == 30000)
	{
		m_ModBw.SetCurSel(6);
	}
	if (m_ModItem.nBW == 15000)
	{
		m_ModBw.SetCurSel(7);
	}
	if (m_ModItem.nBW == 12000)
	{
		m_ModBw.SetCurSel(8);
	}
	if (m_ModItem.nBW == 9000)
	{
		m_ModBw.SetCurSel(9);
	}
	if (m_ModItem.nBW == 6000)
	{
		m_ModBw.SetCurSel(10);
	}
	if (m_ModItem.nBW == 2400)
	{
		m_ModBw.SetCurSel(11);
	}
	if (m_ModItem.nBW == 1500)
	{
		m_ModBw.SetCurSel(12);
	}

	int num = MultiByteToWideChar(0, 0, m_ModItem.sMode, -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, m_ModItem.sMode, -1, wide, num);

	if (wide == CString("FM"))
	{
		m_ModMode.SetCurSel(0);
	}
	if (m_ModItem.sMode == CString("AM"))
	{
		m_ModMode.SetCurSel(1);
	}
	if (m_ModItem.sMode == CString("PM"))
	{
		m_ModMode.SetCurSel(2);
	}
	if (m_ModItem.sMode == CString("CW"))
	{
		m_ModMode.SetCurSel(3);
	}
	if (m_ModItem.sMode == CString("LSB"))
	{
		m_ModMode.SetCurSel(4);
	}
	if (m_ModItem.sMode == CString("USB"))
	{
		m_ModMode.SetCurSel(5);
	}
	if (m_ModItem.sMode == CString("PULSE"))
	{
		m_ModMode.SetCurSel(6);
	}
	if (m_ModItem.sMode == CString("IQ"))
	{
		m_ModMode.SetCurSel(7);
	}

	
	return TRUE;
}

void CDlgTableMod::SetModItem(TASK_ITEM item)
{
	m_ModItem = item;

}

TASK_ITEM CDlgTableMod::GetModItem()
{


	return m_ModItem;
}



void CDlgTableMod::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szTemp;
	int nSelect;

	GetDlgItem(IDC_MOD_CENTERFRE)->GetWindowText(szTemp);
	m_ModItem.nCenter = _ttof(szTemp)*MHZ_1;

	GetDlgItem(IDC_MOD_NOISE)->GetWindowText(szTemp);
	m_ModItem.nNoise = _ttof(szTemp);

	nSelect = m_ModBw.GetCurSel();
	switch (nSelect)
	{
	case 0:
		m_ModItem.nBW = 500000;
		break;
	case 1:
		m_ModItem.nBW = 300000;
		break;
	case 2:
		m_ModItem.nBW = 250000;
		break;
	case 3:
		m_ModItem.nBW = 150000;
		break;
	case 4:
		m_ModItem.nBW = 120000;
		break;
	case 5:
		m_ModItem.nBW = 50000;
		break;
	case 6:
		m_ModItem.nBW = 30000;
		break;
	case 7:
		m_ModItem.nBW = 15000;
		break;
	case 8:
		m_ModItem.nBW = 12000;
		break;
	case 9:
		m_ModItem.nBW = 9000;
		break;
	case 10:
		m_ModItem.nBW = 6000;
		break;
	case 11:
		m_ModItem.nBW = 2400;
		break;
	case 12:
		m_ModItem.nBW = 1500;
		break;
	}

	nSelect = m_ModAtt.GetCurSel();
	switch (nSelect)
	{
	case 0:
		m_ModItem.nAtt = -1;
		break;
	case 1:
		m_ModItem.nAtt = 0;
		break;
	case 2:
		m_ModItem.nAtt = 5;
		break;
	case 3:
		m_ModItem.nAtt = 10;
		break;
	case 4:
		m_ModItem.nAtt = 15;
		break;
	case 5:
		m_ModItem.nAtt = 20;
		break;
	case 6:
		m_ModItem.nAtt = 25;
		break;
	case 7:
		m_ModItem.nAtt = 30;
		break;
	case 8:
		m_ModItem.nAtt = 35;
		break;
	case 9:
		m_ModItem.nAtt = 40;
		break;
	case 10:
		m_ModItem.nAtt = 45;
		break;
	case 11:
		m_ModItem.nAtt = 50;
		break;
	}

	nSelect = m_ModMode.GetCurSel();
	switch (nSelect)
	{
	case 0:
		sprintf(m_ModItem.sMode, "FM");
		break;
	case 1:
		sprintf(m_ModItem.sMode, "AM");
		break;
	case 2:
		sprintf(m_ModItem.sMode, "PM");
		break;
	case 3:
		sprintf(m_ModItem.sMode, "CW");
		break;
	case 4:
		sprintf(m_ModItem.sMode, "LSB");
		break;
	case 5:
		sprintf(m_ModItem.sMode, "USB");
		break;
	case 6:
		sprintf(m_ModItem.sMode, "PULSE");
		break;
	case 7:
		sprintf(m_ModItem.sMode, "IQ");
		break;
	}
	CDialogEx::OnOK();
}
