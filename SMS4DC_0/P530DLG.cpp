// P530DLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "P530DLG.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CP530DLG dialog


CP530DLG::CP530DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CP530DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP530DLG)
	m_k = _T("4/3");
	m_k99 = _T("4/3");
	m_fzn = 1.0;
	m_atomi = 1;
	m_dist = 42.1;
	m_anav = _T("99.99");
	m_CHECK_Q = FALSE;
	//}}AFX_DATA_INIT
}


void CP530DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP530DLG)
	DDX_Control(pDX, IDC_CHECK_ITUstd, m_ITUstd);
	DDX_Control(pDX, IDC_COMBO_atom, m_atom);
	DDX_Text(pDX, IDC_EDIT_k, m_k);
	DDX_Text(pDX, IDC_EDIT_k99, m_k99);
	DDX_Text(pDX, IDC_EDIT_FZN, m_fzn);
	DDV_MinMaxDouble(pDX, m_fzn, 1.e-002, 20.);
	DDX_Text(pDX, IDC_EDIT_atomi, m_atomi);
	DDX_Text(pDX, IDC_EDIT_D, m_dist);
	DDX_Text(pDX, IDC_EDIT_anav, m_anav);
	DDX_Check(pDX, IDC_CHECK_Quick, m_CHECK_Q);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP530DLG, CDialog)
	//{{AFX_MSG_MAP(CP530DLG)
	ON_CBN_SELCHANGE(IDC_COMBO_atom, OnSelchangeCOMBOatom)
	ON_BN_CLICKED(IDC_CHECK_ITUstd, OnCHECKITUstd)
	ON_BN_CLICKED(IDC_RADIO1_Av, OnRADIO1Av)
	ON_BN_CLICKED(IDC_RADIO1_Wo, OnRADIO1Wo)
	ON_EN_KILLFOCUS(IDC_EDIT_anav, OnKillfocusEDITanav)
	ON_BN_CLICKED(IDC_RADIO1_rain1, OnRADIO1rain1)
	ON_BN_CLICKED(IDC_RADIO1_rain2, OnRADIO1rain2)
	ON_BN_CLICKED(IDC_RADIO1_rain3, OnRADIO1rain3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP530DLG message handlers

BOOL CP530DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(true);

	((CButton*)GetDlgItem(IDC_RADIO1_rain1))->SetWindowText("Global");
	((CButton*)GetDlgItem(IDC_RADIO1_rain2))->SetWindowText("Tropical, subtropical and temperate climate regions with frequent rain");
	((CButton*)GetDlgItem(IDC_RADIO1_rain3))->SetWindowText("Dry temperate, polar and desert regions");
	OnRADIO1rain1();

	((CButton*)GetDlgItem(IDC_RADIO1_Av))->SetWindowText("Avarage year/Annual");
	((CButton*)GetDlgItem(IDC_RADIO1_Wo))->SetWindowText("Worst-Month");
	((CButton*)GetDlgItem(IDC_RADIO1_Av))->SetCheck(true);
	m_flag_WorstMonth = 0;

	((CButton*)GetDlgItem(IDC_CHECK_Quick))->SetWindowText(_Z("Quick planning"));

/*
	m_atom.AddString(_Z("ANNUAL TROPIC"));
	m_atom.AddString(_Z("ITU-R REF STD (default)"));
	m_atom.AddString(_Z("SUMMER HIGH LATITUDE"));
	m_atom.AddString(_Z("SUMMER MID-LATITUDE"));
	m_atom.AddString(_Z("WINTER HIGH LATITUDE"));
	m_atom.AddString(_Z("WINTER MID-LATITUDE"));
	m_atom.SetTopIndex(1);
	m_atom.SetCurSel(1);	
*/
	m_atom.AddString(_Z("SUMMER"));
	m_atom.AddString(_Z("WINTER"));
	m_atom.SetCurSel(0);
	
	RADIO_AvWo();

	m_ITUstd.SetCheck(true);
	OnCHECKITUstd();
	
	m_k99.Format("%0.4f", Dist_ke(m_dist));
	m_k = m_k99;

	UpdateData(false);
	
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CP530DLG::OnSelchangeCOMBOatom() 
{
	UpdateData(true);
//	m_atomi = m_atom.GetCurSel();
	OnCHECKITUstd();
	UpdateData(false);
}


double CP530DLG::Dist_ke(double d) 
{
	//  Calculation of Effective the K Factor respect to sites distance
	double ke ;
	if(d<18.4)
		ke = 0.55;
	else if (d>199.5) 
		ke = 1.0;
	else
	{
		//	Reading k 99.99 % from saved curve file: K_Factor.txt
 		FILE *File;
		int i;
 		double ke0[364], D0[364];

		CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\K_factor.txt");
 		if ((File = fopen(FileInfo,"r"))==NULL)
 		{
 			AfxMessageBox("The file 'K_Factor.txt' was not opened.");	exit(0);
 		}
		char bf1[200],bf2[200];
		for (i=0; i<364; i++)
		{
			fscanf(File,"%s  %s",&bf1,&bf2);
			D0[i] = atof(bf1);
			ke0[i] = atof(bf2);
		}
		ke = Interp1(D0, ke0, d, 364);
	}
	return ke;
}

double CP530DLG::Interp1(double *D0,double *E0,double d,int num) 
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

void CP530DLG::OnCHECKITUstd() 
{
	int i = m_ITUstd.GetCheck();
	bool flag = false;
	if(i==1)						m_iClimate = 0;	//m_ClimateSTR = "ITU-R REF STD (default)";
	else
	{
		if(fabs(m_LatM)<22.0)		m_iClimate = 4;	//m_ClimateSTR = "";
		else
		{
			int iClimate = m_atom.GetCurSel();
			if		(iClimate==0)	m_iClimate = 1;	//m_ClimateSTR = "SUMMER";
			else if (iClimate==1)	m_iClimate = 2;	//m_ClimateSTR = "WINTER";
			flag = true;
		}
	}
	GetDlgItem(IDC_STATICb6)->EnableWindow(flag);
	GetDlgItem(IDC_COMBO_atom)->EnableWindow(flag);
}


void CP530DLG::RADIO_AvWo() 
{
//	GetDlgItem(IDC_STATIC_841)->EnableWindow(m_flag_WorstMonth);
//	GetDlgItem(IDC_RADIO1_rain1)->EnableWindow(m_flag_WorstMonth);
//	GetDlgItem(IDC_RADIO1_rain2)->EnableWindow(m_flag_WorstMonth);
//	GetDlgItem(IDC_RADIO1_rain3)->EnableWindow(m_flag_WorstMonth);
	OnKillfocusEDITanav();
}
void CP530DLG::OnRADIO1Av() 
{
	((CButton*)GetDlgItem(IDC_RADIO1_Av))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO1_Wo))->SetCheck(false);
	m_flag_WorstMonth = 0;
	RADIO_AvWo();
}
void CP530DLG::OnRADIO1Wo() 
{
	((CButton*)GetDlgItem(IDC_RADIO1_Av))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO1_Wo))->SetCheck(true);
	m_flag_WorstMonth = 1;
	RADIO_AvWo();
}

void CP530DLG::OnKillfocusEDITanav() 
{
	UpdateData();
//	double h1 = m_Htg + m_H[0];
//	double h2 = m_Hrg + m_H[m_N-1];

	if(atof(m_anav)>=100.0)		m_anav.Format("%0.6f", 99.9999999);
	if(atof(m_anav)<=0.0)		m_anav.Format("%0.6f",  0.0000001);

	double pw, py, DeltaG;
	if(m_flag_WorstMonth == 1)	pw = 100.0 - atof(m_anav);
	else
	{
		py = 100.0 - atof(m_anav);
		DeltaG = DeltaG_factor(m_LatM,m_dist,m_h1,m_h2);
		pw = pow(10.0, (DeltaG/10.0))*py;			// conversion from average year to the Worst month
	}

	if(pw>=100)  
	{
		pw = 99.9999999;
		if(m_flag_WorstMonth == 1)	m_anav.Format("%0.6f", 100.0 - pw);
		else
		{
			DeltaG = DeltaG_factor(m_LatM,m_dist,m_h1,m_h2);
			py = pow(10.0, (-DeltaG/10.0))*pw;		// conversion from Worst month to the average year
			m_anav.Format("%0.6f", 100.0 - py);
		}
	}
	m_pw.Format("%0.6f", pw);
	UpdateData(false);
}
double CP530DLG::DeltaG_factor(double lat_deg,double d_km,double hr,double he)
{
	double ep = fabs(hr-he)/d_km ;		//Equation (6)   path inclination in miliradian

	int  S;
	if(lat_deg<=45.0)	S = +1;
	else				S = -1;
	double pi = 4.0*atan(1.0);
	double DeltaG = 10.5-5.6*log10(1.1 + S*pow(fabs(cos(2.0*lat_deg*pi/180.0)) , 0.7) )-2.7*log10(d_km)+1.7*log10(1+ep); //Equation (24)
	DeltaG = min(10.8 , DeltaG);

	return DeltaG;
}

void CP530DLG::OnRADIO1rain1() 
{
	((CButton*)GetDlgItem(IDC_RADIO1_rain1))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO1_rain2))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO1_rain3))->SetCheck(false);
	m_RADIO1_rain = 1;
}
void CP530DLG::OnRADIO1rain2() 
{
	((CButton*)GetDlgItem(IDC_RADIO1_rain1))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO1_rain2))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO1_rain3))->SetCheck(false);	
	m_RADIO1_rain = 2;
}
void CP530DLG::OnRADIO1rain3() 
{
	((CButton*)GetDlgItem(IDC_RADIO1_rain1))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO1_rain2))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO1_rain3))->SetCheck(true);	
	m_RADIO1_rain = 3;
}


