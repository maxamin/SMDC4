// TxRxFiltersSet.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "TxRxFiltersSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTxRxFiltersSet

IMPLEMENT_DYNAMIC(CTxRxFiltersSet, CRecordset)

CTxRxFiltersSet::CTxRxFiltersSet(CString SQL,CDatabase* pdb)
	: CRecordset(pdb),m_SQL_SET(SQL)
{
	//{{AFX_FIELD_INIT(CTxRxFiltersSet)
	m_EqID = 0;
	m_CS = 0.0;
	m_Att = 0.0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CTxRxFiltersSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=WorkDB");
	return ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
}

CString CTxRxFiltersSet::GetDefaultSQL()
{
	return m_SQL_SET;
//	return _T("[Filters]");
}

void CTxRxFiltersSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTxRxFiltersSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[EqID]"), m_EqID);
	RFX_Double(pFX, _T("[CS]"), m_CS);
	RFX_Double(pFX, _T("[Att]"), m_Att);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTxRxFiltersSet diagnostics

#ifdef _DEBUG
void CTxRxFiltersSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTxRxFiltersSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
