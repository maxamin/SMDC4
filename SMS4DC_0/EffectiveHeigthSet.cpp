// EffectiveHeigthSet.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "EffectiveHeigthSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthSet

IMPLEMENT_DYNAMIC(CEffectiveHeigthSet, CRecordset)

CEffectiveHeigthSet::CEffectiveHeigthSet(CString SQL,CDatabase* pdb)
	: CRecordset(pdb),m_SQL_SET(SQL)
{
	//{{AFX_FIELD_INIT(CEffectiveHeigthSet)
	m_AntID = 0;
	m_Azm = 0.0;
	m_EffHgt = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CEffectiveHeigthSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=WorkDB");
	return ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

}

CString CEffectiveHeigthSet::GetDefaultSQL()
{
	return m_SQL_SET;
//	return _T("[AntHgt]");
}

void CEffectiveHeigthSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEffectiveHeigthSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[AntID]"), m_AntID);
	RFX_Double(pFX, _T("[Azm]"), m_Azm);
	RFX_Long(pFX, _T("[EffHgt]"), m_EffHgt);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthSet diagnostics

#ifdef _DEBUG
void CEffectiveHeigthSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEffectiveHeigthSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
