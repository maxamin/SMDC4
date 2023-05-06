// Contour_DEMView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Contour_DEMView.h"

#include "MainFrm.h"
#include <math.h>
#include "NormalizeDLG.h"
#include "ContourDLG.h"
#include "UTM.h"

#include "DataBaseLDLG.h"
#include "SymbolDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMView

IMPLEMENT_DYNCREATE(CContour_DEMView, CView)

CContour_DEMView::CContour_DEMView()
{
	old_cx=old_cy=600;
//	new_cx1=new_cy1=0;
//	new_cx2=new_cy2=600;
	m_LegendFlag=false;
	m_level=255;
	m_bLPressed=false;
	m_bLSelect=false;

	Num_ST=0;
	m_SymbolColor=RGB(0,0,80);
	m_SymbolTextColor=RGB(0,0,80);
	m_SymbolSize=4;

	m_IsPrinting=false;
	m_pscale=1;
}

CContour_DEMView::~CContour_DEMView()
{
	if (Num_ST>0)
	{
		delete [] Lat_ST;
		delete [] Lon_ST;
		delete [] Name_ST;
	}
}


BEGIN_MESSAGE_MAP(CContour_DEMView, CView)
	//{{AFX_MSG_MAP(CContour_DEMView)
	ON_WM_SIZE()
	ON_COMMAND(ID_OPTION_CONTOUR, OnOptionContour)
	ON_COMMAND(ID_Topo_0, OnTopo0)
	ON_UPDATE_COMMAND_UI(ID_Topo_0, OnUpdateTopo0)
	ON_COMMAND(ID_Jet, OnJet)
	ON_UPDATE_COMMAND_UI(ID_Jet, OnUpdateJet)
	ON_COMMAND(ID_SHOW_LEGEND, OnShowLegend)
	ON_UPDATE_COMMAND_UI(ID_SHOW_LEGEND, OnUpdateShowLegend)
	ON_COMMAND(ID_Topo_1, OnTopo1)
	ON_UPDATE_COMMAND_UI(ID_Topo_1, OnUpdateTopo1)
	ON_COMMAND(ID_Gray, OnGray)
	ON_UPDATE_COMMAND_UI(ID_Gray, OnUpdateGray)
	ON_COMMAND(ID_Pink, OnPink)
	ON_UPDATE_COMMAND_UI(ID_Pink, OnUpdatePink)
	ON_COMMAND(ID_Copper, OnCopper)
	ON_UPDATE_COMMAND_UI(ID_Copper, OnUpdateCopper)
	ON_COMMAND(ID_Globe, OnGlobe)
	ON_UPDATE_COMMAND_UI(ID_Globe, OnUpdateGlobe)
	ON_COMMAND(ID_TOOLS_NORMALIZE, OnToolsNormalize)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DATABASE_DISPLAYSELECTEDSTATIONS, OnDatabaseDisplayselectedstations)
	ON_COMMAND(ID_TOOLS_SYMBOLATTRIBUTE, OnToolsSymbolattribute)
	ON_COMMAND(ID_DATABASE_REMOVESTATIONSFROMDISPLAY, OnDatabaseRemovestationsfromdisplay)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMView drawing

#include "memdc.h"
void CContour_DEMView::OnDraw(CDC* pDC)	//98/01/25
{
	CMemDC mDC(pDC);
	OnDraw4(mDC);
}
void CContour_DEMView::OnDraw4(CDC* pDC)	//98/01/25
{
	CContour_DEMDoc *pDoc =(CContour_DEMDoc *) GetDocument();
	
	if(pDoc->m_ReadyDoc ==1)
	{
		pDC->SetStretchBltMode(COLORONCOLOR);	//98/01/25

		m_IsPrinting=pDC->IsPrinting();
//		m_pscale = (m_IsPrinting ? 12 :1);
	////////////////////////////////////////
		BYTE *temp2 , *Display=(BYTE *)malloc(pDoc->Width * pDoc->Height * sizeof(BYTE)); 
		_int16 *temp = (_int16 *)pDoc->bufArea;
		temp2=Display;

		_int16 m_MinValue1 = max(pDoc->bufMin,pDoc->m_MinValue);
		_int16 m_MaxValue1 = min(pDoc->bufMax,pDoc->m_MaxValue);

		for (int i=0;i<pDoc->Width;i++)
			for (int j=0;j<pDoc->Height;j++)
				{
					if((*temp)!=pDoc->m_NoData)
					{
						if (m_MaxValue1 == m_MinValue1)		*temp2 = 0;
						else								*temp2 = Contour( min(max((*temp),m_MinValue1),m_MaxValue1) ,m_MinValue1,m_MaxValue1,m_level);
					}
					else									*temp2 = 255;

					if     ((*temp)<=m_MinValue1)			*temp2 = 0;
					else if((*temp)>=m_MaxValue1)			*temp2 = 254;

					temp2++;		temp++;
				}

		BITMAPFILEHEADER * pbmfh ;
		BITMAPINFO       * pbmi ;
		BYTE             * pBits ;
		int              cxDib, cyDib ;
			
		// Load the entire DIB into memory
		pbmfh = (struct tagBITMAPFILEHEADER *)malloc (1078) ;

//		CString BMP_HEADER =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\BMP_HEADER");
//		FILE *fp=fopen(BMP_HEADER,"rb");
//		fread(pbmfh,1078,1,fp);
//		fclose(fp);
              
		// Get pointers to the info structure & the bits
		pbmfh->bfType='BM';
		pbmfh->bfReserved1=0;
		pbmfh->bfReserved2=0;
		pbmfh->bfSize=pDoc->Width * pDoc->Height+1078;
		pbmfh->bfOffBits=1078;

		pbmi  = (BITMAPINFO *) (pbmfh + 1 ) ;
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
				x1=0;		y1=0;		x2=new_cx;	y2=new_cy;
			}
			m_x1 = x1;	m_y1 = y1;	m_x2 = x2;	m_y2 = y2;

			///////////////////////////////////////
		//	pDC->StretchBlt(0,0,new_cx,new_cy,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);
		//	pDC->StretchBlt(new_cx1,new_cy1,new_cx2,new_cy2,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);

			pDC->StretchBlt(x1,y1,x2,y2,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);

			DeleteDC(MemDC.m_hDC);
			MemDC.Detach();
			old_cx=cxDib;
			old_cy=cyDib;

		}
		free (pbmfh) ;		free(Display);
	/////////////////// Station ////////////////////////

		if (Num_ST>0)
		{
			CPoint Point1;
			for (i=0;i<Num_ST;i++)
			{
				DrawSymboleStation(pDC, Lat_ST[i], Lon_ST[i], m_SymbolColor, m_SymbolSize*m_pscale);
				LatLon2Point(Lat_ST[i], Lon_ST[i],&Point1);
				TextDraw(pDC,Point1.x+4*m_pscale, Point1.y-5*m_pscale,Name_ST[i],m_SymbolTextColor,0,12*m_pscale);
			}
		}
	////////////////////////////////////////
		if(m_LegendFlag)
			LegendLOC(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMView diagnostics

#ifdef _DEBUG
void CContour_DEMView::AssertValid() const
{
	CView::AssertValid();
}

void CContour_DEMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMView message handlers

void CContour_DEMView::OnSize(UINT nType, int cx, int cy) 
{
//	static int old_cx=1200,old_cy=1200;
	CView::OnSize(nType, cx, cy);
	if(cx && cy)
	{
		new_cx=cx;
		new_cy=cy;
	}
}

int CContour_DEMView::Contour(double y,double MinV,double MaxV,int nL) 
{
	if (nL>=255)
		return int(( y - MinV) * 255.0 / (MaxV- MinV));

	double StepV = ((MaxV-MinV)/nL);

	double a1,a2,b1,b2;
	int c=0;

	for (int i=0;i<nL;i++)
	{
		a1=MinV+i*StepV;
		a2=a1+StepV;
		if ( (y>=a1) && (y<a2))
		{
			b1=255.0*(a1-MinV)/(MaxV-MinV);
			b2=255.0*(a2-MinV)/(MaxV-MinV);
		//	c=int((b1+b2)/2.0);
			c=int(b1);
		}
	}
	return c;
}

void CContour_DEMView::OnOptionContour() 
{
	CContour_DEMDoc *pDoc =(CContour_DEMDoc *) GetDocument();
	CContourDLG cdlg;
	cdlg.m_min = pDoc->m_MinValue;
	cdlg.m_max = pDoc->m_MaxValue;
	cdlg.m_step = double((int(1000.0*(pDoc->m_MaxValue - pDoc->m_MinValue)/m_level))/1000.0);
	cdlg.m_nL = m_level;
	if(cdlg.DoModal()==IDOK)
	{
		m_level = cdlg.m_nL;
		Invalidate();
	}
}

void CContour_DEMView::OnTopo0() 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	if(pDoc->colormaptype != "Topo_0")
	{
		pDoc->colormaptype="Topo_0";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CContour_DEMView::OnUpdateTopo0(CCmdUI* pCmdUI) 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Topo_0" ? 1 : 0);
}

void CContour_DEMView::OnJet() 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	if(pDoc->colormaptype != "Jet")
	{
		pDoc->colormaptype="Jet";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CContour_DEMView::OnUpdateJet(CCmdUI* pCmdUI) 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Jet" ? 1 : 0);
}

void CContour_DEMView::OnShowLegend() 
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

void CContour_DEMView::OnUpdateShowLegend(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LegendFlag ? 1 : 0);
	
}

void CContour_DEMView::OnTopo1() 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	if(pDoc->colormaptype != "Topo_1")
	{
		pDoc->colormaptype="Topo_1";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CContour_DEMView::OnUpdateTopo1(CCmdUI* pCmdUI) 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Topo_1" ? 1 : 0);
}

void CContour_DEMView::OnGray() 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	if(pDoc->colormaptype != "Gray")
	{
		pDoc->colormaptype="Gray";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CContour_DEMView::OnUpdateGray(CCmdUI* pCmdUI) 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Gray" ? 1 : 0);
}

void CContour_DEMView::OnPink() 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	if(pDoc->colormaptype != "Pink")
	{
		pDoc->colormaptype="Pink";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CContour_DEMView::OnUpdatePink(CCmdUI* pCmdUI) 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Pink" ? 1 : 0);
}

void CContour_DEMView::OnCopper() 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	if(pDoc->colormaptype != "Copper")
	{
		pDoc->colormaptype="Copper";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CContour_DEMView::OnUpdateCopper(CCmdUI* pCmdUI) 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Copper" ? 1 : 0);
}

void CContour_DEMView::OnGlobe() 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	if(pDoc->colormaptype != "Globe")
	{
		pDoc->colormaptype="Globe";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CContour_DEMView::OnUpdateGlobe(CCmdUI* pCmdUI) 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Globe" ? 1 : 0);
}

void CContour_DEMView::OnToolsNormalize() 
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();

	CNormalizeDLG xx;
	xx.m_MinValue2 = pDoc->bufMin;
	xx.m_MaxValue2 = pDoc->bufMax;
	xx.m_MinValue  = pDoc->m_MinValue;
	xx.m_MaxValue  = pDoc->m_MaxValue;

	if (xx.DoModal()==IDOK)
	{
		pDoc->m_MinValue = xx.m_MinValue;
		pDoc->m_MaxValue = xx.m_MaxValue;
		Invalidate();
	}	
}

void CContour_DEMView::OnMouseMove(UINT nFlags, CPoint point) 
{
	///////////////////// StatusBAR/////////////////////////////////////
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();

	if (pDoc->m_ReadyDoc == 1)
	{
		CString string;
		CRect rect;
		GetClientRect(&rect);

		double lon=pDoc->Freelon0 + (double)((point.x)*(pDoc->Width-1))*
						(pDoc->m_Resolution_x/(double)(pDoc->m_ZoomFactor))
						/((double)(rect.Width()-1));

		double lat=pDoc->Freelat0 + (double)((rect.Height()-1 -point.y)*(pDoc->Height-1))*
						(pDoc->m_Resolution_y/(double)(pDoc->m_ZoomFactor))
						/((double)(rect.Height()-1));

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

lon = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(lon);			//98/01/31

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

		double ix = (((double)(point.x * (pDoc->Width-1))) / ((double)(rect.Width()-1)));
		double jy = (((double)((rect.Height()-1 - point.y) * (pDoc->Height-1))) / ((double)(rect.Height()-1)));
		double z = RoundBUF_Hg(ix, jy);
		string.Format("Alt(m) : %0.0f",z );
	   ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(3, string);
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

void CContour_DEMView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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

double CContour_DEMView::RoundBUF_Hg0(double xps,double yps)  //98/01/31
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();

	int i1=int(xps);		int j1=int(yps);
	int i2=i1+1;			int j2=j1+1;

	double h11 = pDoc->bufArea[i1+j1*pDoc->Width];
	double h12 = pDoc->bufArea[i1+j2*pDoc->Width];
	double h21 = pDoc->bufArea[i2+j1*pDoc->Width];
	double h22 = pDoc->bufArea[i2+j2*pDoc->Width];

	//y = y1 +(x-x1)*(y2-y1)/(x2-x1)

	double hx1 = h11 +(xps-i1)*(h21-h11)/(i2-i1);
	double hx2 = h12 +(xps-i1)*(h22-h12)/(i2-i1);
	double hy = hx1 +(yps-j1)*(hx2-hx1)/(j2-j1);

	return hy;
}
double CContour_DEMView::RoundBUF_Hg(double xps,double yps) //98/01/31
{
	CContour_DEMDoc* pDoc = (CContour_DEMDoc*)GetDocument();
	int W = pDoc->Width;	int H = pDoc->Height;

	int i1 = int(xps);				int j1 = int(yps);
	i1 = max(min(i1,W-1),0);		j1 = max(min(j1,H-1),0);
	int i2 = i1+1;					int j2 = j1+1;
	double h11, h12, h21, h22, hx1, hx2, hy;

	if     ((i1 == (W-1))&&(j1 == (H-1)))		hy = pDoc->bufArea[i1+j1*W];
	else if((i1 == (W-1))&&(j1 < (W-1)))
	{
		h11 = pDoc->bufArea[i1+j1*W]; h12 = pDoc->bufArea[i1+j2*W];	hy  = h11 +(yps-j1)*(h12-h11)/(j2-j1);
	}
	else if((i1 < (W-1))&&(j1 == (H-1)))
	{
		h11 = pDoc->bufArea[i1+j1*W]; h21 = pDoc->bufArea[i2+j1*W];	hy  = h11 +(xps-i1)*(h21-h11)/(i2-i1);
	}
	else
	{
		h11 = pDoc->bufArea[i1+j1*W]; h12 = pDoc->bufArea[i1+j2*W]; h21 = pDoc->bufArea[i2+j1*W]; h22 = pDoc->bufArea[i2+j2*W];

		//y = y1 +(x-x1)*(y2-y1)/(x2-x1)
		hx1 = h11 +(xps-i1)*(h21-h11)/(i2-i1); hx2 = h12 +(xps-i1)*(h22-h12)/(i2-i1);
		hy  = hx1 +(yps-j1)*(hx2-hx1)/(j2-j1);
	}
	return hy;
}



void CContour_DEMView::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CContour_DEMView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed=false;
	m_bLSelect=false;
	CView::OnLButtonUp(nFlags, point);
}


void CContour_DEMView::LegendLOC(CDC* pDC) 
{
	CContour_DEMDoc *pDoc =(CContour_DEMDoc *) GetDocument();
	int x1,y1,x2,y2,w=10,h=1,pscale=12;

	if (pDC->IsPrinting())
	{
		int offset1 = 200;
		pscale=8;
		x1=0+offset1;
	//	y1=0+offset1;

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
	h=1*pscale;
	CSize sz(w, h);


	CBrush brush01(RGB(212,208,200));
	pDC->SelectObject(&brush01);
	pDC->Rectangle(x1,y1,x2,y2);
	pDC->MoveTo(x1,y1+17*pscale);	pDC->LineTo(x2,y1+17*pscale);


	COLORREF RGBt[256];
	CTile m_tile;
	CString label;
	double y;

	m_level = min(255,m_level);
	int tt=int(255.0/m_level);

	m_tile.ColorMap(pDoc->colormaptype);

	for (int i=0;i<256;i++)
	{
		RGBt[i]=m_tile.RGBt[ tt*(i/tt) ];
		CPoint pt(x1+5*pscale, y1+(30+255-i)*pscale);
		CRect rect3(pt, sz);
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

	pDC->TextOut(x1+5*pscale,y1+5*pscale,"Altitude (m)");
	pDC->SetTextAlign(TA_RIGHT);

	for ( i=0;i<256;i=i+17)
	{
		y=pDoc->m_MinValue + ((double)i)*(pDoc->m_MaxValue - pDoc->m_MinValue)/255.0;
//		label.Format("%0.2f",y);
		label.Format("%ld",(long)y);
		pDC->TextOut(x1+w+(5+55)*pscale,y1+(22+(255-i))*pscale,label);
		CPen pen;
		pen.CreatePen(PS_SOLID ,1*pscale,RGBt[i]);
		pDC->SelectObject(&pen);
		pDC->MoveTo(x1+5*pscale+w,y1+(30+(255-i))*pscale);
		pDC->LineTo(x1+w+(10+5)*pscale,y1+(30+(255-i))*pscale);
	}

	pDC->SelectObject(def_font);
	font.DeleteObject(); 
}

void CContour_DEMView::OnDatabaseDisplayselectedstations() 
{
	CDataBaseLDLG dbdlg;
	int xxDLG = dbdlg.DoModal();
	if (xxDLG == IDOK)
	{
		CString m_Sel;
		int Nrow =	((CSMS4DCApp *)AfxGetApp())->Nrow;
		if (Nrow>0)
		{
			double lat1,lon1;
			CString name1;
			for (int i=0;i<Nrow;i++)
			{
				m_Sel	=	((CSMS4DCApp *)AfxGetApp())->m_Sel[i];
				if (m_Sel!="")
				{
					name1 = GetFld(m_Sel,2);
					lat1  = atof(GetFld(m_Sel,3));
					lon1  = atof(GetFld(m_Sel,4));
					AddStation_disp(lat1,lon1,name1) ;
				}
			}
			InvalidateRect(NULL,false);
		}
	}	
}

void CContour_DEMView::DrawSymboleStation(CDC* pDC,double lats,double lons,COLORREF color1,int len1) 
{
	CPen penStation(PS_SOLID,1*m_pscale,color1);
	CPen *Oldpen=pDC->SelectObject(&penStation);
	CBrush brushStation(color1);
	CBrush *Oldbrush=pDC->SelectObject(&brushStation);

	CPoint points;
	LatLon2Point(lats,lons,&points);
	pDC->MoveTo(points.x-len1,points.y);
	pDC->LineTo(points.x+len1,points.y);

	pDC->MoveTo(points.x,points.y-3*len1);
	pDC->LineTo(points.x,points.y+3*len1);
//	CRect rects(points.x-len1,points.y-len1,points.x+len1,points.y+len1);
//	pDC->Draw3dRect(rects,color1,color1);

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

//	pDC->SelectObject(&Oldpen);
//	pDC->SelectObject(&Oldbrush);
}

void CContour_DEMView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
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

CString CContour_DEMView::GetFld(CString Src,int N)
{

	CString Fld = "";
	int place=0,Cnt=0;
	while( place <= Src.GetLength())
	{
		Fld="";
		for(int j = place ; j<=Src.GetLength();j++)
		{
			if(Src.Mid(j, 1) == ",") break;
			Fld = Fld + Src.Mid(j, 1);
		}//end for
		Cnt++;
		place = j + 1;
		if(Cnt==N) break;
	}//end while
	return Fld;
}

void CContour_DEMView::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
{
	CContour_DEMDoc *pDoc =(CContour_DEMDoc *) GetDocument();


	CString globeTileInfo = ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Texts\\globe.txt");
	if (pDoc->TileInfo != globeTileInfo)
	{
		CUtm m_utm;
		m_utm.phi=lat_deg;
		m_utm.lambda=lon_deg;
		m_utm.philambda2UTM();
		lat_deg=m_utm.y;
		lon_deg=m_utm.x;
	}

//	double ix = new_cx1 + ( (new_cx2-1)*(lon_deg - pDoc->Freelon0)/((pDoc->Width-1)*pDoc->m_Resolution_x)   );
//	double jy = new_cy1+new_cy2-1 - ( (new_cy2-1)*(lat_deg - pDoc->Freelat0)/((pDoc->Height-1)*pDoc->m_Resolution_y)  );

	double ix = 0 + ( (new_cx-1)*(lon_deg - pDoc->Freelon0)/((pDoc->Width-1)*pDoc->m_Resolution_x)   );
	double jy = 0 + new_cy-1 - ( (new_cy-1)*(lat_deg - pDoc->Freelat0)/((pDoc->Height-1)*pDoc->m_Resolution_y)  );

	(*PointSt).x = (long)ix;
	(*PointSt).y = (long)(jy);

}

void CContour_DEMView::OnToolsSymbolattribute() 
{

	CSymbolDLG symdlg;

	symdlg.m_symbolcolorR = GetRValue(m_SymbolColor);
	symdlg.m_symbolcolorG = GetGValue(m_SymbolColor);
	symdlg.m_symbolcolorB = GetBValue(m_SymbolColor);

	symdlg.m_symbolTcolorR = GetRValue(m_SymbolTextColor);
	symdlg.m_symbolTcolorG = GetGValue(m_SymbolTextColor);
	symdlg.m_symbolTcolorB = GetBValue(m_SymbolTextColor);

	symdlg.m_symbolsize = m_SymbolSize;

	if (symdlg.DoModal()== IDOK)
	{
		m_SymbolColor=RGB(symdlg.m_symbolcolorR,symdlg.m_symbolcolorG,symdlg.m_symbolcolorB);
		m_SymbolTextColor=RGB(symdlg.m_symbolTcolorR,symdlg.m_symbolTcolorG,symdlg.m_symbolTcolorB);
		m_SymbolSize=symdlg.m_symbolsize;
	}
	InvalidateRect(NULL,false);	
}


void CContour_DEMView::AddStation_disp(double lat1,double lon1,CString name1) 
{
	if (Num_ST==0)
	{
		Num_ST=1;
		Lat_ST=new double[Num_ST];
		Lon_ST=new double[Num_ST];
		Name_ST=new CString[Num_ST];

		Lat_ST[Num_ST-1] = lat1;
		Lon_ST[Num_ST-1] = lon1;
		Name_ST[Num_ST-1] = name1;
	}
	else
	{
		Num_ST=Num_ST+1;

		double *Lat_ST0 = new double[Num_ST];
		double *Lon_ST0 = new double[Num_ST];
		CString *Name_ST0 = new CString[Num_ST];

		for (int i=0;i<Num_ST-1;i++)
		{
			Lat_ST0[i] = Lat_ST[i];
			Lon_ST0[i] = Lon_ST[i];
			Name_ST0[i] = Name_ST[i];
		}
		Lat_ST0[Num_ST-1] = lat1;
		Lon_ST0[Num_ST-1] = lon1;
		Name_ST0[Num_ST-1] = name1;

		delete [] Lat_ST;
		delete [] Lon_ST;
		delete [] Name_ST;
		Lat_ST = new double[Num_ST];
		Lon_ST = new double[Num_ST];
		Name_ST = new CString[Num_ST];
		for ( i=0;i<Num_ST;i++)
		{
			Lat_ST[i] = Lat_ST0[i];
			Lon_ST[i] = Lon_ST0[i];
			Name_ST[i] = Name_ST0[i];
		}

		delete [] Lat_ST0;
		delete [] Lon_ST0;
		delete [] Name_ST0;
	}
}

void CContour_DEMView::OnDatabaseRemovestationsfromdisplay() 
{
	if (Num_ST>0)
	{
		delete [] Lat_ST;
		delete [] Lon_ST;
		delete [] Name_ST;
		Num_ST = 0;
	}
	InvalidateRect(NULL,false);	
}


BOOL CContour_DEMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CContour_DEMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CContour_DEMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CContour_DEMView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
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
void CContour_DEMView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}

void CContour_DEMView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

void CContour_DEMView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "Contour_DEM";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE27);
}

BOOL CContour_DEMView::OnEraseBkgnd(CDC* pDC)	//98/01/25
{
	return true;
//	return CView::OnEraseBkgnd(pDC);
}
