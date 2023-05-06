// AntennaFormDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "AntennaFormDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormDoc

IMPLEMENT_DYNCREATE(CAntennaFormDoc, CDocument)

CAntennaFormDoc::CAntennaFormDoc()
{
}

BOOL CAntennaFormDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CAntennaFormDoc::~CAntennaFormDoc()
{
}


BEGIN_MESSAGE_MAP(CAntennaFormDoc, CDocument)
	//{{AFX_MSG_MAP(CAntennaFormDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormDoc diagnostics

#ifdef _DEBUG
void CAntennaFormDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAntennaFormDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormDoc serialization

void CAntennaFormDoc::Serialize(CArchive& ar)
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
// CAntennaFormDoc commands
