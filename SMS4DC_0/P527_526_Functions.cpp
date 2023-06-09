// P527_526_Functions.cpp: implementation of the CP527_526_Functions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS4DC.h"
#include "P527_526_Functions.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP527_526_Functions::CP527_526_Functions()
{
}

CP527_526_Functions::~CP527_526_Functions()
{

}


double CP527_526_Functions::Lsmoot(int TerType,double Frq_MHz,double kf,int pol,double d_km,double h1_m,double h2_m)
{
//////////////////////////////////////////////// Conductivity  (S/m) ///////////////////////////////////////////////
	double aF_As[] = {0.01,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aAs[] = {5.0,5.0,6.21,7.1357,8.1994,9.4217,11.1312,12.4399,13.9025,15.1113,16.8879,33.8298,49.9189,57.3601,60.6384,64.1041,67.7678,69.6775,69.6775,71.641,71.641,73.6598};
	int aN_As = 22;

	double aF_Bs[] = {0.01,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aBs[] = {0.01,0.01,0.0104,0.0104,0.01131,0.01229,0.01336,0.014125,0.01452,0.01579,0.02603,0.03736,0.052148,0.06697,0.07484,0.088419,0.11043,0.12689,0.14581,0.39652,0.67232,1.0488,1.3468,1.6821,2.0433,2.3479,2.8521,3.1874,6.385,10.2408,12.099,13.5215,15.1113,15.5371,16.8879,16.8879,17.3638,17.8531,17.8531};
	int aN_Bs = 39;

	double aF_Cs[] = {0.01,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aCs[] = {0.003,0.003,0.003063,0.0033,0.0036,0.004044,0.004396,0.004647,0.0049,0.005194,0.009842,0.0167,0.0299, 0.04538, 0.06513,0.088, 0.11354,0.1379, 0.17712,0.6723,1.5912,2.6979,3.981,6.21,8.1994, 10.5294, 11.7674, 14.2943, 32.9027, 51.3256, 57.3601, 60.6384, 64.1041, 67.7678, 69.6775, 69.6775,71.641,71.641, 73.6598};
	int aN_Cs = 39;

	double aF_Ds[] = {0.01,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aDs[] = {0.001,0.001,0.001036,0.001095, 0.00119,0.001258,0.001368,0.001487,0.001529,0.0018,0.003826,0.0061,0.009, 0.01229, 0.01669, 0.02027,0.026032, 0.02991, 0.03343,0.1167,0.2472,0.4,0.5534,0.7725,0.965,1.14,1.3468,1.636,4.2085,7.3368, 10.2408, 11.7674, 14.2943, 15.5371, 16.4251, 16.8879, 17.3638, 17.8531, 17.8531};
	int aN_Ds = 39;

	double aF_Es[] = {0.01,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aEs[] = {0.0001,0.0001,0.0001,0.00010913, 0.0001219, 0.0001363,  0.000161,  0.000683,  0.002452,   0.00534,   0.00931,   0.01452,   0.02084,  0.029093,   0.03534,   0.04538,   0.17712,   0.35481,0.5383,0.6186,   0.75137,0.8167,0.8877,0.9384,0.965,  1,  1};
	int aN_Es = 27;

	double aF_Fs[] = {9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aFs[] = {1.5599e-005,2.0032e-005,7.8181e-005,0.000185,0.0003,0.00045,0.0007,0.000853,0.001158,  0.0014466,0.001807,0.007051,0.017158,0.0299,0.041753,0.06161,0.086,0.10741,0.1342,0.1723,0.7,1.6821,2.9325,3.8719,6.0398,7.9747,9.6872,11.7674,13.9025,32.9027,49.9189,57.3601,60.6384,64.1041,67.7678,69.6775,69.6775,71.641,71.641,73.6598	};
	int aN_Fs = 40;

	double aF_G1s[] = {0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,20,30,40,50,60,70,80,90, 100, 200, 300, 400, 500, 600, 700, 800, 900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000};
	double aG1s[] = {2.3667e-005,2.5724e-005,2.6449e-005,2.7961e-005,2.9559e-005,2.9559e-005,3.0392e-005,3.1248e-005,3.1248e-005,3.2129e-005,3.4922e-005,3.6918e-005,3.9028e-005,3.9028e-005,4.1259e-005,4.1259e-005,4.3617e-005,4.4846e-005,4.4846e-005,5.1531e-005,5.6011e-005,6.0881e-005,6.6174e-005,6.6174e-005,6.8039e-005,7.1928e-005,7.3955e-005,7.6039e-005, 9.497e-005,0.0001153,0.0001325, 0.000144,0.0001566,0.00017, 0.000175, 0.000185,0.0001956, 0.000288, 0.000371,0.00045,0.00053, 0.000578,0.0006284,0.0007023,0.0007634,0.0008298, 0.001368,0.00191, 0.002386, 0.003063, 0.003424,0.004,0.00452,0.005,0.00534, 0.010698, 0.015353,0.02027};
	int aN_G1s = 58;

	double aF_G10s[] = {0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000};
	double aG10s[] = {1e-005,1.0282e-005,1.0282e-005,1.0572e-005,1.0572e-005,1.0869e-005,1.0869e-005,1.0869e-005,1.1176e-005,1.1176e-005,1.1491e-005,1.2147e-005,1.2147e-005,1.249e-005,1.3204e-005,1.3204e-005,1.3576e-005,1.3576e-005,1.3958e-005,1.6039e-005,1.7925e-005,1.8949e-005,1.9483e-005,2.0597e-005,2.1774e-005,2.2387e-005,2.2387e-005,2.3018e-005,3.0392e-005,3.5906e-005,3.9028e-005,4.3617e-005,4.8745e-005,5.0119e-005,5.4476e-005,5.759e-005,6.0881e-005,8.7373e-005,0.0001122,0.0001363,0.0001523,0.00017023,0.00019024,0.0002068,0.0002376,0.00025119,0.0004259,0.00061123,0.0007849,0.00098,0.0011265,0.0012589,0.0014068,0.0015293,0.0017091,0.0031497,0.0046477,0.0058048};
	int aN_G10s = 58;

//////////////////////////////////////////////// Relative permittivity  (er) ////////////////////////////////////////////////////
	double aF_Ae[] = {0.01, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aAe[] = {70,70,66.8625,63.71,62.69,59.7353,57.8423,54.2342,52.5154,50,29.4229,19.3517,13.58,11.1932, 9.84,8.651, 8.11, 7.73, 7.61, 7, 7};
	int aN_Ae = 21;

	double aF_Be[] = {0.01,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,300000};
	double aBe[] = {30,30,27.58,24.25,20.64,18.44,16.474,14.96,13.36,12.1317,11.19, 6.7,5.34,4.62,4.33, 4, 4, 4, 4, 4};
	int aN_Be = 20;

	double aF_Ce[] = {0.01,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aCe[] = {80,80,76.3984,76.4,73.98,71.64,44.232,27.752,18.5683,13.6816,11.2815, 9.6,8.72,8.0495,7.6706, 7, 7};
	int aN_Ce = 17;

	double aF_De[] = {0.01,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,300000};
	double aDe[] = {15,15,14.25,13.8,13.15,12.7321,12.33,11.19, 6.7,5.34,4.62,4.33, 4, 4, 4, 4, 4};
	int aN_De = 17;

	double aF_Ee[] = {0.01,300000};
	double aEe[] = {3,3};
	int aN_Ee = 2;

	double aF_Fe[] = {0.01,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,300000};
	double aFe[] = {80,80,76.3984,76.4,73.98,71.64,44.232,27.752,18.5683,13.6816,11.2815, 9.6,8.72,8.0495,7.6706, 7, 7};
	int aN_Fe = 17;

	double aF_G1e[] = {0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,300000};
	double aG1e[] = {26.7,14.72,9.0792,6.5794,5.1676,4.2596,3.685,3.3456,3.1879,3,3};
	int aN_G1e = 11;

	double aF_G10e[] = {0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09, 0.1,300000};
	double aG10e[] = {13.15, 6.7,4.7679,3.8674, 3.4,3.24,3.14,3,3,3,3};
	int aN_G10e = 11;

	double Sigma, epsr;
	if(TerType==0)
	{
		Sigma = Interp1(aF_As,aAs,Frq_MHz,aN_As);
		epsr  = Interp1(aF_Ae,aAe,Frq_MHz,aN_Ae);
	}
	else if(TerType==1)
	{
		Sigma = Interp1(aF_Bs,aBs,Frq_MHz,aN_Bs);
		epsr  = Interp1(aF_Be,aBe,Frq_MHz,aN_Be);
	}
	else if(TerType==2)
	{
		Sigma = Interp1(aF_Cs,aCs,Frq_MHz,aN_Cs);
		epsr  = Interp1(aF_Ce,aCe,Frq_MHz,aN_Ce);
	}
	else if(TerType==3)
	{
		Sigma = Interp1(aF_Ds,aDs,Frq_MHz,aN_Ds);
		epsr  = Interp1(aF_De,aDe,Frq_MHz,aN_De);
	}
	else if(TerType==4)
	{
		Sigma = Interp1(aF_Es,aEs,Frq_MHz,aN_Es);
		epsr  = Interp1(aF_Ee,aEe,Frq_MHz,aN_Ee);
	}
	else if(TerType==5)
	{
		Sigma = Interp1(aF_Fs,aFs,Frq_MHz,aN_Fs);
		epsr  = Interp1(aF_Fe,aFe,Frq_MHz,aN_Fe);
	}
	else if(TerType==6)
	{
		Sigma = Interp1(aF_G1s,aG1s,Frq_MHz,aN_G1s);
		epsr  = Interp1(aF_G1e,aG1e,Frq_MHz,aN_G1e);
	}
	else if(TerType==7)
	{
		Sigma = Interp1(aF_G10s,aG10s,Frq_MHz,aN_G10s);
		epsr  = Interp1(aF_G10e,aG10e,Frq_MHz,aN_G10e);
	}

	double pi = 4.0*atan(1.0);
	double la = 300.0/Frq_MHz;
	double R = 6371000.0;
	double ae = R*kf;
	double Kh = pow(2*pi*ae/la,-1.0/3.0)*pow(pow(epsr-1.0,2.0)+pow(60.0*la*Sigma,2.0) , -1.0/4.0);
	double Kv = Kh*pow(pow(epsr,2.0)+pow(60.0*la*Sigma,2.0) , 1.0/2.0);

	double K =1.0;
	K = (pol==0) ? Kh : Kv;

	double beta = (1.0+1.6*K*K+0.75*K*K*K*K)/(1.0+4.5*K*K+1.35*K*K*K*K);

	double X = 1000.0*beta*d_km*pow(pi/(la*ae*ae),1.0/3.0);
	double FX = 11.0+10.0*log10(X)-17.6*X;

	double Y1 = 2.0*beta*h1_m*pow(pi*pi/(la*la*ae),1.0/3.0);
	double Y2 = 2.0*beta*h2_m*pow(pi*pi/(la*la*ae),1.0/3.0);
	double GY1 = G_Y(K,Y1);
	double GY2 = G_Y(K,Y2);

	return (FX+GY1+GY2);
}


double CP527_526_Functions::G_Y(double K,double Y) 
{
	double GY = 0.0;
	if(Y>2.0)
		GY = 17.6*pow(Y-1.1,1.0/2.0)-5.0*log10(Y-1.1)-8.0;
	else if((Y>10.0*K) && (Y<=2.0))
		GY = 20.0*log10(Y+0.1*Y*Y*Y);
	else if((Y>K/10.0) && (Y<=10.0*K))
		GY = 2.0+20.0*log10(K)+9.0*log10(Y/K)*(1.0+log10(Y/K));
	else if(Y<=(K/10.0))
		GY = 2.0+20.0*log10(K);
	return GY;
}

double CP527_526_Functions::Interp1(double *D0,double *E0,double d,int num) 
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
	Eb=((d1==d2) ? E1 : E1+(E2-E1)*log10(d/d1)/log10(d2/d1));
	return Eb;
}
