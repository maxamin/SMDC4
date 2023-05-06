// Pro_P526V14_LinkView.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Pro_P526V14_LinkView.h"
#include <math.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P526V14_LinkView

IMPLEMENT_DYNCREATE(CPro_P526V14_LinkView, CFormView)

CPro_P526V14_LinkView::CPro_P526V14_LinkView()
	: CFormView(CPro_P526V14_LinkView::IDD)
{
	//{{AFX_DATA_INIT(CPro_P526V14_LinkView)
	m_Frequency = 0.0;
	m_Distance = _T("");
	m_FsLoss = _T("");
	m_Gr = 0.0;
	m_Gt = 0.0;
	m_Hr = 0.0;
	m_Ht = 0.0;
	m_Lcr = 3.0;
	m_Lct = 3.0;
	m_Lml = _T("");
	m_Loss1 = _T("");
	m_Loss2 = _T("");
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
	m_S = _T("");
	m_Sw = _T("");
	m_tit = _T("");
	m_TxName = _T("");
	m_VSWR1 = _T("");
	m_VSWR2 = _T("1.5");
	m_VSWR2w = _T("");
	m_kfactor = _T("");
	m_EDIT_Lba = _T("");
	m_EDIT_Lbs = _T("");
	m_EDIT_Lsph = _T("");
	m_thr = _T("");
	m_thr2 = _T("");
	//}}AFX_DATA_INIT

	m_bLPressed=false;
	m_bRPressed=false;

	m_AxesT=0;
	m_AxesH=0;
	m_AxesL=0;
	m_AxesW=0;
	m_stPoint.x=0;
	m_stPoint.y=0;

	m_Fresnel = 1;
	m_InitForm = true;

	VERIFY(m_font.CreateFont(
		   15,                        // nHeight
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
	
	m_d0 = 0.5;
}

CPro_P526V14_LinkView::~CPro_P526V14_LinkView()
{
	m_font.DeleteObject();
}

void CPro_P526V14_LinkView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPro_P526V14_LinkView)
	DDX_Text(pDX, IDC_EDIT_Frequncy, m_Frequency);
	DDX_Text(pDX, IDC_EDIT_Distance, m_Distance);
	DDX_Text(pDX, IDC_EDIT_FsLoss, m_FsLoss);
	DDX_Text(pDX, IDC_EDIT_Gr, m_Gr);
	DDX_Text(pDX, IDC_EDIT_Gt, m_Gt);
	DDX_Text(pDX, IDC_EDIT_Hr, m_Hr);
	DDX_Text(pDX, IDC_EDIT_Ht, m_Ht);
	DDX_Text(pDX, IDC_EDIT_Lcr, m_Lcr);
	DDX_Text(pDX, IDC_EDIT_Lct, m_Lct);
	DDX_Text(pDX, IDC_EDIT_Lml, m_Lml);
	DDX_Text(pDX, IDC_EDIT_Loss1, m_Loss1);
	DDX_Text(pDX, IDC_EDIT_Loss2, m_Loss2);
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
	DDX_Text(pDX, IDC_EDIT_tit, m_tit);
	DDX_Text(pDX, IDC_EDIT_TxName, m_TxName);
	DDX_Text(pDX, IDC_EDIT_VSWR1, m_VSWR1);
	DDX_Text(pDX, IDC_EDIT_VSWR2, m_VSWR2);
	DDX_Text(pDX, IDC_EDIT_VSWR2w, m_VSWR2w);
	DDX_Text(pDX, IDC_EDIT_k, m_kfactor);
	DDX_Text(pDX, IDC_EDIT_Lba, m_EDIT_Lba);
	DDX_Text(pDX, IDC_EDIT_Lbs, m_EDIT_Lbs);
	DDX_Text(pDX, IDC_EDIT_Lsph, m_EDIT_Lsph);
	DDX_Text(pDX, IDC_EDIT_thr, m_thr);
	DDX_Text(pDX, IDC_EDIT_thr2, m_thr2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPro_P526V14_LinkView, CFormView)
	//{{AFX_MSG_MAP(CPro_P526V14_LinkView)
	ON_BN_CLICKED(IDC_BUTTON_Link, OnBUTTONLink)
	ON_BN_CLICKED(IDC_RADIO_R_L, OnRadioRL)
	ON_BN_CLICKED(IDC_RADIO_L_R, OnRadioLR)
	ON_BN_CLICKED(IDC_BUTTON_SaveProfile, OnBUTTONSaveProfile)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_Sw, OnChangeEDITSw)
	ON_EN_CHANGE(IDC_EDIT_VSWR2w, OnChangeEDITVSWR2w)
	ON_BN_CLICKED(IDC_BUTTON_SaveImage, OnBUTTONSaveImage)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPro_P526V14_LinkView diagnostics

#ifdef _DEBUG
void CPro_P526V14_LinkView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPro_P526V14_LinkView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P526V14_LinkView message handlers


void CPro_P526V14_LinkView::Plot(CDC* pDC,double *xi, double *yi,int N,
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
void CPro_P526V14_LinkView::DrawAntSymbol(CDC* pDC,double xi, double yi,
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



void CPro_P526V14_LinkView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
							int Escapement,
							int nHeight,int nWidth,int FontWeight,CString FontName) 
{
	pDC->SetBkMode(TRANSPARENT);
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = nHeight;                // request a 12-pixel-height font
	lf.lfWidth  = nWidth;

//	lf.lfHeight = -MulDiv( nHeight, 72, pDC->GetDeviceCaps(LOGPIXELSY));
//	lf.lfHeight = -MulDiv( nHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72);
//	lf.lfWidth  = -MulDiv( nWidth , (pDC->GetDeviceCaps(LOGPIXELSX))*(str.GetLength()), 72);
	
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


void CPro_P526V14_LinkView::LineDraw(CDC* pDC,int x1, int y1,int x2, int y2,
							int nWidth, COLORREF crColor, int nStyle) 
{
	CPen pen;
	pen.CreatePen(nStyle,nWidth,crColor);
	pDC->SelectObject(&pen);

	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

void CPro_P526V14_LinkView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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

void CPro_P526V14_LinkView::YtickL(CDC* pDC,double yiMIN,double yiMAX) 
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
		//		TextDraw(pDC,13*m_AxesL/16,y+20,label,RGB(0,0,0),0,30) ;
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
//		TextDraw(pDC,13*m_AxesL/16,y+20,label,RGB(0,0,255),0,30) ;
		TextDraw(pDC,13*m_AxesL/16,y+m_fontH20,label,RGB(0,0,255),0, m_fontH30) ;
	}
	m_ytickMIN=ytickMIN;     m_ytickSTEP=ytickSTEP;  m_ytickMAX=ytickMAX;
//	TextDraw(pDC,12*m_AxesL/16,(2*m_AxesT+m_AxesH)/2,_Z("Altitude (m)"),RGB(0,0,255),2700,40,0,FW_BOLD) ;
	TextDraw(pDC,12*m_AxesL/16,(2*m_AxesT+m_AxesH)/2,_Z("Altitude (m)"),RGB(0,0,255),2700,m_fontH40,0,FW_BOLD) ;
}


void CPro_P526V14_LinkView::Xtick(CDC* pDC,double xiMIN,double xiMAX) 
{
	CPro_P526V14_LinkDoc* pDoc = (CPro_P526V14_LinkDoc *)GetDocument();
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
				LineDraw(pDC,x,m_AxesH,x,m_AxesH-m_fontH20, m_fontH6) ;//20,6
				LineDraw(pDC,x,m_AxesT,x,m_AxesH,1,RGB(0,255,0),PS_DOT) ;
				label.Format("%.1f",xround);
//				TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,34);
//				TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,30);

				TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,0,0),900, m_fontH30);
			}
			i++;
		}
	}
	else
	{
		x=m_AxesW/2;
		LineDraw(pDC,x,m_AxesH,x,m_AxesH-m_fontH20,m_fontH6) ;
		label.Format("%.1f",xiMIN);
//		TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,34);
//		TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,30);
		TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,0,0),900, m_fontH30);
	}
//	TextDraw(pDC,m_AxesL+m_AxesW/3,m_AxesH+3*m_AxesT/10,_Z("Distance (km)"),RGB(0,0,255),0,44,0,FW_BOLD) ;
	TextDraw(pDC,m_AxesL+m_AxesW/3,m_AxesH+3*m_AxesT/10,_Z("Distance (km)"),RGB(0,0,255),0,m_fontH44,0,FW_BOLD) ;
}

double CPro_P526V14_LinkView::MinValue(double *xi,int N) 
{
	double  xiMIN=100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMIN=min(xiMIN,xi[i]);	
	}
	return xiMIN;
}

double CPro_P526V14_LinkView::MaxValue(double *xi,int N) 
{
	double  xiMAX=-100000000.0;
	for (int i=0;i<N;i++)
	{
		xiMAX=max(xiMAX,xi[i]);	
	}
	return xiMAX;
}

double CPro_P526V14_LinkView::InterpXY(double *D0,double *E0,double d,int num)
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


void CPro_P526V14_LinkView::OnDraw(CDC* pDC) 
{
	CPro_P526V14_LinkDoc* pDoc = (CPro_P526V14_LinkDoc *)GetDocument();

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
		pen.CreatePen(PS_SOLID, m_fontH6 ,RGB(0,0,0));	//5
		pDC->SelectObject(&pen);
		pDC->Rectangle(AxesL-2,AxesT,AxesW+6,AxesH);

		Hmin=pDoc->Hmin;
		Np=pDoc->Np;
		double d=pDoc->Dmax-pDoc->Dmin;

		double pi=4.0*atan(1.0);
//		double re=6371.0*atof_kfactor(m_kfactor);
		double re=6371.0*pDoc->Linkk;

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
			//	rfi[i] = m_Fresnel*sqrt(0.3*pDoc->m_di[i]*(d-pDoc->m_di[i])/(m_FrqMHz*d));
				
		//		rfi[i] = sqrt(m_Fresnel*0.3*pDoc->m_di[i]*    (d-pDoc->m_di[i])/(pDoc->LinkfMHz_ST*d));
				rfi[i] = sqrt(m_Fresnel*0.3*pDoc->m_di[i]*fabs(d-pDoc->m_di[i])/(pDoc->LinkfMHz_ST*d));  //930814
				
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
			
			double yf1MIN=MinValue(yf1,Np);
			double yf1MAX=MaxValue(yf1,Np);
			double yf2MIN=MinValue(yf2,Np);
			double yf2MAX=MaxValue(yf2,Np);
			double yfMIN=min(yf1MIN,yf2MIN);
			double yfMAX=max(yf1MAX,yf2MAX);
			yMIN=min(yMIN,yfMIN);
			yMAX=max(yMAX,yfMAX);

			Plot(pDC,xpc,ypc,2*Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_SOLID,1,RGB(0,200,0)) ;//4
			Plot(pDC,xc,  yc,  Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6  ,RGB(128,0,0),PS_SOLID,1,RGB(212,208,200)) ;//5

			Plot(pDC,xl,yl,  Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(255,0,0),PS_SOLID,0) ;
			Plot(pDC,xf1,yf1,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_DASH,0) ;
			Plot(pDC,xf2,yf2,Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_DASH,0) ;
			Plot(pDC,xat,yat,2,   xMIN,xMAX,yMIN,yMAX,  m_fontH14,RGB(0,0,255),PS_SOLID,0) ;
			Plot(pDC,xar,yar,2,   xMIN,xMAX,yMIN,yMAX,  m_fontH14,RGB(0,0,255),PS_SOLID,0) ;
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
			Plot(pDC,xpc,ypc,2*Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6-1,RGB(0,0,255),PS_SOLID,1,RGB(0,200,0)) ;//4
			Plot(pDC,xc,yc,    Np,  xMIN,xMAX,yMIN,yMAX,  m_fontH6,  RGB(128,0,0),PS_SOLID,1,RGB(204,204,204)) ;//5
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

		m_Xmin = xMIN;		m_Xmax = xMAX;
		m_Ymin = yMIN;		m_Ymax = yMAX;

		TxRxObj(pDC);
		if (m_InitForm)
		{
			InitForm(pDoc);
			m_InitForm = false;
		}
	}	
}

void CPro_P526V14_LinkView::InitForm(CPro_P526V14_LinkDoc* pDoc) 
{
	UpdateData();
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

	m_EDIT_Lba.Format("%0.3f",pDoc->m_Lba);
	((CStatic*)GetDlgItem(IDC_STATIC_Lba))->SetWindowText(_Z("§ 4.5.1 Bullington model for the actual terrain profile and antenna heights."));

	m_EDIT_Lbs.Format("%0.3f",pDoc->m_Lbs);
	((CStatic*)GetDlgItem(IDC_STATIC_Lbs))->SetWindowText(_Z("§ 4.5.1 Bullington model for a smooth profile by setting all profile heights to zero."));

	m_EDIT_Lsph.Format("%0.3f",pDoc->m_Lsph);
	((CStatic*)GetDlgItem(IDC_STATIC_Lsph))->SetWindowText(_Z("§ 3.2 Diffraction over spherical earth path."));

//	((CStatic*)GetDlgItem(IDC_STATIC_L526))->SetWindowText(_Z("§ 4.5.2 The diffraction loss for the general path.   L526 = Lba + max (Lsph - Lbs, 0) (66)"));
	((CStatic*)GetDlgItem(IDC_STATIC_L526))->SetWindowText(_Z("§ 4.5.2 The diffraction loss for the general path.")+("   L526 = Lba + max (Lsph - Lbs, 0) (66)"));


	m_Distance.Format("%0.3f",pDoc->m_Distance);
	m_FsLoss.Format("%0.3f",pDoc->m_FsLoss);
	m_Frequency = pDoc->LinkfMHz_ST;

	m_kfactor = pDoc->m_kfactor;

	m_RxName = pDoc->LinkName_Rx;
	m_TxName = pDoc->LinkName_ST;

	m_tit = pDoc->m_tit;

//	CStatic* xx1 = (CStatic*)GetDlgItem(IDC_STATIC_loss1);
//	xx1->SetWindowText(pDoc->m_Loss1L);
	m_Loss1 = pDoc->m_Loss1;

	CStatic* xx1 = (CStatic*)GetDlgItem(IDC_STATIC_loss2);
	xx1->SetWindowText(pDoc->m_Loss2L);
	m_Loss2 = pDoc->m_Loss2;

	m_TotalLoss = atof(m_Loss2);

	m_thr.Format("%0.3f (uV)",pDoc->LinkRxThreshold);
	if(pDoc->LinkRxThreshold>0)
	{
		double RxThreshold = -90.0-10.0*log10(m_R)+20.0*log10(pDoc->LinkRxThreshold);
		m_thr2.Format("%0.3f (dBm)",RxThreshold);
	}
	else
		m_thr2 = "----";

	UpdateData(false);
}


void CPro_P526V14_LinkView::TxRxObj(CDC* pDC) 
{
	int x1,y1,x2,y2,len1,a;

//	len1 = m_AxesL/4;
	len1 = m_fontH150;
	
//	if (pDC->IsPrinting())		len1 = (int)(60.0*29.0/12.0);


	x1 = m_AxesL/8;
	y1 = 4.7*m_AxesT;
	x2 = x1+len1;
	y2 = y1+len1;
	a = 2*x1+m_AxesW;

	DrawRoundRect(pDC,x1,y1,x2,y2,RGB(128,128,128));

//	TextDraw(pDC,x1+len1/4,y1+0.8*len1,"Tx",RGB(255,255,255),0,100,0,FW_BOLD);
//	TextDraw(pDC,x1+len1/8,y1+0.8*len1,"Tx",RGB(255,255,255),0,100,0,FW_BOLD);
	TextDraw(pDC,x1+len1/8,y1+0.8*len1,"Tx",RGB(255,255,255),0,m_fontH100,0,FW_BOLD);

	DrawRect(pDC,	x2						,y2-len1/2 ,
					x2+len1/8+len1/32		,y2-len1/2+len1/16,		RGB(255,255,255));
	DrawRect(pDC,	x2+2*len1/8-len1/16		,y2+6*len1-len1/16 ,
					x2+len1					,y2+6*len1,				RGB(255,255,255));
	DrawRect(pDC,	x2+len1/8+len1/32		,y2-len1/2,
					x2+2*len1/8-len1/32		,y2+6*len1,				RGB(255,255,255));
	DrawRect(pDC,	x2+len1/8,y2+len1/4,
					x2+2*len1/8,y2+5*len1,							RGB(128,128,128));

	DrawRoundRect(pDC,x1+a,y1,x2+a,y2,RGB(128,128,128));

//	TextDraw(pDC,a+x1+len1/4,y1+0.8*len1,"Rx",RGB(255,255,255),0,100,0,FW_BOLD);
//	TextDraw(pDC,a+x1+len1/8,y1+0.8*len1,"Rx",RGB(255,255,255),0,100,0,FW_BOLD);
	TextDraw(pDC,a+x1+len1/8,y1+0.8*len1,"Rx",RGB(255,255,255),0,m_fontH100,0,FW_BOLD);

	DrawRect(pDC,	a+x2-3*len1/2+2*len1/8+3*len1/32	,y2-len1/2 ,
					a+x2-3*len1/2+3*len1/8+4*len1/32	,y2-len1/2+len1/16,		RGB(255,255,255));
	DrawRect(pDC,	a+x2-3*len1/2+5*len1/8-len1			,y2+6*len1-len1/16 ,
					a+x2-3*len1/2+3*len1/8				,y2+6*len1,				RGB(255,255,255));
	DrawRect(pDC,	a+x2-3*len1/2+2*len1/8+3*len1/32	,y2-len1/2,
					a+x2-3*len1/2+3*len1/8+len1/32		,y2+6*len1,				RGB(255,255,255));
	DrawRect(pDC,	a+x2-3*len1/2+2*len1/8+len1/16		,y2+len1/4,
					a+x2-3*len1/2+3*len1/8+len1/16		,y2+5*len1,				RGB(128,128,128));

	//Antenna Arc
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


void CPro_P526V14_LinkView::DrawRect(CDC* pDC,int x1,int y1,int x2,int y2,COLORREF flColor) 
{
	CBrush brush(flColor);
	CBrush *oldbrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID , m_fontH2 ,RGB(0,0,0));	//2
	CPen *oldpen = pDC->SelectObject(&pen);
	pDC->Rectangle(x1,y1,x2,y2);
//	pDC->SelectObject(&oldbrush);
//	pDC->SelectObject(&oldpen);
}

void CPro_P526V14_LinkView::DrawRoundRect(CDC* pDC,int x1,int y1,int x2,int y2,COLORREF flColor) 
{
	CBrush brush(flColor);
	CBrush *oldbrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID , m_fontH6 ,RGB(0,0,0));		//6
	CPen *oldpen = pDC->SelectObject(&pen);
	pDC->RoundRect(x1,y1,x2,y2,(x2-x1)/2,(y2-y1)/2);
//	pDC->SelectObject(&oldbrush);
//	pDC->SelectObject(&oldpen);
}



void CPro_P526V14_LinkView::OnBUTTONLink() 
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

	UpdateData(false);		
}

void CPro_P526V14_LinkView::OnRadioLR() 
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

void CPro_P526V14_LinkView::OnRadioRL() 
{
	OnRadioLR();
}


void CPro_P526V14_LinkView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
//	initDP_LP();

	CString Title_En  = "Link Calculation (P526-14)";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	UpdateData();
	CheckRadioButton(IDC_RADIO_R_L,IDC_RADIO_L_R, IDC_RADIO_L_R);
	
	GetDlgItem(IDC_EDIT_Prd)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_Pid)->ShowWindow(SW_HIDE);

/*
	CEdit* EDIT_S=(CEdit*)GetDlgItem(IDC_EDIT_S);
	CEdit* EDIT_VSWR2=(CEdit*)GetDlgItem(IDC_EDIT_VSWR2);
	CEdit* EDIT_Pbw=(CEdit*)GetDlgItem(IDC_EDIT_Pbw);
	CEdit* EDIT_Pow=(CEdit*)GetDlgItem(IDC_EDIT_Pow);
	CButton* BUTTON_Link=(CButton*)GetDlgItem(IDC_BUTTON_Link);

	CFont font;
	VERIFY(font.CreateFont(
	   16,                        // nHeight
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

	EDIT_S->SetFont(&font);
	EDIT_VSWR2->SetFont(&font);
	BUTTON_Link->SetFont(&font);
	EDIT_Pow->SetFont(&font);
	EDIT_Pbw->SetFont(&font);

	CEdit* xx = (CEdit*)GetDlgItem(IDC_EDIT_Distance);  	xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_tit);					xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_Lba);					xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_Lbs);					xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_Lsph);					xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_Loss1);				xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_Loss2);				xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_FsLoss);				xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_Frequncy);				xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_k);					xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_TxName);				xx->SetFont(&font);
	xx = (CEdit*)GetDlgItem(IDC_EDIT_RxName);				xx->SetFont(&font);
	font.DeleteObject();
*/

	((CEdit*)GetDlgItem(IDC_EDIT_S))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_VSWR2))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_Pbw))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_Pow))->SetFont(&m_font);
	((CButton*)GetDlgItem(IDC_BUTTON_Link))->SetFont(&m_font);

	((CEdit*)GetDlgItem(IDC_EDIT_Distance))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_tit))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_Lba))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_Lbs))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_Lsph))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_Loss1))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_Loss2))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_FsLoss))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_Frequncy))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_k))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_TxName))->SetFont(&m_font);
	((CEdit*)GetDlgItem(IDC_EDIT_RxName))->SetFont(&m_font);

	UpdateData(false);		
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE51);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog((CDialog *)this);

}


void CPro_P526V14_LinkView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)		m_rcPrintRect=pInfo->m_rectDraw;
///////////////////////////////////////////////
	pDC->Rectangle(m_rcPrintRect);

	int x = m_rcPrintRect.left,		w = 14*m_rcPrintRect.Width()/100,
		y = m_rcPrintRect.top, 		h =    m_rcPrintRect.Height()/40;

	CString str , str1;
//	int nHeight = 95;
	int nHeight = DP_LP(pDC, 38);	//95
//	int nHeight = DP_LP(pDC, 22);	//95

	str.Format(_Z("Frequency(MHz) : ")+"%g",    m_Frequency);	TextDraw(pDC,x+w/8, y+h/2+1*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Total Distance(km) : ")+"%s",m_Distance);	TextDraw(pDC,x+w/8, y+h/2+2*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("k_factor : ")+"%s",          m_kfactor);		TextDraw(pDC,x+w/8, y+h/2+3*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	((CStatic*)GetDlgItem(IDC_STATIC_Lba))->GetWindowText(str1);
	str.Format("%s %s","Lba (dB) : ", m_EDIT_Lba);				TextDraw(pDC,x+2*w, y+h/2+1*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("%s",str1);										TextDraw(pDC,x+3*w, y+h/2+1*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	((CStatic*)GetDlgItem(IDC_STATIC_Lbs))->GetWindowText(str1);
	str.Format("%s %s","Lbs (dB) : ", m_EDIT_Lbs);				TextDraw(pDC,x+2*w, y+h/2+2*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("%s",str1);										TextDraw(pDC,x+3*w, y+h/2+2*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	((CStatic*)GetDlgItem(IDC_STATIC_Lsph))->GetWindowText(str1);
	str.Format("%s %s","Lsph (dB) : ", m_EDIT_Lsph);			TextDraw(pDC,x+2*w, y+h/2+3*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("%s",str1);										TextDraw(pDC,x+3*w, y+h/2+3*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	((CStatic*)GetDlgItem(IDC_STATIC_L526))->GetWindowText(str1);
	str.Format("%s %s","L526-14 (dB) : ", m_Loss1);				TextDraw(pDC,x+2*w, y+h/2+4*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("%s",str1);										TextDraw(pDC,x+3*w, y+h/2+4*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	((CStatic*)GetDlgItem(IDC_STATIC_loss2))->GetWindowText(str1);
	str.Format("%s %s",str1,m_Loss2);							TextDraw(pDC,x+2*w, y+h/2+5*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	str.Format(_Z("Free Space Loss(dB) : ")+"%s", m_FsLoss);	TextDraw(pDC,x+4*w, y+h/2+5*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format(_Z("Name :")+" %s", m_TxName);					TextDraw(pDC,x+w/4, y+7*h, str,RGB(200,0,0),0,nHeight+10,0,FW_BOLD);
	str.Format(_Z("EIRP(w) :")+" %s",m_Pr);						TextDraw(pDC,x+w/4, y+8*h, str,RGB(0,0,127),0,nHeight   ,0,FW_BOLD);
	str.Format(_Z("Name :")+" %s", m_RxName);					TextDraw(pDC,x+6*w, y+7*h, str,RGB(200,0,0),0,nHeight+10,0,FW_BOLD);

	str.Format(_Z("Received Level :"));							TextDraw(pDC,x+6*w, y+ 9*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("           %s (uV)", m_S);						TextDraw(pDC,x+6*w, y+10*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	
	if(atof(m_S)>0)
	{
		double PdBm = 10.0*log10(1000.0*pow(atof(m_S)*0.000001,2.0 )/m_R);
		str.Format("           %0.3f (dBm)",PdBm);
	}
	else
		str.Format("           ---- (dBm)");
	TextDraw(pDC,x+6*w,y+11*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	str.Format(_Z("Threshold :"));		TextDraw(pDC,x+6*w,y+12*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("           %s",m_thr);	TextDraw(pDC,x+6*w,y+13*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);
	str.Format("           %s",m_thr2);	TextDraw(pDC,x+6*w,y+14*h,str,RGB(0,0,127),0,nHeight,0,FW_BOLD);

	CFormView::OnPrint(pDC, pInfo);
}

void CPro_P526V14_LinkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CPro_P526V14_LinkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
BOOL CPro_P526V14_LinkView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	((CSMS4DCApp*)AfxGetApp())->SetLandscape();
	return DoPreparePrinting(pInfo);
}


void CPro_P526V14_LinkView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CFormView::OnFilePrintPreview();
}
void CPro_P526V14_LinkView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CFormView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}


HBRUSH CPro_P526V14_LinkView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if ( pWnd->GetDlgCtrlID() == IDC_EDIT_VSWR2 ||
		 pWnd->GetDlgCtrlID() == IDC_EDIT_S     ||
		 pWnd->GetDlgCtrlID() == IDC_EDIT_Pbw   ||		 
		 pWnd->GetDlgCtrlID() == IDC_EDIT_Pow     )
			pDC->SetBkColor(RGB( 253, 177, 13 ));

	if (  pWnd->GetDlgCtrlID() == IDC_EDIT_Distance		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_tit			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Lba			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Lbs			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Lsph			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Loss1		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Loss2		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_FsLoss		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_Frequncy		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_k			)

			pDC->SetTextColor(RGB( 0, 0, 127 ));

	if (  pWnd->GetDlgCtrlID() == IDC_EDIT_TxName		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_RxName)
		//	pDC->SetTextColor(RGB( 255, 255, 0 ));
			pDC->SetBkColor(RGB(255,255,0));

	return hbr;
}


void CPro_P526V14_LinkView::OnChangeEDITVSWR2w() 
{
	UpdateData();
	m_VSWR2 = m_VSWR2w;
	UpdateData(false);	
}

void CPro_P526V14_LinkView::OnChangeEDITSw() 
{
	UpdateData();
	m_S = m_Sw;
	UpdateData(false);
}


void CPro_P526V14_LinkView::OnBUTTONSaveProfile() 
{
	CPro_P526V14_LinkDoc* pDoc = (CPro_P526V14_LinkDoc *)GetDocument();

	CString str;	str.Format("%s_%s",pDoc->LinkName_ST,pDoc->LinkName_Rx);
//	char strFilter[] = { "text Files (*.txt)|*.txt|prf Files (*.prf)|*.prf|All Files (*.*)|*.*||"};
	CString strFilter = _Z("text Files") + " (*.txt)|*.txt|" + _Z("All Files")+" (*.*)|*.*||";
	CFileDialog FileDLG(FALSE, ".txt", str, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);

	if (FileDLG.DoModal() == IDOK)
	{
		FILE *fp=fopen(FileDLG.GetPathName(),"wt");
		if(fp)
		{
			for(int i=0;i<Np;i++)
				fprintf(fp,"%lf %d\n",pDoc->m_di[i],(int)(pDoc->m_hi[i]));
			fclose(fp);
		}
	}	
}

void CPro_P526V14_LinkView::OnBUTTONSaveImage() 
{
	CPro_P526V14_LinkDoc* pDoc = (CPro_P526V14_LinkDoc *)GetDocument();
	CString str = pDoc->GetTitle();

	CDC *pDC = GetDC();
	str = ((CSMS4DCApp *)AfxGetApp())->SaveDesktop(pDC, str);
	ReleaseDC(pDC);	

	ShellExecute(m_hWnd, "open", str, NULL, NULL, SW_SHOWNORMAL);
}



void CPro_P526V14_LinkView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLPressed = true;	
	CFormView::OnLButtonDown(nFlags, point);
}
void CPro_P526V14_LinkView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed = false;
	CFormView::OnLButtonUp(nFlags, point);
}

void CPro_P526V14_LinkView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CPro_P526V14_LinkDoc* pDoc = (CPro_P526V14_LinkDoc *)GetDocument();
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
		CPro_P526V14_LinkDoc* pDoc = (CPro_P526V14_LinkDoc *)GetDocument();
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
void CPro_P526V14_LinkView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_bRPressed = true;	
	CFormView::OnRButtonDown(nFlags, point);
}
void CPro_P526V14_LinkView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_bRPressed = false;
	CPro_P526V14_LinkDoc* pDoc = (CPro_P526V14_LinkDoc *)GetDocument();
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


int CPro_P526V14_LinkView::DP_LP(CDC* pDC,int nH_DP) //97/10/12
{
	if (pDC->IsPrinting())		return (int)(nH_DP*30.0/12.0);

	CSize z1(0, nH_DP);
	pDC->DPtoLP(&z1);
	return z1.cy;
}

void CPro_P526V14_LinkView::initDP_LP(CDC * pDC) //97/10/12
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
