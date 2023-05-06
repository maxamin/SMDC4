//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_GE84_EUDLG_H__96119BEF_5D77_4E45_9E11_423A328B58ED__INCLUDED_)
#define AFX_GE84_EUDLG_H__96119BEF_5D77_4E45_9E11_423A328B58ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE84_EUDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE84_EUDLG dialog

class CGE84_EUDLG : public CDialog
{
// Construction
public:
	CGE84_EUDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE84_EUDLG)
	enum { IDD = IDD_GE84_EuDLG };
	CString	m_editX;
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	CString	m_editY;
	int		m_rowsY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE84_EUDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE84_EUDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

		CString m_dataX, m_dataY;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE84_EUDLG_H__96119BEF_5D77_4E45_9E11_423A328B58ED__INCLUDED_)
