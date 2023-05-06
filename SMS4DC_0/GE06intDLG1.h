#if !defined(AFX_GE06INTDLG1_H__35FE1FEE_BB88_46FB_BBAB_B0ED2A9BF9F1__INCLUDED_)
#define AFX_GE06INTDLG1_H__35FE1FEE_BB88_46FB_BBAB_B0ED2A9BF9F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE06intDLG1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE06intDLG1 dialog

class CGE06intDLG1 : public CDialog
{
// Construction
public:
	CGE06intDLG1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE06intDLG1)
	enum { IDD = IDD_GE06intDLG1 };
	CComboBox	m_environment;
	double	m_SR;
	double	m_Ti;
	double	m_LPM;
	double	m_FR;
	double	m_Lat;
	double	m_Lon;
	//}}AFX_DATA
	int	m_AntDisc , m_env, m_FXMlocation, m_FXMlocationDisp;
//	int m_srv, m_FXMDisp;
	CString	m_LPMstr;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE06intDLG1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE06intDLG1)
	virtual BOOL OnInitDialog();
	afx_msg void OnCHECKAntDisc();
	afx_msg void OnSelchangeenvironment();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE06INTDLG1_H__35FE1FEE_BB88_46FB_BBAB_B0ED2A9BF9F1__INCLUDED_)
