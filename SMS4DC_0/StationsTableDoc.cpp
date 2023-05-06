// StationsTableDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "StationsTableDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationsTableDoc

IMPLEMENT_DYNCREATE(CStationsTableDoc, CDocument)

CStationsTableDoc::CStationsTableDoc()
{
}

BOOL CStationsTableDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CStationsTableDoc::~CStationsTableDoc()
{
}


BEGIN_MESSAGE_MAP(CStationsTableDoc, CDocument)
	//{{AFX_MSG_MAP(CStationsTableDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStationsTableDoc diagnostics

#ifdef _DEBUG
void CStationsTableDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStationsTableDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStationsTableDoc serialization

void CStationsTableDoc::Serialize(CArchive& ar)
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
// CStationsTableDoc commands
