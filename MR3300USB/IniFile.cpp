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
	//保存到FileContainer
	WriteFileString(Section, Item, strtemp);
	//保存到ini文件
	WriteIniFile();
}

void CIniFile::SetFloat(CString Section, CString Item, float Value)
{
	CString strtemp;
	strtemp.Format(L"%lf",Value);
	//保存到FileContainer
	WriteFileString(Section, Item, strtemp);
	//保存到ini文件
	WriteIniFile();
}

void CIniFile::SetString(CString Section, CString Item, CString Value)
{
	//保存到FileContainer
	WriteFileString(Section, Item, Value);
	//保存到ini文件
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

	//将IniFile文件数据读到FileContainer
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

	//将FileContainer写到IniFile文件
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
	ReadIniFile();//打开文件

	if(bFileExist == FALSE || FileContainer.GetSize() < 0)
		return Value;//文件打开出错或文件为空，返回默认值

	int i = 0;
	int iFileLines = FileContainer.GetSize();
	CString strline,str;

	while(i<iFileLines)
	{
		strline = FileContainer.GetAt(i++);

		strline.TrimLeft();
		if(strline.GetAt(0)=='[')//查找Section，第一个必须为[
		{
			str=strline.Left(strline.Find(L"]"));//去掉]右边
			str=str.Right(str.GetLength()-str.Find(L"[")-1);//去掉[左边

			str.TrimLeft();
			str.TrimRight();

			if(Section == str)//找到Section
			{
				while(i<iFileLines)
				{
					strline = FileContainer.GetAt(i++);
					strline.TrimLeft();

					if(strline.GetAt(0)=='[')
						return Value;//如果到达下一个[]，即找不到,返回默认值
					
					str = strline.Left(strline.Find(L"="));//去掉=右边

					str.TrimLeft();
					str.TrimRight();

					if(Item == str)//找到Item
					{
						str=strline.Right(strline.GetLength()-strline.Find(L"=")-1);//去掉=左边

						str.TrimLeft();
						str.TrimRight();

						return str;
					}
				}
				return Value;//找不到,返回默认值
			}

		}

	}
	return Value;//找不到,返回默认值
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
		if(strline.GetAt(0)=='[')//查找Section，第一个必须为[
		{
			str=strline.Left(strline.Find(L"]"));//去掉]右边
			str=str.Right(str.GetLength()-str.Find(L"[")-1);//去掉[左边

			str.TrimLeft();
			str.TrimRight();

			if(Section == str)//找到Section
			{
				while(i<iFileLines)
				{
					strline = FileContainer.GetAt(i++);
					strline.TrimLeft();

					if(strline.GetAt(0)=='[')//如果到达下一个[]，即找不到Item
					{
						break;
					}
					
					str = strline.Left(strline.Find(L"="));//去掉=右边

					str.TrimLeft();
					str.TrimRight();

					if(Item == str)//找到Item
					{
						strline = Item + "=" + Value;
						FileContainer[i-1] = strline;
						return;
					}
				}
				//找不到Item
				strline = Item + "=" + Value;
				FileContainer.InsertAt(i-1, strline);
				return;

			}

		}

	}
	//找不到Section
	//直接在最后加入Section，Item，Value
	FileContainer.Add(L"[" + Section + L"]");
	FileContainer.Add(Item + L"=" + Value);
	return;
}

