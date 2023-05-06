// ProfilePolygonDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "ProfilePolygonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePolygonDoc

IMPLEMENT_DYNCREATE(CProfilePolygonDoc, CDocument)

CProfilePolygonDoc::CProfilePolygonDoc()
{
	m_ReadyDoc=0;
}

BOOL CProfilePolygonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

CProfilePolygonDoc::~CProfilePolygonDoc()
{
	delete [] m_di;
	delete [] m_hi;
	delete [] m_lati;
	delete [] m_loni;
	delete [] Npt;


}


BEGIN_MESSAGE_MAP(CProfilePolygonDoc, CDocument)
	//{{AFX_MSG_MAP(CProfilePolygonDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfilePolygonDoc diagnostics

#ifdef _DEBUG
void CProfilePolygonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProfilePolygonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProfilePolygonDoc serialization

void CProfilePolygonDoc::Serialize(CArchive& ar)
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
// CProfilePolygonDoc commands
