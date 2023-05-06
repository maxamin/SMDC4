#if !defined(AFX_PRO_LOS_AREAFRM_H__3629CEC3_9CB0_498E_876A_C4944A78207F__INCLUDED_)
#define AFX_PRO_LOS_AREAFRM_H__3629CEC3_9CB0_498E_876A_C4944A78207F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_LoS_AreaFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaFrm frame

class CPro_LoS_AreaFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_LoS_AreaFrm)
protected:
	CPro_LoS_AreaFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_LoS_AreaFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_LoS_AreaFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_LoS_AreaFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_LOS_AREAFRM_H__3629CEC3_9CB0_498E_876A_C4944A78207F__INCLUDED_)
