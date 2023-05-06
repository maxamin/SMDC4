// BorderRep1DLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "BorderRep1DLG.h"
#include "HTML_Report.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBorderRep1DLG dialog


CBorderRep1DLG::CBorderRep1DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CBorderRep1DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBorderRep1DLG)
	m_rowsY = 0;
	m_editX = _T("");
	m_editY = _T("");
	m_mode = 0;
	//}}AFX_DATA_INIT
	m_title1 = _Z("Border Coordination Result");
	m_title2 = _Z("Wanted Station :");
	m_title3 = _Z("Border Calculations (Concerned Countries) :");
}


void CBorderRep1DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBorderRep1DLG)
	DDX_Text(pDX, IDC_EDIT_rowsY, m_rowsY);
	DDX_Text(pDX, IDC_EDIT_X, m_editX);
	DDX_Text(pDX, IDC_EDIT_Y, m_editY);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_LIST1);
	DDX_Control(pDX, IDC_MSFLEXGRID2, m_LIST2);
	DDX_Text(pDX, IDC_EDIT_mode, m_mode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBorderRep1DLG, CDialog)
	//{{AFX_MSG_MAP(CBorderRep1DLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBorderRep1DLG message handlers

BOOL CBorderRep1DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_title1);
	CStatic *x2;	x2 = (CStatic *)GetDlgItem(IDC_STATIC_t2);	x2->SetWindowText(m_title2);
	CStatic *x3;	x3 = (CStatic *)GetDlgItem(IDC_STATIC_t3);	x3->SetWindowText(m_title3);

	int j,nCOLS;
	CString ResultSTR;
	int n;

	if((m_mode==1)||(m_mode==2)||(m_mode==3))
	{
		nCOLS = 8;	
		m_LIST1.SetCols(nCOLS);
		m_LIST1.SetColWidth(0,400);
		m_LIST1.SetColWidth(1,900);
		m_LIST1.SetColWidth(2,1200);
		m_LIST1.SetColWidth(3,900);
		m_LIST1.SetColWidth(4,800);
		m_LIST1.SetColWidth(5,1900);
		m_LIST1.SetColWidth(6,1500);
		m_LIST1.SetColWidth(7,3000);

		m_LIST1.SetRowHeight(0,400);

		m_LIST1.SetRow(0);
		m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
		m_LIST1.SetCol(1);		m_LIST1.SetText("ID");
		m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("Name"));
		m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("St_Class"));
		m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Country"));
		m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Location"));
		m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("AgName"));
		m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Categories"));

		m_dataX = m_editX;
		m_dataY = m_editY;

		int m_nROWS=2;
		m_LIST1.SetRows(m_nROWS);

		for(int j=0;j<m_nROWS-1;j++)
		{
			m_LIST1.SetRow(j+1);
			m_LIST1.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST1.SetText(ResultSTR);

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editX.Find(',',0);
				ResultSTR = m_editX.Left(n);
				m_editX = m_editX.Mid(n+1);
				m_LIST1.SetCol(i+1);
				m_LIST1.SetText(ResultSTR);
			}
		}
		m_LIST1.SetCol(nCOLS-1);
		m_LIST1.SetText(m_editX);
	}
//////////////////////////////////////////
	if(m_mode==1)
	{
		nCOLS = 12; 
		m_LIST2.SetCols(nCOLS);
		m_LIST2.SetColWidth(0,400);
		m_LIST2.SetColWidth(1,1000);
		m_LIST2.SetColWidth(2,700);
		m_LIST2.SetColWidth(3,800);
		m_LIST2.SetColWidth(4,1500);
		m_LIST2.SetColWidth(5,1900);
		m_LIST2.SetColWidth(6,1000);
		m_LIST2.SetColWidth(7,1500);
		m_LIST2.SetColWidth(8,1900);
		m_LIST2.SetColWidth(9,1000);
		m_LIST2.SetColWidth(10,1300);
		m_LIST2.SetColWidth(11,900);

		m_LIST2.SetRowHeight(0,400);
		m_LIST2.SetRow(0);
		m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
		m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("Frq(MHz)"));
		m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("Tx/Rx"));
		m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Country"));
		m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("maxEb(dBuV/m)"));
		m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("DistB(km)"));
		m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("maxEc(dBuV/m)"));
		m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("DistC(km)"));
		m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("PIFS(dBuV/m)"));
		m_LIST2.SetCol(11);		m_LIST2.SetText(_T("CBR(km)"));

		m_LIST2.SetRows(m_rowsY);

		for(j=0;j<m_rowsY-1;j++)
		{
			m_LIST2.SetRow(j+1);
			m_LIST2.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST2.SetText(ResultSTR);

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editY.Find(',',0);
				ResultSTR = m_editY.Left(n);
				m_editY = m_editY.Mid(n+1);
				m_LIST2.SetCol(i+1);
				m_LIST2.SetText(ResultSTR);
			}
		}
		m_LIST2.SetCol(nCOLS-1);
		m_LIST2.SetText(m_editY);
		
		if(m_rowsY>1)
		for(j=0;j<m_rowsY-1;j++)
		{
			if((   atof(m_LIST2.GetTextMatrix(j+1,7)) > atof(m_LIST2.GetTextMatrix(j+1,10))  )&&( (m_LIST2.GetTextMatrix(j+1,7))!=_T("---") ))
			{
				m_LIST2.SetCol(7);
				m_LIST2.SetRow(j+1);
				m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
			if((   atof(m_LIST2.GetTextMatrix(j+1,4)) > atof(m_LIST2.GetTextMatrix(j+1,10))  )&&( (m_LIST2.GetTextMatrix(j+1,4))!=_T("---") ))
			{
				m_LIST2.SetCol(4);
				m_LIST2.SetRow(j+1);
				m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
		}
	}
	else if(m_mode==2)
	{
		nCOLS = 12; 
		m_LIST2.SetCols(nCOLS);
		m_LIST2.SetColWidth(0,400);
		m_LIST2.SetColWidth(1,1000);
		m_LIST2.SetColWidth(2,700);
		m_LIST2.SetColWidth(3,800);
		m_LIST2.SetColWidth(4,1500);
		m_LIST2.SetColWidth(5,1900);
		m_LIST2.SetColWidth(6,1000);
		m_LIST2.SetColWidth(7,1500);
		m_LIST2.SetColWidth(8,1900);
		m_LIST2.SetColWidth(9,1000);
		m_LIST2.SetColWidth(10,1300);
		m_LIST2.SetColWidth(11,900);

		m_LIST2.SetRowHeight(0,400);
		m_LIST2.SetRow(0);
		m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
		m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("Frq(MHz)"));
		m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("Tx/Rx"));
		m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Country"));
		m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("maxEb(dBuV/m)"));
		m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("DistB(km)"));
		m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("maxEx(dBuV/m)"));
		m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("DistX(km)"));
		m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("PIFS(dBuV/m)"));
		m_LIST2.SetCol(11);		m_LIST2.SetText(_T("XKM(km)"));

		m_LIST2.SetRows(m_rowsY);

		for(j=0;j<m_rowsY-1;j++)
		{
			m_LIST2.SetRow(j+1);
			m_LIST2.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST2.SetText(ResultSTR);

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editY.Find(',',0);
				ResultSTR = m_editY.Left(n);
				m_editY = m_editY.Mid(n+1);
				m_LIST2.SetCol(i+1);
				m_LIST2.SetText(ResultSTR);
			}
		}
		m_LIST2.SetCol(nCOLS-1);
		m_LIST2.SetText(m_editY);

		if(m_rowsY>1)
		for(j=0;j<m_rowsY-1;j++)
		{
			if((   atof(m_LIST2.GetTextMatrix(j+1,7)) > atof(m_LIST2.GetTextMatrix(j+1,10))  )&&( (m_LIST2.GetTextMatrix(j+1,7))!=_T("---") ))
			{
				m_LIST2.SetCol(7);
				m_LIST2.SetRow(j+1);
				m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
		}

	}
	else if(m_mode==3)
	{
		nCOLS = 7; 
		m_LIST2.SetCols(nCOLS);
		m_LIST2.SetColWidth(0,400);
		m_LIST2.SetColWidth(1,1000);
		m_LIST2.SetColWidth(2,700);
		m_LIST2.SetColWidth(3,800);
		m_LIST2.SetColWidth(4,1500);
		m_LIST2.SetColWidth(5,1900);
		m_LIST2.SetColWidth(6,1500);

		m_LIST2.SetRowHeight(0,400);
		m_LIST2.SetRow(0);
		m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
		m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("Frq(MHz)"));
		m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("Tx/Rx"));
		m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Country"));
		m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("minDistB(km)"));
		m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Coord Dist(km)"));

		m_LIST2.SetRows(m_rowsY);

		for(j=0;j<m_rowsY-1;j++)
		{
			m_LIST2.SetRow(j+1);
			m_LIST2.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST2.SetText(ResultSTR);

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editY.Find(',',0);
				ResultSTR = m_editY.Left(n);
				m_editY = m_editY.Mid(n+1);
				m_LIST2.SetCol(i+1);
				m_LIST2.SetText(ResultSTR);
			}
		}
		m_LIST2.SetCol(nCOLS-1);
		m_LIST2.SetText(m_editY);
		
		if(m_rowsY>1)
		for(j=0;j<m_rowsY-1;j++)
		{
			if((   atof(m_LIST2.GetTextMatrix(j+1,4)) < atof(m_LIST2.GetTextMatrix(j+1,6))  )&&((m_LIST2.GetTextMatrix(j+1,4).Left(3))!=_T("---")))
			{
				m_LIST2.SetCol(4);
				m_LIST2.SetRow(j+1);
				m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
		}
	}
	else if(m_mode==4)
	{
		nCOLS = 7;	
		m_LIST1.SetCols(nCOLS);
		m_LIST1.SetColWidth(0,400);
		m_LIST1.SetColWidth(1,1500);
		m_LIST1.SetColWidth(2,1200);
		m_LIST1.SetColWidth(3,900);
		m_LIST1.SetColWidth(4,1900);
		m_LIST1.SetColWidth(5,1000);
		m_LIST1.SetColWidth(6,900);

		m_LIST1.SetRowHeight(0,400);

		m_LIST1.SetRow(0);
		m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
		m_LIST1.SetCol(1);		m_LIST1.SetText(_T("ID"));
		m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("Name"));
		m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("Country"));
		m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Location"));
		m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Frq(MHz)"));
		m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("St_Class"));

		m_dataX = m_editX;
		m_dataY = m_editY;

		int m_nROWS=2;
		m_LIST1.SetRows(m_nROWS);
		int n;
		CString ResultSTR;

		for(int j=0;j<m_nROWS-1;j++)
		{
			m_LIST1.SetRow(j+1);
			m_LIST1.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST1.SetText(ResultSTR);

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editX.Find(',',0);
				ResultSTR = m_editX.Left(n);
				m_editX = m_editX.Mid(n+1);
				m_LIST1.SetCol(i+1);
				m_LIST1.SetText(ResultSTR);
			}
		}
		m_LIST1.SetCol(nCOLS-1);
		m_LIST1.SetText(m_editX);

		nCOLS = 10; 
		m_LIST2.SetCols(nCOLS);
		m_LIST2.SetColWidth(0,400);
		m_LIST2.SetColWidth(1,1000);
		m_LIST2.SetColWidth(2,1200);
		m_LIST2.SetColWidth(3,800);
		m_LIST2.SetColWidth(4,1900);
		m_LIST2.SetColWidth(5,800);
		m_LIST2.SetColWidth(6,1000);
		m_LIST2.SetColWidth(7,900);
		m_LIST2.SetColWidth(8,1000);
		m_LIST2.SetColWidth(9,1400);

		m_LIST2.SetRowHeight(0,400);
		m_LIST2.SetRow(0);
		m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
		m_LIST2.SetCol(1);		m_LIST2.SetText(_T("ID"));
		m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("Name"));
		m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Country"));
		m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Dist(km)"));
		m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Frq(MHz)"));
		m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("St_Class"));
		m_LIST2.SetCol(8);		m_LIST2.SetText(_T("E(dBuV/m)"));
		m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("Elimit(dBuV/m)"));

		m_LIST2.SetRows(m_rowsY);

		for(j=0;j<m_rowsY-1;j++)
		{
			m_LIST2.SetRow(j+1);
			m_LIST2.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST2.SetText(ResultSTR);

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editY.Find(',',0);
				ResultSTR = m_editY.Left(n);
				m_editY = m_editY.Mid(n+1);
				m_LIST2.SetCol(i+1);
				m_LIST2.SetText(ResultSTR);
			}
		}
		m_LIST2.SetCol(nCOLS-1);
		m_LIST2.SetText(m_editY);

		if(m_rowsY>1)
		for(j=0;j<m_rowsY-1;j++)
		{
			if(   atof(m_LIST2.GetTextMatrix(j+1,8)) > atof(m_LIST2.GetTextMatrix(j+1,9))  )
			{
				m_LIST2.SetCol(8);
				m_LIST2.SetRow(j+1);
				m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
		}

	}
	else if(m_mode==5)
	{
		nCOLS = 6;	
		m_LIST1.SetCols(nCOLS);
		m_LIST1.SetColWidth(0,400);
		m_LIST1.SetColWidth(1,1500);
		m_LIST1.SetColWidth(2,1200);
		m_LIST1.SetColWidth(3,900);
		m_LIST1.SetColWidth(4,1900);
		m_LIST1.SetColWidth(5,1000);

		m_LIST1.SetRowHeight(0,400);

		m_LIST1.SetRow(0);
		m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
		m_LIST1.SetCol(1);		m_LIST1.SetText(_T("ID"));
		m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("Name"));
		m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("Country"));
		m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Location"));
		m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Frq(MHz)"));

		m_dataX = m_editX;
		m_dataY = m_editY;

		int m_nROWS=2;
		m_LIST1.SetRows(m_nROWS);
		int n;
		CString ResultSTR;

		for(int j=0;j<m_nROWS-1;j++)
		{
			m_LIST1.SetRow(j+1);
			m_LIST1.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST1.SetText(ResultSTR);

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editX.Find(',',0);
				ResultSTR = m_editX.Left(n);
				m_editX = m_editX.Mid(n+1);
				m_LIST1.SetCol(i+1);
				m_LIST1.SetText(ResultSTR);
			}
		}
		m_LIST1.SetCol(nCOLS-1);
		m_LIST1.SetText(m_editX);

		nCOLS = 11; 
		m_LIST2.SetCols(nCOLS);
		m_LIST2.SetColWidth(0,400);
		m_LIST2.SetColWidth(1,1000);
		m_LIST2.SetColWidth(2,1200);
		m_LIST2.SetColWidth(3,800);
		m_LIST2.SetColWidth(4,1900);
		m_LIST2.SetColWidth(5,800);
		m_LIST2.SetColWidth(6,1000);
		m_LIST2.SetColWidth(7,900);
		m_LIST2.SetColWidth(8,1000);
		m_LIST2.SetColWidth(9,1200);
		m_LIST2.SetColWidth(10,4200);

		m_LIST2.SetRowHeight(0,400);
		m_LIST2.SetRow(0);
		m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
		m_LIST2.SetCol(1);		m_LIST2.SetText(_T("ID"));
		m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("Name"));
		m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Country"));
		m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Dist(km)"));
		m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Frq(MHz)"));
		m_LIST2.SetCol(7);		m_LIST2.SetText(_T("I(dBW)"));
		m_LIST2.SetCol(8);		m_LIST2.SetText(_T("TD(dB)"));
		m_LIST2.SetCol(9);		m_LIST2.SetText(m_pTD);
		m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Path Type"));

		m_LIST2.SetRows(m_rowsY);

		for(j=0;j<m_rowsY-1;j++)
		{
			m_LIST2.SetRow(j+1);
			m_LIST2.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST2.SetText(ResultSTR);

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editY.Find(',',0);
				ResultSTR = m_editY.Left(n);
				m_editY = m_editY.Mid(n+1);
				m_LIST2.SetCol(i+1);
				m_LIST2.SetText(ResultSTR);
			}
		}
		m_LIST2.SetCol(nCOLS-1);
		m_LIST2.SetText(m_editY);
		
		m_LIST2.SetCol(9);
		for(j=0;j<m_rowsY-1;j++)
		{
			m_LIST2.SetRow(j+1);
			if((atof(m_LIST2.GetText()))>0)
				m_LIST2.SetCellBackColor(RGB(255,150,150));
		}

	}
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CBorderRep1DLG::OnOK() 
{
	if(m_mode==1)
	{
		CFileDialog oFileDlg(FALSE, 
							_T("html"), _T("OutPutFile"), 
							OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
							_T("HTML Files (*.html)|*.html|"), this );
		CString str = _T("Save HTML file as...");
		oFileDlg.m_ofn.lpstrTitle = str;
		if (oFileDlg.DoModal() == IDOK)
		{
			CString sFile, ResultSTR, sCELL[12], m_dataX1 = m_dataX+",", m_dataY1 = m_dataY+",";
			int i, j, n , iRow = 2, iCol = 8;
			sFile = oFileDlg.GetFileName();
			CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
			HtmlReport.InsertTableHeader(iCol, _Z("No."), _Z("ID"), _Z("Name"), _Z("St_Class"), _Z("Country"), _Z("Location"),_Z("AgName"),_Z("Categories"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataX1.Find(',',0);
					ResultSTR = m_dataX1.Left(n);
					m_dataX1 = m_dataX1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7]);
				iRow--;
			}
			HtmlReport.WriteHTMLFile(sFile);

			iRow = m_rowsY, iCol = 12;
			CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
			HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("Frq(MHz)"), _Z("Tx/Rx"), _Z("Country"), _Z("maxEb(dBuV/m)"), _Z("Location"), _Z("DistB(km)"), _Z("maxEc(dBuV/m)"), _Z("Location"), _Z("DistC(km)"), _Z("PIFS(dBuV/m)"),_T("CBR(km)"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataY1.Find(',',0);
					ResultSTR = m_dataY1.Left(n);
					m_dataY1 = m_dataY1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11]);
				iRow--;
			}

			CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
			HtmlReport1.WriteHTMLFile(FileInfo);
			int m_num = HtmlReport1.m_num;

			FILE *stream, *stream1;
			char *list; list = new char[m_num];
			if((stream = fopen(FileInfo, "rt")) != NULL)
			{
				fread( list, sizeof( char ), m_num, stream );
				fclose( stream );
			}
			if((stream1 = fopen(sFile, "at")) != NULL)
			{
				fwrite(list, sizeof(char), m_num, stream1);
				fclose( stream1 );
			}
			delete [] list;

			ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
		}	
	}
	else if(m_mode==2)
	{
		CFileDialog oFileDlg(FALSE, 
							_T("html"), _T("OutPutFile"), 
							OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
							_Z("HTML Files")+" (*.html)|*.html|", this );
		CString str = _T("Save HTML file as...");
		oFileDlg.m_ofn.lpstrTitle = str;
		if (oFileDlg.DoModal() == IDOK)
		{
			CString sFile, ResultSTR, sCELL[12], m_dataX1 = m_dataX+",", m_dataY1 = m_dataY+",";
			int i, j, n , iRow = 2, iCol = 8;
			sFile = oFileDlg.GetFileName();
			CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
			HtmlReport.InsertTableHeader(iCol, _Z("No."), _T("ID"), _Z("Name"), _Z("St_Class"), _Z("Country"), _Z("Location"),_Z("AgName"),_Z("Categories"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataX1.Find(',',0);
					ResultSTR = m_dataX1.Left(n);
					m_dataX1 = m_dataX1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7]);
				iRow--;
			}
			HtmlReport.WriteHTMLFile(sFile);

			iRow = m_rowsY, iCol = 12;
			CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
			HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("Frq(MHz)"), _Z("Tx/Rx"), _Z("Country"), _Z("maxEb(dBuV/m)"), _Z("Location"), _Z("DistB(km)"), _Z("maxEx(dBuV/m)"), _Z("Location"), _Z("DistX(km)"), _Z("PIFS(dBuV/m)"),_T("XKM(km)"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataY1.Find(',',0);
					ResultSTR = m_dataY1.Left(n);
					m_dataY1 = m_dataY1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11]);
				iRow--;
			}

			CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
			HtmlReport1.WriteHTMLFile(FileInfo);
			int m_num = HtmlReport1.m_num;

			FILE *stream, *stream1;
			char *list; list = new char[m_num];
			if((stream = fopen(FileInfo, "rt")) != NULL)
			{
				fread( list, sizeof( char ), m_num, stream );
				fclose( stream );
			}
			if((stream1 = fopen(sFile, "at")) != NULL)
			{
				fwrite(list, sizeof(char), m_num, stream1);
				fclose( stream1 );
			}
			delete [] list;

			ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
		}	
	}
	else if(m_mode==3)
	{
		CFileDialog oFileDlg(FALSE, 
							_T("html"), _T("OutPutFile"), 
							OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
							_Z("HTML Files")+" (*.html)|*.html|", this );
		CString str = _T("Save HTML file as...");
		oFileDlg.m_ofn.lpstrTitle = str;
		if (oFileDlg.DoModal() == IDOK)
		{
			CString sFile, ResultSTR, sCELL[8], m_dataX1 = m_dataX+",", m_dataY1 = m_dataY+",";
			int i, j, n , iRow = 2, iCol = 8;
			sFile = oFileDlg.GetFileName();
			CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
			HtmlReport.InsertTableHeader(iCol, _Z("No."), _T("ID"), _Z("Name"), _Z("St_Class"), _Z("Country"), _Z("Location"),_Z("AgName"),_Z("Categories"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataX1.Find(',',0);
					ResultSTR = m_dataX1.Left(n);
					m_dataX1 = m_dataX1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7]);
				iRow--;
			}
			HtmlReport.WriteHTMLFile(sFile);

			iRow = m_rowsY, iCol = 7;
			CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
			HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("Frq(MHz)"), _Z("Tx/Rx"), _Z("Country"), _Z("minDistB(km)"), _Z("Location"), _Z("Coord Dist(km)"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataY1.Find(',',0);
					ResultSTR = m_dataY1.Left(n);
					m_dataY1 = m_dataY1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6]);
				iRow--;
			}

			CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
			HtmlReport1.WriteHTMLFile(FileInfo);
			int m_num = HtmlReport1.m_num;

			FILE *stream, *stream1;
			char *list; list = new char[m_num];
			if((stream = fopen(FileInfo, "rt")) != NULL)
			{
				fread( list, sizeof( char ), m_num, stream );
				fclose( stream );
			}
			if((stream1 = fopen(sFile, "at")) != NULL)
			{
				fwrite(list, sizeof(char), m_num, stream1);
				fclose( stream1 );
			}
			delete [] list;

			ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
		}	
	}
	else if(m_mode==4)
	{
		CFileDialog oFileDlg(FALSE, 
							_T("html"), _T("OutPutFile"), 
							OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
							_Z("HTML Files")+" (*.html)|*.html|", this );
		CString str = _T("Save HTML file as...");
		oFileDlg.m_ofn.lpstrTitle = str;
		if (oFileDlg.DoModal() == IDOK)
		{
			CString sFile, ResultSTR, sCELL[10], m_dataX1 = m_dataX+",", m_dataY1 = m_dataY+",";
			int i, j, n , iRow = 2, iCol = 7;
			sFile = oFileDlg.GetFileName();
			CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
			HtmlReport.InsertTableHeader(iCol, _Z("No."), _T("ID"), _Z("Name"), _Z("Country"), _Z("Location"),_Z("Frq(MHz)"),_Z("St_Class"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataX1.Find(',',0);
					ResultSTR = m_dataX1.Left(n);
					m_dataX1 = m_dataX1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6]);
				iRow--;
			}
			HtmlReport.WriteHTMLFile(sFile);

			iRow = m_rowsY, iCol = 10;
			CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);

			HtmlReport1.InsertTableHeader(iCol, _Z("No."), _T("ID"), _Z("Name"), _Z("Country"), _Z("Location"), _Z("Dist(km)"),_Z("Frq(MHz)"),_Z("St_Class"),"E(dBuV/m)",_Z("Elimit(dBuV/m)"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataY1.Find(',',0);
					ResultSTR = m_dataY1.Left(n);
					m_dataY1 = m_dataY1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9]);
				iRow--;
			}

			CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
			HtmlReport1.WriteHTMLFile(FileInfo);
			int m_num = HtmlReport1.m_num;

			FILE *stream, *stream1;
			char *list; list = new char[m_num];
			if((stream = fopen(FileInfo, "rt")) != NULL)
			{
				fread( list, sizeof( char ), m_num, stream );
				fclose( stream );
			}
			if((stream1 = fopen(sFile, "at")) != NULL)
			{
				fwrite(list, sizeof(char), m_num, stream1);
				fclose( stream1 );
			}
			delete [] list;

			ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
		}	
	}
	else if(m_mode==5)
	{
		CFileDialog oFileDlg(FALSE, 
							_T("html"), _T("OutPutFile"), 
							OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
							_Z("HTML Files")+" (*.html)|*.html|", this );
		CString str = _T("Save HTML file as...");
		oFileDlg.m_ofn.lpstrTitle = str;
		if (oFileDlg.DoModal() == IDOK)
		{
			CString sFile, ResultSTR, sCELL[11], m_dataX1 = m_dataX+",", m_dataY1 = m_dataY+",";
			int i, j, n , iRow = 2, iCol = 6;
			sFile = oFileDlg.GetFileName();
			CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
			HtmlReport.InsertTableHeader(iCol, _Z("No."), _T("ID"), _Z("Name"), _Z("Country"), _Z("Location"),_Z("Frq(MHz)"));
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataX1.Find(',',0);
					ResultSTR = m_dataX1.Left(n);
					m_dataX1 = m_dataX1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5]);
				iRow--;
			}
			HtmlReport.WriteHTMLFile(sFile);

			iRow = m_rowsY, iCol = 11;
			CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);

			HtmlReport1.InsertTableHeader(iCol, _Z("No."), _T("ID"), _Z("Name"), _Z("Country"), _Z("Location"), _Z("Dist(km)"),_Z("Frq(MHz)"),"I(dBW)","TD(dB)",m_pTD,"Path Type");
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				for( i=0;i<iCol-1;i++)
				{
					n = m_dataY1.Find(',',0);
					ResultSTR = m_dataY1.Left(n);
					m_dataY1 = m_dataY1.Mid(n+1);
					sCELL[i+1] = ResultSTR;
				}
				HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10]);
				iRow--;
			}

			CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
			HtmlReport1.WriteHTMLFile(FileInfo);
			int m_num = HtmlReport1.m_num;

			FILE *stream, *stream1;
			char *list; list = new char[m_num];
			if((stream = fopen(FileInfo, "rt")) != NULL)
			{
				fread( list, sizeof( char ), m_num, stream );
				fclose( stream );
			}
			if((stream1 = fopen(sFile, "at")) != NULL)
			{
				fwrite(list, sizeof(char), m_num, stream1);
				fclose( stream1 );
			}
			delete [] list;

			ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
		}	
	}

//	CDialog::OnOK();
}
