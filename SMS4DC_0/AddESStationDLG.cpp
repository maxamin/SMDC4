// AddESStationDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "AddESStationDLG.h"

#include <math.h>
#include <afxdb.h>

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddESStationDLG dialog


CAddESStationDLG::CAddESStationDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAddESStationDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddESStationDLG)
	m_STname = _T("");
	m_latD = _T("");
	m_latM = _T("");
	m_latS = _T("");
	m_lonD = _T("");
	m_lonM = _T("");
	m_lonS = _T("");
	m_STh_asl = 0.0;
	m_STlat_deg = 0.0;
	m_STlon_deg = 0.0;
	m_nameSat = _T("");
	m_AzFrom = 0.0;
	m_AzTo = 360.0;
	m_ElST = 5.0;
	m_ntcID = 0;
	//}}AFX_DATA_INIT
}


void CAddESStationDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddESStationDLG)
	DDX_Control(pDX, IDC_EStype, m_EStype);
	DDX_Control(pDX, IDC_lonU, m_lonU);
	DDX_Control(pDX, IDC_latU, m_latU);
	DDX_Text(pDX, IDC_EDIT_nameST, m_STname);
	DDX_Text(pDX, IDC_EDIT_latD, m_latD);
	DDX_Text(pDX, IDC_EDIT_latM, m_latM);
	DDX_Text(pDX, IDC_EDIT_latS, m_latS);
	DDX_Text(pDX, IDC_EDIT_lonD, m_lonD);
	DDX_Text(pDX, IDC_EDIT_lonM, m_lonM);
	DDX_Text(pDX, IDC_EDIT_lonS, m_lonS);
	DDX_Text(pDX, IDC_EDIT_HaslST, m_STh_asl);
	DDX_Text(pDX, IDC_EDIT_latST, m_STlat_deg);
	DDX_Text(pDX, IDC_EDIT_lonST, m_STlon_deg);
	DDX_Text(pDX, IDC_EDIT_nameSat, m_nameSat);
	DDX_Text(pDX, IDC_EDIT_AzFrom, m_AzFrom);
	DDX_Text(pDX, IDC_EDIT_AzTo, m_AzTo);
	DDX_Text(pDX, IDC_EDIT_ElST, m_ElST);
	DDX_Text(pDX, IDC_EDIT_IDST, m_ntcID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddESStationDLG, CDialog)
	//{{AFX_MSG_MAP(CAddESStationDLG)
	ON_EN_KILLFOCUS(IDC_EDIT_latD, OnKillfocusEDITlatD)
	ON_EN_KILLFOCUS(IDC_EDIT_latM, OnKillfocusEDITlatM)
	ON_EN_KILLFOCUS(IDC_EDIT_latS, OnKillfocusEDITlatS)
	ON_EN_KILLFOCUS(IDC_EDIT_lonD, OnKillfocusEDITlonD)
	ON_EN_KILLFOCUS(IDC_EDIT_lonM, OnKillfocusEDITlonM)
	ON_EN_KILLFOCUS(IDC_EDIT_lonS, OnKillfocusEDITlonS)
	ON_CBN_SELCHANGE(IDC_latU, OnSelchangelatU)
	ON_CBN_SELCHANGE(IDC_lonU, OnSelchangelonU)
	ON_EN_KILLFOCUS(IDC_EDIT_latST, OnKillfocusEDITlatST)
	ON_EN_KILLFOCUS(IDC_EDIT_lonST, OnKillfocusEDITlonST)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddESStationDLG message handlers

BOOL CAddESStationDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData();
	m_latU.AddString("N");
	m_latU.AddString("S");
	m_latU.SetTopIndex(1);
	m_latU.SetCurSel(0);
	
	m_lonU.AddString("E");
	m_lonU.AddString("W");
	m_lonU.SetTopIndex(1);
	m_lonU.SetCurSel(0);

	m_EStype.AddString("Specific (S)");
	m_EStype.AddString("Typical (T)");
	m_EStype.SetTopIndex(1);
	m_EStype.SetCurSel(0);

	left2right();

//98/04/12
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));		
	lf.lfHeight  = 14;					
	lf.lfCharSet = DEFAULT_CHARSET;			
	strcpy(lf.lfFaceName, "Arial");
	VERIFY(m_font.CreateFontIndirect(&lf));  
	((CEdit*)GetDlgItem(IDC_EDIT_nameST))->SetFont(&m_font);


	UpdateData(false);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}
//98/04/12
void CAddESStationDLG::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_font.DeleteObject();
}



void CAddESStationDLG::left2right() 
{
		char   xU,yU;
		int    xD,xM,yD,yM;
		double xS,yS;
		DEG2DMS("LON",m_STlon_deg,&xD,&xM,&xS,&xU);
		DEG2DMS("LAT",m_STlat_deg,&yD,&yM,&yS,&yU);

		CString str;
		str.Format("%03d",xD);	m_lonD=str;
		str.Format("%02d",xM);	m_lonM=str;
		str.Format("%0.1f",xS);	m_lonS=str;
		if (xU=='E')
			m_lonU.SetCurSel(0);
		else
			m_lonU.SetCurSel(1);

		str.Format("%02d",yD);	m_latD=str;
		str.Format("%02d",yM);	m_latM=str;
		str.Format("%0.1f",yS);	m_latS=str;
		if (yU=='N')
			m_latU.SetCurSel(0);
		else
			m_latU.SetCurSel(1);

}

void CAddESStationDLG::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
{
	if (x < 0)
	{
		x=-x;
		xU[0] = ( (type=="LON") ? 'W' : 'S');
	}
	else
		xU[0] = ( (type=="LON") ? 'E' : 'N');

	*xD=(int)x;
	double xM0=60.0*(x-(*xD));
	*xM=(int)xM0;
	*xS=60.0*(xM0-(*xM));

//	if (*xS>=59.999)
	if (*xS>=59.9)
	{
		*xM=*xM+1;	*xS=0.0;
		if (*xM>=60)
		{
			*xD=*xD+1;	*xM=0;
		}
	}
}

void CAddESStationDLG::OnKillfocusEDITlatD() 
{
	UpdateData();
	int D=atoi(m_latD	);
	D=min(90,max(D,0));
	CString str;
	str.Format("%02d",D);	m_latD=str;
	int k=m_latU.GetCurSel();
	double abs_lat_deg = (((double)D)+atof(m_latM)/60.0+atof(m_latS)/3600.0);
	abs_lat_deg = min(max(abs_lat_deg,0.0),90.0);
	m_STlat_deg = ( (k==0) ? 1.0:-1.0  ) * abs_lat_deg;

	CString strLat;
	strLat.Format("%0.6f",m_STlat_deg);
	m_STlat_deg = atof(strLat);

	left2right() ;
	UpdateData(FALSE);	
}

void CAddESStationDLG::OnKillfocusEDITlatM() 
{
	UpdateData();
	int M=atoi(m_latM	);
	M=min(59,max(M,0));
	CString str;
	str.Format("%02d",M);	m_latM=str;
	int k=m_latU.GetCurSel();
	double abs_lat_deg = (atof(m_latD)+((double)M)/60.0+atof(m_latS	)/3600.0);
	abs_lat_deg = min(max(abs_lat_deg,0.0),90.0);
	m_STlat_deg=( (k==0) ? 1.0:-1.0  ) * abs_lat_deg;

	CString strLat;
	strLat.Format("%0.6f",m_STlat_deg);
	m_STlat_deg = atof(strLat);

	left2right() ;
	UpdateData(FALSE);	
}

void CAddESStationDLG::OnKillfocusEDITlatS() 
{
	UpdateData();
	double S=atof(m_latS	);
//	S=min(59.999,max(S,0));
	S=min(59.9,max(S,0));
	CString str;
	str.Format("%0.1f",S);	m_latS=str;
	int k=m_latU.GetCurSel();
	double abs_lat_deg = (atof(m_latD)+atof(m_latM)/60.0+S/3600.0);
	abs_lat_deg = min(max(abs_lat_deg,0.0),90.0);
	m_STlat_deg=( (k==0) ? 1.0:-1.0  ) * abs_lat_deg;

	CString strLat;
	strLat.Format("%0.6f",m_STlat_deg);
	m_STlat_deg = atof(strLat);

	left2right() ;
	UpdateData(FALSE);	
}

void CAddESStationDLG::OnKillfocusEDITlonD() 
{
	UpdateData();
	int D=atoi(m_lonD	);
	D=min(180,max(D,0));
	CString str;
	str.Format("%03d",D);	m_lonD=str;
	int k=m_lonU.GetCurSel();
	double abs_lon_deg = (((double)D)+atof(m_lonM)/60.0+atof(m_lonS)/3600.0);
	abs_lon_deg = min(max(abs_lon_deg,0.0),180.0);
	m_STlon_deg=( (k==0) ? 1.0:-1.0  ) * abs_lon_deg;

	CString strLon;
	strLon.Format("%0.6f",m_STlon_deg);
	m_STlon_deg = atof(strLon);

	left2right() ;
	UpdateData(FALSE);	
}

void CAddESStationDLG::OnKillfocusEDITlonM() 
{
	UpdateData();
	int M=atoi(m_lonM	);
	M=min(59,max(M,0));
	CString str;
	str.Format("%02d",M);	m_lonM=str;
	int k=m_lonU.GetCurSel();
	double abs_lon_deg = (atof(m_lonD)+((double)M)/60.0+atof(m_lonS)/3600.0);
	abs_lon_deg = min(max(abs_lon_deg,0.0),180.0);
	m_STlon_deg=( (k==0) ? 1.0:-1.0  ) * abs_lon_deg;

	CString strLon;
	strLon.Format("%0.6f",m_STlon_deg);
	m_STlon_deg = atof(strLon);

	left2right() ;
	UpdateData(FALSE);
}

void CAddESStationDLG::OnKillfocusEDITlonS() 
{
	UpdateData();
	double S=atof(m_lonS);
//	S=min(59.999,max(S,0));
	S=min(59.9,max(S,0));
	CString str;
	str.Format("%0.1f",S);	m_lonS=str;
	int k=m_lonU.GetCurSel();
	double abs_lon_deg = (atof(m_lonD)+atof(m_lonM)/60.0+S/3600.0);
	abs_lon_deg = min(max(abs_lon_deg,0.0),180.0);
	m_STlon_deg=( (k==0) ? 1.0:-1.0  ) * abs_lon_deg;

	CString strLon;
	strLon.Format("%0.6f",m_STlon_deg);
	m_STlon_deg = atof(strLon);

	left2right() ;
	UpdateData(FALSE);	
}

void CAddESStationDLG::OnSelchangelatU() 
{
	UpdateData();
	int k=m_latU.GetCurSel();
	m_STlat_deg=( (k==0) ? 1.0:-1.0  )*(atof(m_latD)+atof(m_latM)/60.0+atof(m_latS)/3600.0);

	CString strLat;
	strLat.Format("%0.6f",m_STlat_deg);
	m_STlat_deg = atof(strLat);

	UpdateData(FALSE);	
}

void CAddESStationDLG::OnSelchangelonU() 
{
	UpdateData();
	int k=m_lonU.GetCurSel();
	m_STlon_deg=( (k==0) ? 1.0:-1.0  )*(atof(m_lonD)+atof(m_lonM)/60.0+atof(m_lonS)/3600.0);

	CString strLon;
	strLon.Format("%0.6f",m_STlon_deg);
	m_STlon_deg = atof(strLon);

	UpdateData(FALSE);	
}

void CAddESStationDLG::OnKillfocusEDITlatST() 
{
	UpdateData();
	m_STlat_deg = min(max(m_STlat_deg,-90.0),90.0);
	left2right() ;
	UpdateData(FALSE);	
}

void CAddESStationDLG::OnKillfocusEDITlonST() 
{
	UpdateData();
	m_STlon_deg = min(max(m_STlon_deg,-180.0),180.0);
	left2right() ;
	UpdateData(FALSE);	
}


long CAddESStationDLG::AddESSt(CString STname, int lonD, CString lonU, int lonM, int lonS, int latD, CString latU, int latM, int latS,CString SATname, double EL,double AZf,double AZt,double HstASL, double STlat_deg, double STlon_deg,CString type)
{
	////////////////// Country Code ////////////////////////////////////////
	double pi=4.0*atan(1.0);
	float RLON = (float)(STlon_deg*pi/180.0) ;
	float RLAT = (float)(STlat_deg*pi/180.0) ;

	CString Country("");
	GEOPLC(&RLON, &RLAT, (BYTE*)Country.GetBufferSetLength(3)) ;

	CString SQL1, LastntcID;
	CDatabase DB1;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	DB1.Open(_T(m_DB),false,false,_T("ODBC;"),false);
	CRecordset rs;
	rs.m_pDatabase=&DB1;

//e_stn
 	rs.Open(CRecordset::snapshot, _T("select max(ntc_id)+1 from e_stn"));
	rs.GetFieldValue((short)0,LastntcID);
	rs.Close();
	if(LastntcID.IsEmpty())
		LastntcID=_T("1");
	SQL1.Format(_T("SELECT %ld,-1,'%s','%s',%d,'%s',%d,%d,%d,'%s',%d,%d,'%s',%lf,%lf,%lf,%lf,%lf,%lf"), atol(LastntcID), STname, Country, lonD,lonU,lonM,lonS, latD,latU,latM,latS, SATname,EL,AZf,AZt,HstASL, STlon_deg, STlat_deg);
	SQL1=_T("INSERT INTO e_stn (ntc_id,LicID, stn_name,ctry,long_deg,long_ew,long_min,long_sec,lat_deg,lat_ns,lat_min,lat_sec,sat_name,elev_min,azm_fr,azm_to,ant_alt, long_dec, lat_dec) ")+SQL1;
	DB1.ExecuteSQL(SQL1);

//notice
	SQL1.Format(_T("SELECT %ld, '%s'"), atol(LastntcID), type); 
	SQL1=_T("INSERT INTO notice (ntc_id, ntc_type) ")+SQL1;
	DB1.ExecuteSQL(SQL1);

	DB1.Close();

	return atol(LastntcID);
}

void CAddESStationDLG::OnOK() 
{
	UpdateData();
	
	CString lonU,latU,type;
	m_lonU.GetWindowText(lonU);
	m_latU.GetWindowText(latU);
	
//	m_EStype.GetWindowText(type);
	type = _T("S");

	m_ntcID = AddESSt(	m_STname,
						atoi(m_lonD),
						lonU,
						atoi(m_lonM),
						atoi(m_lonS),
						atoi(m_latD),
						latU,
						atoi(m_latM),
						atoi(m_latS),
						m_nameSat,
						m_ElST,
						m_AzFrom,
						m_AzTo,
						m_STh_asl,
						m_STlat_deg,
						m_STlon_deg,
						type.Left(1)
									);	
	UpdateData(FALSE);	
	CDialog::OnOK();
}
