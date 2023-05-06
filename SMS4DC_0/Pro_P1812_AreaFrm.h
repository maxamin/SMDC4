#if !defined(AFX_PRO_P1812_AREAFRM_H__CFFC99BB_9738_4071_8AD2_A8C48A828FDC__INCLUDED_)
#define AFX_PRO_P1812_AREAFRM_H__CFFC99BB_9738_4071_8AD2_A8C48A828FDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1812_AreaFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_AreaFrm frame

class CPro_P1812_AreaFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1812_AreaFrm)
protected:
	CPro_P1812_AreaFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1812_AreaFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1812_AreaFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1812_AreaFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1812_AREAFRM_H__CFFC99BB_9738_4071_8AD2_A8C48A828FDC__INCLUDED_)
