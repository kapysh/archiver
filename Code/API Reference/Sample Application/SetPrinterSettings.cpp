// SetPrinterSettings.cpp : implementation file
//

#include "stdafx.h"
#include "PTRobotApp.h"
#include "SetPrinterSettings.h"
#include ".\setprintersettings.h"
#include "..\PTRobot.h"
#include "utility.h"


// CSetPrinterSettings dialog

IMPLEMENT_DYNAMIC(CSetPrinterSettings, CDialog)
CSetPrinterSettings::CSetPrinterSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CSetPrinterSettings::IDD, pParent)
{
}

CSetPrinterSettings::~CSetPrinterSettings()
{
}

void CSetPrinterSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRINT_QUALITY_EDIT, m_PrintQualityEdit);
	DDX_Control(pDX, IDC_OUTERMARGIN_EDIT, m_OuterDiamEdit);
	DDX_Control(pDX, IDC_INNERDIAM_EDIT, m_InnerDiamEdit);
}


BOOL CSetPrinterSettings::OnInitDialog()
{
	PTPrinterSettings PtrSettings;
	TCHAR tszSetting[20];
	DWORD dwErr;

	CDialog::OnInitDialog();

	dwErr = PTRobot_GetPrinterSettings(this->m_hRobot, &PtrSettings);
	if (dwErr == PTROBOT_OK)
	{
		_stprintf(tszSetting, _T("%i"), PtrSettings.dwPrintQuality);
		this->m_PrintQualityEdit.SetWindowText(tszSetting);
		_stprintf(tszSetting, _T("%i"), PtrSettings.dwOuterMargin);
		this->m_OuterDiamEdit.SetWindowText(tszSetting);
		_stprintf(tszSetting, _T("%i"), PtrSettings.dwInnerDiam);
		this->m_InnerDiamEdit.SetWindowText(tszSetting);
	}
	else
	{
		MessageBox( _T("Unable to get printer settings"), _T("Error"), MB_OK);
		this->EndDialog(0);
		return FALSE;
	}
	return TRUE;
}
BEGIN_MESSAGE_MAP(CSetPrinterSettings, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetPrinterSettings message handlers

void CSetPrinterSettings::OnBnClickedOk()
{
	PTPrinterSettings2 PtrSettings;
	TCHAR tszSetting[20];
	DWORD dwErr;

	this->m_PrintQualityEdit.GetWindowText(tszSetting, 20);
	PtrSettings.dwPrintQuality = GetIntFromString(tszSetting);

	this->m_OuterDiamEdit.GetWindowText(tszSetting, 20);
	PtrSettings.dwOuterMargin = GetIntFromString(tszSetting);

	this->m_InnerDiamEdit.GetWindowText(tszSetting, 20);
	PtrSettings.dwInnerDiam = GetIntFromString(tszSetting);

	PtrSettings.dwCartridge = 0xffff;
	PtrSettings.dwColorMatchType = 0xffff;
	PtrSettings.dwColorTable = 0xffff;
	PtrSettings.dwPrintBidi = 0xffff;
	PtrSettings.dwSaturation = 0xffff;
	PtrSettings.dwRotate180 = 1;

	dwErr = PTRobot_SetPrinterSettings2(this->m_hRobot, &PtrSettings);
	if (dwErr == PTROBOT_OK)
	{
		MessageBox(_T("Printer settings set successfully"), _T("Success"), MB_OK);
	}
	else
	{
		MessageBox(_T("Printer settings failed"), _T("Error"), MB_OK);
	}
	OnOK();
}

void CSetPrinterSettings::OnBnClickedCancel()
{
	OnCancel();
}
