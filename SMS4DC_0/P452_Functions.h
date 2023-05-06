// P452_Functions.h: interface for the CP452_Functions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P452_FUNCTIONS_H__62B3222A_A433_4208_81D7_0B381D74F773__INCLUDED_)
#define AFX_P452_FUNCTIONS_H__62B3222A_A433_4208_81D7_0B381D74F773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CP452_Functions  
{
public:
	CP452_Functions();
	virtual ~CP452_Functions();

private:
	void extract_Dtm_Dlm(double *di,int *zi,int npiont, double *d_tm_p, double *d_lm_p);
	double do_beta_0 (double *di,int *zi,int npoint);
	double do_k (double time_pc, double k50, double beta_0);
	double extract_sea_fraction (int *zi,int points);
	int fresnel_clearance(double *di,double *hi, double r, long p, long q,
			long test_start, long test_stop, double Wave_km,long *start, long *stop ,long *index, double *clearance);
	double pn526_fres_clearance(double *di,double *hi,int npoint,double f_ghz, double r);
	double do_gas_loss (double d, double f, double r);
	double  clear_air_enhance (double d_km, double time_pc);
	void pn452_Lbo (double d_km, double f_ghz,double time_pc, double w, double *val_p);
	double pn526_fres_clear_loss (double clearance);
	double knife_edge_loss (double nu);
	int extract_hozs (double *di,double *hi,int npoint, double r,
				 double *d_lt_p,    double *d_lr_p,
				 double *t_t_mr_p,  double *t_r_mr_p,
				 long   *i_lt_p,    long   *i_lr_p    );
	void get_hoz_point (double *di,double *hi,int npoint, double r, long obs_i,
				int to_rx, double *d_km, double *theta_r, long *i_p);
	long max_elevation(double *di,double *hi,int npoint, double r, long start, long end1);
	int stretch_string(double *di,double *hi,int npoint, double r, long *points, long *index);
	int obstacle_indices(long points, long *index,
									long *obstacles,long *w,long *x,long *y,long *z);

	void obstacle_parms
			(double *di,double *hi,int npoint, double r_eff,long obstacles,  double Wave_km,double Ht,double Hr,
							long *w1,long *x1,long *y1,long *z1,
							double *d_v1,double *h_v1,double *h1,
							double *s11,double *s21,double *nu1,double *r1);
	void sub_path_section(double *hi, long p, long q, long *start, long *stop);
	double subpath_losses
			(double *di,double *hi,int npoint, double r, long obstacles, double Wave_km,
			long *w,long *x,long *y,long *z);
	double cylinder_loss (double s1,double s2,double h,double r,double nu,double Wave_km);
	double spread_losses (long obstacles, double *s1,double *s2);
	double  obstacle_losses(long obstacles,double *s1,double *s2,double *h,double *r,double *nu,double Wave_km);
	int pn526_Led(double *di, double *hi,int npoint,
							 double f_GHz,  double r, double Ht, double Hr,double *val_p);


	void pn452_Lba (double d_km,    double f_ghz,
				  double time_pc, double beta_0,
				  double r50,     double w,
				  double h_t,     double h_r,
				  double h_te,    double h_re,   double h_m,
				  double d_lt,    double d_lr,
				  double t_t,     double t_r,
				  double d_ct,    double d_cr,   double *val_p);

	void pn452_Lbs (double d_km, double f_ghz, double time_pc,
				  double n_0, double theta_mr,
				  double gt, double gr, double *val_p);

	int pn452_Lbd (double *di, double *hi,int npoint,
							  double f_ghz, double r_e, double w,double Ht,double Hr,double *val_p,double *o_loss_d);

	double do_k50 (double delta_N);
	void extract_coasts(double *di,int *zi,int npoint,
								   double *d_ct, double *d_cr);

	void terrain_roughness (double *di,double *hi,int npoint,
									   double Ht,double Hr, long i_lt, long i_lr,
									  double *h_te_p, double *h_re_p, double *h_m_p);


	void ReadData(CString antfile) ;

	double	*m_di;
	double	*m_hikm;
	double	*m_hi;
	int		*m_zi;
	int m_npoint;

public:
	int pn452_Lb (double *di,double *hi,int *zi,int npoint,
					double f_ghz, double time_pc,
					double n_0, double delta_n, double beta_e,
					double gt, double gr,double Ht, double Hr, double *val_p,
					double *o_loss_bd,double *o_loss_bs,double *o_loss_ba,
					double *o_loss_d,int *o_done_d,int *o_done_a,double *o_clear_e,double *o_clear_50,
					int *o_path_type,double *o_k_e);


	double pn452_Lbdiff (double *di,double *hi,int npoint,double f_ghz,double k50,double Ht,double Hr,int *o_path_type);
	double do_k_diff (double time_pc, double k50, double beta_0);

};

#endif // !defined(AFX_P452_FUNCTIONS_H__62B3222A_A433_4208_81D7_0B381D74F773__INCLUDED_)
