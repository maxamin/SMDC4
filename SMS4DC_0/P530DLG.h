#if !defined(AFX_P530DLG_H__5BF150FA_4542_429B_BBA6_9C9CE2C06DA1__INCLUDED_)
#define AFX_P530DLG_H__5BF150FA_4542_429B_BBA6_9C9CE2C06DA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// P530DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CP530DLG dialog

class CP530DLG : public CDialog
{
// Construction
public:
	CP530DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CP530DLG)
	enum { IDD = IDD_P530DLG };
	CButton	m_ITUstd;
	CComboBox	m_atom;
	CString	m_k;
	CString	m_k99;
	double	m_fzn;
	int		m_atomi;
	double	m_dist;
	CString	m_anav;
	BOOL	m_CHECK_Q;
	//}}AFX_DATA

	double m_LatM, m_h1, m_h2;
	BOOL m_flag_WorstMonth;
	int m_iClimate, m_RADIO1_rain;
	CString m_pw;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP530DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP530DLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOatom();
	afx_msg void OnCHECKITUstd();
	afx_msg void OnRADIO1Av();
	afx_msg void OnRADIO1Wo();
	afx_msg void OnKillfocusEDITanav();
	afx_msg void OnRADIO1rain1();
	afx_msg void OnRADIO1rain2();
	afx_msg void OnRADIO1rain3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	double Dist_ke(double d) ;
	double Interp1(double *D0,double *E0,double d,int num) ;
	void RADIO_AvWo();
	double DeltaG_factor(double lat_deg,double d_km,double hr,double he);

	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P530DLG_H__5BF150FA_4542_429B_BBA6_9C9CE2C06DA1__INCLUDED_)
