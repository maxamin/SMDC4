// TBEpolar.cpp : implementation file
//

#include "stdafx.h"
#include "thalesdrawdll.h"
#include "TBEpolar.h"
#include <math.h>

#include "FileDLG_ChangedType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTBEpolar dialog


CTBEpolar::CTBEpolar(CWnd* pParent /*=NULL*/)
	: CDialog(CTBEpolar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTBEpolar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTBEpolar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTBEpolar)
	DDX_Control(pDX, IDC_COMBO_Time, m_COMBO_Time);
	DDX_Control(pDX, IDC_COMBO_Fr, m_COMBO_Fr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTBEpolar, CDialog)
	//{{AFX_MSG_MAP(CTBEpolar)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_CBN_SELCHANGE(IDC_COMBO_Fr, OnSelchangeCOMBOFr)
	ON_CBN_SELCHANGE(IDC_COMBO_Time, OnSelchangeCOMBOTime)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_googleEarth, OnBUTTONgoogleEarth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTBEpolar message handlers

BOOL CTBEpolar::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CThalesDrawDLLApp *)AfxGetApp())->m_Lang = m_Lang;

	////////////////////////Path Application////////////////////////////////////
	m_AppPath = GetCommandLine();
	int zz = m_AppPath.ReverseFind('\\');
	m_AppPath.Delete(zz,m_AppPath.GetLength()-zz);
	zz = m_AppPath.ReverseFind('\\')+1;
	m_AppPath.Delete(zz,m_AppPath.GetLength()-zz);
	m_AppPath.Delete(0);
	///////////////////////////////////////////////////////////////////////////

	m_fill = true;
	m_5degreestick = 2;
	ColorMap(m_colormaptype);

	CString str = m_flagLQ  ?  _Z("Direction-Level") : _Z("Direction-Quality");
	SetWindowText(str);

	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(m_flagLQ);
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(!m_flagLQ);

	m_single = TRUE;
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(!m_single);
	m_i = 0;
	
	for(long i=0;i<m_FreqUniq.GetSize();i++)
		m_COMBO_Fr.AddString(m_FreqUniq.GetAt(i));
	m_COMBO_Fr.SetCurSel(0);

	for( i=0;i<m_ListDateTime.GetSize();i++)
		m_COMBO_Time.AddString(m_ListDateTime.GetAt(i));
	m_COMBO_Time.SetCurSel(0);

	GetFrequency();
	Set_Static_R();

	GetDlgItem(IDC_RADIO1)->EnableWindow(m_L.GetSize()>0);
	GetDlgItem(IDC_RADIO2)->EnableWindow(m_Q.GetSize()>0);

	((CThalesDrawDLLApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}
void CTBEpolar::Set_Static_R() 
{
	CString str;
	str.Format(_T("%ld of %ld") , m_i+1 , m_D.GetSize());
	GetDlgItem(IDC_STATIC_R)->SetWindowText(str);

	if((m_single)||(m_D.GetSize()==1))
	{
		str.Format(_T("%g") , m_D.GetAt(m_i));	GetDlgItem(IDC_STATIC_D )->SetWindowText(str);

		if(m_L.GetSize()>0)	str.Format(_T("%g") , m_L.GetAt(m_i));
		else				str.Format(_T("") );
		GetDlgItem(IDC_STATIC_L )->SetWindowText(str);

		if(m_Q.GetSize()>0)	str.Format(_T("%g") , m_Q.GetAt(m_i));
		else				str.Format(_T("") );
		GetDlgItem(IDC_STATIC_Q )->SetWindowText(str);

		if(m_Lu == _T("dB�V/m"))	m_Lu = _T("dBuV/m");
		else if(m_Lu == _T("dB�V"))	m_Lu = _T("dBuV");

		str.Format(_Z("Level")+"(%s)" , m_Lu);	GetDlgItem(IDC_STATIC_L0)->SetWindowText(str);
	}
	else
	{
		GetDlgItem(IDC_STATIC_L )->SetWindowText(_T(""));
		GetDlgItem(IDC_STATIC_Q )->SetWindowText(_T(""));
		GetDlgItem(IDC_STATIC_D )->SetWindowText(_T(""));
	}
}

void CTBEpolar::DrawPattern(int HV,int x0,int y0,int radius,int offset) 
{
	CClientDC dc(this);
	CString str;
	double az,pi=4.0*atan(1.0);
	int i,x,y, x01,y01;
	int radius1 = radius;	

	double step=radius/10.0;
	radius1=radius;
//////////////////////////////Draw Diagram//////////////////////////////////////////////
	double a,r;
	CPoint pointH[361];
	for ( i=0;i<360;i++)
	{
		r = radius-(step/5.0)*min(50.0, 0 );
		a = ((double)(i))*pi/180.0;
		x = int(x0+r*sin(a));
		y = int(y0-r*cos(a));
		pointH[i] = CPoint(x,y);
	}
	pointH[360]=pointH[0];

	if (m_fill)
	{
		CBrush brush(m_fillcolor);
		dc.SelectObject(&brush);
		dc.Polygon(pointH,361);
	}

///////////////////////////////////////////////////////////////////////////////////////
	for (i=0;i<36*m_5degreestick;i++)
	{
		int L = (i*10/m_5degreestick)%10;
		if(L==0)	L = 10;
		az = (i*10.0/m_5degreestick)*pi/180.0;
		x = int(x0 + (radius+L)*sin(az));
		y = int(y0 - (radius+L)*cos(az));

		x01 = int(x0 + radius*sin(az));
		y01 = int(y0 - radius*cos(az));

		DrawLine(x01,y01,x,y,PS_SOLID,1,RGB(0,0,0));
	}

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextAlign(TA_CENTER);
	for (i=0;i<36;i++)
	{
		az=(i*10.0)*pi/180.0;
		x = int(   x0-radius-12-6 + (radius+12+6)*(1.0 + sin(az))   );
		y = int(   y0-radius-20-5 + (radius+12+6)*(1.0 - cos(az))   );

		str.Format("%d",i*10);
		if	   (i==0)		dc.TextOut(x,y,_T("N"));
		else if(i== 9)		dc.TextOut(x,y,_T("E"));
		else if(i==18)		dc.TextOut(x,y,_T("S"));
		else if(i==27)		dc.TextOut(x,y,_T("W"));
		else				dc.TextOut(x,y,str);
	}

	long N = m_D.GetSize();
	double v , vMax , vMin;
	int c , X1 , Y1;

	if(m_flagLQ)	{vMax = m_Lmax;	vMin = m_Lmin;}
	else			{vMax = m_Qmax;	vMin = m_Qmin;}


	if(m_single)
	{
		if(m_flagLQ)	v = m_L.GetAt(m_i);
		else			v = m_Q.GetAt(m_i);
		a = (m_D.GetAt(m_i))*pi/180.0;

		c = Contour(v , vMin , vMax , 255) ;
		v = 40.0*(vMax-v)/(vMax-vMin);

		r = radius-(step/5.0)*min(40.0, v );
		X1 = int(x0+r*sin(a));
		Y1 = int(y0-r*cos(a));
		DrawLine(x0,y0,X1,Y1,PS_SOLID,m_ThickLines,RGBt[c]);
	}
	else
	{
		for (i=0;i<N;i++)
		{
			if(m_flagLQ)	v = m_L.GetAt(i);
			else			v = m_Q.GetAt(i);
			a = (m_D.GetAt(i))*pi/180.0;

			c = Contour(v , vMin , vMax , 255) ;
			v = 40.0*(vMax-v)/(vMax-vMin);

			r = radius-(step/5.0)*min(40.0, v );
			X1 = int(x0+r*sin(a));
			Y1 = int(y0-r*cos(a));
			DrawLine(x0,y0,X1,Y1,PS_SOLID,m_ThickLines,RGBt[c]);
		}
	}
}

void CTBEpolar::DrawEllipse(BOOL nMode,int x1,int y1,int x2,int y2,int nStyle,int nWidth,COLORREF pColor,int x3,int y3,int x4,int y4,COLORREF bColor) 
{
	CClientDC dc(this);
	CBrush brush(bColor);
	CBrush* OLDbrush = dc.SelectObject(&brush);
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = dc.SelectObject(&pen);

	if (nMode)	dc.Ellipse(x1,y1,x2,y2);
	else		dc.Arc(x1,y1,x2,y2,x3,y3,x4,y4);

	dc.SelectObject(OLDbrush);
	dc.SelectObject(OLDpen);
}

void CTBEpolar::DrawLine(int x1,int y1,int x2,int y2,int nStyle,int nWidth,COLORREF pColor) 
{
	CClientDC dc(this);
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = dc.SelectObject(&pen);
	dc.MoveTo(x1,y1);
	dc.LineTo(x2,y2);
	dc.SelectObject(OLDpen);
}

void CTBEpolar::OnPaint() 
{
	CPaintDC dc(this); 
	DrawPattern(true,170+25,180+25,160,25);
}

int CTBEpolar::Contour(double y,double MinV,double MaxV,int nL) 
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
			c=int((b1+b2)/2.0);
		//	c=int(b1);
		}
	}
	return c;
}


void CTBEpolar::ColorMap(CString type)
{
	if (type=="Topo_1")
	{
		RGBt[  0] = RGB(      0,      0,      150);
		RGBt[  1] = RGB(      0,      0,      130);
		RGBt[  2] = RGB(      0,      0,      110);
		RGBt[  3] = RGB(      0,      0,      100);
		RGBt[  4] = RGB(      0,      0,      90);
		RGBt[  5] = RGB(      0,  6.208,      80);
		RGBt[  6] = RGB(      0, 12.667,      70);
		RGBt[  7] = RGB(      0, 19.065,      60);
		RGBt[  8] = RGB(      0,   25.4,      50);
		RGBt[  9] = RGB(      0, 32.624,      40);
		RGBt[ 10] = RGB(      0,  40.76,      30);
		RGBt[ 11] = RGB(      0, 47.605,      20);
		RGBt[ 12] = RGB(      0, 50.939,      10);
		RGBt[ 13] = RGB(      0,     51,      0);
		RGBt[ 14] = RGB(      0,     51,      0);
		RGBt[ 15] = RGB(      0,     51,      0);
		RGBt[ 16] = RGB(      0,     51,      0);
		RGBt[ 17] = RGB(      0, 53.704,      0);
		RGBt[ 18] = RGB(      0, 61.943,      0);
		RGBt[ 19] = RGB(      0,  71.19,      0);
		RGBt[ 20] = RGB(      0, 76.741,      0);
		RGBt[ 21] = RGB(      0,     77,      0);
		RGBt[ 22] = RGB(      0,     77,      0);
		RGBt[ 23] = RGB(      0,     77,      0);
		RGBt[ 24] = RGB(      0,     77,      0);
		RGBt[ 25] = RGB(      0, 79.061,      0);
		RGBt[ 26] = RGB(      0, 86.655,      0);
		RGBt[ 27] = RGB(      0, 95.649,      0);
		RGBt[ 28] = RGB(      0,101.519,      0);
		RGBt[ 29] = RGB(      0,    102,      0);
		RGBt[ 30] = RGB(      0,    102,      0);
		RGBt[ 31] = RGB(      0,    102,      0);
		RGBt[ 32] = RGB(      0,    102,      0);
		RGBt[ 33] = RGB(      0,102.378,      0);
		RGBt[ 34] = RGB(      0,104.112,      0);
		RGBt[ 35] = RGB(      0,106.285,      0);
		RGBt[ 36] = RGB(      0,107.812,      0);
		RGBt[ 37] = RGB(      0,    108,      0);
		RGBt[ 38] = RGB(      0,    108,      0);
		RGBt[ 39] = RGB(      0,    108,      0);
		RGBt[ 40] = RGB(      0,    108,      0);
		RGBt[ 41] = RGB(      0,110.066,      0);
		RGBt[ 42] = RGB(      0,122.331,      0);
		RGBt[ 43] = RGB(      0,138.669,      0);
		RGBt[ 44] = RGB(      0,150.934,      0);
		RGBt[ 45] = RGB(      0,    153,      0);
		RGBt[ 46] = RGB(      0,    153,      0);
		RGBt[ 47] = RGB(      0,    153,      0);
		RGBt[ 48] = RGB(      0,    153,      0);
		RGBt[ 49] = RGB(      0,153.813,      0);
		RGBt[ 50] = RGB(      0, 160.43,      0);
		RGBt[ 51] = RGB(      0,169.848,      0);
		RGBt[ 52] = RGB(      0,177.362,      0);
		RGBt[ 53] = RGB(      0,    179,      0);
		RGBt[ 54] = RGB(      0,    179,      0);
		RGBt[ 55] = RGB(      0,    179,      0);
		RGBt[ 56] = RGB(      0,    179,      0);
		RGBt[ 57] = RGB(      0,179.481,      0);
		RGBt[ 58] = RGB(      0,185.351,      0);
		RGBt[ 59] = RGB(      0,194.345,      0);
		RGBt[ 60] = RGB(      0,201.939,      0);
		RGBt[ 61] = RGB(      0,    204,      0);
		RGBt[ 62] = RGB(      0,    204,      0);
		RGBt[ 63] = RGB(      0,    204,      0);
		RGBt[ 64] = RGB(      0,    204,      0);
		RGBt[ 65] = RGB(      0,204.259,      0);
		RGBt[ 66] = RGB(      0, 209.81,      0);
		RGBt[ 67] = RGB(      0,219.057,      0);
		RGBt[ 68] = RGB(      0,227.296,      0);
		RGBt[ 69] = RGB(      0,    230,      0);
		RGBt[ 70] = RGB(      0,    230,      0);
		RGBt[ 71] = RGB(      0,    230,      0);
		RGBt[ 72] = RGB(      0,    230,      0);
		RGBt[ 73] = RGB(      0,230.091,      0);
		RGBt[ 74] = RGB(      0,234.854,      0);
		RGBt[ 75] = RGB(      0,243.602,      0);
		RGBt[ 76] = RGB(      0,251.811,      0);
		RGBt[ 77] = RGB(      0,    255,      0);
		RGBt[ 78] = RGB(      0,    255,      0);
		RGBt[ 79] = RGB(      0,    255,      0);
		RGBt[ 80] = RGB(      0,    255,      0);
		RGBt[ 81] = RGB(  0.053,    255,      0);
		RGBt[ 82] = RGB( 21.285,    255,      0);
		RGBt[ 83] = RGB( 65.129,    255,      0);
		RGBt[ 84] = RGB(108.422,    255,      0);
		RGBt[ 85] = RGB(    128,    255,      0);
		RGBt[ 86] = RGB(    128,    255,      0);
		RGBt[ 87] = RGB(    128,    255,      0);
		RGBt[ 88] = RGB(    128,    255,      0);
		RGBt[ 89] = RGB(    128,    255,      0);
		RGBt[ 90] = RGB(130.422,    255,      0);
		RGBt[ 91] = RGB(136.769,    255,      0);
		RGBt[ 92] = RGB( 144.83,    255,      0);
		RGBt[ 93] = RGB(152.387,    255,      0);
		RGBt[ 94] = RGB(159.752,    255,      0);
		RGBt[ 95] = RGB(168.216,    255,      0);
		RGBt[ 96] = RGB( 175.41,    255,      0);
		RGBt[ 97] = RGB(178.936,    255,      0);
		RGBt[ 98] = RGB(    179,    255,      0);
		RGBt[ 99] = RGB(    179,    255,      0);
		RGBt[100] = RGB(    179,    255,      0);
		RGBt[101] = RGB(    179,    255,      0);
		RGBt[102] = RGB(    179,    255,      0);
		RGBt[103] = RGB(    179,    255,      0);
		RGBt[104] = RGB(    179,    255,      0);
		RGBt[105] = RGB(    179,    255,      0);
		RGBt[106] = RGB(181.324,    255,      0);
		RGBt[107] = RGB(189.087,    255,      0);
		RGBt[108] = RGB(198.035,    255,      0);
		RGBt[109] = RGB(203.644,    255,      0);
		RGBt[110] = RGB(    204,    255,      0);
		RGBt[111] = RGB(    204,    255,      0);
		RGBt[112] = RGB(    204,    255,      0);
		RGBt[113] = RGB(    204,    255,      0);
		RGBt[114] = RGB(205.884,    255,      0);
		RGBt[115] = RGB(213.595,    255,      0);
		RGBt[116] = RGB(222.986,    255,      0);
		RGBt[117] = RGB(229.352,    255,      0);
		RGBt[118] = RGB(    230,    255,      0);
		RGBt[119] = RGB(    230,    255,      0);
		RGBt[120] = RGB(    230,    255,      0);
		RGBt[121] = RGB(    230,    255,      0);
		RGBt[122] = RGB(231.354,    255,  2.437);
		RGBt[123] = RGB(238.379,    255, 15.082);
		RGBt[124] = RGB( 247.45,    255, 31.409);
		RGBt[125] = RGB(254.043,    255, 43.278);
		RGBt[126] = RGB(    255,    255, 42.934);
		RGBt[127] = RGB(    255,    255, 30.669);
		RGBt[128] = RGB(    255,    255, 14.331);
		RGBt[129] = RGB(    255,    255,  2.066);
		RGBt[130] = RGB(    255,254.043,      0);
		RGBt[131] = RGB(    255, 247.45,      0);
		RGBt[132] = RGB(    255,238.379,      0);
		RGBt[133] = RGB(    255,231.354,      0);
		RGBt[134] = RGB(    255,    230,      0);
		RGBt[135] = RGB(    255,    230,      0);
		RGBt[136] = RGB(    255,    230,      0);
		RGBt[137] = RGB(    255,    230,      0);
		RGBt[138] = RGB(    255,229.352,      0);
		RGBt[139] = RGB(    255,222.986,      0);
		RGBt[140] = RGB(    255,213.595,      0);
		RGBt[141] = RGB(    255,205.884,      0);
		RGBt[142] = RGB(    255,    204,      0);
		RGBt[143] = RGB(    255,    204,      0);
		RGBt[144] = RGB(    255,    204,      0);
		RGBt[145] = RGB(    255,    204,      0);
		RGBt[146] = RGB(    255,203.644,      0);
		RGBt[147] = RGB(    255,198.035,      0);
		RGBt[148] = RGB(    255,189.087,      0);
		RGBt[149] = RGB(    255,181.324,      0);
		RGBt[150] = RGB(    255,    179,      0);
		RGBt[151] = RGB(    255,    179,      0);
		RGBt[152] = RGB(    255,    179,      0);
		RGBt[153] = RGB(    255,    179,      0);
		RGBt[154] = RGB(    255,178.833,      0);
		RGBt[155] = RGB(    255,173.576,      0);
		RGBt[156] = RGB(    255,164.398,      0);
		RGBt[157] = RGB(    255,156.004,      0);
		RGBt[158] = RGB(    255,    153,      0);
		RGBt[159] = RGB(    255,    153,      0);
		RGBt[160] = RGB(    255,    153,      0);
		RGBt[161] = RGB(    255,    153,      0);
		RGBt[162] = RGB(254.959,152.959,      0);
		RGBt[163] = RGB(250.499,148.499,      0);
		RGBt[164] = RGB(241.839,139.839,      0);
		RGBt[165] = RGB(233.501,131.501,      0);
		RGBt[166] = RGB(    230,    128,      0);
		RGBt[167] = RGB(    230,    128,      0);
		RGBt[168] = RGB(    230,    128,      0);
		RGBt[169] = RGB(    230,    128,      0);
		RGBt[170] = RGB(    230,    128,      0);
		RGBt[171] = RGB(226.023,124.023,      0);
		RGBt[172] = RGB(217.229,115.229,      0);
		RGBt[173] = RGB(208.324,106.324,      0);
		RGBt[174] = RGB(204.011,102.011,      0);
		RGBt[175] = RGB(    204,    102,      0);
		RGBt[176] = RGB(    204,    102,      0);
		RGBt[177] = RGB(    204,    102,      0);
		RGBt[178] = RGB(    204,    102,      0);
		RGBt[179] = RGB(200.811, 98.811,      0);
		RGBt[180] = RGB(192.602, 90.602,      0);
		RGBt[181] = RGB(183.854, 81.854,      0);
		RGBt[182] = RGB(179.091, 77.091,      0);
		RGBt[183] = RGB(    179,     77,      0);
		RGBt[184] = RGB(    179,     77,      0);
		RGBt[185] = RGB(    179,     77,      0);
		RGBt[186] = RGB(    179,     77,      0);
		RGBt[187] = RGB(176.296, 74.296,      0);
		RGBt[188] = RGB(168.057, 66.057,      0);
		RGBt[189] = RGB( 158.81,  56.81,      0);
		RGBt[190] = RGB(153.259, 51.259,      0);
		RGBt[191] = RGB(    153,     51,      0);
		RGBt[192] = RGB(    153,     51,      0);
		RGBt[193] = RGB(    153,     51,      0);
		RGBt[194] = RGB(    153,     51,      0);
		RGBt[195] = RGB(150.939, 48.939,      0);
		RGBt[196] = RGB(143.345, 41.345,      0);
		RGBt[197] = RGB(134.351, 32.351,      0);
		RGBt[198] = RGB(128.481, 26.481,      0);
		RGBt[199] = RGB(    128,     26,      0);
		RGBt[200] = RGB(    128,     26,      0);
		RGBt[201] = RGB(    128,     26,      0);
		RGBt[202] = RGB(    128,     26,      0);
		RGBt[203] = RGB(126.362, 24.362,      0);
		RGBt[204] = RGB(118.848, 16.848,      0);
		RGBt[205] = RGB( 109.43,   7.43,      0);
		RGBt[206] = RGB(102.813,  0.813,      0);
		RGBt[207] = RGB(    102,      0,      0);
		RGBt[208] = RGB(    102,      0,      0);
		RGBt[209] = RGB(    102,      0,      0);
		RGBt[210] = RGB(    102,      0,      0);
		RGBt[211] = RGB( 99.659,  2.341,  3.535);
		RGBt[212] = RGB( 85.758, 16.242, 24.523);
		RGBt[213] = RGB( 67.242, 34.758, 52.477);
		RGBt[214] = RGB( 53.341, 48.659, 73.465);
		RGBt[215] = RGB(     51,     51,     77);
		RGBt[216] = RGB(     51,     51,     77);
		RGBt[217] = RGB(     51,     51,     77);
		RGBt[218] = RGB(     51,     51,     77);
		RGBt[219] = RGB( 51.813, 51.813, 77.781);
		RGBt[220] = RGB(  58.43,  58.43, 84.144);
		RGBt[221] = RGB( 67.848, 67.848,   93.2);
		RGBt[222] = RGB( 75.362, 75.362,100.425);
		RGBt[223] = RGB(     77,     77,    102);
		RGBt[224] = RGB(     77,     77,    102);
		RGBt[225] = RGB(     77,     77,    102);
		RGBt[226] = RGB(     77,     77,    102);
		RGBt[227] = RGB( 77.981, 77.981,102.981);
		RGBt[228] = RGB( 89.956, 89.956,114.956);
		RGBt[229] = RGB(108.304,108.304,133.304);
		RGBt[230] = RGB(123.796,123.796,148.796);
		RGBt[231] = RGB(    128,    128,    153);
		RGBt[232] = RGB(    128,    128,    153);
		RGBt[233] = RGB(    128,    128,    153);
		RGBt[234] = RGB(    128,    128,    153);
		RGBt[235] = RGB(128.249,128.249,153.259);
		RGBt[236] = RGB(133.586,133.586, 158.81);
		RGBt[237] = RGB(142.478,142.478,168.057);
		RGBt[238] = RGB(  150.4,  150.4,176.296);
		RGBt[239] = RGB(    153,    153,    179);
		RGBt[240] = RGB(    153,    153,    179);
		RGBt[241] = RGB(    153,    153,    179);
		RGBt[242] = RGB(    153,    153,    179);
		RGBt[243] = RGB(153.095,153.095,179.091);
		RGBt[244] = RGB(158.048,158.048,183.854);
		RGBt[245] = RGB(167.146,167.146,192.602);
		RGBt[246] = RGB(175.683,175.683,200.811);
		RGBt[247] = RGB(    179,    179,    204);
		RGBt[248] = RGB(    179,    179,    204);
		RGBt[249] = RGB(    179,    179,    204);
		RGBt[250] = RGB(    179,    179,    204);
		RGBt[251] = RGB( 179.01, 179.01,204.011);
		RGBt[252] = RGB(183.157,183.157,208.324);
		RGBt[253] = RGB(191.721,191.721,217.229);
		RGBt[254] = RGB(200.176,200.176,226.023);
		RGBt[255] = RGB(    204,    204,    230);
	}
	else if (type=="Globe")
	{
		RGBt[  0] = RGB(  0,  0,  0);
		RGBt[  1] = RGB(  0,157,157);
		RGBt[  2] = RGB(  0,165,165);
		RGBt[  3] = RGB(  0,172,172);
		RGBt[  4] = RGB(  0,180,180);
		RGBt[  5] = RGB(  0,188,188);
		RGBt[  6] = RGB(  0,195,195);
		RGBt[  7] = RGB(  0,203,203);
		RGBt[  8] = RGB(  0,211,211);
		RGBt[  9] = RGB(  0,218,218);
		RGBt[ 10] = RGB(  0,226,226);
		RGBt[ 11] = RGB(  0,234,234);
		RGBt[ 12] = RGB(  0,241,241);
		RGBt[ 13] = RGB(  0,249,249);
		RGBt[ 14] = RGB(  0,100,  0);
		RGBt[ 15] = RGB(  0,104,  0);
		RGBt[ 16] = RGB(  0,108,  0);
		RGBt[ 17] = RGB(  0,112,  0);
		RGBt[ 18] = RGB(  0,115,  0);
		RGBt[ 19] = RGB(  0,119,  0);
		RGBt[ 20] = RGB(  0,123,  0);
		RGBt[ 21] = RGB(  0,127,  0);
		RGBt[ 22] = RGB(  0,130,  0);
		RGBt[ 23] = RGB(  0,134,  0);
		RGBt[ 24] = RGB(  0,138,  0);
		RGBt[ 25] = RGB(  0,142,  0);
		RGBt[ 26] = RGB(  0,145,  0);
		RGBt[ 27] = RGB(  0,149,  0);
		RGBt[ 28] = RGB(  0,153,  0);
		RGBt[ 29] = RGB(  0,157,  0);
		RGBt[ 30] = RGB(  0,160,  0);
		RGBt[ 31] = RGB(  0,164,  0);
		RGBt[ 32] = RGB(  0,168,  0);
		RGBt[ 33] = RGB(  0,172,  0);
		RGBt[ 34] = RGB(  0,175,  0);
		RGBt[ 35] = RGB(  0,179,  0);
		RGBt[ 36] = RGB(  0,183,  0);
		RGBt[ 37] = RGB(  0,187,  0);
		RGBt[ 38] = RGB(  0,190,  0);
		RGBt[ 39] = RGB(  0,194,  0);
		RGBt[ 40] = RGB(  0,198,  0);
		RGBt[ 41] = RGB(  0,202,  0);
		RGBt[ 42] = RGB(  0,205,  0);
		RGBt[ 43] = RGB(  0,209,  0);
		RGBt[ 44] = RGB(  0,213,  0);
		RGBt[ 45] = RGB(  0,217,  0);
		RGBt[ 46] = RGB(  0,220,  0);
		RGBt[ 47] = RGB(  0,224,  0);
		RGBt[ 48] = RGB(  0,228,  0);
		RGBt[ 49] = RGB(  0,232,  0);
		RGBt[ 50] = RGB(  0,235,  0);
		RGBt[ 51] = RGB(  0,239,  0);
		RGBt[ 52] = RGB(  0,243,  0);
		RGBt[ 53] = RGB(  0,247,  0);
		RGBt[ 54] = RGB(  0,250,  0);
		RGBt[ 55] = RGB(  0,254,  0);
		RGBt[ 56] = RGB(254,254,  1);
		RGBt[ 57] = RGB(253,253,  3);
		RGBt[ 58] = RGB(251,251,  4);
		RGBt[ 59] = RGB(250,250,  6);
		RGBt[ 60] = RGB(248,248,  7);
		RGBt[ 61] = RGB(247,247,  9);
		RGBt[ 62] = RGB(245,245, 11);
		RGBt[ 63] = RGB(244,244, 12);
		RGBt[ 64] = RGB(243,243, 14);
		RGBt[ 65] = RGB(241,241, 15);
		RGBt[ 66] = RGB(240,240, 17);
		RGBt[ 67] = RGB(238,238, 19);
		RGBt[ 68] = RGB(237,237, 20);
		RGBt[ 69] = RGB(235,235, 22);
		RGBt[ 70] = RGB(234,234, 23);
		RGBt[ 71] = RGB(232,232, 25);
		RGBt[ 72] = RGB(231,231, 26);
		RGBt[ 73] = RGB(229,229, 28);
		RGBt[ 74] = RGB(228,228, 30);
		RGBt[ 75] = RGB(227,227, 31);
		RGBt[ 76] = RGB(225,225, 33);
		RGBt[ 77] = RGB(224,224, 34);
		RGBt[ 78] = RGB(222,222, 36);
		RGBt[ 79] = RGB(221,221, 38);
		RGBt[ 80] = RGB(219,219, 39);
		RGBt[ 81] = RGB(218,218, 41);
		RGBt[ 82] = RGB(216,216, 42);
		RGBt[ 83] = RGB(215,215, 44);
		RGBt[ 84] = RGB(214,214, 46);
		RGBt[ 85] = RGB(212,212, 47);
		RGBt[ 86] = RGB(211,211, 49);
		RGBt[ 87] = RGB(209,209, 50);
		RGBt[ 88] = RGB(208,208, 52);
		RGBt[ 89] = RGB(206,206, 54);
		RGBt[ 90] = RGB(205,205, 55);
		RGBt[ 91] = RGB(203,203, 57);
		RGBt[ 92] = RGB(202,202, 58);
		RGBt[ 93] = RGB(200,200, 60);
		RGBt[ 94] = RGB(199,199, 62);
		RGBt[ 95] = RGB(198,198, 63);
		RGBt[ 96] = RGB(196,196, 65);
		RGBt[ 97] = RGB(195,195, 66);
		RGBt[ 98] = RGB(193,193, 68);
		RGBt[ 99] = RGB(192,192, 70);
		RGBt[100] = RGB(190,190, 71);
		RGBt[101] = RGB(189,189, 73);
		RGBt[102] = RGB(187,187, 74);
		RGBt[103] = RGB(186,186, 76);
		RGBt[104] = RGB(185,185, 78);
		RGBt[105] = RGB(183,183, 79);
		RGBt[106] = RGB(182,182, 81);
		RGBt[107] = RGB(180,180, 82);
		RGBt[108] = RGB(179,179, 84);
		RGBt[109] = RGB(177,177, 86);
		RGBt[110] = RGB(176,176, 87);
		RGBt[111] = RGB(174,174, 89);
		RGBt[112] = RGB(173,173, 90);
		RGBt[113] = RGB(171,171, 92);
		RGBt[114] = RGB(170,170, 94);
		RGBt[115] = RGB(169,169, 95);
		RGBt[116] = RGB(167,167, 97);
		RGBt[117] = RGB(166,166, 98);
		RGBt[118] = RGB(164,164,100);
		RGBt[119] = RGB(163,163,102);
		RGBt[120] = RGB(161,161,103);
		RGBt[121] = RGB(160,160,105);
		RGBt[122] = RGB(158,158,106);
		RGBt[123] = RGB(157,157,108);
		RGBt[124] = RGB(155,155,110);
		RGBt[125] = RGB(155,155,116);
		RGBt[126] = RGB(156,156,117);
		RGBt[127] = RGB(157,157,118);
		RGBt[128] = RGB(158,158,119);
		RGBt[129] = RGB(158,158,120);
		RGBt[130] = RGB(159,159,121);
		RGBt[131] = RGB(160,160,122);
		RGBt[132] = RGB(161,161,123);
		RGBt[133] = RGB(161,161,124);
		RGBt[134] = RGB(162,162,125);
		RGBt[135] = RGB(163,163,126);
		RGBt[136] = RGB(164,164,127);
		RGBt[137] = RGB(164,164,128);
		RGBt[138] = RGB(165,165,129);
		RGBt[139] = RGB(166,166,130);
		RGBt[140] = RGB(167,167,131);
		RGBt[141] = RGB(167,167,132);
		RGBt[142] = RGB(168,168,134);
		RGBt[143] = RGB(169,169,135);
		RGBt[144] = RGB(170,170,136);
		RGBt[145] = RGB(170,170,137);
		RGBt[146] = RGB(171,171,138);
		RGBt[147] = RGB(172,172,139);
		RGBt[148] = RGB(173,173,140);
		RGBt[149] = RGB(173,173,141);
		RGBt[150] = RGB(174,174,142);
		RGBt[151] = RGB(175,175,143);
		RGBt[152] = RGB(176,176,144);
		RGBt[153] = RGB(176,176,145);
		RGBt[154] = RGB(177,177,146);
		RGBt[155] = RGB(178,178,147);
		RGBt[156] = RGB(179,179,148);
		RGBt[157] = RGB(179,179,149);
		RGBt[158] = RGB(180,180,150);
		RGBt[159] = RGB(181,181,152);
		RGBt[160] = RGB(182,182,153);
		RGBt[161] = RGB(182,182,154);
		RGBt[162] = RGB(183,183,155);
		RGBt[163] = RGB(184,184,156);
		RGBt[164] = RGB(185,185,157);
		RGBt[165] = RGB(185,185,158);
		RGBt[166] = RGB(186,186,159);
		RGBt[167] = RGB(187,187,160);
		RGBt[168] = RGB(188,188,161);
		RGBt[169] = RGB(189,189,162);
		RGBt[170] = RGB(189,189,163);
		RGBt[171] = RGB(190,190,164);
		RGBt[172] = RGB(191,191,165);
		RGBt[173] = RGB(192,192,166);
		RGBt[174] = RGB(192,192,167);
		RGBt[175] = RGB(193,193,168);
		RGBt[176] = RGB(194,194,170);
		RGBt[177] = RGB(195,195,171);
		RGBt[178] = RGB(195,195,172);
		RGBt[179] = RGB(196,196,173);
		RGBt[180] = RGB(197,197,174);
		RGBt[181] = RGB(198,198,175);
		RGBt[182] = RGB(198,198,176);
		RGBt[183] = RGB(199,199,177);
		RGBt[184] = RGB(200,200,178);
		RGBt[185] = RGB(201,201,179);
		RGBt[186] = RGB(201,201,180);
		RGBt[187] = RGB(202,202,181);
		RGBt[188] = RGB(203,203,182);
		RGBt[189] = RGB(204,204,183);
		RGBt[190] = RGB(204,204,184);
		RGBt[191] = RGB(205,205,185);
		RGBt[192] = RGB(206,206,186);
		RGBt[193] = RGB(207,207,187);
		RGBt[194] = RGB(207,207,189);
		RGBt[195] = RGB(208,208,190);
		RGBt[196] = RGB(209,209,191);
		RGBt[197] = RGB(210,210,192);
		RGBt[198] = RGB(210,210,193);
		RGBt[199] = RGB(211,211,194);
		RGBt[200] = RGB(212,212,195);
		RGBt[201] = RGB(213,213,196);
		RGBt[202] = RGB(213,213,197);
		RGBt[203] = RGB(214,214,198);
		RGBt[204] = RGB(215,215,199);
		RGBt[205] = RGB(216,216,200);
		RGBt[206] = RGB(216,216,201);
		RGBt[207] = RGB(217,217,202);
		RGBt[208] = RGB(218,218,203);
		RGBt[209] = RGB(219,219,204);
		RGBt[210] = RGB(219,219,205);
		RGBt[211] = RGB(220,220,207);
		RGBt[212] = RGB(221,221,208);
		RGBt[213] = RGB(222,222,209);
		RGBt[214] = RGB(223,223,210);
		RGBt[215] = RGB(223,223,211);
		RGBt[216] = RGB(224,224,212);
		RGBt[217] = RGB(225,225,213);
		RGBt[218] = RGB(226,226,214);
		RGBt[219] = RGB(226,226,215);
		RGBt[220] = RGB(227,227,216);
		RGBt[221] = RGB(228,228,217);
		RGBt[222] = RGB(229,229,218);
		RGBt[223] = RGB(229,229,219);
		RGBt[224] = RGB(230,230,220);
		RGBt[225] = RGB(231,231,221);
		RGBt[226] = RGB(232,232,222);
		RGBt[227] = RGB(232,232,223);
		RGBt[228] = RGB(233,233,225);
		RGBt[229] = RGB(234,234,226);
		RGBt[230] = RGB(235,235,227);
		RGBt[231] = RGB(235,235,228);
		RGBt[232] = RGB(236,236,229);
		RGBt[233] = RGB(237,237,230);
		RGBt[234] = RGB(238,238,231);
		RGBt[235] = RGB(238,238,232);
		RGBt[236] = RGB(239,239,233);
		RGBt[237] = RGB(240,240,234);
		RGBt[238] = RGB(241,241,235);
		RGBt[239] = RGB(241,241,236);
		RGBt[240] = RGB(242,242,237);
		RGBt[241] = RGB(243,243,238);
		RGBt[242] = RGB(244,244,239);
		RGBt[243] = RGB(244,244,240);
		RGBt[244] = RGB(245,245,241);
		RGBt[245] = RGB(246,246,243);
		RGBt[246] = RGB(247,247,244);
		RGBt[247] = RGB(247,247,245);
		RGBt[248] = RGB(248,248,246);
		RGBt[249] = RGB(249,249,247);
		RGBt[250] = RGB(250,250,248);
		RGBt[251] = RGB(250,250,249);
		RGBt[252] = RGB(251,251,250);
		RGBt[253] = RGB(252,252,251);
		RGBt[254] = RGB(253,253,252);
		RGBt[255] = RGB(254,254,253);
	}
	else if (type=="Pink")
	{
		RGBt[  0] = RGB( 15,  0,  0);
		RGBt[  1] = RGB( 25, 13, 13);
		RGBt[  2] = RGB( 32, 18, 18);
		RGBt[  3] = RGB( 38, 23, 23);
		RGBt[  4] = RGB( 43, 26, 26);
		RGBt[  5] = RGB( 47, 29, 29);
		RGBt[  6] = RGB( 51, 32, 32);
		RGBt[  7] = RGB( 55, 34, 34);
		RGBt[  8] = RGB( 58, 37, 37);
		RGBt[  9] = RGB( 62, 39, 39);
		RGBt[ 10] = RGB( 65, 41, 41);
		RGBt[ 11] = RGB( 68, 43, 43);
		RGBt[ 12] = RGB( 71, 45, 45);
		RGBt[ 13] = RGB( 73, 47, 47);
		RGBt[ 14] = RGB( 76, 49, 49);
		RGBt[ 15] = RGB( 79, 50, 50);
		RGBt[ 16] = RGB( 81, 52, 52);
		RGBt[ 17] = RGB( 83, 54, 54);
		RGBt[ 18] = RGB( 86, 55, 55);
		RGBt[ 19] = RGB( 88, 57, 57);
		RGBt[ 20] = RGB( 90, 58, 58);
		RGBt[ 21] = RGB( 92, 60, 60);
		RGBt[ 22] = RGB( 95, 61, 61);
		RGBt[ 23] = RGB( 97, 63, 63);
		RGBt[ 24] = RGB( 99, 64, 64);
		RGBt[ 25] = RGB(101, 65, 65);
		RGBt[ 26] = RGB(103, 66, 66);
		RGBt[ 27] = RGB(104, 68, 68);
		RGBt[ 28] = RGB(106, 69, 69);
		RGBt[ 29] = RGB(108, 70, 70);
		RGBt[ 30] = RGB(110, 71, 71);
		RGBt[ 31] = RGB(112, 73, 73);
		RGBt[ 32] = RGB(114, 74, 74);
		RGBt[ 33] = RGB(115, 75, 75);
		RGBt[ 34] = RGB(117, 76, 76);
		RGBt[ 35] = RGB(119, 77, 77);
		RGBt[ 36] = RGB(120, 78, 78);
		RGBt[ 37] = RGB(122, 79, 79);
		RGBt[ 38] = RGB(124, 80, 80);
		RGBt[ 39] = RGB(125, 81, 81);
		RGBt[ 40] = RGB(127, 82, 82);
		RGBt[ 41] = RGB(128, 83, 83);
		RGBt[ 42] = RGB(130, 84, 84);
		RGBt[ 43] = RGB(131, 85, 85);
		RGBt[ 44] = RGB(133, 86, 86);
		RGBt[ 45] = RGB(134, 87, 87);
		RGBt[ 46] = RGB(136, 88, 88);
		RGBt[ 47] = RGB(137, 89, 89);
		RGBt[ 48] = RGB(139, 90, 90);
		RGBt[ 49] = RGB(140, 91, 91);
		RGBt[ 50] = RGB(141, 92, 92);
		RGBt[ 51] = RGB(143, 93, 93);
		RGBt[ 52] = RGB(144, 94, 94);
		RGBt[ 53] = RGB(146, 95, 95);
		RGBt[ 54] = RGB(147, 96, 96);
		RGBt[ 55] = RGB(148, 97, 97);
		RGBt[ 56] = RGB(150, 98, 98);
		RGBt[ 57] = RGB(151, 98, 98);
		RGBt[ 58] = RGB(152, 99, 99);
		RGBt[ 59] = RGB(154,100,100);
		RGBt[ 60] = RGB(155,101,101);
		RGBt[ 61] = RGB(156,102,102);
		RGBt[ 62] = RGB(157,103,103);
		RGBt[ 63] = RGB(159,103,103);
		RGBt[ 64] = RGB(160,104,104);
		RGBt[ 65] = RGB(161,105,105);
		RGBt[ 66] = RGB(162,106,106);
		RGBt[ 67] = RGB(164,107,107);
		RGBt[ 68] = RGB(165,108,108);
		RGBt[ 69] = RGB(166,108,108);
		RGBt[ 70] = RGB(167,109,109);
		RGBt[ 71] = RGB(168,110,110);
		RGBt[ 72] = RGB(169,111,111);
		RGBt[ 73] = RGB(171,111,111);
		RGBt[ 74] = RGB(172,112,112);
		RGBt[ 75] = RGB(173,113,113);
		RGBt[ 76] = RGB(174,114,114);
		RGBt[ 77] = RGB(175,114,114);
		RGBt[ 78] = RGB(176,115,115);
		RGBt[ 79] = RGB(177,116,116);
		RGBt[ 80] = RGB(179,117,117);
		RGBt[ 81] = RGB(180,117,117);
		RGBt[ 82] = RGB(181,118,118);
		RGBt[ 83] = RGB(182,119,119);
		RGBt[ 84] = RGB(183,119,119);
		RGBt[ 85] = RGB(184,120,120);
		RGBt[ 86] = RGB(185,121,121);
		RGBt[ 87] = RGB(186,122,122);
		RGBt[ 88] = RGB(187,122,122);
		RGBt[ 89] = RGB(188,123,123);
		RGBt[ 90] = RGB(189,124,124);
		RGBt[ 91] = RGB(190,124,124);
		RGBt[ 92] = RGB(191,125,125);
		RGBt[ 93] = RGB(192,126,126);
		RGBt[ 94] = RGB(193,126,126);
		RGBt[ 95] = RGB(194,127,127);
		RGBt[ 96] = RGB(195,129,128);
		RGBt[ 97] = RGB(195,130,128);
		RGBt[ 98] = RGB(196,132,129);
		RGBt[ 99] = RGB(196,133,130);
		RGBt[100] = RGB(197,135,130);
		RGBt[101] = RGB(197,136,131);
		RGBt[102] = RGB(198,138,132);
		RGBt[103] = RGB(198,139,132);
		RGBt[104] = RGB(198,140,133);
		RGBt[105] = RGB(199,142,134);
		RGBt[106] = RGB(199,143,134);
		RGBt[107] = RGB(200,145,135);
		RGBt[108] = RGB(200,146,135);
		RGBt[109] = RGB(201,147,136);
		RGBt[110] = RGB(201,149,137);
		RGBt[111] = RGB(201,150,137);
		RGBt[112] = RGB(202,151,138);
		RGBt[113] = RGB(202,153,139);
		RGBt[114] = RGB(203,154,139);
		RGBt[115] = RGB(203,155,140);
		RGBt[116] = RGB(203,156,140);
		RGBt[117] = RGB(204,158,141);
		RGBt[118] = RGB(204,159,142);
		RGBt[119] = RGB(205,160,142);
		RGBt[120] = RGB(205,161,143);
		RGBt[121] = RGB(206,163,143);
		RGBt[122] = RGB(206,164,144);
		RGBt[123] = RGB(206,165,145);
		RGBt[124] = RGB(207,166,145);
		RGBt[125] = RGB(207,167,146);
		RGBt[126] = RGB(208,169,146);
		RGBt[127] = RGB(208,170,147);
		RGBt[128] = RGB(208,171,148);
		RGBt[129] = RGB(209,172,148);
		RGBt[130] = RGB(209,173,149);
		RGBt[131] = RGB(210,174,149);
		RGBt[132] = RGB(210,175,150);
		RGBt[133] = RGB(210,177,150);
		RGBt[134] = RGB(211,178,151);
		RGBt[135] = RGB(211,179,151);
		RGBt[136] = RGB(212,180,152);
		RGBt[137] = RGB(212,181,153);
		RGBt[138] = RGB(212,182,153);
		RGBt[139] = RGB(213,183,154);
		RGBt[140] = RGB(213,184,154);
		RGBt[141] = RGB(214,185,155);
		RGBt[142] = RGB(214,186,155);
		RGBt[143] = RGB(214,187,156);
		RGBt[144] = RGB(215,189,156);
		RGBt[145] = RGB(215,190,157);
		RGBt[146] = RGB(216,191,158);
		RGBt[147] = RGB(216,192,158);
		RGBt[148] = RGB(216,193,159);
		RGBt[149] = RGB(217,194,159);
		RGBt[150] = RGB(217,195,160);
		RGBt[151] = RGB(218,196,160);
		RGBt[152] = RGB(218,197,161);
		RGBt[153] = RGB(218,198,161);
		RGBt[154] = RGB(219,199,162);
		RGBt[155] = RGB(219,200,162);
		RGBt[156] = RGB(220,201,163);
		RGBt[157] = RGB(220,202,163);
		RGBt[158] = RGB(220,203,164);
		RGBt[159] = RGB(221,204,164);
		RGBt[160] = RGB(221,205,165);
		RGBt[161] = RGB(221,206,165);
		RGBt[162] = RGB(222,207,166);
		RGBt[163] = RGB(222,208,166);
		RGBt[164] = RGB(223,208,167);
		RGBt[165] = RGB(223,209,167);
		RGBt[166] = RGB(223,210,168);
		RGBt[167] = RGB(224,211,168);
		RGBt[168] = RGB(224,212,169);
		RGBt[169] = RGB(225,213,169);
		RGBt[170] = RGB(225,214,170);
		RGBt[171] = RGB(225,215,170);
		RGBt[172] = RGB(226,216,171);
		RGBt[173] = RGB(226,217,171);
		RGBt[174] = RGB(226,218,172);
		RGBt[175] = RGB(227,219,172);
		RGBt[176] = RGB(227,220,173);
		RGBt[177] = RGB(228,220,173);
		RGBt[178] = RGB(228,221,174);
		RGBt[179] = RGB(228,222,174);
		RGBt[180] = RGB(229,223,175);
		RGBt[181] = RGB(229,224,175);
		RGBt[182] = RGB(229,225,176);
		RGBt[183] = RGB(230,226,176);
		RGBt[184] = RGB(230,227,177);
		RGBt[185] = RGB(230,228,177);
		RGBt[186] = RGB(231,228,178);
		RGBt[187] = RGB(231,229,178);
		RGBt[188] = RGB(232,230,179);
		RGBt[189] = RGB(232,231,179);
		RGBt[190] = RGB(232,232,180);
		RGBt[191] = RGB(233,233,180);
		RGBt[192] = RGB(233,233,182);
		RGBt[193] = RGB(233,233,183);
		RGBt[194] = RGB(234,234,184);
		RGBt[195] = RGB(234,234,186);
		RGBt[196] = RGB(235,235,187);
		RGBt[197] = RGB(235,235,188);
		RGBt[198] = RGB(235,235,190);
		RGBt[199] = RGB(236,236,191);
		RGBt[200] = RGB(236,236,192);
		RGBt[201] = RGB(236,236,194);
		RGBt[202] = RGB(237,237,195);
		RGBt[203] = RGB(237,237,196);
		RGBt[204] = RGB(237,237,198);
		RGBt[205] = RGB(238,238,199);
		RGBt[206] = RGB(238,238,200);
		RGBt[207] = RGB(238,238,202);
		RGBt[208] = RGB(239,239,203);
		RGBt[209] = RGB(239,239,204);
		RGBt[210] = RGB(240,240,205);
		RGBt[211] = RGB(240,240,207);
		RGBt[212] = RGB(240,240,208);
		RGBt[213] = RGB(241,241,209);
		RGBt[214] = RGB(241,241,210);
		RGBt[215] = RGB(241,241,211);
		RGBt[216] = RGB(242,242,213);
		RGBt[217] = RGB(242,242,214);
		RGBt[218] = RGB(242,242,215);
		RGBt[219] = RGB(243,243,216);
		RGBt[220] = RGB(243,243,217);
		RGBt[221] = RGB(243,243,218);
		RGBt[222] = RGB(244,244,220);
		RGBt[223] = RGB(244,244,221);
		RGBt[224] = RGB(244,244,222);
		RGBt[225] = RGB(245,245,223);
		RGBt[226] = RGB(245,245,224);
		RGBt[227] = RGB(245,245,225);
		RGBt[228] = RGB(246,246,226);
		RGBt[229] = RGB(246,246,228);
		RGBt[230] = RGB(247,247,229);
		RGBt[231] = RGB(247,247,230);
		RGBt[232] = RGB(247,247,231);
		RGBt[233] = RGB(248,248,232);
		RGBt[234] = RGB(248,248,233);
		RGBt[235] = RGB(248,248,234);
		RGBt[236] = RGB(249,249,235);
		RGBt[237] = RGB(249,249,236);
		RGBt[238] = RGB(249,249,237);
		RGBt[239] = RGB(250,250,239);
		RGBt[240] = RGB(250,250,240);
		RGBt[241] = RGB(250,250,241);
		RGBt[242] = RGB(251,251,242);
		RGBt[243] = RGB(251,251,243);
		RGBt[244] = RGB(251,251,244);
		RGBt[245] = RGB(252,252,245);
		RGBt[246] = RGB(252,252,246);
		RGBt[247] = RGB(252,252,247);
		RGBt[248] = RGB(253,253,248);
		RGBt[249] = RGB(253,253,249);
		RGBt[250] = RGB(253,253,250);
		RGBt[251] = RGB(254,254,251);
		RGBt[252] = RGB(254,254,252);
		RGBt[253] = RGB(254,254,253);
		RGBt[254] = RGB(255,255,254);
		RGBt[255] = RGB(255,255,255);
	}
	else if (type=="Gray")
	{
		RGBt[  0] = RGB(  0,  0,  0);
		RGBt[  1] = RGB(  1,  1,  1);
		RGBt[  2] = RGB(  2,  2,  2);
		RGBt[  3] = RGB(  3,  3,  3);
		RGBt[  4] = RGB(  4,  4,  4);
		RGBt[  5] = RGB(  5,  5,  5);
		RGBt[  6] = RGB(  6,  6,  6);
		RGBt[  7] = RGB(  7,  7,  7);
		RGBt[  8] = RGB(  8,  8,  8);
		RGBt[  9] = RGB(  9,  9,  9);
		RGBt[ 10] = RGB( 10, 10, 10);
		RGBt[ 11] = RGB( 11, 11, 11);
		RGBt[ 12] = RGB( 12, 12, 12);
		RGBt[ 13] = RGB( 13, 13, 13);
		RGBt[ 14] = RGB( 14, 14, 14);
		RGBt[ 15] = RGB( 15, 15, 15);
		RGBt[ 16] = RGB( 16, 16, 16);
		RGBt[ 17] = RGB( 17, 17, 17);
		RGBt[ 18] = RGB( 18, 18, 18);
		RGBt[ 19] = RGB( 19, 19, 19);
		RGBt[ 20] = RGB( 20, 20, 20);
		RGBt[ 21] = RGB( 21, 21, 21);
		RGBt[ 22] = RGB( 22, 22, 22);
		RGBt[ 23] = RGB( 23, 23, 23);
		RGBt[ 24] = RGB( 24, 24, 24);
		RGBt[ 25] = RGB( 25, 25, 25);
		RGBt[ 26] = RGB( 26, 26, 26);
		RGBt[ 27] = RGB( 27, 27, 27);
		RGBt[ 28] = RGB( 28, 28, 28);
		RGBt[ 29] = RGB( 29, 29, 29);
		RGBt[ 30] = RGB( 30, 30, 30);
		RGBt[ 31] = RGB( 31, 31, 31);
		RGBt[ 32] = RGB( 32, 32, 32);
		RGBt[ 33] = RGB( 33, 33, 33);
		RGBt[ 34] = RGB( 34, 34, 34);
		RGBt[ 35] = RGB( 35, 35, 35);
		RGBt[ 36] = RGB( 36, 36, 36);
		RGBt[ 37] = RGB( 37, 37, 37);
		RGBt[ 38] = RGB( 38, 38, 38);
		RGBt[ 39] = RGB( 39, 39, 39);
		RGBt[ 40] = RGB( 40, 40, 40);
		RGBt[ 41] = RGB( 41, 41, 41);
		RGBt[ 42] = RGB( 42, 42, 42);
		RGBt[ 43] = RGB( 43, 43, 43);
		RGBt[ 44] = RGB( 44, 44, 44);
		RGBt[ 45] = RGB( 45, 45, 45);
		RGBt[ 46] = RGB( 46, 46, 46);
		RGBt[ 47] = RGB( 47, 47, 47);
		RGBt[ 48] = RGB( 48, 48, 48);
		RGBt[ 49] = RGB( 49, 49, 49);
		RGBt[ 50] = RGB( 50, 50, 50);
		RGBt[ 51] = RGB( 51, 51, 51);
		RGBt[ 52] = RGB( 52, 52, 52);
		RGBt[ 53] = RGB( 53, 53, 53);
		RGBt[ 54] = RGB( 54, 54, 54);
		RGBt[ 55] = RGB( 55, 55, 55);
		RGBt[ 56] = RGB( 56, 56, 56);
		RGBt[ 57] = RGB( 57, 57, 57);
		RGBt[ 58] = RGB( 58, 58, 58);
		RGBt[ 59] = RGB( 59, 59, 59);
		RGBt[ 60] = RGB( 60, 60, 60);
		RGBt[ 61] = RGB( 61, 61, 61);
		RGBt[ 62] = RGB( 62, 62, 62);
		RGBt[ 63] = RGB( 63, 63, 63);
		RGBt[ 64] = RGB( 64, 64, 64);
		RGBt[ 65] = RGB( 65, 65, 65);
		RGBt[ 66] = RGB( 66, 66, 66);
		RGBt[ 67] = RGB( 67, 67, 67);
		RGBt[ 68] = RGB( 68, 68, 68);
		RGBt[ 69] = RGB( 69, 69, 69);
		RGBt[ 70] = RGB( 70, 70, 70);
		RGBt[ 71] = RGB( 71, 71, 71);
		RGBt[ 72] = RGB( 72, 72, 72);
		RGBt[ 73] = RGB( 73, 73, 73);
		RGBt[ 74] = RGB( 74, 74, 74);
		RGBt[ 75] = RGB( 75, 75, 75);
		RGBt[ 76] = RGB( 76, 76, 76);
		RGBt[ 77] = RGB( 77, 77, 77);
		RGBt[ 78] = RGB( 78, 78, 78);
		RGBt[ 79] = RGB( 79, 79, 79);
		RGBt[ 80] = RGB( 80, 80, 80);
		RGBt[ 81] = RGB( 81, 81, 81);
		RGBt[ 82] = RGB( 82, 82, 82);
		RGBt[ 83] = RGB( 83, 83, 83);
		RGBt[ 84] = RGB( 84, 84, 84);
		RGBt[ 85] = RGB( 85, 85, 85);
		RGBt[ 86] = RGB( 86, 86, 86);
		RGBt[ 87] = RGB( 87, 87, 87);
		RGBt[ 88] = RGB( 88, 88, 88);
		RGBt[ 89] = RGB( 89, 89, 89);
		RGBt[ 90] = RGB( 90, 90, 90);
		RGBt[ 91] = RGB( 91, 91, 91);
		RGBt[ 92] = RGB( 92, 92, 92);
		RGBt[ 93] = RGB( 93, 93, 93);
		RGBt[ 94] = RGB( 94, 94, 94);
		RGBt[ 95] = RGB( 95, 95, 95);
		RGBt[ 96] = RGB( 96, 96, 96);
		RGBt[ 97] = RGB( 97, 97, 97);
		RGBt[ 98] = RGB( 98, 98, 98);
		RGBt[ 99] = RGB( 99, 99, 99);
		RGBt[100] = RGB(100,100,100);
		RGBt[101] = RGB(101,101,101);
		RGBt[102] = RGB(102,102,102);
		RGBt[103] = RGB(103,103,103);
		RGBt[104] = RGB(104,104,104);
		RGBt[105] = RGB(105,105,105);
		RGBt[106] = RGB(106,106,106);
		RGBt[107] = RGB(107,107,107);
		RGBt[108] = RGB(108,108,108);
		RGBt[109] = RGB(109,109,109);
		RGBt[110] = RGB(110,110,110);
		RGBt[111] = RGB(111,111,111);
		RGBt[112] = RGB(112,112,112);
		RGBt[113] = RGB(113,113,113);
		RGBt[114] = RGB(114,114,114);
		RGBt[115] = RGB(115,115,115);
		RGBt[116] = RGB(116,116,116);
		RGBt[117] = RGB(117,117,117);
		RGBt[118] = RGB(118,118,118);
		RGBt[119] = RGB(119,119,119);
		RGBt[120] = RGB(120,120,120);
		RGBt[121] = RGB(121,121,121);
		RGBt[122] = RGB(122,122,122);
		RGBt[123] = RGB(123,123,123);
		RGBt[124] = RGB(124,124,124);
		RGBt[125] = RGB(125,125,125);
		RGBt[126] = RGB(126,126,126);
		RGBt[127] = RGB(127,127,127);
		RGBt[128] = RGB(128,128,128);
		RGBt[129] = RGB(129,129,129);
		RGBt[130] = RGB(130,130,130);
		RGBt[131] = RGB(131,131,131);
		RGBt[132] = RGB(132,132,132);
		RGBt[133] = RGB(133,133,133);
		RGBt[134] = RGB(134,134,134);
		RGBt[135] = RGB(135,135,135);
		RGBt[136] = RGB(136,136,136);
		RGBt[137] = RGB(137,137,137);
		RGBt[138] = RGB(138,138,138);
		RGBt[139] = RGB(139,139,139);
		RGBt[140] = RGB(140,140,140);
		RGBt[141] = RGB(141,141,141);
		RGBt[142] = RGB(142,142,142);
		RGBt[143] = RGB(143,143,143);
		RGBt[144] = RGB(144,144,144);
		RGBt[145] = RGB(145,145,145);
		RGBt[146] = RGB(146,146,146);
		RGBt[147] = RGB(147,147,147);
		RGBt[148] = RGB(148,148,148);
		RGBt[149] = RGB(149,149,149);
		RGBt[150] = RGB(150,150,150);
		RGBt[151] = RGB(151,151,151);
		RGBt[152] = RGB(152,152,152);
		RGBt[153] = RGB(153,153,153);
		RGBt[154] = RGB(154,154,154);
		RGBt[155] = RGB(155,155,155);
		RGBt[156] = RGB(156,156,156);
		RGBt[157] = RGB(157,157,157);
		RGBt[158] = RGB(158,158,158);
		RGBt[159] = RGB(159,159,159);
		RGBt[160] = RGB(160,160,160);
		RGBt[161] = RGB(161,161,161);
		RGBt[162] = RGB(162,162,162);
		RGBt[163] = RGB(163,163,163);
		RGBt[164] = RGB(164,164,164);
		RGBt[165] = RGB(165,165,165);
		RGBt[166] = RGB(166,166,166);
		RGBt[167] = RGB(167,167,167);
		RGBt[168] = RGB(168,168,168);
		RGBt[169] = RGB(169,169,169);
		RGBt[170] = RGB(170,170,170);
		RGBt[171] = RGB(171,171,171);
		RGBt[172] = RGB(172,172,172);
		RGBt[173] = RGB(173,173,173);
		RGBt[174] = RGB(174,174,174);
		RGBt[175] = RGB(175,175,175);
		RGBt[176] = RGB(176,176,176);
		RGBt[177] = RGB(177,177,177);
		RGBt[178] = RGB(178,178,178);
		RGBt[179] = RGB(179,179,179);
		RGBt[180] = RGB(180,180,180);
		RGBt[181] = RGB(181,181,181);
		RGBt[182] = RGB(182,182,182);
		RGBt[183] = RGB(183,183,183);
		RGBt[184] = RGB(184,184,184);
		RGBt[185] = RGB(185,185,185);
		RGBt[186] = RGB(186,186,186);
		RGBt[187] = RGB(187,187,187);
		RGBt[188] = RGB(188,188,188);
		RGBt[189] = RGB(189,189,189);
		RGBt[190] = RGB(190,190,190);
		RGBt[191] = RGB(191,191,191);
		RGBt[192] = RGB(192,192,192);
		RGBt[193] = RGB(193,193,193);
		RGBt[194] = RGB(194,194,194);
		RGBt[195] = RGB(195,195,195);
		RGBt[196] = RGB(196,196,196);
		RGBt[197] = RGB(197,197,197);
		RGBt[198] = RGB(198,198,198);
		RGBt[199] = RGB(199,199,199);
		RGBt[200] = RGB(200,200,200);
		RGBt[201] = RGB(201,201,201);
		RGBt[202] = RGB(202,202,202);
		RGBt[203] = RGB(203,203,203);
		RGBt[204] = RGB(204,204,204);
		RGBt[205] = RGB(205,205,205);
		RGBt[206] = RGB(206,206,206);
		RGBt[207] = RGB(207,207,207);
		RGBt[208] = RGB(208,208,208);
		RGBt[209] = RGB(209,209,209);
		RGBt[210] = RGB(210,210,210);
		RGBt[211] = RGB(211,211,211);
		RGBt[212] = RGB(212,212,212);
		RGBt[213] = RGB(213,213,213);
		RGBt[214] = RGB(214,214,214);
		RGBt[215] = RGB(215,215,215);
		RGBt[216] = RGB(216,216,216);
		RGBt[217] = RGB(217,217,217);
		RGBt[218] = RGB(218,218,218);
		RGBt[219] = RGB(219,219,219);
		RGBt[220] = RGB(220,220,220);
		RGBt[221] = RGB(221,221,221);
		RGBt[222] = RGB(222,222,222);
		RGBt[223] = RGB(223,223,223);
		RGBt[224] = RGB(224,224,224);
		RGBt[225] = RGB(225,225,225);
		RGBt[226] = RGB(226,226,226);
		RGBt[227] = RGB(227,227,227);
		RGBt[228] = RGB(228,228,228);
		RGBt[229] = RGB(229,229,229);
		RGBt[230] = RGB(230,230,230);
		RGBt[231] = RGB(231,231,231);
		RGBt[232] = RGB(232,232,232);
		RGBt[233] = RGB(233,233,233);
		RGBt[234] = RGB(234,234,234);
		RGBt[235] = RGB(235,235,235);
		RGBt[236] = RGB(236,236,236);
		RGBt[237] = RGB(237,237,237);
		RGBt[238] = RGB(238,238,238);
		RGBt[239] = RGB(239,239,239);
		RGBt[240] = RGB(240,240,240);
		RGBt[241] = RGB(241,241,241);
		RGBt[242] = RGB(242,242,242);
		RGBt[243] = RGB(243,243,243);
		RGBt[244] = RGB(244,244,244);
		RGBt[245] = RGB(245,245,245);
		RGBt[246] = RGB(246,246,246);
		RGBt[247] = RGB(247,247,247);
		RGBt[248] = RGB(248,248,248);
		RGBt[249] = RGB(249,249,249);
		RGBt[250] = RGB(250,250,250);
		RGBt[251] = RGB(251,251,251);
		RGBt[252] = RGB(252,252,252);
		RGBt[253] = RGB(253,253,253);
		RGBt[254] = RGB(254,254,254);
		RGBt[255] = RGB(255,255,255);
	}
	else if (type=="Copper")
	{
		RGBt[  0] = RGB(  0,  0,  0);
		RGBt[  1] = RGB(  1,  1,  0);
		RGBt[  2] = RGB(  3,  2,  1);
		RGBt[  3] = RGB(  4,  2,  1);
		RGBt[  4] = RGB(  5,  3,  2);
		RGBt[  5] = RGB(  6,  4,  2);
		RGBt[  6] = RGB(  8,  5,  3);
		RGBt[  7] = RGB(  9,  5,  3);
		RGBt[  8] = RGB( 10,  6,  4);
		RGBt[  9] = RGB( 11,  7,  4);
		RGBt[ 10] = RGB( 13,  8,  5);
		RGBt[ 11] = RGB( 14,  9,  5);
		RGBt[ 12] = RGB( 15,  9,  6);
		RGBt[ 13] = RGB( 16, 10,  6);
		RGBt[ 14] = RGB( 18, 11,  7);
		RGBt[ 15] = RGB( 19, 12,  7);
		RGBt[ 16] = RGB( 20, 12,  8);
		RGBt[ 17] = RGB( 21, 13,  8);
		RGBt[ 18] = RGB( 22, 14,  9);
		RGBt[ 19] = RGB( 24, 15,  9);
		RGBt[ 20] = RGB( 25, 16, 10);
		RGBt[ 21] = RGB( 26, 16, 10);
		RGBt[ 22] = RGB( 28, 17, 11);
		RGBt[ 23] = RGB( 29, 18, 11);
		RGBt[ 24] = RGB( 30, 19, 12);
		RGBt[ 25] = RGB( 31, 20, 12);
		RGBt[ 26] = RGB( 33, 20, 13);
		RGBt[ 27] = RGB( 34, 21, 13);
		RGBt[ 28] = RGB( 35, 22, 14);
		RGBt[ 29] = RGB( 36, 23, 14);
		RGBt[ 30] = RGB( 38, 23, 15);
		RGBt[ 31] = RGB( 39, 24, 15);
		RGBt[ 32] = RGB( 40, 25, 16);
		RGBt[ 33] = RGB( 41, 26, 16);
		RGBt[ 34] = RGB( 43, 27, 17);
		RGBt[ 35] = RGB( 44, 27, 17);
		RGBt[ 36] = RGB( 45, 28, 18);
		RGBt[ 37] = RGB( 46, 29, 18);
		RGBt[ 38] = RGB( 48, 30, 19);
		RGBt[ 39] = RGB( 49, 30, 19);
		RGBt[ 40] = RGB( 50, 31, 20);
		RGBt[ 41] = RGB( 51, 32, 20);
		RGBt[ 42] = RGB( 53, 33, 21);
		RGBt[ 43] = RGB( 54, 34, 21);
		RGBt[ 44] = RGB( 55, 34, 22);
		RGBt[ 45] = RGB( 56, 35, 22);
		RGBt[ 46] = RGB( 58, 36, 23);
		RGBt[ 47] = RGB( 59, 37, 23);
		RGBt[ 48] = RGB( 60, 37, 24);
		RGBt[ 49] = RGB( 61, 38, 24);
		RGBt[ 50] = RGB( 63, 39, 25);
		RGBt[ 51] = RGB( 64, 40, 25);
		RGBt[ 52] = RGB( 65, 41, 26);
		RGBt[ 53] = RGB( 66, 41, 26);
		RGBt[ 54] = RGB( 68, 42, 27);
		RGBt[ 55] = RGB( 69, 43, 27);
		RGBt[ 56] = RGB( 70, 44, 28);
		RGBt[ 57] = RGB( 71, 45, 28);
		RGBt[ 58] = RGB( 73, 45, 29);
		RGBt[ 59] = RGB( 74, 46, 29);
		RGBt[ 60] = RGB( 75, 47, 30);
		RGBt[ 61] = RGB( 76, 48, 30);
		RGBt[ 62] = RGB( 78, 48, 31);
		RGBt[ 63] = RGB( 79, 49, 31);
		RGBt[ 64] = RGB( 80, 50, 32);
		RGBt[ 65] = RGB( 81, 51, 32);
		RGBt[ 66] = RGB( 83, 52, 33);
		RGBt[ 67] = RGB( 84, 52, 33);
		RGBt[ 68] = RGB( 85, 53, 34);
		RGBt[ 69] = RGB( 86, 54, 34);
		RGBt[ 70] = RGB( 88, 55, 35);
		RGBt[ 71] = RGB( 89, 55, 35);
		RGBt[ 72] = RGB( 90, 56, 36);
		RGBt[ 73] = RGB( 91, 57, 36);
		RGBt[ 74] = RGB( 93, 58, 37);
		RGBt[ 75] = RGB( 94, 59, 37);
		RGBt[ 76] = RGB( 95, 59, 38);
		RGBt[ 77] = RGB( 96, 60, 38);
		RGBt[ 78] = RGB( 98, 61, 39);
		RGBt[ 79] = RGB( 99, 62, 39);
		RGBt[ 80] = RGB(100, 62, 40);
		RGBt[ 81] = RGB(101, 63, 40);
		RGBt[ 82] = RGB(103, 64, 41);
		RGBt[ 83] = RGB(104, 65, 41);
		RGBt[ 84] = RGB(105, 66, 42);
		RGBt[ 85] = RGB(106, 66, 42);
		RGBt[ 86] = RGB(108, 67, 43);
		RGBt[ 87] = RGB(109, 68, 43);
		RGBt[ 88] = RGB(110, 69, 44);
		RGBt[ 89] = RGB(111, 70, 44);
		RGBt[ 90] = RGB(113, 70, 45);
		RGBt[ 91] = RGB(114, 71, 45);
		RGBt[ 92] = RGB(115, 72, 46);
		RGBt[ 93] = RGB(116, 73, 46);
		RGBt[ 94] = RGB(118, 73, 47);
		RGBt[ 95] = RGB(119, 74, 47);
		RGBt[ 96] = RGB(120, 75, 48);
		RGBt[ 97] = RGB(121, 76, 48);
		RGBt[ 98] = RGB(123, 77, 49);
		RGBt[ 99] = RGB(124, 77, 49);
		RGBt[100] = RGB(125, 78, 50);
		RGBt[101] = RGB(126, 79, 50);
		RGBt[102] = RGB(128, 80, 51);
		RGBt[103] = RGB(129, 80, 51);
		RGBt[104] = RGB(130, 81, 52);
		RGBt[105] = RGB(131, 82, 52);
		RGBt[106] = RGB(133, 83, 53);
		RGBt[107] = RGB(134, 84, 53);
		RGBt[108] = RGB(135, 84, 54);
		RGBt[109] = RGB(136, 85, 54);
		RGBt[110] = RGB(138, 86, 55);
		RGBt[111] = RGB(139, 87, 55);
		RGBt[112] = RGB(140, 87, 56);
		RGBt[113] = RGB(141, 88, 56);
		RGBt[114] = RGB(143, 89, 57);
		RGBt[115] = RGB(144, 90, 57);
		RGBt[116] = RGB(145, 91, 58);
		RGBt[117] = RGB(146, 91, 58);
		RGBt[118] = RGB(148, 92, 59);
		RGBt[119] = RGB(149, 93, 59);
		RGBt[120] = RGB(150, 94, 60);
		RGBt[121] = RGB(151, 95, 60);
		RGBt[122] = RGB(153, 95, 61);
		RGBt[123] = RGB(154, 96, 61);
		RGBt[124] = RGB(155, 97, 62);
		RGBt[125] = RGB(156, 98, 62);
		RGBt[126] = RGB(158, 98, 63);
		RGBt[127] = RGB(159, 99, 63);
		RGBt[128] = RGB(160,100, 64);
		RGBt[129] = RGB(161,101, 64);
		RGBt[130] = RGB(163,102, 65);
		RGBt[131] = RGB(164,102, 65);
		RGBt[132] = RGB(165,103, 66);
		RGBt[133] = RGB(166,104, 66);
		RGBt[134] = RGB(168,105, 67);
		RGBt[135] = RGB(169,105, 67);
		RGBt[136] = RGB(170,106, 68);
		RGBt[137] = RGB(171,107, 68);
		RGBt[138] = RGB(172,108, 69);
		RGBt[139] = RGB(174,109, 69);
		RGBt[140] = RGB(175,109, 70);
		RGBt[141] = RGB(176,110, 70);
		RGBt[142] = RGB(178,111, 71);
		RGBt[143] = RGB(179,112, 71);
		RGBt[144] = RGB(180,112, 72);
		RGBt[145] = RGB(181,113, 72);
		RGBt[146] = RGB(182,114, 73);
		RGBt[147] = RGB(184,115, 73);
		RGBt[148] = RGB(185,116, 74);
		RGBt[149] = RGB(186,116, 74);
		RGBt[150] = RGB(188,117, 75);
		RGBt[151] = RGB(189,118, 75);
		RGBt[152] = RGB(190,119, 76);
		RGBt[153] = RGB(191,120, 76);
		RGBt[154] = RGB(193,120, 77);
		RGBt[155] = RGB(194,121, 77);
		RGBt[156] = RGB(195,122, 78);
		RGBt[157] = RGB(196,123, 78);
		RGBt[158] = RGB(198,123, 79);
		RGBt[159] = RGB(199,124, 79);
		RGBt[160] = RGB(200,125, 80);
		RGBt[161] = RGB(201,126, 80);
		RGBt[162] = RGB(203,127, 81);
		RGBt[163] = RGB(204,127, 81);
		RGBt[164] = RGB(205,128, 82);
		RGBt[165] = RGB(206,129, 82);
		RGBt[166] = RGB(208,130, 83);
		RGBt[167] = RGB(209,130, 83);
		RGBt[168] = RGB(210,131, 84);
		RGBt[169] = RGB(211,132, 84);
		RGBt[170] = RGB(212,133, 85);
		RGBt[171] = RGB(214,134, 85);
		RGBt[172] = RGB(215,134, 86);
		RGBt[173] = RGB(216,135, 86);
		RGBt[174] = RGB(218,136, 87);
		RGBt[175] = RGB(219,137, 87);
		RGBt[176] = RGB(220,137, 88);
		RGBt[177] = RGB(221,138, 88);
		RGBt[178] = RGB(223,139, 89);
		RGBt[179] = RGB(224,140, 89);
		RGBt[180] = RGB(225,141, 90);
		RGBt[181] = RGB(226,141, 90);
		RGBt[182] = RGB(228,142, 91);
		RGBt[183] = RGB(229,143, 91);
		RGBt[184] = RGB(230,144, 92);
		RGBt[185] = RGB(231,145, 92);
		RGBt[186] = RGB(233,145, 93);
		RGBt[187] = RGB(234,146, 93);
		RGBt[188] = RGB(235,147, 94);
		RGBt[189] = RGB(236,148, 94);
		RGBt[190] = RGB(238,148, 95);
		RGBt[191] = RGB(239,149, 95);
		RGBt[192] = RGB(240,150, 96);
		RGBt[193] = RGB(241,151, 96);
		RGBt[194] = RGB(243,152, 97);
		RGBt[195] = RGB(244,152, 97);
		RGBt[196] = RGB(245,153, 98);
		RGBt[197] = RGB(246,154, 98);
		RGBt[198] = RGB(248,155, 99);
		RGBt[199] = RGB(249,155, 99);
		RGBt[200] = RGB(250,156,100);
		RGBt[201] = RGB(251,157,100);
		RGBt[202] = RGB(252,158,100);
		RGBt[203] = RGB(254,159,101);
		RGBt[204] = RGB(255,159,101);
		RGBt[205] = RGB(255,160,102);
		RGBt[206] = RGB(255,161,102);
		RGBt[207] = RGB(255,162,103);
		RGBt[208] = RGB(255,162,103);
		RGBt[209] = RGB(255,163,104);
		RGBt[210] = RGB(255,164,104);
		RGBt[211] = RGB(255,165,105);
		RGBt[212] = RGB(255,166,105);
		RGBt[213] = RGB(255,166,106);
		RGBt[214] = RGB(255,167,106);
		RGBt[215] = RGB(255,168,107);
		RGBt[216] = RGB(255,169,107);
		RGBt[217] = RGB(255,170,108);
		RGBt[218] = RGB(255,170,108);
		RGBt[219] = RGB(255,171,109);
		RGBt[220] = RGB(255,172,109);
		RGBt[221] = RGB(255,173,110);
		RGBt[222] = RGB(255,173,110);
		RGBt[223] = RGB(255,174,111);
		RGBt[224] = RGB(255,175,111);
		RGBt[225] = RGB(255,176,112);
		RGBt[226] = RGB(255,177,112);
		RGBt[227] = RGB(255,177,113);
		RGBt[228] = RGB(255,178,113);
		RGBt[229] = RGB(255,179,114);
		RGBt[230] = RGB(255,180,114);
		RGBt[231] = RGB(255,180,115);
		RGBt[232] = RGB(255,181,115);
		RGBt[233] = RGB(255,182,116);
		RGBt[234] = RGB(255,183,116);
		RGBt[235] = RGB(255,184,117);
		RGBt[236] = RGB(255,184,117);
		RGBt[237] = RGB(255,185,118);
		RGBt[238] = RGB(255,186,118);
		RGBt[239] = RGB(255,187,119);
		RGBt[240] = RGB(255,187,119);
		RGBt[241] = RGB(255,188,120);
		RGBt[242] = RGB(255,189,120);
		RGBt[243] = RGB(255,190,121);
		RGBt[244] = RGB(255,191,121);
		RGBt[245] = RGB(255,191,122);
		RGBt[246] = RGB(255,192,122);
		RGBt[247] = RGB(255,193,123);
		RGBt[248] = RGB(255,194,123);
		RGBt[249] = RGB(255,195,124);
		RGBt[250] = RGB(255,195,124);
		RGBt[251] = RGB(255,196,125);
		RGBt[252] = RGB(255,197,125);
		RGBt[253] = RGB(255,198,126);
		RGBt[254] = RGB(255,198,126);
		RGBt[255] = RGB(255,199,127);
	}
	else if (type=="Jet")
	{
		RGBt[  0] = RGB(      0,      0,131.484);
		RGBt[  1] = RGB(      0,      0,135.469);
		RGBt[  2] = RGB(      0,      0,139.453);
		RGBt[  3] = RGB(      0,      0,143.438);
		RGBt[  4] = RGB(      0,      0,147.422);
		RGBt[  5] = RGB(      0,      0,151.406);
		RGBt[  6] = RGB(      0,      0,155.391);
		RGBt[  7] = RGB(      0,      0,159.375);
		RGBt[  8] = RGB(      0,      0,163.359);
		RGBt[  9] = RGB(      0,      0,167.344);
		RGBt[ 10] = RGB(      0,      0,171.328);
		RGBt[ 11] = RGB(      0,      0,175.313);
		RGBt[ 12] = RGB(      0,      0,179.297);
		RGBt[ 13] = RGB(      0,      0,183.281);
		RGBt[ 14] = RGB(      0,      0,187.266);
		RGBt[ 15] = RGB(      0,      0, 191.25);
		RGBt[ 16] = RGB(      0,      0,195.234);
		RGBt[ 17] = RGB(      0,      0,199.219);
		RGBt[ 18] = RGB(      0,      0,203.203);
		RGBt[ 19] = RGB(      0,      0,207.188);
		RGBt[ 20] = RGB(      0,      0,211.172);
		RGBt[ 21] = RGB(      0,      0,215.156);
		RGBt[ 22] = RGB(      0,      0,219.141);
		RGBt[ 23] = RGB(      0,      0,223.125);
		RGBt[ 24] = RGB(      0,      0,227.109);
		RGBt[ 25] = RGB(      0,      0,231.094);
		RGBt[ 26] = RGB(      0,      0,235.078);
		RGBt[ 27] = RGB(      0,      0,239.063);
		RGBt[ 28] = RGB(      0,      0,243.047);
		RGBt[ 29] = RGB(      0,      0,247.031);
		RGBt[ 30] = RGB(      0,      0,251.016);
		RGBt[ 31] = RGB(      0,      0,    255);
		RGBt[ 32] = RGB(      0,  3.984,    255);
		RGBt[ 33] = RGB(      0,  7.969,    255);
		RGBt[ 34] = RGB(      0, 11.953,    255);
		RGBt[ 35] = RGB(      0, 15.938,    255);
		RGBt[ 36] = RGB(      0, 19.922,    255);
		RGBt[ 37] = RGB(      0, 23.906,    255);
		RGBt[ 38] = RGB(      0, 27.891,    255);
		RGBt[ 39] = RGB(      0, 31.875,    255);
		RGBt[ 40] = RGB(      0, 35.859,    255);
		RGBt[ 41] = RGB(      0, 39.844,    255);
		RGBt[ 42] = RGB(      0, 43.828,    255);
		RGBt[ 43] = RGB(      0, 47.813,    255);
		RGBt[ 44] = RGB(      0, 51.797,    255);
		RGBt[ 45] = RGB(      0, 55.781,    255);
		RGBt[ 46] = RGB(      0, 59.766,    255);
		RGBt[ 47] = RGB(      0,  63.75,    255);
		RGBt[ 48] = RGB(      0, 67.734,    255);
		RGBt[ 49] = RGB(      0, 71.719,    255);
		RGBt[ 50] = RGB(      0, 75.703,    255);
		RGBt[ 51] = RGB(      0, 79.688,    255);
		RGBt[ 52] = RGB(      0, 83.672,    255);
		RGBt[ 53] = RGB(      0, 87.656,    255);
		RGBt[ 54] = RGB(      0, 91.641,    255);
		RGBt[ 55] = RGB(      0, 95.625,    255);
		RGBt[ 56] = RGB(      0, 99.609,    255);
		RGBt[ 57] = RGB(      0,103.594,    255);
		RGBt[ 58] = RGB(      0,107.578,    255);
		RGBt[ 59] = RGB(      0,111.563,    255);
		RGBt[ 60] = RGB(      0,115.547,    255);
		RGBt[ 61] = RGB(      0,119.531,    255);
		RGBt[ 62] = RGB(      0,123.516,    255);
		RGBt[ 63] = RGB(      0,  127.5,    255);
		RGBt[ 64] = RGB(      0,131.484,    255);
		RGBt[ 65] = RGB(      0,135.469,    255);
		RGBt[ 66] = RGB(      0,139.453,    255);
		RGBt[ 67] = RGB(      0,143.438,    255);
		RGBt[ 68] = RGB(      0,147.422,    255);
		RGBt[ 69] = RGB(      0,151.406,    255);
		RGBt[ 70] = RGB(      0,155.391,    255);
		RGBt[ 71] = RGB(      0,159.375,    255);
		RGBt[ 72] = RGB(      0,163.359,    255);
		RGBt[ 73] = RGB(      0,167.344,    255);
		RGBt[ 74] = RGB(      0,171.328,    255);
		RGBt[ 75] = RGB(      0,175.313,    255);
		RGBt[ 76] = RGB(      0,179.297,    255);
		RGBt[ 77] = RGB(      0,183.281,    255);
		RGBt[ 78] = RGB(      0,187.266,    255);
		RGBt[ 79] = RGB(      0, 191.25,    255);
		RGBt[ 80] = RGB(      0,195.234,    255);
		RGBt[ 81] = RGB(      0,199.219,    255);
		RGBt[ 82] = RGB(      0,203.203,    255);
		RGBt[ 83] = RGB(      0,207.188,    255);
		RGBt[ 84] = RGB(      0,211.172,    255);
		RGBt[ 85] = RGB(      0,215.156,    255);
		RGBt[ 86] = RGB(      0,219.141,    255);
		RGBt[ 87] = RGB(      0,223.125,    255);
		RGBt[ 88] = RGB(      0,227.109,    255);
		RGBt[ 89] = RGB(      0,231.094,    255);
		RGBt[ 90] = RGB(      0,235.078,    255);
		RGBt[ 91] = RGB(      0,239.063,    255);
		RGBt[ 92] = RGB(      0,243.047,    255);
		RGBt[ 93] = RGB(      0,247.031,    255);
		RGBt[ 94] = RGB(      0,251.016,    255);
		RGBt[ 95] = RGB(      0,    255,    255);
		RGBt[ 96] = RGB(  3.984,    255,251.016);
		RGBt[ 97] = RGB(  7.969,    255,247.031);
		RGBt[ 98] = RGB( 11.953,    255,243.047);
		RGBt[ 99] = RGB( 15.938,    255,239.063);
		RGBt[100] = RGB( 19.922,    255,235.078);
		RGBt[101] = RGB( 23.906,    255,231.094);
		RGBt[102] = RGB( 27.891,    255,227.109);
		RGBt[103] = RGB( 31.875,    255,223.125);
		RGBt[104] = RGB( 35.859,    255,219.141);
		RGBt[105] = RGB( 39.844,    255,215.156);
		RGBt[106] = RGB( 43.828,    255,211.172);
		RGBt[107] = RGB( 47.813,    255,207.188);
		RGBt[108] = RGB( 51.797,    255,203.203);
		RGBt[109] = RGB( 55.781,    255,199.219);
		RGBt[110] = RGB( 59.766,    255,195.234);
		RGBt[111] = RGB(  63.75,    255, 191.25);
		RGBt[112] = RGB( 67.734,    255,187.266);
		RGBt[113] = RGB( 71.719,    255,183.281);
		RGBt[114] = RGB( 75.703,    255,179.297);
		RGBt[115] = RGB( 79.688,    255,175.313);
		RGBt[116] = RGB( 83.672,    255,171.328);
		RGBt[117] = RGB( 87.656,    255,167.344);
		RGBt[118] = RGB( 91.641,    255,163.359);
		RGBt[119] = RGB( 95.625,    255,159.375);
		RGBt[120] = RGB( 99.609,    255,155.391);
		RGBt[121] = RGB(103.594,    255,151.406);
		RGBt[122] = RGB(107.578,    255,147.422);
		RGBt[123] = RGB(111.563,    255,143.438);
		RGBt[124] = RGB(115.547,    255,139.453);
		RGBt[125] = RGB(119.531,    255,135.469);
		RGBt[126] = RGB(123.516,    255,131.484);
		RGBt[127] = RGB(  127.5,    255,  127.5);
		RGBt[128] = RGB(131.484,    255,123.516);
		RGBt[129] = RGB(135.469,    255,119.531);
		RGBt[130] = RGB(139.453,    255,115.547);
		RGBt[131] = RGB(143.438,    255,111.563);
		RGBt[132] = RGB(147.422,    255,107.578);
		RGBt[133] = RGB(151.406,    255,103.594);
		RGBt[134] = RGB(155.391,    255, 99.609);
		RGBt[135] = RGB(159.375,    255, 95.625);
		RGBt[136] = RGB(163.359,    255, 91.641);
		RGBt[137] = RGB(167.344,    255, 87.656);
		RGBt[138] = RGB(171.328,    255, 83.672);
		RGBt[139] = RGB(175.313,    255, 79.688);
		RGBt[140] = RGB(179.297,    255, 75.703);
		RGBt[141] = RGB(183.281,    255, 71.719);
		RGBt[142] = RGB(187.266,    255, 67.734);
		RGBt[143] = RGB( 191.25,    255,  63.75);
		RGBt[144] = RGB(195.234,    255, 59.766);
		RGBt[145] = RGB(199.219,    255, 55.781);
		RGBt[146] = RGB(203.203,    255, 51.797);
		RGBt[147] = RGB(207.188,    255, 47.813);
		RGBt[148] = RGB(211.172,    255, 43.828);
		RGBt[149] = RGB(215.156,    255, 39.844);
		RGBt[150] = RGB(219.141,    255, 35.859);
		RGBt[151] = RGB(223.125,    255, 31.875);
		RGBt[152] = RGB(227.109,    255, 27.891);
		RGBt[153] = RGB(231.094,    255, 23.906);
		RGBt[154] = RGB(235.078,    255, 19.922);
		RGBt[155] = RGB(239.063,    255, 15.938);
		RGBt[156] = RGB(243.047,    255, 11.953);
		RGBt[157] = RGB(247.031,    255,  7.969);
		RGBt[158] = RGB(251.016,    255,  3.984);
		RGBt[159] = RGB(    255,    255,      0);
		RGBt[160] = RGB(    255,251.016,      0);
		RGBt[161] = RGB(    255,247.031,      0);
		RGBt[162] = RGB(    255,243.047,      0);
		RGBt[163] = RGB(    255,239.063,      0);
		RGBt[164] = RGB(    255,235.078,      0);
		RGBt[165] = RGB(    255,231.094,      0);
		RGBt[166] = RGB(    255,227.109,      0);
		RGBt[167] = RGB(    255,223.125,      0);
		RGBt[168] = RGB(    255,219.141,      0);
		RGBt[169] = RGB(    255,215.156,      0);
		RGBt[170] = RGB(    255,211.172,      0);
		RGBt[171] = RGB(    255,207.188,      0);
		RGBt[172] = RGB(    255,203.203,      0);
		RGBt[173] = RGB(    255,199.219,      0);
		RGBt[174] = RGB(    255,195.234,      0);
		RGBt[175] = RGB(    255, 191.25,      0);
		RGBt[176] = RGB(    255,187.266,      0);
		RGBt[177] = RGB(    255,183.281,      0);
		RGBt[178] = RGB(    255,179.297,      0);
		RGBt[179] = RGB(    255,175.313,      0);
		RGBt[180] = RGB(    255,171.328,      0);
		RGBt[181] = RGB(    255,167.344,      0);
		RGBt[182] = RGB(    255,163.359,      0);
		RGBt[183] = RGB(    255,159.375,      0);
		RGBt[184] = RGB(    255,155.391,      0);
		RGBt[185] = RGB(    255,151.406,      0);
		RGBt[186] = RGB(    255,147.422,      0);
		RGBt[187] = RGB(    255,143.438,      0);
		RGBt[188] = RGB(    255,139.453,      0);
		RGBt[189] = RGB(    255,135.469,      0);
		RGBt[190] = RGB(    255,131.484,      0);
		RGBt[191] = RGB(    255,  127.5,      0);
		RGBt[192] = RGB(    255,123.516,      0);
		RGBt[193] = RGB(    255,119.531,      0);
		RGBt[194] = RGB(    255,115.547,      0);
		RGBt[195] = RGB(    255,111.563,      0);
		RGBt[196] = RGB(    255,107.578,      0);
		RGBt[197] = RGB(    255,103.594,      0);
		RGBt[198] = RGB(    255, 99.609,      0);
		RGBt[199] = RGB(    255, 95.625,      0);
		RGBt[200] = RGB(    255, 91.641,      0);
		RGBt[201] = RGB(    255, 87.656,      0);
		RGBt[202] = RGB(    255, 83.672,      0);
		RGBt[203] = RGB(    255, 79.688,      0);
		RGBt[204] = RGB(    255, 75.703,      0);
		RGBt[205] = RGB(    255, 71.719,      0);
		RGBt[206] = RGB(    255, 67.734,      0);
		RGBt[207] = RGB(    255,  63.75,      0);
		RGBt[208] = RGB(    255, 59.766,      0);
		RGBt[209] = RGB(    255, 55.781,      0);
		RGBt[210] = RGB(    255, 51.797,      0);
		RGBt[211] = RGB(    255, 47.813,      0);
		RGBt[212] = RGB(    255, 43.828,      0);
		RGBt[213] = RGB(    255, 39.844,      0);
		RGBt[214] = RGB(    255, 35.859,      0);
		RGBt[215] = RGB(    255, 31.875,      0);
		RGBt[216] = RGB(    255, 27.891,      0);
		RGBt[217] = RGB(    255, 23.906,      0);
		RGBt[218] = RGB(    255, 19.922,      0);
		RGBt[219] = RGB(    255, 15.938,      0);
		RGBt[220] = RGB(    255, 11.953,      0);
		RGBt[221] = RGB(    255,  7.969,      0);
		RGBt[222] = RGB(    255,  3.984,      0);
		RGBt[223] = RGB(    255,      0,      0);
		RGBt[224] = RGB(251.016,      0,      0);
		RGBt[225] = RGB(247.031,      0,      0);
		RGBt[226] = RGB(243.047,      0,      0);
		RGBt[227] = RGB(239.063,      0,      0);
		RGBt[228] = RGB(235.078,      0,      0);
		RGBt[229] = RGB(231.094,      0,      0);
		RGBt[230] = RGB(227.109,      0,      0);
		RGBt[231] = RGB(223.125,      0,      0);
		RGBt[232] = RGB(219.141,      0,      0);
		RGBt[233] = RGB(215.156,      0,      0);
		RGBt[234] = RGB(211.172,      0,      0);
		RGBt[235] = RGB(207.188,      0,      0);
		RGBt[236] = RGB(203.203,      0,      0);
		RGBt[237] = RGB(199.219,      0,      0);
		RGBt[238] = RGB(195.234,      0,      0);
		RGBt[239] = RGB( 191.25,      0,      0);
		RGBt[240] = RGB(187.266,      0,      0);
		RGBt[241] = RGB(183.281,      0,      0);
		RGBt[242] = RGB(179.297,      0,      0);
		RGBt[243] = RGB(175.313,      0,      0);
		RGBt[244] = RGB(171.328,      0,      0);
		RGBt[245] = RGB(167.344,      0,      0);
		RGBt[246] = RGB(163.359,      0,      0);
		RGBt[247] = RGB(159.375,      0,      0);
		RGBt[248] = RGB(155.391,      0,      0);
		RGBt[249] = RGB(151.406,      0,      0);
		RGBt[250] = RGB(147.422,      0,      0);
		RGBt[251] = RGB(143.438,      0,      0);
		RGBt[252] = RGB(139.453,      0,      0);
		RGBt[253] = RGB(135.469,      0,      0);
		RGBt[254] = RGB(131.484,      0,      0);
		RGBt[255] = RGB(  127.5,      0,      0);
	}
	else if (type=="Topo_0")
	{
//		RGBt[  0] = RGB( 219, 191, 177);
//		RGBt[  1] = RGB( 219, 191, 177);
//		RGBt[  2] = RGB( 219, 191, 177);
//		RGBt[  3] = RGB( 218, 218, 218);
//		RGBt[  4] = RGB( 202, 199, 196);
		RGBt[  0] = RGB( 177, 191, 219);
		RGBt[  1] = RGB( 177, 191, 219);
		RGBt[  2] = RGB( 177, 191, 219);
		RGBt[  3] = RGB( 218, 218, 218);
		RGBt[  4] = RGB( 196, 199, 202);
		RGBt[  5] = RGB( 193, 193, 194);
		RGBt[  6] = RGB( 187, 186, 189);
		RGBt[  7] = RGB( 182, 182, 182);
		RGBt[  8] = RGB( 181, 181, 180);
		RGBt[  9] = RGB( 180, 179, 178);
		RGBt[ 10] = RGB( 180, 177, 176);
		RGBt[ 11] = RGB( 179, 176, 174);
		RGBt[ 12] = RGB( 177, 175, 172);
		RGBt[ 13] = RGB( 175, 174, 170);
		RGBt[ 14] = RGB( 173, 173, 169);
		RGBt[ 15] = RGB( 171, 172, 167);
		RGBt[ 16] = RGB( 170, 171, 166);
		RGBt[ 17] = RGB( 169, 170, 166);
		RGBt[ 18] = RGB( 169, 169, 166);
		RGBt[ 19] = RGB( 168, 168, 166);
		RGBt[ 20] = RGB( 167, 168, 166);
		RGBt[ 21] = RGB( 166, 167, 166);
		RGBt[ 22] = RGB( 166, 166, 166);
		RGBt[ 23] = RGB( 165, 165, 166);
		RGBt[ 24] = RGB( 164, 164, 165);
		RGBt[ 25] = RGB( 164, 164, 164);
		RGBt[ 26] = RGB( 163, 163, 163);
		RGBt[ 27] = RGB( 163, 162, 162);
		RGBt[ 28] = RGB( 162, 161, 160);
		RGBt[ 29] = RGB( 161, 161, 159);
		RGBt[ 30] = RGB( 161, 160, 158);
		RGBt[ 31] = RGB( 160, 159, 157);
		RGBt[ 32] = RGB( 160, 159, 156);
		RGBt[ 33] = RGB( 159, 158, 155);
		RGBt[ 34] = RGB( 159, 157, 154);
		RGBt[ 35] = RGB( 159, 157, 154);
		RGBt[ 36] = RGB( 158, 156, 153);
		RGBt[ 37] = RGB( 158, 156, 153);
		RGBt[ 38] = RGB( 158, 155, 152);
		RGBt[ 39] = RGB( 157, 155, 152);
		RGBt[ 40] = RGB( 157, 154, 151);
		RGBt[ 41] = RGB( 157, 154, 151);
		RGBt[ 42] = RGB( 156, 153, 150);
		RGBt[ 43] = RGB( 156, 152, 149);
		RGBt[ 44] = RGB( 156, 152, 149);
		RGBt[ 45] = RGB( 155, 151, 148);
		RGBt[ 46] = RGB( 155, 151, 148);
		RGBt[ 47] = RGB( 155, 151, 148);
		RGBt[ 48] = RGB( 154, 151, 148);
		RGBt[ 49] = RGB( 154, 150, 148);
		RGBt[ 50] = RGB( 153, 150, 148);
		RGBt[ 51] = RGB( 153, 150, 148);
		RGBt[ 52] = RGB( 152, 150, 148);
		RGBt[ 53] = RGB( 152, 150, 148);
		RGBt[ 54] = RGB( 152, 149, 148);
		RGBt[ 55] = RGB( 151, 149, 148);
		RGBt[ 56] = RGB( 151, 149, 147);
		RGBt[ 57] = RGB( 150, 149, 147);
		RGBt[ 58] = RGB( 150, 148, 147);
		RGBt[ 59] = RGB( 149, 148, 147);
		RGBt[ 60] = RGB( 149, 148, 147);
		RGBt[ 61] = RGB( 149, 148, 147);
		RGBt[ 62] = RGB( 148, 147, 147);
		RGBt[ 63] = RGB( 148, 147, 147);
		RGBt[ 64] = RGB( 147, 147, 147);
		RGBt[ 65] = RGB( 147, 147, 147);
		RGBt[ 66] = RGB( 146, 146, 146);
		RGBt[ 67] = RGB( 146, 146, 146);
		RGBt[ 68] = RGB( 146, 146, 146);
		RGBt[ 69] = RGB( 146, 146, 146);
		RGBt[ 70] = RGB( 145, 145, 145);
		RGBt[ 71] = RGB( 145, 145, 145);
		RGBt[ 72] = RGB( 145, 145, 145);
		RGBt[ 73] = RGB( 144, 144, 145);
		RGBt[ 74] = RGB( 144, 144, 145);
		RGBt[ 75] = RGB( 144, 144, 144);
		RGBt[ 76] = RGB( 144, 144, 144);
		RGBt[ 77] = RGB( 143, 143, 144);
		RGBt[ 78] = RGB( 143, 143, 144);
		RGBt[ 79] = RGB( 143, 143, 143);
		RGBt[ 80] = RGB( 142, 142, 143);
		RGBt[ 81] = RGB( 142, 142, 143);
		RGBt[ 82] = RGB( 142, 142, 143);
		RGBt[ 83] = RGB( 142, 142, 142);
		RGBt[ 84] = RGB( 141, 141, 142);
		RGBt[ 85] = RGB( 141, 141, 142);
		RGBt[ 86] = RGB( 141, 141, 142);
		RGBt[ 87] = RGB( 140, 140, 141);
		RGBt[ 88] = RGB( 140, 140, 141);
		RGBt[ 89] = RGB( 140, 140, 141);
		RGBt[ 90] = RGB( 140, 139, 140);
		RGBt[ 91] = RGB( 140, 139, 140);
		RGBt[ 92] = RGB( 140, 139, 140);
		RGBt[ 93] = RGB( 139, 138, 139);
		RGBt[ 94] = RGB( 139, 138, 139);
		RGBt[ 95] = RGB( 139, 138, 139);
		RGBt[ 96] = RGB( 139, 137, 138);
		RGBt[ 97] = RGB( 139, 137, 138);
		RGBt[ 98] = RGB( 138, 137, 138);
		RGBt[ 99] = RGB( 138, 136, 137);
		RGBt[ 100] = RGB( 138, 136, 137);
		RGBt[ 101] = RGB( 138, 136, 137);
		RGBt[ 102] = RGB( 138, 135, 136);
		RGBt[ 103] = RGB( 137, 135, 136);
		RGBt[ 104] = RGB( 137, 135, 136);
		RGBt[ 105] = RGB( 137, 134, 135);
		RGBt[ 106] = RGB( 137, 134, 135);
		RGBt[ 107] = RGB( 137, 134, 135);
		RGBt[ 108] = RGB( 136, 133, 134);
		RGBt[ 109] = RGB( 136, 133, 134);
		RGBt[ 110] = RGB( 136, 133, 134);
		RGBt[ 111] = RGB( 136, 132, 134);
		RGBt[ 112] = RGB( 136, 132, 134);
		RGBt[ 113] = RGB( 136, 132, 133);
		RGBt[ 114] = RGB( 135, 131, 133);
		RGBt[ 115] = RGB( 135, 131, 133);
		RGBt[ 116] = RGB( 135, 131, 133);
		RGBt[ 117] = RGB( 135, 130, 132);
		RGBt[ 118] = RGB( 135, 130, 132);
		RGBt[ 119] = RGB( 134, 130, 132);
		RGBt[ 120] = RGB( 134, 129, 132);
		RGBt[ 121] = RGB( 134, 129, 131);
		RGBt[ 122] = RGB( 134, 129, 131);
		RGBt[ 123] = RGB( 134, 128, 131);
		RGBt[ 124] = RGB( 133, 128, 131);
		RGBt[ 125] = RGB( 133, 128, 130);
		RGBt[ 126] = RGB( 133, 127, 130);
		RGBt[ 127] = RGB( 133, 127, 130);
		RGBt[ 128] = RGB( 133, 127, 130);
		RGBt[ 129] = RGB( 132, 126, 129);
		RGBt[ 130] = RGB( 132, 126, 129);
		RGBt[ 131] = RGB( 132, 126, 129);
		RGBt[ 132] = RGB( 132, 126, 129);
		RGBt[ 133] = RGB( 132, 126, 129);
		RGBt[ 134] = RGB( 132, 126, 129);
		RGBt[ 135] = RGB( 131, 126, 129);
		RGBt[ 136] = RGB( 131, 126, 128);
		RGBt[ 137] = RGB( 131, 126, 128);
		RGBt[ 138] = RGB( 131, 125, 128);
		RGBt[ 139] = RGB( 131, 125, 128);
		RGBt[ 140] = RGB( 130, 125, 128);
		RGBt[ 141] = RGB( 130, 125, 128);
		RGBt[ 142] = RGB( 130, 125, 128);
		RGBt[ 143] = RGB( 130, 125, 127);
		RGBt[ 144] = RGB( 130, 125, 127);
		RGBt[ 145] = RGB( 129, 125, 127);
		RGBt[ 146] = RGB( 129, 124, 127);
		RGBt[ 147] = RGB( 129, 124, 127);
		RGBt[ 148] = RGB( 129, 124, 127);
		RGBt[ 149] = RGB( 129, 124, 127);
		RGBt[ 150] = RGB( 128, 124, 126);
		RGBt[ 151] = RGB( 128, 124, 126);
		RGBt[ 152] = RGB( 128, 124, 126);
		RGBt[ 153] = RGB( 128, 124, 126);
		RGBt[ 154] = RGB( 128, 124, 126);
		RGBt[ 155] = RGB( 128, 123, 126);
		RGBt[ 156] = RGB( 127, 123, 126);
		RGBt[ 157] = RGB( 127, 123, 125);
		RGBt[ 158] = RGB( 127, 123, 125);
		RGBt[ 159] = RGB( 127, 123, 125);
		RGBt[ 160] = RGB( 127, 123, 125);
		RGBt[ 161] = RGB( 126, 123, 125);
		RGBt[ 162] = RGB( 126, 123, 125);
		RGBt[ 163] = RGB( 126, 122, 125);
		RGBt[ 164] = RGB( 126, 122, 124);
		RGBt[ 165] = RGB( 126, 122, 124);
		RGBt[ 166] = RGB( 125, 122, 124);
		RGBt[ 167] = RGB( 125, 122, 124);
		RGBt[ 168] = RGB( 125, 122, 124);
		RGBt[ 169] = RGB( 125, 122, 124);
		RGBt[ 170] = RGB( 125, 122, 124);
		RGBt[ 171] = RGB( 124, 121, 123);
		RGBt[ 172] = RGB( 124, 121, 123);
		RGBt[ 173] = RGB( 124, 121, 123);
		RGBt[ 174] = RGB( 124, 121, 123);
		RGBt[ 175] = RGB( 124, 121, 123);
		RGBt[ 176] = RGB( 123, 121, 123);
		RGBt[ 177] = RGB( 123, 121, 123);
		RGBt[ 178] = RGB( 123, 121, 123);
		RGBt[ 179] = RGB( 123, 121, 123);
		RGBt[ 180] = RGB( 122, 121, 123);
		RGBt[ 181] = RGB( 122, 121, 123);
		RGBt[ 182] = RGB( 122, 120, 122);
		RGBt[ 183] = RGB( 122, 120, 122);
		RGBt[ 184] = RGB( 121, 120, 122);
		RGBt[ 185] = RGB( 121, 120, 122);
		RGBt[ 186] = RGB( 121, 120, 122);
		RGBt[ 187] = RGB( 121, 120, 122);
		RGBt[ 188] = RGB( 120, 120, 122);
		RGBt[ 189] = RGB( 120, 120, 122);
		RGBt[ 190] = RGB( 120, 120, 122);
		RGBt[ 191] = RGB( 120, 120, 122);
		RGBt[ 192] = RGB( 119, 119, 121);
		RGBt[ 193] = RGB( 119, 119, 121);
		RGBt[ 194] = RGB( 119, 119, 121);
		RGBt[ 195] = RGB( 119, 119, 121);
		RGBt[ 196] = RGB( 119, 119, 121);
		RGBt[ 197] = RGB( 118, 119, 121);
		RGBt[ 198] = RGB( 118, 119, 121);
		RGBt[ 199] = RGB( 118, 119, 121);
		RGBt[ 200] = RGB( 118, 119, 121);
		RGBt[ 201] = RGB( 117, 119, 121);
		RGBt[ 202] = RGB( 117, 119, 121);
		RGBt[ 203] = RGB( 117, 118, 120);
		RGBt[ 204] = RGB( 117, 118, 120);
		RGBt[ 205] = RGB( 116, 118, 120);
		RGBt[ 206] = RGB( 116, 118, 120);
		RGBt[ 207] = RGB( 116, 118, 120);
		RGBt[ 208] = RGB( 116, 118, 120);
		RGBt[ 209] = RGB( 115, 118, 120);
		RGBt[ 210] = RGB( 115, 118, 120);
		RGBt[ 211] = RGB( 115, 118, 120);
		RGBt[ 212] = RGB( 115, 118, 120);
		RGBt[ 213] = RGB( 114, 117, 119);
		RGBt[ 214] = RGB( 114, 117, 119);
		RGBt[ 215] = RGB( 114, 117, 119);
		RGBt[ 216] = RGB( 114, 117, 118);
		RGBt[ 217] = RGB( 114, 117, 118);
		RGBt[ 218] = RGB( 114, 117, 118);
		RGBt[ 219] = RGB( 114, 116, 117);
		RGBt[ 220] = RGB( 113, 116, 117);
		RGBt[ 221] = RGB( 113, 116, 116);
		RGBt[ 222] = RGB( 113, 116, 116);
		RGBt[ 223] = RGB( 113, 116, 116);
		RGBt[ 224] = RGB( 113, 116, 115);
		RGBt[ 225] = RGB( 113, 115, 115);
		RGBt[ 226] = RGB( 113, 115, 115);
		RGBt[ 227] = RGB( 112, 115, 114);
		RGBt[ 228] = RGB( 112, 115, 114);
		RGBt[ 229] = RGB( 112, 115, 113);
		RGBt[ 230] = RGB( 112, 115, 113);
		RGBt[ 231] = RGB( 112, 114, 113);
		RGBt[ 232] = RGB( 112, 114, 112);
		RGBt[ 233] = RGB( 112, 114, 112);
		RGBt[ 234] = RGB( 111, 114, 111);
		RGBt[ 235] = RGB( 111, 114, 111);
		RGBt[ 236] = RGB( 111, 114, 111);
		RGBt[ 237] = RGB( 111, 113, 110);
		RGBt[ 238] = RGB( 111, 113, 110);
		RGBt[ 239] = RGB( 111, 113, 110);
		RGBt[ 240] = RGB( 111, 113, 109);
		RGBt[ 241] = RGB( 110, 113, 109);
		RGBt[ 242] = RGB( 110, 113, 108);
		RGBt[ 243] = RGB( 110, 112, 108);
		RGBt[ 244] = RGB( 110, 112, 108);
		RGBt[ 245] = RGB( 110, 112, 107);
		RGBt[ 246] = RGB( 110, 112, 107);
		RGBt[ 247] = RGB( 110, 112, 107);
		RGBt[ 248] = RGB( 109, 112, 106);
		RGBt[ 249] = RGB( 109, 111, 106);
		RGBt[ 250] = RGB( 109, 111, 105);
		RGBt[ 251] = RGB( 109, 111, 105);
		RGBt[ 252] = RGB( 109, 111, 105);
		RGBt[ 253] = RGB( 109, 111, 104);
		RGBt[ 254] = RGB( 109, 111, 104);
		RGBt[ 255] = RGB( 108, 110, 103);
	}
}

HBRUSH CTBEpolar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (( pWnd->GetDlgCtrlID() == IDC_STATIC_L )||
	    ( pWnd->GetDlgCtrlID() == IDC_STATIC_D )||
	    ( pWnd->GetDlgCtrlID() == IDC_STATIC_Q ))
	{
		CFont font ;
        if (!(HFONT)font)
		{
            LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfHeight = 14;
			lf.lfWeight = FW_BOLD;
			strcpy(lf.lfFaceName , "Arial");
            font.CreateFontIndirect(&lf);
        }
        pDC->SelectObject(&font);
		pDC->SetTextColor(RGB( 0, 0, 255 ));
		font.DeleteObject();
	}	
	return hbr;
}

void CTBEpolar::OnRadio1() 
{
	if(!m_flagLQ)
	{
		m_flagLQ = TRUE;
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(m_flagLQ);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(!m_flagLQ);
		CString str = m_flagLQ  ?  _Z("Direction-Level") : _Z("Direction-Quality");
		SetWindowText(str);
		Invalidate();
	}
}
void CTBEpolar::OnRadio2() 
{
	if(m_flagLQ)
	{
		m_flagLQ = FALSE;
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(m_flagLQ);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(!m_flagLQ);
		CString str = m_flagLQ  ?  _Z("Direction-Level") : _Z("Direction-Quality");
		SetWindowText(str);
		Invalidate();
	}
}

void CTBEpolar::OnCheck1() 
{
	m_single = !m_single;
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(!m_single);

	GetDlgItem(IDC_COMBO_Time)->EnableWindow(m_single);
	GetDlgItem(IDC_STATIC_R)->EnableWindow(m_single);
	GetDlgItem(IDC_STATIC_Time)->EnableWindow(m_single);
	Set_Static_R();
	Invalidate();
}

void CTBEpolar::OnSelchangeCOMBOFr() 
{
	GetFrequency();	
	Set_Static_R();
	Invalidate();
}

void CTBEpolar::OnSelchangeCOMBOTime() 
{
	m_i = m_COMBO_Time.GetCurSel();
	Set_Static_R();
	Invalidate();
}

void CTBEpolar::GetFrequency() 
{
	CString f,str;
	long n = m_COMBO_Fr.GetCurSel();
	m_COMBO_Fr.GetLBText(n,f);

	m_D.RemoveAll();
	m_Q.RemoveAll();
	m_L.RemoveAll();
	m_ListDateTime.RemoveAll();
	
	m_COMBO_Time.ResetContent();
	for(long i=0;i<m_F.GetSize();i++)
	{
		if(f==m_F.GetAt(i))
		{
			m_D.Add(m_D1.GetAt(i));
			m_Q.Add(m_Q1.GetAt(i));
			if(m_L1.GetSize()>0)		m_L.Add(m_L1.GetAt(i));
			
			m_ListDateTime.Add(m_TimeListREStotal[i]);
			str = m_TimeListREStotal[i];
			m_COMBO_Time.AddString(str);
		}
	}
	m_COMBO_Time.SetCurSel(0);
	m_i = 0;
}


void CTBEpolar::OnClose() 
{
	m_F.RemoveAll();
	m_L1.RemoveAll();
	m_Q1.RemoveAll();
	m_D1.RemoveAll();
	m_TimeListREStotal.RemoveAll();
	m_L.RemoveAll();
	m_Q.RemoveAll();
	m_D.RemoveAll();
	m_ListDateTime.RemoveAll();
	m_FreqUniq.RemoveAll();
	m_COMBO_Fr.ResetContent();

	CDialog::OnClose();
}

void CTBEpolar::OnBUTTONgoogleEarth() 
{
	int m_Num = m_F.GetSize();
	if(m_Num>0)
	{
		CString TxName = m_TxName;
		CString X1     = m_MOlon_degStr;				
		CString Y1     = m_MOlat_degStr;	
		if((X1.GetLength()>0)&&(Y1.GetLength()>0))
		{
			double X = atof(X1.Left(3)) + (atof(X1.Mid(4,2)))/60.0 + (atof(X1.Mid(6,6)))/3600.0;
			double Y = atof(Y1.Left(2)) + (atof(Y1.Mid(3,2)))/60.0 + (atof(Y1.Mid(5,6)))/3600.0;
			double MOlon_deg = ((X1.Mid(3,1))==_T("E")) ? X : -X;		//deg
			double MOlat_deg = ((Y1.Mid(2,1))==_T("N")) ? Y : -Y;		//deg

			CString str2,str = "";
			double RxLat, RxLon;
			for(int i=0;i<m_Num;i++)
			{
				CString TxID        = "";				
				CString TimeSample  = m_TimeListREStotal.GetAt(i);				
				double FrqSample  = atof(m_F.GetAt(i));				
				double az_deg     = m_D1.GetAt(i);
				int quality    = (int)m_Q1.GetAt(i);
				if(TimeSample.GetLength()>0)
				{
					reckon(MOlat_deg,MOlon_deg,20,az_deg,&RxLat,&RxLon);
			//		str2.Format(_T("<Placemark><name>%s_%s_%0.6lfMHz</name><Style><LineStyle><color>%s</color><width>1</width></LineStyle></Style><LineString><altitudeMode>relativeToGround</altitudeMode><coordinates>%lf,%lf,%lf %lf,%lf,%lf</coordinates></LineString></Placemark>"),TxID,TimeSample,FrqSample, quality2color( quality) ,MOlon_deg,MOlat_deg, 10.0 ,RxLon,RxLat,10.0);
					str2.Format(_T("<Placemark><name>%s_%s_%0.6lfMHz</name><Style><LineStyle><color>%s</color><width>1</width></LineStyle></Style><LineString><coordinates>%lf,%lf,%lf %lf,%lf,%lf</coordinates></LineString></Placemark>"),TxID,TimeSample,FrqSample, quality2color( quality) ,MOlon_deg,MOlat_deg, 0.0 ,RxLon,RxLat,0.0);
					str = str + str2;
				}//if

			}//for

			if(str.GetLength()>0)
			{
				int L = m_PathName.GetLength();
				m_PathName.Delete(L-4,4);
				m_PathName = m_PathName + ".kml";

	//			CString fileOUTkml = ((CThales_DrawApp *)AfxGetApp())->m_AppPath + "Reports\\" + TxName + "_" + MoTime + ".kml";
				CString fileOUTkml = m_PathName;
				CString sFile, sPath;
				BOOL flagShow = FALSE;
				if( KmlSave( &sFile, &sPath , &flagShow , fileOUTkml) )
				{
					sFile.Delete(sFile.GetLength()-4,4);
					fileOUTkml = sPath;

					//CString gifFile = ((CThales_DrawApp *)AfxGetApp())->m_AppPath + _T("Image_map\\st.gif");
					CString gifFile = m_AppPath + _T("Image_map\\st.gif");
					FILE *fp2 = fopen(fileOUTkml,_T("wt"));

					CString str1;
					str1.Format(_T("<kml>\n<Folder>\n<name>SMS4DC_THALES:%s</name>\n<open>1</open>"),sFile);
					fprintf(fp2,_T("%s\n"),str1);

					str2.Format(_T("<Placemark><name>%s</name><StyleMap id=\'msn_A\'><Pair><key>normal</key><styleUrl>#sn_A</styleUrl></Pair></StyleMap><Style id=\'sn_A\'><IconStyle><scale>0.9</scale><Icon><href>%s</href></Icon></IconStyle><LabelStyle><scale>0.7</scale></LabelStyle></Style><styleUrl>#msn_A</styleUrl><Point><coordinates>%lf,%lf,0</coordinates></Point></Placemark>"),TxName,gifFile ,MOlon_deg,MOlat_deg);
					fprintf(fp2,_T("%s \n"),str2);

					fprintf(fp2,_T("%s \n"),str);

					fprintf(fp2,_T("</Folder>\n</kml>"));
					fclose(fp2);
					if(flagShow)	ShellExecute(m_hWnd, "open", fileOUTkml, NULL, NULL, SW_SHOWNORMAL);
				}//if KmlSave

			}//if str
		}//if X1,Y1
	}//if m_Num

}


void CTBEpolar::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) 
{
	double pi=4.0*atan(1.0);
	double R = 6371.0;
//	double R = 6373.398513241601;

	double rng_rad = rng_km/R;
	double az_rad  = az_deg*pi/180.0;
	double lat_rad = lat_deg*pi/180.0;
	double lon_rad = lon_deg*pi/180.0;

	double temp1  = sin(lat_rad)*cos(rng_rad);          
	double temp2  = cos(lat_rad)*sin(rng_rad)*cos(az_rad);
	double newlat = asin(temp1+temp2);

	temp1  = sin(rng_rad)*sin(az_rad);            
	temp2  = cos(lat_rad)*cos(rng_rad);
	double temp3  = sin(lat_rad)*sin(rng_rad)*cos(az_rad);
	double newlon = lon_rad + atan2(temp1,temp2-temp3);

	*latC_deg=newlat*180.0/pi;
	*lonC_deg=newlon*180.0/pi;
}


CString CTBEpolar::quality2color(int quality) 
{
	COLORREF RGBt[10];
	RGBt[0] = RGB(0  ,0  ,170);
	RGBt[1] = RGB(0  ,0  ,255);
	RGBt[2] = RGB(0  ,85 ,255);
	RGBt[3] = RGB(0  ,170,255);
	RGBt[4] = RGB(0  ,255,255);
	RGBt[5] = RGB(85 ,255,170);
	RGBt[6] = RGB(170,255,85 );
	RGBt[7] = RGB(255,255,0  );
	RGBt[8] = RGB(255,170,0  );
	RGBt[9] = RGB(255,85 ,0  );

	if(quality<1)	quality = 1;
	if(quality>10)	quality = 10;

	COLORREF CL = RGBt[quality-1];

	CString str;
	str.Format(_T("FF%02X%02X%02X") , GetBValue(CL),GetGValue(CL),GetRValue(CL));
	return str;
}




BOOL CTBEpolar::KmlSave(CString *sFile,CString *sPath,BOOL *flagShow, CString sDefault) 
{
/*
	CFileDlg FileDLG(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "*.kml", NULL );
	if (FileDLG.DoModal() == IDOK)
	{
		*sPath = FileDLG.m_Path;		*sFile = FileDLG.m_FName;
		return true;
	}
	return false;
*/
//	char strFilter[] = {"Google Files(*.kml)|*.kml||"};
	CString strFilter = _Z("Google Files") +"(*.kml)|*.kml||";

	CFileDLG_ChangedType FileDLG(FALSE, ".kml", sDefault, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , strFilter);

	FileDLG.m_Lang = m_Lang;
	if (IsWin2000())		FileDLG.m_ofn.lStructSize = 88;		//76
	if (FileDLG.DoModal() == IDOK)
	{
		*sPath = FileDLG.GetPathName();
		*sFile = FileDLG.GetFileName();
		*flagShow = FileDLG.m_ShowFlag;
		return true;
	}
	return false;
}


// IsWin2000
BOOL CTBEpolar::IsWin2000()
{
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	BOOL bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO *) &osvi);
	if (!bOsVersionInfoEx)
	{
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO *) &osvi))
			return FALSE;
	}

	switch (osvi.dwPlatformId)
	{
		case VER_PLATFORM_WIN32_NT:
			if (osvi.dwMajorVersion >= 5)
				return TRUE;
			break;
	}
	return FALSE;
}
