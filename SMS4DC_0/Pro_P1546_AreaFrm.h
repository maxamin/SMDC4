#if !defined(AFX_PRO_P1546_AREAFRM_H__1655B6C0_69D0_45DF_A64F_E1E0A4CD4CD0__INCLUDED_)
#define AFX_PRO_P1546_AREAFRM_H__1655B6C0_69D0_45DF_A64F_E1E0A4CD4CD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1546_AreaFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_AreaFrm frame

class CPro_P1546_AreaFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1546_AreaFrm)
protected:
	CPro_P1546_AreaFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1546_AreaFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1546_AreaFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1546_AreaFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1546_AREAFRM_H__1655B6C0_69D0_45DF_A64F_E1E0A4CD4CD0__INCLUDED_)
