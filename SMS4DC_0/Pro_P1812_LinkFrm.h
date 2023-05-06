#if !defined(AFX_PRO_P1812_LINKFRM_H__F25E72B3_F8FB_4474_984C_CF70F41A6109__INCLUDED_)
#define AFX_PRO_P1812_LINKFRM_H__F25E72B3_F8FB_4474_984C_CF70F41A6109__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1812_LinkFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_LinkFrm frame

class CPro_P1812_LinkFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1812_LinkFrm)
protected:
	CPro_P1812_LinkFrm();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1812_LinkFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1812_LinkFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1812_LinkFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1812_LINKFRM_H__F25E72B3_F8FB_4474_984C_CF70F41A6109__INCLUDED_)
