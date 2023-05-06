// SelRecord.cpp : implementation file
//

#include "stdafx.h"
#include "IFICImport.h"
#include "SelRecord.h"
#include "columns.h"    // CColumns collection object header file.
#include "column.h"     // CColumn object header file.
#include "_recordset.h" // C_Recordset object header file.
#include "fields.h"     // CFields collection object header file.
#include "field.h"      // CFields object header file.
#include <comdef.h>
#include <AfxDisp.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelRecord dialog


CSelRecord::CSelRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CSelRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelRecord)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelRecord)
	DDX_Control(pDX, IDC_ADODC1, m_Recs);
	DDX_Control(pDX, IDC_DATAGRID2, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelRecord, CDialog)
	//{{AFX_MSG_MAP(CSelRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelRecord message handlers

BOOL CSelRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Grid.GetColumns().Remove(_variant_t((short)1));
	for(int i=0; i<m_Recs.GetRecordset().GetFields().GetCount(); i++)
	{
		m_Grid.GetColumns().Add(i);
		CField Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)i));
		m_Grid.GetColumns().GetItem(_variant_t((short)i)).SetCaption(Field.GetName());
		m_Grid.GetColumns().GetItem(_variant_t((short)i)).SetDataField(Field.GetName());
	}
	m_Grid.GetColumns().Remove(_variant_t((short)i));
	m_Recs.SetRecordSource(m_SQL);
	m_Recs.Refresh();	
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelRecord::OnOK() 
{
	CField Field;
	VARIANT TempVar;
	CString str;
	CDatabase DB;
	long MaxID;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)0));
	TempVar=Field.GetValue();
	m_SelectID=TempVar.lVal;
	DB.Open("WorkDB",false,false,_T("ODBC;"),false);
	CRecordset Sttable;
	Sttable.m_pDatabase=&DB;
	Sttable.Open(CRecordset::snapshot,"select max(IDst) as maxst from sttable");
	Sttable.GetFieldValue((int)0,str);
	MaxID=atol(str)+1;
	CString STTP, STname, Antenna, Polarization="", SQL1, SQL2, AntDir;
	int SRV=1;
	double TXFreq, STlon_deg, STlat_deg, Power_eirp, ANTgain, Azimuth=0, BWh=0, BWv=0, Elevation, STh_agl;

	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)1));	TempVar=Field.GetValue();	TXFreq=TempVar.dblVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)2));	TempVar=Field.GetValue();	STTP=TempVar.bstrVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)3));	TempVar=Field.GetValue();	STname=TempVar.bstrVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)4));	TempVar=Field.GetValue();	STlon_deg=TempVar.dblVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)5));	TempVar=Field.GetValue();	STlat_deg=TempVar.dblVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)6));	TempVar=Field.GetValue();	Power_eirp=pow(10.0,TempVar.dblVal/10.0);
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)7));	TempVar=Field.GetValue();	Azimuth=TempVar.dblVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)8));	TempVar=Field.GetValue();	ANTgain=TempVar.dblVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)9));	TempVar=Field.GetValue();	BWh=TempVar.dblVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)10));	TempVar=Field.GetValue();	Elevation=TempVar.dblVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)11));	TempVar=Field.GetValue();	Polarization=TempVar.bstrVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)12));	TempVar=Field.GetValue();	STh_agl=TempVar.dblVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)13));	TempVar=Field.GetValue();	Antenna=TempVar.bstrVal;
	Field=m_Recs.GetRecordset().GetFields().GetItem(_variant_t((short)14));	TempVar=Field.GetValue();	AntDir=TempVar.bstrVal;

	CDatabase DB2;
	DB2.Open("SMS_DB",false,false,_T("ODBC;"),false);
	CRecordset Sttable2;
	Sttable2.m_pDatabase=&DB2;
	SQL2.Format("select StSrv from StClass where StClassID like \'%2s%%\'", STTP);
	Sttable2.Open(CRecordset::snapshot,SQL2);
	Sttable2.GetFieldValue((int)0,str);
	Sttable2.Close();

	DB2.Close();
	SRV=atoi(str);
	//if(STTP=="FX") SRV="1";
	//else if(STTP=="FB") SRV="2";
	if(Polarization.GetLength()>1)
		Polarization="";
	if(AntDir.Left(2)=="ND")
		BWh=BWv=360.;
	SQL2="INSERT INTO sttable (IDst, TXfreq, STTP, STname, STlon_deg, STlat_deg, Power_eirp, Azimuth, ";
	SQL2+="ANTgain, BWh, BWv, Elevation, Polarization, STh_agl, Antenna, SRV) ";
	SQL1.Format("SELECT %ld as a, %lf as b, \'%s\' as c, \'%s\' as d, %lf as e, ",MaxID, TXFreq, STTP, STname, STlon_deg);
	SQL2+=SQL1;
	SQL1.Format("%lf as f, %lf as g, %lf as h, %lf as i, %lf as j, %lf as o, ",STlat_deg, Power_eirp, Azimuth, ANTgain, BWh, BWv);
	SQL2+=SQL1;
	SQL1.Format("%lf as k, \'%s\' as l, %lf as m, \'DEFAULT\' as n, %d as q",Elevation, Polarization, STh_agl, SRV);
	SQL2+=SQL1;
	DB.ExecuteSQL(SQL2);
	DB.Close();
	
	CDialog::OnOK();
}
