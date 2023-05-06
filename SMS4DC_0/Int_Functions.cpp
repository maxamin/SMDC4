// Int_Functions.cpp: implementation of the CInt_Functions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sms4dc.h"
#include "Int_Functions.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInt_Functions::CInt_Functions()
{

}

CInt_Functions::~CInt_Functions()
{

}



double CInt_Functions::BT655_Table7(CString Xsys,CString Ysys)
{
	double At = 0;
	if((Ysys=="G")||(Ysys=="H"))
		At = -9;
	else if(Ysys=="I")
	{
		At = -9;
		if(Xsys=="L")
			At = 0;
	}
	else if((Ysys=="D")||(Ysys=="D1")||(Ysys=="K")||(Ysys=="K1"))
	{
		if((Xsys=="G")||(Xsys=="D")||(Xsys=="D1")||(Xsys=="K")||(Xsys=="K1"))
			At = -9;
		else if((Xsys=="H")||(Xsys=="I"))
			At = 13;
		else if(Xsys=="L")
			At = -12;
	}
	else if(Ysys=="L")
	{
		if((Xsys=="G")||(Xsys=="D")||(Xsys=="D1")||(Xsys=="K"))
			At = -5;
		else if((Xsys=="H")||(Xsys=="I")||(Xsys=="K1"))
			At = 17;
		else if(Xsys=="L")
			At = -8;
	}
	return At;
}

void CInt_Functions::BT655_Table6(CString freq_stablX,double Doffset,double *At,double *Ac)
{
	double Doffset0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
	double aAtN[] = {45,44,40,34,30,28,27,28,30,34,40,44,45,44,40,34,30,28,27,28,30,34,40,44,45,44,40,34,30,28,27,28,30,34,40,44,45};
	double aAcN[] = {52,51,48,44,40,36,33,36,40,44,48,51,52,51,48,44,40,36,33,36,40,44,48,51,52,51,48,44,40,36,33,36,40,44,48,51,52};
	double aAtP[] = {32,34,30,26,22,22,24,22,22,26,30,34,38,34,30,26,22,22,24,22,22,26,30,34,38,34,30,26,22,22,24,22,22,26,30,34,38};
	double aAcP[] = {36,38,34,30,27,27,30,27,27,30,34,38,42,38,34,30,27,27,30,27,27,30,34,38,42,38,34,30,27,27,30,27,27,30,34,38,42};

	double At0[37] , Ac0[37];
	
	if(freq_stablX=="NORMAL")
		for(int i=0;i<37;i++)
		{
			At0[i] = aAtN[i];
			Ac0[i] = aAcN[i];
		}
	else if(freq_stablX=="PRECISION")
		for(int i=0;i<37;i++)
		{
			At0[i] = aAtP[i];
			Ac0[i] = aAcP[i];
		}
	*At = Interp2(Doffset0,At0,Doffset,37);
	*Ac = Interp2(Doffset0,Ac0,Doffset,37);
}

double CInt_Functions::BT_ProtectionR(double Fx_MHz,double Fy_MHz,double offsetX,double offsetY,CString Xsys,CString Ysys,CString freq_stablX,double E50,double Et) 
{
	double off_freq , Doffset , At = 0 , Ac = 0 , PR = 0;
	off_freq = Fy_MHz-Fx_MHz;
	int Co_Adj;

	if(off_freq==0)			// Co_Channel
		Co_Adj = 0;
	else if(off_freq<0)		// Lower Adj_Channel
		Co_Adj = -1;
	else if(off_freq>0)		// Upper Adj_Channel
		Co_Adj = +1;

	Doffset = fabs(offsetY-offsetX);

	if((Co_Adj == 0)&&(Xsys == "M"))
	{
		if((freq_stablX=="NORMAL")||(freq_stablX=="PRECISION"))
			At = 28.0;
		else if((freq_stablX=="RELAXED"))
			At = 45.0;
	}
	else if((Co_Adj == 1)&&(Xsys == "M"))
		At = -10.0;
	else if((Co_Adj == -1)&&(Xsys == "M"))
		At = -13.0;
	else if((Co_Adj == 0)&&(Xsys != "M"))
	{
		if((freq_stablX=="RELAXED"))
			At = 45.0;
//		else if((freq_stablX!="RELAXED"))	// Table 6	rec BT655
//			BT655_Table6(freq_stablX, Doffset,&At,&Ac);
	}
	else if((Co_Adj == -1) && (Fx_MHz >= 30) && (Fx_MHz <= 300))
	{
		if(Ysys=="L")
			At = -8;
		else
			At = -9;
	}
	else if((Co_Adj == -1) && (Fx_MHz >= 300) && (Fx_MHz <= 3000))	// Table 7	rec BT655
		At = BT655_Table7( Xsys, Ysys);
	else if(Co_Adj == +1)
	{
		if((Xsys=="D")||(Xsys=="K"))
			At = -6;
		else
			At = -12;
	}
	Ac = At + 10.0;

	if((Co_Adj == 0) && (Xsys != "M") && (freq_stablX!="RELAXED"))	// Table 6	rec BT655
			BT655_Table6(freq_stablX, Doffset,&At,&Ac);


	if((E50+Ac)>=(At+Et))
		PR = Ac;
	else
		PR = At;

	return PR;
}



double CInt_Functions::BT419(double dAz,double Fx_MHz) 
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



double CInt_Functions::BS599(double dAz,int Xsys) 
{
	double x1,y1,x2,y2 , y;

	if((Xsys==1)||(Xsys==2))
	{
		x1 = 50;	y1 = 0;
		x2 = 70;	y2 = -6.0;
	}
	else
	{
		x1 = 27;	y1 = 0;
		x2 = 60;	y2 = -12.0;
	}
	if(dAz<x2)
		y = y1+(dAz-x1)*(y2-y1)/(x2-x1);
	else
		y = y2;

	y = min(0,y);

	return y;
}

double CInt_Functions::Eu_PowerSum(double *Esi,long num,double Emin) 
{
	// Esi , Emin ---> dBuV/m

	double Eu , E , E1 , Esum2;

	E1 = pow(10.0,Emin/20.0);	// uV/m
	Esum2 = E1*E1;

	for(long i=0;i<num;i++)
	{
		E = pow( 10.0 , Esi[i]/20.0 );	// uV/m

		Esum2 = Esum2 + E*E;
	}
	Eu = sqrt(Esum2);
	Eu = 20.0*log10(Eu);	//dBuV/m
	
	return Eu;
}


double CInt_Functions::Eu_SimpleMulti(double *Esi,long num,double P_location,double Fx_MHz) 
{
	long i;
	double maxEsi = Esi[0] , Eu;
	for(i=0;i<num;i++)
		maxEsi = max(maxEsi,Esi[i]);

	double segma = ((Fx_MHz>=30)&&(Fx_MHz<=300)) ? 8.3 : 9.5;

	double Pc , P , Xi ,LXi , dEu;
	Pc = P_location/100.0;

	Eu = maxEsi + 6.0;	//dBuV/m
	while (1)
	{
		P = 1;
		for(i=0;i<num;i++)
		{
			Xi = (Eu-Esi[i])/(segma*sqrt(2.0));
			LXi = L_Xi(Xi);
			P = P*LXi;
		}
		dEu = (Pc-P)/0.05;

		if(dEu<0.01)
			return Eu;
		else
			Eu = Eu + dEu;
	}
	return Eu;	//dBuV/m
}



double CInt_Functions::L_Xi(double Xi) 
{
	double LXi = 0;

	if(Xi<0) 
		LXi = 1.0 - L_Xi0(-Xi);
	else
		LXi = L_Xi0(Xi);

	return LXi;
}

double CInt_Functions::L_Xi0(double Xi) 
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

double CInt_Functions::BS412_TABLE_3_4(double f_MHz,BOOL Mono,BOOL Steady,int Df) 
{
	//	for	BC	Rec BS.412-9
	double aF0[]   = {0,25,50,75,100,125,150,175,200,225,250,275,300,325,350,375};
	double PR0[17];
	int i;
	double PR = 0.0;

	if(Df==75)	//TABLE3
	{
		double aMSF75[] = {36,31,24,16,12,9.5,8,7,6,4.5,2,-2,-7,-11.5,-15,-17.5,-20};
		double aMTF75[] = {28,27,22,16,12,9.5,8,7,6,4.5,2,-2,-7,-11.5,-15,-17.5,-20};
		double aSSF75[] = {45,51,51,45,33,24.5,18,11,7,4.5,2,-2,-7,-11.5,-15,-17.5,-20};
		double aSTF75[] = {37,43,43,37,25,18,14,10,7,4.5,2,-2,-7,-11.5,-15,-17.5,-20};

		if	   ((Mono)&&(Steady))
			for (i=0;i<17;i++)
				PR0[i] = aMSF75[i];

		else if((Mono)&&(!Steady))
			for (i=0;i<17;i++)
				PR0[i]=aMTF75[i];

		else if((!Mono)&&(Steady))
			for (i=0;i<17;i++)
				PR0[i]=aSSF75[i];

		else if((!Mono)&&(!Steady))
			for (i=0;i<17;i++)
				PR0[i]=aSTF75[i];

		PR = Interp2(aF0,PR0,f_MHz*1000.0,17);

	}
	else if(Df==50)	//TABLE4
	{
		double aMSF50[] = {39,32,24,15,12,7.5,6,2,-2.5,-3.5,-6,-7.5,-10,-12,-15,-17.5,-20};
		double aMTF50[] = {32,28,22,15,12,7.5,6,2,-2.5,-3.5,-6,-7.5,-10,-12,-15,-17.5,-20};
		double aSSF50[] = {49,53,51,45,33,25,18,12,7,5,2,0,-7,-10,-15,-17.5,-20};
		double aSTF50[] = {41,45,43,37,25,18,14,11,7,5,2,0,-7,-10,-15,-17.5,-20};

		if	   ((Mono)&&(Steady))
			for (i=0;i<17;i++)
				PR0[i] = aMSF50[i];

		else if((Mono)&&(!Steady))
			for (i=0;i<17;i++)
				PR0[i]=aMTF50[i];

		else if((!Mono)&&(Steady))
			for (i=0;i<17;i++)
				PR0[i]=aSSF50[i];

		else if((!Mono)&&(!Steady))
			for (i=0;i<17;i++)
				PR0[i]=aSTF50[i];

		PR = Interp2(aF0,PR0,f_MHz*1000.0,17);
	}
	return PR;
}

double CInt_Functions::BC_ProtectionR(double Fx_MHz,double Fy_MHz,int Xsys,double E50,double Et) 
{
	double As = 0.0, At = 0.0, PR = 0.0;

	double Foffset = fabs(Fx_MHz-Fy_MHz);

	if(Xsys==1)
	{
		As = BS412_TABLE_3_4(Foffset,TRUE,TRUE,75) ;
		At = BS412_TABLE_3_4(Foffset,TRUE,FALSE,75) ;
	}
	else if(Xsys==2)
	{
		As = BS412_TABLE_3_4(Foffset,TRUE,TRUE,50) ;
		At = BS412_TABLE_3_4(Foffset,TRUE,FALSE,50) ;
	}
	else if((Xsys==3)||(Xsys==5))
	{
		As = BS412_TABLE_3_4(Foffset,FALSE,TRUE,50) ;
		At = BS412_TABLE_3_4(Foffset,FALSE,FALSE,50) ;
	}
	else if(Xsys==4)
	{
		As = BS412_TABLE_3_4(Foffset,FALSE,TRUE,75) ;
		At = BS412_TABLE_3_4(Foffset,FALSE,FALSE,75) ;
	}

	if((E50+As)>=(At+Et))
		PR = As;
	else
		PR = At;

	return PR;
}


double CInt_Functions::Interp2(double *D0,double *E0,double d,int num) 
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
