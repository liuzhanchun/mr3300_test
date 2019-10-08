// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// ChildFrm.h : CChildFrame 类的接口
//

#pragma once

#include "ExtSplitter.h"
#include "DlgParaConfig.h"
#include "OutlookBar.h"
#include <deque>
#include "StructDef.h"
//#include "DlgTest.h"
#include "DlgParaConfig.h"
#include "Tools.h"
#include "SpectroView.h"
class CMR3300USBView;
class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 特性
public:
// 操作
public:
	// 生成的消息映射函数
	BOOL CreateOutlookBar(COutlookBar& bar, UINT uiID, int nInitialWidth, std::deque<stOutlookBarItem>& Items);		
	template<class T> void AddOutlookBarPane(T* ptDlg, TYPE_VIEW tv, UINT nImageID, UINT nDlgID, UINT nStringID,std::deque<stOutlookBarItem>& SAOutlookBarItems);
	void OnSplitterShowRow(int nRow);
	void OnSplitterHideRow(int nRow);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);


	//CDlgTest *m_pDlg;
	CExtSplitter* GetSplitter() { return &m_Splitter; }
	CExtSplitter m_Splitter;
	CMR3300USBView* m_pView[2];
	CSpectroView *m_pSpectroView;
	std::deque<stOutlookBarItem> m_SAOutlookBarItems;
	COutlookBarTabCtrl* m_pOutlookBar;
	COutlookBar m_wndNavigationBar;

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
private:
	BOOL m_IsInited;
// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnMyClose(WPARAM wParam, LPARAM lParam);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
template<class T>
void CChildFrame::AddOutlookBarPane(T* ptDlg, TYPE_VIEW tv, UINT nImageID, UINT nDlgID, UINT nStringID,std::deque<stOutlookBarItem>& SAOutlookBarItems)
{
	stOutlookBarItem stItem;
	//ptDlg->SetInterface(m_pInterface[tv]);
	stItem.pDlg = (CDialog*)ptDlg;
	stItem.nImageID = nImageID;
	stItem.nDlgID = nDlgID;

	_tcscpy(stItem.strTitle, CTools::LoadStringW(nStringID)); 
	SAOutlookBarItems.push_back(stItem);
}

