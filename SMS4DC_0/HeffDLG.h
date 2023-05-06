//{{AFX_INCLUDES()
#include "EditGrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_HEFFDLG_H__6BEF312D_9EA9_4E7D_985F_65FBB3D212A4__INCLUDED_)
#define AFX_HEFFDLG_H__6BEF312D_9EA9_4E7D_985F_65FBB3D212A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeffDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHeffDLG dialog

class CHeffDLG : public CDialog
{
// Construction
public:
	CHeffDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHeffDLG)
	enum { IDD = IDD_HeffDLG };
	CBitmapButton	m_BUTTON_Save;
	CString	m_maxH;
	double	m_maxH2;
	CEditGrid	m_grid;
	//}}AFX_DATA
	long m_AntID , m_AntCatID, m_num;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeffDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHeffDLG)
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEFFDLG_H__6BEF312D_9EA9_4E7D_985F_65FBB3D212A4__INCLUDED_)
