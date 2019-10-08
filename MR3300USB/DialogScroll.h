#pragma once


// CDialogScroll dialog

class CDialogScroll : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogScroll)

public:
	CDialogScroll(CWnd* pParent = NULL);   // standard constructor
	CDialogScroll(UINT nIDTemplate, CWnd *pParent = NULL);
	virtual ~CDialogScroll();

	// Dialog Data
	enum { IDD = NULL };//IDD_DIALOGSCROLL
public:
	CRect	m_rcOriginalRect;

	// dragging
	BOOL	m_bDragging;
	CPoint	m_ptDragPoint;

	// actual scroll position
	int		m_nScrollPos;

	// actual dialog height
	int		m_nCurHeight;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
