// HorizonElevationDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "HorizonElevationDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHorizonElevationDLG dialog


CHorizonElevationDLG::CHorizonElevationDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CHorizonElevationDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHorizonElevationDLG)
	m_ES_Altitude = 0.0;
	m_D_max = 15.0;
	m_k = _T("4/3");
	m_Earth_radius_km = 6371.0;
	//}}AFX_DATA_INIT
}


void CHorizonElevationDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHorizonElevationDLG)
	DDX_Text(pDX, IDC_EDIT_ES_Altitude, m_ES_Altitude);
	DDX_Text(pDX, IDC_EDIT_D_max, m_D_max);
	DDX_Text(pDX, IDC_EDIT_k, m_k);
	DDX_Text(pDX, IDC_EDIT_Earth_radius_km, m_Earth_radius_km);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHorizonElevationDLG, CDialog)
	//{{AFX_MSG_MAP(CHorizonElevationDLG)
	ON_BN_CLICKED(IDC_RADIO_1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO_5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO_10, OnRadio10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHorizonElevationDLG message handlers

BOOL CHorizonElevationDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CButton *x1 =  (CButton *)GetDlgItem(IDC_RADIO_1);			x1->SetCheck(m_Azimuth_Step_Deg==1);
	CButton *x2 =  (CButton *)GetDlgItem(IDC_RADIO_5);			x2->SetCheck(m_Azimuth_Step_Deg==5);
	CButton *x3 =  (CButton *)GetDlgItem(IDC_RADIO_10);			x3->SetCheck(m_Azimuth_Step_Deg==10);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}


void CHorizonElevationDLG::OnRadio1() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_RADIO_1);			int i1 = x1->GetCheck();
	CButton *x2 =  (CButton *)GetDlgItem(IDC_RADIO_5);			int i2 = x2->GetCheck();
	CButton *x3 =  (CButton *)GetDlgItem(IDC_RADIO_10);			int i3 = x3->GetCheck();
	if(i1==1)		m_Azimuth_Step_Deg = 1;
	if(i2==1)		m_Azimuth_Step_Deg = 5;
	if(i3==1)		m_Azimuth_Step_Deg = 10;
}
void CHorizonElevationDLG::OnRadio5() 
{
	OnRadio1();
}
void CHorizonElevationDLG::OnRadio10() 
{
	OnRadio1();
}

