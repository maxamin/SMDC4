// SMS4DCDoc.cpp : implementation of the CSMS4DCDoc class
//

#include "stdafx.h"
#include "SMS4DC.h"

#include "SMS4DCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCDoc

IMPLEMENT_DYNCREATE(CSMS4DCDoc, CDocument)

BEGIN_MESSAGE_MAP(CSMS4DCDoc, CDocument)
	//{{AFX_MSG_MAP(CSMS4DCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCDoc construction/destruction

CSMS4DCDoc::CSMS4DCDoc()
{
	colormaptype = _T("Topo_0");
	m_tile.ColorMap(colormaptype);
	for (int i=0;i<256;i++)
		RGBt[i]=m_tile.RGBt[i];

	CString AppPath = ((CSMS4DCApp *)AfxGetApp())->m_AppPath ;
	TileInfo = AppPath + _T("Texts\\globe.txt");

	TileX = ((CSMS4DCApp *)AfxGetApp())->TileX ;
	TileY = ((CSMS4DCApp *)AfxGetApp())->TileY ;

	PreGetData();
	GetData();
}

CSMS4DCDoc::~CSMS4DCDoc()
{
//	buf = NULL;
//	delete [] buf;
}

BOOL CSMS4DCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCDoc serialization

void CSMS4DCDoc::Serialize(CArchive& ar)
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
// CSMS4DCDoc diagnostics

#ifdef _DEBUG
void CSMS4DCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSMS4DCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCDoc commands

void CSMS4DCDoc::PreGetData()
{
	m_tile.getTileInfo(TileInfo,&TileX,&TileY,&m_Npx,&m_Npy,&m_Nod,
										m_FilesPath,m_FilesPrefix);
	Width  = 2*m_Npx;
	Height = 2*m_Npy;

	m_Lower_left_x=m_tile.m_Lower_left_x;
	m_Lower_left_y=m_tile.m_Lower_left_y;
	m_Resolution_x=m_tile.m_Resolution_x;
	m_Resolution_y=m_tile.m_Resolution_y;
	m_NoData=m_tile.m_NoData;
	m_MachineFormat[0]=m_tile.m_MachineFormat[0];
	m_Nxmax = m_tile.m_Nxmax;
	m_Nymax = m_tile.m_Nymax;

((CSMS4DCApp *)AfxGetApp())->m_Nxmax = m_Nxmax;
}



void CSMS4DCDoc::GetData()
{
//	buf = NULL;
//	delete [] buf;
//	buf = new _int16[1200][1200];

//	TileX = min(m_Nxmax-1,max(1,TileX));
	TileY = min(m_Nymax-1,max(1,TileY));

	bufMax=-32768;   	bufMin=32767;
	m_tile.getTileBuf(TileX,TileY,   m_Npx,m_Npy,m_Nod,
					   m_FilesPath,m_FilesPrefix,
					   buf,	   &bufMin,&bufMax);
}


BOOL CSMS4DCDoc::IsMapCircle()
{
	double X0 = m_Lower_left_x;
	double Xn = X0 + (m_Npx*m_Nxmax-1)*m_Resolution_x;

	long Xn_X0 = Round(Xn-X0); 
	if(Xn_X0==360)	return TRUE;
	return FALSE;
}

long CSMS4DCDoc::Round(double x) 
{
	long y;
	long x1 = (int) x;
	if(x>=0)	{long x2 = x1+1;		y = ( (x > ((double)x1)+0.45) ? x2 : x1);}
	else		{long x2 = x1-1;		y = ( (x > ((double)x2)+0.45) ? x1 : x2);}
	return y;
}