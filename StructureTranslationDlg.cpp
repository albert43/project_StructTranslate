
// StructureTranslationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructureTranslation.h"
#include "StructureTranslationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStructureTranslationDlg dialog



CStructureTranslationDlg::CStructureTranslationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStructureTranslationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStructureTranslationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORIGIN, m_editOrigin);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
}

BEGIN_MESSAGE_MAP(CStructureTranslationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStructureTranslationDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CStructureTranslationDlg message handlers

BOOL CStructureTranslationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStructureTranslationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStructureTranslationDlg::OnPaint()
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
HCURSOR CStructureTranslationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <iostream>
#include "Gdb.h"
using namespace std;
using namespace Al;

void CStructureTranslationDlg::OnBnClickedOk()
{
//	m_editOrigin.SetSel(-1, 0);


	// TODO: Add your control notification handler code here
	TCHAR	tszBuffOrigin[4096];
	TCHAR	*ptszBuffResult;
	char	*pszBuffOrigin;
	char	*pszBuffResult;
	int		nIndex;
	Gdb		g;

	m_editOrigin.GetWindowTextW(tszBuffOrigin, 4096);

	//	Translate char_t to char: tszBuffOrigin -> pszBuffOrigin
	nIndex = WideCharToMultiByte(CP_ACP, 0, tszBuffOrigin, -1, NULL, 0, NULL, NULL);
	pszBuffOrigin = new char[nIndex + 1];
	WideCharToMultiByte(CP_ACP, 0, tszBuffOrigin, -1, pszBuffOrigin, nIndex, NULL, NULL);
	
	//	Structure translate: pszBuffOrigin -> pszBuffResult
	g.gdb2default(pszBuffOrigin, &pszBuffResult);

//	pszBuffResult = new char[strlen(pszBuffOrigin) + 20];
//	strcpy(pszBuffResult, pszBuffOrigin);
//	strcat(pszBuffResult, "\r\nAlbert\r\n");

	//	Translate char to char_t: pszBuffResult -> ptszBuffResult
	nIndex = MultiByteToWideChar(CP_ACP, 0, pszBuffResult, -1, NULL, 0);
	ptszBuffResult = new TCHAR[nIndex + 1];
	MultiByteToWideChar(CP_ACP, 0, pszBuffResult, -1, ptszBuffResult, nIndex);
	

	m_editResult.SetWindowTextW(ptszBuffResult);

	delete pszBuffOrigin;
	delete pszBuffResult;
	delete ptszBuffResult;
//	CDialogEx::OnOK();

}

afx_msg BOOL CStructureTranslationDlg::PreTranslateMessage(MSG* pMsg)
{
	BOOL	bCtrl = false;

	bCtrl = GetKeyState(VK_CONTROL) & 0x8000;
	if ((bool)bCtrl == true)
	{
		if (pMsg->message == WM_KEYUP)
		{
			switch (pMsg->wParam)
			{
				case 'A':
				case 'a':
					if (GetFocus()->GetDlgCtrlID() == IDC_EDIT_ORIGIN)
					{
						m_editOrigin.SetSel(0,-1);
						return true;
					}
					else if (GetFocus()->GetDlgCtrlID() == IDC_EDIT_RESULT)
					{
						m_editResult.SetSel(0, -1);
						return true;
					}
					
					break;
			}
		}
	}

	return false;
}