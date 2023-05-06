// TxRxFilterDLG.cpp : implementation file
//

#include "stdafx.h"
#include "Administrative.h"
#include "TxRxFilterDLG.h"
#include <math.h>
#include "afxdb.h"
#include "TxRxFiltersSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTxRxFilterDLG dialog


CTxRxFilterDLG::CTxRxFilterDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CTxRxFilterDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTxRxFilterDLG)
	m_Channelsep = 14.0;
	//}}AFX_DATA_INIT
	m_AxesT=0;
	m_AxesH=0;
	m_AxesL=0;
	m_AxesW=0;

	m_fuFlag = 1;
	m_TxRx = 1;
	m_num = 20;
}


void CTxRxFilterDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTxRxFilterDLG)
	DDX_Control(pDX, IDC_COMBO_fu, m_fu);
	DDX_Text(pDX, IDC_EDIT_Channelsep, m_Channelsep);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_ListGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTxRxFilterDLG, CDialog)
	//{{AFX_MSG_MAP(CTxRxFilterDLG)
	ON_BN_CLICKED(IDC_BUTTON_Draw, OnBUTTONDraw)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_fu, OnSelchangeCOMBOfu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTxRxFilterDLG message handlers

BOOL CTxRxFilterDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_fu.AddString(_T("kHz"));	
	m_fu.AddString(_T("MHz"));	
	m_fu.AddString(_T("GHz"));	
	m_fu.SetCurSel(m_fuFlag);

	if(m_TxRx==1)
		m_title =_Z("Transmitter spectrum mask");
	if(m_TxRx==2)
		m_title =_Z("Receiver spectrum mask");
	if(m_TxRx==3)
		m_title =_Z("Earth station spectrum mask");
	SetWindowText(m_title);

	int nCOLS = 3;	
	m_ListGrid.SetCols(0,nCOLS);
	m_ListGrid.SetColWidth(0,0,300);
	m_ListGrid.SetColWidth(1,0,2300);
	m_ListGrid.SetColWidth(2,0,900);
	m_ListGrid.SetRow(0);
	m_ListGrid.SetCol(1);
	m_ListGrid.SetText(_Z("Frequency - Center Frequency"));
	m_ListGrid.SetCellAlignment(4);

	m_ListGrid.SetCol(2);
	m_ListGrid.SetText(_Z("Atten.(dB)"));
	m_ListGrid.SetCellAlignment(4);

	m_ListGrid.SetRows(21);
	LoadData();

	CString str;
	for(int i=0;i<m_num;i++)
	{
		m_ListGrid.SetRow(i+1);
		m_ListGrid.SetCol(1);	str.Format("%g",m_f[i]);	m_ListGrid.SetText(str);
		m_ListGrid.SetCol(2);	str.Format("%g",m_a[i]);	m_ListGrid.SetText(str);
	}
	OnBUTTONDraw();
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog(this);

	return TRUE;  
}

void CTxRxFilterDLG::LoadData()
{
	CString SQL;
	CDatabase DB;
	CRecordset RS;
	RS.m_pDatabase=&DB;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	if(m_TxRx==1)
		SQL.Format(_T("select Frequency.ChannelSep,TXFilters.* from Frequency,TXFilters where FreqID=TXFilters.EqID and FreqID=%ld"),m_ID);
	if(m_TxRx==2)
		SQL.Format(_T("select Frequency.ChannelSep,RXFilters.* from Frequency,RXFilters where FreqID=RXFilters.EqID and FreqID=%ld"),m_ID);
	if(m_TxRx==3)
		SQL.Format(_T("select * from ESFilters where EqID=%ld"),m_ID);
	RS.Open(CRecordset::snapshot,SQL);
	int i=0;
	if(RS.GetRecordCount()>0)
	{
		while(true)
		{
			CString Value;
			if(RS.IsEOF()) break;
			if(m_TxRx<3)
			{
				RS.GetFieldValue((short)0,Value);
				m_Channelsep=atof(Value);
				RS.GetFieldValue(2,Value);
				m_f[i]=atof(Value);
				RS.GetFieldValue(3 ,Value);
				m_a[i]=atof(Value);
			}
			else
			{
				RS.GetFieldValue(1,Value);
				m_f[i]=atof(Value);
				RS.GetFieldValue(2 ,Value);
				m_a[i]=atof(Value);
			}
			RS.MoveNext();
			i++;
		}
		m_num=i;
	}
	else
	{
		m_f[0]=-28.;
		m_f[1]=-22.;
		m_f[2]=-20.;
		m_f[3]=-14.;
		m_f[4]=-12.;
		m_f[5]=-8.;
		m_f[6]=0.;
		m_f[7]=8.;
		m_f[8]=12.;
		m_f[9]=14.;
		m_f[10]=20.;
		m_f[11]=22.;
		m_f[12]=28.;
		m_a[0]=41.;
		m_a[1]=40.;
		m_a[2]=26.7;
		m_a[3]=17.8;
		m_a[4]=17.8;
		m_a[5]=0.;
		m_a[6]=0.;
		m_a[7]=0.;
		m_a[8]=17.8;
		m_a[9]=17.8;
		m_a[10]=26.7;
		m_a[11]=40.;
		m_a[12]=41.;
		m_num=13;
		AfxMessageBox(_Z("No filter is defined. Default values loaded."));
	}
	RS.Close();
	DB.Close();
	UpdateData(false);
}

void CTxRxFilterDLG::OnBUTTONDraw() 
{
	UpdateData();
	CString str1,str2;
	double ft[20], at[20], minF, maxF, z1;

	m_ListGrid.SetRow(1);
	m_ListGrid.SetCol(1);	str1 = m_ListGrid.GetText();
	minF = maxF = atof(str1);
	//////////////////////// Get Data from Grid /////////////////////
	int i1, j1, i, n = 0;
	for(i = 0; i<20 ; i++)
	{
		m_ListGrid.SetRow(i+1);
		m_ListGrid.SetCol(1);	str1 = m_ListGrid.GetText();
		m_ListGrid.SetCol(2);	str2 = m_ListGrid.GetText();
		if((!str1.IsEmpty()) && (!str2.IsEmpty()) && atof(str2)>=0)
		{
			ft[n] = atof(str1);
			at[n] = atof(str2);
			minF = min(minF,ft[n]);
			maxF = max(maxF,ft[n]);
			n++;
		}
	}
	m_num = n;
	//////////////////////// Sort /////////////////////
	for(j1=0;j1<n;j1++)
	{
		for(i1 = j1+1;i1<n;i1++)
		{
			if(ft[i1]<ft[j1])
			{
				z1 = ft[i1];	ft[i1] = ft[j1];	ft[j1] = z1;
				z1 = at[i1];	at[i1] = at[j1];	at[j1] = z1;
			}
		}
	}
	//////////////////////// fill Grid /////////////////////
	for(i=0;i<20;i++)
	{
		if(i<n)
		{
			str1.Format("%g",ft[i]);
			str2.Format("%g",at[i]);
		}
		else
			str1 = str2 = "";
		m_ListGrid.SetRow(i+1);
		m_ListGrid.SetCol(1);	m_ListGrid.SetText(str1);
		m_ListGrid.SetCol(2);	m_ListGrid.SetText(str2);
	}
	//////////////////////// Set Data /////////////////////
	for(i = 0; i<m_num ; i++)
	{
		m_f[i] = ft[i];
		m_a[i] = at[i];
	//	m_f[i] = minF + i*(maxF-minF)/19.0;
	//	m_a[i] = interwt(ft,at,n,m_f[i]) ;
		str1.Format("%0.3f",m_f[i]);	m_f[i] = atof(str1);
		str1.Format("%0.3f",m_a[i]);	m_a[i] = atof(str1);
	}
	Invalidate();
	UpdateData(false);		
}

double CTxRxFilterDLG::interwt(double *ft,double *at,int n,double f0) 
{
	double t0;

	if (f0>ft[n-1])
		t0 = at[n-1];
	else if (f0<ft[0])
		t0 = at[0];
	else
	{
		for (int i=0;i<n;i++)
		{
            if (ft[i]==f0)
			{
                t0 = at[i];
                break;
			}
            else if (ft[i]>f0)
			{
				t0=at[i-1]+(f0-ft[i-1])*(at[i]-at[i-1])/(ft[i]-ft[i-1]);
                break;
            }
		}
	}
	return t0;
}

void CTxRxFilterDLG::OnPaint() 
{
	CPaintDC pDC(this); // device context for painting
	
	int i;
	double ft[20], at[20], atp[20];

	for(i=0;i<m_num;i++)
	{
		ft[i] = m_f[i];
		at[i] = m_a[i];
		atp[i] = -at[i];
	}
//////////////////////////Drawing///////////////////////////////////////////
	pDC.SetMapMode(MM_LOMETRIC);

	CRect rect;
	///////////////////////////////////////
	if (pDC.IsPrinting())
		rect=m_rcPrintRect;
	else
		GetClientRect(&rect);
	pDC.DPtoLP(&rect);

	initDP_LP(&pDC);							//1400/04/20
///////////////////////////////////////

//	CBrush brush(RGB(204,204,204));
//	pDC.FillRect(rect,&brush);

	int AxesW = (int)((rect.Width()));
	int AxesH = (int)((rect.Height()));
	int AxesT = (int)(rect.top  );
	int AxesL = (int)(rect.left );

	m_AxesT = AxesT+3*AxesH/50;
	m_AxesH = AxesH-AxesH/5+2*AxesH/50;
	m_AxesW = AxesW-2*AxesW/50;
	m_AxesL = AxesL+AxesW/2+3*AxesW/100;

	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(0,0,0));
	pDC.SelectObject(&pen);
	pDC.Rectangle(m_AxesL-0,m_AxesT,m_AxesW+0,m_AxesH);

	double fMIN = MinValue(ft,m_num);
	double fMAX = MaxValue(ft,m_num);
	double tMIN = MinValue(atp,m_num);
	double tMAX = MaxValue(atp,m_num);
	if (m_TxRx==1)
		Plot(&pDC,ft,atp,m_num,  fMIN,fMAX,tMIN,tMAX,  5,RGB(0,0,150),PS_SOLID,1,RGB(0,0,150)) ;
	else
		Plot(&pDC,ft,atp,m_num,  fMIN,fMAX,tMIN,tMAX,  5,RGB(150,0,0),PS_SOLID,1,RGB(150,0,0)) ;

	Xtick(&pDC,fMIN,fMAX);
	YtickL(&pDC,tMIN,tMAX);
}
double CTxRxFilterDLG::MinValue(double *xi,int N) 
{
	double  xiMIN = xi[0];
	for (int i=1;i<N;i++)
		xiMIN = min(xiMIN,xi[i]);	
	return xiMIN;
}
double CTxRxFilterDLG::MaxValue(double *xi,int N) 
{
	double  xiMAX = xi[0];
	for (int i=1;i<N;i++)
		xiMAX = max(xiMAX,xi[i]);	
	return xiMAX;
}


void CTxRxFilterDLG::Plot(CPaintDC* pDC,double *xi, double *yi,int N,
						double xiMIN,double xiMAX,double yiMIN,double yiMAX,
						int nWidth,COLORREF crColor, int nStyle, int nMode,COLORREF flColor) 
{
	double AxesT=m_AxesT;
	double AxesH=m_AxesH;
	double AxesW=m_AxesW;
	double AxesL=m_AxesL;
//////////////////////////plot////////////////////////////////////

	CPoint *pts;
	pts=new CPoint[N+2];

	for (int i=0;i<N;i++)
	{
		pts[i].x = Round( AxesL + (AxesW - AxesL)*(xi[i] - xiMIN)/(xiMAX-xiMIN) );
		pts[i].y = Round( AxesH + (AxesT - AxesH)*(yi[i] - yiMIN)/(yiMAX-yiMIN) );
	}
	pts[N].x = pts[N-1].x ;
	pts[N].y = long(AxesH);
	pts[N+1].x = pts[0].x ;
	pts[N+1].y = long(AxesH);

	CPen pen(nStyle, nWidth, crColor);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush brush(flColor);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	if (nMode==0)
		pDC->Polyline(pts, N+2);
	else
		pDC->Polygon(pts, N+2);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	delete [] pts;

}


void CTxRxFilterDLG::Xtick(CPaintDC* pDC,double xiMIN,double xiMAX) 
{
	CString label;
	double r,step_m,xround=0,xiMAXr;
	int x=0,xNum=10;

	if (xiMIN != xiMAX)
	{
		step_m = (xiMAX-xiMIN)/xNum;
		r = ((step_m>10.0) ? 10.0 : ((step_m>1.0) ? 1.0 :  ((step_m>0.1) ? 0.1 : ((step_m>0.01) ? 0.01 : ((step_m>0.001) ? 0.001 : ((step_m>0.0001) ? 0.0001 : 0.00001))))));
		step_m=((int)(((xiMAX-xiMIN)/xNum)/r))*r;
		xiMAXr=((int)(xiMAX/r))*r;

		xround=(xiMIN+xiMAX)/2.0;		int i=0;
		while ( xround<=xiMAX && xround>=xiMIN )
		{
			xround=(xiMIN+i*step_m);
			x=(int)(m_AxesL+( xround - xiMIN )*(m_AxesW-m_AxesL)/(xiMAX-xiMIN));
			if (xround<=xiMAX && xround>=xiMIN)
			{
		//		LineDraw(pDC,x,m_AxesH,x,m_AxesH-20,6) ;
				LineDraw(pDC,x,m_AxesH,x,m_AxesH-m_fontH20,m_fontH6) ;					//1400/04/20
				LineDraw(pDC,x,m_AxesT,x,m_AxesH,1,RGB(0,255,0),PS_DOT) ;
				label.Format("%g",xround);
		//		TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,38);
				TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,0,0),900,m_fontH30);	//1400/04/20
			}
			i++;
		}
	}
	else
	{
		x=m_AxesW/2;
//		LineDraw(pDC,x,m_AxesH,x,m_AxesH-20,6) ;
		LineDraw(pDC,x,m_AxesH,x,m_AxesH-m_fontH20,m_fontH6) ;					//1400/04/20
		label.Format("%g",xiMIN);
//		TextDraw(pDC,x+20,m_AxesH-28,label,RGB(0,0,0),900,38);
		TextDraw(pDC,x+m_fontH20,m_AxesH-m_fontH28,label,RGB(0,0,0),900,m_fontH30);	//1400/04/20
	}

}

void CTxRxFilterDLG::TextDraw(CPaintDC* pDC,int x, int y,CString str,COLORREF FontColor,
							int Escapement,
							int nHeight,int nWidth,int FontWeight,CString FontName) 
{
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


void CTxRxFilterDLG::YtickL(CPaintDC* pDC,double yiMIN,double yiMAX) 
{
	CString label;
	double r, step_m,yround=0, yiMAXr;
	int y=0,yNum=10;

	if (yiMAX != yiMIN)
	{
		step_m = (yiMAX-yiMIN)/yNum;
		r = ((step_m>10.0) ? 10.0 : ((step_m>1.0) ? 1.0 :  ((step_m>0.1) ? 0.1 : ((step_m>0.01) ? 0.01 : 0.001))));
		step_m=((int)(((yiMAX-yiMIN)/yNum)/r))*r;
		yiMAXr=((int)(yiMAX/r))*r;

		yround=(yiMIN+yiMAX)/2.0;		int i=0;
		while ( yround<=yiMAX && yround>=yiMIN )
		{
			yround=(yiMAXr-i*step_m);
			y=(int)(m_AxesT+( yiMAX - yround )*(m_AxesH-m_AxesT)/(yiMAX-yiMIN));
			if ( yround<=yiMAX && yround>=yiMIN )
			{
		//		LineDraw(pDC,m_AxesL,y,m_AxesL-20,y,6) ;
				LineDraw(pDC,m_AxesL,y,m_AxesL-m_fontH20,y,m_fontH6) ;					//1400/04/20
				LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(0,255,0),PS_DOT) ;
				label.Format("%g",-yround);
		//		TextDraw(pDC,93*m_AxesL/100,y+20,label,RGB(0,0,0),0,38) ;
				TextDraw(pDC,93*m_AxesL/100,y+m_fontH20,label,RGB(0,0,0),0,m_fontH30) ;	//1400/04/20
			}
			i++;
		}

	}
	else
	{
		y=m_AxesH/2;
//		LineDraw(pDC,m_AxesL,y,m_AxesL-20,y,6) ;
		LineDraw(pDC,m_AxesL,y,m_AxesL-m_fontH20,y,m_fontH6) ;					//1400/04/20
		LineDraw(pDC,m_AxesL,y,m_AxesW,y,1,RGB(0,0,255),PS_DOT) ;
		label.Format("%g",yiMIN);
//		TextDraw(pDC,93*m_AxesL/100,y+20,label,RGB(0,0,0),0,38) ;
		TextDraw(pDC,93*m_AxesL/100,y+m_fontH20,label,RGB(0,0,0),0,m_fontH30) ;	//1400/04/20
	}
}


void CTxRxFilterDLG::LineDraw(CPaintDC* pDC,int x1, int y1,int x2, int y2,
							int nWidth, COLORREF crColor, int nStyle) 
{
		CPen pen;
		pen.CreatePen(nStyle,nWidth,crColor);
		pDC->SelectObject(&pen);
		pDC->MoveTo(x1,y1);
		pDC->LineTo(x2,y2);
}


int CTxRxFilterDLG::Round(double x) 
{
	int x1 = (int) x;
	int x2 = x1+1;
	return ( (x > ((double)x1)+0.4) ? x2 : x1);

}

void CTxRxFilterDLG::OnSelchangeCOMBOfu() 
{
	UpdateData();
	int i, j = m_fu.GetCurSel();
	if(m_fuFlag != j)
	{
		OnBUTTONDraw();
		double dum;CString str1;
		for(i = 0; i<m_num ; i++)
		{
			m_f[i] = m_f[i]*pow(1000.0,m_fuFlag-j);
			m_ListGrid.SetRow(i+1);
			m_ListGrid.SetCol(1);	str1 = m_ListGrid.GetText();

			if((!str1.IsEmpty()) && (!str1.IsEmpty()))
			{
				dum = atof(str1);
				dum = dum*pow(1000.0,m_fuFlag-j);
				str1.Format("%g",dum);
				m_ListGrid.SetText(str1);
			}
		}
		m_fuFlag = j;
		InvalidateRect(NULL,false);
	}
	UpdateData(false);		
}

void CTxRxFilterDLG::OnOK() 
{
	int yy;
	yy = MessageBox(_Z("Filter values are going to be changed.\t\rThe old values will be lost if you choose 'Yes' button.\t\r\rDo you want to save the new values?\t"), _T("Warning"), MB_ICONQUESTION | MB_YESNO);
	if(yy==6)
	{
		OnBUTTONDraw();

		Delete_set(m_ID);

		int i, j = m_fu.GetCurSel();
		CString str;
		if(m_TxRx==1)
			str.Format(_T("SELECT * FROM TxFilters WHERE EqID=%ld"),m_ID);
		if(m_TxRx==2)
			str.Format(_T("SELECT * FROM RxFilters WHERE EqID=%ld"),m_ID);
		if(m_TxRx==3)
			str.Format(_T("SELECT * FROM ESFilters WHERE EqID=%ld"),m_ID);
		CTxRxFiltersSet m_pSet(m_CDBSTR,str);
		m_pSet.Open();
		for( i=0;i<m_num;i++)
		{
			m_pSet.AddNew();
			m_pSet.m_EqID  = m_ID;
			m_pSet.m_CS  = m_f[i]*pow(1000.0,j-1);
			m_pSet.m_Att = m_a[i];
			m_pSet.Update();
		}
		m_pSet.Close();
	}
	CDialog::OnOK();
}

void CTxRxFilterDLG::Delete_set(long ID) 
{
	CString str;
	if(m_TxRx==1)
		str.Format(_T("SELECT * FROM TxFilters WHERE (((EqID)=%ld)) ORDER BY EqID;"),m_ID);
	if(m_TxRx==2)
		str.Format(_T("SELECT * FROM RxFilters WHERE (((EqID)=%ld)) ORDER BY EqID;"),m_ID);
	if(m_TxRx==3)
		str.Format(_T("SELECT * FROM ESFilters WHERE EqID=%ld"),m_ID);
	CTxRxFiltersSet m_pSet(m_CDBSTR,str);
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

//1400/04/20
int CTxRxFilterDLG::DP_LP(CDC* pDC,int nH_DP) //1400/04/20
{
	if (pDC->IsPrinting())		return (int)(nH_DP*30.0/12.0);

	CSize z1(0, nH_DP);
	pDC->DPtoLP(&z1);
	return z1.cy;
}
void CTxRxFilterDLG::initDP_LP(CDC * pDC) //1400/04/20
{
	m_fontH2   = DP_LP(pDC,  1); //2
	m_fontH6   = DP_LP(pDC,  2); //6
	m_fontH12  = DP_LP(pDC,  5); //12
	m_fontH14  = DP_LP(pDC,  6); //14
	m_fontH20  = DP_LP(pDC,  8); //20
	m_fontH24  = DP_LP(pDC, 10); //24
	m_fontH28  = DP_LP(pDC, 11); //28
	m_fontH30  = DP_LP(pDC, 12); //30
	m_fontH40  = DP_LP(pDC, 16); //40
	m_fontH44  = DP_LP(pDC, 18); //44
	m_fontH46  = DP_LP(pDC, 19); //46
	m_fontH100 = DP_LP(pDC, 40); //100
	m_fontH150 = DP_LP(pDC, 60); //150
}