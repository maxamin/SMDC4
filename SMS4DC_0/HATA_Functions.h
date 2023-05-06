// HATA_Functions.h: interface for the CHATA_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HATA_FUNCTIONS_H__43D99B7D_0F5D_4242_BD35_299766D81340__INCLUDED_)
#define AFX_HATA_FUNCTIONS_H__43D99B7D_0F5D_4242_BD35_299766D81340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHATA_Functions  
{
public:
	CHATA_Functions();
	virtual ~CHATA_Functions();

private:
	double L01(double a1,double a2,double a3,double b1,double b2,double f,double h1,double d);
	double L01_openarea(double f);
	double L01_suburban(double f);
	double L01_urban_Medium(double f,double h2);
	double L01_urban_Large(double f,double h2);
	double E01(double a1,double a2,double a3,double b1,double b2,
					double f,double h1,double d,double h2,int ENV);
	double E02(double a1,double a2,double a3,double b1,double b2,
					double f,double h1,double d,double h2,int ENV,double tetamax15);

	double TCAcorr370(double Tdeg,double f_MHz);
	double zTCAcorr370_0(double Tdeg,double f_MHz);
public:
	double E_HATA(double a1,double a2,double a3,double b1,double b2,
					double f,double h1,double d,double h2,int ENV,double tetamax15);

};

#endif // !defined(AFX_HATA_FUNCTIONS_H__43D99B7D_0F5D_4242_BD35_299766D81340__INCLUDED_)
