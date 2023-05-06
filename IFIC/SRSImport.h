#if !defined(AFX_SRSIMPORT_H__4EA33464_36DF_43DC_AF10_E9FE26EE08C8__INCLUDED_)
#define AFX_SRSIMPORT_H__4EA33464_36DF_43DC_AF10_E9FE26EE08C8__INCLUDED_

#include "resource.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SRSImport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSRSImport dialog

class CSRSImport : public CDialog
{
// Construction
public:
	CSRSImport(CWnd* pParent = NULL);   // standard constructor
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };

// Dialog Data
	//{{AFX_DATA(CSRSImport)
	enum { IDD = IDD_SRSDLG };
	CProgressCtrl	m_ImportProgress;
	CListBox	m_AdmSel;
	CListBox	m_AdmList;
	//}}AFX_DATA
	CString m_CDBSTR, m_Lang;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRSImport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString GetAdmList();

	// Generated message map functions
	//{{AFX_MSG(CSRSImport)
	afx_msg void OnAdmAdd();
	afx_msg void OnAdmAddAll();
	afx_msg void OnAdmRemove();
	afx_msg void OnAdmClear();
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRSIMPORT_H__4EA33464_36DF_43DC_AF10_E9FE26EE08C8__INCLUDED_)
