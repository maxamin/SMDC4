// Pro_LoS_LineView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_LoS_LineView.h"
#include "Pro_LoS_LineDoc.h"
#include "MainFrm.h"
#include <math.h>

#include "LoSDLG.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineView

IMPLEMENT_DYNCREATE(CPro_LoS_LineView, CView)

CPro_LoS_LineView::CPro_LoS_LineView()
{
	m_AxesT=0;
	m_AxesH=0;
	m_AxesL=0;
	m_AxesW=0;
	m_bLPressed=false;
	m_stPoint.x=0;
	m_stPoint.y=0;

}

CPro_LoS_LineView::~CPro_LoS_LineView()
{
}


BEGIN_MESSAGE_MAP(CPro_LoS_LineView, CView)
	//{{AFX_MSG_MAP(CPro_LoS_LineView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_OPTION_CHANGEPARAMETERS, OnOptionChangeparameters)
	ON_COMMAND(ID_Refresh, OnRefresh)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineView drawing

void CPro_LoS_LineView::OnDraw(CDC* pDC)
{
	CPro_LoS_LineDoc* pDoc = (CPro_LoS_LineDoc*)GetDocument();
	if (pDoc->m_ReadyDoc == 1)
	{	
		pDC->SetMapMode(MM_LOMETRIC);

		CRect rect;
	///////////////////////////////////////
		if (pDC->IsPrinting())
			rect=m_rcPrintRect;
		else
			GetClientRect(&rect);
		pDC->DPtoLP(&rect);
	///////////////////////////////////////

		CBrush brush(RGB(204,204,204));
		pDC->FillRect(rect,&brush);

		int AxesW=(int)((0.92)*(rect.Width()));
		int AxesH=(int)((0.90)*(rect.Height()));
		int AxesT=(int)(rect.top+(rect.Height())- AxesH );
		int AxesL=(int)(rect.left+(rect.Width())- AxesW );
		m_AxesT=AxesT;
		m_AxesH=AxesH;
		m_AxesW=AxesW;
		m_AxesL=AxesL;

		CPen pen;
		pen.CreatePen(PS_SOLID,5,RGB(0,0,0));
		pDC->SelectObject(&pen);
		pDC->Rectangle(AxesL-2,AxesT,AxesW+6,AxesH);

		double Hmin=pDoc->Hmin;
		Np=pDoc->Np;
		double d = pDoc->Dmax - pDoc->Dmin;
		

		double pi=4.0*atan(1.0);
		double re=6371.0*(pDoc->Linek);
		double a=re*sin(d/(2.0*re));
		double b=-re*cos(d/(2.0*re));
		double *phi;	phi=new double[Np];
		double *xc;		xc=new double[Np];
		double *yc;		yc=new double[Np];
		double *xp1;	xp1=new double[Np];
		double *yp1;	yp1=new double[Np];
		double *xp0;	xp0=new double[Np];
		double *yp0;	yp0=new double[Np];
		double *xp;		xp=new double[Np];
		double *yp;		yp=new double[Np];

		for (int i=0;i<Np;i++)
		{
			phi[i]=(pi/2.0)+(d/(2.0*re))-(pDoc->m_di[i]/(re));
			xc[i]=a+re*cos(phi[i]);
			yc[i]=b+re*sin(phi[i]);
			yc[i]=Hmin+1000.0*yc[i];

			xp1[i]=a+(re+pDoc->Er1[i]/1000.0-Hmin/1000.0)*cos(phi[i]);
			yp1[i]=b+(re+pDoc->Er1[i]/1000.0-Hmin/1000.0)*sin(phi[i]);
			yp1[i]=Hmin+1000.0*yp1[i];

			xp0[i]=a+(re+pDoc->Er0[i]/1000.0-Hmin/1000.0)*cos(phi[i]);
			yp0[i]=b+(re+pDoc->Er0[i]/1000.0-Hmin/1000.0)*sin(phi[i]);
			yp0[i]=Hmin+1000.0*yp0[i];

			xp[i]=a+(re+pDoc->m_hi[i]/1000.0-Hmin/1000.0)*cos(phi[i]);
			yp[i]=b+(re+pDoc->m_hi[i]/1000.0-Hmin/1000.0)*sin(phi[i]);
			yp[i]=Hmin+1000.0*yp[i];

		}

		double *xpc1;		xpc1=new double[2*Np];
		double *ypc1;		ypc1=new double[2*Np];
		double *xpc0;		xpc0=new double[2*Np];
		double *ypc0;		ypc0=new double[2*Np];
		double *xpc;		xpc=new double[2*Np];
		double *ypc;		ypc=new double[2*Np];
		for ( i=0;i<Np;i++)
		{
			xpc1[i]=xp1[i];
			ypc1[i]=yp1[i];
			xpc1[Np+i]=xc[Np-i-1];
			ypc1[Np+i]=yc[Np-i-1];

			xpc0[i]=xp0[i];
			ypc0[i]=yp0[i];
			xpc0[Np+i]=xc[Np-i-1];
			ypc0[Np+i]=yc[Np-i-1];

			xpc[i]=xp[i];
			ypc[i]=yp[i];
			xpc[Np+i]=xc[Np-i-1];
			ypc[Np+i]=yc[Np-i-1];

		}
		double xpc1MIN=MinValue(xpc1,Np);
		double xpc1MAX=MaxValue(xpc1,Np);
		double ypc1MIN=MinValue(ypc1,Np);
		double ypc1MAX=MaxValue(ypc1,Np);

		double xpc0MIN=MinValue(xpc0,Np);
		double xpc0MAX=MaxValue(xpc0,Np);
		double ypc0MIN=MinValue(ypc0,Np);
		double ypc0MAX=MaxValue(ypc0,Np);

		double xpcMIN=MinValue(xpc,Np);
		double xpcMAX=MaxValue(xpc,Np);
		double ypcMIN=MinValue(ypc,Np);
		double ypcMAX=MaxValue(ypc,Np);

		double xcMIN=MinValue(xc,Np);
		double xcMAX=MaxValue(xc,Np);
		double ycMIN=MinValue(yc,Np);
		double ycMAX=MaxValue(yc,Np);

		double xMIN = min(min(xcMIN,xpc0MIN) ,xpc1MIN);
		double yMIN = min(min(ycMIN,ypc0MIN) ,ypc1MIN);
		double xMAX = max(max(xcMAX,xpc0MAX) ,xpc1MAX);
		double yMAX = max(max(ycMAX,ypc0MAX) ,ypc1MAX);

		Plot(pDC,xpc0,ypc0,2*Np,  xMIN,xMAX,yMIN,yMAX,  4,RGB(0,127,255),PS_SOLID,1,RGB(0,127,255)) ;
		Plot(pDC,xpc1,ypc1,2*Np,  xMIN,xMAX,yMIN,yMAX,  4,RGB(255,0,0),PS_SOLID,1,RGB(255,0,0)) ;

		Plot(pDC,xpc,ypc,2*Np,  xMIN,xMAX,yMIN,yMAX,  5,RGB(0,0,127),PS_SOLID,0,RGB(0,0,127)) ;
		Plot(pDC,xc,yc,Np,  xMIN,xMAX,yMIN,yMAX,  5,RGB(128,0,0),PS_SOLID,1,RGB(204,204,204)) ;
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

		delete [] xpc1;
		delete [] ypc1;
		delete [] xpc0;
		delete [] ypc0;
		delete [] xpc;
		delete [] ypc;
		delete [] xc;
		delete [] yc;
		delete [] phi;
		delete [] xp1;
		delete [] yp1;
		delete [] xp0;
		delete [] yp0;
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
	else
		GetParentFrame()->ShowWindow(SW_HIDE);
}

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineView diagnostics

#ifdef _DEBUG
void CPro_LoS_LineView::AssertValid() const
{
	CView::AssertValid();
}

void CPro_LoS_LineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineView message handlers


void CPro_LoS_LineView::Plot(CDC* pDC,double *xi, double *yi,int N,
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
		pts[i].x = Round( AxesL + (AxesW - AxesL)*(xi[i] - xiMIN)/(xiMAX-xiMIN) );
		pts[i].y = Round( AxesH + (AxesT - AxesH)*(yi[i] - yiMIN)/(yiMAX-yiMIN) );
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

void CPro_LoS_LineView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
							int Escapement,
							int nHeight,int nWidth,int FontWeight,CString FontName) 
{
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


void CPro_LoS_LineView::LineDraw(CDC* pDC,int x1, int y1,int x2, int y2,
							int nWidth, COLORREF crColor, int nStyle) 
{
	CPen pen;
	pen.CreatePen(nStyle,nWidth,crColor);
	pDC->SelectObject(&pen);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

double CPro_LoS_LineView::Distance_km(double lat1,double lon1,double lat2,double lon2) 
{
	double temp1,temp2,temp3,rng;

	double pi = 4.0*atan(1.0);
	double R = 6371.0;

	lat1=lat1*pi/180.0;
	lat2=lat2*pi/180.0;
	lon1=lon1*pi/180.0;
	lon2=lon2*pi/180.0;

	temp1 = sin(lat1)*sin(lat2);
	temp2 = cos(lat1)*cos(lat2)*cos(lon2-lon1);
	temp3 = temp1+temp2;
	temp3=min(1.0,max(-1.0,temp3));
	rng = acos(temp3);

	rng=R*rng;    //km
	return rng;
}

double CPro_LoS_LineView::MinValue(double *xi,int N) 
{
	double  xiMIN=100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMIN=min(xiMIN,xi[i]);	
	}
	return xiMIN;
}

double CPro_LoS_LineView::MaxValue(double *xi,int N) 
{
	double  xiMAX=-100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMAX=max(xiMAX,xi[i]);	
	}
	return xiMAX;
}



void CPro_LoS_LineView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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


int CPro_LoS_LineView::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);

}

void CPro_LoS_LineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
	m_bLPressed=true;
	CView::OnLButtonDown(nFlags, point);
}

void CPro_LoS_LineView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed=false;
	CView::OnLButtonUp(nFlags, point);
}

void CPro_LoS_LineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CPro_LoS_LineDoc* pDoc = (CPro_LoS_LineDoc*)GetDocument();

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


		double E = InterpXY(pDoc->m_di,pDoc->Er,rng,Np);
		E=double(Round(E));

		string.Format(_Z("Line of Sight :")+" %s",((E==1.0) ? _Z("Yes") : _Z("No")) );
		//string.Format("%0.3f",E );

		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(5, string);

		m_stPoint=point;
	}
		CView::OnMouseMove(nFlags, point);
}

void CPro_LoS_LineView::YtickL(CDC* pDC,double yiMIN,double yiMAX) 
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
				LineDraw(pDC,m_AxesL,y,m_AxesL-20,y,6) ;
				//LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(0,0,255),PS_DOT) ;
				label.Format("%.1f",yround);
				TextDraw(pDC,3*m_AxesL/10,y+20,label,RGB(0,0,0),0,38) ;
			}
			i++;
		}

	}
	else
	{
		ytickMIN=0.99*yiMIN  ;   ytickSTEP=0.01*yiMIN  ;  ytickMAX=1.01*yiMIN;
		y=m_AxesH/2;
		LineDraw(pDC,m_AxesL,y,m_AxesL-20,y,6) ;
		label.Format("%.1f",yiMIN);
		TextDraw(pDC,3*m_AxesL/10,y+20,label,RGB(0,0,255),0,38) ;
	}
	m_ytickMIN=ytickMIN;     m_ytickSTEP=ytickSTEP;  m_ytickMAX=ytickMAX;
	TextDraw(pDC,1*m_AxesL/20,(2*m_AxesT+m_AxesH)/2,_Z("Altitude (m)"),RGB(0,0,255),2700,40,0,FW_BOLD) ;
}


void CPro_LoS_LineView::Xtick(CDC* pDC,double xiMIN,double xiMAX) 
{
	CPro_LoS_LineDoc* pDoc = (CPro_LoS_LineDoc *)GetDocument();
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
				LineDraw(pDC,x,m_AxesH,x,m_AxesH-20,6) ;
				LineDraw(pDC,x,m_AxesT,x,m_AxesH,1,RGB(0,255,0),PS_DOT) ;
				label.Format("%.1f",xround);
				TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,38);
			}
			i++;
		}
	}
	else
	{
		x=m_AxesW/2;
		LineDraw(pDC,x,m_AxesH,x,m_AxesH-20,6) ;
		label.Format("%.1f",xiMIN);
		TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,38);
	}

	label.Format(_Z("Total Distance(km) = %.3f  ,   k-factor = %.6f  ,  Receiver Height_AGL(m) = %0.1f"), pDoc->Dmax,pDoc->Linek,pDoc->LineRxH);
	TextDraw(pDC,m_AxesW/4,m_AxesT/2,label,RGB(0,0,0),0,46,0,FW_BOLD);
	TextDraw(pDC,m_AxesW/2,m_AxesH+6*m_AxesT/10,_Z("Distance (km)"),RGB(0,0,255),0,44,0,FW_BOLD) ;
}


void CPro_LoS_LineView::OnOptionChangeparameters() 
{
	CPro_LoS_LineDoc* pDoc = (CPro_LoS_LineDoc*)GetDocument();

	CLoSDLG Linedlg;
	Linedlg.m_title = _Z("Line of Sight Model Parameters");
	Linedlg.m_kfactor = pDoc->Linek;
	Linedlg.m_RxH = pDoc->LineRxH;
	if (Linedlg.DoModal()==IDOK)
	{
		if ( (pDoc->Linek != Linedlg.m_kfactor) || (pDoc->LineRxH != Linedlg.m_RxH) )
		{
			pDoc->Linek = Linedlg.m_kfactor;
			pDoc->LineRxH = Linedlg.m_RxH;
			pDoc->GetData();
			Invalidate();
		}
	}
}

void CPro_LoS_LineView::OnRefresh() 
{
	Invalidate();	
}

double CPro_LoS_LineView::InterpXY(double *D0,double *E0,double d,int num)
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

void CPro_LoS_LineView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
		m_rcPrintRect=pInfo->m_rectDraw;
	CView::OnPrint(pDC, pInfo);
}
void CPro_LoS_LineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CPro_LoS_LineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
BOOL CPro_LoS_LineView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CPro_LoS_LineView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}

void CPro_LoS_LineView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

void CPro_LoS_LineView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "Line Calculation (Line of Sight)";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 
	
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE20);
}
