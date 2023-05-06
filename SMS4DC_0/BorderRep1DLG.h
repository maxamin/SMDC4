//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_BORDERREP1DLG_H__AFE3E454_632C_4F73_93DB_0FF900574445__INCLUDED_)
#define AFX_BORDERREP1DLG_H__AFE3E454_632C_4F73_93DB_0FF900574445__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BorderRep1DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBorderRep1DLG dialog

class CBorderRep1DLG : public CDialog
{
// Construction
public:
	CBorderRep1DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBorderRep1DLG)
	enum { IDD = IDD_BorderRep1DLG };
	long	m_rowsY;
	CString	m_editX;
	CString	m_editY;
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	int		m_mode;
	//}}AFX_DATA
	CString m_title1, m_title2, m_title3,m_pTD;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorderRep1DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBorderRep1DLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString m_dataX, m_dataY;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORDERREP1DLG_H__AFE3E454_632C_4F73_93DB_0FF900574445__INCLUDED_)
