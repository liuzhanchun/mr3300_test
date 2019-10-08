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

// ChildFrm.h : CChildFrame ��Ľӿ�
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

// ����
public:
// ����
public:
	// ���ɵ���Ϣӳ�亯��
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

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
private:
	BOOL m_IsInited;
// ʵ��
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
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

