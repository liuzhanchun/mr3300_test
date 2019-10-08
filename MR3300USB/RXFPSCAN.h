#pragma once
#include "Measure.h"
#include "DataDef.h"
//const int DOT_NUM_SA = 1601;

#pragma pack ( push, 1 )
struct STRUCT_PSCAN_DATA
{
	short Lev[800 ];
	short Lev_Avg[ 800 ];
	int  NNumber[ 800 ];// DG_GENERIC数量//有多少包数据

};
#pragma pack ( pop )


class CRXFPSCAN: public CMeasure
{
public:
	CRXFPSCAN(void);
	~CRXFPSCAN(void);
protected:
	int rand_X(int x);

	void virtual ReadData ( void );
	int virtual  GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status);
	int virtual  GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata);


	STRUCT_PSCAN_DATA fscan_lev;

};
extern CRXFPSCAN *g_pRXFPSCAN;
extern double g_nFPSCAN[800];
