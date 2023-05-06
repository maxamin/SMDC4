//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GE84BC2BCDLG_H__67FC4A83_2F33_4BC8_BAAA_673BDE2EC1EE__INCLUDED_)
#define AFX_GE84BC2BCDLG_H__67FC4A83_2F33_4BC8_BAAA_673BDE2EC1EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE84BC2BCDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE84BC2BCDLG dialog

class CGE84BC2BCDLG : public CDialog
{
// Construction
public:
	CGE84BC2BCDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE84BC2BCDLG)
	enum { IDD = IDD_GE84BC2BCDLG };
	CMSFlexGrid	m_LIST1;
	int		m_nROWS;
	CString	m_data;
	CString	m_title;
	CString	m_DorE;
	CMSFlexGrid	m_LIST2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE84BC2BCDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE84BC2BCDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

		CString m_data1;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE84BC2BCDLG_H__67FC4A83_2F33_4BC8_BAAA_673BDE2EC1EE__INCLUDED_)
