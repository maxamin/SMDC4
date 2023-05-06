// ESNotice.cpp : implementation file
//

#include "stdafx.h"
#include "administrative.h"
#include "ESNotice.h"
#include <afxdao.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CESNotice dialog


CESNotice::CESNotice(CWnd* pParent /*=NULL*/)
	: CDialog(CESNotice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CESNotice)
	m_Adm = _T("");
	m_Date = COleDateTime::GetCurrentTime();
	m_RefID = _T("");
	m_TgtNtc = _T("");
	//}}AFX_DATA_INIT
}


void CESNotice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CESNotice)
	DDX_Control(pDX, IDC_NTC_SUB, m_Sub);
	DDX_Control(pDX, IDC_NTC_RR, m_RR);
	DDX_Control(pDX, IDC_NTC_PROV, m_Prov);
	DDX_Control(pDX, IDC_NTC_ACTION, m_Action);
	DDX_Text(pDX, IDC_NTC_ADM, m_Adm);
	DDX_DateTimeCtrl(pDX, IDC_NTC_DATE, m_Date);
	DDX_Text(pDX, IDC_NTC_REFID, m_RefID);
	DDX_Text(pDX, IDC_NTC_TGTNTC, m_TgtNtc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CESNotice, CDialog)
	//{{AFX_MSG_MAP(CESNotice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CESNotice message handlers

BOOL CESNotice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	AfxGetModuleState()->m_dwVersion = 0x0601; 
	CString SQL,Label,Val,Unit,Format,Srv,Mask,Adm;
	CDatabase DB;
	CRecordset RS;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("UPDATE rf_ctry, e_stn, notice SET notice.adm = [rf_ctry].[adm] WHERE (((e_stn.ctry)=[rf_ctry].[ctry]) AND ((e_stn.ntc_id)=%ld) AND ((e_stn.ntc_id)=[notice].[ntc_id]))"),m_ntc_id);
	DB.ExecuteSQL(SQL);

	SQL.Format(_T("select * from notice,e_stn where notice.ntc_id=e_stn.ntc_id and notice.ntc_id=%ld"),m_ntc_id);
	RS.Open(CRecordset::snapshot,SQL);

	((CStatic *)GetDlgItem(IDC_NTC_ID_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CEdit *)GetDlgItem(IDC_NTC_ID))->SetWindowText(Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_ID_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_TYPE_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CEdit *)GetDlgItem(IDC_NTC_TYPE))->SetWindowText(Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_TYPE_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_REFID_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CEdit *)GetDlgItem(IDC_NTC_REFID))->SetWindowText(Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_REFID_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_DATE_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CEdit *)GetDlgItem(IDC_NTC_DATE))->SetWindowText(Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_DATE_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_PROV_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CComboBox *)GetDlgItem(IDC_NTC_PROV))->SelectString(0,Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_PROV_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_ACTION_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CComboBox *)GetDlgItem(IDC_NTC_ACTION))->SelectString(0,Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_ACTION_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_ADM_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CEdit *)GetDlgItem(IDC_NTC_ADM))->SetWindowText(Val);
	Label=GetFieldName(&DB,_T("notice"),_T("adm"),_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_ADM_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_SUB_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CComboBox *)GetDlgItem(IDC_NTC_SUB))->SelectString(0,Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_SUB_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_TGTNTC_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	if(Val!=_T("0"))
		((CEdit *)GetDlgItem(IDC_NTC_TGTNTC))->SetWindowText(Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_TGTNTC_lbl))->SetWindowText(Label);

	((CStatic *)GetDlgItem(IDC_NTC_RR_lbl))->GetWindowText(Label);
	RS.GetFieldValue(Label,Val);
	((CComboBox *)GetDlgItem(IDC_NTC_RR))->SelectString(0,Val);
	Label=GetFieldName(&DB,_T("notice"),Label,_T("En"),&Unit,&Format,&Srv,&Mask)+_T(" :");
	((CStatic *)GetDlgItem(IDC_NTC_RR_lbl))->SetWindowText(Label);

	RS.Close();
	DB.Close();
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CESNotice::GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit, CString *Format, CString *Srv, CString *Mask)
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
		RS.GetFieldValue(9,*Srv);
		RS.GetFieldValue(10,*Mask);
		RS.GetFieldValue(11,*Format);
	}
	else
	{
		*Srv=_T("-");
	}
	RS.Close();
	return FieldName;
}

void CESNotice::OnOK() 
{
	CDatabase DB,Orig;
	CString Prov,Action,Occurs,Rsn,SQL,Conn,MDBFile,TempVal;
	int start,end;
	CRecordset RS,RS2,RS3,RS4,RS5;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	RS2.m_pDatabase=&DB;
	RS3.m_pDatabase=&DB;
	RS4.m_pDatabase=&DB;
	RS5.m_pDatabase=&DB;
	UpdateData();
	m_Prov.GetWindowText(Prov);
	m_Action.GetWindowText(Action);
	m_Sub.GetWindowText(Occurs);
	//m_RR.GetWindowText(Rsn);
	if(Prov.Left(1)==_T("1"))   Rsn=_T("N");
	else						Rsn=_T("D");
	SQL.Format(_T("update notice set adm_ref_id='%s', d_adm='%s', prov='%s', tgt_ntc_id=%ld, act_code='%s', adm='%s', ntf_occurs='%s', ntf_rsn='%s' where ntc_id=%ld"),
		m_RefID,m_Date.Format(_T("%Y/%m/%d")),Prov,atol(m_TgtNtc),Action,m_Adm,Occurs,Rsn,m_ntc_id);
	DB.ExecuteSQL(SQL);
	Orig.Open(_T("SRS_Notice"),false,false,_T("ODBC;"),false);
	Conn=Orig.GetConnect();
	start=Conn.Find(_T("DBQ="))+4;
	end=Conn.Find(_T(";"),start);
	Orig.Close();
	CFileDialog FileDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST, _T("MDB Files (*.mdb)|*.mdb||"), NULL );
	FileDlg.DoModal();
	MDBFile=FileDlg.GetPathName();
	if(!MDBFile.IsEmpty())
	{
		if(MDBFile.Right(4).CompareNoCase(_T(".mdb")))
			MDBFile+=_T(".mdb");
		CString Cmd,SQL1,SQL2;
		Cmd.Format(_T("copy \"%s\" \"%s\""),Conn.Mid(start,end-start),MDBFile);
		if(system(Cmd)!=-1)
		{

			CCmdTarget::BeginWaitCursor();
			CString Values[60],Dt;
			CDaoDatabase DB1;
			CDaoRecordset DaoRS;
			DaoRS.m_pDatabase=&DB1;
			DB1.Open(MDBFile);
			SQL2+=_T("SELECT ntc_id, ntc_type, adm_ref_id, d_adm, prov, act_code, adm, ntwk_org, ntf_occurs, tgt_ntc_id, d_upd, f_int_ext, ntf_rsn, st_cur ");
			SQL1.Format(_T("FROM notice where ntc_id=%ld "),m_ntc_id);
			RS.Open(CRecordset::snapshot, SQL2+SQL1);
			{
				CString LastNtcID, LastPattID, LastGrpID, LastAntID;
				long OldGrpID=0;
				for(int i=0;i<14;i++)
					RS.GetFieldValue(i,Values[i]);
				RS.Close();
		//notice
				CString ntf_occ,prov,action;
				m_Sub.GetWindowText(ntf_occ);
				m_Prov.GetWindowText(prov);
				m_Action.GetWindowText(action);
					SQL1.Format(_T("SELECT %ld, '%s', %s,'%s','%s','%s','%s',%s,'%s',%s,'%s','%s','%s','01' "), m_ntc_id, Values[1], 
						(m_RefID.IsEmpty()?_T("NULL"):"'"+m_RefID+"'"), Values[3], prov, action, Values[6], (Values[7].IsEmpty()?_T("NULL"):"'"+Values[7]+"'"), ntf_occ, 
						(m_TgtNtc.IsEmpty()?_T("NULL"):m_TgtNtc),m_Date.Format(_T("%Y/%m/%d")),(Values[11].IsEmpty()?_T("E"):Values[11]),Values[12]/*,Values[13]*/);
					SQL1=_T("INSERT INTO notice (ntc_id, ntc_type, adm_ref_id, d_adm, prov, act_code, adm, ntwk_org, ntf_occurs, tgt_ntc_id, d_upd, f_int_ext, ntf_rsn,st_cur) ")+SQL1;
					DB1.Execute(SQL1);
		//com_el 1
					SQL1.Format(_T("SELECT %ld, '%s', %s,'%s','%s','%s',%s,%s,'%s' "), m_ntc_id, Values[1], 
						(Values[2].IsEmpty()?_T("NULL"):"'"+Values[2]+"'"), Values[4], Values[5], Values[6], (Values[7].IsEmpty()?_T("NULL"):"'"+Values[7]+"'"),  
						(Values[9].IsEmpty()?_T("NULL"):Values[9]),Values[12]);
					SQL1=_T("INSERT INTO com_el (ntc_id, ntc_type, adm_ref_id, prov, act_code, adm, ntwk_org, tgt_ntc_id, ntf_rsn) ")+SQL1;
					DB1.Execute(SQL1);
		//e_stn
					SQL1.Format(_T("select * from e_stn where ntc_id=%ld"),m_ntc_id);
					RS.Open(CRecordset::snapshot, SQL1);
					for(i=0;i<23;i++)
						RS.GetFieldValue(i,Values[i]);
					RS.Close();
					SQL1.Format(_T("SELECT %ld, '%s','%s',%s,'%s',%s,%s,%s,'%s',%s,%s,'%s',%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"), m_ntc_id,
						Values[1], Values[2], (Values[3].IsEmpty()?_T("NULL"):Values[3]),
						Values[4], (Values[5].IsEmpty()?_T("NULL"):Values[5]),(Values[6].IsEmpty()?_T("NULL"):Values[6]),
						(Values[7].IsEmpty()?_T("NULL"):Values[7]), Values[8],(Values[9].IsEmpty()?_T("NULL"):Values[9]),
						(Values[10].IsEmpty()?_T("NULL"):Values[10]),Values[11],
						(Values[12].IsEmpty()?_T("NULL"):Values[12]),(Values[13].IsEmpty()?_T("NULL"):Values[13]),
						(Values[14].IsEmpty()?_T("NULL"):Values[14]),(Values[15].IsEmpty()?_T("NULL"):Values[15]),
						(Values[16].IsEmpty()?_T("NULL"):Values[16]),(Values[17].IsEmpty()?_T("NULL"):Values[17]),
						(Values[18].IsEmpty()?_T("NULL"):Values[18]),(Values[19].IsEmpty()?_T("NULL"):"'"+Values[19]+"'"),
						(Values[20].IsEmpty()?_T("NULL"):Values[20]),(Values[21].IsEmpty()?_T("NULL"):Values[21]),(Values[22].IsEmpty()?_T("NULL"):"'"+Values[22]+"'"));
					SQL2=_T("INSERT INTO e_stn (ntc_id, stn_name, ctry, long_deg, long_ew, long_min, long_sec, lat_deg, lat_ns, lat_min, lat_sec, sat_name, long_nom, attch_hor, elev_min, elev_max, azm_fr, azm_to, ant_alt, f_active, long_dec, lat_dec, f_pfd_se) ");
					SQL1=SQL2+SQL1;
					DB1.Execute(SQL1);
		//com_el 2
					CString Part;
					SQL2="";
					if(!Values[12].IsEmpty())
						SQL2.Format(_T(", long_nom=%s"),Values[12]);
					Part+=SQL2;
					if(!Values[20].IsEmpty())
						SQL2.Format(_T(", long_dec=%s"),Values[20]);
					Part+=SQL2;
					if(!Values[21].IsEmpty())
						SQL2.Format(_T(", lat_dec=%s"),Values[21]);
					Part+=SQL2;
					CTime Today =CTime::GetCurrentTime();
					Dt.Format(_T("%04d/%02d/%02d"),Today.GetYear(),Today.GetMonth(),Today.GetDay());
					SQL1.Format(_T("update com_el set sat_name='%s', stn_name='%s' %s, ctry='%s', d_rcv='%s', st_cur='01' where ntc_id=%ld"), 
						Values[11], Values[1], Part, Values[2],Dt,m_ntc_id);
					DB1.Execute(SQL1);
		//notice 2
					SQL1.Format(_T("update notice set d_st_cur='%s', d_rcv='%s' where ntc_id=%ld"), 
						Dt,Dt,m_ntc_id);
					DB1.Execute(SQL1);
		//hor_elev
					SQL1.Format(_T("select * from hor_elev where ntc_id=%ld"),m_ntc_id);
					RS.Open(CRecordset::snapshot, SQL1);
					while(!RS.IsEOF())
					{
						for(i=0;i<4;i++)
							RS.GetFieldValue(i,Values[i]);
						SQL1.Format(_T("insert into hor_elev (ntc_id,azm,elev_ang,hor_dist) select %ld,%s,%s,%s "), m_ntc_id,
							(Values[1].IsEmpty()?_T("NULL"):Values[1]),(Values[2].IsEmpty()?_T("NULL"):Values[2]),
							(Values[3].IsEmpty()?_T("NULL"):Values[3]));
						DB1.Execute(SQL1);
						RS.MoveNext();
					}
					RS.Close();
		//e_ant_elev
					SQL1.Format(_T("select * from e_ant_elev where ntc_id=%ld"),m_ntc_id);
					RS.Open(CRecordset::snapshot, SQL1);
					while(!RS.IsEOF())
					{
						for(i=0;i<3;i++)
							RS.GetFieldValue(i,Values[i]);
						SQL1.Format(_T("insert into e_ant_elev (ntc_id,azm,elev_ang) select %ld,%s,%s "), m_ntc_id,
							(Values[1].IsEmpty()?_T("NULL"):Values[1]),(Values[2].IsEmpty()?_T("NULL"):Values[2]));
						DB1.Execute(SQL1);
						RS.MoveNext();
					}
					RS.Close();
		//e_ant
					SQL1.Format(_T("select * from e_ant where ntc_id=%ld"),m_ntc_id);
					RS2.Open(CRecordset::snapshot, SQL1);
					while(!RS2.IsEOF())
					{
						for(i=0;i<13;i++)
							RS2.GetFieldValue(i,Values[i]);
						if(atol(Values[9])>0)
						{
							SQL1.Format(_T("select * from ant_type where pattern_id=%s"),Values[9]);
							RS3.Open(CRecordset::snapshot, SQL1);
							for(i=15;i<27;i++)
								RS3.GetFieldValue(i-15,Values[i]);
							RS3.Close();

							COleVariant TempOLE;
							SQL1.Format(_T("select count(pattern_id) from ant_type where pattern_id=%s"),Values[9]);
							DaoRS.Open(dbOpenSnapshot, SQL1);
							DaoRS.GetFieldValue((short)0,TempOLE);
							DaoRS.Close();
							if(TempOLE.lVal==0)
							{
								SQL1.Format(_T("select %s,'%s','%s','%s','%s',%s,%s,%s,%s,%s,'%s','%s' "),Values[9],
									Values[16],Values[17],Values[18],
									(Values[19].IsEmpty()?_T("NULL"):Values[19]),(Values[20].IsEmpty()?_T("NULL"):Values[20]),
									(Values[21].IsEmpty()?_T("NULL"):Values[21]),(Values[22].IsEmpty()?_T("NULL"):Values[22]),
									(Values[23].IsEmpty()?_T("NULL"):Values[23]),(Values[24].IsEmpty()?_T("NULL"):Values[24]),
									Values[25],Values[26]);
								SQL1=_T("insert into ant_type (pattern_id,f_ant_type,f_sub_type,emi_rcp,pattern,coefa,coefb,coefc,coefd,phi1,f_ant_new,apl_name) ")+SQL1;
								DB1.Execute(SQL1);
							}
						}

						SQL1.Format(_T("SELECT %ld, '%s','%s',%s,%s,%s,%s,%s,%s,%s,%s,%s,%s "), m_ntc_id,
							Values[1], Values[2], (Values[3].IsEmpty()?_T("NULL"):"'"+Values[3]+"'"), (Values[4].IsEmpty()?_T("NULL"):"'"+Values[4]+"'"), 
							(Values[5].IsEmpty()?_T("NULL"):Values[5]),
							(Values[6].IsEmpty()?_T("NULL"):Values[6]), (Values[7].IsEmpty()?_T("NULL"):Values[7]),
							(Values[8].IsEmpty()?_T("NULL"):Values[8]),(Values[9].IsEmpty()?_T("NULL"):Values[9]),
							(Values[10].IsEmpty()?_T("NULL"):Values[10]),(Values[11].IsEmpty()?_T("NULL"):Values[11]),
							(Values[12].IsEmpty()?_T("NULL"):Values[12]));
						SQL2=_T("INSERT INTO e_ant (ntc_id, emi_rcp, beam_name, act_code, beam_old, bmwdth, attch_e, attch_e_x, gain, pattern_id, pattern_id_x, ant_diam, attch_crdn) ");
						SQL1=SQL2+SQL1;
						DB1.Execute(SQL1);
		//grp
						SQL1.Format(_T("select * from grp where ntc_id=%ld and emi_rcp='%s' and beam_name='%s'"),m_ntc_id,Values[1],Values[2]);
						RS3.Open(CRecordset::snapshot, SQL1);
						while(!RS3.IsEOF())
						{
							CString EMI_RCP, BeamName, Bdwdth, Freq_min, Freq_max;
							for(i=0;i<48;i++)
								RS3.GetFieldValue(i,Values[i]);
							EMI_RCP=Values[2];
							BeamName=Values[3];
							Bdwdth=Values[7];
							Freq_min=Values[45];
							Freq_max=Values[46];
							OldGrpID=atol(Values[0]);											   // ,%s,%s					  ,%s
							SQL1.Format(_T("SELECT %s, %s,'%s','%s',%s,%s,'%s',%s,'%s',%s,%s,'%s',%s      ,%s,%s,%s,%s,%s,%s   ,%s,%s,%s,%s,"), Values[0], Values[1],
								Values[2], Values[3], (Values[4].IsEmpty()?_T("NULL"):Values[4]),
								(Values[5].IsEmpty()?_T("NULL"):"'"+Values[5]+"'"), Values[6], (Values[7].IsEmpty()?_T("NULL"):Values[7]),
								Values[8], (Values[9].IsEmpty()?_T("NULL"):Values[9]),(Values[10].IsEmpty()?_T("NULL"):Values[10]), 
								Values[11],(Values[12].IsEmpty()?_T("NULL"):Values[12]), /*(Values[13].IsEmpty()?_T("NULL"):Values[13]), 
								(Values[14].IsEmpty()?_T("NULL"):Values[14]),*/ (Values[15].IsEmpty()?_T("NULL"):Values[15]), 
								(Values[16].IsEmpty()?_T("NULL"):"'"+Values[16]+"'"),(Values[17].IsEmpty()?_T("NULL"):Values[17]),
								(Values[18].IsEmpty()?_T("NULL"):Values[18]), (Values[19].IsEmpty()?_T("NULL"):Values[19]), 
								(Values[20].IsEmpty()?_T("NULL"):"'"+Values[20]+"'"),/*(Values[21].IsEmpty()?_T("NULL"):Values[21]),*/
								(Values[22].IsEmpty()?_T("NULL"):Values[22]), (Values[23].IsEmpty()?_T("NULL"):"'"+Values[23]+"'"), (Values[24].IsEmpty()?_T("NULL"):Values[24]),
								(Values[25].IsEmpty()?_T("NULL"):Values[25]));
							//					,%s
							//SQL2.Format(_T("'%s'   ,%s,%s,'%s','%s',%s,%s,'N' "),
							SQL2.Format(_T("%s,%s,%s,%s,%s,%s,'N' "),
								/*(Values[39].IsEmpty()?_T(" "):Values[39])*//*, (Values[40].IsEmpty()?_T("NULL"):Values[40]),*/ (Values[41].IsEmpty()?_T("NULL"):Values[41]), 
								(Values[42].IsEmpty()?_T("NULL"):Values[42]),(Values[43].IsEmpty()?_T("NULL"):"'"+Values[43]+"'"), (Values[44].IsEmpty()?_T("NULL"):"'"+Values[44]+"'"),
								(Values[45].IsEmpty()?_T("NULL"):Values[45]), (Values[46].IsEmpty()?_T("NULL"):Values[46]));
							SQL1+=SQL2;
							SQL2=_T("INSERT INTO grp (grp_id, ntc_id, emi_rcp, beam_name, page_no, act_code, adm_resp, bdwdth, d_inuse, noise_t, op_agcy, polar_type, ");
							SQL2+=_T("polar_ang, prd_valid, remark, tgt_grp_id, pwr_max, bdwdth_aggr, f_trp_band, area_no, observ_cls, ");
							SQL2+=_T("reg_op_fr, reg_op_to, elev_min, gso_sep, prov, ");
							//SQL2+=_T("reg_op_fr, reg_op_to,area_name, elev_min, gso_sep, prov, ");
							/*SQL2+=_T("polar_ang, diag_area, diag_spect, prd_valid, remark, tgt_grp_id, pwr_max, bdwdth_aggr, f_trp_band, attch_mux, area_no, observ_cls, ");
							SQL2+=_T("reg_op_fr, reg_op_to,area_name, attch_reg, elev_min, gso_sep, prov, ");*/
							SQL2+=_T(" srv_code, freq_min, freq_max, f_no_intfr) ");
							SQL1=SQL2+SQL1;
							DB1.Execute(SQL1);			
		//emiss
							SQL1.Format(_T("select * from emiss where grp_id=%ld order by seq_no"),OldGrpID);
							RS4.Open(CRecordset::snapshot, SQL1);
							while(!RS4.IsEOF())
							{
								for(i=0;i<14;i++)
									RS4.GetFieldValue(i,Values[i]);
								SQL1.Format(_T("select %ld,%s,'%s',%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s "),OldGrpID,
									(Values[1].IsEmpty()?_T("NULL"):Values[1]),Values[2],
									(Values[3].IsEmpty()?_T("NULL"):Values[3]),(Values[4].IsEmpty()?_T("NULL"):Values[4]),
									(Values[5].IsEmpty()?_T("NULL"):Values[5]),(Values[6].IsEmpty()?_T("NULL"):Values[6]),
									(Values[7].IsEmpty()?_T("NULL"):Values[7]),(Values[8].IsEmpty()?_T("NULL"):Values[8]),
									(Values[9].IsEmpty()?_T("NULL"):"'"+Values[9]+"'"),(Values[10].IsEmpty()?_T("NULL"):Values[10]),
									(Values[11].IsEmpty()?_T("NULL"):Values[11]),(Values[12].IsEmpty()?_T("NULL"):Values[12]),(Values[13].IsEmpty()?_T("NULL"):"'"+Values[13]+"'"));
								SQL1=_T("insert into emiss (grp_id, seq_no, design_emi, pep_max, pwr_ds_max, pep_min, pwr_ds_min, c_to_n, pwr_ds_nbw, f_emi_type, attch_pep, attch_mpd, attch_c2n, f_cmp_rec) ")+SQL1;
								DB1.Execute(SQL1);

								RS4.MoveNext();
							}
							RS4.Close();
		//provn
							SQL1.Format(_T("select * from provn where grp_id=%ld order by seq_no"),OldGrpID);
							RS4.Open(CRecordset::snapshot, SQL1);
							while(!RS4.IsEOF())
							{
								for(i=0;i<8;i++)
									RS4.GetFieldValue(i,Values[i]);
								SQL1.Format(_T("select %ld,'%s','%s',%s,%s,%s,%s,%s "),OldGrpID,
									Values[1],Values[2],(Values[3].IsEmpty()?_T("NULL"):Values[3]),
									(Values[4].IsEmpty()?_T("NULL"):"'"+Values[4]+"'"),(Values[5].IsEmpty()?_T("NULL"):"'"+Values[5]+"'"),(Values[6].IsEmpty()?_T("NULL"):"'"+Values[6]+"'"),
									(Values[7].IsEmpty()?_T("NULL"):"'"+Values[7]+"'"));
								SQL1=_T("insert into provn (grp_id, coord_prov, agree_st, seq_no, coord_st, adm, ntwk_org, ctry) ")+SQL1;
								DB1.Execute(SQL1);

								RS4.MoveNext();
							}
							RS4.Close();
		//gpub
							SQL1.Format(_T("select * from gpub where grp_id=%ld order by seq_no"),OldGrpID);
							RS4.Open(CRecordset::snapshot, SQL1);
							while(!RS4.IsEOF())
							{
								for(i=0;i<7;i++)
									RS4.GetFieldValue(i,Values[i]);
								SQL1.Format(_T("select %ld,%s,'%s',%s,'%s',%s,%s "),OldGrpID,
									(Values[1].IsEmpty()?_T("NULL"):Values[1]),Values[2],(Values[3].IsEmpty()?_T("NULL"):Values[3]),
									Values[4],(Values[5].IsEmpty()?_T("NULL"):"'"+Values[5]+"'"),(Values[6].IsEmpty()?_T("NULL"):Values[6]));
								SQL1=_T("insert into gpub (grp_id, seq_no, pub_ref, pub_no, ssn_type, ssn_rev, ssn_rev_no) ")+SQL1;
//								AfxMessageBox(SQL1);
								DB1.Execute(SQL1);

								RS4.MoveNext();
							}
							RS4.Close();
		//assgn & freq
							SQL1.Format(_T("select * from assgn where grp_id=%ld order by seq_no"),OldGrpID);
							RS4.Open(CRecordset::snapshot, SQL1);
							while(!RS4.IsEOF())
							{
								for(i=0;i<6;i++)
									RS4.GetFieldValue(i,Values[i]);
								SQL1.Format(_T("select %ld,%s,'%s',%s,%s,%s "),OldGrpID,
									(Values[1].IsEmpty()?_T("NULL"):Values[1]),Values[2],(Values[3].IsEmpty()?_T("NULL"):Values[3]),
									(Values[4].IsEmpty()?_T("NULL"):Values[4]),(Values[5].IsEmpty()?_T("NULL"):"'"+Values[5]+"'"));
								SQL1=_T("insert into assgn (grp_id, seq_no, freq_sym, freq_assgn, freq_mhz, f_cmp_rec) ")+SQL1;
								DB1.Execute(SQL1);


								SQL1.Format(_T("select %ld,'%s','%s',%ld,%s,'%s',%s,%s,%s,%s,%s,'S' "),m_ntc_id, EMI_RCP, BeamName, OldGrpID,
									(Values[1].IsEmpty()?_T("NULL"):Values[1]),Values[2],(Values[3].IsEmpty()?_T("NULL"):Values[3]),
									(Values[4].IsEmpty()?_T("NULL"):Values[4]),Freq_min, Freq_max, Bdwdth);
								SQL1=_T("insert into freq (ntc_id, emi_rcp, beam_name, grp_id, seq_no, freq_sym, freq_assgn, freq_mhz, freq_min, freq_max, bdwdth, ntc_type) ")+SQL1;
								DB1.Execute(SQL1);


								RS4.MoveNext();
							}
							RS4.Close();
		//srv_cls
							SQL1.Format(_T("select * from srv_cls where grp_id=%ld order by seq_no"),OldGrpID);
							RS4.Open(CRecordset::snapshot, SQL1);
							while(!RS4.IsEOF())
							{
								for(i=0;i<4;i++)
									RS4.GetFieldValue(i,Values[i]);
								SQL1.Format(_T("select %ld,%s,'%s','%s' "),OldGrpID,
									(Values[1].IsEmpty()?_T("NULL"):Values[1]),Values[2],Values[3]);
								SQL1=_T("insert into srv_cls (grp_id, seq_no, stn_cls, nat_srv) ")+SQL1;
								DB1.Execute(SQL1);

								RS4.MoveNext();
							}
							RS4.Close();

							RS3.MoveNext();
						}
						RS3.Close();
						
						RS2.MoveNext();
					}
					RS2.Close();

			//	rs.MoveNext();
			//	Recs++;
			}
			DB1.Close();
			CCmdTarget::EndWaitCursor();

		}
		else
			AfxMessageBox(_Z("System failed to create notice file! Please try again."));
	}
	DB.Close();
	CDialog::OnOK();
	AfxDaoTerm( );
}
