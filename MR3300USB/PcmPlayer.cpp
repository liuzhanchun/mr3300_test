#include "StdAfx.h"
#include "PcmPlayer.h"

int CPcmPlayer::nCount = 0;

CPcmPlayer::CPcmPlayer(int bufferSize, int bufferCnt)
{
	m_hWaveOut = NULL;
	m_hBufferEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	InitializeCriticalSection(&m_BufferOpCriticalSection);

	//�����ڴ�
	m_headAndDatas = new WaveHeadandData[bufferCnt];
	for (int i = 0; i < bufferCnt; i++)
	{
		memset(&m_headAndDatas[i].header, 0, sizeof(WAVEHDR));
		m_headAndDatas[i].header.dwFlags = WHDR_DONE;
		m_headAndDatas[i].data = new char[bufferSize];
	}

	m_maxBufferSize = bufferSize;
	m_maxBufferCnt = bufferCnt;
}


CPcmPlayer::~CPcmPlayer()
{
	//�ر�Wave
	if (m_hWaveOut != NULL)
	{
		ClearPcmData();
		waveOutClose(m_hWaveOut);
		m_hWaveOut = NULL;
	}

	//�ر�һЩ���
	CloseHandle(m_hBufferEvent);

	//ɾ���ٽ���
	DeleteCriticalSection(&m_BufferOpCriticalSection);

	//�ͷ��ڴ�
	for (int i = 0; i < m_maxBufferCnt; i++)
		delete[] m_headAndDatas[i].data;

	delete[] m_headAndDatas;
}
int CPcmPlayer::Init(int channels, int samplePerSec, int bitsPerSample)
{
	if (m_hWaveOut != NULL) {
		return 0;// �Ѿ������˳�ʼ��
	}

	// ��һ��: ��ȡwaveformat��Ϣ
	m_waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	m_waveFormat.nChannels = channels;
	m_waveFormat.wBitsPerSample = bitsPerSample;
	m_waveFormat.nSamplesPerSec = samplePerSec;
	m_waveFormat.nBlockAlign =
		m_waveFormat.nChannels * m_waveFormat.wBitsPerSample / 8;
	m_waveFormat.nAvgBytesPerSec =
		m_waveFormat.nSamplesPerSec * m_waveFormat.nBlockAlign;
	m_waveFormat.cbSize = sizeof(m_waveFormat);

	MMRESULT ret = waveOutOpen(NULL, WAVE_MAPPER, &m_waveFormat,
		NULL, NULL, WAVE_FORMAT_QUERY);
	if (MMSYSERR_NOERROR != ret) {
		return -1;
	}

	// �ڶ���: ��ȡWAVEOUT���
	ret = waveOutOpen(&m_hWaveOut, WAVE_MAPPER, &m_waveFormat,
		(DWORD_PTR)WaveOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION);

	if (MMSYSERR_NOERROR != ret) {
		return -1;
	}

	return 0;
}

void CALLBACK CPcmPlayer::WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	CPcmPlayer *render = (CPcmPlayer *)dwInstance;
	//WAVEHDR *header = (WAVEHDR *)dwParam1;
	int i = 0;
	switch (uMsg)
	{
	case WOM_DONE:
		EnterCriticalSection(&render->m_BufferOpCriticalSection);
		SetEvent(render->m_hBufferEvent);



		LeaveCriticalSection(&render->m_BufferOpCriticalSection);
		break;
	case WOM_CLOSE:
		i = 1;
		break;
	case WOM_OPEN:
		i = 2;
		break;
	}
}

int CPcmPlayer::ClearPcmData()
{
	if (m_hWaveOut != NULL)
	{
		EnterCriticalSection(&m_BufferOpCriticalSection);
		for (int i = 0; i < m_maxBufferCnt; i++)
		{
			if (m_headAndDatas[i].header.dwFlags & WHDR_PREPARED) //�����ݱ�Prepered
				waveOutUnprepareHeader(m_hWaveOut, &m_headAndDatas[i].header, sizeof(WAVEHDR));
		}

		waveOutReset(m_hWaveOut);
		LeaveCriticalSection(&m_BufferOpCriticalSection);
	}
	return 0;
}

int CPcmPlayer::WriteToWave(const void *data, int len)
{
	MMRESULT mmres;
	int i;
	EnterCriticalSection(&m_BufferOpCriticalSection);
	for (i = 0; i < m_maxBufferCnt; i++)
		if (m_headAndDatas[i].header.dwFlags & WHDR_DONE)
		{
			//�鿴�Ƿ���Ҫ�ͷ�֮ǰ�Ѿ�Prepared��Դ
			if (m_headAndDatas[i].header.dwFlags & WHDR_PREPARED) //�����ݱ�Prepered
				waveOutUnprepareHeader(m_hWaveOut, &m_headAndDatas[i].header, sizeof(WAVEHDR));

			//д���µ����ݵ���Ƶ������        
			memcpy(m_headAndDatas[i].data, data, len);
			m_headAndDatas[i].header.lpData = m_headAndDatas[i].data;
			m_headAndDatas[i].header.dwBufferLength = len;
			m_headAndDatas[i].header.dwFlags = 0;

			mmres = waveOutPrepareHeader(m_hWaveOut, &m_headAndDatas[i].header, sizeof(WAVEHDR));
			if (MMSYSERR_NOERROR == mmres)
				mmres = waveOutWrite(m_hWaveOut, &m_headAndDatas[i].header, sizeof(WAVEHDR));


			break;
		}
	LeaveCriticalSection(&m_BufferOpCriticalSection);

	if (i == m_maxBufferCnt)
		return -2;

	return (mmres == MMSYSERR_NOERROR) ? 0 : -1;
}

//���PCM��Ƶ���ݣ��ȴ�����
int CPcmPlayer::PcmToWave(const void *data, int len, int timeout)
{
	int res;

	if (len > m_maxBufferSize)
		return -1;

	res = WriteToWave(data, len);

	//��������������Ҫ�ȴ�
	if (res == -2)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hBufferEvent, timeout))
			res = WriteToWave(data, len);
	}

	return res;
}

int CPcmPlayer::ToSpeaker(const void *data, int len, int timeout)
{
	int res;
	int n, l, ptr;

	//�Դ��������ֶδ���
	n = len / m_maxBufferSize;
	l = len % m_maxBufferSize;
	ptr = 0;

	for (int i = 0; i < n; i++)
	{
		res = PcmToWave(((char *)data) + ptr, m_maxBufferSize, timeout);
		ptr += m_maxBufferSize;
		if (res != 0)
			return -1;
	}

	return PcmToWave(((char *)data) + ptr, l, timeout);
}