// BorderMLDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "BorderMLDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBorderMLDLG dialog


CBorderMLDLG::CBorderMLDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CBorderMLDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBorderMLDLG)
	m_Name = _T("");
	m_Lat = _T("00N0000");
	m_Lon = _T("000E0000");
	m_cty = _T("");
	m_mobile = 0;
	//}}AFX_DATA_INIT
}


void CBorderMLDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBorderMLDLG)
	DDX_Text(pDX, IDC_EDIT_Name, m_Name);
	DDX_Text(pDX, IDC_EDIT_Lat, m_Lat);
	DDV_MaxChars(pDX, m_Lat, 7);
	DDX_Text(pDX, IDC_EDIT_Lon, m_Lon);
	DDV_MaxChars(pDX, m_Lon, 8);
	DDX_Text(pDX, IDC_EDIT_cty, m_cty);
	DDV_MaxChars(pDX, m_cty, 3);
	DDX_Text(pDX, IDC_EDIT_mobile, m_mobile);
	DDV_MinMaxInt(pDX, m_mobile, 0, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBorderMLDLG, CDialog)
	//{{AFX_MSG_MAP(CBorderMLDLG)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBorderMLDLG message handlers



BOOL CBorderMLDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_mobile==0)
	{
		CButton *xx = (CButton *)GetDlgItem(IDC_RADIO1);
		xx->SetCheck(TRUE);
	}
	else if(m_mobile==1)
	{
		CButton *xx = (CButton *)GetDlgItem(IDC_RADIO2);
		xx->SetCheck(TRUE);
	}
	else if(m_mobile==2)
	{
		CButton *xx = (CButton *)GetDlgItem(IDC_RADIO3);
		xx->SetCheck(TRUE);
	}

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}


void CBorderMLDLG::OnRadio1() 
{
	UpdateData();
	CButton *x1 = (CButton *)GetDlgItem(IDC_RADIO1);
	BOOL i = x1->GetCheck();
	if(i==TRUE)
	{
		m_mobile=0;
		CEdit *x2 = (CEdit *)GetDlgItem(IDC_EDIT_Lon);		x2->SetReadOnly();
		CEdit *x3 = (CEdit *)GetDlgItem(IDC_EDIT_Lat);		x3->SetReadOnly();
	}
	UpdateData(false);	
}

void CBorderMLDLG::OnRadio2() 
{
	UpdateData();
	CButton *x1 = (CButton *)GetDlgItem(IDC_RADIO2);
	BOOL i = x1->GetCheck();
	if(i==TRUE)
	{
		m_mobile=1;
		CEdit *x2 = (CEdit *)GetDlgItem(IDC_EDIT_Lon);		x2->SetReadOnly();
		CEdit *x3 = (CEdit *)GetDlgItem(IDC_EDIT_Lat);		x3->SetReadOnly();
	}
	UpdateData(false);		
}

void CBorderMLDLG::OnRadio3() 
{
	UpdateData();
	CButton *x1 = (CButton *)GetDlgItem(IDC_RADIO3);
	BOOL i = x1->GetCheck();
	if(i==TRUE)
	{
		m_mobile=2;
		CEdit *x2 = (CEdit *)GetDlgItem(IDC_EDIT_Lon);		x2->SetReadOnly(FALSE);
		CEdit *x3 = (CEdit *)GetDlgItem(IDC_EDIT_Lat);		x3->SetReadOnly(FALSE);
	}
	UpdateData(false);		
}
