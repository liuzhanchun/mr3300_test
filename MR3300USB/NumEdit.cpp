// NumEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NumEdit.h"


// CNumEdit

IMPLEMENT_DYNAMIC(CNumEdit, CEdit)

CNumEdit::CNumEdit()
{
    m_nLength = 20;      //长度
    m_nDec = 0;         //精度
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
    //有效按键是数字和负号正号小数点和回退键
    BOOL bConitue = (nChar >= 48 && nChar <= 57) 
        || nChar == 43
        || nChar == 45
        || nChar == 46
        || nChar == 8;
    if(!bConitue)
        return;
    CString sBefore,sAfter;
    GetWindowText(sBefore);
    //保存光标位置
    int nPosCurbgn, nPosCurend;
    GetSel(nPosCurbgn, nPosCurend);
    CEdit::OnChar(  nChar,  nRepCnt,  nFlags);
    GetWindowText(sAfter);
    int nLength = sAfter.GetLength();
    int nPos = sAfter.Find(_T("."));
    //如果长度超过设置长度则返回
    if(nLength > m_nLength)
    {
        SetWindowText(sBefore);
        SetSel(nPosCurbgn,nPosCurend,true);
        return;
    }
    //如果精度超过设置的精度则返回
    if(nPos != CB_ERR && nLength - nPos -1 > m_nDec)
    {
        SetWindowText(sBefore);
        SetSel(nPosCurbgn,nPosCurend,true);
        return;
    }
    //小数点不在首位
    if(nLength > 0 && sAfter.Left(1) == _T("."))
    {
        SetWindowText(sBefore);
        SetSel(nPosCurbgn,nPosCurend,true);
        return;
    }
    //只有一个小数点
    if(sBefore.Find(_T(".")) != CB_ERR && nChar == 46)
    {
        SetWindowText(sBefore);
        SetSel(nPosCurbgn,nPosCurend,true);
        return;
    }
}

