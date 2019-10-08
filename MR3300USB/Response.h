#pragma once
#include "Measure.h"
#include "DataDef.h"


namespace resp_ns
{
	enum RESP_FITER_RESULT
	{
		FITER_NONE = -2 ,
		FITER_FLASE = -1,
		FITER_OK,
	};

	//9K频响
	const __int64 RESP_FREQ_START_9K_LOW = KHZ_9; //从9k开始打
	const __int64 RESP_FREQ_START_9K_HIGH = KHZ_20; //从20k开始打
	const __int64 RESP_FREQ_START_9K_STOP = KHZ_50; //打到50K
	const __int64 RESP_STEP_9K_LOW = KHZ_3;  //打频响时的频率步进
	const __int64 RESP_STEP_9K_HIGH= KHZ_10;  //打频响时的频率步进
	const int RESP_DOT_NUM_9K = 8;//频率为9K,12K,15K,18K,20K,30k,40k,50K,共8个	
	const short RESP_LOW_DATA = 247; //6.02 /DB_RANGE * AD_RANGE;
	const double D_VALUE_DMB_MV_50 = -9.03221;
	const double D_VALUE_DMB_MV_75 = -7.448586716489;
	const double SIGNAL_GEN_ATT[]={ 10,30,60,100,200,300,600,1000,2000,3000,5000,5000 };
	//正常dbm和mv换算 dbm=10lg(1000mV2/50),低频频响输入为峰值dbm= 10lg((0.707mV×1000/2)2/50) 差值= 10lg(0.707/2)2=-0.903221;

	const __int64 RESP_FREQ_START = MHZ_40;
	const __int64 RESP_FREQ_STOP = GHZ_8; //7995M
	const __int64 RESP_STEP = MHZ_5;  //打频响时的频率步进
	const int RESP_FIELD_NUM_NORMAL = 11;
	const int RESP_FIELD_NUM_LOWDISTORT = 7;//0-30
	const int RESP_FIELD_NUM_LOWNOISE = 5;//0-20
	const int RESP_FIELD_NUM = RESP_FIELD_NUM_NORMAL + RESP_FIELD_NUM_LOWDISTORT + RESP_FIELD_NUM_LOWNOISE;   //打幅度频响场数(仅常温)

	const int RESP_DOT_NUM   = ( RESP_FREQ_STOP - RESP_FREQ_START ) / RESP_STEP + 1;  
	const int FREQ_RESP_NUM = 11;     //频率计数修正的点数1 MHz~2991,步进299M

	const int RESP_ID_FAST   = RESP_FIELD_NUM ; //打快扫频响的场的ID
	const int RESP_ID_MAX = RESP_ID_FAST+1;//幅度频响+fast

	const int UPTIME_MIN = 600; //打频响前要求系统启动时间至少多少秒

	const int RESP_DOT_NUM_FAST = 800; //快扫下频响的点数, 带宽20M(近似)
	const int FREQ_STEP_FAST = KHZ_50;
	const __int64 FAST_CORR_SPAN = MHZ_40;  
} //end namespace declare
const int FILE_VER_RESP = 2;
#pragma pack ( push, 1 )

//struct STRUCT_FAST_RESP //快扫频响
//{
//	FILE_HEAD Head;            //文件头, 包括, 版本, 时间, 长度, 校验和, ver = 1
//	bool bSuccess;             //校准是否成功, true成功, false失败
//	short shResp[resp_ns::RESP_DOT_NUM_FAST];  //频响数据, +-500, 代表+-5db
//};
struct STRUCT_FAST_RESP //快扫频响
{
	FILE_HEAD Head;            //文件头, 包括, 版本, 时间, 长度, 校验和, ver = 1
	bool bSuccess; 
	UCHAR cReserve[21];
	short nFastRespNum;//校准是否成功, true成功, false失败
	short shResp[2000];  //频响数据, +-500, 代表+-5db
};
struct STRUCT_CAL_ONE //幅度校准
{     
	short CalDataNum;//中频衰减器档数
	short cReserve[9];
	short shSpanData[10][20];  //最多十个中频滤波器带宽,衰减器最多20档
};

struct STRUCT_CAL //频响(幅度/频率)
{
	FILE_HEAD stHead;
	bool bRespFinish;
	UCHAR SpanNum;
	UCHAR cReserve[100];
	STRUCT_CAL_ONE shCalData[3];
};
//struct STRUCT_RESP //频响(幅度/频率)
//{
//	FILE_HEAD stHead;  //带版本号(FILE_VER_CAL_RESP), 时间, 长度, 校验和的文件头
//	short shRespData[resp_ns::RESP_FIELD_NUM][resp_ns::RESP_DOT_NUM];//幅度频响数据, AD值, ad=10代表从dsp读的ad值再加10才是准确
//	float fCalOut;                    //10M校准源输出误差, dB值, 校准源修正加此修正才是 理论值	
//	float fTem[resp_ns::RESP_FIELD_NUM];       //每场频响数据的温度,摄氏度
//	__int64 FreqData[resp_ns::FREQ_RESP_NUM];  //频率计数点的修正, 如100, 代表从dsp读出的值再加100hz才是准确读数
//	bool bRespFinish[resp_ns::RESP_FIELD_NUM]; //每场频响数据是否完整, 常温
//	char cReserve[100];                //保留, 全0
//};
struct STRUCT_RESP_ONE //频响(幅度/频率)
{
	int nFieldPn;//是第几场
	int nRespNum;
	bool bRespFinish;
	char cReserve[20];
	short shRespData[2000];
};
struct STRUCT_RESP //频响(幅度/频率)
{
	FILE_HEAD stHead;  //带版本号(FILE_VER_CAL_RESP), 时间, 长度, 校验和的文件头
	UCHAR cReserve[100];
	STRUCT_RESP_ONE shRespData[30];
};

struct STRUCT_RESP_LOW //频响(幅度/频率)
{
	FILE_HEAD stHead;  //带版本号(FILE_VER_CAL_RESP), 时间, 长度, 校验和的文件头
	float fTem[resp_ns::RESP_FIELD_NUM];       //每场频响数据的温度,摄氏度
	short shRespData[resp_ns::RESP_FIELD_NUM][resp_ns::RESP_DOT_NUM_9K];//幅度频响数据, AD值, ad=10代表从dsp读的ad值再加10才是准确
	bool bRespFinish[resp_ns::RESP_FIELD_NUM]; //每场频响数据是否完整, 常温
	char cReserve[100];                //保留, 全0
};

//struct STRUCT_FAST_RESP //快扫频响
//{
//	FILE_HEAD Head;            //文件头, 包括, 版本, 时间, 长度, 校验和, ver = 1
//	bool bSuccess;             //校准是否成功, true成功, false失败
//	short shResp[resp_ns::RESP_DOT_NUM_FAST];  //频响数据, +-500, 代表+-5db
//};

#pragma pack ( pop )

class CResponse : public CMeasure
{
public:
	CResponse(void);
	~CResponse(void);

protected:
	void virtual ReadData ( void );
	int virtual  GetData(double*& data, int& nLen, __int64 &freq, float &level, STRUCT_ITU_DATA &itu,WaveStatus &Status);
	int virtual  GetLevel(queue <double>& data, int& nLen,__int64 &freq,double*& leveldata);
private:
	bool ReadRespFile(STRUCT_RESP *data);
	void WriteRespFile ( STRUCT_RESP *data );
	void WriteFastRespFile ( const STRUCT_FAST_RESP *data ); 
	void WriteRespCalFile ( STRUCT_CAL *data ); 
	short m_shField[2000]; //最多点数为2000,一般少于2000
	STRUCT_RESP m_MemCorr; //频响修正文件, 从硬盘读出, 打完一场, 在内存更新一下, 再写入
	STRUCT_CAL m_AmpCalData;
};
extern CResponse *g_pRes;

