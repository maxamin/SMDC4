// AddStationRecSet.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "AddStationRecSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddStationRecSet

IMPLEMENT_DYNAMIC(CAddStationRecSet, CRecordset)

CAddStationRecSet::CAddStationRecSet(CString SQL,CDatabase* pdb)
	: CRecordset(pdb),m_SQL (SQL)
{
	//{{AFX_FIELD_INIT(CAddStationRecSet)
	m_IDst = 0;
	m_STname = _T("");
	m_STlat_deg = 0.0;
	m_STlon_deg = 0.0;
	m_STh_agl = 0.0;
	m_TXfreq = 0.0;
	m_Power_eirp = 0.0;
	m_Azimuth = 0.0;
	m_Elevation = 0.0;
	m_ANTgain = 0.0;
	m_BWh = 0.0;
	m_BWv = 0.0;
	m_Polarization = _T("");
	m_Antenna = _T("");
	m_InsertionLoss = 0.0;
	m_RxSensitivity = 0.0;

	m_Srv = 0;
	m_STTP = _T("");
	m_Emission = _T("");

	m_nFields = 19;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CAddStationRecSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=WorkDB");
}

CString CAddStationRecSet::GetDefaultSQL()
{
	return m_SQL;

	//	return _T("[STtable]");
}

void CAddStationRecSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAddStationRecSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[IDst]"), m_IDst);
	RFX_Text(pFX, _T("[STname]"), m_STname);
	RFX_Double(pFX, _T("[STlat_deg]"), m_STlat_deg);
	RFX_Double(pFX, _T("[STlon_deg]"), m_STlon_deg);
	RFX_Double(pFX, _T("[STh_agl]"), m_STh_agl);
	RFX_Double(pFX, _T("[TXfreq]"), m_TXfreq);
	RFX_Double(pFX, _T("[Power_eirp]"), m_Power_eirp);
	RFX_Double(pFX, _T("[Azimuth]"), m_Azimuth);
	RFX_Double(pFX, _T("[Elevation]"), m_Elevation);
	RFX_Double(pFX, _T("[ANTgain]"), m_ANTgain);
	RFX_Double(pFX, _T("[BWh]"), m_BWh);
	RFX_Double(pFX, _T("[BWv]"), m_BWv);
	RFX_Text(pFX, _T("[Polarization]"), m_Polarization);
	RFX_Text(pFX, _T("[Antenna]"), m_Antenna);
	RFX_Double(pFX, _T("[InsertionLoss]"), m_InsertionLoss);
	RFX_Double(pFX, _T("[RxSensitivity]"), m_RxSensitivity);
	RFX_Int(pFX, _T("[Srv]"), m_Srv);
	RFX_Text(pFX, _T("[STTP]"), m_STTP);
	RFX_Text(pFX, _T("[Emission]"), m_Emission);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAddStationRecSet diagnostics

#ifdef _DEBUG
void CAddStationRecSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAddStationRecSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
