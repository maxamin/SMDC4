//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GE06REPDLG1_H__CE7957ED_7B23_442F_A400_4906E40D05D9__INCLUDED_)
#define AFX_GE06REPDLG1_H__CE7957ED_7B23_442F_A400_4906E40D05D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE06repDLG1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE06repDLG1 dialog

class CGE06repDLG1 : public CDialog
{
// Construction
public:
	CGE06repDLG1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE06repDLG1)
	enum { IDD = IDD_GE06repDLG1 };
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	BOOL	m_Google;
	//}}AFX_DATA
	 
	int		m_rowsY , m_rowsX , m_mode , m_Bdisplay;
	CString	m_dataX , m_dataX1 , m_dataY , m_dataY1;
	CString	m_title1 , m_title2 , m_title3;
	BOOL	m_GoogleFlag;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE06repDLG1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE06repDLG1)
	virtual BOOL OnInitDialog();
	afx_msg void OnReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE06REPDLG1_H__CE7957ED_7B23_442F_A400_4906E40D05D9__INCLUDED_)
