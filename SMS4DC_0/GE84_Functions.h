// GE84_Functions.h: interface for the CGE84_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GE84_FUNCTIONS_H__84D701D2_85DF_4B85_9AF4_E53848BE82B1__INCLUDED_)
#define AFX_GE84_FUNCTIONS_H__84D701D2_85DF_4B85_9AF4_E53848BE82B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGE84_Functions  
{
public:
	CGE84_Functions();
	virtual ~CGE84_Functions();

	double GE84_1(int p,double erpW,double h1=10) ;
	double GE84_BT1(int p,double erpW,double h1, double f_MHz) ;
//	double GE84_ProtectionR(CString Yst_cls,double Fx_MHz,double Fy_MHz,int Xsys,int Ysys,double E50,double Et,CString Ymod="FM") ;
	double GE84_ProtectionR(CString Yst_cls,double Fx_MHz,double Fy_MHz,int Xsys,int Ysys,double E50,double Et,CString Ymod="F") ;
	BOOL CTRY_Check(CString str);

protected:
	void TABLE_4_1(double *D010,double *D037,double *D075,double *D0150,double *D0300,double *D0600,double *D01200,double *D01800) ;
	void TABLE_4_2(double *D010,double *D037,double *D075,double *D0150,double *D0300,double *D0600,double *D01200,double *D01800) ;
	void TABLE_4_3(double *D010,double *D037,double *D075,double *D0150,double *D0300,double *D0600,double *D01200,double *D01800) ;
	void TABLE_4_4(double *D0) ;
	double GE84_0(int p,double erpW,double h1=10) ;
	double Interp1(double *D0,double *E0,double d,int num) ;

	void TABLE_4_5(double *D010,double *D037,double *D075,double *D0150,double *D0300,double *D0600,double *D01200,double *D01800) ;
	void TABLE_4_6(double *D010,double *D037,double *D075,double *D0150,double *D0300,double *D0600,double *D01200,double *D01800) ;
	void TABLE_4_7(double *D010,double *D037,double *D075,double *D0150,double *D0300,double *D0600,double *D01200,double *D01800) ;
	double TABLE_4_8(double f_MHz) ;
	double GE84_BT0(int p,double erpW,double h1=10) ;
	double Interp2(double *D0,double *E0,double d,int num) ;

	double SM851_TABLE_1213(double f_MHz,BOOL Mono,BOOL Steady,BOOL Fm,int Df) ;
	double GE84_TABLE_2_3(double f_MHz,BOOL Steady,int DfW) ;
	double GE84_TABLE_2_7(double f_MHz,BOOL Mono) ;

};

#endif // !defined(AFX_GE84_FUNCTIONS_H__84D701D2_85DF_4B85_9AF4_E53848BE82B1__INCLUDED_)
