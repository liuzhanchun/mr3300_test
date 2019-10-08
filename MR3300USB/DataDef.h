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



const int   SYSRESP = 101;      // ��Ƶ��  



const int MARK_COUNT = 6;
const int REFLINE_COUNT = 1;

const int DATA_LEN = 50000;//10000;
const int DATA_LEN_MINI = 50000;
const int LIMIT_LEN = 1000; // �ϸ��ߵ���
const int LIMIT_COUNT = 8;		// �ϸ�������
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
// ��ɫ����

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

struct MARKER_DATA {	// Ƶ������
	BOOL IsEnable;
	UINT nPos;
	INT64 nFreq;
	double dValue;
	TCHAR szAmpUnit[5];
	TCHAR szFreqUnit[5];
};

struct SPECT_MARKER_DATA {	// Ƶ������
	BOOL IsEnable;
	UINT nPos;
	INT64 nFreq;
	double dValue;
	TCHAR szAmpUnit[5];
	TCHAR szFreqUnit[5];
	SYSTEMTIME tm;
};

struct REFLINE_DATA {
	int		nRefID;						// �ο���ID
	bool	IsEnable;					// �Ĳο����Ƿ��
	double	dRefLine;					// �ο���λ��
	int     nUnit;						// �ο��ߵ�λ
	TCHAR	szText[100];				// �ο���������
	int		nTextPos;					// �ο���������λ��
	COLORREF crLineColor;				// ����ɫ
};

struct LIMIT_LINE {
	INT64 nStart;
	INT64 nStop;
	BOOL IsEnable;	// �úϸ����Ƿ�ʹ��
	int nCount;
	int nOffset;	// ƫ���������ڲ���ʽ�ϸ���
	double dLimit[LIMIT_LEN];
};

struct stSAInfo {
	int nGroupID;		// ��ID
	int nInstrID;       // ����ID
	TCHAR strName[30];
	BOOL IsConnectAble;
	TCHAR strIPAddr[20];

	MARKER_DATA MarkerData[MARK_COUNT];				// Ƶ������
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
	HANDLE hMap;		// �����ڴ���
	void* pMemData;		// �����ڴ���

	HANDLE hMapStatus;	// ״̬���������
	void* pMemDataStatus;  // ״̬�����ڴ���

	HANDLE hMapLimits;	// �ϸ��߹��������
	void* pMemDataLimits; // �ϸ��߹�����

	CString strIP;
	CString strPort;
};

struct sa_struct      //200�ֽ�
{
	char ver;				//�汾��Ĭ��2
	INT64 cent;				//����Ƶ��
	INT64 span;				//ɨ��
	double ref_data;		//�ο���ƽ
	int ref_unit;			//�ο���ƽ��λ
	bool log_on;			//��������
	int att;				//˥����
	bool att_auto;			//˥�����Զ�
	bool ampli_on;			//�Ŵ���
	bool pre_sel;			//Ԥѡ��(8853)
	int rbw;				//rbw
	bool rbw_auto;			//rbw�Զ�
	int vbw;				//vbw
	bool vbw_auto;			//vbw�Զ�
	INT64 sweep;			//ɨ��ʱ��
	bool sweep_auto;		//ɨ��ʱ���Զ�
	char fast_sweep;		//����ɨ�迪��
	int dete;				//�첨��ʽ
	int trig;				//������ʽ
	bool bUncal; //true uncal, false����

	char reserve[134];		//������ȫ0
};

struct sa_my_struct 
{
	sa_struct sa;
	double div;

	bool bDispLineON;     //�ο��߿���
	double dDispLineLev;  //�ο��߷���dbm 
	int nMarkType[MARK_COUNT]; //Ƶ������: �ر�0 /��ͨ1
	__int64 MarkFreqFix[MARK_COUNT]; //Ƶ��Ƶ��/ʱ��hz/ns
	__int64 MarkFreqMove[MARK_COUNT]; //Ƶ��Ƶ��/ʱ��hz/ns
};

struct sa_mrk_refline{	
	float fMarkLevFix[MARK_COUNT];  //Ƶ�����dbm(log) mv (lin)
	float fMarkLevMove[MARK_COUNT];  //Ƶ�����dbm(log) mv (lin)
};

struct sa_frame {
	UINT nMode;			// ģʽ
	SYSTEMTIME tms;		// ʱ���
	sa_my_struct status;
	UINT nDataLen;
	BYTE byData[DATA_LEN];

	sa_mrk_refline mrkref;
};

struct sa_frame_mini {
	UINT nMode;			// ģʽ
	SYSTEMTIME tms;		// ʱ���
	sa_my_struct status;
	UINT nDataLen;
	BYTE byData[DATA_LEN_MINI];

	sa_mrk_refline mrkref;
};

struct chpow_struct {
	INT64 nCHPBw;	// ͨ�����ʴ���
	double dCHP;	// ͨ������
	double dDensity;// �����ܶ�

};

// ͨ�����ʽṹ
struct chpow_frame {
	UINT nMode;			// ģʽ
	SYSTEMTIME tms;		// ʱ���
	sa_my_struct status;// Ƶ����Ϣ
	UINT nDataLen;      // ���ݳ���
	BYTE byData[DATA_LEN_MINI]; // ������

	sa_mrk_refline mrkref;
	chpow_struct chpData; // ͨ����������	
};

struct obw_struct {
	double dPercent;// ռ�ðٷֱ�
	double dCHP;	// ͨ������
	INT64  nOBWBw;	// ͨ������
	INT64  nOBWidth;// ռ�ô���
	INT64  nOffset; // ����Ƶ��
};

// ռ�ô���ṹ
struct obw_frame {
	UINT nMode;			// ģʽ
	SYSTEMTIME tms;		// ʱ���
	sa_my_struct status;// Ƶ����Ϣ
	UINT nDataLen;      // ���ݳ���
	BYTE byData[DATA_LEN_MINI]; // ������

	sa_mrk_refline mrkref;
	obw_struct obwData;
};

struct qam_struct      //200�ֽ�
{
	char ver;				//�汾��Ĭ��3
	INT64 cent;				//����Ƶ��
	int att;				//˥����
	bool att_auto;			//˥�����Զ�
	bool ampli_on;			//�Ŵ���
	bool pre_sel;			//Ԥѡ��(8853)
	int symb;				//������(���õ�)
	bool symb_auto;			//�������Զ�
	int pol;				//����
	double mer_th;			//mer����
	bool mer_th_auto;		//mer�����Զ�
	double pre_th;			//ber_pre����
	bool pre_th_auto;		//ber_pre�����Զ�
	double post_th;			//ber_post����
	bool post_th_auto;		//ber_post�����Զ�
	int mod;				//��������
	int std;				//��׼
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
	int real_symb;			//ʵ�ʷ�����
	INT64 freq_offset;		//Ƶ��ƫ��
	bool symb_lock;			//��������
	bool fec_lock;
	bool stream_lock;
	double chan_pow;		//ͨ������
	bool ampli_auto;		//�Ŵ����Զ�  true�Զ�  false�ֶ�
	char reserve[64];		//������ȫ0
};

struct qam_my_struct 
{
	qam_struct qam;
	int ref_unit;
};

struct qam_frame {
	UINT nMode;			// ģʽ
	SYSTEMTIME tms;		// ʱ���
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
	INT64 nFreqVal;                  //Ƶ��
	double dAmpCurVal;              //����
	BOOL bIsChecked;                //�Ƿ���checkbox��ѡ��,����ͼ��û��
}LIMITE_DATA, *PLIMITE_DATA;

//һ��ϸ������� 6*100,һ����������30��
typedef struct _tagSAVE_REC_LIMIT
{
	int nLimitPos[c_nLIMITE_NUM];                                                  //�ϸ��߹յ����
	INT64 nFreqVal[c_nLIMITE_NUM][c_nLIMITE_MAX];                  //Ƶ��
	double dAmpCurVal[c_nLIMITE_NUM][c_nLIMITE_MAX];               //����
}SAVE_REC_LIMIT, *PSAVE_REC_LIMIT;

typedef struct _tagSAVE_REC_DATA
{
	sa_struct sa;                   //SA��Ϣ
	SYSTEMTIME saveTime;            //����ʱ��
	int nWavePoints;                //���ε���
	double dWaveData[1000];         //�������ݣ�E8000:421�㣬8831:501�㣬ʣ�±���
	int nLimitIdx;                  //�ϸ�������
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
struct FILE_HEAD //�ļ�ͷ
{
	char cVer;            //�ļ��汾��
	int nFileLen;         //�����ļ�����, ����sizeof(Ҫ��Ľṹ��)
	int nSaveTime;        //��󱣴��ļ�ʱ��, ��1970�������
	UCHAR ucCRC;  //���������ֽڵĺ� & 0xff
};


//struct STRUCT_RESP_LEVEL_DATA
//{
//	__int64 startfreq;//Ƶ��
//	__int64 stopfreq;//����
//	__int64 centfreq;//��ǰ��Ƶ��
//	int fieldcount;
//	int atttype;
//	int att;
//	short ncout;//��ǰ��λ��
//	short level;
//};
struct STRUCT_RESP_LEVEL_DATA
{
	int nRespType;//0:��ƵƵ��,1:��Ƶ˥����,2:��Ƶ����Ƶ��
	int DotNumber;//�ó��ܵ���
	__int64 startfreq;//Ƶ��
	__int64 stopfreq;//����
	__int64 centfreq;//��ǰ��Ƶ��
	int fieldcount;
	int atttype;
	int att;
	short ncout;//��ǰ��λ��
	short level;
};
struct STRUCT_HEAD_DATA
{
	UINT version;//�汾�ţ���ǰΪ0//û��
	UINT dgnum;// DG_GENERIC����//�ж��ٰ�����
};

struct STRUCT_GENERIC_DATA//ÿ�����ݽṹ
{
	/*UINT tag;//���,����ֵ����ο��±�
	UINT version;//�����汾��,�豸���������������Ϣ���ܷ����仯,��ǰ�汾�Ųο�����
	char chnum;//ͨ������,1��·,����Ϊ��·
	char chid;//ͨ����
	USHORT state;//״̬,�ο�״̬��¼
	UINT length;//data����*/
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
	short nLen;//��д�����ֽں��ĵĳ���
	UCHAR cRWType;//��д����
};
//struct STRUCT_DT_FRAME
//{
//	int nCalledNum;//���к�
//	int nCallingNum;//���к�
//	int nColourCode;// ɫ��
//	int nLen;
//	UCHAR sMSGContent[540];//��������512����
//}DT_FRAME;
struct STRUCT_LEVEL_DATA
{
	__int64 freq;//Ƶ��
	__int64 bw;//����
	int att;
	float level;//��ƽ
	float field;//��ǿ
};

struct STRUCT_SPECTRUM_HEAD //dBuV*10
{
	__int64 freq;// Ƶ��
	__int64 span; //����
	int att;
	UINT pt;//���� 421/571
};

struct STRUCT_ITU_DATA
{
	__int64 freq;//Ƶ��
	__int64 betabw;//beta%��������ֵ
	__int64 xdbbw; //xdB��������ֵ
	float am;//������
	float am_pos; //��������
	float am_neg; //��������
	float fm;//��ƵƵƫ
	float fm_pos; //����ƵƵƫ
	float fm_neg; //����ƵƵƫ
	float pm; //����Ƕ�
	float pm_pos; //�������Ƕ�
	float pm_neg; //������С�Ƕ�
	int mod;//����ʶ����,ֵ��-1��ʼ���ζ�ӦError, AM, FM, 2FSK, 4FSK, 2PSK, 4PSK, 2ASK, 4ASK, DSB, CW, VSB, Noise, UnKnown
};

struct STRUCT_SCAN_HEAD
{
	__int64 start;//ɨ����ʼƵ��
	__int64 stop; //ɨ�����Ƶ��
	__int64 step; //ɨ�貽��Ƶ��
	UINT frameid; //ɨ�����,��ʱδʹ��
	UINT total;//һ�������ܼƵ���
	UINT pdloc;//�ð�������һ��ɨ�����ݵĵ�λ�ã�ѹ����Ч0
	UINT pdpt;//�ð����ݰ���������ʵ�ʷ�������
};

struct STRUCT_SCAN_HEAD_FAST
{
	__int64 start;//ɨ����ʼƵ��
	__int64 stop; //ɨ�����Ƶ��
	__int64 step; //ɨ�貽��Ƶ��
	UINT frameid; //ɨ�����,��ʱδʹ��
	UINT pdpt;//�ð����ݰ���������ʵ�ʷ�������
};

struct STRUCT_AUDIO_HEAD
{
	__int64 freq;//Ƶ��
	__int64 bw;//����
	__int64 samplerate;//������
	UINT reserved;
	UINT len;//��Ƶ����
};

//
//struct  STRUCT_DFIND_DATA
//{
//	__int64 freq;
//	__int64 bwDF;
//	int system;//�������ƣ��ò��õ���ֵ��ʾ���������õ�����һ�ֲ�������
//	int reserved;
//	float level;
//	float azimuth;//ʾ��ȣ��Ƕ�ֵ������Ч��Χ��[0, 360)
//	float quality;//������������Ч��Χ��[0, 100]
//	short extra_size;//�������ݵĳ��ȣ�ͨ��Ϊ�㣬��Ϊ���Խ׶�
//
//};
//
//struct  STRUCT_DFPAN_DATA
//{
//	__int64 freq;
//	__int64 bwDF;
//	int system;//�������ƣ��ò��õ���ֵ��ʾ���������õ�����һ�ֲ�������
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
	__int64 freq;//Ƶ��
	__int64 bw;//����
	__int64 samplerate;//������
	int att;
	short antnum;//�������
	UCHAR channum;// ͨ����
	char datatype;//-1��������ͨ��һ����,����>=0����ͨ����
	short contnum;//���߿���������
	short contoffset;//�����������߿�������,
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
	__int64 Step; //ɨ�貽��Ƶ��
	__int64 total; //ɨ�貽��Ƶ��
	double RBW;
	double Ref;
	int Att;
	bool Ampli;
};

// ������ʾ��ʶ
enum WAVE_OUTPUT
{
	WAVE_NORMAL = 0,
	WAVE_MAX = 4,
	WAVE_MIN = 5,
	WAVE_AVG = 2
};
struct Section
{
	// ��Ч��ʶ��
	static const int NA = -20000;

	// ���ݻ�������С
	static const int DATA_BUF = 1000000;

	// ��������Ч���ݳ���
	int nDataLen;

	// �����������,��󱣳֣���С���֣�ƽ����
	WAVE_OUTPUT OutPut;

	// ������ָ��
	double* fData;

	// ƽ����������
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
const int DATA_TYPE_IQ = 1; //IQ����
const int DATA_TYPE_LEVEL = 2;//��ƽ����
const UINT DATA_TYPE_DFIQ = 0x00000200;
const int DATA_TYPE_SPECTRUM = 4;//	Ƶ������
const int DATA_TYPE_DFIND = 8;//��Ƶ�ʲ�������
const int DATA_TYPE_DFPAN = 16;//����������ݣ�FFT����
const int DATA_TYPE_AUDIO = 32;//	��Ƶ����
const int DATA_TYPE_ITU = 64;//ITU��������
const int DATA_TYPE_SCAN = 128;//Ƶ��ɨ������
const int DATA_TYPE_FSCAN = 130;//Ƶ��ɨ������
const int DATA_TYPE_MSCAN = 132;//Ƶ��ɨ������
const int DATA_TYPE_TDOA = 256;//����ɨ������
const int DATA_TYPE_MESS =1024;
const __int64 DATA_TYPE_RESP = 1000000;//����ɨ������
enum MARKER_DEF
{

	MARK_PEAK_SEARCH = 0,
	MARK_NORMAL = 1
};















#endif
