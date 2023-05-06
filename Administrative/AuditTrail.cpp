#include "AuditTrail.h"
#include "test6.h"

void AddTrail(CString Action, long RecordID, CString Table)
{
	//CRecordset m_rs;
	//CDBVariant TempVar;
	CDatabase DB;
	CString UserName=((CSMS4DCApp *)AfxGetApp())->m_UserName;
	CTime Date=CTime::GetCurrentTime();
	DB.Open(((CSMS4DCApp *)AfxGetApp())->m_CDBSTR,false,false,_T("ODBC;"),false);
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