#if !defined(AFX_RIGHTGRID_H__8D0CB781_FDD2_4357_AA04_6F3BBA0BA8F6__INCLUDED_)
#define AFX_RIGHTGRID_H__8D0CB781_FDD2_4357_AA04_6F3BBA0BA8F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RightGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRightGrid dialog

class CRightGrid : public CDialog
{
// Construction
public:
	CRightGrid(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRightGrid)
	enum { IDD = IDD_GRID };
	CDateTimeCtrl	m_Date1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRightGrid)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRightGrid)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTGRID_H__8D0CB781_FDD2_4357_AA04_6F3BBA0BA8F6__INCLUDED_)
