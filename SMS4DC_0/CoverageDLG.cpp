// CoverageDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "CoverageDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoverageDLG dialog


CCoverageDLG::CCoverageDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CCoverageDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoverageDLG)
	m_max = 10.0;
	m_min = 1.0;
	m_thr = 5.0;
	m_title = _T("Coverage Area Parameter");
	//}}AFX_DATA_INIT
}


void CCoverageDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoverageDLG)
	DDX_Text(pDX, IDC_EDIT_max, m_max);
	DDX_Text(pDX, IDC_EDIT_min, m_min);
	DDX_Text(pDX, IDC_EDIT_thr, m_thr);
	DDX_Text(pDX, IDC_EDIT_title, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCoverageDLG, CDialog)
	//{{AFX_MSG_MAP(CCoverageDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoverageDLG message handlers

BOOL CCoverageDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_title);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}
