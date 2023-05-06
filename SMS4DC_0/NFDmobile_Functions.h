// NFDmobile_Functions.h: interface for the CNFDmobile_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NFDMOBILE_FUNCTIONS_H__AB7A85A6_600C_42E7_A059_C4E065975B78__INCLUDED_)
#define AFX_NFDMOBILE_FUNCTIONS_H__AB7A85A6_600C_42E7_A059_C4E065975B78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNFDmobile_Functions  
{
public:
	CNFDmobile_Functions();
	virtual ~CNFDmobile_Functions();

	double NFDmobile(double TxNecessaryBandwidth , double RxNecessaryBandwidth , double Df);
	double NFDmobile1(CString TxEmission ,CString RxEmission , double Df, BOOL Emergency);

protected:
	double Interp2(double *D0,double *E0,double d,int num) ;
	double table1_RxBW25(double TxBW , double Df);
	double table2_RxBW20(double TxBW , double Df);
	double table3_RxBW12(double TxBW , double Df);

	double table4_TxBW25(double RxBW , double Df);
	double table5_RxBW25(double TxBW , double Df);

	double Emission2NBW(CString Emission) ;


};

#endif // !defined(AFX_NFDMOBILE_FUNCTIONS_H__AB7A85A6_600C_42E7_A059_C4E065975B78__INCLUDED_)
