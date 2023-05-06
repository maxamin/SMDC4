//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_AP7_CORDCONTOURDLG_H__A06A2C13_9229_4F5D_80CB_30A9C32DE168__INCLUDED_)
#define AFX_AP7_CORDCONTOURDLG_H__A06A2C13_9229_4F5D_80CB_30A9C32DE168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AP7_CordContourDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAP7_CordContourDLG dialog

class CAP7_CordContourDLG : public CDialog
{
// Construction
public:
	CAP7_CordContourDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAP7_CordContourDLG)
	enum { IDD = IDD_AP7_CordContourDLG };
	BOOL	m_M1;
	BOOL	m_M1_10;
	BOOL	m_M1_20;
	BOOL	m_M1_30;
	BOOL	m_M1_40;
	BOOL	m_M1_50;
	BOOL	m_M1_60;
	BOOL	m_M2;
	CString	m_Data;
	long	m_NRow;
	long	m_NRowsel;
	long	m_Rows;
	CMSFlexGrid	m_LIST1;
	BOOL	m_All;
	//}}AFX_DATA
	CString affected_CTRY[1000];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAP7_CordContourDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAP7_CordContourDLG)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnCHECKall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AP7_CORDCONTOURDLG_H__A06A2C13_9229_4F5D_80CB_30A9C32DE168__INCLUDED_)
