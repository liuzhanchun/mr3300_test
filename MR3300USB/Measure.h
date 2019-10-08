#pragma once
#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

class CMeasure
{



public:
	CMeasure(void);
	~CMeasure(void);
	bool DataPro ( bool meas=true );
	int GetMeasID ( void ) { return m_nMeasID; } //返回当前测量类型
	void SetMeasID (int measid){m_nMeasID=measid;}
	bool GetDataPro (double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu ,WaveStatus &Status);
	bool GetLevelPro(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata);

	vector<TASK_ITEM> m_vtTask;
	
protected:
	virtual void ReadData ( void ) = 0;  
	virtual int GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status) = 0;
	virtual int GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata) = 0;
	int m_nMeasID; //测量类型标记, 表示是哪种测量, 基类(含子基类)此ID都为NULL
	queue <double> m_qlevel;
	void clear(queue<double>& q) {
		queue<double> empty;
		swap(empty, q);
	}
	STRUCT_RESP_LEVEL_DATA RespLevel;
	STRUCT_HEAD_DATA file_head;
	STRUCT_GENERIC_DATA generic_data;
	STRUCT_LEVEL_DATA level_data;
	STRUCT_SPECTRUM_HEAD  spec_data;
	STRUCT_SCAN_HEAD scan_data;
	STRUCT_SCAN_HEAD_FAST fscan_data;
	STRUCT_ITU_DATA itu_data;
	STRUCT_DFIND_IQ dfiqHead;

	STRUCT_IQ_HEAD IQData;
//	STRUCT_DT_FRAME Mess;
	Section sections;
	Section levelsections;
	CCriticalSection *m_pLevel;
	CCriticalSection *m_pCSData;
	

};
extern CMeasure *g_pMea;


