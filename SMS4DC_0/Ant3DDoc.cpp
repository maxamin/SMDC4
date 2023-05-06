// Ant3DDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Ant3DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnt3DDoc

IMPLEMENT_DYNCREATE(CAnt3DDoc, CDocument)

CAnt3DDoc::CAnt3DDoc()
{
}

BOOL CAnt3DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CAnt3DDoc::~CAnt3DDoc()
{
}


BEGIN_MESSAGE_MAP(CAnt3DDoc, CDocument)
	//{{AFX_MSG_MAP(CAnt3DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnt3DDoc diagnostics

#ifdef _DEBUG
void CAnt3DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAnt3DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnt3DDoc serialization

void CAnt3DDoc::Serialize(CArchive& ar)
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
// CAnt3DDoc commands
