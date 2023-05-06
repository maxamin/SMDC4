// P530_Functions.cpp: implementation of the CP530_Functions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS4DC.h"
#include "P530_Functions.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP530_Functions::CP530_Functions()
{

}

CP530_Functions::~CP530_Functions()
{

}

//////////////////////////////////////////////////////////////////////

void CP530_Functions::P530Attn(int iClimate,double AnAv,double LatM,double LongM,double FrqMHzL, double h1, double h2,
						double LOSDist,CString PolL,double FZClearance,int Fresnelnum,double mK,
						double *RainAttnL,double *AtomGasLossL,double *DiffLoss,
						double *RXClearAirFadingR,
						double *RainFadeML,double *A0dot01L)
{
	CString	Climate;
	if      (iClimate==0)		Climate = "ANNUAL TROPIC";
	else if (iClimate==1)		Climate = "ITU-R REF STD (default)";
	else if (iClimate==2)		Climate = "SUMMER HIGH LATITUDE";
	else if (iClimate==3)		Climate = "SUMMER MID-LATITUDE";
	else if (iClimate==4)		Climate = "WINTER HIGH LATITUDE";
	else if (iClimate==5)		Climate = "WINTER MID-LATITUDE";
	else						Climate = "ITU-R REF STD (default)";

	double 	AnEx = 100.0 - AnAv;

	*AtomGasLossL = AtmosphericAbsorbtion(Climate,FrqMHzL,LOSDist,h1,h2);
	*DiffLoss = Diff_Loss(FZClearance,Fresnelnum) ;

	RainAttenuation(FrqMHzL,h1,h2,LOSDist,PolL,AnEx,LatM,LongM, &(*RainAttnL),&(*RainFadeML),&(*A0dot01L));
	A_from_pw(AnEx,LOSDist,FrqMHzL,h1,h2,mK,LatM, &(*RXClearAirFadingR));
}

void CP530_Functions::P530Outage(double LatM,double RainFadeML,double A0dot01L,
								double FrqMHz,double LOSDist,double h1,double h2,
								double FlatFadeMarginR,double mK,
								double *RainAnEx,double *RainWorstMonthEx,
								double *MultipathAnEx,double *MultipathWorstMonthEx) 
{
	RainOutage(LatM,RainFadeML,A0dot01L,&(*RainAnEx),&(*RainWorstMonthEx));

	double p0 = PathP0(FrqMHz,LOSDist,h1,h2,mK);
	double An2WorstMonthC = An2WorstMonthConvertor(LatM,LOSDist,h1,h2);
	MultipathOutage(FlatFadeMarginR,p0,An2WorstMonthC,&(*MultipathAnEx),&(*MultipathWorstMonthEx));
}




//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
double CP530_Functions::Interp1I(double *E0,double *D0,double E,int num) 
{
	double d1,d2,E1,E2,Db;
	if (E>E0[0])
	{
		d1=D0[0];d2=D0[1];
		E1=E0[0];E2=E0[1];
	}
	else if (E<E0[num-1])
	{
		d1=D0[num-2];d2=D0[num-1];
		E1=E0[num-2];E2=E0[num-1];
	}
	else
	{
		/////////////////////////////////////////////
		int n1=0;
		while(E<=E0[n1])
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
		while(E>=E0[n2])
		{
			n2--;
			if (n2==0)
				break;
		}
		d2=D0[n2+1];E2=E0[n2+1];
		////////////////////////////////////////////////
	}
	Db=((E1==E2) ? d1 : d1+((d2-d1)*(E-E1)/(E2-E1)) );
	return Db;
}
double CP530_Functions::Interp1(double *D0,double *E0,double d,int num) 
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


double CP530_Functions::Diff_Loss(double FZClearance,int Fresnelnum) 
{
	double DiffLoss = 0.0;
	double FirstFresnelZoneClearance = FZClearance*sqrt(Fresnelnum);
	if (FirstFresnelZoneClearance>=1)
		DiffLoss =0;
	else
	{
		if (FirstFresnelZoneClearance<0)
			DiffLoss = -20.0*FirstFresnelZoneClearance + 10.0;
		else
		{
			// Loading Diffraction Loss
 			FILE *File;
			CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\DiffLoss.txt");
 			if( (File = fopen(FileInfo,"r")) == NULL )
 			{
 				AfxMessageBox(_Z("The file 'DiffLoss.txt' was not opened.")); 	exit(0);
 			}
			double Clearance0[337], Diff0[337];
			char bf1[200],bf2[200];
			for (int i=0; i<337; i++)
			{
				fscanf(File,"%s  %s",&bf1,&bf2);
				Clearance0[i] = atof(bf1);
				Diff0[i] = atof(bf2);
			}
			DiffLoss = Interp1(Clearance0, Diff0, FirstFresnelZoneClearance ,337);
		}
	}
	return DiffLoss;
}


void CP530_Functions::StandardAtmosphers(CString atmos, double hei, double *P1, double *T1, double *RHO1)
{
	double p, T, ro;

	if (atmos.Compare("SUMMER MID-LATITUDE")==0)
	{
		// Pressure in hPa
		if (hei>=0 && hei<=10)
			p =1012.8186 - 111.5569*hei + 3.8646*hei*hei;
		else if (hei>10 && hei<=72)
			p = 283.7096*exp(-0.147*(hei - 10));
		else if (hei>72 && hei<=100)
			p=0.0312402229*exp(-0.165*(hei-72));
		else
			p=0;

		// Temperature in Kelvin
		if (hei>=0 && hei<=13)
			T = 294.9838 - 5.2159*hei - 0.07109*hei*hei;
		else if (hei>13 && hei<=17)
			T = 215.15;
		else if (hei>17 && hei<=47)
			T = 215.15*exp(0.008128*(hei-17));
		else if (hei>47 && hei<=53)
			T=275;
		else if (hei>53 && hei<=80)
			T = 275+20*(1 - exp(0.06*(hei-53)));
		else if (hei>80 && hei<=100)
			T=175;
		else
			T=0;

		// absolute humidity in g/m^3
		if (hei>=0 &&	hei<=15)
			ro = 14.2542*exp(-0.4174*hei-0.02290*hei*hei + 0.001007*hei*hei*hei);
		else
			ro=0;
	}

	if (atmos.Compare("WINTER MID-LATITUDE")==0)
	{
		// Pressure in hPa
		if (hei>=0 && hei<=10)
			p = 1018.8627 - 124.2954*hei + 4.8307*hei*hei;
		else if (hei>10 && hei<=72)
			p = 258.9787*exp(-0.147*(hei-10));
		else if (hei>72 && hei<=100)
			p = 0.0285170199*exp(-0.155*(hei-72));
		else
			p=0;

		// Temperature in Kelvin
		if (hei>=0 && hei<=10)
			T = 272.7241 - 3.6217*hei - 0.1759*hei*hei;
		else if (hei>10 && hei<=33)
			T=218;
		else if (hei>33 && hei<=47)
			T = 218 + 3.3571*(hei-33);
		else if (hei>47 && hei<=53)
			T=265;
		else if (hei>53 && hei<=80)
			T = 265-2.0370*(hei-53);
		else if (hei>80 && hei<=100)
			T = 210;
		else
			T = 0;

		// absolute humidity in g/m^3
		if (hei>=0 && hei<=10)
			ro = 3.4742*exp(-0.2697*hei - 0.03604*hei*hei + 0.0004489*hei*hei*hei);
		else
			ro = 0;
		}

    if (atmos.Compare("SUMMER HIGH LATITUDE")==0)
	{
		// Pressure in hPa
		if (hei>=0 && hei<=10)
			p = 1008.0278 - 113.2494*hei + 3.9408*hei*hei;
		else if (hei>10 && hei<=72)
			p = 269.6138*exp(-0.140*(hei-10));
		else if (hei>72 && hei<=100)
			p = 0.0458211532*exp(-0.165*(hei-72));
		else
			p = 0;

		// Temperature in Kelvin
		if (hei>=0 && hei<=10)
			T = 286.8374 - 4.7805*hei - 0.1402*hei*hei;
		else if (hei>10 && hei<=23)
			T = 225;
		else if (hei>23 && hei<=48)
			T = 225*exp(0.008317*(hei-23));
		else if (hei>48 && hei<=53)
			T = 277;
		else if (hei>53 && hei<=79)
			T = 277-4.0769*(hei-53);
		else if (hei>79 && hei<=100)
			T=171;
		else
			T=0;

		// absolute humidity in g/m^3
		if (hei>=0 && hei<=15)
			ro = 8.988*exp(-0.3614*hei - 0.005402*hei*hei - 0.001955*hei*hei*hei);
		else
			ro = 0;
	}

    if (atmos.Compare("WINTER HIGH LATITUDE")==0)
	{
		// Pressure in hPa
		if (hei>=0 && hei<=10)
			p = 1010.8828 - 122.2411*hei + 4.554*hei*hei;
		else if (hei>10 && hei<=72)
			p = 243.8718*exp(-0.147*(hei-10));
		else if (hei>72 && hei<=100)
			p = 0.0268535481*exp(-0.150*(hei-72));
		else
			p = 0;

		// Temperature in Kelvin
		if (hei>=0 && hei<=8.5)
			T = 257.4345 + 2.3474*hei - 1.5479*hei*hei + 0.08473*hei*hei*hei;
		else if (hei>8.5 && hei<=30)
			T = 217.5;
		else if (hei>30 && hei<=50)
			T = 217.5 + 2.125*(hei-30);
		else if (hei>50 && hei<=54)
			T = 260;
		else if (hei>54 && hei<=100)
			T = 260-1.667*(hei-54);
		else
			T = 0;
   
		// absolute humidity in g/m^3
		if (hei>=0 && hei<=10)
			ro = 1.2319*exp(0.07481*hei - 0.0981*hei*hei + 0.00281*hei*hei*hei);
		else
			ro = 0;
	}

	if (atmos.Compare("ANNUAL TROPIC")==0)
	{
		// Pressure in hPa
		if (hei>=0 && hei<=10)
			p = 1012.0306 - 109.0338*hei + 3.6316*hei*hei;
		else if (hei>10 && hei<=72)
			p = 284.8526*exp(-0.147*(hei-10));
		else if (hei>72 && hei<=100)
			p = 0.0313660825*exp(-0.165*(hei-72));
		else
			p = 0;
	
		// Temperature in Kelvin
		if (hei>=0 && hei<=17)
			T = 300.4222 - 6.3533*hei + 0.005886*hei*hei;
		else if (hei>17 && hei<=47)
			T = 194 + 2.533*(hei-17);
		else if (hei>47 && hei<=52)
			T = 270;
		else if (hei>52 && hei<=80)
			T = 270 - 3.0714*(hei-52);
		else if (hei>80 && hei<=100)
			T = 184;
		else
			T = 0;

		// absolute humidity in g/m^3
		if (hei>=0 && hei<=15)
			ro = 19.6542*exp(-0.2313*hei-0.1122*hei*hei + 0.01351*hei*hei*hei - 0.0005923*hei*hei*hei*hei);
		else
			ro = 0;
	}

    if (atmos.Compare("ITU-R REF STD (default)")==0)
	{
		// Pressure in hPa
		if (hei>=0 && hei<=11)
			p = 1013.25*pow(288.15/(288.15-6.5*hei),34.163/(-6.5));
		else if (hei>11 && hei<=20)
			p = 226.3226*exp((-34.163*(hei-11))/216.65);
		else if (hei>20 && hei<=32)
			p = 54.7498*pow(216.65/(216.65+hei-20), 34.163);
		else if (hei>32 && hei <=47)
			p = 8.6804*pow(228.65/(228.65+(2.8)*(hei-32)), 34.163/(2.8));
		else if (hei>47 && hei<=51)
			p = 1.1091*exp((-34.163*(hei-47))/270.65);
		else if (hei>51 && hei<=71)
			p = 0.6694*pow(270.65/(270.65+(-2.8)*(hei-51)), 34.163/(-2.8));
		else if (hei>71 && hei<=100)
			p = 0.0396*pow(214.65/(214.65+(-2.0)*(hei-71)), 34.163/(-2.0));
		else
			p = 0;

		// Temperature in Kelvin
		if (hei>=0 && hei<=11)
			T = 288.15 + (-6.5)*(hei);
		else if (hei>11 && hei<=20)
			T = 216.65;
		else if (hei>20 && hei<=32)
			T = 216.65 + (hei-20);
		else if (hei>32 && hei <=47)
			T = 228.65 + 2.8*(hei-32);
		else if (hei>47 && hei<=51)
			T = 270.65;
		else if (hei>51 && hei<=71)
			T = 270.65 - 2.8*(hei-51);
		else if (hei>71 && hei<=100)
			T = 214.65 - 2.0*(hei-71);
		else
			T = 0;

		// absolute humidity in g/m^3
		if (hei>100)
			ro = 0;
		else
		{
			ro = 7.5*exp(-0.5*hei);
			double mix = (ro*T/216.7)/p;
			if (mix<2.0e-6)
			{
				double e = 2.0e-6*p;
				ro = e*216.7/T;
			}
		}
	}
	*P1 = p;
	*T1 = T;
	*RHO1 = ro;
}

double CP530_Functions::AtmosphericAbsorbtion(CString Climate,double FrqMHzL,double LOSDist,double h1,double h2)
{
	double  GammaL,LAGasLoss;
	double p,T,ro;
	double	AvgH = (0.0005*(h1 + h2));

	StandardAtmosphers(Climate, AvgH, &p, &T, &ro);
	GammaL = SpecificGasAbsorption(0.001*FrqMHzL, p, T, ro);

	LAGasLoss = GammaL*LOSDist;
	return LAGasLoss;
}

double	CP530_Functions::SpecificGasAbsorption(double f, double P, double T, double ro)
{
	FILE *File; 
	long i;
	double  y = 1;

	double Sio[44], Siw[30] , deltao[44], deltafo[44], deltafw[30],
			part1Fio[44], part2Fio[44], Fio[44], part1Fiw[30],
			part2Fiw[30], Fiw[30],	wat[210], oxy[308];

	CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\wat.txt");
	if ((File = fopen(FileInfo,"r"))==NULL)
	{
		AfxMessageBox(_Z("The file 'wat.txt' was not opened."));
		exit(0);
	}
	char bf[200];
	for (i=0; i<210; i++)
	{
		fscanf(File,"%s",&bf);	wat[i] = atof(bf);
	}
	fclose(File);	

	FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\oxy.txt");
	if ((File = fopen(FileInfo,"r"))==NULL)
	{
		AfxMessageBox(_Z("The file 'oxy.txt' was not opened."));
		exit(0);
	}
	for (i=0; i<308; i++)
	{
		fscanf(File,"%s",&bf);	oxy[i] = atof(bf);
	}
	fclose(File);	

	double theta = 300./T;
	double e = ro/(7.223*theta)*10;
	e = ro*T/216.7;
	double p = P - e;

	// Dry air continuum N2Df ( N''D(f) )
	double d = 5.6e-4*(p+1.1*e)*theta;
	double N2Df = f*p*pow(theta, 2)*(6.14*1e-5)/(d*(1+pow(f/d,2)))+1.4e-12*(1-1.2e-5*pow(f, 1.5))*pow(p, 2)*f*pow(theta, 3.5);
	double N2Wf = f*(3.57*pow(theta,7.5)*e+0.113*p)*1.0e-7*e*pow(theta, 3);

	double sFio = 0, sFiw = 0;

	for( i=0;i<44;i++)
	{
		Sio[i] =  (oxy[i]*( 1e-7*pow(theta,3.0)*p ))*(exp((oxy[i+44]*(1-theta))));

		deltao[i] = (oxy[i+4*44] + oxy[i+5*44]*theta)*((1e-4)*p*pow(theta, 0.8));
		deltafo[i] = (oxy[i+2*44]*1e-4)*((pow(theta,(-(oxy[i+3*44])+0.8)))*p+1.1*e*theta);
		part1Fio[i] = (deltafo[i] - (deltao[i]*(oxy[i+6*44] - f))) / ((  (oxy[i+6*44]-f)*(oxy[i+6*44]-f)   ) + (   deltafo[i]*deltafo[i]   ));
		part2Fio[i] = (deltafo[i] - (deltao[i]*(oxy[i+6*44] + f))) / ((  (oxy[i+6*44]+f)*(oxy[i+6*44]+f)   ) + (   deltafo[i]*deltafo[i]   ));
		Fio[i] = ((    1.0/(oxy[i+6*44])   )*f) * (part1Fio[i] + part2Fio[i]);

		sFio = sFio + Fio[i]*Sio[i];

	}
	for( i=0;i<30;i++)
	{
		Siw[i] =  (wat[i]*( 1e-1*pow(theta,3.5)*e ))*(exp((wat[i+30]*(1-theta))));

		deltafw[i] = (wat[i+2*30]*1e-4)*(((pow(theta, (wat[i+3*30])))*p) + ((wat[i+4*30]*e)*(pow(theta, (wat[i+5*30])))));
		part1Fiw[i] = deltafw[i]/((    (wat[i+6*30]-f)*(wat[i+6*30]-f)     ) + (   deltafw[i]*deltafw[i]   ));
		part2Fiw[i] = deltafw[i]/((    (wat[i+6*30]-f)*(wat[i+6*30]+f)     ) + (   deltafw[i]*deltafw[i]   ));
		Fiw[i] = ((      1.0/(wat[i+6*30])     )*f) * (part1Fiw[i] + part2Fiw[i]);

		sFiw = sFiw + Fiw[i]*Siw[i];
	}

	double N2f = sFio+sFiw+N2Df+N2Wf;
	y = 0.1820*f*N2f;       // eq. 1 from P.676-5	

	return y;
 }

double CP530_Functions::RainIntensityAtP(double Longitude, double Latitude, double Probability)
{
	double  MyMs, MyMc, MyPr6,	P0, a, b, c, AA, BB, CC,RainRate = 12;

	MsMcPr6(Longitude, Latitude, &MyMs, &MyMc, &MyPr6);

	P0 = MyPr6*(1.0-exp(-0.0117*(MyMs/MyPr6)));
	
    a  = 1.11;
    b  = (MyMc + MyMs)/(22932.*P0);
    c  = 31.5*b;
    AA = a*b;
    BB = a + c*log(Probability/P0);
    CC = log(Probability/P0);
    RainRate = (-BB + sqrt(BB*BB-4.0*AA*CC))/(2.0*AA);

	return RainRate;
}
void CP530_Functions::MsMcPr6(double Longitude, double Latitude, double *MyMs, double *MyMc, double *MyPr6)
{
	// loading information from files
	// Pr6, Mc, Ms: parameters of rain distribution
	// P. 837
	double Ms, Mc, Pr6;

	CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\Ms.dat");
	if( dat_files(Latitude,Longitude,FileInfo,&Ms)==0)
	{
		AfxMessageBox(_Z("The file 'Ms.dat' was not opened."));
		exit(0);
	}
	*MyMs = Ms;
	FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\Mc.dat");
	if( dat_files(Latitude,Longitude,FileInfo,&Mc)==0)
	{
		AfxMessageBox(_Z("The file 'Mc.dat' was not opened."));
		exit(0);
	}
	*MyMc = Mc;
	FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\Pr6.dat");
	if( dat_files(Latitude,Longitude,FileInfo,&Pr6)==0)
	{
		AfxMessageBox(_Z("The file 'Pr6.dat' was not opened."));
		exit(0);
	}
	*MyPr6 = Pr6;
}

double CP530_Functions::SpecificRainAttenuation(double r, double theta, double tau, double freq)
{
	double  
		freq_int[31] = {1,         1.5,       2,         2.5,       3,         4,         5,         6,         7,         8,        9,        10,       12,       15,      20,      25,     30,     35,     40,     45,     50,     60,     70,     80,     90,     100,    120,    150,    200,    300,    400},
		     kh [31] = {0.0000387, 0.0000868, 0.0001543, 0.0002416, 0.0003504, 0.0006479, 0.0011030, 0.0018130, 0.0029150, 0.004567, 0.006916, 0.010060, 0.018820, 0.03689, 0.07504, 0.1237, 0.1864, 0.2632, 0.3504, 0.4426, 0.5346, 0.7039, 0.8440, 0.9552, 1.0432, 1.1142, 1.2218, 1.3293, 1.4126, 1.3737, 1.3163},
			 kv [31] = {0.0000352, 0.0000784, 0.0001388, 0.0002169, 0.0003145, 0.0005807, 0.0009829, 0.0016030, 0.0026500, 0.003996, 0.006056, 0.008853, 0.016800, 0.03362, 0.06898, 0.1125, 0.1673, 0.2341, 0.3104, 0.3922, 0.4755, 0.6347, 0.7735, 0.8888, 0.9832, 1.0603, 1.1766, 1.2886, 1.3764, 1.3665, 1.3059},
			 ah [31] = {0.9122,    0.9341,    0.9629,    0.9873,    1.0185,    1.1212,    1.2338,    1.3068,    1.3334,    1.3275,   1.3044,   1.2747,   1.2168,   1.1549,  1.0995,  1.0604, 1.0202, 0.9789, 0.9394, 0.9040, 0.8735, 0.8266, 0.7943, 0.7719, 0.7557, 0.7434, 0.7255, 0.7080, 0.6930, 0.6862, 0.6840},
			 av [31] = {0.8801,    0.8905,    0.9230,    0.9594,    0.9927,    1.0749,    1.1805,    1.2662,    1.3086,    1.3129,   1.2937,   1.2636,   1.1994,   1.1275,  1.0663,  1.0308, 0.9974, 0.9630, 0.9293, 0.8981, 0.8705, 0.8263, 0.7948, 0.7723, 0.7558, 0.7434, 0.7257, 0.7091, 0.6948, 0.6869, 0.6849},
			 thetar, taur, k, a, y[31], pi = 4.0*atan(1.0);
	
	thetar = theta * pi/180.0;  taur = tau * pi/180.0;
	if (freq <1)
	{
//		MessageBox(_Z("Precipitation Attenuation for Frequencies less than 1GHz is ignorable"), "Hint", MB_ICONERROR | MB_OK);
		return 0;
//		return -1;
	}
	if (freq >400)
	{
		AfxMessageBox(_Z("No method for Calculation of Precipitation Attenuation for Frequencies greater than 400GHz."));
		return 0;
//		return -1;
	}

	for (long f=0; f<31; f++)
	{
	    k = (kh[f] + kv[f] + (kh[f] - kv[f]) * pow(cos(thetar),2.0) * cos(2.0*taur)) / 2.0;
	    a = (kh[f]*ah[f]+kv[f]*av[f]+(kh[f]*ah[f]-kv[f]*av[f])*pow(cos(thetar),2.0)*cos(2.0*taur))/(2.0*k);
	    y[f] = k*pow(r,a);
	}

	return Interp1(freq_int, y, freq, 31);
}

void CP530_Functions::RainAttenuation(double FrqMHzL, double h1, double h2, double LOSDist,CString PolL,double AnEx, double LatM,double LongM,double *RainAttnL,double *RainFadeML,double *A0dot01L0)
{
	double PathElevation, tau, gamma_rL, d0, r, p, pp, ApLeftToRight, frq1 = FrqMHzL;

	if ((frq1 > 400000))
	{
		AfxMessageBox(_Z("Out of frequency range supported by ITU-R Rec. P.838-2 refered in P.530-10, for rain attenuation calculation. The frequencies are going to be set 400 GHz in this case"));
		frq1 = 400000;
	}
	double RainRate = RainIntensityAtP(LongM, LatM, 0.01);
	
	PathElevation = fabs(h1-h2)/(LOSDist*1000.0);	// Path elevation angle	in radians
	double pi = 4.0*atan(1.0);
	tau = (PolL.Compare("V")==0) ? 90 : 0;
	gamma_rL = SpecificRainAttenuation(RainRate, PathElevation*180.0/pi, tau, 0.001*frq1); // specific rain attenuation in dB/km,  step 2

	d0 = (RainRate <= 100) ? (35.0*exp(-0.015*RainRate)) : (35.0*exp(-1.5));	// step 3
	r = 1./(1. + LOSDist/d0);					 // r is the distance factor

	double A0dot01L = gamma_rL*r*LOSDist;		 // step 4, the path attenuation exceeded for 0.01% of the time
	*A0dot01L0 = A0dot01L;

	double a1,a2,a3;
	if (fabs(LatM)>=30)
	{
		a1 = 0.12, a2 = 0.546, a3 = 0.043;	// step 5, the attenuation exceeded for other percentages of time p in the range 0.001% to 1% 
	}
	else
	{
		a1 = 0.07, a2 = 0.855, a3 = 0.139;	// step 6, the attenuation exceeded for other percentages of time p in the range 0.001% to 1% 
	}

	p = AnEx;
	pp = p;
	if (p==0.01)
		ApLeftToRight = A0dot01L;
	else
	{
		if ((p>=0.001) && (p<=1))
			pp = p;
		else
		{
			AfxMessageBox(_Z("The ITU-R P.530-10 could calculate the attenuation exceeded for time percentages higher than one percent and no less than 0.001. So,  here, the Rain Attenuation is going to be calculated for 99% or 99.999%."));
			if (p<0.001)
				pp = 0.001;
			else  // for p>1 %
				pp = 1;
		}
		ApLeftToRight = A0dot01L*a1*pow(pp, -(a2+a3*log10(pp)));
	}
	*RainAttnL = ApLeftToRight;
	*RainFadeML = ApLeftToRight;
}

void CP530_Functions::A_from_pw(double AnEx,double LOSDist,double FrqMHzL,double h1,double h2,double mK, double LatM,double *RXClearAirFadingR)
{
	double Pw, p0, p = AnEx , frq1 = FrqMHzL;
	double ep, DeltaG, At, Aa, pt, qap, qt, LAa, A0, A[201], qa[201], pw[201];

	if ((FrqMHzL>45000)||(FrqMHzL<(15000.0/LOSDist)))
	{
		AfxMessageBox(_Z("Out of frequency range applicable for P.530-10, due to conditions of equations (7) and (8) mentioned in the section 2.3.1. The lowest/highest possible frequencies are going to be used in this step!"));
		frq1 = max(min(frq1,45000.0),15000.0/LOSDist);
	}
	ep = fabs((h2-h1)/LOSDist);				// path inclination in miliradian
	DeltaG = An2WorstMonthConvertor(LatM,LOSDist,h1,h2);

	Pw = pow(10, (DeltaG/10))*p;			// conversion from average year to the Worst month
	p0 = PathP0(frq1,LOSDist,h1,h2,mK);

	At = (log10(p0)*1.2) + 25.0;			// fade depth, At, at which the transition occurs between the deep fading distribution and the shallow-fading distribution
    Aa = log10(p0/Pw)*10.0;					// Aa is the fade depth corresponding to the Pw % of time of the worst month

	pt = pow(10, -(At*0.1))*p0;
	qap = log10(-log((-pt+100)/100))*(-20)/At;
	qt  =  ((qap-2.0)/( ( pow(10, (-At/20))*.3+1 ) * pow(10, (-(At*0.016))) )) - (pow(10., (-At/20))+(At/800))*4.3;
	
	for(int i=0;i<201;i++)
	{
		A[i] = i;
		qa[i] = ((((pow(10.,-(A[i]/20.)))*0.3) + 1.)*(pow(10., (-(A[i]*0.016))))*(qt+((pow(10., -(A[i]/20.))+(A[i]/800.))*4.3))) + 2.;
		pw[i] = (-exp(-(pow(10., -(qa[i]*(A[i]/20.)))))+1.)*100.;
	}
	LAa = Interp1I(pw,A,Pw,201);
	LAa = LAa*(Aa< At);
	A0 = LAa+(Aa*(Aa>=At));

	*RXClearAirFadingR = A0;
}


double CP530_Functions::Preparation(  double LatM,double LongM,double Sa)
{
	double dN1;
	CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\DNDZ_01.dat");
	if( dat_files(LatM,LongM,FileInfo,&dN1)==0)
	{
		AfxMessageBox(_Z("The file 'dndz_01.dat' was not opened."));
		exit(0);
	}
	// calculation of equation (4), (6) and (7) in ITU-R P.530-10, step 1 to 3 of 2.3.1
	double mK = pow(10.0, (-3.9-0.003*dN1))*pow(Sa,-0.42);
	return mK;
}

int CP530_Functions::dat_files(double LatM,double LongM,CString dat_fname,double *hy)
{
	FILE *fp;
	float  data[121][241];
	if ((fp = fopen(dat_fname,"rb"))==NULL)
	return 0;

	fread( data,sizeof(float),121*241, fp );	
	fclose(fp);

	double x,y,h11,h12,h21,h22,hx1,hx2,LongM1;
	int i1,i2,j1,j2;
	LongM1 = LongM + 360.0*(LongM<0);

	x = LongM1/1.5;			y = (90.0-LatM)/1.5;
/*
	i1 = int(x);			j1 = int(y);
	i2 = i1+1;				j2 = j1+1;
	h11 = data[i1][j1];		h12 = data[i1][j2];
	h21 = data[i2][j1];		h22 = data[i2][j2];
	hx1 = h11 +(x-i1)*(h21-h11)/(i2-i1);
	hx2 = h12 +(x-i1)*(h22-h12)/(i2-i1);
	*hy = hx1 +(y-j1)*(hx2-hx1)/(j2-j1);
*/
	j1 = int(x);			i1 = int(y);
	i2 = i1+1;				j2 = j1+1;
	h11 = data[i1][j1];		h12 = data[i1][j2];
	h21 = data[i2][j1];		h22 = data[i2][j2];
	hx1 = h21 +(x-j1)*(h22-h21)/(j2-j1);
	hx2 = h11 +(x-j1)*(h12-h11)/(j2-j1);
	*hy = hx2 +(y-i1)*(hx1-hx2)/(i2-i1);

	return 1;
}

double CP530_Functions::PathP0(double frq,double LOSDist,double h1,double h2,double mK)
{
	double ep = fabs((h2-h1)/LOSDist);		// path inclination in miliradian
	double p0 = pow(10.0,((frq*0.000032)-(min(h1,h2)*0.00085)))*(mK*pow(LOSDist, 3.2)*pow((1+ep),-0.97)); // equation (10) as step 1
	return p0;
}

double CP530_Functions::An2WorstMonthConvertor(double LatM,double LOSDist,double h1,double h2)
{
	double ep = fabs((h2-h1)/LOSDist);		// path inclination in miliradian
	double DeltaG;

	if (LatM <45.0)
		DeltaG = 10.5-5.6*log10(1.1 + pow(fabs(cos(2*LatM)), 0.7))-2.7*log10(LOSDist) + 1.7*log10(1.0+ep);
	else
		DeltaG = 10.5-5.6*log10(1.1 - pow(fabs(cos(2*LatM)), 0.7))-2.7*log10(LOSDist) + 1.7*log10(1.0+ep);
	
	return DeltaG;
}


void CP530_Functions::RainOutage(double LatM,double RainFadeMargin,double A0dot01L2R,double *RainAnEx1,double *RainWorstMonthEx)
{
	double  Q1, Q, p, beta, RainAnEx;

	if (RainFadeMargin <0)
		RainAnEx = 100;
	else
	{
		double pp[2000], yy[2000] , yymax = -99999999.0;

		for(int i=0 ; i<2000 ; i++)
		{
			pp[i] = 1e-5 + i*5e-4;
			if (fabs(LatM)>=30.0)
				yy[i] = (pow(pp[i] , (-((log10(pp[i])*0.043)+0.546))) )*(A0dot01L2R*0.12);
			else
				yy[i] = (pow(pp[i] , (-((log10(pp[i])*0.139)+0.855))) )*(A0dot01L2R*0.07);
			yymax = max(yymax,yy[i]);
		}
		if (RainFadeMargin > yymax)
			RainAnEx = 0;	// Less than 1e-3 Exceedance probability
		else
			RainAnEx = Interp1I(yy, pp, RainFadeMargin,2000);
	}
	*RainAnEx1 = RainAnEx;

    Q1 = 2.85;	beta = 0.13;
	p  = RainAnEx;
    if (p < pow(Q1/12.0, 1.0/beta))
        Q = 12.0;
    else
	{
		if ((p >=pow(Q1/12.0, 1.0/beta)) && (p<3.0))
			Q = Q1*pow(p,-beta);
		else
		{
			if (p>=3 && p<30)
				Q = Q1*pow(3,-beta);
			else
			{
				if (p >=30)
					Q = Q1*pow(3,-beta)*pow(p/30,log10(Q1*pow(3, -beta))/log10(0.3));
			}
		}
	}
    // the average annual worst-month time percentage of excess
	*RainWorstMonthEx = Q*p;
}

void CP530_Functions::MultipathOutage(double FlatFadeMarginR,double p0,double An2WorstMonthC,double *MultipathAnEx,double *MultipathWorstMonthEx)
{
	double A, At;
	A = FlatFadeMarginR;		// Left to Right
	At  = 25.0 + 1.2*log10(p0);
	if(A>=At)
		*MultipathWorstMonthEx = p0*pow(10.0, -A/10.0) ;
	else
		*MultipathWorstMonthEx = 100.0*(1.0-exp(-pow(10.0, -(2.0+(1.0+0.3*(pow(10.0, -A/20.0)))*(pow(10.0, -0.016*A))*((((-20.0*log10(-log((100.0-p0*pow(10.0, -0.1*At))/100.0))/At)-2.0)/((1.0+0.3*(pow(10.0, -At/20.0)))*(pow(10.0, -0.016*At)))-4.3*((pow(10.0, -At/20.0))+At/800.0))+4.3*(pow(10.0, -A/20.0)+A/800.0)))*A/20.0)));
	*MultipathAnEx = (*MultipathWorstMonthEx)*pow(10.0,-An2WorstMonthC/10.0);
}
