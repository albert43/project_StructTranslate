
// StructureTranslationDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CStructureTranslationDlg dialog
class CStructureTranslationDlg : public CDialogEx
{
// Construction
public:
	CStructureTranslationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STRUCTURETRANSLATION_DIALOG };

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
public:
	afx_msg void OnBnClickedOk();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_editOrigin;
	CEdit m_editResult;
	CComboBox m_listOriginal;
};
