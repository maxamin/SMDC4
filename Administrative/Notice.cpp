// Notice.cpp : implementation file
//

#include "stdafx.h"
#include "Administrative.h"
#include "Notice.h"
#include "AntPattern.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotice dialog


CNotice::CNotice(CWnd* pParent /*=NULL*/)
	: CDialog(CNotice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNotice)
	m_T14 = FALSE;
	m_Admin = _T("");
	//}}AFX_DATA_INIT
}


void CNotice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotice)
	DDX_Control(pDX, IDC_PUBREQ, m_PubReq);
	DDX_Control(pDX, IDC_RESUB, m_IsResub);
	DDX_Control(pDX, IDC_NOTICE_DATE, m_NoticeDate);
	DDX_Control(pDX, IDC_ACTION, m_Action);
	DDX_Check(pDX, IDC_T14, m_T14);
	DDX_Text(pDX, IDC_ADMIN, m_Admin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNotice, CDialog)
	//{{AFX_MSG_MAP(CNotice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotice message handlers

void CNotice::OnOK() 
{

	if(!m_SrvType.CollateNoCase("F")) Fixed();
	if(!m_SrvType.CollateNoCase("MT"))	LandMobile();
	if(!m_SrvType.CollateNoCase("B")) Broadcast();
	if(!m_SrvType.CollateNoCase("Allotment")) Allotment();
	if(!m_SrvType.CollateNoCase("Contour")) Contour();

	CDialog::OnOK();
}

void CNotice::Fixed()
{
	if(/*m_Fragment.GetWindowTextLength() &&*/ m_Action.GetWindowTextLength())
	{
		CString OutFile, Country, Fragment, SQL, FValue, StClass, AntDir, NoticeDate, Pol, AntCatID, NoticeType;
		char buf[100];
		CDatabase m_DB;
		m_DB.Open(m_CDBSTR, FALSE, FALSE, _T("ODBC;"), FALSE);
		CRecordset Stations, EffHgt, AntPatt;
		Stations.m_pDatabase=&m_DB;
		int St;		//Station counter
		CDBVariant FVal;
		UpdateData();
		OutFile=GetCommandLine();
		int Place=OutFile.ReverseFind('\\')-1;
		OutFile.Delete(0);
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		Place=OutFile.ReverseFind('\\')+1;
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		OutFile+=_T("reports\\");
		if(m_StID==-1)
		{
			SQL.Format(_T("'F' and equipment.eqcatid=eqcat.eqcatid and antenna.antcatid=antcat.antcatid and Station.LicID=%ld"),m_LicID);
			SQL=_T(" Equipment.EqID = Antenna.EqID and [Station].[StID]=[Equipment].[StID] AND License.SrvID=")+SQL;
			SQL=_T("WHERE License.LicID = Station.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and ")+SQL;
			SQL=_T("SELECT* FROM Equipment,EqCat ,Antenna,AntCat, Frequency ,Owner , License, Station ")+SQL;
			OutFile+=_T("Lic");
		}
		else
		{
			SQL.Format(_T("and equipment.eqcatid=eqcat.eqcatid and antenna.antcatid=antcat.antcatid and License.SrvID = 'F' and Station.StID=%ld"),m_StID);
			SQL=_T(" Equipment.EqID = Antenna.EqID and [Station].[StID]=[Equipment].[StID] and provisions.provision=station.provision ")+SQL;
			SQL=_T("WHERE License.LicID = Station.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and ")+SQL;
			SQL=_T("SELECT* FROM Equipment,EqCat ,Antenna,AntCat, Frequency ,Owner , License, Station, provisions ")+SQL;
			OutFile+="St";
		}

		Stations.Open(CRecordset::snapshot, SQL);
		if(Stations.GetRecordCount()==0)
		{
Err_FX:		AfxMessageBox(_Z("Data for this Notice is not complete!"));
			m_DB.Close();
			return;
		}
		m_NoticeDate.GetWindowText(NoticeDate);
		m_Action.GetWindowText(FValue);
		if(m_StID==-1)
			ltoa(m_LicID,buf,10);
		else
			ltoa(m_StID,buf,10);
		OutFile+=buf;
		OutFile+=FValue+NoticeDate;
		OutFile+=_T(".txt");
		FILE *output=fopen(OutFile,_T("wt"));
		fprintf(output,_T("<HEAD>\n"));
		Stations.GetFieldValue(97,Country);
		fprintf(output,_T("t_adm=%s\n"),Country);
		m_NoticeDate.GetWindowText(FValue);
		fprintf(output,_T("t_d_sent=%s\n"),FValue);
		fprintf(output,_T("</HEAD>\n"));
		for(St=0;!Stations.IsEOF();St++)
		{
//
//		Fixed transmitters			T11
//
			fprintf(output,_T("<NOTICE>\n"));
			Stations.GetFieldValue(_T("ClassStation"),FValue);
			StClass=FValue;
			Stations.GetFieldValue(_T("Fragment"),Fragment);
			fprintf(output,_T("t_fragment=%s\n"),Fragment);
			Stations.GetFieldValue(_T("NoticeType"),NoticeType);
			if(NoticeType.Left(1)==_T("G"))
			{
				m_IsResub.GetWindowText(FValue);
				if(FValue==_T("Yes"))
					fprintf(output,"t_is_resub=TRUE\n");
				else
					fprintf(output,"t_is_resub=FALSE\n");
			}
			if(NoticeType.Right(2)==_T("14"))
			{
				fprintf(output,_T("t_notice_type=%s\n"), NoticeType);
				if(!Fragment.Compare(_T("NTFD_RR")))
					fprintf(output,"t_prov=RR11.17\n");
				if(!Fragment.Compare("Req_agrt"))
					fprintf(output,"t_prov=RR9.21\n");
				if(!Fragment.Compare("GE06L"))
					fprintf(output,"t_prov=GE06-4.2\n");
			}
			else
			{
				fprintf(output,_T("t_notice_type=%s\n"), NoticeType);
				if(!Fragment.Compare(_T("NTFD_RR")))
					fprintf(output,"t_prov=RR11.2\n");
				if(!Fragment.Compare("Req_agrt"))
					fprintf(output,"t_prov=RR9.21\n");
				if(!Fragment.Compare("GE06L"))
					fprintf(output,"t_prov=GE06-4.2\n");
			}
			m_Action.GetWindowText(FValue);
			fprintf(output,"t_action=%s\n",FValue);
			if(FValue=="ADD")
			{
				Stations.GetFieldValue("AdmRefID",FValue);
				if(!FValue.IsEmpty()) fprintf(output,"t_adm_ref_id=%s\n",FValue);
			}
			else if(FValue=="MODIFY")
			{
					CString Rep;
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					Stations.GetFieldValue("trgLon",FValue);
					int d,m,s;
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target longitude missing,");
					Stations.GetFieldValue("trgLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target latitude missing,");
					Stations.GetFieldValue("trgFrequency",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
					else		Rep+=_Z("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_FX;
					}
			}
			if(FValue.Compare("SUPPRESS") && FValue.Compare("WITHDRAW"))
			{
				Stations.GetFieldValue("Frequency",FVal);
				fprintf(output,"t_freq_assgn=%lf\n",FVal.m_dblVal/1000000.);
				Stations.GetFieldValue("RefFreq",FVal);
				if(FVal.m_dblVal>0) fprintf(output,"t_freq_carr=%lf\n",FVal.m_dblVal/1000000.);
				Stations.GetFieldValue("OpDate",FVal);
				fprintf(output,"t_d_inuse=%4d-%02d-%02d\n",FVal.m_pdate->year,FVal.m_pdate->month,FVal.m_pdate->day);
				Stations.GetFieldValue("CallSign",FValue);
				if(!(FValue.IsEmpty())) fprintf(output,"t_call_sign=%s\n",(LPCTSTR)FValue);
				if(NoticeType.Right(2)!=_T("14"))
				{
					Stations.GetFieldValue("SiteID",FValue);
					if(!FValue.IsEmpty())  fprintf(output,"t_station_id=%s\n",FValue);
					Stations.GetFieldValue("SiteName",FValue);
					fprintf(output,"t_site_name=%s\n",(LPCTSTR)FValue);
				}
				Stations.GetFieldValue("EmissionCl",FValue);
				fprintf(output,"t_emi_cls=%s\n",(LPCTSTR)FValue);
				Stations.GetFieldValue("BandWidth",FVal);
				fprintf(output,"t_bdwdth_cde=%s\n",BandWidthCode((float)FVal.m_dblVal));
				if(NoticeType.Left(1)!=_T("T"))
				{
					m_PubReq.GetWindowText(FValue);
					if(FValue==_T("Yes"))
						fprintf(output,"t_is_pub_req=TRUE\n");
					else
						fprintf(output,"t_is_pub_req=FALSE\n");
					Stations.GetFieldValue("SystemType1",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_system_type=%s\n",(LPCTSTR)FValue);
					Stations.GetFieldValue("SystemType2",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_system_type=%s\n",(LPCTSTR)FValue);
				}
				fprintf(output,"t_stn_cls=%s\n",StClass.Left(2));
				Stations.GetFieldValue("NatServ",FValue);
				fprintf(output,"t_nat_srv=%s\n",(LPCTSTR)FValue.Left(2));
				if(Fragment!=_T("Req_agrt"))
				{
					Stations.GetFieldValue("HourFrom",FValue);
					fprintf(output,"t_op_hh_fr=%s\n",(LPCTSTR)FValue);
						Stations.GetFieldValue("HourTo",FValue);
					fprintf(output,"t_op_hh_to=%s\n",(LPCTSTR)FValue);
					Stations.GetFieldValue("AddrCode",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_addr_code=%s\n",FValue);
					Stations.GetFieldValue("OpAgency",FValue);
					if(!(FValue.IsEmpty())) fprintf(output,"t_op_agcy=%s\n",(LPCTSTR)FValue.Left(3));
				}
				CRecordset Coord;
				CString CoordSQL,Adm,FreqID;
				Coord.m_pDatabase=&m_DB;
				Stations.GetFieldValue(_T("FreqID"),FreqID);
				if(NoticeType.Right(2)!=_T("14"))
				{
					Stations.GetFieldValue("HeightASL",FVal);
					fprintf(output,"t_site_alt=%ld\n",FVal.m_lVal);
					Stations.GetFieldValue(133,FValue);
					fprintf(output,"t_ctry=%s\n",FValue);
					Stations.GetFieldValue("GeoLon",FVal);
					int d,m,s;
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
					Stations.GetFieldValue("GeoLat",FVal);
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
				}
				else
				{
/*					CRecordset Receivers;
					CString RSQL;
					Receivers.m_pDatabase=&m_DB;
					RSQL.Format(_T("Select * from link where TXID=%s"),FreqID);
					Receivers.Open(CRecordset::snapshot,RSQL);
					if(Receivers.GetRecordCount()>0)
					{
						Receivers.GetFieldValue(_T("GeoType"),FValue);
						fprintf(output,"t_geo_type=%s\n",FValue);
						if(FValue==_T("ZONE"))
						{
							Receivers.GetFieldValue("zone",FValue);
							fprintf(output,"t_zone_id=%s\n",FValue);
						}
					}
					Receivers.Close();*/
					Stations.GetFieldValue("AreaOfTrans",FValue);
					if(FValue.IsEmpty())
					{
						fprintf(output,"t_geo_type=CIRCLE\n");
						Stations.GetFieldValue("GeoLon",FVal);
						int d,m,s;
						Coord2DMS(&d,&m,&s,FVal.m_dblVal);
						fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
						Stations.GetFieldValue("GeoLat",FVal);
						Coord2DMS(&d,&m,&s,FVal.m_dblVal);
						fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
						Stations.GetFieldValue("Radius",FVal);
						fprintf(output,"t_radius=%ld\n",FVal.m_lVal);
					}
					else
					{
						fprintf(output,"t_geo_type=ZONE\n");
						fprintf(output,"t_zone_id=%s\n",FValue);
					}
				}
				CoordSQL.Format(_T("select * from Coord where agree_st like 'O%%' and freq_id=%s"),FreqID);
				Coord.Open(CRecordset::snapshot,CoordSQL);
				if(Coord.GetRecordCount()>0)
				{
					fprintf(output,"<COORD>\n");
					while(!Coord.IsEOF())
					{
						Coord.GetFieldValue(_T("adm"),Adm);
						fprintf(output,_T("t_adm=%s\n"),Adm);
						Coord.MoveNext();
					}
					fprintf(output,"</COORD>\n");
				}
				Coord.Close();
				fprintf(output,"<ANTENNA>\n");
				if(NoticeType.Left(1)==_T("G"))
				{
					Stations.GetFieldValue("MaxEffHght",FVal);
					fprintf(output,"t_eff_hgtmax=%d\n",FVal.m_iVal);
				}
				Stations.GetFieldValue("PowerType",FValue);
				if(!(FValue.IsEmpty())) fprintf(output,"t_pwr_xyz=%s\n",FValue.Left(1));
				Stations.GetFieldValue("Pwr2Ant",FVal);
				fprintf(output,"t_pwr_ant=%lf\n",10.0*log10(FVal.m_dblVal));
				
				Stations.GetFieldValue("RadPwr",FVal);
				fprintf(output,"t_pwr_dbw=%lf\n",10.0*log10(FVal.m_dblVal));
				Stations.GetFieldValue("RadPowerType",FValue);
				if(!(FValue.IsEmpty())) fprintf(output,"t_pwr_eiv=%s\n",FValue.Left(1));

				if(NoticeType.Right(2)!=_T("14"))
				{
					Stations.GetFieldValue("AntDir",FValue);
					fprintf(output,"t_ant_dir=%s\n",(FValue==_T("N")?_T("ND"):_T("D")));
					AntDir=(FValue==_T("N")?_T("ND"):_T("D"));
					if(AntDir==_T("D"))
					{
						Stations.GetFieldValue("AzimTo",FValue);
						Stations.GetFieldValue("Azimuth",FVal);
						if(atof(FValue)!=0)
						{
							fprintf(output,"t_azm_fr=%lf\n",FVal.m_dblVal);
							fprintf(output,"t_azm_to=%s\n",FValue);
						}
						else
						{
							fprintf(output,"t_azm_max_e=%lf\n",FVal.m_dblVal);
						}
						Stations.GetFieldValue("BeamWidthH",FVal);
						fprintf(output,"t_bmwdth=%lf\n",FVal.m_dblVal);
					}
					Stations.GetFieldValue("Elevation",FVal);
					fprintf(output,"t_elev=%lf\n",FVal.m_dblVal);
					Stations.GetFieldValue("Pol",FVal);
					Pol=FVal.m_pstring->Left(1);
					fprintf(output,"t_polar=%s\n",Pol);
					Stations.GetFieldValue("AntHeightAGL",FVal);
					fprintf(output,"t_hgt_agl=%ld\n",(long)FVal.m_dblVal);
					Stations.GetFieldValue("GainType",FValue);
					if(!FValue.IsEmpty())	fprintf(output,"t_gain_type=%s\n",FValue);
					Stations.GetFieldValue("Gain",FVal);
					fprintf(output,"t_gain_max=%lf\n",FVal.m_dblVal);
				}

/////////////////////////////////////
			if(NoticeType.Left(1)==_T("G"))
			{
				if(NoticeType.Right(2)!=_T("14"))
				{
					fprintf(output,"<ANT_HGT>\n");
					EffHgt.m_pDatabase=&m_DB;
					Stations.GetFieldValue("AntID",FVal);
					long AntID=FVal.m_lVal, height;
					double azm;
					bool NoData;
					SQL.Format("Select * from AntHgt where AntID=%ld order by azm",AntID);
					EffHgt.Open(CRecordset::snapshot, SQL);
					while(!EffHgt.IsEOF())
					{
						EffHgt.GetFieldValue("Azm",FVal);
						azm=FVal.m_dblVal;
						if(azm==((int)(azm/10))*10)
						{
							EffHgt.GetFieldValue("EffHgt",FVal);
							height=FVal.m_lVal;							
							fprintf(output,"t_eff_hgt@azm%d = %ld\n",(int)azm,height);
							NoData=false;
						}
						EffHgt.MoveNext();
					}
					EffHgt.Close();
					fprintf(output,"</ANT_HGT>\n");
					if(NoData)
					{
						AfxMessageBox(_Z("No effective height available!"));
						Stations.Close();
						m_DB.Close();
						return;
					}
				}
				double Patt[2][360]={0.0}; //,Patt2[2][360]={0.0};
				int i;
				AntPatt.m_pDatabase=&m_DB;
				Stations.GetFieldValue(_T("AntCatID"),AntCatID);
				i=0;
				if(Pol!=_T("V")) 
				{
					fprintf(output,_T("<ANT_DIAGR_H>\n"));
					SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%s order by azm"),AntCatID);
					AntPatt.Open(CRecordset::snapshot, SQL);
					while(!AntPatt.IsEOF())
					{
						double azm, attn;
						AntPatt.GetFieldValue(_T("Azm"),FVal);
						Patt[0][i]=azm=FVal.m_dblVal;
						AntPatt.GetFieldValue(_T("Attn"),FVal);
						Patt[1][i]=attn=FVal.m_dblVal;
						AntPatt.MoveNext();
						i++;
					}
					AntPatt.Close();
					if(i<360)
					{
//  interpolation
						double PatternTmp[361],AngleTmp[361];
						Patt[0][i] = 360;
						Patt[1][i] = Patt[1][0];

						int m_NUM = 360; 
						for (int j=0;j<m_NUM;j++)
						{
							AngleTmp[j]=j;
							PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
						}
						PatternTmp[360]=PatternTmp[0];
						AngleTmp[360]=360;
						for(i=0;i<360;i++)
						{
							Patt[0][i]=AngleTmp[i];
							Patt[1][i]=PatternTmp[i];
						}
					}
////////////////
					for(i=0;i<360;i+=10)
						fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
					fprintf(output,_T("</ANT_DIAGR_H>\n"));
				}
				i=0;
				if(Pol!=_T("H")) 
				{
					fprintf(output,_T("<ANT_DIAGR_V>\n"));
					SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%s order by azm"),AntCatID);
					AntPatt.Open(CRecordset::snapshot, SQL);
					while(!AntPatt.IsEOF())
					{
						double azm, attn;
						AntPatt.GetFieldValue(_T("Azm"),FVal);
						Patt[0][i]=azm=FVal.m_dblVal;
						AntPatt.GetFieldValue(_T("Attn"),FVal);
						Patt[1][i]=attn=FVal.m_dblVal;
						AntPatt.MoveNext();
						i++;
					}
					AntPatt.Close();
					if(i<360)
					{
//  interpolation
						double PatternTmp[361],AngleTmp[361];
						Patt[0][i] = 360;
						Patt[1][i] = Patt[1][0];

						int m_NUM = 360; 
						for (int j=0;j<m_NUM;j++)
						{
							AngleTmp[j]=j;
							PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
						}
						PatternTmp[360]=PatternTmp[0];
						AngleTmp[360]=360;
						for(i=0;i<360;i++)
						{
							Patt[0][i]=AngleTmp[i];
							Patt[1][i]=PatternTmp[i];
						}
					}
////////////////
					for(i=0;i<360;i+=10)
						fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
					fprintf(output,_T("</ANT_DIAGR_V>\n"));
				}
			} // if G11
/////////////////////////////////////
				
				CRecordset Receivers;
				CString RSQL;
				Receivers.m_pDatabase=&m_DB;
				//Stations.GetFieldValue(_T("FreqID"),FreqID);
				RSQL.Format(_T("Select * from link where TXID=%s"),FreqID);
				Receivers.Open(CRecordset::snapshot,RSQL);
				if(Receivers.GetRecordCount()>0 && NoticeType.Right(2)!=_T("14"))
					while(true)
					{
						if(Receivers.IsEOF()) break;
						fprintf(output,"<RX_STATION>\n");
						Receivers.GetFieldValue(_T("GeoType"),FValue);
						fprintf(output,"t_geo_type=%s\n",FValue);
						if(FValue==_T("CIRCLE"))
						{
							int d,m,s;
							Receivers.GetFieldValue("Radius",FVal);
							fprintf(output,"t_radius=%ld\n",FVal.m_lVal);
							Receivers.GetFieldValue("RecLat",FValue);
							Coord2DMS(&d,&m,&s,atof(FValue));
							fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
							Receivers.GetFieldValue("RecLon",FValue);
							Coord2DMS(&d,&m,&s,atof(FValue));
							fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
							//Receivers.GetFieldValue("Country",FValue);
							//fprintf(output,"t_ctry=%s\n",FValue);
						}
						if(FValue==_T("POINT"))
						{
							CString RecID,Field,SQL;
							Receivers.GetFieldValue((short)0,RecID);
							SQL.Format(_T(" from link,Frequency, Equipment, Station where receiverID=%s"), RecID);
							SQL=_T("Select sitename, geolat, geolon, station.country ")+SQL;
							SQL=SQL+ _T(" and link.rxid=frequency.freqid and frequency.eqid=equipment.eqid and equipment.stid=station.stid");
							CRecordset Recs;
							Recs.m_pDatabase=&m_DB;
							Recs.Open(CRecordset::snapshot,SQL);
							if(Recs.GetRecordCount()>0)
							{
								int d,m,s;
								Recs.GetFieldValue(1,Field);
								Coord2DMS(&d,&m,&s,atof(Field));
								fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
								Recs.GetFieldValue(2,Field);
								Coord2DMS(&d,&m,&s,atof(Field));
								fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
								Recs.GetFieldValue(3,Field);
								fprintf(output,_T("t_ctry=%s\n"),Field);
								Recs.GetFieldValue((short)0,Field);
								fprintf(output,_T("t_site_name=%s\n"),Field);
							}
							Recs.Close();
						}
						if(FValue==_T("MULTIPOINT"))
						{
							for(int i=1;i<=6;i++)
							{
								CString LatName,Lat,LonName,Lon;
								int d,m,s;
								LatName.Format(_T("lat%d"),i);
								LonName.Format(_T("lon%d"),i);
								Receivers.GetFieldValue(LatName,Lat);
								Receivers.GetFieldValue(LonName,Lon);
								if(atof(Lat)==0 && atof(Lon)==0) break;
								fprintf(output,"<POINT>\n");
								Coord2DMS(&d,&m,&s,atof(Lat));
								fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
								Coord2DMS(&d,&m,&s,atof(Lon));
								fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
								fprintf(output,"</POINT>\n");
							}
						}
						Receivers.GetFieldValue(_T("NoiseTemp"),FValue);
						fprintf(output,"t_noise_temp=%s\n",FValue);
						fprintf(output,"</RX_STATION>\n");
						Receivers.MoveNext();
					}
					Receivers.Close();
					fprintf(output,"</ANTENNA>\n");
			}
			else
			{
				Stations.GetFieldValue("Frequency",FVal);
				fprintf(output,"t_trg_freq_assgn=%lf\n",FVal.m_dblVal/1000000.);
				Stations.GetFieldValue("EmissionCl",FValue);
				fprintf(output,"t_trg_emi_cls=%s\n",FValue);
				fprintf(output,"t_trg_stn_cls=%s\n",StClass.Left(2));
				Stations.GetFieldValue("BandWidth",FVal);
				fprintf(output,"t_trg_bdwdth_cde=%s\n",BandWidthCode((float)FVal.m_dblVal));
				Stations.GetFieldValue("HourFrom",FValue);
				fprintf(output,"t_trg_op_hh_fr=%s\n",FValue);
				Stations.GetFieldValue("HourTo",FValue);
				fprintf(output,"t_trg_op_hh_to=%s\n",FValue);
				Stations.GetFieldValue("GeoLon",FVal);
				int d,m,s;
				Coord2DMS(&d,&m,&s,FVal.m_dblVal);
				fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
				Stations.GetFieldValue("GeoLat",FVal);
				Coord2DMS(&d,&m,&s,FVal.m_dblVal);
				fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
			}
			fprintf(output,"</NOTICE>\n");

			Stations.MoveNext();
		}//end for
		Stations.Close();
		fprintf(output,"<TAIL>\n");
		fprintf(output,"t_num_notices=%d\n", St);
		fprintf(output,"</TAIL>\n");
		fclose(output);
		ShellExecute(this->m_hWnd,"open",OutFile,NULL,NULL,SW_SHOWNORMAL);
	}//end if
}

void CNotice::LandMobile()
{
	if(/*m_Fragment.GetWindowTextLength() &&*/ m_Action.GetWindowTextLength())
	{
		CString OutFile, Country, NoticeDate, Fragment, SQL, FValue, StClass, AntDir, AntCatID, Pol, NoticeType;
		char buf[100];
		CDatabase m_DB;
		m_DB.Open(m_CDBSTR, FALSE, FALSE, "ODBC;", FALSE);
		CRecordset Stations, EffHgt, AntPatt;
		Stations.m_pDatabase=&m_DB;
		int St=0;		//Station counter
		CDBVariant FVal;
		long AntID;
		bool HeaderDone=false;
		OutFile=GetCommandLine();
		int Place=OutFile.ReverseFind('\\')-1;
		OutFile.Delete(0);
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		Place=OutFile.ReverseFind('\\')+1;
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		OutFile+="reports\\";
		if(m_StID==-1)
		{
			SQL.Format("%ld",m_LicID);
			SQL.Format("\'Land Mobile\' and Station.LicID=%ld",m_LicID);
			SQL=" Equipment.EqID = Antenna.EqID and [Station].[StID]=[Equipment].[StID] AND (SrvType.SrvType)="+SQL;
			SQL="WHERE License.SrvID = SrvType.SrvID and License.LicID = Station.LicID and Admin.ID = License.AdmID and Equipment.EqID = Frequency.EqID and "+SQL;
			SQL="SELECT* FROM Equipment ,Antenna, Frequency ,Admin , License, Station , SrvType "+SQL;
			OutFile+="Lic";
		}
		else
			{
				SQL.Format(_T("and equipment.eqcatid=eqcat.eqcatid and antenna.antcatid=antcat.antcatid and License.SrvID = 'MT' and Station.StID=%ld"),m_StID);
				SQL=_T(" Equipment.EqID = Antenna.EqID and [Station].[StID]=[Equipment].[StID] and provisions.provision=station.provision ")+SQL;
				SQL=_T("WHERE License.LicID = Station.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and ")+SQL;
				SQL=_T("SELECT* FROM Equipment,EqCat ,Antenna,AntCat, Frequency ,Owner , License, Station, provisions ")+SQL;
				OutFile+="St";
			}
		m_NoticeDate.GetWindowText(NoticeDate);
		m_Action.GetWindowText(FValue);
		if(m_StID==-1)
			ltoa(m_LicID,buf,10);
		else
			ltoa(m_StID,buf,10);
		OutFile+=buf;
		OutFile+=FValue+NoticeDate;
		OutFile+=".txt";
		FILE *output=fopen(OutFile,"wt");

		if(m_StTable!="Mobiles")
		{
			Stations.Open(CRecordset::snapshot, SQL);
			if(Stations.GetRecordCount()==0)
			{
Err_FB:			AfxMessageBox(_Z("Data for this Notice is not complete!"));
				m_DB.Close();
				return;
			}
			fprintf(output,"<HEAD>\n");
			Stations.GetFieldValue(97,Country);
			fprintf(output,"t_adm=%s\n",Country);
			m_NoticeDate.GetWindowText(FValue);
			fprintf(output,"t_d_sent=%s\n",FValue);
			fprintf(output,"</HEAD>\n");
			HeaderDone=true;
			for(St=0;!Stations.IsEOF();St++)
			{
	//
	//		Base station		T12
	//
				fprintf(output,"<NOTICE>\n");
				Stations.GetFieldValue("ClassStation",FValue);
				StClass=FValue;
				Stations.GetFieldValue("Fragment",Fragment);
				fprintf(output,"t_fragment=%s\n",Fragment);
				Stations.GetFieldValue(_T("NoticeType"),NoticeType);
				if(NoticeType.Left(1)==_T("G"))
				{
					m_IsResub.GetWindowText(FValue);
					if(FValue==_T("Yes"))
						fprintf(output,"t_is_resub=TRUE\n");
					else
						fprintf(output,"t_is_resub=FALSE\n");
				}
				if(NoticeType.Right(2)==_T("14"))
				{
					fprintf(output,_T("t_notice_type=%s\n"), NoticeType);
					if(!Fragment.Compare(_T("NTFD_RR")))
						fprintf(output,"t_prov=RR11.17\n");
					if(!Fragment.Compare("Req_agrt"))
						fprintf(output,"t_prov=RR9.21\n");
					if(!Fragment.Compare("GE06L"))
						fprintf(output,"t_prov=GE06-4.2\n");
				}
				else
				{
					fprintf(output,_T("t_notice_type=%s\n"), NoticeType);
					if(!Fragment.Compare(_T("NTFD_RR")))
						fprintf(output,"t_prov=RR11.2\n");
					if(!Fragment.Compare("Req_agrt"))
						fprintf(output,"t_prov=RR9.21\n");
					if(!Fragment.Compare("GE06L"))
						fprintf(output,"t_prov=GE06-4.2\n");
				}
				m_Action.GetWindowText(FValue);
				fprintf(output,"t_action=%s\n",FValue);
				if(FValue=="ADD")
				{
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_adm_ref_id=%s\n",FValue);
				}
				else if(FValue=="MODIFY")
				{
					CString Rep;
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					Stations.GetFieldValue("trgLon",FValue);
					int d,m,s;
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target longitude missing,");
					Stations.GetFieldValue("trgLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target latitude missing,");
					Stations.GetFieldValue("trgFrequency",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
					else		Rep+=_Z("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_FB;
					}
				}
				if(FValue.Compare("SUPPRESS") && FValue.Compare("WITHDRAW"))
				{
					Stations.GetFieldValue("Frequency",FVal);
					fprintf(output,"t_freq_assgn=%lf\n",FVal.m_dblVal/1000000.);
					Stations.GetFieldValue("RefFreq",FVal);
					if(FVal.m_dblVal>0) fprintf(output,"t_freq_carr=%lf\n",FVal.m_dblVal/1000000.);
					Stations.GetFieldValue("OpDate",FVal);
					fprintf(output,"t_d_inuse=%4d-%02d-%02d\n",FVal.m_pdate->year,FVal.m_pdate->month,FVal.m_pdate->day);
					Stations.GetFieldValue("CallSign",FValue);
					if(!(FValue.IsEmpty())) fprintf(output,"t_call_sign=%s\n",FValue);
					if(NoticeType.Right(2)!=_T("14"))
					{
						Stations.GetFieldValue("SiteID",FValue);
						if(!FValue.IsEmpty())  fprintf(output,"t_station_id=%s\n",FValue);
						Stations.GetFieldValue("SiteName",FValue);
						fprintf(output,"t_site_name=%s\n",FValue);
					}
					Stations.GetFieldValue("EmissionCl",FValue);
					fprintf(output,"t_emi_cls=%s\n",FValue);
					Stations.GetFieldValue("BandWidth",FVal);
					fprintf(output,"t_bdwdth_cde=%s\n",BandWidthCode((float)FVal.m_dblVal));
					if(NoticeType.Left(1)!=_T("T"))
					{
						m_PubReq.GetWindowText(FValue);
						if(FValue==_T("Yes"))
							fprintf(output,"t_is_pub_req=TRUE\n");
						else
							fprintf(output,"t_is_pub_req=FALSE\n");
						Stations.GetFieldValue("SystemType1",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_system_type=%s\n",(LPCTSTR)FValue);
						Stations.GetFieldValue("SystemType2",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_system_type=%s\n",(LPCTSTR)FValue);
					}
					int d,m,s;
					fprintf(output,"t_stn_cls=%s\n",StClass.Left(2));
					Stations.GetFieldValue("NatServ",FVal);
					fprintf(output,"t_nat_srv=%s\n",FVal.m_pstring->Left(2));
					if(Fragment!=_T("Req_agrt"))
					{
						Stations.GetFieldValue("HourFrom",FValue);
						fprintf(output,"t_op_hh_fr=%s\n",FValue);
							Stations.GetFieldValue("HourTo",FValue);
						fprintf(output,"t_op_hh_to=%s\n",FValue);
						Stations.GetFieldValue("AddrCode",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_addr_code=%s\n",FValue);
						Stations.GetFieldValue("OpAgency",FValue);
						if(!(FValue.IsEmpty())) fprintf(output,"t_op_agcy=%s\n",(LPCTSTR)FValue.Left(3));
					}

					CRecordset Coord;
					CString CoordSQL,Adm,FreqID;
					Coord.m_pDatabase=&m_DB;
					Stations.GetFieldValue(_T("FreqID"),FreqID);
					if(NoticeType.Right(2)!=_T("14"))
					{
						Stations.GetFieldValue("HeightASL",FVal);
						fprintf(output,"t_site_alt=%ld\n",FVal.m_lVal);
						Stations.GetFieldValue(133,FValue);
						fprintf(output,"t_ctry=%s\n",FValue);
						Stations.GetFieldValue("GeoLon",FVal);
						int d,m,s;
						Coord2DMS(&d,&m,&s,FVal.m_dblVal);
						fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
						Stations.GetFieldValue("GeoLat",FVal);
						Coord2DMS(&d,&m,&s,FVal.m_dblVal);
						fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
					}
					else
					{
		/*					CRecordset Receivers;
						CString RSQL;
						Receivers.m_pDatabase=&m_DB;
						RSQL.Format(_T("Select * from link where TXID=%s"),FreqID);
						Receivers.Open(CRecordset::snapshot,RSQL);
						if(Receivers.GetRecordCount()>0)
						{
							Receivers.GetFieldValue(_T("GeoType"),FValue);
							fprintf(output,"t_geo_type=%s\n",FValue);
							if(FValue==_T("ZONE"))
							{
								Receivers.GetFieldValue("zone",FValue);
								fprintf(output,"t_zone_id=%s\n",FValue);
							}
						}
						Receivers.Close();*/
						Stations.GetFieldValue("AreaOfTrans",FValue);
						if(FValue.IsEmpty())
						{
							fprintf(output,"t_geo_type=CIRCLE\n");
							Stations.GetFieldValue("GeoLon",FVal);
							int d,m,s;
							Coord2DMS(&d,&m,&s,FVal.m_dblVal);
							fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
							Stations.GetFieldValue("GeoLat",FVal);
							Coord2DMS(&d,&m,&s,FVal.m_dblVal);
							fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
							Stations.GetFieldValue("Radius",FVal);
							fprintf(output,"t_radius=%ld\n",FVal.m_lVal);
						}
						else
						{
							fprintf(output,"t_geo_type=ZONE\n");
							fprintf(output,"t_zone_id=%s\n",FValue);
						}
					}
					CoordSQL.Format(_T("select * from Coord where agree_st like 'O%%' and freq_id=%s"),FreqID);
					Coord.Open(CRecordset::snapshot,CoordSQL);
					if(Coord.GetRecordCount()>0)
					{
						fprintf(output,"<COORD>\n");
						while(!Coord.IsEOF())
						{
							Coord.GetFieldValue(_T("adm"),Adm);
							fprintf(output,_T("t_adm=%s\n"),Adm);
							Coord.MoveNext();
						}
						fprintf(output,"</COORD>\n");
					}
					Coord.Close();
					fprintf(output,"<ANTENNA>\n");
					if(NoticeType.Left(1)==_T("G"))
					{
						Stations.GetFieldValue("MaxEffHght",FVal);
						fprintf(output,"t_eff_hgtmax=%d\n",FVal.m_iVal);
					}
					Stations.GetFieldValue("PowerType",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_pwr_xyz=%s\n",FValue.Left(1));
					Stations.GetFieldValue("Pwr2Ant",FVal);
					fprintf(output,"t_pwr_ant=%lf\n",10.0*log10(FVal.m_dblVal));
					
					Stations.GetFieldValue("RadPwr",FVal);
					fprintf(output,"t_pwr_dbw=%lf\n",10.0*log10(FVal.m_dblVal));
					Stations.GetFieldValue("RadPowerType",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_pwr_eiv=%s\n",FValue.Left(1));

					if(NoticeType.Right(2)!=_T("14"))
					{
						Stations.GetFieldValue("AntDir",FValue);
						fprintf(output,"t_ant_dir=%s\n",(FValue==_T("N")?_T("ND"):_T("D")));
						AntDir=(FValue==_T("N")?_T("ND"):_T("D"));
						if(AntDir==_T("D"))
						{
							Stations.GetFieldValue("AzimTo",FVal);
							Stations.GetFieldValue("Azimuth",FVal);
							if(atof(FValue)!=0)
							{
								fprintf(output,"t_azm_fr=%lf\n",FVal.m_dblVal);
								fprintf(output,"t_azm_to=%s\n",FValue);
							}
							else
							{
								fprintf(output,"t_azm_max_e=%lf\n",FVal.m_dblVal);
							}
							Stations.GetFieldValue("BeamWidthH",FVal);
							fprintf(output,"t_bmwdth=%lf\n",FVal.m_dblVal);
						}
						Stations.GetFieldValue("Elevation",FVal);
						fprintf(output,"t_elev=%lf\n",FVal.m_dblVal);
						if(NoticeType==_T("G12"))
						{
							Stations.GetFieldValue("Pol",FValue);
							Pol=FValue.Left(1);
							fprintf(output,"t_polar=%s\n",Pol);
						}
						Stations.GetFieldValue("AntHeightAGL",FVal);
						fprintf(output,"t_hgt_agl=%ld\n",(long)FVal.m_dblVal);
						Stations.GetFieldValue("GainType",FValue);
						fprintf(output,"t_gain_type=%s\n",FValue.Left(1));
						Stations.GetFieldValue("Gain",FVal);
						fprintf(output,"t_gain_max=%lf\n",FVal.m_dblVal);
					}

/////////////////////////////////////
				if(NoticeType.Left(1)==_T("G"))
				{

					if(NoticeType.Right(2)!=_T("14"))
					{
						fprintf(output,"<ANT_HGT>\n");
						EffHgt.m_pDatabase=&m_DB;
						Stations.GetFieldValue("AntID",FVal);
						AntID=FVal.m_lVal;
						SQL.Format("Select * from AntHgt where AntID=%ld order by azm",AntID);
						EffHgt.Open(CRecordset::snapshot, SQL);
						double azm;
						long height;
						bool NoData;
						while(!EffHgt.IsEOF())
						{
							EffHgt.GetFieldValue("Azm",FVal);
							azm=FVal.m_dblVal;
							if(azm==((int)(azm/10))*10)
							{
								EffHgt.GetFieldValue("EffHgt",FVal);
								height=FVal.m_lVal;							
								fprintf(output,"t_eff_hgt@azm%d = %ld\n",(int)azm,height);
								NoData=false;
							}
							EffHgt.MoveNext();
						}
						EffHgt.Close();
						fprintf(output,"</ANT_HGT>\n");
						if(NoData)
						{
							AfxMessageBox(_Z("No effective height available!"));
							Stations.Close();
							m_DB.Close();
							return;
						}
					}
					double Patt[2][360]={0.0}; //,Patt2[2][360]={0.0};
					int i;
					AntPatt.m_pDatabase=&m_DB;
					Stations.GetFieldValue(_T("AntCatID"),AntCatID);
					i=0;
					if(Pol!=_T("V")) 
					{
						fprintf(output,_T("<ANT_DIAGR_H>\n"));
						SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%s order by azm"),AntCatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						while(!AntPatt.IsEOF())
						{
							double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=azm=FVal.m_dblVal;
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=attn=FVal.m_dblVal;
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						if(i<360)
						{
	//  interpolation
							double PatternTmp[361],AngleTmp[361];
							Patt[0][i] = 360;
							Patt[1][i] = Patt[1][0];

							int m_NUM = 360; 
							for (int j=0;j<m_NUM;j++)
							{
								AngleTmp[j]=j;
								PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
							}
							PatternTmp[360]=PatternTmp[0];
							AngleTmp[360]=360;
							for(i=0;i<360;i++)
							{
								Patt[0][i]=AngleTmp[i];
								Patt[1][i]=PatternTmp[i];
							}
						}
	////////////////
						for(i=0;i<360;i+=10)
							fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
						fprintf(output,_T("</ANT_DIAGR_H>\n"));
					}
					i=0;
					if(Pol!=_T("H")) 
					{
						fprintf(output,_T("<ANT_DIAGR_V>\n"));
						SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%s order by azm"),AntCatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						while(!AntPatt.IsEOF())
						{
							double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=azm=FVal.m_dblVal;
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=attn=FVal.m_dblVal;
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						if(i<360)
						{
	//  interpolation
							double PatternTmp[361],AngleTmp[361];
							Patt[0][i] = 360;
							Patt[1][i] = Patt[1][0];

							int m_NUM = 360; 
							for (int j=0;j<m_NUM;j++)
							{
								AngleTmp[j]=j;
								PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
							}
							PatternTmp[360]=PatternTmp[0];
							AngleTmp[360]=360;
							for(i=0;i<360;i++)
							{
								Patt[0][i]=AngleTmp[i];
								Patt[1][i]=PatternTmp[i];
							}
						}
	////////////////
						for(i=0;i<360;i+=10)
							fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
						fprintf(output,_T("</ANT_DIAGR_V>\n"));
					}
				}//if G12 or G14
/////////////////////////////////////
					
					CRecordset Receivers;
					CString RSQL;
					Receivers.m_pDatabase=&m_DB;
					//Stations.GetFieldValue(_T("FreqID"),FreqID);
					RSQL.Format(_T("Select * from link where TXID=%s"),FreqID);
					Receivers.Open(CRecordset::snapshot,RSQL);
					if(Receivers.GetRecordCount()>0 && !m_T14)
						while(true)
						{
							if(Receivers.IsEOF()) break;
							fprintf(output,"<RX_STATION>\n");
							Receivers.GetFieldValue(_T("GeoType"),FValue);
							fprintf(output,"t_geo_type=%s\n",FValue);
							if(FValue==_T("CIRCLE"))
							{
								Receivers.GetFieldValue("Radius",FVal);
								fprintf(output,"t_radius=%ld\n",FVal.m_lVal);
								Receivers.GetFieldValue("RecLat",FValue);
								Coord2DMS(&d,&m,&s,atof(FValue));
								fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
								Receivers.GetFieldValue("RecLon",FValue);
								Coord2DMS(&d,&m,&s,atof(FValue));
								fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
								//Receivers.GetFieldValue("Country",FValue);
								//fprintf(output,"t_ctry=%s\n",FValue);
							}
							if(FValue==_T("POINT"))
							{
	/*							CString RecID,Field,SQL;
								Receivers.GetFieldValue((short)0,RecID);
								SQL.Format(_T(" from link,Frequency, Equipment, Station where receiverID=%s"), RecID);
								SQL=_T("Select sitename, geolat, geolon, station.country ")+SQL;
								SQL=SQL+ _T(" and link.rxid=frequency.freqid and frequency.eqid=equipment.eqid and equipment.stid=station.stid");
								CRecordset Recs;
								Recs.m_pDatabase=&m_DB;
								Recs.Open(CRecordset::snapshot,SQL);
								if(Recs.GetRecordCount()>0)
								{
									Recs.GetFieldValue(1,Field);
									fprintf(output,_T("t_lat=%s\n"),Field);
									Recs.GetFieldValue(2,Field);
									fprintf(output,_T("t_long=%s\n"),Field);
									Recs.GetFieldValue(3,Field);
									fprintf(output,_T("t_ctry=%s\n"),Field);
									Recs.GetFieldValue((short)0,Field);
									fprintf(output,_T("t_site_name=%s\n"),Field);
								}
								Recs.Close();*/
							}
							if(FValue==_T("MULTIPOINT"))
							{
								for(int i=1;i<=6;i++)
								{
									CString LatName,Lat,LonName,Lon;
									LatName.Format(_T("lat%d"),i);
									LonName.Format(_T("lon%d"),i);
									Receivers.GetFieldValue(LatName,Lat);
									Receivers.GetFieldValue(LonName,Lon);
									if(atof(Lat)==0 && atof(Lon)==0) break;
									fprintf(output,"<POINT>\n");
									Coord2DMS(&d,&m,&s,atof(Lat));
									fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
									Coord2DMS(&d,&m,&s,atof(Lon));
									fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
									fprintf(output,"</POINT>\n");
								}
							}
							//Receivers.GetFieldValue(_T("NoiseTemp"),FValue);
							//fprintf(output,"t_noise_temp=%s\n",FValue);
							fprintf(output,"</RX_STATION>\n");
							Receivers.MoveNext();
						}
					Receivers.Close();
					fprintf(output,"</ANTENNA>\n");
				}
				else
				{
					Stations.GetFieldValue("Frequency",FVal);
					fprintf(output,"t_trg_freq_assgn=%lf\n",FVal.m_dblVal/1000000.);
					Stations.GetFieldValue("EmissionCl",FValue);
					fprintf(output,"t_trg_emi_cls=%s\n",FValue);
					fprintf(output,"t_trg_stn_cls=%s\n",StClass.Left(2));
					Stations.GetFieldValue("BandWidth",FVal);
					fprintf(output,"t_trg_bdwdth_cde=%s\n",BandWidthCode((float)FVal.m_dblVal));
					Stations.GetFieldValue("HourFrom",FValue);
					fprintf(output,"t_trg_op_hh_fr=%s\n",FValue);
					Stations.GetFieldValue("HourTo",FVal);
					fprintf(output,"t_trg_op_hh_to=%s\n",FValue);
					Stations.GetFieldValue("GeoLon",FVal);
					int d,m,s;
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					Stations.GetFieldValue("GeoLat",FVal);
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
				}
				fprintf(output,"</NOTICE>\n");

				Stations.MoveNext();
			}//end for
			Stations.Close();
		}
		if(m_StTable!="Station")
		{
//
//		Mobile stations		T13
//
//			if(m_StID==-1)
//			{
//				SQL.Format(" Mobiles.LicID=%ld",m_LicID);
//				SQL=" Equipment.EqID = Antenna.EqID and [Mobiles].[MobID]=[Equipment].[MobID] AND"+SQL;
//				SQL="WHERE License.SrvID = SrvType.SrvID and License.LicID = Mobiles.LicID and Admin.ID = License.AdmID and Equipment.EqID = Frequency.EqID and "+SQL;
//				SQL="SELECT* FROM Equipment ,Antenna, Frequency ,Admin , License, Mobiles , SrvType "+SQL;
//			}
//			else
//			{
				SQL.Format(_T("and equipment.eqcatid=eqcat.eqcatid and antenna.antcatid=antcat.antcatid and License.SrvID = 'MT' and Mobiles.MobID=%ld"),m_StID);
				SQL=_T(" Equipment.EqID = Antenna.EqID and [Mobiles].[MobID]=[Equipment].[MobID] and provisions.provision=mobiles.provision ")+SQL;
				SQL=_T("WHERE License.LicID = Mobiles.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and ")+SQL;
				SQL=_T("SELECT* FROM Equipment,EqCat ,Antenna,AntCat, Frequency ,Owner , License, Mobiles, provisions ")+SQL;
//				OutFile+="St";
//			}
			Stations.Open(CRecordset::snapshot, SQL);
			if(Stations.GetRecordCount()==0)
			{
				AfxMessageBox(_Z("Data for this Notice is not complete!"));
				m_DB.Close();
				return;
			}
			if(!HeaderDone)
			{
				fprintf(output,"<HEAD>\n");
				Stations.GetFieldValue(97,Country);
				fprintf(output,"t_adm=%s\n",Country);
				m_NoticeDate.GetWindowText(FValue);
				fprintf(output,"t_d_sent=%s\n",FValue);
				fprintf(output,"</HEAD>\n");
			}
			for(;!Stations.IsEOF();St++)
			{
				fprintf(output,"<NOTICE>\n");
				Stations.GetFieldValue("ClassStation",FValue);
				StClass=FValue;
				Stations.GetFieldValue(_T("Fragment"),Fragment);
				fprintf(output,_T("t_fragment=%s\n"),Fragment);
//				if(!Fragment.Compare(_T("NTFD_RR")))
//					fprintf(output,"t_prov=RR11.2\n");
//				if(!Fragment.Compare("Req_agrt"))
//					fprintf(output,"t_prov=RR9.21\n");
				if(!Fragment.Compare("GE06L"))
				{
					fprintf(output,"t_prov=GE06-4.2\n");
					fprintf(output,_T("t_notice_type=G13\n"));
					m_PubReq.GetWindowText(FValue);
					if(FValue==_T("Yes"))
						fprintf(output,"t_is_pub_req=TRUE\n");
					else
						fprintf(output,"t_is_pub_req=FALSE\n");
				}
				else
				{
					fprintf(output,"t_prov=RR11.9\n");
					fprintf(output,_T("t_notice_type=T13\n"));
				}
				m_Action.GetWindowText(FValue);
				fprintf(output,"t_action=%s\n",FValue);
				m_IsResub.GetWindowText(FValue);
				if(FValue==_T("Yes"))
					fprintf(output,"t_is_resub=TRUE\n");
				else
					fprintf(output,"t_is_resub=FALSE\n");
				m_Action.GetWindowText(FValue);
				if(FValue=="ADD")
				{
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_adm_ref_id=%s\n",FValue);
				}
				else if(FValue=="MODIFY")
				{
					CString Rep;
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
/*					Stations.GetFieldValue("trgLon",FValue);
					int d,m,s;
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_T("Target longitude missing,");
					Stations.GetFieldValue("trgLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_T("Target latitude missing,");*/
					Stations.GetFieldValue("trgFrequency",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
					else		Rep+=_Z("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_FB;
					}
				}
				if(FValue.Compare("SUPPRESS") && FValue.Compare("WITHDRAW"))
				{
					CRecordset Transmitters;
					CString RSQL;
					Transmitters.m_pDatabase=&m_DB;
					CString CoordSQL,Adm,FreqID;
					Stations.GetFieldValue(_T("FreqID"),FreqID);
					RSQL.Format(_T("Select * from link where TXID=%s"),FreqID);
					Transmitters.Open(CRecordset::snapshot,RSQL);
					if(Transmitters.GetRecordCount()>0)
					{
						CString RecID,Field,SQL;
						Transmitters.GetFieldValue((short)0,RecID);
						SQL.Format(_T(" from link,Frequency, Equipment,antenna,antcat, Station where receiverID=%s"), RecID);
						SQL=_T("Select sitename, geolat, geolon, station.country, AntDir, Pol, AntHeightAGL ")+SQL;
						SQL=SQL+ _T(" and antenna.eqid=equipment.eqid and antenna.antcatid=antcat.antcatid");
						SQL=SQL+ _T(" and link.rxid=frequency.freqid and frequency.eqid=equipment.eqid and equipment.stid=station.stid");
						CRecordset Recs;
						Recs.m_pDatabase=&m_DB;
						Recs.Open(CRecordset::snapshot,SQL);
						if(Recs.GetRecordCount()>0)
						{
							int d,m,s;
							Recs.GetFieldValue(1,Field);
							Coord2DMS(&d,&m,&s,atof(Field));
							fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
							Recs.GetFieldValue(2,Field);
							Coord2DMS(&d,&m,&s,atof(Field));
							fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
///							Recs.GetFieldValue(3,Field);
///							fprintf(output,_T("t_ctry=%s\n"),Field);
							Recs.GetFieldValue((short)0,Field);
							fprintf(output,_T("t_site_name=%s\n"),Field);
//							Recs.GetFieldValue((short)4,Field);
//							fprintf(output,_T("t_ant_dir=%s\n"),Field==_T("D")?_T("D"):_T("ND"));
							Recs.GetFieldValue((short)5,Field);
							Pol=Field;
							if(NoticeType.Left(1)!=_T("T"))
							{
//								fprintf(output,"t_polar=%s\n",(LPCTSTR)Pol);
//								Recs.GetFieldValue((short)6,Field);
//								fprintf(output,_T("t_hgt_agl=%s\n"),Field);
							}
						}
						Recs.Close();
					}
					Transmitters.Close();

					Stations.GetFieldValue("Frequency",FVal);
					fprintf(output,"t_freq_assgn=%lf\n",FVal.m_dblVal/1000000.);
					Stations.GetFieldValue("RefFreq",FVal);
					if(FVal.m_dblVal>0) fprintf(output,"t_freq_carr=%lf\n",FVal.m_dblVal/1000000.);
					Stations.GetFieldValue("OpDate",FVal);
					fprintf(output,"t_d_inuse=%4d-%02d-%02d\n",FVal.m_pdate->year,FVal.m_pdate->month,FVal.m_pdate->day);
					Stations.GetFieldValue("CallSign",FValue);
					if(!(FValue.IsEmpty())) fprintf(output,"t_call_sign=%s\n",FValue);
//					Stations.GetFieldValue("MobileID",FVal);
//					fprintf(output,"t_station_id=%s\n",*FVal.m_pstring);
///					Stations.GetFieldValue("MobName",FValue);
///					fprintf(output,"t_site_name=%s\n",FValue);
					Stations.GetFieldValue("EmissionCl",FValue);
					fprintf(output,"t_emi_cls=%s\n",FValue);
					Stations.GetFieldValue("BandWidth",FVal);
					fprintf(output,"t_bdwdth_cde=%s\n",BandWidthCode((float)FVal.m_dblVal));
					if(NoticeType.Left(1)!=_T("T"))
					{
						Stations.GetFieldValue("SystemType1",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_system_type=%s\n",(LPCTSTR)FValue);
						Stations.GetFieldValue("SystemType2",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_system_type=%s\n",(LPCTSTR)FValue);
					}
///					Stations.GetFieldValue("GeoLon",FVal);
///					int d,m,s;
///					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
///					fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
///					Stations.GetFieldValue("GeoLat",FVal);
///					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
///					fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
					fprintf(output,"t_stn_cls=%s\n",StClass.Left(2));
					Stations.GetFieldValue("NatServ",FValue);
					fprintf(output,"t_nat_srv=%s\n",FValue.Left(2));
		//			Stations.GetFieldValue("HeightASL",FVal);
		//			fprintf(output,"t_site_alt=%ld\n",FVal.m_lVal);
					if(Fragment!=_T("Req_agrt"))
					{
						Stations.GetFieldValue("HourFrom",FValue);
						fprintf(output,"t_op_hh_fr=%s\n",FValue);
						Stations.GetFieldValue("HourTo",FValue);
						fprintf(output,"t_op_hh_to=%s\n",FValue);
						Stations.GetFieldValue("AddrCode",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_addr_code=%s\n",FValue);
						Stations.GetFieldValue("OpAgency",FValue);
						if(!(FValue.IsEmpty())) fprintf(output,"t_op_agcy=%s\n",FValue.Left(3));
					}
					Stations.GetFieldValue(131,FValue);
					fprintf(output,"t_ctry=%s\n",FValue);

					CRecordset Coord;
					Coord.m_pDatabase=&m_DB;
					CoordSQL.Format(_T("select * from Coord where agree_st like 'O%%' and freq_id=%s"),FreqID);
					Coord.Open(CRecordset::snapshot,CoordSQL);
					if(Coord.GetRecordCount()>0)
					{
						fprintf(output,"<COORD>\n");
						while(!Coord.IsEOF())
						{
							Coord.GetFieldValue(_T("adm"),Adm);
							fprintf(output,_T("t_adm=%s\n"),Adm);
							Coord.MoveNext();
						}
						fprintf(output,"</COORD>\n");
					}
					Coord.Close();

					fprintf(output,"<ANTENNA>\n");
					Stations.GetFieldValue("PowerType",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_pwr_xyz=%s\n",FValue.Left(1));
					Stations.GetFieldValue("Pwr2Ant",FVal);
					fprintf(output,"t_pwr_ant=%lf\n",10.0*log10(FVal.m_dblVal));
					
					Stations.GetFieldValue("RadPwr",FVal);
					fprintf(output,"t_pwr_dbw=%lf\n",10.0*log10(FVal.m_dblVal));
					Stations.GetFieldValue("RadPowerType",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_pwr_eiv=%s\n",FValue.Left(1));

		//			Stations.GetFieldValue("AntDir",FVal);
		//			fprintf(output,"t_ant_dir=%s\n",*FVal.m_pstring);
		//			AntDir=*FVal.m_pstring;
		//			Stations.GetFieldValue("Azimuth",FVal);
		//			fprintf(output,"t_azm_max_e=%lf\n",FVal.m_dblVal);
		//			Stations.GetFieldValue("AzimTo",FValue);
		//			if(!FValue.IsEmpty())
		//			{
		//				fprintf(output,"t_azm_fr=%lf\n",FVal.m_dblVal);
		//				fprintf(output,"t_azm_to=%s\n",FValue);
		//			}
		//			Stations.GetFieldValue("Elevation",FVal);
		//			fprintf(output,"t_elev=%lf\n",FVal.m_dblVal);
		//			Stations.GetFieldValue("BeamWidthH",FVal);
		//			fprintf(output,"t_bmwdth=%lf\n",FVal.m_dblVal);
///					Stations.GetFieldValue("Pol",FValue);
///					Pol=FValue.Left(1);
///					fprintf(output,"t_polar=%s\n",(LPCTSTR)Pol);
	//				Stations.GetFieldValue("AntHeightAGL",FVal);
	//				fprintf(output,"t_hgt_agl=%ld\n",FVal.m_lVal);
	//				Stations.GetFieldValue("GainType",FVal);
	//				fprintf(output,"t_gain_type=%s\n",FVal.m_pstring->Left(1));
	//				Stations.GetFieldValue("Gain",FVal);
	//				fprintf(output,"t_gain_max=%lf\n",FVal.m_dblVal);
	//				fprintf(output,"<TX_STATION>\n");

				if(NoticeType.Left(1)==_T("G"))
				{
					double Patt[2][360]={0.0}; //,Patt2[2][360]={0.0};
					int i;
					AntPatt.m_pDatabase=&m_DB;
					Stations.GetFieldValue(_T("AntCatID"),AntCatID);
					i=0;
					if(Pol!=_T("V")) 
					{
						fprintf(output,_T("<ANT_DIAGR_H>\n"));
						SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%s order by azm"),AntCatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						while(!AntPatt.IsEOF())
						{
							double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=azm=FVal.m_dblVal;
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=attn=FVal.m_dblVal;
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						if(i<360)
						{
	//  interpolation
							double PatternTmp[361],AngleTmp[361];
							Patt[0][i] = 360;
							Patt[1][i] = Patt[1][0];

							int m_NUM = 360; 
							for (int j=0;j<m_NUM;j++)
							{
								AngleTmp[j]=j;
								PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
							}
							PatternTmp[360]=PatternTmp[0];
							AngleTmp[360]=360;
							for(i=0;i<360;i++)
							{
								Patt[0][i]=AngleTmp[i];
								Patt[1][i]=PatternTmp[i];
							}
						}
	////////////////
						for(i=0;i<360;i+=10)
							fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
						fprintf(output,_T("</ANT_DIAGR_H>\n"));
					}
					i=0;
					if(Pol!=_T("H")) 
					{
						fprintf(output,_T("<ANT_DIAGR_V>\n"));
						SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%s order by azm"),AntCatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						while(!AntPatt.IsEOF())
						{
							double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=azm=FVal.m_dblVal;
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=attn=FVal.m_dblVal;
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						if(i<360)
						{
	//  interpolation
							double PatternTmp[361],AngleTmp[361];
							Patt[0][i] = 360;
							Patt[1][i] = Patt[1][0];

							int m_NUM = 360; 
							for (int j=0;j<m_NUM;j++)
							{
								AngleTmp[j]=j;
								PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
							}
							PatternTmp[360]=PatternTmp[0];
							AngleTmp[360]=360;
							for(i=0;i<360;i++)
							{
								Patt[0][i]=AngleTmp[i];
								Patt[1][i]=PatternTmp[i];
							}
						}
	////////////////
						for(i=0;i<360;i+=10)
							fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
						fprintf(output,_T("</ANT_DIAGR_V>\n"));
					}
					
				}//if G13					
					fprintf(output,"<TX_STATION>\n");
					Stations.GetFieldValue(_T("AreaOfTrans"),FValue);
					if(FValue.IsEmpty())	// CIRCLE
					{
						fprintf(output,"t_geo_type=CIRCLE\n");
						Stations.GetFieldValue("Radius",FVal);
						fprintf(output,"t_radius=%ld\n",FVal.m_lVal);
						Stations.GetFieldValue("GeoLon",FVal);
						int d,m,s;
						Coord2DMS(&d,&m,&s,FVal.m_dblVal);
						fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
						Stations.GetFieldValue("GeoLat",FVal);
						Coord2DMS(&d,&m,&s,FVal.m_dblVal);
						fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
					}
					else  // ZONE
					{
						fprintf(output,"t_geo_type=ZONE\n");
						fprintf(output,"t_zone_id=%s\n",FValue);
					}
					fprintf(output,"</TX_STATION>\n");
					fprintf(output,"</ANTENNA>\n");
				}
				else
				{
					Stations.GetFieldValue("Frequency",FVal);
					fprintf(output,"t_trg_freq_assgn=%lf\n",FVal.m_dblVal/1000000.);
					Stations.GetFieldValue("EmissionCl",FValue);
					fprintf(output,"t_trg_emi_cls=%s\n",FValue);
					fprintf(output,"t_trg_stn_cls=%s\n",StClass.Left(2));
					Stations.GetFieldValue("BandWidth",FVal);
					fprintf(output,"t_trg_bdwdth_cde=%s\n",BandWidthCode((float)FVal.m_dblVal));
					Stations.GetFieldValue("HourFrom",FValue);
					fprintf(output,"t_trg_op_hh_fr=%s\n",FValue);
					Stations.GetFieldValue("HourTo",FValue);
					fprintf(output,"t_trg_op_hh_to=%s\n",FValue);
					Stations.GetFieldValue("GeoLon",FVal);
					int d,m,s;
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					Stations.GetFieldValue("GeoLat",FVal);
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
				}
				fprintf(output,"</NOTICE>\n");

				Stations.MoveNext();
			}//end for
			Stations.Close();
		}

		fprintf(output,"<TAIL>\n");
		fprintf(output,"t_num_notices=%d\n", St);
		fprintf(output,"</TAIL>\n");
		fclose(output);
		ShellExecute(this->m_hWnd,"open",OutFile,NULL,NULL,SW_SHOWNORMAL);
	}//end if
}

void CNotice::Broadcast()
{
	if(/*m_Fragment.GetWindowTextLength() &&*/ m_Action.GetWindowTextLength())
	{
		CString OutFile, Country, NoticeDate,Fragment, AntCatID, NoticeType, TVSys,
			SQL, FValue, Pol,StClass, AntDir,FreqID, CoordSQL,Adm;
		long AntID, height;
		bool NoData=true;
		CRecordset Stations, Coord, EffHgt, AntPatt;
		char buf[100];
		double Frequency,Azimuth, azm;
		CDatabase m_DB;
		int d,m,s;
		m_DB.Open(m_CDBSTR, FALSE, FALSE, "ODBC;", FALSE);
		Stations.m_pDatabase=&m_DB;
		int St;		//Station counter
		CDBVariant FVal;
		OutFile=GetCommandLine();
		int Place=OutFile.ReverseFind('\\')-1;
		OutFile.Delete(0);
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		Place=OutFile.ReverseFind('\\')+1;
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		OutFile+="reports\\";
//		if(m_StID==-1)
//		{
//			SQL.Format("\'Broadcasting\' and BCStation.LicID=%ld",m_LicID);
//			SQL=" Equipment.EqID = Antenna.EqID and BCStation.StID=Equipment.BCID AND (SrvType.SrvType)="+SQL;
//			SQL="WHERE License.SrvID = SrvType.SrvID and License.LicID = BCStation.LicID and Admin.ID = License.AdmID and Equipment.EqID = Frequency.EqID and "+SQL;
//			SQL="SELECT* FROM Equipment ,Antenna, Frequency ,Admin , License, BCStation , SrvType "+SQL;
//			OutFile+="Lic";
//		}
//		else
			{
				SQL.Format("equipment.eqcatid=eqcat.eqcatid and antenna.antcatid=antcat.antcatid and BCStation.StID=%ld order by antcat.AntCatID",m_StID);
				SQL=" Equipment.EqID = Antenna.EqID and BCStation.StID=Equipment.BCID AND provisions.provision=BCStation.provision and "+SQL;
				SQL="WHERE License.LicID = BCStation.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and "+SQL;
				SQL="SELECT* FROM  Equipment, Eqcat ,Antenna, Antcat, Frequency ,Owner, License, BCStation,provisions "+SQL;
				OutFile+="St";
			}
		Stations.Open(CRecordset::snapshot, SQL);
		if(Stations.GetRecordCount()==0)
		{
Err_BC:		AfxMessageBox(_Z("Data for this Notice is not complete!"));
			m_DB.Close();
			return;
		}
		Stations.GetFieldValue(_T("NoticeType"),NoticeType);
		m_NoticeDate.GetWindowText(NoticeDate);
		m_Action.GetWindowText(FValue);
		if(m_StID==-1)
			ltoa(m_LicID,buf,10);
		else
			ltoa(m_StID,buf,10);
		OutFile+=buf;
		OutFile+=FValue+NoticeDate;
		OutFile+=".txt";
		FILE *output=fopen(OutFile,"wt");
		fprintf(output,"<HEAD>\n");
		Stations.GetFieldValue(97,Country);
		fprintf(output,"t_adm=%s\n",Country);
		m_NoticeDate.GetWindowText(FValue);
		fprintf(output,"t_d_sent=%s\n",FValue);
		fprintf(output,"</HEAD>\n");
		for(St=1;!Stations.IsEOF();St++)
		{
//
//		Broadcast transmitters			T01, T02
//
			if(NoticeType==_T("GT1") || NoticeType==_T("DT1") || NoticeType==_T("GB1"))
			{
				fprintf(output,"<NOTICE>\n");

				Stations.GetFieldValue(_T("Frequency"),FVal);
				Frequency=FVal.m_dblVal;
//				if(Frequency<3.e+9 && Frequency>=3.e+7)
				Stations.GetFieldValue("Fragment",Fragment);
				fprintf(output,"t_fragment=%s\n",Fragment);
				m_Action.GetWindowText(FValue);
				fprintf(output,"t_action=%s\n",FValue);
				Stations.GetFieldValue(_T("Azimuth"),FVal);
				Azimuth=FVal.m_dblVal;
///				if(FValue=="ADMINID")  //???
///				{
///				}
///				else if(FValue=="CONFORM")  //???
///				{
///				}
///				else if(FValue=="PARTB")  //TB3
///				{ 
///				}
///				else if(FValue=="COORDINATION")  //???
///				{
///				}
///				else 
					if(FValue=="SUPPRESS" || FValue=="WITHDRAW")  //TB5
				{
					CString Rep;
					fprintf(output,"t_notice_type=TB5\n");
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					Stations.GetFieldValue("GeoLon",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target longitude missing,");
					Stations.GetFieldValue("GeoLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target latitude missing,");
					//Stations.GetFieldValue("Frequency",FValue);
					/*if(!FValue.IsEmpty())*/ fprintf(output,"t_trg_freq_assgn=%lf\n",Frequency/1000000.);
					//else		Rep+=_T("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_BC;
					}
				}
				else if(FValue=="ADD" || FValue=="MODIFY")  //GT1
				{
					fprintf(output,"t_notice_type=%s\n", (LPCTSTR)NoticeType);
					if(FValue=="ADD")
					{
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_adm_ref_id=%s\n",FValue);
					}
					else
					{
						CString Rep;
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
						Stations.GetFieldValue("trgLon",FValue);
						Coord2DMS(&d,&m,&s,atof(FValue));
						if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
						else		Rep+=_Z("Target longitude missing,");
						Stations.GetFieldValue("trgLat",FValue);
						Coord2DMS(&d,&m,&s,atof(FValue));
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
						else		Rep+=_Z("Target latitude missing,");
						Stations.GetFieldValue("trgFrequency",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
						else		Rep+=_Z("Target frequency missing,");
						if(!Rep.IsEmpty())
						{
							AfxMessageBox(Rep);
							Stations.Close();
							goto Err_BC;
						}
					}
					if(Fragment==_T("GE06D")) // Article 4
					{
						Stations.GetFieldValue("RefPlanCfg",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_ref_plan_cfg=%s\n",FValue);
						m_PubReq.GetWindowText(FValue);
						if(FValue==_T("Yes"))
							fprintf(output,"t_is_pub_req=TRUE\n");
						else
							fprintf(output,"t_is_pub_req=FALSE\n");
					}
					if(Fragment==_T("NTFD_RR")) // Article 5
					{
						Stations.GetFieldValue("CallSign",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_call_sign=%s\n",FValue);
						Stations.GetFieldValue("OpAgency",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_op_agcy=%s\n",FValue);
						Stations.GetFieldValue("AddrCode",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_addr_code=%s\n",FValue);
						Stations.GetFieldValue("HourFrom",FValue);
						fprintf(output,"t_op_hh_fr=%s\n",FValue);
						Stations.GetFieldValue("HourTo",FValue);
						fprintf(output,"t_op_hh_to=%s\n",FValue);
						Stations.GetFieldValue("CondMet",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_remark_conds_met =%s\n",
							(FValue==_T("1"))?_T("TRUE"):_T("FALSE"));
						m_IsResub.GetWindowText(FValue);
						if(FValue==_T("Yes"))
							fprintf(output,"t_is_resub=TRUE\n");
						else
							fprintf(output,"t_is_resub=FALSE\n");
						Stations.GetFieldValue("SignedCommit",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_signed_commitment=%s\n",
							(FValue==_T("1"))?_T("TRUE"):_T("FALSE"));
					}

					Stations.GetFieldValue("PlanEntry",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_plan_entry=%s\n",FValue);
					Stations.GetFieldValue("AssignCode",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_assgn_code=%s\n",FValue);
					Stations.GetFieldValue("AssocAllotID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_associated_adm_allot_id=%s\n",FValue);
					Stations.GetFieldValue("AssocAllotSFN",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_associated_allot_sfn_id=%s\n",FValue);
					Stations.GetFieldValue("SfnID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_sfn_id=%s\n",FValue);
					fprintf(output,"t_freq_assgn=%lf\n",Frequency/1000000.);
					Stations.GetFieldValue("Offset",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_offset=%s\n",FValue);
					Stations.GetFieldValue("OpDate",FVal);
					fprintf(output,"t_d_inuse=%4d-%02d-%02d\n",FVal.m_pdate->year,FVal.m_pdate->month,FVal.m_pdate->day);
					Stations.GetFieldValue("SiteName",FValue);
					fprintf(output,"t_site_name=%s\n",FValue);
					Stations.GetFieldValue(133,FValue);
					fprintf(output,"t_ctry=%s\n",FValue);
					Stations.GetFieldValue("GeoLon",FVal);
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
					Stations.GetFieldValue("GeoLat",FVal);
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
					if(NoticeType!=_T("GB1"))
					{
						Stations.GetFieldValue("SysVar",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_sys_var=%s\n",FValue);
						Stations.GetFieldValue("RXMode",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_rx_mode=%s\n",FValue);
						Stations.GetFieldValue("SpectMask",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_spect_mask=%s\n",FValue);
					}
					else
					{
						Stations.GetFieldValue("BandWidth",FVal);
						fprintf(output,"t_bdwdth=%ld\n",(long)FVal.m_dblVal);
						Stations.GetFieldValue("EmissionCl",FValue);
						fprintf(output,"t_emi_cls=%s\n",(LPCTSTR)FValue);
						Stations.GetFieldValue("ClassStation",FValue);
						fprintf(output,"t_stn_cls=%s\n",FValue.Left(2));
						Stations.GetFieldValue("MaxPowDens",FValue);
						fprintf(output,"t_pwr_dens=%s\n",FValue);
					}
					Stations.GetFieldValue("Pol",FValue);
					Pol=FValue.Left(1);
					if(Pol!=_T("V"))
					{
						Stations.GetFieldValue("ERP_h_dbw",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_erp_h_dbw=%s\n",FValue);
					}
					if(Pol!=_T("H"))
					{
						Stations.GetFieldValue("ERP_v_dbw",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_erp_v_dbw=%s\n",FValue);
					}
///					Stations.GetFieldValue("ERPTilt",FValue);
///					if(!FValue.IsEmpty()) fprintf(output,"t_erp_beam_tilt_dbw =%s\n",FValue);
///					Stations.GetFieldValue("Tilt",FValue);
///					if(!FValue.IsEmpty()) fprintf(output,"t_beam_tilt_angle =%s\n",FValue);
					Stations.GetFieldValue("AntDir",FValue);
					fprintf(output,"t_ant_dir=%s\n",(FValue==_T("N")?_T("ND"):_T("D")));
					Stations.GetFieldValue("AntHeightAGL",FVal);
					fprintf(output,"t_hgt_agl=%ld\n",(long)FVal.m_dblVal);
					fprintf(output,"t_polar=%s\n",Pol);
					Stations.GetFieldValue("HeightASL",FVal);
					fprintf(output,"t_site_alt=%ld\n",FVal.m_lVal);
					Stations.GetFieldValue("MaxEffHght",FVal);
					fprintf(output,"t_eff_hgtmax=%d\n",FVal.m_iVal);
					Coord.m_pDatabase=&m_DB;
					Stations.GetFieldValue(_T("FreqID"),FreqID);
					CoordSQL.Format(_T("select * from Coord where agree_st like 'O%%' and freq_id=%s"),FreqID);
					Coord.Open(CRecordset::snapshot,CoordSQL);
					if(Coord.GetRecordCount()>0)
					{
						fprintf(output,"<COORD>\n");
						while(!Coord.IsEOF())
						{
							Coord.GetFieldValue(_T("adm"),Adm);
							fprintf(output,_T("t_adm=%s\n"),Adm);
							Coord.MoveNext();
						}
						fprintf(output,"</COORD>\n");
					}
					Coord.Close();

					fprintf(output,"<ANT_HGT>\n");
					EffHgt.m_pDatabase=&m_DB;
					Stations.GetFieldValue("AntID",FVal);
					AntID=FVal.m_lVal;
					SQL.Format("Select * from AntHgt where AntID=%ld order by azm",AntID);
					EffHgt.Open(CRecordset::snapshot, SQL);
					while(!EffHgt.IsEOF())
					{
						EffHgt.GetFieldValue("Azm",FVal);
						azm=FVal.m_dblVal;
						if(azm==((int)(azm/10))*10)
						{
							EffHgt.GetFieldValue("EffHgt",FVal);
							height=FVal.m_lVal;							
							fprintf(output,"t_eff_hgt@azm%d = %ld\n",(int)azm,height);
							NoData=false;
						}
						EffHgt.MoveNext();
					}
					EffHgt.Close();
					fprintf(output,"</ANT_HGT>\n");
					if(NoData)
					{
						AfxMessageBox(_Z("No effective height available!"));
						Stations.Close();
						m_DB.Close();
						return;
					}
					double Patt[2][360]={0.0}; //,Patt2[2][360]={0.0};
					int i;
					AntPatt.m_pDatabase=&m_DB;
					while(true)
					{
						Stations.GetFieldValue(_T("AntCatID"),AntCatID);
						i=0;
						if(Pol!=_T("V")) 
						{
							fprintf(output,_T("<ANT_DIAGR_H>\n"));
							SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%s order by azm"),AntCatID);
							AntPatt.Open(CRecordset::snapshot, SQL);
							while(!AntPatt.IsEOF())
							{
								double azm, attn;
								AntPatt.GetFieldValue(_T("Azm"),FVal);
								Patt[0][i]=azm=FVal.m_dblVal;
								AntPatt.GetFieldValue(_T("Attn"),FVal);
								Patt[1][i]=attn=FVal.m_dblVal;
								AntPatt.MoveNext();
								i++;
							}
							AntPatt.Close();
							if(i<360)
							{
	//  interpolation
								double PatternTmp[361],AngleTmp[361];
								Patt[0][i] = 360;
								Patt[1][i] = Patt[1][0];

								int m_NUM = 360; 
								for (int j=0;j<m_NUM;j++)
								{
									AngleTmp[j]=j;
									PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
								}
								PatternTmp[360]=PatternTmp[0];
								AngleTmp[360]=360;
								for(i=0;i<360;i++)
								{
									Patt[0][i]=AngleTmp[i];
									Patt[1][i]=PatternTmp[i];
								}
							}
		////////////////
							for(i=0;i<360;i+=10)
								fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
							fprintf(output,_T("</ANT_DIAGR_H>\n"));
						}
						i=0;
						if(Pol!=_T("H")) 
						{
							fprintf(output,_T("<ANT_DIAGR_V>\n"));
							SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%s order by azm"),AntCatID);
							AntPatt.Open(CRecordset::snapshot, SQL);
							while(!AntPatt.IsEOF())
							{
								double azm, attn;
								AntPatt.GetFieldValue(_T("Azm"),FVal);
								Patt[0][i]=azm=FVal.m_dblVal;
								AntPatt.GetFieldValue(_T("Attn"),FVal);
								Patt[1][i]=attn=FVal.m_dblVal;
								AntPatt.MoveNext();
								i++;
							}
							AntPatt.Close();
							if(i<360)
							{
	//  interpolation
								double PatternTmp[361],AngleTmp[361];
								Patt[0][i] = 360;
								Patt[1][i] = Patt[1][0];

								int m_NUM = 360; 
								for (int j=0;j<m_NUM;j++)
								{
									AngleTmp[j]=j;
									PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
								}
								PatternTmp[360]=PatternTmp[0];
								AngleTmp[360]=360;
								for(i=0;i<360;i++)
								{
									Patt[0][i]=AngleTmp[i];
									Patt[1][i]=PatternTmp[i];
								}
							}
	////////////////
							for(i=0;i<360;i+=10)
								fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
							fprintf(output,_T("</ANT_DIAGR_V>\n"));
						}
						Stations.MoveNext();
						if(Stations.IsEOF()) break;
						Stations.GetFieldValue("Pol",FVal);
						Pol=FVal.m_pstring->Left(1);
					}
				}
				else
					AfxMessageBox(_Z("Action is not applicable here!"));
			}//// end GT1 and DT1
			else if(NoticeType==_T("GS1") || NoticeType==_T("DS1"))
			{
				fprintf(output,"<NOTICE>\n");

				Stations.GetFieldValue(_T("Frequency"),FVal);
				Frequency=FVal.m_dblVal;
				Stations.GetFieldValue("Fragment",Fragment);
				fprintf(output,"t_fragment=%s\n",Fragment);
				m_Action.GetWindowText(FValue);
				fprintf(output,"t_action=%s\n",FValue);
				Stations.GetFieldValue(_T("Azimuth"),FVal);
				Azimuth=FVal.m_dblVal;
///				if(FValue=="ADMINID")  //???
///				{
///				}
///				else if(FValue=="CONFORM")  //???
///				{
///				}
///				else if(FValue=="PARTB")  //TB3
///				{ 
///				}
///				else if(FValue=="COORDINATION")  //???
///				{
///				}
///				else 
				if(FValue=="SUPPRESS" || FValue=="WITHDRAW")  //TB5
				{
					CString Rep;
					fprintf(output,"t_notice_type=TB5\n");
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					Stations.GetFieldValue("GeoLon",FValue);
					int d,m,s;
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target longitude missing,");
					Stations.GetFieldValue("GeoLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target latitude missing,");
					//Stations.GetFieldValue("Frequency",FValue);
					/*if(!FValue.IsEmpty())*/ fprintf(output,"t_trg_freq_assgn=%lf\n",Frequency/1000000.);
					//else		Rep+=_T("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_BC;
					}
				}
				else if(FValue=="ADD" || FValue=="MODIFY")  //GS1
				{
					fprintf(output,"t_notice_type=GS1\n");
					if(FValue=="ADD")
					{
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_adm_ref_id=%s\n",FValue);
					}
					else
					{
						CString Rep;
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
						Stations.GetFieldValue("trgLon",FValue);
						int d,m,s;
						Coord2DMS(&d,&m,&s,atof(FValue));
						if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
						else		Rep+=_Z("Target longitude missing,");
						Stations.GetFieldValue("trgLat",FValue);
						Coord2DMS(&d,&m,&s,atof(FValue));
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
						else		Rep+=_Z("Target latitude missing,");
						Stations.GetFieldValue("trgFrequency",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
						else		Rep+=_Z("Target frequency missing,");
						if(!Rep.IsEmpty())
						{
							AfxMessageBox(Rep);
							Stations.Close();
							goto Err_BC;
						}
					}
					if(Fragment==_T("GE06D")) // Article 4
					{
						m_PubReq.GetWindowText(FValue);
						if(FValue==_T("Yes"))
							fprintf(output,"t_is_pub_req=TRUE\n");
						else
							fprintf(output,"t_is_pub_req=FALSE\n");
					}
					if(Fragment==_T("NTFD_RR")) // Article 5
					{
						Stations.GetFieldValue("CallSign",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_call_sign=%s\n",FValue);
						Stations.GetFieldValue("OpAgency",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_op_agcy=%s\n",FValue);
						Stations.GetFieldValue("AddrCode",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_addr_code=%s\n",FValue);
						Stations.GetFieldValue("HourFrom",FVal);
						fprintf(output,"t_op_hh_fr=%s\n",*FVal.m_pstring);
						Stations.GetFieldValue("HourTo",FVal);
						fprintf(output,"t_op_hh_to=%s\n",*FVal.m_pstring);
						Stations.GetFieldValue("CondMet",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_remark_conds_met =%s\n",
							(FValue==_T("1"))?_T("TRUE"):_T("FALSE"));
						m_IsResub.GetWindowText(FValue);
						if(FValue==_T("Yes"))
							fprintf(output,"t_is_resub=TRUE\n");
						else
							fprintf(output,"t_is_resub=FALSE\n");
						Stations.GetFieldValue("SignedCommit",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_signed_commitment=%s\n",
							(FValue==_T("1"))?_T("TRUE"):_T("FALSE"));
					}
					Stations.GetFieldValue("PlanEntry",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_plan_entry=%s\n",FValue);
					Stations.GetFieldValue("AssignCode",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_assgn_code=%s\n",FValue);
					Stations.GetFieldValue("AssocAllotID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_associated_adm_allot_id=%s\n",FValue);
					Stations.GetFieldValue("AssocAllotSFN",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_associated_allot_sfn_id=%s\n",FValue);
					Stations.GetFieldValue("SfnID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_sfn_id=%s\n",FValue);
					fprintf(output,"t_freq_assgn=%lf\n",Frequency/1000000.);
					Stations.GetFieldValue("Offset",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_offset=%s\n",FValue);
					Stations.GetFieldValue("OpDate",FVal);
					fprintf(output,"t_d_inuse=%4d-%02d-%02d\n",FVal.m_pdate->year,FVal.m_pdate->month,FVal.m_pdate->day);
					Stations.GetFieldValue("SiteName",FVal);
					fprintf(output,"t_site_name=%s\n",*FVal.m_pstring);
					Stations.GetFieldValue(133,FValue);
					fprintf(output,"t_ctry=%s\n",FValue);
					Stations.GetFieldValue("GeoLon",FVal);
					int d, m,s;
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
					Stations.GetFieldValue("GeoLat",FVal);
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
					Stations.GetFieldValue("RefPlanCfg",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_ref_plan_cfg=%s\n",FValue);
					Stations.GetFieldValue("SpectMask",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_spect_mask=%s\n",FValue);
					Stations.GetFieldValue("Pol",FVal);
					Pol=FVal.m_pstring->Left(1);
					if(Pol!=_T("V"))
					{
						Stations.GetFieldValue("ERP_h_dbw",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_erp_h_dbw=%s\n",FValue);
					}
					if(Pol!=_T("H"))
					{
						Stations.GetFieldValue("ERP_v_dbw",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_erp_v_dbw=%s\n",FValue);
					}
//					Stations.GetFieldValue("ERPTilt",FValue);
//					if(!FValue.IsEmpty()) fprintf(output,"t_erp_beam_tilt_dbw =%s\n",FValue);
//					Stations.GetFieldValue("Tilt",FValue);
//					if(!FValue.IsEmpty()) fprintf(output,"t_beam_tilt_angle =%s\n",FValue);
					Stations.GetFieldValue("AntDir",FValue);
					fprintf(output,"t_ant_dir=%s\n",(FValue==_T("N")?_T("ND"):_T("D")));
					Stations.GetFieldValue("AntHeightAGL",FVal);
					fprintf(output,"t_hgt_agl=%ld\n",(long)FVal.m_dblVal);
					fprintf(output,"t_polar=%s\n",Pol);
					Stations.GetFieldValue("HeightASL",FVal);
					fprintf(output,"t_site_alt=%ld\n",FVal.m_lVal);
					Stations.GetFieldValue("MaxEffHght",FVal);
					fprintf(output,"t_eff_hgtmax=%d\n",FVal.m_iVal);
//					CRecordset Coord;
//					CString CoordSQL,Adm,FreqID;
					Coord.m_pDatabase=&m_DB;
					Stations.GetFieldValue(_T("FreqID"),FreqID);
					CoordSQL.Format(_T("select * from Coord where agree_st like 'O%%' and freq_id=%s"),FreqID);
					Coord.Open(CRecordset::snapshot,CoordSQL);
					if(Coord.GetRecordCount()>0)
					{
						fprintf(output,"<COORD>\n");
						while(!Coord.IsEOF())
						{
							Coord.GetFieldValue(_T("adm"),Adm);
							fprintf(output,_T("t_adm=%s\n"),Adm);
							Coord.MoveNext();
						}
						fprintf(output,"</COORD>\n");
					}
					Coord.Close();

					fprintf(output,"<ANT_HGT>\n");
//					CRecordset EffHgt;
//					long AntID;
					bool NoData=true;
					EffHgt.m_pDatabase=&m_DB;
					Stations.GetFieldValue("AntID",FVal);
					AntID=FVal.m_lVal;
					SQL.Format("Select * from AntHgt where AntID=%ld order by azm",AntID);
					EffHgt.Open(CRecordset::snapshot, SQL);
					while(!EffHgt.IsEOF())
					{
//						double azm;
//						long height;
						EffHgt.GetFieldValue("Azm",FVal);
						azm=FVal.m_dblVal;
						if(azm==((int)(azm/10))*10)
						{
							EffHgt.GetFieldValue("EffHgt",FVal);
							height=FVal.m_lVal;							
							fprintf(output,"t_eff_hgt@azm%d = %ld\n",(int)azm,height);
							NoData=false;
						}
						EffHgt.MoveNext();
					}
					EffHgt.Close();
					fprintf(output,"</ANT_HGT>\n");
					if(NoData)
					{
						AfxMessageBox(_Z("No effective height available!"));
						Stations.Close();
						m_DB.Close();
						return;
					}
//					CRecordset AntPatt;
					double Patt[2][360]={0.0}; //,Patt2[2][360]={0.0};
					int i;
					AntPatt.m_pDatabase=&m_DB;
					while(true)
					{
						Stations.GetFieldValue(_T("AntCatID"),AntCatID);
						i=0;
						if(Pol!=_T("V")) 
						{
							fprintf(output,_T("<ANT_DIAGR_H>\n"));
							SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%s order by azm"),AntCatID);
							AntPatt.Open(CRecordset::snapshot, SQL);
							while(!AntPatt.IsEOF())
							{
								double azm, attn;
								AntPatt.GetFieldValue(_T("Azm"),FVal);
								Patt[0][i]=azm=FVal.m_dblVal;
								AntPatt.GetFieldValue(_T("Attn"),FVal);
								Patt[1][i]=attn=FVal.m_dblVal;
								AntPatt.MoveNext();
								i++;
							}
							AntPatt.Close();
							if(i<360)
							{
	//  interpolation
								double PatternTmp[361],AngleTmp[361];
								Patt[0][i] = 360;
								Patt[1][i] = Patt[1][0];

								int m_NUM = 360; 
								for (int j=0;j<m_NUM;j++)
								{
									AngleTmp[j]=j;
									PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
								}
								PatternTmp[360]=PatternTmp[0];
								AngleTmp[360]=360;
								for(i=0;i<360;i++)
								{
									Patt[0][i]=AngleTmp[i];
									Patt[1][i]=PatternTmp[i];
								}
							}
	////////////////
							for(i=0;i<360;i+=10)
								fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
							fprintf(output,_T("</ANT_DIAGR_H>\n"));
						}
						i=0;
						if(Pol!=_T("H")) 
						{
							fprintf(output,_T("<ANT_DIAGR_V>\n"));
							SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%s order by azm"),AntCatID);
							AntPatt.Open(CRecordset::snapshot, SQL);
							while(!AntPatt.IsEOF())
							{
								double azm, attn;
								AntPatt.GetFieldValue(_T("Azm"),FVal);
								Patt[0][i]=azm=FVal.m_dblVal;
								AntPatt.GetFieldValue(_T("Attn"),FVal);
								Patt[1][i]=attn=FVal.m_dblVal;
								AntPatt.MoveNext();
								i++;
							}
							AntPatt.Close();
							if(i<360)
							{
	//  interpolation
								double PatternTmp[361],AngleTmp[361];
								Patt[0][i] = 360;
								Patt[1][i] = Patt[1][0];

								int m_NUM = 360; 
								for (int j=0;j<m_NUM;j++)
								{
									AngleTmp[j]=j;
									PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
								}
								PatternTmp[360]=PatternTmp[0];
								AngleTmp[360]=360;
								for(i=0;i<360;i++)
								{
									Patt[0][i]=AngleTmp[i];
									Patt[1][i]=PatternTmp[i];
								}
							}
	////////////////
							for(i=0;i<360;i+=10)
								fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
							fprintf(output,_T("</ANT_DIAGR_V>\n"));
						}
						Stations.MoveNext();
						if(Stations.IsEOF()) break;
						Stations.GetFieldValue("Pol",FVal);
						Pol=FVal.m_pstring->Left(1);
					}
				}
				else
					AfxMessageBox(_Z("Action is not applicable here!"));
			} /// end GS1 and DS1
			else if(NoticeType==_T("T01") || NoticeType==_T("T02") || NoticeType==_T("G02"))
			{
				fprintf(output,"<NOTICE>\n");
				m_PubReq.GetWindowText(FValue);
				if(NoticeType==_Z("G02"))
				{
					if(FValue==_T("Yes"))
						fprintf(output,"t_is_pub_req=TRUE\n");
					else
						fprintf(output,"t_is_pub_req=FALSE\n");
				}
				Stations.GetFieldValue(_T("Frequency"),FVal);
				Frequency=FVal.m_dblVal;
				if(Frequency<3.e+9 && Frequency>=3.e+7)
				{
				Stations.GetFieldValue("Fragment",Fragment);
				fprintf(output,"t_fragment=%s\n",Fragment);
				m_Action.GetWindowText(FValue);
				fprintf(output,"t_action=%s\n",FValue);
				Stations.GetFieldValue(_T("Azimuth"),FVal);
				Azimuth=FVal.m_dblVal;

				if(FValue=="ADMINID")  //TB01
				{
					CString Rep;
					fprintf(output,"t_notice_type=TB1\n");
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					else		Rep+=_Z("Admin. RefID missing,");
					Stations.GetFieldValue("trgLon",FValue);
					int d,m,s;
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target longitude missing,");
					Stations.GetFieldValue("trgLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target latitude missing,");
					Stations.GetFieldValue("trgFrequency",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
					else		Rep+=_Z("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_BC;
					}
				}//ADMINID
				else if(FValue=="CONFORM") //TB02
				{
				}//CONFORM
				else if(FValue=="PARTB") //TB03
				{
					CString Rep;
					fprintf(output,"t_notice_type=TB3\n");
					Stations.GetFieldValue("Plan",FValue);
					fprintf(output,"t_plan=%s\n",FValue);
					m_NoticeDate.GetWindowText(FValue);
					fprintf(output,"t_d_adm_ntc=%s\n",FValue);
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					Stations.GetFieldValue("trgLon",FValue);
					int d,m,s;
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target longitude missing,");
					Stations.GetFieldValue("trgLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target latitude missing,");
					Stations.GetFieldValue("trgFrequency",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
					else		Rep+=_Z("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_BC;
					}
				}//PARTB
				else if(FValue=="COORDINATION") //TB04
				{
					CString Rep;
					fprintf(output,"t_notice_type=TB4\n");
					m_NoticeDate.GetWindowText(FValue);
					fprintf(output,"t_d_adm_ntc=%s\n",FValue);
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					Stations.GetFieldValue("trgLon",FValue);
					int d,m,s;
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target longitude missing,");
					Stations.GetFieldValue("trgLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target latitude missing,");
					Stations.GetFieldValue("trgFrequency",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
					else		Rep+=_Z("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_BC;
					}
					fprintf(output,"<COORD>\n");
					CRecordset Coord;
					CString CoordSQL,Adm;
					Coord.m_pDatabase=&m_DB;
					Stations.GetFieldValue(_T("FreqID"),FreqID);
					CoordSQL.Format(_T("select * from Coord where agree_st like 'O%%' and freq_id=%s"),FreqID);
					Coord.Open(CRecordset::snapshot,CoordSQL);
					while(!Coord.IsEOF())
					{
						Coord.GetFieldValue(_T("adm"),Adm);
						fprintf(output,_T("t_adm=%s\n"),Adm);
						Coord.MoveNext();
					}
					Coord.Close();
					fprintf(output,"</COORD>\n");
				}//COORDINATION
				else if(FValue=="SUPPRESS" || FValue=="WITHDRAW") //TB05
				{
					CString Rep;
					fprintf(output,"t_notice_type=TB5\n");
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					Stations.GetFieldValue("GeoLon",FValue);
					int d,m,s;
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target longitude missing,");
					Stations.GetFieldValue("GeoLat",FValue);
					Coord2DMS(&d,&m,&s,atof(FValue));
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
					else		Rep+=_Z("Target latitude missing,");
					//Stations.GetFieldValue("Frequency",FValue);
					/*if(!FValue.IsEmpty())*/ fprintf(output,"t_trg_freq_assgn=%lf\n",Frequency/1000000.);
					//else		Rep+=_Z("Target frequency missing,");
					if(!Rep.IsEmpty())
					{
						AfxMessageBox(Rep);
						Stations.Close();
						goto Err_BC;
					}
				}//SUPPRESS / WITHDRAW
				else if(FValue=="ADD" || FValue=="MODIFY") //T01 & T02
				{
					if(FValue=="ADD")
					{
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_adm_ref_id=%s\n",FValue);
					}
					else
					{
						CString Rep;
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
						Stations.GetFieldValue("trgLon",FValue);
						int d,m,s;
						Coord2DMS(&d,&m,&s,atof(FValue));
						if(!FValue.IsEmpty())  fprintf(output,"t_trg_long=%+04d%02d%02d\n",d,m,s);
						else		Rep+=_Z("Target longitude missing,");
						Stations.GetFieldValue("trgLat",FValue);
						Coord2DMS(&d,&m,&s,atof(FValue));
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_lat=%+03d%02d%02d\n",d,m,s);
						else		Rep+=_Z("Target latitude missing,");
						Stations.GetFieldValue("trgFrequency",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_freq_assgn=%s\n",FValue);
						else		Rep+=_Z("Target frequency missing,");
						if(!Rep.IsEmpty())
						{
							AfxMessageBox(Rep);
							Stations.Close();
							goto Err_BC;
						}
					}
					Stations.GetFieldValue("ClassStation",FValue);
					StClass=FValue;
//					if(StClass.Left(2)=="BC")	//				T01
//						NoticeType="T01";
//					else						//				T02
//						NoticeType="T02";
					fprintf(output,"t_notice_type=%s\n",(LPCTSTR)NoticeType);
					Stations.GetFieldValue("TVSys",TVSys);
//					if(NoticeType==_T("T02") && TVSys.Left(1)!=_T("T"))
//					{
//						Stations.GetFieldValue("Plan",FValue);
//						fprintf(output,"t_plan=%s\n",FValue);
//					}
					fprintf(output,"t_freq_assgn=%lf\n",Frequency/1000000.);
					Stations.GetFieldValue("CallSign",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_call_sign=%s\n",FValue);
					Stations.GetFieldValue("SiteID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_station_id=%s\n",FValue);
					Stations.GetFieldValue("SiteName",FVal);
					fprintf(output,"t_site_name=%s\n",*FVal.m_pstring);
					Stations.GetFieldValue("GeoLon",FVal);
					int d, m,s;
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_long=%+04d%02d%02d\n",d,m,s);
					Stations.GetFieldValue("GeoLat",FVal);
					Coord2DMS(&d,&m,&s,FVal.m_dblVal);
					fprintf(output,"t_lat=%+03d%02d%02d\n",d,m,s);
					Stations.GetFieldValue("HeightASL",FVal);
					fprintf(output,"t_site_alt=%ld\n",FVal.m_lVal);
					if(Fragment==_T("NTFD_RR"))
					{
						fprintf(output,_T("t_notice_type=%s\n"), NoticeType);
						fprintf(output,"t_prov=RR11.2\n");
						Stations.GetFieldValue("OpDate",FVal);
						fprintf(output,"t_d_inuse=%4d-%02d-%02d\n",FVal.m_pdate->year,FVal.m_pdate->month,FVal.m_pdate->day);
						Stations.GetFieldValue("HourFrom",FVal);
						fprintf(output,"t_op_hh_fr=%s\n",*FVal.m_pstring);
							Stations.GetFieldValue("HourTo",FVal);
						fprintf(output,"t_op_hh_to=%s\n",*FVal.m_pstring);
						Stations.GetFieldValue("AddrCode",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_addr_code=%s\n",FValue);
					}
					Stations.GetFieldValue(133,FValue);
					fprintf(output,"t_ctry=%s\n",FValue);
					Stations.GetFieldValue("AntHeightAGL",FVal);
					fprintf(output,"t_hgt_agl=%ld\n",(long)FVal.m_dblVal);
					if(NoticeType==_T("G02"))
					{
						Stations.GetFieldValue("AntDir",FValue);
						fprintf(output,"t_ant_dir=%s\n",(FValue==_T("N")?_T("ND"):_T("D")));
					}
					Stations.GetFieldValue("Pol",FVal);
					fprintf(output,"t_polar=%s\n",FVal.m_pstring->Left(1));
					Pol=FVal.m_pstring->Left(1);
					Stations.GetFieldValue("MaxEffHght",FVal);
					fprintf(output,"t_eff_hgtmax=%d\n",FVal.m_iVal);
					if(Pol==_T("H"))
					{
						Stations.GetFieldValue("ERP_h_dbw",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_erp_h_dbw=%s\n",FValue);
					}
					else
					{
						Stations.GetFieldValue("ERP_v_dbw",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_erp_v_dbw=%s\n",FValue);
					}

					if(NoticeType=="T01")
					{
						Stations.GetFieldValue("TranSys",FValue);
						fprintf(output,"t_tran_sys=%s\n",FValue);
						Stations.GetFieldValue("BandWidth",FVal);
						fprintf(output,"t_bdwdth=%ld\n",(long)FVal.m_dblVal);
					}
					else
					{
						bool S_flag=false, V_flag=false;
						fprintf(output,"t_tran_sys=%s\n",TVSys);
						Stations.GetFieldValue("FreqStabl",FValue);
						fprintf(output,"t_freq_stabl=%s\n",FValue);
						Stations.GetFieldValue("OsetV",FValue);
						if(!FValue.IsEmpty())
						{
							fprintf(output,"t_oset_v_khz=%+ld\n",atol(FValue));
							V_flag=true;
						}
						Stations.GetFieldValue("OsetS",FValue);
						if(!FValue.IsEmpty())
						{
							fprintf(output,"t_oset_s_khz=%+ld\n",atol(FValue));
							S_flag=true;
						}
						if(TVSys.Left(1)!=_T("T"))
						{
							Stations.GetFieldValue("OsetV12",FVal);
							if(!V_flag) fprintf(output,"t_oset_v_12=%+ld\n",FVal.m_lVal);
							Stations.GetFieldValue("OsetS12",FVal);
							if(!S_flag) fprintf(output,"t_oset_s_12=%+ld\n",FVal.m_lVal);
							Stations.GetFieldValue("ColorSys",FValue);
							fprintf(output,"t_color=%s\n",FValue);
							Stations.GetFieldValue("PwrRatio",FVal);
							fprintf(output,"t_pwr_ratio=%f\n",FVal.m_dblVal);
						}
					}
					fprintf(output,"<ANT_HGT>\n");
//					CRecordset EffHgt;
//					long AntID;
					bool NoData=true;
					EffHgt.m_pDatabase=&m_DB;
					Stations.GetFieldValue("AntID",FVal);
					AntID=FVal.m_lVal;
					SQL.Format("Select * from AntHgt where AntID=%ld order by azm",AntID);
					EffHgt.Open(CRecordset::snapshot, SQL);
					while(!EffHgt.IsEOF())
					{
//						double azm;
//						long height;
						EffHgt.GetFieldValue("Azm",FVal);
						azm=FVal.m_dblVal;
						if(azm==((int)(azm/10))*10)
						{
							EffHgt.GetFieldValue("EffHgt",FVal);
							height=FVal.m_lVal;							
							fprintf(output,"t_eff_hgt@azm%d = %ld\n",(int)azm,height);
							NoData=false;
						}
						EffHgt.MoveNext();
					}
					EffHgt.Close();
					fprintf(output,"</ANT_HGT>\n");
					if(NoData)
					{
						AfxMessageBox(_Z("No effective height available!"));
						Stations.Close();
						m_DB.Close();
						return;
					}
//					CRecordset AntPatt;
					double Patt[2][360]={0.0}; //,Patt2[2][360]={0.0};
					int i;
					AntPatt.m_pDatabase=&m_DB;
					while(true)
					{
						Stations.GetFieldValue(_T("AntCatID"),AntCatID);
						i=0;
						if(Pol!=_T("V")) 
						{
							fprintf(output,_T("<ANT_DIAGR_H>\n"));
							SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%s order by azm"),AntCatID);
							AntPatt.Open(CRecordset::snapshot, SQL);
							while(!AntPatt.IsEOF())
							{
								double azm, attn;
								AntPatt.GetFieldValue(_T("Azm"),FVal);
								Patt[0][i]=azm=FVal.m_dblVal;
								AntPatt.GetFieldValue(_T("Attn"),FVal);
								Patt[1][i]=attn=FVal.m_dblVal;
								AntPatt.MoveNext();
								i++;
							}
							AntPatt.Close();
							if(i<360)
							{
	//  interpolation
								double PatternTmp[361],AngleTmp[361];
								Patt[0][i] = 360;
								Patt[1][i] = Patt[1][0];

								int m_NUM = 360; 
								for (int j=0;j<m_NUM;j++)
								{
									AngleTmp[j]=j;
									PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
								}
								PatternTmp[360]=PatternTmp[0];
								AngleTmp[360]=360;
								for(i=0;i<360;i++)
								{
									Patt[0][i]=AngleTmp[i];
									Patt[1][i]=PatternTmp[i];
								}
							}
	////////////////
							for(i=0;i<360;i+=10)
								fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
							fprintf(output,_T("</ANT_DIAGR_H>\n"));
						}
						i=0;
						if(Pol!=_T("H")) 
						{
							fprintf(output,_T("<ANT_DIAGR_V>\n"));
							SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%s order by azm"),AntCatID);
							AntPatt.Open(CRecordset::snapshot, SQL);
							while(!AntPatt.IsEOF())
							{
								double azm, attn;
								AntPatt.GetFieldValue(_T("Azm"),FVal);
								Patt[0][i]=azm=FVal.m_dblVal;
								AntPatt.GetFieldValue(_T("Attn"),FVal);
								Patt[1][i]=attn=FVal.m_dblVal;
								AntPatt.MoveNext();
								i++;
							}
							AntPatt.Close();
							if(i<360)
							{
	//  interpolation
								double PatternTmp[361],AngleTmp[361];
								Patt[0][i] = 360;
								Patt[1][i] = Patt[1][0];

								int m_NUM = 360; 
								for (int j=0;j<m_NUM;j++)
								{
									AngleTmp[j]=j;
									PatternTmp[j] = Interp2(Patt[0],Patt[1],j*360/m_NUM,i+1) ;
								}
								PatternTmp[360]=PatternTmp[0];
								AngleTmp[360]=360;
								for(i=0;i<360;i++)
								{
									Patt[0][i]=AngleTmp[i];
									Patt[1][i]=PatternTmp[i];
								}
							}
	////////////////
							for(i=0;i<360;i+=10)
								fprintf(output,"t_attn@azm%d = %f\n",i/*(int)Patt2[0][i]*/,Patt[1][i]);
							fprintf(output,_T("</ANT_DIAGR_V>\n"));
						}
/*					CRecordset AntPatt;
					double Patt[2][360]={0.0}; //,Patt2[2][360]={0.0};
					int i;
					AntPatt.m_pDatabase=&m_DB;
					while(true)
					{
						Stations.GetFieldValue(_T("AntCatID"),AntCatID);
						i=0;
						if(Pol==_T("H")) fprintf(output,_T("<ANT_DIAGR_H>\n"));
						else			fprintf(output,_T("<ANT_DIAGR_V>\n"));
						SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%s order by azm"),AntCatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						while(!AntPatt.IsEOF())
						{
							double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=azm=FVal.m_dblVal;
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=attn=FVal.m_dblVal;
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						i=0;
						while(Patt[0][i]<Azimuth && i<360)
							i++;
						if(i==360) i=359;
						for(int j=i;j<360;j++)
							Patt[0][j]-=Azimuth;
						for(j=0;j<i;j++)
							Patt[0][j]+=359-Azimuth;
						for(j=0;j<360;j++)
						{
							Patt2[0][j]=(double)j;
							Patt2[1][(int)Patt[0][j]]=Patt[1][j];
						}
						for(i=0;i<360;i+=10)
							fprintf(output,"t_attn@azm%d = %f\n",i,Patt2[1][i]);
						if(Pol==_T("H")) fprintf(output,_T("</ANT_DIAGR_H>\n"));
						else			fprintf(output,_T("</ANT_DIAGR_V>\n"));*/
						Stations.MoveNext();
						if(Stations.IsEOF()) break;
						Stations.GetFieldValue("Pol",FVal);
						Pol=FVal.m_pstring->Left(1);
					}
				}
				else
					AfxMessageBox(_Z("Action is not applicable here!"));
				}
//			fprintf(output,"</NOTICE>\n");
			}
			//Stations.MoveNext();
			break;
		}//end for
		fprintf(output,"</NOTICE>\n");
		Stations.Close();
		fprintf(output,"<TAIL>\n");
		fprintf(output,"t_num_notices=%d\n", St);
		fprintf(output,"</TAIL>\n");
		fclose(output);
		ShellExecute(this->m_hWnd,"open",OutFile,NULL,NULL,SW_SHOWNORMAL);
	}//end if
}

BOOL CNotice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CAdministrativeApp *)AfxGetApp())->m_Lang=m_Lang;

	CDatabase DB;
	CRecordset RS;
	CString m_Tbl,F1;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	m_Tbl.Format(_T("SELECT Action FROM NoticeActions where Service='%s'"),m_SrvType);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Action.ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Action.AddString(F1);
		RS.MoveNext();
	}
	RS.Close();
	if(m_Action.GetCount()==0)
	{
		m_Action.AddString(_T("ADD"));
		m_Action.AddString(_T("MODIFY"));
	}
	m_Action.SelectString(0,_T("ADD"));
	m_NoticeDate.SetFormat(_T("yyyy'-'MM'-'dd"));
//	if(m_SrvType==_T("F") || (m_SrvType==_T("MT") && !m_StTable.CompareNoCase(_T("Station"))))
//	{
//		((CButton *)GetDlgItem(IDC_T14))->EnableWindow(true);
//	}
	if(!m_SrvType.CompareNoCase(_T("Contour")))
	{
		m_IsResub.EnableWindow(false);
		m_PubReq.EnableWindow(false);
	}
	m_IsResub.SelectString(0,_T("No"));
	m_PubReq.SelectString(0,_T("Yes"));

	if(!m_SrvType.CollateNoCase("F")) m_Tbl.Format(_T("SELECT rf_ctry.adm FROM Station, rf_ctry WHERE [Station].[country]=[rf_ctry].[ctry] AND Station.stid=%ld"),m_StID);
	if(!m_SrvType.CollateNoCase("MT"))
	{
		if(m_StTable=="Mobiles")
			m_Tbl.Format(_T("SELECT rf_ctry.adm FROM Mobiles, rf_ctry WHERE [Mobiles].[country]=[rf_ctry].[ctry] AND Mobiles.Mobid=%ld"),m_StID);
		else
			m_Tbl.Format(_T("SELECT rf_ctry.adm FROM Station, rf_ctry WHERE [Station].[country]=[rf_ctry].[ctry] AND Station.stid=%ld"),m_StID);
	}
	if(!m_SrvType.CollateNoCase("B")) m_Tbl.Format(_T("SELECT rf_ctry.adm FROM BCStation, rf_ctry WHERE [BCStation].[country]=[rf_ctry].[ctry] AND BCStation.stid=%ld"),m_StID);
	if(!m_SrvType.CollateNoCase("Allotment")) m_Tbl.Format(_T("SELECT rf_ctry.adm FROM rrc_allotment, rf_ctry WHERE [rrc_allotment].[ctry]=[rf_ctry].[ctry] AND rrc_allotment.allotkey=%ld"),m_StID);
	if(!m_SrvType.CollateNoCase("Contour")) m_Tbl.Format(_T("SELECT rf_ctry.adm FROM rrc_contour, rf_ctry WHERE [rrc_contour].[ctry]=[rf_ctry].[ctry] AND rrc_contour.contourkey=%ld"),m_StID);

	
	RS.Open( CRecordset::snapshot, m_Tbl);
	RS.GetFieldValue((short)0,F1);
	m_Admin=F1;
	((CEdit *)GetDlgItem(IDC_ADMIN))->SetWindowText(F1);
	RS.Close();
	DB.Close();

	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CNotice::BandWidthCode(float BW)
{
	int i;
	CString Temp;
	BW*=1000;
	char Code;
	if(BW<1000)
	{
		Code='H';
	}
	if(BW>=1000. && BW<1e+6)
	{
		BW/=1000.;
		Code='K';
	}
	if(BW>=1e+6 && BW<1e+9)
	{
		BW/=1e+6;
		Code='M';
	}
	if(BW>=1e+9 && BW<1e+12)
	{
		BW/=1e+9;
		Code='G';
	}
		int IPart=(int)BW;
		float FPart2=BW-IPart;
		char FP[10], tt[20];
		sprintf(FP,"%.3f",FPart2);
		strcpy(tt,FP+2);

		if(IPart)
		{
			if(FPart2)
				Temp.Format("%d%c%s",IPart,Code,tt);
			else
				Temp.Format("%d%c",IPart,Code);
		}
		else
			Temp.Format("%c%s",Code,tt);

	for(i=Temp.GetLength();i<4;i++)
		Temp+="0";
	Temp=Temp.Left(4);
	return Temp;
}

void CNotice::Coord2DMS(int *d, int *m, int *s, double Val)
{
	CString Temp;
	double lat=Val;
	int dd=(int)lat,
	mm=abs((int)((fabs(lat)-(double)abs(dd))*60.));
	double ss=fabs(((fabs(lat)-(double)abs(dd))*60.-(double)abs(mm))*60.);
	if(ss>59.99)
	{
		ss=0;
		mm++;
	}
	if(mm>59.)
	{
		mm=0;
		dd++;
	}

	Temp.Format(_T("%+04d%02d%05.2f"),dd,mm,ss);
	*d=atoi(Temp.Left(4));
	*m=atoi(Temp.Mid(4,2));
	*s=atoi(Temp.Mid(6,2));
/*	double sgn;
	*d=(int)Val;
	sgn=(d<0)?-1:1;
	*m=abs((int)((fabs(Val)-(double)abs(*d))*60.));
	*s=abs((int)(((fabs(Val)-(double)abs(*d))*60.-(double)abs(*m))*60.));*/
}

/////////////////////////////////////////////////////////////////////////////
// CNotice message handlers

double CNotice::Interp2(double *D0,double *E0,double d,int num) 
{
	double d1,d2,E1,E2,Eb;
	if (d<D0[0])
	{
		d1=D0[0];d2=D0[1];
		E1=E0[0];E2=E0[1];
	}
	else if (d>D0[num-1])
	{
		d1=D0[num-2];d2=D0[num-1];
		E1=E0[num-2];E2=E0[num-1];
	}
	else
	{
		/////////////////////////////////////////////
		int n1=0;
		while(d>=D0[n1])
		{
			n1++;
			if (n1==num)
				break;
		}
		if (n1==0)
			n1=1;
		d1=D0[n1-1],E1=E0[n1-1];
		///////////////////////////////////////////////
		int n2=num-1;
		while(d<=D0[n2])
			n2--;
		d2=D0[n2+1],E2=E0[n2+1];
		////////////////////////////////////////////////
	}
	Eb=((d1==d2) ? E1 : E1+(E2-E1)*(d-d1)/(d2-d1));

	return Eb;

}

void CNotice::Allotment()
{
	if(m_Action.GetWindowTextLength())
	{
		CString OutFile, Country, NoticeDate,Fragment, AntCatID;
		char buf[100];
		CString NoticeType, TVSys;
		double Frequency;
		CDatabase m_DB;
		CString	SQL, FValue, Pol;
		m_DB.Open(m_CDBSTR, FALSE, FALSE, "ODBC;", FALSE);
		CRecordset Stations,Contours;
		Stations.m_pDatabase=&m_DB;
		Contours.m_pDatabase=&m_DB;
		int St;		//Station counter
		CDBVariant FVal;
		CString StClass, AntDir,FreqID;
		OutFile=GetCommandLine();
		int Place=OutFile.ReverseFind('\\')-1;
		OutFile.Delete(0);
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		Place=OutFile.ReverseFind('\\')+1;
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		OutFile+="reports\\";
		SQL.Format(_T("and license.licid=rrc_allotment.licid and allotkey=%ld"),m_StID);
		SQL=_T("SELECT * FROM rrc_allotment,Owner,License where owner.ID=License.AdmID ")+SQL;
		OutFile+="Allot";
		Stations.Open(CRecordset::snapshot, SQL);
		if(Stations.GetRecordCount()==0)
		{
			AfxMessageBox(_Z("Data for this Notice is not complete!"));
			m_DB.Close();
			return;
		}
		Stations.GetFieldValue(_T("NoticeType"),NoticeType);
		m_NoticeDate.GetWindowText(NoticeDate);
		m_Action.GetWindowText(FValue);
		if(m_StID==-1)
			ltoa(m_LicID,buf,10);
		else
			ltoa(m_StID,buf,10);
		OutFile+=buf;
		OutFile+=FValue+NoticeDate;
		OutFile+=".txt";
		FILE *output=fopen(OutFile,"wt");
		fprintf(output,"<HEAD>\n");
		Stations.GetFieldValue(24,Country); 
		fprintf(output,"t_adm=%s\n",Country);
		m_NoticeDate.GetWindowText(FValue);
		fprintf(output,"t_d_sent=%s\n",FValue);
		fprintf(output,"</HEAD>\n");
		for(St=1;!Stations.IsEOF();St++)
		{
//
//		Broadcasting allotments			GS2, GT2
//
			if(NoticeType==_T("GT2") || NoticeType==_T("DT2"))
			{
				fprintf(output,"<NOTICE>\n");

				Stations.GetFieldValue(_T("Frequency"),FVal);
				Frequency=FVal.m_dblVal;
				Stations.GetFieldValue("Fragment",Fragment);
				fprintf(output,"t_fragment=%s\n",Fragment);
				m_Action.GetWindowText(FValue);
				fprintf(output,"t_action=%s\n",FValue);
				if(FValue=="SUPPRESS" || FValue=="WITHDRAW")  //TB5
				{
					CString Rep;
					fprintf(output,"t_notice_type=TB5\n");
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
				}
				else if(FValue=="ADD" || FValue=="MODIFY")  //GT1
				{
					fprintf(output,"t_notice_type=GT2\n");
					if(FValue=="ADD")
					{
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_adm_ref_id=%s\n",FValue);
					}
					else
					{
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					}
					m_PubReq.GetWindowText(FValue);
					if(FValue==_T("Yes"))
						fprintf(output,"t_is_pub_req=TRUE\n");
					else
						fprintf(output,"t_is_pub_req=FALSE\n");
					Stations.GetFieldValue("PlanEntry",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_plan_entry=%s\n",FValue);
					Stations.GetFieldValue("SfnID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_sfn_id=%s\n",FValue);
					fprintf(output,"t_freq_assgn=%lf\n",Frequency/1000000.);
					Stations.GetFieldValue("Offset",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_offset=%s\n",FValue);
					Stations.GetFieldValue("ExpDate",FVal);
					fprintf(output,"t_d_expiry=%4d-%02d-%02d\n",FVal.m_pdate->year,FVal.m_pdate->month,FVal.m_pdate->day);
					Stations.GetFieldValue("allot_name",FVal);
					fprintf(output,"t_allot_name=%s\n",*FVal.m_pstring);
					Stations.GetFieldValue(13,FValue);
					fprintf(output,"t_ctry=%s\n",FValue);
					Stations.GetFieldValue("geo_area",FValue);
					fprintf(output,"t_geo_area=%s\n",FValue);
					Stations.GetFieldValue("nb_sub_areas",FValue);
					fprintf(output,"t_nb_sub_areas=%ld\n",atol(FValue));
					SQL.Format(_T("select * from rrc_sub_area where allotkey=%ld"),m_StID);
					Contours.Open(CRecordset::snapshot,SQL);
					while(!Contours.IsEOF())
					{
						Contours.GetFieldValue(1,FValue);
						fprintf(output,"t_contour_id=%s\n",FValue);
						Contours.MoveNext();
					}
					Contours.Close();
					Stations.GetFieldValue("RefPlanCfg",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_ref_plan_cfg=%s\n",FValue);
					Stations.GetFieldValue("TypRefNetwk",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_typ_ref_netwk=%s\n",FValue);
					Stations.GetFieldValue("SpectMask",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_spect_mask=%s\n",FValue);
					Stations.GetFieldValue("Polar",FVal);
					Pol=FVal.m_pstring->Left(1);
					fprintf(output,"t_polar=%s\n",Pol);
//// Coordination 
					CRecordset Coord;
					CString CoordSQL,Adm,AllotKey;
					Coord.m_pDatabase=&m_DB;
					Stations.GetFieldValue(_T("allotkey"),AllotKey);
					CoordSQL.Format(_T("select * from rrc_allot_coord where agree_st like 'O%%' and allotkey=%s"),AllotKey);
					Coord.Open(CRecordset::snapshot,CoordSQL);
					if(Coord.GetRecordCount()>0)
					{
						fprintf(output,"<COORD>\n");
						while(!Coord.IsEOF())
						{
							Coord.GetFieldValue(_T("adm"),Adm);
							fprintf(output,_T("t_adm=%s\n"),Adm);
							Coord.MoveNext();
						}
						fprintf(output,"</COORD>\n");
					}
					Coord.Close();
					fprintf(output,"</NOTICE>\n");
				}
				else
					AfxMessageBox(_Z("Action is not applicable here!"));
			}//// end GT2
			else if(NoticeType==_T("GS2") || NoticeType==_T("DS2"))
			{
				fprintf(output,"<NOTICE>\n");

				Stations.GetFieldValue(_T("Frequency"),FVal);
				Frequency=FVal.m_dblVal;
				Stations.GetFieldValue("Fragment",Fragment);
				fprintf(output,"t_fragment=%s\n",Fragment);
				m_Action.GetWindowText(FValue);
				fprintf(output,"t_action=%s\n",FValue);
				if(FValue=="SUPPRESS" || FValue=="WITHDRAW")  //TB5
				{
					CString Rep;
					fprintf(output,"t_notice_type=TB5\n");
					Stations.GetFieldValue("AdmRefID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
				}
				else if(FValue=="ADD" || FValue=="MODIFY")  //GS2
				{
					fprintf(output,"t_notice_type=GS2\n");
					if(FValue=="ADD")
					{
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_adm_ref_id=%s\n",FValue);
					}
					else
					{
						Stations.GetFieldValue("AdmRefID",FValue);
						if(!FValue.IsEmpty()) fprintf(output,"t_trg_adm_ref_id=%s\n",FValue);
					}
					m_PubReq.GetWindowText(FValue);
					if(FValue==_T("Yes"))
						fprintf(output,"t_is_pub_req=TRUE\n");
					else
						fprintf(output,"t_is_pub_req=FALSE\n");
					Stations.GetFieldValue("PlanEntry",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_plan_entry=%s\n",FValue);
					Stations.GetFieldValue("SfnID",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_sfn_id=%s\n",FValue);
					fprintf(output,"t_freq_assgn=%lf\n",Frequency/1000000.);
					Stations.GetFieldValue("Offset",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_offset=%s\n",FValue);
					Stations.GetFieldValue("ExpDate",FVal);
					fprintf(output,"t_d_expiry=%4d-%02d-%02d\n",FVal.m_pdate->year,FVal.m_pdate->month,FVal.m_pdate->day);
					Stations.GetFieldValue("allot_name",FVal);
					fprintf(output,"t_allot_name=%s\n",*FVal.m_pstring);
					Stations.GetFieldValue(13,FValue);
					fprintf(output,"t_ctry=%s\n",FValue);
					Stations.GetFieldValue("geo_area",FValue);
					fprintf(output,"t_geo_area=%s\n",FValue);
					Stations.GetFieldValue("nb_sub_areas",FValue);
					fprintf(output,"t_nb_sub_areas=%ld\n",atol(FValue));
					SQL.Format(_T("select * from rrc_sub_area where allotkey=%ld"),m_StID);
					Contours.Open(CRecordset::snapshot,SQL);
					while(!Contours.IsEOF())
					{
						Contours.GetFieldValue(1,FValue);
						fprintf(output,"t_contour_id=%s\n",FValue);
						Contours.MoveNext();
					}
					Contours.Close();
					Stations.GetFieldValue("RefPlanCfg",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_ref_plan_cfg=%s\n",FValue);
					Stations.GetFieldValue("SpectMask",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_spect_mask=%s\n",FValue);
					Stations.GetFieldValue("Polar",FVal);
					Pol=FVal.m_pstring->Left(1);
					fprintf(output,"t_polar=%s\n",Pol);
//// Coordination 
					CRecordset Coord;
					CString CoordSQL,Adm,AllotKey;
					Coord.m_pDatabase=&m_DB;
					Stations.GetFieldValue(_T("allotkey"),AllotKey);
					CoordSQL.Format(_T("select * from rrc_allot_coord where agree_st like 'O%%' and allotkey=%s"),AllotKey);
					Coord.Open(CRecordset::snapshot,CoordSQL);
					if(Coord.GetRecordCount()>0)
					{
						fprintf(output,"<COORD>\n");
						while(!Coord.IsEOF())
						{
							Coord.GetFieldValue(_T("adm"),Adm);
							fprintf(output,_T("t_adm=%s\n"),Adm);
							Coord.MoveNext();
						}
						fprintf(output,"</COORD>\n");
					}
					Coord.Close();
					fprintf(output,"</NOTICE>\n");
				}
				else
					AfxMessageBox("Action is not applicable here!");
			}//// end GS2
			//Stations.MoveNext();
			break;
		}//end for
		Stations.Close();
		fprintf(output,"<TAIL>\n");
		fprintf(output,"t_num_notices=%d\n", St);
		fprintf(output,"</TAIL>\n");
		fclose(output);
		ShellExecute(this->m_hWnd,"open",OutFile,NULL,NULL,SW_SHOWNORMAL);
	}//end if
}


void CNotice::Contour()
{
	if(m_Action.GetWindowTextLength())
	{
		CString OutFile, Country, NoticeDate;
		char buf[100];
		CString NoticeType;
		CDatabase m_DB;
		CString	SQL, FValue;
		m_DB.Open(m_CDBSTR, FALSE, FALSE, "ODBC;", FALSE);
		CRecordset Stations,Contours;
		Stations.m_pDatabase=&m_DB;
		Contours.m_pDatabase=&m_DB;
		CDBVariant FVal;
		OutFile=GetCommandLine();
		int Place=OutFile.ReverseFind('\\')-1;
		OutFile.Delete(0);
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		Place=OutFile.ReverseFind('\\')+1;
		OutFile.Delete(Place,OutFile.GetLength()-Place);
		OutFile+="reports\\";
		SQL.Format(_T("SELECT * FROM rrc_contour where contourkey=%ld"),m_StID);
		OutFile+="Contour";
		Stations.Open(CRecordset::snapshot, SQL);
		if(Stations.GetRecordCount()==0)
		{
			AfxMessageBox(_Z("Data for this Notice is not complete!"));
			m_DB.Close();
			return;
		}
		NoticeType=_T("GA1");
		m_NoticeDate.GetWindowText(NoticeDate);
		m_Action.GetWindowText(FValue);
		ltoa(m_StID,buf,10);
		OutFile+=buf;
		OutFile+=FValue+NoticeDate;
		OutFile+=".txt";
		FILE *output=fopen(OutFile,"wt");
		fprintf(output,"<HEAD>\n");
		Stations.GetFieldValue(2,Country); 
		fprintf(output,"t_adm=%s\n",Country);
		fprintf(output,"t_d_sent=%s\n",NoticeDate);
		fprintf(output,"</HEAD>\n");
//
//		Broadcasting contour			GA1
//
//			if(NoticeType==_T("GT2") || NoticeType==_T("DT2"))
			{
				fprintf(output,"<NOTICE>\n");

				fprintf(output,"t_notice_type=GA1\n");
				m_Action.GetWindowText(FValue);
				fprintf(output,"t_action=%s\n",FValue);
				if(FValue=="SUPPRESS" || FValue=="ADD")  //GA1
				{
					Stations.GetFieldValue("contour_id",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_contour_id=%s\n",FValue);
					Stations.GetFieldValue("nb_test_pts",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_nb_test_pts=%s\n",FValue);
					Stations.GetFieldValue("ctry",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_ctry=%s\n",FValue);
					Stations.GetFieldValue("remarks",FValue);
					if(!FValue.IsEmpty()) fprintf(output,"t_remarks=%s\n",FValue);

					
					
					SQL.Format(_T("select * from rrc_contour_pt where contourkey=%ld order by test_pt"),m_StID);
					Contours.Open(CRecordset::snapshot,SQL);
					while(!Contours.IsEOF())
					{
						CString D,M,S;
						fprintf(output,"<POINT>\n");
						Contours.GetFieldValue(6,D);
						Contours.GetFieldValue(7,M);
						Contours.GetFieldValue(8,S);
						Contours.GetFieldValue(9,FValue);
						fprintf(output,"t_long=%c%02d%02d%02d\n",FValue==_T("S")?_T('-'):_T('+'),
							atoi(D),atoi(M),atoi(S));
						Contours.GetFieldValue(2,D);
						Contours.GetFieldValue(3,M);
						Contours.GetFieldValue(4,S);
						Contours.GetFieldValue(5,FValue);
						fprintf(output,"t_long=%c%03d%02d%02d\n",FValue==_T("W")?_T('-'):_T('+'),
							atoi(D),atoi(M),atoi(S));
						fprintf(output,"</POINT>\n");
						Contours.MoveNext();
					}
					Contours.Close();
					fprintf(output,"</NOTICE>\n");
				}
				else
					AfxMessageBox(_Z("Action is not applicable here!"));
			}//// end GA1
		Stations.Close();
		fprintf(output,"<TAIL>\n");
		fprintf(output,"t_num_notices=1\n");
		fprintf(output,"</TAIL>\n");
		fclose(output);
		ShellExecute(this->m_hWnd,"open",OutFile,NULL,NULL,SW_SHOWNORMAL);
	}//end if
}

