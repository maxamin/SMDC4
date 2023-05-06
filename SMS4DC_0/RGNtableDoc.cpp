// RGNtableDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "RGNtableDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGNtableDoc

IMPLEMENT_DYNCREATE(CRGNtableDoc, CDocument)

CRGNtableDoc::CRGNtableDoc()
{
}

BOOL CRGNtableDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CRGNtableDoc::~CRGNtableDoc()
{
}


BEGIN_MESSAGE_MAP(CRGNtableDoc, CDocument)
	//{{AFX_MSG_MAP(CRGNtableDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRGNtableDoc diagnostics

#ifdef _DEBUG
void CRGNtableDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRGNtableDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRGNtableDoc serialization

void CRGNtableDoc::Serialize(CArchive& ar)
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
// CRGNtableDoc commands
