// Allocations_DrawView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Allocations_DrawView.h"
#include "Allocations_DrawDoc.h"
#include <math.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawView

IMPLEMENT_DYNCREATE(CAllocations_DrawView, CFormView)

CAllocations_DrawView::CAllocations_DrawView()
	: CFormView(CAllocations_DrawView::IDD)
{
	//{{AFX_DATA_INIT(CAllocations_DrawView)
	//}}AFX_DATA_INIT

	m_Fustr = _Z("Frequency (MHz)");
	m_Bandstr="";
	m_SRVstr="";
	m_SRVstrfot="";
	m_SRVstrfotPS="";

	m_ListNUM = 0;

//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarALLplan), TRUE, FALSE);
}

CAllocations_DrawView::~CAllocations_DrawView()
{
	int i;
	for (i=0;i<4;i++)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.DeleteString(0);
	for (i=0;i<3;i++)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlUnit.DeleteString(0);
	for (i=0;i<2;i++)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlScale.DeleteString(0);
	for (i=0;i<m_ListNUM;i++)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.DeleteString(0);

	if(m_ListNUM>0)
		delete [] m_ArtS5_codeList;

//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarALLplan), FALSE, FALSE);
}

void CAllocations_DrawView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAllocations_DrawView)
	DDX_Control(pDX, IDC_EDIT_Doc, m_EDIT_Doc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAllocations_DrawView, CFormView)
	//{{AFX_MSG_MAP(CAllocations_DrawView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT_PLAN, OnEditPlan)
	ON_CBN_SELCHANGE(IDC_CBREGION, OnSelchangeCOMBOregions)
	ON_CBN_SELCHANGE(IDC_CBUNIT, OnSelchangeCOMBOunit)
	ON_CBN_SELCHANGE(IDC_CBSCALE, OnSelchangeCOMBOscale)
	ON_BN_CLICKED(IDC_CBAPPLY, OnApply)
	ON_CBN_SELCHANGE(IDC_CBS5, OnSelchangeCOMBOArt5)
	ON_COMMAND(ID_EDIT_SERVICETABLE, OnEditServicetable)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PLAN, OnUpdateEditPlan)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SERVICETABLE, OnUpdateEditServicetable)
	ON_COMMAND(ID_EDIT_FOOTNOTE, OnEditFootnote)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FOOTNOTE, OnUpdateEditFootnote)
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_FILE_IMPORT_PLAN, OnFileImportPlan)
	ON_COMMAND(ID_FILE_IMPORT_SERVICETABLE, OnFileImportServicetable)
	ON_COMMAND(ID_FILE_IMPORT_FOOTNOTE, OnFileImportFootnote)
	ON_COMMAND(ID_FILE_EXPORT_PLAN, OnFileExportPlan)
	ON_COMMAND(ID_FILE_EXPORT_SERVICETABLE, OnFileExportServicetable)
	ON_COMMAND(ID_FILE_EXPORT_FOOTNOTE, OnFileExportFootnote)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawView diagnostics

#ifdef _DEBUG
void CAllocations_DrawView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAllocations_DrawView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawView message handlers

void CAllocations_DrawView::OnDraw(CDC* pDC) 
{
	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();

	if(pDoc->m_ReadyDoc ==1)
	{
		CRect rect1;
		GetClientRect(rect1);

		m_AxesW1 = (0.98)*(rect1.Width());
		m_AxesH1 = (0.8)*(rect1.Height());
		m_AxesT1 = rect1.top + rect1.Height() - 0.84 * m_AxesH1;
		m_AxesL1 = rect1.left + rect1.Width() - m_AxesW1;

		pDC->SetMapMode(MM_LOMETRIC);
		CRect rect;
	///////////////////////////////////////
		if (pDC->IsPrinting())	rect = m_rcPrintRect;
		else					GetClientRect(&rect);
		pDC->DPtoLP(&rect);

initDP_LP(pDC);

	///////////////////////////////////////

		m_AxesW = (0.98)*(rect.Width());
		m_AxesH = (0.8)*(rect.Height());
		m_AxesT = rect.top + rect.Height() - 0.84 * m_AxesH;
		m_AxesL = rect.left + rect.Width() - m_AxesW;

		double xiMIN=pDoc->m_Recs[0].FRQ_LO,xiMAX=pDoc->m_Recs[pDoc->m_RecsNUM-1].FRQ_HI,yiMIN=0,yiMAX=1 ,f1,f2;
		int x1,y1,x2,y2 ,fsrv ,SRV_p_s,SRV_sat;
		COLORREF srvRGB;
		CString str;

        if (pDoc->m_Lin_Log==1)
		{
           xiMIN=log10(xiMIN);	xiMAX=log10(xiMAX);
		}
		
		for (int i=0;i<pDoc->m_RecsNUM;i++)
		{
			fsrv = pDoc->m_Recs[i].SRVnum;
			f1 = pDoc->m_Recs[i].FRQ_LO;
			f2 = pDoc->m_Recs[i].FRQ_HI;

			if (pDoc->m_Lin_Log==1)
			{
			   f1=log10(f1);	f2=log10(f2);
			}

			x1 = int( m_AxesL + (m_AxesW - m_AxesL)*(f1 - xiMIN)/(xiMAX-xiMIN) );
			x2 = int( m_AxesL + (m_AxesW - m_AxesL)*(f2 - xiMIN)/(xiMAX-xiMIN) );

			for (int j=0;j<fsrv;j++)
			{
				srvRGB = pDoc->m_Recs[i].srvC[fsrv-1-j];
				y1 = int( m_AxesH + (m_AxesT - m_AxesH)*(yiMAX*j/fsrv - yiMIN)/(yiMAX-yiMIN) );
				y2 = int( m_AxesH + (m_AxesT - m_AxesH)*(yiMAX*(j+1)/fsrv - yiMIN)/(yiMAX-yiMIN) );

				SRV_p_s = pDoc->m_Recs[i].SRV_p_s[fsrv-1-j];
				SRV_sat = pDoc->m_Recs[i].SRV_sat[fsrv-1-j];

				DrawRectangle(pDC,&m_rgnSRV[i][fsrv-1-j],x1,y1,x2,y2,srvRGB,SRV_p_s,SRV_sat); 
			}

			if (pDoc->m_Lin_Log==1)
			{
			   f1=pow(10.0,f1);	f2=pow(10.0,f2);
			}

			y1 = int( m_AxesH + (m_AxesT - m_AxesH)*(yiMAX+0.01 - yiMIN)/(yiMAX-yiMIN) );
			
			if      (pDoc->m_Fu==0)		f1 = f1*1000.0;
			else if (pDoc->m_Fu==2)		f1 = f1/1000.0;
			
//			str.Format("%0.3f",f1);
			str.Format("%g",f1);
			TextDraw(pDC,(x1-15),y1,str,RGB(0,0,0),2700,m_fontH40,0,FW_BOLD) ;
		}

		if      (pDoc->m_Fu==0)		f2 = f2*1000.0;
		else if (pDoc->m_Fu==2)		f2 = f2/1000.0;

//		str.Format("%0.3f",f2);
		str.Format("%g",f2);
		TextDraw(pDC,(x2-25),y1,str,RGB(0,0,0),2700,m_fontH40,0,FW_BOLD) ;

		CRgn rgn0;
/* 971101
		TextDraw(pDC,int(m_AxesL),(-25),    m_Bandstr,    RGB(0,0,180),0,m_fontH48,0,FW_BOLD,"Times") ;
		TextDraw(pDC,int(m_AxesL),(-50-25), m_SRVstr,     RGB(0,0,127),0,m_fontH48,0,FW_BOLD,"Times") ;
		TextDraw(pDC,int(m_AxesL),(-100-25),m_SRVstrfotPS,RGB(0,100,0),0,m_fontH48,0,FW_BOLD,"Times") ;
		TextDraw(pDC,int(m_AxesL),(-150-25),m_SRVstrfot,  RGB(200,0,0),0,m_fontH48,0,FW_BOLD,"Times") ;

		//Black Line
		DrawRectangle(pDC,&rgn0,	0,  (-220-25),	  int(m_AxesW+100),	(-220-25-5),RGB(127,0,127),1,0); 

		TextDraw(pDC,int(m_AxesW-300),(-25),_Z("Secondary Service"),RGB(0,0,0),0,m_fontH42,0,FW_NORMAL) ;
		DrawRectangle(pDC,&rgn0,int(m_AxesW-250),(-75),	int(m_AxesW-250+180),(-75-90),RGB(255,255,255),0,0); 

		TextDraw(pDC,int(m_AxesW-630),(-25),_Z("Satellite Service"),RGB(0,0,0),0,m_fontH42,0,FW_NORMAL) ;
		DrawRectangle(pDC,&rgn0,int(m_AxesW-600),(-75),		int(m_AxesW-600+180),(-75-90),RGB(127,0,127),1,1); 
*/
		TextDraw(pDC,int(m_AxesL),(-m_fontH25), m_Bandstr,    RGB(0,0,180),0,m_fontH48,0,FW_BOLD,"Times") ;
		TextDraw(pDC,int(m_AxesL),(-m_fontH75),	m_SRVstr,     RGB(0,0,127),0,m_fontH48,0,FW_BOLD,"Times") ;
		TextDraw(pDC,int(m_AxesL),(-m_fontH125),m_SRVstrfotPS,RGB(0,100,0),0,m_fontH48,0,FW_BOLD,"Times") ;
		TextDraw(pDC,int(m_AxesL),(-m_fontH175),m_SRVstrfot,  RGB(200,0,0),0,m_fontH48,0,FW_BOLD,"Times") ;

		//Black Line
		DrawRectangle(pDC,&rgn0,	0,  (-m_fontH245),	  int(m_AxesW+m_fontH100),	(-m_fontH250),RGB(127,0,127),1,0); 

		TextDraw(pDC,int(m_AxesW-m_fontH300),(-m_fontH25),_Z("Secondary Service"),RGB(0,0,0),0,m_fontH42,0,FW_NORMAL) ;
		DrawRectangle(pDC,&rgn0,int(m_AxesW-m_fontH250),(-m_fontH75),	int(m_AxesW-m_fontH70),(-m_fontH165),RGB(255,255,255),0,0); 

		TextDraw(pDC,int(m_AxesW-m_fontH630),(-m_fontH25),_Z("Satellite Service"),RGB(0,0,0),0,m_fontH42,0,FW_NORMAL) ;
		DrawRectangle(pDC,&rgn0,int(m_AxesW-m_fontH600),(-m_fontH75),	int(m_AxesW-m_fontH420),(-m_fontH165),RGB(127,0,127),1,1); 

		TextDraw(pDC,int((m_AxesW-m_AxesL-100)/2),int(m_AxesH),m_Fustr,RGB(0,0,0),0,m_fontH48,0,FW_BOLD,"Times") ;
		m_EDIT_Doc.SetWindowPos(NULL,int(m_AxesL1),int(m_AxesH1+25), int(m_AxesW1-m_AxesL1),65,	 SWP_ASYNCWINDOWPOS);
	}
	pDC->SetTextColor(RGB(255,0,0));

}

void CAllocations_DrawView::DrawRectangle(CDC* pDC,CRgn *rgn1,int x1,int y1,int x2,int y2,COLORREF fColor,int SRV_p_s,int SRV_sat) 
{
	pDC->SetBkMode(TRANSPARENT);

	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	CBrush brush(fColor);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(x1,y1,x2,y2);

	rgn1->DeleteObject();
	rgn1->CreateRectRgn(x1,y1,x2,y2);

	pDC->SelectObject(pOldBrush);
	DeleteObject(brush);		DeleteObject(pOldBrush);//971102


	int RV,GV,BV,dx,dy;
	COLORREF fColor1;

	if (SRV_sat==1)
	{
		int step=20;
		double dxs = double(x2-x1)/double(step);
		double dxe = double(x2-x1)/2.0;
		double dys = double(y2-y1)/double(step);
		double dye = double(y2-y1)/2.0;

		dxs=dxs*2.0;
		dys=dys*2.0;

		for (int i=0;i<step;i++)
		{
			RV = min(255,GetRValue(fColor)+i*(255-GetRValue(fColor))/(step-1));
			GV = min(255,GetGValue(fColor)+i*(255-GetGValue(fColor))/(step-1));
			BV = min(255,GetBValue(fColor)+i*(255-GetBValue(fColor))/(step-1));
			fColor1 = RGB(RV,GV,BV);
			dx =int(dxs + i*( (dxe-dxs)/(step-1.0) ));
			dy =int(dys + i*( (dye-dys)/(step-1.0) ));

			CPen pen1(PS_SOLID,1,fColor1);
			CPen* pOldPen1 = pDC->SelectObject(&pen1);

			CBrush brush2(fColor1);
			CBrush* pOldBrush2 = pDC->SelectObject(&brush2);

			pDC->Ellipse(x1+dx,y1+dy,x2-dx,y2-dy);

			pDC->SelectObject(pOldBrush2);
			pDC->SelectObject(pOldPen1);

			DeleteObject(pen1);			DeleteObject(pOldPen1);  //971102
			DeleteObject(brush2);		DeleteObject(pOldBrush2);//971102
		}
	}

	if (SRV_p_s==0)
	{
		CBrush brush1(HS_BDIAGONAL,RGB(0,0,0));
		CBrush* pOldBrush1 = pDC->SelectObject(&brush1);
		pDC->Rectangle(x1,y1,x2,y2);
		pDC->SelectObject(pOldBrush1);
		DeleteObject(brush1);		DeleteObject(pOldBrush1);//971102
	}

	pDC->SelectObject(pOldPen);
	DeleteObject(pen);			DeleteObject(pOldPen);//971102
}


void CAllocations_DrawView::TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor,
							int Escapement,
							int nHeight,int nWidth,int FontWeight,CString FontName) 
{
	pDC->SetBkMode(TRANSPARENT);
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));      // zero out structure
	lf.lfHeight = nHeight;                // request a 12-pixel-height font
	lf.lfWidth =nWidth;
	lf.lfWeight = FontWeight;
	strcpy(lf.lfFaceName, FontName);       // request a face name "Arial"
	lf.lfEscapement=Escapement;
	VERIFY(font.CreateFontIndirect(&lf));  // create the font

	CFont* def_font = pDC->SelectObject(&font);

	pDC->SetTextColor(FontColor);
	pDC->TextOut(x,y,str);
	pDC->SelectObject(def_font);

	font.DeleteObject(); 
	DeleteObject(def_font);//971102
}

void CAllocations_DrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x1 = int( m_AxesL + (m_AxesW - m_AxesL)*(point.x - m_AxesL1)/(m_AxesW1 - m_AxesL1) );
	int y1 = int( m_AxesT + (m_AxesH - m_AxesT)*(point.y - m_AxesT1)/(m_AxesH1 - m_AxesT1) );
	CPoint point1(x1,y1);

	if ( (point.x >= m_AxesL1) && (point.x <= m_AxesW1) && (point.y>=m_AxesT1) && (point.y<=m_AxesH1) )
	{
		CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
		int fsrv=0,i=0,j=0,kj;
		for ( i=0;i<pDoc->m_RecsNUM;i++)
		{
			fsrv = pDoc->m_Recs[i].SRVnum;
			for ( j=0;j<fsrv;j++)
			{
				kj=fsrv-1-j;
				if(m_rgnSRV[i][kj].PtInRegion(point1))		break;
			}
			if(m_rgnSRV[i][kj].PtInRegion(point1))			break;
		}
		CString str,FOTPS,FOTt,SRVname;
		SRVname =     pDoc->m_Recs[i].SRVname[kj];
		FOTPS =       pDoc->m_Recs[i].SRV_fot[kj];
		FOTt =        pDoc->m_Recs[i].SRV_fotT;

		double f1 = pDoc->m_Recs[i].FRQ_LO;
		double f2 = pDoc->m_Recs[i].FRQ_HI;
		if (pDoc->m_Fu==0)
		{
			f1 = f1*1000.0;
			f2 = f2*1000.0;
		}
		else if (pDoc->m_Fu==2)
		{
			f1 = f1/1000.0;
			f2 = f2/1000.0;
		}
//		str.Format(_Z("Frequency Band") + " :  %0.3f - %0.3f   %s",f1,f2,m_Fustr.Mid(11,3));    
		str.Format(_Z("Frequency Band") + " :  %0.3f - %0.3f   %s",f1,f2, GetUnitFreq(m_Fustr));  //940312
		m_Bandstr = str;

		int SRV_p_s = pDoc->m_Recs[i].SRV_p_s[kj];

		if (SRV_p_s)	str.Format(_Z("Primary Service :")   + " %s",SRVname);
		else			str.Format(_Z("Secondary Service :") + " %s",SRVname);
		m_SRVstr = str;

		str.Format(_Z("Service Footnote :") + " %s",FOTPS);	m_SRVstrfotPS = str;
		str.Format(_Z("Band Footnote :") + " %s",FOTt);		m_SRVstrfot   = str;
	}
	else
	{
		m_Bandstr="";
		m_SRVstr="";
		m_SRVstrfot="";
		m_SRVstrfotPS="";
	}
//	InvalidateRect(CRect(0,0,int(m_AxesW1-170),90),true);
	InvalidateRect(CRect(0,0,int(m_AxesW1-170),100),true);    //940312

	CFormView::OnLButtonDown(nFlags, point);
}

void CAllocations_DrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( (point.x >= m_AxesL1) && (point.x <= m_AxesW1) && (point.y>=m_AxesT1) && (point.y<=m_AxesH1) )
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	else
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	
	CFormView::OnMouseMove(nFlags, point);
}

void CAllocations_DrawView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

//	initDP_LP();

	CString Title_En  = "Frequency Allocations 2D Chart";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.ResetContent();
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.AddString(_Z("Region 1"));
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.AddString(_Z("Region 2"));
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.AddString(_Z("Region 3"));
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.AddString(_Z("National"));
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.SetCurSel(2);
	
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlEdit_Flo.SetWindowText("8025");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlEdit_Fhi.SetWindowText("9200");

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlUnit.ResetContent();
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlUnit.AddString("kHz");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlUnit.AddString("MHz");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlUnit.AddString("GHz");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlUnit.SetCurSel(1);

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlScale.ResetContent();
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlScale.AddString(_Z("Linear"));
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlScale.AddString(_Z("Logarithmic"));
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlScale.SetCurSel(0);

	m_ListNUM = ArtS5_codeList(TRUE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.ResetContent();
	for (long i=0;i<m_ListNUM;i++)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.AddString(m_ArtS5_codeList[i]);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.SetCurSel(0);

	OnSelchangeCOMBOArt5() ;
//	m_EDIT_Doc.SetWindowText(_T("In all documents of the Union where the terms allocation, allotment and assignment are to be used, they shall have the meaning given them in Nos. 1.16 to 1.18, the terms used in the three working languages being as follows:"));

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE21);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog((CDialog *)this);
}


long CAllocations_DrawView::ArtS5_codeList(BOOL S5_N)
{
	long NUM = 0;

	CODBCFieldInfo FldInfo;
	CDatabase m_mydb;
	CRecordset m_rs;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	CString	m_Tbl;
//	if(S5_N)	m_Tbl=_T("select Article_code from Art_S5");
//	else		m_Tbl=_T("select Article_code from Art_S5N");
	if(S5_N)	m_Tbl = _T("SELECT Article_code FROM Art_S5table  ORDER BY IIf(Len(Int(Val(Mid([Article_code],3,10))))=1,'00'+Mid([Article_code],3,10),IIf(Len(Int(Val(Mid([Article_code],3,10))))=2,'0'+Mid([Article_code],3,10),Mid([Article_code],3,10)));");
	else		m_Tbl = _T("SELECT Article_code FROM Art_S5Ntable ORDER BY Article_code;");

	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		m_rs.m_pDatabase=&m_mydb;
		m_rs.Open( CRecordset::snapshot, m_Tbl);

		if(m_rs.GetRecordCount() == 1)
		{
			m_rs.MoveFirst();
			while(1)
			{
				if(m_rs.IsEOF()) break;
				NUM++;
				m_rs.MoveNext();
			}
			m_ArtS5_codeList = new CString[NUM];

			m_rs.MoveFirst();
			for (long i=0;i<NUM;i++)
			{
				m_rs.GetFieldValue(short(0), m_ArtS5_codeList[i]);
				m_rs.MoveNext();
			}
		}
	}
	m_rs.Close();
	m_mydb.Close();
	return NUM;
}

CString CAllocations_DrawView::Code2Doc(CString code_str , BOOL S5_N)
{
	CODBCFieldInfo FldInfo;
	CDatabase m_mydb;
	CRecordset m_rs;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	CString	m_Tbl;

	CString m_LangApp = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
	if(m_LangApp==_T("En"))
	{
//		if(S5_N)	m_Tbl=_T("select Article_doc_En from Art_S5");
//		else		m_Tbl=_T("select Article_doc_En from Art_S5N");
		if(S5_N)	m_Tbl=_T("select Article_doc_En from Art_S5table");
		else		m_Tbl=_T("select Article_doc_En from Art_S5Ntable");
	}
	else if(m_LangApp==_T("Fr"))
	{
//		if(S5_N)	m_Tbl=_T("select Article_doc_Fr from Art_S5");
//		else		m_Tbl=_T("select Article_doc_Fr from Art_S5N");
		if(S5_N)	m_Tbl=_T("select Article_doc_Fr from Art_S5table");
		else		m_Tbl=_T("select Article_doc_Fr from Art_S5Ntable");
	}
	else if(m_LangApp==_T("Es"))  //940312
	{
		if(S5_N)	m_Tbl=_T("select Article_doc_Es from Art_S5table");
		else		m_Tbl=_T("select Article_doc_Es from Art_S5Ntable");
	}
	else if(m_LangApp==_T("Ch"))  //940312
	{
		if(S5_N)	m_Tbl=_T("select Article_doc_Ch from Art_S5table");
		else		m_Tbl=_T("select Article_doc_Ch from Art_S5Ntable");
	}
	else if(m_LangApp==_T("Ar"))  //940312
	{
		if(S5_N)	m_Tbl=_T("select Article_doc_Ar from Art_S5table");
		else		m_Tbl=_T("select Article_doc_Ar from Art_S5Ntable");
	}
	else if(m_LangApp==_T("Ru"))  //940312
	{
		if(S5_N)	m_Tbl=_T("select Article_doc_Ru from Art_S5table");
		else		m_Tbl=_T("select Article_doc_Ru from Art_S5Ntable");
	}
	else
	{
//		if(S5_N)	m_Tbl=_T("select Article_doc_En from Art_S5");
//		else		m_Tbl=_T("select Article_doc_En from Art_S5N");
		if(S5_N)	m_Tbl=_T("select Article_doc_En from Art_S5table");
		else		m_Tbl=_T("select Article_doc_En from Art_S5Ntable");
	}

	CString Filter;
	CString Article_doc=_T("");

	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		m_rs.m_pDatabase=&m_mydb;
		Filter.Format("(Article_code=\'%s\')",code_str);

		if(m_Tbl.Find(" where ")==-1)	Filter = m_Tbl + " where " + Filter;
		else							Filter = m_Tbl + " and "   + Filter;

		m_rs.Open( CRecordset::snapshot, Filter);
		m_rs.MoveFirst();

		m_rs.GetFieldValue(short(0), Article_doc);
	}
	m_rs.Close();
	m_mydb.Close();

	return Article_doc;
}


void CAllocations_DrawView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pInfo)
	{
		m_rcPrintRect = pInfo->m_rectDraw;
	}

	CFormView::OnPrint(pDC, pInfo);
}
void CAllocations_DrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CAllocations_DrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) 
{
}
BOOL CAllocations_DrawView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}


void CAllocations_DrawView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CFormView::OnFilePrintPreview();
}
void CAllocations_DrawView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CFormView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

void CAllocations_DrawView::OnEditPlan() 
{
	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();

	CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\tRegion1234.tmp");
	FILE *fp = fopen(FileInfo,"wt");
	if(fp)
	{
		fprintf(fp,"%d",pDoc->m_REGION);
		fclose(fp);
	}
	((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("RGNtable");
}


void CAllocations_DrawView::OnSelchangeCOMBOregions() 
{
	int nIndex =((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.GetCurSel();
	if(nIndex == CB_ERR)
	return;

	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
	int i = 1 + nIndex;
	if(pDoc->m_REGION != i)
	{
		pDoc->m_REGION = i ;
		pDoc->GetData();

		m_Bandstr="";
		m_SRVstr="";
		m_SRVstrfot="";
		m_SRVstrfotPS="";

		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.ResetContent();
		if(i==4)
		{
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_Static_S5.SetWindowText(_Z("National : "));
			m_ListNUM = ArtS5_codeList(FALSE);
		}
		else
		{
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_Static_S5.SetWindowText(_Z("RR-Article 5 : "));
			m_ListNUM = ArtS5_codeList(TRUE);
		}
		for (long j=0;j<m_ListNUM;j++)
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.AddString(m_ArtS5_codeList[j]);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.SetCurSel(0);
		OnSelchangeCOMBOArt5() ;

		Invalidate();
	}
}

void CAllocations_DrawView::OnSelchangeCOMBOunit() 
{
	int nIndex =((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlUnit.GetCurSel();
	if(nIndex == CB_ERR)
	return;

	CString strFLO,strFHI;
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlEdit_Flo.GetWindowText(strFLO);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlEdit_Fhi.GetWindowText(strFHI);
	double m_EDIT_Flo = atof(strFLO);
	double m_EDIT_Fhi = atof(strFHI);

	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();

	UpdateData();
	int i = nIndex;
	if(pDoc->m_Fu != i)
	{
		pDoc->m_Fu = i ;
		if (i==0)
		{
			pDoc->m_Flo = m_EDIT_Flo/1000.0;
			pDoc->m_Fhi = m_EDIT_Fhi/1000.0;
			m_Fustr = _Z("Frequency (kHz)");

		}
		else if (i==1)
		{
			pDoc->m_Flo = m_EDIT_Flo;
			pDoc->m_Fhi = m_EDIT_Fhi;
			m_Fustr = _Z("Frequency (MHz)");

		}
		else if (i==2)
		{
			pDoc->m_Flo = m_EDIT_Flo*1000.0;
			pDoc->m_Fhi = m_EDIT_Fhi*1000.0;
			m_Fustr = _Z("Frequency (GHz)");

		}
		pDoc->GetData();

		m_Bandstr="";
		m_SRVstr="";
		m_SRVstrfot="";
		m_SRVstrfotPS="";

		Invalidate();
	}
	UpdateData(false);
}

void CAllocations_DrawView::OnSelchangeCOMBOscale() 
{
	int nIndex =((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlScale.GetCurSel();
	if(nIndex == CB_ERR)
	return;

	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();

	int i = nIndex;
	if(pDoc->m_Lin_Log != i)
	{
		pDoc->m_Lin_Log = i ;
		Invalidate();
	}
}

void CAllocations_DrawView::OnApply() 
{
	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
	UpdateData();

	int nIndex =((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlUnit.GetCurSel();
	if(nIndex == CB_ERR)
	return;

	CString strFLO,strFHI;
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlEdit_Flo.GetWindowText(strFLO);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlEdit_Fhi.GetWindowText(strFHI);
	double m_EDIT_Flo = atof(strFLO);
	double m_EDIT_Fhi = atof(strFHI);

	int i = nIndex;
	if (i==0)
	{
		pDoc->m_Flo = m_EDIT_Flo/1000.0;
		pDoc->m_Fhi = m_EDIT_Fhi/1000.0;
	}
	else if (i==1)
	{
		pDoc->m_Flo = m_EDIT_Flo;
		pDoc->m_Fhi = m_EDIT_Fhi;
	}
	else if (i==2)
	{
		pDoc->m_Flo = m_EDIT_Flo*1000.0;
		pDoc->m_Fhi = m_EDIT_Fhi*1000.0;
	}
	pDoc->GetData();

	m_Bandstr="";
	m_SRVstr="";
	m_SRVstrfot="";
	m_SRVstrfotPS="";

	Invalidate();

	UpdateData(false);
}


void CAllocations_DrawView::OnSelchangeCOMBOArt5() 
{
	int n =((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.GetCurSel();
	if(n == CB_ERR)
	return;
	n = n + 1;
	BOOL S5_N = (n==4) ? FALSE : TRUE;

	int nIndex =((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.GetCurSel();
	if(nIndex == CB_ERR)
	return;

	int i = nIndex;
	
	CString Docstr = Code2Doc(m_ArtS5_codeList[i],S5_N);

	UpdateData();
	m_EDIT_Doc.FmtLines(true);
	m_EDIT_Doc.SetWindowText(Docstr);
	UpdateData(false);
}

void CAllocations_DrawView::OnEditServicetable() 
{
	((CSMS4DCApp *)AfxGetApp())->OpenNewDocument("SRVtable");
}

void CAllocations_DrawView::OnUpdateEditPlan(CCmdUI* pCmdUI) 
{
	int level = ((CSMS4DCApp *)AfxGetApp())->m_UserLevel;
	pCmdUI->Enable(level!=6);		
}
void CAllocations_DrawView::OnUpdateEditServicetable(CCmdUI* pCmdUI) 
{
	int level = ((CSMS4DCApp *)AfxGetApp())->m_UserLevel;
	pCmdUI->Enable(level!=6);		
}

extern "C" int WINAPI Art5N(HWND hWndParent,CString DBSTR,CString Lang,int S5_N);	//Art5NDLL.lib
void CAllocations_DrawView::OnEditFootnote() 
{
	CString CDBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CString Lang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;

	int nIndex =((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlRegion.GetCurSel();
	if(nIndex == CB_ERR)
	return;

	int i = 1 + nIndex;
	int S5_N = (i==4) ? 1 : 0;

	Art5N(this->m_hWnd,CDBSTR,Lang,S5_N);		
}

void CAllocations_DrawView::OnUpdateEditFootnote(CCmdUI* pCmdUI) 
{
	int level = ((CSMS4DCApp *)AfxGetApp())->m_UserLevel;
	pCmdUI->Enable(level!=6);			
}

void CAllocations_DrawView::OnKillFocus(CWnd* pNewWnd) 
{
	CFormView::OnKillFocus(pNewWnd);
/*	
	m_ListNUM = ArtS5_codeList(TRUE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.ResetContent();
	for (long i=0;i<m_ListNUM;i++)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.AddString(m_ArtS5_codeList[i]);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.SetCurSel(0);
	OnSelchangeCOMBOArt5() ;

	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
	pDoc->GetData();
	Invalidate();
*/
	int I5 = ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.GetCurSel();
	CString sI5 = m_ArtS5_codeList[I5];

	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
	int r = pDoc->m_REGION;
	m_ListNUM = ArtS5_codeList(r<4);

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.ResetContent();
	for (long i=0;i<m_ListNUM;i++)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.AddString(m_ArtS5_codeList[i]);

	I5 = ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.FindStringExact(0, sI5);
	if(I5==-1)	I5 = 0;
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ctlS5.SetCurSel(I5);

	OnSelchangeCOMBOArt5() ;
	pDoc->GetData();
	Invalidate();	
}


CString CAllocations_DrawView::GetUnitFreq(CString strF)   //940312
{
	CString str = strF;
	int i = str.Find("(");
	str.Delete(0,i+1);
	str.Replace(")","");
	return str;
}


int CAllocations_DrawView::DP_LP(CDC* pDC,int nH_DP) //97/10/12
{
	if (pDC->IsPrinting())		return (int)(nH_DP*30.0/12.0);

	CSize z1(0, nH_DP);
	pDC->DPtoLP(&z1);
	return z1.cy;
}

void CAllocations_DrawView::initDP_LP(CDC * pDC) //97/10/12
{
//	CDC * pDC = GetDC();
//	pDC->SetMapMode(MM_LOMETRIC);

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
	m_fontH42  = DP_LP(pDC, 17); //42
	m_fontH48  = DP_LP(pDC, 19); //48
	m_fontH100 = DP_LP(pDC, 40); //100

	m_fontH25  = DP_LP(pDC, 10);  //25
	m_fontH70  = DP_LP(pDC, 28);  //70
	m_fontH75  = DP_LP(pDC, 30);  //75
	m_fontH125 = DP_LP(pDC, 50);  //125
	m_fontH175 = DP_LP(pDC, 70);  //175
	m_fontH245 = DP_LP(pDC, 98);  //245
	m_fontH250 = DP_LP(pDC, 100); //250
	m_fontH300 = DP_LP(pDC, 120); //300
	m_fontH600 = DP_LP(pDC, 240); //600
	m_fontH630 = DP_LP(pDC, 252); //630
	m_fontH165 = DP_LP(pDC, 66);  //165
	m_fontH420 = DP_LP(pDC, 168); //420
}



//////////////////////////////////////////////////////////////
///////////////////////// 98/05/06  Import Tables/////////////////////////////////////
//////////////////////////////////////////////////////////////
int CAllocations_DrawView::Exist_Table(CString sFile, CString table, CString strPWD) 
{
	CString sDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn;	sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s %s;",sDriver, sFile, strPWD);
	int m=0;
	TRY
	{
		CDatabase database;		database.Open(NULL,false,false,sDsn);
		CRecordset recset( &database );

		CString SqlString;		SqlString.Format("SELECT * FROM %s;" , table);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while( !recset.IsEOF() )
		{
			recset.MoveNext();
			m++;
		}
		database.Close();
	}
	CATCH(CDBException, e)
	{
		m=-1;
	}
	END_CATCH;
	return m;
}
void CAllocations_DrawView::Import_Table(CDatabase *sms4dc_DB0, CString mdbPathFile_Src, CString tbl_Src, CString strPWD, 
									 CString mdbPathFile_Plan, CString tbl_Plan) 
{
	TRY
	{
		if( Exist_Table(mdbPathFile_Src, tbl_Src, strPWD)>-1 )
		{
			CString str1;
			str1.Format(_Z("Do you want to delete the table :\n\n\t'' %s ''\n\nfrom SMS4DC database and replace with new one from the selected database :\n\n\t'' %s '' ?\t\t") , 
						 tbl_Src, mdbPathFile_Plan);

			int i = MessageBox(str1, _Z("!!!  Warning  !!!") , MB_YESNO|MB_ICONWARNING);
			if(i==IDYES)
			{
				str1.Format("drop table [%s]" ,  tbl_Src);	//Delete tbl_Src Table from mdbPathFile_Src database
				sms4dc_DB0->ExecuteSQL(str1 );

				str1.Format("SELECT * INTO [%s] FROM [%s].[%s]"  , tbl_Src ,  mdbPathFile_Plan, tbl_Plan);
				sms4dc_DB0->ExecuteSQL(str1 );
			}
		}
	}
	CATCH(CDBException, e)
	{
	}
	END_CATCH;
}
void CAllocations_DrawView::File_Import(CString sFilePath, int iTable) 
{
	CString mCDBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CString strPWD = mCDBSTR;
	strPWD.Delete(0,strPWD.Find("PWD")-1);

	CString pathfile, mdbPathFile_Src, mdbPathFile_Plan;

	CDatabase sms4dc_DB0;
	try
	{
		sms4dc_DB0.Open(mCDBSTR, false,false,_T("ODBC;"),false);

		pathfile = sms4dc_DB0.GetConnect();
	//	int i1 = pathfile.Find("DBQ",0)+4;		pathfile.Delete(0,i1);
	//	i1 = pathfile.Find("SMS-NEW.mdb",0);	pathfile.Delete(i1,pathfile.GetLength()-i1);
	//	mdbPathFile_Src  = pathfile + "SMS-NEW.mdb";

		int i1 = pathfile.Find("DBQ",0)+4;		pathfile.Delete(0,i1);
		i1 = pathfile.Find(";",0);				pathfile.Delete(i1,pathfile.GetLength()-i1);
		mdbPathFile_Src  = pathfile;

		mdbPathFile_Plan = sFilePath;
	}
	catch(CDBException* pE)
	{
		pE->ReportError();
		pE->Delete();
		return ;
	}

	if     (iTable==0)	Import_Table(&sms4dc_DB0, mdbPathFile_Src, "ITU_PLAN_R1", strPWD, mdbPathFile_Plan, "ITU_PLAN_R1");
	else if(iTable==1)	Import_Table(&sms4dc_DB0, mdbPathFile_Src, "ITU_PLAN_R2", strPWD, mdbPathFile_Plan, "ITU_PLAN_R2");
	else if(iTable==2)	Import_Table(&sms4dc_DB0, mdbPathFile_Src, "ITU_PLAN_R3", strPWD, mdbPathFile_Plan, "ITU_PLAN_R3");
	else if(iTable==3)	Import_Table(&sms4dc_DB0, mdbPathFile_Src, "ITU_PLAN_R4", strPWD, mdbPathFile_Plan, "National_PLAN");
	else if(iTable==4)	Import_Table(&sms4dc_DB0, mdbPathFile_Src, "SRVCode_Color_Name", strPWD, mdbPathFile_Plan, "SRVCode_Color_Name");
	else if(iTable==5)	Import_Table(&sms4dc_DB0, mdbPathFile_Src, "Art_S5table",  strPWD, mdbPathFile_Plan, "Art_S5table");
	else if(iTable==6)	Import_Table(&sms4dc_DB0, mdbPathFile_Src, "Art_S5Ntable", strPWD, mdbPathFile_Plan, "Art_S5Ntable");

	sms4dc_DB0.Close();
}
#include "FileDLG_ChangedType.h"

void CAllocations_DrawView::OnFileImport_(int iTable) 
{
	CFileDLG_ChangedType oFileDlg(TRUE, _T("mdb"), _T("SMS4DC_Plans"), 
						OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT|OFN_HIDEREADONLY , 
						_Z("MDB Files")+ " (*.mdb)|*.mdb|", this );
	oFileDlg.m_ShowCheckBox = FALSE;

	CString s = _Z("Open Plan file ...");	
	oFileDlg.m_ofn.lpstrTitle = s;
	if (((CSMS4DCApp *)AfxGetApp())->IsWin2000())		oFileDlg.m_ofn.lStructSize = 88;		//76
	if (oFileDlg.DoModal() == IDOK)
	{
		File_Import(oFileDlg.GetPathName() , iTable);
	}		
}

void CAllocations_DrawView::OnFileImportPlan() 
{
	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
	int iRegion = pDoc->m_REGION - 1;

	OnFileImport_(iRegion);	
}
void CAllocations_DrawView::OnFileImportServicetable() 
{
	OnFileImport_(4);	
}
void CAllocations_DrawView::OnFileImportFootnote() 
{
	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
	int iRegion = pDoc->m_REGION - 1;

	if(iRegion==3)	OnFileImport_(6);
	else			OnFileImport_(5);	
}
//////////////////////////////////////////////////////////////
///////////////////////// 98/05/06  Export Tables/////////////////////////////////////
//////////////////////////////////////////////////////////////
void CAllocations_DrawView::Export_Table(CDatabase *sms4dc_DB, CString mdbPathFile_Src, CString strPWD, CString mdbPathFile_Plan, CString tbl_Src, CString tbl_Plan) 
{
	TRY
	{
		CString str1;	int i = IDYES;
		if( Exist_Table(mdbPathFile_Plan, tbl_Plan, "")>-1 )
		{
			str1.Format(_Z("Do you want to delete the table :\n\n\t'' %s ''\n\nfrom the selected database :\n\n\t'' %s ''\t\t\n\nand replace with the new one from SMS4DC database ?\t") , tbl_Plan, mdbPathFile_Plan);

			i = MessageBox(str1, _Z("!!!  Warning  !!!") , MB_YESNO|MB_ICONWARNING);
			if(i==IDYES)
			{
				str1.Format("drop table [%s].[%s]" ,  mdbPathFile_Plan, tbl_Plan);	//Delete tbl_Plan Table from mdbPathFile_Plan database
				sms4dc_DB->ExecuteSQL(str1 );
			}

		}
		if(i==IDYES)
		{
			str1.Format("SELECT * INTO [%s].[%s] FROM [%s]" ,  mdbPathFile_Plan, tbl_Plan, tbl_Src);
			sms4dc_DB->ExecuteSQL(str1 );
		}

	}
	CATCH(CDBException, e)
	{
	}
	END_CATCH;
}

void CAllocations_DrawView::File_Export(CString sFilePath, int iTable) 
{
	AfxGetModuleState()->m_dwVersion = 0x0601;

	CString mCDBSTR = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CString strPWD = mCDBSTR;
	strPWD.Delete(0,strPWD.Find("PWD")-1);

	CString pathfile, mdbPathFile_Src, mdbPathFile_Plan;

	CDatabase sms4dc_DB0;
	try
	{
		sms4dc_DB0.Open(mCDBSTR, false,false,_T("ODBC;"),false);

		pathfile = sms4dc_DB0.GetConnect();
	//	int i1 = pathfile.Find("DBQ",0)+4;		pathfile.Delete(0,i1);
	//	i1 = pathfile.Find("SMS-NEW.mdb",0);	pathfile.Delete(i1,pathfile.GetLength()-i1);
	//	mdbPathFile_Src  = pathfile + "SMS-NEW.mdb";

		int i1 = pathfile.Find("DBQ",0)+4;		pathfile.Delete(0,i1);
		i1 = pathfile.Find(";",0);	pathfile.Delete(i1,pathfile.GetLength()-i1);
		mdbPathFile_Src  = pathfile;

		mdbPathFile_Plan = sFilePath;
	}
	catch(CDBException* pE)
	{
		pE->ReportError();
		pE->Delete();
		return ;
	}
	
	if     (iTable==0)	Export_Table(&sms4dc_DB0, mdbPathFile_Src, strPWD, mdbPathFile_Plan, "ITU_PLAN_R1","ITU_PLAN_R1"); 
	else if(iTable==1)	Export_Table(&sms4dc_DB0, mdbPathFile_Src, strPWD, mdbPathFile_Plan, "ITU_PLAN_R2","ITU_PLAN_R2"); 
	else if(iTable==2)	Export_Table(&sms4dc_DB0, mdbPathFile_Src, strPWD, mdbPathFile_Plan, "ITU_PLAN_R3","ITU_PLAN_R3"); 
	else if(iTable==3)	Export_Table(&sms4dc_DB0, mdbPathFile_Src, strPWD, mdbPathFile_Plan, "ITU_PLAN_R4","National_PLAN");
	else if(iTable==4)	Export_Table(&sms4dc_DB0, mdbPathFile_Src, strPWD, mdbPathFile_Plan, "SRVCode_Color_Name","SRVCode_Color_Name");
	else if(iTable==5)	Export_Table(&sms4dc_DB0, mdbPathFile_Src, strPWD, mdbPathFile_Plan, "Art_S5table","Art_S5table");
	else if(iTable==6)	Export_Table(&sms4dc_DB0, mdbPathFile_Src, strPWD, mdbPathFile_Plan, "Art_S5Ntable","Art_S5Ntable");
	
	sms4dc_DB0.Close();
}

void CAllocations_DrawView::OnFileExport_(int iTable) 
{
	CFileDLG_ChangedType oFileDlg(FALSE, _T("mdb"), _T("SMS4DC_Plans"), 
						OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_CREATEPROMPT|OFN_HIDEREADONLY , 
						_Z("MDB Files")+" (*.mdb)|*.mdb|", this );
	oFileDlg.m_ShowCheckBox = FALSE;

	CString s = _Z("Save Plan file as ...");	
	oFileDlg.m_ofn.lpstrTitle = s;
	if (((CSMS4DCApp *)AfxGetApp())->IsWin2000())		oFileDlg.m_ofn.lStructSize = 88;		//76
	if (oFileDlg.DoModal() == IDOK)
	{
		CString sFilePath = oFileDlg.GetPathName();
		
		CString sDriver = "MICROSOFT ACCESS DRIVER (*.mdb)";
		CString sCreate;  sCreate.Format("CREATE_DB=\"%s\" General\0", sFilePath);
		BOOL created = SQLConfigDataSource(NULL, ODBC_ADD_DSN, sDriver, sCreate);

		File_Export(sFilePath, iTable);
	}	
}

void CAllocations_DrawView::OnFileExportPlan() 
{
	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
	int iRegion = pDoc->m_REGION - 1;
	OnFileExport_(iRegion);		
}
void CAllocations_DrawView::OnFileExportServicetable() 
{
	OnFileExport_(4);	
}
void CAllocations_DrawView::OnFileExportFootnote() 
{
	CAllocations_DrawDoc* pDoc = (CAllocations_DrawDoc*)GetDocument();
	int iRegion = pDoc->m_REGION - 1;

	if(iRegion==3)	OnFileExport_(6);
	else			OnFileExport_(5);	
}

