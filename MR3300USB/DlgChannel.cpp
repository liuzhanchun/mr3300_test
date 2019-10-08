// DlgChannel.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgChannel.h"
#include "afxdialogex.h"
#include "RemoteData.h"
#include "Measure.h"
#include "DlgTableAdd.h"
#include "DlgTableMod.h"
CDlgChannel *g_pDlgChannel= NULL; 

// CDlgChannel 对话框

IMPLEMENT_DYNAMIC(CDlgChannel, CDialogScroll)

CDlgChannel::CDlgChannel(CWnd* pParent /*=NULL*/)
	: CDialogScroll(CDlgChannel::IDD, pParent)
{
	m_nCenter = 0;
	m_TaskItem.nCenter = 20000000;
	m_TaskItem.nNoise = -30;
	m_TaskItem.nBW = 500000;
	sprintf(m_TaskItem.sMode, "FM");
	m_TaskItem.nAtt = -1;

}

CDlgChannel::~CDlgChannel()
{
}

void CDlgChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialogScroll::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHANNELTABLE, m_ListTemplate);
	DDX_Control(pDX, IDC_TABLE_BW, m_COMTableBW);
	DDX_Control(pDX, IDC_TABLE_ATT, m_COMTableAtt);
	DDX_Control(pDX, IDC_TABLE_MODE, m_COMTableMode);
}


BEGIN_MESSAGE_MAP(CDlgChannel, CDialogScroll)

	ON_WM_UPDATEUISTATE()
	ON_BN_CLICKED(IDC_TABLE_SADD, &CDlgChannel::OnBnClickedTableSadd)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDlgChannel::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CDlgChannel::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_TABLE_DELETE, &CDlgChannel::OnBnClickedTableDelete)
	ON_BN_CLICKED(IDC_TABLE_EMPTY, &CDlgChannel::OnBnClickedTableEmpty)
	ON_BN_CLICKED(IDC_TABLE_SEND, &CDlgChannel::OnBnClickedTableSend)
	ON_BN_CLICKED(IDC_TABLE_ADD, &CDlgChannel::OnBnClickedTableAdd)
	ON_BN_CLICKED(IDC_TABLE_MOD, &CDlgChannel::OnBnClickedTableMod)
END_MESSAGE_MAP()


// CDlgChannel 消息处理程序



BOOL CDlgChannel::OnInitDialog()
{
	__super::OnInitDialog();

	CString sz;
	sz.Format(_T("%.6lf"), 1.0*m_TaskItem.nCenter / MHZ_1);
	GetDlgItem(IDC_TABLE_CENTER)->SetWindowText(sz);

	sz.Format(_T("%d"), m_TaskItem.nNoise);
	GetDlgItem(IDC_TABLE_NOISE)->SetWindowText(sz);

	m_COMTableBW.SetCurSel(0);
	m_COMTableAtt.SetCurSel(0);
	m_COMTableMode.SetCurSel(0);

	InitTemplateList();

	CString  strPath;
	GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int nPos;
	nPos = strPath.ReverseFind('\\');
	strPath = strPath.Left(nPos);
	strPath += "\\default.task";
	LoadTask(strPath);
	ReflushList();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgChannel::OnOK()
{
	return;
}
void CDlgChannel::InitTemplateList()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_ListTemplate.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK;	//清除显示方式位
	lStyle |= LVS_REPORT;		//设置style
	SetWindowLong(m_ListTemplate.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_ListTemplate.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_ListTemplate.SetExtendedStyle(dwStyle); //设置扩展风格

	CRect rc;
	GetWindowRect(rc);
	int nWidth = rc.Width();

	m_ListTemplate.InsertColumn(0, _T("频率(MHz)"), LVCFMT_LEFT, (int)(0.185*nWidth));		//插入列
	m_ListTemplate.InsertColumn(1, _T("带宽(KHz)"), LVCFMT_LEFT, (int)(0.185*nWidth));
	m_ListTemplate.InsertColumn(2, _T("衰减控制"), LVCFMT_LEFT, (int)(0.185*nWidth));		//插入列
	m_ListTemplate.InsertColumn(3, _T("解调模式"), LVCFMT_LEFT, (int)(0.185*nWidth));
	m_ListTemplate.InsertColumn(4, _T("静噪门限"), LVCFMT_LEFT, (int)(0.185*nWidth));	

}

void CDlgChannel::ReflushList()
{
	m_ListTemplate.DeleteAllItems();
	CString szTemp;
	for (UINT i = 0; i < m_vtTask.size(); i++) {

		szTemp.Format(_T("%.6lf"), 1.0*m_vtTask[i].nCenter / MHZ_1);
		m_ListTemplate.InsertItem(i, szTemp);
		szTemp.Format(_T("%.3lf"), 1.0*m_vtTask[i].nBW / KHZ_1);
		m_ListTemplate.SetItemText(i, 1, szTemp);
		szTemp.Format(_T("%d"), m_vtTask[i].nAtt);
		m_ListTemplate.SetItemText(i, 2, szTemp);

		
		int num = MultiByteToWideChar(0, 0,  m_vtTask[i].sMode, -1, NULL, 0);
		wchar_t *wide = new wchar_t[num];
		MultiByteToWideChar(0, 0,  m_vtTask[i].sMode, -1, wide, num);
		m_ListTemplate.SetItemText(i, 3, wide);

		szTemp.Format(_T("%d"), m_vtTask[i].nNoise);
		m_ListTemplate.SetItemText(i, 4, szTemp);
	}
	CString sz;
	sz.Format(_T("%d"), m_vtTask.size());
	GetDlgItem(IDC_TABLE_DOT)->SetWindowText(sz);
	
}

void CDlgChannel::OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/)
{
	// 该功能要求使用 Windows 2000 或更高版本。
	// 符号 _WIN32_WINNT 和 WINVER 必须 >= 0x0500。
	// TODO: 在此处添加消息处理程序代码




	//	CString sz;
	//	sz.Format(_T("%.6lf"), 1.0*30000000 / MHZ_1);
	//	GetDlgItem(IDC_TABLE_CENTER)->SetWindowText(sz);

	//	SetTaskItem(m_TaskItem);

}


void CDlgChannel::OnBnClickedTableSadd()
{
	// TODO: 在此添加控件通知处理程序代码
	GetTaskItem();
	if (m_nCenter == m_TaskItem.nCenter)
	{
		m_TaskItem.nCenter += MHZ_1;
	}
	m_vtTask.push_back(m_TaskItem);
	ReflushList();
	m_nCenter = m_TaskItem.nCenter;
	SetTaskItem(m_TaskItem);

}

void CDlgChannel::SetTaskItem(TASK_ITEM ti)
{
	CString sz;
	sz.Format(_T("%.6lf"), 1.0*ti.nCenter / MHZ_1);
	GetDlgItem(IDC_TABLE_CENTER)->SetWindowText(sz);

	//sz.Format(_T("%d"), m_Ref);
	//GetDlgItem(IDC_RXFFM_REF)->SetWindowText(sz);



}

void CDlgChannel::GetTaskItem()
{

	CString szTemp;
	int nSelect;
	GetDlgItem(IDC_TABLE_CENTER)->GetWindowText(szTemp);
	m_TaskItem.nCenter = _ttof(szTemp)*MHZ_1;

	GetDlgItem(IDC_TABLE_NOISE)->GetWindowText(szTemp);
	m_TaskItem.nNoise = _ttof(szTemp);

	nSelect = m_COMTableBW.GetCurSel();
	switch (nSelect)
	{
	case 0:
		m_TaskItem.nBW = 500000;
		break;
	case 1:
		m_TaskItem.nBW = 300000;
		break;
	case 2:
		m_TaskItem.nBW = 250000;
		break;
	case 3:
		m_TaskItem.nBW = 150000;
		break;
	case 4:
		m_TaskItem.nBW = 120000;
		break;
	case 5:
		m_TaskItem.nBW = 50000;
		break;
	case 6:
		m_TaskItem.nBW = 30000;
		break;
	case 7:
		m_TaskItem.nBW = 15000;
		break;
	case 8:
		m_TaskItem.nBW = 12000;
		break;
	case 9:
		m_TaskItem.nBW = 9000;
		break;
	case 10:
		m_TaskItem.nBW = 6000;
		break;
	case 11:
		m_TaskItem.nBW = 2400;
		break;
	case 12:
		m_TaskItem.nBW = 1500;
		break;
	}

	nSelect = m_COMTableAtt.GetCurSel();
	switch (nSelect)
	{
	case 0:
		m_TaskItem.nAtt = -1;
		break;
	case 1:
		m_TaskItem.nAtt = 0;
		break;
	case 2:
		m_TaskItem.nAtt = 5;
		break;
	case 3:
		m_TaskItem.nAtt = 10;
		break;
	case 4:
		m_TaskItem.nAtt = 15;
		break;
	case 5:
		m_TaskItem.nAtt = 20;
		break;
	case 6:
		m_TaskItem.nAtt = 25;
		break;
	case 7:
		m_TaskItem.nAtt = 30;
		break;
	case 8:
		m_TaskItem.nAtt = 35;
		break;
	case 9:
		m_TaskItem.nAtt = 40;
		break;
	case 10:
		m_TaskItem.nAtt = 45;
		break;
	case 11:
		m_TaskItem.nAtt = 50;
		break;
	}

	nSelect = m_COMTableMode.GetCurSel();
	switch (nSelect)
	{
	case 0:
		sprintf(m_TaskItem.sMode, "FM");
		break;
	case 1:
		sprintf(m_TaskItem.sMode, "AM");
		break;
	case 2:
		sprintf(m_TaskItem.sMode, "PM");
		break;
	case 3:
		sprintf(m_TaskItem.sMode, "CW");
		break;
	case 4:
		sprintf(m_TaskItem.sMode, "LSB");
		break;
	case 5:
		sprintf(m_TaskItem.sMode, "USB");
		break;
	case 6:
		sprintf(m_TaskItem.sMode, "PULSE");
		break;
	case 7:
		sprintf(m_TaskItem.sMode, "IQ");
		break;
	}
}

void CDlgChannel::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码

	TCHAR szFilter[] = _T("频道表文件(*.task)|*.task||");
	CFileDialog dlg(FALSE, _T("*.task"), _T("default.task"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if (dlg.DoModal() == IDOK) {
		SaveTask(dlg.GetPathName());
	}
}
void CDlgChannel::SaveTask(CString szPath)
{
	CFile file;
	if (file.Open(szPath, CFile::modeCreate | CFile::modeReadWrite))
	{
		for (UINT i = 0; i < m_vtTask.size(); i++) {
			file.Write(&m_vtTask[i], sizeof(TASK_ITEM));
		}
		file.Close();
	}
}

void CDlgChannel::OnBnClickedBtnImport()
{
	// TODO: 在此添加控件通知处理程序代码

	TCHAR szFilter[] = _T("频道表文件(*.task)|*.task||");
	CFileDialog dlg(TRUE, _T("*.task"), _T("default.task"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if (dlg.DoModal() == IDOK) {
		LoadTask(dlg.GetPathName());
		ReflushList();
	}
}
void CDlgChannel::LoadTask(CString szPath)
{
	CFile file;
	m_vtTask.clear();

	if (file.Open(szPath, CFile::modeRead))
	{
		int nCount = file.GetLength() / sizeof(TASK_ITEM);
		for (int i = 0; i < nCount; i++)
		{
			TASK_ITEM ti;
			file.Read(&ti, sizeof(TASK_ITEM));
			m_vtTask.push_back(ti);
		}

		file.Close();
	}
}

int CDlgChannel::GetSelectIndex()
{
	int nSel = -1;
	for (int i = 0; i < m_ListTemplate.GetItemCount(); i++)
	{
		if (m_ListTemplate.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			return i;
		}
	}
	return -1;
}

void CDlgChannel::OnBnClickedTableDelete()
{
	// TODO: 在此添加控件通知处理程序代码

	int nIndex = GetSelectIndex();
	if (nIndex != -1)
	{
		m_vtTask.erase(m_vtTask.begin() + nIndex);
		ReflushList();
	}
}


void CDlgChannel::OnBnClickedTableEmpty()
{
	// TODO: 在此添加控件通知处理程序代码
	vector <TASK_ITEM>::iterator iter=m_vtTask.begin();
	for ( ;iter!=m_vtTask.end();)
	{
		iter=m_vtTask.erase(iter);
	}

	ReflushList();
}


void CDlgChannel::OnBnClickedTableSend()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[500];

	sprintf(Cmd, "MSC:COUN %d", m_vtTask.size());
	g_pRemote->FastSendCmd(Cmd);
	for (UINT i = 0; i < m_vtTask.size(); i++)
	{

		//	sprintf(Cmd, "MEM:CONT 0,20000000,300000,FM,-30,-1");
		//sprintf(Cmd, "MEM:CONT %d,%I64d,%I64d,%s,%d,%d", i, m_vtTask[i].nCenter, m_vtTask[i].nBW, m_vtTask[i].sMode, m_vtTask[i].nNoise,m_vtTask[i].nAtt);
		sprintf(Cmd, "MEM:CONT %d,%I64d,%I64d,%s", i, m_vtTask[i].nCenter, m_vtTask[i].nBW, m_vtTask[i].sMode);
		g_pRemote->FastSendCmd(Cmd);
	}
	g_pMea->m_vtTask.assign(m_vtTask.begin(), m_vtTask.end());  
}


void CDlgChannel::OnBnClickedTableAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgTableAdd Dlg;
	if (Dlg.DoModal() == IDOK)
	{	
		GetTaskItem();
		for (int i=0;i<Dlg.m_vtTaskItem.size();i++)
		{
			m_TaskItem.nCenter = Dlg.m_vtTaskItem[i];
		
			m_vtTask.push_back(m_TaskItem);
		}
	
		ReflushList();
	}


}


void CDlgChannel::OnBnClickedTableMod()
{
	// TODO: 在此添加控件通知处理程序代码

	int nIndex = GetSelectIndex();

	if (nIndex != -1)
	{
		CDlgTableMod Dlg;
		Dlg.SetModItem(m_vtTask[nIndex]);
		if (Dlg.DoModal() == IDOK)
		{
			m_vtTask[nIndex] = Dlg.GetModItem();
			ReflushList();
		}
	}

}
//GetTaskItem();
//if (m_nCenter == m_TaskItem.nCenter)
//{
//	m_TaskItem.nCenter += MHZ_1;
//}
//m_vtTask.push_back(m_TaskItem);
//ReflushList();
//m_nCenter = m_TaskItem.nCenter;
//SetTaskItem(m_TaskItem);