
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



UINT Thread1(LPVOID param);
UINT Thread2(LPVOID param);
UINT Thread3(LPVOID param);
CFTech_LogExDlg::CFTech_LogExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_LogExDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bWork = false;
	m_bSave = false;
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

	m_Log.Initialize(L"C:\\Log");

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
	m_bWork = true;

	AfxBeginThread(Thread1, this);
	AfxBeginThread(Thread2, this);
	//AfxBeginThread(Thread3, this);
	//m_Log.WriteLogMsg(LogList_TOTAL, LogType_NOM, L"%d %s", 1," Thread is working.");
	//m_Log.WriteLogMsg(LogList_TOTAL, LogType_NOM, L"%d %s", 2," Thread is working.");
}

void CFTech_LogExDlg::OnAddLog(int nThId)
{
	m_Log.WriteLogMsg(LogList_TOTAL, LogType_NOM, L"%d %s", nThId," Thread is working.");
}

void CFTech_LogExDlg::OnAddLog2()
{
	CString tmp;
	tmp.Format(L"Thread, Message Output");
	m_Log.WriteLogMsg(LogList_TOTAL, LogType_NOM, tmp);
}

UINT Thread1(LPVOID param)
{
	CFTech_LogExDlg* pMain = (CFTech_LogExDlg*)param;

	while(pMain->m_bWork)
	{
		//Sleep(100);
		if (pMain->m_bSave)
		{
			pMain->OnAddLog(1);
			break;
		}
	}

	return 0;
}

UINT Thread2(LPVOID param)
{
	CFTech_LogExDlg* pMain = (CFTech_LogExDlg*)param;

	while(pMain->m_bWork)
	{
		//Sleep(30);
		if (pMain->m_bSave)
		{
			pMain->OnAddLog(2);
			break;
		}
	}

	return 0;
}

UINT Thread3(LPVOID param)
{
	CFTech_LogExDlg* pMain = (CFTech_LogExDlg*)param;

	while(pMain->m_bWork)
	{
		Sleep(500);
		pMain->OnAddLog2();
	}

	return 0;
}

void CFTech_LogExDlg::OnBnClickedButton2()
{
	//m_bWork = false;
	m_bSave = true;
}

char* CFTech_LogExDlg::CStringToChar(CString strIn)
{
	size_t szCvt = 0;
	static char tmpChar[MAX_PATH] = "";
	wcstombs_s(&szCvt, tmpChar, strIn.GetLength()+1, strIn, _TRUNCATE);

	return tmpChar;
}

bool CFTech_LogExDlg::CStringToChar(const CString strIn, char* pchOut)
{
	if (pchOut == NULL) return false;

	size_t szCvt = 0;
	wcstombs_s(&szCvt, pchOut, strIn.GetLength()+1, strIn, _TRUNCATE);

	return true;
}
