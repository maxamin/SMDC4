#if !defined(AFX_KFACTOR_H__CD81C3C6_4AF8_4097_B78F_D95A9B07933E__INCLUDED_)
#define AFX_KFACTOR_H__CD81C3C6_4AF8_4097_B78F_D95A9B07933E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KFactor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKFactor dialog

class CKFactor : public CDialog
{
// Construction
public:
	CKFactor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKFactor)
	enum { IDD = IDD_kfactorDLG };
	CString	m_kfactorEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKFactor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKFactor)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KFACTOR_H__CD81C3C6_4AF8_4097_B78F_D95A9B07933E__INCLUDED_)
