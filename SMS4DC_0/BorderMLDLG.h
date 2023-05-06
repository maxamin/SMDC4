#if !defined(AFX_BORDERMLDLG_H__26FBCE1A_0EA6_44B9_A930_A9B7F0C288F4__INCLUDED_)
#define AFX_BORDERMLDLG_H__26FBCE1A_0EA6_44B9_A930_A9B7F0C288F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BorderMLDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBorderMLDLG dialog

class CBorderMLDLG : public CDialog
{
// Construction
public:
	CBorderMLDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBorderMLDLG)
	enum { IDD = IDD_BorderMLDLG };
	CString	m_Name;
	CString	m_Lat;
	CString	m_Lon;
	CString	m_cty;
	int		m_mobile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorderMLDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBorderMLDLG)
	afx_msg void OnRadio1();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORDERMLDLG_H__26FBCE1A_0EA6_44B9_A930_A9B7F0C288F4__INCLUDED_)
