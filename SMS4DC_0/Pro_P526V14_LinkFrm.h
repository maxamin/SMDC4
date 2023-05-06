#if !defined(AFX_PRO_P526V14_LINKFRM_H__D055418E_79CA_479F_BC5F_646EB795CA33__INCLUDED_)
#define AFX_PRO_P526V14_LINKFRM_H__D055418E_79CA_479F_BC5F_646EB795CA33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P526V14_LinkFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P526V14_LinkFrm frame

class CPro_P526V14_LinkFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P526V14_LinkFrm)
protected:
	CPro_P526V14_LinkFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P526V14_LinkFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P526V14_LinkFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P526V14_LinkFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P526V14_LINKFRM_H__D055418E_79CA_479F_BC5F_646EB795CA33__INCLUDED_)
