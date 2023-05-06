// CountryList.cpp : implementation file
//

#include "stdafx.h"
#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS
#include "resource.h"
#include "ificImport.h"
#include "CountryList.h"
extern "C" {
#include "idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountryList dialog

extern "C" char * WINAPI Code2NameCTY_lang(CString co, CString mLang);	//CNT.lib
extern "C" char * WINAPI AllCodes_lang(CString CTYCOD[], long *NOCTY);	//CNT.lib

CCountryList::CCountryList(CWnd* pParent /*=NULL*/)
	: CDialog(CCountryList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCountryList)
	//}}AFX_DATA_INIT
}


void CCountryList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCountryList)
	DDX_Control(pDX, IDC_COUNTRIES, m_Countries);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCountryList, CDialog)
	//{{AFX_MSG_MAP(CCountryList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountryList message handlers

BOOL CCountryList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	long UNR = 72, MAXCTY=1000, NOCTY ,ALL=TRUE;
//	unsigned char CTYCOD[1000][3];
//	float RLONLL=-3.1415, RLATLL=-3.1415/2, RLONUR=3.1415, RLATUR=3.1415/2;
//	WDBUNIT(&UNR) ;
//	GEOACW( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &MAXCTY, (unsigned char *)CTYCOD, &NOCTY, &ALL);
//	for(int i=0;i<NOCTY;i++)
//	{
//		m_Countries.AddString((char *)CTYCOD[i]);
//	}
/*	CRecordset RS;
	CDatabase DB;
	DB.Open(m_SDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	RS.Open(CRecordset::snapshot,_T("Select * from country order by CID"));
	while(true)
	{
		if(RS.IsEOF()) break;
		CString F1,F2;
		RS.GetFieldValue(_T("CID"),F1);
		RS.GetFieldValue(_T("Country"),F2);
		m_Countries.AddString(F1+_T("-")+F2);
		RS.MoveNext();
	}
	RS.Close();
	DB.Close();*/
	CString CTYCOD[300];
	long NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Countries.ResetContent();
	for(int i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Countries.AddString(Str);
	}
	TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCountryList::OnOK() 
{
	int List[1000];
	CString Cnt;
	m_Countries.GetSelItems(m_Countries.GetSelCount(),List);
	for(int i=0;i<m_Countries.GetSelCount();i++)
	{
		m_Countries.GetText(List[i],Cnt);
		Cnt=Cnt.Left(Cnt.Find(_T("-"),0));
		Cnt.TrimRight();
		m_Result+=Cnt+_T("_");
	}
	m_Result.Delete(m_Result.GetLength()-1);
	CDialog::OnOK();
}

void CCountryList::TranslateDialog(CDialog *pDialog)
{
	CString strOriginal(_T(""));
	for (int iID = 0; iID < _APS_NEXT_CONTROL_VALUE; iID++)
	{
		pDialog->GetDlgItemText(iID, strOriginal);
		if (!strOriginal.IsEmpty())
		{
			if(((pDialog->GetDlgItem(iID))->IsKindOf(RUNTIME_CLASS(CComboBox)))!=1)
			{
				CString s = GetTranslatedString(strOriginal, m_Lang);
				if (!s.IsEmpty())// && strOriginal != s)
					pDialog->SetDlgItemText(iID, s);
			}
		}
	}//for
	strOriginal = _T("");
	pDialog->GetWindowText(strOriginal);
	if (!strOriginal.IsEmpty())
	{
		CString s = GetTranslatedString(strOriginal, m_Lang);
		if (!s.IsEmpty() && strOriginal != s)
			pDialog->SetWindowText(s);
	}
}

CString CCountryList::GetTranslatedString(CString strOriginal, CString Lang)
{
	static CString m_Lang;
//	m_Lang="CC";
	if(Lang!=m_Lang && !Lang.IsEmpty()) 
		m_Lang=Lang;
	if(m_Lang==_T("En"))	return strOriginal;
	int ID=-1;
	HMODULE	hMod = LoadLibrary("ResDLLen.dll");
	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			int n=0, nLen = ::LoadString(hMod, 0, szTemp, 1000);
			if(nLen!=0)		n = atoi(szTemp);

			for(int ids=1; ids<=n; ids++)
			{
				nLen = ::LoadString(hMod, ids, szTemp, 1000);
				if(strOriginal==szTemp)
				{
					ID = ids;
					break;
				}
			}
		}
		FreeLibrary(hMod);
	}//hMod

	CString str;
	if		(m_Lang==_T("Fr")) 	hMod = LoadLibrary("ResDLLfr.dll");
	else if	(m_Lang==_T("Es")) 	hMod = LoadLibrary("ResDLLes.dll");
	else if	(m_Lang==_T("Ch")) 	hMod = LoadLibrary("ResDLLch.dll");
	else if	(m_Lang==_T("Ar")) 	hMod = LoadLibrary("ResDLLar.dll");
	else if	(m_Lang==_T("Ru")) 	hMod = LoadLibrary("ResDLLru.dll");

	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			::LoadString(hMod, ID, szTemp, 1000);
			str = szTemp;
		}
		FreeLibrary(hMod);
	}//hMod

	return str;
}

