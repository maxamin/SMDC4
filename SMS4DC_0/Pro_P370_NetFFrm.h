#if !defined(AFX_PRO_P370_NETFFRM_H__69AC1DF1_86C5_432A_B10F_1070AFF47137__INCLUDED_)
#define AFX_PRO_P370_NETFFRM_H__69AC1DF1_86C5_432A_B10F_1070AFF47137__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P370_NetFFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_NetFFrm frame

class CPro_P370_NetFFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P370_NetFFrm)
protected:
	CPro_P370_NetFFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P370_NetFFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P370_NetFFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P370_NetFFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P370_NETFFRM_H__69AC1DF1_86C5_432A_B10F_1070AFF47137__INCLUDED_)
