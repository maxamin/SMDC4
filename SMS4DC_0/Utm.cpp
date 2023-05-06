// Utm.cpp: implementation of the CUtm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS4DC.h"
#include "Utm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtm::CUtm()
{
	x=0.0;
	y=0.0;
	phi=0.0;
	lambda=0.0;
	pi=4.0*atan(1.0);
	a = 6378206.4;
	e = 0.0822719;
	phi0 = (24.0 * pi) / 180.0;
    l0 =   (54.0 * pi) / 180.0;
	phi1 = (30.0 * pi) / 180.0;
	phi2 = (36.0 * pi) / 180.0;

}

CUtm::~CUtm()
{

}



double CUtm::FPhi(double pOld,double t)
{
	double pNew = pi/2.0 - 2.0* atan( t* pow(((1.0 - e * sin(pOld)) / (1.0 + e * sin(pOld))) , (e / 2.0)) );
	if (pOld != pNew)
		pNew = FPhi(pNew,t);
	
	return pNew;
}

int CUtm::sign(double t)
{
   //return (   (t==0.0) ? 0 : (int)(t/abs(t))  );

   if (t>0.0)		return 1;
   else if (t<0.0)	return -1;
   else			    return 0;
}



void CUtm::UTM2philambda()
{
/*
	double m1 = cos(phi1) / sqrt( 1.0 - pow(e * sin(phi1),2.0) );
	double m2 = cos(phi2) / sqrt( 1.0 - pow(e * sin(phi2),2.0) );
	double t0 = tan(pi / 4.0 - phi0 / 2.0) / pow( ((1.0 - e * sin(phi0)) / (1.0 + e * sin(phi0))) , (e / 2.0) );
	double t1 = tan(pi / 4.0 - phi1 / 2.0) / pow( ((1.0 - e * sin(phi1)) / (1.0 + e * sin(phi1))) , (e / 2.0) );
	double t2 = tan(pi / 4.0 - phi2 / 2.0) / pow( ((1.0 - e * sin(phi2)) / (1.0 + e * sin(phi2))) , (e / 2.0) );
	double n = log(m1 / m2) / log(t1 / t2);
	double F = m1 / (n * pow(t1 , n));
	double r0 = a * F * pow(t0 , n);

	double r = sign(n) * sqrt((x*x + (r0 - y)*(r0 - y)));
	double t = pow(r / (a * F),1.0 / n);
	phi = FPhi((pi / 2.0 - 2.0 * atan(t)),t) * 180.0 / pi;
    
	double teta = (180.0/pi) * atan(x / (r0 - y)) ;
	lambda = ((l0 * 180.0 / pi) + teta / n);
*/
	phi = y;
	lambda = x;
}

void CUtm::philambda2UTM()
{
/*
	double phi_rad = (phi * pi) / 180.0;
	double lambda_rad = (lambda * pi) / 180.0;

	double m1 = cos(phi1) / sqrt( 1.0 - pow(e * sin(phi1),2.0) );
	double m2 = cos(phi2) / sqrt( 1.0 - pow(e * sin(phi2),2.0) );
	double t = tan(pi / 4.0 - phi_rad / 2.0) / pow( ((1.0 - e * sin(phi_rad)) / (1.0 + e * sin(phi_rad))) , (e / 2.0) );
	double t0 = tan(pi / 4.0 - phi0 / 2.0) / pow( ((1.0 - e * sin(phi0)) / (1.0 + e * sin(phi0))) , (e / 2.0) );
	double t1 = tan(pi / 4.0 - phi1 / 2.0) / pow( ((1.0 - e * sin(phi1)) / (1.0 + e * sin(phi1))) , (e / 2.0) );
	double t2 = tan(pi / 4.0 - phi2 / 2.0) / pow( ((1.0 - e * sin(phi2)) / (1.0 + e * sin(phi2))) , (e / 2.0) );

	double n = log(m1 / m2) / log(t1 / t2);
	double F = m1 / (n * pow(t1 , n));
	double r = a * F * pow(t , n);
	double r0 = a * F * pow(t0 , n);

	double teta=n*(lambda_rad-l0);
	
	x=r*sin(teta);
	y=r0-r*cos(teta);
*/
	y = phi;
	x = lambda;
}