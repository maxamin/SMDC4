#if !defined(AFX_SRVTABLEFRM_H__19695702_7DE9_474E_B96E_07BEC318E9D9__INCLUDED_)
#define AFX_SRVTABLEFRM_H__19695702_7DE9_474E_B96E_07BEC318E9D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SRVtableFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSRVtableFrm frame

class CSRVtableFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CSRVtableFrm)
protected:
	CSRVtableFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRVtableFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSRVtableFrm();

	// Generated message map functions
	//{{AFX_MSG(CSRVtableFrm)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVTABLEFRM_H__19695702_7DE9_474E_B96E_07BEC318E9D9__INCLUDED_)
