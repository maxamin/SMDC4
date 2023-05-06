// P370_Functions.h: interface for the CP370_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P370_FUNCTIONS_H__EB9E9422_B677_4ECF_90A9_94DD9D75DF38__INCLUDED_)
#define AFX_P370_FUNCTIONS_H__EB9E9422_B677_4ECF_90A9_94DD9D75DF38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

class CP370_Functions  
{
public:
	CP370_Functions();
	virtual ~CP370_Functions();


private:
	double Interp1(double *D0,double *E0,double d,int num); 
	double Interp2(double *D0,double *E0,double d,int num); 
	double P370_0(double f,double t,int p,double h1,double d_km,double *Ebfs);
	double P370_1(double f,double t,int p,double h1,double d_km,double *Ebfs); 
	double P370_2(double f,double t,int p,double h1,double d_km,double tetamax15,double *Ebfs); 
	double P370_3(double f,double t,int p,double h1,double d_km,double tetamax15,double h2,int ENV,double *Ebfs) ;
	double P370_4(double f,double t,int p,double h1,double d_km,
						 double tetamax15,double h2,int ENV,double Lp,int syst,double *Ebfs) ;
	double P370_5(double f,double t,int p,double h1,double d_km,
						 double tetamax15,double h2,int ENV,double Lp,int syst,double *Ebfs) ;
	double P370_6(double f,double t,int p,double h1,double d_km,
						 double tetamax15,double h2,int ENV,double Lp,int syst,double ttca,double *Ebfs) ;

	void F370_1A(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_2A(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_3A(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_4A(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_1B(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_2B(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_3B(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_4B(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_2C(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_3C(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_4C(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_9(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_10(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_11(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_13(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_14A(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_15A(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_16A(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_14B(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_15B(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F370_16B(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;

	double zTCAcorr370_0(double Tdeg,double f_MHz);
	double TCAcorr370(double Tdeg,double f_MHz);
	double zdelta_h_cr(double f,double d,double dh);
	double zdelta_h_cr_1(double f,double di,double dh);
	double zdelta_h_cr_2(double f,double d,double dh);
	double Qi(double x);
/*
	double P370_0I(double f,double t,int p,double h1,double E) ;
	double P370_1I(double f,double t,int p,double h1,double E) ;
	double P370_2I(double f,double t,int p,double h1,double E,
							 double tetamax15) ;
	double P370_3I(double f,double t,int p,double h1,double E,
							 double tetamax15,double h2,int ENV) ;
	double P370_4I(double f,double t,int p,double h1,double E,
							 double tetamax15,double h2,int ENV,double Lp,int syst) ;
	double P370_5I(double f,double t,int p,double h1,double E,
							 double tetamax15,double h2,int ENV,double Lp,int syst) ;
	double P370_6I(double f,double t,int p,double h1,double E,
							 double tetamax15,double h2,int ENV,double Lp,int syst,double ttca); 
*/
	double P370_0I(double f,double t,int p,double h1,double E,double Delta_H = 50.0) ;
	double P370_1I(double f,double t,int p,double h1,double E,double Delta_H = 50.0) ;
	double P370_2I(double f,double t,int p,double h1,double E,
							 double tetamax15,double Delta_H = 50.0) ;
	double P370_3I(double f,double t,int p,double h1,double E,
							 double tetamax15,double h2,int ENV,double Delta_H = 50.0) ;
	double P370_4I(double f,double t,int p,double h1,double E,
							 double tetamax15,double h2,int ENV,double Lp,int syst,double Delta_H = 50.0) ;
	double P370_5I(double f,double t,int p,double h1,double E,
							 double tetamax15,double h2,int ENV,double Lp,int syst,double Delta_H = 50.0) ;
	double Interp1I(double *E0,double *D0,double E,int num) ;

public:
	double P370_7(double f,double t,int p,double h1,double d_km,
						 double tetamax15,double h2,int ENV,double Lp,int syst,double ttca,double *Ebfs) ;
//	double P370_7I(double f,double t,int p,double h1,double E,
//						 double tetamax15,double h2,int ENV,double Lp,int syst,double ttca);

	double P370_7I(double f,double t,int p,double h1,double E,
							 double tetamax15,double h2,int ENV,double Lp,int syst,double Delta_H = 50.0);
	double  Delta_H_cr(double f,double d,double dh);
};

#endif // !defined(AFX_P370_FUNCTIONS_H__EB9E9422_B677_4ECF_90A9_94DD9D75DF38__INCLUDED_)
