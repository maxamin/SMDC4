#if !defined(AFX_PRO_FREE_NETFFRM_H__D8BF288F_BAB1_4E91_954C_AA7C1E9DADE3__INCLUDED_)
#define AFX_PRO_FREE_NETFFRM_H__D8BF288F_BAB1_4E91_954C_AA7C1E9DADE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_Free_NetFFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_NetFFrm frame

class CPro_Free_NetFFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_Free_NetFFrm)
protected:
	CPro_Free_NetFFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_Free_NetFFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_Free_NetFFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_Free_NetFFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_FREE_NETFFRM_H__D8BF288F_BAB1_4E91_954C_AA7C1E9DADE3__INCLUDED_)
