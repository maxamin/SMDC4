// SRSImport.cpp : implementation file
//
#include "stdafx.h"
#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS
#include "resource.h"
//#include "ific.h"
#include "SRSImport.h"
#include <afxdao.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSRSImport dialog

extern "C" char * WINAPI Code2NameCTY_lang(CString co, CString mLang);	//CNT.lib
extern "C" char * WINAPI AllCodes_lang(CString CTYCOD[], long *NOCTY);	//CNT.lib

CSRSImport::CSRSImport(CWnd* pParent /*=NULL*/)
	: CDialog(CSRSImport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSRSImport)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSRSImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSRSImport)
	DDX_Control(pDX, IDC_PROGRESS, m_ImportProgress);
	DDX_Control(pDX, IDC_ADMSEL, m_AdmSel);
	DDX_Control(pDX, IDC_ADMLIST, m_AdmList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSRSImport, CDialog)
	//{{AFX_MSG_MAP(CSRSImport)
	ON_BN_CLICKED(IDC_AdmAdd, OnAdmAdd)
	ON_BN_CLICKED(IDC_AdmAddAll, OnAdmAddAll)
	ON_BN_CLICKED(IDC_AdmRemove, OnAdmRemove)
	ON_BN_CLICKED(IDC_AdmClear, OnAdmClear)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRSImport message handlers

void CSRSImport::OnAdmAdd() 
{
	CString SelItem;
	if(m_AdmList.GetCurSel()!=CB_ERR )
	{
		m_AdmList.GetText(m_AdmList.GetCurSel(),SelItem);
		if(m_AdmSel.FindString(-1,SelItem)==LB_ERR)
			m_AdmSel.AddString(SelItem);	
	}	
}

void CSRSImport::OnAdmAddAll() 
{
	m_AdmSel.DeleteString(m_AdmSel.GetCurSel());	
}

void CSRSImport::OnAdmRemove() 
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

void CSRSImport::OnAdmClear() 
{
	m_AdmSel.ResetContent();	
}

BOOL CSRSImport::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	CRecordset m_rs;
	CDatabase m_DB;
	try
	{
		m_DB.Open(m_CDBSTR, FALSE, FALSE, _T("ODBC;"), FALSE);
	}
    catch( CDBException* e )
    {
        AfxMessageBox( _Z("The main database is not installed correctly!"), MB_ICONEXCLAMATION );
        e->Delete();
		return TRUE;
    }
	m_rs.m_pDatabase=&m_DB;
/*	m_rs.Open(CRecordset::snapshot, _T("select cga_symbol from ctry_geo_area order by cga_symbol"));
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

	m_DB.Close();
	TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSRSImport::OnBrowse() 
{
	CString MDBFile;
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("MDB Files (*.mdb)|*.mdb||"), NULL );
	FileDlg.DoModal();
	MDBFile=FileDlg.GetPathName();
	if(!MDBFile.IsEmpty())	
	{
		CDaoDatabase DB;
		DB.Open(MDBFile);
		CDaoTableDef TD(&DB);
		try
		{
			TD.Open(_T("notice"));
		}
		catch( CDaoException* e )
		{
			AfxMessageBox( _Z("This database is not suitable for import!"), MB_ICONEXCLAMATION );
			e->Delete();
			DB.Close();
			return;
		}
		TD.Close();
		try
		{
			TD.Open(_T("e_stn"));
		}
		catch( CDaoException* e )
		{
			AfxMessageBox( _Z("This database is not suitable for import!"), MB_ICONEXCLAMATION );
			e->Delete();
			DB.Close();
			return;
		}
		TD.Close();
		try
		{
			TD.Open(_T("e_ant"));
		}
		catch( CDaoException* e )
		{
			AfxMessageBox( _Z("This database is not suitable for import!"), MB_ICONEXCLAMATION );
			e->Delete();
			DB.Close();
			return;
		}
		TD.Close();
		DB.Close();
	}
	((CEdit *)GetDlgItem(IDC_MDB_FILE))->SetWindowText(MDBFile);
}

void CSRSImport::OnOK() 
{
	CString SQL1,SQL2,MDBFile;
	((CEdit *)GetDlgItem(IDC_MDB_FILE))->GetWindowText(MDBFile);
	if(MDBFile.IsEmpty())
	{
		AfxMessageBox(_Z("Please select a database!"));
		return;
	}
	if(m_AdmSel.GetCount()==0)
	{
		AfxMessageBox(_Z("At least one administration should be selected!"));
		return;
	}
	CCmdTarget::BeginWaitCursor();
	SQL2+=_T("SELECT ntc_id, ntc_type, adm_ref_id, d_adm, prov, act_code, adm, ntwk_org, ntf_occurs, tgt_ntc_id ");
	SQL1+=_T("FROM notice where (ntc_type='S' or ntc_type='T') ");
	if(m_AdmSel.GetCount()) 
		SQL1+=" and adm in (" + GetAdmList() + ")";
	COleVariant Values[60];
	CString Tot;
	char buf[35];
	long Recs=0,Total;
	CDaoDatabase DB1;
	CDatabase DB2;
	DB1.Open(MDBFile);
	DB2.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	CDaoRecordset rs,rs3,rs4,rs5;
	CRecordset rs2;
	rs.m_pDatabase=&DB1;
	rs3.m_pDatabase=&DB1;
	rs4.m_pDatabase=&DB1;
	rs5.m_pDatabase=&DB1;
	rs.Open(dbOpenSnapshot, _T("select count(ntc_id) ")+SQL1);
	COleVariant Var,null;
//	null.SetString(_T("(null)"),VT_BSTR );
	rs.GetFieldValue((short)0,Var);
	Total=Var.lVal;
	rs.Close();
	rs.Open(dbOpenSnapshot, SQL2+SQL1);
	m_ImportProgress.SetRange32(0,Total);
	m_ImportProgress.SetStep(10);
	int Ans=IDNO;
	if(Total>0)
	{
		CString Message;
		Message.Format(_Z("%ld record(s) found. Continue?"),Total);
		Ans=AfxMessageBox(Message,MB_YESNO);
	}
	while(Total>0 && Ans==IDYES)
	{
		CString LastNtcID, LastPattID, LastGrpID, LastAntID, Vals[60], Part;
		long OldNtcID, OldGrpID=0;
		if(rs.IsEOF()) break;
		rs2.m_pDatabase=&DB2;
		for(int i=0;i<10;i++)
			rs.GetFieldValue(i,Values[i]);
		for(i=1;i<9;i++)
			Vals[i].Format(_T("%s"),Values[i].bstrVal);
		OldNtcID=Values[0].lVal;
//notice
			rs2.Open(CRecordset::snapshot, _T("select max(ntc_ID)+1 from e_stn"));
			rs2.GetFieldValue((short)0,LastNtcID);
			rs2.Close();
			if(LastNtcID.IsEmpty()) LastNtcID=_T("1");
			SQL1.Format(_T("SELECT %s, '%s', '%s','%s','%s','%s','%s','%s'"), LastNtcID, (!Vals[1].Compare(_T("(null)"))?"":Vals[1]), 
				(!Vals[2].Compare(_T("(null)"))?"":Vals[2]), 
				(!Vals[4].Compare(_T("(null)"))?"":Vals[4]), (!Vals[5].Compare(_T("(null)"))?"":Vals[5]),
				(!Vals[6].Compare(_T("(null)"))?"":Vals[6]), (!Vals[7].Compare(_T("(null)"))?"":Vals[7]),
				(!Vals[8].Compare(_T("(null)"))?"":Vals[8]));
			if(Values[9].vt==VT_NULL)
				SQL1+=_T(",NULL ");
			else
			{
				Part.Format(_T(",%ld "),Values[9].lVal);
				SQL1+=Part;
			}
			SQL1=_T("INSERT INTO notice (ntc_id, ntc_type, adm_ref_id, prov, act_code, adm, ntwk_org, ntf_occurs, tgt_ntc_id) ")+SQL1;
			DB2.ExecuteSQL(SQL1);
//e_stn
			SQL1.Format(_T("select ntc_id, stn_name, ctry, long_deg, long_ew, long_min, long_sec, lat_deg, lat_ns, lat_min, lat_sec, sat_name, long_nom, attch_hor, elev_min, elev_max, azm_fr, azm_to, ant_alt, f_active, long_dec, lat_dec, f_pfd_se from e_stn where ntc_id=%ld"),OldNtcID);
			rs3.Open(dbOpenSnapshot, SQL1);
			for(i=0;i<23;i++)
				rs3.GetFieldValue(i,Values[i]);
			rs3.Close();
			Vals[1].Format(_T("%s"),Values[1].bstrVal);
			Vals[2].Format(_T("%s"),Values[2].bstrVal);
			Vals[3]=((Values[3].vt==1)?_T("NULL"):itoa(Values[3].iVal,buf,10));
			Vals[4].Format(_T("%s"),Values[4].bstrVal);
			Vals[5]=((Values[5].vt==1)?_T("NULL"):itoa(Values[5].iVal,buf,10));
			Vals[6]=((Values[6].vt==1)?_T("NULL"):itoa(Values[6].iVal,buf,10));
			Vals[7]=((Values[7].vt==1)?_T("NULL"):itoa(Values[7].iVal,buf,10));
			Vals[8].Format(_T("%s"),Values[8].bstrVal);
			Vals[9]=((Values[9].vt==1)?_T("NULL"):itoa(Values[9].iVal,buf,10));
			Vals[10]=((Values[10].vt==1)?_T("NULL"):itoa(Values[10].iVal,buf,10));
			Vals[11].Format(_T("%s"),Values[11].bstrVal);
			Vals[12]=((Values[12].vt==1)?_T("NULL"):gcvt(Values[12].fltVal,20,buf));
			Vals[13]=((Values[13].vt==1)?_T("NULL"):itoa(Values[13].iVal,buf,10));
			Vals[14]=((Values[14].vt==1)?_T("NULL"):gcvt(Values[14].fltVal,20,buf));
			Vals[15]=((Values[15].vt==1)?_T("NULL"):gcvt(Values[15].fltVal,20,buf));
			Vals[16]=((Values[16].vt==1)?_T("NULL"):gcvt(Values[16].fltVal,20,buf));
			Vals[17]=((Values[17].vt==1)?_T("NULL"):gcvt(Values[17].fltVal,20,buf));
			Vals[18]=((Values[18].vt==1)?_T("NULL"):ltoa(Values[18].lVal,buf,10));
			Vals[19].Format(_T("%s"),Values[19].bstrVal);
			Vals[20]=((Values[20].vt==1)?_T("NULL"):gcvt(Values[20].fltVal,20,buf));
			Vals[21]=((Values[21].vt==1)?_T("NULL"):gcvt(Values[21].fltVal,20,buf));
			Vals[22].Format(_T("%s"),Values[22].bstrVal);
			
			SQL1.Format(_T("SELECT %s, '%s','%s',%s,'%s',%s,%s,%s,'%s',%s,%s,'%s',%s,%s,%s,%s,%s,%s,%s,'%s',%s,%s,'%s',-1"), LastNtcID,
				(!Vals[1].Compare(_T("(null)"))?"":Vals[1]), (!Vals[2].Compare(_T("(null)"))?"":Vals[2]), Vals[3],
				(!Vals[4].Compare(_T("(null)"))?"":Vals[4]),Vals[5],Vals[6],Vals[7],(!Vals[8].Compare(_T("(null)"))?"":Vals[8]),
				Vals[9],Vals[10],(!Vals[11].Compare(_T("(null)"))?"":Vals[11]),
				Vals[12],Vals[13],Vals[14],Vals[15],Vals[16],Vals[17],
				Vals[18],(!Vals[19].Compare(_T("(null)"))?"":Vals[19]),
				Vals[20],Vals[21],(!Vals[22].Compare(_T("(null)"))?"":Vals[22]));
			SQL2=_T("INSERT INTO e_stn (ntc_id, stn_name, ctry, long_deg, long_ew, long_min, long_sec, lat_deg, lat_ns, lat_min, lat_sec, sat_name, long_nom, attch_hor, elev_min, elev_max, azm_fr, azm_to, ant_alt, f_active, long_dec, lat_dec, f_pfd_se, LicID) ");
			SQL1=SQL2+SQL1;
			DB2.ExecuteSQL(SQL1);
//hor_elev
			SQL1.Format(_T("select * from hor_elev where ntc_id=%ld"),OldNtcID);
			rs3.Open(dbOpenSnapshot, SQL1);
			while(!rs3.IsEOF())
			{
				for(i=0;i<4;i++)
					rs3.GetFieldValue(i,Values[i]);
				Vals[1]=((Values[1].vt==1)?_T("NULL"):gcvt(Values[1].fltVal,20,buf));
				Vals[2]=((Values[2].vt==1)?_T("NULL"):gcvt(Values[2].fltVal,20,buf));
				Vals[3]=((Values[3].vt==1)?_T("NULL"):gcvt(Values[3].fltVal,20,buf));
				SQL1.Format(_T("insert into hor_elev (ntc_id,azm,elev_ang,hor_dist) select %s,%s,%s,%s "), LastNtcID,
					Vals[1],Vals[2],Vals[3]);
				DB2.ExecuteSQL(SQL1);
				rs3.MoveNext();
			}
			rs3.Close();
//e_ant_elev
			SQL1.Format(_T("select * from e_ant_elev where ntc_id=%ld"),OldNtcID);
			rs3.Open(dbOpenSnapshot, SQL1);
			while(!rs3.IsEOF())
			{
				for(i=0;i<3;i++)
					rs3.GetFieldValue(i,Values[i]);
				SQL1.Format(_T("insert into e_ant_elev (ntc_id,azm,elev_ang) select %s,%f,%f "), LastNtcID,
					Values[1].dblVal,Values[2].fltVal);
				DB2.ExecuteSQL(SQL1);
				rs3.MoveNext();
			}
			rs3.Close();
//e_ant
			SQL1.Format(_T("select ntc_id, emi_rcp, beam_name, act_code, beam_old, bmwdth, attch_e, attch_e_x, gain, pattern_id, pattern_id_x, ant_diam, attch_crdn from e_ant where ntc_id=%ld"),OldNtcID);
			rs3.Open(dbOpenSnapshot, SQL1);
			while(!rs3.IsEOF())
			{
				rs2.Open(CRecordset::snapshot, _T("select max(AntID)+1 from e_ant"));
				rs2.GetFieldValue((short)0,LastAntID);
				rs2.Close();
				if(LastAntID.IsEmpty()) LastAntID=_T("1");
				for(i=0;i<13;i++)
					rs3.GetFieldValue(i,Values[i]);
				Vals[1].Format(_T("%s"),Values[1].bstrVal);
				Vals[2].Format(_T("%s"),Values[2].bstrVal);
				Vals[3].Format(_T("%s"),Values[3].bstrVal);
				Vals[4].Format(_T("%s"),Values[4].bstrVal);
				if(Values[9].iVal>0)
				{
					rs2.Open(CRecordset::snapshot, _T("select max(pattern_id)+1 from ant_type"));
					rs2.GetFieldValue((short)0,LastPattID);
					rs2.Close();
					if(LastPattID.IsEmpty()) LastPattID=_T("1");
					SQL1.Format(_T("select * from ant_type where pattern_id=%d"),Values[9].iVal);
					rs4.Open(dbOpenSnapshot, SQL1);
					for(i=15;i<27;i++)
						rs4.GetFieldValue(i-15,Values[i]);
					rs4.Close();
					Vals[16].Format(_T("%s"),Values[16].bstrVal);
					Vals[17].Format(_T("%s"),Values[17].bstrVal);
					Vals[18].Format(_T("%s"),Values[18].bstrVal);
					Vals[19].Format(_T("%s"),Values[19].bstrVal);
					Vals[20]=((Values[20].vt==1)?_T("NULL"):gcvt(Values[20].fltVal,20,buf));
					Vals[21]=((Values[21].vt==1)?_T("NULL"):gcvt(Values[21].fltVal,20,buf));
					Vals[22]=((Values[22].vt==1)?_T("NULL"):gcvt(Values[22].fltVal,20,buf));
					Vals[23]=((Values[23].vt==1)?_T("NULL"):gcvt(Values[23].fltVal,20,buf));
					Vals[24]=((Values[24].vt==1)?_T("NULL"):gcvt(Values[24].fltVal,20,buf));
					Vals[25].Format(_T("%s"),Values[25].bstrVal);
					Vals[26].Format(_T("%s"),Values[26].bstrVal);
					SQL1.Format(_T("select %s,'%s','%s','%s','%s',%s,%s,%s,%s,%s,'%s','%s' "),LastPattID,
						(!Vals[16].Compare(_T("(null)"))?"":Vals[16]),(!Vals[17].Compare(_T("(null)"))?"":Vals[17]),
						(!Vals[18].Compare(_T("(null)"))?"":Vals[18]),(!Vals[19].Compare(_T("(null)"))?"":Vals[19]),
						Vals[20],Vals[21],Vals[22],Vals[23],Vals[24],
						(!Vals[25].Compare(_T("(null)"))?"":Vals[25]),(!Vals[26].Compare(_T("(null)"))?"":Vals[26]));
					SQL1=_T("insert into ant_type (pattern_id,f_ant_type,f_sub_type,emi_rcp,pattern,coefa,coefb,coefc,coefd,phi1,f_ant_new,apl_name) ")+SQL1;
					DB2.ExecuteSQL(SQL1);
				}

				Vals[5]=((Values[5].vt==1)?_T("NULL"):gcvt(Values[5].fltVal,20,buf));
				Vals[6]=((Values[6].vt==1)?_T("NULL"):itoa(Values[6].iVal,buf,10));
				Vals[7]=((Values[7].vt==1)?_T("NULL"):itoa(Values[7].iVal,buf,10));
				Vals[8]=((Values[8].vt==1)?_T("NULL"):gcvt(Values[8].fltVal,20,buf));
				Vals[10]=((Values[10].vt==1)?_T("NULL"):itoa(Values[10].iVal,buf,10));
				Vals[11]=((Values[11].vt==1)?_T("NULL"):gcvt(Values[11].fltVal,20,buf));
				Vals[12]=((Values[12].vt==1)?_T("NULL"):itoa(Values[12].iVal,buf,10));
				SQL1.Format(_T("SELECT %s, '%s','%s','%s','%s',%s,%s,%s,%s,%d,%s,%s,%s,%s "), LastNtcID,
					(!Vals[1].Compare(_T("(null)"))?"":Vals[1]), (!Vals[2].Compare(_T("(null)"))?"":Vals[2]), 
					(!Vals[3].Compare(_T("(null)"))?"":Vals[3]), (!Vals[4].Compare(_T("(null)"))?"":Vals[4]),Vals[5],
					Vals[6],Vals[7],Vals[8],atoi(LastPattID),Vals[10],Vals[11],Vals[12],LastAntID);
				SQL2="INSERT INTO e_ant (ntc_id, emi_rcp, beam_name, act_code, beam_old, bmwdth, attch_e, attch_e_x, gain, pattern_id, pattern_id_x, ant_diam, attch_crdn, AntID) ";
				SQL1=SQL2+SQL1;
				DB2.ExecuteSQL(SQL1);
//grp
				SQL1=_T("select grp_id, ntc_id, emi_rcp, beam_name, page_no, act_code, adm_resp, bdwdth, d_inuse, ");
				SQL1+=_T("noise_t, op_agcy, polar_type, polar_ang, 0, 0, prd_valid, remark, tgt_grp_id, ");
				SQL1+=_T("pwr_max, bdwdth_aggr, f_trp_band, 0, area_no, observ_cls, reg_op_fr, reg_op_to, ");
				SQL1+=_T("d_upd, st_cur, d_st_cur, wic_no, wic_part, d_wic, d_prot_eff, fdg_reg, fdg_plan, fdg_tex, ");
				SQL1+=_T("fdg_observ, spl_grp_id, comment, '', 0, elev_min, gso_sep, prov, srv_code, ");
				SQL1+=_T("freq_min, freq_max, f_no_intfr, pfd_pk_7g, d_rcv, ra_stn_type, eirp_nom, f_fdg_reqd, cmp_grp_id, ");
				SQL1+=_T("f_cost_rec, f_cmp_str, f_cmp_rec, f_cmp_freq, f_cmp_emi, f_cmp_eas, f_cmp_prov, f_cmp_sas, ");
				SQL1+=_T("f_cmp_gpub, f_cmp_fdg, sr_type, sensitivity, f_ap30b_art6, plan_categ, plan_status ");
				SQL2.Format(_T("from grp where ntc_id=%ld and emi_rcp='%s' and beam_name='%s'"),OldNtcID,Vals[1],Vals[2]);
				SQL1=SQL1+SQL2;
				rs4.Open(dbOpenSnapshot, SQL1);
				while(!rs4.IsEOF())
				{
					CString EMI_RCP, BeamName;
					EMI_RCP=Vals[1];
					BeamName=Vals[2];
					rs2.Open(CRecordset::snapshot, _T("select max(grp_id)+1 from grp"));
					rs2.GetFieldValue((short)0,LastGrpID);
					rs2.Close();
					if(LastGrpID.IsEmpty()) LastGrpID=_T("1");
					for(i=0;i<48;i++)
						rs4.GetFieldValue(i,Values[i]);
					OldGrpID=Values[0].lVal;
					COleDateTime DT;
					Vals[2].Format(_T("%s"),Values[2].bstrVal);
					Vals[3].Format(_T("%s"),Values[3].bstrVal);
					Vals[4]=((Values[4].vt==1)?_T("NULL"):itoa(Values[4].iVal,buf,10));
					Vals[5].Format(_T("%s"),Values[5].bstrVal);
					Vals[6].Format(_T("%s"),Values[6].bstrVal);
					Vals[7]=((Values[7].vt==1)?_T("NULL"):itoa(Values[7].lVal,buf,10));
					DT=Values[8].date;
					Vals[8].Format(_T("%s"),DT.Format(_T("%Y/%m/%d")));
					Vals[9]=((Values[9].vt==1)?_T("NULL"):itoa(Values[9].lVal,buf,10));
					Vals[10]=((Values[10].vt==1)?_T("NULL"):itoa(Values[10].iVal,buf,10));
					Vals[11].Format(_T("%s"),Values[11].bstrVal);
					Vals[12]=((Values[12].vt==1)?_T("NULL"):gcvt(Values[12].fltVal,20,buf));
					Vals[13]=((Values[13].vt==1)?_T("NULL"):itoa(Values[13].iVal,buf,10));
					Vals[14]=((Values[14].vt==1)?_T("NULL"):itoa(Values[14].iVal,buf,10));
					Vals[15]=((Values[15].vt==1)?_T("NULL"):itoa(Values[15].iVal,buf,10));
					Vals[16].Format(_T("%s"),Values[16].bstrVal);
					Vals[17]=((Values[17].vt==1)?_T("NULL"):itoa(Values[17].lVal,buf,10));
					Vals[18]=((Values[18].vt==1)?_T("NULL"):gcvt(Values[18].fltVal,20,buf));
					Vals[19]=((Values[19].vt==1)?_T("NULL"):itoa(Values[19].lVal,buf,10));
					Vals[20].Format(_T("%s"),Values[20].bstrVal);
					Vals[21]=((Values[21].vt==1)?_T("NULL"):itoa(Values[21].iVal,buf,10));
					Vals[22]=((Values[22].vt==1)?_T("NULL"):itoa(Values[22].iVal,buf,10));
					Vals[23].Format(_T("%s"),Values[23].bstrVal);
					Vals[24]=((Values[24].vt==1)?_T("NULL"):itoa(Values[24].lVal,buf,10));
					Vals[25]=((Values[25].vt==1)?_T("NULL"):itoa(Values[25].lVal,buf,10));
					DT=Values[26].date;
					Vals[26].Format(_T("%s"),DT.Format(_T("%Y/%m/%d")));
					Vals[27].Format(_T("%s"),Values[27].bstrVal);
					DT=Values[28].date;
					Vals[28].Format(_T("%s"),DT.Format(_T("%Y/%m/%d")));
					Vals[29]=((Values[29].vt==1)?_T("NULL"):itoa(Values[29].iVal,buf,10));
					Vals[30].Format(_T("%s"),Values[30].bstrVal);
					DT=Values[31].date;
					Vals[31].Format(_T("%s"),DT.Format(_T("%Y/%m/%d")));
					DT=Values[32].date;
					Vals[32].Format(_T("%s"),DT.Format(_T("%Y/%m/%d")));
					Vals[33].Format(_T("%s"),Values[33].bstrVal);
					Vals[34].Format(_T("%s"),Values[34].bstrVal);
					Vals[35].Format(_T("%s"),Values[35].bstrVal);
					Vals[36].Format(_T("%s"),Values[36].bstrVal);
					Vals[37]=((Values[37].vt==1)?_T("NULL"):itoa(Values[37].iVal,buf,10));
					Vals[38].Format(_T("%s"),Values[38].bstrVal);
					Vals[39].Format(_T("%s"),Values[39].bstrVal);
					Vals[40]=((Values[40].vt==1)?_T("NULL"):itoa(Values[40].iVal,buf,10));
					Vals[41]=((Values[41].vt==1)?_T("NULL"):gcvt(Values[41].fltVal,20,buf));
					Vals[42]=((Values[42].vt==1)?_T("NULL"):gcvt(Values[42].fltVal,20,buf));
					Vals[43].Format(_T("%s"),Values[43].bstrVal);
					Vals[44].Format(_T("%s"),Values[44].bstrVal);
					Vals[45]=((Values[45].vt==1)?_T("NULL"):gcvt(Values[45].dblVal,20,buf));
					Vals[46]=((Values[46].vt==1)?_T("NULL"):gcvt(Values[46].dblVal,20,buf));
					Vals[47].Format(_T("%s"),Values[47].bstrVal);

					SQL1.Format(_T("SELECT %s, %s,'%s','%s',%s,'%s','%s',%s,'%s',%s,%s,'%s',%s,%s,%s,%s,'%s',%s,%s,%s,'%s',%s,%s,'%s',%s,%s,'%s',"), LastGrpID, LastNtcID,
						(!Vals[2].Compare(_T("(null)"))?"":Vals[2]), (!Vals[3].Compare(_T("(null)"))?"":Vals[3]), Vals[4],
						(!Vals[5].Compare(_T("(null)"))?"":Vals[5]), (!Vals[6].Compare(_T("(null)"))?"":Vals[6]), Vals[7],
						(!Vals[8].Compare(_T("(null)"))?"":Vals[8]), Vals[9], Vals[10], (!Vals[11].Compare(_T("(null)"))?"":Vals[11]),
						Vals[12], Vals[13], Vals[14], Vals[15], (!Vals[16].Compare(_T("(null)"))?"":Vals[16]),
						Vals[17], Vals[18], Vals[19], (!Vals[20].Compare(_T("(null)"))?"":Vals[20]),
						Vals[21], Vals[22], (!Vals[23].Compare(_T("(null)"))?"":Vals[23]), Vals[24],
						Vals[25], (!Vals[26].Compare(_T("(null)"))?"":Vals[26]));
					//SQL2.Format(_T("'%s','%s',%s,'%s','%s','%s','%s','%s','%s','%s',%s,'%s','%s',%s,%s,%s,'%s','%s',%s,%s,'%s',%s "),
					SQL2.Format(_T("'%s','%s',%s,'%s','%s','%s','%s','%s','%s','%s',%s,'%s',%s,%s,%s,'%s','%s',%s,%s,'%s',%s "),
						(!Vals[27].Compare(_T("(null)"))?"":Vals[27]), (!Vals[28].Compare(_T("(null)"))?"":Vals[28]), 
						Vals[29], (!Vals[30].Compare(_T("(null)"))?"":Vals[30]), (!Vals[31].Compare(_T("(null)"))?"":Vals[31]),
						(!Vals[32].Compare(_T("(null)"))?"":Vals[32]), (!Vals[33].Compare(_T("(null)"))?"":Vals[33]),
						(!Vals[34].Compare(_T("(null)"))?"":Vals[34]), (!Vals[35].Compare(_T("(null)"))?"":Vals[35]),
						(!Vals[36].Compare(_T("(null)"))?"":Vals[36]), Vals[37], (!Vals[38].Compare(_T("(null)"))?"":Vals[38]),
						/*(!Vals[39].Compare(_T("(null)"))?"":Vals[39]),*/ Vals[40], Vals[41], Vals[42],
						(!Vals[43].Compare(_T("(null)"))?"":Vals[43]), (!Vals[44].Compare(_T("(null)"))?"":Vals[44]),
						Vals[45],Vals[46], (!Vals[47].Compare(_T("(null)"))?"":Vals[47]), LastAntID);
					SQL1+=SQL2;
					SQL2=_T("INSERT INTO grp (grp_id, ntc_id, emi_rcp, beam_name, page_no, act_code, adm_resp, bdwdth, d_inuse, noise_t, op_agcy, polar_type, ");
					SQL2+=_T("polar_ang, diag_area, diag_spect, prd_valid, remark, tgt_grp_id, pwr_max, bdwdth_aggr, f_trp_band, attch_mux, area_no, observ_cls, ");
					SQL2+=_T("reg_op_fr, reg_op_to, d_upd, st_cur, d_st_cur, wic_no, wic_part, d_wic, d_prot_eff, fdg_reg, fdg_plan, fdg_tex, fdg_observ, ");
					//SQL2+=_T("spl_grp_id, comment, area_name, attch_reg, elev_min, gso_sep, prov, srv_code, freq_min, freq_max, f_no_intfr, AntID) ");
					SQL2+=_T("spl_grp_id, comment, attch_reg, elev_min, gso_sep, prov, srv_code, freq_min, freq_max, f_no_intfr, AntID) ");
					SQL1=SQL2+SQL1;
					DB2.ExecuteSQL(SQL1);			
//emiss
					SQL1=_T("select grp_id, seq_no, design_emi, pep_max, pwr_ds_max, pep_min, pwr_ds_min, c_to_n, pwr_ds_nbw, ");
					SQL2.Format(_T("f_emi_type, attch_pep, attch_mpd, attch_c2n, f_cmp_rec from emiss where grp_id=%ld order by seq_no"),OldGrpID);
					SQL1=SQL1+SQL2;
					rs5.Open(dbOpenSnapshot, SQL1);
					while(!rs5.IsEOF())
					{
						for(i=0;i<14;i++)
							rs5.GetFieldValue(i,Values[i]);
						Vals[1]=((Values[1].vt==1)?_T("NULL"):itoa(Values[1].iVal,buf,10));
						Vals[2].Format(_T("%s"),Values[2].bstrVal);
						Vals[3]=((Values[3].vt==1)?_T("NULL"):gcvt(Values[3].fltVal,20,buf));
						Vals[4]=((Values[4].vt==1)?_T("NULL"):gcvt(Values[4].fltVal,20,buf));
						Vals[5]=((Values[5].vt==1)?_T("NULL"):gcvt(Values[5].fltVal,20,buf));
						Vals[6]=((Values[6].vt==1)?_T("NULL"):gcvt(Values[6].fltVal,20,buf));
						Vals[7]=((Values[7].vt==1)?_T("NULL"):gcvt(Values[7].fltVal,20,buf));
						Vals[8]=((Values[8].vt==1)?_T("NULL"):gcvt(Values[8].fltVal,20,buf));
						Vals[9].Format(_T("%s"),Values[9].bstrVal);
						Vals[10]=((Values[10].vt==1)?_T("NULL"):itoa(Values[10].iVal,buf,10));
						Vals[11]=((Values[11].vt==1)?_T("NULL"):itoa(Values[11].iVal,buf,10));
						Vals[12]=((Values[12].vt==1)?_T("NULL"):itoa(Values[12].iVal,buf,10));
						Vals[13].Format(_T("%s"),Values[13].bstrVal);
						SQL1.Format(_T("select %s,%s,'%s',%s,%s,%s,%s,%s,%s,'%s',%s,%s,%s,'%s' "),LastGrpID,Vals[1],
							(!Vals[2].Compare(_T("(null)"))?"":Vals[2]),Vals[3],Vals[4],Vals[5],
							Vals[6],Vals[7],Vals[8],(!Vals[9].Compare(_T("(null)"))?"":Vals[9]),
							Vals[10],Vals[11],Vals[12],(!Vals[13].Compare(_T("(null)"))?"":Vals[13]));
						SQL1=_T("insert into emiss (grp_id, seq_no, design_emi, pep_max, pwr_ds_max, pep_min, pwr_ds_min, c_to_n, pwr_ds_nbw, f_emi_type, attch_pep, attch_mpd, attch_c2n, f_cmp_rec) ")+SQL1;
						DB2.ExecuteSQL(SQL1);

						rs5.MoveNext();
					}
					rs5.Close();
//provn
					SQL1.Format(_T("select * from provn where grp_id=%ld order by seq_no"),OldGrpID);
					rs5.Open(dbOpenSnapshot, SQL1);
					while(!rs5.IsEOF())
					{
						for(i=0;i<8;i++)
							rs5.GetFieldValue(i,Values[i]);
						Vals[1].Format(_T("%s"),Values[1].bstrVal);
						Vals[2].Format(_T("%s"),Values[2].bstrVal);
						Vals[3]=((Values[3].vt==1)?_T("NULL"):itoa(Values[3].iVal,buf,10));
						Vals[4].Format(_T("%s"),Values[4].bstrVal);
						Vals[5].Format(_T("%s"),Values[5].bstrVal);
						Vals[6].Format(_T("%s"),Values[6].bstrVal);
						Vals[7].Format(_T("%s"),Values[7].bstrVal);
						SQL1.Format(_T("select %s,'%s','%s',%s,'%s','%s','%s','%s' "),LastGrpID,
							(!Vals[1].Compare(_T("(null)"))?"":Vals[1]),(!Vals[2].Compare(_T("(null)"))?"":Vals[2]),
							Vals[3],(!Vals[4].Compare(_T("(null)"))?"":Vals[4]),
							(!Vals[5].Compare(_T("(null)"))?"":Vals[5]),(!Vals[6].Compare(_T("(null)"))?"":Vals[6]),
							(!Vals[7].Compare(_T("(null)"))?"":Vals[7]));
						SQL1=_T("insert into provn (grp_id, coord_prov, agree_st, seq_no, coord_st, adm, ntwk_org, ctry) ")+SQL1;
						DB2.ExecuteSQL(SQL1);

						rs5.MoveNext();
					}
					rs5.Close();
//gpub
					SQL1.Format(_T("select grp_id, seq_no, pub_ref, pub_no, ssn_type, ssn_rev, ssn_rev_no from gpub where grp_id=%ld order by seq_no"),OldGrpID);
					rs5.Open(dbOpenSnapshot, SQL1);
					while(!rs5.IsEOF())
					{
						for(i=0;i<7;i++)
							rs5.GetFieldValue(i,Values[i]);
						Vals[1]=((Values[1].vt==1)?_T("NULL"):itoa(Values[1].iVal,buf,10));
						Vals[2].Format(_T("%s"),Values[2].bstrVal);
						Vals[3]=((Values[3].vt==1)?_T("NULL"):itoa(Values[3].iVal,buf,10));
						Vals[4].Format(_T("%s"),Values[4].bstrVal);
						Vals[5].Format(_T("%s"),Values[5].bstrVal);
						Vals[6]=((Values[6].vt==1)?_T("NULL"):itoa(Values[6].iVal,buf,10));
						SQL1.Format(_T("select %s,%s,'%s',%s,'%s','%s',%s "),LastGrpID,
							Vals[1],(!Vals[2].Compare(_T("(null)"))?"":Vals[2]),Vals[3],
							(!Vals[4].Compare(_T("(null)"))?"":Vals[4]),(!Vals[5].Compare(_T("(null)"))?"":Vals[5]),
							Vals[6]);
						SQL1=_T("insert into gpub (grp_id, seq_no, pub_ref, pub_no, ssn_type, ssn_rev, ssn_rev_no) ")+SQL1;
						DB2.ExecuteSQL(SQL1);

						rs5.MoveNext();
					}
					rs5.Close();
//assgn & freq
					SQL1.Format(_T("select * from assgn where grp_id=%ld order by seq_no"),OldGrpID);
					rs5.Open(dbOpenSnapshot, SQL1);
					while(!rs5.IsEOF())
					{
						for(i=0;i<6;i++)
							rs5.GetFieldValue(i,Values[i]);
						Vals[1]=((Values[1].vt==1)?_T("NULL"):itoa(Values[1].iVal,buf,10));
						Vals[2].Format(_T("%s"),Values[2].bstrVal);
						Vals[3]=((Values[3].vt==1)?_T("NULL"):gcvt(Values[3].dblVal,20,buf));
						Vals[4]=((Values[4].vt==1)?_T("NULL"):gcvt(Values[4].dblVal,20,buf));
						Vals[5].Format(_T("%s"),Values[5].bstrVal);
						SQL1.Format(_T("select %s,%s,'%s',%s,%s,'%s' "),LastGrpID,
							Vals[1],(!Vals[2].Compare(_T("(null)"))?"":Vals[2]),Vals[3],
							Vals[4],(!Vals[5].Compare(_T("(null)"))?"":Vals[5]));
						SQL1=_T("insert into assgn (grp_id, seq_no, freq_sym, freq_assgn, freq_mhz, f_cmp_rec) ")+SQL1;
						DB2.ExecuteSQL(SQL1);


						rs5.MoveNext();
					}
					rs5.Close();
//srv_cls
					SQL1.Format(_T("select * from srv_cls where grp_id=%ld order by seq_no"),OldGrpID);
					rs5.Open(dbOpenSnapshot, SQL1);
					while(!rs5.IsEOF())
					{
						for(i=0;i<4;i++)
							rs5.GetFieldValue(i,Values[i]);
						Vals[2].Format(_T("%s"),Values[2].bstrVal);
						Vals[3].Format(_T("%s"),Values[3].bstrVal);
						SQL1.Format(_T("select %s,%d,'%s','%s' "),LastGrpID,
							Values[1].iVal,(!Vals[2].Compare(_T("(null)"))?"":Vals[2]),
							(!Vals[3].Compare(_T("(null)"))?"":Vals[3]));
						SQL1=_T("insert into srv_cls (grp_id, seq_no, stn_cls, nat_srv) ")+SQL1;
						DB2.ExecuteSQL(SQL1);

						rs5.MoveNext();
					}
					rs5.Close();

					rs4.MoveNext();
				}
				rs4.Close();
				
				rs3.MoveNext();
			}
			rs3.Close();

		rs.MoveNext();
		Recs++;
		if((Recs%10)==0)
			m_ImportProgress.StepIt();
	}
	rs.Close();
	DB1.Close();
	DB2.Close();
	CCmdTarget::EndWaitCursor();
	AfxDaoTerm( );
	if(Total==0)
		MessageBox(_Z("The query returned no records!"),_T("SRS Import"), MB_ICONEXCLAMATION|MB_OK);
	else
	{
		if( Ans==IDYES ) CDialog::OnOK();
	}
	CDialog::OnOK();
}

CString CSRSImport::GetAdmList()
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

void CSRSImport::TranslateDialog(CDialog *pDialog)
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

CString CSRSImport::GetTranslatedString(CString strOriginal, CString Lang)
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
