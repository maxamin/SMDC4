// SRVtableView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "SRVtableView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSRVtableView

IMPLEMENT_DYNCREATE(CSRVtableView, CRecordView)

CSRVtableView::CSRVtableView()
	: CRecordView(CSRVtableView::IDD)
{
	//{{AFX_DATA_INIT(CSRVtableView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarSRVtable), TRUE, FALSE);
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarALLplan), FALSE, FALSE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(2, "");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(3, "");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(4, "");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(5, "");
}

CSRVtableView::~CSRVtableView()
{
	if (m_pSet)
		delete m_pSet;
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarSRVtable), FALSE, FALSE);
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarALLplan), TRUE, FALSE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, "");
}

void CSRVtableView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSRVtableView)
	DDX_FieldText(pDX, IDC_EDIT_Blue, m_pSet->m_SRV_B, m_pSet);
	DDV_MinMaxLong(pDX, m_pSet->m_SRV_B, 0, 255);
	DDX_FieldText(pDX, IDC_EDIT_code, m_pSet->m_SRV_CODE, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_Green, m_pSet->m_SRV_G, m_pSet);
	DDV_MinMaxLong(pDX, m_pSet->m_SRV_G, 0, 255);
	DDX_FieldText(pDX, IDC_EDIT_ID, m_pSet->m_ID, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_Pname, m_pSet->m_SRV_NAME_P_en, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_Red, m_pSet->m_SRV_R, m_pSet);
	DDV_MinMaxLong(pDX, m_pSet->m_SRV_R, 0, 255);
	DDX_FieldText(pDX, IDC_EDIT_Sname, m_pSet->m_SRV_NAME_S_en, m_pSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSRVtableView, CRecordView)
	//{{AFX_MSG_MAP(CSRVtableView)
	ON_COMMAND(ID_RECORD_FIRST, OnRecordFirst)
	ON_COMMAND(ID_RECORD_PREV, OnRecordPrev)
	ON_COMMAND(ID_RECORD_NEXT, OnRecordNext)
	ON_COMMAND(ID_RECORD_LAST, OnRecordLast)
	ON_COMMAND(ID_RECORD_ADD, OnRecordAdd)
	ON_COMMAND(ID_RECORD_SUB, OnRecordSub)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDIT_Red, OnChangeEDITRed)
	ON_EN_CHANGE(IDC_EDIT_Blue, OnChangeEDITBlue)
	ON_EN_CHANGE(IDC_EDIT_Green, OnChangeEDITGreen)
	ON_COMMAND(ID_RECORD_SAVE, OnRecordSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRVtableView diagnostics

#ifdef _DEBUG
void CSRVtableView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CSRVtableView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSRVtableView message handlers

CRecordset* CSRVtableView::OnGetRecordset()
{
	if (m_pSet != NULL)
		return m_pSet;

	m_pSet = new CSRVtableSet(NULL);
	m_pSet->Open();

	return m_pSet;
}

CSRVtableSet* CSRVtableView::GetRecordset()
{
	CSRVtableSet* pData = (CSRVtableSet*) OnGetRecordset();
	ASSERT(pData == NULL || pData->IsKindOf(RUNTIME_CLASS(CSRVtableSet)));
	return pData;
}

void CSRVtableView::OnInitialUpdate()
{
	BeginWaitCursor();
	GetRecordset();
	CRecordView::OnInitialUpdate();
	if (m_pSet->IsOpen())
	{
		CString strTitle = m_pSet->m_pDatabase->GetDatabaseName();
		CString strTable = m_pSet->GetTableName();		strTable.TrimRight();
		if (!strTable.IsEmpty())
			strTitle += _T(" : ") + _Z(strTable);
		GetDocument()->SetTitle(strTitle);
	}

	m_count=0;
	while (!m_pSet->IsEOF())
	{
		m_count=m_count+1;
		m_pSet->MoveNext();
	}
	m_pSet->MoveFirst();

	CString str;
	m_num=1;
	str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

	m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);

	EndWaitCursor();
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE35);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog((CDialog *)this);
}

void CSRVtableView::OnRecordFirst() 
{
	if(!m_pSet->IsBOF())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		UpdateData();	
		m_pSet->MoveFirst();

		int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;
		CRect rect1(x1,y1,x2,y2);
		m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
		InvalidateRect(rect1,true);

		CString str;
		m_num=1;
		str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

		UpdateData(FALSE);
	}
}

void CSRVtableView::OnRecordPrev() 
{
	if(!m_pSet->IsBOF())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		UpdateData();	
		m_pSet->MovePrev();

		int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;
		CRect rect1(x1,y1,x2,y2);
		m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
		InvalidateRect(rect1,true);

		CString str;
		m_num=m_num-1;
		str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

		UpdateData(FALSE);
	}		
}

void CSRVtableView::OnRecordNext() 
{
	if(!m_pSet->IsEOF())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		UpdateData();	
		m_pSet->MoveNext();

		int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;
		CRect rect1(x1,y1,x2,y2);
		m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
		InvalidateRect(rect1,true);

		CString str;
		m_num=min(m_num+1,m_count);
		str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

		UpdateData(FALSE);
	}	
}

void CSRVtableView::OnRecordLast() 
{
	if(!m_pSet->IsEOF())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		UpdateData();	
		m_pSet->MoveLast();

		int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;
		CRect rect1(x1,y1,x2,y2);
		m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
		InvalidateRect(rect1,true);

		CString str;
		m_num=m_count;
		str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

		UpdateData(FALSE);
	}	
}

void CSRVtableView::OnUpdateRecordNext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_num<m_count);
}
void CSRVtableView::OnUpdateRecordLast(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_num<m_count);
}

void CSRVtableView::OnRecordAdd() 
{
	OnAppend();

	int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;
	CRect rect1(x1,y1,x2,y2);
	m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
	InvalidateRect(rect1,true);
}

void CSRVtableView::OnRecordSub() 
{
	OnDelete() ;

	int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;
	CRect rect1(x1,y1,x2,y2);
	m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
	InvalidateRect(rect1,true);
}


void CSRVtableView::OnAppend() 
{
	if(m_pSet->CanUpdate() && !m_pSet->IsDeleted())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();
	}

	int ID=0;
	m_pSet->MoveFirst();
	while (!m_pSet->IsEOF())
	{
		ID = max(ID,m_pSet->m_ID);
		m_pSet->MoveNext();
	}

	m_pSet->MoveLast();
	m_pSet->AddNew();

	m_pSet->m_SRV_CODE = "0";
	m_pSet->m_SRV_R = 0;
	m_pSet->m_SRV_G = 0;
	m_pSet->m_SRV_B = 0;
	m_pSet->m_ID=ID+1;

	m_count = m_count+1;
	m_num = m_count;
	CString str;
	str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

	m_pSet->Update();
//	m_pSet->Requery();
	m_pSet->MoveLast();

	UpdateData(FALSE);
}


void CSRVtableView::OnDelete() 
{
	m_pSet->Delete();

	m_count = max(m_count-1,1);

	if(!m_pSet->IsEOF() && !m_pSet->IsBOF())
		m_pSet->MoveNext();
	if(m_pSet->IsEOF())
	{
		m_pSet->MovePrev();
		m_num = m_count;
	}
	if(m_pSet->IsBOF())
		m_pSet->MoveNext();

	CString str;
	str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

	UpdateData(FALSE);	
}

void CSRVtableView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;

	CPen pen1(PS_SOLID,1,RGB(255,255,255));
	dc.SelectObject(&pen1);
	dc.MoveTo(x1-1,y2+1);  dc.LineTo(x1-1,y1-1);  dc.LineTo(x2+1,y1-1);

	CPen pen2(PS_SOLID,1,RGB(128,128,128));
	dc.SelectObject(&pen2);
	dc.MoveTo(x2+1,y1);	dc.LineTo(x2+1,y2+1);  dc.LineTo(x1,y2+1);

	CPen pen3(PS_SOLID,1,RGB(64,64,64));
	dc.SelectObject(&pen3);
	dc.MoveTo(x2+2,y1-1);	dc.LineTo(x2+2,y2+2);  dc.LineTo(x1-1,y2+2);

	CRect rect1(x1,y1,x2,y2);
	CBrush brush1(m_color1);
	dc.SelectObject(&brush1);
	dc.FillRect(&rect1,&brush1);
}

void CSRVtableView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;

	if ((point.x>=x1) && (point.x<=x2) && (point.y>=y1) && (point.y<=y2) )
		OnColor2();
	
	CRecordView::OnLButtonDown(nFlags, point);
}


void CSRVtableView::OnColor2() 
{
	CColorDialog xx(m_color1, CC_FULLOPEN);
	m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
	if	(xx.DoModal()==IDOK)
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		COLORREF ZZ = xx.GetColor();
		m_pSet->m_SRV_R = GetRValue(ZZ);
		m_pSet->m_SRV_G = GetGValue(ZZ);
		m_pSet->m_SRV_B = GetBValue(ZZ);
		m_color1 = ZZ;

		int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;
		CRect rect1(x1,y1,x2,y2);
		m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
		InvalidateRect(rect1,true);

		UpdateData(false);
	}
}

void CSRVtableView::OnChangeEDITRed() 
{
	m_pSet->Edit();
	if(!UpdateData()) return;
	m_pSet->Update();

	int x1=85 + 220,y1=63 + 67,    x2=x1+20,y2=y1+20;
	CRect rect1(x1,y1,x2,y2);
	m_color1 = RGB(m_pSet->m_SRV_R,m_pSet->m_SRV_G,m_pSet->m_SRV_B);
	InvalidateRect(rect1,true);
	
	UpdateData(false);
}
void CSRVtableView::OnChangeEDITBlue() 
{
	OnChangeEDITRed();	
}
void CSRVtableView::OnChangeEDITGreen() 
{
	OnChangeEDITRed();	
}

void CSRVtableView::OnRecordSave() 
{
	m_pSet->Edit();
	if(!UpdateData()) return;
	m_pSet->Update();

	UpdateData(FALSE);		
}
