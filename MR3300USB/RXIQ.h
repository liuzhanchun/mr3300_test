#pragma once
#include "Measure.h"
#include "DataDef.h"

class CRXIQ : public CMeasure
{
public:
	CRXIQ(void);
	~CRXIQ(void);

protected:
	void virtual ReadData ( void );
	int virtual  GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status);
	int virtual  GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata);

private:

	double *Ibuf;
	double *Qbuf;

	FILE *m_fp;
};

extern CRXIQ *g_pRXIQ;

