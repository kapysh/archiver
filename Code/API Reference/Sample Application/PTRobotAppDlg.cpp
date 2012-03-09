// PTRobotAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PTRobotApp.h"
#include "PTRobotAppDlg.h"
#include ".\ptrobotappdlg.h"
#include "..\PTRobot.h"
#include "SelectRoboticDrives.h"
#include "SetPrinterSettings.h"
#include "SetMergeData.h"
#include <Winioctl.h>
#include <process.h>
#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_STRING 512

HANDLE g_hKillThreadEvent;

//// PROTOTYPES ////
void _stdcall OpenCloseDrive(HANDLE hDrive, DWORD dwOpen);	// NOTE: must use _stdcall for callback open/close
unsigned __stdcall MoveDiscsThread( LPVOID lpVoid );
DWORD WaitForCommand(HANDLE hRobot);
BOOL OpenClose(TCHAR *tszDrive, DWORD dwOpen);
DWORD MyMessageBoxW( WCHAR * wszText, WCHAR * wszCaption, UINT nType );

typedef struct tagThreadInfo
{
	HANDLE		hRobot;
	HANDLE		hDrive[4];						// array for up to 4 drives per robot
	int			nNumDrives;
	int			nRobot;
	int			nCopies;
	DWORD		dwTo;
	DWORD		dwFrom;
	BOOL		fUseRecorders;
	BOOL		fUsePrinter;
	BOOL		fPrintFirst;
	TCHAR		tszPrintFile[MAX_PATH];
	CString		csMergeData1;
	CString		csMergeData2;
	CString		csMergeData3;
	CString		csMergeData4;
	CString		csMergeData5;
	BOOL		fMergeMethod2;
}THREAD_INFO, *PTHREAD_INFO;
// CAboutDlg dialog used for App About


//// GLOBAL VARIABLES /////
THREAD_INFO g_ThreadInfo;
TCHAR g_szRobotStatus[20][100];		// arrays for up to 20 robots
TCHAR g_szProgress[20][100];
BOOL g_fRobotRunning[20];	
int g_nLanguage = 0;


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPTRobotAppDlg dialog



CPTRobotAppDlg::CPTRobotAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPTRobotAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPTRobotAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROBOT_COMBO, m_RobotCombo);
	DDX_Control(pDX, IDC_ENUM_ROBOTS_BTN, m_EnumRobotsBtn);
	DDX_Control(pDX, IDC_FROM_COMBO, m_FromCombo);
	DDX_Control(pDX, IDC_TO_COMBO, m_ToCombo);
	DDX_Control(pDX, IDC_THROUGH_REC_CHK, m_ThroughRecChk);
	DDX_Control(pDX, IDC_PRINT_FIRST_CHK, m_PrintFirstChk);
	DDX_Control(pDX, IDC_PRINT_FILE_EDIT, m_PrintFileEdit);
	DDX_Control(pDX, IDC_PRINT_BROWSE_BTN, m_PrintBrowseBtn);
	DDX_Control(pDX, IDC_GO_BTN, m_GoBtn);
	DDX_Control(pDX, IDC_PRINTFILE_STATIC, m_PrintFileStatic);
	DDX_Control(pDX, IDC_ROBOT_STATIC, m_RobotStatic);
	DDX_Control(pDX, IDC_MOVEDISCS_GRP, m_MoveDiscsGrp);
	DDX_Control(pDX, IDC_FROM_STATIC, m_FromStatic);
	DDX_Control(pDX, IDC_TO_STATIC, m_ToStatic);
	DDX_Control(pDX, IDC_ROBOTTYPE_STATIC, m_RobotTypeStatic);
	DDX_Control(pDX, IDC_NUMDRIVES_STATIC, m_NumDrivesStatic);
	DDX_Control(pDX, IDC_PRINTER_STATIC, m_PrinterStatic);
	DDX_Control(pDX, IDC_NUMBINS_STATIC, m_NumBinsStatic);
	DDX_Control(pDX, IDC_DRIVE_LIST, m_DriveList);
	DDX_Control(pDX, IDC_OPEN_CLOSE, m_DriveOpenCloseBtn);
	DDX_Control(pDX, IDC_COPIES_EDIT, m_CopiesEdit);
	DDX_Control(pDX, IDC_KILLERROR_BTN, m_KillErrorBtn);
	DDX_Control(pDX, IDC_ROBOTSTATUS, m_RobotStatus);
	DDX_Control(pDX, IDC_KIOSKMODE_CHK, m_KioskModeChk);
	DDX_Control(pDX, IDC_THROGH_PTR_CHK, m_ThroughPrinterChk);
	DDX_Control(pDX, IDC_GET_PTRSETTINGS, m_GetPrinterSettings);
	DDX_Control(pDX, IDC_SET_PTRSETTINGS, m_SetPrinterSettings);
	DDX_Control(pDX, IDC_MANUAL_OPEN_CLOSE_CHK, m_ManualOpenCloseChk);
	DDX_Control(pDX, IDC_JOBPROGRESS, m_JobProgress);
	DDX_Control(pDX, IDC_SET_MERGE, m_SetMergeBtn);
	DDX_Control(pDX, IDC_LANG_COMBO, m_LangCombo);
	DDX_Control(pDX, IDC_SYSTEM_ACTION, m_SystemActionBtn);
	DDX_Control(pDX, IDC_SYSTEMACTION_COMBO, m_SysActionCombo);
}

BEGIN_MESSAGE_MAP(CPTRobotAppDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PRINT_BROWSE_BTN, OnBnClickedPrintBrowseBtn)
	ON_BN_CLICKED(IDC_GO_BTN, OnBnClickedGoBtn)
	ON_CBN_SELCHANGE(IDC_ROBOT_COMBO, OnCbnSelchangeRobotCombo)
	ON_BN_CLICKED(IDC_DRIVEINFO_BTN, OnBnClickedDriveinfoBtn)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_KILLERROR_BTN, OnBnClickedKillerrorBtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_KIOSKMODE_CHK, OnBnClickedKioskmodeChk)
	ON_BN_CLICKED(IDC_THROGH_PTR_CHK, OnBnClickedThroghPtrChk)
	ON_CBN_SELCHANGE(IDC_FROM_COMBO, OnCbnSelchangeFromCombo)
	ON_CBN_SELCHANGE(IDC_TO_COMBO, OnCbnSelchangeToCombo)
	ON_BN_CLICKED(IDC_GET_PTRSETTINGS, OnBnClickedGetPtrsettings)
	ON_BN_CLICKED(IDC_SET_PTRSETTINGS, OnBnClickedSetPtrsettings)
	ON_BN_CLICKED(IDC_OPEN_CLOSE, OnBnClickedOpenClose)
	ON_BN_CLICKED(IDC_SET_MERGE, OnBnClickedSetMerge)
	ON_BN_CLICKED(IDC_ENUM_ROBOTS_BTN, OnBnClickedEnumRobotsBtn)
	ON_BN_CLICKED(IDC_ENUM_DRIVES, OnBnClickedEnumDrives)
	ON_BN_CLICKED(IDC_PRINT_FIRST_CHK, OnBnClickedPrintFirstChk)
	ON_BN_CLICKED(IDC_THROUGH_REC_CHK, OnBnClickedThroughRecChk)
	ON_CBN_SELCHANGE(IDC_LANG_COMBO, OnCbnSelchangeLangCombo)
	ON_BN_CLICKED(IDC_SYSTEM_ACTION, OnBnClickedSystemAction)
END_MESSAGE_MAP()


// CPTRobotAppDlg message handlers


// ******************************************************************************** //
BOOL CPTRobotAppDlg::OnInitDialog()
{	
	int nResponse, nRobot;
	DWORD dwRetVal = PTROBOT_OK, dwRet;
	BOOL fError = FALSE;
	WCHAR wszErrorString[MAX_STRING];
	PTRobotInfo myRobotInfo;
	PTManufactureInfo myManufactureInfo;

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	#ifdef UNICODE
		this->SetDlgItemText( IDC_UNICODE, _T("(Unicode)"));
	#else
		this->SetDlgItemText( IDC_UNICODE, _T("(MBCS)"));
	#endif

	this->m_csMergeData1 = _T("");
	this->m_csMergeData2 = _T("");
	this->m_csMergeData3 = _T("");
	this->m_csMergeData4 = _T("");
	this->m_csMergeData5 = _T("");
	this->m_fMergeMethod2 = false;

	this->m_nRobots=0;


	///////////////////////////////////////////
	//
	//	Setup debugging on the PTRobot module
	//
	/////////////////////////////////////////// 
	dwRetVal = PTRobot_SetupDebugging(_TEXT("C:\\PTRobotDbg.dbg"), 4, _TEXT("C:\\PTRobotTrace.dbg"));
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(0x00000000, dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_SetupDebugging Error", MB_OK);
	}

	///////////////////////////////////////////
	//
	//	Initialize the PTRobot module
	//
	///////////////////////////////////////////
	dwRetVal = PTRobot_Initialize();
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(0x00000000, dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_Initialize Error", MB_OK);
	}
	
	///////////////////////////////////////////
	//
	//	Set the app id.  This is only necessary if you have
	//  received an application ID from Primera.
	//
	//////////////////////////////////////////
	dwRetVal = PTRobot_SetApplicationID( 0 ); 
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(0x00000000, dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_SetApplicationID Error", MB_OK);
	}
	///////////////////////////////////////////
	//
	//	Enumerate the robots and populate the combo box
	//
	///////////////////////////////////////////
	while( 1 )
	{
		EnumRobots();

		if (this->m_RobotCombo.GetCount() == 0)
		{
			nResponse = MessageBox(_T("Unable to enumerate Robots"), _T("Error"), MB_RETRYCANCEL);
			if( nResponse == IDCANCEL )
			{
				PTRobot_Destroy();			// must call before exiting
				this->EndDialog(0);
				return FALSE;
			}
		}
		else
			break;
	}

	this->m_RobotCombo.SetCurSel(0);
	this->UpdateRobotInfo();

	nRobot = this->m_RobotCombo.GetCurSel();
	if( nRobot < 0 )
		nRobot = 0;

	dwRet = PTRobot_GetRobotInfo(this->m_hRobots[nRobot], &myRobotInfo);
	
	// Show options depending on if Kiosk mode is supported or not
	if (myRobotInfo.dwSupportedOptions &  PTOPT_KIOSKMODE)
	{
		this->m_KioskModeChk.EnableWindow(TRUE);

		this->m_FromCombo.InsertString(0, _T("Auto"));
		this->m_FromCombo.InsertString(1, _T("Right Bin"));
		this->m_FromCombo.InsertString(2, _T("Left Bin"));
		this->m_FromCombo.SetCurSel(0);

		this->m_ToCombo.InsertString(0, _T("Auto"));
		this->m_ToCombo.InsertString(1, _T("Right Bin"));
		this->m_ToCombo.InsertString(2, _T("Left Bin"));
		this->m_ToCombo.InsertString(3, _T("Reject"));
	}
	else
	{
		this->m_KioskModeChk.EnableWindow(FALSE);

		this->m_FromCombo.InsertString(0, _T("Right Bin"));
		this->m_FromCombo.SetCurSel(0);

		this->m_ToCombo.InsertString(0, _T("Left Bin"));
		this->m_ToCombo.SetCurSel(0);
	}

	dwRet = PTRobot_GetManufactureInfo(this->m_hRobots[nRobot], &myManufactureInfo);

	this->m_ToCombo.SetCurSel(0);
	this->m_CopiesEdit.SetWindowText(_T("1"));
	this->SetTimer(1, 1000, 0);
	this->m_PrintFileEdit.EnableWindow(FALSE);
	this->m_JobProgress.SetWindowText(_T(" "));
	this->m_PrintBrowseBtn.EnableWindow(FALSE);
	this->m_SetPrinterSettings.EnableWindow(FALSE);
	this->m_GetPrinterSettings.EnableWindow(FALSE);
	this->m_SetMergeBtn.EnableWindow(FALSE);
	this->m_PrintFirstChk.EnableWindow(FALSE);

	// NOTE: This is the order specified in PTRobot.h (ie. English=0, Japanese=1, etc.)
	this->m_LangCombo.InsertString(0, _T("English"));
	this->m_LangCombo.InsertString(1, _T("Japanese"));
	this->m_LangCombo.InsertString(2, _T("German"));
	this->m_LangCombo.InsertString(3, _T("French"));
	this->m_LangCombo.InsertString(4, _T("Spanish"));
	this->m_LangCombo.InsertString(5, _T("Italian"));
	this->m_LangCombo.InsertString(6, _T("Chinese (simplified)"));
	this->m_LangCombo.InsertString(7, _T("Korean"));
	this->m_LangCombo.InsertString(8, _T("Polish"));
	this->m_LangCombo.InsertString(9, _T("Chinese (traditional)"));


	this->m_LangCombo.SetCurSel(0);

	g_hKillThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPTRobotAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPTRobotAppDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPTRobotAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPTRobotAppDlg::OnBnClickedEnumRobotsBtn()
{
	if (this->EnumRobots())
	{
		this->m_RobotCombo.SetCurSel(0);
		this->UpdateRobotInfo();
	}
}

void CPTRobotAppDlg::OnBnClickedRobotInfoBtn()
{
	
}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedPrintBrowseBtn()
{
	OPENFILENAME fileToOpenPRN;
	TCHAR tszFile[MAX_PATH] = _T("");       // buffer for file name
	DWORD Error;
	TCHAR errstr[5];
	INT  nLen;

	ZeroMemory(&fileToOpenPRN, sizeof(OPENFILENAME));
	fileToOpenPRN.lStructSize = sizeof(OPENFILENAME);
	fileToOpenPRN.hwndOwner = NULL;
	fileToOpenPRN.lpstrFile = tszFile;
	fileToOpenPRN.nMaxFile = sizeof(tszFile)/sizeof(TCHAR);
	fileToOpenPRN.lpstrFilter = _T("All\0*.*\0Print Files (.prn .std .bmp .jpg)\0*.PRN;*.STD;*.BMP;*.JPG\0");
	fileToOpenPRN.nFilterIndex = 2;
	fileToOpenPRN.lpstrFileTitle = NULL;
	fileToOpenPRN.nMaxFileTitle = 0;
	fileToOpenPRN.lpstrInitialDir = NULL;
	fileToOpenPRN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&fileToOpenPRN) == TRUE)
	{
		this->m_PrintFileEdit.SetWindowText(fileToOpenPRN.lpstrFile);
	
		// Enable the Merge button only if a Surething (.STD) file selected
		this->m_PrintFileEdit.GetWindowText( tszFile, MAX_PATH );
		nLen = (INT)_tcslen( tszFile );
		if( nLen > 4 )
		{
			if( !_tcsicmp( &tszFile[nLen-4], _T(".STD" )) )
			{
				this->m_SetMergeBtn.EnableWindow(TRUE);				
				PTRobot_GetSureThingPreview(tszFile, _T("C:\\PTRobotPreview.jpg"), 72); 
			}
			else
				this->m_SetMergeBtn.EnableWindow(FALSE);				
		}
		else
			this->m_SetMergeBtn.EnableWindow(FALSE);				

	}
	else
	{
		Error = CommDlgExtendedError();
		_stprintf(errstr, _T("%i"), Error);
		//MyMessageBox((UINT)errstr, (UINT)"OPENFILE", MB_OK);
	}
	
}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedGoBtn()
{
	HANDLE hMoveDiscsThread;
	DWORD dwTo=0, dwFrom = 0, dwRetVal = PTROBOT_OK;
	int nUseRec = 0, nUsePtr = 0, nIndex, nRet;
	TCHAR tszFile[MAX_PATH], tszCopies[11];
	PTRobotInfo myRobotInfo;
	PTRobotStatus myStatus;
	BOOL fPrintFirst = FALSE;
	WCHAR wszErrorString[MAX_STRING];
	unsigned int uThreadID;

	int nRobot = this->m_RobotCombo.GetCurSel();
	if (nRobot <0)
		nRobot=0;
	dwFrom = this->m_FromCombo.GetCurSel();
	dwTo = this->m_ToCombo.GetCurSel();
	
	nUseRec = this->m_ThroughRecChk.GetCheck();
	nUsePtr = this->m_ThroughPrinterChk.GetCheck();

	this->m_PrintFileEdit.GetWindowText(tszFile, MAX_PATH);
	this->m_CopiesEdit.GetWindowText(tszCopies, 10);

	dwRetVal = PTRobot_GetRobotStatus(this->m_hRobots[nRobot], &myStatus);
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetRobotStatus Error", MB_OK);
		return;
	}

	if (myStatus.dwSystemState == SYSSTATE_BUSY)
	{
		MessageBox( _T("The robot is busy, please try again."), _T("Robot Busy"), MB_OK);
		return;
	}
	else if (myStatus.dwSystemState == SYSSTATE_ERROR)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], myStatus.dwSystemError, wszErrorString, MAX_STRING, g_nLanguage))
		{
			if ((myStatus.dwSystemError == SYSERR_CLR_EMPTY) ||
				(myStatus.dwSystemError == SYSERR_BLK_EMPTY) ||
				(myStatus.dwSystemError == SYSERR_BOTH_EMPTY) ||
				(myStatus.dwSystemError == SYSERR_CLR_EMPTY_FINAL) ||
				(myStatus.dwSystemError == SYSERR_BLK_EMPTY_FINAL) ||
				(myStatus.dwSystemError == SYSERR_BOTH_EMPTY_FINAL))
			{
				
				nRet = MyMessageBoxW( wszErrorString, L"Error", MB_OKCANCEL);
				if (nRet == IDCANCEL)
				{
					if (PTROBOT_OK != PTRobot_SystemAction(this->m_hRobots[nRobot], PTACT_IGNOREINKLOW))
						return;
				}
			}
			else
			{
				MyMessageBoxW( wszErrorString, L"Error", MB_OK);
				return;
			}
		}
		else
		{
			MessageBox(_T("The robot is in an error condition, please click kill error and try again."), _T("Robot Error"), MB_OK);
			return;
		}
		

	}

	dwRetVal = PTRobot_GetRobotInfo(this->m_hRobots[nRobot], &myRobotInfo);
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetRobotInfo Error", MB_OK);
		return;
	}


	///////////////////////////////////////////////////////////////////////////////////////
	// Set the Callback Open/Close function -- if selected
	///////////////////////////////////////////////////////////////////////////////////////

	// For this App, we will throw a dialog that instructs the user to Open/Close the drive
	if (this->m_ManualOpenCloseChk.GetCheck() )
	{
		dwRetVal = PTRobot_SetOpenCloseFunction( &OpenCloseDrive );
		if (dwRetVal != PTROBOT_OK)
		{
			if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
				MyMessageBoxW( wszErrorString, L"PTRobot_SetOpenCloseFunction Error", MB_OK);
		}
	}
	// User chose NOT to use callback open/close
	// Set to NULL to tell PTRobot to use its own open/close function
	else
	{
		dwRetVal = PTRobot_SetOpenCloseFunction( NULL );
		if (dwRetVal != PTROBOT_OK)
		{
			if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
				MyMessageBoxW( wszErrorString, L"PTRobot_SetOpenCloseFunction Error", MB_OK);
		}
	}


	////////////////////////////////////////////////////////////////
	// Get all of the flags and settings before starting the job...
	////////////////////////////////////////////////////////////////
	if (nUseRec==1)
		g_ThreadInfo.fUseRecorders = TRUE;
	else
		g_ThreadInfo.fUseRecorders = FALSE;

	if (nUsePtr == 1)
		g_ThreadInfo.fUsePrinter = TRUE;
	else
		g_ThreadInfo.fUsePrinter = FALSE;

	if ((g_ThreadInfo.fUseRecorders) && (g_ThreadInfo.fUsePrinter) &&
		this->m_PrintFirstChk.GetCheck())
		g_ThreadInfo.fPrintFirst = TRUE;
	else
		g_ThreadInfo.fPrintFirst = FALSE;

	g_ThreadInfo.dwFrom = dwFrom;
	g_ThreadInfo.dwTo = dwTo;
	
	g_ThreadInfo.nNumDrives = (int)myRobotInfo.dwNumDrives;
	for ( nIndex=0; nIndex<(int)myRobotInfo.dwNumDrives; nIndex++ )
		g_ThreadInfo.hDrive[nIndex] = myRobotInfo.hDrives[nIndex];
	g_ThreadInfo.hRobot = this->m_hRobots[nRobot];
	g_ThreadInfo.nCopies = GetIntFromString(tszCopies);
	g_ThreadInfo.nRobot = nRobot;
	_tcscpy(g_ThreadInfo.tszPrintFile, tszFile);
	g_ThreadInfo.csMergeData1 = this->m_csMergeData1;
	g_ThreadInfo.csMergeData2 = this->m_csMergeData2;
	g_ThreadInfo.csMergeData3 = this->m_csMergeData3;
	g_ThreadInfo.csMergeData4 = this->m_csMergeData4;
	g_ThreadInfo.csMergeData5 = this->m_csMergeData5;
	g_ThreadInfo.fMergeMethod2 = this->m_fMergeMethod2;


	
	//////////////////////////////////////////////////////
	// Finally, start the Thread to perform the movements
	//////////////////////////////////////////////////////
	if ( hMoveDiscsThread = (HANDLE)_beginthreadex (NULL, 0, MoveDiscsThread, (LPVOID)&g_ThreadInfo, 0, &uThreadID) )
	{
		CloseHandle (hMoveDiscsThread);
	}
	g_fRobotRunning[nRobot] = TRUE;
}



// ******************************************************************************** //
//
// Callback OpenCloseDrive function
//
// PTRobot.dll will call this if enabled.
// We are simply displaying a dialog for the user to open/close the drive
// Most applications would use their burning engine to open/close the drive here...
//
// NOTE: must use _stdcall calling convention!
//
// ******************************************************************************** //
void _stdcall OpenCloseDrive(HANDLE hDrive, DWORD dwOpen)
{
	PTDriveInfo myDriveInfo;
	TCHAR tszDrive[20];
	DWORD dwRetVal = PTROBOT_OK;
	WCHAR wszErrorString[MAX_STRING];

	// Get the description of the drive for display
	dwRetVal = PTRobot_GetDriveInfo(hDrive, &myDriveInfo);
	if ( dwRetVal == PTROBOT_OK )
	{
		// Tell the user to open or close the drive
		_stprintf(tszDrive, _T("\\\\.\\%c:"), (TCHAR)myDriveInfo.hDrive);
		if (!OpenClose(tszDrive, dwOpen))
			MessageBox(NULL, _T("Open/Close IOCTL returned FALSE"), _T("Error"), MB_OK);
	}
	else
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(0x00000000, dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetDriveInfo Error", MB_OK);
	}

}

BOOL OpenClose(TCHAR *tszDrive, DWORD dwOpen) 
{ 
    HANDLE hDevice; 
    DWORD dwBytesReturned; 
	BOOL fResult = FALSE;
	int nRetries=3;

    //get a handle to the device, the parameters used here must be used in order for this to work 
    hDevice=CreateFile(tszDrive, GENERIC_READ|GENERIC_WRITE,
						FILE_SHARE_READ|FILE_SHARE_WRITE, 0,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); 

    //if for some reason we couldn't get a handle to the device we will try again using slightly different parameters for CreateFile 
    if (hDevice != INVALID_HANDLE_VALUE) 
	{
		//Version 1.0.2 We added some retries if the iocontrol function failed.
		while (1)
		{
			if (dwOpen == DRIVE_OPEN)
			{
				fResult=DeviceIoControl(hDevice,IOCTL_STORAGE_EJECT_MEDIA,0,0,0,0,&dwBytesReturned,0); 
			}
			else
			{
				fResult=DeviceIoControl(hDevice,IOCTL_STORAGE_LOAD_MEDIA,0,0,0,0,&dwBytesReturned,0); 
			}
			if ( fResult || (nRetries-- <=0))
				break;
			Sleep(50);
		}
		CloseHandle(hDevice);
	}

	 
    return fResult; 
} 

// ******************************************************************************** //
// WaitForCommand()
//
// Call this to wait for the command to complete 
// (or wait until a robotic error occurs).
//
// ******************************************************************************** //
DWORD WaitForCommand(HANDLE hRobot)
{
	PTRobotStatus myStatus;
	int nInterval=0, nRet;
	DWORD dwRet = SYSERR_NONE, dwWaitResult;
	DWORD dwError = SYSERR_NONE;
	WCHAR wszErrorString[MAX_STRING];
	TCHAR tszDbg[256];

	while(1)
	{
		dwWaitResult = WaitForSingleObject(g_hKillThreadEvent, 0);
		if (dwWaitResult == WAIT_OBJECT_0)
			return 0xFFFFFFFF;
		
		dwRet = PTRobot_GetRobotStatus(hRobot, &myStatus);
		//Version 1.0.1 Check the return value of GetRobotStatus Right now the only error that
		//              is returned in PTROBOT_INVALID_ROBOT, so we are just going to break and
		//              return that from this function.
		if (dwRet != PTROBOT_OK)
		{
			if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
				MyMessageBoxW( wszErrorString, L"PTRobot Error", MB_OKCANCEL);
			else
			{
				_stprintf(tszDbg, _T("PTRobot Error (%lu)"), dwRet);
				MessageBox(NULL, tszDbg, _T("PTRobot Error"), MB_OKCANCEL);
			}
			break;
		}
		if ((myStatus.dwSystemState == SYSSTATE_IDLE))
		{
			break;
		}
		else if ((myStatus.dwSystemState == SYSSTATE_ERROR))
		{
			if ((dwError != myStatus.dwSystemError) && (myStatus.dwSystemError != 0))
			{
				dwError = myStatus.dwSystemError;
				if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, myStatus.dwSystemError, wszErrorString, MAX_STRING, g_nLanguage))
				{
					nRet = MyMessageBoxW( wszErrorString, L"System Error", MB_OKCANCEL);
					if (nRet == IDCANCEL)
					{
						dwRet = myStatus.dwSystemError;
						PTRobot_SystemAction(hRobot, PTACT_CANCELCMD	);
						break;
					}
				}
				else
				{
					_stprintf(tszDbg, _T("System Error (%lu)"), myStatus.dwSystemError);
					nRet = MessageBox(NULL, tszDbg, _T("System Error"), MB_OKCANCEL);
					if (nRet == IDCANCEL)
					{
						dwRet = myStatus.dwSystemError;
						PTRobot_SystemAction(hRobot, PTACT_CANCELCMD	);
						break;
					}
				}
			}
		}
		Sleep(500);
	}
	return dwRet;
}



// ******************************************************************************** //
// MoveDiscsThread()
//
// This is where the action is...
// NOTE that job information is being passed in lpVoid via the PTHREAD_INFO structure
//
// ******************************************************************************** //
unsigned __stdcall MoveDiscsThread( LPVOID lpVoid )
{
	DWORD dwTo=0, dwFrom = 0, dwRet = PTROBOT_OK, dwSysErr = SYSERR_NONE, dwWaitResult;
	int nUseRec = 0, nCopies, nRobot, i;
	TCHAR tszFile[MAX_PATH], tszDbg[256];
	PTRobotInfo myRobotInfo;
	BOOL fError = FALSE, fUseRec=FALSE, fUsePrinter = FALSE, fPrintFirst = FALSE;
	PTHREAD_INFO pThreadInfo;
	HANDLE hRobot, hDrive[4];
	int nIndex, nNumDrives, nRetries = 60;
	PTMediaInfo MediaInfo;
	WCHAR wszErrorString[MAX_STRING];

	pThreadInfo = (PTHREAD_INFO)lpVoid;

	// Get information about the  job...
	dwFrom = pThreadInfo->dwFrom;
	dwTo = pThreadInfo->dwTo;
	nNumDrives = (int)pThreadInfo->nNumDrives;
	for ( nIndex=0; nIndex< nNumDrives; nIndex++ )
    hDrive[nIndex] = pThreadInfo->hDrive[nIndex];
	hRobot = pThreadInfo->hRobot;
	nCopies = pThreadInfo->nCopies;
	nRobot = pThreadInfo->nRobot;
	fUseRec = pThreadInfo->fUseRecorders;
	fUsePrinter = pThreadInfo->fUsePrinter;
	fPrintFirst = pThreadInfo->fPrintFirst;
	_tcscpy(tszFile, pThreadInfo->tszPrintFile);

	dwRet = PTRobot_GetRobotInfo(hRobot, &myRobotInfo);
	if (dwRet != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetRobotInfo Error", MB_OK);
	}
	else
	{

		// Loop to Move the requested number of discs
		// (Version 1.1.8 - changed to be 1-based instead of 0-based because 1 means the first
		//  record in a SureThing file, whereas 0 will print all records if the SureThing file has merge records).
		for (i=1; i<= nCopies; i++)
		{
			dwWaitResult = WaitForSingleObject(g_hKillThreadEvent, 0);
			if (dwWaitResult == WAIT_OBJECT_0)
				break;

			nRetries = 10;
			_stprintf(g_szProgress[nRobot], _T("Job Progress:  %i of %i completed..."), i, nCopies);

			// Move through RECORDERS?
			if ((!fUseRec))
			{
				// NOT through RECORDERS
				// Move through PRINTER?
				if ( !fUsePrinter)
				{
					//Movements WITHOUT recorders or printing
					if (dwFrom == 0)
						dwFrom = 1;
					if (dwTo == 0)
						dwTo = 2;
					else if (dwTo == 3)
						dwTo = LOCATION_REJECT;

					dwRet = PTRobot_MoveDiscBetweenLocations(hRobot, dwFrom, dwTo);
					if (dwRet != PTROBOT_OK)
					{
						if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
							MyMessageBoxW( wszErrorString, L"PTRobot_MoveDiscBetweenLocations Error", MB_OK);
						fError = TRUE;
						break;
					}

					_tcscpy(g_szRobotStatus[nRobot], _T("Moving Disc"));
					//Version 1.0.5 The error is displayed in the WaitForCommand function
					if (PTROBOT_OK != WaitForCommand(hRobot))
					{
						fError = TRUE;
						break;
					}
				}	// if ( !fUsePrinter)

				else
				{
					//No Recorder but send through PRINTER.
					dwRet = PTRobot_LoadPrinter(hRobot, dwFrom);
					if (dwRet != PTROBOT_OK)
					{
						if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
							MyMessageBoxW( wszErrorString, L"PTRobot_LoadPrinter Error", MB_OK);
						fError = TRUE;
						break;
					}
					_tcscpy(g_szRobotStatus[nRobot], _T("Loading Printer"));
					//Version 1.0.5 The error is displayed in the WaitForCommand function
					if (PTROBOT_OK != WaitForCommand(hRobot))
					{
						fError = TRUE;
						break;
					}


					// Printer loaded --
					// Is there a FILE to PRINT?
					if (!fError && (_tcslen(tszFile) > 0))
					{
						// If we have no Merge text then we call the standard PTRobot_PrintFile
						// Note that i tells Surething what Merge record to use if a merge file was set
						if( !_tcslen(pThreadInfo->csMergeData1) &&  !_tcslen(pThreadInfo->csMergeData2) &&  !_tcslen(pThreadInfo->csMergeData3) &&  
								!_tcslen(pThreadInfo->csMergeData4) &&  !_tcslen(pThreadInfo->csMergeData5) )
							dwRet = PTRobot_PrintFile(hRobot, tszFile, i);

						// But if we have Merge Data then we call PrintFileWithMerge
						else					
						{						
							if (pThreadInfo->fMergeMethod2)
							{
								PTRobot_AddMergeFields( hRobot, pThreadInfo->csMergeData1 );
								PTRobot_AddMergeFields( hRobot, pThreadInfo->csMergeData2 );
								PTRobot_AddMergeFields( hRobot, pThreadInfo->csMergeData3 );
								PTRobot_AddMergeFields( hRobot, pThreadInfo->csMergeData4 );
								PTRobot_AddMergeFields( hRobot, pThreadInfo->csMergeData5 );
								dwRet = PTRobot_PrintFileWithMerge2( hRobot, tszFile, TRUE );
							}
							else
							{
								dwRet = PTRobot_PrintFileWithMerge( hRobot, tszFile, 5, pThreadInfo->csMergeData1,
													pThreadInfo->csMergeData2, pThreadInfo->csMergeData3, 
													pThreadInfo->csMergeData4, pThreadInfo->csMergeData5 );
							}
						}
						if (dwRet != PTROBOT_OK)
						{
							if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
								MyMessageBoxW( wszErrorString, L"PTRobot_PrintFile Error", MB_OK);
							fError = TRUE;
							break;
						}
						
						_tcscpy(g_szRobotStatus[nRobot], _T("Printing"));
						Sleep(5000);
						//Version 1.0.5 The error is displayed in the WaitForCommand function
						if (PTROBOT_OK != WaitForCommand(hRobot))
						{
							fError = TRUE;
							break;
						}
					}
					
					// DONE in Printer -- Unload DISC
					if (!fError)
					{
						if (dwTo == 3)
							dwTo = LOCATION_REJECT; 
						dwRet = PTRobot_UnLoadPrinter(hRobot, dwTo);
						if (dwRet != PTROBOT_OK)
						{
							if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
								MyMessageBoxW( wszErrorString, L"PTRobot_UnLoadPrinter Error", MB_OK);
							fError = TRUE;
							break;
						}
						_tcscpy(g_szRobotStatus[nRobot], _T("Unloading Printer"));
						//Version 1.0.5 The error is displayed in the WaitForCommand function
						if (PTROBOT_OK != WaitForCommand(hRobot))
						{
							fError = TRUE;
							break;
						}
					}
				}	// else Printer but No Recorder
			}	// if NOT sending through RECORDER(S)
			
			
			// else we want to move disc through the recorder(s)
			else 
			{
				// move discs through printert too?	
				if (!fUsePrinter)
				{
					// No - Recorder with no printing
					// clear the drive on first load (in case user left disc in drive)
					if ( i < nNumDrives )
						dwRet = PTRobot_LoadDrive(hRobot, hDrive[i%nNumDrives], dwFrom, TRUE);		
					// don't need to clear the disc on later rounds
					else				
						dwRet = PTRobot_LoadDrive(hRobot,hDrive[i%nNumDrives], dwFrom, FALSE);

					if (dwRet != PTROBOT_OK)
					{
						if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
							MyMessageBoxW( wszErrorString, L"PTRobot_LoadDrive Error", MB_OK);
						fError = TRUE;
						break;
					}

					_tcscpy(g_szRobotStatus[nRobot], _T("Loading Drive"));
					//Version 1.0.5 The error is displayed in the WaitForCommand function
					if (PTROBOT_OK != WaitForCommand(hRobot))
					{

						fError = TRUE;
						break;
					}

					Sleep(5000); //Added to ensure drive comes open

					nRetries=60;
					while(1)
					{
						dwRet = PTRobot_GetMediaInfo(hDrive[i%nNumDrives], &MediaInfo);
						if (dwRet == PTROBOT_OK)
							break;
						else if (dwRet != PTROBOT_DRIVE_NOT_READY)
						{
							if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage ))
								MyMessageBoxW( wszErrorString, L"PTRobot_GetMediaInfo Error", MB_OK);
							else
							{
								_stprintf(tszDbg, _T("Error getting Media Info (%lu)"), dwRet);
								MessageBox(NULL, tszDbg, _T("Error"), MB_OK);
							}
							fError = TRUE;
							break;
						}
						if (--nRetries<=0)
						{
							fError = TRUE;
							MessageBox(NULL, _T("Error: Timeout getting Media Info"),_T("Error"), MB_OK);
							break;
						}
						Sleep(500);
					}
					if (fError)
						break;

					if (!fError)
					{
						if (dwTo == 3)
							dwTo = LOCATION_REJECT; 
						dwRet = PTRobot_UnLoadDrive(hRobot,hDrive[i%nNumDrives],dwTo);
						if (dwRet != PTROBOT_OK)
						{
							if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
								MyMessageBoxW( wszErrorString, L"PTRobot_UnLoadDrive Error", MB_OK);
							fError = TRUE;
							break;
						}
						_tcscpy(g_szRobotStatus[nRobot], _T("Unloading Drive"));
						//Version 1.0.5 The error is displayed in the WaitForCommand function
						if (PTROBOT_OK != WaitForCommand(hRobot))
						{
							fError = TRUE;
							break;
						}

					}

				}	// if (!fUsePrinter)
				else
				{
					//Recorder with printing--
					// clear the drive on first disc (in case user left disc in drive)

					if (fPrintFirst)
					{
						dwRet = PTRobot_LoadPrinter(hRobot, dwFrom);
						if (dwRet != PTROBOT_OK)
						{
							if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
								MyMessageBoxW( wszErrorString, L"PTRobot_LoadPrinter Error", MB_OK);
							fError = TRUE;
							break;
						}
						//Version 1.0.5 The error is displayed in the WaitForCommand function
						if (PTROBOT_OK != WaitForCommand(hRobot))
						{
							fError = TRUE;
							break;
						}

					}
					else
					{
						if ( i < nNumDrives )
							dwRet = PTRobot_LoadDrive(hRobot, hDrive[i%nNumDrives], dwFrom, TRUE);		
						// don't need to clear the disc on later rounds
						else				
							dwRet = PTRobot_LoadDrive(hRobot, hDrive[i%nNumDrives], dwFrom, FALSE);

						if (dwRet != PTROBOT_OK)
						{
							if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
								MyMessageBoxW( wszErrorString, L"PTRobot_LoadDrive Error", MB_OK);
							fError = TRUE;
							break;
						}

						_tcscpy(g_szRobotStatus[nRobot], _T("Loading Drive"));

						//Version 1.0.5 The error is displayed in the WaitForCommand function
						if (PTROBOT_OK != WaitForCommand(hRobot))
						{
							fError = TRUE;
							break;
						}

						Sleep(5000); //Added to ensure drive comes open
						nRetries=60;
						while(1)
						{
							dwRet = PTRobot_GetMediaInfo(hDrive[i%nNumDrives], &MediaInfo);
							if (dwRet == PTROBOT_OK)
								break;
							else if (dwRet != PTROBOT_DRIVE_NOT_READY)
							{
								if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage ))
									MyMessageBoxW( wszErrorString, L"PTRobot_GetMediaInfo Error", MB_OK);
								else
								{
									_stprintf(tszDbg, _T("Error getting Media Info (%lu)"), dwRet);
									MessageBox(NULL, tszDbg, _T("Error"), MB_OK);
								}
								fError = TRUE;
								break;
							}
							if (--nRetries<=0)
							{
								fError = TRUE;
								MessageBox(NULL, _T("Error: Timeout getting Media Info"), _T("Error"), MB_OK);
								break;
							}
							Sleep(500);
						}
						if (fError)
							break;

						if (!fError)
						{
							dwRet = PTRobot_LoadPrinterFromDrive(hRobot ,hDrive[i%nNumDrives]);
							if (dwRet != PTROBOT_OK)
							{
								if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
									MyMessageBoxW( wszErrorString, L"PTRobot_LoadPrinterFromDrive Error", MB_OK);
								fError = TRUE;
								break;
							}

							_tcscpy(g_szRobotStatus[nRobot], _T("Loading Printer from Drive"));
							//Version 1.0.5 The error is displayed in the WaitForCommand function
							if (PTROBOT_OK != WaitForCommand(hRobot))
							{
								fError = TRUE;
								break;
							}

						}
					}
					if (!fError && (_tcslen(tszFile) > 0))
					{
						// If we have no Merge text then we call the standard PTRobot_PrintFile
						// Note that i tells Surething what Merge record to use if a merge file was set
						if( !_tcslen(pThreadInfo->csMergeData1) &&  !_tcslen(pThreadInfo->csMergeData2) &&  !_tcslen(pThreadInfo->csMergeData3) &&  
								!_tcslen(pThreadInfo->csMergeData4) &&  !_tcslen(pThreadInfo->csMergeData5) )
							dwRet = PTRobot_PrintFile(hRobot, tszFile, i);

						// But if we have Merge Data then we call PrintFileWithMerge
						else					
							dwRet = PTRobot_PrintFileWithMerge( hRobot, tszFile, 5, pThreadInfo->csMergeData1,
													pThreadInfo->csMergeData2, pThreadInfo->csMergeData3, 
													pThreadInfo->csMergeData4, pThreadInfo->csMergeData5 );

						if (dwRet != PTROBOT_OK)
						{
							if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
								MyMessageBoxW( wszErrorString, L"PTRobot_PrintFile Error", MB_OK);
							fError = TRUE;
							break;
						}

						_tcscpy(g_szRobotStatus[nRobot], _T("Printing"));
						Sleep(5000);
						//Version 1.0.5 The error is displayed in the WaitForCommand function
						if (PTROBOT_OK != WaitForCommand(hRobot))
						{
							fError = TRUE;
							break;
						}

					}
					if (!fError)
					{
						if (fPrintFirst)
						{		
							if ( i < nNumDrives )
								dwRet = PTRobot_LoadDrive(hRobot, hDrive[i%nNumDrives], LOCATION_PRINTER, TRUE);		
							// don't need to clear the disc on later rounds
							else				
								dwRet = PTRobot_LoadDrive(hRobot, hDrive[i%nNumDrives], LOCATION_PRINTER, FALSE);	

							if (dwRet != PTROBOT_OK)
							{
								if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
									MyMessageBoxW( wszErrorString, L"PTRobot_LoadDrive Error", MB_OK);
								fError = TRUE;
								break;
							}
							_tcscpy(g_szRobotStatus[nRobot], _T("Loading Drive from Printer"));

							//Version 1.0.5 The error is displayed in the WaitForCommand function
							if (PTROBOT_OK != WaitForCommand(hRobot))
							{
								fError = TRUE;
								break;
							}

							Sleep(5000); //Added to ensure drive comes open

							nRetries = 60;
							while(1)
							{
								dwRet = PTRobot_GetMediaInfo(hDrive[i%nNumDrives], &MediaInfo);
								if (dwRet == PTROBOT_OK)
									break;
								else if (dwRet != PTROBOT_DRIVE_NOT_READY)
								{
									if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage ))
										MyMessageBoxW( wszErrorString, L"PTRobot_GetMediaInfo Error", MB_OK);
									else
									{
										_stprintf(tszDbg, _T("Error getting Media Info (%lu)"), dwRet);
										MessageBox(NULL, tszDbg, _T("Error"), MB_OK);
									}
									fError = TRUE;
									break;
								}
								if (--nRetries<=0)
								{
									fError = TRUE;
									MessageBox(NULL, _T("Error: Timeout getting Media Info"), _T("Error"), MB_OK);
									break;
								}
								Sleep(500);
							}
							if (fError)
								break;

							if (dwTo == 3)
								dwTo = LOCATION_REJECT; 
							dwRet = PTRobot_UnLoadDrive(hRobot,hDrive[i%nNumDrives], dwTo);
							if (dwRet != PTROBOT_OK)
							{
								if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
									MyMessageBoxW( wszErrorString, L"PTRobot_UnLoadDrive Error", MB_OK);
								fError = TRUE;
								break;
							}

							_tcscpy(g_szRobotStatus[nRobot], _T("Unloading Drive"));
							//Version 1.0.5 The error is displayed in the WaitForCommand function
							if (PTROBOT_OK != WaitForCommand(hRobot))
							{
								fError = TRUE;
								break;
							}

						}
						else
						{
							if (dwTo == 3)
								dwTo = LOCATION_REJECT; 
							dwRet = PTRobot_UnLoadPrinter(hRobot, dwTo);
							if (dwRet != PTROBOT_OK)
							{
								if (PTROBOT_OK == PTRobot_GetErrorString(hRobot, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
									MyMessageBoxW( wszErrorString, L"PTRobot_UnLoadPrinter Error", MB_OK);
								fError = TRUE;
								break;
							}

							_tcscpy(g_szRobotStatus[nRobot], _T("Unloading Printer"));
							//Version 1.0.5 The error is displayed in the WaitForCommand function
							if (PTROBOT_OK != WaitForCommand(hRobot))
							{
								fError = TRUE;
								break;
							}
						}
					}
				}	// else Recorder with Printing
			}	// else moving discs through recorder(s)
		}	// for (i=0; i< nCopies; i++)
	}

	// Make sure the drive(s) are closed after the jobs is completed
	for ( i=0; i<nNumDrives; i++ )
		PTRobot_OpenCloseDrive(hDrive[i], DRIVE_CLOSE);
	
	_tcscpy(g_szRobotStatus[nRobot], _T("Idle"));
	_tcscpy(g_szProgress[nRobot], _T(""));
	g_fRobotRunning[nRobot] = FALSE;
	return 1;
}



// ******************************************************************************** //
BOOL CPTRobotAppDlg::UpdateRobotInfo()
{
	int nRobot;
	PTRobotInfo myRobotInfo;
	PTRobotStatus myRobotStatus;
	PTRobotStatus2 myRobotStatus2;
	PTDriveInfo myDriveInfo;
	TCHAR tszDbg[256];
	WCHAR wszErrorString[MAX_STRING];
	DWORD dwRet, dwDrv;

	nRobot = this->m_RobotCombo.GetCurSel();
	if( nRobot < 0 )
		nRobot = 0;

	dwRet = PTRobot_GetRobotInfo(this->m_hRobots[nRobot], &myRobotInfo);
	if (dwRet == PTROBOT_OK)
	{
		_stprintf(tszDbg, _T("%lu"), myRobotInfo.dwNumBins);
		this->m_NumBinsStatic.SetWindowText(tszDbg);
		_stprintf(tszDbg, _T("%lu"), myRobotInfo.dwNumDrives);
		this->m_NumDrivesStatic.SetWindowText(tszDbg);
		
		if (myRobotInfo.dwNumPrinters > 0)
			this->m_PrinterStatic.SetWindowText(_T("Installed"));
		else
			this->m_PrinterStatic.SetWindowText(_T("Not Installed"));

		if (myRobotInfo.dwRobotType == ROBOT_DISCPUBLISHER)
			this->m_RobotTypeStatic.SetWindowText(_T("Disc Publisher"));
		else if (myRobotInfo.dwRobotType == ROBOT_DISCPUBLISHERII)
			this->m_RobotTypeStatic.SetWindowText(_T("Disc Publisher II"));
		else if (myRobotInfo.dwRobotType == ROBOT_DISCPUBLISHERPRO)
			this->m_RobotTypeStatic.SetWindowText(_T("Disc Publisher PRO"));
		else if (myRobotInfo.dwRobotType == ROBOT_COMPOSERMAX)
			this->m_RobotTypeStatic.SetWindowText(_T("Composer MAX"));
		//Version 1.05 Added support for rackmount bravoII
		else if (myRobotInfo.dwRobotType == ROBOT_RACKMOUNT_DPII)
			this->m_RobotTypeStatic.SetWindowText(_T("Disc Publisher XR"));
		else if (myRobotInfo.dwRobotType == ROBOT_DISCPUBLISHER_XRP)
			this->m_RobotTypeStatic.SetWindowText(_T("Disc Publisher XRP"));
		else if (myRobotInfo.dwRobotType == ROBOT_DISCPUBLISHER_4100)
			this->m_RobotTypeStatic.SetWindowText(_T("Disc Publisher 4100"));
		else if (myRobotInfo.dwRobotType == ROBOT_DISCPUBLISHER_4100_XRP)
			this->m_RobotTypeStatic.SetWindowText(_T("Disc Publisher 4100 XRP"));
		else if (myRobotInfo.dwRobotType == ROBOT_DISCPUBLISHER_4051)
			this->m_RobotTypeStatic.SetWindowText(_T("Disc Publisher 4051"));
		else
			this->m_RobotTypeStatic.SetWindowText(_T("Unknown"));

		this->m_DriveList.ResetContent();
		for (dwDrv=0; dwDrv<myRobotInfo.dwNumDrives; dwDrv++)
		{
			if ( PTROBOT_OK == PTRobot_GetDriveInfo(myRobotInfo.hDrives[dwDrv], &myDriveInfo) )
				_stprintf(tszDbg, _T("%s (%u, %u)"), myDriveInfo.tszDriveName, myDriveInfo.dwDriveColumn, myDriveInfo.dwDriveRow);
			else
				_stprintf(tszDbg, _T("- Invalid drive -") );
			this->m_DriveList.InsertString(dwDrv,tszDbg); 
		}


		//Version 1.08  We added the available system actions to the UI.  This allows us to easily test and
		//              demonstrate these actions.
		this->m_nActions=0;
		this->m_SysActionCombo.ResetContent();

		if (myRobotInfo.dwSupportedActions & PTACT_CLEANCARTRIDGES)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Clean Cartridge(s)"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_CLEANCARTRIDGES;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_ALIGNPRINTER)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Align Printer"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_ALIGNPRINTER;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_REINIT_DRIVES)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Re-init Drives"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_REINIT_DRIVES;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_IGNOREINKLOW)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Ignore Ink Low"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_IGNOREINKLOW;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_DISABLEPWRBUTTON)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Disable Power Button"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_DISABLEPWRBUTTON;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_IDENTIFY)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Id Robot"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_IDENTIFY;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_CANCELCMD)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Cancel Command"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_CANCELCMD;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_ENABLEPWRBUTTON)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Enable Power Button"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_ENABLEPWRBUTTON;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_RESETSYSTEM)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Reset System"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_RESETSYSTEM;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_CHECKDISCS)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Check Discs"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_CHECKDISCS;
			this->m_nActions++;
		}

		if (myRobotInfo.dwSupportedActions & PTACT_CALIBRATE_ONE_DISC)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("One Disc Calibration"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_CALIBRATE_ONE_DISC;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_CHANGE_CARTRIDGE)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Change Cartridge"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_CHANGE_CARTRIDGE;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_END_CARTRIDGE_CHANGE)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("End Cartridge Change"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_END_CARTRIDGE_CHANGE;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_SHIP_POSITION)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Move to Ship Position"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_SHIP_POSITION;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_RESET_LEFT_INK_LEVELS)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Reset LEFT Ink Levels"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_RESET_LEFT_INK_LEVELS;
			this->m_nActions++;
		}
		if (myRobotInfo.dwSupportedActions & PTACT_RESET_RIGHT_INK_LEVELS)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Reset RIGHT Ink Levels"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_RESET_RIGHT_INK_LEVELS;
			this->m_nActions++;
		}

		if (myRobotInfo.dwSupportedActions & PTACT_ALLOW_NO_CARTRIDGES)
		{
			this->m_SysActionCombo.InsertString(this->m_nActions, _T("Allow no Cartridge Robotics"));
			this->m_dwActionCombo[this->m_nActions] = PTACT_ALLOW_NO_CARTRIDGES;
			this->m_nActions++;
		}
		

		this->m_SysActionCombo.SetCurSel(0);
	
		// DEBUGGING
		dwRet = PTRobot_GetRobotStatus(this->m_hRobots[nRobot], &myRobotStatus);
		dwRet = PTRobot_GetRobotStatus2(this->m_hRobots[nRobot], &myRobotStatus2);

	}
	else	
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRet, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetRobotInfo Error", MB_OK);

		return FALSE;
	}
	return TRUE;
}


// ******************************************************************************** //
BOOL CPTRobotAppDlg::EnumRobots()
{
	HANDLE hRobots[10], hDrives[MAX_ROBOT_DRIVES];
	DWORD dwDrives=MAX_ROBOT_DRIVES, dwIndex=0, dwRet=0, dwDrv=0, dwRobots=10;
	TCHAR tszDbg[256];
	WCHAR wszErrorString[MAX_STRING];
	PTRobotInfo myRobotInfo;
	DWORD dwRetVal = PTROBOT_OK, i;
	CSelectRoboticDrives selectDrives;


	//Reset all internal robot info.
	this->m_RobotCombo.ResetContent();
	this->m_DriveList.ResetContent();
	this->m_nRobots = 0;

	/////////////////////////////////////////////////////
	// Have PTRobot enumerate the robots
	/////////////////////////////////////////////////////
	dwRet = PTRobot_EnumRobots(hRobots, &dwRobots);
	
	if (dwRet != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(0x00000000, dwRet, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_EnumRobots Error", MB_OK);
		else
		{
			_stprintf(tszDbg, _T("Unable to enumerate robots.\nError 0x%.8x"), dwRet);
			MessageBox(tszDbg, _T("Error"), MB_OK);
		}
		return FALSE;
	}
	else
	{
		// We may have multiple robots - check each one
		for(dwIndex=0; dwIndex<dwRobots; dwIndex++)
		{
			if( PTROBOT_OK == PTRobot_GetRobotInfo(hRobots[dwIndex], &myRobotInfo))
			{

				///////////////////////////////////////////
				//
				//	Enumerate the drives
				//
				///////////////////////////////////////////
				dwRet = PTRobot_EnumDrives(hRobots[dwIndex], hDrives, &dwDrives);

				// Did we enumerate the drives properly?
				if (dwRet == PTROBOT_OK)
				{
					// Yes, resolved drive(s) -- save robot information
					this->m_RobotCombo.InsertString(this->m_nRobots, myRobotInfo.tszRobotDesc);
					this->m_hRobots[this->m_nRobots]= hRobots[dwIndex];
					g_fRobotRunning[this->m_nRobots] = FALSE;
					_tcscpy(g_szRobotStatus[this->m_nRobots], _T("Idle"));
					this->m_nRobots++;
				}

				// Or was PTRobot unable to enumerate the drives because
				// it had too many drives to resolve which one(s) were robotically controlled?
				else if (dwRet == PTROBOT_MULTDRIVES)
				{
					// Too many drives to resolve --
					// We must have the user help us resolve which drive(s) are robotically controlled
					selectDrives.hRobot = hRobots[dwIndex];
					selectDrives.dwDrives = dwDrives;
					selectDrives.dwRobotType = myRobotInfo.dwRobotType;

					for (i=0; i<dwDrives;i++)
					{
						selectDrives.hDrives[i] = hDrives[i];
					}

					selectDrives.DoModal();
					if (selectDrives.nDrivesSet == myRobotInfo.dwNumDrives)
					{				
						this->m_RobotCombo.InsertString(this->m_nRobots, myRobotInfo.tszRobotDesc);
						this->m_hRobots[this->m_nRobots]= hRobots[dwIndex];
						g_fRobotRunning[this->m_nRobots] = FALSE;
						_tcscpy(g_szRobotStatus[this->m_nRobots], _T("Idle"));
						this->m_nRobots++;
					}
				}
			}
		}
	}


	return TRUE;
}

// ******************************************************************************** //
void CPTRobotAppDlg::OnCbnSelchangeRobotCombo()
{
	this->UpdateRobotInfo();
}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedDriveinfoBtn()
{
	TCHAR tszInfo[500];
	int nDrive=0, nRobot=0;
	PTDriveInfo myDriveInfo;
	PTRobotInfo myRobotInfo;
	PTMediaInfo myMediaInfo;
	WCHAR wszErrorString[MAX_STRING];
	DWORD dwRetVal = PTROBOT_OK;

	nDrive = this->m_DriveList.GetCurSel();
	nRobot = this->m_RobotCombo.GetCurSel();

	dwRetVal = PTRobot_GetRobotInfo(this->m_hRobots[nRobot], &myRobotInfo);
	if (dwRetVal != PTROBOT_OK)	
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetRobotInfo Error", MB_OK);
		return;
	}

	dwRetVal = PTRobot_GetDriveInfo(myRobotInfo.hDrives[nDrive], &myDriveInfo);
	if (dwRetVal != PTROBOT_OK)	
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetDriveInfo Error", MB_OK);
		return;
	}
	dwRetVal = PTRobot_GetMediaInfo(myRobotInfo.hDrives[nDrive], &myMediaInfo);
	if (dwRetVal == PTROBOT_OK)
	{
		_stprintf(tszInfo, _T("Name: %s\nHandle: 0x%.8x\nFW Ver: %s\nSerial: %s\n(Col, Row): (%lu,%lu)\nMedia Type: %s\nMediaID: %s"), 
			myDriveInfo.tszDriveName, (DWORD)myDriveInfo.hDrive, myDriveInfo.tszFirmwareVer, myDriveInfo.tszSerialNum, 
			myDriveInfo.dwDriveColumn, myDriveInfo.dwDriveRow, myMediaInfo.tszMediaType, myMediaInfo.tszMediaID);
	}
	else if (dwRetVal == PTROBOT_NO_MEDIA)
	{
		_stprintf(tszInfo, _T("Name: %s\nHandle: 0x%.8x\nFW Ver: %s\nSerial: %s\n(Col, Row): (%lu,%lu)\nNo Media present"), 
			myDriveInfo.tszDriveName, (DWORD)myDriveInfo.hDrive, myDriveInfo.tszFirmwareVer, myDriveInfo.tszSerialNum, myDriveInfo.dwDriveColumn, myDriveInfo.dwDriveRow);
	}
	else if (dwRetVal == PTROBOT_INVALID_MEDIA)
	{
		_stprintf(tszInfo, _T("Name: %s\nHandle: 0x%.8x\nFW Ver: %s\nSerial: %s\n(Col, Row): (%lu,%lu)\n\nINVALID MEDIA\n\nMedia Type: %s\nMediaID: %s"), 
			myDriveInfo.tszDriveName, (DWORD)myDriveInfo.hDrive, myDriveInfo.tszFirmwareVer, myDriveInfo.tszSerialNum, 
			myDriveInfo.dwDriveColumn, myDriveInfo.dwDriveRow, myMediaInfo.tszMediaType, myMediaInfo.tszMediaID);
	}
	else
	{
		_stprintf(tszInfo, _T("Name: %s\nHandle: 0x%.8x\nFW Ver: %s\nSerial: %s\n(Col, Row): (%lu,%lu)"), 
			myDriveInfo.tszDriveName, (DWORD)myDriveInfo.hDrive, myDriveInfo.tszFirmwareVer, myDriveInfo.tszSerialNum, myDriveInfo.dwDriveColumn, myDriveInfo.dwDriveRow);
	}

	MessageBox(tszInfo, _T("Drive Info"), MB_OK);
}

// ******************************************************************************** //
void CPTRobotAppDlg::OnClose()
{
	int nRobot;
	SetEvent(g_hKillThreadEvent);
	nRobot = this->m_RobotCombo.GetCurSel();

	while(1)
	{
		if (!g_fRobotRunning[nRobot])
			break;
		Sleep(1000);
	}
	
	PTRobot_Destroy();
	CDialog::OnClose();
}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedKillerrorBtn()
{
	int nRobot=0;
	DWORD dwRetVal = PTROBOT_OK;
	WCHAR wszErrorString[MAX_STRING];

	nRobot = this->m_RobotCombo.GetCurSel();
	dwRetVal = PTRobot_KillSystemError(this->m_hRobots[nRobot], FALSE);
	if (dwRetVal != PTROBOT_OK)	
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_KillSystemError Error", MB_OK);
		return;
	}
}



// ******************************************************************************** //
void CPTRobotAppDlg::OnTimer(UINT nIDEvent)
{
	int nRobot = this->m_RobotCombo.GetCurSel();

	this->m_RobotStatus.SetWindowText(g_szRobotStatus[nRobot]);
	this->m_JobProgress.SetWindowText(g_szProgress[nRobot]);

	if (g_fRobotRunning[nRobot])
		this->m_GoBtn.EnableWindow(FALSE);
	else
		this->m_GoBtn.EnableWindow(TRUE);

	CDialog::OnTimer(nIDEvent);
}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedKioskmodeChk()
{
	DWORD dwOptionsToSet=0, dwRetVal = PTROBOT_OK;
	int nRobot=0;
	WCHAR wszErrorString[MAX_STRING];
	
	nRobot = this->m_RobotCombo.GetCurSel();

	dwRetVal = PTRobot_GetRobotOptions(this->m_hRobots[nRobot], &dwOptionsToSet);
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetRobotOptions Error", MB_OK);
	}
	else
	{
		if (this->m_KioskModeChk.GetCheck() == 1)
		{
			dwOptionsToSet = dwOptionsToSet | PTOPT_KIOSKMODE;
			dwRetVal = PTRobot_SetRobotOptions(this->m_hRobots[nRobot], dwOptionsToSet );
			if (dwRetVal != PTROBOT_OK)
			{
				if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
					MyMessageBoxW( wszErrorString, L"PTRobot_SetRobotOptions Error", MB_OK);
			}
		}
		else
		{
			//Turn Kiosk Mode Off
			dwOptionsToSet = dwOptionsToSet & !(PTOPT_KIOSKMODE);	
			dwRetVal = PTRobot_SetRobotOptions(this->m_hRobots[nRobot], dwOptionsToSet );
			if (dwRetVal != PTROBOT_OK)
			{
				if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
					MyMessageBoxW( wszErrorString, L"PTRobot_SetRobotOptions Error", MB_OK);
			}
		}
	}
}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedThroghPtrChk()
{
	TCHAR tszBuf[MAX_PATH];
	INT nLen;

	if (this->m_ThroughPrinterChk.GetCheck() == 1)
	{
		this->m_PrintFileEdit.EnableWindow(TRUE);
		this->m_PrintBrowseBtn.EnableWindow(TRUE);
		this->m_PrintFileStatic.EnableWindow(TRUE);
		this->m_SetPrinterSettings.EnableWindow(TRUE);
		this->m_GetPrinterSettings.EnableWindow(TRUE);

		// Enable the Merge text button only if user has selected a Surething .STD file
		this->m_PrintFileEdit.GetWindowText( tszBuf, MAX_PATH );
		nLen = (INT)_tcslen( tszBuf );
		if( nLen > 4 )
		{
			if( !_tcsicmp( &tszBuf[nLen-4], _T(".STD" )) )
				this->m_SetMergeBtn.EnableWindow(TRUE);				
		}
		if (this->m_ThroughRecChk.GetCheck() == 1)
			this->m_PrintFirstChk.EnableWindow(TRUE);
		else
			this->m_PrintFirstChk.EnableWindow(FALSE);


	}
	else
	{
		this->m_PrintFileEdit.EnableWindow(FALSE);
		this->m_PrintBrowseBtn.EnableWindow(FALSE);
		this->m_PrintFileStatic.EnableWindow(FALSE);
		this->m_SetPrinterSettings.EnableWindow(FALSE);
		this->m_GetPrinterSettings.EnableWindow(FALSE);
		this->m_SetMergeBtn.EnableWindow(FALSE);
		this->m_PrintFirstChk.EnableWindow(FALSE);
	}
}


// ******************************************************************************** //
void CPTRobotAppDlg::OnCbnSelchangeFromCombo()
{
	int nTo= 0, nFrom = 0, nRobot=0;
	DWORD dwOptionsToSet=0, dwRetVal = PTROBOT_OK;
	WCHAR wszErrorString[MAX_STRING];
	
	nRobot = this->m_RobotCombo.GetCurSel();

	nFrom = this->m_FromCombo.GetCurSel();
	nTo = this->m_ToCombo.GetCurSel();
	if ((nFrom == 0) && (nTo == 0))
		this->m_KioskModeChk.EnableWindow(TRUE);
	else 
		this->m_KioskModeChk.EnableWindow(FALSE);


	// Cannot have Kiosk selected unless From/To is set to Auto
	if( nFrom != 0 )
	{
		if (this->m_KioskModeChk.GetCheck() == 1)
		{
			MessageBox(_T("Kiosk Mode is only valid when the From and To locations are set to Auto"), _T("Note"), MB_OK);
			this->m_KioskModeChk.SetCheck( 0 );
			dwOptionsToSet = dwOptionsToSet & ~PTOPT_KIOSKMODE;
			dwRetVal = PTRobot_SetRobotOptions(this->m_hRobots[nRobot], dwOptionsToSet );
			if (dwRetVal != PTROBOT_OK)
			{
				if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
					MyMessageBoxW( wszErrorString, L"PTRobot_SetRobotOptions Error", MB_OK);
			}
		}
	}


}


// ******************************************************************************** //
void CPTRobotAppDlg::OnCbnSelchangeToCombo()
{
	int nTo= 0, nFrom = 0, nRobot = 0;
	DWORD dwOptionsToSet=0, dwRetVal = PTROBOT_OK;
	WCHAR wszErrorString[MAX_STRING];

	nRobot = this->m_RobotCombo.GetCurSel();

	nFrom = this->m_FromCombo.GetCurSel();
	nTo = this->m_ToCombo.GetCurSel();
	if ((nFrom == 0) && (nTo == 0))
		this->m_KioskModeChk.EnableWindow(TRUE);
	else 
		this->m_KioskModeChk.EnableWindow(FALSE);


	// Cannot have Kiosk selected unless From/To is set to Auto
	if( nTo != 0 )
	{
		if (this->m_KioskModeChk.GetCheck() == 1)
		{
			MessageBox(_T("Kiosk Mode is only valid when the From and To locations are set to Auto"), _T("Note"), MB_OK);
			this->m_KioskModeChk.SetCheck( 0 );
			dwOptionsToSet = dwOptionsToSet & ~PTOPT_KIOSKMODE;
			dwRetVal = PTRobot_SetRobotOptions(this->m_hRobots[nRobot], dwOptionsToSet );
			if (dwRetVal != PTROBOT_OK)
			{
				if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
					MyMessageBoxW( wszErrorString, L"PTRobot_SetRobotOptions Error", MB_OK);
			}
		}
	}

}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedGetPtrsettings()
{
	int nRobot = 0;
	PTPrinterSettings myPtrSettings;
	TCHAR tszMsg[256];
	PTRobotInfo myRobotInfo;
	DWORD dwRetVal = PTROBOT_OK;
	WCHAR wszErrorString[MAX_STRING];
	
	nRobot = this->m_RobotCombo.GetCurSel();
	
	dwRetVal = PTRobot_GetRobotInfo(this->m_hRobots[nRobot], &myRobotInfo);
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetRobotInfo Error", MB_OK);
	}

	dwRetVal = PTRobot_GetPrinterSettings(this->m_hRobots[nRobot], &myPtrSettings);
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetPrinterSettings Error", MB_OK);
	}
	else
	{
		_stprintf(tszMsg, _T("Quality: %i\nOuter Margin: %i\nInner Diameter: %i"), myPtrSettings.dwPrintQuality, myPtrSettings.dwOuterMargin, myPtrSettings.dwInnerDiam);
		MessageBox(tszMsg, myRobotInfo.tszRobotDesc, MB_OK);
	}
}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedSetPtrsettings()
{
	CSetPrinterSettings CPtrSettings;
	int nRobot = 0;

	nRobot = this->m_RobotCombo.GetCurSel();

	CPtrSettings.m_hRobot = this->m_hRobots[nRobot];
	CPtrSettings.DoModal();

}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedOpenClose()
{
	int nDrive=0, nRobot=0;
	PTRobotInfo myRobotInfo;
	DWORD dwRetVal = PTROBOT_OK;
	WCHAR wszErrorString[MAX_STRING];

	// Get the Robot & Drive selected - default to 0 element if none selected
	nDrive = this->m_DriveList.GetCurSel();
	if (nDrive < 0)
		nDrive = 0;
	nRobot = this->m_RobotCombo.GetCurSel();
	if (nRobot < 0)
		nRobot = 0;

	// Get the robot info
	dwRetVal = PTRobot_GetRobotInfo(this->m_hRobots[nRobot], &myRobotInfo);
	if (dwRetVal != PTROBOT_OK)	
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_GetRobotInfo Error", MB_OK);
		return;
	}

	// If successful above we can open/close the selected drive
	this->m_DriveOpenCloseBtn.EnableWindow(FALSE);
	dwRetVal = PTRobot_OpenCloseDrive(myRobotInfo.hDrives[nDrive], DRIVE_OPEN);
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_OpenCloseDrive Error", MB_OK);
	}
	Sleep(1000);
	dwRetVal = PTRobot_OpenCloseDrive(myRobotInfo.hDrives[nDrive], DRIVE_CLOSE);
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(this->m_hRobots[nRobot], dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_OpenCloseDrive Error", MB_OK);
	}
	this->m_DriveOpenCloseBtn.EnableWindow(TRUE);

}


// ******************************************************************************** //
void CPTRobotAppDlg::OnBnClickedSetMerge()
{
	CSetMergeData CMergeData;
	
	// init the data to the previous strings...
	CMergeData.m_csMergeData1 = this->m_csMergeData1;
	CMergeData.m_csMergeData2 = this->m_csMergeData2;
	CMergeData.m_csMergeData3 = this->m_csMergeData3;
	CMergeData.m_csMergeData4 = this->m_csMergeData4;
	CMergeData.m_csMergeData5 = this->m_csMergeData5;
	CMergeData.m_fMergeMethod2 = this->m_fMergeMethod2;

	
	// Copy over the Merge data from the Edit fields - IF users clicks OK
	// NOTE: nothing magic about 5 fields (we could have chosen more or less).
	// The important thing is the number of text fields entered must match the number of 
	// Merge fields within the Surething file.
	if (CMergeData.DoModal() == IDOK)
	{
		this->m_csMergeData1 = CMergeData.m_csMergeData1;
		this->m_csMergeData2 = CMergeData.m_csMergeData2;
		this->m_csMergeData3 = CMergeData.m_csMergeData3;
		this->m_csMergeData4 = CMergeData.m_csMergeData4;
		this->m_csMergeData5 = CMergeData.m_csMergeData5;
		this->m_fMergeMethod2 = CMergeData.m_fMergeMethod2;
	}
	
}

void CPTRobotAppDlg::OnBnClickedEnumDrives()
{
	int nRobot;
	HANDLE hRobot, hDrives[MAX_ROBOT_DRIVES];
	DWORD dwDrives=MAX_ROBOT_DRIVES, dwRetVal = PTROBOT_OK; 
	WCHAR wszErrorString[MAX_STRING];
	
	nRobot = this->m_RobotCombo.GetCurSel();

	hRobot = this->m_hRobots[nRobot];
	
	dwRetVal = PTRobot_EnumDrives(hRobot, hDrives, &dwDrives);
	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(hRobot,  dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_EnumDrives Error", MB_OK);
	}

	UpdateRobotInfo();

}

void CPTRobotAppDlg::OnBnClickedPrintFirstChk()
{
	// TODO: Add your control notification handler code here
}

void CPTRobotAppDlg::OnBnClickedThroughRecChk()
{
	if ((this->m_ThroughRecChk.GetCheck() == 1) &&
		(this->m_ThroughPrinterChk.GetCheck() == 1))
		this->m_PrintFirstChk.EnableWindow(TRUE);
	else
		this->m_PrintFirstChk.EnableWindow(FALSE);
}

void CPTRobotAppDlg::OnCbnSelchangeLangCombo()
{
	g_nLanguage = this->m_LangCombo.GetCurSel();
}

void CPTRobotAppDlg::OnBnClickedSystemAction()
{
	int nRobot;
	HANDLE hRobot;
	DWORD dwRetVal=PTROBOT_OK, dwAction = 0;
	PTRobotStatus RobotStatus;
	CWaitCursor wait;

	WCHAR wszErrorString[MAX_STRING];
	
	nRobot = this->m_RobotCombo.GetCurSel();

	hRobot = this->m_hRobots[nRobot];

	dwAction = this->m_dwActionCombo[this->m_SysActionCombo.GetCurSel()];

	
	dwRetVal = PTRobot_SystemAction(hRobot ,dwAction );

	if (dwRetVal != PTROBOT_OK)
	{
		if (PTROBOT_OK == PTRobot_GetErrorString(hRobot,  dwRetVal, wszErrorString, MAX_STRING, g_nLanguage))
			MyMessageBoxW( wszErrorString, L"PTRobot_EnumDrives Error", MB_OK);
	}

	do {
		Sleep(500);
		PTRobot_GetRobotStatus( hRobot, &RobotStatus );
	} while( RobotStatus.dwSystemState == SYSSTATE_BUSY );
	MessageBox( _T("Action Completed"), _T(""), MB_OK );

}


DWORD MyMessageBoxW( WCHAR * wszText, WCHAR * wszCaption, UINT nType )
{
	DWORD dwReturn = 0;	
	#ifdef UNICODE
		dwReturn = MessageBox(NULL, wszText, wszCaption, nType);
	#else
		dwReturn = MessageBoxW(NULL, wszText, wszCaption, nType);
	#endif

	return (dwReturn);
}


