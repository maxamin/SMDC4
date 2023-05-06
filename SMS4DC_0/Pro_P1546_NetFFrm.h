#if !defined(AFX_PRO_P1546_NETFFRM_H__F0F022EE_6AF5_4AA3_AFB6_24902C676CE8__INCLUDED_)
#define AFX_PRO_P1546_NETFFRM_H__F0F022EE_6AF5_4AA3_AFB6_24902C676CE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1546_NetFFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_NetFFrm frame

class CPro_P1546_NetFFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1546_NetFFrm)
protected:
	CPro_P1546_NetFFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1546_NetFFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1546_NetFFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1546_NetFFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1546_NETFFRM_H__F0F022EE_6AF5_4AA3_AFB6_24902C676CE8__INCLUDED_)
