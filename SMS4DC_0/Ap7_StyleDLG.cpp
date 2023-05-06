// Ap7_StyleDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Ap7_StyleDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAp7_StyleDLG dialog


CAp7_StyleDLG::CAp7_StyleDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAp7_StyleDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAp7_StyleDLG)
	m_LineWidth1 = 1;
	m_LineColorBlue1 = 0;
	m_LineColorGreen1 = 0;
	m_LineColorRed1 = 0;
	m_LineStyle01 = 0;
	m_LineWidth2 = 1;
	m_LineColorBlue2 = 0;
	m_LineColorGreen2 = 0;
	m_LineColorRed2 = 0;
	m_LineStyle02 = 0;
	m_LineWidth3 = 1;
	m_LineWidth4 = 1;
	m_LineWidth5 = 1;
	m_LineWidth6 = 1;
	m_LineWidth7 = 1;
	m_LineWidth8 = 1;
	m_LineColorBlue3 = 0;
	m_LineColorBlue4 = 0;
	m_LineColorBlue5 = 0;
	m_LineColorBlue6 = 0;
	m_LineColorBlue7 = 0;
	m_LineColorBlue8 = 0;
	m_LineColorGreen3 = 0;
	m_LineColorGreen4 = 0;
	m_LineColorGreen5 = 0;
	m_LineColorGreen6 = 0;
	m_LineColorGreen7 = 0;
	m_LineColorGreen8 = 0;
	m_LineColorRed3 = 0;
	m_LineColorRed4 = 0;
	m_LineColorRed5 = 0;
	m_LineColorRed6 = 0;
	m_LineColorRed7 = 0;
	m_LineColorRed8 = 0;
	m_LineStyle03 = 0;
	m_LineStyle04 = 0;
	m_LineStyle05 = 0;
	m_LineStyle06 = 0;
	m_LineStyle07 = 0;
	m_LineStyle08 = 0;
	//}}AFX_DATA_INIT
	m_color1=m_color2=m_color3=m_color4=m_color5=m_color6=m_color7=m_color8=RGB(0,0,0);

}


void CAp7_StyleDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAp7_StyleDLG)
	DDX_Control(pDX, IDC_Border_Line_Style8, m_LineStyle8);
	DDX_Control(pDX, IDC_Border_Line_Style7, m_LineStyle7);
	DDX_Control(pDX, IDC_Border_Line_Style6, m_LineStyle6);
	DDX_Control(pDX, IDC_Border_Line_Style5, m_LineStyle5);
	DDX_Control(pDX, IDC_Border_Line_Style4, m_LineStyle4);
	DDX_Control(pDX, IDC_Border_Line_Style3, m_LineStyle3);
	DDX_Control(pDX, IDC_Border_Line_Style2, m_LineStyle2);
	DDX_Control(pDX, IDC_Border_Line_Style1, m_LineStyle1);
	DDX_Text(pDX, IDC_Border_Line_Width1, m_LineWidth1);
	DDX_Text(pDX, IDC_LineColorBlue1, m_LineColorBlue1);
	DDX_Text(pDX, IDC_LineColorGreen1, m_LineColorGreen1);
	DDX_Text(pDX, IDC_LineColorRed1, m_LineColorRed1);
	DDX_Text(pDX, IDC_LineStyle01, m_LineStyle01);
	DDX_Text(pDX, IDC_Border_Line_Width2, m_LineWidth2);
	DDX_Text(pDX, IDC_LineColorBlue2, m_LineColorBlue2);
	DDX_Text(pDX, IDC_LineColorGreen2, m_LineColorGreen2);
	DDX_Text(pDX, IDC_LineColorRed2, m_LineColorRed2);
	DDX_Text(pDX, IDC_LineStyle02, m_LineStyle02);
	DDX_Text(pDX, IDC_Border_Line_Width3, m_LineWidth3);
	DDX_Text(pDX, IDC_Border_Line_Width4, m_LineWidth4);
	DDX_Text(pDX, IDC_Border_Line_Width5, m_LineWidth5);
	DDX_Text(pDX, IDC_Border_Line_Width6, m_LineWidth6);
	DDX_Text(pDX, IDC_Border_Line_Width7, m_LineWidth7);
	DDX_Text(pDX, IDC_Border_Line_Width8, m_LineWidth8);
	DDX_Text(pDX, IDC_LineColorBlue3, m_LineColorBlue3);
	DDX_Text(pDX, IDC_LineColorBlue4, m_LineColorBlue4);
	DDX_Text(pDX, IDC_LineColorBlue5, m_LineColorBlue5);
	DDX_Text(pDX, IDC_LineColorBlue6, m_LineColorBlue6);
	DDX_Text(pDX, IDC_LineColorBlue7, m_LineColorBlue7);
	DDX_Text(pDX, IDC_LineColorBlue8, m_LineColorBlue8);
	DDX_Text(pDX, IDC_LineColorGreen3, m_LineColorGreen3);
	DDX_Text(pDX, IDC_LineColorGreen4, m_LineColorGreen4);
	DDX_Text(pDX, IDC_LineColorGreen5, m_LineColorGreen5);
	DDX_Text(pDX, IDC_LineColorGreen6, m_LineColorGreen6);
	DDX_Text(pDX, IDC_LineColorGreen7, m_LineColorGreen7);
	DDX_Text(pDX, IDC_LineColorGreen8, m_LineColorGreen8);
	DDX_Text(pDX, IDC_LineColorRed3, m_LineColorRed3);
	DDX_Text(pDX, IDC_LineColorRed4, m_LineColorRed4);
	DDX_Text(pDX, IDC_LineColorRed5, m_LineColorRed5);
	DDX_Text(pDX, IDC_LineColorRed6, m_LineColorRed6);
	DDX_Text(pDX, IDC_LineColorRed7, m_LineColorRed7);
	DDX_Text(pDX, IDC_LineColorRed8, m_LineColorRed8);
	DDX_Text(pDX, IDC_LineStyle03, m_LineStyle03);
	DDX_Text(pDX, IDC_LineStyle04, m_LineStyle04);
	DDX_Text(pDX, IDC_LineStyle05, m_LineStyle05);
	DDX_Text(pDX, IDC_LineStyle06, m_LineStyle06);
	DDX_Text(pDX, IDC_LineStyle07, m_LineStyle07);
	DDX_Text(pDX, IDC_LineStyle08, m_LineStyle08);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAp7_StyleDLG, CDialog)
	//{{AFX_MSG_MAP(CAp7_StyleDLG)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_Border_Line_Width1, OnChangeBorderLineWidth1)
	ON_CBN_SELENDOK(IDC_Border_Line_Style1, OnSelendokBorderLineStyle1)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_Border_Line_Width2, OnChangeBorderLineWidth2)
	ON_EN_CHANGE(IDC_Border_Line_Width3, OnChangeBorderLineWidth3)
	ON_EN_CHANGE(IDC_Border_Line_Width4, OnChangeBorderLineWidth4)
	ON_EN_CHANGE(IDC_Border_Line_Width5, OnChangeBorderLineWidth5)
	ON_EN_CHANGE(IDC_Border_Line_Width6, OnChangeBorderLineWidth6)
	ON_EN_CHANGE(IDC_Border_Line_Width7, OnChangeBorderLineWidth7)
	ON_EN_CHANGE(IDC_Border_Line_Width8, OnChangeBorderLineWidth8)
	ON_CBN_SELENDOK(IDC_Border_Line_Style2, OnSelendokBorderLineStyle2)
	ON_CBN_SELENDOK(IDC_Border_Line_Style3, OnSelendokBorderLineStyle3)
	ON_CBN_SELENDOK(IDC_Border_Line_Style4, OnSelendokBorderLineStyle4)
	ON_CBN_SELENDOK(IDC_Border_Line_Style5, OnSelendokBorderLineStyle5)
	ON_CBN_SELENDOK(IDC_Border_Line_Style6, OnSelendokBorderLineStyle6)
	ON_CBN_SELENDOK(IDC_Border_Line_Style7, OnSelendokBorderLineStyle7)
	ON_CBN_SELENDOK(IDC_Border_Line_Style8, OnSelendokBorderLineStyle8)
	ON_EN_CHANGE(IDC_LineColorRed1, OnChangeLineColorRed1)
	ON_EN_CHANGE(IDC_LineColorRed2, OnChangeLineColorRed2)
	ON_EN_CHANGE(IDC_LineColorRed3, OnChangeLineColorRed3)
	ON_EN_CHANGE(IDC_LineColorRed4, OnChangeLineColorRed4)
	ON_EN_CHANGE(IDC_LineColorRed5, OnChangeLineColorRed5)
	ON_EN_CHANGE(IDC_LineColorRed6, OnChangeLineColorRed6)
	ON_EN_CHANGE(IDC_LineColorRed7, OnChangeLineColorRed7)
	ON_EN_CHANGE(IDC_LineColorRed8, OnChangeLineColorRed8)
	ON_EN_CHANGE(IDC_LineColorGreen1, OnChangeLineColorGreen1)
	ON_EN_CHANGE(IDC_LineColorGreen2, OnChangeLineColorGreen2)
	ON_EN_CHANGE(IDC_LineColorGreen3, OnChangeLineColorGreen3)
	ON_EN_CHANGE(IDC_LineColorGreen4, OnChangeLineColorGreen4)
	ON_EN_CHANGE(IDC_LineColorGreen5, OnChangeLineColorGreen5)
	ON_EN_CHANGE(IDC_LineColorGreen6, OnChangeLineColorGreen6)
	ON_EN_CHANGE(IDC_LineColorGreen7, OnChangeLineColorGreen7)
	ON_EN_CHANGE(IDC_LineColorGreen8, OnChangeLineColorGreen8)
	ON_EN_CHANGE(IDC_LineColorBlue1, OnChangeLineColorBlue1)
	ON_EN_CHANGE(IDC_LineColorBlue2, OnChangeLineColorBlue2)
	ON_EN_CHANGE(IDC_LineColorBlue3, OnChangeLineColorBlue3)
	ON_EN_CHANGE(IDC_LineColorBlue4, OnChangeLineColorBlue4)
	ON_EN_CHANGE(IDC_LineColorBlue5, OnChangeLineColorBlue5)
	ON_EN_CHANGE(IDC_LineColorBlue6, OnChangeLineColorBlue6)
	ON_EN_CHANGE(IDC_LineColorBlue7, OnChangeLineColorBlue7)
	ON_EN_CHANGE(IDC_LineColorBlue8, OnChangeLineColorBlue8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAp7_StyleDLG message handlers

BOOL CAp7_StyleDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_LineStyle1.AddString("PS_SOLID");
	m_LineStyle1.AddString("PS_DASH");
	m_LineStyle1.AddString("PS_DOT");
	m_LineStyle1.AddString("PS_DASHDOT");
	m_LineStyle1.AddString("PS_DASHDOTDOT");
	m_LineStyle1.SetTopIndex(1);
	m_LineStyle1.SetCurSel(m_LineStyle01);
	
	m_LineStyle2.AddString("PS_SOLID");
	m_LineStyle2.AddString("PS_DASH");
	m_LineStyle2.AddString("PS_DOT");
	m_LineStyle2.AddString("PS_DASHDOT");
	m_LineStyle2.AddString("PS_DASHDOTDOT");
	m_LineStyle2.SetTopIndex(1);
	m_LineStyle2.SetCurSel(m_LineStyle02);
	
	m_LineStyle3.AddString("PS_SOLID");
	m_LineStyle3.AddString("PS_DASH");
	m_LineStyle3.AddString("PS_DOT");
	m_LineStyle3.AddString("PS_DASHDOT");
	m_LineStyle3.AddString("PS_DASHDOTDOT");
	m_LineStyle3.SetTopIndex(1);
	m_LineStyle3.SetCurSel(m_LineStyle03);
	
	m_LineStyle4.AddString("PS_SOLID");
	m_LineStyle4.AddString("PS_DASH");
	m_LineStyle4.AddString("PS_DOT");
	m_LineStyle4.AddString("PS_DASHDOT");
	m_LineStyle4.AddString("PS_DASHDOTDOT");
	m_LineStyle4.SetTopIndex(1);
	m_LineStyle4.SetCurSel(m_LineStyle04);
	
	m_LineStyle5.AddString("PS_SOLID");
	m_LineStyle5.AddString("PS_DASH");
	m_LineStyle5.AddString("PS_DOT");
	m_LineStyle5.AddString("PS_DASHDOT");
	m_LineStyle5.AddString("PS_DASHDOTDOT");
	m_LineStyle5.SetTopIndex(1);
	m_LineStyle5.SetCurSel(m_LineStyle05);
	
	m_LineStyle6.AddString("PS_SOLID");
	m_LineStyle6.AddString("PS_DASH");
	m_LineStyle6.AddString("PS_DOT");
	m_LineStyle6.AddString("PS_DASHDOT");
	m_LineStyle6.AddString("PS_DASHDOTDOT");
	m_LineStyle6.SetTopIndex(1);
	m_LineStyle6.SetCurSel(m_LineStyle06);
	
	m_LineStyle7.AddString("PS_SOLID");
	m_LineStyle7.AddString("PS_DASH");
	m_LineStyle7.AddString("PS_DOT");
	m_LineStyle7.AddString("PS_DASHDOT");
	m_LineStyle7.AddString("PS_DASHDOTDOT");
	m_LineStyle7.SetTopIndex(1);
	m_LineStyle7.SetCurSel(m_LineStyle07);
	
	m_LineStyle8.AddString("PS_SOLID");
	m_LineStyle8.AddString("PS_DASH");
	m_LineStyle8.AddString("PS_DOT");
	m_LineStyle8.AddString("PS_DASHDOT");
	m_LineStyle8.AddString("PS_DASHDOTDOT");
	m_LineStyle8.SetTopIndex(1);
	m_LineStyle8.SetCurSel(m_LineStyle08);
	
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CAp7_StyleDLG::OnPaint() 
{
	CPaintDC dc(this);

	int x11=390+22, y11=29, x12=x11+20, y12=y11+17;
	CPen pen11(PS_SOLID,1,RGB(255,255,255));			dc.SelectObject(&pen11);
	dc.MoveTo(x11-1,y12+1);  dc.LineTo(x11-1,y11-1);	dc.LineTo(x12+1,y11-1);
	CPen pen12(PS_SOLID,1,RGB(128,128,128));			dc.SelectObject(&pen12);
	dc.MoveTo(x12+1,y11);	dc.LineTo(x12+1,y12+1);		dc.LineTo(x11,y12+1);
	CPen pen13(PS_SOLID,1,RGB(64,64,64));				dc.SelectObject(&pen13);
	dc.MoveTo(x12+2,y11-1);	dc.LineTo(x12+2,y12+2);		dc.LineTo(x11-1,y12+2);
	CRect rect1(x11,y11,x12,y12);	CBrush brush1(m_color1);	dc.SelectObject(&brush1);	dc.FillRect(&rect1,&brush1);

	int x21=390+22, y21=29+50, x22=x21+20, y22=y21+17;
	CPen pen21(PS_SOLID,1,RGB(255,255,255));			dc.SelectObject(&pen21);
	dc.MoveTo(x21-1,y22+1);  dc.LineTo(x21-1,y21-1);	dc.LineTo(x22+1,y21-1);
	CPen pen22(PS_SOLID,1,RGB(128,128,128));			dc.SelectObject(&pen22);
	dc.MoveTo(x22+1,y21);	dc.LineTo(x22+1,y22+1);		dc.LineTo(x21,y22+1);
	CPen pen23(PS_SOLID,1,RGB(64,64,64));				dc.SelectObject(&pen23);
	dc.MoveTo(x22+2,y21-1);	dc.LineTo(x22+2,y22+2);		dc.LineTo(x21-1,y22+2);
	CRect rect2(x21,y21,x22,y22);	CBrush brush2(m_color2);	dc.SelectObject(&brush2);	dc.FillRect(&rect2,&brush2);

	int x31=390+22, y31=29+100, x32=x31+20, y32=y31+17;
	CPen pen31(PS_SOLID,1,RGB(255,255,255));			dc.SelectObject(&pen31);
	dc.MoveTo(x31-1,y32+1);  dc.LineTo(x31-1,y31-1);	dc.LineTo(x32+1,y31-1);
	CPen pen32(PS_SOLID,1,RGB(128,128,128));			dc.SelectObject(&pen32);
	dc.MoveTo(x32+1,y31);	dc.LineTo(x32+1,y32+1);		dc.LineTo(x31,y32+1);
	CPen pen33(PS_SOLID,1,RGB(64,64,64));				dc.SelectObject(&pen33);
	dc.MoveTo(x32+2,y31-1);	dc.LineTo(x32+2,y32+2);		dc.LineTo(x31-1,y32+2);
	CRect rect3(x31,y31,x32,y32);	CBrush brush3(m_color3);	dc.SelectObject(&brush3);	dc.FillRect(&rect3,&brush3);

	int x41=390+22, y41=29+150, x42=x41+20, y42=y41+17;
	CPen pen41(PS_SOLID,1,RGB(255,255,255));			dc.SelectObject(&pen41);
	dc.MoveTo(x41-1,y42+1);  dc.LineTo(x41-1,y41-1);	dc.LineTo(x42+1,y41-1);
	CPen pen42(PS_SOLID,1,RGB(128,128,128));			dc.SelectObject(&pen42);
	dc.MoveTo(x42+1,y41);	dc.LineTo(x42+1,y42+1);		dc.LineTo(x41,y42+1);
	CPen pen43(PS_SOLID,1,RGB(64,64,64));				dc.SelectObject(&pen43);
	dc.MoveTo(x42+2,y41-1);	dc.LineTo(x42+2,y42+2);		dc.LineTo(x41-1,y42+2);
	CRect rect4(x41,y41,x42,y42);	CBrush brush4(m_color4);	dc.SelectObject(&brush4);	dc.FillRect(&rect4,&brush4);

	int x51=390+22, y51=29+200, x52=x51+20, y52=y51+17;
	CPen pen51(PS_SOLID,1,RGB(255,255,255));			dc.SelectObject(&pen51);
	dc.MoveTo(x51-1,y52+1);  dc.LineTo(x51-1,y51-1);	dc.LineTo(x52+1,y51-1);
	CPen pen52(PS_SOLID,1,RGB(128,128,128));			dc.SelectObject(&pen52);
	dc.MoveTo(x52+1,y51);	dc.LineTo(x52+1,y52+1);		dc.LineTo(x51,y52+1);
	CPen pen53(PS_SOLID,1,RGB(64,64,64));				dc.SelectObject(&pen53);
	dc.MoveTo(x52+2,y51-1);	dc.LineTo(x52+2,y52+2);		dc.LineTo(x51-1,y52+2);
	CRect rect5(x51,y51,x52,y52);	CBrush brush5(m_color5);	dc.SelectObject(&brush5);	dc.FillRect(&rect5,&brush5);

	int x61=390+22, y61=29+250, x62=x61+20, y62=y61+17;
	CPen pen61(PS_SOLID,1,RGB(255,255,255));			dc.SelectObject(&pen61);
	dc.MoveTo(x61-1,y62+1);  dc.LineTo(x61-1,y61-1);	dc.LineTo(x62+1,y61-1);
	CPen pen62(PS_SOLID,1,RGB(128,128,128));			dc.SelectObject(&pen62);
	dc.MoveTo(x62+1,y61);	dc.LineTo(x62+1,y62+1);		dc.LineTo(x61,y62+1);
	CPen pen63(PS_SOLID,1,RGB(64,64,64));				dc.SelectObject(&pen63);
	dc.MoveTo(x62+2,y61-1);	dc.LineTo(x62+2,y62+2);		dc.LineTo(x61-1,y62+2);
	CRect rect6(x61,y61,x62,y62);	CBrush brush6(m_color6);	dc.SelectObject(&brush6);	dc.FillRect(&rect6,&brush6);

	int x71=390+22, y71=29+300, x72=x71+20, y72=y71+17;
	CPen pen71(PS_SOLID,1,RGB(255,255,255));			dc.SelectObject(&pen71);
	dc.MoveTo(x71-1,y72+1);  dc.LineTo(x71-1,y71-1);	dc.LineTo(x72+1,y71-1);
	CPen pen72(PS_SOLID,1,RGB(128,128,128));			dc.SelectObject(&pen72);
	dc.MoveTo(x72+1,y71);	dc.LineTo(x72+1,y72+1);		dc.LineTo(x71,y72+1);
	CPen pen73(PS_SOLID,1,RGB(64,64,64));				dc.SelectObject(&pen73);
	dc.MoveTo(x72+2,y71-1);	dc.LineTo(x72+2,y72+2);		dc.LineTo(x71-1,y72+2);
	CRect rect7(x71,y71,x72,y72);	CBrush brush7(m_color7);	dc.SelectObject(&brush7);	dc.FillRect(&rect7,&brush7);

	int x81=390+22, y81=29+350, x82=x81+20, y82=y81+17;
	CPen pen81(PS_SOLID,1,RGB(255,255,255));			dc.SelectObject(&pen81);
	dc.MoveTo(x81-1,y82+1);  dc.LineTo(x81-1,y81-1);	dc.LineTo(x82+1,y81-1);
	CPen pen82(PS_SOLID,1,RGB(128,128,128));			dc.SelectObject(&pen82);
	dc.MoveTo(x82+1,y81);	dc.LineTo(x82+1,y82+1);		dc.LineTo(x81,y82+1);
	CPen pen83(PS_SOLID,1,RGB(64,64,64));				dc.SelectObject(&pen83);
	dc.MoveTo(x82+2,y81-1);	dc.LineTo(x82+2,y82+2);		dc.LineTo(x81-1,y82+2);
	CRect rect8(x81,y81,x82,y82);	CBrush brush8(m_color8);	dc.SelectObject(&brush8);	dc.FillRect(&rect8,&brush8);
}



void CAp7_StyleDLG::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x11=390+22,y11=29,x12=x11+20,y12=y11+17;
	if ((point.x>=x11) && (point.x<=x12) && (point.y>=y11) && (point.y<=y12) )	OnVectorLineColor1();	

	int x21=390+22, y21=29+50, x22=x21+20, y22=y21+17;
	if ((point.x>=x21) && (point.x<=x22) && (point.y>=y21) && (point.y<=y22) )	OnVectorLineColor2();	

	int x31=390+22, y31=29+100, x32=x31+20, y32=y31+17;
	if ((point.x>=x31) && (point.x<=x32) && (point.y>=y31) && (point.y<=y32) )	OnVectorLineColor3();	

	int x41=390+22, y41=29+150, x42=x41+20, y42=y41+17;
	if ((point.x>=x41) && (point.x<=x42) && (point.y>=y41) && (point.y<=y42) )	OnVectorLineColor4();	

	int x51=390+22, y51=29+200, x52=x51+20, y52=y51+17;
	if ((point.x>=x51) && (point.x<=x52) && (point.y>=y51) && (point.y<=y52) )	OnVectorLineColor5();	

	int x61=390+22, y61=29+250, x62=x61+20, y62=y61+17;
	if ((point.x>=x61) && (point.x<=x62) && (point.y>=y61) && (point.y<=y62) )	OnVectorLineColor6();	

	int x71=390+22, y71=29+300, x72=x71+20, y72=y71+17;
	if ((point.x>=x71) && (point.x<=x72) && (point.y>=y71) && (point.y<=y72) )	OnVectorLineColor7();	

	int x81=390+22, y81=29+350, x82=x81+20, y82=y81+17;
	if ((point.x>=x81) && (point.x<=x82) && (point.y>=y81) && (point.y<=y82) )	OnVectorLineColor8();	

	CDialog::OnLButtonDown(nFlags, point);
}

void CAp7_StyleDLG::OnVectorLineColor1() 
{
	CColorDialog xx(m_color1, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed1=GetRValue(ZZ);
		m_LineColorGreen1=GetGValue(ZZ);
		m_LineColorBlue1=GetBValue(ZZ);
		m_color1=ZZ;
		Invalidate();
		UpdateData(false);
	}
}
void CAp7_StyleDLG::OnVectorLineColor2() 
{
	CColorDialog xx(m_color2, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed2=GetRValue(ZZ);
		m_LineColorGreen2=GetGValue(ZZ);
		m_LineColorBlue2=GetBValue(ZZ);
		m_color2=ZZ;
		Invalidate();
		UpdateData(false);
	}
}
void CAp7_StyleDLG::OnVectorLineColor3() 
{
	CColorDialog xx(m_color3, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed3=GetRValue(ZZ);
		m_LineColorGreen3=GetGValue(ZZ);
		m_LineColorBlue3=GetBValue(ZZ);
		m_color3=ZZ;
		Invalidate();
		UpdateData(false);
	}
}
void CAp7_StyleDLG::OnVectorLineColor4() 
{
	CColorDialog xx(m_color4, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed4=GetRValue(ZZ);
		m_LineColorGreen4=GetGValue(ZZ);
		m_LineColorBlue4=GetBValue(ZZ);
		m_color4=ZZ;
		Invalidate();
		UpdateData(false);
	}
}
void CAp7_StyleDLG::OnVectorLineColor5() 
{
	CColorDialog xx(m_color5, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed5=GetRValue(ZZ);
		m_LineColorGreen5=GetGValue(ZZ);
		m_LineColorBlue5=GetBValue(ZZ);
		m_color5=ZZ;
		Invalidate();
		UpdateData(false);
	}
}
void CAp7_StyleDLG::OnVectorLineColor6() 
{
	CColorDialog xx(m_color6, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed6=GetRValue(ZZ);
		m_LineColorGreen6=GetGValue(ZZ);
		m_LineColorBlue6=GetBValue(ZZ);
		m_color6=ZZ;
		Invalidate();
		UpdateData(false);
	}
}
void CAp7_StyleDLG::OnVectorLineColor7() 
{
	CColorDialog xx(m_color7, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed7=GetRValue(ZZ);
		m_LineColorGreen7=GetGValue(ZZ);
		m_LineColorBlue7=GetBValue(ZZ);
		m_color7=ZZ;
		Invalidate();
		UpdateData(false);
	}
}
void CAp7_StyleDLG::OnVectorLineColor8() 
{
	CColorDialog xx(m_color8, CC_FULLOPEN);
	if	(xx.DoModal()==IDOK)
	{
		COLORREF ZZ=xx.GetColor();
		UpdateData(true);
		m_LineColorRed8=GetRValue(ZZ);
		m_LineColorGreen8=GetGValue(ZZ);
		m_LineColorBlue8=GetBValue(ZZ);
		m_color8=ZZ;
		Invalidate();
		UpdateData(false);
	}
}


void CAp7_StyleDLG::OnChangeBorderLineWidth1() 
{
	UpdateData(true);
	if (m_LineWidth1>1)
	{
		m_LineStyle01=0;
		m_LineStyle1.SetCurSel(0);
	}
	UpdateData(false);		
}
void CAp7_StyleDLG::OnChangeBorderLineWidth2() 
{
	UpdateData(true);
	if (m_LineWidth2>1)
	{
		m_LineStyle02=0;
		m_LineStyle2.SetCurSel(0);
	}
	UpdateData(false);	
}
void CAp7_StyleDLG::OnChangeBorderLineWidth3() 
{
	UpdateData(true);
	if (m_LineWidth3>1)
	{
		m_LineStyle03=0;
		m_LineStyle3.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnChangeBorderLineWidth4() 
{
	UpdateData(true);
	if (m_LineWidth4>1)
	{
		m_LineStyle04=0;
		m_LineStyle4.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnChangeBorderLineWidth5() 
{
	UpdateData(true);
	if (m_LineWidth5>1)
	{
		m_LineStyle05=0;
		m_LineStyle5.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnChangeBorderLineWidth6() 
{
	UpdateData(true);
	if (m_LineWidth6>1)
	{
		m_LineStyle06=0;
		m_LineStyle6.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnChangeBorderLineWidth7() 
{
	UpdateData(true);
	if (m_LineWidth7>1)
	{
		m_LineStyle07=0;
		m_LineStyle7.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnChangeBorderLineWidth8() 
{
	UpdateData(true);
	if (m_LineWidth8>1)
	{
		m_LineStyle08=0;
		m_LineStyle8.SetCurSel(0);
	}
	UpdateData(false);
}


void CAp7_StyleDLG::OnSelendokBorderLineStyle1() 
{
	UpdateData(true);
	m_LineStyle01=m_LineStyle1.GetCurSel();

	if (m_LineWidth1>1)
	{
		m_LineStyle01=0;
		m_LineStyle1.SetCurSel(0);
	}
	UpdateData(false);	
}
void CAp7_StyleDLG::OnSelendokBorderLineStyle2() 
{
	UpdateData(true);
	m_LineStyle02=m_LineStyle2.GetCurSel();

	if (m_LineWidth2>1)
	{
		m_LineStyle02=0;
		m_LineStyle2.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnSelendokBorderLineStyle3() 
{
	UpdateData(true);
	m_LineStyle03=m_LineStyle3.GetCurSel();

	if (m_LineWidth3>1)
	{
		m_LineStyle03=0;
		m_LineStyle3.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnSelendokBorderLineStyle4() 
{
	UpdateData(true);
	m_LineStyle04=m_LineStyle4.GetCurSel();

	if (m_LineWidth4>1)
	{
		m_LineStyle04=0;
		m_LineStyle4.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnSelendokBorderLineStyle5() 
{
	UpdateData(true);
	m_LineStyle05=m_LineStyle5.GetCurSel();

	if (m_LineWidth5>1)
	{
		m_LineStyle05=0;
		m_LineStyle5.SetCurSel(0);
	}
	UpdateData(false);	
}

void CAp7_StyleDLG::OnSelendokBorderLineStyle6() 
{
	UpdateData(true);
	m_LineStyle06=m_LineStyle6.GetCurSel();

	if (m_LineWidth6>1)
	{
		m_LineStyle06=0;
		m_LineStyle6.SetCurSel(0);
	}
	UpdateData(false);	
}
void CAp7_StyleDLG::OnSelendokBorderLineStyle7() 
{
	UpdateData(true);
	m_LineStyle07=m_LineStyle7.GetCurSel();

	if (m_LineWidth7>1)
	{
		m_LineStyle07=0;
		m_LineStyle7.SetCurSel(0);
	}
	UpdateData(false);
}
void CAp7_StyleDLG::OnSelendokBorderLineStyle8() 
{
	UpdateData(true);
	m_LineStyle08=m_LineStyle8.GetCurSel();

	if (m_LineWidth8>1)
	{
		m_LineStyle08=0;
		m_LineStyle8.SetCurSel(0);
	}
	UpdateData(false);
}

//////////////////////////////////////////////////////////////
void CAp7_StyleDLG::OnChangeLineColorRed1() 
{
	int x11=390+22, y11=29, x12=x11+20, y12=y11+17;
	CRect rect1(x11,y11,x12,y12);

	UpdateData(true);
	m_color1 = RGB(m_LineColorRed1,m_LineColorGreen1,m_LineColorBlue1);
	InvalidateRect(rect1,FALSE);
	UpdateData(false);	
}
void CAp7_StyleDLG::OnChangeLineColorRed2() 
{
	int x21=390+22, y21=29+50, x22=x21+20, y22=y21+17;
	CRect rect2(x21,y21,x22,y22);

	UpdateData(true);
	m_color2 = RGB(m_LineColorRed2,m_LineColorGreen2,m_LineColorBlue2);
	InvalidateRect(rect2,FALSE);
	UpdateData(false);	
}
void CAp7_StyleDLG::OnChangeLineColorRed3() 
{
	int x31=390+22, y31=29+100, x32=x31+20, y32=y31+17;
	CRect rect3(x31,y31,x32,y32);

	UpdateData(true);
	m_color3 = RGB(m_LineColorRed3,m_LineColorGreen3,m_LineColorBlue3);
	InvalidateRect(rect3,FALSE);
	UpdateData(false);	
}
void CAp7_StyleDLG::OnChangeLineColorRed4() 
{
	int x41=390+22, y41=29+150, x42=x41+20, y42=y41+17;
	CRect rect4(x41,y41,x42,y42);

	UpdateData(true);
	m_color4 = RGB(m_LineColorRed4,m_LineColorGreen4,m_LineColorBlue4);
	InvalidateRect(rect4,FALSE);
	UpdateData(false);	
}
void CAp7_StyleDLG::OnChangeLineColorRed5() 
{
	int x51=390+22, y51=29+200, x52=x51+20, y52=y51+17;
	CRect rect5(x51,y51,x52,y52);

	UpdateData(true);
	m_color5 = RGB(m_LineColorRed5,m_LineColorGreen5,m_LineColorBlue5);
	InvalidateRect(rect5,FALSE);
	UpdateData(false);	
}
void CAp7_StyleDLG::OnChangeLineColorRed6() 
{
	int x61=390+22, y61=29+250, x62=x61+20, y62=y61+17;
	CRect rect6(x61,y61,x62,y62);

	UpdateData(true);
	m_color6 = RGB(m_LineColorRed6,m_LineColorGreen6,m_LineColorBlue6);
	InvalidateRect(rect6,FALSE);
	UpdateData(false);	
}
void CAp7_StyleDLG::OnChangeLineColorRed7() 
{
	int x71=390+22, y71=29+300, x72=x71+20, y72=y71+17;
	CRect rect7(x71,y71,x72,y72);

	UpdateData(true);
	m_color7 = RGB(m_LineColorRed7,m_LineColorGreen7,m_LineColorBlue7);
	InvalidateRect(rect7,FALSE);
	UpdateData(false);	
}
void CAp7_StyleDLG::OnChangeLineColorRed8() 
{
	int x81=390+22, y81=29+350, x82=x81+20, y82=y81+17;
	CRect rect8(x81,y81,x82,y82);

	UpdateData(true);
	m_color8 = RGB(m_LineColorRed8,m_LineColorGreen8,m_LineColorBlue8);
	InvalidateRect(rect8,FALSE);
	UpdateData(false);	
}

void CAp7_StyleDLG::OnChangeLineColorGreen1() 
{
	OnChangeLineColorRed1();	
}
void CAp7_StyleDLG::OnChangeLineColorGreen2() 
{
	OnChangeLineColorRed2();	
}
void CAp7_StyleDLG::OnChangeLineColorGreen3() 
{
	OnChangeLineColorRed3();	
}
void CAp7_StyleDLG::OnChangeLineColorGreen4() 
{
	OnChangeLineColorRed4();	
}
void CAp7_StyleDLG::OnChangeLineColorGreen5() 
{
	OnChangeLineColorRed5();	
}
void CAp7_StyleDLG::OnChangeLineColorGreen6() 
{
	OnChangeLineColorRed6();	
}
void CAp7_StyleDLG::OnChangeLineColorGreen7() 
{
	OnChangeLineColorRed7();	
}
void CAp7_StyleDLG::OnChangeLineColorGreen8() 
{
	OnChangeLineColorRed8();	
}

void CAp7_StyleDLG::OnChangeLineColorBlue1() 
{
	OnChangeLineColorRed1();	
}
void CAp7_StyleDLG::OnChangeLineColorBlue2() 
{
	OnChangeLineColorRed2();	
}
void CAp7_StyleDLG::OnChangeLineColorBlue3() 
{
	OnChangeLineColorRed3();	
}
void CAp7_StyleDLG::OnChangeLineColorBlue4() 
{
	OnChangeLineColorRed4();	
}
void CAp7_StyleDLG::OnChangeLineColorBlue5() 
{
	OnChangeLineColorRed5();	
}
void CAp7_StyleDLG::OnChangeLineColorBlue6() 
{
	OnChangeLineColorRed6();	
}
void CAp7_StyleDLG::OnChangeLineColorBlue7() 
{
	OnChangeLineColorRed7();	
}
void CAp7_StyleDLG::OnChangeLineColorBlue8() 
{
	OnChangeLineColorRed8();	
}
