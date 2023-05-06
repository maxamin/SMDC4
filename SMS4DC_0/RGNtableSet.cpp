// RGNtableSet.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "RGNtableSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGNtableSet

IMPLEMENT_DYNAMIC(CRGNtableSet, CRecordset)

CRGNtableSet::CRGNtableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRGNtableSet)
	m_REGION = 0;
	m_FRQ_LO = 0.0;
	m_FRQ_HI = 0.0;
	m_PS1 = _T("");
	m_FOTP1 = _T("");
	m_PS2 = _T("");
	m_FOTP2 = _T("");
	m_PS3 = _T("");
	m_FOTP3 = _T("");
	m_PS4 = _T("");
	m_FOTP4 = _T("");
	m_PS5 = _T("");
	m_FOTP5 = _T("");
	m_PS6 = _T("");
	m_FOTP6 = _T("");
	m_SS1 = _T("");
	m_FOTS1 = _T("");
	m_SS2 = _T("");
	m_FOTS2 = _T("");
	m_SS3 = _T("");
	m_FOTS3 = _T("");
	m_SS4 = _T("");
	m_FOTS4 = _T("");
	m_SS5 = _T("");
	m_FOTS5 = _T("");
	m_SS6 = _T("");
	m_FOTS6 = _T("");
	m_FOT = _T("");
	m_nFields = 28;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;


	CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\tRegion1234.tmp");
	CString Region1234str;
	FILE *fp = fopen(FileInfo,"rt");
	if(fp)
	{
		fscanf( fp, "%s", Region1234str);
		fclose(fp);
	}
	m_Region1234 = atoi(Region1234str);
}


CString CRGNtableSet::GetDefaultConnect()
{
//	return _T("ODBC;DSN=WorkDB");
	return ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
}

CString CRGNtableSet::GetDefaultSQL()
{
	CString Tb;
	Tb.Format("ITU_PLAN_R%d order by FRQ_LO",m_Region1234);
	return Tb;
//	return _T("[ITU_PLAN_R1]");
}

void CRGNtableSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRGNtableSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[REGION]"), m_REGION);
	RFX_Double(pFX, _T("[FRQ_LO]"), m_FRQ_LO);
	RFX_Double(pFX, _T("[FRQ_HI]"), m_FRQ_HI);
	RFX_Text(pFX, _T("[PS1]"), m_PS1);
	RFX_Text(pFX, _T("[FOTP1]"), m_FOTP1);
	RFX_Text(pFX, _T("[PS2]"), m_PS2);
	RFX_Text(pFX, _T("[FOTP2]"), m_FOTP2);
	RFX_Text(pFX, _T("[PS3]"), m_PS3);
	RFX_Text(pFX, _T("[FOTP3]"), m_FOTP3);
	RFX_Text(pFX, _T("[PS4]"), m_PS4);
	RFX_Text(pFX, _T("[FOTP4]"), m_FOTP4);
	RFX_Text(pFX, _T("[PS5]"), m_PS5);
	RFX_Text(pFX, _T("[FOTP5]"), m_FOTP5);
	RFX_Text(pFX, _T("[PS6]"), m_PS6);
	RFX_Text(pFX, _T("[FOTP6]"), m_FOTP6);
	RFX_Text(pFX, _T("[SS1]"), m_SS1);
	RFX_Text(pFX, _T("[FOTS1]"), m_FOTS1);
	RFX_Text(pFX, _T("[SS2]"), m_SS2);
	RFX_Text(pFX, _T("[FOTS2]"), m_FOTS2);
	RFX_Text(pFX, _T("[SS3]"), m_SS3);
	RFX_Text(pFX, _T("[FOTS3]"), m_FOTS3);
	RFX_Text(pFX, _T("[SS4]"), m_SS4);
	RFX_Text(pFX, _T("[FOTS4]"), m_FOTS4);
	RFX_Text(pFX, _T("[SS5]"), m_SS5);
	RFX_Text(pFX, _T("[FOTS5]"), m_FOTS5);
	RFX_Text(pFX, _T("[SS6]"), m_SS6);
	RFX_Text(pFX, _T("[FOTS6]"), m_FOTS6);
	RFX_Text(pFX, _T("[FOT]"), m_FOT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRGNtableSet diagnostics

#ifdef _DEBUG
void CRGNtableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRGNtableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
