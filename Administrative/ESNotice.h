#if !defined(AFX_ESNOTICE_H__E1096CD5_36B5_4414_A705_FB9784CDC9B5__INCLUDED_)
#define AFX_ESNOTICE_H__E1096CD5_36B5_4414_A705_FB9784CDC9B5__INCLUDED_

#include "resource.h"
#include "Administrative.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ESNotice.h : header file
//
#include "Administrative.h"
/////////////////////////////////////////////////////////////////////////////
// CESNotice dialog

class CESNotice : public CDialog
{
// Construction
public:
	CESNotice(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CESNotice)
	enum { IDD = IDD_SRS_NOTICE };
	CComboBox	m_Sub;
	CComboBox	m_RR;
	CComboBox	m_Prov;
	CComboBox	m_Action;
	CString	m_Adm;
	COleDateTime	m_Date;
	CString	m_RefID;
	CString	m_TgtNtc;
	//}}AFX_DATA

	CString m_CDBSTR;
	CString m_Lang;
	long m_ntc_id;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CESNotice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	CString GetFieldName(CDatabase *DB, CString Table, CString OrigName, 
		CString LangCode, CString *Unit, CString *Format, CString *Srv, CString *Mask);
	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CESNotice)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ESNOTICE_H__E1096CD5_36B5_4414_A705_FB9784CDC9B5__INCLUDED_)
