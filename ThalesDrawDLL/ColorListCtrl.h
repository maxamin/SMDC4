#if !defined(AFX_COLORLISTCTRL_H__870FDFB2_C5CC_45CF_956B_56ADECBFE241__INCLUDED_)
#define AFX_COLORLISTCTRL_H__870FDFB2_C5CC_45CF_956B_56ADECBFE241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl window

class CColorListCtrl : public CListCtrl
{
// Construction
public:
	CColorListCtrl();

// Attributes
public:
	COLORREF m_colRow1;
	COLORREF m_colRow2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorListCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLISTCTRL_H__870FDFB2_C5CC_45CF_956B_56ADECBFE241__INCLUDED_)
