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
	UINT version;//�汾�ţ���ǰΪ0//û��
	UINT dgnum;// DG_GENERIC����//�ж��ٰ�����
};

struct STRUCT_GENERIC_DATA//ÿ�����ݽṹ
{
	UINT tag;//���,����ֵ����ο��±�
	UINT version;//�����汾��,�豸���������������Ϣ���ܷ����仯,��ǰ�汾�Ųο�����
	char chnum;//ͨ������,1��·,����Ϊ��·
	char chid;//ͨ����
	USHORT state;//״̬,�ο�״̬��¼
	UINT length;//data����
};

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
#pragma pack ( pop )

struct FreScanStatus
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

enum FREQ_DEF {
	HZ_1 = 1,
	KHZ_1 = 1000,
	KHZ_30 = 30000,
	KHZ_100 = 100000,
	MHZ_1 = 1000000,
	GHZ_1 = 1000000000,
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
const int DATA_TYPE_SPECTRUM = 4;//	Ƶ������
const int DATA_TYPE_DFIND = 8;//��Ƶ�ʲ�������
const int DATA_TYPE_DFPAN = 16;//����������ݣ�FFT����
const int DATA_TYPE_AUDIO = 32;//	��Ƶ����
const int DATA_TYPE_ITU = 64;//ITU��������
const int DATA_TYPE_SCAN = 128;//Ƶ��ɨ������
const int DATA_TYPE_FSCAN = 130;//Ƶ��ɨ������
const int DATA_TYPE_MSCAN = 132;//Ƶ��ɨ������
const int DATA_TYPE_TDOA = 256;//����ɨ������

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

