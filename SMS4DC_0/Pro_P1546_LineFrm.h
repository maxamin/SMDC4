#if !defined(AFX_PRO_P1546_LINEFRM_H__A45D19C6_12D9_4B46_8576_DEB3554279B5__INCLUDED_)
#define AFX_PRO_P1546_LINEFRM_H__A45D19C6_12D9_4B46_8576_DEB3554279B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1546_LineFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_LineFrm frame

class CPro_P1546_LineFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1546_LineFrm)
protected:
	CPro_P1546_LineFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1546_LineFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1546_LineFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1546_LineFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1546_LINEFRM_H__A45D19C6_12D9_4B46_8576_DEB3554279B5__INCLUDED_)
