// Pro_LoS_AreaDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_LoS_AreaDoc.h"
#include <math.h>
#include "UTM.h"
#include "ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaDoc

IMPLEMENT_DYNCREATE(CPro_LoS_AreaDoc, CDocument)

CPro_LoS_AreaDoc::CPro_LoS_AreaDoc()
{
	colormaptype="Jet";
	m_tile.ColorMap(colormaptype);
	for (int i=0;i<256;i++)
		RGBt[i]=m_tile.RGBt[i];

	m_NoData=(_int16)(m_tile.m_NoData);

	bufMin=32767;	bufMax=-32768;
	ErMin=0.0;	ErMax=1.0;

	m_ZoomFactor=1;

	m_NoData = -500;		//98/01/12
	m_ReadyDoc=0;
}

BOOL CPro_LoS_AreaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_LoS_AreaDoc::~CPro_LoS_AreaDoc()
{
	delete [] bufAreaLoS;
	delete [] bufArea;
	delete [] Er;

}


BEGIN_MESSAGE_MAP(CPro_LoS_AreaDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_LoS_AreaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaDoc diagnostics

#ifdef _DEBUG
void CPro_LoS_AreaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_LoS_AreaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaDoc serialization

void CPro_LoS_AreaDoc::Serialize(CArchive& ar)
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
// CPro_LoS_AreaDoc commands



void CPro_LoS_AreaDoc::GetData()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

LoSlon_ST = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(LoSlon_ST,TileX);
LoSlon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(LoSlon0,  TileX);
LoSlonmax = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(LoSlonmax,TileX);	//97/12/21

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for(int i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j]=bufAreaLoS[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
	//		bufMin=min(bufMin,bufArea[i+Width*j]);		//98/01/12
	//		bufMax=max(bufMax,bufArea[i+Width*j]);
		}

	Er = new double[Width*Height];

	double teta_STi,hi,hii ,ds,tetai,lat0i , lon0i,az,dist;
	double pi=4.0*atan(1.0),  rearth=6371.0;

	double Hg = LatLon2Hg(LoSlat_ST, LoSlon_ST);		//98/01/12	
//	CPoint m_Point_ST,pointi,pointii;
//	LatLon2Point(LoSlat_ST,LoSlon_ST, &m_Point_ST) ;
//	double Hg = Point2Hg(m_Point_ST);

	double lat_j,lon_i;

/*	//97/12/21
	double step = 1.0/m_ZoomFactor;
	CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
	if (TileInfo != globeTileInfo)
		step=(m_Resolution_x/1000.0)/m_ZoomFactor;
*/
//double step = 0.5*Distance_km(LoSlat0, LoSlon0, LoSlat0+m_Resolution_x, LoSlon0+m_Resolution_x)/m_ZoomFactor;
double disttest1 = Distance_km(LoSlat_ST, LoSlon_ST, LoSlat_ST+0, LoSlon_ST+m_Resolution_x);
double disttest2 = Distance_km(LoSlat_ST, LoSlon_ST, LoSlat_ST+m_Resolution_x, LoSlon_ST+0);
double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

double dr = 2.0*LoSk*rearth;		//98/01/12
double Hasl_ST = Hg + LoSHagl_ST;

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			lat_j = LoSlat0+(j/m_ZoomFactor)*m_Resolution_x;
			lon_i = LoSlon0+(i/m_ZoomFactor)*m_Resolution_x;
			/*
			CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
			if (TileInfo != globeTileInfo)
			{
				CUtm m_utm;
				m_utm.y = lat_j;
				m_utm.x = lon_i;
				m_utm.UTM2philambda();
				lat_j=m_utm.phi;
				lon_i=m_utm.lambda;
			}
			*/
			dist = Distance_km(LoSlat_ST,LoSlon_ST,lat_j,lon_i);	
	//		dist = max(dist,0.000001);		//98/01/20
			dist = max(dist,StepRes/2.0);	//98/01/20

			az   = Azimuth_Deg(LoSlat_ST,LoSlon_ST,lat_j,lon_i);

			hi = LatLon2Hg(lat_j,lon_i);		//98/01/12	
	//		LatLon2Point(lat_j,lon_i, &pointi);
	//		hi = Point2Hg(pointi);

			teta_STi = (LoSRxH+hi-Hasl_ST)/(1000.0*dist) - dist/dr;

			tetai = -pi/2.0;
			ds = 0.000001;
			while(ds<=dist)  
			{
				reckon( LoSlat_ST,LoSlon_ST, ds , az , &lat0i , &lon0i) ;
			
				hii = LatLon2Hg(lat0i, lon0i);		//98/01/12	
			//	LatLon2Point(lat0i, lon0i, &pointii) ;
			//	hii = Point2Hg(pointii);

				tetai = max(tetai   , (((hii-Hasl_ST)/(ds*1000.0))-(ds/dr)));
				ds = ds+StepRes;
			}
			Er[i+Width*j] = (teta_STi>=tetai);		//98/01/21
	//		if (teta_STi>=tetai)	Er[i+Width*j] = 1.0;
	//		else					Er[i+Width*j] = 0.0;

			////////////////////progress bar////////////////////
			if(progress_num%100==0)
			{
				progress_str.Format("%02d%%"+_Z(" complete"), progress_num*100/(Width*Height));
				bar.SetText(progress_str);
				bar.SetPos(progress_num);
				//bar.StepIt();
				PeekAndPump();
			}
			progress_num++;
			////////////////////progress bar////////////////////
		}
	m_MinValue = ErMin;
	m_MaxValue = ErMax;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

void CPro_LoS_AreaDoc::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
{
lon_deg = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon_deg,TileX);

/*	CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
	if (TileInfo != globeTileInfo)
	{
		CUtm m_utm;
		m_utm.phi=lat_deg;
		m_utm.lambda=lon_deg;
		m_utm.philambda2UTM();
		lat_deg=m_utm.y;
		lon_deg=m_utm.x;
	}*/

	double ix = (double)(m_ZoomFactor)*((lon_deg - LoSlon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - LoSlat0)/(m_Resolution_x));

	(*PointSt).x = (long)ix;
	(*PointSt).y = (long)(Height-1-jy);
}
double CPro_LoS_AreaDoc::Point2Hg(CPoint point1) 
{
	int i1=point1.x   ,   j1=(Height-1)-point1.y;
	_int16 Hg=bufArea[i1+Width*j1];
	return (double)Hg;
}
//98/01/12
double CPro_LoS_AreaDoc::LatLon2Hg(double lat_deg,double lon_deg) 
{
	CPoint pointi;
	LatLon2Point(lat_deg, lon_deg, &pointi) ;
	double Hg = Point2Hg(pointi);
	return Hg;
}

double CPro_LoS_AreaDoc::Distance_km(double lat1,double lon1,double lat2,double lon2) 
{
	double temp1,temp2,temp3,rng;

	double pi=4.0*atan(1.0);
	double R = 6371.0;

	lat1=lat1*pi/180.0;
	lat2=lat2*pi/180.0;
	lon1=lon1*pi/180.0;
	lon2=lon2*pi/180.0;

	temp1 = sin(lat1)*sin(lat2);
	temp2 = cos(lat1)*cos(lat2)*cos(lon2-lon1);
	temp3 = temp1+temp2;
	temp3=min(1.0,max(-1.0,temp3));

	rng = acos(temp3);

	rng=R*rng;    //km
	return (rng);
}
double CPro_LoS_AreaDoc::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) 
{
	double pi=4.0*atan(1.0);
	double epsilon =  0.000000017453;

	lat1=lat1*pi/180.0;
	lon1=lon1*pi/180.0;
	lat2=lat2*pi/180.0;
	lon2=lon2*pi/180.0;
	double az=0.0;

	if (lat1 >= pi/2.0-epsilon)
		az=pi;
	else if (lat1 <= epsilon-pi/2.0)
		az=0.0;
	else if (lat2 >= pi/2-epsilon)
		az=0.0;
	else if (lat2 <= epsilon-pi/2.0)
		az=pi;
	else
		{
			double fact1 = cos(lat2) * sin(lon2-lon1);
			double fact2 = cos(lat1) * sin(lat2);
			double fact3 = sin(lat1) * cos(lat2) * cos(lon2-lon1);
			az = atan2(fact1,fact2-fact3);

			//az=round(az,-8);
			int az8=(int)(az*100000000.0);
			az=((double)az8)/100000000.0;
			
			if (az < 0.0)
				az=2*pi+az;
		}
	az = az*180.0/pi;
	return az;
}

void CPro_LoS_AreaDoc::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) 
{
	double pi=4.0*atan(1.0);
	double R=6371.0;

	double rng_rad=rng_km/R;
	double az_rad=az_deg*pi/180.0;
	double lat_rad=lat_deg*pi/180.0;
	double lon_rad=lon_deg*pi/180.0;

	double temp1  = sin(lat_rad)*cos(rng_rad);          
	double temp2  = cos(lat_rad)*sin(rng_rad)*cos(az_rad);
	double newlat = asin(temp1+temp2);

	temp1  = sin(rng_rad)*sin(az_rad);            
	temp2  = cos(lat_rad)*cos(rng_rad);
	double temp3  = sin(lat_rad)*sin(rng_rad)*cos(az_rad);
	double newlon = lon_rad + atan2(temp1,temp2-temp3);

	*latC_deg=newlat*180.0/pi;
	*lonC_deg=newlon*180.0/pi;
}


BOOL CPro_LoS_AreaDoc::PeekAndPump()
{
	static MSG msg;
	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
	{
		if (!AfxGetApp()->PumpMessage())
		{
			::PostQuitMessage(0);
			return FALSE;
		}	
	}
	return TRUE;
}