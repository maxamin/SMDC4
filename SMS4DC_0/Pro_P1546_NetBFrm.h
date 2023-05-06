#if !defined(AFX_PRO_P1546_NETBFRM_H__71EEF81B_09BB_4CBB_82DF_80B9ACA0CB5C__INCLUDED_)
#define AFX_PRO_P1546_NETBFRM_H__71EEF81B_09BB_4CBB_82DF_80B9ACA0CB5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1546_NetBFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_NetBFrm frame

class CPro_P1546_NetBFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1546_NetBFrm)
protected:
	CPro_P1546_NetBFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1546_NetBFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1546_NetBFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1546_NetBFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1546_NETBFRM_H__71EEF81B_09BB_4CBB_82DF_80B9ACA0CB5C__INCLUDED_)
