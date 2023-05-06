// FXM_F_D_rngDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "FXM_F_D_rngDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFXM_F_D_rngDLG dialog


CFXM_F_D_rngDLG::CFXM_F_D_rngDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CFXM_F_D_rngDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFXM_F_D_rngDLG)
	m_D = 1500.0;
	m_Emin = 20.0;
	m_F = 400.0;
	m_Emergency = FALSE;
	//}}AFX_DATA_INIT

	m_flag = TRUE;
}


void CFXM_F_D_rngDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFXM_F_D_rngDLG)
	DDX_Text(pDX, IDC_EDIT_D, m_D);
	DDX_Text(pDX, IDC_EDIT_Emin, m_Emin);
	DDX_Text(pDX, IDC_EDIT_F, m_F);
	DDX_Check(pDX, IDC_CHECK1, m_Emergency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFXM_F_D_rngDLG, CDialog)
	//{{AFX_MSG_MAP(CFXM_F_D_rngDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFXM_F_D_rngDLG message handlers

BOOL CFXM_F_D_rngDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

//	if(m_flag)
	{
		GetDlgItem(IDC_EDIT_F)->ShowWindow(m_flag);		GetDlgItem(IDC_STATICb2)->ShowWindow(m_flag);
		GetDlgItem(IDC_EDIT_Emin)->ShowWindow(m_flag);		GetDlgItem(IDC_STATICb3)->ShowWindow(m_flag);
		GetDlgItem(IDC_CHECK1)->ShowWindow(m_flag);

	}

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
