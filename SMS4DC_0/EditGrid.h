#if !defined(AFX_EDITGRID_H__98B002B9_291A_4298_A03E_4D194658066C__INCLUDED_)
#define AFX_EDITGRID_H__98B002B9_291A_4298_A03E_4D194658066C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditGrid window
#include "msflexgrid.h"
#include "EditWnd.h"

class CEditGrid : public CMSFlexGrid
{
// Construction
public:
	CEditGrid();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditGrid)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditGrid();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditGrid)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
	afx_msg void OnUpdateGrid();
public:
	afx_msg void OnDblClickGrid();

	DECLARE_EVENTSINK_MAP()

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
     CEditWnd m_edit;
     long m_lBorderWidth;
     long m_lBorderHeight;

     int m_nLogX;
     int m_nLogY; 

	 long m_r, m_c;
	 bool m_ReadOnly;


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITGRID_H__98B002B9_291A_4298_A03E_4D194658066C__INCLUDED_)
