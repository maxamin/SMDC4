#if !defined(AFX_ANT3DFRM_H__11189E78_254D_42F1_B04B_59E8B75CEE5A__INCLUDED_)
#define AFX_ANT3DFRM_H__11189E78_254D_42F1_B04B_59E8B75CEE5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ant3DFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnt3DFrm frame

class CAnt3DFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CAnt3DFrm)
protected:
	CAnt3DFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnt3DFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAnt3DFrm();

	// Generated message map functions
	//{{AFX_MSG(CAnt3DFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANT3DFRM_H__11189E78_254D_42F1_B04B_59E8B75CEE5A__INCLUDED_)
