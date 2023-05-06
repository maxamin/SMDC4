#if !defined(AFX_FXM_F_D_RNGDLG_H__F7E3E3D6_8A08_4ED1_BF53_3E0E267210A1__INCLUDED_)
#define AFX_FXM_F_D_RNGDLG_H__F7E3E3D6_8A08_4ED1_BF53_3E0E267210A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FXM_F_D_rngDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFXM_F_D_rngDLG dialog

class CFXM_F_D_rngDLG : public CDialog
{
// Construction
public:
	CFXM_F_D_rngDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFXM_F_D_rngDLG)
	enum { IDD = IDD_FXM_F_D_rngDLG };
	double	m_D;
	double	m_Emin;
	double	m_F;
	BOOL	m_Emergency;
	//}}AFX_DATA

	BOOL	m_flag;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFXM_F_D_rngDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFXM_F_D_rngDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FXM_F_D_RNGDLG_H__F7E3E3D6_8A08_4ED1_BF53_3E0E267210A1__INCLUDED_)
