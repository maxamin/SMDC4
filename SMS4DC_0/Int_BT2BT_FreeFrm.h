#if !defined(AFX_INT_BT2BT_FREEFRM_H__32DB7633_915A_42EF_A1FB_89E30FADCD79__INCLUDED_)
#define AFX_INT_BT2BT_FREEFRM_H__32DB7633_915A_42EF_A1FB_89E30FADCD79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_BT2BT_FreeFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_BT2BT_FreeFrm frame

class CInt_BT2BT_FreeFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CInt_BT2BT_FreeFrm)
protected:
	CInt_BT2BT_FreeFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_BT2BT_FreeFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInt_BT2BT_FreeFrm();

	// Generated message map functions
	//{{AFX_MSG(CInt_BT2BT_FreeFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_BT2BT_FREEFRM_H__32DB7633_915A_42EF_A1FB_89E30FADCD79__INCLUDED_)
