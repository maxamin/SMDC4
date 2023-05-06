#if !defined(AFX_ESANTPAT_H__61606FB1_1F36_4354_A183_4D02EB7F566D__INCLUDED_)
#define AFX_ESANTPAT_H__61606FB1_1F36_4354_A183_4D02EB7F566D__INCLUDED_

#include "resource.h"
#include "Administrative.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ESAntPat.h : header file
//
#include "EditGrid.h"

/////////////////////////////////////////////////////////////////////////////
// CESAntPat dialog

class CESAntPat : public CDialog
{
// Construction
public:
	CESAntPat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CESAntPat)
	enum { IDD = IDD_ES_ANT_PAT };
	CString	m_ER;
	CString	m_CoeffA;
	CString	m_CoeffB;
	CString	m_CoeffC;
	CString	m_CoeffD;
	CString	m_AntPatt;
	CString	m_Phi1;
	//}}AFX_DATA
	CString m_CDBSTR;
	CString m_Lang;

	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CESAntPat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CESAntPat)
	afx_msg void OnPattern();
	afx_msg void OnCoeff();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ESANTPAT_H__61606FB1_1F36_4354_A183_4D02EB7F566D__INCLUDED_)
