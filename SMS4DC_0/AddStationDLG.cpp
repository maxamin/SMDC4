// AddStationDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "AddStationDLG.h"

#include "ANTpatternDLG.h"
#include <afxdb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddStationDLG dialog


CAddStationDLG::CAddStationDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAddStationDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddStationDLG)
	m_STname = _T("");
	m_STlat_deg = 0.0;
	m_STlon_deg = 0.0;
	m_Antenna = _T("DEFAULT");
	m_Azimuth = 0.0;
	m_BWh = 360.0;
	m_BWv = 360.0;
	m_Elevation = 0.0;
	m_TXfreq = 0.0;
	m_ANTgain = 0.0;
	m_STh_agl = 0.0;
	m_IDst = 0;
	m_Polarization = _T("V");
	m_Power_eirp = 10.0;
	m_latD = _T("");
	m_latM = _T("");
	m_latS = _T("");
	m_lonD = _T("");
	m_lonM = _T("");
	m_lonS = _T("");
	m_InserLoss = 3.0;
	m_RxSens = 0.35;
	m_STTP = _T("Fx");
	m_Srv = 1;
	m_Emission = _T("8K50F3E--");
	m_STh_asl = 0.0;
	//}}AFX_DATA_INIT
}


void CAddStationDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddStationDLG)
	DDX_Control(pDX, IDC_COMBO_STTP, m_ListSTTP);
	DDX_Control(pDX, IDC_COMBO_Srv, m_ListSrv);
	DDX_Control(pDX, IDC_lonU, m_lonU);
	DDX_Control(pDX, IDC_latU, m_latU);
	DDX_Text(pDX, IDC_EDIT_nameST, m_STname);
	DDX_Text(pDX, IDC_EDIT_latST, m_STlat_deg);
	DDX_Text(pDX, IDC_EDIT_lonST, m_STlon_deg);
	DDX_Text(pDX, IDC_EDIT_AntST, m_Antenna);
	DDX_Text(pDX, IDC_EDIT_AzST, m_Azimuth);
	DDX_Text(pDX, IDC_EDIT_BmwHST, m_BWh);
	DDX_Text(pDX, IDC_EDIT_BmwVST, m_BWv);
	DDX_Text(pDX, IDC_EDIT_ElST, m_Elevation);
	DDX_Text(pDX, IDC_EDIT_FrqST, m_TXfreq);
	DDX_Text(pDX, IDC_EDIT_GainST, m_ANTgain);
	DDX_Text(pDX, IDC_EDIT_HaglST, m_STh_agl);
	DDX_Text(pDX, IDC_EDIT_IDST, m_IDst);
	DDX_Text(pDX, IDC_EDIT_PolST, m_Polarization);
	DDX_Text(pDX, IDC_EDIT_PtGtST, m_Power_eirp);
	DDV_MinMaxDouble(pDX, m_Power_eirp, 1.e-006, 10000000000.);
	DDX_Text(pDX, IDC_EDIT_latD, m_latD);
	DDX_Text(pDX, IDC_EDIT_latM, m_latM);
	DDX_Text(pDX, IDC_EDIT_latS, m_latS);
	DDX_Text(pDX, IDC_EDIT_lonD, m_lonD);
	DDX_Text(pDX, IDC_EDIT_lonM, m_lonM);
	DDX_Text(pDX, IDC_EDIT_lonS, m_lonS);
	DDX_Text(pDX, IDC_EDIT_InserLoss, m_InserLoss);
	DDX_Text(pDX, IDC_EDIT_RxSens, m_RxSens);
	DDX_Text(pDX, IDC_EDIT_STTP, m_STTP);
	DDX_Text(pDX, IDC_EDIT_Srv, m_Srv);
	DDX_Text(pDX, IDC_EDIT_Emission, m_Emission);
	DDX_Text(pDX, IDC_EDIT_HaslST, m_STh_asl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddStationDLG, CDialog)
	//{{AFX_MSG_MAP(CAddStationDLG)
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
	ON_BN_CLICKED(IDC_Assign_Antenna, OnAssignAntenna)
	ON_BN_CLICKED(IDC_Show_Pattern, OnShowPattern)
	ON_CBN_SELCHANGE(IDC_COMBO_Srv, OnSelchangeCOMBOSrv)
	ON_CBN_SELCHANGE(IDC_COMBO_STTP, OnSelchangeComboSttp)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddStationDLG message handlers

BOOL CAddStationDLG::OnInitDialog() 
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
	left2right();

	m_antfile =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Antenna\\ant_DEFAULT.ant");
//	m_antfile = "ant_DEFAULT.ant";

	CDatabase DB;

	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	DB.Open(_T(m_DB),false,false,_T("ODBC;"),false);

	CRecordset m_rs;
	CDBVariant TempVar;
	CString m_Tbl;
	CString F1,F2;
	
	if     (m_Lang == "En")	m_iLang = 1;		//97/12/24
	else if(m_Lang == "Fr")	m_iLang = 2;
	else if(m_Lang == "Es")	m_iLang = 3;
	else if(m_Lang == "Ch")	m_iLang = 4;
	else if(m_Lang == "Ar")	m_iLang = 5;
	else if(m_Lang == "Ru")	m_iLang = 6;

	m_Tbl=_T("select * from SrvType where active=yes");
	m_rs.m_pDatabase=&DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((short)0,F1);
		m_rs.GetFieldValue((short)m_iLang,F2);	//97/12/24
		m_ListSrv.AddString(F1+" - "+F2);
		m_rs.MoveNext();
	}
	m_rs.Close();

	m_Tbl=_T("select * from StClass");
	m_rs.Open( CRecordset::snapshot, m_Tbl);
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((short)0,F1);
		m_rs.GetFieldValue((short)m_iLang,F2);		//97/12/24
		m_ListSTTP.AddString(F1+" - "+F2);
		m_rs.MoveNext();
	}
	m_rs.Close();
	DB.Close();

	m_ListSrv.SetCurSel(0);
	m_ListSTTP.SetCurSel(35);


//98/04/12
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));		
	lf.lfHeight  = 14;					
	lf.lfCharSet = DEFAULT_CHARSET;			
	strcpy(lf.lfFaceName, "Arial");
	VERIFY(m_font.CreateFontIndirect(&lf));  
	((CEdit*)GetDlgItem(IDC_EDIT_nameST))->SetFont(&m_font);


	UpdateData(false);
	
	OnSelchangeCOMBOSrv();

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}
//98/04/12
void CAddStationDLG::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_font.DeleteObject();
}


void CAddStationDLG::left2right() 
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

void CAddStationDLG::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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

void CAddStationDLG::OnKillfocusEDITlatD() 
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

void CAddStationDLG::OnKillfocusEDITlatM() 
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

void CAddStationDLG::OnKillfocusEDITlatS() 
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

void CAddStationDLG::OnKillfocusEDITlonD() 
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

void CAddStationDLG::OnKillfocusEDITlonM() 
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

void CAddStationDLG::OnKillfocusEDITlonS() 
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

void CAddStationDLG::OnSelchangelatU() 
{
	UpdateData();
	int k=m_latU.GetCurSel();
	m_STlat_deg=( (k==0) ? 1.0:-1.0  )*(atof(m_latD)+atof(m_latM)/60.0+atof(m_latS)/3600.0);

	CString strLat;
	strLat.Format("%0.6f",m_STlat_deg);
	m_STlat_deg = atof(strLat);

	UpdateData(FALSE);
}

void CAddStationDLG::OnSelchangelonU() 
{
	UpdateData();
	int k=m_lonU.GetCurSel();
	m_STlon_deg=( (k==0) ? 1.0:-1.0  )*(atof(m_lonD)+atof(m_lonM)/60.0+atof(m_lonS)/3600.0);

	CString strLon;
	strLon.Format("%0.6f",m_STlon_deg);
	m_STlon_deg = atof(strLon);

	UpdateData(FALSE);
}

void CAddStationDLG::OnKillfocusEDITlatST() 
{
	UpdateData();
	m_STlat_deg = min(max(m_STlat_deg,-90.0),90.0);
	left2right() ;
	UpdateData(FALSE);
}

void CAddStationDLG::OnKillfocusEDITlonST() 
{
	UpdateData();
	m_STlon_deg = min(max(m_STlon_deg,-180.0),180.0);
	left2right() ;
	UpdateData(FALSE);	
}

void CAddStationDLG::OnAssignAntenna() 
{
//	char strFilter[] = { "Ant Files (*.ant)|*.ant|All Files (*.*)|*.*||"};
	CString strFilter =  _Z("Ant Files") + " (*.ant)|*.ant|" + _Z("All Files") + " (*.*)|*.*||";

	CFileDialog FileDLG(TRUE, ".ant", NULL, 0, strFilter);

	if (FileDLG.DoModal() == IDOK)
	{
		m_antfile=FileDLG.GetPathName();
		UpdateData();
		ReadAntData(m_antfile) ;
		UpdateData(FALSE);
	}		
}
void CAddStationDLG::ReadAntData(CString antfile) 
{
	FILE *fid;
	fid=fopen(antfile,"rt");
	char Name [20],
		 Gain_dBi [20],
		 BeamWidth_H [20],
		 BeamWidth_V [20],
		 Frq_Lo [20],
		 Frq_Hi [20],
		 Frq_unit [20],
		 Polarization [20],
		 dum[20];
	fscanf( fid, "%s %s", dum,Name);
	fscanf( fid, "%s %s", dum,Gain_dBi);
	fscanf( fid, "%s %s", dum,BeamWidth_H);
	fscanf( fid, "%s %s", dum,BeamWidth_V);
	fscanf( fid, "%s %s", dum,Frq_Lo);
	fscanf( fid, "%s %s", dum,Frq_Hi);
	fscanf( fid, "%s %s", dum,Frq_unit);
	fscanf( fid, "%s %s", dum,Polarization);
	fscanf( fid, "%s", dum);
	fclose(fid);
	m_Antenna = Name;
	m_ANTgain = atof(Gain_dBi);;
	m_BWh = atof(BeamWidth_H);
	m_BWv = atof(BeamWidth_V);
	m_Polarization = Polarization;
}

void CAddStationDLG::OnShowPattern() 
{
	CANTpatternDLG patdlg;
	patdlg.m_antfile = m_antfile;
	patdlg.DoModal();
}

void CAddStationDLG::OnSelchangeCOMBOSrv() 
{
	UpdateData();
	CString str,srv;
	m_ListSrv.GetWindowText(str);
	srv=str.Left(2);
	srv.TrimRight(_T(" "));
	//m_Srv = atoi(str.Left(1));


	m_ListSTTP.ResetContent();
	CDatabase DB;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	DB.Open(_T(m_DB),false,false,_T("ODBC;"),false);

	CRecordset m_rs;
	CDBVariant TempVar;
	CString m_Tbl;
	CString F1,F2;

	m_Tbl=_T("select * from StClass where stsrv='"+srv+"'");
	m_rs.m_pDatabase=&DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);
	while(1)
	{
		if(m_rs.IsEOF()) break;
		m_rs.GetFieldValue((short)0,F1);
		m_rs.GetFieldValue((short)m_iLang,F2);	//97/12/24
		m_ListSTTP.AddString(F1+" - "+F2);
		m_rs.MoveNext();
	}
	m_rs.Close();
	DB.Close();
	m_ListSTTP.SetCurSel(0);

	UpdateData(FALSE);
	OnSelchangeComboSttp();
}

void CAddStationDLG::OnSelchangeComboSttp() 
{
	UpdateData();
	CString str;
	m_ListSTTP.GetWindowText(str);
	m_STTP = str.Left(2);
	UpdateData(FALSE);
}

