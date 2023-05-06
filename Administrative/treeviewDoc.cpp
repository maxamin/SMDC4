// treeviewDoc.cpp : implementation of the CTreeviewDoc class
//

#include "stdafx.h"
#include "Administrative.h"

#include "treeviewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeviewDoc

IMPLEMENT_DYNCREATE(CTreeviewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTreeviewDoc, CDocument)
	//{{AFX_MSG_MAP(CTreeviewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeviewDoc construction/destruction

CTreeviewDoc::CTreeviewDoc()
{
	// TODO: add one-time construction code here

}

CTreeviewDoc::~CTreeviewDoc()
{
}

BOOL CTreeviewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTreeviewDoc serialization

void CTreeviewDoc::Serialize(CArchive& ar)
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
// CTreeviewDoc diagnostics

#ifdef _DEBUG
void CTreeviewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTreeviewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeviewDoc commands
