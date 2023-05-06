// Audit.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "Administrative.h"
#include <comdef.h>
#include "Audit.h"
#include "test6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudit dialog


CAudit::CAudit(CWnd* pParent /*=NULL*/)
	: CDialog(CAudit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAudit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAudit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudit)
	DDX_Control(pDX, IDC_UserName, m_UserName);
	DDX_Control(pDX, IDC_Table, m_Table);
	DDX_Control(pDX, IDC_ACTION, m_Action);
	DDX_Control(pDX, IDC_AuditGrid, m_AuditGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAudit, CDialog)
	//{{AFX_MSG_MAP(CAudit)
	ON_CBN_SELCHANGE(IDC_UserName, OnSelchangeUserName)
	ON_CBN_SELCHANGE(IDC_ACTION, OnSelchangeAction)
	ON_CBN_SELCHANGE(IDC_Table, OnSelchangeTable)
	ON_BN_CLICKED(IDC_AuditRefresh, OnAuditRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudit message handlers

BOOL CAudit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_AuditGrid.SetCols(0,6);
	m_AuditGrid.SetRows(1);
	CString rCaption;
	m_AuditGrid.SetTextMatrix(0,1,_Z("User"));
	m_AuditGrid.SetTextMatrix(0,2,_Z("Date/Time"));
	m_AuditGrid.SetTextMatrix(0,3,_Z("Action"));
	m_AuditGrid.SetTextMatrix(0,4,_Z("Record no."));
	m_AuditGrid.SetTextMatrix(0,5,_Z("Table"));

	CRecordset m_rs;
	CDatabase m_DB;
	CDBVariant TempVar;
	CString F1,F2;
	m_DB.Open(((CSMS4DCApp *)AfxGetApp())->m_CDBSTR, FALSE, FALSE, _T("ODBC;"), FALSE);
	m_rs.m_pDatabase=&m_DB;

	m_rs.Open(CRecordset::snapshot,_T("select * from Audit"));
	int row=1;
	while(true)
	{
		CString Value;
		if(m_rs.IsEOF()) break;
		m_AuditGrid.SetRows(m_AuditGrid.GetRows()+1);
		m_rs.GetFieldValue(_T("UserName"),Value);
		m_AuditGrid.SetTextMatrix(row,1,Value);
		m_rs.GetFieldValue(_T("DateTime"),Value);
		m_AuditGrid.SetTextMatrix(row,2,Value);
		m_rs.GetFieldValue(_T("Action"),Value);
		m_AuditGrid.SetTextMatrix(row,3,Value);
		m_rs.GetFieldValue(_T("Record"),Value);
		m_AuditGrid.SetTextMatrix(row,4,Value);
		m_rs.GetFieldValue(_T("Table"),Value);
		m_AuditGrid.SetTextMatrix(row,5,Value);
		m_rs.MoveNext();
		row++;
	}
	m_rs.Close();

	CString m_Tbl="select distinct UserName from Audit";
	m_rs.Open( CRecordset::snapshot, m_Tbl);
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((short)0,F1);
		m_UserName.AddString(F1);
		m_rs.MoveNext();
	}
	m_rs.Close();
	m_Tbl="select distinct Action from Audit";
	m_rs.Open( CRecordset::snapshot, m_Tbl);
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((short)0,F1);
		m_Action.AddString(F1);
		m_rs.MoveNext();
	}
	m_rs.Close();
	m_Tbl="select distinct [Table] from Audit";
	m_rs.Open( CRecordset::snapshot, m_Tbl);
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((short)0,F1);
		m_Table.AddString(F1);
		m_rs.MoveNext();
	}
	m_rs.Close();

	m_UserName.SelectString(0,_Z("All"));
	m_Action.SelectString(0,_Z("All"));
	m_Table.SelectString(0,_Z("All"));
	m_AuditGrid.SetFixedRows(1);

	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAudit::OnSelchangeUserName() 
{
	OnAuditRefresh();
/*	CString SQL;
	m_UserName.GetWindowText(SQL);
	if(SQL=="")
		SQL="Select * from Audit";
	else
		SQL="Select * from Audit where UserName=\'" + SQL + "\'";
	m_AuditRecs.SetRecordSource(SQL);
	m_AuditRecs.Refresh();*/
}

void CAudit::OnSelchangeAction() 
{
	OnAuditRefresh();
/*	CString SQL;
	m_Action.GetWindowText(SQL);
	SQL="Select * from Audit where Action=\'" + SQL + "\'";
	m_AuditRecs.SetRecordSource(SQL);
	m_AuditRecs.Refresh();	*/
}

void CAudit::OnSelchangeTable() 
{
	OnAuditRefresh();
/*	CString SQL;
	m_Table.GetWindowText(SQL);
	SQL="Select * from Audit where [Table]=\'" + SQL + "\'";
	m_AuditRecs.SetRecordSource(SQL);
	m_AuditRecs.Refresh();	*/
}

void CAudit::OnAuditRefresh() 
{
	bool Flag=false;
	CString SQL, User, Action, Table;
	SQL="Select * from Audit";
	m_UserName.GetWindowText(User);
	m_Action.GetWindowText(Action);
	m_Table.GetWindowText(Table);
	if(User!=_Z("All") || Action!=_Z("All") || Table!=_Z("All"))
		SQL+=" where ";
	if(User!=_Z("All"))
	{
		SQL+="UserName=\'"+User+"\' ";
		Flag=true;
	}
	if(Action!=_Z("All"))
	{
		if(Flag)
			SQL+=" and ";
		SQL+="Action=\'"+Action+"\' ";
		Flag=true;
	}
	if(Table!=_Z("All"))
	{
		if(Flag)
			SQL+=" and ";
		SQL+="Table=\'"+Table+"\' ";
		Flag=true;
	}
	CRecordset m_rs;
	CDatabase m_DB;
	m_DB.Open(((CSMS4DCApp *)AfxGetApp())->m_CDBSTR, FALSE, FALSE, "ODBC;", FALSE);
	m_rs.m_pDatabase=&m_DB;

	m_rs.Open(CRecordset::snapshot,SQL);
	m_AuditGrid.SetRows(1);
	m_AuditGrid.Clear();
	int row=1;
	while(true)
	{
		CString Value;
		if(m_rs.IsEOF()) break;
		m_AuditGrid.SetRows(m_AuditGrid.GetRows()+1);
		m_rs.GetFieldValue(_T("UserName"),Value);
		m_AuditGrid.SetTextMatrix(row,1,Value);
		m_rs.GetFieldValue(_T("DateTime"),Value);
		m_AuditGrid.SetTextMatrix(row,2,Value);
		m_rs.GetFieldValue(_T("Action"),Value);
		m_AuditGrid.SetTextMatrix(row,3,Value);
		m_rs.GetFieldValue(_T("Record"),Value);
		m_AuditGrid.SetTextMatrix(row,4,Value);
		m_rs.GetFieldValue(_T("Table"),Value);
		m_AuditGrid.SetTextMatrix(row,5,Value);
		m_rs.MoveNext();
		row++;
	}
	m_rs.Close();
	m_DB.Close();	
}
