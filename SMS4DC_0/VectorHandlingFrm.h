#if !defined(AFX_VECTORHANDLINGFRM_H__B199B92B_5D46_4845_AF0B_B188A529AFE6__INCLUDED_)
#define AFX_VECTORHANDLINGFRM_H__B199B92B_5D46_4845_AF0B_B188A529AFE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VectorHandlingFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingFrm frame

class CVectorHandlingFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CVectorHandlingFrm)
protected:
	CVectorHandlingFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVectorHandlingFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVectorHandlingFrm();

	// Generated message map functions
	//{{AFX_MSG(CVectorHandlingFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VECTORHANDLINGFRM_H__B199B92B_5D46_4845_AF0B_B188A529AFE6__INCLUDED_)
