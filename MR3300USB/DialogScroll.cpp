// DialogScroll.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DialogScroll.h"
#include "afxdialogex.h"


// CDialogScroll dialog

IMPLEMENT_DYNAMIC(CDialogScroll, CDialogEx)

	CDialogScroll::CDialogScroll(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogScroll::IDD, pParent)
{
	m_bDragging = FALSE;
}

CDialogScroll::CDialogScroll( UINT nIDTemplate, CWnd *pParent /*= NULL*/ )
	: CDialogEx(CDialogScroll::IDD, pParent)
{
	m_bDragging = FALSE;
}

CDialogScroll::~CDialogScroll()
{
}

void CDialogScroll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogScroll, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	//	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDialogScroll message handlers


void CDialogScroll::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == NULL) {
		int nDelta;
		int nMaxPos = m_rcOriginalRect.Height() - m_nCurHeight;

		switch (nSBCode)
		{
		case SB_LINEDOWN:
			if (m_nScrollPos >= nMaxPos)
				return;

			nDelta = min(max(nMaxPos/20,5),nMaxPos-m_nScrollPos);
			break;

		case SB_LINEUP:
			if (m_nScrollPos <= 0)
				return;
			nDelta = -min(max(nMaxPos/20,5),m_nScrollPos);
			break;
		case SB_PAGEDOWN:
			if (m_nScrollPos >= nMaxPos)
				return;
			nDelta = min(max(nMaxPos/10,5),nMaxPos-m_nScrollPos);
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			nDelta = (int)nPos - m_nScrollPos;
			break;

		case SB_PAGEUP:
			if (m_nScrollPos <= 0)
				return;
			nDelta = -min(max(nMaxPos/10,5),m_nScrollPos);
			break;

		default:
			return;
		}
		m_nScrollPos += nDelta;
		SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
		ScrollWindow(0,-nDelta);
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CDialogScroll::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 保存默认大小
	GetWindowRect(m_rcOriginalRect);	

	// 设置初始化位置
	m_nScrollPos = 0; 

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogScroll::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_nCurHeight = cy;

	SCROLLINFO si;

	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = m_rcOriginalRect.Height();
	si.nPage = cy;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE); 	

	OnVScroll(SB_LINEUP, 0, NULL);

	CRect rc;
	this->GetWindowRect(&rc);

	// 以这个为底线
	if (this->GetSafeHwnd()) {
		if (rc.Height() < m_rcOriginalRect.Height()) {
			ShowScrollBar(SB_VERT, TRUE);
		}
		else {
			ShowScrollBar(SB_VERT, FALSE);
		}
	}
}

//void CDialogScroll::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// This feature requires Windows Vista or greater.
//	// The symbol _WIN32_WINNT must be >= 0x0600.
//	// TODO: Add your message handler code here and/or call default
//
//	CDialogEx::OnMouseHWheel(nFlags, zDelta, pt);
//}


BOOL CDialogScroll::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (zDelta == -120)  
	{  
		OnVScroll(SB_LINEDOWN, GetScrollPos(SB_VERT), GetScrollBarCtrl(SB_VERT));
	}  
	else if (zDelta == 120)  
	{  
		OnVScroll(SB_LINEUP, GetScrollPos(SB_VERT), GetScrollBarCtrl(SB_VERT));
	}  

	//m_vScroll.MoveWindow(rt_mvScroll, TRUE);  
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CDialogScroll::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();

	CDialogEx::OnLButtonDown(nFlags, point);
}
