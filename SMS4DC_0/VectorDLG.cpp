// VectorDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "VectorDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorDLG dialog


CVectorDLG::CVectorDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CVectorDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVectorDLG)
	m_LineWidth = 1;
	m_FillMode = FALSE;
	m_LineColorBlue = 0;
	m_LineColorGreen = 0;
	m_LineColorRed = 0;
	m_FillColorBlue = 0;
	m_FillColorGreen = 0;
	m_FillColorRed = 255;
	m_LineStyle0 = 0;
	m_FillTransparancy = 50;
	//}}AFX_DATA_INIT
	m_TitleName="";
//	m_color1=RGB(0,0,0);
//	m_color2=RGB(255,0,0);
	m_Pos = 50;
}


void CVectorDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVectorDLG)
	DDX_Control(pDX, IDC_SLIDER_FillTransparancy, m_SliderFillTransparancy);
	DDX_Control(pDX, IDC_Vector_Line_Style, m_LineStyle);
	DDX_Text(pDX, IDC_Vector_Line_Width, m_LineWidth);
	DDV_MinMaxInt(pDX, m_LineWidth, 1, 10);
	DDX_Check(pDX, IDC_Vector_FillMode, m_FillMode);
	DDX_Text(pDX, IDC_LineColorBlue, m_LineColorBlue);
	DDV_MinMaxInt(pDX, m_LineColorBlue, 0, 255);
	DDX_Text(pDX, IDC_LineColorGreen, m_LineColorGreen);
	DDV_MinMaxInt(pDX, m_LineColorGreen, 0, 255);
	DDX_Text(pDX, IDC_LineColorRed, m_LineColorRed);
	DDV_MinMaxInt(pDX, m_LineColorRed, 0, 255);
	DDX_Text(pDX, IDC_FillColorBlue, m_FillColorBlue);
	DDV_MinMaxInt(pDX, m_FillColorBlue, 0, 255);
	DDX_Text(pDX, IDC_FillColorGreen, m_FillColorGreen);
	DDV_MinMaxInt(pDX, m_FillColorGreen, 0, 255);
	DDX_Text(pDX, IDC_FillColorRed, m_FillColorRed);
	DDV_MinMaxInt(pDX, m_FillColorRed, 0, 255);
	DDX_Text(pDX, IDC_LineStyle0, m_LineStyle0);
	DDX_Text(pDX, IDC_Vector_FillTransparancy, m_FillTransparancy);
	DDV_MinMaxDouble(pDX, m_FillTransparancy, 0., 100.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVectorDLG, CDialog)
	//{{AFX_MSG_MAP(CVectorDLG)
	ON_BN_CLICKED(IDC_Vector_FillMode, OnVectorFillMode)
	ON_CBN_SELENDOK(IDC_Vector_Line_Style, OnSelendokVectorLineStyle)
	ON_EN_CHANGE(IDC_Vector_Line_Width, OnChangeVectorLineWidth)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_Vector_FillTransparancy, OnChangeVectorFillTransparancy)
	ON_WM_LBUTTONDOWN()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_LineColorRed, OnChangeLineColorRed)
	ON_EN_CHANGE(IDC_LineColorGreen, OnChangeLineColorGreen)
	ON_EN_CHANGE(IDC_LineColorBlue, OnChangeLineColorBlue)
	ON_EN_CHANGE(IDC_FillColorRed, OnChangeFillColorRed)
	ON_EN_CHANGE(IDC_FillColorGreen, OnChangeFillColorGreen)
	ON_EN_CHANGE(IDC_FillColorBlue, OnChangeFillColorBlue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVectorDLG message handlers


void CVectorDLG::OnVectorFillMode() 
{
	UpdateData(true);
	if (m_FillMode==false)
	{
		GetDlgItem(IDC_FillColorRed)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FillColorGreen)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FillColorBlue)->ShowWindow(SW_HIDE);
	//	GetDlgItem(IDC_Vector_Fill_Color)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_FillColor)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_FillTransparancy)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_Vector_FillTransparancy)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_FillTransparancy)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_FillColorRed)->ShowWindow(SW_SHOW);	
		GetDlgItem(IDC_FillColorGreen)->ShowWindow(SW_SHOW);	
		GetDlgItem(IDC_FillColorBlue)->ShowWindow(SW_SHOW);	
	//	GetDlgItem(IDC_Vector_Fill_Color)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FillColor)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FillTransparancy)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_Vector_FillTransparancy)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SLIDER_FillTransparancy)->ShowWindow(SW_SHOW);
	}
	UpdateData(false);
	Invalidate();
}

BOOL CVectorDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_TitleName);

	m_LineStyle.AddString("PS_SOLID");
	m_LineStyle.AddString("PS_DASH");
	m_LineStyle.AddString("PS_DOT");
	m_LineStyle.AddString("PS_DASHDOT");
	m_LineStyle.AddString("PS_DASHDOTDOT");
	m_LineStyle.SetTopIndex(1);
	m_LineStyle.SetCurSel(0);
	m_SliderFillTransparancy.SetRange(0,100);
	m_SliderFillTransparancy.SetPos((int)m_FillTransparancy);
	
	OnVectorFillMode();
	m_color1 = RGB(m_LineColorRed,m_LineColorGreen,m_LineColorBlue);
	m_color2 = RGB(m_FillColorRed,m_FillColorGreen,m_FillColorBlue);
	m_LineStyle.SetCurSel(m_LineStyle0);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}

void CVectorDLG::OnSelendokVectorLineStyle() 
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

void CVectorDLG::OnChangeVectorLineWidth() 
{
	UpdateData(true);
	if (m_LineWidth>1)
	{
		m_LineStyle0=0;
		m_LineStyle.SetCurSel(0);
	}
	UpdateData(false);	
}

void CVectorDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	int x1=85+38,y1=63,x2=x1+20,y2=y1+20;
	int x1f=185+20,y1f=113,x2f=x1f+20,y2f=y1f+20;

	CPen pen1(PS_SOLID,1,RGB(255,255,255));
	dc.SelectObject(&pen1);
	dc.MoveTo(x1-1,y2+1);  dc.LineTo(x1-1,y1-1);  dc.LineTo(x2+1,y1-1);
	if (m_FillMode)
	{dc.MoveTo(x1f-1,y2f+1);  dc.LineTo(x1f-1,y1f-1);  dc.LineTo(x2f+1,y1f-1);}

	CPen pen2(PS_SOLID,1,RGB(128,128,128));
	dc.SelectObject(&pen2);
	dc.MoveTo(x2+1,y1);	dc.LineTo(x2+1,y2+1);  dc.LineTo(x1,y2+1);
	if (m_FillMode)
	{dc.MoveTo(x2f+1,y1f);	dc.LineTo(x2f+1,y2f+1);  dc.LineTo(x1f,y2f+1);}

	CPen pen3(PS_SOLID,1,RGB(64,64,64));
	dc.SelectObject(&pen3);
	dc.MoveTo(x2+2,y1-1);	dc.LineTo(x2+2,y2+2);  dc.LineTo(x1-1,y2+2);
	if (m_FillMode)
	{dc.MoveTo(x2f+2,y1f-1);	dc.LineTo(x2f+2,y2f+2);  dc.LineTo(x1f-1,y2f+2);}


	CRect rect1(x1,y1,x2,y2);
	CBrush brush1(m_color1);
	dc.SelectObject(&brush1);
	dc.FillRect(&rect1,&brush1);
	if (m_FillMode)
	{
		CRect rect2(x1f,y1f,x2f,y2f);
		CBrush brush2(m_color2);
		dc.SelectObject(&brush2);
		dc.FillRect(&rect2,&brush2);
	}
}

void CVectorDLG::OnChangeVectorFillTransparancy() 
{
	UpdateData(true);
	m_SliderFillTransparancy.SetPos((int)m_FillTransparancy);
	UpdateData(false);
}

void CVectorDLG::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x1=85+38,y1=63,x2=x1+20,y2=y1+20;
	int x1f=185+20,y1f=113,x2f=x1f+20,y2f=y1f+20;

	if ((point.x>=x1) && (point.x<=x2) && (point.y>=y1) && (point.y<=y2) )
		OnVectorLineColor1();
	
	if (m_FillMode && (point.x>=x1f) && (point.x<=x2f) && (point.y>=y1f) && (point.y<=y2f) )
		OnVectorFillColor1();
	
	CDialog::OnLButtonDown(nFlags, point);
}


void CVectorDLG::OnVectorLineColor1() 
{
	CColorDialog xx(m_color1, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed=GetRValue(ZZ);
		m_LineColorGreen=GetGValue(ZZ);
		m_LineColorBlue=GetBValue(ZZ);
		m_color1=ZZ;
		Invalidate();
		UpdateData(false);
	}
}
void CVectorDLG::OnVectorFillColor1() 
{
	CColorDialog xx(m_color2, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_FillColorRed=GetRValue(ZZ);
		m_FillColorGreen=GetGValue(ZZ);
		m_FillColorBlue=GetBValue(ZZ);
		m_color2=ZZ;
		Invalidate();
		UpdateData(false);
	}
}

void CVectorDLG::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	UpdateData(true);
	int	delta, newPos;
	switch (nSBCode)
	{
	case SB_THUMBTRACK:		
	case SB_THUMBPOSITION:	m_Pos = nPos;	break;
	case SB_LEFT:			delta = -100;		goto New_Pos;
	case SB_RIGHT:			delta = +100;		goto New_Pos;
	case SB_LINELEFT:		delta = -1;			goto New_Pos;
	case SB_LINERIGHT:		delta = +1;			goto New_Pos;
	case SB_PAGELEFT:		delta = -20;		goto New_Pos;
	case SB_PAGERIGHT:		delta = +20;		goto New_Pos;
	New_Pos:
		newPos = m_Pos + delta;
		m_Pos = newPos<0 ? 0 : newPos>100 ? 100 : newPos;
		break;
	case SB_ENDSCROLL:
	default:
		return;
	}
	m_FillTransparancy = m_Pos;
	UpdateData(false);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CVectorDLG::OnChangeLineColorRed() 
{
	UpdateData();
	m_color1 = RGB(m_LineColorRed,m_LineColorGreen,m_LineColorBlue);
	int x1=85+38,y1=63,x2=x1+20,y2=y1+20;
	CRect rect(x1,y1,x2,y2);
	InvalidateRect(rect,FALSE);
	UpdateData(false);
}
void CVectorDLG::OnChangeLineColorGreen() 
{
	OnChangeLineColorRed();
}
void CVectorDLG::OnChangeLineColorBlue() 
{
	OnChangeLineColorRed();
}

void CVectorDLG::OnChangeFillColorRed() 
{
	UpdateData();
	m_color2 = RGB(m_FillColorRed,m_FillColorGreen,m_FillColorBlue);
	int x1f=185+20,y1f=113,x2f=x1f+20,y2f=y1f+20;
	CRect rect(x1f,y1f,x2f,y2f);
	InvalidateRect(rect,FALSE);
	UpdateData(false);
}
void CVectorDLG::OnChangeFillColorGreen() 
{
	OnChangeFillColorRed();	
}
void CVectorDLG::OnChangeFillColorBlue() 
{
	OnChangeFillColorRed();	
}
