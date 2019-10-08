#pragma once

struct stOutlookBarItem {
	CDialog* pDlg;
	UINT nDlgID;
	UINT nImageID;
	TCHAR strTitle[30];
};

enum TYPE_VIEW {
	TYPE_MAIN = 0, // Ö÷´°¿Ú
	TYPE_ASSIST	   // ¸¨Öú´°¿Ú
};

