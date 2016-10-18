
// FTech_LogExDlg.h : header file
//

#pragma once
#include "LogEx.h"
#include "StringConvert.h"
// CFTech_LogExDlg dialog
class CFTech_LogExDlg : public CDialogEx
{
// Construction
public:
	CFTech_LogExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTECH_LOGEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public :
	CLogEx m_Log;
	bool m_bWork;
	bool m_bSave;
	void OnAddLog(int nThId);
	void OnAddLog2();

	char* CStringToChar(CString strIn);
	bool CStringToChar(const CString strIn, char* pchOut);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
