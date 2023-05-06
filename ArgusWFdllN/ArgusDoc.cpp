// ArgusDoc.cpp : implementation of the CArgusDoc class
//

#include "stdafx.h"
//#include "Argus.h"

#include "ArgusDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArgusDoc

IMPLEMENT_DYNCREATE(CArgusDoc, CDocument)

BEGIN_MESSAGE_MAP(CArgusDoc, CDocument)
	//{{AFX_MSG_MAP(CArgusDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArgusDoc construction/destruction

CArgusDoc::CArgusDoc()
{
	// TODO: add one-time construction code here

}

CArgusDoc::~CArgusDoc()
{
}

BOOL CArgusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CArgusDoc serialization

void CArgusDoc::Serialize(CArchive& ar)
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
// CArgusDoc diagnostics

#ifdef _DEBUG
void CArgusDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CArgusDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArgusDoc commands
