#if !defined(AFX_CHILDFRMAREA_H__640BE04B_B8A6_4306_B6E8_8DF6CDA7EE5E__INCLUDED_)
#define AFX_CHILDFRMAREA_H__640BE04B_B8A6_4306_B6E8_8DF6CDA7EE5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildFrmArea.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildFrmArea frame

class CChildFrmArea : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrmArea)
protected:
	CChildFrmArea();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrmArea)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChildFrmArea();

	// Generated message map functions
	//{{AFX_MSG(CChildFrmArea)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRMAREA_H__640BE04B_B8A6_4306_B6E8_8DF6CDA7EE5E__INCLUDED_)
