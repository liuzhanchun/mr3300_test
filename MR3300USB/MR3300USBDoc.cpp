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

// MR3300USBDoc.cpp : CMR3300USBDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CMR3300USBDoc ����/����

CMR3300USBDoc::CMR3300USBDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_pThreadData = NULL;

}

CMR3300USBDoc::~CMR3300USBDoc()
{
}

BOOL CMR3300USBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle(_T(""));  ///doc�ĵ���
	return TRUE;
}




// CMR3300USBDoc ���л�

void CMR3300USBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMR3300USBDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CMR3300USBDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CMR3300USBDoc ���

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


// CMR3300USBDoc ����

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
	Sleep(100); //�ȴ�g_pMea����NULL
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
