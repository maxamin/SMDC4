// PowerCalculatorDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "PowerCalculatorDLG.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPowerCalculatorDLG dialog


CPowerCalculatorDLG::CPowerCalculatorDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CPowerCalculatorDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPowerCalculatorDLG)
	m_f_MHz = 150.0;
	m_Gr = 0.0;
	m_Lc = 0.0;
	m_R = 50.0;
	m_DATAL = _T("0.35");
	m_DATAR = _T("0.35");
	//}}AFX_DATA_INIT
}


void CPowerCalculatorDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPowerCalculatorDLG)
	DDX_Control(pDX, IDC_COMBO_DATAR, m_COMBO_DATAR);
	DDX_Control(pDX, IDC_COMBO_DATAL, m_COMBO_DATAL);
	DDX_Text(pDX, IDC_EDIT_f_MHz, m_f_MHz);
	DDV_MinMaxDouble(pDX, m_f_MHz, 1.e-008, 100000000.);
	DDX_Text(pDX, IDC_EDIT_Gr, m_Gr);
	DDX_Text(pDX, IDC_EDIT_Lc, m_Lc);
	DDX_Text(pDX, IDC_EDIT_R, m_R);
	DDV_MinMaxDouble(pDX, m_R, 1.e-002, 10000000.);
	DDX_Text(pDX, IDC_EDIT_DATAL, m_DATAL);
	DDX_Text(pDX, IDC_EDIT_DATAR, m_DATAR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPowerCalculatorDLG, CDialog)
	//{{AFX_MSG_MAP(CPowerCalculatorDLG)
	ON_BN_CLICKED(IDC_BUTTONL, OnButtonl)
	ON_CBN_SELCHANGE(IDC_COMBO_DATAL, OnSelchangeComboDatal)
	ON_CBN_SELCHANGE(IDC_COMBO_DATAR, OnSelchangeComboDatar)
	ON_BN_CLICKED(IDC_BUTTONR, OnButtonr)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerCalculatorDLG message handlers

BOOL CPowerCalculatorDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	CString str = _T(0x0B5); //u

	UpdateData(true);
	m_COMBO_DATAL.AddString("uV");
	m_COMBO_DATAL.AddString("uW");
	m_COMBO_DATAL.AddString("mW");
	m_COMBO_DATAL.AddString("W");
	m_COMBO_DATAL.AddString("kW");
	m_COMBO_DATAL.AddString("dBW");
	m_COMBO_DATAL.AddString("dBm");
	m_COMBO_DATAL.AddString("dBuV/m");
	m_COMBO_DATAL.SetTopIndex(0);
	m_COMBO_DATAL.SetCurSel(0);	
	
	m_COMBO_DATAR.AddString("uV");
	m_COMBO_DATAR.AddString("uW");
	m_COMBO_DATAR.AddString("mW");
	m_COMBO_DATAR.AddString("W");
	m_COMBO_DATAR.AddString("kW");
	m_COMBO_DATAR.AddString("dBW");
	m_COMBO_DATAR.AddString("dBm");
	m_COMBO_DATAR.AddString("dBuV/m");
	m_COMBO_DATAR.SetTopIndex(0);
	m_COMBO_DATAR.SetCurSel(0);	

	m_ErText = "";

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CPowerCalculatorDLG::OnButtonl() 
{
	UpdateData(true);

	double f_MHz = m_f_MHz;
	double Lc = m_Lc;
	double Gr = m_Gr;
	double R = m_R;

	double DATAL = atof(m_DATAL);
	int DATALl = m_COMBO_DATAL.GetCurSel();
	int DATARl = m_COMBO_DATAR.GetCurSel();	

	double Su,Pw,Puw,Pmw,Pkw,PdBw,PdBm,EdBuvpm;
	CString dumy;

	if (((DATALl==0 || DATALl==1 || DATALl==2 || DATALl==3 || DATALl==4) && (DATAL<0.0)) ||
		((DATALl==0 || DATALl==1 || DATALl==2 || DATALl==3 || DATALl==4) && (DATAL==0.0) && (DATARl==5 || DATARl==6 || DATARl==7) ))
	{
//		GetDlgItem(IDC_STATIC_Erl)->ShowWindow(SW_SHOW);
		m_ErText = "!!!!!! Warning !!!!!! ----> Bad Value";
		m_DATAR = _T("!!!!!");
		Invalidate();
	}
	else
	{
//		GetDlgItem(IDC_STATIC_Erl)->ShowWindow(SW_HIDE);
		m_ErText = "";
		Invalidate();

		if (DATALl==DATARl)   
			m_DATAR = m_DATAL;
		else if  ((DATALl==0) && (DATARl==1))
		{
			Su = DATAL;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			Puw = 1000000.0*Pw;   //uW
			dumy.Format("%0.21f",Puw);	m_DATAR = dumy;
		}
		else if  ((DATALl==0) && (DATARl==2))
		{
			Su = DATAL;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			Pmw = 1000.0*Pw;   //mW
			dumy.Format("%0.21f",Pmw);	m_DATAR = dumy;
		}
		else if  ((DATALl==0) && (DATARl==3))
		{
			Su = DATAL;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			dumy.Format("%0.21f",Pw);	m_DATAR = dumy;
		}
		else if  ((DATALl==0) && (DATARl==4))
		{
			Su = DATAL;
			Pw = pow(Su*0.000001,2.0 )/R  ;
	        Pkw = Pw*0.001;
			dumy.Format("%0.21f",Pkw);	m_DATAR = dumy;
		}
		else if  ((DATALl==0) && (DATARl==5))
		{
			Su = DATAL;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			PdBw = 10.0*log10(Pw);         //dBW
			dumy.Format("%0.21f",PdBw);	m_DATAR = dumy;
		}
		else if  ((DATALl==0) && (DATARl==6))
		{
			Su = DATAL;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			PdBm = 10.0*log10(Pw*1000.0);    //dBm
			dumy.Format("%0.21f",PdBm);	m_DATAR = dumy;
		}
		else if  ((DATALl==0) && (DATARl==7))
		{
			Su = DATAL;
	        EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAR = dumy;
		}
	//------------------------------------------------------------ 

		else if  ((DATALl==1) && (DATARl==0))
		{
			Puw = DATAL;
			Su = sqrt(Puw*R*0.000001) * 1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAR = dumy;
		}
		else if  ((DATALl==1) && (DATARl==2))
		{
			Puw = DATAL;
	        Pmw = Puw * 0.001;
			dumy.Format("%0.21f",Pmw);	m_DATAR = dumy;
		}
		else if  ((DATALl==1) && (DATARl==3))
		{
			Puw = DATAL;
	        Pw = Puw * 0.000001;
			dumy.Format("%0.21f",Pw);	m_DATAR = dumy;
		}
		else if  ((DATALl==1) && (DATARl==4))
		{
			Puw = DATAL;
	        Pkw = Puw * 0.000000001;
			dumy.Format("%0.21f",Pkw);	m_DATAR = dumy;
		}
		else if  ((DATALl==1) && (DATARl==5))
		{
			Puw = DATAL;
	        Pw = Puw * 0.000001;
			PdBw = 10.0 * log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAR = dumy;
		}
		else if  ((DATALl==1) && (DATARl==6))
		{
			Puw = DATAL;
	        Pw = Puw * 0.000001;
	        PdBm = 10.0 * log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAR = dumy;
		}
		else if  ((DATALl==1) && (DATARl==7))
		{
			Puw = DATAL;
			Su = sqrt(Puw*R*0.000001) * 1000000.0;
	        EdBuvpm=20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAR = dumy;
		}
	//------------------------------------------------------------  
		else if  ((DATALl==2) && (DATARl==0))
		{
	        Pmw = DATAL;
			Su = sqrt(Pmw*R*0.001)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAR = dumy;
		}
		else if  ((DATALl==2) && (DATARl==1))
		{
	        Pmw = DATAL;
	        Puw = Pmw * 1000.0;
			dumy.Format("%0.21f",Puw);	m_DATAR = dumy;
		}
		else if  ((DATALl==2) && (DATARl==3))
		{
	        Pmw = DATAL;
	        Pw = Pmw * 0.001;
			dumy.Format("%0.21f",Pw);	m_DATAR = dumy;
		}
		else if  ((DATALl==2) && (DATARl==4))
		{
	        Pmw = DATAL;
	        Pkw = Pmw * 0.000001;
			dumy.Format("%0.21f",Pkw);	m_DATAR = dumy;
		}
		else if  ((DATALl==2) && (DATARl==5))
		{
	        Pmw = DATAL;
	        Pw = Pmw * 0.001;
			PdBw=10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAR = dumy;
		}
		else if  ((DATALl==2) && (DATARl==6))
		{
	        Pmw = DATAL;
	        Pw = Pmw * 0.001;
	        PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAR = dumy;
		}
		else if  ((DATALl==2) && (DATARl==7))
		{
	        Pmw = DATAL;
	        Pw = Pmw * 0.001;
	        Su = sqrt(Pw*R)*1000000.0;
			EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAR = dumy;
		}
	//------------------------------------------------------------   
		else if  ((DATALl==3) && (DATARl==0))
		{
	        Pw = DATAL;
			Su = sqrt(Pw*R*1.0)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAR = dumy;
		}
		else if  ((DATALl==3) && (DATARl==1))
		{
	        Pw = DATAL;
		    Puw = Pw * 1000000.0;
			dumy.Format("%0.21f",Puw);	m_DATAR = dumy;
		}
		else if  ((DATALl==3) && (DATARl==2))
		{
	        Pw = DATAL;
		    Pmw = Pw*1000.0;
			dumy.Format("%0.21f",Pmw);	m_DATAR = dumy;
		}
		else if  ((DATALl==3) && (DATARl==4))
		{
	        Pw = DATAL;
		    Pkw = Pw*0.001;
			dumy.Format("%0.21f",Pkw);	m_DATAR = dumy;
		}
		else if  ((DATALl==3) && (DATARl==5))
		{
	        Pw = DATAL;
		    PdBw = 10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAR = dumy;
		}
		else if  ((DATALl==3) && (DATARl==6))
		{
	        Pw = DATAL;
		    PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAR = dumy;
		}
		else if  ((DATALl==3) && (DATARl==7))
		{
	        Pw = DATAL;
		    Su = sqrt(Pw*R)*1000000.0;
			EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAR = dumy;
		}
	//------------------------------------------------------------ 
		else if  ((DATALl==4) && (DATARl==0))
		{
	        Pkw = DATAL;
		    Pw = Pkw*1000.0;
			Su=sqrt(Pw*R)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAR = dumy;
		}
		else if  ((DATALl==4) && (DATARl==1))
		{
	        Pkw = DATAL;
		    Puw = Pkw*1000000000.0;
			dumy.Format("%0.21f",Puw);	m_DATAR = dumy;
		}
		else if  ((DATALl==4) && (DATARl==2))
		{
	        Pkw = DATAL;
		    Pmw = Pkw*1000000.0;
			dumy.Format("%0.21f",Pmw);	m_DATAR = dumy;
		}
		else if  ((DATALl==4) && (DATARl==3))
		{
	        Pkw = DATAL;
		    Pw = Pkw*1000.0;
			dumy.Format("%0.21f",Pw);	m_DATAR = dumy;
		}
		else if  ((DATALl==4) && (DATARl==5))
		{
	        Pkw = DATAL;
		    Pw = Pkw*1000.0;
			PdBw = 10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAR = dumy;
		}
		else if  ((DATALl==4) && (DATARl==6))
		{
	        Pkw = DATAL;
		    Pw = Pkw*1000.0;
			PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAR = dumy;
		}
		else if  ((DATALl==4) && (DATARl==7))
		{
	        Pkw = DATAL;
		    Pw = Pkw*1000.0;
			Su = sqrt(Pw*R)*1000000.0;
			EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAR = dumy;
		}
	//------------------------------------------------------------  
		else if  ((DATALl==5) && (DATARl==0))
		{
	        PdBw = DATAL;
		    Pw = pow(10.0,(PdBw/10.0));
			Su = sqrt(Pw*R*1.0)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAR = dumy;
		}
		else if  ((DATALl==5) && (DATARl==1))
		{
	        PdBw = DATAL;
		    Pw = pow(10.0,(PdBw/10.0));
			Puw = Pw*1000000.0;
			dumy.Format("%0.21f",Puw);	m_DATAR = dumy;
		}
		else if  ((DATALl==5) && (DATARl==2))
		{
	        PdBw = DATAL;
		    Pw = pow(10.0,(PdBw/10.0));
	        Pmw = Pw*1000.0;
			dumy.Format("%0.21f",Pmw);	m_DATAR = dumy;
		}
		else if  ((DATALl==5) && (DATARl==3))
		{
	        PdBw = DATAL;
		    Pw = pow(10.0,(PdBw/10.0));
			dumy.Format("%0.21f",Pw);	m_DATAR = dumy;
		}
		else if  ((DATALl==5) && (DATARl==4))
		{
	        PdBw = DATAL;
		    Pw = pow(10.0,(PdBw/10.0));
	        Pkw = Pw*0.001;
			dumy.Format("%0.21f",Pkw);	m_DATAR = dumy;
		}
		else if  ((DATALl==5) && (DATARl==6))
		{
	        PdBw = DATAL;
		    Pw = pow(10.0,(PdBw/10.0));
	        PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAR = dumy;
		}
		else if  ((DATALl==5) && (DATARl==7))
		{
	        PdBw = DATAL;
		    Pw = pow(10.0,(PdBw/10.0));
	        Su = sqrt(Pw*R)*1000000.0;
		    EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAR = dumy;
		}
	//------------------------------------------------------------
		else if  ((DATALl==6) && (DATARl==0))
		{
	        PdBm = DATAL;
		    Pw = 0.001*pow(10.0,(PdBm/10.0));
			Su=sqrt(Pw*R)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAR = dumy;
		}
		else if  ((DATALl==6) && (DATARl==1))
		{
	        PdBm = DATAL;
		    Puw = 1000.0*pow(10.0,(PdBm/10.0));
			dumy.Format("%0.21f",Puw);	m_DATAR = dumy;
		}
		else if  ((DATALl==6) && (DATARl==2))
		{
	        PdBm = DATAL;
		    Pmw = pow(10.0,(PdBm/10.0));
			dumy.Format("%0.21f",Pmw);	m_DATAR = dumy;
		}
		else if  ((DATALl==6) && (DATARl==3))
		{
	        PdBm = DATAL;
		    Pw = 0.001*pow(10.0,(PdBm/10.0));
			dumy.Format("%0.21f",Pw);	m_DATAR = dumy;
		}
		else if  ((DATALl==6) && (DATARl==4))
		{
	        PdBm = DATAL;
		    Pkw = 0.000001*pow(10.0,(PdBm/10.0));
			dumy.Format("%0.21f",Pkw);	m_DATAR = dumy;
		}
		else if  ((DATALl==6) && (DATARl==5))
		{
	        PdBm = DATAL;
		    Pw = 0.001*pow(10.0,(PdBm/10.0));
			PdBw = 10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAR = dumy;
		}
		else if  ((DATALl==6) && (DATARl==7))
		{
	        PdBm = DATAL;
		    Pw = 0.001*pow(10.0,(PdBm/10.0));
			Su = sqrt(Pw*R)*1000000.0;
			EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAR = dumy;
		}
	//------------------------------------------------------------   
		else if  ((DATALl==7) && (DATARl==0))
		{
	        EdBuvpm = DATAL;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
			dumy.Format("%0.21f",Su);	m_DATAR = dumy;
		}
		else if  ((DATALl==7) && (DATARl==1))
		{
	        EdBuvpm = DATAL;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
		    Puw = 1000000.0*Pw;   
			dumy.Format("%0.21f",Puw);	m_DATAR = dumy;
		}
		else if  ((DATALl==7) && (DATARl==2))
		{
	        EdBuvpm = DATAL;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
	        Pmw = 1000.0*Pw;   //mW
			dumy.Format("%0.21f",Pmw);	m_DATAR = dumy;
		}
		else if  ((DATALl==7) && (DATARl==3))
		{
	        EdBuvpm = DATAL;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
			dumy.Format("%0.21f",Pw);	m_DATAR = dumy;
		}
		else if  ((DATALl==7) && (DATARl==4))
		{
	        EdBuvpm = DATAL;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pkw = 0.001*(pow((Su*0.000001),2.0)/R);
			dumy.Format("%0.21f",Pkw);	m_DATAR = dumy;
		}
		else if  ((DATALl==7) && (DATARl==5))
		{
	        EdBuvpm = DATAL;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
			PdBw = 10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAR = dumy;
		}
		else if  ((DATALl==7) && (DATARl==6))
		{
	        EdBuvpm = DATAL;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
			PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAR = dumy;
		}
	}
	UpdateData(false);
}

void CPowerCalculatorDLG::OnButtonr() 
{
	UpdateData(true);

	double f_MHz = m_f_MHz;
	double Lc = m_Lc;
	double Gr = m_Gr;
	double R = m_R;

	double DATAR = atof(m_DATAR);
	int DATALl = m_COMBO_DATAL.GetCurSel();
	int DATARl = m_COMBO_DATAR.GetCurSel();	

	double Su,Pw,Puw,Pmw,Pkw,PdBw,PdBm,EdBuvpm;
	CString dumy;

	if (((DATARl==0 || DATARl==1 || DATARl==2 || DATARl==3 || DATARl==4) && (DATAR<0.0)) ||
		((DATARl==0 || DATARl==1 || DATARl==2 || DATARl==3 || DATARl==4) && (DATAR==0.0) && (DATALl==5 || DATALl==6 || DATALl==7) ))
	{
//		GetDlgItem(IDC_STATIC_Erl)->ShowWindow(SW_SHOW);
		m_ErText = "!!!!!! Warning !!!!!! ----> Bad Value";
		m_DATAL = _T("!!!!!");
		Invalidate();
	}
	else
	{
//		GetDlgItem(IDC_STATIC_Erl)->ShowWindow(SW_HIDE);
		m_ErText = "";
		Invalidate();

		if (DATARl==DATALl)   
			m_DATAL = m_DATAR;
		else if  ((DATARl==0) && (DATALl==1))
		{
			Su = DATAR;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			Puw = 1000000.0*Pw;   //uW
			dumy.Format("%0.21f",Puw);	m_DATAL = dumy;
		}
		else if  ((DATARl==0) && (DATALl==2))
		{
			Su = DATAR;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			Pmw = 1000.0*Pw;   //mW
			dumy.Format("%0.21f",Pmw);	m_DATAL = dumy;
		}
		else if  ((DATARl==0) && (DATALl==3))
		{
			Su = DATAR;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			dumy.Format("%0.21f",Pw);	m_DATAL = dumy;
		}
		else if  ((DATARl==0) && (DATALl==4))
		{
			Su = DATAR;
			Pw = pow(Su*0.000001,2.0 )/R  ;
	        Pkw = Pw*0.001;
			dumy.Format("%0.21f",Pkw);	m_DATAL = dumy;
		}
		else if  ((DATARl==0) && (DATALl==5))
		{
			Su = DATAR;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			PdBw = 10.0*log10(Pw);         //dBW
			dumy.Format("%0.21f",PdBw);	m_DATAL = dumy;
		}
		else if  ((DATARl==0) && (DATALl==6))
		{
			Su = DATAR;
			Pw = pow(Su*0.000001,2.0 )/R  ;
			PdBm = 10.0*log10(Pw*1000.0);    //dBm
			dumy.Format("%0.21f",PdBm);	m_DATAL = dumy;
		}
		else if  ((DATARl==0) && (DATALl==7))
		{
			Su = DATAR;
	        EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAL = dumy;
		}
	//------------------------------------------------------------ 

		else if  ((DATARl==1) && (DATALl==0))
		{
			Puw = DATAR;
			Su = sqrt(Puw*R*0.000001) * 1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAL = dumy;
		}
		else if  ((DATARl==1) && (DATALl==2))
		{
			Puw = DATAR;
	        Pmw = Puw * 0.001;
			dumy.Format("%0.21f",Pmw);	m_DATAL = dumy;
		}
		else if  ((DATARl==1) && (DATALl==3))
		{
			Puw = DATAR;
	        Pw = Puw * 0.000001;
			dumy.Format("%0.21f",Pw);	m_DATAL = dumy;
		}
		else if  ((DATARl==1) && (DATALl==4))
		{
			Puw = DATAR;
	        Pkw = Puw * 0.000000001;
			dumy.Format("%0.21f",Pkw);	m_DATAL = dumy;
		}
		else if  ((DATARl==1) && (DATALl==5))
		{
			Puw = DATAR;
	        Pw = Puw * 0.000001;
			PdBw = 10.0 * log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAL = dumy;
		}
		else if  ((DATARl==1) && (DATALl==6))
		{
			Puw = DATAR;
	        Pw = Puw * 0.000001;
	        PdBm = 10.0 * log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAL = dumy;
		}
		else if  ((DATARl==1) && (DATALl==7))
		{
			Puw = DATAR;
			Su = sqrt(Puw*R*0.000001) * 1000000.0;
	        EdBuvpm=20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAL = dumy;
		}
	//------------------------------------------------------------  
		else if  ((DATARl==2) && (DATALl==0))
		{
	        Pmw = DATAR;
			Su = sqrt(Pmw*R*0.001)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAL = dumy;
		}
		else if  ((DATARl==2) && (DATALl==1))
		{
	        Pmw = DATAR;
	        Puw = Pmw * 1000.0;
			dumy.Format("%0.21f",Puw);	m_DATAL = dumy;
		}
		else if  ((DATARl==2) && (DATALl==3))
		{
	        Pmw = DATAR;
	        Pw = Pmw * 0.001;
			dumy.Format("%0.21f",Pw);	m_DATAL = dumy;
		}
		else if  ((DATARl==2) && (DATALl==4))
		{
	        Pmw = DATAR;
	        Pkw = Pmw * 0.000001;
			dumy.Format("%0.21f",Pkw);	m_DATAL = dumy;
		}
		else if  ((DATARl==2) && (DATALl==5))
		{
	        Pmw = DATAR;
	        Pw = Pmw * 0.001;
			PdBw=10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAL = dumy;
		}
		else if  ((DATARl==2) && (DATALl==6))
		{
	        Pmw = DATAR;
	        Pw = Pmw * 0.001;
	        PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAL = dumy;
		}
		else if  ((DATARl==2) && (DATALl==7))
		{
	        Pmw = DATAR;
	        Pw = Pmw * 0.001;
	        Su = sqrt(Pw*R)*1000000.0;
			EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAL = dumy;
		}
	//------------------------------------------------------------   
		else if  ((DATARl==3) && (DATALl==0))
		{
	        Pw = DATAR;
			Su = sqrt(Pw*R*1.0)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAL = dumy;
		}
		else if  ((DATARl==3) && (DATALl==1))
		{
	        Pw = DATAR;
		    Puw = Pw * 1000000.0;
			dumy.Format("%0.21f",Puw);	m_DATAL = dumy;
		}
		else if  ((DATARl==3) && (DATALl==2))
		{
	        Pw = DATAR;
		    Pmw = Pw*1000.0;
			dumy.Format("%0.21f",Pmw);	m_DATAL = dumy;
		}
		else if  ((DATARl==3) && (DATALl==4))
		{
	        Pw = DATAR;
		    Pkw = Pw*0.001;
			dumy.Format("%0.21f",Pkw);	m_DATAL = dumy;
		}
		else if  ((DATARl==3) && (DATALl==5))
		{
	        Pw = DATAR;
		    PdBw = 10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAL = dumy;
		}
		else if  ((DATARl==3) && (DATALl==6))
		{
	        Pw = DATAR;
		    PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAL = dumy;
		}
		else if  ((DATARl==3) && (DATALl==7))
		{
	        Pw = DATAR;
		    Su = sqrt(Pw*R)*1000000.0;
			EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAL = dumy;
		}
	//------------------------------------------------------------ 
		else if  ((DATARl==4) && (DATALl==0))
		{
	        Pkw = DATAR;
		    Pw = Pkw*1000.0;
			Su=sqrt(Pw*R)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAL = dumy;
		}
		else if  ((DATARl==4) && (DATALl==1))
		{
	        Pkw = DATAR;
		    Puw = Pkw*1000000000.0;
			dumy.Format("%0.21f",Puw);	m_DATAL = dumy;
		}
		else if  ((DATARl==4) && (DATALl==2))
		{
	        Pkw = DATAR;
		    Pmw = Pkw*1000000.0;
			dumy.Format("%0.21f",Pmw);	m_DATAL = dumy;
		}
		else if  ((DATARl==4) && (DATALl==3))
		{
	        Pkw = DATAR;
		    Pw = Pkw*1000.0;
			dumy.Format("%0.21f",Pw);	m_DATAL = dumy;
		}
		else if  ((DATARl==4) && (DATALl==5))
		{
	        Pkw = DATAR;
		    Pw = Pkw*1000.0;
			PdBw = 10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAL = dumy;
		}
		else if  ((DATARl==4) && (DATALl==6))
		{
	        Pkw = DATAR;
		    Pw = Pkw*1000.0;
			PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAL = dumy;
		}
		else if  ((DATARl==4) && (DATALl==7))
		{
	        Pkw = DATAR;
		    Pw = Pkw*1000.0;
			Su = sqrt(Pw*R)*1000000.0;
			EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAL = dumy;
		}
	//------------------------------------------------------------  
		else if  ((DATARl==5) && (DATALl==0))
		{
	        PdBw = DATAR;
		    Pw = pow(10.0,(PdBw/10.0));
			Su = sqrt(Pw*R*1.0)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAL = dumy;
		}
		else if  ((DATARl==5) && (DATALl==1))
		{
	        PdBw = DATAR;
		    Pw = pow(10.0,(PdBw/10.0));
			Puw = Pw*1000000.0;
			dumy.Format("%0.21f",Puw);	m_DATAL = dumy;
		}
		else if  ((DATARl==5) && (DATALl==2))
		{
	        PdBw = DATAR;
		    Pw = pow(10.0,(PdBw/10.0));
	        Pmw = Pw*1000.0;
			dumy.Format("%0.21f",Pmw);	m_DATAL = dumy;
		}
		else if  ((DATARl==5) && (DATALl==3))
		{
	        PdBw = DATAR;
		    Pw = pow(10.0,(PdBw/10.0));
			dumy.Format("%0.21f",Pw);	m_DATAL = dumy;
		}
		else if  ((DATARl==5) && (DATALl==4))
		{
	        PdBw = DATAR;
		    Pw = pow(10.0,(PdBw/10.0));
	        Pkw = Pw*0.001;
			dumy.Format("%0.21f",Pkw);	m_DATAL = dumy;
		}
		else if  ((DATARl==5) && (DATALl==6))
		{
	        PdBw = DATAR;
		    Pw = pow(10.0,(PdBw/10.0));
	        PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAL = dumy;
		}
		else if  ((DATARl==5) && (DATALl==7))
		{
	        PdBw = DATAR;
		    Pw = pow(10.0,(PdBw/10.0));
	        Su = sqrt(Pw*R)*1000000.0;
		    EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAL = dumy;
		}
	//------------------------------------------------------------
		else if  ((DATARl==6) && (DATALl==0))
		{
	        PdBm = DATAR;
		    Pw = 0.001*pow(10.0,(PdBm/10.0));
			Su=sqrt(Pw*R)*1000000.0;
			dumy.Format("%0.21f",Su);	m_DATAL = dumy;
		}
		else if  ((DATARl==6) && (DATALl==1))
		{
	        PdBm = DATAR;
		    Puw = 1000.0*pow(10.0,(PdBm/10.0));
			dumy.Format("%0.21f",Puw);	m_DATAL = dumy;
		}
		else if  ((DATARl==6) && (DATALl==2))
		{
	        PdBm = DATAR;
		    Pmw = pow(10.0,(PdBm/10.0));
			dumy.Format("%0.21f",Pmw);	m_DATAL = dumy;
		}
		else if  ((DATARl==6) && (DATALl==3))
		{
	        PdBm = DATAR;
		    Pw = 0.001*pow(10.0,(PdBm/10.0));
			dumy.Format("%0.21f",Pw);	m_DATAL = dumy;
		}
		else if  ((DATARl==6) && (DATALl==4))
		{
	        PdBm = DATAR;
		    Pkw = 0.000001*pow(10.0,(PdBm/10.0));
			dumy.Format("%0.21f",Pkw);	m_DATAL = dumy;
		}
		else if  ((DATARl==6) && (DATALl==5))
		{
	        PdBm = DATAR;
		    Pw = 0.001*pow(10.0,(PdBm/10.0));
			PdBw = 10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAL = dumy;
		}
		else if  ((DATARl==6) && (DATALl==7))
		{
	        PdBm = DATAR;
		    Pw = 0.001*pow(10.0,(PdBm/10.0));
			Su = sqrt(Pw*R)*1000000.0;
			EdBuvpm = 20.0*log10(f_MHz)+20.0*log10(Su)+Lc-Gr-10.0*log10(R)-12.787;  //  dBuV/m
			dumy.Format("%0.21f",EdBuvpm);	m_DATAL = dumy;
		}
	//------------------------------------------------------------   
		else if  ((DATARl==7) && (DATALl==0))
		{
	        EdBuvpm = DATAR;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
			dumy.Format("%0.21f",Su);	m_DATAL = dumy;
		}
		else if  ((DATARl==7) && (DATALl==1))
		{
	        EdBuvpm = DATAR;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
		    Puw = 1000000.0*Pw;   
			dumy.Format("%0.21f",Puw);	m_DATAL = dumy;
		}
		else if  ((DATARl==7) && (DATALl==2))
		{
	        EdBuvpm = DATAR;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
	        Pmw = 1000.0*Pw;   //mW
			dumy.Format("%0.21f",Pmw);	m_DATAL = dumy;
		}
		else if  ((DATARl==7) && (DATALl==3))
		{
	        EdBuvpm = DATAR;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
			dumy.Format("%0.21f",Pw);	m_DATAL = dumy;
		}
		else if  ((DATARl==7) && (DATALl==4))
		{
	        EdBuvpm = DATAR;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pkw = 0.001*(pow((Su*0.000001),2.0)/R);
			dumy.Format("%0.21f",Pkw);	m_DATAL = dumy;
		}
		else if  ((DATARl==7) && (DATALl==5))
		{
	        EdBuvpm = DATAR;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
			PdBw = 10.0*log10(Pw);
			dumy.Format("%0.21f",PdBw);	m_DATAL = dumy;
		}
		else if  ((DATARl==7) && (DATALl==6))
		{
	        EdBuvpm = DATAR;
		    Su = pow(10.0,((EdBuvpm-Lc+Gr+10.0*log10(R)+12.787)/20.0))/f_MHz;
	        Pw = pow((Su*0.000001),2.0)/R;
			PdBm = 10.0*log10(Pw*1000.0);
			dumy.Format("%0.21f",PdBm);	m_DATAL = dumy;
		}

	}
	UpdateData(false);
}


void CPowerCalculatorDLG::OnSelchangeComboDatal() 
{
	int DATALl = m_COMBO_DATAL.GetCurSel();
	int DATARl = m_COMBO_DATAR.GetCurSel();	

	if ( (DATALl==7 && DATARl!=7) || (DATALl!=7 && DATARl==7) )
	{
		GetDlgItem(IDC_EDIT_f_MHz)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_f_MHz)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Gr)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_Gr)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Lc)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_Lc)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_EDIT_f_MHz)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_f_MHz)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Gr)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_Gr)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Lc)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_Lc)->ShowWindow(SW_HIDE);
	}

	if ( (DATALl==0 && DATARl!=0) || (DATALl!=0 && DATARl==0) )
	{
		GetDlgItem(IDC_EDIT_R)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_R)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_EDIT_R)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_R)->ShowWindow(SW_HIDE);
	}

}
void CPowerCalculatorDLG::OnSelchangeComboDatar() 
{
	OnSelchangeComboDatal();
}

void CPowerCalculatorDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	int x = rect.left;
	int y = rect.bottom;

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(200,0,0));
	dc.TextOut(x+20,y-30,m_ErText);
	
	// Do not call CDialog::OnPaint() for painting messages
}

