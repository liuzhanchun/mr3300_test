#pragma once
#include "Measure.h"
#include "DataDef.h"
#include "IniFile.h"
class CRXDFIND : public CMeasure
{
public:
	CRXDFIND(void);
	~CRXDFIND(void);

protected:
	void virtual ReadData ( void );
	int virtual  GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status);
	int virtual  GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata);
private:
	CIniFile m_IniFile;
	double *Ibuf;
	double *Qbuf;

	FILE *m_fp;
};
extern CRXDFIND *g_pRXDFIND;

