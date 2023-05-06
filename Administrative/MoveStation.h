//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_MOVESTATION_H__B0F47F70_18DB_4AD0_B76B_84CE1A0EF612__INCLUDED_)
#define AFX_MOVESTATION_H__B0F47F70_18DB_4AD0_B76B_84CE1A0EF612__INCLUDED_

#include "resource.h"
#include "Administrative.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoveStation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoveStation dialog

class CMoveStation : public CDialog
{
// Construction
public:
	CMoveStation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMoveStation)
	enum { IDD = IDD_MOVE_STATION };
	CMSHFlexGrid	m_Stations;
	//}}AFX_DATA
	CString m_CDBSTR;
	CString m_Service;
	CString m_Lang;
	long m_StID;
	bool m_Base;

	CString GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoveStation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMoveStation)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVESTATION_H__B0F47F70_18DB_4AD0_B76B_84CE1A0EF612__INCLUDED_)
