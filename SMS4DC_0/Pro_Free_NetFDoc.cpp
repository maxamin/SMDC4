// Pro_Free_NetFDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_Free_NetFDoc.h"
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
// CPro_Free_NetFDoc

IMPLEMENT_DYNCREATE(CPro_Free_NetFDoc, CDocument)

CPro_Free_NetFDoc::CPro_Free_NetFDoc()
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

	long UNR = 72 ;	WDBUNIT(&UNR) ;

	pi = 4.0*atan(1.0);
	D2R = pi/180.0;
	R2D = 180.0/pi;

}

BOOL CPro_Free_NetFDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_Free_NetFDoc::~CPro_Free_NetFDoc()
{
	delete [] bufAreaFree;
	delete [] bufArea;
	delete [] Er;
	delete [] Freelat_ST;
	delete [] Freelon_ST;
	delete [] FreePtGt_ST;
	delete [] FreeHagl_ST;
	delete [] FreeAZ_ST;
	delete [] FreeEL_ST;
	delete [] FreeANT_ST;
	delete [] FreeName_ST;
}


BEGIN_MESSAGE_MAP(CPro_Free_NetFDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_Free_NetFDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_NetFDoc diagnostics

#ifdef _DEBUG
void CPro_Free_NetFDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_Free_NetFDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_NetFDoc serialization

void CPro_Free_NetFDoc::Serialize(CArchive& ar)
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
// CPro_Free_NetFDoc commands


void CPro_Free_NetFDoc::GetData0()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

for(int i10=0;i10<Nrow;i10++)
	Freelon_ST[i10] = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelon_ST[i10],TileX);
Freelon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelon0,TileX);
Freelonmax   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelonmax,TileX);

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];
	int i,i1;

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j]=bufAreaFree[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin=min(bufMin,bufArea[i+Width*j]);
			bufMax=max(bufMax,bufArea[i+Width*j]);
		}

	Er=new double[Width*Height];
	double Erm0,Erm;
	double Ghv,	dist;
	double lat_j,lon_i;


	CString antfile;
	double elevp,tp,fp,az,f,t;
	double pi=4.0*atan(1.0);

	double Hr = FreeRxH ,   k = Freek;
	double r = 6371000.0 , re = k*r;

	double AZ0,EL0,Ht;

	CPoint m_Point_ST,pointi;
	double *HgST,Hgi,Hg;
	int f0[360];	double rH1[360]  ,  rV1[360]   ,*rH  ,  *rV;

	HgST = new double[Nrow];
	rH = new double[Nrow*360];
	rV = new double[Nrow*360];

	for( i1=0;i1<Nrow;i1++)
	{
		LatLon2Point(Freelat_ST[i1],Freelon_ST[i1], &m_Point_ST) ;
		HgST[i1] = Point2Hg(m_Point_ST);

		antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,FreeANT_ST[i1]);
		ReadAntennaData(antfile,f0,rH1,rV1) ;
		for( i=0;i<360;i++)
		{
			rH[i+360*i1] = rH1[i];
			rV[i+360*i1] = rV1[i];
		}
	}
//98/01/20
double disttest1 = Distance_km(Freelat_ST[0],Freelon_ST[0], Freelat_ST[0]+0, Freelon_ST[0]+m_Resolution_x);
double disttest2 = Distance_km(Freelat_ST[0],Freelon_ST[0], Freelat_ST[0]+m_Resolution_x, Freelon_ST[0]+0);
double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			Erm=-32768.0;
			for( i1=0;i1<Nrow;i1++)
			{
				lat_j = Freelat0+(j/m_ZoomFactor)*m_Resolution_x;
				lon_i = Freelon0+(i/m_ZoomFactor)*m_Resolution_x;

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
				dist=Distance_km(Freelat_ST[i1],Freelon_ST[i1],lat_j,lon_i);
			//	dist = max(dist,0.00001);	//km		//98/01/20
				dist = max(dist, StepRes/2.0);			//98/01/20

				//0000000000000000000000000000000000000000000000000000000000000000
				//                     Antenna    Effect
				//0000000000000000000000000000000000000000000000000000000000000000
				AZ0 = FreeAZ_ST[i1]*pi/180.0 ;
				EL0 = FreeEL_ST[i1]*pi/180.0 ;
				Ht = FreeHagl_ST[i1];
				Hg = HgST[i1];
				
				az=Azimuth_Deg(Freelat_ST[i1],Freelon_ST[i1],lat_j,lon_i);
				LatLon2Point(lat_j,lon_i, &pointi) ;
				Hgi=Point2Hg(pointi);
										//with Terrain
				elevp = atan(((re+Hr+Hgi)*cos(1000.0*dist/re)-(re+Ht+Hg))/((re+Hr+Hgi)*sin(1000.0*dist/re)));
				dist = sqrt( pow(re+Ht+Hg,2.0) + pow(re+Hr+Hgi,2.0) - 2.0*(re+Ht+Hg)*(re+Hr+Hgi)*cos(1000.0*dist/re) );
										//without Terrain
				//elevp = atan(((re+Hr)*cos((dist*1000.0)/re)-(re+Ht+Hg))/((re+Hr)*sin((dist*1000.0)/re)));
				//dist = sqrt( pow(re+Ht+Hg,2.0) + pow(re+Hr,2.0) -2.0*(re+Ht+Hg)*(re+Hr)*cos(1000.0*dist/re) );

//dist=max(dist,0.05);	//m			//98/01/20
				dist=dist/1000.0;	fp=az*pi/180.0;		tp = (pi/2.0) - elevp;

				f = (180.0/pi)*atan2(sin(tp)*sin(fp-AZ0),(cos(EL0)*sin(tp)*cos(fp-AZ0)+cos(tp)*sin(EL0)));
				t = (180.0/pi)*acos(cos(tp)*cos(EL0)-sin(EL0)*sin(tp)*cos(fp-AZ0));

				if (f<0.0)		f=f+359.4;

				Ghv = Interp2(f0,&rH[360*i1],f,360) * Interp2(f0,&rV[360*i1],t,360);
				//Ghv = rH[Round(f)+360*i1] * rV[Round(t)+360*i1];
				//0000000000000000000000000000000000000000000000000000000000000000

				Erm0=(sqrt(30.0*FreePtGt_ST[i1]*Ghv))/(1000.0*dist);
				Erm0=(120.0+20.0*(log10(Erm0)));

				Erm =max(Erm , Erm0 );
			}

			Er[i+Width*j]=Erm;
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

	delete [] rH;	delete [] rV;	delete [] HgST;

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}
//98/01/19
int CPro_Free_NetFDoc::Round(double x) 
{
	int y;
	int x1 = (int)x;
	if(x>=0)	{int x2 = x1+1;		y = ( (x > ((double)x1)+0.45) ? x2 : x1);}
	else		{int x2 = x1-1;		y = ( (x > ((double)x2)+0.45) ? x1 : x2);}
	return y;
}
/*
int CPro_Free_NetFDoc::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);
}
*/
double CPro_Free_NetFDoc::Distance_km(double lat1,double lon1,double lat2,double lon2) 
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


void CPro_Free_NetFDoc::ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) 
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

double CPro_Free_NetFDoc::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) 
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

void CPro_Free_NetFDoc::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
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
	double ix = (double)(m_ZoomFactor)*((lon_deg - Freelon0)/(m_Resolution_x));
	double jy = (double)(m_ZoomFactor)*((lat_deg - Freelat0)/(m_Resolution_x));

	(*PointSt).x = (long)ix;
	(*PointSt).y=(long)(Height-1-jy);
}

double CPro_Free_NetFDoc::Point2Hg(CPoint point1) 
{
	int i1=point1.x   ,   j1=(Height-1)-point1.y;
	_int16 Hg=bufArea[i1+Width*j1];
	return (double)Hg;
}


BOOL CPro_Free_NetFDoc::PeekAndPump()
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

double CPro_Free_NetFDoc::Interp2(int *D0,double *E0,double d,int num) 
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


//Monitoring Rx Coverage
///////////////////////
void CPro_Free_NetFDoc::GetData1()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	for(int i10=0;i10<Nrow;i10++)
		Freelon_ST[i10] = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelon_ST[i10],TileX);
	Freelon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelon0,TileX);
	Freelonmax   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelonmax,TileX);

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];
	int i,i1;

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j]=bufAreaFree[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin=min(bufMin,bufArea[i+Width*j]);
			bufMax=max(bufMax,bufArea[i+Width*j]);
		}

	Er = new double[Width*Height];
	double Erm0, Erm;
	double Ghv,	dist;
	double lat_j,lon_i;


	CString antfile;
	double elevp,tp,fp,az,f,t;
	double pi=4.0*atan(1.0);

	double Hr = FreeRxH ,   k = Freek;
	double r = 6371000.0 , re = k*r;

	double AZ0,EL0,Ht;

	CPoint m_Point_ST,pointi;
	double *HgST,Hgi,Hg;
	int f0[360];	double rH1[360]  ,  rV1[360]   ,*rH  ,  *rV;

	HgST = new double[Nrow];
	rH = new double[Nrow*360];
	rV = new double[Nrow*360];

	for( i1=0;i1<Nrow;i1++)
	{
		LatLon2Point(Freelat_ST[i1],Freelon_ST[i1], &m_Point_ST) ;
		HgST[i1] = Point2Hg(m_Point_ST);

		antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,FreeANT_ST[i1]);
		ReadAntennaData(antfile,f0,rH1,rV1) ;
		for( i=0;i<360;i++)
		{
			rH[i+360*i1] = rH1[i];
			rV[i+360*i1] = rV1[i];
		}
	}
	//98/01/20
	double disttest1 = Distance_km(Freelat_ST[0],Freelon_ST[0], Freelat_ST[0]+0, Freelon_ST[0]+m_Resolution_x);
	double disttest2 = Distance_km(Freelat_ST[0],Freelon_ST[0], Freelat_ST[0]+m_Resolution_x, Freelon_ST[0]+0);
	double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			lat_j = Freelat0+(j/m_ZoomFactor)*m_Resolution_x;
			lon_i = Freelon0+(i/m_ZoomFactor)*m_Resolution_x;

			Erm=-32768.0;
			for( i1=0;i1<Nrow;i1++)
			{

		/*		CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
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
				dist = Distance_km(Freelat_ST[i1],Freelon_ST[i1],lat_j,lon_i);
				dist = max(dist, StepRes/2.0);			//98/01/20

				//0000000000000000000000000000000000000000000000000000000000000000
				//                     Antenna    Effect
				//0000000000000000000000000000000000000000000000000000000000000000
				AZ0 = FreeAZ_ST[i1]*pi/180.0 ;
				EL0 = FreeEL_ST[i1]*pi/180.0 ;
				Ht = FreeHagl_ST[i1];
				Hg = HgST[i1];
				
				az = Azimuth_Deg(lat_j,lon_i, Freelat_ST[i1],Freelon_ST[i1]);
		//		az = Azimuth_Deg(Freelat_ST[i1],Freelon_ST[i1], lat_j,lon_i);

				LatLon2Point(lat_j,lon_i, &pointi) ;
				Hgi = Point2Hg(pointi);
										//with Terrain
				elevp = atan(((re+Ht+Hg )*cos(1000.0*dist/re)-(re+Hr+Hgi))/((re+Ht+Hg )*sin(1000.0*dist/re)));
		//		elevp = atan(((re+Hr+Hgi)*cos(1000.0*dist/re)-(re+Ht+Hg ))/((re+Hr+Hgi)*sin(1000.0*dist/re)));


				dist = sqrt( pow(re+Hr+Hgi,2.0) + pow(re+Ht+Hg ,2.0) - 2.0*(re+Hr+Hgi)*(re+Ht+Hg )*cos(1000.0*dist/re) );
		//		dist = sqrt( pow(re+Ht+Hg ,2.0) + pow(re+Hr+Hgi,2.0) - 2.0*(re+Ht+Hg )*(re+Hr+Hgi)*cos(1000.0*dist/re) );

				dist=dist/1000.0;	fp=az*pi/180.0;		tp = (pi/2.0) - elevp;

				f = (180.0/pi)*atan2(sin(tp)*sin(fp-AZ0),(cos(EL0)*sin(tp)*cos(fp-AZ0)+cos(tp)*sin(EL0)));
				t = (180.0/pi)*acos(cos(tp)*cos(EL0)-sin(EL0)*sin(tp)*cos(fp-AZ0));

				if (f<0.0)		f=f+359.4;

				Ghv = Interp2(f0,&rH[360*i1],f,360) * Interp2(f0,&rV[360*i1],t,360);

				//0000000000000000000000000000000000000000000000000000000000000000

				Erm0=(sqrt(30.0*FreePtGt_ST[0]*Ghv))/(1000.0*dist);
	//			Erm0=(sqrt(30.0*FreePtGt_ST[i1]*Ghv))/(1000.0*dist);
				Erm0=(120.0+20.0*(log10(Erm0)));

				Erm = max(Erm , Erm0 );
			}
			Er[i+Width*j]=Erm;

			ErMax = max(ErMax , Er[i+Width*j] );
			ErMin = min(ErMin , Er[i+Width*j] );
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

	delete [] rH;	delete [] rV;	delete [] HgST;

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

void CPro_Free_NetFDoc::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) 
{
	float	lat_rad = (float)(lat_deg*D2R),
			lon_rad = (float)(lon_deg*D2R),
			RLON, RLAT,	 rng_km1 = (float)rng_km, az_deg1 = (float)az_deg;
	GEOPDAP( &lon_rad, &lat_rad, &rng_km1, &az_deg1, &RLON, &RLAT);
	*latC_deg = RLAT*R2D;
	*lonC_deg = RLON*R2D;
}

BOOL CPro_Free_NetFDoc::Test1(double * Erm, int n, double Eth)
{
	for(int i=0; i<n; i++)
	{
		if(Erm[i]>=Eth)	return TRUE;
	}
	return FALSE;
}

double CPro_Free_NetFDoc::Find_Point(double lat_ST1,double lon_ST1,double lat_ST2,double lon_ST2,double lat_j,double lon_i) 
{
	double teta = m_teta_deg; 
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



BOOL CPro_Free_NetFDoc::Find_Point2Lines_(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg) 
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

BOOL CPro_Free_NetFDoc::Find_Point2Lines__(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg) 
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

BOOL CPro_Free_NetFDoc::Find_Point2Lines(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg) 
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
		if(n>100)	return FALSE;
	}
	return FALSE;
}



BOOL CPro_Free_NetFDoc::Test2totaln(double * Erm, int n, double Eth, double * lat_ST, double * lon_ST, double lat_j, double lon_i, double *dist1234)
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



#include "MonitoringThDLG.h"

// Monitoring  AoA
///////////////////////
void CPro_Free_NetFDoc::GetData2()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	for(int i10=0;i10<Nrow;i10++)
		Freelon_ST[i10] = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelon_ST[i10],TileX);
	Freelon0   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelon0,TileX);
	Freelonmax   = ((CSMS4DCApp *)AfxGetApp())->ChangeLon(Freelonmax,TileX);

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];
	int i,i1;

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j]=bufAreaFree[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin=min(bufMin,bufArea[i+Width*j]);
			bufMax=max(bufMax,bufArea[i+Width*j]);
		}

	Er = new double[Width*Height];
	double Erm0;
	double *Erm = new double[Nrow];
	double Ghv,	dist;
	double lat_j,lon_i;


	double Eth = 20+28;
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


	CString antfile;
	double elevp,tp,fp,az,f,t;
	double pi=4.0*atan(1.0);

	double Hr = FreeRxH ,   k = Freek;
	double r = 6371000.0 , re = k*r;

	double AZ0,EL0,Ht;

	CPoint m_Point_ST,pointi;
	double *HgST,Hgi,Hg;
	int f0[360];	double rH1[360]  ,  rV1[360]   ,*rH  ,  *rV;

	HgST = new double[Nrow];
	rH = new double[Nrow*360];
	rV = new double[Nrow*360];

	for( i1=0;i1<Nrow;i1++)
	{
		LatLon2Point(Freelat_ST[i1],Freelon_ST[i1], &m_Point_ST) ;
		HgST[i1] = Point2Hg(m_Point_ST);

		antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,FreeANT_ST[i1]);
		ReadAntennaData(antfile,f0,rH1,rV1) ;
		for( i=0;i<360;i++)
		{
			rH[i+360*i1] = rH1[i];
			rV[i+360*i1] = rV1[i];
		}
	}
	//98/01/20
	double disttest1 = Distance_km(Freelat_ST[0],Freelon_ST[0], Freelat_ST[0]+0, Freelon_ST[0]+m_Resolution_x);
	double disttest2 = Distance_km(Freelat_ST[0],Freelon_ST[0], Freelat_ST[0]+m_Resolution_x, Freelon_ST[0]+0);
	double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			lat_j = Freelat0+(j/m_ZoomFactor)*m_Resolution_x;
			lon_i = Freelon0+(i/m_ZoomFactor)*m_Resolution_x;

	//		Erm=-32768.0;
			for( i1=0;i1<Nrow;i1++)
			{

		/*		CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
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
				dist = Distance_km(Freelat_ST[i1],Freelon_ST[i1],lat_j,lon_i);
				dist = max(dist, StepRes/2.0);			//98/01/20

				//0000000000000000000000000000000000000000000000000000000000000000
				//                     Antenna    Effect
				//0000000000000000000000000000000000000000000000000000000000000000
				AZ0 = FreeAZ_ST[i1]*pi/180.0 ;
				EL0 = FreeEL_ST[i1]*pi/180.0 ;
				Ht = FreeHagl_ST[i1];
				Hg = HgST[i1];
				
				az = Azimuth_Deg(lat_j,lon_i, Freelat_ST[i1],Freelon_ST[i1]);
		//		az = Azimuth_Deg(Freelat_ST[i1],Freelon_ST[i1], lat_j,lon_i);

				LatLon2Point(lat_j,lon_i, &pointi) ;
				Hgi = Point2Hg(pointi);
										//with Terrain
				elevp = atan(((re+Ht+Hg )*cos(1000.0*dist/re)-(re+Hr+Hgi))/((re+Ht+Hg )*sin(1000.0*dist/re)));
		//		elevp = atan(((re+Hr+Hgi)*cos(1000.0*dist/re)-(re+Ht+Hg ))/((re+Hr+Hgi)*sin(1000.0*dist/re)));


				dist = sqrt( pow(re+Hr+Hgi,2.0) + pow(re+Ht+Hg ,2.0) - 2.0*(re+Hr+Hgi)*(re+Ht+Hg )*cos(1000.0*dist/re) );
		//		dist = sqrt( pow(re+Ht+Hg ,2.0) + pow(re+Hr+Hgi,2.0) - 2.0*(re+Ht+Hg )*(re+Hr+Hgi)*cos(1000.0*dist/re) );

				dist=dist/1000.0;	fp=az*pi/180.0;		tp = (pi/2.0) - elevp;

				f = (180.0/pi)*atan2(sin(tp)*sin(fp-AZ0),(cos(EL0)*sin(tp)*cos(fp-AZ0)+cos(tp)*sin(EL0)));
				t = (180.0/pi)*acos(cos(tp)*cos(EL0)-sin(EL0)*sin(tp)*cos(fp-AZ0));

				if (f<0.0)		f=f+359.4;

				Ghv = Interp2(f0,&rH[360*i1],f,360) * Interp2(f0,&rV[360*i1],t,360);

				//0000000000000000000000000000000000000000000000000000000000000000

				Erm0=(sqrt(30.0*FreePtGt_ST[0]*Ghv))/(1000.0*dist);
//				Erm0=(sqrt(30.0*FreePtGt_ST[i1]*Ghv))/(1000.0*dist);
				Erm0=(120.0+20.0*(log10(Erm0)));

//				Erm = max(Erm , Erm0 );
				Erm[i1] =  Erm0 ;
			}

double dist1234;
Er[i+Width*j] = -1;

			if(Test1(Erm, Nrow, Eth))	
			{
				if	(Test2totaln(Erm, Nrow, Eth, Freelat_ST, Freelon_ST, lat_j, lon_i, &dist1234))	
				{
					Er[i+Width*j] = dist1234;
				}
			}

//			Er[i+Width*j]=Erm;

			ErMax = max(ErMax , Er[i+Width*j] );
			ErMin = min(ErMin , Er[i+Width*j] );
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

//	m_MinValue = (double)Round(ErMin)+1.0;	//98/01/19
//	m_MaxValue = (double)Round(ErMax)-1.0;
//	m_MinValue = ErMin;
//	m_MaxValue = ErMax;

	m_MinValue = 0;
	m_MaxValue = 5;

	delete [] rH;	delete [] rV;	delete [] HgST;
	delete [] Erm;

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}




void CPro_Free_NetFDoc::GetData()
{
	if     (((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetF == 0)	GetData0();		//Maximum Field Strength
	else if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetF == 1)	GetData1();		//Monitoring Rx Coverage(MFS)
	else if(((CSMS4DCApp *)AfxGetApp())->m_modeFlagFreeNetF == 2)	GetData2();		//Monitoring  AoA
}
