// Int_BC2BC_FreeView.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Int_BC2BC_FreeView.h"

#include "Int_BC2BC_FreeDoc.h"
#include "UTM.h"
#include "MainFrm.h"
#include "NormalizeDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInt_BC2BC_FreeView

IMPLEMENT_DYNCREATE(CInt_BC2BC_FreeView, CView)

CInt_BC2BC_FreeView::CInt_BC2BC_FreeView()
{
	old_cx=old_cy=600;
	new_cx=new_cy=600;
//	m_pLegendDLGModeless=NULL; 
	m_LegendFlag=false;

	m_bLPressed=false;
	m_bLSelect=false;

	m_POLYnum=0;

	m_EuFlag = FALSE;
}

CInt_BC2BC_FreeView::~CInt_BC2BC_FreeView()
{
}


BEGIN_MESSAGE_MAP(CInt_BC2BC_FreeView, CView)
	//{{AFX_MSG_MAP(CInt_BC2BC_FreeView)
	ON_WM_SIZE()
	ON_COMMAND(ID_Jet, OnJet)
	ON_UPDATE_COMMAND_UI(ID_Jet, OnUpdateJet)
	ON_COMMAND(ID_Topo_1, OnTopo1)
	ON_UPDATE_COMMAND_UI(ID_Topo_1, OnUpdateTopo1)
	ON_COMMAND(ID_Topo_0, OnTopo0)
	ON_UPDATE_COMMAND_UI(ID_Topo_0, OnUpdateTopo0)
	ON_COMMAND(ID_Gray, OnGray)
	ON_UPDATE_COMMAND_UI(ID_Gray, OnUpdateGray)
	ON_COMMAND(ID_Pink, OnPink)
	ON_UPDATE_COMMAND_UI(ID_Pink, OnUpdatePink)
	ON_COMMAND(ID_Copper, OnCopper)
	ON_UPDATE_COMMAND_UI(ID_Copper, OnUpdateCopper)
	ON_COMMAND(ID_Globe, OnGlobe)
	ON_UPDATE_COMMAND_UI(ID_Globe, OnUpdateGlobe)
	ON_COMMAND(ID_SHOW_LEGEND, OnShowLegend)
	ON_UPDATE_COMMAND_UI(ID_SHOW_LEGEND, OnUpdateShowLegend)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TOOLS_EU, OnToolsEu)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_EU, OnUpdateToolsEu)
	ON_COMMAND(ID_TOOLS_NORMALIZE, OnToolsNormalize)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_NORMALIZE, OnUpdateToolsNormalize)
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
// CInt_BC2BC_FreeView drawing

#include "memdc.h"
void CInt_BC2BC_FreeView::OnDraw(CDC* pDC)	//98/01/25
{
	CMemDC mDC(pDC);
	OnDraw4(mDC);
}
void CInt_BC2BC_FreeView::OnDraw4(CDC* pDC)	//98/01/25
{
	CInt_BC2BC_FreeDoc *pDoc =(CInt_BC2BC_FreeDoc *) GetDocument();
	
	if(pDoc->m_ReadyDoc ==1)
	{
		pDC->SetStretchBltMode(COLORONCOLOR);	//98/01/25
	////////////////////////////////////////
		BYTE *temp2 , *Display=(BYTE *)malloc(pDoc->Width * pDoc->Height * sizeof(BYTE)); 
		double *temp = (double *)pDoc->Er;
		temp2=Display;

		double m_MinValue1 = max(pDoc->ErMin,pDoc->m_MinValue);
		double m_MaxValue1 = min(pDoc->ErMax,pDoc->m_MaxValue);
		m_CoveredPix = 0;
		for (int i=0;i<pDoc->Width;i++)
			for (int j=0;j<pDoc->Height;j++)
				{
			//		if((*temp)!=pDoc->m_NoData)		//98/01/19
			//		{
						if (m_MaxValue1 == m_MinValue1)		*temp2=0;
						else
						{
							if (pDoc->m_bThreshold)
							{
								if (min(max((*temp),m_MinValue1),m_MaxValue1) >= pDoc->m_Threshold)
								{	
									*temp2 = 159;
									m_CoveredPix = m_CoveredPix +1;
								}
								else				*temp2 = 0;
							}
							else
								*temp2 = Contour( min(max((*temp),m_MinValue1),m_MaxValue1) ,m_MinValue1,m_MaxValue1,pDoc->m_level);
							//	*temp2=(BYTE )(( min(max((*temp),m_MinValue1),m_MaxValue1) - m_MinValue1) * 255 / (m_MaxValue1- m_MinValue1));
						}
			//		}
			//		else		*temp2=255;


					if     ((*temp)<=m_MinValue1)	*temp2=0;
			//		else if((*temp)>=m_MaxValue1)	*temp2=254;		//98/01/19

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
		/*			//98/01/19
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
				m_x1 = x1;	m_y1 = y1;	m_x2 = x2;	m_y2 = y2;
			}
			else
			{
				x1=0;		y1=0;
				x2=new_cx;	y2=new_cy;
				m_x1 = x1;	m_y1 = y1;	m_x2 = x2;	m_y2 = y2;
			}
			///////////////////////////////////////
			pDC->StretchBlt(x1,y1,x2,y2,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);

			DeleteDC(MemDC.m_hDC);
			MemDC.Detach();
			old_cx=cxDib;
			old_cy=cyDib;

		}
		free (pbmfh) ;		free(Display);
	////////////////////////////////////////
//		if (pDoc->m_bThreshold)
//			AreaShow(pDC);
//		
		if ((m_LegendFlag)&&(m_EuFlag))			LegendLOCEu(pDC);
		else if ((m_LegendFlag)&&(!m_EuFlag))	LegendLOC(pDC);

	}
}

/////////////////////////////////////////////////////////////////////////////
// CInt_BC2BC_FreeView diagnostics

#ifdef _DEBUG
void CInt_BC2BC_FreeView::AssertValid() const
{
	CView::AssertValid();
}

void CInt_BC2BC_FreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInt_BC2BC_FreeView message handlers

int CInt_BC2BC_FreeView::Contour(double y,double MinV,double MaxV,int nL) 
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

void CInt_BC2BC_FreeView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if(cx && cy)
	{
		new_cx=cx;
		new_cy=cy;
	}	
}

void CInt_BC2BC_FreeView::OnTopo0() 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	if(pDoc->colormaptype != "Topo_0")
	{
		pDoc->colormaptype="Topo_0";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CInt_BC2BC_FreeView::OnUpdateTopo0(CCmdUI* pCmdUI) 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Topo_0" ? 1 : 0);
}

void CInt_BC2BC_FreeView::OnTopo1() 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	if(pDoc->colormaptype != "Topo_1")
	{
		pDoc->colormaptype="Topo_1";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
}

void CInt_BC2BC_FreeView::OnUpdateTopo1(CCmdUI* pCmdUI) 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Topo_1" ? 1 : 0);
}

void CInt_BC2BC_FreeView::OnJet() 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	if(pDoc->colormaptype != "Jet")
	{
		pDoc->colormaptype="Jet";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}
	
}
void CInt_BC2BC_FreeView::OnUpdateJet(CCmdUI* pCmdUI) 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Jet" ? 1 : 0);
}

void CInt_BC2BC_FreeView::OnGray() 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	if(pDoc->colormaptype != "Gray")
	{
		pDoc->colormaptype="Gray";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}	
}

void CInt_BC2BC_FreeView::OnUpdateGray(CCmdUI* pCmdUI) 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Gray" ? 1 : 0);
}

void CInt_BC2BC_FreeView::OnPink() 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	if(pDoc->colormaptype != "Pink")
	{
		pDoc->colormaptype="Pink";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}		
}

void CInt_BC2BC_FreeView::OnUpdatePink(CCmdUI* pCmdUI) 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Pink" ? 1 : 0);
}

void CInt_BC2BC_FreeView::OnCopper() 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	if(pDoc->colormaptype != "Copper")
	{
		pDoc->colormaptype="Copper";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}		
}

void CInt_BC2BC_FreeView::OnUpdateCopper(CCmdUI* pCmdUI) 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Copper" ? 1 : 0);
}

void CInt_BC2BC_FreeView::OnGlobe() 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	if(pDoc->colormaptype != "Globe")
	{
		pDoc->colormaptype="Globe";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		InvalidateRect(NULL,false);
	}		
}

void CInt_BC2BC_FreeView::OnUpdateGlobe(CCmdUI* pCmdUI) 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Globe" ? 1 : 0);
}

void CInt_BC2BC_FreeView::OnShowLegend() 
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

void CInt_BC2BC_FreeView::OnUpdateShowLegend(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_LegendFlag ? 1 : 0);
}


void CInt_BC2BC_FreeView::LegendLOCEu(CDC* pDC) 
{
	CInt_BC2BC_FreeDoc *pDoc =(CInt_BC2BC_FreeDoc *) GetDocument();
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
	//		RGBt[i]=m_tile.RGBt[ 0+(1-i)*159 ];
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

	pDC->TextOut(x1+5*pscale,y1+5*pscale,_T("E (dBuV/m)"));
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



void CInt_BC2BC_FreeView::LegendLOC(CDC* pDC) 
{
	CInt_BC2BC_FreeDoc *pDoc =(CInt_BC2BC_FreeDoc *) GetDocument();
	int x1,y1,x2,y2,w=10,pscale=12,Nrow=pDoc->Nrow;

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

	int tt=int(255.0/2.0),		tt1=int(255.0/(2.0+1));

	RGBt[0] = RGB(127,127,127);						//98/01/19
	RGBt[1] = m_tile.RGBt[tt];
	RGBt[2] = m_tile.RGBt[tt*2];

	for (int i=0;i<=2;i++)
	{
//		RGBt[i]=m_tile.RGBt[ tt*(i) ];
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

	pDC->TextOut(x1+5*pscale,y1+5*pscale,_Z("Coverage"));
	pDC->SetTextAlign(TA_LEFT);

	label.Format("%s",_Z("Considering"));
	pDC->TextOut(x1+w+(5+5)*pscale,y1+(22+(tt1/2))*pscale,label);
	label.Format("%s",_Z("Interferer(s)"));
	pDC->TextOut(x1+w+(5+5)*pscale,y1+(22+(tt1/2+3*tt1/20))*pscale,label);
	
	label.Format("%s",_Z("Without"));
	pDC->TextOut(x1+w+(5+5)*pscale,y1+(22+(3*tt1/2-3*tt1/20))*pscale,label);
	label.Format("%s",_Z("Considering"));
	pDC->TextOut(x1+w+(5+5)*pscale,y1+(22+(3*tt1/2+0*tt1/20))*pscale,label);
	label.Format("%s",_Z("Interferer(s)"));
	pDC->TextOut(x1+w+(5+5)*pscale,y1+(22+(3*tt1/2+3*tt1/20))*pscale,label);

	label.Format("%s",_Z("Not Covered"));
	pDC->TextOut(x1+w+(5+5)*pscale,y1+(22+(255-tt1/2))*pscale,label);

	pDC->SelectObject(def_font);
	font.DeleteObject(); 
}

void CInt_BC2BC_FreeView::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CInt_BC2BC_FreeView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLPressed=false;
	m_bLSelect=false;
	
	CView::OnLButtonUp(nFlags, point);
}

void CInt_BC2BC_FreeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	///////////////////// StatusBAR/////////////////////////////////////
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();

	if (pDoc->m_ReadyDoc == 1)
	{
		CString string;
		CRect rect;
		GetClientRect(&rect);

		double lon=pDoc->Freelon0 + (double)((point.x)*(pDoc->Width-1))*
						(pDoc->m_Resolution_x/(double)(pDoc->m_ZoomFactor))
						/((double)(rect.Width()-1));

		double lat=pDoc->Freelat0 + (double)((rect.Height()-1 -point.y)*(pDoc->Height-1))*
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

		if(!m_EuFlag)
		{
			if     (E==2)	string.Format(_Z("Coverage : with interferer"));
			else if(E==0)	string.Format(_Z("Coverage : not covered"));
			else if(E==1)	string.Format(_Z("Coverage : without interferer"));
		}
		else
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

void CInt_BC2BC_FreeView::DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) 
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

//98/01/19
int CInt_BC2BC_FreeView::Round(double x) 
{
	int y;
	int x1 = (int)x;
	if(x>=0)	{int x2 = x1+1;		y = ( (x > ((double)x1)+0.45) ? x2 : x1);}
	else		{int x2 = x1-1;		y = ( (x > ((double)x2)+0.45) ? x1 : x2);}
	return y;
}
void CInt_BC2BC_FreeView::OnToolsEu() 
{
	m_EuFlag = !m_EuFlag;
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();
	int i,j;

	if(m_EuFlag)
	{
		for( i=0;i<pDoc->Width;i++)
			for( j=0;j<pDoc->Height;j++)
				pDoc->Er[i+(pDoc->Width)*j] = pDoc->ErU[i+(pDoc->Width)*j];

		pDoc->ErMin = pDoc->ErUMin;
		pDoc->ErMax = pDoc->ErUMax;

		if(pDoc->ErUMax>pDoc->ErUMin)	//98/01/19
		{
			pDoc->m_MinValue = (double)Round(pDoc->ErUMin)+1.0;
			pDoc->m_MaxValue = (double)Round(pDoc->ErUMax)-1.0;
		}
		else
		{
			pDoc->m_MinValue = pDoc->ErUMin;
			pDoc->m_MaxValue = pDoc->ErUMax;
		}
	}
	else
	{
		for( i=0;i<pDoc->Width;i++)
			for( j=0;j<pDoc->Height;j++)
				pDoc->Er[i+(pDoc->Width)*j] = pDoc->ErC[i+(pDoc->Width)*j];

		pDoc->ErMin = pDoc->ErCMin;
		pDoc->ErMax = pDoc->ErCMax;
		pDoc->m_MinValue = pDoc->ErCMin;
		pDoc->m_MaxValue = pDoc->ErCMax;
	}

	InvalidateRect(NULL,false);
	
}
void CInt_BC2BC_FreeView::OnUpdateToolsEu(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_EuFlag);
}

void CInt_BC2BC_FreeView::OnToolsNormalize() 
{
	CInt_BC2BC_FreeDoc* pDoc = (CInt_BC2BC_FreeDoc*)GetDocument();

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
void CInt_BC2BC_FreeView::OnUpdateToolsNormalize(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_EuFlag);	
}


BOOL CInt_BC2BC_FreeView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CInt_BC2BC_FreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CInt_BC2BC_FreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
void CInt_BC2BC_FreeView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
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

void CInt_BC2BC_FreeView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CView::OnFilePrintPreview();
}
void CInt_BC2BC_FreeView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();

}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////Google Earth//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CInt_BC2BC_FreeView::CaptureDC()
{
	CInt_BC2BC_FreeDoc *pDoc =(CInt_BC2BC_FreeDoc *) GetDocument();
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

		double lonW = pDoc->Freelon0;
		double lonE = pDoc->Freelon0 + (double)(pDoc->Width -1)*( pDoc->m_Resolution_x / (double)(pDoc->m_ZoomFactor));
		double latS = pDoc->Freelat0;
		double latN = pDoc->Freelat0 + (double)(pDoc->Height-1)*( pDoc->m_Resolution_x / (double)(pDoc->m_ZoomFactor));
		FILE *fp2 = fopen(fileOUTkml,_T("wt"));
		CString str1,str2,str3,str4;

		str1.Format(_T("<Folder><name>SMS4DC :</name><open>1</open>"));
		str2.Format(_T("<GroundOverlay><name>%s</name><Icon>%s</Icon><LatLonBox>"),filename, filename + _T(".bmp"));
		str3.Format(_T("<west>%lf</west><east>%lf</east><south>%lf</south><north>%lf</north></LatLonBox></GroundOverlay>"),lonW,lonE,latS,latN);
		str4.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),pDoc->FreeName_ST,gifFile ,pDoc->Freelon_ST,pDoc->Freelat_ST);

		CString str0;
		for(int i=0;i<pDoc->Nrow;i++)
		{
			str0.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),pDoc->m_nameY[i],gifFile ,pDoc->m_lonY[i],pDoc->m_latY[i]);
			str4 = str4 + str0;
		}
		fprintf(fp2,_T("<kml> %s %s %s %s </Folder></kml>"),str1,str2,str3,str4);
		fclose(fp2);

		if(flagShow)	ShellExecute(m_hWnd, "open", fileOUTkml, NULL, NULL, SW_SHOWNORMAL);
	}
}

void CInt_BC2BC_FreeView::OnToolsGoogle() 
{
	CaptureDC();
}

void CInt_BC2BC_FreeView::OnFileSaveAs() 
{
	OnFileSave();	
}
void CInt_BC2BC_FreeView::OnFileSave() 
{
	CInt_BC2BC_FreeDoc *pDoc =(CInt_BC2BC_FreeDoc *) GetDocument();
	CString str = pDoc->GetTitle();

	CDC *pDC = GetDC();
	((CSMS4DCApp *)AfxGetApp())->SaveDesktop(pDC, str);
	ReleaseDC(pDC);
}

void CInt_BC2BC_FreeView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "InterferenceBC2BC (Free Space)";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE42);
}

BOOL CInt_BC2BC_FreeView::OnEraseBkgnd(CDC* pDC) 	//98/01/25
{
	return true;
//	return CView::OnEraseBkgnd(pDC);
}
