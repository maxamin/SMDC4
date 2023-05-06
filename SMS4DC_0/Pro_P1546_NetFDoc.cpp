// Pro_P1546_NetFDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P1546_NetFDoc.h"

#include <math.h>
//#include "P1546_Functions.h"
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
// CPro_P1546_NetFDoc

IMPLEMENT_DYNCREATE(CPro_P1546_NetFDoc, CDocument)

CPro_P1546_NetFDoc::CPro_P1546_NetFDoc()
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
	m_Threshold = 60.0;

	long UNR = 72 ;	WDBUNIT(&UNR) ;
	
	pi = 4.0*atan(1.0);
	D2R = pi/180.0;
	R2D = 180.0/pi;
}

BOOL CPro_P1546_NetFDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_P1546_NetFDoc::~CPro_P1546_NetFDoc()
{
	delete [] bufAreaP1546;
	delete [] bufArea;
	delete [] Er;
	delete [] P1546lat_ST;
	delete [] P1546lon_ST;
	delete [] P1546PtGt_ST;
	delete [] P1546Hagl_ST;
	delete [] P1546fMHz_ST;
	delete [] P1546Name_ST;
	delete [] P1546AZ_ST;
	delete [] P1546EL_ST;
	delete [] P1546ANT_ST;
}


BEGIN_MESSAGE_MAP(CPro_P1546_NetFDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_P1546_NetFDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_NetFDoc diagnostics

#ifdef _DEBUG
void CPro_P1546_NetFDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_P1546_NetFDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_NetFDoc serialization

void CPro_P1546_NetFDoc::Serialize(CArchive& ar)
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
// CPro_P1546_NetFDoc commands

__declspec(dllimport) double FieldP1546V5(double f_MHz,double t,int p23path,double h1,double dT_km,double dsea_km,
										  double tetamax15_deg, double tetamax16_deg ,double h2, int ENV,
										  int pRX, double ha, int pTX,
										  double Hgt, double Hgr, int srv, double L, BOOL P1546Clangle, BOOL P1546landsea);


void CPro_P1546_NetFDoc::GetData0()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for(int i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j]=bufAreaP1546[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin=min(bufMin,bufArea[i+Width*j]);
			bufMax=max(bufMax,bufArea[i+Width*j]);
		}
/*
	int	U = P1546environment;
	double R;
	int p;
	if		(U==0){ R=10;p=1;}
	else if (U==1){	R=10;p=1;}
	else if (U==2){	R=10;p=1;}
	else if (U==3){	R=20;p=1;}
	else if (U==4){	R=30;p=1;}
	else if (U==5){	R=10;p=2;}
	else if (U==6){	R=10;p=3;}
	else		  {	R=10;p=1;}
*/

for(int i10=0;i10<Nrow;i10++)
	P1546lon_ST[i10] = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lon_ST[i10],TileX);
P1546lon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lon0,  TileX);
P1546lonmax = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lonmax,TileX);	//97/12/21

	double rearth=6371.0 , Ghv=1.0;

	CPoint m_Point_STcr3,m_Point_STcr15;
	double lat3km,lon3km,lat15km,lon15km,lat015km,lon015km;

	double az,azI,tetamax15=0.0,ttca=0.0,tetamax16,tetai;
	double dist,ds,dz  ,  h1,hii,hi, Eb;

//	CPoint pointi, m_Point_ST;
//	double ELand,EfsLand,ESea,EfsSea,Dland,Ebfs;
//	double corr_ca=0.0;
//	double delta,deltafs,E_sea_total,Efs_sea_total,Emix,Efsmix;
//	double E_Land_total,Efs_Land_total,deltaE,deltaEfs,alpha,beta,XX;
//	CP1546_Functions CP1546;

	Er=new double[Width*Height];

	double *Hg,Erm;
	Hg=new double[Nrow];
	double lat_j,lon_i;

	CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
//	double StepRes=1.0/m_ZoomFactor;
//	if (TileInfo != globeTileInfo)
//		StepRes=(m_Resolution_x/1000.0)/m_ZoomFactor;

double disttest1 = Distance_km(P1546lat_ST[0], P1546lon_ST[0], P1546lat_ST[0]+0, P1546lon_ST[0]+m_Resolution_x); 
double disttest2 = Distance_km(P1546lat_ST[0], P1546lon_ST[0], P1546lat_ST[0]+m_Resolution_x, P1546lon_ST[0]+0); 
double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	double mds,mdz;

	CString antfile;
	double elevp,tp,fp,f,t;

	double Hr = P1546RxH,  	re = P1546k*rearth*1000.0;

	double AZ0,EL0,Ht, Hgi;
	int f0[360];	double rH1[360]  ,  rV1[360]   ,*rH  ,  *rV;

	rH=new double[Nrow*360];
	rV=new double[Nrow*360];

	for(int i1=0;i1<Nrow;i1++)
	{
		Hg[i1] = LatLon2Hg(P1546lat_ST[i1],P1546lon_ST[i1]);

		antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,P1546ANT_ST[i1]);
		ReadAntennaData(antfile,f0,rH1,rV1) ;
		for( i=0;i<360;i++)
		{
			rH[i+360*i1] = rH1[i];
			rV[i+360*i1] = rV1[i];
		}
	}

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

	double DseaW,DseaC,DSea;
//int k;
//double lati,loni,dx,di,step,EsigmaL,sigma;

/////////////////////Load IDWM map////////////////
	LoadIDWMmap();
//////////////////////////////////////////////////

	double dist1000_re,sintp, costp, sinfp_AZ0, cosfp_AZ0, sinEL0, cosEL0;

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			lat_j = P1546lat0+(j/m_ZoomFactor)*m_Resolution_x;
			lon_i = P1546lon0+(i/m_ZoomFactor)*m_Resolution_x;
			/*		//98/01/21
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
			Erm=-32768.0;

			Hgi = LatLon2Hg(lat_j, lon_i);

			for(int i1=0;i1<Nrow;i1++)
			{
				int p = LandWarmColdSea(P1546lon_ST[i1], P1546lat_ST[i1]); 
				int pRX = p, p23path = p;

				dist = Distance_km(P1546lat_ST[i1],P1546lon_ST[i1],lat_j,lon_i);	
			//	dist = max(dist,0.00001);	//km		//98/01/20
				dist = max(dist, StepRes/2.0);			//98/01/20
				az = Azimuth_Deg(P1546lat_ST[i1],P1546lon_ST[i1],lat_j,lon_i);
				Ht = P1546Hagl_ST[i1];

				/////////////////////////////// h1 (Heff) ///////////////////////////////////////////////
				if (dist>=15.0)
				{
					reckon( P1546lat_ST[i1],P1546lon_ST[i1],  3.0 , az , &lat3km  , &lon3km) ;
					reckon( P1546lat_ST[i1],P1546lon_ST[i1], 15.0 , az , &lat15km , &lon15km) ;
				}
				else
				{
					reckon( P1546lat_ST[i1],P1546lon_ST[i1], 0.2*dist , az , &lat3km  , &lon3km) ;
					reckon( P1546lat_ST[i1],P1546lon_ST[i1],     dist , az , &lat15km , &lon15km) ;
				}
				LatLon2Point(lat3km  , lon3km , &m_Point_STcr3) ;
				LatLon2Point(lat15km , lon15km, &m_Point_STcr15) ;
				h1 = Hg[i1]+Ht - Points2HgAvr(m_Point_STcr3 , m_Point_STcr15) ;
				///////////////////////////////// tetamax15 /////////////////////////////////////////////
//				if (h1<0.0)
				{
					tetai=-pi/2.0;
					mds=m_ZoomFactor*min(dist,15.0);
					ds=0.0;
					while( ds<= mds )  //ds=0->15
					{
						ds=ds+StepRes;
						reckon( P1546lat_ST[i1],P1546lon_ST[i1], ds , az , &lat015km , &lon015km) ;
						hi = LatLon2Hg(lat015km, lon015km);

						tetai=max(tetai   ,(((hi-Hg[i1]-Ht)/(ds*1000))-(ds/(2*P1546k*rearth))));
					}
					tetamax15=R2D*tetai;
				}
				/////////////////////////////////Rx ttca /////////////////////////////////////////////
//				if (P1546Clangle==1)
				{
					azI=Azimuth_Deg(lat_j,lon_i,P1546lat_ST[i1],P1546lon_ST[i1]);
					mdz=m_ZoomFactor*min(dist,16.0);
					tetamax16=-pi/2.0;
					dz=0.0;
					while( dz<= mdz )  //dz=0->16
					{
						dz=dz+StepRes;
						reckon(lat_j,lon_i, dz , azI , &lat015km , &lon015km) ;
						hii = LatLon2Hg(lat015km , lon015km);

//						tetamax16 = max(tetamax16   ,(((hii-10.0-Hgi)/(dz*1000.0))-(dz/(2*P1546k*rearth))));
						tetamax16 = max(tetamax16   ,(((hii-10.0-Hgi)/(dz*1000.0))-(dz/(2.0*rearth))));
					}
					ttca=tetamax16*R2D;
//					corr_ca = TCAcorr1546(ttca,P1546fMHz_ST[i1]);
				}
				//////////////////////////////////////////////////////////////////////////////
				if (P1546landsea==1)
				{
					DSea = LandWarmColdSea_D_Sea_kmIDWM(P1546lat_ST[i1],P1546lon_ST[i1],lat_j,lon_i, &DseaW, &pRX); 
					DseaC = DSea - DseaW;
													p23path = 1;
					if      (DseaW>0)				p23path = 3;
					else if((DseaW<=0)&&(DseaC>0))	p23path = 2;
				}
				Eb = FieldP1546V5(P1546fMHz_ST[i1],P1546time, p23path, h1,dist, DSea,
										  tetamax15, ttca ,Hr, P1546environment,
										  pRX, Ht, p,  Hg[i1], Hgi, 
										  P1546syst, P1546location, P1546Clangle, P1546landsea);
/*	//old version
				if (P1546landsea==1)
				{
			//		step=StepRes;
			//		int n=1+(int)(dist/step);
			//		dx=0.0;k=0;
			//		for (int j2=0;j2<n;j2++)
			//		{
			//			di=dx;
			//			reckon(P1546lat_ST[i1],P1546lon_ST[i1],di,az,&lati,&loni);
			//			hi = LatLon2Hg(lati,loni);
			//			if(hi<= m_NoData)	k=k+1;	//Sea
			//			dx=dx+step;
			//		}
			//		Dland=dist*( (double)(n-k) )/( (double)n );

					DSea = D_Sea_kmIDWM(P1546lat_ST[i1],P1546lon_ST[i1],lat_j,lon_i, &DseaW);
					Dland = dist - DSea;
					DseaC = DSea - DseaW;

					if (Dland==dist)		Eb = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,1,h1,dist,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&Ebfs);
					else if (DseaC==dist)	Eb = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,2,h1,dist,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&Ebfs);
					else if (DseaW==dist)	Eb = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,3,h1,dist,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&Ebfs);
					else
					{
						if (Dland<1.0)
						{
							ELand = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,1,h1,1.0,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&EfsLand);
							ESea = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,3,h1,1.0,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&EfsSea);
							delta = Dland * (ELand - ESea);
							deltafs = Dland * (EfsLand - EfsSea);
						}
						else if (Dland>=1.0)
						{
							ELand = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,1,h1,Dland,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&EfsLand);
							ESea = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,3,h1,Dland,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&EfsSea);
							delta = ELand - ESea;
							deltafs = EfsLand - EfsSea;
						}

						E_sea_total = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,3,h1,dist,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&Efs_sea_total);
						Emix = E_sea_total + delta;
						Efsmix = Efs_sea_total + deltafs;

						E_Land_total = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,1,h1,dist,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&Efs_Land_total);
						deltaE = Emix - E_Land_total;
						deltaEfs = Efsmix - Efs_Land_total;

						alpha = 0.3;      beta=0.0001;
						XX = alpha + (1.0 - alpha) * exp(-(beta *    pow( Dland , (2.42-0.0003527*h1) )    ));
						Eb = E_Land_total + deltaE * XX;
						Ebfs = Efs_Land_total + deltaEfs * XX;

						}

				//		LatLon2Point(lat_j,lon_i, &pointi) ;
				//		hi=Point2Hg(pointi);
				//		if(hi<= m_NoData)	EsigmaL = 0.0;	//Sea  p=3
				//		else				EsigmaL = zsigmaLcrr(1,P1546syst,P1546fMHz_ST[i1],P1546location,&sigma);   //Land   p=1
				}
				else
				{
					Eb = CP1546.P1546_8(P1546fMHz_ST[i1],P1546time,p,h1,dist,P1546RxH,P1546environment,tetamax15,P1546syst,P1546location,&Ebfs);
				//	EsigmaL = zsigmaLcrr(p,P1546syst,P1546fMHz_ST[i1],P1546location,&sigma);
				}

				Eb = Eb + corr_ca;
		//		Eb=Eb+EsigmaL;
				Eb=min(Eb,Ebfs);
*/
				//0000000000000000000000000000000000000000000000000000000000000000
				//                     Antenna    Effect
				//0000000000000000000000000000000000000000000000000000000000000000
				AZ0 = P1546AZ_ST[i1]*D2R ;
				EL0 = P1546EL_ST[i1]*D2R ;
														
				sinEL0 = sin(EL0);				cosEL0 = cos(EL0);
				dist1000_re = 1000.0*dist/re;
										
				elevp = atan(((re+Hr+Hgi)*cos(dist1000_re)-(re+Ht+Hg[i1]))/((re+Hr+Hgi)*sin(dist1000_re)));//with Terrain
			//	elevp = atan(((re+Hr    )*cos(dist1000_re)-(re+Ht+Hg[i1]))/((re+Hr    )*sin(dist1000_re)));//without Terrain

				fp=az*D2R;		tp = (pi/2.0) - elevp;
				sinfp_AZ0 = sin(fp-AZ0);	cosfp_AZ0 = cos(fp-AZ0);	sintp = sin(tp);	costp = cos(tp);

				f = R2D*atan2(sintp*sinfp_AZ0 , cosEL0*sintp*cosfp_AZ0 + costp*sinEL0);
				t = R2D*acos(costp*cosEL0 - sinEL0*sintp*cosfp_AZ0);
				if (f<0.0)			f=f+359.4;

//				Ghv = Interp2(f0,rH,f,360) * Interp2(f0,rV,t,360);
				Ghv = Interp2(f0,&rH[360*i1],f,360) * Interp2(f0,&rV[360*i1],t,360);

				//Ghv = rH[Round(f)+360*i1] * rV[Round(t)+360*i1];
				//0000000000000000000000000000000000000000000000000000000000000000
				Eb = Eb + 10.0*log10(P1546PtGt_ST[i1]*Ghv/1650.0);
				Erm = max(Erm , Eb );
			}
			Er[i+Width*j]=Erm;
			ErMax=max(ErMax , Er[i+Width*j] );
			ErMin=min(ErMin , Er[i+Width*j] );
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

	m_MinValue = (double)Round(ErMin)+1.0;	//98/01/19
	m_MaxValue = (double)Round(ErMax)-1.0;
//	m_MinValue = ErMin;
//	m_MaxValue = ErMax;

	delete [] Hg;	delete [] rH;	delete [] rV;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}
//98/01/19
int CPro_P1546_NetFDoc::Round(double x) 
{
	int y;
	int x1 = (int)x;
	if(x>=0)	{int x2 = x1+1;		y = ( (x > ((double)x1)+0.45) ? x2 : x1);}
	else		{int x2 = x1-1;		y = ( (x > ((double)x2)+0.45) ? x1 : x2);}
	return y;
}
/*
int CPro_P1546_NetFDoc::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);
}
*/
void CPro_P1546_NetFDoc::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
{
lon_deg = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon_deg,TileX);
/*		98/01/21
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
	double ix = (double)(m_ZoomFactor)*((lon_deg - P1546lon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - P1546lat0)/(m_Resolution_x));

	(*PointSt).x = (long)ix;
	(*PointSt).y=(long)(Height-1-jy);

}
double CPro_P1546_NetFDoc::Point2Hg(CPoint point1) 
{
	int i1=point1.x   ,   j1=(Height-1)-point1.y;
	_int16 Hg=bufArea[i1+Width*j1];
	return (double)Hg;
}
double CPro_P1546_NetFDoc::LatLon2Hg0(double lat_deg,double lon_deg) 
{
	CPoint pointi;
	LatLon2Point(lat_deg, lon_deg, &pointi) ;	
	double hi = Point2Hg(pointi);
	return hi;
}
double CPro_P1546_NetFDoc::LatLon2Hg(double lat_deg,double lon_deg)
{
	lon_deg = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(lon_deg,TileX);
/*		//98/01/19
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
	double ix = (double)(m_ZoomFactor)*((lon_deg - P1546lon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - P1546lat0)/(m_Resolution_x));

	double Hg = RoundBUF_Hg(ix, jy);
	return Hg;
}
double CPro_P1546_NetFDoc::RoundBUF_Hg(double xps,double yps) 
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
double CPro_P1546_NetFDoc::Distance_km(double lat1,double lon1,double lat2,double lon2) 
{
	float	lat10 = (float)(lat1*D2R),
			lon10 = (float)(lon1*D2R),
			lat20 = (float)(lat2*D2R),
			lon20 = (float)(lon2*D2R),	rng;
	GEODSTR( &lon10, &lat10, &lon20, &lat20, &rng);
	return (rng);

/*
	double temp1,temp2,temp3,rng;
	double pi=4.0*atan(1.0);
	double R = 6371.0;

	lat1=lat1*D2R;
	lat2=lat2*D2R;
	lon1=lon1*D2R;
	lon2=lon2*D2R;

	temp1 = sin(lat1)*sin(lat2);
	temp2 = cos(lat1)*cos(lat2)*cos(lon2-lon1);
	temp3 = temp1+temp2;
	temp3=min(1.0,max(-1.0,temp3));

	rng = acos(temp3);
	rng=R*rng;    //km
	return (rng);
*/
}
double CPro_P1546_NetFDoc::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) 
{
	float	lat10 = (float)(lat1*D2R),
			lon10 = (float)(lon1*D2R),
			lat20 = (float)(lat2*D2R),
			lon20 = (float)(lon2*D2R),	RDIST, RAZIM;
	GEOPPDA( &lon10 ,&lat10, &lon20,&lat20, &RDIST, &RAZIM);
	return RAZIM;

/*
	double pi=4.0*atan(1.0);
	double epsilon =  0.000000017453;

	lat1=lat1*D2R;
	lon1=lon1*D2R;
	lat2=lat2*D2R;
	lon2=lon2*D2R;
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
	az = az*R2D;
	return az;
*/
}

void CPro_P1546_NetFDoc::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) 
{
	float	lat_rad = (float)(lat_deg*D2R),
			lon_rad = (float)(lon_deg*D2R),
			RLON, RLAT,	 rng_km1 = (float)rng_km, az_deg1 = (float)az_deg;
	GEOPDAP( &lon_rad, &lat_rad, &rng_km1, &az_deg1, &RLON, &RLAT);
	*latC_deg = RLAT*R2D;
	*lonC_deg = RLON*R2D;
/*
	double pi=4.0*atan(1.0);
	double R=6371.0;

	double rng_rad=rng_km/R;
	double az_rad=az_deg*D2R;
	double lat_rad=lat_deg*D2R;
	double lon_rad=lon_deg*D2R;

	double temp1  = sin(lat_rad)*cos(rng_rad);          
	double temp2  = cos(lat_rad)*sin(rng_rad)*cos(az_rad);
	double newlat = asin(temp1+temp2);

	temp1  = sin(rng_rad)*sin(az_rad);            
	temp2  = cos(lat_rad)*cos(rng_rad);
	double temp3  = sin(lat_rad)*sin(rng_rad)*cos(az_rad);
	double newlon = lon_rad + atan2(temp1,temp2-temp3);

	*latC_deg=newlat*R2D;
	*lonC_deg=newlon*R2D;
*/
}

double CPro_P1546_NetFDoc::Points2HgAvr(CPoint point1 , CPoint point2) 
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

double CPro_P1546_NetFDoc::TCAcorr1546(double Tdeg,double f_MHz)
{
	Tdeg=min(max(Tdeg , -0.8) ,40.0);

	double v = 0.065 * Tdeg * sqrt(f_MHz);
	double v01 = v - 0.1;
	double Jv = 6.9 + 20.0 * log10( sqrt(1+v01*v01) + v01 );
	double vp = 0.036 * sqrt(f_MHz);
	double vp01 = vp - 0.1;
	double Jvp = 6.9 + 20.0 *log10( sqrt(1+vp01*vp01) + vp01 );
	double Corr = Jvp - Jv;

	return Corr;
}


void CPro_P1546_NetFDoc::ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) 
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
		MessageBox(NULL,str, _Z("Warning!!!"), MB_ICONWARNING | MB_OK);
		for (int i=0;i<360;i++)
		{
			f0[i] = i;		rH[i]=1.0;		rV[i]=1.0;
		}
	}
}


BOOL CPro_P1546_NetFDoc::PeekAndPump()
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

double CPro_P1546_NetFDoc::Interp2(int *D0,double *E0,double d,int num) 
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


int CPro_P1546_NetFDoc::WarmColdSea(double RLON_deg,double RLAT_deg) 
{
	int nFlag = 0;  //"Cold Sea"

	if ((((RLON_deg>=2.0 && RLON_deg<=42.0)&&(RLAT_deg>=30.0 && RLAT_deg<=48.0))||
		((RLON_deg>=-5.6 && RLON_deg<=2.0)&&(RLAT_deg>=30.0 && RLAT_deg<=42.0)))||(RLAT_deg<=30.0))
		nFlag = 1;  // "Warm Sea"

	return nFlag;
}

int CPro_P1546_NetFDoc::LandWarmColdSea(double RLON_deg,double RLAT_deg) 
{
	int WCSea = WarmColdSea(RLON_deg, RLAT_deg);

	float RLON = (float)(RLON_deg*D2R), RLAT = (float)(RLAT_deg*D2R), GC;

//	long int N=4, IER;	GEOGCMS ( &N, &IER );

//	float RLON1 = (float)(RLON-pi/90.0), RLAT1 = (float)(RLAT-pi/90.0),
//		  RLON2 = (float)(RLON+pi/90.0), RLAT2 = (float)(RLAT+pi/90.0);

//	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
//	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2],  GC;
//	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
//	GEOGCM( &IVAL, (float *)WND, &IRANGE);
	GEOGCP( &RLON, &RLAT, &GC);

	int p=1;
	if		((GC==1)&&(WCSea==0)) p=2;	//LandSea = "Coastal Zone : Cold Sea";
	else if ((GC==1)&&(WCSea==1)) p=3;	//LandSea = "Coastal Zone : Warm Sea";
//	else if (GC==3)				  p=1;	//LandSea = "Coastal Zone : Coastal Land";
//	else if (GC==4)			 	  p=1;	//LandSea = "Coastal Zone : Land";

	return p;
}



double CPro_P1546_NetFDoc::D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,
									   double *D_SeaW_km)  
{
	float RLON1 = (float)(lon1_deg*pi/180.f), RLAT1 = (float)(lat1_deg*pi/180.f),
		  RLON2 = (float)(lon2_deg*pi/180.f), RLAT2 = (float)(lat2_deg*pi/180.f); 

	float RDIST, RAZIM;
	GEOPPDA( &RLON1, &RLAT1, &RLON2, &RLAT2, &RDIST, &RAZIM);

//	long int N=4, IER;	GEOGCMS ( &N, &IER );

//	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
//	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2];
//	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
//	GEOGCM( &IVAL, (float *)WND, &IRANGE);

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

//		if(CNDVEK[i]==1) //"S";  //"Sea";
//		if(CNDVEK[i]==3) //"CL"; //"Coastal Land";
//		if(CNDVEK[i]==4) //"L";   //"Inland Land";

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

			flag1 = WarmColdSea(loni0*R2D, lati0*R2D);
			flag2 = WarmColdSea(loni1*R2D, lati1*R2D);
			if (flag1!=flag2)
			{
				WarmColdCross(loni0*R2D, lati0*R2D, loni1*R2D, lati1*R2D,
																		&lonCross, &latCross);
				lonCross1 = lonCross*D2R;
				latCross1 = latCross*D2R;
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



void CPro_P1546_NetFDoc::WarmColdCross(double RLON_deg1,double RLAT_deg1,double RLON_deg2,double RLAT_deg2,
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
	float RLON1 = (float)(RLON_deg1*D2R),
		  RLAT1 = (float)(RLAT_deg1*D2R),
		  RLON2 = (float)(RLON_deg2*D2R),
		  RLAT2 = (float)(RLAT_deg2*D2R);

	float RLON10 = (float)(lon1p*D2R),
		  RLAT10 = (float)(lat1p*D2R),
		  RLON20 = (float)(lon2p*D2R),
		  RLAT20 = (float)(lat2p*D2R);

	float CRDLN1[2][2] = {RLON1, RLAT1, RLON2, RLAT2};
	float CRDLN2[2][2] = {RLON10, RLAT10, RLON20, RLAT20};
	float CROSVEK[1][2];

	long NRPNT1 = 2, NRPNT2 = 2, C180=0, IEND=0, MAXCROS=100, CROSS, IREST;
	GEOC2L( (float *)CRDLN1, &NRPNT1, (float *)CRDLN2, &NRPNT2,
						&C180, &IEND, (float *)CROSVEK,  &MAXCROS, &CROSS, &IREST);
	if(CROSS>0)
	{
		*RLON_degcross = CROSVEK[0][0]*R2D;
		*RLAT_degcross = CROSVEK[0][1]*R2D;
	}
}

double CPro_P1546_NetFDoc::LandWarmColdSea_D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,
									   double *D_SeaW_km, int *p2) 
{
	float RLON1 = (float)(lon1_deg*D2R), RLAT1 = (float)(lat1_deg*D2R),
		  RLON2 = (float)(lon2_deg*D2R), RLAT2 = (float)(lat2_deg*D2R); 

	float RDIST, RAZIM, GC;
	GEOPPDA( &RLON1, &RLAT1, &RLON2, &RLAT2, &RDIST, &RAZIM);

//	long int N=4, IER;	GEOGCMS ( &N, &IER );

//	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
//	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2], GC;
//	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
//	GEOGCM( &IVAL, (float *)WND, &IRANGE);

////////////////////
	int WCSea = WarmColdSea(lon2_deg, lat2_deg);
	GEOGCP( &RLON2, &RLAT2, &GC);
	*p2 = 1;
	if		((GC==1)&&(WCSea==0)) *p2=2;	//LandSea = "Coastal Zone : Cold Sea";
	else if ((GC==1)&&(WCSea==1)) *p2=3;	//LandSea = "Coastal Zone : Warm Sea";
//	else if (GC==3)				  *p2=1;	//LandSea = "Coastal Zone : Coastal Land";
//	else if (GC==4)			 	  *p2=1;	//LandSea = "Coastal Zone : Land";
/////////////////////

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

//	if(CNDVEK[i]==1) //"S";  //"Sea";
//	if(CNDVEK[i]==3) //"CL"; //"Coastal Land";
//	if(CNDVEK[i]==4) //"L";  //"Inland Land";

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

			flag1 = WarmColdSea(loni0*R2D, lati0*R2D);
			flag2 = WarmColdSea(loni1*R2D, lati1*R2D);
			if (flag1!=flag2)
			{
				WarmColdCross(loni0*R2D, lati0*R2D, loni1*R2D, lati1*R2D, &lonCross, &latCross);
				lonCross1 = lonCross*D2R;
				latCross1 = latCross*D2R;
				if(flag1)		GEODSTR( &loni0, &lati0, &lonCross1,&latCross1, &dst2p);
				else			GEODSTR( &loni1, &lati1, &lonCross1,&latCross1, &dst2p);
				DseaWarm = DseaWarm + dst2p;
			}
			else
			{
				if(flag1)	DseaWarm = Dsea;
				else		DseaWarm = 0.0;
			}
		}
		*D_SeaW_km = DseaWarm;
	}
	return Dsea;
}

void CPro_P1546_NetFDoc::LoadIDWMmap() 
{
	double minLat = P1546lat0,	 maxLat = P1546lat0+((Height-1)/m_ZoomFactor)*m_Resolution_x;
	double minLon = P1546lon0,	 maxLon = P1546lon0+((Width- 1)/m_ZoomFactor)*m_Resolution_x;
	float RLON1 = (float)(minLon*D2R-pi/90.0), RLAT1 = (float)(minLat*D2R-pi/90.0),	  RLON2 = (float)(maxLon*D2R+pi/90.0), RLAT2 = (float)(maxLat*D2R+pi/90.0); 

	long N = 4, IER;	GEOGCMS (&N, &IER );

	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2];
	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
	GEOGCM( &IVAL, (float *)WND, &IRANGE);
}


//Monitoring Rx Coverage(MFS)
/////////////////////////////
void CPro_P1546_NetFDoc::GetData1()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	Width   = m_ZoomFactor * bufAreaW;
	Height  = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for(int i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j] = bufAreaP1546[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin = min(bufMin,bufArea[i+Width*j]);
			bufMax = max(bufMax,bufArea[i+Width*j]);
		}

	for(int i10=0;i10<Nrow;i10++)
		P1546lon_ST[i10] = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lon_ST[i10],TileX);
	P1546lon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lon0,  TileX);
	P1546lonmax = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lonmax,TileX);	//97/12/21

	double rearth=6371.0 , Ghv=1.0;

	CPoint m_Point_STcr3,m_Point_STcr15;
	double lat3km,lon3km,lat15km,lon15km,lat015km,lon015km;

	double az,azI,tetamax15 = 0.0, ttca = 0.0,tetamax16,tetai;
	double dist,ds,dz  ,  h1,hii,hi, Eb;

	Er = new double[Width*Height];

	double *Hg, Erm;
	Hg = new double[Nrow];
	double lat_j, lon_i;

	double disttest1 = Distance_km(P1546lat_ST[0], P1546lon_ST[0], P1546lat_ST[0]+0, P1546lon_ST[0]+m_Resolution_x); 
	double disttest2 = Distance_km(P1546lat_ST[0], P1546lon_ST[0], P1546lat_ST[0]+m_Resolution_x, P1546lon_ST[0]+0); 
	double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	double mds,mdz;

	CString antfile;
	double elevp,tp,fp,f,t;

	double Hr = P1546RxH,  	re = P1546k*rearth*1000.0;

	double AZ0,EL0,Ht, Hgi;
	int f0[360];	double rH1[360]  ,  rV1[360]   ,*rH  ,  *rV;

	rH = new double[Nrow*360];
	rV = new double[Nrow*360];

	for(int i1=0;i1<Nrow;i1++)
	{
		Hg[i1] = LatLon2Hg(P1546lat_ST[i1],P1546lon_ST[i1]);

		antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,P1546ANT_ST[i1]);
		ReadAntennaData(antfile,f0,rH1,rV1) ;
		for( i=0;i<360;i++)
		{
			rH[i+360*i1] = rH1[i];
			rV[i+360*i1] = rV1[i];
		}
	}

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

	double DseaW,DseaC,DSea;

/////////////////////Load IDWM map////////////////
	LoadIDWMmap();
//////////////////////////////////////////////////

	double dist1000_re,sintp, costp, sinfp_AZ0, cosfp_AZ0, sinEL0, cosEL0;

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			lat_j = P1546lat0+(j/m_ZoomFactor)*m_Resolution_x;
			lon_i = P1546lon0+(i/m_ZoomFactor)*m_Resolution_x;

			Erm = -32768.0;

			Hgi = LatLon2Hg(lat_j, lon_i);

			for(int i1=0;i1<Nrow;i1++)
			{
				int p = LandWarmColdSea(P1546lon_ST[i1], P1546lat_ST[i1]); 
				int pRX = p, p23path = p;

				dist = Distance_km(P1546lat_ST[i1],P1546lon_ST[i1],lat_j,lon_i);	
				dist = max(dist, StepRes/2.0);			//98/01/20
				az = Azimuth_Deg(lat_j, lon_i, P1546lat_ST[i1], P1546lon_ST[i1]);
			//	az = Azimuth_Deg(P1546lat_ST[i1], P1546lon_ST[i1], lat_j, lon_i);
				Ht = P1546Hagl_ST[i1];

				/////////////////////////////// h1 (Heff) ///////////////////////////////////////////////
				if (dist>=15.0)
				{
					reckon( lat_j,lon_i,  3.0 , az , &lat3km  , &lon3km) ;
					reckon( lat_j,lon_i, 15.0 , az , &lat15km , &lon15km) ;
			//		reckon( P1546lat_ST[i1],P1546lon_ST[i1],  3.0 , az , &lat3km  , &lon3km) ;
			//		reckon( P1546lat_ST[i1],P1546lon_ST[i1], 15.0 , az , &lat15km , &lon15km) ;
				}
				else
				{
					reckon( lat_j,lon_i, 0.2*dist , az , &lat3km  , &lon3km) ;
					reckon( lat_j,lon_i,     dist , az , &lat15km , &lon15km) ;
			//		reckon( P1546lat_ST[i1],P1546lon_ST[i1], 0.2*dist , az , &lat3km  , &lon3km) ;
			//		reckon( P1546lat_ST[i1],P1546lon_ST[i1],     dist , az , &lat15km , &lon15km) ;
				}
				LatLon2Point(lat3km  , lon3km , &m_Point_STcr3) ;
				LatLon2Point(lat15km , lon15km, &m_Point_STcr15) ;
				h1 = Hgi   + Hr - Points2HgAvr(m_Point_STcr3 , m_Point_STcr15) ;
			//	h1 = Hg[i1]+ Ht - Points2HgAvr(m_Point_STcr3 , m_Point_STcr15) ;
				///////////////////////////////// tetamax15 /////////////////////////////////////////////
//				if (h1<0.0)
				{
					tetai = -pi/2.0;
					mds   = m_ZoomFactor*min(dist,15.0);
					ds    = 0.0;
					while( ds<= mds )  //ds=0->15
					{
						ds = ds+StepRes;
						reckon( lat_j,lon_i,                     ds , az , &lat015km , &lon015km) ;
				//		reckon( P1546lat_ST[i1],P1546lon_ST[i1], ds , az , &lat015km , &lon015km) ;
						hi = LatLon2Hg(lat015km, lon015km);

						tetai = max(tetai   ,(((hi-Hgi-   Hr)/(ds*1000))-(ds/(2*P1546k*rearth))));
				//		tetai = max(tetai   ,(((hi-Hg[i1]-Ht)/(ds*1000))-(ds/(2*P1546k*rearth))));
					}
					tetamax15 = R2D*tetai;
				}
				/////////////////////////////////Rx ttca /////////////////////////////////////////////
//				if (P1546Clangle==1)
				{
					azI = Azimuth_Deg(P1546lat_ST[i1],P1546lon_ST[i1], lat_j,lon_i);
			//		azI = Azimuth_Deg(lat_j,lon_i,P1546lat_ST[i1],P1546lon_ST[i1]);
					mdz=m_ZoomFactor*min(dist,16.0);
					tetamax16=-pi/2.0;
					dz=0.0;
					while( dz<= mdz )  //dz=0->16
					{
						dz=dz+StepRes;
						reckon(P1546lat_ST[i1],P1546lon_ST[i1], dz , azI , &lat015km , &lon015km) ;
				//		reckon(lat_j,lon_i, dz , azI , &lat015km , &lon015km) ;
						hii = LatLon2Hg(lat015km , lon015km);

						tetamax16 = max(tetamax16   ,(((hii-10.0-Hg[i1])/(dz*1000.0))-(dz/(2.0*rearth))));
				//		tetamax16 = max(tetamax16   ,(((hii-10.0-Hgi)/(dz*1000.0))-(dz/(2.0*rearth))));
					}
					ttca = tetamax16*R2D;
				}
				//////////////////////////////////////////////////////////////////////////////
				if (P1546landsea==1)
				{
					DSea = LandWarmColdSea_D_Sea_kmIDWM(lat_j,lon_i,P1546lat_ST[i1],P1546lon_ST[i1], &DseaW, &pRX); 
		//			DSea = LandWarmColdSea_D_Sea_kmIDWM(P1546lat_ST[i1],P1546lon_ST[i1],lat_j,lon_i, &DseaW, &pRX); 
					DseaC = DSea - DseaW;
													p23path = 1;
					if      (DseaW>0)				p23path = 3;
					else if((DseaW<=0)&&(DseaC>0))	p23path = 2;
				}
				Eb = FieldP1546V5(P1546fMHz_ST[i1],P1546time, p23path, h1,dist, DSea,
										  tetamax15, ttca ,Ht, P1546environment,
										  pRX, Hr, p,  Hgi, Hg[i1],  
										  P1546syst, P1546location, P1546Clangle, P1546landsea);
		//		Eb = FieldP1546V5(P1546fMHz_ST[i1],P1546time, p23path, h1,dist, DSea,
		//								  tetamax15, ttca ,Hr, P1546environment,
		//								  pRX, Ht, p,  Hg[i1], Hgi, 
		//								  P1546syst, P1546location, P1546Clangle, P1546landsea);

				//0000000000000000000000000000000000000000000000000000000000000000
				//                     Antenna    Effect
				//0000000000000000000000000000000000000000000000000000000000000000
				AZ0 = P1546AZ_ST[i1]*D2R ;
				EL0 = P1546EL_ST[i1]*D2R ;
														
				sinEL0 = sin(EL0);				cosEL0 = cos(EL0);
				dist1000_re = 1000.0*dist/re;
										
				elevp = atan(((re+Ht+Hg[i1])*cos(dist1000_re)-(re+Hr+Hgi))/((re+Ht+Hg[i1])*sin(dist1000_re)));//with Terrain
		//		elevp = atan(((re+Hr+Hgi)*cos(dist1000_re)-(re+Ht+Hg[i1]))/((re+Hr+Hgi)*sin(dist1000_re)));//with Terrain

				fp=az*D2R;		tp = (pi/2.0) - elevp;
				sinfp_AZ0 = sin(fp-AZ0);	cosfp_AZ0 = cos(fp-AZ0);	sintp = sin(tp);	costp = cos(tp);

				f = R2D*atan2(sintp*sinfp_AZ0 , cosEL0*sintp*cosfp_AZ0 + costp*sinEL0);
				t = R2D*acos(costp*cosEL0 - sinEL0*sintp*cosfp_AZ0);
				if (f<0.0)			f=f+359.4;

				Ghv = Interp2(f0,&rH[360*i1],f,360) * Interp2(f0,&rV[360*i1],t,360);

				//0000000000000000000000000000000000000000000000000000000000000000
//				Eb = Eb + 10.0*log10(P1546PtGt_ST[i1]*Ghv/1650.0);
				Eb = Eb + 10.0*log10(P1546PtGt_ST[0]*Ghv/1650.0);
				Erm = max(Erm , Eb );
			}
			Er[i+Width*j] = Erm;
			ErMax = max(ErMax , Er[i+Width*j] );
			ErMin = min(ErMin , Er[i+Width*j] );
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

	m_MinValue = (double)Round(ErMin)+1.0;	//98/01/19
	m_MaxValue = (double)Round(ErMax)-1.0;

	delete [] Hg;	delete [] rH;	delete [] rV;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

#include "MonitoringThDLG.h"

// Monitoring  AoA
///////////////////////
void CPro_P1546_NetFDoc::GetData2()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	Width   = m_ZoomFactor * bufAreaW;
	Height  = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for(int i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j] = bufAreaP1546[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin = min(bufMin,bufArea[i+Width*j]);
			bufMax = max(bufMax,bufArea[i+Width*j]);
		}

	for(int i10=0;i10<Nrow;i10++)
		P1546lon_ST[i10] = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lon_ST[i10],TileX);
	P1546lon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lon0,  TileX);
	P1546lonmax = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(P1546lonmax,TileX);	//97/12/21

	double rearth=6371.0 , Ghv=1.0;

	CPoint m_Point_STcr3,m_Point_STcr15;
	double lat3km,lon3km,lat15km,lon15km,lat015km,lon015km;

	double az,azI,tetamax15 = 0.0, ttca = 0.0,tetamax16,tetai;
	double dist,ds,dz  ,  h1,hii,hi, Eb;

	Er = new double[Width*Height];

	double *Hg = new double[Nrow];


double Eth = 20;
m_teta_deg = 1;

//	if (EthFlag)
//	{
		CMonitoringThDLG zz;

		zz.m_flag = 2;

		zz.m_title  = _Z("Threshold Value");
		zz.m_label1 = _Z("Threshold Value (dBuV/m) :");
		zz.m_label2 = _Z("R.M.S Value (Deg.) :");

		zz.m_EDIT_mth1 = Eth;
		zz.m_EDIT_mth2 = m_teta_deg;

		if(zz.DoModal()!=IDOK)		return;

		Eth = zz.m_EDIT_mth1;
		m_teta_deg = zz.m_EDIT_mth2;

//	}	
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	double *Erm = new double[Nrow];

	double lat_j, lon_i;

	double disttest1 = Distance_km(P1546lat_ST[0], P1546lon_ST[0], P1546lat_ST[0]+0, P1546lon_ST[0]+m_Resolution_x); 
	double disttest2 = Distance_km(P1546lat_ST[0], P1546lon_ST[0], P1546lat_ST[0]+m_Resolution_x, P1546lon_ST[0]+0); 
	double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	double mds,mdz;

	CString antfile;
	double elevp,tp,fp,f,t;

	double Hr = P1546RxH,  	re = P1546k*rearth*1000.0;

	double AZ0,EL0,Ht, Hgi;
	int f0[360];	double rH1[360]  ,  rV1[360]   ,*rH  ,  *rV;

	rH = new double[Nrow*360];
	rV = new double[Nrow*360];

	for(int i1=0;i1<Nrow;i1++)
	{
		Hg[i1] = LatLon2Hg(P1546lat_ST[i1],P1546lon_ST[i1]);

		antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,P1546ANT_ST[i1]);
		ReadAntennaData(antfile,f0,rH1,rV1) ;
		for( i=0;i<360;i++)
		{
			rH[i+360*i1] = rH1[i];
			rV[i+360*i1] = rV1[i];
		}
	}

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

	double DseaW,DseaC,DSea;

/////////////////////Load IDWM map////////////////
	LoadIDWMmap();
//////////////////////////////////////////////////

	double dist1000_re,sintp, costp, sinfp_AZ0, cosfp_AZ0, sinEL0, cosEL0;

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			lat_j = P1546lat0+(j/m_ZoomFactor)*m_Resolution_x;
			lon_i = P1546lon0+(i/m_ZoomFactor)*m_Resolution_x;

//			Erm = -32768.0;

			Hgi = LatLon2Hg(lat_j, lon_i);

			for(int i1=0;i1<Nrow;i1++)
			{
				int p = LandWarmColdSea(P1546lon_ST[i1], P1546lat_ST[i1]); 
				int pRX = p, p23path = p;

				dist = Distance_km(P1546lat_ST[i1],P1546lon_ST[i1],lat_j,lon_i);	
				dist = max(dist, StepRes/2.0);			//98/01/20
				az = Azimuth_Deg(lat_j, lon_i, P1546lat_ST[i1], P1546lon_ST[i1]);
			//	az = Azimuth_Deg(P1546lat_ST[i1], P1546lon_ST[i1], lat_j, lon_i);
				Ht = P1546Hagl_ST[i1];

				/////////////////////////////// h1 (Heff) ///////////////////////////////////////////////
				if (dist>=15.0)
				{
					reckon( lat_j,lon_i,  3.0 , az , &lat3km  , &lon3km) ;
					reckon( lat_j,lon_i, 15.0 , az , &lat15km , &lon15km) ;
			//		reckon( P1546lat_ST[i1],P1546lon_ST[i1],  3.0 , az , &lat3km  , &lon3km) ;
			//		reckon( P1546lat_ST[i1],P1546lon_ST[i1], 15.0 , az , &lat15km , &lon15km) ;
				}
				else
				{
					reckon( lat_j,lon_i, 0.2*dist , az , &lat3km  , &lon3km) ;
					reckon( lat_j,lon_i,     dist , az , &lat15km , &lon15km) ;
			//		reckon( P1546lat_ST[i1],P1546lon_ST[i1], 0.2*dist , az , &lat3km  , &lon3km) ;
			//		reckon( P1546lat_ST[i1],P1546lon_ST[i1],     dist , az , &lat15km , &lon15km) ;
				}
				LatLon2Point(lat3km  , lon3km , &m_Point_STcr3) ;
				LatLon2Point(lat15km , lon15km, &m_Point_STcr15) ;
				h1 = Hgi   + Hr - Points2HgAvr(m_Point_STcr3 , m_Point_STcr15) ;
			//	h1 = Hg[i1]+ Ht - Points2HgAvr(m_Point_STcr3 , m_Point_STcr15) ;
				///////////////////////////////// tetamax15 /////////////////////////////////////////////
//				if (h1<0.0)
				{
					tetai = -pi/2.0;
					mds   = m_ZoomFactor*min(dist,15.0);
					ds    = 0.0;
					while( ds<= mds )  //ds=0->15
					{
						ds = ds+StepRes;
						reckon( lat_j,lon_i,                     ds , az , &lat015km , &lon015km) ;
				//		reckon( P1546lat_ST[i1],P1546lon_ST[i1], ds , az , &lat015km , &lon015km) ;
						hi = LatLon2Hg(lat015km, lon015km);

						tetai = max(tetai   ,(((hi-Hgi-   Hr)/(ds*1000))-(ds/(2*P1546k*rearth))));
				//		tetai = max(tetai   ,(((hi-Hg[i1]-Ht)/(ds*1000))-(ds/(2*P1546k*rearth))));
					}
					tetamax15 = R2D*tetai;
				}
				/////////////////////////////////Rx ttca /////////////////////////////////////////////
//				if (P1546Clangle==1)
				{
					azI = Azimuth_Deg(P1546lat_ST[i1],P1546lon_ST[i1], lat_j,lon_i);
			//		azI = Azimuth_Deg(lat_j,lon_i,P1546lat_ST[i1],P1546lon_ST[i1]);
					mdz=m_ZoomFactor*min(dist,16.0);
					tetamax16=-pi/2.0;
					dz=0.0;
					while( dz<= mdz )  //dz=0->16
					{
						dz=dz+StepRes;
						reckon(P1546lat_ST[i1],P1546lon_ST[i1], dz , azI , &lat015km , &lon015km) ;
				//		reckon(lat_j,lon_i, dz , azI , &lat015km , &lon015km) ;
						hii = LatLon2Hg(lat015km , lon015km);

						tetamax16 = max(tetamax16   ,(((hii-10.0-Hg[i1])/(dz*1000.0))-(dz/(2.0*rearth))));
				//		tetamax16 = max(tetamax16   ,(((hii-10.0-Hgi)/(dz*1000.0))-(dz/(2.0*rearth))));
					}
					ttca = tetamax16*R2D;
				}
				//////////////////////////////////////////////////////////////////////////////
				if (P1546landsea==1)
				{
					DSea = LandWarmColdSea_D_Sea_kmIDWM(lat_j,lon_i,P1546lat_ST[i1],P1546lon_ST[i1], &DseaW, &pRX); 
		//			DSea = LandWarmColdSea_D_Sea_kmIDWM(P1546lat_ST[i1],P1546lon_ST[i1],lat_j,lon_i, &DseaW, &pRX); 
					DseaC = DSea - DseaW;
													p23path = 1;
					if      (DseaW>0)				p23path = 3;
					else if((DseaW<=0)&&(DseaC>0))	p23path = 2;
				}
				Eb = FieldP1546V5(P1546fMHz_ST[i1],P1546time, p23path, h1,dist, DSea,
										  tetamax15, ttca ,Ht, P1546environment,
										  pRX, Hr, p,  Hgi, Hg[i1],  
										  P1546syst, P1546location, P1546Clangle, P1546landsea);
		//		Eb = FieldP1546V5(P1546fMHz_ST[i1],P1546time, p23path, h1,dist, DSea,
		//								  tetamax15, ttca ,Hr, P1546environment,
		//								  pRX, Ht, p,  Hg[i1], Hgi, 
		//								  P1546syst, P1546location, P1546Clangle, P1546landsea);

				//0000000000000000000000000000000000000000000000000000000000000000
				//                     Antenna    Effect
				//0000000000000000000000000000000000000000000000000000000000000000
				AZ0 = P1546AZ_ST[i1]*D2R ;
				EL0 = P1546EL_ST[i1]*D2R ;
														
				sinEL0 = sin(EL0);				cosEL0 = cos(EL0);
				dist1000_re = 1000.0*dist/re;
										
				elevp = atan(((re+Ht+Hg[i1])*cos(dist1000_re)-(re+Hr+Hgi))/((re+Ht+Hg[i1])*sin(dist1000_re)));//with Terrain
		//		elevp = atan(((re+Hr+Hgi)*cos(dist1000_re)-(re+Ht+Hg[i1]))/((re+Hr+Hgi)*sin(dist1000_re)));//with Terrain

				fp=az*D2R;		tp = (pi/2.0) - elevp;
				sinfp_AZ0 = sin(fp-AZ0);	cosfp_AZ0 = cos(fp-AZ0);	sintp = sin(tp);	costp = cos(tp);

				f = R2D*atan2(sintp*sinfp_AZ0 , cosEL0*sintp*cosfp_AZ0 + costp*sinEL0);
				t = R2D*acos(costp*cosEL0 - sinEL0*sintp*cosfp_AZ0);
				if (f<0.0)			f=f+359.4;

				Ghv = Interp2(f0,&rH[360*i1],f,360) * Interp2(f0,&rV[360*i1],t,360);

				//0000000000000000000000000000000000000000000000000000000000000000
//				Eb = Eb + 10.0*log10(P1546PtGt_ST[i1]*Ghv/1650.0);
				Eb = Eb + 10.0*log10(P1546PtGt_ST[0]*Ghv/1650.0);
//				Erm = max(Erm , Eb );
				Erm[i1] =  Eb ;
			}

double dist1234;
Er[i+Width*j] = -1;

			if(Test1(Erm, Nrow, Eth))	
			{
				if	(Test2totaln(Erm, Nrow, Eth, P1546lat_ST, P1546lon_ST, lat_j, lon_i, &dist1234))	
				{
					Er[i+Width*j] = dist1234;
				}
			}

//			Er[i+Width*j] = Erm;
			ErMax = max(ErMax , Er[i+Width*j] );
			ErMin = min(ErMin , Er[i+Width*j] );
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

//	m_MinValue = (double)Round(ErMin)+1.0;	//98/01/19
//	m_MaxValue = (double)Round(ErMax)-1.0;

//	m_MinValue = ErMin;
//	m_MaxValue = ErMax;

	m_MinValue = 0;
	m_MaxValue = 5;

	delete [] Hg;	delete [] rH;	delete [] rV;	
	delete [] Erm;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

BOOL CPro_P1546_NetFDoc::Test1(double * Erm, int n, double Eth)
{
	for(int i=0; i<n; i++)
	{
		if(Erm[i]>=Eth)	return TRUE;
	}
	return FALSE;
}
BOOL CPro_P1546_NetFDoc::Test2totaln(double * Erm, int n, double Eth, double * lat_ST, double * lon_ST, double lat_j, double lon_i, double *dist1234)
{
	*dist1234 = 999999;
	BOOL flag = FALSE;
	if(n>1)
	{
		for(int i=0; i<n; i++)
		{
			for(int j=i+1; j<n; j++)
			{
				if((Erm[i]>=Eth)&&(Erm[j]>=Eth))
				{
					double Dd = Find_Point(lat_ST[i],lon_ST[i],lat_ST[j],lon_ST[j], lat_j, lon_i);
					if(Dd>=0)
					{
						*dist1234 = min(*dist1234, Dd); 
						flag = TRUE;
					}
				}
			}
		}
	}
	return flag;
}

double CPro_P1546_NetFDoc::Find_Point(double lat_ST1,double lon_ST1,double lat_ST2,double lon_ST2,double lat_j,double lon_i) 
{
	double teta = 1; 
	double az1 = Azimuth_Deg(lat_ST1, lon_ST1, lat_j,lon_i);
	double az2 = Azimuth_Deg(lat_ST2, lon_ST2, lat_j,lon_i);

	double latC_deg, lonC_deg;
	int m = 0;

	double dist1 = 0;
	if(Find_Point2Lines(lat_ST1, lon_ST1, az1-teta, lat_ST2, lon_ST2, az2-teta, &latC_deg, &lonC_deg))
		dist1 = Distance_km(lat_j,lon_i, latC_deg, lonC_deg);
	else		m++;

	double	dist2 = 0;
	if(Find_Point2Lines(lat_ST1, lon_ST1, az1-teta, lat_ST2, lon_ST2, az2+teta, &latC_deg, &lonC_deg))
		dist2 = Distance_km(lat_j,lon_i, latC_deg, lonC_deg);
	else		m++;

	double dist3 = 0;
	if(Find_Point2Lines(lat_ST1, lon_ST1, az1+teta, lat_ST2, lon_ST2, az2-teta, &latC_deg, &lonC_deg))
		dist3 = Distance_km(lat_j,lon_i, latC_deg, lonC_deg);
	else		m++;

	double dist4 = 0;
	if(Find_Point2Lines(lat_ST1, lon_ST1, az1+teta, lat_ST2, lon_ST2, az2+teta, &latC_deg, &lonC_deg))
		dist4 = Distance_km(lat_j,lon_i, latC_deg, lonC_deg);
	else		m++;

	double dist1234 = max(max(max(dist1, dist2), dist3), dist4);
	
	if     (m==0)	return dist1234;
	else if(m==2)
	{
		dist1 = Distance_km(lat_j,lon_i, lat_ST1, lon_ST1);
		dist2 = Distance_km(lat_j,lon_i, lat_ST2, lon_ST2);
		dist1234 = max(max(dist1, dist2), dist1234);
		return dist1234;
	}
	else			return -1;

	return dist1234;
}



BOOL CPro_P1546_NetFDoc::Find_Point2Lines_(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg) 
{
	double dist12 = Distance_km(lat1, lon1, lat2, lon2);

	double lat1p, lon1p;
	reckon(lat1, lon1, 1*dist12, az1, &lat1p, &lon1p);

	float RLON1 = (float)(lon1*D2R),	RLAT1 = (float)(lat1*D2R),
		  RLON2 = (float)(lon1p*D2R),	RLAT2 = (float)(lat1p*D2R);

	double lat2p, lon2p;
	reckon(lat2, lon2, 1*dist12, az2, &lat2p, &lon2p);

	float RLON10 = (float)(lon2*D2R),		RLAT10 = (float)(lat2*D2R),
		  RLON20 = (float)(lon2p*D2R),		RLAT20 = (float)(lat2p*D2R);

	float CRDLN1[2][2] = {RLON1,  RLAT1,  RLON2,  RLAT2 };
	float CRDLN2[2][2] = {RLON10, RLAT10, RLON20, RLAT20};
	float CROSVEK[1][2];

	long NRPNT1 = 2, NRPNT2 = 2, C180=0, IEND=0, MAXCROS=100, CROSS, IREST;
	GEOC2L( (float *)CRDLN1, &NRPNT1, (float *)CRDLN2, &NRPNT2,
						&C180, &IEND, (float *)CROSVEK,  &MAXCROS, &CROSS, &IREST);

	if(CROSS>0)
	{
		*lonC_deg = CROSVEK[0][0]*R2D;
		*latC_deg = CROSVEK[0][1]*R2D;
		return TRUE;
	}
	return FALSE;
}
BOOL CPro_P1546_NetFDoc::Find_Point2Lines__(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg) 
{
	double dist12 = Distance_km(lat1, lon1, lat2, lon2);

	double lat1p, lon1p;	reckon(lat1, lon1, 3*dist12, az1, &lat1p, &lon1p);
	float RLON1 = (float)(lon1*D2R),	RLAT1 = (float)(lat1*D2R),
		  RLON2 = (float)(lon1p*D2R),	RLAT2 = (float)(lat1p*D2R);

	double lat2p, lon2p;	reckon(lat2, lon2, 3*dist12, az2, &lat2p, &lon2p);
	float RLON10 = (float)(lon2*D2R),		RLAT10 = (float)(lat2*D2R),
		  RLON20 = (float)(lon2p*D2R),		RLAT20 = (float)(lat2p*D2R);

	long NRCRD = 30;
	float CRDARR1[30][2];
	float CRDARR2[30][2];
	GEOADP(&RLON1,  &RLAT1,  &RLON2,  &RLAT2,  &NRCRD, (float *)CRDARR1 );
	GEOADP(&RLON10, &RLAT10, &RLON20, &RLAT20, &NRCRD, (float *)CRDARR2 );

	float CROSVEK[1][2];
	long NRPNT1 = NRCRD, NRPNT2 = NRCRD, C180=0, IEND=0, MAXCROS=100, CROSS, IREST;
	GEOC2L( (float *)CRDARR1, &NRPNT1, (float *)CRDARR2, &NRPNT2,
						&C180, &IEND, (float *)CROSVEK,  &MAXCROS, &CROSS, &IREST);

	if(CROSS>0)
	{
		*lonC_deg = CROSVEK[0][0]*R2D;
		*latC_deg = CROSVEK[0][1]*R2D;
		return TRUE;
	}
	return FALSE;
}
BOOL CPro_P1546_NetFDoc::Find_Point2Lines(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg) 
{
	double dist12 = Distance_km(lat1, lon1, lat2, lon2);
	int n = 0;
	while(1)
	{
		n++;
		double lat1p, lon1p;	reckon(lat1, lon1, n*dist12, az1, &lat1p, &lon1p);
		float RLON1 = (float)(lon1*D2R),	RLAT1 = (float)(lat1*D2R),
			  RLON2 = (float)(lon1p*D2R),	RLAT2 = (float)(lat1p*D2R);

		double lat2p, lon2p;	reckon(lat2, lon2, n*dist12, az2, &lat2p, &lon2p);
		float RLON10 = (float)(lon2*D2R),		RLAT10 = (float)(lat2*D2R),
			  RLON20 = (float)(lon2p*D2R),		RLAT20 = (float)(lat2p*D2R);

		long NRCRD = 10;
		float CRDARR1[10][2];
		float CRDARR2[10][2];
		GEOADP(&RLON1,  &RLAT1,  &RLON2,  &RLAT2,  &NRCRD, (float *)CRDARR1 );
		GEOADP(&RLON10, &RLAT10, &RLON20, &RLAT20, &NRCRD, (float *)CRDARR2 );

		float CROSVEK[1][2];
		long NRPNT1 = NRCRD, NRPNT2 = NRCRD, C180=0, IEND=2, MAXCROS=1, CROSS, IREST;
		GEOC2L( (float *)CRDARR1, &NRPNT1, (float *)CRDARR2, &NRPNT2,
							&C180, &IEND, (float *)CROSVEK,  &MAXCROS, &CROSS, &IREST);

		if(CROSS>0)
		{
			*lonC_deg = CROSVEK[0][0]*R2D;
			*latC_deg = CROSVEK[0][1]*R2D;
			return TRUE;
		}
		if(n>100)	
			return FALSE;
	}
	return FALSE;
}

void CPro_P1546_NetFDoc::GetData()
{
	if     (((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetF == 0)	GetData0();		//Maximum Field Strength
	else if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetF == 1)	GetData1();		//Monitoring Rx Coverage(MFS)
	else if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagP1546NetF == 2)	GetData2();		//Monitoring  AoA
}