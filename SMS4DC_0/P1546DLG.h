#if !defined(AFX_P1546DLG_H__5E6D8FF0_7565_4A8B_BC56_C3EBC979AE19__INCLUDED_)
#define AFX_P1546DLG_H__5E6D8FF0_7565_4A8B_BC56_C3EBC979AE19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// P1546DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CP1546DLG dialog

class CP1546DLG : public CDialog
{
// Construction
public:
	CP1546DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CP1546DLG)
	enum { IDD = IDD_P1546DLG };
	CComboBox	m_system;
	CComboBox	m_environment;
	BOOL	m_Clangle;
	BOOL	m_landsea;
	double	m_k;
	int		m_env;
	double	m_location;
	double	m_RxH;
	int		m_syst;
	double	m_time;
	BOOL	m_RxShow;
	double	m_Cvalue;
	BOOL	m_CvShow;
	//}}AFX_DATA

BOOL m_Monitoring;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP1546DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP1546DLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangesystem();
	afx_msg void OnSelchangeenvironment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P1546DLG_H__5E6D8FF0_7565_4A8B_BC56_C3EBC979AE19__INCLUDED_)
