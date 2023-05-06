// GrpDetails.cpp : implementation file
//

#include "stdafx.h"
#include "administrative.h"
#include "GrpDetails.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrpDetails dialog


CGrpDetails::CGrpDetails(CWnd* pParent /*=NULL*/)
	: CDialog(CGrpDetails::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrpDetails)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGrpDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrpDetails)
	DDX_Control(pDX, IDC_SAVE, m_SaveGrid);
	DDX_Control(pDX, IDC_DELREC, m_DelRec);
	DDX_Control(pDX, IDC_ADDREC, m_AddRec);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrpDetails, CDialog)
	//{{AFX_MSG_MAP(CGrpDetails)
	ON_BN_CLICKED(IDC_ADDREC, OnAddrec)
	ON_BN_CLICKED(IDC_DELREC, OnDelrec)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrpDetails message handlers

BOOL CGrpDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_DataSaved=false;
	m_AddRec.LoadBitmaps(IDB_PLUS1,IDB_PLUS2,IDB_PLUS1,IDB_PLUS3);
	m_DelRec.LoadBitmaps(IDB_MINUS1,IDB_MINUS2,IDB_MINUS1,IDB_MINUS3);
	m_SaveGrid.LoadBitmaps(IDB_SAVE1,IDB_SAVE2,IDB_SAVE1,IDB_SAVE3);
	m_DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	m_RS.m_pDatabase=&m_DB;
	m_Grid.SetRowHeight(0,900);

	if(m_Type==1)	//Emissions
	{
		CString SQL;
		if(m_BeamType==1)
			SQL.Format(_T("Select design_emi, pep_max, pwr_ds_max, pep_min, pwr_ds_min from emiss where grp_id=%ld order by seq_no"),m_Grp_id);
		else
			SQL.Format(_T("Select design_emi, c_to_n from emiss where grp_id=%ld order by seq_no"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Emissions"));
	}
	if(m_Type==2)	//Frequencies
	{
		CString SQL;
		SQL.Format(_T("Select freq_mhz,FreqFee from assgn where grp_id=%ld order by seq_no"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Frequencies"));
	}
	if(m_Type==3)	//Special Section
	{
		CString SQL;
		SQL.Format(_T("Select pub_ref, pub_no, ssn_rev, ssn_rev_no from gpub where grp_id=%ld order by seq_no"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Special Section"));
	}
	if(m_Type==4)	//Coordination
	{
		CString SQL;
		SQL.Format(_T("Select coord_prov, agree_st, adm from provn where grp_id=%ld order by coord_prov,seq_no"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Coordination"));
	}
	if(m_Type==5)	//Class of station
	{
		CString SQL;
		SQL.Format(_T("Select stn_cls, nat_srv from srv_cls where grp_id=%ld order by seq_no"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Class of station/Nature of service"));
	}
	if(m_Type==6)	//Elevation angle
	{
		CString SQL;
		SQL.Format(_T("Select azm, elev_ang, hor_dist from hor_elev where ntc_id=%ld order by azm"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Horizon Elevation"));
	}
	if(m_Type==7)	//Minimum Elev. Angles
	{
		CString SQL;
		SQL.Format(_T("Select azm, elev_ang from e_ant_elev where ntc_id=%ld order by azm"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Minimum Elevation Angles"));
	}
	if(m_Type==8)	//Antenna pattern
	{
		CString SQL;
		SQL.Format(_T("Select OffAng,AntGain from ESAntPatt where AntID=%ld order by OffAng"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Antenna Pattern"));
	}
	if(m_Type==9)	//Terresterial coord.
	{
		CString SQL;
		SQL.Format(_T("Select coord_prov, agree_st, adm from Coord where freq_id=%ld order by coord_prov"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Coordination"));
	}
	if(m_Type==10)	//Contour
	{
		CString SQL;
		SQL.Format(_T("Select long_deg, long_min, long_sec, long_ew, lat_deg, lat_min, lat_sec, lat_ns from rrc_contour_pt where contourkey=%ld order by test_pt"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,3);
		SetWindowText(_Z("GE06 Contour"));
	}
	if(m_Type==11)	//Service Area
	{
		CString SQL;
		SQL.Format(_T("Select SiteName, GeoLon, GeoLat, UFS as [Emed/UFS], Em from CSArea where IDst=%ld"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,5);
		SetWindowText(_Z("Service Area"));
	}
	if(m_Type==12)	//Allotment coord.
	{
		CString SQL;
		SQL.Format(_T("Select coord_prov, agree_st, adm from rrc_allot_coord where allotkey=%ld order by coord_prov"),m_Grp_id);
		m_RS.Open(CRecordset::dynaset,SQL);
		m_Grid.SetCols(0,m_RS.GetODBCFieldCount()+1);
		SetWindowText(_Z("Coordination"));
	}

	for(int i=0;m_Type!=10 && m_Type!=11 && i<m_RS.GetODBCFieldCount();i++)
	{
		CODBCFieldInfo Fld;
		CString Unit, Format, Srv, Mask, NewName;
		m_RS.GetODBCFieldInfo(i,Fld);
		if(m_Type==1)
			NewName=GetFieldName(&m_DB, _T("Emiss"), Fld.m_strName, m_Lang, &Unit, &Format, &Srv, &Mask);
		if(m_Type==2)
			NewName=GetFieldName(&m_DB, _T("Assgn"), Fld.m_strName, m_Lang, &Unit, &Format, &Srv, &Mask);
		if(m_Type==3)
			NewName=GetFieldName(&m_DB, _T("gpub"), Fld.m_strName, m_Lang, &Unit, &Format, &Srv, &Mask);
		if(m_Type==4 || m_Type==9 ||  m_Type==12)
			NewName=GetFieldName(&m_DB, _T("Provn"), Fld.m_strName, m_Lang, &Unit, &Format, &Srv, &Mask);
		if(m_Type==5)
			NewName=GetFieldName(&m_DB, _T("Srv_cls"), Fld.m_strName, m_Lang, &Unit, &Format, &Srv, &Mask);
		if(m_Type==6)
			NewName=GetFieldName(&m_DB, _T("Hor_elev"), Fld.m_strName, m_Lang, &Unit, &Format, &Srv, &Mask);
		if(m_Type==7)
			NewName=GetFieldName(&m_DB, _T("Ant_elev"), Fld.m_strName, m_Lang, &Unit, &Format, &Srv, &Mask);
		if(m_Type==8)
			NewName=GetFieldName(&m_DB, _T("ESAntPatt"), Fld.m_strName, m_Lang, &Unit, &Format, &Srv, &Mask);
		m_Grid.SetTextMatrix(0,i+1,NewName);
	}
	if(m_Type==1)
	{
		m_Grid.SetRow(0);
		m_Grid.SetCol(1);
		m_Grid.SetCellFontBold(true);
		if(m_Grid.GetCols(0)>3)
		{
			m_Grid.SetCol(2);
			m_Grid.SetCellFontBold(true);
			m_Grid.SetCol(3);
			m_Grid.SetCellFontBold(true);
		}
	}
	if(m_Type==2)
	{
		m_Grid.SetRow(0);
		m_Grid.SetCol(1);
		m_Grid.SetCellFontBold(true);
	}
	if(m_Type==3)
	{
		m_Grid.SetRow(0);
		m_Grid.SetCol(1);
		m_Grid.SetCellFontBold(true);
		m_Grid.SetCol(2);
		m_Grid.SetCellFontBold(true);
	}
	if(m_Type==4 || m_Type==9)
	{
		m_Grid.SetRow(0);
		m_Grid.SetCol(1);
		m_Grid.SetCellFontBold(true);
		m_Grid.SetCol(2);
		m_Grid.SetCellFontBold(true);
		m_Grid.SetCol(3);
		m_Grid.SetCellFontBold(true);
	}
	if(m_Type==5)
	{
		m_Grid.SetRow(0);
		m_Grid.SetCol(1);
		m_Grid.SetCellFontBold(true);
		m_Grid.SetCol(2);
		m_Grid.SetCellFontBold(true);
	}
	if(m_Type==10 || m_Type==11)
	{
		m_Grid.SetRow(0);
		m_Grid.SetTextMatrix(0,1,_Z("Longitude\n\n+DDDMMSS.SS"));
		m_Grid.SetCol(1);
		m_Grid.SetCellFontBold(true);
		m_Grid.SetCellAlignment(4);
		m_Grid.SetColWidth(1,0,1500);
		m_Grid.SetTextMatrix(0,2,_Z("Latitude\n\n+DDMMSS.SS"));
		m_Grid.SetCol(2);
		m_Grid.SetCellFontBold(true);
		m_Grid.SetCellAlignment(4);
		m_Grid.SetColWidth(2,0,1500);
	}
	if(m_Type==11)
	{
		m_Grid.SetTextMatrix(0,3,_Z("Emed/UFS"));
		m_Grid.SetTextMatrix(0,4,_Z("Em"));
	}
	int j=1;
	while(true)
	{
		if(m_RS.IsEOF()) break;
		if(m_Type==10)
		{
			CString dg, mn, sc, nswe, res;
			m_RS.GetFieldValue((int)0,dg);
			m_RS.GetFieldValue(1,mn);
			m_RS.GetFieldValue(2,sc);
			m_RS.GetFieldValue(3,nswe);
			res.Format(_T("%c%03d%02d%05.2f"),(nswe.CompareNoCase(_T("W"))?'+':'-'), atoi((LPCTSTR)dg),atoi((LPCTSTR)mn),atof((LPCTSTR)sc));
			m_Grid.SetTextMatrix(j,1,res);
			m_RS.GetFieldValue(4,dg);
			m_RS.GetFieldValue(5,mn);
			m_RS.GetFieldValue(6,sc);
			m_RS.GetFieldValue(7,nswe);
			res.Format(_T("%c%02d%02d%05.2f"),(nswe.CompareNoCase(_T("S"))?'+':'-'), atoi((LPCTSTR)dg),atoi((LPCTSTR)mn),atof((LPCTSTR)sc));
			m_Grid.SetTextMatrix(j,2,res);
		}
		else if(m_Type==11)
		{
			CString Temp;
			m_RS.GetFieldValue((int)0,m_StName);
			m_RS.GetFieldValue(2,Temp);
			double lat=atof(Temp);
			int d=(int)lat,
			m=abs((int)((fabs(lat)-(double)abs(d))*60.));
			double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;				m++;
			}
			if(m>59.)
			{
				m=0;				d++;
			}
			Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
			m_Grid.SetTextMatrix(j,2,Temp);

			m_RS.GetFieldValue(1,Temp);
			double lon=atof(Temp);
			d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;				m++;
			}
			if(m>59.)
			{
				m=0;				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			m_Grid.SetTextMatrix(j,1,Temp);
			for(int i=3;i<5;i++)
			{
				CString Val;
				m_RS.GetFieldValue(i,Val);
				m_Grid.SetTextMatrix(j,i,Val);
			}
		}
		else
		{
			for(int i=0;i<m_RS.GetODBCFieldCount();i++)
			{
				CString Val;
				m_RS.GetFieldValue(i,Val);
				m_Grid.SetTextMatrix(j,i+1,Val);
			}
		}
		j++;
		m_RS.MoveNext();
		m_Grid.SetRows(j+1);
	}
//	RS.Close();
	if(j>1) m_Grid.SetRows(m_Grid.GetRows()-1);

	m_Grid.SetRow(1);
	m_Grid.SetRowSel(1);
	m_Grid.SetCol(1);
	m_Grid.SetColSel(1);
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CGrpDetails::GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit, CString *Format, CString *Srv, CString *Mask)
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
		RS.GetFieldValue(5,*Unit);
		RS.GetFieldValue(6,*Srv);
		RS.GetFieldValue(7,*Mask);
		RS.GetFieldValue(8,*Format);
	}
	else
	{
		*Srv=_T("-");
	}
	RS.Close();
	return FieldName;
}

void CGrpDetails::OnAddrec() 
{
	m_Grid.SetRows(m_Grid.GetRows()+1);	
}

void CGrpDetails::OnDelrec() 
{
	if(m_Grid.GetRows()>2)
		m_Grid.SetRows(m_Grid.GetRows()-1);		
}

bool CGrpDetails::OnSave() 
{
	CString SQL,Mess,Part;
	int i;
	bool res=false;
	switch(m_Type)
	{
	case 1:
			for(i=1;i<m_Grid.GetRows();i++)
			{
				if(m_Grid.GetTextMatrix(i,1).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,1),i);
					Mess+=Part;
				}
				if(m_Grid.GetCols(0)>3)
				{
					if(m_Grid.GetTextMatrix(i,2).IsEmpty())
					{
						Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,2),i);
						Mess+=Part;
					}
					if(m_Grid.GetTextMatrix(i,3).IsEmpty())
					{
						Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,3),i);
						Mess+=Part;
					}
				}
			}
			if(Mess.IsEmpty())
			{
				SQL.Format(_T("delete * from emiss where grp_id=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					if(m_BeamType==1)
					{
						SQL.Format(_T("insert into emiss (grp_id,seq_no,design_emi, pep_max, pwr_ds_max, pep_min, pwr_ds_min) select %ld,%d,'%s',%s,%s,%s,%s "),
							m_Grp_id,i,m_Grid.GetTextMatrix(i,1),m_Grid.GetTextMatrix(i,2),m_Grid.GetTextMatrix(i,3),
							(m_Grid.GetTextMatrix(i,4).IsEmpty()?_T("NULL"):m_Grid.GetTextMatrix(i,4)),
							(m_Grid.GetTextMatrix(i,5).IsEmpty()?_T("NULL"):m_Grid.GetTextMatrix(i,5)));
					}
					else
					{
						SQL.Format(_T("insert into emiss (grp_id,seq_no,design_emi, c_to_n) select %ld,%d,'%s',%s "),
							m_Grp_id,i,m_Grid.GetTextMatrix(i,1),(m_Grid.GetTextMatrix(i,2).IsEmpty()?_T("NULL"):m_Grid.GetTextMatrix(i,2)));
					}
					m_DB.ExecuteSQL(SQL);
				}
				res=true;
			}
			else
			{
				Mess.Delete(Mess.GetLength()-1);
				AfxMessageBox(Mess);
			}
			
			break;
	case 2:
			for(i=1;i<m_Grid.GetRows();i++)
				if(m_Grid.GetTextMatrix(i,1).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,1),i);
					Mess+=Part;
				}
			if(Mess.IsEmpty())
			{
				double fmin=1e+70,fmax=-1000000000.;
				SQL.Format(_T("delete * from assgn where grp_id=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					double freq=atof(m_Grid.GetTextMatrix(i,1));
					double freq2=freq;
					long FreqFee=atol(m_Grid.GetTextMatrix(i,2));
					CString FreqSym=_T("M");
					if(freq>1000.)
					{
						FreqSym=_T("G");
						freq2=freq/1000.;
					}
					if(freq<1. && freq>=0.001)
					{
						FreqSym=_T("k");
						freq2=freq*1000.;
					}
					if(freq<0.001)
					{
						FreqSym=_T("H");
						freq2=freq*1000000.;
					}
					SQL.Format(_T("insert into assgn (grp_id,seq_no,freq_mhz, freq_sym, freq_assgn,FreqFee) select %ld,%d,%lf,'%s',%lf,%ld "),
						m_Grp_id,i,freq,FreqSym,freq2,FreqFee);
					m_DB.ExecuteSQL(SQL);
					if(freq<fmin)  fmin=freq;
					if(freq>fmax)  fmax=freq;
				}
				CRecordset RS;
				CString Value;
				RS.m_pDatabase=&m_DB;
				SQL.Format(_T("select bdwdth from grp where grp_id=%ld"),m_Grp_id);
				RS.Open(CRecordset::snapshot,SQL);
				RS.GetFieldValue((short)0,Value);
				SQL.Format(_T("update grp set freq_min=%lf, freq_max=%lf where grp_id=%ld"),((fmin*1000.)-atof(Value)/2.)/1000., ((fmax*1000.)+atof(Value)/2.)/1000., m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				res=true;
			}
			else
			{
				Mess.Delete(Mess.GetLength()-1);
				AfxMessageBox(Mess);
			}

			break;
	case 3:
			for(i=1;i<m_Grid.GetRows();i++)
			{
				if(m_Grid.GetTextMatrix(i,1).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,1),i);
					Mess+=Part;
				}
				if(m_Grid.GetTextMatrix(i,2).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,2),i);
					Mess+=Part;
				}
			}
			if(Mess.IsEmpty())
			{
				SQL.Format(_T("delete * from gpub where grp_id=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					SQL.Format(_T("insert into gpub (grp_id,seq_no,pub_ref, pub_no,ssn_type, ssn_rev,ssn_rev_no) select %ld,%d,'%s',%s,'N','%s',%s "),
						m_Grp_id,i,m_Grid.GetTextMatrix(i,1),(m_Grid.GetTextMatrix(i,2).IsEmpty()?_T("NULL"):m_Grid.GetTextMatrix(i,2)),
						m_Grid.GetTextMatrix(i,3),(m_Grid.GetTextMatrix(i,4).IsEmpty()?_T("NULL"):m_Grid.GetTextMatrix(i,4)));
					m_DB.ExecuteSQL(SQL);
				}
				res=true;
			}
			else
			{
				Mess.Delete(Mess.GetLength()-1);
				AfxMessageBox(Mess);
			}

			break;
	case 4:
			for(i=1;i<m_Grid.GetRows();i++)
			{
				if(m_Grid.GetTextMatrix(i,1).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,1),i);
					Mess+=Part;
				}
				if(m_Grid.GetTextMatrix(i,2).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,2),i);
					Mess+=Part;
				}
				if(m_Grid.GetTextMatrix(i,3).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,3),i);
					Mess+=Part;
				}
			}
			if(Mess.IsEmpty())
			{
				SQL.Format(_T("delete * from provn where grp_id=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					SQL.Format(_T("insert into provn (grp_id,seq_no,coord_prov, agree_st, adm) select %ld,%d,'%s','%s','%s' "),
						m_Grp_id,i,m_Grid.GetTextMatrix(i,1),m_Grid.GetTextMatrix(i,2),m_Grid.GetTextMatrix(i,3));
					m_DB.ExecuteSQL(SQL);
				}
				res=true;
			}
			else
			{
				Mess.Delete(Mess.GetLength()-1);
				AfxMessageBox(Mess);
			}
			break;
	case 5:
			for(i=1;i<m_Grid.GetRows();i++)
			{
				if(m_Grid.GetTextMatrix(i,1).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,1),i);
					Mess+=Part;
				}
				if(m_Grid.GetTextMatrix(i,2).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,2),i);
					Mess+=Part;
				}
			}
			if(Mess.IsEmpty())
			{
				SQL.Format(_T("delete * from srv_cls where grp_id=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					SQL.Format(_T("insert into srv_cls (grp_id,seq_no,stn_cls, nat_srv) select %ld,%d,'%s','%s' "),
						m_Grp_id,i,m_Grid.GetTextMatrix(i,1),m_Grid.GetTextMatrix(i,2));
					m_DB.ExecuteSQL(SQL);
				}
				res=true;
			}
			else
			{
				Mess.Delete(Mess.GetLength()-1);
				AfxMessageBox(Mess);
			}
			break;
	case 6:
			SQL.Format(_T("delete * from hor_elev where ntc_id=%ld "),m_Grp_id);
			m_DB.ExecuteSQL(SQL);
			for(i=1;i<m_Grid.GetRows();i++)
			{
				double azm=atof(m_Grid.GetTextMatrix(i,1)),elev=atof(m_Grid.GetTextMatrix(i,2)),dist=atof(m_Grid.GetTextMatrix(i,3));
				SQL.Format(_T("insert into hor_elev (ntc_id,azm,elev_ang,hor_dist) select %ld,%lf,%lf,%lf "),
					m_Grp_id,azm,elev,dist);
				m_DB.ExecuteSQL(SQL);
			}
				res=true;
			break;
	case 7:
			SQL.Format(_T("delete * from e_ant_elev where ntc_id=%ld "),m_Grp_id);
			m_DB.ExecuteSQL(SQL);
			for(i=1;i<m_Grid.GetRows();i++)
			{
				double azm=atof(m_Grid.GetTextMatrix(i,1)),elev=atof(m_Grid.GetTextMatrix(i,2));
				SQL.Format(_T("insert into e_ant_elev (ntc_id,azm,elev_ang) select %ld,%lf,%lf "),
					m_Grp_id,azm,elev);
				m_DB.ExecuteSQL(SQL);
			}
				res=true;
			break;
	case 8:
			SQL.Format(_T("delete * from ESAntPatt where AntID=%ld "),m_Grp_id);
			m_DB.ExecuteSQL(SQL);
			for(i=1;i<m_Grid.GetRows();i++)
			{
				double OffAngle=atof(m_Grid.GetTextMatrix(i,1)),Gain=atof(m_Grid.GetTextMatrix(i,2));
				SQL.Format(_T("insert into ESAntPatt (AntID,OffAng,AntGain) select %ld,%lf,%lf "),
					m_Grp_id,OffAngle,Gain);
				if(OffAngle<=180 && OffAngle>=0)
					m_DB.ExecuteSQL(SQL);
			}
			m_DataSaved=true;
				res=true;
			break;
	case 9:
			for(i=1;i<m_Grid.GetRows();i++)
			{
				if(m_Grid.GetTextMatrix(i,1).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,1),i);
					Mess+=Part;
				}
				if(m_Grid.GetTextMatrix(i,2).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,2),i);
					Mess+=Part;
				}
				if(m_Grid.GetTextMatrix(i,3).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,3),i);
					Mess+=Part;
				}
			}
			if(Mess.IsEmpty())
			{
				SQL.Format(_T("delete * from Coord where freq_id=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					SQL.Format(_T("insert into Coord (freq_id,coord_prov, agree_st, adm) select %ld,'%s','%s','%s' "),
						m_Grp_id,m_Grid.GetTextMatrix(i,1),m_Grid.GetTextMatrix(i,2),m_Grid.GetTextMatrix(i,3));
					m_DB.ExecuteSQL(SQL);
				}
				res=true;
			}
			else
			{
				Mess.Delete(Mess.GetLength()-1);
				AfxMessageBox(Mess);
			}
			break;
	case 10:
		{
			bool FormatOK=true;
			for(i=1;i<m_Grid.GetRows();i++)
			{
				CString Lon=m_Grid.GetTextMatrix(i,1),Lat=m_Grid.GetTextMatrix(i,2);
				if(Lon.IsEmpty())
				{
					Part.Format(_Z("Longitude in row %d is mandatory,"),i);
					Mess+=Part;
				}
				if(Lat.IsEmpty())
				{
					Part.Format(_Z("Latitude in row %d is mandatory,"),i);
					Mess+=Part;
				}
				if((Lon.Left(1).Compare(_T("+")) && Lon.Left(1).Compare(_T("-"))) ||
					(Lat.Left(1).Compare(_T("+")) && Lat.Left(1).Compare(_T("-"))))
					FormatOK=false;
				if(Lon.GetLength()<11 || Lat.GetLength()<10)
					FormatOK=false;
			}
			if(Mess.IsEmpty() && FormatOK)
			{
				SQL.Format(_T("delete * from rrc_contour_pt where contourkey=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					CString Lon=m_Grid.GetTextMatrix(i,1), Lat=m_Grid.GetTextMatrix(i,2);
					SQL.Format(_T("insert into rrc_contour_pt (contourkey,test_pt,long_deg,long_min,long_sec,long_ew,lat_deg,lat_min,lat_sec,lat_ns) select %ld,%d,%s,%s,%s,'%s',%s,%s,%s,'%s' "),
						m_Grp_id,i-1,Lon.Mid(1,3),Lon.Mid(4,2),Lon.Mid(6),Lon.Left(1).Compare(_T("-"))?_T("E"):_T("W"),
									 Lat.Mid(1,2),Lat.Mid(3,2),Lat.Mid(5),Lat.Left(1).Compare(_T("-"))?_T("N"):_T("S"));
					m_DB.ExecuteSQL(SQL);
				}
				res=true;
			}
			else
			{
				if(!FormatOK)
					AfxMessageBox(_Z("Coordinates in some rows are not in correct format!"));
				if(!Mess.IsEmpty())
				{
					Mess.Delete(Mess.GetLength()-1);
					AfxMessageBox(Mess);
				}
			}
			break;
		}
	case 11:
		{
			bool FormatOK=true;
			for(i=1;i<m_Grid.GetRows();i++)
			{
				CString Lon=m_Grid.GetTextMatrix(i,1),Lat=m_Grid.GetTextMatrix(i,2);
				if(Lon.IsEmpty())
				{
					Part.Format(_Z("Longitude in row %d is mandatory,"),i);
					Mess+=Part;
				}
				if(Lat.IsEmpty())
				{
					Part.Format(_Z("Latitude in row %d is mandatory,"),i);
					Mess+=Part;
				}
				if((Lon.Left(1).Compare(_T("+")) && Lon.Left(1).Compare(_T("-"))) ||
					(Lat.Left(1).Compare(_T("+")) && Lat.Left(1).Compare(_T("-"))))
					FormatOK=false;
				if(Lon.GetLength()<11 || Lat.GetLength()<10)
					FormatOK=false;
			}
			if(Mess.IsEmpty() && FormatOK)
			{
				SQL.Format(_T("delete * from CSArea where IDst=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					double sgn;
					CString Lon=m_Grid.GetTextMatrix(i,1), 
						    Lat=m_Grid.GetTextMatrix(i,2),
							UFS=m_Grid.GetTextMatrix(i,3),
							Em=m_Grid.GetTextMatrix(i,4);
					if(Lat.Left(1)==_T("-")) sgn=-1.0;
					else					sgn=1.0;
					double LAT = (atof(Lat.Left(3))+sgn*atof(Lat.Mid(3,2))/60.+sgn*atof(Lat.Mid(5,5))/3600.);
					if(Lon.Left(1)==_T("-")) sgn=-1.0;
					else					sgn=1.0;
					double LON = (atof(Lon.Left(4))+sgn*atof(Lon.Mid(4,2))/60.+sgn*atof(Lon.Mid(6,5))/3600.);

					SQL.Format(_T("insert into CSArea (IDst,SiteName,GeoLat,GeoLon,UFS,Em) select %ld,'%s',%lf,%lf,%s,%s "),
						m_Grp_id,m_StName,LAT,LON,UFS,Em);
					m_DB.ExecuteSQL(SQL);
				}
				res=true;
			}
			else
			{
				if(!FormatOK)
					AfxMessageBox(_Z("Coordinates in some rows are not in correct format!"));
				if(!Mess.IsEmpty())
				{
					Mess.Delete(Mess.GetLength()-1);
					AfxMessageBox(Mess);
				}
			}
			break;
		}	
	case 12:
			for(i=1;i<m_Grid.GetRows();i++)
			{
				if(m_Grid.GetTextMatrix(i,1).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,1),i);
					Mess+=Part;
				}
				if(m_Grid.GetTextMatrix(i,2).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,2),i);
					Mess+=Part;
				}
				if(m_Grid.GetTextMatrix(i,3).IsEmpty())
				{
					Part.Format(_Z("%s in row %d is mandatory,"),m_Grid.GetTextMatrix(0,3),i);
					Mess+=Part;
				}
			}
			if(Mess.IsEmpty())
			{
				SQL.Format(_T("delete * from rrc_allot_coord where allotkey=%ld "),m_Grp_id);
				m_DB.ExecuteSQL(SQL);
				for(i=1;i<m_Grid.GetRows();i++)
				{
					SQL.Format(_T("insert into rrc_allot_coord (allotkey,coord_prov, agree_st, adm) select %ld,'%s','%s','%s' "),
						m_Grp_id,m_Grid.GetTextMatrix(i,1),m_Grid.GetTextMatrix(i,2),m_Grid.GetTextMatrix(i,3));
					m_DB.ExecuteSQL(SQL);
				}
				res=true;
			}
			else
			{
				Mess.Delete(Mess.GetLength()-1);
				AfxMessageBox(Mess);
			}
			break;
	}
	return res;
}

void CGrpDetails::OnClose() 
{

	int code= AfxMessageBox(_Z("Do you want to save the changes?"),MB_YESNO);
	bool res=true;
	if(code==IDYES)
		res=OnSave();
	if(res) CDialog::OnClose();
}

void CGrpDetails::OnCancel() 
{
	int code= AfxMessageBox(_Z("Do you want to save the changes?"),MB_YESNO);
	bool res=true;
	if(code==IDYES)
		res=OnSave();
	if(res) CDialog::OnCancel();
}
