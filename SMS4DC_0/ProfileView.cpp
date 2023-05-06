// ProfileView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "ProfileView.h"
#include "ProfileDoc.h"

#include "MainFrm.h"
#include <math.h>
#include "KFactor.h"
#include "FresnelDLG.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileView

IMPLEMENT_DYNCREATE(CProfileView, CView)

CProfileView::CProfileView()
{
	m_kfactor="4/3";
	m_bLPressed=false;

	m_AxesT=0;
	m_AxesH=0;
	m_AxesL=0;
	m_AxesW=0;
	m_stPoint.x=0;
	m_stPoint.y=0;

	m_Fresnel = 1;
	m_FrqMHz = 150.0;
	m_TxH = 300.0;
	m_RxH = 100.0;
}

CProfileView::~CProfileView()
{
	m_pView = ((CSMS4DCView *)(((CSMS4DCApp *)AfxGetApp())->m_pView));
	if(m_pView)
	{
		m_pView->m_CoplLat = -999;
		m_pView->m_CoplLon = -999;

		m_pView->OnRefresh1();
		m_pView = NULL;
	}
}


BEGIN_MESSAGE_MAP(CProfileView, CView)
	//{{AFX_MSG_MAP(CProfileView)
	ON_COMMAND(ID_Refresh, OnRefresh)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_OPTION_CHANGEKFACTOR, OnOptionChangekfactor)
	ON_COMMAND(ID_OPTION_CHANGEFRESNELZONEPARAMETERS, OnOptionChangefresnelzoneparameters)
	ON_UPDATE_COMMAND_UI(ID_OPTION_CHANGEFRESNELZONEPARAMETERS, OnUpdateOptionChangefresnelzoneparameters)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileView drawing

void CProfileView::Plot(CDC* pDC,double *xi, double *yi,int N,
						double xiMIN,double xiMAX,double yiMIN,double yiMAX,
						int nWidth,COLORREF crColor, int nStyle, int nMode,COLORREF flColor) 
{
	double AxesT=m_AxesT;
	double AxesH=m_AxesH;
	double AxesW=m_AxesW;
	double AxesL=m_AxesL;
//////////////////////////plot////////////////////////////////////
	CPoint *pts;
	pts=new CPoint[N];

	for (int i=0;i<N;i++)
	{
		pts[i].x = (long)( AxesL + (AxesW - AxesL)*(xi[i] - xiMIN)/(xiMAX-xiMIN) );
		pts[i].y = (long)( AxesH + (AxesT - AxesH)*(yi[i] - yiMIN)/(yiMAX-yiMIN) );
	}
	CPen pen(nStyle, nWidth, crColor);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush brush(flColor);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	if (nMode==0)
		pDC->Polyline(pts, N);
	else
		pDC->Polygon(pts, N);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	delete [] pts;

}
void CProfileView::DrawAntSymbol(CDC* pDC,double xi, double yi,
						double xiMIN,double xiMAX,double yiMIN,double yiMAX,
						COLORREF crColor, int nMode) 
{
	double AxesT=m_AxesT;
	double AxesH=m_AxesH;
	double AxesW=m_AxesW;
	double AxesL=m_AxesL;
//////////////////////////plot////////////////////////////////////
	CPoint *pts,point1;
	pts=new CPoint[4];

	point1.x = (long)( AxesL + (AxesW - AxesL)*(xi - xiMIN)/(xiMAX-xiMIN) );
	point1.y = (long)( AxesH + (AxesT - AxesH)*(yi - yiMIN)/(yiMAX-yiMIN) );

	int len = m_fontH24;
	pts[0] = CPoint(point1.x,point1.y+len);
	if (nMode)
		pts[1] = CPoint(point1.x+len,point1.y);
	else
		pts[1] = CPoint(point1.x-len,point1.y);
	pts[2] = CPoint(point1.x,point1.y-len);
	pts[3] = pts[0];

	CPen pen(PS_SOLID, 1, crColor);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush brush(crColor);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	pDC->Polygon(pts, 4);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	delete [] pts;
}

void CProfileView::OnDraw(CDC* pDC)
{
	CProfileDoc* pDoc = (CProfileDoc *)GetDocument();

if(	pDoc->m_ReadyDoc == 1)
{
	pDC->SetMapMode(MM_LOMETRIC);

	CRect rect;
///////////////////////////////////////
	if (pDC->IsPrinting())
		rect=m_rcPrintRect;
	else
		GetClientRect(&rect);
	pDC->DPtoLP(&rect);

	initDP_LP(pDC);
///////////////////////////////////////

	CBrush brush(RGB(204,204,204));
	pDC->FillRect(rect,&brush);

	int AxesW=(int)((0.93)*(rect.Width()));
	int AxesH=(int)((0.90)*(rect.Height()));
	int AxesT=(int)(rect.top+(rect.Height())- AxesH );
	int AxesL=(int)(rect.left+(rect.Width())- AxesW );
	m_AxesT=AxesT;
	m_AxesH=AxesH;
	m_AxesW=AxesW;
	m_AxesL=AxesL;

	CPen pen;
	pen.CreatePen(PS_SOLID, m_fontH6,RGB(0,0,0));
	pDC->SelectObject(&pen);
	pDC->Rectangle(AxesL-2,AxesT,AxesW+6,AxesH);

	Hmin=pDoc->Hmin;
	Np=pDoc->Np;
	double d=pDoc->Dmax-pDoc->Dmin;

	double pi=4.0*atan(1.0);
	double re=6371.0*atof_kfactor(m_kfactor);
	double a=re*sin(d/(2.0*re));
	double b=-re*cos(d/(2.0*re));
	double *phi;	phi=new double[Np];
	double *xc;		xc=new double[Np];
	double *yc;		yc=new double[Np];
	double *xp;		xp=new double[Np];
	double *yp;		yp=new double[Np];
	for (int i=0;i<Np;i++)
	{
		phi[i]=(pi/2.0)+(d/(2.0*re))-(pDoc->m_di[i]/(re));
		xc[i]=a+re*cos(phi[i]);
		yc[i]=b+re*sin(phi[i]);
		yc[i]=Hmin+1000.0*yc[i];

		xp[i]=a+(re+pDoc->m_hi[i]/1000.0-Hmin/1000.0)*cos(phi[i]);
		yp[i]=b+(re+pDoc->m_hi[i]/1000.0-Hmin/1000.0)*sin(phi[i]);
		yp[i]=Hmin+1000.0*yp[i];
	}

	double *xpc;		xpc=new double[2*Np];
	double *ypc;		ypc=new double[2*Np];
	for ( i=0;i<Np;i++)
	{
		xpc[i]=xp[i];
		ypc[i]=yp[i];
		xpc[Np+i]=xc[Np-i-1];
		ypc[Np+i]=yc[Np-i-1];
	}
	double xpcMIN=MinValue(xpc,2*Np);
	double xpcMAX=MaxValue(xpc,2*Np);
	double ypcMIN=MinValue(ypc,2*Np);
	double ypcMAX=MaxValue(ypc,2*Np);

	double xcMIN=MinValue(xc,Np);
	double xcMAX=MaxValue(xc,Np);
	double ycMIN=MinValue(yc,Np);
	double ycMAX=MaxValue(yc,Np);

	double xMIN=min(xcMIN,xpcMIN);
	double yMIN=min(ycMIN,ypcMIN);
	double xMAX=max(xcMAX,xpcMAX);
	double yMAX=max(ycMAX,ypcMAX);

	if(	pDoc->m_DrawFresnel )
	{
		double *xl;		xl=new double[Np];
		double *yl;		yl=new double[Np];
		double *rfi;	rfi=new double[Np];
		double *xf1;	xf1=new double[Np];
		double *yf1;	yf1=new double[Np];
		double *xf2;	xf2=new double[Np];
		double *yf2;	yf2=new double[Np];

		double tt = (m_RxH+pDoc->m_hi[Np-1] - m_TxH-pDoc->m_hi[0])/(1000.0*d) - d/(2.0*re);
		for ( i=0;i<Np;i++)
		{
			//%%%%%%%%% Line %%%%%%%%%%%%%%%%
			xl[i] = a + ((m_TxH+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re-Hmin/1000.0)*cos(phi[i]);
			yl[i] = b + ((m_TxH+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re-Hmin/1000.0)*sin(phi[i]);
			yl[i] = Hmin + 1000.0*yl[i];
			//%%%%%%%% Fresnel Zone %%%%%%%%%%%%%%%%%
		//	rfi[i] = m_Fresnel*sqrt(0.3*pDoc->m_di[i]*(d-pDoc->m_di[i])/(m_FrqMHz*d));
			rfi[i] = sqrt(m_Fresnel*0.3*pDoc->m_di[i]*(d-pDoc->m_di[i])/(m_FrqMHz*d));
			xf1[i] = a + ((m_TxH+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re-rfi[i]-Hmin/1000.0)*cos(phi[i]);
			yf1[i] = b + ((m_TxH+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re-rfi[i]-Hmin/1000.0)*sin(phi[i]);
			yf1[i] = Hmin + 1000.0*yf1[i];
			xf2[i] = a + ((m_TxH+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re+rfi[i]-Hmin/1000.0)*cos(phi[i]);
			yf2[i] = b + ((m_TxH+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re+rfi[i]-Hmin/1000.0)*sin(phi[i]);
			yf2[i] = Hmin + 1000.0*yf2[i];
		}
		//%%%%%%%%% Antenna %%%%%%%%%%%%%%%
		double *xat;		xat=new double[2];
		double *yat;		yat=new double[2];
		double *xar;		xar=new double[2];
		double *yar;		yar=new double[2];

		xat[0] = xp[0];			yat[0] = yp[0];
		xat[1] = a + ((m_TxH+pDoc->m_hi[0])/1000.0+re-Hmin/1000.0)*cos(phi[0]);
		yat[1] = b + ((m_TxH+pDoc->m_hi[0])/1000.0+re-Hmin/1000.0)*sin(phi[0]);
		yat[1] = Hmin + 1000.0*yat[1];

		xar[0] = xp[Np-1];		yar[0] = yp[Np-1];
		xar[1] = a + ((m_RxH+pDoc->m_hi[Np-1])/1000.0+re-Hmin/1000.0)*cos(phi[Np-1]);
		yar[1] = b + ((m_RxH+pDoc->m_hi[Np-1])/1000.0+re-Hmin/1000.0)*sin(phi[Np-1]);
		yar[1] = Hmin + 1000.0*yar[1];
		
		double yf1MIN=MinValue(yf1,Np);
		double yf1MAX=MaxValue(yf1,Np);
		double yf2MIN=MinValue(yf2,Np);
		double yf2MAX=MaxValue(yf2,Np);
		double yfMIN=min(yf1MIN,yf2MIN);
		double yfMAX=max(yf1MAX,yf2MAX);
		yMIN=min(yMIN,yfMIN);
		yMAX=max(yMAX,yfMAX);

		Plot(pDC,xpc,ypc,2*Np,  xMIN,xMAX,yMIN,yMAX,   m_fontH6-1,RGB(0,0,255),PS_SOLID,1,RGB(0,200,0)) ;
//		Plot(pDC,xc,yc,Np,  xMIN,xMAX,yMIN,yMAX,  5,RGB(128,0,0),PS_SOLID,1,RGB(204,204,204)) ;

		Plot(pDC,xl,yl,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(255,0,0),PS_SOLID,0) ;
		Plot(pDC,xf1,yf1,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_DASH,0) ;
		Plot(pDC,xf2,yf2,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_DASH,0) ;
		Plot(pDC,xat,yat,2,  xMIN,xMAX,yMIN,yMAX,  m_fontH14,RGB(0,0,255),PS_SOLID,0) ;
		Plot(pDC,xar,yar,2,  xMIN,xMAX,yMIN,yMAX,  m_fontH14,RGB(0,0,255),PS_SOLID,0) ;
		DrawAntSymbol(pDC,xat[1],yat[1],  xMIN,xMAX,yMIN,yMAX,  RGB(255,0,0),1) ;
		DrawAntSymbol(pDC,xar[1],yar[1],  xMIN,xMAX,yMIN,yMAX,  RGB(255,0,0),0) ;
		delete [] xl;
		delete [] yl;
		delete [] rfi;
		delete [] xf1;
		delete [] yf1;
		delete [] xf2;
		delete [] yf2;
		delete [] xat;
		delete [] yat;
		delete [] xar;
		delete [] yar;
	}
	else
	{
		Plot(pDC,xpc,ypc,2*Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_SOLID,1,RGB(0,200,0)) ;
//		Plot(pDC,xc,yc,Np,  xMIN,xMAX,yMIN,yMAX,  5,RGB(128,0,0),PS_SOLID,1,RGB(204,204,204)) ;
	}

	Xtick(pDC,xMIN,xMAX) ;
	YtickL(pDC,yMIN,yMAX) ;

	double ytick1=m_ytickMIN,ytick2=m_ytickSTEP,ytick3=m_ytickMAX;
	double ytick=ytick1;

	int j=0;
	while (  (ytick<=ytick3 && ytick>=ytick1) )
	{
		ytick=ytick1+j*ytick2;
		for ( i=0;i<Np;i++)
		{
			xc[i]=a+(ytick/1000.0+re-Hmin/1000.0)*cos(phi[i]);
			yc[i]=b+(ytick/1000.0+re-Hmin/1000.0)*sin(phi[i]);
			yc[i]=Hmin+1000.0*yc[i];

			yc[i]=min(yc[i],yMAX);
		}
		j++;
		Plot(pDC,xc,yc,Np,  xMIN,xMAX,yMIN,yMAX,  1,RGB(0,255,0),PS_DOT) ;
	}

	delete [] xpc;
	delete [] ypc;
	delete [] xc;
	delete [] yc;
	delete [] phi;
	delete [] xp;
	delete [] yp;

	CPen pen0;
	pen0.CreatePen(PS_DOT ,1,RGB(0,0,255));
	pDC->SelectObject(&pen0);

	m_stPoint.x=AxesL;
	pDC->MoveTo(m_stPoint.x,m_AxesT);
	pDC->LineTo(m_stPoint.x,m_AxesH);

	pDC->MoveTo(m_stPoint.x-2,m_AxesT);
	pDC->LineTo(m_stPoint.x-2,m_AxesH);

	pDC->MoveTo(m_stPoint.x+2,m_AxesT);
	pDC->LineTo(m_stPoint.x+2,m_AxesH);

}


}
/////////////////////////////////////////////////////////////////////////////

void CProfileView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
	m_bLPressed=true;
	CView::OnLButtonDown(nFlags, point);
}

void CProfileView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CProfileDoc* pDoc = (CProfileDoc *)GetDocument();
	if (m_bLPressed==true)
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));

		CClientDC dc(this);
		dc.SetMapMode(MM_LOMETRIC);
		dc.DPtoLP(&point);

		CPen pen;
		pen.CreatePen(PS_DOT ,1,RGB(0,0,255));
		dc.SelectObject(&pen);

		dc.SetROP2(R2_XORPEN);
		dc.MoveTo(m_stPoint.x,m_AxesT);
		dc.LineTo(m_stPoint.x,m_AxesH);

		dc.MoveTo(m_stPoint.x-2,m_AxesT);
		dc.LineTo(m_stPoint.x-2,m_AxesH);

		dc.MoveTo(m_stPoint.x+2,m_AxesT);
		dc.LineTo(m_stPoint.x+2,m_AxesH);

		
		point.x=min(max(point.x,m_AxesL),m_AxesW);

		dc.MoveTo(point.x,m_AxesT);
		dc.LineTo(point.x,m_AxesH);

		dc.MoveTo(point.x-2,m_AxesT);
		dc.LineTo(point.x-2,m_AxesH);

		dc.MoveTo(point.x+2,m_AxesT);
		dc.LineTo(point.x+2,m_AxesH);

		CString string;
		double rng;
		rng=pDoc->m_di[0]+(pDoc->m_di[Np-1]-pDoc->m_di[0])*(point.x-m_AxesL)/(m_AxesW-m_AxesL);
		string.Format("Dist(km) : %0.3f", rng  );
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(4, string);

		double y = InterpXY(pDoc->m_di,pDoc->m_hi,rng,Np);

		string.Format("Alt(m) : %0.0f", y  );
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(3, string);

		double yUTM = InterpXY(pDoc->m_di,pDoc->m_lati,rng,Np);
		double xUTM = InterpXY(pDoc->m_di,pDoc->m_loni,rng,Np);
xUTM = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(xUTM);
		char   xU,yU;
		int    xUTMD,xUTMM,yUTMD,yUTMM;
		double xUTMS,yUTMS;
		DEG2DMS("LON",xUTM,&xUTMD,&xUTMM,&xUTMS,&xU);
		DEG2DMS("LAT",yUTM,&yUTMD,&yUTMM,&yUTMS,&yU);

		string.Format("Lat(%c) : %02d ° %02d ' %0.3f ''",yU,yUTMD,yUTMM,yUTMS );
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, string);

		string.Format("Lon(%c) : %03d ° %02d ' %0.3f ''",xU,xUTMD,xUTMM,xUTMS );
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(2, string);

		m_stPoint=point;
//////////////////////////////
		m_pView = ((CSMS4DCView *)(((CSMS4DCApp *)AfxGetApp())->m_pView));
		if(m_pView)
		{
			m_pView->m_CoplLat = yUTM;
			m_pView->m_CoplLon = xUTM;
			m_pView->OnRefresh1();
		}
//////////////////////////////
	}
	CView::OnMouseMove(nFlags, point);
}

void CProfileView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed=false;
	CView::OnLButtonUp(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
// CProfileView diagnostics

#ifdef _DEBUG
void CProfileView::AssertValid() const
{
	CView::AssertValid();
}

void CProfileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProfileView message handlers

void CProfileView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
							int Escapement,
							int nHeight,int nWidth,int FontWeight,CString FontName) 
{
/*
	CFont font;
	VERIFY(font.CreateFont(
	   14,                        // nHeight
	   0,                         // nWidth
	   900,                         // nEscapement
	   0,                         // nOrientation
	   FW_BOLD,                 // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   "Arial"));                 // lpszFacename
*/ 

//		CClientDC dc(this);
	pDC->SetBkMode(TRANSPARENT);
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = nHeight;                // request a 12-pixel-height font
	lf.lfWidth =nWidth;
	lf.lfWeight = FontWeight;
	strcpy(lf.lfFaceName, FontName);        // request a face name "Arial"
	lf.lfEscapement=Escapement;
	VERIFY(font.CreateFontIndirect(&lf));  // create the font

	CFont* def_font = pDC->SelectObject(&font);

	pDC->SetTextColor(FontColor);
	pDC->TextOut(x,y,str);
	pDC->SelectObject(def_font);

	font.DeleteObject(); 
}


void CProfileView::LineDraw(CDC* pDC,int x1, int y1,int x2, int y2,
							int nWidth, COLORREF crColor, int nStyle) 
{
	CPen pen;
	pen.CreatePen(nStyle,nWidth,crColor);
	pDC->SelectObject(&pen);

	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

void CProfileView::OnRefresh() 
{
	Invalidate();	
}

void CProfileView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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

void CProfileView::YtickL(CDC* pDC,double yiMIN,double yiMAX) 
{
	double ytickMIN  ,   ytickSTEP  ,  ytickMAX;

	CString label;
	double r,step_m,yround=0,yiMAXr;
	int y=0,yNum=20;

	if (yiMAX != yiMIN)
	{
		step_m = (yiMAX-yiMIN)/yNum;
		r = ((step_m>10.0) ? 10.0 : ((step_m>1.0) ? 1.0 :  ((step_m>0.1) ? 0.1 : ((step_m>0.01) ? 0.01 : 0.001))));
		step_m=((int)(((yiMAX-yiMIN)/yNum)/r))*r;
		yiMAXr=((int)(yiMAX/r))*r;
		ytickMIN=yiMAXr  ;   ytickSTEP=step_m  ;  ytickMAX=yiMAXr;

		yround=(yiMIN+yiMAX)/2.0;		int i=0;
		while ( yround<=yiMAX && yround>=yiMIN )
		{
			yround=(yiMAXr-i*step_m);
			y=(int)(m_AxesT+( yiMAX - yround )*(m_AxesH-m_AxesT)/(yiMAX-yiMIN));
			if ( yround<=yiMAX && yround>=yiMIN )
			{
				ytickMAX=max(ytickMAX,yround);
				ytickMIN=min(ytickMIN,yround);
				LineDraw(pDC,m_AxesL,y,m_AxesL-m_fontH20,y,m_fontH6) ;
				//LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(0,0,255),PS_DOT) ;
				label.Format("%.1f",yround);
				TextDraw(pDC,3*m_AxesL/10,y+m_fontH20,label,RGB(0,0,0),0,m_fontH30) ;
			}
			i++;
		}

	}
	else
	{
		ytickMIN=0.99*yiMIN  ;   ytickSTEP=0.01*yiMIN  ;  ytickMAX=1.01*yiMIN;
		y=m_AxesH/2;
		LineDraw(pDC,m_AxesL,y,m_AxesL-m_fontH20,y,m_fontH6) ;
		label.Format("%.1f",yiMIN);
		TextDraw(pDC,3*m_AxesL/10,y+m_fontH20,label,RGB(0,0,255),0,m_fontH30) ;
	}
	m_ytickMIN=ytickMIN;     m_ytickSTEP=ytickSTEP;  m_ytickMAX=ytickMAX;
	TextDraw(pDC,1*m_AxesL/20,(2*m_AxesT+m_AxesH)/2,_Z("Altitude (m)"),RGB(0,0,255),2700,m_fontH40,0,FW_BOLD) ;
}


void CProfileView::Xtick(CDC* pDC,double xiMIN,double xiMAX) 
{
	CProfileDoc* pDoc = (CProfileDoc *)GetDocument();
	CString label;
	double r,step_m,xround=0,xiMAXr;
	int x=0,xNum=20;

	if (xiMIN != xiMAX)
	{
		step_m = (xiMAX-xiMIN)/xNum;
		r = ((step_m>10.0) ? 10.0 : ((step_m>1.0) ? 1.0 :  ((step_m>0.1) ? 0.1 : ((step_m>0.01) ? 0.01 : 0.001))));
		step_m=((int)(((xiMAX-xiMIN)/xNum)/r))*r;
		xiMAXr=((int)(xiMAX/r))*r;

		xround=(xiMIN+xiMAX)/2.0;		int i=0;
		while ( xround<=xiMAX && xround>=xiMIN )
		{
			xround=(xiMIN+i*step_m);
			x=(int)(m_AxesL+( xround - xiMIN )*(m_AxesW-m_AxesL)/(xiMAX-xiMIN));
			if (xround<=xiMAX && xround>=xiMIN)
			{
				LineDraw(pDC,x,m_AxesH,x,m_AxesH-m_fontH20,m_fontH6) ;
				LineDraw(pDC,x,m_AxesT,x,m_AxesH,1,RGB(0,255,0),PS_DOT) ;
				label.Format("%.1f",xround);
				TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,0,0),900,m_fontH30);
			}
			i++;
		}
	}
	else
	{
		x=m_AxesW/2;
		LineDraw(pDC,x,m_AxesH,x,m_AxesH-m_fontH20,m_fontH6) ;
		label.Format("%.1f",xiMIN);
		TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,0,0),900,m_fontH30);
	}
	
	if(	pDoc->m_DrawFresnel )
	{
		label.Format(_Z("Ht_agl(m) = %.1f,  Hr_agl(m) = %.1f,  Freq.(MHz) = %.3f,  k-factor = %s,  Fresnel Zone Number = %d"),m_TxH,m_RxH,m_FrqMHz,m_kfactor,m_Fresnel);
		TextDraw(pDC,m_AxesW/10,m_AxesT/2,label,RGB(0,0,0),0,m_fontH46,0,FW_BOLD);
	}
	else
	{
		label.Format(_Z("Total Distance(km) =")+" %.3f  ,      "+_Z("k-factor")+" = %s", pDoc->Dmax,m_kfactor);
		TextDraw(pDC,m_AxesW/3,m_AxesT/2,label,RGB(0,0,0),0,m_fontH46,0,FW_BOLD);
	}
	TextDraw(pDC,m_AxesW/2,m_AxesH+6*m_AxesT/10,_Z("Distance (km)"),RGB(0,0,255),0,m_fontH44,0,FW_BOLD) ;
}

double CProfileView::MinValue(double *xi,int N) 
{
	double  xiMIN=100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMIN=min(xiMIN,xi[i]);	
	}
	return xiMIN;
}

double CProfileView::MaxValue(double *xi,int N) 
{
	double  xiMAX=-100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMAX=max(xiMAX,xi[i]);	
	}
	return xiMAX;
}

void CProfileView::OnOptionChangekfactor() 
{
	CKFactor  kfactorDLG;

	kfactorDLG.m_kfactorEdit = m_kfactor;
	if (kfactorDLG.DoModal() == IDOK)
		if (m_kfactor != kfactorDLG.m_kfactorEdit)
		{
			kfactorDLG.m_kfactorEdit.MakeLower();
			int n1=kfactorDLG.m_kfactorEdit.FindOneOf("\\!@#$%^&*()_+=qwertyuiop[]asdfghjkl;':zxcvbnm,<>?`~\"");
			int n2=kfactorDLG.m_kfactorEdit.FindOneOf("|");
			if((n1==-1) && (n2==-1))
			{
				CString xx = kfactorDLG.m_kfactorEdit;
				xx.Remove(' ');
				double yy = atof_kfactor(xx);

				if		(yy<-20)				yy = -20;
				else if((yy>-0.01)&&(yy<0))		yy = -0.01;
				else if((yy>=0)&&(yy<0.01))		yy =  0.01;
				else if(yy>20)					yy =  20;
				xx.Format("%g",yy);	m_kfactor = xx;

			//	m_kfactor = kfactorDLG.m_kfactorEdit;
			//	m_kfactor.Remove(' ');
				InvalidateRect(NULL,false);
			}
			else
			{
				CString str;
				str.Format(_Z("{  k-factor = ''  %s  ''  }  is not valid.\t"),kfactorDLG.m_kfactorEdit);
				if (MessageBox(str,_Z("ERROR!!!"),MB_RETRYCANCEL | MB_ICONERROR)==IDRETRY)
					OnOptionChangekfactor();
			}
		}
}

double CProfileView::InterpXY(double *D0,double *E0,double d,int num)
{
	double d1,d2,E1,E2,Eb;
	int m;

	if (d<=D0[0])
		m=0;
	else if (d>=D0[num-1])
		m=num-2;
	else
	{
		int n=0;
		while(D0[n]<=d)
			n++;

		m=n-1;
	}

		d1=D0[m];d2=D0[m+1];
		E1=E0[m];E2=E0[m+1];

	Eb = E1+(E2-E1)*(d-d1)/(d2-d1);
	return Eb;
}

void CProfileView::OnOptionChangefresnelzoneparameters() 
{
	CFresnelDLG xx;
	xx.m_TxH = m_TxH;
	xx.m_RxH = m_RxH;
	xx.m_FrqMHz = m_FrqMHz;
	xx.m_Fresnel = m_Fresnel;

	if (xx.DoModal()==IDOK)
	{
		m_TxH = xx.m_TxH;
		m_RxH = xx.m_RxH;
		m_FrqMHz = xx.m_FrqMHz;
		m_Fresnel = xx.m_Fresnel;
		InvalidateRect(NULL,false);
	}
}
void CProfileView::OnUpdateOptionChangefresnelzoneparameters(CCmdUI* pCmdUI) 
{
	CProfileDoc* pDoc = (CProfileDoc *)GetDocument();
	pCmdUI->Enable(pDoc->m_DrawFresnel);
}


double CProfileView::atof_kfactor(CString k1) 
{
	double k2 = 1.0;
	k1.Remove(' ');
	int n = k1.Find('/');
	if (n != -1)
	{
		int m = k1.GetLength();
		CString ss1 = k1.Left(n);
		CString ss2 = k1.Right(m-n-1);
		k2 = atof(ss1)/atof(ss2);
	}
	else
		k2 = atof(k1);

	return k2;
}

void CProfileView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
		m_rcPrintRect=pInfo->m_rectDraw;
	
	CView::OnPrint(pDC, pInfo);
}
BOOL CProfileView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CProfileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CProfileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
void CProfileView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}

void CProfileView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

void CProfileView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();	
	
//	initDP_LP();

	CString Title_En  = "Profile";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE1);
}

int CProfileView::DP_LP(CDC* pDC,int nH_DP) //97/10/12
{
	if (pDC->IsPrinting())		return (int)(nH_DP*30.0/12.0);

	CSize z1(0, nH_DP);
	pDC->DPtoLP(&z1);
	return z1.cy;
}

void CProfileView::initDP_LP(CDC * pDC) //97/10/12
{
//	CDC * pDC = GetDC();
//	pDC->SetMapMode(MM_LOMETRIC);

	m_fontH2   = DP_LP(pDC,  1); //2
	m_fontH6   = DP_LP(pDC,  2); //6
	m_fontH12  = DP_LP(pDC,  5); //12
	m_fontH14  = DP_LP(pDC,  6); //14
	m_fontH20  = DP_LP(pDC,  8); //20
	m_fontH24  = DP_LP(pDC, 10); //24
	m_fontH28  = DP_LP(pDC, 11); //28
	m_fontH30  = DP_LP(pDC, 12); //30
	m_fontH40  = DP_LP(pDC, 16); //40
	m_fontH44  = DP_LP(pDC, 18); //44
	m_fontH46  = DP_LP(pDC, 19); //46
	m_fontH100 = DP_LP(pDC, 40); //100
	m_fontH150 = DP_LP(pDC, 60); //150
}