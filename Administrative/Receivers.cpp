// Receivers.cpp : implementation file
//

#include "stdafx.h"
#include "Administrative.h"
#include "Receivers.h"
#include "leftview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReceivers dialog

extern "C" char * WINAPI Code2NameCTY_lang(CString co, CString mlang);	//CNT.lib
extern "C" char * WINAPI AllCodes_lang(CString CTYCOD[], int *NOCTY);	//CNT.lib

CReceivers::CReceivers(CWnd* pParent /*=NULL*/)
	: CDialog(CReceivers::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReceivers)
	m_CenLat = 0.0;
	m_CenLon = 0.0;
	m_RecRadius = 0;
	m_HopID = 0;
	m_LinkID = 0;
	m_Lat1 = 0.0;
	m_Lat2 = 0.0;
	m_Lat3 = 0.0;
	m_Lat4 = 0.0;
	m_Lat5 = 0.0;
	m_Lat6 = 0.0;
	m_Lon1 = 0.0;
	m_Lon2 = 0.0;
	m_Lon3 = 0.0;
	m_Lon4 = 0.0;
	m_Lon5 = 0.0;
	m_Lon6 = 0.0;
	m_NoiseTemp = 0.0;
	//}}AFX_DATA_INIT
}


void CReceivers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReceivers)
	DDX_Control(pDX, IDC_POINTS, m_Points);
	DDX_Control(pDX, IDC_ZONE_LIST, m_Zone);
	DDX_Text(pDX, IDC_CEN_LAT, m_CenLat);
	DDV_MinMaxDouble(pDX, m_CenLat, -900000., 900000.);
	DDX_Text(pDX, IDC_CEN_LON, m_CenLon);
	DDV_MinMaxDouble(pDX, m_CenLon, -1800000., 1800000.);
	DDX_Text(pDX, IDC_REC_RADIUS, m_RecRadius);
	DDV_MinMaxLong(pDX, m_RecRadius, 0, 2500);
	DDX_Control(pDX, IDC_RECEIVER_STATIONS, m_RecStations);
	DDX_Text(pDX, IDC_HOP_ID, m_HopID);
	DDV_MinMaxLong(pDX, m_HopID, 1, 100000);
	DDX_Text(pDX, IDC_LINK_ID, m_LinkID);
	DDV_MinMaxLong(pDX, m_LinkID, 1, 100000);
	DDX_Text(pDX, IDC_LAT1, m_Lat1);
	DDV_MinMaxDouble(pDX, m_Lat1, -900000., 900000.);
	DDX_Text(pDX, IDC_LAT2, m_Lat2);
	DDV_MinMaxDouble(pDX, m_Lat2, -900000., 900000.);
	DDX_Text(pDX, IDC_LAT3, m_Lat3);
	DDV_MinMaxDouble(pDX, m_Lat3, -900000., 900000.);
	DDX_Text(pDX, IDC_LAT4, m_Lat4);
	DDV_MinMaxDouble(pDX, m_Lat4, -900000., 900000.);
	DDX_Text(pDX, IDC_LAT5, m_Lat5);
	DDV_MinMaxDouble(pDX, m_Lat5, -900000., 900000.);
	DDX_Text(pDX, IDC_LAT6, m_Lat6);
	DDV_MinMaxDouble(pDX, m_Lat6, -900000., 900000.);
	DDX_Text(pDX, IDC_LON1, m_Lon1);
	DDV_MinMaxDouble(pDX, m_Lon1, -1800000., 1800000.);
	DDX_Text(pDX, IDC_LON2, m_Lon2);
	DDV_MinMaxDouble(pDX, m_Lon2, -1800000., 1800000.);
	DDX_Text(pDX, IDC_LON3, m_Lon3);
	DDV_MinMaxDouble(pDX, m_Lon3, -1800000., 1800000.);
	DDX_Text(pDX, IDC_LON4, m_Lon4);
	DDV_MinMaxDouble(pDX, m_Lon4, -1800000., 1800000.);
	DDX_Text(pDX, IDC_LON5, m_Lon5);
	DDV_MinMaxDouble(pDX, m_Lon5, -1800000., 1800000.);
	DDX_Text(pDX, IDC_LON6, m_Lon6);
	DDV_MinMaxDouble(pDX, m_Lon6, -1800000., 1800000.);
	DDX_Control(pDX, IDC_TX_ANTENNA, m_TXAntenna);
	DDX_Text(pDX, IDC_NOISE_TEMP, m_NoiseTemp);
	DDV_MinMaxDouble(pDX, m_NoiseTemp, 150., 2500.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReceivers, CDialog)
	//{{AFX_MSG_MAP(CReceivers)
	ON_BN_CLICKED(IDC_POINT, OnPoint)
	ON_BN_CLICKED(IDC_MULTIPOINT, OnMultipoint)
	ON_BN_CLICKED(IDC_CIRCLE, OnCircle)
	ON_BN_CLICKED(IDC_ZONE, OnZone)
	ON_CBN_SELCHANGE(IDC_POINTS, OnSelchangePoints)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReceivers message handlers

void CReceivers::OnPoint() 
{
	CDatabase DB;
	CRecordset RS;
	CString LicID, StID, Freq;
	long i=1;
	m_HopID=1;
	m_LinkID=2;
	m_NoiseTemp=273;
	UpdateData(false);
	m_RecStations.Clear();
	m_RecStations.SetRows(1);
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	CString SQL;
	int Typ;
	HTREEITEM Node=m_TreeView->GetTreeCtrl().GetParentItem(
						m_TreeView->GetTreeCtrl().GetParentItem(
							m_TreeView->GetTreeCtrl().GetParentItem(m_TreeView->GetTreeCtrl().GetSelectedItem())));
	m_TreeView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==LICENSE)
	{
		if(m_STTP!=_T("ML"))
		{
			SQL.Format(_T("select license.licid,Station.StID,frequency.frequency from frequency, equipment, station, license where freqid=%ld and "),m_ID);
			SQL+=_T("frequency.eqid=equipment.eqid and station.stid=equipment.stid and station.licid=license.licid");
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,LicID);
			RS.GetFieldValue(1,StID);
			RS.GetFieldValue(2,Freq);
			RS.Close();
			SQL.Format(_T(" from Frequency,eqcat, Equipment,antenna, antcat, Station where station.LicID=%s and station.stid<>%s and RespFreq=%s "), LicID, StID, Freq);
			SQL=_T("Select frequency.freqid,Antenna.AntID as AntID, AntCat.AntName as [Antenna Name], sitename as Station_name, geolat as latitude, geolon as longitude, station.country as Country, eqname as Equipment_name,frequency/1000000 as [Frequency(MHz)], antname ")+SQL;
			SQL=SQL+ _T(" and frequency.eqid=equipment.eqid and equipment.stid=station.stid and eqcat.eqcatid=equipment.eqcatid and antenna.eqid=equipment.eqid ");
			SQL=SQL+ _T(" and antenna.antcatid=antcat.antcatid and (antcat.classofant='C' or antcat.classofant='R') order by sitename");
		}
		else
		{
			SQL.Format(_T("select license.licid,Mobiles.mobID,frequency.frequency from frequency, equipment, mobiles, license where freqid=%ld and "),m_ID);
			SQL+=_T("frequency.eqid=equipment.eqid and mobiles.mobid=equipment.mobid and mobiles.licid=license.licid");
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,LicID);
			RS.GetFieldValue(1,StID);
			RS.GetFieldValue(2,Freq);
			RS.Close();
//			SQL.Format(_T(" from Frequency,eqcat, Equipment,antenna, antcat, Station where station.LicID=%s and station.stid<>%s "), LicID, StID);
			SQL.Format(_T(" from Frequency,eqcat, Equipment,antenna, antcat, Station where station.LicID=%s and RespFreq=%s "), LicID, Freq);
			SQL=_T("Select frequency.freqid,Antenna.AntID as AntID, AntCat.AntName as [Antenna Name],sitename as Station_name, geolat as latitude, geolon as longitude, station.country as Country, eqname as Equipment_name,frequency/1000000 as [Frequency(MHz)], antname ")+SQL;
			SQL=SQL+ _T(" and frequency.eqid=equipment.eqid and equipment.stid=station.stid and eqcat.eqcatid=equipment.eqcatid and antenna.eqid=equipment.eqid ");
			SQL=SQL+ _T(" and antenna.antcatid=antcat.antcatid and (antcat.classofant='C' or antcat.classofant='T') and ClassStation='FB' order by sitename");
		}
	}
	else
	{
		if(m_STTP!=_T("ML"))
		{
			SQL.Format(_T("select Station.StID,frequency.frequency from frequency, equipment, station where freqid=%ld and "),m_ID);
			SQL+=_T("frequency.eqid=equipment.eqid and station.stid=equipment.stid ");
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,StID);
			RS.GetFieldValue(1,Freq);
			RS.Close();
			SQL.Format(_T(" from Frequency,eqcat, Equipment,antenna,antcat, Station where station.LicID=-1 and station.stid<>%s and RespFreq=%s "), StID, Freq);
			SQL=_T("Select frequency.freqid,Antenna.AntID as AntID, AntCat.AntName as [Antenna Name],sitename as Station_name, geolat as latitude, geolon as longitude, station.country as Country, eqname as Equipment_name,frequency/1000000 as [Frequency(MHz)], antname ")+SQL;
			SQL=SQL+ _T(" and frequency.eqid=equipment.eqid and equipment.stid=station.stid and eqcat.eqcatid=equipment.eqcatid and antenna.eqid=equipment.eqid ");
			SQL=SQL+ _T(" and antenna.antcatid=antcat.antcatid and (antcat.classofant='C' or antcat.classofant='R') order by sitename");
		}
		else
		{
			SQL.Format(_T("select Mobiles.mobID,frequency.frequency from frequency, equipment, mobiles where freqid=%ld and "),m_ID);
			SQL+=_T("frequency.eqid=equipment.eqid and mobiles.mobid=equipment.mobid");
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,StID);
			RS.GetFieldValue(1,Freq);
			RS.Close();
			SQL.Format(_T(" from Frequency,eqcat, Equipment,antenna,antcat, Station where station.LicID=-1 and station.stid<>%s and RespFreq=%s "), StID, Freq);
			SQL=_T("Select frequency.freqid,Antenna.AntID as AntID, AntCat.AntName as [Antenna Name],sitename as Station_name, geolat as latitude, geolon as longitude, station.country as Country, eqname as Equipment_name,frequency/1000000 as [Frequency(MHz)], antname ")+SQL;
			SQL=SQL+ _T(" and frequency.eqid=equipment.eqid and equipment.stid=station.stid and eqcat.eqcatid=equipment.eqcatid and antenna.eqid=equipment.eqid ");
			SQL=SQL+ _T(" and antenna.antcatid=antcat.antcatid and (antcat.classofant='C' or antcat.classofant='T') and ClassStation='FB' order by sitename");
		}
	}
	RS.Open(CRecordset::dynaset,SQL);
	if(RS.GetRecordCount()>0)
	{
		m_RecStations.SetCols(0,9);
		for(int j=1;j<9;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_RecStations.SetTextMatrix(0,j,FldInfo.m_strName);
		}
		while(true)
		{
			CString Value;
			if(RS.IsEOF()) break;
			m_RecStations.SetRows(m_RecStations.GetRows()+1);
			for(int j=1;j<9;j++)
			{
				RS.GetFieldValue(j,Value);
				m_RecStations.SetTextMatrix(i,j,Value);
			}
			RS.GetFieldValue((short)0,Value);
			m_RecStations.SetRowData(i,atol(Value));
			RS.MoveNext();
			i++;
		}	
		if(m_RecStations.GetRows()>1)
			m_RecStations.SetFixedRows(1);
	}
	else
	{
//		if(m_STTP==_T("ML"))
//			AfxMessageBox(_Z("No TX stations are available!"));
//		else
			AfxMessageBox(_Z("No RX stations are available!"));
	}
	RS.Close();
	DB.Close();	
	m_RecStations.EnableWindow(true);
	m_Points.EnableWindow(false);
	GetDlgItem(IDC_CEN_LAT)->EnableWindow(false);
	GetDlgItem(IDC_CEN_LON)->EnableWindow(false);
	GetDlgItem(IDC_REC_RADIUS)->EnableWindow(false);
	GetDlgItem(IDC_HOP_ID)->EnableWindow(true);
	GetDlgItem(IDC_LINK_ID)->EnableWindow(true);
	GetDlgItem(IDC_NOISE_TEMP)->EnableWindow(true);

	GetDlgItem(IDC_LAT1)->EnableWindow(false);
	GetDlgItem(IDC_LON1)->EnableWindow(false);
	GetDlgItem(IDC_LAT2)->EnableWindow(false);
	GetDlgItem(IDC_LON2)->EnableWindow(false);
	GetDlgItem(IDC_LAT3)->EnableWindow(false);
	GetDlgItem(IDC_LON3)->EnableWindow(false);
	GetDlgItem(IDC_LAT4)->EnableWindow(false);
	GetDlgItem(IDC_LON4)->EnableWindow(false);
	GetDlgItem(IDC_LAT5)->EnableWindow(false);
	GetDlgItem(IDC_LON5)->EnableWindow(false);
	GetDlgItem(IDC_LAT6)->EnableWindow(false);
	GetDlgItem(IDC_LON6)->EnableWindow(false);
	m_Zone.EnableWindow(false);
}

void CReceivers::OnMultipoint() 
{
	m_HopID=1;
	m_LinkID=1;
	m_NoiseTemp=273;
	UpdateData(false);
	m_RecStations.Clear();
	m_RecStations.SetRows(2);
	m_RecStations.EnableWindow(false);
	GetDlgItem(IDC_CEN_LAT)->EnableWindow(false);
	GetDlgItem(IDC_CEN_LON)->EnableWindow(false);
	GetDlgItem(IDC_REC_RADIUS)->EnableWindow(false);
	GetDlgItem(IDC_HOP_ID)->EnableWindow(false);
	GetDlgItem(IDC_LINK_ID)->EnableWindow(false);
	GetDlgItem(IDC_NOISE_TEMP)->EnableWindow(false);
	m_Points.EnableWindow(true);
	m_Points.SelectString(0,"3");
	GetDlgItem(IDC_LAT1)->EnableWindow(true);
	GetDlgItem(IDC_LON1)->EnableWindow(true);
	GetDlgItem(IDC_LAT2)->EnableWindow(true);
	GetDlgItem(IDC_LON2)->EnableWindow(true);
	GetDlgItem(IDC_LAT3)->EnableWindow(true);
	GetDlgItem(IDC_LON3)->EnableWindow(true);
/*	GetDlgItem(IDC_LAT4)->EnableWindow(true);
	GetDlgItem(IDC_LON4)->EnableWindow(true);
	GetDlgItem(IDC_LAT5)->EnableWindow(true);
	GetDlgItem(IDC_LON5)->EnableWindow(true);
	GetDlgItem(IDC_LAT6)->EnableWindow(true);
	GetDlgItem(IDC_LON6)->EnableWindow(true);*/
	m_Zone.EnableWindow(false);
	GetDlgItem(IDC_LAT1)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON1)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT2)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON2)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT3)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON3)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT4)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON4)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT5)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON5)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT6)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON6)->SetWindowText(_T("+0100000.00"));
}

void CReceivers::OnCircle() 
{
	m_HopID=1;
	m_LinkID=1;
	m_NoiseTemp=273;
	UpdateData(false);
	m_RecStations.Clear();
	m_RecStations.SetRows(2);
	m_RecStations.EnableWindow(false);
	GetDlgItem(IDC_CEN_LAT)->EnableWindow(true);
	GetDlgItem(IDC_CEN_LON)->EnableWindow(true);
	GetDlgItem(IDC_REC_RADIUS)->EnableWindow(true);
	GetDlgItem(IDC_HOP_ID)->EnableWindow(false);
	GetDlgItem(IDC_LINK_ID)->EnableWindow(false);
	GetDlgItem(IDC_NOISE_TEMP)->EnableWindow(false);
	GetDlgItem(IDC_LAT1)->EnableWindow(false);
	GetDlgItem(IDC_LON1)->EnableWindow(false);
	GetDlgItem(IDC_LAT2)->EnableWindow(false);
	GetDlgItem(IDC_LON2)->EnableWindow(false);
	GetDlgItem(IDC_LAT3)->EnableWindow(false);
	GetDlgItem(IDC_LON3)->EnableWindow(false);
	GetDlgItem(IDC_LAT4)->EnableWindow(false);
	GetDlgItem(IDC_LON4)->EnableWindow(false);
	GetDlgItem(IDC_LAT5)->EnableWindow(false);
	GetDlgItem(IDC_LON5)->EnableWindow(false);
	GetDlgItem(IDC_LAT6)->EnableWindow(false);
	GetDlgItem(IDC_LON6)->EnableWindow(false);
	m_Points.EnableWindow(false);
	m_Zone.EnableWindow(false);
	GetDlgItem(IDC_CEN_LAT)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_CEN_LON)->SetWindowText(_T("+0100000.00"));
}

void CReceivers::OnOK() 
{
	if(UpdateData(true))
	{
		if(m_TXAntenna.GetRowSel()>0)
		{
			if(((CButton *)GetDlgItem(IDC_POINT))->GetCheck()==BST_CHECKED)
				if(m_RecStations.GetRowSel()>0)
				{
					CString SQL, RecID;
					HTREEITEM Node;
					CDatabase DB;
					CRecordset RS;
					DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
					RS.m_pDatabase=&DB;
					RS.Open(CRecordset::snapshot,_T("Select max(receiverID)+1 from link"));
					RS.GetFieldValue((short)0,RecID);
					RS.Close();
					if(RecID.IsEmpty()) RecID=_T("1");
					//if(m_STTP!=_T("ML"))
					{
						SQL.Format(_T("select %ld,%ld,%ld, 'POINT',%ld,%ld,%ld,%s,%lf "),atol(RecID),m_HopID,m_LinkID, 
							m_ID,m_RecStations.GetRowData(m_RecStations.GetRowSel()),m_TXAntenna.GetRowData(m_TXAntenna.GetRowSel()),
							m_RecStations.GetTextMatrix(m_RecStations.GetRowSel(),1),m_NoiseTemp);
						SQL=_T("Insert into link (ReceiverID,HopID,LinkID,GeoType,TXID,RXID,TXAntID,RXAntID,NoiseTemp) ")+SQL;
						DB.ExecuteSQL(SQL);
						DB.Close();
//						Node=m_TreeView->GetTreeCtrl().InsertItem(_T("Receiver: POINT"),RECEIVER,RECEIVER,m_TreeView->GetTreeCtrl().GetSelectedItem());
					}
					//else
					//{
					//	SQL.Format(_T("select %ld,%ld,%ld, 'POINT',%ld,%ld,%ld,%s,%lf "),atol(RecID),m_HopID,m_LinkID, 
					//		m_RecStations.GetRowData(m_RecStations.GetRowSel()),m_ID,m_RecStations.GetTextMatrix(m_RecStations.GetRowSel(),1),
					//		m_TXAntenna.GetRowData(m_TXAntenna.GetRowSel()),m_NoiseTemp);
					//	SQL=_T("Insert into link (ReceiverID,HopID,LinkID,GeoType,TXID,RXID,TXAntID,RXAntID,NoiseTemp) ")+SQL;
					//	DB.ExecuteSQL(SQL);
					//	DB.Close();
					//	Node=m_TreeView->GetTreeCtrl().InsertItem(_T("Transmitter"),RECEIVER,RECEIVER,m_TreeView->GetTreeCtrl().GetSelectedItem());
					//}
//					m_TreeView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(RecID));
//					m_TreeView->RedrawWindow();
//					m_TreeView->GetTreeCtrl().Select(Node,TVGN_CARET);
					TVITEM tvItem={0};
					tvItem.mask=TVIF_CHILDREN;
					tvItem.cChildren=1;
					tvItem.hItem=m_TreeView->GetTreeCtrl().GetSelectedItem();
					m_TreeView->GetTreeCtrl().SetItem(&tvItem);
				}
				else
				{
					AfxMessageBox(_Z("No receivers are selected!"));
				}
			if(((CButton *)GetDlgItem(IDC_MULTIPOINT))->GetCheck()==BST_CHECKED)
			{
				CString SQL, RecID;
				CDatabase DB;
				CRecordset RS;
				DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
				RS.m_pDatabase=&DB;
				RS.Open(CRecordset::snapshot,_T("Select max(receiverID)+1 from link"));
				RS.GetFieldValue((short)0,RecID);
				RS.Close();
				if(RecID.IsEmpty()) RecID=_T("1");
				int j=0;
				double pt[12]={200},sgn;
				CString Val;
				((CEdit *)GetDlgItem(IDC_LAT1))->GetWindowText(Val);
				if(Val.Left(1)==_T("-")) sgn=-1.0;
				else					sgn=1.0;
				pt[j++]=(atof(Val.Left(3))+sgn*atof(Val.Mid(3,2))/60.+sgn*atof(Val.Mid(5,5))/3600.);
				((CEdit *)GetDlgItem(IDC_LON1))->GetWindowText(Val);
				if(Val.Left(1)==_T("-")) sgn=-1.0;
				else					sgn=1.0;
				pt[j++]=(atof(Val.Left(4))+sgn*atof(Val.Mid(4,2))/60.+sgn*atof(Val.Mid(6,5))/3600.);
				((CEdit *)GetDlgItem(IDC_LAT2))->GetWindowText(Val);
				if(Val.Left(1)==_T("-")) sgn=-1.0;
				else					sgn=1.0;
				pt[j++]=(atof(Val.Left(3))+sgn*atof(Val.Mid(3,2))/60.+sgn*atof(Val.Mid(5,5))/3600.);
				((CEdit *)GetDlgItem(IDC_LON2))->GetWindowText(Val);
				if(Val.Left(1)==_T("-")) sgn=-1.0;
				else					sgn=1.0;
				pt[j++]=(atof(Val.Left(4))+sgn*atof(Val.Mid(4,2))/60.+sgn*atof(Val.Mid(6,5))/3600.);
				((CEdit *)GetDlgItem(IDC_LAT3))->GetWindowText(Val);
				if(Val.Left(1)==_T("-")) sgn=-1.0;
				else					sgn=1.0;
				pt[j++]=(atof(Val.Left(3))+sgn*atof(Val.Mid(3,2))/60.+sgn*atof(Val.Mid(5,5))/3600.);
				((CEdit *)GetDlgItem(IDC_LON3))->GetWindowText(Val);
				if(Val.Left(1)==_T("-")) sgn=-1.0;
				else					sgn=1.0;
				pt[j++]=(atof(Val.Left(4))+sgn*atof(Val.Mid(4,2))/60.+sgn*atof(Val.Mid(6,5))/3600.);
				int PointsNo;
				CString Pts;
				m_Points.GetWindowText(Pts);
				PointsNo=atoi(Pts);
				SQL.Format(_T("select %ld,%ld,%ld, 'MULTIPOINT',%ld,-1,%ld,-1,%lf,%lf,%lf,%lf,%lf,%lf "),atol(RecID),m_HopID,m_LinkID, 
					m_ID,m_TXAntenna.GetRowData(m_TXAntenna.GetRowSel()),pt[0],pt[1],pt[2],pt[3],pt[4],pt[5],pt[6]);
				SQL=_T("Insert into link (ReceiverID,HopID,LinkID,GeoType,TXID,RXID,TXAntID,RXAntID,lat1,lon1,lat2,lon2,lat3,lon3) ")+SQL;
				if(PointsNo>3)
				{
					((CEdit *)GetDlgItem(IDC_LAT4))->GetWindowText(Val);
					if(Val.Left(1)==_T("-")) sgn=-1.0;
					else					sgn=1.0;
					pt[j++]=(atof(Val.Left(3))+sgn*atof(Val.Mid(3,2))/60.+sgn*atof(Val.Mid(5,5))/3600.);
					((CEdit *)GetDlgItem(IDC_LON4))->GetWindowText(Val);
					if(Val.Left(1)==_T("-")) sgn=-1.0;
					else					sgn=1.0;
					pt[j++]=(atof(Val.Left(4))+sgn*atof(Val.Mid(4,2))/60.+sgn*atof(Val.Mid(6,5))/3600.);
					SQL.Format(_T("select %ld,%ld,%ld, 'MULTIPOINT',%ld,-1,%ld,-1,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf "),atol(RecID),m_HopID,m_LinkID, 
						m_ID,m_TXAntenna.GetRowData(m_TXAntenna.GetRowSel()),pt[0],pt[1],pt[2],pt[3],pt[4],pt[5],pt[6],pt[7],pt[8]);
					SQL=_T("Insert into link (ReceiverID,HopID,LinkID,GeoType,TXID,RXID,TXAntID,RXAntID,lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4) ")+SQL;
				}
				if(PointsNo>4)
				{
					((CEdit *)GetDlgItem(IDC_LAT5))->GetWindowText(Val);
					if(Val.Left(1)==_T("-")) sgn=-1.0;
					else					sgn=1.0;
					pt[j++]=(atof(Val.Left(3))+sgn*atof(Val.Mid(3,2))/60.+sgn*atof(Val.Mid(5,5))/3600.);
					((CEdit *)GetDlgItem(IDC_LON5))->GetWindowText(Val);
					if(Val.Left(1)==_T("-")) sgn=-1.0;
					else					sgn=1.0;
					pt[j++]=(atof(Val.Left(4))+sgn*atof(Val.Mid(4,2))/60.+sgn*atof(Val.Mid(6,5))/3600.);
					SQL.Format(_T("select %ld,%ld,%ld, 'MULTIPOINT',%ld,-1,%ld,-1,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf "),atol(RecID),m_HopID,m_LinkID, 
						m_ID,m_TXAntenna.GetRowData(m_TXAntenna.GetRowSel()),pt[0],pt[1],pt[2],pt[3],pt[4],pt[5],pt[6],pt[7],pt[8],pt[9],pt[10]);
					SQL=_T("Insert into link (ReceiverID,HopID,LinkID,GeoType,TXID,RXID,TXAntID,RXAntID,lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4,lat5,lon5) ")+SQL;
				}
				if(PointsNo>5)
				{
					((CEdit *)GetDlgItem(IDC_LAT6))->GetWindowText(Val);
					if(Val.Left(1)==_T("-")) sgn=-1.0;
					else					sgn=1.0;
					pt[j++]=(atof(Val.Left(3))+sgn*atof(Val.Mid(3,2))/60.+sgn*atof(Val.Mid(5,5))/3600.);
					((CEdit *)GetDlgItem(IDC_LON6))->GetWindowText(Val);
					if(Val.Left(1)==_T("-")) sgn=-1.0;
					else					sgn=1.0;
					pt[j++]=(atof(Val.Left(4))+sgn*atof(Val.Mid(4,2))/60.+sgn*atof(Val.Mid(6,5))/3600.);
					SQL.Format(_T("select %ld,%ld,%ld, 'MULTIPOINT',%ld,-1,%ld,-1,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf "),atol(RecID),m_HopID,m_LinkID, 
						m_ID,m_TXAntenna.GetRowData(m_TXAntenna.GetRowSel()),pt[0],pt[1],pt[2],pt[3],pt[4],pt[5],pt[6],pt[7],pt[8],pt[9],pt[10],pt[11],pt[12]);
					SQL=_T("Insert into link (ReceiverID,HopID,LinkID,GeoType,TXID,RXID,TXAntID,RXAntID,lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4,lat5,lon5,lat6,lon6) ")+SQL;
				}
				DB.ExecuteSQL(SQL);
				DB.Close();
//				HTREEITEM Node=m_TreeView->GetTreeCtrl().InsertItem(_T("Receiver: MULTIPOINT"),RECEIVER,RECEIVER,m_TreeView->GetTreeCtrl().GetSelectedItem());
//				m_TreeView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(RecID));
//				m_TreeView->RedrawWindow();
//				m_TreeView->GetTreeCtrl().Select(Node,TVGN_CARET);
				TVITEM tvItem={0};
				tvItem.mask=TVIF_CHILDREN;
				tvItem.cChildren=1;
				tvItem.hItem=m_TreeView->GetTreeCtrl().GetSelectedItem();
				m_TreeView->GetTreeCtrl().SetItem(&tvItem);
			}
			if(((CButton *)GetDlgItem(IDC_CIRCLE))->GetCheck()==BST_CHECKED)
			{
				double lat,lon,sgn;
				CString Val;
				Val.Format(_T("%+010.2lf"),m_CenLat);
				if(Val.Left(1)==_T("-")) sgn=-1.0;
				else					sgn=1.0;
				lat=(atof(Val.Left(3))+sgn*atof(Val.Mid(3,2))/60.+sgn*atof(Val.Mid(5,5))/3600.);
				
				Val.Format(_T("%+011.2lf"),m_CenLon);
				if(Val.Left(1)==_T("-")) sgn=-1.0;
				else					sgn=1.0;
				lon=(atof(Val.Left(4))+sgn*atof(Val.Mid(4,2))/60.+sgn*atof(Val.Mid(6,5))/3600.);
				CString SQL, RecID;
				CDatabase DB;
				CRecordset RS;
				DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
				RS.m_pDatabase=&DB;
				RS.Open(CRecordset::snapshot,_T("Select max(receiverID)+1 from link"));
				RS.GetFieldValue((short)0,RecID);
				RS.Close();
				if(RecID.IsEmpty()) RecID=_T("1");
				SQL.Format(_T("select %ld,'CIRCLE',%ld,-1,%ld,-1,%lf,%lf,%ld "),atol(RecID),
					m_ID,m_TXAntenna.GetRowData(m_TXAntenna.GetRowSel()),lat,lon,m_RecRadius);
				SQL=_T("Insert into link (ReceiverID,GeoType,TXID,RXID,TXAntID,RXAntID,RecLat,RecLon,Radius) ")+SQL;
				DB.ExecuteSQL(SQL);
				DB.Close();
//				HTREEITEM Node=m_TreeView->GetTreeCtrl().InsertItem(_T("Receiver: CIRCLE"),RECEIVER,RECEIVER,m_TreeView->GetTreeCtrl().GetSelectedItem());
//				m_TreeView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(RecID));
//				m_TreeView->GetTreeCtrl().Select(Node,TVGN_CARET);
//				m_TreeView->RedrawWindow();
				TVITEM tvItem={0};
				tvItem.mask=TVIF_CHILDREN;
				tvItem.cChildren=1;
				tvItem.hItem=m_TreeView->GetTreeCtrl().GetSelectedItem();
				m_TreeView->GetTreeCtrl().SetItem(&tvItem);
			}
			if(((CButton *)GetDlgItem(IDC_ZONE))->GetCheck()==BST_CHECKED)
			{
				CString SQL, RecID, Zone;
				CDatabase DB;
				CRecordset RS;
				DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
				RS.m_pDatabase=&DB;
				RS.Open(CRecordset::snapshot,_T("Select max(receiverID)+1 from link"));
				RS.GetFieldValue((short)0,RecID);
				RS.Close();
				if(RecID.IsEmpty()) RecID=_T("1");
				m_Zone.GetWindowText(Zone);
				if(Zone.Right(1)==_T("-"))
					Zone=Zone.Left(1);
				SQL.Format(_T("select %ld,'ZONE',%ld,-1,%ld,-1,'%s' "),atol(RecID),
					m_ID,m_TXAntenna.GetRowData(m_TXAntenna.GetRowSel()),Zone);
				SQL=_T("Insert into link (ReceiverID,GeoType,TXID,RXID,TXAntID,RXAntID,zone) ")+SQL;
				DB.ExecuteSQL(SQL);
				DB.Close();
//				HTREEITEM Node=m_TreeView->GetTreeCtrl().InsertItem(_T("Receiver: ZONE"),RECEIVER,RECEIVER,m_TreeView->GetTreeCtrl().GetSelectedItem());
//				m_TreeView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(RecID));
//				m_TreeView->RedrawWindow();
//				m_TreeView->GetTreeCtrl().Select(Node,TVGN_CARET);
				TVITEM tvItem={0};
				tvItem.mask=TVIF_CHILDREN;
				tvItem.cChildren=1;
				tvItem.hItem=m_TreeView->GetTreeCtrl().GetSelectedItem();
				m_TreeView->GetTreeCtrl().SetItem(&tvItem);
			}
		}
		else
			MessageBox(_Z("Please select a TX antenna."));
		CDialog::OnOK();
	}
}

BOOL CReceivers::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if(m_IsTypical)
	{
		this->SetWindowText(_Z("Service area"));
		((CWnd *)GetDlgItem(IDC_POINT))->EnableWindow(false);
		((CWnd *)GetDlgItem(IDC_MULTIPOINT))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_CIRCLE))->SetCheck(BST_CHECKED);
		OnCircle();
	}
	
	else if(m_Srv==_T("B"))
	{
		((CWnd *)GetDlgItem(IDC_POINT))->EnableWindow(false);
		((CWnd *)GetDlgItem(IDC_MULTIPOINT))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_CIRCLE))->SetCheck(BST_CHECKED);
		OnCircle();
	}
	else if(m_STTP==_T("FX"))
	{
		((CWnd *)GetDlgItem(IDC_CIRCLE))->EnableWindow(false);
		((CWnd *)GetDlgItem(IDC_ZONE))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_POINT))->SetCheck(BST_CHECKED);
		OnPoint();
	}
	else if(m_STTP==_T("FB"))
	{
		((CWnd *)GetDlgItem(IDC_POINT))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_MULTIPOINT))->SetCheck(BST_CHECKED);
		OnMultipoint();
	}
	else if(m_STTP==_T("ML"))
	{
		((CWnd *)GetDlgItem(IDC_CIRCLE))->EnableWindow(false);
		((CWnd *)GetDlgItem(IDC_ZONE))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_POINT))->SetCheck(BST_CHECKED);
		OnPoint();
	}
	CDatabase DB;
	CRecordset RS;
	CString EqID;
	long i=1;
	UpdateData(false);
	m_HopID=0;
	m_LinkID=0;
	m_NoiseTemp=0;
	m_TXAntenna.Clear();
	m_TXAntenna.SetRows(1);
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	CString SQL;
	if(m_Srv==_T("B"))
	{
		SQL.Format(_T("select equipment.EqID from frequency, equipment where freqid=%ld and "),m_ID);
		SQL+=_T("frequency.eqid=equipment.eqid");
	}
	else
	{
		SQL.Format(_T("select equipment.EqID from frequency, equipment where freqid=%ld and "),m_ID);
		SQL+=_T("frequency.eqid=equipment.eqid");
	}
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,EqID);
	RS.Close();

	if(m_STTP!=_T("ML"))
	{
		if(m_Srv==_T("B"))
		{
			SQL.Format(_T("select antenna.antid,AntName,Gain,Azimuth,Elevation,antheightagl as [Antenna Height] from antenna,antcat,equipment where equipment.eqid=%s and "),EqID);
			SQL+=_T("antenna.eqid=equipment.eqid and antenna.antcatid=antcat.antcatid and ");
			SQL+=_T("(antcat.classofant='T' or antcat.classofant='C')");
		}
		else
		{
			SQL.Format(_T("select antenna.antid,AntName,Gain,Azimuth,Elevation,antheightagl as [Antenna Height] from antenna,antcat,equipment where equipment.eqid=%s and "),EqID);
			SQL+=_T("antenna.eqid=equipment.eqid and antenna.antcatid=antcat.antcatid and ");
			SQL+=_T("(antcat.classofant='T' or antcat.classofant='C')");
		}
		RS.Open(CRecordset::dynaset,SQL);
		if(RS.IsEOF())
		{
			MessageBox(_Z("No TX antennas are defined for this station!"));
			DB.Close();
			EndDialog(FALSE);
			return false;
		}
		m_TXAntenna.SetCols(0,6);
		for(int j=1;j<6;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_TXAntenna.SetTextMatrix(0,j,FldInfo.m_strName);
		}
		while(true)
		{
			CString Value;
			if(RS.IsEOF()) break;
			m_TXAntenna.SetRows(m_TXAntenna.GetRows()+1);
			for(int j=1;j<6;j++)
			{
				RS.GetFieldValue(j,Value);
				m_TXAntenna.SetTextMatrix(i,j,Value);
			}
			RS.GetFieldValue((short)0,Value);
			m_TXAntenna.SetRowData(i,atol(Value));
			RS.MoveNext();
			i++;
		}
		m_TXAntenna.SetFixedRows(1);
		RS.Close();
	}
	else
	{
		SQL.Format(_T("select antenna.antid,AntName,Gain,Azimuth,Elevation,antheightagl as [Antenna Height] from antenna,antcat,equipment where equipment.eqid=%s and "),EqID);
		SQL+=_T("antenna.eqid=equipment.eqid and antenna.antcatid=antcat.antcatid and ");
		SQL+=_T("(antcat.classofant='R' or antcat.classofant='C')");
		RS.Open(CRecordset::dynaset,SQL);
		if(RS.IsEOF())
		{
			MessageBox(_Z("No RX antennas are defined for this station!"));
			DB.Close();
			EndDialog(FALSE);
			return false;
		}
		m_TXAntenna.SetCols(0,6);
		for(int j=1;j<6;j++)
		{
			CODBCFieldInfo FldInfo;
			CString Unit;
			RS.GetODBCFieldInfo(j,FldInfo);
			m_TXAntenna.SetTextMatrix(0,j,FldInfo.m_strName);
		}
		while(true)
		{
			CString Value;
			if(RS.IsEOF()) break;
			m_TXAntenna.SetRows(m_TXAntenna.GetRows()+1);
			for(int j=1;j<6;j++)
			{
				RS.GetFieldValue(j,Value);
				m_TXAntenna.SetTextMatrix(i,j,Value);
			}
			RS.GetFieldValue((short)0,Value);
			m_TXAntenna.SetRowData(i,atol(Value));
			RS.MoveNext();
			i++;
		}
		m_TXAntenna.SetFixedRows(1);
		RS.Close();
		((CWnd *)GetDlgItem(IDC_POINT))->EnableWindow(true);
		((CWnd *)GetDlgItem(IDC_MULTIPOINT))->EnableWindow(false);
		((CWnd *)GetDlgItem(IDC_CIRCLE))->EnableWindow(false);
		((CWnd *)GetDlgItem(IDC_ZONE))->EnableWindow(false);
		((CWnd *)GetDlgItem(IDC_ANT_LIST))->SetWindowText(_Z("Receiver antenna"));
	}
/*	GetDlgItem(IDC_LAT1)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON1)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT2)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON2)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT3)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON3)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT4)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON4)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT5)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON5)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_LAT6)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_LON6)->SetWindowText(_T("+0100000.00"));
	GetDlgItem(IDC_CEN_LAT)->SetWindowText(_T("+010000.00"));
	GetDlgItem(IDC_CEN_LON)->SetWindowText(_T("+0100000.00"));*/

/*	CString m_Tbl=_T("select * from Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Zone.ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Zone.AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Zone.ResetContent();
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Zone.AddString(Str);
	}
	DB.Close();	
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReceivers::OnZone() 
{
	m_HopID=1;
	m_LinkID=1;
	m_NoiseTemp=273;
	UpdateData(false);
	m_RecStations.Clear();
	m_RecStations.SetRows(2);
	m_RecStations.EnableWindow(false);
	GetDlgItem(IDC_CEN_LAT)->EnableWindow(false);
	GetDlgItem(IDC_CEN_LON)->EnableWindow(false);
	GetDlgItem(IDC_REC_RADIUS)->EnableWindow(false);
	GetDlgItem(IDC_HOP_ID)->EnableWindow(false);
	GetDlgItem(IDC_LINK_ID)->EnableWindow(false);
	GetDlgItem(IDC_NOISE_TEMP)->EnableWindow(false);
	GetDlgItem(IDC_LAT1)->EnableWindow(false);
	GetDlgItem(IDC_LON1)->EnableWindow(false);
	GetDlgItem(IDC_LAT2)->EnableWindow(false);
	GetDlgItem(IDC_LON2)->EnableWindow(false);
	GetDlgItem(IDC_LAT3)->EnableWindow(false);
	GetDlgItem(IDC_LON3)->EnableWindow(false);
	GetDlgItem(IDC_LAT4)->EnableWindow(false);
	GetDlgItem(IDC_LON4)->EnableWindow(false);
	GetDlgItem(IDC_LAT5)->EnableWindow(false);
	GetDlgItem(IDC_LON5)->EnableWindow(false);
	GetDlgItem(IDC_LAT6)->EnableWindow(false);
	GetDlgItem(IDC_LON6)->EnableWindow(false);
	m_Points.EnableWindow(false);
	m_Zone.EnableWindow(true);
}

void CReceivers::OnSelchangePoints() 
{
	int PointsNo;
	CString Pts;
	m_Points.GetWindowText(Pts);
	PointsNo=atoi(Pts);
	if(PointsNo>2)
	{
		GetDlgItem(IDC_LAT3)->EnableWindow(true);
		GetDlgItem(IDC_LON3)->EnableWindow(true);
		GetDlgItem(IDC_LAT4)->EnableWindow(false);
		GetDlgItem(IDC_LON4)->EnableWindow(false);
		GetDlgItem(IDC_LAT5)->EnableWindow(false);
		GetDlgItem(IDC_LON5)->EnableWindow(false);
		GetDlgItem(IDC_LAT6)->EnableWindow(false);
		GetDlgItem(IDC_LON6)->EnableWindow(false);
	}
	if(PointsNo>3)
	{
		GetDlgItem(IDC_LAT4)->EnableWindow(true);
		GetDlgItem(IDC_LON4)->EnableWindow(true);
		GetDlgItem(IDC_LAT5)->EnableWindow(false);
		GetDlgItem(IDC_LON5)->EnableWindow(false);
		GetDlgItem(IDC_LAT6)->EnableWindow(false);
		GetDlgItem(IDC_LON6)->EnableWindow(false);
	}
	if(PointsNo>4)
	{
		GetDlgItem(IDC_LAT5)->EnableWindow(true);
		GetDlgItem(IDC_LON5)->EnableWindow(true);
		GetDlgItem(IDC_LAT6)->EnableWindow(false);
		GetDlgItem(IDC_LON6)->EnableWindow(false);
	}
	if(PointsNo>5)
	{
		GetDlgItem(IDC_LAT6)->EnableWindow(true);
		GetDlgItem(IDC_LON6)->EnableWindow(true);
	}
	
}
