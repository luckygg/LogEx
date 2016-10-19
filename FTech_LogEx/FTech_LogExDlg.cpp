
// FTech_LogExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_LogEx.h"
#include "FTech_LogExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFTech_LogExDlg dialog
CFTech_LogExDlg::CFTech_LogExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_LogExDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTech_LogExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFTech_LogExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFTech_LogExDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFTech_LogExDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CFTech_LogExDlg message handlers

BOOL CFTech_LogExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_Log[Log_Error].SetFolderPathName(L"C:\\Log",L"ERROR");
	m_Log[Log_Total].SetFolderPathName(L"C:\\Log",L"TOTAL");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTech_LogExDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFTech_LogExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFTech_LogExDlg::OnBnClickedButton1()
{
	// Total에도 같이 기록한다.
	m_Log[Log_Error].WriteLogMsg(LogType_ERR, L"Error !!");
	m_Log[Log_Total].WriteLogMsg(LogType_ERR, L"Error !!");
}


void CFTech_LogExDlg::OnBnClickedButton2()
{
	m_Log[Log_Total].WriteLogMsg(LogType_NOM, L"Normal !!");
}
