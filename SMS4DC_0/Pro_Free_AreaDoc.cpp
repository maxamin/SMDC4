// Pro_Free_AreaDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_Free_AreaDoc.h"
#include "ProgressBar.h"
#include "UTM.h"
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
// CPro_Free_AreaDoc

IMPLEMENT_DYNCREATE(CPro_Free_AreaDoc, CDocument)

CPro_Free_AreaDoc::CPro_Free_AreaDoc()
{
	colormaptype="Jet";
	m_tile.ColorMap(colormaptype);
	for (int i=0;i<256;i++)
		RGBt[i]=m_tile.RGBt[i];

	m_NoData=(_int16)(m_tile.m_NoData);

	bufMin=32767;	bufMax=-32768;
	ErMin=32767.0;	ErMax=-32768.0;

	m_ZoomFactor=1;

	m_ReadyDoc=0;

	m_level = 255;
	m_bThreshold = false;
	m_Threshold = 60.0;
}
/*
BOOL CPro_Free_AreaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}
*/
CPro_Free_AreaDoc::~CPro_Free_AreaDoc()
{
	delete [] bufAreaFree;
	delete [] bufArea;
	delete [] Er;
}


BEGIN_MESSAGE_MAP(CPro_Free_AreaDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_Free_AreaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_AreaDoc diagnostics

#ifdef _DEBUG
void CPro_Free_AreaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_Free_AreaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_AreaDoc serialization
/*
void CPro_Free_AreaDoc::Serialize(CArchive& ar)
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
*/

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_AreaDoc commands


void CPro_Free_AreaDoc::GetData()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

Freelon_ST = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelon_ST,TileX);
Freelon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelon0,TileX);
Freelonmax = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelonmax,TileX);	//97/12/21

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

	Er=new double[Width*Height];

	double Ghv=1.0,	dist;

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));
	//bar.SetBkColour(RGB(255,0,0));

	double lat_j,lon_i;

	CString antfile;
	antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,FreeANT_ST);

	int f0[360];	double rH[360]  ,  rV[360];
	ReadAntennaData(antfile,f0,rH,rV) ;

	double elevp,tp,fp,az,f,t;
	double pi=4.0*atan(1.0);

	double Hr = FreeRxH ,   k = Freek;
	double r = 6371000.0 , re = k*r;
	double AZ0 = FreeAZ_ST*pi/180.0 ,	EL0 = FreeEL_ST*pi/180.0  ,  Ht = FreeHagl_ST;

//	CPoint m_Point_ST,pointi;							//98/01/19
//	LatLon2Point(Freelat_ST,Freelon_ST, &m_Point_ST) ;
//	double Hg=Point2Hg(m_Point_ST);
	double Hg = LatLon2Hg(Freelat_ST,Freelon_ST);
	double Hgi;

//98/01/20
double disttest1 = Distance_km(Freelat_ST,Freelon_ST, Freelat_ST+0, Freelon_ST+m_Resolution_x);
double disttest2 = Distance_km(Freelat_ST,Freelon_ST, Freelat_ST+m_Resolution_x, Freelon_ST+0);
double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			lat_j = Freelat0+(j/m_ZoomFactor)*m_Resolution_x;
			lon_i = Freelon0+(i/m_ZoomFactor)*m_Resolution_x;
/*	//98/01/19
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
			dist=Distance_km(Freelat_ST,Freelon_ST,lat_j,lon_i);
		//	dist = max(dist,0.00001);	//km		//98/01/20
			dist = max(dist, StepRes/2.0);			//98/01/20

			//0000000000000000000000000000000000000000000000000000000000000000
			//                     Antenna    Effect
			//0000000000000000000000000000000000000000000000000000000000000000
			az=Azimuth_Deg(Freelat_ST,Freelon_ST,lat_j,lon_i);

		//	LatLon2Point(lat_j,lon_i, &pointi);	//98/01/19
		//	Hgi=Point2Hg(pointi);
			Hgi = LatLon2Hg(lat_j,lon_i);

									//with Terrain
			elevp = atan(((re+Hr+Hgi)*cos(1000.0*dist/re)-(re+Ht+Hg))/((re+Hr+Hgi)*sin(1000.0*dist/re)));
			dist = sqrt( pow(re+Ht+Hg,2.0) + pow(re+Hr+Hgi,2.0) - 2.0*(re+Ht+Hg)*(re+Hr+Hgi)*cos(1000.0*dist/re) );
									//without Terrain
			//elevp = atan(((re+Hr)*cos((dist*1000.0)/re)-(re+Ht+Hg))/((re+Hr)*sin((dist*1000.0)/re)));
			//dist = sqrt( pow(re+Ht+Hg,2.0) + pow(re+Hr,2.0) -2.0*(re+Ht+Hg)*(re+Hr)*cos(1000.0*dist/re) );

//dist=max(dist,0.05);	//m		//98/01/20
			dist=dist/1000.0;	fp=az*pi/180.0;		tp = (pi/2.0) - elevp;

			f = (180.0/pi)*atan2(sin(tp)*sin(fp-AZ0),(cos(EL0)*sin(tp)*cos(fp-AZ0)+cos(tp)*sin(EL0)));
			t = (180.0/pi)*acos(cos(tp)*cos(EL0)-sin(EL0)*sin(tp)*cos(fp-AZ0));

			if (f<0.0)		f=f+359.4;

			Ghv = Interp2(f0,rH,f,360) * Interp2(f0,rV,t,360);
			//0000000000000000000000000000000000000000000000000000000000000000

			Er[i+Width*j]=(sqrt(30.0*FreePtGt_ST*Ghv))/(1000.0*dist);
			Er[i+Width*j] = 120.0+20.0*(log10(Er[i+Width*j]));

			ErMax=max(ErMax , Er[i+Width*j] );
			ErMin=min(ErMin , Er[i+Width*j] );

			////////////////////progress bar////////////////////
			if(progress_num%100==0)
			{
				progress_str.Format("%02d%%" + _Z(" complete"), progress_num*100/(Width*Height));
				bar.SetText(progress_str);
				bar.SetPos(progress_num);
				//bar.StepIt();
				PeekAndPump();
			}
			progress_num++;
			////////////////////progress bar////////////////////
		}
	m_MinValue = (double)Round(ErMin)+1.0;	//98/01/19
	m_MaxValue = (double)Round(ErMax)-1.0;
//	m_MinValue = ErMin;
//	m_MaxValue = ErMax;

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}
//98/01/19
int CPro_Free_AreaDoc::Round(double x) 
{
	int y;
	int x1 = (int)x;
	if(x>=0)	{int x2 = x1+1;		y = ( (x > ((double)x1)+0.45) ? x2 : x1);}
	else		{int x2 = x1-1;		y = ( (x > ((double)x2)+0.45) ? x1 : x2);}
	return y;
}
/*
int CPro_Free_AreaDoc::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);
}
*/

double CPro_Free_AreaDoc::Distance_km(double lat1,double lon1,double lat2,double lon2) 
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

BOOL CPro_Free_AreaDoc::PeekAndPump()
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



void CPro_Free_AreaDoc::ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) 
{
	FILE *fid;
	if( (fid  = fopen(antfile,"rt")) != NULL )
	{
		char Name [20],
			 Gain_dBi [20],
			 BeamWidth_H [20],
			 BeamWidth_V [20],
			 Frq_Lo [20],
			 Frq_Hi [20],
			 Frq_unit [20],
			 Polarization [20],
			 dum[20];

		char Ang[20],PatH[20],PatV[20];

		fscanf( fid, "%s %s", dum,Name);
		fscanf( fid, "%s %s", dum,Gain_dBi);
		fscanf( fid, "%s %s", dum,BeamWidth_H);
		fscanf( fid, "%s %s", dum,BeamWidth_V);
		fscanf( fid, "%s %s", dum,Frq_Lo);
		fscanf( fid, "%s %s", dum,Frq_Hi);
		fscanf( fid, "%s %s", dum,Frq_unit);
		fscanf( fid, "%s %s", dum,Polarization);
		fscanf( fid, "%s", dum);

		double pi=4.0*atan(1.0);
		double rH1,rV1;
		for (int i=0;i<360;i++)
		{
			fscanf( fid, "%s %s %s", Ang,PatH,PatV);
			f0[i] = atoi(Ang);
			rH1 = atof(PatH);		rV1 = atof(PatV);
			rH1 = pow( 10.0 , (-rH1/10.0) );
			rV1 = pow( 10.0 , (-rV1/10.0) );
			rH[i]=rH1;		rV[i]=rV1;
		}
		fclose(fid);
	}
	else
	{
		CString str;
		str.Format(_Z("The Antenna name  [%s]  was not found!  \r\rThe Isotropic Antenna will be select."),antfile);
		MessageBox(NULL,str, _Z("Warning"), MB_ICONWARNING | MB_OK);

		for (int i=0;i<360;i++)
		{
			f0[i] = i;		rH[i]=1.0;		rV[i]=1.0;
		}
	}
}

double CPro_Free_AreaDoc::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) 
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

//98/01/19
double CPro_Free_AreaDoc::LatLon2Hg(double lat_deg,double lon_deg) 
{
	CPoint pointi;
	LatLon2Point(lat_deg, lon_deg, &pointi) ;
	double Hg = Point2Hg(pointi);
	return Hg;
}

void CPro_Free_AreaDoc::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
{
lon_deg = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon_deg,TileX);
/*	//98/01/19
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
*/
	double ix = (double)(m_ZoomFactor)*((lon_deg - Freelon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - Freelat0)/(m_Resolution_x));

	(*PointSt).x = (long)ix;
	(*PointSt).y=(long)(Height-1-jy);
}

double CPro_Free_AreaDoc::Point2Hg(CPoint point1) 
{
	int i1=point1.x   ,   j1=(Height-1)-point1.y;
	_int16 Hg=bufArea[i1+Width*j1];
	return (double)Hg;
}


double CPro_Free_AreaDoc::Interp2(int *D0,double *E0,double d,int num) 
{
	double d1,d2,E1,E2,Eb;
	if (d<D0[0])
	{
		d1 = D0[0];		d2 = D0[1];
		E1 = E0[0];		E2 = E0[1];
	}
	else if (d>D0[num-1])
	{
		d1 = D0[num-2];	d2 = D0[num-1];
		E1 = E0[num-2];	E2 = E0[num-1];
	}
	else
	{
		/////////////////////////////////////////////
		int n1 = 0;
		while(d>=D0[n1])
		{
			n1++;
			if (n1==num)	break;
		}
		if (n1==0)			n1 = 1;

		d1 = D0[n1-1];	E1 = E0[n1-1];
		///////////////////////////////////////////////
		int n2 = num-1;
		while(d<=D0[n2])	n2--;

		d2 = D0[n2+1];	E2 = E0[n2+1];
		////////////////////////////////////////////////
	}
	Eb = ( (d1==d2) ? E1 : E1+(E2-E1)*(d-d1)/(d2-d1) );
	return Eb;
}

void CPro_Free_AreaDoc::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) 
{
	double pi=4.0*atan(1.0);
	float	lat_rad = (float)(lat_deg*pi/180.0),
			lon_rad = (float)(lon_deg*pi/180.0),
			RLON, RLAT,	 rng_km1 = (float)rng_km, az_deg1 = (float)az_deg;
	GEOPDAP( &lon_rad, &lat_rad, &rng_km1, &az_deg1, &RLON, &RLAT);
	*latC_deg = RLAT*180.0/pi;
	*lonC_deg = RLON*180.0/pi;
}