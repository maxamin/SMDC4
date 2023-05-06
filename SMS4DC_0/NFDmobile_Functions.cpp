// NFDmobile_Functions.cpp: implementation of the CNFDmobile_Functions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sms4dc.h"
#include "NFDmobile_Functions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNFDmobile_Functions::CNFDmobile_Functions()
{

}

CNFDmobile_Functions::~CNFDmobile_Functions()
{

}



double CNFDmobile_Functions::Interp2(double *D0,double *E0,double d,int num) 
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
		{
			n2--;
			if (n2==0)
				break;
		}
		d2=D0[n2+1];E2=E0[n2+1];
		////////////////////////////////////////////////
	}
	Eb=((d1==d2) ? E1 : E1+(E2-E1)*(d-d1)/(d2-d1));

	return Eb;

}




double CNFDmobile_Functions::table1_RxBW25(double TxBW , double Df)
{
	//Rx Channel Spacing =  25kHz

	double Df0[]	=	{0,5,6.25,10,12.5,20,25};
	double aInc5[]	=	{0,0.7,1.2,14.5,40.6,72,79};
	double aInc6[]	=	{0,0.6,1.0,12.0,36.9,70.3,78.3};
	double aInc10[]	=	{0,0.6,0.7,7.3,27.1,66.2,75.5};
	double aInc12[]	=	{0,0.4,0.5,5.4,22.4,63.2,73.9};
	double aInc20[]	=	{0,0,0,2.6,11.7,56.1,69.1};
	double aInc25[]	=	{0,-0.3,-0.2,1.9,7.7,50,65.9};

	int i;
	double aInc[7];

	if (TxBW==5.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc5[i];
	else if (TxBW==6.25)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc6[i];
	else if (TxBW==10.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc10[i];
	else if (TxBW==12.5)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc12[i];
	else if (TxBW==20.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc20[i];
	else if (TxBW==25.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc25[i];

	double NFDm = Interp2(Df0,aInc,Df,7) ;
	return NFDm;
}


double CNFDmobile_Functions::table2_RxBW20(double TxBW , double Df)
{
	//Rx Channel Spacing =  20kHz

	double Df0[]	=	{0,5,6.25,10,12.5,20,25};
	double aInc5[]	=	{0,1.5,7.2,14,33,74.6,81.3};
	double aInc6[]	=	{0,1.5,7,13.1,30.5,73.1,80.5};
	double aInc10[]	=	{0,1.5,6,10.9,24.9,68.9,78.2};
	double aInc12[]	=	{0,1.5,5.1,10,22,66.4,76.7};
	double aInc20[]	=	{0,1.7,3.8,8,15.4,59.1,72.1};
	double aInc25[]	=	{0,1.9,3.4,7.2,12.3,53.5,69.1};

	int i;
	double aInc[7];

	if (TxBW==5.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc5[i];
	else if (TxBW==6.25)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc6[i];
	else if (TxBW==10.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc10[i];
	else if (TxBW==12.5)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc12[i];
	else if (TxBW==20.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc20[i];
	else if (TxBW==25.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc25[i];

	double NFDm = Interp2(Df0,aInc,Df,7) ;
	return NFDm;
}


double CNFDmobile_Functions::table3_RxBW12(double TxBW , double Df)
{
	//Rx Channel Spacing =  12.5kHz

	double Df0[]	=	{0,5,6.25,10,12.5,20,25};
	double aInc5[]	=	{0,2.7,7.1,41.3,57.8,73,76.6};
	double aInc6[]	=	{0,2.7,6.5,37.7,55.6,72.7,76.7};
	double aInc10[]	=	{0,2.9,5.4,29.2,48.9,71.5,76.8};
	double aInc12[]	=	{0,2.6,4.4,24.1,43.2,69.9,76.2};
	double aInc20[]	=	{0,1.7,2.7,13.3,28,64.7,72.9};
	double aInc25[]	=	{0,1.5,2.3,9.4,20.6,60.7,70.2};

	int i;
	double aInc[7];

	if (TxBW==5.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc5[i];
	else if (TxBW==6.25)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc6[i];
	else if (TxBW==10.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc10[i];
	else if (TxBW==12.5)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc12[i];
	else if (TxBW==20.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc20[i];
	else if (TxBW==25.0)
	for( i=0;i<7;i++)
		aInc[i]	=	aInc25[i];

	double NFDm = Interp2(Df0,aInc,Df,7) ;
	return NFDm;
}

double CNFDmobile_Functions::NFDmobile(double TxNecessaryBandwidth , double RxNecessaryBandwidth , double Df)
{
	double NFDm = 0;

	double TxNBW = TxNecessaryBandwidth ,  RxNBW = RxNecessaryBandwidth ;
	double TxChannelSpacing , RxChannelSpacing;

	if		 (TxNBW<=4.4)					TxChannelSpacing = 5.0;
	else if ((TxNBW>4.4)&&(TxNBW<=5.5))		TxChannelSpacing = 6.25;
	else if ((TxNBW>5.5)&&(TxNBW<=8.8))		TxChannelSpacing = 10.0;
	else if ((TxNBW>8.8)&&(TxNBW<=11.0))	TxChannelSpacing = 12.5;
	else if ((TxNBW>11.0)&&(TxNBW<=14.0))	TxChannelSpacing = 20.0;
	else if ((TxNBW>14.0)&&(TxNBW<=16.0))	TxChannelSpacing = 25.0;
	else									TxChannelSpacing = 25.0;  //	(TxNBW>16.0)   ???????
											
	if       (RxNBW<=11.0)					RxChannelSpacing = 12.5;
	else if ((RxNBW>11.0)&&(RxNBW<=14.0))	RxChannelSpacing = 20.0;
	else if  (RxNBW>14.0)					RxChannelSpacing = 25.0;

	if      (RxChannelSpacing==12.5)	NFDm = table3_RxBW12( TxChannelSpacing ,  Df);
	else if (RxChannelSpacing==20.0)	NFDm = table2_RxBW20( TxChannelSpacing ,  Df);
	else if (RxChannelSpacing==25.0)	NFDm = table1_RxBW25( TxChannelSpacing ,  Df);
	return NFDm;
}


/////////////////////////////////////////////////////////////////////////////////////////
double CNFDmobile_Functions::table4_TxBW25(double RxBW , double Df)
{
	//Tx Channel Spacing =  25kHz		TxEmission = 25K0G7W

	double Df0[]	=	{0,5,6.25,7.5,8.75,10,12.5,15,17.5,20,22.5,25,27.5,30};
	double aInc10[]	=	{0,0.3,0.6,1.2,2.4,4,8,16.2,38.3,58.5,60.6,62.3,63,64.8};
	double aInc12[]	=	{0,0.6,1,1.5,2.4,3.4,6.6,12.8,26.9,53.7,59.6,61.8,62.5,63.6};
	double aInc20[]	=	{0,0.9,1.4,1.8,2.4,3.1,4.7,7.7,13.7,25.2,41.8,59.7,61.3,62.2};
	double aInc25[]	=	{0,1.4,2,2.4,2.7,3,4.3,6.4,10.3,17.6,28.7,43.4,58.8,60.9};

	int i;
	double aInc[14];

	if (RxBW==10.0)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc10[i];
	else if (RxBW==12.5)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc12[i];
	else if (RxBW==20.0)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc20[i];
	else if (RxBW==25.0)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc25[i];

	double NFDm = Interp2(Df0,aInc,Df,14) ;
	return NFDm;
}


double CNFDmobile_Functions::table5_RxBW25(double TxBW , double Df)
{
	//Rx Channel Spacing =  25.0kHz		RxEmission = 25K0G7W	

	double Df0[]	=	{0,5,6.25,7.5,8.75,10,12.5,15,17.5,20,22.5,25,27.5,30};
	double aInc5[]	=	{0,0.1,0,1.3,3.7,8.5,34.8,62.6,67.4,69.9,71.5,73,73.9,75};
	double aInc6[]	=	{0,0.1,0.2,1.4,3.7,8.4,32,62.6,67.5,69.9,71.5,73,73.9,75};
	double aInc10[]	=	{0,0.1,0.2,1.4,3.7,7.4,25.8,58.2,67.1,69.8,71.5,72.9,73.8,75};
	double aInc12[]	=	{0,0.1,0.2,1.3,3.2,6.3,22.6,53.9,66.4,70,71.8,73,73.9,75.1};
	double aInc20[]	=	{0,0.4,0.8,1.4,2.5,4.7,15.6,43,64.8,69.5,71.7,72.9,73.8,75};
	double aInc25[]	=	{0,0.1,0.7,1.4,2.1,4.2,12.1,34.8,58.9,69.2,71.2,72.4,73.5,74.7};

	int i;
	double aInc[14];

	if (TxBW==5.0)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc5[i];
	else if (TxBW==6.25)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc6[i];
	else if (TxBW==10.0)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc10[i];
	else if (TxBW==12.5)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc12[i];
	else if (TxBW==20.0)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc20[i];
	else if (TxBW==25.0)
	for( i=0;i<14;i++)
		aInc[i]	=	aInc25[i];

	double NFDm = Interp2(Df0,aInc,Df,14) ;
	return NFDm;
}
double CNFDmobile_Functions::Emission2NBW(CString Emission) 
{
	double NBW_kHz = 0;
	CString c , BWs = Emission.Left(4);
	BWs.MakeUpper();

	for(int i=0;i<4;i++)
	{
		c = BWs.Mid(i,1);
		if(c=="H")
		{
			BWs.Replace('H','.');
			NBW_kHz = (0.001)*atof(BWs);
			return NBW_kHz;
		}
		else if(c=="K")
		{
			BWs.Replace('K','.');
			NBW_kHz = atof(BWs);
			return NBW_kHz;
		}
		else if(c=="M")
		{
			BWs.Replace('M','.');
			NBW_kHz = (1000.0)*atof(BWs);
			return NBW_kHz;
		}
		else if(c=="G")
		{
			BWs.Replace('G','.');
			NBW_kHz = (1000000.0)*atof(BWs);
			return NBW_kHz;
		}
	}
	return NBW_kHz;
}


double CNFDmobile_Functions::NFDmobile1(CString TxEmission ,CString RxEmission ,double Df, BOOL Emergency)
{
	double NFDm = 0;

	if(Df>25)
		NFDm = 82;
	else
	{
		double TxNBW = Emission2NBW(TxEmission) ,	RxNBW = Emission2NBW(RxEmission) ;
		int TxN6 = atoi(TxEmission.Mid(5,1)) ,		RxN6 = atoi(RxEmission.Mid(5,1));

		BOOL TxTetra = FALSE , RxTetra = FALSE;
		if(TxEmission==_T("25K0G7W"))	TxTetra = TRUE;
		if(RxEmission==_T("25K0G7W"))	RxTetra = TRUE;

		BOOL TxAnalogue = FALSE , RxAnalogue = FALSE;
		if((TxN6!=1)&&(TxN6!=2)&&(TxN6!=7)&&(TxN6!=9))		TxAnalogue = TRUE;
		if((RxN6!=1)&&(RxN6!=2)&&(RxN6!=7)&&(RxN6!=9))		RxAnalogue = TRUE;

		BOOL TxDigital = FALSE , RxDigital = FALSE;
		if(((TxN6==1)||(TxN6==2)||(TxN6==7)||(TxN6==9)))	TxDigital = TRUE;
		if(((RxN6==1)||(RxN6==2)||(RxN6==7)||(RxN6==9)))	RxDigital = TRUE;

		double TxChannelSpacing , RxChannelSpacing;
		if		 (TxNBW<=4.4)					TxChannelSpacing = 5.0;
		else if ((TxNBW>4.4)&&(TxNBW<=5.5))		TxChannelSpacing = 6.25;
		else if ((TxNBW>5.5)&&(TxNBW<=8.8))		TxChannelSpacing = 10.0;
		else if ((TxNBW>8.8)&&(TxNBW<=11.0))	TxChannelSpacing = 12.5;
		else if ((TxNBW>11.0)&&(TxNBW<=14.0))	TxChannelSpacing = 20.0;
		else if ((TxNBW>14.0)&&(TxNBW<=16.0))	TxChannelSpacing = 25.0;
		else									TxChannelSpacing = 25.0;  //	(TxNBW>16.0)   ???????
												
		if       (RxNBW<=11.0)					RxChannelSpacing = 12.5;
		else if ((RxNBW>11.0)&&(RxNBW<=14.0))	RxChannelSpacing = 20.0;
		else if  (RxNBW>14.0)					RxChannelSpacing = 25.0;

		if((TxAnalogue)&&(RxAnalogue)&&(Emergency==0))
		{
			if (RxChannelSpacing==12.5)			NFDm = table3_RxBW12( TxChannelSpacing ,  Df);
			else if (RxChannelSpacing==20.0)	NFDm = table2_RxBW20( TxChannelSpacing ,  Df);
			else if (RxChannelSpacing==25.0)	NFDm = table1_RxBW25( TxChannelSpacing ,  Df);
		}
		else if((TxTetra)&&(RxAnalogue))		NFDm = table4_TxBW25(RxChannelSpacing , Df);
		else if((TxAnalogue)&&(RxTetra))		NFDm = table5_RxBW25(TxChannelSpacing , Df);
		else if(((TxDigital)||(Emergency))&&((RxDigital)||(Emergency)))
		{
			double B1 = max(TxChannelSpacing,RxChannelSpacing);
			double B2 = min(TxChannelSpacing,RxChannelSpacing);
			if(Df < ((B1+B2)/2.0))	NFDm = 0;
			else					NFDm = 45;
		}
	}
	return NFDm;
}