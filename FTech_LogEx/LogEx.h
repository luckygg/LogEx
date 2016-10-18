#pragma once

#define MAX_BUFFER_SIZE 4096

enum ELogType
{
	LogType_NOM,		// Normal.
	LogType_ERR			// Error.
};

enum ELogList
{
	LogList_ERROR,		// Error log.
	LogList_JOB,		// JOB log.
	LogList_TOTAL,		// Total log.
	LogList_TCPIP,		// TCP/IP log.
	LogList_RS232,		// RS232 log.
	LogList_MAX			// Enum max count.
};

// Log base class.
class CLogBase
{
public:
	CLogBase(void);
	~CLogBase(void);

private:
	bool m_bTime;
	int m_nBufferSize;

	CString m_strFolderPath;	// Folder path.
	CString m_strFileName;		// File name.

public:
	void SetFolderPath(CString strPath) { m_strFolderPath = strPath; }
	void SetFileName(CString szFileName) { m_strFileName = szFileName; }

	CString GetFileName();

	void SetBufferSize(UINT nBufferSize) { m_nBufferSize = nBufferSize; }
	void SetAddTime(bool bEnable) {	m_bTime = bEnable; }

	void WriteLogMsg(ELogType nLogType, CString strMsg);

	void Write(CString strBuffer=L"");
};

class CLogEx
{
public:
	static CLogEx* Instance();
	static void Release();
private:
	static CLogEx* _instance;

public:
	CLogEx(void);
	~CLogEx(void);

private:
	CLogBase m_Log[LogList_MAX];
	bool IsExistDir(CString strPath) { 
		if (GetFileAttributes(strPath) == -1) return false; 
	else return true; 
	} // -1 is No Exist
	void CreateDir(CString Path) { CreateDirectory(Path,NULL); }
public:
	void Initialize(CString strPath);
	void WriteLogMsg(ELogList nLogList, ELogType nLogType, CString strFmt, ...);
	void OnWriteNowAll();
	void OnWriteNowAt(ELogList nLogList);
};
