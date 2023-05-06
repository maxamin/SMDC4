#if !defined(AFX_TXRXFILTERSSET_H__DEE74B22_B6E4_4992_86E1_8A109E2FCDF5__INCLUDED_)
#define AFX_TXRXFILTERSSET_H__DEE74B22_B6E4_4992_86E1_8A109E2FCDF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TxRxFiltersSet.h : header file
//

#include <afxdb.h>			// MFC ODBC database classes

/////////////////////////////////////////////////////////////////////////////
// CTxRxFiltersSet recordset

class CTxRxFiltersSet : public CRecordset
{
public:
	CTxRxFiltersSet(CString DBSTR,CString SQL = _T("SELECT * FROM TxFilters"),CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTxRxFiltersSet)

// Field/Param Data
	//{{AFX_FIELD(CTxRxFiltersSet, CRecordset)
	long	m_EqID;
	double	m_CS;
	double	m_Att;
	//}}AFX_FIELD
	CString m_SQL_SET,m_CDBSTR;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxRxFiltersSet)
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

#endif // !defined(AFX_TXRXFILTERSSET_H__DEE74B22_B6E4_4992_86E1_8A109E2FCDF5__INCLUDED_)
