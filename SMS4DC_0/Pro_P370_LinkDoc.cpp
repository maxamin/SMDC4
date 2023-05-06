// Pro_P370_LinkDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P370_LinkDoc.h"
#include <math.h>
#include "P370_Functions.h"
#include "UTM.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_LinkDoc

IMPLEMENT_DYNCREATE(CPro_P370_LinkDoc, CDocument)

CPro_P370_LinkDoc::CPro_P370_LinkDoc()
{
	m_ReadyDoc=0;
	m_DrawFresnel = false;

	m_ZoomFactor=16;
}

BOOL CPro_P370_LinkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_P370_LinkDoc::~CPro_P370_LinkDoc()
{
	delete [] m_di;
	delete [] m_hi;
	delete [] m_lati;
	delete [] m_loni;

	delete [] bufAreaP370;
	delete [] bufArea;
}


BEGIN_MESSAGE_MAP(CPro_P370_LinkDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_P370_LinkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_LinkDoc diagnostics

#ifdef _DEBUG
void CPro_P370_LinkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_P370_LinkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_LinkDoc serialization

void CPro_P370_LinkDoc::Serialize(CArchive& ar)
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
// CPro_P370_LinkDoc commands


int CPro_P370_LinkDoc::GetData() 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for(int i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
			bufArea[i+Width*j]=bufAreaP370[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];

	double Ghv=1.0,dist;

	CString antfile;
	antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,LinkANT_ST);
	
	int f0[360];	double rH[360]  ,  rV[360];
	int Ierror = ReadAntennaData(antfile,f0,rH,rV) ;

	double elevp,tp,fp,az,f,t;
	double pi=4.0*atan(1.0)  ,   r=6371.0;

	double re = Linkk*6371000.0;
	double AZ0 = LinkAZ_ST*pi/180.0 ,	EL0 = LinkEL_ST*pi/180.0;
	double Hgi, Hg = LinkHasl_ST,  Ht = LinkHagl_ST,  Hr = LinkRxH;

	CPoint m_Point_STcr3,m_Point_STcr15,pointi;
	double lat3km,lon3km,lat15km,lon15km,h1,tetai,tetamax15;

	double tetamax16,ttca=-999.999;
	double Dland,ELand,EfsLand,Eb,Ebfs;

	double StepRes=1.0/m_ZoomFactor;
	CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
	if (TileInfo != globeTileInfo)
		StepRes=8.0*(m_Resolution_x/1000.0)/m_ZoomFactor;

	CP370_Functions CP370;
/*
	int	U = Linkenvironment;
	int p,ENV;
	if		(U==0){ p=1;ENV=1;}
	else if (U==1){	p=1;ENV=2;}
	else if (U==2){	p=1;ENV=3;}
	else if (U==3){	p=2;ENV=1;}
	else if (U==4){	p=3;ENV=1;}
*/

	int	ENV = Linkenvironment + 1;
//	int p = LandWarmColdSea(Linklat_ST,Linklon_ST);
	int p = LandWarmColdSea(Linklon_ST, Linklat_ST);
	double DseaW,DseaC,ESeaW,ESeaC,EfsSeaC,EfsSeaW,DSea;
	//double EfsSea,ESea;
	//int k;

//	dist = Distance_km(Linklat_ST,Linklon_ST,Linklat_Rx,Linklon_Rx);
	dist = Dmax-Dmin;
//	dist = max(dist , 0.00001);
	az=Azimuth_Deg(Linklat_ST,Linklon_ST,Linklat_Rx,Linklon_Rx);

	/////////////////////////////// h1 (Heff) ///////////////////////////////////////////////
	if (dist>=15.0)
	{
		reckon( Linklat_ST,Linklon_ST,  3.0 , az , &lat3km  , &lon3km) ;
		reckon( Linklat_ST,Linklon_ST, 15.0 , az , &lat15km , &lon15km) ;

		LatLon2Point(lat3km  , lon3km , &m_Point_STcr3) ;
		LatLon2Point(lat15km , lon15km, &m_Point_STcr15) ;

		h1=Hg+LinkHagl_ST - Points2HgAvr(m_Point_STcr3 , m_Point_STcr15) ;
	}
	else
	{
		reckon( Linklat_ST,Linklon_ST, 0.2*dist , az , &lat3km  , &lon3km) ;
		reckon( Linklat_ST,Linklon_ST,     dist , az , &lat15km , &lon15km) ;

		LatLon2Point(lat3km  , lon3km , &m_Point_STcr3) ;
		LatLon2Point(lat15km , lon15km, &m_Point_STcr15) ;

		h1=Hg+LinkHagl_ST - Points2HgAvr(m_Point_STcr3 , m_Point_STcr15) ;
	}
//	h1 = zheff370() ;
	///////////////////////////////// tetamax15 /////////////////////////////////////////////
	if (h1<0.0)
	{
		tetai=-pi/2.0;
		for (int iu=0;iu<Np;iu++)
			if (m_di[iu]<=15.0)
				tetai=max(tetai   ,(((m_hi[iu]-Hg-LinkHagl_ST)/(m_di[iu]*1000))-(m_di[iu]/(2.0*Linkk*r))));

		tetamax15=-(180.0/pi)*tetai;
	}
	/////////////////////////////////Rx ttca /////////////////////////////////////////////
	if (LinkClangle==1)
	{
		tetamax16=-pi/2.0;
		for (int iu=0;iu<Np;iu++)
			if (Dmax-m_di[iu]<=16.0)
				tetamax16=max(tetamax16   ,(((m_hi[iu]-10.0-m_hi[Np-1])/((Dmax-m_di[iu])*1000))-((Dmax-m_di[iu])/(2.0*Linkk*r))));

		ttca=-tetamax16*(180.0/pi);
	}
	//////////////////////////////////////////////////////////////////////////////
	if (Linklandsea==1)
	{
/*
		k=0;
		for (int iu=0;iu<Np;iu++)
			if(m_hi[iu]<= m_NoData)	//Sea
				k=k+1;			

		Dland=dist*( (double)(Np-k) )/( (double)Np );

		ELand=CP370.P370_7(LinkfMHz_ST,Linktime,1,h1,dist,tetamax15,LinkRxH,ENV,Linklocation,Linksyst,ttca,&EfsLand);
		ESea=CP370.P370_7(LinkfMHz_ST,Linktime,3,h1,dist,tetamax15,LinkRxH,ENV,Linklocation,Linksyst,ttca,&EfsSea);

		Eb=(Dland*ELand+(dist-Dland)*ESea)/dist;
		Ebfs=(Dland*EfsLand+(dist-Dland)*EfsSea)/dist;
*/
		DSea = D_Sea_kmIDWM(Linklat_ST,Linklon_ST,Linklat_Rx,Linklon_Rx, &DseaW);
		Dland = dist - DSea;
		DseaC = DSea - DseaW;

		ELand = CP370.P370_7(LinkfMHz_ST,Linktime,1,h1,dist,tetamax15,LinkRxH,ENV,Linklocation,Linksyst,ttca,&EfsLand);
		ESeaC = CP370.P370_7(LinkfMHz_ST,Linktime,2,h1,dist,tetamax15,LinkRxH,ENV,Linklocation,Linksyst,ttca,&EfsSeaC);
		ESeaW = CP370.P370_7(LinkfMHz_ST,Linktime,3,h1,dist,tetamax15,LinkRxH,ENV,Linklocation,Linksyst,ttca,&EfsSeaW);

		Eb = (Dland*ELand + DseaC*ESeaC + DseaW*ESeaW)/dist;
		Ebfs = (Dland*EfsLand + DseaC*EfsSeaC + DseaW*EfsSeaW)/dist;
	}
	else
		Eb=CP370.P370_7(LinkfMHz_ST,Linktime,p,h1,dist,tetamax15,LinkRxH,ENV,Linklocation,Linksyst,ttca,&Ebfs);

	Eb=min(Eb,Ebfs);
	//0000000000000000000000000000000000000000000000000000000000000000
	//                     Antenna    Effect
	//0000000000000000000000000000000000000000000000000000000000000000
	Hgi=m_hi[Np-1];
							//with Terrain
	elevp = atan(((re+Hr+Hgi)*cos(1000.0*dist/re)-(re+Ht+Hg))/((re+Hr+Hgi)*sin(1000.0*dist/re)));
	dist = sqrt( pow(re+Ht+Hg,2.0) + pow(re+Hr+Hgi,2.0) - 2.0*(re+Ht+Hg)*(re+Hr+Hgi)*cos(1000.0*dist/re) );
							//without Terrain
	//elevp = atan(((re+Hr)*cos((dist*1000.0)/re)-(re+Ht+Hg))/((re+Hr)*sin((dist*1000.0)/re)));
	//dist = sqrt( pow(re+Ht+Hg,2.0) + pow(re+Hr,2.0) -2.0*(re+Ht+Hg)*(re+Hr)*cos(1000.0*dist/re) );

	dist=dist/1000.0;	fp=az*pi/180.0;		tp = (pi/2.0) - elevp;

	f = (180.0/pi)*atan2(sin(tp)*sin(fp-AZ0),(cos(EL0)*sin(tp)*cos(fp-AZ0)+cos(tp)*sin(EL0)));
	t = (180.0/pi)*acos(cos(tp)*cos(EL0)-sin(EL0)*sin(tp)*cos(fp-AZ0));

	if (f<0.0)
		f=f+359.4;

	Ghv = Interp2(f0,rH,f,360) * Interp2(f0,rV,t,360);
	//0000000000000000000000000000000000000000000000000000000000000000

//	Eb = Eb+10.0*log10(LinkPtGt_ST*Ghv/1650.0);
	Eb = Eb+10.0*log10(Ghv);
	Er = Eb;

	m_TotalLoss = 139.0 - Eb + 20.0*log10(LinkfMHz_ST);
	m_FsLoss = 20.0*log10(4.0*pi*dist*LinkfMHz_ST/0.3);
	
	m_heff = Round(1000.0*h1)/1000.0;
	m_Distance = Round(1000.0*(Dmax-Dmin))/1000.0;
	m_Loss370 = Round(1000.0*(m_TotalLoss - m_FsLoss))/1000.0;
	m_FsLoss = Round(1000.0*m_FsLoss)/1000.0;
	m_TotalLoss = Round(1000.0*m_TotalLoss)/1000.0;

	m_RxCL = ( (LinkClangle==1) ? ttca : -999);
	m_RxCL = Round(1000.0*m_RxCL)/1000.0;

	m_TxCL = ( (h1>=0) ? -999 : tetamax15);
	m_TxCL = Round(1000.0*m_TxCL)/1000.0;

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return Ierror;
}

double CPro_P370_LinkDoc::zheff370() 
{
	double d_m = m_di[Np-1] - m_di[0];
	double d1=3.0,d2=15.0,hav=0.0;

	if (d_m>=15.0)
	{
		d1=3.0;d2=15.0;
	}
	else if (d_m<15.0 && d_m>=3.0)
	{
		d1=3.0;d2=d_m;
	}
	else if (d_m<3.0 )
	{
		d1=0.0;d2=d_m;
	}

	int k=0;
	for(int i=0;i<Np;i++)
	{
		if (m_di[i]>=d1 && m_di[i]<=d2)
		{
			hav = hav+m_hi[i];
			k++;
		}
	}
	hav = hav/( (double)k );
	return (m_hi[0] + LinkHagl_ST - hav);
}


double CPro_P370_LinkDoc::Distance_km(double lat1,double lon1,double lat2,double lon2) 
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(lat1*pi/180.0),
			lon10 = (float)(lon1*pi/180.0),
			lat20 = (float)(lat2*pi/180.0),
			lon20 = (float)(lon2*pi/180.0),	rng;
	GEODSTR( &lon10, &lat10, &lon20, &lat20, &rng);
	return (rng);
/*
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
*/
}

double CPro_P370_LinkDoc::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) 
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(lat1*pi/180.0),
			lon10 = (float)(lon1*pi/180.0),
			lat20 = (float)(lat2*pi/180.0),
			lon20 = (float)(lon2*pi/180.0),	RDIST, RAZIM;
	GEOPPDA( &lon10 ,&lat10, &lon20,&lat20, &RDIST, &RAZIM);
	return RAZIM;

/*
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
*/
}

int CPro_P370_LinkDoc::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);
}



double CPro_P370_LinkDoc::Interp2(int *D0,double *E0,double d,int num) 
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


void CPro_P370_LinkDoc::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) 
{
	double pi=4.0*atan(1.0);
	float	lat_rad = (float)(lat_deg*pi/180.0),
			lon_rad = (float)(lon_deg*pi/180.0),
			RLON, RLAT,	 rng_km1 = (float)rng_km, az_deg1 = (float)az_deg;
	GEOPDAP( &lon_rad, &lat_rad, &rng_km1, &az_deg1, &RLON, &RLAT);
	*latC_deg = RLAT*180.0/pi;
	*lonC_deg = RLON*180.0/pi;
/*
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
*/
}


void CPro_P370_LinkDoc::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
{
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
	double ix = (double)(m_ZoomFactor)*((lon_deg - Linklon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - Linklat0)/(m_Resolution_x));

	(*PointSt).x = (long)ix;
	(*PointSt).y=(long)(Height-1-jy);
}


double CPro_P370_LinkDoc::Points2HgAvr(CPoint point1 , CPoint point2) 
{
	double HgAvr = 0.0;
	if (point1 != point2)
	{
		long x1 = point1.x,		y1 = point1.y;
		long x2 = point2.x,		y2 = point2.y;
		long xabs = abs(x1-x2),	yabs = abs(y1-y2);

		int Np = ((xabs>=yabs) ? xabs+1 : yabs+1);
		int *X;		X = new int[Np];
		int *Y;		Y = new int[Np];
		if (xabs>=yabs)
		{
			for (int i=0; i<Np; i++)
			{
				X[i]=((x1<x2) ? x1+i : x1-i);
				Y[i]=Round((double)y1+(double)((X[i]-x1)*(y2-y1))/((double)(x2-x1)));
			}
		}
		else
		{
			for (int i=0; i<Np; i++)
			{
				Y[i]=((y1<y2) ? y1+i :y1-i);
				X[i]=Round((double)x1+(double)((Y[i]-y1)*(x2-x1))/((double)(y2-y1)));
			}
		}

		CPoint point0;
		double HgSum = 0.0;
		for (int i=0; i<Np; i++)
		{	point0.x = X[i];	point0.y = Y[i];
			HgSum = HgSum + Point2Hg(point0);
		}
		HgAvr = HgSum/((double)Np);
		delete [] X; 
		delete [] Y; 
	}
	else
		HgAvr = Point2Hg(point1);

	return HgAvr;
}



double CPro_P370_LinkDoc::Point2Hg(CPoint point1) 
{
	int i1=point1.x   ,   j1=(Height-1)-point1.y;
	_int16 Hg=bufArea[i1+Width*j1];
	return (double)Hg;
}


int CPro_P370_LinkDoc::ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) 
{
	int Ierror = 0;
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
//		MessageBox(NULL,str, _Z("Warning!!!"), MB_ICONWARNING | MB_OK);
		for (int i=0;i<360;i++)
		{
			f0[i] = i;		rH[i]=1.0;		rV[i]=1.0;
		}
		Ierror = 1;
	}
	return Ierror;
}

int CPro_P370_LinkDoc::WarmColdSea(double RLON_deg,double RLAT_deg) 
{
	int nFlag = 0;  //"Cold Sea"

	if ((((RLON_deg>=2.0 && RLON_deg<=42.0)&&(RLAT_deg>=30.0 && RLAT_deg<=48.0))||
		((RLON_deg>=-5.6 && RLON_deg<=2.0)&&(RLAT_deg>=30.0 && RLAT_deg<=42.0)))||(RLAT_deg<=30.0))
		nFlag = 1;  // "Warm Sea"

	return nFlag;
}

int CPro_P370_LinkDoc::LandWarmColdSea(double RLON_deg,double RLAT_deg) 
{
	int WCSea = WarmColdSea(RLON_deg, RLAT_deg);

	double pi=4.0*atan(1.0);
	float RLON = (float)(RLON_deg*pi/180.0);
	float RLAT = (float)(RLAT_deg*pi/180.0);

	long int N=4, IER;
	GEOGCMS ( &N, &IER );

	float RLON1 = (float)(RLON-pi/90.0), RLAT1 = (float)(RLAT-pi/90.0),
		  RLON2 = (float)(RLON+pi/90.0), RLAT2 = (float)(RLAT+pi/90.0);

	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2],  GC;
	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
	GEOGCM( &IVAL, (float *)WND, &IRANGE);
	GEOGCP( &RLON, &RLAT, &GC);

	int p=1;
	if		((GC==1)&&(WCSea==0)) p=2;	//LandSea = "Coastal Zone : Cold Sea";
	else if ((GC==1)&&(WCSea==1)) p=3;	//LandSea = "Coastal Zone : Warm Sea";
	else if (GC==3)				  p=1;	//LandSea = "Coastal Zone : Coastal Land";
	else if (GC==4)			 	  p=1;	//LandSea = "Coastal Zone : Land";

	return p;
}


double CPro_P370_LinkDoc::D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,
									   double *D_SeaW_km)  
{
	double pi = 4.0*atan(1.0);

	float RLON1 = (float)(lon1_deg*pi/180.f), RLAT1 = (float)(lat1_deg*pi/180.f),
		  RLON2 = (float)(lon2_deg*pi/180.f), RLAT2 = (float)(lat2_deg*pi/180.f); 

	float RDIST, RAZIM;
	GEOPPDA( &RLON1, &RLAT1, &RLON2, &RLAT2, &RDIST, &RAZIM);

	long int N=4, IER;
	GEOGCMS ( &N, &IER );

	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2];
	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
	GEOGCM( &IVAL, (float *)WND, &IRANGE);

	float RIDIST[200], CROSVEK[200][2], CNDVEK[200];
	long  MAXCROS=200, CROSS, IREST;
	GEOGCC3( &RLON1, &RLAT1, &RDIST, &RAZIM, &MAXCROS, (float *)CROSVEK, RIDIST, 
                     (float *)CNDVEK, &CROSS, &IREST);
	int i;
	float PointVEK[200][2];
	PointVEK[0][0] = RLON1;
	PointVEK[0][1] = RLAT1;
	for (i=1;i<=CROSS;i++)
	{
		PointVEK[i][0] = CROSVEK[i-1][0];
		PointVEK[i][1] = CROSVEK[i-1][1];
	}
	PointVEK[i][0] = RLON2;
	PointVEK[i][1] = RLAT2;

	double latCross,lonCross, Dsea = 0, DseaWarm = 0, DseaCold = 0;
	float dst2p, latCross1,lonCross1, loni0,lati0,loni1,lati1;
	int flag1, flag2, LandSea = 1;

	for(i=0;i<CROSS;i++)
	{
		if(CNDVEK[i]==1)  //"Sea";
		{
			loni0 = PointVEK[i][0];
			lati0 = PointVEK[i][1];
			loni1 = PointVEK[i+1][0];
			lati1 = PointVEK[i+1][1];

			GEODSTR( &loni0, &lati0, &loni1, &lati1, &dst2p);
			Dsea = Dsea + dst2p;

			flag1 = WarmColdSea(loni0*180.0/pi, lati0*180.0/pi);
			flag2 = WarmColdSea(loni1*180.0/pi, lati1*180.0/pi);
			if (flag1!=flag2)
			{
				WarmColdCross(loni0*180.0/pi, lati0*180.0/pi, loni1*180.0/pi, lati1*180.0/pi,
																		&lonCross, &latCross);
				lonCross1 = lonCross*pi/180.0;
				latCross1 = latCross*pi/180.0;
				if(flag1)
					GEODSTR( &loni0, &lati0, &lonCross1,&latCross1, &dst2p);
				else
					GEODSTR( &loni1, &lati1, &lonCross1,&latCross1, &dst2p);
				DseaWarm = DseaWarm + dst2p;
			}
			else
			{
				if(flag1)
					DseaWarm = Dsea;
				else
					DseaWarm = 0.0;
			}
		}
		*D_SeaW_km = DseaWarm;
	}
	return Dsea;
}

void CPro_P370_LinkDoc::WarmColdCross(double RLON_deg1,double RLAT_deg1,double RLON_deg2,double RLAT_deg2,
						  double *RLON_degcross,double *RLAT_degcross) 
{
	double lon1,lon2,lat1,lat2,lon1p,lon2p,lat1p,lat2p;
	lon1=min(RLON_deg1,RLON_deg2);
	lon2=max(RLON_deg1,RLON_deg2);
	lat1=min(RLAT_deg1,RLAT_deg2);
	lat2=max(RLAT_deg1,RLAT_deg2);
	lon1p = lon1;
	lon2p = lon2;
	lat1p = lat1;
	lat2p = lat2;
	if ((lat1<30.0)&&(lat2>30.0))
	{
		lon1p = max((lon1-1.0),-180.0);
		lon2p = min((lon2+1.0), 180.0);
		lat1p = 30.0;
		lat2p = 30.0;
	}
	else if ((lon1<-5.6)&&(lon2>-5.6))
	{
		lon1p = -5.6;
		lon2p = -5.6;
		lat1p = max((lat1-1.0),-90.0);
		lat2p = min((lat2+1.0), 90.0);
	}
	double pi = 4.0*atan(1.0);
	float RLON1 = (float)(RLON_deg1*pi/180.0),
		  RLAT1 = (float)(RLAT_deg1*pi/180.0),
		  RLON2 = (float)(RLON_deg2*pi/180.0),
		  RLAT2 = (float)(RLAT_deg2*pi/180.0);

	float RLON10 = (float)(lon1p*pi/180.0),
		  RLAT10 = (float)(lat1p*pi/180.0),
		  RLON20 = (float)(lon2p*pi/180.0),
		  RLAT20 = (float)(lat2p*pi/180.0);

	float CRDLN1[2][2] = {RLON1, RLAT1, RLON2, RLAT2};
	float CRDLN2[2][2] = {RLON10, RLAT10, RLON20, RLAT20};
	float CROSVEK[1][2];

	long NRPNT1 = 2, NRPNT2 = 2, C180=0, IEND=0, MAXCROS=100, CROSS, IREST;
	GEOC2L( (float *)CRDLN1, &NRPNT1, (float *)CRDLN2, &NRPNT2,
						&C180, &IEND, (float *)CROSVEK,  &MAXCROS, &CROSS, &IREST);
	if(CROSS>0)
	{
		*RLON_degcross = CROSVEK[0][0]*180.0/pi;
		*RLAT_degcross = CROSVEK[0][1]*180.0/pi;
	}
}

void CPro_P370_LinkDoc::MissingAntena() 
{
	CString antfile;
	antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,LinkANT_ST);

	CString str;
	str.Format(_Z("The Antenna name  [%s]  was not found!  \r\rThe Isotropic Antenna will be select."),antfile);

	MessageBox(NULL,str, _Z("Warning!!!"), MB_ICONWARNING | MB_OK);
}