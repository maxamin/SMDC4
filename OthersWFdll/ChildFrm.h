// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__73990184_8725_4EDD_B6C4_51E99C52CC79__INCLUDED_)
#define AFX_CHILDFRM_H__73990184_8725_4EDD_B6C4_51E99C52CC79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SMS4DC.h"

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:
	CToolBar    m_wndToolBar;
	CString m_Lang;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT*pResult);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
    virtual void GetMessageString(UINT nID, CString& rMessage) const;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__73990184_8725_4EDD_B6C4_51E99C52CC79__INCLUDED_)
