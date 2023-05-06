#if !defined(AFX_EFFECTIVEHEIGTHSET_H__2847B4CA_DC03_45C5_824B_09C92650A1C5__INCLUDED_)
#define AFX_EFFECTIVEHEIGTHSET_H__2847B4CA_DC03_45C5_824B_09C92650A1C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EffectiveHeigthSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthSet recordset

#include <afxdb.h>			// MFC ODBC database classes


class CEffectiveHeigthSet : public CRecordset
{
public:
	CEffectiveHeigthSet(CString SQL = _T("SELECT * FROM AntHgt"),CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEffectiveHeigthSet)

// Field/Param Data
	//{{AFX_FIELD(CEffectiveHeigthSet, CRecordset)
	long	m_AntID;
	double	m_Azm;
	long	m_EffHgt;
	//}}AFX_FIELD
	CString m_SQL_SET;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEffectiveHeigthSet)
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

#endif // !defined(AFX_EFFECTIVEHEIGTHSET_H__2847B4CA_DC03_45C5_824B_09C92650A1C5__INCLUDED_)
