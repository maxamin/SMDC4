// ANTpatternDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "ANTpatternDLG.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CANTpatternDLG dialog


CANTpatternDLG::CANTpatternDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CANTpatternDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CANTpatternDLG)
	m_antfile = _T("ant_DEFAULT.ant");
	//}}AFX_DATA_INIT
}


void CANTpatternDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANTpatternDLG)
	DDX_Text(pDX, IDC_EDIT_Name, m_antfile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CANTpatternDLG, CDialog)
	//{{AFX_MSG_MAP(CANTpatternDLG)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANTpatternDLG message handlers

BOOL CANTpatternDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ThickLines=2;	
	m_fill=true;
	m_fillcolor=RGB(255,255,128);
	m_5degreestick=1;
	m_1degreestick=false;
	m_1dbtick=false;

	m_flag = ReadData(m_antfile) ;

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}


bool CANTpatternDLG::ReadData(CString antfile) 
{
	FILE *fid;
	m_flag = false;

	if((fid=fopen(antfile,"rt"))!=NULL)
	{
		m_flag = true;

		char Name [20],
			 Gain_dBi [20],
			 BeamWidth_H [20],
			 BeamWidth_V [20],
			 Frq_Lo [20],
			 Frq_Hi [20],
			 Frq_unit [20],
			 Polarization [20],
			 dum[20];

		char Ang[20],PatH[20],PatV[20];

		fscanf( fid, "%s %s", dum,Name);
		fscanf( fid, "%s %s", dum,Gain_dBi);
		fscanf( fid, "%s %s", dum,BeamWidth_H);
		fscanf( fid, "%s %s", dum,BeamWidth_V);
		fscanf( fid, "%s %s", dum,Frq_Lo);
		fscanf( fid, "%s %s", dum,Frq_Hi);
		fscanf( fid, "%s %s", dum,Frq_unit);
		fscanf( fid, "%s %s", dum,Polarization);
		fscanf( fid, "%s", dum);

	//	m_Name = Name;
	//	m_Gain_dBi = atof(Gain_dBi);
	//	m_BeamWidth_H = atof(BeamWidth_H);
	//	m_BeamWidth_V = atof(BeamWidth_V);
	//	m_Frq_Lo = atof(Frq_Lo);
	//	m_Frq_Hi = atof(Frq_Hi);
	//	m_Frq_unit = Frq_unit;
	//	m_Polarization = Polarization;

		for (int i=0;i<360;i++)
		{
			fscanf( fid, "%s %s %s", Ang,PatH,PatV);
			m_Angle[i] = atoi(Ang);
			m_PatternH[i] = atof(PatH);
			m_PatternV[i] = atof(PatV);
		}
		fclose(fid);
	}
	return m_flag;
}


void CANTpatternDLG::DrawPattern(int HV,int x0,int y0,int radius,int offset) 
{
	CClientDC dc(this);
	CString str;
	double az,pi=4.0*atan(1.0);
	int i,x,y, x01,y01;
	int radius1 = radius;	

	double step=radius/10.0;
	radius1=radius;
	DrawEllipse(true,x0-radius1,y0-radius1,x0+radius1,y0+radius1);

//////////////////////////////Draw Diagram//////////////////////////////////////////////
	double a,r;
	CPoint pointH[361];
	for ( i=0;i<360;i++)
	{
		if (HV)
		{
			r = radius-(step/5.0)*min(50.0,m_PatternH[i]);
			a = ((double)(i))*pi/180.0;
		}
		else 
		{
			r = radius-(step/5.0)*min(50.0,m_PatternV[i]);
			a = ((double)(90-i))*pi/180.0;
		}
		x=int(x0+r*sin(a));
		y=int(y0-r*cos(a));
		pointH[i]=CPoint(x,y);
	}
	pointH[360]=pointH[0];

	CPen pen(PS_SOLID,m_ThickLines,RGB(0,0,255));
	dc.SelectObject(&pen);
	dc.Polyline(pointH,361);

	if (m_fill)
	{
		CBrush brush(m_fillcolor);
		dc.SelectObject(&brush);
		dc.Polygon(pointH,361);
	}
//////////////////////////////////////////////////////////////////////////////////
	if(m_1dbtick)
	{
		for (int i=1;i<=50;i++)
		{
			radius1=int(radius-(step/5.0)*i);
			DrawEllipse(false,x0-radius1,y0-radius1,x0+radius1,y0+radius1,PS_DOT,1,RGB(0,255,0),x0,offset,x0,offset);
		}
	}
	if(m_1degreestick)
	{
		for ( i=0;i<36*10;i++)
		{
			az=( i*10.0/10)*pi/180.0;
			x = int(offset + radius + radius*sin(az));
			y = int(offset + radius - radius*cos(az));
			if ( (i!=0*10) && (i!=9*10) && (i!=18*10) && (i!=27*10) )
			{
				x01 = int(offset + radius - 4*step + 4*step + 4*step*sin(az));
				y01 = int(offset + radius - 4*step + 4*step - 4*step*cos(az));
			}
			else
			{
				x01=x0;
				y01=y0;
			}
			DrawLine(x01,y01,x,y,PS_DOT,1,RGB(0,255,0));
		}
	}
///////////////////////////////////////////////////////////////////////////////////////
	for ( i=1;i<=10;i++)
	{
		radius1=int(radius-step*i);
		DrawEllipse(false,x0-radius1,y0-radius1,x0+radius1,y0+radius1,PS_SOLID,1,RGB(0,255,0),x0,offset,x0,offset);
	}

	for (i=0;i<36*m_5degreestick;i++)
	{
		az=(i*10.0/m_5degreestick)*pi/180.0;
		x = int(x0 + radius*sin(az));
		y = int(y0 - radius*cos(az));
		if ( (i!=0*m_5degreestick) && (i!=9*m_5degreestick) && (i!=18*m_5degreestick) && (i!=27*m_5degreestick) )
		{
			x01 = int(x0 - step + step + step*sin(az));
			y01 = int(y0 - step + step - step*cos(az));
		}
		else
		{
			x01=x0;
			y01=y0;
		}
		DrawLine(x01,y01,x,y,PS_SOLID,1,RGB(0,255,0));

	}

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextAlign(TA_CENTER);
	for (i=0;i<36;i++)
	{
		az=(i*10.0)*pi/180.0;
		x = int(   x0-radius-12 + (radius+12)*(1.0 + sin(az))   );
		y = int(   y0-radius-20 + (radius+12)*(1.0 - cos(az))   );
		if(HV)
			str.Format("%d",i*10);
		else
		{
			if (i<19)
				str.Format("%d",i*10);
			else
				str.Format("%d",-360+i*10);
		}
		dc.TextOut(x,y,str);
	}
	dc.SetTextAlign(TA_TOP);
	dc.TextOut(x0,int(y0-radius+1.0*step/15.0),"-3");
	dc.TextOut(x0,int(y0-radius+2.0*step),"-10");
	dc.TextOut(x0,int(y0-radius+4.0*step),"-20");
	dc.TextOut(x0,int(y0-radius+6.0*step),"-30");
	dc.TextOut(x0,int(y0-radius+8.0*step),"-40");

	Draw3Angle(x0,y0-radius-5,x0-5,y0-radius+5,x0+5,y0-radius+5);

	radius1=int(radius-3.0*step/5.0);
	DrawEllipse(false,x0-radius1,y0-radius1,x0+radius1,y0+radius1,PS_SOLID,1,RGB(0,0,0),x0,offset,x0,offset);

}

void CANTpatternDLG::DrawEllipse(BOOL nMode,int x1,int y1,int x2,int y2,int nStyle,int nWidth,COLORREF pColor,int x3,int y3,int x4,int y4,COLORREF bColor) 
{
	CClientDC dc(this);
	CBrush brush(bColor);
	CBrush* OLDbrush = dc.SelectObject(&brush);
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = dc.SelectObject(&pen);

	if (nMode)
		dc.Ellipse(x1,y1,x2,y2);
	else
		dc.Arc(x1,y1,x2,y2,x3,y3,x4,y4);

	dc.SelectObject(OLDbrush);
	dc.SelectObject(OLDpen);
}

void CANTpatternDLG::DrawLine(int x1,int y1,int x2,int y2,int nStyle,int nWidth,COLORREF pColor) 
{
	CClientDC dc(this);
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = dc.SelectObject(&pen);
	dc.MoveTo(x1,y1);
	dc.LineTo(x2,y2);
	dc.SelectObject(OLDpen);
}

void CANTpatternDLG::Draw3Angle(int x1,int y1,int x2,int y2,int x3,int y3,int nStyle,int nWidth,COLORREF pColor,COLORREF bColor) 
{
	CClientDC dc(this);
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = dc.SelectObject(&pen);

	CBrush brush(bColor);
	CBrush* OLDbrush = dc.SelectObject(&brush);

	CPoint point[3];
	point[0]=CPoint(x1,y1);
	point[1]=CPoint(x2,y2);
	point[2]=CPoint(x3,y3);
	dc.Polygon(point,3);

	dc.SelectObject(OLDbrush);
	dc.SelectObject(OLDpen);
}

void CANTpatternDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (m_flag)
	{
		DrawPattern(true,170+25,180+25,160,25);
		DrawPattern(false,545+25,180+25,160,25);
		SetWindowText(m_antfile);
	}
}
