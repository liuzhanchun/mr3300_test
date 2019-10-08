#pragma once
#include "afxoutlookbartabctrl.h"

class COutlookBarTabCtrl :
	public CMFCOutlookBarTabCtrl
{
public:
	COutlookBarTabCtrl(void);
	~COutlookBarTabCtrl(void);

public:
	virtual void OnShowOptions();
	virtual void RecalcLayout();
};

