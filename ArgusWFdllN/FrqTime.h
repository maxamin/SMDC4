#if !defined(AFX_FRQTIME_H__E3664E3F_C930_4C29_9D73_59594D024BD2__INCLUDED_)
#define AFX_FRQTIME_H__E3664E3F_C930_4C29_9D73_59594D024BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrqTime.h : header file
//
#include "ColorListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFrqTime dialog

class CFrqTime : public CDialog
{
// Construction
public:
	CFrqTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFrqTime)
	enum { IDD = IDD_DIALOG_FrqTime };
	CColorListCtrl	m_List1;
	//}}AFX_DATA

	CStringArray m_ListDateTime;
	CArray<double,double>m_ListFrq;
	CString m_strOUT;
	BOOL m_flag_Frq_Time;

	CString m_Lang;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrqTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrqTime)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CArgusWFdllApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRQTIME_H__E3664E3F_C930_4C29_9D73_59594D024BD2__INCLUDED_)
