#if !defined(AFX_P370DLG_H__C536AA74_D622_4286_8FD0_4D0212C074CF__INCLUDED_)
#define AFX_P370DLG_H__C536AA74_D622_4286_8FD0_4D0212C074CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// P370DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CP370DLG dialog

class CP370DLG : public CDialog
{
// Construction
public:
	CP370DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CP370DLG)
	enum { IDD = IDD_P370DLG };
	CComboBox	m_environment;
	CComboBox	m_system;
	double	m_time;
	double	m_location;
	double	m_k;
	double	m_RxH;
	BOOL	m_Clangle;
	BOOL	m_landsea;
	int		m_env;
	int		m_syst;
	BOOL	m_RxShow;
	BOOL	m_CvShow;
	double	m_Cvalue;
	BOOL	m_DHflag;
	double	m_DH;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP370DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP370DLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangesystem();
	afx_msg void OnSelchangeenvironment();
	afx_msg void OnCHECKDHflag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P370DLG_H__C536AA74_D622_4286_8FD0_4D0212C074CF__INCLUDED_)
