#pragma once
#include "afxwin.h"


// CSelectRoboticDrives dialog

class CSelectRoboticDrives : public CDialog
{
	DECLARE_DYNAMIC(CSelectRoboticDrives)

public:
	CSelectRoboticDrives(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectRoboticDrives();

// Dialog Data
	enum { IDD = IDD_CHOOSE_ROBODRIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_OpenClose[5];
	CStatic m_DriveDesc[5];
	CComboBox m_DriveLocation[5];
	afx_msg void OnCbnSelchangeDriveCombo1();
	afx_msg void OnCbnSelchangeDriveCombo2();
	afx_msg void OnCbnSelchangeDriveCombo3();
	afx_msg void OnCbnSelchangeDriveCombo4();
	afx_msg void OnCbnSelchangeDriveCombo5();
	afx_msg void OnBnClickedOpenclose1();
	afx_msg void OnBnClickedOpenclose2();
	afx_msg void OnBnClickedOpenclose3();
	afx_msg void OnBnClickedOpenclose4();
	afx_msg void OnBnClickedOpenclose5();
	HANDLE hRobot;
	DWORD dwDrives;
	HANDLE hDrives[5];
	DWORD dwRobotType;
	int nDrivesSet;
	afx_msg void OnBnClickedOk();
	CButton m_IDRobotBtn;
	afx_msg void OnBnClickedIdrobot();
};
