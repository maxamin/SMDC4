// GE06srvDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "GE06srvDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGE06srvDLG dialog


CGE06srvDLG::CGE06srvDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CGE06srvDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGE06srvDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_EXA = 1;
	m_LNB = 1;
	m_AZstep = 60;
	m_UD = 0;
	m_UDdisplay = 1;
}

void CGE06srvDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGE06srvDLG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGE06srvDLG, CDialog)
	//{{AFX_MSG_MAP(CGE06srvDLG)
	ON_BN_CLICKED(IDC_RADIO_EXA, OnRadioExa)
	ON_BN_CLICKED(IDC_RADIO_NA, OnRadioNa)
	ON_BN_CLICKED(IDC_CHECK_LNB, OnCheckLnb)
	ON_BN_CLICKED(IDC_RADIO_6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO_12, OnRadio12)
	ON_BN_CLICKED(IDC_RADIO_36, OnRadio36)
	ON_BN_CLICKED(IDC_CHECK_UD, OnCheckUd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGE06srvDLG message handlers

BOOL CGE06srvDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CButton *x1 =  (CButton *)GetDlgItem(IDC_RADIO_EXA);		x1->SetCheck(m_EXA==1);
	CButton *x2 =  (CButton *)GetDlgItem(IDC_RADIO_NA);			x2->SetCheck(m_EXA==0);
	CButton *x3 =  (CButton *)GetDlgItem(IDC_CHECK_LNB);		x3->SetCheck(m_LNB==1);
	CButton *x4 =  (CButton *)GetDlgItem(IDC_RADIO_6);			x4->SetCheck(m_AZstep==60);
	CButton *x5 =  (CButton *)GetDlgItem(IDC_RADIO_12);			x5->SetCheck(m_AZstep==30);
	CButton *x6 =  (CButton *)GetDlgItem(IDC_RADIO_36);			x6->SetCheck(m_AZstep==10);
	
	CButton *x7 =  (CButton *)GetDlgItem(IDC_CHECK_UD);			x7->SetCheck(m_UD==1);
																x7->EnableWindow(m_UDdisplay);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CGE06srvDLG::OnRadioExa() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_RADIO_EXA);	m_EXA = x1->GetCheck();
}
void CGE06srvDLG::OnRadioNa() 
{
	OnRadioExa();
}
void CGE06srvDLG::OnCheckLnb() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_CHECK_LNB);	m_LNB = x1->GetCheck();	
}

void CGE06srvDLG::OnRadio6() 
{
	CButton *x1 =  (CButton *)GetDlgItem(IDC_RADIO_6);			int i1 = x1->GetCheck();
	CButton *x2 =  (CButton *)GetDlgItem(IDC_RADIO_12);			int i2 = x2->GetCheck();
	CButton *x3 =  (CButton *)GetDlgItem(IDC_RADIO_36);			int i3 = x3->GetCheck();
	if(i1==1)		m_AZstep = 60;
	if(i2==1)		m_AZstep = 30;
	if(i3==1)		m_AZstep = 10;
}
void CGE06srvDLG::OnRadio12() 
{
	OnRadio6();
}
void CGE06srvDLG::OnRadio36() 
{
	OnRadio6();
}

void CGE06srvDLG::OnCheckUd() 
{
	CButton *x7 =  (CButton *)GetDlgItem(IDC_CHECK_UD);			m_UD = x7->GetCheck();

	CButton *x1 =  (CButton *)GetDlgItem(IDC_RADIO_EXA);		x1->EnableWindow(!m_UD);
	CButton *x2 =  (CButton *)GetDlgItem(IDC_RADIO_NA);			x2->EnableWindow(!m_UD);
	CButton *x3 =  (CButton *)GetDlgItem(IDC_CHECK_LNB);		x3->EnableWindow(!m_UD);
	CButton *x4 =  (CButton *)GetDlgItem(IDC_RADIO_6);			x4->EnableWindow(!m_UD);
	CButton *x5 =  (CButton *)GetDlgItem(IDC_RADIO_12);			x5->EnableWindow(!m_UD);
	CButton *x6 =  (CButton *)GetDlgItem(IDC_RADIO_36);			x6->EnableWindow(!m_UD);
}
