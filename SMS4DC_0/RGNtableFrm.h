#if !defined(AFX_RGNTABLEFRM_H__11D0E78C_2A1E_4929_BE42_89830FDDAF60__INCLUDED_)
#define AFX_RGNTABLEFRM_H__11D0E78C_2A1E_4929_BE42_89830FDDAF60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGNtableFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGNtableFrm frame

class CRGNtableFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRGNtableFrm)
protected:
	CRGNtableFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGNtableFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRGNtableFrm();

	// Generated message map functions
	//{{AFX_MSG(CRGNtableFrm)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGNTABLEFRM_H__11D0E78C_2A1E_4929_BE42_89830FDDAF60__INCLUDED_)
