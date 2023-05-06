//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "ESAntPat.h"
#if !defined(AFX_CATSELECT_H__F22CCE2D_5179_4BB3_BF27_C6AD58F13347__INCLUDED_)
#define AFX_CATSELECT_H__F22CCE2D_5179_4BB3_BF27_C6AD58F13347__INCLUDED_

#include "resource.h"
#include "Administrative.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EqCatSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCatSelect dialog

class CCatSelect : public CDialog
{
// Construction
public:
	CCatSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCatSelect)
	enum { IDD = IDD_EQ_CAT };
	CString m_CDBSTR;
	//}}AFX_DATA
	CMSHFlexGrid	m_CatGrid, *m_EqGrid;
	long m_ID,m_CatID;
	CString m_Table;
	int m_typ;
	CString m_Srv;
	CString m_Lang;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void OnOK();
	CString GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit, CString *Format, CString *Srv, CString *Mask);
	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCatSelect)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddPattern();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATSELECT_H__F22CCE2D_5179_4BB3_BF27_C6AD58F13347__INCLUDED_)
