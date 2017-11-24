
// FTech_LogExDlg.h : header file
//

#pragma once
#include "LogEx.h"
// CFTech_LogExDlg dialog

class CFTech_LogExDlg : public CDialogEx
{
// Construction
public:
	CFTech_LogExDlg(CWnd* pParent = NULL);	// standard constructor

	typedef enum {eError=0, eTotal, eMax} ELogList ;
// Dialog Data
	enum { IDD = IDD_FTECH_LOGEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private :
	CLogEx m_Log[eMax];
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