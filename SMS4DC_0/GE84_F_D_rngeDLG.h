#if !defined(AFX_GE84_F_D_RNGEDLG_H__31B9C388_534B_4DE5_91D1_D1DFAC4DB22C__INCLUDED_)
#define AFX_GE84_F_D_RNGEDLG_H__31B9C388_534B_4DE5_91D1_D1DFAC4DB22C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE84_F_D_rngeDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE84_F_D_rngeDLG dialog

class CGE84_F_D_rngeDLG : public CDialog
{
// Construction
public:
	CGE84_F_D_rngeDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE84_F_D_rngeDLG)
	enum { IDD = IDD_GE84_F_D_rngeDLG };
	double	m_D;
	double	m_Emin;
	double	m_F;
	double	m_T;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE84_F_D_rngeDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE84_F_D_rngeDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE84_F_D_RNGEDLG_H__31B9C388_534B_4DE5_91D1_D1DFAC4DB22C__INCLUDED_)
