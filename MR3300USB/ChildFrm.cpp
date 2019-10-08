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

// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "MR3300USBView.h"
#include "ChildFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define U_SA_OUTLOOKBAR 41000

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CONTEXTMENU()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_USER + 1002, OnMyClose)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_wndNavigationBar.ShowWindow(SW_SHOW);
	m_IsInited = FALSE;

}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;
	//cs.style&=~FWS_ADDTOTITLE; 
	//cs.style&=~FWS_PREFIXTITLE; 
	cs.style |= WS_VISIBLE|WS_MAXIMIZE;
	return CMDIChildWnd::PreCreateWindow(cs); 
	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	SetTimer(1, 500, NULL);  
	m_Splitter.CreateStatic(this,2,1);

	m_Splitter.CreateView( 0, 0, RUNTIME_CLASS(CMR3300USBView),CSize(100,100), pContext);
	m_pView[0] = (CMR3300USBView *)m_Splitter.GetPane( 0, 0 );

	m_Splitter.CreateView( 1, 0, RUNTIME_CLASS(CSpectroView),CSize(100,100), pContext);
	m_pSpectroView=(CSpectroView *)m_Splitter.GetPane( 1, 0 );
	
	m_Splitter.HideRow(TYPE_ASSIST);

	m_Splitter.evHideRow.bind(this, &CChildFrame::OnSplitterHideRow);
	m_Splitter.evShowRow.bind(this, &CChildFrame::OnSplitterShowRow);

	stOutlookBarItem stItem;

	g_pDlgParaConfig = new CDlgParaConfig();
	g_pDlgParaConfig->SetViewPtr(m_pView[0]);

	AddOutlookBarPane(g_pDlgParaConfig, TYPE_MAIN, 4, DLG_PARACONFIG,IDS_STRING111,m_SAOutlookBarItems);

	int nValue = CCommon::ReadRegQueryValue();
	if (!CreateOutlookBar(m_wndNavigationBar, U_SA_OUTLOOKBAR, nValue, m_SAOutlookBarItems))
	{
		return -1;      // δ�ܴ���
	}	
	m_IsInited = TRUE;

	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
//	return TRUE;
}

BOOL CChildFrame::CreateOutlookBar(COutlookBar& bar, UINT uiID, int nInitialWidth, std::deque<stOutlookBarItem>& Items)
{
	bar.SetMode2003();

	//BOOL bNameValid;
	CString strTemp;

	if (!bar.Create(_T(""), this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_RIGHT|WS_VSCROLL))
	{
		return FALSE; // δ�ܴ���
	}

	m_pOutlookBar = (COutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (m_pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}
	m_pOutlookBar->EnableInPlaceEdit(FALSE);

	// �ɸ��������Զ����أ��ɵ�����С�������ܹر�
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	for (UINT i=0; i<Items.size(); i++) {
		Items[i].pDlg->Create(Items[i].nDlgID, m_pOutlookBar);

		Items[i].pDlg->ShowWindow(SW_SHOW);
		m_pOutlookBar->AddControl(Items[i].pDlg, Items[i].strTitle, Items[i].nImageID, TRUE, dwStyle);
	}

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_OUTLOOKBAR24 : IDB_PAGES, 24);
	m_pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_OUTLOOKBAR16 : IDB_PAGES_SMALL, 16);
	m_pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	COutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

void CChildFrame::OnSplitterShowRow(int nRow)
{

}

void CChildFrame::OnSplitterHideRow(int nRow)
{

}


void CChildFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_bIsRun = FALSE;
	Sleep(300);
	CMDIChildWndEx::OnClose();
}

LRESULT CChildFrame::OnMyClose(WPARAM wParam, LPARAM lParam)
{
	OnClose();
	return 0;
}
void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	if (m_IsInited) {
		CRect rect;
		int	frame_width = 6;
		m_Splitter.GetClientRect( &rect );

		if(m_Splitter.GetSafeHwnd())
		{
			for(int i=0; i<2; i++)
			{
				if (i==0)
				{
					m_Splitter.SetRowInfo(i, rect.Height()*0.5, 10);
				}
				else
				{
					m_Splitter.SetRowInfo(i, rect.Height()*0.5, 10);
				}
			}
			m_Splitter.RecalcLayout();
		}
	}
}
void CChildFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x   = 800;   
	lpMMI->ptMinTrackSize.y   = 500;   
	lpMMI->ptMaxTrackSize.x   = 20000;   
	lpMMI->ptMaxTrackSize.y   =  20000;  

	CMDIChildWndEx::OnGetMinMaxInfo(lpMMI);
}

void CChildFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1)
	{
		if (g_bIsSpectroEN ==true)
		{
			if (g_bSpectroView)
			{
				m_Splitter.ShowRow(TYPE_ASSIST);
				CSpectroView* pView1 = (CSpectroView*)m_Splitter.GetPane(1,0);
				pView1->SetDevGDI(TRUE);
				g_bSpectroView = false;
			} 
			else
			{
				m_Splitter.HideRow(TYPE_ASSIST);
				CSpectroView* pView1 = (CSpectroView*)m_Splitter.GetPane(1,0);
				pView1->SetDevGDI(FALSE);
			}
			g_bIsSpectroEN=false;
		}
	}
	CMDIChildWndEx::OnTimer(nIDEvent);
}
