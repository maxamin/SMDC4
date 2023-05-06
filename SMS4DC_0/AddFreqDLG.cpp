// AddFreqDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "AddFreqDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddFreqDLG dialog


CAddFreqDLG::CAddFreqDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAddFreqDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddFreqDLG)
	m_BW = 0.0;
	m_Freq = 0.0;
	m_Flag = FALSE;
	m_Flo = _Z("Frequency(MHz)");
	m_Fhi = _Z("BandWidth(kHz)");
	m_title = _T("Add Frequency");
	//}}AFX_DATA_INIT
}


void CAddFreqDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddFreqDLG)
	DDX_Text(pDX, IDC_EDIT_BW, m_BW);
	DDX_Text(pDX, IDC_EDIT_Freq, m_Freq);
	DDX_Text(pDX, IDC_EDIT_Flag, m_Flag);
	DDX_Text(pDX, IDC_EDIT_FLO, m_Flo);
	DDX_Text(pDX, IDC_EDIT_FHI, m_Fhi);
	DDX_Text(pDX, IDC_EDIT_title, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddFreqDLG, CDialog)
	//{{AFX_MSG_MAP(CAddFreqDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddFreqDLG message handlers

BOOL CAddFreqDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CEdit* xx1 ;		xx1 = (CEdit*)GetDlgItem(IDC_EDIT_BW);
	CStatic* xx2 ;		xx2 = (CStatic*)GetDlgItem(IDC_STATIC_BW);
	xx1->ShowWindow(m_Flag);
	xx2->ShowWindow(m_Flag);

	xx2->SetWindowText(m_Fhi);

	CStatic* xx3 ;		xx3 = (CStatic*)GetDlgItem(IDC_STATIC_F);
	xx3->SetWindowText(m_Flo);

	SetWindowText(m_title);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}
