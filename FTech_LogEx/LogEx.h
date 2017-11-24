#pragma once

//----------------------------------------------------------
// LogEx Class
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------
// Last Update : 2017-11-24 13:44
// Modified by William Kim
//----------------------------------------------------------

#define MAX_BUFFER_SIZE 4096



class CBase
{
public :
	typedef enum  {eNOM=0, eERR	} ELogType;

	void ConvertCStringToChar(CString strIn, char** pcOut)
	{
		//CString to char* //Unicode
		wchar_t* wchar_str;     

		int      char_str_len;  
		wchar_str = strIn.GetBuffer(strIn.GetLength());

		char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
		*pcOut = new char[char_str_len];
		WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, *pcOut, char_str_len, 0,0);
	}
};
// Log base class.
class CLogBase : public CBase
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

	bool WriteLogMsg(ELogType nLogType, CString strMsg);

	bool Write(CString strBuffer=_T(""));

};

class CLogEx : public CBase
{
public:

	static CLogEx*	Instance();
	static void		Release();
private:
	static CLogEx* _instance;

public:
	CLogEx(void);
	~CLogEx(void);

private:
	CLogBase m_LogBase;
	bool m_bInit;
	bool IsExistDir(CString strPath) { 
		if (GetFileAttributes(strPath) == -1) return false; 
	else return true; 
	} // -1 is No Exist
	void CreateDir(CString Path) { CreateDirectory(Path,NULL); }
public:
	void SetFolderPathName(CString strPath, CString strName);
	bool WriteLogMsg(ELogType nLogType, CString strFmt, ...);
};
