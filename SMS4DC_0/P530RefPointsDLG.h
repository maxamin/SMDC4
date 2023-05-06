//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_P530REFPOINTSDLG_H__34D0CD63_57B5_4012_B062_06BDE8FA5436__INCLUDED_)
#define AFX_P530REFPOINTSDLG_H__34D0CD63_57B5_4012_B062_06BDE8FA5436__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// P530RefPointsDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CP530RefPointsDLG dialog

class CP530RefPointsDLG : public CDialog
{
// Construction
public:
	CP530RefPointsDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CP530RefPointsDLG)
	enum { IDD = IDD_P530RefPointsDLG };
	CMSFlexGrid	m_List1;
	CString	m_data;
	int		m_nROWS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP530RefPointsDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP530RefPointsDLG)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P530REFPOINTSDLG_H__34D0CD63_57B5_4012_B062_06BDE8FA5436__INCLUDED_)
