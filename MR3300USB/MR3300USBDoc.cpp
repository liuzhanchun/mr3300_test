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

// MR3300USBDoc.cpp : CMR3300USBDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MR3300USB.h"
#endif

#include "MR3300USBDoc.h"
#include "MR3300USBView.h"
#include <propkey.h>
#include "Measure.h"
#include "MeasSwitch.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "SpectroView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMR3300USBDoc

IMPLEMENT_DYNCREATE(CMR3300USBDoc, CDocument)

BEGIN_MESSAGE_MAP(CMR3300USBDoc, CDocument)
END_MESSAGE_MAP()


// CMR3300USBDoc 构造/析构

CMR3300USBDoc::CMR3300USBDoc()
{
	// TODO: 在此添加一次性构造代码
	m_pThreadData = NULL;

}

CMR3300USBDoc::~CMR3300USBDoc()
{
}

BOOL CMR3300USBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(_T(""));  ///doc文档中
	return TRUE;
}




// CMR3300USBDoc 序列化

void CMR3300USBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMR3300USBDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMR3300USBDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMR3300USBDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMR3300USBDoc 诊断

#ifdef _DEBUG
void CMR3300USBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMR3300USBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMR3300USBDoc 命令

void CMR3300USBDoc::Start()
{
	//CMR3300USBView* pView = (CMR3300USBView*)GetView(RUNTIME_CLASS(CMR3300USBView));
	//pView->Start();
	CChildFrame* pChild = (CChildFrame*)(((CMainFrame*)AfxGetMainWnd())->MDIGetActive()); 
	CMR3300USBView* pView = (CMR3300USBView*)(pChild->GetSplitter()->GetPane(0,0));
	pView->Start();

	CSpectroView *pView1 = (CSpectroView*)(pChild->GetSplitter()->GetPane(1,0));
	pView1->Start();



	m_pThreadData = AfxBeginThread(CMR3300USBDoc::ThreadData, this);
}


UINT CMR3300USBDoc::ThreadData(LPVOID lp)
{
	CMR3300USBDoc* ptr = (CMR3300USBDoc*)lp;
	Sleep(100); //等待g_pMea不是NULL
	while (g_bIsRun)
	{
		g_MeasSwitch.EnterLock();
		g_pMea->DataPro();
		g_MeasSwitch.LeaveLock();
#ifdef  _LOWCONFIGURE
		Sleep(15);
#else
		Sleep(3);
#endif
	}
	return 0;
}
CView* CMR3300USBDoc::GetView(CRuntimeClass* pClass)
{
	CView* pView = NULL;
	POSITION pos = GetFirstViewPosition();

	while (pos != NULL) {
		pView = GetNextView(pos);
		if (pView->IsKindOf(pClass))
		{
			return pView;
		}
	}
	return NULL;
}
