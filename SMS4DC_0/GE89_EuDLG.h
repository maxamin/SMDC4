//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GE89_EUDLG_H__FC792574_41EC_4315_BF79_00BA0ABA05FD__INCLUDED_)
#define AFX_GE89_EUDLG_H__FC792574_41EC_4315_BF79_00BA0ABA05FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE89_EuDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE89_EuDLG dialog

class CGE89_EuDLG : public CDialog
{
// Construction
public:
	CGE89_EuDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE89_EuDLG)
	enum { IDD = IDD_GE89_EuDLG };
	int		m_rowsY;
	CString	m_editY;
	CString	m_editX;
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	//}}AFX_DATA

	CString m_title1, m_title2;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE89_EuDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE89_EuDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

		CString m_dataX, m_dataY;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE89_EUDLG_H__FC792574_41EC_4315_BF79_00BA0ABA05FD__INCLUDED_)
