// PaymentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Administrative.h"
#include "PaymentDlg.h"
//#include "AuditTrail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaymentDlg dialog


CPaymentDlg::CPaymentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaymentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaymentDlg)
	m_PaymentNo = _T("");
	m_PaymentVal = 0;
	m_PayDesc = _T("");
	m_PayDate = 0;
	//}}AFX_DATA_INIT
}


void CPaymentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaymentDlg)
	DDX_Text(pDX, IDC_PAYMENT_NO, m_PaymentNo);
	DDX_Text(pDX, IDC_PAYMENT_VAL, m_PaymentVal);
	DDV_MinMaxLong(pDX, m_PaymentVal, -2000000000, 2000000000);
	DDX_Text(pDX, IDC_PAYMENT_DESC, m_PayDesc);
	DDX_DateTimeCtrl(pDX, IDC_PAY_DATE, m_PayDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaymentDlg, CDialog)
	//{{AFX_MSG_MAP(CPaymentDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaymentDlg message handlers

void CPaymentDlg::OnOK() 
{
	CDatabase DB;
	CRecordset RS;
	CString SQL,ID,Val;
	UpdateData();
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("select count(PaymentID) from payment where PaymentNo='%s'"),m_PaymentNo);
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,Val);
	RS.Close();
	if(atol(Val)==0)
	{
		RS.Open(CRecordset::dynaset,_T("Select max(PaymentID) from Payment"));
		RS.GetFieldValue((short)0,ID);
		RS.Close();
		if(ID.IsEmpty()) ID=_T("1");
		UpdateData();
		SQL.Format(_T("select %ld, %ld, '%s', #%s#, '%s', %ld"), atol(ID)+1, m_ID, m_PaymentNo, m_PayDate.Format(_T("%Y/%m/%d %H:%M:%S")), m_PayDesc, m_PaymentVal);
		SQL=_T("Insert into payment (PaymentID, LicID, PaymentNo, PayDate, Description, Amount) ") +SQL;
		DB.ExecuteSQL(SQL);
		AddTrail(_Z("Add payment"),atol(ID)+1,"Payment");
	}
	else
	{
		AfxMessageBox(_Z("This payment number is duplicate!"));
	}
	DB.Close();
	CDialog::OnOK();
}

BOOL CPaymentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString Value;
	CTime Today =CTime::GetCurrentTime();
	Value.Format(_T("%04d-%02d-%02d"),Today.GetYear(),Today.GetMonth(),Today.GetDay());
	m_PayDate=Today;
	UpdateData(false);
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPaymentDlg::AddTrail(CString Action, long RecordID, CString Table)
{
	//CRecordset m_rs;
	//CDBVariant TempVar;
	CDatabase DB;
	CString UserName=m_UserName;
	CTime Date=CTime::GetCurrentTime();
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	CString temp,
		m_Tbl="INSERT INTO Audit ( UserName, [DateTime], [Action], Record, [Table] ) SELECT \'";
	m_Tbl+= UserName +"\' as Expr1, \'";
	m_Tbl+= Date.Format("%c") + "\' AS Expr2, \'";
	m_Tbl+= Action + "\' AS Expr3, ";
	temp.Format("%ld",RecordID);
	m_Tbl+= temp + " AS Expr4, \'";
	m_Tbl+= Table + "\' AS Expr5";
	//m_rs.m_pDatabase=pDB;
	DB.ExecuteSQL(m_Tbl);
	DB.Close();
	//m_rs.Open( CRecordset::dynaset, m_Tbl);
}