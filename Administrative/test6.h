// test6.h : main header file for the TEST6 application
//

#if !defined(AFX_TEST6_H__882D761B_76C4_4AF1_B430_6CD01BE6D816__INCLUDED_)
#define AFX_TEST6_H__882D761B_76C4_4AF1_B430_6CD01BE6D816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest6App:
// See test6.cpp for the implementation of this class
//

class CSMS4DCApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMS4DCApp)
	public:
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSMS4DCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
public:
		int xN,yN;

		int Nrow;
		CString *m_Sel;

		CString m_antfile;

		int TileX,TileY;
		CString m_CDataBaseSTR , m_CDBSTR;

		CString m_AppPath;
		CString m_UserName;
		int m_UserLevel;
		CString m_Lang;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST6_H__882D761B_76C4_4AF1_B430_6CD01BE6D816__INCLUDED_)
