// P1546DLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "P1546DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CP1546DLG dialog


CP1546DLG::CP1546DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CP1546DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP1546DLG)
	m_Clangle = FALSE;
	m_landsea = FALSE;
	m_k = 1.3333333333;
	m_env = 3;
	m_location = 50.0;
	m_RxH = 3.0;
	m_syst = 2;
	m_time = 50.0;
	m_RxShow = TRUE;
	m_Cvalue = -10.0;
	m_CvShow = FALSE;
	//}}AFX_DATA_INIT
	
	m_Monitoring = false;		//990428
}


void CP1546DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP1546DLG)
	DDX_Control(pDX, IDC_system, m_system);
	DDX_Control(pDX, IDC_environment, m_environment);
	DDX_Check(pDX, IDC_CHECK_Clangle, m_Clangle);
	DDX_Check(pDX, IDC_CHECK_landsea, m_landsea);
	DDX_Text(pDX, IDC_EDIT_earth, m_k);
	DDX_Text(pDX, IDC_EDIT_env, m_env);
	DDX_Text(pDX, IDC_EDIT_location, m_location);
	DDV_MinMaxDouble(pDX, m_location, 1., 99.);
	DDX_Text(pDX, IDC_EDIT_RxH, m_RxH);
	DDX_Text(pDX, IDC_EDIT_syst, m_syst);
	DDX_Text(pDX, IDC_EDIT_time, m_time);
	DDV_MinMaxDouble(pDX, m_time, 1., 50.);
	DDX_Text(pDX, IDC_EDIT_RxShow, m_RxShow);
	DDX_Text(pDX, IDC_EDIT_Cvalue, m_Cvalue);
	DDX_Text(pDX, IDC_EDIT_CvShow, m_CvShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP1546DLG, CDialog)
	//{{AFX_MSG_MAP(CP1546DLG)
	ON_CBN_SELCHANGE(IDC_system, OnSelchangesystem)
	ON_CBN_SELCHANGE(IDC_environment, OnSelchangeenvironment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP1546DLG message handlers

BOOL CP1546DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(true);

	m_system.AddString(_Z("Broadcasting, Analogue"));
	m_system.AddString(_Z("Broadcasting, Digital"));
	m_system.AddString(_Z("Mobile, Urban"));
	m_system.AddString(_Z("Mobile, SubUrban, Rolling hills"));
	m_system.SetTopIndex(1);
	m_system.SetCurSel(2);	

	m_environment.AddString(_Z("Open Area"));
	m_environment.AddString(_Z("Rural Area"));
	m_environment.AddString(_Z("SubUrban Area"));
	m_environment.AddString(_Z("Urban Area"));
	m_environment.AddString(_Z("Dense Urban Area"));
//	m_environment.AddString(_Z("Cold Sea (North Sea)"));
//	m_environment.AddString(_Z("Warm Sea (Mediterranean Sea)"));
	m_environment.SetTopIndex(1);
	m_environment.SetCurSel(3);	
	
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
		GetDlgItem(IDC_STATIC_Cvalue)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Cvalue)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CHECK_Clangle)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_Cvalue)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Cvalue)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK_Clangle)->ShowWindow(SW_SHOW);
	}

	if(m_Monitoring == TRUE)
	{
		GetDlgItem(IDC_STATIC_Cvalue)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Cvalue)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_RxH)->SetWindowText(_Z("Transmitter Height(m)"));
		GetDlgItem(IDC_STATIC_Cvalue)->SetWindowText(_Z("Transmitter Power(W)"));
	}


	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CP1546DLG::OnSelchangesystem() 
{
	UpdateData(true);
	m_syst=m_system.GetCurSel();
	UpdateData(false);
}

void CP1546DLG::OnSelchangeenvironment() 
{
	UpdateData(true);
	m_env=m_environment.GetCurSel();
	UpdateData(false);
}
