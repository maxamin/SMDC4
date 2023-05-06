#if !defined(AFX_FRESNELDLG_H__3216950C_B0E0_46D5_AFEA_D0961F84566C__INCLUDED_)
#define AFX_FRESNELDLG_H__3216950C_B0E0_46D5_AFEA_D0961F84566C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FresnelDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFresnelDLG dialog

class CFresnelDLG : public CDialog
{
// Construction
public:
	CFresnelDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFresnelDLG)
	enum { IDD = IDD_FresnelDLG };
	int		m_Fresnel;
	double	m_FrqMHz;
	double	m_RxH;
	double	m_TxH;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFresnelDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFresnelDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRESNELDLG_H__3216950C_B0E0_46D5_AFEA_D0961F84566C__INCLUDED_)
