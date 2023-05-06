//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GE84_EUIDLG_H__B4C2FF3D_DB32_420A_A91D_0BE2BE54BF59__INCLUDED_)
#define AFX_GE84_EUIDLG_H__B4C2FF3D_DB32_420A_A91D_0BE2BE54BF59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE84_EUIDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE84_EUIDLG dialog

class CGE84_EUIDLG : public CDialog
{
// Construction
public:
	CGE84_EUIDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE84_EUIDLG)
	enum { IDD = IDD_GE84_EuIDLG };
	int		m_rowsY;
	CString	m_editX;
	CString	m_editY;
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE84_EUIDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE84_EUIDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

		CString m_dataX, m_dataY;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE84_EUIDLG_H__B4C2FF3D_DB32_420A_A91D_0BE2BE54BF59__INCLUDED_)
