// IFICImport.cpp : implementation file
//
#include "stdafx.h"
#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS
#include "resource.h"
#include "IFICImport.h"
#include "SelRecord.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFICImport dialog


CIFICImport::CIFICImport(CWnd* pParent /*=NULL*/)
	: CDialog(CIFICImport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFICImport)
	//}}AFX_DATA_INIT
}


void CIFICImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFICImport)
	DDX_Control(pDX, IDC_BROWSE, m_Browse);
	DDX_Control(pDX, IDC_MDB, m_AccessMDB);
	DDX_Control(pDX, IDC_SQLITE, m_SQLite);
	DDX_Control(pDX, IDC_DIGITAL, m_Digital);
	DDX_Control(pDX, IDC_IDSel, m_IDSel);
	DDX_Control(pDX, IDC_IDRemove, m_IDRemove);
	DDX_Control(pDX, IDC_IDAdd, m_IDAdd);
	DDX_Control(pDX, IDC_ID, m_TerraKey);
	DDX_Control(pDX, IDC_FragSel, m_FragSel);
	DDX_Control(pDX, IDC_FragRemove, m_FragRemove);
	DDX_Control(pDX, IDC_FragClear, m_FragClear);
	DDX_Control(pDX, IDC_FragAdd, m_FragAdd);
	DDX_Control(pDX, IDC_ClassSel, m_ClassSel);
	DDX_Control(pDX, IDC_ClassRemove, m_ClassRemove);
	DDX_Control(pDX, IDC_ClassClear, m_ClassClear);
	DDX_Control(pDX, IDC_ClassAdd, m_ClassAdd);
	DDX_Control(pDX, IDC_FRAGMENT, m_Fragment);
	DDX_Control(pDX, IDC_STATION_CLASS, m_StationClass);
	DDX_Control(pDX, IDC_PROGRESS, m_ImportProgress);
	DDX_Control(pDX, IDC_LFMF, m_LFMF);
	DDX_Control(pDX, IDC_FXM, m_FXM);
	DDX_Control(pDX, IDC_FreqRem, m_FreqRem);
	DDX_Control(pDX, IDC_FreqCondSel, m_FreqCondSel);
	DDX_Control(pDX, IDC_FreqCond, m_FreqCond);
	DDX_Control(pDX, IDC_FreqAdd, m_FreqAdd);
	DDX_Control(pDX, IDC_FMTV, m_FMTV);
	DDX_Control(pDX, IDC_F2U, m_F2U);
	DDX_Control(pDX, IDC_F2, m_F2);
	DDX_Control(pDX, IDC_F1U, m_F1U);
	DDX_Control(pDX, IDC_F1, m_F1);
	DDX_Control(pDX, IDC_ADMSEL, m_AdmSel);
	DDX_Control(pDX, IDC_AdmRemove, m_AdmRemove);
	DDX_Control(pDX, IDC_ADMLIST, m_AdmList);
	DDX_Control(pDX, IDC_AdmClear, m_AdmClear);
	DDX_Control(pDX, IDC_AdmAddAll, m_AdmAddAll);
	DDX_Control(pDX, IDC_AdmAdd, m_AdmAdd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIFICImport, CDialog)
	//{{AFX_MSG_MAP(CIFICImport)
	ON_BN_CLICKED(IDC_AdmAdd, OnAdmAdd)
	ON_BN_CLICKED(IDC_AdmRemove, OnAdmRemove)
	ON_BN_CLICKED(IDC_AdmClear, OnAdmClear)
	ON_BN_CLICKED(IDC_AdmAddAll, OnAdmAddAll)
	ON_LBN_SELCHANGE(IDC_FreqCond, OnSelchangeFreqCond)
	ON_BN_CLICKED(IDC_FreqAdd, OnFreqAdd)
	ON_BN_CLICKED(IDC_FreqRem, OnFreqRem)
	ON_BN_CLICKED(IDC_FMTV, OnFmtv)
	ON_BN_CLICKED(IDC_FXM, OnFxm)
	ON_BN_CLICKED(IDC_ClassRemove, OnClassRemove)
	ON_BN_CLICKED(IDC_FragRemove, OnFragRemove)
	ON_BN_CLICKED(IDC_ClassAdd, OnClassAdd)
	ON_BN_CLICKED(IDC_FragAdd, OnFragAdd)
	ON_BN_CLICKED(IDC_ClassClear, OnClassClear)
	ON_BN_CLICKED(IDC_FragClear, OnFragClear)
	ON_BN_CLICKED(IDC_IDAdd, OnIDAdd)
	ON_BN_CLICKED(IDC_IDRemove, OnIDRemove)
	ON_BN_CLICKED(IDC_MDB, OnMdb)
	ON_BN_CLICKED(IDC_SQLITE, OnSqlite)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFICImport message handlers
extern "C" char * WINAPI AllCodes_lang(CString CTYCOD[], long *NOCTY);	//CNT.lib

BOOL CIFICImport::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRecordset m_rs;
	CDatabase m_DB;
	AfxGetModuleState()->m_dwVersion = 0x0601;

	m_SQLite.SetCheck(BST_CHECKED);
	m_BRIFIC="BRIFIC2019SQLiteAccess";
//	CDialog::OnInitDialog();
	m_rs.m_pDatabase=&m_DB;
/*	m_rs.Open(CRecordset::snapshot, _T("select * from ref_adm"));
	CString Temp;
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((int)0,Temp);
		m_AdmList.AddString(Temp);
		m_rs.MoveNext();
	}//end while
	m_rs.Close();*/
	CString CTYCOD[300];
	long NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_AdmList.ResetContent();
	for(int i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
//		Str+=_T(" - ");
//		Str+=Code2NameCTY(CTYCOD[i]);
		m_AdmList.AddString(Str);
	}

	m_FreqCond.AddString("F = F1");
	m_FreqCond.AddString("F <> F1");
	m_FreqCond.AddString("F > F1");
	m_FreqCond.AddString("F >= F1");
	m_FreqCond.AddString("F < F1");
	m_FreqCond.AddString("F <= F1");
	m_FreqCond.AddString("F > F1 and F < F2");
	m_FreqCond.AddString("F >= F1 and F <= F2");
	m_FreqCond.AddString("F1 <= F or F >= F2");
	m_FreqCond.AddString("F1 < F or F > F2");
	m_F2U.SelectString(0,"MHz");
	m_F1U.SelectString(0,"MHz");
	
	CDatabase DB;
	CDBVariant TempVar;
	CString m_Tbl;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	m_Tbl="select * from provisions";
	m_rs.m_pDatabase=&DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);
	m_Fragment.ResetContent();
	CString F1;
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((short)0,F1);
		m_Fragment.AddString(F1);
		m_rs.MoveNext();
	}
	m_rs.Close();
	m_Tbl.Format("select StClassID, StClass%s from StClass where StSrv in ('B','F','MT')",m_Lang); // ('DNA','B','F','MT')
	m_rs.m_pDatabase=&DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);
	CString F2;
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((short)0,F1);
		m_rs.GetFieldValue((short)1,F2);
		m_StationClass.AddString(F1+" - "+F2);
		m_rs.MoveNext();
	}
	m_rs.Close();
	DB.Close();
	TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
extern "C" char * WINAPI Code2NameCTY_lang(CString co, CString mLang);	//CNT.lib

void CIFICImport::OnAdmAdd() 
{
	CString SelItem;
	if(m_AdmList.GetCurSel()!=CB_ERR )
	{
		m_AdmList.GetText(m_AdmList.GetCurSel(),SelItem);
		if(m_AdmSel.FindString(-1,SelItem)==LB_ERR)
			m_AdmSel.AddString(SelItem);	
	}
}

void CIFICImport::OnAdmRemove() 
{
	m_AdmSel.DeleteString(m_AdmSel.GetCurSel());
}

void CIFICImport::OnAdmClear() 
{
	m_AdmSel.ResetContent();	
}

void CIFICImport::OnAdmAddAll() 
{
	CString SelItem;
	int i;
	for(i=0;i<m_AdmList.GetCount();i++)
	{
		m_AdmList.GetText(i,SelItem);
		if(m_AdmSel.FindString(-1,SelItem)==LB_ERR)
			m_AdmSel.AddString(SelItem);
	}
}

void CIFICImport::OnSelchangeFreqCond() 
{
	if(m_FreqCond.GetCurSel()>5)
	{
		m_F2.EnableWindow(TRUE);
		m_F2U.EnableWindow(TRUE);
	}
	else
	{
		m_F2.EnableWindow(FALSE);
		m_F2U.EnableWindow(FALSE);
	}
}

void CIFICImport::OnFreqAdd() 
{
	CString	FreqCond, F1, F2, FreqU, Temp;
	if(m_FreqCond.GetCurSel()!=CB_ERR )
	{
		m_FreqCond.GetText(m_FreqCond.GetCurSel(),FreqCond);
		m_F1.GetWindowText(F1);
		m_F1U.GetWindowText(FreqU);
		Temp.Format("%.6lf MHz",atof(F1)*GetFreqUnit(FreqU));
		FreqCond.Replace(_T("F1"),Temp);
		m_F2.GetWindowText(F2);
		m_F2U.GetWindowText(FreqU);
		Temp.Format("%.6lf MHz",atof(F2)*GetFreqUnit(FreqU));
		FreqCond.Replace(_T("F2"),Temp);
		if(m_FreqCondSel.FindString(-1,FreqCond)==LB_ERR)
			m_FreqCondSel.AddString(FreqCond);
	}
}

double CIFICImport::GetFreqUnit(CString Unit)
{
	if(!Unit.Compare("KHz"))		return 0.001;
	if(!Unit.Compare("MHz"))		return 1.;
	if(!Unit.Compare("GHz"))		return 1000.;
	return 0.000001;
}


void CIFICImport::OnOK() 
{
	CString SQL1,SQL2;
	bool RecFound=false;
//	if(m_SQLite.GetCheck()==BST_CHECKED)
//		((CEdit *)GetDlgItem(IDC_DB3_FILE))->GetWindowText(m_BRIFIC);
	if(m_IDSel.GetCount()==0 && m_AdmSel.GetCount()==0 && m_FreqCondSel.GetCount()==0 && m_ClassSel.GetCount()==0 && m_FragSel.GetCount()==0)
	{
		AfxMessageBox(_Z("At least one criteria should be entered!"));
		return;
	}
	if(m_FXM.GetCheck())
	{
		CCmdTarget::BeginWaitCursor();
		CString F1,F2,FreqU;
		double f1,f2;
		m_F1.GetWindowText(F1);
		m_F1U.GetWindowText(FreqU);
		f1=atof(F1)*GetFreqUnit(FreqU);
		//Temp.Format("%.6lf MHz",atof(F1)*GetFreqUnit(FreqU));
		//FreqCond.Replace(_T("F1"),Temp);
		m_F2.GetWindowText(F2);
		m_F2U.GetWindowText(FreqU);
		f2=atof(F2)*GetFreqUnit(FreqU);
		//Temp.Format("%.6lf MHz",atof(F2)*GetFreqUnit(FreqU));
//		if(f1>=1000 || f2>=1000)
//		{
			SQL2+="SELECT fxm_terra.terrakey, adm_ref_id, assgn_id, ctry, site_name, lat_dec, long_dec, site_alt, stn_cls, '',radius, region, ";
			SQL2+="stn_id, stn_type, prov, pwr_xyz, pwr_ant, pwr_dbw, pwr_eiv, '', emi_cls, bdwdth, energy_dsp, ";
			SQL2+="hgt_agl, polar, ant_dir, azm_max_e, gain_max, gain_type, bmwdth, elev, freq_min, freq_max, freq_assgn, traffic, ";
			SQL2+="freq_carr, freq_dev, nat_srv, notice_typ ";
			SQL1+="FROM fxm_terra, fxm_nat_serv, fxm_ant, fxm_geo, fxm_region, fxm_geo_pt WHERE ";
			SQL1+="fxm_terra.terrakey=fxm_nat_serv.terrakey and fxm_terra.terrakey=fxm_ant.terrakey and fxm_terra.geo_key=fxm_geo.geo_key and ";
			SQL1+="fxm_terra.geo_key=fxm_region.geo_key and fxm_terra.geo_key=fxm_geo_pt.geo_key and stn_type<>'TP' ";
/*		}
		else
		{
			SQL2+="SELECT fxm_terra.terrakey, adm_ref_id, assgn_id, ctry, site_name, lat_dec, long_dec, site_alt, stn_cls, call_sign,radius, region, ";
			SQL2+="stn_id, stn_type, prov, pwr_xyz, pwr_ant, pwr_dbw, pwr_eiv, op_cls, emi_cls, bdwdth, energy_dsp, ";
			SQL2+="hgt_agl, polar, ant_dir, azm_max_e, gain_max, gain_type, bmwdth, elev, freq_min, freq_max, freq_assgn, traffic, ";
			SQL2+="freq_carr, freq_dev, nat_srv ";
			SQL1+="FROM fxm_call_sign,fxm_terra, fxm_nat_serv, fxm_ant, fxm_geo, fxm_region, fxm_geo_pt WHERE fxm_terra.terrakey=fxm_call_sign.terrakey and ";
			SQL1+="fxm_terra.terrakey=fxm_nat_serv.terrakey and fxm_terra.terrakey=fxm_ant.terrakey and fxm_terra.geo_key=fxm_geo.geo_key and ";
			SQL1+="fxm_terra.geo_key=fxm_region.geo_key and fxm_terra.geo_key=fxm_geo_pt.geo_key ";
		}*/
		if(m_AdmSel.GetCount()) 
			SQL1+=" and ctry in (" + GetAdmList() + ")";
		if(m_FreqCondSel.GetCount())
			SQL1+=" and (" + GetFreqCond() + ")";
		if(m_ClassSel.GetCount())
			SQL1+=" and stn_cls in (" + GetClassList() + ")";
		else
			SQL1+=" and stn_cls in (\'FX\',\'FB\',\'ML\')"; //,\'AL\',\'AM\')";
		if(m_FragSel.GetCount())
			SQL1+=" and fragment in (" + GetFragList() + ")";
		if(m_IDSel.GetCount())
			SQL1+=" and fxm_terra.assgn_id in (" + GetIDList() + ")";
		CString Values[50],Tot;
		long Recs=0,Total;
		CDatabase DB1,DB2;
//		if(m_BRIFIC.Left(4)=="ODBC")
			DB1.Open(m_BRIFIC,false,false,_T("ODBC;"),false);
//		else
//			DB1.Open(m_BRIFIC);
		DB2.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
		CRecordset rs,rs2,rs3;
		rs.m_pDatabase=&DB1;
		rs3.m_pDatabase=&DB1;
		//FILE *fp=fopen("c:\\test.txt","wt");
		//fprintf(fp,SQL2+SQL1);
		//fclose(fp);
		rs.Open(CRecordset::snapshot, "select count(fxm_terra.terrakey) "+SQL1);
		rs.GetFieldValue((short)0,Tot);
		Total=atol((LPCTSTR)Tot);
		rs.Close();
		rs.Open(CRecordset::snapshot, SQL2+SQL1);
		m_ImportProgress.SetRange32(0,Total);
		m_ImportProgress.SetStep(10);
		int Ans=IDNO;
		if(Total>0)
		{
			CString Message;
			RecFound=true;
			Message.Format(_Z("%ld record(s) found for non-typical stations. Continue?"),Total);
			Ans=AfxMessageBox(Message,MB_YESNO);
		}
		while(Total>0 && Ans==IDYES)
		{
			CString LastStID, LastEqID, LastEqCatID, LastAntID, LastAntCatID, LastFreqID;
			CString SysType[2];
			if(rs.IsEOF()) break;
			rs2.m_pDatabase=&DB2;
			for(int i=0;i<15;i++)
			{
				rs.GetFieldValue(i,Values[i]);
				Values[i].TrimRight();
			}
			rs.GetFieldValue(38,Values[38]);
			if(Values[14].Left(11)==_T("GE06-Origin"))
				Values[14]=_T("Geneva 2006L");
			if(!Values[8].CompareNoCase(_T("FX")) || !Values[8].CompareNoCase(_T("FB"))
				|| !Values[8].CompareNoCase(_T("AL")))
			{
	// Station
				rs2.Open(CRecordset::snapshot, "select max(StID)+1 from Station");
				rs2.GetFieldValue((short)0,LastStID);
				rs2.Close();
				if(LastStID.IsEmpty()) LastStID=_T("1");
				//Values[3].TrimRight(" ");
				//Values[4].TrimRight(" ");
				//Values[9].TrimRight(" ");
				//Values[2].TrimRight(" ");
				//Values[14].TrimRight(" ");
				//Values[12].TrimRight(" ");
				//Values[8].TrimRight(" ");
				RemoveQuote(&Values[4]);
				SQL1.Format("SELECT %s, -1, '%s','%s','%s','%s','%s',%s,%s,%s,'%s','%s',%s,%s,'%s', 'Fixed','%s', '%s' ", LastStID, Values[0],
					Values[1], Values[2], Values[3], Values[4], (Values[5].IsEmpty()?"0":Values[5]), 
					(Values[6].IsEmpty()?"NULL":Values[6]), (Values[7].IsEmpty()?"NULL":Values[7]),Values[8],Values[9],
					(Values[10].IsEmpty()?"NULL":Values[10]), (Values[11].IsEmpty()?"NULL":Values[11]), Values[12], Values[14],
					Values[38]);
				SQL1=",radius, ituregion, siteID, sttype, provision, NoticeType) "+SQL1;
				SQL1="INSERT INTO Station (StID, LicID, TerraKey, admrefID, Assgn_ID, Country, SiteName, GeoLat, GeoLon, HeightASL, ClassStation, Callsign "+SQL1;
				DB2.ExecuteSQL(SQL1);
	//EqCat
				rs2.Open(CRecordset::snapshot, "select max(EqCatID)+1 from EqCat");
				rs2.GetFieldValue((short)0,LastEqCatID);
				rs2.Close();
				if(LastEqCatID.IsEmpty()) LastEqCatID=_T("1");
				SQL1.Format(_T("SELECT system_type from fxm_system_type where terrakey=%s"), Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				i=0;
				while(!rs3.IsEOF() && i<2)
				{
					rs3.GetFieldValue((short)0,SysType[i++]);
					SysType[i-1].TrimRight();
					rs3.MoveNext();
				}
				rs3.Close();
				for(i=15;i<23;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				//Values[15].TrimRight(" ");
				//Values[18].TrimRight(" ");
				//Values[19].TrimRight(" ");
				//Values[20].TrimRight(" ");
				SQL1.Format("SELECT %s, '%s','%s','%s',%s, '%s', '%s'", LastEqCatID,
					Values[15],	Values[18], Values[19],(Values[22].IsEmpty()?"NULL":Values[22]),
					SysType[0],SysType[1]);
				SQL2="INSERT INTO EqCat (EqCatID, powertype, radpowertype, classop, endisp, SystemType1, SystemType2) ";
				SQL1=SQL2+SQL1;
				DB2.ExecuteSQL(SQL1);

				
	//Equipment
				rs2.Open(CRecordset::snapshot, "select max(EqID)+1 from Equipment");
				rs2.GetFieldValue((short)0,LastEqID);
				rs2.Close();
				if(LastEqID.IsEmpty()) LastEqID=_T("1");
				double pwr1=pow(10.,atof(Values[16])/10),pwr2=pow(10.,atof(Values[17])/10);
				SQL1.Format("SELECT %s, %s,%s,%lf,%lf", LastEqID, LastEqCatID, LastStID
					, pwr1, pwr2);
				SQL1="INSERT INTO Equipment (EqID, EqCatID, StID, pwr2ant, radpwr) "+SQL1;
				DB2.ExecuteSQL(SQL1);
	//AntCat				
				rs2.Open(CRecordset::snapshot, "select max(AntCatID)+1 from AntCat");
				rs2.GetFieldValue((short)0,LastAntCatID);
				rs2.Close();
				if(LastAntCatID.IsEmpty()) LastAntCatID=_T("1");
				for(i=23;i<33;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				if(Values[24].IsEmpty())
					Values[24]=_T("M");
				//Values[24].TrimRight(" ");
				//Values[25].TrimRight(" ");
				//Values[28].TrimRight(" ");
				//Values[25]=Values[25].Left(1);
				if(Values[25].Left(1)==_T("N"))
				{
					Values[25]=_T("N");
					Values[29]=_T("360.0");
				}
				else
				{
					Values[25]=_T("D");
					if(Values[29].IsEmpty() || atof(Values[29])>359.0)
						Values[29]=_T("359.0");
				}
				SQL1.Format("SELECT %s,'%s','%s',%s,'%s',%s,%s,%s,%s,'C','%09ld',NULL", LastAntCatID,
					Values[24], Values[25],
					(Values[27].IsEmpty()?"NULL":Values[27]),Values[28],(Values[29].IsEmpty()?"NULL":Values[29]),
					(Values[29].IsEmpty()?"NULL":Values[29]),
					(Values[31].IsEmpty()?"NULL":Values[31]),(Values[32].IsEmpty()?"NULL":Values[32]),atol(LastAntCatID));
				SQL1="INSERT INTO AntCat (AntCatID, Pol, AntDir, gain, gaintype, beamwidthH, beamwidthV, freqfrom, freqto,ClassOfAnt,AntName,MaxEffHght) "+SQL1;
				DB2.ExecuteSQL(SQL1);
	//Antenna
				rs2.Open(CRecordset::snapshot, "select max(AntID)+1 from Antenna");
				rs2.GetFieldValue((short)0,LastAntID);
				rs2.Close();
				if(LastAntID.IsEmpty()) LastAntID=_T("1");
				SQL1.Format("SELECT %s, %s,%s, %s,%s,%s", LastAntID, LastAntCatID, LastEqID,(Values[23].IsEmpty()?"37.5":Values[23])
					, (Values[26].IsEmpty()?"0":Values[26]),(Values[30].IsEmpty()?"NULL":Values[30]));
				SQL1="INSERT INTO Antenna (AntID, AntCatID, EqID, AntHeightAGL, azimuth, elevation) "+SQL1;
				DB2.ExecuteSQL(SQL1);

	//Ant pattern
//////////////////////////////////////////////////////////////////////////////
				SQL1.Format("SELECT %s, azm, polar, attn from fxm_ant_diag where terrakey=%s and Polar='H'", LastAntCatID, Values[0]);
				double AngV[361]={0.0},PattV[361]={0.0},AngH[361]={0.0},PattH[361]={0.0};
				rs3.Open(CRecordset::snapshot,SQL1);
				if(rs3.GetRecordCount()>0)
				{
					int i=0;
					while(!rs3.IsEOF())
					{
						double azm, attn;
						CDBVariant FVal;
						rs3.GetFieldValue(_T("azm"),FVal);
						AngH[i]=azm=FVal.m_dblVal;
						rs3.GetFieldValue(_T("attn"),FVal);
						PattH[i]=attn=FVal.m_dblVal;
						rs3.MoveNext();
						i++;
					}
					double PatternTmp[361],AngleTmp[361];
					//Ang[i] = 360;
					//Patt[i] = Patt[0];

					for (int j=0;j<360;j++)
					{
						AngleTmp[j]=j;
						PatternTmp[j] = Interp2(AngH,PattH,j,i) ;
					}
					//PatternTmp[360]=PatternTmp[0];
					//AngleTmp[360]=360.;
					for(i=0;i<360;i++)
					{
						AngH[i]=AngleTmp[i];
						PattH[i]=PatternTmp[i];
					}
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						SQL1.Format("SELECT %s, %d, 'H', %lf ", LastAntCatID, PattItem, PattH[PattItem]);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
					}		
				}
				else
				{
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						AngH[PattItem]=PattItem;
						PattH[PattItem]=0.0;
						SQL1.Format("SELECT %s, %d, 'H', 0.0 ", LastAntCatID, PattItem);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
					}
				}
				rs3.Close();
				SQL1.Format("SELECT %s, azm, polar, attn from fxm_ant_diag where terrakey=%s and Polar='V'", LastAntCatID, Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				if(rs3.GetRecordCount()>0)
				{
					int i=0;
					while(!rs3.IsEOF())
					{
						double azm, attn;
						CDBVariant FVal;
						rs3.GetFieldValue(_T("azm"),FVal);
						AngV[i]=azm=FVal.m_dblVal;
						rs3.GetFieldValue(_T("attn"),FVal);
						PattV[i]=attn=FVal.m_dblVal;
						rs3.MoveNext();
						i++;
					}
					double PatternTmp[361],AngleTmp[361];
					//Ang[i] = 360;
					//Patt[i] = Patt[0];

					for (int j=0;j<360;j++)
					{
						AngleTmp[j]=j;
						PatternTmp[j] = Interp2(AngV,PattV,j,i) ;
					}
					//PatternTmp[360]=PatternTmp[0];
					//AngleTmp[360]=360.;
					for(i=0;i<360;i++)
					{
						AngV[i]=AngleTmp[i];
						PattV[i]=PatternTmp[i];
					}
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						SQL1.Format("SELECT %s, %d, 'V', %lf ", LastAntCatID, PattItem, PattV[PattItem]);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
					}
				}
				else
				{
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						AngV[PattItem]=PattItem;
						PattV[PattItem]=0.0;
						SQL1.Format("SELECT %s, %d, 'V', 0.0 ", LastAntCatID, PattItem);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
					}
				}
				rs3.Close();
				AntennaSaveTxt(LastAntCatID, 0.0, atof(Values[29]), atof(Values[29]), atof(Values[31]),
					atof(Values[32]), Values[24], PattV, PattH,atof(Values[26]));

	//Ant height
				SQL1.Format("SELECT azm, eff_hgt from fxm_ant_hgt where terrakey=%s ", Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				while(!rs3.IsEOF())
				{
					CString Azm, EffHgt;
					rs3.GetFieldValue((int)0,Azm);
					rs3.GetFieldValue((int)1,EffHgt);
					SQL1.Format(_T("Select %s,%s,%s "), LastAntID, Azm, EffHgt);
					SQL1="INSERT INTO AntHgt ( AntID, azm, EffHgt ) "+SQL1;
					DB2.ExecuteSQL(SQL1);
					rs3.MoveNext();
				}
				rs3.Close();
///////////////////////////////////////////////////////////////////				
				
	//Frequency
				rs2.Open(CRecordset::snapshot, "select max(FreqID)+1 from Frequency");
				rs2.GetFieldValue((short)0,LastFreqID);
				rs2.Close();
				if(LastFreqID.IsEmpty()) LastFreqID=_T("1");
				for(i=33;i<38;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				//Values[37].TrimRight(" ");
				Values[33].Format(_T("%lf"),atof(Values[33])*1000000.);
//				CString RecsSQL,FValue;
				double RXFreq=0;
/*				CRecordset RSet;
				RSet.m_pDatabase=&DB1;
				if(!Values[8].CompareNoCase(_T("FX")))
				{
					RecsSQL.Format(_T("select freq_assgn from fxm_rx,fxm_terra where fxm_rx.terrakey=%s and fxm_rx.geo_key=fxm_terra.geo_key"),Values[0]);
					RSet.Open(CRecordset::snapshot,RecsSQL);
					if(RSet.GetRecordCount())
					{
						RSet.GetFieldValue((short)0,FValue);
						RXFreq=atof(FValue)*1000000.;
					}
					RSet.Close();
				}
				if(!Values[29].CompareNoCase(_T("FB")))
				{
				}*/
				SQL1.Format("SELECT %s, %s, %s, %s, %s, %s, '%s','%s',%s,'%s',%lf", LastFreqID, LastEqID, (Values[33].IsEmpty()?"NULL":Values[33]),
					(Values[34].IsEmpty()?"NULL":Values[34]),(Values[35].IsEmpty()?"NULL":Values[35]),
					(Values[36].IsEmpty()?"NULL":Values[36]),Values[37], Values[20], (Values[21].IsEmpty()?"NULL":Values[21]),BandWidthCode(atof(Values[21]))+Values[20],
					RXFreq);
				SQL1="INSERT INTO Frequency ( FreqID, EqID, Frequency, traffic, reffreq, freqdev, natserv, emissioncl, bandwidth, EmDes, RespFreq ) "+SQL1;
				DB2.ExecuteSQL(SQL1);
			}
			if(!Values[8].CompareNoCase(_T("ML")) || !Values[8].CompareNoCase(_T("AM")))
			{
	// Mobile
				rs2.Open(CRecordset::snapshot, "select max(MobID)+1 from Mobiles");
				rs2.GetFieldValue((short)0,LastStID);
				rs2.Close();
				if(LastStID.IsEmpty()) LastStID=_T("1");
				//Values[3].TrimRight(" ");
				//Values[4].TrimRight(" ");
				//Values[9].TrimRight(" ");
				//Values[2].TrimRight(" ");
				//Values[14].TrimRight(" ");
				//Values[12].TrimRight(" ");
				//Values[8].TrimRight(" ");
				RemoveQuote(&Values[4]);
			/*	SQL1.Format("SELECT %s, -1, '%s','%s','%s','%s','%s','%s', %s, %s, 'Handheld','%s' ", LastStID, Values[1], 
					Values[3], Values[12], Values[4], Values[8],Values[9],
					(Values[10].IsEmpty()?"NULL":Values[10]), (Values[11].IsEmpty()?"NULL":Values[11]), Values[14]);
				SQL1=",radius, ituregion, sttype, provision) "+SQL1;
				SQL1="INSERT INTO Mobiles (MobID, LicID, admrefID, Country, MobileID, MobName, ClassStation, Callsign "+SQL1;*/
				
				SQL1.Format("SELECT %s, -1, '%s','%s','%s','%s','%s','%s', %s, %s, %s, %s, 'Handheld','%s' ", LastStID, Values[1], 
					Values[3], Values[12], Values[4], Values[8],Values[9],(Values[5].IsEmpty()?"0":Values[5]), 
					(Values[6].IsEmpty()?"0":Values[6]), (Values[10].IsEmpty()?"0":Values[10]), (Values[11].IsEmpty()?"0":Values[11]), Values[14]);
				SQL1=", GeoLat, GeoLon, radius, ituregion, sttype, provision) "+SQL1;
				SQL1="INSERT INTO Mobiles (MobID, LicID, admrefID, Country, MobileID, MobName, ClassStation, Callsign "+SQL1;
				try{
					DB2.ExecuteSQL(SQL1);
				}
				catch (int e)
				{
				}
	//EqCat
				rs2.Open(CRecordset::snapshot, "select max(EqCatID)+1 from EqCat");
				rs2.GetFieldValue((short)0,LastEqCatID);
				rs2.Close();
				if(LastEqCatID.IsEmpty()) LastEqCatID=_T("1");
/*				for(i=15;i<23;i++)
					rs.GetFieldValue(i,Values[i]);
				Values[15].TrimRight(" ");
				Values[18].TrimRight(" ");
				Values[19].TrimRight(" ");
				Values[20].TrimRight(" ");
				SQL1.Format("SELECT %s, '%s','%s','%s',%s", LastEqCatID,
					Values[15],	Values[18], Values[19],(Values[22].IsEmpty()?"NULL":Values[22]));
				SQL2="INSERT INTO EqCat (EqCatID, powertype, radpowertype, classop, endisp) ";*/
				SQL1.Format(_T("SELECT system_type from fxm_system_type where terrakey=%s"), Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				i=0;
				while(!rs3.IsEOF() && i<2)
				{
					rs3.GetFieldValue((short)0,SysType[i++]);
					SysType[i-1].TrimRight();
					rs3.MoveNext();
				}
				rs3.Close();
				for(i=15;i<23;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				//Values[15].TrimRight(" ");
				//Values[18].TrimRight(" ");
				//Values[19].TrimRight(" ");
				//Values[20].TrimRight(" ");
				SQL1.Format("SELECT %s, '%s','%s','%s',%s, '%s', '%s'", LastEqCatID,
					Values[15],	Values[18], Values[19],(Values[22].IsEmpty()?"NULL":Values[22]),
					SysType[0],SysType[1]);
				SQL2="INSERT INTO EqCat (EqCatID, powertype, radpowertype, classop, endisp, SystemType1, SystemType2) ";
				SQL1=SQL2+SQL1;
				DB2.ExecuteSQL(SQL1);
	//Equipment
				rs2.Open(CRecordset::snapshot, "select max(EqID)+1 from Equipment");
				rs2.GetFieldValue((short)0,LastEqID);
				rs2.Close();
				if(LastEqID.IsEmpty()) LastEqID=_T("1");
				double pwr1=pow(10.,atof(Values[16])/10),pwr2=pow(10.,atof(Values[17])/10);
				SQL1.Format("SELECT %s, %s,%s,%lf,%lf", LastEqID, LastEqCatID, LastStID
					, pwr1, pwr2);
				SQL1="INSERT INTO Equipment (EqID, EqCatID, MobID, pwr2ant, radpwr) "+SQL1;
				DB2.ExecuteSQL(SQL1);
	//AntCat				
				rs2.Open(CRecordset::snapshot, "select max(AntCatID)+1 from AntCat");
				rs2.GetFieldValue((short)0,LastAntCatID);
				rs2.Close();
				if(LastAntCatID.IsEmpty()) LastAntCatID=_T("1");
				for(i=23;i<33;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				if(Values[24].IsEmpty())
					Values[24]=_T("M");
				//Values[24].TrimRight(" ");
				//Values[25].TrimRight(" ");
				//Values[28].TrimRight(" ");
				SQL1.Format("SELECT %s,'%s','%s',%s,'%s',%lf,%lf,%s,%s,'C','DEFAULT',NULL", LastAntCatID,
					Values[24], _T("N"),
					(Values[27].IsEmpty()?"NULL":Values[27]),Values[28],360.0,360.0,
					(Values[31].IsEmpty()?"NULL":Values[31]),(Values[32].IsEmpty()?"NULL":Values[32]));
				SQL1="INSERT INTO AntCat (AntCatID, Pol, AntDir, gain, gaintype, beamwidthH, beamwidthV, freqfrom, freqto,ClassOfAnt,AntName,MaxEffHght) "+SQL1;
				DB2.ExecuteSQL(SQL1);
	//Antenna
				rs2.Open(CRecordset::snapshot, "select max(AntID)+1 from Antenna");
				rs2.GetFieldValue((short)0,LastAntID);
				rs2.Close();
				if(LastAntID.IsEmpty()) LastAntID=_T("1");
				SQL1.Format("SELECT %s, %s,%s, %s,%s,%s", LastAntID, LastAntCatID, LastEqID,"1.5"
					, (Values[26].IsEmpty()?"0":Values[26]),(Values[30].IsEmpty()?"NULL":Values[30]));
				SQL1="INSERT INTO Antenna (AntID, AntCatID, EqID, AntHeightAGL, azimuth, elevation) "+SQL1;
				DB2.ExecuteSQL(SQL1);

	//Ant pattern
//////////////////////////////////////////////////////////////////////////////
				for(int PattItem=0;PattItem<360;PattItem++)
				{
					SQL1.Format("SELECT %s, %d, 'H', 0.0 ", LastAntCatID, PattItem);
					SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
					DB2.ExecuteSQL(SQL1);
					SQL1.Format("SELECT %s, %d, 'V', 0.0 ", LastAntCatID, PattItem);
					SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
					DB2.ExecuteSQL(SQL1);
				}

///////////////////////////////////////////////////////////////////////////////////////				
	//Frequency
				rs2.Open(CRecordset::snapshot, "select max(FreqID)+1 from Frequency");
				rs2.GetFieldValue((short)0,LastFreqID);
				rs2.Close();
				if(LastFreqID.IsEmpty()) LastFreqID=_T("1");
				for(i=33;i<38;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				//Values[37].TrimRight(" ");
				Values[33].Format(_T("%lf"),atof(Values[33])*1000000.);
				CString RecsSQL,FValue;
				double RXFreq=0;
/*				CRecordset RSet;
				RSet.m_pDatabase=&DB1;
				if(!Values[8].CompareNoCase(_T("FX")))
				{
					RecsSQL.Format(_T("select freq_assgn from fxm_rx,fxm_terra where fxm_rx.terrakey=%s and fxm_rx.geo_key=fxm_terra.geo_key"),Values[0]);
					RSet.Open(CRecordset::snapshot,RecsSQL);
					if(RSet.GetRecordCount())
					{
						RSet.GetFieldValue((short)0,FValue);
						RXFreq=atof(FValue)*1000000.;
					}
					RSet.Close();
				}
				if(!Values[8].CompareNoCase(_T("FB")))
				{
				}*/
				SQL1.Format("SELECT %s, %s, %s, %s, %s, %s, '%s','%s',%s,'%s',%lf", LastFreqID, LastEqID, (Values[33].IsEmpty()?"NULL":Values[33]),
					(Values[34].IsEmpty()?"NULL":Values[34]),(Values[35].IsEmpty()?"NULL":Values[35]),
					(Values[36].IsEmpty()?"NULL":Values[36]),Values[37], Values[20], (Values[21].IsEmpty()?"NULL":Values[21]),BandWidthCode(atof(Values[21]))+Values[20],
					RXFreq);
				SQL1="INSERT INTO Frequency ( FreqID, EqID, Frequency, traffic, reffreq, freqdev, natserv, emissioncl, bandwidth, EmDes, RespFreq ) "+SQL1;
				DB2.ExecuteSQL(SQL1);
			}
			
/////////////////////////////////////////////
///   Add receiver / receiving area

			if(!Values[8].CompareNoCase(_T("ML")) && Values[13].CompareNoCase(_T("RX")))
			{
				SQL2.Format(_T(" fxm_tx, fxm_geo where fxm_tx.geo_key=fxm_geo.geo_key and terrakey=%s"),Values[0]);
				SQL2=_T("select fxm_geo.geo_key, geo_type, ctry, site_name, zone_id, radius from")+SQL2;
				rs3.Open(CRecordset::snapshot, SQL2);
				while(!rs3.IsEOF())
				{
					CRecordset rs4,rs5;
					rs5.m_pDatabase=rs4.m_pDatabase=rs3.m_pDatabase;
					CString GeoType, RecID, Country, Zone, GeoKey, Radius, SiteName;
					rs3.GetFieldValue(_T("geo_key"),GeoKey);
					rs3.GetFieldValue(_T("geo_type"),GeoType);
					rs3.GetFieldValue(_T("ctry"),Country);
					rs3.GetFieldValue(_T("zone_id"),Zone);
					rs3.GetFieldValue(_T("radius"),Radius);
					rs3.GetFieldValue(_T("site_name"),SiteName);
					GeoType.TrimRight();
					Country.TrimRight();
					Zone.TrimRight();
					rs2.Open(CRecordset::snapshot, "select max(ReceiverID)+1 from Link");
					rs2.GetFieldValue((short)0,RecID);
					rs2.Close();
					if(RecID.IsEmpty()) RecID=_T("1");
					CString Lon, Lat, LastAntID2, LastFreqID2, LastStID2;
					int i=0;
					SQL2.Format(_T("select * from fxm_geo_pt where geo_key=%s order by geo_pt"),GeoKey);
					rs4.Open(CRecordset::snapshot, SQL2);
					if(!rs4.IsEOF())
					{
						rs4.GetFieldValue(_T("long_dec"),Lon);
						rs4.GetFieldValue(_T("lat_dec"),Lat);
						rs2.Open(CRecordset::snapshot, "select max(StID)+1 from Station");
						rs2.GetFieldValue((short)0,LastStID2);
						rs2.Close();
						if(LastStID2.IsEmpty()) LastStID2=_T("1");
						SQL1.Format("SELECT %s, -1, '-1','%s','%s',%s,%s,'FB',%s, 'Base','%s', '%s' ", LastStID2,  
							Values[3], Values[4], Values[5], Values[6],(Values[11].IsEmpty()?"NULL":Values[11]),
							Values[14], Values[38]==_T("G13")?_T("G12"):_T("T12"));
						SQL1=", ituregion, sttype, provision, NoticeType) "+SQL1;
						SQL1="INSERT INTO Station (StID, LicID, TerraKey, Country, SiteName, GeoLat, GeoLon, ClassStation "+SQL1;
						DB2.ExecuteSQL(SQL1);
			//Equipment
						rs2.Open(CRecordset::snapshot, "select max(EqID)+1 from Equipment");
						rs2.GetFieldValue((short)0,LastEqID);
						rs2.Close();
						if(LastEqID.IsEmpty()) LastEqID=_T("1");
						SQL1.Format("SELECT %s, %s,%s,%lf,%lf", LastEqID, LastEqCatID, LastStID2
							, 10.0, 10.0);
						if(!Values[8].CompareNoCase(_T("FB")))
						{
							SQL1="INSERT INTO Equipment (EqID, EqCatID, MobID, pwr2ant, radpwr) "+SQL1;
						}
						else
						{
							SQL1="INSERT INTO Equipment (EqID, EqCatID, StID, pwr2ant, radpwr) "+SQL1;
						}
						DB2.ExecuteSQL(SQL1);
						if(Values[24].IsEmpty())
							Values[24]=_T("M");
			//AntCat				
						rs2.Open(CRecordset::snapshot, "select max(AntCatID)+1 from AntCat");
						rs2.GetFieldValue((short)0,LastAntCatID);
						rs2.Close();
						if(LastAntCatID.IsEmpty()) LastAntCatID=_T("1");
						Values[25]=Values[25].Left(1);
						if(Values[25].Left(1)==_T("N"))
						{
							Values[25]=_T("N");
							Values[29]=_T("360.0");
						}
						else
						{
							Values[25]=_T("D");
							if(Values[29].IsEmpty() || atof(Values[29])>359.0)
								Values[29]=_T("359.0");
						}
						SQL1.Format("SELECT %s,'%s','%s',%s,'%s',%s,%s,%s,%s,'C','%s',NULL", LastAntCatID,
							Values[24], Values[25],
							(Values[27].IsEmpty()?"NULL":Values[27]),Values[28],(Values[29].IsEmpty()?"NULL":Values[29]),
							(Values[29].IsEmpty()?"NULL":Values[29]),
							(Values[31].IsEmpty()?"NULL":Values[31]),(Values[32].IsEmpty()?"NULL":Values[32]),Values[2]);
						SQL1="INSERT INTO AntCat (AntCatID, Pol, AntDir, gain, gaintype, beamwidthH, beamwidthV, freqfrom, freqto,ClassOfAnt,AntName,MaxEffHght) "+SQL1;
						DB2.ExecuteSQL(SQL1);
						SQL1.Format("SELECT %s, azm, polar, attn from fxm_ant_diag where terrakey=%s and Polar='H'", LastAntCatID, Values[0]);
						double AngV[361]={0.0},PattV[361]={0.0},AngH[361]={0.0},PattH[361]={0.0};
						rs5.Open(CRecordset::snapshot,SQL1);
						if(rs5.GetRecordCount()>0)
						{
							int i=0;
							while(!rs5.IsEOF())
							{
								double azm, attn;
								CDBVariant FVal;
								rs5.GetFieldValue(_T("azm"),FVal);
								AngH[i]=azm=FVal.m_dblVal;
								rs5.GetFieldValue(_T("attn"),FVal);
								PattH[i]=attn=FVal.m_dblVal;
								rs5.MoveNext();
								i++;
							}
							double PatternTmp[361],AngleTmp[361];
							//Ang[i] = 360;
							//Patt[i] = Patt[0];

							for (int j=0;j<360;j++)
							{
								AngleTmp[j]=j;
								PatternTmp[j] = Interp2(AngH,PattH,j,i) ;
							}
							//PatternTmp[360]=PatternTmp[0];
							//AngleTmp[360]=360.;
							for(i=0;i<360;i++)
							{
								AngH[i]=AngleTmp[i];
								PattH[i]=PatternTmp[i];
							}
							for(int PattItem=0;PattItem<360;PattItem++)
							{
								SQL1.Format("SELECT %s, %d, 'H', %lf ", LastAntCatID, PattItem, PattH[PattItem]);
								SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
								DB2.ExecuteSQL(SQL1);
							}		
						}
						else
						{
							for(int PattItem=0;PattItem<360;PattItem++)
							{
								AngH[PattItem]=PattItem;
								PattH[PattItem]=0.0;
								SQL1.Format("SELECT %s, %d, 'H', 0.0 ", LastAntCatID, PattItem);
								SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
								DB2.ExecuteSQL(SQL1);
							}
						}
						rs5.Close();
						SQL1.Format("SELECT %s, azm, polar, attn from fxm_ant_diag where terrakey=%s and Polar='V'", LastAntCatID, Values[0]);
						rs5.Open(CRecordset::snapshot,SQL1);
						if(rs5.GetRecordCount()>0)
						{
							int i=0;
							while(!rs5.IsEOF())
							{
								double azm, attn;
								CDBVariant FVal;
								rs5.GetFieldValue(_T("azm"),FVal);
								AngV[i]=azm=FVal.m_dblVal;
								rs5.GetFieldValue(_T("attn"),FVal);
								PattV[i]=attn=FVal.m_dblVal;
								rs5.MoveNext();
								i++;
							}
							double PatternTmp[361],AngleTmp[361];
							//Ang[i] = 360;
							//Patt[i] = Patt[0];

							for (int j=0;j<360;j++)
							{
								AngleTmp[j]=j;
								PatternTmp[j] = Interp2(AngV,PattV,j,i) ;
							}
							//PatternTmp[360]=PatternTmp[0];
							//AngleTmp[360]=360.;
							for(i=0;i<360;i++)
							{
								AngV[i]=AngleTmp[i];
								PattV[i]=PatternTmp[i];
							}
							for(int PattItem=0;PattItem<360;PattItem++)
							{
								SQL1.Format("SELECT %s, %d, 'V', %lf ", LastAntCatID, PattItem, PattV[PattItem]);
								SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
								DB2.ExecuteSQL(SQL1);
							}
						}
						else
						{
							for(int PattItem=0;PattItem<360;PattItem++)
							{
								AngV[PattItem]=PattItem;
								PattV[PattItem]=0.0;
								SQL1.Format("SELECT %s, %d, 'V', 0.0 ", LastAntCatID, PattItem);
								SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
								DB2.ExecuteSQL(SQL1);
							}
						}
						rs5.Close();
						AntennaSaveTxt(LastAntCatID, 0.0, atof(Values[29]), atof(Values[29]), atof(Values[31]),
							atof(Values[32]), Values[24], PattV, PattH,atof(Values[26]));
			//Antenna
						rs2.Open(CRecordset::snapshot, "select max(AntID)+1 from Antenna");
						rs2.GetFieldValue((short)0,LastAntID2);
						rs2.Close();
						if(LastAntID2.IsEmpty()) LastAntID2=_T("1");
						SQL1.Format("SELECT %s, %s,%s,%s,0,0", LastAntID2, LastAntCatID, LastEqID,(Values[23].IsEmpty()?"37.5":Values[23]));
						SQL1="INSERT INTO Antenna (AntID, AntCatID, EqID, AntHeightAGL, azimuth, elevation) "+SQL1;
						DB2.ExecuteSQL(SQL1);
			//Ant height
						SQL1.Format("SELECT azm, eff_hgt from fxm_ant_hgt where terrakey=%s ", Values[0]);
						rs5.Open(CRecordset::snapshot,SQL1);
						while(!rs5.IsEOF())
						{
							CString Azm, EffHgt;
							rs5.GetFieldValue((int)0,Azm);
							rs5.GetFieldValue((int)1,EffHgt);
							SQL1.Format(_T("Select %s,%s,%s "), LastAntID, Azm, EffHgt);
							SQL1="INSERT INTO AntHgt ( AntID, azm, EffHgt ) "+SQL1;
							DB2.ExecuteSQL(SQL1);
							rs5.MoveNext();
						}
						rs5.Close();
			//Frequency
						rs2.Open(CRecordset::snapshot, "select max(FreqID)+1 from Frequency");
						rs2.GetFieldValue((short)0,LastFreqID2);
						rs2.Close();
						if(LastFreqID2.IsEmpty()) LastFreqID2=_T("1");
						SQL1.Format("SELECT %s, %s, 0.0, 'CP','%s',%s,'%s',%s", LastFreqID2, LastEqID, 
							Values[20], (Values[21].IsEmpty()?"NULL":Values[21]),BandWidthCode(atof(Values[21]))+Values[20],
							(Values[33].IsEmpty()?"NULL":Values[33]));
						SQL1="INSERT INTO Frequency ( FreqID, EqID, Frequency, natserv, emissioncl, bandwidth, EmDes, RespFreq ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
						SQL2.Format(_T("Country, RecLat, RecLon) select %s, 1, 1, 'POINT', %s, %s, %s, %s, '%s', %s, %s"),
							RecID, LastFreqID, LastFreqID2, LastAntID, LastAntID2, Country, Lat, Lon);
						SQL2=_T("Insert into link (ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID,")+SQL2;
						DB2.ExecuteSQL(SQL2);
					}
					rs4.Close();

					if(GeoType==_T("CIRCLE"))
					{
						CString Lon, Lat;
						SQL2.Format(_T("select * from fxm_geo_pt where geo_key=%s order by geo_pt"),GeoKey);
						rs4.Open(CRecordset::snapshot, SQL2);
						if(!rs4.IsEOF())
						{
							rs4.GetFieldValue(_T("long_dec"),Lon);
							rs4.GetFieldValue(_T("lat_dec"),Lat);
							SQL2.Format(_T("Update Mobiles Set GeoLat= %s, GeoLon= %s, Radius= %s where MobID= %s"),
								Lat, Lon, Radius, LastStID);
							DB2.ExecuteSQL(SQL2);
						}
						rs4.Close();
					}
					if(GeoType==_T("ZONE"))
					{
						Zone.TrimRight();
						SQL2.Format(_T("Update Mobiles Set AreaOfTrans= '%s', GeoLat= '', GeoLon= '', Radius= '' where MobID= %s"),
							Zone, LastStID);
						DB2.ExecuteSQL(SQL2);
					}
					rs3.MoveNext();
				}
			}
			else if(!Values[8].CompareNoCase(_T("FX")) || !Values[8].CompareNoCase(_T("FB")))
			{
				SQL2.Format(_T(" fxm_rx, fxm_geo where fxm_rx.geo_key=fxm_geo.geo_key and terrakey=%s"),Values[0]);
				SQL2=_T("select fxm_geo.geo_key, geo_type, ctry, site_name, zone_id, radius from")+SQL2;
				rs3.Open(CRecordset::snapshot, SQL2);
				while(!rs3.IsEOF())
				{
					CRecordset rs4;
					rs4.m_pDatabase=rs3.m_pDatabase;
					CString GeoType, RecID, Country, Zone, GeoKey, Radius, SiteName;
					rs3.GetFieldValue(_T("geo_key"),GeoKey);
					rs3.GetFieldValue(_T("geo_type"),GeoType);
					rs3.GetFieldValue(_T("ctry"),Country);
					rs3.GetFieldValue(_T("zone_id"),Zone);
					rs3.GetFieldValue(_T("radius"),Radius);
					rs3.GetFieldValue(_T("site_name"),SiteName);
					GeoType.TrimRight();
					Country.TrimRight();
					Zone.TrimRight();
					rs2.Open(CRecordset::snapshot, "select max(ReceiverID)+1 from Link");
					rs2.GetFieldValue((short)0,RecID);
					rs2.Close();
					if(RecID.IsEmpty()) RecID=_T("1");
					if(GeoType==_T("POINT"))
					{
						CString Lon, Lat, LastAntID2, LastFreqID2;
						int i=0;
						SQL2.Format(_T("select * from fxm_geo_pt where geo_key=%s order by geo_pt"),GeoKey);
						rs4.Open(CRecordset::snapshot, SQL2);
						if(!rs4.IsEOF())
						{
							rs4.GetFieldValue(_T("long_dec"),Lon);
							rs4.GetFieldValue(_T("lat_dec"),Lat);
							Values[23]=_T("37.5");
							if(!Values[8].CompareNoCase(_T("FX")))
							{
								rs2.Open(CRecordset::snapshot, "select max(StID)+1 from Station");
								rs2.GetFieldValue((short)0,LastStID);
								rs2.Close();
								if(LastStID.IsEmpty()) LastStID=_T("1");
								SQL1.Format("SELECT %s, -1, '-1','%s','%s',%s,%s,'FX',%s, 'Fixed','%s' ", LastStID,  
									Country, SiteName, Lat, Lon,(Values[11].IsEmpty()?"NULL":Values[11]),
									Values[14]);
								SQL1=", ituregion, sttype, provision) "+SQL1;
								SQL1="INSERT INTO Station (StID, LicID, TerraKey, Country, SiteName, GeoLat, GeoLon, ClassStation "+SQL1;
							}
							if(!Values[8].CompareNoCase(_T("FB")))
							{
								rs2.Open(CRecordset::snapshot, "select max(MobID)+1 from Mobiles");
								rs2.GetFieldValue((short)0,LastStID);
								rs2.Close();
								if(LastStID.IsEmpty()) LastStID=_T("1");
								SQL1.Format("SELECT %s, -1, '-1','%s','%s',%s,%s,'ML',%s, 'Mobile','Article 11' ", LastStID,  
									Country, SiteName, Lat, Lon,(Values[11].IsEmpty()?"NULL":Values[11]));
								SQL1=", ituregion, sttype, provision) "+SQL1;
								SQL1="INSERT INTO Station (StID, LicID, TerraKey, Country, SiteName, GeoLat, GeoLon, ClassStation "+SQL1;
								Values[23]=_T("1.5");
							}
							if(!Values[8].CompareNoCase(_T("ML")))
							{
								rs2.Open(CRecordset::snapshot, "select max(StID)+1 from Station");
								rs2.GetFieldValue((short)0,LastStID);
								rs2.Close();
								if(LastStID.IsEmpty()) LastStID=_T("1");
								SQL1.Format("SELECT %s, -1, '-1','%s','%s',%s,%s,'FB',%s, 'Base','Article 11' ", LastStID,  
									Country, SiteName, Lat, Lon,(Values[11].IsEmpty()?"NULL":Values[11]));
								SQL1=", ituregion, sttype, provision) "+SQL1;
								SQL1="INSERT INTO Station (StID, LicID, TerraKey, Country, SiteName, GeoLat, GeoLon, ClassStation "+SQL1;
							}
							DB2.ExecuteSQL(SQL1);
				//Equipment
							rs2.Open(CRecordset::snapshot, "select max(EqID)+1 from Equipment");
							rs2.GetFieldValue((short)0,LastEqID);
							rs2.Close();
							if(LastEqID.IsEmpty()) LastEqID=_T("1");
							SQL1.Format("SELECT %s, %s,%s,%lf,%lf", LastEqID, LastEqCatID, LastStID
								, 10.0, 10.0);
							if(!Values[8].CompareNoCase(_T("FB")))
							{
								SQL1="INSERT INTO Equipment (EqID, EqCatID, MobID, pwr2ant, radpwr) "+SQL1;
							}
							else
							{
								SQL1="INSERT INTO Equipment (EqID, EqCatID, StID, pwr2ant, radpwr) "+SQL1;
							}
							DB2.ExecuteSQL(SQL1);
							if(Values[24].IsEmpty())
								Values[24]=_T("M");
				//AntCat				
							rs2.Open(CRecordset::snapshot, "select max(AntCatID)+1 from AntCat");
							rs2.GetFieldValue((short)0,LastAntCatID);
							rs2.Close();
							if(LastAntCatID.IsEmpty()) LastAntCatID=_T("1");
							SQL1.Format("SELECT %s,'%s','%s',%s,'%s',%lf,%lf,%s,%s,'C','DEFAULT',NULL", LastAntCatID,
								Values[24], _T("N"),
								(Values[27].IsEmpty()?"NULL":Values[27]),Values[28],360.0,360.0,
								(Values[31].IsEmpty()?"NULL":Values[31]),(Values[32].IsEmpty()?"NULL":Values[32]));
							SQL1="INSERT INTO AntCat (AntCatID, Pol, AntDir, gain, gaintype, beamwidthH, beamwidthV, freqfrom, freqto,ClassOfAnt,AntName,MaxEffHght) "+SQL1;
							DB2.ExecuteSQL(SQL1);
							for(int PattItem=0;PattItem<360;PattItem++)
							{
								SQL1.Format("SELECT %s, %d, 'H', 0.0 ", LastAntCatID, PattItem);
								SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
								DB2.ExecuteSQL(SQL1);
								SQL1.Format("SELECT %s, %d, 'V', 0.0 ", LastAntCatID, PattItem);
								SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
								DB2.ExecuteSQL(SQL1);
							}
				//Antenna
							rs2.Open(CRecordset::snapshot, "select max(AntID)+1 from Antenna");
							rs2.GetFieldValue((short)0,LastAntID2);
							rs2.Close();
							if(LastAntID2.IsEmpty()) LastAntID2=_T("1");
							SQL1.Format("SELECT %s, %s,%s,%s,0,0", LastAntID2, LastAntCatID, LastEqID, Values[23]);
							SQL1="INSERT INTO Antenna (AntID, AntCatID, EqID, AntHeightAGL, azimuth, elevation) "+SQL1;
							DB2.ExecuteSQL(SQL1);
				//Frequency
							rs2.Open(CRecordset::snapshot, "select max(FreqID)+1 from Frequency");
							rs2.GetFieldValue((short)0,LastFreqID2);
							rs2.Close();
							if(LastFreqID2.IsEmpty()) LastFreqID2=_T("1");
							SQL1.Format("SELECT %s, %s, 0.0, 'CP','%s',%s,'%s',%s", LastFreqID2, LastEqID, 
								Values[20], (Values[21].IsEmpty()?"NULL":Values[21]),BandWidthCode(atof(Values[21]))+Values[20],
								(Values[33].IsEmpty()?"NULL":Values[33]));
							SQL1="INSERT INTO Frequency ( FreqID, EqID, Frequency, natserv, emissioncl, bandwidth, EmDes, RespFreq ) "+SQL1;
							DB2.ExecuteSQL(SQL1);
							SQL2.Format(_T("Country, RecLat, RecLon) select %s, 1, 1, 'POINT', %s, %s, %s, %s, '%s', %s, %s"),
								RecID, LastFreqID, LastFreqID2, LastAntID, LastAntID2, Country, Lat, Lon);
							SQL2=_T("Insert into link (ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID,")+SQL2;
							DB2.ExecuteSQL(SQL2);
						}
						rs4.Close();
					}
					if(GeoType==_T("MULTIPOINT"))
					{
						CString Lon[6], Lat[6];
						int i=0;
						SQL2.Format(_T("select * from fxm_geo_pt where geo_key=%s order by geo_pt"),GeoKey);
						rs4.Open(CRecordset::snapshot, SQL2);
						while(!rs4.IsEOF())
						{
							rs4.GetFieldValue(_T("long_dec"),Lon[i]);
							rs4.GetFieldValue(_T("lat_dec"),Lat[i++]);
							rs4.MoveNext();
						}
						rs4.Close();
						SQL2.Format(_T("select %s, 1, 1, 'MULTIPOINT', %s, -1, %s, -1, '%s', %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s "),
							RecID, LastFreqID, LastAntID, Country, Lat[0]==_T("")?_T("NULL"):Lat[0], Lon[0]==_T("")?_T("NULL"):Lon[0], 
							Lat[1]==_T("")?_T("NULL"):Lat[1], Lon[1]==_T("")?_T("NULL"):Lon[1], 
							Lat[2]==_T("")?_T("NULL"):Lat[2], Lon[2]==_T("")?_T("NULL"):Lon[2], 
							Lat[3]==_T("")?_T("NULL"):Lat[3], Lon[3]==_T("")?_T("NULL"):Lon[3], 
							Lat[4]==_T("")?_T("NULL"):Lat[4], Lon[4]==_T("")?_T("NULL"):Lon[4], 
							Lat[5]==_T("")?_T("NULL"):Lat[5], Lon[5]==_T("")?_T("NULL"):Lon[5]);
						SQL2=_T("Insert into link (ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID,Country, lat1, lon1, lat2, lon2, lat3, lon3, lat4, lon4, lat5, lon5, lat6, lon6)")+SQL2;
						DB2.ExecuteSQL(SQL2);
					}
					if(GeoType==_T("CIRCLE"))
					{
						CString Lon, Lat;
						SQL2.Format(_T("select * from fxm_geo_pt where geo_key=%s order by geo_pt"),GeoKey);
						rs4.Open(CRecordset::snapshot, SQL2);
						if(!rs4.IsEOF())
						{
							rs4.GetFieldValue(_T("long_dec"),Lon);
							rs4.GetFieldValue(_T("lat_dec"),Lat);
							SQL2.Format(_T("Country, RecLat, RecLon, Radius) select %s, 1, 1, 'CIRCLE', %s, -1, %s, -1, '%s', %s, %s, %s"),
								RecID, LastFreqID, LastAntID, Country, Lat, Lon, Radius);
							SQL2=_T("Insert into link (ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID,")+SQL2;
							DB2.ExecuteSQL(SQL2);
						}
						rs4.Close();
					}
					if(GeoType==_T("ZONE"))
					{
						SQL2.Format(_T("Country, zone) select %s, 1, 1, 'ZONE', %s, -1, %s, -1, '%s', '%s'"),
							RecID, LastFreqID, LastAntID, Country, Zone);
						SQL2=_T("Insert into link (ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID,")+SQL2;
						DB2.ExecuteSQL(SQL2);
					}
					rs3.MoveNext();
				}
			}
			rs3.Close();
/////////////////////////////////////////////

			rs.MoveNext();
			Recs++;
			if((Recs%10)==0)
				m_ImportProgress.StepIt();
		}
		rs.Close();
/////////////////////////Typical///////////////////////
			SQL2="SELECT fxm_terra.terrakey,adm_ref_id, assgn_id, ctry, site_name, '' AS lat_dec, '' AS long_dec, '' AS site_alt, stn_cls, '' AS Expr1, ";
			SQL2+="radius,region,stn_id, stn_type, prov, pwr_xyz,pwr_ant, pwr_dbw, pwr_eiv,'', emi_cls, bdwdth, energy_dsp, hgt_agl, polar, ";
			SQL2+="ant_dir, azm_max_e, gain_max, gain_type, bmwdth, elev, freq_min, freq_max, freq_assgn, traffic, freq_carr, freq_dev, nat_srv, ";
			SQL2+=" notice_typ ";
			SQL1=" FROM fxm_terra, fxm_nat_serv, fxm_ant, fxm_geo, fxm_region WHERE ";
			SQL1+="fxm_terra.terrakey=fxm_nat_serv.terrakey and fxm_terra.terrakey=fxm_ant.terrakey and fxm_terra.geo_key=fxm_geo.geo_key and ";
			SQL1+="fxm_terra.geo_key=fxm_region.geo_key and stn_type='TP' ";
		if(m_AdmSel.GetCount()) 
			SQL1+=" and adm in (" + GetAdmList() + ")";
		if(m_FreqCondSel.GetCount())
			SQL1+=" and (" + GetFreqCond() + ")";
		if(m_ClassSel.GetCount())
			SQL1+=" and stn_cls in (" + GetClassList() + ")";
		if(m_FragSel.GetCount())
			SQL1+=" and fragment in (" + GetFragList() + ")";
		if(m_IDSel.GetCount())
			SQL1+=" and fxm_terra.assgn_id in (" + GetIDList() + ")";
//		CString Values[50],Tot;
//		long Recs=0,Total;
		rs.Open(CRecordset::snapshot, "select count(fxm_terra.terrakey) "+SQL1);
		rs.GetFieldValue((short)0,Tot);
		Total=atol((LPCTSTR)Tot);
		rs.Close();
		rs.Open(CRecordset::snapshot, SQL2+SQL1);
		m_ImportProgress.SetRange32(0,Total);
		m_ImportProgress.SetStep(10);
		//Ans=IDNO;
		if(Total>0)
		{
			CString Message;
			RecFound=true;
			Message.Format(_Z("%ld record(s) found for typical stations. Continue?"),Total);
			Ans=AfxMessageBox(Message,MB_YESNO);
		}
		while(Total>0 && Ans==IDYES)
		{
			CString LastStID, LastEqID, LastEqCatID, LastAntID, LastAntCatID, LastFreqID;
			CString SysType[2];
			if(rs.IsEOF()) break;
			rs2.m_pDatabase=&DB2;
			for(int i=0;i<15;i++)
			{
				rs.GetFieldValue(i,Values[i]);
				Values[i].TrimRight();
			}
			rs.GetFieldValue(38,Values[38]);
			if(Values[14].Left(11)==_T("GE06-Origin"))
				Values[14]=_T("Geneva 2006L");
			if(!Values[8].CompareNoCase(_T("FX")) || !Values[8].CompareNoCase(_T("FB")))
			{
	// Station
				rs2.Open(CRecordset::snapshot, "select max(StID)+1 from Station");
				rs2.GetFieldValue((short)0,LastStID);
				rs2.Close();
				if(LastStID.IsEmpty()) LastStID=_T("1");
				//Values[3].TrimRight(" ");
				//Values[1].TrimRight(" ");
				//Values[4].TrimRight(" ");
				//Values[9].TrimRight(" ");
				//Values[2].TrimRight(" ");
				//Values[14].TrimRight(" ");
				//Values[12].TrimRight(" ");
				//Values[8].TrimRight(" ");
				RemoveQuote(&Values[4]);

				SQL2.Format(_T(" fxm_terra, fxm_geo where fxm_terra.geo_key=fxm_geo.geo_key and terrakey=%s"),Values[0]);
				SQL2=_T("select fxm_geo.geo_key, geo_type, ctry, site_name, zone_id, radius from")+SQL2;
				rs3.Open(CRecordset::snapshot, SQL2);
				CString GeoType, RecID, Country, Zone, GeoKey, Radius, SiteName;
				CString Lon, Lat;
				if(!rs3.IsEOF())
				{
					rs3.GetFieldValue(_T("geo_key"),GeoKey);
					rs3.GetFieldValue(_T("geo_type"),GeoType);
					rs3.GetFieldValue(_T("ctry"),Country);
					rs3.GetFieldValue(_T("zone_id"),Zone);
					rs3.GetFieldValue(_T("radius"),Radius);
					rs3.GetFieldValue(_T("site_name"),SiteName);
					GeoType.TrimRight();
					Country.TrimRight();
					Zone.TrimRight();
					if(GeoType==_T("CIRCLE"))
					{
						CRecordset rs4;
						rs4.m_pDatabase=rs3.m_pDatabase;
						SQL2.Format(_T("select * from fxm_geo_pt where geo_key=%s order by geo_pt"),GeoKey);
						rs4.Open(CRecordset::snapshot, SQL2);
						if(!rs4.IsEOF())
						{
							rs4.GetFieldValue(_T("long_dec"),Lon);
							rs4.GetFieldValue(_T("lat_dec"),Lat);
						}
						rs4.Close();
					}
				}
				rs3.Close();
				SQL1.Format("SELECT %s, -1, '%s','%s','%s','%s','%s','%s','%s',%s,%s,'%s', 'Typical','%s', '%s', %s, %s, '%s' ", LastStID, Values[0],
					Values[1], Values[2], Values[3], _T("TP")+Values[2], Values[8],Values[9],
					(Values[10].IsEmpty()?"NULL":Values[10]), (Values[11].IsEmpty()?"NULL":Values[11]), Values[12], 
					(Values[14].Mid(3,2)==_T("11")?_T("Article 11"):Values[14]),
					Values[38], (Lat.IsEmpty()?"NULL":Lat), (Lon.IsEmpty()?"NULL":Lon), Zone);
				SQL1=",radius, ituregion, siteID, sttype, provision, NoticeType, GeoLat, GeoLon, AreaOfTrans) "+SQL1;
				SQL1="INSERT INTO Station (StID, LicID, TerraKey, admrefID, Assgn_ID, Country, SiteName, ClassStation, Callsign "+SQL1;
				DB2.ExecuteSQL(SQL1);
	//EqCat
				rs2.Open(CRecordset::snapshot, "select max(EqCatID)+1 from EqCat");
				rs2.GetFieldValue((short)0,LastEqCatID);
				rs2.Close();
				if(LastEqCatID.IsEmpty()) LastEqCatID=_T("1");
				SQL1.Format(_T("SELECT system_type from fxm_system_type where terrakey=%s"), Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				i=0;
				while(!rs3.IsEOF() && i<2)
				{
					rs3.GetFieldValue((short)0,SysType[i++]);
					SysType[i-1].TrimRight();
					rs3.MoveNext();
				}
				rs3.Close();
				for(i=15;i<23;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				//Values[15].TrimRight(" ");
				//Values[18].TrimRight(" ");
				//Values[19].TrimRight(" ");
				//Values[20].TrimRight(" ");
				SQL1.Format("SELECT %s, '%s','%s','%s',%s, '%s', '%s'", LastEqCatID,
					Values[15],	Values[18], Values[19],(Values[22].IsEmpty()?"NULL":Values[22]),
					SysType[0],SysType[1]);
				SQL2="INSERT INTO EqCat (EqCatID, powertype, radpowertype, classop, endisp, SystemType1, SystemType2) ";
				SQL1=SQL2+SQL1;
				DB2.ExecuteSQL(SQL1);

				
	//Equipment
				rs2.Open(CRecordset::snapshot, "select max(EqID)+1 from Equipment");
				rs2.GetFieldValue((short)0,LastEqID);
				rs2.Close();
				if(LastEqID.IsEmpty()) LastEqID=_T("1");
				double pwr1=pow(10.,atof(Values[16])/10),pwr2=pow(10.,atof(Values[17])/10);
				SQL1.Format("SELECT %s, %s,%s,%lf,%lf", LastEqID, LastEqCatID, LastStID
					, pwr1, pwr2);
				SQL1="INSERT INTO Equipment (EqID, EqCatID, StID, pwr2ant, radpwr) "+SQL1;
				DB2.ExecuteSQL(SQL1);
	//AntCat				
				rs2.Open(CRecordset::snapshot, "select max(AntCatID)+1 from AntCat");
				rs2.GetFieldValue((short)0,LastAntCatID);
				rs2.Close();
				if(LastAntCatID.IsEmpty()) LastAntCatID=_T("1");
				for(i=23;i<33;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				if(Values[24].IsEmpty())
					Values[24]=_T("M");
				//Values[24].TrimRight(" ");
				//Values[25].TrimRight(" ");
				//Values[28].TrimRight(" ");
				Values[25]=Values[25].Left(1);
				if(Values[25].Left(1)==_T("N"))
				{
					Values[25]=_T("N");
					Values[29]=_T("360.0");
				}
				else
				{
					Values[25]=_T("D");
					if(Values[29].IsEmpty() || atof(Values[29])>359.0)
						Values[29]=_T("359.0");
				}
				SQL1.Format("SELECT %s,'%s','%s',%s,'%s',%s,%s,%s,%s,'C','%09ld'", LastAntCatID,
					Values[24], Values[25],
					(Values[27].IsEmpty()?"NULL":Values[27]),Values[28],(Values[29].IsEmpty()?"NULL":Values[29]),
					(Values[29].IsEmpty()?"NULL":Values[29]),
					(Values[31].IsEmpty()?"NULL":Values[31]),(Values[32].IsEmpty()?"NULL":Values[32]),atol(LastAntCatID));
				SQL1="INSERT INTO AntCat (AntCatID, Pol, AntDir, gain, gaintype, beamwidthH, beamwidthV, freqfrom, freqto,ClassOfAnt,AntName) "+SQL1;
				DB2.ExecuteSQL(SQL1);
	//Antenna
				rs2.Open(CRecordset::snapshot, "select max(AntID)+1 from Antenna");
				rs2.GetFieldValue((short)0,LastAntID);
				rs2.Close();
				if(LastAntID.IsEmpty()) LastAntID=_T("1");
				SQL1.Format("SELECT %s, %s,%s, %s,%s,%s", LastAntID, LastAntCatID, LastEqID,(Values[23].IsEmpty()?"37.5":Values[23])
					, (Values[26].IsEmpty()?"0":Values[26]),(Values[30].IsEmpty()?"NULL":Values[30]));
				SQL1="INSERT INTO Antenna (AntID, AntCatID, EqID, AntHeightAGL, azimuth, elevation) "+SQL1;
				DB2.ExecuteSQL(SQL1);

	//Ant pattern
//////////////////////////////////////////////////////////////////////////////
				SQL1.Format("SELECT %s, azm, polar, attn from fxm_ant_diag where terrakey=%s and Polar='H'", LastAntCatID, Values[0]);
				double AngV[361]={0.0},PattV[361]={0.0},AngH[361]={0.0},PattH[361]={0.0};
				rs3.Open(CRecordset::snapshot,SQL1);
				if(rs3.GetRecordCount()>0)
				{
					int i=0;
					while(!rs3.IsEOF())
					{
						double azm, attn;
						CDBVariant FVal;
						rs3.GetFieldValue(_T("azm"),FVal);
						AngH[i]=azm=FVal.m_dblVal;
						rs3.GetFieldValue(_T("attn"),FVal);
						PattH[i]=attn=FVal.m_dblVal;
						rs3.MoveNext();
						i++;
					}
					double PatternTmp[361],AngleTmp[361];
					//Ang[i] = 360;
					//Patt[i] = Patt[0];

					for (int j=0;j<360;j++)
					{
						AngleTmp[j]=j;
						PatternTmp[j] = Interp2(AngH,PattH,j,i) ;
					}
					//PatternTmp[360]=PatternTmp[0];
					//AngleTmp[360]=360.;
					for(i=0;i<360;i++)
					{
						AngH[i]=AngleTmp[i];
						PattH[i]=PatternTmp[i];
					}
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						SQL1.Format("SELECT %s, %d, 'H', %lf ", LastAntCatID, PattItem, PattH[PattItem]);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
					}		
				}
				else
				{
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						AngH[PattItem]=PattItem;
						PattH[PattItem]=0.0;
						SQL1.Format("SELECT %s, %d, 'H', 0.0 ", LastAntCatID, PattItem);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
					}
				}
				rs3.Close();
				SQL1.Format("SELECT %s, azm, polar, attn from fxm_ant_diag where terrakey=%s and Polar='V'", LastAntCatID, Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				if(rs3.GetRecordCount()>0)
				{
					int i=0;
					while(!rs3.IsEOF())
					{
						double azm, attn;
						CDBVariant FVal;
						rs3.GetFieldValue(_T("azm"),FVal);
						AngV[i]=azm=FVal.m_dblVal;
						rs3.GetFieldValue(_T("attn"),FVal);
						PattV[i]=attn=FVal.m_dblVal;
						rs3.MoveNext();
						i++;
					}
					double PatternTmp[361],AngleTmp[361];
					//Ang[i] = 360;
					//Patt[i] = Patt[0];

					for (int j=0;j<360;j++)
					{
						AngleTmp[j]=j;
						PatternTmp[j] = Interp2(AngV,PattV,j,i) ;
					}
					//PatternTmp[360]=PatternTmp[0];
					//AngleTmp[360]=360.;
					for(i=0;i<360;i++)
					{
						AngV[i]=AngleTmp[i];
						PattV[i]=PatternTmp[i];
					}
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						SQL1.Format("SELECT %s, %d, 'V', %lf ", LastAntCatID, PattItem, PattV[PattItem]);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
					}
				}
				else
				{
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						AngV[PattItem]=PattItem;
						PattV[PattItem]=0.0;
						SQL1.Format("SELECT %s, %d, 'V', 0.0 ", LastAntCatID, PattItem);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB2.ExecuteSQL(SQL1);
					}
				}
				rs3.Close();
				AntennaSaveTxt(LastAntCatID, 0.0, atof(Values[29]), atof(Values[29]), atof(Values[31]),
					atof(Values[32]), Values[24], PattV, PattH,atof(Values[26]));

	//Ant height
				SQL1.Format("SELECT azm, eff_hgt from fxm_ant_hgt where terrakey=%s ", Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				while(!rs3.IsEOF())
				{
					CString Azm, EffHgt;
					rs3.GetFieldValue((int)0,Azm);
					rs3.GetFieldValue((int)1,EffHgt);
					SQL1.Format(_T("Select %s,%s,%s "), LastAntID, Azm, EffHgt);
					SQL1="INSERT INTO AntHgt ( AntID, azm, EffHgt ) "+SQL1;
					DB2.ExecuteSQL(SQL1);
					rs3.MoveNext();
				}
				rs3.Close();
///////////////////////////////////////////////////////////////////				
				
	//Frequency
				rs2.Open(CRecordset::snapshot, "select max(FreqID)+1 from Frequency");
				rs2.GetFieldValue((short)0,LastFreqID);
				rs2.Close();
				if(LastFreqID.IsEmpty()) LastFreqID=_T("1");
				for(i=33;i<38;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				//Values[37].TrimRight(" ");
				Values[33].Format(_T("%lf"),atof(Values[33])*1000000.);
//				CString RecsSQL,FValue;
				double RXFreq=0;
				SQL1.Format("SELECT %s, %s, %s, %s, %s, %s, '%s','%s',%s,'%s',%lf", LastFreqID, LastEqID, (Values[33].IsEmpty()?"NULL":Values[33]),
					(Values[34].IsEmpty()?"NULL":Values[34]),(Values[35].IsEmpty()?"NULL":Values[35]),
					(Values[36].IsEmpty()?"NULL":Values[36]),Values[37], Values[20], (Values[21].IsEmpty()?"NULL":Values[21]),BandWidthCode(atof(Values[21]))+Values[20],
					RXFreq);
				SQL1="INSERT INTO Frequency ( FreqID, EqID, Frequency, traffic, reffreq, freqdev, natserv, emissioncl, bandwidth, EmDes, RespFreq ) "+SQL1;
				DB2.ExecuteSQL(SQL1);
			}
			
			rs3.Close();
/////////////////////////////////////////////

			rs.MoveNext();
			Recs++;
			if((Recs%10)==0)
				m_ImportProgress.StepIt();
		}
		rs.Close();

/////////////////////////Typical///////////////////////

		DB1.Close();
		DB2.Close();
		CCmdTarget::EndWaitCursor();
		if(!RecFound)
			MessageBox(_Z("The query returned no records!"),"IFIC Import", MB_ICONEXCLAMATION|MB_OK);
		else
		{
			if( Ans==IDYES ) CDialog::OnOK();
		}
	}//end if
	else if(m_FMTV.GetCheck())
	{
		if(!m_Digital.GetCheck())
		{
			CCmdTarget::BeginWaitCursor();
			SQL2+="SELECT terrakey, assgn_id, ctry, site_name, lat_dec, long_dec, site_alt, stn_cls, eu_ref, ";
			SQL2+="hgt_agl, polar, ant_dir, eff_hgtmax, erp_dbw, erp_h_dbw, erp_v_dbw, emi_cls, tran_sys, freq_stabl, ";
			SQL2+="oset_v_12, oset_v_khz, oset_s_12, freq_vcarr, freq_scarr, pwr_ratio, tv_chan, color, freq_assgn, fragment, ";
			SQL2+="call_sign, region, oset_s_khz, bdwdth, azm_max_e, freq_min, freq_max, notice_typ, adm_ref_id, plan_entry, assgn_code, ";
			SQL2+="erp_beam_tilt_dbw, beam_tilt_angle, rx_mode, ref_plan_cfg, sfn_id, assoc_allot_id, assoc_allot_sfn_id, spect_mask ";
			SQL1+="FROM fmtv_terra WHERE adm is not null";
			if(m_AdmSel.GetCount()) 
				SQL1+=" and adm in (" + GetAdmList() + ")";
			if(m_FreqCondSel.GetCount())
				SQL1+=" and (" + GetFreqCond() + ")";
			if(m_ClassSel.GetCount())
				SQL1+=" and stn_cls in (" + GetClassList() + ")";
			if(m_FragSel.GetCount())
				SQL1+=" and fragment in (" + GetFragList() + ")";
			if(m_IDSel.GetCount())
				SQL1+=" and fmtv_terra.assgn_id in (" + GetIDList() + ")";
/*			FILE *fp=fopen("c:\\test.txt","wt");
			fprintf(fp,SQL2+SQL1);
			fclose(fp);*/
			CString Values[50],Tot;
			long Recs=0,Total;
			CDatabase DB1,DB;
//			if(m_BRIFIC.Left(4)=="ODBC")
				DB1.Open(m_BRIFIC,false,false,_T("ODBC;"),false);
//			else
//				DB1.Open(m_BRIFIC);
			DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
			CRecordset rs,rs2,rs3;
			rs3.m_pDatabase=&DB1;
			rs.m_pDatabase=&DB1;
			rs.Open(CRecordset::snapshot, "select count(fmtv_terra.terrakey) "+SQL1);
			rs.GetFieldValue((short)0,Tot);
			Total=atol((LPCTSTR)Tot);
			rs.Close();
			rs.Open(CRecordset::snapshot, SQL2+SQL1);
			m_ImportProgress.SetRange32(0,Total);
			m_ImportProgress.SetStep(10);
			int Ans=IDNO;
			if(Total>0)
			{
				CString Message;
				RecFound=true;
				Message.Format(_Z("%ld record(s) found. Continue?"),Total);
				Ans=AfxMessageBox(Message,MB_YESNO);
			}
			while(Total>0 && Ans==IDYES)
			{
				CString LastStID, LastEqID, LastEqCatID, LastAntID, LastAntCatID, LastFreqID;
				if(rs.IsEOF()) break;
				for(int i=0;i<48;i++)
				{
					rs.GetFieldValue(i,Values[i]);
					Values[i].TrimRight();
				}
				rs2.m_pDatabase=&DB;
	// BCStation
				rs2.Open(CRecordset::snapshot, "select max(StID)+1 from BCStation");
				rs2.GetFieldValue((short)0,LastStID);
				rs2.Close();
				if(LastStID.IsEmpty()) LastStID=_T("1");
	//			for(int i=0;i<9;i++)
	//				rs.GetFieldValue(i,Values[i]);
	//			rs.GetFieldValue(28, Values[28]);
				RemoveQuote(&Values[3]);
				Values[38].TrimRight();
				Values[39].TrimRight();
				Values[44].TrimRight();
				Values[45].TrimRight();
				Values[46].TrimRight();
				SQL2.Format("SELECT %s, -1, %s,'%s','%s','%s',%s,%s,%s,'%s','%s',%s,provision,'Fixed','%s','%s', %s, '%s', '%s', '%s', '%s' from provisions where provisions.fragment='%s' ", LastStID, 
					Values[0], Values[1], Values[2], Values[3], (Values[4].IsEmpty()?"NULL":Values[4]), (Values[5].IsEmpty()?"NULL":Values[5]), 
					(Values[6].IsEmpty()?"NULL":Values[6]), Values[7],Values[29],(Values[30].IsEmpty()?"NULL":Values[30]),Values[36],Values[37],
					(Values[38].IsEmpty()?"NULL":Values[38]), Values[39], Values[44], Values[45], Values[46],Values[28]);
				SQL1="INSERT INTO BCStation (StID, LicID, TerraKey, Assgn_ID, Country, SiteName, GeoLat, GeoLon, HeightASL, ClassStation, callsign,ituregion, ";
				SQL1=SQL1 + "Provision, StType, NoticeType, AdmRefID, PlanEntry, AssignCode, sfnid, assocallotid, assocallotsfn) "+SQL2;
				DB.ExecuteSQL(SQL1);
	//AntCat				
				rs2.Open(CRecordset::snapshot, _T("select max(AntCatID)+1 from AntCat"));
				rs2.GetFieldValue((short)0,LastAntCatID);
				rs2.Close();
				if(LastAntCatID.IsEmpty()) LastAntCatID=_T("1");
	//			for(i=9;i<13;i++)
	//				rs.GetFieldValue(i,Values[i]);
				if(Values[10].IsEmpty())
					Values[10]=_T("M");
				CString Polar=Values[10];
				float BMwdth;
				if(Values[11].Left(1)==_T("N"))
				{
					Values[11]=_T("N");
					BMwdth=360.0;
				}
				else
				{
					Values[11]=_T("D");
					BMwdth=359.0;
				}
	///			if(!Values[10].Left(1).CompareNoCase(_T("M"))) Polar=_T("V");
				SQL1.Format("SELECT %s,'%s','%s',%s,'C','%09ld', %lf, %lf,0,'I',%f,%f ", LastAntCatID,
					Polar, Values[11],/*(Values[11]==_T("ND")?_T("N"):Values[11]),*/ (Values[12].IsEmpty()?"NULL":Values[12]),
					atol(LastAntCatID), atof(Values[34]), atof(Values[35]), BMwdth, BMwdth);
				SQL1="INSERT INTO AntCat (AntCatID, Pol, AntDir, MaxEffHght,ClassOfAnt,AntName,FreqFrom,FreqTo,gain, gaintype, beamwidthH,beamwidthV) "+SQL1;
				DB.ExecuteSQL(SQL1);
	//EqCat
				rs2.Open(CRecordset::snapshot, "select max(EqCatID)+1 from EqCat");
				rs2.GetFieldValue((short)0,LastEqCatID);
				rs2.Close();
				if(LastEqCatID.IsEmpty()) LastEqCatID=_T("1");
	//			for(i=13;i<27;i++)
	//				rs.GetFieldValue(i,Values[i]);
				if(!Values[7].CompareNoCase(_T("BT")))
				{
					SQL1.Format("SELECT %s, %s,%s,%s,'%s','%s',%s,%s,%s,%s,'%s',%s,%s,'%s','%s' ", LastEqCatID,
						(Values[13].IsEmpty()?"NULL":Values[13]), (Values[14].IsEmpty()?"NULL":Values[14]), (Values[15].IsEmpty()?"NULL":Values[15]),
						 Values[17], Values[18], (Values[19].IsEmpty()?"NULL":Values[19]),(Values[20].IsEmpty()?"NULL":Values[20]), 
						(Values[21].IsEmpty()?"NULL":Values[21]),
						(Values[24].IsEmpty()?"NULL":Values[24]), Values[26], (Values[8].IsEmpty()?"NULL":Values[8]),
						(Values[31].IsEmpty()?"NULL":Values[31]), Values[43], Values[42]);
					SQL2="INSERT INTO EqCat (EqCatID, ERP_dbw, ERP_h_dbw, ERP_v_dbw, TVSys, ";
					SQL2=SQL2+ "FreqStabl, OsetV12, OsetV, OsetS12, PwrRatio,  ColorSys, EU_Ref,OsetS, RefPlanCfg, RXMode ) ";
				}
				else
				{
					SQL1.Format("SELECT %s, %s,%s,%s,%s,'%s',%s,%s,%s,%s,'%s',%s,%s,'%s','%s' ", LastEqCatID,
						(Values[13].IsEmpty()?"NULL":Values[13]), (Values[14].IsEmpty()?"NULL":Values[14]), (Values[15].IsEmpty()?"NULL":Values[15]),
						(Values[17].IsEmpty()?"NULL":Values[17]), Values[18], (Values[19].IsEmpty()?"NULL":Values[19]),(Values[20].IsEmpty()?"NULL":Values[20]), 
						(Values[21].IsEmpty()?"NULL":Values[21]),
						(Values[24].IsEmpty()?"NULL":Values[24]), Values[26], (Values[8].IsEmpty()?"NULL":Values[8]),
						(Values[31].IsEmpty()?"NULL":Values[31]), Values[43], Values[42]);
					SQL2="INSERT INTO EqCat (EqCatID, ERP_dbw, ERP_h_dbw, ERP_v_dbw, TranSys, ";
					SQL2=SQL2+ "FreqStabl, OsetV12, OsetV, OsetS12, PwrRatio,  ColorSys, EU_Ref,OsetS, RefPlanCfg, RXMode) ";
				}
				SQL1=SQL2+SQL1;
				DB.ExecuteSQL(SQL1);
	//Equipment
				rs2.Open(CRecordset::snapshot, "select max(EqID)+1 from Equipment");
				rs2.GetFieldValue((short)0,LastEqID);
				rs2.Close();
				if(LastEqID.IsEmpty()) LastEqID=_T("1");
				double pwr2=pow(10.,atof(Values[13])/10);
//				if(Polar==_T("H"))
//					pwr1=pow(10.,);
				SQL1.Format("SELECT %s, %s,%s,%lf,%lf", LastEqID, LastEqCatID, LastStID,pwr2,pwr2);
				SQL1="INSERT INTO Equipment (EqID, EqCatID, BCID,RadPwr,Pwr2Ant) "+SQL1;
				DB.ExecuteSQL(SQL1);
	//Antenna
				rs2.Open(CRecordset::snapshot, "select max(AntID)+1 from Antenna");
				rs2.GetFieldValue((short)0,LastAntID);
				rs2.Close();
				if(LastAntID.IsEmpty()) LastAntID=_T("1");
				SQL1.Format("SELECT %s, %s,%s, %s,%s", LastAntID, LastAntCatID, LastEqID,(Values[9].IsEmpty()?"37.5":Values[9]),
					(Values[33].IsEmpty()?"0":Values[33]));
				SQL1="INSERT INTO Antenna (AntID, AntCatID, EqID, AntHeightAGL,azimuth) "+SQL1;
				DB.ExecuteSQL(SQL1);
	//Ant pattern

				SQL1.Format("SELECT %s, azm, polar, attn from fmtv_ant_diag where terrakey=%s and Polar='H'", LastAntCatID, Values[0]);
				double AngV[361]={0.0},PattV[361]={0.0},AngH[361]={0.0},PattH[361]={0.0};
				rs3.Open(CRecordset::snapshot,SQL1);
				if(rs3.GetRecordCount()>0)
				{
					int i=0;
					while(!rs3.IsEOF())
					{
						double azm, attn;
						CDBVariant FVal;
						rs3.GetFieldValue(_T("azm"),FVal);
						AngH[i]=azm=FVal.m_dblVal;
						rs3.GetFieldValue(_T("attn"),FVal);
						PattH[i]=attn=FVal.m_dblVal;
						rs3.MoveNext();
						i++;
					}
					double PatternTmp[361],AngleTmp[361];
					//Ang[i] = 360;
					//Patt[i] = Patt[0];

					for (int j=0;j<360;j++)
					{
						AngleTmp[j]=j;
						PatternTmp[j] = Interp2(AngH,PattH,j,i) ;
					}
					//PatternTmp[360]=PatternTmp[0];
					//AngleTmp[360]=360.;
					for(i=0;i<360;i++)
					{
						AngH[i]=AngleTmp[i];
						PattH[i]=PatternTmp[i];
					}
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						SQL1.Format("SELECT %s, %d, 'H', %lf ", LastAntCatID, PattItem, PattH[PattItem]);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB.ExecuteSQL(SQL1);
					}		
				}
				else
				{
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						AngH[PattItem]=PattItem;
						PattH[PattItem]=0.0;
						SQL1.Format("SELECT %s, %d, 'H', 0.0 ", LastAntCatID, PattItem);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB.ExecuteSQL(SQL1);
					}
				}
				rs3.Close();
				SQL1.Format("SELECT %s, azm, polar, attn from fmtv_ant_diag where terrakey=%s and Polar='V'", LastAntCatID, Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				if(rs3.GetRecordCount()>0)
				{
					int i=0;
					while(!rs3.IsEOF())
					{
						double azm, attn;
						CDBVariant FVal;
						rs3.GetFieldValue(_T("azm"),FVal);
						AngV[i]=azm=FVal.m_dblVal;
						rs3.GetFieldValue(_T("attn"),FVal);
						PattV[i]=attn=FVal.m_dblVal;
						rs3.MoveNext();
						i++;
					}
					double PatternTmp[361],AngleTmp[361];
					//Ang[i] = 360;
					//Patt[i] = Patt[0];

					for (int j=0;j<360;j++)
					{
						AngleTmp[j]=j;
						PatternTmp[j] = Interp2(AngV,PattV,j,i) ;
					}
					//PatternTmp[360]=PatternTmp[0];
					//AngleTmp[360]=360.;
					for(i=0;i<360;i++)
					{
						AngV[i]=AngleTmp[i];
						PattV[i]=PatternTmp[i];
					}
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						SQL1.Format("SELECT %s, %d, 'V', %lf ", LastAntCatID, PattItem, PattV[PattItem]);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB.ExecuteSQL(SQL1);
					}
				}
				else
				{
					for(int PattItem=0;PattItem<360;PattItem++)
					{
						AngV[PattItem]=PattItem;
						PattV[PattItem]=0.0;
						SQL1.Format("SELECT %s, %d, 'V', 0.0 ", LastAntCatID, PattItem);
						SQL1="INSERT INTO AntDiag ( AntID, azm, polar, attn ) "+SQL1;
						DB.ExecuteSQL(SQL1);
					}
				}
				rs3.Close();
				AntennaSaveTxt(LastAntCatID, 0.0, 360.0, 360.0, atof(Values[34]),
					atof(Values[35]), Polar, PattV, PattH,atof(Values[33]));

	//Ant height
				SQL1.Format("SELECT azm, eff_hgt from fmtv_ant_hgt where terrakey=%s ", Values[0]);
				rs3.Open(CRecordset::snapshot,SQL1);
				while(!rs3.IsEOF())
				{
					CString Azm, EffHgt;
					rs3.GetFieldValue((int)0,Azm);
					rs3.GetFieldValue((int)1,EffHgt);
					SQL1.Format(_T("Select %s,%s,%s "), LastAntID, Azm, EffHgt);
					SQL1="INSERT INTO AntHgt ( AntID, azm, EffHgt ) "+SQL1;
					DB.ExecuteSQL(SQL1);
					rs3.MoveNext();
				}
				rs3.Close();
	//Frequency
				rs2.Open(CRecordset::snapshot, "select max(FreqID)+1 from Frequency");
				rs2.GetFieldValue((short)0,LastFreqID);
				rs2.Close();
				if(LastFreqID.IsEmpty()) LastFreqID=_T("1");
	//			rs.GetFieldValue(27,Values[27]);
				Values[27].Format(_T("%lf"),atof(Values[27])*1000000.);
				SQL1.Format("SELECT %s, %s, %s,'%s',%s,%s,'%s',%s,'%s','%s' ", LastFreqID, LastEqID, (Values[27].IsEmpty()?"NULL":Values[27]),
					Values[16], (Values[22].IsEmpty()?"NULL":Values[22]), (Values[23].IsEmpty()?"NULL":Values[23]), (Values[25].IsEmpty()?"NULL":Values[25]),
					(Values[32].IsEmpty()?"NULL":Values[32]),BandWidthCode(atof(Values[32]))+Values[16], Values[47]);
				SQL1="INSERT INTO Frequency ( FreqID, EqID, Frequency, EmissionCl, FreqVCarr, FreqSCarr, TVChan,BandWidth,EmDes, SpectMask ) "+SQL1;
				DB.ExecuteSQL(SQL1);

				rs.MoveNext();
				Recs++;
				if((Recs%10)==0)
					m_ImportProgress.StepIt();
			}
			rs.Close();
			DB.Close();
			DB1.Close();
			CCmdTarget::EndWaitCursor();
			if(!RecFound)
				MessageBox(_Z("The query returned no records!"),"IFIC Import", MB_ICONEXCLAMATION|MB_OK);
			else
			{
				if( Ans==IDYES ) CDialog::OnOK();
			}
		}
		else     //   Allotments
		{
			CCmdTarget::BeginWaitCursor();
			SQL2+="SELECT terrakey, assgn_id, ctry, stn_cls, polar, tv_chan, freq_assgn, fragment, ";
			SQL2+="region, bdwdth, freq_min, freq_max, plan_entry, notice_typ, ";
			SQL2+="adm_ref_id, ref_plan_cfg, sfn_id, spect_mask, adm ";
			SQL1+="FROM ge06_allot_terra WHERE adm is not null";
			if(m_AdmSel.GetCount()) 
				SQL1+=" and adm in (" + GetAdmList() + ")";
			if(m_FreqCondSel.GetCount())
				SQL1+=" and (" + GetFreqCond() + ")";
			if(m_ClassSel.GetCount())
				SQL1+=" and stn_cls in (" + GetClassList() + ")";
			if(m_FragSel.GetCount())
				SQL1+=" and fragment in (" + GetFragList() + ")";
			if(m_IDSel.GetCount())
				SQL1+=" and assgn_id in (" + GetIDList() + ")";
			CString Tot;
			COleVariant Values[50],Values2[20],TempOLE;
			long Recs=0,Total;
			CDatabase DB2;
			CDaoDatabase DB,DB1;
			CString Conn;
			char buf[200]="C:\\BR_Soft\\Terrasys\\TerRaQ\\Data\\TERRABROADCAST.MDB";
			int start, end;
/*			DB2.Open(m_BRIFIC,false,false,_T("ODBC;"),false);
			Conn=DB2.GetConnect();
			if(m_BRIFIC.Left(6)!="BRIFIC")
			{
				start=Conn.Find(_T("DBQ="))+4;
				end=Conn.Find(_T(";"),start);
				DB2.Close();
				end=Conn.ReverseFind(_T('\\'));
				Conn=Conn.Mid(start,end-start+1)+_T("TERRABROADCAST.MDB");
			}
			else
			{
				start=Conn.Find(_T("Database="))+9;
				end=Conn.Find(_T(";"),start);
				DB2.Close();
				end=Conn.ReverseFind(_T('\\'));
				Conn=Conn.Mid(start,end-start+1)+_T("TERRABROADCAST.MDB");
			}*/
		/*	FILE *fp=fopen("c:\\temp\\test.txt","rt");
			fgets(buf,200,fp);
			fclose(fp);*/
			Conn=buf;
			DB1.Open(Conn);			
			DB2.Open(m_CDBSTR,false,false,_T("ODBC;"),false);

				Conn=DB2.GetConnect();
				start=Conn.Find(_T("DBQ="))+4;
				end=Conn.Find(_T(";"),start);
				DB2.Close();
				Conn=Conn.Mid(start,end-start);
			DB.Open(Conn,false,false,_T(";PWD=hoteldrake"));
			//CRecordset rs2;
			CDaoRecordset rs4,rs,rs2,rs3;
			rs3.m_pDatabase=&DB1;
			rs.m_pDatabase=&DB1;
			rs4.m_pDatabase=&DB1;
			rs.Open(dbOpenSnapshot, _T("select count(terrakey) ")+SQL1);
			rs.GetFieldValue((short)0,TempOLE);
			Total=TempOLE.lVal;
			rs.Close();
			rs.Open(dbOpenSnapshot, SQL2+SQL1);
			m_ImportProgress.SetRange32(0,Total);
			m_ImportProgress.SetStep(10);
			int Ans=IDNO;
			if(Total>0)
			{
				CString Message;
				RecFound=true;
				Message.Format(_Z("%ld record(s) found. Continue?"),Total);
				Ans=AfxMessageBox(Message,MB_YESNO);
			}
			while(Total>0 && Ans==IDYES)
			{
				CString LastStID, LastEqID, LastEqCatID, LastAntID, LastAntCatID, LastFreqID;
				bool GE06=true;
				if(rs.IsEOF()) break;
				for(int i=0;i<19;i++)
				{
					rs.GetFieldValue(i,Values[i]);
//					Tot.Format("%s",Values[i].bstrVal);
//					Tot.TrimRight();
//					Values[i].SetString(Tot);
				}
				CString TTT;
				CString Notice,TempStr;
				Notice.Format(_T("%s"),Values[13].bstrVal);
				{
					SQL1.Format(_T("ge06_allot_terra.terrakey=%ld"), Values[0].lVal);
					SQL1=_T("ge06_sub_area.ge06_sub_area_key=ge06_allot_sub_area_xref.ge06_sub_area_key and ") + SQL1;
					SQL1=_T("where ge06_allot_terra.terrakey=ge06_allot_sub_area_xref.terrakey and ") + SQL1;
					SQL1=_T(" typ_ref_netwk from ge06_allot_terra, ge06_sub_area, ge06_allot_sub_area_xref ")+SQL1;
					SQL1=_T("select allot_name, geo_area, ")+SQL1;
					rs4.Open(dbOpenSnapshot, SQL1);
					for(i=0;i<3;i++)
						rs4.GetFieldValue(i,Values2[i]);
					rs4.Close();
					
					SQL1.Format(_T("ge06_allot_terra.terrakey=%ld"), Values[0].lVal);
					SQL1=_T("where ge06_allot_terra.terrakey=ge06_allot_sub_area_xref.terrakey and ") + SQL1;
					SQL1=_T("select count(ge06_sub_area_key) from ge06_allot_sub_area_xref, ge06_allot_terra ")+SQL1;
					rs4.Open(dbOpenSnapshot, SQL1);
					rs4.GetFieldValue((short)0,Values2[4]);
					rs4.Close();

					rs2.m_pDatabase=&DB;
	// rrc_allotments
					rs2.Open(dbOpenSnapshot, _T("select max(allotkey)+1 from rrc_allotment"));
					rs2.GetFieldValue((short)0,TempOLE);
					LastStID.Format(_T("%ld"),TempOLE.lVal);
					rs2.Close();
					if(LastStID.IsEmpty() || LastStID==_T("0")) LastStID=_T("1");
					TempOLE.SetString(LastStID,VT_BSTR);
					rs2.Open(dbOpenDynaset, _T("select * from rrc_allotment"));
					rs2.AddNew();
					rs2.SetFieldValue(_T("terrakey"),Values[0]);
					rs2.SetFieldValue(_T("allotkey"),(LPCTSTR)LastStID);
					TTT.Format("%s",Values2[0].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("allot_name"),(LPCTSTR)TTT);
					TTT.Format("%s",Values2[1].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("geo_area"),(LPCTSTR)TTT);
					rs2.SetFieldValue(_T("nb_sub_areas"),Values2[4]);
					COleVariant AllotKey=TempOLE;
					rs2.SetFieldValue(_T("LicID"),_T("-1"));
					TTT.Format("%s",Values[13].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("NoticeType"),(LPCTSTR)TTT);
					TTT.Format("%s",Values[7].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("Fragment"),(LPCTSTR)TTT);
					rs2.SetFieldValue(_T("PlanEntry"),Values[12]);
					TTT.Format("%s",Values[16].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("SfnID"),(LPCTSTR)TTT);
					TTT.Format("%s",Values[15].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("RefPlanCfg"),(LPCTSTR)TTT);
					Values[6].dblVal*=1000000.;
					rs2.SetFieldValue(_T("Frequency"),Values[6]);
					TTT.Format("%s",Values[14].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("AdmRefID"),(LPCTSTR)TTT);
					TTT.Format("%s",Values[2].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("ctry"),(LPCTSTR)TTT);
					rs2.SetFieldValue(_T("ClassStation"),Values[3]);
					CString Polar;
					Polar.Format(_T("%s"),Values[4].bstrVal);
					Polar.TrimRight();
					rs2.SetFieldValue(_T("Polar"),(LPCTSTR)Polar);
					TTT.Format("%s",Values2[2].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("TypRefNetwk"),(LPCTSTR)TTT);
					TTT.Format("%s",Values[17].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("SpectMask"),(LPCTSTR)TTT);
					TTT.Format("%s",Values[5].bstrVal);
					TTT.TrimRight();
					rs2.SetFieldValue(_T("TVChannel"),(LPCTSTR)TTT);
					rs2.Update();
					rs2.Close();
	// rrc_sub_area
					SQL1.Format(_T("select * from ge06_allot_sub_area_xref where terrakey=%ld"),Values[0].lVal);
					rs4.Open(dbOpenSnapshot, SQL1);
///					rs2.Open(dbOpenDynaset, _T("select * from rrc_sub_area"));
					while(!rs4.IsEOF())
					{
						COleVariant ContourKey;
						CString NewContourKey;
						rs4.GetFieldValue((short)0,ContourKey);

		//rrc_contour
						rs2.Open(dbOpenSnapshot, _T("select max(contourkey)+1 from rrc_contour"));
						rs2.GetFieldValue((short)0,TempOLE);
						NewContourKey.Format(_T("%ld"),TempOLE.lVal);
						rs2.Close();
						if(NewContourKey.IsEmpty() || NewContourKey==_T("0")) NewContourKey=_T("1");
				//		SQL1.Format(_T("select contour_id, adm, ctry, 999 from ge06_sub_area_adm where ge06_sub_area_key=%ld"), ContourKey.lVal);
				//		rs3.Open(dbOpenSnapshot,SQL1);
				//		for(i=0;i<4;i++)
				//			rs3.GetFieldValue(i,Values2[i]);
				//		rs3.Close();
						TTT.Format("%s",Values[2].bstrVal);
						TTT.TrimRight();
						CString TTT2;
						TTT2.Format("%s",Values[18].bstrVal);
						TTT2.TrimRight();
						SQL1.Format(_T("insert into rrc_contour(contourkey, contour_id, adm, ctry, nb_test_pts) select %s, %s,'%s','%s',999 "), NewContourKey, 
							NewContourKey/*Values2[0].lVal*/, (LPCTSTR)TTT2, (LPCTSTR)TTT);
						DB.Execute(SQL1);
			//rrc_contour_pt
						SQL1.Format(_T("select * from ge06_sub_area_pt where ge06_sub_area_key=%ld"), ContourKey.lVal);
						rs3.Open(dbOpenSnapshot,SQL1);
						long int pt_count=0;
						while(!rs3.IsEOF())
						{
							for(i=0;i<10;i++)
								rs3.GetFieldValue(i,Values2[i]);
							rs2.Open(dbOpenDynaset, _T("select * from rrc_contour_pt"));
							rs2.AddNew();
							rs2.SetFieldValue(_T("contourkey"),(LPCTSTR)NewContourKey);
							rs2.SetFieldValue(_T("test_pt"),Values2[1]);
							rs2.SetFieldValue(_T("long_deg"),Values2[2]);
							rs2.SetFieldValue(_T("long_min"),Values2[4]);
							rs2.SetFieldValue(_T("long_sec"),Values2[5]);
							rs2.SetFieldValue(_T("long_ew"),Values2[3]);
							rs2.SetFieldValue(_T("lat_deg"),Values2[6]);
							rs2.SetFieldValue(_T("lat_min"),Values2[8]);
							rs2.SetFieldValue(_T("lat_sec"),Values2[9]);
							rs2.SetFieldValue(_T("lat_ns"),Values2[7]);
							rs2.Update();
							rs2.Close();
							rs3.MoveNext();
							pt_count++;
						}
						rs3.Close();

						SQL1.Format(_T("update rrc_contour SET nb_test_pts=%ld where contourkey=%s"), pt_count, NewContourKey);
						DB.Execute(SQL1);

						SQL1.Format(_T("insert into rrc_sub_area(allotkey,contourkey) select %s, %s "),
							LastStID, NewContourKey);
						DB.Execute(SQL1);
						rs4.MoveNext();
///						rs2.AddNew();
///						rs2.SetFieldValue(_T("allotkey"),AllotKey);
///						rs2.SetFieldValue(_T("contourkey"),TempOLE);
///						rs2.Update();
					}
///					rs2.Close();
					rs4.Close();
				}
				rs.MoveNext();
				Recs++;
				if((Recs%10)==0)
					m_ImportProgress.StepIt();
			}
			rs.Close();
			DB.Close();
			DB1.Close();
//			DB2.Close();
			CCmdTarget::EndWaitCursor();
			if(!RecFound)
				MessageBox(_Z("The query returned no records!"),"IFIC Import", MB_ICONEXCLAMATION|MB_OK);
			else
			{
				if( Ans==IDYES ) CDialog::OnOK();
			}
		}
	}
	else
		AfxMessageBox(_Z("Please select at least one service (FM/TV or FXM)."));

//	CDialog::OnOK();
}

CString CIFICImport::GetAdmList()
{
	CString List,Item;
	for(int i=0;i<m_AdmSel.GetCount();i++)
	{
		m_AdmSel.GetText(i,Item);
		Item.TrimRight(" ");
		List+="'" + Item + "',";
	}
	List.Delete(List.GetLength()-1);
	return List;
}

CString CIFICImport::GetFreqCond()
{
	CString List,Item;
	for(int i=0;i<m_FreqCondSel.GetCount();i++)
	{
		m_FreqCondSel.GetText(i,Item);
		Item.Replace("F ","Freq_Assgn ");
		Item.Replace("MHz","");
		Item.Replace("MHz","");
		List+="(" + Item + ") or ";
	}
	List.Delete(List.GetLength()-3,4);
	return List;
}

CString CIFICImport::GetClassList()
{
	CString List,Item;
	for(int i=0;i<m_ClassSel.GetCount();i++)
	{
		m_ClassSel.GetText(i,Item);
		CString Code=Item.Left(2);
		Code.TrimRight(" ");
		List+="'" + Code + "',";
	}
	List.Delete(List.GetLength()-1);
	return List;
}

CString CIFICImport::GetFragList()
{
	CString List,Item;
	for(int i=0;i<m_FragSel.GetCount();i++)
	{
		m_FragSel.GetText(i,Item);
		Item.TrimRight(" ");
		List+="'" + Item + "',";
	}
	List.Delete(List.GetLength()-1);

	CDatabase DB;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset rs;
	rs.m_pDatabase=&DB;
	rs.Open(CRecordset::snapshot, "select Fragment from provisions where provision in ("+List+")");

	List="";
	while(!rs.IsEOF())
	{
		rs.GetFieldValue((short)0,Item);
		Item.TrimRight(" ");
		List+="'" + Item + "',";
		rs.MoveNext();
	}
	rs.Close();
	DB.Close();
	List.Delete(List.GetLength()-1);

	return List;
}

void CIFICImport::OnFreqRem() 
{
	m_FreqCondSel.DeleteString(m_FreqCondSel.GetCurSel());	
}

void CIFICImport::ImportData(CDatabase m_DB, CRecordset m_rs)
{
	CRecordset m_BRIFIC;
	m_BRIFIC.m_pDatabase=&m_DB;
	m_BRIFIC.Open(CRecordset::dynaset, "BRIFIC");
	m_rs.MoveFirst();
	while(!m_rs.IsEOF())
	{
		m_BRIFIC.AddNew();
//		m_BRIFIC.
	}//end while
	m_BRIFIC.Close();
}

CString CIFICImport::GetODBCPath(CString Connection)
{
	CString Path;
	int Start;
	Start=Connection.Find("DBQ=")+4;
	Path=Connection.Mid(Start,Connection.Find(";",Start)-Start);
	AfxMessageBox(Path);
	return Path;
}

void CIFICImport::OnFmtv() 
{
	if(m_FMTV.GetCheck())
	{
		m_Digital.EnableWindow();
		/*CDatabase DB;
		CRecordset m_rs;
		CDBVariant TempVar;
		CString m_Tbl;
		DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
		m_Tbl="select * from StClass where StSrv='B'";
		m_rs.m_pDatabase=&DB;
		m_rs.Open( CRecordset::snapshot, m_Tbl);
		m_StationClass.ResetContent();
		CString F1,F2;
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,F1);
			m_rs.GetFieldValue((short)1,F2);
			m_StationClass.AddString(F1+" - "+F2);
			m_rs.MoveNext();
		}
		m_rs.Close();
		DB.Close();*/
	}
	else
		m_Digital.EnableWindow(false);
}

void CIFICImport::OnFxm() 
{
/*	if(m_FXM.GetCheck())
	{
		CDatabase DB;
		CRecordset m_rs;
		CDBVariant TempVar;
		CString m_Tbl;
		DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
		m_Tbl="select * from StClass where StSrv='F' or StSrv='MT'";
		m_rs.m_pDatabase=&DB;
		m_rs.Open( CRecordset::snapshot, m_Tbl);
		CString F1,F2;
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,F1);
			m_rs.GetFieldValue((short)1,F2);
			m_StationClass.AddString(F1+" - "+F2);
			m_rs.MoveNext();
		}
		m_rs.Close();
		DB.Close();
	}
*/	
}

void CIFICImport::OnClassRemove() 
{
	m_ClassSel.DeleteString(m_ClassSel.GetCurSel());	
	
}

void CIFICImport::OnFragRemove() 
{
	m_FragSel.DeleteString(m_FragSel.GetCurSel());	
	
}

void CIFICImport::OnClassAdd() 
{
	CString SelItem;
	if(m_StationClass.GetCurSel()!=CB_ERR )
	{
		m_StationClass.GetWindowText(SelItem);
		if(m_ClassSel.FindString(-1,SelItem)==LB_ERR)
			m_ClassSel.AddString(SelItem);	
	}	
}

void CIFICImport::OnFragAdd() 
{
	CString SelItem;
	if(m_Fragment.GetCurSel()!=CB_ERR )
	{
		m_Fragment.GetWindowText(SelItem);
		if(m_FragSel.FindString(-1,SelItem)==LB_ERR)
			m_FragSel.AddString(SelItem);	
	}	
}

void CIFICImport::OnClassClear() 
{
	m_ClassSel.ResetContent();	
}

void CIFICImport::OnFragClear() 
{
	m_FragSel.ResetContent();	
}

void CIFICImport::RemoveQuote(CString *Str)
{
	while(true)
	{
		int place=Str->Find(_T("\'"));
		if(place!=-1)
			Str->SetAt(place,' ');
		else
			break;
	}
}

void CIFICImport::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

CString CIFICImport::BandWidthCode(double BW)
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
		double FPart2=BW-IPart;
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

double CIFICImport::Interp2(double *D0,double *E0,double d,int num) 
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

void CIFICImport::AntennaSaveTxt(CString Name, double Gain, double BWH, double BWV, double FLow, double FHi, 
								 CString Pol, double PattV[], double PattH[], double Azimuth)
{
	CString Path;
	Path=GetCommandLine();
	int Place=Path.ReverseFind('\\')-1;
	Path.Delete(0);
	Path.Delete(Place,Path.GetLength()-Place);
	Place=Path.ReverseFind('\\')+1;
	Path.Delete(Place,Path.GetLength()-Place);
	Path+=_T("Antenna\\ant_");
	Name.Format(_T("%09ld"),atol((LPCTSTR)Name));
	FILE *fp;
	fp=fopen(Path+Name+_T(".ant"),_T("wt"));
	if(fp)
	{
		double Patt[2][360]={0.0},Patt2[2][360]={0.0};
		for(int i=0;i<360;i++)		Patt[0][i]=Patt[1][i]=i;
		Pol.TrimRight();
		Azimuth*=-1.0;
		if(Pol==_T("H"))
		{
			if(Azimuth>=0)
			{
				i=359;
				while(Patt[0][i]>359-Azimuth && i>=0)
					i--;
				if(i==-1) i=359;
				for(int j=i;j>=0;j--)
					Patt[0][j]+=Azimuth;
				for(j=i+1;j<360;j++)
					Patt[0][j]-=360-Azimuth;
			}
			else
			{
				i=0;
				while(Patt[0][i]<-Azimuth && i<360)
					i++;
				if(i==360) i=0;
				for(int j=i;j<360;j++)
					Patt[0][j]+=Azimuth;
				for(j=0;j<i;j++)
					Patt[0][j]+=360+Azimuth;
			}
			for(int j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[0][j]]=PattH[j];
			}
			for(i=0;i<360;i++)
			{
				PattH[i]= Patt2[1][i];
			}
			Azimuth=90;
			if(Azimuth>=0)
			{
				i=359;
				while(Patt[1][i]>359-Azimuth && i>=0)
					i--;
				if(i==-1) i=359;
				for(int j=i;j>=0;j--)
					Patt[1][j]+=Azimuth;
				for(j=i+1;j<360;j++)
					Patt[1][j]-=360-Azimuth;
			}
			for(j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[1][j]]=PattV[j];
			}
			for(i=0;i<360;i++)
			{
				PattV[i]= Patt2[1][i];
			}
		}
		if(Pol==_T("V"))
		{
			if(Azimuth>=0)
			{
				i=359;
				while(Patt[0][i]>359-Azimuth && i>=0)
					i--;
				if(i==-1) i=359;
				for(int j=i;j>=0;j--)
					Patt[0][j]+=Azimuth;
				for(j=i+1;j<360;j++)
					Patt[0][j]-=360-Azimuth;
			}
			else
			{
				i=0;
				while(Patt[0][i]<-Azimuth && i<360)
					i++;
				if(i==360) i=0;
				for(int j=i;j<360;j++)
					Patt[0][j]+=Azimuth;
				for(j=0;j<i;j++)
					Patt[0][j]+=360+Azimuth;
			}
			for(int j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[0][j]]=PattV[j];
			}
			for(i=0;i<360;i++)
			{
				PattV[i]= Patt2[1][i];
			}
			Azimuth=90;
			if(Azimuth>=0)
			{
				i=359;
				while(Patt[1][i]>359-Azimuth && i>=0)
					i--;
				if(i==-1) i=359;
				for(int j=i;j>=0;j--)
					Patt[1][j]+=Azimuth;
				for(j=i+1;j<360;j++)
					Patt[1][j]-=360-Azimuth;
			}
			for(j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[1][j]]=PattH[j];
			}
			for(i=0;i<360;i++)
			{
				PattH[i]= Patt2[1][i];
			}
		}
		if(Pol==_T("M"))
		{
			if(Azimuth>=0)
			{
				i=359;
				while(Patt[0][i]>359-Azimuth && i>=0)
					i--;
				if(i==-1) i=359;
				for(int j=i;j>=0;j--)
					Patt[0][j]+=Azimuth;
				for(j=i+1;j<360;j++)
					Patt[0][j]-=360-Azimuth;
			}
			else
			{
				i=0;
				while(Patt[0][i]<-Azimuth && i<360)
					i++;
				if(i==360) i=0;
				for(int j=i;j<360;j++)
					Patt[0][j]+=Azimuth;
				for(j=0;j<i;j++)
					Patt[0][j]+=360+Azimuth;
			}
			for(int j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[0][j]]=PattH[j];
			}
			for(i=0;i<360;i++)
			{
				PattH[i]= Patt2[1][i];
			}

			for(i=0;i<180;i++)
			{
				double Temp=PattV[i];
				PattV[i]= PattV[359-i];
				PattV[359-i]=Temp;
			}
			Azimuth=-Azimuth+90;
			if(Azimuth>=0)
			{
				i=359;
				while(Patt[1][i]>359-Azimuth && i>=0)
					i--;
				if(i==-1) i=359;
				for(int j=i;j>=0;j--)
					Patt[1][j]+=Azimuth;
				for(j=i+1;j<360;j++)
					Patt[1][j]-=360-Azimuth;
			}
			for(j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[1][j]]=PattV[j];
			}
			for(i=0;i<360;i++)
			{
				PattV[i]= Patt2[1][i];
			}
		}

		fprintf(fp,_T("Name %09ld\n"),atol(Name));
		fprintf(fp,_T("Gain_dBi %lf\n"),Gain);
		fprintf(fp,_T("BeamWidth_H %lf\n"),BWH);
		fprintf(fp,_T("BeamWidth_V %lf\n"),BWV);
		fprintf(fp,_T("Frq_Lo %lf\n"),FLow);
		fprintf(fp,_T("Frq_Hi %lf\n"),FHi);
		fprintf(fp,_T("Frq_unit MHz\n"));
		fprintf(fp,_T("Polarization %s\n"),Pol);
		fprintf(fp,_T("Pattern\n"));
		if(Pol!=_T("V"))
		{
			for(i=0;i<360;i++)
				fprintf(fp,_T("%3d%6.2f%6.2f\n"),i,PattH[i],PattV[i]);
		}
		else
		{
			for(i=0;i<360;i++)
				fprintf(fp,_T("%3d%6.2f%6.2f\n"),i,PattV[i],PattH[i]);
		}
		fclose(fp);
	}
	else
		AfxMessageBox(_Z("Couldn't create *.ant file!"));
}


void CIFICImport::OnIDAdd() 
{
	CString TerraKey;
	m_TerraKey.GetWindowText(TerraKey);
	if(!TerraKey.IsEmpty())
	{
		if(m_IDSel.FindString(-1,TerraKey)==LB_ERR)
			m_IDSel.AddString(TerraKey);	
	}
}

void CIFICImport::OnIDRemove() 
{
	m_IDSel.DeleteString(m_IDSel.GetCurSel());		
}

CString CIFICImport::GetIDList()
{
	CString List,Item;
	for(int i=0;i<m_IDSel.GetCount();i++)
	{
		m_IDSel.GetText(i,Item);
		Item.TrimRight(" ");
		List+= "'" + Item + "',";
	}
	List.Delete(List.GetLength()-1);

	return List;
}

void CIFICImport::TranslateDialog(CDialog *pDialog)
{
	CString strOriginal(_T(""));
	for (int iID = 0; iID < _APS_NEXT_CONTROL_VALUE; iID++)
	{
		pDialog->GetDlgItemText(iID, strOriginal);
		if (!strOriginal.IsEmpty())
		{
			if(((pDialog->GetDlgItem(iID))->IsKindOf(RUNTIME_CLASS(CComboBox)))!=1)
			{
				CString s = GetTranslatedString(strOriginal, m_Lang);
				if (!s.IsEmpty())// && strOriginal != s)
					pDialog->SetDlgItemText(iID, s);
			}
		}
	}//for
	strOriginal = _T("");
	pDialog->GetWindowText(strOriginal);
	if (!strOriginal.IsEmpty())
	{
		CString s = GetTranslatedString(strOriginal, m_Lang);
		if (!s.IsEmpty() && strOriginal != s)
			pDialog->SetWindowText(s);
	}
}

CString CIFICImport::GetTranslatedString(CString strOriginal, CString Lang)
{
	static CString m_Lang;
//	m_Lang="CC";
	if(Lang!=m_Lang && !Lang.IsEmpty()) 
		m_Lang=Lang;
	if(m_Lang==_T("En"))	return strOriginal;
	int ID=-1;
	HMODULE	hMod = LoadLibrary("ResDLLen.dll");
	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			int n=0, nLen = ::LoadString(hMod, 0, szTemp, 1000);
			if(nLen!=0)		n = atoi(szTemp);

			for(int ids=1; ids<=n; ids++)
			{
				nLen = ::LoadString(hMod, ids, szTemp, 1000);
				if(strOriginal==szTemp)
				{
					ID = ids;
					break;
				}
			}
		}
		FreeLibrary(hMod);
	}//hMod

	CString str;
	if		(m_Lang==_T("Fr")) 	hMod = LoadLibrary("ResDLLfr.dll");
	else if	(m_Lang==_T("Es")) 	hMod = LoadLibrary("ResDLLes.dll");
	else if	(m_Lang==_T("Ch")) 	hMod = LoadLibrary("ResDLLch.dll");
	else if	(m_Lang==_T("Ar")) 	hMod = LoadLibrary("ResDLLar.dll");
	else if	(m_Lang==_T("Ru")) 	hMod = LoadLibrary("ResDLLru.dll");

	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			::LoadString(hMod, ID, szTemp, 1000);
			str = szTemp;
		}
		FreeLibrary(hMod);
	}//hMod

	return str;
}



void CIFICImport::OnMdb() 
{
	CDatabase m_DB;
	m_Browse.EnableWindow(TRUE);
	m_BRIFIC="";
	try
	{
		m_DB.Open("CDTerRaBaseBETA", FALSE, FALSE, "ODBC;", FALSE);
	}
    catch( CDBException* e )
    {
        AfxMessageBox(_Z("The BRIFIC is not installed correctly!"), MB_ICONEXCLAMATION );
        e->Delete();
		EndDialog(!IDOK);
		return;
    }	
	m_BRIFIC="CDTerRaBaseBETA";
}

void CIFICImport::OnSqlite() 
{
//	m_Browse.EnableWindow(FALSE);
	m_BRIFIC="";

	CDatabase m_DB;
	try
	{
		m_DB.Open("BRIFIC2019SQLiteAccess", FALSE, FALSE, "ODBC;", FALSE);
	}
    catch( CDBException* e )
    {
        AfxMessageBox(_Z("The BRIFIC link database is not created correctly!"), MB_ICONEXCLAMATION );
        e->Delete();
		EndDialog(!IDOK);
		return;
    }
	m_BRIFIC="BRIFIC2019SQLiteAccess";

}

void CIFICImport::OnBrowse() 
{
	CString SQLiteFile;
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _Z("SQLite Linked Files (*.MDB)|*.MDB||"), NULL );
	FileDlg.DoModal();
	SQLiteFile=FileDlg.GetPathName();
	if(!SQLiteFile.IsEmpty())	
		((CEdit *)GetDlgItem(IDC_DB3_FILE))->SetWindowText(SQLiteFile);	
}
