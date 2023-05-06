#if !defined(AFX_SMOOTHDLG_H__CE6B0F21_167D_44D6_A40D_28CAEAE49DD1__INCLUDED_)
#define AFX_SMOOTHDLG_H__CE6B0F21_167D_44D6_A40D_28CAEAE49DD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmoothDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSmoothDLG dialog

class CSmoothDLG : public CDialog
{
// Construction
public:
	CSmoothDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSmoothDLG)
	enum { IDD = IDD_SmoothDLG };
	CComboBox	m_List1;
	CString	m_kfactor;
	int		m_Type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmoothDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSmoothDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMOOTHDLG_H__CE6B0F21_167D_44D6_A40D_28CAEAE49DD1__INCLUDED_)
