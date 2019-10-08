// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "MR3300USB.h"

#include "MainFrm.h"
#include "MR3300USBDoc.h"
#include "Tools.h"
#include "DlgConnect.h"
#include "MeasSwitch.h"
#include "DlgParaConfig.h"
#include "DlgSystemPara.h"
#include "DlgResponse.h"
#include "DlgLogin.h"
#include "Measure.h"
#include "ChildFrm.h"
#include "IniFile.h"
#include "DlgHelp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_BTN_RXFFM, &CMainFrame::OnBtnRxffm)
	ON_UPDATE_COMMAND_UI(ID_BTN_RXFFM, &CMainFrame::OnUpdateBtnRxffm)
	ON_COMMAND(ID_BTN_CONNECT, &CMainFrame::OnBtnConnect)
	ON_WM_CLOSE()
	ON_COMMAND(ID_BTN_RXPSCAN, &CMainFrame::OnBtnRxpscan)
	ON_UPDATE_COMMAND_UI(ID_BTN_CONNECT, &CMainFrame::OnUpdateBtnConnect)
	ON_COMMAND(ID_BTN_DISCONNECT, &CMainFrame::OnBtnDisconnect)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISCONNECT, &CMainFrame::OnUpdateBtnDisconnect)
	ON_UPDATE_COMMAND_UI(ID_BTN_RXPSCAN, &CMainFrame::OnUpdateBtnRxpscan)
	ON_COMMAND(ID_BTN_FPSCAN, &CMainFrame::OnBtnFpscan)
	ON_UPDATE_COMMAND_UI(ID_BTN_FPSCAN, &CMainFrame::OnUpdateBtnFpscan)
	ON_COMMAND(ID_BTN_HELP, &CMainFrame::OnBtnHelp)
	ON_UPDATE_COMMAND_UI(ID_BTN_HELP, &CMainFrame::OnUpdateBtnHelp)
	ON_COMMAND(ID_BTN_MS, &CMainFrame::OnBtnMs)
	ON_UPDATE_COMMAND_UI(ID_BTN_MS, &CMainFrame::OnUpdateBtnMs)
	ON_COMMAND(ID_BTN_FA, &CMainFrame::OnBtnFa)
	ON_UPDATE_COMMAND_UI(ID_BTN_FA, &CMainFrame::OnUpdateBtnFa)
	ON_COMMAND(ID_BTN_IP3, &CMainFrame::OnBtnIp3)
	ON_UPDATE_COMMAND_UI(ID_BTN_IP3, &CMainFrame::OnUpdateBtnIp3)
	ON_COMMAND(ID_BTN_IP2, &CMainFrame::OnBtnIp2)
	ON_UPDATE_COMMAND_UI(ID_BTN_IP2, &CMainFrame::OnUpdateBtnIp2)
	ON_COMMAND(ID_BTN_FIFR, &CMainFrame::OnBtnFifr)
	ON_UPDATE_COMMAND_UI(ID_BTN_FIFR, &CMainFrame::OnUpdateBtnFifr)
	ON_COMMAND(ID_BTN_SIFR, &CMainFrame::OnBtnSifr)
	ON_UPDATE_COMMAND_UI(ID_BTN_SIFR, &CMainFrame::OnUpdateBtnSifr)
	ON_COMMAND(ID_BTN_FIR, &CMainFrame::OnBtnFir)
	ON_UPDATE_COMMAND_UI(ID_BTN_FIR, &CMainFrame::OnUpdateBtnFir)
	ON_COMMAND(ID_BTN_SIR, &CMainFrame::OnBtnSir)
	ON_UPDATE_COMMAND_UI(ID_BTN_SIR, &CMainFrame::OnUpdateBtnSir)
	ON_COMMAND(ID_BTN_SS, &CMainFrame::OnBtnSs)
	ON_UPDATE_COMMAND_UI(ID_BTN_SS, &CMainFrame::OnUpdateBtnSs)
	ON_COMMAND(ID_BTN_LM, &CMainFrame::OnBtnLm)
	ON_UPDATE_COMMAND_UI(ID_BTN_LM, &CMainFrame::OnUpdateBtnLm)
	ON_COMMAND(ID_BTN_NF, &CMainFrame::OnBtnNf)
	ON_UPDATE_COMMAND_UI(ID_BTN_NF, &CMainFrame::OnUpdateBtnNf)
	ON_COMMAND(ID_BTN_PN, &CMainFrame::OnBtnPn)
	ON_UPDATE_COMMAND_UI(ID_BTN_PN, &CMainFrame::OnUpdateBtnPn)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
	g_pRemote = NULL;
	g_pData = NULL;
	g_pAud = NULL;
	m_bEnableConBtn = TRUE;
	m_bEnableDisConBtn = FALSE;
	m_bEnableRXFFMBtn = FALSE;
	m_bEnableRXPscanBtn = FALSE;
	m_bEnableRXFPSCANBtn = FALSE;
	m_bEnableMSBtn = FALSE;
	m_bEnableHelpBtn = TRUE;

	m_bEnableFABtn= FALSE;
	m_bEnableIP3Btn= FALSE;
	m_bEnableIP2Btn= FALSE;
	m_bEnableFIFRBtn= FALSE;
	m_bEnableSIFRBtn= FALSE;
	m_bEnableFIRBtn= FALSE;
	m_bEnableSIRBtn= FALSE;
	m_bEnableSSBtn= FALSE;
	m_bEnableLMBtn= FALSE;
	m_bEnableNFBtn= FALSE;
	m_bEnablePNBtn= FALSE;

}

CMainFrame::~CMainFrame()
{
	if (g_pRemote != NULL)
	{
		delete g_pRemote;
		g_pRemote = NULL;
	}

	if (g_pData != NULL)
	{
		delete g_pData;
		g_pData = NULL;
	}

	if (g_pAud != NULL)
	{
		delete g_pAud;
		g_pAud = NULL;
	}
/*	if (g_pResp != NULL)
	{
		delete g_pResp;
		g_pResp = NULL;
	}*/
	if (g_pIF != NULL)
	{
		delete g_pIF;
		g_pIF = NULL;
	}
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//BOOL bNameValid;
	//// ���ڳ־�ֵ�����Ӿ�����������ʽ
	//OnApplicationLook(theApp.m_nAppLook);

	//CMDITabInfo mdiTabParams;
	//mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	//mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	//mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	//mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	//mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	//EnableMDITabbedGroups(TRUE, mdiTabParams);

	//m_wndRibbonBar.Create(this);
	//m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("δ�ܴ���״̬��\n");
	//	return -1;      // δ�ܴ���
	//}

	//CString strTitlePane1;
	//CString strTitlePane2;
	//bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	//ASSERT(bNameValid);
	//bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	//ASSERT(bNameValid);
	//m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	//m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	//// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	//CDockingManager::SetDockingMode(DT_SMART);
	//// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	//EnableAutoHidePanes(CBRS_ALIGN_ANY);

	//// ������ǿ�Ĵ��ڹ���Ի���
	//EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	//// ���ĵ�����Ӧ�ó��������ڴ��ڱ������ϵ�˳����н�������
	//// ���Ľ��������Ŀ����ԣ���Ϊ��ʾ���ĵ�����������ͼ��
	//ModifyStyle(0, FWS_PREFIXTITLE);





	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// �������񽫴�������࣬��˽���ʱ��������ͣ��:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);
	// �Ѵ��� Outlook ����Ӧ���������ͣ����
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnBtnRxffm()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_DS);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}


void CMainFrame::OnBtnRxpscan()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXPSCAN);
	g_MeasSwitch.LeaveLock();
	//g_pDlgParaConfig->ChangeDispForMode(RXPSCAN);
	g_pDlgParaConfig->ChangeDispForMode(MEA_SS);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnFpscan()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFPSCAN);
	g_pDlgParaConfig->Detection(TRUE);
	g_MeasSwitch.LeaveLock();
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnMs()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_MS);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();

}
void CMainFrame::OnBtnFa()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_FA);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}

void CMainFrame::OnBtnIp3()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_IP3);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}

void CMainFrame::OnBtnIp2()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_IP2);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnFifr()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_FIFR);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnSifr()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_SIFR);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnFir()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_FIR);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnSir()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_SIR);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnSs()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFPSCAN);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_SS);
	g_pDlgParaConfig->Detection(FALSE);
	g_bIsWave = FALSE;
	g_bDraw = true;
	EndWaitCursor();
}
void CMainFrame::OnBtnLm()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_LM);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnNf()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_NF);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}
void CMainFrame::OnBtnPn()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();
	g_bIsWave = TRUE;
	Sleep(300);
	g_MeasSwitch.EnterLock();
	g_MeasSwitch.SwitchMeas(RXFFM);
	g_MeasSwitch.LeaveLock();
	g_pDlgParaConfig->ChangeDispForMode(MEA_PN);
	g_pDlgParaConfig->Detection(TRUE);
	g_bIsWave = FALSE;
	g_bDraw = false;
	EndWaitCursor();
}



void CMainFrame::OnBtnHelp()
{
	// TODO: �ڴ���������������
	CDlgHelp Dlg;
	if (Dlg.DoModal() == IDOK)
	{

	}
}

void CMainFrame::ReadConfigIni()
{
	CIniFile m_IniFile;
	m_IniFile.SetFileName(L"config.ini");

	CString csCount=m_IniFile.GetString(L"FREQ",L"count",L"");
	int nCount=_ttoi(csCount);
	ConfigIni.nCount = nCount;
	CString freq;
	CString FreqValue;
	for (int i=0;i<nCount;i++)
	{
		freq.Format(L"f%d",i+1);
		FreqValue= m_IniFile.GetString(L"FREQ",freq,L"");
		ConfigIni.nFreq[i] =  _ttof(FreqValue);
	}

	csCount=m_IniFile.GetString(L"AMP",L"count",L"");
	nCount=_ttoi(csCount);
	CString Amp;
	CString AmpValue;
	for (int i=0;i<nCount;i++)
	{
		Amp.Format(L"A%d",i+1);
		AmpValue= m_IniFile.GetString(L"AMP",Amp,L"");
		ConfigIni.fAmp[i] =  _ttof(AmpValue);
	}

	csCount=m_IniFile.GetString(L"FREQ_COMP",L"count",L"");
	nCount=_ttoi(csCount);
	CString fComp;
	CString fCompValue;
	for (int i=0;i<nCount;i++)
	{
		fComp.Format(L"f_comp%d",i+1);
		fCompValue= m_IniFile.GetString(L"FREQ_COMP",fComp,L"");
		ConfigIni.nFreqComp[i] =  _ttof(fCompValue);
	}
	ConfigIni.nRF_LN =  _ttoi(m_IniFile.GetString(L"ATT",L"RF_LN",L""));
	ConfigIni.nIF_LN =  _ttoi(m_IniFile.GetString(L"ATT",L"IF_LN",L""));
	ConfigIni.nRF_NM =  _ttoi(m_IniFile.GetString(L"ATT",L"RF_NM",L""));
	ConfigIni.nIF_NM =  _ttoi(m_IniFile.GetString(L"ATT",L"IF_NM",L""));
	ConfigIni.nRF_LD =  _ttoi(m_IniFile.GetString(L"ATT",L"RF_LD",L""));
	ConfigIni.nIF_LD =  _ttoi(m_IniFile.GetString(L"ATT",L"IF_LD",L""));
	ConfigIni.nMeasureTime =  _ttoi(m_IniFile.GetString(L"MEA_TIME",L"measure_time",L""));
}
void CMainFrame::OnBtnConnect()
{
	// TODO: �ڴ���������������
	BOOL IsRunning = FALSE;
	CDlgConnect Dlg;
	if (Dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();
		int num1 = WideCharToMultiByte(CP_OEMCP, NULL, Dlg.m_szTcpIP.GetBuffer(), -1, NULL, 0, NULL, FALSE);
		char *pchar = new char[num1];
		WideCharToMultiByte(CP_OEMCP, NULL, Dlg.m_szTcpIP.GetBuffer(), -1, pchar, num1, NULL, FALSE);
		g_pRemote = new CRemoteData(pchar, Dlg.m_nPort);
		Dlg.m_szTcpIP.ReleaseBuffer();

		if (g_pRemote->ConnectDev() == OPT_SUCCESS)
		{
			g_pRemote->DisconnectDev();

			char InitCmd[350];
			sprintf(InitCmd, "SYSTem:COMMunicate:ECHO ON");
			g_pRemote->FastSendCmd(InitCmd);
			IsRunning = FALSE;
		}
		else
		{
			MessageBox(L"�����ջ������Ƿ�������");
			IsRunning = TRUE;
			goto endconnect;
		}

		ReadConfigIni();
		char Cmd[350];
		num1 = WideCharToMultiByte(CP_OEMCP, NULL, Dlg.m_szUdpIP.GetBuffer(), -1, NULL, 0, NULL, FALSE);
		pchar = new char[num1];
		WideCharToMultiByte(CP_OEMCP, NULL, Dlg.m_szUdpIP.GetBuffer(), -1, pchar, num1, NULL, FALSE);

		sprintf(Cmd, "TRAC:UDP \"%s\",4567,MEASURE", pchar);
		g_pRemote->FastSendCmd(Cmd);

		sprintf(Cmd, "TRAC:UDP \"%s\",4567,SCAN", pchar);
		g_pRemote->FastSendCmd(Cmd);

		sprintf(Cmd, "TRAC:UDP \"%s\",4568,AUDIO", pchar);
		g_pRemote->FastSendCmd(Cmd);

	/*	sprintf(Cmd, "TRAC:UDP \"%s\",4569,RESP", pchar);
		g_pRemote->FastSendCmd(Cmd);*/

		sprintf(Cmd, "TRAC:UDP \"%s\",4570,IF", pchar);
		g_pRemote->FastSendCmd(Cmd);

		Dlg.m_szUdpIP.ReleaseBuffer();

		g_pData  =new CUdpServer(4567);
		g_pAud  = new CUdpServer(4568);
		//g_pResp  = new CUdpServer(4569);
		g_pIF = new CUdpServer(4570);
		//Ĭ�Ͻ���RXFFM
		g_MeasSwitch.EnterLock();
		g_MeasSwitch.SwitchMeas(RXFFM);
		g_MeasSwitch.LeaveLock();
		//
		g_bIsRun =TRUE;
		if (theApp.NumberOfOpenDocuments() == 0) {
			CMR3300USBDoc* pDoc = (CMR3300USBDoc*)(theApp.m_pTemplateFFM->OpenDocumentFile(NULL));
			pDoc->Start();
		}
		g_pDlgParaConfig->ChangeDispForMode(MEA_DS);
		g_pDlgParaConfig->Detection(TRUE);
		CChildFrame* pChild = (CChildFrame*)(((CMainFrame*)AfxGetMainWnd())->MDIGetActive()); 

		SetConBtnSatate(FALSE);
		SetDisConBtnSatate(TRUE);
		SetRXFFMBtnSatate(TRUE);
		SetRXPscanBtnSatate(TRUE);
		SetRXFPSCANBtnSatate(TRUE);
		SetMSBtnSatate(TRUE);
		SetFABtnSatate(TRUE);
		SetIP3BtnSatate(TRUE);
		SetIP2BtnSatate(TRUE);
		SetFIFRBtnSatate(TRUE);
		SetSIFRBtnSatate(TRUE);
		SetFIRBtnSatate(TRUE);
		SetSIRBtnSatate(TRUE);
		SetSSBtnSatate(TRUE);
		SetLMBtnSatate(TRUE);
		SetNFBtnSatate(TRUE);
		SetPNBtnSatate(TRUE);
		EndWaitCursor();
	}
endconnect:
	if (IsRunning)
	{
		delete g_pRemote;
		g_pRemote = NULL;
	}
}
void CMainFrame::OnBtnDisconnect()
{
	// TODO: �ڴ���������������

	CMDIChildWnd* pFrame = MDIGetActive();
	if (pFrame != NULL)
	{
		GetActiveFrame()->SendMessage(WM_CLOSE);
	}
//	g_bIsRun = FALSE;
	//Sleep(800);
	if (g_pRemote != NULL)
	{
		delete g_pRemote;
		g_pRemote = NULL;
	}
	if (g_pData != NULL)
	{
		delete g_pData;
		g_pData = NULL;
	}
	if (g_pAud != NULL)
	{
		delete g_pAud;
		g_pAud = NULL;
	}
/*	if (g_pResp != NULL)
	{
		delete g_pResp;
		g_pResp = NULL;
	}*/
	if (g_pIF != NULL)
	{
		delete g_pIF;
		g_pIF = NULL;
	}
	

	g_pMea->SetMeasID(RXNONE) ;

	SetConBtnSatate(TRUE);
	SetDisConBtnSatate(FALSE);
	SetRXFFMBtnSatate(FALSE);
	SetRXPscanBtnSatate(FALSE);
	SetRXFPSCANBtnSatate(FALSE);
	SetMSBtnSatate(FALSE);
	SetFABtnSatate(FALSE);
	SetIP3BtnSatate(FALSE);
	SetIP2BtnSatate(FALSE);
	SetFIFRBtnSatate(FALSE);
	SetSIFRBtnSatate(FALSE);
	SetFIRBtnSatate(FALSE);
	SetSIRBtnSatate(FALSE);
	SetSSBtnSatate(FALSE);
	SetLMBtnSatate(FALSE);
	SetNFBtnSatate(FALSE);
	SetPNBtnSatate(FALSE);
}

void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_bIsRun = FALSE;
	Sleep(300);
	CMDIFrameWndEx::OnClose();
}

void CMainFrame::OnUpdateBtnConnect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bEnableConBtn);
}

void CMainFrame::OnUpdateBtnDisconnect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bEnableDisConBtn);
}

void CMainFrame::OnUpdateBtnRxffm(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bEnableRXFFMBtn);
}

void CMainFrame::OnUpdateBtnRxpscan(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bEnableRXPscanBtn);
}

void CMainFrame::OnUpdateBtnFpscan(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bEnableRXFPSCANBtn);
}
void CMainFrame::OnUpdateBtnHelp(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bEnableHelpBtn);
}

void CMainFrame::OnUpdateBtnMs(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bEnableMSBtn);
}
void CMainFrame::OnUpdateBtnFa(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableFABtn);
}
void CMainFrame::OnUpdateBtnIp3(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableIP3Btn);
}
void CMainFrame::OnUpdateBtnIp2(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableIP2Btn);
}
void CMainFrame::OnUpdateBtnFifr(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableFIFRBtn);
}
void CMainFrame::OnUpdateBtnSifr(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableSIFRBtn);
}
void CMainFrame::OnUpdateBtnFir(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableFIRBtn);
}
void CMainFrame::OnUpdateBtnSir(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableSIRBtn);
}
void CMainFrame::OnUpdateBtnSs(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableSSBtn);
}
void CMainFrame::OnUpdateBtnLm(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableLMBtn);
}
void CMainFrame::OnUpdateBtnNf(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnableNFBtn);
}
void CMainFrame::OnUpdateBtnPn(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(m_bEnablePNBtn);
}






