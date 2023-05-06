// BorderRadiusDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "BorderRadiusDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBorderRadiusDLG dialog


CBorderRadiusDLG::CBorderRadiusDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CBorderRadiusDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBorderRadiusDLG)
	m_R = 0.0;
	//}}AFX_DATA_INIT
}


void CBorderRadiusDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBorderRadiusDLG)
	DDX_Text(pDX, IDC_EDIT_R, m_R);
	DDV_MinMaxDouble(pDX, m_R, 0., 1500.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBorderRadiusDLG, CDialog)
	//{{AFX_MSG_MAP(CBorderRadiusDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBorderRadiusDLG message handlers

BOOL CBorderRadiusDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}
