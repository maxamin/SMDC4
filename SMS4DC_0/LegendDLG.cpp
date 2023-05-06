// LegendDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "LegendDLG.h"
#include "Tile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLegendDLG dialog


CLegendDLG::CLegendDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CLegendDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLegendDLG)
	m_MinValue = -500.35;
	m_MaxValue = 5600.12;
	m_title = _Z("Altitude (m)");
	m_colormaptype = _T("Jet");
	m_level = 255;
	m_bThreshold = FALSE;
	m_Threshold = 10.0;
	m_colorRate = 0;
	//}}AFX_DATA_INIT
	m_ColorMapNegative = FALSE;		//97/12/26
}


void CLegendDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLegendDLG)
	DDX_Text(pDX, IDC_EDIT_max, m_MinValue);
	DDX_Text(pDX, IDC_EDIT_min, m_MaxValue);
	DDX_Text(pDX, IDC_EDIT_title, m_title);
	DDX_Text(pDX, IDC_EDIT_colormaptype, m_colormaptype);
	DDX_Text(pDX, IDC_EDIT_level, m_level);
	DDX_Text(pDX, IDC_EDIT_bthr, m_bThreshold);
	DDX_Text(pDX, IDC_EDIT_thr, m_Threshold);
	DDX_Text(pDX, IDC_EDIT_colorRate, m_colorRate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLegendDLG, CDialog)
	//{{AFX_MSG_MAP(CLegendDLG)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLegendDLG message handlers


void CLegendDLG::OnPaint() 
{
	UpdateData();

//	CRect rect1;
//	GetWindowRect(&rect1);
//	SetWindowPos(NULL,875+rect1.left,rect1.top+30,rect1.Width(),rect1.Height(),SWP_DRAWFRAME);

	CPaintDC dc(this); // device context for painting

	COLORREF RGBt[256];
	CTile m_tile;
	CSize sz(30, 1);
	CString label;
	double y;

	int tt=int(255.0/m_level);

	m_tile.ColorMap(m_colormaptype);
	long R,G,B;

	if (m_bThreshold)
	{
		for (int i=0;i<2;i++)
		{
			RGBt[i] = m_tile.RGBt[ 0+(1-i)*159 ];

			if(m_ColorMapNegative)		//97/12/26	
			{
				R = 255-GetRValue(RGBt[i]);	
				G = 255-GetGValue(RGBt[i]);		
				B = 255-GetBValue(RGBt[i]);
				RGBt[i] = RGB(R,G,B);
			}

			CPoint pt(20, 30+127*i);
			CRect rect3(pt, CSize(30, 127.5));
			CBrush brush3(RGBt[i]);
			dc.SelectObject(&brush3);
			dc.FillRect(&rect3,&brush3);
		}
	}
	else
	{
		for (int i=0;i<256;i++)
		{
			RGBt[i] = m_tile.RGBt[ tt*(i/tt) ];

			R = GetRValue(RGBt[i]);
			G = GetGValue(RGBt[i]);
			B = GetBValue(RGBt[i]);

			if(m_ColorMapNegative)		//97/12/26	
			{
				R =   255-R;	G =   255-G;		B =   255-B;
			}

			R = max(0,min(255,m_colorRate + R ));
			G = max(0,min(255,m_colorRate + G ));
			B = max(0,min(255,m_colorRate + B ));

			RGBt[i] = RGB(R,G,B);

			CPoint pt(20, 30+255-i);
			CRect rect3(pt, sz);
			CBrush brush3(RGBt[i]);
			dc.SelectObject(&brush3);
			dc.FillRect(&rect3,&brush3);
		}
	}


	dc.SetBkMode(TRANSPARENT);
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));      
	lf.lfHeight = 12;               
	lf.lfWidth =0;
	lf.lfWeight = FW_BOLD;
	strcpy(lf.lfFaceName, "Arial");       
	lf.lfEscapement=0;
	VERIFY(font.CreateFontIndirect(&lf));  
	CFont* def_font = dc.SelectObject(&font);
	dc.SetTextColor(RGB(0,0,0));

	dc.TextOut(20,5,m_title);
	dc.SetTextAlign(TA_RIGHT);

	if (m_bThreshold)
	{
		label.Format("%0.2f",m_Threshold);
		dc.TextOut(20+30+55,-10+159,label);

		CPen pen;
		pen.CreatePen(PS_SOLID ,1,RGB(0,0,0));
		dc.SelectObject(&pen);
		dc.MoveTo(20+30+0,-2+159);
		dc.LineTo(20+30+10,-2+159);
	}
	else
	{
		for (int i=0;i<256;i=i+17)
		{
			y=m_MinValue + ((double)i)*(m_MaxValue - m_MinValue)/255.0;
//			label.Format("%0.2f",y);
			label.Format("%ld",(long)y);
			dc.TextOut(20+30+55,22+(255-i),label);
			CPen pen;
			pen.CreatePen(PS_SOLID ,1,RGBt[i]);
			dc.SelectObject(&pen);
			dc.MoveTo(20+30+0,30+(255-i));
			dc.LineTo(20+30+10,30+(255-i));

		}
	}
	dc.SelectObject(def_font);
	font.DeleteObject(); 

	UpdateData(false);
}

void CLegendDLG::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
	delete this;
}

void CLegendDLG::OnClose() 
{
	CDialog::OnClose();
	delete this;
}


BOOL CLegendDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
