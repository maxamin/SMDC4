// GE84BC2BCDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "GE84BC2BCDLG.h"

#include "HTML_Report.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGE84BC2BCDLG dialog


CGE84BC2BCDLG::CGE84BC2BCDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CGE84BC2BCDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGE84BC2BCDLG)
	m_nROWS = 0;
	m_data =_T("");
	m_title = _Z("GE84 BC to BC - Coordination Distance");
	m_DorE = _Z("Cord_Dist(km)");
	//}}AFX_DATA_INIT
}


void CGE84BC2BCDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGE84BC2BCDLG)
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_LIST1);
	DDX_Text(pDX, IDC_EDIT_rows, m_nROWS);
	DDX_Text(pDX, IDC_EDIT_data, m_data);
	DDX_Text(pDX, IDC_EDIT_title, m_title);
	DDX_Text(pDX, IDC_EDIT_DorE, m_DorE);
	DDX_Control(pDX, IDC_MSFLEXGRID2, m_LIST2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGE84BC2BCDLG, CDialog)
	//{{AFX_MSG_MAP(CGE84BC2BCDLG)
	ON_BN_CLICKED(IDOK, OnReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGE84BC2BCDLG message handlers

BOOL CGE84BC2BCDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(m_title);

	m_LIST2.SetCols(5);
	m_LIST2.SetColWidth(0,400);
	m_LIST2.SetColWidth(1,1300);
	m_LIST2.SetColWidth(2,1300);
	m_LIST2.SetColWidth(3,2000);
	m_LIST2.SetColWidth(4,1300);

	m_LIST2.SetRow(0);
	m_LIST2.SetCol(0);	m_LIST2.SetText(" ");
	m_LIST2.SetCol(1);	m_LIST2.SetText(_Z("AssignID"));
	m_LIST2.SetCol(2);	m_LIST2.SetText(_Z("Country"));
	m_LIST2.SetCol(3);	m_LIST2.SetText(_Z("Coordinates"));
	m_LIST2.SetCol(4);	m_LIST2.SetText(_Z("Name"));

	m_LIST2.SetRowHeight(0,400);
	m_LIST2.SetColAlignment(0,4);
	m_LIST2.SetColAlignment(1,4);
	m_LIST2.SetColAlignment(2,4);
	m_LIST2.SetColAlignment(3,4);
	m_LIST2.SetColAlignment(4,4);

	m_data1 = m_data;
	int n,i;

	CString ResultSTR;

	m_LIST2.SetRow(1);
	m_LIST2.SetCol(0);

	for( i=0;i<5-1;i++)
	{
		n = m_data.Find(',',0);
		ResultSTR = m_data.Left(n);
		m_data = m_data.Mid(n+1);
		m_LIST2.SetCol(i+1);	m_LIST2.SetText(ResultSTR);
	}
	for( i=4;i<10-1;i++)
	{
		n = m_data.Find(',',0);
		ResultSTR = m_data.Left(n);
		m_data = m_data.Mid(n+1);
	}

	int nCOLS = 10;	
	m_LIST1.SetCols(nCOLS);
	m_LIST1.SetColWidth(0,400);
	m_LIST1.SetColWidth(1,1100);
	m_LIST1.SetColWidth(2,800);
	m_LIST1.SetColWidth(3,2000);
	m_LIST1.SetColWidth(4,1300);
	m_LIST1.SetColWidth(5,1300);
	m_LIST1.SetColWidth(6,1300);
	m_LIST1.SetColWidth(7,900);
	m_LIST1.SetColWidth(8,1100);
	m_LIST1.SetColWidth(9,700);

	m_LIST1.SetRowHeight(0,400);
//	m_LIST1.SetRowHeight(1,400);

	m_LIST1.SetRow(0);
	m_LIST1.SetCol(0);	m_LIST1.SetText(_Z("No."));
	m_LIST1.SetCol(1);	m_LIST1.SetText(_Z("P_Affected"));
	m_LIST1.SetCol(2);	m_LIST1.SetText(_Z("Country"));
	m_LIST1.SetCol(3);	m_LIST1.SetText(_Z("Coordinates"));
	m_LIST1.SetCol(4);	m_LIST1.SetText(_Z("Azimuth(Deg)"));
	m_LIST1.SetCol(5);	m_LIST1.SetText(_Z("Distance(km)"));
	m_LIST1.SetCol(6);	m_LIST1.SetText(m_DorE);
	m_LIST1.SetCol(7);	m_LIST1.SetText(_Z("Heff(m)"));

	m_LIST1.SetCol(8);
	if(m_title.Left(1)=="G")		m_LIST1.SetText(_Z("Band(MHz)"));
	else							m_LIST1.SetText(_Z("Band"));
	if(m_title.Left(4)=="GE89")		m_LIST1.SetText(_Z("Frequency(MHz)"));

	m_LIST1.SetCol(9);	m_LIST1.SetText(_Z("Region"));

	m_LIST1.SetColAlignment(1,4);
	m_LIST1.SetColAlignment(2,4);
	m_LIST1.SetColAlignment(3,4);

//	m_data1 = m_data;

	m_LIST1.SetRows(m_nROWS);
//	int n;
//	CString ResultSTR;

	for(int j=0;j<m_nROWS-1;j++)
	{
		m_LIST1.SetRow(j+1);
		m_LIST1.SetCol(0);
		ResultSTR.Format("%d",j+1);
		m_LIST1.SetText(ResultSTR);

		for( i=0;i<nCOLS-1;i++)
		{
			n = m_data.Find(',',0);
			ResultSTR = m_data.Left(n);
			m_data = m_data.Mid(n+1);
			m_LIST1.SetCol(i+1);		m_LIST1.SetText(ResultSTR);
		}
	}
	if(m_nROWS>1)
	{
		m_LIST1.SetCol(nCOLS-1);
		m_LIST1.SetText(m_data);
	}

//	m_LIST1.SetRow(1);
//	for( i=0;i<nCOLS;i++)
//	{
//		m_LIST1.SetCol(i);
//		m_LIST1.SetCellBackColor(RGB(255,0,0));
//	}
//	m_LIST1.SetRow(1);
//	m_LIST1.SetCol(0);
//	m_LIST1.SetText(" ");

	m_LIST1.SetColAlignment(4,7);

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CGE84BC2BCDLG::OnReport() 
{
	CFileDialog oFileDlg(FALSE, 
						_T("html"), _Z("OutPutFile"), 
						OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
						_Z("HTML Files")+" (*.html)|*.html|", this );

	CString str = _Z("Save HTML file as...");
	
	oFileDlg.m_ofn.lpstrTitle = str;
//	oFileDlg.m_ofn.lpstrTitle = _Z("Save HTML file as...");
	if (oFileDlg.DoModal() == IDOK)
	{
		CString sFile, ResultSTR, sCELL[10], m_data2 = m_data1+",";
		int i, j, n , iRow = 2, iCol = 4;

		sFile = oFileDlg.GetFileName();
		
		CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",_Z("Wanted Station :"),"  ");
		HtmlReport.InsertTableHeader(iCol, _Z("AssignID"), _Z("Country"), _Z("Coordinates"), _Z("Name"));
		for( j = 1; iRow>1; j++)
		{
	//		ResultSTR.Format("%d",j);
	//		sCELL[0] = ResultSTR;
			for( i=0;i<iCol-0;i++)
			{
				n = m_data2.Find(',',0);
				ResultSTR = m_data2.Left(n);
				m_data2 = m_data2.Mid(n+1);
				sCELL[i+0] = ResultSTR;
			}
			HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3]);
			iRow--;

			for( i=4;i<10-1;i++)
			{
				n = m_data2.Find(',',0);
				ResultSTR = m_data2.Left(n);
				m_data2 = m_data2.Mid(n+1);
			}

		}
		HtmlReport.WriteHTMLFile(sFile);
		
		iRow = m_nROWS;		iCol = 10;
		CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title);

		if(m_title.Left(1)=="G")		HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("P_Affected"), _Z("Country"), _Z("Coordinates"), _Z("Azimuth(Deg)"), _Z("Distance(km)"), m_DorE, _Z("Heff(m)"),_Z("Band(MHz)"),_Z("Region"));
		else							HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("P_Affected"), _Z("Country"), _Z("Coordinates"), _Z("Azimuth(Deg)"), _Z("Distance(km)"), m_DorE, _Z("Heff(m)"),_Z("Band"),_Z("Region"));
		if(m_title.Left(4)=="GE89")		HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("P_Affected"), _Z("Country"), _Z("Coordinates"), _Z("Azimuth(Deg)"), _Z("Distance(km)"), m_DorE, _Z("Heff(m)"),_Z("Frequency(MHz)"),_Z("Region"));

		for( j = 1; iRow>1; j++)
		{
			ResultSTR.Format("%d",j-0);
		//	sCELL[0] = (j==1) ? " " : ResultSTR;
			sCELL[0] = ResultSTR;

			for( i=0;i<iCol-1;i++)
			{
				n = m_data2.Find(',',0);
				ResultSTR = m_data2.Left(n);
				m_data2 = m_data2.Mid(n+1);
				sCELL[i+1] = ResultSTR;
			}
			HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9]);
			iRow--;
		}
//		HtmlReport1.WriteHTMLFile(sFile);

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


