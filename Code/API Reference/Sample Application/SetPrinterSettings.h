#pragma once
#include "afxwin.h"


// CSetPrinterSettings dialog

class CSetPrinterSettings : public CDialog
{
	DECLARE_DYNAMIC(CSetPrinterSettings)

public:
	CSetPrinterSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPrinterSettings();

// Dialog Data
	enum { IDD = IDD_SETPRINER_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_PrintQualityEdit;
	CEdit m_OuterDiamEdit;
	CEdit m_InnerDiamEdit;
	HANDLE m_hRobot;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
