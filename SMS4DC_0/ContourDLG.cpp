// ContourDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "ContourDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContourDLG dialog


CContourDLG::CContourDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CContourDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContourDLG)
	m_max = 12.0;
	m_min = 2.0;
	m_nL = 2;
	m_step = 5.0;
	//}}AFX_DATA_INIT
}


void CContourDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContourDLG)
	DDX_Text(pDX, IDC_EDIT_max, m_max);
	DDX_Text(pDX, IDC_EDIT_min, m_min);
	DDX_Text(pDX, IDC_EDIT_nL, m_nL);
	DDV_MinMaxInt(pDX, m_nL, 2, 255);
	DDX_Text(pDX, IDC_EDIT_step, m_step);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContourDLG, CDialog)
	//{{AFX_MSG_MAP(CContourDLG)
	ON_EN_CHANGE(IDC_EDIT_step, OnChangeEDITstep)
	ON_EN_CHANGE(IDC_EDIT_nL, OnChangeEDITnL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContourDLG message handlers

void CContourDLG::OnChangeEDITstep() 
{
	UpdateData();
	m_nL = int((m_max - m_min)/m_step);
	UpdateData(false);
}

void CContourDLG::OnChangeEDITnL() 
{
	UpdateData();
	m_step = double((int(1000.0*(m_max - m_min)/m_nL))/1000.0);
	UpdateData(false);
}



BOOL CContourDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE; 
}
