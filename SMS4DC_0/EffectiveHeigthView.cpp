// EffectiveHeigthView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "EffectiveHeigthView.h"
#include "EffectiveHeigthDoc.h"
#include "UTM.h"
#include "MainFrm.h"

#include "EffectiveHeigthSet.h"

#include <math.h>
#include "HeffDLG.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthView

IMPLEMENT_DYNCREATE(CEffectiveHeigthView, CView)

CEffectiveHeigthView::CEffectiveHeigthView()
{
	m_TextColor=RGB(0,0,0);
	m_LineColor=RGB(0,0,255);
	m_background = false;
	m_printstate=false;

	m_step = 5;
	m_num = 360/m_step + 1;
	m_Heff_m = new double[m_num]; 

}

CEffectiveHeigthView::~CEffectiveHeigthView()
{
	delete [] m_Heff_m;
}


BEGIN_MESSAGE_MAP(CEffectiveHeigthView, CView)
	//{{AFX_MSG_MAP(CEffectiveHeigthView)
	ON_COMMAND(ID_TOOLS_TEXTCOLOR, OnToolsTextcolor)
	ON_COMMAND(ID_TOOLS_LINECOLOR, OnToolsLinecolor)
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
	ON_COMMAND(ID_TOOLS_BACKGROUND, OnToolsBackground)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BACKGROUND, OnUpdateToolsBackground)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_TOOLS_SAVEEFFECTIVEHEIGHT, OnToolsSaveeffectiveheight)
	ON_COMMAND(ID_HEFFDATA_SAVEHEFF, OnHeffdataSaveheff)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SAVEEFFECTIVEHEIGHT, OnUpdateToolsSaveeffectiveheight)
	ON_UPDATE_COMMAND_UI(ID_HEFFDATA_SAVEHEFF, OnUpdateHeffdataSaveheff)
	ON_COMMAND(ID_TOOLS_TXT, OnToolsTxt)
	ON_COMMAND(ID_HEFFDATA_TXT, OnHeffdataTxt)
	ON_COMMAND(ID_TOOLS_EDITDATABASE, OnToolsEditdatabase)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthView drawing

void CEffectiveHeigthView::OnFilePrintPreview()
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	m_printstate = true;
	CView::OnFilePrintPreview();
}
void CEffectiveHeigthView::OnFilePrint()
{
	m_printstate = false;
	CView::OnFilePrint();
}

void CEffectiveHeigthView::OnDraw(CDC* pDC)
{
	CEffectiveHeigthDoc *pDoc =(CEffectiveHeigthDoc *) GetDocument();
	if(pDoc->m_bflag==1)
	{
		if(pDoc->m_ReadyDoc ==1)
		{
			CRect rect,rect1;
		///////////////////////////////////////
			if (pDC->IsPrinting())		rect1 = m_rcPrintRect;
			else						GetClientRect(&rect1);
			int AxesW1=(int)((rect1.Width()));
			int AxesH1=(int)((rect1.Height()));
			int AxesT1=(int)(rect1.top );
			int AxesL1=(int)(rect1.left );
			pDC->DPtoLP(&rect1);

	//		pDC->SetMapMode(MM_LOMETRIC);
			pDC->SetMapMode(MM_TEXT);
		///////////////////////////////////////
			if (pDC->IsPrinting())		rect = m_rcPrintRect;
			else						GetClientRect(&rect);
			pDC->DPtoLP(&rect);
		///////////////////////////////////////
			int AxesW=(int)((rect.Width()));
			int AxesH=(int)((rect.Height()));
			int AxesT=(int)(rect.top );
			int AxesL=(int)(rect.left );

			m_AxesW = (0.9)*AxesW;
			m_AxesH = (0.9)*AxesH;
			m_AxesT = AxesT + (AxesH - m_AxesH)/2 ;
			m_AxesL = AxesL + (AxesW - m_AxesW)/2;
			pDC->Rectangle(AxesL+(0.025)*AxesW,AxesT+(0.025)*AxesH,(0.975)*AxesW,(0.975)*AxesH);

			if(m_background)
			{
				pDC->SetStretchBltMode(COLORONCOLOR);
				_int16 m_MinValue1 = (pDoc->bufMin);
				_int16 m_MaxValue1 = (pDoc->bufMax);
				////////////////////////////////////////
				BYTE *temp2 , *Display=(BYTE *)malloc(pDoc->Width * pDoc->Height * sizeof(BYTE)); 
				_int16 *temp = (_int16 *)pDoc->bufArea;
				temp2 = Display;

				for (int i=0;i<pDoc->Width;i++)
					for (int j=0;j<pDoc->Height;j++)
					{
						if((*temp)!=pDoc->m_NoData)
						{
							if (pDoc->bufMax == pDoc->bufMin)	*temp2 = 0;
							else		*temp2 = ( min(max((*temp),m_MinValue1),m_MaxValue1) - m_MinValue1) * 255 / (m_MaxValue1- m_MinValue1);
						//	else		*temp2 = ((*temp) - pDoc->bufMin) * 255 / (pDoc->bufMax- pDoc->bufMin);
						}
						else			*temp2 = 255;

						if     ((*temp)<=m_MinValue1)			*temp2 = 0;		//98/01/31
						else if((*temp)>=m_MaxValue1)			*temp2 = 254;	//98/01/31

						temp2++;	temp++;
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
					///////////////////////////////////////////////////////////////////
					/*
					double ratW,ratH;
					if(m_printstate)
					{
						ratW = 1.33*(double)(cxDib * AxesW1)/(double)(AxesW);
						ratH = 1.33*(double)(cyDib * AxesH1)/(double)(AxesH);
					}
					else
					{
						ratW = (double)(cxDib * AxesW)/(double)(AxesW1);
						ratH = (double)(cyDib * AxesH)/(double)(AxesH1);
					}
					pDC->StretchBlt(m_AxesL,m_AxesT,m_AxesW,m_AxesH,&MemDC ,0.0, 0.0, ratW, ratH, SRCCOPY);
					*/
					pDC->StretchBlt(m_AxesL,m_AxesT,m_AxesW,m_AxesH,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);
					///////////////////////////////////////////////////////////////////
			//		pDC->StretchBlt(0,0,new_cx,new_cy,&MemDC ,0,0,pDoc->Width , pDoc->Height,SRCCOPY);
					DeleteDC(MemDC.m_hDC);
					MemDC.Detach();
				}
				free (pbmfh);		free(Display);
			}
		/////////////////// Station ////////////////////////
			CPoint m_Point_ST,m_Point_ST1;
			LatLon2Point(pDoc->lat_ST,pDoc->lon_ST, &m_Point_ST) ;
			Point2Stretch( m_Point_ST,&m_Point_ST1);

			double latC,lonC;
		/////////////////////////////Circle 3km, 15km////////////////////////////////////
			CPoint *m_Point_STcr3;			m_Point_STcr3=new CPoint[m_num];
			CPoint *m_Point_STcr31;			m_Point_STcr31=new CPoint[m_num];
			CPoint *m_Point_STcr15;			m_Point_STcr15=new CPoint[m_num];
			CPoint *m_Point_STcr151;		m_Point_STcr151=new CPoint[m_num];
			for (int i=0;i<m_num;i++)
			{
				reckon( pDoc->lat_ST,pDoc->lon_ST, 3.0 , i*m_step , &latC , &lonC) ;
				LatLon2Point(latC,lonC, &m_Point_STcr3[i]) ;
				Point2Stretch( m_Point_STcr3[i],&m_Point_STcr31[i]);

				reckon( pDoc->lat_ST,pDoc->lon_ST, 15.0 , i*m_step , &latC , &lonC) ;
				LatLon2Point(latC,lonC, &m_Point_STcr15[i]) ;
				Point2Stretch( m_Point_STcr15[i],&m_Point_STcr151[i]);
			}
			pDC->Polyline(m_Point_STcr31,m_num);
			pDC->Polyline(m_Point_STcr151,m_num);
		/////////////////////////////Circle 15km////////////////////////////////////
			CPen pen1;
			pen1.CreatePen(PS_SOLID,1,m_LineColor);
			pDC->SelectObject(&pen1);
			for (i=0;i<m_num;i++)
			{
				pDC->MoveTo(m_Point_STcr31[i]);
				pDC->LineTo(m_Point_STcr151[i]);
			}
		/////////////////////////////Circle 20km////////////////////////////////////
			CPen pen2;
			pen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
			pDC->SelectObject(&pen2);

			CPoint *m_Point_STcr20;			m_Point_STcr20=new CPoint[m_num];
			CPoint *m_Point_STcr201;		m_Point_STcr201=new CPoint[m_num];

	//		double Hg = Point2Hg(m_Point_ST);
			double Hg = pDoc->m_Hasl;
			for ( i=0;i<m_num;i++)
			{
				reckon( pDoc->lat_ST,pDoc->lon_ST, 20.0 , i*m_step , &latC , &lonC) ;
				LatLon2Point(latC,lonC, &m_Point_STcr20[i]) ;
				Point2Stretch( m_Point_STcr20[i],&m_Point_STcr201[i]);

			/////////////////////////////h1////////////////////////////////////
				m_Heff_m[i] = pDoc->m_Heff[i];
			//	m_Heff_m[i] = Hg+pDoc->Hagl_ST - Points2HgAvr(m_Point_STcr3[i] , m_Point_STcr15[i]) ;
			}
			pDC->Polyline(m_Point_STcr201,m_num);
			
		/////////////////////////////Circle 16km, 12km////////////////////////////////////
			CPoint *m_Point_STcr12;				m_Point_STcr12=new CPoint[m_num-1];
			CPoint *m_Point_STcr121;			m_Point_STcr121=new CPoint[m_num-1];

			CPoint *m_Point_STcr16;			m_Point_STcr16=new CPoint[m_num-1];
			CPoint *m_Point_STcr161;		m_Point_STcr161=new CPoint[m_num-1];
			CString deg, deg2;

			int scale = 1;
			if (pDC->IsPrinting())	scale = 16*max(m_AxesW,m_AxesH)/10000;

			for ( i=0;i<m_num-1;i++)
			{
				deg.Format("%d",i*m_step);
				reckon( pDoc->lat_ST,pDoc->lon_ST, 12.0 , i*m_step-1 , &latC , &lonC) ;
				LatLon2Point(latC,lonC, &m_Point_STcr12[i]) ;
				Point2Stretch( m_Point_STcr12[i],&m_Point_STcr121[i]);
		//		TextDraw(pDC,m_Point_STcr121[i].x,m_Point_STcr121[i].y,deg,m_TextColor,(270+i*m_step)*10,12+25, 0, FW_NORMAL,"Arial") ;
				TextDraw(pDC,m_Point_STcr121[i].x,m_Point_STcr121[i].y,deg,m_TextColor,(90-i*m_step)*10,12*scale, 6*scale, FW_NORMAL,"Arial") ;

				deg2.Format("%0.1f",m_Heff_m[i]);
				reckon( pDoc->lat_ST,pDoc->lon_ST, 16.5 , i*m_step-1 , &latC , &lonC) ;
				LatLon2Point(latC,lonC, &m_Point_STcr16[i]) ;
				Point2Stretch( m_Point_STcr16[i],&m_Point_STcr161[i]);
		//		TextDraw(pDC,m_Point_STcr161[i].x,m_Point_STcr161[i].y,deg2,m_TextColor, (270+i*m_step)*10, 12+25, 0, FW_BOLD,"Arial") ;
				TextDraw(pDC,m_Point_STcr161[i].x,m_Point_STcr161[i].y,deg2,m_TextColor, (90-i*m_step)*10, 12*scale, 6*scale, FW_BOLD,"Arial") ;

			}
	//		int len = 4+10;
			int len = 4*scale;
			CPen pen;
			pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
			pDC->SelectObject(&pen);
			pDC->Ellipse(m_Point_ST1.x-len,	m_Point_ST1.y-len, m_Point_ST1.x+len,	m_Point_ST1.y+len);
	//		deg.Format(" Effective Height --->   Station Name : %s   ( Height : %0.1f m ) ",pDoc->Name_ST,Hg);
			deg.Format(" "+_Z("Effective Height")+" --->   "+_Z("Station Name")+" : %s   ( "+_Z("Height")+" : %0.1f m ) ",pDoc->Name_ST,Hg);
			
			GetParent()->SetWindowText(deg);

			delete [] m_Point_STcr3;		delete [] m_Point_STcr31;
			delete [] m_Point_STcr15;		delete [] m_Point_STcr151;
			delete [] m_Point_STcr12;		delete [] m_Point_STcr121;
			delete [] m_Point_STcr20;		delete [] m_Point_STcr201;
			delete [] m_Point_STcr16;		delete [] m_Point_STcr161;
		}
	}//	if(pDoc->m_bflag==1)
	else
	{
		if(pDoc->m_ReadyDoc ==1)
		{

			CRect rect,rect1;
		///////////////////////////////////////
			if (pDC->IsPrinting())	rect1 = m_rcPrintRect;
			else					GetClientRect(&rect1);
			int AxesW1=(int)((rect1.Width()));
			int AxesH1=(int)((rect1.Height()));
			int AxesT1=(int)(rect1.top );
			int AxesL1=(int)(rect1.left );
			pDC->DPtoLP(&rect1);

			pDC->SetMapMode(MM_LOMETRIC);
		///////////////////////////////////////
			if (pDC->IsPrinting())	rect = m_rcPrintRect;
			else					GetClientRect(&rect);
			pDC->DPtoLP(&rect);
		///////////////////////////////////////
			int AxesW=(int)((rect.Width()));
			int AxesH=(int)((rect.Height()));
			int AxesT=(int)(rect.top );
			int AxesL=(int)(rect.left );

			m_AxesW = (0.9)*AxesW;
			m_AxesH = (0.9)*AxesH;
			m_AxesT = AxesT + (AxesH - m_AxesH)/2 ;
			m_AxesL = AxesL + (AxesW - m_AxesW)/2;
			pDC->Rectangle(AxesL+(0.025)*AxesW,AxesT+(0.025)*AxesH,(0.975)*AxesW,(0.975)*AxesH);

			CString deg, deg2;
			double Hg = pDoc->m_Hasl;
			double pi=4.0*atan(1.0);

		/////////////////// Station ////////////////////////
			CPoint m_Point_ST = CPoint(AxesW/2,AxesH/2);

			CPoint *m_Point_STcr3;			m_Point_STcr3=new CPoint[m_num];
			CPoint *m_Point_STcr15;			m_Point_STcr15=new CPoint[m_num];
			CPoint *m_Point_STcr16;			m_Point_STcr16=new CPoint[m_num];
			CPoint *m_Point_STcr12;			m_Point_STcr12=new CPoint[m_num];
			CPoint *m_Point_STcr20;			m_Point_STcr20=new CPoint[m_num];

			int t,  sc = 2  ,  d0 = min(abs(AxesW),abs(AxesH));

			int  r3  = ( 3*sc)*d0/100+10;
			int  r12 = (12*sc)*d0/100+10;
			int  r15 = (15*sc)*d0/100+10;
			int  r16 = (16.4*sc)*d0/100+10;
			int  r20 = (20*sc)*d0/100+10;
			for ( t=0;t<m_num;t++)
			{
				m_Point_STcr3[t].x = m_Point_ST.x + r3*sin(t*m_step*pi/180.0);
				m_Point_STcr3[t].y = m_Point_ST.y + r3*cos(t*m_step*pi/180.0);

				m_Point_STcr15[t].x = m_Point_ST.x + r15*sin(t*m_step*pi/180.0);
				m_Point_STcr15[t].y = m_Point_ST.y + r15*cos(t*m_step*pi/180.0);

				m_Point_STcr20[t].x = m_Point_ST.x + r20*sin(t*m_step*pi/180.0);
				m_Point_STcr20[t].y = m_Point_ST.y + r20*cos(t*m_step*pi/180.0);

			/////////////////////////////h1////////////////////////////////////
				m_Heff_m[t] = pDoc->m_Heff[t];
			}
			pDC->Polyline(m_Point_STcr3,m_num);
			pDC->Polyline(m_Point_STcr15,m_num);

			CPen pen1;
			pen1.CreatePen(PS_SOLID,1,m_LineColor);
			pDC->SelectObject(&pen1);
			for ( t=0;t<m_num-1;t++)
			{
				pDC->MoveTo(m_Point_STcr3[t]);
				pDC->LineTo(m_Point_STcr15[t]);
			}
		/////////////////////////////Circle 20km////////////////////////////////////
			CPen pen2;
			pen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
			pDC->SelectObject(&pen2);
			pDC->Polyline(m_Point_STcr20,m_num);

			for ( t=0;t<m_num-1;t++)
			{
				m_Point_STcr12[t].x = m_Point_ST.x + r12*sin(t*m_step*pi/180.0);
				m_Point_STcr12[t].y = m_Point_ST.y + r12*cos(t*m_step*pi/180.0);
				deg.Format("%d",t*m_step);
				TextDraw(pDC,m_Point_STcr12[t].x,m_Point_STcr12[t].y,deg,m_TextColor,(270+t*m_step)*10,12+25, 0, FW_NORMAL,"Arial") ;

				m_Point_STcr16[t].x = m_Point_ST.x + r16*sin(t*m_step*pi/180.0);
				m_Point_STcr16[t].y = m_Point_ST.y + r16*cos(t*m_step*pi/180.0);
				deg2.Format("%0.1f",m_Heff_m[t]);
				TextDraw(pDC,m_Point_STcr16[t].x,m_Point_STcr16[t].y,deg2,m_TextColor, (270+t*m_step)*10, 12+25, 0, FW_BOLD,"Arial") ;
			}
			delete [] m_Point_STcr3;
			delete [] m_Point_STcr12;
			delete [] m_Point_STcr15;
			delete [] m_Point_STcr16;
			delete [] m_Point_STcr20;

			int len = 4+10;
			CPen pen;
			pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
			pDC->SelectObject(&pen);
			pDC->Ellipse(m_Point_ST.x-len,	m_Point_ST.y-len, m_Point_ST.x+len,	m_Point_ST.y+len);
//			deg.Format(" Effective Height --->   Station Name : %s   ( Height : %0.1f m ) ",pDoc->Name_ST,Hg);
			deg.Format(" "+_Z("Effective Height")+" --->   "+_Z("Station Name")+" : %s   ( "+_Z("Height")+" : %0.1f m ) ",pDoc->Name_ST,Hg);
			GetParent()->SetWindowText(deg);
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthView diagnostics

#ifdef _DEBUG
void CEffectiveHeigthView::AssertValid() const
{
	CView::AssertValid();
}

void CEffectiveHeigthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthView message handlers

void CEffectiveHeigthView::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) 
{
	double pi=4.0*atan(1.0);
	float	lat_rad = (float)(lat_deg*pi/180.0),
			lon_rad = (float)(lon_deg*pi/180.0),
			RLON, RLAT,	 rng_km1 = (float)rng_km, az_deg1 = (float)az_deg;
	GEOPDAP( &lon_rad, &lat_rad, &rng_km1, &az_deg1, &RLON, &RLAT);
	*latC_deg = RLAT*180.0/pi;
	*lonC_deg = RLON*180.0/pi;
/*
	double pi=4.0*atan(1.0);
	double R=6371.0;

	double rng_rad=rng_km/R;
	double az_rad=az_deg*pi/180.0;
	double lat_rad=lat_deg*pi/180.0;
	double lon_rad=lon_deg*pi/180.0;

	double temp1  = sin(lat_rad)*cos(rng_rad);          
	double temp2  = cos(lat_rad)*sin(rng_rad)*cos(az_rad);
	double newlat = asin(temp1+temp2);

	temp1  = sin(rng_rad)*sin(az_rad);            
	temp2  = cos(lat_rad)*cos(rng_rad);
	double temp3  = sin(lat_rad)*sin(rng_rad)*cos(az_rad);
	double newlon = lon_rad + atan2(temp1,temp2-temp3);

	*latC_deg=newlat*180.0/pi;
	*lonC_deg=newlon*180.0/pi;
*/
}

void CEffectiveHeigthView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
							int Escapement,
							int nHeight,int nWidth,int FontWeight,CString FontName) 
{
	pDC->SetTextAlign(TA_CENTER | TA_BASELINE );
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

void CEffectiveHeigthView::OnToolsTextcolor() 
{
	CColorDialog xx(RGB(0, 0, 0), CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		m_TextColor=xx.GetColor();
		Invalidate();
	}
}

void CEffectiveHeigthView::OnToolsLinecolor() 
{
	CColorDialog xx(RGB(255, 255, 255), CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		m_LineColor=xx.GetColor();
		Invalidate();
	}
}

void CEffectiveHeigthView::OnTopo0() 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	if(pDoc->colormaptype != "Topo_0")
	{
		pDoc->colormaptype="Topo_0";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		Invalidate();
	}
}

void CEffectiveHeigthView::OnUpdateTopo0(CCmdUI* pCmdUI) 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Topo_0" ? 1 : 0);	
	pCmdUI->Enable(m_background);	
}

void CEffectiveHeigthView::OnTopo1() 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	if(pDoc->colormaptype != "Topo_1")
	{
		pDoc->colormaptype="Topo_1";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		Invalidate();
	}
}

void CEffectiveHeigthView::OnUpdateTopo1(CCmdUI* pCmdUI) 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Topo_1" ? 1 : 0);	
	pCmdUI->Enable(m_background);	
}

void CEffectiveHeigthView::OnJet() 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	if(pDoc->colormaptype != "Jet")
	{
		pDoc->colormaptype="Jet";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		Invalidate();
	}
}

void CEffectiveHeigthView::OnUpdateJet(CCmdUI* pCmdUI) 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Jet" ? 1 : 0);	
	pCmdUI->Enable(m_background);	
}

void CEffectiveHeigthView::OnGray() 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	if(pDoc->colormaptype != "Gray")
	{
		pDoc->colormaptype="Gray";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		Invalidate();
	}
}

void CEffectiveHeigthView::OnUpdateGray(CCmdUI* pCmdUI) 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Gray" ? 1 : 0);	
	pCmdUI->Enable(m_background);	
}

void CEffectiveHeigthView::OnPink() 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	if(pDoc->colormaptype != "Pink")
	{
		pDoc->colormaptype="Pink";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		Invalidate();
	}
}

void CEffectiveHeigthView::OnUpdatePink(CCmdUI* pCmdUI) 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Pink" ? 1 : 0);	
	pCmdUI->Enable(m_background);	
}

void CEffectiveHeigthView::OnCopper() 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	if(pDoc->colormaptype != "Copper")
	{
		pDoc->colormaptype="Copper";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		Invalidate();
	}
}

void CEffectiveHeigthView::OnUpdateCopper(CCmdUI* pCmdUI) 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Copper" ? 1 : 0);
	pCmdUI->Enable(m_background);	
}

void CEffectiveHeigthView::OnGlobe() 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	if(pDoc->colormaptype != "Globe")
	{
		pDoc->colormaptype="Globe";
		pDoc->m_tile.ColorMap(pDoc->colormaptype);
		for (int i=0;i<256;i++)
			pDoc->RGBt[i]=pDoc->m_tile.RGBt[i];
		Invalidate();
	}
}
void CEffectiveHeigthView::OnUpdateGlobe(CCmdUI* pCmdUI) 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	pCmdUI->SetCheck(pDoc->colormaptype=="Globe" ? 1 : 0);	
	pCmdUI->Enable(m_background);	

}

void CEffectiveHeigthView::OnToolsBackground() 
{
	m_background = !(m_background);
	Invalidate();
}
void CEffectiveHeigthView::OnUpdateToolsBackground(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_background);	
}



void CEffectiveHeigthView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
		m_rcPrintRect = pInfo->m_rectDraw;
	CView::OnPrint(pDC, pInfo);
}
void CEffectiveHeigthView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CEffectiveHeigthView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
	m_printstate = false;
}
BOOL CEffectiveHeigthView::OnPreparePrinting(CPrintInfo* pInfo) 
{
//	((CSMS4DCApp*)AfxGetApp())->SetLandscape();
	return DoPreparePrinting(pInfo);
}
void CEffectiveHeigthView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
	m_printstate = false;
}

void CEffectiveHeigthView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu Menu;
	if (Menu.LoadMenu(IDR_Heff_DATA))
	{
		((CSMS4DCApp *)AfxGetApp())->TranslateMenu(&Menu);	 
		CMenu* pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu!=NULL)
		{
			////////////////////////////////////////
			CString ss;
			int m_step=5;
			int m_num=360/m_step+1;

			pSubMenu->InsertMenu(0,MF_SEPARATOR | MF_BYPOSITION);
//			ss.Format("                               Angle(Deg.)  =>   EffectiveHeight(m)");
			ss.Format("                               " + _Z("Angle(Deg.)  =>   EffectiveHeight(m)"));
			pSubMenu->InsertMenu(1,MF_BYPOSITION,1,ss);
			pSubMenu->InsertMenu(2,MF_SEPARATOR | MF_BYPOSITION);
			for(int i=0;i<m_num/4;i++)
			{
				ss.Format("%03i => %06.1f   |   %03i => %06.1f   |   %03i => %06.1f   |   %03i => %06.1f\n",i*m_step,m_Heff_m[i],(i*m_step)+90,m_Heff_m[i+18],(i*m_step)+180,m_Heff_m[i+36],(i*m_step)+270,m_Heff_m[i+54]);
				pSubMenu->InsertMenu(3 + i,MF_BYPOSITION,1,ss);
			}
			pSubMenu->InsertMenu(m_num/4 + 3, MF_SEPARATOR | MF_BYPOSITION);
			pSubMenu->RemoveMenu(m_num/4 + 4, MF_BYPOSITION);

			/////////////////////////////////////////////
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);
		}
	}
	CView::OnRButtonDown(nFlags, point);
}

void CEffectiveHeigthView::OnToolsSaveeffectiveheight() 
{
	OnHeffdataSaveheff();
}

int CEffectiveHeigthView::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.45) ? x2 : x1);

}
void CEffectiveHeigthView::LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) 
{
	CEffectiveHeigthDoc *pDoc =(CEffectiveHeigthDoc *) GetDocument();

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

	double ix = (double)(pDoc->m_ZoomFactor)*((lon_deg - pDoc->lon0)/(pDoc->m_Resolution_x));
	double jy = (double)(pDoc->m_ZoomFactor)*((lat_deg - pDoc->lat0)/(pDoc->m_Resolution_x));

	(*PointSt).x = (long)ix;
	(*PointSt).y=(long)(pDoc->Height-jy);
}

double CEffectiveHeigthView::Point2Hg(CPoint point1) 
{
	CEffectiveHeigthDoc *pDoc =(CEffectiveHeigthDoc *) GetDocument();
	int i1=point1.x   ,   j1=(pDoc->Height)-point1.y;
	_int16 Hg=pDoc->bufArea[i1+pDoc->Width*j1];
	return (double)Hg;
}

double CEffectiveHeigthView::Points2HgAvr(CPoint point1 , CPoint point2) 
{
	double HgAvr = 0.0;
	if (point1 != point2)
	{
		long x1 = point1.x,		y1 = point1.y;
		long x2 = point2.x,		y2 = point2.y;
		long xabs = abs(x1-x2),	yabs = abs(y1-y2);

		int Np = ((xabs>=yabs) ? xabs+1 : yabs+1);
		int *X;		X = new int[Np];
		int *Y;		Y = new int[Np];
		if (xabs>=yabs)
		{
			for (int i=0; i<Np; i++)
			{
				X[i]=((x1<x2) ? x1+i : x1-i);
				Y[i]=Round((double)y1+(double)((X[i]-x1)*(y2-y1))/((double)(x2-x1)));
			}
		}
		else
		{
			for (int i=0; i<Np; i++)
			{
				Y[i]=((y1<y2) ? y1+i :y1-i);
				X[i]=Round((double)x1+(double)((Y[i]-y1)*(x2-x1))/((double)(y2-y1)));
			}
		}

		CPoint point0;
		double HgSum = 0.0;
		for (int i=0; i<Np; i++)
		{	point0.x = X[i];	point0.y = Y[i];
			HgSum = HgSum + Point2Hg(point0);
		}
		HgAvr = HgSum/((double)Np);
		delete [] X; 
		delete [] Y; 
	}
	else
		HgAvr = Point2Hg(point1);

	return HgAvr;
}


void CEffectiveHeigthView::Point2Stretch(CPoint PointSt1,CPoint *PointSt2) 
{
	CEffectiveHeigthDoc *pDoc =(CEffectiveHeigthDoc *) GetDocument();

	int ofx=(m_AxesW-m_AxesL)/100;
	int ofy=(m_AxesH-m_AxesT)/100;

	(*PointSt2).x =3*ofx+ m_AxesL + (long)(((double)(PointSt1.x)*(m_AxesW-m_AxesL))/((double)(pDoc->Width-0)));
	(*PointSt2).y =4*ofy+ m_AxesT + (long)(((double)(PointSt1.y)*(m_AxesH-m_AxesT))/((double)(pDoc->Height-0)));

}


void CEffectiveHeigthView::OnHeffdataSaveheff() 
{
	int yy = MessageBox(_Z("Effective Height values are going to be changed.\t\rThe old values will be lost if you choose 'Yes' button.\t\r\rDo you want to save the new values?\t"), _Z("Warning"), MB_ICONQUESTION | MB_YESNO);
	if(yy==6)
	{
		CEffectiveHeigthDoc *pDoc =(CEffectiveHeigthDoc *) GetDocument();

		long m_ID = pDoc->m_ID_Ant;
		Delete_set(m_ID);

		CString str = _T("SELECT * FROM AntHgt");

		CEffectiveHeigthSet m_pSet(str);
		m_pSet.Open();

		int m_step = 10;
		int m_num = 360/m_step;
		double MaxHght=-100000;
		for(int i=0;i<m_num;i++)
		{
			m_pSet.AddNew();
			m_pSet.m_AntID  = m_ID;
			m_pSet.m_Azm    = i*m_step;
			m_pSet.m_EffHgt = m_Heff_m[2*i];
			m_pSet.Update();

			MaxHght = max(MaxHght,m_Heff_m[2*i]);
		}
		m_pSet.Close();
		////////////////////////////////////////////
		CString SQL, AntCatID;
		SQL.Format(_T("select antcatid from antenna where antid=%ld"), m_ID);
		CRecordset RS;
		RS.m_pDatabase=m_pSet.m_pDatabase;
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,AntCatID);
		RS.Close();
		SQL.Format(_T("update antcat set maxeffhght=%lf where antcatid=%s"),MaxHght,AntCatID);
		m_pSet.m_pDatabase->ExecuteSQL(SQL);
		/////////////////////////////////
	}
}

void CEffectiveHeigthView::Delete_set(long ID) 
{
	CString str;
	str.Format("SELECT * FROM AntHgt WHERE ((AntID)=%ld);",ID);
	CEffectiveHeigthSet m_pSet(str);
	m_pSet.Open();

	if(m_pSet.GetRecordCount() ==1)
	{
		while(!m_pSet.IsEOF())
		{
			m_pSet.Delete();
			m_pSet.MoveNext();
		}
	}
	m_pSet.Close();
}


void CEffectiveHeigthView::OnUpdateToolsSaveeffectiveheight(CCmdUI* pCmdUI) 
{
	int level = ((CSMS4DCApp *)AfxGetApp())->m_UserLevel;
	pCmdUI->Enable(level!=6);			
}
void CEffectiveHeigthView::OnUpdateHeffdataSaveheff(CCmdUI* pCmdUI) 
{
	int level = ((CSMS4DCApp *)AfxGetApp())->m_UserLevel;
	pCmdUI->Enable(level!=6);			
}

void CEffectiveHeigthView::OnToolsTxt() 
{
	CEffectiveHeigthDoc* pDoc = (CEffectiveHeigthDoc*)GetDocument();
	CString str;	str.Format("Heff_%s.txt",pDoc->Name_ST);
//	char strFilter[] = { "text Files (*.txt)|*.txt|All Files (*.*)|*.*||"};
	CString strFilter =  _Z("text Files") + " (*.txt)|*.txt|" + _Z("All Files") + " (*.*)|*.*||";

	CFileDialog FileDLG(FALSE, ".txt", str, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (FileDLG.DoModal() == IDOK)
	{
		FILE *fp=fopen(FileDLG.GetPathName(),"wt");
		if(fp)
		{
			fprintf(fp,"Station Name :  %s\n",pDoc->Name_ST);
			fprintf(fp,"Map Property File :  %s\n",pDoc->TileInfo);
			fputs("Angle(Deg.)   EffectiveHeight(m)\n",fp);

			int m_step=5;
	//		int m_step=1;
			int m_num=360/m_step+1;

			for(int i=0;i<m_num;i++)
				fprintf(fp,"          %03i        %06.1f\n",i*m_step,m_Heff_m[i]);
			fclose(fp);
			ShellExecute(m_hWnd, "open", FileDLG.GetPathName(), NULL, NULL, SW_SHOWNORMAL);			
		}
	}
	
}

void CEffectiveHeigthView::OnHeffdataTxt() 
{
	OnToolsTxt();	
}

void CEffectiveHeigthView::Point2Stretch1(CPoint PointSt1,CPoint *PointSt2) 
{
	CEffectiveHeigthDoc *pDoc =(CEffectiveHeigthDoc *) GetDocument();

	int ofx=(m_AxesW-m_AxesL)/1;
	int ofy=(m_AxesH-m_AxesT)/1;

	(*PointSt2).x =3*ofx+ m_AxesL + (long)(((double)(PointSt1.x)*(m_AxesW-m_AxesL))/((double)(pDoc->Width-0)));
	(*PointSt2).y =4*ofy+ m_AxesT + (long)(((double)(PointSt1.y)*(m_AxesH-m_AxesT))/((double)(pDoc->Height-0)));

}
void CEffectiveHeigthView::OnToolsEditdatabase() 
{
	CEffectiveHeigthDoc *pDoc =(CEffectiveHeigthDoc *) GetDocument();
	CHeffDLG xx;
	xx.m_AntID = pDoc->m_ID_Ant;
	xx.DoModal();	
}

void CEffectiveHeigthView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE6);
}

