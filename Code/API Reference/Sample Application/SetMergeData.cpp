// SetPrinterSettings.cpp : implementation file
//

#include "stdafx.h"
#include "PTRobotApp.h"
#include "SetMergeData.h"
#include "..\PTRobot.h"


// CSetMergeData dialog

IMPLEMENT_DYNAMIC(CSetMergeData, CDialog)
CSetMergeData::CSetMergeData(CWnd* pParent /*=NULL*/)
	: CDialog(CSetMergeData::IDD, pParent)
{
}

CSetMergeData::~CSetMergeData()
{
}

void CSetMergeData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MERGE_EDIT1, m_MergeDataEdit1);
	DDX_Control(pDX, IDC_MERGE_EDIT2, m_MergeDataEdit2);
	DDX_Control(pDX, IDC_MERGE_EDIT3, m_MergeDataEdit3);
	DDX_Control(pDX, IDC_MERGE_EDIT4, m_MergeDataEdit4);
	DDX_Control(pDX, IDC_MERGE_EDIT5, m_MergeDataEdit5);
	DDX_Control(pDX, IDC_RADIO_MERGE1, m_RadioMerge1);
	DDX_Control(pDX, IDC_RADIO_MERGE2, m_RadioMerge2);
}


BOOL CSetMergeData::OnInitDialog()
{
	
	CDialog::OnInitDialog();

	// init the fields to the previous strings
	this->m_MergeDataEdit1.SetWindowText(this->m_csMergeData1);
	this->m_MergeDataEdit2.SetWindowText(this->m_csMergeData2);
	this->m_MergeDataEdit3.SetWindowText(this->m_csMergeData3);
	this->m_MergeDataEdit4.SetWindowText(this->m_csMergeData4);
	this->m_MergeDataEdit5.SetWindowText(this->m_csMergeData5);

	if (this->m_fMergeMethod2)
	{
		this->m_RadioMerge1.SetCheck(BST_UNCHECKED);
		this->m_RadioMerge2.SetCheck(BST_CHECKED);
	}
	else
	{
		this->m_RadioMerge1.SetCheck(BST_CHECKED);
		this->m_RadioMerge2.SetCheck(BST_UNCHECKED);
	}

	return TRUE;
}
BEGIN_MESSAGE_MAP(CSetMergeData, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_PRINT_BROWSE_BTN, OnBnClickedBrowseBtn)
	ON_BN_CLICKED(IDC_RADIO_MERGE2, &CSetMergeData::OnBnClickedRadioMerge2)
	ON_BN_CLICKED(IDC_RADIO_MERGE1, &CSetMergeData::OnBnClickedRadioMerge1)
END_MESSAGE_MAP()


// CSetMergeData message handlers

void CSetMergeData::OnBnClickedOk()
{
#define BUF_SIZE 300
	TCHAR tszMergeData[BUF_SIZE];

	// Save the text from each of the 5 Edit boxes
	// We could add more than 5, but we just chose 5 as a good number
	// Note that the number of edit boxes that are filled in by the user
	// should match up exactly with the number of Merge fields in the Surething file created.
	this->m_MergeDataEdit1.GetWindowText(tszMergeData, BUF_SIZE);
	this->m_csMergeData1 = tszMergeData;
	this->m_MergeDataEdit2.GetWindowText(tszMergeData, BUF_SIZE);
	this->m_csMergeData2 = tszMergeData;
	this->m_MergeDataEdit3.GetWindowText(tszMergeData, BUF_SIZE);
	this->m_csMergeData3 = tszMergeData;
	this->m_MergeDataEdit4.GetWindowText(tszMergeData, BUF_SIZE);
	this->m_csMergeData4 = tszMergeData;
	this->m_MergeDataEdit5.GetWindowText(tszMergeData, BUF_SIZE);
	this->m_csMergeData5 = tszMergeData;

	OnOK();
}



// ******************************************************************************** //
void CSetMergeData::OnBnClickedBrowseBtn()
{
	OPENFILENAME fileToOpenPRN;
	TCHAR tszFile[MAX_PATH] = _T("");       // buffer for file name

	ZeroMemory(&fileToOpenPRN, sizeof(OPENFILENAME));
	fileToOpenPRN.lStructSize = sizeof(OPENFILENAME);
	fileToOpenPRN.hwndOwner = NULL;
	fileToOpenPRN.lpstrFile = tszFile;
	fileToOpenPRN.nMaxFile = sizeof(tszFile)/sizeof(TCHAR);
	fileToOpenPRN.lpstrFilter = _T("All\0*.*\0Image Files (.JPG .BMP .TIF)\0*.JPG;*.BMP;*.TIF\0");
	fileToOpenPRN.nFilterIndex = 2;
	fileToOpenPRN.lpstrFileTitle = NULL;
	fileToOpenPRN.nMaxFileTitle = 0;
	fileToOpenPRN.lpstrInitialDir = NULL;
	fileToOpenPRN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&fileToOpenPRN) == TRUE)
		this->m_MergeDataEdit5.SetWindowText(fileToOpenPRN.lpstrFile);
	
}

void CSetMergeData::OnBnClickedRadioMerge2()
{
	this->m_fMergeMethod2 = true;
}

void CSetMergeData::OnBnClickedRadioMerge1()
{
	this->m_fMergeMethod2 = false;
}
