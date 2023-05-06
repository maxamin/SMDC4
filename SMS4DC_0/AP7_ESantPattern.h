// AP7_ESantPattern.h: interface for the CAP7_ESantPattern class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AP7_ESANTPATTERN_H__CA4A5D66_DC57_413F_B947_4405A22C6319__INCLUDED_)
#define AFX_AP7_ESANTPATTERN_H__CA4A5D66_DC57_413F_B947_4405A22C6319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAP7_ESantPattern  
{
public:
	CAP7_ESantPattern();
	virtual ~CAP7_ESantPattern();

	double ESantTuser(double phi,long ntc_id, CString beam_name, CString emi_rcp,
								 double Gmax,CString pattern,
								 CString coefA,CString coefB,CString coefC,CString coefD,CString PHI1);

	double func_Pr0_ES2ES(double frq_MHzY, BOOL rSysA) ;
	double func_Pr0_ES2FX(double frq_MHzY, BOOL rSysA, double timeP) ;
	double func_Pr0_FX2ES(double frq_MHzY, BOOL rSysA, double timeP) ;

protected:
	double ESant1(double phi,double Gmax);
	double ESant2(double phi,double Gmax,double coefA,double coefB);
	double ESant3(double phi,double Gmax,double coefA,double coefB,double PHI1);
	double ESant4(double phi,double Gmax,double coefA,double coefB,double coefC,double coefD,double PHI1);
	double ESant5();
	double ESant6(double phi,double Gmax);
	double ESant7(double phi,double Gmax,double x);
	double ESant8(double phi,double Gmax);
	double ESant9(double phi,double Gmax);
	double ESant10(double phi,double Gmax);

	double ESantT(double phi,double Gmax,CString pattern,
								 CString coefA,CString coefB,CString coefC,CString coefD,CString PHI1);

	BOOL ESantUser(double phi,long ntc_id, CString beam_name, CString emi_rcp, double *G);
	double Interp2(double *D0,double *E0,double d,long num) ;

};

#endif // !defined(AFX_AP7_ESANTPATTERN_H__CA4A5D66_DC57_413F_B947_4405A22C6319__INCLUDED_)
