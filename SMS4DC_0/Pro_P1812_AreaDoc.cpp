// Pro_P1812_AreaDoc.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Pro_P1812_AreaDoc.h"

#include <math.h>
#include "UTM.h"
#include "ProgressBar.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_AreaDoc

IMPLEMENT_DYNCREATE(CPro_P1812_AreaDoc, CDocument)

CPro_P1812_AreaDoc::CPro_P1812_AreaDoc()
{
	colormaptype="Jet";
	m_tile.ColorMap(colormaptype);
	for (int i=0;i<256;i++)
		RGBt[i]=m_tile.RGBt[i];

	m_NoData=(_int16)(m_tile.m_NoData);

	bufMin=32767;	bufMax=-32768;
	ErMin=32767;	ErMax=-32768;

	m_ZoomFactor=1;

	m_ReadyDoc=0;
	m_level = 255;
	m_bThreshold = false;
	m_Threshold = 10.0;

	long UNR = 72 ;		WDBUNIT(&UNR) ;

	pi = 4.0*atan(1.0);
	D2R = pi/180.0;
	R2D = 180.0/pi;
}

BOOL CPro_P1812_AreaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_P1812_AreaDoc::~CPro_P1812_AreaDoc()
{
	bufAreaP1812 = NULL;	delete [] bufAreaP1812;
	bufArea = NULL;			delete [] bufArea;
	Er = NULL;				delete [] Er;
}


BEGIN_MESSAGE_MAP(CPro_P1812_AreaDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_P1812_AreaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_AreaDoc diagnostics

#ifdef _DEBUG
void CPro_P1812_AreaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_P1812_AreaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_AreaDoc serialization

void CPro_P1812_AreaDoc::Serialize(CArchive& ar)
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
// CPro_P1812_AreaDoc commands

__declspec(dllimport) double BasicTxLossP1812V3(double* mD, double* mH, int *mZ, long Np, double LatM, double DELTA_N, double N0,
												double pTime, double pLocation, double f, double htg, double hrg, 
												int pol, int srv, int InOutDoor, int zone);

void CPro_P1812_AreaDoc::GetData()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for(int i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j]=bufAreaP1812[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin=min(bufMin,bufArea[i+Width*j]);
			bufMax=max(bufMax,bufArea[i+Width*j]);
		}

	P1812lon_ST = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1812lon_ST,TileX);
	P1812lon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1812lon0,  TileX);
	P1812lonmax = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1812lonmax,TileX);	//97/12/21

	double dist,ds, az, latp,lonp, lat_j,lon_i;

	double rearth = 6371.0 , Ghv;
	CPoint m_Point_STcr3,m_Point_STcr15;

	Er = new double[Width*Height];
	double Hg = LatLon2Hg(P1812lat_ST, P1812lon_ST);

//	CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
//	double StepRes=1.0/m_ZoomFactor;
//	if (TileInfo != globeTileInfo)
//		StepRes=(m_Resolution_x/1000.0)/m_ZoomFactor;

double disttest1 = Distance_km(P1812lat_ST, P1812lon_ST, P1812lat_ST+0, P1812lon_ST+m_Resolution_x);
double disttest2 = Distance_km(P1812lat_ST, P1812lon_ST, P1812lat_ST+m_Resolution_x, P1812lon_ST+0);
double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	CString antfile;
	antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,P1812ANT_ST);

	int f0[360];	double rH[360]  ,  rV[360];
	ReadAntennaData(antfile,f0,rH,rV) ;
	
	double AZ0 = P1812AZ_ST*D2R ,	EL0 = P1812EL_ST*D2R  ,  Ht = P1812Hagl_ST,		Hr = P1812RxH ;
	double Hgi, elevp,tp,fp,f,t;

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

/////////////////////Load IDWM map////////////////
	LoadIDWMmap();
//////////////////////////////////////////////////
	int pol = 1;
	if     (P1812Polarization_ST=="H") pol = 0;
	else if(P1812Polarization_ST=="V") pol = 1;

	double Lb, f_GHz = P1812fMHz_ST/1000.0;

	CString FilepathData = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + "\\Texts\\";
	double LongM, LatM, N0, DELTA_N;

	int status = 0;
	float dataDN50[121][241], dataN050[121][241];
	if( dat_filesDATA(FilepathData + "\\DN50.dat", dataDN50)==0)		status  = 1;
	if( dat_filesDATA(FilepathData + "\\N050.dat", dataN050)==0)		status  = 2;

	double P1812PtGt_STp = P1812PtGt_ST/1650.0;
	double dist1000_re,sintp, costp, sinfp_AZ0, cosfp_AZ0, sinEL0 = sin(EL0), cosEL0 = cos(EL0), re;

	if(status==0)
	{
		for( i=0;i<Width;i++)
			for(int j=0;j<Height;j++)
			{
				lat_j = P1812lat0+(j/m_ZoomFactor)*m_Resolution_x;
				lon_i = P1812lon0+(i/m_ZoomFactor)*m_Resolution_x;
/*	//97/12/21
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
				Hgi  = LatLon2Hg(lat_j, lon_i);

				dist = Distance_km(P1812lat_ST,P1812lon_ST, lat_j,lon_i);	
			//	dist = max(dist,0.00001);		//98/01/20
				dist = max(dist, StepRes/2.0);	//98/01/20
				az   = Azimuth_Deg(P1812lat_ST,P1812lon_ST, lat_j,lon_i);

			//	if((dist<0.25)||(dist<StepRes))		Lb = 92.5  + 20.0*log10(dist * f_GHz);		//98/01/20
				if((dist<0.25)||(dist<2.0*StepRes))	Lb = 92.5  + 20.0*log10(dist * f_GHz);		//98/01/20
				else
				{
					reckon(P1812lat_ST, P1812lon_ST, dist/2.0, az, &LatM, &LongM) ;
					N0      = dat_filesDATAout(LatM,LongM, dataN050);
					DELTA_N = dat_filesDATAout(LatM,LongM, dataDN50);
					P1812k = 157.0 / (157.0 - DELTA_N);	// Equation (6)
					re = P1812k * rearth * 1000.0;

					long Np = 2 + (int)(1 + dist/StepRes);
					double *mD  = new double[Np];
					double *mH  = new double[Np];
					int *mZ = new int[Np+1];

					Np = 0;		ds = 0.0;
					while(ds<dist)
					{
						reckon(P1812lat_ST, P1812lon_ST, ds, az, &latp, &lonp);
						mH[Np] = LatLon2Hg(latp , lonp);
						mD[Np] = ds;
						mZ[Np] = LandSeaCoastal(lonp, latp);
						Np++;
						ds = ds + StepRes;
					}
					mH[Np] = Hgi;	
					mD[Np] = dist;
					mZ[Np] = LandSeaCoastal(lon_i, lat_j);
					Np++;
					mZ[Np] = 0;

					Lb = BasicTxLossP1812V3(mD, mH, mZ, Np, LatM, DELTA_N, N0,
											P1812time, P1812location, f_GHz, Ht, Hr, pol, 
											P1812Service, P1812IODoor, P1812Clutter);
					delete [] mD;	delete [] mH;	delete [] mZ;
				}

				//0000000000000000000000000000000000000000000000000000000000000000
				//                     Antenna    Effect
				//0000000000000000000000000000000000000000000000000000000000000000
				dist1000_re = 1000.0*dist/re;
										
				elevp = atan(((re+Hr+Hgi)*cos(dist1000_re)-(re+Ht+Hg))/((re+Hr+Hgi)*sin(dist1000_re))); //with Terrain
		//		elevp = atan(((re+Hr    )*cos(dist1000_re)-(re+Ht+Hg))/((re+Hr    )*sin(dist1000_re))); //without Terrain

				fp = az*D2R;		tp = (pi/2.0) - elevp;
				sinfp_AZ0 = sin(fp-AZ0);	cosfp_AZ0 = cos(fp-AZ0);
				sintp = sin(tp);			costp = cos(tp);

				f = R2D*atan2(sintp*sinfp_AZ0 , cosEL0*sintp*cosfp_AZ0 + costp*sinEL0);
				t = R2D*acos(costp*cosEL0 - sinEL0*sintp*cosfp_AZ0);

				if (f<0.0)	f=f+359.4;

				Ghv = Interp2(f0,rH,f,360) * Interp2(f0,rV,t,360);
				//0000000000000000000000000000000000000000000000000000000000000000

				double Eb1 = 199.36 + 20.0*log10(f_GHz) - Lb;
				double Eb = Eb1 + 10.0*log10(P1812PtGt_STp*Ghv);
				Er[i+Width*j] = Eb;

		//		ErMax = max(ErMax, Eb );
		//		ErMin = min(ErMin, Eb );
				if(Eb>ErMax)  ErMax = Eb;
				if(Eb<ErMin)  ErMin = Eb;

				////////////////////progress bar////////////////////
				if(progress_num%100==0)
				{
					progress_str.Format("%02d%%"+_Z(" complete"), progress_num*100/(Width*Height));
					bar.SetText(progress_str);
					bar.SetPos(progress_num);
					PeekAndPump();
				}
				progress_num++;
				////////////////////progress bar////////////////////
			}
	}
	if     (status==1)	MessageBox(NULL, _Z("The file 'DN50.dat' was not opened."), _Z("Warning!!!"), MB_ICONWARNING | MB_OK);
	else if(status==2)	MessageBox(NULL, _Z("The file 'N050.dat' was not opened."), _Z("Warning!!!"), MB_ICONWARNING | MB_OK);

	m_MinValue = (double)Round(ErMin)+1.0;	//98/01/19
	m_MaxValue = (double)Round(ErMax)-1.0;
//	m_MinValue = ErMin;
//	m_MaxValue = ErMax;

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

//98/01/19
int CPro_P1812_AreaDoc::Round(double x) 
{
	int y;
	int x1 = (int)x;
	if(x>=0)	{int x2 = x1+1;		y = ( (x > ((double)x1)+0.45) ? x2 : x1);}
	else		{int x2 = x1-1;		y = ( (x > ((double)x2)+0.45) ? x1 : x2);}
	return y;
}
/*
int CPro_P1812_AreaDoc::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);
}
*/

void CPro_P1812_AreaDoc::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt)
{
lon_deg = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon_deg,TileX);
/*
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
	double ix = (double)(m_ZoomFactor)*((lon_deg - P1812lon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - P1812lat0)/(m_Resolution_x));

	(*PointSt).x = (long)ix;
	(*PointSt).y = (long)(Height-1-jy);
}
double CPro_P1812_AreaDoc::Point2Hg(CPoint point1)
{
	int i1=point1.x   ,   j1=(Height-1)-point1.y;
	_int16 Hg=bufArea[i1+Width*j1];
	return (double)Hg;
}
double CPro_P1812_AreaDoc::LatLon2Hg0(double lat_deg,double lon_deg)
{
	CPoint pointi;
	LatLon2Point(lat_deg, lon_deg, &pointi) ;
	double hi = Point2Hg(pointi);
	return hi;
}

double CPro_P1812_AreaDoc::LatLon2Hg(double lat_deg,double lon_deg)
{
	lon_deg = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon_deg,TileX);
/*
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
	double ix = (double)(m_ZoomFactor)*((lon_deg - P1812lon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - P1812lat0)/(m_Resolution_x));

	double Hg = RoundBUF_Hg(ix, jy);
	return Hg;
}
double CPro_P1812_AreaDoc::RoundBUF_Hg(double xps,double yps) 
{
	int i1 = int(xps);				int j1 = int(yps);
	i1 = max(min(i1,Width-1),0);	j1 = max(min(j1,Height-1),0);
	int i2 = i1+1;					int j2 = j1+1;
	double h11, h12, h21, h22, hx1, hx2, hy;

	if     ((i1 == (Width-1))&&(j1 == (Height-1)))		hy = (double)bufArea[i1+Width*j1];
	else if((i1 == (Width-1))&&(j1  < (Height-1)))
	{
		h11 = (double)bufArea[i1+Width*j1]; h12 = (double)bufArea[i1+Width*j2];	hy  = h11 +(yps-j1)*(h12-h11)/(j2-j1);
	}
	else if((i1 < (Width-1))&&(j1 == (Height-1)))
	{
		h11 = (double)bufArea[i1+Width*j1]; h21 = (double)bufArea[i2+Width*j1];	hy  = h11 +(xps-i1)*(h21-h11)/(i2-i1);
	}
	else
	{
		h11 = (double)bufArea[i1+Width*j1]; h12 = (double)bufArea[i1+Width*j2]; h21 = (double)bufArea[i2+Width*j1]; h22 = (double)bufArea[i2+Width*j2];

		hx1 = h11 +(xps-i1)*(h21-h11)/(i2-i1); hx2 = h12 +(xps-i1)*(h22-h12)/(i2-i1);
		hy  = hx1 +(yps-j1)*(hx2-hx1)/(j2-j1);
	}
	return hy;
}


double CPro_P1812_AreaDoc::Distance_km(double lat1,double lon1,double lat2,double lon2)
{
	float	lat10 = (float)(lat1*D2R),
			lon10 = (float)(lon1*D2R),
			lat20 = (float)(lat2*D2R),
			lon20 = (float)(lon2*D2R),	rng;
	GEODSTR( &lon10, &lat10, &lon20, &lat20, &rng);
	return (rng);

/*
	double temp1,temp2,temp3,rng;
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
*/
}

double CPro_P1812_AreaDoc::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2)
{
	float	lat10 = (float)(lat1*D2R),
			lon10 = (float)(lon1*D2R),
			lat20 = (float)(lat2*D2R),
			lon20 = (float)(lon2*D2R),	RDIST, RAZIM;
	GEOPPDA( &lon10 ,&lat10, &lon20,&lat20, &RDIST, &RAZIM);
	return RAZIM;

/*
	double epsilon =  0.000000017453;
	lat1=lat1*pi/180.0;
	lon1=lon1*pi/180.0;
	lat2=lat2*pi/180.0;
	lon2=lon2*pi/180.0;
	double az=0.0;

	if (lat1 >= pi/2.0-epsilon)			az=pi;
	else if (lat1 <= epsilon-pi/2.0)	az=0.0;
	else if (lat2 >= pi/2-epsilon)		az=0.0;
	else if (lat2 <= epsilon-pi/2.0)	az=pi;
	else
	{
		double fact1 = cos(lat2) * sin(lon2-lon1);
		double fact2 = cos(lat1) * sin(lat2);
		double fact3 = sin(lat1) * cos(lat2) * cos(lon2-lon1);
		az = atan2(fact1,fact2-fact3);

		//az=round(az,-8);
		int az8=(int)(az*100000000.0);
		az=((double)az8)/100000000.0;

		if (az < 0.0)		az=2*pi+az;
	}
	az = az*180.0/pi;
	return az;
*/
}

void CPro_P1812_AreaDoc::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg)
{
	float	lat_rad = (float)(lat_deg*D2R),
			lon_rad = (float)(lon_deg*D2R),
			RLON, RLAT,	 rng_km1 = (float)rng_km, az_deg1 = (float)az_deg;
	GEOPDAP( &lon_rad, &lat_rad, &rng_km1, &az_deg1, &RLON, &RLAT);
	*latC_deg = RLAT*R2D;
	*lonC_deg = RLON*R2D;
/*
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
*/
}

void CPro_P1812_AreaDoc::ReadAntennaData(CString antfile,int *f0,double *rH,double *rV)
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
		MessageBox(NULL,str, _Z("Warning!!!"), MB_ICONWARNING | MB_OK);
		for (int i=0;i<360;i++)
		{
			f0[i] = i;		rH[i]=1.0;		rV[i]=1.0;
		}

	}
}

BOOL CPro_P1812_AreaDoc::PeekAndPump()
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


double CPro_P1812_AreaDoc::Interp2(int *D0,double *E0,double d,int num)
{
	double d1,d2,E1,E2,Eb;
	if (d<D0[0])
	{
		d1=D0[0];d2=D0[1];
		E1=E0[0];E2=E0[1];
	}
	else if (d>D0[num-1])
	{
		d1=D0[num-2];d2=D0[num-1];
		E1=E0[num-2];E2=E0[num-1];
	}
	else
	{
		/////////////////////////////////////////////
		int n1=0;
		while(d>=D0[n1])
		{
			n1++;
			if (n1==num)
				break;
		}
		if (n1==0)
			n1=1;
		d1=D0[n1-1];E1=E0[n1-1];
		///////////////////////////////////////////////
		int n2=num-1;
		while(d<=D0[n2])
			n2--;
		d2=D0[n2+1];E2=E0[n2+1];
		////////////////////////////////////////////////
	}
	Eb=((d1==d2) ? E1 : E1+(E2-E1)*(d-d1)/(d2-d1));

	return Eb;
}

void CPro_P1812_AreaDoc::PathMean(double lon10, double lat10, double lon20, double lat20, double *LongM, double *LatM)
{
	double RDIST, RAZIM, RLON, RLAT;

	RDIST = Distance_km(lat10, lon10, lat20, lon20); 
	RAZIM = Azimuth_Deg(lat10, lon10, lat20, lon20); 
	reckon(lat10, lon10, RDIST/2.0, RAZIM, &RLAT, &RLON) ;

	*LongM = RLON;
	*LatM  = RLAT;
}

int CPro_P1812_AreaDoc::LandSeaCoastal(double RLON_deg,double RLAT_deg) 
{
	float RLON = (float)(RLON_deg*D2R);
	float RLAT = (float)(RLAT_deg*D2R);

//	long int N=4, IER;	GEOGCMS ( &N, &IER );
//	float RLON1 = (float)(RLON-pi/90.0), RLAT1 = (float)(RLAT-pi/90.0),
//		  RLON2 = (float)(RLON+pi/90.0), RLAT2 = (float)(RLAT+pi/90.0);

//	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
//	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2],  GC;
//	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
//	GEOGCM( &IVAL, (float *)WND, &IRANGE);

	float  GC;
	GEOGCP( &RLON, &RLAT, &GC);

	int zone = 3;
	if		(GC==1)		zone = 1;	//LandSea = "Coastal Zone : Sea";           B  1
	else if (GC==3)		zone = 2;	//LandSea = "Coastal Zone : Coastal Land";  A1 2
	else if (GC==4)		zone = 3;	//LandSea = "Coastal Zone : InLand";        A2 3

/*
	CString zone = "A2";
	if		(GC==1)		zone = "B";		//LandSea = "Coastal Zone : Sea";			B  1
	else if (GC==3)		zone = "A1";	//LandSea = "Coastal Zone : Coastal Land";  A1 2
	else if (GC==4)		zone = "A2";	//LandSea = "Coastal Zone : InLand";        A2 3
*/
	return zone;
}

int CPro_P1812_AreaDoc::dat_filesDATA(CString dat_fname, float data[121][241])
{
	FILE *fp;

	if ((fp = fopen(dat_fname,"r"))==NULL)	return 0;

	fread( data,sizeof(float),121*241, fp );	
	fclose(fp);

	return 1;
}
double CPro_P1812_AreaDoc::dat_filesDATAout(double LatM,double LongM, float data[121][241])
{
	double x,y,h11,h12,h21,h22,LongM1;
	int i1,i2,j1,j2;
	LongM1 = LongM + 360.0*(LongM<0);

	x = LongM1/1.5;			y = (90.0-LatM)/1.5;

	j1 = int(x);	j2 = j1+1;
	i1 = int(y);	i2 = i1+1;

	h11 = data[i1][j1];		h12 = data[i1][j2];
	h21 = data[i2][j1];		h22 = data[i2][j2];

	double hy = h11*(1+i1-y)*(1+j1-x) + h21*(y-i1)*(1+j1-x) + h12*(1+i1-y)*(x-j1) + h22*(y-i1)*(x-j1);
	return hy;
}

void CPro_P1812_AreaDoc::LoadIDWMmap() 
{
	double minLat = P1812lat0,	 maxLat = P1812lat0+((Height-1)/m_ZoomFactor)*m_Resolution_x;
	double minLon = P1812lon0,	 maxLon = P1812lon0+((Width- 1)/m_ZoomFactor)*m_Resolution_x;
	float RLON1 = (float)(minLon*D2R-pi/90.0), RLAT1 = (float)(minLat*D2R-pi/90.0),	  RLON2 = (float)(maxLon*D2R+pi/90.0), RLAT2 = (float)(maxLat*D2R+pi/90.0); 

	long N = 4, IER;	GEOGCMS (&N, &IER );

	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2];
	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
	GEOGCM( &IVAL, (float *)WND, &IRANGE);
}


double CPro_P1812_AreaDoc::BasicTxLossP1812V3_D(double LatST, double LonST, double lati, double loni, double Hgi, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone)
{
	double DELTA_N, N0, az, dist, lonp, latp, ds, LatM, LongM, Lb;
					
	dist = Distance_km(LatST,LonST, lati,loni);	dist = max(dist,0.00001);
	az   = Azimuth_Deg(LatST,LonST, lati,loni);

	if((dist<0.25)||(dist<StepRes))	Lb = 92.5  + 20.0*log10(dist * f_GHz);
	else
	{
		reckon(LatST,LonST, dist/2.0, az, &LatM, &LongM) ;
		N0      = dat_filesDATAout(LatM,LongM, dataN050);
		DELTA_N = dat_filesDATAout(LatM,LongM, dataDN50);

		long Np = 2 + (int)(1 + dist/StepRes);
		double *mD  = new double[Np];
		double *mH  = new double[Np];
		int *mZ = new int[Np+1];

		Np = 0;		ds = 0.0;
		while(ds<dist)
		{
			reckon(LatST,LonST, ds, az, &latp, &lonp);
			mH[Np] = LatLon2Hg(latp , lonp);
			mD[Np] = ds;
			mZ[Np] = LandSeaCoastal(lonp, latp);
			Np++;
			ds = ds + StepRes;
		}
		mH[Np] = Hgi;	mD[Np] = dist;
		mZ[Np] = LandSeaCoastal(loni, lati);
		Np++;
		mZ[Np] = 0;

		Lb = BasicTxLossP1812V3(mD, mH, mZ, Np, LatM, DELTA_N, N0,
								pTime, pLocation, f_GHz, Ht, Hr, pol, 
								srv, InOutDoor, zone);
		delete [] mD;	delete [] mH;	delete [] mZ;
	}
	double Eb_1kwERP = 199.36 + 20.0*log10(f_GHz) - Lb;
	return Eb_1kwERP;
}
			