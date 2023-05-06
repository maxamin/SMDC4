#if !defined(AFX_GE06SRVDLG_H__40A4B91C_13E0_410E_8627_4A32E570A478__INCLUDED_)
#define AFX_GE06SRVDLG_H__40A4B91C_13E0_410E_8627_4A32E570A478__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GE06srvDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGE06srvDLG dialog

class CGE06srvDLG : public CDialog
{
// Construction
public:
	CGE06srvDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGE06srvDLG)
	enum { IDD = IDD_GE06srvDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	int	m_EXA,m_LNB,m_AZstep,m_UD,m_UDdisplay;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGE06srvDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGE06srvDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioExa();
	afx_msg void OnRadioNa();
	afx_msg void OnCheckLnb();
	afx_msg void OnRadio6();
	afx_msg void OnRadio12();
	afx_msg void OnRadio36();
	afx_msg void OnCheckUd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GE06SRVDLG_H__40A4B91C_13E0_410E_8627_4A32E570A478__INCLUDED_)
