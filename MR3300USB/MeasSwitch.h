#pragma once
#include "DataDef.h"
class CMeasSwitch
{
public:
	CMeasSwitch ( void );
	CMeasSwitch ( const CMeasSwitch & ); //disallowed
	CMeasSwitch & operator= ( CMeasSwitch & ); //disallowed
	~CMeasSwitch ( void );
	static CMeasSwitch m_Instance;  //Î¨Ò»µÄÊµÀý

public:
	static CMeasSwitch &GetInstance ( void ) { return m_Instance; }
	void Initial ( void );
	void SwitchMeas ( int id, bool switch_now = true );

	void EnterLock ( void );
	void LeaveLock ( void );


private:
	void SetPointerNull ( void );

	int m_nPostID;
	CCriticalSection *m_pCS;


};


extern CMeasSwitch &g_MeasSwitch;


