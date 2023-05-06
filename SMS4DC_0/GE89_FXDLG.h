//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GE89_FXDLG_H__46663AED_0A71_4357_A6E2_8F630C56BAC1__INCLUDED_)
#define AFX_GE89_FXDLG_H__46663AED_0A71_4357_A6E2_8F630C56BAC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE89_FXDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE89_FXDLG dialog

class CGE89_FXDLG : public CDialog
{
// Construction
public:
	CGE89_FXDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE89_FXDLG)
	enum { IDD = IDD_GE89_FXDLG };
	CString	m_editX;
	CString	m_editY;
	int		m_rowsY;
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	//}}AFX_DATA
	CString m_title1, m_title2, m_PR_CLS;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE89_FXDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE89_FXDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString m_dataX, m_dataY;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE89_FXDLG_H__46663AED_0A71_4357_A6E2_8F630C56BAC1__INCLUDED_)
