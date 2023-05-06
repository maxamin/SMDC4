#if !defined(AFX_P452DLG_H__9A534A0D_FAEE_4DCD_B180_70A123CF96F5__INCLUDED_)
#define AFX_P452DLG_H__9A534A0D_FAEE_4DCD_B180_70A123CF96F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// P452DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CP452DLG dialog

class CP452DLG : public CDialog
{
// Construction
public:
	CP452DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CP452DLG)
	enum { IDD = IDD_P452DLG };
	CComboBox	m_Clutter;
	double	m_beta_e;
	double	m_dN;
	double	m_N0;
	double	m_time;
	double	m_Pressure;
	double	m_TempC;
	//}}AFX_DATA

double m_ha_Clutter, m_dk_Clutter;
BOOL m_flagAvWo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP452DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP452DLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOClutter();
	afx_msg void OnRADIO1Av();
	afx_msg void OnRADIO1Wo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P452DLG_H__9A534A0D_FAEE_4DCD_B180_70A123CF96F5__INCLUDED_)
