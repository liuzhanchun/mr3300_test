#include "StdAfx.h"
#include "OutlookBar.h"
#include "afxoutlookbar.h"
#include "afxoutlookbartabctrl.h"
#include "afxoutlookbarpaneadapter.h"
#include "afxoutlookbarpane.h"
#include "afxdockingmanager.h"
#include "afxglobalutils.h"
#include "afxregpath.h"
#include "afxsettingsstore.h"
#include "afxpaneframewnd.h"
#include "afxwinappex.h"


COutlookBar::COutlookBar(void)
{
	//m_pTabWnd = NULL;
}


COutlookBar::~COutlookBar(void)
{
}

BEGIN_MESSAGE_MAP(COutlookBar, CMFCOutlookBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int COutlookBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBaseTabbedPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectClient(0, 0, lpCreateStruct->cx, lpCreateStruct->cy);

	ENSURE(m_pTabWnd == NULL);
	m_pTabWnd = new COutlookBarTabCtrl;

	COutlookBarTabCtrl* pTabWnd = (COutlookBarTabCtrl*) m_pTabWnd;

	// enable this before create,a s it may change inside for dialog applications
	pTabWnd->m_bEnableWrapping = TRUE;

	// Create tabs window:
	if (!pTabWnd->Create(rectClient, this, 101))
	{
		TRACE0("Failed to create tab window\n");
		delete m_pTabWnd;
		m_pTabWnd = NULL;
		return -1;      // fail to create
	}

	pTabWnd->SetDockingBarWrapperRTC(RUNTIME_CLASS(CMFCOutlookBarPaneAdapter));

	if (CanFloat())
	{
		pTabWnd->HideSingleTab();
	}

	return 0;
}
