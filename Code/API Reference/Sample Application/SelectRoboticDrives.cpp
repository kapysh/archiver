// SelectRoboticDrives.cpp : implementation file
//

#include "stdafx.h"
#include "PTRobotApp.h"
#include "SelectRoboticDrives.h"
#include ".\selectroboticdrives.h"
#include "..\PTRobot.h"


// CSelectRoboticDrives dialog

IMPLEMENT_DYNAMIC(CSelectRoboticDrives, CDialog)
CSelectRoboticDrives::CSelectRoboticDrives(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectRoboticDrives::IDD, pParent)
{
}

CSelectRoboticDrives::~CSelectRoboticDrives()
{
}

void CSelectRoboticDrives::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRIVE_DESC1, m_DriveDesc[0]);
	DDX_Control(pDX, IDC_DRIVE_DESC2, m_DriveDesc[1]);
	DDX_Control(pDX, IDC_DRIVE_DESC3, m_DriveDesc[2]);
	DDX_Control(pDX, IDC_DRIVE_DESC4, m_DriveDesc[3]);
	DDX_Control(pDX, IDC_DRIVE_DESC5, m_DriveDesc[4]);
	DDX_Control(pDX, IDC_DRIVE_COMBO1, m_DriveLocation[0]);
	DDX_Control(pDX, IDC_DRIVE_COMBO2, m_DriveLocation[1]);
	DDX_Control(pDX, IDC_DRIVE_COMBO3, m_DriveLocation[2]);
	DDX_Control(pDX, IDC_DRIVE_COMBO4, m_DriveLocation[3]);
	DDX_Control(pDX, IDC_DRIVE_COMBO5, m_DriveLocation[4]);
	DDX_Control(pDX, IDC_OPENCLOSE1, m_OpenClose[0]);
	DDX_Control(pDX, IDC_OPENCLOSE2, m_OpenClose[1]);
	DDX_Control(pDX, IDC_OPENCLOSE3, m_OpenClose[2]);
	DDX_Control(pDX, IDC_OPENCLOSE4, m_OpenClose[3]);
	DDX_Control(pDX, IDC_OPENCLOSE5, m_OpenClose[4]);
	DDX_Control(pDX, IDC_IDROBOT, m_IDRobotBtn);
}


BEGIN_MESSAGE_MAP(CSelectRoboticDrives, CDialog)
	ON_CBN_SELCHANGE(IDC_DRIVE_COMBO1, OnCbnSelchangeDriveCombo1)
	ON_CBN_SELCHANGE(IDC_DRIVE_COMBO2, OnCbnSelchangeDriveCombo2)
	ON_CBN_SELCHANGE(IDC_DRIVE_COMBO3, OnCbnSelchangeDriveCombo3)
	ON_CBN_SELCHANGE(IDC_DRIVE_COMBO4, OnCbnSelchangeDriveCombo4)
	ON_CBN_SELCHANGE(IDC_DRIVE_COMBO5, OnCbnSelchangeDriveCombo5)
	ON_BN_CLICKED(IDC_OPENCLOSE1, OnBnClickedOpenclose1)
	ON_BN_CLICKED(IDC_OPENCLOSE2, OnBnClickedOpenclose2)
	ON_BN_CLICKED(IDC_OPENCLOSE3, OnBnClickedOpenclose3)
	ON_BN_CLICKED(IDC_OPENCLOSE4, OnBnClickedOpenclose4)
	ON_BN_CLICKED(IDC_OPENCLOSE5, OnBnClickedOpenclose5)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_IDROBOT, OnBnClickedIdrobot)
END_MESSAGE_MAP()


// CSelectRoboticDrives message handlers

void CSelectRoboticDrives::OnCbnSelchangeDriveCombo1()
{
	// Add your control notification handler code here
}

void CSelectRoboticDrives::OnCbnSelchangeDriveCombo2()
{
	// Add your control notification handler code here
}

void CSelectRoboticDrives::OnCbnSelchangeDriveCombo3()
{
	// Add your control notification handler code here
}

void CSelectRoboticDrives::OnCbnSelchangeDriveCombo4()
{
	// Add your control notification handler code here
}

void CSelectRoboticDrives::OnCbnSelchangeDriveCombo5()
{
	// Add your control notification handler code here
}

void CSelectRoboticDrives::OnBnClickedOpenclose1()
{
	PTRobot_OpenCloseDrive(this->hDrives[0], DRIVE_OPEN);
	PTRobot_OpenCloseDrive(this->hDrives[0], DRIVE_CLOSE);
}

void CSelectRoboticDrives::OnBnClickedOpenclose2()
{
	PTRobot_OpenCloseDrive(this->hDrives[1], DRIVE_OPEN);
	PTRobot_OpenCloseDrive(this->hDrives[1], DRIVE_CLOSE);
}

void CSelectRoboticDrives::OnBnClickedOpenclose3()
{
	PTRobot_OpenCloseDrive(this->hDrives[2], DRIVE_OPEN);
	PTRobot_OpenCloseDrive(this->hDrives[2], DRIVE_CLOSE);
}

void CSelectRoboticDrives::OnBnClickedOpenclose4()
{
	PTRobot_OpenCloseDrive(this->hDrives[3], DRIVE_OPEN);
	PTRobot_OpenCloseDrive(this->hDrives[3], DRIVE_CLOSE);
}

void CSelectRoboticDrives::OnBnClickedOpenclose5()
{
	PTRobot_OpenCloseDrive(this->hDrives[4], DRIVE_OPEN);
	PTRobot_OpenCloseDrive(this->hDrives[4], DRIVE_CLOSE);
}

void CSelectRoboticDrives::OnBnClickedOk()
{
	DWORD dwInd=0;
	int nVal=0;

	nDrivesSet=0;
	for(dwInd =0; dwInd< this->dwDrives; dwInd++)
	{
		nVal = this->m_DriveLocation[dwInd].GetCurSel();
		if (nVal == 1)
		{		
			PTRobot_SetRoboticDrive(this->hRobot, this->hDrives[dwInd], 0,0);
			nDrivesSet++;
		}
		else if (nVal == 2)
		{
			PTRobot_SetRoboticDrive(this->hRobot, this->hDrives[dwInd], 0,1);
			nDrivesSet++;		
		}
	}
	OnOK();
}

BOOL CSelectRoboticDrives::OnInitDialog()
{	
	DWORD dwInd=0;
	PTDriveInfo myDriveInfo;
	PTRobotInfo myRobotInfo;

	CDialog::OnInitDialog();

	PTRobot_GetRobotInfo(this->hRobot, &myRobotInfo);
	this->SetWindowText(myRobotInfo.tszRobotDesc);

	for(dwInd =0; dwInd< this->dwDrives; dwInd++)
	{
		// Attempt to get the drive information
		if ( PTRobot_GetDriveInfo(hDrives[dwInd], &myDriveInfo) == PTROBOT_OK )
		{
			// display the info if successful		
			this->m_DriveDesc[dwInd].ShowWindow(SW_SHOW);
			this->m_DriveLocation[dwInd].ShowWindow(SW_SHOW);
			this->m_OpenClose[dwInd].ShowWindow(SW_SHOW);
			this->m_DriveDesc[dwInd].SetWindowText(myDriveInfo.tszDriveName);
			
			if (myRobotInfo.dwNumDrives > 1)
			{
				this->m_DriveLocation[dwInd].InsertString(0, _T("Non Robotic"));
				this->m_DriveLocation[dwInd].InsertString(1, _T("Robotic Top"));
				this->m_DriveLocation[dwInd].InsertString(2, _T("Robotic Bottom"));
			}
			else
			{
				this->m_DriveLocation[dwInd].InsertString(0, _T("Non Robotic"));
				this->m_DriveLocation[dwInd].InsertString(1, _T("Robotic"));
			}
			this->m_DriveLocation[dwInd].SetCurSel(0);
		}
	}
	return TRUE;
}

void CSelectRoboticDrives::OnBnClickedIdrobot()
{
	PTRobot_SystemAction(this->hRobot, PTACT_IDENTIFY);
}
