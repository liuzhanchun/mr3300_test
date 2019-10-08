// NumEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NumEdit.h"


// CNumEdit

IMPLEMENT_DYNAMIC(CNumEdit, CEdit)

CNumEdit::CNumEdit()
{
    m_nLength = 20;      //����
    m_nDec = 0;         //����
}

CNumEdit::~CNumEdit()
{
}


BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()



// CNumEdit message handlers
void CNumEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    //��Ч���������ֺ͸�������С����ͻ��˼�
    BOOL bConitue = (nChar >= 48 && nChar <= 57) 
        || nChar == 43
        || nChar == 45
        || nChar == 46
        || nChar == 8;
    if(!bConitue)
        return;
    CString sBefore,sAfter;
    GetWindowText(sBefore);
    //������λ��
    int nPosCurbgn, nPosCurend;
    GetSel(nPosCurbgn, nPosCurend);
    CEdit::OnChar(  nChar,  nRepCnt,  nFlags);
    GetWindowText(sAfter);
    int nLength = sAfter.GetLength();
    int nPos = sAfter.Find(_T("."));
    //������ȳ������ó����򷵻�
    if(nLength > m_nLength)
    {
        SetWindowText(sBefore);
        SetSel(nPosCurbgn,nPosCurend,true);
        return;
    }
    //������ȳ������õľ����򷵻�
    if(nPos != CB_ERR && nLength - nPos -1 > m_nDec)
    {
        SetWindowText(sBefore);
        SetSel(nPosCurbgn,nPosCurend,true);
        return;
    }
    //С���㲻����λ
    if(nLength > 0 && sAfter.Left(1) == _T("."))
    {
        SetWindowText(sBefore);
        SetSel(nPosCurbgn,nPosCurend,true);
        return;
    }
    //ֻ��һ��С����
    if(sBefore.Find(_T(".")) != CB_ERR && nChar == 46)
    {
        SetWindowText(sBefore);
        SetSel(nPosCurbgn,nPosCurend,true);
        return;
    }
}

