#include "StdAfx.h"
#include "MeasSwitch.h"
#include "Measure.h"
#include "RXFFM.h"
#include "RXPSCAN.h"
#include "RXFSAN.h"
#include "RXMSCAN.h"
#include "Response.h"
#include "RXDFIND.h"
#include "RXIQ.h"
#include "RXFPSCAN.h"

CMeasSwitch CMeasSwitch::m_Instance;
CMeasSwitch &g_MeasSwitch = CMeasSwitch::GetInstance();

CMeasSwitch::CMeasSwitch(void)
{
	m_nPostID = RXNONE;
	m_pCS = new CCriticalSection();
}


CMeasSwitch::~CMeasSwitch(void)
{
	delete m_pCS;
}
void CMeasSwitch::SwitchMeas ( int id, bool switch_now )
{

	m_nPostID = id;

	//if ( g_pMea == NULL || id != g_pMea->GetMeasID() ) //NULL:刚开机时
	//if ( g_pMea == NULL) //NULL:刚开机时
	//{ 	
		if ( g_pMea != NULL )//不是开机的时候
		{			
			delete g_pMea;
		}
		//id = RXFFM;
		SetPointerNull(); //////////////////////////////注意: 新添加对象, 要在这里加=NULL

		switch ( id )
		{
		case RXMSCAN: //rx
			g_pRXMSCAN = new CRXMSCAN;
			g_pMea = g_pRXMSCAN;
			break;

		case RXPSCAN: //rx
	
			g_pRXPSCAN = new CRXPSCAN;
			g_pMea = g_pRXPSCAN;
			break;

		case RXFSCAN: //rx
			g_pRXFSCAN = new CRXFSAN;
			g_pMea = g_pRXFSCAN;
			break;
		case SYSRESP: //频响
			g_pRes = new CResponse;
			g_pMea = g_pRes;
			break;
		case RXDFIND:  //双通道测向
			g_pRXDFIND = new CRXDFIND;
			g_pMea = g_pRXDFIND;
			break;
		case RXIQ:  //  IQ数据
			g_pRXIQ = new CRXIQ;
			g_pMea = g_pRXIQ;
			break;

		case RXFPSCAN:  //  FPSCAN
			g_pRXFPSCAN = new CRXFPSCAN;
			g_pMea = g_pRXFPSCAN;
			break;
		default: 
			g_pRXFFM = new CRXFFM;
			g_pMea = g_pRXFFM;
			break;   

		}

	//}
}

void CMeasSwitch::SetPointerNull ( void )
{

	g_pMea = NULL;		
	g_pRXFFM = NULL;
	g_pRXPSCAN = NULL;
	g_pRXFSCAN = NULL;
	g_pRXMSCAN = NULL;
	g_pRes = NULL;
	g_pRXDFIND =NULL;
	g_pRXIQ =NULL;
	g_pRXFPSCAN = NULL;
	//g_pRXFscan = NULL; 
	//g_pRXMscan = NULL;
	//g_pRXPscan = NULL;
	//g_pCal = NULL;	
	//g_pResp = NULL;			
	//g_pUpdate = NULL; 		
}



void CMeasSwitch::EnterLock ( void )
{
	m_pCS->Lock();
}
void CMeasSwitch::LeaveLock ( void )
{
	m_pCS->Unlock();
}