// GE06intDLG1.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "GE06intDLG1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGE06intDLG1 dialog


CGE06intDLG1::CGE06intDLG1(CWnd* pParent /*=NULL*/)
	: CDialog(CGE06intDLG1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGE06intDLG1)
	m_SR = 400.0;
	m_Ti = 1.0;
	m_LPM = 4.771;
	m_FR = 8.0;
	m_Lat = 0.0;
	m_Lon = 0.0;
	//}}AFX_DATA_INIT
	m_AntDisc = 0;
	m_env = 0;
	m_LPMstr = _Z("Protection Margin Limit (dB) :");
	m_FXMlocation = 0;
	m_FXMlocationDisp = 0;
//	m_srv = 0;
//	m_FXMDisp = 0;
}


void CGE06intDLG1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGE06intDLG1)
	DDX_Control(pDX, IDC_environment, m_environment);
	DDX_Text(pDX, IDC_EDIT_SR, m_SR);
	DDV_MinMaxDouble(pDX, m_SR, 0., 1500.);
	DDX_Text(pDX, IDC_EDIT_Ti, m_Ti);
	DDX_Text(pDX, IDC_EDIT_LPM, m_LPM);
	DDX_Text(pDX, IDC_EDIT_Fr, m_FR);
	DDX_Text(pDX, IDC_EDIT_Lat, m_Lat);
	DDX_Text(pDX, IDC_EDIT_Lon, m_Lon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGE06intDLG1, CDialog)
	//{{AFX_MSG_MAP(CGE06intDLG1)
	ON_BN_CLICKED(IDC_CHECK_AntDisc, OnCHECKAntDisc)
	ON_CBN_SELCHANGE(IDC_environment, OnSelchangeenvironment)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGE06intDLG1 message handlers

BOOL CGE06intDLG1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CButton *x1 =  (CButton *)GetDlgItem(IDC_CHECK_AntDisc);	x1->SetCheck(m_AntDisc==1);
	CStatic* xx1 = (CStatic*)GetDlgItem(IDC_STATIC_LPM);		xx1->SetWindowText(m_LPMstr);
	
	m_environment.AddString(_Z("Open Area"));
	m_environment.AddString(_Z("Rural Area"));
	m_environment.AddString(_Z("SubUrban Area"));
	m_environment.AddString(_Z("Urban Area"));
	m_environment.AddString(_Z("Dense Urban Area"));
	m_environment.SetTopIndex(1);
	m_environment.SetCurSel(m_env);	

	CButton *x2 =  (CButton *)GetDlgItem(IDC_RADIO1);		x2->EnableWindow(m_FXMlocationDisp);	x2->SetCheck(m_FXMlocation==0);
			 x2 =  (CButton *)GetDlgItem(IDC_RADIO2);		x2->EnableWindow(m_FXMlocationDisp);
			 x2 =  (CButton *)GetDlgItem(IDC_RADIO3);		x2->EnableWindow(m_FXMlocationDisp);

	CStatic* y1 = (CStatic*)GetDlgItem(IDC_STATIC_Lat);		y1->EnableWindow(m_FXMlocationDisp);
			 y1 = (CStatic*)GetDlgItem(IDC_STATIC_Lon);		y1->EnableWindow(m_FXMlocationDisp);
			 y1 = (CStatic*)GetDlgItem(IDC_STATIC_FXM);		y1->EnableWindow(m_FXMlocationDisp);
//			 y1 = (CStatic*)GetDlgItem(IDC_STATIC_system0);	y1->EnableWindow(m_FXMDisp);
	CEdit*	 y2 = (CEdit*)GetDlgItem(IDC_EDIT_Lat);			y2->EnableWindow(m_FXMlocationDisp);
			 y2 = (CEdit*)GetDlgItem(IDC_EDIT_Lon);			y2->EnableWindow(m_FXMlocationDisp);
//			 y2 = (CEdit*)GetDlgItem(IDC_system);			y2->EnableWindow(m_FXMDisp);

//	m_system.AddString(_Z("Mobile, Urban"));
//	m_system.AddString(_Z("Mobile, SubUrban, Rolling hills"));
//	m_system.SetTopIndex(1);
//	m_system.SetCurSel(m_srv);	

	OnRadio1();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CGE06intDLG1::OnCHECKAntDisc() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_CHECK_AntDisc);	m_AntDisc = x1->GetCheck();
}

void CGE06intDLG1::OnSelchangeenvironment() 
{
	UpdateData(true);
	m_env = m_environment.GetCurSel();
	UpdateData(false);	
}

void CGE06intDLG1::OnRadio1() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_RADIO1);	int i1 = x1->GetCheck();
			 x1 =  (CButton *)GetDlgItem(IDC_RADIO2);	int i2 = x1->GetCheck();
			 x1 =  (CButton *)GetDlgItem(IDC_RADIO3);	int i3 = x1->GetCheck();
	if	   (i1==1)	m_FXMlocation = 0;
	else if(i2==1)	m_FXMlocation = 1;
	else if(i3==1)	m_FXMlocation = 2;

	if(m_FXMlocation == 2)
	{
		CStatic* xx1 = (CStatic*)GetDlgItem(IDC_STATIC_Lat);		xx1->EnableWindow(TRUE);
				 xx1 = (CStatic*)GetDlgItem(IDC_STATIC_Lon);		xx1->EnableWindow(TRUE);
		CEdit*	 xx2 = (CEdit*)GetDlgItem(IDC_EDIT_Lat);			xx2->EnableWindow(TRUE);
				 xx2 = (CEdit*)GetDlgItem(IDC_EDIT_Lon);			xx2->EnableWindow(TRUE);
	}
	else
	{
		CStatic* xx1 = (CStatic*)GetDlgItem(IDC_STATIC_Lat);		xx1->EnableWindow(FALSE);
				 xx1 = (CStatic*)GetDlgItem(IDC_STATIC_Lon);		xx1->EnableWindow(FALSE);
		CEdit*	 xx2 = (CEdit*)GetDlgItem(IDC_EDIT_Lat);			xx2->EnableWindow(FALSE);
				 xx2 = (CEdit*)GetDlgItem(IDC_EDIT_Lon);			xx2->EnableWindow(FALSE);
	}
}
void CGE06intDLG1::OnRadio2() 
{
	OnRadio1() ;	
}
void CGE06intDLG1::OnRadio3() 
{
	OnRadio1() ;	
}
