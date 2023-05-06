// HATADLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "HATADLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHATADLG dialog


CHATADLG::CHATADLG(CWnd* pParent /*=NULL*/)
	: CDialog(CHATADLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHATADLG)
	m_UserDefined = FALSE;
	m_Rx = 3.0;
	m_kfactor = 1.3333333333;
	m_FRQ = 150.0;
	m_ENV = 2;
	m_a10 = 0.0;
	m_a20 = 0.0;
	m_a30 = 0.0;
	m_b10 = 0.0;
	m_b20 = 0.0;
	//}}AFX_DATA_INIT
}

void CHATADLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHATADLG)
	DDX_Control(pDX, IDC_COMBO_ENV, m_COMBO_ENV);
	DDX_Control(pDX, IDC_b2, m_b2);
	DDX_Control(pDX, IDC_b1, m_b1);
	DDX_Control(pDX, IDC_a3, m_a3);
	DDX_Control(pDX, IDC_a2, m_a2);
	DDX_Control(pDX, IDC_a1, m_a1);
	DDX_Check(pDX, IDC_UserDefined, m_UserDefined);
	DDX_Text(pDX, IDC_Rx, m_Rx);
	DDX_Text(pDX, IDC_kfactor, m_kfactor);
	DDX_Text(pDX, IDC_FRQ, m_FRQ);
	DDX_Text(pDX, IDC_ENV, m_ENV);
	DDV_MinMaxInt(pDX, m_ENV, 0, 3);
	DDX_Text(pDX, IDC_a10, m_a10);
	DDX_Text(pDX, IDC_a20, m_a20);
	DDX_Text(pDX, IDC_a30, m_a30);
	DDX_Text(pDX, IDC_b10, m_b10);
	DDX_Text(pDX, IDC_b20, m_b20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHATADLG, CDialog)
	//{{AFX_MSG_MAP(CHATADLG)
	ON_BN_CLICKED(IDC_UserDefined, OnUserDefined)
	ON_BN_CLICKED(IDC_Default, OnDefault)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_ENV, OnSelchangeComboEnv)
	ON_EN_CHANGE(IDC_a1, OnChangea1)
	ON_EN_CHANGE(IDC_a2, OnChangea2)
	ON_EN_CHANGE(IDC_a3, OnChangea3)
	ON_EN_CHANGE(IDC_b1, OnChangeb1)
	ON_EN_CHANGE(IDC_b2, OnChangeb2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHATADLG message handlers


BOOL CHATADLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData();

	if (m_FRQ<=1500.0)
	{
		m_a1.SetWindowText("69.55");
		m_a2.SetWindowText("26.16");
	}
	else
	{
		m_a1.SetWindowText("46.3");
		m_a2.SetWindowText("33.9");
		m_COMBO_ENV.EnableWindow(false);
	}
	m_a3.SetWindowText("-13.82");
	m_b1.SetWindowText("44.9");
	m_b2.SetWindowText("-6.55");

	CString str;
	m_a1.GetWindowText(str);	m_a10 = atof(str);
	m_a2.GetWindowText(str);	m_a20 = atof(str);
	m_a3.GetWindowText(str);	m_a30 = atof(str);
	m_b1.GetWindowText(str);	m_b10 = atof(str);
	m_b2.GetWindowText(str);	m_b20 = atof(str);
/*
	CFont font;
	VERIFY(font.CreateFont(
	   16,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_BOLD,                   // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   DEFAULT_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   "Arial"));                 // lpszFacename
*/

CFont font;
LOGFONT lf;
memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
lf.lfHeight = 12;                      // request a 12-pixel-height font
strcpy(lf.lfFaceName, "Arial");        // request a face name "Arial"
VERIFY(font.CreateFontIndirect(&lf));  // create the font


	CEdit* EDIT_S=(CEdit*)GetDlgItem(IDC_HATA_Formula);
	EDIT_S->SetFont(&font);
	EDIT_S->SetWindowText(_T("L = a1 + a2.log(f) + a3.log(h1) + [ b1 + b2.log(h1) ].[ log(d) ]^b - a(f,h2)"));

	CEdit* EDIT_a1=(CEdit*)GetDlgItem(IDC_STATICa1);
	EDIT_a1->SetFont(&font);
	CEdit* EDIT_a2=(CEdit*)GetDlgItem(IDC_STATICa2);
	EDIT_a2->SetFont(&font);
	CEdit* EDIT_a3=(CEdit*)GetDlgItem(IDC_STATICa3);
	EDIT_a3->SetFont(&font);
	CEdit* EDIT_b1=(CEdit*)GetDlgItem(IDC_STATICb1);
	EDIT_b1->SetFont(&font);
	CEdit* EDIT_b2=(CEdit*)GetDlgItem(IDC_STATICb2);
	EDIT_b2->SetFont(&font);

	font.DeleteObject();

	m_COMBO_ENV.AddString(_Z("Open Areas"));
	m_COMBO_ENV.AddString(_Z("SubUrban Areas"));
	m_COMBO_ENV.AddString(_Z("Urban Areas (Medium to Small cities)"));
	m_COMBO_ENV.AddString(_Z("Urban Areas (Large cities)"));
	m_COMBO_ENV.SetTopIndex(1);
	m_COMBO_ENV.SetCurSel(2);	

	UpdateData(false);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}

void CHATADLG::OnUserDefined() 
{
	UpdateData();
	if(m_UserDefined)
	{
		m_a1.SetReadOnly(false);
		m_a2.SetReadOnly(false);
		m_a3.SetReadOnly(false);
		m_b1.SetReadOnly(false);
		m_b2.SetReadOnly(false);
	}
	else
	{
		m_a1.SetReadOnly(true);
		m_a2.SetReadOnly(true);
		m_a3.SetReadOnly(true);
		m_b1.SetReadOnly(true);
		m_b2.SetReadOnly(true);
	}
	UpdateData(false);
}

void CHATADLG::OnDefault() 
{
	UpdateData();
	if (m_FRQ<=1500.0)
	{
		m_a1.SetWindowText("69.55");
		m_a2.SetWindowText("26.16");
	}
	else
	{
		m_a1.SetWindowText("46.3");
		m_a2.SetWindowText("33.9");
		m_COMBO_ENV.EnableWindow(false);
	}
	m_a3.SetWindowText("-13.82");
	m_b1.SetWindowText("44.9");
	m_b2.SetWindowText("-6.55");

	CString str;
	m_a1.GetWindowText(str);	m_a10 = atof(str);
	m_a2.GetWindowText(str);	m_a20 = atof(str);
	m_a3.GetWindowText(str);	m_a30 = atof(str);
	m_b1.GetWindowText(str);	m_b10 = atof(str);
	m_b2.GetWindowText(str);	m_b20 = atof(str);


	UpdateData(false);
	
}

HBRUSH CHATADLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if ( pWnd->GetDlgCtrlID() == IDC_HATA_Formula  )
	{
			pDC->SetBkColor(RGB( 0, 0, 127 ));
			pDC->SetTextColor(RGB( 255, 255, 255 ));
	}

	if ( pWnd->GetDlgCtrlID() == IDC_STATICa1  )
	{
		//	pDC->SetBkColor(RGB( 0, 0, 127 ));
		//	pDC->SetTextColor(RGB( 255, 255, 255 ));
	}


	return hbr;
}

void CHATADLG::OnSelchangeComboEnv() 
{
	UpdateData();
	m_ENV = m_COMBO_ENV.GetCurSel();
	UpdateData(false);
}

void CHATADLG::OnChangea1() 
{
	UpdateData();
	CString str;
	m_a1.GetWindowText(str);	m_a10 = atof(str);
	m_a2.GetWindowText(str);	m_a20 = atof(str);
	m_a3.GetWindowText(str);	m_a30 = atof(str);
	m_b1.GetWindowText(str);	m_b10 = atof(str);
	m_b2.GetWindowText(str);	m_b20 = atof(str);
	UpdateData(false);
}
void CHATADLG::OnChangea2() 
{
	OnChangea1();	
}
void CHATADLG::OnChangea3() 
{
	OnChangea1();	
}
void CHATADLG::OnChangeb1() 
{
	OnChangea1();	
}
void CHATADLG::OnChangeb2() 
{
	OnChangea1();	
}
