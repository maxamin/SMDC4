// P370DLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "P370DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CP370DLG dialog


CP370DLG::CP370DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CP370DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP370DLG)
	m_time = 50.0;
	m_location = 50.0;
	m_k = 1.3333333333;
	m_RxH = 3.0;
	m_Clangle = FALSE;
	m_landsea = FALSE;
	m_env = 2;
	m_syst = 0;
	m_RxShow = TRUE;
	m_CvShow = FALSE;
	m_Cvalue = -10.0;
	m_DHflag = FALSE;
	m_DH = 50.0;
	//}}AFX_DATA_INIT
}


void CP370DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP370DLG)
	DDX_Control(pDX, IDC_environment, m_environment);
	DDX_Control(pDX, IDC_system, m_system);
	DDX_Text(pDX, IDC_EDIT_time, m_time);
	DDV_MinMaxDouble(pDX, m_time, 1., 50.);
	DDX_Text(pDX, IDC_EDIT_location, m_location);
	DDV_MinMaxDouble(pDX, m_location, 1., 99.);
	DDX_Text(pDX, IDC_EDIT_earth, m_k);
	DDX_Text(pDX, IDC_EDIT_RxH, m_RxH);
	DDV_MinMaxDouble(pDX, m_RxH, 0., 1000.);
	DDX_Check(pDX, IDC_CHECK_Clangle, m_Clangle);
	DDX_Check(pDX, IDC_CHECK_landsea, m_landsea);
	DDX_Text(pDX, IDC_EDIT_env, m_env);
	DDV_MinMaxInt(pDX, m_env, 0, 4);
	DDX_Text(pDX, IDC_EDIT_syst, m_syst);
	DDV_MinMaxInt(pDX, m_syst, 0, 1);
	DDX_Text(pDX, IDC_EDIT_RxShow, m_RxShow);
	DDX_Text(pDX, IDC_EDIT_CvShow, m_CvShow);
	DDX_Text(pDX, IDC_EDIT_Cvalue, m_Cvalue);
	DDX_Check(pDX, IDC_CHECK_DHflag, m_DHflag);
	DDX_Text(pDX, IDC_EDIT_DH, m_DH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP370DLG, CDialog)
	//{{AFX_MSG_MAP(CP370DLG)
	ON_CBN_SELCHANGE(IDC_system, OnSelchangesystem)
	ON_CBN_SELCHANGE(IDC_environment, OnSelchangeenvironment)
	ON_BN_CLICKED(IDC_CHECK_DHflag, OnCHECKDHflag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP370DLG message handlers

BOOL CP370DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(true);

	m_system.AddString(_Z("Analogue"));
	m_system.AddString(_Z("Digital"));
	m_system.SetTopIndex(1);
	m_system.SetCurSel(0);	

	m_environment.AddString(_Z("Rural Area"));
	m_environment.AddString(_Z("SubUrban Area"));
	m_environment.AddString(_Z("Urban Area"));
//	m_environment.AddString(_Z("Cold Sea (North Sea)"));
//	m_environment.AddString(_Z("Warm Sea (Mediterranean Sea)"));
	m_environment.SetTopIndex(1);
	m_environment.SetCurSel(2);	

	if(m_RxShow == TRUE)
	{
		GetDlgItem(IDC_EDIT_RxH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_RxH)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_EDIT_RxH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_RxH)->ShowWindow(SW_HIDE);
	}

	if(m_CvShow == TRUE)
	{
		GetDlgItem(IDC_CHECK_DHflag)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_Cvalue)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Cvalue)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CHECK_Clangle)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_DHflag)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_Cvalue)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Cvalue)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK_Clangle)->ShowWindow(SW_SHOW);
	}
	UpdateData(false);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CP370DLG::OnSelchangesystem() 
{
	UpdateData(true);
	m_syst=m_system.GetCurSel();
	UpdateData(false);
}

void CP370DLG::OnSelchangeenvironment() 
{
	UpdateData(true);
	m_env=m_environment.GetCurSel();
	UpdateData(false);
	
}

void CP370DLG::OnCHECKDHflag() 
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
