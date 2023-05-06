// Int_ParametersDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Int_ParametersDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInt_ParametersDLG dialog


CInt_ParametersDLG::CInt_ParametersDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CInt_ParametersDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInt_ParametersDLG)
	m_D = 150.0;
	m_Emin = 56.0;
	m_F = 400.0;
	m_T = 1.0;
	m_L = 50.0;
	m_method = 0;
	m_AntDisc = TRUE;
	m_PolDisc = TRUE;
	m_EDIT_PolDisc = 12.0;
	//}}AFX_DATA_INIT
}


void CInt_ParametersDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInt_ParametersDLG)
	DDX_Control(pDX, IDC_COMBO_method, m_COMBO_method);
	DDX_Text(pDX, IDC_EDIT_D, m_D);
	DDX_Text(pDX, IDC_EDIT_Emin, m_Emin);
	DDX_Text(pDX, IDC_EDIT_F, m_F);
	DDX_Text(pDX, IDC_EDIT_T, m_T);
	DDV_MinMaxDouble(pDX, m_T, 1., 50.);
	DDX_Text(pDX, IDC_EDIT_location, m_L);
	DDV_MinMaxDouble(pDX, m_L, 1., 99.);
	DDX_Text(pDX, IDC_EDIT_method, m_method);
	DDX_Check(pDX, IDC_CHECK_Ant, m_AntDisc);
	DDX_Check(pDX, IDC_CHECK_Pol, m_PolDisc);
	DDX_Text(pDX, IDC_EDIT_Pol, m_EDIT_PolDisc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInt_ParametersDLG, CDialog)
	//{{AFX_MSG_MAP(CInt_ParametersDLG)
	ON_CBN_SELCHANGE(IDC_COMBO_method, OnSelchangeCOMBOmethod)
	ON_BN_CLICKED(IDC_CHECK_Pol, OnCHECKPol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInt_ParametersDLG message handlers

BOOL CInt_ParametersDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_COMBO_method.AddString(_Z("Power Sum"));
	m_COMBO_method.AddString(_Z("Multiplication"));
	m_COMBO_method.SetTopIndex(1);
	m_COMBO_method.SetCurSel(0);	

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CInt_ParametersDLG::OnSelchangeCOMBOmethod() 
{
	UpdateData();
	m_method = m_COMBO_method.GetCurSel();
	UpdateData(false);
}

void CInt_ParametersDLG::OnCHECKPol() 
{
	UpdateData();
	CEdit * xx ;	xx = (CEdit *)GetDlgItem(IDC_EDIT_Pol);
	if(m_PolDisc)
		xx->SetReadOnly(false);
		else
		xx->SetReadOnly();
	UpdateData(false);
}
