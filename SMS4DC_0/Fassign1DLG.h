#if !defined(AFX_FASSIGN1DLG_H__A21F9AAA_0772_4F4B_962F_0D6774F76174__INCLUDED_)
#define AFX_FASSIGN1DLG_H__A21F9AAA_0772_4F4B_962F_0D6774F76174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Fassign1DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFassign1DLG dialog

class CFassign1DLG : public CDialog
{
// Construction
public:
	CFassign1DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFassign1DLG)
	enum { IDD = IDD_Fassign1DLG };
	double	m_CSR;
	double	m_Fmax;
	double	m_Fmin;
	double	m_Imax;
	double	m_Rkm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFassign1DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFassign1DLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASSIGN1DLG_H__A21F9AAA_0772_4F4B_962F_0D6774F76174__INCLUDED_)
