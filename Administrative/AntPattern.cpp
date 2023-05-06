// AntPattern.cpp : implementation file
//

#include "stdafx.h"
#include "Administrative.h"
#include "AntPattern.h"
#include "test6.h"

// AntPattern.cpp : implementation file
//

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAntPattern dialog


CAntPattern::CAntPattern(CWnd* pParent /*=NULL*/)
	: CDialog(CAntPattern::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAntPattern)
	//}}AFX_DATA_INIT
}


void CAntPattern::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAntPattern)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAntPattern, CDialog)
	//{{AFX_MSG_MAP(CAntPattern)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntPattern message handlers

BOOL CAntPattern::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ThickLines=2;	
	m_fill=true;
	m_fillcolor=RGB(255,255,128);
	m_5degreestick=1;
	m_1degreestick=false;
	m_1dbtick=false;

	if(!ReadData())
		EndDialog(false);
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


bool CAntPattern::ReadData() 
{
	int KH=0,KV=0;
	CDatabase DB;
	CRecordset RS;
	CString m_AntCatID;
	double m_AngleHTmp[361],m_AngleVTmp[361],m_PatternHTmp[361],m_PatternVTmp[361];
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	CString SQL;
	SQL.Format(_T("Select AntCatID from antenna where antid=%ld"),m_AntID);
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,m_AntCatID);
	RS.Close();
	SQL.Format(_T("Select Pol from antcat where AntCatID=%s"),m_AntCatID);
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,m_Pol);
	RS.Close();
	m_Pol.TrimRight();
	SQL.Format(_T("select * from antdiag where antid=%s and polar='H' order by azm"),
		m_AntCatID);
	RS.Open(CRecordset::snapshot,SQL);
	if(RS.GetRecordCount()>0)
	{
		CString Ang,Attn,Pol;
		int j=0,k=0;
		for (int i=0;i<360;i++)
		{
			if(RS.IsEOF()) break;
			RS.GetFieldValue(1,Ang);
			RS.GetFieldValue(2,Pol);
			RS.GetFieldValue(3,Attn);
			if(m_Pol!=_T("V"))
			{
				m_AngleHTmp[i] = atoi(Ang);
				m_PatternHTmp[j++] = atof(Attn);
			}
			else
			{
				m_AngleVTmp[i] = atoi(Ang);
				m_PatternVTmp[j++] = atof(Attn);
			}
			RS.MoveNext();
		}
		KH=i;
	}
	RS.Close();
	SQL.Format(_T("select * from antdiag where antid=%s and polar='V' order by azm"),
		m_AntCatID);
	RS.Open(CRecordset::snapshot,SQL);
	if(RS.GetRecordCount()>0)
	{
		CString Ang,Attn,Pol;
		int j=0,k=0;
		for (int i=0;i<360;i++)
		{
			if(RS.IsEOF()) break;
			RS.GetFieldValue(1,Ang);
			RS.GetFieldValue(2,Pol);
			RS.GetFieldValue(3,Attn);
			if(m_Pol!=_T("V"))
			{
				m_AngleVTmp[i] = atoi(Ang);
				m_PatternVTmp[j++] = atof(Attn);
			}
			else
			{
				m_AngleHTmp[i] = atoi(Ang);
				m_PatternHTmp[j++] = atof(Attn);
			}
			RS.MoveNext();
		}
		KV=i;
	}
	RS.Close();
	DB.Close();

	
		m_AngleHTmp[KH] = 360;
		m_AngleVTmp[KV] = 360;
///		azmV[kV] = 360;
		m_PatternHTmp[KH] = m_PatternHTmp[0];
		m_PatternVTmp[KV] = m_PatternVTmp[0];

		//int m_NUM = 360; 
		for (int i=0;i<360;i++)
		{
			m_Angle[i]=i;
			m_PatternH[i] = Interp2(m_AngleHTmp,m_PatternHTmp,i,KH) ;
			m_PatternV[i] = Interp2(m_AngleVTmp,m_PatternVTmp,i,KV) ;
		}
		m_PatternH[360]=m_PatternH[0];
		m_PatternV[360]=m_PatternV[0];
		m_Angle[360]=360;

	return true;
}

void CAntPattern::DrawPattern(int HV,int x0,int y0,int radius,int offset) 
{
	CClientDC dc(this);
	CString str;
	double az,pi=4.0*atan(1.0);
	int i,x,y, x01,y01;
	int radius1 = radius;	

	double step=radius/10.0;
	radius1=radius;
	DrawEllipse(true,x0-radius1,y0-radius1,x0+radius1,y0+radius1);

	double a,r;
	CPoint pointH[361];

	if(m_Pol!=_T("M"))
	{
//////////////////////////////Draw Diagram//////////////////////////////////////////////
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
				//a = ((double)(90-i))*pi/180.0;
				a = ((double)(i))*pi/180.0;
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
		
		if (HV)
			str.Format(_Z(" Antenna Horizontal Pattern (Azimuth Angle)"));
		else
			str.Format(_Z(" Antenna Vertical Pattern (Elevation Angle)"));
	}
	else  // Mixed polarized
	{
//////////////////////////////Draw Diagram//////////////////////////////////////////////
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
				a = ((double)(i))*pi/180.0;
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
//			if(HV)
				str.Format("%d",i*10);
//			else
//			{
//				if (i<19)
//					str.Format("%d",i*10);
//				else
//					str.Format("%d",-360+i*10);
//			}
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
		
		if (HV)
		{
			str.Format(_Z(" H Polarization (E-Plane)"));
			((CWnd *)(this->GetDlgItem(IDC_H_PATTERN)))->SetWindowText(str);
		}
		else
		{
			str.Format(_Z(" V Polarization (E-Plane)"));
			((CWnd *)(this->GetDlgItem(IDC_V_PATTERN)))->SetWindowText(str);
		}
	}

	//GetParent()->SetWindowText(str);
}

void CAntPattern::DrawEllipse(BOOL nMode,int x1,int y1,int x2,int y2,int nStyle,int nWidth,COLORREF pColor,int x3,int y3,int x4,int y4,COLORREF bColor) 
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

void CAntPattern::DrawLine(int x1,int y1,int x2,int y2,int nStyle,int nWidth,COLORREF pColor) 
{
	CClientDC dc(this);
	CPen pen(nStyle,nWidth,pColor);
	CPen* OLDpen = dc.SelectObject(&pen);
	dc.MoveTo(x1,y1);
	dc.LineTo(x2,y2);
	dc.SelectObject(OLDpen);
}

void CAntPattern::Draw3Angle(int x1,int y1,int x2,int y2,int x3,int y3,int nStyle,int nWidth,COLORREF pColor,COLORREF bColor) 
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

void CAntPattern::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	DrawPattern(true,170+25,180+25,160,25);

	DrawPattern(false,545+25,180+25,160,25);
}

double CAntPattern::Interp2(double *D0,double *E0,double d,int num) 
{
	double d1,d2,E1,E2,Eb;
	if (d<D0[0])
	{
		d1=D0[0];d2=D0[1];
		E1=E0[0];E2=E0[1];
	}
	else if (d>D0[num-1])
	{
		d1=D0[num-2];d2=D0[num-1];
		E1=E0[num-2];E2=E0[num-1];
	}
	else
	{
		/////////////////////////////////////////////
		int n1=0;
		while(d>=D0[n1])
		{
			n1++;
			if (n1==num)
				break;
		}
		if (n1==0)
			n1=1;
		d1=D0[n1-1],E1=E0[n1-1];
		///////////////////////////////////////////////
		int n2=num-1;
		while(d<=D0[n2])
			n2--;
		d2=D0[n2+1],E2=E0[n2+1];
		////////////////////////////////////////////////
	}
	Eb=((d1==d2) ? E1 : E1+(E2-E1)*(d-d1)/(d2-d1));

	return Eb;

}

/////////////////////////////////////////////////////////////////////////////
// CAntPattern message handlers
