// Pro_P530_LinkDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P530_LinkDoc.h"

#include <math.h>
#include "UTM.h"

#include "P530_Functions.h"
#include "TxRxFiltersSet.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P530_LinkDoc

IMPLEMENT_DYNCREATE(CPro_P530_LinkDoc, CDocument)

CPro_P530_LinkDoc::CPro_P530_LinkDoc()
{
	m_ReadyDoc=0;
	m_DrawFresnel = false;

	long UNR = 72 ;
	WDBUNIT(&UNR) ;
}

BOOL CPro_P530_LinkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_P530_LinkDoc::~CPro_P530_LinkDoc()
{
	delete [] m_di;
	delete [] m_hi;
	delete [] m_lati;
	delete [] m_loni;
	delete [] m_zi;
}


BEGIN_MESSAGE_MAP(CPro_P530_LinkDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_P530_LinkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P530_LinkDoc diagnostics

#ifdef _DEBUG
void CPro_P530_LinkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_P530_LinkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P530_LinkDoc serialization

void CPro_P530_LinkDoc::Serialize(CArchive& ar)
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
// CPro_P530_LinkDoc commands

__declspec(dllimport) int BasicTxLossP530V15(double* mD, double* mH, long Np, double d_km, double LongM, double LatM, CString FilepathData,
										double anav, BOOL flag_WorstMonth, double f_GHz, double htg, double hrg, double k_factor, 
										int RADIO1_rain, BOOL CHECK_Q, CString POL, int iClimate, int Fresnelnum, 
										double *loss);


int CPro_P530_LinkDoc::GetData() 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	m_zi = new int[Np];
	for(int i=0;i<Np;i++)
		m_zi[i] = LandSeaCoastal(m_loni[i],m_lati[i]);

	double d = Dmax-Dmin;
	double pi = 4.0*atan(1.0);
	double re = 6371000.0 *Linkk;

	m_Distance = d;
	h1 = LinkHagl_ST + LinkHasl_ST;
	h2 = LinkRxH + m_hi[Np-1];
	LOSDist = 0.001*sqrt( pow(re+h1,2.0) + pow(re+h2,2.0) - 2.0*(re+h1)*(re+h2)*cos(1000.0*d/re) );
	m_FsLoss = 20.0*log10(4.0*pi*LOSDist*LinkfMHz_ST/0.3);
	m_Clearance = fresnel_clearance(m_di,m_hi,Np,LinkfMHz_ST, re/1000.0,LinkHagl_ST,LinkRxH);

	PathMean(Linklon_ST, Linklat_ST, Linklon_Rx, Linklat_Rx, &LongM, &LatM);


	//////////////////////////////////P530-15///////////////////////////////////////////////
	CString FilepathData = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + "\\Texts\\";
//	BOOL flag_WorstMonth = 0;
//	int RADIO1_rain = 1;
//	BOOL CHECK_Q = 0;

	int iClimate = m_iClimate;
/*
	CString ClimateSTR;
	if     (iClimate==0)	ClimateSTR = "ITU-R REF STD (default)";
	else if(iClimate==1)	ClimateSTR = "SUMMER";
	else if(iClimate==2)	ClimateSTR = "WINTER";
*/

	double loss[15];
	int status = BasicTxLossP530V15(m_di, m_hi, Np, m_Distance, LongM, LatM, FilepathData,
								Linkanav, m_flag_WorstMonth, LinkfMHz_ST/1000.0, LinkHagl_ST, LinkRxH, Linkk, 
								m_RADIO1_rain, m_CHECK_Q, LinkPol, iClimate, Linkfzn,  
								loss);
	if(status==0)
	{
		m_Loss1L = _Z("Clear Air Fading (dB) : ");			m_Loss1.Format("%0.3f",loss[3]);
		m_Loss2L = _Z("Rain Attenuation (dB) : ");			m_Loss2.Format("%0.3f",loss[2]);
		m_Loss3L = _Z("Atmospheric Absorption (dB) : ");	m_Loss3.Format("%0.3f",loss[7]);
		m_Loss4L = _Z("Diffraction Fading (dB) : ");		m_Loss4.Format("%0.3f",loss[6]);
		m_Loss5L = _Z("Path Loss(dB) : ");					m_Loss5.Format("%0.3f",loss[9]);
	//	m_FsLoss = loss[8];
		m_Clearance = loss[5];
		A0dot01L = loss[10];

		m_rain_py = loss[11];
		m_rain_pw = loss[12];
		m_p0      = loss[13];
		m_DeltaG  = loss[14];
	}
	else
	{
		if(status==1)
		{
			CString str;
			str.Format(" Freq(GHz) : ( %0.3f --> 45.0 )  ", 15.0/m_Distance);
			m_tit = str;
		}
		else if(status==2)	m_tit = _Z("The file 'ESARAIN_MT_v5.dat' was not opened.");
		else if(status==3)	m_tit = _Z("The file 'ESARAIN_BETA_v5.dat' was not opened.");
		else if(status==4)	m_tit = _Z("The file 'ESARAIN_PR6_v5.dat.dat' was not opened.");
		else if(status==5)	m_tit = _Z("The file 'ESA0HEIGHT.dat' was not opened.");
		else if(status==6)	m_tit = _Z("The file 'dndz_01.dat' was not opened.");
		else if(status==7)	m_tit = _Z("The file 'DiffLoss.txt' was not opened.");
		else if(status==8)	m_tit = _Z("The file 'WaterVapour676_9.txt' was not opened.");
		else if(status==9)	m_tit = _Z("The file 'Oxygen676_9.txt' was not opened.");
	}

	//////////////////////////////////////////////////////////////////////////////////////////

/*
	double  RainAttn,AtomGasLoss,DiffLoss,RXClearAirFading, RainFadeML;
	CP530_Functions CP530;
	m_mK = CP530.Preparation( LatM,LongM,m_Sa);
	CP530.P530Attn(Linkatomi,Linkanav,LatM,LongM,LinkfMHz_ST,h1,h2,LOSDist,LinkPol,
									m_Clearance,Linkfzn,m_mK,
									&RainAttn,&AtomGasLoss,&DiffLoss,&RXClearAirFading,
									&RainFadeML,&A0dot01L);

	m_Loss1L = _Z("Clear Air Fading (dB) : ");			m_Loss1.Format("%0.3f",RXClearAirFading);
	m_Loss2L = _Z("Rain Attenuation (dB) : ");			m_Loss2.Format("%0.3f",RainAttn);
	m_Loss3L = _Z("Atmospheric Absorption (dB) : ");	m_Loss3.Format("%0.3f",AtomGasLoss);
	m_Loss4L = _Z("Diffraction Fading (dB) : ");		m_Loss4.Format("%0.3f",DiffLoss);
	m_Loss5L = _Z("Path Loss(dB) : ");
	m_Loss5.Format("%0.3f",m_FsLoss + AtomGasLoss + RainAttn + RXClearAirFading + DiffLoss);
*/
	///////////////////////////////// NFD //////////////
	m_NFD_Loss = 0;
//	m_NFD_Loss = NFD_Loss() ;
//	m_Loss5.Format("%0.3f",m_FsLoss + AtomGasLoss + RainAttn + RXClearAirFading + DiffLoss + m_NFD_Loss);
	////////////////////////////////////////////////////

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return status;
}

void CPro_P530_LinkDoc::PathMean(double LeftLong, double LeftLat, double RightLong, double RightLat, double *LongM, double *LatM)
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(LeftLat*pi/180.0),
			lon10 = (float)(LeftLong*pi/180.0),
			lat20 = (float)(RightLat*pi/180.0),
			lon20 = (float)(RightLong*pi/180.0),	RDIST, RAZIM, RLON, RLAT;
	GEOPPDA( &lon10 ,&lat10, &lon20,&lat20, &RDIST, &RAZIM);

	float rng_km1 = RDIST/2.f;

	GEOPDAP( &lon10 ,&lat10, &rng_km1, &RAZIM, &RLON, &RLAT);
	*LongM = RLON*180.0/pi;
	*LatM  = RLAT*180.0/pi;
}


int CPro_P530_LinkDoc::LandSeaCoastal(double RLON_deg,double RLAT_deg) 
{
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

	int zone = 3;
	if		(GC==1)		zone = 1;	//LandSea = "Coastal Zone : Sea";
	else if (GC==3)		zone = 2;	//LandSea = "Coastal Zone : Coastal Land";
	else if (GC==4)		zone = 3;	//LandSea = "Coastal Zone : InLand";

	return zone;
}
double CPro_P530_LinkDoc::Dist_ke(double d) 
{
	//  Calculation of Effective the K Factor respect to sites distance
	double ke ;
	if(d<18.4)			ke = 0.55;
	else if (d>199.5) 	ke = 1.0;
	else
	{
		//	Reading k 99.99 % from saved curve file: K_Factor.txt
 		FILE *File;
		int i;
 		double ke0[364], D0[364];

		CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\K_factor.txt");
 		if ((File = fopen(FileInfo,"r"))==NULL)
 		{
 			AfxMessageBox("The file 'K_Factor.txt' was not opened.");	exit(0);
 		}
		char bf1[200],bf2[200];
		for (i=0; i<364; i++)
		{
			fscanf(File,"%s  %s",&bf1,&bf2);
			D0[i] = atof(bf1);
			ke0[i] = atof(bf2);
		}
		ke = Interp1(D0, ke0, d, 364);
	}
	return ke;
}
double CPro_P530_LinkDoc::Interp1(double *D0,double *E0,double d,int num) 
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

double CPro_P530_LinkDoc::fresnel_clearance(double *di,double *hi,long Np, double f_MHz, double re, double Ht, double Hr)
{
	double Wave_km = 0.3 / f_MHz;
	long p = 0,				q = Np-1;

	long i;                                  /* general profile index        */
	double r_eff_2;                          /* twice effective earth radius */
	double d_p, d_q;                         /* profile distances of p, q    */
	double d_pi, d_iq, d_pq;                 /* inter-point distances        */
	double h_p, h_q;                         /* point hts above sea          */
	double h_t;                              /* cartesian ht of terrain at i */
	double h_r;                              /* cartesian ht of ray at i     */
	double r_f;                              /* Fresnel zone radius at i     */
	double wave_by_dist;                     /* wavelength over distance term*/
	double clearance1 = 1.0, min_clear;      /* clearance and lowest value   */
	double clearance = 1.0;

	if ((p+1) < (q-2))          /* if at least one point between*/
	{
		r_eff_2 = re * 2.0;                  /* test for minimum clearance   */
		d_p = di[p];
		d_q = di[q];
		h_p = 0.001*(hi[p] + Ht);
		h_q = 0.001*(hi[q] + Hr);
		d_pq = d_q - d_p;
		wave_by_dist = Wave_km / d_pq;

		min_clear = 1.0;                       /* Compiler dummy: not relied on */
		for (i = p+1; i <= q-1; i++)
		{
			d_pi = di[i] - d_p;
			d_iq = d_q - di[i];
			h_t = 0.001*hi[i] + (d_pi * d_iq / r_eff_2);  /* cartesian terrain ht */
			h_r = ((h_p * d_iq) + (h_q * d_pi)) / d_pq;   /* cartesian ray height */
			r_f = sqrt (d_pi * d_iq * wave_by_dist);      /* Fresnel zone radius  */
			clearance1 = (h_r - h_t) / r_f;
			if (i == p+1 || clearance1 < min_clear)
				min_clear = clearance1;
		}
		clearance = min_clear;
	}
	return clearance;
}




double CPro_P530_LinkDoc::interwt(double *ft,double *at,int n,double f0) 
{
	double t0;

	if (f0>ft[n-1])
		t0 = at[n-1];
	else if (f0<ft[0])
		t0 = at[0];
	else
	{
		for (int i=0;i<n;i++)
		{
            if (ft[i]==f0)
			{
                t0 = at[i];
                break;
			}
            else if (ft[i]>f0)
			{
				t0=at[i-1]+(f0-ft[i-1])*(at[i]-at[i-1])/(ft[i]-ft[i-1]);
                break;
            }
		}
	}
	return t0;
}
double CPro_P530_LinkDoc::MinValue(double *xi,int N) 
{
	double  xiMIN = xi[0];
	for (int i=1;i<N;i++)
		xiMIN = min(xiMIN,xi[i]);	
	return xiMIN;
}
double CPro_P530_LinkDoc::MaxValue(double *xi,int N) 
{
	double  xiMAX = xi[0];
	for (int i=1;i<N;i++)
		xiMAX = max(xiMAX,xi[i]);	
	return xiMAX;
}
double CPro_P530_LinkDoc::subsection(double a,double b,double fc) 
{
	double y;
	if (a==0)
        y = fc * pow(10.0,(-b/10.0));
	else
        y = ( pow(10.0,(-b/10.0)) )*( pow(10.0,(-a*fc/10.0)) - 1.0 )/(-a*log(10.0)/10.0);
	return y;
}


double CPro_P530_LinkDoc::NFD_Loss() 
{
///////////////////////////////// NFD /////////////////////////////////
	double NFD = 0;
	CString str;

	str.Format("SELECT * FROM TxFilters WHERE (((EqID)=%ld)) ORDER BY EqID;",ID_Tx);
	CTxRxFiltersSet m_pSet(str);
	m_pSet.Open();
	if(m_pSet.GetRecordCount()==1)
	{
		double ft0[20] , at0[20];
		m_pSet.MoveFirst();
		int TxNum = 0;
		while( !m_pSet.IsEOF())
		{
			ft0[TxNum] = m_pSet.m_CS;
			at0[TxNum] = m_pSet.m_Att;
			TxNum++;
			m_pSet.MoveNext();
		}
		m_pSet.Close();

		str.Format("SELECT * FROM RxFilters WHERE (((EqID)=%ld)) ORDER BY EqID;",ID_Rx);
		CTxRxFiltersSet m_pSet1(str);
		m_pSet1.Open();
		if(m_pSet1.GetRecordCount()==1)
		{
			double fr0[20] , ar0[20];
			m_pSet1.MoveFirst();
			int RxNum = 0;
			while( !m_pSet1.IsEOF())
			{
				fr0[RxNum] = m_pSet1.m_CS;
				ar0[RxNum] = m_pSet1.m_Att;
				RxNum++;
				m_pSet1.MoveNext();
			}
			m_pSet1.Close();

			double  ft[20] , at[20], fr[20] , ar[20];
			double	ft0max = MaxValue(ft0,TxNum),	ft0min = MinValue(ft0,TxNum),
					fr0max = MaxValue(fr0,RxNum),	fr0min = MinValue(fr0,RxNum);

			double stepTx=(ft0max-ft0min)/19.0;
			double stepRx=(fr0max-fr0min)/19.0;
			int i;
			for( i=0;i<20;i++)
			{
				ft[i] = ft0min + i*stepTx;		at[i] = interwt(ft0,at0,TxNum,ft[i]);
				fr[i] = fr0min + i*stepRx;		ar[i] = interwt(fr0,ar0,RxNum,fr[i]);

				ft[i] = (ft[i] + LinkfMHz_ST)*1000000.0;
				fr[i] = (fr[i] + LinkfMHz_Rx)*1000000.0;
			}
			double	ftmax = MaxValue(ft,20),	ftmin = MinValue(ft,20),
					frmax = MaxValue(fr,20),	frmin = MinValue(fr,20),
					fmax = max(ftmax,frmax),	fmin = min(ftmin,frmin);

			int nf = 1000;
			double	fstep=(fmax-fmin)/nf;
			double *fnew;	fnew = new double[nf];
			double *atnew;  atnew = new double[nf];
			double *arnew;  arnew = new double[nf];
			double *y;		y = new double[nf-1];
			double *z;		z = new double[nf-1];
			double *fnewp;  fnewp = new double[nf];
			double *atnewp; atnewp = new double[nf];
			double *arnewp; arnewp = new double[nf];
			double *atrp;	atrp = new double[nf];

			for( i=0;i<nf;i++)
			{
				fnew[i] = fmin + i*fstep;
				atnew[i] = interwt(ft,at,20,fnew[i]);
				arnew[i] = interwt(fr,ar,20,fnew[i]);

				fnewp[i] = fnew[i]/1000000.0;
				atnewp[i] = -atnew[i];
				arnewp[i] = -arnew[i];
				atrp[i] = -atnew[i]-arnew[i];
			}
			double fc,a,b, sumy = 0.0, sumz = 0.0 ;
			for( i=0;i<nf-1;i++)
			{
				fc = fabs(fnew[i+1]-fnew[i]);
				a = (atnew[i+1]-atnew[i])/fc;
   				b = atnew[i];
				y[i] = subsection(a,b,fc);

				a = (atnew[i+1]-atnew[i]+arnew[i+1]-arnew[i])/fc;
				b = atnew[i]+arnew[i];
				z[i] = subsection(a,b,fc); 

				sumy += y[i];
				sumz += z[i];
			}
			NFD = 10.0*log10(sumy/sumz);

			delete [] fnew;	delete [] atnew;	delete [] arnew;	delete [] y;	delete [] z;
			delete [] atnewp;	delete [] arnewp;	delete [] fnewp;	delete [] atrp;

		}	// end if Rx Recoard set
		else
		{
			str.Format(_Z("\nRx Filter is not defined for the Receiver : %s.\t\t\n"),LinkName_Rx);
			MessageBox(NULL,str,_Z("Warning!!!"),MB_ICONWARNING);
		}

	}	// end if Tx Recoard set
	else
	{
		str.Format(_Z("\nTx Filter is not defined for the Transmitter : %s.\t\t\n"),LinkName_ST);
		MessageBox(NULL,str,_Z("Warning!!!"),MB_ICONWARNING);
	}

	return NFD;
}