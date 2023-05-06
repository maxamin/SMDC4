#if !defined(AFX_SRVTABLESET_H__56D00186_6D60_4684_A3E3_7C7A87CAD90B__INCLUDED_)
#define AFX_SRVTABLESET_H__56D00186_6D60_4684_A3E3_7C7A87CAD90B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SRVtableSet.h : header file
//
#include "afxdb.h"

/////////////////////////////////////////////////////////////////////////////
// CSRVtableSet recordset

class CSRVtableSet : public CRecordset
{
public:
	CSRVtableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSRVtableSet)

// Field/Param Data
	//{{AFX_FIELD(CSRVtableSet, CRecordset)
	long	m_ID;
	CString	m_SRV_CODE;
	long	m_SRV_R;
	long	m_SRV_G;
	long	m_SRV_B;
	CString	m_SRV_NAME_P_en;
	CString	m_SRV_NAME_S_en;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRVtableSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVTABLESET_H__56D00186_6D60_4684_A3E3_7C7A87CAD90B__INCLUDED_)
