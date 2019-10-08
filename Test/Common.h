#pragma once


struct TASK_ITEM
{
	__int64 nCenter;
	__int64 nBW;
	int nAtt;
	char sMode[20];
	int nNoise;
};

//struct SaStatus
//{
//	__int64 StartFreq;
//	__int64 StopFreq;
//	__int64 CenterFreq;
//	__int64 FreqSpan;
//	int RBW;
//	double Ref;
//	int Att;
//	int nPoint;
//};

#pragma pack ( push, 1 )
struct STRUCT_HEAD_DATA
{
	UINT version;//版本号，当前为0//没有
	UINT dgnum;// DG_GENERIC数量//有多少包数据
};

struct STRUCT_GENERIC_DATA//每包数据结构
{
	UINT tag;//类别,具体值含义参看下表
	UINT version;//类别包版本号,设备更新因此数据内信息可能发生变化,当前版本号参看类别表
	char chnum;//通道数量,1单路,区域为多路
	char chid;//通道号
	USHORT state;//状态,参看状态附录
	UINT length;//data长度
};

struct STRUCT_LEVEL_DATA
{
	__int64 freq;//频率
	__int64 bw;//带宽
	int att;
	float level;//电平
	float field;//场强
};

struct STRUCT_SPECTRUM_HEAD //dBuV*10
{
	__int64 freq;// 频率
	__int64 span; //带宽
	int att;
	UINT pt;//点数 421/571
};

struct STRUCT_ITU_DATA
{
	__int64 freq;//频率
	__int64 betabw;//beta%测量带宽值
	__int64 xdbbw; //xdB测量带宽值
	float am;//调幅度
	float am_pos; //正调幅度
	float am_neg; //负调幅度
	float fm;//调频频偏
	float fm_pos; //正调频频偏
	float fm_neg; //负调频频偏
	float pm; //调相角度
	float pm_pos; //调相最大角度
	float pm_neg; //调相最小角度
	int mod;//调制识别结果,值从-1开始依次对应Error, AM, FM, 2FSK, 4FSK, 2PSK, 4PSK, 2ASK, 4ASK, DSB, CW, VSB, Noise, UnKnown
};

struct STRUCT_SCAN_HEAD
{
	__int64 start;//扫描起始频率
	__int64 stop; //扫描结束频率
	__int64 step; //扫描步进频率
	UINT frameid; //扫描桢号,暂时未使用
	UINT total;//一桢数据总计点数
	UINT pdloc;//该包数据在一桢扫描数据的点位置，压缩无效0
	UINT pdpt;//该包数据包含点数，实际发出点数
};

struct STRUCT_SCAN_HEAD_FAST
{
	__int64 start;//扫描起始频率
	__int64 stop; //扫描结束频率
	__int64 step; //扫描步进频率
	UINT frameid; //扫描桢号,暂时未使用
	UINT pdpt;//该包数据包含点数，实际发出点数
};

struct STRUCT_AUDIO_HEAD
{
	__int64 freq;//频率
	__int64 bw;//带宽
	__int64 samplerate;//采样率
	UINT reserved;
	UINT len;//音频点书
};

struct STRUCT_IQ_HEAD
{
	__int64 freq;
	__int64 bw;
	__int64 samplerate;
	int att;
	int pt;
};

//
//struct  STRUCT_DFIND_DATA
//{
//	__int64 freq;
//	__int64 bwDF;
//	int system;//测向体制，用不用的数值表示测向结果采用的是哪一种测向体制
//	int reserved;
//	float level;
//	float azimuth;//示向度（角度值），有效范围：[0, 360)
//	float quality;//测向质量，有效范围：[0, 100]
//	short extra_size;//额外数据的长度，通常为零，若为测试阶段
//
//};
//
//struct  STRUCT_DFPAN_DATA
//{
//	__int64 freq;
//	__int64 bwDF;
//	int system;//测向体制，用不用的数值表示测向结果采用的是哪一种测向体制
//	int pt;
//};

struct STRUCT_MSCAN_LIST_DSP
{
	__int64 mFreqCent;
	int mBw;
	short mSql;
	char mDemode;
	char mAtt;
};

struct STRUCT_CHANNEL_PARA
{
	bool m_bChannelEnble;
	USHORT m_ChannelPort;
};
#pragma pack ( pop )

struct FreScanStatus
{
	__int64 StartFreq;
	__int64 StopFreq;
	__int64 Step; //扫描步进频率
	__int64 total; //扫描步进频率
	double RBW;
	double Ref;
	int Att;
	bool Ampli;
};

enum FREQ_DEF {
	HZ_1 = 1,
	KHZ_1 = 1000,
	KHZ_30 = 30000,
	KHZ_100 = 100000,
	MHZ_1 = 1000000,
	GHZ_1 = 1000000000,
};
// 波形显示标识
enum WAVE_OUTPUT
{
	WAVE_NORMAL = 0,
	WAVE_MAX = 4,
	WAVE_MIN = 5,
	WAVE_AVG = 2
};
struct Section
{
	// 无效标识符
	static const int NA = -20000;

	// 数据缓冲区大小
	static const int DATA_BUF = 1000000;

	// 数据区有效数据长度
	int nDataLen;

	// 波形输出类型,最大保持，最小保持，平均等
	WAVE_OUTPUT OutPut;

	// 数据区指针
	double* fData;

	// 平均次数计数
	long long nAvgTimes;

	Section()
	{
		OutPut = WAVE_NORMAL;
		nDataLen = 0;
		nAvgTimes = 0;
		fData = new double[DATA_BUF];
	}

	~Section()
	{
		delete[] fData;
	}
};

const int MEA_TYPE_MAX = 9;
const int DATA_TYPE_IQ = 1; //IQ数据
const int DATA_TYPE_LEVEL = 2;//电平数据
const int DATA_TYPE_SPECTRUM = 4;//	频谱数据
const int DATA_TYPE_DFIND = 8;//单频率测向数据
const int DATA_TYPE_DFPAN = 16;//宽带测向数据（FFT测向）
const int DATA_TYPE_AUDIO = 32;//	音频数据
const int DATA_TYPE_ITU = 64;//ITU测量数据
const int DATA_TYPE_SCAN = 128;//频谱扫描数据
const int DATA_TYPE_FSCAN = 130;//频谱扫描数据
const int DATA_TYPE_MSCAN = 132;//频谱扫描数据
const int DATA_TYPE_TDOA = 256;//测向扫描数据

enum MARKER_DEF
{

	MARK_PEAK_SEARCH = 0,
	MARK_NORMAL = 1
};
class CCommon
{
public:
	CCommon();
	virtual ~CCommon();
	static CString GetCurTimeString(CString szFormat);
	static void SplitString(CString str, CString split, CStringArray & strGet);
	static CString Freq2Str(INT64 nFreq, const TCHAR* tcFormat = _T("%.3lf %s"));
};

extern CString g_IP;
extern BOOL g_bIsRunning;
extern volatile bool g_bIsRun;
extern int g_nCount ;
extern CString g_sMed;

