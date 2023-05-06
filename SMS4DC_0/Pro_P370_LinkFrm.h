#if !defined(AFX_PRO_P370_LINKFRM_H__40539406_83ED_4F0F_8464_C1B0D0D25C42__INCLUDED_)
#define AFX_PRO_P370_LINKFRM_H__40539406_83ED_4F0F_8464_C1B0D0D25C42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P370_LinkFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_LinkFrm frame

class CPro_P370_LinkFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P370_LinkFrm)
protected:
	CPro_P370_LinkFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P370_LinkFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P370_LinkFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P370_LinkFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P370_LINKFRM_H__40539406_83ED_4F0F_8464_C1B0D0D25C42__INCLUDED_)
