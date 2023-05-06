// AP7_ESantPattern.cpp: implementation of the CAP7_ESantPattern class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sms4dc.h"
#include "AP7_ESantPattern.h"

#include <math.h>
#include <afxdb.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAP7_ESantPattern::CAP7_ESantPattern()
{

}

CAP7_ESantPattern::~CAP7_ESantPattern()
{

}


double CAP7_ESantPattern::ESantTuser(double phi,long ntc_id, CString beam_name, CString emi_rcp,
								 double Gmax,CString pattern,
								 CString coefA,CString coefB,CString coefC,CString coefD,CString PHI1)
{
	double G = 0;

	BOOL flag = ESantUser(phi,ntc_id, beam_name, emi_rcp, &G);
	if(flag)
		return G;

	G = ESantT(phi,Gmax,pattern, coefA,coefB,coefC,coefD,PHI1);
	return G;
}



BOOL CAP7_ESantPattern::ESantUser(double phi,long ntc_id, CString beam_name, CString emi_rcp, double *G)
{
	BOOL flag = FALSE;
	long k =0;
	double OffAng[500],AntGain[500];

	CString SQL1, str;
	CDatabase DB;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	DB.Open(_T(m_DB),false,false,_T("ODBC;"),false);
	CRecordset rs;
	rs.m_pDatabase=&DB;

	SQL1.Format("SELECT ntc_id, emi_rcp, beam_name, ESAntPatt.AntID, OffAng, AntGain FROM e_ant INNER JOIN ESAntPatt ON e_ant.AntID = ESAntPatt.AntID WHERE (((ntc_id)=%ld) AND ((emi_rcp)=\'%s\') AND ((beam_name)=\'%s\')) ORDER BY OffAng;",ntc_id,emi_rcp,beam_name);
 	rs.Open(CRecordset::snapshot, SQL1);

	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue((short)4,str);		OffAng[k]  = atof(str);
			rs.GetFieldValue((short)5,str);		AntGain[k] = atof(str);
			k++;
			rs.MoveNext();
		}
	}
	rs.Close();
	DB.Close();
	if(k>2)
	{
		*G = Interp2(OffAng,AntGain,phi,k) ;
		flag = TRUE;
	}
	return flag;
}

double CAP7_ESantPattern::Interp2(double *D0,double *E0,double d,long num) 
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



double CAP7_ESantPattern::ESantT(double phi,double Gmax,CString pattern,
								 CString coefA,CString coefB,CString coefC,CString coefD,CString PHI1)
{
	double G = 0;
	pattern.MakeUpper();	pattern.TrimLeft();		pattern.TrimRight();

    if(pattern==_T("ND"))
        G = ESant5();
    else if((pattern==_T("AP28"))||(pattern==_T("AP8"))||(pattern==_T("AP29")))
        G = ESant1(phi,Gmax);
    else if((pattern==_T("AP7"))||(pattern==_T("REC-1448")))
        G = ESant6(phi,Gmax);
    else if(pattern==_T("REC-465"))
        G = ESant7(phi,Gmax,32.0);
    else if(pattern==_T("AP30A"))
        G = ESant8(phi,Gmax);
    else if(pattern==_T("REC-1295"))
        G = ESant9(phi,Gmax);
    else if(pattern==_T("REC-580"))
        G = ESant10(phi,Gmax);
    else if((!coefA.IsEmpty())&&(!coefB.IsEmpty())&&(coefC.IsEmpty())&&(coefD.IsEmpty())&&(PHI1.IsEmpty())
																			&&(pattern==_T("A-B*LOG(FI)")))
		G = ESant2(phi,Gmax,atof(coefA),atof(coefB));

    else if((!coefA.IsEmpty())&&(!coefB.IsEmpty())&&(coefC.IsEmpty())&&(coefD.IsEmpty())&&(!PHI1.IsEmpty())
																			&&(pattern==_T("A-B*LOG(FI)")))
        G = ESant3(phi,Gmax,atof(coefA),atof(coefB),atof(PHI1));

    else if((!coefA.IsEmpty())&&(!coefB.IsEmpty())&&(!coefC.IsEmpty())&&(!coefD.IsEmpty())&&(!PHI1.IsEmpty())
																						&&(pattern.IsEmpty()))
        G = ESant4(phi,Gmax,atof(coefA),atof(coefB),atof(coefC),atof(coefD),atof(PHI1));

    else if((!coefA.IsEmpty())&&(coefB.IsEmpty())&&(coefC.IsEmpty())&&(coefD.IsEmpty())&&(PHI1.IsEmpty())
																			&&(pattern==_T("A-25*LOG(FI)")))
        G = ESant7(phi,Gmax,atof(coefA));

    else if((coefA.IsEmpty())&&(coefB.IsEmpty())&&(coefC.IsEmpty())&&(coefD.IsEmpty())&&(PHI1.IsEmpty())
																			&&(pattern==_T("A-25*LOG(FI)")))
        G = ESant7(phi,Gmax,32);
    else
        G = ESant7(phi,Gmax,32.0);
	return G;
}



double CAP7_ESantPattern::ESant1(double phi,double Gmax)
{
	double DL = pow(10.0 , (Gmax-7.7)/20.0);
	double G1 = 2.0 + 15.0 * log10(DL);
	double phim = (20.0/DL) * sqrt(Gmax-G1);
	double phir = 15.85 * pow(DL,-0.6);

	double G = 0;
	if(DL>=100.0)
	{
		if((phi>=0)&&(phi<phim))
            G = Gmax - 0.0025*pow(DL*phi,2.0);
		else if((phi>=phim)&&(phi<phir))
            G = G1;
		else if((phi>=phir)&&(phi<48.0))
            G = 32.0 - 25.0*log10(phi);
		else if((phi>=48.0)&&(phi<=180.0))
            G = -10.0;
	}
	else
	{
		if((phi>=0)&&(phi<phim))
            G = Gmax - 0.0025*pow(DL*phi,2.0);
		else if((phi>=phim)&&(phi<(100.0/DL)))
            G = G1;
		else if((phi>=(100.0/DL))&&(phi<48.0))
            G = 52.0 - 10.0*log10(DL) - 25.0*log10(phi);
		else if((phi>=48.0)&&(phi<=180.0))
            G = 10.0 - 10.0*log10(DL);
	}
	return G;
}

double CAP7_ESantPattern::ESant2(double phi,double Gmax,double coefA,double coefB)
{
	double G = 0;

	if((phi>=0)&&(phi<1.0))
        G = Gmax;
    else
	{
        double G1 = (coefA - coefB*log10(phi));
        G = max(G1 , -10.0);
	}
	return G;
}

double CAP7_ESantPattern::ESant3(double phi,double Gmax,double coefA,double coefB,double PHI1)
{
	double G = 0;
	if((phi>=0)&&(phi<PHI1))
        G = Gmax;
    else
	{
        double G1 = ESant1(PHI1,Gmax);
        double G2 = coefA - coefB*log10(PHI1);
        double G3 = ESant1(phi,Gmax);
        if(G1>G2)
            G = min(G2,G3);
        else
            G = G3;
	}
	return G;
}

double CAP7_ESantPattern::ESant4(double phi,double Gmax,double coefA,double coefB,double coefC,double coefD,double PHI1)
{
	double G = 0;

	if(phi<1)
        G = Gmax;
    else if((phi>=1)&&(phi<=PHI1))
        G = coefA - coefB*log10(phi);
    else
	{
        double G0 = ESant4(PHI1,Gmax,coefA,coefB,coefC,coefD,PHI1);
        G = max(min(G0,(coefC-coefD*log10(phi))),-10);
	}
	return G;
}


double CAP7_ESantPattern::ESant5()
{
	return 0.0;
}

double CAP7_ESantPattern::ESant6(double phi,double Gmax)
{
	double DL,phim,phir,G1,G = 0;

	DL = pow(10.0 , (Gmax-7.7)/20.0);
	if(DL>=100)
	{
    	G1 = -1.0 + 15.0*log10(DL);
    	phir = 15.85 * pow(DL,-0.6);
	}
    else
	{
    	G1 = -21.0 + 25.0*log10(DL);
        phir = 100.0/(DL);
	}
	phim = (20.0/DL) * sqrt(Gmax-G1);

	if((phi>=0)&&(phi<phim))
        G = Gmax - 0.0025*pow(DL*phi,2.0);
	else if((phi>=phim)&&(phi<phir))
        G = G1;
	else if((phi>=phir)&&(phi<36.0))
        G = 29.0 - 25.0*log10(phi);
	else if((phi>=36.0)&&(phi<=180.0))
        G = -10.0;
	return G;
}

double CAP7_ESantPattern::ESant7(double phi,double Gmax,double x)
{
	double DL,phim,G1,G = 0;
	DL = pow(10.0 , (Gmax-8.4)/20.0);
	if(DL>=100.0)
    	G1 = x;
    else
    	G1 = 2.0 + 15.0*log10(DL);
	phim = (20.0/DL) * sqrt(Gmax-G1);
	if(phi<=phim)
        G = Gmax - 0.0025*pow(DL*phi,2.0);
	else if((phi>phim)&(DL>=100.0))
        G = max(min(G1,x-25.0*log10(phi)),-10.0);
	else if((phi>phim)&(DL<100.0))
        G = max(min(G1,52.0-10.0*log10(DL)-25.0*log10(phi)),10.0-10.0*log10(DL));
	return G;
}

double CAP7_ESantPattern::ESant8(double phi,double Gmax)
{
	double G = 0;

    if((phi>=0)&&(phi<0.1))
        G = Gmax;
    else if((phi>=0.1)&&(phi<0.32))
        G = Gmax-21.0-20.0*log10(phi);
    else if((phi>=0.32)&&(phi<0.44))
        G = Gmax-5.7-53.2*(phi*phi);
    else if((phi>=0.44)&&(phi<=48.0))
        G = Gmax-25.0-25.0*log10(phi);
    else if(phi>48.0)
        G = Gmax-67;

	return G;
}


double CAP7_ESantPattern::ESant9(double phi,double Gmax)
{
	double G = 0;

    if((phi>=0)&&(phi<0.1))
        G = Gmax;
    else if((phi>=0.1)&&(phi<0.32))
        G = Gmax-21.0-20.0*log10(phi);
    else if((phi>=0.32)&&(phi<0.54))
        G = Gmax-5.7-53.2*(phi*phi);
    else if((phi>=0.54)&&(phi<=36.31))
        G = Gmax-28.0-25.0*log10(phi);
    else if(phi>36.31)
        G = Gmax-67;

	return G;
}


double CAP7_ESantPattern::ESant10(double phi,double Gmax)
{
	double DL,phir,phim,G1,G = 0;
	DL = pow(10.0 , (Gmax-8.4)/20.0);

	if(DL>150.0)
    	G1 = -1.0 + 15.0*log10(DL);
    else
    	G1 = 2.0 + 15.0*log10(DL);
	phim = (20.0/DL) * sqrt(Gmax-G1);
	phir = (100.0/DL);

	if(DL>150.0)
	{
		if(phi<=phim)
            G = Gmax - 0.0025*pow(DL*phi,2.0);
		else if((phi>phim)&&(phi<19.95))
            G = min(G1,29.0-25.0*log10(phi));
		else if(phi>19.95)
            G = max(min(-3.5,32.0-25.0*log10(phi)),-10.0);
    }
    else if((DL>=100.0)&&(DL<=150.0))
	{
		if(phi<=phim)
            G = Gmax - 0.0025*pow(DL*phi,2.0);
        else
            G = max(min(-3.5,32.0-25.0*log10(phi)),-10);
	}
    else if((DL>=50.0)&&(DL<=100.0))
	{
		if(phi<=phim)
            G = Gmax - 0.0025*pow(DL*phi,2.0);
		else if((phi>phim)&&(phi<=phir))
            G = G1;
		else if((phi>phir)&&(phi<=20))
            G = 32.0 - 25.0*log10(phi);
        else if(phi>20.0)
            G = max(52.0-10.0*log10(DL)-25.0*log10(phi),10.0-10.0*log10(DL));
	}
    else if(DL<50.0)
	{
		if(phi<=phim)
            G = Gmax - 0.0025*pow(DL*phi,2.0);
        else
            G = max(min(G1,52.0-10.0*log10(DL)-25.0*log10(phi)),10.0-10.0*log10(DL));
	}

	return G;
}

////////////////////////////////////////////////////////////////////////

double CAP7_ESantPattern::func_Pr0_FX2ES(double frq_MHzY, BOOL rSysA, double timeP) 
{
	double J, W, Ms, Nl = 1, Pr0;
	if((frq_MHzY>=1000)&&(frq_MHzY<10000)&&(rSysA))
	{
		J = -10;		W = 4;		Ms = 2;
	}
	else if((frq_MHzY>=1000)&&(frq_MHzY<10000)&&(!rSysA))
	{
		J = -10;		W = 0;		Ms = 2;
	}
	else if((frq_MHzY>=10000)&&(frq_MHzY<15000)&&(rSysA))
	{
		J = -8.5;		W = 4;		Ms = 4;
	}
	else if((frq_MHzY>=10000)&&(frq_MHzY<15000)&&(!rSysA))
	{
		J = -8.5;		W = 0;		Ms = 4;
	}
	else if((frq_MHzY>=15000)&&(frq_MHzY<=40000))
	{
		J = -7;		W = 0;		Ms = 6;
	}

	if(timeP>=1)	Pr0 = J - W;
	else			Pr0 = 10.0*log10(pow(10.0,Ms/10.0)-1.0) + Nl - W;

	return Pr0;
}

double CAP7_ESantPattern::func_Pr0_ES2FX(double frq_MHzY, BOOL rSysA, double timeP) 
{
	double J, W = 0, Ms, Nl = 0, Pr0;
	if((frq_MHzY>=1000)&&(frq_MHzY<10000)&&(rSysA))
	{
		J = 9;		Ms = 33;
	}
	else if((frq_MHzY>=1000)&&(frq_MHzY<10000)&&(!rSysA))
	{
		J = -6;		Ms = 37;
	}
	else if((frq_MHzY>=10000)&&(frq_MHzY<15000)&&(rSysA))
	{
		J = 13;		Ms = 33;
	}
	else if((frq_MHzY>=10000)&&(frq_MHzY<15000)&&(!rSysA))
	{
		J = -2;		Ms = 37;
	}
	else if((frq_MHzY>=15000)&&(frq_MHzY<=40000))
	{
		J = 0;		Ms = 25;
	}

	if(timeP>=1)	Pr0 = J - W;
	else			Pr0 = 10.0*log10(pow(10.0,Ms/10.0)-1.0) + Nl - W;

	return Pr0;
}

double CAP7_ESantPattern::func_Pr0_ES2ES(double frq_MHzY, BOOL rSysA) 
{
	double W, Ms, Nl = 1, Pr0;
	if((frq_MHzY>=1000)&&(frq_MHzY<2000))
	{
		W = 0;		Ms = 0.9;
	}
	else if((frq_MHzY>=2000)&&(frq_MHzY<10000))
	{
		W = 0;		Ms = 2;
	}
	else if((frq_MHzY>=10000)&&(frq_MHzY<15000)&&(rSysA))
	{
		W = 4;		Ms = 7;
	}
	else if((frq_MHzY>=10000)&&(frq_MHzY<15000)&&(!rSysA))
	{
		W = 0;		Ms = 4;
	}
	else if((frq_MHzY>=15000)&&(frq_MHzY<=40000))
	{
		W = 0;		Ms = 6;
	}

	Pr0 = 10.0*log10(pow(10.0,Ms/10.0)-1.0) + Nl - W;

	return Pr0;
}












