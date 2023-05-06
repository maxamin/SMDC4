// Agreement.cpp : implementation file
//
#include "stdafx.h"
#include "ificimport.h"
#include "Agreement.h"
#include "column.h"
#include "columns.h"
#include <comdef.h>
#include "CountryList.h"
#include "PropSelect.h"
#include "ServSelect.h"
#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgreement dialog


CAgreement::CAgreement(CWnd* pParent /*=NULL*/)
	: CDialog(CAgreement::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAgreement)
	m_AgName = _T("");
	m_AgProp = _T("");
	m_AgCountries = _T("");
	m_AgServ = _T("");
	m_RecordCount = _T("");
	//}}AFX_DATA_INIT
	m_RecNo=1;
}

void CAgreement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAgreement)
	DDX_Control(pDX, IDC_AGPLUS, m_AgPlus);
	DDX_Control(pDX, IDC_AGMINUS, m_AgMinus);
	DDX_Control(pDX, IDC_PREFCOUNTRY, m_PrefCountries);
	DDX_Control(pDX, IDC_SERVLIST, m_ServList);
	DDX_Control(pDX, IDC_MODELLIST, m_ModelList);
	DDX_Control(pDX, IDC_COUNTLIST, m_CountList);
	DDX_Control(pDX, IDC_AGTYPE, m_AgType);
	DDX_Control(pDX, IDC_AGLAST, m_AgLast);
	DDX_Control(pDX, IDC_AGFIRST, m_AgFirst);
	DDX_Control(pDX, IDC_AGDELETE, m_AgDelete);
	DDX_Control(pDX, IDC_AGCANCEL, m_AgCancel);
	DDX_Control(pDX, IDC_AGMODEL, m_AgModel);
	DDX_Control(pDX, IDC_AGSAVE, m_AgSave);
	DDX_Control(pDX, IDC_AGPREV, m_AgPrev);
	DDX_Control(pDX, IDC_AGNEXT, m_AgNext);
	DDX_Control(pDX, IDC_AGNEW, m_AgNew);
	DDX_Control(pDX, IDC_AGMOD, m_AgMod);
	DDX_Text(pDX, IDC_AGNAME, m_AgName);
	DDX_Text(pDX, IDC_AGPROP, m_AgProp);
	DDX_Text(pDX, IDC_AGCOUNTRIES, m_AgCountries);
	DDX_Text(pDX, IDC_AGSERV, m_AgServ);
	DDX_Text(pDX, IDC_RECORDCOUNT, m_RecordCount);
	DDX_Control(pDX, IDC_AGLIST, m_AgList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAgreement, CDialog)
	//{{AFX_MSG_MAP(CAgreement)
	ON_BN_CLICKED(IDC_AGPREV, OnAgprev)
	ON_BN_CLICKED(IDC_AGNEXT, OnAgnext)
	ON_BN_CLICKED(IDC_AGNEW, OnAgnew)
	ON_BN_CLICKED(IDC_AGMOD, OnAgmod)
	ON_BN_CLICKED(IDC_AGSAVE, OnAgsave)
	ON_BN_CLICKED(IDC_AGCANCEL, OnAgcancel)
	ON_BN_CLICKED(IDC_COUNTLIST, OnCountlist)
	ON_BN_CLICKED(IDC_AGFIRST, OnAgfirst)
	ON_BN_CLICKED(IDC_AGLAST, OnAglast)
	ON_BN_CLICKED(IDC_MODELLIST, OnModellist)
	ON_BN_CLICKED(IDC_SERVLIST, OnServlist)
	ON_BN_CLICKED(IDC_PREFCOUNTRY, OnPrefcountry)
	ON_BN_CLICKED(IDC_AGDELETE, OnAgdelete)
	ON_CBN_SELCHANGE(IDC_AGTYPE, OnSelchangeAgtype)
	ON_CBN_SELCHANGE(IDC_AGMODEL, OnSelchangeAgmodel)
	ON_EN_KILLFOCUS(IDC_AGNAME, OnKillfocusAgname)
	ON_BN_CLICKED(IDC_AGMINUS, OnAgminus)
	ON_BN_CLICKED(IDC_AGPLUS, OnAgplus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgreement message handlers

BOOL CAgreement::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_AgFirst.LoadBitmaps(IDB_FIRST1,IDB_FIRST2,IDB_FIRST1,IDB_FIRST3);
	m_AgPrev.LoadBitmaps(IDB_PREV1,IDB_PREV2,IDB_PREV1,IDB_PREV3);
	m_AgNext.LoadBitmaps(IDB_NEXT1,IDB_NEXT2,IDB_NEXT1,IDB_NEXT3);
	m_AgLast.LoadBitmaps(IDB_LAST1,IDB_LAST2,IDB_LAST1,IDB_LAST3);	
	m_AgNew.LoadBitmaps(IDB_ADD1,IDB_ADD2,IDB_ADD1,IDB_ADD3);	
	m_AgDelete.LoadBitmaps(IDB_DELETE1,IDB_DELETE2,IDB_DELETE1,IDB_DELETE3);
	m_AgSave.LoadBitmaps(IDB_SAVE1,IDB_SAVE2,IDB_SAVE1,IDB_SAVE3);
	m_AgPlus.LoadBitmaps(IDB_PLUS1,IDB_PLUS2,IDB_PLUS1,IDB_PLUS3);
	m_AgMinus.LoadBitmaps(IDB_MINUS1,IDB_MINUS2,IDB_MINUS1,IDB_MINUS3);
	CString m_Tbl;
	m_DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	m_RS.m_pDatabase=&m_DB;
	m_Tbl=_T("select * from Agreements order by agid");
	m_RS.Open( CRecordset::dynaset, m_Tbl);
	m_RecTotal=0;
	while(m_RS.GetRecordCount())
	{
		m_RS.MoveNext();
		m_RecTotal++;
		if(m_RS.IsEOF()) break;
	}
	m_RS.MoveFirst();
	LoadAgreement(m_RS);
	m_ViewAddEdit=0;
	UpdateData(false);
	m_AgList.m_ReadOnly=true;
	TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAgreement::LoadAgreement(CRecordset &RS)
{
	CString Field;
	RS.GetFieldValue(_T("AgID"),Field);
	m_AgCode=atol(Field);
	RS.GetFieldValue(_T("AgName"),m_AgName);
	RS.GetFieldValue(_T("Countries"),m_AgCountries);
	RS.GetFieldValue(_T("Service"),m_AgServ);
	RS.GetFieldValue(_T("Model"),Field);
	Field.TrimRight();
	m_AgModel.SelectString(0,Field);
	RS.GetFieldValue(_T("Type"),Field);
	Field.TrimRight();
	m_AgType.SelectString(0,Field);
	RS.GetFieldValue(_T("PropModels"),m_AgProp);
//	m_AgType.GetWindowText(Field);
//	LoadModel(Field);
	OnSelchangeAgmodel();
	m_RecordCount.Format(_T("%ld of %ld"),m_RecNo,m_RecTotal);
	UpdateData(false);
	(CEdit *)GetDlgItem(IDC_AGNAME)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGSERV)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_PREFCOUNTRY)->EnableWindow(false);
	(CButton *)GetDlgItem(IDC_MODELLIST)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGMODEL)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGTYPE)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGPROP)->EnableWindow(false);	
}

void CAgreement::LoadModel(CString m_AgType)
{
	CString SQL,Model;
	CRecordset RS;
	bool PrefCntry=false;
	m_AgModel.GetWindowText(Model);
	if(!Model.CompareNoCase(_T("1")) && !m_AgType.CompareNoCase(_T("B"))) 
	{
		m_ModelList.EnableWindow(false);
		SQL.Format(_T("select LoFreq as [LoFreq (MHz)],HiFreq as [HiFreq (MHz)],'' as PrefCountries,CoordDist1 as [CoordDist1(km)],CoordDist2 as [CoordDist2(km)],Emergency from Model12 where AgID=%ld"),m_AgCode);
		m_AgProp="";
		UpdateData(false);	
	}
	else
	{
		m_ModelList.EnableWindow(true);
		if(atoi(Model)==1)
			SQL.Format(_T("select LoFreq as [LoFreq (MHz)],HiFreq as [HiFreq (MHz)],'' as PrefCountries,PIFS as [PIFS(dBuV/m)],Xkm_CBR as [CBR(km)],ERP as [ERP(dBW)],Emergency from Model12 where AgID=%ld"),m_AgCode);
		else
		{
			SQL.Format(_T("select LoFreq as [LoFreq (MHz)],HiFreq as [HiFreq (MHz)],PrefCountries,PIFS as [PIFS(dBuV/m)],Xkm_CBR as [Xkm(km)],ERP as [ERP(dBW)],Emergency from Model12 where AgID=%ld"),m_AgCode);
			PrefCntry=true;
		}
	}
//	m_ModList.SetRecordSource(SQL);
//	m_ModList.Refresh();
	m_AgList.SetRows(0);
	m_AgList.SetRows(2);
	m_AgList.SetFixedRows(1);
	RS.m_pDatabase=&m_DB;
	RS.Open(CRecordset::snapshot,SQL);
	m_AgList.SetCols(0,RS.GetODBCFieldCount()+1);
	for(int i=0;i<RS.GetODBCFieldCount();i++)
	{
		CODBCFieldInfo Fld;
		RS.GetODBCFieldInfo(i,Fld);
		m_AgList.SetTextMatrix(0,i+1,Fld.m_strName);
	}
	int j=1;
	while(true)
	{
		if(RS.IsEOF()) break;
		for(int i=0;i<RS.GetODBCFieldCount();i++)
		{
//			CODBCFieldInfo Fld;
//			RS.GetODBCFieldInfo(i,&Fld);
			CString Val;
			RS.GetFieldValue(i,Val);
			m_AgList.SetTextMatrix(j,i+1,Val);
		}
		j++;
		RS.MoveNext();
		m_AgList.SetRows(j+1);
	}
	RS.Close();
	if(j>1) m_AgList.SetRows(m_AgList.GetRows()-1);
	m_AgList.SetColWidth(0,0,300);
	m_AgList.SetColWidth(1,0,1100);
	m_AgList.SetColWidth(2,0,1100);
	if(PrefCntry)
		m_AgList.SetColWidth(3,0,1200);
	else
		m_AgList.SetColWidth(3,0,0);
	m_AgList.SetColWidth(4,0,1300);
	m_AgList.SetColWidth(5,0,1300);
	m_AgList.Refresh();
}

void CAgreement::OnAgprev() 
{
	m_RS.MovePrev();
	((CButton *)GetDlgItem(IDC_AGNEXT))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_AGLAST))->EnableWindow(true);
	m_RecNo--;
	if(m_RecNo==1)
	{
		((CButton *)GetDlgItem(IDC_AGPREV))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_AGFIRST))->EnableWindow(false);
	}
	LoadAgreement(m_RS);
}

void CAgreement::OnAgnext() 
{
	m_RS.MoveNext();	
	((CButton *)GetDlgItem(IDC_AGPREV))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_AGFIRST))->EnableWindow(true);
	m_RecNo++;
	if(m_RecNo==m_RecTotal)
	{
		((CButton *)GetDlgItem(IDC_AGNEXT))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_AGLAST))->EnableWindow(false);
	}
	LoadAgreement(m_RS);
}

BEGIN_EVENTSINK_MAP(CAgreement, CDialog)
    //{{AFX_EVENTSINK_MAP(CAgreement)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CAgreement::OnAgnew() 
{
	(CButton *)GetDlgItem(IDC_AGNEW)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGMOD)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGDELETE)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGSAVE)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGCANCEL)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_SERVLIST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_COUNTLIST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_MODELLIST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGPREV)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGNEXT)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGFIRST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGLAST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGPLUS)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGMINUS)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_PREFCOUNTRY)->EnableWindow(false);
	(CButton *)GetDlgItem(IDC_PREFCOUNTRY)->ShowWindow(SW_HIDE);
	(CEdit *)GetDlgItem(IDC_AGNAME)->EnableWindow(true);	
//	(CEdit *)GetDlgItem(IDC_AGSERV)->EnableWindow(true);	
//	(CEdit *)GetDlgItem(IDC_AGCOUNTRIES)->EnableWindow(true);	
	(CEdit *)GetDlgItem(IDC_AGMODEL)->EnableWindow(true);	
	(CEdit *)GetDlgItem(IDC_AGTYPE)->EnableWindow(true);	
	(CEdit *)GetDlgItem(IDC_AGTYPE)->ShowWindow(SW_SHOW);
//	(CEdit *)GetDlgItem(IDC_AGPROP)->EnableWindow(true);
	m_AgCountries = _T("");
	m_AgModel.SelectString(0,_T("1"));
	m_AgName = _T("");
	m_AgServ = _T("");
	m_AgType.SelectString(0,_T("A"));
	m_AgProp = _T("");
	UpdateData(false);
	CRecordset rs;
	CString SQL,Temp;
	rs.m_pDatabase=&m_DB;
	rs.Open(CRecordset::snapshot,_T("select max(AgID)+1 from agreements"));
	rs.GetFieldValue((short)0,Temp);
	if(Temp.IsEmpty()) Temp=_T("1");
	rs.Close();
	m_AgCode=atol(Temp);
//	SQL.Format(_T("select LoFreq as [LoFreq (MHz)],HiFreq as [HiFreq (MHz)],PrefCountries,PIFS as [PIFS(dBuV/m)],Xkm_CBR as [CBR(km)],ERP as [ERP(dBW)],Emergency from Model12 where AgID=%ld"),m_AgCode);
//	m_ModList.SetRecordSource(SQL);
//	m_ModList.Refresh();
	m_ViewAddEdit=1;
	OnSelchangeAgtype();
	m_AgList.SetRows(2);
	m_AgList.m_ReadOnly=false;
}

void CAgreement::OnAgmod() 
{
	(CButton *)GetDlgItem(IDC_AGNEW)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGMOD)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGDELETE)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGSAVE)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGCANCEL)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_SERVLIST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_COUNTLIST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_MODELLIST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGPREV)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGNEXT)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGFIRST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGLAST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGPLUS)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGMINUS)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_PREFCOUNTRY)->EnableWindow(true);
	(CEdit *)GetDlgItem(IDC_AGNAME)->EnableWindow(true);	
	(CEdit *)GetDlgItem(IDC_AGMODEL)->EnableWindow(true);	
	(CEdit *)GetDlgItem(IDC_AGTYPE)->EnableWindow(true);	
	CString Field;
	m_AgModel.GetWindowText(Field);
	m_ModelList.EnableWindow(true);
	if(Field==_T("1"))
	{
		m_AgType.GetWindowText(Field);
		if(Field==_T("B"))
			m_ModelList.EnableWindow(false);
	}
	m_ViewAddEdit=2;
	m_AgList.m_ReadOnly=false;
}

void CAgreement::OnAgsave() 
{
	CString SQL;
	(CButton *)GetDlgItem(IDC_AGNEW)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGMOD)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGDELETE)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGSAVE)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGCANCEL)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_SERVLIST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_COUNTLIST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_MODELLIST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGPREV)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGNEXT)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGFIRST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGLAST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGPLUS)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGMINUS)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_PREFCOUNTRY)->EnableWindow(false);
	(CEdit *)GetDlgItem(IDC_AGNAME)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGMODEL)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGTYPE)->EnableWindow(false);	
	UpdateData();
	CString Type,Model;
	m_AgModel.GetWindowText(Model);
	m_AgType.GetWindowText(Type);
	if(m_ViewAddEdit==1) // Add
	{
		CRecordset rs;
		CString SQL,Temp;
		rs.m_pDatabase=&m_DB;
		rs.Open(CRecordset::snapshot,_T("select max(AgID)+1 from agreements"));
		rs.GetFieldValue((short)0,Temp);
		if(Temp.IsEmpty()) Temp=_T("1");
		rs.Close();
		m_AgCode=atol(Temp);
		SQL.Format(_T("Select %ld,'%s','%s','%s',%s,'%s','%s' "),
			m_AgCode,m_AgName,m_AgServ,m_AgCountries,Model,(Model==_T("2"))?"":Type,m_AgProp);
		SQL=_T("insert into agreements (AgID,AgName,Service,Countries,Model,Type,PropModels)") + SQL;
		m_DB.ExecuteSQL(SQL);
		m_RS.Requery();
		m_RS.MoveLast();
		m_RecTotal++;
		m_RecNo=m_RecTotal;
		m_RecordCount.Format(_T("%ld of %ld"),m_RecNo,m_RecTotal);
		UpdateData(false);
	}
	else				// Edit
	{
		SQL.Format(_T("Update agreements set AgName='%s',Service='%s',Countries='%s',Model=%s,Type='%s',PropModels='%s' where AgID=%ld"),
			m_AgName,m_AgServ,m_AgCountries,Model,(Model==_T("2"))?"":Type,m_AgProp,m_AgCode);
		m_DB.ExecuteSQL(SQL);
	}
////   Grid save
	SQL.Format(_T("delete * from model12 where agid=%ld "),m_AgCode);
	m_DB.ExecuteSQL(SQL);
	for(int i=1;i<m_AgList.GetRows();i++)
	{
		CString Model,FreqLo=m_AgList.GetTextMatrix(i,1),FreqHi=m_AgList.GetTextMatrix(i,2);
		m_AgModel.GetWindowText(Model);
		if(!Type.CompareNoCase(_T("B")) && !Model.CompareNoCase(_T("1"))) 
		{
			CString Coord1=m_AgList.GetTextMatrix(i,4),Coord2=m_AgList.GetTextMatrix(i,5);
			SQL.Format(_T("insert into model12 (AgID,LoFreq,HiFreq,PrefCountries,CoordDist1,CoordDist2,Emergency) select %ld,%lf,%lf,'%s',%ld,%ld,%d "),
				m_AgCode,atof(FreqLo),atof(FreqHi),m_AgList.GetTextMatrix(i,3),atol(Coord1),atol(Coord2),atoi(m_AgList.GetTextMatrix(i,6)));
			m_DB.ExecuteSQL(SQL);
		}
		else
		{
			CString PIFS=m_AgList.GetTextMatrix(i,4),Xkm=m_AgList.GetTextMatrix(i,5),ERP=m_AgList.GetTextMatrix(i,6);
			SQL.Format(_T("insert into model12 (AgID,LoFreq,HiFreq,PrefCountries,PIFS,Xkm_CBR,ERP,Emergency) select %ld,%lf,%lf,'%s',%lf,%ld,%lf,%d "),
				m_AgCode,atof(FreqLo),atof(FreqHi),m_AgList.GetTextMatrix(i,3),atof(PIFS),atol(Xkm),atof(ERP),atoi(m_AgList.GetTextMatrix(i,7)));
			m_DB.ExecuteSQL(SQL);
		}
	}
////
	m_ViewAddEdit=0;
	m_AgList.m_ReadOnly=true;
}

void CAgreement::OnOK()
{
}

void CAgreement::OnAgcancel() 
{
	if(m_ViewAddEdit==1) // Add
	{
		m_RS.MoveNext();
		m_RS.MovePrev();
		LoadAgreement(m_RS);
	}
	(CButton *)GetDlgItem(IDC_AGNEW)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGMOD)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGDELETE)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGSAVE)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_SERVLIST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_COUNTLIST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_MODELLIST)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGPREV)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGNEXT)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGFIRST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGLAST)->EnableWindow(true);	
	(CButton *)GetDlgItem(IDC_AGPLUS)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_AGMINUS)->EnableWindow(false);	
	(CButton *)GetDlgItem(IDC_PREFCOUNTRY)->EnableWindow(false);
	(CEdit *)GetDlgItem(IDC_AGNAME)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGSERV)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGCOUNTRIES)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGMODEL)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGTYPE)->EnableWindow(false);	
	(CEdit *)GetDlgItem(IDC_AGPROP)->EnableWindow(false);	
	m_AgList.m_ReadOnly=true;
}

void CAgreement::OnCountlist() 
{
	CCountryList CountryDlg;
	CountryDlg.m_SDBSTR=m_SDBSTR;
	CountryDlg.m_Lang=m_Lang;
	if(CountryDlg.DoModal()==IDOK)
	{
		m_AgCountries=CountryDlg.m_Result;
		UpdateData(false);
	}
}

void CAgreement::OnAgfirst() 
{
	m_RS.MoveFirst();
	((CButton *)GetDlgItem(IDC_AGNEXT))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_AGLAST))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_AGPREV))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_AGFIRST))->EnableWindow(false);
	m_RecNo=1;
	LoadAgreement(m_RS);	
}

void CAgreement::OnAglast() 
{
	m_RS.MoveLast();	
	((CButton *)GetDlgItem(IDC_AGPREV))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_AGFIRST))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_AGNEXT))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_AGLAST))->EnableWindow(false);
	m_RecNo=m_RecTotal;
	LoadAgreement(m_RS);	
}

void CAgreement::OnModellist() 
{
	CPropSelect PropDlg;
	PropDlg.m_Lang=m_Lang;
	if(PropDlg.DoModal()==IDOK)
	{
		m_AgProp=PropDlg.m_Result;
		UpdateData(false);	
	}
}

void CAgreement::OnServlist() 
{
	CServSelect ServDlg;
	CString Model,Type;
	m_AgModel.GetWindowText(Model);
	m_AgType.GetWindowText(Type);
	if(Model==_T("1") && Type==_T("B"))
		ServDlg.m_Fixed=true;
	else
		ServDlg.m_Fixed=false;
	ServDlg.m_Lang=m_Lang;
	if(ServDlg.DoModal()==IDOK)
	{
		m_AgServ=ServDlg.m_Result;
		UpdateData(false);	
	}
}

void CAgreement::OnPrefcountry() 
{
	CCountryList CountryDlg;
	CountryDlg.m_SDBSTR=m_SDBSTR;
	CountryDlg.m_Lang=m_Lang;
	if(CountryDlg.DoModal()==IDOK)
	{
		m_AgList.SetTextMatrix(m_AgList.GetRow(),3,CountryDlg.m_Result);
		UpdateData(false);
	}
}

void CAgreement::OnAgdelete() 
{
	CString SQL;
	SQL.Format(_T("delete * from model12 where agid=%ld "),m_AgCode);
	m_DB.ExecuteSQL(SQL);
	SQL.Format(_T("delete * from agreements where agid=%ld "),m_AgCode);
	m_DB.ExecuteSQL(SQL);
	m_RS.Requery();
	m_RecTotal--;
	OnAgfirst();
}

void CAgreement::OnSelchangeAgtype() 
{
	CString Field;
	m_AgType.GetWindowText(Field);
	LoadModel(Field);
}

void CAgreement::OnSelchangeAgmodel() 
{
	CString Field;
	m_AgModel.GetWindowText(Field);
	if(Field==_T("1"))
	{
		((CComboBox *)GetDlgItem(IDC_AGTYPE))->ShowWindow(SW_SHOW);
		((CStatic *)GetDlgItem(IDC_TYPE_lbl))->ShowWindow(SW_SHOW);
		((CButton *)GetDlgItem(IDC_PREFCOUNTRY))->ShowWindow(SW_HIDE);
		(CButton *)GetDlgItem(IDC_PREFCOUNTRY)->EnableWindow(false);
	}
	else
	{
		((CComboBox *)GetDlgItem(IDC_AGTYPE))->ShowWindow(SW_HIDE);
		((CStatic *)GetDlgItem(IDC_TYPE_lbl))->ShowWindow(SW_HIDE);
		((CButton *)GetDlgItem(IDC_PREFCOUNTRY))->ShowWindow(SW_SHOW);
		(CButton *)GetDlgItem(IDC_PREFCOUNTRY)->EnableWindow(true);
	}
	m_AgType.GetWindowText(Field);
	LoadModel(Field);
}

void CAgreement::OnKillfocusAgname() 
{
	UpdateData();	
}

void CAgreement::OnAgminus() 
{
	if(m_AgList.GetRows()>2)
		m_AgList.SetRows(m_AgList.GetRows()-1);	
}

void CAgreement::OnAgplus() 
{
	m_AgList.SetRows(m_AgList.GetRows()+1);		
}

void CAgreement::TranslateDialog(CDialog *pDialog)
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

CString CAgreement::GetTranslatedString(CString strOriginal, CString Lang)
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
