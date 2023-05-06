// DataBaseDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "DataBaseDLG.h"

#include "HTML_Report.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataBaseDLG dialog


CDataBaseDLG::CDataBaseDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CDataBaseDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataBaseDLG)
	m_Heff1 = FALSE;
	m_Heff = TRUE;
	m_ReportFlag = TRUE;
	//}}AFX_DATA_INIT
	m_Title = _Z("Station Table");
	m_pToolTip = NULL;
	m_GridLoaded = FALSE;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CDataBaseDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataBaseDLG)
	DDX_Control(pDX, IDC_BUTTON_Report, m_BUTTON_Report);
	DDX_Control(pDX, IDC_Sort_ZA, m_Sort_ZA);
	DDX_Control(pDX, IDC_Sort_AZ, m_Sort_AZ);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_DataGrid);
	DDX_Text(pDX, IDC_EDIT_Heff1, m_Heff1);
	DDX_Check(pDX, IDC_CHECK_Heff, m_Heff);
	DDX_Text(pDX, IDC_EDIT_reportFlag, m_ReportFlag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataBaseDLG, CDialog)
	//{{AFX_MSG_MAP(CDataBaseDLG)
	ON_WM_SIZING()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Sort_AZ, OnSortAZ)
	ON_BN_CLICKED(IDC_Sort_ZA, OnSortZA)
	ON_BN_CLICKED(IDC_CHECK_Heff, OnCHECKHeff)
	ON_BN_CLICKED(IDC_BUTTON_Report, OnBUTTONReport)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataBaseDLG message handlers

BOOL CDataBaseDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_SMS4DCTYPE5))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_Sort_AZ.LoadBitmaps(IDB_Sort_AZ1,IDB_Sort_AZ2);
	m_Sort_ZA.LoadBitmaps(IDB_Sort_ZA1,IDB_Sort_ZA2);
	m_DataGrid.m_FlexGrid= (CMSFlexGrid *)GetDlgItem(IDC_MSFLEXGRID1);

	m_DataGrid.SetColWidth(0,300);
	m_O = m_DataGrid.LoadData();	

	CWnd *xx;	xx = GetDlgItem(IDC_CHECK_Heff);
	xx->ShowWindow(m_Heff1);

	m_BUTTON_Report.LoadBitmaps(IDB_Report1,IDB_Report2);
	m_BUTTON_Report.ShowWindow(m_ReportFlag);

	if(m_O==1)
		SetWindowText(m_Title);
	else
		SetWindowText(_Z("Warning !!!   (No station found)"));

	m_pToolTip = new CToolTipCtrl;
	m_pToolTip->Create(this);
	m_pToolTip->AddTool(&m_Sort_AZ,_Z("Sort A to Z"));
	m_pToolTip->AddTool(&m_Sort_ZA,_Z("Sort Z to A"));
	m_pToolTip->AddTool(&m_BUTTON_Report,_Z("View Report"));
	m_pToolTip->Activate(TRUE);

	m_GridLoaded = TRUE;
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE; 
}

void CDataBaseDLG::OnSortAZ() 
{
/*
	m_DataGrid.SetCols(m_DataGrid.GetCols() + 1);
    int SortCol = m_DataGrid.GetCols() - 1;
    for(int Ro = 1 ; Ro<m_DataGrid.GetRows() ; Ro++)
	{
        CString SortKey = "";
        for(int Col = m_DataGrid.GetCol() ; Col<m_DataGrid.GetColSel()+1 ;Col++)
            SortKey = SortKey + m_DataGrid.GetTextMatrix(Ro, Col);
        m_DataGrid.SetTextMatrix(Ro, SortCol, SortKey);
    }//end for
    m_DataGrid.m_Entrance = 0;
    int TempCol = m_DataGrid.GetCol();
    m_DataGrid.SetCol(SortCol);
        m_DataGrid.SetSort(5);
    m_DataGrid.SetCols(m_DataGrid.GetCols() - 1);
    m_DataGrid.SetCol(TempCol);
    m_DataGrid.m_Entrance = 1;
*/
	m_DataGrid.SetColSel(m_DataGrid.GetCol());
	switch(m_DataGrid.m_fields[m_DataGrid.GetCol()-1].FType)
	{
		case DBVT_SHORT:	m_DataGrid.SetSort(1);	break;
		case DBVT_LONG:		m_DataGrid.SetSort(1);	break;
		case DBVT_UCHAR:	m_DataGrid.SetSort(5);	break;
		case DBVT_STRING:	m_DataGrid.SetSort(5);	break;
		case DBVT_SINGLE:	m_DataGrid.SetSort(1);	break;
		case DBVT_DOUBLE:	m_DataGrid.SetSort(1);	break;
		default :			m_DataGrid.SetSort(5);	break;
	}	
}


void CDataBaseDLG::OnSortZA() 
{
/*
	m_DataGrid.SetCols(m_DataGrid.GetCols() + 1);
    int SortCol = m_DataGrid.GetCols() - 1;
    for(int Ro = 1 ; Ro<m_DataGrid.GetRows() ; Ro++)
	{
        CString SortKey = "";
        for(int Col = m_DataGrid.GetCol() ; Col<m_DataGrid.GetColSel()+1 ;Col++)
            SortKey = SortKey + m_DataGrid.GetTextMatrix(Ro, Col);
        m_DataGrid.SetTextMatrix(Ro, SortCol, SortKey);
    }//end for
    m_DataGrid.m_Entrance = 0;
    int TempCol = m_DataGrid.GetCol();
    m_DataGrid.SetCol(SortCol);
        m_DataGrid.SetSort(6);
    m_DataGrid.SetCols(m_DataGrid.GetCols() - 1);
    m_DataGrid.SetCol(TempCol);
    m_DataGrid.m_Entrance = 1;
*/
	m_DataGrid.SetColSel(m_DataGrid.GetCol());
	switch(m_DataGrid.m_fields[m_DataGrid.GetCol()-1].FType)
	{
		case DBVT_SHORT:	m_DataGrid.SetSort(2);	break;
		case DBVT_LONG:		m_DataGrid.SetSort(2);	break;
		case DBVT_UCHAR:	m_DataGrid.SetSort(6);	break;
		case DBVT_STRING:	m_DataGrid.SetSort(6);	break;
		case DBVT_SINGLE:	m_DataGrid.SetSort(2);	break;
		case DBVT_DOUBLE:	m_DataGrid.SetSort(2);	break;
		default :			m_DataGrid.SetSort(6);	break;
	}
}

void CDataBaseDLG::OnSizing( UINT nSide, LPRECT lpRect)
{
	CDialog::OnSizing(nSide, lpRect);
/*
	CRect Rct;
	m_DataGrid.GetWindowRect(&Rct);
	m_DataGrid.SetWindowPos(&CWnd::wndTopMost,
		0,
		40,
		lpRect->right-lpRect->left-10,
		lpRect->bottom-lpRect->top-70,
		SWP_SHOWWINDOW);
*/

}

BEGIN_EVENTSINK_MAP(CDataBaseDLG, CDialog)
    //{{AFX_EVENTSINK_MAP(CDataBaseDLG)
	ON_EVENT(CDataBaseDLG, IDC_MSFLEXGRID1, -607 /* MouseUp */, OnMouseUpMsflexgrid1, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDataBaseDLG::OnMouseUpMsflexgrid1(short Button, short Shift, long x, long y) 
{
	m_DataGrid.OnMouseUp(Button, Shift, x, y);
}


HCURSOR CDataBaseDLG::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDataBaseDLG::OnOK() 
{
	if ((m_DataGrid.m_MaxRowSel >0)&&(m_O==1))
	{
		m_DataGrid.GetSelection();
	}
	CDialog::OnOK();
}

void CDataBaseDLG::OnCHECKHeff() 
{
	UpdateData();
	m_Heff1 = m_Heff;	
	UpdateData(false);
}

void CDataBaseDLG::OnBUTTONReport() 
{
/*
	CFileDialog oFileDlg(FALSE, 
						_T("html"), _T("OutPutFile"), 
						OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
						_T("HTML Files (*.html)|*.html|"), this );
	oFileDlg.m_ofn.lpstrTitle = _T("Save HTML file as...");
	if (oFileDlg.DoModal() == IDOK)
	{
		CString sFile = oFileDlg.GetFileName();

		long iCol = m_DataGrid.GetCols();
		long iRow = m_DataGrid.GetRows();
		long i,j;
		CString *sCELL; sCELL = new CString[iCol-1];

		m_DataGrid.SetRow(0);
		for( i=0; i<iCol-1;i++)
		{
			m_DataGrid.SetCol(i+1);
			sCELL[i] = m_DataGrid.GetText();
		}
		CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_Title," ");
		HtmlReport.InsertTableHeader1(iCol-1, sCELL);
		for( j=1; j<iRow;j++)
		{
			m_DataGrid.SetRow(j);
			for( i=0;i<iCol-1;i++)
			{
				m_DataGrid.SetCol(i+1);
				sCELL[i] = m_DataGrid.GetText();
			}
			HtmlReport.InsertTableRow1( sCELL);
		}
		HtmlReport.WriteHTMLFile(sFile);
		ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);

		delete [] sCELL;
	}
*/
	CFileDialog oFileDlg(FALSE, _T("CSV"), _T("OutPutFile"), 
						OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
						_Z("CSV Files (*.CSV)|*.CSV|"), this );

	CString s = _Z("Save CSV file as...");	
	oFileDlg.m_ofn.lpstrTitle = s;
	if (((CSMS4DCApp *)AfxGetApp())->IsWin2000())		oFileDlg.m_ofn.lStructSize = 88;		//76
	if (oFileDlg.DoModal() == IDOK)
	{
		long iCol = m_DataGrid.GetCols();
		long iRow = m_DataGrid.GetRows();
		long i,j;

		CString sFilePath = oFileDlg.GetPathName();
		FILE *fp = fopen(sFilePath,_T("wt"));

		CString sSeparator = _T(";");
		TCHAR sz[2];
		int bResult = GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SLIST, sz, 2);
		if(bResult==2)	sSeparator  = sz;

		m_DataGrid.SetRow(0);
//		m_DataGrid.SetCol(1); CString str = m_DataGrid.GetText();str.Replace(_T("ID"),_T(" ID")); fprintf(fp,_T("%s"),str);
		fprintf(fp, _T("SMS4DC\n") );m_DataGrid.SetCol(1);	fprintf(fp,_T("%s") ,m_DataGrid.GetText());
		for( i=1; i<iCol-1;i++)
		{
			m_DataGrid.SetCol(i+1);		fprintf(fp,_T("%s%s") ,sSeparator,m_DataGrid.GetText());
		}
		fprintf(fp,_T("\n") );

		for( j=1; j<iRow;j++)
		{
			m_DataGrid.SetRow(j);
			m_DataGrid.SetCol(1);		fprintf(fp,_T("%s") ,m_DataGrid.GetText());
			for( i=1;i<iCol-1;i++)
			{
				m_DataGrid.SetCol(i+1); fprintf(fp,_T("%s%s") ,sSeparator,m_DataGrid.GetText());
			}
			fprintf(fp,_T("\n") );
		}
		fclose(fp);
		ShellExecute(m_hWnd, _T("open"), sFilePath, NULL, NULL, SW_SHOWNORMAL);
	}
}

void CDataBaseDLG::PostNcDestroy() 
{
	delete m_pToolTip;
	
	CDialog::PostNcDestroy();
}

BOOL CDataBaseDLG::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
            m_pToolTip->RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDataBaseDLG::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect Rct;
	if(m_GridLoaded)
	{
		m_DataGrid.GetWindowRect(&Rct);
		m_DataGrid.SetWindowPos(&CWnd::wndTopMost,
			10,
			40,
			cx-10-10,
			cy-12-40,
			SWP_SHOWWINDOW);
	}
}
