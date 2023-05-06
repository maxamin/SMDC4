// MoveStation.cpp : implementation file
//

#include "stdafx.h"
#include "Administrative.h"
#include "MoveStation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoveStation dialog


CMoveStation::CMoveStation(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveStation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMoveStation)
	m_StID=-1;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMoveStation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoveStation)
	DDX_Control(pDX, IDC_STATIONS, m_Stations);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoveStation, CDialog)
	//{{AFX_MSG_MAP(CMoveStation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoveStation message handlers

BOOL CMoveStation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CDatabase DB;
	CRecordset RS;
	long i=1;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	m_Stations.SetRows(1);
	if(m_Service==_T("B"))
	{
		RS.Open(CRecordset::snapshot,_T("select StID, SiteID, SiteName, GeoLat, GeoLon, ClassStation from BCStation where LicID=-1"));
		m_Stations.SetCols(0,6);
		for(int j=1;j<6;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_Stations.SetTextMatrix(0,j,GetFieldName(&DB, _T("BCStation"), FldInfo.m_strName,_T("En"),&Unit));
		}
		while(true)
		{
			CString StID;
			if(RS.IsEOF()) break;
			m_Stations.SetRows(m_Stations.GetRows()+1);
			RS.GetFieldValue((short)0,StID);
			m_Stations.SetRowData(i,atol(StID));
			for(int j=1;j<6;j++)
			{
				CString Value;
				RS.GetFieldValue(j,Value);
				m_Stations.SetTextMatrix(i,j,Value);
			}
			RS.MoveNext();
			i++;
		}	
	}
	else if(m_Service==_T("F"))
	{
		RS.Open(CRecordset::snapshot,_T("select StID, SiteID, SiteName, GeoLat, GeoLon, ClassStation from Station where LicID=-1 and ClassStation='FX'"));
		m_Stations.SetCols(0,6);
		for(int j=1;j<6;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_Stations.SetTextMatrix(0,j,GetFieldName(&DB, _T("Station"), FldInfo.m_strName,_T("En"),&Unit));
		}
		while(true)
		{
			CString StID;
			if(RS.IsEOF()) break;
			m_Stations.SetRows(m_Stations.GetRows()+1);
			RS.GetFieldValue((short)0,StID);
			m_Stations.SetRowData(i,atol(StID));
			for(int j=1;j<6;j++)
			{
				CString Value;
				RS.GetFieldValue(j,Value);
				m_Stations.SetTextMatrix(i,j,Value);
			}
			RS.MoveNext();
			i++;
		}	
	}
	else if(m_Service==_T("MT"))
	{
		RS.Open(CRecordset::snapshot,_T("select StID, SiteID, SiteName, GeoLat, GeoLon, ClassStation from Station where LicID=-1 and ClassStation='FB'"));
		m_Stations.SetCols(0,6);
		for(int j=1;j<6;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_Stations.SetTextMatrix(0,j,GetFieldName(&DB, _T("Station"), FldInfo.m_strName,_T("En"),&Unit));
		}
		while(true)
		{
			CString StID;
			if(RS.IsEOF()) break;
			m_Stations.SetRows(m_Stations.GetRows()+1);
			RS.GetFieldValue((short)0,StID);
			m_Stations.SetRowData(i,atol(StID));
			for(j=1;j<6;j++)
			{
				CString Value;
				RS.GetFieldValue(j,Value);
				m_Stations.SetTextMatrix(i,j,Value);
			}
			RS.MoveNext();
			i++;
		}	
		RS.Close();
		RS.Open(CRecordset::snapshot,_T("select MobID, MobileID, MobName, GeoLat, GeoLon, ClassStation from Mobiles where LicID=-1"));
//		for(j=1;j<6;j++)
//		{
//			CODBCFieldInfo FldInfo;
//			CString Unit;
//			RS.GetODBCFieldInfo(j,FldInfo);
//			m_Stations.SetTextMatrix(0,j,GetFieldName(&DB, _T("Mobiles"), FldInfo.m_strName,_T("En"),&Unit));
//		}
		while(true)
		{
			CString StID;
			if(RS.IsEOF()) break;
			m_Stations.SetRows(m_Stations.GetRows()+1);
			RS.GetFieldValue((short)0,StID);
			m_Stations.SetRowData(i,atol(StID));
			for(j=1;j<6;j++)
			{
				CString Value;
				RS.GetFieldValue(j,Value);
				m_Stations.SetTextMatrix(i,j,Value);
			}
			RS.MoveNext();
			i++;
		}	
	}
	else if(m_Service==_T("Allotment"))
	{
		RS.Open(CRecordset::snapshot,_T("select AllotKey, Allot_name, geo_area, nb_sub_areas, NoticeType, SfnID, RefPlanCfg, Frequency/1000000 as Freq, Ctry, ClassStation from rrc_allotment where LicID=-1"));
		m_Stations.SetCols(0,10);
		for(int j=1;j<10;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_Stations.SetTextMatrix(0,j,GetFieldName(&DB, _T("rrc_allotment"), FldInfo.m_strName,_T("En"),&Unit));
		}
		while(true)
		{
			CString StID;
			if(RS.IsEOF()) break;
			m_Stations.SetRows(m_Stations.GetRows()+1);
			RS.GetFieldValue((short)0,StID);
			m_Stations.SetRowData(i,atol(StID));
			for(j=1;j<10;j++)
			{
				CString Value;
				RS.GetFieldValue(j,Value);
				m_Stations.SetTextMatrix(i,j,Value);
			}
			RS.MoveNext();
			i++;
		}	
	}
	else
	{
		RS.Open(CRecordset::snapshot,_T("select ntc_id, stn_name, sat_name, long_nom, long_dec, lat_dec, ctry from e_stn where LicID=-1"));
		m_Stations.SetCols(0,7);
		for(int j=1;j<7;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_Stations.SetTextMatrix(0,j,GetFieldName(&DB, _T("E-stn"), FldInfo.m_strName,_T("En"),&Unit));
		}
		while(true)
		{
			CString StID;
			if(RS.IsEOF()) break;
			m_Stations.SetRows(m_Stations.GetRows()+1);
			RS.GetFieldValue((short)0,StID);
			m_Stations.SetRowData(i,atol(StID));
			for(int j=1;j<7;j++)
			{
				CString Value;
				RS.GetFieldValue(j,Value);
				m_Stations.SetTextMatrix(i,j,Value);
			}
			RS.MoveNext();
			i++;
		}	
	}
	RS.Close();
	DB.Close();
	if(m_Stations.GetRows()==1)
	{
		EndDialog(false);
		return false;
	}
	m_Stations.SetFixedRows(1);
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CMoveStation::GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit)
{
	CRecordset	RS;
	RS.m_pDatabase=DB;
	CString FieldName,SQL;
	SQL.Format(_T("Select * from Fields where TableName='%s' and FieldName='%s'"), Table, OrigName);
	RS.Open(CRecordset::dynaset,SQL);
//	LangCode=/*((CSMS4DCApp *)AfxGetApp())->*/m_Lang;
	if(RS.GetRecordCount()>0)
	{
		if(m_Lang==_T("En"))
			RS.GetFieldValue(2,FieldName);
		if(m_Lang==_T("Fr"))
			RS.GetFieldValue(3,FieldName);
		if(m_Lang==_T("Es"))
			RS.GetFieldValue(4,FieldName);
		if(m_Lang==_T("Ch"))
			RS.GetFieldValue(5,FieldName);
		if(m_Lang==_T("Ru"))
			RS.GetFieldValue(6,FieldName);
		if(m_Lang==_T("Ar"))
			RS.GetFieldValue(7,FieldName);
		RS.GetFieldValue(8,*Unit);
	}
	RS.Close();
	return FieldName;
}

void CMoveStation::OnOK()
{
	if(m_Stations.GetRowSel()>-1)
	{
		m_StID=m_Stations.GetRowData(m_Stations.GetRowSel());
		if(m_Stations.GetTextMatrix(m_Stations.GetRowSel(),5).Left(2)==_T("FB"))
			m_Base=true;
		else
			m_Base=false;
	}
	else
		m_StID=-1;
	CDialog::OnOK();
}
