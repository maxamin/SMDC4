// GE89_Functions.h: interface for the CGE89_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GE89_FUNCTIONS_H__23D83FC6_BFBA_4931_9610_F42A239A112D__INCLUDED_)
#define AFX_GE89_FUNCTIONS_H__23D83FC6_BFBA_4931_9610_F42A239A112D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGE89_Functions  
{
public:
	CGE89_Functions();
	virtual ~CGE89_Functions();


	
	////////////////////////////Band I , II , III , IV , V//////////////////////////////////////
	int GE89_BAND1345(CString cty,double FreqXa) ;
	BOOL GE89_BAND(CString cty,double FreqXa) ;

	////////////////////////////Cord. Distance//////////////////////////////////////
	double GE89_Dcord(CString Zone,double Heff,double ERP_W,double FreqXa) ;


	////////////////////////////Protection Ratio//////////////////////////////////////
	BOOL Protection_Ratio(double FvX , double FvY , double FsX , double FsY ,
							 double offvX , double offvY , double offsY , 
							 double VSRx , double VSRy , int Xn , int Yn ,
							 CString Xsys, CString Ysys , 
							 CString Xcolor , CString freq_stablX ,
							 double *PR_t , double *PR_c  );


	////////////////////////////Fst.Calculation//////////////////////////////////////
	double GE89_E_3(double f,double t,CString z,double h1,double d_km) ;
	double Eu_SimpleMulti(double *Esi,long num,double P_location,double FvX,double *g_dB) ;
	double F_2_1(double Frac, double t) ;
	double Delta_h_cr(double f,double d,double dh, CString cty);
	double F_2B_1_2(double f,double Pl,double dh,CString cty);

	////////////////////////////Fixed srv//////////////////////////////////////
	BOOL Fixed_Band(double f,CString cty);
	double F_1(double Df,double fc,double fs);
	BOOL Fixed_cty(CString cty);

	/////////////////////////////////Mobile srv/////////////////////////////////////
	BOOL Mobile_Band(double f,CString cty);
	double Mobile_Elimit(double Fm);
	double Mobile_Height_gain(double Fm , double h2 , int Zone);

	/////////////////////////////////Interference////////////////////////////////////////
	double RPR_Int(double Df,double fc,double fs);
	double AntAdjustmentFactor(double dAz,double FaY_MHz,CString stn_clsX,CString polX,CString polY) ;
	double Mobile_Fsmin_Int(double Fm,double necBWm);


protected:
	////////////////////////////Cord. Distance//////////////////////////////////////
	double TABLE_I(CString Zone,double Heff,double ERP_W) ;
	double TABLE_II(CString Zone,double Heff,double ERP_W) ;
	double TABLE_III(CString Zone,double Heff,double ERP_W) ;
	double TABLE_IV(CString Zone,double Heff,double ERP_W) ;
	double Interp2(double *D0,double *E0,double d,int num) ;
	double GE89_Dcord0(CString Zone,double Heff,double ERP_W,double FreqXa) ;
	double Interp1(double *D0,double *E0,double d,int num) ;


	////////////////////////////Fst.Calculation//////////////////////////////////////
	void F_2_2(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_3(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_4(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_5(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_6(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_7(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_8(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_9(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_10(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_11(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_12(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_13(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_14(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_15(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_16(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_17(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_18(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_19(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_20(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_21(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_22(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_23(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_24(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;
	void F_2_25(double *E037,double *E075,double *E0150,double *E0300,double *E0600,double *E01200,double *E0fs) ;

	double GE89_E_0(double f,double t,int z,double h1,double d_km,double *Ebfs) ;
	double GE89_E_1(double f,double t,int z,double h1,double d_km,double *Ebfs) ;
	double GE89_E_2(double f,double t,int z,double h1,double d_km,double *Ebfs) ;

	double F_2A_5(double Angle, double f) ;

	double F_2A_2_3(double f,double di,double dh);
	double Delta_h_cr_0(double f,double d,double dh);

	double L_Xi0(double Xi) ;
	double L_Xi (double Xi) ;

	double F_2B_1(double f,double Pl);
	double F_2B_2_0(double f,double Pl,double dh);
	double F_2B_2(double f,double Pl,double dh);


	////////////////////////////Protection Ratio//////////////////////////////////////
	double Table_3_VI0 (double DoffV,double DfV,CString Xsys,CString Xcolor);
	double Table_3_VI  (double DoffV,double DfV,CString Xsys,CString Xcolor);
	double Table_3_VII0(double DoffV,double DfV,CString Xsys,CString Xcolor);
	double Table_3_VII (double DoffV,double DfV,CString Xsys,CString Xcolor);

	double Table_3_C_II0 (double DoffV,double DfV,CString Xsys,CString Xcolor);
	double Table_3_C_II  (double DoffV,double DfV,CString Xsys,CString Xcolor);
	double Table_3_C_III0(double DoffV,double DfV,CString Xsys,CString Xcolor);
	double Table_3_C_III (double DoffV,double DfV,CString Xsys,CString Xcolor);

	void   Table_3_VIII0(double DfV,CString Xsys,double *PRtv,double *PRcv);
	void   Table_3_VIII (double DfV,CString Xsys,double *PRtv,double *PRcv);
	void   Table_3_IX   (double DfV,double *PRtv,double *PRcv);
	int    Table_3_IV   (CString Xsys,CString Ysys,int Xn ,double *PR , int *Yn);
	double Table_3_III  (CString Xsys,CString Ysys);


	void PRv_t_c(double DoffV,double DfV,CString Xsys,CString Ysys,
									   CString Xcolor,CString freq_stablX ,
									   double *PRv_t , double *PRv_c);

	void PRsv_t_c(double DoffSV,double DfSV,double DfV,CString Xsys,CString Ysys,
									   CString Xcolor,CString freq_stablX ,
									   double FvX , double VSRy ,
									   double *PRsv_t , double *PRsv_c);

	void PRs_t_c(double DfS , double VSRx , double VSRy , double *PRs_t , double *PRs_c);
	void PRvs_t_c(double DfVS , double VSRx , double *PRvs_t , double *PRvs_c);

	void PRimage_t_c(double FvX , CString Xsys,CString Ysys,int Xn,int Yn,
											double *PRimage_t , double *PRimage_c);

	////////////////////////////Fixed srv//////////////////////////////////////
//	BOOL Fixed_cty(CString cty);
	BOOL Fixed_ctyI(CString cty);
	BOOL Fixed_ctyIIIn(CString cty);

	/////////////////////////////////Mobile srv////////////////////////////////
	BOOL Mobile_ctyI(CString cty);
	BOOL Mobile_ctyIIIn(CString cty);

	/////////////////////////////////Interference//////////////////////////////
	double F_3_2(double dAz,double Fx_MHz) ;


};

#endif // !defined(AFX_GE89_FUNCTIONS_H__23D83FC6_BFBA_4931_9610_F42A239A112D__INCLUDED_)
