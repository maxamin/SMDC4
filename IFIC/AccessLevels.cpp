// AccessLevels.cpp : implementation file
//

#include "stdafx.h"
#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS
#include "Resource.h"
#include "AccessLevels.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccessLevels dialog


CAccessLevels::CAccessLevels(CWnd* pParent /*=NULL*/)
	: CDialog(CAccessLevels::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccessLevels)
	m_PassAdd = _T("");
	m_PassMod = _T("");
	m_UserAdd = _T("");
	m_Enabled = FALSE;
	//}}AFX_DATA_INIT
}


void CAccessLevels::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccessLevels)
	DDX_Control(pDX, IDC_USERMOD, m_UserMod);
	DDX_Control(pDX, IDC_ACCESSLEVEL, m_AccessLevel);
	DDX_Text(pDX, IDC_PASSADD, m_PassAdd);
	DDX_Text(pDX, IDC_PASSMOD, m_PassMod);
	DDX_Text(pDX, IDC_USERADD, m_UserAdd);
	DDX_Check(pDX, IDC_ENABLED, m_Enabled);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccessLevels, CDialog)
	//{{AFX_MSG_MAP(CAccessLevels)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(ID_SAVE, OnSave)
	ON_BN_CLICKED(ID_DELETE, OnDelete)
	ON_CBN_SELCHANGE(IDC_USERMOD, OnSelchangeUsermod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccessLevels message handlers


BOOL CAccessLevels::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString m_Tbl;
	CDatabase DB;
	CRecordset RS;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	m_Tbl.Format(_T("select [Level],Description%s from Levels"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_AccessLevel.ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_AccessLevel.AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Tbl=_T("select * from Users");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_UserMod.ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)1,F2);
		m_UserMod.AddString(F2);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	((CButton *)GetDlgItem(IDC_NEW))->SetCheck(true);
	OnNew();
	TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAccessLevels::OnNew() 
{
	GetDlgItem(IDC_USERADD)->EnableWindow(true);
	GetDlgItem(IDC_PASSADD)->EnableWindow(true);
	GetDlgItem(IDC_USERMOD)->EnableWindow(false);
	GetDlgItem(IDC_PASSMOD)->EnableWindow(false);
	GetDlgItem(ID_DELETE)->EnableWindow(false);
}

void CAccessLevels::OnModify() 
{
	GetDlgItem(IDC_USERADD)->EnableWindow(false);
	GetDlgItem(IDC_PASSADD)->EnableWindow(false);
	GetDlgItem(IDC_USERMOD)->EnableWindow(true);
	GetDlgItem(IDC_PASSMOD)->EnableWindow(true);	
	GetDlgItem(ID_DELETE)->EnableWindow(true);
}

void CAccessLevels::OnSave() 
{
	CDatabase DB;
	CRecordset RS;
	CString SQL,Rep;
	UpdateData();
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	if(((CButton *)GetDlgItem(IDC_NEW))->GetCheck()==BST_CHECKED)
	{
		m_PassAdd.TrimLeft(_T(" "));
		m_PassAdd.TrimRight(_T(" "));
		if(m_PassAdd.IsEmpty())
		{
			MessageBox(_Z("Password cannot be empty!"));
			DB.Close();
			return;
		}
		SQL=_T("select count(ID) from Users where UserName='") + m_UserAdd + _T("'");
		RS.Open( CRecordset::snapshot, SQL);
		RS.GetFieldValue((short)0,Rep);
		RS.Close();
		if(atol(Rep)==0)
		{
			SQL=_T("select max(ID)+1 from Users");
			RS.Open( CRecordset::snapshot, SQL);
			RS.GetFieldValue((short)0,Rep);
			RS.Close();
			CString Lev;
			m_AccessLevel.GetWindowText(Lev);
			if(Lev.IsEmpty())
			{
				MessageBox(_Z("Please select a security level."));
				DB.Close();
				return;
			}
			SQL.Format(_T("insert into Users (ID, UserName, UserPassword, [Level], [Enabled]) select %s,'%s','%s',%s,%d"), 
				Rep, m_UserAdd, m_PassAdd, Lev.Left(1), m_Enabled);
			DB.ExecuteSQL(SQL);
			MessageBox(_Z("User defined successfully."));
		}
		else
		{
			MessageBox(_Z("Another user with the same name exists!"));
		}
	}
	if(((CButton *)GetDlgItem(IDC_MODIFY))->GetCheck()==BST_CHECKED)
	{
		CString Nam;
		m_PassMod.TrimLeft(_T(" "));
		m_PassMod.TrimRight(_T(" "));
		m_UserMod.GetWindowText(Nam);
		SQL.Format(_T("select ID from Users where UserName='%s'"),Nam);
		RS.Open( CRecordset::snapshot, SQL);
		RS.GetFieldValue((short)0,Rep);
		RS.Close();
		CString Lev;
		m_AccessLevel.GetWindowText(Lev);
		if(Lev.IsEmpty())
		{
			MessageBox(_Z("Please select a security level."));
			DB.Close();
			return;
		}
		if(m_PassMod.IsEmpty())
			SQL.Format(_T("Update Users set [Enabled]=%d,[Level]=%s where ID=%s"), m_Enabled,Lev.Left(1),Rep);
		else
			SQL.Format(_T("Update Users set [Enabled]=%d,[Level]=%s, UserPassword='%s' where ID=%s"), m_Enabled,Lev.Left(1),m_PassMod,Rep);
		DB.ExecuteSQL(SQL);
		MessageBox(_Z("User changed successfully."));
	}
	DB.Close();
	CDialog::OnOK();
}

void CAccessLevels::OnDelete() 
{
	CDatabase DB;
	CRecordset RS;
	CString SQL,Hist,str;
	UpdateData();
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	m_UserMod.GetWindowText(str);
	SQL=_T("select count(UserName) from Audit where UserName='") + str + _T("'");
	RS.Open( CRecordset::snapshot, SQL);
	RS.GetFieldValue((short)0,Hist);
	RS.Close();
	if(atol(Hist)==0)
	{
		SQL=_T("Delete * from Users where UserName='")+ str + _T("'");
		DB.ExecuteSQL(SQL);
	}
	else
	{
		AfxMessageBox(_Z("This user has some transaction history thus cannot be deleted!"));
	}
	DB.Close();
	CDialog::OnOK();
}

void CAccessLevels::OnOK()
{
}

void CAccessLevels::OnSelchangeUsermod() 
{
	CDatabase DB;
	CRecordset RS;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	CString Nam,SQL, En;
	m_UserMod.GetWindowText(Nam);
	SQL.Format(_T("select [Enabled],[Level] from Users where UserName='%s'"),Nam);
	RS.Open( CRecordset::snapshot, SQL);
	RS.GetFieldValue((short)0,En);
	RS.GetFieldValue((short)1,Nam);
	RS.Close();
	m_AccessLevel.SelectString(0,Nam);
	if(atoi(En)==1)
		((CButton *)GetDlgItem(IDC_ENABLED))->SetCheck(true);
	else
		((CButton *)GetDlgItem(IDC_ENABLED))->SetCheck(false);
	DB.Close();
	
}

void CAccessLevels::TranslateDialog(CDialog *pDialog)
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

CString CAccessLevels::GetTranslatedString(CString strOriginal, CString Lang)
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

