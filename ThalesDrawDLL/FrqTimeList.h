#if !defined(AFX_FRQTIMELIST_H__E70E055C_E960_4BAE_9AB6_89F2508CFD6A__INCLUDED_)
#define AFX_FRQTIMELIST_H__E70E055C_E960_4BAE_9AB6_89F2508CFD6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrqTimeList.h : header file
//
#include "ColorListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CFrqTimeList dialog

class CFrqTimeList : public CDialog
{
// Construction
public:
	CFrqTimeList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFrqTimeList)
	enum { IDD = IDD_DIALOG_FrqTimeList };
//	CListCtrl	m_List1;
	CColorListCtrl	m_List1;
	//}}AFX_DATA

	CStringArray m_Freq;
	CArray<double,double>m_GlobalRate;

	CStringArray m_TimeBracketList;
	BOOL m_flag_Frq_Time;

	CString m_strOUT;
	CString m_strTimeStart;
	BOOL m_OccResFlag;

	CString m_Lang;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrqTimeList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrqTimeList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CThalesDrawDLLApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRQTIMELIST_H__E70E055C_E960_4BAE_9AB6_89F2508CFD6A__INCLUDED_)
