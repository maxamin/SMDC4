// LoSDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "LoSDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoSDLG dialog


CLoSDLG::CLoSDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CLoSDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoSDLG)
	m_kfactor = 1.3333333333;
	m_RxH = 3.0;
	m_title = _Z("Line of Sight Model Parameters");
	m_Overlap = FALSE;
	m_Fd = 0.0;
	m_RPR = 0.0;
	//}}AFX_DATA_INIT
	m_title1 = _Z("Receiver Height_AGL (m)");
	m_overlapDisp = 0;
	m_FdDisp = 0;

	m_stepDisp = 0;
	m_step = 10;

	m_bcbtDisp = 0;
	m_bcbt = _T("DVB 8MHz");
	m_AntDisc = 0;

	m_Monitoring = false;		//990428
}


void CLoSDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoSDLG)
	DDX_Text(pDX, IDC_EDIT_kfactor, m_kfactor);
	DDX_Text(pDX, IDC_EDIT_RxH, m_RxH);
	DDV_MinMaxDouble(pDX, m_RxH, 0., 1500.);
	DDX_Text(pDX, IDC_EDIT_title, m_title);
	DDX_Check(pDX, IDC_CHECK_overlap, m_Overlap);
	DDX_Text(pDX, IDC_EDIT_Fd, m_Fd);
	DDX_Text(pDX, IDC_EDIT_RPR, m_RPR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoSDLG, CDialog)
	//{{AFX_MSG_MAP(CLoSDLG)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_CHECK_AntDisc, OnCHECKAntDisc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoSDLG message handlers

BOOL CLoSDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_title);

	CStatic* xx1;	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_Rx);		xx1->SetWindowText(m_title1);
	CButton* xx2;	xx2 = (CButton*)GetDlgItem(IDC_CHECK_overlap);	xx2->ShowWindow(m_overlapDisp);
	CEdit* xx3;		xx3 = (CEdit*)GetDlgItem(IDC_EDIT_Fd);			xx3->ShowWindow(m_FdDisp);
	CStatic* xx4;	xx4 = (CStatic*)GetDlgItem(IDC_STATIC_Fd);		xx4->ShowWindow(m_FdDisp);

	CStatic* xx5;	xx5 = (CStatic*)GetDlgItem(IDC_STATIC_step);	xx5->ShowWindow(m_stepDisp);
	CButton* xx6;	xx6 = (CButton*)GetDlgItem(IDC_RADIO1);			xx6->ShowWindow(m_stepDisp);
	CButton* xx7;	xx7 = (CButton*)GetDlgItem(IDC_RADIO2);			xx7->ShowWindow(m_stepDisp);

	xx6->SetCheck(m_step == 1);
	xx7->SetCheck(m_step == 10);

	CStatic* xx8;	xx8 = (CStatic*)GetDlgItem(IDC_STATIC_bcbt);	xx8->ShowWindow(m_bcbtDisp);
	CButton* xx9;	xx9 = (CButton*)GetDlgItem(IDC_RADIO3);			xx9->ShowWindow(m_bcbtDisp);
	CButton* xx10;	xx10 = (CButton*)GetDlgItem(IDC_RADIO4);		xx10->ShowWindow(m_bcbtDisp);
	CButton* xx11;	xx11 = (CButton*)GetDlgItem(IDC_RADIO5);		xx11->ShowWindow(m_bcbtDisp);
	CButton* xx12;	xx12 = (CButton*)GetDlgItem(IDC_RADIO6);		xx12->ShowWindow(m_bcbtDisp);
	CButton* xx13;	xx13 = (CButton*)GetDlgItem(IDC_RADIO7);		xx13->ShowWindow(m_bcbtDisp);
	CButton* xx14;	xx14 = (CButton*)GetDlgItem(IDC_CHECK_AntDisc);	xx14->ShowWindow(m_bcbtDisp);
	CStatic* xx15;	xx15 = (CStatic*)GetDlgItem(IDC_STATIC_RPR);	xx15->ShowWindow(m_bcbtDisp);
	CButton* xx16;	xx16 = (CButton*)GetDlgItem(IDC_EDIT_RPR);		xx16->ShowWindow(m_bcbtDisp);
	RPR_FUNCTION();

	xx9->SetCheck(m_bcbt == _T("DVB 8MHz"));
	xx10->SetCheck(m_bcbt == _T("DVB 7MHz"));
	xx11->SetCheck(m_bcbt == _T("T-DAB"));
	xx12->SetCheck(m_bcbt == _T("ANA 8MHz"));
	xx13->SetCheck(m_bcbt == _T("ANA 7MHz"));
	xx14->SetCheck(m_AntDisc == 1);

	xx10->EnableWindow(m_nFter==FALSE);
	xx11->EnableWindow(m_nFter==FALSE);
	xx13->EnableWindow(m_nFter==FALSE);

	if(m_Monitoring == TRUE)
	{
		GetDlgItem(IDC_STATIC_Fd)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Fd)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_Rx)->SetWindowText(_Z("Transmitter Height(m)"));
		GetDlgItem(IDC_STATIC_Fd)->SetWindowText(_Z("Transmitter Power(W)"));
	}


	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CLoSDLG::OnRadio1() 
{
	m_step = 1;
}
void CLoSDLG::OnRadio2() 
{
	m_step = 10;
}

void CLoSDLG::OnRadio3() 
{
	m_bcbt = _T("DVB 8MHz");
	RPR_FUNCTION();
}
void CLoSDLG::OnRadio4() 
{
	m_bcbt = _T("DVB 7MHz");
	RPR_FUNCTION();
}
void CLoSDLG::OnRadio5() 
{
	m_bcbt = _T("T-DAB");
	RPR_FUNCTION();
}

void CLoSDLG::OnRadio6() 
{
	m_bcbt = _T("ANA 8MHz");
	RPR_FUNCTION();
}

void CLoSDLG::OnRadio7() 
{
	m_bcbt = _T("ANA 7MHz");
	RPR_FUNCTION();
}

void CLoSDLG::OnCHECKAntDisc() 
{
	CButton* xx1;	xx1 = (CButton*)GetDlgItem(IDC_CHECK_AntDisc);	
	m_AntDisc = xx1->GetCheck();
}


void CLoSDLG::RPR_FUNCTION() 
{
	if((m_bcbt == _T("ANA 7MHz"))||(m_bcbt == _T("ANA 8MHz")))
	{
		CStatic* xx15;	xx15 = (CStatic*)GetDlgItem(IDC_STATIC_RPR);	xx15->EnableWindow(TRUE);
		CButton* xx16;	xx16 = (CButton*)GetDlgItem(IDC_EDIT_RPR);		xx16->EnableWindow(TRUE);
	}
	else
	{
		CStatic* xx15;	xx15 = (CStatic*)GetDlgItem(IDC_STATIC_RPR);	xx15->EnableWindow(FALSE);
		CButton* xx16;	xx16 = (CButton*)GetDlgItem(IDC_EDIT_RPR);		xx16->EnableWindow(FALSE);
	}
}
