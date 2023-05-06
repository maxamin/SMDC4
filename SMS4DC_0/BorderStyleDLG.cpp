// BorderStyleDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "BorderStyleDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBorderStyleDLG dialog


CBorderStyleDLG::CBorderStyleDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CBorderStyleDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBorderStyleDLG)
	m_LineWidth = 1;
	m_LineColorBlue = 0;
	m_LineColorGreen = 0;
	m_LineColorRed = 0;
	m_LineStyle0 = 0;
	//}}AFX_DATA_INIT
	m_color1=RGB(0,0,0);

	m_Title = _Z("Border Style");	
}


void CBorderStyleDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBorderStyleDLG)
	DDX_Control(pDX, IDC_Border_Line_Style, m_LineStyle);
	DDX_Text(pDX, IDC_Border_Line_Width, m_LineWidth);
	DDV_MinMaxInt(pDX, m_LineWidth, 0, 6);
	DDX_Text(pDX, IDC_LineColorBlue, m_LineColorBlue);
	DDV_MinMaxByte(pDX, m_LineColorBlue, 0, 255);
	DDX_Text(pDX, IDC_LineColorGreen, m_LineColorGreen);
	DDV_MinMaxByte(pDX, m_LineColorGreen, 0, 255);
	DDX_Text(pDX, IDC_LineColorRed, m_LineColorRed);
	DDV_MinMaxByte(pDX, m_LineColorRed, 0, 255);
	DDX_Text(pDX, IDC_LineStyle0, m_LineStyle0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBorderStyleDLG, CDialog)
	//{{AFX_MSG_MAP(CBorderStyleDLG)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_Border_Line_Width, OnChangeBorderLineWidth)
	ON_CBN_SELENDOK(IDC_Border_Line_Style, OnSelendokBorderLineStyle)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_LineColorRed, OnChangeLineColorRed)
	ON_EN_CHANGE(IDC_LineColorGreen, OnChangeLineColorGreen)
	ON_EN_CHANGE(IDC_LineColorBlue, OnChangeLineColorBlue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBorderStyleDLG message handlers

BOOL CBorderStyleDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(m_Title);

	m_LineStyle.AddString("PS_SOLID");
	m_LineStyle.AddString("PS_DASH");
	m_LineStyle.AddString("PS_DOT");
	m_LineStyle.AddString("PS_DASHDOT");
	m_LineStyle.AddString("PS_DASHDOTDOT");
	m_LineStyle.SetTopIndex(1);
	m_LineStyle.SetCurSel(m_LineStyle0);
	
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CBorderStyleDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	int x1=85+38,y1=63,x2=x1+20,y2=y1+20;

	CPen pen1(PS_SOLID,1,RGB(255,255,255));
	dc.SelectObject(&pen1);
	dc.MoveTo(x1-1,y2+1);  dc.LineTo(x1-1,y1-1);  dc.LineTo(x2+1,y1-1);

	CPen pen2(PS_SOLID,1,RGB(128,128,128));
	dc.SelectObject(&pen2);
	dc.MoveTo(x2+1,y1);	dc.LineTo(x2+1,y2+1);  dc.LineTo(x1,y2+1);

	CPen pen3(PS_SOLID,1,RGB(64,64,64));
	dc.SelectObject(&pen3);
	dc.MoveTo(x2+2,y1-1);	dc.LineTo(x2+2,y2+2);  dc.LineTo(x1-1,y2+2);


	CRect rect1(x1,y1,x2,y2);
	CBrush brush1(m_color1);
	dc.SelectObject(&brush1);
	dc.FillRect(&rect1,&brush1);
}

void CBorderStyleDLG::OnChangeBorderLineWidth() 
{
	UpdateData(true);
	if (m_LineWidth>1)
	{
		m_LineStyle0=0;
		m_LineStyle.SetCurSel(0);
	}
	UpdateData(false);	
}

void CBorderStyleDLG::OnSelendokBorderLineStyle() 
{
	UpdateData(true);
	m_LineStyle0=m_LineStyle.GetCurSel();

	if (m_LineWidth>1)
	{
		m_LineStyle0=0;
		m_LineStyle.SetCurSel(0);
	}

	UpdateData(false);
}

void CBorderStyleDLG::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x1=85+38,y1=63,x2=x1+20,y2=y1+20;

	if ((point.x>=x1) && (point.x<=x2) && (point.y>=y1) && (point.y<=y2) )
		OnVectorLineColor1();
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CBorderStyleDLG::OnVectorLineColor1() 
{
	CColorDialog xx(m_color1, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ = xx.GetColor();
		UpdateData(true);
		m_LineColorRed = GetRValue(ZZ);
		m_LineColorGreen = GetGValue(ZZ);
		m_LineColorBlue = GetBValue(ZZ);
		m_color1 = ZZ;
		Invalidate();
		UpdateData(false);
	}
}

void CBorderStyleDLG::OnChangeLineColorRed() 
{
	int x1=85+38,y1=63,x2=x1+20,y2=y1+20;
	CRect rect1(x1,y1,x2,y2);

	UpdateData(true);
	m_color1 = RGB(m_LineColorRed,m_LineColorGreen,m_LineColorBlue);
	InvalidateRect(rect1,FALSE);
	UpdateData(false);
}
void CBorderStyleDLG::OnChangeLineColorGreen() 
{
	OnChangeLineColorRed();	
}
void CBorderStyleDLG::OnChangeLineColorBlue() 
{
	OnChangeLineColorRed();	
}
