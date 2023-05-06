#if !defined(AFX_AREA3DFRM_H__D90D27A4_77C8_48E9_9461_BFF85B96DF46__INCLUDED_)
#define AFX_AREA3DFRM_H__D90D27A4_77C8_48E9_9461_BFF85B96DF46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Area3DFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArea3DFrm frame

class CArea3DFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CArea3DFrm)
protected:
	CArea3DFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArea3DFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CArea3DFrm();

	// Generated message map functions
	//{{AFX_MSG(CArea3DFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREA3DFRM_H__D90D27A4_77C8_48E9_9461_BFF85B96DF46__INCLUDED_)
