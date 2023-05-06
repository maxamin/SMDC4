// SmoothDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "SmoothDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmoothDLG dialog


CSmoothDLG::CSmoothDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CSmoothDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmoothDLG)
	m_kfactor = _T("4/3");
	m_Type = 0;
	//}}AFX_DATA_INIT
}


void CSmoothDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmoothDLG)
	DDX_Control(pDX, IDC_COMBO1, m_List1);
	DDX_Text(pDX, IDC_EDIT_earth, m_kfactor);
	DDX_Text(pDX, IDC_EDIT_Type, m_Type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSmoothDLG, CDialog)
	//{{AFX_MSG_MAP(CSmoothDLG)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmoothDLG message handlers

BOOL CSmoothDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(true);

	m_List1.AddString(_Z("A:Sea Water (average salinity), 20° C"));
	m_List1.AddString(_Z("B:Wet Ground"));
	m_List1.AddString(_Z("C:Fresh Water"));
	m_List1.AddString(_Z("D:Medium Dry Ground"));
	m_List1.AddString(_Z("E:Very Dry Ground"));
	m_List1.AddString(_Z("F:Pure Water, 20° C"));
	m_List1.AddString(_Z("G:Ice(Fresh Water), -1° C"));
	m_List1.AddString(_Z("G:Ice(Fresh Water), -10° C"));
	m_List1.SetTopIndex(1);
	m_List1.SetCurSel(0);	
	
	UpdateData(false);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CSmoothDLG::OnSelchangeCombo1() 
{
	UpdateData(true);
	m_Type = m_List1.GetCurSel();
	UpdateData(false);
}
