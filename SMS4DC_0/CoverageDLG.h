#if !defined(AFX_COVERAGEDLG_H__F6666577_1F3F_43F6_8C6D_B919152B3B2A__INCLUDED_)
#define AFX_COVERAGEDLG_H__F6666577_1F3F_43F6_8C6D_B919152B3B2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoverageDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCoverageDLG dialog

class CCoverageDLG : public CDialog
{
// Construction
public:
	CCoverageDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCoverageDLG)
	enum { IDD = IDD_CoverageDLG };
	double	m_max;
	double	m_min;
	double	m_thr;
	CString	m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoverageDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCoverageDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COVERAGEDLG_H__F6666577_1F3F_43F6_8C6D_B919152B3B2A__INCLUDED_)
