
// FTech_LogExDlg.h : header file
//

#pragma once
#include "LogEx.h"
// CFTech_LogExDlg dialog

enum ELogList {Log_Error, Log_Total, Log_Max};
class CFTech_LogExDlg : public CDialogEx
{
// Construction
public:
	CFTech_LogExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTECH_LOGEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private :
	CLogEx m_Log[Log_Max];
public :
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