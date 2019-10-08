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

	//9KƵ��
	const __int64 RESP_FREQ_START_9K_LOW = KHZ_9; //��9k��ʼ��
	const __int64 RESP_FREQ_START_9K_HIGH = KHZ_20; //��20k��ʼ��
	const __int64 RESP_FREQ_START_9K_STOP = KHZ_50; //��50K
	const __int64 RESP_STEP_9K_LOW = KHZ_3;  //��Ƶ��ʱ��Ƶ�ʲ���
	const __int64 RESP_STEP_9K_HIGH= KHZ_10;  //��Ƶ��ʱ��Ƶ�ʲ���
	const int RESP_DOT_NUM_9K = 8;//Ƶ��Ϊ9K,12K,15K,18K,20K,30k,40k,50K,��8��	
	const short RESP_LOW_DATA = 247; //6.02 /DB_RANGE * AD_RANGE;
	const double D_VALUE_DMB_MV_50 = -9.03221;
	const double D_VALUE_DMB_MV_75 = -7.448586716489;
	const double SIGNAL_GEN_ATT[]={ 10,30,60,100,200,300,600,1000,2000,3000,5000,5000 };
	//����dbm��mv���� dbm=10lg(1000mV2/50),��ƵƵ������Ϊ��ֵdbm= 10lg((0.707mV��1000/2)2/50) ��ֵ= 10lg(0.707/2)2=-0.903221;

	const __int64 RESP_FREQ_START = MHZ_40;
	const __int64 RESP_FREQ_STOP = GHZ_8; //7995M
	const __int64 RESP_STEP = MHZ_5;  //��Ƶ��ʱ��Ƶ�ʲ���
	const int RESP_FIELD_NUM_NORMAL = 11;
	const int RESP_FIELD_NUM_LOWDISTORT = 7;//0-30
	const int RESP_FIELD_NUM_LOWNOISE = 5;//0-20
	const int RESP_FIELD_NUM = RESP_FIELD_NUM_NORMAL + RESP_FIELD_NUM_LOWDISTORT + RESP_FIELD_NUM_LOWNOISE;   //�����Ƶ�쳡��(������)

	const int RESP_DOT_NUM   = ( RESP_FREQ_STOP - RESP_FREQ_START ) / RESP_STEP + 1;  
	const int FREQ_RESP_NUM = 11;     //Ƶ�ʼ��������ĵ���1 MHz~2991,����299M

	const int RESP_ID_FAST   = RESP_FIELD_NUM ; //���ɨƵ��ĳ���ID
	const int RESP_ID_MAX = RESP_ID_FAST+1;//����Ƶ��+fast

	const int UPTIME_MIN = 600; //��Ƶ��ǰҪ��ϵͳ����ʱ�����ٶ�����

	const int RESP_DOT_NUM_FAST = 800; //��ɨ��Ƶ��ĵ���, ����20M(����)
	const int FREQ_STEP_FAST = KHZ_50;
	const __int64 FAST_CORR_SPAN = MHZ_40;  
} //end namespace declare
const int FILE_VER_RESP = 2;
#pragma pack ( push, 1 )

//struct STRUCT_FAST_RESP //��ɨƵ��
//{
//	FILE_HEAD Head;            //�ļ�ͷ, ����, �汾, ʱ��, ����, У���, ver = 1
//	bool bSuccess;             //У׼�Ƿ�ɹ�, true�ɹ�, falseʧ��
//	short shResp[resp_ns::RESP_DOT_NUM_FAST];  //Ƶ������, +-500, ����+-5db
//};
struct STRUCT_FAST_RESP //��ɨƵ��
{
	FILE_HEAD Head;            //�ļ�ͷ, ����, �汾, ʱ��, ����, У���, ver = 1
	bool bSuccess; 
	UCHAR cReserve[21];
	short nFastRespNum;//У׼�Ƿ�ɹ�, true�ɹ�, falseʧ��
	short shResp[2000];  //Ƶ������, +-500, ����+-5db
};
struct STRUCT_CAL_ONE //����У׼
{     
	short CalDataNum;//��Ƶ˥��������
	short cReserve[9];
	short shSpanData[10][20];  //���ʮ����Ƶ�˲�������,˥�������20��
};

struct STRUCT_CAL //Ƶ��(����/Ƶ��)
{
	FILE_HEAD stHead;
	bool bRespFinish;
	UCHAR SpanNum;
	UCHAR cReserve[100];
	STRUCT_CAL_ONE shCalData[3];
};
//struct STRUCT_RESP //Ƶ��(����/Ƶ��)
//{
//	FILE_HEAD stHead;  //���汾��(FILE_VER_CAL_RESP), ʱ��, ����, У��͵��ļ�ͷ
//	short shRespData[resp_ns::RESP_FIELD_NUM][resp_ns::RESP_DOT_NUM];//����Ƶ������, ADֵ, ad=10�����dsp����adֵ�ټ�10����׼ȷ
//	float fCalOut;                    //10MУ׼Դ������, dBֵ, У׼Դ�����Ӵ��������� ����ֵ	
//	float fTem[resp_ns::RESP_FIELD_NUM];       //ÿ��Ƶ�����ݵ��¶�,���϶�
//	__int64 FreqData[resp_ns::FREQ_RESP_NUM];  //Ƶ�ʼ����������, ��100, �����dsp������ֵ�ټ�100hz����׼ȷ����
//	bool bRespFinish[resp_ns::RESP_FIELD_NUM]; //ÿ��Ƶ�������Ƿ�����, ����
//	char cReserve[100];                //����, ȫ0
//};
struct STRUCT_RESP_ONE //Ƶ��(����/Ƶ��)
{
	int nFieldPn;//�ǵڼ���
	int nRespNum;
	bool bRespFinish;
	char cReserve[20];
	short shRespData[2000];
};
struct STRUCT_RESP //Ƶ��(����/Ƶ��)
{
	FILE_HEAD stHead;  //���汾��(FILE_VER_CAL_RESP), ʱ��, ����, У��͵��ļ�ͷ
	UCHAR cReserve[100];
	STRUCT_RESP_ONE shRespData[30];
};

struct STRUCT_RESP_LOW //Ƶ��(����/Ƶ��)
{
	FILE_HEAD stHead;  //���汾��(FILE_VER_CAL_RESP), ʱ��, ����, У��͵��ļ�ͷ
	float fTem[resp_ns::RESP_FIELD_NUM];       //ÿ��Ƶ�����ݵ��¶�,���϶�
	short shRespData[resp_ns::RESP_FIELD_NUM][resp_ns::RESP_DOT_NUM_9K];//����Ƶ������, ADֵ, ad=10�����dsp����adֵ�ټ�10����׼ȷ
	bool bRespFinish[resp_ns::RESP_FIELD_NUM]; //ÿ��Ƶ�������Ƿ�����, ����
	char cReserve[100];                //����, ȫ0
};

//struct STRUCT_FAST_RESP //��ɨƵ��
//{
//	FILE_HEAD Head;            //�ļ�ͷ, ����, �汾, ʱ��, ����, У���, ver = 1
//	bool bSuccess;             //У׼�Ƿ�ɹ�, true�ɹ�, falseʧ��
//	short shResp[resp_ns::RESP_DOT_NUM_FAST];  //Ƶ������, +-500, ����+-5db
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
	short m_shField[2000]; //������Ϊ2000,һ������2000
	STRUCT_RESP m_MemCorr; //Ƶ�������ļ�, ��Ӳ�̶���, ����һ��, ���ڴ����һ��, ��д��
	STRUCT_CAL m_AmpCalData;
};
extern CResponse *g_pRes;

