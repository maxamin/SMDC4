// Fassign2DLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Fassign2DLG.h"
#include <afxdb.h>

#include <math.h>
#include "NFDmobile_Functions.h"
#include "TxRxFiltersSet.h"
#include "MainFrm.h"


extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFassign2DLG dialog


CFassign2DLG::CFassign2DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CFassign2DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFassign2DLG)
	m_STname = _T("");
	m_STLatLon = _T("");
	m_Imax = 0.0;
	m_SRV = _T("");
	m_SRV0 = 0;
	m_SChannel = _T("");
	m_STfrq = 0.0;
	m_IntC = 0;
	m_TotalC = 0;
	m_STemission = _T("");
	//}}AFX_DATA_INIT
}


void CFassign2DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFassign2DLG)
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_GRID1);
	DDX_Control(pDX, IDC_MSFLEXGRID2, m_GRID2);
	DDX_Text(pDX, IDC_EDIT_STname, m_STname);
	DDX_Text(pDX, IDC_EDIT_STLatLon, m_STLatLon);
	DDX_Text(pDX, IDC_EDIT_Imax, m_Imax);
	DDX_Text(pDX, IDC_EDIT_Srv, m_SRV);
	DDX_Text(pDX, IDC_EDIT_Srv0, m_SRV0);
	DDX_Text(pDX, IDC_EDIT_Schannel, m_SChannel);
	DDX_Text(pDX, IDC_EDIT_STfrq, m_STfrq);
	DDX_Text(pDX, IDC_EDIT_IntC, m_IntC);
	DDX_Text(pDX, IDC_EDIT_TotalC, m_TotalC);
	DDX_Text(pDX, IDC_EDIT_Emission, m_STemission);
	DDV_MaxChars(pDX, m_STemission, 9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFassign2DLG, CDialog)
	//{{AFX_MSG_MAP(CFassign2DLG)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFassign2DLG message handlers

BOOL CFassign2DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ID	= new long[4000][200];
	m_numID = new long[4000];

	m_GRID1.SetCols(8);
	m_GRID1.SetColWidth(0,400);
	m_GRID1.SetColWidth(1,1100);
	m_GRID1.SetColWidth(2,1100);
	m_GRID1.SetColWidth(3,900);
	m_GRID1.SetColWidth(4,1200);
	m_GRID1.SetColWidth(5,1100);
	m_GRID1.SetColWidth(6,1100);
	m_GRID1.SetColWidth(7,1200);

	m_GRID1.SetTextMatrix(0,0,_Z("No."));
	m_GRID1.SetTextMatrix(0,1,"Fn");
	m_GRID1.SetTextMatrix(0,2,"F'n");
	m_GRID1.SetTextMatrix(0,3,_Z("BandWidth"));
	m_GRID1.SetTextMatrix(0,4,_Z("Num of Stations"));

	m_GRID1.SetTextMatrix(0,5,_Z("PlanID"));
	m_GRID1.SetTextMatrix(0,6,_Z("Srv Priority"));
	m_GRID1.SetTextMatrix(0,7,_Z("Comment"));

	m_GRID1.SetColAlignment(4,4);
	m_GRID1.SetColAlignment(1,2);
	m_GRID1.SetColAlignment(2,2);

	m_GRID2.SetCols(10);
	m_GRID2.SetRows(1);
	m_GRID2.SetColWidth(0,400);
	m_GRID2.SetColWidth(1,500);
	m_GRID2.SetColWidth(6,700);
	m_GRID2.SetColWidth(7,600);
	m_GRID2.SetColWidth(8,600);
	m_GRID2.SetColWidth(9,600);
	m_GRID2.SetTextMatrix(0,0,_Z("No."));
	m_GRID2.SetTextMatrix(0,1,"ID");
	m_GRID2.SetTextMatrix(0,2,_Z("Name")+"(2)");

	m_GRID2.SetTextMatrix(0,3,_Z("Service"));

	m_GRID2.SetTextMatrix(0,4,_Z("Frequency"));
	m_GRID2.SetTextMatrix(0,5,_Z("Coordinates"));
	m_GRID2.SetTextMatrix(0,6,_Z("Dist_km"));
	m_GRID2.SetTextMatrix(0,7,"E1_2");
	m_GRID2.SetTextMatrix(0,8,"E2_1");
	m_GRID2.SetTextMatrix(0,9,"dE1_2");
	m_GRID2.SetColWidth(5,1700);

	long UNR = 72 ;
	WDBUNIT(&UNR) ;

	CString ss;

	float lonRAD, latRAD;
	double pi = 4.0*atan(1.0);
	latRAD = (float)(m_STLat*pi/180.0);
	lonRAD = (float)(m_STLon*pi/180.0);
	unsigned char COORD[15];
	CRADDG4( &lonRAD, &latRAD, COORD );
	ss = COORD;		ss = ss.Left(15);
	m_STLatLon = ss.Left(8) + "  " +ss.Right(7);

	CString SRV;
	if		(m_SRV0 == 1)	{m_SRV = _T("Fixed");			SRV = _T("Fx");}
	else if (m_SRV0 == 2)	{m_SRV = _T("Land Mobile");		SRV = _T("LM");}
	else if (m_SRV0 == 3)	{m_SRV = _T("Broadcasting");	SRV = _T("BC");}

	CDatabase m_mydb;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		CRecordset m_rs;
		CString	m_Tbl;
	
		//Query FrequencyPlan
//		CString str1 = _T(" [ SELECT DISTINCT Fplan_IRegular.ID, Fplan_Reqular.ChannelNum AS Channels, Fplan_IRegular.ChannelNo AS No, Fplan_Reqular.PlanID, Fplan_Reqular.Region, Fplan_Reqular.Srv, IIf(Priority=1,\'Primary\',\'Secondary\') AS SrvPriority, Fplan_Type.Type, Fplan_IRegular.Fn, Fplan_IRegular.FnP, Fplan_IRegular.BandWidth, Fplan_Reqular.Comment ");
		CString str1 = _T(" [ SELECT DISTINCT Fplan_IRegular.ID, Fplan_Reqular.ChannelNum AS Channels, Fplan_IRegular.ChannelNo AS No, Fplan_Reqular.PlanID, Fplan_Reqular.Region, Fplan_Reqular.Srv, IIf(Priority=1,\'Primary\',\'Secondary\') AS SrvPriority, Fplan_Type.TypeEn, Fplan_IRegular.Fn, Fplan_IRegular.FnP, Fplan_IRegular.BandWidth, Fplan_Reqular.Comment ");
		CString str2 = _T(" FROM (Fplan_Type INNER JOIN Fplan_Reqular ON Fplan_Type.ID = Fplan_Reqular.PlanType) INNER JOIN Fplan_IRegular ON Fplan_Reqular.ID = Fplan_IRegular.AssignmentID ]. as FrequencyPlan ");
		CString qFrequencyPlan = str1+str2;
		m_Tbl.Format(_T("SELECT * FROM %s WHERE (((Fn)>=%f And (Fn)<=%f And (Srv)=\'%s\')) ORDER BY Fn;") , qFrequencyPlan , m_Fmin,m_Fmax,SRV);
		
//		m_Tbl.Format(_T("SELECT * FROM FrequencyPlan WHERE (((Fn)>=%f And (Fn)<=%f And (Srv)=\'%s\')) ORDER BY Fn;") , m_Fmin,m_Fmax,SRV);
		
		m_rs.m_pDatabase=&m_mydb;
		m_rs.Open( CRecordset::snapshot, m_Tbl);

		long k = 0 , kI = 0;
		while(!m_rs.IsEOF())
		{
			m_rs.MoveNext();
			k++;
		}
		m_GRID1.SetRows(k+1);
		m_TotalC = k;
		if(k>0)
		{
			m_rs.MoveFirst();
			CString str;
			double Fn;
			long ID[1000];

			int progress_num=0;
			CString progress_str, progress_char = _T("I");
			progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
			PeekAndPump();
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

			for (int i=0;i<k;i++)
			{
				str.Format("%d",i+1);						m_GRID1.SetTextMatrix(i+1,0,str);
				m_rs.GetFieldValue("Fn", ss);	Fn = atof(ss);
				str.Format("%f",Fn);						m_GRID1.SetTextMatrix(i+1,1,ss);

				m_rs.GetFieldValue("FnP", str);
				if(atof(str)==0)
					str=_T("");
				m_GRID1.SetTextMatrix(i+1,2,str);

				m_rs.GetFieldValue("BandWidth", str);		m_GRID1.SetTextMatrix(i+1,3,str);
				m_rs.GetFieldValue("PlanID", str);			m_GRID1.SetTextMatrix(i+1,5,str);
				m_rs.GetFieldValue("SrvPriority", str);		m_GRID1.SetTextMatrix(i+1,6,str);
				m_rs.GetFieldValue("Comment", str);			m_GRID1.SetTextMatrix(i+1,7,str);

				m_numID[i] = FindStation(Fn,m_Df/1000.0,ID) ;
				str.Format("%d",m_numID[i]);	m_GRID1.SetTextMatrix(i+1,4,str);
				if(m_numID[i]>0)
				{
					m_GRID1.SetRow(i+1);
					for(int b1=1;b1<8;b1++)
					{
						m_GRID1.SetCol(b1);
						m_GRID1.SetCellBackColor(RGB(255,255,150));
					}

					kI++;
					for(int j=0;j<m_numID[i];j++)
						m_ID[i][j] = ID[j];
				}
				m_rs.MoveNext();

				progress_char = str_rep("I",(int)((++progress_num)*50.0/((double)(k))) );
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(double)(k)),progress_char);
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
			}
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, "");
		}
		m_IntC = kI;
		m_rs.Close();

		CRecordset m_rs1;
//		m_Tbl.Format(_T("SELECT * FROM FrequencyPlan WHERE (((FnP)>=%f And (FnP)<=%f And (Srv)=\'%s\')) ORDER BY FnP;") , m_Fmin,m_Fmax,SRV);
		m_Tbl.Format(_T("SELECT * FROM %s WHERE (((FnP)>=%f And (FnP)<=%f And (Srv)=\'%s\')) ORDER BY FnP;") , qFrequencyPlan , m_Fmin,m_Fmax,SRV);
		
		m_rs1.m_pDatabase=&m_mydb;
		m_rs1.Open( CRecordset::snapshot, m_Tbl);

		long k1 = 0 , kI1 = 0;
		while(!m_rs1.IsEOF())
		{
			m_rs1.MoveNext();
			k1++;
		}
		m_GRID1.SetRows(k1+k+1);
		m_TotalC = k1+k;

		if(k1>0)
		{
			m_rs1.MoveFirst();
			CString str;
			double FnP;
			long ID[1000];

			int progress_num=0;
			CString progress_str, progress_char = _T("I");
			progress_str.Format("  %02d%%"+_Z(" complete")+" %s",0,_T("............."));
			PeekAndPump();
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);

			for (int i=k;i<(k1+k);i++)
			{
				str.Format("%d",i+1);						m_GRID1.SetTextMatrix(i+1,0,str);
				m_rs1.GetFieldValue("FnP", ss);		FnP = atof(ss);

				str.Format("%f",FnP);						m_GRID1.SetTextMatrix(i+1,1,ss);
				m_rs1.GetFieldValue("Fn", str);				m_GRID1.SetTextMatrix(i+1,2,str);
				m_rs1.GetFieldValue("BandWidth", str);		m_GRID1.SetTextMatrix(i+1,3,str);
				m_rs1.GetFieldValue("PlanID", str);			m_GRID1.SetTextMatrix(i+1,5,str);
				m_rs1.GetFieldValue("SrvPriority", str);	m_GRID1.SetTextMatrix(i+1,6,str);
				m_rs1.GetFieldValue("Comment", str);		m_GRID1.SetTextMatrix(i+1,7,str);

				m_numID[i] = FindStation(FnP,m_Df/1000.0,ID) ;
				str.Format("%d",m_numID[i]);	m_GRID1.SetTextMatrix(i+1,4,str);
				if(m_numID[i]>0)
				{
					m_GRID1.SetRow(i+1);
					for(int b1=1;b1<8;b1++)
					{
						m_GRID1.SetCol(b1);
						m_GRID1.SetCellBackColor(RGB(255,255,150));
					}

					kI1++;
					for(int j=0;j<m_numID[i];j++)
						m_ID[i][j] = ID[j];
				}
				m_rs1.MoveNext();

				progress_char = str_rep("I",(int)((++progress_num)*50.0/((double)(k1))) );
				progress_str.Format("  %02d%%"+_Z(" complete")+" %s",(int)(100.0*progress_num/(double)(k1)),progress_char);
				PeekAndPump();
				((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, progress_str);
			}
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, "");
		}
		m_IntC = kI1+kI;

		m_rs1.Close();
	}
	m_mydb.Close();


	UpdateData(false);
	
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}



long CFassign2DLG::FindStation(double Fn,double Df,long *ID) 
{
	long m = 0 , k = 0;

	CDatabase m_mydb;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		CRecordset m_rs;
		CString	m_Tbl;
//		m_Tbl.Format(_T("SELECT * FROM STtable WHERE (((TXfreq)>=%f And (TXfreq)<=%f And (IDst)<>%ld)) ORDER BY TXfreq;") , Fn-Df,Fn+Df,m_STID);
		m_Tbl.Format(_T("SELECT * FROM %s WHERE (((TXfreq)>=%f And (TXfreq)<=%f And (IDst)<>%ld)) ORDER BY TXfreq;") , ((CSMS4DCApp *)AfxGetApp())->Query_STtable() , Fn-Df,Fn+Df,m_STID);

		m_rs.m_pDatabase=&m_mydb;
		m_rs.Open( CRecordset::snapshot, m_Tbl);

		while(!m_rs.IsEOF())
		{
			m_rs.MoveNext();
			k++;
		}
		if(k>0)
		{
			m_rs.MoveFirst();
			CString ss;
			float latRAD,lonRAD , lonRADst , latRADst , rng;
			double pi = 4.0*atan(1.0);

			for (int i=0;i<k;i++)
			{
				m_rs.GetFieldValue("STlat_deg", ss);	latRAD = (float)(atof(ss)*pi/180.0);
				m_rs.GetFieldValue("STlon_deg", ss);	lonRAD = (float)(atof(ss)*pi/180.0);

				lonRADst = (float)(m_STLon*pi/180.0);	latRADst = (float)(m_STLat*pi/180.0);
				GEODSTR( &lonRADst, &latRADst, &lonRAD, &latRAD, &rng);
				if(rng<=m_Rkm)
				{
					m_rs.GetFieldValue("IDst", ss);		ID[m] = atol(ss);
					m++;
				}
				m_rs.MoveNext();
			}
		}
		m_rs.Close();
	}
	m_mydb.Close();

	return m;
}

BEGIN_EVENTSINK_MAP(CFassign2DLG, CDialog)
    //{{AFX_EVENTSINK_MAP(CFassign2DLG)
	ON_EVENT(CFassign2DLG, IDC_MSFLEXGRID1, -601 /* DblClick */, OnDblClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CFassign2DLG::OnDblClickMsflexgrid1() 
{
	UpdateData();
	long i = m_GRID1.GetRow();
	long nn = m_numID[i-1];

	double STfrq , NFD1 = 0, NFD2 = 0;
	CString name , str,LatLon , Emission;
	double frq, Dist, PtGt,Ghv1 = 1 ,Ghv2 = 1 , E1_2 , E2_1;
	int srv;

	m_SChannel = m_GRID1.GetTextMatrix(i,1);		STfrq = atof(m_SChannel);
	m_SChannelR = m_GRID1.GetTextMatrix(i,2);
	m_GRID2.SetRows(nn+1);

	CNFDmobile_Functions NFDm;


	double LatRx,LonRx,AZ0Rx,EL0Rx,HaslRx,HaglRx;
	CString antfile , antRx;
	int Txf0[360] , Rxf0[360];
	double TxrH[360]  ,  TxrV[360] , RxrH[360]  ,  RxrV[360];
	double AZ0Tx,EL0Tx , fpi,el , re = (4.0/3.0)*6371000;
	double GhvRx,GhvTx,tpi ,fi,ti, pi = 4.0*atan(1.0);

	antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,m_STant);
	ReadAntennaData(antfile,Txf0,TxrH,TxrV) ;
	AZ0Tx  = (pi/180.0)*m_STaz0;
	EL0Tx  = (pi/180.0)*m_STel0;


	long mm = 0;
	if(nn>0)
	for(long k=0;k<nn;k++)
	{
		long ID = m_ID[i-1][k];

		FillGRID2(ID,&name,&frq,&LatLon,&Dist,&PtGt,&Emission,&srv,
			&LatRx,&LonRx,&AZ0Rx,&EL0Rx,&HaslRx,&HaglRx,&antRx) ;

		str.Format("%ld",k+1);		m_GRID2.SetTextMatrix(k+1,0,str);
		str.Format("%ld",ID);		m_GRID2.SetTextMatrix(k+1,1,str);
									m_GRID2.SetTextMatrix(k+1,2,name);

		if		(srv == 1)	str = _Z("Fixed");
		else if (srv == 2)	str = _Z("Land Mobile");
		else if (srv == 3)	str = _Z("Broadcasting");

									m_GRID2.SetTextMatrix(k+1,3,str);
		str.Format("%f",frq);		m_GRID2.SetTextMatrix(k+1,4,str);
									m_GRID2.SetTextMatrix(k+1,5,LatLon);
		str.Format("%0.1f",Dist);	m_GRID2.SetTextMatrix(k+1,6,str);

		if(Dist>0)
		{
			if((m_SRV0==1)||(m_SRV0==3))
			{
				NFD1 = NFD_Fixed(m_STID , ID , STfrq , frq , m_STname , name) ;
				NFD2 = NFD_Fixed(ID , m_STID , frq , STfrq , name , m_STname) ;
			}
			else if(m_SRV0==2)
			{
				NFD1 = NFDm.NFDmobile(Emission2NBW(m_STemission),Emission2NBW(Emission),fabs(STfrq-frq)*1000.0);
				NFD2 = NFDm.NFDmobile(Emission2NBW(Emission),Emission2NBW(m_STemission),fabs(STfrq-frq)*1000.0);
			}
	//		else 
	//		{
	//			if(STfrq == frq)	{NFD1 =  0;		NFD2 =  0;}
	//			else				{NFD1 = 40;		NFD2 = 40;}
	//		}

			/////////////////////Antenna Tx & Rx/////////////////////
			el = AZ_EL(m_STLat,m_STLon, LatRx,LonRx , m_STh_asl+m_STh_agl, HaslRx+HaglRx, re, &fpi) ;
			tpi = (pi/2.0) - el;
			fi = (180.0/pi)*atan2(sin(tpi)*sin(fpi-AZ0Tx),(cos(EL0Tx)*sin(tpi)*cos(fpi-AZ0Tx)+cos(tpi)*sin(EL0Tx)));
			ti = (180.0/pi)*acos(cos(tpi)*cos(EL0Tx)-sin(EL0Tx)*sin(tpi)*cos(fpi-AZ0Tx));
			if (fi<0.0)		fi = fi + 359.4;
			GhvTx = Interp2(Txf0,TxrH,fi,360) * Interp2(Txf0,TxrV,ti,360);
			GhvTx = 10.0*log10(GhvTx);

			antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,antRx);
			ReadAntennaData(antfile,Rxf0,RxrH,RxrV) ;
			AZ0Rx  = (pi/180.0)*AZ0Rx;
			EL0Rx  = (pi/180.0)*EL0Rx;
			el = AZ_EL(LatRx,LonRx ,m_STLat,m_STLon, HaslRx+HaglRx, m_STh_asl+m_STh_agl, re, &fpi) ;
			tpi = (pi/2.0) - el;
			fi = (180.0/pi)*atan2(sin(tpi)*sin(fpi-AZ0Rx),(cos(EL0Rx)*sin(tpi)*cos(fpi-AZ0Rx)+cos(tpi)*sin(EL0Rx)));
			ti = (180.0/pi)*acos(cos(tpi)*cos(EL0Rx)-sin(EL0Rx)*sin(tpi)*cos(fpi-AZ0Rx));
			if (fi<0.0)		fi = fi + 359.4;
			GhvRx = Interp2(Rxf0,RxrH,fi,360) * Interp2(Rxf0,RxrV,ti,360);
			GhvRx = 10.0*log10(GhvRx);
			/////////////////////////////////////////

			E1_2 = (sqrt(30.0*m_STptgt))/(1000.0*Dist);
			E1_2 = 120.0+20.0*(log10(E1_2)) - NFD1 + GhvTx + GhvRx;
			str.Format("%0.2f",E1_2);			m_GRID2.SetTextMatrix(k+1,7,str);

			E2_1 = (sqrt(30.0*PtGt))/(1000.0*Dist);
			E2_1 = 120.0+20.0*(log10(E2_1)) - NFD2 + GhvTx + GhvRx;
			str.Format("%0.2f",E2_1);			m_GRID2.SetTextMatrix(k+1,8,str);
			str.Format("%0.2f",E1_2-m_Imax);	m_GRID2.SetTextMatrix(k+1,9,str);


			m_GRID2.SetRow(k+1);	m_GRID2.SetCol(9);
			if((E1_2-m_Imax)>0)	{	m_GRID2.SetCellBackColor(RGB(255,150,150));	mm = 1;	}
			else					m_GRID2.SetCellBackColor(RGB(255,255,255));

		}//if Dist
		else
		{
			m_GRID2.SetTextMatrix(k+1,6,"");
			m_GRID2.SetTextMatrix(k+1,7,"");
			m_GRID2.SetTextMatrix(k+1,8,"");
			m_GRID2.SetRow(k+1);	m_GRID2.SetCol(8);
			m_GRID2.SetCellBackColor(RGB(255,255,255));
		}//else Dist

	}//for k nn

	m_GRID1.SetRow(i);
	for(int b1=1;b1<8;b1++)
	{
		m_GRID1.SetCol(b1);
		if(mm==1)	m_GRID1.SetCellBackColor(RGB(255,150,150));
		else		m_GRID1.SetCellBackColor(RGB(255,255,255));
	}
	UpdateData(false);
}



void CFassign2DLG::FillGRID2(long ID,CString * name,double *frq,CString *LatLon , double *Dist ,
							 double *PtGt,CString *Emission,int *Srv,double *Lat,double *Lon,
							 double *AZ ,double *EL ,double *Hasl ,double *Hagl,CString *ant) 
{
	CDatabase m_mydb;
	CRecordset m_rs;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	CString	m_Tbl;
//	m_Tbl.Format(_T("SELECT * FROM STtable WHERE (((IDst)=%ld));") , ID);
	m_Tbl.Format(_T("SELECT * FROM %s WHERE (((IDst)=%ld));") , ((CSMS4DCApp *)AfxGetApp())->Query_STtable() , ID);

	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		CString ss;
		double pi = 4.0*atan(1.0);
		float lonRAD, latRAD;
		m_rs.m_pDatabase=&m_mydb;
		m_rs.Open( CRecordset::snapshot, m_Tbl);

		m_rs.GetFieldValue("STname", ss);			*name = ss;
		m_rs.GetFieldValue("TXfreq", ss);			*frq = atof(ss);
		m_rs.GetFieldValue("STlat_deg", ss);		latRAD = (float)(atof(ss)*pi/180.0);	*Lat = atof(ss);
		m_rs.GetFieldValue("STlon_deg", ss);		lonRAD = (float)(atof(ss)*pi/180.0);	*Lon = atof(ss);
		m_rs.GetFieldValue("Power_eirp", ss);		*PtGt = atof(ss);
		m_rs.GetFieldValue("Emission", ss);			*Emission = ss;
		m_rs.GetFieldValue("Srv", ss);				*Srv = atoi(ss);
		m_rs.GetFieldValue("Azimuth", ss);			*AZ = atof(ss);
		m_rs.GetFieldValue("Elevation", ss);		*EL = atof(ss);
		m_rs.GetFieldValue("Sth_asl", ss);			*Hasl = atof(ss);
		m_rs.GetFieldValue("Sth_agl", ss);			*Hagl = atof(ss);
		m_rs.GetFieldValue("Antenna", ss);			*ant = ss;

		unsigned char COORD[15];
		CRADDG4( &lonRAD, &latRAD, COORD );
		ss = COORD;		ss = ss.Left(15);
		*LatLon = ss.Left(8) + "  " +ss.Right(7);

		float lonRADst = (float)(m_STLon*pi/180.0), latRADst = (float)(m_STLat*pi/180.0);
		float rng;
		GEODSTR( &lonRADst, &latRADst, &lonRAD, &latRAD, &rng);
		*Dist = rng;
	}
	m_rs.Close();
	m_mydb.Close();

}

double CFassign2DLG::Emission2NBW(CString Emission) 
{
	double NBW_kHz = 0;
	CString c , BWs = Emission.Left(4);
	BWs.MakeUpper();

	for(int i=0;i<4;i++)
	{
		c = BWs.Mid(i,1);
		if(c=="H")
		{
			BWs.Replace('H','.');
			NBW_kHz = (0.001)*atof(BWs);
			return NBW_kHz;
		}
		else if(c=="K")
		{
			BWs.Replace('K','.');
			NBW_kHz = atof(BWs);
			return NBW_kHz;
		}
		else if(c=="M")
		{
			BWs.Replace('M','.');
			NBW_kHz = (1000.0)*atof(BWs);
			return NBW_kHz;
		}
		else if(c=="G")
		{
			BWs.Replace('G','.');
			NBW_kHz = (1000000.0)*atof(BWs);
			return NBW_kHz;
		}
	}
	return NBW_kHz;
}


double CFassign2DLG::NFD_Fixed(long ID_Tx,long ID_Rx, double frq_Tx, double frq_Rx,CString name_Tx,CString name_Rx) 
{
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

		str.Format("SELECT * FROM RxFilters WHERE (((EqID)=%ld)) ORDER BY EqID;",ID_Rx);
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

				ft[i] = (ft[i] + frq_Tx)*1000000.0;
				fr[i] = (fr[i] + frq_Rx)*1000000.0;
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

		}// end if Rx Recoard set
		else
		{
			str.Format(_Z("\nRx Filter is not defined for the Receiver : %s.\t\t\n"),name_Rx);
			MessageBox(str,_Z("Warning!!!"),MB_ICONWARNING);
		}

	}// end if Tx Recoard set
	else
	{
		str.Format(_Z("\nTx Filter is not defined for the Transmitter : %s.\t\t\n"),name_Tx);
		MessageBox(str,_Z("Warning!!!"),MB_ICONWARNING);
	}

	return NFD;
}

double CFassign2DLG::MinValue(double *xi,int N) 
{
	double  xiMIN = xi[0];
	for (int i=1;i<N;i++)
		xiMIN = min(xiMIN,xi[i]);	
	return xiMIN;
}
double CFassign2DLG::MaxValue(double *xi,int N) 
{
	double  xiMAX = xi[0];
	for (int i=1;i<N;i++)
		xiMAX = max(xiMAX,xi[i]);	
	return xiMAX;
}
double CFassign2DLG::interwt(double *ft,double *at,int n,double f0) 
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
double CFassign2DLG::subsection(double a,double b,double fc) 
{
	double y;
	if (a==0)
        y = fc * pow(10.0,(-b/10.0));
	else
        y = ( pow(10.0,(-b/10.0)) )*( pow(10.0,(-a*fc/10.0)) - 1.0 )/(-a*log(10.0)/10.0);
	return y;
}

HBRUSH CFassign2DLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (  pWnd->GetDlgCtrlID() == IDC_EDIT_Schannel)
	{
		CFont font ;
        if (!(HFONT)font)
		{
            LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfHeight = 16;
			lf.lfWeight = FW_BOLD;
			strcpy(lf.lfFaceName , "Arial");
            font.CreateFontIndirect(&lf);
        }
        pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(0,0,200));
		font.DeleteObject();
	}
	return hbr;
}


double CFassign2DLG::AZ_EL(double latT , double lonT , double latR , double lonR, double HtASGL, double HrASGL, double re, double *AZrad) 
{
	double pi=4.0*atan(1.0);
	*AZrad = (pi/180.0)*Azimuth_Deg(latT , lonT , latR , lonR);
	double DIST = Distance_km(latT , lonT , latR , lonR);
	double Ht = HtASGL;
	double Hr = HrASGL;
	double ELrad = atan(((re+Hr)*cos(1000.0*DIST/re)-(re+Ht))/((re+Hr)*sin(1000.0*DIST/re)));
	return ELrad;
}
double CFassign2DLG::Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) 
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(lat1*pi/180.0),
			lon10 = (float)(lon1*pi/180.0),
			lat20 = (float)(lat2*pi/180.0),
			lon20 = (float)(lon2*pi/180.0),	RDIST, RAZIM;
	GEOPPDA( &lon10 ,&lat10, &lon20,&lat20, &RDIST, &RAZIM);
	return RAZIM;
}
double CFassign2DLG::Distance_km(double lat1,double lon1,double lat2,double lon2) 
{
	double pi=4.0*atan(1.0);
	float	lat10 = (float)(lat1*pi/180.0),
			lon10 = (float)(lon1*pi/180.0),
			lat20 = (float)(lat2*pi/180.0),
			lon20 = (float)(lon2*pi/180.0),	rng;
	GEODSTR( &lon10, &lat10, &lon20, &lat20, &rng);
	return (rng);
}

void CFassign2DLG::ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) 
{
	FILE *fid;
	if( (fid  = fopen(antfile,"rt")) != NULL )
	{
		char Name [20],
			 Gain_dBi [20],
			 BeamWidth_H [20],
			 BeamWidth_V [20],
			 Frq_Lo [20],
			 Frq_Hi [20],
			 Frq_unit [20],
			 Polarization [20],
			 dum[20];

		char Ang[20],PatH[20],PatV[20];

		fscanf( fid, "%s %s", dum,Name);
		fscanf( fid, "%s %s", dum,Gain_dBi);
		fscanf( fid, "%s %s", dum,BeamWidth_H);
		fscanf( fid, "%s %s", dum,BeamWidth_V);
		fscanf( fid, "%s %s", dum,Frq_Lo);
		fscanf( fid, "%s %s", dum,Frq_Hi);
		fscanf( fid, "%s %s", dum,Frq_unit);
		fscanf( fid, "%s %s", dum,Polarization);
		fscanf( fid, "%s", dum);

		double pi=4.0*atan(1.0);
		double rH1,rV1;
		for (int i=0;i<360;i++)
		{
			fscanf( fid, "%s %s %s", Ang,PatH,PatV);
			f0[i] = atoi(Ang);
			rH1 = atof(PatH);		rV1 = atof(PatV);
			rH1 = pow( 10.0 , (-rH1/10.0) );
			rV1 = pow( 10.0 , (-rV1/10.0) );
			rH[i]=rH1;		rV[i]=rV1;
		}
		fclose(fid);
	}
	else
	{
		CString str;
		str.Format(_Z("The Antenna name  [%s]  was not found!  \r\rThe Isotropic Antenna will be select."),antfile);
		MessageBox(str, _Z("Warning!!!"), MB_ICONWARNING | MB_OK);
		for (int i=0;i<360;i++)
		{
			f0[i] = i;		rH[i]=1.0;		rV[i]=1.0;
		}
	}
}
double CFassign2DLG::Interp2(int *D0,double *E0,double d,int num) 
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


CString CFassign2DLG::str_rep(CString str,int num)
{
	CString str1 = str;
	for(int i=0;i<num;i++)
		str1 = str1+str;
	return str1;
}
BOOL CFassign2DLG::PeekAndPump()
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

void CFassign2DLG::Del() 
{
	delete [] m_ID;
	delete [] m_numID;
}