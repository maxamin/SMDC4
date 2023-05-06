// Administrative.h : main header file for the ADMINISTRATIVE DLL
//

#if !defined(AFX_ADMINISTRATIVE_H__BEE6E235_EC73_4282_BB17_9CC6D1517DE2__INCLUDED_)
#define AFX_ADMINISTRATIVE_H__BEE6E235_EC73_4282_BB17_9CC6D1517DE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdministrativeApp
// See Administrative.cpp for the implementation of this class
//

class CAdministrativeApp : public CWinApp
{
public:
	CAdministrativeApp();
		void TranslateDialog(CDialog *pDialog);
		CString GetTranslatedString(CString strOriginal, CString Lang);
		CString m_Lang;
		//CString _Z(CString s){ return (GetTranslatedString(_T(s))); };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdministrativeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAdministrativeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#include "test6.h"
#include "Afxcview.h"
#include "Stdafx.h"
#include "resource.h"		// main symbols
#include "ChildFrm.h"

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADMINISTRATIVE_H__BEE6E235_EC73_4282_BB17_9CC6D1517DE2__INCLUDED_)
