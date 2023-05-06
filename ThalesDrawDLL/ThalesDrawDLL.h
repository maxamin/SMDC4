// ThalesDrawDLL.h : main header file for the THALESDRAWDLL DLL
//

#if !defined(AFX_THALESDRAWDLL_H__1D87FD7A_3656_426A_8564_D2687DCC7B85__INCLUDED_)
#define AFX_THALESDRAWDLL_H__1D87FD7A_3656_426A_8564_D2687DCC7B85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CThalesDrawDLLApp
// See ThalesDrawDLL.cpp for the implementation of this class
//

class CThalesDrawDLLApp : public CWinApp
{
public:
	CThalesDrawDLLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThalesDrawDLLApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CThalesDrawDLLApp)
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

#endif // !defined(AFX_THALESDRAWDLL_H__1D87FD7A_3656_426A_8564_D2687DCC7B85__INCLUDED_)
