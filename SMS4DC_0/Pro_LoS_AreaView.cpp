// Pro_LoS_AreaView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_LoS_AreaView.h"
#include "Pro_LoS_AreaDoc.h"
#include "MainFrm.h"
#include <math.h>
#include "UTM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaView

IMPLEMENT_DYNCREATE(CPro_LoS_AreaView, CView)

CPro_LoS_AreaView::CPro_LoS_AreaView()
{
	old_cx=old_cy=600;
	new_cx=new_cy=600;
	m_LegendFlag=false;
	m_bLPressed=false;
	m_bLSelect=false;
}

CPro_LoS_AreaView::~CPro_LoS_AreaView()
{
}


BEGIN_MESSAGE_MAP(CPro_LoS_AreaView, CView)
	//{{AFX_MSG_MAP(CPro_LoS_AreaView)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SHOW_LEGEND, OnShowLegend)
	ON_UPDATE_COMMAND_UI(ID_SHOW_LEGEND, OnUpdateShowLegend)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_TOOLS_GOOGLE, OnToolsGoogle)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaView drawing

#include "memdc.h"
void CPro_LoS_AreaView::OnDraw(CDC* pDC)	//98/01/25
{
	CMemDC mDC(pDC);
	OnDraw4(mDC);
}
void CPro_LoS_AreaView::OnDraw4(CDC* pDC)	//98/01/25
{
	CPro_LoS_AreaDoc *pDoc =(CPro_LoS_AreaDoc *) GetDocument();
	
	if(pDoc->m_ReadyDoc ==1)
	{
		pDC->SetStretchBltMode(COLORONCOLOR);	//98/01/25
	////////////////////////////////////////
		BYTE *temp2 , *Display=(BYTE *)malloc(pDoc->Width * pDoc->Height * sizeof(BYTE)); 
		double *temp = (double *)pDoc->Er;
		temp2=Display;

		double m_MinValue1 = max(pDoc->ErMin,pDoc->m_MinValue);
		double m_MaxValue1 = min(pDoc->ErMax,pDoc->m_MaxValue);

		for (int i=0;i<pDoc->Width;i++)
			for (int j=0;j<pDoc->Height;j++)
				{
			//		if((*temp)!=pDoc->m_NoData)		//9801/19
			//		{
						if (m_MaxValue1 == m_MinValue1)		*temp2 = 0;
						else
							*temp2=(BYTE )(( min(max((*temp),m_MinValue1),m_MaxValue1) - m_MinValue1)*255.0/(m_MaxValue1-m_MinValue1));
			//		}
			//		else	*temp2 = 255;

					if     ((*temp)<=m_MinValue1)	*temp2 = 0;
					else if((*temp)>=m_MaxValue1)	*temp2 = 254;

					temp2++;		temp++;
				}

		BITMAPFILEHEADER * pbmfh ;
		BITMAPINFO       * pbmi ;
		BYTE             * pBits ;
		int              cxDib, cyDib ;
			
		// Load the entire DIB into memory
		pbmfh = (struct tagBITMAPFILEHEADER *)malloc (1078) ;
		CString BMP_HEADER =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\BMP_HEADER");
		FILE *fp=fopen(BMP_HEADER,"rb");
		fread(pbmfh,1078,1,fp);
		fclose(fp);
              
		// Get pointers to the info structure & the bits
		pbmfh->bfType=19778;
		pbmfh->bfReserved1=0;
		pbmfh->bfReserved2=0;
		pbmfh->bfSize=pDoc->Width * pDoc->Height+1078;
		pbmfh->bfOffBits=1078;

		pbmi  = (BITMAPINFO *) (pbmfh + 1) ;
		pbmi->bmiHeader.biSize=40;
		pbmi->bmiHeader.biWidth=pDoc->Width ;
		pbmi->bmiHeader.biHeight=pDoc->Height ;
		pbmi->bmiHeader.biPlanes=1;
		pbmi->bmiHeader.biBitCount=8;
		pbmi->bmiHeader.biCompression=0;
		pbmi->bmiHeader.biSizeImage=pDoc->Width * pDoc->Height ;
		pbmi->bmiHeader.biXPelsPerMeter=0;
		pbmi->bmiHeader.biYPelsPerMeter=0;
		pbmi->bmiHeader.biClrUsed=256;
		pbmi->bmiHeader.biClrImportant=256;
		for( i=0;i<256;i++)
		{
			pbmi->bmiColors[i].rgbBlue =  GetBValue(pDoc->RGBt[i]);
			pbmi->bmiColors[i].rgbGreen = GetGValue(pDoc->RGBt[i]);
			pbmi->bmiColors[i].rgbRed =   GetRValue(pDoc->RGBt[i]);
			pbmi->bmiColors[i].rgbReserved=0;
		}
		pbmi->bmiColors[255].rgbBlue=255;
		pbmi->bmiColors[255].rgbGreen=0;
		pbmi->bmiColors[255].rgbRed=0;
		pbmi->bmiColors[255].rgbReserved=0;	
		
		pBits = (BYTE *) Display; 
		// Get the DIB width and height
		if (pbmi->bmiHeader.biSize == sizeof (BITMAPCOREHEADER))
		{
			cxDib = ((BITMAPCOREHEADER *) pbmi)->bcWidth ;
			cyDib = ((BITMAPCOREHEADER *) pbmi)->bcHeight ;
		}
		else
		{
			cxDib =      pbmi->bmiHeader.biWidth ;
			cyDib = abs (pbmi->bmiHeader.biHeight) ;
		}

		if (pbmfh)
		{
			CDC MemDC;
			BITMAP bm;
			CBitmap m_bitmap;

			m_bitmap.CreateCompatibleBitmap(pDC, pDoc->Width , pDoc->Height);
			m_bitmap.GetObject (sizeof (BITMAP), &bm);
			MemDC.CreateCompatibleDC(pDC);
			MemDC.SetMapMode(pDC->GetMapMode());
			MemDC.SelectObject(m_bitmap);

			SetDIBitsToDevice (MemDC.m_hDC,    //pDC->m_hDC, 
							  0,         // xDst
							  0,         // yDst
							  cxDib,     // cxSrc
							  cyDib,     // cySrc
							  0,         // xSrc
							  0,         // ySrc
							  0,         // first scan line
							  cyDib,     // number of scan lines
							  pBits, 
							  pbmi, 
							  DIB_RGB_COLORS) ;

			///////////////////////////////////////
			int x1,y1,x2,y2;
			if (pDC->IsPrinting())
			{
				int offset = 1300;
				x1=m_rcPrintRect.left+offset;
				y1=m_rcPrintRect.top+offset;
				x2=m_rcPrintRect.right-x1-offset;
				y2=m_rcPrintRect.bottom-y1-offset;
			}
			else
			{
				x1=0;		y1=0;
				x2=new_cx;	y2=new_cy;
			}
			///////////////////////////////////////
		//	pDC->StretchBlt(0,0,new_cx,new_cy,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);
			pDC->StretchBlt(x1,y1,x2,y2,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);
			DeleteDC(MemDC.m_hDC);
			MemDC.Detach();
			old_cx=cxDib;
			old_cy=cyDib;

		}
		free (pbmfh) ;
		free(Display);
	////////////////////////////////////////
		if(m_LegendFlag)
			LegendLOC(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaView diagnostics

#ifdef _DEBUG
void CPro_LoS_AreaView::AssertValid() const
{
	CView::AssertValid();
}

void CPro_LoS_AreaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaView message handlers

void CPro_LoS_AreaView::OnSize(UINT nType, int cx, int cy) 
{
//	static int old_cx=1200,old_cy=1200;
	CView::OnSize(nType, cx, cy);
	if(cx && cy)
	{
		new_cx=cx;
		new_cy=cy;
	}
}

void CPro_LoS_AreaView::OnMouseMove(UINT nFlags, CPoint point) 
{
	///////////////////// StatusBAR/////////////////////////////////////
	CPro_LoS_AreaDoc* pDoc = (CPro_LoS_AreaDoc*)GetDocument();

	if (pDoc->m_ReadyDoc == 1)
	{
		//SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));

		CString string;
		CRect rect;
		GetClientRect(&rect);

		double lon=pDoc->LoSlon0 + (double)((point.x)*(pDoc->Width-1))*
						(pDoc->m_Resolution_x/(double)(pDoc->m_ZoomFactor))
						/((double)(rect.Width()-1));

		double lat=pDoc->LoSlat0 + (double)((rect.Height()-1 -point.y)*(pDoc->Height-1))*
						(pDoc->m_Resolution_x/(double)(pDoc->m_ZoomFactor))
						/((double)(rect.Height()-1));
/*		//98/01/24
		CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
		if (pDoc->TileInfo != globeTileInfo)
		{
			CUtm m_utm;
			m_utm.y = lat;
			m_utm.x = lon;
			m_utm.UTM2philambda();
			lat=m_utm.phi;
			lon=m_utm.lambda;
		}
*/
lon = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(lon);

		string.Format("Lat :%0.12f ° , Lon: %0.12f °",lat,lon);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(0, string);

		char   xU,yU;
		int    xUTMD,xUTMM,yUTMD,yUTMM;
		double xUTMS,yUTMS;
		DEG2DMS("LON",lon,&xUTMD,&xUTMM,&xUTMS,&xU);
		DEG2DMS("LAT",lat,&yUTMD,&yUTMM,&yUTMS,&yU);

		string.Format("Lat(%c) : %02d ° %02d ' %0.3f ''",yU,yUTMD,yUTMM,yUTMS );
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, string);

		string.Format("Lon(%c) : %03d ° %02d ' %0.3f ''",xU,xUTMD,xUTMM,xUTMS );
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(2, string);

//98/01/24
//		int ix =(int) (((double)(point.x * (pDoc->Width-1))) / ((double)(rect.Width()-1)));
//		int jy =(int) (((double)((rect.Height()-1 - point.y) * (pDoc->Height-1))) / ((double)(rect.Height()-1)));
//		_int16 z = pDoc->bufArea[ix+jy*pDoc->Width];

double xps = (((double)(point.x * (pDoc->Width-1.0))) / ((double)(rect.Width()-1.0)));
double yps = (((double)((rect.Height()-1.0 - point.y) * (pDoc->Height-1.0))) / ((double)(rect.Height()-1.0)));
int z = Round(RoundBUF_E_A(xps, yps, pDoc->Width, pDoc->Height, pDoc->bufArea));
int E = Round(RoundBUF_E_A(xps, yps, pDoc->Width, pDoc->Height, pDoc->Er     ));		//0 , 1

		string.Format("Alt(m) : %d",z );
	   ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(3, string);

//		double E = pDoc->Er[ix+jy*pDoc->Width];
//		string.Format(_Z("Line of Sight :")+" %s",((E==1.0) ? _Z("Yes") : _Z("No")) );
		string.Format(_Z("Line of Sight :")+" %s",((E==1  ) ? _Z("Yes") : _Z("No")) );

	   ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(5, string);

		double dist=Distance_km(pDoc->LoSlat_ST,pDoc->LoSlon_ST,lat,lon);
		string.Format("Dist(km) : %0.3f",dist );
	   ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(4, string);
		if (m_LegendFlag && m_bLPressed && m_bLSelect)
		{
			m_x1L = m_x1L + (point.x - m_x0L);
			m_y1L = m_y1L + (point.y - m_y0L);
			InvalidateRect(NULL,false);
			m_x0L = point.x;
			m_y0L = point.y;
		}
	}

	CView::OnMouseMove(nFlags, point);
}

//98/01/24
double CPro_LoS_AreaView::RoundBUF_E_A(double xps,double yps, int W, int H, _int16 *E_A) 
{
	int i1 = int(xps);				int j1 = int(yps);
	i1 = max(min(i1,W-1),0);		j1 = max(min(j1,H-1),0);
	int i2 = i1+1;					int j2 = j1+1;

	double h11, h12, h21, h22, hx1, hx2, hy;
	if     ((i1 == (W-1))&&(j1 == (H-1)))			hy = E_A[i1+j1*W];
	else if((i1 == (W-1))&&(j1 <  (H-1)))
	{
		h11 = E_A[i1+j1*W]; 	h12 = E_A[i1+j2*W];	hy  = h11 +(yps-j1)*(h12-h11)/(j2-j1);
	}
	else if((i1  < (W-1))&&(j1 == (H-1)))
	{
		h11 = E_A[i1+j1*W]; 	h21 = E_A[i2+j1*W];	hy  = h11 +(xps-i1)*(h21-h11)/(i2-i1);
	}
	else
	{
		h11 = E_A[i1+j1*W];	h12 = E_A[i1+j2*W]; 	h21 = E_A[i2+j1*W]; 	h22 = E_A[i2+j2*W];
		hx1 = h11 +(xps-i1)*(h21-h11)/(i2-i1); 
		hx2 = h12 +(xps-i1)*(h22-h12)/(i2-i1);		hy  = hx1 +(yps-j1)*(hx2-hx1)/(j2-j1);
	}
	return hy;
}
//98/01/24
double CPro_LoS_AreaView::RoundBUF_E_A(double xps,double yps, int W, int H, double *E_A) 
{
	int i1 = int(xps);				int j1 = int(yps);
	i1 = max(min(i1,W-1),0);		j1 = max(min(j1,H-1),0);
	int i2 = i1+1;					int j2 = j1+1;

	double h11, h12, h21, h22, hx1, hx2, hy;
	if     ((i1 == (W-1))&&(j1 == (H-1)))			hy = E_A[i1+j1*W];
	else if((i1 == (W-1))&&(j1 <  (H-1)))
	{
		h11 = E_A[i1+j1*W]; 	h12 = E_A[i1+j2*W];	hy  = h11 +(yps-j1)*(h12-h11)/(j2-j1);
	}
	else if((i1  < (W-1))&&(j1 == (H-1)))
	{
		h11 = E_A[i1+j1*W]; 	h21 = E_A[i2+j1*W];	hy  = h11 +(xps-i1)*(h21-h11)/(i2-i1);
	}
	else
	{
		h11 = E_A[i1+j1*W];	h12 = E_A[i1+j2*W]; 	h21 = E_A[i2+j1*W]; 	h22 = E_A[i2+j2*W];
		hx1 = h11 +(xps-i1)*(h21-h11)/(i2-i1); 
		hx2 = h12 +(xps-i1)*(h22-h12)/(i2-i1);		hy  = hx1 +(yps-j1)*(hx2-hx1)/(j2-j1);
	}
	return hy;
}
//98/01/24
int CPro_LoS_AreaView::Round(double x) 
{
	int y;
	int x1 = (int)x;
	if(x>=0)	{int x2 = x1+1;		y = ( (x > ((double)x1)+0.45) ? x2 : x1);}
	else		{int x2 = x1-1;		y = ( (x > ((double)x2)+0.45) ? x1 : x2);}
	return y;
}

void CPro_LoS_AreaView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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
double CPro_LoS_AreaView::Distance_km(double lat1,double lon1,double lat2,double lon2) 
{
	double temp1,temp2,temp3,rng;

	double pi=4.0*atan(1.0);
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
	return (rng);

}

void CPro_LoS_AreaView::OnShowLegend() 
{
	m_LegendFlag = (m_LegendFlag ? false : true);
	if (m_LegendFlag)
	{
		CRect rect01;GetClientRect(&rect01);
		m_x1L=rect01.Width()-85;
		m_y1L=rect01.top;
		InvalidateRect(CRect(m_x1L,m_y1L,m_x1L+85,m_y1L+293),false);
	}
	InvalidateRect(NULL,false);
}

void CPro_LoS_AreaView::OnUpdateShowLegend(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LegendFlag ? 1 : 0);
}


void CPro_LoS_AreaView::LegendLOC(CDC* pDC) 
{
	CPro_LoS_AreaDoc *pDoc =(CPro_LoS_AreaDoc *) GetDocument();
	int x1,y1,x2,y2,w=10,pscale=12,Nrow=1;

	if (pDC->IsPrinting())
	{
		int offset1 = 200;
		pscale=8;
		x1=0+offset1;

		int offset = 1300;
		y1=m_rcPrintRect.top+offset;
	}
	else
	{
		pscale=1;
		x1=m_x1L;y1=m_y1L;
	}
	x2=x1+85*pscale;
	y2=y1+293*pscale;
	w=10*pscale;

	CBrush brush01(RGB(212,208,200));
	pDC->SelectObject(&brush01);
	pDC->Rectangle(x1,y1,x2,y2);
	pDC->MoveTo(x1,y1+17*pscale);	pDC->LineTo(x2,y1+17*pscale);

	COLORREF RGBt[256];
	CTile m_tile;
	CString label;
	m_tile.ColorMap(pDoc->colormaptype);

	int tt=int(255.0/Nrow),		tt1=int(255.0/(Nrow+1));

	for (int i=0;i<=Nrow;i++)
	{
		RGBt[i]=m_tile.RGBt[ tt*(i) ];
		CPoint pt(x1+5*pscale, y1+(30+255-(i+1)*tt1)*pscale);

		CRect rect3(pt, CSize(w, tt1*pscale));
		CBrush brush3(RGBt[i]);
		pDC->SelectObject(&brush3);
		pDC->FillRect(&rect3,&brush3);
	}

	pDC->SetBkMode(TRANSPARENT);
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));      
	lf.lfHeight = 12*pscale;               
	lf.lfWidth =0;
	lf.lfWeight = FW_BOLD;
	strcpy(lf.lfFaceName, "Arial");       
	lf.lfEscapement=0;
	VERIFY(font.CreateFontIndirect(&lf));  
	CFont* def_font = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0,0,0));

	pDC->TextOut(x1+5*pscale,y1+5*pscale,_Z("Color Legend"));
	pDC->SetTextAlign(TA_LEFT);


	label.Format("%s",_Z("LoS"));
	pDC->TextOut(x1+w+(5+5)*pscale,y1+(22+(255-3*tt1/2))*pscale,label);
	label.Format("%s",_Z("No LoS"));
	pDC->TextOut(x1+w+(5+5)*pscale,y1+(22+(255-tt1/2))*pscale,label);


	pDC->SelectObject(def_font);
	font.DeleteObject(); 
}

void CPro_LoS_AreaView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLPressed=true;
	if (m_LegendFlag)
	{
		if ((point.x>=m_x1L) && (point.x<=m_x1L+85) && (point.y>=m_y1L) && (point.y<=m_y1L+293) )
		{
			m_bLSelect=true;
			m_x0L=point.x;
			m_y0L=point.y;
		}
		else
			m_bLSelect=false;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CPro_LoS_AreaView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed=false;
	m_bLSelect=false;
	CView::OnLButtonUp(nFlags, point);
}

BOOL CPro_LoS_AreaView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CPro_LoS_AreaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CPro_LoS_AreaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
void CPro_LoS_AreaView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
	{
		m_rcPrintRect=pInfo->m_rectDraw;
		int x1,y1,x2,y2;
		int offset = 200;
		x1=m_rcPrintRect.left+offset;
		y1=m_rcPrintRect.top+offset;
		x2=m_rcPrintRect.right-x1-offset;
		y2=m_rcPrintRect.bottom-y1-offset;
		pDC->Rectangle(x1,y1,x2,y2);
	}
	CView::OnPrint(pDC, pInfo);
}


void CPro_LoS_AreaView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}

void CPro_LoS_AreaView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////Google Earth//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CPro_LoS_AreaView::CaptureDC()
{
	CPro_LoS_AreaDoc *pDoc =(CPro_LoS_AreaDoc *) GetDocument();
	CString str = pDoc->GetTitle();
	CString fileOUTkml = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Reports\\") + str + _T("g.kml");

	CString sFile, sPath;
	BOOL flagShow = FALSE;
	if(((CSMS4DCApp *)AfxGetApp())->KmlSave( &sFile, &sPath , &flagShow , fileOUTkml))
	{
		CString filename = sFile;
		int L = filename.GetLength();
		filename.Delete(L-4,4);

		fileOUTkml = sPath;
		CString fileOUTbmp = fileOUTkml;
		L = fileOUTbmp.GetLength();
		fileOUTbmp.Delete(L-3,3);
		fileOUTbmp = fileOUTbmp + _T("bmp");

		CString gifFile = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Image_map\\st.gif");
		((CSMS4DCApp *)AfxGetApp())->PeekAndPump();

		CDC *pDC = GetDC();
		((CSMS4DCApp *)AfxGetApp())->CDCToBmp24(pDC, fileOUTbmp);
		ReleaseDC(pDC);

		double lonW = pDoc->LoSlon0;
		double lonE = pDoc->LoSlon0 + (double)(pDoc->Width -1)*( pDoc->m_Resolution_x / (double)(pDoc->m_ZoomFactor));
		double latS = pDoc->LoSlat0;
		double latN = pDoc->LoSlat0 + (double)(pDoc->Height-1)*( pDoc->m_Resolution_x / (double)(pDoc->m_ZoomFactor));
		FILE *fp2 = fopen(fileOUTkml,_T("wt"));
		CString str1,str2,str3,str4;

double LoSlon_ST = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(pDoc->LoSlon_ST);

		str1.Format(_T("<Folder><name>SMS4DC :</name><open>1</open>"));
		str2.Format(_T("<GroundOverlay><name>%s</name><Icon>%s</Icon><LatLonBox>"),filename, filename + _T(".bmp"));
		str3.Format(_T("<west>%lf</west><east>%lf</east><south>%lf</south><north>%lf</north></LatLonBox></GroundOverlay>"),lonW,lonE,latS,latN);
//		str4.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),pDoc->LoSName_ST,gifFile ,pDoc->LoSlon_ST,pDoc->LoSlat_ST);
		str4.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),pDoc->LoSName_ST,gifFile ,      LoSlon_ST,pDoc->LoSlat_ST);
		
		fprintf(fp2,_T("<kml> %s %s %s %s </Folder></kml>"),str1,str2,str3,str4);
		fclose(fp2);

		if(flagShow)	ShellExecute(m_hWnd, "open", fileOUTkml, NULL, NULL, SW_SHOWNORMAL);
	}
}
void CPro_LoS_AreaView::OnToolsGoogle() 
{
	CaptureDC();
}

void CPro_LoS_AreaView::OnFileSaveAs() 
{
	OnFileSave();	
}
void CPro_LoS_AreaView::OnFileSave() 
{
	CPro_LoS_AreaDoc *pDoc =(CPro_LoS_AreaDoc *) GetDocument();
	CString str = pDoc->GetTitle();

	CDC *pDC = GetDC();
	((CSMS4DCApp *)AfxGetApp())->SaveDesktop(pDC, str);
	ReleaseDC(pDC);
}

void CPro_LoS_AreaView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "Area Calculation (Line of Sight)";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE10);
}

BOOL CPro_LoS_AreaView::OnEraseBkgnd(CDC* pDC) 	//98/01/25
{
	return true;
//	return CView::OnEraseBkgnd(pDC);
}
