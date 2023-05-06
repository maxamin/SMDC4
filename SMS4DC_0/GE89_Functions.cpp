// GE89_Functions.cpp: implementation of the CGE89_Functions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sms4dc.h"
#include "GE89_Functions.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGE89_Functions::CGE89_Functions()
{

}

CGE89_Functions::~CGE89_Functions()
{

}
/////////////////////////////////////////////////////////
//CGE89_Functions Functions


////////////////////////////Protection Ratio Calculation//////////////////////////////////////

BOOL CGE89_Functions::Protection_Ratio(double FvX , double FvY , double FsX , double FsY ,
							 double offvX , double offvY , double offsY , 
							 double VSRx , double VSRy , int Xn , int Yn ,
							 CString Xsys, CString Ysys , 
							 CString Xcolor , CString freq_stablX ,
							 double *PR_t , double *PR_c )
{
	double PRv_t = -999.0, PRv_c = -999.0;
	double PRsv_t = -999.0 , PRsv_c = -999.0;
	double PRs_t = -999.0 , PRs_c = -999.0;
	double PRvs_t = -999.0 , PRvs_c = -999.0;
	double PRimage_t = -999.0 , PRimage_c = -999.0;
	double DoffV = fabs(offvY - offvX);

	if(DoffV<=13.0)
	{
		double DfV = FvY - FvX;
		PRv_t_c( DoffV, DfV, Xsys, Ysys, Xcolor, freq_stablX ,  &PRv_t , &PRv_c);
		/////////////////////////////////
		double DfSV = FsY - FvX;
		double DoffSV = fabs(offsY - offvX);
		PRsv_t_c( DoffSV, DfSV, DfV, Xsys, Ysys,Xcolor, freq_stablX ,FvX , VSRy ,&PRsv_t , &PRsv_c);
		/////////////////////////////////
		double DfS = fabs(FsY - FsX);
		PRs_t_c( DfS , VSRx , VSRy ,&PRs_t , &PRs_c);
		/////////////////////////////////
		double DfVS = fabs(FvY - FsX);
		PRvs_t_c( DfVS , VSRx , &PRvs_t , &PRvs_c);
	}
	/////////////////////////////////
	PRimage_t_c( FvX ,  Xsys, Ysys, Xn, Yn,&PRimage_t , &PRimage_c);
	/////////////////////////////////
	double At = max(max(max(max(PRv_t,PRsv_t),PRs_t),PRvs_t),PRimage_t);
	double Ac = max(max(max(max(PRv_c,PRsv_c),PRs_c),PRvs_c),PRimage_c);

	if((At>-100)&&(Ac>-100))
	{
		*PR_t = At;
		*PR_c = Ac;
		return TRUE;
	}
	else
		return FALSE;

}

void CGE89_Functions::PRimage_t_c(double FvX , CString Xsys,CString Ysys,int Xn,int Yn,
														double *PRimage_t , double *PRimage_c)
{
	double PRimageT = -999, PRimageC = -999;
	if(FvX>300.0)
	{
		double PR0[3];		int Yn0[3];

		int Num = Table_3_IV( Xsys, Ysys, Xn ,PR0 , Yn0);
		for(int i=0;i<Num;i++)
		{
			if(Yn0[i]==Yn)
			{
				PRimageT = PR0[i];
				PRimageC = PRimageT + 10.0;
			}
		}
	}
	*PRimage_t = PRimageT;
	*PRimage_c = PRimageC;
}

void CGE89_Functions::PRvs_t_c(double DfVS , double VSRx ,
								   double *PRvs_t , double *PRvs_c)
{
	double PRvst , PRvsc;
	Table_3_IX( DfVS, &PRvst, &PRvsc);
	*PRvs_t = PRvst - 2 + VSRx;
	*PRvs_c = PRvsc - 2 + VSRx;
}

void CGE89_Functions::PRs_t_c(double DfS , double VSRx , double VSRy ,
								   double *PRs_t , double *PRs_c)
{
	double PRst , PRsc;
	Table_3_IX( DfS, &PRst, &PRsc);
	*PRs_t = PRst - VSRy + VSRx;
	*PRs_c = PRsc - VSRy + VSRx;
}


void CGE89_Functions::PRsv_t_c(double DoffSV,double DfSV,double DfV,CString Xsys,CString Ysys,
								   CString Xcolor,CString freq_stablX , 
								   double FvX , double VSRy ,
								   double *PRsv_t , double *PRsv_c)
{
	double PRsvt = -999.0 , PRsvc = -999.0;
	if((DfSV>=-1.25)&&(DfSV<=6.0)&&(freq_stablX=="NORMAL"))
	{
		PRsvt = -VSRy + Table_3_VI ( DoffSV, DfSV, Xsys, Xcolor);
		PRsvc = -VSRy + Table_3_VII( DoffSV, DfSV, Xsys, Xcolor);
	}
	else if((DfSV>=-1.25)&&(DfSV<=6.0)&&(freq_stablX=="PRECISION"))
	{
		PRsvt = -VSRy + Table_3_C_II ( DoffSV, DfSV, Xsys, Xcolor);
		PRsvc = -VSRy + Table_3_C_III( DoffSV, DfSV, Xsys, Xcolor);
	}
	else if(((DfSV>6.0)&&(DfSV<=6.2))&&((Xsys=="B")||(Xsys=="G")))
	{
		double PRvt1 , PRvt2 , PRvc1 , PRvc2;

		if (freq_stablX=="NORMAL")
		{
			PRvt1 = -VSRy + Table_3_VI ( DoffSV, 6.0, Xsys, Xcolor);
			PRvc1 = -VSRy + Table_3_VII( DoffSV, 6.0, Xsys, Xcolor);
		}
		else if (freq_stablX=="PRECISION")
		{
			PRvt1 = -VSRy + Table_3_C_II ( DoffSV, 6.0, Xsys, Xcolor);
			PRvc1 = -VSRy + Table_3_C_III( DoffSV, 6.0, Xsys, Xcolor);
		}
		Table_3_VIII( 6.2, Xsys,&PRvt2,&PRvc2);
		PRvt2 = -VSRy + PRvt2;
		PRvc2 = -VSRy + PRvc2;

		PRsvt = PRvt1+(DfSV-6.0)*(PRvt2-PRvt1)/(6.2-6.0);
		PRsvc = PRvc1+(DfSV-6.0)*(PRvc2-PRvc1)/(6.2-6.0);
	}
	else if(((DfSV>6.0)&&(DfSV<=7.3))&&((Xsys=="I")||(Xsys=="K1")))
	{
		double PRvt1 , PRvt2 , PRvc1 , PRvc2;

		if (freq_stablX=="NORMAL")
		{
			PRvt1 = -VSRy + Table_3_VI ( DoffSV, 6.0, Xsys, Xcolor);
			PRvc1 = -VSRy + Table_3_VII( DoffSV, 6.0, Xsys, Xcolor);
		}
		else if (freq_stablX=="PRECISION")
		{
			PRvt1 = -VSRy + Table_3_C_II ( DoffSV, 6.0, Xsys, Xcolor);
			PRvc1 = -VSRy + Table_3_C_III( DoffSV, 6.0, Xsys, Xcolor);
		}
		Table_3_VIII( 7.3, Xsys,&PRvt2,&PRvc2);
		PRvt2 = -VSRy + PRvt2;
		PRvc2 = -VSRy + PRvc2;

		PRsvt = PRvt1+(DfSV-6.0)*(PRvt2-PRvt1)/(7.3-6.0);
		PRsvc = PRvc1+(DfSV-6.0)*(PRvc2-PRvc1)/(7.3-6.0);
	}
	else if((((DfSV>6.2)&&(DfSV<=15.0))&&((Xsys=="B")||(Xsys=="G")))||((DfSV>=-14.0)&&(DfSV<-1.25)))
	{
		Table_3_VIII( DfSV, Xsys,&PRsvt,&PRsvc);
		PRsvt = -VSRy + PRsvt;
		PRsvc = -VSRy + PRsvc;
	}
	else if((((DfSV>7.3)&&(DfSV<=15.0))&&((Xsys=="I")||(Xsys=="K1")))||((DfSV>=-14.0)&&(DfSV<-1.25)))
	{
		Table_3_VIII( DfSV, Xsys,&PRsvt,&PRsvc);
		PRsvt = -VSRy + PRsvt;
		PRsvc = -VSRy + PRsvc;
	}
	if((DfV==-7.0)&&(Xsys=="B")&&(Ysys=="B")&&(FvX>=30.0)&&(FvX<=300.0))
	{
		PRsvt = -9.0 + 10.0 -VSRy;
		PRsvc =  1.0 + 10.0 -VSRy;
	}
	if((DfV==-8.0)&&(Xsys!="B")&&(Ysys!="B")&&(FvX>=30.0)&&(FvX<=300.0))
	{
		PRsvt = -9.0 + 10.0 -VSRy;
		PRsvc =  1.0 + 10.0 -VSRy;
	}
	if((DfV==-8.0)&&(FvX>300.0))
	{
		PRsvt = Table_3_III( Xsys, Ysys) + 10.0 -VSRy;
		PRsvc = PRsvt + 10.0;
	}
	*PRsv_t = PRsvt;
	*PRsv_c = PRsvc;
}


void CGE89_Functions::PRv_t_c(double DoffV,double DfV,CString Xsys,CString Ysys,
								   CString Xcolor,CString freq_stablX ,
								   double *PRv_t , double *PRv_c)
{
	double PRvt = -999.0 , PRvc = -999.0 , Corr1 = -2.0;

	if((DfV>=-1.25)&&(DfV<=6.0)&&(freq_stablX=="NORMAL"))
	{
		PRvt = Corr1 + Table_3_VI ( DoffV, DfV, Xsys, Xcolor);
		PRvc = Corr1 + Table_3_VII( DoffV, DfV, Xsys, Xcolor);
	}
	else if((DfV>=-1.25)&&(DfV<=6.0)&&(freq_stablX=="PRECISION"))
	{
		PRvt = Corr1 + Table_3_C_II ( DoffV, DfV, Xsys, Xcolor);
		PRvc = Corr1 + Table_3_C_III( DoffV, DfV, Xsys, Xcolor);
	}
	else if(((DfV>6.0)&&(DfV<=6.2))&&((Xsys=="B")||(Xsys=="G")))
	{
		double PRvt1 , PRvt2 , PRvc1 , PRvc2;

		if (freq_stablX=="NORMAL")
		{
			PRvt1 = Corr1 + Table_3_VI ( DoffV, 6.0, Xsys, Xcolor);
			PRvc1 = Corr1 + Table_3_VII( DoffV, 6.0, Xsys, Xcolor);
		}
		else if (freq_stablX=="PRECISION")
		{
			PRvt1 = Corr1 + Table_3_C_II ( DoffV, 6.0, Xsys, Xcolor);
			PRvc1 = Corr1 + Table_3_C_III( DoffV, 6.0, Xsys, Xcolor);
		}
		Table_3_VIII( 6.2, Xsys,&PRvt2,&PRvc2);
		PRvt2 = PRvt2;
		PRvc2 = PRvc2;

		PRvt = PRvt1+(DfV-6.0)*(PRvt2-PRvt1)/(6.2-6.0);
		PRvc = PRvc1+(DfV-6.0)*(PRvc2-PRvc1)/(6.2-6.0);
	}
	else if(((DfV>6.0)&&(DfV<=7.3))&&((Xsys=="I")||(Xsys=="K1")))
	{
		double PRvt1 , PRvt2 , PRvc1 , PRvc2;

		if (freq_stablX=="NORMAL")
		{
			PRvt1 = Corr1 + Table_3_VI ( DoffV, 6.0, Xsys, Xcolor);
			PRvc1 = Corr1 + Table_3_VII( DoffV, 6.0, Xsys, Xcolor);
		}
		else if (freq_stablX=="PRECISION")
		{
			PRvt1 = Corr1 + Table_3_C_II ( DoffV, 6.0, Xsys, Xcolor);
			PRvc1 = Corr1 + Table_3_C_III( DoffV, 6.0, Xsys, Xcolor);
		}
		Table_3_VIII( 7.3, Xsys,&PRvt2,&PRvc2);
		PRvt2 = PRvt2;
		PRvc2 = PRvc2;

		PRvt = PRvt1+(DfV-6.0)*(PRvt2-PRvt1)/(7.3-6.0);
		PRvc = PRvc1+(DfV-6.0)*(PRvc2-PRvc1)/(7.3-6.0);
	}
	else if((((DfV>6.2)&&(DfV<=15.0))&&((Xsys=="B")||(Xsys=="G")))||((DfV>=-14.0)&&(DfV<-1.25)))
	{
		Table_3_VIII( DfV, Xsys,&PRvt,&PRvc);
	//	PRvt = Corr1 + PRvt;
	//	PRvc = Corr1 + PRvc;
	}
	else if((((DfV>7.3)&&(DfV<=15.0))&&((Xsys=="I")||(Xsys=="K1")))||((DfV>=-14.0)&&(DfV<-1.25)))
	{
		Table_3_VIII( DfV, Xsys,&PRvt,&PRvc);
	//	PRvt = Corr1 + PRvt;
	//	PRvc = Corr1 + PRvc;
	}

	if((DfV==7.0)&&(Xsys=="B")&&(Ysys=="B"))
	{
		PRvt = -12.0;		PRvc = -2.0;
	}
	if((DfV==8.0)&&(Xsys!="B")&&(Ysys!="B"))
	{
		PRvt = -12.0;		PRvc = -2.0;
	}
	*PRv_t = PRvt;
	*PRv_c = PRvc;
}


double CGE89_Functions::Table_3_III(CString Xsys,CString Ysys)
{
	double PR = -999.0;
	if((Ysys=="G")||(Ysys=="H")||(Ysys=="I"))
		PR = -9.0;
	else if(Ysys=="K1")
	{
		if((Xsys=="G")||(Xsys=="K1"))
			PR = -9.0;
		else if((Xsys=="H")||(Xsys=="I"))
			PR = 13.0;
	}
	return PR;
}

int CGE89_Functions::Table_3_IV(CString Xsys,CString Ysys,int Xn ,double *PR , int *Yn)
{
	int Out_Num = 0;

	if(Xsys=="G")
	{
		Out_Num = 1;
		Yn[0] = Xn + 9;
		if((Ysys=="G")||(Ysys=="H"))	PR[0] = -1;
		else if(Ysys=="I")				PR[0] = -4;
		else if(Ysys=="K1")				PR[0] = -11;
	}
	else if(Xsys=="H")
	{
		Out_Num = 1;
		Yn[0] = Xn + 9;
		if((Ysys=="G")||(Ysys=="H"))	PR[0] = -1;
		else if(Ysys=="I")				PR[0] = -4;
		else if(Ysys=="K1")				PR[0] = -9;
	}
	else if(Xsys=="I")
	{
		Out_Num = 1;
		Yn[0] = Xn + 9;
		if((Ysys=="G")||(Ysys=="H"))	PR[0] = -13;
		else if(Ysys=="I")				PR[0] = -10;
		else if(Ysys=="K1")				PR[0] = -10;
	}
	else if(Xsys=="K1")
	{
		Out_Num = 3;

		Yn[0] = Xn - 9;		Yn[1] = Xn + 9;		Yn[2] = Xn + 10;
		if((Ysys=="G")||(Ysys=="H")){	PR[0] = -1;		PR[1] = -1;			PR[2] = +7;	}
		else if(Ysys=="I")			{	PR[0] = 0;		PR[1] = -4;			PR[2] = +7;	}
		else if(Ysys=="K1")			{	PR[0] = -2;		PR[1] = -5;			PR[2] = +7;	}
	}
	else
	{
		Yn[0] = -999;
		PR[0] = -999;
	}
	return Out_Num;	
}

void CGE89_Functions::Table_3_IX(double DfV,double *PRtv,double *PRcv)
{
	double DfV0[] = {0,15,50,250};
	double PRt0[] = {32,30,22,-6};
	double PRc0[] = {39,35,24,-6};

	*PRtv = Interp2(DfV0,PRt0, DfV*1000.0,4);
	*PRcv = Interp2(DfV0,PRc0, DfV*1000.0,4);
}



void CGE89_Functions::Table_3_VIII(double DfV,CString Xsys,double *PRtv,double *PRcv)
{
	double PRt = -999.0,PRc = -999.0;

	if((DfV>-6.0)&&(DfV<-2.5))
	{
		double PRt1,PRc1,PRt2,PRc2;

		double DfV1 = -6.0 , DfV2 = -2.5;
		Table_3_VIII0( DfV1, Xsys,&PRt1,&PRc1);
		Table_3_VIII0( DfV2, Xsys,&PRt2,&PRc2);

		PRt = PRt1+(DfV-DfV1)*(PRt2-PRt1)/(DfV2-DfV1);
		PRc = PRc1+(DfV-DfV1)*(PRc2-PRc1)/(DfV2-DfV1);
	}
	else if((DfV>-1.5)&&(DfV<-1.25))
	{
		double PRt1,PRc1,PRt2,PRc2;

		double DfV1 = -1.5 , DfV2 = -1.25;
		Table_3_VIII0( DfV1, Xsys,&PRt1,&PRc1);
		Table_3_VIII0( DfV2, Xsys,&PRt2,&PRc2);

		PRt = PRt1+(DfV-DfV1)*(PRt2-PRt1)/(DfV2-DfV1);
		PRc = PRc1+(DfV-DfV1)*(PRc2-PRc1)/(DfV2-DfV1);
	}
	else
		Table_3_VIII0( DfV, Xsys,&PRt,&PRc);

	*PRtv = PRt;
	*PRcv = PRc;
}

void CGE89_Functions::Table_3_VIII0(double DfV,CString Xsys,double *PRtv,double *PRcv)
{
	double PRt = -999.0 , PRc = -999.0;
	
	if(((DfV>=-14.0)&&(DfV<=-6))&&((Xsys=="B")||(Xsys=="G")||(Xsys=="I")||(Xsys=="K1")))
	{
		PRt = -15;		PRc = -10;
	}
	else if(((DfV>=-2.5)&&(DfV<=-1.5))&&((Xsys=="B")||(Xsys=="G")||(Xsys=="I")||(Xsys=="K1")))
	{
		PRt = 1;		PRc = 11;
	}
	else if(((DfV>=6.2)&&(DfV<=15.0))&&((Xsys=="B")||(Xsys=="G")))
	{
		PRt = -12;		PRc = -2;
	}
	else if(((DfV>=7.3)&&(DfV<=15.0))&&((Xsys=="I")||(Xsys=="K1")))
	{
		PRt = -12;		PRc = -2;
	}
	else if((DfV==-1.25)&&((Xsys=="I")||(Xsys=="K1")))
	{
		PRt = 32;		PRc = 40;
	}
	else if((DfV==-1.25)&&((Xsys=="B")||(Xsys=="G")))
	{
		PRt = 23;		PRc = 32;
	}
	*PRtv = PRt;
	*PRcv = PRc;
}


double CGE89_Functions::Table_3_C_III(double DoffV,double DfV,CString Xsys,CString Xcolor)
{
	double PRcv = -999.0 , DfV1 , DfV2;
	if((DfV>-1.25)&&(DfV<-0.5))
	{
		DfV1 = -1.25;		DfV2 = -0.5;
	}
	else if((DfV>-0.5)&&(DfV<0.0))
	{
		DfV1 = -0.5;		DfV2 = 0.0;
	}
	else if((DfV>0.0)&&(DfV<0.5))
	{
		DfV1 = 0.0;		DfV2 = 0.5;
	}
	else if((DfV>0.5)&&(DfV<1.0))
	{
		DfV1 = 0.5;		DfV2 = 1.0;
	}
	else if((DfV>1.0)&&(DfV<2.0))
	{
		DfV1 = 1.0;		DfV2 = 2.0;
	}
	else if((DfV>2.0)&&(DfV<3.0))
	{
		DfV1 = 2.0;		DfV2 = 3.0;
	}
	else if((DfV>3.0)&&(DfV<3.6))
	{
		DfV1 = 3.0;		DfV2 = 3.6;
	}
	else if ((!((Xsys=="B")||(Xsys=="G")))&&((DfV>4.8)&&(DfV<5.7)))
	{
		DfV1 = 4.8;		DfV2 = 5.7;
	}
	else if (((Xsys=="B")||(Xsys=="G"))&&((DfV>4.8)&&(DfV<5.3)))
	{
		DfV1 = 4.8;		DfV2 = 5.3;
	}
	else
	{
		DfV1 = DfV;		DfV2 = DfV;
	}

	if(DfV1==DfV2)
		PRcv = Table_3_C_III0( DoffV, DfV1, Xsys, Xcolor);
	else
	{
		double PRtv1 = Table_3_C_III0( DoffV, DfV1, Xsys, Xcolor);
		double PRtv2 = Table_3_C_III0( DoffV, DfV2, Xsys, Xcolor);

		PRcv = PRtv1+(DfV-DfV1)*(PRtv2-PRtv1)/(DfV2-DfV1);
	}
	return PRcv;
}
double CGE89_Functions::Table_3_C_III0(double DoffV,double DfV,CString Xsys,CString Xcolor)
{
	double DoffV0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
	double aPRtv1[] = {30,29,27,24,22,22,23,22,22,24,27,29,30,29,27,24,22,22,23,22,22,24,27,29,30,29,27,24,22,22,23,22,22,24,27,29,30};
	double aPRtv2[] = {22,22,20,17,15,15,16,15,15,17,20,22,22,22,20,17,15,15,16,15,15,17,20,22,22,22,20,17,15,15,16,15,15,17,20,22,22};
	double aPRtv3[] = {37,38,34,30,27,27,29,27,27,30,34,38,37,38,34,30,27,27,29,27,27,30,34,38,37,38,34,30,27,27,29,27,27,30,34,38,37};
	double aPRtv4[] = {38,40,36,32,29,29,32,29,29,32,36,40,44,40,36,32,29,29,32,29,29,32,36,40,44,40,36,32,29,29,32,29,29,32,36,40,44};
	double aPRtv5[] = {44,42,38,34,31,31,33,31,31,34,38,42,44,42,38,34,31,31,33,31,31,34,38,42,44,42,38,34,31,31,33,31,31,34,38,42,44};
	double aPRtv6[] = {42,41,37,33,31,31,32,31,31,33,37,41,42,41,37,33,31,31,32,31,31,33,37,41,42,41,37,33,31,31,32,31,31,33,37,41,42};
	double aPRtv7[] = {36,36,34,31,30,30,30,30,30,31,34,36,36,36,34,31,30,30,30,30,30,31,34,36,36,36,34,31,30,30,30,30,30,31,34,36,36};
	double aPRtv8[] = {34,36,39,40,39,36,34,34,36,39,36,34,34,36,39,40,39,36,34,34,36,39,36,34,34,36,39,40,39,36,34,34,36,39,36,34,34};
	double aPRtv9[] = {21,22,24,26,24,22,21,21,22,24,22,21,21,22,24,26,24,22,21,21,22,24,22,21,21,22,24,26,24,22,21,21,22,24,22,21,21};
	double aPRtv10[] = {37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37};
	double aPRtv11[] = {21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21};

	double aPRtv0[37];	int i;

	if(((Xsys=="H")||(Xsys=="I")||(Xsys=="K1"))&&(DfV==-1.25))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv1[i];
	else if(((Xsys=="B")||(Xsys=="G"))&&(DfV==-1.25))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv2[i];
	else if(DfV==-0.5)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv3[i];
	else if(DfV==0.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv4[i];
	else if(DfV==0.5)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv5[i];
	else if(DfV==1.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv5[i];
	else if(DfV==2.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv6[i];
	else if(DfV==3.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv7[i];
	else if((DfV>=3.6)&&(DfV<=4.8)&&(Xcolor="PAL"))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv8[i];
	else if(((DfV>=5.7)&&(DfV<=6.0)&&(Xcolor="PAL"))&& !((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv9[i];
	else if(((DfV>=5.3)&&(DfV<=6.0)&&(Xcolor="PAL"))&& ((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv9[i];
	else if((DfV>=3.6)&&(DfV<=4.8)&&(Xcolor="SECAM"))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv10[i];
	else if(((DfV>=5.7)&&(DfV<=6.0)&&(Xcolor="SECAM"))&& !((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv11[i];
	else if(((DfV>=5.3)&&(DfV<=6.0)&&(Xcolor="SECAM"))&& ((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv11[i];

	double PRcv = Interp2(DoffV0,aPRtv0, DoffV,37);
	return PRcv;
}


double CGE89_Functions::Table_3_C_II(double DoffV,double DfV,CString Xsys,CString Xcolor)
{
	double PRtv = -999.0 , DfV1 , DfV2;
	if((DfV>-1.25)&&(DfV<-0.5))
	{
		DfV1 = -1.25;		DfV2 = -0.5;
	}
	else if((DfV>-0.5)&&(DfV<0.0))
	{
		DfV1 = -0.5;		DfV2 = 0.0;
	}
	else if((DfV>0.0)&&(DfV<0.5))
	{
		DfV1 = 0.0;		DfV2 = 0.5;
	}
	else if((DfV>0.5)&&(DfV<1.0))
	{
		DfV1 = 0.5;		DfV2 = 1.0;
	}
	else if((DfV>1.0)&&(DfV<2.0))
	{
		DfV1 = 1.0;		DfV2 = 2.0;
	}
	else if((DfV>2.0)&&(DfV<3.0))
	{
		DfV1 = 2.0;		DfV2 = 3.0;
	}
	else if((DfV>3.0)&&(DfV<3.6))
	{
		DfV1 = 3.0;		DfV2 = 3.6;
	}
	else if ((!((Xsys=="B")||(Xsys=="G")))&&((DfV>4.8)&&(DfV<5.7)))
	{
		DfV1 = 4.8;		DfV2 = 5.7;
	}
	else if (((Xsys=="B")||(Xsys=="G"))&&((DfV>4.8)&&(DfV<5.3)))
	{
		DfV1 = 4.8;		DfV2 = 5.3;
	}
	else
	{
		DfV1 = DfV;		DfV2 = DfV;
	}

	if(DfV1==DfV2)
		PRtv = Table_3_C_II0( DoffV, DfV1, Xsys, Xcolor);
	else
	{
		double PRtv1 = Table_3_C_II0( DoffV, DfV1, Xsys, Xcolor);
		double PRtv2 = Table_3_C_II0( DoffV, DfV2, Xsys, Xcolor);

		PRtv = PRtv1+(DfV-DfV1)*(PRtv2-PRtv1)/(DfV2-DfV1);
	}
	return PRtv;
}

double CGE89_Functions::Table_3_C_II0(double DoffV,double DfV,CString Xsys,CString Xcolor)
{
	double DoffV0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
	double aPRtv1[] = {23,23,21,19,17,17,17,17,17,19,21,23,23,23,21,19,17,17,17,17,17,19,21,23,23,23,21,19,17,17,17,17,17,19,21,23,23};
	double aPRtv2[] = {11,11,9,7,5,5,5,5,5,7,9,11,11,11,9,7,5,5,5,5,5,7,9,11,11,11,9,7,5,5,5,5,5,7,9,11,11};
	double aPRtv3[] = {32,33,29,25,22,22,24,22,22,25,29,33,32,33,29,25,22,22,24,22,22,25,29,33,32,33,29,25,22,22,24,22,22,25,29,33,32};
	double aPRtv4[] = {34,36,32,28,24,24,26,24,24,28,32,36,40,36,32,28,24,24,26,24,24,28,32,36,40,36,32,28,24,24,26,24,24,28,32,36,40};
	double aPRtv5[] = {40,39,35,31,26,26,28,26,26,31,35,39,40,39,35,31,26,26,28,26,26,31,35,39,40,39,35,31,26,26,28,26,26,31,35,39,40};
	double aPRtv6[] = {37,36,33,29,25,25,26,25,25,29,33,35,37,36,33,29,25,25,26,25,25,29,33,35,37,36,33,29,25,25,26,25,25,29,33,35,37};
	double aPRtv7[] = {31,31,29,26,24,24,24,24,24,26,29,31,31,31,29,26,24,24,24,24,24,26,29,31,31,31,29,26,24,24,24,24,24,26,29,31,31};
	double aPRtv8[] = {28,31,34,35,34,31,28,28,31,34,31,28,28,31,34,35,34,31,28,28,31,34,31,28,28,31,34,35,34,31,28,28,31,34,31,28,28};
	double aPRtv9[] = {15,16,17,18,17,16,15,15,16,17,16,15,15,16,17,18,17,16,15,15,16,17,16,15,15,16,17,18,17,16,15,15,16,17,16,15,15};
	double aPRtv10[] = {33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33};
	double aPRtv11[] = {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18};

	double aPRtv0[37];	int i;

	if(((Xsys=="H")||(Xsys=="I")||(Xsys=="K1"))&&(DfV==-1.25))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv1[i];
	else if(((Xsys=="B")||(Xsys=="G"))&&(DfV==-1.25))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv2[i];
	else if(DfV==-0.5)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv3[i];
	else if(DfV==0.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv4[i];
	else if(DfV==0.5)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv5[i];
	else if(DfV==1.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv5[i];
	else if(DfV==2.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv6[i];
	else if(DfV==3.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv7[i];
	else if((DfV>=3.6)&&(DfV<=4.8)&&(Xcolor="PAL"))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv8[i];
	else if(((DfV>=5.7)&&(DfV<=6.0)&&(Xcolor="PAL"))&& !((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv9[i];
	else if(((DfV>=5.3)&&(DfV<=6.0)&&(Xcolor="PAL"))&& ((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv9[i];
	else if((DfV>=3.6)&&(DfV<=4.8)&&(Xcolor="SECAM"))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv10[i];
	else if(((DfV>=5.7)&&(DfV<=6.0)&&(Xcolor="SECAM"))&& !((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv11[i];
	else if(((DfV>=5.3)&&(DfV<=6.0)&&(Xcolor="SECAM"))&& ((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv11[i];

	double PRtv = Interp2(DoffV0,aPRtv0, DoffV,37);
	return PRtv;
}

double CGE89_Functions::Table_3_VII(double DoffV,double DfV,CString Xsys,CString Xcolor)
{
	double PRcv = -999.0 , DfV1 , DfV2;
	if((DfV>-1.25)&&(DfV<-0.5))
	{
		DfV1 = -1.25;		DfV2 = -0.5;
	}
	else if((DfV>-0.5)&&(DfV<0.0))
	{
		DfV1 = -0.5;		DfV2 = 0.0;
	}
	else if((DfV>0.0)&&(DfV<0.5))
	{
		DfV1 = 0.0;		DfV2 = 0.5;
	}
	else if((DfV>0.5)&&(DfV<1.0))
	{
		DfV1 = 0.5;		DfV2 = 1.0;
	}
	else if((DfV>1.0)&&(DfV<2.0))
	{
		DfV1 = 1.0;		DfV2 = 2.0;
	}
	else if((DfV>2.0)&&(DfV<3.0))
	{
		DfV1 = 2.0;		DfV2 = 3.0;
	}
	else if((DfV>3.0)&&(DfV<3.6))
	{
		DfV1 = 3.0;		DfV2 = 3.6;
	}
	else if ((!((Xsys=="B")||(Xsys=="G")))&&((DfV>4.8)&&(DfV<5.7)))
	{
		DfV1 = 4.8;		DfV2 = 5.7;
	}
	else if (((Xsys=="B")||(Xsys=="G"))&&((DfV>4.8)&&(DfV<5.3)))
	{
		DfV1 = 4.8;		DfV2 = 5.3;
	}
	else
	{
		DfV1 = DfV;		DfV2 = DfV;
	}

	if(DfV1==DfV2)
		PRcv = Table_3_VII0( DoffV, DfV1, Xsys, Xcolor);
	else
	{
		double PRcv1 = Table_3_VII0( DoffV, DfV1, Xsys, Xcolor);
		double PRcv2 = Table_3_VII0( DoffV, DfV2, Xsys, Xcolor);

		PRcv = PRcv1+(DfV-DfV1)*(PRcv2-PRcv1)/(DfV2-DfV1);
	}
	return PRcv;
}


double CGE89_Functions::Table_3_VII0(double DoffV,double DfV,CString Xsys,CString Xcolor)
{
	double DoffV0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
	double aPRtv1[] = {40,38,34,30,28,26,24,26,28,30,34,38,40,38,34,30,28,26,24,26,28,30,34,38,40,38,34,30,28,26,24,26,28,30,34,38,40};
	double aPRtv2[] = {32,30,27,23,21,19,17,19,21,23,27,30,32,30,27,23,21,19,17,19,21,23,27,30,32,30,27,23,21,19,17,19,21,23,27,30,32};
	double aPRtv3[] = {50,49,46,42,38,35,33,35,38,42,46,49,50,49,46,42,38,35,33,35,38,42,46,49,50,49,46,42,38,35,33,35,38,42,46,49,50};
	double aPRtv4[] = {54,53,50,46,42,38,35,38,42,46,50,53,54,53,50,46,42,38,35,38,42,46,50,53,54,53,50,46,42,38,35,38,42,46,50,53,54};
	double aPRtv5[] = {58,57,55,50,45,41,37,41,45,50,55,57,58,57,55,50,45,41,37,41,45,50,55,57,58,57,55,50,45,41,37,41,45,50,55,57,58};
	double aPRtv6[] = {54,53,51,46,42,38,36,38,42,46,51,53,54,53,51,46,42,38,36,38,42,46,51,53,54,53,51,46,42,38,36,38,42,46,51,53,54};
	double aPRtv7[] = {44,43,41,38,35,32,30,32,35,38,41,43,44,43,41,38,35,32,30,32,35,38,41,43,44,43,41,38,35,32,30,32,35,38,41,43,44};
	double aPRtv8[] = {45,48,51,53,51,48,45,45,48,51,48,45,45,48,51,53,51,48,45,45,48,51,48,45,45,48,51,53,51,48,45,45,48,51,48,45,45};
	double aPRtv9[] = {30,32,33,35,33,32,30,30,32,33,32,30,30,32,33,35,33,32,30,30,32,33,32,30,30,32,33,35,33,32,30,30,32,33,32,30,30};
	double aPRtv10[] = {45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45};
	double aPRtv11[] = {30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30};

	double aPRtv0[37];	int i;

	if(((Xsys=="H")||(Xsys=="I")||(Xsys=="K1"))&&(DfV==-1.25))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv1[i];
	else if(((Xsys=="B")||(Xsys=="G"))&&(DfV==-1.25))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv2[i];
	else if(DfV==-0.5)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv3[i];
	else if(DfV==0.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv4[i];
	else if(DfV==0.5)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv5[i];
	else if(DfV==1.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv5[i];
	else if(DfV==2.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv6[i];
	else if(DfV==3.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv7[i];
	else if((DfV>=3.6)&&(DfV<=4.8)&&(Xcolor="PAL"))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv8[i];
	else if(((DfV>=5.7)&&(DfV<=6.0)&&(Xcolor="PAL"))&& !((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv9[i];
	else if(((DfV>=5.3)&&(DfV<=6.0)&&(Xcolor="PAL"))&& ((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv9[i];
	else if((DfV>=3.6)&&(DfV<=4.8)&&(Xcolor="SECAM"))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv10[i];
	else if(((DfV>=5.7)&&(DfV<=6.0)&&(Xcolor="SECAM"))&& !((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv11[i];
	else if(((DfV>=5.3)&&(DfV<=6.0)&&(Xcolor="SECAM"))&& ((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv11[i];

	double PRcv = Interp2(DoffV0,aPRtv0, DoffV,37);
	return PRcv;
}


double CGE89_Functions::Table_3_VI(double DoffV,double DfV,CString Xsys,CString Xcolor)
{
	double PRtv = -999.0 , DfV1 , DfV2;
	if((DfV>-1.25)&&(DfV<-0.5))
	{
		DfV1 = -1.25;		DfV2 = -0.5;
	}
	else if((DfV>-0.5)&&(DfV<0.0))
	{
		DfV1 = -0.5;		DfV2 = 0.0;
	}
	else if((DfV>0.0)&&(DfV<0.5))
	{
		DfV1 = 0.0;		DfV2 = 0.5;
	}
	else if((DfV>0.5)&&(DfV<1.0))
	{
		DfV1 = 0.5;		DfV2 = 1.0;
	}
	else if((DfV>1.0)&&(DfV<2.0))
	{
		DfV1 = 1.0;		DfV2 = 2.0;
	}
	else if((DfV>2.0)&&(DfV<3.0))
	{
		DfV1 = 2.0;		DfV2 = 3.0;
	}
	else if((DfV>3.0)&&(DfV<3.6))
	{
		DfV1 = 3.0;		DfV2 = 3.6;
	}
	else if ((!((Xsys=="B")||(Xsys=="G")))&&((DfV>4.8)&&(DfV<5.7)))
	{
		DfV1 = 4.8;		DfV2 = 5.7;
	}
	else if (((Xsys=="B")||(Xsys=="G"))&&((DfV>4.8)&&(DfV<5.3)))
	{
		DfV1 = 4.8;		DfV2 = 5.3;
	}
	else
	{
		DfV1 = DfV;		DfV2 = DfV;
	}

	if(DfV1==DfV2)
		PRtv = Table_3_VI0( DoffV, DfV1, Xsys, Xcolor);
	else
	{
		double PRtv1 = Table_3_VI0( DoffV, DfV1, Xsys, Xcolor);
		double PRtv2 = Table_3_VI0( DoffV, DfV2, Xsys, Xcolor);

		PRtv = PRtv1+(DfV-DfV1)*(PRtv2-PRtv1)/(DfV2-DfV1);
	}
	return PRtv;
}

double CGE89_Functions::Table_3_VI0(double DoffV,double DfV,CString Xsys,CString Xcolor)
{
	double DoffV0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
	double aPRtv1[] = {32,31,28,25,22,20,19,20,22,25,28,31,32,31,28,25,22,20,19,20,22,25,28,31,32,31,28,25,22,20,19,20,22,25,28,31,32};
	double aPRtv2[] = {23,20,17,13,10,8,7,8,10,13,17,20,23,20,17,13,10,8,7,8,10,13,17,20,23,20,17,13,10,8,7,8,10,13,17,20,23};
	double aPRtv3[] = {44,43,39,34,30,28,27,28,30,34,39,43,44,43,39,34,30,28,27,28,30,34,39,43,44,43,39,34,30,28,27,28,30,34,39,43,44};
	double aPRtv4[] = {47,46,42,36,32,30,29,30,32,36,42,46,47,46,42,36,32,30,29,30,32,36,42,46,47,46,42,36,32,30,29,30,32,36,42,46,47};
	double aPRtv5[] = {50,49,45,39,35,32,31,32,35,39,45,49,50,49,45,39,35,32,31,32,35,39,45,49,50,49,45,39,35,32,31,32,35,39,45,49,50};
	double aPRtv6[] = {44,42,39,35,32,30,29,30,32,35,39,42,44,42,39,35,32,30,29,30,32,35,39,42,44,42,39,35,32,30,29,30,32,35,39,42,44};
	double aPRtv7[] = {36,34,32,29,27,25,24,25,27,29,32,34,36,34,32,29,27,25,24,25,27,29,32,34,36,34,32,29,27,25,24,25,27,29,32,34,36};
	double aPRtv8[] = {35,39,42,45,42,39,35,35,39,42,39,35,35,39,42,45,42,39,35,35,39,42,39,35,35,39,42,45,42,39,35,35,39,42,39,35,35};
	double aPRtv9[] = {18,20,22,25,22,20,18,18,20,22,20,18,18,20,22,25,22,20,18,18,20,22,20,18,18,20,22,25,22,20,18,18,20,22,20,18,18};
	double aPRtv10[] = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40};
	double aPRtv11[] = {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25};

	double aPRtv0[37];	int i;

	if(((Xsys=="H")||(Xsys=="I")||(Xsys=="K1"))&&(DfV==-1.25))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv1[i];
	else if(((Xsys=="B")||(Xsys=="G"))&&(DfV==-1.25))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv2[i];
	else if(DfV==-0.5)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv3[i];
	else if(DfV==0.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv4[i];
	else if(DfV==0.5)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv5[i];
	else if(DfV==1.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv5[i];
	else if(DfV==2.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv6[i];
	else if(DfV==3.0)
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv7[i];
	else if((DfV>=3.6)&&(DfV<=4.8)&&(Xcolor="PAL"))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv8[i];
	else if(((DfV>=5.7)&&(DfV<=6.0)&&(Xcolor="PAL"))&& !((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv9[i];
	else if(((DfV>=5.3)&&(DfV<=6.0)&&(Xcolor="PAL"))&& ((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv9[i];
	else if((DfV>=3.6)&&(DfV<=4.8)&&(Xcolor="SECAM"))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv10[i];
	else if(((DfV>=5.7)&&(DfV<=6.0)&&(Xcolor="SECAM"))&& !((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv11[i];
	else if(((DfV>=5.3)&&(DfV<=6.0)&&(Xcolor="SECAM"))&& ((Xsys=="B")||(Xsys=="G")))
		for(i=0;i<37;i++)		aPRtv0[i] = aPRtv11[i];

	double PRtv = Interp2(DoffV0,aPRtv0, DoffV,37);
	return PRtv;
}


////////////////////////////Cord. Distance Calculation//////////////////////////////////////

int CGE89_Functions::GE89_BAND1345(CString cty,double FreqXa) 
{
	int BandNUM = 0;
	BOOL ctyIII = ((cty=="BOT")||(cty=="LSO")||(cty=="MWI")||(cty=="MOZ")||(cty=="NMB")||(cty=="AFS")||(cty=="SWZ")||(cty=="ZMB")||(cty=="ZWE"));

	if((FreqXa>= 47.0)&&(FreqXa<= 68.0))
		BandNUM = 1;
	else if((FreqXa>= 174.0)&&(FreqXa<= 230.0))
		BandNUM = 3;
	else if((((FreqXa>= 230.0)&&(FreqXa<= 238.0))||((FreqXa>= 246.0)&&(FreqXa<= 254.0)))&&(ctyIII))
		BandNUM = 3;
	else if((FreqXa>= 470.0)&&(FreqXa<= 582.0))
		BandNUM = 4;
	else if((FreqXa> 582.0)&&(FreqXa<= 862.0))
		BandNUM = 5;

	return BandNUM;
}



BOOL CGE89_Functions::GE89_BAND(CString cty,double FreqXa) 
{
/*
	if(((FreqXa>= 47.0)&&(FreqXa<= 68.0))||((FreqXa>=174.0)&&(FreqXa<=230.0))||((FreqXa>=470.0)&&(FreqXa<=862.0)))
		return TRUE;
	else if (((FreqXa> 230.0)&&(FreqXa<=238.0))||((FreqXa>= 246.0)&&(FreqXa<=254.0)))
	{
		if((cty=="BOT")||(cty=="LSO")||(cty=="MWI")||(cty=="MOZ")||(cty=="NMB")||(cty=="AFS")||(cty=="SWZ")||(cty=="ZMB")||(cty=="ZWE"))
			return TRUE;
	}
	return FALSE;
*/

	if((FreqXa>= 47.0)&&(FreqXa<= 68.0))
		return TRUE;
	else if (((FreqXa> 230.0)&&(FreqXa<=238.0))||((FreqXa>= 246.0)&&(FreqXa<=254.0)))
	{
		if((cty=="BOT")||(cty=="LSO")||(cty=="MWI")||(cty=="MOZ")||(cty=="NMB")||(cty=="AFS")||(cty=="SWZ")||(cty=="ZMB")||(cty=="ZWE"))
			return TRUE;
	}
	return FALSE;
}


double CGE89_Functions::GE89_Dcord(CString Zone,double Heff,double ERP_W,double FreqXa) 
{
	double Dcord = 0;
	double Heff0 = max(Heff,75.0);
	ERP_W = max(ERP_W,1.0);

	if((Heff0==75.0)||(Heff0==300.0)||(Heff0==1200.0))
		Dcord = GE89_Dcord0(Zone,Heff0,ERP_W,FreqXa) ;
	else
	{
		double Heff1 , Heff2 , Dcord1 , Dcord2;
		if((Heff0>75.0)&&(Heff0<300.0))
		{
			Heff1 = 75;
			Heff2 = 300;
		}
		else if(Heff0>300.0)
		{
			Heff1 = 300;
			Heff2 = 1200;
		}
		Dcord1 = GE89_Dcord0(Zone,Heff1,ERP_W,FreqXa) ;
		Dcord2 = GE89_Dcord0(Zone,Heff2,ERP_W,FreqXa) ;
		Dcord = Dcord1 + (Heff0-Heff1)*(Dcord2-Dcord1)/(Heff2-Heff1);
	}

	return Dcord;
}

double CGE89_Functions::GE89_Dcord0(CString Zone,double Heff,double ERP_W,double FreqXa) 
{
	double Dcord = 0;

	if		((FreqXa>= 47.0)&&(FreqXa<= 68.0))	Dcord = TABLE_I  (Zone,Heff,ERP_W) ;
	else if ((FreqXa>=174.0)&&(FreqXa<=254.0))	Dcord = TABLE_II (Zone,Heff,ERP_W) ;
	else if ((FreqXa>=470.0)&&(FreqXa<=582.0))	Dcord = TABLE_III(Zone,Heff,ERP_W) ;
	else if ((FreqXa> 582.0)&&(FreqXa<=862.0))	Dcord = TABLE_IV (Zone,Heff,ERP_W) ;

	return Dcord;
}

double CGE89_Functions::TABLE_I(CString Zone,double Heff,double ERP_W) 
{
//	TABLE I  — Band 47 - 68 MHz Coordination distance limits (km)

	double Heff0[] = {75,300,1200};
	double Erp0[] = {1,10,100,1000,10000,100000};
	double Erp0log[] = {0,1,2,3,4,5};

	double aDi0_1[]  = {600, 640, 710, 490, 530, 600, 380, 420, 490, 280, 310, 380, 170, 210, 290, 100, 130, 200};
	double aDi0_2[]  = {410, 450, 500, 320, 360, 410, 240, 280, 340, 180, 210, 270, 130, 160, 220, 90, 120, 170};
	double aDi0_3[]  = {480, 510, 560, 380, 420, 480, 290, 340, 390, 210, 260, 330, 140, 190, 270, 85, 120, 210};
	double aDi0_4[]  = {1050, 1050, 1050, 830, 870, 950, 630, 670, 750, 450, 490, 560, 300, 330, 410, 170, 205, 290};
	double aDi0_A[]  = {1150, 1150, 1150, 1050, 1050, 1050, 900, 960, 1000, 640, 700, 800, 430, 470, 580, 240, 290, 410};
	double aDi0_B[]  = {1100, 1100, 1100, 1000, 1000, 1000, 760, 810, 880, 540, 590, 670, 360, 400, 490, 200, 240, 340};
	double aDi0_C[]  = {1500, 1500, 1500, 1200, 1200, 1200, 1050, 1050, 1050, 850, 850, 850, 550, 550, 550, 410, 410, 410};
	double aDi0_C1[] = {1000, 1000, 1000, 820, 820, 820, 650, 650, 650, 490, 490, 490, 360, 360, 360, 240, 240, 240};

	double aDi0_1_75[6]  , aDi0_1_300[6]  , aDi0_1_1200[6];
	double aDi0_2_75[6]  , aDi0_2_300[6]  , aDi0_2_1200[6];
	double aDi0_3_75[6]  , aDi0_3_300[6]  , aDi0_3_1200[6];
	double aDi0_4_75[6]  , aDi0_4_300[6]  , aDi0_4_1200[6];
	double aDi0_A_75[6]  , aDi0_A_300[6]  , aDi0_A_1200[6];
	double aDi0_B_75[6]  , aDi0_B_300[6]  , aDi0_B_1200[6];
	double aDi0_C_75[6]  , aDi0_C_300[6]  , aDi0_C_1200[6];
	double aDi0_C1_75[6] , aDi0_C1_300[6] , aDi0_C1_1200[6];

	for (int i=0;i<6;i++)
	{
		aDi0_1_75[i]   = aDi0_1[15-3*i];		aDi0_1_300[i]  = aDi0_1[16-3*i];		aDi0_1_1200[i] = aDi0_1[17-3*i];
		aDi0_2_75[i]   = aDi0_2[15-3*i];		aDi0_2_300[i]  = aDi0_2[16-3*i];		aDi0_2_1200[i] = aDi0_2[17-3*i];
		aDi0_3_75[i]   = aDi0_3[15-3*i];		aDi0_3_300[i]  = aDi0_3[16-3*i];		aDi0_3_1200[i] = aDi0_3[17-3*i];
		aDi0_4_75[i]   = aDi0_4[15-3*i];		aDi0_4_300[i]  = aDi0_4[16-3*i];		aDi0_4_1200[i] = aDi0_4[17-3*i];
		aDi0_A_75[i]   = aDi0_A[15-3*i];		aDi0_A_300[i]  = aDi0_A[16-3*i];		aDi0_A_1200[i] = aDi0_A[17-3*i];
		aDi0_B_75[i]   = aDi0_B[15-3*i];		aDi0_B_300[i]  = aDi0_B[16-3*i];		aDi0_B_1200[i] = aDi0_B[17-3*i];
		aDi0_C_75[i]   = aDi0_C[15-3*i];		aDi0_C_300[i]  = aDi0_C[16-3*i];		aDi0_C_1200[i] = aDi0_C[17-3*i];
		aDi0_C1_75[i]   = aDi0_C1[15-3*i];		aDi0_C1_300[i]  = aDi0_C1[16-3*i];		aDi0_C1_1200[i] = aDi0_C1[17-3*i];
	}

	double Dcord = 0;

	if(Zone=="1")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_1_75,log10(ERP_W),6) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_1_300,log10(ERP_W),6) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_1_1200,log10(ERP_W),6) ;
	}
	else if(Zone=="2")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_2_75,log10(ERP_W),6) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_2_300,log10(ERP_W),6) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_2_1200,log10(ERP_W),6) ;
	}
	else if(Zone=="3")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_3_75,log10(ERP_W),6) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_3_300,log10(ERP_W),6) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_3_1200,log10(ERP_W),6) ;
	}
	else if(Zone=="4")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_4_75,log10(ERP_W),6) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_4_300,log10(ERP_W),6) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_4_1200,log10(ERP_W),6) ;
	}
	else if(Zone=="A")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_A_75,log10(ERP_W),6) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_A_300,log10(ERP_W),6) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_A_1200,log10(ERP_W),6) ;
	}
	else if(Zone=="B")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_B_75,log10(ERP_W),6) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_B_300,log10(ERP_W),6) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_B_1200,log10(ERP_W),6) ;
	}
	else if(Zone=="C")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_C_75,log10(ERP_W),6) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_C_300,log10(ERP_W),6) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_C_1200,log10(ERP_W),6) ;
	}
	else if(Zone=="C1")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_C1_75,log10(ERP_W),6) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_C1_300,log10(ERP_W),6) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_C1_1200,log10(ERP_W),6) ;
	}

	return Dcord;
}

double CGE89_Functions::TABLE_II(CString Zone,double Heff,double ERP_W) 
{
//	TABLE II — Band 174 - 254 MHz Coordination distance limits (km)

	double Heff0[] = {75,300,1200};
	double Erp0[] = {1,10,100,1000,10000,100000,200000};
	double Erp0log[] = {0,1,2,3,4,5,log10(200000.0)};

	double aDi0_1[]  = {560,590,660,530,560,630,420,450,520,310,340,410,200,240,310,120,150,230,60,90,160};
	double aDi0_2[]  = {370,410,460,350,380,440,270,300,360,200,230,290,140,180,230,100,130,190,60,90,140};
	double aDi0_3[]  = {440,470,530,410,440,500,320,360,420,230,280,340,160,210,280,100,140,230,60,90,170};
	double aDi0_4[]  = {1100,1100,1100,910,950,1030,720,750,820,520,550,630,350,390,460,220,250,330,120,150,230};
	double aDi0_A[]  = {1300,1300,1300,1200,1200,1200,1050,1050,1050,830,900,970,560,620,730,350,400,530,190,240,370};
	double aDi0_B[]  = {1200,1200,1200,1150,1150,1150,900,940,1020,650,710,780,440,490,570,270,310,410,150,190,290};
	double aDi0_C[]  = {1600,1600,1600,1400,1400,1400,1200,1200,1200,950,950,950,600,600,600,450,450,450,410,410,410};
	double aDi0_C1[] = {930,930,930,880,880,880,700,700,700,540,540,540,400,400,400,280,280,280,170,170,170};

	double aDi0_1_75[7]  , aDi0_1_300[7]  , aDi0_1_1200[7];
	double aDi0_2_75[7]  , aDi0_2_300[7]  , aDi0_2_1200[7];
	double aDi0_3_75[7]  , aDi0_3_300[7]  , aDi0_3_1200[7];
	double aDi0_4_75[7]  , aDi0_4_300[7]  , aDi0_4_1200[7];
	double aDi0_A_75[7]  , aDi0_A_300[7]  , aDi0_A_1200[7];
	double aDi0_B_75[7]  , aDi0_B_300[7]  , aDi0_B_1200[7];
	double aDi0_C_75[7]  , aDi0_C_300[7]  , aDi0_C_1200[7];
	double aDi0_C1_75[7] , aDi0_C1_300[7] , aDi0_C1_1200[7];

	for (int i=0;i<7;i++)
	{
		aDi0_1_75[i]   = aDi0_1[18-3*i];		aDi0_1_300[i]  = aDi0_1[19-3*i];		aDi0_1_1200[i] = aDi0_1[20-3*i];
		aDi0_2_75[i]   = aDi0_2[18-3*i];		aDi0_2_300[i]  = aDi0_2[19-3*i];		aDi0_2_1200[i] = aDi0_2[20-3*i];
		aDi0_3_75[i]   = aDi0_3[18-3*i];		aDi0_3_300[i]  = aDi0_3[19-3*i];		aDi0_3_1200[i] = aDi0_3[20-3*i];
		aDi0_4_75[i]   = aDi0_4[18-3*i];		aDi0_4_300[i]  = aDi0_4[19-3*i];		aDi0_4_1200[i] = aDi0_4[20-3*i];
		aDi0_A_75[i]   = aDi0_A[18-3*i];		aDi0_A_300[i]  = aDi0_A[19-3*i];		aDi0_A_1200[i] = aDi0_A[20-3*i];
		aDi0_B_75[i]   = aDi0_B[18-3*i];		aDi0_B_300[i]  = aDi0_B[19-3*i];		aDi0_B_1200[i] = aDi0_B[20-3*i];
		aDi0_C_75[i]   = aDi0_C[18-3*i];		aDi0_C_300[i]  = aDi0_C[19-3*i];		aDi0_C_1200[i] = aDi0_C[20-3*i];
		aDi0_C1_75[i]   = aDi0_C1[18-3*i];		aDi0_C1_300[i]  = aDi0_C1[19-3*i];		aDi0_C1_1200[i] = aDi0_C1[20-3*i];
	}

	double Dcord = 0;

	if(Zone=="1")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_1_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_1_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_1_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="2")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_2_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_2_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_2_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="3")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_3_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_3_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_3_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="4")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_4_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_4_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_4_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="A")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_A_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_A_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_A_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="B")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_B_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_B_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_B_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="C")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_C_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_C_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_C_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="C1")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_C1_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_C1_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_C1_1200,log10(ERP_W),7) ;
	}

	return Dcord;
}


double CGE89_Functions::TABLE_III(CString Zone,double Heff,double ERP_W) 
{
//	TABLE III — Bande 470 - 582 MHz Coordination distance limits (km)

	double Heff0[] = {75,300,1200};
	double Erp0[] = {1,10,100,1000,10000,100000,500000};
	double Erp0log[] = {0,1,2,3,4,5,log10(500000.0)};

	double aDi0_1[]  = {380,430,520,310,350,450,220,250,330,130,180,240,80,130,180,50,80,140,30,50,100};
	double aDi0_2[]  = {280,310,370,230,260,320,170,200,260,120,160,210,80,120,170,50,80,130,30,50,100};
	double aDi0_3[]  = {290,340,400,240,290,350,180,220,290,130,170,230,80,120,180,50,80,140,30,50,100};
	double aDi0_4[]  = {1300,1300,1300,1100,1100,1100,900,900,900,750,750,750,650,650,650,460,460,460,300,300,300};
	double aDi0_A[]  = {1400,1400,1400,1350,1350,1350,1100,1100,1100,900,900,900,750,750,750,650,650,650,460,460,460};
	double aDi0_B[]  = {1350,1350,1350,1200,1200,1200,1000,1000,1000,800,800,800,700,700,700,550,550,550,370,370,370};
	double aDi0_C[]  = {1500,1500,1500,1400,1400,1400,1200,1200,1200,1000,1000,1000,800,800,800,700,700,700,400,400,400};
	double aDi0_C1[] = {590,590,590,530,530,530,440,440,440,360,360,360,280,280,280,210,210,210,140,140,140};

	double aDi0_1_75[7]  , aDi0_1_300[7]  , aDi0_1_1200[7];
	double aDi0_2_75[7]  , aDi0_2_300[7]  , aDi0_2_1200[7];
	double aDi0_3_75[7]  , aDi0_3_300[7]  , aDi0_3_1200[7];
	double aDi0_4_75[7]  , aDi0_4_300[7]  , aDi0_4_1200[7];
	double aDi0_A_75[7]  , aDi0_A_300[7]  , aDi0_A_1200[7];
	double aDi0_B_75[7]  , aDi0_B_300[7]  , aDi0_B_1200[7];
	double aDi0_C_75[7]  , aDi0_C_300[7]  , aDi0_C_1200[7];
	double aDi0_C1_75[7] , aDi0_C1_300[7] , aDi0_C1_1200[7];

	for (int i=0;i<7;i++)
	{
		aDi0_1_75[i]   = aDi0_1[18-3*i];		aDi0_1_300[i]  = aDi0_1[19-3*i];		aDi0_1_1200[i] = aDi0_1[20-3*i];
		aDi0_2_75[i]   = aDi0_2[18-3*i];		aDi0_2_300[i]  = aDi0_2[19-3*i];		aDi0_2_1200[i] = aDi0_2[20-3*i];
		aDi0_3_75[i]   = aDi0_3[18-3*i];		aDi0_3_300[i]  = aDi0_3[19-3*i];		aDi0_3_1200[i] = aDi0_3[20-3*i];
		aDi0_4_75[i]   = aDi0_4[18-3*i];		aDi0_4_300[i]  = aDi0_4[19-3*i];		aDi0_4_1200[i] = aDi0_4[20-3*i];
		aDi0_A_75[i]   = aDi0_A[18-3*i];		aDi0_A_300[i]  = aDi0_A[19-3*i];		aDi0_A_1200[i] = aDi0_A[20-3*i];
		aDi0_B_75[i]   = aDi0_B[18-3*i];		aDi0_B_300[i]  = aDi0_B[19-3*i];		aDi0_B_1200[i] = aDi0_B[20-3*i];
		aDi0_C_75[i]   = aDi0_C[18-3*i];		aDi0_C_300[i]  = aDi0_C[19-3*i];		aDi0_C_1200[i] = aDi0_C[20-3*i];
		aDi0_C1_75[i]   = aDi0_C1[18-3*i];		aDi0_C1_300[i]  = aDi0_C1[19-3*i];		aDi0_C1_1200[i] = aDi0_C1[20-3*i];
	}

	double Dcord = 0;

	if(Zone=="1")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_1_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_1_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_1_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="2")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_2_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_2_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_2_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="3")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_3_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_3_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_3_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="4")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_4_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_4_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_4_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="A")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_A_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_A_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_A_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="B")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_B_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_B_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_B_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="C")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_C_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_C_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_C_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="C1")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_C1_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_C1_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_C1_1200,log10(ERP_W),7) ;
	}

	return Dcord;
}


double CGE89_Functions::TABLE_IV(CString Zone,double Heff,double ERP_W) 
{
//	TABLE IV — Band 582 - 862 MHz Coordination distance limits (km)

	double Heff0[] = {75,300,1200};
	double Erp0[] = {1,10,100,1000,10000,100000,500000};
	double Erp0log[] = {0,1,2,3,4,5,log10(500000.0)};

	double aDi0_1[]  = {330,370,460,260,300,380,170,210,280,100,150,210,60,100,160,40,60,120,25,50,90};
	double aDi0_2[]  = {240,280,340,200,230,290,150,180,240,100,130,190,60,100,150,40,65,120,25,50,90};
	double aDi0_3[]  = {260,300,370,210,250,320,160,190,260,110,150,210,60,100,160,35,65,120,20,40,90};
	double aDi0_4[]  = {1200,1200,1200,1000,1000,1000,800,800,800,650,650,650,550,550,550,370,370,370,230,230,230};
	double aDi0_A[]  = {1300,1300,1300,1200,1200,1200,1000,1000,1000,800,800,800,650,650,650,550,550,550,370,370,370};
	double aDi0_B[]  = {1250,1250,1250,1100,1100,1100,900,900,900,700,700,700,600,600,600,460,460,460,300,300,300};
	double aDi0_C[]  = {1400,1400,1400,1250,1250,1250,1100,1100,1100,900,900,900,700,700,700,500,500,500,270,270,270};
	double aDi0_C1[] = {540,540,540,480,480,480,400,400,400,320,320,320,240,240,240,170,170,170,110,110,110};

	double aDi0_1_75[7]  , aDi0_1_300[7]  , aDi0_1_1200[7];
	double aDi0_2_75[7]  , aDi0_2_300[7]  , aDi0_2_1200[7];
	double aDi0_3_75[7]  , aDi0_3_300[7]  , aDi0_3_1200[7];
	double aDi0_4_75[7]  , aDi0_4_300[7]  , aDi0_4_1200[7];
	double aDi0_A_75[7]  , aDi0_A_300[7]  , aDi0_A_1200[7];
	double aDi0_B_75[7]  , aDi0_B_300[7]  , aDi0_B_1200[7];
	double aDi0_C_75[7]  , aDi0_C_300[7]  , aDi0_C_1200[7];
	double aDi0_C1_75[7] , aDi0_C1_300[7] , aDi0_C1_1200[7];

	for (int i=0;i<7;i++)
	{
		aDi0_1_75[i]   = aDi0_1[18-3*i];		aDi0_1_300[i]  = aDi0_1[19-3*i];		aDi0_1_1200[i] = aDi0_1[20-3*i];
		aDi0_2_75[i]   = aDi0_2[18-3*i];		aDi0_2_300[i]  = aDi0_2[19-3*i];		aDi0_2_1200[i] = aDi0_2[20-3*i];
		aDi0_3_75[i]   = aDi0_3[18-3*i];		aDi0_3_300[i]  = aDi0_3[19-3*i];		aDi0_3_1200[i] = aDi0_3[20-3*i];
		aDi0_4_75[i]   = aDi0_4[18-3*i];		aDi0_4_300[i]  = aDi0_4[19-3*i];		aDi0_4_1200[i] = aDi0_4[20-3*i];
		aDi0_A_75[i]   = aDi0_A[18-3*i];		aDi0_A_300[i]  = aDi0_A[19-3*i];		aDi0_A_1200[i] = aDi0_A[20-3*i];
		aDi0_B_75[i]   = aDi0_B[18-3*i];		aDi0_B_300[i]  = aDi0_B[19-3*i];		aDi0_B_1200[i] = aDi0_B[20-3*i];
		aDi0_C_75[i]   = aDi0_C[18-3*i];		aDi0_C_300[i]  = aDi0_C[19-3*i];		aDi0_C_1200[i] = aDi0_C[20-3*i];
		aDi0_C1_75[i]   = aDi0_C1[18-3*i];		aDi0_C1_300[i]  = aDi0_C1[19-3*i];		aDi0_C1_1200[i] = aDi0_C1[20-3*i];
	}

	double Dcord = 0;

	if(Zone=="1")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_1_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_1_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_1_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="2")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_2_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_2_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_2_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="3")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_3_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_3_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_3_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="4")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_4_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_4_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_4_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="A")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_A_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_A_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_A_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="B")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_B_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_B_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_B_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="C")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_C_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_C_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_C_1200,log10(ERP_W),7) ;
	}
	else if(Zone=="C1")
	{
		if	   (Heff==75)
			Dcord = Interp2(Erp0log,aDi0_C1_75,log10(ERP_W),7) ;
		else if(Heff==300)
			Dcord = Interp2(Erp0log,aDi0_C1_300,log10(ERP_W),7) ;
		else if(Heff==1200)
			Dcord = Interp2(Erp0log,aDi0_C1_1200,log10(ERP_W),7) ;
	}

	return Dcord;
}


double CGE89_Functions::Interp2(double *D0,double *E0,double d,int num) 
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



////////////////////////////Fst. Calculation//////////////////////////////////////
void CGE89_Functions::F_2_2(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{63.80,56.10,50.20,45.50,41.60,38.10,35.00,32.30,30.00,26.00,22.60,20.00,17.60,15.00,7.00,1.00,-4.50,-9.40,-14.10,-18.10,-22.30,-26.50,-30.60,-34.60,-38.70,-42.90,-47.00,-51.10,-55.20,-59.30,-63.70,-68.00};
	double aE075[]	=	{70.70,62.20,56.20,51.20,47.10,43.90,40.80,38.40,36.00,31.40,27.70,24.20,21.50,18.70,9.20,2.10,-3.40,-8.20,-13.20,-17.40,-21.60,-25.70,-29.80,-33.80,-38.00,-42.10,-46.20,-50.30,-54.40,-58.40,-62.60,-66.80};
	double aE0150[]	=	{77.80,69.10,63.20,58.30,54.30,51.20,48.20,45.10,43.10,37.70,33.70,30.00,26.70,23.40,11.70,3.70,-1.60,-6.90,-11.50,-16.10,-20.20,-24.30,-28.30,-32.30,-36.50,-40.70,-44.80,-48.80,-52.90,-56.90,-61.10,-65.20};
	double aE0300[]	=	{84.50,76.10,70.80,66.20,62.20,59.00,55.80,52.70,50.20,45.00,40.80,36.30,32.70,28.80,15.20,6.60,0.70,-4.90,-9.60,-14.00,-18.30,-22.50,-26.60,-30.70,-34.80,-39.10,-43.20,-47.20,-51.30,-55.30,-59.40,-63.50};
	double aE0600[]	=	{87.00,81.60,77.30,73.10,69.50,66.30,63.40,60.60,58.30,53.70,49.40,45.00,41.30,37.20,22.00,11.30,4.60,-1.30,-6.90,-11.50,-15.70,-19.90,-24.10,-28.20,-32.30,-36.40,-40.10,-44.60,-48.70,-52.70,-56.90,-61.10};
	double aE01200[]=	{87.00,83.40,80.90,78.30,76.20,74.00,71.90,70.00,67.90,63.80,59.80,55.70,51.90,48.00,31.70,19.40,10.60,3.00,-2.60,-7.50,-12.00,-16.50,-20.60,-24.70,-29.00,-33.20,-37.30,-41.30,-45.40,-49.40,-53.70,-58.00};
	double aE0fs[]	=	{86.84,83.68,81.05,78.81,77.36,75.92,74.86,73.94,72.89,71.18,70,68.94,67.76,66.97,63.42,61.05,58.94,57.36,56.18,55.13,54.07,53.28,52.36,51.71,50.78,50.13,49.34,48.55,48.02,47.5,46.97,46.44};

	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_3(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{63.80,56.40,50.70,46.60,42.90,39.80,37.20,35.00,33.40,31.20,29.20,27.50,26.00,24.40,17.80,11.50,5.70,0.30,-4.80,-9.80,-14.30,-18.70,-23.20,-27.70,-32.10,-36.40,-40.80,-45.10,-49.50,-53.80,-57.90,-61.90};
	double aE075[]	=	{71.00,62.60,57.00,52.20,48.10,45.00,42.50,40.00,38.30,35.30,32.80,30.50,28.40,26.70,19.70,13.00,7.50,1.70,-3.60,-8.70,-13.30,-17.80,-22.10,-26.40,-30.90,-35.30,-39.60,-43.90,-48.30,-52.70,-56.90,-61.00};
	double aE0150[]	=	{78.00,69.70,63.60,58.60,54.80,51.40,48.20,45.90,43.60,40.00,37.10,34.40,32.50,30.60,21.80,14.80,8.80,3.10,-2.40,-7.50,-12.10,-16.60,-21.00,-25.30,-29.70,-34.00,-38.40,-42.80,-47.30,-51.80,-56.20,-60.60};
	double aE0300[]	=	{84.50,77.10,71.20,66.60,62.60,59.20,56.20,53.80,51.20,47.10,43.30,40.00,37.40,34.80,25.30,17.70,11.30,5.00,-0.40,-5.60,-10.30,-14.90,-19.20,-23.50,-27.90,-32.30,-36.70,-41.10,-45.60,-50.00,-54.40,-58.70};
	double aE0600[]	=	{87.00,82.30,78.30,74.00,70.10,66.80,63.50,60.60,58.30,53.70,49.70,46.20,43.30,40.10,29.60,21.40,14.90,8.50,3.10,-2.20,-7.10,-12.00,-16.40,-20.70,-25.10,-29.50,-33.90,-38.20,-42.70,-47.10,-51.50,-55.80};
	double aE01200[]=	{87.00,83.40,80.90,78.50,76.30,74.20,72.10,70.00,67.90,63.80,60.00,56.20,53.10,49.50,36.50,27.30,20.30,13.50,7.70,2.10,-2.90,-7.80,-12.50,-17.10,-21.50,-25.80,-30.20,-34.60,-39.10,-43.50,-47.90,-52.30};
	
	double aE0fs[]	=	{86.83,84.18,81.41,79.56,77.85,76.26,75.2,74.02,73.22,71.51,70.05,68.87,67.94,66.75,63.45,61.21,58.96,57.38,56.32,55,54.08,53.15,52.36,51.57,50.77,49.98,49.32,48.66,47.87,47.34,46.81,46.55};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_4(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{64.11,56.19,51.3,47.47,44.3,41.93,40.08,38.49,36.91,34.79,32.68,30.7,28.98,27.4,20.66,15.12,10.1,4.69,-0.19,-4.55,-9.3,-13.66,-18.02,-22.24,-26.47,-30.96,-35.19,-39.41,-43.11,-46.81,-50.31,-53.62};
	double aE075[]	=	{70.98,62.92,57.24,52.89,49.45,46.81,44.83,42.98,41.27,38.49,35.85,33.47,31.63,29.78,22.91,17.5,12.21,6.67,1.91,-2.7,-7.19,-11.94,-16.43,-20.92,-25.15,-29.38,-33.6,-37.56,-41.53,-45.22,-48.66,-51.91};
	double aE0150[]	=	{78.24,69.79,63.98,59.62,55.92,52.89,50.51,48.4,46.42,43.11,40.08,37.04,34.66,32.55,25.15,20,14.59,9.04,3.89,-0.72,-5.34,-10.1,-14.59,-19.34,-23.57,-27.53,-31.75,-35.98,-39.94,-43.64,-46.94,-50};
	double aE0300[]	=	{84.05,76.92,71.37,66.62,62.66,59.36,56.58,54.21,51.83,48.13,45.1,42.19,39.94,37.7,29.38,23.31,17.63,11.16,6.01,1.38,-3.36,-7.98,-12.74,-17.23,-21.45,-25.68,-29.64,-33.87,-38.09,-41.79,-44.96,-47.6};
	double aE0600[]	=	{86.96,83.13,79.03,74.81,70.85,67.41,64.77,62.13,59.49,55.26,51.43,48.13,45.62,43.11,33.74,26.87,20.93,14.59,9.04,4.16,-0.98,-5.87,-10.62,-15.11,-19.47,-23.57,-27.92,-31.75,-35.85,-39.68,-43.11,-45.49};
	double aE01200[]=	{86.96,84.45,82.07,79.43,77.05,74.54,72.17,70.05,67.94,64.24,60.68,57.24,54.21,51.04,39.81,30.7,24.1,17.63,11.95,6.8,1.78,-3.23,-8.11,-12.74,-17.23,-21.32,-25.41,-29.38,-33.21,-37.04,-40.2,-42.85};
	double aE0fs[]	=	{86.96,84.45,82.2,80.09,78.24,76.66,75.34,74.15,72.96,71.24,69.92,68.47,67.28,66.36,63.72,61.73,60.02,58.17,56.58,55.26,53.94,52.89,52.09,51.17,50.51,49.85,49.32,48.92,48.53,48.26,47.87,47.6};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_11(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{62.87,56.39,51.63,47.98,45.01,42.52,40.38,38.14,36.15,32.71,29.4,26.23,23.58,21.2,10.48,3.87,-1.81,-6.84,-11.34,-15.83,-19.8,-23.77,-28.01,-31.97,-36.21,-40.44,-44.41,-48.64,-52.62,-56.37,-59.92,-63.28};
	double aE075[]	=	{68.43,61.55,56.66,53.01,50.04,47.69,45.67,43.43,41.44,38,34.83,31.65,28.48,25.3,12.73,5.46,-0.36,-5.38,-10.01,-14.25,-18.48,-22.45,-26.55,-30.65,-34.89,-38.99,-43.09,-47.32,-51.3,-55.05,-58.59,-61.96};
	double aE0150[]	=	{76.63,70.02,64.99,61.13,57.98,55.35,53.08,50.63,48.45,44.88,41.18,37.47,33.77,30.33,15.64,7.31,1.09,-4.06,-8.69,-12.92,-17.16,-20.99,-25.1,-29.33,-33.56,-37.8,-41.77,-46,-50,-53.76,-57.33,-60.71};
	double aE0300[]	=	{84.31,77.69,72.53,68.74,65.65,63.09,60.89,58.16,55.73,51.5,47.13,42.63,38.8,35.09,19.08,10.35,3.74,-1.68,-6.31,-10.67,-15.04,-19.01,-22.98,-27.21,-31.45,-35.68,-39.78,-43.88,-48.12,-52.11,-55.88,-59.46};
	double aE0600[]	=	{86.95,81.66,77.29,73.87,71.08,68.73,66.71,64.61,62.74,59.17,55.2,51.1,47.66,44.48,26.23,14.85,7.31,1.62,-3.53,-8.03,-12.39,-16.36,-20.33,-24.57,-28.8,-32.9,-37,-41.24,-45.47,-49.44,-53.19,-56.75};
	double aE01200[]=	{86.95,84.17,81.4,78.85,76.77,74.92,73.33,71.51,69.89,67.11,64.2,61.29,58.51,55.6,34.96,21.2,11.67,5.19,-0.09,-4.99,-9.48,-13.45,-17.69,-21.66,-26.02,-30.39,-34.62,-38.59,-42.82,-46.79,-50.55,-54.11};
	double aE0fs[]	=	{86.95,84.17,81.4,79.35,77.69,76.34,75.18,74.06,73.06,71.34,70.02,68.56,67.77,66.97,63.8,61.55,59.57,57.71,55.99,54.67,53.08,52.03,50.97,50.17,49.51,48.59,48.19,47.79,47.53,47.26,47,47.13};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_12(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{63.80,57.30,52.40,49.20,46.40,44.20,42.40,41.10,40.40,38.20,36.20,34.50,33.00,31.40,22.80,15.90,11.60,7.40,3.60,0.00,-2.80,-5.60,-8.40,-11.10,-13.40,-15.70,-17.80,-19.90,-22.00,-24.00,-25.90,-27.70};
	double aE075[]	=	{71.00,63.50,58.80,54.80,51.60,49.40,47.80,46.10,45.30,42.30,39.80,37.50,35.40,33.70,24.70,18.00,13.40,9.10,5.10,1.40,-1.60,-4.50,-7.20,-9.90,-12.30,-14.70,-16.60,-18.50,-20.60,-22.60,-24.60,-26.50};
	double aE0150[]	=	{78.00,70.60,65.30,61.20,58.30,55.80,53.40,52.00,50.60,47.00,44.10,41.40,39.50,37.60,26.80,21.60,16.20,11.10,6.80,2.90,-0.20,-3.30,-6.00,-8.70,-11.10,-13.50,-15.70,-17.80,-19.80,-21.80,-23.60,-25.30};
	double aE0300[]	=	{84.50,78.00,72.90,69.20,66.10,63.60,61.40,59.90,58.20,54.10,50.30,47.00,44.40,41.80,30.30,24.50,18.80,13.30,8.90,4.80,1.50,-1.90,-4.70,-7.40,-9.90,-12.30,-14.60,-16.90,-18.70,-20.50,-22.50,-24.40};
	double aE0600[]	=	{87.00,82.30,78.30,74.80,72.00,69.50,67.50,65.90,64.60,60.70,56.70,53.20,50.30,47.10,34.60,28.30,21.80,15.60,11.20,7.00,3.50,0.00,-2.90,-5.70,-8.30,-10.80,-13.00,-15.20,-17.40,-19.50,-21.30,-23.00};
	double aE01200[]=	{87.00,83.40,80.90,79.00,77.20,75.50,73.70,72.10,70.60,67.90,65.50,63.20,60.10,56.50,41.50,34.60,27.00,19.70,14.70,10.00,6.30,2.60,-0.30,-3.20,-6.20,-9.10,-11.40,-13.60,-15.80,-17.90,-20.00,-22.10 };   

	double aE0fs[]	=	{86.96,83.79,81.28,79.17,77.45,76.17,75.07,74.02,73.09,71.37,70.05,68.87,67.81,66.88,63.45,61.21,59.23,57.38,55.92,54.74,53.55,52.62,51.57,50.77,49.98,49.45,48.92,48.66,48.13,47.87,47.6,47.47};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_13(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{64.80,60.40,57.50,55.30,53.30,52.10,50.60,49.60,48.40,46.70,45.00,43.60,42.30,41.20,36.40,32.60,29.00,25.40,22.20,19.20,16.80,14.30,12.30,10.20,8.90,7.50,6.30,5.00,3.90,2.80,2.00,1.20};
	double aE075[]	=	{71.10,66.00,62.40,59.80,57.40,55.70,54.20,52.90,51.90,49.70,47.80,46.20,45.00,43.80,38.60,34.70,30.80,27.10,23.90,20.70,18.30,15.80,13.80,11.80,10.10,8.40,7.10,5.80,4.70,3.60,2.70,1.80};
	double aE0150[]	=	{78.00,72.20,68.10,65.00,62.60,60.50,58.70,57.30,56.00,53.70,51.60,49.70,48.20,46.90,40.90,36.60,32.70,28.80,25.30,22.10,19.60,17.00,14.80,12.60,10.90,9.20,7.90,6.50,5.40,4.20,3.30,2.40};
	double aE0300[]	=	{84.50,78.10,73.70,70.10,67.00,64.80,62.70,61.30,59.90,57.20,55.00,53.00,51.50,50.00,43.80,38.40,34.00,30.00,26.50,23.20,20.60,17.90,15.70,13.40,11.70,10.00,8.70,7.30,6.20,5.00,4.00,2.90};
	double aE0600[]	=	{87.00,82.30,78.30,74.80,72.00,69.50,67.50,65.90,64.60,61.80,59.50,57.40,55.60,54.10,47.10,41.70,36.80,32.20,28.50,25.00,22.30,19.60,17.30,15.00,13.10,11.20,9.80,8.30,7.10,5.80,4.80,3.70};
	double aE01200[]=	{87.00,83.40,80.90,79.00,77.20,75.50,73.70,72.10,70.60,67.90,65.50,63.60,61.70,59.80,52.00,45.20,39.90,35.00,31.00,27.30,24.60,21.80,19.40,16.90,14.90,12.90,11.20,9.40,8.10,6.80,5.60,4.30};

	double aE0fs[]	=	{86.96,84.05,81.81,79.83,77.71,76.26,75.07,74.02,72.83,70.98,69.39,68.21,67.15,66.22,63.19,61.21,59.75,58.17,56.72,55.26,54.21,53.15,52.09,51.17,50.51,49.72,49.19,48.79,48.53,48,47.87,47.6};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_14(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{61.29,52.55,46.47,41.84,37.74,34.3,31.39,29.01,26.49,22.39,18.69,15.91,13,10.22,0.16,-6.04,-12.53,-17.69,-22.58,-27.48,-32.24,-36.74,-41.37,-45.6,-50,-54.06,-57.85,-61.39,-64.72,-67.86,-70.82,-73.64};
	double aE075[]	=	{68.69,60.23,53.88,48.72,43.82,39.99,36.81,34.16,31.39,26.62,22.65,19.21,16.17,13,1.88,-4.59,-11.34,-16.5,-21.66,-26.42,-31.18,-35.81,-40.18,-44.68,-48.91,-52.83,-56.48,-59.89,-63.1,-66.12,-68.98,-71.69};
	double aE0150[]	=	{76.77,67.9,61.82,56.39,51.63,47.39,44.22,41.18,38.13,32.18,27.29,23.45,20.14,16.44,4.13,-2.47,-9.62,-14.78,-19.8,-24.83,-29.59,-34.22,-38.59,-42.96,-47.32,-51.36,-55.13,-58.65,-61.95,-65.07,-68.02,-70.82};
	double aE0300[]	=	{84.31,76.77,70.81,65.52,60.76,56.52,52.95,49.78,46.34,39.72,34.43,30.2,26.36,22.52,8.5,0.3,-6.97,-12.53,-17.95,-22.98,-27.74,-32.37,-36.74,-41.24,-45.6,-50,-54.09,-57.91,-61.5,-64.89,-68.1,-71.14};
	double aE0600[]	=	{86.95,83.38,79.01,74.91,70.68,66.45,62.74,59.3,55.86,49.25,43.82,39.19,35.09,30.59,14.32,5.19,-3.27,-9.09,-14.78,-20.2,-25.1,-29.73,-34.36,-38.85,-43.09,-47.45,-51.52,-55.32,-58.89,-62.26,-65.44,-68.47};
	double aE01200[]=	{86.95,83.38,80.73,78.62,76.5,74.38,72.13,69.75,67.37,62.21,56.92,52.16,47.79,42.9,23.98,12.34,2.81,-4.06,-10.15,-15.83,-20.99,-25.89,-30.78,-35.28,-39.65,-44.15,-48.38,-52.34,-56.06,-59.57,-62.89,-66.03};
	double aE0fs[]	=	{86.95,83.38,80.73,78.75,77.16,75.84,74.78,73.72,72.66,70.94,69.36,68.3,67.24,66.31,63.01,61.29,59.17,57.58,56.26,54.94,53.88,52.82,52.03,51.1,50.44,49.64,49.11,48.85,48.32,48.06,47.53,47.26};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_15(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{62.18,52.69,46.36,41.49,37.4,34.5,31.6,29.49,27.51,24.75,22.77,20.53,18.68,16.31,8.27,2.6,-3.45,-8.99,-14.13,-18.88,-23.36,-27.84,-32.32,-36.54,-41.02,-45.77,-50.19,-54.32,-58.2,-61.86,-65.32,-68.61};
	double aE075[]	=	{69.43,60.07,53.88,49,44.52,41.09,37.93,35.42,33.05,28.96,26.33,23.69,21.32,18.95,9.98,4.05,-1.87,-7.41,-12.55,-17.3,-22.04,-26.52,-30.87,-35.22,-39.84,-44.32,-48.93,-53.25,-57.3,-61.12,-64.74,-68.17};
	double aE0150[]	=	{76.15,67.45,60.86,55.59,51.11,47.81,44.39,41.62,38.98,34.1,30.55,27.12,24.48,22.11,12.22,6.03,-0.03,-5.7,-10.97,-15.98,-20.72,-25.2,-29.69,-34.17,-38.39,-42.87,-47.48,-51.8,-55.85,-59.67,-63.29,-66.72};
	double aE0300[]	=	{84.06,75.5,69.56,64.82,60.07,56.51,52.56,49.53,46.63,41.49,37.4,32.79,29.36,26.2,15.25,8.4,2.34,-3.45,-8.86,-14,-19.01,-23.62,-28.1,-32.59,-37.07,-41.42,-46.03,-50.35,-54.4,-58.22,-61.84,-65.27};
	double aE0600[]	=	{86.96,83.14,78.53,73.78,69.43,65.87,62.18,58.89,55.59,49.66,45.44,41.22,37.4,32.92,20.4,12.49,5.5,-0.42,-5.96,-11.23,-16.24,-20.85,-25.6,-29.95,-34.43,-38.91,-43.53,-47.61,-51.45,-55.07,-58.49,-61.74};
	double aE01200[]=	{86.96,83.54,81.03,78.92,76.55,74.44,71.67,69.17,66.4,61.52,57.3,52.43,48.47,44.25,27.51,18.29,11.04,4.45,-1.48,-7.15,-12.29,-17.03,-21.78,-26.52,-30.87,-35.35,-39.97,-44.19,-48.4,-52.38,-56.14,-59.71};
	double aE0fs[]	=	{86.96,83.54,81.03,78.92,77.08,75.63,74.18,73.12,72.2,70.49,69.17,68.11,67.19,66.4,63.37,61.39,59.81,57.96,56.38,55.06,53.88,52.95,51.9,51.11,50.45,49.79,49.4,49,48.74,48.34,47.95,47.95};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_16(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{65.3,57.11,51.17,46.81,42.98,39.94,37.7,35.72,33.74,30.7,28.19,26.08,24.36,22.65,15.12,9.7,4.42,-0.45,-5.34,-9.57,-14.06,-18.28,-22.51,-26.73,-30.96,-35.19,-39.54,-43.77,-47.74,-51.48,-55.02,-58.38};
	double aE075[]	=	{70.58,62.92,57.11,52.36,48.4,45.36,42.85,40.74,38.62,35.06,32.15,29.78,27.53,25.42,16.7,11.16,5.74,0.86,-4.02,-8.25,-12.74,-17.23,-21.32,-25.55,-29.9,-34,-38.22,-42.58,-46.68,-50.53,-54.19,-57.65};
	double aE0150[]	=	{76.13,68.34,62.79,58.57,54.87,51.83,49.19,46.81,44.7,40.47,37.04,34.4,31.89,29.38,20,13.8,7.59,2.57,-2.3,-6.79,-11.28,-15.64,-19.87,-24.09,-28.32,-32.81,-37.04,-41.39,-45.75,-50,-54.01,-57.82};
	double aE0300[]	=	{83.26,76.13,70.58,66.09,62.13,58.7,56.06,53.68,51.04,46.55,42.85,39.81,37.04,34.13,23.97,17.23,10.36,4.95,0.06,-4.28,-8.77,-13.26,-17.75,-22.11,-26.47,-30.7,-35.19,-39.68,-44.17,-48.52,-52.65,-56.56};
	double aE0600[]	=	{86.96,81.94,77.58,73.49,69.92,66.62,64.11,61.87,59.49,55.53,51.7,48.4,45.36,42.19,30.3,20.8,13.27,7.59,2.7,-1.64,-6.4,-10.89,-15.38,-19.6,-24.09,-28.58,-32.81,-37.43,-41.92,-46.41,-50.66,-54.69};
	double aE01200[]=	{86.96,84.05,81.15,78.64,76.26,73.88,71.64,69.53,67.15,63.19,59.49,56.19,53.02,49.72,36.64,27.27,18.42,11.68,6.4,1.78,-2.96,-7.45,-12.21,-16.7,-20.92,-25.28,-29.77,-33.87,-38.09,-42.58,-46.81,-50.82};
	double aE0fs[]	=	{86.96,84.05,81.68,79.69,78.11,76.66,75.47,74.41,73.49,71.51,69.92,68.73,67.55,66.62,62.92,60.81,58.96,57.38,56.06,55,53.94,53.02,52.09,51.3,50.64,49.98,49.32,48.66,48.26,47.87,47.6,47.6};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_23(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{65.83,62.79,59.09,55.66,51.83,48.4,45.1,41.93,39.02,33.47,28.19,23.57,19.48,15.38,2.97,-4.42,-10.62,-16.83,-22.08,-26.62,-30.63,-34.22,-37.47,-40.43,-43.15,-45.67,-48.02,-50.22,-52.28,-54.23,-56.07,-57.82};
	double aE075[]	=	{71.64,68.21,64.9,61.6,58.17,54.74,51.57,48.66,45.62,39.55,33.61,28.46,23.7,19.08,5.74,-2.17,-8.64,-14.98,-20.34,-24.98,-29.08,-32.74,-36.05,-39.08,-41.86,-44.44,-46.84,-49.08,-51.19,-53.18,-55.06,-56.84};
	double aE0150[]	=	{77.45,74.15,70.98,67.68,64.24,61.07,58.3,55.53,52.49,45.76,38.76,33.08,27.93,22.91,8.65,-0.19,-6.79,-13.4,-19.21,-24.24,-28.68,-32.65,-36.24,-39.52,-42.54,-45.33,-47.94,-50.37,-52.65,-54.81,-56.85,-58.78};
	double aE0300[]	=	{83.52,80.22,77.19,74.28,71.11,68.34,65.7,62.79,59.62,52.75,45.76,39.28,32.81,27.27,11.68,2.57,-4.68,-11.28,-17.49,-22.87,-27.61,-31.85,-35.69,-39.19,-42.42,-45.4,-48.18,-50.78,-53.22,-55.52,-57.7,-59.76};
	double aE0600[]	=	{86.69,83.92,81.28,78.64,76,73.49,71.11,68.73,65.83,59.49,53.02,46.55,39.55,32.95,15.65,6.4,-0.72,-7.85,-13.92,-19.34,-24.12,-28.39,-32.25,-35.78,-39.03,-42.03,-44.83,-47.44,-49.9,-52.22,-54.41,-56.49};
	double aE01200[]=	{90,87.62,85.64,83.66,81.54,79.43,77.45,75.34,73.22,69,64.9,59.62,53.41,45.49,22.25,12.08,4.82,-2.17,-8.64,-14.19,-19.87,-24.95,-29.54,-33.74,-37.6,-41.17,-44.5,-47.61,-50.53,-53.29,-55.89,-58.36};
	double aE0fs[]	=	{86.69,82.86,80.62,78.64,76.92,75.47,74.41,73.22,72.17,70.71,69.26,68.21,67.28,66.22,62.92,60.55,58.7,57.11,55.79,54.74,53.68,52.62,51.83,51.04,50.25,49.72,48.92,48.4,47.87,47.6,47.47,47.47};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_24(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{66.22,63.06,60.41,58.3,56.45,54.6,53.41,52.23,50.91,48.53,46.42,44.83,43.25,41.66,35.98,31.89,27.93,24.23,20.53,17.1,13.67,10.36,7.06,3.89,0.99,-1.64,-4.15,-6.4,-8.64,-10.62,-12.6,-14.19};
	double aE075[]	=	{72.17,69.13,66.49,64.38,62.53,60.68,59.09,57.51,56.19,53.55,51.43,49.45,47.74,46.15,39.94,35.32,30.83,26.61,22.65,18.95,15.51,12.08,8.78,5.48,2.44,-0.32,-2.83,-5.08,-7.32,-9.43,-11.42,-13.26};
	double aE0150[]	=	{77.98,74.41,71.77,69.53,67.28,65.17,63.58,62,60.41,57.51,55.13,53.02,51.17,49.59,42.85,37.96,33.47,28.98,24.76,20.8,17.36,13.67,10.23,7.06,3.89,0.99,-1.64,-3.89,-6.13,-8.11,-10.23,-11.94};
	double aE0300[]	=	{83.92,80.35,77.58,75.2,72.83,70.85,69.13,67.41,65.7,62.66,59.89,57.64,55.53,53.41,46.02,41,36.12,31.63,27.14,22.91,19.21,15.51,11.82,8.65,5.48,2.57,-0.06,-2.44,-4.68,-6.79,-8.77,-10.49};
	double aE0600[]	=	{87.09,83.26,80.75,78.77,76.66,74.68,72.96,71.51,69.79,66.75,63.85,61.47,59.36,57.11,49.59,44.43,39.42,34.66,30.04,25.68,21.85,17.89,14.06,10.63,7.46,4.42,1.78,-0.72,-3.1,-5.34,-7.32,-8.91};
	double aE01200[]=	{90,86.56,83.92,81.81,79.69,77.71,76,74.54,73.09,70.05,67.41,65.3,63.19,61.21,53.41,48,42.85,38.1,33.61,29.25,25.02,20.8,16.97,13.4,9.97,7.06,4.16,1.52,-0.98,-3.23,-5.21,-6.79};
	double aE0fs[]	=	{86.96,83.39,80.75,78.77,77.19,75.73,74.68,73.62,72.56,70.85,69.26,68.21,67.28,66.36,63.45,61.34,59.62,57.9,56.58,55.26,54.47,53.41,52.62,51.7,51.04,50.25,49.45,48.92,48.4,47.87,47.34,47.21};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_25(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{66.4,65.87,65.08,64.69,64.29,63.76,63.5,63.24,62.97,62.45,61.92,61.39,61.13,60.86,59.15,57.17,53.88,49.92,46.36,43.07,40.43,37.53,34.76,32.39,29.89,27.51,25.14,22.9,20.79,18.68,16.7,14.73};
	double aE075[]	=	{70.88,70.22,69.56,68.9,68.25,67.59,67.06,66.66,66.14,65.35,64.69,64.03,63.5,62.84,60.07,57.96,53.88,49.92,46.36,43.07,40.43,37.53,34.76,32.39,29.89,27.51,25.14,22.9,20.79,18.68,16.7,14.73};
	double aE0150[]	=	{78.26,76.42,74.97,73.91,72.86,72.07,71.28,70.75,70.09,68.77,67.72,66.8,66,64.95,61,57.83,53.88,49.92,46.36,43.07,40.43,37.53,34.76,32.39,29.89,27.51,25.14,22.9,20.79,18.68,16.7,14.73};
	double aE0300[]	=	{83.01,80.77,79.05,77.74,76.55,75.5,74.44,73.78,72.86,71.28,69.96,68.9,67.98,66.8,62.45,58.89,53.88,49.92,46.36,43.07,40.43,37.53,34.76,32.39,29.89,27.51,25.14,22.9,20.79,18.68,16.7,14.73};
	double aE0600[]	=	{86.96,84.2,82.22,80.64,79.32,78.13,76.95,76.15,75.23,73.65,72.07,70.88,69.7,68.64,63.5,58.75,53.88,49.92,46.36,43.07,40.43,37.53,34.76,32.39,29.89,27.51,25.14,22.9,20.79,18.68,16.7,14.73};
	double aE01200[]=	{90,87.1,85.12,83.4,81.82,80.64,79.58,78.66,77.74,76.02,74.44,73.12,71.8,70.49,64.29,58.75,53.88,49.92,46.36,43.07,40.43,37.53,34.76,32.39,29.89,27.51,25.14,22.9,20.79,18.68,16.7,14.73};
	double aE0fs[]	=	{86.83,84.2,81.95,79.98,78.26,76.95,75.63,74.84,73.78,71.8,70.09,69.04,67.98,66.8,63.24,61.26,59.68,58.23,56.91,55.59,54.54,53.48,52.43,51.5,50.58,49.79,49.13,48.47,48.08,47.55,47.15,46.89};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_5(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{64.52,56.66,50.95,46.90,42.85,39.63,36.42,33.21,30.00,26.42,22.14,18.57,14.76,11.42,-1.66,-10.47,-17.38,-23.33,-28.57,-32.61,-36.66,-40.47,-44.28,-47.38,-50.48,-53.58,-56.68,-59.78,-62.88,-65.98,-69.08,-72.18};
	double aE075[]	=	{71.42,63.33,57.38,52.85,48.33,45.11,41.90,39.28,36.66,31.90,27.38,22.85,19.52,16.42,2.85,-7.14,-14.52,-20.23,-25.95,-30.47,-34.76,-38.57,-42.38,-45.95,-50.00,-54.05,-58.10,-62.15,-66.20,-70.25,-74.30,-78.35};
	double aE0150[]	=	{78.57,70.23,64.52,59.76,55.00,51.78,48.57,45.95,43.33,37.85,33.80,29.52,24.99,21.42,6.19,-3.33,-11.00,-17.85,-23.33,-28.57,-32.61,-37.14,-41.19,-44.52,-48.33,-52.14,-55.95,-59.76,-63.57,-67.38,-71.19,-75.00};
	double aE0300[]	=	{84.52,77.85,72.14,67.73,63.33,59.40,55.47,52.61,49.76,45.23,39.99,35.23,30.95,26.99,10.47,0.00,-7.38,-14.04,-20.23,-25.95,-30.71,-35.23,-39.52,-43.09,-47.14,-51.19,-55.24,-59.29,-63.34,-67.39,-71.44,-75.49};
	double aE0600[]	=	{87.61,82.85,78.33,74.52,70.71,67.37,64.04,61.30,58.57,53.57,48.57,44.04,39.99,35.00,17.85,5.23,-3.33,-10.71,-17.38,-23.80,-28.57,-33.57,-37.61,-41.90,-45.47,-48.57,-51.67,-54.77,-57.87,-60.97,-64.07,-67.17};
	double aE01200[]=	{87.61,84.52,82.01,79.93,77.85,75.35,72.85,70.59,68.33,63.80,59.28,54.28,50.47,45.71,27.14,10.47,0.23,-7.61,-14.76,-21.19,-26.66,-31.66,-36.42,-40.47,-44.00,-47.38,-50.76,-54.14,-57.52,-60.90,-64.28,-67.66};
	double aE0fs[]	=	{87.60,84.76,82.37,80.82,79.28,77.85,76.42,75.47,74.52,72.85,71.42,69.99,68.80,67.85,64.28,62.14,59.99,58.57,56.90,55.70,54.52,53.57,52.61,51.90,51.19,50.47,50.23,49.52,49.28,48.57,48.33,48.33};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_6(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{64.54,57.41,52.83,49.14,45.45,42.77,40.10,37.81,35.52,31.54,28.40,25.60,22.80,20.00,9.81,0.14,-6.72,-13.34,-18.94,-24.29,-28.10,-32.43,-36.50,-40.07,-43.89,-46.94,-50.00,-53.06,-56.12,-59.18,-62.24,-65.30};
	double aE075[]	=	{70.65,63.78,58.69,54.87,51.05,47.99,44.94,42.65,40.36,36.03,32.72,29.41,26.36,23.56,12.61,3.45,-4.43,-10.80,-16.90,-22.50,-26.83,-31.67,-35.74,-39.05,-42.61,-46.18,-48.98,-51.78,-54.58,-57.38,-60.18,-62.98};
	double aE0150[]	=	{76.50,69.38,64.54,60.59,56.65,53.47,50.29,47.99,45.70,41.38,38.07,34.25,30.94,28.40,16.18,6.50,-1.63,-9.01,-14.87,-20.47,-25.30,-30.40,-34.47,-37.78,-41.09,-44.90,-48.47,-52.04,-55.61,-59.18,-62.75,-66.32};
	double aE0300[]	=	{84.40,77.27,72.18,68.23,64.29,60.98,57.67,55.12,52.58,48.25,44.43,40.61,37.30,34.00,20.25,9.56,1.92,-6.21,-12.83,-18.94,-24.03,-29.12,-33.20,-37.01,-40.32,-43.89,-47.20,-49.23,-51.26,-53.29,-55.32,-57.35};
	double aE0600[]	=	{87.20,82.36,77.78,74.21,70.65,67.72,64.80,62.25,59.70,54.87,50.54,46.72,43.16,40.36,25.34,13.63,5.23,-2.14,-9.52,-15.38,-20.47,-26.07,-30.65,-34.72,-38.80,-42.61,-45.92,-48.98,-52.04,-55.10,-58.16,-61.22};
	double aE01200[]=	{87.70,84.65,82.10,79.68,77.27,75.23,73.20,71.16,69.12,65.05,60.72,56.62,52.83,49.52,33.49,20.76,10.83,2.69,-4.94,-11.81,-17.41,-23.27,-28.36,-32.43,-36.50,-40.58,-44.14,-47.20,-50.00,-52.80,-55.60,-58.40};
	double aE0fs[]	=	{87.60,87.45,84.40,83.25,82.10,80.45,78.80,77.52,76.25,74.20,72.69,71.41,69.89,68.87,67.85,64.54,62.25,60.47,58.94,57.41,56.40,55.38,54.10,53.34,52.58,51.81,51.05,49.78,49.27,49.01,48.50,48.00};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_7(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{65.32,57.71,53.05,49.96,46.87,44.45,42.04,40.88,39.72,36.95,34.41,32.10,29.57,27.49,17.80,9.50,2.35,-4.56,-10.79,-16.55,-21.63,-26.93,-31.77,-36.39,-40.31,-44.00,-47.46,-50.92,-54.38,-57.84,-61.30,-64.76};
	double aE075[]	=	{71.77,63.93,59.09,55.51,51.94,49.63,47.33,45.60,43.87,41.10,38.79,36.02,33.26,30.95,20.80,12.04,4.66,-2.02,-8.48,-14.48,-19.55,-24.85,-30.16,-34.54,-38.69,-42.84,-46.07,-49.07,-52.07,-55.07,-58.07,-61.07};
	double aE0150[]	=	{78.00,69.70,64.86,61.05,57.24,54.70,52.17,50.21,48.25,45.02,42.71,40.18,37.41,35.32,24.72,15.04,7.43,0.51,-6.40,-12.63,-17.47,-23.24,-28.08,-33.29,-37.31,-40.77,-44.69,-47.82,-50.95,-54.08,-57.21,-60.34};
	double aE0300[]	=	{84.23,77.54,72.24,68.23,64.22,61.54,58.86,56.32,53.78,50.56,46.63,43.41,40.60,38.10,27.49,18.03,10.42,2.81,-4.10,-10.32,-15.63,-21.16,-26.24,-31.54,-35.93,-39.85,-43.54,-46.53,-49.30,-52.07,-54.84,-57.61};
	double aE0600[]	=	{87.00,82.38,77.77,74.42,71.08,68.43,65.78,63.35,60.93,56.78,53.32,50.99,46.63,44.10,31.64,21.26,13.26,6.50,-0.41,-7.56,-12.63,-18.40,-23.93,-29.47,-34.08,-37.77,-41.69,-44.46,-47.69,-50.92,-54.15,-57.38};
	double aE01200[]=	{87.00,83.54,81.23,79.50,77.77,75.69,73.62,71.77,69.93,66.47,62.55,59.09,55.63,53.09,40.18,29.11,20.34,12.50,5.58,-2.02,-7.79,-14.48,-20.47,-25.09,-30.62,-35.23,-39.38,-43.08,-46.07,-49.30,-52.53,-55.76};
	double aE0fs[]	=	{87.00,83.54,81.23,79.50,77.77,76.50,75.23,74.19,73.16,71.77,70.16,69.01,68.08,67.39,63.93,61.86,60.24,58.40,57.24,56.09,55.17,54.25,53.09,52.17,51.71,50.79,50.09,49.04,48.94,48.48,48.02,47.79};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_8(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{62.18,54.76,49.43,45.49,41.55,38.53,35.52,33.09,30.66,26.72,23.47,20.23,17.21,15.13,7.01,0.06,-5.72,-12.21,-17.54,-22.88,-27.28,-31.92,-36.09,-40.49,-44.66,-48.60,-52.54,-56.48,-60.42,-64.36,-68.30,-72.24};
	double aE075[]	=	{69.83,61.95,56.15,51.86,47.58,44.33,41.09,38.42,35.76,31.35,27.88,24.17,21.39,19.07,10.03,3.07,-4.10,-10.36,-15.92,-21.02,-25.43,-29.83,-34.70,-39.10,-43.04,-47.21,-51.38,-55.55,-59.72,-63.89,-68.06,-72.23};
	double aE0150[]	=	{77.48,68.90,63.34,58.82,54.30,50.94,47.58,44.79,42.01,37.61,34.13,30.19,27.41,24.63,13.27,5.86,-1.78,-7.81,-13.14,-18.94,-23.57,-27.98,-32.84,-37.25,-41.42,-45.36,-49.30,-53.24,-57.18,-61.12,-65.06,-69.00};
	double aE0300[]	=	{83.04,76.55,70.99,66.70,62.41,59.05,55.69,52.56,49.43,44.33,40.39,35.99,32.51,29.73,17.21,9.33,2.38,-4.10,-9.90,-15.92,-20.79,-25.89,-30.99,-35.16,-39.33,-43.04,-46.52,-50.00,-53.48,-56.96,-60.44,-63.92};
	double aE0600[]	=	{87.21,81.65,77.01,73.19,69.37,66.24,63.11,60.09,57.08,52.21,47.81,43.87,39.93,36.22,22.31,13.97,7.01,-1.09,-6.42,-12.68,-18.01,-22.88,-27.74,-32.61,-37.25,-41.29,-44.66,-47.91,-51.16,-54.41,-57.66,-60.91};
	double aE01200[]=	{86.97,83.50,81.42,79.31,77.20,74.64,72.09,69.30,66.51,62.09,57.67,53.48,49.99,46.04,30.23,20.23,10.93,4.18,-2.55,-9.30,-14.88,-20.69,-25.81,-30.69,-35.34,-39.30,-43.25,-46.51,-50.00,-53.49,-56.98,-60.47};
	double aE0fs[]	=	{86.98,83.50,81.42,79.91,78.41,77.13,75.86,74.81,73.77,71.92,70.52,69.37,68.21,67.28,63.80,61.72,60.09,58.47,56.85,55.92,54.76,53.84,52.91,51.98,51.05,50.36,49.66,49.20,48.74,48.04,47.81,47.58};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_9(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{63.46,56.36,51.38,47.59,43.80,41.31,38.83,36.69,34.56,31.01,27.93,25.32,22.96,21.06,12.30,5.90,-0.01,-5.93,-11.38,-16.59,-21.33,-26.54,-31.28,-35.78,-39.57,-43.36,-47.15,-50.94,-54.73,-58.52,-62.31,-66.10};
	double aE075[]	=	{70.57,63.23,58.25,54.34,50.43,47.59,44.75,42.73,40.72,36.70,33.38,30.06,27.46,25.32,16.09,9.69,3.06,-2.62,-8.54,-13.99,-19.20,-24.17,-29.19,-33.41,-37.91,-42.18,-45.73,-50.00,-54.27,-58.54,-62.81,-67.08};
	double aE0150[]	=	{77.20,70.10,64.89,60.74,56.59,53.63,50.67,48.06,45.46,41.67,38.12,34.80,31.96,29.59,19.17,12.53,5.43,-0.72,-6.88,-12.00,-17.30,-22.75,-27.73,-31.99,-36.73,-40.76,-44.78,-48.57,-52.36,-56.15,-59.94,-63.73};
	double aE0300[]	=	{83.84,76.97,71.75,68.08,64.41,61.21,58.02,55.29,52.57,48.54,44.51,40.72,37.64,35.04,24.61,16.56,8.98,2.35,-3.57,-10.20,-15.41,-21.57,-26.54,-31.28,-35.78,-39.81,-43.60,-47.63,-51.66,-55.69,-59.72,-63.75};
	double aE0600[]	=	{87.15,81.94,77.91,74.24,70.57,67.61,64.65,62.40,60.15,55.41,51.38,47.83,44.75,41.91,30.54,22.01,13.24,5.90,-0.96,-7.36,-12.80,-18.96,-24.41,-29.15,-33.18,-37.68,-41.47,-45.49,-49.05,-52.61,-56.17,-59.73};
	double aE01200[]=	{87.15,83.84,81.47,79.33,77.20,75.07,72.94,71.16,69.39,65.83,61.81,57.78,54.46,51.15,38.83,29.35,20.11,10.87,4.24,-3.35,-9.01,-14.07,-20.86,-26.07,-30.33,-35.07,-39.90,-43.36,-47.15,-50.94,-54.73,-58.52};
	double aE0fs[]	=	{87.15,83.84,81.47,80.04,78.62,77.32,76.02,75.07,74.12,72.47,71.04,69.62,68.68,67.73,63.94,61.57,59.91,58.49,56.83,55.65,54.46,53.75,52.80,52.09,51.38,50.91,50.43,49.96,49.25,48.54,48.30,47.59};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_10(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{64.22,58.42,54.01,50.76,47.51,45.07,42.63,40.77,38.92,35.90,32.86,30.79,28.74,26.84,18.49,12.22,6.88,0.38,-5.42,-11.22,-15.87,-20.74,-26.08,-31.19,-35.83,-40.01,-44.19,-47.91,-51.63,-55.35,-59.07,-62.79};
	double aE075[]	=	{70.03,63.99,59.35,56.10,52.85,50.29,47.74,45.76,43.79,40.31,36.83,34.51,32.18,30.09,20.81,14.31,8.50,2.00,-3.79,-9.60,-14.24,-19.81,-24.92,-30.03,-34.67,-39.08,-43.03,-46.74,-50.00,-53.26,-56.52,-59.78};
	double aE0150[]	=	{77.46,70.49,65.38,61.67,57.96,55.29,52.62,50.18,47.74,44.26,41.01,37.99,35.43,33.35,24.52,17.56,11.29,4.56,-1.47,-7.74,-12.62,-17.72,-23.06,-28.40,-33.26,-37.69,-41.40,-45.12,-48.37,-51.62,-54.87,-58.12};
	double aE0300[]	=	{84.42,77.46,72.12,68.29,64.46,61.44,58.42,55.98,53.54,49.60,46.58,43.33,40.54,38.22,28.47,21.74,15.24,8.04,1.54,-5.19,-10.53,-15.37,-21.44,-26.31,-31.42,-35.83,-40.01,-43.49,-47.21,-50.93,-54.65,-58.37};
	double aE0600[]	=	{87.73,82.33,78.15,74.78,71.42,68.63,65.85,63.29,60.74,57.26,54.01,50.53,47.74,45.19,35.20,27.08,19.65,12.22,5.25,-1.70,-7.74,-13.31,-18.88,-23.53,-28.64,-33.51,-37.46,-41.87,-45.58,-48.83,-52.08,-55.33};
	double aE01200[]=	{86.98,83.96,81.64,79.89,78.15,76.06,73.98,72.12,70.26,67.01,63.99,60.51,57.49,55.40,44.49,35.90,26.61,18.02,9.90,2.70,-3.10,-9.36,-15.87,-20.74,-25.85,-30.49,-35.37,-39.55,-43.03,-46.98,-50.93,-54.88};
	double aE0fs[]	=	{86.98,83.73,81.64,80.01,78.39,77.22,76.06,74.90,73.74,72.12,70.96,69.56,68.40,67.47,63.76,61.44,59.81,58.19,56.79,55.40,54.47,53.31,52.62,51.69,50.76,50.06,49.36,48.90,47.97,47.28,47.28,47.04};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}
void CGE89_Functions::F_2_17(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{60.01,52.22,46.55,42.30,38.06,34.63,31.21,28.96,26.72,22.47,17.99,14.45,11.38,8.78,-4.90,-14.82,-22.37,-28.98,-35.12,-40.32,-44.80,-49.29,-53.78,-58.27,-62.76,-67.25,-71.74,-76.23,-80.72,-85.21,-89.70,-94.19};
	double aE075[]	=	{67.33,60.01,54.11,49.39,44.67,41.12,37.58,34.51,31.45,26.49,21.77,17.99,14.45,11.14,-1.83,-11.75,-19.78,-27.09,-33.23,-38.66,-43.38,-48.11,-52.84,-57.57,-62.30,-67.03,-71.76,-76.49,-81.22,-85.95,-90.68,-95.41};
	double aE0150[]	=	{76.07,68.27,62.37,57.29,52.22,48.44,44.67,41.36,38.06,32.63,27.90,23.65,19.88,16.57,2.17,-8.44,-16.94,-24.26,-30.64,-36.54,-41.50,-45.98,-50.00,-54.02,-58.04,-62.06,-66.08,-70.10,-74.12,-78.14,-82.16,-86.18};
	double aE0300[]	=	{83.86,76.07,69.93,64.97,60.01,55.88,51.75,48.68,45.61,39.47,34.28,29.79,25.78,22.00,6.42,-5.37,-13.87,-21.43,-28.51,-34.41,-39.13,-44.33,-48.58,-52.83,-57.08,-61.33,-65.58,-69.83,-74.08,-78.33,-82.58,-86.83};
	double aE0600[]	=	{86.22,82.91,79.37,75.35,71.34,67.21,63.08,59.65,56.23,50.33,44.43,39.47,34.75,30.50,13.50,0.75,-9.62,-17.65,-25.44,-31.58,-36.77,-42.20,-46.69,-50.00,-53.31,-56.62,-59.93,-63.24,-66.55,-69.86,-73.17,-76.48};
	double aE01200[]=	{86.45,83.15,81.26,79.49,77.72,75.12,72.52,69.92,67.33,62.14,56.71,51.28,46.08,41.83,22.00,7.36,-4.43,-13.64,-21.19,-28.27,-33.94,-39.13,-43.86,-47.87,-51.88,-55.89,-59.90,-63.91,-67.92,-71.93,-75.94,-79.95};
	double aE0fs[]	=	{86.45,83.15,81.26,79.49,77.72,76.65,75.59,74.53,73.47,72.05,70.64,69.22,68.27,67.57,64.03,61.66,59.78,58.12,56.94,55.76,54.82,53.87,52.93,51.98,51.28,50.33,49.62,48.92,48.68,47.97,47.50,47.26};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_18(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{61.34,53.42,47.83,43.87,39.91,36.88,33.86,31.53,29.20,25.24,22.21,18.48,15.92,13.36,4.27,-4.57,-12.26,-18.78,-24.84,-29.73,-35.09,-39.98,-44.87,-48.60,-52.33,-56.06,-59.79,-63.52,-67.25,-70.98,-74.71,-78.44};
	double aE075[]	=	{67.87,59.71,54.82,50.51,46.20,43.29,40.38,38.05,35.72,30.83,28.03,24.30,21.28,18.71,7.53,-2.24,-9.70,-16.92,-22.51,-28.33,-33.22,-38.35,-43.01,-47.20,-51.39,-55.58,-59.77,-63.96,-68.15,-72.34,-76.53,-80.72};
	double aE0150[]	=	{76.72,68.33,62.27,57.84,53.42,50.04,46.67,43.99,41.31,36.65,33.16,29.20,25.70,22.91,10.09,-0.14,-7.60,-14.59,-20.88,-26.70,-31.59,-36.95,-41.84,-45.57,-50.00,-54.43,-58.86,-63.29,-67.72,-72.15,-76.58,-81.01};
	double aE0300[]	=	{83.71,76.25,70.43,65.88,61.34,57.73,54.12,51.21,48.30,43.64,39.45,35.49,31.76,28.50,14.05,3.11,-5.04,-12.03,-18.78,-24.84,-29.73,-35.32,-40.21,-44.40,-48.36,-52.32,-56.28,-60.24,-64.20,-68.16,-72.12,-76.08};
	double aE0600[]	=	{86.27,83.01,78.81,74.97,71.13,67.63,64.14,60.76,57.38,51.79,47.37,42.71,38.51,34.55,18.48,6.83,-1.78,-9.23,-16.22,-22.04,-27.17,-32.76,-38.12,-42.31,-46.73,-50.00,-53.27,-56.54,-59.81,-63.08,-66.35,-69.62};
	double aE01200[]=	{86.27,83.01,81.14,79.28,77.42,75.09,72.76,70.54,68.33,62.97,58.55,54.12,49.46,45.27,29.43,16.15,4.97,-2.71,-10.39,-17.38,-23.21,-29.03,-34.62,-39.98,-44.40,-47.90,-51.40,-54.90,-58.40,-61.90,-65.40,-68.90};
	double aE0fs[]	=	{86.30,83.04,81.14,79.51,77.88,76.60,75.32,74.39,73.46,71.59,70.43,69.03,67.63,66.70,63.21,60.88,59.25,57.38,56.22,55.05,54.12,53.19,52.26,51.56,50.63,49.93,49.46,49.00,48.53,47.83,47.37,46.90};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_19(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{62.09,55.05,50.13,46.61,43.09,40.63,38.17,36.41,34.65,31.13,28.55,25.98,23.63,21.52,12.37,2.76,-5.20,-12.01,-17.87,-23.50,-28.19,-33.35,-38.27,-42.49,-46.95,-51.41,-55.87,-60.33,-64.79,-69.25,-73.71,-78.17};
	double aE075[]	=	{68.66,61.15,55.99,52.24,48.49,45.91,43.33,41.33,39.34,36.06,33.01,29.96,27.38,25.27,14.48,5.34,-2.62,-9.66,-15.76,-21.85,-26.78,-31.70,-36.63,-41.08,-45.30,-49.76,-54.22,-58.68,-63.14,-67.60,-72.06,-76.52};
	double aE0150[]	=	{76.39,69.12,63.50,59.74,55.99,53.17,50.36,47.90,45.44,41.45,38.17,35.12,32.07,29.49,17.77,7.92,-0.28,-7.08,-13.65,-19.51,-24.90,-30.06,-35.46,-39.68,-43.66,-48.12,-52.58,-57.04,-61.50,-65.96,-70.42,-74.88};
	double aE0300[]	=	{83.66,76.86,71.23,67.01,62.79,59.74,56.70,54.00,51.30,47.32,43.80,40.28,37.23,34.65,21.75,10.97,2.76,-4.97,-12.01,-17.87,-23.26,-28.65,-33.58,-38.27,-42.96,-46.71,-50.46,-54.21,-57.96,-61.71,-65.46,-69.21};
	double aE0600[]	=	{86.48,83.19,78.97,75.45,71.94,68.65,65.37,62.32,59.27,54.82,50.36,46.38,43.09,40.51,25.98,15.42,6.28,-1.45,-8.49,-14.82,-20.21,-26.08,-31.23,-36.16,-40.38,-44.84,-48.35,-51.86,-55.37,-58.88,-62.39,-65.90};
	double aE01200[]=	{86.48,83.43,81.32,79.21,77.10,74.99,72.88,70.65,68.42,64.90,60.68,57.16,53.65,50.60,35.36,23.40,14.25,5.34,-2.62,-9.66,-15.99,-22.09,-27.48,-33.11,-37.33,-41.79,-46.24,-50.00,-53.76,-57.52,-61.28,-65.04};
	double aE0fs[]	=	{86.48,83.43,81.32,79.79,78.27,76.86,75.46,74.52,73.58,72.17,70.53,69.36,68.19,67.25,63.50,60.92,58.81,57.40,55.99,54.82,53.65,52.71,51.77,51.30,50.36,49.89,49.43,48.72,48.25,48.02,47.55,47.55};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_20(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{61.37,52.23,45.73,41.28,36.83,33.34,29.86,27.69,25.53,21.20,17.83,14.70,12.06,9.41,-0.68,-8.38,-14.87,-20.65,-26.18,-31.47,-36.52,-41.82,-46.63,-51.44,-56.25,-61.06,-65.87,-70.68,-75.49,-80.30,-85.11,-89.92};
	double aE075[]	=	{68.11,59.69,53.43,48.50,43.57,39.96,36.35,33.34,30.34,25.29,21.68,18.07,15.18,12.78,1.95,-6.21,-12.71,-18.24,-24.02,-29.79,-34.60,-39.65,-44.70,-50.00,-55.30,-60.60,-65.90,-71.20,-76.50,-81.80,-87.10,-92.40};
	double aE0150[]	=	{77.01,68.35,61.13,56.20,51.27,47.18,43.09,39.96,36.83,31.78,27.69,23.60,20.00,17.35,5.56,-2.61,-9.82,-16.08,-22.09,-27.62,-32.43,-37.97,-42.78,-47.83,-52.88,-57.93,-62.98,-68.03,-73.08,-78.13,-83.18,-88.23};
	double aE0300[]	=	{84.46,76.52,70.51,65.58,60.65,56.80,52.95,49.34,45.73,40.44,35.39,30.82,26.73,23.60,10.37,0.75,-7.18,-13.67,-19.69,-25.46,-30.03,-35.56,-41.34,-46.15,-50.96,-55.77,-60.58,-65.39,-70.20,-75.01,-79.82,-84.63};
	double aE0600[]	=	{86.63,83.50,79.65,75.08,70.51,66.42,62.33,58.84,55.36,49.58,44.53,38.76,34.91,31.30,16.15,5.80,-1.40,-9.10,-15.60,-22.09,-27.38,-32.19,-37.97,-43.26,-49.03,-54.80,-60.57,-66.34,-72.11,-77.88,-83.65,-89.42};
	double aE01200[]=	{86.60,83.50,81.34,79.65,77.97,75.44,72.92,70.27,67.62,62.81,57.52,52.95,48.14,44.29,27.21,14.70,4.36,-4.53,-12.47,-18.48,-24.26,-30.27,-35.56,-40.37,-45.42,-50.47,-55.52,-60.57,-65.62,-70.67,-75.72,-80.77};
	double aE0fs[]	=	{86.60,83.50,81.33,79.65,77.97,76.76,75.56,74.48,73.40,71.71,70.03,68.59,67.38,66.66,63.53,61.37,59.69,58.24,56.80,55.36,54.39,53.19,52.23,51.51,50.55,49.82,49.10,48.62,48.38,47.66,47.18,46.94};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_21(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{62.42,54.41,48.75,44.50,40.26,37.31,34.37,32.25,30.13,26.59,24.00,21.41,19.29,16.93,7.27,-0.26,-9.22,-15.11,-20.77,-26.19,-31.14,-36.09,-41.04,-45.52,-49.29,-53.06,-56.83,-60.60,-64.37,-68.14,-71.91,-75.68};
	double aE075[]	=	{69.96,61.24,55.35,50.75,46.16,43.09,40.03,37.43,34.84,31.31,27.54,24.71,21.88,19.76,9.62,0.90,-6.86,-13.70,-19.59,-25.01,-29.96,-34.91,-39.62,-43.87,-48.35,-52.83,-57.31,-61.79,-66.27,-70.75,-75.23,-79.71};
	double aE0150[]	=	{77.50,69.25,62.89,58.41,53.93,50.28,46.63,43.92,41.21,36.49,32.49,29.19,26.59,24.24,12.92,5.15,-3.80,-10.63,-17.00,-22.66,-27.84,-33.26,-37.97,-42.22,-46.93,-51.64,-56.35,-61.06,-65.77,-70.48,-75.19,-79.90};
	double aE0300[]	=	{85.05,77.50,71.38,66.66,61.95,58.18,54.41,51.34,48.28,43.56,39.56,35.79,32.02,29.66,17.87,9.39,0.20,-7.57,-13.93,-19.36,-25.01,-29.96,-35.38,-39.86,-44.10,-48.35,-52.60,-56.85,-61.10,-65.35,-69.60,-73.85};
	double aE0600[]	=	{87.17,83.87,79.62,75.38,71.14,67.48,63.83,60.88,57.94,52.52,48.28,44.04,40.50,37.20,23.77,14.10,5.15,-2.39,-9.22,-15.35,-21.01,-26.66,-32.32,-37.03,-42.22,-46.46,-50.70,-54.94,-59.18,-63.42,-67.66,-71.90};
	double aE01200[]=	{87.17,83.87,81.75,80.10,78.45,75.74,73.03,70.55,68.08,63.36,59.12,55.11,51.11,47.34,32.49,20.70,10.80,2.32,-4.51,-11.58,-17.71,-24.07,-29.73,-34.68,-39.39,-44.10,-48.11,-52.12,-56.13,-60.14,-64.15,-68.16};
	double aE0fs[]	=	{87.17,83.87,81.75,80.10,78.45,77.15,75.85,74.79,73.73,72.08,70.90,69.73,68.08,66.90,63.60,61.48,59.59,58.18,56.53,55.35,54.64,53.70,52.99,52.05,51.58,50.63,50.16,49.69,48.98,48.75,48.28,48.04};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

void CGE89_Functions::F_2_22(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) 
{
	double aE037[]	=	{62.81,55.60,50.55,46.94,43.33,40.56,37.80,36.11,34.43,31.54,29.14,26.97,25.05,22.88,13.26,5.32,-3.57,-10.06,-16.08,-21.61,-26.66,-31.95,-36.76,-41.58,-46.15,-50.72,-55.29,-59.86,-64.43,-69.00,-73.57,-78.14};
	double aE075[]	=	{69.07,61.85,56.32,52.47,48.62,45.97,43.33,41.28,39.24,35.87,32.98,30.34,28.65,26.25,16.63,7.97,-0.92,-7.42,-14.15,-19.69,-24.98,-30.03,-35.56,-40.61,-44.70,-49.51,-54.32,-59.13,-63.94,-68.75,-73.56,-78.37};
	double aE0150[]	=	{77.73,69.07,63.53,59.32,55.12,52.35,49.58,47.17,44.77,40.92,37.56,34.91,32.74,30.58,20.24,10.85,2.19,-4.77,-11.51,-17.52,-22.57,-28.35,-33.64,-38.93,-43.74,-48.31,-52.88,-57.45,-62.02,-66.59,-71.16,-75.73};
	double aE0300[]	=	{84.22,77.01,70.75,66.54,62.33,59.20,56.08,53.67,51.27,46.94,43.57,40.44,37.56,35.63,25.29,15.91,6.52,-1.16,-7.90,-14.39,-20.65,-26.42,-31.95,-37.25,-42.06,-46.63,-51.20,-55.77,-60.34,-64.91,-69.48,-74.05};
	double aE0600[]	=	{86.87,83.74,79.41,75.56,71.71,68.46,65.22,62.57,59.93,55.60,51.03,47.18,44.29,41.16,29.38,19.75,10.13,2.68,-4.77,-11.27,-17.76,-23.78,-29.31,-34.36,-39.41,-43.74,-48.07,-52.40,-56.73,-61.06,-65.39,-69.72};
	double aE01200[]=	{86.87,83.74,81.58,79.65,77.73,75.20,72.68,70.63,68.59,64.26,60.89,56.80,53.19,50.06,36.35,27.21,18.07,9.17,0.75,-6.21,-12.95,-19.20,-25.22,-30.03,-35.32,-40.13,-44.70,-49.03,-53.36,-57.69,-62.02,-66.35};
	double aE0fs[]	=	{86.87,83.74,81.58,80.01,78.45,77.00,75.56,74.60,73.64,71.95,70.51,69.31,67.86,67.14,63.53,61.61,59.93,58.48,57.52,56.32,54.87,53.91,53.19,51.99,51.51,50.79,50.06,49.10,48.62,48.14,47.90,47.42};
	for(int i=0;i<32;i++)
	{
		E037[i]		=	aE037[i];
		E075[i]		=	aE075[i];
		E0150[i]	=	aE0150[i];
		E0300[i]	=	aE0300[i];
		E0600[i]	=	aE0600[i];
		E01200[i]	=	aE01200[i];
		E0fs[i]		=	aE0fs[i];
	}
}

double CGE89_Functions::F_2A_5(double Angle, double f) 
{
	double aAngle[]	=	{-5,-4.75, -4.5,-4.25,   -4,-3.75, -3.5,-3.25,   -3,-2.75, -2.5,-2.25,   -2,-1.75, -1.5,-1.25,   -1,-0.75, -0.5,-0.25,    0, 0.25,  0.5};
	double aCA[]	=	{-21.2613,-20.8324,-20.3604,-19.8321,-19.2793,-18.7265,-18.1983,-17.7564,-17.2974,-16.7246,-16.0361,-15.1753,-14.1442,-12.9253,-11.5316,-10.0115, -8.2883,-6.24969,  -3.964,-1.53047,  1.1711, 4.26812,  7.7477};
	double aCB[]	=	{-21.1712,-20.7423,-20.2703,-19.7297,-19.1892,-18.7387,-18.2883,-17.7655,-17.2073,-16.6276,-16.0361,-15.4849,-14.8649,-14.0163, -12.973,-11.7719,-10.2703,-8.19485, -5.5856,-2.54394,  1.2612, 6.39803, 12.8829};

	double  Correc = 0;
	if( (f>=30.0) && (f<=250.0) )
		Correc = Interp2(aAngle,aCA, Angle,23);
	else if((f>=450.0) && (f<=1000.0) )
		Correc = Interp2(aAngle,aCB, Angle,23);
	return Correc;
}

double CGE89_Functions::F_2_1(double Frac, double t) 
{
	double aFrac[]	=	{0,0.05, 0.1,0.15, 0.2,0.25, 0.3,0.35, 0.4,0.45, 0.5,0.55, 0.6,0.65, 0.7,0.75, 0.8,0.85, 0.9,0.95,   1};
	double aA5[]	=	{0,0.036336,0.074325, 0.11464, 0.15541, 0.19378, 0.23311, 0.27708, 0.32264,  0.3674, 0.41216, 0.45633, 0.50169, 0.55025, 0.60135, 0.65488, 0.71115, 0.76878, 0.83277, 0.91023,   1};
	double aA1[]	=	{0,0.030833,  0.0625,0.094371, 0.12838, 0.16798, 0.20946, 0.24916, 0.28885, 0.32888, 0.36993, 0.41281, 0.45777, 0.50539, 0.55574, 0.60861, 0.66554, 0.72643,  0.7973, 0.88884,   1};

	double  A = 0;
	if (t>=5)
		A = Interp2(aFrac,aA5, Frac,21);
	else if (t==1)
		A = Interp2(aFrac,aA1, Frac,21);
	else if ((t>1)&&(t<5))
	{
		double t1 = 1;
		double t2 = 5;
		double A1 = Interp2(aFrac,aA1, Frac,21);
		double A2 = Interp2(aFrac,aA5, Frac,21);

		A = A1+(A2-A1)*(t-t1)/(t2-t1);
	}
	return A;
}

double CGE89_Functions::GE89_E_3(double f,double t,CString z,double h1,double d_km) 
{
	double Eb,E0fs;

	if(z=="1")
		Eb = GE89_E_2(f,t,1,h1,d_km,&E0fs);
	else if(z=="2")
		Eb = GE89_E_2(f,t,2,h1,d_km,&E0fs);
	else if(z=="3")
		Eb = GE89_E_2(f,t,3,h1,d_km,&E0fs);
	else if(z=="4")
		Eb = GE89_E_2(f,t,4,h1,d_km,&E0fs);
	else if(z=="A")
	{
		Eb = 10.0 + GE89_E_2(f,t,4,h1,d_km,&E0fs);
		Eb = min(Eb , E0fs + 6.0);
	}
	else if(z=="B")
	{
		Eb = 5.0 + GE89_E_2(f,t,4,h1,d_km,&E0fs);
		Eb = min(Eb , E0fs + 6.0);
	}
	else if(z=="C")
	{
		if(t==50.0)
		{
			Eb = 15.0 + GE89_E_2(f,t,4,h1,d_km,&E0fs);
			Eb = min(Eb , E0fs);
		}
		else if(t==10.0)
		{
			Eb = 15.0 + GE89_E_2(f,t,4,h1,d_km,&E0fs);
			double Eb4_1 = GE89_E_2(f,1,4,h1,d_km,&E0fs);
			Eb = min(Eb , Eb4_1);
		}
		else if( (t==1.0) && (f>=30.0) && (f<=250.0) )
		{
			Eb = 15.0 + GE89_E_2(f,t,4,150.0,d_km,&E0fs);
			Eb = min(Eb , E0fs);
		}
		else if( (t==1.0) && (f>=450.0) && (f<=1000.0) )
		{
			Eb = GE89_E_2(f,t,4,150.0,d_km,&E0fs);

			Eb = 106.9 - 20.0*log10(d_km) - 0.012*d_km;
			Eb = min(Eb , E0fs);
		}
	}
	else if(z=="C1")
	{
		if((t==10.0)||(t==50.0))
		{
			Eb = (GE89_E_2(f,t,1,h1,d_km,&E0fs) + GE89_E_2(f,t,2,h1,d_km,&E0fs))/2.0;	//	??????

		}
		else if( (t==1.0) && (f>=30.0) && (f<=250.0) )
		{
			double Eb4 = 15.0 + GE89_E_2(f,t,4,150.0,d_km,&E0fs);
			Eb4 = min(Eb4 , E0fs);
			Eb =  Eb4 + (GE89_E_2(f,t,1,150.0,d_km,&E0fs) + GE89_E_2(f,t,2,150.0,d_km,&E0fs))/2.0;//	??????
			Eb = Eb/2.0;

			//	Eb = min(Eb , E0fs);
		}
		else if( (t==1.0) && (f>=450.0) && (f<=1000.0) )
		{
			Eb = GE89_E_2(f,t,4,150.0,d_km,&E0fs);

			Eb = 106.9 - 20.0*log10(d_km) + 0.1*d_km;
			Eb = min(Eb , E0fs);
		}
	}

	return Eb;

}

double CGE89_Functions::GE89_E_2(double f,double t,int z,double h1,double d_km,double *Ebfs) 
{
	double Eb,E0fs,dum;

	if ( (h1>=37.5) && (h1<=1200.0) )
		Eb = GE89_E_1(f,t,z,h1,d_km,&E0fs);
	else if ( (h1>=0.0) && (h1<37.5) )
	{
		double dh1 = 4.1*sqrt(h1);
		if (d_km<dh1)
			Eb = GE89_E_1(f,t,z,37.5,d_km,&E0fs) - GE89_E_1(f,t,z,37.5,dh1,&E0fs) + GE89_E_1(f,t,z,37.5,4.1*sqrt(37.5),&E0fs);
		else
			Eb = GE89_E_1(f,t,z,37.5,d_km+4.1*sqrt(37.5)-dh1,&E0fs);
	}
	else if ( (h1>1200.0) )
	{
		double dh1 = 4.1*sqrt(h1);
		if (d_km<dh1)
			Eb = GE89_E_1(f,t,z,1200.0,d_km,&E0fs) - GE89_E_1(f,t,z,1200.0,dh1,&E0fs) + GE89_E_1(f,t,z,1200,4.1*sqrt(1200.0),&E0fs);
		else
			Eb = GE89_E_1(f,t,z,1200.0,d_km+4.1*sqrt(1200.0)-dh1,&E0fs);
	}
	else if ( (h1<0.0) )
		Eb = GE89_E_2(f,t,z,0.0,d_km,&E0fs);

	dum = GE89_E_1(f,t,z,h1,d_km,&E0fs);
	*Ebfs = E0fs;
	Eb = min(Eb,E0fs);
	return Eb;
}

double CGE89_Functions::GE89_E_1(double f,double t,int z,double h1,double d_km,double *Ebfs) 
{
	double Eb,E0fs;

	if ( (h1==37.5) || (h1==75.0) || (h1==150.0) || (h1==300.0) || (h1==600.0) || (h1==1200.0) )
		Eb = GE89_E_0( f , t , z , h1 , d_km , &E0fs );
	else
	{
		double h11,h12,E1,E2;
		
		if		( (h1 > 37.5) && (h1 < 75.0  ) )   {h11=37.5  ;h12=75.0;  }
		else if ( (h1 > 75.0  ) && (h1 < 150.0 ) ) {h11=75.0  ;h12=150.0; }
		else if ( (h1 > 150.0 ) && (h1 < 300.0 ) ) {h11=150.0 ;h12=300.0; }
		else if ( (h1 > 300.0 ) && (h1 < 600.0 ) ) {h11=300.0 ;h12=600.0; }
		else if ( (h1 > 600.0 ) && (h1 < 1200.0) ) {h11=600.0 ;h12=1200.0;}
		E1 = GE89_E_0( f , t , z , h11 , d_km , &E0fs );
		E2 = GE89_E_0( f , t , z , h12 , d_km , &E0fs );
		Eb = E1+(E2-E1)*log10(h1/h11)/log10(h12/h11);
	}
	*Ebfs=E0fs;
	return Eb;
}

double CGE89_Functions::GE89_E_0(double f,double t,int z,double h1,double d_km,double *Ebfs) 
{
	//	double h0[]		=	{37.5,75,150,300,600,1200};
	double D0[]		=	{10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,50.0,60.0,70.0,80.0,90.0,100.0,150.0,200.0,250.0,300.0,350.0,400.0,450.0,500.0,550.0,600.0,650.0,700.0,750.0,800.0,850.0,900.0,950.0,1000.0};
	double E037[32],E075[32],E0150[32],E0300[32],E0600[32],E01200[32],E0fs[32];	
	
	if ( (f>=30.0) && (f<=250.0) )
	{
		if ( (t==50) && (z==1) ) 
			F_2_2(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==10) && (z==1) )
			F_2_3(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==1) && (z==1) )
			F_2_4(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==50) && (z==2) ) 
			F_2_5(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==10) && (z==2) )
			F_2_6(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==1) && (z==2) )
			F_2_7(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==50) && (z==3) ) 
			F_2_8(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==10) && (z==3) )
			F_2_9(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==1) && (z==3) )
			F_2_10(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==50) && (z==4) ) 
			F_2_11(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==10) && (z==4) )
			F_2_12(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==1) && (z==4) )
			F_2_13(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
	}
	else if ( (f>=450.0) && (f<=1000.0) )
	{
		if ( (t==50) && (z==1) ) 
			F_2_14(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==10) && (z==1) )
			F_2_15(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==1) && (z==1) )
			F_2_16(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==50) && (z==2) ) 
			F_2_17(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==10) && (z==2) )
			F_2_18(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==1) && (z==2) )
			F_2_19(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==50) && (z==3) ) 
			F_2_20(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==10) && (z==3) )
			F_2_21(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==1) && (z==3) )
			F_2_22(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==50) && (z==4) ) 
			F_2_23(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==10) && (z==4) )
			F_2_24(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
		else if ( (t==1) && (z==4) )
			F_2_25(E037,E075,E0150,E0300,E0600,E01200,E0fs) ;
	}

	double E0[32];
	int i;

	if(h1==37.5)
		for (i=0;i<32;i++)
			E0[i] = E037[i];
	else if(h1==75.0)
		for (i=0;i<32;i++)
			E0[i] = E075[i];
	else if(h1==150.0)
		for (i=0;i<32;i++)
			E0[i] = E0150[i];
	else if(h1==300.0)
		for (i=0;i<32;i++)
			E0[i] = E0300[i];
	else if(h1==600.0)
		for (i=0;i<32;i++)
			E0[i] = E0600[i];
	else if(h1==1200.0)
		for (i=0;i<32;i++)
			E0[i] = E01200[i];

	*Ebfs = Interp1(D0,E0fs, d_km,32);
	double  Eb = Interp1(D0,E0, d_km,32);
	Eb = min(Eb,*Ebfs);
	return Eb;
}


double CGE89_Functions::Interp1(double *D0,double *E0,double d,int num) 
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


double CGE89_Functions::Delta_h_cr(double f,double d,double dh, CString cty)
{
	if(dh==0)
		return 0.0;

	int BandNUM = GE89_BAND1345(cty, f) ;
	if((BandNUM == 3)||(BandNUM == 4)||(BandNUM == 5))	//Band III , IV ,V
	{
		double y ,	y0[9] , dh0[9] = {10, 20, 30, 50, 80, 100, 150, 300, 500};

		for (int j=0;j<9;j++)
			y0[j] = Delta_h_cr_0(f,d,dh0[j]);
		y = Interp2(dh0,y0,dh,9);
		return y;
	}
	else
		return 0.0;

}
double CGE89_Functions::Delta_h_cr_0(double f,double d,double dh)
{
	double D0[34] = {1 ,10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80 ,90, 100, 150, 200, 250, 300,
		350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1100};

	double y0[34],y;

	if ( (dh==10) ||(dh==20) ||(dh==30) ||(dh==50) ||(dh==80) ||(dh==100) ||(dh==150) ||(dh==300) ||(dh==500) )
	{
		for (int j=0;j<34;j++)
			y0[j] = F_2A_2_3(f,D0[j],dh);
		y = Interp2(D0,y0,d,34);
	}
	return y;
}
double CGE89_Functions::F_2A_2_3(double f,double di,double dh)
{
	double p1,p2;
	 if ( (f>=30.0) && (f<=300.0) )
	 {
		p1 = -7.1154*(dh==10.0) +	(-4.1346)*(dh==20.0) +
			(-2.5962)*(dh==30.0) +	0.0*(dh==50.0) +
			2.8846*(dh==80.0) + 	4.9038*(dh==100.0) +
			7.8846*(dh==150.0) +	13.8942*(dh==300.0) +	18.8942*(dh==500.0);

		p2 = -3.125*(dh==10.0) +	(-2.1154)*(dh==20.0) +
			(-1.6346)*(dh==30.0) +	0.0*(dh==50.0) +
			1.875*(dh==80.0) + 	2.8846*(dh==100.0) +
			4.375*(dh==150.0) +	7.8846*(dh==300.0) +	9.4231*(dh==500.0);
	 }
	 else if ((f>=450.0) && (f<=1000.0) )
	 {
		p1 = -10*(dh==10.0) +	(-5.0)*(dh==20.0) +
			(-2.0)*(dh==30.0) +	0.0*(dh==50.0) +
			3.9979*(dh==80.0) + 	7.0203*(dh==100.0) +
			9.8028*(dh==150.0) +	19.9733*(dh==300.0) +	27.9371*(dh==500.0);

		p2 = -5*(dh==10.0) +	(-2.9104)*(dh==20.0) +
			(-1.6346)*(dh==30.0) +	0.0*(dh==50.0) +
			2.0309*(dh==80.0) + 	3.5181*(dh==100.0) +
			5.0533*(dh==150.0) +	9.9947*(dh==300.0) +	13.0171*(dh==500.0);
	 }
	 else
		 return 0.0;

	double y;
	if (di<10.0)
		y = 0.0;
	else if ( (di>=10.0) && (di<=50.0) )
		y = 0.0+(di-10.0)*(p1-0.0)/(50.0-10.0);
	else if ( (di>50.0) && (di<=100.0) )
		y = p1;
	else if ( (di>100.0) && (di<200.0) )
		y = p1+(di-100.0)*(p2-p1)/(200.0-100.0);
	else if ( di>=200.0 )
		y = p2;

	return y;

}

double CGE89_Functions::L_Xi(double Xi) 
{
	double LXi = 0;

	if(Xi<0) 
		LXi = 1.0 - L_Xi0(-Xi);
	else
		LXi = L_Xi0(Xi);

	return LXi;
}

double CGE89_Functions::L_Xi0(double Xi) 
{
	double LXi = 0;
	double y = 1.0/(1.0+0.2316419*fabs(Xi));

	double c1 =  0.319361530;
	double c2 = -0.356563782;
	double c3 =  1.781477937;
	double c4 = -1.821255978;
	double c5 =  1.330274429;

	double H_y = c1*y + c2*y*y + c3*y*y*y + c4*y*y*y*y + c5*y*y*y*y*y;

	double pi = 4.0*atan(1.0);

	LXi = 1.0 - (H_y * exp(-Xi*Xi/2.0) / sqrt(2*pi));
	return LXi;
}


double CGE89_Functions::Eu_SimpleMulti(double *Esi,long num,double P_location,double FvX,double *g_dB) 
{
	// E   :   Y----->X

	long i;
	double maxEsi = Esi[0] , Eu;

	double *segma;	segma=new double[num];

	for(i=0;i<num;i++)
	{
		maxEsi = max(maxEsi,Esi[i]);
		segma[i] = ((FvX>=470)&&(FvX<=862)) ? (9.5 + 0.405*g_dB[i]) : 8.3;
	}
	double Pc , P , Xi ,LXi , dEu;
	Pc = P_location/100.0;

	Eu = maxEsi + 6.0;	//dBuV/m
	while (1)
	{
		P = 1;
		for(i=0;i<num;i++)
		{
			Xi = (Eu-Esi[i])/(segma[i]*sqrt(2.0));
			LXi = L_Xi(Xi);
			P = P*LXi;
		}
		dEu = (Pc-P)/0.05;

		if(fabs(dEu)<0.01)
			return Eu;
		else
			Eu = Eu + dEu;
	}

	delete [] segma;

	return Eu;	//dBuV/m
}


double CGE89_Functions::F_2B_1_2(double f,double Pl,double dh,CString cty)
{
	double y = 0;
	int i = GE89_BAND1345(cty,f) ;
	if((i==1)||(i==3))
		y = F_2B_1( f, Pl);
	else if((i==4)||(i==5))
		y = F_2B_2( f, Pl , dh);

	return y;
}

double CGE89_Functions::F_2B_1(double f,double Pl)
{
	double y;

	double Pl0[] = {1,2,5,10,20,30,40,50,60,70,80,90,95,98,99};
	double loss0[] = {19.1349,16.872,13.4776,10.6157,6.8886,4.1598,2.03,0,-1.8968,-4.1597,-6.7554,-10.416,-13.6107,-16.9385,-19.0683};
	y = Interp2(Pl0,loss0,Pl,15);

	return y;
}

double CGE89_Functions::F_2B_2(double f,double Pl,double dh)
{
	double y;
	double dH0[] = {50,150,300};

	double L50 = F_2B_2_0( f, Pl, 50);
	double L150 = F_2B_2_0( f, Pl, 150);
	double L300 = F_2B_2_0( f, Pl, 300);

	double L0[] = {L50,L150,L300};

	y = Interp1(dH0,L0,dh,3);

	return y;
}

double CGE89_Functions::F_2B_2_0(double f,double Pl,double dh)
{
	double Pl0[] = {1,2,5,10,20,30,40,50,60,70,80,90,95,98,99};
	double loss50[] = {21.0352,18.4977,14.8917,11.5528,7.4125,4.4743,1.8032,0,-2.4706,-5.0082,-7.9464,-11.9531,-15.4255,-18.898,-21.5691};
	double loss150[] = {30.7848,27.3124,21.9701,17.0286,10.885,6.6112,3.0052,0,-3.5391,-7.1451,-11.4189,-17.2953,-22.1033,-27.4456,-31.1851};
	double loss300[] = {36.9284,32.9217,26.2439,20.2339,13.1554,7.8132,3.8065,0,-4.3404,-8.4806,-13.5558,-20.6342,-26.6442,-33.1885,-37.1951};

	double y;
	if		(dh==50)
		y = Interp2(Pl0,loss50,Pl,15);
	else if(dh==150)
		y = Interp2(Pl0,loss150,Pl,15);
	else if(dh==300)
		y = Interp2(Pl0,loss300,Pl,15);

	return y;
}

/////////////////////////////////////Fixed srv GE89////////////////////////////

BOOL CGE89_Functions::Fixed_cty(CString cty)
{
	//GE89 members Countries

	CString cty0[] = {	"AFS","AGL","ALG","ARS","ASC","BDI","BEN","BFA","BHR","BOT",
						"CAF","CME","CNR","COD","COG","COM","CPV","CTI","DJI","EGY",
						"ERI","ETH","GAB","GHA","GMB","GNB","GNE","GUI","IRN","IRQ",
						"KEN","KWT","LBR","LBY","LSO","MAU","MDG","MLI","MOZ","MRC",
						"MTN","MWI","MYT","NGR","NIG","NMB","OMA","QAT","REU","RRW",
						"SDN","SEN","SEY","SHN","SOM","SRL","STP","SWZ","TCD","TGO",
						"TRC","TZA","UAE","UGA","YEM","ZMB","ZWE"};
	for(int i=0;i<67 ;i++)
	{
		if(cty0[i]==cty)
			return TRUE;
	}
	return FALSE;
}

BOOL CGE89_Functions::Fixed_ctyI(CString cty)
{
	CString cty0[] = {"AFS","AGL","BOT","BDI","CME","COD","COG","IRN","LSO","MDG",
					  "MLI","MOZ","MWI","NMB","RRW","SOM","SDN","SWZ","TCD","TZA",
					  "ZWE"};
	for(int i=0;i<21 ;i++)
	{
		if(cty0[i]==cty)
			return TRUE;
	}
	return FALSE;
}

BOOL CGE89_Functions::Fixed_ctyIIIn(CString cty)
{
	CString cty0[] = {"BOT","LSO","MWI","MOZ","NMB","AFS","SWZ","ZMB","ZWE"};
	for(int i=0;i<9 ;i++)
	{
		if(cty0[i]==cty)
			return TRUE;
	}
	return FALSE;
}

BOOL CGE89_Functions::Fixed_Band(double f,CString cty)
{
/*
	BOOL j = FALSE;
	if	   ((f>=47)&&(f<=68)&&Fixed_ctyI(cty))								j = TRUE;
	else if((f>=174)&&(f<=230)&&(cty==_T("IRN")))							j = TRUE;
	else if((f>230)&&(f<=238)&&(Fixed_cty(cty))&&(!Fixed_ctyIIIn(cty)))		j = TRUE;
	else if((f>=246)&&(f<=254)&&(Fixed_cty(cty))&&(!Fixed_ctyIIIn(cty)))	j = TRUE;
	else if((f>=470)&&(f<=790)&&(cty==_T("IRN")))							j = TRUE;
	else if((f>=790)&&(f<=862)&&Fixed_cty(cty))								j = TRUE;
	return j;
*/
	BOOL j = FALSE;
	if	   ((f>=47)&&(f<=68)&&Fixed_ctyI(cty))								j = TRUE;
	else if((f>230)&&(f<=238)&&(Fixed_cty(cty))&&(!Fixed_ctyIIIn(cty)))		j = TRUE;
	else if((f>=246)&&(f<=254)&&(Fixed_cty(cty))&&(!Fixed_ctyIIIn(cty)))	j = TRUE;
	return j;
}


double CGE89_Functions::F_1(double Df,double fc,double fs)
{
	double RPR = -80;
	if		(Df<-6)								RPR = -80;
	else if ((Df>=-6)&&(Df<-2.5))				RPR = -55;
	else if ((Df>=-2.5)&&(Df<-1.5))				RPR = -54;
	else if ((Df>=-1.5)&&(Df<-1.0))				RPR = -45;
	else if ((Df>=-1.0)&&(Df<-0.5))				RPR = -35;
	else if ((Df>=-0.5)&&(Df<-0.2))				RPR = -20;
	else if ((Df>=-0.2)&&(Df<-0.1))				RPR = -5;
	else if ((Df>=-0.1)&&(Df<=0.1))				RPR = 0;
	else if ((Df>0.0)&&(Df<=0.2))				RPR = -5;
	else if ((Df>0.2)&&(Df<=0.5))				RPR = -20;
	else if ((Df>0.5)&&(Df<(fc-0.4)))			RPR = -35;
	else if ((Df>=(fc-0.4))&&(Df<=(fc+0.4)))	RPR = -20;
	else if ((Df> (fc+0.4))&&(Df< (fs-0.4)))	RPR = -35;
	else if ((Df>=(fs-0.4))&&(Df<=(fs+0.4)))	RPR = -10;
	else if ((Df> (fs+0.4))&&(Df<=(fs+1.5)))	RPR = -70;
	else if ((Df> (fs+1.5))&&(Df<=(fs+2.5)))	RPR = -75;
	else if  (Df> (fs+2.5))						RPR = -80;

	return RPR;
}

/////////////////////////////////Mobile srv/////////////////////////////////////

BOOL CGE89_Functions::Mobile_ctyI(CString cty)
{
	CString cty0[] = {"AFS","AGL","BOT","BDI","CME","COD","COG",
					  "LSO","SWZ","TCD","TZA","ZWE","MDG","MLI",
					  "MOZ","MWI","NMB","RRW","SOM","SDN","IRN"};
	for(int i=0;i<21 ;i++)
	{
		if(cty0[i]==cty)
			return TRUE;
	}
	return FALSE;
}

BOOL CGE89_Functions::Mobile_ctyIIIn(CString cty)
{
	CString cty0[] = {"BOT","LSO","MWI","MOZ","NMB","AFS","SWZ","ZMB","ZWE"};
	for(int i=0;i<9 ;i++)
	{
		if(cty0[i]==cty)
			return TRUE;
	}
	return FALSE;
}

BOOL CGE89_Functions::Mobile_Band(double f,CString cty)
{
/*
	BOOL j = FALSE;
	if((f>=47)&&(f<=68)&&Mobile_ctyI(cty))									j = TRUE;
	else if((f>=174)&&(f<=230)&&(cty==_T("IRN")))							j = TRUE;
	else if((f>230)&&(f<=238)&&(Fixed_cty(cty))&&(!Mobile_ctyIIIn(cty)))	j = TRUE;
	else if((f>=470)&&(f<=862)&&(cty==_T("IRN")))							j = TRUE;
	return j;
*/

	BOOL j = FALSE;
	if	   ((f>=47)&&(f<=68)&&Fixed_ctyI(cty))								j = TRUE;
	else if((f>230)&&(f<=238)&&(Fixed_cty(cty))&&(!Fixed_ctyIIIn(cty)))		j = TRUE;
	else if((f>=246)&&(f<=254)&&(Fixed_cty(cty))&&(!Fixed_ctyIIIn(cty)))	j = TRUE;
	return j;
}

double CGE89_Functions::Mobile_Elimit(double Fm)
{
	if((Fm>=47)&&(Fm<=68))
		return 9.0;
	else if((Fm>=174)&&(Fm<=254))
		return 11.0;
	else if((Fm>=470)&&(Fm<=582))
		return 14.0;
	else if((Fm>582)&&(Fm<=862))
		return 28.0;
	else
		return -999.0;
}

double CGE89_Functions::Mobile_Height_gain(double Fm , double h2 , int Zone)
{
	double v = 0;
	if	    ((Fm>=30)&&(Fm<=300))
	{
		if	   (Zone==0)			v = 4.0;
		else if(Zone==1)			v = 5.0;
		else if(Zone==2)			v = 6.0;
	}
	else if((Fm>300)&&(Fm<=3000))
	{
		if	   (Zone==0)			v = 4.0;
		else if(Zone==1)			v = 6.0;
		else if(Zone==2)			v = 8.0;
	}

	double Height_gaint = (v/6.0)*20.0*log10(h2/10.0);
	return Height_gaint;
}

/////////////////////////////////Interference////////////////////////////////////////
double CGE89_Functions::RPR_Int(double Df,double fc,double fs)
{
	double RPR = -30;
	if		(Df<-0.5)							RPR = -30;
	else if ((Df>=-0.5)&&(Df<=0.5))				RPR = 0;
	else if ((Df>0.5)&&(Df<(fc-0.5)))			RPR = -30;
	else if ((Df>=(fc-0.5))&&(Df<=(fc+0.5)))	RPR = -20;
	else if ((Df> (fc+0.5))&&(Df<=(fs-0.2)))	RPR = -30;
	else if ((Df>=(fs-0.2))&&(Df<=(fs+0.2)))	RPR = -10;
	else if  (Df>=(fs+0.2))						RPR = -30;

	return RPR;
}

double CGE89_Functions::F_3_2(double dAz,double Fx_MHz) 
{
	double x1,y1,x2,y2 , y;

	if((Fx_MHz>=47.0)&&(Fx_MHz<=68.0))	//Band I
	{
		x1 = 50;	y1 = 0;
		x2 = 70;	y2 = -6.0;
	}
	else if((Fx_MHz>=174.0)&&(Fx_MHz<=254.0))	//Band III
	{
		x1 = 27;	y1 = 0;
		x2 = 60;	y2 = -12.0;
	}
	else if((Fx_MHz>=470.0)&&(Fx_MHz<=862.0))	//Band IV,V
	{
		x1 = 20;	y1 = 0;
		x2 = 60;	y2 = -16.0;
	}

	if(dAz<x2)
		y = y1+(dAz-x1)*(y2-y1)/(x2-x1);
	else
		y = y2;

	y = min(0,y);

	return y;
}

double CGE89_Functions::AntAdjustmentFactor(double dAz,double FaY_MHz,CString stn_clsX,CString polX,CString polY) 
{
	double AF;
	if     ((stn_clsX==_T("FX"))&&(((polX==_T("V"))&&(polY==_T("H")))||((polX==_T("H"))&&(polY==_T("V")))))
		AF = -16;
	else if((stn_clsX==_T("FB"))&&(((polX==_T("V"))&&(polY==_T("H")))||((polX==_T("H"))&&(polY==_T("V")))))
		AF = -16;
	else if(stn_clsX==_T("ML"))
		AF = -15;
	else
		AF = 0;

//	else
//		AF = F_3_2( dAz, FaY_MHz);

	return AF;
}

double CGE89_Functions::Mobile_Fsmin_Int(double Fm,double necBWm)
{
	double ChannelSpacing;
	if(necBWm<=11)
		ChannelSpacing = 12.5;
	else if ((necBWm>11)&&(necBWm<=14))
		ChannelSpacing = 20;
	else if(necBWm>14)
		ChannelSpacing = 25;

	double Fsmin;
	
	if((Fm>=47)&&(Fm<=68))
	{
		if(ChannelSpacing>12.5)
			Fsmin = 19;
		else
			Fsmin = 22;
	}
	else if((Fm>=174)&&(Fm<=254))
	{
		if(ChannelSpacing>12.5)
			Fsmin = 21;
		else
			Fsmin = 24;
	}
	else if((Fm>=470)&&(Fm<=582))
	{
		if(ChannelSpacing>12.5)
			Fsmin = 24;
		else
			Fsmin = 27;
	}
	else if((Fm>582)&&(Fm<=862))
	{
		if(ChannelSpacing>12.5)
			Fsmin = 38;
		else
			Fsmin = 41;
	}
	else					//	????????
	{
		if(ChannelSpacing>12.5)
			Fsmin = 38;
		else
			Fsmin = 41;
	}

	return Fsmin;
}
