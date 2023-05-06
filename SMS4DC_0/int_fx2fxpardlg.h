#if !defined(AFX_INT_FX2FXPARDLG_H__2585D44A_4285_46B6_AADA_0C437142EE30__INCLUDED_)
#define AFX_INT_FX2FXPARDLG_H__2585D44A_4285_46B6_AADA_0C437142EE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_FX2FXparDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_FX2FXparDLG dialog

class CInt_FX2FXparDLG : public CDialog
{
// Construction
public:
	CInt_FX2FXparDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInt_FX2FXparDLG)
	enum { IDD = IDD_Int_FX2FXparDLG };
	CComboBox	m_Clutter;
	double	m_beta;
	double	m_D;
	double	m_dN;
	double	m_F;
	double	m_N0;
	double	m_time;
	double	m_Pressure;
	double	m_TempC;
	//}}AFX_DATA

double m_ha_Clutter, m_dk_Clutter;
BOOL m_flagAvWo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_FX2FXparDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInt_FX2FXparDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOClutterX();
	afx_msg void OnRADIO1AvX();
	afx_msg void OnRADIO1WoX();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_FX2FXPARDLG_H__2585D44A_4285_46B6_AADA_0C437142EE30__INCLUDED_)
