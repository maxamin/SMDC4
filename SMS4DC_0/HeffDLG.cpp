// HeffDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "HeffDLG.h"
#include <afxdb.h>			// MFC ODBC database classes

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeffDLG dialog


CHeffDLG::CHeffDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CHeffDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHeffDLG)
	m_maxH = _T("");
	m_maxH2 = 0.0;
	//}}AFX_DATA_INIT
}


void CHeffDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHeffDLG)
	DDX_Control(pDX, IDC_Save, m_BUTTON_Save);
	DDX_Text(pDX, IDC_EDIT_maxH, m_maxH);
	DDX_Text(pDX, IDC_EDIT_maxH2, m_maxH2);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHeffDLG, CDialog)
	//{{AFX_MSG_MAP(CHeffDLG)
	ON_BN_CLICKED(IDC_Save, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeffDLG message handlers

BOOL CHeffDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString m_CDBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	m_grid.SetCols(2);
	m_grid.SetTextMatrix(0,0,"Azimuth(Deg.)");
	m_grid.SetTextMatrix(0,1,"Heff(m)");
	m_grid.SetColWidth(0,1200);
	m_grid.SetRowHeightMin(250);

	CString  tbl , m_DB = m_CDBSTR;
	CDatabase DB1;	CRecordset rs;
	DB1.Open(m_DB,false,false,_T("ODBC;"),false);
	rs.m_pDatabase = &DB1;
	tbl.Format(_T("SELECT * FROM AntHgt WHERE (((AntID)=%ld)) ORDER BY Azm;"), m_AntID);
	rs.Open(CRecordset::snapshot, tbl);
	m_num = 0;
	double Hmax = -9999;
	CString str = _T("");

	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			m_num++;
			m_grid.SetRows(m_num+1);
			rs.GetFieldValue(_T("Azm"),str);	m_grid.SetTextMatrix(m_num,0,str);
			rs.GetFieldValue(_T("EffHgt"),str);	m_grid.SetTextMatrix(m_num,1,str);
			Hmax = max(Hmax,atof(str));
			rs.MoveNext();
		}
	}
	rs.Close();	
	
	if(m_num>0)
	{
		tbl.Format(_T("select AntCatID from Antenna where AntID=%ld"), m_AntID);
		rs.Open(CRecordset::snapshot,tbl);
		rs.GetFieldValue("AntCatID",str);	m_AntCatID = atol(str);
		rs.Close();

		tbl.Format(_T("SELECT MaxEffHght FROM AntCat WHERE (((AntCatID)=%ld));"), m_AntCatID);
		rs.Open(CRecordset::snapshot,tbl);
		rs.GetFieldValue("MaxEffHght",str);
		rs.Close();
		DB1.Close();

		m_maxH = str;		m_maxH2 = Hmax;
		UpdateData(false);
	}
	else
		m_BUTTON_Save.EnableWindow(FALSE);

	m_BUTTON_Save.LoadBitmaps(IDB_Save1,IDB_Save2,IDB_Save1,IDB_Save3);
	return TRUE;  
}


void CHeffDLG::OnSave() 
{
	if(m_num>0)
	{
		CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
		CDatabase DB1;		CRecordset rs;
		DB1.Open(m_DB,false,false,_T("ODBC;"),false);

		CString SQL1;
		SQL1.Format(_T("DELETE * FROM AntHgt WHERE (((AntID)=%ld));"), m_AntID);
		DB1.ExecuteSQL(SQL1);

		CString Azm, EffHgt;
		for(int i=0;i<m_num;i++)
		{
			Azm		= m_grid.GetTextMatrix(i+1,0);
			EffHgt	= m_grid.GetTextMatrix(i+1,1);

			SQL1.Format(_T("SELECT %ld,%s,%s "), m_AntID, Azm, EffHgt);
			SQL1 = _T("INSERT INTO AntHgt (AntID, Azm, EffHgt) ") + SQL1;
			DB1.ExecuteSQL(SQL1);
		}

		UpdateData();
		SQL1.Format(_T("UPDATE AntCat SET MaxEffHght = %s WHERE (((AntCatID)=%ld));"), m_maxH,m_AntCatID) ;
		DB1.ExecuteSQL(SQL1);
		DB1.Close();
	}
}
