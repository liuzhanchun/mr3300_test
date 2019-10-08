#ifndef __DATA_DEF__
#define __DATA_DEF__
#include <vector>
using namespace std;


const int LevelDot =300;
struct TASK_ITEM
{
	__int64 nCenter;
	__int64 nBW;
	int nAtt;
	char sMode[20];
	int nNoise;
};

#pragma pack(1)



const int 	RXNONE=0;
const int 	RXFFM = 1;
const int 	RXMSCAN = 2;
const int 	RXPSCAN = 3;
const int 	RXFSCAN = 4;
const int   RXDFIND = 5;
const int   RXIQ = 6;
const int   RXFPSCAN = 7;
const int   MEA_DS = 8;
const int   MEA_MS = 9;
const int   MEA_FA = 10;
const int   MEA_IP3 = 11;
const int   MEA_IP2 = 12;
const int   MEA_FIFR = 13;
const int   MEA_SIFR = 14;
const int   MEA_FIR = 15;
const int   MEA_SIR = 16;
const int   MEA_SS = 17;
const int   MEA_LM = 18;
const int   MEA_NF = 19;
const int   MEA_PN = 20;
//const int   MEA_IMAGE =



const int   SYSRESP = 101;      // 打频响  



const int MARK_COUNT = 6;
const int REFLINE_COUNT = 1;

const int DATA_LEN = 50000;//10000;
const int DATA_LEN_MINI = 50000;
const int LIMIT_LEN = 1000; // 合格线点数
const int LIMIT_COUNT = 8;		// 合格线条数
const double UNPOSSIBLE_AMP_DOWN = -20000.0;
const double UNPOSSIBLE_AMP_UP = 20000.0;

const INT64 N64_Hz = 1L;
const INT64 N64_KHz = 1000L;
const INT64 N64_MHz = 1000L*1000L;
const INT64 N64_GHz = 1000L*1000L*1000L;

const INT64 N64_DAY = 24*60*60*1000L;
const INT64 N64_HOUR = 60*60*1000L;
const INT64 N64_MINUTE = 60*1000L;
const INT64 N64_SEC = 1000L;
const INT64 N64_MSEC = 1L;

const __int64 GHZ_10        = 10000000000LL;
const __int64 GHZ_8         = 8000000000LL;
const __int64 GHZ_6         = 6000000000LL;
const __int64 MHZ_59999     = 5999900000LL;
const __int64 MHZ_5500      = 5500000000LL;
const __int64 MHZ_4500      = 4500000000LL;
const __int64 GHZ_3         = 3000000000LL;
const __int64 GHZ_2         = 2000000000LL;
const __int64 GHZ_1         = 1000000000;
const __int64 MHZ_990       = 990000000;
const __int64 MHZ_950       = 950000000;
const __int64 MHZ_900       = 900000000;
const __int64 MHZ_800       = 800000000;
const __int64 MHZ_685       = 685000000;
const __int64 MHZ_555       = 555000000;
const __int64 MHZ_550       = 550000000;
const __int64 MHZ_500       = 500000000;
const __int64 MHZ_450       = 450000000;
const __int64 MHZ_415       = 415000000;
const __int64 MHZ_300       = 300000000;
const __int64 MHZ_265       = 265000000;
const __int64 MHZ_200       = 200000000;
const __int64 MHZ_175       = 175000000;
const __int64 MHZ_150       = 150000000;
const __int64 MHZ_100       = 100000000;
const __int64 MHZ_110       = 110000000;
const __int64 MHZ_101       = 101000000;
const __int64 MHZ_99        = 99000000;
const __int64 MHZ_72        = 72000000;
const __int64 MHZ_60        = 60000000;
const __int64 MHZ_50        = 50000000;
const __int64 MHZ_40        = 40000000;
const __int64 MHZ_32        = 32000000;
const __int64 MHZ_30        = 30000000;
const __int64 MHZ_35        = 36000000;
const __int64 MHZ_25        = 25000000;
const __int64 MHZ_24        = 24000000;
const __int64 MHZ_21        = 21000000;
const __int64 MHZ_20        = 20000000;
const __int64 MHZ_16        = 16000000;
const __int64 MHZ_15        = 15000000;
const __int64 MHZ_11        = 11000000;
const __int64 MHZ_10        = 10000000;
const __int64 MHZ_8         = 8000000;
const __int64 MHZ_7_61      = 7610000;
const __int64 MHZ_7_56      = 7560000;
const __int64 MHZ_7_512     = 7512000;
const __int64 MHZ_7_5       = 7500000;
const __int64 MHZ_7         = 7000000;
const __int64 MHZ_6         = 6000000;
const __int64 MHZ_5_6       = 5600000;
const __int64 MHZ_5         = 5000000;
const __int64 MHZ_4_8       = 4800000;
const __int64 MHZ_4_515     = 4515000;
const __int64 MHZ_4_5       = 4500000;
const __int64 MHZ_4         = 4000000;
const __int64 MHZ_3_84      = 3840000;
const __int64 MHZ_3_75      = 3750000;
const __int64 MHZ_3_2       = 3200000;
const __int64 MHZ_3_125     = 3125000;
const __int64 MHZ_3         = 3000000;
const __int64 MHZ_2         = 2000000;
const __int64 MHZ_1_995     = 1995000;
const __int64 MHZ_1_6       = 1600000;
const __int64 MHZ_1_28      = 1280000;
const __int64 MHZ_1_25      = 1250000;
const __int64 MHZ_1_23      = 1230000;
const __int64 MHZ_1         = 1000000;
const __int64 KHZ_900       = 900000;
const __int64 KHZ_800       = 800000;
const __int64 KHZ_765       = 765000;
const __int64 KHZ_750       = 750000;
const __int64 KHZ_700       = 700000;
const __int64 KHZ_600       = 600000;
const __int64 KHZ_500       = 500000;
const __int64 KHZ_400       = 400000;
const __int64 KHZ_300       = 300000;
const __int64 KHZ_250       = 250000;
const __int64 KHZ_240       = 240000;
const __int64 KHZ_200       = 200000;
const __int64 KHZ_150       = 150000;
const __int64 KHZ_120       = 120000;
const __int64 KHZ_100       = 100000;
const __int64 KHZ_80        = 80000;
const __int64 KHZ_60        = 60000;
const __int64 KHZ_50        = 50000;
const __int64 KHZ_40        = 40000;
const __int64 KHZ_30        = 30000;
const __int64 KHZ_25        = 25000;
const __int64 KHZ_24        = 24000;
const __int64 KHZ_20        = 20000;
const __int64 KHZ_18        = 18000;
const __int64 KHZ_15        = 15000;
const __int64 KHZ_12_5      = 12500;
const __int64 KHZ_12        = 12000;
const __int64 KHZ_10        = 10000;
const __int64 KHZ_9         = 9000;
const __int64 KHZ_8         = 8000;
const __int64 KHZ_6_25      = 6250;
const __int64 KHZ_6         = 6000;
const __int64 KHZ_5         = 5000;
const __int64 KHZ_4         = 4000;
const __int64 KHZ_3_125     = 3125;
const __int64 KHZ_3         = 3000;
const __int64 KHZ_2_4       = 2400;
const __int64 KHZ_2         = 2000;
const __int64 KHZ_1_5       = 1500;
const __int64 KHZ_1         = 1000;
const __int64 HZ_6250       = 6250;
const __int64 HZ_2500       = 2500;
const __int64 HZ_1250       = 1250;
const __int64 HZ_625        = 625;
const __int64 HZ_600        = 500;
const __int64 HZ_500        = 500;
const __int64 HZ_300        = 300;
const __int64 HZ_250        = 250;
const __int64 HZ_200        = 200;
const __int64 HZ_150        = 150;
const __int64 HZ_125        = 125;
const __int64 HZ_100        = 100;
const __int64 HZ_63         = 63;
const __int64 HZ_50         = 50;
const __int64 HZ_30         = 30;
const __int64 HZ_25         = 25;
const __int64 HZ_20         = 20;
const __int64 HZ_13         = 13;
const __int64 HZ_10         = 10;
const __int64 HZ_5          = 5;
const __int64 HZ_3          = 3;
const __int64 HZ_2          = 2;
const __int64 HZ_1          = 1;
const __int64 HZ_0          = 0;
// 颜色定义

#define UD_SpringGreen			RGB(0,205,102)
#define UD_RED					RGB(255,0,0)
#define UD_GREEN				RGB(0,255,0) 
#define UD_BLUE					RGB(0,0,225)
#define UD_YELLOW				RGB(255,255,0)
#define UD_ORANGE				RGB(255,153,51)
#define UD_HOT_PINK				RGB(255,51,153)
#define UD_PURPLE				RGB(153,0,204)
#define UD_CYAN					RGB(0,255,255)
#define UD_BLACK				RGB(0,0,0)
#define UD_WHITE				RGB(255,255,255)
#define UD_LAVENDER				RGB(199,177,255)
#define UD_PEACH				RGB(255,226,177)
#define UD_SKY_BLUE				RGB(142,255,255)
#define UD_FOREST_GREEN			RGB(0,192,0)
#define UD_BROWN				RGB(80,50,0)
#define UD_TURQUOISE			RGB(0,192,192)
#define UD_ROYAL_BLUE			RGB(0,0,192)
#define UD_GREY					RGB(192,192,192)
#define UD_DARK_GREY			RGB(128,128,128)
#define UD_TAN					RGB(255,198,107)
#define UD_DARK_BLUE			RGB(0,0,128)
#define UD_MAROON				RGB(128,0,0)
#define UD_DUSK					RGB(255,143,107)
#define UD_LIGHT_GREY			RGB(225,225,225)	//only for 3D graph lines	
#define UD_EQUALIZER			RGB(220, 220, 220)
#define UD_DRAKISH				RGB(50, 50, 50)		//2009-8-31 liuhuijun
#define UD_BOTTLE_GREEN			RGB(45, 170, 90)	//RGB(30, 95, 40)	//RGB(45, 185, 95)
#define UD_WINE_RED				RGB(80, 0, 0)
#define UD_LARK_GREY			RGB(235,235,225)

struct MARKER_DATA {	// 频标数据
	BOOL IsEnable;
	UINT nPos;
	INT64 nFreq;
	double dValue;
	TCHAR szAmpUnit[5];
	TCHAR szFreqUnit[5];
};

struct SPECT_MARKER_DATA {	// 频标数据
	BOOL IsEnable;
	UINT nPos;
	INT64 nFreq;
	double dValue;
	TCHAR szAmpUnit[5];
	TCHAR szFreqUnit[5];
	SYSTEMTIME tm;
};

struct REFLINE_DATA {
	int		nRefID;						// 参考线ID
	bool	IsEnable;					// 改参考线是否打开
	double	dRefLine;					// 参考线位置
	int     nUnit;						// 参考线单位
	TCHAR	szText[100];				// 参考线上文字
	int		nTextPos;					// 参考线上文字位置
	COLORREF crLineColor;				// 线颜色
};

struct LIMIT_LINE {
	INT64 nStart;
	INT64 nStop;
	BOOL IsEnable;	// 该合格线是否使能
	int nCount;
	int nOffset;	// 偏移量，用于波形式合格线
	double dLimit[LIMIT_LEN];
};

struct stSAInfo {
	int nGroupID;		// 组ID
	int nInstrID;       // 仪器ID
	TCHAR strName[30];
	BOOL IsConnectAble;
	TCHAR strIPAddr[20];

	MARKER_DATA MarkerData[MARK_COUNT];				// 频标数据
	REFLINE_DATA RefLineData[REFLINE_COUNT];
};

struct stColorConf {
	COLORREF crBK;
	COLORREF crGrid;
	COLORREF crWave;
	COLORREF crMrk;
	COLORREF crMrkA;
	COLORREF crStatus;
	COLORREF crRefA;
	//COLORREF crRefB;
	COLORREF crTitle;
};

struct stListColorConf {
	TCHAR strName[100];
	stColorConf ColorConf;
};

enum CONNECT_MODE {
	FROM_SHARE_MEM = 0,
	FROM_SOCKET
};

enum UNIT_FLAG 
{
	DBM_FLAG = 0,
	DBMV_FLAG,
	DBUV_FLAG,
	V_FLAG,
	MV_FLAG,
	UV_FLAG,
	NV_FLAG
};

struct st_sharemem_info {
	HANDLE hMap;		// 共享内存句柄
	void* pMemData;		// 共享内存区

	HANDLE hMapStatus;	// 状态共享区句柄
	void* pMemDataStatus;  // 状态共享内存区

	HANDLE hMapLimits;	// 合格线共享区句柄
	void* pMemDataLimits; // 合格线共享区

	CString strIP;
	CString strPort;
};

struct sa_struct      //200字节
{
	char ver;				//版本，默认2
	INT64 cent;				//中心频率
	INT64 span;				//扫宽
	double ref_data;		//参考电平
	int ref_unit;			//参考电平单位
	bool log_on;			//对数线性
	int att;				//衰减器
	bool att_auto;			//衰减器自动
	bool ampli_on;			//放大器
	bool pre_sel;			//预选器(8853)
	int rbw;				//rbw
	bool rbw_auto;			//rbw自动
	int vbw;				//vbw
	bool vbw_auto;			//vbw自动
	INT64 sweep;			//扫描时间
	bool sweep_auto;		//扫描时间自动
	char fast_sweep;		//快速扫描开关
	int dete;				//检波方式
	int trig;				//触发方式
	bool bUncal; //true uncal, false正常

	char reserve[134];		//保留，全0
};

struct sa_my_struct 
{
	sa_struct sa;
	double div;

	bool bDispLineON;     //参考线开关
	double dDispLineLev;  //参考线幅度dbm 
	int nMarkType[MARK_COUNT]; //频标类型: 关闭0 /普通1
	__int64 MarkFreqFix[MARK_COUNT]; //频标频率/时间hz/ns
	__int64 MarkFreqMove[MARK_COUNT]; //频标频率/时间hz/ns
};

struct sa_mrk_refline{	
	float fMarkLevFix[MARK_COUNT];  //频标幅度dbm(log) mv (lin)
	float fMarkLevMove[MARK_COUNT];  //频标幅度dbm(log) mv (lin)
};

struct sa_frame {
	UINT nMode;			// 模式
	SYSTEMTIME tms;		// 时间戳
	sa_my_struct status;
	UINT nDataLen;
	BYTE byData[DATA_LEN];

	sa_mrk_refline mrkref;
};

struct sa_frame_mini {
	UINT nMode;			// 模式
	SYSTEMTIME tms;		// 时间戳
	sa_my_struct status;
	UINT nDataLen;
	BYTE byData[DATA_LEN_MINI];

	sa_mrk_refline mrkref;
};

struct chpow_struct {
	INT64 nCHPBw;	// 通道功率带宽
	double dCHP;	// 通道功率
	double dDensity;// 功率密度

};

// 通道功率结构
struct chpow_frame {
	UINT nMode;			// 模式
	SYSTEMTIME tms;		// 时间戳
	sa_my_struct status;// 频谱信息
	UINT nDataLen;      // 数据长度
	BYTE byData[DATA_LEN_MINI]; // 数据区

	sa_mrk_refline mrkref;
	chpow_struct chpData; // 通道功率数据	
};

struct obw_struct {
	double dPercent;// 占用百分比
	double dCHP;	// 通道功率
	INT64  nOBWBw;	// 通道带宽
	INT64  nOBWidth;// 占用带宽
	INT64  nOffset; // 中心频谱
};

// 占用带宽结构
struct obw_frame {
	UINT nMode;			// 模式
	SYSTEMTIME tms;		// 时间戳
	sa_my_struct status;// 频谱信息
	UINT nDataLen;      // 数据长度
	BYTE byData[DATA_LEN_MINI]; // 数据区

	sa_mrk_refline mrkref;
	obw_struct obwData;
};

struct qam_struct      //200字节
{
	char ver;				//版本，默认3
	INT64 cent;				//中心频率
	int att;				//衰减器
	bool att_auto;			//衰减器自动
	bool ampli_on;			//放大器
	bool pre_sel;			//预选器(8853)
	int symb;				//符号率(设置的)
	bool symb_auto;			//符号率自动
	int pol;				//极性
	double mer_th;			//mer门限
	bool mer_th_auto;		//mer门限自动
	double pre_th;			//ber_pre门限
	bool pre_th_auto;		//ber_pre门限自动
	double post_th;			//ber_post门限
	bool post_th_auto;		//ber_post门限自动
	int mod;				//调制类型
	int std;				//标准
	double pre;				//ber_pre
	double post;			//ber_post
	float mer;				//mer
	float enm;        
	float evm;
	float pj;
	float qe;
	float ai;
	float snr;
	float cs;
	float ci;
	int real_symb;			//实际符号率
	INT64 freq_offset;		//频率偏移
	bool symb_lock;			//符号锁定
	bool fec_lock;
	bool stream_lock;
	double chan_pow;		//通道功率
	bool ampli_auto;		//放大器自动  true自动  false手动
	char reserve[64];		//保留，全0
};

struct qam_my_struct 
{
	qam_struct qam;
	int ref_unit;
};

struct qam_frame {
	UINT nMode;			// 模式
	SYSTEMTIME tms;		// 时间戳
	qam_struct status;
	UINT nDataLen;
	BYTE byData[DATA_LEN];
};

CONST int c_nLIMITE_NUM = 6;
CONST int c_nLIMITE_MAX = 100;
CONST int c_nLIMITE_SAVE_NUM = 30;

typedef enum LIM_STYLE
{
	LIM_NONE = -1,
	LIM_UP1 = 0,
	LIM_UP2,
	LIM_UP3,
	LIM_DOWN1,
	LIM_DOWN2,
	LIM_DOWN3
};

typedef struct _tagLIMITE_DATA
{
	INT64 nFreqVal;                  //频率
	double dAmpCurVal;              //幅度
	BOOL bIsChecked;                //是否在checkbox中选择,解析图像没用
}LIMITE_DATA, *PLIMITE_DATA;

//一组合格线数据 6*100,一共可以设置30组
typedef struct _tagSAVE_REC_LIMIT
{
	int nLimitPos[c_nLIMITE_NUM];                                                  //合格线拐点个数
	INT64 nFreqVal[c_nLIMITE_NUM][c_nLIMITE_MAX];                  //频率
	double dAmpCurVal[c_nLIMITE_NUM][c_nLIMITE_MAX];               //幅度
}SAVE_REC_LIMIT, *PSAVE_REC_LIMIT;

typedef struct _tagSAVE_REC_DATA
{
	sa_struct sa;                   //SA信息
	SYSTEMTIME saveTime;            //保存时间
	int nWavePoints;                //波形点数
	double dWaveData[1000];         //波形数据，E8000:421点，8831:501点，剩下保留
	int nLimitIdx;                  //合格线索引
}SAVE_REC_DATA, *PSAVE_REC_DATA;







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
struct FILE_HEAD //文件头
{
	char cVer;            //文件版本号
	int nFileLen;         //整个文件长度, 等于sizeof(要存的结构体)
	int nSaveTime;        //最后保存文件时间, 自1970年的秒数
	UCHAR ucCRC;  //后面所有字节的和 & 0xff
};


//struct STRUCT_RESP_LEVEL_DATA
//{
//	__int64 startfreq;//频率
//	__int64 stopfreq;//带宽
//	__int64 centfreq;//当前点频率
//	int fieldcount;
//	int atttype;
//	int att;
//	short ncout;//当前点位置
//	short level;
//};
struct STRUCT_RESP_LEVEL_DATA
{
	int nRespType;//0:射频频响,1:中频衰减器,2:中频带内频响
	int DotNumber;//该场总点数
	__int64 startfreq;//频率
	__int64 stopfreq;//带宽
	__int64 centfreq;//当前点频率
	int fieldcount;
	int atttype;
	int att;
	short ncout;//当前点位置
	short level;
};
struct STRUCT_HEAD_DATA
{
	UINT version;//版本号，当前为0//没有
	UINT dgnum;// DG_GENERIC数量//有多少包数据
};

struct STRUCT_GENERIC_DATA//每包数据结构
{
	/*UINT tag;//类别,具体值含义参看下表
	UINT version;//类别包版本号,设备更新因此数据内信息可能发生变化,当前版本号参看类别表
	char chnum;//通道数量,1单路,区域为多路
	char chid;//通道号
	USHORT state;//状态,参看状态附录
	UINT length;//data长度*/
	UINT32 tag;
	UINT32 version;
	UINT32 time_s;
	UINT32 time_ns;
	UINT32 length;
};
struct STRUCT_HEAD_MESS
{
	UCHAR cHead1;
	UCHAR cHead2;
	UCHAR cHead3;
	short nLen;//读写类型字节后报文的长度
	UCHAR cRWType;//读写类型
};
//struct STRUCT_DT_FRAME
//{
//	int nCalledNum;//被叫号
//	int nCallingNum;//主叫号
//	int nColourCode;// 色码
//	int nLen;
//	UCHAR sMSGContent[540];//短信内容512个字
//}DT_FRAME;
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
struct STRUCT_DFIND_IQ
{
	__int64 freq;//频率
	__int64 bw;//带宽
	__int64 samplerate;//采样率
	int att;
	short antnum;//天线序号
	UCHAR channum;// 通道数
	char datatype;//-1代表所有通道一起发送,其他>=0代表通道号
	short contnum;//天线控制码总数
	short contoffset;//本组数据天线控制码编号,
	int dotnum;
};

struct STRUCT_IQ_HEAD
{
	__int64 freq;
	__int64 bw;
	__int64 samplerate;
	int att;
	int len;
};





#pragma pack ( pop )

struct WaveStatus
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
const UINT DATA_TYPE_DFIQ = 0x00000200;
const int DATA_TYPE_SPECTRUM = 4;//	频谱数据
const int DATA_TYPE_DFIND = 8;//单频率测向数据
const int DATA_TYPE_DFPAN = 16;//宽带测向数据（FFT测向）
const int DATA_TYPE_AUDIO = 32;//	音频数据
const int DATA_TYPE_ITU = 64;//ITU测量数据
const int DATA_TYPE_SCAN = 128;//频谱扫描数据
const int DATA_TYPE_FSCAN = 130;//频谱扫描数据
const int DATA_TYPE_MSCAN = 132;//频谱扫描数据
const int DATA_TYPE_TDOA = 256;//测向扫描数据
const int DATA_TYPE_MESS =1024;
const __int64 DATA_TYPE_RESP = 1000000;//测向扫描数据
enum MARKER_DEF
{

	MARK_PEAK_SEARCH = 0,
	MARK_NORMAL = 1
};















#endif
