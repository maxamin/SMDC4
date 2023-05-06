// EffectiveHeigthDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "EffectiveHeigthDoc.h"

#include <math.h>

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthDoc

IMPLEMENT_DYNCREATE(CEffectiveHeigthDoc, CDocument)

CEffectiveHeigthDoc::CEffectiveHeigthDoc()
{
	colormaptype="Topo_1";
	m_tile.ColorMap(colormaptype);
	for (int i=0;i<256;i++)
		RGBt[i]=m_tile.RGBt[i];

	m_NoData=(_int16)(m_tile.m_NoData);

	bufMin=32767;	bufMax=-32768;
	m_ZoomFactor=16;
	m_ReadyDoc = 0;
	m_bflag = 0;
}

BOOL CEffectiveHeigthDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	return TRUE;
}

CEffectiveHeigthDoc::~CEffectiveHeigthDoc()
{
	if(m_bflag==1)
	{
		delete [] bufArea;
		delete [] bufAreaHeff;
	}
}


BEGIN_MESSAGE_MAP(CEffectiveHeigthDoc, CDocument)
	//{{AFX_MSG_MAP(CEffectiveHeigthDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthDoc diagnostics

#ifdef _DEBUG
void CEffectiveHeigthDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEffectiveHeigthDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthDoc serialization

void CEffectiveHeigthDoc::Serialize(CArchive& ar)
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
// CEffectiveHeigthDoc commands


void CEffectiveHeigthDoc::GetData()
{
	if(m_bflag==1)
	{
/*
		if      (TileInfo == (((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt")))		m_ZoomFactor = 16;
		else if (TileInfo == (((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\UserMap1.txt")))	m_ZoomFactor =  8;
		else if (TileInfo == (((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\UserMap2.txt")))	m_ZoomFactor =  2;
*/
		// 98/01/31
		if     (fabs((3600.0*m_Resolution_x- 1.0)<0.1))		m_ZoomFactor =  1;		//Arc  1"	Res = 0.00027777777777778
		if     (fabs((3600.0*m_Resolution_x- 3.0)<0.1))		m_ZoomFactor =  2;		//Arc  3"	Res = 0.00083333333333333
		else if(fabs((3600.0*m_Resolution_x-15.0)<0.1))		m_ZoomFactor =  8;		//Arc 15"	Res = 0.00416666641831398
		else												m_ZoomFactor = 16;		//Arc 30"	Res = 0.0083333333334

		Width  = m_ZoomFactor * m_W_Heff;
		Height = m_ZoomFactor * m_H_Heff;
		bufArea = new _int16[Width*Height];

		for(int i=0;i<Width;i++)
			for(int j=0;j<Height;j++)
			{
				bufArea[i+Width*j] = bufAreaHeff[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
				bufMin = min(bufMin,bufArea[i+Width*j]);
				bufMax = max(bufMax,bufArea[i+Width*j]);
			}

		lat0 = bufAreaHeff_lat0;
		lon0 = bufAreaHeff_lon0;
//		m_Resolution_x = m_Resolution_x;
	}
	lat_ST  = bufAreaHeff_lat_ST;
	lon_ST  = bufAreaHeff_lon_ST;
	Hagl_ST = bufAreaHeff_Hagl_ST;
	Name_ST = bufAreaHeff_Name_ST;
}

double CEffectiveHeigthDoc::Distance_km(double lat1,double lon1,double lat2,double lon2) 
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(lat1*pi/180.0),
			lon10 = (float)(lon1*pi/180.0),
			lat20 = (float)(lat2*pi/180.0),
			lon20 = (float)(lon2*pi/180.0),	rng;
	GEODSTR( &lon10, &lat10, &lon20, &lat20, &rng);
	return (rng);
}
