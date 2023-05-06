// P452_Functions.cpp: implementation of the CP452_Functions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS4DC.h"
#include "P452_Functions.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP452_Functions::CP452_Functions()
{

}

CP452_Functions::~CP452_Functions()
{

}


double CP452_Functions::pn452_Lbdiff (double *di,double *hi,int npoint,double f_ghz,double k50,double Ht,double Hr,int *o_path_type)
{

	hi[0] = hi[0] + Ht;
	hi[npoint - 1] = hi[npoint - 1] + Hr;

	int PN452_LOS_CLEAR   = 0,
		PN452_LOS_SUB_P   = 1,
		PN452_TRANS_HOZ   = 2;

	double	d_km = di[npoint - 1],
			PN452_REARTH_KM   = 6371.0,
			o_loss_d = 0.0, r50, fres_clear;

	r50 = k50 * PN452_REARTH_KM;                
	fres_clear = pn526_fres_clearance(di,hi,npoint,f_ghz, r50);

	if (fres_clear > 0.6)               /* LOS path with Fresnel clearance */
	{
		*o_path_type = PN452_LOS_CLEAR;
		o_loss_d  = 0;
	}
	else if (fres_clear > 0.0)          /* LOS path with sub-path obstruct */
	{
		*o_path_type = PN452_LOS_SUB_P;
		double clear; 
		clear = pn526_fres_clearance(di,hi,npoint,f_ghz, r50);         
		o_loss_d = pn526_fres_clear_loss (clear);
	}
	else                              /* transhorizon path                 */
	{
		*o_path_type = PN452_TRANS_HOZ;
		pn526_Led (di,hi,npoint,f_ghz, r50,Ht,Hr, &o_loss_d);
	}

	return o_loss_d;
}


int CP452_Functions::pn452_Lb (double *di,double *hi,int *zi,int npoint,
				double f_ghz, double time_pc,
				double n_0, double delta_n, double beta_e,
				double gt, double gr,double Ht, double Hr, double *val_p,
				double *o_loss_bd,double *o_loss_bs,double *o_loss_ba,
				double *o_loss_d,int *o_done_d,int *o_done_a,double *o_clear_e,double *o_clear_50,
				int *o_path_type,double *o_k_e)
{
	double d_km;                   /* path distance in km                    */
	double beta_0;                 /* radio-meteorological parameter         */
	double k50;                    /* median effective earth radius factor   */
	double r50;                    /* median effective earth radius km       */
	double k_e;                    /* effective earth radius factor for time */
	double r_e;                    /* effective earth radius for time percent*/
	double fres_clear;             /* Fresnel clearance of path              */
	double w;                      /* fraction of path over sea              */
	double loss_b;                 /* basic transmission loss                */
	long   points;                 /* number of profile points               */
	int    status;

	*o_clear_e = 0.0;                          /* set to zero report     */
	*o_loss_d  = 0.0;                          /*  values which are      */
	*o_loss_bd = 0.0;                          /*  assigned only under   */
	*o_loss_bs = 0.0;                          /*  particular conditions */
	*o_loss_ba = 0.0;
	*o_done_d  = 0;
	*o_done_a  = 0;

	 points = npoint;
	 d_km = di[points - 1];

	int TDB_PRF_MIN_PTS   =   4,
		PN452_PRF_MIN_PTS = TDB_PRF_MIN_PTS,
		PN452_SUCCESS     = 0,
		PN452_PATH        = -1,
		PN452_PROF        = -2,
		PN452_FREQ        = -3,
		PN452_TIME        = -4,
		PN452_RAD_MET     = -5,
		PN452_ANT_HTS     = -6,
		PN452_ERROR       = -7,
		PN452_LOS_CLEAR   = 0,
		PN452_LOS_SUB_P   = 1,
		PN452_TRANS_HOZ   = 2;

	double	PN452_KM_MIN      =  0.0009,
			PN452_GHZ_MIN     =  0.69,
			PN452_GHZ_MAX     =  40.01,
			PN452_TIME_MIN    =  0.00099,
			PN452_TIME_MAX    = 50.0 ,
			PN452_DIF_KM      = 200.0,
			PN452_REARTH_KM   = 6371.0,
			PN452_ANA_PC      = 50.1,
			PN452_ANA_KM      = 20.0,
			PN452_MIN_SEA     = 0.75; 

	if (points < PN452_PRF_MIN_PTS)                           /* test inputs */
		status = PN452_PROF;
	else if (d_km < PN452_KM_MIN)
		status = PN452_PATH;
	else if (f_ghz < PN452_GHZ_MIN || f_ghz > PN452_GHZ_MAX)
		status = PN452_FREQ;
	else if (time_pc < PN452_TIME_MIN || time_pc > PN452_TIME_MAX)
		status = PN452_TIME;
	else if (n_0 < 0.0 || delta_n < 0.0 || beta_e < 0.0)
		status = PN452_RAD_MET;
	else if (Ht < 0.0 || Hr < 0.0)
		status = PN452_ANT_HTS;
	else
	{
		status = PN452_SUCCESS;                   /* OK: do initial setting-up */
//		tdb_ant_up (p_p);                            /* ensure antennas are up */
		hi[0] = hi[0] + Ht;
		hi[points - 1] = hi[points - 1] + Hr;

		k50 = do_k50(delta_n);                       /* median k-factor and    */
		r50 = k50 * PN452_REARTH_KM;                 /*  earth radius          */
		beta_0 = beta_e * do_beta_0 (di,zi,npoint);           /* beta-null              */
		k_e = do_k_diff (time_pc, k50, beta_0);      /* k-factor and earth     */
		r_e = k_e * PN452_REARTH_KM;                 /*  radius for time %     */
		w = extract_sea_fraction (zi,npoint);              /* set fraction over sea  */
		fres_clear = pn526_fres_clearance            /* get path clearance     */
					(di,hi,npoint,f_ghz, r50);         /*  at median k-factor    */
//		m_k50 = k50;                            /*  load report values    */
		*o_k_e = k_e;
//		m_beta_0   = beta_0;
//		m_omega    = w;
		*o_clear_50 = fres_clear;       /* Proceed according to clearance: */
		if (fres_clear > 0.6)               /* LOS path with Fresnel clearance */
		{
			*o_path_type = PN452_LOS_CLEAR;
			pn452_Lbo (d_km, f_ghz, time_pc, w, &loss_b);  /* LOS basic xmn loss */
			*o_loss_d  = 0;
		}
		else if (fres_clear > 0.0)          /* LOS path with sub-path obstruct */
		{
			*o_path_type = PN452_LOS_SUB_P;
			pn452_Lbo (d_km, f_ghz, time_pc, w, &loss_b);  /* LOS basic xmn loss */

			{
				double clear;                        /* clearance for time %       */
				double loss_sp;                      /* sub-path diffraction loss  */

				clear = pn526_fres_clearance             /* get path clearance     */
					(di,hi,npoint,f_ghz, r_e);          /*  at effective k-factor */
				loss_sp = pn526_fres_clear_loss (clear);
				loss_b += loss_sp;
				*o_clear_e = clear;
				*o_loss_d  = loss_sp;
			}
		}
		else                              /* transhorizon path                 */
		{
			double enhance;                     /* clear-air diffraction enhance */
			double d_ct, d_cr;                     /* distances to coasts, km    */
			double d_lt, d_lr;                     /* distances to horizons, km  */
			double t_t,  t_r;                      /* horizon angles, mradians   */
			double h_t,  h_r;                      /* heights above sea, m       */
			double h_te, h_re;                     /* effective terminal hts, m  */
			double h_m;                            /* terrain roughness, m       */
			double loss_bd;                        /* basic diffraction loss     */
			double loss_bs;                        /* basic tropo-scatter loss   */
			double loss_ba;                        /* basic anomalous loss       */
			double theta;                          /* angular distance, mradians */
			long   i_lt, i_lr;                     /* indices of horizon points  */
			int    done_d, done_a;                 /* flags: diff, anom, done    */
			double loss_d;
			done_d = done_a = 0;                   /* clear model-option flags   */

			status = extract_hozs                       /* get horizon details   */
				  (di,hi,npoint, r50, &d_lt, &d_lr,
				   &t_t, &t_r, &i_lt, &i_lr);
			if (status != PN452_SUCCESS)                  /* if LOS, this is     */
				status = PN452_ERROR;                      /*  inconsistency      */
			if (status == PN452_SUCCESS)
			{
				if (d_km < PN452_DIF_KM)             /* diffraction                */
				{
					status = pn452_Lbd(di, hi,npoint,
										f_ghz, r_e, w,Ht,Hr,&loss_bd,&loss_d);
					enhance = clear_air_enhance (d_lt + d_lr, time_pc);
					loss_bd -= enhance;
					done_d = 1;
					*o_loss_d  = loss_d;
				}
			}
			if (status == PN452_SUCCESS)           /* troposcatter               */
			{
				if (status == PN452_SUCCESS)
				{
					theta = (d_km * 1000.0 / r50 ) + t_t + t_r; /* angular distance    */
					pn452_Lbs (d_km, f_ghz, time_pc,          /* basic xmn loss      */
					n_0, theta, gt, gr, &loss_bs);
				}
			}
			if (status == PN452_SUCCESS)            /* anomalous                 */
			{
				if (   (time_pc < PN452_ANA_PC)            /*  do if within time   */
						&& (d_km > PN452_ANA_KM)   )           /*  and distance limits */
				{
					if (w >= PN452_MIN_SEA)                  /* if sea path          */
						extract_coasts (di,zi,npoint, &d_ct, &d_cr);    /*  get coast distances */
					else                                     /* if not sea path      */
						d_ct = d_cr = 0.0;                     /*  assign to be tidy   */

					terrain_roughness                                /* terrain      */
								(di,hi,npoint,Ht,Hr, i_lt, i_lr, &h_te, &h_re, &h_m);  /*  roughness   */

//					h_t = (m_tx_kmgas + m_tx_kmagl) * 1000;    /* antenna hts  */
//					h_r = (m_rx_kmgas + m_rx_kmagl) * 1000;    /*  m above sea */
					h_t = (hi[0]) * 1000;    /* antenna hts  */
					h_r = (hi[npoint-1]) * 1000;    /*  m above sea */
					pn452_Lba
						(d_km, f_ghz, time_pc, beta_0, r50,   w,     /* basic xmn loss */
					h_t,  h_r,   h_te,    h_re,   h_m,
					d_lt, d_lr,  t_t,     t_r,    d_ct,  d_cr, &loss_ba);
					done_a = 1;
				}
			}
			if (status == PN452_SUCCESS)             /* final result: sum powers */
			{
				double sum;

				sum = pow (10.0, -0.2 * loss_bs);      /* tropo is always done     */

				if (done_d)                            /* if diffraction done,     */
				sum += pow (10.0, -0.2 * loss_bd);   /*  add to power-sum, and   */

				if (done_a)                            /* if anomalous done,       */
				sum += pow (10.0, -0.2 * loss_ba);   /*  add to power sum, and   */

				loss_b = -5.0 * log10 (sum);           /* basic transmission loss  */

				*o_loss_bd = loss_bd;              /* write individual losses, */
				*o_loss_bs = loss_bs;              /*  including null values,  */
				*o_loss_ba = loss_ba;              /*  to Report data          */
				*o_done_d  = done_d;
				*o_done_a  = done_a;
			}
			*o_path_type = PN452_TRANS_HOZ;      /* flag transhorizon path   */
		}
	}
	if (status == PN452_SUCCESS)      /* NOTE: clutter model not implemented */
		*val_p = loss_b;

//	*o_loss_b   = loss_b;         /* set report basic transmission loss  */

	return status;

}

void CP452_Functions::terrain_roughness (double *di,double *hi,int npoint,
								   double Ht,double Hr, long i_lt, long i_lr,
								  double *h_te_p, double *h_re_p, double *h_m_p)
{
	double       d_km;          /* path distance in km                       */
	double       d_by_2;        /* half the path distance in km              */
	double       h;             /* height of profile points in km            */
	double       d_d;           /* distance of point beyond profile centre   */
	double       h_a;           /* accumulator for average height km         */
	double       h_av;          /* average height km                         */
	double       d_a, n_a;      /* accumulators for denominator, numerator   */
	double       slope;         /* slope as true ratio, NOT m/km             */
	double       rise_by_2;     /* half total height change of smooth surf   */
	double       hss, hass;     /* height of smooth surface, height above it */
	double       h_st, h_sr;    /* ht of smooth-earth surface at tx, rx, km  */
	double       h_m_max;       /* store for max of h_m, in km               */
	long         points;
	long         pts_to_do;     /* points - 2; terminals not included        */
	long         i;

	points = npoint;                        /* number of profile points */

//	double tx_kmgas = m_tx_kmgas;
//	double rx_kmgas = m_rx_kmgas;

	double tx_kmgas = hi[0] - Ht;
	double rx_kmgas = hi[points - 1] - Hr;



	double tx_kmagl = Ht;
	double rx_kmagl = Hr;

	d_km = di[points - 1];       /* path length, km       */
	d_by_2 = d_km / 2.0;                              /* half path length      */
	pts_to_do = points - 2 -1;                         /* loop end-test         */
	h_a = d_a = n_a = 0.0;                          /* clear accumulators    */

	for (i = 0; i < pts_to_do; i++)
	{
		h = hi[i+1];                              /* do least-squares fit  */
		d_d = di[i+1] - d_by_2;
		h_a += h;
		n_a += h * d_d;
		d_a += d_d * d_d;
	}
	slope = n_a / d_a;                 /* slope of initial least-squares fit */
	h_av = h_a / pts_to_do;            /* average height                     */
	rise_by_2 = slope * d_by_2;        /* half the rise along smooth surface */
	h_st = h_av - rise_by_2;           /* height of smooth surface at tx     */
	h_sr = h_av + rise_by_2;           /* height of smooth surface at rx     */
	if (h_st > tx_kmgas)          /* if smooth surface heights are      */
		h_st = tx_kmgas;            /*  above actual ground heights       */
	if (h_sr > rx_kmgas)          /*   then correct them down to the    */
		h_sr = rx_kmgas;            /*       actual ground heights        */
	slope = (h_sr - h_st) / d_km;      /* re-compute slope just in case      */

	h_m_max = -1000.0;                 /* to avoid warning only, not used    */

	for (i = i_lt;i <= i_lr; i++)                              
	{
		hss = h_st + (slope * di[i]);     /* height of smooth surface  */
		hass = hi[i] - hss;                 /* terrain height above ss   */
		if (i == i_lt || hass > h_m_max)          /* for 1st or maximum point  */
			h_m_max = hass;                         /*  set roughness parameter  */
	}
	*h_te_p = (tx_kmagl + tx_kmgas - h_st) * 1000.0;      /* assign  */
	*h_re_p = (rx_kmagl + rx_kmgas - h_sr) * 1000.0;      /*  output */
	*h_m_p  = h_m_max * 1000.0;                                     /*  values */
}


void CP452_Functions::extract_coasts(double *di,int *zi,int npoint,
							   double *d_ct, double *d_cr)
{
	int  TDB_ZONE_SEA = 1;

	double       d_km;                    /* path distance km                */
	double       d_t, d_r;                /* profile distances of tx, rx     */
	long         points;                  /* number of points in profile     */
	long         tx_i, rx_i;              /* indices of tx, rx               */
	long         i;

	points = npoint;
	d_km = di[points - 1];
	tx_i = 0;
	rx_i = points - 1;
	d_t = di[tx_i];
	d_r = di[rx_i];

	*d_ct = *d_cr = d_km;                 /* initial values: may be no sea   */
	for ( i = tx_i;i <= rx_i; i++)
	{
		if (zi[i] == TDB_ZONE_SEA)
		{ 
			*d_ct = di[i] - d_t;
			break;
		}
	}
	for (i = rx_i; i >= tx_i; i--)
	{
		if (zi[i] == TDB_ZONE_SEA)
		{ 
			*d_cr = d_r - di[i];
			break;
		}
	}

}

double CP452_Functions::do_k50 (double delta_N)
{
	return (157.0 / (157.0 - (delta_N)));
}

int CP452_Functions::pn452_Lbd (double *di, double *hi,int npoint,
						  double f_ghz, double r_e, double w,double Ht,double Hr,double *val_p,double *o_loss_d)
{
	double d_km;                          /* path distance km                 */
	double rho;                           /* wavet vapour density gm/cu m     */
	double loss_g;                        /* gas absorption loss dB           */
	double loss_d;                        /* diffraction loss dB              */
	double loss_b;                        /* basic transmission loss          */
	long points;                          /* number of points in profile      */
	int status;
	int  PN452_ERROR = -7,
		PN452_SUCCESS = 0;

	points = npoint;
	d_km = di[points - 1];

	rho = (7.5+(2.5*(w)));                        /* water vapour density       */
	loss_g = do_gas_loss (d_km, f_ghz, rho);    /* gas loss                   */

	if (pn526_Led (di,hi,npoint,f_ghz, r_e,Ht,Hr, &loss_d))      /* excess diffraction loss */
		status = PN452_ERROR;
	else
	{
		loss_b = 92.45 + (20.0 * log10 (f_ghz * d_km))   /* basic xmn loss      */
				+ loss_d + loss_g;
		*val_p = loss_b;                          /* diffraction basic loss     */
		status = PN452_SUCCESS;
	}

	*o_loss_d = loss_d;                     /* diff loss for diag report  */
	return status;
}

void CP452_Functions::pn452_Lbs (double d_km, double f_ghz, double time_pc,
		      double n_0, double theta_mr,
		      double gt, double gr, double *val_p)
{
	double loss_f;                          /* frequency dependent loss      */
	double loss_c;                          /* aperture-medium coupling loss */
	double loss_g;                          /* gas aborptions loss           */
	double logfby2;                         /* log of half the frequency     */
	double enhance;                         /* clear-air enhancement         */
	double lbs;                             /* tropo basic transmission loss */
	int PN452_TROPO_RHO = 3;
	logfby2 = log10 (f_ghz * 0.5);
	loss_f = (25.0 * log10 (f_ghz)) - (2.5 * logfby2 * logfby2);
	loss_c = 0.051 * exp (0.055 * (gt + gr));
	loss_g = do_gas_loss (d_km, f_ghz, PN452_TROPO_RHO);
	enhance = 10.1 * pow (-log10 (time_pc / 50), 0.7);
	lbs = 190.1 + loss_f + (20.0 * log10 (d_km))
		  + (0.573 * theta_mr) - (0.15 * n_0) + loss_c + loss_g - enhance;
	*val_p = lbs;
}

void CP452_Functions::pn452_Lba (double d_km,    double f_ghz,
		      double time_pc, double beta_0,
		      double r50,     double w,
		      double h_t,     double h_r,
		      double h_te,    double h_re,   double h_m,
		      double d_lt,    double d_lr,
		      double t_t,     double t_r,
		      double d_ct,    double d_cr,   double *val_p)
{
	double f_3rd;                       /* cube root of freq in GHz           */
	double d10_lt, d10_lr;              /* hoz distances in 10 kms            */
	double tp;                          /* modified ang distance theta-prime  */
	double tp_t, tp_r;                  /* terminal theta-primes, mradians    */
	double tpp_t, tpp_r;                /* terminal theta-double-primes, mrad */
	double a_st, a_sr;                  /* site-shielding losses Act,cr       */
	double a_ct, a_cr;                  /* over-sea duct coupling Ast,sr      */
	double a_c;                         /* total couopling loss (not clutter) */
	double a_p;                         /* time percentage variability A(p)   */
	double g_d;                         /* specifi angular attenuation        */
	double a_dp;                        /* time and distance variability Ad(p)*/
	double rho;                         /* water-vapour density gm/cu m       */
	double a_g;                         /* gas absorption loss dB             */
	double PN452_MIN_SEA = 0.75; 
	double PN452_SEA_HOZ_KM = 5.0;


	f_3rd = pow (f_ghz, 1.0 / 3.0);                 /* frequency cube root      */
	d10_lt = 0.1 * d_lt;                          /* modified hoz distances   */
	d10_lr = 0.1 * d_lr;
	tp_t = (t_t > d10_lt)? d10_lt: t_t;           /* terminal theta-primes    */
	tp_r = (t_r > d10_lr)? d10_lr: t_r;
	tp = (1000.0 * d_km / r50) + tp_t + tp_r;     /* path theta-prime         */
	tpp_t = t_t - d10_lt;                         /* term theta-double-primes */
	tpp_r = t_r - d10_lr;

				/* Terminal site-shielding diffraction losses  */
	a_st = (tpp_t > 0.0)?
				(20.0 * log10 (1.0 + 0.361 * tpp_t * sqrt ( f_ghz * d_lt)))
				+ 0.264 * tpp_t * f_3rd :  0.0;
	a_sr = (tpp_r > 0.0)?
				(20.0 * log10 (1.0 + 0.361 * tpp_r * sqrt ( f_ghz * d_lr)))
				+ 0.264 * tpp_r * f_3rd :  0.0;

	a_ct = a_cr = 0.0;         /* Over-sea surface duct coupling corrections  */

	if (w > PN452_MIN_SEA)                           /* if mainly sea path: */
	{
		if (d_ct < d_lt && d_ct < PN452_SEA_HOZ_KM)
			a_ct = (-3.0 * exp (-0.25 * d_ct * d_ct)) * (1.0 + tanh (0.07 * (50.0 - h_t)));
		if (d_cr < d_lr && d_cr < PN452_SEA_HOZ_KM)
			a_cr = (-3.0 * exp (-0.25 * d_cr * d_cr)) * (1.0 + tanh (0.07 * (50.0 - h_r)));
	}

	a_c = 102.45 + (20.0 * log10 (f_ghz))    /* total coupling losses       */
		+ (20.0 * log10 (d_lt + d_lr))      /*  (except local clutter)     */
		+ a_st + a_sr + a_ct + a_cr;

	{                         /* block with local variables to compute A(p):  */
		double a0_p;                      /* A(p) term Ao(p)                    */
		double g;                         /* upper-case greek Gamma             */
		double b;                         /* reference time percentage beta     */
		double mu_2, mu_3;                /* factors in beta, mu2, mu3          */
		double pow_arg;                   /* argument to function pow()         */
		double sum_root_h;                /* part of denominator for mu2        */
		double fact_1, fact_2;            /* factors in power used for mu2      */
		double s;                         /* exponent used for 'alpha'          */
		double a;                         /* power 'alpha' used for mu2         */
		double d_i;                       /* used for terrain roughness         */

		d_i = d_km - d_lt - d_lr;
		if (d_i > 40.0)
			d_i = 40.0;
		mu_3 = (h_m > 10.0) ?  exp (-0.000046 * (h_m - 10.0) * (43.0 + d_i * 6.0)) : 1.0;
		s = 0.0067 * pow (d_km * (1.0 - w), 1.6);
		a = -0.6 - (d_km * 0.001 * (1.0 - exp (-s)));
		sum_root_h = sqrt (h_te) + sqrt (h_re);
		fact_1 = 500.0 / r50;
		fact_2 = (d_km * d_km) / (sum_root_h * sum_root_h);
		mu_2 = pow (fact_1 * fact_2, a);
		if (mu_2 > 1.0)
			mu_2 = 1.0;
		b = beta_0 * mu_2 * mu_3;
		pow_arg = log10 (b) + 4.0;                       /* trap possible -ve    */
		if (pow_arg < 0.0)                             /*  to function pow()   */
			pow_arg = 0.0;
		g = 0.17 * exp ((b * 0.027) + (0.15 * pow (pow_arg, 1.4)));
		a0_p = -12.0 + (1.2 + (0.004 * d_km)) * log10 (time_pc / b);

		a_p = a0_p + 12.0 * pow (time_pc / b, g);    /* time variability A(p)  */
	}

	g_d = 0.00005 * r50 * f_3rd;        /* specific angular attenuation      */
	a_dp = (g_d * tp) + a_p;            /* time and angle dependent loss     */

	rho = (7.5+(2.5*(w))) ;                      /* water vapour density        */
	a_g = do_gas_loss (d_km, f_ghz, rho);     /* gas loss                    */

	*val_p = a_c + a_dp + a_g;                /* assign result               */
}




int CP452_Functions::pn526_Led(double *di, double *hi,int npoint,
						 double f_GHz,  double r, double Ht, double Hr,double *val_p)
{
//	tdb_ant_up (p_p);                                 /* raise antennas       */
//	hi[0] = hi[0] + Ht;
//	hi[npoint-1] = hi[npoint-1] + Hr;

	double Wave_km = 0.0003 / f_GHz;                             /* assign wavelength km */

	long points;
	long *index;	index = new long[npoint]; 
	int k1 = stretch_string(di,hi, npoint,  r, &points, index);
	if (k1)
	{
		delete [] index;
		return -1;                                      /* error if too many    */
	}

	long obstacles;
	long *w;	w = new long[npoint]; 
	long *x;	x = new long[npoint]; 
	long *y;	y = new long[npoint]; 
	long *z;	z = new long[npoint]; 

	int k2 = obstacle_indices(points, index, &obstacles, w, x, y, z);
	if(k2)
	{
		delete [] w;
		delete [] x;
		delete [] y;
		delete [] z;

		return -1;                                      /* error if too many    */
	}

	double  obs_loss = 0.0;
	if (obstacles!=0)
	{
		double *d_v;	d_v = new double[obstacles];
		double *h_v;	h_v = new double[obstacles];
		double *h;		h = new double[obstacles];
		double *s1;		s1 = new double[obstacles];
		double *s2;		s2 = new double[obstacles];
		double *nu;		nu = new double[obstacles];
		double *r1;		r1 = new double[obstacles];

		obstacle_parms(di,hi,npoint, r, obstacles,  Wave_km, Ht, Hr,
								w,x,y,z,  d_v,h_v,h, s1,s2,nu,r1);
		obs_loss = obstacle_losses(obstacles,s1,s2,h,r1,nu, Wave_km);

		delete [] d_v;
		delete [] h_v;
		delete [] h;
		delete [] s1;
		delete [] s2;
		delete [] nu;
		delete [] r1;
	}
	else
		obs_loss = 0;  
 
	double subpath_loss = subpath_losses(di,hi, npoint,r, obstacles, Wave_km, w,x,y,z);
	double obstacles_loss = obs_loss + subpath_loss;
	*val_p = obstacles_loss;

	delete [] index;
	delete [] w;
	delete [] x;
	delete [] y;
	delete [] z;

	return 0;
}


double  CP452_Functions::obstacle_losses(long obstacles,double *s1,double *s2,double *h,double *r,double *nu,double Wave_km)
{
	long i;
	double spread_loss;

	double loss,obs_loss = 0.0;

	for (i = 0; i < obstacles; i++)
	{
		loss = cylinder_loss (s1[i],s2[i],h[i], r[i], nu[i], Wave_km);
		obs_loss += loss;
	}
	spread_loss = spread_losses (obstacles, s1,s2);
	obs_loss += spread_loss;

	return obs_loss;
}


double CP452_Functions::spread_losses (long obstacles, double *s1,double *s2)
{
	long n;                                   /* number of obstacles         */
	double a, b, c;                           /* terms in expression         */
	long i;
	double loss;

	n = obstacles;
	if (n)                                      /* if 1 or more obstacles    */
	{
		a = s1[0];
		b = s1[0];
		c = s1[0] * s2[n-1];
		for (i = 0; i < n; i++)
		{
			a *= s2[i];
			b += s2[i];
			c *= (s1[i] + s2[i]);
		}
		loss = - 10.0 * log10 (a * b / c);
	}
	else                                         /* if no obstacles          */
		loss = 0.0;                                /*  spreading loss is zero  */

	return loss;                                 /* return result            */
}

double CP452_Functions::cylinder_loss (double s1,double s2,double h,double r,double nu,double Wave_km)
{
	double d;                  /* horizon and total obstacle dists  */
	double root_3;                     /* cube root term                    */
	double m, n;                       /* variables of function T           */
	double loss_k;                     /* knife-edge diffraction loss in dB */
	double loss_t;                     /* function T diffraction loss in dB */
	double loss;                       /* total diffraction loss in dB      */
	double pi = 4.0*atan(1.0);

	d = s1 + s2;
	loss_k = knife_edge_loss (nu);

	root_3 = pow (pi * r / Wave_km, 1.0 / 3.0);

	m = (r * d) / (s1 * s2 * root_3);
	n = (h * root_3 * root_3) / r;

	double k, p;                     /* constant and power for T(m,n)     */
	k = 8.2 + 12.0 * n;
	p = 0.73 + 0.27 * (1.0 - exp (-1.43 * n));
	loss_t = k * pow (m, p);

	loss = loss_k + loss_t;            /* knife-edge plus cylinder extra    */
	return loss;
}


double CP452_Functions::subpath_losses
	    (double *di,double *hi,int npoint, double r, long obstacles, double Wave_km,
		long *w,long *x,long *y,long *z)
{
	long start;
	int i;

	double loss,subpath_loss = 0.0;

	long  stop1, stop2 ,index;
	double clearance;


	if (obstacles == 0)                        /* if LOS path:         */
	{ 
		fresnel_clearance(di,hi, r, 0, npoint - 1, 1, npoint - 2,Wave_km,
							&start,&stop1,&index,&clearance);
		loss = pn526_fres_clear_loss (clearance);
		subpath_loss =subpath_loss + loss;
	}
	else                                            /* if non-LOS path:     */
	{ 
		sub_path_section(hi, w[0], x[0], &start, &stop1);
		fresnel_clearance(di,hi, r, w[0], x[0], start, stop1,Wave_km,
							&start,&stop2,&index,&clearance);
		loss = pn526_fres_clear_loss (clearance);
		subpath_loss =subpath_loss + loss;

		for (i = 0; i < obstacles; i++)                /* then 2nd half  */
		{
			sub_path_section(hi, y[i],z[i], &start,&stop1);
			fresnel_clearance(di,hi, r, y[i], z[i], start, stop1,Wave_km,
							&start,&stop2,&index,&clearance);
			loss = pn526_fres_clear_loss (clearance);
			subpath_loss =subpath_loss + loss;
		}
	}

	return subpath_loss;
}

void CP452_Functions::sub_path_section(double *hi, long p, long q, long *start, long *stop)
{
	double ht, old_ht;
	long start_i, stop_i;
	long i;

	start_i = p;
	for (i = p + 1; i < q; i++)
	{
		ht = hi[i];
		if (start_i == p)
			old_ht = ht;
		else if (ht > old_ht)
			break;
		else
			old_ht = ht;
		start_i++;
	}
	stop_i = q;
	for (i = q - 1; i > p; i--)
	{
		if (stop_i == start_i)
			break;
		ht = hi[i];
		if (stop_i == q)
			old_ht = ht;
		else if (ht > old_ht)
			break;
		else
			old_ht = ht;
		stop_i--;
	}
	*start = start_i;
	*stop = stop_i;
}


void CP452_Functions::obstacle_parms
	    (double *di,double *hi,int npoint, double r_eff,long obstacles, double Wave_km,double Ht,double Hr,
						long *w1,long *x1,long *y1,long *z1,
						double *d_v1,double *h_v1,double *h1,
						double *s11,double *s21,double *nu1,double *r1)
{
	long n;                               /* loop counter for obstacles      */
	int single_point_obstacle;            /* single point obstacle flag      */
	long w, x, y, z;                      /* obstacle profile indices        */
	double d_w, d_x, d_y, d_z;            /* profile distance of obst points */
	double h_w, h_x, h_y, h_z;            /* profile heights of obst points  */
	double d_v, h_v;                      /* profile dist, ht of obst vertex */
	double d_wx, d_xy, d_yz, d_wz;        /* inter-point distance            */
	double a_w, a_z;                      /* obstacle elevations at w, z     */
	double a_e;                           /* great circle path angle radians */
	double d;                             /* distance for cylinder radius    */
	double t;                             /* diffraction angle "theta"       */
	double h;                             /* vertex ht above baseline        */
	double d_wv, d_vz;                    /* horizontal vertex distances     */
	double nu;                            /* equivalent knife-edge 'nu'      */
	double r_cyl;                         /* cylinder radius km              */
	double r_eff_2;                       /* 2 * effective earth radius km   */

	r_eff_2 = r_eff * 2.0;

	for (n = 0; n < obstacles; n++)       /* loop for each obstacle in turn  */
	{
		w = w1[n], x = x1[n];               /* de-reference data needed for    */
		y = y1[n], z = z1[n];               /*  following calculations         */
		d_w = di[w];
		h_w = hi[w];
		d_x = di[x];
		h_x = hi[x];
		d_y = di[y];
		h_y = hi[y];
		d_z = di[z];
		h_z = hi[z];
		d_wx = d_x - d_w;
		d_xy = d_y - d_x;
		d_yz = d_z - d_y;
		d_wz = d_z - d_w;
		single_point_obstacle = (x == y);

		a_w = (h_x - h_w) / d_wx - d_wx / r_eff_2;      /* obs elevation at w  */
		a_z = (h_y - h_z) / d_yz - d_yz / r_eff_2;      /* obs elevation at z  */
		a_e = d_wz / r_eff;                             /* Gt circle obs angle */
		t = a_w + a_z + a_e;                            /* diffraction angle   */

		if (single_point_obstacle)                  /* distance from point w   */
			d_wv = d_wx;                                /* to vertex point       */
		else
		{
			d_xy = d_y - d_x;
			if (t < d_xy / r_eff)                     /* for v small diff angle  */
				d_wv = d_wx + d_xy * 0.5;                 /* assume mid-obstacle   */
			else
			d_wv = ((a_z + a_e / 2.0) * d_wz + h_z - h_w) / t;
		}
		d_vz = d_wz - d_wv;                 /* distance from vertex to point z */
		d_v = d_w + d_wv;                           /* vertex profile distance */

		if (single_point_obstacle)                  /* height of vertex above  */
			h_v = h_x;                                  /* sea level, km         */
		else
			h_v = (d_wv * a_w) + h_w + (d_wv * d_wv / r_eff_2);

					   /* ht of vertex above baseline */
		h = h_v + (d_wv * d_vz / r_eff_2) - ((h_w * d_vz + h_z * d_wv) / d_wz);

					  /* equivalent knife-edge 'nu'   */
		nu = h * sqrt ((2.0 * (d_wv + d_vz)) / (Wave_km * d_wv * d_vz));

	   /* CYLINDER RADIUS */
		long p, q;                                  /* point indices         */
		double d_px, d_yq;
		double h_p, h_q;

		//     tdb_ant_down (p_p);
		hi[0] = hi[0] - Ht;
		hi[npoint-1] = hi[npoint-1] - Hr;

		p = x - 1;                                  /* (remember x = y for   */
		q = y + 1;                                  /*  single-pt obstacle)  */
		d_px = d_x - di[p];
		d_yq = di[q] - d_y;
		d = di[q] - di[p];
		h_p = hi[p];
		h_q = hi[q];
		t = ((h_x - h_p) / d_px) + ((h_y - h_q) / d_yq) + (d / r_eff);
		r_cyl = d / t;

		//     tdb_ant_up (p_p);
		hi[0] = hi[0] + Ht;
		hi[npoint-1] = hi[npoint-1] + Hr;

		d_v1[n] = d_v;                                /* vertex profile dist   */
		h_v1[n] = h_v;                                /* vertex profile height */
		h1[n] = h;                                    /* diffraction height    */
		s11[n] = d_wv;                                /* obstacle horizon      */
		s21[n] = d_vz;                                /*   distances           */
		nu1[n] = nu;                                  /* equiv knife-edge 'nu' */

		r1[n] = r_cyl                              /* smoothed cylinder radius */
		  * pow ((1.0 - exp (-3.7 * nu)), 3);
	}

}


int CP452_Functions::obstacle_indices(long points, long *index,
								long *obstacles,long *w,long *x,long *y,long *z)
{
	long PN526_MAX_OBS = 100;

	long s, t;                             /* string indices                 */
	long last_string;                      /* index of last string point     */
	int same_obs;                          /* flag: treat as same obsacle    */

	s = 0;
	t = 1;
	last_string = points - 1;         /* index of last string point     */

	*obstacles = 0;                    /* no obstacles found yet         */

	long ob = 0;

	 while (t < last_string)                /* loop for all obstacles         */
	 { w[ob] = index[s];                  /* store path start prof index */
	   x[ob] = index[t];                  /* store obst start prof index */
	   do                                      /* loop to find next pair not  */
	   { s++; t++;                             /*  adjacent or end of path    */
		 same_obs = (   (index[t] == index[s] + 1)
			 && (t < last_string) );
		 if (!same_obs)
		 { y[ob] = index[s];                 /* store obst end prof index*/
		   z[ob] = index[t];                 /* store path end prof index*/
		   ob++;                                  /* point to next obstacle   */
		   ++(*obstacles);                    /* increment obstacles count*/
		   if (*obstacles > PN526_MAX_OBS)
		 return -1;
		 }
	   } while (same_obs);
	 }
	return 0;
}

int CP452_Functions::stretch_string(double *di,double *hi,int npoint, double r,
							  long *points, long *index)
{
	long str_i;                           /* string points index             */
	long prf_i;                           /* profile points index            */
	long start;                           /* index of each starting point    */
					   /*  when seeking next string point */
	long end1;                             /* index of last profile point     */

	long tx_i = 0;
	long rx_i = npoint-1;

	long PN526_MAX_STR_PTS = 1000;

	start = tx_i;                    /* profile indices at start and    */
	end1  = rx_i;                    /*  end of path                    */

	index[0] = 0;                    /* first string pt is prf start    */
	*points = 1;                      /* one string point loaded so far  */
	str_i = 1;
	do
	{ if (str_i == PN526_MAX_STR_PTS)     /* if room for no more string pts  */
		return -1;                                 /*  then bad return       */
		prf_i = max_elevation (di,hi,npoint, r, start, end1);  /* find highest elevation */
		index[str_i] = prf_i;                   /* save in string         */
		*points = ++str_i;                       /* count string points    */
		start = prf_i;                               /* set next start         */
	} while (start < end1);                         /* loop to profile end    */

	return 0;                                            /* else good return */
}



long CP452_Functions::max_elevation(double *di,double *hi,int npoint, double r, long start, long end1)
{
	double r2;                                  /* twice effective radius    */
	double d1;                                  /* profile distance at start */
	double h1;                                  /* profile height at start   */
	double d;                                   /* distance to each point    */
	double e;                                   /* elevation of each point   */
	double max_e;                               /* max elevation radians     */
	long i;                                     /* index into profile        */
	long max_i;                                 /* index of max elev point   */

	d1 = di[start];          /* starting distance         */
	h1 = hi[start];            /* starting height           */
	r2 = r * 2.0;

	max_e = -1000.0;                      /* to avoid warning only, not used */

	for (i = ++start; i <= end1; i++)            /* loop from point after     */
	{                                           /*  start to end of profile  */
		d = di[i] - d1;          /* distance from start km  */
		e = ((hi[i] - h1) / d)     /* point elevation radians */
		  - (d / r2);
		if (   (i == start)                       /* on 1st loop or if         */
			   || (e > max_e))                       /*  greater elevation        */
		{	 max_e = e;                              /*   save max elevation      */
			 max_i = i;                              /*   and point index         */
		}
	}
	return max_i;            /* return index of point with highest elevation */
}



void CP452_Functions::get_hoz_point (double *di,double *hi,int npoint, double r, long obs_i,
			int to_rx, double *d_km, double *theta_r, long *i_p)
{
	double rby2;                             /* twice effective earth radius */
	double start_h;                          /* start height above sea, km   */
	double start_d;                          /* start profile distance, km   */
	double dist;                             /* +ve distance, start to point */
	double theta;                            /* elevation angle radians      */
	double max_theta;                        /* maximum elevation found rad  */
	long tx_i, rx_i;                         /* indices of rx and tx points  */
	long start_i;                            /* first point to test          */
	long stop_i;                             /* index of stop point: not done*/
	long max_i;                              /* index of max elevation point */
	long step;                               /* profile index step  +/-1     */
	long i;                                  /* profile variable index       */

	tx_i = 0;                                /* index of transmitter point   */
	rx_i = npoint - 1;		                  /* index of receiver point      */
	rby2 = r * 2;                            /* twice effective earth radius */

	step = (to_rx)? 1: -1;                   /* set step direction           */
	start_i = obs_i + step;
	stop_i = (to_rx)? rx_i + 1: tx_i - 1;    /* end test point: not done     */

	start_h = hi[obs_i];                   /* set start height..           */
	start_d = di[obs_i];                 /*  and distance                */

	max_theta = -1000.0;                  /* to avoid warning only, not used */

	for (i = start_i;   i != stop_i;   i += step)
	{
		dist = fabs (di[i] - start_d);
		theta = ((hi[i] - start_h) / dist) - (dist / rby2);
		if (   (i == start_i)                                    /* if 1st or  */
			   || (theta > max_theta) )                             /*  max point */
		{ max_theta = theta;                                     /*  set max   */
			 max_i = i;                                             /*  & index   */
		}
	}

	*d_km = fabs (di[max_i] - start_d);
	*theta_r = max_theta;
	*i_p = max_i;
}

int CP452_Functions::extract_hozs (double *di,double *hi,int npoint, double r,
			 double *d_lt_p,    double *d_lr_p,
			 double *t_t_mr_p,  double *t_r_mr_p,
			 long   *i_lt_p,    long   *i_lr_p    )
{
	double d_lt, d_lr;                    /* tx, rx horizon distances km     */
	double t_t_r, t_r_r;                  /* tx, rx horizon angles, radians  */
	long tx_i, rx_i;                      /* indices of tx, rx points        */
	long i_lt, i_lr;                      /* indices of tx, rx hoz points    */
	int status;

	int PN452_SUCCESS = 0,
		PN452_LOS = -8,
		PN452_TO_RX = 1,
		PN452_TO_TX = 0;

	tx_i = 0;                                   /* tx profile index  */
	rx_i = npoint-1;                            /* rx profile index  */

	get_hoz_point (di,hi,npoint, r, tx_i, PN452_TO_RX, &d_lt, &t_t_r, &i_lt);
	get_hoz_point (di,hi,npoint, r, rx_i, PN452_TO_TX, &d_lr, &t_r_r, &i_lr);

	*d_lt_p   = d_lt;                                /* assign return values */
	*d_lr_p   = d_lr;
	*t_t_mr_p = t_t_r * 1000.0;                        /*  converting radians  */
	*t_r_mr_p = t_r_r * 1000.0;                        /*   to millradians     */
	*i_lt_p   = i_lt;
	*i_lr_p   = i_lr;

	status = (i_lr < rx_i)? PN452_SUCCESS: PN452_LOS;       /* assign status */

	return status;
}


double CP452_Functions::knife_edge_loss (double nu)
{
	double nu_minus;

	nu_minus = nu - 0.1;
	return 6.9 + 20.0 * log10 (sqrt ((nu_minus * nu_minus) + 1) + nu_minus);
}

double CP452_Functions::pn526_fres_clear_loss (double clearance)
{
	double nu;          /* knife-edge diffraction geometrical parameter 'nu' */
	double loss;        /* excess diffraction loss (only +ve values)         */

	nu = -clearance * sqrt(2.0);

	if (nu > -0.7)
		loss = knife_edge_loss (nu);
	else
		loss = 0.0;

	return loss;
}

void CP452_Functions::pn452_Lbo (double d_km, double f_ghz,
		      double time_pc, double w, double *val_p)
{
	double rho;                                   /* water-vapour density     */
	double loss_g;                                /* gas absorption loss db   */
	double enhance;                               /* clear-air enhancement db */

	rho = (7.5+(2.5*(w)));                              /* water-vapour density */
	loss_g = do_gas_loss (d_km, f_ghz, rho);          /* gaseous absorption   */
	enhance = clear_air_enhance (d_km, time_pc);      /* clear-air enhancement*/

	*val_p = 92.45 + 20.0 * log10 (f_ghz * d_km)      /* basic transmission   */
			 + loss_g - enhance;                     /*    loss              */
}


double  CP452_Functions::clear_air_enhance (double d_km, double time_pc)
{
	return -2.6 * (1.0 - exp (-d_km / 10.0)) * log10 (time_pc / 50.0);
}

double CP452_Functions::do_gas_loss (double d, double f, double r)
{
	double gamma_o;          /* specific oxygen absorption rate dB/km        */
	double gamma_w;          /* specific water-vapour absorption rate dB/km  */
	double loss;             /* resultant gaseous absorption loss            */
	double f2;               /* square of input frequency                    */
	double t22, t57;         /* terms for specific frequencies               */

	f2 = f * f;
	t22 = (f - 22.2);        /* 22 GHz water vapour peak frequency term      */
	t57 = (f - 57.0);        /* 57 GHz oxygen peak frequency term            */

	gamma_o =
		(0.00719 + (6.09 / (f2 + 0.227)) + (4.81 / (t57 * t57))) * f2 * 0.001;
	gamma_w =
		(0.050 + (0.0021 * r) + (3.6 / ((t22 * t22) + 8.5))) * f2 * r * 0.0001;

	loss = (gamma_o + gamma_w) * d;
	return loss;
}

double CP452_Functions::pn526_fres_clearance(double *di,double *hi,int npoint,double f_ghz, double r)
{
	long tx_i, rx_i;
	double Wave_km = 0.0003 / f_ghz;                /* set global wavelength in km */
	tx_i = 0;                        /* profile indices of tx       */
	rx_i = npoint-1;                        /*     and rx                  */

	long start,  stop , index;
	double clearance;

	fresnel_clearance (di,hi, r, tx_i, rx_i, tx_i + 1, rx_i - 1,Wave_km,
											&start,  &stop , &index, &clearance);
	return clearance;
}

int CP452_Functions::fresnel_clearance(double *di,double *hi, double r, long p, long q,
	    long test_start, long test_stop, double Wave_km,
		long *start, long *stop ,long *index, double *clearance)
{
	 long i;                                  /* general profile index        */
	 double r_eff_2;                          /* twice effective earth radius */
	 double d_p, d_q;                         /* profile distances of p, q    */
	 double d_pi, d_iq, d_pq;                 /* inter-point distances        */
	 double h_p, h_q;                         /* point hts above sea          */
	 double h_t;                              /* cartesian ht of terrain at i */
	 double h_r;                              /* cartesian ht of ray at i     */
	 double r_f;                              /* Fresnel zone radius at i     */
	 double wave_by_dist;                     /* wavelength over distance term*/
	 double clearance1, min_clear;             /* clearance and lowest value   */
	 long index1;                              /* index of lowest-clearance pt */

	 *start = p;
	 *stop  = q;

	 if (test_start < test_stop - 1)          /* if at least one point between*/
	 {
		r_eff_2 = r * 2.0;                     /* test for minimum clearance   */
		d_p = di[p];
		d_q = di[q];
		h_p = hi[p];
		h_q = hi[q];
		d_pq = d_q - d_p;
		wave_by_dist = Wave_km / d_pq;

		min_clear = 1.0;                       /* Compiler dummy: not relied on */
		for (i = test_start; i <= test_stop; i++)
		{
			d_pi = di[i] - d_p;
			d_iq = d_q - di[i];
			h_t = hi[i] + (d_pi * d_iq / r_eff_2);  /* cartesian terrain ht */
			h_r = ((h_p * d_iq) + (h_q * d_pi)) / d_pq;   /* cartesian ray height */
			r_f = sqrt (d_pi * d_iq * wave_by_dist);      /* Fresnel zone radius  */
			clearance1 = (h_r - h_t) / r_f;
			if (i == test_start || clearance1 < min_clear)
			{
				index1 = i;
				min_clear = clearance1;
			}
		}
		*index = index1;
		*clearance = min_clear;
	}
	else                                     /* if no point between set       */
	{
		*index = 0;                          /* default index and clearance   */
		*clearance = 1.0;
		return 0;
	}
	 return 0;
}

double CP452_Functions::extract_sea_fraction (int *zi,int points)
{
	double sea_fract;                   /* fraction of path over sea         */
	long water_pts = 0;                     /* number of water points            */
	int  TDB_ZONE_SEA = 1;

	for (long i = 0; i < points; i++)                  /* count sea points        */
	{
		if (zi[i] == TDB_ZONE_SEA)
			water_pts++;
	}
	sea_fract = (double)(water_pts) / (double)(points);     /* assign returned result  */

	return sea_fract;
}

double CP452_Functions::do_k_diff (double time_pc, double k50, double beta_0)
{
	if (time_pc < beta_0)                /* for time percentage < beta_0  */
		time_pc = beta_0;                  /*  time percentage set = beta_0 */

	double k = do_k (time_pc, k50, beta_0);     /* compute k factor              */
	return k;
}


double CP452_Functions::do_k (double time_pc, double k50, double beta_0)
{
	 double eta;                                      /* eta in PN452 */
	 double k;                                        /* k factor     */

	 eta = log10 (time_pc / beta_0) / log10 (1.0 + (20.0 / beta_0));
	 k = k50 + (5.0 - k50) * exp (-5.3 * eta);
	 return k;
}

void CP452_Functions::ReadData(CString antfile) 
{
	int k = 0;
	double *m_di1;		m_di1 = new double[100000];
	double *m_hi1;		m_hi1 = new double[100000];
	int *m_zi1;			m_zi1 = new int[100000];

	FILE *fid;
	fid = fopen(antfile,"rt");

	char di [20], hi [20], zi [20];

	while( !feof( fid ) )
	{
		fscanf( fid, "%s %s %s", di,hi,zi);
		m_di1[k] = atof(di);
		m_hi1[k] = atof(hi);
		m_zi1[k] = atoi(zi);
		k++;
	}
	fclose(fid);

	m_npoint = k;

	m_di = new double[m_npoint];
	m_hi = new double[m_npoint];
	m_hikm = new double[m_npoint];
	m_zi = new int[m_npoint];

	for (int i=0;i<m_npoint;i++)
	{
		m_di[i] = m_di1[i];
		m_hikm[i] = m_hi1[i]/1000.0;
		m_hi[i] = m_hi1[i];
		m_zi[i] = m_zi1[i];
	}
	delete [] m_di1;
	delete [] m_hi1;
	delete [] m_zi1;
}
void CP452_Functions::extract_Dtm_Dlm(double *di,int *zi,int npiont, double *d_tm_p, double *d_lm_p)
{
	long i;
	int is_land, is_inland;           /* flags to indicate zone              */
	double land_near, inland_near;    /* distance at which section starts km */
	double land_far, inland_far;      /* distance at which section stops  km */
	double land, inland;              /* current maximum section lengths km  */
	double d_tm, d_lm;                /* final results                       */

	is_land = is_inland = 0;
	land_near = inland_near = 0.0;                     /* set up flags       */
	land_far = inland_far = 0.0;                       /*  and initial       */
	land = inland = 0.0;                               /*  distances         */
	d_tm = d_lm = 0.0;

	int TDB_ZONE_SEA     = 1,
		TDB_ZONE_COASTAL = 2,
		TDB_ZONE_INLAND  = 3;

	for (i = 0; i < npiont; i++)    /* loop points:    */
	{
		if (zi[i] == TDB_ZONE_SEA)                           /* end of LAND     */
		{
			if (is_land)
			{
				land = land_far - land_near;
				if (land > d_tm)
					d_tm = land;
				is_land = 0;
			}
		}
		if (zi[i] == TDB_ZONE_SEA || zi[i] == TDB_ZONE_COASTAL)     /* end of INLAND   */
		{
			if (is_inland)
			{
				inland = inland_far - inland_near;
				if (inland > d_lm)
					d_lm = inland;
				is_inland = 0;
			}
		}
		if (zi[i] == TDB_ZONE_COASTAL || zi[i] == TDB_ZONE_INLAND)  /* start of LAND */
		{
			if (is_land)
				land_far = di[i];
			else
			{
				is_land = 1;
				land_near = land_far = di[i];
			}
		}
		if (zi[i] == TDB_ZONE_INLAND)                        /* start of INLAND */
		{
			if (is_inland)
				inland_far = di[i];
			else
			{
				is_inland = 1;
				inland_near = inland_far = di[i];
			}
		}
	}                                                     /* at end of       */
	if (is_land)                                          /*  profile, stop  */
	{
		land = land_far - land_near;                        /*  any current    */
		if (land > d_tm)                                    /*  sections       */
			d_tm = land;
	}
	if (is_inland)
	{
		inland = inland_far - inland_near;
		if (inland > d_lm)
			d_lm = inland;
	}
	*d_tm_p = d_tm;                                       /* assign return   */
	*d_lm_p = d_lm;                                       /*  values         */
}

double CP452_Functions::do_beta_0 (double *di,int *zi,int npoint)
{
	double d_tm, d_lm;         /* longest continuous land, inland,           */
	double tau, mu1;           /* distances km used in computation of beta_0 */
	double beta_0;
	extract_Dtm_Dlm (di,zi,npoint, &d_tm, &d_lm);         /* total-land and inland km */

	tau = 0.1 + (0.22 * exp (-d_lm / 20.0));       /* NOTE: '20' was '25' &    */
	mu1 = tau + ((1.0 - tau) * exp (-d_tm / 15.0));  /* '15' was '13' at Boulder */
	beta_0 = 7.0 * mu1;
	return beta_0;
}
