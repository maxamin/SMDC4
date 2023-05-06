#if !defined(AFX_DGRID_H__EEDF9EE2_E2BB_4D85_8A5E_3BAC6E046AE5__INCLUDED_)
#define AFX_DGRID_H__EEDF9EE2_E2BB_4D85_8A5E_3BAC6E046AE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DGrid.h : header file
//


#include "msflexgrid.h"
#include <afxdb.h>

typedef struct{
	CString Name;
	BOOL Indexed;
	unsigned long FType;
}Fld;

typedef struct{
    BOOL Selected;
    int index;
}Status;

/////////////////////////////////////////////////////////////////////////////
// CDGrid window

class CDGrid : public CMSFlexGrid
{
public:
	CMSFlexGrid *m_FlexGrid;

	int m_OldRow,
		m_OldCol,
		m_NewCol,
		m_NewRow,
		m_TextRow,
		m_TextCol,
		m_MaxRowSel,
		m_MaxColSel,
		m_Selcount;
	CString m_DB, m_Tbl;
	BOOL m_Entrance, m_RdOnly, m_RowDirty, m_Adding,m_Navigator;

	Fld m_fields[1000];
	Status m_ColStat[1000], m_RowStat[100000];
	CString m_Sel[10000];
	CDatabase m_mydb;
	CRecordset m_rs;

	BOOL LoadData();
	void GetSelection();
	int FindOrigRow(int j);
	CString GetRowText(int j);
	CString ExtractTable(CString Tb);

// Construction
public:
	CDGrid();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDGrid();

	// Generated message map functions
public:
	//{{AFX_MSG(CDGrid)
		afx_msg void OnMouseUp(short Button, short Shift, long x, long y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DGRID_H__EEDF9EE2_E2BB_4D85_8A5E_3BAC6E046AE5__INCLUDED_)
