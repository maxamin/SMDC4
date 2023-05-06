// ESAntPat.cpp : implementation file
//

#include "stdafx.h"
#include "administrative.h"
#include "ESAntPat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CESAntPat dialog


CESAntPat::CESAntPat(CWnd* pParent /*=NULL*/)
	: CDialog(CESAntPat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CESAntPat)
	//m_CoeffA = 0.0;
	//m_CoeffB = 0.0;
	//m_CoeffC = 0.0;
	//m_CoeffD = 0.0;
	m_AntPatt = _T("");
	//m_Phi1 = 0.0;
	//}}AFX_DATA_INIT
}


void CESAntPat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CESAntPat)
	DDX_Text(pDX, IDC_ER, m_ER);
	DDX_Text(pDX, IDC_CoeffA, m_CoeffA);
	DDX_Text(pDX, IDC_CoeffB, m_CoeffB);
	DDX_Text(pDX, IDC_CoeffC, m_CoeffC);
	DDX_Text(pDX, IDC_CoeffD, m_CoeffD);
	DDX_Text(pDX, IDC_ESAntPatt, m_AntPatt);
	DDX_Text(pDX, IDC_Phi1, m_Phi1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CESAntPat, CDialog)
	//{{AFX_MSG_MAP(CESAntPat)
	ON_BN_CLICKED(IDC_PATTERN, OnPattern)
	ON_BN_CLICKED(IDC_COEFF, OnCoeff)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CESAntPat message handlers

void CESAntPat::OnPattern() 
{
	((CEdit *)GetDlgItem(IDC_ESAntPatt))->EnableWindow(true);
	((CEdit *)GetDlgItem(IDC_CoeffA))->EnableWindow(true);
	((CEdit *)GetDlgItem(IDC_CoeffB))->EnableWindow(true);
	((CEdit *)GetDlgItem(IDC_CoeffC))->EnableWindow(true);
	((CEdit *)GetDlgItem(IDC_CoeffD))->EnableWindow(true);
	((CEdit *)GetDlgItem(IDC_Phi1))->EnableWindow(true);
}

void CESAntPat::OnCoeff() 
{
	((CEdit *)GetDlgItem(IDC_ESAntPatt))->EnableWindow(false);
	((CEdit *)GetDlgItem(IDC_CoeffA))->EnableWindow(false);
	((CEdit *)GetDlgItem(IDC_CoeffB))->EnableWindow(false);
	((CEdit *)GetDlgItem(IDC_CoeffC))->EnableWindow(false);
	((CEdit *)GetDlgItem(IDC_CoeffD))->EnableWindow(false);
	((CEdit *)GetDlgItem(IDC_Phi1))->EnableWindow(false);
}

BOOL CESAntPat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CDatabase DB;
	CRecordset RS;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);

//	OnPattern();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CESAntPat::OnOK() 
{
	bool result=true;
//	if(((CButton *)GetDlgItem(IDC_PATTERN))->GetCheck()==BST_CHECKED)
//	{
//		if(m_AntPatt.IsEmpty()) result=false;
//		else
//		{
			CString SQL,ER,NewID;
			CDatabase DB;
			CRecordset RS;
			DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
			RS.m_pDatabase=&DB;
			SQL=_T("Select max(pattern_id)+1 from ant_type");
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,NewID);
			RS.Close();
			UpdateData(true);
			if(NewID.IsEmpty()) NewID=_T("1");
			SQL.Format(_T("insert into ant_type (pattern_id,f_ant_type,emi_rcp,pattern,coefa,coefb,coefc,coefd,phi1) select %s,'E','%s','%s',%s,%s,%s,%s,%s"),
				NewID,m_ER,m_AntPatt,(m_CoeffA.IsEmpty()?_T("NULL"):m_CoeffA),(m_CoeffB.IsEmpty()?_T("NULL"):m_CoeffB),
				(m_CoeffC.IsEmpty()?_T("NULL"):m_CoeffC),(m_CoeffD.IsEmpty()?_T("NULL"):m_CoeffD),(m_Phi1.IsEmpty()?_T("NULL"):m_Phi1));
			DB.ExecuteSQL(SQL);
			DB.Close();
//		}
//	}
//	if(((CButton *)GetDlgItem(IDC_COEFF))->GetCheck()==BST_CHECKED)
//	{
//	}
	CDialog::OnOK();
}
