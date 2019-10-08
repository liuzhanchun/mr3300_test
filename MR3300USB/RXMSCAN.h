#pragma once
#include "Measure.h"
#include "DataDef.h"

class CRXMSCAN : public CMeasure
{
public:
	CRXMSCAN(void);
	~CRXMSCAN(void);

protected:
	void virtual ReadData ( void );
	int virtual  GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status);
	int virtual  GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata );

};

extern CRXMSCAN *g_pRXMSCAN;

