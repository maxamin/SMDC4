// PropSelect.cpp : implementation file
//

#include "stdafx.h"
#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS
#include "resource.h"
#include "ificimport.h"
#include "PropSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropSelect dialog


CPropSelect::CPropSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CPropSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropSelect)
	//}}AFX_DATA_INIT
}


void CPropSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropSelect)
	DDX_Control(pDX, IDC_PROPS, m_Props);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropSelect, CDialog)
	//{{AFX_MSG_MAP(CPropSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropSelect message handlers

void CPropSelect::OnOK() 
{
	CString Cnt;
/*	int List[1000];

	m_Props.GetSelItems(m_Props.GetSelCount(),List);
	for(int i=0;i<m_Props.GetSelCount();i++)
	{
		m_Props.GetText(List[i],Cnt);
		Cnt.TrimRight();
		m_Result+=Cnt+_T("_");
	}
	m_Result.Delete(m_Result.GetLength()-1);
*/
	m_Props.GetText(m_Props.GetCurSel(),m_Result);
	CDialog::OnOK();
}

BOOL CPropSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	m_Props.AddString(_T("REC-452"));
	m_Props.AddString(_T("REC-1546"));
	m_Props.AddString(_T("FREE SPACE"));
	
	TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropSelect::TranslateDialog(CDialog *pDialog)
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

CString CPropSelect::GetTranslatedString(CString strOriginal, CString Lang)
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

