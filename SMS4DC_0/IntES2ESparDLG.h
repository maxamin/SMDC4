#if !defined(AFX_INTES2ESPARDLG_H__C11C0079_276A_4355_8DAD_160B6B4444D5__INCLUDED_)
#define AFX_INTES2ESPARDLG_H__C11C0079_276A_4355_8DAD_160B6B4444D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IntES2ESparDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIntES2ESparDLG dialog

class CIntES2ESparDLG : public CDialog
{
// Construction
public:
	CIntES2ESparDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIntES2ESparDLG)
	enum { IDD = IDD_Int_ES2ESparDLG };
	CComboBox	m_Clutter;
	double	m_beta;
	double	m_D;
	double	m_dN;
	double	m_F;
	double	m_N0;
	double	m_time;
	double	m_EDIT_Pol;
	double	m_EDIT_uPr;
	double	m_Pressure;
	double	m_TempC;
	//}}AFX_DATA
	BOOL m_uPr;

double m_ha_Clutter, m_dk_Clutter;
BOOL m_flagAvWo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntES2ESparDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIntES2ESparDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnCHECKuPr();
	afx_msg void OnSelchangeCOMBOClutterZ();
	afx_msg void OnRADIO1AvZ();
	afx_msg void OnRADIO1WoZ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTES2ESPARDLG_H__C11C0079_276A_4355_8DAD_160B6B4444D5__INCLUDED_)
