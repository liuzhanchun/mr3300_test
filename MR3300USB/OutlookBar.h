#pragma once
#include "afxoutlookbar.h"
#include "OutlookBarTabCtrl.h"

class COutlookBar :
	public CMFCOutlookBar
{
public:
	COutlookBar(void);
	~COutlookBar(void);

public:
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual BOOL CanBeResized() const{ return FALSE;}
	virtual BOOL OnShowControlBarMenu(CPoint point){return TRUE;}

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

