#pragma once
#include "afxwin.h"


// CSetPrinterSettings dialog

class CSetMergeData : public CDialog
{
	DECLARE_DYNAMIC(CSetMergeData)

public:
	CSetMergeData(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetMergeData();

// Dialog Data
	enum { IDD = IDD_MERGE_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	HANDLE m_hRobot;
	afx_msg void OnBnClickedOk();
	CEdit m_MergeDataEdit1;
	CEdit m_MergeDataEdit2;
	CEdit m_MergeDataEdit3;
	CEdit m_MergeDataEdit4;
	CEdit m_MergeDataEdit5;
	CString m_csMergeData1;
	CString m_csMergeData2;
	CString m_csMergeData3;
	CString m_csMergeData4;
	CString m_csMergeData5;
	bool	m_fMergeMethod2;
	afx_msg void OnBnClickedBrowseBtn();
	afx_msg void OnBnClickedRadioMerge2();
	afx_msg void OnBnClickedRadioMerge1();
	CButton m_RadioMerge1;
	CButton m_RadioMerge2;
};
