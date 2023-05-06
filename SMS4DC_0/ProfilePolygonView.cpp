// ProfilePolygonView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "ProfilePolygonView.h"
#include "ProfilePolygonDoc.h"
#include <math.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePolygonView

IMPLEMENT_DYNCREATE(CProfilePolygonView, CView)

CProfilePolygonView::CProfilePolygonView()
{
	m_AxesT=0;
	m_AxesH=0;
	m_AxesL=0;
	m_AxesW=0;
	m_bLPressed=false;
	m_stPoint.x=0;
	m_stPoint.y=0;
}

CProfilePolygonView::~CProfilePolygonView()
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


BEGIN_MESSAGE_MAP(CProfilePolygonView, CView)
	//{{AFX_MSG_MAP(CProfilePolygonView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfilePolygonView drawing

void CProfilePolygonView::OnDraw(CDC* pDC)
{
	CProfilePolygonDoc* pDoc = (CProfilePolygonDoc*)GetDocument();
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

		initDP_LP(pDC);
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
		pen.CreatePen(PS_SOLID,m_fontH6,RGB(0,0,0));
		pDC->SelectObject(&pen);
		pDC->Rectangle(AxesL-2,AxesT,AxesW,AxesH);

		Np=pDoc->Np;

		double m_diMIN=MinValue(pDoc->m_di,Np);
		double m_diMAX=MaxValue(pDoc->m_di,Np);
		double m_hiMIN=MinValue(pDoc->m_hi,Np);
		double m_hiMAX=MaxValue(pDoc->m_hi,Np);
		Plot(pDC,pDoc->m_di,pDoc->m_hi,Np,  m_diMIN,m_diMAX,m_hiMIN,m_hiMAX,  m_fontH6-1,RGB(0,0,255),PS_SOLID) ;

		double *xp,*yp;
		xp=new double[pDoc->m_PolyPointNum-0];
		yp=new double[pDoc->m_PolyPointNum-0];
		int tt=0;
		xp[0] = pDoc->m_di[tt];
		yp[0] = pDoc->m_hi[tt];
		for (int k=0;k<pDoc->m_PolyPointNum-1;k++)
		{
			tt=tt+(pDoc->Npt[k]);
			xp[k+1] = pDoc->m_di[tt-1];
			yp[k+1] = pDoc->m_hi[tt-1];
			
		}
		PlotPoint(pDC,xp,yp,pDoc->m_PolyPointNum,  m_diMIN,m_diMAX,m_hiMIN,m_hiMAX,  m_fontH10,RGB(0,0,0),PS_SOLID,m_fontH12,RGB(255,255,255)) ;

		delete [] xp;
		delete [] yp;

		Xtick(pDC,m_diMIN,m_diMAX);
		YtickL(pDC,m_hiMIN,m_hiMAX);

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
// CProfilePolygonView diagnostics

#ifdef _DEBUG
void CProfilePolygonView::AssertValid() const
{
	CView::AssertValid();
}

void CProfilePolygonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProfilePolygonView message handlers

void CProfilePolygonView::Plot(CDC* pDC,double *xi, double *yi,int N,
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

void CProfilePolygonView::Xtick(CDC* pDC,double xiMIN,double xiMAX) 
{
	CProfilePolygonDoc* pDoc = (CProfilePolygonDoc*)GetDocument();
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
				TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,200,0),900,m_fontH30);
			}
			i++;
		}
	}
	else
	{
		x=m_AxesW/2;
		LineDraw(pDC,x,m_AxesH,x,m_AxesH-m_fontH20,m_fontH6) ;
		label.Format("%.1f",xiMIN);
		TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,200,0),900,m_fontH30);
	}

	label.Format(_Z("Total Distance(km) =") + " %.3f ", pDoc->Dmax);
	TextDraw(pDC,m_AxesW/3,m_AxesT/2,label,RGB(0,0,0),0,m_fontH46,0,FW_BOLD);
	TextDraw(pDC,m_AxesW/2,m_AxesH+6*m_AxesT/10,_Z("Distance (km)"),RGB(0,200,0),0,m_fontH44,0,FW_BOLD) ;
}

void CProfilePolygonView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
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


void CProfilePolygonView::LineDraw(CDC* pDC,int x1, int y1,int x2, int y2,
							int nWidth, COLORREF crColor, int nStyle) 
{
	CPen pen;
	pen.CreatePen(nStyle,nWidth,crColor);
	pDC->SelectObject(&pen);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

void CProfilePolygonView::YtickL(CDC* pDC,double yiMIN,double yiMAX) 
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
				LineDraw(pDC,m_AxesL,y,m_AxesL-m_fontH20,y,m_fontH6) ;
				LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(0,0,255),PS_DOT) ;
				label.Format("%.1f",yround);
				TextDraw(pDC,3*m_AxesL/10,y+m_fontH20,label,RGB(0,0,255),0,m_fontH30) ;
			}
			i++;
		}

	}
	else
	{
		y=m_AxesH/2;
		LineDraw(pDC,m_AxesL,y,m_AxesL-m_fontH20,y,m_fontH6) ;
		LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(0,0,255),PS_DOT) ;
		label.Format("%.1f",yiMIN);
		TextDraw(pDC,3*m_AxesL/10,y+m_fontH20,label,RGB(0,0,255),0,m_fontH30) ;
	}
	TextDraw(pDC,m_AxesL/20,(2*m_AxesT+m_AxesH)/2,_Z("Altitude (m)"),RGB(0,0,255),2700,m_fontH40,0,FW_BOLD) ;
}

double CProfilePolygonView::MinValue(double *xi,int N) 
{
	double  xiMIN=100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMIN=min(xiMIN,xi[i]);	
	}
	return xiMIN;
}

double CProfilePolygonView::MaxValue(double *xi,int N) 
{
	double  xiMAX=-100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMAX=max(xiMAX,xi[i]);	
	}
	return xiMAX;
}

void CProfilePolygonView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
	m_bLPressed=true;	
	CView::OnLButtonDown(nFlags, point);
}

void CProfilePolygonView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed=false;
	CView::OnLButtonUp(nFlags, point);
}

void CProfilePolygonView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CProfilePolygonDoc* pDoc = (CProfilePolygonDoc *)GetDocument();
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

void CProfilePolygonView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
{
	if (x < 0)
	{
		x=-x;
		xU[0]=((type=="LON") ? 'W' : 'S');
	}
	else
	{
		xU[0]=((type=="LON") ? 'E' : 'N');
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


void CProfilePolygonView::PlotPoint(CDC* pDC,double *xi, double *yi,int N,
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

//	if (nMode==0)
//		pDC->Polyline(pts, N);
//	else
//		pDC->Polygon(pts, N);

//	int len=4;
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

double CProfilePolygonView::InterpXY(double *D0,double *E0,double d,int num)
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




void CProfilePolygonView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
		m_rcPrintRect=pInfo->m_rectDraw;
	
	CView::OnPrint(pDC, pInfo);
}
void CProfilePolygonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CProfilePolygonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
BOOL CProfilePolygonView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CProfilePolygonView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}

void CProfilePolygonView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}


void CProfilePolygonView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

//	initDP_LP();

	CString Title_En  = "Profile Polygon";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE4);
}

int CProfilePolygonView::DP_LP(CDC* pDC,int nH_DP) //97/10/12
{
	if (pDC->IsPrinting())		return (int)(nH_DP*30.0/12.0);

	CSize z1(0, nH_DP);
	pDC->DPtoLP(&z1);
	return z1.cy;
}

void CProfilePolygonView::initDP_LP(CDC * pDC) //97/10/12
{
//	CDC * pDC = GetDC();
//	pDC->SetMapMode(MM_LOMETRIC);

	m_fontH2   = DP_LP(pDC,  1); //2
	m_fontH6   = DP_LP(pDC,  2); //6
	m_fontH10  = DP_LP(pDC,  4); //10
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