// SMS4DC.h : main header file for the SMS4DC application
//

#if !defined(AFX_SMS4DC_H__882D761B_76C4_4AF1_B430_6CD01BE6D816__INCLUDED_)
#define AFX_SMS4DC_H__882D761B_76C4_4AF1_B430_6CD01BE6D816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "DLLwrapper.h"

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCApp:
// See SMS4DC.cpp for the implementation of this class
//

class CSMS4DCApp : public CWinApp
{
public:

	CSMS4DCApp();
	virtual ~CSMS4DCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMS4DCApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSMS4DCApp)
	afx_msg void OnAppAbout();
	afx_msg BOOL OnFileNew();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		BOOL OpenNewDocument(const CString& strTarget);
		int xN,yN;

		int Nrow;
		CString *m_Sel;

		CString m_antfile;

		int TileX,TileY;
		void SetLandscape();
		CString m_CDataBaseSTR , m_CDBSTR;

		CString m_AppPath;
		CString m_UserName;
		int m_UserLevel;
		CString m_Lang;
		CString m_ctryLocal;
		void ctryQ();
		void timeQ();

		int   m_number_of_dlls ;  

		// number loaded
		DLLwrapper *m_LoadedDLLs ;   

		// pointer to objects
		int   LoadDLLs();
		int   RegisterDocTemplates();

		BOOL IsWin2000();
		BOOL PeekAndPump();
		void CDCToBmp24(CDC *pDC, CString fileOUT);
		BOOL VectorFileName(CString *sFile,CString *sPath , BOOL flag=TRUE ,CString sDefault=_T("*.txt")); 
		BOOL KmlSave(CString *sFile,CString *sPath , BOOL *flagShow,CString sDefault=_T("*.kml"));
		CString VectorFileNameSave(CString FileNameNL); 
		CString SaveDesktop(CDC *pDC, CString FileName);

		CView *m_pView;
		CString Query_STtable(); 

		void TranslateMenu(CMenu *pMenu);
		void TranslateDialog(CDialog *pDialog);
		CString GetTranslatedString(CString strOriginal);

	//	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
		CString _Z(CString s){ return (GetTranslatedString(_T(s))); };

		double ChangeLon(double lon,int Tx); 
		double ReverseLon(double lon);
		int m_Nxmax;
		void FindHelpFile();
		CString FindIndexFile(CString FilesPath, CString FilesPrefix); 

		void CSMS4DCApp::ToolBar_Function(int n);

		//Monitoring		98/12/17
		int m_modeFlagP1812NetB, m_modeFlagP1812NetF;
		int m_modeFlagP1546NetB, m_modeFlagP1546NetF;
		int m_modeFlagFreeNetB, m_modeFlagFreeNetF;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMS4DC_H__882D761B_76C4_4AF1_B430_6CD01BE6D816__INCLUDED_)
