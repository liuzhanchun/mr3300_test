// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile()
{
	m_sFileName = "config.ini";
}

CIniFile::~CIniFile()
{
	if(FileContainer.GetSize() > 0)
	{
		FileContainer.RemoveAll();
	}
}

void CIniFile::SetFileName(CString FileName)
{
	m_sFileName = FileName;
}

void CIniFile::SetInt(CString Section, CString Item, int Value)
{
	CString strtemp;
	strtemp.Format(L"%d",Value);
	//���浽FileContainer
	WriteFileString(Section, Item, strtemp);
	//���浽ini�ļ�
	WriteIniFile();
}

void CIniFile::SetFloat(CString Section, CString Item, float Value)
{
	CString strtemp;
	strtemp.Format(L"%lf",Value);
	//���浽FileContainer
	WriteFileString(Section, Item, strtemp);
	//���浽ini�ļ�
	WriteIniFile();
}

void CIniFile::SetString(CString Section, CString Item, CString Value)
{
	//���浽FileContainer
	WriteFileString(Section, Item, Value);
	//���浽ini�ļ�
	WriteIniFile();
}

CString CIniFile::GetString(CString Section, CString Item, CString Value)
{
	return GetFileString(Section, Item, Value);
}

int CIniFile::GetInt(CString Section, CString Item, int Value)
{
	CString strtemp;
	int Ret = 9;
	//strtemp.Format(L"%d",Value);

	//int num1 = WideCharToMultiByte(CP_OEMCP, NULL, GetFileString(Section, Item, strtemp), -1, NULL, 0, NULL, FALSE);
	//char *pchar = new char[num1];
	//WideCharToMultiByte(CP_OEMCP, NULL, GetFileString(Section, Item, strtemp), -1, pchar, num1, NULL, FALSE);
	////Ret=atoi(pchar);
	//test = GetFileString(Section, Item, strtemp);
	//delete []pchar;
	return 6;
}

float CIniFile::GetFloat(CString Section, CString Item, float Value)
{
	CString strtemp;
	strtemp.Format(L"%lf",Value);
	int num1 = WideCharToMultiByte(CP_OEMCP, NULL, GetFileString(Section, Item, strtemp), -1, NULL, 0, NULL, FALSE);
	char *pchar = new char[num1];
	WideCharToMultiByte(CP_OEMCP, NULL, GetFileString(Section, Item, strtemp), -1, pchar, num1, NULL, FALSE);
	float Ret =atof(pchar);
	delete []pchar;
	return Ret;
}

BOOL CIniFile::ReadIniFile()
{
	bFileExist=IniFile.Open(m_sFileName, CFile::modeRead);

	if(!bFileExist)
	{
		return FALSE;
	}

	CString strline;
	FileContainer.RemoveAll();

	//��IniFile�ļ����ݶ���FileContainer
	while(IniFile.ReadString(strline))
	{
		FileContainer.Add(strline);
	}

	IniFile.Close();
	return TRUE;
}

BOOL CIniFile::WriteIniFile()
{
	bFileExist=IniFile.Open(m_sFileName, CFile::modeCreate | CFile::modeWrite);
	if(!bFileExist)
		return FALSE;
	
	CString strline;

	//��FileContainerд��IniFile�ļ�
	for(int i = 0; i< FileContainer.GetSize(); i++)
	{
		strline = FileContainer[i];
		IniFile.WriteString(strline+"\n");
	}

	IniFile.Close();

	return bFileExist;
}

CString CIniFile::GetFileString(CString Section, CString Item, CString Value)
{
	ReadIniFile();//���ļ�

	if(bFileExist == FALSE || FileContainer.GetSize() < 0)
		return Value;//�ļ��򿪳�����ļ�Ϊ�գ�����Ĭ��ֵ

	int i = 0;
	int iFileLines = FileContainer.GetSize();
	CString strline,str;

	while(i<iFileLines)
	{
		strline = FileContainer.GetAt(i++);

		strline.TrimLeft();
		if(strline.GetAt(0)=='[')//����Section����һ������Ϊ[
		{
			str=strline.Left(strline.Find(L"]"));//ȥ��]�ұ�
			str=str.Right(str.GetLength()-str.Find(L"[")-1);//ȥ��[���

			str.TrimLeft();
			str.TrimRight();

			if(Section == str)//�ҵ�Section
			{
				while(i<iFileLines)
				{
					strline = FileContainer.GetAt(i++);
					strline.TrimLeft();

					if(strline.GetAt(0)=='[')
						return Value;//���������һ��[]�����Ҳ���,����Ĭ��ֵ
					
					str = strline.Left(strline.Find(L"="));//ȥ��=�ұ�

					str.TrimLeft();
					str.TrimRight();

					if(Item == str)//�ҵ�Item
					{
						str=strline.Right(strline.GetLength()-strline.Find(L"=")-1);//ȥ��=���

						str.TrimLeft();
						str.TrimRight();

						return str;
					}
				}
				return Value;//�Ҳ���,����Ĭ��ֵ
			}

		}

	}
	return Value;//�Ҳ���,����Ĭ��ֵ
}

void CIniFile::WriteFileString(CString Section, CString Item, CString Value)
{
	int i = 0;
	int iFileLines = FileContainer.GetSize();
	CString strline,str;

	while(i<iFileLines)
	{
		strline = FileContainer.GetAt(i++);

		strline.TrimLeft();
		if(strline.GetAt(0)=='[')//����Section����һ������Ϊ[
		{
			str=strline.Left(strline.Find(L"]"));//ȥ��]�ұ�
			str=str.Right(str.GetLength()-str.Find(L"[")-1);//ȥ��[���

			str.TrimLeft();
			str.TrimRight();

			if(Section == str)//�ҵ�Section
			{
				while(i<iFileLines)
				{
					strline = FileContainer.GetAt(i++);
					strline.TrimLeft();

					if(strline.GetAt(0)=='[')//���������һ��[]�����Ҳ���Item
					{
						break;
					}
					
					str = strline.Left(strline.Find(L"="));//ȥ��=�ұ�

					str.TrimLeft();
					str.TrimRight();

					if(Item == str)//�ҵ�Item
					{
						strline = Item + "=" + Value;
						FileContainer[i-1] = strline;
						return;
					}
				}
				//�Ҳ���Item
				strline = Item + "=" + Value;
				FileContainer.InsertAt(i-1, strline);
				return;

			}

		}

	}
	//�Ҳ���Section
	//ֱ����������Section��Item��Value
	FileContainer.Add(L"[" + Section + L"]");
	FileContainer.Add(Item + L"=" + Value);
	return;
}

