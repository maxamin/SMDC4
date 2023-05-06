// ArgusWFdll.h : main header file for the ARGUSWFDLL DLL
//

#if !defined(AFX_ARGUSWFDLL_H__E33B5FE2_E166_40BE_9CF5_1F747DD06F67__INCLUDED_)
#define AFX_ARGUSWFDLL_H__E33B5FE2_E166_40BE_9CF5_1F747DD06F67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CArgusWFdllApp
// See ArgusWFdll.cpp for the implementation of this class
//

class CArgusWFdllApp : public CWinApp
{
public:
	CArgusWFdllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArgusWFdllApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CArgusWFdllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
		void TranslateDialog(CDialog *pDialog);
		CString GetTranslatedString(CString strOriginal);
		CString m_Lang;
		CString _Z(CString s){ return (GetTranslatedString(_T(s))); };

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARGUSWFDLL_H__E33B5FE2_E166_40BE_9CF5_1F747DD06F67__INCLUDED_)
