// ST61_Functions.h: interface for the CST61_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ST61_FUNCTIONS_H__DBCA1993_BEF2_4DDC_950A_42CFC2565C33__INCLUDED_)
#define AFX_ST61_FUNCTIONS_H__DBCA1993_BEF2_4DDC_950A_42CFC2565C33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CST61_Functions  
{
public:
	CST61_Functions();
	virtual ~CST61_Functions();

	double ST61(double f_MHz, double Perp, int p, double h1,double per1=100) ;
BOOL CTRY_Check(CString str);

protected:
	double TABLE_A_BAND_I(double Perp, int p, double h1) ;
	double TABLE_B_BAND_II(double Perp, int p, double h1) ;
	double TABLE_C_BAND_III(double Perp, int p, double h1) ;
	double TABLE_D1_BAND_IV(double Perp, int p,double per1) ;
	double TABLE_D1_BAND_V(double Perp, int p,double per1) ;
	double TABLE_D2_BAND_IV(double Perp, int p,double per1) ;
	double TABLE_D2_BAND_V(double Perp, int p,double per1) ;
	double TABLE_D3_BAND_IV(double Perp, int p,double per1) ;
	double TABLE_D3_BAND_V(double Perp, int p,double per1) ;
	double Interp1(double *D0,double *E0,double d,int num) ;

};

#endif // !defined(AFX_ST61_FUNCTIONS_H__DBCA1993_BEF2_4DDC_950A_42CFC2565C33__INCLUDED_)
