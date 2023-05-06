// HATA_Functions.cpp: implementation of the CHATA_Functions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS4DC.h"
#include "HATA_Functions.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHATA_Functions::CHATA_Functions()
{

}

CHATA_Functions::~CHATA_Functions()
{

}

double CHATA_Functions::E_HATA(double a1,double a2,double a3,double b1,double b2,
						  double f,double h1,double d,double h2,int ENV,double tetamax15) 
{
	h2 = max(h2,1.0);
	double Eb;

	if ((f>=150.0) && (f<=2000.0))
		Eb = E02(a1,a2,a3,b1,b2,f,h1,d,min(h2,10.0),ENV,tetamax15) + 20.0*log10(max(h2,10.0)/10.0);
	else if (f<150.0)
	{
		double finf,fsup,Ebinf,Ebsup;
		finf=150.0;		fsup=250.0;

		Ebinf = E02(a1,a2,a3,b1,b2,finf,h1,d,min(h2,10.0),ENV,tetamax15) + 20.0*log10(max(h2,10.0)/10.0);
		Ebsup = E02(a1,a2,a3,b1,b2,fsup,h1,d,min(h2,10.0),ENV,tetamax15) + 20.0*log10(max(h2,10.0)/10.0);
		Eb=Ebinf+(Ebsup-Ebinf)*log10(f/finf)/log10(fsup/finf);
	}   
	else if (f>2000.0)
	{
		double finf,fsup,Ebinf,Ebsup;
		finf=1500.0;	fsup=2000.0;

		Ebinf = E02(a1,a2,a3,b1,b2,finf,h1,d,min(h2,10.0),ENV,tetamax15) + 20.0*log10(max(h2,10.0)/10.0);
		Ebsup = E02(a1,a2,a3,b1,b2,fsup,h1,d,min(h2,10.0),ENV,tetamax15) + 20.0*log10(max(h2,10.0)/10.0);
		Eb=Ebinf+(Ebsup-Ebinf)*log10(f/finf)/log10(fsup/finf);
	}   
	double Ebfs = 106.9 - 20.0*log10(d);
	return ( min(Eb,Ebfs) );
}

/*
double CHATA_Functions::E_HATA(double a1,double a2,double a3,double b1,double b2,
						  double f,double h1,double d,double h2,int ENV,double tetamax15) 
{
	h2 = max(h2,1.0);
	double Eb = E02(a1,a2,a3,b1,b2,f,h1,d,min(h2,10.0),ENV,tetamax15) + 20.0*log10(max(h2,10.0)/10.0);
	double Ebfs = 106.9 - 20.0*log10(d);
	return ( min(Eb,Ebfs) );
}
*/

double CHATA_Functions::E02(double a1,double a2,double a3,double b1,double b2,
						  double f,double h1,double d,double h2,int ENV,double tetamax15) 
{
	double Eb,h1inf=30.0,h1sup=300.0;

	if ( (h1>=h1inf) && (h1<=h1sup) )
		Eb = E01(a1,a2,a3,b1,b2,f,h1,d,h2,ENV) ;
	else if ( (h1>=0.0) && (h1<h1inf) )
	{
		double dh1=4.1*sqrt(h1);
		if (d<dh1)
			Eb = E01(a1,a2,a3,b1,b2,f,h1inf,d,h2,ENV) - 
				 E01(a1,a2,a3,b1,b2,f,h1inf,dh1,h2,ENV) + 
				 E01(a1,a2,a3,b1,b2,f,h1inf,4.1*sqrt(h1inf),h2,ENV);
		else
			Eb = E01(a1,a2,a3,b1,b2,f,h1inf,d + 4.1*sqrt(h1inf) - dh1,h2,ENV) ;
	}
	else if ( (h1>h1sup) )
	{
		double dh1=4.1*sqrt(h1);
		if (d<dh1)
			Eb = E01(a1,a2,a3,b1,b2,f,h1sup,d,h2,ENV) - 
				 E01(a1,a2,a3,b1,b2,f,h1sup,dh1,h2,ENV) + 
				 E01(a1,a2,a3,b1,b2,f,h1sup,4.1*sqrt(h1sup),h2,ENV);
		else
			Eb = E01(a1,a2,a3,b1,b2,f,h1sup,d + 4.1*sqrt(h1sup) - dh1,h2,ENV) ;
	}
	else if ( (h1<0.0) )
		Eb = E02(a1,a2,a3,b1,b2,f,0.0,d,h2,ENV,tetamax15) + TCAcorr370(tetamax15,f);

	double Ebfs = 106.9 - 20.0*log10(d);
	return ( min(Eb,Ebfs) );
}


double CHATA_Functions::TCAcorr370(double Tdeg,double f_MHz)
{

	double LinDown,LimUP,Corr,Tdeginf,Tdegsup,Corrinf,Corrsup;


	if ( (f_MHz>=30.0) && (f_MHz<=300.0) )          // VHF
	{
		LinDown=-32.0;
        LimUP=30.0;
	}
	else if ( (f_MHz>300.0) && (f_MHz<=3000.0) )    // UHF
	{
		LinDown=-34.0;
        LimUP=40.0;
	}

	
	if (Tdeg<-40.0)								//-------------(Tdeg<-40)------------
		Corr=LinDown;
	
	else if ( (Tdeg>=-40.0) && (Tdeg<-20.0) )	//-------(Tdeg>=-40 , Tdeg<-20)------
	{
		Tdeginf=-40.0;
		Tdegsup=-20.0;
		Corrinf=LinDown;
		Corrsup=zTCAcorr370_0(-20.0,f_MHz);
		Corr=Corrinf + (Tdeg - Tdeginf)*(Corrsup - Corrinf)/(Tdegsup - Tdeginf);
	}
	else if ( (Tdeg>=-20.0) && (Tdeg<0.8) )		//-------(Tdeg>=-20 , Tdeg<=0.8)-------
		Corr=zTCAcorr370_0(Tdeg,f_MHz);
	else if ( (Tdeg>=0.8) && (Tdeg<=1.5) )	    //-------(Tdeg>0.8 , Tdeg<=1.5)--------
	{
		Tdeginf=0.8;
		Tdegsup=1.5;
		Corrinf=zTCAcorr370_0(0.8,f_MHz);
		Corrsup=LimUP;
		Corr=Corrinf + (Tdeg - Tdeginf)*(Corrsup - Corrinf)/(Tdegsup - Tdeginf);
	}
	else if ( Tdeg>1.5 )					//---------------(Tdeg>1.5)-----------------
		Corr=LimUP;

	return Corr;
}

double CHATA_Functions::zTCAcorr370_0(double Tdeg,double f_MHz)
{
	// (Tdeg>=-20 & Tdeg<=0.8)
	double pi=3.14159265358979;
	double Trad=Tdeg*pi/180.0;
	double v,Jvp,v01,Corr;

	if ( (f_MHz>=30.0) && (f_MHz<=300.0) )          // VHF
	{
		v=-Trad*sqrt(4000.0*95.0/300.0);
		Jvp=8.1;
	}
	else if ( (f_MHz>300.0) && (f_MHz<=3000.0) )    // UHF
	{
		v=-Trad*sqrt(4000.0*650.0/300.0);
		Jvp=14.9;
	}
	v01=v-0.1;
	Corr=Jvp-(6.9+20.0*log10(sqrt(1.0+v01*v01)+v01));
	return Corr;
}


double CHATA_Functions::E01(double a1,double a2,double a3,double b1,double b2,
						  double f,double h1,double d,double h2,int ENV) 
{
	f = min(max(f,150.0),2000.0);
	h1 = min(max(h1,30.0),300.0);
	d=max(d,0.001);

	double L=0;
	switch (ENV)
	{
		case 0:
			L= L01(a1,a2,a3,b1,b2,f,h1,d) - L01_openarea( f );
			break;
		case 1:
			L= L01(a1,a2,a3,b1,b2,f,h1,d) - L01_suburban( f );
			break;
		case 2:
			L= L01(a1,a2,a3,b1,b2,f,h1,d) - L01_urban_Medium( f, h2 );
			break;
		case 3:
			L= L01(a1,a2,a3,b1,b2,f,h1,d) - L01_urban_Large( f, h2 );
			break;
	}
	return ( 139.37 - L + 20.0*log10(f) );
}

double CHATA_Functions::L01_urban_Large(double f,double h2) 
{
	double k1 = (f<300.0) ? 8.29 : 3.2;
	double k2 = (f<300.0) ? 1.54 : 11.75;
	double k3 = (f<300.0) ? -1.1 : -4.97;

	double k = log10(k2*h2);

	return (  k1*k*k + k3  );
}



double CHATA_Functions::L01_urban_Medium(double f,double h2) 
{
	return (  (1.1*log10(f)-0.7)*h2 - (1.56*log10(f)-0.8)  );
}

double CHATA_Functions::L01_suburban(double f) 
{
	return (  5.4 + 2.0*pow(log10(f/28.0),2.0)  );
}

double CHATA_Functions::L01_openarea(double f) 
{
	double k = log10(f);
	return (  4.78*k*k - 18.33*k + 40.94  );
}

double CHATA_Functions::L01(double a1,double a2,double a3,double b1,double b2,double f,double h1,double d) 
{
	double hp1=h1/sqrt(1.0+0.000007*h1*h1);
	double b = (d<=20.0) ? 1.0 : ( 1.0+(0.14+f*0.000187+hp1*0.00107)*pow(log10(d/20.0),0.8) );

	return ( a1+a2*log10(f)+a3*log10(h1) ) + ( b1+b2*log10(h1) )*(pow(log10(d),b));
}

