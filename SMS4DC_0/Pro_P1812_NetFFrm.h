#if !defined(AFX_PRO_P1812_NETFFRM_H__68F41789_CA82_4D5A_AB28_27B263A08D8E__INCLUDED_)
#define AFX_PRO_P1812_NETFFRM_H__68F41789_CA82_4D5A_AB28_27B263A08D8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1812_NetFFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_NetFFrm frame

class CPro_P1812_NetFFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1812_NetFFrm)
protected:
	CPro_P1812_NetFFrm();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1812_NetFFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1812_NetFFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1812_NetFFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1812_NETFFRM_H__68F41789_CA82_4D5A_AB28_27B263A08D8E__INCLUDED_)
