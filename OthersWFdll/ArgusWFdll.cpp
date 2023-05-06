// ArgusWFdll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ArgusWFdll.h"

#include "MyMultiDocTemplate.h"
#include "ChildFrm.h"
#include "ArgusDoc.h"
#include "ArgusView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CArgusWFdllApp

BEGIN_MESSAGE_MAP(CArgusWFdllApp, CWinApp)
	//{{AFX_MSG_MAP(CArgusWFdllApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArgusWFdllApp construction

CArgusWFdllApp::CArgusWFdllApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CArgusWFdllApp object

CArgusWFdllApp theApp;

CMyMultiDocTemplate* DLLothersDocTemplate()
{
	CMyMultiDocTemplate*pTemplate = NULL ;

	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	// add our document template
	pTemplate = new CMyMultiDocTemplate(
							theApp.m_hInstance,         // the DLL's app object HINSTANCE
							IDR_ARGUSTYPE,               // the document/view resource info
							RUNTIME_CLASS(CArgusDoc),
							RUNTIME_CLASS(CChildFrame), // custom MDI child frame
							RUNTIME_CLASS(CArgusView));
	return pTemplate ;
}



/////////////////////////////Language////////////////////////////
#define APSTUDIO_INVOKED
#include "resource.h"
void CArgusWFdllApp::TranslateDialog(CDialog *pDialog)
{
	CString strOriginal(_T(""));
	for (int iID = 0; iID < _APS_NEXT_CONTROL_VALUE; iID++)
	{
		pDialog->GetDlgItemText(iID, strOriginal);
		if (!strOriginal.IsEmpty())
		{
			if(((pDialog->GetDlgItem(iID))->IsKindOf(RUNTIME_CLASS(CComboBox)))!=1)
			{
				CString s = GetTranslatedString(strOriginal);
				if (!s.IsEmpty() && strOriginal != s)
					pDialog->SetDlgItemText(iID, s);
			}
		}
	}//for
	strOriginal = _T("");
	pDialog->GetWindowText(strOriginal);
	if (!strOriginal.IsEmpty())
	{
		CString s = GetTranslatedString(strOriginal);
		if (!s.IsEmpty() && strOriginal != s)
			pDialog->SetWindowText(s);
	}
}

CString CArgusWFdllApp::GetTranslatedString(CString strOriginal)
{
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


