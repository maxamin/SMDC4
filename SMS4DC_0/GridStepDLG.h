#if !defined(AFX_GRIDSTEPDLG_H__D280828A_51DA_472A_8533_576C87CF79AA__INCLUDED_)
#define AFX_GRIDSTEPDLG_H__D280828A_51DA_472A_8533_576C87CF79AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridStepDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridStepDLG dialog

class CGridStepDLG : public CDialog
{
// Construction
public:
	CGridStepDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGridStepDLG)
	enum { IDD = IDD_GridStepDLG };
	double	m_GridStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridStepDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGridStepDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDSTEPDLG_H__D280828A_51DA_472A_8533_576C87CF79AA__INCLUDED_)
