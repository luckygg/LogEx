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

void CLogBase::WriteLogMsg(ELogType nLogType, CString strMsg)
{
	if(strMsg.GetLength() < 1)
		return;

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

	Write(strMsg);
	
}

void CLogBase::Write(CString strBuffer)
{
	if( m_strFolderPath.GetLength() < 1 || m_strFileName.GetLength() < 1 )
		return;

	FILE *file=NULL;
	CString strFilePath=L"";

	strFilePath.Format(L"%s%s",m_strFolderPath,GetFileName());
	
	char cFilePath[MAX_BUFFER_SIZE]={0,};
	CStringConvert::CStringToChar(strFilePath, cFilePath);

	if(fopen_s( &file, cFilePath, "a+t" ) == 0 )
	{
		char cBuffer[MAX_BUFFER_SIZE]={0,};
		CStringConvert::CStringToChar(strBuffer, cBuffer);
		
		fprintf(file, "%s\n", cBuffer);

		fclose(file);
	}
	else
	{
		CString msg=L"";
		msg.Format(L"Log File open Fail! (%s)\n", strFilePath);
		OutputDebugString(msg);
	}

	SetBufferSize(m_nBufferSize);
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
}

CLogEx::~CLogEx(void)
{
}

void CLogEx::WriteLogMsg(ELogList nLogList, ELogType nLogType, CString strFmt, ...)
{
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

	m_Log[nLogList].WriteLogMsg(nLogType, strTemp);
}

void CLogEx::OnWriteNowAll()
{
	for(int i = 0; i < LogList_MAX; i++)
		m_Log[i].Write();
}

void CLogEx::OnWriteNowAt(ELogList nLogList)
{
	m_Log[nLogList].Write();
}

void CLogEx::Initialize(CString strPath)
{
	if (IsExistDir(strPath) == false)
		CreateDir(strPath);
	
	strPath+=L"\\";

	m_Log[LogList_TOTAL].SetFileName(L"Total Log");
	m_Log[LogList_TOTAL].SetFolderPath(strPath);
}