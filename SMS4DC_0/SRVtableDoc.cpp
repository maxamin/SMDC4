// SRVtableDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "SRVtableDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSRVtableDoc

IMPLEMENT_DYNCREATE(CSRVtableDoc, CDocument)

CSRVtableDoc::CSRVtableDoc()
{
}

BOOL CSRVtableDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSRVtableDoc::~CSRVtableDoc()
{
}


BEGIN_MESSAGE_MAP(CSRVtableDoc, CDocument)
	//{{AFX_MSG_MAP(CSRVtableDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRVtableDoc diagnostics

#ifdef _DEBUG
void CSRVtableDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSRVtableDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSRVtableDoc serialization

void CSRVtableDoc::Serialize(CArchive& ar)
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
// CSRVtableDoc commands
