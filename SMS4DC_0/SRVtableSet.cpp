// SRVtableSet.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "SRVtableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSRVtableSet

IMPLEMENT_DYNAMIC(CSRVtableSet, CRecordset)

CSRVtableSet::CSRVtableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSRVtableSet)
	m_ID = 0;
	m_SRV_CODE = _T("");
	m_SRV_R = 0;
	m_SRV_G = 0;
	m_SRV_B = 0;
	m_SRV_NAME_P_en = _T("");
	m_SRV_NAME_S_en = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CSRVtableSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=WorkDB");
	return ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
}

CString CSRVtableSet::GetDefaultSQL()
{
//	return _T("[SRVCode_Color_Name]");

	CString str = _T("");
	if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("En"))
		str = _T("SELECT ID, SRV_CODE, SRV_R, SRV_G, SRV_B, SRV_NAME_P_en, SRV_NAME_S_en FROM SRVCode_Color_Name  order by SRV_CODE;");
	else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Fr"))
		str = _T("SELECT ID, SRV_CODE, SRV_R, SRV_G, SRV_B, SRV_NAME_P_fr as SRV_NAME_P_en, SRV_NAME_S_fr as SRV_NAME_S_en FROM SRVCode_Color_Name  order by SRV_CODE;");

	else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Es"))  //940312
		str = _T("SELECT ID, SRV_CODE, SRV_R, SRV_G, SRV_B, SRV_NAME_P_es as SRV_NAME_P_en, SRV_NAME_S_es as SRV_NAME_S_en FROM SRVCode_Color_Name  order by SRV_CODE;");

	return str;
}

void CSRVtableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSRVtableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[SRV_CODE]"), m_SRV_CODE);
	RFX_Long(pFX, _T("[SRV_R]"), m_SRV_R);
	RFX_Long(pFX, _T("[SRV_G]"), m_SRV_G);
	RFX_Long(pFX, _T("[SRV_B]"), m_SRV_B);
	RFX_Text(pFX, _T("[SRV_NAME_P_en]"), m_SRV_NAME_P_en);
	RFX_Text(pFX, _T("[SRV_NAME_S_en]"), m_SRV_NAME_S_en);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSRVtableSet diagnostics

#ifdef _DEBUG
void CSRVtableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSRVtableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
