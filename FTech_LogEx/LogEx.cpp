#include "StdAfx.h"
#include "StringConvert.h"
#include "LogEx.h"

CLogBase::CLogBase(void)
{
	m_nBufferSize	= MAX_BUFFER_SIZE;
	
	m_strFolderPath = L"";
	m_strFileName	= L"";

	m_bTime			= true;

	SetBufferSize(m_nBufferSize);
}

CLogBase::~CLogBase(void)
{
	Write();
}

CString CLogBase::GetFileName()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	CString strFilePath=L"";
	strFilePath.Format(L"[%04u-%02u-%02u]_%s.txt", t.wYear, t.wMonth, t.wDay, m_strFileName); 

	return strFilePath;
}

bool CLogBase::WriteLogMsg(ELogType nLogType, CString strMsg)
{
	if(strMsg.GetLength() < 1)
		return false;

	CString strLogText=L"";
	CString strType=L"";

	switch(nLogType)
	{
		case LogType_NOM : strType = L"[NOM]"; break;
		case LogType_ERR : strType = L"[ERR]"; break;
	}

	if(m_bTime == true)
	{
		SYSTEMTIME t;
		GetLocalTime(&t);
		// For csv format.
		strLogText.Format(L"%04u-%02u-%02u , %02u:%02u:%02u:%03u , %s , %s"	,t.wYear, t.wMonth, t.wDay
																			,t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, strType, strMsg);
	}
	else
	{
		strLogText.Format(L"%s, %s", strType, strMsg);
	}
	
	strMsg = strLogText;

	return Write(strMsg);
}

bool CLogBase::Write(CString strBuffer)
{
	if( m_strFolderPath.GetLength() < 1 || m_strFileName.GetLength() < 1 )
		return false;

	FILE *file=NULL;
	CString strFilePath=L"";

	strFilePath.Format(L"%s%s",m_strFolderPath,GetFileName());
	
	char cFilePath[MAX_BUFFER_SIZE]={0,};
	CStringConvert::CStringToChar(strFilePath, cFilePath);

	bool ret=false;
	if(fopen_s( &file, cFilePath, "a+t" ) == 0 )
	{
		char cBuffer[MAX_BUFFER_SIZE]={0,};
		CStringConvert::CStringToChar(strBuffer, cBuffer);
		
		fprintf(file, "%s\n", cBuffer);

		fclose(file);
		ret = true;
	}
	else
	{
		CString msg=L"";
		msg.Format(L"Log File open Fail! (%s)\n", strFilePath);
		OutputDebugString(msg);
		ret = false;
	}

	SetBufferSize(m_nBufferSize);

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// CLogEx
//////////////////////////////////////////////////////////////////////////
CLogEx* CLogEx::_instance=NULL;
CLogEx* CLogEx::Instance()
{
	if (_instance == NULL)
	{
		_instance = new CLogEx;
	}

	return _instance;
}

void CLogEx::Release()
{
	if (_instance != NULL) 
	{
		delete _instance;
		_instance = NULL;
	}
}

CLogEx::CLogEx( void )
{
	m_bInit = false;
}

CLogEx::~CLogEx(void)
{
	m_bInit = false;
}

bool CLogEx::WriteLogMsg(ELogType nLogType, CString strFmt, ...)
{
	if (m_bInit == false) return false;
	char cFmt[MAX_BUFFER_SIZE]={0,};
	CStringConvert::CStringToChar(strFmt,cFmt);

	char buf[MAX_BUFFER_SIZE]={0,};
	va_list vlist;
	va_start(vlist, strFmt);
	int len = vsprintf_s(buf, cFmt, vlist);
	va_end(vlist);

	CString strTemp=L"";

	CString tmp = (CString)buf;
	strTemp.Format(L"MSG: %s",tmp);

	char cTemp[MAX_BUFFER_SIZE]={0,};
	CStringConvert::CStringToChar(strTemp,cTemp);

	sprintf_s(buf,cTemp);

	return m_LogBase.WriteLogMsg(nLogType, strTemp);
}

void CLogEx::SetFolderPathName(CString strPath, CString strName)
{
	if (IsExistDir(strPath) == false)
		CreateDir(strPath);
	
	strPath+=L"\\";

	m_LogBase.SetFileName(strName);
	m_LogBase.SetFolderPath(strPath);

	m_bInit = true;
}