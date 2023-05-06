// P527_526_Functions.h: interface for the CP527_526_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P527_526_FUNCTIONS_H__689F8F74_1C72_49E5_B382_6F9BFC3576BB__INCLUDED_)
#define AFX_P527_526_FUNCTIONS_H__689F8F74_1C72_49E5_B382_6F9BFC3576BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CP527_526_Functions  
{
public:
	CP527_526_Functions();
	virtual ~CP527_526_Functions();


	double Lsmoot(int TerType,double Frq_MHz,double kf,int pol,double d_km,double h1_m,double h2_m);

protected:
	double Interp1(double *D0,double *E0,double d,int num) ;
	double G_Y(double K,double Y) ;


};

#endif // !defined(AFX_P527_526_FUNCTIONS_H__689F8F74_1C72_49E5_B382_6F9BFC3576BB__INCLUDED_)
