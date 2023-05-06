// Pro_LoS_LineDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_LoS_LineDoc.h"
#include <math.h>
#include "UTM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineDoc

IMPLEMENT_DYNCREATE(CPro_LoS_LineDoc, CDocument)

CPro_LoS_LineDoc::CPro_LoS_LineDoc()
{
	m_ReadyDoc=0;
	m_ZoomFactor=1;
}

BOOL CPro_LoS_LineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_LoS_LineDoc::~CPro_LoS_LineDoc()
{
	delete [] m_di;
	delete [] m_hi;
	delete [] m_lati;
	delete [] m_loni;
	delete [] Er;
	delete [] bufAreaLoS;
	delete [] bufArea;
	delete [] Er0;
	delete [] Er1;

}


BEGIN_MESSAGE_MAP(CPro_LoS_LineDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_LoS_LineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineDoc diagnostics

#ifdef _DEBUG
void CPro_LoS_LineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_LoS_LineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineDoc serialization

void CPro_LoS_LineDoc::Serialize(CArchive& ar)
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
// CPro_LoS_LineDoc commands


void CPro_LoS_LineDoc::GetData() 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

Linelon_ST = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Linelon_ST,TileX);
Linelon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Linelon0,TileX);

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for(int i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
			bufArea[i+Width*j]=bufAreaLoS[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];

	Er=new double[Np];
	Er0=new double[Np];
	Er1=new double[Np];

	double pi=4.0*atan(1.0), rearth=6371.0;
	double teta_STi ,tetai,ds,lat0i,lon0i,hii,az,dist;

	CPoint pointii;

	double step=1.0/m_ZoomFactor;
	CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
	if (TileInfo != globeTileInfo)
		step=(m_Resolution_x/1000.0)/m_ZoomFactor;

	for ( i=0;i<Np;i++)
	{
		dist = Distance_km(Linelat_ST,Linelon_ST,m_lati[i],m_loni[i]);
		dist = max(dist , 0.0001);
		az=Azimuth_Deg(Linelat_ST,Linelon_ST,m_lati[i],m_loni[i]);

		teta_STi=(LineRxH+m_hi[i]-LineHagl_ST-LineHasl_ST)/(1000.0*dist) - dist/(2.0*Linek*rearth);

		tetai=-pi/2.0;
		ds=0.000001;
		while(ds<=dist)  
		{
			reckon( Linelat_ST,Linelon_ST, ds , az , &lat0i , &lon0i) ;
			LatLon2Point(lat0i , lon0i, &pointii) ;
			hii=Point2Hg(pointii);
			tetai=max(tetai   ,(((hii-LineHasl_ST-LineHagl_ST)/(ds*1000.0))-(ds/(2.0*Linek*rearth))));
			ds=ds+step;

		}
		Er[i] = ( (teta_STi>=tetai) ? 1.0 : 0.0);

		Er1[i]=Er[i]*m_hi[i];
		Er0[i]=(1.0-Er[i])*m_hi[i];

		if(Er1[i]==0)	Er1[i]=Hmin;
		if(Er0[i]==0)	Er0[i]=Hmin;

	}
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

double CPro_LoS_LineDoc::Distance_km(double lat1,double lon1,double lat2,double lon2) 
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


double CPro_LoS_LineDoc::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) 
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


void CPro_LoS_LineDoc::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) 
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


void CPro_LoS_LineDoc::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
{
lon_deg = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon_deg,TileX);

	CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
	if (TileInfo != globeTileInfo)
	{
		CUtm m_utm;
		m_utm.phi=lat_deg;
		m_utm.lambda=lon_deg;
		m_utm.philambda2UTM();
		lat_deg=m_utm.y;
		lon_deg=m_utm.x;
	}

	double ix = (double)(m_ZoomFactor)*((lon_deg - Linelon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - Linelat0)/(m_Resolution_x));

	(*PointSt).x = (long)ix;
	(*PointSt).y=(long)(Height-1-jy);
}

double CPro_LoS_LineDoc::Point2Hg(CPoint point1) 
{
	int i1=point1.x   ,   j1=(Height-1)-point1.y;
	_int16 Hg=bufArea[i1+Width*j1];
	return (double)Hg;
}