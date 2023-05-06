// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__0B6FCA03_F56F_440A_A4A9_E5BA771D5FDB__INCLUDED_)
#define AFX_CHILDFRM_H__0B6FCA03_F56F_440A_A4A9_E5BA771D5FDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Administrative.h"
class CTreeviewView;


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();
	bool m_inProcess;
// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
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

public:
	CTreeviewView* GetRightPane();
// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT*pResult);//<<<<---------
	DECLARE_MESSAGE_MAP()


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__0B6FCA03_F56F_440A_A4A9_E5BA771D5FDB__INCLUDED_)
