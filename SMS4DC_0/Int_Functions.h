// Int_Functions.h: interface for the CInt_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INT_FUNCTIONS_H__62B09900_400C_4A9F_B401_C4E230F9EBE1__INCLUDED_)
#define AFX_INT_FUNCTIONS_H__62B09900_400C_4A9F_B401_C4E230F9EBE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInt_Functions  
{
public:
	CInt_Functions();
	virtual ~CInt_Functions();


	double BC_ProtectionR(double Fx_MHz,double Fy_MHz,int Xsys,double E50,double Et) ;
	double Eu_SimpleMulti(double *Esi,long num,double P_location,double Fx_MHz) ;
	double Eu_PowerSum(double *Esi,long num,double Emin) ;
	double BS599(double dAz,int Xsys) ;

	double BT_ProtectionR(double Fx_MHz,double Fy_MHz,double offsetX,double offsetY,CString Xsys,CString Ysys,CString freq_stablX,double E50,double Et) ;
	double BT419(double dAz,double Fx_MHz) ;

protected:
	double BS412_TABLE_3_4(double f_MHz,BOOL Mono,BOOL Steady,int Df) ;
	double Interp2(double *D0,double *E0,double d,int num) ;
	double L_Xi0(double Xi) ;
	double L_Xi(double Xi) ;

	void BT655_Table6(CString freq_stablX,double Doffset,double *At,double *Ac);
	double BT655_Table7(CString Xsys,CString Ysys);


};

#endif // !defined(AFX_INT_FUNCTIONS_H__62B09900_400C_4A9F_B401_C4E230F9EBE1__INCLUDED_)
