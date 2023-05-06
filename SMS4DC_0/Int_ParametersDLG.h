#if !defined(AFX_INT_PARAMETERSDLG_H__CD5A7E91_00B2_42A8_B450_B131E952D64D__INCLUDED_)
#define AFX_INT_PARAMETERSDLG_H__CD5A7E91_00B2_42A8_B450_B131E952D64D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_ParametersDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_ParametersDLG dialog

class CInt_ParametersDLG : public CDialog
{
// Construction
public:
	CInt_ParametersDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInt_ParametersDLG)
	enum { IDD = IDD_Int_ParametersDLG };
	CComboBox	m_COMBO_method;
	double	m_D;
	double	m_Emin;
	double	m_F;
	double	m_T;
	double	m_L;
	int		m_method;
	BOOL	m_AntDisc;
	BOOL	m_PolDisc;
	double	m_EDIT_PolDisc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_ParametersDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInt_ParametersDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOmethod();
	afx_msg void OnCHECKPol();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_PARAMETERSDLG_H__CD5A7E91_00B2_42A8_B450_B131E952D64D__INCLUDED_)
