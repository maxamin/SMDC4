// AntennaFormView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "AntennaFormView.h"
#include <math.h>

#include "Ant3DDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormView

IMPLEMENT_DYNCREATE(CAntennaFormView, CFormView)

CAntennaFormView::CAntennaFormView()
	: CFormView(CAntennaFormView::IDD)
{
	//{{AFX_DATA_INIT(CAntennaFormView)
	m_Ang = _T("000");
	m_AttnH = _T("0.000");
	m_AttnV = _T("0.000");
	m_Frq_Hi = 20000.0;
	m_Frq_Lo = 20.0;
	m_Frq_unit = _T("MHz");
	m_Gain_dBi = 0.0;
	m_Name = _T("DEFAULT");
	m_Polarization = _T("V");
	m_BeamWidth_H = 360.0;
	m_BeamWidth_V = 360.0;
	m_AllValue = 0.0;
	//}}AFX_DATA_INIT

	m_HV = true;
	m_ThickLines=1;
	m_5degreestick=1;
	m_1degreestick=false;
	m_1dbtick=false;
	m_fill=false;
	m_fillcolor=RGB(255,255,0);

	m_antfile =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Antenna\\ant_DEFAULT.ant");

	m_lbutton=false;
}

CAntennaFormView::~CAntennaFormView()
{
}

void CAntennaFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAntennaFormView)
	DDX_Control(pDX, IDC_LIST_Pattern, m_list);
	DDX_Text(pDX, IDC_EDIT_Angle, m_Ang);
	DDX_Text(pDX, IDC_EDIT_AttnH, m_AttnH);
	DDX_Text(pDX, IDC_EDIT_AttnV, m_AttnV);
	DDX_Text(pDX, IDC_EDIT_FHI, m_Frq_Hi);
	DDX_Text(pDX, IDC_EDIT_FLO, m_Frq_Lo);
	DDX_Text(pDX, IDC_EDIT_FU, m_Frq_unit);
	DDX_Text(pDX, IDC_EDIT_Gain, m_Gain_dBi);
	DDX_Text(pDX, IDC_EDIT_Name, m_Name);
	DDX_Text(pDX, IDC_EDIT_Pol, m_Polarization);
	DDX_Text(pDX, IDC_EDIT_bH, m_BeamWidth_H);
	DDX_Text(pDX, IDC_EDIT_bV, m_BeamWidth_V);
	DDX_Text(pDX, IDC_EDIT_AllValue, m_AllValue);
	DDV_MinMaxDouble(pDX, m_AllValue, 0., 99.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAntennaFormView, CFormView)
	//{{AFX_MSG_MAP(CAntennaFormView)
	ON_COMMAND(ID_OPTION_THICKLINES, OnOptionThicklines)
	ON_UPDATE_COMMAND_UI(ID_OPTION_THICKLINES, OnUpdateOptionThicklines)
	ON_COMMAND(ID_OPTION_5DEGREESTICK, OnOption5degreestick)
	ON_UPDATE_COMMAND_UI(ID_OPTION_5DEGREESTICK, OnUpdateOption5degreestick)
	ON_COMMAND(ID_OPTION_1DEGREESTICK, OnOption1degreestick)
	ON_UPDATE_COMMAND_UI(ID_OPTION_1DEGREESTICK, OnUpdateOption1degreestick)
	ON_COMMAND(ID_OPTION_1DBTICK, OnOption1dbtick)
	ON_UPDATE_COMMAND_UI(ID_OPTION_1DBTICK, OnUpdateOption1dbtick)
	ON_BN_CLICKED(IDC_Load, OnLoad)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_LBN_SELCHANGE(IDC_LIST_Pattern, OnSelchangeLISTPattern)
	ON_BN_CLICKED(IDC_Save, OnSave)
	ON_EN_CHANGE(IDC_EDIT_AttnH, OnChangeEDITAttnH)
	ON_EN_CHANGE(IDC_EDIT_AttnV, OnChangeEDITAttnV)
	ON_BN_CLICKED(IDC_Omni, OnOmni)
	ON_BN_CLICKED(IDC_Clear, OnClear)
	ON_BN_CLICKED(IDC_SetAll, OnSetAll)
	ON_COMMAND(ID_OPTION_FILLDIAGRAM, OnOptionFilldiagram)
	ON_UPDATE_COMMAND_UI(ID_OPTION_FILLDIAGRAM, OnUpdateOptionFilldiagram)
	ON_COMMAND(ID_OPTION_HORIZONTALPATTERN, OnOptionHorizontalpattern)
	ON_UPDATE_COMMAND_UI(ID_OPTION_HORIZONTALPATTERN, OnUpdateOptionHorizontalpattern)
	ON_COMMAND(ID_OPTION_VERTICALPATTERN, OnOptionVerticalpattern)
	ON_UPDATE_COMMAND_UI(ID_OPTION_VERTICALPATTERN, OnUpdateOptionVerticalpattern)
	ON_COMMAND(ID_OPTION_3DGRAPH, OnOption3dgraph)
	ON_BN_CLICKED(IDC_Hor, OnHor)
	ON_BN_CLICKED(IDC_Ver, OnVer)
	ON_BN_CLICKED(IDC_3D, On3d)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormView diagnostics

#ifdef _DEBUG
void CAntennaFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAntennaFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormView message handlers

void CAntennaFormView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	ReadData(m_antfile) ;
	CString str;
	for (int i=0;i<360;i++)
	{
		str.Format("%03d  %7.3f    %7.3f",m_Angle[i],m_PatternH[i],m_PatternV[i]);
		m_list.AddString(str);
	}
	m_list.SetCurSel(0);

	m_Xp=m_X;m_Yp=m_Y;

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE17);	//98/05/06
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog((CDialog *)this);
}

void CAntennaFormView::OnDraw(CDC* pDC) 
{
	CRect rect1;
	GetClientRect(&rect1);

	int AxesT1 = rect1.top;
	int AxesL1 = rect1.left;
	int AxesW1 = 748*rect1.Width()/1000;
	int AxesH1 = 948*rect1.Height()/1000;

	m_AxesL1 = AxesL1+6*AxesW1/100;
	m_AxesT1 = AxesT1+6*AxesH1/100;
	m_AxesW1 = AxesW1-3*AxesW1/100;
	m_AxesH1 = AxesH1-3*AxesH1/100;

	pDC->SetMapMode(MM_LOMETRIC);
	CRect rect;
///////////////////////////////////////
	if (pDC->IsPrinting())
		rect = m_rcPrintRect;
	else
		GetClientRect(&rect);
	pDC->DPtoLP(&rect);
///////////////////////////////////////
	double W = rect.Width()/1000.0;
	double H = rect.Height()/1000.0;
	
	int AxesT = rect.top;
	int AxesL = rect.left;
	int AxesW = 748*W;
	int AxesH = 948*H;

	m_AxesL = AxesL+6*AxesW/100;
	m_AxesT = AxesT+6*AxesH/100;
	m_AxesW = AxesW-3*AxesW/100;
	m_AxesH = AxesH-3*AxesH/100;

	double radius1x,radius1y;
	m_X		= (m_AxesL+m_AxesW)/2;
	radius1x = abs(m_AxesW-m_AxesL)/2;

	m_Y		= (m_AxesT+m_AxesH)/2;
	radius1y = abs(m_AxesH-m_AxesT)/2;
	m_radius = min(radius1x,radius1y);

	DrawPattern(pDC,m_HV);
	////////////////Pointer//////////////////////
	DrawEllipse(pDC,false,m_Xp-m_radius/50,m_Yp-m_radius/50,m_Xp+m_radius/50,m_Yp+m_radius/50,PS_SOLID,2,RGB(255,0,0),m_Xp,m_Yp,m_Xp,m_Yp);

	if (!(pDC->IsPrinting()))
	{
		////////////////////////////////////////////Controls///////////////////////////////////
		pDC->LPtoDP(&rect);
		W = rect.Width()/1000.0;
		H = rect.Height()/1000.0;
//		GetDlgItem(IDC_STATIC_Properties)	->MoveWindow( 780*W,   1*H, 210*W, 275*H , TRUE );
		GetDlgItem(IDC_STATIC_Properties)	->MoveWindow( 730*W,   1*H, 260*W, 275*H , TRUE );
		GetDlgItem(IDC_STATIC_name)			->MoveWindow( 785*W,  15*H, 200*W,  25*H , TRUE );
		GetDlgItem(IDC_EDIT_Name)			->MoveWindow( 785*W,  40*H, 200*W,  30*H , TRUE );
		GetDlgItem(IDC_STATIC_fband)		->MoveWindow( 785*W,  70*H, 200*W,  25*H , TRUE );
		GetDlgItem(IDC_EDIT_FLO)			->MoveWindow( 788*W,  95*H,  74*W,  30*H , TRUE );
		GetDlgItem(IDC_EDIT_FHI)			->MoveWindow( 862*W,  95*H,  74*W,  30*H , TRUE );
		GetDlgItem(IDC_EDIT_FU)				->MoveWindow( 936*W,  95*H,  50*W,  30*H , TRUE );
//		GetDlgItem(IDC_STATIC_BWH)			->MoveWindow( 788*W, 130*H, 120*W,  25*H , TRUE );
		GetDlgItem(IDC_STATIC_BWH)			->MoveWindow( 738*W, 130*H, 170*W,  25*H , TRUE );
		GetDlgItem(IDC_EDIT_bH)				->MoveWindow( 910*W, 130*H,  76*W,  30*H , TRUE );
//		GetDlgItem(IDC_STATIC_BWV)			->MoveWindow( 788*W, 165*H, 120*W,  25*H , TRUE );
		GetDlgItem(IDC_STATIC_BWV)			->MoveWindow( 738*W, 165*H, 170*W,  25*H , TRUE );
		GetDlgItem(IDC_EDIT_bV)				->MoveWindow( 910*W, 165*H,  76*W,  30*H , TRUE );
		GetDlgItem(IDC_STATIC_POL)			->MoveWindow( 788*W, 200*H,  76*W,  25*H , TRUE );
		GetDlgItem(IDC_EDIT_Pol)			->MoveWindow( 910*W, 200*H,  76*W,  30*H , TRUE );
		GetDlgItem(IDC_STATIC_Gain)			->MoveWindow( 788*W, 235*H,  76*W,  25*H , TRUE );
		GetDlgItem(IDC_EDIT_Gain)			->MoveWindow( 910*W, 235*H,  76*W,  30*H , TRUE );

		GetDlgItem(IDC_STATIC_Pdata)		->MoveWindow( 780*W, 275*H, 210*W, 525*H , TRUE );
		GetDlgItem(IDC_LIST_Pattern)		->MoveWindow( 785*W, 325*H, 200*W, 400*H , TRUE );
		GetDlgItem(IDC_STATIC_data)			->MoveWindow( 785*W, 725*H, 200*W,  65*H , TRUE );
		GetDlgItem(IDC_EDIT_Angle)			->MoveWindow( 790*W, 750*H,  40*W,  25*H , TRUE );
		GetDlgItem(IDC_EDIT_AttnH)			->MoveWindow( 830*W, 750*H,  60*W,  30*H , TRUE );
		GetDlgItem(IDC_EDIT_AttnV)			->MoveWindow( 890*W, 750*H,  60*W,  30*H , TRUE );

//		GetDlgItem(IDC_STATIC_load)			->MoveWindow( 780*W, 787*H, 210*W, 175*H , TRUE );
		GetDlgItem(IDC_STATIC_load)			->MoveWindow( 730*W, 787*H, 260*W, 175*H , TRUE );
		GetDlgItem(IDC_Hor)					->MoveWindow( 785*W, 807*H,  65*W,  30*H , TRUE );
		GetDlgItem(IDC_Ver)					->MoveWindow( 852*W, 807*H,  65*W,  30*H , TRUE );
		GetDlgItem(IDC_3D)					->MoveWindow( 920*W, 807*H,  64*W,  30*H , TRUE );
//		GetDlgItem(IDC_SetAll)				->MoveWindow( 785*W, 845*H, 120*W,  30*H , TRUE );
		GetDlgItem(IDC_SetAll)				->MoveWindow( 735*W, 845*H, 170*W,  30*H , TRUE );
		GetDlgItem(IDC_EDIT_AllValue)		->MoveWindow( 910*W, 845*H,  76*W,  30*H , TRUE );
		GetDlgItem(IDC_Omni)				->MoveWindow( 785*W, 880*H, 100*W,  35*H , TRUE );
		GetDlgItem(IDC_Clear)				->MoveWindow( 890*W, 880*H,  95*W,  35*H , TRUE );
		GetDlgItem(IDC_Load)				->MoveWindow( 785*W, 920*H, 100*W,  35*H , TRUE );
		GetDlgItem(IDC_Save)				->MoveWindow( 890*W, 920*H,  95*W,  35*H , TRUE );

		pDC->DPtoLP(&rect);
		W = rect.Width()/1000.0;
		H = rect.Height()/1000.0;
/*
		CString str;
		str.Format("%c/%c               %c                %c",_T(0x6A),_T(0x71),_T(0x6A),_T(0x71));
		DrawLable(pDC,794*W,300*H,str,44,RGB(0,0,200),"Symbol"); 
		str.Format("        Attn_E(   )  Attn_H(   )");
		DrawLable(pDC,794*W,300*H,str,42,RGB(0,0,0),"Arial");
*/
		CString str;	int s,x,y,L;	x = 794*W;		y = (300-5)*H;		s = 40;
		str.Format(_T("%c/%c "),_T(0x6A),_T(0x71));	L = DrawLable(pDC,x,y,str,s,RGB(0,0,200),"Symbol");x = x + L;
		str.Format(_Z("Attn_E"));					L = DrawLable(pDC,x,y,str,s-2,RGB(0,0,0),"Arial");x = x + L;
		str.Format(_T("("));						L = DrawLable(pDC,x,y,str,s-2,RGB(0,0,0),"Arial");x = x + L;
		str.Format(_T("%c"), _T(0x6A));				L = DrawLable(pDC,x,y,str,s,RGB(0,0,200),"Symbol");x = x + L;
		str.Format(_T(") "));						L = DrawLable(pDC,x,y,str,s-2,RGB(0,0,0),"Arial");x = x + L;
		str.Format(_Z("Attn_H"));					L = DrawLable(pDC,x,y,str,s-2,RGB(0,0,0),"Arial");x = x + L;
		str.Format(_T("("));						L = DrawLable(pDC,x,y,str,s-2,RGB(0,0,0),"Arial");x = x + L;
		str.Format(_T("%c"), _T(0x71));				L = DrawLable(pDC,x,y,str,s,RGB(0,0,200),"Symbol");x = x + L;
		str.Format(_T(")"));						L = DrawLable(pDC,x,y,str,s-2,RGB(0,0,0),"Arial"); 
	/*
		GetDlgItem(IDC_STATIC_Properties)	->MoveWindow( 248*W,   -1*H, 66*W,  -94*H , TRUE );
		GetDlgItem(IDC_STATIC_name)			->MoveWindow( 248*W,   -6*H, 66*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_Name)			->MoveWindow( 250*W,  -14*H, 62*W,  -10*H , TRUE );
		GetDlgItem(IDC_STATIC_fband)		->MoveWindow( 250*W,  -26*H, 62*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_FLO)			->MoveWindow( 250*W,  -34*H, 23*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_FHI)			->MoveWindow( 274*W,  -34*H, 23*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_FU)				->MoveWindow( 298*W,  -34*H, 14*W,  -10*H , TRUE );
		GetDlgItem(IDC_STATIC_BWH)			->MoveWindow( 250*W,  -48*H, 39*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_bH)				->MoveWindow( 290*W,  -48*H, 22*W,  -10*H , TRUE );
		GetDlgItem(IDC_STATIC_BWV)			->MoveWindow( 250*W,  -58*H, 39*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_bV)				->MoveWindow( 290*W,  -58*H, 22*W,  -10*H , TRUE );
		GetDlgItem(IDC_STATIC_POL)			->MoveWindow( 250*W,  -68*H, 39*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_Pol)			->MoveWindow( 290*W,  -68*H, 22*W,  -10*H , TRUE );
		GetDlgItem(IDC_STATIC_Gain)			->MoveWindow( 250*W,  -78*H, 39*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_Gain)			->MoveWindow( 290*W,  -78*H, 22*W,  -10*H , TRUE );

		GetDlgItem(IDC_STATIC_Pdata)		->MoveWindow( 248*W,  -95*H, 66*W, -150*H , TRUE );
		GetDlgItem(IDC_LIST_Pattern)		->MoveWindow( 254*W, -110*H, 55*W, -115*H , TRUE );
		GetDlgItem(IDC_STATIC_data)			->MoveWindow( 249*W, -223*H, 63*W,  -20*H , TRUE );
		GetDlgItem(IDC_EDIT_Angle)			->MoveWindow( 255*W, -232*H, 10*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_AttnH)			->MoveWindow( 265*W, -230*H, 20*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_AttnV)			->MoveWindow( 285*W, -230*H, 20*W,  -10*H , TRUE );

		GetDlgItem(IDC_STATIC_load)			->MoveWindow( 248*W, -242*H, 66*W,  -62*H , TRUE );
		GetDlgItem(IDC_Hor)					->MoveWindow( 249*W, -247*H, 20*W,  -10*H , TRUE );
		GetDlgItem(IDC_Ver)					->MoveWindow( 271*W, -247*H, 20*W,  -10*H , TRUE );
		GetDlgItem(IDC_3D)					->MoveWindow( 292*W, -247*H, 20*W,  -10*H , TRUE );
		GetDlgItem(IDC_SetAll)				->MoveWindow( 250*W, -262*H, 40*W,  -10*H , TRUE );
		GetDlgItem(IDC_EDIT_AllValue)		->MoveWindow( 291*W, -262*H, 20*W,  -10*H , TRUE );
		GetDlgItem(IDC_Omni)				->MoveWindow( 250*W, -274*H, 30*W,  -11*H , TRUE );
		GetDlgItem(IDC_Clear)				->MoveWindow( 282*W, -274*H, 30*W,  -11*H , TRUE );
		GetDlgItem(IDC_Load)				->MoveWindow( 250*W, -290*H, 30*W,  -11*H , TRUE );
		GetDlgItem(IDC_Save)				->MoveWindow( 282*W, -290*H, 30*W,  -11*H , TRUE );
	*/
	}

}

void CAntennaFormView::ReadData(CString antfile) 
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

	m_Name = Name;
	m_Gain_dBi = atof(Gain_dBi);
	m_BeamWidth_H = atof(BeamWidth_H);
	m_BeamWidth_V = atof(BeamWidth_V);
	m_Frq_Lo = atof(Frq_Lo);
	m_Frq_Hi = atof(Frq_Hi);
	m_Frq_unit = Frq_unit;
	m_Polarization = Polarization;

	for (int i=0;i<360;i++)
	{
		fscanf( fid, "%s %s %s", Ang,PatH,PatV);
		m_Angle[i] = atoi(Ang);
		m_PatternH[i] = atof(PatH);
		m_PatternV[i] = atof(PatV);
	}
	fclose(fid);
}


void CAntennaFormView::DrawPattern(CDC* pDC,BOOL HV) 
{
	CString str;
	double az,pi = 4.0*atan(1.0);
	int i,x,y, x01,y01,radius1;

	double step = m_radius/10.0;
	DrawEllipse(pDC,true,m_X-m_radius,m_Y-m_radius,m_X+m_radius,m_Y+m_radius);

//////////////////////////////Draw Diagram//////////////////////////////////////////////
	double a,r;
	CPoint pointH[361];
	for ( i=0;i<360;i++)
	{
		if (HV)
		{
			r = m_radius-(step/5.0)*min(50.0,m_PatternH[i]);
			a = ((double)(i))*pi/180.0;
		}
		else 
		{
			r = m_radius-(step/5.0)*min(50.0,m_PatternV[i]);
			a = ((double)(90-i))*pi/180.0;
		}
		x = int(m_X+r*sin(a));
		y = int(m_Y+r*cos(a));
		pointH[i]=CPoint(x,y);
	}
	pointH[360] = pointH[0];

	CPen pen(PS_SOLID,m_ThickLines,RGB(0,0,255));
	pDC->SelectObject(&pen);
	pDC->Polyline(pointH,361);

	if (m_fill)
	{
		CBrush brush(m_fillcolor);
		pDC->SelectObject(&brush);
		pDC->Polygon(pointH,361);
	}
//////////////////////////////////////////////////////////////////////////////////
	if(m_1dbtick)
	{
		for (int i=1;i<=50;i++)
		{
			radius1=int(m_radius-(step/5.0)*i);
			DrawEllipse(pDC,false,m_X-radius1,m_Y-radius1,m_X+radius1,m_Y+radius1,PS_DOT,1,RGB(0,255,0),m_X,m_Y,m_X,m_Y);
		}
	}
	if(m_1degreestick)
	{
		for ( i=0;i<36*10;i++)
		{
			az = ( i*10.0/10)*pi/180.0;
			x = int(m_X + m_radius*sin(az));
			y = int(m_Y + m_radius*cos(az));
			if ( (i!=0*10) && (i!=9*10) && (i!=18*10) && (i!=27*10) )
			{
				x01 = int(m_X + 4*step*sin(az));
				y01 = int(m_Y + 4*step*cos(az));
			}
			else
			{
				x01 = m_X;
				y01 = m_Y;
			}
			DrawLine(pDC,x01,y01,x,y,PS_DOT,1,RGB(0,255,0));
		}
	}
///////////////////////////////////////////////////////////////////////////////////////
	for ( i=1;i<=10;i++)
	{
		radius1 = int(m_radius-step*i);
		DrawEllipse(pDC,false,m_X-radius1,m_Y-radius1,m_X+radius1,m_Y+radius1,PS_SOLID,1,RGB(0,255,0),m_X,m_Y,m_X,m_Y);
	}

	for (i=0;i<36*m_5degreestick;i++)
	{
		az = (i*10.0/m_5degreestick)*pi/180.0;
		x = int(m_X + m_radius*sin(az));
		y = int(m_Y + m_radius*cos(az));
		if ( (i!=0*m_5degreestick) && (i!=9*m_5degreestick) && (i!=18*m_5degreestick) && (i!=27*m_5degreestick) )
		{
			x01 = int(m_X + step*sin(az));
			y01 = int(m_Y + step*cos(az));
		}
		else
		{
			x01 = m_X;
			y01 = m_Y;
		}
		DrawLine(pDC,x01,y01,x,y,PS_SOLID,1,RGB(0,255,0));
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER);
	for (i=0;i<36;i++)
	{
		az = (i*10.0)*pi/180.0;
		x = int(m_X + (105*m_radius/100)* sin(az));
		y = int(m_Y+3*m_radius/100 + (105*m_radius/100)* cos(az));
		if(HV==1)
			str.Format("%d",i*10);
		else
		{
			if (i<19)
				str.Format("%d",i*10);
			else
				str.Format("%d",-360+i*10);
		}
		DrawLable(pDC,x,y,str,46,RGB(0,0,0),"Arial"); 

	}
	pDC->SetTextAlign(TA_TOP);

	DrawLable(pDC,m_X,int(m_Y+m_radius-3*m_radius/50),"-3",46,RGB(0,0,0),"Arial"); 
	DrawLable(pDC,m_X,int(m_Y+m_radius-10*m_radius/50),"-10",46,RGB(0,0,0),"Arial"); 
	DrawLable(pDC,m_X,int(m_Y+m_radius-20*m_radius/50),"-20",46,RGB(0,0,0),"Arial"); 
	DrawLable(pDC,m_X,int(m_Y+m_radius-30*m_radius/50),"-30",46,RGB(0,0,0),"Arial"); 
	DrawLable(pDC,m_X,int(m_Y+m_radius-40*m_radius/50),"-40",46,RGB(0,0,0),"Arial"); 

	Draw3Angle(pDC,m_X,m_Y+m_radius+1*m_radius/50,
					m_X-1*m_radius/50,m_Y+m_radius-1*m_radius/50,
					m_X+1*m_radius/50,m_Y+m_radius-1*m_radius/50);

	radius1 = int(m_radius-3.0*step/5.0);
	DrawEllipse(pDC,false,m_X-radius1,m_Y-radius1,m_X+radius1,m_Y+radius1,PS_SOLID,4,RGB(0,0,0),m_X,m_Y,m_X,m_Y);
/*	
	if (HV)
		str.Format(" Antenna Horizontal Pattern (Azimuth Angle)");
	else
		str.Format(" Antenna Vertical Pattern (Elevation Angle)");
*/
	if (HV)	str.Format(_Z("Antenna E-plane Pattern"));
	else	str.Format(_Z("Antenna H-plane Pattern"));

	GetParent()->SetWindowText(str);
}


void CAntennaFormView::DrawEllipse(CDC* pDC,BOOL nMode,int x1,int y1,int x2,int y2,int nStyle,int nWidth,COLORREF pColor,int x3,int y3,int x4,int y4,COLORREF bColor) 
{
	CBrush brush(bColor);
	CBrush* OLDbrush = pDC->SelectObject(&brush);
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = pDC->SelectObject(&pen);

	if (nMode)
		pDC->Ellipse(x1,y1,x2,y2);
	else
		pDC->Arc(x1,y1,x2,y2,x3,y3,x4,y4);

	pDC->SelectObject(OLDbrush);
	pDC->SelectObject(OLDpen);
}

void CAntennaFormView::DrawLine(CDC* pDC,int x1,int y1,int x2,int y2,int nStyle,int nWidth,COLORREF pColor) 
{
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = pDC->SelectObject(&pen);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
	pDC->SelectObject(OLDpen);
}


void CAntennaFormView::Draw3Angle(CDC* pDC,int x1,int y1,int x2,int y2,int x3,int y3,int nStyle,int nWidth,COLORREF pColor,COLORREF bColor) 
{
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = pDC->SelectObject(&pen);

	CBrush brush(bColor);
	CBrush* OLDbrush = pDC->SelectObject(&brush);

	CPoint point[3];
	point[0]=CPoint(x1,y1);
	point[1]=CPoint(x2,y2);
	point[2]=CPoint(x3,y3);
	pDC->Polygon(point,3);

	pDC->SelectObject(OLDbrush);
	pDC->SelectObject(OLDpen);
}


int CAntennaFormView::DrawLable(CDC* pDC,int x,int y,CString str,int nSize,COLORREF nColor,CString nFontname) 
{
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(nColor);

	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       
	lf.lfHeight = nSize;                
	lf.lfWidth =0;
	lf.lfWeight = FW_NORMAL;
	strcpy(lf.lfFaceName, nFontname);        
	lf.lfEscapement=0;
	VERIFY(font.CreateFontIndirect(&lf));  
	CFont* def_font = pDC->SelectObject(&font);

	pDC->TextOut(x,y,str);
	CSize sz = pDC->GetTextExtent(str, str.GetLength());

	pDC->SelectObject(def_font);
	font.DeleteObject(); 
	return (sz.cx);
}


void CAntennaFormView::OnOptionThicklines() 
{
	m_ThickLines =  (m_ThickLines==1 ? 10 : 1);
	InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
}

void CAntennaFormView::OnUpdateOptionThicklines(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ThickLines!=1);
}

void CAntennaFormView::OnOption5degreestick() 
{
	m_5degreestick =  (m_5degreestick==1 ? 2 : 1);
	InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
}

void CAntennaFormView::OnUpdateOption5degreestick(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_5degreestick!=1);
}

void CAntennaFormView::OnOption1degreestick() 
{
	m_1degreestick =  (m_1degreestick ? false : true);
	InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
}

void CAntennaFormView::OnUpdateOption1degreestick(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_1degreestick);
}

void CAntennaFormView::OnOption1dbtick() 
{
	m_1dbtick =  (m_1dbtick ? false : true);
	InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
}

void CAntennaFormView::OnUpdateOption1dbtick(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_1dbtick);
}

void CAntennaFormView::OnLoad() 
{
//	char strFilter[] = { "Ant Files (*.ant)|*.ant|All Files (*.*)|*.*||"};
	CString strFilter =  _Z("Ant Files") + " (*.ant)|*.ant|" + _Z("All Files") + " (*.*)|*.*||";

	CFileDialog FileDLG(TRUE, ".ant", NULL, 0, strFilter);
	if (FileDLG.DoModal() == IDOK)
	{
		m_list.ResetContent();

		m_antfile=FileDLG.GetPathName();
		UpdateData();
		ReadData(m_antfile) ;
		UpdateData(false);

		CString str;
		for (int i=0;i<360;i++)
		{
			str.Format("%03d  %7.3f    %7.3f",m_Angle[i],m_PatternH[i],m_PatternV[i]);
			m_list.AddString(str);
		}
		Invalidate();
	}
}

void CAntennaFormView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_lbutton=true;
	if(m_lbutton)
	{
		double pi   = 4.0*atan(1.0);
		int x11 = m_AxesL+(point.x-m_AxesL1)*(m_AxesW-m_AxesL)/(m_AxesW1-m_AxesL1);
		int y11 = m_AxesT+(point.y-m_AxesT1)*(m_AxesH-m_AxesT)/(m_AxesH1-m_AxesT1);
		double rSin =  x11 - m_X;
		double rCos =  y11 - m_Y;

		double teta = (180.0/pi)*atan2(rSin,rCos);
		double rPix    = sqrt(rSin*rSin+rCos*rCos);

		if ( rPix <= (m_radius + 10.0*m_radius/400.0) )
		{
			UpdateData();
			double rdB = 50.0 * ( -1.0 + rPix/m_radius );
			rdB = max(min(rdB,0.0),-50.0);
			CString str;
			double teta1;
			int arg,ang;
			if(m_HV)
			{
				teta1 = teta;
				if (teta1<0)
					teta1 = 360.0 + teta1;
				teta1 = (teta1 == 360.0) ? 0.0 : teta1;
				arg = max(0,min(359,Round(teta1)));
				ang = arg;
				m_PatternH[arg] = -rdB;
				str.Format("%0.3f",-rdB);				m_AttnH = str;
				str.Format("%0.3f",m_PatternV[arg]);	m_AttnV = str;
			}
			else
			{
				teta1 = 90.0 - teta;
				if (teta1<0)
					teta1 = 360.0 + teta1;
				teta1 = (teta1 == 360.0) ? 0.0 : teta1;
				arg = max(0,min(359,Round(teta1)));
				ang = 90 - arg;
				m_PatternV[arg] = -rdB;
				str.Format("%0.3f",-rdB);				m_AttnV = str;
				str.Format("%0.3f",m_PatternH[arg]);	m_AttnH = str;
			}
			m_list.ResetContent();
			for (int i=0;i<360;i++)
			{
				str.Format("%03d  %7.3f    %7.3f",m_Angle[i],m_PatternH[i],m_PatternV[i]);
				m_list.AddString(str);
			}
			m_list.SetCurSel(arg);

			str.Format("%03d",arg);	m_Ang = str;
			//////////////////Pointer///////////////////////
			m_Xp = int(m_X + min(m_radius,rPix)*sin(ang*pi/180.0));
			m_Yp = int(m_Y + min(m_radius,rPix)*cos(ang*pi/180.0));
			/////////////////////////////////////////
			InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
			UpdateData(false);
		}
	}
	
	CFormView::OnLButtonDown(nFlags, point);
}

void CAntennaFormView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_lbutton=false;
	CFormView::OnLButtonUp(nFlags, point);
}

int CAntennaFormView::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);
}

void CAntennaFormView::OnSelchangeLISTPattern() 
{
	UpdateData();
	int i = m_list.GetCurSel();
	double rdBH = m_PatternH[i];
	double rdBV = m_PatternV[i];

	CString str;
	str.Format("%03d",i);		m_Ang = str;
	str.Format("%0.3f",rdBH);	m_AttnH = str;
	str.Format("%0.3f",rdBV);	m_AttnV = str;

	//////////////////Pointer///////////////////////
	double pi   = 4.0*atan(1.0), rPix;
	if(m_HV)
		rPix = m_radius*(1.0-rdBH/50.0);
	else
	{
		rPix = m_radius*(1.0-rdBV/50.0);
		i=90-i;
	}
	m_Xp = int(m_X + rPix*sin(i*pi/180.0));
	m_Yp = int(m_Y + rPix*cos(i*pi/180.0));

	InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
	/////////////////////////////////////////
	UpdateData(false);
}

void CAntennaFormView::OnSave() 
{
	UpdateData();
	m_Name.TrimLeft();	m_Name.TrimRight();	m_Name.Replace(' ','_');

	CString str;
	str.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,m_Name);

//	char strFilter[] = { "Ant Files (*.ant)|*.ant|All Files (*.*)|*.*||"};
	CString strFilter =  _Z("Ant Files") + " (*.ant)|*.ant|" + _Z("All Files") + " (*.*)|*.*||";

	CFileDialog FileDLG(FALSE, ".ant", str, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (FileDLG.DoModal() == IDOK)
	{
		m_antfile = FileDLG.GetPathName();

		str = FileDLG.GetFileName();
		int len = str.GetLength();
		m_Name = str.Mid(4,len-8);

		m_Name.TrimLeft();	m_Name.TrimRight();	m_Name.Replace(' ','_');
		int j = m_antfile.ReverseFind('\\');
		m_antfile = m_antfile.Left(j+1) + _T("ant_") + m_Name + _T(".ant");

		WriteToFile(m_antfile);	
		//////////////////////////
		m_list.ResetContent();
		ReadData(m_antfile) ;
		for (int i=0;i<360;i++)
		{
			str.Format("%03d  %7.3f    %7.3f",m_Angle[i],m_PatternH[i],m_PatternV[i]);
			m_list.AddString(str);
		}
		InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
	}
	UpdateData(false);
}


int CAntennaFormView::WriteToFile(CString FileName)
{
	FILE *fp=fopen(FileName,"wt");
	if(fp)
	{
		fprintf(fp,"Name %s\n",m_Name);
		fprintf(fp,"Gain_dBi %.6lf\n",m_Gain_dBi);
		fprintf(fp,"BeamWidth_H %.6lf\n",m_BeamWidth_H);
		fprintf(fp,"BeamWidth_V %.6lf\n",m_BeamWidth_V);
		fprintf(fp,"Frq_Lo %.6lf\n",m_Frq_Lo);
		fprintf(fp,"Frq_Hi %.6lf\n",m_Frq_Hi);
		fprintf(fp,"Frq_unit %s\n",m_Frq_unit);
		fprintf(fp,"Polarization %s\n",m_Polarization);
		fputs("Pattern\n",fp);
		for(int i=0;i<360;i++)
			fprintf(fp,"%3i %5.2f %5.2f\n",m_Angle[i],m_PatternH[i],m_PatternV[i]);

		fclose(fp);
		return 1;
	}//end if
	else 
		return 0;
}

void CAntennaFormView::OnChangeEDITAttnH() 
{
	UpdateData();

	int n = atoi(m_Ang);
	m_PatternH[n] = min(50.0,max(0.0,atof(m_AttnH)));
	m_PatternV[n] = min(50.0,max(0.0,atof(m_AttnV)));

	//////////////////////////
	CString str;
	m_list.ResetContent();
	for (int i=0;i<360;i++)
	{
		str.Format("%03d  %7.3f    %7.3f",m_Angle[i],m_PatternH[i],m_PatternV[i]);
		m_list.AddString(str);
	}
	m_list.SetCurSel(n);

	//////////////////Pointer///////////////////////
	double pi   = 4.0*atan(1.0), rPix;
	if(m_HV)
		rPix = m_radius*(1.0-m_PatternH[n]/50.0);
	else
	{
		rPix = m_radius*(1.0-m_PatternV[n]/50.0);
		n=90-n;
	}
	m_Xp = int(m_X + rPix*sin(n*pi/180.0));
	m_Yp = int(m_Y + rPix*cos(n*pi/180.0));
	////////////////////////////////////////////
	InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);

	UpdateData(false);
}

void CAntennaFormView::OnChangeEDITAttnV() 
{
	OnChangeEDITAttnH();	
}

void CAntennaFormView::OnOmni() 
{
	SetValue(0.0);	
}

void CAntennaFormView::OnClear() 
{
	SetValue(50.0);	
}

void CAntennaFormView::OnSetAll() 
{
	UpdateData();
	SetValue(m_AllValue);	
	UpdateData(false);	
}

void CAntennaFormView::SetValue(double Val) 
{
	UpdateData();
	CString str;
	m_list.ResetContent();
	for (int i=0;i<360;i++)
	{
		if(m_HV)
			m_PatternH[i]=min(50.0,max(0.0,Val));
		else
			m_PatternV[i]=min(50.0,max(0.0,Val));

		str.Format("%03d  %7.3f    %7.3f",m_Angle[i],m_PatternH[i],m_PatternV[i]);
		m_list.AddString(str);
	}
	m_list.SetCurSel(0);
	InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
	UpdateData(false);
}

void CAntennaFormView::OnOptionFilldiagram() 
{
	if(!m_fill)
	{
		CColorDialog xx(m_fillcolor, CC_FULLOPEN);
		if	(xx.DoModal()==IDOK)
			m_fillcolor=xx.GetColor();
	}
	m_fill =  (m_fill ? false : true);
	Invalidate();
	
}
void CAntennaFormView::OnUpdateOptionFilldiagram(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_fill);
}

void CAntennaFormView::OnOptionHorizontalpattern() 
{
	if (m_HV==false)
	{
		m_HV = true;
		m_Xp = m_X;m_Yp = m_Y;
	//	InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
		InvalidateRect(CRect(0 ,0, m_AxesW1, 1.1*m_AxesH1),true);
	}
}
void CAntennaFormView::OnUpdateOptionHorizontalpattern(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_HV);
}

void CAntennaFormView::OnOptionVerticalpattern() 
{
	if (m_HV)
	{
		m_HV = false;
		m_Xp = m_X;m_Yp = m_Y;
//		InvalidateRect(CRect(m_AxesL1 ,m_AxesT1, m_AxesW1, m_AxesH1),true);
		InvalidateRect(CRect(0 ,0, m_AxesW1, 1.1*m_AxesH1),true);
	}
}
void CAntennaFormView::OnUpdateOptionVerticalpattern(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!m_HV);
}

void CAntennaFormView::OnOption3dgraph() 
{
	((CSMS4DCApp *)AfxGetApp())->m_antfile  = m_antfile;
	((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Antenna 3D View");
}

void CAntennaFormView::OnHor() 
{
	OnOptionHorizontalpattern();
}
void CAntennaFormView::OnVer() 
{
	OnOptionVerticalpattern();	
}
void CAntennaFormView::On3d() 
{
	OnOption3dgraph();	
}


BOOL CAntennaFormView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}
void CAntennaFormView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CAntennaFormView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}

void CAntennaFormView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
		m_rcPrintRect=pInfo->m_rectDraw;
	
	CFormView::OnPrint(pDC, pInfo);
}

void CAntennaFormView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CFormView::OnFilePrintPreview();
}

void CAntennaFormView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
	Invalidate();
}
