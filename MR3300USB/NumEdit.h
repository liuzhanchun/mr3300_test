#pragma once


// CNumEdit

class CNumEdit : public CEdit
{
	DECLARE_DYNAMIC(CNumEdit)

public:
	CNumEdit();
	virtual ~CNumEdit();

    void SetLength(int nLength) {m_nLength = nLength;}
    void SetDec(int nDec) {m_nDec = nDec;}

protected:
    //{{AFX_MSG(CNumEdit)
    afx_msg void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    int m_nLength;      //长度
    int m_nDec;         //精度
};


