#include "StdAfx.h"
#include "OutlookBarTabCtrl.h"
#include "afxcontrolbarutil.h"
#include "afxoutlookbartabctrl.h"
#include "afxoutlookbarpane.h"
#include "afxoutlookbar.h"
#include "afxdockablepaneadapter.h"
#include "afxglobals.h"
#include "afxvisualmanager.h"
#include "afxoutlookbarpanebutton.h"
#include "afxdockingmanager.h"
#include "afxribbonres.h"
#include "afxcustomizebutton.h"
#include "afxmultipaneframewnd.h"

COutlookBarTabCtrl::COutlookBarTabCtrl(void)
{
}


COutlookBarTabCtrl::~COutlookBarTabCtrl(void)
{
}

void COutlookBarTabCtrl::OnShowOptions()
{
	
}

void COutlookBarTabCtrl::RecalcLayout()
{
	CMFCOutlookBarTabCtrl::RecalcLayout();
	//m_wndToolBar.EnableCustomizeButton(FALSE, NULL, _T(""));
	m_wndToolBar.RemoveAllButtons();
}
