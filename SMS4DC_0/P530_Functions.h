// P530_Functions.h: interface for the CP530_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P530_FUNCTIONS_H__E96DC594_7586_409E_AA1C_4D813F8552AC__INCLUDED_)
#define AFX_P530_FUNCTIONS_H__E96DC594_7586_409E_AA1C_4D813F8552AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CP530_Functions  
{
public:
	CP530_Functions();
	virtual ~CP530_Functions();

	double Preparation( double LatM,double LongM,double Sa);

	void P530Attn(int iClimate,double AnAv,double LatM,double LongM ,double FrqMHzL, double h1, double h2,
								double LOSDist,CString PolL,double FZClearance,int Fresnelnum,double mK,
								double *RainAttnL,double *AtomGasLossL,double *DiffLoss,
								double *RXClearAirFadingR,
								double *RainFadeML,double *A0dot01L);

	void P530Outage(double LatM,double RainFadeML,double A0dot01L,
								double FrqMHz,double LOSDist,double h1,double h2,
								double FlatFadeMarginR,double mK,
								double *RainAnEx,double *RainWorstMonthEx,
								double *MultipathAnEx,double *MultipathWorstMonthEx) ;

protected:

	double Interp1(double *D0,double *E0,double d,int num) ;
	double Interp1I(double *E0,double *D0,double E,int num) ;

	double Diff_Loss(double FZClearance,int Fresnelnum) ;
	void StandardAtmosphers(CString atmos, double hei, double *P1, double *T1, double *RHO1);
	double AtmosphericAbsorbtion(CString Climate,double FrqMHzL,double LOSDist,double h1,double h2);
	double	SpecificGasAbsorption	(double f, double P, double T, double ro);
	double RainIntensityAtP(double Longitude, double Latitude, double Probability);
	double SpecificRainAttenuation(double r, double theta, double tau, double freq);
	void RainAttenuation(double FrqMHzL, double h1, double h2, double LOSDist,CString PolL,double AnEx, double LatM,double LongM,double *RainAttnL,double *RainFadeML,double *A0dot01L0);

	void A_from_pw(double AnEx,double LOSDist,double FrqMHzL,double h1,double h2,double mK, double LatM,double *RXClearAirFadingR);
	void MsMcPr6(double Longitude, double Latitude, double *MyMs, double *MyMc, double *MyPr6);

	double An2WorstMonthConvertor(double LatM,double LOSDist,double h1,double h2);
	double PathP0(double frq,double LOSDist,double h1,double h2,double mK);
	void RainOutage(double LatM,double RainFadeMargin,double A0dot01L2R,
									double *RainAnEx1,double *RainWorstMonthEx);
	void MultipathOutage(double FlatFadeMarginR,double p0,double An2WorstMonthC,
									double *MultipathAnEx,double *MultipathWorstMonthEx);

	int dat_files(double LatM,double LongM,CString dat_fname,double *hy);
	
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

#endif // !defined(AFX_P530_FUNCTIONS_H__E96DC594_7586_409E_AA1C_4D813F8552AC__INCLUDED_)
