// SymbolDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "SymbolDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSymbolDLG dialog


CSymbolDLG::CSymbolDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CSymbolDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSymbolDLG)
	m_symbolcolorB = 80;
	m_symbolcolorG = 0;
	m_symbolcolorR = 0;
	m_symbolsize = 4;
	m_symbolTcolorB = 80;
	m_symbolTcolorG = 0;
	m_symbolTcolorR = 0;
	//}}AFX_DATA_INIT
	m_rectS = CRect(110+10,54,110+22+10,54+22);
	m_rectT = CRect(110+10,79,110+22+10,79+22);
	m_bLDown = 0;
}


void CSymbolDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSymbolDLG)
	DDX_Text(pDX, IDC_Symbol_ColorBlue, m_symbolcolorB);
	DDV_MinMaxInt(pDX, m_symbolcolorB, 0, 255);
	DDX_Text(pDX, IDC_Symbol_ColorGreen, m_symbolcolorG);
	DDV_MinMaxInt(pDX, m_symbolcolorG, 0, 255);
	DDX_Text(pDX, IDC_Symbol_ColorRed, m_symbolcolorR);
	DDV_MinMaxInt(pDX, m_symbolcolorR, 0, 255);
	DDX_Text(pDX, IDC_Symbol_Size, m_symbolsize);
	DDV_MinMaxInt(pDX, m_symbolsize, 1, 10);
	DDX_Text(pDX, IDC_Symbol_Text_ColorBlue, m_symbolTcolorB);
	DDV_MinMaxInt(pDX, m_symbolTcolorB, 0, 255);
	DDX_Text(pDX, IDC_Symbol_Text_ColorGreen, m_symbolTcolorG);
	DDV_MinMaxInt(pDX, m_symbolTcolorG, 0, 255);
	DDX_Text(pDX, IDC_Symbol_Text_ColorRed, m_symbolTcolorR);
	DDV_MinMaxInt(pDX, m_symbolTcolorR, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSymbolDLG, CDialog)
	//{{AFX_MSG_MAP(CSymbolDLG)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_Symbol_Size, OnChangeSymbolSize)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_EN_UPDATE(IDC_Symbol_ColorRed, OnUpdateSymbolColorRed)
	ON_EN_UPDATE(IDC_Symbol_Text_ColorRed, OnUpdateSymbolTextColorRed)
	ON_EN_UPDATE(IDC_Symbol_ColorGreen, OnUpdateSymbolColorGreen)
	ON_EN_UPDATE(IDC_Symbol_ColorBlue, OnUpdateSymbolColorBlue)
	ON_EN_UPDATE(IDC_Symbol_Text_ColorGreen, OnUpdateSymbolTextColorGreen)
	ON_EN_UPDATE(IDC_Symbol_Text_ColorBlue, OnUpdateSymbolTextColorBlue)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSymbolDLG message handlers

void CSymbolDLG::OnPaint() 
{
	CPaintDC dc(this);

	COLORREF m_color1 = RGB(m_symbolcolorR,m_symbolcolorG,m_symbolcolorB);
	COLORREF m_color2 = RGB(m_symbolTcolorR,m_symbolTcolorG,m_symbolTcolorB);

	CPen penStation(PS_SOLID,1,m_color1);
	CPen *Oldpen = dc.SelectObject(&penStation);
	CBrush brushStation(m_color1);
	CBrush *Oldbrush = dc.SelectObject(&brushStation);

	CPoint points(150,150);
	len1 = m_symbolsize;

	dc.MoveTo(points.x-len1,points.y);
	dc.LineTo(points.x+len1,points.y);
	dc.MoveTo(points.x,points.y-3*len1);
	dc.LineTo(points.x,points.y+3*len1);

	dc.MoveTo(points.x-len1,points.y-len1);
	dc.LineTo(points.x+len1,points.y-len1);
	dc.LineTo(points.x+len1,points.y+len1);
	dc.LineTo(points.x-len1,points.y+len1);
	dc.LineTo(points.x-len1,points.y-len1);

	CPoint pointsBT[5];
	pointsBT[0]=CPoint(points.x-len1,points.y+len1);
	pointsBT[1]=CPoint(points.x+len1,points.y+len1);
	pointsBT[2]=CPoint(points.x+3*len1,points.y+3*len1);
	pointsBT[3]=CPoint(points.x-3*len1,points.y+3*len1);
	pointsBT[4]=pointsBT[0];
	dc.Polygon(pointsBT,5);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_color2);
	dc.TextOut(points.x+10,points.y-8,_Z("Station Name"));


	dc.FillRect(m_rectS, &brushStation);
	dc.DrawEdge(m_rectS, FALSE ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);

	CBrush bkBrush2(m_color2);
	dc.FillRect(m_rectT, &bkBrush2);
	dc.DrawEdge(m_rectT, FALSE ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);

	dc.SelectObject(&Oldpen);
	dc.SelectObject(&Oldbrush);
}

void CSymbolDLG::OnChangeSymbolSize() 
{
	UpdateData(true);
	len1 = m_symbolsize;
	UpdateData(false);
	Invalidate();
}

void CSymbolDLG::OnSymbolColor() 
{
	CColorDialog xx(RGB(0, 0, 80), CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ = xx.GetColor();
		UpdateData(true);
		m_symbolcolorR=GetRValue(ZZ);
		m_symbolcolorG=GetGValue(ZZ);
		m_symbolcolorB=GetBValue(ZZ);
		Invalidate();
		UpdateData(false);
	}
}

void CSymbolDLG::OnSymbolTextColor() 
{
	CColorDialog xx(RGB(0, 0, 80), CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ = xx.GetColor();
		UpdateData(true);
		m_symbolTcolorR=GetRValue(ZZ);
		m_symbolTcolorG=GetGValue(ZZ);
		m_symbolTcolorB=GetBValue(ZZ);
		Invalidate();
		UpdateData(false);
	}
}

void CSymbolDLG::OnUpdateSymbolColorRed() 
{
	UpdateData();
	InvalidateRect(m_rectS,true);

	CPoint points(150,150);
	CRect rect = CRect(points.x-4*len1,points.y-4*len1,points.x+4*len1,points.y+4*len1);
	InvalidateRect(rect,true);

	UpdateData(false);
}
void CSymbolDLG::OnUpdateSymbolColorGreen() 
{
	OnUpdateSymbolColorRed(); 
}
void CSymbolDLG::OnUpdateSymbolColorBlue() 
{
	OnUpdateSymbolColorRed(); 
}

void CSymbolDLG::OnUpdateSymbolTextColorRed() 
{
	UpdateData();
	InvalidateRect(m_rectT,true);

	CPoint points(150,150);
	CRect rect = CRect(points.x-4*4,points.y-4*4,points.x+30*4,points.y+4*4);
	InvalidateRect(rect,true);

	UpdateData(false);	
}
void CSymbolDLG::OnUpdateSymbolTextColorGreen() 
{
	OnUpdateSymbolTextColorRed();	
}
void CSymbolDLG::OnUpdateSymbolTextColorBlue() 
{
	OnUpdateSymbolTextColorRed();	
}

void CSymbolDLG::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRgn rgnS, rgnT;
	rgnS.CreateRectRgn(m_rectS.left,m_rectS.top,m_rectS.right, m_rectS.bottom);
	rgnT.CreateRectRgn(m_rectT.left,m_rectT.top,m_rectT.right, m_rectT.bottom);
	
	if(rgnS.PtInRegion(point))
	{
		CDC *dc = this->GetDC();
		dc->DrawEdge(m_rectS, TRUE  ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);
		m_bLDown = 1;
		ReleaseDC(dc);
	}
	else if(rgnT.PtInRegion(point))
	{
		CDC *dc = this->GetDC();
		dc->DrawEdge(m_rectT, TRUE  ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);
		m_bLDown = 2;
		ReleaseDC(dc);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CSymbolDLG::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bLDown>0)
	{
		CDC *dc = this->GetDC();
		dc->DrawEdge(m_rectS, FALSE ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);
		dc->DrawEdge(m_rectT, FALSE ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);

		CRgn rgnS, rgnT;
		rgnS.CreateRectRgn(m_rectS.left,m_rectS.top,m_rectS.right, m_rectS.bottom);
		rgnT.CreateRectRgn(m_rectT.left,m_rectT.top,m_rectT.right, m_rectT.bottom);

		if		((rgnS.PtInRegion(point))&&(m_bLDown == 1))	OnSymbolColor();
		else if	((rgnT.PtInRegion(point))&&(m_bLDown == 2))	OnSymbolTextColor();
		m_bLDown = 0;
		ReleaseDC(dc);
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CSymbolDLG::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bLDown>0)
	{
		CRgn rgnS, rgnT;
		rgnS.CreateRectRgn(m_rectS.left,m_rectS.top,m_rectS.right, m_rectS.bottom);
		rgnT.CreateRectRgn(m_rectT.left,m_rectT.top,m_rectT.right, m_rectT.bottom);

		CDC *dc = this->GetDC();
		if((m_bLDown == 1))
		{
			if((rgnS.PtInRegion(point)))
					dc->DrawEdge(m_rectS, TRUE  ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);
			else	dc->DrawEdge(m_rectS, FALSE ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);
		}
		else if(m_bLDown == 2)
		{
			if((rgnT.PtInRegion(point)))
					dc->DrawEdge(m_rectT, TRUE  ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);
			else	dc->DrawEdge(m_rectT, FALSE ? BDR_SUNKENOUTER : BDR_RAISEDINNER,  BF_RECT);
		}
		ReleaseDC(dc);
	}
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CSymbolDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}