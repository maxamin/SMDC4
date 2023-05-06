// Int_ES2ESoutDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Int_ES2ESoutDLG.h"
#include "HTML_Report.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInt_ES2ESoutDLG dialog


CInt_ES2ESoutDLG::CInt_ES2ESoutDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CInt_ES2ESoutDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInt_ES2ESoutDLG)
	m_rowsY = 0;
	m_editX = _T("");
	m_editY = _T("");
	//}}AFX_DATA_INIT
	m_Title1 = _Z("P.452 ES2ES : Interference from the Wanted ES to the Found ES(s)");
	m_Title2 = _Z("Wanted ES (Tx): ");
	m_Title3 = _Z("Found ES(s) (Rx):");
	m_mode = 1;

}


void CInt_ES2ESoutDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInt_ES2ESoutDLG)
	DDX_Text(pDX, IDC_EDIT_rowsY, m_rowsY);
	DDX_Text(pDX, IDC_EDIT_X, m_editX);
	DDX_Text(pDX, IDC_EDIT_Y, m_editY);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_LIST1);
	DDX_Control(pDX, IDC_MSFLEXGRID2, m_LIST2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInt_ES2ESoutDLG, CDialog)
	//{{AFX_MSG_MAP(CInt_ES2ESoutDLG)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInt_ES2ESoutDLG message handlers

BOOL CInt_ES2ESoutDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_Title1);
	CStatic *x2;	x2 = (CStatic *)GetDlgItem(IDC_STATIC_t2);	x2->SetWindowText(m_Title2);
	CStatic *x3;	x3 = (CStatic *)GetDlgItem(IDC_STATIC_t3);	x3->SetWindowText(m_Title3);

	if(	m_mode == 1)
	{
		int nCOLS = 8;	
		m_LIST1.SetCols(nCOLS);
		m_LIST1.SetColWidth(0,400);
		m_LIST1.SetColWidth(1,500);
		m_LIST1.SetColWidth(2,1000);
		m_LIST1.SetColWidth(3,800);
		m_LIST1.SetColWidth(4,1200);
		m_LIST1.SetColWidth(5,1200);
		m_LIST1.SetColWidth(6,1900);
		m_LIST1.SetColWidth(7,1200);

		m_LIST1.SetRowHeight(0,400);
		m_LIST1.SetRow(0);
		m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
		m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("CTRY"));
		m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("Notice ID"));
		m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("Beam"));
		m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Group ID"));
		m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("ES Name"));
		m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("Location"));
		m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Freq(MHz)"));

		int m_nROWS = m_rowsX;
		int n;
		CString ResultSTR;
		m_LIST1.SetRows(m_nROWS);

		for(int j=0;j<m_nROWS-1;j++)
		{
			m_LIST1.SetRow(j+1);
			m_LIST1.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST1.SetText(ResultSTR);

			m_editX = m_strXt[j];

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editX.Find(',',0);
				ResultSTR = m_editX.Left(n);
				m_editX = m_editX.Mid(n+1);
				m_LIST1.SetCol(i+1);
				m_LIST1.SetText(ResultSTR);
			}
			m_LIST1.SetCol(nCOLS-1);
			m_LIST1.SetText(m_editX);
		}

	//////////////////////////////////////////
		nCOLS = 14; 
		m_LIST2.SetCols(nCOLS);
		m_LIST2.SetColWidth(0,400);
		m_LIST2.SetColWidth(1,500);
		m_LIST2.SetColWidth(2,1000);
		m_LIST2.SetColWidth(3,800);
		m_LIST2.SetColWidth(4,1200);
		m_LIST2.SetColWidth(5,1200);
		m_LIST2.SetColWidth(6,1900);
		m_LIST2.SetColWidth(7,1200);
		m_LIST2.SetColWidth(8,1200);
		m_LIST2.SetColWidth(9,900);
		m_LIST2.SetColWidth(10,1000);
		m_LIST2.SetColWidth(11,1000);
		m_LIST2.SetColWidth(12,1000);
		m_LIST2.SetColWidth(13,2000);

		m_LIST2.SetRowHeight(0,400);
		m_LIST2.SetRow(0);
		m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
		m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("CTRY"));
		m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("Notice ID"));
		m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Beam"));
		m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("Group ID"));
		m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("ES Name"));
		m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("IntDist(km)"));
		m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Freq(MHz)"));
		m_LIST2.SetCol(9);		m_LIST2.SetText(_T("TD(dB)"));
		m_LIST2.SetCol(10);		m_LIST2.SetText(_T("I(dBW)"));
		m_LIST2.SetCol(11);		m_LIST2.SetText(_T("Pr(dBW)"));
		m_LIST2.SetCol(12);		m_LIST2.SetText(_T("I-Pr(dB)"));
		m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("Path Type"));

		m_rowsY = m_rowsYx[0];
		m_editY = m_strYt[0];

		m_LIST2.SetRows(m_rowsY);

		for( j=0;j<m_rowsY-1;j++)
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
		if(m_rowsY>1)
		{
			m_LIST2.SetCol(nCOLS-1);
			m_LIST2.SetText(m_editY);	

			m_LIST2.SetCol(12);
			for(j=0;j<m_rowsY-1;j++)
			{
				m_LIST2.SetRow(j+1);
				if(((m_LIST2.GetText()) != _T("-"))&&((atof(m_LIST2.GetText()))>=0))
					m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
		}
	}


	else if((m_mode == 2)||(m_mode == 3))
	{
		int nCOLS = 8;	
		m_LIST1.SetCols(nCOLS);
		m_LIST1.SetColWidth(0,400);
		m_LIST1.SetColWidth(1,500);
		m_LIST1.SetColWidth(2,1000);
		m_LIST1.SetColWidth(3,800);
		m_LIST1.SetColWidth(4,1200);
		m_LIST1.SetColWidth(5,1200);
		m_LIST1.SetColWidth(6,1900);
		m_LIST1.SetColWidth(7,1200);

		m_LIST1.SetRowHeight(0,400);
		m_LIST1.SetRow(0);
		m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
		m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("CTRY"));
		m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("Notice ID"));
		m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("Beam"));
		m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Group ID"));
		m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("ES Name"));
		m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("Location"));
		m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Freq(MHz)"));

		int m_nROWS = m_rowsX;
		int n;
		CString ResultSTR;
		m_LIST1.SetRows(m_nROWS);

		for(int j=0;j<m_nROWS-1;j++)
		{
			m_LIST1.SetRow(j+1);
			m_LIST1.SetCol(0);
			ResultSTR.Format("%d",j+1);
			m_LIST1.SetText(ResultSTR);

			m_editX = m_strXt[j];

			for(int i=0;i<nCOLS-1;i++)
			{
				n = m_editX.Find(',',0);
				ResultSTR = m_editX.Left(n);
				m_editX = m_editX.Mid(n+1);
				m_LIST1.SetCol(i+1);
				m_LIST1.SetText(ResultSTR);
			}
			m_LIST1.SetCol(nCOLS-1);
			m_LIST1.SetText(m_editX);
		}

	//////////////////////////////////////////
		nCOLS = 12; 
		m_LIST2.SetCols(nCOLS);
		m_LIST2.SetColWidth(0,400);
		m_LIST2.SetColWidth(1,500);
		m_LIST2.SetColWidth(2,1000);
		m_LIST2.SetColWidth(3,1200);
		m_LIST2.SetColWidth(4,1900);
		m_LIST2.SetColWidth(5,1200);
		m_LIST2.SetColWidth(6,1200);
		m_LIST2.SetColWidth(7,900);
		m_LIST2.SetColWidth(8,1000);
		m_LIST2.SetColWidth(9,1000);
		m_LIST2.SetColWidth(10,1000);
		m_LIST2.SetColWidth(11,2000);

		m_LIST2.SetRowHeight(0,400);
		m_LIST2.SetRow(0);
		m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
		m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("CTRY"));
		m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("ST ID"));
		m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("ST Name"));
		m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("Location"));
		m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("IntDist(km)"));
		m_LIST2.SetCol(6);
			if(m_mode == 2)		m_LIST2.SetText(_Z("RxFreq(MHz)"));
			else				m_LIST2.SetText(_Z("TxFreq(MHz)"));
		m_LIST2.SetCol(7);		m_LIST2.SetText(_T("TD(dB)"));
		m_LIST2.SetCol(8);		m_LIST2.SetText(_T("I(dBW)"));
		m_LIST2.SetCol(9);		m_LIST2.SetText(_T("Pr(dBW)"));
		m_LIST2.SetCol(10);		m_LIST2.SetText(_T("I-Pr(dB)"));
		m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("Path Type"));

		m_rowsY = m_rowsYx[0];
		m_editY = m_strYt[0];

		m_LIST2.SetRows(m_rowsY);

		for( j=0;j<m_rowsY-1;j++)
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
		if(m_rowsY>1)
		{
			m_LIST2.SetCol(nCOLS-1);
			m_LIST2.SetText(m_editY);
			
			m_LIST2.SetCol(10);
			for(j=0;j<m_rowsY-1;j++)
			{
				m_LIST2.SetRow(j+1);
				if(((m_LIST2.GetText()) != _T("-"))&&((atof(m_LIST2.GetText()))>=0))
					m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
		}

	}

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

BEGIN_EVENTSINK_MAP(CInt_ES2ESoutDLG, CDialog)
    //{{AFX_EVENTSINK_MAP(CInt_ES2ESoutDLG)
	ON_EVENT(CInt_ES2ESoutDLG, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CInt_ES2ESoutDLG::OnClickMsflexgrid1() 
{
	if(	m_mode == 1)
	{
		long r = m_LIST1.GetRow();
		CString str;		str.Format("%ld",r);

		CString ResultSTR;
		int	n, nCOLS = 14; 

		m_rowsY = m_rowsYx[r-1];
		m_editY = m_strYt[r-1];

		m_LIST2.SetRows(m_rowsY);
		for(int j=0;j<m_rowsY-1;j++)
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
		if(m_rowsY>1)
		{
			m_LIST2.SetCol(nCOLS-1);
			m_LIST2.SetText(m_editY);	

			m_LIST2.SetCol(12);
			for(j=0;j<m_rowsY-1;j++)
			{
				m_LIST2.SetRow(j+1);
				m_LIST2.SetCellBackColor(RGB(255,255,255));
				if(((m_LIST2.GetText()) != _T("-"))&&((atof(m_LIST2.GetText()))>=0))
					m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
		}
	}

	else if((m_mode == 2)||(m_mode == 3))
	{
		long r = m_LIST1.GetRow();
		CString str;		str.Format("%ld",r);

		CString ResultSTR;
		int	n, nCOLS = 12; 

		m_rowsY = m_rowsYx[r-1];
		m_editY = m_strYt[r-1];

		m_LIST2.SetRows(m_rowsY);
		for(int j=0;j<m_rowsY-1;j++)
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
		if(m_rowsY>1)
		{
			m_LIST2.SetCol(nCOLS-1);
			m_LIST2.SetText(m_editY);	

			m_LIST2.SetCol(10);
			for(j=0;j<m_rowsY-1;j++)
			{
				m_LIST2.SetRow(j+1);
				m_LIST2.SetCellBackColor(RGB(255,255,255));
				if(((m_LIST2.GetText()) != _T("-"))&&((atof(m_LIST2.GetText()))>=0))
					m_LIST2.SetCellBackColor(RGB(255,150,150));
			}
		}


	}

}

void CInt_ES2ESoutDLG::OnOK() 
{
	if(	m_mode == 1)
	{
		CFileDialog oFileDlg(FALSE, 
							_T("html"), _T("OutPutFile"), 
							OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
							_Z("HTML Files")+" (*.html)|*.html|", this );
		CString str = _Z("Save HTML file as...");
		oFileDlg.m_ofn.lpstrTitle = str;
		if (oFileDlg.DoModal() == IDOK)
		{
			CString sFile, ResultSTR, sCELL[14], m_dataX1, m_dataY1;
			int i, j, n , iRow = m_rowsX, iCol = 8;
			sFile = oFileDlg.GetFileName();
			CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_Title2,m_Title1);
			HtmlReport.InsertTableHeader(iCol, _Z("No."), _Z("CTRY"), _Z("Notice ID"), _Z("Beam"),_Z("Group ID"), _Z("ES Name"),_Z("Location"),_Z("Freq(MHz)"));
			
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				m_dataX1 = m_strXt[j-1]+",";

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

			iCol = 14;
			for(long r=1;r<m_rowsX;r++)
			{
				iRow = m_rowsYx[r-1];
				m_dataY1 = m_strYt[r-1]+",";

				CString titFlage = _T("");
				BOOL timeFlag = FALSE;

				if(r==m_rowsX-1)
					timeFlag = TRUE;
				if(r==1)
					titFlage = m_Title3;

				CHTML_Report HtmlReport1(timeFlag, "OutPut HTML","Behzad Paknahad",titFlage);
				HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("CTRY"), _Z("Notice ID"),_Z("Beam"), _Z("Group ID"), _Z("ES Name"),_Z("Location"),_Z("IntDist(km)"), _Z("Freq(MHz)"), "TD(dB)", "I(dBW)", "Pr(dBW)","I-Pr(dB)", _Z("Path Type"));
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
					HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13]);
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
			}
			ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////
	else if((m_mode == 2)||(m_mode == 3))
	{
		CFileDialog oFileDlg(FALSE, 
							_T("html"), _T("OutPutFile"), 
							OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
							_Z("HTML Files")+" (*.html)|*.html|", this );
		CString str = _Z("Save HTML file as...");
		oFileDlg.m_ofn.lpstrTitle = str;
		if (oFileDlg.DoModal() == IDOK)
		{
			CString sFile, ResultSTR, sCELL[12], m_dataX1, m_dataY1;
			int i, j, n , iRow = m_rowsX, iCol = 8;
			sFile = oFileDlg.GetFileName();
			CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_Title2,m_Title1);
			HtmlReport.InsertTableHeader(iCol, _Z("No."), _Z("CTRY"), _Z("Notice ID"), _Z("Beam"),_Z("Group ID"), _Z("ES Name"),_Z("Location"),_Z("Freq(MHz)"));
			
			for( j = 1; iRow>1; j++)
			{
				ResultSTR.Format("%d",j);
				sCELL[0] = ResultSTR;
				m_dataX1 = m_strXt[j-1]+",";

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

			iCol = 12;
			for(long r=1;r<m_rowsX;r++)
			{
				iRow = m_rowsYx[r-1];
				m_dataY1 = m_strYt[r-1]+",";

				CString titFlage = _T("");
				BOOL timeFlag = FALSE;

				if(r==m_rowsX-1)
					timeFlag = TRUE;
				if(r==1)
					titFlage = m_Title3;

				CHTML_Report HtmlReport1(timeFlag, "OutPut HTML","Behzad Paknahad",titFlage);

				if (m_mode == 2)
					HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("CTRY"), _Z("ST ID"),_Z("ST Name"), _Z("Location"),_Z("IntDist(km)"), _Z("RxFreq(MHz)"), "TD(dB)", "I(dBW)", "Pr(dBW)","I-Pr(dB)", _Z("Path Type"));
				else
					HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("CTRY"), _Z("ST ID"),_Z("ST Name"), _Z("Location"),_Z("IntDist(km)"), _Z("TxFreq(MHz)"), "TD(dB)", "I(dBW)", "Pr(dBW)","I-Pr(dB)", _Z("Path Type"));

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
			}
			ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
		}
	}

//	CDialog::OnOK();
}

void CInt_ES2ESoutDLG::OnClose() 
{
	delete [] m_strXt;	
	delete [] m_strYt;	
	delete [] m_rowsYx;	
	CDialog::OnClose();
}
