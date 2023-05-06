// CircleRadiusDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "CircleRadiusDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCircleRadiusDLG dialog


CCircleRadiusDLG::CCircleRadiusDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CCircleRadiusDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCircleRadiusDLG)
	m_CircleRadius = 50.0;
	m_title = _Z("Circle Radius");
	m_lable = _Z("Enter Radius (km) :");
	//}}AFX_DATA_INIT
}


void CCircleRadiusDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCircleRadiusDLG)
	DDX_Text(pDX, IDC_EDIT1, m_CircleRadius);
	DDV_MinMaxDouble(pDX, m_CircleRadius, 0., 1000.);
	DDX_Text(pDX, IDC_EDIT2, m_title);
	DDX_Text(pDX, IDC_EDIT3, m_lable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCircleRadiusDLG, CDialog)
	//{{AFX_MSG_MAP(CCircleRadiusDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCircleRadiusDLG message handlers

BOOL CCircleRadiusDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_title);
	GetDlgItem(IDC_STATIC)->SetWindowText(m_lable);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
