///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////GE06/////////////////////////////////////////
//////////////////////////////////////////////P1812////////////////////////////////////////

#include "stdafx.h"
#include "SMS4DC.h"
#include "SMS4DCDoc.h"
#include "SMS4DCView.h"

#include <math.h>
#include "MainFrm.h"
//#include "DataBaseDLG.h"
#include "DataBaseLDLG.h"
#include "LoSDLG.h"

#include "P154606_Functions.h"
#include "GE06repDLG1.h"
#include "GE06cvaDLG.h"
#include "GE06srvDLG.h"
#include "GE06intDLG1.h"

#include <io.h>

#include "iter.h"
#include "P1812DLG.h"
#include "FileDLG_ChangedType.h"

#include "UTM.h"
#include "Pro_P1812_AreaDoc.h"
#include "Pro_P1812_LineDoc.h"
#include "Pro_P1812_PolygonDoc.h"
#include "Pro_P1812_LinkDoc.h"
#include "Pro_P1812_NetFDoc.h"
#include "Pro_P1812_NetBDoc.h"

#include "KFactor.h"
#include "Pro_P526V14_LinkDoc.h"

#include "NormalizeDLG.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////GE06/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

double CSMS4DCView::E_P154606ALn(double latST,double lonST,double lat0,double lon0,double h1,
						  double f_MHz, double Ptime)
{
	double zDist[9] , Ei[9] , Eb = -999.0;
//	CString Zones[9];
//	int IER = 1;
//	IER = GEZones(4,latST,lonST,lat0,lon0,zDist,Zones) ;

	char Zones[10] = {"12345ABCD"};
	int IER = 1;
	IER = GE06Zones(latST,lonST,lat0,lon0,zDist) ;

	if(IER==0)
	{
		double /*pi = 4.0*atan(1.0)  ,*/  dist , Ebfs;

		CP154606_Functions CP154606;
		dist = Distance_km(latST,lonST,lat0,lon0);
		dist = max(dist,0.00001);

		double dlT , dsT , EDli , EDsi;
		for(int i=0;i<9;i++)
		{
			if(zDist[i]>0)
			{
		//		Ei[i] = CP154606.P1546_8(f_MHz,Ptime,Zones[i],h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Ebfs);
				Ei[i] = CP154606.P1546_20(f_MHz,Ptime,Zones[i],h1,dist,&Ebfs);
				Ei[i] = min(Ei[i],Ebfs);
			}
			else
				Ei[i] = 0;
		}

		dlT = zDist[0] + zDist[1] + zDist[2] + zDist[8];
		EDli = zDist[0]*Ei[0] + zDist[1]*Ei[1] + zDist[2]*Ei[2] + zDist[8]*Ei[8];

		dsT = zDist[3] + zDist[4] + zDist[5] + zDist[6] + zDist[7];
		EDsi = zDist[3]*Ei[3] + zDist[4]*Ei[4] + zDist[5]*Ei[5] + zDist[6]*Ei[6] + zDist[7]*Ei[7];

		if		(dsT==0)	Eb = EDli/dlT;
		else if (dlT==0)	Eb = EDsi/dsT;
		else
		{
			double Fs = dsT/dist;
			double A0 = CP154606.F_A_2_1_2n(Fs);
			double delta = EDsi/dsT - EDli/dlT;
			double V = max(1.0 , 1.0 + delta/40.0);
			double A = pow(A0 , V);
			Eb = (1.0-A)*EDli/dlT + A*EDsi/dsT;
		}
	}
	return Eb;	//dBuV/m
}


double CSMS4DCView::E_P154606AL_hR(double latST,double lonST,double lat0,double lon0,double h1,
						  double f_MHz, double Ptime, double RxH,int ENV)
{
	double zDist[9] , Ei[9] , Eb = -999.0;

//	CString Zones[9];
//	int IER = 1;
//	IER = GEZones(4,latST,lonST,lat0,lon0,zDist,Zones) ;

	char Zones[10] = {"12345ABCD"};
	int IER = 1;
	IER = GE06Zones(latST,lonST,lat0,lon0,zDist) ;

	if(IER==0)
	{
		double /*pi = 4.0*atan(1.0)  ,*/  dist , Ebfs;

		CP154606_Functions CP154606;
		dist = Distance_km(latST,lonST,lat0,lon0);
		dist = max(dist,0.00001);
//		OnDatabaseStationsindesktop2(latST,lonST);

		double dlT = 0  , dsT = 0 , EDli = 0  , EDsi = 0;
		for(int i=0;i<9;i++)
		{
			if(zDist[i]>0)
			{
		//		Ei[i] = CP154606.P1546_8(f_MHz,Ptime,Zones[i],h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Ebfs);
				Ei[i] = CP154606.P1546_30(f_MHz,Ptime,Zones[i],h1,dist,RxH,ENV,&Ebfs);
			}
			else
				Ei[i] = 0;
		}
		dlT = zDist[0] + zDist[1] + zDist[2] + zDist[8];
		EDli = zDist[0]*Ei[0] + zDist[1]*Ei[1] + zDist[2]*Ei[2] + zDist[8]*Ei[8];

		dsT = zDist[3] + zDist[4] + zDist[5] + zDist[6] + zDist[7];
		EDsi = zDist[3]*Ei[3] + zDist[4]*Ei[4] + zDist[5]*Ei[5] + zDist[6]*Ei[6] + zDist[7]*Ei[7];

		if		(dsT==0)	Eb = EDli/dlT;
		else if (dlT==0)	Eb = EDsi/dsT;
		else
		{
			double Fs = dsT/dist;
		//	double A0 = CP154606.F_A_2_1_2(Fs,Ptime);
			double A0 = 1.0 - pow((1.0 - Fs) , 2.0/3.0);

			double delta = EDsi/dsT - EDli/dlT;
			double V = max(1.0 , 1.0 + delta/40.0);
			double A = pow(A0 , V);
			Eb = (1.0-A)*EDli/dlT + A*EDsi/dsT;
		}
	}
	return Eb;	//dBuV/m
}

double CSMS4DCView::E_P154606AL(double latST,double lonST,double lat0,double lon0,double h1,
						  double f_MHz, double Ptime)
{
	double zDist[9] , Ei[9] , Eb = -999.0;
//	CString Zones[9];
//	int IER = 1;
//	IER = GEZones(4,latST,lonST,lat0,lon0,zDist,Zones) ;

	char Zones[10] = {"12345ABCD"};
	int IER = 1;
	IER = GE06Zones(latST,lonST,lat0,lon0,zDist) ;

	if(IER==0)
	{
		double /*pi = 4.0*atan(1.0)  ,*/  dist , Ebfs;

		CP154606_Functions CP154606;
		dist = Distance_km(latST,lonST,lat0,lon0);
		dist = max(dist,0.00001);
//		OnDatabaseStationsindesktop2(latST,lonST);

		double dlT = 0  , dsT = 0 , EDli = 0  , EDsi = 0;
		for(int i=0;i<9;i++)
		{
			if(zDist[i]>0)
			{
		//		Ei[i] = CP154606.P1546_8(f_MHz,Ptime,Zones[i],h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Ebfs);
				Ei[i] = CP154606.P1546_20(f_MHz,Ptime,Zones[i],h1,dist,&Ebfs);

				Ei[i] = min(Ei[i],Ebfs);
			}
			else
				Ei[i] = 0;
		}

		dlT = zDist[0] + zDist[1] + zDist[2] + zDist[8];
		EDli = zDist[0]*Ei[0] + zDist[1]*Ei[1] + zDist[2]*Ei[2] + zDist[8]*Ei[8];

		dsT = zDist[3] + zDist[4] + zDist[5] + zDist[6] + zDist[7];
		EDsi = zDist[3]*Ei[3] + zDist[4]*Ei[4] + zDist[5]*Ei[5] + zDist[6]*Ei[6] + zDist[7]*Ei[7];

		if		(dsT==0)	Eb = EDli/dlT;
		else if (dlT==0)	Eb = EDsi/dsT;
		else
		{
			double Fs = dsT/dist;
		//	double A0 = CP154606.F_A_2_1_2(Fs,Ptime);
			double A0 = 1.0 - pow((1.0 - Fs) , 2.0/3.0);

			double delta = EDsi/dsT - EDli/dlT;
			double V = max(1.0 , 1.0 + delta/40.0);
			double A = pow(A0 , V);
			Eb = (1.0-A)*EDli/dlT + A*EDsi/dsT;
		}
	}
	return Eb;	//dBuV/m
}

double CSMS4DCView::E_P154606(double latST,double lonST,double lat0,double lon0,double h1,
						  double HasglST, double f_MHz, double kfactor,
						  double Ptime,double RxH,int ENV,int syst,double Plocation,
						  int P1546Clangle)
{
	double zDist[9] , Ei[9] , Eb = -999.0;
//	CString Zones[9];
//	int IER = 1;
//	IER = GEZones(4,latST,lonST,lat0,lon0,zDist,Zones) ;

	char Zones[10] = {"12345ABCD"};
	int IER = 1;
	IER = GE06Zones(latST,lonST,lat0,lon0,zDist) ;

	if(IER==0)
	{
		CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument();

		double dist , az , lat15km , lon15km , StepRes , Ebfs;
		double /*pi = 4.0*atan(1.0)  ,*/  rearth = 6371.0  , tetamax15 = 0 , m_ZoomFactor = 1,corr_ca = 0;
		double tetai , mds , ds , hi, azI , mdz , dz , tetamax16 , hii,hir,ttca;	

		CP154606_Functions CP154606;
		dist = Distance_km(latST,lonST,lat0,lon0);
		dist = max(dist,0.00001);
		az = Azimuth_Deg(latST,lonST,lat0,lon0);
		OnDatabaseStationsindesktop2(latST,lonST);
		///////////////////////////////// tetamax15 /////////////////////////////////////////////
		StepRes = 1.0/m_ZoomFactor;
		CString globeTileInfo = m_AppPath + _T("Texts\\globe.txt");
		if (pDoc->TileInfo != globeTileInfo)
			StepRes = (pDoc->m_Resolution_x/1000.0)/m_ZoomFactor;
		
		if (h1<0.0)
		{
			tetai=-pi/2.0;
			mds=m_ZoomFactor*min(dist,15.0);
			ds=0.0;
			while( ds< mds )  //ds=0->15
			{
				ds = ds+StepRes;
				reckon( latST,lonST, ds , az , &lat15km , &lon15km) ;
				hi = LatLon2Hg(lat15km , lon15km) ;
				tetai=max(tetai   ,(((hi-HasglST)/(ds*1000.0))-(ds/(2.0*kfactor*rearth))));
			}
			tetamax15 = (180.0/pi)*tetai;
		}
		/////////////////////////////////Rx ttca /////////////////////////////////////////////
		if (P1546Clangle==1)
		{
			OnDatabaseStationsindesktop2(lat0,lon0);

			hir = LatLon2Hg(lat0,lon0) ;
			azI=Azimuth_Deg(lat0,lon0,latST,lonST);
			mdz=m_ZoomFactor*min(dist,16.0);
			tetamax16=-pi/2.0;
			dz=0.0;
			while( dz< mdz )  //dz=0->16
			{
				dz=dz+StepRes;
				reckon(lat0,lon0, dz , azI , &lat15km , &lon15km) ;
				hii = LatLon2Hg(lat15km , lon15km) ;
				tetamax16=max(tetamax16   ,(((hii-10.0-hir)/(dz*1000))-(dz/(2.0*kfactor*rearth))));
			}
			ttca = tetamax16*(180.0/pi);
			corr_ca = TCAcorr1546(ttca,f_MHz);
		}

		double dlT  , dsT , EDli  , EDsi;
		for(int i=0;i<9;i++)
		{
			if(zDist[i]>0)
			{
				Ei[i] = CP154606.P1546_6(f_MHz,Ptime,Zones[i],h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Ebfs);
				Ei[i] = Ei[i] + corr_ca;
				Ei[i] = min(Ei[i],Ebfs);
			}
			else
				Ei[i] = 0;
		}
		dlT = zDist[0] + zDist[1] + zDist[2] + zDist[8];
		EDli = zDist[0]*Ei[0] + zDist[1]*Ei[1] + zDist[2]*Ei[2] + zDist[8]*Ei[8];

		dsT = zDist[3] + zDist[4] + zDist[5] + zDist[6] + zDist[7];
		EDsi = zDist[3]*Ei[3] + zDist[4]*Ei[4] + zDist[5]*Ei[5] + zDist[6]*Ei[6] + zDist[7]*Ei[7];

		if	   (dsT==0)	Eb = EDli/dlT;
		else if(dlT==0)	Eb = EDsi/dsT;
		else
		{
			double Fs = dsT/dist;
			double A0 = CP154606.F_A_2_1_2(Fs,Ptime);
			double delta = EDsi/dsT - EDli/dlT;
			double V = max(1.0 , 1.0 + delta/40.0);
			double A = pow(A0 , V);
			Eb = (1.0-A)*EDli/dlT + A*EDsi/dsT;
		}
	}
	return Eb;	//dBuV/m
}

long CSMS4DCView::QGE06_BCBT_A1(CString AssocAllotID) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT IDst FROM CommonFields WHERE (((AssocAllotID)=\'%s\') AND ((AssignCode)='L'));"),AssocAllotID);
	tbl.Format(_T("SELECT IDst FROM %s WHERE (((AssocAllotID)=\'%s\') AND ((AssignCode)='L'));"),m_qCommonFields,AssocAllotID);
	rs.Open(CRecordset::snapshot, tbl);
	long c = rs.GetRecordCount();
	rs.Close();	DB1.Close();
	return c;
}

long CSMS4DCView::QGE06_BCBT_A5(CString AssocAllotID,CString *GeoLat,CString *GeoLon,CString *Frequency,CString *Pol,
								CString *ERP_h_dbw,CString *ERP_v_dbw,CString *AntCatID,CString *AntHeightAGL,
								CString *AntID,CString *MaxEffHght , CString *AntDir) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;
	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>\'%s\') AND ((AssocAllotID)=\'%s\'));"),_T("---"),AssocAllotID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((AssocAllotID)=\'%s\'));"),m_qCommonFields,_T("---"),AssocAllotID);
	rs.Open(CRecordset::snapshot, tbl);
	long c = rs.GetRecordCount();
	if(c == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		rs.GetFieldValue(_T("GeoLat"),str);				*GeoLat = str;
		rs.GetFieldValue(_T("GeoLon"),str);				*GeoLon = str;
		rs.GetFieldValue(_T("Frequency"),str);			*Frequency = str;
		rs.GetFieldValue(_T("Pol"),str);				*Pol = str;
		rs.GetFieldValue(_T("ERP_h_dbw"),str);			*ERP_h_dbw = str;
		rs.GetFieldValue(_T("ERP_v_dbw"),str);			*ERP_v_dbw = str;
		rs.GetFieldValue(_T("AntCatID"),str);			*AntCatID =  str;
		rs.GetFieldValue(_T("AntHeightAGL"),str);		*AntHeightAGL = str;
		rs.GetFieldValue(_T("AntID"),str);				*AntID = str;
		rs.GetFieldValue(_T("MaxEffHght"),str);			*MaxEffHght = str;
		rs.GetFieldValue(_T("AntDir"),str);				*AntDir = str;
	}
	rs.Close();	DB1.Close();
	return c;
}

long CSMS4DCView::QGE06_BCBT_A2(CString SfnID,CString *GeoLat,CString *GeoLon,CString *Frequency,CString *Pol,
								CString *ERP_h_dbw,CString *ERP_v_dbw,CString *AntCatID,CString *AntHeightAGL,
								CString *AntID,CString *MaxEffHght , CString *AntDir,int mode) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	if		(mode==0)	tbl.Format(_T("SELECT * FROM CommonFields WHERE ((IDst<>\'%s\') AND (SfnID=\'%s\'));"), _T("---") ,SfnID);
//	else if (mode==1)	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));"), SfnID);
	if		(mode==0)	tbl.Format(_T("SELECT * FROM %s WHERE ((IDst<>\'%s\') AND (SfnID=\'%s\'));"),m_qCommonFields, _T("---") ,SfnID);
	else if (mode==1)	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));"), m_qCommonFields, SfnID);
	rs.Open(CRecordset::snapshot, tbl);
	long c = 0;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("GeoLat"),str);				*GeoLat = *GeoLat + _T(",") + str;
			rs.GetFieldValue(_T("GeoLon"),str);				*GeoLon = *GeoLon + _T(",") + str;
			rs.GetFieldValue(_T("Frequency"),str);			*Frequency = *Frequency + _T(",") + str;
			rs.GetFieldValue(_T("Pol"),str);				*Pol = *Pol + _T(",") + str;
			rs.GetFieldValue(_T("ERP_h_dbw"),str);			*ERP_h_dbw = *ERP_h_dbw + _T(",") + str;
			rs.GetFieldValue(_T("ERP_v_dbw"),str);			*ERP_v_dbw = *ERP_v_dbw + _T(",") + str;
			rs.GetFieldValue(_T("AntCatID"),str);			*AntCatID = *AntCatID + _T(",") + str;
			rs.GetFieldValue(_T("AntHeightAGL"),str);		*AntHeightAGL = *AntHeightAGL + _T(",") + str;
			rs.GetFieldValue(_T("AntID"),str);				*AntID = *AntID + _T(",") + str;
			rs.GetFieldValue(_T("MaxEffHght"),str);			*MaxEffHght = *MaxEffHght + _T(",") + str;
			rs.GetFieldValue(_T("AntDir"),str);				*AntDir = *AntDir + _T(",") + str;
			c++;
			rs.MoveNext();
		}
	}
	rs.Close();	DB1.Close();
	(*GeoLat).Delete(0);		(*GeoLon).Delete(0);		(*Frequency).Delete(0);
	(*Pol).Delete(0);			(*ERP_h_dbw).Delete(0);		(*ERP_v_dbw).Delete(0);
	(*AntCatID).Delete(0);		(*AntHeightAGL).Delete(0);	(*AntID).Delete(0);
	(*MaxEffHght).Delete(0);	(*AntDir).Delete(0);
	return c;
}

long CSMS4DCView::QGE06_BCBT_A2_1(CString SfnID,CString IDst,CString *strOUT ,int mode) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	if		(mode==0)	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>'---') AND ((IDst)<>\'%s\') AND ((SfnID)=\'%s\'));") , IDst ,SfnID);
//	else if (mode==1)	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>'---' And (IDst)<>\'%s\') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));") , IDst ,SfnID);
	if		(mode==0)	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>'---') AND ((IDst)<>\'%s\') AND ((SfnID)=\'%s\'));") , m_qCommonFields,IDst ,SfnID);
	else if (mode==1)	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>'---' And (IDst)<>\'%s\') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));") , m_qCommonFields,IDst ,SfnID);
	rs.Open(CRecordset::snapshot, tbl);
	long c = 0;
//	double pi = 4.0*atan(1.0);
	CString adm , RLONbs,RLATbs , str1 = _T("");
	CString SiteName,AdmRefID,NoticeType,PlanEntry,AssignCode,Country,Frequency,Pol,AssocAllotID;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("SiteName"),SiteName);
			rs.GetFieldValue(_T("AdmRefID"),AdmRefID);			AdmRefID.Replace('/','_');
			rs.GetFieldValue(_T("NoticeType"),NoticeType);
			rs.GetFieldValue(_T("PlanEntry"),PlanEntry);
			rs.GetFieldValue(_T("AssignCode"),AssignCode);
			rs.GetFieldValue(_T("Country"),Country);			adm = Cty2AdmGE06(&Country);//GEOCTYA((BYTE *)Country.GetBufferSetLength(3), (BYTE *)adm.GetBufferSetLength(3));
			rs.GetFieldValue(_T("Frequency"),Frequency);
			rs.GetFieldValue(_T("GeoLon"),str);				float RLON   = (float)((pi/180.0)*atof(str)) ;
			rs.GetFieldValue(_T("GeoLat"),str);				float RLAT   = (float)((pi/180.0)*atof(str));
			Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
			rs.GetFieldValue(_T("Pol"),Pol);
			rs.GetFieldValue(_T("AssocAllotID"),AssocAllotID);
			rs.GetFieldValue(_T("SfnID"),SfnID);

			str.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s" , _T("AS") , SiteName, AdmRefID, NoticeType, PlanEntry, AssignCode, Country,adm, Frequency, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
			str1 = str1 + _T(",") + str;
			c++;
			rs.MoveNext();
		}
		str1.Delete(0);
	}
	rs.Close();	DB1.Close();
	*strOUT = str1;
	return c;
}

CString CSMS4DCView::QGE06_BCBT_A5_2(CString AssocAllotID) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>\'%s\') AND ((AssocAllotID)=\'%s\'));"),_T("---"),AssocAllotID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((AssocAllotID)=\'%s\'));"),m_qCommonFields, _T("---"),AssocAllotID);
	rs.Open(CRecordset::snapshot, tbl);

//	double pi = 4.0*atan(1.0);
	CString adm , RLONbs,RLATbs , str1 = _T("");
	CString SiteName,AdmRefID,NoticeType,PlanEntry,AssignCode,Country,Frequency,Pol,SfnID;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");

		rs.GetFieldValue(_T("SiteName"),SiteName);
		rs.GetFieldValue(_T("AdmRefID"),AdmRefID);			AdmRefID.Replace('/','_');
		rs.GetFieldValue(_T("NoticeType"),NoticeType);
		rs.GetFieldValue(_T("PlanEntry"),PlanEntry);
		rs.GetFieldValue(_T("AssignCode"),AssignCode);
		rs.GetFieldValue(_T("Country"),Country);			adm = Cty2AdmGE06(&Country);//GEOCTYA((BYTE *)Country.GetBufferSetLength(3), (BYTE *)adm.GetBufferSetLength(3));
		rs.GetFieldValue(_T("Frequency"),Frequency);
		rs.GetFieldValue(_T("GeoLon"),str);				float RLON   = (float)((pi/180.0)*atof(str)) ;
		rs.GetFieldValue(_T("GeoLat"),str);				float RLAT   = (float)((pi/180.0)*atof(str));
		Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
		rs.GetFieldValue(_T("Pol"),Pol);
		rs.GetFieldValue(_T("SfnID"),SfnID);

		str.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s" , _T("AS") , SiteName, AdmRefID, NoticeType, PlanEntry, AssignCode, Country,adm, Frequency, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
		str1 = str1 + _T(",") + str;
		str1.Delete(0);
	}
	rs.Close();	DB1.Close();
	return str1;
}

CString CSMS4DCView::QGE06_BCBT_A5_1(CString AdmRefID) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
///	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)=\'%s\') AND ((AdmRefID)=\'%s\') AND ((SfnID) Is Null));"),_T("---"),AdmRefID);
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)=\'%s\') AND ((AdmRefID)=\'%s\') AND ((SfnID)='' Or (SfnID) Is Null));"),_T("---"),AdmRefID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)=\'%s\') AND ((AdmRefID)=\'%s\') AND ((SfnID)='' Or (SfnID) Is Null));"),m_qCommonFields,_T("---"),AdmRefID);
	rs.Open(CRecordset::snapshot, tbl);
	CString str1 = _T("");
//	double pi = 4.0*atan(1.0);
	CString adm ;
	CString SiteName,NoticeType,PlanEntry,AssignCode,Country,Frequency,Pol,SfnID,AssocAllotID;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");

		rs.GetFieldValue(_T("SiteName"),SiteName);
		AdmRefID.Replace('/','_');
		rs.GetFieldValue(_T("NoticeType"),NoticeType);
		rs.GetFieldValue(_T("PlanEntry"),PlanEntry);
		rs.GetFieldValue(_T("AssignCode"),AssignCode);
		rs.GetFieldValue(_T("Country"),Country);			adm = Cty2AdmGE06(&Country);//GEOCTYA((BYTE *)Country.GetBufferSetLength(3), (BYTE *)adm.GetBufferSetLength(3));
		rs.GetFieldValue(_T("Frequency"),Frequency);
		rs.GetFieldValue(_T("Pol"),Pol);
		rs.GetFieldValue(_T("AssocAllotID"),AssocAllotID);
		rs.GetFieldValue(_T("SfnID"),SfnID);

		str.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s" , _T("AL") , SiteName, AdmRefID, NoticeType, PlanEntry, AssignCode, Country,adm, Frequency, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
		str1 = str1 + _T(",") + str;
		str1.Delete(0);
	}
	rs.Close();	DB1.Close();
	return str1;
}

CString CSMS4DCView::QGE06_BCBT_A4_2(CString SfnID) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)='---') AND ((SfnID)=\'%s\'));") ,SfnID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)='---') AND ((SfnID)=\'%s\'));") ,m_qCommonFields,SfnID);
	rs.Open(CRecordset::snapshot, tbl);
	
	CString str1 = _T("");
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
//		double pi = 4.0*atan(1.0);
		CString adm;
		CString SiteName,AdmRefID,NoticeType,PlanEntry,AssignCode,Country,Frequency,Pol,AssocAllotID;

		rs.GetFieldValue(_T("SiteName"),SiteName);
		rs.GetFieldValue(_T("AdmRefID"),AdmRefID);			AdmRefID.Replace('/','_');
		rs.GetFieldValue(_T("NoticeType"),NoticeType);
		rs.GetFieldValue(_T("PlanEntry"),PlanEntry);
		rs.GetFieldValue(_T("AssignCode"),AssignCode);
		rs.GetFieldValue(_T("Country"),Country);			adm = Cty2AdmGE06(&Country);//GEOCTYA((BYTE *)Country.GetBufferSetLength(3), (BYTE *)adm.GetBufferSetLength(3));
		rs.GetFieldValue(_T("Frequency"),Frequency);
		rs.GetFieldValue(_T("Pol"),Pol);
		rs.GetFieldValue(_T("AssocAllotID"),AssocAllotID);
		rs.GetFieldValue(_T("SfnID"),SfnID);

		str.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s" , _T("AL") , SiteName, AdmRefID, NoticeType, PlanEntry, AssignCode, Country,adm, Frequency, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
		str1 = str1 + _T(",") + str;
		str1.Delete(0);
	}
	rs.Close();	DB1.Close();
	return str1;
}

long CSMS4DCView::QGE06_BCBT_A3_1(long contourkey,long n_tp, CString *lat_tp, CString *lon_tp,double *GRlat , double *GRlon) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
	tbl.Format(_T("SELECT * FROM rrc_contour_pt WHERE (((contourkey)=%ld)) ORDER BY test_pt;"),contourkey);

	rs.Open(CRecordset::snapshot, tbl);
	long c = 0l;

	double lat_deg, lat_min, lat_sec;
	double long_deg, long_min, long_sec;
	int EW , NS;

	double *lat;  lat = new double[n_tp];
	double *lon;  lon = new double[n_tp];
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("long_deg"),str);	long_deg = atof(str);
			rs.GetFieldValue(_T("long_min"),str);	long_min = atof(str);
			rs.GetFieldValue(_T("long_sec"),str);	long_sec = atof(str);
			rs.GetFieldValue(_T("long_ew"),str);	EW = (str==_T("E")) ? 1 : -1; 
			lon[c] = (long_deg + long_min/60.0 + long_sec/3600.0)*EW;	str.Format("%lf",lon[c]);
			*lon_tp = *lon_tp + _T(",") + str;

			rs.GetFieldValue(_T("lat_deg"),str);	lat_deg = atof(str);
			rs.GetFieldValue(_T("lat_min"),str);	lat_min = atof(str);
			rs.GetFieldValue(_T("lat_sec"),str);	lat_sec = atof(str);
			rs.GetFieldValue(_T("lat_ns"),str);		NS = (str==_T("N")) ? 1 : -1; 
			lat[c] = (lat_deg + lat_min/60.0 + lat_sec/3600.0)*NS;	str.Format("%lf",lat[c]);
			*lat_tp = *lat_tp + _T(",") + str;

			c++;
			rs.MoveNext();
		}
		(*lat_tp).Delete(0);		(*lon_tp).Delete(0);
	}
	rs.Close();	DB1.Close();

	double GRlat0 , GRlon0;
	CP154606_Functions CP154606;
	CP154606.GrPointT(lat , lon, n_tp, &GRlat0 , &GRlon0);
	*GRlat = GRlat0;	*GRlon = GRlon0;

	delete [] lat;	delete [] lon;
	return c;
}

long CSMS4DCView::QGE06_BCBT_A3_2(long allotkey , CString *contourkey , CString *nb_test_pts) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
	tbl.Format(_T("SELECT rrc_sub_area.contourkey, rrc_contour.nb_test_pts FROM rrc_sub_area, rrc_contour WHERE (((rrc_sub_area.allotkey)=%ld) AND ((rrc_sub_area.contourkey)=[rrc_contour].[contourkey]));"),allotkey);

	rs.Open(CRecordset::snapshot, tbl);
	long c = 0l;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("contourkey"),str);		*contourkey = *contourkey + _T(",") + str;
			rs.GetFieldValue(_T("nb_test_pts"),str);	*nb_test_pts = *nb_test_pts + _T(",") + str;
			c++;
			rs.MoveNext();
		}
		(*contourkey).Delete(0);		(*nb_test_pts).Delete(0);
	}
	rs.Close();	DB1.Close();
	return c;
}

CString CSMS4DCView::VectorCountry1(CString cty,long *NcontourT) 
{
	cty.TrimLeft();	cty.TrimRight();
	if(cty.GetLength() < 3)		cty = cty + _T("  ");

	unsigned char CTYVEK[4]={""}, BCILR;
	strcpy((char *)CTYVEK,cty);

	float CRDARR[2*15000], DENS=0;
	long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;

	float RLONLL, RLATLL, RLONUR, RLATUR;
	GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
	GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	

	CString FileName =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\") + cty + _T("_C.txt");
	FILE *fp=fopen(FileName,"wt");
	long j=0 , NcontourT0 = 0;
	while(!NOMORE)
	{
		GEOLIW( &ITYPE, (float *)CRDARR, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
		if(NOMORE)	break;

//		if(j>0)
//		fprintf(fp,"%s\n","NaN  NaN");
		for(long p=0;p<NRCRD;p++)
		{
			fprintf(fp," %0.10f  %0.10f\n",CRDARR[2*p],CRDARR[2*p+1]);
			NcontourT0++;
		}//end for
		j++;
	}//end while
	fclose(fp);
	*NcontourT = NcontourT0;
	return FileName;
}


long CSMS4DCView::QGE06_BCBT_Aux_Border(CString cty, CString *lat_tp, CString *lon_tp,double *GRlat , double *GRlon) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;
	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
	tbl.Format(_T("SELECT test_pt, long_deg, long_min, long_sec, long_ew, lat_deg, lat_min, lat_sec, lat_ns,nb_test_pts FROM rrc_aux_border_contour, rrc_aux_border_contour_pt WHERE (((ctry)=\'%s\') AND ((rrc_aux_border_contour.contourkey)=[rrc_aux_border_contour_pt].[contourkey])) ORDER BY test_pt;"),cty); 
	rs.Open(CRecordset::snapshot, tbl);
	long n_tp , c = 0;

	double lat_deg, lat_min, lat_sec , long_deg, long_min, long_sec , GRlat0 , GRlon0;
	int EW , NS;
	if(rs.GetRecordCount() == 1)
	{
		CString str = _T("");
		rs.GetFieldValue(_T("nb_test_pts"),str);	n_tp = atol(str);
		double *lat;  lat = new double[n_tp];
		double *lon;  lon = new double[n_tp];

		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("long_deg"),str);	long_deg = atof(str);
			rs.GetFieldValue(_T("long_min"),str);	long_min = atof(str);
			rs.GetFieldValue(_T("long_sec"),str);	long_sec = atof(str);
			rs.GetFieldValue(_T("long_ew"),str);	EW = (str==_T("E")) ? 1 : -1; 
			lon[c] = (long_deg + long_min/60.0 + long_sec/3600.0)*EW;	str.Format("%lf",lon[c]);
			*lon_tp = *lon_tp + _T(",") + str;

			rs.GetFieldValue(_T("lat_deg"),str);	lat_deg = atof(str);
			rs.GetFieldValue(_T("lat_min"),str);	lat_min = atof(str);
			rs.GetFieldValue(_T("lat_sec"),str);	lat_sec = atof(str);
			rs.GetFieldValue(_T("lat_ns"),str);		NS = (str==_T("N")) ? 1 : -1; 
			lat[c] = (lat_deg + lat_min/60.0 + lat_sec/3600.0)*NS;	str.Format("%lf",lat[c]);
			*lat_tp = *lat_tp + _T(",") + str;

			c++;
			rs.MoveNext();
		}
		(*lat_tp).Delete(0);	(*lon_tp).Delete(0);

		CP154606_Functions CP154606;
		CP154606.GrPointT(lat , lon, n_tp, &GRlat0 , &GRlon0);
		delete [] lat;		delete [] lon;
	}
	rs.Close();		DB1.Close();
	*GRlat = GRlat0;	*GRlon = GRlon0;
	return c;
}

int CSMS4DCView::GE06_PEC(CString AdmRefID , CString AssocAllotID , CString PlanEntry , CString SfnID , CString STN) 
{
	int PEC = 0;
	if(PlanEntry.IsEmpty())
	{
		int SFN,ALLOT;

		if		((STN==_T("ASS"))||(STN==_T("AST"))||(STN==_T("ALS"))||(STN==_T("ALT")))	SFN = !(SfnID.IsEmpty());

		if		((STN==_T("ASS"))||(STN==_T("AST")))	ALLOT = !(AssocAllotID.IsEmpty());
		else if	((STN==_T("ALS"))||(STN==_T("ALT")))	ALLOT = QGE06_BCBT_A1(AdmRefID);

		if     (((STN==_T("ASS"))||(STN==_T("AST")))&&(SFN==0)&&(ALLOT==0))		PEC = 1;
		else if(((STN==_T("ASS"))||(STN==_T("AST")))&&(SFN==1)&&(ALLOT==0))		PEC = 2;
		else if(((STN==_T("ALS"))||(STN==_T("ALT")))&&(ALLOT==0))				PEC = 3;
		else if(((STN==_T("ASS"))||(STN==_T("AST"))||(STN==_T("ALS"))||(STN==_T("ALT")))&&(SFN==1)&&(ALLOT==1))	PEC = 4;
		else if(((STN==_T("ASS"))||(STN==_T("AST"))||(STN==_T("ALS"))||(STN==_T("ALT")))&&(SFN==0)&&(ALLOT==1))	PEC = 5;
	}
	else	PEC = atoi(PlanEntry);
	return PEC;
}

CString CSMS4DCView::QGE06_BCBT_A4_1(CString SfnID) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)='---') AND ((SfnID)=\'%s\'));") ,SfnID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)='---') AND ((SfnID)=\'%s\'));") ,m_qCommonFields,SfnID);
	rs.Open(CRecordset::snapshot, tbl);
	
	CString strT = _T("");
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		rs.GetFieldValue(_T("allotkey"),str);		strT = str;
		rs.GetFieldValue(_T("Fragment"),str);		strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("NoticeType"),str);		strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("AdmRefID"),str);		strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("AssocAllotID"),str);	strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("PlanEntry"),str);		strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("RefPlanCfg"),str);		strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("TypRefNetwk"),str);	strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("GeoArea"),str);		strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("Pol"),str);			strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("SysVar"),str);			strT = strT + _T(",") + str;
		rs.GetFieldValue(_T("SpectMask"),str);		strT = strT + _T(",") + str;
	}
	rs.Close();	DB1.Close();
	return strT;
}

CString CSMS4DCView::QGE06_BCBT_A0(double latContour_deg[],double lonContour_deg[],int nContour,CString cty1, double FStrig, long *Ncty, int mode, double hR, CString BCBT) 
{
//	double pi = 4.0*atan(1.0);
	long NRPNT = nContour, IGCTY = 1, MAXCTY = 400,  IREST , NOCTY;
	unsigned char CTYCOD[1400];
	float (*CRDARR)[2];		CRDARR = new float[nContour][2];
	for(int i=0;i<nContour;i++)
	{
		CRDARR[i][0] = (float)((pi/180.0)*lonContour_deg[i]) ;
		CRDARR[i][1] = (float)((pi/180.0)*latContour_deg[i]) ;
	}
	GEOCIA( (float *)CRDARR, &NRPNT, &IGCTY, (BYTE *)cty1.GetBufferSetLength(3),&MAXCTY, &NOCTY, (unsigned char *)CTYCOD, &IREST);
	delete [] CRDARR;
	char temp[4];
	long Ncty0 = 0;
	CString strY = _T("");
	if(NOCTY>0)
	{
		CP154606_Functions CP154606;
		CString ADM0, CTY0 , strY1 = _T("");
		for(long i=0;i<NOCTY ;i++)
		{
			temp[0] = CTYCOD[3*i]; temp[1] = CTYCOD[3*i+1]; temp[2] = CTYCOD[3*i+2]; temp[3] = 0;
			CTY0 = temp;
			if(CP154606.GE06_cty(CTY0))
			{
				Ncty0++;
				ADM0 = Cty2AdmGE06(&CTY0);//GEOCTYA((BYTE *)CTY0.GetBufferSetLength(3), (BYTE *)ADM0.GetBufferSetLength(3));
				if		(mode==0)	strY1.Format("%s,%s,%g",CTY0,ADM0,FStrig); 
				else if (mode==2)	strY1.Format("%s,%s,%g,%g",CTY0,ADM0,FStrig,hR); 
				else if (mode==3)	strY1.Format("%s,%s,%g,%g,%s",CTY0,ADM0,FStrig,hR,BCBT); 
				strY = strY + _T(",") + strY1;
			}
		}//for
		strY.Delete(0);
	}//NOCTY
	*Ncty = Ncty0;
	return strY;
}
   
extern "C" int WINAPI GoogleFile(CString mLang, CString InputPath = _T(""));	//GoogleFileDLL.lib
void CSMS4DCView::OnCoordinationGe06Bcbt2bcbt() 
{
	BeginWaitCursor();
	CString CDataBaseSTR;
//	CDataBaseSTR = _T("SELECT * FROM CommonFields WHERE (((Fragment)=\'RC06\' Or (Fragment)=\'GE06A\' Or (Fragment)=\'GE06D\') AND ((AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)=\'---\' Or (AssignCode) Is Null Or (AssignCode)=''));");
	CDataBaseSTR.Format( _T("SELECT * FROM %s WHERE (((Fragment)=\'RC06\' Or (Fragment)=\'GE06A\' Or (Fragment)=\'GE06D\') AND ((AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)=\'---\' Or (AssignCode) Is Null Or (AssignCode)=''));") , m_qCommonFields );
	
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = TRUE;
	datadlg.m_Title = _Z("Wanted Assignment/Allotment");
	if (datadlg.DoModal()==IDOK)
	{
		BeginWaitCursor();
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if(Nrow!=1)
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
			return;
		}
		else	//if (Nrow==1)
		{
			CString m_Sel = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
			CString IDst = GetFld(m_Sel,1),			TerraKey = GetFld(m_Sel,2),			AdmRefID = GetFld(m_Sel,3),
					SiteName = GetFld(m_Sel,4),		GeoLat = GetFld(m_Sel,5),			GeoLon = GetFld(m_Sel,6),
					Fragment = GetFld(m_Sel,8),		PlanEntry = GetFld(m_Sel,10),		AssignCode = GetFld(m_Sel,11),
					SfnID = GetFld(m_Sel,12),		NoticeType = GetFld(m_Sel,13),		GeoArea = GetFld(m_Sel,14),
					RPC = GetFld(m_Sel,15),			Hagl_ST = GetFld(m_Sel,20),			Pol = GetFld(m_Sel,21),
					Frequency = GetFld(m_Sel,22),	AssocAllotID = GetFld(m_Sel,28),	nb_sub_areas = GetFld(m_Sel,29),
					ERP_h_dbw = GetFld(m_Sel,31),	ERP_v_dbw = GetFld(m_Sel,32),		AntCatID = GetFld(m_Sel,33),
					AntID = GetFld(m_Sel,34),		AntDir = GetFld(m_Sel,35),			MaxEffHght = GetFld(m_Sel,36),
					allotkey = GetFld(m_Sel,37),	cty1 = GetFld(m_Sel,7);

//			double pi = 4.0*atan(1.0);
			float RLON   = (float)((pi/180.0)*atof(GeoLon)), RLAT   = (float)((pi/180.0)*atof(GeoLat));
		//	CString cty1("");		GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;

		//	if(cty1.GetLength()==1)			cty1 = cty1 + _T("  ");
		//	else if(cty1.GetLength()==2)	cty1 = cty1 + _T(" ");
		//	CString adm1;	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
			CString adm1 = Cty2AdmGE06(&cty1);

			CP154606_Functions CP154606;
			CString STN = CP154606.GE06_STN(Fragment,NoticeType);
			int PEC = GE06_PEC(AdmRefID , AssocAllotID , PlanEntry , SfnID , STN) ;
			CString NET;	NET.Format("%s%d",STN,PEC);

			if((NET==_T("ASS1"))||(NET==_T("AST1"))||(NET==_T("ASA0")))	/////////A1
			{
				CLoSDLG Pdlg;
				Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0; Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
				Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
				if(Pdlg.DoModal()==IDOK)
				{
					int AZstep = Pdlg.m_step;
					double GRlat , GRlon , frq_MHz;
					GRlat = atof(GeoLat);		GRlon = atof(GeoLon);
					frq_MHz = atof(Frequency);
			
					double FStrig = CP154606.GE06_FStrig(STN,frq_MHz);
					////////////////////////////////////
					int az0[37];
					for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
					double attH0[37], attV0[37];
					if(AntDir==_T("D"))
						GE84pattern(atol(AntCatID),attH0,attV0,Pol);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;		attV0[i] = 0;
						}
					attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
					double attH0[361], attV0[361];
					GE06patternT(atol(AntCatID), AntDir, Pol,attH0,attV0); 

					double latContour_deg[360],lonContour_deg[360];
					double ERP,attnH,attnV,RAZIM , h1 , h10[37] , latC_deg,lonC_deg;

					double t = 1 , h2 = 10 , L = 50;
					int ENV = 0 , srv = 1 , P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double Sradius_km = Pdlg.m_RxH;

					OnDatabaseStationsindesktop2(GRlat,GRlon);
					double Hasl_ST = LatLon2Hg(GRlat,GRlon);
					double Hasgl_ST = Hasl_ST + atof(Hagl_ST);

					double azz, h1_15[360] , lat3km  , lon3km , lat15km , lon15km;
					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					if(datadlg.m_Heff1)
					{
						for(long i=0;i<(360/AZstep);i++)
						{
							azz = (double)(i*AZstep);
							reckon( GRlat,GRlon,  3.0 , azz , &lat3km  , &lon3km) ;
							reckon( GRlat,GRlon, 15.0 , azz , &lat15km , &lon15km) ;
							h1_15[i] = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}
					}
					double d_km , d_km1 , d_km2 , Em;
					progress_num=0;
//					Pol.TrimLeft();		Pol.TrimRight();
			
					LoadMap_IDWMpr(4,GRlat,GRlon , 1500.0); 
					for(int az = 0; az<(360/AZstep) ; az++)
					{
						RAZIM = (double)(az*AZstep);
					//	attnH = Interp2(az0,attH0,RAZIM,37) ;	attnV = Interp2(az0,attV0,RAZIM,37) ;
						attnH = attH0[az*AZstep];	attnV = attV0[az*AZstep];

						if     (Pol==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
						else if(Pol==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
						else if((Pol==_T("M"))||(Pol==_T("U")))		ERP = 10.0*log10(pow(10.0,(atof(ERP_h_dbw)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbw)-attnV)/10.0));
							
						if(!(datadlg.m_Heff1))
						{
							GE84Heff(atol(AntID),atof(MaxEffHght),h10) ;
							h10[36] = h10[0];
							h1 = Interp2(az0,h10,RAZIM,37) ;
						}
						Em = -999.0;

						d_km1 = 0;		d_km2 = Sradius_km;
						d_km = (d_km1 + d_km2)/2.0;

						while(1)
						{
							reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
							/////////////////////////// h1 //////////////////////
							if(datadlg.m_Heff1)
							{
								if (d_km>=15.0)		h1 = h1_15[az];
								else
								{
									reckon( GRlat,GRlon, 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
									reckon( GRlat,GRlon,     d_km , RAZIM , &lat15km , &lon15km) ;
									h1 = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
								}
							}
							Em = E_P1546_06(GRlat,GRlon,latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
							Em = Em - 30.0 + ERP;

							if(fabs(Em-FStrig)<0.1)
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
							}
							else if(Em>=FStrig)
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km1 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
							}
							else
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km2 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									d_km = d_km - 5.0;
									if(d_km<=0)
									{
										latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
										break;
									}
								}
							}

						}//while
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

					}//for
					long Ncty;
					CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty); 

					CString strX , RLONbs,RLATbs;
					Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
					if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS"), SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
					else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS"), SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
					CGE06repDLG1 dlgList;
					dlgList.m_dataX = strX;
					dlgList.m_dataY = strY;
					dlgList.m_rowsY = Ncty+1;
					dlgList.m_GoogleFlag = m_GoogleFlag;
					if(dlgList.DoModal()==IDOK)
					{
						CString FileName;
						AdmRefID.Replace('/','_');
						FileName.Format("%sReports\\%s_%s_BCBT.txt",m_AppPath,adm1,AdmRefID);
						FILE *fpOUT = fopen(FileName,"wt");
						for(int i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
						fclose(fpOUT);
						OnDrawVector(FileName);
						if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang, FileName);
					}
				}//Pdlg
			}/////////A1
			else if((NET==_T("ASS2"))||(NET==_T("AST2")))	/////////A2
			{
				CLoSDLG Pdlg;
				Pdlg.m_kfactor = 4.0/3.0; Pdlg.m_RxH = 1000.0; Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
				Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
				if(Pdlg.DoModal()==IDOK)
				{
					int AZstep = Pdlg.m_step;
					double GRlat , GRlon ,frq_MHz;
					frq_MHz = atof(Frequency);
					double FStrig = CP154606.GE06_FStrig(STN,frq_MHz);

					CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN;
					long numAssign = QGE06_BCBT_A2(SfnID,&GeoLatN,&GeoLonN,&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
													&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN) ;
					double *GeoLatI;		GeoLatI = new double[numAssign];
					double *GeoLonI;		GeoLonI = new double[numAssign];
					double *FrequencyI;		FrequencyI = new double[numAssign];
					double *Hasgl_STI;		Hasgl_STI = new double[numAssign];
					double *ERPI;			ERPI = new double[numAssign*360/AZstep];
					double *h1_15;			h1_15 = new double[numAssign*360/AZstep];

					int az0[37];
					for(int i=0;i<=36;i++)		az0[i] = 10*i;

					CString AntDirI, AntCatIDI,PolI,ERP_h_dbwI , ERP_v_dbwI , AntIDI , MaxEffHghtI;
					double h10[37] , lat3km, lon3km, lat15km, lon15km, Hasl_ST;

				//	double attH0[37], attV0[37];
					double attH0[361], attV0[361];

					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					for(long ASi=0;ASi<numAssign;ASi++)
					{
						GeoLatI[ASi] = atof(GetFld(GeoLatN,ASi+1));
						GeoLonI[ASi] = atof(GetFld(GeoLonN,ASi+1));
						FrequencyI[ASi] = atof(GetFld(FrequencyN,ASi+1));
						Hagl_ST = GetFld(AntHeightAGLN,ASi+1);
						AntDirI = GetFld(AntDirN,ASi+1);
						AntCatIDI = GetFld(AntCatIDN,ASi+1);
						PolI = GetFld(PolN,ASi+1);
						ERP_h_dbwI = GetFld(ERP_h_dbwN,ASi+1);
						ERP_v_dbwI = GetFld(ERP_v_dbwN,ASi+1);
						AntIDI = GetFld(AntIDN,ASi+1);
						MaxEffHghtI = GetFld(MaxEffHghtN,ASi+1);

						OnDatabaseStationsindesktop2(GeoLatI[ASi],GeoLonI[ASi]);
						Hasl_ST = LatLon2Hg(GeoLatI[ASi],GeoLonI[ASi]);
						Hasgl_STI[ASi] = Hasl_ST + atof(Hagl_ST);
/*
						if(AntDirI==_T("D"))
							GE84pattern(atol(AntCatIDI),attH0,attV0,PolI);
						else
							for(int i=0;i<36;i++)
							{
								attH0[i] = 0;	attV0[i] = 0;
							}
						attH0[36] = attH0[0];	attV0[36] = attV0[0];
*/
						GE06patternT(atol(AntCatIDI), AntDirI, PolI,attH0,attV0); 

						for(int az = 0; az<(360/AZstep) ; az++)
						{
							double RAZIM = (double)(az*AZstep);
						//	double attnH = Interp2(az0,attH0,RAZIM,37),	attnV = Interp2(az0,attV0,RAZIM,37) ;
							double attnH = attH0[az*AZstep],	attnV = attV0[az*AZstep];

							if     (PolI==_T("H"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_h_dbwI)-attnH;
							else if(PolI==_T("V"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_v_dbwI)-attnV;
							else if((PolI==_T("M"))||(PolI==_T("U")))	ERPI[az + (360/AZstep)*ASi] = 10.0*log10(pow(10.0,(atof(ERP_h_dbwI)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbwI)-attnV)/10.0));
							if(datadlg.m_Heff1)		//d>15
							{
								reckon( GeoLatI[ASi],GeoLonI[ASi],  3.0 , RAZIM , &lat3km  , &lon3km) ;
								reckon( GeoLatI[ASi],GeoLonI[ASi], 15.0 , RAZIM , &lat15km , &lon15km) ;
								h1_15[az + (360/AZstep)*ASi] = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
							}
							else					//All
							{
								GE84Heff(atol(AntIDI),atof(MaxEffHghtI),h10) ;
								h10[36] = h10[0];
								h1_15[az + (360/AZstep)*ASi] = Interp2(az0,h10,RAZIM,37) ;
							}
							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*numAssign/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*numAssign/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

						}//for az
					}//for ASi

					CP154606.GrPointT(GeoLatI , GeoLonI, numAssign, &GRlat , &GRlon);
					
					double latContour_deg[360] ,lonContour_deg[360] , Em , h1;
					double t = 1, h2 = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double Sradius_km = Pdlg.m_RxH;
					progress_num=0;

					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
					double RAZIM,latC_deg,lonC_deg, d_km, d_km1, d_km2 ,Esum,Esum0;

					for(int az = 0; az<(360/AZstep) ; az++)
					{
						RAZIM = (double)(az*AZstep);
						Esum = -999;
						d_km1 = 0;			d_km2 = Sradius_km;
						d_km = (d_km1 + d_km2)/2.0;

						while(1)
						{
							reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
							Esum0 = 0;
							for( ASi=0;ASi<numAssign;ASi++)
							{
								/////////////////////////// h1 //////////////////////
								if(datadlg.m_Heff1)
								{
									if (d_km>=15.0)		h1 = h1_15[az + (360/AZstep)*ASi];
									else
									{
										reckon(GeoLatI[ASi],GeoLonI[ASi], 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
										reckon(GeoLatI[ASi],GeoLonI[ASi],     d_km , RAZIM , &lat15km , &lon15km) ;
										h1 = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
									}
								}
								else		h1 = h1_15[az + (360/AZstep)*ASi];

								Em = E_P1546_06(GeoLatI[ASi],GeoLonI[ASi],latC_deg,lonC_deg, h1, Hasgl_STI[ASi], FrequencyI[ASi], kfactor, t,h2, ENV,srv,L,P1546Clangle);
								Em = Em - 30.0 + ERPI[az + (360/AZstep)*ASi];
								Esum0 = Esum0 + pow(10.0 , Em/10.0);
							}// for ASi
							Esum = 10.0*log10(Esum0);

							if(fabs(Esum-FStrig)<0.1)
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
							}
							else if(Esum>=FStrig)
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km1 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
							}
							else
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km2 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									d_km = d_km - 5.0;
									if(d_km<=0)
									{
										latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
										break;
									}
								}
							}

						}//while
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					}//for az
					delete [] GeoLatI; delete [] GeoLonI;
					delete [] FrequencyI; delete [] Hasgl_STI; delete [] ERPI; delete [] h1_15;
					long Ncty;
					CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty); 

					CString strX , RLONbs,RLATbs;
					Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
					if(PEC==0) 	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
					else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);

					CString strOUT;
					long cd = QGE06_BCBT_A2_1( SfnID, IDst,&strOUT) ;
					if(cd>0)
						strX = strX +","+ strOUT;

					CGE06repDLG1 dlgList;
					dlgList.m_dataX = strX;
					dlgList.m_dataY = strY;
					dlgList.m_rowsY = Ncty + 1;
					dlgList.m_rowsX = cd + 2;
					dlgList.m_GoogleFlag = m_GoogleFlag;
					if(dlgList.DoModal()==IDOK)
					{
						CString FileName;
						AdmRefID.Replace('/','_');
						FileName.Format("%sReports\\%s_%s_BCBT.txt",m_AppPath,adm1,AdmRefID);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
						fclose(fpOUT);
						OnDrawVector(FileName);	
						if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
					}
				}//Pdlg

			}/////////A2
			else if((NET==_T("ALS3"))||(NET==_T("ALT3")))	/////////A3
			{
				if(GeoArea.IsEmpty())
				{
					CLoSDLG Pdlg;
					Pdlg.m_kfactor = 4.0/3.0; Pdlg.m_RxH = 1000.0; Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
					Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
					if(Pdlg.DoModal()==IDOK)
					{
						int AZstep = Pdlg.m_step;
						CString contourkeyN , nb_test_ptsN;
						long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey) , &contourkeyN , &nb_test_ptsN);
						long *contourkeyI;		contourkeyI = new long[contourkeyNum];
						long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
						double *GRlatC;			GRlatC = new double[contourkeyNum];
						double *GRlonC;			GRlonC = new double[contourkeyNum];
						long NcontourT = 0;
						for(long i=0;i<contourkeyNum;i++)
						{
							contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
							nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
							NcontourT = NcontourT + nb_test_ptsI[i];
						}
						double * lat_TP;   lat_TP = new double[NcontourT];
						double * lon_TP;   lon_TP = new double[NcontourT];
						double * y;		y = lat_TP;
						double * x;		x = lon_TP;
						for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
						{
							CString lat_tpStr, lon_tpStr;
							long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM] ,nb_test_ptsI[iCNUM] , &lat_tpStr, &lon_tpStr , &GRlatC[iCNUM] , &GRlonC[iCNUM]) ;
							for(long jTP=0;jTP<n_tp;jTP++)
							{
								*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
								*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
							}
						}
						double GRlat0 , GRlon0, GRlat , GRlon;
						CP154606.GrPointT(GRlatC , GRlonC, contourkeyNum, &GRlat0 , &GRlon0);
		
//						double pi = 4.0*atan(1.0);
						float POINTgr[1][2];
						POINTgr[0][0] = (float)(GRlon0*pi/180.0);	POINTgr[0][1] = (float)(GRlat0*pi/180.0);
						int uflag = false;
					
						long i1=0,i2=0;
						for( iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
						{
							long n_tp = nb_test_ptsI[iCNUM];
							i2 = i2 + n_tp;
							float (*CRDARR)[2]; CRDARR = new float[n_tp][2];
							long NRPNT = n_tp;
							
							long i3 = 0;
							for(long jTP = i1; jTP<i2 ; jTP++)
							{
								CRDARR[i3][0] = (float)(lon_TP[jTP]*pi/180.0);
								CRDARR[i3][1] = (float)(lat_TP[jTP]*pi/180.0);
								i3++;
							}
							uflag = GEOPIA2((float *)POINTgr, (float *)CRDARR, &NRPNT);
							CRDARR = NULL;
							delete [] CRDARR;
							i1 = i1 + n_tp;
							if(uflag)
							{
								GRlat = GRlat0;		GRlon = GRlon0;		break;
							}
						}
						if(!uflag)
						{
							double dist1 , dist0 = 99999999999.0;
							for( i=0;i<NcontourT;i++)
							{
								dist1 = Distance_km(lat_TP[i],lon_TP[i],GRlat0,GRlon0);		dist0 = min(dist0, dist1);
								if(dist0==dist1)
								{
									GRlat = lat_TP[i];	GRlon = lon_TP[i];
								}
							}
						}
						OnDatabaseStationsindesktop2(GRlat,GRlon);

						double frq_MHz = atof(Frequency);
						CString Band  = CP154606.GE06_Band(frq_MHz);
						double FStrig = CP154606.GE06_FStrig(STN , frq_MHz);

						CString RN = _T("");
						if     (NET==_T("ALT3"))						RN = GetFld(m_Sel,30);
						else if((NET==_T("ALS3"))&&(RPC==_T("RPC4")))	RN = _T("RN5");
						else if((NET==_T("ALS3"))&&(RPC==_T("RPC5")))	RN = _T("RN6");

						double latContour_deg[360] ,lonContour_deg[360] ;
						double t = 1, h2 = 10, L = 50;
						int ENV = 0, srv = 1, P1546Clangle = 0;
						double kfactor = Pdlg.m_kfactor;
						double Sradius_km = Pdlg.m_RxH;
						double latTx[7], lonTx[7] , ERPall[7], Hasgl_ST = 0,h1 = 150;
						int progress_num=0;
						CString progress_str, progress_char = _T("I");
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					
						LoadMap_IDWMpr(4,GRlat,GRlon , 1500.0); 
						double RAZIM, latC_deg,lonC_deg, d_km, d_km1, d_km2, Esum,Esum1, Em ,Esum0;
						long az,jTP,ASi;
						
						for( az = 0; az<(360/AZstep) ; az++)
						{
							RAZIM = (double)(az*AZstep);
							Esum = -999;
							d_km1 = 0, d_km2 = Sradius_km;
							d_km = (d_km1 + d_km2)/2.0;

							while(1)
							{
								reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
								Esum1 = -999;
/*
								double DistLimit = 999999999999 , latmin, lonmin , Dist1;
								for(long jTP=0;jTP<NcontourT;jTP++)
								{
									Dist1 = Distance_km(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP]);
									DistLimit = min(DistLimit , Dist1);
									if(DistLimit == Dist1)
									{
										latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
									}
								}
					//			for(long jTP=0;jTP<NcontourT;jTP++)
								{
					//				int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
									int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,latmin,lonmin,frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
									
									double Em ,Esum0 = 0;
									for(int ASi=0;ASi<N_Tx;ASi++)
									{
										Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, frq_MHz, t,h2, ENV,srv,L);
								//		Em = E_P154606(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									
										Em = Em - 30.0 + ERPall[ASi];
										Esum0 = Esum0 + pow(10.0 , Em/10.0);
									}
								//	Esum1 = max(Esum1 , 10.0*log10(Esum0));
									Esum1 = 10.0*log10(Esum0);
								}
								Esum = Esum1;
*/
								for( jTP=0;jTP<NcontourT;jTP++)
								{
									int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
									
									Esum0 = 0;
									for( ASi=0;ASi<N_Tx;ASi++)
									{
										Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, frq_MHz, t);
								//		Em = E_P1546_06(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
										Em = Em - 30.0 + ERPall[ASi];
										Esum0 = Esum0 + pow(10.0 , Em/10.0);
									}
									Esum1 = max(Esum1 , 10.0*log10(Esum0));
								}
								Esum = Esum1;

								if(fabs(Esum-FStrig)<0.1)
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
								else if(Esum>=FStrig)
								{
									if(d_km1 < (d_km2-10.0))
									{
										d_km1 = d_km;
										d_km = (d_km1 + d_km2)/2.0;
									}
									else
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
									}
								}
								else
								{
									if(d_km1 < (d_km2-10.0))
									{
										d_km2 = d_km;
										d_km = (d_km1 + d_km2)/2.0;
									}
									else
									{
										d_km = d_km - 5.0;
										if(d_km<=0)
										{
											latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
											break;
										}
									}
								}

							}//while

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

						}//for az
						delete [] contourkeyI; delete [] nb_test_ptsI;
						delete [] GRlatC; delete [] GRlonC; delete [] lat_TP; delete [] lon_TP;

						float RLON   = (float)((pi/180.0)*GRlon),  RLAT   = (float)((pi/180.0)*GRlat);
						CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
				//		CString adm1("");	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
						CString adm1 = Cty2AdmGE06(&cty1);

						long Ncty;
						CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty); 

						CString strX , RLONbs,RLATbs;
						Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
						if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
						else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty+1;
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							CString FileName;
							AdmRefID.Replace('/','_');
							FileName.Format("%sReports\\%s_%s_BCBT.txt",m_AppPath,adm1,AdmRefID);
							FILE *fpOUT = fopen(FileName,"wt");
							for( i=0;i<(360/AZstep);i++)
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);
							OnDrawVector(FileName);
							if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
						}
					}//Pdlg
				}//if GeoArea
				else		//!(GeoArea.IsEmpty())
				{
					CLoSDLG Pdlg;
					Pdlg.m_kfactor = 4.0/3.0; Pdlg.m_RxH = 1000.0; Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
					Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
					if(Pdlg.DoModal()==IDOK)
					{
						int AZstep = Pdlg.m_step;
						double GRlat0 , GRlon0, GRlat , GRlon;
						long NcontourT;

			//			CString FileName = VectorCountry1( GeoArea,&NcontourT) ;
			//			char X1[20],Y1[20];
			//			double * lat_TP;   lat_TP = new double[NcontourT];
			//			double * lon_TP;   lon_TP = new double[NcontourT];
			//			FILE *fp1 = fopen(FileName,"rt");
			//			for(long jTP=0;jTP<NcontourT;jTP++)
			//			{
			//				fscanf( fp1, "%s %s", X1,Y1);
			//				lat_TP[jTP] =  atof(Y1);			lon_TP[jTP] =  atof(X1);
			//			}
			//			fclose(fp1);
			//			CP154606.GrPointT(lat_TP , lon_TP, NcontourT, &GRlat0 , &GRlon0);

						CString lat_tpSTR, lon_tpSTR;
						NcontourT = QGE06_BCBT_Aux_Border(GeoArea, &lat_tpSTR, &lon_tpSTR,&GRlat0 , &GRlon0) ;
						double * lat_TP;   lat_TP = new double[NcontourT];
						double * lon_TP;   lon_TP = new double[NcontourT];
						for(long jTP=0;jTP<NcontourT;jTP++)
						{
							lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
							lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
						}
//						double pi = 4.0*atan(1.0);
/*
						float POINTgr[1][2];
						POINTgr[0][0] = (float)(GRlon0*pi/180.0);
						POINTgr[0][1] = (float)(GRlat0*pi/180.0);
						int uflag = false;
						float (*CRDARR1)[2]; CRDARR1 = new float[NcontourT][2];
						long NRPNT = NcontourT;
						for( jTP=0;jTP<NcontourT;jTP++)
						{
							CRDARR1[jTP][0] = (float)(lon_TP[jTP]*pi/180.0);
							CRDARR1[jTP][1] = (float)(lat_TP[jTP]*pi/180.0);
						}
						uflag = GEOPIA2((float *)POINTgr, (float *)CRDARR1, &NRPNT);
						delete [] CRDARR1;
						if(uflag)
						{
							GRlat = GRlat0;				GRlon = GRlon0;
						}
						if(!uflag)
						{
							double dist1 , dist0 = 99999999999.0;
							for(long i=0;i<NcontourT;i++)
							{
								dist1 = Distance_km(lat_TP[i],lon_TP[i],GRlat0,GRlon0);
 								dist0 = min(dist0 , dist1);
								if(dist0==dist1)
								{
									GRlat = lat_TP[i];	GRlon = lon_TP[i];
								}
							}
						}
*/
						GRlat = GRlat0;			GRlon = GRlon0;
						OnDatabaseStationsindesktop2(GRlat,GRlon);

						double frq_MHz = atof(Frequency);
						CString Band  = CP154606.GE06_Band(frq_MHz);
						double FStrig = CP154606.GE06_FStrig(STN , frq_MHz);

						CString RN = _T("");
						if     (NET==_T("ALT3"))						RN = GetFld(m_Sel,30);
						else if((NET==_T("ALS3"))&&(RPC==_T("RPC4")))	RN = _T("RN5");
						else if((NET==_T("ALS3"))&&(RPC==_T("RPC5")))	RN = _T("RN6");

						double latContour_deg[360] ,lonContour_deg[360] ;
						double t = 1, h2 = 10, L = 50;
						int ENV = 0, srv = 1, P1546Clangle = 0;
						double kfactor = Pdlg.m_kfactor;
						double Sradius_km = Pdlg.m_RxH;
						double latTx[7], lonTx[7] , ERPall[7], Hasgl_ST = 0,h1 = 150;
						int progress_num=0;
						CString progress_str, progress_char = _T("I");
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
		
						LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
						double RAZIM,latC_deg,lonC_deg, d_km,d_km1, d_km2,Em ,Esum0,Esum,Esum1;
						
						for(int az = 0; az<(360/AZstep) ; az++)
						{
							RAZIM = (double)(az*AZstep);
							Esum = -999;

							d_km1 = 0;		d_km2 = Sradius_km;
							d_km = (d_km1 + d_km2)/2.0;

							while(1)
							{
								reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
								Esum1 = -999;

								for(long jTP=0;jTP<NcontourT;jTP++)
								{
									int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
					
									Esum0 = 0;
									for(int ASi=0;ASi<N_Tx;ASi++)
									{
										Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, frq_MHz, t);
								//		Em = E_P1546_06(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									
										Em = Em - 30.0 + ERPall[ASi];
										Esum0 = Esum0 + pow(10.0 , Em/10.0);
									}
									Esum1 = max(Esum1 , 10.0*log10(Esum0));
								}
								Esum = Esum1;

								if(fabs(Esum-FStrig)<0.1)
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
								else if(Esum>=FStrig)
								{
									if(d_km1 < (d_km2-10.0))
									{
										d_km1 = d_km;
										d_km = (d_km1 + d_km2)/2.0;
									}
									else
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
									}
								}
								else
								{
									if(d_km1 < (d_km2-10.0))
									{
										d_km2 = d_km;
										d_km = (d_km1 + d_km2)/2.0;
									}
									else
									{
										d_km = d_km - 5.0;
										if(d_km<=0)
										{
											latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
											break;
										}
									}
								}

							}//while
							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}//for az
						delete [] lat_TP;	delete [] lon_TP;

						float RLON   = (float)((pi/180.0)*GRlon), RLAT   = (float)((pi/180.0)*GRlat);
						CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
				//		CString adm1("");	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
						CString adm1 = Cty2AdmGE06(&cty1);
					
						long Ncty;
						CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty); 
						CString strX , RLONbs,RLATbs;
						Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
						if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
						else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);

						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty+1;
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							CString FileName;
							AdmRefID.Replace('/','_');
							FileName.Format("%sReports\\%s_%s_BCBT.txt",m_AppPath,adm1,AdmRefID);
							FILE *fpOUT = fopen(FileName,"wt");
							for(int i=0;i<(360/AZstep);i++)
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);
							OnDrawVector(FileName);
							if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
						}
					}//Pdlg
				}//else GeoArea

			}/////////A3
			else if((NET==_T("ASS4"))||(NET==_T("AST4")))	/////////A4_1
			{
				CLoSDLG Pdlg;
				Pdlg.m_kfactor = 4.0/3.0; Pdlg.m_RxH = 1000.0; Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
				Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
				if(Pdlg.DoModal()==IDOK)
				{
					int AZstep = Pdlg.m_step;
				//+++++++++++++++++++++++++++++++++Assignment+++++++++++++++++++++++++++++++++++++++++++++++++++
					double frq_MHz = atof(Frequency);
					CString Band  = CP154606.GE06_Band(frq_MHz);
					double FStrig = CP154606.GE06_FStrig(STN,frq_MHz);

					CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN;
					long numAssign = QGE06_BCBT_A2(SfnID,&GeoLatN,&GeoLonN,&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
													&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,1) ;
					double *GeoLatI;		GeoLatI = new double[numAssign];
					double *GeoLonI;		GeoLonI = new double[numAssign];
					double *FrequencyI;		FrequencyI = new double[numAssign];
					double *Hasgl_STI;		Hasgl_STI = new double[numAssign];
					double *ERPI;			ERPI = new double[numAssign*360/AZstep];
					double *h1_15;			h1_15 = new double[numAssign*360/AZstep];

					int az0[37];
					for(int i=0;i<=36;i++)	az0[i] = 10*i;

					CString AntDirI, AntCatIDI,PolI,ERP_h_dbwI , ERP_v_dbwI , AntIDI , MaxEffHghtI;
					double h10[37], lat3km  , lon3km , lat15km , lon15km, Hasl_ST;

				//	double attH0[37], attV0[37];
					double attH0[361], attV0[361];

					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					for(long ASi=0;ASi<numAssign;ASi++)
					{
						GeoLatI[ASi] = atof(GetFld(GeoLatN,ASi+1));
						GeoLonI[ASi] = atof(GetFld(GeoLonN,ASi+1));
						FrequencyI[ASi] = atof(GetFld(FrequencyN,ASi+1));
						Hagl_ST = GetFld(AntHeightAGLN,ASi+1);
						AntDirI = GetFld(AntDirN,ASi+1);
						AntCatIDI = GetFld(AntCatIDN,ASi+1);
						PolI = GetFld(PolN,ASi+1);
						ERP_h_dbwI = GetFld(ERP_h_dbwN,ASi+1);
						ERP_v_dbwI = GetFld(ERP_v_dbwN,ASi+1);
						AntIDI = GetFld(AntIDN,ASi+1);
						MaxEffHghtI = GetFld(MaxEffHghtN,ASi+1);

						OnDatabaseStationsindesktop2(GeoLatI[ASi],GeoLonI[ASi]);
						Hasl_ST = LatLon2Hg(GeoLatI[ASi],GeoLonI[ASi]);
						Hasgl_STI[ASi] = Hasl_ST + atof(Hagl_ST);
/*
						if(AntDirI==_T("D"))
							GE84pattern(atol(AntCatIDI),attH0,attV0,PolI);
						else
							for(int i=0;i<36;i++)
							{
								attH0[i] = 0;		attV0[i] = 0;
							}
						attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
						GE06patternT(atol(AntCatIDI), AntDirI, PolI,attH0,attV0); 

						for(int az = 0; az<(360/AZstep) ; az++)
						{
							double RAZIM = (double)(az*AZstep);
						//	double attnH = Interp2(az0,attH0,RAZIM,37), attnV = Interp2(az0,attV0,RAZIM,37) ;
							double attnH = attH0[az*AZstep],	attnV = attV0[az*AZstep];

							if     (PolI==_T("H"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_h_dbwI)-attnH;
							else if(PolI==_T("V"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_v_dbwI)-attnV;
							else if((PolI==_T("M"))||(PolI==_T("U")))	ERPI[az + (360/AZstep)*ASi] = 10.0*log10(pow(10.0,(atof(ERP_h_dbwI)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbwI)-attnV)/10.0));
							if(datadlg.m_Heff1)		//d>15
							{
								reckon( GeoLatI[ASi],GeoLonI[ASi],  3.0 , RAZIM , &lat3km  , &lon3km) ;
								reckon( GeoLatI[ASi],GeoLonI[ASi], 15.0 , RAZIM , &lat15km , &lon15km) ;
								h1_15[az + (360/AZstep)*ASi] = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
							}
							else					//All
							{
								GE84Heff(atol(AntIDI),atof(MaxEffHghtI),h10) ;
								h10[36] = h10[0];
								h1_15[az + (360/AZstep)*ASi] = Interp2(az0,h10,RAZIM,37) ;
							}
							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*numAssign/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*numAssign/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}//for az
					}//for ASi
				//+++++++++++++++++++++++++++++++++Allotment+++++++++++++++++++++++++++++++++++++++++++++++++++
					CString AllotmentSTR = QGE06_BCBT_A4_1(SfnID) ;
					CString GeoAreaAL = GetFld(AllotmentSTR,9) ;

					double GRlat0 , GRlon0, GRlat , GRlon/*, pi = 4.0*atan(1.0)*/;
					long NcontourT = 0;
					double * lat_TP;		double * lon_TP;

					if(GeoAreaAL.IsEmpty())
					{
						CString contourkeyN , nb_test_ptsN;
						long contourkeyNum = QGE06_BCBT_A3_2(atol(GetFld(AllotmentSTR,1)) , &contourkeyN , &nb_test_ptsN);
						long *contourkeyI;		contourkeyI = new long[contourkeyNum];
						long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
						double *GRlatC;			GRlatC = new double[contourkeyNum];
						double *GRlonC;			GRlonC = new double[contourkeyNum];
						for( i=0;i<contourkeyNum;i++)
						{
							contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
							nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
							NcontourT = NcontourT + nb_test_ptsI[i];
						}
						lat_TP = new double[NcontourT];		lon_TP = new double[NcontourT];
						double * y;		y = lat_TP;
						double * x;		x = lon_TP;
						for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
						{
							CString lat_tpStr, lon_tpStr;
							long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM] ,nb_test_ptsI[iCNUM] , &lat_tpStr, &lon_tpStr , &GRlatC[iCNUM] , &GRlonC[iCNUM]) ;
							for(long jTP=0;jTP<n_tp;jTP++)
							{
								*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
								*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
							}
						}
						CP154606.GrPointT(GRlatC , GRlonC, contourkeyNum, &GRlat0 , &GRlon0);
		
						float POINTgr[1][2];
						POINTgr[0][0] = (float)(GRlon0*pi/180.0); POINTgr[0][1] = (float)(GRlat0*pi/180.0);
						int uflag = false;
						long i1=0,i2=0;
						for( iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
						{
							long n_tp = nb_test_ptsI[iCNUM];
							i2 = i2 + n_tp;
							float (*CRDARR)[2]; CRDARR = new float[n_tp][2];
							long NRPNT = n_tp, i3 = 0;
							for(long jTP = i1 ; jTP<i2 ; jTP++)
							{
								CRDARR[i3][0] = (float)(lon_TP[jTP]*pi/180.0);
								CRDARR[i3][1] = (float)(lat_TP[jTP]*pi/180.0);
								i3++;
							}
							uflag = GEOPIA2((float *)POINTgr, (float *)CRDARR, &NRPNT);
							CRDARR = NULL;
							delete [] CRDARR;
							i1 = i1 + n_tp;
							if(uflag)
							{
								GRlat = GRlat0;		GRlon = GRlon0;		break;
							}
						}
						if(!uflag)
						{
							double dist1 , dist0 = 99999999999.0;
							for( i=0;i<NcontourT;i++)
							{
								dist1 = Distance_km(lat_TP[i],lon_TP[i],GRlat0,GRlon0);	dist0 = min(dist0, dist1);
								if(dist0==dist1)
								{
									GRlat = lat_TP[i];	GRlon = lon_TP[i];
								}
							}
						}
						delete [] contourkeyI; delete [] nb_test_ptsI; delete [] GRlatC; delete [] GRlonC;
					}//	if(GeoAreaAL.IsEmpty())
					else
					{
						CString lat_tpSTR, lon_tpSTR;
						NcontourT = QGE06_BCBT_Aux_Border(GeoAreaAL, &lat_tpSTR, &lon_tpSTR,&GRlat0 , &GRlon0) ;
						lat_TP = new double[NcontourT];		lon_TP = new double[NcontourT];
						for(long jTP=0;jTP<NcontourT;jTP++)
						{
							lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
							lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
						}
						GRlat = GRlat0;			GRlon = GRlon0;

					}//	else(GeoAreaAL.IsEmpty())
					OnDatabaseStationsindesktop2(GRlat,GRlon);
			//00000000000000000000000000000000000000000000000000000000000000000000000000
					CString STNal = CP154606.GE06_STN(GetFld(AllotmentSTR,2),GetFld(AllotmentSTR,3));
					int PECal = GE06_PEC(GetFld(AllotmentSTR,4) , GetFld(AllotmentSTR,5) , GetFld(AllotmentSTR,6) , SfnID , STNal) ;
					CString NETal;	NETal.Format("%s%d",STNal,PECal);
					CString RPCal = GetFld(AllotmentSTR,7);

					CString RNal = _T("");
					if     (NETal==_T("ALT4"))							RNal = GetFld(AllotmentSTR,8);
					else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC4")))	RNal = _T("RN5");
					else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC5")))	RNal = _T("RN6");
			//00000000000000000000000000000000000000000000000000000000000000000000000000
					double latContour_deg[360] ,lonContour_deg[360] ;
					double t = 1, h2 = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double Sradius_km = Pdlg.m_RxH;
					double latTx[7], lonTx[7] , ERPall[7], Em , h1;
					progress_num=0;
					
					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
					double latC_deg,lonC_deg, RAZIM, EsumASS,EsumALLOT , Esum, Esum0, Esum1, d_km, d_km1, d_km2;
					for(int az = 0; az<(360/AZstep) ; az++)
					{
						RAZIM = (double)(az*AZstep);
						Esum = -999;

						d_km1 = 0;		d_km2 = Sradius_km;
						d_km = (d_km1 + d_km2)/2.0;;
						while(1)
						{
							reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
							Esum0 = 0;
							for( ASi=0;ASi<numAssign;ASi++)
							{
								/////////////////////////// h1 //////////////////////
								if(datadlg.m_Heff1)
								{
									if (d_km>=15.0)		h1 = h1_15[az + (360/AZstep)*ASi];
									else
									{
										reckon(GeoLatI[ASi],GeoLonI[ASi], 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
										reckon(GeoLatI[ASi],GeoLonI[ASi],     d_km , RAZIM , &lat15km , &lon15km) ;
										h1 = Hasgl_STI[ASi] - Points2HgAvr1(lat3km , lon3km,lat15km , lon15km,120);
									}
								}
								else		h1 = h1_15[az + (360/AZstep)*ASi];

								Em = E_P1546_06(GeoLatI[ASi],GeoLonI[ASi],latC_deg,lonC_deg, h1, Hasgl_STI[ASi], FrequencyI[ASi], kfactor, t,h2, ENV,srv,L,P1546Clangle);
								Em = Em - 30.0 + ERPI[az + (360/AZstep)*ASi];
								Esum0 = Esum0 + pow(10.0 , Em/10.0);
							}// for ASi
							EsumASS = 10.0*log10(Esum0);

							Esum1 = -999;
/*
							double DistLimit = 999999999999 , latmin, lonmin , Dist1;
							for(long jTP=0;jTP<NcontourT;jTP++)
							{
								Dist1 = Distance_km(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP]);
								DistLimit = min(DistLimit , Dist1);
								if(DistLimit == Dist1)
								{
									latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
								}
							}
				//			for(long jTP=0;jTP<NcontourT;jTP++)
							{
				//				int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
								int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,latmin,lonmin,frq_MHz,Band,RPCal,RNal, ERPall,latTx,lonTx) ;
								
								double Esum0 = 0;
								for(int ASi=0;ASi<N_Tx;ASi++)
								{
									Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150, frq_MHz, t,h2, ENV,srv,L);

							//		Em = E_P154606(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									Em = Em - 30.0 + ERPall[ASi];
									Esum0 = Esum0 + pow(10.0 , Em/10.0);
								}
								Esum1 = max(Esum1 , 10.0*log10(Esum0));
							}
							EsumALLOT = Esum1;
							Esum = max(EsumASS,EsumALLOT);
*/
							for(long jTP=0;jTP<NcontourT;jTP++)
							{
								int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPCal,RNal, ERPall,latTx,lonTx) ;
								
								Esum0 = 0;
								for(int ASi=0;ASi<N_Tx;ASi++)
								{
								//	Em = E_P1546_06(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150, 0, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150.0, frq_MHz, t);
								
									Em = Em - 30.0 + ERPall[ASi];
									Esum0 = Esum0 + pow(10.0 , Em/10.0);
								}
								Esum1 = max(Esum1 , 10.0*log10(Esum0));
							}
							EsumALLOT = Esum1;
							Esum = max(EsumASS,EsumALLOT);

							if(fabs(Esum-FStrig)<0.1)
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
							}
							else if(Esum>=FStrig)
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km1 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
							}
							else
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km2 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									d_km = d_km - 5.0;
									if(d_km<=0)
									{
										latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
										break;
									}
								}
							}

						}//while
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

					}//for az
					delete [] GeoLatI; delete [] GeoLonI; delete [] FrequencyI; delete [] Hasgl_STI;
					delete [] ERPI; delete [] h1_15; delete [] lat_TP; delete [] lon_TP;
					long Ncty;
					CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty); 

					CString strX , RLONbs,RLATbs;
					Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
					if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
					else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);

					CString strOUT;
					long cd = QGE06_BCBT_A2_1( SfnID, IDst,&strOUT,1) ;
					if(cd>0)
						strX = strX +","+ strOUT;

					CString alLink = QGE06_BCBT_A4_2( SfnID) ;
					strX = strX +","+ alLink;

					CGE06repDLG1 dlgList;
					dlgList.m_dataX = strX;
					dlgList.m_dataY = strY;
					dlgList.m_rowsY = Ncty + 1;
					dlgList.m_rowsX = cd + 2 + 1;
					dlgList.m_GoogleFlag = m_GoogleFlag;
					if(dlgList.DoModal()==IDOK)
					{
						CString FileName;
						AdmRefID.Replace('/','_');
						FileName.Format("%sReports\\%s_%s_BCBT.txt",m_AppPath,adm1,AdmRefID);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
						fclose(fpOUT);
						OnDrawVector(FileName);
						if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
					}
				}//Pdlg
			}/////////A4_1
			else if((NET==_T("ALS4"))||(NET==_T("ALT4")))	/////////A4_2
			{
				CLoSDLG Pdlg;
				Pdlg.m_kfactor = 4.0/3.0; Pdlg.m_RxH = 1000.0; Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
				Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
				if(Pdlg.DoModal()==IDOK)
				{
					int AZstep = Pdlg.m_step;
				//+++++++++++++++++++++++++++++++++Assignment+++++++++++++++++++++++++++++++++++++++++++++++++++
					double frq_MHz = atof(Frequency);
					CString Band  = CP154606.GE06_Band(frq_MHz);
					double FStrig = CP154606.GE06_FStrig(STN,frq_MHz);

					CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN;
					long numAssign = QGE06_BCBT_A2(SfnID,&GeoLatN,&GeoLonN,&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
													&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,1) ;
					double *GeoLatI;		GeoLatI = new double[numAssign];
					double *GeoLonI;		GeoLonI = new double[numAssign];
					double *FrequencyI;		FrequencyI = new double[numAssign];
					double *Hasgl_STI;		Hasgl_STI = new double[numAssign];
					double *ERPI;			ERPI = new double[numAssign*360/AZstep];
					double *h1_15;			h1_15 = new double[numAssign*360/AZstep];

					int az0[37];
					for(int i=0;i<=36;i++)		az0[i] = 10*i;

					CString AntDirI, AntCatIDI,PolI,ERP_h_dbwI , ERP_v_dbwI , AntIDI , MaxEffHghtI;
					double h10[37], lat3km  , lon3km , lat15km , lon15km, Hasl_ST;

				//	double attH0[37], attV0[37];
					double attH0[361], attV0[361];

					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					for(long ASi=0;ASi<numAssign;ASi++)
					{
						GeoLatI[ASi] = atof(GetFld(GeoLatN,ASi+1));
						GeoLonI[ASi] = atof(GetFld(GeoLonN,ASi+1));
						FrequencyI[ASi] = atof(GetFld(FrequencyN,ASi+1));
						Hagl_ST = GetFld(AntHeightAGLN,ASi+1);
						AntDirI = GetFld(AntDirN,ASi+1);
						AntCatIDI = GetFld(AntCatIDN,ASi+1);
						PolI = GetFld(PolN,ASi+1);
						ERP_h_dbwI = GetFld(ERP_h_dbwN,ASi+1);
						ERP_v_dbwI = GetFld(ERP_v_dbwN,ASi+1);
						AntIDI = GetFld(AntIDN,ASi+1);
						MaxEffHghtI = GetFld(MaxEffHghtN,ASi+1);

						OnDatabaseStationsindesktop2(GeoLatI[ASi],GeoLonI[ASi]);
						Hasl_ST = LatLon2Hg(GeoLatI[ASi],GeoLonI[ASi]);
						Hasgl_STI[ASi] = Hasl_ST + atof(Hagl_ST);
/*
						if(AntDirI==_T("D"))
							GE84pattern(atol(AntCatIDI),attH0,attV0,PolI);
						else
							for(int i=0;i<36;i++)
							{
								attH0[i] = 0;		attV0[i] = 0;
							}
						attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
						GE06patternT(atol(AntCatIDI), AntDirI, PolI,attH0,attV0); 

						for(int az = 0; az<(360/AZstep) ; az++)
						{
							double RAZIM = (double)(az*AZstep);
						//	double attnH = Interp2(az0,attH0,RAZIM,37), attnV = Interp2(az0,attV0,RAZIM,37) ;
							double attnH = attH0[az*AZstep],	attnV = attV0[az*AZstep];

							if     (PolI==_T("H"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_h_dbwI)-attnH;
							else if(PolI==_T("V"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_v_dbwI)-attnV;
							else if((PolI==_T("M"))||(PolI==_T("U")))	ERPI[az + (360/AZstep)*ASi] = 10.0*log10(pow(10.0,(atof(ERP_h_dbwI)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbwI)-attnV)/10.0));
							if(datadlg.m_Heff1)		//d>15
							{
								reckon( GeoLatI[ASi],GeoLonI[ASi],  3.0 , RAZIM , &lat3km  , &lon3km) ;
								reckon( GeoLatI[ASi],GeoLonI[ASi], 15.0 , RAZIM , &lat15km , &lon15km) ;
								h1_15[az + (360/AZstep)*ASi] = Hasgl_STI[ASi] - Points2HgAvr1(lat3km , lon3km,lat15km , lon15km,120);
							}
							else					//All
							{
								GE84Heff(atol(AntIDI),atof(MaxEffHghtI),h10) ;
								h10[36] = h10[0];
								h1_15[az + (360/AZstep)*ASi] = Interp2(az0,h10,RAZIM,37) ;
							}
							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*numAssign/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*numAssign/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

						}//for az
					}//for ASi
				//+++++++++++++++++++++++++++++++++Allotment+++++++++++++++++++++++++++++++++++++++++++++++++++
					double GRlat0 , GRlon0, GRlat , GRlon/*, pi = 4.0*atan(1.0)*/;
					long NcontourT = 0;
					double * lat_TP;			double * lon_TP;
					if(GeoArea.IsEmpty())
					{
						CString contourkeyN , nb_test_ptsN;
						long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey) , &contourkeyN , &nb_test_ptsN);
						long *contourkeyI;		contourkeyI = new long[contourkeyNum];
						long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
						double *GRlatC;			GRlatC = new double[contourkeyNum];
						double *GRlonC;			GRlonC = new double[contourkeyNum];
						for( i=0;i<contourkeyNum;i++)
						{
							contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
							nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
							NcontourT = NcontourT + nb_test_ptsI[i];
						}
						lat_TP = new double[NcontourT];	lon_TP = new double[NcontourT];
						double * y;		y = lat_TP;
						double * x;		x = lon_TP;
						for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
						{
							CString lat_tpStr, lon_tpStr;
							long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM] ,nb_test_ptsI[iCNUM] , &lat_tpStr, &lon_tpStr , &GRlatC[iCNUM] , &GRlonC[iCNUM]) ;
							for(long jTP=0;jTP<n_tp;jTP++)
							{
								*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
								*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
							}
						}
						CP154606.GrPointT(GRlatC , GRlonC, contourkeyNum, &GRlat0 , &GRlon0);
						float POINTgr[1][2];
						POINTgr[0][0] = (float)(GRlon0*pi/180.0);
						POINTgr[0][1] = (float)(GRlat0*pi/180.0);
						int uflag = false;
						long i1=0,i2=0;
						for( iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
						{
							long n_tp = nb_test_ptsI[iCNUM];
							i2 = i2 + n_tp;

							float (*CRDARR)[2]; CRDARR = new float[n_tp][2];
							long NRPNT = n_tp;
							long i3 = 0;
							for(long jTP = i1 ; jTP<i2 ; jTP++)
							{
								CRDARR[i3][0] = (float)(lon_TP[jTP]*pi/180.0);
								CRDARR[i3][1] = (float)(lat_TP[jTP]*pi/180.0);
								i3++;
							}
							uflag = GEOPIA2((float *)POINTgr, (float *)CRDARR, &NRPNT);
							CRDARR = NULL;
							delete [] CRDARR;
							i1 = i1 + n_tp;
							if(uflag)
							{
								GRlat = GRlat0;			GRlon = GRlon0;	break;
							}
						}
						if(!uflag)
						{
							double dist1 , dist0 = 99999999999.0;
							for( i=0;i<NcontourT;i++)
							{
								dist1 = Distance_km(lat_TP[i],lon_TP[i],GRlat0,GRlon0);		dist0 = min(dist0, dist1);
								if(dist0==dist1)
								{
									GRlat = lat_TP[i];	GRlon = lon_TP[i];
								}
							}
						}
						delete [] contourkeyI; delete [] nb_test_ptsI; delete [] GRlatC; delete [] GRlonC;
					}//	if(GeoArea.IsEmpty())
					else
					{
						CString lat_tpSTR, lon_tpSTR;
						NcontourT = QGE06_BCBT_Aux_Border(GeoArea, &lat_tpSTR, &lon_tpSTR,&GRlat0 , &GRlon0) ;
						lat_TP = new double[NcontourT];
						lon_TP = new double[NcontourT];
						for(long jTP=0;jTP<NcontourT;jTP++)
						{
							lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
							lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
						}
						GRlat = GRlat0;			GRlon = GRlon0;
					}//	else(GeoArea.IsEmpty())
					OnDatabaseStationsindesktop2(GRlat,GRlon);
					CString RN = _T("");
					if     (NET==_T("ALT4"))						RN = GetFld(m_Sel,30);
					else if((NET==_T("ALS4"))&&(RPC==_T("RPC4")))	RN = _T("RN5");
					else if((NET==_T("ALS4"))&&(RPC==_T("RPC5")))	RN = _T("RN6");

					double latContour_deg[360] ,lonContour_deg[360] ;
					double t = 1, h2 = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double Sradius_km = Pdlg.m_RxH;
					double latTx[7], lonTx[7] , ERPall[7], Em , h1;
					progress_num=0;

					LoadMap_IDWMpr(4,GRlat,GRlon , 1500.0);
					double d_km, d_km1, d_km2, EsumASS,EsumALLOT , Esum,Esum0,Esum1,latC_deg,lonC_deg, RAZIM;
					for(int az = 0; az<(360/AZstep) ; az++)
					{
						RAZIM = (double)(az*AZstep);
						Esum = -999;

						d_km1 = 0;		d_km2 = Sradius_km;
						d_km = (d_km1 + d_km2)/2.0;

						while(1)
						{
							reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
							Esum0 = 0;
							for( ASi=0;ASi<numAssign;ASi++)
							{
								/////////////////////////// h1 //////////////////////
								if(datadlg.m_Heff1)
								{
									if (d_km>=15.0)		h1 = h1_15[az + (360/AZstep)*ASi];
									else
									{
										reckon(GeoLatI[ASi],GeoLonI[ASi], 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
										reckon(GeoLatI[ASi],GeoLonI[ASi],     d_km , RAZIM , &lat15km , &lon15km) ;
										h1 = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
									}
								}
								else		h1 = h1_15[az + (360/AZstep)*ASi];
								Em = E_P1546_06(GeoLatI[ASi],GeoLonI[ASi],latC_deg,lonC_deg, h1, Hasgl_STI[ASi], FrequencyI[ASi], kfactor, t,h2, ENV,srv,L,P1546Clangle);
								Em = Em - 30.0 + ERPI[az + (360/AZstep)*ASi];
								Esum0 = Esum0 + pow(10.0 , Em/10.0);
							}// for ASi
							EsumASS = 10.0*log10(Esum0);

							Esum1 = -999;
/*
							double DistLimit = 999999999999 , latmin, lonmin , Dist1, Esum1 = -999;
							for(long jTP=0;jTP<NcontourT;jTP++)
							{
								Dist1 = Distance_km(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP]);
								DistLimit = min(DistLimit , Dist1);
								if(DistLimit == Dist1)
								{
									latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
								}
							}
				//			for(long jTP=0;jTP<NcontourT;jTP++)
							{
				//				int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
								int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,latmin,lonmin,frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
								
								double Esum0 = 0;
								for(int ASi=0;ASi<N_Tx;ASi++)
								{
									Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150, frq_MHz, t,h2, ENV,srv,L);

							//		Em = E_P154606(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									Em = Em - 30.0 + ERPall[ASi];
									Esum0 = Esum0 + pow(10.0 , Em/10.0);
								}
								Esum1 = max(Esum1 , 10.0*log10(Esum0));
							}
							EsumALLOT = Esum1;
*/
							for(long jTP=0;jTP<NcontourT;jTP++)
							{
								int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
								
								Esum0 = 0;
								for(int ASi=0;ASi<N_Tx;ASi++)
								{
								//	Em = E_P1546_06(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150, 0, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150.0, frq_MHz, t);
								
									Em = Em - 30.0 + ERPall[ASi];
									Esum0 = Esum0 + pow(10.0 , Em/10.0);
								}
								Esum1 = max(Esum1 , 10.0*log10(Esum0));
							}
							EsumALLOT = Esum1;
							Esum = max(EsumASS,EsumALLOT);

							if(fabs(Esum-FStrig)<0.1)
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
							}
							else if(Esum>=FStrig)
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km1 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
							}
							else
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km2 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									d_km = d_km - 5.0;
									if(d_km<=0)
									{
										latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
										break;
									}
								}
							}

						}//while
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

					}//for az
					delete [] GeoLatI; 	delete [] GeoLonI; delete [] FrequencyI; delete [] Hasgl_STI;
					delete [] ERPI; delete [] h1_15; delete [] lat_TP; delete [] lon_TP;

					float RLON   = (float)((pi/180.0)*GRlon), RLAT   = (float)((pi/180.0)*GRlat);
					CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
			//		CString adm1("");	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
					CString adm1 = Cty2AdmGE06(&cty1);
			
					long Ncty;
					CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty); 

					CString strX , RLONbs,RLATbs;
					Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
					if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
					else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
					CString strOUT;
					long cd = QGE06_BCBT_A2_1( SfnID, IDst,&strOUT,1) ;
					if(cd>0)
						strX = strX +","+ strOUT;

					CGE06repDLG1 dlgList;
					dlgList.m_dataX = strX;
					dlgList.m_dataY = strY;
					dlgList.m_rowsY = Ncty + 1;
					dlgList.m_rowsX = cd + 2;
					dlgList.m_GoogleFlag = m_GoogleFlag;
					if(dlgList.DoModal()==IDOK)
					{
						CString FileName;
						AdmRefID.Replace('/','_');
						FileName.Format("%sReports\\%s_%s_BCBT.txt",m_AppPath,adm1,AdmRefID);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
						fclose(fpOUT);
						OnDrawVector(FileName);
						if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
					}
				}//Pdlg
			}/////////A4_2
			else if((NET==_T("ASS5"))||(NET==_T("AST5")))	/////////A5_1
			{
				CLoSDLG Pdlg;
				Pdlg.m_kfactor = 4.0/3.0; Pdlg.m_RxH = 1000.0; Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
				Pdlg.m_title  = _Z("Model Parameters"); Pdlg.m_title1 = _Z("Search Radius(km)");
				if(Pdlg.DoModal()==IDOK)
				{
					int AZstep = Pdlg.m_step;
					double GRlat , GRlon , frq_MHz;
					GRlat = atof(GeoLat);		GRlon = atof(GeoLon);
					frq_MHz = atof(Frequency);
			
					double FStrig = CP154606.GE06_FStrig(STN,frq_MHz);
					////////////////////////////////////
					int az0[37];
					for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
					double attH0[37], attV0[37];
					if(AntDir==_T("D"))
						GE84pattern(atol(AntCatID),attH0,attV0,Pol);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;		attV0[i] = 0;
						}
					attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
					double attH0[361], attV0[361];
					GE06patternT(atol(AntCatID), AntDir, Pol,attH0,attV0); 

					double latContour_deg[360],lonContour_deg[360];
					double ERP,attnH,attnV,RAZIM, h1 , h10[37], latC_deg,lonC_deg;
					double t = 1, h2 = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double Sradius_km = Pdlg.m_RxH;

					OnDatabaseStationsindesktop2(GRlat,GRlon);
					double Hasl_ST = LatLon2Hg(GRlat,GRlon);
					double Hasgl_ST = Hasl_ST + atof(Hagl_ST);
					double azz, h1_15[360] , lat3km  , lon3km , lat15km , lon15km;
					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					if(datadlg.m_Heff1)
					{
						for(long i=0;i<(360/AZstep);i++)
						{
							azz = (double)(i*AZstep);
							reckon( GRlat,GRlon,  3.0 , azz , &lat3km  , &lon3km) ;
							reckon( GRlat,GRlon, 15.0 , azz , &lat15km , &lon15km) ;
							h1_15[i] = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}
					}

					double d_km , d_km1 , d_km2 , Em;
					progress_num=0;
					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
					for(int az = 0; az<(360/AZstep) ; az++)
					{
						RAZIM = (double)(az*AZstep);
				//		attnH = Interp2(az0,attH0,RAZIM,37);	attnV = Interp2(az0,attV0,RAZIM,37);
						attnH = attH0[az*AZstep];	attnV = attV0[az*AZstep];

						if     (Pol==_T("H"))					ERP = atof(ERP_h_dbw)-attnH;
						else if(Pol==_T("V"))					ERP = atof(ERP_v_dbw)-attnV;
						else if((Pol==_T("M"))||(Pol==_T("U")))	ERP = 10.0*log10(pow(10.0,(atof(ERP_h_dbw)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbw)-attnV)/10.0));
							
						if(!(datadlg.m_Heff1))
						{
							GE84Heff(atol(AntID),atof(MaxEffHght),h10) ;
							h10[36] = h10[0];
							h1 = Interp2(az0,h10,RAZIM,37) ;
						}
						d_km1 = 0;		d_km2 = Sradius_km;
						d_km = (d_km1 + d_km2)/2.0;
						Em = -999.0;

						while(1)
						{
							reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
							/////////////////////////// h1 //////////////////////
							if(datadlg.m_Heff1)
							{
								if (d_km>=15.0)		h1 = h1_15[az];
								else
								{
									reckon( GRlat,GRlon, 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
									reckon( GRlat,GRlon,     d_km , RAZIM , &lat15km , &lon15km) ;
									h1 = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
								}
							}
							Em = E_P1546_06(GRlat,GRlon,latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
							Em = Em - 30.0 + ERP;

							if(fabs(Em-FStrig)<0.1)
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
							}
							else if(Em>=FStrig)
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km1 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
							}
							else
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km2 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									d_km = d_km - 5.0;
									if(d_km<=0)
									{
										latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
										break;
									}
								}
							}

						}//while
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

					}//for

					long Ncty;
					CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty); 

					CString strX , RLONbs,RLATbs;
					Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
					if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
					else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);

					CString strOUT = QGE06_BCBT_A5_1(AssocAllotID) ;
					strX = strX +","+ strOUT;

					CGE06repDLG1 dlgList;
					dlgList.m_dataX = strX;
					dlgList.m_dataY = strY;
					dlgList.m_rowsY = Ncty+1;
					dlgList.m_rowsX = 3;
					dlgList.m_GoogleFlag = m_GoogleFlag;
					if(dlgList.DoModal()==IDOK)
					{
						CString FileName;
						AdmRefID.Replace('/','_');
						FileName.Format("%sReports\\%s_%s_BCBT.txt",m_AppPath,adm1,AdmRefID);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
						fclose(fpOUT);
						OnDrawVector(FileName);
						if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
					}
				}//Pdlg
			}/////////A5_1
			else if((NET==_T("ALS5"))||(NET==_T("ALT5")))	/////////A5_2
			{
				CLoSDLG Pdlg;
				Pdlg.m_kfactor = 4.0/3.0; Pdlg.m_RxH = 1000.0; Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
				Pdlg.m_title  = _Z("Model Parameters"); Pdlg.m_title1 = _Z("Search Radius(km)");
				if(Pdlg.DoModal()==IDOK)
				{
					int AZstep = Pdlg.m_step;
					CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN, ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN;

					long c = QGE06_BCBT_A5( AdmRefID,&GeoLatN,&GeoLonN,	&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
								&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN , &AntDirN) ;

					double GRlat , GRlon , frq_MHz;
					GRlat = atof(GeoLatN);		GRlon = atof(GeoLonN);
					frq_MHz = atof(FrequencyN);

					double FStrig = CP154606.GE06_FStrig(STN,frq_MHz);

					////////////////////////////////////
					int az0[37];
					for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
					double attH0[37], attV0[37];
					if(AntDirN==_T("D"))
						GE84pattern(atol(AntCatIDN),attH0,attV0,PolN);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;	attV0[i] = 0;
						}
					attH0[36] = attH0[0];	attV0[36] = attV0[0];
*/
					double attH0[361], attV0[361];
					GE06patternT(atol(AntCatIDN), AntDirN, PolN,attH0,attV0); 

					double latC_deg,lonC_deg;
					double latContour_deg[360],lonContour_deg[360];
					double ERP,attnH,attnV,RAZIM , h1 , h10[37];
					double t = 1, h2 = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double Sradius_km = Pdlg.m_RxH;

					OnDatabaseStationsindesktop2(GRlat,GRlon);
					double Hasl_ST = LatLon2Hg(GRlat,GRlon);
					double Hasgl_ST = Hasl_ST + atof(AntHeightAGLN);

					double azz, h1_15[360] , lat3km  , lon3km , lat15km , lon15km;
					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					if(datadlg.m_Heff1)
					{
						for(long i=0;i<(360/AZstep);i++)
						{
							azz = (double)(i*AZstep);
							reckon( GRlat,GRlon,  3.0 , azz , &lat3km  , &lon3km) ;
							reckon( GRlat,GRlon, 15.0 , azz , &lat15km , &lon15km) ;
							h1_15[i] = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}
					}
					double d_km , d_km1 , d_km2 , Em;
					progress_num=0;
					LoadMap_IDWMpr(4,GRlat,GRlon , 1500.0); 

					for(int az = 0; az<(360/AZstep) ; az++)
					{
						RAZIM = (double)(az*AZstep);
				//		attnH = Interp2(az0,attH0,RAZIM,37) ;		attnV = Interp2(az0,attV0,RAZIM,37) ;
						attnH = attH0[az*AZstep];	attnV = attV0[az*AZstep];

						if     (PolN==_T("H"))						ERP = atof(ERP_h_dbwN)-attnH;
						else if(PolN==_T("V"))						ERP = atof(ERP_v_dbwN)-attnV;
						else if((PolN==_T("M"))||(PolN==_T("U")))	ERP = 10.0*log10(pow(10.0,(atof(ERP_h_dbwN)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbwN)-attnV)/10.0));
						if(!(datadlg.m_Heff1))
						{
							GE84Heff(atol(AntIDN),atof(MaxEffHghtN),h10) ;
							h10[36] = h10[0];
							h1 = Interp2(az0,h10,RAZIM,37) ;
						}
						d_km1 = 0;		d_km2 = Sradius_km;
						d_km = (d_km1 + d_km2)/2.0;
						Em = -999.0;

						while(1)
						{
							reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
							/////////////////////////// h1 //////////////////////
							if(datadlg.m_Heff1)
							{
								if (d_km>=15.0)		h1 = h1_15[az];
								else
								{
									reckon( GRlat,GRlon, 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
									reckon( GRlat,GRlon,     d_km , RAZIM , &lat15km , &lon15km) ;
									h1 = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
								}
							}
							Em = E_P1546_06(GRlat,GRlon,latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
							Em = Em - 30.0 + ERP;

							if(fabs(Em-FStrig)<0.1)
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
							}
							else if(Em>=FStrig)
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km1 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
							}
							else
							{
								if(d_km1 < (d_km2-10.0))
								{
									d_km2 = d_km;
									d_km = (d_km1 + d_km2)/2.0;
								}
								else
								{
									d_km = d_km - 5.0;
									if(d_km<=0)
									{
										latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
										break;
									}
								}
							}

						}//while
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					}//for

//					double pi = 4.0*atan(1.0);
					float RLON   = (float)((pi/180.0)*GRlon), RLAT   = (float)((pi/180.0)*GRlat);
					CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
			//		CString adm1("");	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
					CString adm1 = Cty2AdmGE06(&cty1);

					long Ncty;
					CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty); 
					CString strX , RLONbs,RLATbs;
					Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
					if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
					else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
					CString strOUT = QGE06_BCBT_A5_2(AdmRefID) ;
					strX = strX +","+ strOUT;

					CGE06repDLG1 dlgList;
					dlgList.m_dataX = strX;
					dlgList.m_dataY = strY;
					dlgList.m_rowsY = Ncty+1;
					dlgList.m_rowsX = 3;
					dlgList.m_GoogleFlag = m_GoogleFlag;
					if(dlgList.DoModal()==IDOK)
					{
						CString FileName;
						AdmRefID.Replace('/','_');
						FileName.Format("%sReports\\%s_%s_BCBT.txt",m_AppPath,adm1,AdmRefID);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
						fclose(fpOUT);
						OnDrawVector(FileName);
						if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
					}
				}//Pdlg
			}/////////A5_2

		}//Nrow
	}//database
	Set_STtable_Default();
	EndWaitCursor();
}

long CSMS4DCView::QGE06_BCBT_B1_FX_POINT(double latC, double lonC, double Drange,double frq_MHz, double BandWidthBS_MHz,double FrqRange,int OverLapFlag , CString sttp , CString cty1, CString NoticeType, CString Fragment,CString RPRstr) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	double dumy,  lonmin , lonmax , latmin , latmax ,rng_km = Drange , fmin , fmax;
	reckon(latC,lonC, rng_km,  0.0,&latmax,&dumy) ;
	reckon(latC,lonC, rng_km,180.0,&latmin,&dumy) ;
	reckon(latC,lonC, rng_km, 90.0,&dumy,&lonmax) ;
	reckon(latC,lonC, rng_km,270.0,&dumy,&lonmin) ;
	fmin = frq_MHz - FrqRange;
	fmax = frq_MHz + FrqRange;

	long n = 0;
	double dist ,STlat_deg,STlon_deg , BandW_ter, FStrig[2],hR[2];
	CString SQL1, str = _T("") , strF = _T("") , str0 = _T("") , str1 = _T("") , str2 = _T("");

//	tbl.Format(_T("SELECT * FROM STtableGE06 WHERE (((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((((RXfreq)>=174 And (RXfreq)<=230) Or ((RXfreq)>=470 And (RXfreq)<=862)) And ((RXfreq)>=%lf And (RXfreq)<=%lf)) AND ((STTP)=\'%s\') AND ((Fragment)=\'%s\') AND ((ctry)<>\'%s\'));"), latmin,latmax,lonmin,lonmax,fmin,fmax, sttp,_T("GE06L"),cty1);
	tbl.Format(_T("SELECT * FROM %s WHERE (((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((((RXfreq)>=174 And (RXfreq)<=230) Or ((RXfreq)>=470 And (RXfreq)<=862)) And ((RXfreq)>=%lf And (RXfreq)<=%lf)) AND ((STTP)=\'%s\') AND ((Fragment)=\'%s\') AND ((ctry)<>\'%s\'));"), m_qSTtableGE06,latmin,latmax,lonmin,lonmax,fmin,fmax, sttp,_T("GE06L"),cty1);
	
//	FILE *fp11 = fopen("F:\\map1\\SMS4DC_0\\DB\\test.txt","wt");	//ALAKI1
//	fprintf(fp11,"%s",tbl);
//	fclose(fp11);
	
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;

			rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
			rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
			dist = Distance_km(latC,lonC,STlat_deg,STlon_deg);
			if(dist<=Drange)
			{
				rs.GetFieldValue(_T("RXfreq"),strF);
				rs.GetFieldValue(_T("Emission"),str);		BandW_ter = Emission2NBW(str)/1000.0; 

				CP154606_Functions CP154606;

				double RPR = 0;
				if(Fragment == _T("GE06A"))
				{
					double freq_vcarr = atof(GetFld(RPRstr,1));
					double freq_scarr = atof(GetFld(RPRstr,2));
					CString TV_COLOR = GetFld(RPRstr,3);
					CString TV_SYS = GetFld(RPRstr,4);
					RPR = CP154606.ATV2FXM_RPR(atof(strF),BandW_ter,sttp,freq_vcarr,freq_scarr,TV_COLOR,TV_SYS); 
				}

				if(OverLapFlag==1)
				{
					int OverLap = CP154606.AP3_OVERLAP(frq_MHz, BandWidthBS_MHz, atof(strF), BandW_ter) ;
					if(OverLap==1)
					{
						rs.GetFieldValue(_T("IDst"),str0);
						rs.GetFieldValue(_T("SystemType1"),str1);
						rs.GetFieldValue(_T("SystemType2"),str2);
						
						int nFStrig = CP154606.AP2_FStrigT(sttp, atof(strF), str1, str2, frq_MHz, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR , RPR) ;
						for(int i=0;i<nFStrig;i++)
						{
							SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',%lf,%lf "), str0, FStrig[i], hR[i], strF, sttp, _T("POINT"),STlat_deg,STlon_deg);
							SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp) ") + SQL1;

//::SQLSetConnectOption( DB1.m_hdbc, SQL_NOSCAN, SQL_NOSCAN_ON );
							DB1.ExecuteSQL(SQL1);
//::SQLSetConnectOption( DB1.m_hdbc, SQL_NOSCAN, SQL_NOSCAN_OFF );

							n++;
						}
					}
				}
				else
				{
					rs.GetFieldValue(_T("IDst"),str0);
					rs.GetFieldValue(_T("SystemType1"),str1);
					rs.GetFieldValue(_T("SystemType2"),str2);
					
					int nFStrig = CP154606.AP2_FStrigT(sttp, atof(strF), str1, str2, frq_MHz, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR , RPR) ;
					for(int i=0;i<nFStrig;i++)
					{
						SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',%lf,%lf "), str0, FStrig[i], hR[i], strF, sttp, _T("POINT"),STlat_deg,STlon_deg);
						SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp) ") + SQL1;
						DB1.ExecuteSQL(SQL1);
						n++;
					}
				}
			}
			rs.MoveNext();
		}
	}
	rs.Close();	DB1.Close();
	return n;
}

long CSMS4DCView::QGE06_BCBT_B1_FX_MPOINT(double latC, double lonC, double Drange,double frq_MHz, double BandWidthBS_MHz,double FrqRange,int OverLapFlag , CString sttp , CString recType , CString cty1, CString NoticeType, CString Fragment,CString RPRstr) 
{
	CString  tbl ,m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs,rs1;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	double fmin = frq_MHz - FrqRange;
	double fmax = frq_MHz + FrqRange;

	long n1 = 0;
	double BandW_ter, FStrig[2],hR[2];
	CString SQL1, str = _T("") , strF = _T("") , str1 = _T("") , str2 = _T(""),IDst = _T(""),GeoType = _T("");

//	tbl.Format(_T("SELECT * FROM STtableGE06 WHERE (((((TXfreq)>=174 And (TXfreq)<=230) Or ((TXfreq)>=470 And (TXfreq)<=862)) And ((TXfreq)>=%lf And (TXfreq)<=%lf)) AND ((STTP)=\'%s\') AND ((Fragment)=\'%s\') AND ((ctry)<>\'%s\'));"), fmin,fmax, sttp,_T("GE06L"),cty1);
	tbl.Format(_T("SELECT * FROM %s WHERE (((((TXfreq)>=174 And (TXfreq)<=230) Or ((TXfreq)>=470 And (TXfreq)<=862)) And ((TXfreq)>=%lf And (TXfreq)<=%lf)) AND ((STTP)=\'%s\') AND ((Fragment)=\'%s\') AND ((ctry)<>\'%s\'));"), m_qSTtableGE06, fmin,fmax, sttp,_T("GE06L"),cty1);
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);

			double lat[6],lon[6];
			int n;
			CString zone = _T(""), sttpR = _T(""), latc,lonc,Rc;
			BOOL MpointFlag = FALSE;
			if(sttp==_T("FX"))
			{
				MpointFlag = QGE06_BCBT_Q1(atol(IDst) ,latC, lonC, Drange,lat, lon,&n) ;
				sttpR = sttp;
			}
			else if(sttp==_T("FB"))
			{
				if     (recType==_T("ZONE"))	MpointFlag = QGE06_BCBT_Q2(atol(IDst) ,latC, lonC, Drange, &zone) ;
				else if(recType==_T("CIRCLE"))	MpointFlag = QGE06_BCBT_Q3(atol(IDst) ,latC, lonC, Drange, &latc,&lonc,&Rc) ;
				sttpR = _T("ML");
			}

			if(MpointFlag)
			{
				rs.GetFieldValue(_T("TXfreq"),strF);
				rs.GetFieldValue(_T("Emission"),str);		BandW_ter = Emission2NBW(str)/1000.0; 
				CP154606_Functions CP154606;

				double RPR = 0;
				if(Fragment == _T("GE06A"))
				{
					double freq_vcarr = atof(GetFld(RPRstr,1));
					double freq_scarr = atof(GetFld(RPRstr,2));
					CString TV_COLOR = GetFld(RPRstr,3);
					CString TV_SYS = GetFld(RPRstr,4);
					RPR = CP154606.ATV2FXM_RPR(atof(strF),BandW_ter,sttp,freq_vcarr,freq_scarr,TV_COLOR,TV_SYS); 
				}

				if(OverLapFlag==1)
				{
					int OverLap = CP154606.AP3_OVERLAP(frq_MHz, BandWidthBS_MHz, atof(strF), BandW_ter) ;
					if(OverLap==1)
					{
						rs.GetFieldValue(_T("SystemType1"),str1);
						rs.GetFieldValue(_T("SystemType2"),str2);
						
						int nFStrig = CP154606.AP2_FStrigT(sttpR, atof(strF), str1, str2, frq_MHz, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR, RPR) ;
						for(int i=0;i<nFStrig;i++)
						{
							if(sttp==_T("FX"))
							{
								SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf "), IDst, FStrig[i], hR[i], strF, sttp, recType,n,lat[0],lon[0],lat[1],lon[1],lat[2],lon[2],lat[3],lon[3],lat[4],lon[4],lat[5],lon[5]);
								SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,Npoint,lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4,lat5,lon5,lat6,lon6) ") + SQL1;
							}
							else if(sttp==_T("FB"))
							{
								if     (recType==_T("ZONE"))
								{
									SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',\'%s\' "), IDst, FStrig[i], hR[i], strF, sttp, recType,zone);
									SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,zone) ") + SQL1;
								}
								else if(recType==_T("CIRCLE"))
								{
									SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',%s,%s,%s "), IDst, FStrig[i], hR[i], strF, sttp, recType,latc,lonc,Rc);
									SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp,Rp) ") + SQL1;
								}
							}
							DB1.ExecuteSQL(SQL1);
							n1++;
						}

					}//if OverLap
				}//if OverLapFlag
				else
				{
					rs.GetFieldValue(_T("SystemType1"),str1);
					rs.GetFieldValue(_T("SystemType2"),str2);

					int nFStrig = CP154606.AP2_FStrigT(sttpR, atof(strF), str1, str2, frq_MHz, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR, RPR) ;
					for(int i=0;i<nFStrig;i++)
					{
						if(sttp==_T("FX"))
						{
							SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf "), IDst, FStrig[i], hR[i], strF, sttp, recType,n,lat[0],lon[0],lat[1],lon[1],lat[2],lon[2],lat[3],lon[3],lat[4],lon[4],lat[5],lon[5]);
							SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,Npoint,lat1,lon1,lat2,lon2,lat3,lon3,lat4,lon4,lat5,lon5,lat6,lon6) ") + SQL1;
						}
						else if(sttp==_T("FB"))
						{
							if     (recType==_T("ZONE"))
							{
								SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',\'%s\' "), IDst, FStrig[i], hR[i], strF, sttp, recType,zone);
								SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,zone) ") + SQL1;
							}
							else if(recType==_T("CIRCLE"))
							{
								SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',%s,%s,%s "), IDst, FStrig[i], hR[i], strF, sttp, recType,latc,lonc,Rc);
								SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp,Rp) ") + SQL1;
							}
						}
						DB1.ExecuteSQL(SQL1);
						n1++;
					}

				}//else OverLapFlag
			}//if MpointFlag
			rs.MoveNext();
		}//while
	}//if GetRecordCount
	rs.Close();	DB1.Close();
	return n1;
}

long CSMS4DCView::QGE06_BCBT_B1_ML_SRV(double latC, double lonC, double Drange,double frq_MHz, double BandWidthBS_MHz,double FrqRange,int OverLapFlag , CString cty1, CString NoticeType, CString Fragment,CString RPRstr) 
{
	CString sttp = _T("ML");
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs,rs1;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
	double fmin = frq_MHz - FrqRange;
	double fmax = frq_MHz + FrqRange;

	long n = 0;
	double BandW_ter, FStrig[2],hR[2];;
	CString SQL1, str = _T("") , strF = _T("") , str1 = _T("") , str2 = _T(""),IDst = _T(""),AreaOfTrans = _T("");
	
//	tbl.Format(_T("SELECT * FROM STtableGE06 WHERE (((((RXfreq)>=174 And (RXfreq)<=230) Or ((RXfreq)>=470 And (RXfreq)<=862)) And ((RXfreq)>=%lf And (RXfreq)<=%lf)) AND ((STTP)=\'%s\') AND ((Fragment)=\'%s\') AND ((ctry)<>\'%s\'));"), fmin,fmax, sttp,_T("GE06L"),cty1);
	tbl.Format(_T("SELECT * FROM %s WHERE (((((RXfreq)>=174 And (RXfreq)<=230) Or ((RXfreq)>=470 And (RXfreq)<=862)) And ((RXfreq)>=%lf And (RXfreq)<=%lf)) AND ((STTP)=\'%s\') AND ((Fragment)=\'%s\') AND ((ctry)<>\'%s\'));"), m_qSTtableGE06,fmin,fmax, sttp,_T("GE06L"),cty1);
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("AreaOfTrans"),AreaOfTrans);

			if(AreaOfTrans.GetLength()>0)
			{
				rs.GetFieldValue(_T("RXfreq"),strF);
				rs.GetFieldValue(_T("Emission"),str);		BandW_ter = Emission2NBW(str)/1000.0; 
				CP154606_Functions CP154606;
				double RPR = 0;
				if(Fragment == _T("GE06A"))
				{
					double freq_vcarr = atof(GetFld(RPRstr,1));
					double freq_scarr = atof(GetFld(RPRstr,2));
					CString TV_COLOR = GetFld(RPRstr,3);
					CString TV_SYS = GetFld(RPRstr,4);
					RPR = CP154606.ATV2FXM_RPR(atof(strF),BandW_ter,sttp,freq_vcarr,freq_scarr,TV_COLOR,TV_SYS); 
				}

				if(OverLapFlag==1)
				{
					int OverLap = CP154606.AP3_OVERLAP(frq_MHz, BandWidthBS_MHz, atof(strF), BandW_ter) ;
					if(OverLap==1)
					{
						rs.GetFieldValue(_T("SystemType1"),str1);
						rs.GetFieldValue(_T("SystemType2"),str2);
					
						int nFStrig = CP154606.AP2_FStrigT(sttp, atof(strF), str1, str2, frq_MHz, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
						for(int i=0;i<nFStrig;i++)
						{
							SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',\'%s\' "), IDst, FStrig[i], hR[i], strF, sttp, _T("ZONE"),AreaOfTrans);
							SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType, zone ) ") + SQL1;
							DB1.ExecuteSQL(SQL1);
							n++;
						}

					}//if OverLap
				}//if OverLapFlag
				else
				{
					rs.GetFieldValue(_T("SystemType1"),str1);
					rs.GetFieldValue(_T("SystemType2"),str2);
					
					int nFStrig = CP154606.AP2_FStrigT(sttp, atof(strF), str1, str2, frq_MHz, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
					for(int i=0;i<nFStrig;i++)
					{
						SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',\'%s\' "), IDst, FStrig[i], hR[i], strF, sttp, _T("ZONE"),AreaOfTrans);
						SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,zone ) ") + SQL1;
						DB1.ExecuteSQL(SQL1);
						n++;
					}
				}//else OverLapFlag
			}//if AreaOfTrans
			else
			{
				CString latc,lonc,Rc;
				BOOL MpointFlag	= QGE06_BCBT_Q4(atol(IDst) ,latC, lonC, Drange, &latc,&lonc,&Rc) ;
				if(MpointFlag)
				{
					rs.GetFieldValue(_T("RXfreq"),strF);
					rs.GetFieldValue(_T("Emission"),str);		BandW_ter = Emission2NBW(str)/1000.0; 
					CP154606_Functions CP154606;

					double RPR = 0;
					if(Fragment == _T("GE06A"))
					{
						double freq_vcarr = atof(GetFld(RPRstr,1));
						double freq_scarr = atof(GetFld(RPRstr,2));
						CString TV_COLOR = GetFld(RPRstr,3);
						CString TV_SYS = GetFld(RPRstr,4);
						RPR = CP154606.ATV2FXM_RPR(atof(strF),BandW_ter,sttp,freq_vcarr,freq_scarr,TV_COLOR,TV_SYS); 
					}

					if(OverLapFlag==1)
					{
						int OverLap = CP154606.AP3_OVERLAP(frq_MHz, BandWidthBS_MHz, atof(strF), BandW_ter) ;
						if(OverLap==1)
						{
							rs.GetFieldValue(_T("SystemType1"),str1);
							rs.GetFieldValue(_T("SystemType2"),str2);
						
							int nFStrig = CP154606.AP2_FStrigT(sttp, atof(strF), str1, str2, frq_MHz, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR, RPR) ;
							for(int i=0;i<nFStrig;i++)
							{
								SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',%s,%s,%s "), IDst, FStrig[i], hR[i], strF, sttp, _T("CIRCLE") , latc,lonc,Rc);
								SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType, latp,lonp,Rp) ") + SQL1;
								DB1.ExecuteSQL(SQL1);
								n++;
							}

						}//if OverLap
					}//if OverLapFlag
					else
					{
						rs.GetFieldValue(_T("SystemType1"),str1);
						rs.GetFieldValue(_T("SystemType2"),str2);
						
						int nFStrig = CP154606.AP2_FStrigT(sttp, atof(strF), str1, str2, frq_MHz, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
						for(int i=0;i<nFStrig;i++)
						{
							SQL1.Format(_T("SELECT %s,%0.4lf,%0.4lf,%s,\'%s\',\'%s\',%s,%s,%s "), IDst, FStrig[i], hR[i], strF, sttp, _T("CIRCLE") , latc,lonc,Rc);
							SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType, latp,lonp,Rp) ") + SQL1;
							DB1.ExecuteSQL(SQL1);
							n++;
						}
					}//else OverLapFlag
				}//if MpointFlag
			}//  else AreaOfTrans

			rs.MoveNext();
		}//while
	}//if GetRecordCount
	rs.Close();	DB1.Close();
	return n;
}

long CSMS4DCView::QGE06_BCBT_B1(double latC, double lonC, double Drange,double frq_MHz, double BandWidthBS_MHz,double FrqRange,int OverLapFlag , CString cty1, CString NoticeType, CString Fragment,CString RPRstr) 
{
	CString  SQL1 , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
//	SQL1 = _T("DELETE IDst, FStrig, hR,Freq_ter, STTP, GeoType FROM FStrig_hR;");	//950909
	SQL1 = _T("DELETE FROM FStrig_hR;");											//950909
	DB1.ExecuteSQL(SQL1);
	DB1.Close();

	long n1 = QGE06_BCBT_B1_FX_POINT (latC,lonC,Drange,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,_T("FX"),cty1, NoticeType, Fragment,RPRstr) ;
	long n2 = QGE06_BCBT_B1_FX_MPOINT(latC,lonC,Drange,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,_T("FX"),_T("MPOINT"),cty1, NoticeType, Fragment,RPRstr) ;
	long n3 = QGE06_BCBT_B1_FX_POINT (latC,lonC,Drange,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,_T("FB"),cty1, NoticeType, Fragment,RPRstr) ;
	long n4 = QGE06_BCBT_B1_FX_MPOINT(latC,lonC,Drange,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,_T("FB"),_T("ZONE"),cty1, NoticeType, Fragment,RPRstr) ;
	long n5 = QGE06_BCBT_B1_FX_MPOINT(latC,lonC,Drange,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,_T("FB"),_T("CIRCLE"),cty1, NoticeType, Fragment,RPRstr) ;
	long n6 = QGE06_BCBT_B1_ML_SRV(latC,lonC,Drange,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType, Fragment,RPRstr) ;

	return (n1+n2+n3+n4+n5+n6);
}

BOOL CSMS4DCView::QGE06_BCBT_Q2(long IDst ,double latC, double lonC, double Drange,CString *zone) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	int i = 0;
	CString  zone0 = _T("");
//	tbl.Format(_T("SELECT Link.zone FROM Link, Link_TX WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("ZONE"));
	tbl.Format(_T("SELECT Link.zone FROM Link, %s WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX , IDst, _T("ZONE"));
	
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();		
		rs.GetFieldValue(_T("zone"),zone0);
		i++;
	}
	rs.Close();	DB1.Close();

	if(i>0)
	{
		if(zone0.GetLength()==1)		zone0 = zone0 + _T("  ");
		else if(zone0.GetLength()==2)	zone0 = zone0 + _T(" ");
		*zone = zone0;

		double lat0[360],lon0[360];
		for(long i=0;i<360;i++)	reckon(latC,lonC, Drange , i , &lat0[i] , &lon0[i]) ;

		long n1 = Ctry2Point(zone0); 
		double *lat;  lat = new double[n1];
		double *lon;  lon = new double[n1];
		float *CRDARR0;	CRDARR0 = new float[2*n1];

		unsigned char CTYVEK[4]={""}, BCILR;
		strcpy((char *)CTYVEK,zone0);
		long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;
		float RLONLL, RLATLL, RLONUR, RLATUR , DENS=0;
		GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
		GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	

		long j = 0;
		while(!NOMORE)
		{
			GEOLIW( &ITYPE, CRDARR0, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
			if(NOMORE)	break;
			for(long p=0;p<NRCRD;p++)
			{
				lat[j] = CRDARR0[2*p+1];			//ITYPE=2  Deg.
				lon[j] = CRDARR0[2*p];
				j++;

			}//end for
		}//end while
		delete [] CRDARR0;

		BOOL uflag = InterSection(lat,lon,n1,lat0,lon0,360) ;
		delete [] lat;	delete [] lon;
		return uflag;
	}//if i>0
	return FALSE;
}

long CSMS4DCView::Ctry2Point(CString ctry) 
{
	long n = 0;
	unsigned char CTYVEK[4]={""}, BCILR;
	strcpy((char *)CTYVEK,ctry);
	float CRDARR0[2*15000], DENS=0;
	long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=1, MAXCRD=30000;
	float RLONLL, RLATLL, RLONUR, RLATUR;
	GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
	GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	
	while(!NOMORE)
	{
		GEOLIW( &ITYPE, (float *)CRDARR0, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
		if(NOMORE)	break;
		n = n + NRCRD;
	}//end while
	return n;
}

BOOL CSMS4DCView::QGE06_BCBT_Q3(long IDst , double latC, double lonC, double Drange,CString *latci,CString *lonci,CString *Rci) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	double RecLat , RecLon , Radius;
	int i = 0;
	CString  str = _T("");
//	tbl.Format(_T("SELECT Link.RecLat, Link.RecLon, Link.Radius FROM Link, Link_TX WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("CIRCLE"));
	tbl.Format(_T("SELECT Link.RecLat, Link.RecLon, Link.Radius FROM Link, %s WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX,IDst, _T("CIRCLE"));
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		rs.GetFieldValue(_T("RecLat"),str);		RecLat = atof(str);		*latci = str;
		rs.GetFieldValue(_T("RecLon"),str);		RecLon = atof(str);		*lonci = str;
		rs.GetFieldValue(_T("Radius"),str);		Radius = atof(str);		*Rci = str;
		i++;
	}
	rs.Close();	DB1.Close();
	if(i>0)
	{
		double dist = Distance_km(latC,lonC,RecLat,RecLon);
		if(dist<=(Drange+Radius))		return TRUE;
	}
	return FALSE;
}

BOOL CSMS4DCView::QGE06_BCBT_Q4(long IDst , double latC, double lonC, double Drange,CString *latci,CString *lonci,CString *Rci) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;
	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	double STlat_deg , STlon_deg , radius;
	int i = 0;
	CString  str = _T("");
//	tbl.Format(_T("SELECT IDst, STlat_deg, STlon_deg, radius FROM STtableGE06 WHERE (((IDst)=%ld));"), IDst);
	tbl.Format(_T("SELECT IDst, STlat_deg, STlon_deg, radius FROM %s WHERE (((IDst)=%ld));"), m_qSTtableGE06,IDst);
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);		*latci = str;
		rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);		*lonci = str;
		rs.GetFieldValue(_T("radius"),str);			radius = atof(str);			*Rci = str;
		i++;
	}
	rs.Close();	DB1.Close();
	if(i>0)
	{
		double dist = Distance_km(latC,lonC,STlat_deg,STlon_deg);
		if(dist<=(Drange+radius))
			return TRUE;
	}
	return FALSE;
}

BOOL CSMS4DCView::QGE06_BCBT_Q0(double latC, double lonC, double Drange, double lat[],double lon[],int N_Mpoint) 
{
	double lat0[360],lon0[360];
	for(long i=0;i<360;i++)	reckon(latC,lonC, Drange , i , &lat0[i] , &lon0[i]) ;

	BOOL uflag = InterSection(lat0,lon0,360,lat,lon,N_Mpoint) ;
	return uflag;
}

BOOL CSMS4DCView::QGE06_BCBT_Q1(long IDst ,double latC, double lonC, double Drange, double lat[], double lon[],int *n0) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	int n = 0;
	CString  strlat = _T("") , strlon = _T("");

	lat[0]=lat[1]=lat[2]=lat[3]=lat[4]=lat[5]=-999;
	lon[0]=lon[1]=lon[2]=lon[3]=lon[4]=lon[5]=-999;

//	tbl.Format(_T("SELECT Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, Link_TX WHERE (((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.TXID)=%ld) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("MULTIPOINT"));
	tbl.Format(_T("SELECT Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, %s WHERE (((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.TXID)=%ld) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX,IDst, _T("MULTIPOINT"));
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
					
		rs.GetFieldValue(_T("lat1"),strlat);	rs.GetFieldValue(_T("lon1"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat2"),strlat);	rs.GetFieldValue(_T("lon2"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat3"),strlat);	rs.GetFieldValue(_T("lon3"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat4"),strlat);	rs.GetFieldValue(_T("lon4"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat5"),strlat);	rs.GetFieldValue(_T("lon5"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat6"),strlat);	rs.GetFieldValue(_T("lon6"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
	}
	rs.Close();	DB1.Close();
	*n0 = n;
	if(n>0)
	{
		BOOL MpointFlag = QGE06_BCBT_Q0(latC, lonC, Drange, lat,lon, n);
		return MpointFlag;
	}
	return FALSE;
}

long CSMS4DCView::QGE06_BCBT_Q5(double FStrig, double hR, double latContour_deg[] ,double lonContour_deg[], int nContour ,CString *outStr) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	long n = 0;
	CString  IDst = _T("") , GeoType = _T("") , sttp = _T("") , str = _T("") , Freq_ter;
	CString IDstr = _T(""),GeoTypeStr = _T("") , sttpStr = _T(""), FreqterStr = _T("");

	tbl.Format(_T("SELECT * FROM FStrig_hR WHERE (((FStrig)=%lf) AND ((hR)=%lf));"), FStrig, hR);
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("STTP"),sttp);
			rs.GetFieldValue(_T("GeoType"),GeoType);
			rs.GetFieldValue(_T("Freq_ter"),Freq_ter);

			if(  ((sttp==_T("FX"))||(sttp==_T("FB"))) &&(GeoType==_T("POINT")) )
			{
				double lat[1],lon[1];
				rs.GetFieldValue(_T("latp"),str);		lat[0] = atof(str);
				rs.GetFieldValue(_T("lonp"),str);		lon[0] = atof(str);

				BOOL uflag = InterSection(lat,lon,1,latContour_deg,lonContour_deg,nContour) ;
				if(uflag)
				{
					IDstr = IDstr + _T(",") + IDst;
					GeoTypeStr = GeoTypeStr + _T(",") + GeoType;
					FreqterStr = FreqterStr + _T(",") + Freq_ter;
					sttpStr = sttpStr + _T(",") + sttp;
					n++;
				}
			}
			else if(  (sttp==_T("FX"))   &&(GeoType==_T("MPOINT")) )
			{
				double lat[7],lon[7];
				int Npoint;
				CString str0lat,str0lon;
				rs.GetFieldValue(_T("Npoint"),str);		Npoint = atoi(str);

				for(int i=0;i<Npoint;i++)
				{
					str0lat.Format("lat%d",i+1);
					str0lon.Format("lon%d",i+1);
					rs.GetFieldValue(str0lat,str);		lat[i] = atof(str) ;
					rs.GetFieldValue(str0lon,str);		lon[i] = atof(str) ;
				}
				lat[Npoint] = lat[0];	lon[Npoint] = lon[0];

				BOOL uflag = InterSection(lat,lon,Npoint,latContour_deg,lonContour_deg,nContour) ;
				if(uflag)
				{
					IDstr = IDstr + _T(",") + IDst;
					GeoTypeStr = GeoTypeStr + _T(",") + GeoType;
					FreqterStr = FreqterStr + _T(",") + Freq_ter;
					sttpStr = sttpStr + _T(",") + sttp;
					n++;
				}
			}
			else if(  (sttp==_T("FB"))   &&(GeoType==_T("CIRCLE")) )
			{
				double lat[360],lon[360];
				double latC,lonC, R;
				rs.GetFieldValue(_T("latp"),str);		latC = atof(str);
				rs.GetFieldValue(_T("lonp"),str);		lonC = atof(str);
				rs.GetFieldValue(_T("Rp"),str);			R = atof(str);

				for(long i=0;i<360;i++)	reckon(latC,lonC, R , i , &lat[i] , &lon[i]) ;

				BOOL uflag = InterSection(lat,lon,360,latContour_deg,lonContour_deg,nContour) ;
				if(uflag)
				{
					IDstr = IDstr + _T(",") + IDst;
					GeoTypeStr = GeoTypeStr + _T(",") + GeoType;
					FreqterStr = FreqterStr + _T(",") + Freq_ter;
					sttpStr = sttpStr + _T(",") + sttp;
					n++;
				}
			}
			else if(((sttp==_T("FB"))&&(GeoType==_T("ZONE")))||((sttp==_T("ML"))&&(GeoType==_T("ZONE"))))
			{
				rs.GetFieldValue(_T("zone"),str);
				if(str.GetLength()==1)			str = str + _T("  ");
				else if(str.GetLength()==2)		str = str + _T(" ");

				long n1 = Ctry2Point(str); 
				double *lat;  lat = new double[n1];
				double *lon;  lon = new double[n1];
				float *CRDARR0;		CRDARR0 = new float[2*n1];

				unsigned char CTYVEK[4]={""}, BCILR;
				strcpy((char *)CTYVEK,str);
				long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;
				float RLONLL, RLATLL, RLONUR, RLATUR , DENS=0;
				GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
				GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	

				long j = 0;
				while(!NOMORE)
				{
					GEOLIW( &ITYPE, CRDARR0, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
					if(NOMORE)	break;
					for(long p=0;p<NRCRD;p++)
					{
						lat[j] = CRDARR0[2*p+1];		//ITYPE=2  Deg.
						lon[j] = CRDARR0[2*p];
						j++;

					}//end for
				}//end while
				delete [] CRDARR0;

				BOOL uflag = InterSection(lat,lon,n1,latContour_deg,lonContour_deg,nContour) ;
				if(uflag)
				{
					IDstr = IDstr + _T(",") + IDst;
					GeoTypeStr = GeoTypeStr + _T(",") + GeoType;
					FreqterStr = FreqterStr + _T(",") + Freq_ter;
					sttpStr = sttpStr + _T(",") + sttp;
					n++;
				}
				delete [] lat;		delete [] lon;
			}
			else if( (sttp==_T("ML"))&&(GeoType==_T("CIRCLE")) )
			{
				double lat[360],lon[360] , latC,lonC, R;
				rs.GetFieldValue(_T("latp"),str);		latC = atof(str);
				rs.GetFieldValue(_T("lonp"),str);		lonC = atof(str);
				rs.GetFieldValue(_T("Rp"),str);			R = atof(str);

				for(long i=0;i<360;i++)	reckon(latC,lonC, R , i , &lat[i] , &lon[i]) ;

				BOOL uflag = InterSection(lat,lon,360,latContour_deg,lonContour_deg,nContour) ;
				if(uflag)
				{
					IDstr = IDstr + _T(",") + IDst;
					GeoTypeStr = GeoTypeStr + _T(",") + GeoType;
					FreqterStr = FreqterStr + _T(",") + Freq_ter;
					sttpStr = sttpStr + _T(",") + sttp;
					n++;
				}
			}
			rs.MoveNext();
		}
	}
	rs.Close();	DB1.Close();
	IDstr.Delete(0);	GeoTypeStr.Delete(0);	FreqterStr.Delete(0);	sttpStr.Delete(0);

	CString strY;
	for(long i=0;i<n;i++)
	{
		long ID = atol(GetFld(IDstr,i+1));
		double fter = atof(GetFld(FreqterStr,i+1));
		CString geo = GetFld(GeoTypeStr,i+1);
		CString sttp1 = GetFld(sttpStr,i+1);
		CString strY1 = QGE06_BCBT_Q6(ID, fter, geo, FStrig,  hR , sttp1); 
		strY = strY + _T(",") + strY1;
	}
	strY.Delete(0);
	*outStr = strY;
	return n;
}

CString CSMS4DCView::QGE06_BCBT_Q6(long IDst,double fter,CString geoType,double FStrig, double hR,CString sttp) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;
	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	int i = 0;
	CString  ctry1 = _T(""),adm1 , str = _T("") , str1 = _T("") , lat = _T("") , lon = _T("");
//	tbl.Format(_T("SELECT STtableGE06.IDst, STtableGE06.STname, STtableGE06.ctry, FStrig_hR.Freq_ter, STtableGE06.STTP, STtableGE06.STlat_deg, STtableGE06.STlon_deg, STtableGE06.SystemType1, STtableGE06.SystemType2, FStrig_hR.FStrig, FStrig_hR.hR FROM STtableGE06, FStrig_hR WHERE (((STtableGE06.IDst)=[FStrig_hR].[IDst]) AND ((STtableGE06.IDst)=%ld) AND ((FStrig_hR.Freq_ter)=%lf) AND ((FStrig_hR.FStrig)=%lf) AND ((FStrig_hR.hR)=%lf) AND ((FStrig_hR.GeoType)=\'%s\') AND ((STtableGE06.STTP)=\'%s\'));"), IDst,fter,FStrig,hR,geoType,sttp);
	tbl.Format(_T("SELECT STtableGE06.IDst, STtableGE06.STname, STtableGE06.ctry, FStrig_hR.Freq_ter, STtableGE06.STTP, STtableGE06.STlat_deg, STtableGE06.STlon_deg, STtableGE06.SystemType1, STtableGE06.SystemType2, FStrig_hR.FStrig, FStrig_hR.hR FROM %s, FStrig_hR WHERE (((STtableGE06.IDst)=[FStrig_hR].[IDst]) AND ((STtableGE06.IDst)=%ld) AND ((FStrig_hR.Freq_ter)=%lf) AND ((FStrig_hR.FStrig)=%lf) AND ((FStrig_hR.hR)=%lf) AND ((FStrig_hR.GeoType)=\'%s\') AND ((STtableGE06.STTP)=\'%s\'));"), m_qSTtableGE06 , IDst,fter,FStrig,hR,geoType,sttp);

	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();	
		
		rs.GetFieldValue(_T("IDst"),str);			str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("STname"),str);			str1 = str1 + _T(",") + str;

		rs.GetFieldValue(_T("ctry"),ctry1);	
//		if(ctry1.GetLength()==1)			ctry1 = ctry1 + _T("  ");
//		else if(ctry1.GetLength()==2)		ctry1 = ctry1 + _T(" ");
//		GEOCTYA((BYTE *)ctry1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
		adm1 = Cty2AdmGE06(&ctry1);
													str = ctry1 + _T(",") + adm1;
													str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("Freq_ter"),str);		str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("STTP"),str);			str1 = str1 + _T(",") + str;

		rs.GetFieldValue(_T("STlat_deg"),lat);		
		rs.GetFieldValue(_T("STlon_deg"),lon);
		CString RLONx,RLATx;
//		double pi = 4.0*atan(1.0);
		Rad2Str(atof(lon)*pi/180.0,atof(lat)*pi/180.0, &RLONx,&RLATx);
		str1 = str1 + _T(",") + RLONx;
		str1 = str1 + _T("  ") + RLATx;

		rs.GetFieldValue(_T("SystemType1"),str);	str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("SystemType2"),str);	str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("FStrig"),str);			str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("hR"),str);				str1 = str1 + _T(",") + str;

		i++;
	}
	rs.Close();	DB1.Close();
	str1.Delete(0);
	return str1;
}

CString CSMS4DCView::QGE06_BCBT_Qx(BOOL *hef_flag) 
{
	CString Selx = _T("");
	CString CDataBaseSTR;
//	CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)=\'RC06\' Or (Fragment)=\'GE06A\' Or (Fragment)=\'GE06D\') AND ((AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)=\'---\' Or (AssignCode) Is Null Or (AssignCode)=''));");
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)=\'RC06\' Or (Fragment)=\'GE06A\' Or (Fragment)=\'GE06D\') AND ((AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)=\'---\' Or (AssignCode) Is Null Or (AssignCode)=''));") , m_qSTtableGE06ASAL);
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = TRUE;
	datadlg.m_Title = _T("Wanted Assignment/Allotment");

	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if(Nrow!=1)
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
		}
		else //if (Nrow==1)
		{
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
			*hef_flag = datadlg.m_Heff1;
		}
	}
	return Selx;
}

BOOL CSMS4DCView::InterSection(double lat1[],double lon1[],long n1,double lat2[],double lon2[],long n2) 
{
//	double pi = 4.0*atan(1.0);
	long i;

	float (*CRDLN1)[2];	CRDLN1 = new float[n1][2];
	for( i=0;i<n1;i++)
	{
		CRDLN1[i][0] = (float)((pi/180.0)*lon1[i]);
		CRDLN1[i][1] = (float)((pi/180.0)*lat1[i]);
	}
	float (*CRDLN2)[2];	CRDLN2 = new float[n2][2];
	for( i=0;i<n2;i++)
	{
		CRDLN2[i][0] = (float)((pi/180.0)*lon2[i]);
		CRDLN2[i][1] = (float)((pi/180.0)*lat2[i]);
	}
	if(n1==1)
	{
		long uflag;
		float POINT1[1][2];
		POINT1[0][0] = CRDLN1[0][0];
		POINT1[0][1] = CRDLN1[0][1];
		uflag = GEOPIA2( (float *)POINT1, (float *)CRDLN2, &n2);
		if(uflag)
		{
			delete [] CRDLN1;		delete [] CRDLN2;
			return TRUE;
		}
	}
	else
	{
		float CROSVEK[1][2];
		long C180=0, IEND=2, MAXCROS=1, CROSS, IREST;
		GEOC2L( (float *)CRDLN1, &n1, (float *)CRDLN2, &n2,	&C180, &IEND, (float *)CROSVEK,  &MAXCROS, &CROSS, &IREST);
		if(CROSS>0)		// Cross 1,2
		{
			delete [] CRDLN1;		delete [] CRDLN2;
			return TRUE;
		}
		for( i=0;i<n1;i++)			// 1   into   2
		{
			float POINT1[1][2];
			POINT1[0][0] = CRDLN1[i][0];
			POINT1[0][1] = CRDLN1[i][1];
			long uflag = GEOPIA2( (float *)POINT1, (float *)CRDLN2, &n2);
			if(uflag)
			{
				delete [] CRDLN1;	delete [] CRDLN2;
				return TRUE;
			}
		}
		for( i=0;i<n2;i++)			// 2   into   1
		{
			float POINT2[1][2];
			POINT2[0][0] = CRDLN2[i][0];
			POINT2[0][1] = CRDLN2[i][1];
			long uflag = GEOPIA2( (float *)POINT2, (float *)CRDLN1, &n1);
			if(uflag)
			{
				delete [] CRDLN1;	delete [] CRDLN2;
				return TRUE;
			}
		}
	}
	delete [] CRDLN1;	delete [] CRDLN2;
	return FALSE;
}

BOOL CSMS4DCView::QGE06_BCBT_Qy(int TxRx) 
{
	BOOL YOK = FALSE;
	CString CDataBaseSTR;
	if(TxRx==0)		CDataBaseSTR = _T("SELECT DISTINCT FStrig, hR FROM FStrig_hR ORDER BY FStrig;");
	else			CDataBaseSTR = _T("SELECT DISTINCT FStrig, hR, Freq_ter, latp, lonp, GeoType,ant FROM FStrig_hR ORDER BY FStrig;");

	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;

	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = FALSE;
	datadlg.m_Title = _Z("Select Found Trigger Field Strength(s) :");

	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow>=1)	YOK = TRUE;
	}
	Set_STtable_Default();
	return YOK;
}

void CSMS4DCView::OnDatabaseGeotype() 
{
	CString CDataBaseSTR;

///	CString str1 , str2;
///	str1.Format(_T("        SELECT STtableGE06.IDst, STtableGE06.STname, STtableGE06.STlat_deg, STtableGE06.STlon_deg, Link.GeoType, Link.RecLat, Link.RecLon, Link.Radius, Link.zone, Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, STtableGE06 WHERE (((STtableGE06.IDst)=Link.TXID) And ((Link.GeoType)=\'%s\' Or (Link.GeoType)=\'%s\' Or (Link.GeoType)=\'%s\'));"),_T("MULTIPOINT"),_T("ZONE"),_T("CIRCLE"));
///	str2.Format(_T("  UNION ALL SELECT STtableGE06.IDst, STtableGE06.STname, STtableGE06.STlat_deg, STtableGE06.STlon_deg, 'CIRCLE' AS GeoType, STtableGE06.STlat_deg AS RecLat, STtableGE06.STlon_deg AS RecLon, STtableGE06.radius AS Radius, 'CIRCLE' AS [zone], '' AS lat1, '' AS lon1, '' AS lat2, '' AS lon2, '' AS lat3, '' AS lon3, '' AS lat4, '' AS lon4, '' AS lat5, '' AS lon5, '' AS lat6, '' AS lon6 FROM STtableGE06 WHERE (((STtableGE06.STTP)=\'%s\')) order by STtableGE06.IDst;"),_T("ML"));
///	CDataBaseSTR = str1 + str2;
 
//	CDataBaseSTR.Format(_T("SELECT STtableGE06.IDst, STtableGE06.STname, STtableGE06.STlat_deg, STtableGE06.STlon_deg, Link.GeoType, Link.RecLat, Link.RecLon, Link.Radius, Link.zone, Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, STtableGE06 WHERE (((STtableGE06.IDst)=[Link].[TXID]) AND ((Link.GeoType)='ZONE' Or (Link.GeoType)='MULTIPOINT' Or (Link.GeoType)='CIRCLE')) ORDER BY STtableGE06.IDst;"));
	CDataBaseSTR.Format(_T("SELECT STtableGE06.IDst, STtableGE06.STname, STtableGE06.STlat_deg, STtableGE06.STlon_deg, Link.GeoType, Link.RecLat, Link.RecLon, Link.Radius, Link.zone, Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, %s  WHERE (((STtableGE06.IDst)=[Link].[TXID]) AND ((Link.GeoType)='ZONE' Or (Link.GeoType)='MULTIPOINT' Or (Link.GeoType)='CIRCLE')) ORDER BY STtableGE06.IDst;") , m_qSTtableGE06);

	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG dbdlg;
	int xxDLG = dbdlg.DoModal();
	if (xxDLG == IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow!=1)
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
			return;
		}

		CString Sel	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
		if (Sel!=_T(""))
		{
			double lat1,lon1;
			CString name1;

			long ID1  = atol(GetFld(Sel,1));	name1 = GetFld(Sel,2);
			lat1  = atof(GetFld(Sel,3));		lon1  = atof(GetFld(Sel,4));

			OnDatabaseStationsindesktop2(lat1,lon1);
			AddStation_disp(ID1,lat1,lon1,name1) ;
			CString GeoType = GetFld(Sel,5);

			if(GeoType==_T("CIRCLE"))
			{
				double lat2,lon2 ,latC,lonC,R;
				lat2  = atof(GetFld(Sel,6));	lon2  = atof(GetFld(Sel,7));	R  = atof(GetFld(Sel,8));
			
				CString sFile;
				sFile.Format(_T("%s%s%d.tmp") , ((CSMS4DCApp *)AfxGetApp())->m_AppPath , _T("Temp\\tempM") , m_POLYnum);
				FILE *fptemp=fopen(sFile,"wt");

				for (int i=0;i<73;i++)
				{
					reckon(lat2,lon2, R , i*5 , &latC , &lonC) ;
					fprintf(fptemp,"%0.14lf  %0.14lf\n",lonC, latC);
				}
				fclose(fptemp);
				OnDrawVector(sFile);
			}
			else if(GeoType==_T("MULTIPOINT"))
			{
				CString latp1  = GetFld(Sel,10) , lonp1  = GetFld(Sel,11);
				CString latp2  = GetFld(Sel,12) , lonp2  = GetFld(Sel,13);
				CString latp3  = GetFld(Sel,14) , lonp3  = GetFld(Sel,15);
				CString latp4  = GetFld(Sel,16) , lonp4  = GetFld(Sel,17);
				CString latp5  = GetFld(Sel,18) , lonp5  = GetFld(Sel,19);
				CString latp6  = GetFld(Sel,20) , lonp6  = GetFld(Sel,21);
				CString sFile;
				sFile.Format(_T("%s%s%d.tmp") , ((CSMS4DCApp *)AfxGetApp())->m_AppPath , _T("Temp\\tempM") , m_POLYnum);

				FILE *fptemp=fopen(sFile,"wt");
				if((latp1.GetLength()>0)&&(lonp1.GetLength()>0))		fprintf(fptemp,"%s  %s\n",lonp1, latp1);
				if((latp2.GetLength()>0)&&(lonp2.GetLength()>0))		fprintf(fptemp,"%s  %s\n",lonp2, latp2);
				if((latp3.GetLength()>0)&&(lonp3.GetLength()>0))		fprintf(fptemp,"%s  %s\n",lonp3, latp3);
				if((latp4.GetLength()>0)&&(lonp4.GetLength()>0))		fprintf(fptemp,"%s  %s\n",lonp4, latp4);
				if((latp5.GetLength()>0)&&(lonp5.GetLength()>0))		fprintf(fptemp,"%s  %s\n",lonp5, latp5);
				if((latp6.GetLength()>0)&&(lonp6.GetLength()>0))		fprintf(fptemp,"%s  %s\n",lonp6, latp6);
				if((latp1.GetLength()>0)&&(lonp1.GetLength()>0))		fprintf(fptemp,"%s  %s\n",lonp1, latp1);
				fclose(fptemp);
				OnDrawVector(sFile);
			}
			else if(GeoType==_T("ZONE"))
			{
				CString zone = GetFld(Sel,9);	CString sFile = VectorCountry(zone) ;
				OnDrawVector(sFile);
			}
			InvalidateRect(NULL,false);
		}
	}
	Set_STtable_Default();
}

void CSMS4DCView::GE06ShowAllot(CString allotkey , CString GeoArea) 
{
	CString sFile;	sFile.Format(_T("%s%s%d.tmp") , ((CSMS4DCApp *)AfxGetApp())->m_AppPath , _T("Temp\\tempM") , m_POLYnum);
	FILE *fptemp = fopen(sFile,"wt");
	if(GeoArea.IsEmpty())
	{
		CString contourkeyN , nb_test_ptsN;
		long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey), &contourkeyN, &nb_test_ptsN);
		for(long i=0;i<contourkeyNum;i++)
		{
			if(i>0)		fprintf(fptemp,"%s\n","NaN  NaN");
			double GRlat , GRlon;	CString lat_tpStr, lon_tpStr;	long contourkey , nb_test_pts , n_tp;
			contourkey  = atol(GetFld(contourkeyN,i+1));
			nb_test_pts = atol(GetFld(nb_test_ptsN,i+1));
			n_tp = QGE06_BCBT_A3_1(contourkey,nb_test_pts,&lat_tpStr,&lon_tpStr,&GRlat, &GRlon);
			if(n_tp>2)
			{
				for(long j=0;j<n_tp;j++)
					fprintf(fptemp,"%0.14lf  %0.14lf\n",atof(GetFld(lon_tpStr,j+1)), atof(GetFld(lat_tpStr,j+1)));
					fprintf(fptemp,"%0.14lf  %0.14lf\n",atof(GetFld(lon_tpStr,1)), atof(GetFld(lat_tpStr,1)));
				OnDatabaseStationsindesktop2(GRlat,GRlon);
			}
			else
			{
				CString str;	str.Format("No. of test points is less than 3.\nThe allotment contour can not be shown.");
				MessageBox(str,"Warning!!!",MB_ICONWARNING);
			}
		}//for  i
	}//if GeoArea.IsEmpty()
	else
	{
		double GRlat , GRlon;		CString lat_tpStr, lon_tpStr;
		long NcontourT = QGE06_BCBT_Aux_Border(GeoArea, &lat_tpStr, &lon_tpStr,&GRlat , &GRlon) ;
		for(long j=0;j<NcontourT;j++)
			fprintf(fptemp,"%0.14lf  %0.14lf\n",atof(GetFld(lon_tpStr,j+1)), atof(GetFld(lat_tpStr,j+1)));
			fprintf(fptemp,"%0.14lf  %0.14lf\n",atof(GetFld(lon_tpStr,1)), atof(GetFld(lat_tpStr,1)));
		OnDatabaseStationsindesktop2(GRlat,GRlon);
	}// ! GeoArea.IsEmpty()
	fclose(fptemp);	
	OnDrawVector(sFile);
	InvalidateRect(NULL,false);
}
void CSMS4DCView::OnDatabaseShowallot() 
{
//	CString CDataBaseSTR = _T("SELECT * FROM CommonFields WHERE (((IDst)='---')) order by allotkey;");
	CString CDataBaseSTR;
	CDataBaseSTR.Format( _T("SELECT * FROM %s WHERE (((IDst)='---')) order by allotkey;") , m_qCommonFields );

	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Title = _T("Select One Allotment");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
		{
			CString Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
			CString GeoArea = GetFld(Selx,14),	allotkey = GetFld(Selx,37);
			GE06ShowAllot(allotkey, GeoArea);
		}//if  Nrow
		else
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
		}
	}//if  datadlg
	Set_STtable_Default();
}

CString CSMS4DCView::QGE06_Allot_Qx() 
{
	CString Selx = _T("");
//	CString CDataBaseSTR = _T("SELECT * FROM CommonFields WHERE (((IDst)=\'---\')) order by allotkey;");
	CString CDataBaseSTR;
	CDataBaseSTR.Format( _T("SELECT * FROM %s WHERE (((IDst)=\'---\')) order by allotkey;") , m_qCommonFields );

	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;

	CDataBaseLDLG datadlg;
	datadlg.m_Title = _T("Select One Allotment");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
		else
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			EndWaitCursor();
		}
	}
	return Selx;
	Set_STtable_Default();
}

void CSMS4DCView::OnDatabaseDefineallot() 
{
	long m_NPoint = m_PolyPointNum;
	if(m_NPoint>2)
	{
		CString Selx = QGE06_Allot_Qx() ;
		if(Selx.GetLength()>0)
		{
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
			CString GeoArea = GetFld(Selx,14);
			long allotkey = atol(GetFld(Selx,37));
			CString adm , ctry = GetFld(Selx,7);
	//		GEOCTYA((BYTE *)ctry.GetBufferSetLength(3), (BYTE *)adm.GetBufferSetLength(3));
			adm = Cty2AdmGE06(&ctry);

			CDatabase DB1;
			CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
			DB1.Open(_T(m_DB),false,false,_T("ODBC;"),false);
			CRecordset rs;
			rs.m_pDatabase=&DB1;
			CString SQL1,Lastcontourkey , Lastcontour_id;

//			rs.Open(CRecordset::snapshot, _T("select max(contourkey)+1 from rrc_sub_area"));
			rs.Open(CRecordset::snapshot, _T("select max(contourkey)+1 from rrc_contour_pt"));
			rs.GetFieldValue((short)0,Lastcontourkey);
			rs.Close();
			if(Lastcontourkey.IsEmpty())
				Lastcontourkey = _T("1");

			SQL1.Format(_T("SELECT %ld,%s "), allotkey, Lastcontourkey);
			SQL1=_T("INSERT INTO rrc_sub_area (allotkey, contourkey) ") + SQL1;
			DB1.ExecuteSQL(SQL1);

			rs.Open(CRecordset::snapshot, _T("select max(contour_id)+1 from rrc_contour"));
			rs.GetFieldValue((short)0,Lastcontour_id);
			rs.Close();
			if(Lastcontour_id.IsEmpty())
				Lastcontour_id = _T("1");

			long nb_test_pts = m_NPoint;
			SQL1.Format(_T("SELECT %s,%s,'%s','%s',%ld "), Lastcontourkey, Lastcontour_id,adm, ctry,nb_test_pts);
			SQL1=_T("INSERT INTO rrc_contour (contourkey, contour_id, adm, ctry, nb_test_pts) ") + SQL1;
			DB1.ExecuteSQL(SQL1);

			CString Lastnb_sub_areas;
			SQL1.Format(_T("select max(nb_sub_areas)+1 from rrc_allotment WHERE (((allotkey)=%ld));"), allotkey);
			rs.Open(CRecordset::snapshot, SQL1);
			rs.GetFieldValue((short)0,Lastnb_sub_areas);
			rs.Close();
			if(Lastnb_sub_areas.IsEmpty())
				Lastnb_sub_areas = _T("1");

			SQL1.Format(_T("UPDATE rrc_allotment SET nb_sub_areas = %s WHERE (((allotkey)=%ld));"), Lastnb_sub_areas,allotkey) ;
			DB1.ExecuteSQL(SQL1);

			CPoint point1;
			double Lat1,Lon1 , long_sec, lat_sec;
			long test_pt;
			int long_deg, long_min , lat_deg, lat_min;
			CString long_ew, lat_ns;

//			double pi = 4.0*atan(1.0);
			float RLAT , RLON;
			CString  RLONbs,RLATbs;

			for(long i=0; i<m_NPoint ;i++)
			{
				test_pt = i;
				point1 = m_PolyPoint[i];
				Point2LatLon(point1,&Lat1,&Lon1) ;
				RLON   = (float)((pi/180.0)*Lon1); RLAT   = (float)((pi/180.0)*Lat1);
				Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);

				long_deg = atol(RLONbs.Left(3)); long_ew = RLONbs.Mid(3,1); long_min = atol(RLONbs.Mid(4,2)); long_sec = atof(RLONbs.Mid(6,2));
				lat_deg = atol(RLATbs.Left(2));  lat_ns = RLATbs.Mid(2,1); 	lat_min = atol(RLATbs.Mid(3,2));  lat_sec = atof(RLATbs.Mid(5,2));

				SQL1.Format(_T("SELECT %s,%ld,%d,%d,%lf,'%s',%d,%d,%lf,'%s' "), Lastcontourkey, test_pt, long_deg, long_min, long_sec, long_ew, lat_deg, lat_min, lat_sec, lat_ns);
				SQL1=_T("INSERT INTO rrc_contour_pt (contourkey, test_pt, long_deg, long_min, long_sec, long_ew, lat_deg, lat_min, lat_sec, lat_ns) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
			}
			DB1.Close();
		}
	}
}
void CSMS4DCView::OnUpdateDatabaseDefineallot(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_PolyPointNum>2);	
}

void CSMS4DCView::OnCoordinationGe06Bcbt2fxlm() 
{
	BeginWaitCursor();
	BOOL hef_flag;
	CString Sel_I = QGE06_BCBT_Qx(&hef_flag) ;
	if(Sel_I.GetLength()>0)
	{
		BeginWaitCursor();
		CString IDst = GetFld(Sel_I,1),				Fragment = GetFld(Sel_I,28),		cty1 = GetFld(Sel_I,25),
				NoticeType = GetFld(Sel_I,35),		PlanEntry = GetFld(Sel_I,50),		SfnID = GetFld(Sel_I,52),
				AssocAllotID = GetFld(Sel_I,59),	AdmRefID = GetFld(Sel_I,33),		GeoLat = GetFld(Sel_I,3),
				GeoLon = GetFld(Sel_I,4),			Frequency = GetFld(Sel_I,6),		Pol = GetFld(Sel_I,13),
				ERP_h_dbw = GetFld(Sel_I,62),		ERP_v_dbw = GetFld(Sel_I,63),		AntDir = GetFld(Sel_I,31),
				AntCatID = GetFld(Sel_I,30),		AntID = GetFld(Sel_I,20),			MaxEffHght = GetFld(Sel_I,32),
				Hagl_ST = GetFld(Sel_I,5),			SiteName = GetFld(Sel_I,2),			AssignCode = GetFld(Sel_I,51),
				GeoArea = GetFld(Sel_I,53),			nb_sub_areas = GetFld(Sel_I,60),	allotkey = GetFld(Sel_I,64),
				RPC = GetFld(Sel_I,37),				TV_SYS  = GetFld(Sel_I,36),			SYS_VAR = GetFld(Sel_I,38),
				RN_I = GetFld(Sel_I,61);

		CString freq_vcarr_I = (GetFld(Sel_I,39)),		freq_scarr_I = (GetFld(Sel_I,41)),
				TV_COLOR_I = GetFld(Sel_I,40),			TV_SYS_I = GetFld(Sel_I,36);
		CString RPRstr;	RPRstr.Format(_T("%s,%s,%s,%s"),freq_vcarr_I , freq_scarr_I , TV_COLOR_I , TV_SYS_I);

//		double pi = 4.0*atan(1.0);
		float RLON   = (float)((pi/180.0)*atof(GeoLon)) ;
		float RLAT   = (float)((pi/180.0)*atof(GeoLat));
//		CString cty1("");		GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;

//		if(cty1.GetLength()==1)			cty1 = cty1 + _T("  ");
//		else if(cty1.GetLength()==2)	cty1 = cty1 + _T(" ");
//		CString adm1;	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
		CString adm1 = Cty2AdmGE06(&cty1);

		CP154606_Functions CP154606;
		CString STN = CP154606.GE06_STN(Fragment,NoticeType);
		int PEC = GE06_PEC(AdmRefID , AssocAllotID , PlanEntry , SfnID , STN) ;

		double frq_MHz = atof(Frequency);
		double BandWidthBS_MHz = CP154606.AP3_BandW_BS(STN, TV_SYS, RPC, SYS_VAR, frq_MHz) ;
		CString NET;	NET.Format("%s%d",STN,PEC);

		if((NET==_T("ASS1"))||(NET==_T("AST1"))||(NET==_T("ASA0")))	/////////B1
		{
			CLoSDLG Pdlg;
			Pdlg.m_overlapDisp = 1;	Pdlg.m_Overlap = 1; Pdlg.m_FdDisp = 1; 	Pdlg.m_Fd = 8;
			Pdlg.m_stepDisp = 1;	Pdlg.m_step = 10;	Pdlg.m_kfactor = 4.0/3.0; Pdlg.m_RxH = 1000.0;
			Pdlg.m_title  = _Z("Model Parameters");	Pdlg.m_title1 = _Z("Search Radius(km)");
			if(Pdlg.DoModal()==IDOK)
			{
				double GRlat , GRlon , Sradius_km , FrqRange;
				int OverLapFlag;
				GRlat = atof(GeoLat);		GRlon = atof(GeoLon);
				Sradius_km = Pdlg.m_RxH;	FrqRange = Pdlg.m_Fd;	OverLapFlag = Pdlg.m_Overlap;
				int AZstep = Pdlg.m_step;

				long nST = QGE06_BCBT_B1(GRlat,GRlon,Sradius_km,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType,Fragment,RPRstr) ;
				QGE06_BCBT_Qy();

				long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
				if(Nrowy>0)
				{
					int az0[37];
					for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
					double attH0[37], attV0[37];
					if(AntDir==_T("D"))
						GE84pattern(atol(AntCatID),attH0,attV0,Pol);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;		attV0[i] = 0;
						}
					attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
					double attH0[361], attV0[361];
					GE06patternT(atol(AntCatID), AntDir, Pol,attH0,attV0); 

					double latContour_deg[360],lonContour_deg[360];
					double ERP,attnH,attnV,RAZIM, h1 , h10[37], latC_deg,lonC_deg;
					double t = 10, L = 50;
					int ENV = 0, srv = 1 , P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;

					OnDatabaseStationsindesktop2(GRlat,GRlon);
					double Hasl_ST = LatLon2Hg(GRlat,GRlon);
					double Hasgl_ST = Hasl_ST + atof(Hagl_ST);

					double azz, h1_15[360] , lat3km  , lon3km , lat15km , lon15km;
					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					if(hef_flag)
					{
						for(long i=0;i<(360/AZstep);i++)
						{
							azz = (double)(i*AZstep);
							reckon( GRlat,GRlon,  3.0 , azz , &lat3km  , &lon3km) ;
							reckon( GRlat,GRlon, 15.0 , azz , &lat15km , &lon15km) ;
							h1_15[i] = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}
					}
					CString strY = _T("");
					long Ncty = 0 , iplot = 0;
					progress_num=0;
					
					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
					for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
					{
						CString m_Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
						double FStrig  = atof(GetFld(m_Sely,1));
						double hR  = atof(GetFld(m_Sely,2));

						if(FStrig>-999)
						{
							CString FileName;
							AdmRefID.Replace('/','_');
							FileName.Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,iplot+1);
							FILE *fpOUT = fopen(FileName,"wt");
							iplot++;
							////////////////////////////////////
							double h2 = hR , d_km , d_km1 , d_km2 , Em;

							for(int az = 0; az<(360/AZstep) ; az++)
							{
								RAZIM = (double)(az*AZstep);
							//	attnH = Interp2(az0,attH0,RAZIM,37);		attnV = Interp2(az0,attV0,RAZIM,37) ;
								attnH = attH0[az*AZstep];	attnV = attV0[az*AZstep];

								if     (Pol==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
								else if(Pol==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
								else if((Pol==_T("M"))||(Pol==_T("U")))		ERP = 10.0*log10(pow(10.0,(atof(ERP_h_dbw)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbw)-attnV)/10.0));
									
								if(!(hef_flag))
								{
									GE84Heff(atol(AntID),atof(MaxEffHght),h10) ;
									h10[36] = h10[0];
									h1 = Interp2(az0,h10,RAZIM,37) ;
								}
								Em = -999.0;

								d_km1 = 0;		d_km2 = Sradius_km;
								d_km = (d_km1 + d_km2)/2.0;

								while(1)
								{
									reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
									/////////////////////////// h1 //////////////////////
									if(hef_flag)
									{
										if (d_km>=15.0)		h1 = h1_15[az];
										else
										{
											reckon( GRlat,GRlon, 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
											reckon( GRlat,GRlon,     d_km , RAZIM , &lat15km , &lon15km) ;
											h1 = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
										}
									}
									Em = E_P1546_06(GRlat,GRlon,latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									Em = Em - 30.0 + ERP;

									if(fabs(Em-FStrig)<0.1)
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
										fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
										break;
									}
									else if(Em>=FStrig)
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km1 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
											fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
											break;
										}
									}
									else
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km2 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											d_km = d_km - 5.0;
											if(d_km<=0)
											{
												latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
												fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
												break;
											}
										}
									}

								}//while
								progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
								progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
								PeekAndPump();
								((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
							}//for az
				
							CString strY1 = _T("");
							long Ncty1 = QGE06_BCBT_Q5( FStrig,  hR, latContour_deg , lonContour_deg, 360/AZstep ,&strY1) ;
							if(Ncty1>0)
							{
								strY = strY + _T(",") + strY1;
								Ncty = Ncty + Ncty1;
							}
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);

						}//if FStrig
				
					}//for iFStrig
					strY.Delete(0);

				//	if(Ncty>0)
					{
						CString strX , RLONbs,RLATbs;
						Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
						if(PEC==0)		strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS"), SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
						else			strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS"), SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);

						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty+1;
						dlgList.m_mode = 1;
						dlgList.m_title1 = _Z("GE06 BC-BT to FX-LM - Affected Administrations");
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							for(long i=0;i<iplot;i++)
							{
								CString FileName;
								AdmRefID.Replace('/','_');
								FileName.Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,i+1);
								OnDrawVector(FileName);
								if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
							}
						}
					}//if Ncty
				}//if(Nrowy>0)
			}//Pdlg
		}/////////B1
		else if((NET==_T("ASS2"))||(NET==_T("AST2")))	/////////B2
		{
			CLoSDLG Pdlg;
			Pdlg.m_overlapDisp = 1; Pdlg.m_Overlap = 1; Pdlg.m_FdDisp = 1; Pdlg.m_Fd = 8;
			Pdlg.m_stepDisp = 1; 	Pdlg.m_step = 10; 	Pdlg.m_kfactor = 4.0/3.0; 	Pdlg.m_RxH = 1000.0;
			Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
			if(Pdlg.DoModal()==IDOK)
			{
				double GRlat , GRlon , Sradius_km , FrqRange;
				int OverLapFlag;
				Sradius_km = Pdlg.m_RxH;
				FrqRange = Pdlg.m_Fd;
				OverLapFlag = Pdlg.m_Overlap;
				int AZstep = Pdlg.m_step;

				CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN;
				long numAssign = QGE06_BCBT_A2(SfnID,&GeoLatN,&GeoLonN,&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
												&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN) ;
				double *GeoLatI;		GeoLatI = new double[numAssign];
				double *GeoLonI;		GeoLonI = new double[numAssign];
				double *FrequencyI;		FrequencyI = new double[numAssign];
				double *Hasgl_STI;		Hasgl_STI = new double[numAssign];
				double *ERPI;			ERPI = new double[numAssign*360/AZstep];
				double *h1_15;			h1_15 = new double[numAssign*360/AZstep];

				int az0[37];
				for(int i=0;i<=36;i++)		az0[i] = 10*i;

				CString AntDirI, AntCatIDI,PolI,ERP_h_dbwI , ERP_v_dbwI , AntIDI , MaxEffHghtI;
				double h10[37], lat3km  , lon3km , lat15km , lon15km, Hasl_ST;

			//	double attH0[37], attV0[37];
				double attH0[361], attV0[361];

				int progress_num=0;
				CString progress_str, progress_char = _T("I");
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
				for(long ASi=0;ASi<numAssign;ASi++)
				{
					GeoLatI[ASi] = atof(GetFld(GeoLatN,ASi+1));
					GeoLonI[ASi] = atof(GetFld(GeoLonN,ASi+1));
					FrequencyI[ASi] = atof(GetFld(FrequencyN,ASi+1));
					Hagl_ST = GetFld(AntHeightAGLN,ASi+1);
					AntDirI = GetFld(AntDirN,ASi+1);
					AntCatIDI = GetFld(AntCatIDN,ASi+1);
					PolI = GetFld(PolN,ASi+1);
					ERP_h_dbwI = GetFld(ERP_h_dbwN,ASi+1);
					ERP_v_dbwI = GetFld(ERP_v_dbwN,ASi+1);
					AntIDI = GetFld(AntIDN,ASi+1);
					MaxEffHghtI = GetFld(MaxEffHghtN,ASi+1);

					OnDatabaseStationsindesktop2(GeoLatI[ASi],GeoLonI[ASi]);
					Hasl_ST = LatLon2Hg(GeoLatI[ASi],GeoLonI[ASi]);
					Hasgl_STI[ASi] = Hasl_ST + atof(Hagl_ST);
/*
					if(AntDirI==_T("D"))
						GE84pattern(atol(AntCatIDI),attH0,attV0,PolI);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;		attV0[i] = 0;
						}
					attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
					GE06patternT(atol(AntCatIDI), AntDirI, PolI,attH0,attV0); 

					for(int az = 0; az<(360/AZstep) ; az++)
					{
						double RAZIM = (double)(az*AZstep);
					//	double attnH = Interp2(az0,attH0,RAZIM,37), attnV = Interp2(az0,attV0,RAZIM,37) ;
						double attnH = attH0[az*AZstep],	attnV = attV0[az*AZstep];

						if     (PolI==_T("H"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_h_dbwI)-attnH;
						else if(PolI==_T("V"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_v_dbwI)-attnV;
						else if((PolI==_T("M"))||(PolI==_T("U")))	ERPI[az + (360/AZstep)*ASi] = 10.0*log10(pow(10.0,(atof(ERP_h_dbwI)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbwI)-attnV)/10.0));
					
						if(hef_flag)		//d>15
						{
							reckon( GeoLatI[ASi],GeoLonI[ASi],  3.0 , RAZIM , &lat3km  , &lon3km) ;
							reckon( GeoLatI[ASi],GeoLonI[ASi], 15.0 , RAZIM , &lat15km , &lon15km) ;
							h1_15[az + (360/AZstep)*ASi] = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
						}
						else					//All
						{
							GE84Heff(atol(AntIDI),atof(MaxEffHghtI),h10) ;
							h10[36] = h10[0];
							h1_15[az + (360/AZstep)*ASi] = Interp2(az0,h10,RAZIM,37) ;
						}
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*numAssign/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*numAssign/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					}//for az
				}//for ASi

				CP154606.GrPointT(GeoLatI , GeoLonI, numAssign, &GRlat , &GRlon);
				long nST = QGE06_BCBT_B1(GRlat,GRlon,Sradius_km,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType, Fragment) ;
				QGE06_BCBT_Qy();

				long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
				if(Nrowy>0)
				{
					double latContour_deg[360] ,lonContour_deg[360] ;
					double t = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double Em , h1;
					CString strY = _T("");
					long Ncty = 0 , iplot = 0;
					progress_num=0;

					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
					for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
					{
						CString m_Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
						double FStrig  = atof(GetFld(m_Sely,1));
						double hR  = atof(GetFld(m_Sely,2));
						if(FStrig>-999)
						{
							CString FileName;
							AdmRefID.Replace('/','_');
							FileName.Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,iplot+1);
							FILE *fpOUT = fopen(FileName,"wt");
							iplot++;
							////////////////////////////////////
							double h2 = hR, RAZIM, latC_deg,lonC_deg , d_km, d_km1, d_km2,Esum,Esum0 ;

							for(int az = 0; az<(360/AZstep) ; az++)
							{
								RAZIM = (double)(az*AZstep);
								Esum = -999;

								d_km1 = 0;			d_km2 = Sradius_km;
								d_km = (d_km1 + d_km2)/2.0;

								while(1)
								{
									reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
									Esum0 = 0;
									for( ASi=0;ASi<numAssign;ASi++)
									{
										/////////////////////////// h1 //////////////////////
										if(hef_flag)
										{
											if (d_km>=15.0)		h1 = h1_15[az + (360/AZstep)*ASi];
											else
											{
												reckon(GeoLatI[ASi],GeoLonI[ASi], 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
												reckon(GeoLatI[ASi],GeoLonI[ASi],     d_km , RAZIM , &lat15km , &lon15km) ;
												h1 = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
											}
										}
										else		h1 = h1_15[az + (360/AZstep)*ASi];

										Em = E_P1546_06(GeoLatI[ASi],GeoLonI[ASi],latC_deg,lonC_deg, h1, Hasgl_STI[ASi], FrequencyI[ASi], kfactor, t,h2, ENV,srv,L,P1546Clangle);
										Em = Em - 30.0 + ERPI[az + (360/AZstep)*ASi];
										Esum0 = Esum0 + pow(10.0 , Em/10.0);
									}// for ASi
									Esum = 10.0*log10(Esum0);

									if(fabs(Esum-FStrig)<0.1)
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
										fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
										break;
									}
									else if(Esum>=FStrig)
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km1 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
											fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
											break;
										}
									}
									else
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km2 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											d_km = d_km - 5.0;
											if(d_km<=0)
											{
												latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
												fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
												break;
											}
										}
									}

								}//while
								progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
								progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
								PeekAndPump();
								((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

							}//for az

							CString strY1 = _T("");
							long Ncty1 = QGE06_BCBT_Q5( FStrig,  hR, latContour_deg , lonContour_deg, 360/AZstep ,&strY1) ;
							if(Ncty1>0)
							{
								strY = strY + _T(",") + strY1;		Ncty = Ncty + Ncty1;
							}
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);

						}//if FStrig

					}//for iFStrig
					strY.Delete(0);

				//	if(Ncty>0)
					{
						CString strX , RLONbs,RLATbs;
						Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
						if(PEC==0) 		strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
						else			strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);

						CString strOUT;
						long cd = QGE06_BCBT_A2_1( SfnID, IDst,&strOUT) ;
						if(cd>0)
							strX = strX +","+ strOUT;

						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty + 1;
						dlgList.m_rowsX = cd + 2;
						dlgList.m_mode = 1;
						dlgList.m_title1 = _Z("GE06 BC-BT to FX-LM - Affected Administrations");
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							for(long i=0;i<iplot;i++)
							{
								CString FileName;
								AdmRefID.Replace('/','_');
								FileName.Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,i+1);
								OnDrawVector(FileName);
								if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
							}
						}
					}//if Ncty

				}//if Nrowy>0
				delete [] GeoLatI; delete [] GeoLonI; delete [] FrequencyI; delete [] Hasgl_STI; delete [] ERPI; delete [] h1_15;

			}//Pdlg
		}/////////B2
		else if((NET==_T("ALS3"))||(NET==_T("ALT3")))	/////////B3
		{
			if(GeoArea.IsEmpty())
			{
				CLoSDLG Pdlg;
				Pdlg.m_overlapDisp = 1;		Pdlg.m_Overlap = 1;		Pdlg.m_FdDisp = 1;		Pdlg.m_Fd = 8;
				Pdlg.m_stepDisp = 1;	Pdlg.m_step = 10;	Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0;
				Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
				if(Pdlg.DoModal()==IDOK)
				{
					double Sradius_km , FrqRange;
					int OverLapFlag, AZstep = Pdlg.m_step;
					Sradius_km = Pdlg.m_RxH;		FrqRange = Pdlg.m_Fd;	OverLapFlag = Pdlg.m_Overlap;

					CString contourkeyN , nb_test_ptsN;
					long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey) , &contourkeyN , &nb_test_ptsN);
					long *contourkeyI;		contourkeyI = new long[contourkeyNum];
					long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
					double *GRlatC;			GRlatC = new double[contourkeyNum];
					double *GRlonC;			GRlonC = new double[contourkeyNum];
					long NcontourT = 0;
					for(long i=0;i<contourkeyNum;i++)
					{
						contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
						nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
						NcontourT = NcontourT + nb_test_ptsI[i];
					}
					double * lat_TP;   lat_TP = new double[NcontourT];
					double * lon_TP;   lon_TP = new double[NcontourT];
					double * y;		y = lat_TP;
					double * x;		x = lon_TP;
					for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
					{
						CString lat_tpStr, lon_tpStr;
						long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM] ,nb_test_ptsI[iCNUM] , &lat_tpStr, &lon_tpStr , &GRlatC[iCNUM] , &GRlonC[iCNUM]) ;
						for(long jTP=0;jTP<n_tp;jTP++)
						{
							*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
							*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
						}
					}
					double GRlat0 , GRlon0, GRlat , GRlon;
					CP154606.GrPointT(GRlatC , GRlonC, contourkeyNum, &GRlat0 , &GRlon0);

//					double pi = 4.0*atan(1.0);
					float POINTgr[1][2];
					POINTgr[0][0] = (float)(GRlon0*pi/180.0);	POINTgr[0][1] = (float)(GRlat0*pi/180.0);
					int uflag = false;

					long i1=0,i2=0;
					for( iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
					{
						long n_tp = nb_test_ptsI[iCNUM];
						i2 = i2 + n_tp;
						float (*CRDARR)[2]; CRDARR = new float[n_tp][2];
						long NRPNT = n_tp, i3 = 0;
						for(long jTP = i1 ; jTP<i2 ; jTP++)
						{
							CRDARR[i3][0] = (float)(lon_TP[jTP]*pi/180.0);
							CRDARR[i3][1] = (float)(lat_TP[jTP]*pi/180.0);
							i3++;
						}
						uflag = GEOPIA2((float *)POINTgr, (float *)CRDARR, &NRPNT);
						CRDARR = NULL;
						delete [] CRDARR;
						i1 = i1 + n_tp;
						if(uflag)
						{
							GRlat = GRlat0;		GRlon = GRlon0;		break;
						}
					}
					if(!uflag)
					{
						double dist1 , dist0 = 99999999999.0;
						for( i=0;i<NcontourT;i++)
						{
							dist1 = Distance_km(lat_TP[i],lon_TP[i],GRlat0,GRlon0);		dist0 = min(dist0, dist1);
							if(dist0==dist1)
							{
								GRlat = lat_TP[i];	GRlon = lon_TP[i];
							}
						}
					}
					OnDatabaseStationsindesktop2(GRlat,GRlon);

					long nST = QGE06_BCBT_B1(GRlat,GRlon,Sradius_km,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType, Fragment) ;
					QGE06_BCBT_Qy();

					long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
					if(Nrowy>0)
					{
						CString Band  = CP154606.GE06_Band(frq_MHz);
						CString RN = _T("");
						if     (NET==_T("ALT3"))						RN = RN_I;
						else if((NET==_T("ALS3"))&&(RPC==_T("RPC4")))	RN = _T("RN5");
						else if((NET==_T("ALS3"))&&(RPC==_T("RPC5")))	RN = _T("RN6");

						double latContour_deg[360] ,lonContour_deg[360] ;
						double t = 10, L = 50;
						int ENV = 0, srv = 1, P1546Clangle = 0;
						double kfactor = Pdlg.m_kfactor;
						double latTx[7], lonTx[7] , ERPall[7], Hasgl_ST = 0,h1 = 150;
						int progress_num=0;
						CString progress_str, progress_char = _T("I");
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

						CString strY = _T("");
						long Ncty = 0 , iplot = 0;

						CString *FileName;		FileName = new CString[Nrowy];
						AdmRefID.Replace('/','_');
						LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
						for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
						{
							CString m_Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
							double FStrig  = atof(GetFld(m_Sely,1));
							double hR  = atof(GetFld(m_Sely,2));
							if(FStrig>-999)
							{
								FileName[iplot].Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,iplot+1);
								FILE *fpOUT = fopen(FileName[iplot],"wt");
								iplot++;
								////////////////////////////////////
								double RAZIM,latC_deg,lonC_deg, d_km, d_km1, d_km2, Esum,Esum1,Em ,Esum0;
								double h2 = hR;
								for(int az = 0; az<(360/AZstep) ; az++)
								{
									RAZIM = (double)(az*AZstep);
									Esum = -999;

									d_km1 = 0;	d_km2 = Sradius_km;
									d_km =(d_km1+d_km2)/2.0;
									while(1)
									{
										reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
										Esum1 = -999;
/*
										double DistLimit = 999999999999 , latmin, lonmin , Dist1;
										for(long jTP=0;jTP<NcontourT;jTP++)
										{
											Dist1 = Distance_km(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP]);
											DistLimit = min(DistLimit , Dist1);
											if(DistLimit == Dist1)
											{
												latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
											}
										}
							//			for(long jTP=0;jTP<NcontourT;jTP++)
										{
							//				int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
											int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,latmin,lonmin,frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
											
											double Em ,Esum0 = 0;
											for(int ASi=0;ASi<N_Tx;ASi++)
											{
										//		Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, frq_MHz, t,h2, ENV,srv,L);
												Em = E_P154606(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
											
												Em = Em - 30.0 + ERPall[ASi];
												Esum0 = Esum0 + pow(10.0 , Em/10.0);
											}
											Esum1 = max(Esum1 , 10.0*log10(Esum0));
										}
										Esum = Esum1;
*/
										for(long jTP=0;jTP<NcontourT;jTP++)
										{
											int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
											
											Esum0 = 0;
											for(int ASi=0;ASi<N_Tx;ASi++)
											{
										//		Em = E_P1546_06(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
												Em = E_P154606AL_hR(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, frq_MHz, t,h2, ENV);
												
												Em = Em - 30.0 + ERPall[ASi];
												Esum0 = Esum0 + pow(10.0 , Em/10.0);
											}
											Esum1 = max(Esum1 , 10.0*log10(Esum0));
										}
										Esum = Esum1;

										if(fabs(Esum-FStrig)<0.1)
										{
											latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
											fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
											break;
										}
										else if(Esum>=FStrig)
										{
											if(d_km1 < (d_km2-10.0))
											{
												d_km1 = d_km;
												d_km = (d_km1 + d_km2)/2.0;
											}
											else
											{
												latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
												fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
												break;
											}
										}
										else
										{
											if(d_km1 < (d_km2-10.0))
											{
												d_km2 = d_km;
												d_km = (d_km1 + d_km2)/2.0;
											}
											else
											{
												d_km = d_km - 5.0;
												if(d_km<=0)
												{
													latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
													fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
													break;
												}
											}
										}
					
									}//while
									progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
									progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
									PeekAndPump();
									((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
								}//for az

								CString strY1 = _T("");
								long Ncty1 = QGE06_BCBT_Q5( FStrig,  hR, latContour_deg , lonContour_deg, 360/AZstep ,&strY1) ;
								if(Ncty1>0)
								{
									strY = strY + _T(",") + strY1;		Ncty = Ncty + Ncty1;
								}
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
								fclose(fpOUT);

							}//if FStrig

						}//for iFStrig
						strY.Delete(0);
						delete [] contourkeyI; delete [] nb_test_ptsI; delete [] GRlatC; delete [] GRlonC; delete [] lat_TP; delete [] lon_TP;

					//	if(Ncty>0)
						{
							float RLON   = (float)((pi/180.0)*GRlon), RLAT   = (float)((pi/180.0)*GRlat);
							CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
					//		CString adm1("");	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
							CString adm1 = Cty2AdmGE06(&cty1);

							CString strX , RLONbs,RLATbs;
							Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
							if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
							else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
							CGE06repDLG1 dlgList;
							dlgList.m_dataX = strX;
							dlgList.m_dataY = strY;
							dlgList.m_rowsY = Ncty + 1;
							dlgList.m_mode = 1;
							dlgList.m_title1 = _Z("GE06 BC-BT to FX-LM - Affected Administrations");
							dlgList.m_GoogleFlag = m_GoogleFlag;
							if(dlgList.DoModal()==IDOK)
							{
								for(long i=0;i<iplot;i++)
								{
									OnDrawVector(FileName[i]);
									if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName[i]);
								}
							}
							delete [] FileName;
						}//if Ncty

					}//Pdlg

				}//Nrow

			}//if GeoArea
			else		//!(GeoArea.IsEmpty())
			{
				CLoSDLG Pdlg;
				Pdlg.m_overlapDisp = 1;	Pdlg.m_Overlap = 1;	Pdlg.m_FdDisp = 1;	Pdlg.m_Fd = 8;
				Pdlg.m_stepDisp = 1;	Pdlg.m_step = 10;	Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0;
				Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
				if(Pdlg.DoModal()==IDOK)
				{
					double Sradius_km , FrqRange;
					int OverLapFlag;
					Sradius_km = Pdlg.m_RxH;
					FrqRange = Pdlg.m_Fd;
					OverLapFlag = Pdlg.m_Overlap;
					int AZstep = Pdlg.m_step;

					double GRlat0 , GRlon0, GRlat , GRlon;
					long NcontourT;

		//			CString FileName = VectorCountry1( GeoArea,&NcontourT) ;
		//			char X1[20],Y1[20];
		//			double * lat_TP;   lat_TP = new double[NcontourT];
		//			double * lon_TP;   lon_TP = new double[NcontourT];
		//			FILE *fp1 = fopen(FileName,"rt");
		//			for(long jTP=0;jTP<NcontourT;jTP++)
		//			{
		//				fscanf( fp1, "%s %s", X1,Y1);
		//				lat_TP[jTP] =  atof(Y1);			lon_TP[jTP] =  atof(X1);
		//			}
		//			fclose(fp1);
		//			CP154606.GrPointT(lat_TP , lon_TP, NcontourT, &GRlat0 , &GRlon0);

					CString lat_tpSTR, lon_tpSTR;
					NcontourT = QGE06_BCBT_Aux_Border(GeoArea, &lat_tpSTR, &lon_tpSTR,&GRlat0 , &GRlon0) ;
					double * lat_TP;   lat_TP = new double[NcontourT];
					double * lon_TP;   lon_TP = new double[NcontourT];
					for(long jTP=0;jTP<NcontourT;jTP++)
					{
						lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
						lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
					}
//					double pi = 4.0*atan(1.0);
/*
					float POINTgr[1][2];
					POINTgr[0][0] = (float)(GRlon0*pi/180.0);
					POINTgr[0][1] = (float)(GRlat0*pi/180.0);
					int uflag = false;
					float (*CRDARR1)[2]; CRDARR1 = new float[NcontourT][2];
					long NRPNT = NcontourT;
					for( jTP=0;jTP<NcontourT;jTP++)
					{
						CRDARR1[jTP][0] = (float)(lon_TP[jTP]*pi/180.0);
						CRDARR1[jTP][1] = (float)(lat_TP[jTP]*pi/180.0);
					}
					uflag = GEOPIA2((float *)POINTgr, (float *)CRDARR1, &NRPNT);
					delete [] CRDARR1;
					if(uflag)
					{
						GRlat = GRlat0;				GRlon = GRlon0;
					}
					if(!uflag)
					{
						double dist1 , dist0 = 99999999999.0;
						for(long i=0;i<NcontourT;i++)
						{
							dist1 = Distance_km(lat_TP[i],lon_TP[i],GRlat0,GRlon0);
 							dist0 = min(dist0 , dist1);
							if(dist0==dist1)
							{
								GRlat = lat_TP[i];	GRlon = lon_TP[i];
							}
						}
					}
*/
					GRlat = GRlat0;			GRlon = GRlon0;
					OnDatabaseStationsindesktop2(GRlat,GRlon);

					long nST = QGE06_BCBT_B1(GRlat,GRlon,Sradius_km,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType, Fragment) ;
					QGE06_BCBT_Qy();

					long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
					if(Nrowy>0)
					{
						CString Band  = CP154606.GE06_Band(frq_MHz);
						CString RN = _T("");
						if     (NET==_T("ALT3"))						RN = RN_I;
						else if((NET==_T("ALS3"))&&(RPC==_T("RPC4")))	RN = _T("RN5");
						else if((NET==_T("ALS3"))&&(RPC==_T("RPC5")))	RN = _T("RN6");

						double latContour_deg[360] ,lonContour_deg[360] ;
						double t = 10, h2 = 10, L = 50;
						int ENV = 0, srv = 1, P1546Clangle = 0;
						double kfactor = Pdlg.m_kfactor;
						double Sradius_km = Pdlg.m_RxH;

						double latTx[7], lonTx[7] , ERPall[7], Hasgl_ST = 0,h1 = 150;
						int progress_num=0;
						CString progress_str, progress_char = _T("I");
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

						CString strY = _T("");
						long Ncty = 0 , iplot = 0;
	
						CString *FileName;		FileName = new CString[Nrowy];
						AdmRefID.Replace('/','_');

						LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
						for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
						{
							CString m_Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
							double FStrig  = atof(GetFld(m_Sely,1));
							double hR  = atof(GetFld(m_Sely,2));
							if(FStrig>-999)
							{
								FileName[iplot].Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,iplot+1);
								FILE *fpOUT = fopen(FileName[iplot],"wt");
								iplot++;
								////////////////////////////////////
								double h2 = hR, RAZIM,latC_deg,lonC_deg, d_km, d_km1, d_km2,Esum,Esum1,Em ,Esum0 ;

								for(int az = 0; az<(360/AZstep) ; az++)
								{
									RAZIM = (double)(az*AZstep);
									Esum = -999;

									d_km1 = 0;		d_km2 = Sradius_km;
									d_km = (d_km1 + d_km2)/2.0;

									while(1)
									{
										reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
										Esum1 = -999;
/*
										double DistLimit = 999999999999 , latmin, lonmin , Dist1;
										for(long jTP=0;jTP<NcontourT;jTP++)
										{
											Dist1 = Distance_km(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP]);
											DistLimit = min(DistLimit , Dist1);
											if(DistLimit == Dist1)
											{
												latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
											}
										}
							//			for(long jTP=0;jTP<NcontourT;jTP++)
										{
							//				int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
											int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,latmin,lonmin,frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
							
											double Em ,Esum0 = 0;
											for(int ASi=0;ASi<N_Tx;ASi++)
											{
												Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, frq_MHz, t,h2, ENV,srv,L);

										//		Em = E_P154606(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
												Em = Em - 30.0 + ERPall[ASi];
												Esum0 = Esum0 + pow(10.0 , Em/10.0);
											}
											Esum1 = max(Esum1 , 10.0*log10(Esum0));
										}
										Esum = Esum1;
*/
										for(long jTP=0;jTP<NcontourT;jTP++)
										{
											int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
											Esum0 = 0;
											for(int ASi=0;ASi<N_Tx;ASi++)
											{
									//			Em = E_P1546_06(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
												Em = E_P154606AL_hR(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, frq_MHz, t,h2, ENV);
												
												Em = Em - 30.0 + ERPall[ASi];
												Esum0 = Esum0 + pow(10.0 , Em/10.0);
											}
											Esum1 = max(Esum1 , 10.0*log10(Esum0));
										}
										Esum = Esum1;

										if(fabs(Esum-FStrig)<0.1)
										{
											latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
											fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
											break;
										}
										else if(Esum>=FStrig)
										{
											if(d_km1 < (d_km2-10.0))
											{
												d_km1 = d_km;
												d_km = (d_km1 + d_km2)/2.0;
											}
											else
											{
												latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
												fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
												break;
											}
										}
										else
										{
											if(d_km1 < (d_km2-10.0))
											{
												d_km2 = d_km;
												d_km = (d_km1 + d_km2)/2.0;
											}
											else
											{
												d_km = d_km - 5.0;
												if(d_km<=0)
												{
													latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
													fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
													break;
												}
											}
										}

									}//while
									progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
									progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
									PeekAndPump();
									((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

								}//for az

								CString strY1 = _T("");
								long Ncty1 = QGE06_BCBT_Q5( FStrig,  hR, latContour_deg , lonContour_deg, 360/AZstep ,&strY1) ;
								if(Ncty1>0)
								{
									strY = strY + _T(",") + strY1;		Ncty = Ncty + Ncty1;
								}
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
								fclose(fpOUT);

							}//if FStrig

						}//for iFStrig
						strY.Delete(0);
						delete [] lat_TP; 	delete [] lon_TP;

					//	if(Ncty>0)
						{
							float RLON   = (float)((pi/180.0)*GRlon), RLAT   = (float)((pi/180.0)*GRlat);
							CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
				//			CString adm1("");	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
							CString adm1 = Cty2AdmGE06(&cty1);

							CString strX , RLONbs,RLATbs;
							Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
							if(PEC==0)		strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
							else			strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);

							CGE06repDLG1 dlgList;
							dlgList.m_dataX = strX;
							dlgList.m_dataY = strY;
							dlgList.m_rowsY = Ncty + 1;
							dlgList.m_mode = 1;
							dlgList.m_title1 = _Z("GE06 BC-BT to FX-LM - Affected Administrations");
							dlgList.m_GoogleFlag = m_GoogleFlag;
							if(dlgList.DoModal()==IDOK)
							{
								for(long i=0;i<iplot;i++)
								{
									OnDrawVector(FileName[i]);
									if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName[i]);
								}
							}
							delete [] FileName;

						}//if Ncty
						
					}//Pdlg

				}//Nrowy

			}//else GeoArea

		}/////////B3
		else if((NET==_T("ASS4"))||(NET==_T("AST4")))	/////////B4_1
		{
			CLoSDLG Pdlg;
			Pdlg.m_overlapDisp = 1;	Pdlg.m_Overlap = 1;		Pdlg.m_FdDisp = 1;		Pdlg.m_Fd = 8;
			Pdlg.m_stepDisp = 1;	Pdlg.m_step = 10;		Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0;
			Pdlg.m_title  = _Z("Model Parameters");
			Pdlg.m_title1 = _Z("Search Radius(km)");
			if(Pdlg.DoModal()==IDOK)
			{
				double Sradius_km , FrqRange;
				int OverLapFlag , AZstep = Pdlg.m_step;
				Sradius_km = Pdlg.m_RxH;	FrqRange = Pdlg.m_Fd;	OverLapFlag = Pdlg.m_Overlap;
			//+++++++++++++++++++++++++++++++++Assignment+++++++++++++++++++++++++++++++++++++++++++++++++++
				CString Band  = CP154606.GE06_Band(frq_MHz);

				CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN;

				long numAssign = QGE06_BCBT_A2(SfnID,&GeoLatN,&GeoLonN,&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
												&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,1) ;
				double *GeoLatI;		GeoLatI = new double[numAssign];
				double *GeoLonI;		GeoLonI = new double[numAssign];
				double *FrequencyI;		FrequencyI = new double[numAssign];
				double *Hasgl_STI;		Hasgl_STI = new double[numAssign];
				double *ERPI;			ERPI = new double[numAssign*360/AZstep];
				double *h1_15;			h1_15 = new double[numAssign*360/AZstep];

				int az0[37];
				for(int i=0;i<=36;i++)	az0[i] = 10*i;

				CString AntDirI, AntCatIDI,PolI,ERP_h_dbwI , ERP_v_dbwI , AntIDI , MaxEffHghtI;
				double h10[37], lat3km  , lon3km , lat15km , lon15km, Hasl_ST;

			//	double attH0[37], attV0[37];
				double attH0[361], attV0[361];

				int progress_num=0;
				CString progress_str, progress_char = _T("I");
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
				for(long ASi=0;ASi<numAssign;ASi++)
				{
					GeoLatI[ASi] = atof(GetFld(GeoLatN,ASi+1));
					GeoLonI[ASi] = atof(GetFld(GeoLonN,ASi+1));
					FrequencyI[ASi] = atof(GetFld(FrequencyN,ASi+1));
					Hagl_ST = GetFld(AntHeightAGLN,ASi+1);
					AntDirI = GetFld(AntDirN,ASi+1);
					AntCatIDI = GetFld(AntCatIDN,ASi+1);
					PolI = GetFld(PolN,ASi+1);
					ERP_h_dbwI = GetFld(ERP_h_dbwN,ASi+1);
					ERP_v_dbwI = GetFld(ERP_v_dbwN,ASi+1);
					AntIDI = GetFld(AntIDN,ASi+1);
					MaxEffHghtI = GetFld(MaxEffHghtN,ASi+1);

					OnDatabaseStationsindesktop2(GeoLatI[ASi],GeoLonI[ASi]);
					Hasl_ST = LatLon2Hg(GeoLatI[ASi],GeoLonI[ASi]);
					Hasgl_STI[ASi] = Hasl_ST + atof(Hagl_ST);
/*
					if(AntDirI==_T("D"))
						GE84pattern(atol(AntCatIDI),attH0,attV0,PolI);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;		attV0[i] = 0;
						}
					attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
					GE06patternT(atol(AntCatIDI), AntDirI, PolI,attH0,attV0); 

					for(int az = 0; az<(360/AZstep) ; az++)
					{
						double RAZIM = (double)(az*AZstep);
					//	double attnH = Interp2(az0,attH0,RAZIM,37), attnV = Interp2(az0,attV0,RAZIM,37) ;
						double attnH = attH0[az*AZstep],	attnV = attV0[az*AZstep];

						if     (PolI==_T("H"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_h_dbwI)-attnH;
						else if(PolI==_T("V"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_v_dbwI)-attnV;
						else if((PolI==_T("M"))||(PolI==_T("U")))	ERPI[az + (360/AZstep)*ASi] = 10.0*log10(pow(10.0,(atof(ERP_h_dbwI)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbwI)-attnV)/10.0));
						if(hef_flag)		//d>15
						{
							reckon( GeoLatI[ASi],GeoLonI[ASi],  3.0 , RAZIM , &lat3km  , &lon3km) ;
							reckon( GeoLatI[ASi],GeoLonI[ASi], 15.0 , RAZIM , &lat15km , &lon15km) ;
							h1_15[az + (360/AZstep)*ASi] = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
						}
						else					//All
						{
							GE84Heff(atol(AntIDI),atof(MaxEffHghtI),h10) ;
							h10[36] = h10[0];
							h1_15[az + (360/AZstep)*ASi] = Interp2(az0,h10,RAZIM,37) ;
						}
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*numAssign/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*numAssign/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

					}//for az
				}//for ASi
			//+++++++++++++++++++++++++++++++++Allotment+++++++++++++++++++++++++++++++++++++++++++++++++++
				CString AllotmentSTR = QGE06_BCBT_A4_1(SfnID) ;
				CString GeoAreaAL = GetFld(AllotmentSTR,9) ;

				double GRlat0 , GRlon0, GRlat , GRlon/*, pi = 4.0*atan(1.0)*/;
				long NcontourT = 0;
				double * lat_TP;		double * lon_TP;
				if(GeoAreaAL.IsEmpty())
				{
					CString contourkeyN , nb_test_ptsN;
					long contourkeyNum = QGE06_BCBT_A3_2(atol(GetFld(AllotmentSTR,1)) , &contourkeyN , &nb_test_ptsN);
					long *contourkeyI;		contourkeyI = new long[contourkeyNum];
					long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
					double *GRlatC;			GRlatC = new double[contourkeyNum];
					double *GRlonC;			GRlonC = new double[contourkeyNum];
					for( i=0;i<contourkeyNum;i++)
					{
						contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
						nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
						NcontourT = NcontourT + nb_test_ptsI[i];
					}
					lat_TP = new double[NcontourT];		lon_TP = new double[NcontourT];
					double * y;		y = lat_TP;
					double * x;		x = lon_TP;
					for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
					{
						CString lat_tpStr, lon_tpStr;
						long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM] ,nb_test_ptsI[iCNUM] , &lat_tpStr, &lon_tpStr , &GRlatC[iCNUM] , &GRlonC[iCNUM]) ;
						for(long jTP=0;jTP<n_tp;jTP++)
						{
							*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
							*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
						}
					}
					CP154606.GrPointT(GRlatC , GRlonC, contourkeyNum, &GRlat0 , &GRlon0);
	
					float POINTgr[1][2];
					POINTgr[0][0] = (float)(GRlon0*pi/180.0);		POINTgr[0][1] = (float)(GRlat0*pi/180.0);
					int uflag = false;
					long i1=0,i2=0;
					for( iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
					{
						long n_tp = nb_test_ptsI[iCNUM];
						i2 = i2 + n_tp;
						float (*CRDARR)[2]; CRDARR = new float[n_tp][2];
						long NRPNT = n_tp , i3 = 0;

						for(long jTP = i1 ; jTP<i2 ; jTP++)
						{
							CRDARR[i3][0] = (float)(lon_TP[jTP]*pi/180.0);
							CRDARR[i3][1] = (float)(lat_TP[jTP]*pi/180.0);
							i3++;
						}
						uflag = GEOPIA2((float *)POINTgr, (float *)CRDARR, &NRPNT);
						CRDARR = NULL;
						delete [] CRDARR;
						i1 = i1 + n_tp;
						if(uflag)
						{
							GRlat = GRlat0;		GRlon = GRlon0;			break;
						}
					}
					if(!uflag)
					{
						double dist1 , dist0 = 99999999999.0;
						for( i=0;i<NcontourT;i++)
						{
							dist1 = Distance_km(lat_TP[i],lon_TP[i],GRlat0,GRlon0);		dist0 = min(dist0, dist1);
							if(dist0==dist1)
							{
								GRlat = lat_TP[i];	GRlon = lon_TP[i];
							}
						}
					}
					delete [] contourkeyI; delete [] nb_test_ptsI; delete [] GRlatC; delete [] GRlonC;

				}//	if(GeoAreaAL.IsEmpty())
				else
				{
					CString lat_tpSTR, lon_tpSTR;
					NcontourT = QGE06_BCBT_Aux_Border(GeoAreaAL, &lat_tpSTR, &lon_tpSTR,&GRlat0 , &GRlon0) ;
					lat_TP = new double[NcontourT];
					lon_TP = new double[NcontourT];
					for(long jTP=0;jTP<NcontourT;jTP++)
					{
						lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
						lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
					}
					GRlat = GRlat0;			GRlon = GRlon0;

				}//	else(GeoAreaAL.IsEmpty())
				OnDatabaseStationsindesktop2(GRlat,GRlon);

				long nST = QGE06_BCBT_B1(GRlat,GRlon,Sradius_km,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType, Fragment) ;
				QGE06_BCBT_Qy();

				long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
				if(Nrowy>0)
				{
			//00000000000000000000000000000000000000000000000000000000000000000000000000
					CString STNal = CP154606.GE06_STN(GetFld(AllotmentSTR,2),GetFld(AllotmentSTR,3));
					int PECal = GE06_PEC(GetFld(AllotmentSTR,4) , GetFld(AllotmentSTR,5) , GetFld(AllotmentSTR,6) , SfnID , STNal) ;
					CString NETal;	NETal.Format("%s%d",STNal,PECal);
					CString RPCal = GetFld(AllotmentSTR,7);

					CString RNal = _T("");
					if     (NETal==_T("ALT4"))							RNal = GetFld(AllotmentSTR,8);
					else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC4")))	RNal = _T("RN5");
					else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC5")))	RNal = _T("RN6");
			//00000000000000000000000000000000000000000000000000000000000000000000000000
					double latContour_deg[360] ,lonContour_deg[360] ;
					double t = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double latTx[7], lonTx[7] , ERPall[7], Em , h1;
					progress_num=0;
					CString strY = _T("");
					long Ncty = 0 , iplot = 0;

					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 

					for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
					{
						CString m_Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
						double FStrig  = atof(GetFld(m_Sely,1));
						double hR  = atof(GetFld(m_Sely,2));
						if(FStrig>-999)
						{
							CString FileName;
							AdmRefID.Replace('/','_');
							FileName.Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,iplot+1);
							FILE *fpOUT = fopen(FileName,"wt");
							iplot++;
							////////////////////////////////////
							double h2 = hR,	RAZIM,latC_deg,lonC_deg,EsumASS,EsumALLOT , Esum, d_km, d_km1, d_km2, Esum0, Esum1;

							for(int az = 0; az<(360/AZstep) ; az++)
							{
								RAZIM = (double)(az*AZstep);
								Esum = -999;

								d_km1 = 0;		d_km2 = Sradius_km;
								d_km = (d_km1 + d_km2)/2.0;
								while(1)
								{
									reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;

									Esum0 = 0;
									for( ASi=0;ASi<numAssign;ASi++)
									{
										/////////////////////////// h1 //////////////////////
										if(hef_flag)
										{
											if (d_km>=15.0)		h1 = h1_15[az + (360/AZstep)*ASi];
											else
											{
												reckon(GeoLatI[ASi],GeoLonI[ASi], 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
												reckon(GeoLatI[ASi],GeoLonI[ASi],     d_km , RAZIM , &lat15km , &lon15km) ;
												h1 = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
											}
										}
										else		h1 = h1_15[az + (360/AZstep)*ASi];

										Em = E_P1546_06(GeoLatI[ASi],GeoLonI[ASi],latC_deg,lonC_deg, h1, Hasgl_STI[ASi], FrequencyI[ASi], kfactor, t,h2, ENV,srv,L,P1546Clangle);
										Em = Em - 30.0 + ERPI[az + (360/AZstep)*ASi];
										Esum0 = Esum0 + pow(10.0 , Em/10.0);
									}// for ASi
									EsumASS = 10.0*log10(Esum0);

									Esum1 = -999;
/*
									double DistLimit = 999999999999 , latmin, lonmin , Dist1, Esum1 = -999;
									for(long jTP=0;jTP<NcontourT;jTP++)
									{
										Dist1 = Distance_km(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP]);
										DistLimit = min(DistLimit , Dist1);
										if(DistLimit == Dist1)
										{
											latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
										}
									}
						//			for(long jTP=0;jTP<NcontourT;jTP++)
									{
						//				int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
										int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,latmin,lonmin,frq_MHz,Band,RPCal,RNal, ERPall,latTx,lonTx) ;
										double Esum0 = 0;
										for(int ASi=0;ASi<N_Tx;ASi++)
										{
											Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150, frq_MHz, t,h2, ENV,srv,L);

									//		Em = E_P154606(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
											Em = Em - 30.0 + ERPall[ASi];
											Esum0 = Esum0 + pow(10.0 , Em/10.0);
										}
										Esum1 = max(Esum1 , 10.0*log10(Esum0));
									}
									EsumALLOT = Esum1;
*/
									for(long jTP=0;jTP<NcontourT;jTP++)
									{
										int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPCal,RNal, ERPall,latTx,lonTx) ;
										Esum0 = 0;
										for(int ASi=0;ASi<N_Tx;ASi++)
										{
								//			Em = E_P1546_06(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150, 0, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
											Em = E_P154606AL_hR(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150.0, frq_MHz, t,h2, ENV);
											
											Em = Em - 30.0 + ERPall[ASi];
											Esum0 = Esum0 + pow(10.0 , Em/10.0);
										}
										Esum1 = max(Esum1 , 10.0*log10(Esum0));
									}
									EsumALLOT = Esum1;

									Esum = max(EsumASS,EsumALLOT);

									if(fabs(Esum-FStrig)<0.1)
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
										fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
										break;
									}
									else if(Esum>=FStrig)
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km1 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
											fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
											break;
										}
									}
									else
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km2 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											d_km = d_km - 5.0;
											if(d_km<=0)
											{
												latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
												fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
												break;
											}
										}
									}

								}//while
								progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
								progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
								PeekAndPump();
								((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

							}//for az

							CString strY1 = _T("");
							long Ncty1 = QGE06_BCBT_Q5( FStrig,  hR, latContour_deg , lonContour_deg, 360/AZstep ,&strY1) ;
							if(Ncty1>0)
							{
								strY = strY + _T(",") + strY1;
								Ncty = Ncty + Ncty1;
							}
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);

						}//if FStrig

					}//for iFStrig
					strY.Delete(0);
					delete [] GeoLatI; 	delete [] GeoLonI; delete [] FrequencyI; delete [] Hasgl_STI;
					delete [] ERPI; delete [] h1_15; delete [] lat_TP; delete [] lon_TP;
				//	if(Ncty>0)
					{
						CString strX , RLONbs,RLATbs;
						Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
						if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
						else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);

						CString strOUT;
						long cd = QGE06_BCBT_A2_1( SfnID, IDst,&strOUT,1) ;
						if(cd>0)
							strX = strX +","+ strOUT;

						CString alLink = QGE06_BCBT_A4_2( SfnID) ;
						strX = strX +","+ alLink;

						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty + 1;
						dlgList.m_rowsX = cd + 2 + 1;
						dlgList.m_mode = 1;
						dlgList.m_title1 = _Z("GE06 BC-BT to FX-LM - Affected Administrations");
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							for(long i=0;i<iplot;i++)
							{
								CString FileName;
								AdmRefID.Replace('/','_');
								FileName.Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,i+1);
								OnDrawVector(FileName);
								if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
							}
						}

					}//if Ncty

				}//Pdlg

			}//Nrowy

		}/////////B4_1
		else if((NET==_T("ALS4"))||(NET==_T("ALT4")))	/////////B4_2
		{
			CLoSDLG Pdlg;
			Pdlg.m_overlapDisp = 1;	Pdlg.m_Overlap = 1;	Pdlg.m_FdDisp = 1;	Pdlg.m_Fd = 8;
			Pdlg.m_stepDisp = 1;	Pdlg.m_step = 10;	Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0;
			Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
			if(Pdlg.DoModal()==IDOK)
			{
				double Sradius_km , FrqRange;
				int OverLapFlag , AZstep = Pdlg.m_step;
				Sradius_km = Pdlg.m_RxH;	FrqRange = Pdlg.m_Fd;	OverLapFlag = Pdlg.m_Overlap;
			
			//+++++++++++++++++++++++++++++++++Assignment+++++++++++++++++++++++++++++++++++++++++++++++++++
				CString Band  = CP154606.GE06_Band(frq_MHz);
				CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN;
				long numAssign = QGE06_BCBT_A2(SfnID,&GeoLatN,&GeoLonN,&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
												&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,1) ;
				double *GeoLatI;		GeoLatI = new double[numAssign];
				double *GeoLonI;		GeoLonI = new double[numAssign];
				double *FrequencyI;		FrequencyI = new double[numAssign];
				double *Hasgl_STI;		Hasgl_STI = new double[numAssign];
				double *ERPI;			ERPI = new double[numAssign*360/AZstep];
				double *h1_15;			h1_15 = new double[numAssign*360/AZstep];

				int az0[37];
				for(int i=0;i<=36;i++)		az0[i] = 10*i;

				CString AntDirI, AntCatIDI,PolI,ERP_h_dbwI , ERP_v_dbwI , AntIDI , MaxEffHghtI;
				double h10[37], lat3km  , lon3km , lat15km , lon15km, Hasl_ST;

			//	double attH0[37], attV0[37];
				double attH0[361], attV0[361];

				int progress_num=0;
				CString progress_str, progress_char = _T("I");
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
				for(long ASi=0;ASi<numAssign;ASi++)
				{
					GeoLatI[ASi] = atof(GetFld(GeoLatN,ASi+1));
					GeoLonI[ASi] = atof(GetFld(GeoLonN,ASi+1));
					FrequencyI[ASi] = atof(GetFld(FrequencyN,ASi+1));
					Hagl_ST = GetFld(AntHeightAGLN,ASi+1);
					AntDirI = GetFld(AntDirN,ASi+1);
					AntCatIDI = GetFld(AntCatIDN,ASi+1);
					PolI = GetFld(PolN,ASi+1);
					ERP_h_dbwI = GetFld(ERP_h_dbwN,ASi+1);
					ERP_v_dbwI = GetFld(ERP_v_dbwN,ASi+1);
					AntIDI = GetFld(AntIDN,ASi+1);
					MaxEffHghtI = GetFld(MaxEffHghtN,ASi+1);

					OnDatabaseStationsindesktop2(GeoLatI[ASi],GeoLonI[ASi]);
					Hasl_ST = LatLon2Hg(GeoLatI[ASi],GeoLonI[ASi]);
					Hasgl_STI[ASi] = Hasl_ST + atof(Hagl_ST);
/*
					if(AntDirI==_T("D"))
						GE84pattern(atol(AntCatIDI),attH0,attV0,PolI);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;		attV0[i] = 0;
						}
					attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
					GE06patternT(atol(AntCatIDI), AntDirI, PolI,attH0,attV0); 

					for(int az = 0; az<(360/AZstep) ; az++)
					{
						double RAZIM = (double)(az*AZstep);
				//		double attnH = Interp2(az0,attH0,RAZIM,37),		attnV = Interp2(az0,attV0,RAZIM,37) ;
						double attnH = attH0[az*AZstep],	attnV = attV0[az*AZstep];

						if     (PolI==_T("H")) 						ERPI[az + (360/AZstep)*ASi] = atof(ERP_h_dbwI)-attnH;
						else if(PolI==_T("V"))						ERPI[az + (360/AZstep)*ASi] = atof(ERP_v_dbwI)-attnV;
						else if((PolI==_T("M"))||(PolI==_T("U")))	ERPI[az + (360/AZstep)*ASi] = 10.0*log10(pow(10.0,(atof(ERP_h_dbwI)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbwI)-attnV)/10.0));
					
						if(hef_flag)		//d>15
						{
							reckon( GeoLatI[ASi],GeoLonI[ASi],  3.0 , RAZIM , &lat3km  , &lon3km) ;
							reckon( GeoLatI[ASi],GeoLonI[ASi], 15.0 , RAZIM , &lat15km , &lon15km) ;
							h1_15[az + (360/AZstep)*ASi] = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
						}
						else					//All
						{
							GE84Heff(atol(AntIDI),atof(MaxEffHghtI),h10) ;
							h10[36] = h10[0];
							h1_15[az + (360/AZstep)*ASi] = Interp2(az0,h10,RAZIM,37) ;
						}
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*numAssign/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*numAssign/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

					}//for az
				}//for ASi
			//+++++++++++++++++++++++++++++++++Allotment+++++++++++++++++++++++++++++++++++++++++++++++++++
				double GRlat0 , GRlon0, GRlat , GRlon/*, pi = 4.0*atan(1.0)*/;
				long NcontourT = 0;
				double * lat_TP;		double * lon_TP;
				if(GeoArea.IsEmpty())
				{
					CString contourkeyN , nb_test_ptsN;
					long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey) , &contourkeyN , &nb_test_ptsN);
					long *contourkeyI;		contourkeyI = new long[contourkeyNum];
					long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
					double *GRlatC;			GRlatC = new double[contourkeyNum];
					double *GRlonC;			GRlonC = new double[contourkeyNum];
					for( i=0;i<contourkeyNum;i++)
					{
						contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
						nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
						NcontourT = NcontourT + nb_test_ptsI[i];
					}
					lat_TP = new double[NcontourT];			lon_TP = new double[NcontourT];
					double * y;		y = lat_TP;
					double * x;		x = lon_TP;
					for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
					{
						CString lat_tpStr, lon_tpStr;
						long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM] ,nb_test_ptsI[iCNUM] , &lat_tpStr, &lon_tpStr , &GRlatC[iCNUM] , &GRlonC[iCNUM]) ;
						for(long jTP=0;jTP<n_tp;jTP++)
						{
							*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
							*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
						}
					}
					CP154606.GrPointT(GRlatC , GRlonC, contourkeyNum, &GRlat0 , &GRlon0);
	
					float POINTgr[1][2];
					POINTgr[0][0] = (float)(GRlon0*pi/180.0);
					POINTgr[0][1] = (float)(GRlat0*pi/180.0);
					int uflag = false;
					long i1=0,i2=0;
					for( iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
					{
						long n_tp = nb_test_ptsI[iCNUM];
						i2 = i2 + n_tp;

						float (*CRDARR)[2]; CRDARR = new float[n_tp][2];
						long NRPNT = n_tp;
						long i3 = 0;
						for(long jTP = i1 ; jTP<i2 ; jTP++)
						{
							CRDARR[i3][0] = (float)(lon_TP[jTP]*pi/180.0);
							CRDARR[i3][1] = (float)(lat_TP[jTP]*pi/180.0);
							i3++;
						}
						uflag = GEOPIA2((float *)POINTgr, (float *)CRDARR, &NRPNT);
						CRDARR = NULL;
						delete [] CRDARR;
						i1 = i1 + n_tp;
						if(uflag)
						{
							GRlat = GRlat0;		GRlon = GRlon0;		break;
						}
					}
					if(!uflag)
					{
						double dist1 , dist0 = 99999999999.0;
						for( i=0;i<NcontourT;i++)
						{
							dist1 = Distance_km(lat_TP[i],lon_TP[i],GRlat0,GRlon0);		dist0 = min(dist0, dist1);
							if(dist0==dist1)
							{
								GRlat = lat_TP[i];	GRlon = lon_TP[i];
							}
						}
					}
					delete [] contourkeyI; delete [] nb_test_ptsI;	delete [] GRlatC; delete [] GRlonC;
				}//	if(GeoArea.IsEmpty())
				else
				{
					CString lat_tpSTR, lon_tpSTR;
					NcontourT = QGE06_BCBT_Aux_Border(GeoArea, &lat_tpSTR, &lon_tpSTR,&GRlat0 , &GRlon0) ;
					lat_TP = new double[NcontourT];		lon_TP = new double[NcontourT];
					for(long jTP=0;jTP<NcontourT;jTP++)
					{
						lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
						lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
					}
					GRlat = GRlat0;			GRlon = GRlon0;
				}//	else(GeoArea.IsEmpty())
				OnDatabaseStationsindesktop2(GRlat,GRlon);

				long nST = QGE06_BCBT_B1(GRlat,GRlon,Sradius_km,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType, Fragment) ;
				QGE06_BCBT_Qy();

				long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
				if(Nrowy>0)
				{
					CString RN = _T("");
					if     (NET==_T("ALT4"))						RN = RN_I;
					else if((NET==_T("ALS4"))&&(RPC==_T("RPC4")))	RN = _T("RN5");
					else if((NET==_T("ALS4"))&&(RPC==_T("RPC5")))	RN = _T("RN6");

					double latContour_deg[360] ,lonContour_deg[360] ;
					double t = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;
					double latTx[7], lonTx[7] , ERPall[7], Em , h1;
					progress_num=0;
					CString strY = _T("");
					long Ncty = 0 , iplot = 0;
					CString *FileName;		FileName = new CString[Nrowy];
					AdmRefID.Replace('/','_');

					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
					for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
					{
						CString m_Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
						double FStrig  = atof(GetFld(m_Sely,1));
						double hR  = atof(GetFld(m_Sely,2));
						if(FStrig>-999)
						{
							FileName[iplot].Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,iplot+1);
							FILE *fpOUT = fopen(FileName[iplot],"wt");
							iplot++;
							////////////////////////////////////
							double h2 = hR, RAZIM,latC_deg,lonC_deg,d_km,d_km1,d_km2,EsumASS,EsumALLOT , Esum, Esum1, Esum0;

							for(int az = 0; az<(360/AZstep) ; az++)
							{
								RAZIM = (double)(az*AZstep);
								Esum = -999;

								d_km1 = 0;		d_km2 = Sradius_km;
								d_km = (d_km1 + d_km2)/2.0;
								while(1)
								{
									reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
									Esum0 = 0;
									for( ASi=0;ASi<numAssign;ASi++)
									{
										/////////////////////////// h1 //////////////////////
										if(hef_flag)
										{
											if (d_km>=15.0)		h1 = h1_15[az + (360/AZstep)*ASi];
											else
											{
												reckon(GeoLatI[ASi],GeoLonI[ASi], 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
												reckon(GeoLatI[ASi],GeoLonI[ASi],     d_km , RAZIM , &lat15km , &lon15km) ;
												h1 = Hasgl_STI[ASi] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
											}
										}
										else		h1 = h1_15[az + (360/AZstep)*ASi];

										Em = E_P1546_06(GeoLatI[ASi],GeoLonI[ASi],latC_deg,lonC_deg, h1, Hasgl_STI[ASi], FrequencyI[ASi], kfactor, t,h2, ENV,srv,L,P1546Clangle);
										Em = Em - 30.0 + ERPI[az + (360/AZstep)*ASi];
										Esum0 = Esum0 + pow(10.0 , Em/10.0);
									}// for ASi
									EsumASS = 10.0*log10(Esum0);
									Esum1 = -999;
/*
									double DistLimit = 999999999999 , latmin, lonmin , Dist1;
									for(long jTP=0;jTP<NcontourT;jTP++)
									{
										Dist1 = Distance_km(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP]);
										DistLimit = min(DistLimit , Dist1);
										if(DistLimit == Dist1)
										{
											latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
										}
									}
						//			for(long jTP=0;jTP<NcontourT;jTP++)
									{
						//				int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
				//						int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,latmin,lonmin,frq_MHz,Band,RPCal,RNal, ERPall,latTx,lonTx) ;
										int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,latmin,lonmin,frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
										double Esum0 = 0;
										for(int ASi=0;ASi<N_Tx;ASi++)
										{
											Em = E_P154606AL(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150, frq_MHz, t,h2, ENV,srv,L);
									//		Em = E_P154606(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
											Em = Em - 30.0 + ERPall[ASi];
											Esum0 = Esum0 + pow(10.0 , Em/10.0);
										}
										Esum1 = max(Esum1 , 10.0*log10(Esum0));
									}
									EsumALLOT = Esum1;
*/
									for(long jTP=0;jTP<NcontourT;jTP++)
									{
										int N_Tx = CP154606.Table_RNs(latC_deg,lonC_deg,lat_TP[jTP],lon_TP[jTP],frq_MHz,Band,RPC,RN, ERPall,latTx,lonTx) ;
										Esum0 = 0;
										for(int ASi=0;ASi<N_Tx;ASi++)
										{
									//		Em = E_P1546_06(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150, 0, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
											Em = E_P154606AL_hR(latTx[ASi],lonTx[ASi],latC_deg,lonC_deg, 150.0, frq_MHz, t,h2, ENV);
											
											Em = Em - 30.0 + ERPall[ASi];
											Esum0 = Esum0 + pow(10.0 , Em/10.0);
										}
										Esum1 = max(Esum1 , 10.0*log10(Esum0));
									}
									EsumALLOT = Esum1;

									Esum = max(EsumASS,EsumALLOT);

									if(fabs(Esum-FStrig)<0.1)
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
										fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
										break;
									}
									else if(Esum>=FStrig)
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km1 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
											fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
											break;
										}
									}
									else
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km2 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											d_km = d_km - 5.0;
											if(d_km<=0)
											{
												latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
												fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
												break;
											}
										}
									}

								}//while
								progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
								progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
								PeekAndPump();
								((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
							}//for az
							CString strY1 = _T("");
							long Ncty1 = QGE06_BCBT_Q5( FStrig,  hR, latContour_deg , lonContour_deg, 360/AZstep ,&strY1) ;
							if(Ncty1>0)
							{
								strY = strY + _T(",") + strY1;		Ncty = Ncty + Ncty1;
							}
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);
						}//if FStrig

					}//for iFStrig
					strY.Delete(0);
					delete [] GeoLatI; delete [] GeoLonI; delete [] FrequencyI; delete [] Hasgl_STI;
					delete [] ERPI; delete [] h1_15; delete [] lat_TP; delete [] lon_TP;
				//	if(Ncty>0)
					{
						float RLON   = (float)((pi/180.0)*GRlon), RLAT   = (float)((pi/180.0)*GRlat);
						CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
			//			CString adm1("");	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
						CString adm1 = Cty2AdmGE06(&cty1);

						CString strX , RLONbs,RLATbs;
						Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
						if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
						else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);

						CString strOUT;
						long cd = QGE06_BCBT_A2_1( SfnID, IDst,&strOUT,1) ;
						if(cd>0)
							strX = strX +","+ strOUT;

						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty + 1;
						dlgList.m_rowsX = cd + 2;
						dlgList.m_mode = 1;
						dlgList.m_title1 = _Z("GE06 BC-BT to FX-LM - Affected Administrations");
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							for(long i=0;i<iplot;i++)
							{
								OnDrawVector(FileName[i]);
								if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName[i]);
							}
						}
						delete [] FileName;
					}//if Ncty
				}//Nrowy
			}//Pdlg

		}/////////B4_2
		else if((NET==_T("ASS5"))||(NET==_T("AST5")))	/////////A5_1
		{
			CLoSDLG Pdlg;
			Pdlg.m_overlapDisp = 1;	Pdlg.m_Overlap = 1;	Pdlg.m_FdDisp = 1;	Pdlg.m_Fd = 8;
			Pdlg.m_stepDisp = 1;	Pdlg.m_step = 10;	Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0;
			Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
			if(Pdlg.DoModal()==IDOK)
			{
				double Sradius_km , FrqRange;
				int OverLapFlag , AZstep = Pdlg.m_step;
				Sradius_km = Pdlg.m_RxH;		FrqRange = Pdlg.m_Fd;		OverLapFlag = Pdlg.m_Overlap;

				double GRlat , GRlon;
				GRlat = atof(GeoLat);		GRlon = atof(GeoLon);
				long nST = QGE06_BCBT_B1(GRlat,GRlon,Sradius_km,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType,Fragment) ;
				QGE06_BCBT_Qy();
				long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
				if(Nrowy>0)
				{
					////////////////////////////////////
					int az0[37];
					for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
					double attH0[37], attV0[37];
					if(AntDir==_T("D"))
						GE84pattern(atol(AntCatID),attH0,attV0,Pol);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;		attV0[i] = 0;
						}
					attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
					double attH0[361], attV0[361];
					GE06patternT(atol(AntCatID), AntDir, Pol,attH0,attV0); 

					double latContour_deg[360],lonContour_deg[360];
					double ERP,attnH,attnV,RAZIM, h1 , h10[37] , latC_deg,lonC_deg;
					double t = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;

					OnDatabaseStationsindesktop2(GRlat,GRlon);
					double Hasl_ST = LatLon2Hg(GRlat,GRlon);
					double Hasgl_ST = Hasl_ST + atof(Hagl_ST);

					double azz, h1_15[360] , lat3km  , lon3km , lat15km , lon15km;
					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					if(hef_flag)
					{
						for(long i=0;i<(360/AZstep);i++)
						{
							azz = (double)(i*AZstep);
							reckon( GRlat,GRlon,  3.0 , azz , &lat3km  , &lon3km) ;
							reckon( GRlat,GRlon, 15.0 , azz , &lat15km , &lon15km) ;
							h1_15[i] = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}
					}
					CString strY = _T("");
					long Ncty = 0 , iplot = 0;
					progress_num=0;

					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 
					for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
					{
						CString m_Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
						double FStrig  = atof(GetFld(m_Sely,1));
						double hR  = atof(GetFld(m_Sely,2));
						if(FStrig>-999)
						{
							CString FileName;
							AdmRefID.Replace('/','_');
							FileName.Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,iplot+1);
							FILE *fpOUT = fopen(FileName,"wt");
							iplot++;
							////////////////////////////////////
							double h2 = hR , d_km, d_km1, d_km2 , Em;

							for(int az = 0; az<(360/AZstep) ; az++)
							{
								RAZIM = (double)(az*AZstep);
							//	attnH = Interp2(az0,attH0,RAZIM,37) ;		attnV = Interp2(az0,attV0,RAZIM,37) ;
								attnH = attH0[az*AZstep];	attnV = attV0[az*AZstep];

								if     (Pol==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
								else if(Pol==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
								else if((Pol==_T("M"))||(Pol==_T("U")))		ERP = 10.0*log10(pow(10.0,(atof(ERP_h_dbw)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbw)-attnV)/10.0));
								if(!(hef_flag))
								{
									GE84Heff(atol(AntID),atof(MaxEffHght),h10) ;
									h10[36] = h10[0];
									h1 = Interp2(az0,h10,RAZIM,37) ;
								}
								Em = -999.0;

								d_km1 = 0;			d_km2 = Sradius_km;
								d_km = (d_km1 + d_km2)/2.0;
								while(1)
								{
									reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
									/////////////////////////// h1 //////////////////////
									if(hef_flag)
									{
										if (d_km>=15.0)		h1 = h1_15[az];
										else
										{
											reckon( GRlat,GRlon, 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
											reckon( GRlat,GRlon,     d_km , RAZIM , &lat15km , &lon15km) ;
											h1 = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
										}
									}
									Em = E_P1546_06(GRlat,GRlon,latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									Em = Em - 30.0 + ERP;

									if(fabs(Em-FStrig)<0.1)
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
										fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
										break;
									}
									else if(Em>=FStrig)
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km1 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
											fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
											break;
										}
									}
									else
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km2 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											d_km = d_km - 5.0;
											if(d_km<=0)
											{
												latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
												fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
												break;
											}
										}
									}

								}//while
								progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
								progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
								PeekAndPump();
								((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
							}//for az
				
							CString strY1 = _T("");
							long Ncty1 = QGE06_BCBT_Q5( FStrig,  hR, latContour_deg , lonContour_deg, 360/AZstep ,&strY1) ;
							if(Ncty1>0)
							{
								strY = strY + _T(",") + strY1;		Ncty = Ncty + Ncty1;
							}
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);

						}//if FStrig
					}//for iFStrig
					strY.Delete(0);
				//	if(Ncty>0)
					{
						CString strX , RLONbs,RLATbs;
						Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
						if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);
						else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AS") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, AssocAllotID, SfnID);

						CString strOUT = QGE06_BCBT_A5_1(AssocAllotID) ;
						strX = strX +","+ strOUT;

						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty+1;
						dlgList.m_rowsX = 3;
						dlgList.m_mode = 1;
						dlgList.m_title1 = _T("GE06 BC-BT to FX-LM - Affected Administrations");
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							for(long i=0;i<iplot;i++)
							{
								CString FileName;
								AdmRefID.Replace('/','_');
								FileName.Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,i+1);
								OnDrawVector(FileName);
								if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
							}
						}
					}//if Ncty
				}//Nrow
			}//Pdlg
		}/////////B5_1
		else if((NET==_T("ALS5"))||(NET==_T("ALT5")))	/////////B5_2
		{
			CLoSDLG Pdlg;
			Pdlg.m_overlapDisp = 1;	Pdlg.m_Overlap = 1;	Pdlg.m_FdDisp = 1;	Pdlg.m_Fd = 8;	Pdlg.m_stepDisp = 1;
			Pdlg.m_step = 10;		Pdlg.m_kfactor = 4.0/3.0;		Pdlg.m_RxH = 1000.0;
			Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
			if(Pdlg.DoModal()==IDOK)
			{
				double Sradius_km , FrqRange;
				int OverLapFlag, AZstep = Pdlg.m_step;
				Sradius_km = Pdlg.m_RxH;		FrqRange = Pdlg.m_Fd;		OverLapFlag = Pdlg.m_Overlap;
			
				CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN;
				long c = QGE06_BCBT_A5( AdmRefID,&GeoLatN,&GeoLonN,&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
							&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN , &AntDirN) ;

				double GRlat , GRlon;
				GRlat = atof(GeoLatN);		GRlon = atof(GeoLonN);
				long nST = QGE06_BCBT_B1(GRlat,GRlon,Sradius_km,frq_MHz, BandWidthBS_MHz,FrqRange,OverLapFlag,cty1, NoticeType,Fragment) ;
				QGE06_BCBT_Qy();
				long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
				if(Nrowy>0)
				{
					////////////////////////////////////
					int az0[37];
					for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
					double attH0[37], attV0[37];
					if(AntDirN==_T("D"))
						GE84pattern(atol(AntCatIDN),attH0,attV0,PolN);
					else
						for(int i=0;i<36;i++)
						{
							attH0[i] = 0;		attV0[i] = 0;
						}
					attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
					double attH0[361], attV0[361];
					GE06patternT(atol(AntCatIDN), AntDirN, PolN,attH0,attV0); 

					double latContour_deg[360],lonContour_deg[360];
					double ERP,attnH,attnV,RAZIM , h1 , h10[37], latC_deg,lonC_deg;
					double t = 10, L = 50;
					int ENV = 0, srv = 1, P1546Clangle = 0;
					double kfactor = Pdlg.m_kfactor;

					OnDatabaseStationsindesktop2(GRlat,GRlon);
					double Hasl_ST = LatLon2Hg(GRlat,GRlon);
					double Hasgl_ST = Hasl_ST + atof(AntHeightAGLN);

					double azz, h1_15[360] , lat3km  , lon3km , lat15km , lon15km;
					int progress_num=0;
					CString progress_str, progress_char = _T("I");
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					if(hef_flag)
					{
						for(long i=0;i<(360/AZstep);i++)
						{
							azz = (double)(i*AZstep);
							reckon( GRlat,GRlon,  3.0 , azz , &lat3km  , &lon3km) ;
							reckon( GRlat,GRlon, 15.0 , azz , &lat15km , &lon15km) ;
							h1_15[i] = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}
					}
					CString strY = _T("");
					long Ncty = 0 , iplot = 0;
					progress_num=0;
					CString *FileName;		FileName = new CString[Nrowy];
					AdmRefID.Replace('/','_');

					LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km);
					for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
					{
						CString m_Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
						double FStrig  = atof(GetFld(m_Sely,1));
						double hR  = atof(GetFld(m_Sely,2));
						if(FStrig>-999)
						{
							FileName[iplot].Format("%sReports\\%s_%s_BCBTFXLM%ld.txt",m_AppPath,adm1,AdmRefID,iplot+1);
							FILE *fpOUT = fopen(FileName[iplot],"wt");
							iplot++;
							////////////////////////////////////
							double h2 = hR , d_km, d_km1, d_km2 , Em;

							for(int az = 0; az<(360/AZstep) ; az++)
							{
								RAZIM = (double)(az*AZstep);
						//		attnH = Interp2(az0,attH0,RAZIM,37);		attnV = Interp2(az0,attV0,RAZIM,37);
								attnH = attH0[az*AZstep];	attnV = attV0[az*AZstep];

								if     (PolN==_T("H"))						ERP = atof(ERP_h_dbwN)-attnH;
								else if(PolN==_T("V"))						ERP = atof(ERP_v_dbwN)-attnV;
								else if((PolN==_T("M"))||(PolN==_T("U")))	ERP = 10.0*log10(pow(10.0,(atof(ERP_h_dbwN)-attnH)/10.0) + pow(10.0,(atof(ERP_v_dbwN)-attnV)/10.0));
									
								if(!(hef_flag))
								{
									GE84Heff(atol(AntIDN),atof(MaxEffHghtN),h10) ;
									h10[36] = h10[0];
									h1 = Interp2(az0,h10,RAZIM,37) ;
								}
								Em = -999.0;

								d_km1 = 0;		d_km2 = Sradius_km;
								d_km = (d_km1 + d_km2)/2.0;
								while(1)
								{
									reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
									/////////////////////////// h1 //////////////////////
									if(hef_flag)
									{
										if (d_km>=15.0)		h1 = h1_15[az];
										else
										{
											reckon( GRlat,GRlon, 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
											reckon( GRlat,GRlon,     d_km , RAZIM , &lat15km , &lon15km) ;
											h1 = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
										}
									}
									Em = E_P1546_06(GRlat,GRlon,latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
									Em = Em - 30.0 + ERP;

									if(fabs(Em-FStrig)<0.1)
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
										fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
										break;
									}
									else if(Em>=FStrig)
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km1 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;
											fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
											break;
										}
									}
									else
									{
										if(d_km1 < (d_km2-10.0))
										{
											d_km2 = d_km;
											d_km = (d_km1 + d_km2)/2.0;
										}
										else
										{
											d_km = d_km - 5.0;
											if(d_km<=0)
											{
												latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
												fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[az], latContour_deg[az]);
												break;
											}
										}
									}

								}//while
								progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
								progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
								PeekAndPump();
								((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
							}//for AZ
						
							CString strY1 = _T("");
							long Ncty1 = QGE06_BCBT_Q5( FStrig,  hR, latContour_deg , lonContour_deg, 360/AZstep ,&strY1) ;
							if(Ncty1>0)
							{
								strY = strY + _T(",") + strY1;		Ncty = Ncty + Ncty1;
							}
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);
						}//if FStrig
					}//for iFStrig
					strY.Delete(0);
				//	if(Ncty>0)
					{
//						double pi = 4.0*atan(1.0);
						float RLON   = (float)((pi/180.0)*GRlon), RLAT   = (float)((pi/180.0)*GRlat);
						CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
				//		CString strX,adm1; 	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
						CString strX,adm1 = Cty2AdmGE06(&cty1);

						if(PEC==0)	strX.Format("%s,%s,%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, _T(""), AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);
						else		strX.Format("%s,%s,%s,%s,%d,%s,%s,%s,%g,%s  %s,%s,%s,%s" , _T("AL") ,SiteName, AdmRefID, NoticeType, PEC, AssignCode, cty1,adm1, frq_MHz, _T("---"),_T("---"), Pol, AssocAllotID, SfnID);

						CString strOUT = QGE06_BCBT_A5_2(AdmRefID) ;
						strX = strX +","+ strOUT;

						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty+1;
						dlgList.m_rowsX = 3;
						dlgList.m_mode = 1;
						dlgList.m_title1 = _Z("GE06 BC-BT to FX-LM - Affected Administrations");
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							for(long i=0;i<iplot;i++)
							{
								OnDrawVector(FileName[i]);
								if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName[i]);
							}
						}
						delete [] FileName;
					}//if Ncty
				}//if Nrowy
			}//Pdlg
		}/////////B5_2
	}//m_Selx
	Set_STtable_Default();
	EndWaitCursor();
}

CString CSMS4DCView::QGE06_FXMBCBT_QTx(BOOL *hef_flag) 
{
	CString Selx = _T("");
	CString CDataBaseSTR;
//	CDataBaseSTR = _T("SELECT * FROM STtableGE06 WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB' Or (STTP)='ML') AND (((TXfreq)>=174 And (TXfreq)<=230) Or ((TXfreq)>=470 And (TXfreq)<=862)));");
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB' Or (STTP)='ML') AND (((TXfreq)>=174 And (TXfreq)<=230) Or ((TXfreq)>=470 And (TXfreq)<=862)));") , m_qSTtableGE06);
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = TRUE;
//	datadlg.m_Title = _T("Wanted Assignment/Allotment");
	datadlg.m_Title = _T("Wanted FXM Station");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
		{
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
			*hef_flag = datadlg.m_Heff1;
		}
		else
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
		}

	}
	return Selx;
}

long CSMS4DCView::QGE06_FXMBCBT_Q1(long IDst,CString *zone) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
	long n = 0;
	CString  zone0 = _T("");
//	tbl.Format(_T("SELECT AreaOfTrans FROM STtableGE06 WHERE (((IDst)=%ld));"), IDst);
	tbl.Format(_T("SELECT AreaOfTrans FROM %s WHERE (((IDst)=%ld));"), m_qSTtableGE06 , IDst);

	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		rs.GetFieldValue(_T("AreaOfTrans"),zone0);
		if(zone0.GetLength()==1)			zone0 = zone0 + _T("  ");
		else if(zone0.GetLength()==2)		zone0 = zone0 + _T(" ");
		*zone = zone0;
		n = Ctry2Point(zone0); 
	}
	rs.Close();	DB1.Close();
	return n;
}
void CSMS4DCView::QGE06_FXMBCBT_Q2(long n1,CString zone, double *lat,double *lon) 
{
	if(n1>0)
	{
		float *CRDARR0;	CRDARR0 = new float[2*n1];
		unsigned char CTYVEK[4]={""}, BCILR;
		strcpy((char *)CTYVEK,zone);
		long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;
		float RLONLL, RLATLL, RLONUR, RLATUR , DENS=0;
		GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
		GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	
		long j = 0;
		while(!NOMORE)
		{
			GEOLIW( &ITYPE, CRDARR0, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
			if(NOMORE)	break;
			for(long p=0;p<NRCRD;p++)
			{
				lat[j] = CRDARR0[2*p+1];			//ITYPE=2  Deg.
				lon[j] = CRDARR0[2*p];
				j++;

			}//end for
		}//end while
		delete [] CRDARR0;
	}//if n1>0
}

void CSMS4DCView::OnCoordinationGe06Fxlm2bcbtTxfxlm() 
{
	BeginWaitCursor();
	BOOL hef_flag;
	CString Selx = QGE06_FXMBCBT_QTx(&hef_flag) ;
	if(Selx.GetLength()>0)
	{
		CString IDst = GetFld(Selx,1),		SiteName = GetFld(Selx,2),		lat = GetFld(Selx,3),
				lon = GetFld(Selx,4),		Frequency = GetFld(Selx,6),		Pol = GetFld(Selx,13),
				sttp = GetFld(Selx,18),		StType = GetFld(Selx,29),		AntID = GetFld(Selx,20),
				AntCatID = GetFld(Selx,30),	AntDir = GetFld(Selx,31),		MaxEffHght = GetFld(Selx,32),
				Hagl_ST = GetFld(Selx,5),	AdmRefID = GetFld(Selx,33),		Emission = GetFld(Selx,19);
		double	power = atof(GetFld(Selx,7));	power = 10.0*log10(power) - 2.15;	//dBw ERP
		double	radius = atof(GetFld(Selx,22)) , BandW_kHz = Emission2NBW(Emission);

//		double pi = 4.0*atan(1.0);
		float RLON   = (float)((pi/180.0)*atof(lon)), RLAT   = (float)((pi/180.0)*atof(lat));
	//	CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
		CString cty1 = GetFld(Selx,25);
//		if(cty1.GetLength()==1)			cty1 = cty1 + _T("  ");
//		else if(cty1.GetLength()==2)	cty1 = cty1 + _T(" ");
//		CString adm1;	GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
		CString adm1 = Cty2AdmGE06(&cty1);

		if(((sttp==_T("FX"))||(sttp==_T("FB")))&&(StType!=_T("Typical")))	//////////////////C1
		{
			CLoSDLG Pdlg;
			Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0;	Pdlg.m_stepDisp = 1; Pdlg.m_step = 10;
			Pdlg.m_title  = _Z("Model Parameters");			Pdlg.m_title1 = _Z("Search Radius(km)");
			if(Pdlg.DoModal()==IDOK)
			{
				if(MaxEffHght.GetLength()==0)  MaxEffHght = _T("37.5");
				int AZstep = Pdlg.m_step;
				double GRlat , GRlon , frq_MHz;
				GRlat = atof(lat);		GRlon = atof(lon);		frq_MHz = atof(Frequency);
				double FStrig;
				if	   ((frq_MHz>=174)&&(frq_MHz<=230))		FStrig = 10;
				else if((frq_MHz>=470)&&(frq_MHz<582))		FStrig = 18;
				else if((frq_MHz>=582)&&(frq_MHz<718))		FStrig = 20;
				else if((frq_MHz>=718)&&(frq_MHz<=862))		FStrig = 22;
				////////////////////////////////////
				int az0[37];
				for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
				double attH0[37], attV0[37];
				if(AntDir==_T("D"))
					GE84pattern(atol(AntCatID),attH0,attV0,Pol);
				else
					for(int i=0;i<36;i++)
					{
						attH0[i] = 0;		attV0[i] = 0;
					}
				attH0[36] = attH0[0];		attV0[36] = attV0[0];
*/
				double attH0[361], attV0[361];
				GE06patternT(atol(AntCatID), AntDir, Pol,attH0,attV0); 

				double latContour_deg[360],lonContour_deg[360];
				double ERP,attnH,attnV,RAZIM, h1 , h10[37], latC_deg,lonC_deg;
				double t = 1, h2 = 10, L = 50;
				int ENV = 0, srv = 1, P1546Clangle = 0;
				double kfactor = Pdlg.m_kfactor;
				double Sradius_km = Pdlg.m_RxH;

				OnDatabaseStationsindesktop2(GRlat,GRlon);
				double Hasl_ST = LatLon2Hg(GRlat,GRlon);
				double Hasgl_ST = Hasl_ST + atof(Hagl_ST);

				double lat3km  , lon3km , lat15km , lon15km, azz, h1_15[360];
				int progress_num=0;
				CString progress_str, progress_char = _T("I");
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
				if(hef_flag)
				{
					for(long i=0;i<(360/AZstep);i++)
					{
						azz = (double)(i*AZstep);
						reckon( GRlat,GRlon,  3.0 , azz , &lat3km  , &lon3km) ;
						reckon( GRlat,GRlon, 15.0 , azz , &lat15km , &lon15km) ;
						h1_15[i] = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);

						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					}
				}
				double d_km ,d_km1,d_km2, Em;
				LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 

				progress_num=0;
				for(int az = 0; az<(360/AZstep) ; az++)
				{
					RAZIM = (double)(az*AZstep);
				//	attnH = Interp2(az0,attH0,RAZIM,37) ;		attnV = Interp2(az0,attV0,RAZIM,37) ;
					attnH = attH0[az*AZstep];	attnV = attV0[az*AZstep];

					if     (Pol==_T("H"))						ERP = power - attnH;
					else if(Pol==_T("V"))						ERP = power - attnV;
					else if((Pol==_T("M"))||(Pol==_T("U")))		ERP = 10.0*log10(pow(10.0,(power-3.0-attnH)/10.0) + pow(10.0,(power-3.0-attnV)/10.0));
					if(!(hef_flag))
					{
						GE84Heff(atol(AntID),atof(MaxEffHght),h10) ;
						h10[36] = h10[0];
						h1 = Interp2(az0,h10,RAZIM,37) ;
					}
					Em = -999.0;

					d_km1 = 0;		d_km2 = Sradius_km;
					d_km = (d_km1 + d_km2)/2.0;
					while(1)
					{
						reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
						/////////////////////////// h1 //////////////////////
						if(hef_flag)
						{
							if (d_km>=15.0)		h1 = h1_15[az];
							else
							{
								reckon( GRlat,GRlon, 0.2*d_km , RAZIM , &lat3km  , &lon3km) ;
								reckon( GRlat,GRlon,     d_km , RAZIM , &lat15km , &lon15km) ;
								h1 = Hasgl_ST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km,120);
							}
						}
						Em = E_P1546_06(GRlat,GRlon,latC_deg,lonC_deg, h1, Hasgl_ST, frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
						Em = Em - 30.0 + ERP;

						if(fabs(Em-FStrig)<0.1)
						{
							latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
						}
						else if(Em>=FStrig)
						{
							if(d_km1 < (d_km2-10.0))
							{
								d_km1 = d_km;
								d_km = (d_km1 + d_km2)/2.0;
							}
							else
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
							}
						}
						else
						{
							if(d_km1 < (d_km2-10.0))
							{
								d_km2 = d_km;
								d_km = (d_km1 + d_km2)/2.0;
							}
							else
							{
								d_km = d_km - 5.0;
								if(d_km<=0)
								{
									latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
									break;
								}
							}
						}

					}//while
					progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

				}//for
				long Ncty;		int mode = 2;
				CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty , mode, h2); 

				CString strX , RLONbs,RLATbs;
				Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
				if(StType==_T("Typical"))	strX.Format("%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%lf,%lf" ,SiteName, AdmRefID, sttp, _T("TP"), cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, BandW_kHz, power);
				else	 					strX.Format("%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%lf,%lf" ,SiteName, AdmRefID, sttp, _T("Tx"), cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, BandW_kHz, power);

				CGE06repDLG1 dlgList;
				dlgList.m_dataX = strX;
				dlgList.m_dataY = strY;
				dlgList.m_rowsY = Ncty+1;
				dlgList.m_title1 = _Z("GE06 FX-LM to BC-BT - Affected Administrations");
				dlgList.m_title2 = _Z("Wanted Tx Station :");
				dlgList.m_mode = mode;
				dlgList.m_GoogleFlag = m_GoogleFlag;
				if(dlgList.DoModal()==IDOK)
				{
					CString FileName;
					AdmRefID.Replace('/','_');
					FileName.Format("%sReports\\%s_%s_FXLMBCBT.txt",m_AppPath,adm1,AdmRefID);
					FILE *fpOUT = fopen(FileName,"wt");
					for( i=0;i<(360/AZstep);i++)
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
					fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
					fclose(fpOUT);
					OnDrawVector(FileName);
					if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
				}
			}//Pdlg
		}//////////////////C1
		else if(  ((sttp==_T("ML")) && (StType!=_T("Typical")))||(((sttp==_T("FX"))||(sttp==_T("FB")))&&(StType==_T("Typical")))  )		//////////////C2
		{
			CLoSDLG Pdlg;
			Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0;	Pdlg.m_stepDisp = 1;	Pdlg.m_step = 10;
			Pdlg.m_title  = _Z("Model Parameters");		Pdlg.m_title1 = _Z("Search Radius(km)");
			if(Pdlg.DoModal()==IDOK)
			{
				int AZstep = Pdlg.m_step;
				double GRlat , GRlon , frq_MHz;
				frq_MHz = atof(Frequency);
				CString zone0;
				long m1 , n1 = QGE06_FXMBCBT_Q1(atol(IDst),&zone0) ;
				double *latCi=NULL;		double *lonCi=NULL;	double *Hasgl_ST=NULL;
				if(n1==0)
				{
					GRlat = atof(lat);		GRlon = atof(lon);
					int AZstep1 = 10;
					m1 = 360/AZstep1;
					latCi = new double[m1];		lonCi = new double[m1];		Hasgl_ST = new double[m1];
					double Hagla = atof(Hagl_ST);
					for(long az1 = 0; az1<m1 ; az1++)
					{
						double RAZIM1 = (double)(az1*AZstep1);
						reckon(GRlat,GRlon,radius,RAZIM1,&latCi[az1],&lonCi[az1]) ;
						OnDatabaseStationsindesktop2(latCi[az1],lonCi[az1]);
						Hasgl_ST[az1] = Hagla + LatLon2Hg(latCi[az1],lonCi[az1]);
					}
				}
				else
				{
					m1 = n1;
					latCi = new double[m1];		lonCi = new double[m1];		Hasgl_ST = new double[m1];
					QGE06_FXMBCBT_Q2(m1,zone0, latCi,lonCi) ;
					CP154606_Functions CP154606;
					CP154606.GrPointT(latCi,lonCi , m1 , &GRlat , &GRlon);
					double Hagla = atof(Hagl_ST);
					for(long az1 = 0; az1<m1 ; az1++)
					{
						OnDatabaseStationsindesktop2(latCi[az1],lonCi[az1]);
						Hasgl_ST[az1] = Hagla + LatLon2Hg(latCi[az1],lonCi[az1]);
					}
				}
				double FStrig;
				if	   ((frq_MHz>=174)&&(frq_MHz<=230))		FStrig = 10;
				else if((frq_MHz>=470)&&(frq_MHz<582))		FStrig = 18;
				else if((frq_MHz>=582)&&(frq_MHz<718))		FStrig = 20;
				else if((frq_MHz>=718)&&(frq_MHz<=862))		FStrig = 22;
				////////////////////////////////////
				int az0[37];
				for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
				double attH0[37], attV0[37];
				if(AntDir==_T("D"))
					GE84pattern(atol(AntCatID),attH0,attV0,Pol);
				else
					for(int i=0;i<36;i++)
					{
						attH0[i] = 0;	attV0[i] = 0;
					}
				attH0[36] = attH0[0];	attV0[36] = attV0[0];
*/
				double attH0[361], attV0[361];
				GE06patternT(atol(AntCatID), AntDir, Pol,attH0,attV0); 

				double latContour_deg[360],lonContour_deg[360];
				double ERP,attnH,attnV,RAZIM , h1, latC_deg,lonC_deg;

				double t = 1, h2 = 10, L = 50;
				int ENV = 0, srv = 1, P1546Clangle = 0;
				double kfactor = Pdlg.m_kfactor;
				double Sradius_km = Pdlg.m_RxH;
				OnDatabaseStationsindesktop2(GRlat,GRlon);

				LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 

				double lat3km  , lon3km , lat15km , lon15km;
				int progress_num=0;
				CString progress_str, progress_char = _T("I");
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

				double d_km ,d_km0,d_km1,d_km2, Em , latCross, lonCross, D_1000, RAZIM1 , Em_max;
				long az,az1;
				BOOL ss;

				for( az = 0; az<(360/AZstep) ; az++)
				{
					RAZIM = (double)(az*AZstep);
					Em = -999.0;

					reckon(GRlat,GRlon,Sradius_km,RAZIM,&latC_deg,&lonC_deg) ;
					ss = CrossPoint(GRlat,GRlon,latC_deg,lonC_deg , latCi,lonCi,m1 , &latCross,&lonCross) ;
				
					d_km0 = Distance_km(GRlat,GRlon,latCross, lonCross) ;
					d_km1 = d_km0;		d_km2 = Sradius_km;
					d_km = (d_km1 + d_km2)/2.0;

					while(1)
					{
						reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
						Em_max = -99999;
					
						for( az1 = 0; az1<m1 ; az1++)
						{
							D_1000 = Distance_km(latCi[az1],lonCi[az1],latC_deg,lonC_deg) ;
							if(D_1000<(d_km-d_km0/2.0))
							{
								RAZIM1 = Azimuth_Deg(latCi[az1],lonCi[az1],latC_deg,lonC_deg) ;
							//	attnH = Interp2(az0,attH0,RAZIM1,37);	attnV = Interp2(az0,attV0,RAZIM1,37);
								attnH = attH0[(int)RAZIM1];	attnV = attV0[(int)RAZIM1];

								if     (Pol==_T("H"))						ERP = power - attnH;
								else if(Pol==_T("V"))						ERP = power - attnV;
								else if((Pol==_T("M"))||(Pol==_T("U")))		ERP = 10.0*log10(pow(10.0,(power-3.0-attnH)/10.0) + pow(10.0,(power-3.0-attnV)/10.0));

								if (d_km>=15.0)	
								{
									reckon(latCi[az1],lonCi[az1],  3.0 , RAZIM1 , &lat3km  , &lon3km) ;
									reckon(latCi[az1],lonCi[az1], 15.0 , RAZIM1 , &lat15km , &lon15km) ;
									h1 = Hasgl_ST[az1] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km , 120);
								}
								else
								{
									reckon(latCi[az1],lonCi[az1], 0.2*d_km , RAZIM1 , &lat3km  , &lon3km) ;
									reckon(latCi[az1],lonCi[az1],     d_km , RAZIM1 , &lat15km , &lon15km) ;
									h1 = Hasgl_ST[az1] - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km, 120);
								}

 								Em = E_P1546_06(latCi[az1],lonCi[az1],latC_deg,lonC_deg, h1, Hasgl_ST[az1], frq_MHz, kfactor, t,h2, ENV,srv,L,P1546Clangle);
								Em = Em - 30.0 + ERP;
								Em_max = max(Em_max , Em);
							}
						}
						Em = Em_max;

						if(fabs(Em-FStrig)<0.1)
						{
							latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
						}
						else if(Em>=FStrig)
						{
							if(d_km1 < (d_km2-10.0))
							{
								d_km1 = d_km;
								d_km = (d_km1 + d_km2)/2.0;
							}
							else
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
							}
						}
						else
						{
							if(d_km1 < (d_km2-10.0))
							{
								d_km2 = d_km;
								d_km = (d_km1 + d_km2)/2.0;
							}
							else
							{
								d_km = d_km - 5.0;
								if(d_km<=d_km0)
								{
									latContour_deg[az] = latCross;	lonContour_deg[az] = lonCross;
									break;
								}
							}
						}

					}//while
					progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
				}//for
				long Ncty;		int mode = 2;
				CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty , mode, h2); 

				CString strX , RLONbs,RLATbs;
				Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
 				strX.Format("%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%lf,%lf" ,SiteName, AdmRefID, sttp, _T("Tx"), cty1,adm1, frq_MHz, RLONbs,RLATbs, Pol, BandW_kHz, power);

				CGE06repDLG1 dlgList;
				dlgList.m_dataX = strX;
				dlgList.m_dataY = strY;
				dlgList.m_rowsY = Ncty+1;
				dlgList.m_title1 = _Z("GE06 FX-LM to BC-BT - Affected Administrations");
				dlgList.m_title2 = _Z("Wanted Tx Station :");
				dlgList.m_mode = mode;
				dlgList.m_GoogleFlag = m_GoogleFlag;
				if(dlgList.DoModal()==IDOK)
				{
					CString FileName;
					AdmRefID.Replace('/','_');
					FileName.Format("%sReports\\%s_%s_FXLMBCBT.txt",m_AppPath,adm1,AdmRefID);
					FILE *fpOUT = fopen(FileName,"wt");
					for( i=0;i<(360/AZstep);i++)
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
					fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
					fclose(fpOUT);
					OnDrawVector(FileName);
					if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);	
				}
				delete [] latCi; delete [] lonCi; delete [] Hasgl_ST;
			}//Pdlg
		}//////////////////C2
	}//selx
	Set_STtable_Default();
	EndWaitCursor();
}

CString CSMS4DCView::QGE06_FXMBCBT_QRx(BOOL *hef_flag) 
{
	CString CDataBaseSTR , Selx = _T("");
//	CDataBaseSTR = _T("SELECT * FROM STtableGE06 WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB' Or (STTP)='ML') AND ((StType)<>'Typical'));");
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB' Or (STTP)='ML') AND ((StType)<>'Typical'));") , m_qSTtableGE06);
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = FALSE;
//	datadlg.m_Title = _T("Wanted Assignment/Allotment");
	datadlg.m_Title = _T("Wanted FXM Station");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
		{
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
			*hef_flag = datadlg.m_Heff1;
		}
		else
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
		}
	}
	return Selx;
}

int CSMS4DCView::QGE06_FXMBCBT_Q3(long IDst ,double *GRlat, double *GRlon) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
	int n = 0;
	CString  strlat = _T("") , strlon = _T("");
	double lat[7], lon[7];
	lat[0]=lat[1]=lat[2]=lat[3]=lat[4]=lat[5]=-999;
	lon[0]=lon[1]=lon[2]=lon[3]=lon[4]=lon[5]=-999;

//	tbl.Format(_T("SELECT Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, Link_TX WHERE (((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.TXID)=%ld) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("MULTIPOINT"));
	tbl.Format(_T("SELECT Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, %s WHERE (((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.TXID)=%ld) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX , IDst, _T("MULTIPOINT"));
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
					
		rs.GetFieldValue(_T("lat1"),strlat);	rs.GetFieldValue(_T("lon1"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat2"),strlat);	rs.GetFieldValue(_T("lon2"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat3"),strlat);	rs.GetFieldValue(_T("lon3"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat4"),strlat);	rs.GetFieldValue(_T("lon4"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat5"),strlat);	rs.GetFieldValue(_T("lon5"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat6"),strlat);	rs.GetFieldValue(_T("lon6"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
	}
	rs.Close();	DB1.Close();
	if(n>0)
	{
		double GRlat0 , GRlon0;

		lat[n] = lat[0];	lon[n] = lon[0];
		CP154606_Functions CP154606;
		CP154606.GrPointT(lat,lon , n+1 , &GRlat0 , &GRlon0);
		*GRlat = GRlat0;	*GRlon = GRlon0;
	}
	return n;
}

long CSMS4DCView::QGE06_FXMBCBT_Q4(long IDst ,double *GRlat, double *GRlon) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	int i = 0;
	CString  zone0 = _T("");
//	tbl.Format(_T("SELECT Link.zone FROM Link, Link_TX WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("ZONE"));
	tbl.Format(_T("SELECT Link.zone FROM Link, %s WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX,IDst, _T("ZONE"));
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();		
		rs.GetFieldValue(_T("zone"),zone0);
		i++;
	}
	rs.Close();		DB1.Close();
	long n = 0;
	if(i>0)
	{
		if(zone0.GetLength()==1)		zone0 = zone0 + _T("  ");
		else if(zone0.GetLength()==2)	zone0 = zone0 + _T(" ");

		n = Ctry2Point(zone0); 
		double *lat;  lat = new double[n];
		double *lon;  lon = new double[n];
		float *CRDARR0;	CRDARR0 = new float[2*n];

		unsigned char CTYVEK[4]={""}, BCILR;
		strcpy((char *)CTYVEK,zone0);
		long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;
		float RLONLL, RLATLL, RLONUR, RLATUR , DENS=0;
		GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
		GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	
		long j = 0;
		while(!NOMORE)
		{
			GEOLIW( &ITYPE, CRDARR0, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
			if(NOMORE)	break;
			for(long p=0;p<NRCRD;p++)
			{
				lat[j] = CRDARR0[2*p+1];			//ITYPE=2  Deg.
				lon[j] = CRDARR0[2*p];
				j++;

			}//end for
		}//end while
		delete [] CRDARR0;
		if(n>0)
		{
			double GRlat0 , GRlon0;
			CP154606_Functions CP154606;
			CP154606.GrPointT(lat,lon , n , &GRlat0 , &GRlon0);
			*GRlat = GRlat0;	*GRlon = GRlon0;
		}
		delete [] lat;		delete [] lon;
	}//if i>0
	return n;
}

int CSMS4DCView::QGE06_FXMBCBT_Q5(long IDst ,double *GRlat, double *GRlon) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
	int i = 0;
	CString  str = _T("");
//	tbl.Format(_T("SELECT Link.RecLat, Link.RecLon, Link.Radius FROM Link, Link_TX WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("CIRCLE"));
	tbl.Format(_T("SELECT Link.RecLat, Link.RecLon, Link.Radius FROM Link, %s WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX , IDst, _T("CIRCLE"));
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		rs.GetFieldValue(_T("RecLat"),str);		*GRlat = atof(str);
		rs.GetFieldValue(_T("RecLon"),str);		*GRlon = atof(str);
		i++;
	}
	rs.Close();	DB1.Close();
	return i;
}

int CSMS4DCView::QGE06_FXMBCBT_Q6(long IDst, double FrqR, double FrqT, double lat, double lon ,CString sttp,CString BCBT,CString SysType1, CString SysType2,double RPR) 
{
	CString  SQL1 , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);

//	SQL1 = _T("DELETE IDst, FStrig, hR,Freq_ter, STTP, GeoType FROM FStrig_hR;");	//950909
	SQL1 = _T("DELETE FROM FStrig_hR;");											//950909
	DB1.ExecuteSQL(SQL1);

	double	BandWidthBS_MHz;
	CString NoticeType, Fragment;

	if	   (BCBT == _T("T-DAB"))	{Fragment = _T("GE06D"); NoticeType = _T("GS1");	BandWidthBS_MHz = 1.536;}
	else if(BCBT == _T("DVB 7MHz"))	{Fragment = _T("GE06D"); NoticeType = _T("GT1");	BandWidthBS_MHz = 7;	}
	else if(BCBT == _T("DVB 8MHz"))	{Fragment = _T("GE06D"); NoticeType = _T("GT1");	BandWidthBS_MHz = 8;	}
	else if(BCBT == _T("ANA 7MHz"))	{Fragment = _T("GE06A"); 							BandWidthBS_MHz = 7;	}
	else if(BCBT == _T("ANA 8MHz"))	{Fragment = _T("GE06A");							BandWidthBS_MHz = 8;	}

//double RPR = 0;
//if(Fragment == _T("GE06A"))
//	RPR = CP154606.ATV2FXM_RPR(Freq_W,Band_W,sttp_W,freq_vcarr_I,freq_scarr_I,TV_COLOR_I,TV_SYS_I); 
 
	int n = 0;
	CP154606_Functions CP154606;
	double FStrig[2],hR[2];

	double freq_ter0 , GRlat0 , GRlon0;
	if(((sttp==_T("FX"))||(sttp==_T("FB")))&&(((FrqR>=174)&&(FrqR<=230))||((FrqR>=470)&&(FrqR<=862))))	//point
	{
		freq_ter0 = FrqR;
		GRlat0 = lat;			GRlon0 = lon;

		int nFStrig = CP154606.AP2_FStrigT(sttp, freq_ter0,SysType1, SysType2, freq_ter0, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
		for(int i=0;i<nFStrig;i++)
		{
			SQL1.Format(_T("SELECT %ld,%0.4lf,%0.4lf,%0.4lf,\'%s\',\'%s\',%lf,%lf,%d "), IDst, FStrig[i], hR[i], freq_ter0, sttp, _T("POINT"),GRlat0,GRlon0,1);
			SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp,ant) ") + SQL1;
			DB1.ExecuteSQL(SQL1);
			n++;
		}
	}
	if((sttp==_T("ML"))&&(((FrqR>=174)&&(FrqR<=230))||((FrqR>=470)&&(FrqR<=862))))
	{
		freq_ter0 = FrqR;
		CString zone;
		long m = QGE06_FXMBCBT_Q1((IDst), &zone) ;
		if(m==0)										//CIRCLE
		{
			GRlat0 = lat;		GRlon0 = lon;
			int nFStrig = CP154606.AP2_FStrigT(sttp, freq_ter0,SysType1, SysType2, freq_ter0, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
			for(int i=0;i<nFStrig;i++)
			{
				SQL1.Format(_T("SELECT %ld,%0.4lf,%0.4lf,%0.4lf,\'%s\',\'%s\',%lf,%lf,%d "), IDst, FStrig[i], hR[i], freq_ter0, sttp, _T("CIRCLE"),GRlat0,GRlon0,0);
				SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp,ant) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
				n++;
			}
		}
		else											//ZONE
		{
			double *latCi;		latCi = new double[m];
			double *lonCi;		lonCi = new double[m];
			QGE06_FXMBCBT_Q2(m,zone, latCi,lonCi) ;
			CP154606_Functions CP154606;
			CP154606.GrPointT(latCi,lonCi , m , &GRlat0 , &GRlon0);
			delete [] latCi;		delete [] lonCi;

			int nFStrig = CP154606.AP2_FStrigT(sttp, freq_ter0,SysType1, SysType2, freq_ter0, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
			for(int i=0;i<nFStrig;i++)
			{
				SQL1.Format(_T("SELECT %ld,%0.4lf,%0.4lf,%0.4lf,\'%s\',\'%s\',%lf,%lf,%d "), IDst, FStrig[i], hR[i], freq_ter0, sttp, _T("ZONE"),GRlat0,GRlon0,0);
				SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp,ant) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
				n++;
			}
		}
	}
	if((sttp==_T("FX"))&&(((FrqT>=174)&&(FrqT<=230))||((FrqT>=470)&&(FrqT<=862))))	//MPOINT
	{
		int m = QGE06_FXMBCBT_Q3((IDst) ,&GRlat0 , &GRlon0) ;
		if(m>0)
		{
			freq_ter0 = FrqT;

			int nFStrig = CP154606.AP2_FStrigT(sttp, freq_ter0,SysType1, SysType2, freq_ter0, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
			for(int i=0;i<nFStrig;i++)
			{
				SQL1.Format(_T("SELECT %ld,%0.4lf,%0.4lf,%0.4lf,\'%s\',\'%s\',%lf,%lf,%d "), IDst, FStrig[i], hR[i], freq_ter0, sttp, _T("MPOINT"),GRlat0,GRlon0,0);
				SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp,ant) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
				n++;
			}
		}
	}
	if((sttp==_T("FB"))&&(((FrqT>=174)&&(FrqT<=230))||((FrqT>=470)&&(FrqT<=862))))
	{
		long n1 = QGE06_FXMBCBT_Q4((IDst) ,&GRlat0 , &GRlon0) ;	//ZONE
		if(n1>0)
		{
			freq_ter0 = FrqT;

			int nFStrig = CP154606.AP2_FStrigT(_T("ML"), freq_ter0,SysType1, SysType2, freq_ter0, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
			for(int i=0;i<nFStrig;i++)
			{
				SQL1.Format(_T("SELECT %ld,%0.4lf,%0.4lf,%0.4lf,\'%s\',\'%s\',%lf,%lf,%d "), IDst, FStrig[i], hR[i], freq_ter0, sttp, _T("ZONE"),GRlat0,GRlon0,0);
				SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp,ant) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
				n++;
			}
		}
		long n2 = QGE06_FXMBCBT_Q5((IDst) ,&GRlat0 , &GRlon0) ;	//CIRCLE
		if(n2>0)
		{
			freq_ter0 = FrqT;

			int nFStrig = CP154606.AP2_FStrigT(_T("ML"), freq_ter0,SysType1, SysType2, freq_ter0, BandWidthBS_MHz, NoticeType, Fragment, FStrig,hR,RPR) ;
			for(int i=0;i<nFStrig;i++)
			{
				SQL1.Format(_T("SELECT %ld,%0.4lf,%0.4lf,%0.4lf,\'%s\',\'%s\',%lf,%lf,%d "), IDst, FStrig[i], hR[i], freq_ter0, sttp, _T("CIRCLE"),GRlat0,GRlon0,0);
				SQL1 = _T("INSERT INTO FStrig_hR (IDst, FStrig, hR, Freq_ter, STTP, GeoType,latp,lonp,ant) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
				n++;
			}
		}
	}
	DB1.Close();
	return n;
}

void CSMS4DCView::OnCoordinationGe06Fxlm2bcbtRxfxlm() 
{
	BeginWaitCursor();
	BOOL hef_flag;
	CString Selx = QGE06_FXMBCBT_QRx(&hef_flag) ;
	if(Selx.GetLength()>0)
	{
		CString	IDst = GetFld(Selx,1),		SiteName = GetFld(Selx,2),	lat = GetFld(Selx,3),
				lon = GetFld(Selx,4),		Pol = GetFld(Selx,13),		sttp = GetFld(Selx,18),
				AdmRefID = GetFld(Selx,33),	Emission = GetFld(Selx,19),	SysType1 = GetFld(Selx,26),
				SysType2 = GetFld(Selx,27),	cty1 = GetFld(Selx,25),		AntCatID = GetFld(Selx,30),
				AntDir = GetFld(Selx,31);

		int az0[37];
		for(int i=0;i<=36;i++)		az0[i] = 10*i;
/*
		double attH0[37], attV0[37];
		if(AntDir==_T("D"))
			GE84pattern(atol(AntCatID),attH0,attV0,Pol);
		else
			for(int i=0;i<36;i++)
			{
				attH0[i] = 0;		attV0[i] = 0;
			}
		attH0[36] = attH0[0];	attV0[36] = attV0[0];
*/
		double attH0[361], attV0[361];
		GE06patternT(atol(AntCatID), AntDir, Pol,attH0,attV0); 

		double	FrqT = atof(GetFld(Selx,6)),	FrqR = atof(GetFld(Selx,21)),
				BandW_kHz = Emission2NBW(Emission);

//		double pi = 4.0*atan(1.0);
		float RLON   = (float)((pi/180.0)*atof(lon)), RLAT   = (float)((pi/180.0)*atof(lat));
	//	CString cty1("");	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;

//		if(cty1.GetLength()==1)			cty1 = cty1 + _T("  ");
//		else if(cty1.GetLength()==2)	cty1 = cty1 + _T(" ");
//		CString adm1;		GEOCTYA((BYTE *)cty1.GetBufferSetLength(3), (BYTE *)adm1.GetBufferSetLength(3));
		CString adm1 = Cty2AdmGE06(&cty1);

		double freq_ter , GRlat , GRlon, FStrig,hR;
		double h1 = 600 , power = 50;		//dBw ERP
///////////////////////////////////////////////////////
		CLoSDLG Pdlg;
		Pdlg.m_kfactor = 4.0/3.0;	Pdlg.m_RxH = 1000.0;	Pdlg.m_stepDisp = 1;	Pdlg.m_step = 10;
		Pdlg.m_title  = _Z("Model Parameters");	Pdlg.m_title1 = _Z("Search Radius(km)"); Pdlg.m_bcbtDisp = 1; Pdlg.m_bcbt = _T("DVB 8MHz");

		Pdlg.m_nFter = QGE06_FXMBCBT_Q6Fter(atol(IDst), FrqR, FrqT, sttp) ;
		
		if(Pdlg.DoModal()==IDOK)
		{
			int AZstep = Pdlg.m_step;
			////////////////////////////////////
			int AntDisc = Pdlg.m_AntDisc;
			CString BCBT = Pdlg.m_bcbt;
			double RPR = Pdlg.m_RPR;
			QGE06_FXMBCBT_Q6(atol(IDst), FrqR, FrqT, atof(lat), atof(lon) ,sttp,BCBT,SysType1, SysType2, RPR);

			QGE06_BCBT_Qy(1);
			long Nrowy = ((CSMS4DCApp *)AfxGetApp())->Nrow;
			if(Nrowy>0)
			{
				double latC_deg,lonC_deg;
				double latContour_deg[360],lonContour_deg[360];
				double t = 10, L = 50;
				int ENV = 0, srv = 1, P1546Clangle = 0;
				double kfactor = Pdlg.m_kfactor;
				double Sradius_km = Pdlg.m_RxH;
				double d_km ,d_km1 ,d_km2 , Em , RAZIM ,ERP = power;
				int progress_num=0;
				CString progress_str, progress_char = _T("I");
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
				for(int iFStrig = 0;iFStrig<Nrowy;iFStrig++)
				{
					CString Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iFStrig];
					FStrig  = atof(GetFld(Sely,1));
					if(FStrig>-999)
					{
						hR = atof(GetFld(Sely,2));		freq_ter = atof(GetFld(Sely,3));
						GRlat = atof(GetFld(Sely,4)); 	GRlon = atof(GetFld(Sely,5));
						int ant = atof(GetFld(Sely,7));
				
						LoadMap_IDWMpr(4,GRlat,GRlon , Sradius_km); 

						for(int az = 0; az<(360/AZstep) ; az++)
						{
							RAZIM = (double)(az*AZstep);
						///////////////////////////////////////////////////////
							double ATTNantrec = 0, PolAntDisc = 0;
							if((AntDisc==1)&&(ant==1))
							{
						//		if     (Pol==_T("H"))		ATTNantrec = Interp2(az0,attH0,RAZIM,37);
						//		else if(Pol==_T("V"))		ATTNantrec = Interp2(az0,attV0,RAZIM,37);
								if     (Pol==_T("H"))		ATTNantrec = attH0[az*AZstep];
								else if(Pol==_T("V"))		ATTNantrec = attV0[az*AZstep];
								PolAntDisc = QGE06_XPD(atol(AntCatID)); 
							}
						///////////////////////////////////////////////////////////
							Em = -999.0;
							d_km1 = 0;	d_km2 = Sradius_km;
							d_km = (d_km1 + d_km2)/2.0;

							while(1)
							{
								reckon(GRlat,GRlon,d_km,RAZIM,&latC_deg,&lonC_deg) ;
						//		Em = E_P1546_06(latC_deg,lonC_deg ,GRlat,GRlon, h1, 0, freq_ter, kfactor, t,hR, ENV,srv,L,P1546Clangle);
								Em = E_P154606AL_hR(latC_deg,lonC_deg ,GRlat,GRlon, h1, freq_ter, t, hR, ENV);
					
								Em = Em - 30.0 + ERP;

								if     ((Pol==_T("H"))||(Pol==_T("V")))	Em = 10.0*log10(pow(10.0 , (Em-ATTNantrec)/10.0) + pow(10.0 , (Em-PolAntDisc)/10.0));
								else if((Pol==_T("M"))||(Pol==_T("U")))	Em = 10.0*log10(pow(10.0 , Em/10.0) + pow(10.0 , Em/10.0));

								if(fabs(Em-FStrig)<0.1)
								{
									latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
								}
								else if(Em>=FStrig)
								{
									if(d_km1 < (d_km2-10.0))
									{
										d_km1 = d_km;
										d_km = (d_km1 + d_km2)/2.0;
									}
									else
									{
										latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	break;
									}
								}
								else
								{
									if(d_km1 < (d_km2-10.0))
									{
										d_km2 = d_km;
										d_km = (d_km1 + d_km2)/2.0;
									}
									else
									{
										d_km = d_km - 5.0;
										if(d_km<=0)
										{
											latContour_deg[az] = GRlat;	lonContour_deg[az] = GRlon;
											break;
										}
									}
								}

							}//while
							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0*Nrowy/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0*Nrowy/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}//for az
						long Ncty;				int mode = 3;
						CString strY = QGE06_BCBT_A0(latContour_deg, lonContour_deg, 360/AZstep,cty1, FStrig, &Ncty , mode, hR,BCBT); 
						CString strX , RLONbs,RLATbs;
						Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
						strX.Format("%s,%s,%s,%s,%s,%s,%g,%s  %s,%s,%lf,%s,%s" ,SiteName, AdmRefID, sttp, _T("Rx"), cty1,adm1, freq_ter, RLONbs,RLATbs, Pol, BandW_kHz , SysType1, SysType2);

						CGE06repDLG1 dlgList;
						dlgList.m_dataX = strX;
						dlgList.m_dataY = strY;
						dlgList.m_rowsY = Ncty+1;
						dlgList.m_title1 = _Z("GE06 FX-LM to BC-BT - Affected Administrations");
						dlgList.m_title2 = _Z("Wanted Rx Station :");
						dlgList.m_mode = mode;
						dlgList.m_GoogleFlag = m_GoogleFlag;
						if(dlgList.DoModal()==IDOK)
						{
							CString FileName;
							AdmRefID.Replace('/','_');
							FileName.Format("%sReports\\%s_%s_FXLMBCBT%d.txt",m_AppPath,adm1,AdmRefID,iFStrig);
							FILE *fpOUT = fopen(FileName,"wt");
							for(int i=0;i<(360/AZstep);i++)
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
							fclose(fpOUT);
							OnDrawVector(FileName);
							if(dlgList.m_Google)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileName);
						}
					}//if FStrig
				}//for  iFStrig
			}//if Nrowy
		}//if(Pdlg
	}//if Selx
	Set_STtable_Default();
	EndWaitCursor();
}

void CSMS4DCView::OnDatabaseShowsrv() 
{
	CString CDataBaseSTR, Selx = _T("");
//	CDataBaseSTR = _T("SELECT * FROM STtableGE06 WHERE (((AreaOfTrans)<>'')) OR (((radius) Is Not Null And (radius)<>0)) ORDER BY IDst;");
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((AreaOfTrans)<>'')) OR (((radius) Is Not Null And (radius)<>0)) ORDER BY IDst;") , m_qSTtableGE06);
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = FALSE;
	datadlg.m_Title = _T("Select One Station");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow!=1)
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
			return;
		}
		else		//if (Nrow==1)
		{
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
			CString	zone0 = GetFld(Selx,34);
			double	IDst = atol(GetFld(Selx,1));
			CString	name = GetFld(Selx,2);

			if(zone0.GetLength()>0)
			{
				if(zone0.GetLength()==1)			zone0 = zone0 + _T("  ");
				else if(zone0.GetLength()==2)		zone0 = zone0 + _T(" ");
				CString pathfile = VectorCountry(zone0) ;
				OnDrawVector(pathfile);
				double GRlat, GRlon;
				Zone2GRpoint(zone0 ,&GRlat, &GRlon) ;
				OnDatabaseStationsindesktop2(GRlat, GRlon);
				AddStation_disp(IDst,GRlat, GRlon,name) ;
				InvalidateRect(NULL,false);
			}
			else
			{
				double	lat = atof(GetFld(Selx,3)), lon = atof(GetFld(Selx,4));
				CString	r = GetFld(Selx,22);
				if(r.GetLength()>0)
				{
					double latC,lonC;

					CString sFile;
					sFile.Format(_T("%s%s%d.tmp") , ((CSMS4DCApp *)AfxGetApp())->m_AppPath , _T("Temp\\tempM") , m_POLYnum);
					FILE *fptemp=fopen(sFile,"wt");
					for (int i=0;i<73;i++)
					{
						reckon(lat,lon, atof(r) , i*5 , &latC , &lonC) ;
						fprintf(fptemp,"%0.14lf  %0.14lf\n",lonC, latC);
					}
					fclose(fptemp);
					OnDrawVector(sFile);
					OnDatabaseStationsindesktop2(lat,lon);
					AddStation_disp(IDst,lat,lon,name) ;
					InvalidateRect(NULL,false);
				}
			}
		}
	}
	Set_STtable_Default();
}

void CSMS4DCView::Zone2GRpoint(CString zone ,double *GRlat, double *GRlon) 
{
	if(zone.GetLength()==1)			zone = zone + _T("  ");
	else if(zone.GetLength()==2)	zone = zone + _T(" ");

	long n1 = Ctry2Point(zone); 
	double *lat;  lat = new double[n1];
	double *lon;  lon = new double[n1];
	float *CRDARR0;	CRDARR0 = new float[2*n1];

	unsigned char CTYVEK[4]={""}, BCILR;
	strcpy((char *)CTYVEK,zone);
	long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;
	float RLONLL, RLATLL, RLONUR, RLATUR , DENS=0;
	GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
	GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	

	long j = 0;
	while(!NOMORE)
	{
		GEOLIW( &ITYPE, CRDARR0, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
		if(NOMORE)	break;
		for(long p=0;p<NRCRD;p++)
		{
			lat[j] = CRDARR0[2*p+1];			//ITYPE=2  Deg.
			lon[j] = CRDARR0[2*p];
			j++;

		}//end for
	}//end while
	delete [] CRDARR0;

	CP154606_Functions CP154606;
	double GRlat0,GRlon0;
	CP154606.GrPointT(lat , lon , n1 , &GRlat0,&GRlon0);
	*GRlat = GRlat0;	*GRlon = GRlon0;
	delete [] lat;	delete [] lon;
}

CString CSMS4DCView::QGE06_CArea_Qx(BOOL *hef_flag) 
{
	CString CDataBaseSTR, Selx = _T("");
//	CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)=\'GE06A\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\' Or (NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\'));");
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)=\'GE06A\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\' Or (NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\'));") , m_qSTtableGE06ASAL);
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = TRUE;
	datadlg.m_Title = _T("Wanted Assignment");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
		{
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
			*hef_flag = datadlg.m_Heff1;
		}
		else
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
		}
	}
	return Selx;
}

BOOL CSMS4DCView::QGE06_CArea_Q1(long allotkey,double GeoLat_W, double GeoLon_W,double SearchRadius) 
{
	CString contourkeyN , nb_test_ptsN;
	long contourkeyNum = QGE06_BCBT_A3_2(allotkey , &contourkeyN , &nb_test_ptsN);
	long *contourkeyI;		contourkeyI  = new long[contourkeyNum];
	long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
	double dum;
	long NcontourT = 0;
	for(long i=0;i<contourkeyNum;i++)
	{
		contourkeyI[i] = atol(GetFld(contourkeyN,(int)i + 1));
		nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,(int)i + 1));
		NcontourT = NcontourT + nb_test_ptsI[i];
	}
	double * lat_TP;   lat_TP = new double[NcontourT];
	double * lon_TP;   lon_TP = new double[NcontourT];
	double * y;			y = lat_TP;
	double * x;			x = lon_TP;
	for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
	{
		CString lat_tpStr, lon_tpStr;
		long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM] ,nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum);
		for(long jTP=0;jTP<n_tp;jTP++)
		{
			*y = atof(GetFld(lat_tpStr,(int)jTP+1));		y++;
			*x = atof(GetFld(lon_tpStr,(int)jTP+1));		x++;
		}
	}
	double lat0[360],lon0[360];
	for(i=0;i<360;i++)		reckon(GeoLat_W,GeoLon_W, SearchRadius, (double)i, &lat0[i], &lon0[i]) ;

	BOOL uflag = InterSection(lat0,lon0,360,lat_TP,lon_TP,NcontourT) ;
	delete [] contourkeyI;	delete [] nb_test_ptsI;	delete [] lat_TP;		delete [] lon_TP;
	return uflag;
}

int CSMS4DCView::QGE06_CArea_Qy(CString IDst_W, double GeoLat_W, double GeoLon_W,double SearchRadius,double Freq_W,double FR,
								int DP,int AP,int OS, int PEC_W, CString SfnID_W,CString AssocAllotID_W,CString Fragment_W) 
{
	int Nrow = 0,	NrowT = 0;
	double dumy,  lonmin , lonmax , latmin , latmax ,rng_km = SearchRadius , fmin , fmax;
	reckon(GeoLat_W,GeoLon_W, rng_km,  0.0,&latmax,&dumy) ;
	reckon(GeoLat_W,GeoLon_W, rng_km,180.0,&latmin,&dumy) ;
	reckon(GeoLat_W,GeoLon_W, rng_km, 90.0,&dumy,&lonmax) ;
	reckon(GeoLat_W,GeoLon_W, rng_km,270.0,&dumy,&lonmin) ;
	fmin = Freq_W - FR;
	fmax = Freq_W + FR;

	CString CDataBaseSTR = _T("");
	if((PEC_W==1)||(Fragment_W==_T("GE06A")))
	{
		if((DP==1)&&(AP==0)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax);
		else if((DP==0)&&(AP==1)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax);
		else if((DP==0)&&(AP==0)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==1)&&(AP==1)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax,IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax);
		else if((DP==1)&&(AP==0)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==0)&&(AP==1)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==1)&&(AP==1)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
	}
	else if(PEC_W==2)
	{
		if((DP==1)&&(AP==0)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((SfnID)<>\'%s\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,SfnID_W, fmin, fmax);
		else if((DP==0)&&(AP==1)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax);
		else if((DP==0)&&(AP==0)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==1)&&(AP==1)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((SfnID)<>\'%s\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,SfnID_W, fmin, fmax,IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax);
		else if((DP==1)&&(AP==0)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((SfnID)<>\'%s\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,SfnID_W, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==0)&&(AP==1)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==1)&&(AP==1)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((SfnID)<>\'%s\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,SfnID_W, fmin, fmax,IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
	}
	else if((PEC_W==3)||(PEC_W==5))
	{
		if((DP==1)&&(AP==0)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((AdmRefID)<>\'%s\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, AssocAllotID_W);
		else if((DP==0)&&(AP==1)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax);
		else if((DP==0)&&(AP==0)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==1)&&(AP==1)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((AdmRefID)<>\'%s\')) OR (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, AssocAllotID_W, IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax);
		else if((DP==1)&&(AP==0)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((AdmRefID)<>\'%s\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax,AssocAllotID_W, latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==0)&&(AP==1)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==1)&&(AP==1)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((AdmRefID)<>\'%s\')) OR (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax,AssocAllotID_W, IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
	}
	else if(PEC_W==4)
	{
		if((DP==1)&&(AP==0)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((SfnID)<>\'%s\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((AdmRefID)<>\'%s\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,SfnID_W, fmin, fmax, AssocAllotID_W);
		else if((DP==0)&&(AP==1)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax);
		else if((DP==0)&&(AP==0)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==1)&&(AP==1)&&(OS==0))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((SfnID)<>\'%s\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((AdmRefID)<>\'%s\')) OR (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,SfnID_W, fmin, fmax, AssocAllotID_W, IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax);
		else if((DP==1)&&(AP==0)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((SfnID)<>\'%s\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((AdmRefID)<>\'%s\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,SfnID_W, fmin, fmax,AssocAllotID_W, latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==0)&&(AP==1)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
		else if((DP==1)&&(AP==1)&&(OS==1))
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'%s\') AND ((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT1\' Or (NoticeType)=\'GT1\' Or (NoticeType)=\'DS1\' Or (NoticeType)=\'GS1\') AND ((AssignCode) Is Null Or (AssignCode)=\'L\' Or (AssignCode)=\'S\' Or (AssignCode)='') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((SfnID)<>\'%s\')) OR (((Fragment)=\'GE06D\' Or (Fragment)=\'RC06\') AND ((NoticeType)=\'DT2\' Or (NoticeType)=\'GT2\' Or (NoticeType)=\'DS2\' Or (NoticeType)=\'GS2\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\') AND ((AdmRefID)<>\'%s\')) OR (((IDst)<>\'%s\') AND ((Fragment)=\'GE06A\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'BC\' Or (STTP)=\'BT\')) OR (((Fragment)=\'GE06L\') AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf) AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)<>\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'FX\' Or (STTP)=\'FB\') AND ((StType)=\'Typical\')) OR (((Fragment)=\'GE06L\') AND ((TXfreq)>=%lf And (TXfreq)<=%lf) AND ((STTP)=\'ML\'));"),m_qSTtableGE06ASAL,IDst_W,latmin, latmax, lonmin, lonmax, fmin, fmax,SfnID_W, fmin, fmax,AssocAllotID_W, IDst_W, latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax, fmin, fmax);
	}
	if(CDataBaseSTR.GetLength()>0)
	{
		CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
		CDatabase DB1;		CRecordset rs;
		DB1.Open(m_DB,false,false,_T("ODBC;"),false);
		rs.m_pDatabase = &DB1;
		double STlat_deg , STlon_deg;
		CString str, IDst , IDstN = _T(""), allotkey , allotkeyN = _T(""),Fragment,NoticeType,StType,STTP,radius,zone0;

		rs.Open(CRecordset::snapshot, CDataBaseSTR);
		if(rs.GetRecordCount() == 1)
		{
			rs.MoveFirst();
			while(1)
			{
				if(rs.IsEOF()) break;
				rs.GetFieldValue(_T("IDst"),IDst);
				rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
				rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
				rs.GetFieldValue(_T("Fragment"),Fragment);
				rs.GetFieldValue(_T("NoticeType"),NoticeType);
				rs.GetFieldValue(_T("StType"),StType);
				rs.GetFieldValue(_T("STTP"),STTP);
				rs.GetFieldValue(_T("allotkey"),allotkey);
				if(((NoticeType==_T("DT1"))||(NoticeType==_T("GT1"))||(NoticeType==_T("DS1"))||(NoticeType==_T("GS1")))||(Fragment==_T("GE06A"))||(   (Fragment==_T("GE06L"))&&(StType!=_T("Typical"))  &&  ((STTP==_T("FX"))||(STTP==_T("FB")))  ))
				{
					double dist = Distance_km(GeoLat_W,GeoLon_W,STlat_deg,STlon_deg);
					if((dist <= SearchRadius)&&(dist > 0.0000001))
					{
						IDstN = IDstN + _T(",") + IDst;
						allotkeyN = allotkeyN + _T(",") + allotkey;
						Nrow++;
					}
				}
				else if((NoticeType==_T("DT2"))||(NoticeType==_T("GT2"))||(NoticeType==_T("DS2"))||(NoticeType==_T("GS2")))
				{
					BOOL uflag = QGE06_CArea_Q1(atol(allotkey),GeoLat_W, GeoLon_W,SearchRadius);
					if(uflag)
					{
						IDstN = IDstN + _T(",") + IDst;
						allotkeyN = allotkeyN + _T(",") + allotkey;
						Nrow++;
					}
				}
				else if(((Fragment==_T("GE06L"))&&(StType==_T("Typical"))&& ((STTP==_T("FX"))||(STTP==_T("FB"))))||((Fragment==_T("GE06L"))&&(STTP==_T("ML"))))
				{
					rs.GetFieldValue(_T("AreaOfTrans"),zone0);
					if(zone0.GetLength()>0)
					{
						if(zone0.GetLength()==1)			zone0 = zone0 + _T("  ");
						else if(zone0.GetLength()==2)		zone0 = zone0 + _T(" ");
						CString pathfile = VectorCountry(zone0) ;

						long n = Ctry2Point(zone0);
						double *latz;	latz=new double[n];
						double *lonz;	lonz=new double[n];
						QGE06_FXMBCBT_Q2(n, zone0, latz,lonz); 

						double lat0[360],lon0[360];
						for(int i=0;i<360;i++)	reckon(GeoLat_W,GeoLon_W, SearchRadius , (double)i , &lat0[i] , &lon0[i]) ;

						BOOL uflag = InterSection(lat0,lon0,360,latz,lonz,n) ;
						if(uflag)
						{
							IDstN = IDstN + _T(",") + IDst;
							allotkeyN = allotkeyN + _T(",") + allotkey;
							Nrow++;
						}
					}
					else
					{
						rs.GetFieldValue(_T("radius"),radius);
						if(radius.GetLength()>0)
						{
							double dist = Distance_km(GeoLat_W,GeoLon_W,STlat_deg,STlon_deg);
							if(dist <= (SearchRadius+atof(radius)))
							{
								IDstN = IDstN + _T(",") + IDst;
								allotkeyN = allotkeyN + _T(",") + allotkey;
								Nrow++;
							}
						}
					}
				}
				rs.MoveNext();
			}//while
		}
		rs.Close();		DB1.Close();
		IDstN.Delete(0);	allotkeyN.Delete(0);
		if(Nrow>0)
		{
			CString str1,str2 = _T("");
			for(long j=0 ; j<Nrow ;j++)
			{
				str1.Format(_T("(((IDst)=\'%s\') AND ((allotkey)=\'%s\'))"),GetFld(IDstN,j+1),GetFld(allotkeyN,j+1));
				str2 = str2 + _T(" OR ") + str1;
			}
			str2.Delete(0,4);	str2 = str2 + _T(";");
//			CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE %s"),str2);
			CDataBaseSTR.Format(_T("SELECT * FROM %s  WHERE %s "), m_qSTtableGE06ASAL,str2 );
		}
		else		CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE IDst=\'z\';") , m_qSTtableGE06ASAL);
//		else		CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE IDst=\'z\';");

		((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
		((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
		CDataBaseLDLG datadlg;
		datadlg.m_Heff1 = FALSE;
		datadlg.m_Title = _T("Interferer Station / Assignment / Allotment");
		if (datadlg.DoModal()==IDOK)
		{
			NrowT = ((CSMS4DCApp *)AfxGetApp())->Nrow;
	//		*hef_flag = datadlg.m_Heff1;
		}
	}//if CDataBaseSTR
	return NrowT;
}

long CSMS4DCView::QGE06_CArea_Q2(CString SfnID,CString *GeoLat,CString *GeoLon,	CString *Frequency,CString *Pol,
								CString *ERP_h_dbw,CString *ERP_v_dbw,CString *AntCatID,CString *AntHeightAGL,
								CString *AntID,CString *MaxEffHght, CString *AntDir, CString *IDst,int mode) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	if(mode==0)			tbl.Format(_T("SELECT * FROM CommonFields WHERE ((IDst<>\'---\') AND (SfnID=\'%s\'));"), SfnID);
//	else if(mode==1)	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));"), SfnID);
	if(mode==0)			tbl.Format(_T("SELECT * FROM %s WHERE ((IDst<>\'---\') AND (SfnID=\'%s\'));"), m_qCommonFields,SfnID);
	else if(mode==1)	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));"), m_qCommonFields,SfnID);
	rs.Open(CRecordset::snapshot, tbl);
	long c = 0;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),str);				*IDst = *IDst + _T(",") + str;
			rs.GetFieldValue(_T("GeoLat"),str);				*GeoLat = *GeoLat + _T(",") + str;
			rs.GetFieldValue(_T("GeoLon"),str);				*GeoLon = *GeoLon + _T(",") + str;
			rs.GetFieldValue(_T("Frequency"),str);			*Frequency = *Frequency + _T(",") + str;
			rs.GetFieldValue(_T("Pol"),str);				*Pol = *Pol + _T(",") + str;
			rs.GetFieldValue(_T("ERP_h_dbw"),str);			*ERP_h_dbw = *ERP_h_dbw + _T(",") + str;
			rs.GetFieldValue(_T("ERP_v_dbw"),str);			*ERP_v_dbw = *ERP_v_dbw + _T(",") + str;
			rs.GetFieldValue(_T("AntCatID"),str);			*AntCatID = *AntCatID + _T(",") + str;
			rs.GetFieldValue(_T("AntHeightAGL"),str);		*AntHeightAGL = *AntHeightAGL + _T(",") + str;
			rs.GetFieldValue(_T("AntID"),str);				*AntID = *AntID + _T(",") + str;
			rs.GetFieldValue(_T("MaxEffHght"),str);			*MaxEffHght = *MaxEffHght + _T(",") + str;
			rs.GetFieldValue(_T("AntDir"),str);				*AntDir = *AntDir + _T(",") + str;
			c++;
			rs.MoveNext();
		}
	}
	rs.Close();	DB1.Close();
	(*IDst).Delete(0);		(*GeoLat).Delete(0);		(*GeoLon).Delete(0);
	(*Frequency).Delete(0);	(*Pol).Delete(0);			(*ERP_h_dbw).Delete(0);
	(*ERP_v_dbw).Delete(0);	(*AntCatID).Delete(0);		(*AntHeightAGL).Delete(0);
	(*AntID).Delete(0);		(*MaxEffHght).Delete(0);	(*AntDir).Delete(0);
	return c;
}

long CSMS4DCView::QGE06_CArea_Q2_1(CString SfnID,CString *GeoLat,CString *GeoLon,CString *Frequency,CString *Pol,
								CString *ERP_h_dbw,CString *ERP_v_dbw,CString *AntCatID,CString *AntHeightAGL,
								CString *AntID,CString *MaxEffHght, CString *AntDir, CString *IDst,
								CString *NoticeType, CString *RPC, CString *SysVar, CString *RXMode, CString *SpecMask) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));"), SfnID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));"), m_qCommonFields,SfnID);
	rs.Open(CRecordset::snapshot, tbl);
	long c = 0;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),str);				*IDst = *IDst + _T(",") + str;
			rs.GetFieldValue(_T("GeoLat"),str);				*GeoLat = *GeoLat + _T(",") + str;
			rs.GetFieldValue(_T("GeoLon"),str);				*GeoLon = *GeoLon + _T(",") + str;
			rs.GetFieldValue(_T("Frequency"),str);			*Frequency = *Frequency + _T(",") + str;
			rs.GetFieldValue(_T("Pol"),str);				*Pol = *Pol + _T(",") + str;
			rs.GetFieldValue(_T("ERP_h_dbw"),str);			*ERP_h_dbw = *ERP_h_dbw + _T(",") + str;
			rs.GetFieldValue(_T("ERP_v_dbw"),str);			*ERP_v_dbw = *ERP_v_dbw + _T(",") + str;
			rs.GetFieldValue(_T("AntCatID"),str);			*AntCatID = *AntCatID + _T(",") + str;
			rs.GetFieldValue(_T("AntHeightAGL"),str);		*AntHeightAGL = *AntHeightAGL + _T(",") + str;
			rs.GetFieldValue(_T("AntID"),str);				*AntID = *AntID + _T(",") + str;
			rs.GetFieldValue(_T("MaxEffHght"),str);			*MaxEffHght = *MaxEffHght + _T(",") + str;
			rs.GetFieldValue(_T("AntDir"),str);				*AntDir = *AntDir + _T(",") + str;
			rs.GetFieldValue(_T("NoticeType"),str);			*NoticeType = *NoticeType + _T(",") + str;
			rs.GetFieldValue(_T("RefPlanCfg"),str);			*RPC = *RPC + _T(",") + str;
			rs.GetFieldValue(_T("SysVar"),str);				*SysVar = *SysVar + _T(",") + str;
			rs.GetFieldValue(_T("RXMode"),str);				*RXMode = *RXMode + _T(",") + str;
			rs.GetFieldValue(_T("SpectMask"),str);			*SpecMask = *SpecMask + _T(",") + str;
			c++;
			rs.MoveNext();
		}
	}
	rs.Close();	DB1.Close();
	(*IDst).Delete(0);			(*GeoLat).Delete(0);		(*GeoLon).Delete(0);
	(*Frequency).Delete(0);		(*Pol).Delete(0);			(*ERP_h_dbw).Delete(0);
	(*ERP_v_dbw).Delete(0);		(*AntCatID).Delete(0);		(*AntHeightAGL).Delete(0);
	(*AntID).Delete(0);			(*MaxEffHght).Delete(0);	(*AntDir).Delete(0);
	(*NoticeType).Delete(0);	(*RPC).Delete(0);			(*SysVar).Delete(0);
	(*RXMode).Delete(0),		(*SpecMask).Delete(0);
	return c;
}

int CSMS4DCView::IDstCompare(CString IDst, CString IDstN,int num)
{
	int n = IDstN.GetLength();
	for(int j=0;j<n;j++)
	{
		if((IDstN.Left(1))==_T(","))	IDstN.Delete(0);
		else							break;
	}
	for(int i=0;i<num;i++)
	{
		long ID = atol(GetFld(IDstN,i+1));
		if(atol(IDst)==ID)		return 1;
	}
	return 0;
}

double CSMS4DCView::CNFS_Function(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
								double latCal,double lonCal,double CF,double  PRC,double  PRT,double  PR,
								int AntDisc, int ENV,double Ti,double kfactor,double A2D) 
{
	double  CNFS,PR0;
	CP154606_Functions CP154606;
	int az0[37];
	for(int i=0;i<=36;i++)		az0[i] = 10*i;
	double az_I2Cal = Azimuth_Deg(GeoLat_I,GeoLon_I,latCal,lonCal) ;
	double attH0_I[37], attV0_I[37];
	if(AntDir_I==_T("D"))
		GE84pattern(atol(AntCatID_I),attH0_I,attV0_I,Pol_I);
	else
		for(int i=0;i<36;i++)
		{
			attH0_I[i] = 0;		attV0_I[i] = 0;
		}
	attH0_I[36] = attH0_I[0];	attV0_I[36] = attV0_I[0];

	double attnH_I2Cal = Interp2(az0,attH0_I,az_I2Cal,37) ;
	double attnV_I2Cal = Interp2(az0,attV0_I,az_I2Cal,37) ;

	double ERPH,ERPV;
	if     (Pol_I==_T("H"))						ERPH = atof(ERP_h_dbw_I)-attnH_I2Cal;
	else if(Pol_I==_T("V"))						ERPV = atof(ERP_v_dbw_I)-attnV_I2Cal;
	else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{ERPH = atof(ERP_h_dbw_I)-attnH_I2Cal-A2D;	ERPV = atof(ERP_v_dbw_I)-attnV_I2Cal-A2D;}
	/////////////////////////// h1_I //////////////////////
	double h1_I, lat3km, lon3km, lat15km, lon15km;
	double dist_I2Cal = Distance_km(GeoLat_I,GeoLon_I,latCal,lonCal) ;

	OnDatabaseStationsindesktop2(GeoLat_I,GeoLon_I);
	double Hasl_I = LatLon2Hg(GeoLat_I,GeoLon_I);
	double Hasgl_I = Hasl_I + atof(Hagl_I);
	
	if (dist_I2Cal>=15.0)
	{
		reckon(GeoLat_I,GeoLon_I,  3.0 , az_I2Cal , &lat3km  , &lon3km) ;
		reckon(GeoLat_I,GeoLon_I, 15.0 , az_I2Cal , &lat15km , &lon15km) ;
		h1_I = Hasgl_I - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km , 120);
	}
	else
	{
		reckon(GeoLat_I,GeoLon_I, 0.2*dist_I2Cal , az_I2Cal , &lat3km  , &lon3km) ;
		reckon(GeoLat_I,GeoLon_I,     dist_I2Cal , az_I2Cal , &lat15km , &lon15km) ;
		h1_I = Hasgl_I - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km , 120);
	}
	double ATTNantrec = 0, PolAntDisc = 0;
	if(AntDisc==1)
	{
		double az_Cal2W = Azimuth_Deg(latCal,lonCal,GeoLat_W,GeoLon_W) ;
		double az_Cal2I = Azimuth_Deg(latCal,lonCal,GeoLat_I,GeoLon_I) ;
		double AZMantrec = fabs(az_Cal2W-az_Cal2I);
		if(AZMantrec>180)	AZMantrec = 360.0 - AZMantrec;
		ATTNantrec = CP154606.F_3_1_BT419(AZMantrec,Freq_W) ;	//Fig.3-1 REC BT.419
		PolAntDisc = 16;
	}
	double Em = -999, EmH = -999, EmV = -999, EmI = -999;
	Em = E_P154606(GeoLat_I,GeoLon_I,latCal,lonCal, h1_I, Hasgl_I, Freq_I, kfactor, Ti, 10, ENV,0,50, 0);

	if     (Pol_I==_T("H"))						EmH = Em - 30.0 + ERPH;
	else if(Pol_I==_T("V"))						EmV = Em - 30.0 + ERPV;
	else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{EmH = Em - 30.0 + ERPH;	EmV = Em - 30.0 + ERPV;}

	if     (Pol_W==_T("H"))						EmI = 10.0*log10(pow(10.0 , (EmH-ATTNantrec)/10.0) + pow(10.0 , (EmV-PolAntDisc)/10.0));
	else if(Pol_W==_T("V"))						EmI = 10.0*log10(pow(10.0 , (EmH-PolAntDisc)/10.0) + pow(10.0 , (EmV-ATTNantrec)/10.0));
	else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	EmI = 10.0*log10(pow(10.0 , EmH/10.0) + pow(10.0 , EmV/10.0));

	double EmIT = EmI;
	if(Fragment_W==_T("GE06A"))
	{
		double Em = -999, EmH = -999, EmV = -999, EmI = -999;
		Em = E_P154606(GeoLat_I,GeoLon_I,latCal,lonCal, h1_I, Hasgl_I, Freq_I, kfactor, 50, 10, ENV,0,50, 0);

		if     (Pol_I==_T("H"))						EmH = Em - 30.0 + ERPH;
		else if(Pol_I==_T("V"))						EmV = Em - 30.0 + ERPV;
		else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{EmH = Em - 30.0 + ERPH;	EmV = Em - 30.0 + ERPV;	}

		if     (Pol_W==_T("H"))						EmI = 10.0*log10(pow(10.0 , (EmH-ATTNantrec)/10.0) + pow(10.0 , (EmV-PolAntDisc)/10.0));
		else if(Pol_W==_T("V"))						EmI = 10.0*log10(pow(10.0 , (EmH-PolAntDisc)/10.0) + pow(10.0 , (EmV-ATTNantrec)/10.0));
		else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	EmI = 10.0*log10(pow(10.0 , EmH/10.0) + pow(10.0 , EmV/10.0));

		double EmIC = EmI;
		if((EmIC+PRC)>(EmIT+PRT))	PR0 = PRC;
		else						PR0 = PRT;
	}
	else PR0 = PR;
	CNFS = EmIT + PR0 + CF;
	return CNFS;
}

double CSMS4DCView::CNFS_FunctionAL(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
									double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,
									double lat_TP[],double lon_TP[],long NcontourT,double CF,double PRC,double PRT,double PR,
									int AntDisc, int ENV,double Ti) 
{
	double  CNFS,PR0;
	CP154606_Functions CP154606;
	double latTx[7], lonTx[7] , ERPall[7];
	CString Band_I  = CP154606.GE06_Band(Freq_I);

	double DistLimit = 999999999999 , latmin, lonmin , Di1;
	for(long jTP=0;jTP<NcontourT;jTP++)
	{
		Di1 = Distance_km(latCal, lonCal,lat_TP[jTP],lon_TP[jTP]);
		DistLimit = min(DistLimit , Di1);
		if(DistLimit == Di1)
		{
			latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
		}
	}
	int N_Tx = CP154606.Table_RNs(latCal,lonCal, latmin,lonmin,Freq_I,Band_I,RPC_I,RN, ERPall,latTx,lonTx) ;

	double ERPH,ERPV, EmIT = 0;
	for(int ASi=0;ASi<N_Tx;ASi++)
	{
		if     (Pol_I==_T("H"))						ERPH = ERPall[ASi];
		else if(Pol_I==_T("V"))						ERPV = ERPall[ASi];
		else if((Pol_I==_T("M"))||(Pol_I==_T("U"))){ERPH = ERPall[ASi]-3.0;	ERPV = ERPall[ASi]-3.0;}
		double ATTNantrec = 0, PolAntDisc = 0;
		if(AntDisc==1)
		{
			double az_Cal2W = Azimuth_Deg(latCal,lonCal,GeoLat_W,GeoLon_W) ;
			double az_Cal2I = Azimuth_Deg(latCal,lonCal,latTx[ASi],lonTx[ASi]) ;
			double AZMantrec = fabs(az_Cal2W-az_Cal2I);
			if(AZMantrec>180)	AZMantrec = 360.0 - AZMantrec;
			ATTNantrec = CP154606.F_3_1_BT419(AZMantrec,Freq_W) ;	//Fig.3-1 REC BT.419
			PolAntDisc = 16;
		}
		double Em = -999, EmH = -999, EmV = -999, Em1 = -999;
//		Em = E_P154606AL(latTx[ASi],lonTx[ASi],latCal,lonCal, 150, Freq_I, Ti,10, ENV,0,50);
		Em = E_P154606AL(latTx[ASi],lonTx[ASi],latCal,lonCal, 150, Freq_I, Ti);
		if     (Pol_I==_T("H"))						EmH = Em - 30.0 + ERPH;
		else if(Pol_I==_T("V"))						EmV = Em - 30.0 + ERPV;
		else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{EmH = Em - 30.0 + ERPH;	EmV = Em - 30.0 + ERPV;}
		if     (Pol_W==_T("H"))						Em1 = 10.0*log10(pow(10.0 , (EmH-ATTNantrec)/10.0) + pow(10.0 , (EmV-PolAntDisc)/10.0));
		else if(Pol_W==_T("V"))						Em1 = 10.0*log10(pow(10.0 , (EmH-PolAntDisc)/10.0) + pow(10.0 , (EmV-ATTNantrec)/10.0));
		else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	Em1 = 10.0*log10(pow(10.0 , EmH/10.0) + pow(10.0 , EmV/10.0));
		EmIT = EmIT + pow(10.0 , Em1/10.0);
	}
	EmIT = 10.0*log10(EmIT);

	if(Fragment_W==_T("GE06A"))
	{
		double EmIC = 0;
		for(int ASi=0;ASi<N_Tx;ASi++)
		{
			if     (Pol_I==_T("H"))						ERPH = ERPall[ASi];
			else if(Pol_I==_T("V"))						ERPV = ERPall[ASi];
			else if((Pol_I==_T("M"))||(Pol_I==_T("U"))){ERPH = ERPall[ASi]-3.0;	ERPV = ERPall[ASi]-3.0;}
			double ATTNantrec = 0, PolAntDisc = 0;
			if(AntDisc==1)
			{
				double az_Cal2W = Azimuth_Deg(latCal,lonCal,GeoLat_W,GeoLon_W) ;
				double az_Cal2I = Azimuth_Deg(latCal,lonCal,latTx[ASi],lonTx[ASi]) ;
				double AZMantrec = fabs(az_Cal2W-az_Cal2I);
				if(AZMantrec>180)	AZMantrec = 360.0 - AZMantrec;
				ATTNantrec = CP154606.F_3_1_BT419(AZMantrec,Freq_W) ;	//Fig.3-1 REC BT.419
				PolAntDisc = 16;
			}
			double Em = -999, EmH = -999, EmV = -999, Em1 = -999;
//			Em = E_P154606AL(latTx[ASi],lonTx[ASi],latCal,lonCal, 150, Freq_I, 50,10, ENV,0,50);
			Em = E_P154606AL(latTx[ASi],lonTx[ASi],latCal,lonCal, 150, Freq_I, 50);
			if     (Pol_I==_T("H"))						EmH = Em - 30.0 + ERPH;
			else if(Pol_I==_T("V"))						EmV = Em - 30.0 + ERPV;
			else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{EmH = Em - 30.0 + ERPH;	EmV = Em - 30.0 + ERPV;}
			if     (Pol_W==_T("H"))						Em1 = 10.0*log10(pow(10.0 , (EmH-ATTNantrec)/10.0) + pow(10.0 , (EmV-PolAntDisc)/10.0));
			else if(Pol_W==_T("V"))						Em1 = 10.0*log10(pow(10.0 , (EmH-PolAntDisc)/10.0) + pow(10.0 , (EmV-ATTNantrec)/10.0));
			else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	Em1 = 10.0*log10(pow(10.0 , EmH/10.0) + pow(10.0 , EmV/10.0));
			EmIC = EmIC + pow(10.0 , Em1/10.0);
		}
		EmIC = 10.0*log10(EmIC);
		if((EmIC+PRC)>(EmIT+PRT))	PR0 = PRC;
		else						PR0 = PRT;
	}
	else PR0 = PR;
	CNFS = EmIT + PR0 + CF;
	return CNFS;
}

CString CSMS4DCView::QGE06_CArea_Q3(CString AdmRefID) 
{
	CString  allotkey , tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)=\'---\') AND ((AdmRefID)=\'%s\') AND ((SfnID)='' Or (SfnID) Is Null));"),AdmRefID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)=\'---\') AND ((AdmRefID)=\'%s\') AND ((SfnID)='' Or (SfnID) Is Null));"),m_qCommonFields,AdmRefID);
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		rs.GetFieldValue(_T("allotkey"),allotkey);
	}
	rs.Close();	DB1.Close();
	return allotkey;
}
CString CSMS4DCView::QGE06_CArea_Q4(CString AssocAllotID) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR , str1 = _T("");
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>\'---\') AND ((AssocAllotID)=\'%s\'));"),AssocAllotID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'---\') AND ((AssocAllotID)=\'%s\'));"),m_qCommonFields,AssocAllotID);
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		rs.GetFieldValue(_T("IDst"),str);			str1 = str;
		rs.GetFieldValue(_T("Pol"),str);			str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("GeoLat"),str);			str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("GeoLon"),str);			str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("ERP_h_dbw"),str);		str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("ERP_v_dbw"),str);		str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("AntDir"),str);			str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("AntCatID"),str);		str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("AntHeightAGL"),str);	str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("NoticeType"),str);		str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("RefPlanCfg"),str);		str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("SysVar"),str);			str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("RXMode"),str);			str1 = str1 + _T(",") + str;
		rs.GetFieldValue(_T("SpectMask"),str);		str1 = str1 + _T(",") + str;
	}
	rs.Close();	DB1.Close();
	return str1;
}
void CSMS4DCView::Zone2NearPoint(CString zone ,double lat0, double lon0 ,double *Nlat, double *Nlon) 
{
	if(zone.GetLength()==1)			zone = zone + _T("  ");
	else if(zone.GetLength()==2)	zone = zone + _T(" ");
	long n1 = Ctry2Point(zone); 
	double lat , lon;
	float *CRDARR0;	CRDARR0 = new float[2*n1];
	unsigned char CTYVEK[4]={""}, BCILR;
	strcpy((char *)CTYVEK,zone);
	long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;
	float RLONLL, RLATLL, RLONUR, RLATUR , DENS=0;
	GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
	GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	
	double dist , Dmin = 99999999;
	while(!NOMORE)
	{
		GEOLIW( &ITYPE, CRDARR0, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
		if(NOMORE)	break;
		for(long p=0;p<NRCRD;p++)
		{
			lat = CRDARR0[2*p+1];	lon = CRDARR0[2*p];			//ITYPE=2  Deg.
			dist = Distance_km(lat0,lon0, lat,lon) ;
			Dmin = min(Dmin , dist);
			if(Dmin == dist)
			{
				*Nlat = lat;		*Nlon = lon;
			}
		}//end for
	}//end while
	delete [] CRDARR0;
}

double CSMS4DCView::GE06UFS(int Nrowy,CString Fragment_W,CString NoticeType_W,double Freq_W,
						  CString TV_SYS_W, CString RPC_W, CString SYS_VAR_W, double freq_vcarr_W,
						  CString TV_COLOR_W, double freq_scarr_W,CString oset_v_12_W,CString oset_v_khz_W,
						  CString TV_ch_W, CString RxMode_W, CString freq_stabl_W, double miu_W, double Sigma_W,
						  double GeoLat_W, double GeoLon_W, CString Pol_W, double latCal, double lonCal,
						  int AntDisc, int ENV, double Ti, double kfactor,double UFSmin )
{
	CP154606_Functions CP154606;
	double UFS,		CNFS_T1 = 0;
	CString Assign_IDst = _T(""),	Allot_IDst = _T("");	int nAssign_IDst = 0,	nAllot_IDst = 0;

	for(int iY=0; iY<Nrowy; iY++)
	{
		CString Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iY];
		CString IDst_I = GetFld(Sely,1),				RxMode_I = GetFld(Sely,54),			Fragment_I = GetFld(Sely,28),
				NoticeType_I = GetFld(Sely,35),			sttp_I = GetFld(Sely,18),			TV_SYS_I = GetFld(Sely,36),
				RPC_I = GetFld(Sely,37),				SYS_VAR_I = GetFld(Sely,38),		Emission_I = GetFld(Sely,19),
				TV_COLOR_I = GetFld(Sely,40),			SysType1_I = GetFld(Sely,26),		SysType2_I = GetFld(Sely,27),
				oset_v_12_I = GetFld(Sely,42),			oset_v_khz_I = GetFld(Sely,43),		TV_ch_I = GetFld(Sely,44);
		double  Freq_I = atof(GetFld(Sely,6)),			pwr_ratio_I = atof(GetFld(Sely,46)),
				freq_vcarr_I = atof(GetFld(Sely,39)),	freq_scarr_I = atof(GetFld(Sely,41));

		double PR, PRC, PRT;
		CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
								freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,RxMode_W,freq_stabl_W,
								Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPC_I,SYS_VAR_I,
								Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,SysType2_I,freq_scarr_I,
								oset_v_12_I,oset_v_khz_I,TV_ch_I,pwr_ratio_I, &PR, &PRC, &PRT) ;

		if( ((Fragment_W==_T("GE06A"))&&(PRC!=-999)&&(PRT!=-999))  ||  ((Fragment_W!=_T("GE06A"))&&(PR!=-999))	)
		{
		//	double Sigma_N = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, SRV_I);
			double Sigma_N = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, ENV,sttp_I);
			double CF = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_N*Sigma_N);
			CString PlanEntry_I = GetFld(Sely,50),		SfnID_I = GetFld(Sely,52),	AssocAllotID_I = GetFld(Sely,59),	AdmRefID_I = GetFld(Sely,33);
			CString STN_I = CP154606.GE06_STN(Fragment_I, NoticeType_I);
			int PEC_I = GE06_PEC(AdmRefID_I , AssocAllotID_I , PlanEntry_I , SfnID_I , STN_I) ;
			CString NET_I;	NET_I.Format("%s%d",STN_I,PEC_I);

			if((NET_I==_T("ASA0"))||(PEC_I==1))
			{
				CString Pol_I = GetFld(Sely,13),			ERP_h_dbw_I = GetFld(Sely,62),		ERP_v_dbw_I = GetFld(Sely,63),
						AntDir_I = GetFld(Sely,31),			AntCatID_I = GetFld(Sely,30),		Hagl_I = GetFld(Sely,5);
				double  GeoLat_I = atof(GetFld(Sely,3)),	GeoLon_I = atof(GetFld(Sely,4));
				double CNFSj = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
											 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
											 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
											 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor); 
				CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
			}//if((NET_I==_T("ASA0"))||(PEC_I==1))
			else if(PEC_I==2)
			{
				int flagID = IDstCompare(IDst_I, Assign_IDst, nAssign_IDst);
				if(flagID==0)
				{
					CString SFNID_I = GetFld(Sely,52);
					CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN, ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN;
					long numAssign = QGE06_CArea_Q2(SFNID_I,&GeoLatN,&GeoLonN,
													&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
													&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN) ;
					Assign_IDst = Assign_IDst + _T(",") + IDstN;	nAssign_IDst = nAssign_IDst + numAssign;
					for(int iAS = 0; iAS<numAssign ; iAS++)
					{
						CString Pol_I = GetFld(PolN,iAS+1),					AntDir_I = GetFld(AntDirN,iAS+1),
								AntCatID_I = GetFld(AntCatIDN,iAS+1),		ERP_h_dbw_I = GetFld(ERP_h_dbwN,iAS+1),
								ERP_v_dbw_I = GetFld(ERP_v_dbwN,iAS+1),		Hagl_I = GetFld(AntHeightAGLN,iAS+1);
						double  GeoLat_I = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_I = atof(GetFld(GeoLonN,iAS+1)),
								Freq_I = atof(GetFld(FrequencyN,iAS+1));

						double CNFSj = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
													 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
													 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
													 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor); 
						CNFS_T1 = CNFS_T1 + pow(10.0, (CNFSj)/10.0);

					}//for  iAS

				}//if flagID
			}//if(PEC_I==2)
			else if(PEC_I==3)
			{
				CString GeoArea_I = GetFld(Sely,53);	CString Pol_I = GetFld(Sely,13);
				CString allotkey_I = GetFld(Sely,64);
				if(GeoArea_I.IsEmpty())
				{
					CString contourkeyN , nb_test_ptsN;
					long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_I) , &contourkeyN , &nb_test_ptsN);
					long *contourkeyI;		contourkeyI = new long[contourkeyNum];
					long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
					double dum;
					long NcontourT = 0;
					for(long i=0;i<contourkeyNum;i++)
					{
						contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
						nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
						NcontourT = NcontourT + nb_test_ptsI[i];
					}
					double * lat_TP;   lat_TP = new double[NcontourT];
					double * lon_TP;   lon_TP = new double[NcontourT];
					double * y;		y = lat_TP;
					double * x;		x = lon_TP;
					for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
					{
						CString lat_tpStr, lon_tpStr;
						long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
						for(long jTP=0;jTP<n_tp;jTP++)
						{
							*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
							*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
						}
					}
					CString RN = _T("");
					if     (NET_I==_T("ALT3"))							RN = GetFld(Sely,61);
					else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
					else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

					double CNFSj = CNFS_FunctionAL_0(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,	latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN,	lat_TP, lon_TP, NcontourT, CF, PRC, PRT, PR,AntDisc, ENV, Ti) ;
					CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
					delete [] contourkeyI;		delete [] nb_test_ptsI;	delete [] lat_TP;	delete [] lon_TP;
				}//if GeoArea_I
				else
				{
					CString lat_tpSTR, lon_tpSTR;
					double dum;
					long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_I, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
					double * lat_TP;   lat_TP = new double[NcontourT];
					double * lon_TP;   lon_TP = new double[NcontourT];
					for(long jTP=0;jTP<NcontourT;jTP++)
					{
						lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
						lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
					}
					CString RN = _T("");
					if     (NET_I==_T("ALT3"))							RN = GetFld(Sely,61);
					else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
					else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

					double CNFSj = CNFS_FunctionAL_0(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,	latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN,	lat_TP, lon_TP, NcontourT, CF, PRC, PRT, PR,AntDisc, ENV, Ti) ;
					CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
					delete [] lat_TP;		delete [] lon_TP;
				}//else GeoArea_I
			}//if(PEC_I==3)
			else if(PEC_I==4)
			{
				if((NET_I==_T("ASS4"))||(NET_I==_T("AST4")))	/////////A4_1
				{
					double CNFSsfn = 0, CNFSallot = 0;
					//+++++++++++++++Assignment++++++++++++++++++++++++++++++++++++++++
					int flagID = IDstCompare(IDst_I, Assign_IDst, nAssign_IDst);
					CString SFNID_I = GetFld(Sely,52);
					if(flagID==0)
					{
						CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN;
						long numAssign = QGE06_CArea_Q2(SFNID_I,&GeoLatN,&GeoLonN,
														&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
														&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN,1) ;
						Assign_IDst = Assign_IDst + _T(",") + IDstN;	nAssign_IDst = nAssign_IDst + numAssign;
						double CNFSjAS = 0;
						for(int iAS = 0; iAS<numAssign ; iAS++)
						{
							CString Pol_I = GetFld(PolN,iAS+1),					AntDir_I = GetFld(AntDirN,iAS+1),
									AntCatID_I = GetFld(AntCatIDN,iAS+1),		ERP_h_dbw_I = GetFld(ERP_h_dbwN,iAS+1),
									ERP_v_dbw_I = GetFld(ERP_v_dbwN,iAS+1),		Hagl_I = GetFld(AntHeightAGLN,iAS+1);
							double  GeoLat_I = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_I = atof(GetFld(GeoLonN,iAS+1)),
									Freq_I = atof(GetFld(FrequencyN,iAS+1));

							double CNFS1 = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
														 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
														 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
														 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor); 
							CNFSjAS = CNFSjAS + pow(10.0, (CNFS1)/10.0);
						}//for  iAS
						CNFSsfn = 10.0*log10(CNFSjAS);
					}//if flagID
					//+++++++++++++++Allotment++++++++++++++++++++++++++++++++++++++++
					CString AllotmentSTR = QGE06_BCBT_A4_1(SFNID_I) ;
					CString allotkey_I = GetFld(AllotmentSTR,1) ;
					int flagIDal = IDstCompare(allotkey_I, Allot_IDst, nAllot_IDst);
					if(flagIDal==0)
					{
						CString NoticeType_I = GetFld(AllotmentSTR,3);	CString GeoArea_I = GetFld(AllotmentSTR,9) ;
						CString Pol_I = GetFld(AllotmentSTR,10);		CString SYS_VAR_I = GetFld(AllotmentSTR,11) ;
						Allot_IDst = Allot_IDst + _T(",") + allotkey_I;	nAllot_IDst = nAllot_IDst + 1;
						if(GeoArea_I.IsEmpty())
						{
							CString contourkeyN , nb_test_ptsN;
							long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_I) , &contourkeyN , &nb_test_ptsN);
							long *contourkeyI;		contourkeyI = new long[contourkeyNum];
							long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
							double dum;
							long NcontourT = 0;
							for(long i=0;i<contourkeyNum;i++)
							{
								contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
								nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
								NcontourT = NcontourT + nb_test_ptsI[i];
							}
							double * lat_TP;   lat_TP = new double[NcontourT];
							double * lon_TP;   lon_TP = new double[NcontourT];
							double * y;		y = lat_TP;
							double * x;		x = lon_TP;
							for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
							{
								CString lat_tpStr, lon_tpStr;
								long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
								for(long jTP=0;jTP<n_tp;jTP++)
								{
									*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
									*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
								}
							}
					//00000000000000000000000000000000000000000000000000000000000000000000000000
							CString STNal = CP154606.GE06_STN(GetFld(AllotmentSTR,2),GetFld(AllotmentSTR,3));
							int PECal = GE06_PEC(GetFld(AllotmentSTR,4) , GetFld(AllotmentSTR,5) , GetFld(AllotmentSTR,6) , SfnID_I , STNal) ;
							CString NETal;	NETal.Format("%s%d",STNal,PECal);
							CString RPCal = GetFld(AllotmentSTR,7);
							CString RNal = _T("");
							if     (NETal==_T("ALT4"))							RNal = GetFld(AllotmentSTR,8);
							else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC4")))	RNal = _T("RN5");
							else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC5")))	RNal = _T("RN6");

							double PRal, PRCal, PRTal;
							CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,
													SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
													freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,
													RxMode_W,freq_stabl_W,
													Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPCal,
													SYS_VAR_I,Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,
													SysType2_I,freq_scarr_I,oset_v_12_I,oset_v_khz_I,TV_ch_I,
													pwr_ratio_I, &PRal, &PRCal, &PRTal) ;

						//	double Sigma_Nal = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPCal, Freq_I, SRV_I);
							double Sigma_Nal = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPCal, Freq_I, ENV,sttp_I);
							double CFal = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_Nal*Sigma_Nal);
					//00000000000000000000000000000000000000000000000000000000000000000000000000
							double CNFSj = CNFS_FunctionAL_0(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
														   latCal, lonCal, Freq_I,  Pol_I,  RPCal, RNal, lat_TP, lon_TP, NcontourT,
														   CFal, PRCal, PRTal, PRal,AntDisc, ENV, Ti) ;
							CNFSallot = CNFSj;
							delete [] contourkeyI;	delete [] nb_test_ptsI;		delete [] lat_TP;		delete [] lon_TP;
						}//if GeoArea_I
						else
						{
							CString lat_tpSTR, lon_tpSTR;
							double dum;
							long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_I, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
							double * lat_TP;   lat_TP = new double[NcontourT];
							double * lon_TP;   lon_TP = new double[NcontourT];
							for(long jTP=0;jTP<NcontourT;jTP++)
							{
								lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
								lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
							}
					//00000000000000000000000000000000000000000000000000000000000000000000000000
							CString STNal = CP154606.GE06_STN(GetFld(AllotmentSTR,2),GetFld(AllotmentSTR,3));
							int PECal = GE06_PEC(GetFld(AllotmentSTR,4) , GetFld(AllotmentSTR,5) , GetFld(AllotmentSTR,6) , SfnID_I , STNal) ;
							CString NETal;	NETal.Format("%s%d",STNal,PECal);
							CString RPCal = GetFld(AllotmentSTR,7);
							CString RNal = _T("");
							if     (NETal==_T("ALT4"))							RNal = GetFld(AllotmentSTR,8);
							else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC4")))	RNal = _T("RN5");
							else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC5")))	RNal = _T("RN6");

							double PRal, PRCal, PRTal;
							CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,
													SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
													freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,
													RxMode_W,freq_stabl_W,
													Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPCal,
													SYS_VAR_I,Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,
													SysType2_I,freq_scarr_I,oset_v_12_I,oset_v_khz_I,TV_ch_I,
													pwr_ratio_I, &PRal, &PRCal, &PRTal) ;

						//	double Sigma_Nal = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPCal, Freq_I, SRV_I);
							double Sigma_Nal = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPCal, Freq_I, ENV,sttp_I);
							double CFal = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_Nal*Sigma_Nal);
					//00000000000000000000000000000000000000000000000000000000000000000000000000
							double CNFSj = CNFS_FunctionAL_0(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
														   latCal, lonCal, Freq_I,  Pol_I,  RPCal, RNal,lat_TP, lon_TP, NcontourT,
														   CFal, PRCal, PRTal, PRal,AntDisc, ENV, Ti) ;
							CNFSallot = CNFSj;
							delete [] lat_TP;	delete [] lon_TP;
						}//else GeoArea_I
					}//if flagIDal
					double CNFSj = max(CNFSsfn , CNFSallot);
					CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
				}/////////A4_1
				else if((NET_I==_T("ALS4"))||(NET_I==_T("ALT4")))	/////////A4_2
				{
					double CNFSsfn = 0, CNFSallot = 0;
					//+++++++++++++++Assignment++++++++++++++++++++++++++++++++++++++++
					CString SFNID_I = GetFld(Sely,52);
					CString dumstr;
					CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN, NoticeTypeN, RPCN , SysVarN, RxModeN;
					long numAssign = QGE06_CArea_Q2_1(SFNID_I,&GeoLatN,&GeoLonN,
													&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
													&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN,
													&NoticeTypeN, &RPCN , &SysVarN, &RxModeN,&dumstr) ;
					int flagID = IDstCompare(GetFld(IDstN,1), Assign_IDst, nAssign_IDst);
					if(flagID==0)
					{
						Assign_IDst = Assign_IDst + _T(",") + IDstN;	nAssign_IDst = nAssign_IDst + numAssign;

						CString NoticeType_I = GetFld(NoticeTypeN,1),	RPC_I = GetFld(RPCN,1),
								SysVar_I = GetFld(SysVarN,1),			RxMode_I = GetFld(RxModeN,1);
						double PRas, PRCas, PRTas;
						CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,
												SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
												freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,
												RxMode_W,freq_stabl_W,
												Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPC_I,
												SYS_VAR_I,Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,
												SysType2_I,freq_scarr_I,oset_v_12_I,oset_v_khz_I,TV_ch_I,
												pwr_ratio_I, &PRas, &PRCas, &PRTas) ;

					//	double Sigma_Nas = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, SRV_I);
						double Sigma_Nas = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, ENV,sttp_I);
						double CFas = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_Nas*Sigma_Nas);
						double CNFSjAS = 0;
						for(int iAS = 0; iAS<numAssign ; iAS++)
						{
							CString Pol_I = GetFld(PolN,iAS+1),					AntDir_I = GetFld(AntDirN,iAS+1),
									AntCatID_I = GetFld(AntCatIDN,iAS+1),		ERP_h_dbw_I = GetFld(ERP_h_dbwN,iAS+1),
									ERP_v_dbw_I = GetFld(ERP_v_dbwN,iAS+1),		Hagl_I = GetFld(AntHeightAGLN,iAS+1);
							double  GeoLat_I = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_I = atof(GetFld(GeoLonN,iAS+1));

							double CNFS1 = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
														 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
														 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
														 latCal, lonCal, CFas, PRCas, PRTas, PRas,AntDisc, ENV, Ti, kfactor); 
							CNFSjAS = CNFSjAS + pow(10.0, (CNFS1)/10.0);
						}//for  iAS
						CNFSsfn = 10.0*log10(CNFSjAS);
					}//if flagID
					//+++++++++++++++Allotment++++++++++++++++++++++++++++++++++++++++
					CString allotkey_I = GetFld(Sely,64);
					int flagIDal = IDstCompare(allotkey_I, Allot_IDst, nAllot_IDst);
					if(flagIDal==0)
					{
						CString GeoArea_I = GetFld(Sely,53);	CString Pol_I = GetFld(Sely,13);
						Allot_IDst = Allot_IDst + _T(",") + allotkey_I;	nAllot_IDst = nAllot_IDst + 1;
						if(GeoArea_I.IsEmpty())
						{
							CString contourkeyN , nb_test_ptsN;
							long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_I) , &contourkeyN , &nb_test_ptsN);
							long *contourkeyI;		contourkeyI = new long[contourkeyNum];
							long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
							double dum;
							long NcontourT = 0;
							for(long i=0;i<contourkeyNum;i++)
							{
								contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
								nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
								NcontourT = NcontourT + nb_test_ptsI[i];
							}
							double * lat_TP;   lat_TP = new double[NcontourT];
							double * lon_TP;   lon_TP = new double[NcontourT];
							double * y;		y = lat_TP;
							double * x;		x = lon_TP;
							for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
							{
								CString lat_tpStr, lon_tpStr;
								long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
								for(long jTP=0;jTP<n_tp;jTP++)
								{
									*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
									*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
								}
							}
							CString RN = _T("");
							if     (NET_I==_T("ALT4"))							RN = GetFld(Sely,61);
							else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
							else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

							double CNFSj = CNFS_FunctionAL_0(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,	latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN,	lat_TP, lon_TP, NcontourT, CF, PRC, PRT, PR,AntDisc, ENV, Ti) ;
							CNFSallot = CNFSj;
							delete [] contourkeyI;	delete [] nb_test_ptsI;	delete [] lat_TP;		delete [] lon_TP;
						}//if GeoArea_I
						else
						{
							CString lat_tpSTR, lon_tpSTR;
							double dum;
							long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_I, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
							double * lat_TP;   lat_TP = new double[NcontourT];
							double * lon_TP;   lon_TP = new double[NcontourT];
							for(long jTP=0;jTP<NcontourT;jTP++)
							{
								lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
								lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
							}
							CString RN = _T("");
							if     (NET_I==_T("ALT4"))							RN = GetFld(Sely,61);
							else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
							else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

							double CNFSj = CNFS_FunctionAL_0(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,	latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN,	lat_TP, lon_TP, NcontourT, CF, PRC, PRT, PR,AntDisc, ENV, Ti) ;
							CNFSallot = CNFSj;
							delete [] lat_TP;		delete [] lon_TP;
						}//else GeoArea_I
					}//if flagIDal
					double CNFSj = max(CNFSsfn , CNFSallot);
					CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
				}/////////A4_2
			}//if(PEC_I==4)
			else if(PEC_I==5)
			{
				if((NET_I==_T("ASS5"))||(NET_I==_T("AST5")))	/////////A5_1
				{
					int flagID = IDstCompare(IDst_I, Assign_IDst, nAssign_IDst);
					if(flagID==0)
					{
						CString allotkey_I = QGE06_CArea_Q3(AssocAllotID_I) ;
						Allot_IDst = Allot_IDst + _T(",") + allotkey_I;	nAllot_IDst = nAllot_IDst + 1;
						Assign_IDst = Assign_IDst + _T(",") + IDst_I;	nAssign_IDst = nAssign_IDst + 1;
						
						CString Pol_I = GetFld(Sely,13),			ERP_h_dbw_I = GetFld(Sely,62),
								ERP_v_dbw_I = GetFld(Sely,63),		AntDir_I = GetFld(Sely,31),
								AntCatID_I = GetFld(Sely,30),		Hagl_I = GetFld(Sely,5);
						double  GeoLat_I = atof(GetFld(Sely,3)),	GeoLon_I = atof(GetFld(Sely,4));

						double CNFSj = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
													 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
													 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
													 latCal, lonCal, CF, PRC, PRT, PR,AntDisc, ENV, Ti, kfactor); 
						CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
					}//if flagIDal
				}	/////////A5_1
				else if((NET_I==_T("ALS5"))||(NET_I==_T("ALT5")))	/////////A5_2
				{
					CString allotkey_I = GetFld(Sely,64);
					int flagIDal = IDstCompare(allotkey_I, Allot_IDst, nAllot_IDst);
					if(flagIDal==0)
					{
						CString ASstr = QGE06_CArea_Q4(AdmRefID_I);
						CString IDst_I = GetFld(ASstr,1);
						Allot_IDst = Allot_IDst + _T(",") + allotkey_I;	nAllot_IDst = nAllot_IDst + 1;
						Assign_IDst = Assign_IDst + _T(",") + IDst_I;	nAssign_IDst = nAssign_IDst + 1;
						CString Pol_I = GetFld(ASstr,2),			ERP_h_dbw_I = GetFld(ASstr,5),
								ERP_v_dbw_I = GetFld(ASstr,6),		AntDir_I = GetFld(ASstr,7),
								AntCatID_I = GetFld(ASstr,8),		Hagl_I = GetFld(ASstr,9),
								NoticeType_I = GetFld(ASstr,10),	RPC_I = GetFld(ASstr,11),
								SYS_VAR_I = GetFld(ASstr,12),		RxMode_I = GetFld(ASstr,13);
						double  GeoLat_I = atof(GetFld(ASstr,3)),	GeoLon_I = atof(GetFld(ASstr,4));
						double PRas, PRCas, PRTas;
						CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,
												SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
												freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,
												RxMode_W,freq_stabl_W,
												Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPC_I,
												SYS_VAR_I,Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,
												SysType2_I,freq_scarr_I,oset_v_12_I,oset_v_khz_I,TV_ch_I,
												pwr_ratio_I, &PRas, &PRCas, &PRTas) ;
					//	double Sigma_Nas = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, SRV_I);
						double Sigma_Nas = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, ENV,sttp_I);
						double CFas = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_Nas*Sigma_Nas);
						double CNFSj = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
													 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
													 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
													 latCal, lonCal, CFas, PRCas, PRTas, PRas,AntDisc, ENV, Ti, kfactor); 
						CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
					}//if flagID
				}	/////////A5_2
			}//if(PEC_I==5)
			else if(Fragment_I==_T("GE06L"))
			{
				CString Pol_I = GetFld(Sely,13);	CString StType_I = GetFld(Sely,29);
				int dflag = 0;
				double  GeoLat_I, GeoLon_I;
				if((((sttp_I==_T("FX"))||(sttp_I==_T("FB")))&&(StType_I==_T("Typical"))) || ((sttp_I==_T("ML"))&&(StType_I!=_T("Typical"))))
				{
					CString zone0 = GetFld(Sely,34);
					if(zone0.GetLength()>0)
					{
						if(zone0.GetLength()==1)			zone0 = zone0 + _T("  ");
						else if(zone0.GetLength()==2)		zone0 = zone0 + _T(" ");
						Zone2NearPoint(zone0, latCal, lonCal, &GeoLat_I, &GeoLon_I); 
						dflag = 1;
					}//if zone0
					else
					{
						CString radius = GetFld(Sely,22);
						if(radius.GetLength()>0)
						{
							double latC = atof(GetFld(Sely,3))  ,  lonC = atof(GetFld(Sely,4));
							double azC = Azimuth_Deg(latC, lonC, latCal,lonCal) ;
							reckon(latC, lonC, atof(radius), azC, &GeoLat_I, &GeoLon_I) ;
							dflag = 1;
						}
					}
				}
				else if(((sttp_I==_T("FX"))||(sttp_I==_T("FB")))&&(StType_I!=_T("Typical")))
				{
					GeoLat_I = atof(GetFld(Sely,3));	GeoLon_I = atof(GetFld(Sely,4));
					dflag = 1;
				}
				if(dflag == 1)
				{
					double PWR = atof(GetFld(Sely,7));	//W
					double PwrERP = 10.0*log10(PWR) - 2.15;	//dBw
					CString ERP_h_dbw_I;	ERP_h_dbw_I.Format(_T("%lf"), PwrERP);
					CString ERP_v_dbw_I;	ERP_v_dbw_I.Format(_T("%lf"), PwrERP);
					CString AntDir_I = GetFld(Sely,31),		AntCatID_I = GetFld(Sely,30),	Hagl_I = GetFld(Sely,5);
					double CNFSj = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
												 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
												 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
												 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,3); 
					CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
				}//if dflag
			}//if Fragment_I==_T("GE06L"))

		}//if _I is Interferer
	}//for iY
	UFS = 10.0*log10(CNFS_T1 + pow(10.0, (UFSmin)/10.0));
	return UFS;
}
void CSMS4DCView::OnCoordinationGe06Coveragearea()
{
	GE06CoverageArea(-1, -1, 10);
}

void CSMS4DCView::GE06CoverageArea(int EXA, int LNB, int AZstep, int UD) 
{
	CString FileNameNL , FileNameIL , FileNameTP;
	for(;;)
	{
		BeginWaitCursor();
		BOOL hef_flag;
		CString Selx = QGE06_CArea_Qx(&hef_flag) ;
		if(Selx.GetLength()>0)
		{
			BeginWaitCursor();
			CString IDst_W = GetFld(Selx,1),		 RPC_W = GetFld(Selx,37),				SYS_VAR_W = GetFld(Selx,38),	 RxMode_W = GetFld(Selx,54),	Fragment_W = GetFld(Selx,28),	 NoticeType_W = GetFld(Selx,35),		TV_SYS_W = GetFld(Selx,36),		 PlanEntry_W = GetFld(Selx,50),
					SfnID_W = GetFld(Selx,52),		 AssocAllotID_W = GetFld(Selx,59),		AdmRefID_W = GetFld(Selx,33),	 Pol_W = GetFld(Selx,13),		AntDir_W = GetFld(Selx,31),		 AntCatID_W = GetFld(Selx,30),			ERP_h_dbw = GetFld(Selx,62),	 ERP_v_dbw = GetFld(Selx,63),
					Hagl_W = GetFld(Selx,5),		 SiteName_W = GetFld(Selx,2),			cty_W = GetFld(Selx,25),		 AntID_W = GetFld(Selx,20),		MaxEffHght_W = GetFld(Selx,32);
			double  Freq_W = atof(GetFld(Selx,6)),	 GeoLat_W = atof(GetFld(Selx,3)),		GeoLon_W = atof(GetFld(Selx,4));

			int CSmode = 0;
			if(UD==1)
			{
				if	   (Fragment_W!=_T("GE06A"))						CSmode = 7;
				else if(Fragment_W==_T("GE06A"))						CSmode = 8;
			}
			else
			{
				if	   ((EXA==1)&&(LNB==0))								CSmode = 1;
				else if((EXA==1)&&(LNB==1))								CSmode = 2;
				else if((EXA==0)&&(LNB==0)&&(Fragment_W!=_T("GE06A")))	CSmode = 3;
				else if((EXA==0)&&(LNB==1)&&(Fragment_W!=_T("GE06A")))	CSmode = 4;
				else if((EXA==0)&&(LNB==0)&&(Fragment_W==_T("GE06A")))	CSmode = 5;
				else if((EXA==0)&&(LNB==1)&&(Fragment_W==_T("GE06A")))	CSmode = 6;
			}

	//		double pi = 4.0*atan(1.0);
			float RLON   = (float)((pi/180.0)*(GeoLon_W)),	 RLAT   = (float)((pi/180.0)*(GeoLat_W));
	//		if(cty_W.GetLength()==1)			cty_W = cty_W + _T("  ");
	//		else if(cty_W.GetLength()==2)		cty_W = cty_W + _T(" ");
	//		CString adm_W;	GEOCTYA((BYTE *)cty_W.GetBufferSetLength(3), (BYTE *)adm_W.GetBufferSetLength(3));
			CString adm_W = Cty2AdmGE06(&cty_W);
	
			AddStation_disp(atol(IDst_W),GeoLat_W, GeoLon_W,SiteName_W) ;

			double L,Emed,Sigma_W, miu_W, UFSmin , SR,FR,Ti , kfactor = 4.0/3.0;
			int DP,AP,OS,ENV, AntDisc;
		//	int SRV_I;
			CP154606_Functions CP154606;
			CP154606.Default_CArea_0(Fragment_W, NoticeType_W, RxMode_W, RPC_W,Freq_W, TV_SYS_W, SYS_VAR_W, &L,&Emed,&AntDisc,&Sigma_W); 

			CGE06cvaDLG cvaDLG;
			Emed = Round(Emed*100.0)/100.0;
			cvaDLG.m_Emed = Emed;	cvaDLG.m_L = L;	cvaDLG.m_AntDisc = AntDisc;
			cvaDLG.m_CSdisplay = ((CSmode==3)||(CSmode==4)||(CSmode==7));
			cvaDLG.m_CSdisplay1 = (CSmode==7);

		//	cvaDLG.m_CSdisplay = ((CSmode==3)||(CSmode==4));

			if(cvaDLG.DoModal()==IDOK)
			{
				SR = cvaDLG.m_SR;		Emed = cvaDLG.m_Emed;	L = cvaDLG.m_L;		FR = cvaDLG.m_Fr;		Ti = cvaDLG.m_Ti;		AntDisc = cvaDLG.m_AntDisc;
				DP = cvaDLG.m_DP;		AP = cvaDLG.m_AP;		OS = cvaDLG.m_OS;	ENV = cvaDLG.m_env;		
			//	SRV_I = cvaDLG.m_srv;
				miu_W = CP154606.Qi(100-L);		UFSmin = Emed;

				CString STN_W = CP154606.GE06_STN(Fragment_W, NoticeType_W);
				int PEC_W = GE06_PEC(AdmRefID_W , AssocAllotID_W , PlanEntry_W , SfnID_W , STN_W) ;
				CString NET_W;	NET_W.Format("%s%d",STN_W,PEC_W);
				////////////////////////////////////
				int az0[37];	for(int i=0;i<=36;i++)		az0[i] = 10*i;
	/*
				double attH0[37], attV0[37];
				if(AntDir_W==_T("D"))
					GE84pattern(atol(AntCatID_W),attH0,attV0,Pol_W);
				else
					for(int i=0;i<36;i++)	{	attH0[i] = 0;	attV0[i] = 0;	}
				attH0[36] = attH0[0];	attV0[36] = attV0[0];
	*/
				double attH0[361], attV0[361];
				GE06patternT(atol(AntCatID_W), AntDir_W, Pol_W,attH0,attV0); 

				OnDatabaseStationsindesktop2(GeoLat_W, GeoLon_W);
				double Hasl_W = LatLon2Hg(GeoLat_W, GeoLon_W);
				double Hasgl_W = Hasl_W + atof(Hagl_W);

				double h1dkm[37][15];
				for(long j=0;j<(360/AZstep);j++)		h1dkm[j][0] = atof(Hagl_W);

				double latC_deg, lonC_deg, attnH, attnV, ERP , d_km, Em , h1, lat3km, lon3km, lat15km, lon15km , azz,az_W;
				double latContour_deg[37],	lonContour_deg[37] , h1_15[37], h10[37], EmWNL[37];
				int progress_num = 0;
				CString progress_str, progress_char = _T("I");
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

				LoadMap_IDWMpr(4,GeoLat_W, GeoLon_W , 1500.0); 

				if((CSmode != 7)&&(CSmode != 8))
				{
					if(hef_flag)
					{
						for(long i=0;i<(360/AZstep);i++)
						{
							azz = (double)(i*AZstep);
							reckon(GeoLat_W, GeoLon_W,  3.0 , azz , &lat3km  , &lon3km) ;
							reckon(GeoLat_W, GeoLon_W, 15.0 , azz , &lat15km , &lon15km) ;
							h1_15[i] = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}
					}
				}
				double C2S = 0;
				if((CSmode == 3)||(CSmode == 4)||(CSmode == 5)||(CSmode == 6))	C2S = 3;

	////////////////////////////////////////////////////////////////////////
				if(CSmode == 7)
				{
					long NPoint = m_PolyPointNum;
					if(NPoint>2)
					{
						double *latP;		latP = new double[NPoint];
						double *lonP;		lonP = new double[NPoint];
						double *EmWUD;		EmWUD = new double[NPoint];
						progress_num = 0;
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						for(long i=0; i<NPoint ;i++)
						{
							double Lat1, Lon1;
							CPoint point1 = m_PolyPoint[i];
							Point2LatLon(point1,&Lat1,&Lon1);
							az_W = Azimuth_Deg(GeoLat_W, GeoLon_W,Lat1,Lon1);
							d_km = Distance_km(GeoLat_W, GeoLon_W,Lat1,Lon1);

						//	attnH = Interp2(az0,attH0,az_W,37)+C2S;		attnV = Interp2(az0,attV0,az_W,37)+C2S;
							attnH = attH0[(int)az_W]+C2S;				attnV = attV0[(int)az_W]+C2S;

							if     (Pol_W==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
							else if(Pol_W==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
							else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	ERP = max(atof(ERP_h_dbw)-attnH , atof(ERP_v_dbw)-attnV);
							if(!(hef_flag))
							{
								GE84Heff(atol(AntID_W),atof(MaxEffHght_W),h10) ;
								h10[36] = h10[0];
								h1 = Interp2(az0,h10,az_W,37) ;
							}
							else
							{
								if (d_km>=15.0)
								{
									reckon(GeoLat_W, GeoLon_W,  3.0 , az_W , &lat3km  , &lon3km) ;
									reckon(GeoLat_W, GeoLon_W, 15.0 , az_W , &lat15km , &lon15km) ;
									h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km);
								}
								else
								{
									reckon(GeoLat_W, GeoLon_W, 0.2*d_km , az_W , &lat3km  , &lon3km) ;
									reckon(GeoLat_W, GeoLon_W,     d_km , az_W , &lat15km , &lon15km) ;
									h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
								}
							}
							Em = E_P1546_06(GeoLat_W, GeoLon_W,Lat1,Lon1, h1, Hasgl_W, Freq_W, kfactor, 50, 10, ENV,0,50, 0);
							Em = Em - 30.0 + ERP;
							latP[i] = Lat1;			lonP[i] = Lon1;		EmWUD[i] = Em;

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(NPoint)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(NPoint)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}//for i NPoint
						CString FileName;
						AdmRefID_W.Replace('/','_');

						FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<NPoint;i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonP[i], latP[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonP[0], latP[0]);
						fclose(fpOUT);
						FileNameTP = FileName;

						FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						fpOUT = fopen(FileName,"wt");
						for( i=0;i<NPoint;i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin,EmWUD[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin,EmWUD[0]);
						fclose(fpOUT);
						CSArea_Table(IDst_W, SiteName_W,latP,lonP,UFSmin,EmWUD,NPoint) ;
						delete [] latP;		delete [] lonP;		delete [] EmWUD;
					}//if(m_NPoint>2)
				//	return;
					break;
				}//if(CSmode == 7)
	////////////////////////////////////////////////////////////////////////

				progress_num = 0;
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
				for(int az = 0; az<(360/AZstep) ; az++)
				{
					az_W = (double)(az*AZstep);
				//	attnH = Interp2(az0,attH0,az_W,37)+C2S;		attnV = Interp2(az0,attV0,az_W,37)+C2S;
					attnH = attH0[az*AZstep]+C2S;				attnV = attV0[az*AZstep]+C2S;

					if     (Pol_W==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
					else if(Pol_W==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
					else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	ERP = max(atof(ERP_h_dbw)-attnH , atof(ERP_v_dbw)-attnV);
					if(!(hef_flag))
					{
						GE84Heff(atol(AntID_W),atof(MaxEffHght_W),h10) ;
						h10[36] = h10[0];
						h1 = Interp2(az0,h10,az_W,37) ;
					}
					d_km = 1.0;		Em = 9999.0;
					while(Em>UFSmin)
					{
						reckon(GeoLat_W, GeoLon_W, d_km , az_W, &latC_deg, &lonC_deg) ;
						/////////////////////////// h1 //////////////////////
						if(hef_flag)
						{
							if (d_km>=15.0)		h1 = h1_15[az];
							else
							{
								reckon(GeoLat_W, GeoLon_W, 0.2*d_km , az_W , &lat3km  , &lon3km) ;
								reckon(GeoLat_W, GeoLon_W,     d_km , az_W , &lat15km , &lon15km) ;
								h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
								int dist00 = (int)Round(d_km);
								h1dkm[az][dist00] = h1;
							}
						}
						Em = E_P1546_06(GeoLat_W, GeoLon_W,latC_deg,lonC_deg, h1, Hasgl_W, Freq_W, kfactor, 50, 10, ENV,0,50, 0);
						Em = Em - 30.0 + ERP;
						if(Em<=UFSmin)
						{
							latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	EmWNL[az] = Em;
						}
						else
						{
							d_km = d_km + 1.0;
							if(d_km>=SR)
							{
								latContour_deg[az] = latC_deg;	lonContour_deg[az] = lonC_deg;	EmWNL[az] = Em;
								Em = -999.0;
							}
						}
					}//while
					progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
				}//for az
				CString FileName;
				AdmRefID_W.Replace('/','_');

				if(CSmode==0)
				{
					FileName.Format("%sReports\\%s_%s_%s_NLCVA.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
					FILE *fpOUT = fopen(FileName,"wt");
					for( i=0;i<(360/AZstep);i++)
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
					fclose(fpOUT);
					FileNameNL = FileName;

				}//if(CSmode==0)
				else if(CSmode==3)
				{
					FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
					FILE *fpOUT = fopen(FileName,"wt");
					for( i=0;i<(360/AZstep);i++)
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
					fclose(fpOUT);
					FileNameTP = FileName;

					FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
					fpOUT = fopen(FileName,"wt");
					for( i=0;i<(360/AZstep);i++)
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin,EmWNL[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin,EmWNL[0]);
					fclose(fpOUT);
					CSArea_Table(IDst_W, SiteName_W,latContour_deg,lonContour_deg,UFSmin,EmWNL,(360/AZstep)) ;
				//	return;
					break;
				}//if(CSmode==3)
				else if(CSmode==4)
				{
					double latNL[37], lonNL[37];
					progress_num=0;
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					for(int az = 0; az<(360/AZstep) ; az++)
					{
						double latTest, lonTest , dZ = 0;
						az_W = (double)(az*AZstep);
						double az_Con2W = Azimuth_Deg(latContour_deg[az], lonContour_deg[az],GeoLat_W,GeoLon_W) ;
						double d_Con2W =  Distance_km(latContour_deg[az], lonContour_deg[az],GeoLat_W,GeoLon_W) ;
						int flagTest=0;
						while(flagTest==0)
						{
							reckon(latContour_deg[az], lonContour_deg[az], dZ , az_Con2W, &latTest, &lonTest) ;
							float RLON1 = (float)((pi/180.0)*lonTest), RLAT1 = (float)((pi/180.0)*latTest);
							CString ctyTest("");		GEOPLC(&RLON1, &RLAT1, (BYTE*)ctyTest.GetBufferSetLength(3));
							
							if(ctyTest==cty_W)	flagTest = 1;
							else
							{
								dZ = dZ + 0.1;
								if(dZ>d_Con2W)	flagTest = 1;
							}
						}
						double d_Test2W =  Distance_km(latTest, lonTest,GeoLat_W,GeoLon_W) ;
				//		attnH = Interp2(az0,attH0,az_W,37)+C2S;		attnV = Interp2(az0,attV0,az_W,37)+C2S;
						attnH = attH0[az*AZstep]+C2S;				attnV = attV0[az*AZstep]+C2S;

						if     (Pol_W==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
						else if(Pol_W==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
						else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	ERP = max(atof(ERP_h_dbw)-attnH , atof(ERP_v_dbw)-attnV);
						if(!(hef_flag))
						{
							GE84Heff(atol(AntID_W),atof(MaxEffHght_W),h10) ;
							h10[36] = h10[0];
							h1 = Interp2(az0,h10,az_W,37) ;
						}
						else
						{
							if (d_Test2W>=15.0)		h1 = h1_15[az];
							else
							{
						//		reckon(GeoLat_W, GeoLon_W, 0.2*d_Test2W , az_W , &lat3km  , &lon3km) ;
						//		reckon(GeoLat_W, GeoLon_W,     d_Test2W , az_W , &lat15km , &lon15km) ;
						//		h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
								int dist00 = (int)Round(d_Test2W);
								h1 = h1dkm[az][dist00];
							}
						}
						Em = E_P1546_06(GeoLat_W, GeoLon_W,latTest, lonTest, h1, Hasgl_W, Freq_W, kfactor, 50, 10, ENV,0,50, 0);
						Em = Em - 30.0 + ERP;
						latNL[az] = latTest;	lonNL[az] = lonTest;	EmWNL[az] = Em;

						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					}//for az
					FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
					FILE *fpOUT = fopen(FileName,"wt");
					for( i=0;i<(360/AZstep);i++)
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonNL[i], latNL[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonNL[0], latNL[0]);
					fclose(fpOUT);
					FileNameTP = FileName;

					FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
					fpOUT = fopen(FileName,"wt");
					for( i=0;i<(360/AZstep);i++)
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin,EmWNL[i]);
						fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin,EmWNL[0]);
					fclose(fpOUT);
					CSArea_Table(IDst_W, SiteName_W,latNL,lonNL,UFSmin,EmWNL,(360/AZstep)) ;
			//		return;
					break;
				}//if(CSmode==4)

		//////////////////////////////////////////////////////////////////////
				int Nrowy = QGE06_CArea_Qy(IDst_W,GeoLat_W, GeoLon_W,SR,Freq_W,FR, DP,AP,OS,PEC_W, SfnID_W,AssocAllotID_W,Fragment_W) ;
				if(Nrowy>0)
				{
					double latIL[37], lonIL[37] , latCal, lonCal , dC , UFSIL[37], EmWIL[37];
					CString TV_ch_W = GetFld(Selx,44);				CString TV_COLOR_W = GetFld(Selx,40);
					CString oset_v_12_W = GetFld(Selx,42);			CString oset_v_khz_W = GetFld(Selx,43);		CString freq_stabl_W = GetFld(Selx,45);
					double  freq_vcarr_W = atof(GetFld(Selx,39));	double  freq_scarr_W = atof(GetFld(Selx,41));
					if(CSmode==5)
					{
						double UFS_5[37];
						for(int az = 0; az<(360/AZstep) ; az++)
							UFS_5[az] = GE06UFS(Nrowy, Fragment_W, NoticeType_W, Freq_W,TV_SYS_W, RPC_W, SYS_VAR_W, freq_vcarr_W, TV_COLOR_W, freq_scarr_W, oset_v_12_W, oset_v_khz_W, TV_ch_W, RxMode_W, freq_stabl_W, miu_W, Sigma_W, GeoLat_W, GeoLon_W, Pol_W, latContour_deg[az],lonContour_deg[az], AntDisc, ENV, Ti, kfactor, UFSmin);

						FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
						fclose(fpOUT);
						FileNameTP = FileName;

						FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFS_5[i], EmWNL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFS_5[0], EmWNL[0]);
						fclose(fpOUT);
						CSArea_Table(IDst_W, SiteName_W,latContour_deg,lonContour_deg,UFS_5,EmWNL,(360/AZstep)) ;
					//	return;
						break;
					}//if(CSmode==5)
					else if(CSmode==6)
					{
						double latNL[37], lonNL[37] , UFS_5[37];
						progress_num=0;
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						for(int az = 0; az<(360/AZstep) ; az++)
						{
							double latTest, lonTest , dZ = 0;
							az_W = (double)(az*AZstep);
							double az_Con2W = Azimuth_Deg(latContour_deg[az], lonContour_deg[az],GeoLat_W,GeoLon_W) ;
							double d_Con2W =  Distance_km(latContour_deg[az], lonContour_deg[az],GeoLat_W,GeoLon_W) ;
							int flagTest=0;
							while(flagTest==0)
							{
								reckon(latContour_deg[az], lonContour_deg[az], dZ , az_Con2W, &latTest, &lonTest) ;
								float RLON1 = (float)((pi/180.0)*lonTest), RLAT1 = (float)((pi/180.0)*latTest);
								CString ctyTest("");		GEOPLC(&RLON1, &RLAT1, (BYTE*)ctyTest.GetBufferSetLength(3));
								
								if(ctyTest==cty_W)	flagTest = 1;
								else
								{
									dZ = dZ + 0.1;
									if(dZ>d_Con2W)	flagTest = 1;
								}
							}
							double d_Test2W =  Distance_km(latTest, lonTest,GeoLat_W,GeoLon_W) ;
						//	attnH = Interp2(az0,attH0,az_W,37)+C2S;		attnV = Interp2(az0,attV0,az_W,37)+C2S;
							attnH = attH0[az*AZstep]+C2S;	attnV = attV0[az*AZstep]+C2S;

							if     (Pol_W==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
							else if(Pol_W==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
							else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	ERP = max(atof(ERP_h_dbw)-attnH , atof(ERP_v_dbw)-attnV);
							if(!(hef_flag))
							{
								GE84Heff(atol(AntID_W),atof(MaxEffHght_W),h10) ;
								h10[36] = h10[0];
								h1 = Interp2(az0,h10,az_W,37) ;
							}
							else
							{
								if (d_Test2W>=15.0)		h1 = h1_15[az];
								else
								{
							//		reckon(GeoLat_W, GeoLon_W, 0.2*d_Test2W , az_W , &lat3km  , &lon3km) ;
							//		reckon(GeoLat_W, GeoLon_W,     d_Test2W , az_W , &lat15km , &lon15km) ;
							//		h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
									int dist00 = (int)Round(d_Test2W);
									h1 = h1dkm[az][dist00];
								}
							}
							Em = E_P1546_06(GeoLat_W, GeoLon_W,latTest, lonTest, h1, Hasgl_W, Freq_W, kfactor, 50, 10, ENV,0,50, 0);
							Em = Em - 30.0 + ERP;
							latNL[az] = latTest;	lonNL[az] = lonTest;	EmWNL[az] = Em;
							UFS_5[az] = GE06UFS(Nrowy, Fragment_W, NoticeType_W, Freq_W,TV_SYS_W, RPC_W, SYS_VAR_W, freq_vcarr_W, TV_COLOR_W, freq_scarr_W, oset_v_12_W, oset_v_khz_W, TV_ch_W, RxMode_W, freq_stabl_W, miu_W, Sigma_W, GeoLat_W, GeoLon_W, Pol_W, latTest,lonTest, AntDisc, ENV, Ti, kfactor, UFSmin);

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}//for az
						FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonNL[i], latNL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonNL[0], latNL[0]);
						fclose(fpOUT);
						FileNameTP = FileName;
						
						FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFS_5[i], EmWNL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFS_5[0], EmWNL[0]);
						fclose(fpOUT);
						CSArea_Table(IDst_W, SiteName_W,latNL,lonNL,UFS_5,EmWNL,(360/AZstep)) ;
					//	return;
						break;
					}//if(CSmode==6)

	////////////////////////////////////////////////////////////////////////
					if(CSmode == 8)
					{
						long NPoint = m_PolyPointNum;
						if(NPoint>2)
						{
							double *latP;		latP = new double[NPoint];
							double *lonP;		lonP = new double[NPoint];
							double *EmWUD;		EmWUD = new double[NPoint];
							double *UFS_5;		UFS_5 = new double[NPoint];

							progress_num = 0;
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
							for(long i=0; i<NPoint ;i++)
							{
								double Lat1, Lon1;
								CPoint point1 = m_PolyPoint[i];
								Point2LatLon(point1,&Lat1,&Lon1);

								az_W = Azimuth_Deg(GeoLat_W, GeoLon_W,Lat1,Lon1);
								d_km = Distance_km(GeoLat_W, GeoLon_W,Lat1,Lon1);

						//		attnH = Interp2(az0,attH0,az_W,37)+C2S;		attnV = Interp2(az0,attV0,az_W,37)+C2S;
								attnH = attH0[(int)az_W]+C2S;	attnV = attV0[(int)az_W]+C2S;

								if     (Pol_W==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
								else if(Pol_W==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
								else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	ERP = max(atof(ERP_h_dbw)-attnH , atof(ERP_v_dbw)-attnV);
								if(!(hef_flag))
								{
									GE84Heff(atol(AntID_W),atof(MaxEffHght_W),h10) ;
									h10[36] = h10[0];
									h1 = Interp2(az0,h10,az_W,37) ;
								}
								else
								{
									if (d_km>=15.0)
									{
										reckon(GeoLat_W, GeoLon_W,  3.0 , az_W , &lat3km  , &lon3km) ;
										reckon(GeoLat_W, GeoLon_W, 15.0 , az_W , &lat15km , &lon15km) ;
										h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
									}
									else
									{
										reckon(GeoLat_W, GeoLon_W, 0.2*d_km , az_W , &lat3km  , &lon3km) ;
										reckon(GeoLat_W, GeoLon_W,     d_km , az_W , &lat15km , &lon15km) ;
										h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
									}
								}
								Em = E_P1546_06(GeoLat_W, GeoLon_W,Lat1,Lon1, h1, Hasgl_W, Freq_W, kfactor, 50, 10, ENV,0,50, 0);
								Em = Em - 30.0 + ERP;
						
								latP[i] = Lat1;			lonP[i] = Lon1;			EmWUD[i] = Em;
								UFS_5[i] = GE06UFS(Nrowy, Fragment_W, NoticeType_W, Freq_W,TV_SYS_W, RPC_W, SYS_VAR_W, freq_vcarr_W, TV_COLOR_W, freq_scarr_W, oset_v_12_W, oset_v_khz_W, TV_ch_W, RxMode_W, freq_stabl_W, miu_W, Sigma_W, GeoLat_W, GeoLon_W, Pol_W, Lat1,Lon1, AntDisc, ENV, Ti, kfactor, UFSmin);

								progress_char = str_rep("I",(int)((++progress_num)*50.0/(NPoint)) );
								progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(NPoint)),progress_char);
								PeekAndPump();
								((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

							}//for i NPoint
							CString FileName;
							AdmRefID_W.Replace('/','_');

							FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
							FILE *fpOUT = fopen(FileName,"wt");
							for( i=0;i<NPoint;i++)
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonP[i], latP[i]);
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonP[0], latP[0]);
							fclose(fpOUT);
							FileNameTP = FileName;

							FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
							fpOUT = fopen(FileName,"wt");
							for( i=0;i<NPoint;i++)
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFS_5[i],EmWUD[i]);
								fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFS_5[0],EmWUD[0]);
							fclose(fpOUT);
							CSArea_Table(IDst_W, SiteName_W,latP,lonP,UFS_5,EmWUD,NPoint) ;
							delete [] latP;		delete [] lonP;		delete [] EmWUD;		delete [] UFS_5;
						}//if(m_NPoint>2)
				//		return;
						break;
					}//if(CSmode == 8)
	////////////////////////////////////////////////////////////////////////

					CDatabase DB1;
					CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
					DB1.Open(_T(m_DB),false,false,_T("ODBC;"),false);

					progress_num=0;
					progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
					PeekAndPump();
					((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					for(int azi = 0; azi<(360/AZstep) ; azi++)
					{
						az_W = (double)(azi*AZstep);
				//		attnH = Interp2(az0,attH0,az_W,37);			attnV = Interp2(az0,attV0,az_W,37);
						attnH = attH0[azi*AZstep];					attnV = attV0[azi*AZstep];

						if     (Pol_W==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
						else if(Pol_W==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
						else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	ERP = max(atof(ERP_h_dbw)-attnH , atof(ERP_v_dbw)-attnV);
						if(!(hef_flag))
						{
							GE84Heff(atol(AntID_W),atof(MaxEffHght_W),h10) ;
							h10[36] = h10[0];
							h1 = Interp2(az0,h10,az_W,37) ;
						}
						double az_Cont2W = Azimuth_Deg(latContour_deg[azi],lonContour_deg[azi],GeoLat_W,GeoLon_W) ;
						double dist1 = Distance_km(latContour_deg[azi],lonContour_deg[azi],GeoLat_W,GeoLon_W);
					
						double UFS1 = GE06UFS1(Nrowy, Fragment_W, NoticeType_W, Freq_W,TV_SYS_W, RPC_W, SYS_VAR_W,
										freq_vcarr_W, TV_COLOR_W, freq_scarr_W, oset_v_12_W, oset_v_khz_W,
										TV_ch_W, RxMode_W, freq_stabl_W, miu_W, Sigma_W, GeoLat_W, GeoLon_W,
										Pol_W, latContour_deg[azi], lonContour_deg[azi], AntDisc, ENV, Ti, kfactor, UFSmin,0,&DB1);

						dC = 0;
						double EmW = -99999 , UFS = 99999;
						while(EmW<UFS)
						{
							reckon(latContour_deg[azi],lonContour_deg[azi],  dC , az_Cont2W , &latCal, &lonCal) ;
					//		double dist0 = Distance_km(GeoLat_W,GeoLon_W, latCal, lonCal);
							double dist0 = dist1 - dC;
							
							if(hef_flag)
							{
								if (dist0>=15.0)		h1 = h1_15[azi];
								else
								{
							//		reckon(GeoLat_W, GeoLon_W, 0.2*dist0 , az_W , &lat3km  , &lon3km) ;
							//		reckon(GeoLat_W, GeoLon_W,     dist0 , az_W , &lat15km , &lon15km) ;
							//		h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
									int dist00 = (int)Round(dist0);
									h1 = h1dkm[azi][dist00];
								}
							}
							EmW = E_P1546_06(GeoLat_W, GeoLon_W,latCal, lonCal, h1, Hasgl_W, Freq_W, kfactor, 50, 10, ENV,0,50, 0);
							EmW = EmW - 30.0 + ERP;
						
							if(dC==0)	UFS = UFS1;
							else		UFS = GE06UFS1(Nrowy, Fragment_W, NoticeType_W, Freq_W,TV_SYS_W, RPC_W, SYS_VAR_W,
											freq_vcarr_W, TV_COLOR_W, freq_scarr_W, oset_v_12_W, oset_v_khz_W,
											TV_ch_W, RxMode_W, freq_stabl_W, miu_W, Sigma_W, GeoLat_W, GeoLon_W,
											Pol_W, latCal, lonCal, AntDisc, ENV, Ti, kfactor, UFSmin,1,&DB1);

							if(EmW>=UFS)
							{
								if((CSmode==0)||(CSmode==1))
								{
									latIL[azi] = latCal; lonIL[azi] = lonCal; UFSIL[azi] = UFS; EmWIL[azi] = EmW;
								}
								else if(CSmode==2)
								{
									float RLON1 = (float)((pi/180.0)*lonCal), RLAT1 = (float)((pi/180.0)*latCal);
									CString ctyTest("");		GEOPLC(&RLON1, &RLAT1, (BYTE*)ctyTest.GetBufferSetLength(3));
									if(ctyTest==cty_W)
									{
										latIL[azi] = latCal; lonIL[azi] = lonCal; UFSIL[azi] = UFS; EmWIL[azi] = EmW;
									}
									else
									{
										dC = dC + 1.0;
										if(dC>(dist1-0.001))
										{
											latIL[azi] = latCal; lonIL[azi] = lonCal; UFSIL[azi] = UFS; EmWIL[azi] = EmW;
											UFS = -9999.0;
										}
										else	UFS = +9999.0;
									}
								}//if CSmode
							}
							else
							{
								dC = dC + 1.0;
								if(dC>(dist1-0.001))
								{
									latIL[azi] = latCal; lonIL[azi] = lonCal; UFSIL[azi] = UFS; EmWIL[azi] = EmW;
									UFS = -9999.0;
								}
							}
						}//while  (EmW<UFS)
						progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
					}//for azi
					DB1.Close();

					if(CSmode==0)
					{
						FileName.Format("%sReports\\%s_%s_%s_ILCVA.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonIL[i], latIL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonIL[0], latIL[0]);
						fclose(fpOUT);
						FileNameIL = FileName;
					}
					else if((CSmode==1)||(CSmode==2))
					{
						FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonIL[i], latIL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonIL[0], latIL[0]);
						fclose(fpOUT);
						FileNameTP = FileName;

						FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSIL[i], EmWIL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSIL[0], EmWIL[0]);
						fclose(fpOUT);
						CSArea_Table(IDst_W, SiteName_W,latIL,lonIL,UFSIL,EmWIL,(360/AZstep)) ;
					}
				}//if Nrowy
				else
				{
					if((CSmode==5)||(CSmode==1))
					{
						FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[i], latContour_deg[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonContour_deg[0], latContour_deg[0]);
						fclose(fpOUT);
						FileNameTP = FileName;

						FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin, EmWNL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin, EmWNL[0]);
						fclose(fpOUT);
						CSArea_Table(IDst_W, SiteName_W,latContour_deg,lonContour_deg,UFSmin,EmWNL,(360/AZstep)) ;
				//		return;
						break;
					}//if(CSmode==5)
					else if((CSmode==6)||(CSmode==2))
					{
						double latNL[37], lonNL[37];
						progress_num=0;
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
						PeekAndPump();
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						for(int az = 0; az<(360/AZstep) ; az++)
						{
							double latTest, lonTest , dZ = 0;
							az_W = (double)(az*AZstep);
							double az_Con2W = Azimuth_Deg(latContour_deg[az], lonContour_deg[az],GeoLat_W,GeoLon_W) ;
							double d_Con2W =  Distance_km(latContour_deg[az], lonContour_deg[az],GeoLat_W,GeoLon_W) ;
							int flagTest=0;
							while(flagTest==0)
							{
								reckon(latContour_deg[az], lonContour_deg[az], dZ , az_Con2W, &latTest, &lonTest) ;
								float RLON1 = (float)((pi/180.0)*lonTest), RLAT1 = (float)((pi/180.0)*latTest);
								CString ctyTest("");	GEOPLC(&RLON1, &RLAT1, (BYTE*)ctyTest.GetBufferSetLength(3));
								
								if(ctyTest==cty_W)	flagTest = 1;
								else
								{
									dZ = dZ + 0.1;
									if(dZ>d_Con2W)	flagTest = 1;
								}
							}
							double d_Test2W =  Distance_km(latTest, lonTest,GeoLat_W,GeoLon_W) ;
						//	attnH = Interp2(az0,attH0,az_W,37)+C2S;		attnV = Interp2(az0,attV0,az_W,37)+C2S;
							attnH = attH0[az*AZstep]+C2S;	attnV = attV0[az*AZstep]+C2S;

							if     (Pol_W==_T("H"))						ERP = atof(ERP_h_dbw)-attnH;
							else if(Pol_W==_T("V"))						ERP = atof(ERP_v_dbw)-attnV;
							else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	ERP = max(atof(ERP_h_dbw)-attnH , atof(ERP_v_dbw)-attnV);
							if(!(hef_flag))
							{
								GE84Heff(atol(AntID_W),atof(MaxEffHght_W),h10) ;
								h10[36] = h10[0];
								h1 = Interp2(az0,h10,az_W,37) ;
							}
							else
							{
								if (d_Test2W>=15.0)		h1 = h1_15[az];
								else
								{
							//		reckon(GeoLat_W, GeoLon_W, 0.2*d_Test2W , az_W , &lat3km  , &lon3km) ;
							//		reckon(GeoLat_W, GeoLon_W,     d_Test2W , az_W , &lat15km , &lon15km) ;
							//		h1 = Hasgl_W - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km,120);
									int dist00 = (int)Round(d_Test2W);
									h1 = h1dkm[az][dist00];
								}
							}
							Em = E_P1546_06(GeoLat_W, GeoLon_W,latTest, lonTest, h1, Hasgl_W, Freq_W, kfactor, 50, 10, ENV,0,50, 0);
							Em = Em - 30.0 + ERP;
							latNL[az] = latTest;	lonNL[az] = lonTest;	EmWNL[az] = Em;

							progress_char = str_rep("I",(int)((++progress_num)*50.0/(360.0/AZstep)) );
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(360.0/AZstep)),progress_char);
							PeekAndPump();
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
						}//for az
						FileName.Format("%sReports\\%s_%s_%s_SraTP.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						FILE *fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonNL[i], latNL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , lonNL[0], latNL[0]);
						fclose(fpOUT);
						FileNameTP = FileName;

						FileName.Format("%sReports\\%s_%s_%s_SraUE.txt",m_AppPath,IDst_W,cty_W,AdmRefID_W);
						fpOUT = fopen(FileName,"wt");
						for( i=0;i<(360/AZstep);i++)
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin, EmWNL[i]);
							fprintf(fpOUT," %0.14lf    %0.14lf\n" , UFSmin, EmWNL[0]);
						fclose(fpOUT);
						CSArea_Table(IDst_W, SiteName_W,latNL,lonNL,UFSmin,EmWNL,(360/AZstep)) ;
					//	return;
						break;
					}//if(CSmode==6)
				}//else Nrowy
		////////////////////////////////////////////////////////////////////////
			}//if cvaDLG
		}//if Selx
		Set_STtable_Default();
		EndWaitCursor();

		break;
	}
	FileNameNL = ((CSMS4DCApp *)AfxGetApp())->VectorFileNameSave( FileNameNL);
	if(FileNameNL.GetLength()>0)	OnDrawVector(FileNameNL);
	FileNameIL = ((CSMS4DCApp *)AfxGetApp())->VectorFileNameSave( FileNameIL);
	if(FileNameIL.GetLength()>0)	OnDrawVector(FileNameIL);
	FileNameTP = ((CSMS4DCApp *)AfxGetApp())->VectorFileNameSave( FileNameTP);
	if(FileNameTP.GetLength()>0)	OnDrawVector(FileNameTP,2);
	if(m_GoogleFlag)
	{
		if(MessageBox(_Z("Do you want to save the vector(s)\t\n in Google file format?"),_Z("Google File Format"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			if(FileNameNL.GetLength()>0)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileNameNL);
			if(FileNameIL.GetLength()>0)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileNameIL);
			if(FileNameTP.GetLength()>0)	GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , FileNameTP);
		}
	}
}


void CSMS4DCView::CSArea_Table(CString IDst, CString Name,double Lat[],double Lon[],double UFS[],double Em[],int Num) 
{
	int SaveYes = MessageBox(_Z("Do you want to save this vector\t\n into Database?"),_Z("Save Vector"),MB_YESNO | MB_ICONQUESTION);
	if(SaveYes==IDYES)
	{
		CDatabase DB1;
		CString  SQL1 , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
		DB1.Open(_T(m_DB),false,false,_T("ODBC;"),false);

		SQL1.Format(_T("DELETE * FROM CSArea WHERE (((IDst)=%ld));") , atol(IDst));	DB1.ExecuteSQL(SQL1);
		for(int i=0;i<Num;i++)
		{
			SQL1.Format(_T("SELECT %ld,'%s',%lf,%lf,%lf,%lf "), atol(IDst), Name,Lat[i], Lon[i],UFS[i],Em[i]);
			SQL1 = _T("INSERT INTO CSArea (IDst, SiteName, GeoLat, GeoLon, UFS, Em) ") + SQL1;
			DB1.ExecuteSQL(SQL1);
		}
		DB1.Close();
	}
}
void CSMS4DCView::CSArea_Table(CString IDst, CString Name,double Lat[],double Lon[],double UFS,double Em[],int Num) 
{
	int SaveYes = MessageBox(_Z("Do you want to save this vector\t\n into Database?"),_Z("Save Vector"),MB_YESNO | MB_ICONQUESTION);
	if(SaveYes==IDYES)
	{
		CDatabase DB1;
		CString  SQL1 , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
		DB1.Open(_T(m_DB),false,false,_T("ODBC;"),false);

		SQL1.Format(_T("DELETE * FROM CSArea WHERE (((IDst)=%ld));") , atol(IDst));	DB1.ExecuteSQL(SQL1);
		for(int i=0;i<Num;i++)
		{
			SQL1.Format(_T("SELECT %ld,'%s',%lf,%lf,%lf,%lf "), atol(IDst), Name,Lat[i], Lon[i],UFS,Em[i]);
			SQL1 = _T("INSERT INTO CSArea (IDst, SiteName, GeoLat, GeoLon, UFS, Em) ") + SQL1;
			DB1.ExecuteSQL(SQL1);
		}
		DB1.Close();
	}
}

void CSMS4DCView::OnCoordinationGe06Servicearea() 
{
	CGE06srvDLG	srvDLG;
	srvDLG.m_UDdisplay = (m_PolyPointNum>0);
	if(srvDLG.DoModal()==IDOK)
	{
		int AZstep = srvDLG.m_AZstep,	EXA = srvDLG.m_EXA,		LNB = srvDLG.m_LNB,	UD = srvDLG.m_UD;
		GE06CoverageArea(EXA, LNB, AZstep , UD);
	}//srvDLG
	Set_STtable_Default();
}

CString CSMS4DCView::QGE06_Digital_Qx(int flagC) 
{
	CString CDataBaseSTR, Selx = _T("");
//	if(flagC==1)	CDataBaseSTR = _T("SELECT * FROM CommonFields WHERE (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT1' Or (NoticeType)='GT1' Or (NoticeType)='DS1' Or (NoticeType)='GS1') AND ((AssignCode)='C') AND ((SfnID) Is Not Null And (SfnID)<>'')) OR (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT2' Or (NoticeType)='GT2' Or (NoticeType)='DS2' Or (NoticeType)='GS2') AND ((SfnID) Is Not Null And (SfnID)<>''));");
//	else			CDataBaseSTR = _T("SELECT * FROM CommonFields WHERE (((Fragment)='RC06' Or (Fragment)='GE06D') AND ((NoticeType)='DS2' Or (NoticeType)='GS2' Or (NoticeType)='DT2' Or (NoticeType)='GT2')) OR (((Fragment)='RC06' Or (Fragment)='GE06D') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode) Is Null Or (AssignCode)='L' Or (AssignCode)='S' Or (AssignCode)=''));");
	if(flagC==1)	CDataBaseSTR.Format( _T("SELECT * FROM %s WHERE (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT1' Or (NoticeType)='GT1' Or (NoticeType)='DS1' Or (NoticeType)='GS1') AND ((AssignCode)='C') AND ((SfnID) Is Not Null And (SfnID)<>'')) OR (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT2' Or (NoticeType)='GT2' Or (NoticeType)='DS2' Or (NoticeType)='GS2') AND ((SfnID) Is Not Null And (SfnID)<>''));") , m_qCommonFields);
	else			CDataBaseSTR.Format( _T("SELECT * FROM %s WHERE (((Fragment)='RC06' Or (Fragment)='GE06D') AND ((NoticeType)='DS2' Or (NoticeType)='GS2' Or (NoticeType)='DT2' Or (NoticeType)='GT2')) OR (((Fragment)='RC06' Or (Fragment)='GE06D') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode) Is Null Or (AssignCode)='L' Or (AssignCode)='S' Or (AssignCode)=''));") , m_qCommonFields);
	
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	CDataBaseLDLG datadlg;
	if(flagC==1)	datadlg.m_Title = _T("Select One Converted Assignment / Allotment");
	else			datadlg.m_Title = _T("Select One Assignment / Allotment");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
		else
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
		}
	}
	return Selx;
}
void CSMS4DCView::QGE06_Digital_Qy(CString IDst, int PEC, CString NoticeType, CString SfnID, CString allotkey,CString AdmRefID,CString AssocAllotID,CString STN,int flagC) 
{
	CString CDataBaseSTR, Title;
	if(flagC==1)
	{
		if(IDst==_T("---"))		Title.Format(_Z("Source Allotment : IDst = %s ,  Notice Type = %s , PEC = %ld , SfnID = %s , allotkey = %s"),IDst,NoticeType,PEC,SfnID,allotkey);
		else					Title.Format(_Z("Converted Assignment : IDst = %s ,  Notice Type = %s , PEC = %ld , SfnID = %s , allotkey = %s"),IDst,NoticeType,PEC,SfnID,allotkey);
//		CDataBaseSTR.Format(_T("SELECT * FROM CommonFields WHERE (((Fragment)='RC06' Or (Fragment)='GE06D') AND ((NoticeType)='DS2' Or (NoticeType)='GS2' Or (NoticeType)='DT2' Or (NoticeType)='GT2') AND ((SfnID)=\'%s\')) OR (((Fragment)='RC06' Or (Fragment)='GE06D') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='C') AND ((SfnID)=\'%s\'));"), SfnID, SfnID); 
		CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='RC06' Or (Fragment)='GE06D') AND ((NoticeType)='DS2' Or (NoticeType)='GS2' Or (NoticeType)='DT2' Or (NoticeType)='GT2') AND ((SfnID)=\'%s\')) OR (((Fragment)='RC06' Or (Fragment)='GE06D') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='C') AND ((SfnID)=\'%s\'));"), m_qCommonFields,SfnID, SfnID); 
	}
	else
	{
		if(PEC==1)
		{
			Title.Format(_Z("Linked Assignment / Allotment with : IDst = %s , Notice Type = %s , PEC = %ld"),IDst,NoticeType,PEC);
//			CDataBaseSTR.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)=\'%s\'));"), IDst); 
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)=\'%s\'));"), m_qCommonFields,IDst); 
		}
		else if(PEC==2)
		{
			Title.Format(_Z("Linked Assignment / Allotment with : IDst = %s , Notice Type = %s , PEC = %ld , SfnID = %s"),IDst,NoticeType,PEC,SfnID);
//			CDataBaseSTR.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\'));"), SfnID); 
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\'));"), m_qCommonFields,SfnID); 
		}
		else if(PEC==3)
		{
			Title.Format(_Z("Linked Assignment / Allotment with : IDst = %s , Notice Type = %s , PEC = %ld , allotkey = %s"),IDst,NoticeType,PEC,allotkey);
//			CDataBaseSTR.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)=\'%s\') AND ((allotkey)=\'%s\'));"), IDst,allotkey); 
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((IDst)=\'%s\') AND ((allotkey)=\'%s\'));"), m_qCommonFields,IDst,allotkey); 
		}
		else if(PEC==4)
		{
			Title.Format(_Z("Linked Assignment / Allotment with : IDst = %s , Notice Type = %s , PEC = %ld , SfnID = %s , allotkey = %s"),IDst,NoticeType,PEC,SfnID,allotkey);
//			CDataBaseSTR.Format(_T("SELECT * FROM CommonFields WHERE (((SfnID)=\'%s\') AND ((AssignCode)='L' Or (AssignCode)='S' Or (AssignCode) Is Null Or (AssignCode)='' Or (AssignCode)='---'));"), SfnID); 
			CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((SfnID)=\'%s\') AND ((AssignCode)='L' Or (AssignCode)='S' Or (AssignCode) Is Null Or (AssignCode)='' Or (AssignCode)='---'));"), m_qCommonFields,SfnID); 
		}
		else if(PEC==5)
		{
			CString NET;	NET.Format("%s%d",STN,PEC);
			Title.Format(_Z("Linked Assignment / Allotment with : IDst = %s , Notice Type = %s , PEC = %ld , allotkey = %s"),IDst,NoticeType,PEC,allotkey);
//			if	   ((NET==_T("ASS5"))||(NET==_T("AST5")))	CDataBaseSTR.Format(_T("SELECT * FROM CommonFields WHERE (((AssocAllotID)=\'%s\')) OR (((AdmRefID)=\'%s\'));"), AssocAllotID,AssocAllotID);
//			else if((NET==_T("ALS5"))||(NET==_T("ALT5")))	CDataBaseSTR.Format(_T("SELECT * FROM CommonFields WHERE (((AssocAllotID)=\'%s\')) OR (((AdmRefID)=\'%s\'));"), AdmRefID,AdmRefID);
			if	   ((NET==_T("ASS5"))||(NET==_T("AST5")))	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((AssocAllotID)=\'%s\')) OR (((AdmRefID)=\'%s\'));"), m_qCommonFields,AssocAllotID,AssocAllotID);
			else if((NET==_T("ALS5"))||(NET==_T("ALT5")))	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((AssocAllotID)=\'%s\')) OR (((AdmRefID)=\'%s\'));"), m_qCommonFields,AdmRefID,AdmRefID);
		}
	}
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Title = Title;
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		for (int i=0;i<Nrow;i++)
		{
			CString Selx, IDst0, SiteName;		double GeoLat, GeoLon;
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[i];
			IDst0 = GetFld(Selx,1);
			if(IDst0==_T("---"))
			{
				CString allotkey0 = GetFld(Selx,37),  GeoArea = GetFld(Selx,14);
				GE06ShowAllot(allotkey0, GeoArea);
			}
			else
			{
				SiteName = GetFld(Selx,4);	GeoLat = atof(GetFld(Selx,5));	GeoLon = atof(GetFld(Selx,6));
				OnDatabaseStationsindesktop2(GeoLat,GeoLon);
				AddStation_disp(atol(IDst0),GeoLat,GeoLon,SiteName) ;
			}//if IDst0
		}//for  i<Nrow 
	}//if datadlg
}
void CSMS4DCView::GE06linked_Converted(int flagC) 
{
	CString Selx = QGE06_Digital_Qx(flagC);
	if(Selx.GetLength()>0)
	{
		CString allotkey,AdmRefID, AssocAllotID,SfnID,PlanEntry, NoticeType,Fragment , IDst;
		IDst = GetFld(Selx,1);		AdmRefID = GetFld(Selx,3);		Fragment = GetFld(Selx,8);		PlanEntry = GetFld(Selx,10);
		SfnID = GetFld(Selx,12);	NoticeType = GetFld(Selx,13);	AssocAllotID = GetFld(Selx,28);	allotkey = GetFld(Selx,37);
		CP154606_Functions CP154606;
		CString STN = CP154606.GE06_STN(Fragment,NoticeType);
		int PEC = GE06_PEC(AdmRefID , AssocAllotID , PlanEntry , SfnID , STN) ;
		QGE06_Digital_Qy(IDst, PEC, NoticeType, SfnID, allotkey, AdmRefID, AssocAllotID, STN, flagC) ;
	}
	Set_STtable_Default();
}

void CSMS4DCView::OnDatabaseDisplayge06linked()
{
	GE06linked_Converted(0);
}

void CSMS4DCView::OnDatabaseConverted()
{
	GE06linked_Converted(1);
}


double CSMS4DCView::GE06UFS1(int Nrowy,CString Fragment_W,CString NoticeType_W,double Freq_W,
						  CString TV_SYS_W, CString RPC_W, CString SYS_VAR_W, double freq_vcarr_W,
						  CString TV_COLOR_W, double freq_scarr_W,CString oset_v_12_W,CString oset_v_khz_W,
						  CString TV_ch_W, CString RxMode_W, CString freq_stabl_W, double miu_W, double Sigma_W,
						  double GeoLat_W, double GeoLon_W, CString Pol_W, double latCal, double lonCal,
						  int AntDisc, int ENV, double Ti, double kfactor,double UFSmin ,int UFScheck,CDatabase *DB1)
{
	CP154606_Functions CP154606;
	double UFS,		CNFS_T1 = 0;
	CString Assign_IDst = _T(""),	Allot_IDst = _T("");	int nAssign_IDst = 0,	nAllot_IDst = 0;

	for(int iY=0; iY<Nrowy; iY++)
	{
		CString Sely = ((CSMS4DCApp *)AfxGetApp())->m_Sel[iY];
		CString IDst_I = GetFld(Sely,1),				RxMode_I = GetFld(Sely,54),			Fragment_I = GetFld(Sely,28),
				NoticeType_I = GetFld(Sely,35),			sttp_I = GetFld(Sely,18),			TV_SYS_I = GetFld(Sely,36),
				RPC_I = GetFld(Sely,37),				SYS_VAR_I = GetFld(Sely,38),		Emission_I = GetFld(Sely,19),
				TV_COLOR_I = GetFld(Sely,40),			SysType1_I = GetFld(Sely,26),		SysType2_I = GetFld(Sely,27),
				oset_v_12_I = GetFld(Sely,42),			oset_v_khz_I = GetFld(Sely,43),		TV_ch_I = GetFld(Sely,44);
	
//		TV_SYS_W.TrimLeft();		TV_SYS_W.TrimRight();
//		TV_COLOR_W.TrimLeft();		TV_COLOR_W.TrimRight();
//		freq_stabl_W.TrimLeft();	freq_stabl_W.TrimRight();
//		Pol_W.TrimLeft();			Pol_W.TrimRight();

//		TV_SYS_I.TrimLeft();		TV_SYS_I.TrimRight();
//		TV_COLOR_I.TrimLeft();		TV_COLOR_I.TrimRight();
	
		double  Freq_I = atof(GetFld(Sely,6)),			pwr_ratio_I = atof(GetFld(Sely,46)),
				freq_vcarr_I = atof(GetFld(Sely,39)),	freq_scarr_I = atof(GetFld(Sely,41));

		double PR, PRC, PRT;
		CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
								freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,RxMode_W,freq_stabl_W,
								Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPC_I,SYS_VAR_I,
								Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,SysType2_I,freq_scarr_I,
								oset_v_12_I,oset_v_khz_I,TV_ch_I,pwr_ratio_I, &PR, &PRC, &PRT) ;

		if( ((Fragment_W==_T("GE06A"))&&(PRC!=-999)&&(PRT!=-999))  ||  ((Fragment_W!=_T("GE06A"))&&(PR!=-999))	)
		{
		//	double Sigma_N = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, SRV_I);
			double Sigma_N = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, ENV,sttp_I);
			double CF = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_N*Sigma_N);
			CString PlanEntry_I = GetFld(Sely,50),		SfnID_I = GetFld(Sely,52),	AssocAllotID_I = GetFld(Sely,59),	AdmRefID_I = GetFld(Sely,33);
			CString STN_I = CP154606.GE06_STN(Fragment_I, NoticeType_I);
			int PEC_I = GE06_PEC(AdmRefID_I , AssocAllotID_I , PlanEntry_I , SfnID_I , STN_I) ;
			CString NET_I;	NET_I.Format("%s%d",STN_I,PEC_I);

			if((NET_I==_T("ASA0"))||(PEC_I==1))
			{
				CString IDst_I = GetFld(Sely,1),			Pol_I = GetFld(Sely,13),			ERP_h_dbw_I = GetFld(Sely,62),		ERP_v_dbw_I = GetFld(Sely,63),
						AntDir_I = GetFld(Sely,31),			AntCatID_I = GetFld(Sely,30),		Hagl_I = GetFld(Sely,5);
				double  GeoLat_I = atof(GetFld(Sely,3)),	GeoLon_I = atof(GetFld(Sely,4));

//				Pol_I.TrimLeft();			Pol_I.TrimRight();
				
				double CNFSj = CNFS_Function1(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
										 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
										 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,IDst_I,
										 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,UFSmin, UFScheck,DB1); 
				
				CNFS_T1  = CNFS_T1 + CNFSj;

			}//if((NET_I==_T("ASA0"))||(PEC_I==1))
			else if(PEC_I==2)
			{
				int flagID = IDstCompare(IDst_I, Assign_IDst, nAssign_IDst);
				if(flagID==0)
				{
					CString SFNID_I = GetFld(Sely,52);
					CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN, ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN;
					long numAssign = QGE06_CArea_Q2(SFNID_I,&GeoLatN,&GeoLonN,
													&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
													&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN) ;
					Assign_IDst = Assign_IDst + _T(",") + IDstN;	nAssign_IDst = nAssign_IDst + numAssign;
					for(int iAS = 0; iAS<numAssign ; iAS++)
					{
						CString IDst_Ii = GetFld(IDstN,iAS+1),				Pol_I = GetFld(PolN,iAS+1),					AntDir_I = GetFld(AntDirN,iAS+1),
								AntCatID_I = GetFld(AntCatIDN,iAS+1),		ERP_h_dbw_I = GetFld(ERP_h_dbwN,iAS+1),
								ERP_v_dbw_I = GetFld(ERP_v_dbwN,iAS+1),		Hagl_I = GetFld(AntHeightAGLN,iAS+1);
						double  GeoLat_I = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_I = atof(GetFld(GeoLonN,iAS+1)),
								Freq_I = atof(GetFld(FrequencyN,iAS+1));

						double CNFSj = CNFS_Function1(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
												 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
												 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,IDst_Ii,
												 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,UFSmin, UFScheck,DB1); 
						CNFS_T1 = CNFS_T1 + CNFSj;

					}//for  iAS

				}//if flagID
			}//if(PEC_I==2)
			else if(PEC_I==3)
			{
				CString GeoArea_I = GetFld(Sely,53);	CString Pol_I = GetFld(Sely,13);
				CString allotkey_I = GetFld(Sely,64);
				if(GeoArea_I.IsEmpty())
				{
					CString contourkeyN , nb_test_ptsN;
					long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_I) , &contourkeyN , &nb_test_ptsN);
					long *contourkeyI;		contourkeyI = new long[contourkeyNum];
					long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
					double dum;
					long NcontourT = 0;
					for(long i=0;i<contourkeyNum;i++)
					{
						contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
						nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
						NcontourT = NcontourT + nb_test_ptsI[i];
					}
					double * lat_TP;   lat_TP = new double[NcontourT];
					double * lon_TP;   lon_TP = new double[NcontourT];
					double * y;		y = lat_TP;
					double * x;		x = lon_TP;
					for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
					{
						CString lat_tpStr, lon_tpStr;
						long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
						for(long jTP=0;jTP<n_tp;jTP++)
						{
							*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
							*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
						}
					}
					CString RN = _T("");
					if     (NET_I==_T("ALT3"))							RN = GetFld(Sely,61);
					else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
					else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

					double CNFSj = CNFS_FunctionAL1(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
									latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN,allotkey_I, lat_TP, lon_TP, NcontourT,
									CF, PRC, PRT, PR,AntDisc, ENV, Ti, UFSmin, UFScheck,DB1) ;

					CNFS_T1  = CNFS_T1 + CNFSj;
					
					delete [] contourkeyI;		delete [] nb_test_ptsI;	delete [] lat_TP;	delete [] lon_TP;
				}//if GeoArea_I
				else
				{
					CString lat_tpSTR, lon_tpSTR;
					double dum;
					long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_I, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
					double * lat_TP;   lat_TP = new double[NcontourT];
					double * lon_TP;   lon_TP = new double[NcontourT];
					for(long jTP=0;jTP<NcontourT;jTP++)
					{
						lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
						lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
					}
					CString RN = _T("");
					if     (NET_I==_T("ALT3"))							RN = GetFld(Sely,61);
					else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
					else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

					double CNFSj = CNFS_FunctionAL1(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
									latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN,allotkey_I, lat_TP, lon_TP, NcontourT,
									CF, PRC, PRT, PR,AntDisc, ENV, Ti, UFSmin, UFScheck,DB1) ;

					CNFS_T1  = CNFS_T1 + CNFSj;

					delete [] lat_TP;		delete [] lon_TP;
				}//else GeoArea_I
			}//if(PEC_I==3)
			else if(PEC_I==4)
			{
				if((NET_I==_T("ASS4"))||(NET_I==_T("AST4")))	/////////A4_1
				{
					double CNFSsfn = 0, CNFSallot = 0;
					//+++++++++++++++Assignment++++++++++++++++++++++++++++++++++++++++
					int flagID = IDstCompare(IDst_I, Assign_IDst, nAssign_IDst);
					CString SFNID_I = GetFld(Sely,52);
					if(flagID==0)
					{
						CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN;
						long numAssign = QGE06_CArea_Q2(SFNID_I,&GeoLatN,&GeoLonN,
														&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
														&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN,1) ;
						Assign_IDst = Assign_IDst + _T(",") + IDstN;	nAssign_IDst = nAssign_IDst + numAssign;
						double CNFSjAS = 0;
						for(int iAS = 0; iAS<numAssign ; iAS++)
						{
							CString IDst_Ii = GetFld(IDstN,iAS+1),				Pol_I = GetFld(PolN,iAS+1),					AntDir_I = GetFld(AntDirN,iAS+1),
									AntCatID_I = GetFld(AntCatIDN,iAS+1),		ERP_h_dbw_I = GetFld(ERP_h_dbwN,iAS+1),
									ERP_v_dbw_I = GetFld(ERP_v_dbwN,iAS+1),		Hagl_I = GetFld(AntHeightAGLN,iAS+1);
							double  GeoLat_I = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_I = atof(GetFld(GeoLonN,iAS+1)),
									Freq_I = atof(GetFld(FrequencyN,iAS+1));

							double CNFS1 = CNFS_Function1(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
													 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
													 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,IDst_Ii,
													 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,UFSmin, UFScheck,DB1); 
							CNFSjAS = CNFSjAS + CNFS1;

						}//for  iAS
						CNFSsfn = CNFSjAS;
					}//if flagID
					//+++++++++++++++Allotment++++++++++++++++++++++++++++++++++++++++
					CString AllotmentSTR = QGE06_BCBT_A4_1(SFNID_I) ;
					CString allotkey_I = GetFld(AllotmentSTR,1) ;
					int flagIDal = IDstCompare(allotkey_I, Allot_IDst, nAllot_IDst);
					if(flagIDal==0)
					{
						CString NoticeType_I = GetFld(AllotmentSTR,3);	CString GeoArea_I = GetFld(AllotmentSTR,9) ;
						CString Pol_I = GetFld(AllotmentSTR,10);		CString SYS_VAR_I = GetFld(AllotmentSTR,11) ;
						Allot_IDst = Allot_IDst + _T(",") + allotkey_I;	nAllot_IDst = nAllot_IDst + 1;
						if(GeoArea_I.IsEmpty())
						{
							CString contourkeyN , nb_test_ptsN;
							long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_I) , &contourkeyN , &nb_test_ptsN);
							long *contourkeyI;		contourkeyI = new long[contourkeyNum];
							long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
							double dum;
							long NcontourT = 0;
							for(long i=0;i<contourkeyNum;i++)
							{
								contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
								nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
								NcontourT = NcontourT + nb_test_ptsI[i];
							}
							double * lat_TP;   lat_TP = new double[NcontourT];
							double * lon_TP;   lon_TP = new double[NcontourT];
							double * y;		y = lat_TP;
							double * x;		x = lon_TP;
							for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
							{
								CString lat_tpStr, lon_tpStr;
								long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
								for(long jTP=0;jTP<n_tp;jTP++)
								{
									*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
									*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
								}
							}
					//00000000000000000000000000000000000000000000000000000000000000000000000000
							CString STNal = CP154606.GE06_STN(GetFld(AllotmentSTR,2),GetFld(AllotmentSTR,3));
							int PECal = GE06_PEC(GetFld(AllotmentSTR,4) , GetFld(AllotmentSTR,5) , GetFld(AllotmentSTR,6) , SfnID_I , STNal) ;
							CString NETal;	NETal.Format("%s%d",STNal,PECal);
							CString RPCal = GetFld(AllotmentSTR,7);
							CString RNal = _T("");
							if     (NETal==_T("ALT4"))							RNal = GetFld(AllotmentSTR,8);
							else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC4")))	RNal = _T("RN5");
							else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC5")))	RNal = _T("RN6");

							double PRal, PRCal, PRTal;
							CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,
													SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
													freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,
													RxMode_W,freq_stabl_W,
													Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPCal,
													SYS_VAR_I,Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,
													SysType2_I,freq_scarr_I,oset_v_12_I,oset_v_khz_I,TV_ch_I,
													pwr_ratio_I, &PRal, &PRCal, &PRTal) ;

						//	double Sigma_Nal = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPCal, Freq_I, SRV_I);
							double Sigma_Nal = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPCal, Freq_I, ENV,sttp_I);
							double CFal = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_Nal*Sigma_Nal);
					//00000000000000000000000000000000000000000000000000000000000000000000000000
							double CNFSj = CNFS_FunctionAL1(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
											latCal, lonCal, Freq_I,  Pol_I,  RPCal, RNal ,allotkey_I, lat_TP, lon_TP, NcontourT,
											CFal, PRCal, PRTal, PRal,AntDisc, ENV, Ti, UFSmin, UFScheck,DB1) ;
							CNFSallot  = CNFSj;
							delete [] contourkeyI;	delete [] nb_test_ptsI;		delete [] lat_TP;		delete [] lon_TP;
						}//if GeoArea_I
						else
						{
							CString lat_tpSTR, lon_tpSTR;
							double dum;
							long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_I, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
							double * lat_TP;   lat_TP = new double[NcontourT];
							double * lon_TP;   lon_TP = new double[NcontourT];
							for(long jTP=0;jTP<NcontourT;jTP++)
							{
								lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
								lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
							}
					//00000000000000000000000000000000000000000000000000000000000000000000000000
							CString STNal = CP154606.GE06_STN(GetFld(AllotmentSTR,2),GetFld(AllotmentSTR,3));
							int PECal = GE06_PEC(GetFld(AllotmentSTR,4) , GetFld(AllotmentSTR,5) , GetFld(AllotmentSTR,6) , SfnID_I , STNal) ;
							CString NETal;	NETal.Format("%s%d",STNal,PECal);
							CString RPCal = GetFld(AllotmentSTR,7);
							CString RNal = _T("");
							if     (NETal==_T("ALT4"))							RNal = GetFld(AllotmentSTR,8);
							else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC4")))	RNal = _T("RN5");
							else if((NETal==_T("ALS4"))&&(RPCal==_T("RPC5")))	RNal = _T("RN6");

							double PRal, PRCal, PRTal;
							CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,
													SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
													freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,
													RxMode_W,freq_stabl_W,
													Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPCal,
													SYS_VAR_I,Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,
													SysType2_I,freq_scarr_I,oset_v_12_I,oset_v_khz_I,TV_ch_I,
													pwr_ratio_I, &PRal, &PRCal, &PRTal) ;

						//	double Sigma_Nal = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPCal, Freq_I, SRV_I);
							double Sigma_Nal = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPCal, Freq_I, ENV,sttp_I);
							double CFal = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_Nal*Sigma_Nal);
					//00000000000000000000000000000000000000000000000000000000000000000000000000
							double CNFSj = CNFS_FunctionAL1(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
											latCal, lonCal, Freq_I,  Pol_I,  RPCal, RNal ,allotkey_I, lat_TP, lon_TP, NcontourT,
											CFal, PRCal, PRTal, PRal,AntDisc, ENV, Ti, UFSmin, UFScheck,DB1) ;
							CNFSallot  = CNFSj;
							delete [] lat_TP;	delete [] lon_TP;
						}//else GeoArea_I
					}//if flagIDal
					double CNFSj = max(CNFSsfn , CNFSallot);
					CNFS_T1  = CNFS_T1 + CNFSj;
				}/////////A4_1
				else if((NET_I==_T("ALS4"))||(NET_I==_T("ALT4")))	/////////A4_2
				{
					double CNFSsfn = 0, CNFSallot = 0;
					CString dumstr;
					//+++++++++++++++Assignment++++++++++++++++++++++++++++++++++++++++
					CString SFNID_I = GetFld(Sely,52);
					CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN, NoticeTypeN, RPCN , SysVarN, RxModeN;
					long numAssign = QGE06_CArea_Q2_1(SFNID_I,&GeoLatN,&GeoLonN,
													&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
													&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN,
													&NoticeTypeN, &RPCN , &SysVarN, &RxModeN,&dumstr) ;
					int flagID = IDstCompare(GetFld(IDstN,1), Assign_IDst, nAssign_IDst);
					if(flagID==0)
					{
						Assign_IDst = Assign_IDst + _T(",") + IDstN;	nAssign_IDst = nAssign_IDst + numAssign;

						CString NoticeType_I = GetFld(NoticeTypeN,1),	RPC_I = GetFld(RPCN,1),
								SysVar_I = GetFld(SysVarN,1),			RxMode_I = GetFld(RxModeN,1);
						double PRas, PRCas, PRTas;
						CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,
												SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
												freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,
												RxMode_W,freq_stabl_W,
												Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPC_I,
												SYS_VAR_I,Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,
												SysType2_I,freq_scarr_I,oset_v_12_I,oset_v_khz_I,TV_ch_I,
												pwr_ratio_I, &PRas, &PRCas, &PRTas) ;

					//	double Sigma_Nas = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, SRV_I);
						double Sigma_Nas = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, ENV,sttp_I);
						double CFas = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_Nas*Sigma_Nas);
						double CNFSjAS = 0;
						for(int iAS = 0; iAS<numAssign ; iAS++)
						{
							CString IDst_Ii = GetFld(IDstN,iAS+1),				Pol_I = GetFld(PolN,iAS+1),					AntDir_I = GetFld(AntDirN,iAS+1),
									AntCatID_I = GetFld(AntCatIDN,iAS+1),		ERP_h_dbw_I = GetFld(ERP_h_dbwN,iAS+1),
									ERP_v_dbw_I = GetFld(ERP_v_dbwN,iAS+1),		Hagl_I = GetFld(AntHeightAGLN,iAS+1);
							double  GeoLat_I = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_I = atof(GetFld(GeoLonN,iAS+1));

							double CNFS1 = CNFS_Function1(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
													 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
													 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,IDst_Ii,
													 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,UFSmin, UFScheck,DB1); 
							CNFSjAS = CNFSjAS + CNFS1;
						}//for  iAS
						CNFSsfn = CNFSjAS;
					}//if flagID
					//+++++++++++++++Allotment++++++++++++++++++++++++++++++++++++++++
					CString allotkey_I = GetFld(Sely,64);
					int flagIDal = IDstCompare(allotkey_I, Allot_IDst, nAllot_IDst);
					if(flagIDal==0)
					{
						CString GeoArea_I = GetFld(Sely,53);	CString Pol_I = GetFld(Sely,13);
						Allot_IDst = Allot_IDst + _T(",") + allotkey_I;	nAllot_IDst = nAllot_IDst + 1;
						if(GeoArea_I.IsEmpty())
						{
							CString contourkeyN , nb_test_ptsN;
							long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_I) , &contourkeyN , &nb_test_ptsN);
							long *contourkeyI;		contourkeyI = new long[contourkeyNum];
							long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
							double dum;
							long NcontourT = 0;
							for(long i=0;i<contourkeyNum;i++)
							{
								contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
								nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
								NcontourT = NcontourT + nb_test_ptsI[i];
							}
							double * lat_TP;   lat_TP = new double[NcontourT];
							double * lon_TP;   lon_TP = new double[NcontourT];
							double * y;		y = lat_TP;
							double * x;		x = lon_TP;
							for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
							{
								CString lat_tpStr, lon_tpStr;
								long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
								for(long jTP=0;jTP<n_tp;jTP++)
								{
									*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
									*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
								}
							}
							CString RN = _T("");
							if     (NET_I==_T("ALT4"))							RN = GetFld(Sely,61);
							else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
							else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

							double CNFSj = CNFS_FunctionAL1(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
											latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN ,allotkey_I, lat_TP, lon_TP, NcontourT,
											CF, PRC, PRT, PR,AntDisc, ENV, Ti, UFSmin, UFScheck,DB1) ;

							CNFSallot  = CNFSj;
							delete [] contourkeyI;	delete [] nb_test_ptsI;	delete [] lat_TP;		delete [] lon_TP;
						}//if GeoArea_I
						else
						{
							CString lat_tpSTR, lon_tpSTR;
							double dum;
							long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_I, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
							double * lat_TP;   lat_TP = new double[NcontourT];
							double * lon_TP;   lon_TP = new double[NcontourT];
							for(long jTP=0;jTP<NcontourT;jTP++)
							{
								lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
								lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
							}
							CString RN = _T("");
							if     (NET_I==_T("ALT4"))							RN = GetFld(Sely,61);
							else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
							else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

							double CNFSj = CNFS_FunctionAL1(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
											latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN ,allotkey_I, lat_TP, lon_TP, NcontourT,
											CF, PRC, PRT, PR,AntDisc, ENV, Ti, UFSmin, UFScheck,DB1) ;

							CNFSallot  = CNFSj;
							delete [] lat_TP;		delete [] lon_TP;
						}//else GeoArea_I
					}//if flagIDal
					double CNFSj = max(CNFSsfn , CNFSallot);
				//	CNFS_T1  = CNFS_T1 + pow(10.0, (CNFSj)/10.0);
					CNFS_T1  = CNFS_T1 + CNFSj;
				}/////////A4_2
			}//if(PEC_I==4)
			else if(PEC_I==5)
			{
				if((NET_I==_T("ASS5"))||(NET_I==_T("AST5")))	/////////A5_1
				{
					int flagID = IDstCompare(IDst_I, Assign_IDst, nAssign_IDst);
					if(flagID==0)
					{
						CString allotkey_I = QGE06_CArea_Q3(AssocAllotID_I) ;
						Allot_IDst = Allot_IDst + _T(",") + allotkey_I;	nAllot_IDst = nAllot_IDst + 1;
						Assign_IDst = Assign_IDst + _T(",") + IDst_I;	nAssign_IDst = nAssign_IDst + 1;
						
						CString Pol_I = GetFld(Sely,13),			ERP_h_dbw_I = GetFld(Sely,62),
								ERP_v_dbw_I = GetFld(Sely,63),		AntDir_I = GetFld(Sely,31),
								AntCatID_I = GetFld(Sely,30),		Hagl_I = GetFld(Sely,5);
						double  GeoLat_I = atof(GetFld(Sely,3)),	GeoLon_I = atof(GetFld(Sely,4));

						double CNFSj = CNFS_Function1(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
												 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
												 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,IDst_I,
												 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,UFSmin, UFScheck,DB1); 
						CNFS_T1 = CNFS_T1 + CNFSj;

					}//if flagIDal
				}	/////////A5_1
				else if((NET_I==_T("ALS5"))||(NET_I==_T("ALT5")))	/////////A5_2
				{
					CString allotkey_I = GetFld(Sely,64);
					int flagIDal = IDstCompare(allotkey_I, Allot_IDst, nAllot_IDst);
					if(flagIDal==0)
					{
						CString ASstr = QGE06_CArea_Q4(AdmRefID_I);
						CString IDst_I = GetFld(ASstr,1);
						Allot_IDst = Allot_IDst + _T(",") + allotkey_I;	nAllot_IDst = nAllot_IDst + 1;
						Assign_IDst = Assign_IDst + _T(",") + IDst_I;	nAssign_IDst = nAssign_IDst + 1;
						CString Pol_I = GetFld(ASstr,2),			ERP_h_dbw_I = GetFld(ASstr,5),
								ERP_v_dbw_I = GetFld(ASstr,6),		AntDir_I = GetFld(ASstr,7),
								AntCatID_I = GetFld(ASstr,8),		Hagl_I = GetFld(ASstr,9),
								NoticeType_I = GetFld(ASstr,10),	RPC_I = GetFld(ASstr,11),
								SYS_VAR_I = GetFld(ASstr,12),		RxMode_I = GetFld(ASstr,13);
						double  GeoLat_I = atof(GetFld(ASstr,3)),	GeoLon_I = atof(GetFld(ASstr,4));
						double PRas, PRCas, PRTas;
						CP154606.GE06_PR_bcbt_W(Fragment_W,NoticeType_W,Freq_W, TV_SYS_W,RPC_W,
												SYS_VAR_W,freq_vcarr_W,TV_COLOR_W,
												freq_scarr_W,oset_v_12_W,oset_v_khz_W,TV_ch_W,
												RxMode_W,freq_stabl_W,
												Fragment_I,NoticeType_I,Freq_I,sttp_I,TV_SYS_I,RPC_I,
												SYS_VAR_I,Emission_I,freq_vcarr_I,TV_COLOR_I,SysType1_I,
												SysType2_I,freq_scarr_I,oset_v_12_I,oset_v_khz_I,TV_ch_I,
												pwr_ratio_I, &PRas, &PRCas, &PRTas) ;
					//	double Sigma_Nas = CP154606.Table_SigmaN(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, SRV_I);
						double Sigma_Nas = CP154606.Table_SigmaN_0(Fragment_I, NoticeType_I, RxMode_I, RPC_I, Freq_I, ENV,sttp_I);
						double CFas = miu_W*sqrt(Sigma_W*Sigma_W + Sigma_Nas*Sigma_Nas);
					
						double CNFSj = CNFS_Function1(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
												 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
												 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,IDst_I,
												 latCal, lonCal, CFas, PRCas, PRTas, PRas, AntDisc, ENV, Ti, kfactor,UFSmin, UFScheck,DB1); 
						CNFS_T1 = CNFS_T1 + CNFSj;

					}//if flagID
				}	/////////A5_2
			}//if(PEC_I==5)
			else if(Fragment_I==_T("GE06L"))
			{
				CString Pol_I = GetFld(Sely,13);	CString StType_I = GetFld(Sely,29);
				int dflag = 0;
				double  GeoLat_I, GeoLon_I;
				if((((sttp_I==_T("FX"))||(sttp_I==_T("FB")))&&(StType_I==_T("Typical"))) || ((sttp_I==_T("ML"))&&(StType_I!=_T("Typical"))))
				{
					CString zone0 = GetFld(Sely,34);
					if(zone0.GetLength()>0)
					{
						if(zone0.GetLength()==1)			zone0 = zone0 + _T("  ");
						else if(zone0.GetLength()==2)		zone0 = zone0 + _T(" ");
						Zone2NearPoint(zone0, latCal, lonCal, &GeoLat_I, &GeoLon_I); 
						dflag = 1;
					}//if zone0
					else
					{
						CString radius = GetFld(Sely,22);
						if(radius.GetLength()>0)
						{
							double latC = atof(GetFld(Sely,3))  ,  lonC = atof(GetFld(Sely,4));
							double azC = Azimuth_Deg(latC, lonC, latCal,lonCal) ;
							reckon(latC, lonC, atof(radius), azC, &GeoLat_I, &GeoLon_I) ;
							dflag = 1;
						}
					}
				}
				else if(((sttp_I==_T("FX"))||(sttp_I==_T("FB")))&&(StType_I!=_T("Typical")))
				{
					GeoLat_I = atof(GetFld(Sely,3));	GeoLon_I = atof(GetFld(Sely,4));
					dflag = 1;
				}
				if(dflag == 1)
				{
					double PWR = atof(GetFld(Sely,7));	//W
					double PwrERP = 10.0*log10(PWR) - 2.15;	//dBw
					CString ERP_h_dbw_I;	ERP_h_dbw_I.Format(_T("%lf"), PwrERP);
					CString ERP_v_dbw_I;	ERP_v_dbw_I.Format(_T("%lf"), PwrERP);
					CString AntDir_I = GetFld(Sely,31),		AntCatID_I = GetFld(Sely,30),	Hagl_I = GetFld(Sely,5);
				
					double CNFSj = CNFS_Function1(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
											 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,
											 AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,IDst_I,
											 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,UFSmin, UFScheck,DB1,3); 
					CNFS_T1 = CNFS_T1 + CNFSj;

				}//if dflag
			}//if Fragment_I==_T("GE06L"))

		}//if _I is Interferer
	}//for iY
	UFS = 10.0*log10(CNFS_T1 + pow(10.0, (UFSmin)/10.0));
	return UFS;
}

void CSMS4DCView::GE06_USFtest1(CString IDst,CString allotkey,double CNFS,double UFSmin,CDatabase *DB1)
{
	int flag = 1;
	if(CNFS<(UFSmin-12.0))		flag = 0;

	CString SQL1;
	SQL1.Format(_T("DELETE * FROM UFStest WHERE (((IDst)=\'%s\') AND ((Allotkey)=\'%s\'));"),IDst,allotkey);
	DB1->ExecuteSQL(SQL1);

	SQL1.Format(_T("SELECT \'%s\',\'%s\',%d "), IDst, allotkey, flag);
	SQL1 = _T("INSERT INTO UFStest (IDst, Allotkey, flag) ") + SQL1;
	DB1->ExecuteSQL(SQL1);
}

int CSMS4DCView::GE06_USFtest2(CString IDst,CString allotkey,CDatabase *DB1)
{
	CRecordset rs;	rs.m_pDatabase = DB1;
	CString  tbl;	tbl.Format(_T("SELECT flag FROM UFStest WHERE (((IDst)=\'%s\') AND ((Allotkey)=\'%s\'));"), IDst,allotkey);
	rs.Open(CRecordset::snapshot, tbl);
	int c = 0;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		rs.GetFieldValue(_T("flag"),str);	c = atol(str);
	}
	rs.Close();
	return c;
}

double CSMS4DCView::CNFS_Function1(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,CString IDst_I,
								double latCal,double lonCal,double CF,double  PRC,double  PRT,double  PR,
								int AntDisc, int ENV,double Ti,double kfactor,double UFSmin, int UFScheck,CDatabase *DB1,double A2D) 
{
	double CNFS_T1, CNFSj = 0, co = 0;
	if(UFScheck==0)
	{
		co = 1;
		CNFSj = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
							 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
							 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,A2D); 
		GE06_USFtest1(IDst_I, _T("---"),CNFSj,UFSmin,DB1);
	}
	else
	{
		co = GE06_USFtest2(IDst_I, _T("---"),DB1);
		if(co==1)
		{
			CNFSj = CNFS_Function_0(GeoLat_W, GeoLon_W, Freq_W, Pol_W, Fragment_W,
								 GeoLat_I, GeoLon_I, Freq_I, Pol_I, Hagl_I,AntDir_I, AntCatID_I, ERP_h_dbw_I, ERP_v_dbw_I,
								 latCal, lonCal, CF, PRC, PRT, PR, AntDisc, ENV, Ti, kfactor,A2D); 
		}
	}
	CNFS_T1 = co*pow(10.0, (CNFSj)/10.0);
	return CNFS_T1;
}

double CSMS4DCView::CNFS_FunctionAL1(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
									double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,CString allotkey_I,
									double lat_TP[],double lon_TP[],long NcontourT,double CF,double PRC,double PRT,double PR,
									int AntDisc, int ENV,double Ti,double UFSmin, int UFScheck,CDatabase *DB1) 
{
	double CNFS_T1, CNFSj = 0, co = 0;
	if(UFScheck==0)
	{
		co = 1;
		CNFSj = CNFS_FunctionAL_0(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
						latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN,	lat_TP, lon_TP, NcontourT,
						CF, PRC, PRT, PR,AntDisc, ENV, Ti) ;
		GE06_USFtest1(_T("---"), allotkey_I ,CNFSj,UFSmin,DB1);
	}
	else
	{
		co = GE06_USFtest2(_T("---"), allotkey_I,DB1);
		if(co==1)
		{
			CNFSj = CNFS_FunctionAL_0(GeoLat_W, GeoLon_W, Freq_W,  Pol_W,  Fragment_W,
						latCal, lonCal, Freq_I,  Pol_I,  RPC_I, RN,	lat_TP, lon_TP, NcontourT,
						CF, PRC, PRT, PR,AntDisc, ENV, Ti) ;
		}
	}
	CNFS_T1 = co*pow(10.0, (CNFSj)/10.0);
	return CNFS_T1;
}

double CSMS4DCView::CNFS_Function_IntA(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
										CString NoticeType_W,CString RXMode_W,CString RPC_W,
										double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
										CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
										double latCal,double lonCal,double CF,double  PRC,double  PRT,
										int AntDisc, int ENV,double Ti,double kfactor,double A2D) 
{
	double  CNFS,PR0;
	CP154606_Functions CP154606;
	double az_I2Cal = Azimuth_Deg(GeoLat_I,GeoLon_I,latCal,lonCal);
/*
	int az0[37];
	for(int i=0;i<=36;i++)		az0[i] = 10*i;
	double attH0_I[37], attV0_I[37];
	if(AntDir_I==_T("D"))
		GE84pattern(atol(AntCatID_I),attH0_I,attV0_I,Pol_I);
	else
		for(int i=0;i<36;i++)
		{
			attH0_I[i] = 0;		attV0_I[i] = 0;
		}
	attH0_I[36] = attH0_I[0];	attV0_I[36] = attV0_I[0];
	double attnH_I2Cal = Interp2(az0,attH0_I,az_I2Cal,37) ;
	double attnV_I2Cal = Interp2(az0,attV0_I,az_I2Cal,37) ;
*/
	double attH0_I[361], attV0_I[361];
	GE06patternT(atol(AntCatID_I), AntDir_I, Pol_I,attH0_I,attV0_I); 
	double attnH_I2Cal = attH0_I[(int)az_I2Cal],	attnV_I2Cal = attV0_I[(int)az_I2Cal];

	double ERPH,ERPV;
	if     (Pol_I==_T("H"))						ERPH = atof(ERP_h_dbw_I)-attnH_I2Cal;
	else if(Pol_I==_T("V"))						ERPV = atof(ERP_v_dbw_I)-attnV_I2Cal;
	else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{ERPH = atof(ERP_h_dbw_I)-attnH_I2Cal-A2D;	ERPV = atof(ERP_v_dbw_I)-attnV_I2Cal-A2D;}
	/////////////////////////// h1_I //////////////////////
	double h1_I, lat3km, lon3km, lat15km, lon15km;
	double dist_I2Cal = Distance_km(GeoLat_I,GeoLon_I,latCal,lonCal) ;

	OnDatabaseStationsindesktop2(GeoLat_I,GeoLon_I);
	double Hasl_I = LatLon2Hg(GeoLat_I,GeoLon_I);
	double Hasgl_I = Hasl_I + atof(Hagl_I);
	
	if (dist_I2Cal>=15.0)
	{
		reckon(GeoLat_I,GeoLon_I,  3.0 , az_I2Cal , &lat3km  , &lon3km) ;
		reckon(GeoLat_I,GeoLon_I, 15.0 , az_I2Cal , &lat15km , &lon15km) ;
		h1_I = Hasgl_I - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km , 120);
	}
	else
	{
		reckon(GeoLat_I,GeoLon_I, 0.2*dist_I2Cal , az_I2Cal , &lat3km  , &lon3km) ;
		reckon(GeoLat_I,GeoLon_I,     dist_I2Cal , az_I2Cal , &lat15km , &lon15km) ;
		h1_I = Hasgl_I - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km , 120);
	}
	double ATTNantrec = 0, PolAntDisc = 0;
//	if(AntDisc==1)
	if((AntDisc==1)&&((NoticeType_W==_T("DT1"))||(NoticeType_W==_T("GT1")))&&((RXMode_W==_T("FX"))||(RPC_W==_T("RPC1"))))
	{
		double az_Cal2W = Azimuth_Deg(latCal,lonCal,GeoLat_W,GeoLon_W) ;
		double az_Cal2I = Azimuth_Deg(latCal,lonCal,GeoLat_I,GeoLon_I) ;
		double AZMantrec = fabs(az_Cal2W-az_Cal2I);
		if(AZMantrec>180)	AZMantrec = 360.0 - AZMantrec;
		ATTNantrec = CP154606.F_3_1_BT419(AZMantrec,Freq_W) ;	//Fig.3-1 REC BT.419
		PolAntDisc = 16;
	}
	double Em = -999, EmH = -999, EmV = -999, EmI = -999;
	Em = E_P1546_06(GeoLat_I,GeoLon_I,latCal,lonCal, h1_I, Hasgl_I, Freq_I, kfactor, Ti, 10, ENV,0,50, 0);

	if     (Pol_I==_T("H"))						EmH = Em - 30.0 + ERPH;
	else if(Pol_I==_T("V"))						EmV = Em - 30.0 + ERPV;
	else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{EmH = Em - 30.0 + ERPH;	EmV = Em - 30.0 + ERPV;}

	if     (Pol_W==_T("H"))						EmI = 10.0*log10(pow(10.0 , (EmH-ATTNantrec)/10.0) + pow(10.0 , (EmV-PolAntDisc)/10.0));
	else if(Pol_W==_T("V"))						EmI = 10.0*log10(pow(10.0 , (EmH-PolAntDisc)/10.0) + pow(10.0 , (EmV-ATTNantrec)/10.0));
	else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	EmI = 10.0*log10(pow(10.0 , EmH/10.0) + pow(10.0 , EmV/10.0));

	double EmIT = EmI;
	if(Fragment_W==_T("GE06A"))
	{
		double Em = -999, EmH = -999, EmV = -999, EmI = -999;
		Em = E_P1546_06(GeoLat_I,GeoLon_I,latCal,lonCal, h1_I, Hasgl_I, Freq_I, kfactor, 50, 10, ENV,0,50, 0);

		if     (Pol_I==_T("H"))						EmH = Em - 30.0 + ERPH;
		else if(Pol_I==_T("V"))						EmV = Em - 30.0 + ERPV;
		else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{EmH = Em - 30.0 + ERPH;	EmV = Em - 30.0 + ERPV;	}

		if     (Pol_W==_T("H"))						EmI = 10.0*log10(pow(10.0 , (EmH-ATTNantrec)/10.0) + pow(10.0 , (EmV-PolAntDisc)/10.0));
		else if(Pol_W==_T("V"))						EmI = 10.0*log10(pow(10.0 , (EmH-PolAntDisc)/10.0) + pow(10.0 , (EmV-ATTNantrec)/10.0));
		else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	EmI = 10.0*log10(pow(10.0 , EmH/10.0) + pow(10.0 , EmV/10.0));

		double EmIC = EmI;
		if((EmIC+PRC)>(EmIT+PRT))	PR0 = PRC;
		else						PR0 = PRT;
	}
//	else PR0 = PR;
	CNFS = EmIT + PR0 + CF;
	return CNFS;
}

int CSMS4DCView::QGE06_IntToBCBT2FXM_Qy(double GRlat, double GRlon, double SR, double Freq_I, double FR) 
{
	int NrowT = 0, Nrow = 0;
	CString CDataBaseSTR = _T("");
	double dumy,  lonmin , lonmax , latmin , latmax ,rng_km = SR , fmin , fmax;
	fmin = Freq_I - FR;
	fmax = Freq_I + FR;
	reckon(GRlat,GRlon, rng_km,  0.0,&latmax,&dumy) ;
	reckon(GRlat,GRlon, rng_km,180.0,&latmin,&dumy) ;
	reckon(GRlat,GRlon, rng_km, 90.0,&dumy,&lonmax) ;
	reckon(GRlat,GRlon, rng_km,270.0,&dumy,&lonmin) ;

	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;		CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	CString SQL1;
	SQL1 = _T("DELETE * FROM FStrig_hR;");
	DB1.ExecuteSQL(SQL1);

	double STlat_deg , STlon_deg;
	CString str, IDst;
//	CString IDstN = _T("");

//	CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB') AND ((StType)<>'Typical') AND ((RXfreq)>=%lf And (RXfreq)<=%lf) AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf));"), fmin , fmax, latmin , latmax, lonmin , lonmax);
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB') AND ((StType)<>'Typical') AND ((RXfreq)>=%lf And (RXfreq)<=%lf) AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf));"), m_qSTtableGE06ASAL,fmin , fmax, latmin , latmax, lonmin , lonmax);
	rs.Open(CRecordset::snapshot, CDataBaseSTR);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
			rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
			double dist = Distance_km(GRlat,GRlon,STlat_deg,STlon_deg);
			if((dist <= SR)&&(dist > 0.0000001))
			{
		//		IDstN = IDstN + _T(",") + IDst;
				Nrow++;

				CString sttp,Freq;
				rs.GetFieldValue(_T("STTP"),sttp);
				rs.GetFieldValue(_T("RXfreq"),Freq);
				SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s' "), IDst, 1, Freq, sttp, _T("POINT"));
				SQL1 = _T("INSERT INTO FStrig_hR (IDst, ant, Freq_ter, STTP, GeoType) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
			}
			rs.MoveNext();
		}//while
	}//if
	rs.Close();	

//	CDataBaseSTR.Format(_T("SELECT IDst,STlat_deg,STlon_deg,STTP,TXfreq,GeoType ,zone,RecLat,RecLon,Link.Radius  FROM Link, STtableGE06 WHERE (((STtableGE06.IDst)=[Link].[TXID]) AND ((STtableGE06.STTP)='FX' Or (STtableGE06.STTP)='FB') AND ((STtableGE06.TXfreq)>=%lf And (STtableGE06.TXfreq)<=%lf) AND ((STtableGE06.STlat_deg)>=%lf And (STtableGE06.STlat_deg)<=%lf) AND ((STtableGE06.STlon_deg)>=%lf And (STtableGE06.STlon_deg)<=%lf) AND ((Link.GeoType)='MULTIPOINT' Or (Link.GeoType)='ZONE' Or (Link.GeoType)='CIRCLE') AND ((STtableGE06.Fragment)='GE06L')) ORDER BY STtableGE06.IDst;"), fmin , fmax, latmin , latmax, lonmin , lonmax);
	CDataBaseSTR.Format(_T("SELECT IDst,STlat_deg,STlon_deg,STTP,TXfreq,GeoType ,zone,RecLat,RecLon,Link.Radius  FROM Link, %s WHERE (((STtableGE06.IDst)=[Link].[TXID]) AND ((STtableGE06.STTP)='FX' Or (STtableGE06.STTP)='FB') AND ((STtableGE06.TXfreq)>=%lf And (STtableGE06.TXfreq)<=%lf) AND ((STtableGE06.STlat_deg)>=%lf And (STtableGE06.STlat_deg)<=%lf) AND ((STtableGE06.STlon_deg)>=%lf And (STtableGE06.STlon_deg)<=%lf) AND ((Link.GeoType)='MULTIPOINT' Or (Link.GeoType)='ZONE' Or (Link.GeoType)='CIRCLE') AND ((STtableGE06.Fragment)='GE06L')) ORDER BY STtableGE06.IDst;"), m_qSTtableGE06 , fmin , fmax, latmin , latmax, lonmin , lonmax);
	rs.Open(CRecordset::snapshot, CDataBaseSTR);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
			rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
			double dist = Distance_km(GRlat,GRlon,STlat_deg,STlon_deg);
			if((dist <= SR)&&(dist > 0.0000001))
			{
		//		IDstN = IDstN + _T(",") + IDst;
				Nrow++;

				CString sttp,Freq,zone,RecLat,RecLon,Radius;
				rs.GetFieldValue(_T("STTP"),sttp);
				rs.GetFieldValue(_T("TXfreq"),Freq);
				rs.GetFieldValue(_T("GeoType"),str);
				rs.GetFieldValue(_T("zone"),zone);
				rs.GetFieldValue(_T("RecLat"),RecLat);
				rs.GetFieldValue(_T("RecLon"),RecLon);
				rs.GetFieldValue(_T("Radius"),Radius);

			//	SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s','%s',%s,%s,%s "), IDst, 0, Freq, sttp, str,zone,RecLat,RecLon,Radius);
				SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s','%s',%s,%s,%s "), IDst, 0, Freq, sttp, str,zone, RecLat.IsEmpty()?"NULL":RecLat ,RecLon.IsEmpty()?"NULL":RecLon,Radius.IsEmpty()?"NULL":Radius);
				
				SQL1 = _T("INSERT INTO FStrig_hR (IDst, ant, Freq_ter, STTP, GeoType,zone,latp,lonp,Rp) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
			}
			rs.MoveNext();
		}//while
	}//if
	rs.Close();	

///	CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06L') AND ((STTP)='ML') AND ((RXfreq)>=%lf And (RXfreq)<=%lf) AND ((STlat_deg)>=%lf And (STlat_deg)<=%lf) AND ((STlon_deg)>=%lf And (STlon_deg)<=%lf)) OR (((Fragment)='GE06L') AND ((STTP)='ML'));"), fmin , fmax, latmin , latmax, lonmin , lonmax);
//	CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06L') AND ((STTP)='ML') AND ((RXfreq)>=%lf And (RXfreq)<=%lf));"), fmin , fmax);
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06L') AND ((STTP)='ML') AND ((RXfreq)>=%lf And (RXfreq)<=%lf));"), m_qSTtableGE06ASAL,fmin , fmax);

	rs.Open(CRecordset::snapshot, CDataBaseSTR);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);

			rs.GetFieldValue(_T("AreaOfTrans"),str);
			if(str.GetLength()>0)
			{
				double lat,lon;
				Zone2GRpoint(str,&lat,&lon);

				double dist = Distance_km(GRlat,GRlon,lat,lon);
				if((dist <= SR)&&(dist > 0.0000001))
				{
			//		IDstN = IDstN + _T(",") + IDst;
					Nrow++;

					CString sttp,Freq;
					rs.GetFieldValue(_T("STTP"),sttp);
					rs.GetFieldValue(_T("RXfreq"),Freq);
					SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s','%s' "), IDst, 0, Freq, sttp, _T("ZONE"),str);
					SQL1 = _T("INSERT INTO FStrig_hR (IDst, ant, Freq_ter, STTP, GeoType,zone) ") + SQL1;
					DB1.ExecuteSQL(SQL1);
				}
			}
			else
			{
				rs.GetFieldValue(_T("radius"),str);
				if(str.GetLength()>0)
				{
					CString lat,lon;
					rs.GetFieldValue(_T("STlat_deg"),lat);
					rs.GetFieldValue(_T("STlon_deg"),lon);

					double dist = Distance_km(GRlat,GRlon,atof(lat),atof(lon));
					if((dist <= SR)&&(dist > 0.0000001))
					{
				//		IDstN = IDstN + _T(",") + IDst;
						Nrow++;

						CString sttp,Freq;
						rs.GetFieldValue(_T("STTP"),sttp);
						rs.GetFieldValue(_T("RXfreq"),Freq);
						SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s',%s,%s,%s "), IDst, 0, Freq, sttp, _T("CIRCLE"),lat,lon,str);
						SQL1 = _T("INSERT INTO FStrig_hR (IDst, ant, Freq_ter, STTP, GeoType,latp,lonp,Rp) ") + SQL1;
						DB1.ExecuteSQL(SQL1);
					}
				}
			}
			rs.MoveNext();
		}//while
	}//if
	rs.Close();		DB1.Close();

/*
	IDstN.Delete(0);
	if(Nrow>0)
	{
		CString str1,str2 = _T("");
		for(long j=0 ; j<Nrow ;j++)
		{
			str1.Format(_T("(((IDst)=\'%s\'))"),GetFld(IDstN,j+1));
			str2 = str2 + _T(" OR ") + str1;
		}
		str2.Delete(0,4);	str2 = str2 + _T(";");
		CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE %s"),str2);
	}
	else
		CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE IDst=\'z\';");
*/

//	CDataBaseSTR.Format(_T("SELECT FStrig_hR.IDst, STtableGE06ASAL.STname, STtableGE06ASAL.STlat_deg, STtableGE06ASAL.STlon_deg, STtableGE06ASAL.Sth_agl, STtableGE06ASAL.TXfreq, STtableGE06ASAL.Power_eirp, STtableGE06ASAL.Azimuth, STtableGE06ASAL.Elevation, STtableGE06ASAL.ANTgain, STtableGE06ASAL.BWh, STtableGE06ASAL.BWv, STtableGE06ASAL.Polarization, STtableGE06ASAL.Antenna, STtableGE06ASAL.InsertionLoss, STtableGE06ASAL.RxSensitivity, STtableGE06ASAL.Srv, STtableGE06ASAL.STTP, STtableGE06ASAL.Emission, STtableGE06ASAL.AntID, STtableGE06ASAL.RXfreq, STtableGE06ASAL.radius, STtableGE06ASAL.NoiseFactor, STtableGE06ASAL.Sth_asll, STtableGE06ASAL.ctry, STtableGE06ASAL.SystemType1, STtableGE06ASAL.SystemType2, STtableGE06ASAL.Fragment, STtableGE06ASAL.StType, STtableGE06ASAL.AntCatID, STtableGE06ASAL.AntDir, STtableGE06ASAL.MaxEffHght, STtableGE06ASAL.AdmRefID, STtableGE06ASAL.AreaOfTrans, STtableGE06ASAL.NoticeType, STtableGE06ASAL.TVSys, STtableGE06ASAL.RefPlanCfg, STtableGE06ASAL.SysVar, STtableGE06ASAL.FreqVCarr, STtableGE06ASAL.ColorSys, STtableGE06ASAL.FreqSCarr, STtableGE06ASAL.OsetV12, STtableGE06ASAL.OsetV, STtableGE06ASAL.TVChannel, STtableGE06ASAL.FreqStabl, STtableGE06ASAL.VSWR, STtableGE06ASAL.SpectMask, STtableGE06ASAL.TerraKey, STtableGE06ASAL.Plan, STtableGE06ASAL.PlanEntry, STtableGE06ASAL.AssignCode, STtableGE06ASAL.SfnID, STtableGE06ASAL.GeoArea, STtableGE06ASAL.RXMode, STtableGE06ASAL.ERPTilt, STtableGE06ASAL.Tilt, STtableGE06ASAL.Offset, STtableGE06ASAL.StID, STtableGE06ASAL.AssocAllotID, STtableGE06ASAL.nb_sub_areas, STtableGE06ASAL.TypRefNetwk, STtableGE06ASAL.ERP_h_dbw, STtableGE06ASAL.ERP_v_dbw, STtableGE06ASAL.allotkey, FStrig_hR.ant, FStrig_hR.GeoType, FStrig_hR.STTP AS sttp1, FStrig_hR.Freq_ter, FStrig_hR.zone, FStrig_hR.latp, FStrig_hR.lonp, FStrig_hR.Rp FROM STtableGE06ASAL, FStrig_hR WHERE (((FStrig_hR.IDst)=Val([STtableGE06ASAL].[IDst])));"));
	CDataBaseSTR.Format(_T("SELECT FStrig_hR.IDst, STtableGE06ASAL.STname, STtableGE06ASAL.STlat_deg, STtableGE06ASAL.STlon_deg, STtableGE06ASAL.Sth_agl, STtableGE06ASAL.TXfreq, STtableGE06ASAL.Power_eirp, STtableGE06ASAL.Azimuth, STtableGE06ASAL.Elevation, STtableGE06ASAL.ANTgain, STtableGE06ASAL.BWh, STtableGE06ASAL.BWv, STtableGE06ASAL.Polarization, STtableGE06ASAL.Antenna, STtableGE06ASAL.InsertionLoss, STtableGE06ASAL.RxSensitivity, STtableGE06ASAL.Srv, STtableGE06ASAL.STTP, STtableGE06ASAL.Emission, STtableGE06ASAL.AntID, STtableGE06ASAL.RXfreq, STtableGE06ASAL.radius, STtableGE06ASAL.NoiseFactor, STtableGE06ASAL.Sth_asll, STtableGE06ASAL.ctry, STtableGE06ASAL.SystemType1, STtableGE06ASAL.SystemType2, STtableGE06ASAL.Fragment, STtableGE06ASAL.StType, STtableGE06ASAL.AntCatID, STtableGE06ASAL.AntDir, STtableGE06ASAL.MaxEffHght, STtableGE06ASAL.AdmRefID, STtableGE06ASAL.AreaOfTrans, STtableGE06ASAL.NoticeType, STtableGE06ASAL.TVSys, STtableGE06ASAL.RefPlanCfg, STtableGE06ASAL.SysVar, STtableGE06ASAL.FreqVCarr, STtableGE06ASAL.ColorSys, STtableGE06ASAL.FreqSCarr, STtableGE06ASAL.OsetV12, STtableGE06ASAL.OsetV, STtableGE06ASAL.TVChannel, STtableGE06ASAL.FreqStabl, STtableGE06ASAL.VSWR, STtableGE06ASAL.SpectMask, STtableGE06ASAL.TerraKey, STtableGE06ASAL.Plan, STtableGE06ASAL.PlanEntry, STtableGE06ASAL.AssignCode, STtableGE06ASAL.SfnID, STtableGE06ASAL.GeoArea, STtableGE06ASAL.RXMode, STtableGE06ASAL.ERPTilt, STtableGE06ASAL.Tilt, STtableGE06ASAL.Offset, STtableGE06ASAL.StID, STtableGE06ASAL.AssocAllotID, STtableGE06ASAL.nb_sub_areas, STtableGE06ASAL.TypRefNetwk, STtableGE06ASAL.ERP_h_dbw, STtableGE06ASAL.ERP_v_dbw, STtableGE06ASAL.allotkey, FStrig_hR.ant, FStrig_hR.GeoType, FStrig_hR.STTP AS sttp1, FStrig_hR.Freq_ter, FStrig_hR.zone, FStrig_hR.latp, FStrig_hR.lonp, FStrig_hR.Rp FROM %s, FStrig_hR WHERE (((FStrig_hR.IDst)=Val([STtableGE06ASAL].[IDst])));") , m_qSTtableGE06ASAL);
	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = FALSE;
	datadlg.m_Title = _T("Victim FXM Stations");
	if (datadlg.DoModal()==IDOK)
		NrowT = ((CSMS4DCApp *)AfxGetApp())->Nrow;
	
	return NrowT;
}

int CSMS4DCView::QGE06_IntToBCBT2FXM_Q1(long IDst ,double lat[], double lon[]) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	int n = 0;
	CString  strlat = _T("") , strlon = _T("");

	lat[0]=lat[1]=lat[2]=lat[3]=lat[4]=lat[5]=-999;
	lon[0]=lon[1]=lon[2]=lon[3]=lon[4]=lon[5]=-999;

//	tbl.Format(_T("SELECT Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, Link_TX WHERE (((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.TXID)=%ld) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("MULTIPOINT"));
	tbl.Format(_T("SELECT Link.lat1, Link.lon1, Link.lat2, Link.lon2, Link.lat3, Link.lon3, Link.lat4, Link.lon4, Link.lat5, Link.lon5, Link.lat6, Link.lon6 FROM Link, %s WHERE (((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.TXID)=%ld) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX , IDst, _T("MULTIPOINT"));
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
					
		rs.GetFieldValue(_T("lat1"),strlat);	rs.GetFieldValue(_T("lon1"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat2"),strlat);	rs.GetFieldValue(_T("lon2"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat3"),strlat);	rs.GetFieldValue(_T("lon3"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat4"),strlat);	rs.GetFieldValue(_T("lon4"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat5"),strlat);	rs.GetFieldValue(_T("lon5"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
		rs.GetFieldValue(_T("lat6"),strlat);	rs.GetFieldValue(_T("lon6"),strlon);
		if((strlat.GetLength()>0)&&(strlon.GetLength()>0))
		{
			lat[n] = atof(strlat);			lon[n] = atof(strlon);			n++;
		}
	}
	rs.Close();	DB1.Close();

	return n;
}


CString CSMS4DCView::QGE06_IntToBCBT2FXM_Q2(long IDst) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	int i = 0;
	CString  zone0 = _T("");
//	tbl.Format(_T("SELECT Link.zone FROM Link, Link_TX WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("ZONE"));
	tbl.Format(_T("SELECT Link.zone FROM Link, %s WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX, IDst, _T("ZONE"));
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();		
		rs.GetFieldValue(_T("zone"),zone0);
		i++;
	}
	rs.Close();	DB1.Close();
	return zone0;
}

void CSMS4DCView::QGE06_IntToBCBT2FXM_Q3(CString zone0,double *lat,double *lon,long n1) 
{
	if(zone0.GetLength()==1)		zone0 = zone0 + _T("  ");
	else if(zone0.GetLength()==2)	zone0 = zone0 + _T(" ");

	float *CRDARR0;	CRDARR0 = new float[2*n1];

	unsigned char CTYVEK[4]={""}, BCILR;
	strcpy((char *)CTYVEK,zone0);
	long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;
	float RLONLL, RLATLL, RLONUR, RLATUR , DENS=0;
	GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
	GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	

	long j = 0;
	while(!NOMORE)
	{
		GEOLIW( &ITYPE, CRDARR0, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
		if(NOMORE)	break;
		for(long p=0;p<NRCRD;p++)
		{
			lat[j] = CRDARR0[2*p+1];			//ITYPE=2  Deg.
			lon[j] = CRDARR0[2*p];
			j++;

		}//end for
	}//end while
	delete [] CRDARR0;
}

void CSMS4DCView::QGE06_IntToBCBT2FXM_Q4(long IDst , double *latci,double *lonci,double *Rci) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	int i = 0;
	CString  str = _T("");
//	tbl.Format(_T("SELECT Link.RecLat, Link.RecLon, Link.Radius FROM Link, Link_TX WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), IDst, _T("CIRCLE"));
	tbl.Format(_T("SELECT Link.RecLat, Link.RecLon, Link.Radius FROM Link, %s WHERE (((Link.TXID)=%ld) AND ((Link.ReceiverID)=[Link_TX].[ReceiverID]) AND ((Link.GeoType)=\'%s\'));"), m_qLink_TX , IDst, _T("CIRCLE"));
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		rs.GetFieldValue(_T("RecLat"),str);		*latci = atof(str);
		rs.GetFieldValue(_T("RecLon"),str);		*lonci = atof(str);
		rs.GetFieldValue(_T("Radius"),str);		*Rci = atof(str);
		i++;
	}
	rs.Close();	DB1.Close();
}


double CSMS4DCView::QGE06_XPD(long AntCatID) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	int i = 0;
	CString  str = _T("");
	tbl.Format(_T("SELECT AntCatID, AntName, XPD FROM AntCat WHERE (((AntCatID)=%ld));"), AntCatID);

	double XPD = 0;
	rs.Open(CRecordset::snapshot, tbl);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		rs.GetFieldValue(_T("XPD"),str);		XPD = atof(str);
		i++;
	}
	rs.Close();	DB1.Close();
	return XPD;
}


double CSMS4DCView::CNFS_Function_FXM(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
								double latCal,double lonCal,double CF,double  PR,
								int AntDisc, int ENV,double Ti,double kfactor,int ant,double hR,
								CString AntDir_W,CString AntCatID_W) 
{
	double  CNFS;
	CP154606_Functions CP154606;
	int az0[37];
	for(int i=0;i<=36;i++)		az0[i] = 10*i;
	double az_I2Cal = Azimuth_Deg(GeoLat_I,GeoLon_I,latCal,lonCal) ;
	double attH0_I[37], attV0_I[37];
	if(AntDir_I==_T("D"))
		GE84pattern(atol(AntCatID_I),attH0_I,attV0_I,Pol_I);
	else
		for(int i=0;i<36;i++)
		{
			attH0_I[i] = 0;		attV0_I[i] = 0;
		}
	attH0_I[36] = attH0_I[0];	attV0_I[36] = attV0_I[0];

	double attnH_I2Cal = Interp2(az0,attH0_I,az_I2Cal,37) ;
	double attnV_I2Cal = Interp2(az0,attV0_I,az_I2Cal,37) ;

	double ERPH,ERPV;
	if     (Pol_I==_T("H"))						ERPH = atof(ERP_h_dbw_I)-attnH_I2Cal;
	else if(Pol_I==_T("V"))						ERPV = atof(ERP_v_dbw_I)-attnV_I2Cal;
	else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{ERPH = atof(ERP_h_dbw_I)-attnH_I2Cal;	ERPV = atof(ERP_v_dbw_I)-attnV_I2Cal;}
	/////////////////////////// h1_I //////////////////////
	double h1_I, lat3km, lon3km, lat15km, lon15km;
	double dist_I2Cal = Distance_km(GeoLat_I,GeoLon_I,latCal,lonCal) ;

	OnDatabaseStationsindesktop2(GeoLat_I,GeoLon_I);
	double Hasl_I = LatLon2Hg(GeoLat_I,GeoLon_I);
	double Hasgl_I = Hasl_I + atof(Hagl_I);
	
	if (dist_I2Cal>=15.0)
	{
		reckon(GeoLat_I,GeoLon_I,  3.0 , az_I2Cal , &lat3km  , &lon3km) ;
		reckon(GeoLat_I,GeoLon_I, 15.0 , az_I2Cal , &lat15km , &lon15km) ;
		h1_I = Hasgl_I - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km , 120);
	}
	else
	{
		reckon(GeoLat_I,GeoLon_I, 0.2*dist_I2Cal , az_I2Cal , &lat3km  , &lon3km) ;
		reckon(GeoLat_I,GeoLon_I,     dist_I2Cal , az_I2Cal , &lat15km , &lon15km) ;
		h1_I = Hasgl_I - Points2HgAvr1(lat3km, lon3km, lat15km, lon15km , 120);
	}
	double ATTNantrec = 0, PolAntDisc = 0;
	if((AntDisc==1)&&(ant==1))
	{
		double az_Cal2I = Azimuth_Deg(latCal,lonCal,GeoLat_I,GeoLon_I) ;
		double attH0_W[37], attV0_W[37];
		if(AntDir_W==_T("D"))
			GE84pattern(atol(AntCatID_W),attH0_W,attV0_W,Pol_W);
		else
			for(int i=0;i<36;i++)
			{
				attH0_W[i] = 0;		attV0_W[i] = 0;
			}
		attH0_W[36] = attH0_W[0];	attV0_W[36] = attV0_W[0];

		if     (Pol_W==_T("H"))		ATTNantrec = Interp2(az0,attH0_W,az_Cal2I,37);
		else if(Pol_W==_T("V"))		ATTNantrec = Interp2(az0,attV0_W,az_Cal2I,37);
		PolAntDisc = QGE06_XPD(atol(AntCatID_W)); 
	}
	double Em = -999, EmH = -999, EmV = -999, EmI = -999;
	Em = E_P154606(GeoLat_I,GeoLon_I,latCal,lonCal, h1_I, Hasgl_I, Freq_I, kfactor, Ti, hR, ENV,0,50, 0);

	if     (Pol_I==_T("H"))						EmH = Em - 30.0 + ERPH;
	else if(Pol_I==_T("V"))						EmV = Em - 30.0 + ERPV;
	else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{EmH = Em - 30.0 + ERPH;	EmV = Em - 30.0 + ERPV;}

	if     (Pol_W==_T("H"))						EmI = 10.0*log10(pow(10.0 , (EmH-ATTNantrec)/10.0) + pow(10.0 , (EmV-PolAntDisc)/10.0));
	else if(Pol_W==_T("V"))						EmI = 10.0*log10(pow(10.0 , (EmH-PolAntDisc)/10.0) + pow(10.0 , (EmV-ATTNantrec)/10.0));
	else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	EmI = 10.0*log10(pow(10.0 , EmH/10.0) + pow(10.0 , EmV/10.0));

	double EmIT = EmI;

	CNFS = EmIT + PR + CF;
	return CNFS;
}

double CSMS4DCView::CNFS_FunctionAL_FXM(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
									double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,
									double lat_TP[],double lon_TP[],long NcontourT,double CF,double PR,
									int AntDisc, int ENV,double Ti,int ant,double hR,
									CString AntDir_W,CString AntCatID_W) 
{
	double  CNFS;
	CP154606_Functions CP154606;
	double latTx[7], lonTx[7] , ERPall[7];
	CString Band_I  = CP154606.GE06_Band(Freq_I);

	double attH0_W[37], attV0_W[37];
	int az0[37];
	for(int i=0;i<=36;i++)		az0[i] = 10*i;

	double DistLimit = 999999999999 , latmin, lonmin , Di1;
	for(long jTP=0;jTP<NcontourT;jTP++)
	{
		Di1 = Distance_km(latCal, lonCal,lat_TP[jTP],lon_TP[jTP]);
		DistLimit = min(DistLimit , Di1);
		if(DistLimit == Di1)
		{
			latmin = lat_TP[jTP];		lonmin = lon_TP[jTP];
		}
	}
	int N_Tx = CP154606.Table_RNs(latCal,lonCal, latmin,lonmin,Freq_I,Band_I,RPC_I,RN, ERPall,latTx,lonTx) ;

	double ERPH,ERPV, EmIT = 0;
	for(int ASi=0;ASi<N_Tx;ASi++)
	{
		if     (Pol_I==_T("H"))						ERPH = ERPall[ASi];
		else if(Pol_I==_T("V"))						ERPV = ERPall[ASi];
		else if((Pol_I==_T("M"))||(Pol_I==_T("U"))){ERPH = ERPall[ASi]-3.0;	ERPV = ERPall[ASi]-3.0;}
		double ATTNantrec = 0, PolAntDisc = 0;
		if((AntDisc==1)&&(ant==1))
		{
			double az_Cal2I = Azimuth_Deg(latCal,lonCal,latTx[ASi],lonTx[ASi]) ;
			if(AntDir_W==_T("D"))
				GE84pattern(atol(AntCatID_W),attH0_W,attV0_W,Pol_W);
			else
				for(int i=0;i<36;i++)
				{
					attH0_W[i] = 0;		attV0_W[i] = 0;
				}
			attH0_W[36] = attH0_W[0];	attV0_W[36] = attV0_W[0];

			if     (Pol_W==_T("H"))		ATTNantrec = Interp2(az0,attH0_W,az_Cal2I,37);
			else if(Pol_W==_T("V"))		ATTNantrec = Interp2(az0,attV0_W,az_Cal2I,37);
			PolAntDisc = QGE06_XPD(atol(AntCatID_W)); 
		}
		double Em = -999, EmH = -999, EmV = -999, Em1 = -999;
//		Em = E_P154606AL(latTx[ASi],lonTx[ASi],latCal,lonCal, 150, Freq_I, Ti,hR, ENV,0,50);
		Em = E_P154606AL_hR(latTx[ASi],lonTx[ASi],latCal,lonCal, 150, Freq_I, Ti,hR, ENV);
		if     (Pol_I==_T("H"))						EmH = Em - 30.0 + ERPH;
		else if(Pol_I==_T("V"))						EmV = Em - 30.0 + ERPV;
		else if((Pol_I==_T("M"))||(Pol_I==_T("U")))	{EmH = Em - 30.0 + ERPH;	EmV = Em - 30.0 + ERPV;}
		if     (Pol_W==_T("H"))						Em1 = 10.0*log10(pow(10.0 , (EmH-ATTNantrec)/10.0) + pow(10.0 , (EmV-PolAntDisc)/10.0));
		else if(Pol_W==_T("V"))						Em1 = 10.0*log10(pow(10.0 , (EmH-PolAntDisc)/10.0) + pow(10.0 , (EmV-ATTNantrec)/10.0));
		else if((Pol_W==_T("M"))||(Pol_W==_T("U")))	Em1 = 10.0*log10(pow(10.0 , EmH/10.0) + pow(10.0 , EmV/10.0));
		EmIT = EmIT + pow(10.0 , Em1/10.0);
	}
	EmIT = 10.0*log10(EmIT);

	CNFS = EmIT + PR + CF;
	return CNFS;
}

double CSMS4DCView::GE06UFS_FXM(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
								double latCal,double lonCal,double CF,double  PR,
								int AntDisc, int ENV,double Ti,double kfactor,int ant,double hR,
								CString NET_I,int PEC_I,CString SFNID_I, CString GeoArea_I, CString allotkey_I,
								CString	RN_I, CString RPC_I,CString AdmRefID_I,CString AntDir_W,CString AntCatID_W,
								CString sttp_W,CString Emission_W,CString SysType1_W,CString SysType2_W,CString Fragment_I,
								int GENERIC)
{
	double CNFS;

	if((NET_I==_T("ASA0"))||(PEC_I==1))
	{
		CNFS = CNFS_Function_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
								 GeoLat_I, GeoLon_I, Freq_I,Pol_I,Hagl_I,
								 AntDir_I,AntCatID_I,ERP_h_dbw_I, ERP_v_dbw_I,
								 latCal, lonCal, CF,PR,
								 AntDisc,ENV, Ti, kfactor, ant, hR, AntDir_W, AntCatID_W); 

	}//if((NET_I==_T("ASA0"))||(PEC_I==1))
	else if(PEC_I==2)
	{
		double CNFS_T1 = 0;
		CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN, ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN;
		long numAssign = QGE06_CArea_Q2(SFNID_I,&GeoLatN,&GeoLonN,
										&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
										&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN) ;
		for(int iAS = 0; iAS<numAssign ; iAS++)
		{
			CString Pol_Ii = GetFld(PolN,iAS+1),					AntDir_Ii = GetFld(AntDirN,iAS+1),
					AntCatID_Ii = GetFld(AntCatIDN,iAS+1),			ERP_h_dbw_Ii = GetFld(ERP_h_dbwN,iAS+1),
					ERP_v_dbw_Ii = GetFld(ERP_v_dbwN,iAS+1),		Hagl_Ii = GetFld(AntHeightAGLN,iAS+1);
			double  GeoLat_Ii = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_Ii = atof(GetFld(GeoLonN,iAS+1)),
					Freq_Ii = atof(GetFld(FrequencyN,iAS+1));

			double CNFSj = CNFS_Function_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
									 GeoLat_Ii, GeoLon_Ii, Freq_Ii,Pol_Ii,Hagl_Ii,
									 AntDir_Ii,AntCatID_Ii,ERP_h_dbw_Ii, ERP_v_dbw_Ii,
									 latCal, lonCal, CF,PR,
									 AntDisc,ENV, Ti, kfactor, ant, hR,AntDir_W, AntCatID_W); 

			CNFS_T1 = CNFS_T1 + pow(10.0, (CNFSj)/10.0);

		}//for  iAS
		CNFS = 10.0*log10(CNFS_T1);

	}//if(PEC_I==2)
	else if(PEC_I==3)
	{
		if(GeoArea_I.IsEmpty())
		{
			CString contourkeyN , nb_test_ptsN;
			long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_I) , &contourkeyN , &nb_test_ptsN);
			long *contourkeyI;		contourkeyI = new long[contourkeyNum];
			long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
			double dum;
			long NcontourT = 0;
			for(long i=0;i<contourkeyNum;i++)
			{
				contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
				nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
				NcontourT = NcontourT + nb_test_ptsI[i];
			}
			double * lat_TP;   lat_TP = new double[NcontourT];
			double * lon_TP;   lon_TP = new double[NcontourT];
			double * y;		y = lat_TP;
			double * x;		x = lon_TP;
			for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
			{
				CString lat_tpStr, lon_tpStr;
				long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
				for(long jTP=0;jTP<n_tp;jTP++)
				{
					*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
					*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
				}
			}
			CString RN = _T("");
			if     (NET_I==_T("ALT3"))							RN = RN_I;
			else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
			else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

			CNFS = CNFS_FunctionAL_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
										 latCal, lonCal, Freq_I,Pol_I,RPC_I, RN,
										 lat_TP, lon_TP, NcontourT, CF, PR,
										 AntDisc,ENV, Ti, ant, hR,
										 AntDir_W,AntCatID_W); 

			delete [] contourkeyI;		delete [] nb_test_ptsI;	delete [] lat_TP;	delete [] lon_TP;
		}//if GeoArea_I
		else
		{
			CString lat_tpSTR, lon_tpSTR;
			double dum;
			long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_I, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
			double * lat_TP;   lat_TP = new double[NcontourT];
			double * lon_TP;   lon_TP = new double[NcontourT];
			for(long jTP=0;jTP<NcontourT;jTP++)
			{
				lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
				lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
			}
			CString RN = _T("");
			if     (NET_I==_T("ALT3"))							RN = RN_I;
			else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
			else if((NET_I==_T("ALS3"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

			CNFS = CNFS_FunctionAL_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
										 latCal, lonCal, Freq_I,Pol_I,RPC_I, RN,
										 lat_TP, lon_TP, NcontourT, CF, PR,
										 AntDisc,ENV, Ti, ant, hR,
										 AntDir_W,AntCatID_W); 

			delete [] lat_TP;		delete [] lon_TP;
		}//else GeoArea_I
	}//if(PEC_I==3)
	else if(PEC_I==4)
	{
		if((NET_I==_T("ASS4"))||(NET_I==_T("AST4")))	/////////A4_1
		{
			double CNFSsfn = 0, CNFSallot = 0;
			//+++++++++++++++Assignment++++++++++++++++++++++++++++++++++++++++
			CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN;
			long numAssign = QGE06_CArea_Q2(SFNID_I,&GeoLatN,&GeoLonN,
											&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
											&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN,1) ;
			double CNFSjAS = 0;
			for(int iAS = 0; iAS<numAssign ; iAS++)
			{
				CString Pol_Ii = GetFld(PolN,iAS+1),					AntDir_Ii = GetFld(AntDirN,iAS+1),
						AntCatID_Ii = GetFld(AntCatIDN,iAS+1),			ERP_h_dbw_Ii = GetFld(ERP_h_dbwN,iAS+1),
						ERP_v_dbw_Ii = GetFld(ERP_v_dbwN,iAS+1),		Hagl_Ii = GetFld(AntHeightAGLN,iAS+1);
				double  GeoLat_Ii = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_Ii = atof(GetFld(GeoLonN,iAS+1)),
						Freq_Ii = atof(GetFld(FrequencyN,iAS+1));

				double CNFSj = CNFS_Function_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
										 GeoLat_Ii, GeoLon_Ii, Freq_Ii,Pol_Ii,Hagl_Ii,
										 AntDir_Ii,AntCatID_Ii,ERP_h_dbw_Ii, ERP_v_dbw_Ii,
										 latCal, lonCal, CF,PR,
										 AntDisc,ENV, Ti, kfactor, ant, hR,AntDir_W, AntCatID_W); 

				CNFSjAS = CNFSjAS + pow(10.0, (CNFSj)/10.0);
			}//for  iAS
			CNFSsfn = 10.0*log10(CNFSjAS);

			//+++++++++++++++Allotment++++++++++++++++++++++++++++++++++++++++
			CP154606_Functions CP154606;

			CString AllotmentSTR = QGE06_BCBT_A4_1(SFNID_I) ;
			CString allotkey_Ii = GetFld(AllotmentSTR,1) ;

			CString NoticeType_Ii = GetFld(AllotmentSTR,3), GeoArea_Ii = GetFld(AllotmentSTR,9),
					Pol_Ii = GetFld(AllotmentSTR,10),		SYS_VAR_Ii = GetFld(AllotmentSTR,11),
					SpecMask_Ii = GetFld(AllotmentSTR,12);
			if(GeoArea_Ii.IsEmpty())
			{
				CString contourkeyN , nb_test_ptsN;
				long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_Ii) , &contourkeyN , &nb_test_ptsN);
				long *contourkeyI;		contourkeyI = new long[contourkeyNum];
				long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
				double dum;
				long NcontourT = 0;
				for(long i=0;i<contourkeyNum;i++)
				{
					contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
					nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
					NcontourT = NcontourT + nb_test_ptsI[i];
				}
				double * lat_TP;   lat_TP = new double[NcontourT];
				double * lon_TP;   lon_TP = new double[NcontourT];
				double * y;		y = lat_TP;
				double * x;		x = lon_TP;
				for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
				{
					CString lat_tpStr, lon_tpStr;
					long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
					for(long jTP=0;jTP<n_tp;jTP++)
					{
						*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
						*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
					}
				}
		//00000000000000000000000000000000000000000000000000000000000000000000000000
				CString STN_Ii = CP154606.GE06_STN(GetFld(AllotmentSTR,2),GetFld(AllotmentSTR,3));
				int PEC_Ii = GE06_PEC(GetFld(AllotmentSTR,4) , GetFld(AllotmentSTR,5) , GetFld(AllotmentSTR,6) , SFNID_I , STN_Ii) ;
				CString NET_Ii;	NET_Ii.Format("%s%d",STN_Ii,PEC_Ii);
				CString RPC_Ii = GetFld(AllotmentSTR,7);
				CString RN_Ii = _T("");
				if     (NET_Ii==_T("ALT4"))							RN_Ii = GetFld(AllotmentSTR,8);
				else if((NET_Ii==_T("ALS4"))&&(RPC_Ii==_T("RPC4")))	RN_Ii = _T("RN5");
				else if((NET_Ii==_T("ALS4"))&&(RPC_Ii==_T("RPC5")))	RN_Ii = _T("RN6");


				double PR_Ii;
				if(GENERIC==1)	PR_Ii = 0;
				else			PR_Ii = CP154606.GE06_PR_BCBT2FXM(Freq_W, sttp_W, Emission_W, SysType1_W, SysType2_W,
											 Fragment_I, NoticeType_Ii, Freq_I, "", RPC_Ii,
											 SYS_VAR_Ii, 0, "", 0, SpecMask_Ii);

		//00000000000000000000000000000000000000000000000000000000000000000000000000
				double CNFSj = CNFS_FunctionAL_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
											 latCal, lonCal, Freq_I,Pol_Ii,RPC_Ii, RN_Ii,
											 lat_TP, lon_TP, NcontourT, CF, PR_Ii,
											 AntDisc,ENV, Ti, ant, hR,
											 AntDir_W,AntCatID_W); 

				CNFSallot = CNFSj;
				delete [] contourkeyI;	delete [] nb_test_ptsI;		delete [] lat_TP;		delete [] lon_TP;
			}//if GeoArea_I
			else
			{
				CString lat_tpSTR, lon_tpSTR;
				double dum;
				long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_Ii, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
				double * lat_TP;   lat_TP = new double[NcontourT];
				double * lon_TP;   lon_TP = new double[NcontourT];
				for(long jTP=0;jTP<NcontourT;jTP++)
				{
					lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
					lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
				}
		//00000000000000000000000000000000000000000000000000000000000000000000000000
				CString STN_Ii = CP154606.GE06_STN(GetFld(AllotmentSTR,2),GetFld(AllotmentSTR,3));
				int PEC_Ii = GE06_PEC(GetFld(AllotmentSTR,4) , GetFld(AllotmentSTR,5) , GetFld(AllotmentSTR,6) , SFNID_I , STN_Ii) ;
				CString NET_Ii;	NET_Ii.Format("%s%d",STN_Ii,PEC_Ii);
				CString RPC_Ii = GetFld(AllotmentSTR,7);
				CString RN_Ii = _T("");
				if     (NET_Ii==_T("ALT4"))							RN_Ii = GetFld(AllotmentSTR,8);
				else if((NET_Ii==_T("ALS4"))&&(RPC_Ii==_T("RPC4")))	RN_Ii = _T("RN5");
				else if((NET_Ii==_T("ALS4"))&&(RPC_Ii==_T("RPC5")))	RN_Ii = _T("RN6");

				double PR_Ii;
				if(GENERIC==1)	PR_Ii = 0;
				else			PR_Ii = CP154606.GE06_PR_BCBT2FXM(Freq_W, sttp_W, Emission_W, SysType1_W, SysType2_W,
											 Fragment_I, NoticeType_Ii, Freq_I, "", RPC_Ii,
											 SYS_VAR_Ii, 0, "", 0, SpecMask_Ii);

		//00000000000000000000000000000000000000000000000000000000000000000000000000
				double CNFSj = CNFS_FunctionAL_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
											 latCal, lonCal, Freq_I,Pol_Ii,RPC_Ii, RN_Ii,
											 lat_TP, lon_TP, NcontourT, CF, PR_Ii,
											 AntDisc,ENV, Ti, ant, hR,
											 AntDir_W,AntCatID_W); 
				CNFSallot = CNFSj;
				delete [] lat_TP;	delete [] lon_TP;
			}//else GeoArea_I

			CNFS = max(CNFSsfn , CNFSallot);

		}/////////A4_1

		else if((NET_I==_T("ALS4"))||(NET_I==_T("ALT4")))	/////////A4_2
		{
			CP154606_Functions CP154606;

			double CNFSsfn = 0, CNFSallot = 0;
			//+++++++++++++++Assignment++++++++++++++++++++++++++++++++++++++++
			CString GeoLatN , GeoLonN , FrequencyN,PolN,ERP_h_dbwN,ERP_v_dbwN,AntCatIDN,AntHeightAGLN,AntIDN,MaxEffHghtN ,AntDirN ,IDstN, NoticeTypeN, RPCN , SysVarN, RxModeN, SpecMaskN;
			long numAssign = QGE06_CArea_Q2_1(SFNID_I,&GeoLatN,&GeoLonN,
											&FrequencyN,&PolN,&ERP_h_dbwN,&ERP_v_dbwN,
											&AntCatIDN,&AntHeightAGLN,&AntIDN,&MaxEffHghtN,&AntDirN,&IDstN,
											&NoticeTypeN, &RPCN , &SysVarN, &RxModeN, &SpecMaskN) ;
	
			CString NoticeType_Ii = GetFld(NoticeTypeN,1),	RPC_Ii = GetFld(RPCN,1),
					SpecMask_Ii = GetFld(SpecMaskN,1),		SysVar_Ii = GetFld(SysVarN,1);
		
			double PR_Ii;
			if(GENERIC==1)	PR_Ii = 0;
			else			PR_Ii = CP154606.GE06_PR_BCBT2FXM(Freq_W, sttp_W, Emission_W, SysType1_W, SysType2_W,
										 Fragment_I, NoticeType_Ii, Freq_I, "", RPC_Ii,
										 SysVar_Ii, 0, "", 0, SpecMask_Ii);
			double CNFSjAS = 0;
			for(int iAS = 0; iAS<numAssign ; iAS++)
			{
				CString Pol_Ii = GetFld(PolN,iAS+1),					AntDir_Ii = GetFld(AntDirN,iAS+1),
						AntCatID_Ii = GetFld(AntCatIDN,iAS+1),			ERP_h_dbw_Ii = GetFld(ERP_h_dbwN,iAS+1),
						ERP_v_dbw_Ii = GetFld(ERP_v_dbwN,iAS+1),		Hagl_Ii = GetFld(AntHeightAGLN,iAS+1);
				double  GeoLat_Ii = atof(GetFld(GeoLatN,iAS+1)),		GeoLon_Ii = atof(GetFld(GeoLonN,iAS+1));

				double CNFSj = CNFS_Function_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
										 GeoLat_Ii, GeoLon_Ii, Freq_I,Pol_Ii,Hagl_Ii,
										 AntDir_Ii,AntCatID_Ii,ERP_h_dbw_Ii, ERP_v_dbw_Ii,
										 latCal, lonCal, CF,PR_Ii,
										 AntDisc,ENV, Ti, kfactor, ant, hR,AntDir_W, AntCatID_W); 

				CNFSjAS = CNFSjAS + pow(10.0, (CNFSj)/10.0);
			}//for  iAS
			CNFSsfn = 10.0*log10(CNFSjAS);
	
			//+++++++++++++++Allotment++++++++++++++++++++++++++++++++++++++++

			if(GeoArea_I.IsEmpty())
			{
				CString contourkeyN , nb_test_ptsN;
				long contourkeyNum = QGE06_BCBT_A3_2(atol(allotkey_I) , &contourkeyN , &nb_test_ptsN);
				long *contourkeyI;		contourkeyI = new long[contourkeyNum];
				long *nb_test_ptsI;		nb_test_ptsI = new long[contourkeyNum];
				double dum;
				long NcontourT = 0;
				for(long i=0;i<contourkeyNum;i++)
				{
					contourkeyI[i] = atol(GetFld(contourkeyN,i+1));
					nb_test_ptsI[i] = atol(GetFld(nb_test_ptsN,i+1));
					NcontourT = NcontourT + nb_test_ptsI[i];
				}
				double * lat_TP;   lat_TP = new double[NcontourT];
				double * lon_TP;   lon_TP = new double[NcontourT];
				double * y;		y = lat_TP;
				double * x;		x = lon_TP;
				for(long iCNUM=0;iCNUM<contourkeyNum;iCNUM++)
				{
					CString lat_tpStr, lon_tpStr;
					long n_tp = QGE06_BCBT_A3_1(contourkeyI[iCNUM], nb_test_ptsI[iCNUM], &lat_tpStr, &lon_tpStr, &dum, &dum) ;
					for(long jTP=0;jTP<n_tp;jTP++)
					{
						*y = atof(GetFld(lat_tpStr,jTP+1));	y++;
						*x = atof(GetFld(lon_tpStr,jTP+1));	x++;
					}
				}
				CString RN = _T("");
				if     (NET_I==_T("ALT4"))							RN = RN_I;
				else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
				else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

				double CNFSj = CNFS_FunctionAL_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
							 latCal, lonCal, Freq_I,Pol_I,RPC_I, RN,
							 lat_TP, lon_TP, NcontourT, CF, PR,
							 AntDisc,ENV, Ti, ant, hR,
							 AntDir_W,AntCatID_W); 
				
				CNFSallot = CNFSj;
				delete [] contourkeyI;	delete [] nb_test_ptsI;	delete [] lat_TP;		delete [] lon_TP;
			}//if GeoArea_I
			else
			{
				CString lat_tpSTR, lon_tpSTR;
				double dum;
				long NcontourT = QGE06_BCBT_Aux_Border(GeoArea_I, &lat_tpSTR, &lon_tpSTR, &dum, &dum) ;
				double * lat_TP;   lat_TP = new double[NcontourT];
				double * lon_TP;   lon_TP = new double[NcontourT];
				for(long jTP=0;jTP<NcontourT;jTP++)
				{
					lat_TP[jTP] =  atof(GetFld(lat_tpSTR , jTP+1));
					lon_TP[jTP] =  atof(GetFld(lon_tpSTR , jTP+1));
				}
				CString RN = _T("");
				if     (NET_I==_T("ALT4"))							RN = RN_I;
				else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC4")))	RN = _T("RN5");
				else if((NET_I==_T("ALS4"))&&(RPC_I==_T("RPC5")))	RN = _T("RN6");

				double CNFSj = CNFS_FunctionAL_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
							 latCal, lonCal, Freq_I,Pol_I,RPC_I, RN,
							 lat_TP, lon_TP, NcontourT, CF, PR,
							 AntDisc,ENV, Ti, ant, hR,
							 AntDir_W,AntCatID_W); 

				CNFSallot = CNFSj;
				delete [] lat_TP;		delete [] lon_TP;
			}//else GeoArea_I

			CNFS = max(CNFSsfn , CNFSallot);
			
		}/////////A4_2

	}//if(PEC_I==4)
	else if(PEC_I==5)
	{
		if((NET_I==_T("ASS5"))||(NET_I==_T("AST5")))	/////////A5_1
		{
			CNFS = CNFS_Function_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
									 GeoLat_I, GeoLon_I, Freq_I,Pol_I,Hagl_I,
									 AntDir_I,AntCatID_I,ERP_h_dbw_I, ERP_v_dbw_I,
									 latCal, lonCal, CF,PR,
									 AntDisc,ENV, Ti, kfactor, ant, hR,AntDir_W, AntCatID_W); 
		}	/////////A5_1

		else if((NET_I==_T("ALS5"))||(NET_I==_T("ALT5")))	/////////A5_2
		{
			CP154606_Functions CP154606;
		
			CString ASstr = QGE06_CArea_Q4(AdmRefID_I);
			CString IDst_Ii = GetFld(ASstr,1);
			CString Pol_Ii = GetFld(ASstr,2),			ERP_h_dbw_Ii = GetFld(ASstr,5),
					ERP_v_dbw_Ii = GetFld(ASstr,6),		AntDir_Ii = GetFld(ASstr,7),
					AntCatID_Ii = GetFld(ASstr,8),		Hagl_Ii = GetFld(ASstr,9),
					NoticeType_Ii = GetFld(ASstr,10),	RPC_Ii = GetFld(ASstr,11),
					SYS_VAR_Ii = GetFld(ASstr,12),		SpecMask_Ii = GetFld(ASstr,14);
			double  GeoLat_Ii = atof(GetFld(ASstr,3)),	GeoLon_Ii = atof(GetFld(ASstr,4));

			double PR_Ii;
			if(GENERIC==1)	PR_Ii = 0;
			else			PR_Ii = CP154606.GE06_PR_BCBT2FXM(Freq_W, sttp_W, Emission_W, SysType1_W, SysType2_W,
										 Fragment_I, NoticeType_Ii, Freq_I, "", RPC_Ii,
										 SYS_VAR_Ii, 0, "", 0, SpecMask_Ii);

			CNFS = CNFS_Function_FXM_0( GeoLat_W, GeoLon_W, Freq_W,Pol_W,Fragment_W,
									 GeoLat_Ii, GeoLon_Ii, Freq_I,Pol_Ii,Hagl_Ii,
									 AntDir_Ii,AntCatID_Ii,ERP_h_dbw_Ii, ERP_v_dbw_Ii,
									 latCal, lonCal, CF,PR_Ii,
									 AntDisc,ENV, Ti, kfactor, ant, hR,AntDir_W, AntCatID_W); 
		}	/////////A5_2

	}//if(PEC_I==5)

	return CNFS;
}

CString CSMS4DCView::QGE06_IntFrom_Qx(int type) 
{
	CString CDataBaseSTR, Selx = _T("");
///	if	   (type==0)	CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT1' Or (NoticeType)='GT1' Or (NoticeType)='DS1' Or (NoticeType)='GS1') AND ((AssignCode)='L' Or (AssignCode)='S' Or (AssignCode) Is Null Or (AssignCode)='')) OR (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT2' Or (NoticeType)='GT2' Or (NoticeType)='DS2' Or (NoticeType)='GS2'));");
//	if	   (type==0)	CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT1' Or (NoticeType)='GT1' Or (NoticeType)='DS1' Or (NoticeType)='GS1') AND ((AssignCode)='L' Or (AssignCode)='S' Or (AssignCode) Is Null Or (AssignCode)='' Or (AssignCode)='C')) OR (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT2' Or (NoticeType)='GT2' Or (NoticeType)='DS2' Or (NoticeType)='GS2'));");
//	else if(type==1)	CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06A'));");

	if	   (type==0)	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT1' Or (NoticeType)='GT1' Or (NoticeType)='DS1' Or (NoticeType)='GS1') AND ((AssignCode)='L' Or (AssignCode)='S' Or (AssignCode) Is Null Or (AssignCode)='' Or (AssignCode)='C')) OR (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT2' Or (NoticeType)='GT2' Or (NoticeType)='DS2' Or (NoticeType)='GS2'));") , m_qSTtableGE06ASAL);
	else if(type==1)	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06A'));") , m_qSTtableGE06ASAL);

	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	CDataBaseLDLG datadlg;
	if	   (type==0)	datadlg.m_Title = _T("Select One Victim Assignment / Allotment");
	else if(type==1)	datadlg.m_Title = _T("Select One Victim Assignment");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
		else
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
		}
	}
	return Selx;
}

int CSMS4DCView::QGE06_IntFromBCBT2DBCBT_Qy(CString IDst_WT, int nIDst_WT, CString allotkey_WT, int nallotkey_WT, double GRlat, double GRlon, double SR, double Freq_W, double FR) 
{
	int NrowT = 0, Nrow = 0;
	CString CDataBaseSTR = _T("");

	double dumy,  lonmin , lonmax , latmin , latmax ,rng_km = SR , fmin , fmax;
	fmin = Freq_W - FR;
	fmax = Freq_W + FR;

	reckon(GRlat,GRlon, rng_km,  0.0,&latmax,&dumy) ;
	reckon(GRlat,GRlon, rng_km,180.0,&latmin,&dumy) ;
	reckon(GRlat,GRlon, rng_km, 90.0,&dumy,&lonmax) ;
	reckon(GRlat,GRlon, rng_km,270.0,&dumy,&lonmin) ;

//	CDataBaseSTR.Format(_T("SELECT * FROM CommonFields WHERE (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT1' Or (NoticeType)='GT1' Or (NoticeType)='DS1' Or (NoticeType)='GS1') AND ((GeoLat)>=%lf And (GeoLat)<=%lf) AND ((GeoLon)>=%lf And (GeoLon)<=%lf) AND ((Frequency)>=%lf And (Frequency)<=%lf) AND ((AssignCode)='S' Or (AssignCode)='L' Or (AssignCode) Is Null Or (AssignCode)='')) OR (((Fragment)='GE06A') AND ((GeoLat)>=%lf And (GeoLat)<=%lf) AND ((GeoLon)>=%lf And (GeoLon)<=%lf) AND ((Frequency)>=%lf And (Frequency)<=%lf)) OR (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT2' Or (NoticeType)='GT2' Or (NoticeType)='DS2' Or (NoticeType)='GS2') AND ((Frequency)>=%lf And (Frequency)<=%lf));"), latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax);
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT1' Or (NoticeType)='GT1' Or (NoticeType)='DS1' Or (NoticeType)='GS1') AND ((GeoLat)>=%lf And (GeoLat)<=%lf) AND ((GeoLon)>=%lf And (GeoLon)<=%lf) AND ((Frequency)>=%lf And (Frequency)<=%lf) AND ((AssignCode)='S' Or (AssignCode)='L' Or (AssignCode) Is Null Or (AssignCode)='')) OR (((Fragment)='GE06A') AND ((GeoLat)>=%lf And (GeoLat)<=%lf) AND ((GeoLon)>=%lf And (GeoLon)<=%lf) AND ((Frequency)>=%lf And (Frequency)<=%lf)) OR (((Fragment)='GE06D' Or (Fragment)='RC06') AND ((NoticeType)='DT2' Or (NoticeType)='GT2' Or (NoticeType)='DS2' Or (NoticeType)='GS2') AND ((Frequency)>=%lf And (Frequency)<=%lf));"), m_qCommonFields,latmin, latmax, lonmin, lonmax, fmin, fmax,latmin, latmax, lonmin, lonmax, fmin, fmax, fmin, fmax);

	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;		CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	double STlat_deg , STlon_deg;
	CString str, IDst, GeoArea , IDstN = _T(""), allotkey , allotkeyN = _T("");

	rs.Open(CRecordset::snapshot, CDataBaseSTR);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("GeoLat"),str);		STlat_deg = atof(str);
			rs.GetFieldValue(_T("GeoLon"),str);		STlon_deg = atof(str);
			rs.GetFieldValue(_T("GeoArea"),GeoArea);
			rs.GetFieldValue(_T("allotkey"),allotkey);

			if(IDst==_T("---"))
			{
				int flagID = IDstCompare(allotkey, allotkey_WT, nallotkey_WT);
				if(flagID==0)
				{
					BOOL uflag;
					if(GeoArea.IsEmpty())		uflag = QGE06_CArea_Q1(atol(allotkey),GRlat,GRlon,SR);
					else						uflag = QGE06_IntTo_Q5(GeoArea,GRlat,GRlon,SR);
					if(uflag)
					{
						IDstN = IDstN + _T(",") + IDst;
						allotkeyN = allotkeyN + _T(",") + allotkey;
						Nrow++;
					}
				}
			}
			else
			{
				int flagID = IDstCompare(IDst, IDst_WT, nIDst_WT);
				if(flagID==0)
				{
					double dist = Distance_km(GRlat,GRlon,STlat_deg,STlon_deg);
					if((dist <= SR)&&(dist > 0.0000001))
					{
						IDstN = IDstN + _T(",") + IDst;
						allotkeyN = allotkeyN + _T(",") + allotkey;
						Nrow++;
					}
				}
			}
			rs.MoveNext();
		}//while
	}//if
	rs.Close();		DB1.Close();

	IDstN.Delete(0);	allotkeyN.Delete(0);
	if(Nrow>0)
	{
		CString str1,str2 = _T("");
		for(long j=0 ; j<Nrow ;j++)
		{
			str1.Format(_T("(((IDst)=\'%s\') AND ((allotkey)=\'%s\'))"),GetFld(IDstN,j+1),GetFld(allotkeyN,j+1));
			str2 = str2 + _T(" OR ") + str1;
		}
		str2.Delete(0,4);	str2 = str2 + _T(";");
//		CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE %s"),str2);
		CDataBaseSTR.Format(_T("SELECT * FROM %s  WHERE  %s "),m_qSTtableGE06ASAL,str2);
	}
	else	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE IDst=\'z\';") , m_qSTtableGE06ASAL);
//	else	CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE IDst=\'z\';");

	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = FALSE;
	datadlg.m_Title = _T("Interferer Assignments / Allotments");
	if (datadlg.DoModal()==IDOK)
		NrowT = ((CSMS4DCApp *)AfxGetApp())->Nrow;
	
	return NrowT;
}

long CSMS4DCView::QGE06_IntFrom_Q2(CString SfnID_I,CString IDst_I,CString *IDst,CString *str_out,
								   CString RLONbs,CString RLATbs,
								   CString P_out,
								   int mode) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

//	if(mode==0)			tbl.Format(_T("SELECT * FROM CommonFields WHERE ((IDst<>\'---\') AND (SfnID=\'%s\'));"), SfnID_I);
//	else if(mode==1)	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));"), SfnID_I);
	if(mode==0)			tbl.Format(_T("SELECT * FROM %s WHERE ((IDst<>\'---\') AND (SfnID=\'%s\'));"), m_qCommonFields,SfnID_I);
	else if(mode==1)	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>'---') AND ((SfnID)=\'%s\') AND ((NoticeType)='DS1' Or (NoticeType)='GS1' Or (NoticeType)='DT1' Or (NoticeType)='GT1') AND ((AssignCode)='L'));"), m_qCommonFields,SfnID_I);

	CString adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,Pol_I,str_out1;
	rs.Open(CRecordset::snapshot, tbl);
	long c = 0;
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),str);				*IDst = *IDst + _T(",") + str;

			rs.GetFieldValue(_T("Country"),ctry_I);
			rs.GetFieldValue(_T("SiteName"),SiteName_I);
			rs.GetFieldValue(_T("AdmRefID"),AdmRefID_I);
			rs.GetFieldValue(_T("NoticeType"),NoticeType_I);
			rs.GetFieldValue(_T("PlanEntry"),PEC_I);
			rs.GetFieldValue(_T("AssignCode"),AssignCode_I);
			rs.GetFieldValue(_T("Frequency"),Freq_I);
			rs.GetFieldValue(_T("Pol"),Pol_I);

	//		if		(ctry_I.GetLength()==1)		ctry_I = ctry_I + _T("  ");
	//		else if (ctry_I.GetLength()==2)		ctry_I = ctry_I + _T(" ");
	//		GEOCTYA((BYTE *)ctry_I.GetBufferSetLength(3), (BYTE *)adm_I.GetBufferSetLength(3));
			adm_I = Cty2AdmGE06(&ctry_I);

			c++;
			rs.MoveNext();
			if(str==IDst_I)		str_out1.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s"), _T("W"), _T("AS"),adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
			else				str_out1.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s"), _T("L"), _T("AS"),adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);

			*str_out = *str_out + _T(",") + str_out1;
		}
	}
	rs.Close();	DB1.Close();
	(*IDst).Delete(0);
	(*str_out).Delete(0);
	return c;
}

CString CSMS4DCView::QGE06_IntFrom_Q3(CString SfnID_I,
								   CString RLONbs,CString RLATbs,
								   CString P_out,
								   CString *str_out) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)='---') AND ((SfnID)=\'%s\'));") ,SfnID_I);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)='---') AND ((SfnID)=\'%s\'));") ,m_qCommonFields,SfnID_I);
	rs.Open(CRecordset::snapshot, tbl);
	
	CString adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,Pol_I,str_out1,allotkey_I;

	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();

		rs.GetFieldValue(_T("Country"),ctry_I);
		rs.GetFieldValue(_T("SiteName"),SiteName_I);
		rs.GetFieldValue(_T("AdmRefID"),AdmRefID_I);
		rs.GetFieldValue(_T("NoticeType"),NoticeType_I);
		rs.GetFieldValue(_T("PlanEntry"),PEC_I);
		rs.GetFieldValue(_T("AssignCode"),AssignCode_I);
		rs.GetFieldValue(_T("Frequency"),Freq_I);
		rs.GetFieldValue(_T("Pol"),Pol_I);
		rs.GetFieldValue(_T("allotkey"),allotkey_I);

//		if		(ctry_I.GetLength()==1)		ctry_I = ctry_I + _T("  ");
//		else if (ctry_I.GetLength()==2)		ctry_I = ctry_I + _T(" ");
//		GEOCTYA((BYTE *)ctry_I.GetBufferSetLength(3), (BYTE *)adm_I.GetBufferSetLength(3));
		adm_I = Cty2AdmGE06(&ctry_I);

		str_out1.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s"), _T("L"), _T("AL"), adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
	}
	rs.Close();	DB1.Close();
	*str_out = str_out1;

	return allotkey_I;
}


CString CSMS4DCView::QGE06_IntFrom_Q4(CString AdmRefID,CString SfnID_I,
								CString RLONbs,CString RLATbs,
								CString P_out,
								CString *str_out) 
{
	CString  allotkey , tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)=\'---\') AND ((AdmRefID)=\'%s\') AND ((SfnID)='' Or (SfnID) Is Null));"),AdmRefID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)=\'---\') AND ((AdmRefID)=\'%s\') AND ((SfnID)='' Or (SfnID) Is Null));"),m_qCommonFields, AdmRefID);
	rs.Open(CRecordset::snapshot, tbl);
	
	CString adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,Pol_I,str_out1,allotkey_I;
	
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();

		rs.GetFieldValue(_T("Country"),ctry_I);
		rs.GetFieldValue(_T("SiteName"),SiteName_I);
		rs.GetFieldValue(_T("AdmRefID"),AdmRefID_I);
		rs.GetFieldValue(_T("NoticeType"),NoticeType_I);
		rs.GetFieldValue(_T("PlanEntry"),PEC_I);
		rs.GetFieldValue(_T("AssignCode"),AssignCode_I);
		rs.GetFieldValue(_T("Frequency"),Freq_I);
		rs.GetFieldValue(_T("Pol"),Pol_I);
		rs.GetFieldValue(_T("allotkey"),allotkey_I);

//		if		(ctry_I.GetLength()==1)		ctry_I = ctry_I + _T("  ");
//		else if (ctry_I.GetLength()==2)		ctry_I = ctry_I + _T(" ");
//		GEOCTYA((BYTE *)ctry_I.GetBufferSetLength(3), (BYTE *)adm_I.GetBufferSetLength(3));
		adm_I = Cty2AdmGE06(&ctry_I);

		str_out1.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s"), _T("L"), _T("AL"), adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
	}
	rs.Close();	DB1.Close();
	*str_out = str_out1;

	return allotkey_I;
}

CString CSMS4DCView::QGE06_IntFrom_Q5(CString AssocAllotID,
								CString RLONbs,CString RLATbs,
								CString P_out,
								CString *str_out) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR , str1 = _T("");
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE (((IDst)<>\'---\') AND ((AssocAllotID)=\'%s\'));"),AssocAllotID);
	tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)<>\'---\') AND ((AssocAllotID)=\'%s\'));"),m_qCommonFields,AssocAllotID);
	rs.Open(CRecordset::snapshot, tbl);

	CString adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,Pol_I,str_out1,IDst_I,SfnID_I;

	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		rs.GetFieldValue(_T("Country"),ctry_I);
		rs.GetFieldValue(_T("SiteName"),SiteName_I);
		rs.GetFieldValue(_T("AdmRefID"),AdmRefID_I);
		rs.GetFieldValue(_T("NoticeType"),NoticeType_I);
		rs.GetFieldValue(_T("PlanEntry"),PEC_I);
		rs.GetFieldValue(_T("AssignCode"),AssignCode_I);
		rs.GetFieldValue(_T("Frequency"),Freq_I);
		rs.GetFieldValue(_T("Pol"),Pol_I);
		rs.GetFieldValue(_T("IDst"),IDst_I);
		rs.GetFieldValue(_T("SfnID"),SfnID_I);

//		if		(ctry_I.GetLength()==1)		ctry_I = ctry_I + _T("  ");
//		else if (ctry_I.GetLength()==2)		ctry_I = ctry_I + _T(" ");
//		GEOCTYA((BYTE *)ctry_I.GetBufferSetLength(3), (BYTE *)adm_I.GetBufferSetLength(3));
		adm_I = Cty2AdmGE06(&ctry_I);

		str_out1.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s  %s,%s,%s,%s"), _T("L"), _T("AS"), adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
	}
	rs.Close();	DB1.Close();
	*str_out = str_out1;

	return IDst_I;
}




CString CSMS4DCView::QGE06_IntFrom_Q1(CString IDst_I,CString SfnID_I,CString NET_I,int PEC_I,CString allotkey_I, CString AssocAllotID_I, CString AdmRefID_I,
										CString adm_I,CString ctry_I,CString SiteName_I,
										CString NoticeType_I,CString AssignCode_I,double Freq_I,CString Pol_I,
										CString RLONbs,CString RLATbs,CString P_out,
										CString *IDst_out,int *Nas,CString *allotkey_out,int *Nal) 
{
//Pout = double L,double EmedW,double CNFSmax,double PMmin,double LPM,

	CString str_out0,str_out1,str_out2;
	int Nstr_I = 0, Nas_I = 0, Nal_I = 0;
	*IDst_out = _T("");
	*allotkey_out = _T("");

	if((NET_I==_T("ASA0"))||(PEC_I==1))
	{
		*IDst_out = IDst_I;
		str_out0.Format(_T("%s,%s,%s,%s,%s,%s,%s,%d,%s,%0.4lf,%s  %s,%s,%s,%s"), _T("W"), _T("AS"), adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
		Nas_I = 1;

	}//if(PEC_I==1)
	else if(PEC_I==2)
	{
		CString IDstN;
		Nas_I = QGE06_IntFrom_Q2(SfnID_I,IDst_I,&IDstN,&str_out0,RLONbs, RLATbs, P_out); 
		*IDst_out = IDstN;
	
	}//if(PEC_I==2)
	else if(PEC_I==3)
	{
		*allotkey_out = allotkey_I;
		str_out0.Format(_T("%s,%s,%s,%s,%s,%s,%s,%d,%s,%0.4lf,%s  %s,%s,%s,%s"), _T("W"), _T("AL"), adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
		Nal_I = 1;

	}//if(PEC_I==3)
	else if(PEC_I==4)
	{
		if((NET_I==_T("ASS4"))||(NET_I==_T("AST4")))	/////////A4_1
		{
			CString IDstN;
			Nas_I = QGE06_IntFrom_Q2(SfnID_I,IDst_I,&IDstN,&str_out1,RLONbs, RLATbs, P_out,1); 

			*IDst_out = IDstN;
			*allotkey_out = QGE06_IntFrom_Q3(SfnID_I,RLONbs, RLATbs, P_out,&str_out2);
			str_out0 = str_out1 + _T(",") + str_out2;
			Nal_I = 1;

		}/////////A4_1
		else if((NET_I==_T("ALS4"))||(NET_I==_T("ALT4")))	/////////A4_2
		{
			CString IDstN;
			Nas_I = QGE06_IntFrom_Q2(SfnID_I,IDst_I,&IDstN,&str_out1,RLONbs, RLATbs, P_out,1); 
			*IDst_out = IDstN;
			*allotkey_out = allotkey_I;

			str_out2.Format(_T("%s,%s,%s,%s,%s,%s,%s,%d,%s,%0.4lf,%s  %s,%s,%s,%s"), _T("W"), _T("AL"), adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
			str_out0 = str_out1 + _T(",") + str_out2;
			Nal_I = 1;

		}/////////A4_2
	}//if(PEC_I==4)
	else if(PEC_I==5)
	{
		if((NET_I==_T("ASS5"))||(NET_I==_T("AST5")))	/////////A5_1
		{
			*IDst_out = IDst_I;
			str_out1.Format(_T("%s,%s,%s,%s,%s,%s,%s,%d,%s,%0.4lf,%s  %s,%s,%s,%s"), _T("W"), _T("AS"), adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
			*allotkey_out = QGE06_IntFrom_Q4( AssocAllotID_I, SfnID_I, RLONbs, RLATbs, P_out,&str_out2); 
			str_out0 = str_out1 + _T(",") + str_out2;
			Nas_I = 1;			Nal_I = 1;

		}	/////////A5_1
		else if((NET_I==_T("ALS5"))||(NET_I==_T("ALT5")))	/////////A5_2
		{
			*allotkey_out = allotkey_I;
			str_out1.Format(_T("%s,%s,%s,%s,%s,%s,%s,%d,%s,%0.4lf,%s  %s,%s,%s,%s"), _T("W"), _T("AL"), adm_I,ctry_I,SiteName_I,AdmRefID_I,NoticeType_I,PEC_I,AssignCode_I,Freq_I,RLONbs,RLATbs,Pol_I,SfnID_I,P_out);
			*IDst_out = QGE06_IntFrom_Q5(AdmRefID_I, RLONbs, RLATbs, P_out,&str_out2);
 			str_out0 = str_out1 + _T(",") + str_out2;
			Nas_I = 1;			Nal_I = 1;

		}	/////////A5_2
	}//if(PEC_I==5)

	Nstr_I = Nas_I + Nal_I;
	*Nas = Nas_I;
	*Nal = Nal_I;

	return str_out0;
}

int CSMS4DCView::QGE06_IntFromFXM2DBCBT_Qy(double GRlat_W, double GRlon_W, double SR, double Freq_W, double FR) 
{
	int NrowT = 0, Nrow = 0;
	CString CDataBaseSTR = _T("");

	double fmin , fmax;
	fmin = Freq_W - FR;
	fmax = Freq_W + FR;
//	CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB' Or (STTP)='ML') AND ((TXfreq)>=%lf And (TXfreq)<=%lf));"), fmin, fmax);
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB' Or (STTP)='ML') AND ((TXfreq)>=%lf And (TXfreq)<=%lf));"), m_qSTtableGE06ASAL,fmin, fmax);

	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;		CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	double STlat_deg , STlon_deg;
	CString str, IDst, STTP , IDstN = _T(""), StType , allotkeyN = _T("");

	rs.Open(CRecordset::snapshot, CDataBaseSTR);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
			rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
			rs.GetFieldValue(_T("STTP"),STTP);
			rs.GetFieldValue(_T("StType"),StType);

			if(((STTP==_T("FX"))||(STTP==_T("FB")))&&(StType!=_T("Typical")))
			{
				double dist = Distance_km(GRlat_W,GRlon_W,STlat_deg,STlon_deg);
				if((dist <= SR)&&(dist > 0.0000001))
				{
					IDstN = IDstN + _T(",") + IDst;
					Nrow++;
				}
			}
			else if((STTP==_T("ML"))||(((STTP==_T("FX"))||(STTP==_T("FB")))&&(StType==_T("Typical"))))
			{
				CString AreaOfTrans;
				rs.GetFieldValue(_T("AreaOfTrans"),AreaOfTrans);
				if(AreaOfTrans.GetLength()>0)
				{
					double lat,lon;
					Zone2GRpoint(AreaOfTrans,&lat,&lon);
					double dist = Distance_km(GRlat_W,GRlon_W,lat,lon);
					if((dist <= SR)&&(dist > 0.0000001))
					{
						IDstN = IDstN + _T(",") + IDst;
						Nrow++;
					}
				}
				else
				{
					CString radius;
					rs.GetFieldValue(_T("radius"),radius);
					if(radius.GetLength()>0)
					{
						double dist = Distance_km(GRlat_W,GRlon_W,STlat_deg,STlon_deg);
						if((dist <= SR)&&(dist > 0.0000001))
						{
							IDstN = IDstN + _T(",") + IDst;
							Nrow++;
						}
					}
				}
			}
			rs.MoveNext();
		}//while
	}//if
	rs.Close();		DB1.Close();

	IDstN.Delete(0);
	if(Nrow>0)
	{
		CString str1,str2 = _T("");
		for(long j=0 ; j<Nrow ;j++)
		{
			str1.Format(_T("((IDst)=\'%s\')"),GetFld(IDstN,j+1),GetFld(allotkeyN,j+1));
			str2 = str2 + _T(" OR ") + str1;
		}
		str2.Delete(0,4);	str2 = str2 + _T(";");
//		CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE %s"),str2);
		CDataBaseSTR.Format(_T("SELECT * FROM %s  WHERE  %s "),m_qSTtableGE06ASAL,str2);
	}
	else	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE IDst=\'z\';") , m_qSTtableGE06ASAL);
//	else	CDataBaseSTR = _T("SELECT * FROM STtableGE06ASAL WHERE IDst=\'z\';");

	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = FALSE;
	datadlg.m_Title = _T("Interferer Stations");
	if (datadlg.DoModal()==IDOK)
		NrowT = ((CSMS4DCApp *)AfxGetApp())->Nrow;
	
	return NrowT;
}


CString CSMS4DCView::QGE06_IntFromBCBT2FXM_Qx() 
{
	CString Selx = _T("");
	CString CDataBaseSTR = _T("");

	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;		CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;

	CString SQL1 = _T("DELETE * FROM FStrig_hR;");
	DB1.ExecuteSQL(SQL1);

	CString str, IDst;

//	CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB') AND ((StType)<>'Typical') AND (((RXfreq)>=174 And (RXfreq)<=230) Or ((RXfreq)>=470 And (RXfreq)<=862)));"));
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06L') AND ((STTP)='FX' Or (STTP)='FB') AND ((StType)<>'Typical') AND (((RXfreq)>=174 And (RXfreq)<=230) Or ((RXfreq)>=470 And (RXfreq)<=862)));") , m_qSTtableGE06ASAL);
	rs.Open(CRecordset::snapshot, CDataBaseSTR);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;

			CString sttp,Freq;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("STTP"),sttp);
			rs.GetFieldValue(_T("RXfreq"),Freq);
			SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s' "), IDst, 1, Freq, sttp, _T("POINT"));
			SQL1 = _T("INSERT INTO FStrig_hR (IDst, ant, Freq_ter, STTP, GeoType) ") + SQL1;
			DB1.ExecuteSQL(SQL1);

			rs.MoveNext();
		}//while
	}//if
	rs.Close();	

//	CDataBaseSTR.Format(_T("SELECT IDst, STTP, TXfreq, GeoType, zone, RecLat, RecLon, Link.Radius FROM Link, STtableGE06 WHERE (((STtableGE06.IDst)=[Link].[TXID]) AND ((STtableGE06.STTP)='FX' Or (STtableGE06.STTP)='FB') AND (((STtableGE06.TXfreq)>=174 And (STtableGE06.TXfreq)<=230) Or ((STtableGE06.TXfreq)>=470 And (STtableGE06.TXfreq)<=862)) AND ((Link.GeoType)='MULTIPOINT' Or (Link.GeoType)='ZONE' Or (Link.GeoType)='CIRCLE') AND ((STtableGE06.Fragment)='GE06L') AND ((STtableGE06.StType)<>'Typical'));"));
	CDataBaseSTR.Format(_T("SELECT IDst, STTP, TXfreq, GeoType, zone, RecLat, RecLon, Link.Radius FROM Link, %s WHERE (((STtableGE06.IDst)=[Link].[TXID]) AND ((STtableGE06.STTP)='FX' Or (STtableGE06.STTP)='FB') AND (((STtableGE06.TXfreq)>=174 And (STtableGE06.TXfreq)<=230) Or ((STtableGE06.TXfreq)>=470 And (STtableGE06.TXfreq)<=862)) AND ((Link.GeoType)='MULTIPOINT' Or (Link.GeoType)='ZONE' Or (Link.GeoType)='CIRCLE') AND ((STtableGE06.Fragment)='GE06L') AND ((STtableGE06.StType)<>'Typical'));") , m_qSTtableGE06);
	rs.Open(CRecordset::snapshot, CDataBaseSTR);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			CString sttp,Freq,zone,RecLat,RecLon,Radius;

			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("STTP"),sttp);
			rs.GetFieldValue(_T("TXfreq"),Freq);
			rs.GetFieldValue(_T("GeoType"),str);
			rs.GetFieldValue(_T("zone"),zone);
			rs.GetFieldValue(_T("RecLat"),RecLat);
			rs.GetFieldValue(_T("RecLon"),RecLon);
			rs.GetFieldValue(_T("Radius"),Radius);

		//	SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s','%s',%s,%s,%s "), IDst, 0, Freq, sttp, str,zone,RecLat,RecLon,Radius);
			SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s','%s',%s,%s,%s "), IDst, 0, Freq, sttp, str,zone, RecLat.IsEmpty()?"NULL":RecLat ,RecLon.IsEmpty()?"NULL":RecLon,Radius.IsEmpty()?"NULL":Radius);
			
			SQL1 = _T("INSERT INTO FStrig_hR (IDst, ant, Freq_ter, STTP, GeoType,zone,latp,lonp,Rp) ") + SQL1;
			DB1.ExecuteSQL(SQL1);

			rs.MoveNext();
		}//while
	}//if
	rs.Close();	

//	CDataBaseSTR.Format(_T("SELECT * FROM STtableGE06ASAL WHERE (((Fragment)='GE06L') AND ((STTP)='ML') AND (((RXfreq)>=174 And (RXfreq)<=230) Or ((RXfreq)>=470 And (RXfreq)<=862)));"));
	CDataBaseSTR.Format(_T("SELECT * FROM %s WHERE (((Fragment)='GE06L') AND ((STTP)='ML') AND (((RXfreq)>=174 And (RXfreq)<=230) Or ((RXfreq)>=470 And (RXfreq)<=862)));") , m_qSTtableGE06ASAL);
	rs.Open(CRecordset::snapshot, CDataBaseSTR);
	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);

			rs.GetFieldValue(_T("AreaOfTrans"),str);
			if(str.GetLength()>0)
			{
				CString sttp,Freq;
				rs.GetFieldValue(_T("STTP"),sttp);
				rs.GetFieldValue(_T("RXfreq"),Freq);
				SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s','%s' "), IDst, 0, Freq, sttp, _T("ZONE"),str);
				SQL1 = _T("INSERT INTO FStrig_hR (IDst, ant, Freq_ter, STTP, GeoType,zone) ") + SQL1;
				DB1.ExecuteSQL(SQL1);
			}
			else
			{
				rs.GetFieldValue(_T("radius"),str);
				if(str.GetLength()>0)
				{
					CString lat,lon,sttp,Freq;

					rs.GetFieldValue(_T("STlat_deg"),lat);
					rs.GetFieldValue(_T("STlon_deg"),lon);
					rs.GetFieldValue(_T("STTP"),sttp);
					rs.GetFieldValue(_T("RXfreq"),Freq);
					SQL1.Format(_T("SELECT %s,%d,%s,'%s','%s',%s,%s,%s "), IDst, 0, Freq, sttp, _T("CIRCLE"),lat,lon,str);
					SQL1 = _T("INSERT INTO FStrig_hR (IDst, ant, Freq_ter, STTP, GeoType,latp,lonp,Rp) ") + SQL1;
					DB1.ExecuteSQL(SQL1);
				}
			}
			rs.MoveNext();
		}//while
	}//if
	rs.Close();		DB1.Close();

//	CDataBaseSTR.Format(_T("SELECT FStrig_hR.IDst, STtableGE06ASAL.STname, STtableGE06ASAL.STlat_deg, STtableGE06ASAL.STlon_deg, STtableGE06ASAL.Sth_agl, STtableGE06ASAL.TXfreq, STtableGE06ASAL.Power_eirp, STtableGE06ASAL.Azimuth, STtableGE06ASAL.Elevation, STtableGE06ASAL.ANTgain, STtableGE06ASAL.BWh, STtableGE06ASAL.BWv, STtableGE06ASAL.Polarization, STtableGE06ASAL.Antenna, STtableGE06ASAL.InsertionLoss, STtableGE06ASAL.RxSensitivity, STtableGE06ASAL.Srv, STtableGE06ASAL.STTP, STtableGE06ASAL.Emission, STtableGE06ASAL.AntID, STtableGE06ASAL.RXfreq, STtableGE06ASAL.radius, STtableGE06ASAL.NoiseFactor, STtableGE06ASAL.Sth_asll, STtableGE06ASAL.ctry, STtableGE06ASAL.SystemType1, STtableGE06ASAL.SystemType2, STtableGE06ASAL.Fragment, STtableGE06ASAL.StType, STtableGE06ASAL.AntCatID, STtableGE06ASAL.AntDir, STtableGE06ASAL.MaxEffHght, STtableGE06ASAL.AdmRefID, STtableGE06ASAL.AreaOfTrans, STtableGE06ASAL.NoticeType, STtableGE06ASAL.TVSys, STtableGE06ASAL.RefPlanCfg, STtableGE06ASAL.SysVar, STtableGE06ASAL.FreqVCarr, STtableGE06ASAL.ColorSys, STtableGE06ASAL.FreqSCarr, STtableGE06ASAL.OsetV12, STtableGE06ASAL.OsetV, STtableGE06ASAL.TVChannel, STtableGE06ASAL.FreqStabl, STtableGE06ASAL.VSWR, STtableGE06ASAL.SpectMask, STtableGE06ASAL.TerraKey, STtableGE06ASAL.Plan, STtableGE06ASAL.PlanEntry, STtableGE06ASAL.AssignCode, STtableGE06ASAL.SfnID, STtableGE06ASAL.GeoArea, STtableGE06ASAL.RXMode, STtableGE06ASAL.ERPTilt, STtableGE06ASAL.Tilt, STtableGE06ASAL.Offset, STtableGE06ASAL.StID, STtableGE06ASAL.AssocAllotID, STtableGE06ASAL.nb_sub_areas, STtableGE06ASAL.TypRefNetwk, STtableGE06ASAL.ERP_h_dbw, STtableGE06ASAL.ERP_v_dbw, STtableGE06ASAL.allotkey, FStrig_hR.ant, FStrig_hR.GeoType, FStrig_hR.STTP AS sttp1, FStrig_hR.Freq_ter, FStrig_hR.zone, FStrig_hR.latp, FStrig_hR.lonp, FStrig_hR.Rp FROM STtableGE06ASAL, FStrig_hR WHERE (((FStrig_hR.IDst)=Val([STtableGE06ASAL].[IDst]))) order by FStrig_hR.IDst;"));
	CDataBaseSTR.Format(_T("SELECT FStrig_hR.IDst, STtableGE06ASAL.STname, STtableGE06ASAL.STlat_deg, STtableGE06ASAL.STlon_deg, STtableGE06ASAL.Sth_agl, STtableGE06ASAL.TXfreq, STtableGE06ASAL.Power_eirp, STtableGE06ASAL.Azimuth, STtableGE06ASAL.Elevation, STtableGE06ASAL.ANTgain, STtableGE06ASAL.BWh, STtableGE06ASAL.BWv, STtableGE06ASAL.Polarization, STtableGE06ASAL.Antenna, STtableGE06ASAL.InsertionLoss, STtableGE06ASAL.RxSensitivity, STtableGE06ASAL.Srv, STtableGE06ASAL.STTP, STtableGE06ASAL.Emission, STtableGE06ASAL.AntID, STtableGE06ASAL.RXfreq, STtableGE06ASAL.radius, STtableGE06ASAL.NoiseFactor, STtableGE06ASAL.Sth_asll, STtableGE06ASAL.ctry, STtableGE06ASAL.SystemType1, STtableGE06ASAL.SystemType2, STtableGE06ASAL.Fragment, STtableGE06ASAL.StType, STtableGE06ASAL.AntCatID, STtableGE06ASAL.AntDir, STtableGE06ASAL.MaxEffHght, STtableGE06ASAL.AdmRefID, STtableGE06ASAL.AreaOfTrans, STtableGE06ASAL.NoticeType, STtableGE06ASAL.TVSys, STtableGE06ASAL.RefPlanCfg, STtableGE06ASAL.SysVar, STtableGE06ASAL.FreqVCarr, STtableGE06ASAL.ColorSys, STtableGE06ASAL.FreqSCarr, STtableGE06ASAL.OsetV12, STtableGE06ASAL.OsetV, STtableGE06ASAL.TVChannel, STtableGE06ASAL.FreqStabl, STtableGE06ASAL.VSWR, STtableGE06ASAL.SpectMask, STtableGE06ASAL.TerraKey, STtableGE06ASAL.Plan, STtableGE06ASAL.PlanEntry, STtableGE06ASAL.AssignCode, STtableGE06ASAL.SfnID, STtableGE06ASAL.GeoArea, STtableGE06ASAL.RXMode, STtableGE06ASAL.ERPTilt, STtableGE06ASAL.Tilt, STtableGE06ASAL.Offset, STtableGE06ASAL.StID, STtableGE06ASAL.AssocAllotID, STtableGE06ASAL.nb_sub_areas, STtableGE06ASAL.TypRefNetwk, STtableGE06ASAL.ERP_h_dbw, STtableGE06ASAL.ERP_v_dbw, STtableGE06ASAL.allotkey, FStrig_hR.ant, FStrig_hR.GeoType, FStrig_hR.STTP AS sttp1, FStrig_hR.Freq_ter, FStrig_hR.zone, FStrig_hR.latp, FStrig_hR.lonp, FStrig_hR.Rp FROM %s, FStrig_hR WHERE (((FStrig_hR.IDst)=Val([STtableGE06ASAL].[IDst]))) order by FStrig_hR.IDst;") , m_qSTtableGE06ASAL);
	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = FALSE;
	datadlg.m_Title = _T("Select One Victim FXM Station");
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
			Selx = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
		else
		{
			MessageBox(_Z("Please Select One Record."),_Z("ERROR!!!"),MB_ICONERROR);
			Set_STtable_Default();
			EndWaitCursor();
		}
	}
	return Selx;
}

long CSMS4DCView::QGE06_IntFrom_C(CString SfnID,CString *IDst,CString *AllotC) 
{
	CString  tbl , m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
//	tbl.Format(_T("SELECT * FROM CommonFields WHERE ((SfnID=\'%s\'));"), SfnID);
	tbl.Format(_T("SELECT * FROM %s WHERE ((SfnID=\'%s\'));"), m_qCommonFields,SfnID);
	rs.Open(CRecordset::snapshot, tbl);
	long c = 0;

	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		CString str = _T("");
		while(1)
		{
			if(rs.IsEOF()) break;

			rs.GetFieldValue(_T("allotkey"),str);
			if(str!=_T("---"))		*AllotC = str;

			rs.GetFieldValue(_T("IDst"),str);
			if(str!=_T("---"))
			{
				*IDst = *IDst + _T(",") + str;
				c++;
			}
			rs.MoveNext();
		}
	}
	rs.Close();	DB1.Close();
	(*IDst).Delete(0);

	return c;
}

BOOL CSMS4DCView::QGE06_FXMBCBT_Q6Fter(long IDst, double FrqR, double FrqT, CString sttp) 
{
	double GRlat0 , GRlon0,   Freqter1 = 0 ,Freqter2 = 0;

	if(( (sttp==_T("FX"))||(sttp==_T("FB"))||(sttp==_T("ML")) )&&(((FrqR>=174)&&(FrqR<=230))||((FrqR>=470)&&(FrqR<=862))))	//point
		Freqter1  = FrqR;
	if((sttp==_T("FX"))&&(((FrqT>=174)&&(FrqT<=230))||((FrqT>=470)&&(FrqT<=862))))	//MPOINT
	{
		int m = QGE06_FXMBCBT_Q3((IDst) ,&GRlat0 , &GRlon0) ;
		if(m>0)					Freqter2  = FrqT;
	}
	if((sttp==_T("FB"))&&(((FrqT>=174)&&(FrqT<=230))||((FrqT>=470)&&(FrqT<=862))))
	{
		long n1 = QGE06_FXMBCBT_Q4((IDst) ,&GRlat0 , &GRlon0) ;	//ZONE
		long n2 = QGE06_FXMBCBT_Q5((IDst) ,&GRlat0 , &GRlon0) ;	//CIRCLE
		if((n1>0)||(n2>0))		Freqter2  = FrqT;
	}

	BOOL n = FALSE;
	if     ((Freqter1 > 230)&&(Freqter2 == 0))	n = TRUE;
	else if((Freqter1 == 0 )&&(Freqter2 > 230))	n = TRUE;
	else if((Freqter1 > 230)&&(Freqter2 > 230))	n = TRUE;
/*
	else if((Freqter1 < 230)&&(Freqter2 == 0))	n = FALSE;
	else if((Freqter1 == 0 )&&(Freqter2 < 230))	n = FALSE;
	else if((Freqter1 < 230)&&(Freqter2 < 230))	n = FALSE;
	else if((Freqter1 == 0)&&(Freqter2 == 0))	n = FALSE;
	else if((Freqter1 < 230)&&(Freqter2 > 230))	n = FALSE;
	else if((Freqter1 > 230)&&(Freqter2 < 230))	n = FALSE;
*/
	return n;
}

CString CSMS4DCView::Cty2AdmGE06(CString *cty1) 
{
	CString adm0 = _T("");
	CString cty0 = *cty1;
	if	   (cty0.GetLength()==1)	cty0 = cty0 + _T("  ");
	else if(cty0.GetLength()==2)	cty0 = cty0 + _T(" ");

	if	   (cty0==_T("AOE"))	adm0 = _T("MRC");
	else if(cty0==_T("XGZ"))	adm0 = _T("PSE");
	else if(cty0==_T("XWB"))	adm0 = _T("PSE");
	else						GEOCTYA((BYTE *)cty0.GetBufferSetLength(3), (BYTE *)adm0.GetBufferSetLength(3));

	*cty1 = cty0;
	return adm0;
}



void CSMS4DCView::Function_Queries() 
{
	CString str1,str2,str3,str4,str5,str6,str7,str8,str9,str10,str11,str12,str13, str14,str15,str16;

	//Query CommonFields
	str1 = _T(" ( SELECT  Frequency.freqid AS IDst,  BCstation.TerraKey, AdmRefID, SiteName, GeoLat, GeoLon, Country,  Fragment, Plan, PlanEntry, AssignCode, SfnID , NoticeType, BCStation.GeoArea,RefPlanCfg, SysVar, RXMode, ERPTilt, Tilt, AntHeightAGL, Pol,  Frequency.Frequency/1000000 as Frequency, TVChan, SpectMask, Offset , ClassStation, BCstation.StID,AssocAllotID,'' as nb_sub_areas,'' as TypRefNetwk,EqCat.ERP_h_dbw,EqCat.ERP_v_dbw,Antenna.AntCatID,Antenna.AntID,AntCat.AntDir,AntCat.MaxEffHght,'---' as allotkey,TVSys ");
	str2 = _T(" FROM BCstation, AntCat,Antenna,EqCat, Equipment,Frequency,Provisions ");
	str3 = _T(" WHERE BCstation.StID=Equipment.BCID AND Antenna.EqID=Equipment.EqID and  AntCat.AntCatID = Antenna.AntCatID and  EqCat.EqCatID = Equipment.EqCatID and Equipment.EqID = Frequency.EqID and provisions.provision=BCStation.provision ");
	str4 = _T(" UNION ALL SELECT '---',terrakey, AdmRefID, allot_name, NULL , NULL , Ctry,Fragment,'---', PlanEntry,'---', SfnID, NoticeType, geo_area,RefPlanCfg,'---','---', '---','---' ,'---', Polar,  rrc_allotment.Frequency/1000000, TVChannel, SpectMask, Offset,  ClassStation,'---', '',nb_sub_areas,TypRefNetwk ,'' ,'','','','','', rrc_allotment.allotkey ,'' ");
	str5 = _T(" FROM rrc_allotment ) as CommonFields ");
	m_qCommonFields = str1+str2+str3+str4+str5;

	//Query EarthStationAp7_Int
	str1 = _T(" [ SELECT e_stn.ctry, e_stn.ntc_id, e_ant.beam_name, grp.grp_id, e_ant.emi_rcp, e_stn.long_dec, e_stn.lat_dec, e_stn.stn_name, e_stn.elev_min, e_stn.azm_fr, e_stn.azm_to, e_ant.gain, grp.pwr_max, ant_type.pattern, ant_type.coefa, ant_type.coefb, ant_type.coefc, ant_type.coefd, ant_type.phi1, assgn.freq_mhz, grp.polar_type, grp.polar_ang, grp.noise_t, grp.bdwdth ");
	str2 = _T(" FROM (((e_stn INNER JOIN e_ant ON e_stn.ntc_id = e_ant.ntc_id) INNER JOIN grp ON (e_ant.ntc_id = grp.ntc_id) AND (e_ant.emi_rcp = grp.emi_rcp) AND (e_ant.beam_name = grp.beam_name)) LEFT JOIN ant_type ON e_ant.pattern_id = ant_type.pattern_id) INNER JOIN assgn ON grp.grp_id = assgn.grp_id ");
	str3 = _T(" WHERE (((e_stn.long_dec) Is Not Null) AND ((e_stn.long_nom) Is Not Null)) ]. as EarthStationAp7_Int ");
	m_qEarthStationAp7_Int = str1+str2+str3;

	//Query GE84BC2BC
	str1 = _T(" [ SELECT AntCat.AntCatID AS terrakey, BCstation.StID AS Assgn_ID, BCstation.Country AS ctry, BCstation.SiteName AS site_name, BCstation.GeoLat AS lat_dec, BCstation.GeoLon AS long_dec, Antenna.AntHeightAGL AS hgt_agl, AntCat.Pol AS polar, EqCat.ERP_dbw, EqCat.ERP_h_dbw, EqCat.ERP_v_dbw, AntCat.AntDir AS ant_dir, BCstation.HeightASL AS site_alt, Frequency/1000000 AS freq_assgn, Frequency.EmissionCl AS emi_cls, EqCat.TranSys AS tran_sys, BCstation.ClassStation AS stn_cls, IIf(classstation=\'BC\',frequency/1000000,freqvcarr) AS freq_y, EqCat.EU_Ref, AntCat.MaxEffHght AS eff_hgtmax, Provisions.Fragment, EqCat.FreqStabl AS freq_stabl, EqCat.OsetV12 AS oset_v_12, EqCat.OsetV AS oset_v_khz, Frequency.FreqSCarr AS freq_scarr, EqCat.OsetS12 AS oset_s_12, EqCat.PwrRatio AS pwr_ratio, Frequency.TVChan AS tv_chan, EqCat.ColorSys AS color, Antenna.AntID ");
	str2 = _T(" FROM BCstation, AntCat, Antenna, Equipment, EqCat, Frequency, Provisions ");
	str3 = _T(" WHERE (((BCstation.StID)=equipment.bcid) AND ((Provisions.Fragment)='GE84' Or (Provisions.Fragment)='ST61') AND ((Equipment.EqCatID)=eqcat.eqcatid) AND ((Equipment.EqID)=frequency.eqid And (Equipment.EqID)=antenna.eqid) AND ((Antenna.AntCatID)=antcat.antcatid) AND ((BCstation.Provision)=provisions.provision)) ]. as GE84BC2BC ");
	m_qGE84BC2BC = str1+str2+str3;

	//Query GE89BT2BT
	str1 = _T(" [ SELECT AntCat.AntCatID AS terrakey, BCstation.StID AS Assgn_ID, BCstation.Country AS ctry, BCstation.SiteName AS site_name, BCstation.GeoLat AS lat_dec, BCstation.GeoLon AS long_dec, Antenna.AntHeightAGL AS hgt_agl, AntCat.Pol AS polar, EqCat.ERP_dbw, EqCat.ERP_h_dbw, EqCat.ERP_v_dbw, AntCat.AntDir AS ant_dir, BCstation.HeightASL AS site_alt, Frequency/1000000 AS freq_assgn, Frequency.EmissionCl AS emi_cls, EqCat.TVSys AS tran_sys, BCstation.ClassStation AS stn_cls, IIf(classstation=\'BC\',frequency/1000000,freqvcarr) AS freq_y, EqCat.EU_Ref, AntCat.MaxEffHght AS eff_hgtmax, Provisions.Fragment, EqCat.FreqStabl AS freq_stabl, EqCat.OsetV12 AS oset_v_12, EqCat.OsetV AS oset_v_khz, Frequency.FreqSCarr AS freq_scarr, EqCat.OsetS12 AS oset_s_12, EqCat.PwrRatio AS pwr_ratio, Frequency.TVChan AS tv_chan, EqCat.ColorSys AS color, Antenna.Azimuth AS azm_max_e, Antenna.AntID ");
	str2 = _T(" FROM BCstation, AntCat, Antenna, Equipment, EqCat, Frequency, Provisions ");
	str3 = _T(" WHERE (((BCstation.StID)=equipment.bcid) AND ((Provisions.Fragment)='GE89') AND ((Equipment.EqCatID)=eqcat.eqcatid) AND ((Equipment.EqID)=frequency.eqid And (Equipment.EqID)=antenna.eqid) AND ((Antenna.AntCatID)=antcat.antcatid) AND ((BCstation.Provision)=provisions.provision)) ]. as GE89BT2BT ");
	m_qGE89BT2BT = str1+str2+str3;

	//Query Link_TX
	str1 = _T(" ( SELECT Station.StID, Station.GeoLat, Station.GeoLon, Station.SiteName, Antenna.AntHeightAGL, Antenna.AntID, AntCat.Gain, AntCat.XPD, Equipment.RadPwr, AntCat.InsLoss, Frequency.Frequency, AntCat.Pol, Frequency.EmissionCl, Link.HopID, Link.LinkID, Link.ReceiverID, Frequency.BandWidth, EqCat.Sensitivity, Frequency.FreqID ");
	str2 = _T(" FROM Equipment, EqCat, Antenna, AntCat, Frequency, Link, Station ");
	str3 = _T(" WHERE (((Station.StID)=Equipment.StID) AND ((Antenna.AntID)=TXAntID) AND ((Frequency.FreqID)=Link.TXID) AND ((Equipment.EqID)=Antenna.EqID And (Equipment.EqID)=Frequency.EqID) AND ((Antenna.AntCatID)=AntCat.AntCatID) AND ((Equipment.EqCatID)=EqCat.EqCatID)) ) as Link_TX ");
	m_qLink_TX = str1+str2+str3;

	//Query Link_RX
	str1 = _T(" ( SELECT Station.StID, Station.GeoLat, Station.GeoLon, Station.SiteName, Antenna.AntHeightAGL, Antenna.AntID, AntCat.Gain, AntCat.XPD, Equipment.RadPwr, AntCat.InsLoss, Frequency.Frequency, AntCat.Pol, Frequency.EmissionCl, Link.HopID, Link.LinkID, Link.ReceiverID, Frequency.BandWidth, EqCat.Sensitivity, Frequency.FreqID ");
	str2 = _T(" FROM Equipment, EqCat, Antenna, AntCat, Frequency, Link, Station ");
	str3 = _T(" WHERE (((Station.StID)=Equipment.StID) AND ((Antenna.AntID)=RXAntID) AND ((Frequency.FreqID)=Link.RXID) AND ((Equipment.EqID)=Antenna.EqID And (Equipment.EqID)=Frequency.EqID) AND ((Antenna.AntCatID)=AntCat.AntCatID) AND ((Equipment.EqCatID)=EqCat.EqCatID)) ) as Link_RX ");
	m_qLink_RX = str1+str2+str3;

	//Query Links
	CString qLinks;	qLinks.Format(_T(" ( SELECT * FROM %s , %s  WHERE (((Link_RX.ReceiverID)=Link_TX.ReceiverID))   ) as Links ") , m_qLink_RX,m_qLink_TX);

	//Query Q_Links
	str1 = _T("SELECT Links.Link_TX.ReceiverID AS HopID, Links.Link_TX.FreqID AS TxID, Links.Link_TX.SiteName AS TxName, Links.Link_TX.GeoLat AS TxLat, Links.Link_TX.GeoLon AS TxLon, (Link_TX.Frequency)/1000000 AS TxFrq, Links.Link_TX.EmissionCl AS TxEmission, Links.Link_TX.AntHeightAGL AS TxHagl, Links.Link_TX.Gain AS TxGain, Links.Link_TX.BandWidth AS TxBandWidth, Links.Link_TX.Sensitivity AS TxSensitivity, Links.Link_TX.AntID AS TxAntID, Links.Link_TX.XPD AS TxXPD, Links.Link_TX.Pol AS TxPol, Links.Link_RX.FreqID AS RxID, Links.Link_RX.SiteName AS RxName, Links.Link_RX.GeoLat AS RxLat, Links.Link_RX.GeoLon AS RxLon, (Link_RX.Frequency)/1000000 AS RxFrq, Links.Link_RX.EmissionCl AS RxEmission, Links.Link_RX.AntHeightAGL AS RxHagl, Links.Link_RX.Gain AS RxGain, Links.Link_RX.BandWidth AS RxBandWidth, Links.Link_RX.Sensitivity AS RxSensitivity, Links.Link_RX.AntID AS RxAntID, Links.Link_RX.XPD AS RxXPD, Links.Link_RX.Pol AS RxPol, Links.Link_TX.RadPwr AS RadPwr, Links.Link_RX.InsLoss AS InsLoss");
	m_qQ_Links.Format( _T(" ( %s  from  %s ) as  Q_Links ")   , str1  , qLinks );

	//Query STtableGE06
	str1 = _T(" ( SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 1 as Srv,ClassStation AS STTP, EmDes AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asl,station.country as ctry,SystemType1,SystemType2,  Fragment,StType, AntCat.AntCatID, AntCat.AntDir ,  AntCat.MaxEffHght , AdmRefID , AreaOfTrans ");
	str2 = _T(" FROM station, equipment, eqcat, antenna, antcat, frequency,Provisions ");
	str3 = _T(" WHERE station.stid=equipment.stid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid and ClassOfAnt<>'R'  and classstation='FX'  and provisions.provision=station.provision ");
	str4 = _T(" union all SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 2 as Srv,ClassStation AS STTP, EmDes AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asll,station.country as ctry,SystemType1,SystemType2,  Fragment,StType, AntCat.AntCatID, AntCat.AntDir, AntCat.MaxEffHght , AdmRefID , AreaOfTrans ");
	str5 = _T(" FROM station, equipment, eqcat, antenna, antcat, frequency,Provisions ");
	str6 = _T(" WHERE station.stid=equipment.stid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid and ClassOfAnt<>'R' and classstation='FB' and provisions.provision=station.provision ");
	str7 = _T(" union all SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 3 as Srv,ClassStation AS STTP,  EmDes  AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asll,BCstation.country as ctry,SystemType1,SystemType2,  Fragment,StType, AntCat.AntCatID, AntCat.AntDir, AntCat.MaxEffHght , AdmRefID , '' ");
	str8 = _T(" FROM bcstation, equipment, eqcat, antenna, antcat, frequency,Provisions ");
	str9 = _T(" WHERE bcstation.stid=equipment.bcid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid  and provisions.provision=BCStation.provision ");
	str10 = _T(" UNION ALL SELECT Frequency.freqid AS IDst, MobName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq,iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 2  as Srv,ClassStation AS STTP,  EmDes  AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,3 as Sth_asll,Mobiles.country as ctry,SystemType1,SystemType2,  Fragment,StType, AntCat.AntCatID , AntCat.AntDir, AntCat.MaxEffHght , AdmRefID , AreaOfTrans ");
	str11 = _T(" FROM mobiles, equipment, eqcat, antenna, antcat, frequency,Provisions ");
	str12 = _T(" WHERE mobiles.mobid=equipment.mobid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid  and provisions.provision=mobiles.provision ");
	str13 = _T(" ) as STtableGE06 ");
	m_qSTtableGE06 = str1+str2+str3+str4+str5+str6+str7+str8+str9+str10+str11+str12+str13;

	//Query STtableGE06ASAL
	str1 = _T(" ( SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 3 as Srv,ClassStation AS STTP,  EmDes  AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asll,BCstation.country as ctry,SystemType1,SystemType2,  Fragment,StType, AntCat.AntCatID, AntCat.AntDir, AntCat.MaxEffHght , AdmRefID , '' as AreaOfTrans, NoticeType, TVSys, RefPlanCfg, SysVar, FreqVCarr, ColorSys, FreqSCarr, OsetV12, OsetV, TVChan as TVChannel, FreqStabl, PwrRatio as VSWR, SpectMask,  BCstation.TerraKey, Plan, PlanEntry, AssignCode, SfnID ,BCStation.GeoArea,  ");
	str2 = _T(" RXMode, ERPTilt, Tilt, Offset , BCstation.StID,AssocAllotID,'' as nb_sub_areas,'' as TypRefNetwk,EqCat.ERP_h_dbw,EqCat.ERP_v_dbw,'---' as allotkey ");
	str3 = _T(" FROM bcstation, equipment, eqcat, antenna, antcat, frequency,Provisions ");
	str4 = _T(" WHERE bcstation.stid=equipment.bcid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid  and provisions.provision=BCStation.provision ");
	str5 = _T(" UNION ALL SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 1 as Srv,ClassStation AS STTP, EmDes AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asl,station.country as ctry,SystemType1,SystemType2,  Fragment,StType, AntCat.AntCatID, AntCat.AntDir ,  AntCat.MaxEffHght , AdmRefID , AreaOfTrans,  NoticeType, '---' as TVSys, '---' as RefPlanCfg, '---' as SysVar, '---' as FreqVCarr, '---' as ColorSys, '---' as FreqSCarr, '---' as OsetV12, '---' as OsetV, '---' as TVChannel, '---' as FreqStabl, '---' as VSWR, '---' as SpectMask,'', '', '', '' , '' ,AreaOfTrans,'', '', '', Offset ,Station.StID,'','' as nb_sub_areas,'' as TypRefNetwk,'','','---' as allotkey ");
	str6 = _T(" FROM station, equipment, eqcat, antenna, antcat, frequency,Provisions ");
	str7 = _T(" WHERE station.stid=equipment.stid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid and ClassOfAnt<>'R'  and classstation='FX'  and provisions.provision=station.provision ");
	str8 = _T(" union all SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 2 as Srv,ClassStation AS STTP, EmDes AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asll,station.country as ctry,SystemType1,SystemType2,  Fragment,StType, AntCat.AntCatID, AntCat.AntDir, AntCat.MaxEffHght , AdmRefID , AreaOfTrans,  NoticeType, '---' as TVSys, '---' as RefPlanCfg, '---' as SysVar, '---' as FreqVCarr, '---' as ColorSys, '---' as FreqSCarr, '---' as OsetV12, '---' as OsetV, '---' as TVChannel, '---' as FreqStabl, '---' as VSWR, '---' as SpectMask,'', '', '', '', '' ,AreaOfTrans,'', '', '', Offset ,Station.StID,'','' as nb_sub_areas,'' as TypRefNetwk,'','','---' as allotkey ");
	str9 = _T(" FROM station, equipment, eqcat, antenna, antcat, frequency,Provisions ");
	str10 = _T(" WHERE station.stid=equipment.stid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid and ClassOfAnt<>'R' and classstation='FB' and provisions.provision=station.provision ");
	str11 = _T(" UNION ALL SELECT Frequency.freqid AS IDst, MobName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq,iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 2  as Srv,ClassStation AS STTP,  EmDes  AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,3 as Sth_asll,Mobiles.country as ctry,SystemType1,SystemType2,  Fragment,StType, AntCat.AntCatID , AntCat.AntDir, AntCat.MaxEffHght , AdmRefID , AreaOfTrans,  NoticeType, '---' as TVSys, '---' as RefPlanCfg, '---' as SysVar, '---' as FreqVCarr, '---' as ColorSys, '---' as FreqSCarr, '---' as OsetV12, '---' as OsetV, '---' as TVChannel, '---' as FreqStabl, '---' as VSWR, '---' as SpectMask,'', '', '', '', ''  ,AreaOfTrans,'', '', '', Offset , Mobiles.MobID,'','' as nb_sub_areas,'' as TypRefNetwk,'','','---' as allotkey ");
	str12 = _T(" FROM mobiles, equipment, eqcat, antenna, antcat, frequency,Provisions ");
	str13 = _T(" WHERE mobiles.mobid=equipment.mobid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid  and provisions.provision=mobiles.provision ");
	str14 = _T(" UNION ALL select '---' AS IDst, allot_name AS STname, NULL AS STlat_deg,NULL AS STlon_deg, '---' AS Sth_agl, frequency/1000000 AS TXfreq,'---' AS Power_eirp, '---' as Azimuth, '---' as Elevation, '---' AS ANTgain, '---' AS BWh, '---' AS BWv, Polar AS Polarization, '---' AS Antenna, '--' AS InsertionLoss, '---' AS RxSensitivity, '-'  as Srv,ClassStation AS STTP,  '---' AS Emission, '---' as AntID , NULL as  RXfreq,'---' as radius,'--' as NoiseFactor,'-' as Sth_asll, ctry, '---' as SystemType1,'---' as SystemType2,  Fragment, '---' as StType, '---' as AntCatID , '---' as AntDir, '---' as MaxEffHght , AdmRefID , '---' as AreaOfTrans, NoticeType, '---' as TVSys, RefPlanCfg, '---' as SysVar, '---' as FreqVCarr, '---' as ColorSys, '---' as FreqSCarr, '---' as OsetV12, '---' as OsetV, TVChannel, '---' as FreqStabl, '---' as VSWR, SpectMask,terrakey,'',PlanEntry,'',SfnID,geo_area,'','','', Offset,'---', '',nb_sub_areas,TypRefNetwk ,'' ,'', rrc_allotment.allotkey ");
	str15 = _T(" FROM rrc_allotment ");
	str16 = _T(" ) as STtableGE06ASAL ");
	m_qSTtableGE06ASAL = str1+str2+str3+str4+str5+str6+str7+str8+str9+str10+str11+str12+str13+str14+str15+str16;

	//Query STtable
	m_qSTtable = ((CSMS4DCApp *)AfxGetApp())->Query_STtable();

}

void CSMS4DCView::Set_STtable_Default() 
{
	CString CDataBaseSTR;	
	CDataBaseSTR.Format( _T("select * from %s order by IDst;") ,  m_qSTtable );
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;
}


double CSMS4DCView::BorderAnt(double latX, double lonX, double HaglX,double AZ0X, double EL0X, int f0[], double rH[], double rV[],
							  double latY, double lonY, double HaglY,double kfactor) 
{
	double Ghv = 1;
	double el , fpi, tpi ,fi , ti;
	//double pi = 4.0*atan(1.0);
	double re = kfactor*6371000;

	/////////////////////Antenna/////////////////////
	el = AZ_EL(latX,lonX ,latY,lonY, HaglX, HaglY, re, &fpi) ;
	tpi = (pi/2.0) - el;
	fi = (180.0/pi)*atan2(sin(tpi)*sin(fpi-AZ0X),(cos(EL0X)*sin(tpi)*cos(fpi-AZ0X)+cos(tpi)*sin(EL0X)));
	ti = (180.0/pi)*acos(cos(tpi)*cos(EL0X)-sin(EL0X)*sin(tpi)*cos(fpi-AZ0X));
	if (fi<0.0)		fi = fi + 359.4;
	Ghv = Interp2(f0,rH,fi,360) * Interp2(f0,rV,ti,360);
	return Ghv;
}



//////////////////////////////////////////////////////////////////
////////////////////////////THALES-ESMERALDA//////////////////////////////////////
//////////////////////////////////////////////////////////////////
void CSMS4DCView::Get_ReqFile(CString Req_filepath) 
{
	FILE *fp = fopen(Req_filepath,"rt");
	if(fp)
	{
		CString sdum1;		CString sdum2[23];		CString sdum3[6];		char dum1[500];
		int t, n;

		fgets( dum1, 500, fp );
		sdum1 = dum1;
		n = 0;
		while(1)
		{
			t = sdum1.Find('\t');
			if(t==-1)	break;
			sdum2[n] = sdum1.Left(t);

m_Grid1_thalesReq.SetAtGrow(n,sdum2[n]);

			sdum1.Delete(0,t+1);
			n++;
		}
		sdum1.TrimRight();
		sdum2[n] = sdum1;

m_Grid1_thalesReq.SetAtGrow(n,sdum2[n]);

//		m_Mfunction  = m_Grid1_thalesReq.GetAt(0);
//m_Mstation  = m_Grid1_thalesReq.GetAt(3);

		fgets( dum1, 500, fp );
		sdum1 = dum1;
		n = 0;
		while(1)
		{
			t = sdum1.Find('\t');
			if(t==-1)	break;
			sdum3[n] = sdum1.Left(t);

m_Grid2_thalesReq.SetAtGrow(n,sdum3[n]);

			sdum1.Delete(0,t+1);
			n++;
		}
		sdum1.TrimRight();
		sdum3[n] = sdum1;
m_Grid2_thalesReq.SetAtGrow(n,sdum3[n]);


		fgets( dum1, 500, fp );
		m_Num_thalesReq = atoi(dum1);

		CString str;
		for(int j=0;j<m_Num_thalesReq;j++)
		{
			fgets( dum1, 500, fp );
			sdum1 = dum1;
			n = 0;
			while(1)
			{
				t = sdum1.Find('\t');
				if(t==-1)	break;

				str = sdum1.Left(t);

m_Grid3_thalesReq.SetAtGrow(n+j*6,str);

				sdum1.Delete(0,t+1);
				n++;
			}
			sdum1.TrimRight();

m_Grid3_thalesReq.SetAtGrow(n+j*6,sdum1);

		}

		fclose(fp);
	}//fp
}

CString CSMS4DCView::OnBUTTONFile_thalesReq(CString mReq_filepath) 
{
	CString Req_fileName = mReq_filepath;
	int L = Req_fileName.ReverseFind('\\');
	Req_fileName.Delete(0,L+1);

	CString Chk_fileName = Req_fileName;
	int t = Chk_fileName.Replace(_T(".req"),_T(".chk"));
	if(t==0)
		Chk_fileName.Replace(_T(".REQ"),_T(".chk"));

	Get_ReqFile(mReq_filepath);

	FindThalesIniFile(&m_PathINBOXth, &m_PathOUTBOXth, &m_PathREQUESTth);

	CString mChk_filepath = m_PathINBOXth + "\\" + m_Grid1_thalesReq.GetAt(3) + "\\";
	CreateDirectory(mChk_filepath, NULL);
	mChk_filepath = mChk_filepath + Chk_fileName;
	return mChk_filepath;
}

/*
#include "P1546DLG.h"
void CSMS4DCView::OnBUTTONCreateCHK_thalesReq(CString mReq_filepath) 
{
	CString Req_fileName = mReq_filepath;
	int L = Req_fileName.ReverseFind('\\');
	Req_fileName.Delete(0,L+1);

	CString Chk_fileName = Req_fileName;
	int t = Chk_fileName.Replace(_T(".req"),_T(".chk"));
	if(t==0)
		Chk_fileName.Replace(_T(".REQ"),_T(".chk"));

	Get_ReqFile(mReq_filepath);

	FindThalesIniFile(&m_PathINBOXth, &m_PathOUTBOXth, &m_PathREQUESTth);

	CString mChk_filepath = m_PathINBOXth + "\\" + m_Grid1_thalesReq.GetAt(3) + "\\";
	CreateDirectory(mChk_filepath, NULL);
	mChk_filepath = mChk_filepath + Chk_fileName;


	CString	mMfunction  = m_Grid1_thalesReq.GetAt(0);
	CString mQuerySTR = ((CSMS4DCApp *)AfxGetApp())->Query_STtable();			
	CString mCDBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;			


	BOOL flag = FALSE;

	if(	(mMfunction==_T("FBM"))||
		(mMfunction==_T("FBF"))
	  )
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];

			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);

			fgets( dum1, 1000, fp );
			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);

			int NsubBand = atoi(sdum1);
			for(int i=0;i<NsubBand;i++)
			{
				fgets( dum1, 1000, fp );	sdum1 = dum1;
				fprintf(fp1,_T("%s"),sdum1);
			}
			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp
	}
	else if	(mMfunction==_T("UBS"))
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];

			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);

			fgets( dum1, 1000, fp );
			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);

			int NsubBand = atoi(sdum1);
			for(int i=0;i<NsubBand;i++)
			{
				fgets( dum1, 1000, fp );	sdum1 = dum1;
				fprintf(fp1,_T("%s"),sdum1);
			}

			///////////////////////////////////Stations///////////////////////////////////////////////
			CString X1  = m_Grid1_thalesReq.GetAt(4);				
			CString Y1  = m_Grid1_thalesReq.GetAt(5);				
			double X = atof(X1.Left(3)) + (atof(X1.Mid(4,2)))/60.0 + (atof(X1.Mid(6,6)))/3600.0;
			double Y = atof(Y1.Left(2)) + (atof(Y1.Mid(3,2)))/60.0 + (atof(Y1.Mid(5,6)))/3600.0;
			double MOlon_deg = ((X1.Mid(3,1))==_T("E")) ? X : -X;		//deg
			double MOlat_deg = ((Y1.Mid(2,1))==_T("N")) ? Y : -Y;		//deg

			double rng_km  = atof(m_Grid2_thalesReq.GetAt(0))/2.0;		//km
			double az1 = atof(m_Grid2_thalesReq.GetAt(1));				//deg
			double az2 = atof(m_Grid2_thalesReq.GetAt(2));				//deg

			CString str = _T("");
			for(int ii=0;ii<m_Num_thalesReq;ii++)
			{
				double fmin = atof(m_Grid3_thalesReq.GetAt(0+6*ii))/1000000.0;	//MHz
				double fmax = atof(m_Grid3_thalesReq.GetAt(1+6*ii))/1000000.0;	//MHz
				sdum1.Format(_T("((TXfreq>=%lf) AND (TXfreq<=%lf))"), fmin,fmax);
				str = str + _T(" OR ") + sdum1;
			}
			str.Delete(0,4);

			double dumy,  lonmin , lonmax , latmin , latmax ;
			reckon(MOlat_deg,MOlon_deg, rng_km,  0.0,&latmax,&dumy) ;
			reckon(MOlat_deg,MOlon_deg, rng_km,180.0,&latmin,&dumy) ;
			reckon(MOlat_deg,MOlon_deg, rng_km, 90.0,&dumy,&lonmax) ;
			reckon(MOlat_deg,MOlon_deg, rng_km,270.0,&dumy,&lonmin) ;

			CString	Tbl;
			Tbl.Format(_T("SELECT * FROM %s WHERE ( ( %s ) AND ((STlat_deg>=%lf) AND (STlat_deg<=%lf) AND (STlon_deg>=%lf) AND (STlon_deg<=%lf)) );") , mQuerySTR,str,latmin,latmax,lonmin,lonmax);

			CDatabase myDB;		CRecordset rs;
			myDB.Open(_T(mCDBSTR),FALSE,FALSE, "ODBC;", FALSE);
			rs.m_pDatabase = &myDB;
			rs.Open( CRecordset::snapshot, Tbl);
			
			if(rs.GetRecordCount() == 1)
			{
				rs.MoveFirst();
				long n = 0;
				CString strOUT;
				double STlat_deg, STlon_deg, BWh;
				CString IDst, str, strBWh;

/////////////////////////
double Hagl_ST,Hg;			
double E,PtGt_ST,kfactor, HasglST, Ptime,Plocation, RxH;
int ENV, syst, P1546Clangle, P1546landsea ,p=1;
CP1546DLG p1546dlg;
if (p1546dlg.DoModal()==IDOK)
{
	Ptime = p1546dlg.m_time;
	Plocation = p1546dlg.m_location;
	kfactor = p1546dlg.m_k;
	RxH = p1546dlg.m_RxH;
	syst = p1546dlg.m_syst;
	ENV = p1546dlg.m_env;
	P1546Clangle = p1546dlg.m_Clangle;
	P1546landsea = p1546dlg.m_landsea;
/////////////////////////////

				while(1)
				{
					if(rs.IsEOF()) break;

					rs.GetFieldValue(_T("IDst"),IDst);
					rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
					rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
					double dist = Distance_km(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
					if((dist <= rng_km)&&(dist > 0.0000001))
					{
						double az = Azimuth_Deg(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
						if((az>=az1)&&(az<=az2))
						{
							n++;
							CString STname,TXfreq,Emission,Polarization,lon,lat;
							lon = DEG2DMSth(_T("LON"),STlon_deg) ;
							lat = DEG2DMSth(_T("LAT"),STlat_deg) ;
							rs.GetFieldValue(_T("STname"),STname);
							rs.GetFieldValue(_T("TXfreq"),TXfreq);
							rs.GetFieldValue(_T("Emission"),Emission);
							rs.GetFieldValue(_T("Polarization"),Polarization);
							double BW = 1000.0*Emission2NBW(Emission);

							if(Polarization==_T("M"))	Polarization = _T("MX");
							rs.GetFieldValue(_T("BWh"),str);	BWh  = atof(str);
							if((BWh==0)||(BWh>359))	strBWh = _T("N");
							else					strBWh = _T("D");

////////////////////////////
	rs.GetFieldValue(_T("Sth_agl"),str);	Hagl_ST  = atof(str);
	rs.GetFieldValue(_T("Power_eirp"),str);	PtGt_ST  = atof(str);

	OnDatabaseStationsindesktop2(STlat_deg,STlon_deg);
	Hg = LatLon2Hg(STlat_deg,STlon_deg);
	HasglST = Hg + Hagl_ST;

	E = E_P1546(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg,
				  HasglST, atof(TXfreq), PtGt_ST, kfactor,
				  Ptime, RxH, ENV, syst, Plocation,
				  P1546Clangle , P1546landsea, p);

////////////////////////////
					//		str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t\t%s\t%s\t%s\t%0.lf\t\t%s\t%s\t") , IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,m_Grid2_thalesReq.GetAt(4),m_Grid2_thalesReq.GetAt(5),m_Grid3_thalesReq.GetAt(3),BW,Polarization,m_Grid3_thalesReq.GetAt(5));
							str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t%0.1lf\t%s\t%s\t%s\t%0.lf\t%s\t%s\t%s\t") , IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,E, m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),m_Grid3_thalesReq.GetAt(3),BW, strBWh ,Polarization, m_Grid3_thalesReq.GetAt(5));
							strOUT = strOUT + _T("\n") + str;
						}//az
					}//dist
					rs.MoveNext();
				}//while

/////////////////////////////
}//p1546dlg
///////////////////////

				strOUT.Delete(0);
				fprintf(fp1,_T("%d\n"),n);
				fprintf(fp1,_T("%s"),strOUT);
				strOUT.Empty();

			}//if rs
			else
				fprintf(fp1,_T("%d\n"),0);

			rs.Close();
			myDB.Close();
			//////////////////////////////////////////////////////////////////////////////////

			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp
	}
	else if	(	(mMfunction==_T("SCT"))||
				(mMfunction==_T("TOR"))||
				(mMfunction==_T("CAM"))||
				(mMfunction==_T("TVM"))
		    )
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];
			fgets( dum1, 1000, fp );		sdum1 = dum1;

			//////////////////////Thales BUG////////////////////////////////
			if	(mMfunction==_T("TVM"))
			{
				int t,n0;
				CString strDUM3,strDUM2,strDUM1 = sdum1;
				n0 = 0;
				while(1)
				{
					t = strDUM1.Find('\t');
					if(t==-1)	break;

					strDUM3 = strDUM1.Left(t);
					if(n0==8) strDUM3 = _T("TP");
					strDUM2 = strDUM2 + strDUM3 + "\t";

					strDUM1.Delete(0,t+1);
					n0++;
				}
				sdum1 = strDUM2 + "\n";
			}
			//////////////////////////////////////////////////////

			fprintf(fp1,_T("%s"),sdum1);
			fprintf(fp1,_T("\n") );
			//////////////////////////////////////////////////////
			CString X1  = m_Grid1_thalesReq.GetAt(4);				
			CString Y1  = m_Grid1_thalesReq.GetAt(5);				
			double X = atof(X1.Left(3)) + (atof(X1.Mid(4,2)))/60.0 + (atof(X1.Mid(6,6)))/3600.0;
			double Y = atof(Y1.Left(2)) + (atof(Y1.Mid(3,2)))/60.0 + (atof(Y1.Mid(5,6)))/3600.0;
			double MOlon_deg = ((X1.Mid(3,1))==_T("E")) ? X : -X;		//deg
			double MOlat_deg = ((Y1.Mid(2,1))==_T("N")) ? Y : -Y;		//deg

			double rng_km  = atof(m_Grid2_thalesReq.GetAt(0))/2.0;		//km
			double az1 = atof(m_Grid2_thalesReq.GetAt(1));				//deg
			double az2 = atof(m_Grid2_thalesReq.GetAt(2));				//deg

			CString str = _T("");
			for(int ii=0;ii<m_Num_thalesReq;ii++)
			{
				double fmin = atof(m_Grid3_thalesReq.GetAt(0+6*ii))/1000000.0;	//MHz
				double fmax = atof(m_Grid3_thalesReq.GetAt(1+6*ii))/1000000.0;	//MHz
				sdum1.Format(_T("((TXfreq>=%lf) AND (TXfreq<=%lf))"), fmin,fmax);
				str = str + _T(" OR ") + sdum1;
			}
			str.Delete(0,4);

			double dumy,  lonmin , lonmax , latmin , latmax ;
			reckon(MOlat_deg,MOlon_deg, rng_km,  0.0,&latmax,&dumy) ;
			reckon(MOlat_deg,MOlon_deg, rng_km,180.0,&latmin,&dumy) ;
			reckon(MOlat_deg,MOlon_deg, rng_km, 90.0,&dumy,&lonmax) ;
			reckon(MOlat_deg,MOlon_deg, rng_km,270.0,&dumy,&lonmin) ;

			CString	Tbl;
			Tbl.Format(_T("SELECT * FROM %s WHERE ( ( %s ) AND ((STlat_deg>=%lf) AND (STlat_deg<=%lf) AND (STlon_deg>=%lf) AND (STlon_deg<=%lf)) );") , mQuerySTR,str,latmin,latmax,lonmin,lonmax);

			CDatabase myDB;		CRecordset rs;
			myDB.Open(_T(mCDBSTR),FALSE,FALSE, "ODBC;", FALSE);
			rs.m_pDatabase = &myDB;
			rs.Open( CRecordset::snapshot, Tbl);
			
			if(rs.GetRecordCount() == 1)
			{
				rs.MoveFirst();
				long n = 0;
				CString strOUT;
				double STlat_deg, STlon_deg,BWh;
				CString IDst, str,strBWh;


/////////////////////////
double Hagl_ST,Hg;			
double E,PtGt_ST,kfactor, HasglST, Ptime,Plocation, RxH;
int ENV, syst, P1546Clangle, P1546landsea ,p=1;
CP1546DLG p1546dlg;
if (p1546dlg.DoModal()==IDOK)
{
	Ptime = p1546dlg.m_time;
	Plocation = p1546dlg.m_location;
	kfactor = p1546dlg.m_k;
	RxH = p1546dlg.m_RxH;
	syst = p1546dlg.m_syst;
	ENV = p1546dlg.m_env;
	P1546Clangle = p1546dlg.m_Clangle;
	P1546landsea = p1546dlg.m_landsea;
/////////////////////////////

				while(1)
				{
					if(rs.IsEOF()) break;
					rs.GetFieldValue(_T("IDst"),IDst);
					rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
					rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
					double dist = Distance_km(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
					if((dist <= rng_km)&&(dist > 0.0000001))
					{
						double az = Azimuth_Deg(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
						if((az>=az1)&&(az<=az2))
						{
							n++;
							CString STname,TXfreq,Emission,Polarization,lon,lat;
							lon = DEG2DMSth(_T("LON"),STlon_deg) ;
							lat = DEG2DMSth(_T("LAT"),STlat_deg) ;
							rs.GetFieldValue(_T("STname"),STname);
							rs.GetFieldValue(_T("TXfreq"),TXfreq);
							rs.GetFieldValue(_T("Emission"),Emission);
							rs.GetFieldValue(_T("Polarization"),Polarization);
							double BW = 1000.0*Emission2NBW(Emission); 

							if(Polarization==_T("M"))	Polarization = _T("MX");
							rs.GetFieldValue(_T("BWh"),str);	BWh  = atof(str);
							if((BWh==0)||(BWh>359))	strBWh = _T("N");
							else					strBWh = _T("D");

////////////////////////////
	rs.GetFieldValue(_T("Sth_agl"),str);	Hagl_ST  = atof(str);
	rs.GetFieldValue(_T("Power_eirp"),str);	PtGt_ST  = atof(str);

	OnDatabaseStationsindesktop2(STlat_deg,STlon_deg);
	Hg = LatLon2Hg(STlat_deg,STlon_deg);
	HasglST = Hg + Hagl_ST;

	E = E_P1546(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg,
				  HasglST, atof(TXfreq), PtGt_ST, kfactor,
				  Ptime, RxH, ENV, syst, Plocation,
				  P1546Clangle , P1546landsea, p);

////////////////////////////

//							str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t\t%s\t%s\t%s\t%0.lf\t%s\t%s\t%s\t") ,       IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,   m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),m_Grid3_thalesReq.GetAt(3),BW, strBWh ,Polarization, m_Grid3_thalesReq.GetAt(5));
							str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t%0.1lf\t%s\t%s\t%s\t%0.lf\t%s\t%s\t%s\t") , IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,E, m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),m_Grid3_thalesReq.GetAt(3),BW, strBWh ,Polarization, m_Grid3_thalesReq.GetAt(5));
							
							
							strOUT = strOUT + _T("\n") + str;
						}//az
					}//dist
					rs.MoveNext();
				}//while

/////////////////////////////
}//p1546dlg
///////////////////////

				strOUT.Delete(0);
				fprintf(fp1,_T("%d\n"),n);
				fprintf(fp1,_T("%s"),strOUT);
				strOUT.Empty();

			}//if rs
			else
				fprintf(fp1,_T("%d\n"),0);

			rs.Close();
			myDB.Close();
			///////////////////////////////////////////////////////

			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp

	}//else if m_Mfunction
	else if	(	(mMfunction==_T("FSM"))||
				(mMfunction==_T("FSF"))||
				(mMfunction==_T("SFS"))||
				(mMfunction==_T("ATR"))
		    )
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];

			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);
			fprintf(fp1,_T("\n") );

			fgets( dum1, 1000, fp );
			fgets( dum1, 1000, fp );		sdum1 = dum1;

			int NsubBand = atoi(sdum1);
			int j = 0;
			CString str;
			for(int i=0;i<NsubBand;i++)
			{
				double Fstart = atof(m_Grid3_thalesReq.GetAt(0+6*i));
				double Fstop  = atof(m_Grid3_thalesReq.GetAt(1+6*i));
				double Fstep  = atof(m_Grid3_thalesReq.GetAt(2+6*i));

				if(Fstep==0)
				{
					sdum1.Format(_T("%d\t\t\t\t%0.0lf\t%s\t\t\t\t\t%s\t\t\t\t%s\t\n") , 1+j, Fstart, m_Grid3_thalesReq.GetAt(4+6*i), m_Grid3_thalesReq.GetAt(3+6*i), m_Grid3_thalesReq.GetAt(5+6*i));
					str = str + sdum1;
					j++;
				}
				else
				{
					double F = Fstart;
					while(1)
					{
						if(F>Fstop) break;
						sdum1.Format(_T("%d\t\t\t\t%0.0lf\t%s\t\t\t\t\t%s\t\t\t\t%s\t\n") , 1+j, F, m_Grid3_thalesReq.GetAt(4+6*i), m_Grid3_thalesReq.GetAt(3+6*i), m_Grid3_thalesReq.GetAt(5+6*i));
						str = str + sdum1;
						F = F + Fstep;
						j++;
					}
				}//if Fstep
			}//for

			fprintf(fp1,_T("%d\n"),j);
			fprintf(fp1,_T("%s"),str);

			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp

	}//else if m_Mfunction
	else if	(
				(mMfunction==_T("USS"))
		    )
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];

			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);
			fprintf(fp1,_T("\n") );

			fgets( dum1, 1000, fp );
			fgets( dum1, 1000, fp );		sdum1 = dum1;

			int NsubBand = atoi(sdum1);
			int j = 0;
			CString str;
			for(int i=0;i<NsubBand;i++)
			{
				double Fstart = atof(m_Grid3_thalesReq.GetAt(0+6*i));
				double Fstop  = atof(m_Grid3_thalesReq.GetAt(1+6*i));
				double Fstep  = atof(m_Grid3_thalesReq.GetAt(2+6*i));
				CString D_Threshold = m_Grid3_thalesReq.GetAt(3+6*i);
				CString TxEmi = m_Grid3_thalesReq.GetAt(4+6*i);
				CString Ant = m_Grid3_thalesReq.GetAt(5+6*i);

				int n = FindStationDB(Fstart/1000000.0,Fstop/1000000.0,D_Threshold, Ant,&sdum1); 
				if(n!=0)
				{
					str = str + _T("\n") + sdum1;
					j = j + n;
				}
				else
				{
					if(Fstep==0)
					{
						sdum1.Format(_T("%d\t\t\t\t%0.0lf\t%s\t\t\t\t\t%s\t\t\t\t%s\t") , 1+j, Fstart, TxEmi, D_Threshold, Ant);
						str = str + _T("\n") + sdum1;
						j++;
					}
					else
					{
						double F = Fstart;
						while(1)
						{
							if(F>Fstop) break;
							sdum1.Format(_T("%d\t\t\t\t%0.0lf\t%s\t\t\t\t\t%s\t\t\t\t%s\t") , 1+j, F, TxEmi, D_Threshold, Ant);
							str = str + _T("\n") + sdum1;
							j++;
							F = F + Fstep;
						}
					}//if Fstep
				}// n
			}//for
	
			str.Delete(0);

			fprintf(fp1,_T("%d\n"),j);
			fprintf(fp1,_T("%s"),str);
			str.Empty();

			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp

	}//else if m_Mfunction

	if(flag)
	{
		CString str = m_PathOUTBOXth + _T("\\") + Req_fileName;
		MoveFile(mReq_filepath,  str);
//		ShellExecute(NULL,"Open","Notepad",mChk_filepath,NULL,SW_SHOWNORMAL);
	}

}

int CSMS4DCView::FindStationDB(double fmin,double fmax,CString D_Threshold,CString Ant,CString *Sout) 
{
	CString mQuerySTR = ((CSMS4DCApp *)AfxGetApp())->Query_STtable();			
	CString mCDBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;			

	CString strOUT;
	int n = 0;
	CString sdum1;
	//////////////////////////////////////////////////////
	CString X1  = m_Grid1_thalesReq.GetAt(4);				
	CString Y1  = m_Grid1_thalesReq.GetAt(5);				
	double X = atof(X1.Left(3)) + (atof(X1.Mid(4,2)))/60.0 + (atof(X1.Mid(6,6)))/3600.0;
	double Y = atof(Y1.Left(2)) + (atof(Y1.Mid(3,2)))/60.0 + (atof(Y1.Mid(5,6)))/3600.0;
	double MOlon_deg = ((X1.Mid(3,1))==_T("E")) ? X : -X;		//deg
	double MOlat_deg = ((Y1.Mid(2,1))==_T("N")) ? Y : -Y;		//deg

	double rng_km  = atof(m_Grid2_thalesReq.GetAt(0))/2.0;		//km
	double az1 = atof(m_Grid2_thalesReq.GetAt(1));				//deg
	double az2 = atof(m_Grid2_thalesReq.GetAt(2));				//deg

	double dumy,  lonmin , lonmax , latmin , latmax ;
	reckon(MOlat_deg,MOlon_deg, rng_km,  0.0,&latmax,&dumy) ;
	reckon(MOlat_deg,MOlon_deg, rng_km,180.0,&latmin,&dumy) ;
	reckon(MOlat_deg,MOlon_deg, rng_km, 90.0,&dumy,&lonmax) ;
	reckon(MOlat_deg,MOlon_deg, rng_km,270.0,&dumy,&lonmin) ;

	CString	Tbl;
	Tbl.Format(_T("SELECT * FROM %s WHERE ( ((TXfreq>=%lf) AND (TXfreq<=%lf)) AND ((STlat_deg>=%lf) AND (STlat_deg<=%lf) AND (STlon_deg>=%lf) AND (STlon_deg<=%lf)) );") , mQuerySTR,fmin,fmax,latmin,latmax,lonmin,lonmax);

	CDatabase myDB;		CRecordset rs;
	myDB.Open(_T(mCDBSTR),FALSE,FALSE, "ODBC;", FALSE);
	rs.m_pDatabase = &myDB;
	rs.Open( CRecordset::snapshot, Tbl);

	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		double STlat_deg, STlon_deg, BWh;
		CString IDst, str, strBWh;


/////////////////////////
double Hagl_ST,Hg;			
double E,PtGt_ST,kfactor, HasglST, Ptime,Plocation, RxH;
int ENV, syst, P1546Clangle, P1546landsea ,p=1;
CP1546DLG p1546dlg;
if (p1546dlg.DoModal()==IDOK)
{
	Ptime = p1546dlg.m_time;
	Plocation = p1546dlg.m_location;
	kfactor = p1546dlg.m_k;
	RxH = p1546dlg.m_RxH;
	syst = p1546dlg.m_syst;
	ENV = p1546dlg.m_env;
	P1546Clangle = p1546dlg.m_Clangle;
	P1546landsea = p1546dlg.m_landsea;
/////////////////////////////

		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
			rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
			double dist = Distance_km(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
			if((dist <= rng_km)&&(dist > 0.0000001))
			{
				double az = Azimuth_Deg(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
				if((az>=az1)&&(az<=az2))
				{
					n++;
					CString STname,TXfreq,Emission,Polarization,lon,lat;
					lon = DEG2DMSth(_T("LON"),STlon_deg) ;
					lat = DEG2DMSth(_T("LAT"),STlat_deg) ;
					rs.GetFieldValue(_T("STname"),STname);
					rs.GetFieldValue(_T("TXfreq"),TXfreq);
					rs.GetFieldValue(_T("Emission"),Emission);
					rs.GetFieldValue(_T("Polarization"),Polarization);
					double BW = 1000.0*Emission2NBW(Emission); 

					if(Polarization==_T("M"))	Polarization = _T("MX");
					rs.GetFieldValue(_T("BWh"),str);	BWh  = atof(str);
					if((BWh==0)||(BWh>359))	strBWh = _T("N");
					else					strBWh = _T("D");

////////////////////////////
	rs.GetFieldValue(_T("Sth_agl"),str);	Hagl_ST  = atof(str);
	rs.GetFieldValue(_T("Power_eirp"),str);	PtGt_ST  = atof(str);

	OnDatabaseStationsindesktop2(STlat_deg,STlon_deg);
	Hg = LatLon2Hg(STlat_deg,STlon_deg);
	HasglST = Hg + Hagl_ST;

	E = E_P1546(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg,
				  HasglST, atof(TXfreq), PtGt_ST, kfactor,
				  Ptime, RxH, ENV, syst, Plocation,
				  P1546Clangle , P1546landsea, p);

////////////////////////////

			//		str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t\t%s\t%s\t%s\t%0.lf\t\t%s\t%s\t") ,         IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,   m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),D_Threshold,BW,Polarization,Ant);
					str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t%0.1lf\t%s\t%s\t%s\t%0.lf\t%s\t%s\t%s\t") , IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,E, m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),D_Threshold,BW, strBWh ,Polarization, Ant);
					
					strOUT = strOUT + _T("\n") + str;
				}//az
			}//dist
			rs.MoveNext();
		}//while

/////////////////////////////
}//p1546dlg
///////////////////////

		strOUT.Delete(0);

	}//if rs
	rs.Close();
	myDB.Close();

	*Sout = strOUT;
	strOUT.Empty();

	return	n;
}
*/

#include "P1546DLG.h"
void CSMS4DCView::OnBUTTONCreateCHK_thalesReq(CString mReq_filepath,
											  double Ptime, double Plocation, double kfactor, double RxH, 
											  int syst, int ENV, int P1546Clangle, int P1546landsea )
{
	if(mReq_filepath.GetLength()==0)	return;
	CString Req_fileName = mReq_filepath;
	int L = Req_fileName.ReverseFind('\\');
	Req_fileName.Delete(0,L+1);

	CString Chk_fileName = Req_fileName;
	int t = Chk_fileName.Replace(_T(".req"),_T(".chk"));
	if(t==0)
		Chk_fileName.Replace(_T(".REQ"),_T(".chk"));

	Get_ReqFile(mReq_filepath);

	FindThalesIniFile(&m_PathINBOXth, &m_PathOUTBOXth, &m_PathREQUESTth);

	CString mChk_filepath = m_PathINBOXth + "\\" + m_Grid1_thalesReq.GetAt(3) + "\\";
	CreateDirectory(mChk_filepath, NULL);
	mChk_filepath = mChk_filepath + Chk_fileName;

	CString	mMfunction  = m_Grid1_thalesReq.GetAt(0);
	CString mQuerySTR = ((CSMS4DCApp *)AfxGetApp())->Query_STtable();			
	CString mCDBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;			

	BOOL flag = FALSE;

	if(	(mMfunction==_T("FBM"))||
		(mMfunction==_T("FBF"))
	  )
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];

			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);

			fgets( dum1, 1000, fp );
			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);

			int NsubBand = atoi(sdum1);
			for(int i=0;i<NsubBand;i++)
			{
				fgets( dum1, 1000, fp );	sdum1 = dum1;
				fprintf(fp1,_T("%s"),sdum1);
			}
			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp
	}
	else if	(	(mMfunction==_T("FSF"))||
				(mMfunction==_T("FSM"))||
				(mMfunction==_T("SFS"))
		    )
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];

			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);
			fprintf(fp1,_T("\n") );

			fgets( dum1, 1000, fp );
			fgets( dum1, 1000, fp );		sdum1 = dum1;

			int NsubBand = atoi(sdum1);
			int j = 0;
			CString str;
			for(int i=0;i<NsubBand;i++)
			{
				double Fstart = atof(m_Grid3_thalesReq.GetAt(0+6*i));
				double Fstop  = atof(m_Grid3_thalesReq.GetAt(1+6*i));
				double Fstep  = atof(m_Grid3_thalesReq.GetAt(2+6*i));

				if(Fstep==0)
				{
					sdum1.Format(_T("%d\t\t\t\t%0.0lf\t%s\t\t\t\t\t%s\t\t\t\t%s\t\n") , 1+j, Fstart, m_Grid3_thalesReq.GetAt(4+6*i), m_Grid3_thalesReq.GetAt(3+6*i), m_Grid3_thalesReq.GetAt(5+6*i));
					str = str + sdum1;
					j++;
				}
				else
				{
					double F = Fstart;
					while(1)
					{
						if(F>Fstop) break;
						sdum1.Format(_T("%d\t\t\t\t%0.0lf\t%s\t\t\t\t\t%s\t\t\t\t%s\t\n") , 1+j, F, m_Grid3_thalesReq.GetAt(4+6*i), m_Grid3_thalesReq.GetAt(3+6*i), m_Grid3_thalesReq.GetAt(5+6*i));
						str = str + sdum1;
						F = F + Fstep;
						j++;
					}
				}//if Fstep
			}//for

			fprintf(fp1,_T("%d\n"),j);
			fprintf(fp1,_T("%s"),str);

			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp

	}//else if m_Mfunction

	else if	(mMfunction==_T("UBS"))
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];

			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);

			fgets( dum1, 1000, fp );
			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);

			int NsubBand = atoi(sdum1);
			for(int i=0;i<NsubBand;i++)
			{
				fgets( dum1, 1000, fp );	sdum1 = dum1;
				fprintf(fp1,_T("%s"),sdum1);
			}

			///////////////////////////////////Stations///////////////////////////////////////////////
	//		CString X1  = m_Grid1_thalesReq.GetAt(4);				
	//		CString Y1  = m_Grid1_thalesReq.GetAt(5);
			
			CString X1,Y1;
			int mm = FindMonitoringStation(&X1, &Y1);
			if(mm==0)  return;

			double X = atof(X1.Left(3)) + (atof(X1.Mid(4,2)))/60.0 + (atof(X1.Mid(6,6)))/3600.0;
			double Y = atof(Y1.Left(2)) + (atof(Y1.Mid(3,2)))/60.0 + (atof(Y1.Mid(5,6)))/3600.0;
			double MOlon_deg = ((X1.Mid(3,1))==_T("E")) ? X : -X;		//deg
			double MOlat_deg = ((Y1.Mid(2,1))==_T("N")) ? Y : -Y;		//deg

			double rng_km  = atof(m_Grid2_thalesReq.GetAt(0))/2.0;		//km
			double az1 = atof(m_Grid2_thalesReq.GetAt(1));				//deg
			double az2 = atof(m_Grid2_thalesReq.GetAt(2));				//deg

			CString str = _T("");
			for(int ii=0;ii<m_Num_thalesReq;ii++)
			{
				double fmin = atof(m_Grid3_thalesReq.GetAt(0+6*ii))/1000000.0;	//MHz
				double fmax = atof(m_Grid3_thalesReq.GetAt(1+6*ii))/1000000.0;	//MHz
				sdum1.Format(_T("((TXfreq>=%lf) AND (TXfreq<=%lf))"), fmin,fmax);
				str = str + _T(" OR ") + sdum1;
			}
			str.Delete(0,4);

			double dumy,  lonmin , lonmax , latmin , latmax ;
			reckon(MOlat_deg,MOlon_deg, rng_km,  0.0,&latmax,&dumy) ;
			reckon(MOlat_deg,MOlon_deg, rng_km,180.0,&latmin,&dumy) ;
			reckon(MOlat_deg,MOlon_deg, rng_km, 90.0,&dumy,&lonmax) ;
			reckon(MOlat_deg,MOlon_deg, rng_km,270.0,&dumy,&lonmin) ;

			CString	Tbl;
			Tbl.Format(_T("SELECT * FROM %s WHERE ( ( %s ) AND ((STlat_deg>=%lf) AND (STlat_deg<=%lf) AND (STlon_deg>=%lf) AND (STlon_deg<=%lf)) );") , mQuerySTR,str,latmin,latmax,lonmin,lonmax);

			CDatabase myDB;		CRecordset rs;
			myDB.Open(_T(mCDBSTR),FALSE,FALSE, "ODBC;", FALSE);
			rs.m_pDatabase = &myDB;
			rs.Open( CRecordset::snapshot, Tbl);
			
			if(rs.GetRecordCount() == 1)
			{
				rs.MoveFirst();
				long n = 0;
				CString strOUT;
				double STlat_deg, STlon_deg, BWh;
				CString IDst, str, strBWh;
				double HasglST,E,PtGt_ST,Hagl_ST,Hg;	int p=1;			

				while(1)
				{
					if(rs.IsEOF()) break;

					rs.GetFieldValue(_T("IDst"),IDst);
					rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
					rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
					double dist = Distance_km(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
					if((dist <= rng_km)&&(dist > 0.0000001))
					{
						double az = Azimuth_Deg(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
						if((az>=az1)&&(az<=az2))
						{
							n++;
							CString STname,TXfreq,Emission,Polarization,lon,lat;
							lon = DEG2DMSth(_T("LON"),STlon_deg) ;
							lat = DEG2DMSth(_T("LAT"),STlat_deg) ;
							rs.GetFieldValue(_T("STname"),STname);
							rs.GetFieldValue(_T("TXfreq"),TXfreq);
							rs.GetFieldValue(_T("Emission"),Emission);
							rs.GetFieldValue(_T("Polarization"),Polarization);
							double BW = 1000.0*Emission2NBW(Emission);

							if(Polarization==_T("M"))	Polarization = _T("MX");
							rs.GetFieldValue(_T("BWh"),str);	BWh  = atof(str);
							if((BWh==0)||(BWh>359))	strBWh = _T("N");
							else					strBWh = _T("D");

						////////////////////////////
							rs.GetFieldValue(_T("Sth_agl"),str);	Hagl_ST  = atof(str);
							rs.GetFieldValue(_T("Power_eirp"),str);	PtGt_ST  = atof(str);

							OnDatabaseStationsindesktop2(STlat_deg,STlon_deg);
							Hg = LatLon2Hg(STlat_deg,STlon_deg);
							HasglST = Hg + Hagl_ST;

double Drange = Distance_km(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg); 
LoadIDWMmap_r(STlat_deg,STlon_deg, Drange);

//  E = E_P1546(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg, HasglST, atof(TXfreq), PtGt_ST, kfactor, Ptime, RxH, ENV, syst, Plocation, P1546Clangle , P1546landsea, p);
E = E_P1546_V05(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg, Hagl_ST, atof(TXfreq), PtGt_ST, kfactor, Ptime, RxH, ENV, syst, Plocation, P1546Clangle , P1546landsea, p);

						////////////////////////////
					//		str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t\t%s\t%s\t%s\t%0.lf\t\t%s\t%s\t") , IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,m_Grid2_thalesReq.GetAt(4),m_Grid2_thalesReq.GetAt(5),m_Grid3_thalesReq.GetAt(3),BW,Polarization,m_Grid3_thalesReq.GetAt(5));
							str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t%0.1lf\t%s\t%s\t%s\t%0.lf\t%s\t%s\t%s\t") , IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,E, m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),m_Grid3_thalesReq.GetAt(3),BW, strBWh ,Polarization, m_Grid3_thalesReq.GetAt(5));
							strOUT = strOUT + _T("\n") + str;
						}//az
					}//dist
					rs.MoveNext();
				}//while
				strOUT.Delete(0);
				fprintf(fp1,_T("%d\n"),n);
				fprintf(fp1,_T("%s"),strOUT);
				strOUT.Empty();

			}//if rs
			else
				fprintf(fp1,_T("%d\n"),0);

			rs.Close();
			myDB.Close();
			//////////////////////////////////////////////////////////////////////////////////

			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp
	}
	else if	(	(mMfunction==_T("SCT"))||
				(mMfunction==_T("TOR"))||
				(mMfunction==_T("CAM"))||
				(mMfunction==_T("TVM"))
		    )
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];
			fgets( dum1, 1000, fp );		sdum1 = dum1;

			//////////////////////Thales BUG////////////////////////////////
			if	(mMfunction==_T("TVM"))
			{
				int t,n0;
				CString strDUM3,strDUM2,strDUM1 = sdum1;
				n0 = 0;
				while(1)
				{
					t = strDUM1.Find('\t');
					if(t==-1)	break;

					strDUM3 = strDUM1.Left(t);
					if(n0==8) strDUM3 = _T("TP");
					strDUM2 = strDUM2 + strDUM3 + "\t";

					strDUM1.Delete(0,t+1);
					n0++;
				}
				sdum1 = strDUM2 + "\n";
			}
			//////////////////////////////////////////////////////

			fprintf(fp1,_T("%s"),sdum1);
			fprintf(fp1,_T("\n") );
			//////////////////////////////////////////////////////
		//	CString X1  = m_Grid1_thalesReq.GetAt(4);				
		//	CString Y1  = m_Grid1_thalesReq.GetAt(5);
			
			CString X1,Y1;
			int mm = FindMonitoringStation(&X1, &Y1);
			if(mm==0)  return;

			double X = atof(X1.Left(3)) + (atof(X1.Mid(4,2)))/60.0 + (atof(X1.Mid(6,6)))/3600.0;
			double Y = atof(Y1.Left(2)) + (atof(Y1.Mid(3,2)))/60.0 + (atof(Y1.Mid(5,6)))/3600.0;
			double MOlon_deg = ((X1.Mid(3,1))==_T("E")) ? X : -X;		//deg
			double MOlat_deg = ((Y1.Mid(2,1))==_T("N")) ? Y : -Y;		//deg

			double rng_km  = atof(m_Grid2_thalesReq.GetAt(0))/2.0;		//km
			double az1 = atof(m_Grid2_thalesReq.GetAt(1));				//deg
			double az2 = atof(m_Grid2_thalesReq.GetAt(2));				//deg

			CString str = _T("");
			for(int ii=0;ii<m_Num_thalesReq;ii++)
			{
				double fmin = atof(m_Grid3_thalesReq.GetAt(0+6*ii))/1000000.0;	//MHz
				double fmax = atof(m_Grid3_thalesReq.GetAt(1+6*ii))/1000000.0;	//MHz
				sdum1.Format(_T("((TXfreq>=%lf) AND (TXfreq<=%lf))"), fmin,fmax);
				str = str + _T(" OR ") + sdum1;
			}
			str.Delete(0,4);

			double dumy,  lonmin , lonmax , latmin , latmax ;
			reckon(MOlat_deg,MOlon_deg, rng_km,  0.0,&latmax,&dumy) ;
			reckon(MOlat_deg,MOlon_deg, rng_km,180.0,&latmin,&dumy) ;
			reckon(MOlat_deg,MOlon_deg, rng_km, 90.0,&dumy,&lonmax) ;
			reckon(MOlat_deg,MOlon_deg, rng_km,270.0,&dumy,&lonmin) ;

			CString	Tbl;
			Tbl.Format(_T("SELECT * FROM %s WHERE ( ( %s ) AND ((STlat_deg>=%lf) AND (STlat_deg<=%lf) AND (STlon_deg>=%lf) AND (STlon_deg<=%lf)) );") , mQuerySTR,str,latmin,latmax,lonmin,lonmax);

			CDatabase myDB;		CRecordset rs;
			myDB.Open(_T(mCDBSTR),FALSE,FALSE, "ODBC;", FALSE);
			rs.m_pDatabase = &myDB;
			rs.Open( CRecordset::snapshot, Tbl);
			
			if(rs.GetRecordCount() == 1)
			{
				rs.MoveFirst();
				long n = 0;
				CString strOUT;
				double STlat_deg, STlon_deg,BWh;
				CString IDst, str,strBWh;

				double HasglST,E,PtGt_ST,Hagl_ST,Hg;	int p=1;			

				while(1)
				{
					if(rs.IsEOF()) break;
					rs.GetFieldValue(_T("IDst"),IDst);
					rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
					rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
					double dist = Distance_km(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
					if((dist <= rng_km)&&(dist > 0.0000001))
					{
						double az = Azimuth_Deg(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
						if((az>=az1)&&(az<=az2))
						{
							n++;
							CString STname,TXfreq,Emission,Polarization,lon,lat;
							lon = DEG2DMSth(_T("LON"),STlon_deg) ;
							lat = DEG2DMSth(_T("LAT"),STlat_deg) ;
							rs.GetFieldValue(_T("STname"),STname);
							rs.GetFieldValue(_T("TXfreq"),TXfreq);
							rs.GetFieldValue(_T("Emission"),Emission);
							rs.GetFieldValue(_T("Polarization"),Polarization);
							double BW = 1000.0*Emission2NBW(Emission); 

							if(Polarization==_T("M"))	Polarization = _T("MX");
							rs.GetFieldValue(_T("BWh"),str);	BWh  = atof(str);
							if((BWh==0)||(BWh>359))	strBWh = _T("N");
							else					strBWh = _T("D");

						////////////////////////////
							rs.GetFieldValue(_T("Sth_agl"),str);	Hagl_ST  = atof(str);
							rs.GetFieldValue(_T("Power_eirp"),str);	PtGt_ST  = atof(str);

							OnDatabaseStationsindesktop2(STlat_deg,STlon_deg);
							Hg = LatLon2Hg(STlat_deg,STlon_deg);
							HasglST = Hg + Hagl_ST;

double Drange = Distance_km(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg); 
LoadIDWMmap_r(STlat_deg,STlon_deg, Drange);

//  E = E_P1546(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg, HasglST, atof(TXfreq), PtGt_ST, kfactor, Ptime, RxH, ENV, syst, Plocation, P1546Clangle , P1546landsea, p);
E = E_P1546_V05(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg, Hagl_ST, atof(TXfreq), PtGt_ST, kfactor, Ptime, RxH, ENV, syst, Plocation, P1546Clangle , P1546landsea, p);

						////////////////////////////

//							str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t\t%s\t%s\t%s\t%0.lf\t%s\t%s\t%s\t") ,       IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,   m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),m_Grid3_thalesReq.GetAt(3),BW, strBWh ,Polarization, m_Grid3_thalesReq.GetAt(5));
							str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t%0.1lf\t%s\t%s\t%s\t%0.lf\t%s\t%s\t%s\t") , IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,E, m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),m_Grid3_thalesReq.GetAt(3),BW, strBWh ,Polarization, m_Grid3_thalesReq.GetAt(5));
							
							
							strOUT = strOUT + _T("\n") + str;
						}//az
					}//dist
					rs.MoveNext();
				}//while
				strOUT.Delete(0);
				fprintf(fp1,_T("%d\n"),n);
				fprintf(fp1,_T("%s"),strOUT);
				strOUT.Empty();

			}//if rs
			else
				fprintf(fp1,_T("%d\n"),0);

			rs.Close();
			myDB.Close();
			///////////////////////////////////////////////////////

			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp

	}//else if m_Mfunction
	else if	(
				(mMfunction==_T("ATR"))||
				(mMfunction==_T("USS"))
		    )
	{
		FILE *fp = fopen(mReq_filepath,"rt");
		if(fp)
		{
			FILE *fp1 = fopen(mChk_filepath,"wt");

			CString sdum1;
			char dum1[1000];

			fgets( dum1, 1000, fp );		sdum1 = dum1;
			fprintf(fp1,_T("%s"),sdum1);
			fprintf(fp1,_T("\n") );

			fgets( dum1, 1000, fp );
			fgets( dum1, 1000, fp );		sdum1 = dum1;

			int NsubBand = atoi(sdum1);
			int j = 0;
			CString str;
			for(int i=0;i<NsubBand;i++)
			{
				double Fstart = atof(m_Grid3_thalesReq.GetAt(0+6*i));
				double Fstop  = atof(m_Grid3_thalesReq.GetAt(1+6*i));
				double Fstep  = atof(m_Grid3_thalesReq.GetAt(2+6*i));
				CString D_Threshold = m_Grid3_thalesReq.GetAt(3+6*i);
				CString TxEmi = m_Grid3_thalesReq.GetAt(4+6*i);
				CString Ant = m_Grid3_thalesReq.GetAt(5+6*i);

		//		int n = FindStationDB(Fstart/1000000.0,Fstop/1000000.0,D_Threshold, Ant,&sdum1); 
				int n = FindStationDB(Fstart/1000000.0,Fstop/1000000.0,D_Threshold, Ant,&sdum1,
									  Ptime, Plocation, kfactor, RxH, syst, ENV, P1546Clangle, P1546landsea); 

				if(n!=0)
				{
					str = str + _T("\n") + sdum1;
					j = j + n;
				}
				else
				{
					if(Fstep==0)
					{
						sdum1.Format(_T("%d\t\t\t\t%0.0lf\t%s\t\t\t\t\t%s\t\t\t\t%s\t") , 1+j, Fstart, TxEmi, D_Threshold, Ant);
						str = str + _T("\n") + sdum1;
						j++;
					}
					else
					{
						double F = Fstart;
						while(1)
						{
							if(F>Fstop) break;
							sdum1.Format(_T("%d\t\t\t\t%0.0lf\t%s\t\t\t\t\t%s\t\t\t\t%s\t") , 1+j, F, TxEmi, D_Threshold, Ant);
							str = str + _T("\n") + sdum1;
							j++;
							F = F + Fstep;
						}
					}//if Fstep
				}// n
			}//for
	
			str.Delete(0);

			fprintf(fp1,_T("%d\n"),j);
			fprintf(fp1,_T("%s"),str);
			str.Empty();

			fclose(fp1);
			fclose(fp);
			flag = TRUE;
		}//fp

	}//else if m_Mfunction

	if(flag)
	{
		CString str = m_PathOUTBOXth + _T("\\") + Req_fileName;
		MoveFile(mReq_filepath,  str);
//		ShellExecute(NULL,"Open","Notepad",mChk_filepath,NULL,SW_SHOWNORMAL);
	}
}

int CSMS4DCView::FindMonitoringStation(CString * X, CString * Y) 
{
	CString X1  = m_Grid1_thalesReq.GetAt(4);				
	CString Y1  = m_Grid1_thalesReq.GetAt(5);
	if((X1.GetLength()==0)||(Y1.GetLength()==0))
	{
		CString name  = m_Grid1_thalesReq.GetAt(3);	
		name.TrimLeft();		name.TrimRight();
		CString MstationPath = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("\\Texts\\MStation.txt");
		FILE *fp;
		if(fp=fopen(MstationPath,"rt"))
		{
			char dum1[100];	CString sdum1;
			int n = 0;
			while( !feof( fp ) )
			{
				dum1[0] = '\0';			fscanf( fp, "%s", dum1 );	
				dum1[0] = '\0';			fscanf( fp, "%s", dum1 );	
				sdum1 = dum1;
				sdum1.TrimLeft();		sdum1.TrimRight();
				if(sdum1==name)
				{
					dum1[0] = '\0';		fscanf( fp, "%s", dum1 );		X1 = dum1;
					dum1[0] = '\0';		fscanf( fp, "%s", dum1 );		Y1 = dum1;
				}
				else
				{
					dum1[0] = '\0';			fscanf( fp, "%s", dum1 );	
					dum1[0] = '\0';			fscanf( fp, "%s", dum1 );	
				}
			}//while
			fclose(fp);
		}//end if
	}
	*X = X1;	*Y = Y1;
	if((X1.GetLength()==0)||(Y1.GetLength()==0))	return 0;

	return 1;
}


int CSMS4DCView::FindStationDB(double fmin,double fmax,CString D_Threshold,CString Ant,CString *Sout,
											  double Ptime, double Plocation, double kfactor, double RxH, 
											  int syst, int ENV, int P1546Clangle, int P1546landsea) 
{
	CString mQuerySTR = ((CSMS4DCApp *)AfxGetApp())->Query_STtable();			
	CString mCDBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;			

	CString sdum1, strOUT;
	int n = 0;
	//////////////////////////////////////////////////////
	CString X1,Y1;
	int mm = FindMonitoringStation(&X1, &Y1);
	if(mm==0)  return 0;

	double X = atof(X1.Left(3)) + (atof(X1.Mid(4,2)))/60.0 + (atof(X1.Mid(6,6)))/3600.0;
	double Y = atof(Y1.Left(2)) + (atof(Y1.Mid(3,2)))/60.0 + (atof(Y1.Mid(5,6)))/3600.0;
	double MOlon_deg = ((X1.Mid(3,1))==_T("E")) ? X : -X;		//deg
	double MOlat_deg = ((Y1.Mid(2,1))==_T("N")) ? Y : -Y;		//deg

	double rng_km  = atof(m_Grid2_thalesReq.GetAt(0))/2.0;		//km
	double az1 = atof(m_Grid2_thalesReq.GetAt(1));				//deg
	double az2 = atof(m_Grid2_thalesReq.GetAt(2));				//deg

	double dumy,  lonmin , lonmax , latmin , latmax ;
	reckon(MOlat_deg,MOlon_deg, rng_km,  0.0,&latmax,&dumy) ;
	reckon(MOlat_deg,MOlon_deg, rng_km,180.0,&latmin,&dumy) ;
	reckon(MOlat_deg,MOlon_deg, rng_km, 90.0,&dumy,&lonmax) ;
	reckon(MOlat_deg,MOlon_deg, rng_km,270.0,&dumy,&lonmin) ;

	CString	Tbl;
	Tbl.Format(_T("SELECT * FROM %s WHERE ( ((TXfreq>=%lf) AND (TXfreq<=%lf)) AND ((STlat_deg>=%lf) AND (STlat_deg<=%lf) AND (STlon_deg>=%lf) AND (STlon_deg<=%lf)) );") , mQuerySTR,fmin,fmax,latmin,latmax,lonmin,lonmax);

	CDatabase myDB;		CRecordset rs;
	myDB.Open(_T(mCDBSTR),FALSE,FALSE, "ODBC;", FALSE);
	rs.m_pDatabase = &myDB;
	rs.Open( CRecordset::snapshot, Tbl);

	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		double STlat_deg, STlon_deg, BWh;
		CString IDst, str, strBWh;

		double HasglST,E,PtGt_ST,Hagl_ST,Hg;	int p=1;			
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue(_T("IDst"),IDst);
			rs.GetFieldValue(_T("STlat_deg"),str);		STlat_deg = atof(str);
			rs.GetFieldValue(_T("STlon_deg"),str);		STlon_deg = atof(str);
			double dist = Distance_km(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
			if((dist <= rng_km)&&(dist > 0.0000001))
			{
				double az = Azimuth_Deg(MOlat_deg, MOlon_deg, STlat_deg,STlon_deg);
				if((az>=az1)&&(az<=az2))
				{
					n++;
					CString STname,TXfreq,Emission,Polarization,lon,lat;
					lon = DEG2DMSth(_T("LON"),STlon_deg) ;
					lat = DEG2DMSth(_T("LAT"),STlat_deg) ;
					rs.GetFieldValue(_T("STname"),STname);
					rs.GetFieldValue(_T("TXfreq"),TXfreq);
					rs.GetFieldValue(_T("Emission"),Emission);
					rs.GetFieldValue(_T("Polarization"),Polarization);
					double BW = 1000.0*Emission2NBW(Emission); 

					if(Polarization==_T("M"))	Polarization = _T("MX");
					rs.GetFieldValue(_T("BWh"),str);	BWh  = atof(str);
					if((BWh==0)||(BWh>359))	strBWh = _T("N");
					else					strBWh = _T("D");

				////////////////////////////
					rs.GetFieldValue(_T("Sth_agl"),str);	Hagl_ST  = atof(str);
					rs.GetFieldValue(_T("Power_eirp"),str);	PtGt_ST  = atof(str);

					OnDatabaseStationsindesktop2(STlat_deg,STlon_deg);
					Hg = LatLon2Hg(STlat_deg,STlon_deg);
					HasglST = Hg + Hagl_ST;

double Drange = Distance_km(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg); 
LoadIDWMmap_r(STlat_deg,STlon_deg, Drange);

//  E = E_P1546(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg, HasglST, atof(TXfreq), PtGt_ST, kfactor, Ptime, RxH, ENV, syst, Plocation, P1546Clangle , P1546landsea, p);
E = E_P1546_V05(STlat_deg,STlon_deg, MOlat_deg, MOlon_deg, Hagl_ST, atof(TXfreq), PtGt_ST, kfactor, Ptime, RxH, ENV, syst, Plocation, P1546Clangle , P1546landsea, p);

				////////////////////////////

			//		str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t\t%s\t%s\t%s\t%0.lf\t\t%s\t%s\t") ,         IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,   m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),D_Threshold,BW,Polarization,Ant);
					str.Format(_T("%s\t%s\t%s\t%s\t%0.lf\t%s\t%0.1lf\t%0.1lf\t%s\t%s\t%s\t%0.lf\t%s\t%s\t%s\t") , IDst,STname,lon,lat,1000000.0*atof(TXfreq),Emission,az,E, m_Grid2_thalesReq.GetAt(4), m_Grid2_thalesReq.GetAt(5),D_Threshold,BW, strBWh ,Polarization, Ant);
					
					strOUT = strOUT + _T("\n") + str;
				}//az
			}//dist
			rs.MoveNext();
		}//while
		strOUT.Delete(0);

	}//if rs
	rs.Close();
	myDB.Close();

	*Sout = strOUT;
	strOUT.Empty();

	return	n;
}

int CSMS4DCView::PointInArea(double Lats,double Lons,double Lat1,double Lon1,double Lat2,double Lon2) 
{
	/*double pi = 4.0*atan(1.0);*/	float POINTs[1][2], CRDARR[4][2];	long NRPNT = 4;
	POINTs[0][0] = (float)(Lons*pi/180.0);	POINTs[0][1] = (float)(Lats*pi/180.0);
	
	CRDARR[0][0] = (float)(Lon1*pi/180.0);	CRDARR[0][1] = (float)(min(Lat1,Lat2)*pi/180.0);
	CRDARR[1][0] = (float)(Lon2*pi/180.0);	CRDARR[1][1] = (float)(min(Lat1,Lat2)*pi/180.0);
	CRDARR[2][0] = (float)(Lon2*pi/180.0);	CRDARR[2][1] = (float)(max(Lat1,Lat2)*pi/180.0);
	CRDARR[3][0] = (float)(Lon1*pi/180.0);	CRDARR[3][1] = (float)(max(Lat1,Lat2)*pi/180.0);
	int uflag = -GEOPIA2((float *)POINTs, (float *)CRDARR, &NRPNT);
	return uflag;
}

void CSMS4DCView::SetBoxCorner() 
{
	int xmin = min(m_stBoxPoint.x , m_enBoxPoint.x);
	int xmax = max(m_stBoxPoint.x , m_enBoxPoint.x);
	int ymin = min(m_stBoxPoint.y , m_enBoxPoint.y);
	int ymax = max(m_stBoxPoint.y , m_enBoxPoint.y);
	m_stBoxPoint = CPoint(xmin, ymax);
	m_enBoxPoint = CPoint(xmax, ymin);
}

//--------------------------------------------------------------------------------------------
///////////////////////////////Monitoring Others//////////////////////////////////////////////
//--------------------------------------------------------------------------------------------

//------------------Others-------Respond to M2S order--------------------------------
void CSMS4DCView::OnMonitoringOthersRespondtom2sorder() 
{
	m_OthersOrder = !m_OthersOrder;
	if(m_OthersOrder)	// Start up the timer...
	{
		FindOthersIniFile(&m_PathINBOXothers, &m_PathOUTBOXothers);

		ASSERT(GetSafeHwnd());     
		m_nTimerOthersID = SetTimer(ID_OthersTIMER,10000,NULL);
		m_thisListOthers.SetAt(m_nTimerOthersID, (LPVOID) this);
	}
	else				// Stop the timer
	{
		::KillTimer( this->m_hWnd, m_nTimerOthersID);
		m_thisListOthers.RemoveKey(m_nTimerOthersID);   
		m_nTimerOthersID = 0;
	}	
}
void CSMS4DCView::OnUpdateMonitoringOthersRespondtom2sorder(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_OthersOrder);
}

void CSMS4DCView::FindOthersIniFile(CString *PathINBOX, CString *PathOUTBOX)
{
	CString PathOUTBOX0,PathINBOX0 , OthersIniFile = m_AppPath + _T("\\Texts\\Others.txt");

	CFileFind x1;
	BOOL cx1 = x1.FindFile(OthersIniFile);
	if(!cx1)
	{
		PathINBOX0   = _T("C:\\OTHERS\\INBOX");
		PathOUTBOX0  = _T("C:\\OTHERS\\OUTBOX");

		FILE *fid = fopen(OthersIniFile,_T("wt"));
		fprintf( fid, _T("%s\n"), PathINBOX0);
		fprintf( fid, _T("%s\n"), PathOUTBOX0);
		fclose(fid);
		
	}//if !cx1
	else
	{
		char buftemp[400];
		FILE *fid = fopen(OthersIniFile,_T("rt"));

		fgets(buftemp,400,fid);
		PathINBOX0 = buftemp;		PathINBOX0.TrimLeft();		PathINBOX0.TrimRight();

		fgets(buftemp,400,fid);
		PathOUTBOX0 = buftemp;		PathOUTBOX0.TrimLeft();		PathOUTBOX0.TrimRight();

		fclose(fid);
	}
	x1.Close();
	*PathINBOX  = PathINBOX0;
	*PathOUTBOX = PathOUTBOX0;
}

extern "C" int WINAPI argusO_smsR(HWND hWndParent,CString DBSTR,CString PathIN,CString PathOUT,CString Lang);
void CSMS4DCView::On_othersO_smsR(HWND hwnd) 
{
	bool Is_In = false;
	CString mLang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
	CString PathFileOUTBOX, DBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
    struct _finddata_t xml_file;
    long hFile;

	if(!Is_In)		
	if( (hFile = _findfirst( m_PathOUTBOXothers + _T("\\I*.xml") , &xml_file )) != -1L )	/* Find first .xml file in current directory */
	{
		Is_In = true;
		PathFileOUTBOX = m_PathOUTBOXothers + _T("\\") + xml_file.name;
		argusO_smsR(hwnd, DBSTR, PathFileOUTBOX, m_PathINBOXothers, mLang);
		CFile::Remove(PathFileOUTBOX);
		while( _findnext( hFile, &xml_file ) == 0 )		/* Find the rest of the .xml files */
		{
			PathFileOUTBOX = m_PathOUTBOXothers + _T("\\")  + xml_file.name;
			argusO_smsR(hwnd, DBSTR, PathFileOUTBOX, m_PathINBOXothers, mLang);
			CFile::Remove(PathFileOUTBOX);
		}
	   _findclose( hFile );
		Is_In=false;
	}
}
//------------------Others-------S2M Order-------------------------
//F:\map1\SMS4DC_0\bin\S2MtabDLL.lib
//extern "C" int WINAPI S2M_O_Tab(HWND hWndParent,CString PathINBOX,CString PathOUTBOX ,CString AppPath , CString Lang, CString mDB, CString mTbl);
void CSMS4DCView::OnMonitoringOthersS2morder() 
{
	typedef UINT ( * LPDLLFUNC)(HWND ,CString ,CString  ,CString  , CString , CString , CString );
	HINSTANCE hDLL = LoadLibrary("S2MtabDLL.dll");
	if(hDLL)
	{
		LPDLLFUNC lpfnDllFunc = (LPDLLFUNC)GetProcAddress(hDLL,"S2M_O_Tab");
		if (!lpfnDllFunc)
		{
			CString str;
			str.Format(_Z("\nThe function [ %s ] was not found.\t\n") , "S2M_O_Tab : S2MtabDLL.dll");
			MessageBox(str,  _Z("Error!!!"), MB_ICONERROR | MB_OK);
			FreeLibrary(hDLL);
			return;
		}
		
		CString PathINBOX , PathOUTBOX , mLang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
		FindOthersIniFile(&PathINBOX, &PathOUTBOX);

		lpfnDllFunc(this->m_hWnd, PathINBOX,PathOUTBOX ,m_AppPath, mLang 
			, ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR  , ((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR);	
		
		FreeLibrary(hDLL);
	}
	else
	{
		CString str;
		str.Format(_Z("\nThe file [ %s ] was not found.\t\n") , "S2MtabDLL.dll");
		MessageBox(str,  _Z("Error!!!"), MB_ICONERROR | MB_OK);
	}

//	CString PathINBOX , PathOUTBOX , mLang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
//	FindOthersIniFile(&PathINBOX, &PathOUTBOX);

//	S2M_O_Tab(this->m_hWnd, PathINBOX,PathOUTBOX ,m_AppPath, mLang 
//		, ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR  , ((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR);	
}
//------------------Others-------StatusOrder------------------------
extern "C" int WINAPI SUorder(HWND hWndParent,CString PathINBOX ,CString Lang);
void CSMS4DCView::OnMonitoringOthersOrderstatus() 
{
	CString PathINBOX , PathOUTBOX , mLang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
	FindOthersIniFile(&PathINBOX, &PathOUTBOX);
	SUorder(this->m_hWnd, PathINBOX , mLang);	
}
//------------------Others-------StopOrder----------------------------
extern "C" int WINAPI STorder(HWND hWndParent,CString PathINBOX ,CString Lang ,int ArgusFlag);
void CSMS4DCView::OnMonitoringOthersStoporder() 
{
	CString PathINBOX , PathOUTBOX , mLang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
	FindOthersIniFile(&PathINBOX, &PathOUTBOX);
	STorder(this->m_hWnd, PathINBOX , mLang, 0);	
}
//------------------Others-------Draw Output----------------------------
void CSMS4DCView::OnMonitoringOthersDrawoutput() 
{
	((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Monitoring OTHERS");	
}



void CSMS4DCView::OnPropagationmodelsP18123Area() 
{ 
	CDataBaseLDLG datadlg;
	if (datadlg.DoModal()==IDOK)
	{
		int SelNUM	=	((CSMS4DCApp *)AfxGetApp())->Nrow;
		if(SelNUM==1)
		{
			CString m_Sel	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[0];

			double Lat1, Lon1,Lat2, Lon2,Latst, Lonst;
			Point2LatLon(m_stBoxPoint, &Lat1, &Lon1);	Point2LatLon(m_enBoxPoint, &Lat2, &Lon2);

			CString Namest=GetFld(m_Sel,2);
			Latst=atof(GetFld(m_Sel,3));	Lonst=atof(GetFld(m_Sel,4));

//			if( (Latst>=min(Lat1,Lat2)) && (Latst<=max(Lat1,Lat2)) && (Lonst>=min(Lon1,Lon2)) && (Lonst<=max(Lon1,Lon2)) )
			if(PointInArea(Latst,Lonst, Lat1, Lon1, Lat2, Lon2))
			{
				CP1812DLG p1812dlg;
				if (p1812dlg.DoModal()==IDOK)
				{
					int yst=1200-1-m_stBoxPoint.y;		int yen=1200-1-m_enBoxPoint.y;
					int xst=m_stBoxPoint.x;				int xen=m_enBoxPoint.x;

					int xN    = abs(xst - xen)  ,  yN    = abs(yst - yen) ;
					int xNmin = min(xst , xen)  ,  yNmin = min(yst , yen);
					xN=4*(xN/4);//		xNmin=4*(xNmin/4);

					xN=max(0,min(xN,1200));	yN=max(0,min(yN,1200));

					((CSMS4DCApp *)AfxGetApp())->xN = xN;
					((CSMS4DCApp *)AfxGetApp())->yN = yN;

					((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Area Calculation (P1812)");
					CPro_P1812_AreaDoc *pDocP1812=(CPro_P1812_AreaDoc *)	DocUtil::GetLastDocument("Area Calculation (P1812)");	

					pDocP1812->P1812time        = p1812dlg.m_time;
					pDocP1812->P1812location    = p1812dlg.m_Location;
					pDocP1812->P1812Clutter     = p1812dlg.m_Clutter;
					pDocP1812->P1812Service     = p1812dlg.m_Service;
					pDocP1812->P1812RxH         = p1812dlg.m_RxH;
					pDocP1812->P1812IODoor      = p1812dlg.m_IODoor;
					pDocP1812->P1812Name_ST = Namest;
					pDocP1812->P1812lat_ST  = Latst;
					pDocP1812->P1812lon_ST  = Lonst;
					pDocP1812->P1812Hagl_ST = atof(GetFld(m_Sel,5));
					pDocP1812->P1812fMHz_ST = atof(GetFld(m_Sel,6));
					pDocP1812->P1812PtGt_ST = atof(GetFld(m_Sel,7));
					pDocP1812->P1812AZ_ST = atof(GetFld(m_Sel,8));
					pDocP1812->P1812EL_ST = atof(GetFld(m_Sel,9));
					pDocP1812->P1812ANT_ST = GetFld(m_Sel,14);
					pDocP1812->bufAreaW = xN;
					pDocP1812->bufAreaH = yN;
					pDocP1812->bufAreaP1812 = new _int16[xN*yN];
				
					pDocP1812->P1812Polarization_ST = GetFld(m_Sel,13);

					CSMS4DCDoc* pDoc = GetDocument();
					for (int i=0;i<xN;i++)
						for (int j=0;j<yN;j++)
							pDocP1812->bufAreaP1812[i+xN*j]=pDoc->buf[(yNmin+j)][(xNmin+i)];
/*	//97/12/21
					double xpm = xNmin + 600.0*(pDoc->TileX-1);
					double ypm = yNmin + 600.0*(pDoc->TileY-1);
					double xUTM = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
					double yUTM = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
					yUTM=yUTM-pDoc->m_Resolution_y/2.0;
					xUTM=xUTM-pDoc->m_Resolution_x/2.0;
					pDocP1812->P1812lat0 = yUTM;
					pDocP1812->P1812lon0 = xUTM;
*/
pDocP1812->P1812lat0   = min(Lat1, Lat2);	pDocP1812->P1812lon0   = min(Lon1, Lon2);
pDocP1812->P1812latmax = max(Lat1, Lat2);	pDocP1812->P1812lonmax = max(Lon1, Lon2);

					pDocP1812->TileInfo=pDoc->TileInfo;
					pDocP1812->m_Resolution_x = pDoc->m_Resolution_x;

					double lat1234[4],lon1234[4];
					YX2LatLon(yNmin,xNmin,&lat1234[0],&lon1234[0]);
					YX2LatLon(yNmin,xNmin+(xN-1),&lat1234[1],&lon1234[1]);
					YX2LatLon(yNmin+(yN-1),xNmin+(xN-1),&lat1234[2],&lon1234[2]);
					YX2LatLon(yNmin+(yN-1),xNmin,&lat1234[3],&lon1234[3]);
					pDocP1812->m_AreaTotal = Area_km2(lat1234,lon1234,4);
pDocP1812->TileX = pDoc->TileX;
					pDocP1812->m_ReadyDoc=1;
					pDocP1812->GetData();
					pDocP1812->UpdateAllViews(NULL);
				}//p1812dlg
			}
			else
			{
				CString nst;
				nst.Format(_Z("The selected station '' %s ''  is not inside the selected area."),Namest);
				MessageBox(nst,_Z("!!!  Warning  !!!"));
			}
		}
		else
			MessageBox("\n\t"+_Z("No Station Selected.")+"\t\n",_Z("!!!  Warning  !!!"));
	}//datadlg
///////////////////Close Legend//////////////////////////////
	if(m_LegendFlag)
	{	
		m_pLegendDLGModeless->PostNcDestroy();
		m_LegendFlag=false;
	}
}
void CSMS4DCView::OnUpdatePropagationmodelsP18123Area(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}




double CSMS4DCView::Interp1I(double *E0,double *D0,double E,int num) 
{
	double d1,d2,E1,E2,Db;
	if      (E>E0[0])		{		d1=D0[0];		d2=D0[1];			E1=E0[0];		E2=E0[1];		}
	else if (E<E0[num-1])	{		d1=D0[num-2];	d2=D0[num-1];		E1=E0[num-2];	E2=E0[num-1];	}
	else
	{
		/////////////////////////////////////////////
		int n1=0;
		while(E<=E0[n1])
		{
			n1++;
			if (n1==num)	break;
		}
		if (n1==0)		n1=1;
		d1=D0[n1-1];E1=E0[n1-1];
		///////////////////////////////////////////////
		int n2=num-1;
		while(E>=E0[n2])
		{
			n2--;
			if (n2==0)		break;
		}
		d2=D0[n2+1];E2=E0[n2+1];
		////////////////////////////////////////////////
	}
	Db=((E1==E2) ? d1 : d1*pow(10.0,(log10(d2/d1))*(E-E1)/(E2-E1)) );
	return Db;
}

__declspec(dllimport) double FieldP1546V5(double f_MHz,double t,int p23path,double h1,double dT_km,double dsea_km,
										  double tetamax15_deg, double tetamax16_deg ,double h2, int ENV,
										  int pRX, double ha, int pTX,
										  double Hgt, double Hgr, int srv, double L, BOOL P1546Clangle, BOOL P1546landsea);

double CSMS4DCView::FieldP1546V5_I0(double Latst,double Lonst,double az,double pTX,double h1,
								  double f_MHz,double t , double E,
								  double tetamax15_deg ,double h2, int ENV, double ha,
								  double Hgt, int srv, double L) 
{
	double d1, d2, dk, Eb;
	double Hgi, lati , loni, pRX = pTX, p23path = pTX;

	d1 = 0; d2 = 1000;
	dk = (d1+d2)/2.0;
	reckon(Latst,Lonst, dk, az , &lati  , &loni) ;
	Hgi = LatLon2Hg_n(lati, loni) ;		//98/01/10
	Eb = FieldP1546V5(f_MHz, t, p23path, h1, dk, -999, tetamax15_deg, 0 , h2, ENV, pRX, ha, pTX, Hgt, Hgi, srv, L, 0, 0);

	while(fabs(Eb-E)>0.01)
	{
		if((d2-d1)<0.001)  break;
		if	   (Eb>E)	d1 = dk;
		else if(Eb<E)	d2 = dk;

		dk = (d1+d2)/2.0;
		reckon(Latst,Lonst, dk, az , &lati  , &loni) ;
		Hgi = LatLon2Hg_n(lati, loni) ;		//98/01/10
		Eb = FieldP1546V5(f_MHz, t, p23path, h1, dk, -999, tetamax15_deg, 0 , h2, ENV, pRX, ha, pTX, Hgt, Hgi, srv, L, 0, 0);
	}
	return dk;
/*
	double D0[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000};
	double Db = 0.0, E0[78];

	double dist, Hgi, lati , loni, pRX = pTX, p23path = pTX;

	for(int i=0;i<78;i++)
	{
		dist = D0[i];
		reckon(Latst,Lonst, dist, az , &lati  , &loni) ;
		Hgi = LatLon2Hg(lati, loni) ;
		E0[i] = FieldP1546V5(f_MHz, t, p23path, h1, dist, -999, tetamax15_deg, 0 , h2, ENV, pRX, ha, pTX, Hgt, Hgi, srv, L, 0, 0);
	}
	Db = Interp1I(E0,D0, E,78);
	return Db;
*/
}
double CSMS4DCView::FieldP1546V5_D(double Latst,double Lonst,double az,double pTX, double dist,double h1, double StepRes,
								  double f_MHz,double t ,
								  double tetamax15_deg ,double h2, int ENV, double ha,
								  double Hgt, int srv, double L, BOOL P1546Clangle, BOOL P1546landsea) 
{
	double Hgi, lati , loni, lat15km , lon15km;

	double azI, tetamax16,tetamax16_deg, mdz, dz, hii, rearth = 6371.0;
	double DSea = 0, DseaC, DseaW;
	int pRX = pTX, p23path = pTX;

	reckon(Latst,Lonst, dist, az , &lati  , &loni) ;
	Hgi = LatLon2Hg_n(lati, loni) ;		//98/01/10

	/////////////////////////////////Rx tetamax16_deg /////////////////////////////////////////////
//	if (P1546Clangle==1)     //for Tropospheric scattering(Ets) calculation, P1546-5
	{
		azI=Azimuth_Deg(lati, loni, Latst,Lonst);
		tetamax16 = -pi/2.0;
		mdz = min(dist,16.0);
		dz = 0.0;
		while( dz<= mdz )  //dz=0->16
		{
			dz = dz+StepRes;
			reckon(lati, loni, dz , azI , &lat15km , &lon15km) ;
			hii = LatLon2Hg_n(lat15km, lon15km);		//98/01/10
			tetamax16 = max(tetamax16   ,(((hii-10.0-Hgi)/(dz*1000.0))-(dz/(2.0*rearth))));  //P.1546-5  section 11
		}
		tetamax16_deg = tetamax16*R2D;
	}
	//////////////////////////////////////////////////////////////////////////////
	if (P1546landsea==1)
	{
		DSea = LandWarmColdSea_D_Sea_kmIDWM(Latst,Lonst, lati, loni, &DseaW, &pRX);		DseaC = DSea - DseaW;
										p23path = 1;
		if      (DseaW>0)				p23path = 3;
		else if((DseaW<=0)&&(DseaC>0))	p23path = 2;
	}
	double Eb = FieldP1546V5(f_MHz, t, p23path, h1, dist, DSea, tetamax15_deg,  tetamax16_deg , h2,  ENV,
						  pRX,  ha,  pTX, Hgt,  Hgi,  srv, L, P1546Clangle, P1546landsea);
	return Eb;
}

void CSMS4DCView::OnPropagationmodelsP1546Contour() 
{
	CDataBaseLDLG datadlg;
	if (datadlg.DoModal()==IDOK)
	{
		CString m_Sel	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
		long ID1 = atol(GetFld(m_Sel,1));

		CString Namest = GetFld(m_Sel,2);
		double Latst = atof(GetFld(m_Sel,3));
		double Lonst = atof(GetFld(m_Sel,4));
		OnDatabaseStationsindesktop(ID1,Namest, Latst, Lonst);

		CP1546DLG p1546dlg;
		p1546dlg.m_CvShow = TRUE;
		if (p1546dlg.DoModal()==IDOK)
		{
			double E1 = p1546dlg.m_Cvalue;

			double t = p1546dlg.m_time;
			double Lp = p1546dlg.m_location;
			double P1546k = p1546dlg.m_k;
			double h2 = p1546dlg.m_RxH;
			int syst = p1546dlg.m_syst;
			int ENV = p1546dlg.m_env;
			int P1546Clangle = p1546dlg.m_Clangle;
			double P1546landsea = p1546dlg.m_landsea;

			double Hagl_ST = atof(GetFld(m_Sel,5));
			double f = atof(GetFld(m_Sel,6));
			double PtGt_ST = atof(GetFld(m_Sel,7));
			double AZ0 = atof(GetFld(m_Sel,8));
			double EL0 = atof(GetFld(m_Sel,9));
			CString P1546ANT_ST = GetFld(m_Sel,14);

AZ0 = (pi/180.0)*AZ0;	//931024
EL0 = (pi/180.0)*EL0;	//931024

			int p = LandWarmColdSea(Lonst, Latst);

			double Hg = LatLon2Hg(Latst,Lonst) ;		//98/01/10
			double r = 6371.0, Ghv = 1.0 ,elevp = 0.0;
			double h1, tetamax15 = 0.0, ttca = -999.999;
			double lat3km , lon3km,lat15km ,lon15km, lat015km , lon015km;
			double tetai, mds ,ds, hi, dk, az, E, fp,tp,f1,t1;

//			double Dland,DSea,DseaC,DseaW,ELand,Efs, ESea, delta,E_sea_total,Emix,E_Land_total,deltaE,alpha = 0.3,beta=0.0001,XX;
//			CP1546_Functions CP1546;
			
			double dkL,dkC,dkW;
			double d1,d2,Eb;

			CString antfile;
			antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,P1546ANT_ST);
			int f0[360];	double rH[360]  ,  rV[360];
			ReadAntennaData(antfile,f0,rH,rV) ;

			CString Fname;
			Fname.Format("%sP1546%d%d%d%d%d%d%d%d%d.txt",Namest,(int)Lonst,(int)Latst,abs(E1),(int)t,(int)Lp,(int)h2,(int)(P1546k),syst,ENV);
			CString strFilter = _Z("SMS4DC Vectors")+" (*.txt)|*.txt|"+_Z("Google Files")+" (*.kml)|*.kml||";
			CFileDLG_ChangedType FileDLG(FALSE, NULL, Fname, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , strFilter);
			if (((CSMS4DCApp *)AfxGetApp())->IsWin2000())	FileDLG.m_ofn.lStructSize = 88;		//76
			if (FileDLG.DoModal() == IDOK)
			{
				FILE *fid=fopen(FileDLG.GetPathName(),"wt");
				if(fid)
				{
					CString extFile = FileDLG.GetFileExt();		extFile.MakeUpper();
					CString nameFile = FileDLG.GetFileName();
					nameFile.Delete(nameFile.GetLength()-4,4);
					CString str1,str2,str0;
					if(extFile==_T("KML"))
					{
						CString gifFile = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Image_map\\st.gif");
						str1.Format(_T("<kml>\n<Folder>\n<name>SMS4DC:P1546Contour:%s</name>\n<open>1</open>"),nameFile);
						fprintf(fid,_T("%s\n"),str1);

						str2.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),Namest,gifFile ,Lonst,Latst);
						fprintf(fid,_T("%s \n"),str2);

						str2.Format(_T("<Placemark><name></name><Style><LineStyle><color>FF00FFFF</color><width>1</width></LineStyle></Style><LineString><altitudeMode>relativeToGround</altitudeMode><coordinates>"));
						fprintf(fid,_T("%s \n"),str2);
					}
					CSMS4DCDoc* pDoc = GetDocument();
					double disttest1 = Distance_km(Latst,Lonst, Latst+0, Lonst+pDoc->m_Resolution_x); 
					double disttest2 = Distance_km(Latst,Lonst, Latst+pDoc->m_Resolution_y, Lonst+0);	//97/12/28
				//	double disttest2 = Distance_km(Latst,Lonst, Latst+pDoc->m_Resolution_x, Lonst+0); 
					double StepRes = min(disttest1, disttest2);
					LoadIDWMmap_r(Latst, Lonst, 1000.0);

					int progress_num = 0;
					CString progress_str, progress_char = "|";
					int num = 180;
					for(int i=0;i<=num;i++)
					{
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",100*(++progress_num)/(num+1),progress_char);
						progress_char = str_rep("|",(int)(progress_num*50.0/(num+1)) );
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

						az = i*360.0/num;

						fp = az*D2R;		tp = (pi/2.0) - elevp;
						f1 = R2D*atan2(sin(tp)*sin(fp-AZ0),(cos(EL0)*sin(tp)*cos(fp-AZ0)+cos(tp)*sin(EL0)));
						t1 = R2D*acos(cos(tp)*cos(EL0)-sin(EL0)*sin(tp)*cos(fp-AZ0));
						if (f1<0.0)
							f1=f1+359.4;
						Ghv = Interp2(f0,rH,f1,360) * Interp2(f0,rV,t1,360);

						E = E1 - 10.0*log10(PtGt_ST*Ghv/1650.0);
						/////////////////////////////// h1 (Heff) ///////////////////////////////////////////////
						reckon( Latst,Lonst,  3.0 , az , &lat3km  , &lon3km) ;
						reckon( Latst,Lonst, 15.0 , az , &lat15km , &lon15km) ;
						h1 = Hg + Hagl_ST - Points2HgAvr1(lat3km, lon3km, lat15km ,lon15km);
						///////////////////////////////// tetamax15 /////////////////////////////////////////////
				//		if (h1<0.0)
						{
							tetai = -pi/2.0;
							mds = 15.0;
							ds = 0.0;
							while( ds<= mds )  //ds=0->15
							{
								ds = ds + StepRes;
								reckon( Latst,Lonst, ds , az , &lat015km , &lon015km) ;
								hi = LatLon2Hg_n(lat015km , lon015km) ;		//98/01/10
								tetai = max(tetai   ,(((hi-Hg-Hagl_ST)/(ds*1000.0))-(ds/(2.0*P1546k*r))));
							}
							tetamax15 = R2D*tetai;
						}
						//////////////////////////////////////////////////////////////////////////////
/*
						if (P1546landsea==1)
						{
							dkL = CP1546.P1546_8I(f,t,1,h1,E,h2,ENV,tetamax15,syst,Lp);
							dkC = CP1546.P1546_8I(f,t,2,h1,E,h2,ENV,tetamax15,syst,Lp);
							dkW = CP1546.P1546_8I(f,t,3,h1,E,h2,ENV,tetamax15,syst,Lp);
							dk = max(dkL,max(dkW,dkC));
							reckon( Latst,Lonst,  dk , az , &lat3km  , &lon3km) ;
							DSea = D_Sea_kmIDWM(Latst,Lonst,  lat3km , lon3km, &DseaW);
							Dland = dk - DSea;	DseaC = DSea - DseaW;

							if(dk==Dland)			dk = dkL;
							else if(dk==DseaC)		dk = dkC;
							else if(dk==DseaW)		dk = dkW;
							else
							{
								if (Dland<1.0)
								{
									ELand = CP1546.P1546_8(f,t,1,h1,1.0,h2,ENV,tetamax15,syst,Lp,&Efs);
									ESea = CP1546.P1546_8(f,t,3,h1,1.0,h2,ENV,tetamax15,syst,Lp,&Efs);
									delta = Dland * (ELand - ESea);
								}
								else if (Dland>=1.0)
								{
									ELand = CP1546.P1546_8(f,t,1,h1,Dland,h2,ENV,tetamax15,syst,Lp,&Efs);
									ESea = CP1546.P1546_8(f,t,3,h1,Dland,h2,ENV,tetamax15,syst,Lp,&Efs);
									delta = ELand - ESea;
								}
								E_sea_total = CP1546.P1546_8(f,t,3,h1,dk,h2,ENV,tetamax15,syst,Lp,&Efs);
								Emix = E_sea_total + delta;
								E_Land_total = CP1546.P1546_8(f,t,1,h1,dk,h2,ENV,tetamax15,syst,Lp,&Efs);
								deltaE = Emix - E_Land_total;
								XX = alpha + (1.0 - alpha) * exp(-(beta * pow( Dland , (2.42-0.0003527*h1) ) ));
								Eb = E_Land_total + deltaE * XX;

								while(Eb<E)
								{
									dk = dk-0.1;
									reckon( Latst,Lonst,  dk , az , &lat3km  , &lon3km) ;
									DSea = D_Sea_kmIDWM(Latst,Lonst,  lat3km , lon3km, &DseaW);
									Dland = dk - DSea;	DseaC = DSea - DseaW;

									if (Dland<1.0)
									{
										ELand = CP1546.P1546_8(f,t,1,h1,1.0,h2,ENV,tetamax15,syst,Lp,&Efs);
										ESea = CP1546.P1546_8(f,t,3,h1,1.0,h2,ENV,tetamax15,syst,Lp,&Efs);
										delta = Dland * (ELand - ESea);
									}
									else if (Dland>=1.0)
									{
										ELand = CP1546.P1546_8(f,t,1,h1,Dland,h2,ENV,tetamax15,syst,Lp,&Efs);
										ESea = CP1546.P1546_8(f,t,3,h1,Dland,h2,ENV,tetamax15,syst,Lp,&Efs);
										delta = ELand - ESea;
									}
									E_sea_total = CP1546.P1546_8(f,t,3,h1,dk,h2,ENV,tetamax15,syst,Lp,&Efs);
									Emix = E_sea_total + delta;
									E_Land_total = CP1546.P1546_8(f,t,1,h1,dk,h2,ENV,tetamax15,syst,Lp,&Efs);
									deltaE = Emix - E_Land_total;
									XX = alpha + (1.0 - alpha) * exp(-(beta * pow( Dland , (2.42-0.0003527*h1) ) ));
									Eb = E_Land_total + deltaE * XX;
								}
							}
						}
						else	dk = CP1546.P1546_8I(f,t,p,h1,E,h2,ENV,tetamax15,syst,Lp);
*/
						//Initialize dK 
						dkL = FieldP1546V5_I0(Latst,Lonst, az, 1, h1, f, t, E, tetamax15 , h2, ENV, Hagl_ST, Hg, syst, Lp);
						dkC = FieldP1546V5_I0(Latst,Lonst, az, 2, h1, f, t, E, tetamax15 , h2, ENV, Hagl_ST, Hg, syst, Lp);
						dkW = FieldP1546V5_I0(Latst,Lonst, az, 3, h1, f, t, E, tetamax15 , h2, ENV, Hagl_ST, Hg, syst, Lp);
						dk = max(dkL,max(dkW,dkC));

						Eb = FieldP1546V5_D(Latst,Lonst, az, p, dk, h1,StepRes, f, t, tetamax15 ,h2, ENV, Hagl_ST, Hg, syst, Lp, P1546Clangle, P1546landsea); 
						while(Eb<E)
						{
							dk = dk-1*StepRes;					//97/12/28
					//		dk = dk-1;
							Eb = FieldP1546V5_D(Latst,Lonst, az, p, dk, h1,StepRes, f, t, tetamax15 ,h2, ENV, Hagl_ST, Hg, syst, Lp, P1546Clangle, P1546landsea); 
						}

						d1 = dk-2*StepRes; d2 = dk+2*StepRes;	//97/12/28
					//	d1 = dk-2; d2 = dk+2;
						while(fabs(Eb-E)>0.01)
						{
							if((d2-d1)<0.001)  break;
							if	   (Eb>E)	d1 = dk;
							else if(Eb<E)	d2 = dk;

							dk = (d1+d2)/2.0;
							Eb = FieldP1546V5_D(Latst,Lonst, az, p, dk, h1,StepRes, f, t, tetamax15 ,h2, ENV, Hagl_ST, Hg, syst, Lp, P1546Clangle, P1546landsea); 
						}
						PeekAndPump();

						reckon( Latst,Lonst,  dk , az , &lat3km  , &lon3km) ;
						lon3km = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(lon3km);
						if(extFile==_T("TXT"))	fprintf(fid," %0.14f  %0.14f\n",lon3km,lat3km);
						else if(extFile==_T("KML"))
						{
							str2.Format(_T("%lf,%lf,%lf "),lon3km,lat3km,0.0);
							fprintf(fid,_T("%s \n"),str2);
							if(i==0)	str0 = str2;
						}

					}	//end for

					if(extFile==_T("KML"))
					{
						fprintf(fid,_T("%s \n"),str0);
						str2.Format(_T("</coordinates></LineString></Placemark>"));
						fprintf(fid,_T("%s \n"),str2);
						fprintf(fid,_T("</Folder>\n</kml>"));
					}
					fclose(fid);

					if		(extFile==_T("TXT"))	OnDrawVector(FileDLG.GetPathName()) ;
					else if	((extFile==_T("KML"))&&(FileDLG.m_ShowFlag))	ShellExecute(m_hWnd, "open", FileDLG.GetPathName(), NULL, NULL, SW_SHOWNORMAL);

				}	// end if fid
			}	// end if FileDLG
			
		}	//p1546dlg
		OnDatabaseStationsindesktop(ID1,Namest, Latst, Lonst);		//98/01/10
	}	//	end if datadlg
}

void CSMS4DCView::LoadIDWMmap_r(double lat1_deg,double lon1_deg,double r_km) 
{
	float RLON1 = (float)(lon1_deg*D2R), RLAT1 = (float)(lat1_deg*D2R); 
	long N = 4, IER;	GEOGCMS(&N, &IER );

	long IVAL = 1 , IRANGE = r_km,  NRPNT = 2;
	float  ARRAY[2][2]={RLON1, RLAT1, RLON1, RLAT1};
	GEOGCM( &IVAL, (float *)ARRAY, &IRANGE);
}
double CSMS4DCView::LandWarmColdSea_D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,
									   double *D_SeaW_km, int *p2) 
{
	float RLON1 = (float)(lon1_deg*D2R), RLAT1 = (float)(lat1_deg*D2R), RLON2 = (float)(lon2_deg*D2R), RLAT2 = (float)(lat2_deg*D2R); 

	float RDIST, RAZIM, GC;
	GEOPPDA( &RLON1, &RLAT1, &RLON2, &RLAT2, &RDIST, &RAZIM);

////////////////////
	int WCSea = WarmColdSea(lon2_deg, lat2_deg);
	GEOGCP( &RLON2, &RLAT2, &GC);
	*p2 = 1;
	if		((GC==1)&&(WCSea==0)) *p2=2;	//LandSea = "Coastal Zone : Cold Sea";
	else if ((GC==1)&&(WCSea==1)) *p2=3;	//LandSea = "Coastal Zone : Warm Sea";
//	else if (GC==3)				  *p2=1;	//LandSea = "Coastal Zone : Coastal Land";
//	else if (GC==4)			 	  *p2=1;	//LandSea = "Coastal Zone : Land";
/////////////////////

	float RIDIST[200], CROSVEK[200][2], CNDVEK[200];
	long  MAXCROS=200, CROSS, IREST;
	GEOGCC3( &RLON1, &RLAT1, &RDIST, &RAZIM, &MAXCROS, (float*)CROSVEK, RIDIST, (float*)CNDVEK, &CROSS, &IREST);
	int i;
	float PointVEK[200][2];
	PointVEK[0][0] = RLON1;
	PointVEK[0][1] = RLAT1;
	for (i=1;i<=CROSS;i++)
	{
		PointVEK[i][0] = CROSVEK[i-1][0];
		PointVEK[i][1] = CROSVEK[i-1][1];
	}
	PointVEK[i][0] = RLON2;
	PointVEK[i][1] = RLAT2;

	double latCross,lonCross, Dsea = 0, DseaWarm = 0, DseaCold = 0;
	float dst2p, latCross1,lonCross1, loni0,lati0,loni1,lati1;
	int flag1, flag2, LandSea = 1;

//	if(CNDVEK[i]==1) //"S";  //"Sea";
//	if(CNDVEK[i]==3) //"CL"; //"Coastal Land";
//	if(CNDVEK[i]==4) //"L";  //"Inland Land";

	for(i=0;i<CROSS;i++)
	{
		if(CNDVEK[i]==1)  //"Sea";
		{
			loni0 = PointVEK[i][0];
			lati0 = PointVEK[i][1];
			loni1 = PointVEK[i+1][0];
			lati1 = PointVEK[i+1][1];

			GEODSTR( &loni0, &lati0, &loni1, &lati1, &dst2p);
			Dsea = Dsea + dst2p;

			flag1 = WarmColdSea(loni0*R2D, lati0*R2D);
			flag2 = WarmColdSea(loni1*R2D, lati1*R2D);
			if (flag1!=flag2)
			{
				WarmColdCross(loni0*R2D, lati0*R2D, loni1*R2D, lati1*R2D, &lonCross, &latCross);
				lonCross1 = lonCross*D2R;
				latCross1 = latCross*D2R;
				if(flag1)	GEODSTR( &loni0, &lati0, &lonCross1,&latCross1, &dst2p);
				else		GEODSTR( &loni1, &lati1, &lonCross1,&latCross1, &dst2p);
				DseaWarm = DseaWarm + dst2p;
			}
			else
			{
				if(flag1)	DseaWarm = Dsea;
				else		DseaWarm = 0.0;
			}
		}
		*D_SeaW_km = DseaWarm;
	}
	return Dsea;
}

__declspec(dllimport) double BasicTxLossP1812V3(double* mD, double* mH, int *mZ, long Np, double LatM, double DELTA_N, double N0,
												double pTime, double pLocation, double f, double htg, double hrg, 
												int pol, int srv, int InOutDoor, int zone);

double CSMS4DCView::FieldP1812V3_D(double LatST, double LonST, double dist, double az, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone)
{
	double DELTA_N, N0, LatM, LongM, Lb;		//98/01/06
//	double DELTA_N, N0, lonp, latp, ds, LatM, LongM, Lb;
					
	if((dist<0.25)||(dist<StepRes))	Lb = 92.5  + 20.0*log10(dist * f_GHz);
	else
	{
		reckon(LatST,LonST, dist/2.0, az, &LatM, &LongM) ;
		N0      = dat_filesDATAout(LatM,LongM, dataN050);
		DELTA_N = dat_filesDATAout(LatM,LongM, dataDN50);

		long Np = 2 + (int)(1 + dist/StepRes);
		double *mD  = new double[Np];
		double *mH  = new double[Np];
		int *mZ     = new int[Np+1];

		Np = FieldP1812V3_profile(LatST, LonST, dist, az, StepRes, mD, mH, mZ);	//98/01/06
/*
		Np = 0;		ds = 0.0;
		while(ds<dist)
		{
			reckon(LatST,LonST, ds, az, &latp, &lonp);
			mH[Np] = LatLon2Hg(latp , lonp);
			mD[Np] = ds;
			mZ[Np] = LandSeaCoastal_noMap(lonp, latp);
			Np++;
			ds = ds + StepRes;
		}
		reckon(LatST,LonST, dist, az, &latp, &lonp);
		mH[Np] = LatLon2Hg(latp , lonp);
		mD[Np] = dist;
		mZ[Np] = LandSeaCoastal_noMap(lonp, latp);
		Np++;
		mZ[Np] = 0;
*/

		Lb = BasicTxLossP1812V3(mD, mH, mZ, Np, LatM, DELTA_N, N0,
								pTime, pLocation, f_GHz, Ht, Hr, pol, 
								srv, InOutDoor, zone);
		delete [] mD;	delete [] mH;	delete [] mZ;
	}
	double Eb_1kwERP = 199.36 + 20.0*log10(f_GHz) - Lb;
	return Eb_1kwERP;
}
//98/01/06
double CSMS4DCView::FieldP1812V3_Dn(double LatST, double LonST, double dist, double az, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone,
												int Np, double *mD, double *mH, int *mZ)
{
	double DELTA_N, N0, LatM, LongM, Lb;
					
	if((dist<0.25)||(dist<StepRes))	Lb = 92.5  + 20.0*log10(dist * f_GHz);
	else
	{
		reckon(LatST,LonST, dist/2.0, az, &LatM, &LongM) ;
		N0      = dat_filesDATAout(LatM,LongM, dataN050);
		DELTA_N = dat_filesDATAout(LatM,LongM, dataDN50);

		Lb = BasicTxLossP1812V3(mD, mH, mZ, Np, LatM, DELTA_N, N0,
								pTime, pLocation, f_GHz, Ht, Hr, pol, 
								srv, InOutDoor, zone);
	}
	double Eb_1kwERP = 199.36 + 20.0*log10(f_GHz) - Lb;
	return Eb_1kwERP;
}
//98/01/06
int CSMS4DCView::FieldP1812V3_profile(double LatST, double LonST, double dist, double az, double StepRes,
									   double *mD, double *mH, int *mZ)
{
	double lonp, latp, ds = 0.0;
	int n = 0; 
	while(ds<dist)
	{
		reckon(LatST,LonST, ds, az, &latp, &lonp);
//		mH[n] = LatLon2Hg(latp , lonp);
		mH[n] = LatLon2Hg_n(latp , lonp);	//98/01/07
		mD[n] = ds;
		mZ[n] = LandSeaCoastal_noMap(lonp, latp);
		n++;
		ds = ds + StepRes;
	}
	reckon(LatST,LonST, dist, az, &latp, &lonp);
//	mH[n] = LatLon2Hg(latp , lonp);
	mH[n] = LatLon2Hg_n(latp , lonp);	//98/01/07
	mD[n] = dist;
	mZ[n] = LandSeaCoastal_noMap(lonp, latp);
	n++;
	mZ[n] = 0;
	return n;
}

double CSMS4DCView::FieldP1812V3_D0(double LatST, double LonST, double dist, double az, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone)
{
	double DELTA_N, N0, lonp, latp, ds, LatM, LongM, Lb;
					
	if((dist<0.25)||(dist<StepRes))	Lb = 92.5  + 20.0*log10(dist * f_GHz);
	else
	{
		reckon(LatST,LonST, dist/2.0, az, &LatM, &LongM) ;
		N0      = dat_filesDATAout(LatM,LongM, dataN050);
		DELTA_N = dat_filesDATAout(LatM,LongM, dataDN50);

		long Np = 2 + (int)(1 + dist/StepRes);
		double *mD  = new double[Np];
		double *mH  = new double[Np];
		int *mZ     = new int[Np+1];

		Np = 0;		ds = 0.0;

		mH[Np] = LatLon2Hg(LatST,LonST);
		mD[Np] = ds;
		mZ[Np] = 1;//LandSeaCoastal_noMap(LatST,LonST);;
		Np++;
		ds = ds + StepRes;

		while(ds<dist)
		{
//			reckon(LatST,LonST, ds, az, &latp, &lonp);
			mH[Np] = 0.0;	//LatLon2Hg(latp , lonp);
			mD[Np] = ds;
			mZ[Np] = 1;
			Np++;
			ds = ds + StepRes;
		}
		reckon(LatST,LonST, dist, az, &latp, &lonp);
		mH[Np] = LatLon2Hg(latp , lonp);
		mD[Np] = dist;
		mZ[Np] = 1;//LandSeaCoastal_noMap(lonp, latp);;
		Np++;
		mZ[Np] = 0;

		Lb = BasicTxLossP1812V3(mD, mH, mZ, Np, LatM, DELTA_N, N0,
								pTime, pLocation, f_GHz, Ht, Hr, pol, 
								srv, InOutDoor, zone);
		delete [] mD;	delete [] mH;	delete [] mZ;
	}
	double Eb_1kwERP = 199.36 + 20.0*log10(f_GHz) - Lb;
	return Eb_1kwERP;
}

double CSMS4DCView::FieldP1812V3_I0(double LatST, double LonST, double E, double az, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone)
{
	double d1, d2, dk, Eb;
	d1 = 0; d2 = 1000;
	dk = (d1+d2)/2.0;
	Eb = FieldP1812V3_D0(LatST,LonST, dk, az, StepRes, dataDN50, dataN050, pTime, pLocation, f_GHz, Ht, Hr, pol, srv, InOutDoor, zone);
	while(fabs(Eb-E)>0.01)
	{
		if((d2-d1)<0.001)  break;
		if	   (Eb>E)	d1 = dk;
		else if(Eb<E)	d2 = dk;

		dk = (d1+d2)/2.0;
		Eb = FieldP1812V3_D0(LatST,LonST, dk, az, StepRes, dataDN50, dataN050, pTime, pLocation, f_GHz, Ht, Hr, pol, srv, InOutDoor, zone);
	}
	return dk;
}

int CSMS4DCView::LandSeaCoastal_noMap(double RLON_deg,double RLAT_deg) 
{
	float GC,	RLON = (float)(RLON_deg*D2R),  RLAT = (float)(RLAT_deg*D2R);

	GEOGCP( &RLON, &RLAT, &GC);

	int zone = 3;
	if		(GC==1)		zone = 1;	//LandSea = "Coastal Zone : Sea";
	else if (GC==3)		zone = 2;	//LandSea = "Coastal Zone : Coastal Land";
	else if (GC==4)		zone = 3;	//LandSea = "Coastal Zone : InLand";

	return zone;
}
int CSMS4DCView::dat_filesDATA(CString dat_fname, float data[121][241])
{
	FILE *fp;
	if ((fp = fopen(dat_fname,"r"))==NULL)	return 0;
	fread( data,sizeof(float),121*241, fp );	
	fclose(fp);
	return 1;
}
double CSMS4DCView::dat_filesDATAout(double LatM,double LongM, float data[121][241])
{
	double x,y,h11,h12,h21,h22,LongM1;
	int i1,i2,j1,j2;
	LongM1 = LongM + 360.0*(LongM<0);

	x = LongM1/1.5;			y = (90.0-LatM)/1.5;

	j1 = int(x);	j2 = j1+1;
	i1 = int(y);	i2 = i1+1;

	h11 = data[i1][j1];		h12 = data[i1][j2];
	h21 = data[i2][j1];		h22 = data[i2][j2];

	double hy = h11*(1+i1-y)*(1+j1-x) + h21*(y-i1)*(1+j1-x) + h12*(1+i1-y)*(x-j1) + h22*(y-i1)*(x-j1);
	return hy;
}			
void CSMS4DCView::OnPropagationmodelsP18123Fieldstrengthcontour() 
{
	CDataBaseLDLG datadlg;
	if (datadlg.DoModal()==IDOK)
	{
		CString m_Sel	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
		long ID1 = atol(GetFld(m_Sel,1));

		CString Namest = GetFld(m_Sel,2);
		double Latst = atof(GetFld(m_Sel,3));
		double Lonst = atof(GetFld(m_Sel,4));
		OnDatabaseStationsindesktop(ID1,Namest, Latst, Lonst);

		CP1812DLG p1812dlg;
		p1812dlg.m_CvShow = TRUE;
		if (p1812dlg.DoModal()==IDOK)
		{
			double E1 = p1812dlg.m_Cvalue;

			double t = p1812dlg.m_time;
			double Lp = p1812dlg.m_Location;
			double h2 = p1812dlg.m_RxH;
			int srv = p1812dlg.m_Service;
			int Clutter = p1812dlg.m_Clutter;
			double InOutDoor = p1812dlg.m_IODoor;

			double Hagl_ST = atof(GetFld(m_Sel,5));
			double f = atof(GetFld(m_Sel,6));
			double PtGt_ST = atof(GetFld(m_Sel,7));
			double AZ0 = atof(GetFld(m_Sel,8));
			double EL0 = atof(GetFld(m_Sel,9));
			CString P1546ANT_ST = GetFld(m_Sel,14);

AZ0 = (pi/180.0)*AZ0;	//931024
EL0 = (pi/180.0)*EL0;	//931024

			CString PolarizationTx = GetFld(m_Sel,13);
			int pol = 1;
			if     (PolarizationTx=="H") pol = 0;
			else if(PolarizationTx=="V") pol = 1;

			double Hg = LatLon2Hg(Latst,Lonst) ;
			double r = 6371.0, Ghv = 1.0 ,elevp = 0.0;
			double lat3km , lon3km;
			double dk, az, E, fp,tp,f1,t1;
			
			CString antfile;
			antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,P1546ANT_ST);
			int f0[360];	double rH[360]  ,  rV[360];
			ReadAntennaData(antfile,f0,rH,rV) ;

			CString Fname;
			Fname.Format("%sP1812%d%d%d%d%d%d%d%d%d.txt",Namest,(int)Lonst,(int)Latst,abs(E1),(int)t,(int)Lp,(int)h2,(int)(1),srv,Clutter);
			CString strFilter = _Z("SMS4DC Vectors")+" (*.txt)|*.txt|"+_Z("Google Files")+" (*.kml)|*.kml||";
			CFileDLG_ChangedType FileDLG(FALSE, NULL, Fname, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , strFilter);
			if (((CSMS4DCApp *)AfxGetApp())->IsWin2000())	FileDLG.m_ofn.lStructSize = 88;		//76
			if (FileDLG.DoModal() == IDOK)
			{
				FILE *fid=fopen(FileDLG.GetPathName(),"wt");
				if(fid)
				{
					CString extFile = FileDLG.GetFileExt();		extFile.MakeUpper();
					CString nameFile = FileDLG.GetFileName();
					nameFile.Delete(nameFile.GetLength()-4,4);
					CString str1,str2,str0;
					if(extFile==_T("KML"))
					{
						CString gifFile = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Image_map\\st.gif");
						str1.Format(_T("<kml>\n<Folder>\n<name>SMS4DC:P1546Contour:%s</name>\n<open>1</open>"),nameFile);
						fprintf(fid,_T("%s\n"),str1);

						str2.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),Namest,gifFile ,Lonst,Latst);
						fprintf(fid,_T("%s \n"),str2);

						str2.Format(_T("<Placemark><name></name><Style><LineStyle><color>FF00FFFF</color><width>1</width></LineStyle></Style><LineString><altitudeMode>relativeToGround</altitudeMode><coordinates>"));
						fprintf(fid,_T("%s \n"),str2);
					}
					CSMS4DCDoc* pDoc = GetDocument();
					double disttest1 = Distance_km(Latst,Lonst, Latst+0, Lonst+pDoc->m_Resolution_x); 
					double disttest2 = Distance_km(Latst,Lonst, Latst+pDoc->m_Resolution_y, Lonst+0);	//97/12/28
				//	double disttest2 = Distance_km(Latst,Lonst, Latst+pDoc->m_Resolution_x, Lonst+0);
					double StepRes   = min(disttest1, disttest2);
					LoadIDWMmap_r(Latst, Lonst, 1000.0);

					CString FilepathData = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + "\\Texts\\";
					int status = 0;
					float dataDN50[121][241], dataN050[121][241];
					if( dat_filesDATA(FilepathData + "\\DN50.dat", dataDN50)==0)		status  = 1;
					if( dat_filesDATA(FilepathData + "\\N050.dat", dataN050)==0)		status  = 2;
								
					double d1,d2,Eb;

long Np = 2 + (int)(1 + 1000.0/StepRes);	//98/01/06
double *mD  = new double[Np];
double *mH  = new double[Np];
int    *mZ  = new int[Np+1];

					double f_GHz = f/1000.0;
					int progress_num = 0;
					CString progress_str, progress_char = "|";
					int num = 180;
					for(int i=0;i<=num;i++)
					{
						PeekAndPump();
						progress_str.Format("  %02d%%"+_Z(" complete")+" %s",100*(++progress_num)/(num+1),progress_char);
						progress_char = str_rep("|",(int)(progress_num*50.0/(num+1)) );
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

						az = i*360.0/num;

						fp = az*D2R;		tp = (pi/2.0) - elevp;
						f1 = R2D*atan2(sin(tp)*sin(fp-AZ0),(cos(EL0)*sin(tp)*cos(fp-AZ0)+cos(tp)*sin(EL0)));
						t1 = R2D*acos(cos(tp)*cos(EL0)-sin(EL0)*sin(tp)*cos(fp-AZ0));
						if (f1<0.0)
							f1=f1+359.4;
						Ghv = Interp2(f0,rH,f1,360) * Interp2(f0,rV,t1,360);
						E = E1 - 10.0*log10(PtGt_ST*Ghv/1650.0);

						//Initialize dK 
						dk = FieldP1812V3_I0(Latst,Lonst, E, az, StepRes, dataDN50, dataN050, t, Lp, f_GHz, Hagl_ST, h2, pol, srv, InOutDoor, Clutter);
//98/01/06
Np = FieldP1812V3_profile(Latst,Lonst, dk, az, StepRes, mD, mH, mZ);
mZ[Np] = 0;
Eb = FieldP1812V3_Dn(Latst,Lonst, dk, az, StepRes, dataDN50, dataN050, t, Lp, f_GHz, Hagl_ST, h2, pol, srv, InOutDoor, Clutter, Np, mD, mH, mZ);

while(Eb<E)
{
	dk = dk-1.0*StepRes;
	Np = Np-1;
	mZ[Np] = 0;
	Eb = FieldP1812V3_Dn(Latst,Lonst, dk, az, StepRes, dataDN50, dataN050, t, Lp, f_GHz, Hagl_ST, h2, pol, srv, InOutDoor, Clutter, Np, mD, mH, mZ);
}

/*
						Eb = FieldP1812V3_D(Latst,Lonst, dk, az, StepRes, dataDN50, dataN050, t, Lp, f_GHz, Hagl_ST, h2, pol, srv, InOutDoor, Clutter);
						while(Eb<E)
						{
							dk = dk-1.0*StepRes;					//97/12/28
				//			dk = dk-1;
							Eb = FieldP1812V3_D(Latst,Lonst, dk, az, StepRes, dataDN50, dataN050, t, Lp, f/1000.0, Hagl_ST, h2, pol, srv, InOutDoor, Clutter);
						}
*/
						d1 = dk-2.0*StepRes; d2 = dk+2.0*StepRes;	//97/12/28		//fine tun
				//		d1 = dk-2; d2 = dk+2;
						while(fabs(Eb-E)>0.01)
						{
							if((d2-d1)<0.001)  break;
							if	   (Eb>E)	d1 = dk;
							else if(Eb<E)	d2 = dk;
							dk = (d1+d2)/2.0;
							Eb = FieldP1812V3_D(Latst,Lonst, dk, az, StepRes, dataDN50, dataN050, t, Lp, f_GHz, Hagl_ST, h2, pol, srv, InOutDoor, Clutter);
						}
/*
double	d0 = 0;	
dk = 0;
while(1)
{
	d1 = dk; d2 = 1000;
	dk = (d1+d2)/2.0;
	Eb = FieldP1812V3_D(Latst,Lonst, dk, az, StepRes, dataDN50, dataN050, t, Lp, f_GHz, Hagl_ST, h2, pol, srv, InOutDoor, Clutter);
	while(fabs(Eb-E)>0.01)
	{
		if((d2-d1)<0.001)  break;
		if	   (Eb>E)	d1 = dk;
		else if(Eb<E)	d2 = dk;
		dk = (d1+d2)/2.0;
		Eb = FieldP1812V3_D(Latst,Lonst, dk, az, StepRes, dataDN50, dataN050, t, Lp, f_GHz, Hagl_ST, h2, pol, srv, InOutDoor, Clutter);
	}
	if((dk-d0)>0.001)	d0 = dk;
	else				break;
}
dk = d0;
*/

						reckon( Latst,Lonst,  dk , az , &lat3km  , &lon3km) ;
						lon3km = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(lon3km);
						if(extFile==_T("TXT"))	fprintf(fid," %0.14f  %0.14f\n",lon3km,lat3km);
						else if(extFile==_T("KML"))
						{
							str2.Format(_T("%lf,%lf,%lf "),lon3km,lat3km,0.0);
							fprintf(fid,_T("%s \n"),str2);
							if(i==0)	str0 = str2;
						}

					}	//end for
delete [] mD;	delete [] mH;	delete [] mZ;	//98/01/06

					if(extFile==_T("KML"))
					{
						fprintf(fid,_T("%s \n"),str0);
						str2.Format(_T("</coordinates></LineString></Placemark>"));
						fprintf(fid,_T("%s \n"),str2);
						fprintf(fid,_T("</Folder>\n</kml>"));
					}
					fclose(fid);

					if		(extFile==_T("TXT"))	OnDrawVector(FileDLG.GetPathName()) ;
					else if	((extFile==_T("KML"))&&(FileDLG.m_ShowFlag))	ShellExecute(m_hWnd, "open", FileDLG.GetPathName(), NULL, NULL, SW_SHOWNORMAL);

				}	// end if fid
			}	// end if FileDLG
			
		}	//p1812dlg
		OnDatabaseStationsindesktop(ID1,Namest, Latst, Lonst);		//98/01/10
	}	//	end if datadlg
}

void CSMS4DCView::OnPropagationmodelsP18123Line() 
{
	CDataBaseLDLG datadlg;
	if (datadlg.DoModal()==IDOK)
	{
		int SelNUM	=	((CSMS4DCApp *)AfxGetApp())->Nrow;
		if(SelNUM==1)
		{
			CP1812DLG p1812dlg;
			if (p1812dlg.DoModal()==IDOK)
			{
				CString m_Sel	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[0];

				double Latst=atof(GetFld(m_Sel,3));		double Lonst=atof(GetFld(m_Sel,4));

				CPoint pointst;		LatLon2Point(Latst,Lonst,&pointst);
				long x1=m_stLinePoint.x;
				long y1=1200-1-m_stLinePoint.y;
				long x2=m_enLinePoint.x;
				long y2=1200-1-m_enLinePoint.y;
				long x3=pointst.x;
				long y3=1200-1-pointst.y;

				int xNmin = min(min(x1 , x2) ,x3)-20;
				int yNmin = min(min(y1 , y2) ,y3)-20;
				int xNmax = max(max(x1 , x2) ,x3)+20;
				int yNmax = max(max(y1 , y2) ,y3)+20;
				int xN  = abs(xNmax - xNmin);  
				int yN  = abs(yNmax - yNmin);

				//xN=4*(xN/4);//		xNmin=4*(xNmin/4);
				xN=max(0,min(xN,1200));	yN=max(0,min(yN,1200));

				((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Line Calculation (P1812)");
				CPro_P1812_LineDoc *pDocLine=(CPro_P1812_LineDoc *) DocUtil::GetLastDocument("Line Calculation (P1812)");	

				CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument() ;

				pDocLine->bufAreaW = xN;
				pDocLine->bufAreaH = yN;
				pDocLine->bufAreaP1812 = new _int16[xN*yN];
				for (int i=0;i<xN;i++)
					for (int j=0;j<yN;j++)
						pDocLine->bufAreaP1812[i+xN*j] = pDoc->buf[(yNmin+j)][(xNmin+i)];

				pDocLine->m_NoData = (_int16)(pDoc->m_NoData);
				x1=m_stLinePoint.x;				y1=m_stLinePoint.y;
				x2=m_enLinePoint.x;				y2=m_enLinePoint.y;

				long xmin=min(x1 , x2);				long xmax=max(x1 , x2);
				long xabs=xmax-xmin;
				long ymin=min(y1 , y2);				long ymax=max(y1 , y2);
				long yabs=ymax-ymin;

				int Np =((xabs>=yabs) ? xabs+1 : yabs+1);
				int m_scalfactor = 16;
				Np = (Np-1) * m_scalfactor + 1;

				double *X;		X=new double[Np];
				double *Y;		Y=new double[Np];
				if (xabs>=yabs)
				{
					for (int i=0;i<Np;i++)
					{
						X[i]=((x1<x2) ? x1+(double)i/(double)m_scalfactor : x1-(double)i/(double)m_scalfactor);
						Y[i]=((double)y1+(double)((X[i]-x1)*(y2-y1))/((double)(x2-x1)));
					}
				}
				else
				{
					for (int i=0;i<Np;i++)
					{
						Y[i]=((y1<y2) ? y1+(double)i/(double)m_scalfactor :y1-(double)i/(double)m_scalfactor);
						X[i]=((double)x1+(double)((Y[i]-y1)*(x2-x1))/((double)(y2-y1)));
					}
				}
				double *hi1;		hi1=new double[Np];
				double *hi;			hi= new double[Np];
				double *rng;		rng=new double[Np];
				double *x_en;		x_en=new double[Np];
				double *y_en;		y_en=new double[Np];

				double xps,yps,xpm,ypm;
				pDocLine->Np=Np;
				pDocLine->m_di=new double[Np];
				pDocLine->m_hi=new double[Np];
				pDocLine->m_lati=new double[Np];
				pDocLine->m_loni=new double[Np];
				for ( i=0;i<Np;i++)
				{
					xps=X[i];
					yps=1200.0-1.0-(Y[i]);
					xpm = xps + 600.0*((double)(pDoc->TileX-1));
					ypm = yps + 600.0*((double)(pDoc->TileY-1));
					x_en[i] = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
					y_en[i] = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
					y_en[i] = y_en[i]-pDoc->m_Resolution_y/2.0;
					x_en[i] = x_en[i]-pDoc->m_Resolution_x/2.0;

					CString globeTileInfo = m_AppPath + _T("Texts\\globe.txt");
					if (pDoc->TileInfo != globeTileInfo)
					{
						CUtm m_utm;
						m_utm.y = y_en[i];
						m_utm.x = x_en[i];
						m_utm.UTM2philambda();
						y_en[i]=m_utm.phi;
						x_en[i]=m_utm.lambda;
					}
					hi1[i] = RoundBUF_Hg(xps, yps);
					rng[i] = Distance_km( y_en[0], x_en[0], y_en[i], x_en[i]);
					pDocLine->m_di[i]=rng[i];
					pDocLine->m_lati[i]=y_en[i];
					pDocLine->m_loni[i]=x_en[i];
					pDocLine->m_hi[i]=hi1[i];
				}
				pDocLine->Dmin=rng[0];
				pDocLine->Dmax=rng[Np-1];
				pDocLine->Linetime=p1812dlg.m_time;
				pDocLine->Linelocation=p1812dlg.m_Location;
				pDocLine->LineRxH=p1812dlg.m_RxH;
				pDocLine->LineSrv=p1812dlg.m_Service;
				pDocLine->LineClutter=p1812dlg.m_Clutter;
				pDocLine->LineIODoor=p1812dlg.m_IODoor;
				pDocLine->LineName_ST = GetFld(m_Sel,2);
				pDocLine->Linelat_ST  = atof(GetFld(m_Sel,3));
				pDocLine->Linelon_ST  = atof(GetFld(m_Sel,4));
				pDocLine->LineHagl_ST = atof(GetFld(m_Sel,5));
				pDocLine->LinePtGt_ST  = atof(GetFld(m_Sel,7));
				pDocLine->LineAZ_ST = atof(GetFld(m_Sel,8));
				pDocLine->LineEL_ST = atof(GetFld(m_Sel,9));
				pDocLine->LineANT_ST = GetFld(m_Sel,14);
				pDocLine->LinefMHz_ST = atof(GetFld(m_Sel,6));
				pDocLine->LinePolarizationTx = GetFld(m_Sel,13);

				CPoint m_Point_ST;
				LatLon2Point(atof(GetFld(m_Sel,3)),atof(GetFld(m_Sel,4)), &m_Point_ST) ;
				pDocLine->LineHasl_ST = Point2Hg(m_Point_ST);

				xpm = xNmin + 600.0*(pDoc->TileX-1);
				ypm = yNmin + 600.0*(pDoc->TileY-1);
				double xUTM = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
				double yUTM = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
				yUTM=yUTM-pDoc->m_Resolution_y/2.0;
				xUTM=xUTM-pDoc->m_Resolution_x/2.0;
				pDocLine->Linelat0 = yUTM;
				pDocLine->Linelon0 = xUTM;
				pDocLine->m_Resolution_x = pDoc->m_Resolution_x;
				pDocLine->TileInfo=pDoc->TileInfo;
pDocLine->TileX = pDoc->TileX;
				pDocLine->m_ReadyDoc=1;
				pDocLine->GetData();
				pDocLine->UpdateAllViews(NULL);

				delete [] X;	delete [] Y;	delete [] hi1;	delete [] hi;	delete [] rng; delete [] x_en;		delete [] y_en;
			}
		}
		else
			MessageBox("\n\t"+_Z("No Station Selected.")+"\t\n",_Z("!!!  Warning  !!!"));
	}
}
void CSMS4DCView::OnUpdatePropagationmodelsP18123Line(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stLinePoint != m_enLinePoint ? 1 : 0 );	
}




void CSMS4DCView::OnPropagationmodelsP18123Polyline() 
{
	CDataBaseLDLG datadlg;
	if (datadlg.DoModal()==IDOK)
	{
		CP1812DLG p1812dlg;
		if (p1812dlg.DoModal()==IDOK)
		{
			CString m_Sel	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[0];

			double Latst=atof(GetFld(m_Sel,3));		double Lonst=atof(GetFld(m_Sel,4));
			CPoint pointst;		LatLon2Point(Latst,Lonst,&pointst);

			long x1,y1,x2,y2;
			int xNmin=32767,yNmin=32767,xNmax=-32767,yNmax=-32767;
			for (int k1=0;k1<m_PolyPointNum;k1++)
			{
				x1=m_PolyPoint[k1].x;
				y1=1200-1-m_PolyPoint[k1].y;
				xNmin=min(x1 , xNmin);		xNmax=max(x1 , xNmax);
				yNmin=min(y1 , yNmin);		yNmax=max(y1 , yNmax);
			}
			x2=pointst.x;				y2=1200-1-pointst.y;
			xNmin=min(x2 , xNmin);		xNmax=max(x2 , xNmax);
			yNmin=min(y2 , yNmin);		yNmax=max(y2 , yNmax);
			xNmin=xNmin-20;				yNmin=yNmin-20;
			xNmax=xNmax+20;				yNmax=yNmax+20;

			int xN  = abs(xNmax - xNmin);  	int yN  = abs(yNmax - yNmin);
			xN=max(0,min(xN,1200));	yN=max(0,min(yN,1200));

			((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Polygon Calculation (P1812)");
			CPro_P1812_PolygonDoc *pDocPolygon=(CPro_P1812_PolygonDoc *)	DocUtil::GetLastDocument("Polygon Calculation (P1812)");	

			CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument() ;

			pDocPolygon->bufAreaW = xN;		pDocPolygon->bufAreaH = yN;
			pDocPolygon->bufAreaP1812 = new _int16[xN*yN];
			for (int i=0;i<xN;i++)
				for (int j=0;j<yN;j++)
					pDocPolygon->bufAreaP1812[i+xN*j] = pDoc->buf[(yNmin+j)][(xNmin+i)];

			pDocPolygon->m_NoData = (_int16)(pDoc->m_NoData);

			CPoint m_st,m_en;
			long xmin,xmax,xabs,ymin,ymax,yabs;
			int Np=0,k, *Npt;
			double xps,yps,xpm,ypm;
			
			int m_NPoint=m_PolyPointNum;
			Npt = new int[m_NPoint];

			int m_scalfactor=16;

			pDocPolygon->m_PolyPointNum=m_PolyPointNum;
			pDocPolygon->Npt=new int[m_NPoint];
			for ( k=0;k<m_NPoint-1;k++)
			{
				m_st=m_PolyPoint[k];	m_en=m_PolyPoint[k+1];
				if (m_st != m_en)
				{
					x1=m_st.x;	y1=m_st.y;	x2=m_en.x;	y2=m_en.y;
					xmin=min(x1 , x2);		xmax=max(x1 , x2);		xabs=xmax-xmin;
					ymin=min(y1 , y2);		ymax=max(y1 , y2);		yabs=ymax-ymin;
					Npt[k] = ((xabs>=yabs) ? xabs+1 : yabs+1);
					Npt[k] = (Npt[k]-1) * m_scalfactor + 1;
					Np=Np+Npt[k];
					pDocPolygon->Npt[k]=Npt[k];
				}
			}
			pDocPolygon->Np=Np;
			pDocPolygon->m_di=new double[Np];
			pDocPolygon->m_hi=new double[Np];
			pDocPolygon->m_lati=new double[Np];
			pDocPolygon->m_loni=new double[Np];

			int tt,n1=0;
			double r0=0.0;
			for ( k=0;k<m_NPoint-1;k++)
			{	
				tt=Npt[k];

				double *X;		X=new double[tt];
				double *Y;		Y=new double[tt];
				double *hi;			hi= new double[tt];
				double *rng;		rng=new double[tt];
				double *x_en;		x_en=new double[tt];
				double *y_en;		y_en=new double[tt];
				m_st=m_PolyPoint[k];		m_en=m_PolyPoint[k+1];
				if (m_st != m_en)
				{
					x1=m_st.x;	y1=m_st.y;	x2=m_en.x;	y2=m_en.y;
					xmin=min(x1 , x2);		xmax=max(x1 , x2);		xabs=xmax-xmin;
					ymin=min(y1 , y2);		ymax=max(y1 , y2);		yabs=ymax-ymin;
					if (xabs>=yabs)
					{
						for (i=0;i<Npt[k];i++)
						{	X[i]=((x1<x2) ? x1+(double)i/(double)m_scalfactor : x1-(double)i/(double)m_scalfactor);
							Y[i]=y1+(X[i]-x1)*((double)(y2-y1))/((double)(x2-x1));	
						}
					}
					else
					{
						for (i=0;i<Npt[k];i++)
						{	Y[i]=((y1<y2) ? y1+(double)i/(double)m_scalfactor : y1-(double)i/(double)m_scalfactor);
							X[i]=x1+(Y[i]-y1)*((double)(x2-x1))/((double)(y2-y1));
						}
					}
				}
				double *hi1;		hi1=new double[tt];
				for ( i=0;i<tt;i++)
				{
					xps=X[i];			yps=1200.0-1.0-(Y[i]);
					xpm = xps + 600.0*((double)(pDoc->TileX-1));
					ypm = yps + 600.0*((double)(pDoc->TileY-1));

					x_en[i] = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
					y_en[i] = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
					y_en[i] = y_en[i]-pDoc->m_Resolution_y/2.0;
					x_en[i] = x_en[i]-pDoc->m_Resolution_x/2.0;

					CString globeTileInfo = m_AppPath + _T("Texts\\globe.txt");
					if (pDoc->TileInfo != globeTileInfo)
					{
						CUtm m_utm;
						m_utm.y = y_en[i];
						m_utm.x = x_en[i];
						m_utm.UTM2philambda();
						y_en[i]=m_utm.phi;
						x_en[i]=m_utm.lambda;
					}

					hi1[i] = RoundBUF_Hg(xps, yps);
					rng[i] = Distance_km( y_en[0], x_en[0], y_en[i], x_en[i]);
					pDocPolygon->m_di[n1+i]=r0+rng[i];
					pDocPolygon->m_lati[n1+i]=y_en[i];
					pDocPolygon->m_loni[n1+i]=x_en[i];
					pDocPolygon->m_hi[n1+i]=hi1[i];
				}
				r0=r0+rng[tt-1];
				n1=n1+Npt[k];

				delete [] X;	delete [] Y;	delete [] hi1;	delete [] hi;	delete [] rng; 	delete [] x_en;	delete [] y_en;
			}
			delete [] Npt;
			pDocPolygon->Dmin = pDocPolygon->m_di[0];
			pDocPolygon->Dmax = pDocPolygon->m_di[Np-1];
			pDocPolygon->Linetime=p1812dlg.m_time;
			pDocPolygon->Linelocation=p1812dlg.m_Location;
			pDocPolygon->LineRxH=p1812dlg.m_RxH;
			pDocPolygon->LineSrv=p1812dlg.m_Service;
			pDocPolygon->LineClutter=p1812dlg.m_Clutter;
			pDocPolygon->LineIODoor=p1812dlg.m_IODoor;
			pDocPolygon->LineName_ST = GetFld(m_Sel,2);
			pDocPolygon->Linelat_ST  = Latst;
			pDocPolygon->Linelon_ST  = Lonst;
			pDocPolygon->LineHagl_ST = atof(GetFld(m_Sel,5));
			pDocPolygon->LinePtGt_ST  = atof(GetFld(m_Sel,7));
			pDocPolygon->LineAZ_ST = atof(GetFld(m_Sel,8));
			pDocPolygon->LineEL_ST = atof(GetFld(m_Sel,9));
			pDocPolygon->LineANT_ST = GetFld(m_Sel,14);
			pDocPolygon->LinefMHz_ST = atof(GetFld(m_Sel,6));
			pDocPolygon->LineHasl_ST = Point2Hg(pointst);
			pDocPolygon->LinePolarizationTx = GetFld(m_Sel,13);

			xpm = xNmin + 600.0*(pDoc->TileX-1);
			ypm = yNmin + 600.0*(pDoc->TileY-1);
			double xUTM = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
			double yUTM = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
			yUTM=yUTM-pDoc->m_Resolution_y/2.0;
			xUTM=xUTM-pDoc->m_Resolution_x/2.0;
			pDocPolygon->Linelat0 = yUTM;
			pDocPolygon->Linelon0 = xUTM;
			pDocPolygon->m_Resolution_x = pDoc->m_Resolution_x;
			pDocPolygon->TileInfo=pDoc->TileInfo;
pDocPolygon->TileX = pDoc->TileX;
			pDocPolygon->m_ReadyDoc=1;
			pDocPolygon->GetData();
			pDocPolygon->UpdateAllViews(NULL);
		}
	}
}
void CSMS4DCView::OnUpdatePropagationmodelsP18123Polyline(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_PolyPointNum>1 ? 1 : 0 );	
}

void CSMS4DCView::OnPropagationmodelsP18123Link() 
{
	int datadlg = OnDatabaseStationsindesktop1() ;
	if (datadlg==IDOK)
	{
		CP1812DLG p1812dlg;
		p1812dlg.m_RxShow=FALSE;
		if (p1812dlg.DoModal()==IDOK)
		{
			int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
			if (Nrow==2)
			{
				CString name1[2],m_Sel[2];
				CPoint pointst[2];
				double lat1[2],lon1[2];
				for (int i=0;i<2;i++)
				{
					m_Sel[i] = ((CSMS4DCApp *)AfxGetApp())->m_Sel[i];
					name1[i] = GetFld(m_Sel[i],2);
					lat1[i]  = atof(GetFld(m_Sel[i],3));
					lon1[i]  = atof(GetFld(m_Sel[i],4));
					LatLon2Point(lat1[i],lon1[i],&pointst[i]);
				}
				long x1=pointst[0].x;			long y1=1200-1-pointst[0].y;
				long x2=pointst[1].x;			long y2=1200-1-pointst[1].y;

				int xNmin = (min(x1 , x2) )-20;			int yNmin = (min(y1 , y2) )-20;
				int xNmax = (max(x1 , x2) )+20;			int yNmax = (max(y1 , y2) )+20;
				int xN  = abs(xNmax - xNmin);  			int yN  = abs(yNmax - yNmin);
				xN=max(0,min(xN,1200));	yN=max(0,min(yN,1200));

				((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Link Calculation (P1812)");
				CPro_P1812_LinkDoc *pDocLinkP1812=(CPro_P1812_LinkDoc *) DocUtil::GetLastDocument("Link Calculation (P1812)");

				CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument() ;

				pDocLinkP1812->bufAreaW = xN;		pDocLinkP1812->bufAreaH = yN;
				pDocLinkP1812->bufAreaP1812 = new _int16[xN*yN];
				for ( i=0;i<xN;i++)
					for (int j=0;j<yN;j++)
						pDocLinkP1812->bufAreaP1812[i+xN*j] = pDoc->buf[(yNmin+j)][(xNmin+i)];

				pDocLinkP1812->m_NoData = (_int16)(pDoc->m_NoData);

				x1=pointst[0].x;		y1=pointst[0].y;
				x2=pointst[1].x;		y2=pointst[1].y;

				long xmin=min(x1 , x2);			long xmax=max(x1 , x2);
				long xabs=xmax-xmin;
				long ymin=min(y1 , y2);			long ymax=max(y1 , y2);
				long yabs=ymax-ymin;

				int Np =((xabs>=yabs) ? xabs+1 : yabs+1);
				int m_scalfactor=16;
				Np = (Np-1) * m_scalfactor + 1;

				double *X;		X=new double[Np];
				double *Y;		Y=new double[Np];
				if (xabs>=yabs)
				{
					for (int i=0;i<Np;i++)
					{
						X[i]=((x1<x2) ? x1+(double)i/(double)m_scalfactor : x1-(double)i/(double)m_scalfactor);
						Y[i]=((double)y1+(double)((X[i]-x1)*(y2-y1))/((double)(x2-x1)));
					}
				}
				else
				{
					for (int i=0;i<Np;i++)
					{
						Y[i]=((y1<y2) ? y1+(double)i/(double)m_scalfactor :y1-(double)i/(double)m_scalfactor);
						X[i]=((double)x1+(double)((Y[i]-y1)*(x2-x1))/((double)(y2-y1)));
					}
				}
				double *hi;			hi= new double[Np];
				double *rng;		rng=new double[Np];
				double *x_en;		x_en=new double[Np];
				double *y_en;		y_en=new double[Np];

				double xps,yps,xpm,ypm;
				pDocLinkP1812->Np=Np;
				pDocLinkP1812->m_di=new double[Np];
				pDocLinkP1812->m_hi=new double[Np];
				pDocLinkP1812->m_lati=new double[Np];
				pDocLinkP1812->m_loni=new double[Np];
				double *hi1;		hi1=new double[Np];

				double Hmin=32767.0;
				for ( i=0;i<Np;i++)
				{
					xps=X[i];			yps=1200.0-1.0-(Y[i]);
					xpm = xps + 600.0*((double)(pDoc->TileX-1));
					ypm = yps + 600.0*((double)(pDoc->TileY-1));

					x_en[i] = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
					y_en[i] = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
					y_en[i] = y_en[i]-pDoc->m_Resolution_y/2.0;
					x_en[i] = x_en[i]-pDoc->m_Resolution_x/2.0;

					CString globeTileInfo = m_AppPath + _T("Texts\\globe.txt");
					if (pDoc->TileInfo != globeTileInfo)
					{
						CUtm m_utm;
						m_utm.y = y_en[i];
						m_utm.x = x_en[i];
						m_utm.UTM2philambda();
						y_en[i]=m_utm.phi;
						x_en[i]=m_utm.lambda;
					}
					hi1[i] = RoundBUF_Hg(xps, yps);
					rng[i] = Distance_km( y_en[0], x_en[0], y_en[i], x_en[i]);
					pDocLinkP1812->m_di[i]=rng[i];
					pDocLinkP1812->m_lati[i]=y_en[i];
					pDocLinkP1812->m_loni[i]=x_en[i];
					pDocLinkP1812->m_hi[i]=hi1[i];
					Hmin=min(Hmin,hi1[i]);
				}
				pDocLinkP1812->Hmin=Hmin;
				pDocLinkP1812->Dmin=rng[0];
				pDocLinkP1812->Dmax=rng[Np-1];
				pDocLinkP1812->m_DrawFresnel = true;
				pDocLinkP1812->m_Gt = atof(GetFld(m_Sel[0],10));
				pDocLinkP1812->m_Gr = atof(GetFld(m_Sel[1],10));
				pDocLinkP1812->LinkRxH = atof(GetFld(m_Sel[1],5));
				pDocLinkP1812->LinkName_Rx = name1[1];
				pDocLinkP1812->Linklat_Rx  = lat1[1];
				pDocLinkP1812->Linklon_Rx  = lon1[1];
				pDocLinkP1812->Linktime=p1812dlg.m_time;
				pDocLinkP1812->Linklocation=p1812dlg.m_Location;
			//	pDocLinkP1812->Linkk=p1812dlg.m_k;
				pDocLinkP1812->LinkSrv=p1812dlg.m_Service;
				pDocLinkP1812->LinkClutter=p1812dlg.m_Clutter;
				pDocLinkP1812->LinkIODoor=p1812dlg.m_IODoor;
			//	pDocLinkP1812->Linklandsea=p1812dlg.m_landsea;
				pDocLinkP1812->LinkName_ST = name1[0];
				pDocLinkP1812->Linklat_ST  = lat1[0];
				pDocLinkP1812->Linklon_ST  = lon1[0];
				pDocLinkP1812->LinkHagl_ST = atof(GetFld(m_Sel[0],5));
				pDocLinkP1812->LinkPtGt_ST  = atof(GetFld(m_Sel[0],7));
				pDocLinkP1812->LinkAZ_ST = atof(GetFld(m_Sel[0],8));
				pDocLinkP1812->LinkEL_ST = atof(GetFld(m_Sel[0],9));
				pDocLinkP1812->LinkANT_ST = GetFld(m_Sel[0],14);
				pDocLinkP1812->LinkfMHz_ST = atof(GetFld(m_Sel[0],6));
				pDocLinkP1812->LinkPolarizationTx = GetFld(m_Sel[0],13);

				CPoint m_Point_ST;
				LatLon2Point(atof(GetFld(m_Sel[0],3)),atof(GetFld(m_Sel[0],4)), &m_Point_ST) ;
				pDocLinkP1812->LinkHasl_ST = Point2Hg(m_Point_ST);

				xpm = xNmin + 600.0*(pDoc->TileX-1);
				ypm = yNmin + 600.0*(pDoc->TileY-1);
				double xUTM = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
				double yUTM = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
				yUTM=yUTM-pDoc->m_Resolution_y/2.0;
				xUTM=xUTM-pDoc->m_Resolution_x/2.0;
				pDocLinkP1812->Linklat0 = yUTM;
				pDocLinkP1812->Linklon0 = xUTM;
				pDocLinkP1812->m_Resolution_x = pDoc->m_Resolution_x;
				pDocLinkP1812->TileInfo=pDoc->TileInfo;
				
				int Ierror = pDocLinkP1812->GetData();
				pDocLinkP1812->m_ReadyDoc=1;
				pDocLinkP1812->UpdateAllViews(NULL);
				if(Ierror==1)pDocLinkP1812->MissingAntena() ; 

				delete [] X;	delete [] Y;	delete [] hi1;	delete [] hi;	delete [] rng; 	delete [] x_en;	delete [] y_en;
			}
		}//p1812dlg
	}//datadlg	
}


void CSMS4DCView::OnPropagationmodelsP18123NetworkprocessorMaximumfieldstrength()	//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF = 0;
	OnPropagationmodelsP18123NPMFS();
}
void CSMS4DCView::OnUpdatePropagationmodelsP18123NetworkprocessorMaximumFS(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningRxMfsP18123()  						//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF = 1;
	OnPropagationmodelsP18123NPMFS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningRxMfsP18123(CCmdUI* pCmdUI)		//98/12/17 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}
void CSMS4DCView::OnMonitoringNetworkplanningLocationzoneaoaP18123() 				//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF = 2;
	OnPropagationmodelsP18123NPMFS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningLocationzoneaoaP18123(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnPropagationmodelsP18123NPMFS() 
{
	CDataBaseLDLG datadlg;

if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF > 0)		//990428
{
	datadlg.m_Title = _Z("Select Monitoring Stations");
	if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF == 2)	//Monitoring  AoA
		datadlg.m_Title = datadlg.m_Title + " > 1";
}

	if (datadlg.DoModal()==IDOK)
	{
		int Nrow	=	((CSMS4DCApp *)AfxGetApp())->Nrow;
		CString *m_Sel;			m_Sel=new CString[Nrow];
		CString *Namest;		Namest=new CString[Nrow];
		double *Latst;			Latst=new double[Nrow];
		double *Lonst;			Lonst=new double[Nrow];
//		double Latst_min=200.0,Lonst_min=200.0,Latst_max=-200.0,Lonst_max=-200.0;
		double Lat1, Lon1,Lat2, Lon2;
		Point2LatLon(m_stBoxPoint, &Lat1, &Lon1);		Point2LatLon(m_enBoxPoint, &Lat2, &Lon2);
int uflag = 1;
		for (int i1=0;i1<Nrow;i1++)
		{
			m_Sel[i1]	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[i1];
			Namest[i1] = GetFld(m_Sel[i1],2);
			Latst[i1] = atof(GetFld(m_Sel[i1],3));
			Lonst[i1] = atof(GetFld(m_Sel[i1],4));
//			Latst_min=min(Latst_min,Latst[i1]);		Latst_max=max(Latst_max,Latst[i1]);
//			Lonst_min=min(Lonst_min,Lonst[i1]);		Lonst_max=max(Lonst_max,Lonst[i1]);
uflag = uflag*PointInArea(Latst[i1],Lonst[i1], Lat1, Lon1, Lat2, Lon2);
		}
//		double Lat1, Lon1,Lat2, Lon2;
//		Point2LatLon(m_stBoxPoint, &Lat1, &Lon1);		Point2LatLon(m_enBoxPoint, &Lat2, &Lon2);
//		if( (Latst_min>=min(Lat1,Lat2)) && (Latst_max<=max(Lat1,Lat2)) && (Lonst_min>=min(Lon1,Lon2)) && (Lonst_max<=max(Lon1,Lon2)) )
		if(uflag)
		{
			CP1812DLG p1812dlg;

if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF > 0)	//990428
{
	p1812dlg.m_Monitoring = true;
	p1812dlg.m_Cvalue = 10;	//	Tx W
	p1812dlg.m_RxH = 20;	//	Tx m
}
			if (p1812dlg.DoModal()==IDOK)
			{
				int yst=1200-1-m_stBoxPoint.y;		int yen=1200-1-m_enBoxPoint.y;
				int xst=m_stBoxPoint.x;				int xen=m_enBoxPoint.x;
				int xN    = abs(xst - xen)  ,  yN    = abs(yst - yen) ;
				int xNmin = min(xst , xen)  ,  yNmin = min(yst , yen);
				xN=4*(xN/4);//		xNmin=4*(xNmin/4);

				xN=max(0,min(xN,1200));	yN=max(0,min(yN,1200));
				((CSMS4DCApp *)AfxGetApp())->xN = xN;
				((CSMS4DCApp *)AfxGetApp())->yN = yN;

				((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Maximum Field Strength (P1812)");
				CPro_P1812_NetFDoc *pDocP1812=(CPro_P1812_NetFDoc *)	DocUtil::GetLastDocument("Maximum Field Strength (P1812)");	

CString Title_En  = "Maximum Field Strength";			//Maximum Field Strength
CString Title_Num = pDocP1812->GetTitle();		Title_Num.Replace(Title_En,"");

//Monitoring	98/12/17
	if     (((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF == 1)	Title_En  = "Monitoring Rx Coverage(MFS)";	//Monitoring Rx Coverage
	else if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF == 2)	Title_En  = "Location Zone AoA";			//Monitoring  AoA

pDocP1812->SetTitle(_T(Title_En) + Title_Num);		//pDocP1812->SetTitle(_Z(Title_En) + Title_Num);

				pDocP1812->P1812time=p1812dlg.m_time;
				pDocP1812->P1812location=p1812dlg.m_Location;
				pDocP1812->P1812RxH=p1812dlg.m_RxH;
				pDocP1812->P1812Service=p1812dlg.m_Service;
				pDocP1812->P1812Clutter=p1812dlg.m_Clutter;
				pDocP1812->P1812IODoor = p1812dlg.m_IODoor;
				pDocP1812->Nrow = Nrow;
				pDocP1812->P1812lat_ST=new double[Nrow];
				pDocP1812->P1812lon_ST=new double[Nrow];
				pDocP1812->P1812Hagl_ST=new double[Nrow];
				pDocP1812->P1812fGHz_ST=new double[Nrow];
				pDocP1812->P1812PtGt_ST=new double[Nrow];
				pDocP1812->P1812Name_ST=new CString[Nrow];
				pDocP1812->P1812AZ_ST=new double[Nrow];
				pDocP1812->P1812EL_ST=new double[Nrow];
				pDocP1812->P1812ANT_ST=new CString[Nrow];
				pDocP1812->P1812iPolarization_ST=new int[Nrow];
				for (int i1=0;i1<Nrow;i1++)
				{
					pDocP1812->P1812Name_ST[i1] = Namest[i1];
					pDocP1812->P1812lat_ST[i1]  = Latst[i1];
					pDocP1812->P1812lon_ST[i1]  = Lonst[i1];
					pDocP1812->P1812Hagl_ST[i1] = atof(GetFld(m_Sel[i1],5));
					pDocP1812->P1812fGHz_ST[i1] = atof(GetFld(m_Sel[i1],6))/1000.0;
					pDocP1812->P1812PtGt_ST[i1] = atof(GetFld(m_Sel[i1],7));
					pDocP1812->P1812AZ_ST[i1] = atof(GetFld(m_Sel[i1],8));
					pDocP1812->P1812EL_ST[i1] = atof(GetFld(m_Sel[i1],9));
					pDocP1812->P1812ANT_ST[i1] = GetFld(m_Sel[i1],14);

					CString pol = GetFld(m_Sel[i1],13);
					pDocP1812->P1812iPolarization_ST[i1] = 1;
					if     (pol=="H") pDocP1812->P1812iPolarization_ST[i1] = 0;
					else if(pol=="V") pDocP1812->P1812iPolarization_ST[i1] = 1;
				}

if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetF > 0)	//990428
	pDocP1812->P1812PtGt_ST[0] = p1812dlg.m_Cvalue;

				pDocP1812->bufAreaW = xN;				pDocP1812->bufAreaH = yN;
				pDocP1812->bufAreaP1812 = new _int16[xN*yN];

				CSMS4DCDoc* pDoc = GetDocument();
				for (int i=0;i<xN;i++)
					for (int j=0;j<yN;j++)
						pDocP1812->bufAreaP1812[i+xN*j]=pDoc->buf[(yNmin+j)][(xNmin+i)];
/*	//97/12/21
				double xpm = xNmin + 600.0*(pDoc->TileX-1);
				double ypm = yNmin + 600.0*(pDoc->TileY-1);
				double xUTM = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
				double yUTM = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
				yUTM=yUTM-pDoc->m_Resolution_y/2.0;
				xUTM=xUTM-pDoc->m_Resolution_x/2.0;
				pDocP1812->P1812lat0 = yUTM;
				pDocP1812->P1812lon0 = xUTM;
*/
pDocP1812->P1812lat0   = min(Lat1, Lat2);	pDocP1812->P1812lon0   = min(Lon1, Lon2);
pDocP1812->P1812latmax = max(Lat1, Lat2);	pDocP1812->P1812lonmax = max(Lon1, Lon2);

				pDocP1812->TileInfo=pDoc->TileInfo;
				pDocP1812->m_Resolution_x = pDoc->m_Resolution_x;

				double lat1234[4],lon1234[4];
				YX2LatLon(yNmin,xNmin,&lat1234[0],&lon1234[0]);
				YX2LatLon(yNmin,xNmin+(xN-1),&lat1234[1],&lon1234[1]);
				YX2LatLon(yNmin+(yN-1),xNmin+(xN-1),&lat1234[2],&lon1234[2]);
				YX2LatLon(yNmin+(yN-1),xNmin,&lat1234[3],&lon1234[3]);
				pDocP1812->m_AreaTotal = Area_km2(lat1234,lon1234,4);
pDocP1812->TileX = pDoc->TileX;				
				pDocP1812->m_ReadyDoc=1;
				pDocP1812->GetData();
				pDocP1812->UpdateAllViews(NULL);
			}//p1812dlg
		}
		else
		{
			CString NamestOut;
			for(int t1=0;t1<Nrow;t1++)
			{
//				if((Latst[t1]<min(Lat1,Lat2))||(Latst[t1]>max(Lat1,Lat2))||(Lonst[t1]<min(Lon1,Lon2))||(Lonst[t1]>max(Lon1,Lon2)))
				if(!PointInArea(Latst[t1],Lonst[t1], Lat1, Lon1, Lat2, Lon2))
					NamestOut = NamestOut +_T(",")+ Namest[t1];
			}
			NamestOut.Delete(0);
			CString nst;
			nst.Format(_Z("The selected station(s) '' %s ''  is(are) not inside the selected area."),NamestOut);
			MessageBox(nst,_Z("!!!  Warning  !!!"));
		}
	}//datadlg
///////////////////Close Legend//////////////////////////////
	if(m_LegendFlag)
	{	
		m_pLegendDLGModeless->PostNcDestroy();
		m_LegendFlag=false;
	}
}



void CSMS4DCView::OnPropagationmodelsP18123NetworkprocessorBestserver()						//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB = 0;
	OnPropagationmodelsP18123NPBS();
}
void CSMS4DCView::OnUpdatePropagationmodelsP18123NetworkprocessorBestserver(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningRxBsP18123() 									//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB = 1;
	OnPropagationmodelsP18123NPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningRxBsP18123(CCmdUI* pCmdUI)				//98/12/17
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningCoveragezonesP18123() 							//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB = 2;
	OnPropagationmodelsP18123NPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningCoveragezonesP18123(CCmdUI* pCmdUI)		//98/12/17
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}
void CSMS4DCView::OnMonitoringNetworkplanningLocationzonetdoaP18123() 						//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB = 3;
	OnPropagationmodelsP18123NPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningLocationzonetdoaP18123(CCmdUI* pCmdUI) //98/12/17
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnPropagationmodelsP18123NPBS()											//98/12/17
{
	CDataBaseLDLG datadlg;

if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB > 0)		//990428
{
	datadlg.m_Title = _Z("Select Monitoring Stations");
	if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB == 3)	//Monitoring  TDoA
		datadlg.m_Title = datadlg.m_Title + " > 2";
}

	if (datadlg.DoModal()==IDOK)
	{
		int Nrow	=	((CSMS4DCApp *)AfxGetApp())->Nrow;
		CString *m_Sel;			m_Sel=new CString[Nrow];
		CString *Namest;		Namest=new CString[Nrow];
		double *Latst;			Latst=new double[Nrow];
		double *Lonst;			Lonst=new double[Nrow];
//		double Latst_min=200.0,Lonst_min=200.0,Latst_max=-200.0,Lonst_max=-200.0;
		double Lat1, Lon1,Lat2, Lon2;
		Point2LatLon(m_stBoxPoint, &Lat1, &Lon1) ;		Point2LatLon(m_enBoxPoint, &Lat2, &Lon2) ;
int uflag = 1;
		for (int i1=0;i1<Nrow;i1++)
		{
			m_Sel[i1]	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[i1];
			Namest[i1] = GetFld(m_Sel[i1],2);
			Latst[i1] = atof(GetFld(m_Sel[i1],3));
			Lonst[i1] = atof(GetFld(m_Sel[i1],4));
	//		Latst_min=min(Latst_min,Latst[i1]);			Latst_max=max(Latst_max,Latst[i1]);
	//		Lonst_min=min(Lonst_min,Lonst[i1]);			Lonst_max=max(Lonst_max,Lonst[i1]);
uflag = uflag*PointInArea(Latst[i1],Lonst[i1], Lat1, Lon1, Lat2, Lon2);
		}
//		double Lat1, Lon1,Lat2, Lon2;
//		Point2LatLon(m_stBoxPoint, &Lat1, &Lon1) ;		Point2LatLon(m_enBoxPoint, &Lat2, &Lon2) ;
//		if( (Latst_min>=min(Lat1,Lat2)) && (Latst_max<=max(Lat1,Lat2)) && (Lonst_min>=min(Lon1,Lon2)) && (Lonst_max<=max(Lon1,Lon2)) )
		if(uflag)		
		{
			CP1812DLG p1812dlg;

if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB > 0)	//990428
{
	p1812dlg.m_Monitoring = true;
	p1812dlg.m_Cvalue = 10;	//	Tx W
	p1812dlg.m_RxH = 20;	//	Tx m
}
			if (p1812dlg.DoModal()==IDOK)
			{
				int yst=1200-1-m_stBoxPoint.y;		int yen=1200-1-m_enBoxPoint.y;
				int xst=m_stBoxPoint.x;				int xen=m_enBoxPoint.x;
				int xN    = abs(xst - xen)  ,  yN    = abs(yst - yen) ;
				int xNmin = min(xst , xen)  ,  yNmin = min(yst , yen);
				xN=4*(xN/4);//		xNmin=4*(xNmin/4);

				xN=max(0,min(xN,1200));	yN=max(0,min(yN,1200));
				((CSMS4DCApp *)AfxGetApp())->xN = xN;
				((CSMS4DCApp *)AfxGetApp())->yN = yN;

				((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Best Server (P1812)");
				CPro_P1812_NetBDoc *pDocP1812=(CPro_P1812_NetBDoc *)	DocUtil::GetLastDocument("Best Server (P1812)");	

CString Title_En  = "Best Server";			//Best Server
CString Title_Num = pDocP1812->GetTitle();		Title_Num.Replace(Title_En,"");

//Monitoring	98/12/17
	if     (((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB == 1)	Title_En  = "Monitoring Rx Coverage(BS)";	//Monitoring Rx Coverage
	else if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB == 2)	Title_En  = "Coverage Zones";				//Monitoring coverage zones
	else if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB == 3)	Title_En  = "Location Zone TDoA";			//Monitoring  TDoA

pDocP1812->SetTitle(_T(Title_En) + Title_Num);		//pDocP1812->SetTitle(_Z(Title_En) + Title_Num);

				pDocP1812->P1812time=p1812dlg.m_time;
				pDocP1812->P1812location=p1812dlg.m_Location;
				pDocP1812->P1812RxH=p1812dlg.m_RxH;
				pDocP1812->P1812Service=p1812dlg.m_Service;
				pDocP1812->P1812Clutter=p1812dlg.m_Clutter;
				pDocP1812->P1812IODoor = p1812dlg.m_IODoor;
				pDocP1812->Nrow = Nrow;
				pDocP1812->P1812lat_ST=new double[Nrow];
				pDocP1812->P1812lon_ST=new double[Nrow];
				pDocP1812->P1812Hagl_ST=new double[Nrow];
				pDocP1812->P1812fGHz_ST=new double[Nrow];
				pDocP1812->P1812PtGt_ST=new double[Nrow];
				pDocP1812->P1812Name_ST=new CString[Nrow];
				pDocP1812->P1812AZ_ST=new double[Nrow];
				pDocP1812->P1812EL_ST=new double[Nrow];
				pDocP1812->P1812ANT_ST=new CString[Nrow];
				pDocP1812->P1812iPolarization_ST=new int[Nrow];
				for (int i1=0;i1<Nrow;i1++)
				{
					pDocP1812->P1812Name_ST[i1] = Namest[i1];
					pDocP1812->P1812lat_ST[i1]  = Latst[i1];
					pDocP1812->P1812lon_ST[i1]  = Lonst[i1];
					pDocP1812->P1812Hagl_ST[i1] = atof(GetFld(m_Sel[i1],5));
					pDocP1812->P1812fGHz_ST[i1] = atof(GetFld(m_Sel[i1],6))/1000.0;
					pDocP1812->P1812PtGt_ST[i1] = atof(GetFld(m_Sel[i1],7));
					pDocP1812->P1812AZ_ST[i1] = atof(GetFld(m_Sel[i1],8));
					pDocP1812->P1812EL_ST[i1] = atof(GetFld(m_Sel[i1],9));
					pDocP1812->P1812ANT_ST[i1] = GetFld(m_Sel[i1],14);

					CString pol = GetFld(m_Sel[i1],13);
					pDocP1812->P1812iPolarization_ST[i1] = 1;
					if     (pol=="H") pDocP1812->P1812iPolarization_ST[i1] = 0;
					else if(pol=="V") pDocP1812->P1812iPolarization_ST[i1] = 1;
				}

if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1812NetB > 0)	//990428
	pDocP1812->P1812PtGt_ST[0] = p1812dlg.m_Cvalue;

				pDocP1812->bufAreaW = xN;
				pDocP1812->bufAreaH = yN;
				pDocP1812->bufAreaP1812 = new _int16[xN*yN];

				CSMS4DCDoc* pDoc = GetDocument();
				for (int i=0;i<xN;i++)
					for (int j=0;j<yN;j++)
						pDocP1812->bufAreaP1812[i+xN*j]=pDoc->buf[(yNmin+j)][(xNmin+i)];
/*	//97/12/21
				double xpm = xNmin + 600.0*(pDoc->TileX-1);
				double ypm = yNmin + 600.0*(pDoc->TileY-1);
				double xUTM = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
				double yUTM = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
				yUTM=yUTM-pDoc->m_Resolution_y/2.0;
				xUTM=xUTM-pDoc->m_Resolution_x/2.0;
				pDocP1812->P1812lat0 = yUTM;
				pDocP1812->P1812lon0 = xUTM;
*/
pDocP1812->P1812lat0   = min(Lat1, Lat2);	pDocP1812->P1812lon0   = min(Lon1, Lon2);
pDocP1812->P1812latmax = max(Lat1, Lat2);	pDocP1812->P1812lonmax = max(Lon1, Lon2);

				pDocP1812->TileInfo=pDoc->TileInfo;
				pDocP1812->m_Resolution_x = pDoc->m_Resolution_x;
pDocP1812->TileX = pDoc->TileX;
				pDocP1812->m_ReadyDoc=1;
				pDocP1812->GetData();
				pDocP1812->UpdateAllViews(NULL);
			}//p1812dlg
		}
		else
		{
			CString NamestOut;
			for(int t1=0;t1<Nrow;t1++)
			{
//				if((Latst[t1]<min(Lat1,Lat2))||(Latst[t1]>max(Lat1,Lat2))||(Lonst[t1]<min(Lon1,Lon2))||(Lonst[t1]>max(Lon1,Lon2)))
				if(!PointInArea(Latst[t1],Lonst[t1], Lat1, Lon1, Lat2, Lon2))
					NamestOut = NamestOut +_T(",")+ Namest[t1];
			}
			NamestOut.Delete(0);
			CString nst;
			nst.Format(_Z("The selected station(s) '' %s ''  is(are) not inside the selected area."),NamestOut);
			MessageBox(nst,_Z("!!!  Warning  !!!"));
		}
	}//datadlg
///////////////////Close Legend//////////////////////////////
	if(m_LegendFlag)
	{	
		m_pLegendDLGModeless->PostNcDestroy();
		m_LegendFlag=false;
	}	
}


CString CSMS4DCView::LandSeaCoastal_C(double RLON_deg,double RLAT_deg) 
{
//	double pi=4.0*atan(1.0);
	float RLON = (float)(RLON_deg*pi/180.0);
	float RLAT = (float)(RLAT_deg*pi/180.0);

	long int N=4, IER;
	GEOGCMS ( &N, &IER );

	float RLON1 = (float)(RLON-pi/90.0), RLAT1 = (float)(RLAT-pi/90.0),
		  RLON2 = (float)(RLON+pi/90.0), RLAT2 = (float)(RLAT+pi/90.0);

	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2],  GC;
	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
	GEOGCM( &IVAL, (float *)WND, &IRANGE);
	GEOGCP( &RLON, &RLAT, &GC);
/*
	int zone = 3;
	if		(GC==1)		zone = 1;	//LandSea = "Coastal Zone : Sea";           B
	else if (GC==3)		zone = 2;	//LandSea = "Coastal Zone : Coastal Land";  A1
	else if (GC==4)		zone = 3;	//LandSea = "Coastal Zone : InLand";        A2
*/
	CString zone = "A2";
	if		(GC==1)		zone = "B";	//LandSea = "Coastal Zone : Sea";				B
	else if (GC==3)		zone = "A1";	//LandSea = "Coastal Zone : Coastal Land";  A1
	else if (GC==4)		zone = "A2";	//LandSea = "Coastal Zone : InLand";        A2

	return zone;
}

double CSMS4DCView::E_P1546_V05(double latST,double lonST,double lat0,double lon0,
						  double HaglST, double f_MHz,double PtGtSTw, double kfactor,
						  double Ptime,double RxH,int ENV,int syst,double Plocation,
						  int P1546Clangle , int P1546landsea,int p)
{
	CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument();

	double dist , az , h1,lat3km  , lon3km , lat15km , lon15km,DseaW , DSea , DseaC ;
	double /*pi=4.0*atan(1.0)  ,*/  rearth=6371.0 , Ghv = 1;
	double tetai , mds , ds , tetamax15 = 0 , hi;	
	double StepRes , m_ZoomFactor = 1;
	double azI , mdz , dz , tetamax16 , hii,hir,ttca,corr_ca = 0;	
//	double Dland , Ebfs,ELand,EfsLand,ESea,EfsSea,delta,deltafs,deltaE,deltaEfs,alpha,beta,XX;
//	double E_sea_total,Efs_sea_total,Emix,Efsmix,E_Land_total,Efs_Land_total;
	
//	CP1546_Functions CP1546;

double Ht = HaglST;
double Hg = LatLon2Hg(latST,lonST);
double HasglST = Hg + Ht;

double Hgi = LatLon2Hg(lat0,lon0);
double Hr = RxH;

	dist = Distance_km(latST,lonST,lat0,lon0);
	dist = max(dist,0.00001);
	az = Azimuth_Deg(latST,lonST,lat0,lon0);
	OnDatabaseStationsindesktop2(latST,lonST);
	/////////////////////////////// h1 (Heff) ///////////////////////////////////////////////
	if (dist>=15.0)
	{
		reckon( latST,lonST,  3.0 , az , &lat3km  , &lon3km) ;
		reckon( latST,lonST, 15.0 , az , &lat15km , &lon15km) ;
	}
	else
	{
		reckon( latST,lonST, 0.2*dist , az , &lat3km  , &lon3km) ;
		reckon( latST,lonST,     dist , az , &lat15km , &lon15km) ;
	}
	h1 = HasglST - Points2HgAvr1(lat3km  , lon3km,lat15km , lon15km);
	///////////////////////////////// tetamax15 /////////////////////////////////////////////

//	StepRes = 1.0/m_ZoomFactor;
//	CString globeTileInfo = m_AppPath + _T("Texts\\globe.txt");
//	if (pDoc->TileInfo != globeTileInfo)
//		StepRes = (pDoc->m_Resolution_x/1000.0)/m_ZoomFactor;
	
	double disttest1 = Distance_km(latST,lonST, latST+0, lonST+pDoc->m_Resolution_x); 
	double disttest2 = Distance_km(latST,lonST, latST+pDoc->m_Resolution_x, lonST+0); 
	StepRes = min(disttest1, disttest2)/m_ZoomFactor;

//	if (h1<0.0)		//for Tropospheric scattering(Ets) calculation, tetamax15 should be calculated whether or not h1 is negative P1546-5
	{
		tetai = -pi/2.0;
		mds = m_ZoomFactor*min(dist,15.0);
		ds = 0.0;
		while( ds< mds )  //ds=0->15
		{
			ds = ds+StepRes;
			reckon( latST,lonST, ds , az , &lat15km , &lon15km) ;
			hi = LatLon2Hg(lat15km , lon15km) ;
			tetai = max(tetai   ,(((hi-HasglST)/(ds*1000.0))-(ds/(2.0*kfactor*rearth))));
		}
		tetamax15 = R2D*tetai;
	}
	/////////////////////////////////Rx ttca /////////////////////////////////////////////
//	if (P1546Clangle==1)	//for Tropospheric scattering(Ets) calculation, P1546-5
	{
		OnDatabaseStationsindesktop2(lat0,lon0);
		hir = LatLon2Hg(lat0,lon0) ;
		azI = Azimuth_Deg(lat0,lon0,latST,lonST);
		mdz = m_ZoomFactor*min(dist,16.0);
		tetamax16 = -pi/2.0;
		dz=0.0;
		while( dz< mdz )  //dz=0->16
		{
			dz = dz+StepRes;
			reckon(lat0,lon0, dz , azI , &lat15km , &lon15km) ;
			hii = LatLon2Hg(lat15km , lon15km) ;
//			tetamax16 = max(tetamax16   ,(((hii-10.0-hir)/(dz*1000))-(dz/(2.0*kfactor*rearth))));
			tetamax16 = max(tetamax16   ,(((hii-10.0-hir)/(dz*1000.0))-(dz/(2.0*rearth))));	//P.1546-5  section 11
		}
		ttca = tetamax16*R2D;
//		corr_ca = TCAcorr1546(ttca,f_MHz);
	}
	//////////////////////////////////////////////////////////////////////////////
	int pRX = p, p23path = p;

	if (P1546landsea==1)
	{
		DSea = LandWarmColdSea_D_Sea_kmIDWM(latST,lonST, lat0,lon0, &DseaW, &pRX); 
		DseaC = DSea - DseaW;
										p23path = 1;
		if      (DseaW>0)				p23path = 3;
		else if((DseaW<=0)&&(DseaC>0))	p23path = 2;
	}
	double Eb = FieldP1546V5(f_MHz, Ptime, p23path, h1,dist, DSea,
							  tetamax15, ttca ,Hr, ENV,
							  pRX, Ht, p,  Hg, Hgi, 
							  syst, Plocation, P1546Clangle, P1546landsea);
/*
	if (P1546landsea==1)
	{
		DSea = D_Sea_kmIDWM(latST,lonST,lat0,lon0, &DseaW);
		Dland = dist - DSea;		DseaC = DSea - DseaW;
		if (Dland==dist)		Eb = CP1546.P1546_8(f_MHz,Ptime,1,h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Ebfs);
		else if (DseaC==dist)	Eb = CP1546.P1546_8(f_MHz,Ptime,2,h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Ebfs);
		else if (DseaW==dist)	Eb = CP1546.P1546_8(f_MHz,Ptime,3,h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Ebfs);
		else
		{
			if (Dland<1.0)
			{
				ELand = CP1546.P1546_8(f_MHz,Ptime,1,h1,1.0,RxH,ENV,tetamax15,syst,Plocation,&EfsLand);
				ESea  = CP1546.P1546_8(f_MHz,Ptime,3,h1,1.0,RxH,ENV,tetamax15,syst,Plocation,&EfsSea);
				delta = Dland * (ELand - ESea);		deltafs = Dland * (EfsLand - EfsSea);
			}
			else if (Dland>=1.0)
			{
				ELand = CP1546.P1546_8(f_MHz,Ptime,1,h1,Dland,RxH,ENV,tetamax15,syst,Plocation,&EfsLand);
				ESea  = CP1546.P1546_8(f_MHz,Ptime,3,h1,Dland,RxH,ENV,tetamax15,syst,Plocation,&EfsSea);
				delta = ELand - ESea;				deltafs = EfsLand - EfsSea;
			}

			E_sea_total  = CP1546.P1546_8(f_MHz,Ptime,3,h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Efs_sea_total);
			Emix = E_sea_total + delta;			Efsmix = Efs_sea_total + deltafs;

			E_Land_total  = CP1546.P1546_8(f_MHz,Ptime,1,h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Efs_Land_total);
			deltaE = Emix - E_Land_total;		deltaEfs = Efsmix - Efs_Land_total;

			alpha = 0.3;      beta=0.0001;
			XX = alpha + (1.0 - alpha) * exp(-(beta *    pow( Dland , (2.42-0.0003527*h1) )    ));
			Eb = E_Land_total + deltaE * XX;	Ebfs = Efs_Land_total + deltaEfs * XX;
		}
	}
	else	Eb = CP1546.P1546_8(f_MHz,Ptime,p,h1,dist,RxH,ENV,tetamax15,syst,Plocation,&Ebfs);
	Eb = Eb + corr_ca;	Eb = min(Eb,Ebfs);
*/
	Eb = Eb + 10.0*log10(PtGtSTw*Ghv/1650.0);
	return Eb;	//dBuV/m
}
/////////////////////////////////Intermodulation Interference//////////////////////////////////////////
#include "FXM_F_D_rngDLG.h"
#include "NFDmobile_Functions.h"
#include "BorderRep1DLG.h"
CString CSMS4DCView::GetRxDataIntermodulation() 
{
	BeginWaitCursor();
	CString CDataBaseSTR , SelX = _T(" ");
	
	CDataBaseSTR.Format(  _T("SELECT * FROM %s WHERE  ((RXfreq)>0) ;")  ,  m_qSTtable );
	
	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;

	CDataBaseLDLG datadlg;
	datadlg.m_Title = _Z("Wanted Rx Station");

	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow==1)
			SelX = ((CSMS4DCApp *)AfxGetApp())->m_Sel[0];
	}
	Set_STtable_Default();
	return SelX;
}

BOOL CSMS4DCView::GetTxDataIntermodulation(long IDX,double latX, double lonX,  double Drange) 
{
	BOOL YOK = FALSE;
	double dumy,  lonmin , lonmax , latmin , latmax ,rng_km = Drange;
	reckon(latX,lonX, rng_km,  0.0,&latmax,&dumy) ;
	reckon(latX,lonX, rng_km,180.0,&latmin,&dumy) ;
	reckon(latX,lonX, rng_km, 90.0,&dumy,&lonmax) ;
	reckon(latX,lonX, rng_km,270.0,&dumy,&lonmin) ;
lonmin = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(lonmin);
lonmax = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(lonmax);

//	double fmin = frqX - Frange/1000.0,		fmax = frqX + Frange/1000.0;
	CString CDataBaseSTR;

if(lonmin<=lonmax)  CDataBaseSTR.Format("SELECT * FROM %s WHERE (((IDst)<>%ld) AND ((STlat_deg)>=%f And (STlat_deg)<=%f) AND ((STlon_deg)>=%f And (STlon_deg)<=%f)                                         AND ((TXfreq)>0));",m_qSTtable,IDX,latmin,latmax,lonmin,lonmax);
else				CDataBaseSTR.Format("SELECT * FROM %s WHERE (((IDst)<>%ld) AND ((STlat_deg)>=%f And (STlat_deg)<=%f) AND ( (STlon_deg>=%f And STlon_deg<=180) or (STlon_deg>=-180 And STlon_deg<=%f) ) AND ((TXfreq)>0));",m_qSTtable,IDX,latmin,latmax,lonmin,lonmax);

	((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR = CDataBaseSTR;

	CDataBaseLDLG datadlg;
	datadlg.m_Heff1 = FALSE;

	datadlg.m_Title = _Z("Interferer Stations");

	((CSMS4DCApp *)AfxGetApp())->Nrow = 0;
	if (datadlg.DoModal()==IDOK)
	{
		int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow>=1)	YOK = TRUE;
	}
	Set_STtable_Default();
	return YOK;
}
void CSMS4DCView::OnInterferenceIntermodulation() 
{
	BeginWaitCursor();
	CString m_SelX = GetRxDataIntermodulation();
	if(m_SelX!=" ")
	{
		long IDX = atol(GetFld(m_SelX,1));
		double latX = atof(GetFld(m_SelX,3));
		double lonX  = atof(GetFld(m_SelX,4));
		double frqX  = atof(GetFld(m_SelX,21));
		CString NameX = GetFld(m_SelX,2);
		CString st_clsX = GetFld(m_SelX,18);	st_clsX.TrimRight();	st_clsX.MakeUpper();

		CString EmissionX = GetFld(m_SelX,19);
		double BandX_kHz = Emission2NBW(EmissionX);

		double InsertionLoss = atof(GetFld(m_SelX,15));
		double RxSensitivity_uV = atof(GetFld(m_SelX,16));

		CFXM_F_D_rngDLG F_D_rngeDLG;
		F_D_rngeDLG.m_flag = FALSE;
		if(F_D_rngeDLG.DoModal()==IDOK)
		{
			BeginWaitCursor();
			double Emin = F_D_rngeDLG.m_Emin;
			double Frange = F_D_rngeDLG.m_F,   Drange = F_D_rngeDLG.m_D;
			BOOL Emergency = F_D_rngeDLG.m_Emergency;

			BOOL YOK = GetTxDataIntermodulation(IDX,latX, lonX, Drange) ;
			if(YOK==TRUE)
			{
				BeginWaitCursor();
				int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
				if (Nrow>=1)
				{
					double kfactor, Pime, Plocation;
					int ENV,  syst , P1546Clangle , P1546landsea;
					CP1546DLG p1546dlg;
					p1546dlg.m_RxShow=FALSE;
					if(p1546dlg.DoModal()==IDOK)
					{
						Pime = p1546dlg.m_time;		Plocation = p1546dlg.m_location;
						kfactor = p1546dlg.m_k;
						syst = p1546dlg.m_syst;		ENV = p1546dlg.m_env;
						P1546Clangle = p1546dlg.m_Clangle;	P1546landsea = p1546dlg.m_landsea;

						double HaglX = atof(GetFld(m_SelX,5));
						int p = LandWarmColdSea(lonX, latX);

LoadIDWMmap_r(latX,lonX, Drange);

						double HaslY ,HasglY;
						CString *m_Sel; m_Sel = new CString[Nrow];

						CString TxEmission, RxEmission = GetFld(m_SelX,19);	RxEmission.TrimRight();	RxEmission.MakeUpper();
						CNFDmobile_Functions NFDmobile;
							
						double frqY, Gr, dist, Efs, latY, lonY;
						CString NameY, st_clsY , RLONx, RLATx , RLONy, RLATy , antfile, ANT_Tx,ANT_Rx;
						long IDY;
				//		double C2 = 0.0, Df, NFDm, FsLimit;
						double GhvTx , GhvRx;
				//		double pi = 4.0*atan(1.0);
						double EL0Tx ,AZ0Tx,EL0Rx, AZ0Rx, el,fpi , HaglY ,tpi, fi, ti , PtGt_Y;
						int Txf0[360] , Rxf0[360];
						double TxrH[360]  ,  TxrV[360] , RxrH[360]  ,  RxrV[360];

						double re = kfactor*6371000;
						Gr  = atof(GetFld(m_SelX,10));
						EL0Rx  = (pi/180.0)*atof(GetFld(m_SelX,9));
						AZ0Rx  = (pi/180.0)*atof(GetFld(m_SelX,8));
						ANT_Rx = GetFld(m_SelX,14);

						antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,ANT_Rx);
						ReadAntennaData(antfile,Rxf0,RxrH,RxrV) ;

						CString strX,strY="",strY1="";
						int progress_num=0;
						CString progress_str, progress_char = "I";
						for(long Yi = 0;Yi<Nrow;Yi++)
						{
							progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*(++progress_num)/(double)(Nrow)),progress_char);
							progress_char = str_rep("I",(int)(progress_num*50.0/((double)(Nrow))) );
							((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
							PeekAndPump();

							m_Sel[Yi] = ((CSMS4DCApp *)AfxGetApp())->m_Sel[Yi];

							PtGt_Y  = atof(GetFld(m_Sel[Yi],7));
							IDY = atol(GetFld(m_Sel[Yi],1));
							NameY = GetFld(m_Sel[Yi],2);
							st_clsY = GetFld(m_Sel[Yi],18);	st_clsY.TrimRight();	st_clsY.MakeUpper();
							frqY  = atof(GetFld(m_Sel[Yi],6));
							TxEmission = GetFld(m_Sel[Yi],19);	TxEmission.TrimRight();	TxEmission.MakeUpper();
							latY = atof(GetFld(m_Sel[Yi],3));
							lonY  = atof(GetFld(m_Sel[Yi],4));
						
							/////////////////////Antenna Tx & Rx/////////////////////
							HaglY  = atof(GetFld(m_Sel[Yi],5));
							el = AZ_EL(latX,lonX ,latY,lonY, HaglX, HaglY, re, &fpi) ;
							tpi = (pi/2.0) - el;
							fi = (180.0/pi)*atan2(sin(tpi)*sin(fpi-AZ0Rx),(cos(EL0Rx)*sin(tpi)*cos(fpi-AZ0Rx)+cos(tpi)*sin(EL0Rx)));
							ti = (180.0/pi)*acos(cos(tpi)*cos(EL0Rx)-sin(EL0Rx)*sin(tpi)*cos(fpi-AZ0Rx));
							if (fi<0.0)		fi = fi + 359.4;
							GhvRx = Interp2(Rxf0,RxrH,fi,360) * Interp2(Rxf0,RxrV,ti,360);
							GhvRx = 10.0*log10(GhvRx);

							ANT_Tx = GetFld(m_Sel[Yi],14);
							antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,ANT_Tx);
							ReadAntennaData(antfile,Txf0,TxrH,TxrV) ;
							EL0Tx  = (pi/180.0)*atof(GetFld(m_Sel[Yi],9));
							AZ0Tx  = (pi/180.0)*atof(GetFld(m_Sel[Yi],8));
							el = AZ_EL(latY,lonY, latX,lonX , HaglY, HaglX, re, &fpi) ;
							tpi = (pi/2.0) - el;
							fi = (180.0/pi)*atan2(sin(tpi)*sin(fpi-AZ0Tx),(cos(EL0Tx)*sin(tpi)*cos(fpi-AZ0Tx)+cos(tpi)*sin(EL0Tx)));
							ti = (180.0/pi)*acos(cos(tpi)*cos(EL0Tx)-sin(EL0Tx)*sin(tpi)*cos(fpi-AZ0Tx));
							if (fi<0.0)		fi = fi + 359.4;
							GhvTx = Interp2(Txf0,TxrH,fi,360) * Interp2(Txf0,TxrV,ti,360);
							GhvTx = 10.0*log10(GhvTx);
							/////////////////////////////////////////

							OnDatabaseStationsindesktop2(latY,lonY);
							HaslY = LatLon2Hg(latY,lonY);
							HasglY = HaslY+HaglY;

				//			Df = fabs(frqX-frqY)*1000.0;
				//			NFDm = NFDmobile.NFDmobile1(TxEmission ,RxEmission ,Df, Emergency);
				//			FsLimit = Emin - Gr - GhvRx + C2 + NFDm;

							dist = Distance_km(latX,lonX ,latY,lonY);
							Rad2Str(lonY*D2R,latY*D2R, &RLONy,&RLATy);
							if(dist>0)
							{
								Efs = E_P1546_V05(latY,lonY ,latX,lonX, HaglY,  frqY,PtGt_Y, kfactor, Pime, HaglX, ENV, syst,Plocation,P1546Clangle , P1546landsea,p);
								Efs = Efs +	GhvTx;

				//				double Pr_dBm = Efs - 20.0*log10(frqY) - 10.0*log10(16.0*pi*pi/3.0) - 60.0 + Gr + GhvRx - InsertionLoss;
								double Pr_dBm = Efs - 20.0*log10(frqY) - 10.0*log10(16.0*pi*pi/3.0) - 60.0;

								strY1.Format("%g,%0.2f,%ld,%s,%s  %s,%0.0f,%0.2f",frqY,Pr_dBm,IDY,NameY,RLONy,RLATy,dist,Efs);
							}
							else
								strY1.Format("%g,%s,%ld,%s,%s  %s,%0.0f,%s",frqY,"---",IDY,NameY,RLONy,RLATy,dist,"---");
							strY = strY+","+strY1;

						}//for Yi
						delete [] m_Sel;
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, "");
						strY.Delete(0);

						Rad2Str(lonX*D2R,latX*D2R, &RLONx,&RLATx);

			//			double Ps_dBm = 20.0*log10(RxSensitivity_uV) - 90.0 - 10.0*log10(2.0*50.0);
						double Ps_dBm = 20.0*log10(RxSensitivity_uV) + InsertionLoss - Gr - GhvRx -90.0 - 10.0*log10(2.0*50.0);
						int Ps_dBmi = (int)(Ps_dBm*10.0);
						Ps_dBm = Ps_dBmi/10.0;

						strX.Format("%g,%g,%ld,%s,%s  %s,%g",frqX,BandX_kHz,IDX,NameX,RLONx,RLATx,InsertionLoss);

						if(!(strY.IsEmpty()))
						{
							typedef UINT ( * LPDLLFUNC)(HWND, CString, CString, long, CString, double, double);
							HINSTANCE hDLL = LoadLibrary("InterModDLL.dll");
							if(hDLL)
							{
								LPDLLFUNC lpfnDllFunc = (LPDLLFUNC)GetProcAddress(hDLL,"InterMod_Interference");
								if (!lpfnDllFunc)
								{
									CString str;
									str.Format(_Z("\nThe function [ %s ] was not found.\t\n") , "InterMod_Interference : InterModDLL.dll");
									MessageBox(str,  _Z("Error!!!"), MB_ICONERROR | MB_OK);
									FreeLibrary(hDLL);
									return;
								}
								lpfnDllFunc(this->m_hWnd, strX, strY ,Nrow+1, ((CSMS4DCApp *)AfxGetApp())->m_Lang, Ps_dBm, Gr);	
								FreeLibrary(hDLL);
							}
							else
							{
								CString str;
								str.Format(_Z("\nThe file [ %s ] was not found.\t\n") , "InterModDLL.dll");
								MessageBox(str,  _Z("Error!!!"), MB_ICONERROR | MB_OK);
							}
						}

					}//if kfactor
				}//if Nrow	Y
			}//if YOK
		}//if F_D_rngeDLG
	}// if m_SelX
	EndWaitCursor();		
}

void CSMS4DCView::OnPropagationmodelsP526v14Link() 
{
	int datadlg = OnDatabaseStationsindesktop1() ;
	if (datadlg==IDOK)
	{
		CKFactor P526dlg;
		if (P526dlg.DoModal()==IDOK)
		{
			int Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
			if (Nrow==2)
			{
				CString name1[2],m_Sel[2];
				CPoint pointst[2];
				double lat1[2],lon1[2];
				for (int i=0;i<2;i++)
				{
					m_Sel[i] = ((CSMS4DCApp *)AfxGetApp())->m_Sel[i];
					name1[i] = GetFld(m_Sel[i],2);
					lat1[i]  = atof(GetFld(m_Sel[i],3));
					lon1[i]  = atof(GetFld(m_Sel[i],4));
					LatLon2Point(lat1[i],lon1[i],&pointst[i]);
				}
				long x1=pointst[0].x;				long y1=1200-1-pointst[0].y;
				long x2=pointst[1].x;				long y2=1200-1-pointst[1].y;
				int xNmin = (min(x1 , x2) )-20;		int yNmin = (min(y1 , y2) )-20;
				int xNmax = (max(x1 , x2) )+20;		int yNmax = (max(y1 , y2) )+20;
				int xN  = abs(xNmax - xNmin);  		int yN  = abs(yNmax - yNmin);

				xN=max(0,min(xN,1200));	yN=max(0,min(yN,1200));

				((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Link Calculation (P526-14)");
				CPro_P526V14_LinkDoc *pDocLinkP526=(CPro_P526V14_LinkDoc *) DocUtil::GetLastDocument("Link Calculation (P526-14)");

				CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument() ;

				x1=pointst[0].x;		y1=pointst[0].y;
				x2=pointst[1].x;		y2=pointst[1].y;
				long xmin=min(x1 , x2);		long xmax=max(x1 , x2);
				long xabs=xmax-xmin;
				long ymin=min(y1 , y2);		long ymax=max(y1 , y2);
				long yabs=ymax-ymin;

				int Np =((xabs>=yabs) ? xabs+1 : yabs+1);
				int m_scalfactor=16;
				Np = (Np-1) * m_scalfactor + 1;

				double *X;		X=new double[Np];
				double *Y;		Y=new double[Np];
				if (xabs>=yabs)
				{
					for (int i=0;i<Np;i++)
					{
						X[i]=((x1<x2) ? x1+(double)i/(double)m_scalfactor : x1-(double)i/(double)m_scalfactor);
						Y[i]=((double)y1+(double)((X[i]-x1)*(y2-y1))/((double)(x2-x1)));
					}
				}
				else
				{
					for (int i=0;i<Np;i++)
					{
						Y[i]=((y1<y2) ? y1+(double)i/(double)m_scalfactor :y1-(double)i/(double)m_scalfactor);
						X[i]=((double)x1+(double)((Y[i]-y1)*(x2-x1))/((double)(y2-y1)));
					}
				}
				double *hi;			hi= new double[Np];
				double *rng;		rng=new double[Np];
				double *x_en;		x_en=new double[Np];
				double *y_en;		y_en=new double[Np];

				double xps,yps,xpm,ypm;
				pDocLinkP526->Np=Np;
				pDocLinkP526->m_di=new double[Np];
				pDocLinkP526->m_hi=new double[Np];
				pDocLinkP526->m_hikm=new double[Np];

				pDocLinkP526->m_lati=new double[Np];
				pDocLinkP526->m_loni=new double[Np];

				double *hi1;		hi1=new double[Np];

				double Hmin=32767.0;
				for ( i=0;i<Np;i++)
				{
					xps=X[i];			yps=1200.0-1.0-(Y[i]);
					xpm = xps + 600.0*((double)(pDoc->TileX-1));
					ypm = yps + 600.0*((double)(pDoc->TileY-1));

					x_en[i] = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
					y_en[i] = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
					y_en[i] = y_en[i]-pDoc->m_Resolution_y/2.0;
					x_en[i] = x_en[i]-pDoc->m_Resolution_x/2.0;

					CString globeTileInfo = m_AppPath + _T("Texts\\globe.txt");
					if (pDoc->TileInfo != globeTileInfo)
					{
						CUtm m_utm;
						m_utm.y = y_en[i];
						m_utm.x = x_en[i];
						m_utm.UTM2philambda();
						y_en[i]=m_utm.phi;
						x_en[i]=m_utm.lambda;
					}
					hi1[i] = RoundBUF_Hg(xps, yps);
					rng[i] = Distance_km( y_en[0], x_en[0], y_en[i], x_en[i]);
					pDocLinkP526->m_di[i]=rng[i];
					pDocLinkP526->m_hi[i]=hi1[i];
					pDocLinkP526->m_hikm[i]=hi1[i]/1000.0;

					pDocLinkP526->m_lati[i]=y_en[i];
					pDocLinkP526->m_loni[i]=x_en[i];

					Hmin=min(Hmin,hi1[i]);
				}
				pDocLinkP526->Hmin=Hmin;
				pDocLinkP526->Dmin=rng[0];
				pDocLinkP526->Dmax=rng[Np-1];
				pDocLinkP526->m_DrawFresnel = true;
				pDocLinkP526->m_Gt = atof(GetFld(m_Sel[0],10));
				pDocLinkP526->m_Gr = atof(GetFld(m_Sel[1],10));
				pDocLinkP526->LinkRxH = atof(GetFld(m_Sel[1],5));
				pDocLinkP526->LinkName_Rx = name1[1];
				pDocLinkP526->Linklat_Rx  = lat1[1];
				pDocLinkP526->Linklon_Rx  = lon1[1];
				pDocLinkP526->m_kfactor=P526dlg.m_kfactorEdit;
				pDocLinkP526->LinkName_ST = name1[0];
				pDocLinkP526->Linklat_ST  = lat1[0];
				pDocLinkP526->Linklon_ST  = lon1[0];
				pDocLinkP526->LinkHagl_ST = atof(GetFld(m_Sel[0],5));
				pDocLinkP526->LinkPtGt_ST  = atof(GetFld(m_Sel[0],7));
				pDocLinkP526->LinkfMHz_ST = atof(GetFld(m_Sel[0],6));

				pDocLinkP526->LinkRxThreshold = atof(GetFld(m_Sel[1],16));

				CPoint m_Point_ST;
				LatLon2Point(atof(GetFld(m_Sel[0],3)),atof(GetFld(m_Sel[0],4)), &m_Point_ST) ;
				pDocLinkP526->LinkHasl_ST = Point2Hg(m_Point_ST);

				xpm = xNmin + 600.0*(pDoc->TileX-1);
				ypm = yNmin + 600.0*(pDoc->TileY-1);
				double xUTM = pDoc->m_Lower_left_x + pDoc->m_Resolution_x*(xpm-1.0);
				double yUTM = pDoc->m_Lower_left_y + pDoc->m_Resolution_y*(ypm-1.0);
				yUTM=yUTM-pDoc->m_Resolution_y/2.0;
				xUTM=xUTM-pDoc->m_Resolution_x/2.0;
				pDocLinkP526->Linklat0 = yUTM;
				pDocLinkP526->Linklon0 = xUTM;
				pDocLinkP526->m_ReadyDoc=1;
				pDocLinkP526->GetData();
				pDocLinkP526->UpdateAllViews(NULL);

				delete [] X;	delete [] Y;	delete [] hi1;	delete [] hi;	delete [] rng; delete [] x_en;		delete [] y_en;
			}
		}//P526dlg
	}//datadlg			
}

//97/10/18
void CSMS4DCView::OnDraw2(CDC* pDC)
{
	CSMS4DCDoc* pDoc = (CSMS4DCDoc*)GetDocument();
	ASSERT_VALID(pDoc);
////////////////////////////////////////
	BYTE *temp2 , *Display=(BYTE *)malloc(pDoc->Width * pDoc->Height * sizeof(BYTE)); 
	_int16 *temp = (_int16 *)pDoc->buf;	temp2 = Display;

	_int16 m_MinValue1 = (_int16)max((double)pDoc->bufMin,m_MinValue);
	_int16 m_MaxValue1 = (_int16)min((double)pDoc->bufMax,m_MaxValue);
	for (int i=0;i<pDoc->Width;i++)
		for (int j=0;j<pDoc->Height;j++)
		{
			if((*temp)!=pDoc->m_NoData)
			{
				if(m_MaxValue1 == m_MinValue1)	*temp2 = 0;
				else							*temp2 = ( min(max((*temp),m_MinValue1),m_MaxValue1) - m_MinValue1) * 255 / (m_MaxValue1- m_MinValue1);
			}
			else								*temp2 = 255;

			if     ((*temp)<=m_MinValue1)		*temp2 = 0;
			else if((*temp)>=m_MaxValue1)		*temp2 = 254;
			temp2++;	temp++;
		}
	BITMAPFILEHEADER * pbmfh ;
	BITMAPINFO       * pbmi ;
	BYTE             * pBits ;
    int              cxDib, cyDib ;
		
	// Load the entire DIB into memory
	pbmfh = (struct tagBITMAPFILEHEADER *)malloc (1078) ;

//	CString BMP_HEADER =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\BMP_HEADER");
//	FILE *fp=fopen(BMP_HEADER,"rb");
//	fread(pbmfh,1078,1,fp);
//	fclose(fp);
              
	// Get pointers to the info structure & the bits
	pbmfh->bfType='BM';
	pbmfh->bfReserved1=0;
	pbmfh->bfReserved2=0;
	pbmfh->bfSize=pDoc->Width * pDoc->Height+1078;
	pbmfh->bfOffBits=1078;

	pbmi  = (BITMAPINFO *) (pbmfh + 1) ;
	pbmi->bmiHeader.biSize=40;
	pbmi->bmiHeader.biWidth=pDoc->Width ;
	pbmi->bmiHeader.biHeight=pDoc->Height ;
	pbmi->bmiHeader.biPlanes=1;
	pbmi->bmiHeader.biBitCount=8;
	pbmi->bmiHeader.biCompression=0;
	pbmi->bmiHeader.biSizeImage=pDoc->Width * pDoc->Height ;
	pbmi->bmiHeader.biXPelsPerMeter=0;
	pbmi->bmiHeader.biYPelsPerMeter=0;
	pbmi->bmiHeader.biClrUsed=256;
	pbmi->bmiHeader.biClrImportant=256;
	for( i=0;i<256;i++)
	{
		pbmi->bmiColors[i].rgbBlue  =   max(0,min(255,m_colorRate + GetBValue(pDoc->RGBt[i]) ));
		pbmi->bmiColors[i].rgbGreen =   max(0,min(255,m_colorRate + GetGValue(pDoc->RGBt[i]) ));
		pbmi->bmiColors[i].rgbRed   =   max(0,min(255,m_colorRate + GetRValue(pDoc->RGBt[i]) ));
		pbmi->bmiColors[i].rgbReserved=0;
	}
	pbmi->bmiColors[255].rgbBlue = 255;	pbmi->bmiColors[255].rgbGreen = 0;	pbmi->bmiColors[255].rgbRed = 0;
	
	pBits = (BYTE *) Display; 
	// Get the DIB width and height
	if (pbmi->bmiHeader.biSize == sizeof (BITMAPCOREHEADER))
	{
		cxDib = ((BITMAPCOREHEADER *) pbmi)->bcWidth ;		cyDib = ((BITMAPCOREHEADER *) pbmi)->bcHeight ;
	}
	else
	{
		cxDib = pbmi->bmiHeader.biWidth ;					cyDib = abs (pbmi->bmiHeader.biHeight) ;
	}

	if (pbmfh)
	{
		CDC MemDC;		BITMAP bm;		CBitmap m_bitmap;

		m_bitmap.CreateCompatibleBitmap(pDC, pDoc->Width , pDoc->Height);
		m_bitmap.GetObject (sizeof (BITMAP), &bm);
		MemDC.CreateCompatibleDC(pDC);	MemDC.SetMapMode(pDC->GetMapMode());	MemDC.SelectObject(m_bitmap);
		SetDIBitsToDevice (MemDC.m_hDC,	//pDC->m_hDC, //MemDC.m_hDC, 
						  0,         // xDst
						  0,         // yDst
						  cxDib,     // cxSrc
						  cyDib,     // cySrc
						  0,         // xSrc
						  0,         // ySrc
						  0,         // first scan line
						  cyDib,     // number of scan lines
						  pBits, 
						  pbmi, 
						  DIB_RGB_COLORS) ;
			///////////////////////////////////////
			int x1,y1,x2,y2;
			if (pDC->IsPrinting())
			{
				int offset = max(abs(m_rcPrintRect.right - m_rcPrintRect.left),
						         abs(m_rcPrintRect.top - m_rcPrintRect.bottom))/10;		//		int offset = 800;

				x1 = m_rcPrintRect.left+offset;			y1 = m_rcPrintRect.top+offset;
				x2 = m_rcPrintRect.right-offset;		y2 = m_rcPrintRect.bottom-offset;
				m_x1 = x1;	m_y1 = y1;	m_x2 = x2;	m_y2 = y2;
			}
			else
			{
				x1 = 0;		y1 = 0;		x2 = 1200-1;	y2 = 1200-1;
				m_x1 = x1;	m_y1 = y1;	m_x2 = x2;		m_y2 = y2;
			}
			///////////////////////////////////////
			pDC->StretchBlt(x1,y1,x2-x1,y2-y1,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);

			DeleteDC(MemDC.m_hDC);		MemDC.Detach();
	}
	free (pbmfh) ;	free(Display);
////////////// Draw Line /////////////////////////////
	CPen pen;	pen.CreatePen(PS_DOT,1,m_Color);	pDC->SelectObject(&pen);
	pDC->MoveTo(m_x1+(m_x2-m_x1)*(m_stLinePoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_stLinePoint.y)/(1200.0-1.0));
	pDC->LineTo(m_x1+(m_x2-m_x1)*(m_enLinePoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_enLinePoint.y)/(1200.0-1.0));
////////////// Draw Box /////////////////////////////
	pDC->MoveTo(m_x1+(m_x2-m_x1)*(m_stBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_stBoxPoint.y)/(1200.0-1.0));
	pDC->LineTo(m_x1+(m_x2-m_x1)*(m_stBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_enBoxPoint.y)/(1200.0-1.0));
	pDC->LineTo(m_x1+(m_x2-m_x1)*(m_enBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_enBoxPoint.y)/(1200.0-1.0));
	pDC->LineTo(m_x1+(m_x2-m_x1)*(m_enBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_stBoxPoint.y)/(1200.0-1.0));
	pDC->LineTo(m_x1+(m_x2-m_x1)*(m_stBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_stBoxPoint.y)/(1200.0-1.0));
///////////////////Selected Polygon////////////////////////
	CPoint * m_PolyPoint0;	m_PolyPoint0 = new CPoint[m_PolyPointNum+0];
	for (int k=0;k<m_PolyPointNum+0;k++)
	{
		m_PolyPoint0[k] = m_PolyPoint[k];
		m_PolyPoint0[k].x = m_x1+(m_x2-m_x1)*(m_PolyPoint0[k].x)/(1200.0-1.0);
		m_PolyPoint0[k].y = m_y1+(m_y2-m_y1)*(m_PolyPoint0[k].y)/(1200.0-1.0);
	}
	pDC->Polyline(m_PolyPoint0,m_PolyPointNum+0);
	CPen pen1;	pen1.CreatePen(PS_SOLID,3,RGB(0,0,0));	pDC->SelectObject(&pen1);
	int len = 4;
	if (pDC->IsPrinting())	len = 24;

	for ( k=0;k<m_PolyPointNum;k++)	pDC->Ellipse(m_PolyPoint0[k].x-len,	m_PolyPoint0[k].y-len, m_PolyPoint0[k].x+len, m_PolyPoint0[k].y+len);
	delete [] m_PolyPoint0;

/////////////////// Grid Line  ///////////////////////
	if (m_MenuBarGrid)
	{
		CPen penGrid;		penGrid.CreatePen(PS_DASH,1,RGB(127,127,127));		pDC->SelectObject(&penGrid);
		CPoint PointGrig1,PointGrig2;
		double lat1,lon1,lat2,lon2,  lat3,lon3,lat4,lon4,  lat0,lon0,latn,lonn;
		Point2LatLon(CPoint(1200-1,0),		&lat1,&lon1);
		Point2LatLon(CPoint(0,1200-1),		&lat2,&lon2);
		Point2LatLon(CPoint(0,0),			&lat3,&lon3);
		Point2LatLon(CPoint(1200-1,1200-1),	&lat4,&lon4);

lon1 = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon1,pDoc->TileX);
lon2 = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon2,pDoc->TileX);
lon3 = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon3,pDoc->TileX);
lon4 = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon4,pDoc->TileX);

		lon0 = min(min(lon1,lon2),min(lon3,lon4));		lonn = max(max(lon1,lon2),max(lon3,lon4));
		lat0 = max(max(lat1,lat2),max(lat3,lat4));		latn = min(min(lat1,lat2),min(lat3,lat4));

		double z = 0;		lat1 = lat0;	lat2 = latn;
		while (lon1<=lonn)
		{
			lon1 = lon0 + z*m_GridStep;
			LatLon2Point(lat1,lon1,&PointGrig1);	LatLon2Point(lat2,lon1,&PointGrig2);
			pDC->MoveTo(PointGrig1);				pDC->LineTo(PointGrig2);
			z = z + 1.0;
		}
		z = 0;		lon1 = lon0;	lon2 = lonn;
		while (lat1>=latn)
		{
			lat1 = lat0 - z*m_GridStep;
			LatLon2Point(lat1,lon1,&PointGrig1);	LatLon2Point(lat1,lon2,&PointGrig2);
			pDC->MoveTo(PointGrig1);				pDC->LineTo(PointGrig2);
			z = z + 1.0;
		}
	}
/////////////////// Station ////////////////////////
	if (Num_ST>0)
	{
		int scale = 1;
		if (pDC->IsPrinting())		scale = 5;

		CPoint Point1;
		for (i=0;i<Num_ST;i++)
		{
			DrawSymboleStation(pDC, Lat_ST[i], Lon_ST[i], m_SymbolColor, scale*m_SymbolSize);
			LatLon2Point(Lat_ST[i], Lon_ST[i],&Point1);
			TextDraw(pDC,Point1.x+scale*4, Point1.y-scale*5,Name_ST[i],m_SymbolTextColor,0,scale*12);
		}
	}
/////////////////// Link ////////////////////////
	if (Num_Link>0)
	{
		for (i=0;i<Num_Link;i++)		DrawSymboleLink(pDC,Lat_TxLink[i],Lon_TxLink[i],Lat_RxLink[i],Lon_RxLink[i]) ;
	}
/*
/////////////////// Circle  ///////////////////////
	CPoint * m_Point_STcr0;	m_Point_STcr0 = new CPoint[73];
	for ( k=0;k<73;k++)
	{
		m_Point_STcr0[k] = m_Point_STcr[k];
		m_Point_STcr0[k].x = m_x1+(m_x2-m_x1)*(m_Point_STcr0[k].x)/(1200.0-1.0);
		m_Point_STcr0[k].y = m_y1+(m_y2-m_y1)*(m_Point_STcr0[k].y)/(1200.0-1.0);
	}
	pDC->Polyline(m_Point_STcr0,73);
	delete [] m_Point_STcr0;
*/
///////////////////Vector Polygon////////////////////////
	if (m_POLYnum>=1)
		for ( i=0;i<m_POLYnum;i++)	DrawVector(pDC, m_POLY[i].PathNameVec,m_POLY[i].nWidthVec,m_POLY[i].crColorVec,m_POLY[i].nStyleVec,	m_POLY[i].nModeVec,m_POLY[i].flColorVec,m_POLY[i].alphaVec) ;
/////////////////// Earth Station ////////////////////////
	if (Num_EST>0)
	{
		int scale = 1;
		if (pDC->IsPrinting())		scale = 5;
		CPoint Point1;
		for (i=0;i<Num_EST;i++)
		{
			DrawSymboleEarthStation(pDC, Lat_EST[i], Lon_EST[i], m_SymbolColor, scale*m_SymbolSize);
			LatLon2Point(Lat_EST[i], Lon_EST[i],&Point1);
			TextDraw(pDC,Point1.x+scale*4, Point1.y-scale*5,Name_EST[i],m_SymbolTextColor,0,scale*12);
		}
	}

	if(m_OverlayFlag)
		OverlayFunction(m_pDocOverlay , m_OverlayFactor , pDC);

	if(m_CoplLat!=-999)
		DrawSymboleCopl(pDC, m_CoplLat, m_CoplLon, m_SymbolColor, m_SymbolSize);


	/*
	int deltaN[] = {  64, 128,   1,   2,   4,   8,  16,  32};
	int c,r,g,b;
	int ind, ind2, delta;
	double slop, slopmax;

	for ( i=1;i<pDoc->Width-1;i++)
	{
		for (int j=1;j<pDoc->Height-1;j++)
		{
			ind = i+j*(pDoc->Width);
			c = pDoc->buf[i][j];

			delta = 0;
			slopmax = -999999.0;

//			ind2 = (i+1)+(j+0)*(pDoc->Width);
	//		if((ind2>=0)&&(ind2<(pDoc->Width)*(pDoc->Height)))
			{
//				slop = c-pDoc->buf[i+1][j+0];		
				slop = pDC->GetPixel(i,j)-pDC->GetPixel(i+1,j+0);		
				
				slopmax = max(slopmax,slop);	if(slopmax==slop)	delta = deltaN[0];
			}

		//	ind2 = (i+1)+(j-1)*(pDoc->Width);
		//	if((ind2>=0)&&(ind2<(pDoc->Width)*(pDoc->Height)))
			{
		//		slop = (c-pDoc->buf[i+1][j-1])/sqrt(2.0);
				slop = pDC->GetPixel(i,j)-pDC->GetPixel(i+1,j-1);		
				
				slopmax = max(slopmax,slop);	if(slopmax==slop)	delta = deltaN[1];
			}

		//	ind2 = (i+0)+(j-1)*(pDoc->Width);
		//	if((ind2>=0)&&(ind2<(pDoc->Width)*(pDoc->Height)))
			{
		//		slop = c-pDoc->buf[i+0][j-1];
				slop = pDC->GetPixel(i,j)-pDC->GetPixel(i+0,j-1);		
				
				slopmax = max(slopmax,slop);	if(slopmax==slop)	delta = deltaN[2];
			}

		//	ind2 = (i-1)+(j-1)*(pDoc->Width);
		//	if((ind2>=0)&&(ind2<(pDoc->Width)*(pDoc->Height)))
			{
		//		slop = (c-pDoc->buf[i-1][j-1])/sqrt(2.0);
				slop = pDC->GetPixel(i,j)-pDC->GetPixel(i-1,j-1);		
				
				slopmax = max(slopmax,slop);	if(slopmax==slop)	delta = deltaN[3];
			}

		//	ind2 = (i-1)+(j+0)*(pDoc->Width);
		//	if((ind2>=0)&&(ind2<(pDoc->Width)*(pDoc->Height)))
			{
		//		slop = c-pDoc->buf[i-1][j+0];				
				slop = pDC->GetPixel(i,j)-pDC->GetPixel(i-1,j+0);		
				
				slopmax = max(slopmax,slop);	if(slopmax==slop)	delta = deltaN[4];
			}

		//	ind2 = (i-1)+(j+1)*(pDoc->Width);
		//	if((ind2>=0)&&(ind2<(pDoc->Width)*(pDoc->Height)))
			{
		//		slop = (c-pDoc->buf[i-1][j+1])/sqrt(2.0);	
				slop = pDC->GetPixel(i,j)-pDC->GetPixel(i-1,j+1);		
				
				slopmax = max(slopmax,slop);	if(slopmax==slop)	delta = deltaN[5];
			}

		//	ind2 = (i+0)+(j+1)*(pDoc->Width);
		//	if((ind2>=0)&&(ind2<(pDoc->Width)*(pDoc->Height)))
			{
		//		slop = c-pDoc->buf[i+0][j+1];			
				slop = pDC->GetPixel(i,j)-pDC->GetPixel(i+0,j+1);		
				
				slopmax = max(slopmax,slop);	if(slopmax==slop)	delta = deltaN[6];
			}

		//	ind2 = (i+1)+(j+1)*(pDoc->Width);
		//	if((ind2>=0)&&(ind2<(pDoc->Width)*(pDoc->Height)))
			{
		//		slop = (c-pDoc->buf[i+1][j+1])/sqrt(2.0);
				slop = pDC->GetPixel(i,j)-pDC->GetPixel(i+1,j+1);		
				
				slopmax = max(slopmax,slop);	if(slopmax==slop)	delta = deltaN[7];
			}

			COLORREF c1 = pDC->GetPixel(i,j);
			r = GetRValue(c1) + delta;
			g = GetGValue(c1) + delta;
			b = GetBValue(c1) + delta;

			r = min(255, max(0,(r/1 + 0)));
			g = min(255, max(0,(g/1 + 0)));
			b = min(255, max(0,(b/1 + 0)));
			pDC->SetPixel(i,j, RGB(r,g,b));
		}
	}
	*/
}


void CSMS4DCView::OnDraw_Objects(CDC* pDC)
{
	CSMS4DCDoc* pDoc = (CSMS4DCDoc*)GetDocument();
	ASSERT_VALID(pDoc);

////////////// Draw Line /////////////////////////////
	CPen pen;	pen.CreatePen(PS_DOT,1,m_Color);	pDC->SelectObject(&pen);
	if(m_stLinePoint!=m_enLinePoint)
	{
		pDC->MoveTo(m_x1+(m_x2-m_x1)*(m_stLinePoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_stLinePoint.y)/(1200.0-1.0));
		pDC->LineTo(m_x1+(m_x2-m_x1)*(m_enLinePoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_enLinePoint.y)/(1200.0-1.0));
	}
////////////// Draw Box /////////////////////////////
	if(m_stBoxPoint!=m_enBoxPoint)
	{
		pDC->MoveTo(m_x1+(m_x2-m_x1)*(m_stBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_stBoxPoint.y)/(1200.0-1.0));
		pDC->LineTo(m_x1+(m_x2-m_x1)*(m_stBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_enBoxPoint.y)/(1200.0-1.0));
		pDC->LineTo(m_x1+(m_x2-m_x1)*(m_enBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_enBoxPoint.y)/(1200.0-1.0));
		pDC->LineTo(m_x1+(m_x2-m_x1)*(m_enBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_stBoxPoint.y)/(1200.0-1.0));
		pDC->LineTo(m_x1+(m_x2-m_x1)*(m_stBoxPoint.x)/(1200.0-1.0) , m_y1+(m_y2-m_y1)*(m_stBoxPoint.y)/(1200.0-1.0));
	}
///////////////////Selected Polygon////////////////////////
	if(m_PolyPointNum>0)
	{
		CPoint * m_PolyPoint0 = new CPoint[m_PolyPointNum+0];
		for (int k=0;k<m_PolyPointNum+0;k++)
		{
			m_PolyPoint0[k] = m_PolyPoint[k];
			m_PolyPoint0[k].x = m_x1+(m_x2-m_x1)*(m_PolyPoint0[k].x)/(1200.0-1.0);
			m_PolyPoint0[k].y = m_y1+(m_y2-m_y1)*(m_PolyPoint0[k].y)/(1200.0-1.0);
		}
		pDC->Polyline(m_PolyPoint0,m_PolyPointNum+0);
		CPen pen1;	pen1.CreatePen(PS_SOLID,3,RGB(0,0,0));	pDC->SelectObject(&pen1);
		int len = 4;
		if (pDC->IsPrinting())	len = 24;

		for ( k=0;k<m_PolyPointNum;k++)	pDC->Ellipse(m_PolyPoint0[k].x-len,	m_PolyPoint0[k].y-len, m_PolyPoint0[k].x+len, m_PolyPoint0[k].y+len);
		delete [] m_PolyPoint0;
	}
/////////////////// Grid Line  ///////////////////////
	if (m_MenuBarGrid)
	{
		CPen penGrid;		penGrid.CreatePen(PS_DASH,1,RGB(127,127,127));		pDC->SelectObject(&penGrid);
		CPoint PointGrig1,PointGrig2;
		double lat1,lon1,lat2,lon2,  lat3,lon3,lat4,lon4,  lat0,lon0,latn,lonn;
		Point2LatLon(CPoint(1200-1,0),		&lat1,&lon1);
		Point2LatLon(CPoint(0,1200-1),		&lat2,&lon2);
		Point2LatLon(CPoint(0,0),			&lat3,&lon3);
		Point2LatLon(CPoint(1200-1,1200-1),	&lat4,&lon4);

lon1 = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon1,pDoc->TileX);
lon2 = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon2,pDoc->TileX);
lon3 = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon3,pDoc->TileX);
lon4 = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon4,pDoc->TileX);

		lon0 = min(min(lon1,lon2),min(lon3,lon4));		lonn = max(max(lon1,lon2),max(lon3,lon4));
		lat0 = max(max(lat1,lat2),max(lat3,lat4));		latn = min(min(lat1,lat2),min(lat3,lat4));

		double z = 0;		lat1 = lat0;	lat2 = latn;
		while (lon1<=lonn)
		{
			lon1 = lon0 + z*m_GridStep;
			LatLon2Point(lat1,lon1,&PointGrig1);	LatLon2Point(lat2,lon1,&PointGrig2);
			pDC->MoveTo(PointGrig1);				pDC->LineTo(PointGrig2);
			z = z + 1.0;
		}
		z = 0;		lon1 = lon0;	lon2 = lonn;
		while (lat1>=latn)
		{
			lat1 = lat0 - z*m_GridStep;
			LatLon2Point(lat1,lon1,&PointGrig1);	LatLon2Point(lat1,lon2,&PointGrig2);
			pDC->MoveTo(PointGrig1);				pDC->LineTo(PointGrig2);
			z = z + 1.0;
		}
	}
/*/////////////////// Station ////////////////////////
	if (Num_ST>0)
	{
		int scale = 1;
		if (pDC->IsPrinting())		scale = 5;

		CPoint Point1;
		for (i=0;i<Num_ST;i++)
		{
			DrawSymboleStation(pDC, Lat_ST[i], Lon_ST[i], m_SymbolColor, scale*m_SymbolSize);
			LatLon2Point(Lat_ST[i], Lon_ST[i],&Point1);
			TextDraw(pDC,Point1.x+scale*4, Point1.y-scale*5,Name_ST[i],m_SymbolTextColor,0,scale*12);
		}
	}
/////////////////// Link ////////////////////////
	if (Num_Link>0)
	{
		for ( i=0;i<Num_Link;i++)		DrawSymboleLink(pDC,Lat_TxLink[i],Lon_TxLink[i],Lat_RxLink[i],Lon_RxLink[i]) ;
	}

///////////////////Vector Polygon////////////////////////
//	if (m_POLYnum>=1)
//		for ( i=0;i<m_POLYnum;i++)	DrawVector(pDC, m_POLY[i].PathNameVec,m_POLY[i].nWidthVec,m_POLY[i].crColorVec,m_POLY[i].nStyleVec,	m_POLY[i].nModeVec,m_POLY[i].flColorVec,m_POLY[i].alphaVec) ;
/////////////////// Earth Station ////////////////////////
	if (Num_EST>0)
	{
		int scale = 1;
		if (pDC->IsPrinting())		scale = 5;
		CPoint Point1;
		for (i=0;i<Num_EST;i++)
		{
			DrawSymboleEarthStation(pDC, Lat_EST[i], Lon_EST[i], m_SymbolColor, scale*m_SymbolSize);
			LatLon2Point(Lat_EST[i], Lon_EST[i],&Point1);
			TextDraw(pDC,Point1.x+scale*4, Point1.y-scale*5,Name_EST[i],m_SymbolTextColor,0,scale*12);
		}
	}*/

//	if(m_OverlayFlag)
//		OverlayFunction(m_pDocOverlay , m_OverlayFactor , pDC);

//	if(m_CoplLat!=-999)
//		DrawSymboleCopl(pDC, m_CoplLat, m_CoplLon, m_SymbolColor, m_SymbolSize);
}

//////////////////////////////////////////////////////////////971019
HBITMAP CSMS4DCView::Draw_hBitmap2D(CSMS4DCDoc* pDoc)
{
	HBITMAP hRet = NULL;
	HDC hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	if (hScrDC)
	{
		HDC hMemDC = CreateCompatibleDC(hScrDC); 
		if (hMemDC)
		{
			int W = pDoc->Width, H = pDoc->Height;
			////////////////////////////////////////
			// create a bitmap compatible with the screen DC 
//			HBITMAP hBitmap = CreateADIBSection(hScrDC, W, H);
			HBITMAP hBitmap = CreateCompatibleBitmap(hScrDC, W, H);

			if (hBitmap)
			{
				// select new bitmap into memory DC 
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
				RECT rect;	rect.left = rect.top = 0;	rect.right  = W;	rect.bottom = H;
				::SetBkColor(hMemDC, GetSysColor(COLOR_WINDOW));
				::ExtTextOut(hMemDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);

				BYTE *temp2 , *Display=(BYTE *)malloc(W * H * sizeof(BYTE)); 
				_int16 *temp = (_int16 *)pDoc->buf;	temp2 = Display;

				_int16 m_MinValue1 = (_int16)max((double)pDoc->bufMin,m_MinValue);
				_int16 m_MaxValue1 = (_int16)min((double)pDoc->bufMax,m_MaxValue);
				for (int i=0;i<W;i++)
					for (int j=0;j<H;j++)
					{
						if((*temp)!=pDoc->m_NoData)
						{
							if(m_MaxValue1 == m_MinValue1)	*temp2 = 0;
							else							*temp2 = ( min(max((*temp),m_MinValue1),m_MaxValue1) - m_MinValue1) * 255 / (m_MaxValue1- m_MinValue1);
						}
						else								*temp2 = 255;

						if     ((*temp)<=m_MinValue1)		*temp2 = 0;
						else if((*temp)>=m_MaxValue1)		*temp2 = 254;
						temp2++;	temp++;
					}

				BITMAPFILEHEADER * pbmfh ;
				BITMAPINFO       * pbmi ;
				BYTE             * pBits ;
				int              cxDib, cyDib ;
					
				// Load the entire DIB into memory
				pbmfh = (struct tagBITMAPFILEHEADER *)malloc (1078) ;
              
				// Get pointers to the info structure & the bits
				pbmfh->bfType='BM';
				pbmfh->bfReserved1=0;
				pbmfh->bfReserved2=0;
				pbmfh->bfSize=W * H+1078;
				pbmfh->bfOffBits=1078;

				pbmi  = (BITMAPINFO *) (pbmfh + 1) ;
				pbmi->bmiHeader.biSize=40;
				pbmi->bmiHeader.biWidth=W ;
				pbmi->bmiHeader.biHeight=H ;
				pbmi->bmiHeader.biPlanes=1;
				pbmi->bmiHeader.biBitCount=8;
				pbmi->bmiHeader.biCompression=0;
				pbmi->bmiHeader.biSizeImage=W * H ;
				pbmi->bmiHeader.biXPelsPerMeter=0;
				pbmi->bmiHeader.biYPelsPerMeter=0;
				pbmi->bmiHeader.biClrUsed=256;
				pbmi->bmiHeader.biClrImportant=256;
				for( i=0;i<256;i++)
				{
					pbmi->bmiColors[i].rgbBlue  =   max(0,min(255,m_colorRate + GetBValue(pDoc->RGBt[i]) ));
					pbmi->bmiColors[i].rgbGreen =   max(0,min(255,m_colorRate + GetGValue(pDoc->RGBt[i]) ));
					pbmi->bmiColors[i].rgbRed   =   max(0,min(255,m_colorRate + GetRValue(pDoc->RGBt[i]) ));
					pbmi->bmiColors[i].rgbReserved=0;
				}
				pbmi->bmiColors[255].rgbBlue = 255;	pbmi->bmiColors[255].rgbGreen = 0;	pbmi->bmiColors[255].rgbRed = 0;
				
				pBits = (BYTE *) Display; 
				// Get the DIB width and height
				if (pbmi->bmiHeader.biSize == sizeof (BITMAPCOREHEADER))
				{
					cxDib = ((BITMAPCOREHEADER *) pbmi)->bcWidth ;		
					cyDib = ((BITMAPCOREHEADER *) pbmi)->bcHeight ;
				}
				else
				{
					cxDib = pbmi->bmiHeader.biWidth ;					
					cyDib = abs (pbmi->bmiHeader.biHeight) ;
				}

				if (pbmfh)
				{
					SetDIBitsToDevice(	hMemDC,		  // MemDC.m_hDC, 
										0,0,		  // xDst, yDst
										cxDib,cyDib,  // cxSrc, cySrc
										0,0,          // xSrc, ySrc
										0,            // first scan line
										cyDib,        // number of scan lines
										pBits,  pbmi,  DIB_RGB_COLORS) ;
				}
				free (pbmfh) ;	free(Display);

	CDC MemDC;
	MemDC.Attach(hMemDC); 

///////////////////Vector Polygon////////////////////////
	if (m_POLYnum>=1)
		for ( i=0;i<m_POLYnum;i++)	DrawVector(&MemDC, m_POLY[i].PathNameVec,m_POLY[i].nWidthVec,m_POLY[i].crColorVec,m_POLY[i].nStyleVec,	m_POLY[i].nModeVec,m_POLY[i].flColorVec,m_POLY[i].alphaVec) ;
///////////////////Overlay//////////////////////////////
	if(m_OverlayFlag)
		OverlayFunction(m_pDocOverlay , m_OverlayFactor , &MemDC);
/////////////////////////////////////////////////////////
	MemDC.Detach();	MemDC.DeleteDC(); 

				// select the old bitmap back into memory DC and get handle to bitmap
				hRet = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
				SetBitmapDimensionEx(hRet, W, H, NULL);
			}//hBitmap
			DeleteDC(hMemDC); 
			hBitmap = NULL;
		}//hMemDC
	}//hScrDC
	DeleteDC(hScrDC);

	return hRet;
}

void CSMS4DCView::UpDate_hBitmap(void)
{
	CSMS4DCDoc* pDoc = (CSMS4DCDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	
	Del_hBitmap();
	m_hBitmap = Draw_hBitmap(pDoc);
}
void CSMS4DCView::UpDate_hBitmap(CSMS4DCDoc* pDoc)
{
	Del_hBitmap();
	m_hBitmap = Draw_hBitmap(pDoc);
}
void CSMS4DCView::Del_hBitmap(void)
{
	if (m_hBitmap)
	{
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
}

//Move from SMS4DCView.cpp		//971020
///////////////////////////////////////////////////////////////
void CSMS4DCView::OnToolsNormalize() 
{
	CSMS4DCDoc* pDoc = (CSMS4DCDoc*)GetDocument();
	CNormalizeDLG xx;
	xx.m_MinValue2 = pDoc->bufMin;
	xx.m_MaxValue2 = pDoc->bufMax;
	xx.m_MinValue = m_MinValue;
	xx.m_MaxValue = m_MaxValue;
	if (xx.DoModal()==IDOK)
	{
		m_MinValue = xx.m_MinValue;
		m_MaxValue = xx.m_MaxValue;
		InvalidateLegend();	//97/12/26	
		UpDate_hBitmap(pDoc);
		Invalidate();
	}
}
void CSMS4DCView::ColorMap_Function(CString type) 
{
	CSMS4DCDoc* pDoc = GetDocument();
	if(pDoc->colormaptype != type)
	{
		m_ColorMapNegative = FALSE;		//97/12/27
		pDoc->colormaptype = type;
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		UpDate_hBitmap(pDoc);
		Invalidate();
		InvalidateLegend();	//97/12/26	
	}
}
void CSMS4DCView::OnToolsLighten() 
{
	m_colorRate = m_colorRate+20;
	InvalidateLegend();	//97/12/26	
	UpDate_hBitmap();
	InvalidateRect(NULL,false);
}
void CSMS4DCView::OnToolsDarken() 
{
	m_colorRate = m_colorRate-20;
	InvalidateLegend();	//97/12/26	
	UpDate_hBitmap();
	InvalidateRect(NULL,false);
}
void CSMS4DCView::OnNorth() 
{
	CSMS4DCDoc* pDoc = GetDocument();
	if(pDoc->TileY < pDoc->m_Nymax-1)
	{
		for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].y +=600;
	//	for ( i=0;i<73;i++)						m_Point_STcr[i].y +=600;

		m_stLinePoint.y +=600;	m_enLinePoint.y +=600;	m_stBoxPoint.y +=600;	m_enBoxPoint.y +=600;
		pDoc->TileY = pDoc->TileY+1;		pDoc->GetData();	
		UpDate_hBitmap(pDoc);
		Invalidate();
	}
}
void CSMS4DCView::OnSouth() 
{
	CSMS4DCDoc* pDoc = GetDocument();
	if(pDoc->TileY > 1)
	{
		for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].y -=600;
	//	for ( i=0;i<73;i++)						m_Point_STcr[i].y -=600;

		m_stLinePoint.y -=600;	m_enLinePoint.y -=600;	m_stBoxPoint.y -=600;	m_enBoxPoint.y -=600;
		pDoc->TileY=pDoc->TileY-1;		pDoc->GetData();	
		UpDate_hBitmap(pDoc);
		Invalidate();
	}
}
void CSMS4DCView::OnWest() 
{
	CSMS4DCDoc* pDoc = GetDocument();
	if(pDoc->IsMapCircle())
	{
		for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].x +=600;
	//	for ( i=0;i<73;i++)						m_Point_STcr[i].x +=600;

		m_stLinePoint.x +=600;	m_enLinePoint.x +=600;	m_stBoxPoint.x +=600;	m_enBoxPoint.x +=600;
		pDoc->TileX=pDoc->TileX-1;		pDoc->GetData();		
		UpDate_hBitmap(pDoc);
		Invalidate();
	}
	else
	{
		if(pDoc->TileX > 1)
		{
			for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].x +=600;
		//	for ( i=0;i<73;i++)						m_Point_STcr[i].x +=600;

			m_stLinePoint.x +=600;	m_enLinePoint.x +=600;	m_stBoxPoint.x +=600;	m_enBoxPoint.x +=600;
			pDoc->TileX=pDoc->TileX-1;		pDoc->GetData();		
			UpDate_hBitmap(pDoc);
			Invalidate();
		}
	}
/*
//	if(pDoc->TileX > 1)
	{
		for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].x +=600;
	//	for ( i=0;i<73;i++)						m_Point_STcr[i].x +=600;

		m_stLinePoint.x +=600;	m_enLinePoint.x +=600;	m_stBoxPoint.x +=600;	m_enBoxPoint.x +=600;
		pDoc->TileX=pDoc->TileX-1;		pDoc->GetData();		Invalidate();
	}
*/
}
void CSMS4DCView::OnEast() 
{
	CSMS4DCDoc* pDoc = GetDocument();
	if(pDoc->IsMapCircle())
	{
		for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].x -=600;
	//	for ( i=0;i<73;i++)						m_Point_STcr[i].x -=600;

		m_stLinePoint.x -=600;	m_enLinePoint.x -=600;	m_stBoxPoint.x -=600;	m_enBoxPoint.x -=600;
		pDoc->TileX=pDoc->TileX+1;		pDoc->GetData();	
		UpDate_hBitmap(pDoc);
		Invalidate();
	}
	else
	{
		if(pDoc->TileX < pDoc->m_Nxmax-1)
		{
			for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].x -=600;
		//	for ( i=0;i<73;i++)						m_Point_STcr[i].x -=600;

			m_stLinePoint.x -=600;	m_enLinePoint.x -=600;	m_stBoxPoint.x -=600;	m_enBoxPoint.x -=600;
			pDoc->TileX=pDoc->TileX+1;		pDoc->GetData();	
			UpDate_hBitmap(pDoc);
			Invalidate();
		}
	}
/*
//	if(pDoc->TileX < pDoc->m_Nxmax-1)
	{
		for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].x -=600;
	//	for ( i=0;i<73;i++)						m_Point_STcr[i].x -=600;

		m_stLinePoint.x -=600;	m_enLinePoint.x -=600;	m_stBoxPoint.x -=600;	m_enBoxPoint.x -=600;
		pDoc->TileX=pDoc->TileX+1;		pDoc->GetData();	Invalidate();
	}
*/
}
/*
void CSMS4DCView::OnWESTfirst() 
{
	CSMS4DCDoc* pDoc = GetDocument();
	{
int n = pDoc->TileX;
		for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].x +=(n-1)*600;
		m_stLinePoint.x +=(n-1)*600;	m_enLinePoint.x +=(n-1)*600;	m_stBoxPoint.x +=(n-1)*600;	m_enBoxPoint.x +=(n-1)*600;
		
		pDoc->TileX=1;		pDoc->GetData();		Invalidate();
	}
}
void CSMS4DCView::OnEASTend() 
{
	CSMS4DCDoc* pDoc = GetDocument();
	{
int n = pDoc->TileX;
int m_Nxmax = pDoc->m_Nxmax;
		for (int i=0;i<=m_PolyPointNum;i++)		m_PolyPoint[i].x -=(m_Nxmax-1-n)*600;
		m_stLinePoint.x -=(m_Nxmax-1-n)*600;	m_enLinePoint.x -=(m_Nxmax-1-n)*600;	m_stBoxPoint.x -=(m_Nxmax-1-n)*600;	m_enBoxPoint.x -=(m_Nxmax-1-n)*600;

		pDoc->TileX=pDoc->m_Nxmax-1;		pDoc->GetData();	Invalidate();
	}
}
*/

void CSMS4DCView::OnRefresh() 
{	
	UpDate_hBitmap();	
	InvalidateRect(NULL,false);
}
void CSMS4DCView::OnRefresh1()
{
	InvalidateRect(NULL,false);
}
void CSMS4DCView::OnRefresh2() 
{	
	OnRefresh();
}

///////////////////////////////////////////////////////////////
// Code to create a DIB section that will be used as a test case.
HBITMAP CSMS4DCView::CreateADIBSection(HDC hScrDC,int W, int H)
{
	// Initialize the header.
	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = W;
	bmi.bmiHeader.biHeight = H;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	// Create the surface.
	HBITMAP hBitmap = CreateDIBSection(hScrDC,	 // Handle to device context.
							  &bmi,				 // Pointer to creation parameters
							  DIB_RGB_COLORS,	 // Unused.
							  NULL,				 // Address of pointer to surface.		&pBits
							  NULL,				 // No file mapping object.
							  0);				 // No offset.

	::ReleaseDC(NULL, hScrDC);
	return(hBitmap);
}

BOOL CSMS4DCView::OnEraseBkgnd(CDC* pDC) 
{
    FillOutsideRect( pDC, &CBrush( GetSysColor( COLOR_WINDOW ) ) );
    return TRUE;    // Prevent erasing the background to reduce flickering

//	return CScrollView::OnEraseBkgnd(pDC);
}


///////////////////////
///////////////////////
///////////////////////
///////////////////////

int CSMS4DCView::chInd(int I, int Npx) 	
{
	if(I<0)			return 0;
	if(I>(Npx-1))	return (Npx-1);
	return I;

//	int J = I;
//	if(I<0 || I>Npx-1)	J = 0;
//	return J;
}
COLORREF CSMS4DCView::hillshade_new(CSMS4DCDoc* pDoc, int px, int py, int W, int H, COLORREF c) 	
{
	double  zenith = 45.0, azimuth = 315.0, 
			distx = 63710*(pDoc->m_Resolution_x)*D2R,		
			disty = 63710*(pDoc->m_Resolution_y)*D2R;		//		/100

	// lighting altitude
	double zr = (90.0 - zenith)*D2R;	// convert to zenith angle in radians
	
	// lighting azimuth
	double ar = 360.0 - azimuth + 90.0;		// convert to mathematic unit	
	if (ar > 360)  	ar = ar - 360;    	
	ar = ar*D2R;  
	
	_int16 zij;		int I1, J1;
	double	 x = 0.0, y = 0.0, sum_hor = 0.0, sum_ver = 0.0;

	int n = 3;
	int hor[3][3] = { -1, 0, 1, 
		              -2, 0, 2, 
			          -1, 0, 1};
	int ver[3][3] = { 1, 2, 1, 
		              0, 0, 0, 
			         -1,-2,-1};

	for(int i=0; i<n; i++)
	{
		I1 = chInd( px + (i-1), W);
		for(int j=0; j<n; j++)
		{
			J1 = chInd( py + (j-1), H);
			zij = pDoc->buf[I1][J1];
			x += zij * hor[i][j];
			y += zij * ver[i][j];

			sum_hor += fabs(hor[i][j]);
			sum_ver += fabs(ver[i][j]);
		}
	}
	x = x/sum_hor/distx;			//	dz/dx
	y = y/sum_ver/disty;			//	dz/dy
	double slop = atan(sqrt(x*x + y*y)) ;              

//	double z1 = (x!=0) * atan2(y,-x);      
//	z1 = z1 + (z1<0)*(2.0*pi); 
//	double z0 = (x==0) * ((y>0)*(pi/2.0)  +  (y<0)*(2.0*pi-pi/2.0));  
	double z1 = 0, z0 = 0;
	if(x!=0)
	{
		z1 = atan2(y,-x); 
		if(z1<0)	z1 += 2.0*pi;
	}
	else
	{
		if     (y>0)	z0 = pi/2.0;
		else if(y<0)	z0 = 3.0*pi/2.0;
	}

	double asp = z1 + z0;   
	double hs = cos(zr)*cos(slop) + sin(zr)*sin(slop)*cos(ar-asp); 
//	hs = (hs + 1.0)/2.0;

	double 	Per1 = 0.6, Per2 = 0.4;	//percentage Per1+Per2=1
	int r,g,b;

//	double Pmin = -0,	 Pmax = 1,		pz = 255.0*(hs-Pmin)/(Pmax-Pmin);
	double 	pz = m_colorRate + Per1*255.0*hs;
//	pz =  max(0,min(255, pz ));

//c = Z2Color(pDoc, pDoc->buf[px][py]);

	r = (int)(pz + Per2*GetRValue(c));
	g = (int)(pz + Per2*GetGValue(c));
	b = (int)(pz + Per2*GetBValue(c));

	r =  max(0,min(255, r ));
	g =  max(0,min(255, g ));
	b =  max(0,min(255, b ));

	return RGB(b,g,r); 
}

COLORREF CSMS4DCView::IJ2Color(CSMS4DCDoc* pDoc,int i, int j, _int16 min1, _int16 max1) 
{
	_int16 p1 =	pDoc->buf[i][j];

	COLORREF c ;
//	if(p1!=pDoc->m_NoData)
	{
		if(max1 == min1)	c = pDoc->RGBt[0];
		else				
		{
			int p = (int)((255.0*( min(max(p1,min1),max1) - min1))/(max1- min1));	 
			p = min(255,max(0,p));	
			c = pDoc->RGBt[p];
		}
	}
//	else					c = pDoc->RGBt[255];
	if     (p1<=min1)		c = pDoc->RGBt[0];
	else if(p1>=max1)		c = pDoc->RGBt[254];
	return c;
}

HBITMAP CSMS4DCView::Draw_hBitmap3D(CSMS4DCDoc* pDoc)
{
	HBITMAP hRet = NULL;
	HDC hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	if (hScrDC)
	{
		HDC hMemDC = CreateCompatibleDC(hScrDC); 
		if (hMemDC)
		{
			int W = pDoc->Width, H = pDoc->Height;
			////////////////////////////////////////
			HBITMAP hBitmap = CreateCompatibleBitmap(hScrDC, W, H);

			if (hBitmap)
			{
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

			//	RECT rect = CRect(0, 0, W, H);	
			//	::SetBkColor(hMemDC, GetSysColor(COLOR_WINDOW));
			//	::ExtTextOut(hMemDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);

				COLORREF c, *data1 = new COLORREF[W*H]; 
				_int16 m_MinValue1 = (_int16)max((double)pDoc->bufMin, m_MinValue);
				_int16 m_MaxValue1 = (_int16)min((double)pDoc->bufMax, m_MaxValue);
				for (int j=0;j<H;j++)
				{
					for (int i=0;i<W;i++)
					{
						c = IJ2Color(pDoc, i, j, m_MinValue1, m_MaxValue1);
						data1[j + i*H] = hillshade_new(pDoc, i, j, W, H, c);	
					}
				}

				unsigned short BitsPixel = 32;
				BITMAPFILEHEADER * pbmfh ;
				BITMAPINFO       * pbmi ;
				int              cxDib, cyDib ;
					
				// Load the entire DIB into memory
				pbmfh = (struct tagBITMAPFILEHEADER *)malloc (1078) ;
				pbmfh->bfType = 'BM';
				pbmfh->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); 
				pbmfh->bfSize = (H * W * BitsPixel / 8) + pbmfh->bfOffBits; 

				pbmi  = (BITMAPINFO *) (pbmfh + 1) ;
				pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				pbmi->bmiHeader.biWidth = W ;
				pbmi->bmiHeader.biHeight = H ;
				pbmi->bmiHeader.biPlanes = 1;
				pbmi->bmiHeader.biBitCount = BitsPixel;
				pbmi->bmiHeader.biCompression = BI_RGB;
				pbmi->bmiHeader.biSizeImage = (H * W * BitsPixel / 8) ;
				pbmi->bmiHeader.biClrImportant = 0;

				// Get the DIB width and height
				if (pbmi->bmiHeader.biSize == sizeof (BITMAPCOREHEADER))
				{
					cxDib = ((BITMAPCOREHEADER *) pbmi)->bcWidth ;		
					cyDib = ((BITMAPCOREHEADER *) pbmi)->bcHeight ;
				}
				else
				{
					cxDib = pbmi->bmiHeader.biWidth ;					
					cyDib = abs (pbmi->bmiHeader.biHeight) ;
				}

				if (pbmfh)
				{
					SetDIBitsToDevice(	hMemDC,		  // MemDC.m_hDC, 
										0,0,		  // xDst, yDst
										cxDib,cyDib,  // cxSrc, cySrc
										0,0,          // xSrc, ySrc
										0,            // first scan line
										cyDib,        // number of scan lines
										data1,  pbmi,  DIB_RGB_COLORS) ;
				}
				free (pbmfh) ;
				delete [] data1;

				CDC MemDC;
				MemDC.Attach(hMemDC); 

				///////////////////Vector Polygon////////////////////////
				if (m_POLYnum>=1)
					for (int i=0;i<m_POLYnum;i++)	DrawVector(&MemDC, m_POLY[i].PathNameVec,m_POLY[i].nWidthVec,m_POLY[i].crColorVec,m_POLY[i].nStyleVec,	m_POLY[i].nModeVec,m_POLY[i].flColorVec,m_POLY[i].alphaVec) ;
				///////////////////Overlay//////////////////////////////
				if(m_OverlayFlag)
					OverlayFunction(m_pDocOverlay , m_OverlayFactor , &MemDC);
				/////////////////////////////////////////////////////////
				MemDC.Detach();	MemDC.DeleteDC(); 

				// select the old bitmap back into memory DC and get handle to bitmap
				hRet = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
				SetBitmapDimensionEx(hRet, W, H, NULL);

			}//hBitmap
			DeleteDC(hMemDC); 
			hBitmap = NULL;
		}//hMemDC
	}//hScrDC
	DeleteDC(hScrDC);

/*
	for(int i=0;i<256;i++)
	{
		int min1 = pDoc->bufMin;
		int max1 = pDoc->bufMax;
		double z = min1 + i*(max1-min1)/255.0;
		pDoc->RGBt[i] = Z2Color(pDoc, z); 	
	}
*/

	return hRet;
}

HBITMAP CSMS4DCView::Draw_hBitmap(CSMS4DCDoc* pDoc)
{
	if(m_3D)	m_hBitmap = Draw_hBitmap3D(pDoc);
	else		m_hBitmap = Draw_hBitmap2D(pDoc);
	return m_hBitmap;
}

void CSMS4DCView::OnToolsColormap3d() 
{
	m_3D = !m_3D;
	CSMS4DCDoc* pDoc = (CSMS4DCDoc*)GetDocument();
	m_hBitmap = Draw_hBitmap(pDoc);
	Invalidate(false);
}
void CSMS4DCView::OnUpdateToolsColormap3d(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_3D);	
}

void CSMS4DCView::OnToolsColormapNegative() 
{
	m_ColorMapNegative = !m_ColorMapNegative;

	CSMS4DCDoc* pDoc = GetDocument();
	{
		for (int i=0;i<256;i++)
		{
			COLORREF c = pDoc->RGBt[i];
			int r = GetRValue(c);
			int g = GetGValue(c);
			int b = GetBValue(c);

			pDoc->RGBt[i] = RGB(255-r, 255-g, 255-b);
		}
		UpDate_hBitmap(pDoc);
		Invalidate();
		InvalidateLegend();	//97/12/26	
	}	
}
void CSMS4DCView::OnUpdateToolsColormapNegative(CCmdUI* pCmdUI) //97/12/26
{
	pCmdUI->SetCheck(m_ColorMapNegative ? 1 : 0);
}


void CSMS4DCView::OnShowLegend() 
{
	if(m_LegendFlag)
	{	
		m_pLegendDLGModeless->PostNcDestroy();
		m_pLegendDLGModeless = NULL;
	//	m_pLegendDLGModeless->OnClose();
		m_LegendFlag = FALSE;
		return;
	}
	if(!m_LegendFlag)	m_LegendFlag = TRUE;

	m_pLegendDLGModeless = new CLegendDLG;
	if (!m_pLegendDLGModeless)	return;

	CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument() ;
	m_pLegendDLGModeless->m_ColorMapNegative  = m_ColorMapNegative;		//97/12/26
	m_pLegendDLGModeless->m_title        = _Z("Altitude (m)");
	m_pLegendDLGModeless->m_MinValue     = m_MinValue;
	m_pLegendDLGModeless->m_MaxValue     = m_MaxValue;
	m_pLegendDLGModeless->m_colormaptype = pDoc->colormaptype;
	m_pLegendDLGModeless->m_colorRate    = m_colorRate;
//	m_pLegendDLGModeless->Create(IDD_LegendDLG,0);
	m_pLegendDLGModeless->Create(IDD_LegendDLG,this);
	m_pLegendDLGModeless->ShowWindow(SW_SHOW);
	SetFocus();
}
void CSMS4DCView::OnUpdateShowLegend(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LegendFlag ? 1 : 0);
}

void CSMS4DCView::InvalidateLegend(void)	//97/12/26	
{
//	if(m_pLegendDLGModeless)
	if(m_LegendFlag)
	{
		m_pLegendDLGModeless->PostNcDestroy();
		m_pLegendDLGModeless = NULL;			//97/12/26
//		m_pLegendDLGModeless->OnClose();
		m_LegendFlag = FALSE;
		OnShowLegend();
	}
}

//Generating color-relief	// no used
COLORREF CSMS4DCView::Z2Color(CSMS4DCDoc* pDoc, double z) 	
{
	if(z==pDoc->m_NoData)	return pDoc->RGBt[255];
	else 
	{	
		double z1, z2;	
		int r, r1, r2, g, g1, g2, b, b1, b2;

		if(z<1800)	
		{
			z1 = 0;		 z2 = 1800;
			r1 = 46;	 r2 = 251;
			g1 = 154;	 g2 = 255;
			b1 = 88;	 b2 = 128;
		}		
		else if(z>=1800 && z<2800)	
		{
			z1 = 1800;	 z2 = 2800;
			r1 = 251;	 r2 = 224;
			g1 = 255;	 g2 = 108;
			b1 = 128;	 b2 = 31;
		}	
		else if(z>=2800 && z<3500)	
		{
			z1 = 2800;	 z2 = 3500;
			r1 = 224;	 r2 = 200;
			g1 = 108;	 g2 = 55;
			b1 = 31;	 b2 = 55;
		}
		else if(z>=3500)	
		{
			z1 = 3500;	 z2 = 4000;
			r1 = 200;	 r2 = 215;
			g1 = 55;	 g2 = 244;
			b1 = 55;	 b2 = 244;
		}
		r = (int)(r1 + (r2-r1)*(z-z1)/(z2-z1));
		g = (int)(g1 + (g2-g1)*(z-z1)/(z2-z1));
		b = (int)(b1 + (b2-b1)*(z-z1)/(z2-z1));

		return RGB(r, g, b);
	}
	return 0;
}

double CSMS4DCView::LatLon2Hg_n(double lat_deg,double lon_deg) 
{
	CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument();
	double x_en,y_en;

lon_deg = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon_deg,pDoc->TileX);
	y_en = lat_deg + pDoc->m_Resolution_y/2.0;
	x_en = lon_deg + pDoc->m_Resolution_x/2.0;

	double ypm= 1.0+(y_en - pDoc->m_Lower_left_y)/ pDoc->m_Resolution_y;
	double xpm= 1.0+(x_en - pDoc->m_Lower_left_x)/ pDoc->m_Resolution_x;
	double yps = ypm - 600.0*(pDoc->TileY-1.0);
	double xps = xpm - 600.0*(pDoc->TileX-1.0);
	double z = RoundBUF_Hg_n(xps, yps);
	return z;
}
double CSMS4DCView::RoundBUF_Hg_n(double xps,double yps) 
{
	while(xps<0)	 {	OnWest();		xps = xps + 600;	}
	while(xps>1200-1){	OnEast();		xps = xps - 600;	}
	while(yps<0)	 {	OnSouth();		yps = yps + 600;	}
	while(yps>1200-1){	OnNorth();		yps = yps - 600;	}

	CSMS4DCDoc* pDoc=(CSMS4DCDoc*)GetDocument() ;
	int i1 = int(xps);				int j1 = int(yps);
	i1 = max(min(i1,1200-1),0);		j1 = max(min(j1,1200-1),0);
	int i2 = i1+1;					int j2 = j1+1;

	double h11, h12, h21, h22, hx1, hx2, hy;
	if     ((i1 == (1200-1))&&(j1 == (1200-1)))		hy = pDoc->buf[j1][i1];
	else if((i1 == (1200-1))&&(j1 < (1200-1)))
	{
		h11 = pDoc->buf[j1][i1]; 	h12 = pDoc->buf[j2][i1];	hy  = h11 +(yps-j1)*(h12-h11)/(j2-j1);
	}
	else if((i1 < (1200-1))&&(j1 == (1200-1)))
	{
		h11 = pDoc->buf[j1][i1]; 	h21 = pDoc->buf[j1][i2];	hy  = h11 +(xps-i1)*(h21-h11)/(i2-i1);
	}
	else
	{
		h11 = pDoc->buf[j1][i1];	h12 = pDoc->buf[j2][i1]; 	h21 = pDoc->buf[j1][i2]; 	h22 = pDoc->buf[j2][i2];
		hx1 = h11 +(xps-i1)*(h21-h11)/(i2-i1); 
		hx2 = h12 +(xps-i1)*(h22-h12)/(i2-i1);	hy  = hx1 +(yps-j1)*(hx2-hx1)/(j2-j1);
	}
	return hy;
}
//98/01/11
void CSMS4DCView::TransparentBlt_AlphaBlend(CDC* dc,    int Left, int Top, int Width, int Height,
											CDC* MemDC, int rL,   int rT,  int rW,    int rH, 
											const COLORREF Color, BYTE Alpha, int bTA)
{
	// msimg32.lib is included		(msimg32.dll)
	BLENDFUNCTION bn;
	bn.BlendOp     = AC_SRC_OVER;
	bn.BlendFlags  = 0;
	bn.SourceConstantAlpha = Alpha; 
	bn.AlphaFormat = 0;

	if     (bTA==0)
		AlphaBlend(dc->m_hDC, Left, Top, Width, Height, MemDC->m_hDC, rL, rT, rW, rH, bn);
	else if(bTA==1)
		TransparentBlt(dc->m_hDC, Left, Top, Width, Height, MemDC->m_hDC, rL, rT, rW, rH, Color);
	else
	{
		CDC		bufDC;		bufDC.CreateCompatibleDC(MemDC);
		CBitmap bitmap;		bitmap.CreateCompatibleBitmap(MemDC, rW, rH);
		bufDC.SelectObject(bitmap);

		bufDC.BitBlt(rL, rT, rW, rH, dc, Left, Top, SRCCOPY);
		TransparentBlt(bufDC, rL, rT, rW, rH, MemDC->m_hDC, rL, rT, rW, rH, Color);
		AlphaBlend(dc->m_hDC, Left, Top, Width, Height, bufDC, rL, rT, rW, rH, bn);
						
		DeleteDC(bufDC.m_hDC);		bufDC.Detach();
		bitmap.DeleteObject();
	}
}

//////////////Monitoring
void CSMS4DCView::OnP1546NetworkprocessorBestserver() 										//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetB = 0;
	OnPropagationmodelsP1546NPBS();
}
void CSMS4DCView::OnUpdateP1546NetworkprocessorBestserver(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningRxBsP15465()  									//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetB = 1;
	OnPropagationmodelsP1546NPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningRxBsP15465(CCmdUI* pCmdUI)  				//98/12/17
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningCoveragezonesP15465() 							//98/12/17 
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetB = 2;
	OnPropagationmodelsP1546NPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningCoveragezonesP15465(CCmdUI* pCmdUI)		//98/12/17
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningLocationzonetdoaP15465()  						//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetB = 3;
	OnPropagationmodelsP1546NPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningLocationzonetdoaP15465(CCmdUI* pCmdUI)	//98/12/17
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}


void CSMS4DCView::OnP1546NetworkprocessorMaximumfieldstrength() 
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetF = 0;
	OnPropagationmodelsP1546NPMFS();
}
void CSMS4DCView::OnUpdateP1546NetworkprocessorMaximumfieldstrength(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningRxMfsP15465() 									//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetF = 1;
	OnPropagationmodelsP1546NPMFS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningRxMfsP15465(CCmdUI* pCmdUI) 				//98/12/17
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningLocationzoneaoaP15465()  						//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetF = 2;
	OnPropagationmodelsP1546NPMFS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningLocationzoneaoaP15465(CCmdUI* pCmdUI) 	//98/12/17
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}


/////////Free Space
void CSMS4DCView::OnFreespaceNetworkprocessorBestserver()									//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetB = 0;
	OnFreespaceNPBS();
}
void CSMS4DCView::OnUpdateFreespaceNetworkprocessorBestserver(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnFreespaceNetworkprocessorMaximumfieldstrength() 						//98/12/17
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetF = 0;
	OnFreespaceNPMFS();
}
void CSMS4DCView::OnUpdateFreespaceNetworkprocessorMaximumfieldstrength(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

////////////////////
void CSMS4DCView::OnMonitoringNetworkplanningCoveragezonesFreespace() 							//99/04/26
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetB = 2;	//Monitoring coverage zones
	OnFreespaceNPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningCoveragezonesFreespace(CCmdUI* pCmdUI) 		//99/04/26
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningLocationzoneaoaFreespace()							//99/04/26
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetF = 2;
	OnFreespaceNPMFS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningLocationzoneaoaFreespace(CCmdUI* pCmdUI)		//99/04/26
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningLocationzonetdoaFreespace()						//99/04/26
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetB = 3;
	OnFreespaceNPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningLocationzonetdoaFreespace(CCmdUI* pCmdUI)	//99/04/26 
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningRxMFSFreespace()									//99/04/26
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetF = 1;
	OnFreespaceNPMFS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningRxMFSFreespace(CCmdUI* pCmdUI)				//99/04/26
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}

void CSMS4DCView::OnMonitoringNetworkplanningRxBSFreespace() 									//99/04/26
{
	((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetB = 1;
	OnFreespaceNPBS();
}
void CSMS4DCView::OnUpdateMonitoringNetworkplanningRxBSFreespace(CCmdUI* pCmdUI) 				//99/04/26
{
	pCmdUI->Enable(m_stBoxPoint != m_enBoxPoint ? 1 : 0 );	
}
