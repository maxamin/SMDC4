// Pro_P370_PolygonView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P370_PolygonView.h"
#include "Pro_P370_PolygonDoc.h"

#include "MainFrm.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_PolygonView

IMPLEMENT_DYNCREATE(CPro_P370_PolygonView, CView)

CPro_P370_PolygonView::CPro_P370_PolygonView()
{
	m_AxesT=0;
	m_AxesH=0;
	m_AxesL=0;
	m_AxesW=0;
	m_bLPressed=false;
	m_stPoint.x=0;
	m_stPoint.y=0;
}

CPro_P370_PolygonView::~CPro_P370_PolygonView()
{
}


BEGIN_MESSAGE_MAP(CPro_P370_PolygonView, CView)
	//{{AFX_MSG_MAP(CPro_P370_PolygonView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_PolygonView drawing

void CPro_P370_PolygonView::OnDraw(CDC* pDC)
{
	CPro_P370_PolygonDoc* pDoc = (CPro_P370_PolygonDoc*)GetDocument();
	if(pDoc->m_ReadyDoc ==1)
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

		Np=pDoc->Np;

		double m_diMIN=MinValue(pDoc->m_di,Np);
		double m_diMAX=MaxValue(pDoc->m_di,Np);
		double m_hiMIN=MinValue(pDoc->m_hi,Np);
		double m_hiMAX=MaxValue(pDoc->m_hi,Np);
		Plot(pDC,pDoc->m_di,pDoc->m_hi,Np,  m_diMIN,m_diMAX,m_hiMIN,m_hiMAX,  6,RGB(0,0,255),PS_SOLID) ;
		
		double ErMIN=MinValue(pDoc->Er,Np);
		double ErMAX=MaxValue(pDoc->Er,Np);
		Plot(pDC,pDoc->m_di,pDoc->Er,Np,  m_diMIN,m_diMAX,ErMIN,ErMAX,  6,RGB(128,0,0),PS_SOLID) ;


		double *xp,*yp;
		xp=new double[pDoc->m_PolyPointNum];
		yp=new double[pDoc->m_PolyPointNum];
		int tt=0;
		xp[0] = pDoc->m_di[tt];
		yp[0] = pDoc->m_hi[tt];
		for (int k=0;k<pDoc->m_PolyPointNum-1;k++)
		{
			tt=tt+(pDoc->Npt[k]);
			xp[k+1] = pDoc->m_di[tt-1];
			yp[k+1] = pDoc->m_hi[tt-1];
			
		}
		PlotPoint(pDC,xp,yp,pDoc->m_PolyPointNum,  m_diMIN,m_diMAX,m_hiMIN,m_hiMAX,  10,RGB(0,0,0),PS_SOLID,14,RGB(255,255,255)) ;

		delete [] xp;
		delete [] yp;

		Xtick(pDC,m_diMIN,m_diMAX);
		YtickL(pDC,m_hiMIN,m_hiMAX);
		YtickR(pDC,ErMIN,ErMAX);

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
// CPro_P370_PolygonView diagnostics

#ifdef _DEBUG
void CPro_P370_PolygonView::AssertValid() const
{
	CView::AssertValid();
}

void CPro_P370_PolygonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_PolygonView message handlers


void CPro_P370_PolygonView::Plot(CDC* pDC,double *xi, double *yi,int N,
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

void CPro_P370_PolygonView::Xtick(CDC* pDC,double xiMIN,double xiMAX) 
{
	CPro_P370_PolygonDoc* pDoc = (CPro_P370_PolygonDoc*)GetDocument();
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
				TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,200,0),900,38);
			}
			i++;
		}
	}
	else
	{
		x=m_AxesW/2;
		LineDraw(pDC,x,m_AxesH,x,m_AxesH-20,6) ;
		label.Format("%.1f",xiMIN);
		TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,200,0),900,38);
	}

	label.Format(_Z("Total Distance(km) = %.3f  ,Station Name = %s"), pDoc->Dmax,pDoc->LineName_ST);
	TextDraw(pDC,m_AxesW/3,m_AxesT/2,label,RGB(0,0,0),0,46,0,FW_BOLD);
	TextDraw(pDC,m_AxesW/2,m_AxesH+6*m_AxesT/10,_Z("Distance (km)"),RGB(0,200,0),0,44,0,FW_BOLD) ;
}

void CPro_P370_PolygonView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
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


void CPro_P370_PolygonView::LineDraw(CDC* pDC,int x1, int y1,int x2, int y2,
							int nWidth, COLORREF crColor, int nStyle) 
{
	CPen pen;
	pen.CreatePen(nStyle,nWidth,crColor);
	pDC->SelectObject(&pen);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

double CPro_P370_PolygonView::Distance_km(double lat1,double lon1,double lat2,double lon2) 
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


void CPro_P370_PolygonView::YtickL(CDC* pDC,double yiMIN,double yiMAX) 
{
	CString label;
	double r,step_m,yround=0,yiMAXr;
	int y=0,yNum=20;

	if (yiMAX != yiMIN)
	{
		step_m = (yiMAX-yiMIN)/yNum;
		r = ((step_m>10.0) ? 10.0 : ((step_m>1.0) ? 1.0 :  ((step_m>0.1) ? 0.1 : ((step_m>0.01) ? 0.01 : 0.001))));
		step_m=((int)(((yiMAX-yiMIN)/yNum)/r))*r;
		yiMAXr=((int)(yiMAX/r))*r;

		yround=(yiMIN+yiMAX)/2.0;		int i=0;
		while ( yround<=yiMAX && yround>=yiMIN )
		{
			yround=(yiMAXr-i*step_m);
			y=(int)(m_AxesT+( yiMAX - yround )*(m_AxesH-m_AxesT)/(yiMAX-yiMIN));
			if ( yround<=yiMAX && yround>=yiMIN )
			{
				LineDraw(pDC,m_AxesL,y,m_AxesL-20,y,6) ;
				LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(0,0,255),PS_DOT) ;
				label.Format("%.1f",yround);
				TextDraw(pDC,3*m_AxesL/10,y+20,label,RGB(0,0,255),0,38) ;
			}
			i++;
		}

	}
	else
	{
		y=m_AxesH/2;
		LineDraw(pDC,m_AxesL,y,m_AxesL-20,y,6) ;
		LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(0,0,255),PS_DOT) ;
		label.Format("%.1f",yiMIN);
		TextDraw(pDC,3*m_AxesL/10,y+20,label,RGB(0,0,255),0,38) ;
	}
	TextDraw(pDC,m_AxesL/20,(2*m_AxesT+m_AxesH)/2,_Z("Altitude (m)"),RGB(0,0,255),2700,40,0,FW_BOLD) ;
}


void CPro_P370_PolygonView::YtickR(CDC* pDC,double yiMIN,double yiMAX) 
{
	CString label;
	double r,step_m,yround=0,yiMAXr;
	int y=0,yNum=20;

	if (yiMAX != yiMIN)
	{
		step_m = (yiMAX-yiMIN)/yNum;
		r = ((step_m>10.0) ? 10.0 : ((step_m>1.0) ? 1.0 :  ((step_m>0.1) ? 0.1 : ((step_m>0.01) ? 0.01 : 0.001))));
		step_m=((int)(((yiMAX-yiMIN)/yNum)/r))*r;
		yiMAXr=((int)(yiMAX/r))*r;

		yround=(yiMIN+yiMAX)/2.0;		int i=0;
		while ( yround<=yiMAX && yround>=yiMIN )
		{
		//	yround=(yiMAXr-i*step_m);
			yround=(yiMAX-i*step_m);
			y=(int)(m_AxesT+( yiMAX - yround )*(m_AxesH-m_AxesT)/(yiMAX-yiMIN));
			if ( yround<=yiMAX && yround>=yiMIN )
			{
				LineDraw(pDC,m_AxesW-1,y,m_AxesW+20,y,6) ;
				//LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(128,0,0),PS_DOT) ;
				label.Format("%.2f",yround);
				TextDraw(pDC,m_AxesW+1*m_AxesL/5,y+20,label,RGB(128,0,0),0,38) ;
			}
			i++;
		}
	}
	else
	{
		y=m_AxesH/2;
		LineDraw(pDC,m_AxesW-1,y,m_AxesW+20,y,6) ;
		label.Format("%.2f",yiMIN);
		TextDraw(pDC,m_AxesW+1*m_AxesL/5,y+20,label,RGB(128,0,0),0,38) ;
	}
	TextDraw(pDC,m_AxesW+3*m_AxesL/5,(3*m_AxesT+m_AxesH)/2,_Z("Field strength (dBuV/m)"),RGB(128,0,0),2700,42,0,FW_BOLD) ;
}

double CPro_P370_PolygonView::MinValue(double *xi,int N) 
{
	double  xiMIN=100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMIN=min(xiMIN,xi[i]);	
	}
	return xiMIN;
}

double CPro_P370_PolygonView::MaxValue(double *xi,int N) 
{
	double  xiMAX=-100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMAX=max(xiMAX,xi[i]);	
	}
	return xiMAX;
}

void CPro_P370_PolygonView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
	m_bLPressed=true;
	CView::OnLButtonDown(nFlags, point);
}

void CPro_P370_PolygonView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed=false;
	CView::OnLButtonUp(nFlags, point);
}

void CPro_P370_PolygonView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CPro_P370_PolygonDoc* pDoc = (CPro_P370_PolygonDoc*)GetDocument();

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
	//	int ind ;
	//	ind=(int)(0.0+((double)(Np-1.0-0.0))*((double)(point.x-m_AxesL))/((double)(m_AxesW-m_AxesL)));
	//	string.Format("Alt(m) : %0.0f", pDoc->m_hi[ind]  );

		string.Format("Alt(m) : %0.0f", y  );
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(3, string);

		double yUTM = InterpXY(pDoc->m_di,pDoc->m_lati,rng,Np);
		double xUTM = InterpXY(pDoc->m_di,pDoc->m_loni,rng,Np);
	//	double yUTM=	pDoc->m_lati[ind];
	//	double xUTM=	pDoc->m_loni[ind];

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
		string.Format("E(dBuV/m) : %0.3f", E  );

	//	string.Format("E(dBuV/m) : %0.3f", pDoc->Er[ind]  );
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(5, string);

		m_stPoint=point;
	}
	
	CView::OnMouseMove(nFlags, point);
}


void CPro_P370_PolygonView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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


int CPro_P370_PolygonView::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);

}


double CPro_P370_PolygonView::Interp(double *hi , int Np , double x) 
{
	int x1,x2;
	double y;

	if (x < 0.0)
		x1=0;

	else if (x > (double)(Np-1))
		x1=Np-2;

	else
		x1=(int)x;

	x2=x1+1;

	if ( (double)x1 == x)
		y = hi[x1];
	else
		y=  hi[x1]+(hi[x2]-hi[x1])*(x-x1)/(x2-x1);

	return y ;

}


void CPro_P370_PolygonView::PlotPoint(CDC* pDC,double *xi, double *yi,int N,
						double xiMIN,double xiMAX,double yiMIN,double yiMAX,
						int nWidth,COLORREF crColor, int nStyle, int nRadius,COLORREF flColor) 
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

	for (int k=0;k<N;k++)
	{
		pDC->Ellipse(	pts[k].x-nRadius,
						pts[k].y-nRadius,
						pts[k].x+nRadius,
						pts[k].y+nRadius);
	}


	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	delete [] pts;
}

double CPro_P370_PolygonView::InterpXY(double *D0,double *E0,double d,int num)
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

void CPro_P370_PolygonView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
		m_rcPrintRect=pInfo->m_rectDraw;
	CView::OnPrint(pDC, pInfo);
}
void CPro_P370_PolygonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CPro_P370_PolygonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
BOOL CPro_P370_PolygonView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CPro_P370_PolygonView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}

void CPro_P370_PolygonView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}


void CPro_P370_PolygonView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "Polygon Calculation (P370)";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE22);
}
