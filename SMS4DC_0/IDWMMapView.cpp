// IDWMMapView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "IDWMMapView.h"
#include "CountrySelectionDLG.h"

#include <math.h>
#include "MainFrm.h"
#include "Code2NameCTY.h"
#include "BorderStyleDLG.h"

#include "Ap7_StyleDLG.h"

#include "AP7EarthStationDLG.h"
#include "AP7_CordContourDLG.h"
#include <afxdb.h>

//#include "FileDlg.h"
#include "VectorDLG.h"

#include "IDWMMapDoc.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapView

IMPLEMENT_DYNCREATE(CIDWMMapView, CView)

CIDWMMapView::CIDWMMapView()
{
	pi = 4.0*atan(1.0);	//971025
	D2R = pi/180.0;

	m_flagGIBC = FALSE;
	AxesW=600,AxesH=600,AxesT=0,AxesL=0;

	m_bToolBarDraw = "";
	HScrollpos = 0,VScrollpos = 0;
	m_stBoxPoint  = CPoint(0,0);
	m_enBoxPoint  = CPoint(0,0);
	m_stBoxPoint1 = CPoint(0,0);
	m_enBoxPoint1 = CPoint(0,0);

	long UNR = 72 ;
	WDBUNIT(&UNR) ;

	lonO1 = -180.0,  lonO2 =180.0;
	latO1 =  -90.0,  latO2 = 90.0;

	DlonO1 = 50.0,  DlonO2 = 51.0;
	DlatO1 = 35.0,  DlatO2 = 36.0;

	CString ctryLocal = ((CSMS4DCApp *)AfxGetApp())->m_ctryLocal;
	OnCountryDefault(ctryLocal,&DlatO1, &DlonO1) ;
	conS = "";

	gpPicture1=NULL;
	m_Backgroundmap=false;
	m_FillMode = false;
	m_bLPressed = false;
	m_CONPressed = FALSE;

	m_LineColorB = RGB(0,0,0);		m_LineWidthB = 1;	m_LineStyleB = PS_SOLID;
	m_LineColorC = RGB(255,0,0);	m_LineWidthC = 1;	m_LineStyleC = PS_SOLID;
	m_LineColorI = RGB(255,255,0);	m_LineWidthI = 1;	m_LineStyleI = PS_SOLID;
	m_LineColorL = RGB(0,255,0);	m_LineWidthL = 1;	m_LineStyleL = PS_SOLID;
	m_LineColorR = RGB(255,255,255);m_LineWidthR = 2;	m_LineStyleR = PS_SOLID;
	m_LineColorO = RGB(255,0,255);	m_LineWidthO = 1;	m_LineStyleO = PS_SOLID;
	m_LineColorPR= RGB(191,0,0);	m_LineWidthPR= 3;	m_LineStylePR= PS_SOLID;
	m_LineColor7 = RGB(0,0,0);		m_LineWidth7 = 2;	m_LineStyle7 = PS_SOLID;

	m_BKColor = RGB(50,50,255);

	m_LineB = TRUE;
	m_LineC = TRUE;
	m_LineI = FALSE;
	m_LineL = FALSE;
	m_LineO = FALSE;
	m_ITUR  = TRUE;
	m_LinePR = 0;

	m_S7=false;
	m_M1=m_M2=m_M1_10=m_M1_20=m_M1_30=m_M1_40=m_M1_50=m_M1_60 = FALSE;
	m_ifrom = m_ito = 0;


	nWidth1=nWidth2=nWidth3=nWidth4=nWidth5=nWidth6=nWidth7=nWidth8 = 2;
	nStyle1=nStyle2=nStyle3=nStyle4=nStyle5=nStyle6=nStyle7=nStyle8 = PS_SOLID;

	crColor1 = RGB(0,0,0);
	crColor2 = RGB(0,0,200);
	crColor3 = RGB(0,255,0);
	crColor4 = RGB(0,255,255);
	crColor5 = RGB(255,0,0);
	crColor6 = RGB(255,0,255);
	crColor7 = RGB(255,255,0);
	crColor8 = RGB(100,100,100);

//	m_R1448Path = _T("C:\\Br_soft\\ITU_R_RC\\R1448");	//path should be set into C:\windows\br_soft.ini
//	m_R1448Path = _T("C:\\E\\map1\\SMS4DC_0\\R1448");

	m_R1448Path = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("R1448");

	m_zoomFactor = 1;
	
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarIDWMMap), TRUE, FALSE);
	m_POLYnum = 0;
	m_ALLcountry = FALSE;

	//971024
	m_LatGIBC = -999;
	m_LonGIBC = -999;
}

CIDWMMapView::~CIDWMMapView()
{
	 gpPicture1=NULL;
	 delete gpPicture1;
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarIDWMMap), FALSE, FALSE);
}


BEGIN_MESSAGE_MAP(CIDWMMapView, CView)
	//{{AFX_MSG_MAP(CIDWMMapView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ZoomIn, OnZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ZoomIn, OnUpdateZoomIn)
	ON_COMMAND(ID_ZoomOut, OnZoomOut)
	ON_COMMAND(ID_Refresh, OnRefresh)
	ON_COMMAND(ID_Draw_Box, OnDrawBox)
	ON_UPDATE_COMMAND_UI(ID_Draw_Box, OnUpdateDrawBox)
	ON_COMMAND(ID_CountryList, OnCountryList)
	ON_COMMAND(ID_DEM, OnDem)
	ON_COMMAND(ID_OPTION_BACKGROUNDCOLOR, OnOptionBackgroundcolor)
	ON_UPDATE_COMMAND_UI(ID_OPTION_BACKGROUNDCOLOR, OnUpdateOptionBackgroundcolor)
	ON_COMMAND(ID_OPTION_BACKGROUNDMAP, OnOptionBackgroundmap)
	ON_UPDATE_COMMAND_UI(ID_OPTION_BACKGROUNDMAP, OnUpdateOptionBackgroundmap)
	ON_COMMAND(ID_OPTION_BORDER, OnOptionBorder)
	ON_UPDATE_COMMAND_UI(ID_OPTION_BORDER, OnUpdateOptionBorder)
	ON_COMMAND(ID_OPTION_BORDERSTYLE, OnOptionBorderstyle)
	ON_UPDATE_COMMAND_UI(ID_OPTION_BORDERSTYLE, OnUpdateOptionBorderstyle)
	ON_COMMAND(ID_OPTION_COAST, OnOptionCoast)
	ON_UPDATE_COMMAND_UI(ID_OPTION_COAST, OnUpdateOptionCoast)
	ON_COMMAND(ID_OPTION_COASTSTYLE, OnOptionCoaststyle)
	ON_UPDATE_COMMAND_UI(ID_OPTION_COASTSTYLE, OnUpdateOptionCoaststyle)
	ON_COMMAND(ID_OPTION_ISLAND, OnOptionIsland)
	ON_UPDATE_COMMAND_UI(ID_OPTION_ISLAND, OnUpdateOptionIsland)
	ON_COMMAND(ID_OPTION_ISLANDSTYLE, OnOptionIslandstyle)
	ON_UPDATE_COMMAND_UI(ID_OPTION_ISLANDSTYLE, OnUpdateOptionIslandstyle)
	ON_COMMAND(ID_OPTION_LAKE, OnOptionLake)
	ON_UPDATE_COMMAND_UI(ID_OPTION_LAKE, OnUpdateOptionLake)
	ON_COMMAND(ID_OPTION_LAKESTYLE, OnOptionLakestyle)
	ON_UPDATE_COMMAND_UI(ID_OPTION_LAKESTYLE, OnUpdateOptionLakestyle)
	ON_COMMAND(ID_OPTION_ITUREGIONS, OnOptionIturegions)
	ON_UPDATE_COMMAND_UI(ID_OPTION_ITUREGIONS, OnUpdateOptionIturegions)
	ON_COMMAND(ID_OPTION_ITUREGIONSSTYLE, OnOptionIturegionsstyle)
	ON_UPDATE_COMMAND_UI(ID_OPTION_ITUREGIONSSTYLE, OnUpdateOptionIturegionsstyle)
	ON_COMMAND(ID_OPTION_COASTZONES, OnOptionCoastzones)
	ON_UPDATE_COMMAND_UI(ID_OPTION_COASTZONES, OnUpdateOptionCoastzones)
	ON_COMMAND(ID_OPTION_COASTZONESSTYLE, OnOptionCoastzonesstyle)
	ON_UPDATE_COMMAND_UI(ID_OPTION_COASTZONESSTYLE, OnUpdateOptionCoastzonesstyle)
	ON_COMMAND(ID_OPTION_PROPAGATIONZONES_ST61, OnOptionPropagationzonesSt61)
	ON_UPDATE_COMMAND_UI(ID_OPTION_PROPAGATIONZONES_ST61, OnUpdateOptionPropagationzonesSt61)
	ON_COMMAND(ID_OPTION_PROPAGATIONZONES_GE84, OnOptionPropagationzonesGe84)
	ON_UPDATE_COMMAND_UI(ID_OPTION_PROPAGATIONZONES_GE84, OnUpdateOptionPropagationzonesGe84)
	ON_COMMAND(ID_OPTION_PROPAGATIONZONES_GE89, OnOptionPropagationzonesGe89)
	ON_UPDATE_COMMAND_UI(ID_OPTION_PROPAGATIONZONES_GE89, OnUpdateOptionPropagationzonesGe89)
	ON_COMMAND(ID_OPTION_PROPAGATIONZONES_GE2004, OnOptionPropagationzonesGe2004)
	ON_UPDATE_COMMAND_UI(ID_OPTION_PROPAGATIONZONES_GE2004, OnUpdateOptionPropagationzonesGe2004)
	ON_COMMAND(ID_OPTION_PROPAGATIONZONES_CLEARFROMDISPLAY, OnOptionPropagationzonesClearfromdisplay)
	ON_COMMAND(ID_OPTION_PROPAGATIONZONESSTYLE, OnOptionPropagationzonesstyle)
	ON_UPDATE_COMMAND_UI(ID_OPTION_PROPAGATIONZONESSTYLE, OnUpdateOptionPropagationzonesstyle)
	ON_UPDATE_COMMAND_UI(ID_OPTION_PROPAGATIONZONES_CLEARFROMDISPLAY, OnUpdateOptionPropagationzonesClearfromdisplay)
	ON_COMMAND(ID_OPTION_RRAPPENDIX7_EARTHSTATIONSELECTION, OnOptionRrappendix7Earthstationselection)
	ON_COMMAND(ID_OPTION_RRAPPENDIX7_DRAWCONTOURS, OnOptionRrappendix7Drawcontours)
	ON_UPDATE_COMMAND_UI(ID_OPTION_RRAPPENDIX7_DRAWCONTOURS, OnUpdateOptionRrappendix7Drawcontours)
	ON_COMMAND(ID_OPTION_RRAPPENDIX7_STYLE, OnOptionRrappendix7Style)
	ON_UPDATE_COMMAND_UI(ID_OPTION_RRAPPENDIX7_STYLE, OnUpdateOptionRrappendix7Style)
	ON_COMMAND(ID_OPTION_RRAPPENDIX7_VIEWINPUTFILE, OnOptionRrappendix7Viewinputfile)
	ON_COMMAND(ID_OPTION_RRAPPENDIX7_VIEWOUTPUTFILE, OnOptionRrappendix7Viewoutputfile)
	ON_COMMAND(ID_OPTION_RRAPPENDIX7_VIEWOUTPUTFILE1, OnOptionRrappendix7Viewoutputfile1)
	ON_COMMAND(ID_OPTION_RRAPPENDIX7_SAVEVECTORS, OnOptionRrappendix7Savevectors)
	ON_UPDATE_COMMAND_UI(ID_OPTION_RRAPPENDIX7_SAVEVECTORS, OnUpdateOptionRrappendix7Savevectors)
	ON_COMMAND(ID_HELP_MANUAL, OnHelpManual)
	ON_COMMAND(ID_VECTORS_DRAWFROMFILE, OnVectorsDrawfromfile)
	ON_COMMAND(ID_VECTORS_REMOVEFROMDISPLAY, OnVectorsRemovefromdisplay)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_OPTION_FILLCOUNTRIES, OnOptionFillcountries)
	ON_UPDATE_COMMAND_UI(ID_OPTION_FILLCOUNTRIES, OnUpdateOptionFillcountries)
	ON_COMMAND(ID_OPTION_RRAPPENDIX7GIBC, OnOptionRrappendix7gibc)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapView drawing

void CIDWMMapView::Draw_printMargin(CDC* pDC)
{
	float  latO1r = (float)(latO1*D2R);		float  lonO1r = (float)(lonO1*D2R);//971025
	float  latO2r = (float)(latO2*D2R);		float  lonO2r = (float)(lonO2*D2R);

	if ((pDC->IsPrinting()))
	{
		int x11,y11,x21,y21;
		int offset = 100;

		x11 = m_rcPrintRect.left   + offset;
		y11 = m_rcPrintRect.top    + offset;
		x21 = m_rcPrintRect.right  - x11;
		y21 = m_rcPrintRect.bottom - y11;

		CBrush brush(RGB(255,255,255));			pDC->SelectObject(&brush);
		CPen pen(PS_SOLID,1,RGB(255,255,255));	pDC->SelectObject(&pen);
		pDC->Rectangle(0,0,x21+100,y11+700);
		pDC->Rectangle(0,0,x11+700,y21+100);
		pDC->Rectangle(0,y21-700,x21+100,y21+100);
		pDC->Rectangle(x21-700,0,x21+100,y21+100);

		CPen pen0(PS_SOLID,7,RGB(0,0,0));		pDC->SelectObject(&pen0);
		pDC->MoveTo(x11,y11);
		pDC->LineTo(x21,y11);	pDC->LineTo(x21,y21);	pDC->LineTo(x11,y21);	pDC->LineTo(x11,y11);

		float RLON,RLAT;
		CString RLONbs,RLATbs;

		RLON = lonO1r;		RLAT = latO2r;
		Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
		TextDraw(pDC,x21-650, y11+800,RLATbs,RGB(0,0,0),0,7*12);
		TextDraw(pDC,x11+800, y21-700,RLONbs,RGB(0,0,0),0,7*12);

		RLON = lonO2r;		RLAT = latO1r;
		Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
		TextDraw(pDC,x21-650, y21-800,RLATbs,RGB(0,0,0),0,7*12);
		TextDraw(pDC,x21-1000, y21-700,RLONbs,RGB(0,0,0),0,7*12);

		if(m_S7)
		{
			CString CTRYlist[1000];
			AP28_Affected_CTRY(CTRYlist);
			
			CString PathFileNametemp =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("R1448\\temp7.tmp");
			FILE *fptemp=fopen(PathFileNametemp,"rt");
			char dum1[30],dum2[30],dum3[40];

			CString str1,str2,str0, strADMIN, strES, strCTRY, strNTC, strCORD;
			int k=0, L = (m_strout.GetLength())/m_RowNum;
			for(int i=m_ifrom;i<=m_ito;i++)
			{
				fscanf( fptemp, "%s  %s  %s", dum1,dum2,dum3);
				str0 = _T("");
				str1.Format("%02d:  ",i+1);
				str0 = str0 + str1;
				strADMIN =  m_strout.Mid(i*L+0,3);
				strES =  m_strout.Mid(i*L+3,20);	strES.TrimLeft();
				strCTRY =  m_strout.Mid(i*L+0,3);
				str1 = m_strout.Mid(i*L+26,1);
				str1 = (str1=="E") ? "Tx" : "Rx";
				str0 = str0 + str1 + _T(" , ");
				str0 = str0 + dum2 + _T(" , ");
				strCORD =  m_strout.Mid(i*L+63,8) + _T("  ") + m_strout.Mid(i*L+71,7);
				str0 = str0 + m_strout.Mid(i*L+79,3) + _T(" , ");
				str0 = str0 + m_strout.Mid(i*L+82,8) + _T(" , ");
				str0 = str0 + m_strout.Mid(i*L+90,8) + _T(" , ");
				strNTC =  dum1;
				str1 = m_strout.Mid(i*L+43,20);		str1.TrimLeft();
				str0 = str0 + str1 + _T(" , ");
				str0 = str0 + dum3 + _T(" , ");
				str0 = str0 + CTRYlist[i] + _T(" , ");
				str2 = m_strout.Mid(i*L+27,1);
				str2 = (str2=="5") ? "" : " ( " + str2 + " ) ";
				str1 = m_strout.Mid(i*L+35,8) ;
				str1 = str1 + str2;
				str0 = str0 + str1;
				TextDraw(pDC,x21/30, 200+100*k,str0,RGB(0,0,0),0,7*12);
				k++;
			}
			fclose(fptemp);

			str1 = _T("Tx/Rx,Group ID,Service Type,MinFrq(MHz),MaxFrq(MHz),SAT Name,Beam Name,Probably Affected Countries,App7 Method");
			TextDraw(pDC,x21/30, 100,str1,RGB(0,0,125),0,7*12);

			TextDraw(pDC,x21-450, y21/3-400,"Mode 1",     crColor1,0,7*12);
			TextDraw(pDC,x21-450, y21/3-300,"Mode 2",     crColor2,0,7*12);
			TextDraw(pDC,x21-450, y21/3-200,"Mode 1(-10)",crColor3,0,7*12);
			TextDraw(pDC,x21-450, y21/3-100,"Mode 1(-20)",crColor4,0,7*12);
			TextDraw(pDC,x21-450, y21/3+  0,"Mode 1(-30)",crColor5,0,7*12);
			TextDraw(pDC,x21-450, y21/3+100,"Mode 1(-40)",crColor6,0,7*12);
			TextDraw(pDC,x21-450, y21/3+200,"Mode 1(-50)",crColor7,0,7*12);
			TextDraw(pDC,x21-450, y21/3+300,"Mode 1(-60)",crColor8,0,7*12);

			str1.Format("Admin : %s, ES Name : %s, Country : %s, Notice ID : %s, Coordinates : %s",strADMIN, strES, strCTRY, strNTC, strCORD);
			TextDraw(pDC,x21/30, y21-400,str1,RGB(0,0,0),0,7*12);
		}
	}

}
void CIDWMMapView::Draw_BkRect(CDC* pDC)//971026
{
	CRect rect;
	///////////////////////////////////////
	if (pDC->IsPrinting())
	{
		int offset = 800;
		rect.top    = m_rcPrintRect.top    + offset;
		rect.left   = m_rcPrintRect.left   + offset;
		rect.bottom = m_rcPrintRect.bottom - offset;
		rect.right  = m_rcPrintRect.right  - offset;
	}
	else	GetClientRect(&rect);
//	pDC->DPtoLP(&rect);		//??
	///////////////////////////////////////
	AxesL = rect.left;		AxesT = rect.top;
	AxesW = rect.Width();	AxesH = rect.Height();

	if (gpPicture1)
	{
		long hmWidth = 0 , hmHeight = 0;
		gpPicture1->get_Width(&hmWidth);
		gpPicture1->get_Height(&hmHeight);

		int x1 = (int)((hmWidth/2.0)*(lonO1/180.0+1.0));
		int x2 = (int)((hmWidth/2.0)*(lonO2/180.0+1.0));
		int y1 = (int)((hmHeight/2.0)*(latO1/90.0+1.0));
		int y2 = (int)((hmHeight/2.0)*(latO2/90.0+1.0));

		gpPicture1->Render(pDC->m_hDC, AxesL, AxesT, AxesW, AxesH,
										x1, y1+(y2-y1), x2-x1, -(y2-y1), &rect);
	}
	else	pDC->FillRect(&rect,&CBrush(m_BKColor));
}

BOOL CIDWMMapView::OnEraseBkgnd(CDC* pDC) 
{
	return true;
//	return CView::OnEraseBkgnd(pDC);
}

#include "memdc.h"
void CIDWMMapView::OnDraw(CDC* pDC)//97/11/08
{
	CMemDC mDC(pDC);
	OnDraw4(mDC);
}
void CIDWMMapView::OnDraw4(CDC* pDC)//97/11/08
{
	int scale = 1;
	if (pDC->IsPrinting())	scale = 7;

	Draw_BkRect(pDC);

	if(m_ALLcountry)	ALLcountry( pDC) ;

	float  latO1r = (float)(latO1*D2R);		float  lonO1r = (float)(lonO1*D2R);//971025
	float  latO2r = (float)(latO2*D2R);		float  lonO2r = (float)(lonO2*D2R);

	if(m_LineO)	  DrawCoastalZone(pDC,	 'O',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthO*scale, m_LineColorO ,m_LineStyleO );
	if(m_LineB)	  DrawVectorM(    pDC,	 'B',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthB*scale, m_LineColorB ,m_LineStyleB );
	if(m_LineC)	  DrawVectorM(    pDC,	 'C',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthC*scale, m_LineColorC ,m_LineStyleC );
	if(m_LineI)	  DrawVectorM(    pDC,	 'I',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthI*scale, m_LineColorI ,m_LineStyleI );
	if(m_LineL)	  DrawVectorM(    pDC,	 'L',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthL*scale, m_LineColorL ,m_LineStyleL );
	if(m_ITUR)	  DrawVectorM(    pDC,	 ' ',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthR*scale, m_LineColorR ,m_LineStyleR );
	if(m_LinePR>0)DrawVectorGE(   pDC, m_LinePR,lonO1r,latO1r,lonO2r,latO2r, m_LineWidthPR*scale,m_LineColorPR,m_LineStylePR);

	/////////////////////////////App 7////////////////////
	AP28_Draw(pDC);

	/////////////////////////////Country////////////////////
	if(conS.GetLength()>0)	VectorCountry(pDC,conS, 1, RGB(0,0,0) , 3*scale);

	////////////// Draw Box /////////////////////////////
	if (!(pDC->IsPrinting()))
	{
		if(!((m_stLat==m_enLat)&&(m_stLon==m_enLon)))	//971024
		{
			LatLon2Point(m_stLat,m_stLon , &m_stBoxPoint1);
			LatLon2Point(m_enLat,m_enLon , &m_enBoxPoint1);
			pDC->MoveTo(m_stBoxPoint1.x,m_stBoxPoint1.y);
			pDC->LineTo(m_stBoxPoint1.x,m_enBoxPoint1.y);
			pDC->LineTo(m_enBoxPoint1.x,m_enBoxPoint1.y);
			pDC->LineTo(m_enBoxPoint1.x,m_stBoxPoint1.y);
			pDC->LineTo(m_stBoxPoint1.x,m_stBoxPoint1.y);
		}
	}

	Draw_printMargin(pDC);

	///////////////////Vector Polygon////////////////////////
	if (m_POLYnum>=1)
		for (int i=0;i<m_POLYnum;i++)	DrawVector(pDC, m_POLY[i].PathNameVec,m_POLY[i].nWidthVec,m_POLY[i].crColorVec,m_POLY[i].nStyleVec,	m_POLY[i].nModeVec,m_POLY[i].flColorVec,m_POLY[i].alphaVec) ;

	if(m_flagGIBC && m_LatGIBC>-999 && m_LonGIBC>-999)		//971024
	{
		DrawSymboleStation(pDC,m_LatGIBC,m_LonGIBC,m_LineColor7,4*scale); 
		CPoint p0;	LatLon2Point(m_LatGIBC, m_LonGIBC, &p0);
		pDC->SetBkMode(TRANSPARENT);
		TextDraw(pDC,p0.x+scale*5,p0.y-scale*5, m_NameGIBC, RGB(0,0,0),0,scale*12);
	}
}


void CIDWMMapView::OnDraw1(CDC* pDC)//971026
{
	CDocument* pDoc = GetDocument();	//??

	CRect rect;
	int scale = 1;
	///////////////////////////////////////
	if (pDC->IsPrinting())
	{
		int offset = 800;
		rect.top    = m_rcPrintRect.top    + offset;
		rect.left   = m_rcPrintRect.left   + offset;
		rect.bottom = m_rcPrintRect.bottom - offset;
		rect.right  = m_rcPrintRect.right  - offset;
		scale = 7;
	}
	else	GetClientRect(&rect);
	pDC->DPtoLP(&rect);		//??
	///////////////////////////////////////
	AxesL = rect.left;		AxesT = rect.top;
	AxesW = rect.Width();	AxesH = rect.Height();

	if (gpPicture1)
	{
		long hmWidth = 0 , hmHeight = 0;
		gpPicture1->get_Width(&hmWidth);
		gpPicture1->get_Height(&hmHeight);

		int x1 = (int)((hmWidth/2.0)*(lonO1/180.0+1.0));
		int x2 = (int)((hmWidth/2.0)*(lonO2/180.0+1.0));
		int y1 = (int)((hmHeight/2.0)*(latO1/90.0+1.0));
		int y2 = (int)((hmHeight/2.0)*(latO2/90.0+1.0));

		gpPicture1->Render(pDC->m_hDC, AxesL, AxesT, AxesW, AxesH,
				   x1, y1+(y2-y1), x2-x1, -(y2-y1), &rect);
	}
	else	pDC->FillRect(&rect,&CBrush(m_BKColor));


	if(m_ALLcountry)	ALLcountry( pDC) ;

	float  latO1r = (float)(latO1*D2R);		float  lonO1r = (float)(lonO1*D2R);//971025
	float  latO2r = (float)(latO2*D2R);		float  lonO2r = (float)(lonO2*D2R);

	if(m_LineO)	  DrawCoastalZone(pDC,	 'O',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthO*scale, m_LineColorO ,m_LineStyleO );
	if(m_LineB)	  DrawVectorM(    pDC,	 'B',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthB*scale, m_LineColorB ,m_LineStyleB );
	if(m_LineC)	  DrawVectorM(    pDC,	 'C',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthC*scale, m_LineColorC ,m_LineStyleC );
	if(m_LineI)	  DrawVectorM(    pDC,	 'I',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthI*scale, m_LineColorI ,m_LineStyleI );
	if(m_LineL)	  DrawVectorM(    pDC,	 'L',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthL*scale, m_LineColorL ,m_LineStyleL );
	if(m_ITUR)	  DrawVectorM(    pDC,	 ' ',	lonO1r,latO1r,lonO2r,latO2r, m_LineWidthR*scale, m_LineColorR ,m_LineStyleR );
	if(m_LinePR>0)DrawVectorGE(   pDC, m_LinePR,lonO1r,latO1r,lonO2r,latO2r, m_LineWidthPR*scale,m_LineColorPR,m_LineStylePR);

	/////////////////////////////App 7////////////////////
	AP28_Draw(pDC);

	/////////////////////////////Country////////////////////
//	if(conS.GetLength()>0)	VectorCountry(pDC,conS,3*scale);
	if(conS.GetLength()>0)	VectorCountry(pDC,conS, 1, RGB(0,0,0) , 3*scale);

	////////////// Draw Box /////////////////////////////
	if (!(pDC->IsPrinting()))
	{
		if(!((m_stLat==m_enLat)&&(m_stLon==m_enLon)))	//971024
		{
			LatLon2Point(m_stLat,m_stLon , &m_stBoxPoint1);
			LatLon2Point(m_enLat,m_enLon , &m_enBoxPoint1);
			pDC->MoveTo(m_stBoxPoint1.x,m_stBoxPoint1.y);
			pDC->LineTo(m_stBoxPoint1.x,m_enBoxPoint1.y);
			pDC->LineTo(m_enBoxPoint1.x,m_enBoxPoint1.y);
			pDC->LineTo(m_enBoxPoint1.x,m_stBoxPoint1.y);
			pDC->LineTo(m_stBoxPoint1.x,m_stBoxPoint1.y);
		}
	}

	if ((pDC->IsPrinting()))
	{
		int x11,y11,x21,y21;
		int offset = 100;

		x11 = m_rcPrintRect.left   + offset;
		y11 = m_rcPrintRect.top    + offset;
		x21 = m_rcPrintRect.right  - x11;
		y21 = m_rcPrintRect.bottom - y11;

		CBrush brush(RGB(255,255,255));			pDC->SelectObject(&brush);
		CPen pen(PS_SOLID,1,RGB(255,255,255));	pDC->SelectObject(&pen);
		pDC->Rectangle(0,0,x21+100,y11+700);
		pDC->Rectangle(0,0,x11+700,y21+100);
		pDC->Rectangle(0,y21-700,x21+100,y21+100);
		pDC->Rectangle(x21-700,0,x21+100,y21+100);

		CPen pen0(PS_SOLID,7,RGB(0,0,0));		pDC->SelectObject(&pen0);
		pDC->MoveTo(x11,y11);
		pDC->LineTo(x21,y11);	pDC->LineTo(x21,y21);	pDC->LineTo(x11,y21);	pDC->LineTo(x11,y11);

		float RLON,RLAT;
		CString RLONbs,RLATbs;

		RLON = lonO1r;		RLAT = latO2r;
		Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
		TextDraw(pDC,x21-650, y11+800,RLATbs,RGB(0,0,0),0,7*12);
		TextDraw(pDC,x11+800, y21-700,RLONbs,RGB(0,0,0),0,7*12);

		RLON = lonO2r;		RLAT = latO1r;
		Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
		TextDraw(pDC,x21-650, y21-800,RLATbs,RGB(0,0,0),0,7*12);
		TextDraw(pDC,x21-1000, y21-700,RLONbs,RGB(0,0,0),0,7*12);

		if(m_S7)
		{
			CString CTRYlist[1000];
			AP28_Affected_CTRY(CTRYlist);
			
			CString PathFileNametemp =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("R1448\\temp7.tmp");
			FILE *fptemp=fopen(PathFileNametemp,"rt");
			char dum1[30],dum2[30],dum3[40];

			CString str1,str2,str0, strADMIN, strES, strCTRY, strNTC, strCORD;
			int k=0, L = (m_strout.GetLength())/m_RowNum;
			for(int i=m_ifrom;i<=m_ito;i++)
			{
				fscanf( fptemp, "%s  %s  %s", dum1,dum2,dum3);
				str0 = _T("");
				str1.Format("%02d:  ",i+1);
				str0 = str0 + str1;
				strADMIN =  m_strout.Mid(i*L+0,3);
				strES =  m_strout.Mid(i*L+3,20);	strES.TrimLeft();
				strCTRY =  m_strout.Mid(i*L+0,3);
				str1 = m_strout.Mid(i*L+26,1);
				str1 = (str1=="E") ? "Tx" : "Rx";
				str0 = str0 + str1 + _T(" , ");
				str0 = str0 + dum2 + _T(" , ");
				strCORD =  m_strout.Mid(i*L+63,8) + _T("  ") + m_strout.Mid(i*L+71,7);
				str0 = str0 + m_strout.Mid(i*L+79,3) + _T(" , ");
				str0 = str0 + m_strout.Mid(i*L+82,8) + _T(" , ");
				str0 = str0 + m_strout.Mid(i*L+90,8) + _T(" , ");
				strNTC =  dum1;
				str1 = m_strout.Mid(i*L+43,20);		str1.TrimLeft();
				str0 = str0 + str1 + _T(" , ");
				str0 = str0 + dum3 + _T(" , ");
				str0 = str0 + CTRYlist[i] + _T(" , ");
				str2 = m_strout.Mid(i*L+27,1);
				str2 = (str2=="5") ? "" : " ( " + str2 + " ) ";
				str1 = m_strout.Mid(i*L+35,8) ;
				str1 = str1 + str2;
				str0 = str0 + str1;
				TextDraw(pDC,x21/30, 200+100*k,str0,RGB(0,0,0),0,7*12);
				k++;
			}
			fclose(fptemp);

			str1 = _T("Tx/Rx,Group ID,Service Type,MinFrq(MHz),MaxFrq(MHz),SAT Name,Beam Name,Probably Affected Countries,App7 Method");
			TextDraw(pDC,x21/30, 100,str1,RGB(0,0,125),0,7*12);

			TextDraw(pDC,x21-450, y21/3-400,"Mode 1",     crColor1,0,7*12);
			TextDraw(pDC,x21-450, y21/3-300,"Mode 2",     crColor2,0,7*12);
			TextDraw(pDC,x21-450, y21/3-200,"Mode 1(-10)",crColor3,0,7*12);
			TextDraw(pDC,x21-450, y21/3-100,"Mode 1(-20)",crColor4,0,7*12);
			TextDraw(pDC,x21-450, y21/3+  0,"Mode 1(-30)",crColor5,0,7*12);
			TextDraw(pDC,x21-450, y21/3+100,"Mode 1(-40)",crColor6,0,7*12);
			TextDraw(pDC,x21-450, y21/3+200,"Mode 1(-50)",crColor7,0,7*12);
			TextDraw(pDC,x21-450, y21/3+300,"Mode 1(-60)",crColor8,0,7*12);

			str1.Format("Admin : %s, ES Name : %s, Country : %s, Notice ID : %s, Coordinates : %s",strADMIN, strES, strCTRY, strNTC, strCORD);
			TextDraw(pDC,x21/30, y21-400,str1,RGB(0,0,0),0,7*12);
		}
	}

	///////////////////Vector Polygon////////////////////////
	if (m_POLYnum>=1)
		for (int i=0;i<m_POLYnum;i++)	DrawVector(pDC, m_POLY[i].PathNameVec,m_POLY[i].nWidthVec,m_POLY[i].crColorVec,m_POLY[i].nStyleVec,	m_POLY[i].nModeVec,m_POLY[i].flColorVec,m_POLY[i].alphaVec) ;

//	if(m_flagGIBC)
	if(m_flagGIBC && m_LatGIBC>-999 && m_LonGIBC>-999)		//971024
	{
		DrawSymboleStation(pDC,m_LatGIBC,m_LonGIBC,m_LineColor7,4*scale); 
		CPoint p0;	LatLon2Point(m_LatGIBC, m_LonGIBC, &p0);
		pDC->SetBkMode(TRANSPARENT);
		TextDraw(pDC,p0.x+scale*5,p0.y-scale*5, m_NameGIBC, RGB(0,0,0),0,scale*12);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapView diagnostics

#ifdef _DEBUG
void CIDWMMapView::AssertValid() const
{
	CView::AssertValid();
}

void CIDWMMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapView message handlers

void CIDWMMapView::DrawVectorM(CDC *pDC,char m_LineType,float RLONLL, float RLATLL, float RLONUR, float RLATUR,
							int nWidth,COLORREF crColor, int nStyle) 
{
	CPen pen(nStyle, nWidth, crColor); 
	CPen* pOldPen = pDC->SelectObject(&pen);

	unsigned char CTYVEK[2][4]={"",""}, BCILR;
	long NRCTY = 0;
	if (m_LineType == ' ')
	{
		strcpy((char*)CTYVEK[0] , "R13");
		NRCTY = 1;
	}

	float DENS=0;
	long LINE, NRCRD, NOMORE=0, ITYPE=2, MAXCRD=1950;
	float *CRDARR;		CRDARR = new float[2*MAXCRD];
	GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	
	
	while(!NOMORE)
	{
		GEOLIW( &ITYPE, CRDARR, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
		if(NOMORE)	break;

		if (BCILR==m_LineType)
		{
			CPoint *pp;		pp = new CPoint[NRCRD];
			for(int p=0;p<NRCRD;p++)
				LatLon2Point(CRDARR[2*p+1],CRDARR[2*p],&pp[p]);

			pDC->Polyline(pp,p);
			delete [] pp;
		}
	}
	pDC->SelectObject(pOldPen);
	delete [] CRDARR;
}


void CIDWMMapView::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
{
	double lon1 = lonO1  ,  lon2 = lonO2;
	double lat1 = latO1  ,  lat2 = latO2;

	double x_en,y_en;

	double aX = AxesW / (lon2-lon1);
	double bX = AxesL - AxesW*lon1/(lon2-lon1);
	x_en = aX * lon_deg + bX ;

	double aY = AxesH / (lat1-lat2);
	double bY = AxesT - AxesH*lat2/(lat1-lat2);
	y_en = aY * lat_deg + bY ;

	(*PointSt).x = (long)x_en;
	(*PointSt).y = (long)y_en;
}

void CIDWMMapView::Point2LatLon(CPoint PointSt,double *lat_deg,double *lon_deg) 
{
	double lon1 = lonO1  ,  lon2 = lonO2;
	double lat1 = latO1  ,  lat2 = latO2;

	double aX = AxesW / (lon2-lon1);
	double bX = AxesL - AxesW*lon1/(lon2-lon1);
	*lon_deg = (PointSt.x - bX) / aX;

	double aY = AxesH / (lat1-lat2);
	double bY = AxesT - AxesH*lat2/(lat1-lat2);
	*lat_deg = (PointSt.y - bY) / aY;
}

void CIDWMMapView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bToolBarDraw == _T("zoomin"))
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
		m_stBoxPoint.x=point.x+HScrollpos;
		m_stBoxPoint.y=point.y+VScrollpos;
		m_enBoxPoint.x=point.x+HScrollpos;
		m_enBoxPoint.y=point.y+VScrollpos;
		m_bLPressed=true;
	}	

	if (m_bToolBarDraw == _T("box"))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
	//	InvalidateRect(NULL,false);

		m_stBoxPoint1.x=point.x+HScrollpos;
		m_stBoxPoint1.y=point.y+VScrollpos;
		m_enBoxPoint1.x=point.x+HScrollpos;
		m_enBoxPoint1.y=point.y+VScrollpos;
		m_bLPressed=true;
	}	
	CView::OnLButtonDown(nFlags, point);
}

void CIDWMMapView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bToolBarDraw == _T("box"))
	{
//		InvalidateRect(NULL,true);//971026
		InvalidateRect(NULL,false);
		m_bLPressed=false;
		m_bToolBarDraw=_T("");

		double lat1,lon1,lat2,lon2 , Dlat,Dlon,deltaMax,deltaMin,lat0,lon0;
		Point2LatLon(m_stBoxPoint1,&lat1,&lon1);
		Point2LatLon(m_enBoxPoint1,&lat2,&lon2);

		m_stLat = lat1;		m_stLon = lon1;	m_enLat = lat2;		m_enLon = lon2;

		double xlatO1 ,  xlatO2 ,xlonO1 ,  xlonO2;

		xlatO1=min(lat1,lat2);		xlatO2=max(lat1,lat2);
		xlonO1=min(lon1,lon2);		xlonO2=max(lon1,lon2);

		Dlat = xlatO2-xlatO1;			Dlon = xlonO2-xlonO1;
		deltaMax = max(Dlat,Dlon);	deltaMin = min(Dlat,Dlon);
		lat0=(xlatO2+xlatO1)/2.0;		lon0=(xlonO2+xlonO1)/2.0;

		if (deltaMax <= 2.0*deltaMin)	deltaMax = 2.0*deltaMin;
		else							deltaMin = deltaMax/2.0;

		xlatO1=lat0-deltaMin/2.0;	xlatO2=lat0+deltaMin/2.0;
		xlonO1=lon0-deltaMax/2.0;	xlonO2=lon0+deltaMax/2.0;

		xlatO1 = max(-90.0,min(90.0,xlatO1));
		xlatO2 = max(-90.0,min(90.0,xlatO2));
		xlonO1 = max(-180.0,min(180.0,xlonO1));
		xlonO2 = max(-180.0,min(180.0,xlonO2));

	//	RectInRegionVec(xlatO1 ,  xlatO2 ,xlonO1 ,  xlonO2) ;

		DlatO1 = xlatO1;		DlatO2 = xlatO2;
		DlonO1 = xlonO1;		DlonO2 = xlonO2;
	}
	if (m_bToolBarDraw == _T("zoomin"))
	{
		m_bLPressed = false;
		double lat1,lon1, xlatO1 ,  xlatO2 ,xlonO1 ,  xlonO2;
		Point2LatLon(m_stBoxPoint,&lat1,&lon1);

		if(m_stBoxPoint==m_enBoxPoint)	
		{
			m_zoomFactor = m_zoomFactor*2.0;
			xlatO1 = lat1-90.0/m_zoomFactor;
			xlatO2 = lat1+90.0/m_zoomFactor;
			xlonO1 = lon1-180.0/m_zoomFactor;
			xlonO2 = lon1+180.0/m_zoomFactor;
		}
		else
		{
			double lat2,lon2 , Dlat,Dlon,deltaMax,deltaMin,lat0,lon0;
			Point2LatLon(m_enBoxPoint,&lat2,&lon2);

			xlatO1=min(lat1,lat2);		xlatO2=max(lat1,lat2);
			xlonO1=min(lon1,lon2);		xlonO2=max(lon1,lon2);

			Dlat = xlatO2-xlatO1;			Dlon = xlonO2-xlonO1;
			deltaMax = max(Dlat,Dlon);		deltaMin = min(Dlat,Dlon);
			lat0=(xlatO2+xlatO1)/2.0;		lon0=(xlonO2+xlonO1)/2.0;

			if (deltaMax <= 2.0*deltaMin)
				deltaMax = 2.0*deltaMin;
			else
				deltaMin = deltaMax/2.0;

			xlatO1=lat0-deltaMin/2.0;	xlatO2=lat0+deltaMin/2.0;
			xlonO1=lon0-deltaMax/2.0;	xlonO2=lon0+deltaMax/2.0;

			m_zoomFactor = 180.0/deltaMin;

			m_bToolBarDraw = _T("");
		}
		xlatO1 = max(-90.0,min(90.0,xlatO1));
		xlatO2 = max(-90.0,min(90.0,xlatO2));
		xlonO1 = max(-180.0,min(180.0,xlonO1));
		xlonO2 = max(-180.0,min(180.0,xlonO2));

		double latst,lonst,laten,lonen;
		Point2LatLon(m_stBoxPoint1,&latst,&lonst) ;
		Point2LatLon(m_enBoxPoint1,&laten,&lonen) ;
		latO1 = xlatO1;
		latO2 = xlatO2;
		lonO1 = xlonO1;
		lonO2 = xlonO2;
		LatLon2Point(latst,lonst,&m_stBoxPoint1) ;
		LatLon2Point(laten,lonen,&m_enBoxPoint1) ;

		Invalidate();
	}		
	CView::OnLButtonUp(nFlags, point);
}

void CIDWMMapView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString string;
	double yUTM,xUTM;
	Point2LatLon(point,&yUTM,&xUTM);
	char   xU,yU;
	int    xUTMD,xUTMM,yUTMD,yUTMM;
	double xUTMS,yUTMS;

	DEG2DMS("LON",xUTM,&xUTMD,&xUTMM,&xUTMS,&xU);
	DEG2DMS("LAT",yUTM,&yUTMD,&yUTMM,&yUTMS,&yU);

	string.Format("Lat(%c) : %02d ° %02d ' %0.3f ''",yU,yUTMD,yUTMM,yUTMS );
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, string);

	string.Format("Lon(%c) : %03d ° %02d ' %0.3f ''",xU,xUTMD,xUTMM,xUTMS );
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(2, string);

//	double pi=4.0*atan(1.0);
	float RLON = (float)(xUTM*D2R) ;
	float RLAT = (float)(yUTM*D2R) ;

	CString cty1("");
	GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;

	CCode2NameCTY xx;
	CString m_name = xx.Code2Name_idwm(cty1);

	if (cty1[0]!=' ')
		string.Format(_Z("Country/Region: %s(Code: %s)"),m_name,cty1);
	else
		string.Format(_Z("Country/Region: Sea(Code: ---)"));
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, string);

	long  IRGN= 0;
	GEORGN(&RLON, &RLAT,&IRGN) ;
	string.Format(_Z("Region : ")+"%d",IRGN);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(3, string);

	CString adm1("");
	GEOCTYA( (BYTE*)cty1.GetBufferSetLength(3), (BYTE*)adm1.GetBufferSetLength(3));
	if (adm1[0]!=' ')
		string.Format(_Z("Admin. Code :")+"%s",adm1);
	else
		string.Format(_Z("Admin. Code :")+" ---");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(4, string);


	long int N=4, IER;
	GEOGCMS ( &N, &IER );

	float RLON1 = (float)(RLON-pi/90.0), RLAT1 = (float)(RLAT-pi/90.0),
		  RLON2 = (float)(RLON+pi/90.0), RLAT2 = (float)(RLAT+pi/90.0);

	long IVAL = 2 , IRANGE = 0,  NRPNT = 2;
	float  ARRAY[2][2]={RLON1, RLAT1, RLON2, RLAT2},  WND[2][2],  GC;
	GEOWND( (float *)ARRAY, &NRPNT, (float *)WND);
	GEOGCM( &IVAL, (float *)WND, &IRANGE);
	GEOGCP( &RLON, &RLAT, &GC);

	int WCSea = WarmColdSea(xUTM, yUTM);
	CString					LandSea = _Z("Coastal Zone : ---");
	if((GC==1)&&(WCSea==0)) LandSea = _Z("Coastal Zone : Cold Sea");
	if((GC==1)&&(WCSea==1)) LandSea = _Z("Coastal Zone : Warm Sea");
	if (GC==3)				LandSea = _Z("Coastal Zone : Coastal Land");
	if (GC==4)				LandSea = _Z("Coastal Zone : Land");

	if(m_LinePR>0)
	{
		CString strPR = "";
		if	   (m_LinePR==1)	strPR = _T("ST61");
		else if(m_LinePR==2)	strPR = _T("GE84");
		else if(m_LinePR==3)	strPR = _T("GE89");
		else if(m_LinePR==4)	strPR = _T("GE2006");

		long N1 = m_LinePR,IER1;
		GEOPRMS(&N1, &IER1);
		unsigned char PRCODE[2];
		GEOPRP(&RLON, &RLAT, (unsigned char *)PRCODE);
		if(PRCODE[0]==' ')
			LandSea.Format("%s "+_Z("Propagation Area: outside"),strPR);
		else
			LandSea.Format("%s "+_Z("Propagation Area:")+" %c%c",strPR,PRCODE[0],PRCODE[1]);
	}

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(5, LandSea);

	if(m_bToolBarDraw == "zoomin")	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
	/////////////////////////Draw zoomin///////////////////////////////////////////////
	if(m_bLPressed && (m_bToolBarDraw == "zoomin"))
	{
		CClientDC dc(this);

		CPen pen;	pen.CreatePen(PS_DOT,1,RGB(0,0,0));	dc.SelectObject(&pen);

		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_stBoxPoint.x-HScrollpos,m_stBoxPoint.y-VScrollpos);
		dc.LineTo(m_stBoxPoint.x-HScrollpos,m_enBoxPoint.y-VScrollpos);

		dc.MoveTo(m_stBoxPoint.x-HScrollpos,m_stBoxPoint.y-VScrollpos);
		dc.LineTo(m_stBoxPoint.x-HScrollpos,point.y);

//		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_stBoxPoint.x-HScrollpos,m_enBoxPoint.y-VScrollpos);
		dc.LineTo(m_enBoxPoint.x-HScrollpos,m_enBoxPoint.y-VScrollpos);

		dc.MoveTo(m_stBoxPoint.x-HScrollpos,point.y);
		dc.LineTo(point.x,point.y);

//		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_enBoxPoint.x-HScrollpos,m_enBoxPoint.y-VScrollpos);
		dc.LineTo(m_enBoxPoint.x-HScrollpos,m_stBoxPoint.y-VScrollpos);

		dc.MoveTo(point.x,point.y);
		dc.LineTo(point.x,m_stBoxPoint.y-VScrollpos);

//		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_enBoxPoint.x-HScrollpos,m_stBoxPoint.y-VScrollpos);
		dc.LineTo(m_stBoxPoint.x-HScrollpos,m_stBoxPoint.y-VScrollpos);

		dc.MoveTo(point.x,m_stBoxPoint.y-VScrollpos);
		dc.LineTo(m_stBoxPoint.x-HScrollpos,m_stBoxPoint.y-VScrollpos);

		m_enBoxPoint.x=point.x+HScrollpos;
		m_enBoxPoint.y=point.y+VScrollpos;
	}

	if(m_bToolBarDraw == "box")	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
	/////////////////////////Draw Box///////////////////////////////////////////////
	if(m_bLPressed && (m_bToolBarDraw == "box"))
	{
//		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
		CClientDC dc(this);

		CPen pen;	pen.CreatePen(PS_DOT,1,RGB(0,0,0));	dc.SelectObject(&pen);

		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_stBoxPoint1.x-HScrollpos,m_stBoxPoint1.y-VScrollpos);
		dc.LineTo(m_stBoxPoint1.x-HScrollpos,m_enBoxPoint1.y-VScrollpos);

		dc.MoveTo(m_stBoxPoint1.x-HScrollpos,m_stBoxPoint1.y-VScrollpos);
		dc.LineTo(m_stBoxPoint1.x-HScrollpos,point.y);

//		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_stBoxPoint1.x-HScrollpos,m_enBoxPoint1.y-VScrollpos);
		dc.LineTo(m_enBoxPoint1.x-HScrollpos,m_enBoxPoint1.y-VScrollpos);

		dc.MoveTo(m_stBoxPoint1.x-HScrollpos,point.y);
		dc.LineTo(point.x,point.y);

//		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_enBoxPoint1.x-HScrollpos,m_enBoxPoint1.y-VScrollpos);
		dc.LineTo(m_enBoxPoint1.x-HScrollpos,m_stBoxPoint1.y-VScrollpos);

		dc.MoveTo(point.x,point.y);
		dc.LineTo(point.x,m_stBoxPoint1.y-VScrollpos);

//		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_enBoxPoint1.x-HScrollpos,m_stBoxPoint1.y-VScrollpos);
		dc.LineTo(m_stBoxPoint1.x-HScrollpos,m_stBoxPoint1.y-VScrollpos);

		dc.MoveTo(point.x,m_stBoxPoint1.y-VScrollpos);
		dc.LineTo(m_stBoxPoint1.x-HScrollpos,m_stBoxPoint1.y-VScrollpos);

		m_enBoxPoint1.x=point.x+HScrollpos;
		m_enBoxPoint1.y=point.y+VScrollpos;

	}	
	CView::OnMouseMove(nFlags, point);
}


void CIDWMMapView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
{

	if (x < 0)
	{
		x=-x;
		if (type=="LON")
			xU[0]='W';
		else
			xU[0]='S';
	}
	else
	{
		if (type=="LON")
			xU[0]='E';
		else
			xU[0]='N';
	}

	*xD=(int)x;
	double xM0=60*(x-(*xD));
	*xM=(int)xM0;
	*xS=60*(xM0-(*xM));

	if (*xS>=59.999)
	{
		*xM=*xM+1;	*xS=0.0;
		if (*xM>=60)
		{
			*xD=*xD+1;	*xM=0;
		}
	}
}


void CIDWMMapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CIDWMMapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
BOOL CIDWMMapView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}
void CIDWMMapView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
	{
		pDC->SetStretchBltMode(COLORONCOLOR);
		m_rcPrintRect = pInfo->m_rectDraw;

//SetBitmap(pDC);	

/*	
		int x1,y1,x2,y2,offset = 100;
		x1=m_rcPrintRect.left+offset;
		y1=m_rcPrintRect.top+offset;
		x2=m_rcPrintRect.right-x1;
		y2=m_rcPrintRect.bottom-y1;
		pDC->Rectangle(x1,y1,x2,y2);

		double pi = 4.0*atan(1.0);
		float RLON,RLAT;
		CString RLONbs,RLATbs;

		RLON = lonO1r;		RLAT = latO2r;
		Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
		TextDraw(pDC,x1+300, y1+800,RLATbs,RGB(0,0,0),0,7*12);
		TextDraw(pDC,x1+800, y2-700,RLONbs,RGB(0,0,0),0,7*12);

		RLON = lonO2r;		RLAT = latO1r;
		Rad2Str(RLON,RLAT, &RLONbs,&RLATbs);
		TextDraw(pDC,x1+300, y2-800,RLATbs,RGB(0,0,0),0,7*12);
		TextDraw(pDC,x2-1000, y2-700,RLONbs,RGB(0,0,0),0,7*12);
*/
	}
	CView::OnPrint(pDC, pInfo);
}


void CIDWMMapView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
							int Escapement,
							int nHeight,int nWidth,int FontWeight,CString FontName) 
{
	pDC->SetBkMode(TRANSPARENT);
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight  = nHeight;                // request a 12-pixel-height font
	lf.lfWidth   = nWidth;
	lf.lfWeight  = FontWeight;
	lf.lfCharSet = DEFAULT_CHARSET;			//971211
	strcpy(lf.lfFaceName, FontName);        // request a face name "Arial"
	lf.lfEscapement = Escapement;
	VERIFY(font.CreateFontIndirect(&lf));  // create the font

	CFont* def_font = pDC->SelectObject(&font);

	pDC->SetTextColor(FontColor);
	pDC->TextOut(x,y,_T(str));
	pDC->SelectObject(def_font);

	font.DeleteObject(); 
}
void CIDWMMapView::Rad2Str(float lonRAD,float latRAD,CString *lonSTR,CString *latSTR) 
{
	unsigned char COORD[15];
	CRADDG4( &lonRAD, &latRAD, COORD );
	CString COORD1 = COORD;
	COORD1 = COORD1.Left(15);
	*lonSTR = COORD1.Left(8);
	*latSTR = COORD1.Right(7);
}

void CIDWMMapView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}
void CIDWMMapView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

void CIDWMMapView::OnZoomIn() 
{
	m_bToolBarDraw = (m_bToolBarDraw == _T("zoomin")) ? m_bToolBarDraw=_T("") : m_bToolBarDraw =_T("zoomin");
	if  (m_CONPressed)
	{
	//	InvalidateRgn(&rgn[rgnI],false);
		m_CONPressed = FALSE;
	}
	
}
void CIDWMMapView::OnUpdateZoomIn(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bToolBarDraw == _T("zoomin"));
}

void CIDWMMapView::OnZoomOut() 
{
	double latst,lonst,laten,lonen;
	Point2LatLon(m_stBoxPoint1,&latst,&lonst) ;
	Point2LatLon(m_enBoxPoint1,&laten,&lonen) ;

	lonO1 = -180.0,  lonO2 =180.0;
	latO1 =  -90.0,  latO2 = 90.0;
	m_bToolBarDraw=_T("");
	m_CONPressed = FALSE;

	m_zoomFactor = 1;

	LatLon2Point(latst,lonst,&m_stBoxPoint1) ;
	LatLon2Point(laten,lonen,&m_enBoxPoint1) ;

	Invalidate();	
}

void CIDWMMapView::OnRefresh() 
{
	Invalidate();	
}

void CIDWMMapView::OnDrawBox() 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
	m_bToolBarDraw="box";	
}

void CIDWMMapView::OnUpdateDrawBox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_bToolBarDraw == "box" ? 1 : 0 );	
}

void CIDWMMapView::OnCountryList() 
{
	CCountrySelectionDLG dlg;
	dlg.m_code = conS;
	if ( dlg.DoModal()==IDOK )
	{
		conS = dlg.m_code;
		if((conS==_T("RUS"))||(conS==_T("FJI"))||(conS==_T("NZL"))||(conS==_T("ALS"))){	OnZoomOut();	return;}
	
		double  Dlat,Dlon,deltaMax,deltaMin,lat0,lon0;
		double xlatO1 ,  xlatO2 ,xlonO1 ,  xlonO2;

		char *CTYVEK = dlg.m_code.GetBufferSetLength(3);

		float RLONLL, RLATLL, RLONUR, RLATUR;

		long NRCTY = 1;
		GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);

//		double pi = 4.0*atan(1.0);
		xlatO1 = RLATLL*180.0/pi;		xlatO2 = RLATUR*180.0/pi;
		xlonO1 = RLONLL*180.0/pi;		xlonO2 = RLONUR*180.0/pi;

		Dlat = xlatO2-xlatO1;			Dlon = xlonO2-xlonO1;
		deltaMax = max(Dlat,Dlon);	deltaMin = min(Dlat,Dlon);
		lat0=(xlatO2+xlatO1)/2.0;		lon0=(xlonO2+xlonO1)/2.0;

		if (deltaMax <= 2.0*deltaMin)
			deltaMax = 2.0*deltaMin;
		else
			deltaMin = deltaMax/2.0;

		xlatO1=lat0-deltaMin/2.0;	xlatO2=lat0+deltaMin/2.0;
		xlonO1=lon0-deltaMax/2.0;	xlonO2=lon0+deltaMax/2.0;

		double offset = 2.0;
		xlatO1 = xlatO1 - offset;
		xlonO1 = xlonO1 - offset;
		xlatO2 = xlatO2 + offset;
		xlonO2 = xlonO2 + offset;

		xlatO1 = max(-90.0,min(90.0,xlatO1));
		xlatO2 = max(-90.0,min(90.0,xlatO2));
		xlonO1 = max(-180.0,min(180.0,xlonO1));
		xlonO2 = max(-180.0,min(180.0,xlonO2));

//		RectInRegionVec(xlatO1 ,  xlatO2 ,xlonO1 ,  xlonO2) ;

		double latst,lonst,laten,lonen;
		Point2LatLon(m_stBoxPoint1,&latst,&lonst) ;
		Point2LatLon(m_enBoxPoint1,&laten,&lonen) ;
		latO1 = xlatO1;
		latO2 = xlatO2;
		lonO1 = xlonO1;
		lonO2 = xlonO2;
		LatLon2Point(latst,lonst,&m_stBoxPoint1) ;
		LatLon2Point(laten,lonen,&m_enBoxPoint1) ;

		Invalidate();
	}	
}

void CIDWMMapView::OnDem() 
{
	double m_Lower_left_x = -179.99583333333334;
	double m_Lower_left_y = -89.99583333333334;
	double m_Resolution_x = 0.0083333333334;
	double m_Resolution_y = 0.0083333333334;
	int TileX=1,TileY=1;
  
	double ix=(DlonO1 - m_Lower_left_x) / (600.0*m_Resolution_x);
	double jy=(DlatO1 - m_Lower_left_y) / (600.0*m_Resolution_y);
	TileX = ( ( (ix-(int)ix) < 0.5 ) ? (int) ix : 1+(int) ix);
	TileY = ( ( (jy-(int)jy) < 0.5 ) ? (int) jy : 1+(int) jy);

	((CSMS4DCApp *)AfxGetApp())->TileX = TileX;
	((CSMS4DCApp *)AfxGetApp())->TileY = TileY;

this->GetParent()->ShowWindow(SW_MINIMIZE);	//971108

	((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("Main Desktop");

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(4, " ");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(5, " ");	

//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarIDWMMap), FALSE, FALSE);//970710
}

void CIDWMMapView::OnOptionBackgroundcolor() 
{
	CColorDialog xx(m_BKColor, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		m_BKColor = xx.GetColor();
		Invalidate();
	}
}
void CIDWMMapView::OnUpdateOptionBackgroundcolor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_Backgroundmap);
}

void CIDWMMapView::OnOptionBackgroundmap() 
{
	m_Backgroundmap = ~ m_Backgroundmap;
	if(m_Backgroundmap)
		LoadPictureFile2();
	else
		gpPicture1=NULL;
	Invalidate();
}
void CIDWMMapView::OnUpdateOptionBackgroundmap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Backgroundmap);
}



////////////////////////////////////////////////////////////////////
void CIDWMMapView::LoadPictureFile1(LPCTSTR szFile,LPPICTURE *gpPictureXY1)
{
	// open file
	HANDLE hFile = CreateFile(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	_ASSERTE(INVALID_HANDLE_VALUE != hFile);

	// get file size
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	_ASSERTE(-1 != dwFileSize);

	LPVOID pvData = NULL;
	// alloc memory based on file size
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
	_ASSERTE(NULL != hGlobal);

	pvData = GlobalLock(hGlobal);
	_ASSERTE(NULL != pvData);

	DWORD dwBytesRead = 0;
	// read file and store in global memory
	BOOL bRead = ReadFile(hFile, pvData, dwFileSize, &dwBytesRead, NULL);
	_ASSERTE(FALSE != bRead);
	GlobalUnlock(hGlobal);
	CloseHandle(hFile);

	LPSTREAM pstm = NULL;
	// create IStream* from global memory
	HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);
	_ASSERTE(SUCCEEDED(hr) && pstm);


	LPPICTURE gpPictureXY=NULL;

	// Create IPicture from image file
	if (gpPictureXY)
		gpPictureXY->Release();
	hr = ::OleLoadPicture(pstm, dwFileSize, FALSE, IID_IPicture, (LPVOID *)&gpPictureXY);
	_ASSERTE(SUCCEEDED(hr) && gpPictureXY);	
	pstm->Release();

	*gpPictureXY1 = gpPictureXY;
}
void CIDWMMapView::LoadPictureFile2()
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	CString Fname =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Image_map\\GLOBarc3m");
	LoadPictureFile1( Fname, &gpPicture1);
}

void CIDWMMapView::OnOptionBorder() 
{
	m_LineB = !(m_LineB);
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionBorder(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LineB);
}

void CIDWMMapView::OnOptionBorderstyle() 
{
	CBorderStyleDLG dlg;
	dlg.m_color1 = m_LineColorB;
	dlg.m_LineColorRed = GetRValue(m_LineColorB);
	dlg.m_LineColorGreen = GetGValue(m_LineColorB);
	dlg.m_LineColorBlue = GetBValue(m_LineColorB);
	dlg.m_LineWidth = m_LineWidthB;
	dlg.m_LineStyle0 = m_LineStyleB;

	if ( dlg.DoModal()==IDOK )
	{
		m_LineColorB = dlg.m_color1;
		m_LineWidthB = dlg.m_LineWidth;
		m_LineStyleB = dlg.m_LineStyle0;

		Invalidate();
	}
}

void CIDWMMapView::OnUpdateOptionBorderstyle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_LineB);	
}

void CIDWMMapView::OnOptionCoast() 
{
	m_LineC = !(m_LineC);
	InvalidateRect(NULL,FALSE);
}

void CIDWMMapView::OnUpdateOptionCoast(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LineC);
}

void CIDWMMapView::OnOptionCoaststyle() 
{
	CBorderStyleDLG dlg;
	dlg.m_color1 = m_LineColorC;
	dlg.m_LineColorRed = GetRValue(m_LineColorC);
	dlg.m_LineColorGreen = GetGValue(m_LineColorC);
	dlg.m_LineColorBlue = GetBValue(m_LineColorC);
	dlg.m_LineWidth = m_LineWidthC;
	dlg.m_LineStyle0 = m_LineStyleC;

	if ( dlg.DoModal()==IDOK )
	{
		m_LineColorC = dlg.m_color1;
		m_LineWidthC = dlg.m_LineWidth;
		m_LineStyleC = dlg.m_LineStyle0;

		Invalidate();
	}
}
void CIDWMMapView::OnUpdateOptionCoaststyle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_LineC);
}

void CIDWMMapView::OnOptionIsland() 
{
	m_LineI = !(m_LineI);
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionIsland(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LineI);
}

void CIDWMMapView::OnOptionIslandstyle() 
{
	CBorderStyleDLG dlg;
	dlg.m_color1 = m_LineColorI;
	dlg.m_LineColorRed = GetRValue(m_LineColorI);
	dlg.m_LineColorGreen = GetGValue(m_LineColorI);
	dlg.m_LineColorBlue = GetBValue(m_LineColorI);
	dlg.m_LineWidth = m_LineWidthI;
	dlg.m_LineStyle0 = m_LineStyleI;

	if ( dlg.DoModal()==IDOK )
	{
		m_LineColorI = dlg.m_color1;
		m_LineWidthI = dlg.m_LineWidth;
		m_LineStyleI = dlg.m_LineStyle0;

		Invalidate();
	}
}
void CIDWMMapView::OnUpdateOptionIslandstyle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_LineI);
}

void CIDWMMapView::OnOptionLake() 
{
	m_LineL = !(m_LineL);
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionLake(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LineL);
}

void CIDWMMapView::OnOptionLakestyle() 
{
	CBorderStyleDLG dlg;
	dlg.m_color1 = m_LineColorL;
	dlg.m_LineColorRed = GetRValue(m_LineColorL);
	dlg.m_LineColorGreen = GetGValue(m_LineColorL);
	dlg.m_LineColorBlue = GetBValue(m_LineColorL);
	dlg.m_LineWidth = m_LineWidthL;
	dlg.m_LineStyle0 = m_LineStyleL;

	if ( dlg.DoModal()==IDOK )
	{
		m_LineColorL = dlg.m_color1;
		m_LineWidthL = dlg.m_LineWidth;
		m_LineStyleL = dlg.m_LineStyle0;

		Invalidate();
	}
}
void CIDWMMapView::OnUpdateOptionLakestyle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_LineL);
}

void CIDWMMapView::OnOptionIturegions() 
{
	m_ITUR = !(m_ITUR);
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionIturegions(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ITUR);
}

void CIDWMMapView::OnOptionIturegionsstyle() 
{
	CBorderStyleDLG dlg;
	dlg.m_color1 = m_LineColorR;
	dlg.m_LineColorRed = GetRValue(m_LineColorR);
	dlg.m_LineColorGreen = GetGValue(m_LineColorR);
	dlg.m_LineColorBlue = GetBValue(m_LineColorR);
	dlg.m_LineWidth = m_LineWidthR;
	dlg.m_LineStyle0 = m_LineStyleR;

	if ( dlg.DoModal()==IDOK )
	{
		m_LineColorR = dlg.m_color1;
		m_LineWidthR = dlg.m_LineWidth;
		m_LineStyleR = dlg.m_LineStyle0;

		Invalidate();
	}
}
void CIDWMMapView::OnUpdateOptionIturegionsstyle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_ITUR);
}


void CIDWMMapView::DrawCoastalZone(CDC *pDC,char m_LineType,float RLONLL, float RLATLL, float RLONUR, float RLATUR,
							int nWidth,COLORREF crColor, int nStyle) 
{
	CPen pen(nStyle, nWidth, crColor); 
	CPen* pOldPen = pDC->SelectObject(&pen);

	long IREST,NRCRD, NOMORE=0, ITYPE=2, MAXCRD=1950;
	float CNDV1, CNDV2, WND[2][2]={RLONLL, RLATLL, RLONUR, RLATUR};
	float *CRDARR;		CRDARR = new float[2*MAXCRD];
	
	long int N=4, IER;
	GEOGCMS ( &N, &IER );

	while(!NOMORE)
	{
		GEOGCML ( &ITYPE, (float *)WND, &MAXCRD, CRDARR, 
							 &NRCRD, &IREST, &CNDV1, &CNDV2, &NOMORE );
		CPoint *pp;		pp = new CPoint[NRCRD];
		for(int p=0;p<NRCRD;p++)
			LatLon2Point(CRDARR[2*p+1],CRDARR[2*p],&pp[p]);
		pDC->Polyline(pp,p);
		delete [] pp;
	}
	pDC->SelectObject(pOldPen);
	delete [] CRDARR;
}

void CIDWMMapView::OnOptionCoastzones() 
{
	m_LineO = !(m_LineO);
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionCoastzones(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LineO);
}

void CIDWMMapView::OnOptionCoastzonesstyle() 
{
	CBorderStyleDLG dlg;
	dlg.m_color1 = m_LineColorO;
	dlg.m_LineColorRed = GetRValue(m_LineColorO);
	dlg.m_LineColorGreen = GetGValue(m_LineColorO);
	dlg.m_LineColorBlue = GetBValue(m_LineColorO);
	dlg.m_LineWidth = m_LineWidthO;
	dlg.m_LineStyle0 = m_LineStyleO;

	if ( dlg.DoModal()==IDOK )
	{
		m_LineColorO = dlg.m_color1;
		m_LineWidthO = dlg.m_LineWidth;
		m_LineStyleO = dlg.m_LineStyle0;

		Invalidate();
	}
}
void CIDWMMapView::OnUpdateOptionCoastzonesstyle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_LineO);
}

int CIDWMMapView::WarmColdSea(double RLON,double RLAT) 
{
	int nFlag = 0;  //"Cold Sea"

	if ((((RLON>=2.0 && RLON<=42.0)&&(RLAT>=30.0 && RLAT<=48.0))||
		((RLON>=-5.6 && RLON<=2.0)&&(RLAT>=30.0 && RLAT<=42.0)))||(RLAT<=30.0))
		nFlag = 1;  // "Warm Sea"

	return nFlag;
}


void CIDWMMapView::DrawVectorGE(CDC *pDC,int plan,float RLONLL, float RLATLL, float RLONUR, float RLATUR,
							int nWidth,COLORREF crColor, int nStyle) 
{
	long i1 = 0, i = 0;	
	double pi=4.*atan(1.);
	
	CPen pen(nStyle, nWidth, crColor); 
	CPen* pOldPen = pDC->SelectObject(&pen);

	long N = plan,IER;
	GEOPRMS(&N, &IER);

	long IVAL = 1,IRANGE = 1500;
	float WND[2][2] = {RLONLL, RLATLL, RLONUR, RLATUR};
	GEOPRM( &IVAL, (float *)WND, &IRANGE);

	long ITYPE = 2, MAXCRD=6000 , NRCRD, IREST , NOMORE = FALSE;
	float *CRDARR;	CRDARR = new float[2*MAXCRD];
	CPoint *pp;		pp =new CPoint[MAXCRD];
	CPoint *pp1;	pp1=new CPoint[MAXCRD];
	while(!NOMORE)
	{
		GEOPRML(&ITYPE, (float *)WND, &MAXCRD, (float *)CRDARR, &NRCRD, &IREST, &NOMORE);
		for(long p=0;p<NRCRD;p++)
		{
			if(CRDARR[2*p]<-140)
			{
				LatLon2Point(CRDARR[2*p+1],CRDARR[2*p],&pp1[i1]);
				i1++;
			}
			else
			{
				LatLon2Point(CRDARR[2*p+1],CRDARR[2*p],&pp[i]);
				i++;
			}
		}//end for

		if(i1>0)
		{
			pDC->Polyline(pp1,i1);
			i1=0;
		}
		pDC->Polyline(pp,i);
		i=0;

	}//end while

	pDC->SelectObject(pOldPen);
	delete [] pp;
	delete [] pp1;
	delete [] CRDARR;
}

void CIDWMMapView::OnOptionPropagationzonesSt61() 
{
	m_LinePR = 1;
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionPropagationzonesSt61(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LinePR==1);
}

void CIDWMMapView::OnOptionPropagationzonesGe84() 
{
	m_LinePR = 2;
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionPropagationzonesGe84(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LinePR==2);
}

void CIDWMMapView::OnOptionPropagationzonesGe89() 
{
	m_LinePR = 3;
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionPropagationzonesGe89(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LinePR==3);
}

void CIDWMMapView::OnOptionPropagationzonesGe2004() 
{
	m_LinePR = 4;
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionPropagationzonesGe2004(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LinePR==4);
}

void CIDWMMapView::OnOptionPropagationzonesClearfromdisplay() 
{
	m_LinePR = 0;
	InvalidateRect(NULL,FALSE);
}
void CIDWMMapView::OnUpdateOptionPropagationzonesClearfromdisplay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_LinePR>0);
}

void CIDWMMapView::OnOptionPropagationzonesstyle() 
{
	CBorderStyleDLG dlg;
	dlg.m_color1 = m_LineColorPR;
	dlg.m_LineColorRed = GetRValue(m_LineColorPR);
	dlg.m_LineColorGreen = GetGValue(m_LineColorPR);
	dlg.m_LineColorBlue = GetBValue(m_LineColorPR);
	dlg.m_LineWidth = m_LineWidthPR;
	dlg.m_LineStyle0 = m_LineStylePR;

	if ( dlg.DoModal()==IDOK )
	{
		m_LineColorPR = dlg.m_color1;
		m_LineWidthPR = dlg.m_LineWidth;
		m_LineStylePR = dlg.m_LineStyle0;

		InvalidateRect(NULL,FALSE);
	}	
}
void CIDWMMapView::OnUpdateOptionPropagationzonesstyle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_LinePR>0);
}




////////////////////////////APP 7/////////////////////////

int CIDWMMapView::AP28_MakeTXT(CString PathFileName) 
{
	CAP7EarthStationDLG dataDLG;
	dataDLG.m_DataBaseFlag = 1;	// local database

	if(dataDLG.DoModal() == IDOK)
	{
		CString strNTC = dataDLG.m_Notice;
		CString strBEM = dataDLG.m_Beam;
		CString strGRP = dataDLG.m_Group;
		CString strTxRx = dataDLG.m_TxRx;
		strTxRx = (strTxRx==_T("Tx")) ? _T("E") : _T("R");

		BOOL bNTC = strNTC.IsEmpty();
		BOOL bBEM = strBEM.IsEmpty();
		BOOL bGRP = strGRP.IsEmpty();

		CString CTY = dataDLG.m_Ctry;

		CString strSQT;
//		if((bNTC==0)&&(bBEM==1)&&(bGRP==1))			strSQT.Format("select * from EarthStationAp71 WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld));",CTY,atol(strNTC));
//		else if((bNTC==0)&&(bBEM==0)&&(bGRP==1))	strSQT.Format("select * from EarthStationAp71 WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\'));",CTY,atol(strNTC),strBEM,strTxRx);
//		else if((bNTC==0)&&(bBEM==0)&&(bGRP==0))	strSQT.Format("select * from EarthStationAp71 WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\') AND ((grp_id)=%ld));",CTY,atol(strNTC),strBEM,strTxRx,atol(strGRP));
//		else	return 0;
/*
		//Query EarthStationAp71
		CString str1 = _T(" ( SELECT e_stn.ctry, e_stn.ntc_id, e_ant.beam_name, grp.grp_id, e_ant.emi_rcp, e_stn.long_dec, e_stn.lat_dec, e_stn.stn_name, e_stn.long_nom, e_stn.sat_name, e_stn.elev_min, e_stn.diag_hor, e_stn.azm_fr, e_stn.azm_to, e_ant.gain, grp.noise_t, grp.pwr_max, grp.bdwdth, grp.freq_min, grp.freq_max, emiss.seq_no, emiss.design_emi, emiss.pwr_tot_pk, emiss.pwr_ds_max, ant_type.pattern, ant_type.coefa, ant_type.coefb, ant_type.coefc, ant_type.coefd, ant_type.phi1 ");
		CString str2 = _T(" FROM (((e_stn INNER JOIN e_ant ON e_stn.ntc_id = e_ant.ntc_id) INNER JOIN grp ON (e_ant.beam_name = grp.beam_name) AND (e_ant.emi_rcp = grp.emi_rcp) AND (e_ant.ntc_id = grp.ntc_id)) LEFT JOIN emiss ON grp.grp_id = emiss.grp_id) LEFT JOIN ant_type ON e_ant.pattern_id = ant_type.pattern_id ");
		CString str3 = _T(" WHERE (((e_stn.long_dec) Is Not Null))  )  as EarthStationAp7 ");
		CString qEarthStationAp7 = str1+str2+str3;
		CString str4 = _T(" ( SELECT DISTINCT ctry, ntc_id, beam_name, grp_id, emi_rcp, long_dec, lat_dec, stn_name, long_nom, sat_name, elev_min, diag_hor, azm_fr, azm_to, gain, noise_t, pwr_max, bdwdth, freq_min, freq_max, pattern, coefa, coefb, coefc, coefd, phi1, Max(pwr_ds_max) AS MaxOfpwr_ds_max ");
		CString str5;
		str5.Format(_T(" FROM %s  "), qEarthStationAp7);
		CString str6 = _T(" GROUP BY ctry, ntc_id, beam_name, grp_id, emi_rcp, long_dec, lat_dec, stn_name, long_nom, sat_name, elev_min, diag_hor, azm_fr, azm_to, gain, noise_t, pwr_max, bdwdth, freq_min, freq_max, pattern, coefa, coefb, coefc, coefd, phi1 ");
		CString str7 = _T(" ORDER BY grp_id  )  as EarthStationAp71 ");
		CString qEarthStationAp71 = str4+str5+str6+str7;
		if((bNTC==0)&&(bBEM==1)&&(bGRP==1))			strSQT.Format(_T("select * from %s WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld));"),qEarthStationAp71,CTY,atol(strNTC));
		else if((bNTC==0)&&(bBEM==0)&&(bGRP==1))	strSQT.Format(_T("select * from %s WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\'));"),qEarthStationAp71,CTY,atol(strNTC),strBEM,strTxRx);
		else if((bNTC==0)&&(bBEM==0)&&(bGRP==0))	strSQT.Format(_T("select * from %s WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\') AND ((grp_id)=%ld));"),qEarthStationAp71,CTY,atol(strNTC),strBEM,strTxRx,atol(strGRP));
		else	return 0;
*/
		//Query EarthStationAp71
//		CString str1 = _T(" ( SELECT e_stn.ctry, e_stn.ntc_id, e_ant.beam_name, grp.grp_id, e_ant.emi_rcp, e_stn.long_dec, e_stn.lat_dec, e_stn.stn_name, e_stn.long_nom, e_stn.sat_name, e_stn.elev_min, e_stn.diag_hor,  e_stn.azm_fr, e_stn.azm_to, e_ant.gain, grp.noise_t, grp.pwr_max, grp.bdwdth, grp.freq_min, grp.freq_max, emiss.seq_no, emiss.design_emi, emiss.pwr_tot_pk, emiss.pwr_ds_max, ant_type.pattern, ant_type.coefa, ant_type.coefb, ant_type.coefc, ant_type.coefd, ant_type.phi1 ");
		CString str1 = _T(" ( SELECT e_stn.ctry, e_stn.ntc_id, e_ant.beam_name, grp.grp_id, e_ant.emi_rcp, e_stn.long_dec, e_stn.lat_dec, e_stn.stn_name, e_stn.long_nom, e_stn.sat_name, e_stn.elev_min, e_stn.attch_hor, e_stn.azm_fr, e_stn.azm_to, e_ant.gain, grp.noise_t, grp.pwr_max, grp.bdwdth, grp.freq_min, grp.freq_max, emiss.seq_no, emiss.design_emi, emiss.pep_max,    emiss.pwr_ds_max, ant_type.pattern, ant_type.coefa, ant_type.coefb, ant_type.coefc, ant_type.coefd, ant_type.phi1 ");
		CString str2 = _T(" FROM (((e_stn INNER JOIN e_ant ON e_stn.ntc_id = e_ant.ntc_id) INNER JOIN grp ON (e_ant.beam_name = grp.beam_name) AND (e_ant.emi_rcp = grp.emi_rcp) AND (e_ant.ntc_id = grp.ntc_id)) LEFT JOIN emiss ON grp.grp_id = emiss.grp_id) LEFT JOIN ant_type ON e_ant.pattern_id = ant_type.pattern_id ");
		CString str3 = _T(" WHERE (((e_stn.long_dec) Is Not Null))  )  as EarthStationAp7 ");
		CString qEarthStationAp7 = str1+str2+str3;
//		CString str4 = _T(" ( SELECT DISTINCT ctry, ntc_id, beam_name, grp_id, emi_rcp, long_dec, lat_dec, stn_name, long_nom, sat_name, elev_min, diag_hor,  azm_fr, azm_to, gain, noise_t, pwr_max, bdwdth, freq_min, freq_max, pattern, coefa, coefb, coefc, coefd, phi1, Max(pwr_ds_max) AS MaxOfpwr_ds_max ");
		CString str4 = _T(" ( SELECT DISTINCT ctry, ntc_id, beam_name, grp_id, emi_rcp, long_dec, lat_dec, stn_name, long_nom, sat_name, elev_min, attch_hor, azm_fr, azm_to, gain, noise_t, pwr_max, bdwdth, freq_min, freq_max, pattern, coefa, coefb, coefc, coefd, phi1, Max(pwr_ds_max) AS MaxOfpwr_ds_max ");
		CString str5;
		str5.Format(_T(" FROM %s  "), qEarthStationAp7);
//		CString str6 = _T(" GROUP BY ctry, ntc_id, beam_name, grp_id, emi_rcp, long_dec, lat_dec, stn_name, long_nom, sat_name, elev_min, diag_hor,  azm_fr, azm_to, gain, noise_t, pwr_max, bdwdth, freq_min, freq_max, pattern, coefa, coefb, coefc, coefd, phi1 ");
		CString str6 = _T(" GROUP BY ctry, ntc_id, beam_name, grp_id, emi_rcp, long_dec, lat_dec, stn_name, long_nom, sat_name, elev_min, attch_hor, azm_fr, azm_to, gain, noise_t, pwr_max, bdwdth, freq_min, freq_max, pattern, coefa, coefb, coefc, coefd, phi1 ");
		CString str7 = _T(" ORDER BY grp_id  )  as EarthStationAp71 ");
		CString qEarthStationAp71 = str4+str5+str6+str7;
		if((bNTC==0)&&(bBEM==1)&&(bGRP==1))			strSQT.Format(_T("select * from %s WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld));"),qEarthStationAp71,CTY,atol(strNTC));
		else if((bNTC==0)&&(bBEM==0)&&(bGRP==1))	strSQT.Format(_T("select * from %s WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\'));"),qEarthStationAp71,CTY,atol(strNTC),strBEM,strTxRx);
		else if((bNTC==0)&&(bBEM==0)&&(bGRP==0))	strSQT.Format(_T("select * from %s WHERE (((ctry)=\'%s\') AND ((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\') AND ((grp_id)=%ld));"),qEarthStationAp71,CTY,atol(strNTC),strBEM,strTxRx,atol(strGRP));
		else	return 0;

		CString PathFileNametemp =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("R1448\\temp7.tmp");
		FILE *fptemp=fopen(PathFileNametemp,"wt");

		FILE *fp=fopen(PathFileName,"wt");
		if(fp)
		{
			float pi = (float)(4.0*atan(1.0));
			CDatabase DB;

			int m_DataBaseFlag = 1;	// local database
			if(m_DataBaseFlag==0)
				DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
			else
				DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

			CRecordset m_rs;
			CDBVariant Fld;
			m_rs.m_pDatabase=&DB;
			m_rs.Open( CRecordset::snapshot, strSQT);
			while(1)
			{
				if(m_rs.IsEOF()) break;

				m_rs.GetFieldValue((short)1,Fld);	long ntc_id    = Fld.m_lVal;

				CString beamName;
				m_rs.GetFieldValue((short)2,beamName);

				m_rs.GetFieldValue((short)3,Fld);	long grp_id    = Fld.m_lVal;
				CString emi_rcp;		m_rs.GetFieldValue((short)4,emi_rcp);	

				m_rs.GetFieldValue((short)5,Fld);	float lon = Fld.m_fltVal;
				m_rs.GetFieldValue((short)6,Fld);	float lat = Fld.m_fltVal;
				CString ESTN;		m_rs.GetFieldValue((short)7,ESTN);	

				CString long_nomSTR;	m_rs.GetFieldValue((short)8,long_nomSTR);	
				CString SAT;		m_rs.GetFieldValue((short)9,SAT);	

				m_rs.GetFieldValue((short)10,Fld);	float MINELA = Fld.m_fltVal;

				m_rs.GetFieldValue((short)12,Fld);	float azm_fr = Fld.m_fltVal;
				m_rs.GetFieldValue((short)13,Fld);	float azm_to = Fld.m_fltVal;
				m_rs.GetFieldValue((short)14,Fld);	float gain = Fld.m_fltVal;
				m_rs.GetFieldValue((short)15,Fld);	long ESNOISE = Fld.m_lVal;

				CString freq_minSTR;	m_rs.GetFieldValue((short)18,freq_minSTR);	
				CString freq_maxSTR;	m_rs.GetFieldValue((short)19,freq_maxSTR);	
				double freq_min = atof(freq_minSTR);
				double freq_max = atof(freq_maxSTR);

				if((freq_minSTR.IsEmpty()) || (freq_maxSTR.IsEmpty()))
					AP28_SRSfreq(grp_id, &freq_min , &freq_max) ;

				CString PATTERN;	m_rs.GetFieldValue((short)20,PATTERN);	
				CString COEFA;		m_rs.GetFieldValue((short)21,COEFA);	
				CString COEFB;		m_rs.GetFieldValue((short)22,COEFB);	
				CString COEFC;		m_rs.GetFieldValue((short)23,COEFC);	
				CString COEFD;		m_rs.GetFieldValue((short)24,COEFD);	
				CString PHI1;		m_rs.GetFieldValue((short)25,PHI1);	

				m_rs.GetFieldValue((short)26,Fld);	float POWRDENS = Fld.m_fltVal;

				float RLON=lon*pi/180.f, RLAT=lat*pi/180.f;
				CString ESCOORDS;	CRADDG4(&RLON, &RLAT, (BYTE *)ESCOORDS.GetBufferSetLength(15));

				CString ADM;	GEOCTYA((BYTE *)CTY.GetBufferSetLength(3), (BYTE *)ADM.GetBufferSetLength(3));

				double MINRCVFRMHZ = (emi_rcp==_T("R")) ? freq_min : 0.0;
				double MAXRCVFRMHZ = (emi_rcp==_T("R")) ? freq_max : 0.0;
				double MINTRNFRMHZ = (emi_rcp==_T("E")) ? freq_min : 0.0;
				double MAXTRNFRMHZ = (emi_rcp==_T("E")) ? freq_max : 0.0;
				double TRANANTG = (emi_rcp==_T("E")) ? gain : 0.0;
				double RECVANTG = (emi_rcp==_T("R")) ? gain : 0.0;

				int RADPATRN;


				CString OffAng,AntGain;
				long NUM = ESantUser(ntc_id, beamName, emi_rcp, &OffAng, &AntGain);
				if(NUM>0)
				{
					RADPATRN = 4;
					COEFA = _T("");
					COEFB = _T("");
					COEFC = _T("");
					COEFD = _T("");
					PHI1 = _T("");
				}
				else
				{
					if((PATTERN==_T("AP28"))||(PATTERN==_T("AP8"))||(PATTERN==_T("AP29")))
						RADPATRN = 1;
					else if((!COEFA.IsEmpty())&&(!COEFB.IsEmpty())&&(COEFC.IsEmpty())&&(COEFD.IsEmpty())&&(PHI1.IsEmpty())
																							&&(PATTERN==_T("A-B*LOG(FI)")))
						RADPATRN = 2;
					else if((!COEFA.IsEmpty())&&(!COEFB.IsEmpty())&&(COEFC.IsEmpty())&&(COEFD.IsEmpty())&&(!PHI1.IsEmpty())
																							&&(PATTERN==_T("A-B*LOG(FI)")))
						RADPATRN = 3;
					else if((!COEFA.IsEmpty())&&(!COEFB.IsEmpty())&&(!COEFC.IsEmpty())&&(!COEFD.IsEmpty())&&(!PHI1.IsEmpty())
																										&&(PATTERN.IsEmpty()))
						RADPATRN = 5;
					else if((PATTERN==_T("AP7"))||(PATTERN==_T("REC-1448")))
						RADPATRN = 6;
					else if(PATTERN==_T("REC-465"))
						RADPATRN = 7;
					else if((!COEFA.IsEmpty())&&(COEFB.IsEmpty())&&(COEFC.IsEmpty())&&(COEFD.IsEmpty())&&(PHI1.IsEmpty())
																							&&(PATTERN==_T("A-25*LOG(FI)")))
						RADPATRN = 7;
					else if((COEFA.IsEmpty())&&(COEFB.IsEmpty())&&(COEFC.IsEmpty())&&(COEFD.IsEmpty())&&(PHI1.IsEmpty())
																							&&(PATTERN==_T("A-25*LOG(FI)")))
						RADPATRN = 7;
					else if(PATTERN==_T("AP30A"))
						RADPATRN = 8;
					else if(PATTERN==_T("REC-1295"))
						RADPATRN = 9;
					else if(PATTERN==_T("REC-580"))
						RADPATRN = 10;
					else if(PATTERN==_T("ND"))
					{
						RADPATRN = 4;
						fprintf(fp,"OPT4NPTS = 2,\n");
						fprintf(fp,"OPT4OFFANG = 0.0,180.0,\n");
						fprintf(fp,"OPT4ANTGAIN = 0.0,0.0,\n");
					}
					else
					{
						RADPATRN = 7;
						COEFA = _T("32");
						COEFB = _T("");
						COEFC = _T("");
						COEFD = _T("");
						PHI1 = _T("");
					}

					/*
					if((PATTERN==_T("AP8"))||(PATTERN==_T("AP29")))
						RADPATRN = 1;
					else if((!COEFA.IsEmpty())&&(!COEFB.IsEmpty())&&(COEFC.IsEmpty())&&(COEFD.IsEmpty())&&(PHI1.IsEmpty()))
						RADPATRN = 2;
					else if((!COEFA.IsEmpty())&&(!COEFB.IsEmpty())&&(COEFC.IsEmpty())&&(COEFD.IsEmpty())&&(!PHI1.IsEmpty()))
						RADPATRN = 3;
					else if(PATTERN==_T("ND"))
					{
						RADPATRN = 4;
						fprintf(fp,"OPT4NPTS = 2,\n");
						fprintf(fp,"OPT4OFFANG = 0.0,180.0,\n");
						fprintf(fp,"OPT4ANTGAIN = 0.0,0.0,\n");
					}
					else if((!COEFA.IsEmpty())&&(!COEFB.IsEmpty())&&(!COEFC.IsEmpty())&&(!COEFD.IsEmpty())&&(!PHI1.IsEmpty()))
						RADPATRN = 5;
					else if((PATTERN==_T("AP7"))||(PATTERN==_T("AP28"))||(PATTERN==_T("REC-1448")))
						RADPATRN = 6;
					else if(((!COEFA.IsEmpty())&&(COEFB.IsEmpty())&&(COEFC.IsEmpty())&&(COEFD.IsEmpty())&&(PHI1.IsEmpty()))||(PATTERN=="REC-465"))
						RADPATRN = 7;
					else if(PATTERN==_T("AP30A"))
						RADPATRN = 8;
					else if(PATTERN==_T("REC-1295"))
						RADPATRN = 9;
					else if(PATTERN==_T("REC-580"))
						RADPATRN = 10;
					else
					{
						RADPATRN = 10;
						COEFA = _T("32");
						COEFB = _T("");
						COEFC = _T("");
						COEFD = _T("");
						PHI1 = _T("");
					}
					*/

				}
				CString GEOSYNC = (long_nomSTR.IsEmpty()) ? _T("NO") : _T("YES");	//	long_nom==null NO  else YES

				CString BDIRPC = dataDLG.m_BDIRPC;
				CString RECVPC = dataDLG.m_RECVPC;
				CString TRANPC = dataDLG.m_TRANPC;
				CString SATEAST = dataDLG.m_SATEAST;
				CString SATWEST = dataDLG.m_SATWEST;
				CString INCLINATION = dataDLG.m_INCLINATION;
				CString GMIN = dataDLG.m_GMIN;				
				BOOL Manned = dataDLG.m_Manned;

				int SERVTYPE[10];
				int srvNUM = AP28_SRV(freq_min , freq_max, grp_id ,Manned, SERVTYPE) ;

		//		CString OffAng,AntGain;
		//		long NUM = ESantUser(ntc_id, beamName, emi_rcp, &OffAng, &AntGain);

				for(int k=0;k<srvNUM;k++)
				{
					fprintf(fptemp,"%ld  %ld  %s\n",ntc_id, grp_id , beamName);

					fprintf(fp,"NEWFORM\n");
					fprintf(fp,"%ld\n",grp_id);
					fprintf(fp,"&INPUT1\n");
					fprintf(fp,"PLOTSCALE = %g,\n",150.0);
					fprintf(fp,"SQSIDE = %g,\n",100.0);
					fprintf(fp,"AUXPRINT = 'NO',\n");
					fprintf(fp,"DEBUG = 'NO',\n");

					fprintf(fp,"GEOSYNC = '%s',\n",GEOSYNC);

					fprintf(fp,"ESTN = '%20s',\n",ESTN);
					fprintf(fp,"ESCOORDS = '%15s',\n",ESCOORDS);
					fprintf(fp,"SAT = '%20s',\n",SAT);
					fprintf(fp,"ADM = '%s',\n",ADM);
					fprintf(fp,"CTY = '%s',\n",CTY);
					fprintf(fp,"PHASE = '%1s',\n","D");		// =D   allways

					if(emi_rcp==_T("E"))
					{
						fprintf(fp,"MINTRNFRMHZ = %g,\n",MINTRNFRMHZ);
						fprintf(fp,"MAXTRNFRMHZ = %g,\n",MAXTRNFRMHZ);
						fprintf(fp,"TRANANTG = %g,\n",TRANANTG);

					}
					else
					{
						fprintf(fp,"MINRCVFRMHZ = %g,\n",MINRCVFRMHZ);
						fprintf(fp,"MAXRCVFRMHZ = %g,\n",MAXRCVFRMHZ);
						fprintf(fp,"RECVANTG = %g,\n",RECVANTG);
					}
					fprintf(fp,"POWRDENS = %g,\n",POWRDENS);
					fprintf(fp,"ESNOISE = %ld,\n",ESNOISE);
					fprintf(fp,"SERVTYPE = %d,\n",SERVTYPE[k]);

					int i;
					float azm[720],elev_ang[720],hor_dist[720];

					long NUMELEVPAIR = AP28_SRShor_elev(ntc_id,azm,elev_ang,hor_dist); 
					if(NUMELEVPAIR>0)
					{
						fprintf(fp,"NUMELEVPAIR = %ld,\n",NUMELEVPAIR);	//	number of elevation pairs in hor_elev table
						fprintf(fp,"AZIMS = ");					// azm->hor_elev 
						for( i=0 ; i<NUMELEVPAIR ; i++)			fprintf(fp,"%g,",azm[i]);
						fprintf(fp,",\n");

						fprintf(fp,"HORELVS = ");				// elev_ang->hor_elev 
						for( i=0 ; i<NUMELEVPAIR ; i++)			fprintf(fp,"%g,",elev_ang[i]);
						fprintf(fp,",\n");

						fprintf(fp,"HORDIST = ");				// hor_dist->hor_elev 
						for( i=0 ; i<NUMELEVPAIR ; i++)			fprintf(fp,"%g,",hor_dist[i]);
						fprintf(fp,",\n");
					}
					else
					{
						fprintf(fp,"NUMELEVPAIR = %ld,\n",2);
						fprintf(fp,"AZIMS = 0.0,180.0,\n"); 
						fprintf(fp,"HORELVS = 0.0,0.0,\n");
					}

					long NUMMINELEV = AP28_SRSe_ant_elev(ntc_id,elev_ang); 
					if(NUMMINELEV>0)
					{
						fprintf(fp,"NUMMINELEV = %ld,\n",NUMMINELEV);	//	number of elevation pairs in e_ant_elev table
						fprintf(fp,"MINELEVATIONS = ");			// elev_ang->e_ant_elev 
						for( i=0 ; i<NUMMINELEV ; i++)			fprintf(fp,"%g,",elev_ang[i]);
						fprintf(fp,",\n");
					}
					fprintf(fp,"COEFA = %s,\n",COEFA);	
					fprintf(fp,"COEFB = %s,\n",COEFB);
					fprintf(fp,"COEFC = %s,\n",COEFC);	
					fprintf(fp,"COEFD = %s,\n",COEFD);
					fprintf(fp,"PHI1 = %s,\n",PHI1);

					if(NUM>0)
					{
						fprintf(fp,"OPT4NPTS = %d,\n",NUM);
						fprintf(fp,"OPT4OFFANG = %s\n",OffAng);
						fprintf(fp,"OPT4ANTGAIN = %s\n",AntGain);
						RADPATRN = 4;
					}
					fprintf(fp,"RADPATRN = %d,\n",RADPATRN);

					if(BDIRPC.GetLength() >0)	fprintf(fp,"BDIRPC = %s,\n",BDIRPC);
					if(RECVPC.GetLength() >0)	fprintf(fp,"RECVPC = %s,\n",RECVPC);
					if(TRANPC.GetLength() >0)	fprintf(fp,"TRANPC = %s,\n",TRANPC);
					
					if(GEOSYNC==_T("YES"))
					{
						if((SATEAST.GetLength() >0)&&(SATWEST.GetLength() >0))
						{
							fprintf(fp,"SATEAST = %s,\n",SATEAST);
							fprintf(fp,"SATWEST = %s,\n",SATWEST);
						}
						else
							fprintf(fp,"SATLONG = %s,\n",long_nomSTR);
					}
					if(INCLINATION.GetLength() >0)		fprintf(fp,"INCLINATION = %s,\n",INCLINATION);
					
					fprintf(fp,"GMIN = %s,\n",GMIN);

					if(MINELA>0)	fprintf(fp,"MINELA = %g,\n",MINELA);

					fprintf(fp,"SECTOR = %g,%g,\n",azm_fr,azm_to);

					fprintf(fp,"AUXPLOT = ");	// it is fixed
					fprintf(fp,"%g,",-60.0);
					fprintf(fp,"%g,",-50.0);
					fprintf(fp,"%g,",-40.0);
					fprintf(fp,"%g,",-30.0);
					fprintf(fp,"%g,",-20.0);
					fprintf(fp,"%g,\n",-10.0);

					fprintf(fp,"AUXPRINT = '%s',\n",_T("NO"));
					fprintf(fp,"/\n");

				}	// end for k (SERVTYPE)
				m_rs.MoveNext();
			}
			m_rs.Close();
			DB.Close();

			fclose(fp);
			fclose(fptemp);

			return 1;
		}//end if
		else 
			return 0;
	}
	else 
		return 0;
}

int CIDWMMapView::AP28_SRV(double Fmin,double Fmax,long grp_id,BOOL Manned,int *SRVtype) 
{
	CString stn_cls[1000];
	long stn_clsNUM = AP28_SRSsrv_cls(grp_id,stn_cls) ;

	int Si[1000];
	BOOL z1,z2,z3,z4,z5,z6,z7,z8,z9,z10,z11,z12,z13,z14,z15,z16,z17,z18,z19,z20,z21;

	z1  = AP28_BandOverlap(Fmin ,Fmax, 2200.0 , 2290.0) ;
	z2  = AP28_BandOverlap(Fmin ,Fmax, 1525.0 , 1535.0) ;
	z3  = AP28_BandOverlap(Fmin ,Fmax, 400.15 , 401.0) ;
	z4  = AP28_BandOverlap(Fmin ,Fmax, 37000.0 , 38000.0) ;
	z5  = AP28_BandOverlap(Fmin ,Fmax, 1700.0 , 1710.0) ;
	z6  = AP28_BandOverlap(Fmin ,Fmax, 25500.0 , 27000.0) ;
	z7  = AP28_BandOverlap(Fmin ,Fmax, 7750.0 , 7850.0) ;
	z8  = AP28_BandOverlap(Fmin ,Fmax, 7450.0 , 7550.0) ;
	z9  = AP28_BandOverlap(Fmin ,Fmax, 1670.0 , 1710.0) ;
	z10 = AP28_BandOverlap(Fmin ,Fmax, 31800.0 , 32300.0) ;
	z11 = AP28_BandOverlap(Fmin ,Fmax, 2290.0 , 2300.0) ;
	z12 = AP28_BandOverlap(Fmin ,Fmax, 2483.5 , 2500.0) ;
	z13 = AP28_BandOverlap(Fmin ,Fmax, 2160.0 , 2200.0) ;
	z14 = AP28_BandOverlap(Fmin ,Fmax, 1555.0 , 1559.0) ;
	z15 = AP28_BandOverlap(Fmin ,Fmax, 1490.0 , 1530.0) ;
	z16 = AP28_BandOverlap(Fmin ,Fmax, 10700.0 , 12750.0) ;
	z17 = AP28_BandOverlap(Fmin ,Fmax, 17700.0 , 18800.0) ;
	z18 = AP28_BandOverlap(Fmin ,Fmax, 18800.0 , 19300.0) ;
	z19 = AP28_BandOverlap(Fmin ,Fmax, 19300.0 , 19700.0) ;
	z20 = AP28_BandOverlap(Fmin ,Fmax, 37500.0 , 40500.0) ;
	z21 = AP28_BandOverlap(Fmin ,Fmax, 12500.0 , 12750.0) ;

	for(long i=0;i<stn_clsNUM;i++)
	{
		if(( (stn_cls[i] == "TD") || (stn_cls[i] == "TK") || (stn_cls[i] == "TR") || (stn_cls[i] == "TT") || (stn_cls[i] == "UD") || (stn_cls[i] == "UK") || (stn_cls[i] == "UR") || (stn_cls[i] == "UT") ) && (z1 || z2 || z3))
			Si[i] = 1;
		else if(( (stn_cls[i] == "TH") || (stn_cls[i] == "UH") ) && (z3))
			Si[i] = 2;
		else if(( (stn_cls[i] == "TH") || (stn_cls[i] == "UH") ) && (z4 || z1 || z5))
		{
			if(Manned)
				Si[i] = 6;
			else
				Si[i] = 2;
		}
		else if(( (stn_cls[i] == "TW") || (stn_cls[i] == "UW") ) && (z1 || z6))
			Si[i] = 3;
		else if(( (stn_cls[i] == "TM") || (stn_cls[i] == "UM") ) && (z3 || z7 || z8 || z9))
			Si[i] = 4;
		else if(( (stn_cls[i] == "TH") || (stn_cls[i] == "UH") ) && (z10 || z11))
			Si[i] = 5;
		else if(( (stn_cls[i] == "TB") || (stn_cls[i] == "TG") || (stn_cls[i] == "TI") || (stn_cls[i] == "TJ") || (stn_cls[i] == "TU") || (stn_cls[i] == "TY") || (stn_cls[i] == "UA") || (stn_cls[i] == "VA") ) && (z12 || z13 || z14 || z15))
			Si[i] = 7;
		else if(( (stn_cls[i] == "TB") || (stn_cls[i] == "TC") || (stn_cls[i] == "TY") || (stn_cls[i] == "VA") ) && (z16 || z17 || z18 || z19 || z20))
			Si[i] = 8;
		else if(( (stn_cls[i] == "UB") || (stn_cls[i] == "UV") ) && (z21))
			Si[i] = 9;
		else
			Si[i] = 0;
	}

	int S1[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	for(int j=0;j<stn_clsNUM;j++)
		S1[Si[j]] = Si[j];

	int k=0;
	for( j=0;j<10;j++)
	{
		if(S1[j]!=-1)
		{
			SRVtype[k] = S1[j];
			k++;
		}
	}

	return k;
}


BOOL CIDWMMapView::AP28_BandOverlap(double Fmin,double Fmax,double F1,double F2) 
{
	BOOL Overlap = FALSE;

	if((Fmax<F1)||(Fmin>F2))
		Overlap = FALSE;
	else if(((Fmax>=F1) && (Fmax<=F2))||((Fmin>=F1) && (Fmin<=F2)))
		Overlap = TRUE;
	return Overlap;
}

long CIDWMMapView::AP28_SRSsrv_cls(long grp_id,CString *stn_cls) 
{
	CString table = _T("srv_cls");
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CString Fld;

	int m_DataBaseFlag = 1;	// local database
	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

	m_Tbl.Format("select DISTINCT stn_cls FROM %s WHERE (((grp_id)=%ld));",table,grp_id);
	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;

	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,Fld);	stn_cls[i] = Fld;	
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}

long CIDWMMapView::AP28_SRSfreq(long grp_id,double *freq_min,double *freq_max) 
{
	CString table = _T("freq");
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CDBVariant Fld;

	int m_DataBaseFlag = 1;	// local database
	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);
	m_Tbl.Format("select freq_mhz,bdwdth FROM %s WHERE (((grp_id)=%ld));",table,grp_id);
	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;
	double freq_mhz;	long bdwdth;

	double freq_min0 = 9999999.0, freq_max0 = -9999999.0;

	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,Fld);			freq_mhz = Fld.m_dblVal;
			m_rs.GetFieldValue((short)1,Fld);			bdwdth = Fld.m_lVal;

			freq_min0 = min(freq_min0,freq_mhz-bdwdth/2000.0);
			freq_max0 = max(freq_max0,freq_mhz+bdwdth/2000.0);

			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	*freq_min = freq_min0;
	*freq_max = freq_max0;


	return i;
}





long CIDWMMapView::AP28_SRShor_elev(long ntc_id,float *azm,float *elev_ang,float *hor_dist) 
{
	CString table = _T("hor_elev");
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CDBVariant Fld;

	int m_DataBaseFlag = 1;	// local database
	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

	m_Tbl.Format("select * FROM %s WHERE (((ntc_id)=%ld)) ORDER BY azm;",table,ntc_id);
	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;
	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)1,Fld);	azm[i] = Fld.m_fltVal;
			m_rs.GetFieldValue((short)2,Fld);	elev_ang[i] = Fld.m_fltVal;
			m_rs.GetFieldValue((short)3,Fld);	hor_dist[i] = Fld.m_fltVal;
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}
long CIDWMMapView::AP28_SRSe_ant_elev(long ntc_id,float *elev_ang) 
{
	CString table = _T("hor_elev");
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CDBVariant Fld;

	int m_DataBaseFlag = 1;	// local database
	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

	m_Tbl.Format("select * FROM %s WHERE (((ntc_id)=%ld)) ORDER BY azm;",table,ntc_id);
	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;
	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)2,Fld);	elev_ang[i] = Fld.m_fltVal;
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}


void CIDWMMapView::AP28_MakeUPD(CString FileName) 
{
	SHELLEXECUTEINFO info;
	info.cbSize = sizeof(SHELLEXECUTEINFO);
	info.hwnd = NULL;
	info.nShow = SW_SHOW;
	info.hInstApp = NULL;
	info.fMask = NULL;
	info.lpVerb = NULL;
	info.lpParameters = NULL;
	info.lpDirectory = m_R1448Path;
	info.lpFile=_T("r1448.exe");
	ShellExecuteEx(&info);

	HWND  hwnd =::FindWindowEx(NULL, NULL, _T("ConsoleWindowClass"),m_R1448Path + _T("\\r1448.exe"));
	
	::SetForegroundWindow(hwnd);
	Sleep(500);
	UpdateData(true);
	AP28_SendString(FileName);
}
void CIDWMMapView::AP28_SendString(CString String)
{
	char VK,InpCode;
	for(int i=0;i<String.GetLength();i++)
	{
		InpCode = String.GetAt(i);
		if(InpCode==':' || InpCode=='_' || InpCode=='(' || InpCode==')')
			keybd_event(VK_SHIFT , 0xB6,  0, 0);

		VK = (char)VkKeyScan(String.GetAt(i));

		keybd_event(VK, 0,  0, 0);
		keybd_event(VK, 0,  KEYEVENTF_KEYUP, 0);
		if(InpCode==':' || InpCode=='_' || InpCode=='(' || InpCode==')')
			keybd_event(VK_SHIFT , 0xB6,  KEYEVENTF_KEYUP, 0);
	}
	keybd_event(VK_RETURN, 28,  0, 0);
	keybd_event(VK_RETURN, 28,  KEYEVENTF_KEYUP, 0);
}



void CIDWMMapView::AP28_ReadUPD() 
{
	CString m_antfile = m_R1448Path + _T("\\UPD.DAT");

	m_RowNum = 0;
	FILE *fid;
	if((fid=fopen(m_antfile,"rt"))!=NULL)
	{
		fseek(fid,0,SEEK_END);
		long file_size = ftell(fid);
		fseek(fid,0,SEEK_SET);

		CString strBUF,strA[816];
		char buf[4192];

		m_RowNum = file_size/4193;
		m_strout = "";

		for(int k=0;k<m_RowNum;k++)
		{
			fread(buf,4192,1,fid);
			strBUF = buf;
			int i, m, n;
											n=0;	m=3;
			strA[ 0] = strBUF.Left(m);		n=m+n;	m=20;
			strA[ 1] = strBUF.Mid(n,m);		n=m+n;	m=3; 
			strA[ 2] = strBUF.Mid(n,m);		n=m+n;	m=1; 
			strA[ 3] = strBUF.Mid(n,m);		n=m+n;	m=1; 
			strA[ 4] = strBUF.Mid(n,m);		n=m+n;	m=7; 
			strA[ 5] = strBUF.Mid(n,m);		n=m+n;	m=8; 
			strA[ 6] = strBUF.Mid(n,m);		n=m+n;	m=20; 
			strA[ 7] = strBUF.Mid(n,m);		n=m+n;	m=15; 
			strA[ 8] = strBUF.Mid(n,m);		n=m+n;	m=1; 
			strA[ 9] = strBUF.Mid(n,m);		n=m+n;	m=3; 
			strA[10] = strBUF.Mid(n,m);		n=m+n;	m=3; 
			strA[11] = strBUF.Mid(n,m);		n=m+n;	m=1; 
			strA[12] = strBUF.Mid(n,m);		n=m+n;	m=1; 
			strA[13] = strBUF.Mid(n,m);		n=m+n;	m=7; 
			strA[14] = strBUF.Mid(n,m);		n=m+n;	m=7; 
			strA[15] = strBUF.Mid(n,m);		n=m+n;	m=6; 

			m_strA1[k] = strA[ 1];
			m_strA8[k] = strA[ 8];

			for( i=0;i<71;i++)
			{
				strA[16+i] = strBUF.Mid(n,m);		n=m+n;	m=6; 
			}
			strA[87] = strBUF.Mid(n,m);		n=m+n;	m=7; 

			strA[88] = strBUF.Mid(n,m);		n=m+n;	m=8; 
			strA[89] = strBUF.Mid(n,m);		n=m+n;	m=5; 
			strA[90] = strBUF.Mid(n,m);		n=m+n;	m=8; 
			strA[91] = strBUF.Mid(n,m);		n=m+n;	m=7; 
			strA[92] = strBUF.Mid(n,m);		n=m+n;	m=7; 
			strA[93] = strBUF.Mid(n,m);		n=m+n;	m=8; 
			strA[94] = strBUF.Mid(n,m);		n=m+n;	m=8; 
			strA[95] = strBUF.Mid(n,m);		n=m+n;	m=5; 

		////////////////////////////////////////////////////////////////////// Method I
			for( i=0;i<72;i++)
			{
				strA[96+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
				m_CordDistI[k][i] = atoi(strA[96+i]);
			}
		////////////////////////////////////////////////////////////////////// Method II
			for( i=0;i<72;i++)
			{
				strA[168+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
				m_CordDistII[k][i] = atoi(strA[168+i]);
			}
		////////////////////////////////////////////////////////////////////// 0
			for( i=0;i<72;i++)
			{
				strA[240+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
			}
			for( i=0;i<72;i++)
			{
				strA[312+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
			}
		////////////////////////////////////////////////////////////////////// Method I-10
			for( i=0;i<72;i++)
			{
				strA[384+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
				m_CordDistI10[k][i] = atoi(strA[384+i]);	
			}
		////////////////////////////////////////////////////////////////////// Method I-20
			for( i=0;i<72;i++)
			{
				strA[456+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
				m_CordDistI20[k][i] = atoi(strA[456+i]);	
			}
		////////////////////////////////////////////////////////////////////// Method I-30
			for( i=0;i<72;i++)
			{
				strA[528+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
				m_CordDistI30[k][i] = atoi(strA[528+i]);	
			}
		////////////////////////////////////////////////////////////////////// Method I-40
			for( i=0;i<72;i++)
			{
				strA[600+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
				m_CordDistI40[k][i] = atoi(strA[600+i]);	
			}
		////////////////////////////////////////////////////////////////////// Method I-50
			for( i=0;i<72;i++)
			{
				strA[672+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
				m_CordDistI50[k][i] = atoi(strA[672+i]);	
			}
		////////////////////////////////////////////////////////////////////// Method I-60
			for( i=0;i<72;i++)
			{
				strA[744+i] = strBUF.Mid(n,m);		n=m+n;	m=5;
				m_CordDistI60[k][i] = atoi(strA[744+i]);	
			}
		//	m_strout = m_strout + strBUF.Left(82);
			m_strout = m_strout + strBUF.Left(82) + strA[94] + strA[95];

		}	// end for k
		fclose(fid);
	}	// end if fid
	else
	{
		m_S7=false;
		CString str;
		str.Format(_Z("\nRR Appendix 7 Output file (UPD.DAT) was not found.\t\nPlease generate this file through [%s] menu item.\t\n"), _Z("Option")+"->"+_Z("RR Appendix 7")+"->"+_Z("Earth Station Selection"));

		MessageBox(str, _Z("Warning!!!")+"         'UPD.DAT' ???",MB_ICONWARNING | MB_OK);
	}

}
void CIDWMMapView::AP28_DLG() 
{
	if(m_RowNum>0)
	{
		CAP7_CordContourDLG xx;
		xx.m_Data = m_strout;
		xx.m_Rows = m_RowNum;

		CString CTRYlist[1000];
		AP28_Affected_CTRY(CTRYlist);
		
		for(int i=0; i<m_RowNum;i++)
			xx.affected_CTRY[i] = CTRYlist[i];


		if(xx.DoModal() ==IDOK)
		{
			int i1=xx.m_NRow-1 , i2=xx.m_NRowsel-1;
			m_ifrom=min(i1,i2)  , m_ito=max(i1,i2);

			m_M1	= xx.m_M1;
			m_M2	= xx.m_M2;
			m_M1_10 = xx.m_M1_10;
			m_M1_20 = xx.m_M1_20;
			m_M1_30 = xx.m_M1_30;
			m_M1_40 = xx.m_M1_40;
			m_M1_50 = xx.m_M1_50;
			m_M1_60 = xx.m_M1_60;

		}	// end if IDOK
		else
			m_S7 = false;

	}	//	end if RowNum
}

void CIDWMMapView::AP28_Affected_CTRY(CString *CTRYlist) 
{
	char buf[5000];
	CString str0,str;
	int n=0;

	FILE *fid=fopen(m_R1448Path + _T("\\RESULT.LST"),"rt");
	if(fid)
	{
		while( !feof( fid ) )
		{
			fgets( buf, 5000,fid );
			str = buf;
			str0 = str.Mid(1,8);
			if(str0=="PROBABLY")
			{
				CTRYlist[n] = buf;
				n++;
			}
		}
	}
	fclose(fid);

	if(n>0)
	for(int i=0;i<n;i++)
	{
		CTRYlist[i] = CTRYlist[i].Mid(31);
		CTRYlist[i].TrimRight();
	}
}


void CIDWMMapView::AP28_Draw(CDC *pDC)
{
	if(m_S7)
	for(int i=m_ifrom;i<=m_ito;i++)
	{
		if(m_M1)	AP28_Draw_0(pDC,m_strA1[i],m_strA8[i], m_CordDistI[i]  , nWidth1, crColor1,  nStyle1);
		if(m_M2)	AP28_Draw_0(pDC,m_strA1[i],m_strA8[i], m_CordDistII[i] , nWidth2, crColor2,  nStyle2);
		if(m_M1_10)	AP28_Draw_0(pDC,m_strA1[i],m_strA8[i], m_CordDistI10[i], nWidth3, crColor3,  nStyle3);
		if(m_M1_20)	AP28_Draw_0(pDC,m_strA1[i],m_strA8[i], m_CordDistI20[i], nWidth4, crColor4,  nStyle4);
		if(m_M1_30)	AP28_Draw_0(pDC,m_strA1[i],m_strA8[i], m_CordDistI30[i], nWidth5, crColor5,  nStyle5);
		if(m_M1_40)	AP28_Draw_0(pDC,m_strA1[i],m_strA8[i], m_CordDistI40[i], nWidth6, crColor6,  nStyle6);
		if(m_M1_50)	AP28_Draw_0(pDC,m_strA1[i],m_strA8[i], m_CordDistI50[i], nWidth7, crColor7,  nStyle7);
		if(m_M1_60)	AP28_Draw_0(pDC,m_strA1[i],m_strA8[i], m_CordDistI60[i], nWidth8, crColor8,  nStyle8);
	}
}

void CIDWMMapView::AP28_Draw_0(CDC *pDC,CString Name,CString LatLon, long * dist,
								   int nWidth,COLORREF crColor, int nStyle) 
{
	int scale=1;
	if(pDC->IsPrinting())	scale=7;

	CPen pen(nStyle, nWidth*scale, crColor); 
	CPen* pOldPen = pDC->SelectObject(&pen);

	char a8[15];	strcpy(a8,LatLon);
	float LON, LAT , RLON, RLAT, rng_km1, az_deg1;
	CDGRAD4((unsigned char *)a8, &LON, &LAT);
//	double pi=4.0*atan(1.0);
	CPoint pp[73];
	for(int i=0;i<72;i++)
	{
		rng_km1 = (float)dist[i];		az_deg1 = 5.f*i;
		GEOPDAP( &LON, &LAT, &rng_km1, &az_deg1, &RLON, &RLAT);
		LatLon2Point(RLAT*180.0/pi,RLON*180.0/pi,&pp[i]);
	}
	pp[72] = pp[0];
	pDC->Polyline(pp,73);

	LatLon2Point(LAT*180.0/pi,LON*180.0/pi,&pp[0]);

	DrawSymboleStation(pDC,LAT*180.0/pi,LON*180.0/pi,m_LineColor7,4*scale); 

	Name.TrimLeft();
	pDC->SetBkMode(TRANSPARENT);
	TextDraw(pDC,pp[0].x+scale*5,pp[0].y-scale*5,Name,RGB(0,0,0),0,scale*12);

	pDC->SelectObject(pOldPen);
}

void CIDWMMapView::OnOptionRrappendix7Earthstationselection() 
{
	CString FileName = _T("App7_Input.txt");
	CString PathFileName = m_R1448Path + _T("\\") + FileName;

	int i = AP28_MakeTXT(PathFileName);	
	if(i==1)
		AP28_MakeUPD(FileName) ;
}

void CIDWMMapView::OnOptionRrappendix7Drawcontours() 
{
	bool S7 = m_S7;

	m_S7 = !m_S7;
	if(m_S7)
	{
		AP28_ReadUPD();
		AP28_DLG();
	}
	if(m_S7 != S7)
		InvalidateRect(NULL,false);	
}
void CIDWMMapView::OnUpdateOptionRrappendix7Drawcontours(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_S7);
}

void CIDWMMapView::OnOptionRrappendix7Style() 
{
	CAp7_StyleDLG dlg;
	dlg.m_color1 = crColor1;
	dlg.m_LineColorRed1 = GetRValue(crColor1);
	dlg.m_LineColorGreen1 = GetGValue(crColor1);
	dlg.m_LineColorBlue1 = GetBValue(crColor1);
	dlg.m_LineWidth1 = nWidth1;
	dlg.m_LineStyle01 = nStyle1;

	dlg.m_color2 = crColor2;
	dlg.m_LineColorRed2 = GetRValue(crColor2);
	dlg.m_LineColorGreen2 = GetGValue(crColor2);
	dlg.m_LineColorBlue2 = GetBValue(crColor2);
	dlg.m_LineWidth2 = nWidth2;
	dlg.m_LineStyle02 = nStyle2;

	dlg.m_color3 = crColor3;
	dlg.m_LineColorRed3 = GetRValue(crColor3);
	dlg.m_LineColorGreen3 = GetGValue(crColor3);
	dlg.m_LineColorBlue3 = GetBValue(crColor3);
	dlg.m_LineWidth3 = nWidth3;
	dlg.m_LineStyle03 = nStyle3;

	dlg.m_color4 = crColor4;
	dlg.m_LineColorRed4 = GetRValue(crColor4);
	dlg.m_LineColorGreen4 = GetGValue(crColor4);
	dlg.m_LineColorBlue4 = GetBValue(crColor4);
	dlg.m_LineWidth4 = nWidth4;
	dlg.m_LineStyle04 = nStyle4;

	dlg.m_color5 = crColor5;
	dlg.m_LineColorRed5 = GetRValue(crColor5);
	dlg.m_LineColorGreen5 = GetGValue(crColor5);
	dlg.m_LineColorBlue5 = GetBValue(crColor5);
	dlg.m_LineWidth5 = nWidth5;
	dlg.m_LineStyle05 = nStyle5;

	dlg.m_color6 = crColor6;
	dlg.m_LineColorRed6 = GetRValue(crColor6);
	dlg.m_LineColorGreen6 = GetGValue(crColor6);
	dlg.m_LineColorBlue6 = GetBValue(crColor6);
	dlg.m_LineWidth6 = nWidth6;
	dlg.m_LineStyle06 = nStyle6;

	dlg.m_color7 = crColor7;
	dlg.m_LineColorRed7 = GetRValue(crColor7);
	dlg.m_LineColorGreen7 = GetGValue(crColor7);
	dlg.m_LineColorBlue7 = GetBValue(crColor7);
	dlg.m_LineWidth7 = nWidth7;
	dlg.m_LineStyle07 = nStyle7;

	dlg.m_color8 = crColor8;
	dlg.m_LineColorRed8 = GetRValue(crColor8);
	dlg.m_LineColorGreen8 = GetGValue(crColor8);
	dlg.m_LineColorBlue8 = GetBValue(crColor8);
	dlg.m_LineWidth8 = nWidth8;
	dlg.m_LineStyle08 = nStyle8;

	if ( dlg.DoModal()==IDOK )
	{
		crColor1 = dlg.m_color1;
		nWidth1 = dlg.m_LineWidth1;
		nStyle1 = dlg.m_LineStyle01;

		crColor2 = dlg.m_color2;
		nWidth2 = dlg.m_LineWidth2;
		nStyle2 = dlg.m_LineStyle02;

		crColor3 = dlg.m_color3;
		nWidth3 = dlg.m_LineWidth3;
		nStyle3 = dlg.m_LineStyle03;

		crColor4 = dlg.m_color4;
		nWidth4 = dlg.m_LineWidth4;
		nStyle4 = dlg.m_LineStyle04;

		crColor5 = dlg.m_color5;
		nWidth5 = dlg.m_LineWidth5;
		nStyle5 = dlg.m_LineStyle05;

		crColor6 = dlg.m_color6;
		nWidth6 = dlg.m_LineWidth6;
		nStyle6 = dlg.m_LineStyle06;

		crColor7 = dlg.m_color7;
		nWidth7 = dlg.m_LineWidth7;
		nStyle7 = dlg.m_LineStyle07;

		crColor8 = dlg.m_color8;
		nWidth8 = dlg.m_LineWidth8;
		nStyle8 = dlg.m_LineStyle08;

		Invalidate();
	}	
}



void CIDWMMapView::OnUpdateOptionRrappendix7Style(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_S7);
}

void CIDWMMapView::OnOptionRrappendix7Viewinputfile() 
{
	CString PathFileName = m_R1448Path + _T("\\App7_Input.txt");
	ShellExecute(m_hWnd, "open", PathFileName, NULL, NULL, SW_SHOWNORMAL);
}

void CIDWMMapView::OnOptionRrappendix7Viewoutputfile() 
{
	CString PathFileName = m_R1448Path + _T("\\RESULT.LST");
	ShellExecute(m_hWnd,"Open","wordpad",PathFileName,NULL,SW_SHOWNORMAL);
}

void CIDWMMapView::OnOptionRrappendix7Viewoutputfile1() 
{
	CString PathFileName = m_R1448Path + _T("\\UPD.DAT");
	ShellExecute(m_hWnd,"Open","wordpad",PathFileName,NULL,SW_SHOWNORMAL);
}

void CIDWMMapView::DrawSymboleStation(CDC* pDC,double lats,double lons,COLORREF color1,int len1) 
{
	CPen penStation(PS_SOLID,1,color1);
	CPen *Oldpen=pDC->SelectObject(&penStation);
	CBrush brushStation(color1);
	CBrush *Oldbrush=pDC->SelectObject(&brushStation);

	CPoint points;
	LatLon2Point(lats,lons,&points);
	pDC->MoveTo(points.x-len1,points.y);
	pDC->LineTo(points.x+len1,points.y);
	pDC->MoveTo(points.x,points.y-3*len1);
	pDC->LineTo(points.x,points.y+3*len1);

	pDC->Arc(points.x-2*len1,points.y-5*len1,points.x+2*len1,points.y-1*len1,points.x-2*len1,points.y-3*len1,points.x+2*len1,points.y-3*len1);

	pDC->MoveTo(points.x-len1,points.y-len1);
	pDC->LineTo(points.x+len1,points.y-len1);
	pDC->LineTo(points.x+len1,points.y+len1);
	pDC->LineTo(points.x-len1,points.y+len1);
	pDC->LineTo(points.x-len1,points.y-len1);

	CPoint pointsBT[5];
	pointsBT[0]=CPoint(points.x-len1,points.y+len1);
	pointsBT[1]=CPoint(points.x+len1,points.y+len1);
	pointsBT[2]=CPoint(points.x+3*len1,points.y+3*len1);
	pointsBT[3]=CPoint(points.x-3*len1,points.y+3*len1);
	pointsBT[4]=pointsBT[0];
	pDC->Polygon(pointsBT,5);

	if(!pDC->IsPrinting())
	{
		pDC->SelectObject(&Oldpen);
		pDC->SelectObject(&Oldbrush);
	}

}

void CIDWMMapView::OnOptionRrappendix7Savevectors() 
{
	BeginWaitCursor();
	if(m_S7)
	for(int i=m_ifrom;i<=m_ito;i++)
	{
		CString str;
		str.Format("_%d",i);
		if(m_M1)
			AP28_Write_0(m_strA1[i]+_T("_I")+str,m_strA8[i], m_CordDistI[i]) ;
		if(m_M2)
			AP28_Write_0(m_strA1[i]+_T("_II")+str,m_strA8[i], m_CordDistII[i]) ;
		if(m_M1_10)
			AP28_Write_0(m_strA1[i]+_T("_I10")+str,m_strA8[i], m_CordDistI10[i]) ;
		if(m_M1_20)
			AP28_Write_0(m_strA1[i]+_T("_I20")+str,m_strA8[i], m_CordDistI20[i]) ;
		if(m_M1_30)
			AP28_Write_0(m_strA1[i]+_T("_I30")+str,m_strA8[i], m_CordDistI30[i]) ;
		if(m_M1_40)
			AP28_Write_0(m_strA1[i]+_T("_I40")+str,m_strA8[i], m_CordDistI40[i]) ;
		if(m_M1_50)
			AP28_Write_0(m_strA1[i]+_T("_I50")+str,m_strA8[i], m_CordDistI50[i]) ;
		if(m_M1_60)
			AP28_Write_0(m_strA1[i]+_T("_I60")+str,m_strA8[i], m_CordDistI60[i]) ;
	}
	EndWaitCursor();
}
void CIDWMMapView::OnUpdateOptionRrappendix7Savevectors(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_S7);
}


int CIDWMMapView::AP28_Write_0(CString Name,CString LatLon, long * dist) 
{
	char a8[15];	strcpy(a8,LatLon);
	float LON, LAT , RLON, RLAT, rng_km1, az_deg1;
	CDGRAD4((unsigned char *)a8, &LON, &LAT);
//	double pi=4.0*atan(1.0);

	Name.TrimLeft();	Name.TrimRight();
	CString AppPath = ((CSMS4DCApp *)AfxGetApp())->m_AppPath ;
	CString FilePath = AppPath + _T("Reports\\Ap7_") + Name + _T(".txt");

	FILE *fp=fopen(FilePath,"wt");
	if(fp)
	{
		for(int i=0;i<72;i++)
		{
			rng_km1 = (float)dist[i];		az_deg1 = 5.f*i;
			GEOPDAP( &LON, &LAT, &rng_km1, &az_deg1, &RLON, &RLAT);
			fprintf(fp,"%0.14f  %0.14f\n",RLON*180.0/pi,RLAT*180.0/pi);
		}
		rng_km1 = (float)dist[0];		az_deg1 = 0.f;
		GEOPDAP( &LON, &LAT, &rng_km1, &az_deg1, &RLON, &RLAT);
		fprintf(fp,"%0.14f  %0.14f\n",RLON*180.0/pi,RLAT*180.0/pi);
		fclose(fp);
		return 1;
	}//end if
	else 
		return 0;

}

/*
void CIDWMMapView::VectorCountry(CDC *pDC,CString cty,int nWidth,COLORREF crColor, int nStyle) 
{
	int i=0;
	CPoint *pp;			pp=new CPoint[200000];

	unsigned char CTYVEK[4]={""}, BCILR;
	strcpy((char *)CTYVEK,cty);

	float CRDARR[2*15000], DENS=0;
	long LINE, NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=30000;

	float RLONLL, RLATLL, RLONUR, RLATUR;
	GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);
	GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, (unsigned char *)CTYVEK);	

	CPen pen(nStyle, nWidth, crColor); 
	CPen* pOldPen = pDC->SelectObject(&pen);

	while(!NOMORE)
	{
		GEOLIW( &ITYPE, (float *)CRDARR, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
		if(NOMORE)	break;

		for(long p=0;p<NRCRD;p++)
		{
			LatLon2Point(CRDARR[2*p+1],CRDARR[2*p],&pp[i]);
			i++;
		}//end for
		pDC->Polyline(pp,i);
		i=0;

	}//end while
	pDC->SelectObject(pOldPen);
	delete [] pp;
}
*/


void CIDWMMapView::VectorCountry(CDC *pDC,CString cty,BOOL mode ,COLORREF crColor,int nWidth, int nStyle) 
{
	BOOL bRUS = FALSE;
	if(cty=="RUS")	bRUS = TRUE;

	int i=0,	i1=0;
	unsigned char CTYVEK[4]={""}, BCILR;
	strcpy((char *)CTYVEK,cty);

//	long LINE;
	long NRCRD, NOMORE=0, NRCTY=1, ITYPE=2, MAXCRD=15000;

	CPoint *pp;		pp = new CPoint[MAXCRD];
	CPoint *pp1;	pp1= new CPoint[MAXCRD/10];
	float *CRDARR;	CRDARR = new float[2*MAXCRD];

	float RLONLL, RLATLL, RLONUR, RLATUR, DENS=0;
	GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);

//	GEODWD( &RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, &NRCTY, CTYVEK);	
	GEODCW(&RLONLL, &RLATLL, &RLONUR, &RLATUR, &DENS, CTYVEK);

	CPen pen(nStyle, nWidth, crColor); 
	CPen* pOldPen = pDC->SelectObject(&pen);
	while(!NOMORE)
	{
//		GEOLIW( &ITYPE, (float *)CRDARR, &MAXCRD, &LINE, &NRCRD, &BCILR, &NOMORE);
		GEOCIW(&ITYPE, (float *)CRDARR, &MAXCRD, &NRCRD, &BCILR, &NOMORE);

		if(NOMORE)	break;
		for(long p=0;p<NRCRD;p++)
		{
			if((bRUS)&&(CRDARR[2*p]<19))
			{
				LatLon2Point(CRDARR[2*p+1],CRDARR[2*p],&pp1[i1]);
				i1++;
			}
			else
			{
				LatLon2Point(CRDARR[2*p+1],CRDARR[2*p],&pp[i]);
				i++;
			}

		}//end for

		if(mode==1)
		{
			pDC->Polyline(pp,i);
			if(i1 > 0)	pDC->Polyline(pp1,i1);
		}
		else if(mode==2)
		{
			CRgn rgn;
			rgn.CreatePolygonRgn(pp,i, WINDING);
			pDC->FillRgn(&rgn , &CBrush(crColor));

			if(bRUS)
			{
				CRgn rgn1;
				rgn1.CreatePolygonRgn(pp1,i1, WINDING);
				pDC->FillRgn(&rgn1 , &CBrush(crColor));
			}
		}

		i = 0;
		i1 = 0;
		
	}//end while
	pDC->SelectObject(pOldPen);
	delete [] pp;
	delete [] pp1;
	delete [] CRDARR;
}

void CIDWMMapView::OnCountryDefault(CString Dctry,double *DefLat, double *DefLon) 
{
	double  Dlat,Dlon,deltaMax,deltaMin,lat0,lon0;
	double xlatO1 ,  xlatO2 ,xlonO1 ,  xlonO2;

	char *CTYVEK = Dctry.GetBufferSetLength(3);

	float RLONLL, RLATLL, RLONUR, RLATUR;

	long NRCTY = 1;
	GEOCWI(&NRCTY, (unsigned char *)CTYVEK, &RLONLL, &RLATLL, &RLONUR, &RLATUR);

//	double pi = 4.0*atan(1.0);
	xlatO1 = RLATLL*180.0/pi;		xlatO2 = RLATUR*180.0/pi;
	xlonO1 = RLONLL*180.0/pi;		xlonO2 = RLONUR*180.0/pi;

	Dlat = xlatO2-xlatO1;			Dlon = xlonO2-xlonO1;
	deltaMax = max(Dlat,Dlon);	deltaMin = min(Dlat,Dlon);
	lat0=(xlatO2+xlatO1)/2.0;		lon0=(xlonO2+xlonO1)/2.0;

	if (deltaMax <= 2.0*deltaMin)
		deltaMax = 2.0*deltaMin;
	else
		deltaMin = deltaMax/2.0;

	xlatO1=lat0-deltaMin/2.0;	xlatO2=lat0+deltaMin/2.0;
	xlonO1=lon0-deltaMax/2.0;	xlonO2=lon0+deltaMax/2.0;

	double offset = 2.0;
	xlatO1 = xlatO1 - offset;
	xlonO1 = xlonO1 - offset;
	xlatO2 = xlatO2 + offset;
	xlonO2 = xlonO2 + offset;

	xlatO1 = max(-90.0,min(90.0,xlatO1));
	xlatO2 = max(-90.0,min(90.0,xlatO2));
	xlonO1 = max(-180.0,min(180.0,xlonO1));
	xlonO2 = max(-180.0,min(180.0,xlonO2));

	*DefLat = xlatO1/2.0 + xlatO2/2.0;
	*DefLon = xlonO1/2.0 + xlonO2/2.0;
}

void CIDWMMapView::OnHelpManual() 
{
//	CString PathFileName =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Help\\SMS4DC Manual.pdf");
//	ShellExecute(m_hWnd, "open", PathFileName, NULL, NULL, SW_SHOWNORMAL);	
	((CSMS4DCApp *)AfxGetApp())->FindHelpFile();
}


long CIDWMMapView::ESantUser(long ntc_id, CString beam_name, CString emi_rcp, CString *OffAng, CString *AntGain)
{
	long k =0;

	CString SQL1, str;
	CDatabase DB;

	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	DB.Open(_T(m_DB),false,false,_T("ODBC;"),false);
	CRecordset rs;
	rs.m_pDatabase=&DB;

	SQL1.Format("SELECT ntc_id, emi_rcp, beam_name, ESAntPatt.AntID, OffAng, AntGain FROM e_ant INNER JOIN ESAntPatt ON e_ant.AntID = ESAntPatt.AntID WHERE (((ntc_id)=%ld) AND ((emi_rcp)=\'%s\') AND ((beam_name)=\'%s\')) ORDER BY OffAng;",ntc_id,emi_rcp,beam_name);
 	rs.Open(CRecordset::snapshot, SQL1);

	CString OffAngSTR  = _T("");
	CString AntGainSTR = _T("");

	if(rs.GetRecordCount() == 1)
	{
		rs.MoveFirst();
		while(1)
		{
			if(rs.IsEOF()) break;
			rs.GetFieldValue((short)4,str);		OffAngSTR  = OffAngSTR  + str + _T(",");
			rs.GetFieldValue((short)5,str);		AntGainSTR = AntGainSTR + str + _T(",");
			k++;
			rs.MoveNext();
		}
	}
	rs.Close();
	DB.Close();

	*OffAng = OffAngSTR;
	*AntGain = AntGainSTR;

	return k;
}

void CIDWMMapView::OnVectorsDrawfromfile() 
{
	CString sFile, sPath;
	if(((CSMS4DCApp *)AfxGetApp())->VectorFileName( &sFile, &sPath))
	{
		if(!strCompare(sPath))
		{
			CVectorDLG Vdlg;
			Vdlg.m_TitleName = sFile;
			if (Vdlg.DoModal()== IDOK)
			{
				COLORREF crColor = RGB(Vdlg.m_LineColorRed,Vdlg.m_LineColorGreen,Vdlg.m_LineColorBlue);
				COLORREF flColor = RGB(Vdlg.m_FillColorRed,Vdlg.m_FillColorGreen,Vdlg.m_FillColorBlue);
				m_POLY[m_POLYnum].PathNameVec = sPath;
				m_POLY[m_POLYnum].FileNameVec = sFile;
				m_POLY[m_POLYnum].nWidthVec = Vdlg.m_LineWidth;
				m_POLY[m_POLYnum].crColorVec = crColor;
				m_POLY[m_POLYnum].nStyleVec = Vdlg.m_LineStyle0;
				m_POLY[m_POLYnum].nModeVec = Vdlg.m_FillMode;
				m_POLY[m_POLYnum].flColorVec = flColor;
				m_POLY[m_POLYnum].alphaVec = Vdlg.m_FillTransparancy;
				m_POLYnum = m_POLYnum+1;

				Vector2OnePoint(sPath);
				InvalidateRect(NULL,false);
			}
		}
		else
		{
			CString str;
			str.Format(_Z("The vector ''%s''\t\nwas already loaded."),sPath);
			MessageBox(str,_Z("Information!!!"),MB_ICONINFORMATION);
		}
	}
}

void CIDWMMapView::OnVectorsRemovefromdisplay() 
{
	m_flagGIBC = FALSE;

	m_POLYnum = 0;
	InvalidateRect(NULL,false);	
}
/*
void CIDWMMapView::DrawVector(CDC *pDC,CString Vector_filepath,int nWidth,COLORREF crColor, int nStyle,int nMode,COLORREF flColor,int alpha) 
{
	if (!Vector_filepath.IsEmpty())
	{
		FILE *fp;
		int k = 0 , k1 = 0;
		if ( (fp=fopen(Vector_filepath,"rt")) != NULL )
		{
			double *data;	data = new double[200000];
			int *Nk;		Nk = new int[200000];
			CString data1;	char bf[200];
			int i=0;k=i;k1=i;
			while( !feof( fp ) )
			{
				fscanf( fp, "%s", bf);
				data1 = bf;		Nk[k1] = k;
				if (data1=="NaN")	k1++;
				else				{data[i] = atof(data1);	i++;	k=i;}
			}
			fclose(fp);
			DWORD *Mk;	Mk=new DWORD[k1/2+1];
			Mk[0]=(Nk[0]+1)/2;
			for (int j=0;j<k1/2;j++)	Mk[j+1]=(Nk[2*j+2]-Nk[2*j])/2;

			CPoint *pp;		pp = new CPoint[k/2];
			for ( i=0;i<k/2;i++)	LatLon2Point(data[2*i+1],data[2*i],&pp[i]);

			CPen pen(nStyle, nWidth, crColor);	CPen* pOldPen = pDC->SelectObject(&pen);
			CBrush brush(flColor);				CBrush* pOldBrush = pDC->SelectObject(&brush);
			pDC->PolyPolyline(pp,Mk,k1/2+1);
			if (nMode==2)
			{
				int len=4;
				if (pDC->IsPrinting())	len=24;
				for ( i=0;i<k/2;i++)	pDC->Ellipse(pp[i].x-len, pp[i].y-len, pp[i].x+len, pp[i].y+len);
			}
			if (nMode==1)
			{
				int NewRed,NewGreen,NewBlue;	COLORREF OldCol;	CRgn rgn;
		//		rgn.CreatePolygonRgn( pp, k/2 ,WINDING );
				rgn.CreatePolyPolygonRgn(pp,(int *)Mk,k1/2+1 ,WINDING);

				CRect rect;		rgn.GetRgnBox(&rect);
				for(int i=rect.left;i<rect.right;i++)
					for(int j=rect.top;j<rect.bottom;j++)
					{
						if (rgn.PtInRegion(i,j))
						{
							OldCol=pDC->GetPixel(i,j);
							NewRed    =(alpha*(GetRValue(OldCol)-GetRValue(flColor)))/100+GetRValue(flColor);
							NewGreen  =(alpha*(GetGValue(OldCol)-GetGValue(flColor)))/100+GetGValue(flColor);
							NewBlue   =(alpha*(GetBValue(OldCol)-GetBValue(flColor)))/100+GetBValue(flColor);
							pDC->SetPixel(i,j,RGB(NewRed,NewGreen,NewBlue));
						}
					}
			}
			pDC->SelectObject(pOldPen);			pDC->SelectObject(pOldBrush);
			delete [] data;	delete [] Nk;	delete [] Mk;	delete [] pp;
		}
	}
}
*/
void CIDWMMapView::DrawVector(CDC *pDC,CString Vector_filepath,int nWidth,COLORREF crColor, int nStyle,int nMode,COLORREF flColor,int alpha) 
{
	if (!Vector_filepath.IsEmpty())
	{
		FILE *fp;
		if ( (fp = fopen(Vector_filepath,"rt")) != NULL )
		{
			CString bf;
			char bfLon[200], bfLat[200];

			CPoint *pp;		pp = new CPoint[200000];
			DWORD *Nk;		Nk = new DWORD[100000];

			long n = 0, k = 0, k1 = 0;
			while( !feof( fp ) )
			{
				fscanf( fp, "%s  %s", bfLon, bfLat);
				bf = bfLon;

				Nk[k1] = k;
				if (bf==_T("NaN"))
				{
					if(n>0)	k1++;
					k = 0;
				}
				else
				{
					LatLon2Point(atof(bfLat),atof(bfLon),&pp[n]);
					n++;	k++;
				}
			}//while
			fclose(fp);
			if (Nk[k1-1]==0)	k1--;
			if (bf==_T("NaN"))	k1--;

			CPen pen(nStyle, nWidth, crColor);	CPen* pOldPen = pDC->SelectObject(&pen);
			CBrush brush(flColor);				CBrush* pOldBrush = pDC->SelectObject(&brush);
			if (nMode==2)
			{
				pp[n] = pp[0];
				pDC->Polyline(pp,n+1);

				int len=4;
				if (pDC->IsPrinting())	len=24;
				for (long i=0;i<n;i++)	pDC->Ellipse(pp[i].x-len, pp[i].y-len, pp[i].x+len, pp[i].y+len);
			}
			else pDC->PolyPolyline(pp,Nk,k1+1);
			if (nMode==1)
			{
				int NewRed,NewGreen,NewBlue;	COLORREF OldCol;	CRgn rgn;
				rgn.CreatePolyPolygonRgn(pp , (int *)Nk , k1+1, WINDING );

				CRect rect;		rgn.GetRgnBox(&rect);
				for(int i=rect.left;i<rect.right;i++)
					for(int j=rect.top;j<rect.bottom;j++)
					{
						if (rgn.PtInRegion(i,j))
						{
							OldCol=pDC->GetPixel(i,j);
							NewRed    =(alpha*(GetRValue(OldCol)-GetRValue(flColor)))/100+GetRValue(flColor);
							NewGreen  =(alpha*(GetGValue(OldCol)-GetGValue(flColor)))/100+GetGValue(flColor);
							NewBlue   =(alpha*(GetBValue(OldCol)-GetBValue(flColor)))/100+GetBValue(flColor);
							pDC->SetPixel(i,j,RGB(NewRed,NewGreen,NewBlue));
						}
					}
			}
			pDC->SelectObject(pOldPen);			pDC->SelectObject(pOldBrush);
			delete [] Nk;						delete [] pp;
		}//if fp
	}//if (!Vector_filepath.IsEmpty())
}

void CIDWMMapView::OnFileSaveAs() 
{
	OnFileSave();	
}
void CIDWMMapView::OnFileSave() 
{
	CDocument* pDoc = GetDocument();
	CString str = pDoc->GetTitle();

	CDC *pDC = GetDC();
	((CSMS4DCApp *)AfxGetApp())->SaveDesktop(pDC, str);
	ReleaseDC(pDC);
}


BOOL CIDWMMapView::strCompare(CString sPath) 
{
	int N = m_POLYnum;
	for(int i = 0 ; i<N ; i++)
	{
		if((sPath.CompareNoCase(m_POLY[i].PathNameVec))==0)
			return TRUE;
	}
	return FALSE;
}
void CIDWMMapView::Vector2OnePoint(CString Vector_filepath) 
{
	if (!Vector_filepath.IsEmpty())
	{
		FILE *fp;
		if ( (fp = fopen(Vector_filepath,"rt")) != NULL )
		{
			CString dataLon,dataLat;
			char bfLon[200], bfLat[200];
			int n = 0;
			double lat, lon;
			double latmin=90, lonmin=180;
			double latmax=-90, lonmax=-180;
			while( !feof( fp ) )
			{
				fscanf( fp, "%s %s", bfLon,bfLat);
				dataLon = bfLon;  dataLat = bfLat;
				if (dataLon!=_T("NaN"))
				{
					lat = atof(dataLat);		lon = atof(dataLon);
					latmin = min(latmin,lat);	latmax = max(latmax,lat);
					lonmin = min(lonmin,lon);	lonmax = max(lonmax,lon);

					n++;
				}
			}
			fclose(fp);

			double  Dlat,Dlon,deltaMax,deltaMin,lat0,lon0;
			double xlatO1 ,  xlatO2 ,xlonO1 ,  xlonO2;
			xlatO1 = latmin;	
			xlatO2 = latmax;	
			xlonO1 = lonmin;	
			xlonO2 = lonmax;	

			Dlat = xlatO2-xlatO1;			Dlon = xlonO2-xlonO1;
			deltaMax = max(Dlat,Dlon);	deltaMin = min(Dlat,Dlon);
			lat0=(xlatO2+xlatO1)/2.0;		lon0=(xlonO2+xlonO1)/2.0;

			if (deltaMax <= 2.0*deltaMin)
				deltaMax = 2.0*deltaMin;
			else
				deltaMin = deltaMax/2.0;

			xlatO1=lat0-deltaMin/2.0;	xlatO2=lat0+deltaMin/2.0;
			xlonO1=lon0-deltaMax/2.0;	xlonO2=lon0+deltaMax/2.0;

			double offset = 2.0;
			xlatO1 = xlatO1 - offset;
			xlonO1 = xlonO1 - offset;
			xlatO2 = xlatO2 + offset;
			xlonO2 = xlonO2 + offset;

			xlatO1 = max(-90.0,min(90.0,xlatO1));
			xlatO2 = max(-90.0,min(90.0,xlatO2));
			xlonO1 = max(-180.0,min(180.0,xlonO1));
			xlonO2 = max(-180.0,min(180.0,xlonO2));

	//		RectInRegionVec(xlatO1 ,  xlatO2 ,xlonO1 ,  xlonO2) ;

			double latst,lonst,laten,lonen;
			Point2LatLon(m_stBoxPoint1,&latst,&lonst) ;
			Point2LatLon(m_enBoxPoint1,&laten,&lonen) ;
			latO1 = xlatO1;
			latO2 = xlatO2;
			lonO1 = xlonO1;
			lonO2 = xlonO2;
			LatLon2Point(latst,lonst,&m_stBoxPoint1) ;
			LatLon2Point(laten,lonen,&m_enBoxPoint1) ;

		}//if fp
	}//if (!Vector_filepath.IsEmpty())
}


extern "C" char * WINAPI AllCodes_lang(CString CTYCOD[], int *NOCTY);	//CNT_lang.lib
void CIDWMMapView::ALLcountry(CDC * pDC) 
{
	CString countryCODEidwm[300];
	int num;
	AllCodes_lang(countryCODEidwm, &num);

	for (int i=0;i<num;i++)
		VectorCountry(pDC,countryCODEidwm[i],2, RGBcountry(i) ) ;
/*
//	1) SOFTWARE YES /  SUPPORT YES / TRAINING NO 
//	2) SOFTWARE YES /  SUPPORT NO  / TRAINING NO 
//	3) SOFTWARE YES /  SUPPORT YES / TRAINING YES 
//	4) SOFTWARE NO  /  SUPPORT NO  / TRAINING YES 
//	5) SOFTWARE YES /  SUPPORT NO  / TRAINING YES 
	struct	{char CCode[4];	int PCode;}	List[56] = {
	{"ALB" , 3} , 	{"BAH" , 1} , 	{"BFA" , 1} , 	{"BEN" , 1} , 
	{"COG" , 1} , 	{"DJI" , 1} , 	{"ERI" , 1} , 	{"FJI" , 3} , 
	{"GUY" , 1} , 	{"HTI" , 1} , 	{"LBN" , 3} , 	{"LBR" , 1} , 
	{"MAU" , 1} , 	{"BRM" , 1} , 	{"NGR" , 1} , 	{"XWB" , 1} , 
	{"SNG" , 1} , 	{"STP" , 1} , 	{"TZA" , 3} , 	{"THA" , 4} , 
	{"TMP" , 3} , 	{"VUT" , 1} , 	{"YEM" , 3} , 	{"ZWE" , 1} , 
	{"ARG" , 2} , 	{"IRN" , 2} , 	{"SMO" , 2} , 	{"SRL" , 2} , 
	{"KOR" , 2} , 	{"BHR" , 2} , 	{"BGD" , 5} , 	{"VRG" , 2} , 
	{"BDI" , 2} , 	{"CBG" , 3} , 	{"CTI" , 2} , 	{"ETH" , 2} , 
	{"F  " , 1} , 	{"GMB" , 2} , 	{"D  " , 1} , 	{"INS" , 2} , 
	{"KIR" , 2} , 	{"MEX" , 2} , 	{"MNG" , 2} , 	{"NPL" , 3} , 
	{"PHL" , 2} , 	{"SLM" , 2} , 	{"LCA" , 2} , 	{"SDN" , 3} , 
	{"TON" , 2} , 	{"ATG" , 4} , 	{"CPV" , 4} , 	{"GUI" , 4} , 
	{"JOR" , 4} , 	{"GMB" , 4} , 	{"ETH" , 4} , 	{"LAO" , 4} };

	for (int i=0;i<num;i++)		VectorCountry(pDC,countryCODEidwm[i],0, RGB(0,0,0) ) ;

	COLORREF cc;
	for ( i=0;i<56;i++)
	{
		if     (List[i].PCode == 1)	cc = RGB(255,255,0);
		else if(List[i].PCode == 2)	cc = RGB(0,0,255);
		else if(List[i].PCode == 3)	cc = RGB(0,127,0);
		else if(List[i].PCode == 4)	cc = RGB(127,0,0);
		else if(List[i].PCode == 5)	cc = RGB(0,255,255);
		VectorCountry(pDC,List[i].CCode,2, cc ) ;
	}
*/

}

COLORREF CIDWMMapView::RGBcountry(int n) 
{
	COLORREF RGBt[261];
	RGBt[  0] = RGB(167,219, 90);
	RGBt[  1] = RGB(125,114,222);
	RGBt[  2] = RGB(187,177,125);
	RGBt[  3] = RGB(116,148,110);
	RGBt[  4] = RGB(233,190,205);
	RGBt[  5] = RGB(100,112,168);
	RGBt[  6] = RGB(167,230,153);
	RGBt[  7] = RGB( 90,145,154);
	RGBt[  8] = RGB(209,123,169);
	RGBt[  9] = RGB(207,178,145);
	RGBt[ 10] = RGB(166,213,137);
	RGBt[ 11] = RGB(153,162,128);
	RGBt[ 12] = RGB( 98,140,171);
	RGBt[ 13] = RGB(209,230,211);
	RGBt[ 14] = RGB(211,247,137);
	RGBt[ 15] = RGB(191,147, 99);
	RGBt[ 16] = RGB(202,140,155);
	RGBt[ 17] = RGB(244,231,190);
	RGBt[ 18] = RGB(110,111,185);
	RGBt[ 19] = RGB(232,143,226);
	RGBt[ 20] = RGB(140,189,238);
	RGBt[ 21] = RGB(139,130,187);
	RGBt[ 22] = RGB(115,206,239);
	RGBt[ 23] = RGB(198,189,223);
	RGBt[ 24] = RGB(156,200,233);
	RGBt[ 25] = RGB(198,156,145);
	RGBt[ 26] = RGB(222,153,202);
	RGBt[ 27] = RGB(249,226,146);
	RGBt[ 28] = RGB(112,164,181);
	RGBt[ 29] = RGB(244, 96,187);
	RGBt[ 30] = RGB(232, 94,105);
	RGBt[ 31] = RGB(103,131,207);
	RGBt[ 32] = RGB(145,116,135);
	RGBt[ 33] = RGB(179,174,215);
	RGBt[ 34] = RGB(124,144, 90);
	RGBt[ 35] = RGB(162,204,204);
	RGBt[ 36] = RGB(132,148,152);
	RGBt[ 37] = RGB(114,207,100);
	RGBt[ 38] = RGB(242, 91,138);
	RGBt[ 39] = RGB(180,143,233);
	RGBt[ 40] = RGB(169,228,149);
	RGBt[ 41] = RGB(179,247,132);
	RGBt[ 42] = RGB(226,142,133);
	RGBt[ 43] = RGB(169,164,121);
	RGBt[ 44] = RGB(214,156,136);
	RGBt[ 45] = RGB(120,232,202);
	RGBt[ 46] = RGB(115,186,182);
	RGBt[ 47] = RGB(105,177,130);
	RGBt[ 48] = RGB( 93,222,147);
	RGBt[ 49] = RGB(239,221,162);
	RGBt[ 50] = RGB(217,203, 94);
	RGBt[ 51] = RGB(161,163,131);
	RGBt[ 52] = RGB(162,102,219);
	RGBt[ 53] = RGB(186,133,114);
	RGBt[ 54] = RGB(218,196,113);
	RGBt[ 55] = RGB(135,184,248);
	RGBt[ 56] = RGB(232,126,204);
	RGBt[ 57] = RGB(159,103,161);
	RGBt[ 58] = RGB( 97,143,147);
	RGBt[ 59] = RGB(195,203,181);
	RGBt[ 60] = RGB(172, 93, 96);
	RGBt[ 61] = RGB(243,211,202);
	RGBt[ 62] = RGB(226,156,149);
	RGBt[ 63] = RGB(225,247,154);
	RGBt[ 64] = RGB(129,240,241);
	RGBt[ 65] = RGB(243,146,178);
	RGBt[ 66] = RGB(176,215,245);
	RGBt[ 67] = RGB(174,133,218);
	RGBt[ 68] = RGB(213,127,222);
	RGBt[ 69] = RGB(233,124,115);
	RGBt[ 70] = RGB(102,100,174);
	RGBt[ 71] = RGB(192,162,167);
	RGBt[ 72] = RGB( 90,206,118);
	RGBt[ 73] = RGB(164,160,224);
	RGBt[ 74] = RGB(161,223,191);
	RGBt[ 75] = RGB(130,244,115);
	RGBt[ 76] = RGB(165,211,234);
	RGBt[ 77] = RGB(216,208,210);
	RGBt[ 78] = RGB(125,154,170);
	RGBt[ 79] = RGB(115,105,204);
	RGBt[ 80] = RGB(105,101, 97);
	RGBt[ 81] = RGB(164,239,101);
	RGBt[ 82] = RGB( 93,172,187);
	RGBt[ 83] = RGB(134,189,222);
	RGBt[ 84] = RGB(124,132,174);
	RGBt[ 85] = RGB(228,180,120);
	RGBt[ 86] = RGB(240,166,172);
	RGBt[ 87] = RGB(233,183,186);
	RGBt[ 88] = RGB(144,128,164);
	RGBt[ 89] = RGB(158,181,231);
	RGBt[ 90] = RGB(137,234,114);
	RGBt[ 91] = RGB(149,120,245);
	RGBt[ 92] = RGB(105, 93,188);
	RGBt[ 93] = RGB(168,103,206);
	RGBt[ 94] = RGB(137,166,110);
	RGBt[ 95] = RGB(121,216,199);
	RGBt[ 96] = RGB(207,174,240);
	RGBt[ 97] = RGB( 90,220,146);
	RGBt[ 98] = RGB(129,179,107);
	RGBt[ 99] = RGB(248,230,108);
	RGBt[100] = RGB(179,162,101);
	RGBt[101] = RGB(214,194,192);
	RGBt[102] = RGB(104,214,138);
	RGBt[103] = RGB(105,127,193);
	RGBt[104] = RGB(174,204,220);
	RGBt[105] = RGB(244,164,199);
	RGBt[106] = RGB(246,143,240);
	RGBt[107] = RGB(120,175,176);
	RGBt[108] = RGB(249,159,221);
	RGBt[109] = RGB(144,236,115);
	RGBt[110] = RGB(139,142,157);
	RGBt[111] = RGB(150,142, 97);
	RGBt[112] = RGB(164,114,135);
	RGBt[113] = RGB(190,192,220);
	RGBt[114] = RGB(118, 94,105);
	RGBt[115] = RGB(246,214,144);
	RGBt[116] = RGB(222,122,189);
//	RGBt[117] = RGB(186,184,143);
	RGBt[117] = RGB(  0,205,  0);
	RGBt[118] = RGB(125,226,113);
	RGBt[119] = RGB(156,237,231);
	RGBt[120] = RGB(133,185,186);
	RGBt[121] = RGB(225,249,103);
	RGBt[122] = RGB(207,192,174);
	RGBt[123] = RGB(153,215,226);
	RGBt[124] = RGB(105,190,163);
	RGBt[125] = RGB(178,115,154);
	RGBt[126] = RGB(133,213,212);
	RGBt[127] = RGB(185, 92,111);
	RGBt[128] = RGB(209,205,175);
	RGBt[129] = RGB(208,114,161);
	RGBt[130] = RGB(241,239,138);
	RGBt[131] = RGB(148,104,108);
	RGBt[132] = RGB(157,151,188);
	RGBt[133] = RGB(228,244,157);
//	RGBt[134] = RGB(101,216, 93);
	RGBt[134] = RGB(0,255,0);
	RGBt[135] = RGB(158,132,139);
	RGBt[136] = RGB(192,115,229);
	RGBt[137] = RGB(233,110,194);
	RGBt[138] = RGB(182,228, 97);
	RGBt[139] = RGB(133,247, 99);
	RGBt[140] = RGB(216,192,165);
	RGBt[141] = RGB( 95,206,102);
	RGBt[142] = RGB(181,101,131);
	RGBt[143] = RGB(176,186,214);
	RGBt[144] = RGB(242,102,119);
	RGBt[145] = RGB(138,101, 95);
	RGBt[146] = RGB(192,137, 95);
	RGBt[147] = RGB(248,102,240);
	RGBt[148] = RGB(186,104,187);
	RGBt[149] = RGB(159,126,119);
	RGBt[150] = RGB( 94,218,114);
	RGBt[151] = RGB(246,229,186);
	RGBt[152] = RGB(235,193,144);
	RGBt[153] = RGB(118,159,206);
	RGBt[154] = RGB(172,203,134);
	RGBt[155] = RGB(142,180,148);
	RGBt[156] = RGB(140,109,130);
	RGBt[157] = RGB(202,250,221);
	RGBt[158] = RGB( 92,202,219);
	RGBt[159] = RGB(103,168,234);
	RGBt[160] = RGB(109,202,117);
	RGBt[161] = RGB(146,135,231);
	RGBt[162] = RGB(206,119,133);
	RGBt[163] = RGB(183,120,176);
	RGBt[164] = RGB(115,181,162);
	RGBt[165] = RGB(140,235,217);
	RGBt[166] = RGB(206,244,193);
	RGBt[167] = RGB(229,180,189);
	RGBt[168] = RGB(134,220,112);
	RGBt[169] = RGB(156,191,197);
	RGBt[170] = RGB(243,100,127);
	RGBt[171] = RGB(225,223,131);
	RGBt[172] = RGB(243,213,222);
	RGBt[173] = RGB(133,228,103);
	RGBt[174] = RGB(152,118,103);
	RGBt[175] = RGB( 95,205, 98);
	RGBt[176] = RGB(220,217, 99);
	RGBt[177] = RGB(184,227,225);
	RGBt[178] = RGB(133,227,214);
	RGBt[179] = RGB(126,164,176);
	RGBt[180] = RGB(240,225,239);
	RGBt[181] = RGB(249,109,125);
	RGBt[182] = RGB(169,180,149);
	RGBt[183] = RGB(225,206,103);
	RGBt[184] = RGB(231, 98,113);
	RGBt[185] = RGB(209,123,194);
	RGBt[186] = RGB(228,121,190);
	RGBt[187] = RGB(134,173,235);
	RGBt[188] = RGB(180,168,205);
	RGBt[189] = RGB(175,156,174);
	RGBt[190] = RGB( 90,235,143);
	RGBt[191] = RGB(166,180,188);
	RGBt[192] = RGB(167,117, 93);
	RGBt[193] = RGB(233,191,146);
	RGBt[194] = RGB(123,194,103);
	RGBt[195] = RGB(174,126,236);
	RGBt[196] = RGB(138,123,109);
//	RGBt[197] = RGB(132,189,162);
	RGBt[197] = RGB( 82,139,112);
	RGBt[198] = RGB( 95,244,211);
	RGBt[199] = RGB(132,189,191);
	RGBt[200] = RGB(139,227,204);
	RGBt[201] = RGB(247,146,242);
	RGBt[202] = RGB(209,108,185);
	RGBt[203] = RGB(196,152,232);
	RGBt[204] = RGB(111,152,132);
	RGBt[205] = RGB(226,230,127);
	RGBt[206] = RGB(143,240,189);
	RGBt[207] = RGB( 92,176,186);
	RGBt[208] = RGB(113,190,248);
	RGBt[209] = RGB(166,137,171);
	RGBt[210] = RGB(144,146,191);
	RGBt[211] = RGB(174, 96,134);
	RGBt[212] = RGB(148,244,191);
	RGBt[213] = RGB(246,154,230);
	RGBt[214] = RGB(155,213,115);
	RGBt[215] = RGB(173,202,130);
	RGBt[216] = RGB(121,173,115);
	RGBt[217] = RGB( 97,118,138);
	RGBt[218] = RGB(148,143,189);
	RGBt[219] = RGB(133,207,117);
	RGBt[220] = RGB(148,153,169);
	RGBt[221] = RGB(200,198,173);
	RGBt[222] = RGB(244,143,107);
	RGBt[223] = RGB(121,177,165);
	RGBt[224] = RGB(227,113,176);
	RGBt[225] = RGB(208,146,115);
	RGBt[226] = RGB(163,135,202);
	RGBt[227] = RGB(168,158,190);
	RGBt[228] = RGB(234,122,100);
	RGBt[229] = RGB(156,192, 99);
	RGBt[230] = RGB(205,215,178);
	RGBt[231] = RGB(201,238,170);
	RGBt[232] = RGB(229,162,152);
	RGBt[233] = RGB(214,114,132);
	RGBt[234] = RGB(187,206,111);
	RGBt[235] = RGB(245,188,112);
	RGBt[236] = RGB(198,209,127);
	RGBt[237] = RGB(118,107,152);
	RGBt[238] = RGB(133,246,182);
	RGBt[239] = RGB(130,143,181);
	RGBt[240] = RGB(153,146,124);
	RGBt[241] = RGB(198,133,159);
	RGBt[242] = RGB(206,239,201);
	RGBt[243] = RGB(199,124,201);
	RGBt[244] = RGB(250,199,110);
	RGBt[245] = RGB(105,161,172);
	RGBt[246] = RGB(238,130, 91);
	RGBt[247] = RGB(100, 97,169);
	RGBt[248] = RGB(124,104,225);
	RGBt[249] = RGB(176,141,236);
	RGBt[250] = RGB(114,146,112);
	RGBt[251] = RGB(197,188,198);
	RGBt[252] = RGB(224,120,128);
	RGBt[253] = RGB(223,223,195);
	RGBt[254] = RGB(149,218,240);
	RGBt[255] = RGB(147,123,130);
	RGBt[256] = RGB(191,115,149);
	RGBt[257] = RGB( 92,103,147);
	RGBt[258] = RGB( 93,167,162);
	RGBt[259] = RGB(199,219,137);
	RGBt[260] = RGB(110,185,205);
	return RGBt[n];
}

void CIDWMMapView::OnOptionFillcountries() 
{
	m_ALLcountry = !m_ALLcountry;
	InvalidateRect(NULL,FALSE);	
}

void CIDWMMapView::OnUpdateOptionFillcountries(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ALLcountry);
}

void CIDWMMapView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "IDWM Map";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE34);
}

extern "C" int WINAPI APP7(HWND hWndParent,CString DBSTR,CString PathFile0,CString mLang, 
						   CStringArray &ListFile , double &lat , double &lon, CString &ESname);	//APP7DLL.lib
void CIDWMMapView::OnOptionRrappendix7gibc() 
{
	CStringArray ListFile;
	CString mLang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;

	HINSTANCE hClientRes = AfxGetResourceHandle();			//Store the current resource handle
	AfxSetResourceHandle(::GetModuleHandle("APP7DLL.dll"));	//Tell the client to use the .DLL's resources

	APP7(this->m_hWnd,((CSMS4DCApp *)AfxGetApp())->m_CDBSTR,((CSMS4DCApp *)AfxGetApp())->m_AppPath, mLang, ListFile, m_LatGIBC, m_LonGIBC, m_NameGIBC);
	
	AfxSetResourceHandle(hClientRes);						//Restore the client application resource handle	

	int n = ListFile.GetSize();
	for(int i=0;i<n;i++)
		VectorsDrawfromfile(ListFile.GetAt(i)); 
	m_flagGIBC = TRUE;
}

void CIDWMMapView::VectorsDrawfromfile(CString FilePath) 
{
	CString sFile, sPath = FilePath;
	int n = FilePath.ReverseFind('\\');
	sFile = FilePath;		sFile.Delete(0,n+1);

//	if(((CSMS4DCApp *)AfxGetApp())->VectorFileName( &sFile, &sPath))
	{
		if(!strCompare(sPath))
		{
			CVectorDLG Vdlg;
			Vdlg.m_TitleName = sFile;
			if (Vdlg.DoModal()== IDOK)
			{
				COLORREF crColor = RGB(Vdlg.m_LineColorRed,Vdlg.m_LineColorGreen,Vdlg.m_LineColorBlue);
				COLORREF flColor = RGB(Vdlg.m_FillColorRed,Vdlg.m_FillColorGreen,Vdlg.m_FillColorBlue);
				m_POLY[m_POLYnum].PathNameVec = sPath;
				m_POLY[m_POLYnum].FileNameVec = sFile;
				m_POLY[m_POLYnum].nWidthVec = Vdlg.m_LineWidth;
				m_POLY[m_POLYnum].crColorVec = crColor;
				m_POLY[m_POLYnum].nStyleVec = Vdlg.m_LineStyle0;
				m_POLY[m_POLYnum].nModeVec = Vdlg.m_FillMode;
				m_POLY[m_POLYnum].flColorVec = flColor;
				m_POLY[m_POLYnum].alphaVec = Vdlg.m_FillTransparancy;
				m_POLYnum = m_POLYnum+1;

				Vector2OnePoint(sPath);
				InvalidateRect(NULL,false);
			}
		}
		else
		{
			CString str;
			str.Format(_Z("The vector ''%s''\t\nwas already loaded."),sPath);
			MessageBox(str,_Z("Information!!!"),MB_ICONINFORMATION);
		}
	}
}


