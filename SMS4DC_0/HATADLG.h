#if !defined(AFX_HATADLG_H__2CD4338C_7015_4DF6_BFEA_DDEB48374E28__INCLUDED_)
#define AFX_HATADLG_H__2CD4338C_7015_4DF6_BFEA_DDEB48374E28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HATADLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHATADLG dialog

class CHATADLG : public CDialog
{
// Construction
public:
	CHATADLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHATADLG)
	enum { IDD = IDD_HATADLG };
	CComboBox	m_COMBO_ENV;
	CEdit	m_b2;
	CEdit	m_b1;
	CEdit	m_a3;
	CEdit	m_a2;
	CEdit	m_a1;
	BOOL	m_UserDefined;
	double	m_Rx;
	double	m_kfactor;
	double	m_FRQ;
	int		m_ENV;
	double	m_a10;
	double	m_a20;
	double	m_a30;
	double	m_b10;
	double	m_b20;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHATADLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHATADLG)
	afx_msg void OnUserDefined();
	virtual BOOL OnInitDialog();
	afx_msg void OnDefault();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeComboEnv();
	afx_msg void OnChangea1();
	afx_msg void OnChangea2();
	afx_msg void OnChangea3();
	afx_msg void OnChangeb1();
	afx_msg void OnChangeb2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HATADLG_H__2CD4338C_7015_4DF6_BFEA_DDEB48374E28__INCLUDED_)
