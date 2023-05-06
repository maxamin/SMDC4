// GE89_EuDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "GE89_EuDLG.h"

#include "HTML_Report.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGE89_EuDLG dialog


CGE89_EuDLG::CGE89_EuDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CGE89_EuDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGE89_EuDLG)
	m_rowsY = 0;
	m_editY = _T("");
	m_editX = _T("");
	//}}AFX_DATA_INIT
	m_title1 = _Z("GE89 : Interference from selected stations to wanted station");
	m_title2 = _Z("Interference from : ");

}


void CGE89_EuDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGE89_EuDLG)
	DDX_Text(pDX, IDC_EDIT_rowsY, m_rowsY);
	DDX_Text(pDX, IDC_EDIT_Y, m_editY);
	DDX_Text(pDX, IDC_EDIT_X, m_editX);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_LIST1);
	DDX_Control(pDX, IDC_MSFLEXGRID2, m_LIST2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGE89_EuDLG, CDialog)
	//{{AFX_MSG_MAP(CGE89_EuDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGE89_EuDLG message handlers

BOOL CGE89_EuDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(m_title1);
	CStatic *xxx;	xxx = (CStatic *)GetDlgItem(IDC_STATIC_t2);
	xxx->SetWindowText(m_title2);

	int nCOLS = 7;	
	m_LIST1.SetCols(nCOLS);
	m_LIST1.SetColWidth(0,400);
	m_LIST1.SetColWidth(1,1200);
	m_LIST1.SetColWidth(2,2000);
	m_LIST1.SetColWidth(3,800);
	m_LIST1.SetColWidth(4,1500);
	m_LIST1.SetColWidth(5,1100);
	m_LIST1.SetColWidth(6,1200);

	m_LIST1.SetRowHeight(0,400);

	m_LIST1.SetRow(0);
	m_LIST1.SetCol(0);	m_LIST1.SetText(_Z("No."));
	m_LIST1.SetCol(1);	m_LIST1.SetText(_Z("AssignID"));
	m_LIST1.SetCol(2);	m_LIST1.SetText(_Z("Site Name"));
	m_LIST1.SetCol(3);	m_LIST1.SetText(_Z("Country"));
	m_LIST1.SetCol(4);	m_LIST1.SetText(_Z("Vision Frq(MHz)"));
	m_LIST1.SetCol(5);	m_LIST1.SetText(_Z("Polarization"));
	m_LIST1.SetCol(6);	m_LIST1.SetText(_T("Eu(dBuV/m)"));

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

//////////////////////////////////////////

	nCOLS = nCOLS + 2; 
	m_LIST2.SetCols(nCOLS);
	m_LIST2.SetColWidth(0,400);
	m_LIST2.SetColWidth(1,1200);
	m_LIST2.SetColWidth(2,2000);
	m_LIST2.SetColWidth(3,800);
	m_LIST2.SetColWidth(4,1500);
	m_LIST2.SetColWidth(5,800);
	m_LIST2.SetColWidth(6,1100);
	m_LIST2.SetColWidth(7,1200);
	m_LIST2.SetColWidth(8,1400);

	m_LIST2.SetRowHeight(0,400);

	m_LIST2.SetRow(0);
	m_LIST2.SetCol(0);	m_LIST2.SetText(_Z("No."));
	m_LIST2.SetCol(1);	m_LIST2.SetText(_Z("AssignID"));
	m_LIST2.SetCol(2);	m_LIST2.SetText(_Z("Site Name"));
	m_LIST2.SetCol(3);	m_LIST2.SetText(_Z("Country"));
	m_LIST2.SetCol(4);	m_LIST2.SetText(_Z("Vision Frq(MHz)"));
	m_LIST2.SetCol(5);	m_LIST2.SetText(_T("PR(dB)"));
	m_LIST2.SetCol(6);	m_LIST2.SetText(_Z("Polarization"));
	m_LIST2.SetCol(7);	m_LIST2.SetText(_T("Esi(dBuV/m)"));
	m_LIST2.SetCol(8);	m_LIST2.SetText(_Z("Elimit(dBuV/m)"));

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
		if(   atof(m_LIST2.GetTextMatrix(j+1,7))  >  atof(m_LIST2.GetTextMatrix(j+1,8))  )
		{
			m_LIST2.SetCol(7);
			m_LIST2.SetRow(j+1);
			m_LIST2.SetCellBackColor(RGB(255,150,150));
		}
	}
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CGE89_EuDLG::OnOK() 
{
	CFileDialog oFileDlg(FALSE, 
						_T("html"), _T("OutPutFile"), 
						OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
						_Z("HTML Files")+" (*.html)|*.html|", this );
	CString str = _T("Save HTML file as...");
	oFileDlg.m_ofn.lpstrTitle = str;
	if (oFileDlg.DoModal() == IDOK)
	{
		CString sFile, ResultSTR, sCELL[9], m_dataX1 = m_dataX+",", m_dataY1 = m_dataY+",";
		int i, j, n , iRow = 2, iCol = 7;
		sFile = oFileDlg.GetFileName();
		CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",_Z("Wanted Station :"),m_title1);
		HtmlReport.InsertTableHeader(iCol, _Z("No."), _Z("AssignID"), _Z("Site Name"), _Z("Country"), _Z("Vision Frq(MHz)"), _Z("Polarization"), _T("Eu(dBuV/m)"));
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


		iRow = m_rowsY, iCol = 9;
		CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title2);
		HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("AssignID"), _Z("Site Name"), _Z("Country"), _Z("Vision Frq(MHz)"), _T("PR(dB)"), _Z("Polarization"), _T("Esi(dBuV/m)"), _Z("Elimit(dBuV/m)"));
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
			HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8]);
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
//	CDialog::OnOK();
}
