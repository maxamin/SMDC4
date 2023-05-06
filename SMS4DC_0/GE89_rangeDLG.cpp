// GE89_rangeDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "GE89_rangeDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGE89_rangeDLG dialog


CGE89_rangeDLG::CGE89_rangeDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CGE89_rangeDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGE89_rangeDLG)
	m_D = 800.0;
	m_Emin = 47.0;
	m_T = 1.0;
	m_L = 50.0;
	m_DH = 50.0;
	m_DHflag = FALSE;
	m_kfactor = _T("4/3");
	m_kflag = FALSE;
	m_PRflag = FALSE;
	m_PR = 0.0;
	//}}AFX_DATA_INIT
	m_label1 = _T("Minimum Field Strength(dBuV/m)");

	m_kfactorD = 4.0/3.0;
}


void CGE89_rangeDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGE89_rangeDLG)
	DDX_Text(pDX, IDC_EDIT_D, m_D);
	DDV_MinMaxDouble(pDX, m_D, 1., 1500.);
	DDX_Text(pDX, IDC_EDIT_Emin, m_Emin);
	DDX_Text(pDX, IDC_EDIT_T, m_T);
	DDV_MinMaxDouble(pDX, m_T, 1., 50.);
	DDX_Text(pDX, IDC_EDIT_L, m_L);
	DDV_MinMaxDouble(pDX, m_L, 1., 99.);
	DDX_Text(pDX, IDC_EDIT_DH, m_DH);
	DDV_MinMaxDouble(pDX, m_DH, 1., 10000000.);
	DDX_Check(pDX, IDC_CHECK_DHflag, m_DHflag);
	DDX_Text(pDX, IDC_EDIT_k, m_kfactor);
	DDX_Text(pDX, IDC_EDIT_kflag, m_kflag);
	DDX_Text(pDX, IDC_EDIT_PRflag, m_PRflag);
	DDX_Text(pDX, IDC_EDIT_Pr, m_PR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGE89_rangeDLG, CDialog)
	//{{AFX_MSG_MAP(CGE89_rangeDLG)
	ON_BN_CLICKED(IDC_CHECK_DHflag, OnCHECKDHflag)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_EN_CHANGE(IDC_EDIT_k, OnChangeEDITk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGE89_rangeDLG message handlers

void CGE89_rangeDLG::OnCHECKDHflag() 
{
	UpdateData(true);
	if(m_DHflag)
	{
		GetDlgItem(IDC_STATIC_DH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DH)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_DH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DH)->ShowWindow(SW_SHOW);
	}
	UpdateData(false);	
}

void CGE89_rangeDLG::OnRadio1() 
{
	UpdateData();	
	CButton * xx;  xx = (CButton *)GetDlgItem(IDC_RADIO1);
	BOOL I = xx->GetCheck();
	if(I)
		m_T = 1;
	UpdateData(false);	
}

void CGE89_rangeDLG::OnRadio2() 
{
	UpdateData();	
	CButton * xx;  xx = (CButton *)GetDlgItem(IDC_RADIO2);
	BOOL I = xx->GetCheck();
	if(I)
		m_T = 10;
	UpdateData(false);	
}

void CGE89_rangeDLG::OnRadio3() 
{
	UpdateData();	
	CButton * xx;  xx = (CButton *)GetDlgItem(IDC_RADIO3);
	BOOL I = xx->GetCheck();
	if(I)
		m_T = 50;
	UpdateData(false);	
}

BOOL CGE89_rangeDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CButton * xx;
	if(m_T == 1)
	{
		xx = (CButton *)GetDlgItem(IDC_RADIO1);
		xx->SetCheck(TRUE);
	}
	else if(m_T == 10)
	{
		xx = (CButton *)GetDlgItem(IDC_RADIO2);
		xx->SetCheck(TRUE);
	}
	else if(m_T == 50)
	{
		xx = (CButton *)GetDlgItem(IDC_RADIO3);
		xx->SetCheck(TRUE);
	}
	
	CStatic * x;  x = (CStatic *)GetDlgItem(IDC_STATIC_label1);
	x->SetWindowText(m_label1);

	if(m_kflag)
	{
		CStatic * x1;	x1 = (CStatic *)GetDlgItem(IDC_STATIC_k);	x1->ShowWindow(m_kflag);
		CEdit * x2;		x2 = (CEdit *)GetDlgItem(IDC_EDIT_k);		x2->ShowWindow(m_kflag);
	}
	if(m_PRflag)
	{
		CStatic * x1;	x1 = (CStatic *)GetDlgItem(IDC_STATIC_PR);	x1->ShowWindow(m_PRflag);
		CEdit * x2;		x2 = (CEdit *)GetDlgItem(IDC_EDIT_Pr);		x2->ShowWindow(m_PRflag);
	}
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CGE89_rangeDLG::OnChangeEDITk() 
{
	UpdateData();	
	m_kfactorD = atof_kfactor(m_kfactor);
	UpdateData(false);	
}

double CGE89_rangeDLG::atof_kfactor(CString k1) 
{
	double k2 = 1.0;
	k1.Remove(' ');
	int n = k1.Find('/');
	if (n != -1)
	{
		int m = k1.GetLength();
		CString ss1 = k1.Left(n);
		CString ss2 = k1.Right(m-n-1);
		k2 = atof(ss1)/atof(ss2);
	}
	else
		k2 = atof(k1);

	return k2;
}
