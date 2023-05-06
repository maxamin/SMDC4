#if !defined(AFX_MAINMAPFRM_H__3664E838_ACE9_4FC3_AE40_BFF49D49237D__INCLUDED_)
#define AFX_MAINMAPFRM_H__3664E838_ACE9_4FC3_AE40_BFF49D49237D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainMapFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainMapFrm frame

class CMainMapFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMainMapFrm)
protected:
	CMainMapFrm();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainMapFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMainMapFrm();

	// Generated message map functions
	//{{AFX_MSG(CMainMapFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINMAPFRM_H__3664E838_ACE9_4FC3_AE40_BFF49D49237D__INCLUDED_)
