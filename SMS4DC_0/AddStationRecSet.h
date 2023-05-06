#if !defined(AFX_ADDSTATIONRECSET_H__FF704983_5EEB_49CE_94AE_7089A5FF7F73__INCLUDED_)
#define AFX_ADDSTATIONRECSET_H__FF704983_5EEB_49CE_94AE_7089A5FF7F73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddStationRecSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddStationRecSet recordset

#include "afxdb.h"

class CAddStationRecSet : public CRecordset
{
public:
//	CAddStationRecSet(CString SQL = _T("SELECT * FROM STtable"), CDatabase* pDatabase = NULL);
	CAddStationRecSet(CString SQL = _T("SELECT * FROM ") + ((CSMS4DCApp *)AfxGetApp())->Query_STtable() , CDatabase* pDatabase = NULL);
	
	DECLARE_DYNAMIC(CAddStationRecSet)

// Field/Param Data
	//{{AFX_FIELD(CAddStationRecSet, CRecordset)
	long	m_IDst;
	CString	m_STname;
	double	m_STlat_deg;
	double	m_STlon_deg;
	double	m_STh_agl;
	double	m_TXfreq;
	double	m_Power_eirp;
	double	m_Azimuth;
	double	m_Elevation;
	double	m_ANTgain;
	double	m_BWh;
	double	m_BWv;
	CString	m_Polarization;
	CString	m_Antenna;
	double	m_InsertionLoss;
	double	m_RxSensitivity;
	int	m_Srv;
	CString	m_STTP;
	CString	m_Emission;
	//}}AFX_FIELD
	CString m_SQL;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddStationRecSet)
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

#endif // !defined(AFX_ADDSTATIONRECSET_H__FF704983_5EEB_49CE_94AE_7089A5FF7F73__INCLUDED_)
