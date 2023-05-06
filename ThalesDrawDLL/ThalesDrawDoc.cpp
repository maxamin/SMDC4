// ThalesDrawDoc.cpp : implementation of the CThalesDrawDoc class
//

#include "stdafx.h"
//#include "ThalesDraw.h"
#include "ThalesDrawDLL.h"

#include "ThalesDrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThalesDrawDoc

IMPLEMENT_DYNCREATE(CThalesDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CThalesDrawDoc, CDocument)
	//{{AFX_MSG_MAP(CThalesDrawDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThalesDrawDoc construction/destruction

CThalesDrawDoc::CThalesDrawDoc()
{
	// TODO: add one-time construction code here

}

CThalesDrawDoc::~CThalesDrawDoc()
{
}

BOOL CThalesDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CThalesDrawDoc serialization

void CThalesDrawDoc::Serialize(CArchive& ar)
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
// CThalesDrawDoc diagnostics

#ifdef _DEBUG
void CThalesDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CThalesDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThalesDrawDoc commands
