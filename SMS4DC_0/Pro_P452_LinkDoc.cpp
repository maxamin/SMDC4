// Pro_P452_LinkDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P452_LinkDoc.h"
#include <math.h>
#include "UTM.h"
//#include "P452_Functions.h"

#include "TxRxFiltersSet.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P452_LinkDoc

IMPLEMENT_DYNCREATE(CPro_P452_LinkDoc, CDocument)

CPro_P452_LinkDoc::CPro_P452_LinkDoc()
{
	m_ReadyDoc=0;
	m_DrawFresnel = false;

	long UNR = 72 ;
	WDBUNIT(&UNR) ;
}

BOOL CPro_P452_LinkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_P452_LinkDoc::~CPro_P452_LinkDoc()
{
	delete [] m_di;
	delete [] m_hi;
	delete [] m_hikm;
	delete [] m_lati;
	delete [] m_loni;
	delete [] m_zi;

}


BEGIN_MESSAGE_MAP(CPro_P452_LinkDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_P452_LinkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P452_LinkDoc diagnostics

#ifdef _DEBUG
void CPro_P452_LinkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_P452_LinkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P452_LinkDoc serialization

void CPro_P452_LinkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPro_P452_LinkDoc commands


__declspec(dllimport) int BasicTxLossP452V15(double* mD, double* mH, CString *mZ, long Np, double LongM, double LatM, CString FilepathData,
											double mtime, int timeflag, double f, double htg, double hrg, double Gt, double Gr, 
											double pressure, double temp_C, CString POL, double ha_Clutter, double dk_Clutter, 
											double *loss);

int CPro_P452_LinkDoc::GetData() 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	m_zi = new CString[Np+1];
	for(int i=0;i<Np;i++)
		m_zi[i] = LandSeaCoastal(m_loni[i],m_lati[i]);

	m_zi[i] = "";
	CString FilepathData = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + "\\Texts\\";

	double LongM, LatM;	
	PathMean(Linklon_ST, Linklat_ST, Linklon_Rx, Linklat_Rx, &LongM, &LatM);

	CString mLang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;

	double loss[7];
	int status = BasicTxLossP452V15(m_di, m_hi, m_zi, Np, LongM, LatM, FilepathData,
				Linktime, m_flagAvWo, LinkfMHz_ST/1000.0, LinkHagl_ST, LinkRxH, m_Gt,m_Gr, 
				m_Pressure, m_TempC, m_PolarizationTx, m_ha_Clutter, m_dk_Clutter, 
				loss);

	double pi=4.0*atan(1.0);
	m_Distance = Dmax-Dmin;
//	m_FsLoss = 20.0*log10(4.0*pi*m_Distance*LinkfMHz_ST/0.3);
//	m_FsLoss = 92.45 + (20.0 * log10 (m_Distance * LinkfMHz_ST/1000.0));
	m_FsLoss = 92.5  + (20.0 * log10 (m_Distance * LinkfMHz_ST/1000.0));

	if(status==0)
	{
		m_path_type = loss[5];
		Linkk = loss[6];

		if(m_path_type==3)	m_tit = _Z("Transhorizon Path");
		else				m_tit = _Z("Line of Sight Path");

		m_Loss1L = _Z("Diffraction Loss(dB) : ");	m_Loss1.Format("%0.3f",loss[0]);
		m_Loss2L = _Z("Troposcatter Loss(dB) : ");	m_Loss2.Format("%0.3f",loss[1]);
		m_Loss3L = _Z("Anomalous Loss(dB) : ");		m_Loss3.Format("%0.3f",loss[2]);
		m_Loss4L = _Z("Clutter Loss(dB) : ");		m_Loss4.Format("%0.3f",loss[3]);
		m_Loss5L = _Z("Total Loss(dB) : ");			m_Loss5.Format("%0.3f",loss[4]);
	}
	else
	{
		if     (status==1)  m_tit = _Z("The file 'DN50.dat' was not opened.");
		else if(status==2)  m_tit = _Z("The file 'N050.dat' was not opened.");

		m_Loss5L = _Z("Calculated Loss(dB) : ");
		m_Loss5.Format("%0.3f",m_FsLoss);			
		Linkk = 4.0/3.0;
	}

/*
	CP452_Functions CP452;

	double val_p = 0;
	double o_loss_bd,o_loss_bs,o_loss_ba,o_loss_d,o_clear_e,o_clear_50,o_k_e;
	int o_done_d,o_done_a,o_path_type, status;

	status = CP452.pn452_Lb(m_di,m_hikm,m_zi,Np,LinkfMHz_ST/1000.0,Linktime,LinkN0,LinkdN,
						Linkbeta,m_Gt,m_Gr,LinkHagl_ST/1000.0,LinkRxH/1000.0,
						&val_p,&o_loss_bd,&o_loss_bs,&o_loss_ba,&o_loss_d,
						&o_done_d,&o_done_a,&o_clear_e,&o_clear_50,&o_path_type,&o_k_e);

	double pi=4.0*atan(1.0);
	m_Distance = Dmax-Dmin;
//	m_FsLoss = 20.0*log10(4.0*pi*m_Distance*LinkfMHz_ST/0.3);
	m_FsLoss = 92.45 + (20.0 * log10 (m_Distance * LinkfMHz_ST/1000.0));

	int PN452_SUCCESS     = 0,
		PN452_PATH        = -1,
		PN452_PROF        = -2,
		PN452_FREQ        = -3,
		PN452_ANT_HTS     = -6;

	int PN452_LOS_CLEAR   = 0,
		PN452_LOS_SUB_P   = 1,
		PN452_TRANS_HOZ   = 2,
		PN452_ERROR		  = 3;

	if(status == PN452_SUCCESS)
	{
		Linkk = o_k_e;
		m_path_type = o_path_type;
		if (o_path_type==PN452_LOS_CLEAR)
		{
			m_tit = _Z("Line of Sight with > 0.6 Fresnel Clearance");
			m_Loss1L = _Z("Basic XMN Loss(dB) : ");
			m_Loss1.Format("%0.3f",val_p);
		}
		else if (o_path_type==PN452_LOS_SUB_P)
		{
			m_tit = _Z("Line of Sight with Sub-Path Obstruction");
			m_Loss1L = _Z("Fresnel Clear : ");
			m_Loss1.Format("%0.3f",o_clear_50);

			m_Loss2L = _Z("Sup-Path Diff Loss(dB) : ");
			m_Loss2.Format("%0.3f",o_loss_d);

			m_Loss3L = _Z("Basic XMN Loss(dB) : ");
			m_Loss3.Format("%0.3f",val_p);
		}
		else if (o_path_type==PN452_TRANS_HOZ)
		{
			m_tit = _Z("Transhorizon Path");
			if (o_done_d)
				m_Loss1.Format("%0.3f",o_loss_bd);
			else
				m_Loss1.Format("%s","---");
			m_Loss1L = _Z("Diffraction Loss(dB) : ");

			m_Loss2L = _Z("Troposcatter Loss(dB) : ");
			m_Loss2.Format("%0.3f",o_loss_bs);
			if (o_done_a)
			{
				m_Loss3L = _Z("Anomalous Loss(dB) : ");
				m_Loss3.Format("%0.3f",o_loss_ba);
			}
			else
			{
				m_Loss3L = _Z("Anomalous Loss(dB) : ");
				m_Loss3.Format("%s","---");
			}
			m_Loss4L = _Z("Final Result Loss(dB) : ");
			m_Loss4.Format("%0.3f",val_p);
		}
	}
	else
	{
		switch (status)
		{
			case -1	: m_tit = _Z("Warning!--->Path too short");					break;
			case -2	: m_tit = _Z("Warning!--->too few profile points");			break;
			case -3	: m_tit = _Z("Warning!--->Frequency outside limits(0.69 - 40.01 GHz)");			break;
			case -6	: m_tit = _Z("Warning!--->Negative antenna height");			break;
			default	: m_tit = _Z("Warning!--->Unrecognised bad status code");		break;
		}
		m_path_type = PN452_ERROR;
		m_Loss1L = _Z("Calculated Loss(dB) : ");
		m_Loss1.Format("%0.3f",m_FsLoss);
		Linkk = (157.0 / (157.0 - (LinkdN)));
	}
*/
	///////////////////////////////// NFD //////////////
	m_NFD_Loss = 0;
	m_NFD_Loss = NFD_Loss() ;
	////////////////////////////////////////////////////
	return status;
}

CString CPro_P452_LinkDoc::LandSeaCoastal(double RLON_deg,double RLAT_deg) 
{
	double pi=4.0*atan(1.0);
	float RLON = (float)(RLON_deg*pi/180.0);
	float RLAT = (float)(RLAT_deg*pi/180.0);

	long int N=4, IER;
	GEOGCMS ( &N, &IER );

	float RLON1 = (float)(RLON-pi/90.0), RLAT1 = (float)(RLAT-pi/90.0),
		  RLON2 = (float)(RLON+pi/90.0), RLAT2 = (float)(RLAT+pi/90.0);

	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2],  GC;
	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
	GEOGCM( &IVAL, (float *)WND, &IRANGE);
	GEOGCP( &RLON, &RLAT, &GC);
/*
	int zone = 3;
	if		(GC==1)		zone = 1;	//LandSea = "Coastal Zone : Sea";           B
	else if (GC==3)		zone = 2;	//LandSea = "Coastal Zone : Coastal Land";  A1
	else if (GC==4)		zone = 3;	//LandSea = "Coastal Zone : InLand";        A2
*/
	CString zone = "A2";
	if		(GC==1)		zone = "B";	//LandSea = "Coastal Zone : Sea";				B
	else if (GC==3)		zone = "A1";	//LandSea = "Coastal Zone : Coastal Land";  A1
	else if (GC==4)		zone = "A2";	//LandSea = "Coastal Zone : InLand";        A2

	return zone;
}


double CPro_P452_LinkDoc::interwt(double *ft,double *at,int n,double f0) 
{
	double t0;

	if (f0>ft[n-1])
		t0 = at[n-1];
	else if (f0<ft[0])
		t0 = at[0];
	else
	{
		for (int i=0;i<n;i++)
		{
            if (ft[i]==f0)
			{
                t0 = at[i];
                break;
			}
            else if (ft[i]>f0)
			{
				t0=at[i-1]+(f0-ft[i-1])*(at[i]-at[i-1])/(ft[i]-ft[i-1]);
                break;
            }
		}
	}
	return t0;
}
double CPro_P452_LinkDoc::MinValue(double *xi,int N) 
{
	double  xiMIN = xi[0];
	for (int i=1;i<N;i++)
		xiMIN = min(xiMIN,xi[i]);	
	return xiMIN;
}
double CPro_P452_LinkDoc::MaxValue(double *xi,int N) 
{
	double  xiMAX = xi[0];
	for (int i=1;i<N;i++)
		xiMAX = max(xiMAX,xi[i]);	
	return xiMAX;
}
double CPro_P452_LinkDoc::subsection(double a,double b,double fc) 
{
	double y;
	if (a==0)
        y = fc * pow(10.0,(-b/10.0));
	else
        y = ( pow(10.0,(-b/10.0)) )*( pow(10.0,(-a*fc/10.0)) - 1.0 )/(-a*log(10.0)/10.0);
	return y;
}


double CPro_P452_LinkDoc::NFD_Loss() 
{
///////////////////////////////// NFD /////////////////////////////////
	double NFD = 0;
	CString str;

	str.Format("SELECT * FROM TxFilters WHERE (((EqID)=%ld)) ORDER BY CS;",ID_Tx);
	CTxRxFiltersSet m_pSet(str);
	m_pSet.Open();
	if(m_pSet.GetRecordCount()==1)
	{
		double ft0[20] , at0[20];
		m_pSet.MoveFirst();
		int TxNum = 0;
		while( !m_pSet.IsEOF())
		{
			ft0[TxNum] = m_pSet.m_CS;
			at0[TxNum] = m_pSet.m_Att;
			TxNum++;
			m_pSet.MoveNext();
		}
		m_pSet.Close();

		str.Format("SELECT * FROM RxFilters WHERE (((EqID)=%ld)) ORDER BY CS;",ID_Rx);
		CTxRxFiltersSet m_pSet1(str);
		m_pSet1.Open();
		if(m_pSet1.GetRecordCount()==1)
		{
			double fr0[20] , ar0[20];
			m_pSet1.MoveFirst();
			int RxNum = 0;
			while( !m_pSet1.IsEOF())
			{
				fr0[RxNum] = m_pSet1.m_CS;
				ar0[RxNum] = m_pSet1.m_Att;
				RxNum++;
				m_pSet1.MoveNext();
			}
			m_pSet1.Close();

			double  ft[20] , at[20], fr[20] , ar[20];
			double	ft0max = MaxValue(ft0,TxNum),	ft0min = MinValue(ft0,TxNum),
					fr0max = MaxValue(fr0,RxNum),	fr0min = MinValue(fr0,RxNum);

			double stepTx=(ft0max-ft0min)/19.0;
			double stepRx=(fr0max-fr0min)/19.0;
			int i;
			for( i=0;i<20;i++)
			{
				ft[i] = ft0min + i*stepTx;		at[i] = interwt(ft0,at0,TxNum,ft[i]);
				fr[i] = fr0min + i*stepRx;		ar[i] = interwt(fr0,ar0,RxNum,fr[i]);

				ft[i] = (ft[i] + LinkfMHz_ST)*1000000.0;
				fr[i] = (fr[i] + LinkfMHz_Rx)*1000000.0;
			}
			double	ftmax = MaxValue(ft,20),	ftmin = MinValue(ft,20),
					frmax = MaxValue(fr,20),	frmin = MinValue(fr,20),
					fmax = max(ftmax,frmax),	fmin = min(ftmin,frmin);

			int nf = 1000;
			double	fstep=(fmax-fmin)/nf;
			double *fnew;	fnew = new double[nf];
			double *atnew;  atnew = new double[nf];
			double *arnew;  arnew = new double[nf];
			double *y;		y = new double[nf-1];
			double *z;		z = new double[nf-1];
			double *fnewp;  fnewp = new double[nf];
			double *atnewp; atnewp = new double[nf];
			double *arnewp; arnewp = new double[nf];
			double *atrp;	atrp = new double[nf];

			for( i=0;i<nf;i++)
			{
				fnew[i] = fmin + i*fstep;
				atnew[i] = interwt(ft,at,20,fnew[i]);
				arnew[i] = interwt(fr,ar,20,fnew[i]);

				fnewp[i] = fnew[i]/1000000.0;
				atnewp[i] = -atnew[i];
				arnewp[i] = -arnew[i];
				atrp[i] = -atnew[i]-arnew[i];
			}
			double fc,a,b, sumy = 0.0, sumz = 0.0 ;
			for( i=0;i<nf-1;i++)
			{
				fc = fabs(fnew[i+1]-fnew[i]);
				a = (atnew[i+1]-atnew[i])/fc;
   				b = atnew[i];
				y[i] = subsection(a,b,fc);

				a = (atnew[i+1]-atnew[i]+arnew[i+1]-arnew[i])/fc;
				b = atnew[i]+arnew[i];
				z[i] = subsection(a,b,fc); 

				sumy += y[i];
				sumz += z[i];
			}
			NFD = 10.0*log10(sumy/sumz);

			delete [] fnew;	delete [] atnew;	delete [] arnew;	delete [] y;	delete [] z;
			delete [] atnewp;	delete [] arnewp;	delete [] fnewp;	delete [] atrp;

		}	// end if Rx Recoard set
		else
		{
			str.Format(_Z("\nRx Filter is not defined for the Receiver : %s.\t\t\n(Net Filter Discrimination = 0 dB)\n"),LinkName_Rx);
			MessageBox(NULL,str,_Z("Warning!!!"),MB_ICONWARNING);
		}

	}	// end if Tx Recoard set
	else
	{
		str.Format(_Z("\nTx Filter is not defined for the Transmitter : %s.\t\t\n(Net Filter Discrimination = 0 dB)\n"),LinkName_ST);
		MessageBox(NULL,str,_Z("Warning!!!"),MB_ICONWARNING);
	}
	return NFD;
}

void CPro_P452_LinkDoc::PathMean(double LeftLong, double LeftLat, double RightLong, double RightLat, double *LongM, double *LatM)
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(LeftLat*pi/180.0),		lon10 = (float)(LeftLong*pi/180.0),
			lat20 = (float)(RightLat*pi/180.0),		lon20 = (float)(RightLong*pi/180.0),	RDIST, RAZIM, RLON, RLAT;
	GEOPPDA( &lon10 ,&lat10, &lon20,&lat20, &RDIST, &RAZIM);

	float rng_km1 = RDIST/2.f;
	GEOPDAP( &lon10 ,&lat10, &rng_km1, &RAZIM, &RLON, &RLAT);
	*LongM = RLON*180.0/pi;
	*LatM  = RLAT*180.0/pi;
}