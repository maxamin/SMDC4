// DataBaseLDLG.cpp: implementation of the CDataBaseLDLG class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sms4dc.h"
#include "DataBaseLDLG.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataBaseLDLG::CDataBaseLDLG()
{
	m_Heff1 = FALSE;
	m_ReportFlag = TRUE;
	m_Title = _Z("Station Table");

	m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	m_Tbl = ((CSMS4DCApp *)AfxGetApp())->m_CDataBaseSTR;
	m_Lang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
}

CDataBaseLDLG::~CDataBaseLDLG()
{
}

/////////////////////////////List_DataBase.lib/////////////////////////////
extern "C" int WINAPI List_DataBase(HWND hWndParent,CString mDB,CString mTbl,
									 CStringArray *mSel, 
									 CString mTitle, BOOL mReportFlag,CString mLang,
									 BOOL *mHeff1);
int CDataBaseLDLG::DoModal()
{
	CStringArray mSel;
	int uFlag = List_DataBase(NULL,m_DB,m_Tbl, &mSel,m_Title, m_ReportFlag,m_Lang, &m_Heff1);
	int Nrow = mSel.GetSize();
	
	((CSMS4DCApp *)AfxGetApp())->Nrow = Nrow;

	((CSMS4DCApp *)AfxGetApp())->m_Sel = NULL;
	delete [] ((CSMS4DCApp *)AfxGetApp())->m_Sel;
	((CSMS4DCApp *)AfxGetApp())->m_Sel = new CString[Nrow];

    for (int i = 0 ; i<Nrow; i++)
		((CSMS4DCApp *)AfxGetApp())->m_Sel[i] = mSel.GetAt(i);

	return uFlag;
}

