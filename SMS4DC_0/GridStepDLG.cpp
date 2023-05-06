// GridStepDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "GridStepDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridStepDLG dialog


CGridStepDLG::CGridStepDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CGridStepDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridStepDLG)
	m_GridStep = 0.0;
	//}}AFX_DATA_INIT
}


void CGridStepDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridStepDLG)
	DDX_Text(pDX, IDC_EDIT_GridStep, m_GridStep);
	DDV_MinMaxDouble(pDX, m_GridStep, 1.e-002, 10.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGridStepDLG, CDialog)
	//{{AFX_MSG_MAP(CGridStepDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridStepDLG message handlers

BOOL CGridStepDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE; 
}
