#if !defined(AFX_NORMALIZEDLG_H__C7D8EF0F_79A6_4E16_88B6_DD9B6ACED973__INCLUDED_)
#define AFX_NORMALIZEDLG_H__C7D8EF0F_79A6_4E16_88B6_DD9B6ACED973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NormalizeDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNormalizeDLG dialog

class CNormalizeDLG : public CDialog
{
// Construction
public:
	CNormalizeDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNormalizeDLG)
	enum { IDD = IDD_NormalizeDLG };
	double	m_MaxValue;
	double	m_MaxValue2;
	double	m_MinValue;
	double	m_MinValue2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNormalizeDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNormalizeDLG)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NORMALIZEDLG_H__C7D8EF0F_79A6_4E16_88B6_DD9B6ACED973__INCLUDED_)
