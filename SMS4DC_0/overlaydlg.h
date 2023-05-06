#if !defined(AFX_OVERLAYDLG_H__AE59F94E_538A_4E2C_B978_DA16D506914B__INCLUDED_)
#define AFX_OVERLAYDLG_H__AE59F94E_538A_4E2C_B978_DA16D506914B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OverlayDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COverlayDLG dialog
#include "iter.h"

class COverlayDLG : public CDialog
{
// Construction
public:
	COverlayDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COverlayDLG)
	enum { IDD = IDD_OverlayDLG };
	CListBox	m_overlay;
	double	m_OverlayFactor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COverlayDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COverlayDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkLISTOverlay();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
  DocumentList_t Docs;
	CDocument* m_SelectedDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OVERLAYDLG_H__AE59F94E_538A_4E2C_B978_DA16D506914B__INCLUDED_)
