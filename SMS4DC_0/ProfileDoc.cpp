// ProfileDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "ProfileDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileDoc

IMPLEMENT_DYNCREATE(CProfileDoc, CDocument)

CProfileDoc::CProfileDoc()
{
	m_ReadyDoc=0;
	m_DrawFresnel = false;
}


BOOL CProfileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CProfileDoc::~CProfileDoc()
{
	delete [] m_di;
	delete [] m_hi;
	delete [] m_lati;
	delete [] m_loni;
}


BEGIN_MESSAGE_MAP(CProfileDoc, CDocument)
	//{{AFX_MSG_MAP(CProfileDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileDoc diagnostics

#ifdef _DEBUG
void CProfileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProfileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProfileDoc serialization

void CProfileDoc::Serialize(CArchive& ar)
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
// CProfileDoc commands
