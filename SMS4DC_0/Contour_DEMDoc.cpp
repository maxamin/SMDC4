// Contour_DEMDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Contour_DEMDoc.h"
#include "ProgressBar.h"

#include "UTM.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMDoc

IMPLEMENT_DYNCREATE(CContour_DEMDoc, CDocument)

CContour_DEMDoc::CContour_DEMDoc()
{
	colormaptype="Topo_1";
	m_tile.ColorMap(colormaptype);
	for (int i=0;i<256;i++)
		RGBt[i]=m_tile.RGBt[i];

	m_NoData=(_int16)(m_tile.m_NoData);

	bufMin=32767.0;	bufMax=-32768.0;

	m_ZoomFactor=1;

	m_ReadyDoc=0;
}

BOOL CContour_DEMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CContour_DEMDoc::~CContour_DEMDoc()
{
	delete [] bufAreaFree;
	delete [] bufArea;

}


BEGIN_MESSAGE_MAP(CContour_DEMDoc, CDocument)
	//{{AFX_MSG_MAP(CContour_DEMDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMDoc diagnostics

#ifdef _DEBUG
void CContour_DEMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CContour_DEMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMDoc serialization

void CContour_DEMDoc::Serialize(CArchive& ar)
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
// CContour_DEMDoc commands

void CContour_DEMDoc::GetData()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for(int i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j]=bufAreaFree[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin=min(bufMin,bufArea[i+Width*j]);
			bufMax=max(bufMax,bufArea[i+Width*j]);
		}

	
	m_MinValue= bufMin;
	m_MaxValue= bufMax;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

}

