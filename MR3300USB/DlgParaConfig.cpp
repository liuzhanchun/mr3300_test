// DlgParaConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "MR3300USB.h"
#include "DlgParaConfig.h"
#include "afxdialogex.h"
#include "Measure.h"
#include "RemoteData.h"
#include "MR3300USBView.h"
#include <map>  
#include <string>  
#include <iostream>  
#include "ChildFrm.h"
#include "afxwin.h"
using namespace std;

// CDlgParaConfig 对话框
CDlgParaConfig *g_pDlgParaConfig= NULL; 
CString sMed;
map<int, int> MapSpan;
map<double, int> BW;
map<double, int> Step;
map<int, int> AttRF;
map<int, int> AttIF;
int g_nAttMode = 0;

double g_dSignalFre = 0;
double g_dSignalAmp = 0;
int g_nMedMode = 0;


IMPLEMENT_DYNAMIC(CDlgParaConfig, CDialogScroll)
CDlgParaConfig::CDlgParaConfig(CWnd* pParent /*=NULL*/)
	: CDialogScroll(CDlgParaConfig::IDD, pParent)
{
	MapSpan[80000] = 0;
	MapSpan[40000] = 1;
	MapSpan[20000] = 2;
	MapSpan[10000] = 3;
	MapSpan[5000] = 4;
	MapSpan[2000] = 5;
	MapSpan[1000] = 6;
	MapSpan[500] = 7;
	MapSpan[200] = 8;
	MapSpan[100] = 9;
	MapSpan[50] = 10;
	MapSpan[20] = 11;
	MapSpan[10] = 12;
	MapSpan[5] = 13;
	MapSpan[2] = 14;
	MapSpan[1] = 15;

	AttRF[0] = 0;
	AttRF[2] = 1;
	AttRF[4] = 2;
	AttRF[6] = 3;
	AttRF[8] = 4;
	AttRF[10] = 5;
	AttRF[12] = 6;
	AttRF[14] = 7;
	AttRF[16] = 8;
	AttRF[18] = 9;
	AttRF[20] = 10;
	AttRF[22] = 11;
	AttRF[24] = 12;
	AttRF[26] = 13;
	AttRF[28] = 14;
	AttRF[30] = 15;


	AttIF[0] = 0;
	AttIF[1] = 1;
	AttIF[2] = 2;
	AttIF[3] = 3;
	AttIF[4] = 4;
	AttIF[5] = 5;
	AttIF[6] = 6;
	AttIF[7] = 7;
	AttIF[8] = 8;
	AttIF[9] = 9;
	AttIF[10] = 10;
	AttIF[11] = 11;
	AttIF[12] = 12;
	AttIF[13] = 13;
	AttIF[14] = 14;
	AttIF[15] = 15;
	AttIF[16] = 16;
	AttIF[17] = 17;
	AttIF[18] = 18;
	AttIF[19] = 19;
	AttIF[20] = 20;
			

	BW[500] = 0;
	BW[300] = 1;
	BW[200] = 2;
	BW[150] = 3;
	BW[120] = 4;
	BW[50] = 5;
	BW[30] = 6;
	BW[15] = 7;
	BW[12] = 8;
	BW[9] = 9;
	BW[6] = 10;
	BW[2.4] = 11;
	BW[1.5] = 12;

	Step[500] = 0;
	Step[200] = 1;
	Step[100] = 2;
	Step[50] = 3;
	Step[25] = 4;
	Step[12.5] = 5;
	Step[6.25] = 6;
	Step[3.125] = 7;

}

CDlgParaConfig::~CDlgParaConfig()
{
}

void CDlgParaConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogScroll::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CENTERFRE, m_CenterFre);
	DDX_Control(pDX, IDC_CMB_SPAN, m_ComSpan);
	DDX_Control(pDX, IDC_COM_RFMODE, m_Com_RFMode);
	DDX_Control(pDX, IDC_COM_BW, m_Com_BW);
	DDX_Control(pDX, IDC_COM_STEP, m_Com_Step);
	DDX_Control(pDX, IDC_COM_ATTRF, m_ComAttRF);
	DDX_Control(pDX, IDC_COM_ATTIF, m_ComAttIF);
	DDX_Control(pDX, IDC_COM_DEM, m_Com_Dem);
}


BEGIN_MESSAGE_MAP(CDlgParaConfig, CDialogScroll)


	ON_BN_CLICKED(IDC_BTB_CENTERFRE, &CDlgParaConfig::OnBnClickedBtbCenterfre)
	ON_BN_CLICKED(CK_NORMAL, &CDlgParaConfig::OnBnClickedNormal)
	ON_BN_CLICKED(CK_MAX, &CDlgParaConfig::OnBnClickedMax)
	ON_BN_CLICKED(CK_MIN, &CDlgParaConfig::OnBnClickedMin)
	ON_BN_CLICKED(CK_AVG, &CDlgParaConfig::OnBnClickedAvg)
	ON_BN_CLICKED(BTN_RESET, &CDlgParaConfig::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BTN_REF, &CDlgParaConfig::OnBnClickedBtnRef)
	ON_CBN_SELCHANGE(IDC_CMB_SPAN, &CDlgParaConfig::OnCbnSelchangeCmbSpan)
	ON_BN_CLICKED(IDC_CK_SPEC, &CDlgParaConfig::OnBnClickedCkSpec)
	ON_BN_CLICKED(IDC_CK_AUD, &CDlgParaConfig::OnBnClickedCkAud)
	ON_CBN_SELCHANGE(IDC_COM_RFMODE, &CDlgParaConfig::OnCbnSelchangeComRfmode)
	ON_CBN_SELCHANGE(IDC_COM_DEM, &CDlgParaConfig::OnCbnSelchangeComDem)
	ON_CBN_SELCHANGE(IDC_COM_BW, &CDlgParaConfig::OnCbnSelchangeComBw)
	ON_CBN_SELCHANGE(IDC_COM_STEP, &CDlgParaConfig::OnCbnSelchangeComStep)
	ON_BN_CLICKED(IDC_BTN_STARTFRE, &CDlgParaConfig::OnBnClickedBtnStartfre)
	ON_BN_CLICKED(IDC_BTN_STOPFRE, &CDlgParaConfig::OnBnClickedBtnStopfre)
	
	ON_CBN_SELCHANGE(IDC_COM_ATTRF, &CDlgParaConfig::OnCbnSelchangeComAttrf)
	ON_CBN_SELCHANGE(IDC_COM_ATTIF, &CDlgParaConfig::OnCbnSelchangeComAttif)
	ON_BN_CLICKED(IDC_CK_SPECTRO, &CDlgParaConfig::OnBnClickedCkSpectro)
END_MESSAGE_MAP()


// CDlgParaConfig 消息处理程序

void CDlgParaConfig::SetViewPtr(CMR3300USBView* pView)
{
	m_pView = pView;
}

BOOL CDlgParaConfig::OnInitDialog()
{
	__super::OnInitDialog();

	CButton* pBtn = (CButton*)(GetDlgItem(CK_NORMAL));
	pBtn->SetCheck(TRUE);

	m_CenterFre.SetDec(6);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgParaConfig::OnOK()
{
	return;
}
void CDlgParaConfig::ChangeDispForMode(int nMode)
{
	char cBuf[1000] = { 0 };
	char cRecv[1000] = { 0 };
	CString sz;
	char Cmd[50];

	m_pView->m_bFirst = TRUE;


	g_dSignalFre = 0;
	g_dSignalAmp = 0;


	if (nMode==MEA_FA)
	{
		sprintf(Cmd, "FREQuency:SPAN %I64d",(INT64)(1*KHZ_1));
		g_pRemote->FastSendCmd(Cmd);
	}


	GetDlgItem(IDC_STARTFRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOPFRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_STEP)->EnableWindow(TRUE);
	GetDlgItem(IDC_CENTERFRE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTB_CENTERFRE)->EnableWindow(TRUE);

	GetDlgItem(IDC_COM_ATTRF)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_ATTIF)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_BW)->EnableWindow(TRUE);
	GetDlgItem(IDC_CMB_SPAN)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_RFMODE)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_DEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_STEP)->EnableWindow(TRUE);

//	if (nMode == RXFFM)
//	{
		/*GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);*/

	//	GetDlgItem(IDC_CENTERFRE)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_BTB_CENTERFRE)->EnableWindow(TRUE);


		m_pView->SetRef(60);
		GetDlgItem(IDC_REF)->SetWindowText(L"60");

		//sprintf(cBuf, "FREQuency?;FREQuency:SPAN?;TRAC:MED?;BANDwidth:XDB?;BANDwidth:BETA?;MEASure:THReshold?;DEModulation?;ATTenuation:AUTomation?;MEASure:DETector?;ATTenuation:RF:MODE?;BANDwidth?;MEASure:TIME?;MEASure:SQUelch?;ATTenuation:RF?;ATTenuation:IF?"); //;ATTenuation:RF?;ATTenuation:IF?
		sprintf(cBuf, "FREQuency?;FREQuency:SPAN?;TRAC:MED?;ATTenuation:RF:MODE?;ATTenuation:RF?;ATTenuation:IF?;DEModulation?;BANDwidth?;FREQuency:STEP?;FREQuency:STARt?;FREQuency:STOP?");
		OPT_RET Ret = g_pRemote->FastQueryStatus(cBuf, cRecv, 5000);

		CStringArray Array;

		int num = MultiByteToWideChar(0, 0, cRecv, -1, NULL, 0);
		wchar_t *wide = new wchar_t[num];
		MultiByteToWideChar(0, 0, cRecv, -1, wide, num);
		CCommon::SplitString(wide, L";", Array);

		double dCenterFre=1.0*_ttoi64(Array[0]) / MHZ_1;
		sz.Format(_T("%f"), dCenterFre);
		GetDlgItem(IDC_CENTERFRE)->SetWindowText(sz);
		g_dSignalFre = dCenterFre;

		int dSpan=1.0*_ttoi64(Array[1]) / KHZ_1;
		map<int, int>::iterator spaniter;
		spaniter = MapSpan.find(dSpan);
		if (spaniter != MapSpan.end())
			m_ComSpan.SetCurSel(spaniter->second);

		sMed = Array[2];
		if (0 <= sMed.Find(L"Spectrum"))
		{
			CButton* pBtn = (CButton*)(GetDlgItem(IDC_CK_SPEC));
			pBtn->SetCheck(TRUE);
		}
		if (0 <= sMed.Find(L"Audio"))
		{
			CButton* pBtn = (CButton*)(GetDlgItem(IDC_CK_AUD));
			pBtn->SetCheck(TRUE);
		}
		CString csRFMode = Array[3];
		int dAttRF;
		int dAttIF;
		if (csRFMode == L"NORM")
		{
			g_nAttMode = 1;
			dAttRF=_ttof(Array[4]);
			dAttIF=_ttof(Array[5]);
			dAttRF =dAttRF-ConfigIni.nRF_NM;
			dAttIF =dAttIF-ConfigIni.nIF_NM;

			m_Com_RFMode.SetCurSel(0);
		}
		if (csRFMode == L"LOWN")
		{
			g_nAttMode = 2;
			dAttRF=_ttof(Array[4]);
			dAttIF=_ttof(Array[5]);
			dAttRF =dAttRF-ConfigIni.nRF_LN;
			dAttIF =dAttIF-ConfigIni.nIF_LN;
			m_Com_RFMode.SetCurSel(1);
		}
		if (csRFMode == L"LOWD")
		{
			g_nAttMode = 3;
			dAttRF=_ttof(Array[4]);
			dAttIF=_ttof(Array[5]);
			dAttRF =dAttRF-ConfigIni.nRF_LD;
			dAttIF =dAttIF-ConfigIni.nIF_LD;
			m_Com_RFMode.SetCurSel(2);
		}

		map<int, int>::iterator attRFiter;
		attRFiter = AttRF.find(dAttRF);
		if (attRFiter != AttRF.end())
			m_ComAttRF.SetCurSel(attRFiter->second);

		map<int, int>::iterator attIFiter;
		attIFiter = AttIF.find(dAttIF);
		if (attIFiter != AttIF.end())
			m_ComAttIF.SetCurSel(attIFiter->second);

		
		CString csDem = Array[6];
		if (csDem == L"FM")
		{
			m_Com_Dem.SetCurSel(0);
		}
		if (csDem == L"AM")
		{
			m_Com_Dem.SetCurSel(1);
		}
		if (csDem == L"CW")
		{
			m_Com_Dem.SetCurSel(2);
		}
		if (csDem == L"PULSE")
		{
			m_Com_Dem.SetCurSel(3);
		}
		double dBW=1.0*_ttoi64(Array[7]) / KHZ_1;
		map<double, int>::iterator bwiter;
		bwiter = BW.find(dBW);
		if (bwiter != BW.end())
			m_Com_BW.SetCurSel(bwiter->second);


		double dStep=1.0*_ttoi64(Array[8]) / KHZ_1;
		map<double, int>::iterator stepiter;
		stepiter = Step.find(dStep);
		if (stepiter != Step.end())
			m_Com_Step.SetCurSel(stepiter->second);

		double dStartFre=1.0*_ttoi64(Array[9]) / MHZ_1;
		sz.Format(_T("%f"), dStartFre);
		GetDlgItem(IDC_STARTFRE)->SetWindowText(sz);

		double dStopFre=1.0*_ttoi64(Array[10]) / MHZ_1;
		sz.Format(_T("%f"), dStopFre);
		GetDlgItem(IDC_STOPFRE)->SetWindowText(sz);

		g_nMedMode = nMode;
	
		SetSignal(g_dSignalFre,g_dSignalAmp,g_nMedMode);

		if (nMode==MEA_DS)
		{		
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");
			
			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_MS)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_FA)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_IP3)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);

		}
		if (nMode ==MEA_IP2)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_FIFR)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_SIFR)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_FIR)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_SIR)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_SS)
		{


			GetDlgItem(IDC_BTB_CENTERFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_CENTERFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_CENTERFRE)->SetWindowText(L"");

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_LM)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_NF)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
		if (nMode ==MEA_PN)
		{
			GetDlgItem(IDC_BTN_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTFRE)->SetWindowText(L"");

			GetDlgItem(IDC_BTN_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STOPFRE)->SetWindowText(L"");


			m_Com_Step.SetCurSel(-1);
			GetDlgItem(IDC_COM_STEP)->EnableWindow(FALSE);

			m_Com_Dem.SetCurSel(-1);
			GetDlgItem(IDC_COM_DEM)->EnableWindow(FALSE);

			m_Com_BW.SetCurSel(-1);
			GetDlgItem(IDC_COM_BW)->EnableWindow(FALSE);

			//GetDlgItem(IDC_COM_ATTRF)->EnableWindow(FALSE);
			//GetDlgItem(IDC_COM_ATTIF)->EnableWindow(FALSE);
		}
}
void CDlgParaConfig::SetSignal(double signalFre,double signalAmp,int MedMode)
{

	CString szFre1,szAmp1,szFre2,szAmp2;

	if (MedMode==MEA_DS)
	{		
		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"AM/FM");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");


	}
	if (MedMode ==MEA_MS)
	{
		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"AM/FM");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}
	if (MedMode ==MEA_FA)
	{
		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"-50");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}
	if (MedMode ==MEA_IP3)
	{
		szFre1.Format(_T("%f"), signalFre+4);
		szAmp1.Format(_T("%f"), signalAmp);

		szFre2.Format(_T("%f"), signalFre+8);
		szAmp2.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(szFre2);
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"CW");
	}
	if (MedMode ==MEA_IP2)
	{
		szFre1.Format(_T("%f"), signalFre/2+200);
		szAmp1.Format(_T("%f"), signalAmp);

		szFre2.Format(_T("%f"), abs(signalFre/2-200));
		szAmp2.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(szFre2);
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"CW");
	}
	if (MedMode ==MEA_FIFR)
	{
		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}
	if (MedMode ==MEA_SIFR)
	{
		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}
	if (MedMode ==MEA_FIR)
	{
		szFre1.Format(_T("%f/%f"), 4800+signalFre,abs(4800-signalFre));
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}
	if (MedMode ==MEA_SIR)
	{
		szFre1.Format(_T("%f/%f"), 76.8+signalFre,abs(76.8-signalFre));
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}
	if (MedMode ==MEA_SS)
	{

		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"PULSE");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	

	}
	if (MedMode ==MEA_LM)
	{
		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"-50");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}
	if (MedMode ==MEA_NF)
	{
		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}
	if (MedMode ==MEA_PN)
	{
		szFre1.Format(_T("%f"), signalFre);
		szAmp1.Format(_T("%f"), signalAmp);

		GetDlgItem(IDC_SIGNAL1_FRE)->SetWindowText(szFre1);
		GetDlgItem(IDC_SIGNAL1_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL1_MOD)->SetWindowText(L"CW");

		GetDlgItem(IDC_SIGNAL2_FRE)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_AMP)->SetWindowText(L"");
		GetDlgItem(IDC_SIGNAL2_MOD)->SetWindowText(L"");
	}

}

void CDlgParaConfig::OnBnClickedBtbCenterfre()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	CString sz;
	bool bFre = FALSE;
	GetDlgItem(IDC_CENTERFRE)->GetWindowText(sz);
	double dCenterFre = _ttof(sz);

	g_dSignalFre = dCenterFre;

	for (int ConfigCount = 0;ConfigCount<ConfigIni.nCount;ConfigCount++)
	{
		if (((INT64)(dCenterFre*MHZ_1))==ConfigIni.nFreq[ConfigCount])
		{
			dCenterFre = ConfigIni.nFreqComp[ConfigCount]+(dCenterFre*MHZ_1);
			bFre = true;
			break;
		}
	}
	if (bFre == FALSE)
	{
		dCenterFre = (dCenterFre*MHZ_1);
	}

	//g_dSignalFre = dCenterFre/MHZ_1;
	SetSignal(g_dSignalFre,g_dSignalAmp,g_nMedMode);

	sprintf(Cmd, "FREQuency %I64d",(INT64)dCenterFre);
	g_pRemote->FastSendCmd(Cmd);

}


void CDlgParaConfig::OnBnClickedNormal()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)(GetDlgItem(CK_NORMAL));
	m_pView->SetTraceVisable(CMR3300USBView::WAVE_NORMAL, pBtn->GetCheck());

}


void CDlgParaConfig::OnBnClickedMax()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)(GetDlgItem(CK_MAX));
	m_pView->SetTraceVisable(CMR3300USBView::WAVE_MAX, pBtn->GetCheck());
}


void CDlgParaConfig::OnBnClickedMin()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)(GetDlgItem(CK_MIN));
	m_pView->SetTraceVisable(CMR3300USBView::WAVE_MIN, pBtn->GetCheck());
}


void CDlgParaConfig::OnBnClickedAvg()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)(GetDlgItem(CK_AVG));
	m_pView->SetTraceVisable(CMR3300USBView::WAVE_AVG, pBtn->GetCheck());
}


void CDlgParaConfig::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pView->ResetTrace();
}


void CDlgParaConfig::OnBnClickedBtnRef()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[50];
	CString sz;

	GetDlgItem(IDC_REF)->GetWindowText(sz);
	int nRef = _ttof(sz);
	//if (nRef<-50)
	//{
	//	nRef = -50;
	//}
	//if (nRef>200)
	//{
	//	nRef = nRef;
	//}
	m_pView->SetRef(nRef);
}



void CDlgParaConfig::OnCbnSelchangeCmbSpan()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sz;
	char Cmd[50];
	UINT nSpan = 40000;
	g_bSpan = false;
	int nSelect = m_ComSpan.GetCurSel();
	switch (nSelect)
	{
	case 0:
		nSpan = 80000;
		g_bSpan = true;
		break;
	case 1:
		nSpan = 40000;
		break;
	case 2:
		nSpan = 20000;
		break;
	case 3:
		nSpan = 10000;
		break;
	case 4:
		nSpan = 5000;
		break;
	case 5:
		nSpan = 2000;
		break;
	case 6:
		nSpan = 1000;
		break;
	case 7:
		nSpan = 500;
		break;
	case 8:
		nSpan = 200;
		break;
	case 9:
		nSpan = 100;
		break;
	case 10:
		nSpan = 50;
		break;
	case 11:
		nSpan = 20;
		break;
	case 12:
		nSpan = 10;
		break;
	case 13:
		nSpan = 5;
		break;
	case 14:
		nSpan = 2;
		break;
	case 15:
		nSpan = 1;
		break;
	}

	sprintf(Cmd, "FREQuency:SPAN %I64d",(INT64)(nSpan*KHZ_1));
	g_pRemote->FastSendCmd(Cmd);

}


void CDlgParaConfig::OnBnClickedCkSpec()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[150];
	sMed =L"";
	CButton* pBtn = (CButton*)(GetDlgItem(IDC_CK_SPEC));
	if (pBtn->GetCheck())
	{
		sMed = L"Spectrum";
	}
	pBtn = (CButton*)(GetDlgItem(IDC_CK_AUD));
	if (pBtn->GetCheck())
	{
		sMed = sMed+L","+L"Audio";
	}

	int num1 = WideCharToMultiByte(CP_OEMCP, NULL, sMed, -1, NULL, 0, NULL, FALSE);
	char *pchar = new char[num1];
	WideCharToMultiByte(CP_OEMCP, NULL, sMed, -1, pchar, num1, NULL, FALSE);

	sprintf(Cmd, "TRAC:MED %s",pchar);
	g_pRemote->FastSendCmd(Cmd);

}


void CDlgParaConfig::OnBnClickedCkAud()
{
	// TODO: 在此添加控件通知处理程序代码
	char Cmd[150];
	sMed =L"";
	CButton* pBtn = (CButton*)(GetDlgItem(IDC_CK_SPEC));
	if (pBtn->GetCheck())
	{
		sMed = L"Spectrum";
	}
	pBtn = (CButton*)(GetDlgItem(IDC_CK_AUD));
	if (pBtn->GetCheck())
	{
		sMed = sMed+L","+L"Audio";
	}

	m_pView->SetDataVisable(L"Audio", pBtn->GetCheck());

	int num1 = WideCharToMultiByte(CP_OEMCP, NULL, sMed, -1, NULL, 0, NULL, FALSE);
	char *pchar = new char[num1];
	WideCharToMultiByte(CP_OEMCP, NULL, sMed, -1, pchar, num1, NULL, FALSE);

	sprintf(Cmd, "TRAC:MED %s",pchar);
	g_pRemote->FastSendCmd(Cmd);
}


void CDlgParaConfig::OnCbnSelchangeComRfmode()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSelect = m_Com_RFMode.GetCurSel();
	char Cmd[50];
	switch (nSelect)
	{
	case 0:
		g_pRemote->FastSendCmd("ATTenuation:RF:MODE NORM");
		g_nAttMode =1;
		OnCbnSelchangeComAttrf();
		OnCbnSelchangeComAttif();
		break;
	case 1:
		g_pRemote->FastSendCmd("ATTenuation:RF:MODE LOWN");
		g_nAttMode =2;
		OnCbnSelchangeComAttrf();
		OnCbnSelchangeComAttif();
		break;
	case 2:
		g_pRemote->FastSendCmd("ATTenuation:RF:MODE LOWD");
		g_nAttMode =3;
		OnCbnSelchangeComAttrf();
		OnCbnSelchangeComAttif();
		break;
	}

}


void CDlgParaConfig::OnCbnSelchangeComDem()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSelect = m_Com_Dem.GetCurSel();
	switch (nSelect)
	{
	case 0:
		g_pRemote->FastSendCmd("DEModulation FM");
		break;
	case 1:
		g_pRemote->FastSendCmd("DEModulation AM");
		break;
	case 2:
		g_pRemote->FastSendCmd("DEModulation PM");
		break;
	case 3:
		g_pRemote->FastSendCmd("DEModulation CW");
		break;
	case 4:
		g_pRemote->FastSendCmd("DEModulation LSB");
		break;
	case 5:
		g_pRemote->FastSendCmd("DEModulation USB");
		break;
	case 6:
		g_pRemote->FastSendCmd("DEModulation PULSE");
		break;
	case 7:
		g_pRemote->FastSendCmd("DEModulation IQ");
		break;
	case 8:
		g_pRemote->FastSendCmd("DEModulation DMR");
		break;
	case 9:
		g_pRemote->FastSendCmd("DEModulation DPMR");
		break;
	}
}


void CDlgParaConfig::OnCbnSelchangeComBw()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sz;
	char Cmd[50];
	double dBW = 0;

	int nSelect = m_Com_BW.GetCurSel();
	switch (nSelect)
	{
	case 0:
		dBW = 500;
		break;
	case 1:
		dBW = 300;
		break;
	case 2:
		dBW = 200;
		break;
	case 3:
		dBW = 150;
		break;
	case 4:
		dBW = 120;
		break;
	case 5:
		dBW = 50;
		break;
	case 6:
		dBW = 30;
		break;
	case 7:
		dBW = 15;
		break;
	case 8:
		dBW = 12;
		break;
	case 9:
		dBW = 9;
		break;
	case 10:
		dBW = 6;
		break;
	case 11:
		dBW = 2.4;
		break;
	case 12:
		dBW = 1.5;
		break;
	}
	sprintf(Cmd, "BANDwidth %I64d",(INT64)(dBW*KHZ_1));
	g_pRemote->FastSendCmd(Cmd);

}


void CDlgParaConfig::OnCbnSelchangeComStep()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sz;
	char Cmd[50];
	double dStep = 0;

	int nSelect = m_Com_Step.GetCurSel();
	switch (nSelect)
	{
	case 0:
		dStep = 500;
		break;
	case 1:
		dStep = 200;
		break;
	case 2:
		dStep = 100;
		break;
	case 3:
		dStep = 50;
		break;
	case 4:
		dStep = 25;
		break;
	case 5:
		dStep = 12.5;
		break;
	case 6:
		dStep = 6.25;
		break;
	case 7:
		dStep = 3.125;
		break;
	}
	sprintf(Cmd, "FREQuency:STEP %I64d",(INT64)(dStep*KHZ_1));
	g_pRemote->FastSendCmd(Cmd);


}




void CDlgParaConfig::OnBnClickedBtnStartfre()
{
	// TODO: 在此添加控件通知处理程序代码

	char Cmd[50];
	CString sz;

	GetDlgItem(IDC_STARTFRE)->GetWindowText(sz);
	double dStartFre = _ttof(sz);

	sprintf(Cmd, "FREQuency:STARt %I64d",(INT64)(dStartFre*MHZ_1));
	g_pRemote->FastSendCmd(Cmd);

}


void CDlgParaConfig::OnBnClickedBtnStopfre()
{
	// TODO: 在此添加控件通知处理程序代码

	char Cmd[50];
	CString sz;

	GetDlgItem(IDC_STOPFRE)->GetWindowText(sz);
	double dStopFre = _ttof(sz);

	sprintf(Cmd, "FREQuency:STOP %I64d",(INT64)(dStopFre*MHZ_1));
	g_pRemote->FastSendCmd(Cmd);

}


void CDlgParaConfig::OnCbnSelchangeComAttrf()
{
	// TODO: 在此添加控件通知处理程序代码

	CString sz;
	char Cmd[50];
	UINT nAtt = 0;

	int nSelect = m_ComAttRF.GetCurSel();
	switch (nSelect)
	{
	case 0:
		nAtt = 0;
		break;
	case 1:
		nAtt = 2;
		break;
	case 2:
		nAtt = 4;
		break;
	case 3:
		nAtt = 6;
		break;
	case 4:
		nAtt = 8;
		break;
	case 5:
		nAtt = 10;
		break;
	case 6:
		nAtt = 12;
		break;
	case 7:
		nAtt = 14;
		break;
	case 8:
		nAtt = 16;
		break;
	case 9:
		nAtt = 18;
		break;
	case 10:
		nAtt = 20;
		break;
	case 11:
		nAtt = 22;
		break;
	case 12:
		nAtt = 24;
		break;
	case 13:
		nAtt = 26;
		break;
	case 14:
		nAtt = 28;
		break;
	case 15:
		nAtt = 30;
		break;
	}
	if (g_nAttMode ==1)
	{
		nAtt = nAtt +ConfigIni.nRF_NM;
	}
	if (g_nAttMode ==2)
	{
		nAtt = nAtt +ConfigIni.nRF_LN;
	}
	if (g_nAttMode ==3)
	{
		nAtt = nAtt +ConfigIni.nRF_LD;
	}

	sprintf(Cmd, "ATTenuation:RF %d",(int)(nAtt));
	g_pRemote->FastSendCmd(Cmd);
}


void CDlgParaConfig::OnCbnSelchangeComAttif()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sz;
	char Cmd[50];
	UINT nAtt = 0;

	int nSelect = m_ComAttIF.GetCurSel();
	switch (nSelect)
	{
	case 0:
		nAtt = 0;
		break;
	case 1:
		nAtt = 1;
		break;
	case 2:
		nAtt = 2;
		break;
	case 3:
		nAtt = 3;
		break;
	case 4:
		nAtt = 4;
		break;
	case 5:
		nAtt = 5;
		break;
	case 6:
		nAtt = 6;
		break;
	case 7:
		nAtt = 7;
		break;
	case 8:
		nAtt = 8;
		break;
	case 9:
		nAtt = 9;
		break;
	case 10:
		nAtt = 10;
		break;
	case 11:
		nAtt = 11;
		break;
	case 12:
		nAtt = 12;
		break;
	case 13:
		nAtt = 13;
		break;
	case 14:
		nAtt = 14;
		break;
	case 15:
		nAtt = 15;
		break;
	case 16:
		nAtt = 16;
		break;
	case 17:
		nAtt = 17;
		break;
	case 18:
		nAtt = 18;
		break;
	case 19:
		nAtt = 19;
		break;
	case 20:
		nAtt = 20;
		break;
	}
	if (g_nAttMode ==1)
	{
		nAtt = nAtt +ConfigIni.nIF_NM;
	}
	if (g_nAttMode ==2)
	{
		nAtt = nAtt +ConfigIni.nIF_LN;
	}
	if (g_nAttMode ==3)
	{
		nAtt = nAtt +ConfigIni.nIF_LD;
	}

	sprintf(Cmd, "ATTenuation:IF %d",(int)(nAtt));
	g_pRemote->FastSendCmd(Cmd);
}


BOOL CDlgParaConfig::PreTranslateMessage(MSG* pMsg)  
{  
	if(WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)     
	{       
		if(GetFocus()== GetDlgItem(IDC_CENTERFRE)) 
		{  
			UpdateData(TRUE);
			OnBnClickedBtbCenterfre();
			UpdateData(FALSE);

		}  

		if(GetFocus()== GetDlgItem(IDC_REF))  
		{
			UpdateData(TRUE);
			OnBnClickedBtnRef();
			UpdateData(FALSE);
		}

		if(GetFocus()== GetDlgItem(IDC_STARTFRE)) 
		{  
			UpdateData(TRUE);
			OnBnClickedBtnStartfre();
			UpdateData(FALSE);

		}  

		if(GetFocus()== GetDlgItem(IDC_STOPFRE))  
		{
			UpdateData(TRUE);
			OnBnClickedBtnStopfre();
			UpdateData(FALSE);

		}
		return true;
	} 
	return CDialogScroll::PreTranslateMessage(pMsg);
}




void CDlgParaConfig::OnBnClickedCkSpectro()
{
	// TODO: 在此添加控件通知处理程序代码

	CButton* pBtn = (CButton*)(GetDlgItem(IDC_CK_SPECTRO));
	if (pBtn->GetCheck())
	{
		g_bSpectroView = true;
	}
	else
	{
		g_bSpectroView = false;
	}
	g_bIsSpectroEN = true;
}
void CDlgParaConfig::Detection(BOOL bMode)
{
	if (bMode == TRUE)
	{
		//m_bDetMode = TRUE;
		g_pRemote->FastSendCmd("RX:ADVAnced ON");
		g_pRemote->FastSendCmd("MEASure:DETector MIN");
	}
	else
	{
	//	m_bDetMode = FALSE;
		g_pRemote->FastSendCmd("RX:ADVAnced OFF");
		g_pRemote->FastSendCmd("MEASure:DETector AVG");
	}
//	OnCbnSelchangeComDet();
}