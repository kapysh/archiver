// PTRobotAppDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CPTRobotAppDlg dialog
class CPTRobotAppDlg : public CDialog
{
// Construction
public:
	CPTRobotAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PTROBOTAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	HANDLE m_hRobots[20];
	INT m_nRobots;
public:
	CComboBox m_RobotCombo;
	CButton m_EnumRobotsBtn;
	CButton m_RobotInfoBtn;
	CComboBox m_FromCombo;
	CComboBox m_ToCombo;
	CButton m_ThroughRecChk;
	CButton m_PrintFirstChk;
	CEdit m_PrintFileEdit;
	CButton m_PrintBrowseBtn;
	CButton m_GoBtn;
	CStatic m_PrintFileStatic;
	CStatic m_RobotStatic;
	CStatic m_MoveDiscsGrp;
	CStatic m_FromStatic;
	CStatic m_ToStatic;
	afx_msg void OnBnClickedEnumRobotsBtn();
	afx_msg void OnBnClickedRobotInfoBtn();
	afx_msg void OnBnClickedPrintBrowseBtn();
	afx_msg void OnBnClickedGoBtn();
	BOOL EnumRobots();
	BOOL UpdateRobotInfo();
	CStatic m_RobotTypeStatic;
	CStatic m_NumDrivesStatic;
	CStatic m_PrinterStatic;
	CStatic m_NumBinsStatic;
	CListBox m_DriveList;
	CButton m_DriveOpenCloseBtn;
	CEdit m_CopiesEdit;
	afx_msg void OnCbnSelchangeRobotCombo();
	afx_msg void OnBnClickedDriveinfoBtn();
	afx_msg void OnClose();
	CButton m_KillErrorBtn;
	afx_msg void OnBnClickedKillerrorBtn();
	CStatic m_RobotStatus;
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedKioskmodeChk();
	CButton m_KioskModeChk;
	CButton m_ThroughPrinterChk;
	afx_msg void OnBnClickedThroghPtrChk();
	afx_msg void OnCbnSelchangeFromCombo();
	afx_msg void OnCbnSelchangeToCombo();
	CButton m_GetPrinterSettings;
	CButton m_SetPrinterSettings;
	afx_msg void OnBnClickedGetPtrsettings();
	afx_msg void OnBnClickedSetPtrsettings();
	CButton m_ManualOpenCloseChk;
	CStatic m_JobProgress;
	afx_msg void OnBnClickedOpenClose();
	CButton m_SetMergeBtn;
	afx_msg void OnBnClickedSetMerge();
	CString m_csMergeData1;
	CString m_csMergeData2;	
	CString m_csMergeData3;	
	CString m_csMergeData4;
	CString m_csMergeData5;
	bool	m_fMergeMethod2;
	afx_msg void OnBnClickedEnumDrives();
	afx_msg void OnBnClickedPrintFirstChk();
	afx_msg void OnBnClickedThroughRecChk();
	CComboBox m_LangCombo;
	afx_msg void OnCbnSelchangeLangCombo();
	afx_msg void OnBnClickedCancelcmdBtn();
	//Version 1.08 added system action UI
	afx_msg void OnBnClickedSystemAction();
	CButton m_SystemActionBtn;
	CEdit m_SystemActionEdit;
	CComboBox m_SysActionCombo;
	int m_nActions;
	DWORD m_dwActionCombo[20];
};
