#if !defined(AFX_GE06CVADLG_H__0424BF7A_2F5C_40F6_AD27_40F863A3CC90__INCLUDED_)
#define AFX_GE06CVADLG_H__0424BF7A_2F5C_40F6_AD27_40F863A3CC90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE06cvaDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE06cvaDLG dialog

class CGE06cvaDLG : public CDialog
{
// Construction
public:
	CGE06cvaDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE06cvaDLG)
	enum { IDD = IDD_GE06cvaDLG };
	CComboBox	m_environment;
	double	m_Emed;
	double	m_SR;
	double	m_L;
	double	m_Fr;
	double	m_Ti;
	//}}AFX_DATA
	int	m_AntDisc , m_CSdisplay , m_CSdisplay1;
	int	m_DP,m_AP,m_OS,m_env;
//	int m_srv;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE06cvaDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE06cvaDLG)
	afx_msg void OnCHECKAntDisc();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckDp();
	afx_msg void OnCheckAp();
	afx_msg void OnCheckOs();
	afx_msg void OnSelchangeenvironment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE06CVADLG_H__0424BF7A_2F5C_40F6_AD27_40F863A3CC90__INCLUDED_)
