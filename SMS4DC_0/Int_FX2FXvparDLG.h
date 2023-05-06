#if !defined(AFX_INT_FX2FXVPARDLG_H__86E11FB0_6C18_4C19_AC9E_62D5E0FA356F__INCLUDED_)
#define AFX_INT_FX2FXVPARDLG_H__86E11FB0_6C18_4C19_AC9E_62D5E0FA356F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_FX2FXvparDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_FX2FXvparDLG dialog

class CInt_FX2FXvparDLG : public CDialog
{
// Construction
public:
	CInt_FX2FXvparDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInt_FX2FXvparDLG)
	enum { IDD = IDD_Int_FX2FXvparDLG };
	CComboBox	m_Clutter;
	BOOL	m_CHECK_Pol;
	double	m_D;
	double	m_dN;
	double	m_F;
	double	m_N0;
	double	m_EDIT_Pol;
	double	m_pTD;
	double	m_time;
	double	m_beta;
	double	m_Pressure;
	double	m_TempC;
	//}}AFX_DATA

double m_ha_Clutter, m_dk_Clutter;
BOOL m_flagAvWo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_FX2FXvparDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInt_FX2FXvparDLG)
	afx_msg void OnCHECKPol();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOClutterY();
	afx_msg void OnRADIO1AvY();
	afx_msg void OnRADIO1Wo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_FX2FXVPARDLG_H__86E11FB0_6C18_4C19_AC9E_62D5E0FA356F__INCLUDED_)
