// StationsTableView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "StationsTableView.h"
#include "StationsTableDoc.h"
#include "Columns.h"
#include "Column.h"
#include "_recordset.h"
#include "MainFrm.h"

#include "ANTpatternDLG.h"

#include "TxRxFilterDLG.h"
#include "afxdb.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationsTableView

IMPLEMENT_DYNCREATE(CStationsTableView, CFormView)

BEGIN_MESSAGE_MAP(CStationsTableView, CFormView)
	//{{AFX_MSG_MAP(CStationsTableView)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPORT, OnExport)
	ON_COMMAND(ID_IMPORT, OnImport)
	ON_COMMAND(ID_DataBase_SortAZ, OnDataBaseSortAZ)
	ON_COMMAND(ID_DataBase_SortZA, OnDataBaseSortZA)
	ON_COMMAND(ID_AsAntenna, OnAsAntenna)
	ON_COMMAND(ID_ShowPattern, OnShowPattern)
	ON_COMMAND(ID_BUTTON_Tx, OnBUTTONTx)
	ON_COMMAND(ID_BUTTON_Rx, OnBUTTONRx)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_GETSELECTION, GetSelection)
END_MESSAGE_MAP()

CStationsTableView::CStationsTableView()
	: CFormView(CStationsTableView::IDD)
{
	//{{AFX_DATA_INIT(CStationsTableView)
	m_AllowEdit = FALSE;
	//}}AFX_DATA_INIT
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarDATABASE), TRUE, FALSE);
}

CStationsTableView::~CStationsTableView()
{
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarDATABASE), FALSE, FALSE);
}

void CStationsTableView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStationsTableView)
	DDX_Control(pDX, IDC_ADODC1, m_ADO1);
	DDX_Check(pDX, IDC_CHECK1, m_AllowEdit);
	DDX_Control(pDX, IDC_DATAGRID1, m_GRID1);
	//}}AFX_DATA_MAP
}

BOOL CStationsTableView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CStationsTableView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

//	GetParentFrame()->ShowControlBar(&((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar1,
//	(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar1.GetStyle()&WS_VISIBLE)==0,false);


	CSize totalSize(100,100);
    CSize pageSize(50,50);
	CSize lineSize(10,10);
	SetScrollSizes(MM_TEXT, totalSize,pageSize,lineSize);

	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_MaxRowSel=0;
	for(int i=1;i<=m_ADO1.GetRecordset().GetRecordCount() ;i++)
		m_RowStat[i].Selected=0;

}

/////////////////////////////////////////////////////////////////////////////
// CStationsTableView diagnostics

#ifdef _DEBUG
void CStationsTableView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStationsTableView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


/////////////////////////////////////////////////////////////////////////////
// CStationsTableView message handlers

CStationsTableDoc* CStationsTableView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStationsTableDoc)));
	return (CStationsTableDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStationsTableView message handlers

void CStationsTableView::OnCheck1() 
{
	UpdateData(TRUE);
	if (m_AllowEdit==1)
	{
		m_GRID1.SetAllowAddNew(TRUE);
		m_GRID1.SetAllowDelete(TRUE);
		m_GRID1.SetAllowUpdate(TRUE);
	}
	else if (m_AllowEdit==0)
	{
		m_GRID1.SetAllowAddNew(FALSE);
		m_GRID1.SetAllowDelete(FALSE);
		m_GRID1.SetAllowUpdate(FALSE);
	}
	UpdateData(FALSE);
}


BEGIN_EVENTSINK_MAP(CStationsTableView, CFormView)
    //{{AFX_EVENTSINK_MAP(CStationsTableView)
	ON_EVENT(CStationsTableView, IDC_DATAGRID1, -607 /* MouseUp */, OnMouseUpDatagrid1, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void CStationsTableView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if(m_GRID1.m_hWnd)
	{
		CRect Rct;
		m_GRID1.GetWindowRect(&Rct);
		m_GRID1.SetWindowPos(&CWnd::wndTopMost,
			0,
			25,
			cx,
			cy-25,
			SWP_SHOWWINDOW);
		/*m_GRID1.GetParentFrame()->SetWindowPos(&CWnd::wndTopMost,
			0,
			25,
			cx,
			cy-25,
			SWP_SHOWWINDOW);*/
	}//end if
}


void CStationsTableView::OnMouseUpDatagrid1(short Button, short Shift, long X, long Y) 
{
    int tempCol, tempRow, rstat;
    if( Shift == 2) // Ctrl key pressed
	{
        m_Entrance = 0;
        tempCol = m_GRID1.GetCol();
		tempRow = m_GRID1.GetRow();
		m_GRID1.SetRow(GetRow(X, Y));
 		long ttt=m_GRID1.GetSelStart();
        m_GRID1.SetCol(0);
		int cc=atoi(m_GRID1.GetText());
        if(m_RowStat[cc].Selected) 
            rstat = 0;
        else
            rstat = 1;
        m_RowStat[cc].Selected = rstat;
        if(rstat == 1)
		{
            m_MaxRowSel = m_MaxRowSel + 1;
            m_RowStat[cc].index = m_MaxRowSel;
		}
        m_GRID1.SetCol(tempCol);
		m_GRID1.SetRow(tempRow);
        m_Entrance = 1;
    }//end if	
}

void CStationsTableView::GetSelection()
{
	int i, j, k,Selcount = 0;
    k = 0;
	for(i = 1 ; i<=m_ADO1.GetRecordset().GetRecordCount() - 1; i++)
        if(m_RowStat[i].Selected)
			Selcount = Selcount + 1;
    for (i = 1 ; i<=m_MaxRowSel; i++)
	{
        if( k == Selcount)
			break;
        for( j = 1 ; j<=m_ADO1.GetRecordset().GetRecordCount() - 1; j++)
            if(m_RowStat[j].index == i && m_RowStat[j].Selected)
				break;
        if(j != m_ADO1.GetRecordset().GetRecordCount())
		{
            m_Sel[k] = GetRowText(FindOrigRow(j));
            k = k + 1;
        }//end if
    }//end for


	((CSMS4DCApp *)AfxGetApp())->Nrow=m_MaxRowSel;
	((CSMS4DCApp *)AfxGetApp())->m_Sel=new CString[m_MaxRowSel];
    for (k = 0 ; k<m_MaxRowSel; k++)
		((CSMS4DCApp *)AfxGetApp())->m_Sel[k]=m_Sel[k];

}

int CStationsTableView::FindOrigRow(int j)
{
    m_Entrance=0;
	int i,Col=m_GRID1.GetCol(),Row=m_GRID1.GetRow(),Res;
	m_GRID1.SetCol(0);
    for(i = 0 ; i<=m_ADO1.GetRecordset().GetRecordCount() - 1 ;i++)
	{
		m_GRID1.SetRow(i);
		CString txt=m_GRID1.GetText();
        if(atoi(txt)== j) break;
	}//end for
    if(i == m_ADO1.GetRecordset().GetRecordCount())
        Res=-1; //not found
    else
        Res=i;  // found
	m_GRID1.SetCol(Col);
	m_GRID1.SetRow(Row);
	m_Entrance=1;
	return Res;
}

CString CStationsTableView::GetRowText(int j)
{
    CString tmp;
    m_Entrance = 0;
    tmp = "";
	int Col=m_GRID1.GetCol(),Row=m_GRID1.GetRow();
	m_GRID1.SetRow(j);
    for (int i = 1 ; i<m_GRID1.GetColumns().GetCount() ; i++)
	{
		m_GRID1.SetCol(i);
        tmp = tmp + m_GRID1.GetText() + ",";
	}//end for
	tmp = tmp.Left(tmp.GetLength() - 1);
    m_Entrance = 1;
    return tmp;
}

int CStationsTableView::GetRow(int X, int Y)
{
	return (Y-15)/((int)m_GRID1.GetRowHeight()+5);
}

void CStationsTableView::OnExport() 
{
	CFileDialog FileDialog(false,"txt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Export Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	if(FileDialog.DoModal()==IDOK)
	{
		FILE *fp;
		if(fp=fopen(FileDialog.GetPathName(),"wt"))
		{
			int Col=m_GRID1.GetCol(),Row=m_GRID1.GetRow();
			m_Entrance=0;
			CString buf;
			VARIANT Colindex;
			Colindex.vt=VT_I2;
			for (int i = 0; i<m_GRID1.GetColumns().GetCount();i++)
			{
				Colindex.iVal=i;
				buf=buf+m_GRID1.GetColumns().GetItem(Colindex).GetCaption()+"\t";
			}//end for
			buf = buf.Left(buf.GetLength() - 1);
			fprintf(fp,"%s\n", buf);
			buf = "";

			int uRow=(m_ADO1.GetRecordset().GetRecordCount());
			int uCol=(m_GRID1.GetColumns().GetCount());

			for ( i = 0; i<uRow ;i++)
			{
				m_GRID1.SetRow(i);
				for(int j = 0 ; j<uCol ;j++)
				{
					m_GRID1.SetCol(j);
					buf = buf + m_GRID1.GetText() + "\t";
			//		buf = buf + m_GRID1.GetText() + ";";
				}//end for
				buf = buf.Left(buf.GetLength() - 1);
				fprintf(fp,"%s\n", buf);
				buf = "";
			}//end for
			m_GRID1.SetCol(Col);
			m_GRID1.SetRow(Row);
			m_Entrance=1;
			fclose(fp);
		}//end if
	}//end if IDOK
	
}

void CStationsTableView::OnImport() 
{
	CFileDialog FileDialog(true,"txt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Import Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	if(FileDialog.DoModal()==IDOK)
	{
		FILE *fp;
		if(fp=fopen(FileDialog.GetPathName(),"rt"))
		{
			int place = 1,Col=m_GRID1.GetCol(),Row=m_GRID1.GetRow();
			CString buf;
			fscanf(fp,"%s", buf);
			m_Entrance=0;
			m_GRID1.SetRow(0);
			for(int i = 0 ; i<m_GRID1.GetColumns().GetCount();i++)
			{
				CString Fld = "";
				for(int j = place ; j<=buf.GetLength();j++)
				{
					if(buf.Mid(j, 1) == "\t") break;
					Fld = Fld + buf.Mid(j, 1);
				}//end for
				place = j + 1;
				m_GRID1.SetCol(i);
				if(m_GRID1.GetText() != Fld)
				{
					MessageBox("The structure of the chosen file is not suitable for import",  "Error");
					goto out;
				}//end if
				if( place > buf.GetLength()) break;
			}//end for
/*			while(true)
			{
				if(feof(fp)) break;
				fscanf(fp,"%s", buf);
				m_ADO1.GetRecordset().AddNew();
				grid1.Rows = grid1.Rows + 1
				'grid1.TextMatrix(grid1.Rows - 1, 1) = grid1.Rows - 1
				grid1.RowData(grid1.Rows - 1) = grid1.Rows - 1
				place = 1
				For fldno = 0 To rs.fields.Count - 1
					Fld = ""
					For j = place To Len(buf)
						If Mid(buf, j, 1) = Chr(9) Then Exit For
						Fld = Fld + Mid(buf, j, 1)
					Next j
					place = j + 1
					If (rs.fields(fldno).Attributes And dbAutoIncrField) = dbAutoIncrField Then
						'grid1.TextMatrix(grid1.Rows - 1, fldno + 2) = rs.fields(fldno).Value
						grid1.TextMatrix(grid1.Rows - 1, fldno + 1) = rs.fields(fldno).Value
					Else
						'grid1.TextMatrix(grid1.Rows - 1, fldno + 2) = Fld
						grid1.TextMatrix(grid1.Rows - 1, fldno + 1) = Fld
					End If
					'rs.fields(fldno).Value = grid1.TextMatrix(grid1.Rows - 1, fldno + 2)
					rs.fields(fldno).Value = grid1.TextMatrix(grid1.Rows - 1, fldno + 1)
				Next
				rs.Update
			}//end while*/
		out:
			m_GRID1.SetCol(Col);
			m_GRID1.SetRow(Row);
			fclose(fp);
			m_Entrance=1;
		}//end if
	}//end if
}




void CStationsTableView::OnDataBaseSortAZ() 
{
	CString tt;
	VARIANT Colindex;
	Colindex.iVal=m_GRID1.GetSelStartCol();
	Colindex.vt=VT_I2;
	
//	tt = _T("Select * from STtable ORDER BY [") + m_GRID1.GetColumns().GetItem(Colindex).GetCaption() + _T("]");
	tt.Format( _T("Select * from %s ORDER BY [%s]") ,  ((CSMS4DCApp *)AfxGetApp())->Query_STtable  , m_GRID1.GetColumns().GetItem(Colindex).GetCaption() );

	//m_GRID1.GetTextMatrix(1,ColIndex);
	//MessageBox(tt,"");

	m_ADO1.SetRecordSource(tt);

	m_ADO1.Refresh();
	m_GRID1.Refresh();

}

void CStationsTableView::OnDataBaseSortZA() 
{
	
	CString tt;
	VARIANT Colindex;
	Colindex.iVal=m_GRID1.GetSelStartCol();
	Colindex.vt=VT_I2;
	
//	tt = _T("Select * from STtable ORDER BY [") + m_GRID1.GetColumns().GetItem(Colindex).GetCaption() + _T("] DESC");
	tt.Format( _T("Select * from %s ORDER BY [%s] DESC") ,  ((CSMS4DCApp *)AfxGetApp())->Query_STtable  , m_GRID1.GetColumns().GetItem(Colindex).GetCaption() );

	//m_GRID1.GetTextMatrix(1,ColIndex);
	//MessageBox(tt,"");

	m_ADO1.SetRecordSource(tt);

	m_ADO1.Refresh();
	m_GRID1.Refresh();
		
}

/*
void CStationsTableView::OnDestroy() 
{
	CFormView::OnDestroy();
	GetParentFrame()->ShowControlBar(&((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar1,
	(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar1.GetStyle()&~WS_VISIBLE)==0,false);
}
void CStationsTableView::OnKillFocus(CWnd* pNewWnd) 
{
	CFormView::OnKillFocus(pNewWnd);
	
	GetParentFrame()->ShowControlBar(&((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar1,
	(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar1.GetStyle()&~WS_VISIBLE)==0,false);
}
void CStationsTableView::OnSetFocus(CWnd* pNewWnd) 
{
	CFormView::OnSetFocus(pNewWnd);
	
	GetParentFrame()->ShowControlBar(&((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar1,
	(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar1.GetStyle()&WS_VISIBLE)==0,false);
}
*/


/////////////////////////////////////////////////////////////////////////////
// CStationsTableView printing

BOOL CStationsTableView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CStationsTableView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CStationsTableView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CStationsTableView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
}
void CStationsTableView::OnFilePrintPreview() 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	CFormView::OnFilePrintPreview();
}
void CStationsTableView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CFormView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}


void CStationsTableView::OnAsAntenna() 
{
	char strFilter[] = { "Ant Files (*.ant)|*.ant|All Files (*.*)|*.*||"};
	CFileDialog FileDLG(TRUE, ".ant", NULL, 0, strFilter);

	if (FileDLG.DoModal() == IDOK)
	{
		CString	antfile = FileDLG.GetPathName();

		FILE *fid;
		fid=fopen(antfile,"rt");
		char Name [20],
			 Gain_dBi [20],
			 BeamWidth_H [20],
			 BeamWidth_V [20],
			 Frq_Lo [20],
			 Frq_Hi [20],
			 Frq_unit [20],
			 Polarization [20],
			 dum[20];
		fscanf( fid, "%s %s", dum,Name);
		fscanf( fid, "%s %s", dum,Gain_dBi);
		fscanf( fid, "%s %s", dum,BeamWidth_H);
		fscanf( fid, "%s %s", dum,BeamWidth_V);
		fscanf( fid, "%s %s", dum,Frq_Lo);
		fscanf( fid, "%s %s", dum,Frq_Hi);
		fscanf( fid, "%s %s", dum,Frq_unit);
		fscanf( fid, "%s %s", dum,Polarization);
		fscanf( fid, "%s", dum);
		fclose(fid);
	
		m_GRID1.SetCol(9);		m_GRID1.SetText(Gain_dBi);
		m_GRID1.SetCol(10);		m_GRID1.SetText(BeamWidth_H);
		m_GRID1.SetCol(11);		m_GRID1.SetText(BeamWidth_V);
		m_GRID1.SetCol(12);		m_GRID1.SetText(Polarization);
		m_GRID1.SetCol(13);		m_GRID1.SetText(Name);
	}			
}

void CStationsTableView::OnShowPattern() 
{
	m_GRID1.SetEditActive(false);
	m_GRID1.SetCol(13);
	CString Name = m_GRID1.GetText();

	CString antfile;
	antfile.Format("%sAntenna\\ant_%s.ant",((CSMS4DCApp *)AfxGetApp())->m_AppPath ,Name);

	CANTpatternDLG patdlg;
	patdlg.m_antfile = antfile;
	patdlg.DoModal();
}

void CStationsTableView::OnBUTTONTx() 
{
	TxRxFilters(1) ;
}

void CStationsTableView::OnBUTTONRx() 
{
	TxRxFilters(0) ;
}

void CStationsTableView::TxRxFilters(BOOL TxRx) 
{
	m_GRID1.SetEditActive(false);
	m_GRID1.SetCol(0);
	CString ID1 = m_GRID1.GetText();
	long ID = atol(ID1);

//	CString  m_DB = _T("ODBC;DSN=WorkDB;");
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	CDatabase m_mydb;
	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		CRecordset m_rs;
		CString m_Tbl;
		if(TxRx==1)
			m_Tbl.Format("SELECT * FROM TxFilters WHERE (((EqID)=%ld)) ORDER BY EqID;",ID);
		else
			m_Tbl.Format("SELECT * FROM RxFilters WHERE (((EqID)=%ld)) ORDER BY EqID;",ID);

		m_rs.m_pDatabase=&m_mydb;
		m_rs.Open( CRecordset::snapshot, m_Tbl);

		if(m_rs.GetRecordCount()==1)
		{
			double ft[20], at[20];
			CString PS;
			m_rs.MoveFirst();
			int i=0;
			while(!m_rs.IsEOF())
			{
				m_rs.GetFieldValue((short)1, PS);	ft[i] = atof(PS);
				m_rs.GetFieldValue((short)2, PS);	at[i] = atof(PS);
				m_rs.MoveNext();
				i++;
			}
			m_rs.Close();
			m_mydb.Close();

			CTxRxFilterDLG	xx;
			xx.m_TxRx = TxRx;
			if(TxRx==1)
				xx.m_title = "Transmitter spectrum mask";
			else
				xx.m_title = "Receiver selectivity mask";
			xx.m_ID = ID;
			for(int j=0;j<i;j++)
			{
				xx.m_f[j] = ft[j];
				xx.m_a[j] = at[j];
			}
			xx.DoModal();

		}	//end if recordset
		else
		{
			if(TxRx==1)
				MessageBox("\nNo Tx Filter defined for this station.\t\t\n","Warning!!!",MB_ICONWARNING);
			else
				MessageBox("\nNo Rx Filter defined for this station.\t\t\n","Warning!!!",MB_ICONWARNING);

			CTxRxFilterDLG	xx;
			xx.m_TxRx = TxRx;
			if(TxRx==1)
				xx.m_title = "Transmitter spectrum mask";
			else
				xx.m_title = "Receiver selectivity mask";
			xx.m_ID = ID;
			double Channelsep = xx.m_Channelsep;
		//	for(int j=0;j<20;j++)
			{
				xx.m_f[0]  = -28;	xx.m_a[0]  = 41;
				xx.m_f[1]  = -22;	xx.m_a[1]  = 40;
				xx.m_f[2]  = -20;	xx.m_a[2]  = 26.7;
				xx.m_f[3]  = -14;	xx.m_a[3]  = 17.8;
				xx.m_f[4]  = -12;	xx.m_a[4]  = 17.8;
				xx.m_f[5]  =  -8;	xx.m_a[5]  =  0;
				xx.m_f[6]  =   0;	xx.m_a[6]  =  0;
				xx.m_f[7]  =   8;	xx.m_a[7]  =  0;
				xx.m_f[8]  =  12;	xx.m_a[8]  = 17.8;
				xx.m_f[9]  =  14;	xx.m_a[9]  = 17.8;
				xx.m_f[10] =  20;	xx.m_a[10] = 26.7;
				xx.m_f[11] =  22;	xx.m_a[11] = 40;
				xx.m_f[12] =  28;	xx.m_a[12] = 41;

			}
			xx.DoModal();
		}

	}	//end if database
}

