// Area3DDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Area3DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArea3DDoc

IMPLEMENT_DYNCREATE(CArea3DDoc, CDocument)

CArea3DDoc::CArea3DDoc()
{

}

BOOL CArea3DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CArea3DDoc::~CArea3DDoc()
{

}


BEGIN_MESSAGE_MAP(CArea3DDoc, CDocument)
	//{{AFX_MSG_MAP(CArea3DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArea3DDoc diagnostics

#ifdef _DEBUG
void CArea3DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CArea3DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArea3DDoc serialization

void CArea3DDoc::Serialize(CArchive& ar)
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
// CArea3DDoc commands
