// CountrySelectionDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "CountrySelectionDLG.h"

#include "Code2NameCTY.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountrySelectionDLG dialog


CCountrySelectionDLG::CCountrySelectionDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CCountrySelectionDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCountrySelectionDLG)
	m_code = _T("IRN");
	m_Edit1 = 0;
	//}}AFX_DATA_INIT
}


void CCountrySelectionDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCountrySelectionDLG)
	DDX_Control(pDX, IDC_COMBO_Country, m_List);
	DDX_Text(pDX, IDC_EDIT_code, m_code);
	DDV_MaxChars(pDX, m_code, 3);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCountrySelectionDLG, CDialog)
	//{{AFX_MSG_MAP(CCountrySelectionDLG)
	ON_CBN_SELCHANGE(IDC_COMBO_Country, OnSelchangeCOMBOCountry)
	ON_CBN_DBLCLK(IDC_COMBO_Country, OnDblclkCOMBOCountry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountrySelectionDLG message handlers


extern "C" char * WINAPI AllCodes_lang(CString CTYCOD[], int *NOCTY);	//CNT_lang.lib
extern "C" char * WINAPI Code2NameCTY_lang(CString co, CString mLang);	//CNT_lang.lib
BOOL CCountrySelectionDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	AllCodes_lang(countryCODEidwm, &m_num);
	for (int i=0;i<m_num;i++)
	{
		countryNAMEidwm[i] = Code2NameCTY_lang(countryCODEidwm[i], ((CSMS4DCApp *)AfxGetApp())->m_Lang);
		m_List.AddString(countryNAMEidwm[i]);
	}

//	m_List.SetTopIndex(1);
//	m_Edit1 = Code2Indx_list(m_code);
//	m_List.SetCurSel(m_Edit1);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CCountrySelectionDLG::OnSelchangeCOMBOCountry() 
{
	UpdateData(true);
	m_Edit1 = m_List.GetCurSel();

	CString ss;
	m_List.GetLBText(m_Edit1,ss);
	m_code = Name2Code_idwm(ss);

	UpdateData(false);
}

CString CCountrySelectionDLG::Name2Code_idwm(CString name)
{
	for (int i=0;i<m_num;i++)
	{
		if (name == countryNAMEidwm[ i ])
			break;
	}
	if (i==m_num)
		return "";
	else
		return countryCODEidwm[ i ];
}

int CCountrySelectionDLG::Name2Indx_idwm(CString name)
{
	for (int i=0;i<m_num;i++)
	{
		if (name == countryNAMEidwm[ i ])
			break;
	}
	return i;
}

int CCountrySelectionDLG::Code2Indx_list(CString co)
{
	CString ss,cc;
	for (int i=0;i<m_num;i++)
	{
		m_List.GetLBText(i,ss);
		cc = Name2Code_idwm(ss);

		if (co == cc)
			break;
	}
	return i;
}

int CCountrySelectionDLG::Code2Indx_idwm(CString co)
{
	for (int i=0;i<m_num;i++)
	{
		if (co == countryCODEidwm[ i ])
			break;
	}
	return i;
}


void CCountrySelectionDLG::OnDblclkCOMBOCountry() 
{
	CCountrySelectionDLG::OnOK();
}
