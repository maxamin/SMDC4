// P1546_Functions.h: interface for the CP1546_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P1546_FUNCTIONS_H__27C450FC_AE24_41F7_A575_8023CF8CBD9B__INCLUDED_)
#define AFX_P1546_FUNCTIONS_H__27C450FC_AE24_41F7_A575_8023CF8CBD9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

class CP1546_Functions  
{
public:
	CP1546_Functions();
	virtual ~CP1546_Functions();

private:
	void Figure_1(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_2(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_3(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_4(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_5(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_6(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_7(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_8(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_9(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_10(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_11(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_12(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_13(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_14(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_15(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_16(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_17(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_18(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_19(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_20(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_21(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_22(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_23(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void Figure_24(double *E010,double *E020,double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;

	double P1546_0(double f,double t,int p,double h1,double d_km,double *Ebfs); 
	double P1546_1(double f,double t,int p,double h1,double d_km,double *Ebfs); 
	double P1546_1Land(double f,double t,int p,double h1,double d_km); 
	double P1546_1Sea(double f,double t,int p,double h1,double d_km); 
	double P1546_2(double f,double t,int p,double h1,double d_km,double *Ebfs); 
	double P1546_3(double f,double t,int p,double h1,double d_km,double tetamax15,double *Ebfs);
	double P1546_4(double f,double t,int p,double h1,double d_km,double tetamax15,double *Ebfs);
	double P1546_5(double f,double t,int p,double h1,double d_km,double tetamax15,double *Ebfs);
	double P1546_6(double f,double t,int p,double h1,double d_km,double tetamax15,double *Ebfs);
	double P1546_7(double f,double t,int p,double h1,double d_km,double h2,double R,double tetamax15,double *Ebfs);

	double Interp1(double *D0,double *E0,double d,int num); 
	double zD06(double f,double h1,double h2); 
	double TCAcorr1546(double Tdeg,double f_MHz); 
	double Qi(double x);

	double Interp1I(double *E0,double *D0,double E,int num) ;

public:
	double P1546_8(double f_MHz,double t,int p,double h1,double d_km,double h2,int ENV,double tetamax15,int srv,double L,double *Ebfs) ;
	double P1546_8I(double f_MHz,double t,int p,double h1,double E,double h2,int ENV,double tetamax15,int srv,double L) ;




};

#endif // !defined(AFX_P1546_FUNCTIONS_H__27C450FC_AE24_41F7_A575_8023CF8CBD9B__INCLUDED_)
