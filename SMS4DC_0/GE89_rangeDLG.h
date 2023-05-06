#if !defined(AFX_GE89_RANGEDLG_H__567C525A_8B66_4D67_AC5F_E771D51E5B64__INCLUDED_)
#define AFX_GE89_RANGEDLG_H__567C525A_8B66_4D67_AC5F_E771D51E5B64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE89_rangeDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE89_rangeDLG dialog

class CGE89_rangeDLG : public CDialog
{
// Construction
public:
	CGE89_rangeDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE89_rangeDLG)
	enum { IDD = IDD_GE89_rangeDLG };
	double	m_D;
	double	m_Emin;
	double	m_T;
	double	m_L;
	double	m_DH;
	BOOL	m_DHflag;
	CString	m_kfactor;
	BOOL	m_kflag;
	BOOL	m_PRflag;
	double	m_PR;
	//}}AFX_DATA
	CString m_label1;
	double	m_kfactorD;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE89_rangeDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE89_rangeDLG)
	afx_msg void OnCHECKDHflag();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEDITk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

		double atof_kfactor(CString k1) ;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE89_RANGEDLG_H__567C525A_8B66_4D67_AC5F_E771D51E5B64__INCLUDED_)
