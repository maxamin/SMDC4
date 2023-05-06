// VectorHandlingDoc.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "VectorHandlingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingDoc

IMPLEMENT_DYNCREATE(CVectorHandlingDoc, CDocument)

CVectorHandlingDoc::CVectorHandlingDoc()
{
}

BOOL CVectorHandlingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CVectorHandlingDoc::~CVectorHandlingDoc()
{
}


BEGIN_MESSAGE_MAP(CVectorHandlingDoc, CDocument)
	//{{AFX_MSG_MAP(CVectorHandlingDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingDoc diagnostics

#ifdef _DEBUG
void CVectorHandlingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVectorHandlingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingDoc serialization

void CVectorHandlingDoc::Serialize(CArchive& ar)
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
// CVectorHandlingDoc commands
