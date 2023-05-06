// IDWMMapDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "IDWMMapDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapDoc

IMPLEMENT_DYNCREATE(CIDWMMapDoc, CDocument)

CIDWMMapDoc::CIDWMMapDoc()
{
}

BOOL CIDWMMapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CIDWMMapDoc::~CIDWMMapDoc()
{
}


BEGIN_MESSAGE_MAP(CIDWMMapDoc, CDocument)
	//{{AFX_MSG_MAP(CIDWMMapDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapDoc diagnostics

#ifdef _DEBUG
void CIDWMMapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIDWMMapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapDoc serialization

void CIDWMMapDoc::Serialize(CArchive& ar)
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
// CIDWMMapDoc commands
