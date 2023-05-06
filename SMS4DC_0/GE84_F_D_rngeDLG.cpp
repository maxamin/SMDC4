// GE84_F_D_rngeDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "GE84_F_D_rngeDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGE84_F_D_rngeDLG dialog

CGE84_F_D_rngeDLG::CGE84_F_D_rngeDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CGE84_F_D_rngeDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGE84_F_D_rngeDLG)
	m_D = 1500.0;
	m_Emin = 20.0;
	m_F = 400.0;
	m_T = 1.0;
	//}}AFX_DATA_INIT
}


void CGE84_F_D_rngeDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGE84_F_D_rngeDLG)
	DDX_Text(pDX, IDC_EDIT_D, m_D);
	DDX_Text(pDX, IDC_EDIT_Emin, m_Emin);
	DDX_Text(pDX, IDC_EDIT_F, m_F);
	DDX_Text(pDX, IDC_EDIT_T, m_T);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGE84_F_D_rngeDLG, CDialog)
	//{{AFX_MSG_MAP(CGE84_F_D_rngeDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGE84_F_D_rngeDLG message handlers

BOOL CGE84_F_D_rngeDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}
