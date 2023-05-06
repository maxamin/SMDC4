// Fassign1DLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Fassign1DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFassign1DLG dialog


CFassign1DLG::CFassign1DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CFassign1DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFassign1DLG)
	m_CSR = 15.0;
	m_Fmin = 145.0;
	m_Fmax = 155.0;
	m_Imax = 20.0;
	m_Rkm = 50.0;
	//}}AFX_DATA_INIT
}


void CFassign1DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFassign1DLG)
	DDX_Text(pDX, IDC_EDIT_CSR, m_CSR);
	DDX_Text(pDX, IDC_EDIT_Fmax, m_Fmax);
	DDX_Text(pDX, IDC_EDIT_Fmin, m_Fmin);
	DDX_Text(pDX, IDC_EDIT_Imax, m_Imax);
	DDX_Text(pDX, IDC_EDIT_Rkm, m_Rkm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFassign1DLG, CDialog)
	//{{AFX_MSG_MAP(CFassign1DLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFassign1DLG message handlers

BOOL CFassign1DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
