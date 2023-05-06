// GE06cvaDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "GE06cvaDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGE06cvaDLG dialog


CGE06cvaDLG::CGE06cvaDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CGE06cvaDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGE06cvaDLG)
	m_Emed = 0.0;
	m_SR = 400.0;
	m_L = 0.0;
	m_Fr = 8.0;
	m_Ti = 1.0;
	//}}AFX_DATA_INIT
	m_AntDisc = 0;
	m_DP = 1;
	m_AP = 1;
	m_OS = 1;
	m_env = 0;
//	m_srv = 0;
	m_CSdisplay = 0;
	m_CSdisplay1 = 0;
}


void CGE06cvaDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGE06cvaDLG)
	DDX_Control(pDX, IDC_environment, m_environment);
	DDX_Text(pDX, IDC_EDIT_Emed, m_Emed);
	DDX_Text(pDX, IDC_EDIT_SR, m_SR);
	DDV_MinMaxDouble(pDX, m_SR, 0., 1500.);
	DDX_Text(pDX, IDC_EDIT_L, m_L);
	DDV_MinMaxDouble(pDX, m_L, 1., 99.);
	DDX_Text(pDX, IDC_EDIT_Fr, m_Fr);
	DDX_Text(pDX, IDC_EDIT_Ti, m_Ti);
	DDV_MinMaxDouble(pDX, m_Ti, 1., 50.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGE06cvaDLG, CDialog)
	//{{AFX_MSG_MAP(CGE06cvaDLG)
	ON_BN_CLICKED(IDC_CHECK_AntDisc, OnCHECKAntDisc)
	ON_BN_CLICKED(IDC_CHECK_DP, OnCheckDp)
	ON_BN_CLICKED(IDC_CHECK_AP, OnCheckAp)
	ON_BN_CLICKED(IDC_CHECK_OS, OnCheckOs)
	ON_CBN_SELCHANGE(IDC_environment, OnSelchangeenvironment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGE06cvaDLG message handlers

BOOL CGE06cvaDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CButton *x1 =  (CButton *)GetDlgItem(IDC_CHECK_AntDisc);	x1->SetCheck(m_AntDisc==1);
	CButton *x2 =  (CButton *)GetDlgItem(IDC_CHECK_DP);			x2->SetCheck(m_DP==1);
	CButton *x3 =  (CButton *)GetDlgItem(IDC_CHECK_AP);			x3->SetCheck(m_AP==1);
	CButton *x4 =  (CButton *)GetDlgItem(IDC_CHECK_OS);			x4->SetCheck(m_OS==1);

	CButton *x5 =  (CButton *)GetDlgItem(IDC_EDIT_SR);
	CButton *x6 =  (CButton *)GetDlgItem(IDC_STATIC_SR);
	CButton *x7 =  (CButton *)GetDlgItem(IDC_EDIT_Fr);
	CButton *x8 =  (CButton *)GetDlgItem(IDC_STATIC_Fr);
	CButton *x9 =  (CButton *)GetDlgItem(IDC_EDIT_Ti);
	CButton *x10 =  (CButton *)GetDlgItem(IDC_STATIC_Ti);
//	CButton *x11 =  (CButton *)GetDlgItem(IDC_system);
//	CButton *x12 =  (CButton *)GetDlgItem(IDC_STATIC_system);

	CButton *x13 =  (CButton *)GetDlgItem(IDC_EDIT_L);
	CButton *x14 =  (CButton *)GetDlgItem(IDC_STATIC_L);
	CButton *x15 =  (CButton *)GetDlgItem(IDC_EDIT_Emed);
	CButton *x16 =  (CButton *)GetDlgItem(IDC_STATIC_Emed);

	x1->EnableWindow(m_CSdisplay==0);
	x2->EnableWindow(m_CSdisplay==0);
	x3->EnableWindow(m_CSdisplay==0);
	x4->EnableWindow(m_CSdisplay==0);
	x5->EnableWindow(m_CSdisplay==0);
	x6->EnableWindow(m_CSdisplay==0);
	x7->EnableWindow(m_CSdisplay==0);
	x8->EnableWindow(m_CSdisplay==0);
	x9->EnableWindow(m_CSdisplay==0);
	x10->EnableWindow(m_CSdisplay==0);
//	x11->EnableWindow(m_CSdisplay==0);
//	x12->EnableWindow(m_CSdisplay==0);

	x13->EnableWindow(m_CSdisplay1==0);
	x14->EnableWindow(m_CSdisplay1==0);
	x15->EnableWindow(m_CSdisplay1==0);
	x16->EnableWindow(m_CSdisplay1==0);

	m_environment.AddString(_Z("Open Area"));
	m_environment.AddString(_Z("Rural Area"));
	m_environment.AddString(_Z("SubUrban Area"));
	m_environment.AddString(_Z("Urban Area"));
	m_environment.AddString(_Z("Dense Urban Area"));
	m_environment.SetTopIndex(1);
	m_environment.SetCurSel(m_env);	

//	m_system.AddString(_Z("Mobile, Urban"));
//	m_system.AddString(_Z("Mobile, SubUrban, Rolling hills"));
//	m_system.SetTopIndex(1);
//	m_system.SetCurSel(m_srv);	

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CGE06cvaDLG::OnCHECKAntDisc() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_CHECK_AntDisc);	m_AntDisc = x1->GetCheck();
}
void CGE06cvaDLG::OnCheckDp() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_CHECK_DP);			m_DP = x1->GetCheck();
}
void CGE06cvaDLG::OnCheckAp() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_CHECK_AP);			m_AP = x1->GetCheck();
}
void CGE06cvaDLG::OnCheckOs() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_CHECK_OS);			m_OS = x1->GetCheck();
}

void CGE06cvaDLG::OnSelchangeenvironment() 
{
	UpdateData(true);
	m_env = m_environment.GetCurSel();
	UpdateData(false);
}

