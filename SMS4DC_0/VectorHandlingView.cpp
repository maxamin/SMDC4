// VectorHandlingView.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "VectorHandlingView.h"
#include "VectorDLG.h"
#include "VectorHandlingDoc.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingView

IMPLEMENT_DYNCREATE(CVectorHandlingView, CFormView)

CVectorHandlingView::CVectorHandlingView()
	: CFormView(CVectorHandlingView::IDD), m_pView((CSMS4DCView *)(((CSMS4DCApp *)AfxGetApp())->m_pView))
{
	//{{AFX_DATA_INIT(CVectorHandlingView)
	//}}AFX_DATA_INIT
	m_pToolTip = NULL;
}

CVectorHandlingView::~CVectorHandlingView()
{
	delete m_pToolTip;
	m_pView = NULL;
}

void CVectorHandlingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVectorHandlingView)
	DDX_Control(pDX, IDC_BUTTON_Exportg, m_BUTTON_Exportg);
	DDX_Control(pDX, IDC_BUTTON_Export, m_BUTTON_Export);
	DDX_Control(pDX, IDC_BUTTON_Edit, m_BUTTON_Edit);
	DDX_Control(pDX, IDC_BUTTON_Delete, m_BUTTON_Delete);
	DDX_Control(pDX, IDC_BUTTON_Load, m_BUTTON_Load);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_LIST1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVectorHandlingView, CFormView)
	//{{AFX_MSG_MAP(CVectorHandlingView)
	ON_BN_CLICKED(IDC_BUTTON_Load, OnBUTTONLoad)
	ON_BN_CLICKED(IDC_BUTTON_Export, OnBUTTONExport)
	ON_BN_CLICKED(IDC_BUTTON_Delete, OnBUTTONDelete)
	ON_BN_CLICKED(IDC_BUTTON_Exportg, OnBUTTONExportg)
	ON_BN_CLICKED(IDC_BUTTON_Edit, OnBUTTONEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingView diagnostics

#ifdef _DEBUG
void CVectorHandlingView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVectorHandlingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingView message handlers


void CVectorHandlingView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_BUTTON_Load.LoadBitmaps(IDB_Load1,IDB_Load2);
	m_BUTTON_Export.LoadBitmaps(IDB_Save1,IDB_Save2,IDB_Save1,IDB_Save3);
	m_BUTTON_Delete.LoadBitmaps(IDB_Delete1,IDB_Delete2,IDB_Delete1,IDB_Delete3);
	m_BUTTON_Edit.LoadBitmaps(IDB_Edit1,IDB_Edit2,IDB_Edit1,IDB_Edit3);

	m_pToolTip = new CToolTipCtrl;
	m_pToolTip->Create(this);
	m_pToolTip->AddTool(&m_BUTTON_Load,_Z("Load Vector"));
	m_pToolTip->AddTool(&m_BUTTON_Export,_Z("Export Vector"));
	m_pToolTip->AddTool(&m_BUTTON_Delete,_Z("Delete Vector"));
	m_pToolTip->AddTool(&m_BUTTON_Edit,_Z("Edit Properties"));
	m_pToolTip->AddTool(&m_BUTTON_Exportg,_Z("Export/Display Vector in Google Earth Format"));
	m_pToolTip->Activate(TRUE);

	int nCOLS = 1;
	m_LIST1.SetCols(nCOLS);
	m_LIST1.SetRow(0);
	m_LIST1.SetColWidth(0,4*5000);
	m_LIST1.SetColAlignment(0,0);

	FillList();
//	if(m_Rows>1)	m_LIST1.SetRow(1);

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE44);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog((CDialog *)this);
}

void CVectorHandlingView::FillList() 
{
	m_Rows = 1 + m_pView->m_POLYnum;
	m_LIST1.SetRows(m_Rows);
	for(int i=0;i<m_Rows-1;i++)
	{
		m_LIST1.SetRow(i+1);
		CString str = m_pView->m_POLY[i].FileNameVec;
		str.Replace(_T(".txt"),_T(""));
		m_LIST1.SetText(str);
	}
	ActiveButton();
}

void CVectorHandlingView::OnBUTTONEdit() 
{
	UpdateData();
	int POS = m_LIST1.GetRow() - 1;
	if(POS>-1)
	{
		CVectorDLG Vdlg;
		Vdlg.m_TitleName = m_pView->m_POLY[POS].FileNameVec;
		Vdlg.m_LineWidth = m_pView->m_POLY[POS].nWidthVec;
		Vdlg.m_LineStyle0 = m_pView->m_POLY[POS].nStyleVec;
		Vdlg.m_FillTransparancy = m_pView->m_POLY[POS].alphaVec;
		Vdlg.m_LineColorRed = GetRValue(m_pView->m_POLY[POS].crColorVec);
		Vdlg.m_LineColorGreen = GetGValue(m_pView->m_POLY[POS].crColorVec);
		Vdlg.m_LineColorBlue = GetBValue(m_pView->m_POLY[POS].crColorVec);
		Vdlg.m_FillColorRed = GetRValue(m_pView->m_POLY[POS].flColorVec);
		Vdlg.m_FillColorGreen = GetGValue(m_pView->m_POLY[POS].flColorVec);
		Vdlg.m_FillColorBlue = GetBValue(m_pView->m_POLY[POS].flColorVec);
		Vdlg.m_FillMode = m_pView->m_POLY[POS].nModeVec;
		if (Vdlg.DoModal()== IDOK)
		{
			COLORREF crColor = RGB(Vdlg.m_LineColorRed,Vdlg.m_LineColorGreen,Vdlg.m_LineColorBlue);
			COLORREF flColor = RGB(Vdlg.m_FillColorRed,Vdlg.m_FillColorGreen,Vdlg.m_FillColorBlue);
			m_pView->m_POLY[POS].nWidthVec = Vdlg.m_LineWidth;
			m_pView->m_POLY[POS].crColorVec = crColor;
			m_pView->m_POLY[POS].nStyleVec = Vdlg.m_LineStyle0;
			if((m_pView->m_POLY[POS].nModeVec) != 2)
				m_pView->m_POLY[POS].nModeVec = Vdlg.m_FillMode;
			m_pView->m_POLY[POS].flColorVec = flColor;
			m_pView->m_POLY[POS].alphaVec = Vdlg.m_FillTransparancy;
	//		m_pView->OnRefresh1();
			m_pView->OnRefresh2();
		}
	}
	UpdateData(false);
}

void CVectorHandlingView::OnDraw(CDC* pDC) 
{
	int w = 25 , h = 22;
	CRect rect , rect1;
	GetClientRect(rect);
	rect.bottom = rect.bottom-h;
	m_LIST1.MoveWindow(rect);

	CButton *x1 =  (CButton *)GetDlgItem(IDC_BUTTON_Load);
	x1->GetWindowRect(rect1);
	rect1.top = rect.bottom;
	rect1.bottom = rect.bottom + h;
	rect1.left = rect.left + 0*(w);
	rect1.right = rect1.left + w;
	x1->MoveWindow(rect1);

	x1 =  (CButton *)GetDlgItem(IDC_BUTTON_Export);
	x1->GetWindowRect(rect1);
	rect1.top = rect.bottom;
	rect1.bottom = rect.bottom + h;
	rect1.left = rect.left  + 1*(w);
	rect1.right = rect1.left + w;
	x1->MoveWindow(rect1);

	x1 =  (CButton *)GetDlgItem(IDC_BUTTON_Edit);
	x1->GetWindowRect(rect1);
	rect1.top = rect.bottom;
	rect1.bottom = rect.bottom + h;
	rect1.left = rect.left + 2*(w);
	rect1.right = rect1.left + w;
	x1->MoveWindow(rect1);	

	x1 =  (CButton *)GetDlgItem(IDC_BUTTON_Delete);
	x1->GetWindowRect(rect1);
	rect1.top = rect.bottom;
	rect1.bottom = rect.bottom + h;
	rect1.left = rect.left + 3*(w);
	rect1.right = rect1.left + w;
	x1->MoveWindow(rect1);	

	x1 =  (CButton *)GetDlgItem(IDC_BUTTON_Exportg);
	x1->GetWindowRect(rect1);
	rect1.top = rect.bottom;
	rect1.bottom = rect.bottom + h;
//	rect1.left = rect.right - 6*(w);
	rect1.left = rect.right - 7*(w);
	rect1.right = rect.right ;
	x1->MoveWindow(rect1);	

}

void CVectorHandlingView::OnBUTTONLoad() 
{
	m_pView->OnDrawVector1();
}

void CVectorHandlingView::OnBUTTONDelete() 
{
	UpdateData();
	int POS = m_LIST1.GetRow() - 1;
	if(POS>-1)
	{
		int N = m_pView->m_POLYnum;

//		CString str = m_pView->m_POLY[POS].FileNameVec;
//		if((str.CollateNoCase(_T("Circle.txt")))==0)
//			m_pView->m_CircleDraw = FALSE;

		for(int i = POS ; i<N ; i++)	m_pView->m_POLY[i] = m_pView->m_POLY[i+1];
		m_pView->m_POLYnum = N - 1;

		FillList();
//		m_pView->OnRefresh1();
		m_pView->OnRefresh2();
	}
	UpdateData(false);
}

void CVectorHandlingView::PostNcDestroy() 
{
	m_pView->m_pDocVectors = NULL;
	(((CSMS4DCApp *)AfxGetApp())->m_pView) = NULL;
	CFormView::PostNcDestroy();
}

void CVectorHandlingView::OnBUTTONExport() 
{
	UpdateData();
	int POS = m_LIST1.GetRow() - 1;
	if(POS>-1)
	{
		CString Fpath1 = m_pView->m_POLY[POS].PathNameVec;
		CString FpathDes =  Fpath1;
		int L = FpathDes.GetLength();
		FpathDes.Delete(L-4,4);
		FpathDes = FpathDes + _T("_COPY.txt");

//		char strFilter[] = { "SMS4DC Vectors (*.txt)|*.txt||"};
		CString strFilter = _Z("SMS4DC Vectors") + " (*.txt)|*.txt||";
		CFileDialog FileDLG(FALSE, NULL, FpathDes, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , strFilter);
		if (((CSMS4DCApp *)AfxGetApp())->IsWin2000())	FileDLG.m_ofn.lStructSize = 88;		//76
		if (FileDLG.DoModal() == IDOK)
		{
			FpathDes = FileDLG.GetPathName();
			BOOL s = CopyFile(Fpath1,FpathDes,FALSE);
			if(s==0)
			{
				CString str;
				str.Format(_Z("The DataBase [%s] can not be copied."),Fpath1);
				MessageBox(str,_Z("Error!!!"),MB_ICONERROR | MB_OK);
			}
		}
	}
	UpdateData(false);
}


extern "C" int WINAPI GoogleFile(CString mLang, CString InputPath = _T(""));	//GoogleFileDLL.lib
void CVectorHandlingView::OnBUTTONExportg() 
{
	UpdateData();
	int POS = m_LIST1.GetRow() - 1;
	if(POS>-1)
	{
		CString Fpath1 = m_pView->m_POLY[POS].PathNameVec;
		GoogleFile(((CSMS4DCApp *)AfxGetApp())->m_Lang , Fpath1);
	}
	UpdateData(false);
}

BOOL CVectorHandlingView::PreTranslateMessage(MSG* pMsg) 
{
	if (NULL != m_pToolTip)
            m_pToolTip->RelayEvent(pMsg);
	
	return CFormView::PreTranslateMessage(pMsg);
}


void CVectorHandlingView::ActiveButton() 
{
	if(m_Rows>1)
	{
		m_BUTTON_Export.EnableWindow(TRUE);
		m_BUTTON_Delete.EnableWindow(TRUE);
		m_BUTTON_Edit.EnableWindow(TRUE);
		m_BUTTON_Exportg.EnableWindow(TRUE);
	}
	else
	{
		m_BUTTON_Export.EnableWindow(FALSE);
		m_BUTTON_Delete.EnableWindow(FALSE);
		m_BUTTON_Edit.EnableWindow(FALSE);
		m_BUTTON_Exportg.EnableWindow(FALSE);
	}
}

BEGIN_EVENTSINK_MAP(CVectorHandlingView, CFormView)
    //{{AFX_EVENTSINK_MAP(CVectorHandlingView)
	ON_EVENT(CVectorHandlingView, IDC_MSFLEXGRID1, -601 /* DblClick */, OnDblClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CVectorHandlingView::OnDblClickMsflexgrid1() 
{
	UpdateData();
	int POS = m_LIST1.GetRow() - 1;
	if(POS>-1)
	{
		CString Fpath1 = m_pView->m_POLY[POS].PathNameVec;
		m_pView->VectorDesktop(Fpath1);
	}
	UpdateData(false);
}
