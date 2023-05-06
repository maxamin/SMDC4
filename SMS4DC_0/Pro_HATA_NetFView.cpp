// Pro_HATA_NetFView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_HATA_NetFView.h"

#include "Pro_HATA_NetFDoc.h"
#include "NormalizeDLG.h"
#include "MainFrm.h"
#include <math.h>
#include "UTM.h"
#include "ContourDLG.h"
#include "CoverageDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_NetFView

IMPLEMENT_DYNCREATE(CPro_HATA_NetFView, CView)

CPro_HATA_NetFView::CPro_HATA_NetFView()
{
	old_cx=old_cy=600;
	new_cx=new_cy=600;
	m_LegendFlag=false;
	m_bLPressed=false;
	m_bLSelect=false;
}

CPro_HATA_NetFView::~CPro_HATA_NetFView()
{
}


BEGIN_MESSAGE_MAP(CPro_HATA_NetFView, CView)
	//{{AFX_MSG_MAP(CPro_HATA_NetFView)
	ON_WM_SIZE()
	ON_COMMAND(ID_TOOLS_NORMALIZE, OnToolsNormalize)
	ON_COMMAND(ID_SHOW_LEGEND, OnShowLegend)
	ON_UPDATE_COMMAND_UI(ID_SHOW_LEGEND, OnUpdateShowLegend)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TOOLS_CONTOUR, OnToolsContour)
	ON_COMMAND(ID_TOOLS_COVERAGEAREA, OnToolsCoveragearea)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_COVERAGEAREA, OnUpdateToolsCoveragearea)
	ON_COMMAND(ID_Topo_0, OnTopo0)
	ON_UPDATE_COMMAND_UI(ID_Topo_0, OnUpdateTopo0)
	ON_COMMAND(ID_Topo_1, OnTopo1)
	ON_UPDATE_COMMAND_UI(ID_Topo_1, OnUpdateTopo1)
	ON_COMMAND(ID_Jet, OnJet)
	ON_UPDATE_COMMAND_UI(ID_Jet, OnUpdateJet)
	ON_COMMAND(ID_Gray, OnGray)
	ON_UPDATE_COMMAND_UI(ID_Gray, OnUpdateGray)
	ON_COMMAND(ID_Pink, OnPink)
	ON_UPDATE_COMMAND_UI(ID_Pink, OnUpdatePink)
	ON_COMMAND(ID_Copper, OnCopper)
	ON_UPDATE_COMMAND_UI(ID_Copper, OnUpdateCopper)
	ON_COMMAND(ID_Globe, OnGlobe)
	ON_UPDATE_COMMAND_UI(ID_Globe, OnUpdateGlobe)
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
// CPro_HATA_NetFView drawing

#include "memdc.h"
void CPro_HATA_NetFView::OnDraw(CDC* pDC)	//98/01/25
{
	CMemDC mDC(pDC);
	OnDraw4(mDC);
}
void CPro_HATA_NetFView::OnDraw4(CDC* pDC)	//98/01/25
{
	CPro_HATA_NetFDoc *pDoc =(CPro_HATA_NetFDoc *) GetDocument();
	
	if(pDoc->m_ReadyDoc ==1)
	{
		pDC->SetStretchBltMode(COLORONCOLOR);	//98/01/25
	////////////////////////////////////////
		BYTE *temp2 , *Display=(BYTE *)malloc(pDoc->Width * pDoc->Height * sizeof(BYTE)); 
		double *temp = (double *)pDoc->Er;
		temp2=Display;

		double m_MinValue1 = max(pDoc->ErMin,pDoc->m_MinValue);
		double m_MaxValue1 = min(pDoc->ErMax,pDoc->m_MaxValue);
		if (pDoc->m_bThreshold)
		{
			m_MinValue1 = pDoc->ErMin;
			m_MaxValue1 = pDoc->ErMax;
		}
		m_CoveredPix = 0;
		for (int i=0;i<pDoc->Width;i++)
			for (int j=0;j<pDoc->Height;j++)
				{
			//		if((*temp)!=pDoc->m_NoData)		//98/01/19
			//		{
						if (m_MaxValue1 == m_MinValue1)				*temp2=0;
						else
						{
							if (pDoc->m_bThreshold)
							{
								if (min(max((*temp),m_MinValue1),m_MaxValue1) >= pDoc->m_Threshold)
								{	
									*temp2 = 159;
									m_CoveredPix = m_CoveredPix +1;
								}
								else		*temp2 = 0;
							}
							else
								*temp2 = Contour( min(max((*temp),m_MinValue1),m_MaxValue1) ,m_MinValue1,m_MaxValue1,pDoc->m_level);
							//	*temp2=(BYTE )(( min(max((*temp),m_MinValue1),m_MaxValue1) - m_MinValue1) * 255 / (m_MaxValue1- m_MinValue1));
						}
			//		}
			//		else	*temp2=255;


					if     ((*temp)<=m_MinValue1)			*temp2=0;
			//		else if((*temp)>=m_MaxValue1)			*temp2=254;		//98/01/19

					temp2++;			temp++;
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
		/*	//98/01/19
		pbmi->bmiColors[255].rgbBlue=255;
		pbmi->bmiColors[255].rgbGreen=0;
		pbmi->bmiColors[255].rgbRed=0;
		pbmi->bmiColors[255].rgbReserved=0;	
		*/
		pbmi->bmiColors[0].rgbBlue  = 127;
		pbmi->bmiColors[0].rgbGreen = 127;
		pbmi->bmiColors[0].rgbRed   = 127;
		
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
		if (pDoc->m_bThreshold)		AreaShow(pDC);
		if(m_LegendFlag)			LegendLOC(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_NetFView diagnostics

#ifdef _DEBUG
void CPro_HATA_NetFView::AssertValid() const
{
	CView::AssertValid();
}

void CPro_HATA_NetFView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_NetFView message handlers


int CPro_HATA_NetFView::Contour(double y,double MinV,double MaxV,int nL) 
{
//	if(nL>=255) return int(( y - MinV) * 255.0 / (MaxV- MinV));	//98/01/19
	if(nL>=255) return int( 1.0 + (y-MinV)*254.0/(MaxV-MinV) );

	double StepV = ((MaxV-MinV)/nL);

	double a1,a2,b1/*,b2*/;										//98/01/19
	int c = 0;
	for (int i=0;i<nL;i++)
	{
		a1 = MinV + i*StepV;		a2 = a1 + StepV;
		if ( (y>=a1) && (y<a2))
		{
			b1 = 1.0 + 254.0*(a1-MinV)/(MaxV-MinV);				//98/01/19
		/*
			b1=255.0*(a1-MinV)/(MaxV-MinV);
			b2=255.0*(a2-MinV)/(MaxV-MinV);
		//	c=int((b1+b2)/2.0);
		*/
			c = int(b1);
		}
	}
	return c;
}



void CPro_HATA_NetFView::LegendLOC(CDC* pDC) 
{
	CPro_HATA_NetFDoc *pDoc =(CPro_HATA_NetFDoc *) GetDocument();
	int x1,y1,x2,y2,w=10,h=1,pscale=12;

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

	pDoc->m_level = min(255,pDoc->m_level);
	int tt=int(255.0/pDoc->m_level);

	m_tile.ColorMap(pDoc->colormaptype);

	if (pDoc->m_bThreshold)
	{
		RGBt[0] = m_tile.RGBt[159];						//98/01/19
		RGBt[1] = RGB(127,127,127);						//98/01/19
		for (int i=0;i<2;i++)
		{
//			RGBt[i]=m_tile.RGBt[ 0+(1-i)*159 ];			//98/01/19
			CPoint pt(x1+5*pscale, y1+(30+127*i)*pscale);
			CRect rect3(pt, CSize(w, 127.5*pscale));
			CBrush brush3(RGBt[i]);
			pDC->SelectObject(&brush3);
			pDC->FillRect(&rect3,&brush3);
		}
	}
	else
	{
		for (int i=0;i<256;i++)
		{
			RGBt[i]=m_tile.RGBt[ tt*(i/tt) ];
			CPoint pt(x1+5*pscale, y1+(30+255-i)*pscale);
			CRect rect3(pt, sz);
			CBrush brush3(RGBt[i]);
			pDC->SelectObject(&brush3);
			pDC->FillRect(&rect3,&brush3);
		}
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

	pDC->TextOut(x1+5*pscale,y1+5*pscale,"E (dBuV/m)");
	pDC->SetTextAlign(TA_RIGHT);

	if (pDoc->m_bThreshold)
	{
		label.Format("%0.2f",pDoc->m_Threshold);
		pDC->TextOut(x1+w+(5+55)*pscale,y1+(-10+159)*pscale,label);

		CPen pen;
		pen.CreatePen(PS_SOLID ,1,RGB(0,0,0));
		pDC->SelectObject(&pen);
		pDC->MoveTo(x1+5*pscale+w,y1+(-2+159)*pscale);
		pDC->LineTo(x1+w+(5+10)*pscale,y1+(-2+159)*pscale);
	}
	else
	{
		for (int i=0;i<256;i=i+17)
		{
			y=pDoc->m_MinValue + ((double)i)*(pDoc->m_MaxValue - pDoc->m_MinValue)/255.0;
			label.Format("%0.2f",y);
			pDC->TextOut(x1+w+(5+55)*pscale,y1+(22+(255-i))*pscale,label);
			CPen pen;
			pen.CreatePen(PS_SOLID ,1,RGBt[i]);
			pDC->SelectObject(&pen);
			pDC->MoveTo(x1+5*pscale+w,y1+(30+(255-i))*pscale);
			pDC->LineTo(x1+w+(5+10)*pscale,y1+(30+(255-i))*pscale);
		}
	}
	pDC->SelectObject(def_font);
	font.DeleteObject(); 
}

void CPro_HATA_NetFView::AreaShow(CDC* pDC) 
{
	CPro_HATA_NetFDoc *pDoc =(CPro_HATA_NetFDoc *) GetDocument();
	double AreaCovered = (double)m_CoveredPix/(double)(pDoc->Width * pDoc->Height );
	AreaCovered = AreaCovered * pDoc->m_AreaTotal;

	int offset = 1200;
	int x1,y1,pscale=1;
	CRect rect01;
	if (pDC->IsPrinting())
	{
		pscale=12;
		offset = 100*pscale;
		rect01=m_rcPrintRect;
		x1=rect01.left+offset;
	}
	else
	{
		pscale=1;
		offset = 12*pscale;
		GetClientRect(&rect01);
		x1=0;
	}
	y1=rect01.bottom-rect01.top-offset;

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

	CString str;
	str.Format(_Z("Covered Area (km^2) : %0.9f"),AreaCovered );
	pDC->TextOut(x1,y1,str);

	pDC->SelectObject(def_font);
	font.DeleteObject(); 
}

void CPro_HATA_NetFView::OnSize(UINT nType, int cx, int cy) 
{
//	static int old_cx=1200,old_cy=1200;
	CView::OnSize(nType, cx, cy);
	if(cx && cy)
	{
		new_cx=cx;
		new_cy=cy;
	}	
}

void CPro_HATA_NetFView::OnToolsNormalize() 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();

	CNormalizeDLG xx;
	xx.m_MinValue2=pDoc->ErMin;
	xx.m_MaxValue2=pDoc->ErMax;
	xx.m_MinValue=pDoc->m_MinValue;
	xx.m_MaxValue=pDoc->m_MaxValue;

	if (xx.DoModal()==IDOK)
	{
		pDoc->m_MinValue=xx.m_MinValue;
		pDoc->m_MaxValue=xx.m_MaxValue;
		InvalidateRect(NULL,false);
	}		
}

void CPro_HATA_NetFView::OnShowLegend() 
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

void CPro_HATA_NetFView::OnUpdateShowLegend(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LegendFlag ? 1 : 0);
}

void CPro_HATA_NetFView::OnMouseMove(UINT nFlags, CPoint point) 
{
	///////////////////// StatusBAR/////////////////////////////////////
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();

	if (pDoc->m_ReadyDoc == 1)
	{
		CString string;
		CRect rect;
		GetClientRect(&rect);

		double lon=pDoc->HATAlon0 + (double)((point.x)*(pDoc->Width-1))*
						(pDoc->m_Resolution_x/(double)(pDoc->m_ZoomFactor))
						/((double)(rect.Width()-1));

		double lat=pDoc->HATAlat0 + (double)((rect.Height()-1 -point.y)*(pDoc->Height-1))*
						(pDoc->m_Resolution_x/(double)(pDoc->m_ZoomFactor))
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

		int ix =(int) (((double)(point.x * (pDoc->Width-1))) / ((double)(rect.Width()-1)));
		int jy =(int) (((double)((rect.Height()-1 - point.y) * (pDoc->Height-1))) / ((double)(rect.Height()-1)));
		_int16 z=pDoc->bufArea[ix+jy*pDoc->Width];
		string.Format("Alt(m) : %d",z );
	   ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(3, string);

		double E=pDoc->Er[ix+jy*pDoc->Width];
		string.Format("E(dBuV/m) : %0.6f",E );
	   ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(5, string);
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

void CPro_HATA_NetFView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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

void CPro_HATA_NetFView::OnToolsContour() 
{
	CPro_HATA_NetFDoc *pDoc =(CPro_HATA_NetFDoc *) GetDocument();
	CContourDLG cdlg;
	cdlg.m_min = pDoc->m_MinValue;
	cdlg.m_max = pDoc->m_MaxValue;
	cdlg.m_step = double((int(1000.0*(pDoc->m_MaxValue - pDoc->m_MinValue)/pDoc->m_level))/1000.0);
	cdlg.m_nL = pDoc->m_level;
	if(cdlg.DoModal()==IDOK)
	{
		pDoc->m_level = cdlg.m_nL;
		Invalidate();
	}	
}

void CPro_HATA_NetFView::OnToolsCoveragearea() 
{
	CPro_HATA_NetFDoc *pDoc =(CPro_HATA_NetFDoc *) GetDocument();
/*
	pDoc->m_bThreshold = (pDoc->m_bThreshold ? false : true);
	if (pDoc->m_bThreshold)
	{
		CCoverageDLG vdlg;
		vdlg.m_thr = pDoc->m_Threshold;
		vdlg.m_min = pDoc->ErMin;
		vdlg.m_max = pDoc->ErMax;
		if(vdlg.DoModal()==IDOK)
		{
			pDoc->m_Threshold = vdlg.m_thr;
		}
		else
			pDoc->m_bThreshold = false;
	}
	Invalidate();
*/
	if (!(pDoc->m_bThreshold))
	{
		CCoverageDLG vdlg;
		vdlg.m_thr = pDoc->m_Threshold;
		vdlg.m_min = pDoc->ErMin;
		vdlg.m_max = pDoc->ErMax;
		if(vdlg.DoModal()==IDOK)
		{
			pDoc->m_Threshold = vdlg.m_thr;
			pDoc->m_bThreshold = true;
		}
	}
	else
		pDoc->m_bThreshold = false;
	Invalidate();
}

void CPro_HATA_NetFView::OnUpdateToolsCoveragearea(CCmdUI* pCmdUI) 
{
	CPro_HATA_NetFDoc *pDoc =(CPro_HATA_NetFDoc *) GetDocument();
	pCmdUI->SetCheck(pDoc->m_bThreshold);
}

void CPro_HATA_NetFView::OnTopo0() 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	if(pDoc->colormaptype != "Topo_0")
	{
		pDoc->colormaptype="Topo_0";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}
void CPro_HATA_NetFView::OnUpdateTopo0(CCmdUI* pCmdUI) 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Topo_0" ? 1 : 0);
}

void CPro_HATA_NetFView::OnTopo1() 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	if(pDoc->colormaptype != "Topo_1")
	{
		pDoc->colormaptype="Topo_1";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}
void CPro_HATA_NetFView::OnUpdateTopo1(CCmdUI* pCmdUI) 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Topo_1" ? 1 : 0);
}

void CPro_HATA_NetFView::OnJet() 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	if(pDoc->colormaptype != "Jet")
	{
		pDoc->colormaptype="Jet";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}
void CPro_HATA_NetFView::OnUpdateJet(CCmdUI* pCmdUI) 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Jet" ? 1 : 0);
}

void CPro_HATA_NetFView::OnGray() 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	if(pDoc->colormaptype != "Gray")
	{
		pDoc->colormaptype="Gray";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}
void CPro_HATA_NetFView::OnUpdateGray(CCmdUI* pCmdUI) 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Gray" ? 1 : 0);
}

void CPro_HATA_NetFView::OnPink() 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	if(pDoc->colormaptype != "Pink")
	{
		pDoc->colormaptype="Pink";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}
void CPro_HATA_NetFView::OnUpdatePink(CCmdUI* pCmdUI) 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Pink" ? 1 : 0);
}

void CPro_HATA_NetFView::OnCopper() 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	if(pDoc->colormaptype != "Copper")
	{
		pDoc->colormaptype="Copper";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}
void CPro_HATA_NetFView::OnUpdateCopper(CCmdUI* pCmdUI) 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Copper" ? 1 : 0);
}

void CPro_HATA_NetFView::OnGlobe() 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	if(pDoc->colormaptype != "Globe")
	{
		pDoc->colormaptype="Globe";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}
void CPro_HATA_NetFView::OnUpdateGlobe(CCmdUI* pCmdUI) 
{
	CPro_HATA_NetFDoc* pDoc = (CPro_HATA_NetFDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Globe" ? 1 : 0);
}

void CPro_HATA_NetFView::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CPro_HATA_NetFView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed=false;
	m_bLSelect=false;
	CView::OnLButtonUp(nFlags, point);
}

BOOL CPro_HATA_NetFView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CPro_HATA_NetFView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CPro_HATA_NetFView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
void CPro_HATA_NetFView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
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

void CPro_HATA_NetFView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}

void CPro_HATA_NetFView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////Google Earth//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CPro_HATA_NetFView::CaptureDC()
{
	CPro_HATA_NetFDoc *pDoc =(CPro_HATA_NetFDoc *) GetDocument();
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

		double lonW = pDoc->HATAlon0;
		double lonE = pDoc->HATAlon0 + (double)(pDoc->Width -1)*( pDoc->m_Resolution_x / (double)(pDoc->m_ZoomFactor));
		double latS = pDoc->HATAlat0;
		double latN = pDoc->HATAlat0 + (double)(pDoc->Height-1)*( pDoc->m_Resolution_x / (double)(pDoc->m_ZoomFactor));
		FILE *fp2 = fopen(fileOUTkml,_T("wt"));
		CString str1,str2,str3,str4;

		str1.Format(_T("<Folder><name>SMS4DC :</name><open>1</open>"));
		str2.Format(_T("<GroundOverlay><name>%s</name><Icon>%s</Icon><LatLonBox>"),filename, filename + _T(".bmp"));
		str3.Format(_T("<west>%lf</west><east>%lf</east><south>%lf</south><north>%lf</north></LatLonBox></GroundOverlay>"),lonW,lonE,latS,latN);
		
		str4 = _T("");
		CString str0;
		for(int i=0;i<pDoc->Nrow;i++)
		{
double HATAlon_ST = ((CSMS4DCApp *)AfxGetApp())->ReverseLon(pDoc->HATAlon_ST[i]);

//			str0.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),pDoc->HATAName_ST[i],gifFile ,pDoc->HATAlon_ST[i],pDoc->HATAlat_ST[i]);
			str0.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),pDoc->HATAName_ST[i],gifFile ,      HATAlon_ST   ,pDoc->HATAlat_ST[i]);
			str4 = str4 + str0;
		}
		fprintf(fp2,_T("<kml> %s %s %s %s </Folder></kml>"),str1,str2,str3,str4);
		fclose(fp2);

		if(flagShow)	ShellExecute(m_hWnd, "open", fileOUTkml, NULL, NULL, SW_SHOWNORMAL);
	}
}
void CPro_HATA_NetFView::OnToolsGoogle() 
{
	CaptureDC();
}

void CPro_HATA_NetFView::OnFileSaveAs() 
{
	OnFileSave();	
}
void CPro_HATA_NetFView::OnFileSave() 
{
	CPro_HATA_NetFDoc *pDoc =(CPro_HATA_NetFDoc *) GetDocument();
	CString str = pDoc->GetTitle();

	CDC *pDC = GetDC();
	((CSMS4DCApp *)AfxGetApp())->SaveDesktop(pDC, str);
	ReleaseDC(pDC);
}

void CPro_HATA_NetFView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "Maximum Field Strength (HATA)";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE32);
}

BOOL CPro_HATA_NetFView::OnEraseBkgnd(CDC* pDC) 	//98/01/25
{
	return true;
//	return CView::OnEraseBkgnd(pDC);
}
