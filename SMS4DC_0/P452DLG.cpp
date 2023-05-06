// P452DLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "P452DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CP452DLG dialog


CP452DLG::CP452DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CP452DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP452DLG)
	m_beta_e = 1.35;
	m_dN = 45.0;
	m_N0 = 330.0;
	m_time = 50.0;
	m_Pressure = 1013;
	m_TempC = 15;
	//}}AFX_DATA_INIT
}


void CP452DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP452DLG)
	DDX_Control(pDX, IDC_COMBO_Clutter, m_Clutter);
	DDX_Text(pDX, IDC_EDIT_beta_e, m_beta_e);
	DDV_MinMaxDouble(pDX, m_beta_e, 0., 1000000000.);
	DDX_Text(pDX, IDC_EDIT_dN, m_dN);
	DDV_MinMaxDouble(pDX, m_dN, 0., 1000000000.);
	DDX_Text(pDX, IDC_EDIT_N0, m_N0);
	DDV_MinMaxDouble(pDX, m_N0, 0., 1000000000.);
	DDX_Text(pDX, IDC_EDIT_time, m_time);
	DDV_MinMaxDouble(pDX, m_time, 9.9e-004, 50.);
	DDX_Text(pDX, IDC_EDIT_Pressure, m_Pressure);
	DDX_Text(pDX, IDC_EDIT_TempC, m_TempC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP452DLG, CDialog)
	//{{AFX_MSG_MAP(CP452DLG)
	ON_CBN_SELCHANGE(IDC_COMBO_Clutter, OnSelchangeCOMBOClutter)
	ON_BN_CLICKED(IDC_RADIO1_Av, OnRADIO1Av)
	ON_BN_CLICKED(IDC_RADIO1_Wo, OnRADIO1Wo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP452DLG message handlers

BOOL CP452DLG::OnInitDialog() 
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

	((CButton*)GetDlgItem(IDC_RADIO1_Av))->SetWindowText(_Z("Average Year Prediction"));
	((CButton*)GetDlgItem(IDC_RADIO1_Wo))->SetWindowText(_Z("Worst-Month Prediction"));
	((CButton*)GetDlgItem(IDC_RADIO1_Av))->SetCheck(true);
	m_flagAvWo = 0;


	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CP452DLG::OnSelchangeCOMBOClutter() 
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

void CP452DLG::OnRADIO1Av() 
{
	BOOL i = ((CButton*)GetDlgItem(IDC_RADIO1_Av))->GetCheck();
	if(i==1)
	{
		((CButton*)GetDlgItem(IDC_RADIO1_Wo))->SetCheck(false);
		m_flagAvWo = 0;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO1_Wo))->SetCheck(true);
		m_flagAvWo = 1;
	}
}
void CP452DLG::OnRADIO1Wo() 
{
	OnRADIO1Av();
}
