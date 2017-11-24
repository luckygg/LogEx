#include "StdAfx.h"
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
	strFilePath.Format(_T("[%04u-%02u-%02u]_%s.txt"), t.wYear, t.wMonth, t.wDay, m_strFileName); 

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
		case eNOM : strType = _T("[NOM]"); break;
		case eERR : strType = _T("[ERR]"); break;
	}

	if(m_bTime == true)
	{
		SYSTEMTIME t;
		GetLocalTime(&t);
		// For csv format.
		strLogText.Format(_T("%04u-%02u-%02u , %02u:%02u:%02u:%03u , %s , %s") ,t.wYear, t.wMonth, t.wDay
																			,t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, strType, strMsg);
	}
	else
	{
		strLogText.Format(_T("%s, %s"), strType, strMsg);
	}
	
	strMsg = strLogText;

	return Write(strMsg);
}

bool CLogBase::Write(CString strBuffer)
{
	if( m_strFolderPath.GetLength() < 1 || m_strFileName.GetLength() < 1 )
		return false;

	FILE *file=NULL;
	CString strFilePath=_T("");

	strFilePath.Format(_T("%s%s"),m_strFolderPath,GetFileName());
	
	char* pFilePath=NULL;
	ConvertCStringToChar(strFilePath, &pFilePath);

	bool ret=false;
	if(fopen_s( &file, pFilePath, "a+t" ) == 0 )
	{
		char* pBuffer=NULL;
		ConvertCStringToChar(strBuffer, &pBuffer);
		
		fprintf(file, "%s\n", pBuffer);

		fclose(file);

		delete []pBuffer;
		pBuffer = NULL;
		ret = true;
	}
	else
	{
		CString msg=L"";
		msg.Format(_T("Log File open Fail! (%s)\n"), strFilePath);
		OutputDebugString(msg);
		ret = false;
	}

	delete []pFilePath;
	pFilePath = NULL;

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
	char* pcFmt = NULL;
	ConvertCStringToChar(strFmt,&pcFmt);

	char buf[MAX_BUFFER_SIZE]={0,};
	va_list vlist;
	va_start(vlist, strFmt);
	int len = vsprintf_s(buf, pcFmt, vlist);
	va_end(vlist);

	delete []pcFmt;
	pcFmt = NULL;

	CString strTemp=_T("");
	CString tmp = (CString)buf;
	strTemp.Format(_T("%s"),tmp);

	/*ConvertCStringToChar(strTemp,pcFmt);

	sprintf_s(buf,pcFmt);*/

	return m_LogBase.WriteLogMsg(nLogType, strTemp);
}

void CLogEx::SetFolderPathName(CString strPath, CString strName)
{
	if (IsExistDir(strPath) == false)
		CreateDir(strPath);
	
	strPath+=_T("\\");

	m_LogBase.SetFileName(strName);
	m_LogBase.SetFolderPath(strPath);

	m_bInit = true;
}