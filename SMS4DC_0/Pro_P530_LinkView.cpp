// Pro_P530_LinkView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P530_LinkView.h"
#include <math.h>
#include "MainFrm.h"
//#include "P530_Functions.h"
#include "P530availabilityDLG.h"

#include "P530RefPointsDLG.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P530_LinkView

IMPLEMENT_DYNCREATE(CPro_P530_LinkView, CFormView)

CPro_P530_LinkView::CPro_P530_LinkView()
	: CFormView(CPro_P530_LinkView::IDD)
{
	//{{AFX_DATA_INIT(CPro_P530_LinkView)
	m_Frequency = 0.0;
	m_Gr = 0.0;
	m_Gt = 0.0;
	m_Hr = 0.0;
	m_Ht = 0.0;
	m_Lcr = 3.0;
	m_Lct = 3.0;
	m_Lml = _T("");
	m_Pb = _T("");
	m_Pbw = _T("");
	m_Pi = _T("");
	m_Pid = _T("");
	m_Po = _T("");
	m_Pow = _T("");
	m_Pr = _T("");
	m_Prd = _T("");
	m_R = 50.0;
	m_RxName = _T("");
	m_S = _T("0.0");
	m_Sw = _T("");
	m_TxName = _T("");
	m_VSWR1 = _T("");
	m_VSWR2 = _T("1.5");
	m_VSWR2w = _T("");
	m_kfactor = 0.0;
	m_timePC = 0.0;
	m_tit = _T("");
	m_Loss1 = _T("");
	m_Loss2 = _T("");
	m_Loss3 = _T("");
	m_Loss4 = _T("");
	m_Distance = _T("");
	m_FsLoss = _T("");
	m_Loss5 = _T("");
	m_FFM = _T("");
	m_FRL = _T("");
	m_TGL = _T("");
	m_thr = _T("");
	m_thr2 = _T("");
	m_Clearance = _T("");
	m_NFD = _T("");
	m_FrequencyR = 0.0;
	//}}AFX_DATA_INIT

	m_bLPressed=false;
	m_bRPressed=false;

	m_AxesT=0;
	m_AxesH=0;
	m_AxesL=0;
	m_AxesW=0;
	m_stPoint.x = 0;
	m_stPoint.y = 0;

	m_InitForm = true;
	m_Nref = 0;
	m_d0 = 0.5;
}

CPro_P530_LinkView::~CPro_P530_LinkView()
{
	if(m_Nref>0)
	{
		delete [] m_xref;
		delete [] m_yref;

		delete [] m_Delta_R;
		delete [] m_Grazing;
	}
}

void CPro_P530_LinkView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPro_P530_LinkView)
	DDX_Text(pDX, IDC_EDIT_Frequncy, m_Frequency);
	DDX_Text(pDX, IDC_EDIT_Gr, m_Gr);
	DDX_Text(pDX, IDC_EDIT_Gt, m_Gt);
	DDX_Text(pDX, IDC_EDIT_Hr, m_Hr);
	DDX_Text(pDX, IDC_EDIT_Ht, m_Ht);
	DDX_Text(pDX, IDC_EDIT_Lcr, m_Lcr);
	DDX_Text(pDX, IDC_EDIT_Lct, m_Lct);
	DDX_Text(pDX, IDC_EDIT_Lml, m_Lml);
	DDX_Text(pDX, IDC_EDIT_Pb, m_Pb);
	DDX_Text(pDX, IDC_EDIT_Pbw, m_Pbw);
	DDX_Text(pDX, IDC_EDIT_Pi, m_Pi);
	DDX_Text(pDX, IDC_EDIT_Pid, m_Pid);
	DDX_Text(pDX, IDC_EDIT_Po, m_Po);
	DDX_Text(pDX, IDC_EDIT_Pow, m_Pow);
	DDX_Text(pDX, IDC_EDIT_Pr, m_Pr);
	DDX_Text(pDX, IDC_EDIT_Prd, m_Prd);
	DDX_Text(pDX, IDC_EDIT_R, m_R);
	DDX_Text(pDX, IDC_EDIT_RxName, m_RxName);
	DDX_Text(pDX, IDC_EDIT_S, m_S);
	DDX_Text(pDX, IDC_EDIT_Sw, m_Sw);
	DDX_Text(pDX, IDC_EDIT_TxName, m_TxName);
	DDX_Text(pDX, IDC_EDIT_VSWR1, m_VSWR1);
	DDX_Text(pDX, IDC_EDIT_VSWR2, m_VSWR2);
	DDX_Text(pDX, IDC_EDIT_VSWR2w, m_VSWR2w);
	DDX_Text(pDX, IDC_EDIT_k, m_kfactor);
	DDX_Text(pDX, IDC_EDIT_timePC, m_timePC);
	DDX_Text(pDX, IDC_EDIT_tit, m_tit);
	DDX_Text(pDX, IDC_EDIT_Loss1, m_Loss1);
	DDX_Text(pDX, IDC_EDIT_Loss2, m_Loss2);
	DDX_Text(pDX, IDC_EDIT_Loss3, m_Loss3);
	DDX_Text(pDX, IDC_EDIT_Loss4, m_Loss4);
	DDX_Text(pDX, IDC_EDIT_Distance, m_Distance);
	DDX_Text(pDX, IDC_EDIT_FsLoss, m_FsLoss);
	DDX_Text(pDX, IDC_EDIT_Loss5, m_Loss5);
	DDX_Text(pDX, IDC_EDIT_FFM, m_FFM);
	DDX_Text(pDX, IDC_EDIT_FRL, m_FRL);
	DDX_Text(pDX, IDC_EDIT_TGL, m_TGL);
	DDX_Text(pDX, IDC_EDIT_thr, m_thr);
	DDX_Text(pDX, IDC_EDIT_thr2, m_thr2);
	DDX_Text(pDX, IDC_EDIT_clearance, m_Clearance);
	DDX_Text(pDX, IDC_EDIT_NFD, m_NFD);
	DDX_Text(pDX, IDC_EDIT_FrequncyR, m_FrequencyR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPro_P530_LinkView, CFormView)
	//{{AFX_MSG_MAP(CPro_P530_LinkView)
	ON_BN_CLICKED(IDC_BUTTON_Link, OnBUTTONLink)
	ON_BN_CLICKED(IDC_RADIO_R_L, OnRadioRL)
	ON_BN_CLICKED(IDC_RADIO_L_R, OnRadioLR)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_VSWR2w, OnChangeEDITVSWR2w)
	ON_EN_CHANGE(IDC_EDIT_Sw, OnChangeEDITSw)
	ON_BN_CLICKED(IDC_BUTTON_SaveProfile, OnBUTTONSaveProfile)
	ON_BN_CLICKED(IDC_BUTTON_Availability, OnBUTTONAvailability)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_EN_KILLFOCUS(IDC_EDIT_Lcr, OnKillfocusEDITLcr)
	ON_EN_KILLFOCUS(IDC_EDIT_Lct, OnKillfocusEDITLct)
	ON_EN_KILLFOCUS(IDC_EDIT_Gr, OnKillfocusEDITGr)
	ON_EN_KILLFOCUS(IDC_EDIT_Gt, OnKillfocusEDITGt)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_Refpoints, OnBUTTONRefpoints)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P530_LinkView diagnostics

#ifdef _DEBUG
void CPro_P530_LinkView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPro_P530_LinkView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P530_LinkView message handlers



void CPro_P530_LinkView::Plot(CDC* pDC,double *xi, double *yi,int N,
						double xiMIN,double xiMAX,double yiMIN,double yiMAX,
						int nWidth,COLORREF crColor, int nStyle, int nMode,COLORREF flColor) 
{
	double AxesT=m_AxesT;
	double AxesH=m_AxesH;
	double AxesW=m_AxesW;
	double AxesL=m_AxesL;
//////////////////////////plot////////////////////////////////////
	CPoint *pts; 	pts = new CPoint[N];

	for (int i=0;i<N;i++)
	{
		pts[i].x = (long)( AxesL + (AxesW - AxesL)*(xi[i] - xiMIN)/(xiMAX-xiMIN) );
		pts[i].y = (long)( AxesH + (AxesT - AxesH)*(yi[i] - yiMIN)/(yiMAX-yiMIN) );
	}
	CPen pen(nStyle, nWidth, crColor);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush brush(flColor);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	if (nMode==0)	pDC->Polyline(pts, N);
	else			pDC->Polygon(pts, N);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	delete [] pts;

}
void CPro_P530_LinkView::DrawAntSymbol(CDC* pDC,double xi, double yi,
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



void CPro_P530_LinkView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
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


void CPro_P530_LinkView::LineDraw(CDC* pDC,int x1, int y1,int x2, int y2,
							int nWidth, COLORREF crColor, int nStyle) 
{
	CPen pen;
	pen.CreatePen(nStyle,nWidth,crColor);
	pDC->SelectObject(&pen);

	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

void CPro_P530_LinkView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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

void CPro_P530_LinkView::YtickL(CDC* pDC,double yiMIN,double yiMAX) 
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
				label.Format("%.1f",yround);
		//		TextDraw(pDC,13*m_AxesL/16,y+20,label,RGB(0,0,0),0,38) ;
				TextDraw(pDC,13*m_AxesL/16,y+m_fontH20,label,RGB(0,0,0),0,m_fontH30) ;
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
//		TextDraw(pDC,13*m_AxesL/16,y+20,label,RGB(0,0,255),0,38) ;
		TextDraw(pDC,13*m_AxesL/16,y+m_fontH20,label,RGB(0,0,255),0,m_fontH30) ;
	}
	m_ytickMIN=ytickMIN;     m_ytickSTEP=ytickSTEP;  m_ytickMAX=ytickMAX;
	TextDraw(pDC,12*m_AxesL/16,(2*m_AxesT+m_AxesH)/2,_Z("Altitude (m)"),RGB(0,0,255),2700,m_fontH40,0,FW_BOLD) ;
}


void CPro_P530_LinkView::Xtick(CDC* pDC,double xiMIN,double xiMAX) 
{
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
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
		//		TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,38);
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
//		TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,38);
		TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,0,0),900,m_fontH30);
	}
	TextDraw(pDC,m_AxesL+m_AxesW/3,m_AxesH+3*m_AxesT/10,_Z("Distance (km)"),RGB(0,0,255),0,m_fontH44,0,FW_BOLD) ;
}

double CPro_P530_LinkView::MinValue(double *xi,int N) 
{
	double  xiMIN=xi[0];
	for (int i=0;i<N;i++)
	{
		xiMIN=min(xiMIN,xi[i]);	
	}
	return xiMIN;
}

double CPro_P530_LinkView::MaxValue(double *xi,int N) 
{
	double  xiMAX=xi[0];
	for (int i=0;i<N;i++)
	{
		xiMAX=max(xiMAX,xi[i]);	
	}
	return xiMAX;
}

double CPro_P530_LinkView::InterpXY(double *D0,double *E0,double d,int num)
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

void CPro_P530_LinkView::OnDraw(CDC* pDC) 
{
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();

	if(	pDoc->m_ReadyDoc == 1)
	{
		CRect rect1;
		GetClientRect(&rect1);

		m_AxesW1=(int)((0.93)*(rect1.Width()));
		m_AxesH1=(int)((0.90)*(rect1.Height()));
		m_AxesT1=(int)(rect1.top+(rect1.Height())- m_AxesH1 );
		m_AxesL1=(int)(rect1.left+(rect1.Width())- m_AxesW1 );

		m_AxesT1 = int(2*m_AxesT1);
		m_AxesL1 = int(3.6*m_AxesL1);
		m_AxesW1 = int(0.87*m_AxesW1);

		pDC->SetMapMode(MM_LOMETRIC);

		CRect rect;
	///////////////////////////////////////
		if (pDC->IsPrinting())		rect = m_rcPrintRect;
		else						GetClientRect(&rect);
		pDC->DPtoLP(&rect);

		initDP_LP(pDC);
	///////////////////////////////////////

//		CBrush brush(RGB(212,208,200));
//		pDC->FillRect(rect,&brush);

		int AxesW=(int)((0.93)*(rect.Width()));
		int AxesH=(int)((0.90)*(rect.Height()));
		int AxesT=(int)(rect.top+(rect.Height())- AxesH );
		int AxesL=(int)(rect.left+(rect.Width())- AxesW );
		AxesT = int(2*AxesT);
		AxesL = int(3.6*AxesL);
		AxesW = int(0.87*AxesW);

		m_AxesT=AxesT;
		m_AxesH=AxesH;
		m_AxesW=AxesW;
		m_AxesL=AxesL;

		CPen pen;
		pen.CreatePen(PS_SOLID,m_fontH6,RGB(0,0,0));
		pDC->SelectObject(&pen);
		pDC->Rectangle(AxesL-2,AxesT+15,AxesW+6,AxesH);

		Hmin=pDoc->Hmin;
		Np = pDoc->Np;

		double d = pDoc->Dmax - pDoc->Dmin;
		double pi = 4.0*atan(1.0);
		double re = 6371.0*pDoc->Linkk;

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

			double tt = (pDoc->LinkRxH+pDoc->m_hi[Np-1] - pDoc->LinkHagl_ST-pDoc->m_hi[0])/(1000.0*d) - d/(2.0*re);
			for ( i=0;i<Np;i++)
			{
				//%%%%%%%%% Line %%%%%%%%%%%%%%%%
				xl[i] = a + ((pDoc->LinkHagl_ST+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re-Hmin/1000.0)*cos(phi[i]);
				yl[i] = b + ((pDoc->LinkHagl_ST+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re-Hmin/1000.0)*sin(phi[i]);
				yl[i] = Hmin + 1000.0*yl[i];
				//%%%%%%%% Fresnel Zone %%%%%%%%%%%%%%%%%
//				rfi[i] = sqrt(pDoc->Linkfzn*0.3*pDoc->m_di[i]*    (d-pDoc->m_di[i])/(pDoc->LinkfMHz_ST*d));
				rfi[i] = sqrt(pDoc->Linkfzn*0.3*pDoc->m_di[i]*fabs(d-pDoc->m_di[i])/(pDoc->LinkfMHz_ST*d));  //930814
				
				xf1[i] = a + ((pDoc->LinkHagl_ST+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re-rfi[i]-Hmin/1000.0)*cos(phi[i]);
				yf1[i] = b + ((pDoc->LinkHagl_ST+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re-rfi[i]-Hmin/1000.0)*sin(phi[i]);
				yf1[i] = Hmin + 1000.0*yf1[i];
				
				xf2[i] = a + ((pDoc->LinkHagl_ST+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re+rfi[i]-Hmin/1000.0)*cos(phi[i]);
				yf2[i] = b + ((pDoc->LinkHagl_ST+pDoc->m_hi[0])/1000.0 + pDoc->m_di[i]*(tt+pDoc->m_di[i]/(2.0*re))+re+rfi[i]-Hmin/1000.0)*sin(phi[i]);
				yf2[i] = Hmin + 1000.0*yf2[i];
			}
			//%%%%%%%%% Antenna %%%%%%%%%%%%%%%
			double *xat;		xat=new double[2];
			double *yat;		yat=new double[2];
			double *xar;		xar=new double[2];
			double *yar;		yar=new double[2];

			xat[0] = xp[0];			yat[0] = yp[0];
			xat[1] = a + ((pDoc->LinkHagl_ST+pDoc->m_hi[0])/1000.0+re-Hmin/1000.0)*cos(phi[0]);
			yat[1] = b + ((pDoc->LinkHagl_ST+pDoc->m_hi[0])/1000.0+re-Hmin/1000.0)*sin(phi[0]);
			yat[1] = Hmin + 1000.0*yat[1];

			xar[0] = xp[Np-1];		yar[0] = yp[Np-1];
			xar[1] = a + ((pDoc->LinkRxH+pDoc->m_hi[Np-1])/1000.0+re-Hmin/1000.0)*cos(phi[Np-1]);
			yar[1] = b + ((pDoc->LinkRxH+pDoc->m_hi[Np-1])/1000.0+re-Hmin/1000.0)*sin(phi[Np-1]);
			yar[1] = Hmin + 1000.0*yar[1];
			
			double yf1MIN = MinValue(yf1,Np);
			double yf1MAX = MaxValue(yf1,Np);
			double yf2MIN = MinValue(yf2,Np);
			double yf2MAX = MaxValue(yf2,Np);
			double yfMIN = min(yf1MIN,yf2MIN);
			double yfMAX = max(yf1MAX,yf2MAX);
			yMIN = min(yMIN,yfMIN);
			yMAX = max(yMAX,yfMAX);

			Plot(pDC,xpc,ypc,2*Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_SOLID,1,RGB(0,200,0)) ;
			Plot(pDC,xc,yc,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6,RGB(128,0,0),PS_SOLID,1,RGB(212,208,200)) ;

			Plot(pDC,xl,yl,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(255,0,0),PS_SOLID,0) ;

			Plot(pDC,xf1,yf1,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_DASH,0) ;
			Plot(pDC,xf2,yf2,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_DASH,0) ;

			Plot(pDC,xat,yat,2,  xMIN,xMAX,yMIN,yMAX,  m_fontH14,RGB(0,0,255),PS_SOLID,0) ;
			Plot(pDC,xar,yar,2,  xMIN,xMAX,yMIN,yMAX,  m_fontH14,RGB(0,0,255),PS_SOLID,0) ;
			DrawAntSymbol(pDC,xat[1],yat[1],  xMIN,xMAX,yMIN,yMAX,  RGB(255,0,0),1) ;
			DrawAntSymbol(pDC,xar[1],yar[1],  xMIN,xMAX,yMIN,yMAX,  RGB(255,0,0),0) ;

			delete [] rfi;
			delete [] xl;	delete [] yl;
			delete [] xf1;	delete [] yf1;
			delete [] xf2;	delete [] yf2;

////////////////////////Reflection Points/////////////////////////////////
			double *xpp;	xpp   = new double[Np-2];
			double *ypp;	ypp   = new double[Np-2];
			double *AA;		AA    = new double[Np-2];
			double *x2;		x2    = new double[Np-2];
			double *y2;		y2    = new double[Np-2];
			double *x2t;	x2t   = new double[Np-2];
			double *y2t;	y2t   = new double[Np-2];
			double *Delta_R1;		Delta_R1    = new double[Np-2];
			double *Grazing1;		Grazing1    = new double[Np-2];
			double *Delta_R2;		Delta_R2    = new double[Np-2];
			double *Grazing2;		Grazing2    = new double[Np-2];
			double *Delta_R2t;		Delta_R2t    = new double[Np-2];
			double *Grazing2t;		Grazing2t    = new double[Np-2];

			int ii,nt,nr,Nref = 0, ntr = 0, kref = 0;
			double  y, xpp1,ypp1 , xrefD[3], yrefD[3];

		//	double * xidif;	xidif = new double[Np-1];
		//	double m1,m2,mt , T1, T2 ,x01,x02,y01,y02,step0;
		//	diff(xp,xidif,Np);
		//	step0 = MinValue(xidif,Np-1)/1000.0;
		//	delete [] xidif;

			for(int i=0;i<Np-2;i++)
			{
				xpp[i] = xp[i+1];	ypp[i] = yp[i+1];

		//		m1 = 0.001*(ypp[i]-yat[1])/(xpp[i]-xat[1]);
		//		m2 = 0.001*(ypp[i]-yar[1])/(xpp[i]-xar[1]);
		//		x01 = xpp[i] - step0;			x02 = xpp[i] + step0;
		//		y01 = Interp1(xp,yp,x01,Np);	y02 = Interp1(xp,yp,x02,Np);
		//		mt = 0.001*(y02-y01)/(x02-x01);
		//		T1 = (m1+m2)/(1.0-m1*m2);
		//		T2 = (mt+mt)/(1.0-mt*mt);
		//		AA[i] = T1-T2;

				y = yar[1]+(xpp[i]-xar[1])*(yat[1]-yar[1])/(xat[1]-xar[1]);
				if(y<ypp[i])
					ntr++;
			}
			Error_function(pDoc->m_di,pDoc->m_hi, Np, re, pDoc->LinkHagl_ST, pDoc->LinkRxH,AA,Delta_R1,Grazing1) ;
			double er = +909090.909090;

			for( i=0;i<Np-3;i++)
			{
				if ((AA[i]==0) && (AA[i]!=er))
				{
					x2[kref]=xpp[i];	y2[kref]=ypp[i];

					Delta_R2[kref] = Delta_R1[i];
					Grazing2[kref] = Grazing1[i];

					kref++;
				}
				else if ((AA[i]*AA[i+1]<0) && (AA[i]!=er) && (AA[i+1]!=er))
				{
					x2[kref] = xpp[i]+(xpp[i+1]-xpp[i])*(-AA[i])/(AA[i+1]-AA[i]); 
					y2[kref] = Interp1(xpp,ypp,x2[kref],Np-2);

					Delta_R2[kref] = Interp1(xpp,Delta_R1,x2[kref],Np-2);
					Grazing2[kref] = Interp1(xpp,Grazing1,x2[kref],Np-2);

					kref++;
				}
			}
			if((ntr==0)&&(kref>0))
			{
				Nref=0;
				for (i=0;i<kref;i++)
				{
					nt=0, nr=0;
					for (ii=0;ii<Np-2;ii++)
					{
						if(xpp[ii]<x2[i])
						{
							xpp1 = xpp[ii];		ypp1 = ypp[ii];
							y = y2[i]+(xpp1-x2[i])*(yat[1]-y2[i])/(xat[1]-x2[i]);
							if(y<ypp1)	nt++;
						}
						if(xpp[ii]>x2[i])
						{
							xpp1 = xpp[ii];		ypp1 = ypp[ii];
							y = y2[i]+(xpp1-x2[i])*(yar[1]-y2[i])/(xar[1]-x2[i]);
							if(y<ypp1)	nr++;
						}
					} // end for ii
					if ((nt==0) && (nr==0))
					{
						x2t[Nref] = x2[i];		y2t[Nref] = y2[i];

						Delta_R2t[Nref] = Delta_R2[i];
						Grazing2t[Nref] = Grazing2[i];

						Nref++;
					}
				} // end for i
			} // end if ntr

			m_Nref = Nref;
			m_xref = NULL;		m_yref = NULL;

			m_Delta_R = NULL;		m_Grazing = NULL;

			xrefD[0] = xat[1];	yrefD[0] = yat[1];
			xrefD[2] = xar[1];	yrefD[2] = yar[1];
			if(m_Nref>0)
			{
				m_xref = new double[m_Nref];
				m_yref = new double[m_Nref];

				m_Delta_R = new double[m_Nref];
				m_Grazing = new double[m_Nref];

				for( i=0; i<m_Nref;i++)
				{
					m_xref[i] = x2t[i];		m_yref[i] = y2t[i];
					xrefD[1]  = x2t[i];		yrefD[1]  = y2t[i];
					Plot(pDC,xrefD,yrefD,3,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(128,128,128),PS_SOLID,0) ;

					m_Delta_R[i] = Delta_R2t[i];
					m_Grazing[i] = Grazing2t[i];
				}
			}
			delete [] xpp;	delete [] ypp;	delete [] AA;
			delete [] x2;	delete [] y2;	delete [] x2t;	delete [] y2t;
			delete [] Delta_R1;	delete [] Delta_R2;	delete [] Delta_R2t;
			delete [] Grazing1;	delete [] Grazing2;	delete [] Grazing2t;

/////////////////////////////////////////////////////////
			delete [] xat;	delete [] yat;
			delete [] xar;	delete [] yar;
		}
		else
		{
			Plot(pDC,xpc,ypc,2*Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_SOLID,1,RGB(0,200,0)) ;
			Plot(pDC,xc,yc,Np,  xMIN,xMAX,yMIN,yMAX, m_fontH6,RGB(128,0,0),PS_SOLID,1,RGB(204,204,204)) ;
		}

		Xtick(pDC,xMIN,xMAX) ;
		YtickL(pDC,yMIN,yMAX) ;

		double ytick1 = m_ytickMIN, ytick2 = m_ytickSTEP ,ytick3 = m_ytickMAX;
		double ytick = ytick1;

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

		delete [] phi;
		delete [] xpc;	delete [] ypc;
		delete [] xc;	delete [] yc;
		delete [] xp;	delete [] yp;

		m_Xmin = xMIN;		m_Xmax = xMAX;
		m_Ymin = yMIN;		m_Ymax = yMAX;

		m_stPoint.x = AxesL;
/*
		CPen pen0;
		pen0.CreatePen(PS_DOT ,1,RGB(0,0,255));
		pDC->SelectObject(&pen0);

		pDC->MoveTo(m_stPoint.x,m_AxesT);
		pDC->LineTo(m_stPoint.x,m_AxesH);

		pDC->MoveTo(m_stPoint.x-2,m_AxesT);
		pDC->LineTo(m_stPoint.x-2,m_AxesH);

		pDC->MoveTo(m_stPoint.x+2,m_AxesT);
		pDC->LineTo(m_stPoint.x+2,m_AxesH);
*/
		TxRxObj(pDC);
		if (m_InitForm)
		{
			InitForm(pDoc);
			m_InitForm = false;
		}
	}	
}


void CPro_P530_LinkView::Error_function(double *di,double *hi, long n,double re,double Ht,double Hr,
										double *AA,double *Delta_R, double *Grazing) 
{
	double xD,yD,xE,yE,h1,h2,c,m,b0,d1;
	double d,a,b,pi,xat,yat,xar,yar;

	d=di[n-1]-di[0];
	pi = 4.0*atan(1.0);
	a=re*sin(d/(2.0*re));
	b=-re*cos(d/(2.0*re));

	double *xp;		xp   = new double[n];
	double *yp;		yp   = new double[n];
	double *phi;	phi  = new double[n];

	for (int i=0;i<n;i++)
	{
		phi[i]=(pi/2.0)+(d/(2.0*re))-(di[i]/(re));
		xp[i]=(re+hi[i]/1000.0)*cos(phi[i]);
		yp[i]=(re+hi[i]/1000.0)*sin(phi[i]);
	}
	xat = ((Ht+hi[0])/1000.0+re)*cos(phi[0]);
	yat = ((Ht+hi[0])/1000.0+re)*sin(phi[0]);
	xar = ((Hr+hi[n-1])/1000.0+re)*cos(phi[n-1]);
	yar = ((Hr+hi[n-1])/1000.0+re)*sin(phi[n-1]);

	double * xidif;	xidif = new double[n-1];
	diff(xp,xidif,n);
	double step0 = MinValue(xidif,n-1)/1000.0;
	delete [] xidif;

	double x01,y01,x02,y02,mt;
	double *xpp;	xpp  = new double[n-2];
	double *ypp;	ypp  = new double[n-2];

	for( i=0;i<n-2;i++)
	{
		xpp[i] = xp[i+1];	ypp[i] = yp[i+1];

		x01 = xpp[i] - step0;			x02 = xpp[i] + step0;
		y01 = Interp1(xp,yp,x01,n);		y02 = Interp1(xp,yp,x02,n);
		mt = (y02-y01)/(x02-x01);

		xD = (ypp[i]-xpp[i]*mt)/(-mt+yat/xat);    yD = yat*xD/xat;
		xE = (ypp[i]-xpp[i]*mt)/(-mt+yar/xar);    yE = yar*xE/xar;

		h1 = sqrt(xat*xat+yat*yat)-sqrt(xD*xD+yD*yD);
		h2 = sqrt(xar*xar+yar*yar)-sqrt(xE*xE+yE*yE);

		c=(h1-h2)/(h1+h2);
		m=(d*d)/(4.0*re*(h1+h2));
		b0=2.0*sqrt((m+1.0)/(3.0*m))*cos(pi/3.0+acos(1.5*c*sqrt(3.0*m/pow(m+1.0,3.0) ))/3.0);

		d1=d*(1+b0)/2.0;

		Grazing[i] = (h1+h2)*(1.0-m*(1+b0*b0))/d;			//CCIR Rep. 1008
		Delta_R[i] = 2.0*d1*(d-d1)*Grazing[i]*Grazing[i]/d; //CCIR Rep. 1008
		Grazing[i] = (180.0/pi)*atan(Grazing[i]);

/*
Delta_R[i] =	sqrt(pow( xpp[i]-xat ,2.0) + pow( ypp[i]-yat ,2.0)) + 
				sqrt(pow( xpp[i]-xar ,2.0) + pow( ypp[i]-yar ,2.0)) -
				sqrt(pow(    xar-xat ,2.0) + pow(    yar-yat ,2.0));

double TP2 = (pow( xpp[i]-xat ,2.0) + pow( ypp[i]-yat ,2.0));
double DP2 = (pow( xpp[i]-xD ,2.0) + pow( ypp[i]-yD ,2.0));
Grazing[i] = (180.0/pi)*acos((TP2+DP2-h1*h1)/(2*sqrt(TP2)*sqrt(DP2)));
*/
		if(h1<0 || h2<0)
			AA[i] = +909090.909090;
		else
			AA[i] = d1-di[i+1];
	}
	delete [] xp;
	delete [] yp;
	delete [] xpp;
	delete [] ypp;
	delete [] phi;

}
/*
__declspec(dllimport) void OutageP530V15(double LatM,double LongM,double RainFadeML,double A0dot01L,
								double f_GHz,double LOSDist,double h1,double h2,
								double FlatFadeMarginR, int RADIO1_rain, BOOL flagQ, 
								double *RainAnEx, double *RainWorstMonthEx,
								double *MultipathAnEx, double *MultipathWorstMonthEx);
*/
__declspec(dllimport) void MultiPathOutageP530V15(double FlatFadeMarginR, double p0, double DeltaG, double *py, double *pw);

void CPro_P530_LinkView::InitForm(CPro_P530_LinkDoc* pDoc) 
{
	UpdateData();

	m_Lcr = pDoc->LinkRxInsertionLoss;
	m_Lct = pDoc->LinkTxInsertionLoss;

	m_Hr = pDoc->LinkRxH;
	m_Ht = pDoc->LinkHagl_ST;
	m_Pr.Format("%g",pDoc->LinkPtGt_ST);
	m_Gt = pDoc->m_Gt;
	m_Gr = pDoc->m_Gr;
	m_Pi.Format("%g",atof(m_Pr)/pow(10.0,(m_Gt/10.0)));
	double ap = ((atof(m_VSWR2)-1.0)/(atof(m_VSWR2)+1.0)) * pow(10.0,(-m_Lct/10.0));
	m_Lml.Format("%g",-10.0*log10(1.0 -  pow(( ap * pow(10.0,(m_Lct/10.0)) ),2.0) ));
	m_VSWR1.Format("%g",(1.0+ap)/(1.0-ap));
	m_Po.Format("%g",atof(m_Pi) * pow(10.0,(m_Lct/10.0)) * pow(10.0,(atof(m_Lml)/10.0)));
	m_Pb.Format("%g",atof(m_Po) * pow(((atof(m_VSWR1)-1.0)/(atof(m_VSWR1)+1.0)),2.0));

//	m_timePC = pDoc->Linktime;
	m_Distance.Format("%0.3f",pDoc->m_Distance);
	m_FsLoss.Format("%0.3f",pDoc->m_FsLoss);
	m_Frequency  = pDoc->LinkfMHz_ST;
	m_FrequencyR = pDoc->LinkfMHz_Rx;

	m_kfactor = pDoc->Linkk;

	m_RxName = pDoc->LinkName_Rx;
	m_TxName = pDoc->LinkName_ST;

	m_tit = pDoc->m_tit;

	CStatic* xx1 = (CStatic*)GetDlgItem(IDC_STATIC_loss1);
	xx1->SetWindowText(pDoc->m_Loss1L);
	m_Loss1 = pDoc->m_Loss1;

	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_loss2);
	xx1->SetWindowText(pDoc->m_Loss2L);
	m_Loss2 = pDoc->m_Loss2;

	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_loss3);
	xx1->SetWindowText(pDoc->m_Loss3L);
	m_Loss3 = pDoc->m_Loss3;

	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_loss4);
	xx1->SetWindowText(pDoc->m_Loss4L);
	m_Loss4 = pDoc->m_Loss4;

	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_loss5);
	xx1->SetWindowText(pDoc->m_Loss5L);
	m_Loss5 = pDoc->m_Loss5;

	m_TotalLoss = atof(m_Loss5);

	m_TGL.Format("%0.3f",atof(m_Loss3) + atof(m_Loss2) + atof(m_Loss1));	//dB

	double EIRP  = 10.0*log10(atof(m_Pr)) + 30.0;					//dBm
	m_FRL.Format("%0.3f",EIRP - pDoc->m_FsLoss - atof(m_Loss3) - atof(m_Loss4) + m_Gr - m_Lcr);	//dBm

if(pDoc->LinkRxThreshold>0)
{
	double RxThreshold = -90.0-10.0*log10(m_R)+20.0*log10(pDoc->LinkRxThreshold);
	m_FFM.Format("%0.3f",atof(m_FRL) - RxThreshold);						//dBm

	m_thr2.Format("%0.3f (dBm)",RxThreshold);
}
else
{
	m_FFM  = "----";
	m_thr2 = "----";
}

//	CP530_Functions CP530;
//	CP530.P530Outage(pDoc->LatM,atof(m_Loss3),pDoc->A0dot01L,
//									pDoc->LinkfMHz_ST,pDoc->LOSDist,pDoc->h1,pDoc->h2,
//									atof(m_FFM),pDoc->m_mK,
//									&m_RainAnEx,&m_RainWorstMonthEx,
//									&m_MultipathAnEx,&m_MultipathWorstMonthEx) ;


//	OutageP530V15(pDoc->LatM, pDoc->LongM, atof(m_Loss3), pDoc->A0dot01L,
//								pDoc->LinkfMHz_ST/1000.0, pDoc->m_Distance, pDoc->h1, pDoc->h2,
//								atof(m_FFM), pDoc->m_RADIO1_rain, pDoc->m_CHECK_Q, 
//								&m_RainAnEx,&m_RainWorstMonthEx,
//								&m_MultipathAnEx,&m_MultipathWorstMonthEx) ;

	m_RainAnEx = pDoc->m_rain_py;
	m_RainWorstMonthEx = pDoc->m_rain_pw;
	MultiPathOutageP530V15(atof(m_FFM), pDoc->m_p0, pDoc->m_DeltaG, &m_MultipathAnEx,&m_MultipathWorstMonthEx);

	m_thr.Format("%0.3f (uV)",pDoc->LinkRxThreshold);
//	m_thr2.Format("%0.3f (dBm)",RxThreshold);

	m_Clearance.Format("%0.3f F%0.0f",pDoc->m_Clearance, pDoc->Linkfzn);
	m_NFD.Format("%0.3f",pDoc->m_NFD_Loss);

	UpdateData(false);
}


void CPro_P530_LinkView::TxRxObj(CDC* pDC) 
{
	int x1,y1,x2,y2,len1,a;
//	len1 = m_AxesL/4;
	len1 = m_fontH150;

	x1 = m_AxesL/8;
	y1 = 4.7*m_AxesT;
	x2 = x1+len1;
	y2 = y1+len1;
	a = 2*x1+m_AxesW;

	DrawRoundRect(pDC,x1,y1,x2,y2,RGB(128,128,128));
	TextDraw(pDC,x1+len1/8,y1+0.8*len1,"Tx",RGB(255,255,255),0,m_fontH100,0,FW_BOLD);
	DrawRect(pDC,	x2					,y2-len1/2 ,
					x2+len1/8+len1/32	,y2-len1/2+len1/16,
					RGB(255,255,255));
	DrawRect(pDC,	x2+2*len1/8-len1/16		,y2+6*len1-len1/16 ,
					x2+len1					,y2+6*len1,
					RGB(255,255,255));
	DrawRect(pDC,	x2+len1/8+len1/32		,y2-len1/2,
					x2+2*len1/8-len1/32		,y2+6*len1,
					RGB(255,255,255));
	DrawRect(pDC,	x2+len1/8,y2+len1/4,
					x2+2*len1/8,y2+5*len1,
					RGB(128,128,128));

	DrawRoundRect(pDC,x1+a,y1,x2+a,y2,RGB(128,128,128));
	TextDraw(pDC,a+x1+len1/8,y1+0.8*len1,"Rx",RGB(255,255,255),0,m_fontH100,0,FW_BOLD);
	DrawRect(pDC,	a+x2-3*len1/2+2*len1/8+3*len1/32	,y2-len1/2 ,
					a+x2-3*len1/2+3*len1/8+4*len1/32	,y2-len1/2+len1/16,
					RGB(255,255,255));
	DrawRect(pDC,	a+x2-3*len1/2+5*len1/8-len1			,y2+6*len1-len1/16 ,
					a+x2-3*len1/2+3*len1/8				,y2+6*len1,
					RGB(255,255,255));
	DrawRect(pDC,	a+x2-3*len1/2+2*len1/8+3*len1/32	,y2-len1/2,
					a+x2-3*len1/2+3*len1/8+len1/32		,y2+6*len1,
					RGB(255,255,255));
	DrawRect(pDC,	a+x2-3*len1/2+2*len1/8+len1/16	,y2+len1/4,
					a+x2-3*len1/2+3*len1/8+len1/16	,y2+5*len1,
					RGB(128,128,128));

	CPen pen1(PS_SOLID ,m_fontH12,RGB(0,0,0));
	pDC->SelectObject(&pen1);
	pDC->Arc(	x2+len1		,	y2+6*len1-len1/2,
				x2+2*len1	,	y2+7*len1-len1/2,
				x2+len1		,	y2+7*len1-len1/2,
				x2+len1		,	y2+6*len1-len1/2);
	pDC->Arc(	a+x2-3*len1/2-3*len1/8			,y2+7*len1-len1/2,
				a+x2-3*len1/2-3*len1/8-len1		,y2+6*len1-len1/2,
				a+x2-3*len1/2-3*len1/8			,y2+6*len1-len1/2,
				a+x2-3*len1/2-3*len1/8			,y2+7*len1-len1/2);

}


void CPro_P530_LinkView::DrawRect(CDC* pDC,int x1,int y1,int x2,int y2,COLORREF flColor) 
{
	CBrush brush(flColor);
	CBrush *oldbrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID ,m_fontH2,RGB(0,0,0));
	CPen *oldpen = pDC->SelectObject(&pen);
	pDC->Rectangle(x1,y1,x2,y2);
//	pDC->SelectObject(&oldbrush);
//	pDC->SelectObject(&oldpen);
}

void CPro_P530_LinkView::DrawRoundRect(CDC* pDC,int x1,int y1,int x2,int y2,COLORREF flColor) 
{
	CBrush brush(flColor);
	CBrush *oldbrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID ,m_fontH6,RGB(0,0,0));
	CPen *oldpen = pDC->SelectObject(&pen);
	pDC->RoundRect(x1,y1,x2,y2,(x2-x1)/2,(y2-y1)/2);
//	pDC->SelectObject(&oldbrush);
//	pDC->SelectObject(&oldpen);
}

void CPro_P530_LinkView::OnBUTTONLink() 
{
	UpdateData();
	GetDlgItem(IDC_EDIT_Prd)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_Pid)->ShowWindow(SW_SHOW);

	if (GetCheckedRadioButton(IDC_RADIO_R_L,IDC_RADIO_L_R) == IDC_RADIO_R_L)
	{
		m_Pid.Format("%g",( pow(atof(m_S)*0.000001,2.0)/m_R ) * pow(10.0,(m_Lcr/10.0)));
		m_Prd.Format("%g",atof(m_Pid) * pow(10.0,(-m_Gr/10.0)));
		m_Pr.Format("%g",atof(m_Prd) * pow(10.0,(m_TotalLoss/10.0)));
		m_Pi.Format("%g",atof(m_Pr) * pow(10.0,(-m_Gt/10.0)));
		double ap = ((atof(m_VSWR2)-1.0)/(atof(m_VSWR2)+1.0))* pow(10.0,(-m_Lct/10.0));
		m_Lml.Format("%g",-10.0*log10(1.0-   pow(  ap * pow(10.0,(m_Lct/10.0)) , 2.0)  ));
		m_VSWR1.Format("%g",(1.0+ap)/(1.0-ap));
		m_Po.Format("%g",atof(m_Pi)*  pow(10.0,(m_Lct/10.0)) * pow(10.0,(atof(m_Lml)/10.0)));
		m_Pb.Format("%g",atof(m_Po) * pow(  (atof(m_VSWR1)-1)/(atof(m_VSWR1)+1) ,2.0 ));
		m_Pbw = m_Pb;
		m_Pow = m_Po;
	}

	else
	{
		m_VSWR1.Format("%g",(1.0+sqrt(atof(m_Pb)/atof(m_Po)))/(1.0-sqrt(atof(m_Pb)/atof(m_Po))));
		double av = ( (atof(m_VSWR1)-1.0)/(atof(m_VSWR1)+1.0) ) * pow(10.0,(m_Lct/10.0));
		m_Lml.Format("%g",-10.0*log10(1.0-pow(av,2.0)));
		m_VSWR2.Format("%g",(1.0+av)/(1.0-av));
		m_Pi.Format("%g",atof(m_Po) * pow(10.0,(-m_Lct/10.0)) * pow(10.0,(-atof(m_Lml)/10.0)));
		m_Pr.Format("%g",atof(m_Pi) * pow(10.0,(m_Gt/10.0)));
		m_Prd.Format("%g",atof(m_Pr) * pow(10.0,(-m_TotalLoss/10.0)));
		m_Pid.Format("%g",atof(m_Prd) * pow(10.0,(m_Gr/10.0)));
		m_S.Format("%g",( sqrt(m_R * atof(m_Pid) * pow(10.0,(-m_Lcr/10.0)) ) )*1000000.0);
	}

	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
	double EIRP  = 10.0*log10(atof(m_Pr)) + 30.0;					//dBm
	m_FRL.Format("%0.3f",EIRP - pDoc->m_FsLoss - atof(m_Loss3) - atof(m_Loss4) + m_Gr - m_Lcr);	//dBm
	
if(pDoc->LinkRxThreshold>0)
{	
	double RxThreshold = -90.0-10.0*log10(m_R)+20.0*log10(pDoc->LinkRxThreshold);
	m_FFM.Format("%0.3f",atof(m_FRL) - RxThreshold);						//dBm
}
else
	m_FFM = "----";

//	CP530_Functions CP530;
//	CP530.P530Outage(pDoc->LatM,atof(m_Loss3),pDoc->A0dot01L,
//									pDoc->LinkfMHz_ST,pDoc->LOSDist,pDoc->h1,pDoc->h2,
//									atof(m_FFM),pDoc->m_mK,
//									&m_RainAnEx,&m_RainWorstMonthEx,
//									&m_MultipathAnEx,&m_MultipathWorstMonthEx) ;


//	OutageP530V15(pDoc->LatM, pDoc->LongM, atof(m_Loss3), pDoc->A0dot01L,
//								pDoc->LinkfMHz_ST/1000.0, pDoc->m_Distance, pDoc->h1, pDoc->h2,
//								atof(m_FFM), pDoc->m_RADIO1_rain, pDoc->m_CHECK_Q, 
//								&m_RainAnEx,&m_RainWorstMonthEx,
//								&m_MultipathAnEx,&m_MultipathWorstMonthEx) ;

	m_RainAnEx = pDoc->m_rain_py;
	m_RainWorstMonthEx = pDoc->m_rain_pw;
	MultiPathOutageP530V15(atof(m_FFM), pDoc->m_p0, pDoc->m_DeltaG, &m_MultipathAnEx,&m_MultipathWorstMonthEx);

//	m_thr.Format("%0.3f (uV)",pDoc->LinkRxThreshold);
//	m_thr2.Format("%0.3f (dBm)",RxThreshold);

	UpdateData(false);	
}

void CPro_P530_LinkView::OnRadioLR() 
{
	UpdateData();

	CButton* BUTTON_Link=(CButton*)GetDlgItem(IDC_BUTTON_Link);

	if (GetCheckedRadioButton(IDC_RADIO_R_L,IDC_RADIO_L_R) == IDC_RADIO_L_R)
	{
		BUTTON_Link->SetWindowText(_Z(">>Link>>"));

		GetDlgItem(IDC_EDIT_S)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Sw)->ShowWindow(SW_HIDE);
		m_S = m_Sw;
		GetDlgItem(IDC_EDIT_VSWR2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_VSWR2w)->ShowWindow(SW_HIDE);
		m_VSWR2 = m_VSWR2w;

		GetDlgItem(IDC_EDIT_Pb)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Pbw)->ShowWindow(SW_HIDE);
		m_Pb = m_Pbw;
		GetDlgItem(IDC_EDIT_Po)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Pow)->ShowWindow(SW_HIDE);
		m_Po = m_Pow;
	}
	else
	{
		BUTTON_Link->SetWindowText(_Z("<<Link<<"));

		GetDlgItem(IDC_EDIT_S)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Sw)->ShowWindow(SW_SHOW);
		m_Sw = m_S;
		GetDlgItem(IDC_EDIT_VSWR2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VSWR2w)->ShowWindow(SW_SHOW);
		m_VSWR2w = m_VSWR2;

		GetDlgItem(IDC_EDIT_Pb)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Pbw)->ShowWindow(SW_SHOW);
		m_Pbw = m_Pb;
		GetDlgItem(IDC_EDIT_Po)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Pow)->ShowWindow(SW_SHOW);
		m_Pow = m_Po;
	}	
	UpdateData(false);	
}

void CPro_P530_LinkView::OnRadioRL() 
{
	OnRadioLR();
}

void CPro_P530_LinkView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

//	initDP_LP();

	CString Title_En  = "Link Calculation (P530)";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	UpdateData();
	CheckRadioButton(IDC_RADIO_R_L,IDC_RADIO_L_R, IDC_RADIO_L_R);
	GetDlgItem(IDC_EDIT_Prd)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_Pid)->ShowWindow(SW_HIDE);

	CFont font;
	VERIFY(font.CreateFont(
	   18,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_BOLD,					  // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   "Arial"));                 // lpszFacename
	CWnd* xx;
	xx = GetDlgItem(IDC_EDIT_TxName);	xx->SetFont(&font);
	xx = GetDlgItem(IDC_EDIT_RxName);	xx->SetFont(&font);
	xx = GetDlgItem(IDC_EDIT_S);		xx->SetFont(&font);
	xx = GetDlgItem(IDC_EDIT_VSWR2);	xx->SetFont(&font);
	xx = GetDlgItem(IDC_EDIT_Pbw);		xx->SetFont(&font);
	xx = GetDlgItem(IDC_EDIT_Pow);		xx->SetFont(&font);
	xx = GetDlgItem(IDC_BUTTON_Link);	xx->SetFont(&font);
	font.DeleteObject();

	UpdateData(false);	
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE41);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog((CDialog *)this);
}

void CPro_P530_LinkView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
		m_rcPrintRect=pInfo->m_rectDraw;

/////////////////////////////////////////////////
	pDC->Rectangle(m_rcPrintRect);

	int x = m_rcPrintRect.left, y = m_rcPrintRect.top, 
		w = 14*m_rcPrintRect.Width()/100, h = m_rcPrintRect.Height()/40;

	CString str;
//	int nHeight = 95;
	int nHeight = DP_LP(pDC, 38);	//95

	str.Format(_Z("k_factor : ")+"%0.4f",m_kfactor);
	TextDraw(pDC,x+2*w,y+h/2,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Clearance : ")+"%s",m_Clearance);
	TextDraw(pDC,x+2*w,y+h/2+1*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Flat Receive Level (dBm) : ")+"%s",m_FRL);
	TextDraw(pDC,x+2*w,y+h/2+2*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Flat Fade Margin (dB) : ")+"%s",m_FFM);
	TextDraw(pDC,x+2*w,y+h/2+3*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Total Geo-climatic Loss (dB) : ")+"%s",m_TGL);
	TextDraw(pDC,x+2*w,y+h/2+4*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
//	str.Format(_Z("Net Filter Discrimination (dB) : ")+"%s",m_NFD);
//	TextDraw(pDC,x+2*w,y+h/2+5*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Tx Frequency(MHz) : ")+"%g",m_Frequency);
	TextDraw(pDC,x+2*w,y+h/2+6*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	str.Format(_Z("Free Space Loss(dB) : ")+"%s",m_FsLoss);
	TextDraw(pDC,x+4*w,y+h/2,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Clear Air Fading (dB) : ")+"%s",m_Loss1);
	TextDraw(pDC,x+4*w,y+h/2+h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Rain Attenuation (dB) : ")+"%s",m_Loss2);
	TextDraw(pDC,x+4*w,y+h/2+2*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Atmospheric Absorption (dB) : ")+"%s",m_Loss3);
	TextDraw(pDC,x+4*w,y+h/2+3*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Diffraction Fading (dB) : ")+"%s",m_Loss4);
	TextDraw(pDC,x+4*w,y+h/2+4*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Path Loss(dB) : ")+"%s",m_Loss5);
	TextDraw(pDC,x+4*w,y+h/2+5*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Rx Frequency(MHz) : ")+"%g",m_FrequencyR);
	TextDraw(pDC,x+4*w,y+h/2+6*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	str.Format(_Z("Name :")+" %s",m_TxName);
	TextDraw(pDC,x+w/4,y+h,str,RGB(200,0,0),0,nHeight+10,0,FW_BOLD);
	str.Format(_Z("Total Distance(km) : ")+"%s",m_Distance);
	TextDraw(pDC,x+w/4,y+2*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("EIRP(w) :")+" %s",m_Pr);
	TextDraw(pDC,x+w/4,y+3*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	str.Format(_Z("Name :")+" %s",m_RxName);
	TextDraw(pDC,x+6*w,y+h,str,RGB(200,0,0),0,nHeight+10,0,FW_BOLD);
	str.Format(_Z("Threshold :"));
	TextDraw(pDC,x+6*w,y+2*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("           %s",m_thr);
	TextDraw(pDC,x+6*w,y+3*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("           %s",m_thr2);
	TextDraw(pDC,x+6*w,y+4*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	str.Format(_Z("Received Level :"));			TextDraw(pDC,x+6*w,y+5*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("           %s (uV)",m_S);		TextDraw(pDC,x+6*w,y+6*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	
	if(atof(m_S)>0)
	{
		double PdBm = 10.0*log10(1000.0*pow(atof(m_S)*0.000001,2.0 )/m_R);
		str.Format("           %0.3f (dBm)",PdBm);
	}
	else
		str.Format("           ---- (dBm)");	
	TextDraw(pDC,x+6*w,y+7*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

/*
	m_Gr = 0.0;	m_Gt = 0.0;	m_Hr = 0.0;	m_Ht = 0.0;
	m_Lcr = 3.0;	m_Lct = 3.0;	m_Lml = _T("");
	m_Pb = _T("");	m_Pbw = _T("");
	m_Pi = _T("");	m_Pid = _T("");
	m_Po = _T("");	m_Pow = _T("");
	m_Prd = _T("");	m_R = 50.0;
	m_VSWR1 = _T("");	m_VSWR2 = _T("1.5");	m_VSWR2w = _T("");
*/
////////////////////////////////////////////////
	CView::OnPrint(pDC, pInfo);
}
void CPro_P530_LinkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CPro_P530_LinkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
BOOL CPro_P530_LinkView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	((CSMS4DCApp*)AfxGetApp())->SetLandscape();

	return DoPreparePrinting(pInfo);
}


void CPro_P530_LinkView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CFormView::OnFilePrintPreview();
}
void CPro_P530_LinkView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CFormView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

HBRUSH CPro_P530_LinkView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if ( pWnd->GetDlgCtrlID() == IDC_EDIT_VSWR2 ||
		 pWnd->GetDlgCtrlID() == IDC_EDIT_S     ||
		 pWnd->GetDlgCtrlID() == IDC_EDIT_Pbw   ||		 
		 pWnd->GetDlgCtrlID() == IDC_EDIT_Pow     )
			pDC->SetBkColor(RGB( 253, 177, 13 ));

	if (  pWnd->GetDlgCtrlID() == IDC_EDIT_Distance		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Loss1		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Loss2		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Loss3		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Loss4		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Loss5		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_FsLoss		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_FRL			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_FFM			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_TGL			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Frequncy		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_FrequncyR	||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_clearance	||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_NFD			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_k			)
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
		pDC->SetTextColor(RGB( 0, 0, 127 ));
		font.DeleteObject();
	}

	if (  pWnd->GetDlgCtrlID() == IDC_EDIT_TxName		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_RxName)
	{
		CFont font ;
        if (!(HFONT)font)
		{
            LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfHeight = 18;
			lf.lfWeight = FW_BOLD;
			strcpy(lf.lfFaceName , "Arial");
            font.CreateFontIndirect(&lf);
        }
        pDC->SelectObject(&font);
		pDC->SetBkColor(RGB(255,255,0));
		font.DeleteObject();
	}
	return hbr;
}

void CPro_P530_LinkView::OnChangeEDITVSWR2w() 
{
	UpdateData();
	m_VSWR2 = m_VSWR2w;
	UpdateData(false);	
}

void CPro_P530_LinkView::OnChangeEDITSw() 
{
	UpdateData();
	m_S = m_Sw;
	UpdateData(false);
}

void CPro_P530_LinkView::OnBUTTONSaveProfile() 
{
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();

	CString str;	str.Format("%s_%s",pDoc->LinkName_ST,pDoc->LinkName_Rx);
//	char strFilter[] = { "text Files (*.txt)|*.txt|prf Files (*.prf)|*.prf|All Files (*.*)|*.*||"};
	CString strFilter = _Z("text Files")+" (*.txt)|*.txt|"+_Z("All Files")+" (*.*)|*.*||";
	CFileDialog FileDLG(FALSE, ".txt", str, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);

	if (FileDLG.DoModal() == IDOK)
	{
		FILE *fp=fopen(FileDLG.GetPathName(),"wt");
		if(fp)
		{
			for(int i=0;i<Np;i++)
				fprintf(fp,"%0.14f %f %d\n",pDoc->m_di[i],(pDoc->m_hi[i]),pDoc->m_zi[i]);
			//	fprintf(fp,"%lf %d %d\n",pDoc->m_di[i],(int)(pDoc->m_hi[i]),pDoc->m_zi[i]);
			//	fprintf(fp,"%.3f %0.3f %d\n",pDoc->m_di[i],pDoc->m_hi[i],pDoc->m_zi[i]);
			fclose(fp);
		}
		ShellExecute(m_hWnd, "open", FileDLG.GetPathName(), NULL, NULL, SW_SHOWNORMAL);
	}
}

void CPro_P530_LinkView::OnBUTTONAvailability() 
{
	UpdateData();

	CP530availabilityDLG dlg;
	dlg.m_RainWMav.Format("%f",100.0-m_RainWorstMonthEx);
	dlg.m_RainWMoutS.Format("%f",m_RainWorstMonthEx*30.0*24.0*60.0*60.0/100.0);
	dlg.m_RainWMoutM.Format("%f",m_RainWorstMonthEx*30.0*24.0*60.0/100.0);

	dlg.m_RainANav.Format("%f",100.0-m_RainAnEx);
	dlg.m_RainANoutS.Format("%f",m_RainAnEx*365.5*24.0*60.0*60.0/100.0);
	dlg.m_RainANoutM.Format("%f",m_RainAnEx*365.5*24.0*60.0/100.0);

	dlg.m_MultiWMav.Format("%f",100.0-m_MultipathWorstMonthEx);
	dlg.m_MultiWMoutS.Format("%f",m_MultipathWorstMonthEx*30.0*24.0*60.0*60.0/100.0);
	dlg.m_MultiWMoutM.Format("%f",m_MultipathWorstMonthEx*30.0*24.0*60.0/100.0);

	dlg.m_MultiANav.Format("%f",100.0-m_MultipathAnEx);
	dlg.m_MultiANoutS.Format("%f",m_MultipathAnEx*365.5*24.0*60.0*60.0/100.0);
	dlg.m_MultiANoutM.Format("%f",m_MultipathAnEx*365.5*24.0*60.0/100.0);

	dlg.DoModal();
		
	UpdateData(false);
}

void CPro_P530_LinkView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLPressed = true;
	CFormView::OnLButtonDown(nFlags, point);
}

void CPro_P530_LinkView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed = false;
	CFormView::OnLButtonUp(nFlags, point);
}

void CPro_P530_LinkView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
	double xi0 = m_Xmin+(point.x -  m_AxesL1)*(m_Xmax-m_Xmin)/(m_AxesW1 - m_AxesL1) ;
	double yi0 = m_Ymin+(point.y -  m_AxesH1)*(m_Ymax-m_Ymin)/(m_AxesT1 - m_AxesH1) ;

m_d0 = (pDoc->Dmax - pDoc->Dmin)/100.0;

//	if((xi0>=pDoc->Dmin-m_d0 && xi0<=pDoc->Dmin+m_d0 && yi0>=(pDoc->m_hi[0]+m_Ht-10)          && yi0<=(pDoc->m_hi[0]+m_Ht+10)         )||
//	   (xi0>=pDoc->Dmax-m_d0 && xi0<=pDoc->Dmax+m_d0 && yi0>=(pDoc->m_hi[pDoc->Np-1]+m_Hr-10) && yi0<=(pDoc->m_hi[pDoc->Np-1]+m_Hr+10)))
//		SetCursor(AfxGetApp()->LoadCursor(IDC_harrow));

if(  ((fabs(xi0 - pDoc->Dmin) <= m_d0) && (fabs(yi0 - (pDoc->m_hi[0]+m_Ht))          <= 10.0))  ||
     ((fabs(xi0 - pDoc->Dmax) <= m_d0) && (fabs(yi0 - (pDoc->m_hi[pDoc->Np-1]+m_Hr)) <= 10.0))     )
		SetCursor(AfxGetApp()->LoadCursor(IDC_harrow));

	if(m_bRPressed)
	{
//		if(xi0>=pDoc->Dmin-m_d0 && xi0<=pDoc->Dmin+m_d0 && yi0>=pDoc->m_hi[0])
		if( (fabs(xi0 - pDoc->Dmin) <= m_d0) && (yi0 >= pDoc->m_hi[0]) )
		{
			SetCursor(AfxGetApp()->LoadCursor(IDC_harrow));
			UpdateData();
			m_Ht = yi0 - pDoc->m_hi[0];
			m_Ht = max(m_Ht,0.0);
			CString str1;	str1.Format("%0.3f",m_Ht);	m_Ht = atof(str1);
			pDoc->LinkHagl_ST = m_Ht;
			UpdateData(false);

			CRect rect;
			rect.left=m_AxesL1-50;
			rect.top= int(0.89*m_AxesT1);
			rect.right=int(1.01*m_AxesW1);
			rect.bottom=m_AxesT1+m_AxesH1;

			InvalidateRect(rect,true);
		}
//		if(xi0>=pDoc->Dmax-m_d0 && xi0<=pDoc->Dmax+m_d0 && yi0>=pDoc->m_hi[pDoc->Np-1])
		if( (fabs(xi0 - pDoc->Dmax) <= m_d0) && (yi0 >= pDoc->m_hi[pDoc->Np-1]) )
		{
			SetCursor(AfxGetApp()->LoadCursor(IDC_harrow));
			UpdateData();
			m_Hr = yi0 - pDoc->m_hi[pDoc->Np-1];
			m_Hr = max(m_Hr,0.0);
			CString str1;	str1.Format("%0.3f",m_Hr);	m_Hr = atof(str1);
			pDoc->LinkRxH = m_Hr;
			UpdateData(false);

			CRect rect;
			rect.left=m_AxesL1-50;
			rect.top=int(0.89*m_AxesT1);
			rect.right=int(1.01*m_AxesW1);
			rect.bottom=m_AxesT1+m_AxesH1;

			InvalidateRect(rect,true);
		}
	}
	if(m_bLPressed)
	{
		CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
		double xi0 = m_Xmin+(point.x -  m_AxesL1)*(m_Xmax-m_Xmin)/(m_AxesW1 - m_AxesL1) ;
		double yi0 = m_Ymin+(point.y -  m_AxesH1)*(m_Ymax-m_Ymin)/(m_AxesT1 - m_AxesH1) ;
		if(xi0>=pDoc->Dmin && xi0<=pDoc->Dmax)
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
		}
	}
	CFormView::OnMouseMove(nFlags, point);
}

void CPro_P530_LinkView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_bRPressed = true;
	CFormView::OnRButtonDown(nFlags, point);
}
void CPro_P530_LinkView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_bRPressed = false;
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
	double xi0 = m_Xmin+(point.x -  m_AxesL1)*(m_Xmax-m_Xmin)/(m_AxesW1 - m_AxesL1) ;
	double yi0 = m_Ymin+(point.y -  m_AxesH1)*(m_Ymax-m_Ymin)/(m_AxesT1 - m_AxesH1) ;

//	if((xi0>=pDoc->Dmin-m_d0 && xi0<=pDoc->Dmin+m_d0 && yi0>=pDoc->m_hi[0])       ||
//	   (xi0>=pDoc->Dmax-m_d0 && xi0<=pDoc->Dmax+m_d0 && yi0>=pDoc->m_hi[pDoc->Np-1]))

	if( (fabs(xi0 - pDoc->Dmin) <= m_d0) && (yi0 >= pDoc->m_hi[0])         ||
		(fabs(xi0 - pDoc->Dmax) <= m_d0) && (yi0 >= pDoc->m_hi[pDoc->Np-1])   )
	{
		UpdateData();
		pDoc->GetData();
		InitForm(pDoc);
		OnBUTTONLink();
		UpdateData(false);
	}
	CFormView::OnRButtonUp(nFlags, point);
}

void CPro_P530_LinkView::OnKillfocusEDITLcr() 
{
	UpdateData();
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
	pDoc->LinkRxInsertionLoss = m_Lcr;
	pDoc->GetData();
	InitForm(pDoc);
	UpdateData(false);
}

void CPro_P530_LinkView::OnKillfocusEDITLct() 
{
	UpdateData();
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
	pDoc->LinkTxInsertionLoss = m_Lct;
	pDoc->GetData();
	InitForm(pDoc);
	UpdateData(false);
}

void CPro_P530_LinkView::OnKillfocusEDITGr() 
{
	UpdateData();
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
	pDoc->m_Gr = m_Gr;
	pDoc->GetData();
	InitForm(pDoc);
	UpdateData(false);
}

void CPro_P530_LinkView::OnKillfocusEDITGt() 
{
	UpdateData();
	CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();
	pDoc->m_Gt = m_Gt;
	pDoc->GetData();
	InitForm(pDoc);
	UpdateData(false);
}

void CPro_P530_LinkView::diff(double *xi,double *yi,int num) 
{
	for(int i=0;i<num-1;i++)
		yi[i] = xi[i+1]-xi[i];
}

double CPro_P530_LinkView::Interp1(double *D0,double *E0,double d,int num) 
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


void CPro_P530_LinkView::OnBUTTONRefpoints() 
{
//	if(m_Nref>0)
	{
		CPro_P530_LinkDoc* pDoc = (CPro_P530_LinkDoc *)GetDocument();

		CP530RefPointsDLG dlgList;
		dlgList.m_nROWS = m_Nref;
		CString str1,str="", RLONbs,RLATbs;

		double Hmin = pDoc->Hmin;
		double d = pDoc->Dmax-pDoc->Dmin;
		double re = 6371.0*pDoc->Linkk;
		double a = re*sin(d/(2.0*re));
		double b = -re*cos(d/(2.0*re));
		double pi = 4.0*atan(1.0);

		double x,y,hi,di,lati,loni;
		for(int i=0; i<m_Nref;i++)
		{
			x = m_xref[i]-a;
			y = (m_yref[i]-Hmin)/1000.0-b;

			hi = 1000.0*sqrt(x*x+y*y) - 1000.0*re + Hmin;
			di = re*(pi/2+d/(2*re)-atan2(y,x));
			lati = Interp1(pDoc->m_di,pDoc->m_lati,di,Np);
			loni = Interp1(pDoc->m_di,pDoc->m_loni,di,Np);

loni = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(loni);

			Rad2Str(loni*pi/180.0,lati*pi/180.0, &RLONbs,&RLATbs);

			str1.Format("%s  %s,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f",   RLONbs,RLATbs , di , d-di , hi,m_Delta_R[i],m_Grazing[i]);
			str = str+","+str1;
		}
		str.Delete(0);
		str=str+",";
		dlgList.m_data = str;
		dlgList.DoModal();
	}
}

void CPro_P530_LinkView::Rad2Str(float lonRAD,float latRAD,CString *lonSTR,CString *latSTR) 
{
	unsigned char COORD[15];
	CRADDG4( &lonRAD, &latRAD, COORD );
	CString COORD1 = COORD;
	COORD1 = COORD1.Left(15);
	*lonSTR = COORD1.Left(8);
	*latSTR = COORD1.Right(7);
}



int CPro_P530_LinkView::DP_LP(CDC* pDC,int nH_DP) //97/10/12
{
	if (pDC->IsPrinting())		return (int)(nH_DP*30.0/12.0);

	CSize z1(0, nH_DP);
	pDC->DPtoLP(&z1);
	return z1.cy;
}

void CPro_P530_LinkView::initDP_LP(CDC * pDC) //97/10/12
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
	m_fontH100 = DP_LP(pDC, 40); //100
	m_fontH150 = DP_LP(pDC, 60); //150

}
