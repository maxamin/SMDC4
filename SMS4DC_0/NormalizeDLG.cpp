// NormalizeDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "NormalizeDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNormalizeDLG dialog


CNormalizeDLG::CNormalizeDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CNormalizeDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNormalizeDLG)
	m_MaxValue = 0.0;
	m_MaxValue2 = 0.0;
	m_MinValue = 0.0;
	m_MinValue2 = 0.0;
	//}}AFX_DATA_INIT
}


void CNormalizeDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNormalizeDLG)
	DDX_Text(pDX, IDC_EDIT_Maximum, m_MaxValue);
	DDX_Text(pDX, IDC_EDIT_Maximum2, m_MaxValue2);
	DDX_Text(pDX, IDC_EDIT_Minimum, m_MinValue);
	DDX_Text(pDX, IDC_EDIT_Minimum2, m_MinValue2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNormalizeDLG, CDialog)
	//{{AFX_MSG_MAP(CNormalizeDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNormalizeDLG message handlers

void CNormalizeDLG::OnOK() 
{
	UpdateData();

	double Vmin = min(m_MinValue,m_MaxValue);
	double Vmax = max(m_MinValue,m_MaxValue);
	m_MinValue = Vmin;
	m_MaxValue = Vmax;

	m_MinValue = max(m_MinValue,m_MinValue2);
	m_MaxValue = min(m_MaxValue,m_MaxValue2);
	UpdateData(false);
	CDialog::OnOK();
}

BOOL CNormalizeDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}