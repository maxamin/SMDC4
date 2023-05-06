// MainMapDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "MainMapDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainMapDoc

IMPLEMENT_DYNCREATE(CMainMapDoc, CDocument)

CMainMapDoc::CMainMapDoc()
{
}

BOOL CMainMapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMainMapDoc::~CMainMapDoc()
{
}


BEGIN_MESSAGE_MAP(CMainMapDoc, CDocument)
	//{{AFX_MSG_MAP(CMainMapDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainMapDoc diagnostics

#ifdef _DEBUG
void CMainMapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMainMapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainMapDoc serialization

void CMainMapDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMainMapDoc commands
