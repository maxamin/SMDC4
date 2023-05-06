//{{AFX_INCLUDES()
#include "adodc.h"
#include "datagrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_SELRECORD_H__1825B4A7_33B0_417C_AC20_FDA424672A4B__INCLUDED_)
#define AFX_SELRECORD_H__1825B4A7_33B0_417C_AC20_FDA424672A4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelRecord dialog

class CSelRecord : public CDialog
{
// Construction
public:
	CSelRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelRecord)
	enum { IDD = IDD_SelectRecord };
	CAdodc	m_Recs;
	CDataGrid	m_Grid;
	//}}AFX_DATA
	CString m_SQL;
	long m_SelectID;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelRecord)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELRECORD_H__1825B4A7_33B0_417C_AC20_FDA424672A4B__INCLUDED_)
