// FresnelDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "FresnelDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFresnelDLG dialog


CFresnelDLG::CFresnelDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CFresnelDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFresnelDLG)
	m_Fresnel = 1;
	m_FrqMHz = 150.0;
	m_RxH = 10.0;
	m_TxH = 10.0;
	//}}AFX_DATA_INIT
}


void CFresnelDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFresnelDLG)
	DDX_Text(pDX, IDC_EDIT_Fresnel, m_Fresnel);
	DDX_Text(pDX, IDC_EDIT_Frq, m_FrqMHz);
	DDX_Text(pDX, IDC_EDIT_RxH, m_RxH);
	DDX_Text(pDX, IDC_EDIT_TxH, m_TxH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFresnelDLG, CDialog)
	//{{AFX_MSG_MAP(CFresnelDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFresnelDLG message handlers

BOOL CFresnelDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
