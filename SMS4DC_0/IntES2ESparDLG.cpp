// IntES2ESparDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "IntES2ESparDLG.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntES2ESparDLG dialog


CIntES2ESparDLG::CIntES2ESparDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CIntES2ESparDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIntES2ESparDLG)
	m_beta = 1.35;
	m_D = 150.0;
	m_dN = 45.0;
	m_F = 20.0;
	m_N0 = 330.0;
	m_time = 0.0015;
	m_EDIT_Pol = 20.0;
	m_EDIT_uPr = 10.0;
	m_Pressure = 1013;
	m_TempC = 15;
	//}}AFX_DATA_INIT
}


void CIntES2ESparDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntES2ESparDLG)
	DDX_Control(pDX, IDC_COMBO_ClutterZ, m_Clutter);
	DDX_Text(pDX, IDC_EDIT_beta_e, m_beta);
	DDV_MinMaxDouble(pDX, m_beta, 0., 1000000000.);
	DDX_Text(pDX, IDC_EDIT_D, m_D);
	DDX_Text(pDX, IDC_EDIT_dN, m_dN);
	DDV_MinMaxDouble(pDX, m_dN, 0., 1000000000.);
	DDX_Text(pDX, IDC_EDIT_F, m_F);
	DDX_Text(pDX, IDC_EDIT_N0, m_N0);
	DDV_MinMaxDouble(pDX, m_N0, 0., 1000000000.);
	DDX_Text(pDX, IDC_EDIT_time, m_time);
	DDV_MinMaxDouble(pDX, m_time, 1.e-003, 50.);
	DDX_Text(pDX, IDC_EDIT_Pol, m_EDIT_Pol);
	DDX_Text(pDX, IDC_EDIT_uPr, m_EDIT_uPr);
	DDX_Text(pDX, IDC_EDIT_PressureZ, m_Pressure);
	DDX_Text(pDX, IDC_EDIT_TempCZ, m_TempC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIntES2ESparDLG, CDialog)
	//{{AFX_MSG_MAP(CIntES2ESparDLG)
	ON_BN_CLICKED(IDC_CHECK_uPr, OnCHECKuPr)
	ON_CBN_SELCHANGE(IDC_COMBO_ClutterZ, OnSelchangeCOMBOClutterZ)
	ON_BN_CLICKED(IDC_RADIO1_AvZ, OnRADIO1AvZ)
	ON_BN_CLICKED(IDC_RADIO1_WoZ, OnRADIO1WoZ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntES2ESparDLG message handlers

BOOL CIntES2ESparDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Clutter.AddString(_Z("High crop fields"));
	m_Clutter.AddString(_Z("Park land"));
	m_Clutter.AddString(_Z("Irregularly spaced sparse trees"));
	m_Clutter.AddString(_Z("Orchard (regularly spaced)"));
	m_Clutter.AddString(_Z("Sparse houses"));
	m_Clutter.AddString(_Z("Village centre"));
	m_Clutter.AddString(_Z("Deciduous trees (irregularly spaced)"));
	m_Clutter.AddString(_Z("Deciduous trees (regularly spaced)"));
	m_Clutter.AddString(_Z("Mixed tree forest"));
	m_Clutter.AddString(_Z("Coniferous trees (irregularly spaced)"));
	m_Clutter.AddString(_Z("Coniferous trees (regularly spaced)"));
	m_Clutter.AddString(_Z("Tropical rain forest"));
	m_Clutter.AddString(_Z("Suburban"));
	m_Clutter.AddString(_Z("Dense suburban"));
	m_Clutter.AddString(_Z("Urban"));
	m_Clutter.AddString(_Z("Dense urban"));
	m_Clutter.AddString(_Z("High-rise urban"));
	m_Clutter.AddString(_Z("Industrial zone"));
	m_Clutter.SetCurSel(0);
	m_ha_Clutter = 4.0;		m_dk_Clutter = 0.1;	

	((CButton*)GetDlgItem(IDC_RADIO1_AvZ))->SetWindowText(_Z("Average Year Prediction"));
	((CButton*)GetDlgItem(IDC_RADIO1_WoZ))->SetWindowText(_Z("Worst-Month Prediction"));
	((CButton*)GetDlgItem(IDC_RADIO1_AvZ))->SetCheck(true);
	m_flagAvWo = 0;

	m_uPr = FALSE;

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}


void CIntES2ESparDLG::OnCHECKuPr() 
{
	CButton *x1 = (CButton *)GetDlgItem(IDC_CHECK_uPr);
	BOOL u = x1->GetCheck();
	CWnd *x2;
	x2 = GetDlgItem(IDC_EDIT_uPr);		x2->EnableWindow(u);
	m_uPr = u;
}

void CIntES2ESparDLG::OnSelchangeCOMBOClutterZ() 
{
	UpdateData();
	int i = m_Clutter.GetCurSel();
	if(i<5)	        {		m_ha_Clutter = 4.0;		m_dk_Clutter = 0.1;		}
	else if(i==5)	{		m_ha_Clutter = 5.0;		m_dk_Clutter = 0.07;	}
	else if(i==6)	{		m_ha_Clutter = 15.0;	m_dk_Clutter = 0.05;	}
	else if(i==7)	{		m_ha_Clutter = 15.0;	m_dk_Clutter = 0.05;	}
	else if(i==8)	{		m_ha_Clutter = 15.0;	m_dk_Clutter = 0.05;	}
	else if(i==9)	{		m_ha_Clutter = 20.0;	m_dk_Clutter = 0.05;	}
	else if(i==10)	{		m_ha_Clutter = 20.0;	m_dk_Clutter = 0.05;	}
	else if(i==11)	{		m_ha_Clutter = 20.0;	m_dk_Clutter = 0.03;	}
	else if(i==12)	{		m_ha_Clutter = 9.0;		m_dk_Clutter = 0.025;	}
	else if(i==13)	{		m_ha_Clutter = 12.0;	m_dk_Clutter = 0.02;	}
	else if(i==14)	{		m_ha_Clutter = 20.0;	m_dk_Clutter = 0.02;	}
	else if(i==15)	{		m_ha_Clutter = 25.0;	m_dk_Clutter = 0.02;	}
	else if(i==16)	{		m_ha_Clutter = 35.0;	m_dk_Clutter = 0.02;	}
	else if(i==17)	{		m_ha_Clutter = 20.0;	m_dk_Clutter = 0.05;	}
	UpdateData(false);
}

void CIntES2ESparDLG::OnRADIO1AvZ() 
{
	BOOL i = ((CButton*)GetDlgItem(IDC_RADIO1_AvZ))->GetCheck();
	if(i==1)
	{
		((CButton*)GetDlgItem(IDC_RADIO1_WoZ))->SetCheck(false);
		m_flagAvWo = 0;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO1_WoZ))->SetCheck(true);
		m_flagAvWo = 1;
	}
}


void CIntES2ESparDLG::OnRADIO1WoZ() 
{
	OnRADIO1AvZ();
}
