// AP7_OptionsDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "AP7_OptionsDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAP7_OptionsDLG dialog


CAP7_OptionsDLG::CAP7_OptionsDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAP7_OptionsDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAP7_OptionsDLG)
	m_BDIRPC = _T("");
	m_GMIN = _T("-10");
	m_INCLINATION = _T("");
	m_RECVPC = _T("");
	m_SATEAST = _T("");
	m_SATWEST = _T("");
	m_TRANPC = _T("");
	m_Manned = FALSE;
	//}}AFX_DATA_INIT
}


void CAP7_OptionsDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAP7_OptionsDLG)
	DDX_Text(pDX, IDC_EDIT_BDIRPC, m_BDIRPC);
	DDX_Text(pDX, IDC_EDIT_GMIN, m_GMIN);
	DDX_Text(pDX, IDC_EDIT_INCLINATION, m_INCLINATION);
	DDX_Text(pDX, IDC_EDIT_RECVPC, m_RECVPC);
	DDX_Text(pDX, IDC_EDIT_SATEAST, m_SATEAST);
	DDX_Text(pDX, IDC_EDIT_SATWEST, m_SATWEST);
	DDX_Text(pDX, IDC_EDIT_TRANPC, m_TRANPC);
	DDX_Text(pDX, IDC_EDIT_Manned, m_Manned);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAP7_OptionsDLG, CDialog)
	//{{AFX_MSG_MAP(CAP7_OptionsDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAP7_OptionsDLG message handlers

BOOL CAP7_OptionsDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CButton *xx = (CButton *)GetDlgItem(IDC_RADIO2);
	xx->SetCheck(TRUE);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CAP7_OptionsDLG::OnOK() 
{
	UpdateData();

	CButton *xx = (CButton *)GetDlgItem(IDC_RADIO1);
	m_Manned = xx->GetCheck();

	UpdateData(false);	
	CDialog::OnOK();
}
