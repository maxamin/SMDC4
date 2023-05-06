#if !defined(AFX_PRO_P1812_NETBFRM_H__6A3B054B_1DAB_4DBE_B73E_9CFC2B5D6A63__INCLUDED_)
#define AFX_PRO_P1812_NETBFRM_H__6A3B054B_1DAB_4DBE_B73E_9CFC2B5D6A63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1812_NetBFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_NetBFrm frame

class CPro_P1812_NetBFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1812_NetBFrm)
protected:
	CPro_P1812_NetBFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1812_NetBFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1812_NetBFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1812_NetBFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1812_NETBFRM_H__6A3B054B_1DAB_4DBE_B73E_9CFC2B5D6A63__INCLUDED_)
