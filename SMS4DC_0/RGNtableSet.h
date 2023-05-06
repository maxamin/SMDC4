#if !defined(AFX_RGNTABLESET_H__2AA610EB_2C3F_466B_9D8C_D8C67E635652__INCLUDED_)
#define AFX_RGNTABLESET_H__2AA610EB_2C3F_466B_9D8C_D8C67E635652__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGNtableSet.h : header file
//
#include "afxdb.h"

/////////////////////////////////////////////////////////////////////////////
// CRGNtableSet recordset

class CRGNtableSet : public CRecordset
{
public:
	CRGNtableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRGNtableSet)

int m_Region1234;

// Field/Param Data
	//{{AFX_FIELD(CRGNtableSet, CRecordset)
	long	m_REGION;
	double	m_FRQ_LO;
	double	m_FRQ_HI;
	CString	m_PS1;
	CString	m_FOTP1;
	CString	m_PS2;
	CString	m_FOTP2;
	CString	m_PS3;
	CString	m_FOTP3;
	CString	m_PS4;
	CString	m_FOTP4;
	CString	m_PS5;
	CString	m_FOTP5;
	CString	m_PS6;
	CString	m_FOTP6;
	CString	m_SS1;
	CString	m_FOTS1;
	CString	m_SS2;
	CString	m_FOTS2;
	CString	m_SS3;
	CString	m_FOTS3;
	CString	m_SS4;
	CString	m_FOTS4;
	CString	m_SS5;
	CString	m_FOTS5;
	CString	m_SS6;
	CString	m_FOTS6;
	CString	m_FOT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGNtableSet)
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

#endif // !defined(AFX_RGNTABLESET_H__2AA610EB_2C3F_466B_9D8C_D8C67E635652__INCLUDED_)
