#if !defined(AFX_AUDIT_H__BFF10CF5_5AF9_49DE_A04E_44B0B05A3C8F__INCLUDED_)
#define AFX_AUDIT_H__BFF10CF5_5AF9_49DE_A04E_44B0B05A3C8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Audit.h : header file
//
#include "resource.h"
#include "Administrative.h"
#include "stdafx.h"
#include "MSHFlexGrid.h"

/////////////////////////////////////////////////////////////////////////////
// CAudit dialog

class CAudit : public CDialog
{
// Construction
public:
	CAudit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAudit)
	enum { IDD = IDD_AuditTrail };
	CComboBox	m_UserName;
	CComboBox	m_Table;
	CComboBox	m_Action;
	CMSHFlexGrid	m_AuditGrid;
	//}}AFX_DATA

	CString m_Lang;
	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAudit)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeUserName();
	afx_msg void OnSelchangeAction();
	afx_msg void OnSelchangeTable();
	afx_msg void OnAuditRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIT_H__BFF10CF5_5AF9_49DE_A04E_44B0B05A3C8F__INCLUDED_)
