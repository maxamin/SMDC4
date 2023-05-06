// Int_BT2BT_FreeDoc.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Int_BT2BT_FreeDoc.h"


#include "UTM.h"
#include <math.h>
#include <afxdb.h>

#include "Int_Functions.h"
#include "ProgressBar.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInt_BT2BT_FreeDoc

IMPLEMENT_DYNCREATE(CInt_BT2BT_FreeDoc, CDocument)

CInt_BT2BT_FreeDoc::CInt_BT2BT_FreeDoc()
{
	colormaptype="Jet";
	m_tile.ColorMap(colormaptype);
	for (int i=0;i<256;i++)
		RGBt[i]=m_tile.RGBt[i];

	m_NoData=(_int16)(m_tile.m_NoData);

	bufMin=32767;	bufMax=-32768;
	ErMin=32767.0;	ErMax=-32768.0;
	ErUMin=32767.0;	ErUMax=-32768.0;
//	ErCMin=32767.0;	ErCMax=-32768.0;
	ErCMin=0;		ErCMax=2;

	m_ZoomFactor=1;

	m_ReadyDoc=0;

	m_level = 255;
	m_bThreshold = false;
	m_Threshold = 60.0;

	long UNR = 72 ;
	WDBUNIT(&UNR) ;
}

BOOL CInt_BT2BT_FreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CInt_BT2BT_FreeDoc::~CInt_BT2BT_FreeDoc()
{
	delete [] bufAreaFree;
	delete [] bufArea;
	delete [] Er;
	delete [] m_latY;
	delete [] m_lonY;
	delete [] m_nameY;
	delete [] ErU;
	delete [] ErC;
}


BEGIN_MESSAGE_MAP(CInt_BT2BT_FreeDoc, CDocument)
	//{{AFX_MSG_MAP(CInt_BT2BT_FreeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInt_BT2BT_FreeDoc diagnostics

#ifdef _DEBUG
void CInt_BT2BT_FreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInt_BT2BT_FreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInt_BT2BT_FreeDoc serialization

void CInt_BT2BT_FreeDoc::Serialize(CArchive& ar)
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
// CInt_BT2BT_FreeDoc commands


void CInt_BT2BT_FreeDoc::GetData()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	double attH0X[37], attV0X[37], erp_h_dbwX, erp_v_dbwX , erpdbwX, 
		   attH0Y[37], attV0Y[37], erp_h_dbwY, erp_v_dbwY , erpdbwY;
	int az0[37];
	CString polarX , polarY , ant_dirX, ant_dirY;

	long terrakeyY ,	 terrakeyX = atol(GetFld(m_SelX,1));
	long AntID ;	 AntID = atol(GetFld(m_SelX,30));

	double freq_assgnX = atof(GetFld(m_SelX,18));
	CString Xsys  = GetFld(m_SelX,16);		Xsys.TrimRight();

	polarX = GetFld(m_SelX,8);		polarX.TrimRight();
	ant_dirX = GetFld(m_SelX,12);	ant_dirX.TrimRight();
	erp_h_dbwX = atof(GetFld(m_SelX,10));
	erp_v_dbwX = atof(GetFld(m_SelX,11));

	double offsetX = atof(GetFld(m_SelX,23));
	CString freq_stablX = GetFld(m_SelX,22);		freq_stablX.TrimRight();

	for(int i=0;i<36;i++)
		az0[i] = 10*i;

	if(ant_dirX=="D")
		GE84pattern(terrakeyX,attH0X,attV0X,polarX);
	else
		for(int i=0;i<36;i++)
		{
			attH0X[i] = 0;
			attV0X[i] = 0;
		}
	az0[36] = 360;
	attH0X[36] = attH0X[0];
	attV0X[36] = attV0X[0];

	double PodBwX[37];
	for( i=0;i<37;i++)
	{
		if(polarX == "H")			erpdbwX = erp_h_dbwX - attH0X[i];
		else if(polarX == "V")		erpdbwX = erp_v_dbwX - attV0X[i];
		else			erpdbwX = 10.0*log10(pow(10.0,(erp_h_dbwX - attH0X[i])/10.0) + pow(10.0,(erp_v_dbwX - attV0X[i])/10.0));
		erpdbwX = erpdbwX + 2.1;	// EIRP
		PodBwX[i] = erpdbwX;
	}

//98/01/20
double disttest1 = Distance_km(Freelat_ST,Freelon_ST, Freelat_ST+0, Freelon_ST+m_Resolution_x);
double disttest2 = Distance_km(Freelat_ST,Freelon_ST, Freelat_ST+m_Resolution_x, Freelon_ST+0);
double StepRes = min(disttest1, disttest2)/m_ZoomFactor;

	Nrow = ((CSMS4DCApp *)AfxGetApp())->Nrow;
	CString *m_Sel; m_Sel = new CString[Nrow];

	m_latY = new double[Nrow];
	m_lonY = new double[Nrow];
	m_nameY = new CString[Nrow];
	double *freq_assgnY;	freq_assgnY = new double[Nrow];
	double *PodBwY;			PodBwY = new double[Nrow*37];
	double *PolarDisc;		PolarDisc = new double[Nrow];
	double *Esi;			Esi = new double[Nrow];

	int *Orthogonal;		Orthogonal = new int[Nrow];

	double *offsetY;		offsetY = new double[Nrow];
	CString *Ysys;			Ysys = new CString[Nrow];

	double Esi0;

	for(int Yi = 0;Yi<Nrow;Yi++)
	{
		m_Sel[Yi] = ((CSMS4DCApp *)AfxGetApp())->m_Sel[Yi];
		m_latY[Yi] = atof(GetFld(m_Sel[Yi],5));
		m_lonY[Yi]  = atof(GetFld(m_Sel[Yi],6));
		m_nameY[Yi]  = GetFld(m_Sel[Yi],4);
		terrakeyY = atol(GetFld(m_Sel[Yi],1));
		ant_dirY = GetFld(m_Sel[Yi],12);	ant_dirY.TrimRight();
		polarY = GetFld(m_Sel[Yi],8);		polarY.TrimRight();
		erp_h_dbwY = atof(GetFld(m_Sel[Yi],10));
		erp_v_dbwY = atof(GetFld(m_Sel[Yi],11));

		freq_assgnY[Yi] = atof(GetFld(m_Sel[Yi],18));

		offsetY[Yi] = atof(GetFld(m_Sel[Yi],23));
		Ysys[Yi]  = GetFld(m_Sel[Yi],16);	Ysys[Yi].TrimRight();

		/////////////////// Polarization Discrimination ////////
		if((((polarX == "H")&&(polarY == "V"))||((polarX == "V")&&(polarY == "H")))&&(m_PolDisc))
			PolarDisc[Yi] = m_EDIT_PolDisc;
		else
			PolarDisc[Yi] = 0.0;

		if(((polarX == "H")&&(polarY == "V"))||((polarX == "V")&&(polarY == "H")))
			Orthogonal[Yi] = 1;
		else
			Orthogonal[Yi] = 0;

		///////////////////////////////////////////////////

		if(ant_dirY=="D")
			GE84pattern(terrakeyY,attH0Y,attV0Y,polarY);
		else
			for(int i=0;i<36;i++)
			{
				attH0Y[i] = 0;
				attV0Y[i] = 0;
			}
		attH0Y[36] = attH0Y[0];
		attV0Y[36] = attV0Y[0];
		for( i=0;i<37;i++)
		{
			if     (polarY == _T("H"))		erpdbwY = erp_h_dbwY - attH0Y[i];
			else if(polarY == _T("V"))		erpdbwY = erp_v_dbwY - attV0Y[i];
			else						erpdbwY = 10.0*log10(pow(10.0,(erp_h_dbwY - attH0Y[i])/10.0) + pow(10.0,(erp_v_dbwY - attV0Y[i])/10.0));
			erpdbwY = erpdbwY + 2.1;	// EIRP
			PodBwY[i+37*Yi] = erpdbwY;
		}
	}
	double FreePtGt_Y;

	CInt_Functions IntFunc;

	Width  = m_ZoomFactor * bufAreaW;
	Height = m_ZoomFactor * bufAreaH;
	bufArea = new _int16[Width*Height];

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			bufArea[i+Width*j]=bufAreaFree[(i/m_ZoomFactor)+(Width/m_ZoomFactor)*(j/m_ZoomFactor)];
			bufMin=min(bufMin,bufArea[i+Width*j]);
			bufMax=max(bufMax,bufArea[i+Width*j]);
		}

	Er  = new double[Width*Height];
	ErU = new double[Width*Height];
	ErC = new double[Width*Height];

	double Ex , Eu , PR;
	double dist , Ghv=1 , azX, azY;
	double lat_j,lon_i;

	double AzT_X , AzT_Y, DAZ , Ari = 0;

	CProgressBar bar(_T("Progress"), 40, Width*Height,FALSE,0);
	int progress_num=0;
	CString progress_str;
	bar.SetText("  ");
	bar.SetBarColour(RGB(127,0,0));

	for( i=0;i<Width;i++)
		for(int j=0;j<Height;j++)
		{
			lat_j = Freelat0+(j/m_ZoomFactor)*m_Resolution_x;
			lon_i = Freelon0+(i/m_ZoomFactor)*m_Resolution_x;

			CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
			if (TileInfo != globeTileInfo)
			{
				CUtm m_utm;
				m_utm.y = lat_j;
				m_utm.x = lon_i;
				m_utm.UTM2philambda();
				lat_j=m_utm.phi;
				lon_i=m_utm.lambda;
			}
			dist = Dist_km_Az_Deg(Freelat_ST,Freelon_ST,lat_j,lon_i,&azX); 
			dist = max(dist,0.00001);

			FreePtGt_ST = Interp2(az0,PodBwX,azX,37);
			FreePtGt_ST = pow(10.0,FreePtGt_ST/10.0);
			Ex = (sqrt(30.0*FreePtGt_ST*Ghv))/(1000.0*dist);
			Ex = 120.0+20.0*log10(Ex);

			for(Yi=0;Yi<Nrow;Yi++)
			{
				/////////////////// Antenna Discrimination ////////
				Ari = 0;
				if((m_AntDisc)&&(Orthogonal[Yi]==0))
				{
					AzT_X = Azimuth_Deg(lat_j,lon_i,Freelat_ST,Freelon_ST) ;
					AzT_Y = Azimuth_Deg(lat_j,lon_i,m_latY[Yi],m_lonY[Yi]) ;
					DAZ = fabs(AzT_X-AzT_Y);
					if(DAZ>180.0)
						DAZ = 360.0-DAZ;
					Ari = IntFunc.BT419(DAZ,freq_assgnX);
				}
				///////////////////////////////////////////////////
				dist = Dist_km_Az_Deg(m_latY[Yi],m_lonY[Yi],lat_j,lon_i,&azY); 
		//		dist = max(dist,0.00001);
				dist = max(dist,StepRes/2.0);		//98/01/20

				FreePtGt_Y = Interp2(az0,&PodBwY[37*Yi],azY,37);
				FreePtGt_Y = pow(10.0,FreePtGt_Y/10.0);

				Esi0 = (sqrt(30.0*FreePtGt_Y*Ghv))/(1000.0*dist);		//V/m
				Esi0 = 120.0+20.0*log10(Esi0);							//dBuV/m

				PR = IntFunc.BT_ProtectionR(freq_assgnX,freq_assgnY[Yi],offsetX,offsetY[Yi],Xsys,Ysys[Yi],freq_stablX,Esi0,Esi0);

				Esi0 = Esi0 + PR +  Ari - PolarDisc[Yi];				//dBuV/m

				Esi[Yi] = Esi0;
			}
			if(methodSUM==0)
				Eu = IntFunc.Eu_PowerSum(Esi,Nrow,m_Fmin);
			else
				Eu = IntFunc.Eu_SimpleMulti(Esi,Nrow,P_Location,freq_assgnX);

			if(Ex<m_Fmin)		ErC[i+Width*j] = 0;		// not covered
			else
			{
				if (Ex >= Eu)	ErC[i+Width*j] = 2;		// with interference
				else			ErC[i+Width*j] = 1;		// without interference
			}
		//	ErCMax=max(ErCMax , ErC[i+Width*j] );
		//	ErCMin=min(ErCMin , ErC[i+Width*j] );

			ErU[i+Width*j] = Eu;	
			ErUMax=max(ErUMax , ErU[i+Width*j] );
			ErUMin=min(ErUMin , ErU[i+Width*j] );

			Er[i+Width*j] = ErC[i+Width*j];	

			////////////////////progress bar////////////////////
			if(progress_num%100==0)
			{
				progress_str.Format("%02d%% complete", progress_num*100/(Width*Height));
				bar.SetText(progress_str);
				bar.SetPos(progress_num);
				//bar.StepIt();
				PeekAndPump();
			}
			progress_num++;
			////////////////////progress bar////////////////////
		}
	ErMin = ErCMin;
	ErMax = ErCMax;

	m_MinValue = ErMin;
	m_MaxValue = ErMax;

	delete [] m_Sel;
	delete [] PodBwY;
	delete [] freq_assgnY;
	delete [] PolarDisc;
	delete [] Esi;
	delete [] Orthogonal;
	delete [] offsetY;
	delete [] Ysys;

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

double CInt_BT2BT_FreeDoc::Dist_km_Az_Deg(double lat1,double lon1,double lat2,double lon2,double *RAZIM) 
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(lat1*pi/180.0),
			lon10 = (float)(lon1*pi/180.0),
			lat20 = (float)(lat2*pi/180.0),
			lon20 = (float)(lon2*pi/180.0),	RDIST, RAZIM0;
	GEOPPDA( &lon10 ,&lat10, &lon20,&lat20, &RDIST, &RAZIM0);
	*RAZIM = RAZIM0;
	return RDIST;
}


double CInt_BT2BT_FreeDoc::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) 
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(lat1*pi/180.0),
			lon10 = (float)(lon1*pi/180.0),
			lat20 = (float)(lat2*pi/180.0),
			lon20 = (float)(lon2*pi/180.0),	RDIST, RAZIM;
	GEOPPDA( &lon10 ,&lat10, &lon20,&lat20, &RDIST, &RAZIM);
	return RAZIM;
}

double CInt_BT2BT_FreeDoc::Distance_km(double lat1,double lon1,double lat2,double lon2) 
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(lat1*pi/180.0),
			lon10 = (float)(lon1*pi/180.0),
			lat20 = (float)(lat2*pi/180.0),
			lon20 = (float)(lon2*pi/180.0),	rng;
	GEODSTR( &lon10, &lat10, &lon20, &lat20, &rng);
	return (rng);
}

CString CInt_BT2BT_FreeDoc::GetFld(CString Src,int N)
{
	CString Fld = "";
	int place=0,Cnt=0;
	while( place <= Src.GetLength())
	{
		Fld="";
		for(int j = place ; j<=Src.GetLength();j++)
		{
			if(Src.Mid(j, 1) == ",") break;
			Fld = Fld + Src.Mid(j, 1);
		}//end for
		Cnt++;
		place = j + 1;
		if(Cnt==N) break;
	}//end while
	return Fld;
}


void CInt_BT2BT_FreeDoc::GE84pattern(long terrakey,double * attnH,double * attnV,CString pol) 
{
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase m_mydb;
	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		int kH, kV, i; 
		CString ss;
		int azmH[361], azmV[361];
		double attnH0[361],attnV0[361];

		if((pol=="H")||(pol=="M"))
		{
			CRecordset m_rs;
			CString	m_Tbl ;
			//m_Tbl.Format("select * from fmtv_ant_diag WHERE (terrakey=%d AND polar=\'%s\') order by azm;",terrakey,"H");
			m_Tbl.Format("select * from antdiag WHERE (AntID=%ld AND polar=\'%s\') order by azm;",terrakey,"H");

			m_rs.m_pDatabase = &m_mydb;
			m_rs.Open( CRecordset::snapshot, m_Tbl);

			kH=0;
			while(!m_rs.IsEOF())
			{
				m_rs.MoveNext();
				kH++;
			}
			m_rs.MoveFirst();
			for (i=0;i<kH;i++)
			{
				m_rs.GetFieldValue((short)1,ss);
				azmH[i] = atof(ss);
				m_rs.GetFieldValue((short)3,ss);
				attnH0[i] = atof(ss);
				if(pol=="H")
				{
					attnV0[i] = 0.0;
					azmV[i] = azmH[i];
				}
				m_rs.MoveNext();
			}
			m_rs.Close();
		}
		if((pol=="V")||(pol=="M"))
		{
			CRecordset m_rs1;
			CString	m_Tbl1 ;
			m_Tbl1.Format("select * from antdiag WHERE (AntID=%ld AND polar=\'%s\') order by azm;",terrakey,"V");

			m_rs1.m_pDatabase = &m_mydb;
			m_rs1.Open( CRecordset::snapshot, m_Tbl1);
			kV = 0;
			while(!m_rs1.IsEOF())
			{
				m_rs1.MoveNext();
				kV++;
			}
			m_rs1.MoveFirst();
			for (i=0;i<kV;i++)
			{
				m_rs1.GetFieldValue((short)1,ss);
				azmV[i] = atof(ss);
				m_rs1.GetFieldValue((short)3,ss);
				attnV0[i] = atof(ss);
				if(pol=="V")
				{
					attnH0[i]=0.0;
					azmH[i] = azmV[i];
				}
				m_rs1.MoveNext();
			}
			m_rs1.Close();
		}
		m_mydb.Close();

		if(pol=="H")	kV = kH;
		if(pol=="V")	kH = kV;

		azmH[kH] = 360;
		azmV[kV] = 360;
		attnH0[kH] = attnH0[0];
		attnV0[kV] = attnV0[0];

		int m_NUM = 36; 
		for (i=0;i<m_NUM;i++)
		{
			attnH[i] = Interp2(azmH,attnH0,i*360/m_NUM,kH+1) ;
			attnV[i] = Interp2(azmV,attnV0,i*360/m_NUM,kV+1) ;
		}

	}	

}


double CInt_BT2BT_FreeDoc::Interp2(int *D0,double *E0,double d,int num) 
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

BOOL CInt_BT2BT_FreeDoc::PeekAndPump()
{
	static MSG msg;

	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
	{
		if (!AfxGetApp()->PumpMessage())
		{
			::PostQuitMessage(0);
			return FALSE;
		}	
	}

	return TRUE;
}