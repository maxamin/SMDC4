#if !defined(AFX_ALLOCATIONS_DRAWFRM_H__30D23B23_DA36_43C5_A0FE_55B1CD9CF431__INCLUDED_)
#define AFX_ALLOCATIONS_DRAWFRM_H__30D23B23_DA36_43C5_A0FE_55B1CD9CF431__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Allocations_DrawFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawFrm frame

class CAllocations_DrawFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CAllocations_DrawFrm)
protected:
	CAllocations_DrawFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllocations_DrawFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAllocations_DrawFrm();

	// Generated message map functions
	//{{AFX_MSG(CAllocations_DrawFrm)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALLOCATIONS_DRAWFRM_H__30D23B23_DA36_43C5_A0FE_55B1CD9CF431__INCLUDED_)
