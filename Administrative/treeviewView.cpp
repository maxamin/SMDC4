// treeviewView.cpp : implementation of the CTreeviewView class
//

#include <afxdb.h>
#include "stdafx.h"
#include "ChildFrm.h"
#include "Administrative.h"
#include "Font.h"
#include "LeftView.h"
#include "CatSelect.h"
#include "treeviewDoc.h"
#include "treeviewView.h"
#include "Receivers.h"
#include  <math.h>
extern "C" {
#include "idwm32.h"
}
//#include "AuditTrail.h"
#include "Test6.h"
#include "GrpDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTreeviewView
extern "C" char * WINAPI Code2NameCTY_lang(CString co, CString mLang);	//CNT.lib
extern "C" char * WINAPI AllCodes_lang(CString CTYCOD[], int *NOCTY);	//CNT.lib

IMPLEMENT_DYNCREATE(CTreeviewView, CFormView)

BEGIN_MESSAGE_MAP(CTreeviewView, CFormView)
	//{{AFX_MSG_MAP(CTreeviewView)
	ON_WM_SIZE()
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_CBN_KILLFOCUS(IDC_COMBO2, OnKillfocusCombo2)
	ON_CBN_KILLFOCUS(IDC_COMBO3, OnKillfocusCombo3)
	ON_CBN_KILLFOCUS(IDC_COMBO4, OnKillfocusCombo4)
	ON_CBN_KILLFOCUS(IDC_COMBO5, OnKillfocusCombo5)
	ON_CBN_KILLFOCUS(IDC_COMBO6, OnKillfocusCombo6)
	ON_NOTIFY(NM_KILLFOCUS, IDC_DATEPICKER, OnKillfocusDatepicker)
	ON_NOTIFY(NM_KILLFOCUS, IDC_TIMEPICKER, OnKillfocusTimepicker)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeviewView construction/destruction

CTreeviewView::CTreeviewView(): CFormView(CTreeviewView::IDD)
{
	// TODO: add construction code here
	
	m_RecID=0;
	m_Table=_T("");
	m_Refresh=false;
	m_loaded=false;
	m_ReadOnly=true;
	m_OnEdit=false;
	m_CatID=-1;
}

CTreeviewView::~CTreeviewView()
{
}

BOOL CTreeviewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL ans=CFormView::PreCreateWindow(cs);
	return ans;

}

/////////////////////////////////////////////////////////////////////////////
// CTreeviewView drawing

void CTreeviewView::OnDraw(CDC* pDC)
{
	CTreeviewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

//	m_EditBox=(CMSMask *)GetDlgItem(IDC_EDITBOX);
	if(m_Refresh)
	{
		m_Refresh=false;
		m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
		m_Grid->ShowWindow(SW_SHOW);
		((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
		if(m_ReadOnly==false)
			m_Grid->SetBackColorBand(0,0xFFFFFF);
		else
			m_Grid->SetBackColorBand(0,0xDFDFDF);
		GetDlgItem(IDC_SAVE_BUTTON)->ShowWindow(SW_SHOW);
		((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->SetWindowText(_Z("Modify"));
		GetDlgItem(IDC_EDIT_BUTTON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CANCEL_BUTTON)->ShowWindow(SW_SHOW);
		((CButton *)GetDlgItem(IDC_ANTENNA))->ShowWindow(SW_HIDE);

		if(m_Table!="")
		{
			for(int i=0;i<m_Grid->GetRows();i++)
				m_Grid->SetRowData(i,0);
			if(m_Action==1)
			{
				if(m_Table==_T("Owner")) AddOwner();
				if(m_Table==_T("License")) AddLicense();
				if(m_Table==_T("Station")) AddStation();
				if(m_Table==_T("BCStation")) AddBCStation();
				if(m_Table==_T("Mobiles")) AddMobile();
				if(m_Table==_T("Equipment")) AddEquipment();
				if(m_Table==_T("Antenna")) AddAntenna();
				if(m_Table==_T("Frequency")) AddFrequency();
				if(m_Table==_T("Earth")) AddESStation();
				if(m_Table==_T("Eant"))  AddESAnt(m_RecordType);
				if(m_Table==_T("grp")) AddESGroup();
				if(m_Table==_T("Allotment")) AddAllotment();
				if(m_Table==_T("Contour")) AddContour();
/*				if(m_Table=="Invoice") AddInvoice();
				if(m_Table=="Payment") AddPayment();
				if(m_Table=="Link") AddReceiver();*/
			}
			else
			{
				if(m_Table==_T("Active")) CleanScreen(); //LoadUnpaid();
				if(m_Table==_T("Owner")) LoadOwner(m_RecID);
				if(m_Table==_T("License")) LoadLicense(m_RecID);
				if(m_Table==_T("Station")) LoadStation(m_RecID);
				if(m_Table==_T("BCStation")) LoadBC(m_RecID);
				if(m_Table==_T("Mobiles")) LoadMobile(m_RecID);
				if(m_Table==_T("Equipment")) LoadEquipment(m_RecID);
				if(m_Table==_T("Antenna")) LoadAntenna(m_RecID);
				if(m_Table==_T("Frequency")) LoadFrequency(m_RecID);
				if(m_Table==_T("Invoice")) LoadInvoice(m_RecID);
				if(m_Table==_T("Payment")) LoadPayment(m_RecID);
				if(m_Table==_T("Link")) LoadReceiver(m_RecID);
				if(m_Table==_T("Earth")) LoadES(m_RecID);
				if(m_Table==_T("Eant")) LoadESAnt(m_RecID);
				if(m_Table==_T("grp")) LoadESGroup(m_RecID);
				if(m_Table==_T("Allotment")) LoadAllot(m_RecID);
				if(m_Table==_T("Contour")) LoadContour(m_RecID);
			}
		}
		else
			CleanScreen();
	}
}

void CTreeviewView::CleanScreen()
{
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	if(m_Grid)
		m_Grid->ShowWindow(SW_HIDE);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText("");
	GetDlgItem(IDC_SAVE_BUTTON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BUTTON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CANCEL_BUTTON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ATTACH)->ShowWindow(SW_HIDE);
}

void CTreeviewView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_UserName=((CSMS4DCApp *)AfxGetApp())->m_UserName;
	m_UserLevel=((CSMS4DCApp *)AfxGetApp())->m_UserLevel;
	m_Lang=((CSMS4DCApp *)AfxGetApp())->m_Lang;
	m_CDBSTR=((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	CString Title_En  = "Administrative data";			//<<<<---------
	CString Title_Num = GetDocument()->GetTitle();		//<<<<---------
		Title_Num.Replace(Title_En,"");			//<<<<---------
	if(m_Lang=="Fr")
		GetDocument()->SetTitle(_Z(Title_En) + Title_Num); 	//<<<<---------

	// Create an icon button.

	//((CBitmapButton *)GetDlgItem(IDC_SAVE_BUTTON))->LoadBitmaps(IDB_BITMAP1, 0,0,0);

	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_EditBox=(CMSMask *)GetDlgItem(IDC_EDITBOX);
	m_EditBox->SetPromptInclude(false);
	m_EditBox->SetPromptChar(" ");
	m_Grid->SetFixedRows(1);
	m_Grid->SetFixedCols(1);
	m_Grid->SetRowHeightMin(300);
	m_loaded=true;
     m_Grid->SetRow(0);
     m_Grid->SetCol(0);
     // To convert grid rect from twips to DC units you need
     // pixels per inch.
     CDC* pDC = m_Grid->GetDC();
     m_nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
     m_nLogY = pDC->GetDeviceCaps(LOGPIXELSY);
     ReleaseDC(pDC);
	CRect Rect;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->GetWindowRect(&Rect);
	ScreenToClient(&Rect);
     m_lBorderWidth = m_Grid->GetCellLeft();
     m_lBorderHeight =m_Grid->GetCellTop() - 660;

	RECT rcl;

    // Get the client area of the parent window.
    GetClientRect(&rcl);
	m_Grid->SetWindowPos(NULL,0,Rect.bottom,rcl.right,rcl.bottom,SWP_NOZORDER);
	CFont *pTempFont;
	LOGFONT lf;
	pTempFont=((CStatic *)GetDlgItem(IDC_GRID_TITLE))->GetFont();
	pTempFont->GetLogFont(&lf);
	lf.lfWeight=800;
	lf.lfHeight=20;
	lf.lfWidth=10;
	lf.lfItalic=true;
	strcpy(lf.lfFaceName, _T("Times"));
	pTempFont->Detach();
	pTempFont->CreateFontIndirect(&lf);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetFont(pTempFont);
	pTempFont->Detach();
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowPos(NULL,0,0,300,20 ,SWP_NOZORDER);
	ChangeMenuLang();
	((CAdministrativeApp *)AfxGetApp())->TranslateDialog((CDialog *)(this->m_Grid->GetParent()));
}

/////////////////////////////////////////////////////////////////////////////
// CTreeviewView printing

BOOL CTreeviewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTreeviewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTreeviewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTreeviewView diagnostics

#ifdef _DEBUG
void CTreeviewView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTreeviewView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTreeviewDoc* CTreeviewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeviewDoc)));
	return (CTreeviewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeviewView message handlers
void CTreeviewView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CTreeviewView::LoadOwner(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from Owner where ID=%ld"), ID);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Owner information"));
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,2);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,0);
	m_Grid->SetRows(RS.GetODBCFieldCount());
	for(int i=1, j=0;i<RS.GetODBCFieldCount();i++, j++)
	{
		CString FName,Value,Unit,Format,Srv,Mask;
		RS.GetFieldValue(i,Value);
		m_Grid->SetTextMatrix(j+1,1,Value);
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		m_Grid->SetTextMatrix(j+1,0,GetFieldName(&DB, _T("Owner"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask));
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		if(i==4)
			m_Grid->SetRowData(j+1,1);
		if(i==2 || i==9 || i==14)
			m_Grid->SetRowData(j+1,10);
		if(i==12)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Billing"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(12);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(14);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(15);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);

	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
/*	CDBVariant TempVar;
	CString m_Tbl=_T("select * from Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	DB.Close();
	m_Grid->SetFixedRows(1);
}

void CTreeviewView::LoadLicense(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	SQL.Format(_T("Select * from License where LicID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("License Information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,2);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,0);
	m_Grid->SetRows(RS.GetODBCFieldCount()-3);
	for(int i=4,j=0;i<RS.GetODBCFieldCount();i++,j++)
	{
		CString FName,Value,Unit,Format,Srv,Mask;
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("License"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			m_Grid->SetRows(m_Grid->GetRows()-1);
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;

		RS.GetFieldValue(i,Value);
		if(i==5 || i==6)
		{
			Value=Value.Left(10);
			m_Grid->SetRowData(j+1,8);
		}
		m_Grid->SetTextMatrix(j+1,1,Value);
		if(i==7)
			m_Grid->SetRowData(j+1,1);
		if(i==8)
		{
			Value.TrimRight(_T(" "));
			m_Service=Value;
			m_Grid->SetRowData(j+1,2);
//		}
//		if(i==8)
//		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Billing"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==10)
			m_Grid->SetRowData(j+1,3);
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(7);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	CDBVariant TempVar;
	CString m_Tbl=_T("select * from LicStatus");
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl.Format(_T("SELECT [SrvID],[SrvType%s] FROM SrvType WHERE [Active]=Yes"),m_Lang);

	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Tbl=_T("SELECT InvPeriodEn, Months FROM InvoicePeriod");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadStation(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	SQL.Format(_T("Select Station.*,stSrv from Station,StClass where StClass.StClassID=Left(Station.ClassStation,2) and StID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	CString FName,Value,Unit,Format,Srv,Mask;
	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
	Value.TrimRight(_T(" "));
	m_Service=Value;
	if(m_Service.Compare("__"))
		((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Fixed/Base station information"));
	else
		((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Monitoring station information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	m_Grid->SetRows(RS.GetODBCFieldCount()-4);
	for(int i=4,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("Station"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		if(!Value.IsEmpty())
		{
			if(i==11 || (i==19 && !Value.IsEmpty()))
			{
				CString Temp;
				double lat=atof(Value);
				int d=(int)lat,
				m=abs((int)((fabs(lat)-(double)abs(d))*60.));
				double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
				if(s>59.99)
				{
					s=0;
					m++;
				}
				if(m>59.)
				{
					m=0;
					d++;
				}
				Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
				Value=Temp;
			}
			if(i==12 || (i==20 && !Value.IsEmpty()))
			{
				CString Temp;
				double lon=atof(Value);
				int d=(int)lon,
				m=abs((int)((fabs(lon)-(double)abs(d))*60.));
				double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
				if(s>59.99)
				{
					s=0;
					m++;
				}
				if(m>59.)
				{
					m=0;
					d++;
				}
				Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
				Value=Temp;
			}
			m_Grid->SetTextMatrix(j+1,1,Value);
		}
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(i==8)
			m_Grid->SetRowData(j+1,1);
		if(i==9)
			m_Grid->SetRowData(j+1,2);
		if(i==13 || i==17)
			m_Grid->SetRowData(j+1,3);
		if(i==16)
			m_Grid->SetRowData(j+1,4);
		if(i==10)
			m_Grid->SetRowData(j+1,5);
		if(i==21)
			m_Grid->SetRowData(j+1,6);

		if(i==9)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Location"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==15)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(6);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(9);
//	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(10);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(13);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(15);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(20);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	CDBVariant TempVar;
	CString m_Tbl;
	if(m_Service==_T("MT"))
	{
		m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
		m_Combo1->ResetContent();
		m_Combo1->AddString(_T(""));
		m_Combo1->AddString(_T("T12"));
		m_Combo1->AddString(_T("T14"));
		m_Combo1->AddString(_T("G12"));
		m_Combo1->AddString(_T("G14"));
		m_Tbl.Format(_T("select StClassID, StClass%s from StClass where StClassID='FB'"),m_Lang);
	}
	else
	{
		m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
		m_Combo1->ResetContent();
		m_Combo1->AddString(_T(""));
		m_Combo1->AddString(_T("T11"));
		m_Combo1->AddString(_T("T14"));
		m_Combo1->AddString(_T("G11"));
		m_Combo1->AddString(_T("G14"));
		m_Tbl.Format(_T("select StClassID, StClass%s from StClass where StSrv='%s'"),m_Lang,m_Service);
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
//	m_Tbl=_T("SELECT * from StType");
//	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
//	while(1)
//	{
//		if(RS.IsEOF()) break;
//		RS.GetFieldValue((short)0,F1);
//		m_Combo1->AddString(F1);
//		RS.MoveNext();
//	}
//	RS.Close();	
	m_Combo1->AddString(_T("Fixed"));
	m_Combo1->AddString(_T("Typical"));	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
/*	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl=_T("SELECT * FROM Provisions");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	if(m_Service==_T("__"))
	{
		m_Grid->RemoveItem(20);
		m_Grid->RemoveItem(19);
		m_Grid->RemoveItem(18);
		m_Grid->RemoveItem(17);
		m_Grid->RemoveItem(16);
		m_Grid->RemoveItem(15);
		m_Grid->RemoveItem(14);
		m_Grid->RemoveItem(6);
		m_Grid->RemoveItem(4);
		m_Grid->RemoveItem(1);
		m_Grid->RemoveItem(3);
		m_Grid->SetCol(0);
		m_Grid->SetRow(5);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(7);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRowSel(1);
		m_Grid->SetCol(1);
	}
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadBC(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select BCStation.*,stSrv from BCStation,StClass where StClass.StClassID=Left(BCStation.ClassStation,2) and StID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Broadcasting station information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
	Value.TrimRight(_T(" "));
	m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-5);
	for(int i=4,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("BCStation"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		if(i==11 || (i==18 && !Value.IsEmpty()))
		{
			CString Temp;
			double lat=atof(Value);
			int d=(int)lat,
			m=abs((int)((fabs(lat)-(double)abs(d))*60.));
			double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;
				m++;
			}
			if(m>59.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		if(i==12 || (i==19 && !Value.IsEmpty()))
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		if(i==25 || i==26)
			Value=(Value==_T("1")?_T("Yes"):_T("No"));
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(i==8)
			m_Grid->SetRowData(j+1,1);
		if(i==9)
			m_Grid->SetRowData(j+1,2);
		if(i==13)
			m_Grid->SetRowData(j+1,3);
		if(i==16)
			m_Grid->SetRowData(j+1,4);
		if(i==17)
			m_Grid->SetRowData(j+1,5);
		if(i==10)
			m_Grid->SetRowData(j+1,6);
		if(i==20)
			m_Grid->SetRowData(j+1,7);
		if(i==21)
			m_Grid->SetRowData(j+1,11);
		if(i==25)
			m_Grid->SetRowData(j+1,12);
		if(i==26)
			m_Grid->SetRowData(j+1,12);
		if(i==27)
			m_Grid->SetRowData(j+1,13);
		if(i==9)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Location"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==15)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==19)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Geneva 06"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(6);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(9);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(10);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(13);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(15);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(27);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl.Format(_T("select StClassID, StClass%s from StClass where StSrv='%s'"),m_Lang,m_Service);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
//	m_Tbl=_T("SELECT * from StType");
//	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
//	while(1)
//	{
//		if(RS.IsEOF()) break;
//		RS.GetFieldValue((short)0,F1);
//		m_Combo1->AddString(F1);
//		RS.MoveNext();
//	}
//	RS.Close();	
	m_Combo1->AddString(_T("Fixed"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
/*	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl=_T("SELECT * FROM Provisions");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Tbl=_T("SELECT * FROM Plans");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1->AddString(_T("4"));
	m_Combo1->AddString(_T("5"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("C"));
	m_Combo1->AddString(_T("L"));
	m_Combo1->AddString(_T("S"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO9);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("Yes"));
	m_Combo1->AddString(_T("No"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO10);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("GS1"));
	m_Combo1->AddString(_T("GT1"));
	m_Combo1->AddString(_T("G02"));
	m_Combo1->AddString(_T("GB1"));
	m_Combo1->AddString(_T("T01"));
	m_Combo1->AddString(_T("T02"));
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadMobile(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	SQL.Format(_T("Select Mobiles.*,StSrv from Mobiles,StClass where StClass.StClassID=Left(Mobiles.ClassStation,2) and MobID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Mobile station information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
	Value.TrimRight(_T(" "));
	m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-2);
	for(int i=2,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("Mobiles"), FldInfo.m_strName,_T("En"), &Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			m_Grid->SetRows(m_Grid->GetRows()-1);
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		if(i==9 && !Value.IsEmpty())
		{
			CString Temp;
			double lat=atof(Value);
			int d=(int)lat,
			m=abs((int)((fabs(lat)-(double)abs(d))*60.));
			double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;
				m++;
			}
			if(m>59.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		if(i==10 && !Value.IsEmpty())
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;
				m++;
			}
			if(m>59.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(i==6)
			m_Grid->SetRowData(j+1,1);
		if(i==7)
			m_Grid->SetRowData(j+1,2);
		if(i==11 || i==13)
			m_Grid->SetRowData(j+1,3);
		if(i==15)
			m_Grid->SetRowData(j+1,4);
		if(i==8)
			m_Grid->SetRowData(j+1,5);
		if(i==20)
			m_Grid->SetRowData(j+1,6);
		if(i==7)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Location"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==13)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==16)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Vehicle"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(6);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(9);
//	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(10);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(16);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(22);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl.Format(_T("select StClassID, StClass%s from StClass where StClassID='ML'"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl=_T("SELECT StTypeEn from StType");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		F1.TrimRight();
		if(F1!=_T("Fixed") && F1!=_T("Base") && F1!=_T("Typical")) m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
/*	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl=_T("SELECT * FROM Provisions");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("T13"));
	m_Combo1->AddString(_T("G13"));
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadEquipment(long ID)
{
	CString SQL,SQL1;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(false);
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem());
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	SQL1=_T("SELECT EqName, Pwr2Ant, PowerType, RadPwr, RadPowerType, MadeBy, Model, SerialNo, OsetV12, OsetV,");
	SQL1+=_T(" OsetS12, OsetS, TranSys,TVSys,ColorSys, ERP_h_dbw, ERP_v_dbw, ERP_dbw, PwrRatio,EU_Ref, Sensitivity, EnDisp, GndCond, RJ81,");
	SQL1+=_T(" AdjRatio, FreqStabl, AngSep,NoiseFactor,ClassOp, RefPlanCfg, SysVar, RXMode, ERPTilt, Tilt, SystemType1, SystemType2, MaxPowDens,StSrv,ClassStation ");
	if(Typ==STATION)
		SQL.Format(_T("FROM Equipment,EqCat,Station,StClass where StClass.StClassID=Station.ClassStation and Station.StID=Equipment.StID and Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), ID);
	if(Typ==MONITORING)
		SQL.Format(_T("FROM Equipment,EqCat,Station,StClass where StClass.StClassID=Station.ClassStation and Station.StID=Equipment.StID and Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), ID);
	if(Typ==BC)
		SQL.Format(_T("FROM Equipment,EqCat,BCStation,StClass where StClass.StClassID=BCStation.ClassStation and BCStation.StID=Equipment.BCID and Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), ID);
	if(Typ==MOBILE)
		SQL.Format(_T("FROM Equipment,EqCat,Mobiles,StClass where StClass.StClassID=Mobiles.ClassStation and Mobiles.MobID=Equipment.MobID and Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), ID);
//	if(Typ==MONITORING)
//	{
//		SQL1=_T("SELECT EqName, Pwr2Ant, PowerType, RadPwr, RadPowerType, MadeBy, Model, SerialNo, OsetV12, OsetV,");
//		SQL1+=_T(" OsetS12, OsetS, TranSys,TVSys,ColorSys, ERP_h_dbw, ERP_v_dbw, ERP_dbw, PwrRatio,EU_Ref, Sensitivity, EnDisp, GndCond, RJ81,");
//		SQL1+=_T(" AdjRatio, FreqStabl, AngSep,NoiseFactor,ClassOp, RefPlanCfg, SysVar, RXMode, ERPTilt, Tilt, SystemType1, SystemType2, MaxPowDens,ClassStation ");
//		SQL.Format(_T("FROM Equipment,EqCat,Station where Station.StID=Equipment.StID and Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), ID);
//	}
	SQL=SQL1+SQL;

/*	if(Typ==BC)
		SQL.Format(_T("Select Equipment.*,EqCat.*,StSrv,ClassStation from Equipment,EqCat,BCStation,StClass where StClass.StClassID=Left(BCStation.ClassStation,2) and BCStation.StID=Equipment.BCID and Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), ID);
	if(Typ==MOBILE)
		SQL.Format(_T("Select Equipment.*,EqCat.*,StSrv,ClassStation from Equipment,EqCat,Mobiles,StClass where StClass.StClassID=Left(Mobiles.ClassStation,2) and Mobiles.MobID=Equipment.MobID and Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), ID);*/
	RS.Open(CRecordset::dynaset,SQL);
	((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Library"));
	//((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowPos(NULL,0,0,80,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Equipment information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
//	m_Grid->SetBackColorBand(0,0xDFDFDF);
	m_Grid->SetCols(0,4);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,StClass,Mask;
	RS.GetFieldValue(RS.GetODBCFieldCount()-2,Value);
	Value.TrimRight(_T(" "));
	m_Service=Value;
	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
	StClass=Value.Left(2);
	m_Grid->SetRows(RS.GetODBCFieldCount()-1);
	for(int i=0,j=0;i<RS.GetODBCFieldCount()-2;i++,j++)
	{
		if(Typ==BC && (i==3 || i==4))
			continue;
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		if(i==1 || i==3)
			FName=GetFieldName(&DB, _T("Equipment"), FldInfo.m_strName,_T("En"), &Unit,&Format,&Srv,&Mask);
		else
			FName=GetFieldName(&DB, _T("EqCat"), FldInfo.m_strName,_T("En"), &Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			m_Grid->SetRows(m_Grid->GetRows()-1);
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		RS.GetFieldValue(i,Value);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		m_Grid->SetTextMatrix(j+1,3,Srv);
		if(i==2)
			m_Grid->SetRowData(j+1,1);
		if(i==4)
			m_Grid->SetRowData(j+1,2);
		if(i==12) //13
			m_Grid->SetRowData(j+1,7);
		if(i==13) //14
			m_Grid->SetRowData(j+1,3);
		if(i==14) //15
			m_Grid->SetRowData(j+1,4);
		if(i==25) //26
			m_Grid->SetRowData(j+1,6);
		if((StClass!=_T("BT") && StClass!=_T("BC")) && (i==34 || i==35)) //35 || 36
			m_Grid->SetRowData(j+1,5);
		if(i==29) //30
			m_Grid->SetRowData(j+1,11);
		if(i==30) //31
			m_Grid->SetRowData(j+1,12);
		if(i==31) //32
			m_Grid->SetRowData(j+1,5);
		if(i==0)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Power"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(Typ==BC)
		{
			if(i==2)
			{
				j++;
				m_Grid->SetRows(m_Grid->GetRows()+1);
				m_Grid->SetCol(0);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
				m_Grid->SetCellForeColor(0x00FFFF);
				m_Grid->SetTextMatrix(j+1,0,_Z("Physical"));
				m_Grid->SetCellFontItalic(true);
				m_Grid->SetCol(1);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
				m_Grid->SetCol(2);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
			}
		}
		else
		{
			if(i==4)
			{
				j++;
				m_Grid->SetRows(m_Grid->GetRows()+1);
				m_Grid->SetCol(0);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
				m_Grid->SetCellForeColor(0x00FFFF);
				m_Grid->SetTextMatrix(j+1,0,_Z("Physical"));
				m_Grid->SetCellFontItalic(true);
				m_Grid->SetCol(1);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
				m_Grid->SetCol(2);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
			}
		}
		if(i==7)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Broadcasting"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==19)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==27)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Geneva 06"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	if(StClass==_T("BT"))
	{
///		m_Grid->SetRow(14);
///		m_Grid->SetCellFontBold(true);
///		m_Grid->SetRow(15);
///		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(16);
//		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(17);
//		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(18);
//		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(21);
//		m_Grid->SetCellFontBold(true);
	}
	if(StClass==_T("BC"))
	{
///		m_Grid->SetRow(10);
///		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(11);
//		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(12);
//		m_Grid->SetCellFontBold(true);
	}
	if(StClass==_T("FX"))
	{
		m_Grid->SetRow(12); //13
		m_Grid->SetCellFontBold(true);
	}
	if(StClass==_T("FX") || StClass==_T("ML") || StClass==_T("FB"))
	{
		m_Grid->SetRow(5); 
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6); 
		m_Grid->SetCellFontBold(true);
	}
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Grid->SetCol(2);
	for(i=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0x7F7F7F)
		{
			CString Val=m_Grid->GetTextMatrix(i,3);
			if(Val.Find(StClass,0)==-1)
			{
				RowDelete(i);
				i--;
			}
		}
		else
			if(StClass!=_T("BT") && StClass!=_T("BC") && m_Grid->GetTextMatrix(i,0)==_Z("Broadcasting"))
			{
				RowDelete(i);
				i--;
			}
			else
				if(StClass==_T("BC") && m_Grid->GetTextMatrix(i,0)==_Z("Misc."))
				{
					RowDelete(i);
					i--;
				}
	}
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl.Format(_T("select LU_DATA, LU_PROMPT_%s from PowerType"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		if(StClass==_T("FX") || StClass==_T("FB") || StClass==_T("ML") ||
			(StClass==_T("BC") && F1==_T("Y")) || (StClass==_T("BT") && (F1==_T("Y") || F1==_T("X"))))
		{
			RS.GetFieldValue((short)1,F2);
			m_Combo1->AddString(F1+_T(" - ")+F2);
		}
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl=_T("SELECT * from RadPowerType");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Tbl.Format(_T("SELECT SysCode, SysName%s FROM TVSys order by SysCode"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl=_T("SELECT distinct ColNameEn FROM ColorSys");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
//		RS.GetFieldValue((short)1,F2);
//		m_Combo1->AddString(F1+_T(" - ")+F2);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Tbl.Format(_T("SELECT Code, Desc%s FROM SysType order by Code"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Tbl=_T("SELECT StabTextEn FROM FreqStab");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
	m_Tbl.Format(_T("SELECT Code, Text%s FROM TranSys"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	if(StClass==_T("BT"))
	{
		m_Combo1->AddString(_T("RPC1"));
		m_Combo1->AddString(_T("RPC2"));
		m_Combo1->AddString(_T("RPC3"));
	}
	else
	{
		m_Combo1->AddString(_T("RPC4"));
		m_Combo1->AddString(_T("RPC5"));
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO9);
	m_Tbl=_T("SELECT * FROM SysVar");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	if(StClass==_T("BT") || StClass==_T("BC"))
	{
		m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
		m_Combo1->ResetContent();
		m_Combo1->AddString(_T(""));
		CString T=_Z("Fixed");
		T="FX - "+T;
		m_Combo1->AddString(T);
		T=_Z("Portable Outdoor");
		T="PO - "+T;
		m_Combo1->AddString(T);
		T=_Z("Portable Indoor");
		T="PI - "+T;
		m_Combo1->AddString(T);
		T=_Z("Mobile Outdoor");
		T="MO - "+T;
		m_Combo1->AddString(T);
	}
	DB.Close();
	if(m_Service==_T("__"))
	{
		m_Grid->SetRow(12); 
		m_Grid->SetCellFontBold(true);

		m_Grid->RemoveItem(13);
		m_Grid->RemoveItem(13);
		m_Grid->RemoveItem(13);
		m_Grid->RemoveItem(13);
		m_Grid->SetRowSel(1);
		m_Grid->SetCol(1);
	}
	m_Grid->SetFixedRows(1);
	m_Grid->SetCols(0,3);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadAntenna(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	m_CatID=-1;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(false);
	//((CButton *)GetDlgItem(IDC_ANTENNA))->SetWindowPos(NULL,0,0,80,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	((CButton *)GetDlgItem(IDC_ANTENNA))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ANTENNA))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ANTENNA))->SetWindowText(_Z("Add to Lib."));
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem()));
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==STATION || Typ==MONITORING)
		SQL.Format(_T("Select Antenna.*,AntCat.*,StSrv,ClassStation from Antenna,AntCat,Equipment,Station,StClass where StClass.StClassID=Left(Station.ClassStation,2) and Station.StID=Equipment.StID and Equipment.EqID=Antenna.EqID and Antenna.AntCatID=AntCat.AntCatID and AntID=%ld"), ID);
	if(Typ==BC)
		SQL.Format(_T("Select Antenna.*,AntCat.*,StSrv,ClassStation from Antenna,AntCat,Equipment,BCStation,StClass where StClass.StClassID=Left(BCStation.ClassStation,2) and BCStation.StID=Equipment.BCID and Equipment.EqID=Antenna.EqID and Antenna.AntCatID=AntCat.AntCatID and AntID=%ld"), ID);
	if(Typ==MOBILE)
		SQL.Format(_T("Select Antenna.*,AntCat.*,StSrv,ClassStation from Antenna,AntCat,Equipment,Mobiles,StClass where StClass.StClassID=Left(Mobiles.ClassStation,2) and Mobiles.MobID=Equipment.MobID and Equipment.EqID=Antenna.EqID and Antenna.AntCatID=AntCat.AntCatID and AntID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	//((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowPos(NULL,0,0,50,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Library"));
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Antenna information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
//	m_Grid->SetBackColorBand(0,0xDFDFDF);
	m_Grid->SetCols(0,4);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,StClass,Mask;
	RS.GetFieldValue(RS.GetODBCFieldCount()-2,Value);
	Value.TrimRight(_T(" "));
	m_Service=Value;
	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
	StClass=Value.Left(2);
	m_Grid->SetRows(RS.GetODBCFieldCount()-5);
	int j=0;
	m_Grid->SetRows(m_Grid->GetRows()+1);
	m_Grid->SetCol(0);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetCellForeColor(0x00FFFF);
	m_Grid->SetTextMatrix(j+1,0,_Z("Installation"));
	m_Grid->SetCellFontItalic(true);
	m_Grid->SetCol(1);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetCol(2);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	j++;
	for(int i=3;i<RS.GetODBCFieldCount()-2;i++,j++)
	{
		if(i==7) 
		{ 
			j--; 
			RS.GetFieldValue(i,Value);
			m_Grid->SetRowData(j+1,atol(Value)); 
			continue;
		}
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		if(i>7)
			FName=GetFieldName(&DB, _T("AntCat"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		else
			FName=GetFieldName(&DB, _T("Antenna"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		m_Grid->SetTextMatrix(j+1,3,Srv);
		if(i==6)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Technical"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==9)
			m_Grid->SetRowData(j+1,1);
		if(i==11)
			m_Grid->SetRowData(j+1,2);
		if(i==13)
			m_Grid->SetRowData(j+1,3);
		if(i==14)
			m_Grid->SetRowData(j+1,4);
		if(i==20 || i==21)
		{
			Value.Format(_T("%lf"),atof(Value)); //   /1000000.);
			m_Grid->SetTextMatrix(j+1,1,Value);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	if(StClass==_T("BT") || StClass==_T("BC") || StClass==_T("FB") || StClass==_T("ML") || Typ==MONITORING)
	{
		m_Grid->SetRow(2);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(3);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(4);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(7);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(9);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(10);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(12);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
	}
	if(StClass==_T("FX"))
	{
		m_Grid->SetRow(2);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(4);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(5);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(7);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(8);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(10);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(11);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(14);
		m_Grid->SetCellFontBold(true);
	}
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetCol(2);
	for(i=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0x7F7F7F)
		{
			CString Val=m_Grid->GetTextMatrix(i,3);
			if(Val.Find(StClass,0)==-1)
			{
				RowDelete(i);
				i--;
			}
		}
	}
	int Factor=-1;
	if(StClass==_T("FX")) Factor=0;
	m_Grid->SetCol(1);
	m_Grid->SetRow(7+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(10+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(11+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(12+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(13+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(14+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(15+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	if(StClass==_T("BC") || StClass==_T("BT"))
		Factor++;
	m_Grid->SetRow(17+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(18+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl.Format(_T("select AntClassID, AntClass%s from AntClass"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		if(((StClass==_T("BC") || StClass==_T("BT")) && F1!=("T")))
			RS.MoveNext();
		else
		{
			RS.GetFieldValue((short)1,F2);
			m_Combo1->AddString(F1+_T(" - ")+F2);
			RS.MoveNext();
		}
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl.Format(_T("SELECT PolID, PolText%s from PolType"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Tbl.Format(_T("SELECT GTypeID, GTypeText%s FROM GainType"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl.Format(_T("SELECT AntDirCode, AntDirectivity%s FROM AntDir"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	if(m_Service==_T("__"))
	{
		m_Grid->RemoveItem(19);
		m_Grid->RemoveItem(18);
		m_Grid->RemoveItem(15);
		m_Grid->RemoveItem(7);
//		m_Grid->SetRow(12); 
//		m_Grid->SetCellFontBold(true);
		m_Grid->SetRowSel(1);
		m_Grid->SetCol(1);

	}
	m_Grid->SetCols(0,3);
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadFrequency(long ID)
{
	CString SQL,StType;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(true);
	RS.m_pDatabase=&DB;
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	CString FName,Value,Unit,Format,Srv,StClass,Mask;
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem()));
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==STATION || Typ==MONITORING)
		SQL.Format(_T("Select Frequency.*,StSrv,ClassStation,StType from Frequency,Equipment,Station,StClass where StClass.StClassID=Left(Station.ClassStation,2) and Station.StID=Equipment.StID and Equipment.EqID=Frequency.EqID and FreqID=%ld"), ID);
	if(Typ==BC)
		SQL.Format(_T("Select Frequency.*,StSrv,ClassStation,StType from Frequency,Equipment,BCStation,StClass where StClass.StClassID=Left(BCStation.ClassStation,2) and BCStation.StID=Equipment.BCID and Equipment.EqID=Frequency.EqID and FreqID=%ld"), ID);
	if(Typ==MOBILE)
		SQL.Format(_T("Select Frequency.*,StSrv,ClassStation,StType from Frequency,Equipment,Mobiles,StClass where StClass.StClassID=Left(Mobiles.ClassStation,2) and Mobiles.MobID=Equipment.MobID and Equipment.EqID=Frequency.EqID and FreqID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	//((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowPos(NULL,0,0,80,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
	StType=Value;
//	if(Typ==MOBILE)
//		((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText("Add transmitter");
//	else
	if(StType==_T("Typical") || Typ==MONITORING)
		((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	else
		((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);

//		((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText("Service area");
//	else
		((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Add receiver"));
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Frequency information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,4);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	RS.GetFieldValue(RS.GetODBCFieldCount()-3,Value);
	Value.TrimRight(_T(" "));
	m_Service=Value;
	RS.GetFieldValue(RS.GetODBCFieldCount()-2,Value);
	StClass=Value.Left(2);
	m_Grid->SetRows(RS.GetODBCFieldCount()-4);
	for(int i=2,j=0;i<RS.GetODBCFieldCount()-3;i++,j++)
	{
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("Frequency"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,3,Srv);
		if(m_Grid->GetTextMatrix(j+1,2).IsEmpty()) m_Grid->SetTextMatrix(j+1,2,Unit);
		RS.GetFieldValue(i,Value);

		if(Typ==BC && FldInfo.m_strName==_T("NatServ"))
			Value=_T("CP");
//		if(i==18 || i==19)
//		{
//			m_Grid->SetRowData(j+1,9);
//		}
		if(i==2 || i==3 || i==4)
		{
			double Freq=atof(Value),factor=1;
			if(Freq<1000.) m_Grid->SetTextMatrix(j+1,2,_T("Hz"));
			else if(Freq<1000000.) {m_Grid->SetTextMatrix(j+1,2,_T("kHz")); factor=1000.;}
			else if(Freq<1000000000.) {m_Grid->SetTextMatrix(j+1,2,_T("MHz")); factor=1000000.;}
			else {m_Grid->SetTextMatrix(j+1,2,_T("GHz")); factor=1000000000.;}

			Value.Format(_T("%lf"),Freq/factor);
			Value.TrimLeft(_T(" "));
			Value.TrimRight(_T("0"));
			
			m_Grid->SetRowData(j+1,100);
		}
		m_Grid->SetTextMatrix(j+1,1,Value);
		if(i==17)
			m_Grid->SetRowData(j+1,2);
		if(i==8)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==19)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Fee"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==23)
			m_Grid->SetRowData(j+1,3);
	}
	RS.Close();
	m_Grid->SetCol(0);
	if(StClass==_T("BT"))
	{
		m_Grid->SetRow(1);
		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(2);
//		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(3);
//		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(5);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6);
		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(13);
//		m_Grid->SetCellBackColor(0x7F7F7F);
//		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(14);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(16);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetCol(1);
		m_Grid->SetRow(16);
		m_Grid->SetCellBackColor(0xDFDFDF);
	}
	if(StClass==_T("BC"))
	{
		m_Grid->SetRow(1);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(3);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(4);
		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(10);
//		m_Grid->SetCellBackColor(0x7F7F7F);
//		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(10);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(11);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetCol(1);
		m_Grid->SetRow(16);
		m_Grid->SetCellBackColor(0xDFDFDF);
//		m_Grid->SetText(_T("CP"));
	}
	if(StClass==_T("FX") || StClass==_T("ML") || StClass==_T("FB"))
	{
		m_Grid->SetRow(1);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(2);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(7);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(12);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(14);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(16);
		m_Grid->SetCellFontBold(true);
	}
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Grid->SetCol(2);
	for(i=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0x7F7F7F)
		{
			CString Val=m_Grid->GetTextMatrix(i,3);
			if(Val.Find(StClass,0)==-1)
			{
				RowDelete(i);
				i--;
			}
		}
	}
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl=_T("select * from FreqUnit");
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)1,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl.Format(_T("SELECT LU_DATA, LU_PROMPT_%s from NatServ"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1->AddString(_T("N"));
	m_Combo1->AddString(_T("S"));
	if(m_Service==_T("__"))
	{
		m_Grid->SetCol(0);
		m_Grid->SetRow(1); 
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(2); 
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6); 
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(7); 
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRowSel(1);
		m_Grid->RemoveItem(9);

/*		m_Grid->RemoveItem(9);
		m_Grid->RemoveItem(9);
		m_Grid->RemoveItem(9);
		m_Grid->RemoveItem(9);
		m_Grid->RemoveItem(9);
		m_Grid->RemoveItem(9);
		m_Grid->RemoveItem(9);
		m_Grid->RemoveItem(9);
		m_Grid->RemoveItem(9);*/
	}
	m_Grid->SetCols(0,3);
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::RowDelete(long row)
{
	unsigned int BackColor1, BackColor2, ForeColor, Italic;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	for(int i=row+1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRowData(i-1,m_Grid->GetRowData(i));
		m_Grid->SetTextMatrix(i-1,0,m_Grid->GetTextMatrix(i,0));
		m_Grid->SetTextMatrix(i-1,1,m_Grid->GetTextMatrix(i,1));
		m_Grid->SetTextMatrix(i-1,2,m_Grid->GetTextMatrix(i,2));
		m_Grid->SetTextMatrix(i-1,3,m_Grid->GetTextMatrix(i,3));
		m_Grid->SetCol(0);
		m_Grid->SetRow(i);
		ForeColor=m_Grid->GetCellForeColor();
		BackColor1=m_Grid->GetCellBackColor();
		Italic=m_Grid->GetCellFontItalic();
		m_Grid->SetCol(1);
		BackColor2=m_Grid->GetCellBackColor();
		m_Grid->SetRow(i-1);
		m_Grid->SetCellBackColor(BackColor2);
		m_Grid->SetCol(0);
		m_Grid->SetCellFontItalic(Italic);
		m_Grid->SetCellForeColor(ForeColor);
		m_Grid->SetCellBackColor(BackColor1);
		m_Grid->SetCol(2);
		m_Grid->SetCellBackColor(BackColor2);
	}
	m_Grid->SetRows(m_Grid->GetRows()-1);
	for(int j=row;j<59;j++)
	{
		m_Mask[0][j]=m_Mask[0][j+1];
		m_Mask[1][j]=m_Mask[1][j+1];
	}
}

void CTreeviewView::LoadInvoice(long ID)
{
/*	CString SQL,Unit;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(((CSMS4DCApp *)AfxGetApp())->m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from Invoice where LicID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,RS.GetODBCFieldCount()-1);
	m_Grid->SetColWidth(0,0,500);
	m_Grid->SetColWidth(1,0,1000);
	m_Grid->SetRows(1);
	for(int i=2,j=0;i<RS.GetODBCFieldCount();i++,j++)
	{
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		m_Grid->SetTextMatrix(0,j+1,GetFieldName(&DB, "Invoice", FldInfo.m_strName,"En",&Unit));
	}
	for(int k=0;!RS.IsEOF();k++)
	{
		m_Grid->SetRows(m_Grid->GetRows()+1);
		for(int i=2,j=0;i<RS.GetODBCFieldCount();i++,j++)
		{
		CString Value;
		RS.GetFieldValue(i,Value);
		m_Grid->SetTextMatrix(k+1,j+1,Value);
		}
		RS.MoveNext();
	}
	m_Grid->SetFixedRows(1);

	RS.Close();
	DB.Close();*/
}

void CTreeviewView::LoadPayment(long ID)
{
	CString SQL1,SQL2;
	CDatabase	DB;
	CRecordset	RS;
	long Balance=0;
	bool Empty=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->SetWindowText(_Z("Print"));
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_HIDE);
	//((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->SetWindowText(_Z("Delete"));
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_HIDE);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Billing information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetBackColorBand(0,0xDFDFDF);
	m_Grid->SetCols(0,8);
	m_Grid->SetColWidth(0,0,500);
	m_Grid->SetColWidth(1,0,1000);
	m_Grid->SetRows(1);
	m_Grid->SetTextMatrix(0,1,_Z("Bill no."));
	m_Grid->SetTextMatrix(0,2,_Z("Date"));
	m_Grid->SetTextMatrix(0,3,_Z("Description"));
	m_Grid->SetTextMatrix(0,4,_Z("Debit"));
	m_Grid->SetTextMatrix(0,5,_Z("Credit"));
	m_Grid->SetTextMatrix(0,6,_Z("Balance"));
	m_Grid->SetTextMatrix(0,7,_Z("Replaced"));
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	SQL1.Format(_T("Select InvoiceNo, format(InvDate,'yyyy/mm/dd') as dt, Description, Debit, Credit, Replaced, InvDate as d from Invoice where LicID=%ld"), ID);
	SQL2.Format(_T("Select PaymentNo, format(PayDate,'yyyy/mm/dd') as dt, Description, 0, Amount, '---', PayDate as d from Payment where LicID=%ld"), ID);
	SQL1=SQL1 + _T(" union all ") + SQL2;
	SQL2=_T("select * from (") + SQL1 + _T(") order by d");
	RS.Open(CRecordset::dynaset,SQL2);
	for(int k=0;!RS.IsEOF();k++)
	{
		Empty=false;
		m_Grid->SetRows(m_Grid->GetRows()+1);
		CString Value;
		RS.GetFieldValue((short)0,Value);
		m_Grid->SetTextMatrix(k+1,1,Value);
		RS.GetFieldValue(1,Value);
		m_Grid->SetTextMatrix(k+1,2,Value);
		RS.GetFieldValue(5,Value);
		m_Grid->SetTextMatrix(k+1,7,(Value=="0"?_Z("No"):(Value=="---"?"---":_Z("Yes"))));
		if(Value=="---")
		{
			RS.GetFieldValue(2,Value);
			m_Grid->SetTextMatrix(k+1,3,_Z("Payment: ")+Value);
		}
		else
		{
			RS.GetFieldValue(2,Value);
			m_Grid->SetTextMatrix(k+1,3,_Z("Invoice: ")+Value);
		}
		RS.GetFieldValue(3,Value);
		m_Grid->SetTextMatrix(k+1,4,Value);
		RS.GetFieldValue(4,Value);
		m_Grid->SetTextMatrix(k+1,5,Value);
		RS.MoveNext();
		m_Grid->SetRowData(k+1,ID);
	}
	RS.Close();
	DB.Close();
	if(Empty==false)
	{
		m_Grid->SetFixedRows(1);
		m_Grid->SetColSel(1);
		m_Grid->SetCol(1);
		m_Grid->SetRow(0);
		m_Grid->SetRowSel(0);
		for(k=1;k<m_Grid->GetRows();k++)
		{
			char buf[50];
			if( m_Grid->GetTextMatrix(k,7)!="---")
				Balance=atol(m_Grid->GetTextMatrix(k,5))-atol(m_Grid->GetTextMatrix(k,4));
			else
				Balance+=atol(m_Grid->GetTextMatrix(k,5))-atol(m_Grid->GetTextMatrix(k,4));
			ltoa(Balance,buf,10);
			m_Grid->SetTextMatrix(k,6,buf);
		}
	}
//	m_Grid->SetColPosition(3,0,7);
	m_Grid->SetCols(0,m_Grid->GetCols(0)-1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadReceiver(long ID)
{
	CString SQL,GeoType;
	CDatabase	DB;
	CRecordset	RS;
	int Typ;
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	pView->GetTreeCtrl().GetItemImage(
		pView->GetTreeCtrl().GetParentItem(
			pView->GetTreeCtrl().GetParentItem(
				pView->GetTreeCtrl().GetParentItem(
					pView->GetTreeCtrl().GetSelectedItem()))),Typ,Typ);
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_HIDE);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_HIDE);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_HIDE);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select GeoType from link where receiverID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	RS.GetFieldValue((short)0,GeoType);
	RS.Close();
	GeoType.TrimRight(_T(" "));
	if(GeoType==_T("POINT"))
	{
		if(Typ!=MOBILE)
			((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Receiver information"));
		else
			((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Transmitter information"));
		m_Grid->ClearStructure();
		m_Grid->SetCols(0,2);
		m_Grid->SetTextMatrix(0,1,_Z("Value"));
		m_Grid->SetColWidth(0,0,4000);
		m_Grid->SetColWidth(1,0,3000);
		m_Grid->SetColWidth(2,0,2000);
		SQL.Format(_T(" from link,Frequency,eqcat, Equipment, Station where receiverID=%ld"), ID);
		SQL="Select sitename as [Station Name], GeoType as [Type], geolat as Latitude, geolon as Longitude, station.country as Country, eqname as [Equipment],Frequency"+SQL;
		SQL=SQL+ " and link.rxid=frequency.freqid and frequency.eqid=equipment.eqid and equipment.stid=station.stid and eqcat.eqcatid=equipment.eqcatid";
		RS.Open(CRecordset::dynaset,SQL);
		m_Grid->SetRows(RS.GetODBCFieldCount()+1);
		RS.MoveFirst();
		for(int i=0,j=0;i<RS.GetODBCFieldCount() && !RS.IsEOF();i++,j++)
		{
			CString Value;
			RS.GetFieldValue(i,Value);
			if(i==2)
			{
				CString Temp;
				double lat=atof(Value);
				int d=(int)lat,
				m=abs((int)((fabs(lat)-(double)abs(d))*60.));
				double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
				if(s>59.99)
				{
					s=0;
					m++;
				}
				if(m>59.)
				{
					m=0;
					d++;
				}
				Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
				Value=Temp;
			}
			if(i==3)
			{
				CString Temp;
				double lon=atof(Value);
				int d=(int)lon,
				m=abs((int)((fabs(lon)-(double)abs(d))*60.));
				double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
				if(s>59.99)
				{
					s=0;
					m++;
				}
				if(m>59.)
				{
					m=0;
					d++;
				}
				Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
				Value=Temp;
			}

			m_Grid->SetTextMatrix(j+1,1,Value);
			CODBCFieldInfo FldInfo;
			RS.GetODBCFieldInfo(i,FldInfo);
			m_Grid->SetTextMatrix(j+1,0,_Z(FldInfo.m_strName));
		}
		RS.Close();
	}
	if(GeoType==_T("MULTIPOINT"))
	{
		((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Receiving area information"));
		m_Grid->ClearStructure();
		m_Grid->SetCols(0,3);
		m_Grid->SetRows(7);
		m_Grid->SetTextMatrix(0,1,_Z("Latitude"));
		m_Grid->SetTextMatrix(0,2,_Z("Longitude"));
		m_Grid->SetTextMatrix(1,0,_Z("Point1"));
		m_Grid->SetTextMatrix(2,0,_Z("Point2"));
		m_Grid->SetTextMatrix(3,0,_Z("Point3"));
		m_Grid->SetTextMatrix(4,0,_Z("Point4"));
		m_Grid->SetTextMatrix(5,0,_Z("Point5"));
		m_Grid->SetTextMatrix(6,0,_Z("Point6"));
		m_Grid->SetColWidth(0,0,4000);
		m_Grid->SetColWidth(1,0,2000);
		m_Grid->SetColWidth(2,0,2000);
		SQL.Format(_T("Select * from link where receiverID=%ld"), ID);
		RS.Open(CRecordset::dynaset,SQL);
		for(int i=1,j=13;i<7;i++)
		{
			CString Value;
			RS.GetFieldValue(j++,Value);
			if(Value.IsEmpty()) break;
//			if(i==2)
			{
				CString Temp;
				double lat=atof(Value);
				int d=(int)lat,
				m=abs((int)((fabs(lat)-(double)abs(d))*60.));
				double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
				if(s>59.99)
				{
					s=0;
					m++;
				}
				if(m>59.)
				{
					m=0;
					d++;
				}
				Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
				Value=Temp;
			}
			m_Grid->SetTextMatrix(i,1,Value);
			RS.GetFieldValue(j++,Value);
//			if(i==3)
			{
				CString Temp;
				double lon=atof(Value);
				int d=(int)lon,
				m=abs((int)((fabs(lon)-(double)abs(d))*60.));
				double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
				if(s>59.99)
				{
					s=0;
					m++;
				}
				if(m>59.)
				{
					m=0;
					d++;
				}
				Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
				Value=Temp;
			}
			m_Grid->SetTextMatrix(i,2,Value);
		}
		m_Grid->SetRows(i);
		RS.Close();	
	}
	if(GeoType==_T("CIRCLE"))
	{
		CString Value;
		((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Receiving area information"));
		m_Grid->ClearStructure();
		m_Grid->SetCols(0,2);
		m_Grid->SetRows(4);
		m_Grid->SetTextMatrix(0,1,_Z("Value"));
		m_Grid->SetColWidth(0,0,4000);
		m_Grid->SetColWidth(1,0,1000);
		SQL.Format(_T("Select * from link where receiverID=%ld"), ID);
		RS.Open(CRecordset::dynaset,SQL);
		RS.GetFieldValue(9,Value);
		m_Grid->SetTextMatrix(1,0,_Z("Center Latitude"));
		CString Temp;
		double lat=atof(Value);
		int d=(int)lat,
		m=abs((int)((fabs(lat)-(double)abs(d))*60.));
		double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
		if(s>59.99)
		{
			s=0;
			m++;
		}
		if(m>59.)
		{
			m=0;
			d++;
		}
		Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
		Value=Temp;
		m_Grid->SetTextMatrix(1,1,Value);
		RS.GetFieldValue(10,Value);
		m_Grid->SetTextMatrix(2,0,_Z("Center Longitude"));
		lat=atof(Value);
		d=(int)lat,
		m=abs((int)((fabs(lat)-(double)abs(d))*60.));
		 s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
		if(s>59.99)
		{
			s=0;
			m++;
		}
		if(m>59.)
		{
			m=0;
			d++;
		}
		Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
		Value=Temp;
		m_Grid->SetTextMatrix(2,1,Value);
		RS.GetFieldValue(11,Value);
		m_Grid->SetTextMatrix(3,0,_Z("Radius (km)"));
		m_Grid->SetTextMatrix(3,1,Value);
		RS.Close();
	}
	if(GeoType==_T("ZONE"))
	{
		CString Value;
		((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Receiving area information"));
		m_Grid->ClearStructure();
		m_Grid->SetCols(0,2);
		m_Grid->SetRows(2);
		m_Grid->SetTextMatrix(0,1,_Z("Value"));
		m_Grid->SetColWidth(0,0,4000);
		m_Grid->SetColWidth(1,0,1000);
		SQL.Format(_T("Select * from link where receiverID=%ld"), ID);
		RS.Open(CRecordset::dynaset,SQL);
		RS.GetFieldValue(_T("zone"),Value);
		m_Grid->SetTextMatrix(1,0,_Z("Zone"));
		m_Grid->SetTextMatrix(1,1,Value);
		RS.Close();
	}
	DB.Close();
	m_Grid->SetFixedRows(1);
}

void CTreeviewView::LoadES(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select ntc_type,e_stn.* from notice,e_stn where notice.ntc_id=e_stn.ntc_id and e_stn.ntc_id=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Earth station information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	m_Grid->SetRows(RS.GetODBCFieldCount()-13);
	CODBCFieldInfo FldInfo;
	RS.GetODBCFieldInfo((short)0,FldInfo);
	FName=GetFieldName(&DB, _T("Notice"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
	m_Grid->SetTextMatrix(1,0,FName);
	RS.GetFieldValue((short)0,Value);
	m_Grid->SetTextMatrix(1,1,Value);
	m_Grid->SetRowData(1,1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	for(int i=1,j=1;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("E-stn"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		/*if(j==4)
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			float s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}*/
		if(j==10)
		{
			CString Temp;
			double lat=atof(Value);
			int d=(int)lat,
			m=abs((int)((fabs(lat)-(double)abs(d))*60.));
			double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;
				m++;
			}
			if(m>59.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		if(j==9)
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(j==2)
			m_Grid->SetRowData(j+1,2);
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(6);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(7);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(9);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(10);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("S"));
	m_Combo1->AddString(_T("T"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
/*	CDBVariant TempVar;
	CString F1,F2;
	CString m_Tbl;
	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadAllot(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from rrc_allotment where Allotkey=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("GE06 Allotment information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	m_Grid->SetRows(RS.GetODBCFieldCount()-2);
	CODBCFieldInfo FldInfo;
/*	RS.GetODBCFieldInfo((short)0,FldInfo);
	FName=GetFieldName(&DB, _T("Notice"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
	m_Grid->SetTextMatrix(1,0,FName);
	RS.GetFieldValue((short)0,Value);
	m_Grid->SetTextMatrix(1,1,Value);
	m_Grid->SetRowData(1,1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);*/
	for(int i=1,j=0;i<RS.GetODBCFieldCount();i++,j++)
	{
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("rrc_allotment"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		if(FldInfo.m_strName==_T("Frequency"))
			Value.Format(_T("%lf"),atof(Value)/1000000);
		/*if(j==4)
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			float s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}*/
/*		if(j==10)
		{
			CString Temp;
			double lat=atof(Value);
			int d=(int)lat,
			m=abs((int)((fabs(lat)-(double)abs(d))*60.));
			double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;
				m++;
			}
			if(m>59.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		if(j==9)
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}*/
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(j==11)
			m_Grid->SetRowData(j+1,1);
		if(j==1 || j==10)
			m_Grid->SetRowData(j+1,2);
		if(j==12)
			m_Grid->SetRowData(j+1,3);
		if(j==5)
			m_Grid->SetRowData(j+1,4);
		if(j==3)
			m_Grid->SetRowData(j+1,5);
		if(j==7)
			m_Grid->SetRowData(j+1,6);
		if(j==13)
			m_Grid->SetRowData(j+1,7);
		if(j==14)
			m_Grid->SetRowData(j+1,11);
	}
	RS.Close();
	m_Grid->SetCol(1);
	m_Grid->SetRow(3);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(2);
//	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(3);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(6);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(7);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(9);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(10);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(13);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("BC"));
	m_Combo1->AddString(_T("BT"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
/*	CDBVariant TempVar;
	CString F1,F2;
	CString m_Tbl;
	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("H"));
	m_Combo1->AddString(_T("V"));
	m_Combo1->AddString(_T("M"));
	m_Combo1->AddString(_T("U"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1->AddString(_T("4"));
	m_Combo1->AddString(_T("5"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("GS2"));
	m_Combo1->AddString(_T("GT2"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("RPC1"));
	m_Combo1->AddString(_T("RPC2"));
	m_Combo1->AddString(_T("RPC3"));
	m_Combo1->AddString(_T("RPC4"));
	m_Combo1->AddString(_T("RPC5"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("RN1"));
	m_Combo1->AddString(_T("RN2"));
	m_Combo1->AddString(_T("RN3"));
	m_Combo1->AddString(_T("RN4"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1->AddString(_T("N"));
	m_Combo1->AddString(_T("S"));
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadContour(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from rrc_contour where contourkey=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("GE06 contour information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	m_Grid->SetRows(RS.GetODBCFieldCount()-3);
	CODBCFieldInfo FldInfo;
	for(int i=1,j=0;i<RS.GetODBCFieldCount();i++,j++)
	{
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("rrc_contour"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		/*if(j==4)
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			float s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}*/
/*		if(j==10)
		{
			CString Temp;
			double lat=atof(Value);
			int d=(int)lat,
			m=abs((int)((fabs(lat)-(double)abs(d))*60.));
			double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;
				m++;
			}
			if(m>59.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		if(j==9)
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}*/
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(j==0 || j==1)
			m_Grid->SetRowData(j+1,2);
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("S"));
	m_Combo1->AddString(_T("T"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
/*	CDBVariant TempVar;
	CString F1,F2;
	CString m_Tbl;
	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::AddESStation()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	SQL.Format(_T("Select ntc_type,e_stn.* from notice,e_stn where notice.ntc_id=e_stn.ntc_id and e_stn.ntc_id=-1"));
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Earth station information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
//	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
//	Value.TrimRight(" ");
//	m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-13);
	CODBCFieldInfo FldInfo;
	RS.GetODBCFieldInfo((short)0,FldInfo);
	FName=GetFieldName(&DB, _T("Notice"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
	m_Grid->SetTextMatrix(1,0,FName);
	m_Grid->SetRowData(1,1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetTextMatrix(1,1,_T("S"));
	for(int i=1,j=1;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
//		RS.GetFieldValue(i,Value);
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("E-stn"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(j==2)
			m_Grid->SetRowData(j+1,2);
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(6);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(7);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(9);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(10);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	CDBVariant TempVar;
	CString F1,F2;
	CString m_Tbl;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("S"));
	m_Combo1->AddString(_T("T"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
/*	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::AddESAnt(int UpDown)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Library"));
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ANTENNA))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ANTENNA))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ANTENNA))->SetWindowText(_Z("Patt. Values"));
	((CButton *)GetDlgItem(IDC_ANTENNA))->SetWindowPos(NULL,0,0,110,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	SQL.Format(_T("Select * from e_ant where ntc_id=-1"));
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Earth station antenna information"));
	m_CatID=0;
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask,Patt_ID=-1;
	m_Grid->SetRows(RS.GetODBCFieldCount()-12);
	for(int i=1,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
//		RS.GetFieldValue(i,Value);
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("e_ant"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
//		if(i==2)
//			m_Grid->SetRowData(j+1,1);
	}
	RS.Close();
	if(UpDown==EANTUP) 
		m_Grid->SetTextMatrix(1,1,_T("E"));
	else
		m_Grid->SetTextMatrix(1,1,_T("R"));
	m_Grid->SetCol(0);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetCellForeColor(0x00FFFF);
	m_Grid->SetTextMatrix(j+1,0,_Z("Pattern"));
	m_Grid->SetCellFontItalic(true);
	m_Grid->SetCol(1);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetCol(2);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetRow(1);
	m_Grid->SetCol(1);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(0);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(5);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
/*	CDBVariant TempVar;
	CString F1,F2;
	CString m_Tbl;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();*/	
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

bool CTreeviewView::ESSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[30], Values[30], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()==0x7F7F7F)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	Values[0].Format(_T("%ld"),m_RecID);
	if(Values[1].IsEmpty())
		Missing= m_Grid->GetTextMatrix(1,0) + ",";
	if(Values[2].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(2,0) + ",";
	if(Values[3].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	if(Values[4].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(4,0) + ",";
	if(Values[6].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(6,0) + ",";
	if(Values[7].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(7,0) + ",";
	if(Values[8].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(8,0) + ",";
	if(Values[9].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(9,0) + ",";
	if(Values[1]!=_T("T"))
	{
		if(Values[10].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(10,0) + ",";
		if(Values[11].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(11,0) + ",";
	}
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else 
	{
		double sgn;
		int Part=Values[3].Find(_T("-"),0)-1;
		if(Part<0)
			Part=3;
		//if(Values[5].Left(1)==_T("-")) sgn=-1.0;
		//else							sgn=1.0;
		//double NomLON = (atof(Values[5].Left(4))+sgn*atof(Values[5].Mid(4,2))/60.+sgn*atof(Values[5].Right(5))/3600.);
		int d1,d2,m1,m2,s1,s2;
		double NomLON=atof(Values[5]);
		if(Values[10].Left(1)==_T("-")) sgn=-1.0;
		else							sgn=1.0;
		double LON = (atof(Values[10].Left(4))+sgn*atof(Values[10].Mid(4,2))/60.+sgn*atof(Values[10].Mid(6,2))/3600.);
		d1=atoi(Values[10].Left(4));
		m1=atoi(Values[10].Mid(4,2));
		s1=(int)atof(Values[10].Mid(6,2));
		if(Values[11].Left(1)==_T("-")) sgn=-1.0;
		else							sgn=1.0;
		double LAT = (atof(Values[11].Left(3))+sgn*atof(Values[11].Mid(3,2))/60.+sgn*atof(Values[11].Mid(5,2))/3600.);
		d2=atoi(Values[11].Left(3));
		m2=atoi(Values[11].Mid(3,2));
		s2=(int)atof(Values[11].Mid(5,2));
		if(m_Action==1) // Add new
		{
			if(ESValidation(Values))
			{
				CString NewID;
				SQL=_T("Select max(ntc_id)+1 from e_stn");
				RS.Open(CRecordset::dynaset,SQL);
				RS.GetFieldValue((short)0,NewID);
				RS.Close();
				if(NewID.IsEmpty()) NewID=_T("1");
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				SQL.Format(_T("insert into notice (ntc_id,ntc_type,st_cur) select %s,'%s','01'"),NewID,Values[1]);
				DB.ExecuteSQL(SQL);
				if(Values[5].IsEmpty())
				{
					SQL.Format(_T("select %s,%ld,'%s','%s','%s',%s,%s,%s,%s,%.4lf,%.4lf "),NewID, 
						pView->GetTreeCtrl().GetItemData(Node),	Values[2], Values[3].Left(Part), Values[4], (Values[6].IsEmpty()?_T("NULL"):Values[6]), 
						(Values[7].IsEmpty()?_T("NULL"):Values[7]), (Values[8].IsEmpty()?_T("NULL"):Values[8]), 
						(Values[9].IsEmpty()?_T("NULL"):Values[9]), LON,LAT);
					SQL=_T("insert into e_stn (ntc_id,LicID, stn_name, ctry, sat_name, elev_min, azm_fr, azm_to, ant_alt, long_dec, lat_dec) ")+SQL;
				}
				else
				{
					SQL.Format(_T("select %s,%ld,'%s','%s','%s',%lf,%s,%s,%s,%s,%.4lf,%.4lf "),NewID, 
						pView->GetTreeCtrl().GetItemData(Node),	Values[2], Values[3].Left(Part), Values[4], NomLON,(Values[6].IsEmpty()?_T("NULL"):Values[6]), 
						(Values[7].IsEmpty()?_T("NULL"):Values[7]), (Values[8].IsEmpty()?_T("NULL"):Values[8]), 
						(Values[9].IsEmpty()?_T("NULL"):Values[9]), LON,LAT);
					SQL=_T("insert into e_stn (ntc_id,LicID, stn_name, ctry, sat_name, long_nom, elev_min, azm_fr, azm_to, ant_alt, long_dec, lat_dec) ")+SQL;
				}
				DB.ExecuteSQL(SQL);
				SQL.Format(_T("update e_stn set long_deg=%d,long_ew='%s',long_min=%d,long_sec=%d,lat_deg=%d,lat_ns='%s',lat_min=%d,lat_sec=%d where ntc_id=%s "),
					(d1<0?-d1:d1),(d1<0?_T("W"):_T("E")),(m1<0?-m1:m1),(s1<0?-s1:s1),(d2<0?-d2:d2),(d2<0?_T("S"):_T("N")),(m2<0?-m2:m2),(s2<0?-s2:s2), NewID);
				DB.ExecuteSQL(SQL);
				Node=pView->GetTreeCtrl().InsertItem(_Z("ES Station: ")+Values[2]+_T("-")+NewID,ESTATION,ESTATION,pView->GetTreeCtrl().GetSelectedItem());
				pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
				pView->GetTreeCtrl().Select(Node,TVGN_CARET);
				m_Refresh=false;
				pView->RedrawWindow();
				AddTrail(_Z("Add earth station"),atol((LPCTSTR)NewID),_T("e_stn"));
			}
			else
				result=false;
		}
		else    // Update
		{
			CString NewID;
			SQL.Format(_T("Select * from e_stn where ntc_id=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			if(ESValidation(Values))
			{
				SQL1.Format(_T("UPDATE e_stn SET stn_name = '%s', ctry = '%s', sat_name = '%s', "), Values[2], Values[3].Left(Part), Values[4]);
				SQL2=SQL1;
				if(Values[5].IsEmpty())
				{
					SQL1.Format(_T("long_nom=NULL, elev_min = %s, "), (Values[6].IsEmpty()?_T("NULL"):Values[6]));
					SQL2+=SQL1;
				}
				else
				{
					SQL1.Format(_T("long_nom = %lf, elev_min = %s, "), NomLON, (Values[6].IsEmpty()?_T("NULL"):Values[6]));
					SQL2+=SQL1;
				}
				SQL1.Format(_T("azm_fr = %s, azm_to = %s, ant_alt = %s, long_dec = %.4lf, lat_dec=%.4lf "), (Values[7].IsEmpty()?_T("NULL"):Values[7]), 
					(Values[8].IsEmpty()?_T("NULL"):Values[8]), (Values[9].IsEmpty()?_T("NULL"):Values[9]), 
					LON,LAT);
				SQL2+=SQL1;
				SQL1.Format(_T("WHERE ntc_id=%ld"), m_RecID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);
				SQL.Format(_T("update e_stn set long_deg=%d,long_ew='%s',long_min=%d,long_sec=%d,lat_deg=%d,lat_ns='%s',lat_min=%d,lat_sec=%d where ntc_id=%ld "),
					(d1<0?-d1:d1),(d1<0?_T("W"):_T("E")),(m1<0?-m1:m1),(s1<0?-s1:s1),(d2<0?-d2:d2),(d2<0?_T("S"):_T("N")),(m2<0?-m2:m2),(s2<0?-s2:s2), m_RecID);
				DB.ExecuteSQL(SQL);
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				NewID.Format(_T("%s%s-%ld"),_Z("ES Station: "),Values[2],m_RecID);
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),NewID);

				AddTrail(_Z("Update earth station"),m_RecID,"e_stn");
				result=true;
			}
			else
				result=false;
		}
	}
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::ESAntSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[30], Values[30], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()==0x7F7F7F)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
	Values[0].Format(_T("%ld"),pView->GetTreeCtrl().GetItemData(Node));
	if(Values[1].IsEmpty())
		Missing= m_Grid->GetTextMatrix(1,0) + ",";
	if(Values[2].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(2,0) + ",";
	if(Values[3].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	if(Values[4].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(4,0) + ",";
//	if(Values[5].IsEmpty())
//		Missing+= m_Grid->GetTextMatrix(5,0) + ",";
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else 
	{
//		double sgn;
		if(m_Action==1) // Add new
		{
			if(ESAntValidation(Values))
			{
				CString NewID;
				SQL=_T("Select max(AntID)+1 from e_ant");
				RS.Open(CRecordset::dynaset,SQL);
				RS.GetFieldValue((short)0,NewID);
				RS.Close();
				if(NewID.IsEmpty()) NewID=_T("1");
				if(m_CatID>0)
				{
					SQL.Format(_T("select %s,%ld,'%s','%s','%s','%s',%s,%ld "),NewID, 
						pView->GetTreeCtrl().GetItemData(Node),	Values[1], Values[2],  
						(Values[3].IsEmpty()?_T("0"):Values[3]), (Values[4].IsEmpty()?_T("0"):Values[4]), 
						(Values[5].IsEmpty()?_T("NULL"):Values[5]), m_CatID);
					SQL=_T("insert into e_ant (AntID,ntc_id,emi_rcp,beam_name,bmwdth,gain,ant_diam,pattern_id) ")+SQL;
				}
				else
				{
					SQL.Format(_T("select %s,%ld,'%s','%s','%s','%s',%s "),NewID, 
						pView->GetTreeCtrl().GetItemData(Node),	Values[1], Values[2],  
						(Values[3].IsEmpty()?_T("0"):Values[3]), (Values[4].IsEmpty()?_T("0"):Values[4]), 
						(Values[5].IsEmpty()?_T("NULL"):Values[5]));
					SQL=_T("insert into e_ant (AntID,ntc_id,emi_rcp,beam_name,bmwdth,gain,ant_diam) ")+SQL;
				}
				DB.ExecuteSQL(SQL);
				if(Values[1]==_T("E"))
					Node=pView->GetTreeCtrl().InsertItem(_Z("Beam: ")+Values[2],EANTUP,EANTUP,pView->GetTreeCtrl().GetSelectedItem());
				else
					Node=pView->GetTreeCtrl().InsertItem(_Z("Beam: ")+Values[2],EANTDN,EANTDN,pView->GetTreeCtrl().GetSelectedItem());
				pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
				pView->GetTreeCtrl().Select(Node,TVGN_CARET);
				m_Refresh=false;
				pView->RedrawWindow();
				AddTrail(_Z("Add earth station antenna"),atol((LPCTSTR)NewID),_T("e_ant"));
			}
			else
				result=false;
		}
		else    // Update
		{
			SQL.Format(_T("Select * from e_ant where AntID=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			if(ESAntValidation(Values))
			{
				SQL1.Format(_T("UPDATE e_ant SET beam_name = '%s', "), Values[2]);
				SQL2=SQL1;
				SQL1.Format(_T("bmwdth = %s, gain = %s, "), (Values[3].IsEmpty()?_T("0"):Values[3]), (Values[4].IsEmpty()?_T("0"):Values[4]));
				SQL2+=SQL1;
				if(m_CatID>0)
					SQL1.Format(_T("ant_diam = %s, pattern_id = %ld "), (Values[5].IsEmpty()?_T("NULL"):Values[5]), m_CatID);
				else
					SQL1.Format(_T("ant_diam = %s "), (Values[5].IsEmpty()?_T("0"):Values[5]));

				SQL2+=SQL1;
				SQL1.Format(_T("WHERE AntID=%ld"), m_RecID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Beam: ")+Values[2]);

				AddTrail(_Z("Update earth station antenna"),m_RecID,_T("e_ant"));

				SQL2.Format(_T("update grp set beam_name = '%s' where AntID=%ld"),Values[2], m_RecID);
				DB.ExecuteSQL(SQL2);
				result=true;
			}
			else
				result=false;
		}
	}
	RS.Close();
	DB.Close();
	//m_Grid->SetRow(Row);
	//m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::ESAntValidation(CString Values[])
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("select * from e_ant where ntc_id=%s and emi_rcp='%s' and beam_name='%s'"),
		Values[0],Values[1],Values[2]);
	RS.Open(CRecordset::snapshot,SQL);
	if(RS.GetRecordCount()>0)
	{
		AfxMessageBox(_Z("Duplicate beams cannot be defined!"));
		result=false;
	}
	RS.Close();
	DB.Close();
	return result;
}

void CTreeviewView::LoadESAnt(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Library"));
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ANTENNA))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ANTENNA))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_ANTENNA))->SetWindowText(_Z("Patt. Values"));
	((CButton *)GetDlgItem(IDC_ANTENNA))->SetWindowPos(NULL,0,0,110,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from e_ant where AntID=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Earth station antenna information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask,Patt_ID;
	m_Grid->SetRows(RS.GetODBCFieldCount()-12);
	for(int i=1,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		if(!FldInfo.m_strName.CompareNoCase(_T("pattern_id")))
			RS.GetFieldValue(i,Patt_ID);
		FName=GetFieldName(&DB, _T("e_ant"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
	}
	RS.Close();
	m_CatID=atol(Patt_ID);
	m_Grid->SetCol(0);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetCellForeColor(0x00FFFF);
	m_Grid->SetTextMatrix(j+1,0,_Z("Pattern"));
	m_Grid->SetCellFontItalic(true);
	m_Grid->SetCol(1);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetCol(2);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	j++;
	Patt_ID.TrimRight();
	if(atol(Patt_ID)>0)
	{
		SQL.Format(_T("Select * from ant_type where pattern_id=%s"), Patt_ID);
		RS.Open(CRecordset::dynaset,SQL);
		m_Grid->SetRows(m_Grid->GetRows()+RS.GetODBCFieldCount()-6);
		for(int i=1;i<RS.GetODBCFieldCount()-1;i++,j++)
		{
			CODBCFieldInfo FldInfo;
			RS.GetODBCFieldInfo(i,FldInfo);
			FName=GetFieldName(&DB, _T("ant_type"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
			if(Srv==_T("-"))
			{
				j--;
				continue;
			}
			m_Grid->SetTextMatrix(j+1,0,FName);
			m_Mask[0][j+1]=Mask;
			m_Mask[1][j+1]=Format;
			RS.GetFieldValue(i,Value);
			m_Grid->SetTextMatrix(j+1,1,Value);
			m_Grid->SetTextMatrix(j+1,2,Unit);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0xDFDFDF);
			m_Grid->SetCol(2);
			m_Grid->SetCellBackColor(0xDFDFDF);
		}
		RS.Close();
	}	
	m_Grid->SetRow(1);
	m_Grid->SetCol(1);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(0);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(5);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::LoadESGroup(long ID)
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from grp where grp_id=%ld"), ID);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Group information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	//RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
	//Value.TrimRight(_T(" "));
	//m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-52);
	for(int i=1,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("grp"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		RS.GetFieldValue(i,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(j==0)
			m_Grid->SetRowData(j+1,1);
		if(j==4)
			m_Grid->SetRowData(j+1,2);
		if(j==5)
			m_Grid->SetRowData(j+1,3);
		if(j==2)
		{
			Value=Value.Left(10);
			m_Grid->SetRowData(j+1,8);
		}
		m_Grid->SetTextMatrix(j+1,1,Value);
	}
	RS.Close();
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	pView->GetTreeCtrl().GetItemImage(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem()),Typ,Typ);
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	if(Typ==EANTDN)
	{
		m_Grid->SetRow(4);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetCol(1);
		m_Grid->SetRow(9);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetCol(2);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetCol(0);
	}
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(6);
	m_Grid->SetCellFontBold(true);
	if(Typ==EANTUP)
	{
		m_Grid->SetRow(9);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetCol(1);
		m_Grid->SetRow(4);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetCol(2);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetCol(0);
	}
//	m_Grid->SetRow(10);
//	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(11);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetCol(1);
	m_Grid->SetRow(10);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(1);
	m_Grid->SetRow(11);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	long ntcID=pView->GetTreeCtrl().GetItemData(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem())));
	CString Ctry;
	SQL.Format(_T("select ctry from e_stn where ntc_id=%ld"),ntcID);
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,Ctry);
	RS.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	CDBVariant TempVar;
	CString m_Tbl,F1,F2;
	m_Tbl.Format(_T("SELECT op_agcy, op_agcy_name from op_agcy where adm='%s'"),Ctry);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		int f11;
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		f11=atoi(F1);
		F1.Format(_T("%d"),f11);
		RS.GetFieldValue((short)1,F2);
		F2.TrimRight();
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	F1="9999 - "+_Z("Other");
	m_Combo1->AddString(F1);
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Tbl.Format(_T("SELECT cgad_addr_code,cgad_addr_naddr_1 from ctry_geo_area_addr,ctry_geo_area where cgad_cga_id=cga_id and cga_symbol='%s'"),Ctry);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		F2.TrimRight();
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	F1="XX - "+_Z("Other");
	m_Combo1->AddString(F1);
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Tbl.Format(_T("SELECT PolID, PolText%s from PolType"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::AddESGroup()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from grp where grp_id=-1"));
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Group information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	m_Grid->SetRows(RS.GetODBCFieldCount()-52);
	for(int i=1,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
		CODBCFieldInfo FldInfo;
		Value="";
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("grp"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(j==0)
			m_Grid->SetRowData(j+1,1);
		if(j==4)
			m_Grid->SetRowData(j+1,2);
		if(j==5)
			m_Grid->SetRowData(j+1,3);
		if(j==2)
		{
			CTime Today =CTime::GetCurrentTime();
			Value.Format(_T("%04d/%02d/%02d"),Today.GetYear(),Today.GetMonth(),Today.GetDay());
			m_Grid->SetRowData(j+1,8);
		}
//		if(i==17)
//			m_Grid->SetRowData(j+1,5);
//		if(i==10)
//			m_Grid->SetRowData(j+1,6);
		m_Grid->SetTextMatrix(j+1,1,Value);
	}
	RS.Close();
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	pView->GetTreeCtrl().GetItemImage(pView->GetTreeCtrl().GetSelectedItem(),Typ,Typ);
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	if(Typ==EANTDN)
	{
		m_Grid->SetRow(4);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetCol(1);
		m_Grid->SetRow(9);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetCol(2);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetCol(0);
	}
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(6);
	m_Grid->SetCellFontBold(true);
	if(Typ==EANTUP)
	{
		m_Grid->SetRow(9);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetCol(1);
		m_Grid->SetRow(4);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetCol(2);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetCol(0);
	}
//	m_Grid->SetRow(10);
//	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(11);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetCol(1);
	m_Grid->SetRow(10);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(1);
	m_Grid->SetRow(11);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	long ntcID=pView->GetTreeCtrl().GetItemData(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem()));
	CString Ctry;
	SQL.Format(_T("select ctry from e_stn where ntc_id=%ld"),ntcID);
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,Ctry);
	RS.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	CDBVariant TempVar;
	CString m_Tbl,F1,F2;
	m_Tbl.Format(_T("SELECT op_agcy, op_agcy_name from op_agcy where adm='%s'"),Ctry);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		int f11;
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		f11=atoi(F1);
		F1.Format(_T("%d"),f11);
		RS.GetFieldValue((short)1,F2);
		F2.TrimRight();
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	F1="9999 - "+_Z("Other");
	m_Combo1->AddString(F1);
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Tbl.Format(_T("SELECT cgad_addr_code,cgad_addr_naddr_1 from ctry_geo_area_addr,ctry_geo_area where cgad_cga_id=cga_id and cga_symbol='%s'"),Ctry);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		F2.TrimRight();
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	F1="XX - "+_Z("Other");
	m_Combo1->AddString(F1);
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Tbl.Format(_T("SELECT PolID, PolText%s from PolType"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

bool CTreeviewView::ESGrpSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[70], Values[70], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()==0x7F7F7F)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	Values[0].Format(_T("%ld"),m_RecID);
	if(Values[1].IsEmpty())
		Missing= m_Grid->GetTextMatrix(1,0) + ",";
	if(Values[2].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(2,0) + ",";
	if(Values[3].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	if(m_Action==1) // Add new
		pView->GetTreeCtrl().GetItemImage(pView->GetTreeCtrl().GetSelectedItem(),Typ,Typ);
	else
		pView->GetTreeCtrl().GetItemImage(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem()),Typ,Typ);
	if(Typ==EANTDN)
	{
		if(Values[4].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(4,0) + ",";
	}
	if(Values[5].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(5,0) + ",";
	if(Values[6].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(6,0) + ",";
	if(Typ==EANTUP)
	{
		if(Values[9].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(9,0) + ",";
	}
/*	if(Values[10].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(10,0) + ",";
	if(Values[11].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(11,0) + ",";*/
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else 
	{
//		double sgn;
		int Part1=Values[1].Find(_T("-"),0)-1,
			Part2=Values[5].Find(_T("-"),0)-1,
			Part3=Values[6].Find(_T("-"),0)-1;
		if(Part1<0)
			Part1=Values[1].GetLength();
		if(Part2<0)
			Part2=Values[5].GetLength();
		if(Part3<0)
			Part3=Values[6].GetLength();
		if(m_Action==1) // Add new
		{
//			if(ESGrpValidation(Values))
			{
				CString NewID,emi_rcp,bname;
				SQL=_T("Select max(grp_id)+1 from grp");
				RS.Open(CRecordset::snapshot,SQL);
				RS.GetFieldValue((short)0,NewID);
				RS.Close();
				if(NewID.IsEmpty()) NewID=_T("1");
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				SQL.Format(_T("select emi_rcp,beam_name from e_ant where AntID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
				RS.Open(CRecordset::snapshot,SQL);
				RS.GetFieldValue((short)0,emi_rcp);
				RS.GetFieldValue(1,bname);
				RS.Close();
				SQL.Format(_T("select %s,%ld,'%s','%s','%s',%s,'%s',%s,%s,'%s',%s,'%s',%s,%s,%s,%ld "),NewID, 
					pView->GetTreeCtrl().GetItemData(pView->GetTreeCtrl().GetParentItem(Node)),	emi_rcp, bname, Values[1].Left(Part1), 
					(Values[2].IsEmpty()?_T("NULL"):Values[2]), Values[3], (Values[4].IsEmpty()?_T("NULL"):Values[4]), 
					Values[5].Left(Part2),Values[6].Left(Part3),(Values[7].IsEmpty()?_T("NULL"):Values[7]),Values[8],
					(Values[9].IsEmpty()?_T("NULL"):Values[9]),(Values[10].IsEmpty()?_T("NULL"):Values[10]),
					(Values[11].IsEmpty()?_T("NULL"):Values[11]),pView->GetTreeCtrl().GetItemData(Node));
				SQL=_T("insert into grp (grp_id,ntc_id,emi_rcp,beam_name,adm_resp,bdwdth,d_inuse,noise_t,op_agcy,polar_type,polar_ang,remark,pwr_max,freq_min,freq_max,AntID) ")+SQL;
				DB.ExecuteSQL(SQL);
				Node=pView->GetTreeCtrl().InsertItem(_Z("Group: ")+NewID,GROUP,GROUP,pView->GetTreeCtrl().GetSelectedItem());
				pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
				pView->GetTreeCtrl().Select(Node,TVGN_CARET);
				m_Refresh=false;
				pView->RedrawWindow();
				AddTrail(_Z("Add earth station group"),atol((LPCTSTR)NewID),_T("grp"));
			}
//			else
//				result=false;
		}
		else    // Update
		{
			SQL.Format(_T("Select * from grp where grp_id=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
//			if(ESGrpValidation(Values))
			{
				SQL1.Format(_T("UPDATE grp SET adm_resp = '%s', "), Values[1].Left(Part1));
				SQL2=SQL1;
				SQL1.Format(_T("bdwdth = %s, d_inuse = '%s', "), (Values[2].IsEmpty()?_T("NULL"):Values[2]), Values[3]);
				SQL2+=SQL1;
				SQL1.Format(_T("noise_t = %s, op_agcy = '%s', "), (Values[4].IsEmpty()?_T("NULL"):Values[4]), Values[5].Left(Part2));
				SQL2+=SQL1;
				SQL1.Format(_T("polar_type = '%s', polar_ang = %s, "), Values[6].Left(Part3),(Values[7].IsEmpty()?_T("NULL"):Values[7]));
				SQL2+=SQL1;
				SQL1.Format(_T("remark = '%s', pwr_max = %s, "), Values[8],(Values[9].IsEmpty()?_T("NULL"):Values[9]));
				SQL2+=SQL1;
				SQL1.Format(_T("freq_min = %s, freq_max = %s "), (Values[10].IsEmpty()?_T("NULL"):Values[10]),(Values[11].IsEmpty()?_T("NULL"):Values[11]));
				SQL2+=SQL1;
				SQL1.Format(_T("WHERE grp_id=%ld"), m_RecID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Group: ")+Fields[0]);

				AddTrail(_Z("Update earth station group"),m_RecID,_T("grp"));
				result=true;
			}
//			else
//				result=false;
		}
	}
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

void CTreeviewView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	RECT rcl;

	// Get the client area of the parent window.
	GetClientRect(&rcl);
	if(m_loaded)
	{
//		m_Refresh=true;
		m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
		CRect Rect;
		((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->GetWindowRect(&Rect);
		ScreenToClient(&Rect);
		m_Grid->SetWindowPos(NULL,0,Rect.bottom,rcl.right,rcl.bottom-Rect.bottom ,SWP_NOZORDER);
		((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowPos(NULL,0,0,rcl.right,20 ,SWP_NOZORDER);
		OnClickGrid();
	}
}

CString CTreeviewView::GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit, CString *Format, CString *Srv, CString *Mask)
{
	CRecordset	RS;
	RS.m_pDatabase=DB;
	CString FieldName,SQL;
	SQL.Format(_T("Select * from Fields where TableName='%s' and FieldName='%s'"), Table, OrigName);
	RS.Open(CRecordset::dynaset,SQL);
//	LangCode=/*((CSMS4DCApp *)AfxGetApp())->*/m_Lang;
	if(RS.GetRecordCount()>0)
	{
		if(m_Lang==_T("En"))
			RS.GetFieldValue(2,FieldName);
		if(m_Lang==_T("Fr"))
			RS.GetFieldValue(3,FieldName);
		if(m_Lang==_T("Es"))
			RS.GetFieldValue(4,FieldName);
		if(m_Lang==_T("Ch"))
			RS.GetFieldValue(5,FieldName);
		if(m_Lang==_T("Ru"))
			RS.GetFieldValue(6,FieldName);
		if(m_Lang==_T("Ar"))
			RS.GetFieldValue(7,FieldName);
		RS.GetFieldValue(8,*Unit);
		RS.GetFieldValue(9,*Srv);
		RS.GetFieldValue(10,*Mask);
		RS.GetFieldValue(11,*Format);
	}
	else
	{
		*Srv=_T("-");
	}
	RS.Close();
	return FieldName;
}

BEGIN_EVENTSINK_MAP(CTreeviewView, CFormView)
    //{{AFX_EVENTSINK_MAP(CTreeviewView)
//	ON_EVENT(CTreeviewView, IDC_GRID, -600 /* Click */, OnClickGrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTreeviewView::OnClickGrid()
{
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_EditBox=(CMSMask *)GetDlgItem(IDC_EDITBOX);
	m_EditBox->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_NormalEdit=(CEdit *)GetDlgItem(IDC_NORMALEDIT);
	m_NormalEdit->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO9);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO10);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_DATEPICKER);
	m_Date->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_TIMEPICKER);
	m_Date->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
//	m_Grid->SetFocus();
//	m_OnEdit=false;
	if(m_OnEdit==false && !m_ReadOnly && m_Grid->GetCol()==2 && m_Grid->GetCellBackColor()==0xFFFFFF && m_Grid->GetRowData(m_Grid->GetRow())>=100)
	{
		m_OnEdit=false;

		 switch(m_Grid->GetRowData(m_Grid->GetRow())/100)
		 {
		 case 1:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 2:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 3:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 4:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 5:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 6:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 7:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 8:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 9:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO9);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 case 10:
			m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO10);
			m_Combo1->SelectString(0,m_Grid->GetText());
			m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
			((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
			(m_Grid->GetCellWidth()* m_nLogX)/1440+1, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
			SWP_SHOWWINDOW);
			m_Combo1->SetFocus();
			break;
		 }
		 m_OnEdit=true;
	}
	else
		m_OnEdit=false;
}


BOOL CTreeviewView::PreTranslateMessage(MSG* pMsg) 
{
	bool NoReturn=false;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_DATEPICKER);
	m_EditBox=(CMSMask *)GetDlgItem(IDC_EDITBOX);
	m_NormalEdit=(CEdit *)GetDlgItem(IDC_NORMALEDIT);
	if(pMsg->message==WM_KEYDOWN)
	{
		///if(pMsg->wParam==13 || pMsg->wParam==9 || pMsg->wParam==27)
		//if(pMsg->wParam==13 || pMsg->wParam==9 || pMsg->wParam==27 || (pMsg->wParam>='a' && pMsg->wParam<='z') || 
		//	(pMsg->wParam>='A' && pMsg->wParam<='Z') || (pMsg->wParam>='1' && pMsg->wParam<='0'))
		{
			if((pMsg->wParam==13 || pMsg->wParam==9 || pMsg->wParam==27) && m_OnEdit) // && !((pMsg->wParam>='a' && pMsg->wParam<='z') || (pMsg->wParam>='A' && pMsg->wParam<='Z') || (pMsg->wParam>='1' && pMsg->wParam<='0')))
			{
				long RowData=m_Grid->GetRowData(m_Grid->GetRow());
				CString Text;
				if(m_Grid->GetCol()==2)
				{
					switch(RowData/100)
					{
					case 1:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 2:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					}
				}
				else
				{
					switch(RowData%100)
					{
					case 0:
						{
						CString Val;
						int decimal;
						int Dec=atoi(m_Mask[1][m_Grid->GetRow()].Right(m_Mask[1][m_Grid->GetRow()].GetLength()-1));
						///*if(pMsg->wParam==13)*/ m_Grid->SetText(m_EditBox->GetFormattedText());
//						if(pMsg->wParam==13) m_Grid->SetText(m_EditBox->GetText());
						Val=m_EditBox->GetFormattedText();
						if(m_Mask[1][m_Grid->GetRow()].Left(1)==_T("N"))
						{
							if((decimal=m_Mask[1][m_Grid->GetRow()].Find(_T("."),1))==-1)
								Val.Format(_T("%ld"),atol(Val));
							else
								Val.Format(_T("%*.*lf"),Dec,atoi(m_Mask[1][m_Grid->GetRow()].Mid(decimal+1)),atof(Val));
						}
						m_Grid->SetText(Val);
						}
						m_EditBox->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 1:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 2:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 3:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 4:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 5:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 6:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 7:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 8:
						m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_DATEPICKER);
						m_Date->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Date->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 9:
						m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_TIMEPICKER);
						m_Date->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Date->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 10:
						m_NormalEdit->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_NormalEdit->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 11:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 12:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO9);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					case 13:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO10);
						m_Combo1->GetWindowText(Text);
						/*if(pMsg->wParam==13)*/ m_Grid->SetText(Text);
						m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
						m_OnEdit=false;
						break;
					}
				}
				m_Grid->SetFocus();
			}
			else
			{
			//	if(pMsg->wParam==13 && m_Grid->GetCellBackColor()==0xFFFFFF && m_Grid->GetCol()==1) 
				if(!m_OnEdit && (m_Grid->GetCellBackColor()==0xFFFFFF && m_Grid->GetCol()==1) && (pMsg->wParam==13 || 
					(pMsg->wParam>='a' && pMsg->wParam<='z') || (pMsg->wParam>='A' && pMsg->wParam<='Z') || 
					(pMsg->wParam>='1' && pMsg->wParam<='0')))
				{
					CString Dt;
					RECT rcl,GrdRect;
					GetClientRect(&rcl);
					long ColWdthSum=m_Grid->GetColWidth(0,0), DiffWdth;
					for(int i=1;i<m_Grid->GetCols(0);i++)
						if(m_Grid->GetColIsVisible(i))
							ColWdthSum+=m_Grid->GetColWidth(i,0);
					int Sc=0;
					m_Grid->GetWindowRect(&GrdRect);
					//if(m_Grid->GetScrollBars()==1)
					if(rcl.bottom<GrdRect.bottom-GrdRect.top)
						Sc=15;
					DiffWdth=(ColWdthSum*m_nLogX)/1440-rcl.right+Sc;
					CTime tm;
					if(DiffWdth<0)
						DiffWdth=0;
					 switch(m_Grid->GetRowData(m_Grid->GetRow())%100)
					 {
					 case 0:
						m_EditBox->SetText("");
						 m_EditBox->SetMask("");
						 m_EditBox->SetFormat("");
						 m_EditBox->SetMask(m_Mask[0][m_Grid->GetRow()]);
						if(m_Mask[1][m_Grid->GetRow()].Left(1)==_T("N"))
						{
							CString buf,num;

							CString Val;
							int decimal,decimal2;
							int Dec=atoi(m_Mask[1][m_Grid->GetRow()].Right(m_Mask[1][m_Grid->GetRow()].GetLength()-1));
							Val=m_Grid->GetText();
							if((decimal=m_Mask[1][m_Grid->GetRow()].Find(_T("."),1))==-1)
							{
								//if(pMsg->wParam==13)
									Val.Format(_T("%ld"),atol(Val));
								//else
								//	Val.Format(_T("%ld%c"),atol(Val),pMsg->wParam);
								m_EditBox->SetSelStart(0);
								m_EditBox->SetSelLength(Val.GetLength());
								m_EditBox->SetSelText(Val);
							}
							else
							{
								decimal2=atoi(m_Mask[1][m_Grid->GetRow()].Mid(decimal+1));
								//if(pMsg->wParam==13)
									Val.Format(_T("%*.*lf"),Dec,decimal2,atof(Val));
								//else
								//	Val.Format(_T("%*.*lf%c"),Dec,decimal2,atof(Val),pMsg->wParam);
								decimal2=Dec-decimal2-1;
								buf=Val;
								buf.TrimLeft(_T(" "));
								buf.TrimRight(_T("0"));
								num=buf;
								Dec=atoi(m_Mask[1][m_Grid->GetRow()].Right(m_Mask[1][m_Grid->GetRow()].GetLength()-1));
								decimal=buf.Find(_T("."),1);
								//if(decimal==-1)   decimal=buf.GetLength();
								//if(decimal==0)
								//	m_EditBox->SetSelStart(0);
								//else
									m_EditBox->SetSelStart(decimal2-decimal);
								m_EditBox->SetSelLength(num.GetLength());
								m_EditBox->SetSelText(num);
							}
//							m_EditBox->SetText(m_Grid->GetText());
						}
						else
						{
							//if(pMsg->wParam==13)
								Dt.Format(_T("%s"),m_Grid->GetText());
							//else
							//	Dt.Format(_T("%c%s"),pMsg->wParam,m_Grid->GetText());
							m_EditBox->SetText(Dt);
						}
//						 m_EditBox->SetFormat(m_Mask[1][m_Grid->GetRow()]);
						m_EditBox->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
							((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
							(m_Grid->GetCellWidth()* m_nLogX)/1440-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
							SWP_SHOWWINDOW);
						m_EditBox->SetFocus();
						//Dt=m_EditBox->GetText();
						//Dt=(char)pMsg->wParam+Dt;
						//m_EditBox->SetText(Dt);
						break;
					 case 1:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 2:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 3:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 4:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 5:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 6:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 7:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 8:
						 {
							Dt=m_Grid->GetText();
							m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_DATEPICKER);
							CTime tm(atoi(Dt.Left(4)), atoi(Dt.Mid(5,2)), atoi(Dt.Right(2)), 0, 0, 0);
							m_Date->SetFormat(_T("yyyy/MM/dd"));
							m_Date->SetTime(&tm);
							m_Date->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
							((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
							(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
							SWP_SHOWWINDOW);
							m_Date->SetFocus();
						 }
						break;
					 case 9:
						 {
							Dt=m_Grid->GetText();
							m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_TIMEPICKER);
							CTime tm2(2005, 2, 2, atoi(Dt.Left(2)), atoi(Dt.Right(2)), 0);
							m_Date->SetTime(&tm2);
							m_Date->SetFormat(_T("HH:mm"));
							m_Date->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
							((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
							(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
							SWP_SHOWWINDOW);
							m_Date->SetFocus();
						 }
						 break;
					 case 10:
						m_NormalEdit=(CEdit *)GetDlgItem(IDC_NORMALEDIT);
			 			m_NormalEdit->SetWindowText(m_Grid->GetText());
						m_NormalEdit->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_NormalEdit->SetFocus();
						break;
					 case 11:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 12:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO9);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 case 13:
						m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO10);
			 			m_Combo1->SelectString(0,m_Grid->GetText());
						m_Combo1->SetWindowPos(&CWnd::wndTop, ((m_Grid->GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
						((m_Grid->GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
						(m_Grid->GetCellWidth()* m_nLogX)/1440+1-DiffWdth, (m_Grid->GetCellHeight()* m_nLogY)/1440+1,
						SWP_SHOWWINDOW);
						m_Combo1->SetFocus();
						break;
					 }//switch
					 m_OnEdit=true;
				}
			}
		}
	}
	if(pMsg->message==WM_LBUTTONUP)
	{
		if(pMsg->hwnd==((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->m_hWnd && /*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6)
		{
			CString Title;
			((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->GetWindowText(Title);
			if(Title==_Z("Modify"))
				ModifyData();
			else
				PrintBill();
		}
		if(pMsg->hwnd==((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->m_hWnd)
		{
			m_OnEdit=true;
			CString Title;
			((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->GetWindowText(Title);
			if(Title==_Z("Delete"))
			{
				//	if(m_UserLevel==3 || m_UserLevel==4) DeletePayment();
			}
			else
			{
				OnClickGrid();
				bool result;
				switch(m_RecordType)
				{
				case OWNER: result=OwnerSave();
							break;
				case LICENSE: result=LicenseSave();
							break;
				case STATION: result=StationSave();
							break;
				case BC:	result=BCSave();
							break;
				case MOBILE:result=MobileSave();
							break;
				case EQUIPMENT:result=EquipmentSave();
							break;
				case ANTENNA:result=AntennaSave();
							break;
				case FREQUENCY:result=FrequencySave();
								break;
				case ESTATION:result=ESSave();
								break;
				case EANTDN:
				case EANTUP:result=ESAntSave();
								break;
				case GROUP:result=ESGrpSave();
								break;
				case ALLOTMENT: result=AllotSave();
								break;
				case CONTOUR: result=ContourSave();
								break;
				}
				if(result)
				{
					m_ReadOnly=true;
	//				OnClickGrid();
					m_Refresh=true;
					CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
					CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
					pView->GetTreeCtrl().EnableWindow(true);
					m_Action=0;  // View
					RedrawWindow();
					((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(true);
					((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
					((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
				}
			}
		}
		if(pMsg->hwnd==((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->m_hWnd)
		{
			m_Refresh=true;
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			pView->GetTreeCtrl().EnableWindow(true);
			OnClickGrid();
			if(m_Action==1)
			{
				if(m_Table==_T("Eant"))
				{
					CString NewID,SQL;
					CDatabase DB;
					CRecordset RS;
					RS.m_pDatabase=&DB;
					DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
					SQL=_T("select max(AntID)+1 from e_ant");
					RS.Open(CRecordset::snapshot,SQL);
					RS.GetFieldValue((short)0,NewID);
					RS.Close();
					if(NewID.IsEmpty()) NewID=_T("1");
					RS.Close();
					SQL.Format(_T("delete * from ESAntPatt where AntID=%s "),NewID);
					DB.ExecuteSQL(SQL);
					DB.Close();
				}
				m_RecID=m_OldRecID;
				m_Table=m_OldTable;
				m_RecordType=m_OldRecordType;
			}
			m_ReadOnly=true;
			OnClickGrid();
			m_Action=0;  // View
			RedrawWindow();
			((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(true);
			((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(false);
			((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(false);
		}
		if(pMsg->hwnd==((CButton *)GetDlgItem(IDC_ATTACH))->m_hWnd && /*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6)
		{
			OnClickGrid();
			if(m_Table==_T("Equipment"))
			{
				CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
				CCatSelect CatDlg;
				CatDlg.m_CDBSTR=Temp;
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				pView->GetTreeCtrl().GetItemImage(Node,CatDlg.m_typ,CatDlg.m_typ);
				if(CatDlg.m_typ==EQUIPMENT)
				{
					Node=pView->GetTreeCtrl().GetParentItem(Node);
					pView->GetTreeCtrl().GetItemImage(Node,CatDlg.m_typ,CatDlg.m_typ);
				}
				CatDlg.m_ID=pView->GetTreeCtrl().GetItemData(Node);
				CatDlg.m_Table=m_Table;
				CatDlg.m_EqGrid=m_Grid;
				//CatDlg.m_Srv=m_Service;
				CatDlg.DoModal();
				m_CatID=CatDlg.m_CatID;
				NoReturn=true;
				//m_Refresh=true;
				//m_ReadOnly=true;
				//m_Action=0;
				//RedrawWindow();
			}
			if(m_Table==_T("Antenna"))
			{
				CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
				CCatSelect CatDlg;
				CatDlg.m_CDBSTR=Temp;
				HTREEITEM Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem());
				pView->GetTreeCtrl().GetItemImage(Node,CatDlg.m_typ,CatDlg.m_typ);
				if(CatDlg.m_typ==EQUIPMENT)
				{
					Node=pView->GetTreeCtrl().GetParentItem(Node);
					pView->GetTreeCtrl().GetItemImage(Node,CatDlg.m_typ,CatDlg.m_typ);
				}
				CatDlg.m_ID=pView->GetTreeCtrl().GetItemData(Node);
				CatDlg.m_Table=m_Table;
				CatDlg.m_EqGrid=m_Grid;
				//CatDlg.m_Srv=m_Service;
				CatDlg.DoModal();
				m_CatID=CatDlg.m_CatID;
				NoReturn=true;
				//m_Refresh=true;
				//m_ReadOnly=true;
				//m_Action=0;
				//RedrawWindow();
			}
			if(m_Table==_T("Frequency"))
			{
				CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, Button;
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
				CReceivers RecDlg;
				RecDlg.m_Lang=m_Lang;
				RecDlg.m_CDBSTR=Temp;
				int Typ;
				RecDlg.m_ID=m_RecID;
				pView->GetTreeCtrl().GetItemImage(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem())),Typ,Typ);
//				if(!(Typ==MOBILE || m_Service==_T("B")))
//				{
					RecDlg.m_TreeView=pView;
					RecDlg.m_Srv=m_Service;
					if(Typ==MOBILE)
						RecDlg.m_STTP=_T("ML");
					else
						if(Typ==STATION && m_Service==_T("MT"))
							RecDlg.m_STTP=_T("FB");
						else if(Typ==STATION && m_Service==_T("F"))
								RecDlg.m_STTP=_T("FX");
							else
								RecDlg.m_STTP=_T("");
//					GetDlgItem(IDC_ATTACH)->GetWindowText(Button);
//					if(Button==_T("Service area"))
//						RecDlg.m_IsTypical=true;
//					else
					RecDlg.m_IsTypical=false;
					RecDlg.DoModal();
//				}
				NoReturn=true;
			}
			if(m_Table==_T("Eant"))
			{
				CString Temp=m_CDBSTR,SQL;
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
				CCatSelect CatDlg;
				CatDlg.m_CDBSTR=Temp;
				HTREEITEM Node=/*pView->GetTreeCtrl().GetParentItem(*/pView->GetTreeCtrl().GetSelectedItem();
				pView->GetTreeCtrl().GetItemImage(Node,CatDlg.m_typ,CatDlg.m_typ);
				CatDlg.m_ID=pView->GetTreeCtrl().GetItemData(Node);
				CatDlg.m_Table=m_Table;
				CatDlg.m_EqGrid=m_Grid;
				//CatDlg.m_Srv=m_Service;
				CatDlg.DoModal();
				CDatabase DB;
				m_CatID=CatDlg.m_CatID;
				DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
				SQL.Format(_T("delete * from ESAntPatt where AntID=%ld "),CatDlg.m_ID);
				DB.ExecuteSQL(SQL);
				NoReturn=true;
			}
		}
		if(pMsg->hwnd==((CButton *)GetDlgItem(IDC_ANTENNA))->m_hWnd && /*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6)
		{
			OnClickGrid();
			if(m_Table==_T("Eant"))
			{
				CString Temp=m_CDBSTR;
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
				CGrpDetails	GrpDlg;
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				if(m_Action!=1)
				{
					int BeamType;
					pView->GetTreeCtrl().GetItemImage(pView->GetTreeCtrl().GetParentItem(Node),BeamType,BeamType);
					if(BeamType==EANTUP)
						GrpDlg.m_BeamType=1;
					else
						GrpDlg.m_BeamType=2;
					GrpDlg.m_Grp_id=pView->GetTreeCtrl().GetItemData(Node);
				}
				else
				{
					CString NewID,SQL;
					if(m_Grid->GetTextMatrix(1,1)==_T("E"))
						GrpDlg.m_BeamType=1;
					else
						GrpDlg.m_BeamType=2;
					CDatabase DB;
					CRecordset RS;
					RS.m_pDatabase=&DB;
					DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
					SQL=_T("select max(AntID)+1 from e_ant");
					RS.Open(CRecordset::snapshot,SQL);
					RS.GetFieldValue((short)0,NewID);
					RS.Close();
					if(NewID.IsEmpty()) NewID=_T("1");
					RS.Close();
					DB.Close();
					GrpDlg.m_Grp_id=atol(NewID);
				}
				GrpDlg.m_CDBSTR=Temp;
				GrpDlg.m_Lang=m_Lang;
				GrpDlg.m_Type=8;
				GrpDlg.DoModal();
				if(GrpDlg.m_DataSaved) m_CatID=0;
				NoReturn=true;
			}
			else
				AntAssign();
		}
		if(pMsg->hwnd==((CMSHFlexGrid *)GetDlgItem(IDC_GRID))->m_hWnd)
		{
			OnClickGrid();
		}
	}
	if(NoReturn)
		return true;
	else
		return CFormView::PreTranslateMessage(pMsg);
}

bool CTreeviewView::OwnerSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[20], Values[20], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0xFFFFFF)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	Values[0].Format(_T("%ld"),m_RecID);
	if(Values[1].IsEmpty())
		Missing= m_Grid->GetTextMatrix(1,0) + ",";
	if(Values[2].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(2,0) + ",";
	if(Values[3].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	if(Values[4].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(4,0) + ",";
	if(Values[11].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(11,0) + ",";
	if(Values[12].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(12,0) + ",";
	if(Values[13].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(14,0) + ",";
	if(Values[14].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(15,0) + ",";
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else if(OwnerValidation(Values))
	{
		int Part=Values[4].Find(_T("-"),0)-1;
		if(Part<0)
			Part=Values[4].GetLength();
		if(m_Action==1) // Add new
		{
			CString NewID;
			SQL=_T("Select max(id)+1 from Owner");
			RS.Open(CRecordset::dynaset,SQL);
			RS.GetFieldValue((short)0,NewID);
			RS.Close();
			if(NewID.IsEmpty()) NewID=_T("1");
			SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s' "),NewID, Values[1],
				Values[2],Values[3],Values[4].Left(Part),Values[5],Values[6],Values[7],Values[8],Values[9],Values[10],Values[11],Values[12],Values[13],Values[14]);
			SQL1=_T("insert into Owner (ID, AdmName, Address, City, Country, Telephone, Telex, Fax, Email, Remarks, Category, AddrCode, OpAgency, BillName, BillAddress) ")+SQL1;
			DB.ExecuteSQL(SQL1);
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			HTREEITEM Root1=pView->GetTreeCtrl().GetChildItem(pView->GetTreeCtrl().GetFirstVisibleItem()), Root2; //.GetChildItem(pView->GetTreeCtrl().GetSelectedItem()),Root2;
			Root1=pView->GetTreeCtrl().GetNextItem(Root1, TVGN_NEXT);  
			Root2=pView->GetTreeCtrl().GetNextItem(Root1, TVGN_NEXT);
			HTREEITEM Node=pView->GetTreeCtrl().InsertItem(_Z("Owner: ")+Values[1],OWNER,OWNER,Root2);
			pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
			Node=pView->GetTreeCtrl().InsertItem(_Z("Owner: ")+Values[1],OWNER,OWNER,Root1);
			pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
			pView->RedrawWindow();
			pView->GetTreeCtrl().Select(Node,TVGN_CARET);
			AddTrail(_Z("Add owner"),atol((LPCTSTR)NewID),"Owner");
		}
		else    // Update
		{
			SQL.Format(_T("Select * from Owner where ID=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(int i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			Values[0]=Fields[0];
			Values[4].MakeUpper();
			SQL1.Format(_T("UPDATE Owner SET AdmName = '%s', Address = '%s', City = '%s', "), Values[1], Values[2], Values[3]);
			SQL2=SQL1;
			SQL1.Format(_T("Country = '%s', Telephone = '%s', Telex = '%s', "), Values[4].Left(Part), Values[5], Values[6]);
			SQL2+=SQL1;
			SQL1.Format(_T("Fax = '%s', Email = '%s', Remarks = '%s', Category = '%s', "), Values[7], Values[8], Values[9], Values[10]);
			SQL2+=SQL1;
			SQL1.Format(_T("AddrCode = '%s', OpAgency = '%s', BillName = '%s', BillAddress = '%s' WHERE ID=%ld"), Values[11], Values[12], Values[13], Values[14], m_RecID);
			SQL2+=SQL1;
			DB.ExecuteSQL(SQL2);

			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Owner: ")+Values[1]);

			AddTrail(_Z("Update owner"),m_RecID,"Owner");
			result=true;
		}
	}
	else
		result=false;
	DB.Close();
//	m_Grid->SetRow(Row);
//	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::LicenseSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T("ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[20], Values[20], Missing,SQL1,SQL2;
	int i,j;
	for(i=1,j=4;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0xFFFFFF)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	CString Srv=Values[8].Left(2);
	Srv.TrimRight(_T(" "));
	Values[8]=Srv;
	Values[0].Format(_T("%ld"),m_RecID);
	if(Values[4].IsEmpty())
		Missing= m_Grid->GetTextMatrix(1,0) + ",";
	if(Values[5].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(2,0) + ",";
	if(Values[6].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	if(Values[7].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(4,0) + ",";
	if(Values[8].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(5,0) + ",";
	if(Values[9].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(7,0) + ",";
	if(Values[10].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(8,0) + ",";
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else
	{
		if(m_Action==1) // Add new
		{
			if(LicenseValidation(Values,Fields))
			{
				CString NewID;
				SQL=_T("Select max(Licid)+1 from License");
				RS.Open(CRecordset::dynaset,SQL);
				RS.GetFieldValue((short)0,NewID);
				RS.Close();
				if(NewID.IsEmpty()) NewID=_T("1");
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				SQL1.Format(_T("select %s,%ld,0,0,'%s','%s','%s','%s','%s','%s',%s "),NewID, pView->GetTreeCtrl().GetItemData(Node),
					Values[4],Values[5],Values[6],Values[7],Srv,Values[9],Values[10]);
				SQL1=_T("insert into License (LicID, AdmID, Archive, Grantable, LicNo, OpDate, ExpDate, Status, SrvID, InvPeriod, InitFee)")+SQL1;
				DB.ExecuteSQL(SQL1);
				Node=pView->GetTreeCtrl().InsertItem(_Z("License: ")+Values[4],LICENSE,LICENSE,pView->GetTreeCtrl().GetSelectedItem());
				pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
				pView->GetTreeCtrl().Select(Node,TVGN_CARET);
				m_Refresh=false;
				pView->RedrawWindow();
				AddTrail(_Z("Add license"),atol((LPCTSTR)NewID),_T("License"));
			}
			else
				result=false;
		}
		else    // Update
		{
			SQL.Format(_T("Select * from License where LicID=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			Values[10].MakeUpper();
			if(LicenseValidation(Values,Fields))
			{
				SQL1.Format(_T("UPDATE License SET LicNo = '%s', "), Values[4]);
				SQL2=SQL1;
				SQL1.Format(_T("OpDate = '%s', ExpDate = '%s', Status = '%s', "), Values[5], Values[6], Values[7]);
				SQL2+=SQL1;
				SQL1.Format(_T("SrvID = '%s', InvPeriod = '%s', InitFee = %s "), Srv, Values[9], Values[10]);
				SQL2+=SQL1;
				SQL1.Format(_T("WHERE LicID=%ld"), m_RecID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("License: ")+Values[4]);

				AddTrail(_Z("Update license"),m_RecID,_T("License"));
				result=true;
			}
			else
				result=false;
		}
	}
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::StationSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[30], Values[30], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=4;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0xFFFFFF)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	Values[0].Format(_T("%ld"),m_RecID);

	if(i<12) //Monitoring
	{
		if(Values[4].IsEmpty())
			Missing= m_Grid->GetTextMatrix(1,0) + ",";
		if(Values[5].IsEmpty())
			Missing= m_Grid->GetTextMatrix(2,0) + ",";
		if(Values[6].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(4,0) + ",";
		if(Values[7].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(5,0) + ",";
		if(Values[8].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(6,0) + ",";
		if(Values[9].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(7,0) + ",";
	//	if(Values[10].IsEmpty())
	//		Missing+= m_Grid->GetTextMatrix(8,0) + ",";
		if(Values[11].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(9,0) + ",";
	}
	else
	{
		if(Values[5].IsEmpty())
			Missing= m_Grid->GetTextMatrix(2,0) + ",";
		if(Values[6].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(3,0) + ",";
		if(Values[8].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(5,0) + ",";
	//	if(Values[9].IsEmpty())
	//		Missing+= m_Grid->GetTextMatrix(6,0) + ",";
		if(Values[10].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(8,0) + ",";
		if(Values[9]!=_T("Typical") || Values[17].IsEmpty())
		{
			if(Values[11].IsEmpty())
				Missing+= m_Grid->GetTextMatrix(9,0) + ",";
			if(Values[12].IsEmpty())
				Missing+= m_Grid->GetTextMatrix(10,0) + ",";
		}
		if(Values[13].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(11,0) + ",";
		if(Values[15].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(13,0) + ",";
		if(Values[16].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(15,0) + ",";
		if(Values[21].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(20,0) + ",";
	}
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else 
	{
		double sgn;
		int Part;
		if(m_Action==1) // Add new
		{
			if(StationValidation(Values))
			{
				CString NewID;
				SQL=_T("Select max(StID)+1 from Station");
				RS.Open(CRecordset::dynaset,SQL);
				RS.GetFieldValue((short)0,NewID);
				RS.Close();
				if(NewID.IsEmpty()) NewID=_T("1");
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				CString LAT=_T("NULL"), LON=_T("NULL");
				double TLAT =0;
				double TLON =0;
				if(Values[6]==_T("__"))
				{
					Part=Values[9].Find(_T("-"),0)-1;
					if(Part<0)
						Part=3;
					Values[9].MakeUpper();
					if(Values[7].Left(1)==_T("-")) sgn=-1.0;
					else							sgn=1.0;
					LAT.Format(_T("%lf"),(atof(Values[7].Left(3))+sgn*atof(Values[7].Mid(3,2))/60.+sgn*atof(Values[7].Mid(5,5))/3600.));
					if(Values[8].Left(1)==_T("-")) sgn=-1.0;
					else							sgn=1.0;
					LON.Format(_T("%lf"),(atof(Values[8].Left(4))+sgn*atof(Values[8].Mid(4,2))/60.+sgn*atof(Values[8].Mid(6,5))/3600.));
					SQL.Format(_T("select %s,%ld,'%s','%s',%s,%s,%s,'%s',%s,%s "),NewID, 
						pView->GetTreeCtrl().GetItemData(Node),	Values[4], Values[5], Values[6], 
						LAT,LON, Values[9].Left(Part), Values[10], Values[11]);
					SQL=_T("insert into Station (StID,LicID, SiteID, SiteName, ITURegion, GeoLat, GeoLon, Country, Radius, HeightASL) ")+SQL;
					DB.ExecuteSQL(SQL);
					Node=pView->GetTreeCtrl().InsertItem(_Z("Monitoring Station: ")+Values[5],MONITORING,MONITORING,pView->GetTreeCtrl().GetSelectedItem());
					pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
					pView->GetTreeCtrl().Select(Node,TVGN_CARET);
					m_Refresh=false;
					pView->RedrawWindow();
					AddTrail(_Z("Add monitoring station"),atol((LPCTSTR)NewID),"Station");
				}
				else
				{
					Part=Values[13].Find(_T("-"),0)-1;
					if(Part<0)
						Part=3;
					Values[13].MakeUpper();
					Values[8].MakeUpper();
					if(Values[9]!=_T("Typical") || Values[17].IsEmpty())
					{
						if(Values[11].Left(1)==_T("-")) sgn=-1.0;
						else							sgn=1.0;
						LAT.Format(_T("%lf"),(atof(Values[11].Left(3))+sgn*atof(Values[11].Mid(3,2))/60.+sgn*atof(Values[11].Mid(5,5))/3600.));
						if(Values[12].Left(1)==_T("-")) sgn=-1.0;
						else							sgn=1.0;
						LON.Format(_T("%lf"),(atof(Values[12].Left(4))+sgn*atof(Values[12].Mid(4,2))/60.+sgn*atof(Values[12].Mid(6,5))/3600.));
					}
					else
						Values[14]="";
					if(!Values[19].IsEmpty())
					{
						if(Values[19].Left(1)==_T("-")) sgn=-1.0;
						else							sgn=1.0;
						TLAT=(atof(Values[19].Left(3))+sgn*atof(Values[19].Mid(3,2))/60.+sgn*atof(Values[19].Mid(5,5))/3600.);
						Values[19].Format(_T("%lf"),TLAT);
					}
					if(!Values[20].IsEmpty())
					{
						if(Values[20].Left(1)==_T("-")) sgn=-1.0;
						else							sgn=1.0;
						TLON= (atof(Values[20].Left(4))+sgn*atof(Values[20].Mid(4,2))/60.+sgn*atof(Values[20].Mid(6,5))/3600.);
						Values[20].Format(_T("%lf"),TLON);
					}
					SQL.Format(_T("select %s,%ld,'','','%s','%s','%s','%s','%s','%s',%s,%s,%s,'%s',%s,%s,'%s','%s','%s',%s,%s,'%s' "),NewID, 
						pView->GetTreeCtrl().GetItemData(Node),	Values[4], Values[5], Values[6], Values[7], Values[8].Left(2), Values[9], 
						Values[10], LAT,LON, Values[13].Left(Part), (Values[14].IsEmpty()?"NULL":Values[14]), Values[15], Values[16], Values[17].Left(3), Values[18], 
						Values[19].IsEmpty()?_T("NULL"):Values[19], Values[20].IsEmpty()?_T("NULL"):Values[20], Values[21]);
					SQL=_T("insert into Station (StID,LicID, TerraKey, Assgn_ID,AdmRefID, SiteID, SiteName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, HeightASL, Provision, AreaOfTrans, NetID, trgLon, trgLat, NoticeType) ")+SQL;
					DB.ExecuteSQL(SQL);
					Node=pView->GetTreeCtrl().InsertItem(Values[8].Left(2)+_Z(" Station: ")+Values[6],STATION,STATION,pView->GetTreeCtrl().GetSelectedItem());
					pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
					pView->GetTreeCtrl().Select(Node,TVGN_CARET);
					m_Refresh=false;
					pView->RedrawWindow();
					AddTrail(_Z("Add fixed or base station"),atol((LPCTSTR)NewID),"Station");
				}
			}
			else
				result=false;
		}
		else    // Update
		{
			SQL.Format(_T("Select * from Station where StID=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			if(StationValidation(Values))
			{
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				CString LAT=_T("NULL"), LON=_T("NULL");
				double TLAT =0;
				double TLON =0;
				if(Values[6]==_T("__"))
				{
					Part=Values[9].Find(_T("-"),0)-1;
					if(Part<0)
						Part=3;
					Values[9].MakeUpper();
					if(Values[7].Left(1)==_T("-")) sgn=-1.0;
					else							sgn=1.0;
					LAT.Format(_T("%lf"),(atof(Values[7].Left(3))+sgn*atof(Values[7].Mid(3,2))/60.+sgn*atof(Values[7].Mid(5,5))/3600.));
					if(Values[8].Left(1)==_T("-")) sgn=-1.0;
					else							sgn=1.0;
					LON.Format(_T("%lf"),(atof(Values[8].Left(4))+sgn*atof(Values[8].Mid(4,2))/60.+sgn*atof(Values[8].Mid(6,5))/3600.));
					SQL1.Format(_T("UPDATE Station SET SiteID = '%s', SiteName = '%s', "), Values[4], Values[5]);
					SQL2=SQL1;
					SQL1.Format(_T("ITURegion = %s, GeoLat = %s, GeoLon = %s, Country = '%s', "), Values[6], LAT,LON, Values[9].Left(Part));
					SQL2+=SQL1;
					SQL1.Format(_T("Radius = %s, HeightASL = %s"), 
						(Values[10].IsEmpty()?"NULL":Values[10]), Values[11]);
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE StID=%ld"), m_RecID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);
					pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Monitoring Station: ")+Values[5]);
					m_Refresh=false;
					pView->RedrawWindow();
					AddTrail(_Z("Update monitoring station"),m_RecID,"Station");
					result=true;
				}
				else
				{
					Part=Values[13].Find(_T("-"),0)-1;
					if(Part<0)
						Part=3;
					Values[13].MakeUpper();
					Values[8].MakeUpper();
					CString LAT=_T("NULL"), LON=_T("NULL");
					if(Values[9]!=_T("Typical") || Values[17].IsEmpty())
					{
						if(Values[11].Left(1)==_T("-")) sgn=-1.0;
						else							sgn=1.0;
						LAT.Format(_T("%lf"),(atof(Values[11].Left(3))+sgn*atof(Values[11].Mid(3,2))/60.+sgn*atof(Values[11].Mid(5,5))/3600.));
						if(Values[12].Left(1)==_T("-")) sgn=-1.0;
						else							sgn=1.0;
						LON.Format(_T("%lf"),(atof(Values[12].Left(4))+sgn*atof(Values[12].Mid(4,2))/60.+sgn*atof(Values[12].Mid(6,5))/3600.));
					}
					else
						Values[14]="";
					double TLAT =0;
					double TLON =0;
					if(!Values[19].IsEmpty())
					{
						if(Values[19].Left(1)==_T("-")) sgn=-1.0;
						else							sgn=1.0;
						TLAT=(atof(Values[19].Left(3))+sgn*atof(Values[19].Mid(3,2))/60.+sgn*atof(Values[19].Mid(5,5))/3600.);
						Values[19].Format(_T("%lf"),TLAT);
					}
					if(!Values[20].IsEmpty())
					{
						if(Values[20].Left(1)==_T("-")) sgn=-1.0;
						else							sgn=1.0;
						TLON= (atof(Values[20].Left(4))+sgn*atof(Values[20].Mid(4,2))/60.+sgn*atof(Values[20].Mid(6,5))/3600.);
						Values[20].Format(_T("%lf"),TLON);
					}
					SQL1.Format(_T("UPDATE Station SET AdmRefID = '%s', SiteID = '%s', SiteName = '%s', "), Values[4], Values[5], Values[6]);
					SQL2=SQL1;
					SQL1.Format(_T("CallSign = '%s', ClassStation = '%s', StType = '%s', "), Values[7], Values[8].Left(2), Values[9]);
					SQL2+=SQL1;
					SQL1.Format(_T("ITURegion = %s, GeoLat = %s, GeoLon = %s, Country = '%s', "), Values[10], LAT,LON, Values[13].Left(Part));
					SQL2+=SQL1;
					SQL1.Format(_T("Radius = %s, HeightASL = %s, Provision = '%s', AreaOfTrans = '%s', NetID='%s', trgLon=%s, trgLat=%s, NoticeType='%s' "), 
						(Values[14].IsEmpty()?"NULL":Values[14]), Values[15], Values[16], Values[17].Left(3), Values[18], 
						Values[19].IsEmpty()?_T("NULL"):Values[19], Values[20].IsEmpty()?_T("NULL"):Values[20],Values[21]);
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE StID=%ld"), m_RecID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);

					CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
					CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
					pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),Values[8].Left(2)+_Z(" Station: ")+Values[6]);

					AddTrail(_Z("Update fixed or base station"),m_RecID,"Station");
					result=true;
				}
			}
			else
				result=false;
		}
	}
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::BCSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[35], Values[35], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=4;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0xFFFFFF)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	Values[8].MakeUpper();
	Values[13].MakeUpper();
	if(Values[5].IsEmpty())
		Missing= m_Grid->GetTextMatrix(2,0) + ",";
	if(Values[6].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	if(Values[8].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(5,0) + ",";
//	if(Values[9].IsEmpty())
//		Missing+= m_Grid->GetTextMatrix(6,0) + ",";
	if(Values[10].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(8,0) + ",";
	if(Values[11].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(9,0) + ",";
	if(Values[12].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(10,0) + ",";
	if(Values[13].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(11,0) + ",";
	if(Values[15].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(13,0) + ",";
	if(Values[16].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(15,0) + ",";
	if(Values[27].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(27,0) + ",";
	Values[27]=Values[27].Left(3);
/*	if(Values[16].Left(11)==_T("Geneva 2006L"))
	{
		if(Values[20].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(20,0) + ",";
		if(Values[21].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(21,0) + ",";
	}*/
	//if(Values[16].Left(12)==_T("Geneva 2006D"))
	if(strstr(_T("GT1 GS1 TB2 TB3 TB5"),Values[27]))
	{
		if(Values[20].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(20,0) + ",";
		if(Values[21].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(21,0) + ",";
		if(Values[4].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(1,0) + ",";
	}
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else 
	{
		double sgn;
		int Part=Values[13].Find(_T("-"),0)-1;
		if(Part<0)
			Part=3;
		if(Values[11].Left(1)==_T("-")) sgn=-1.0;
		else							sgn=1.0;
		double LAT = (atof(Values[11].Left(3))+sgn*atof(Values[11].Mid(3,2))/60.+sgn*atof(Values[11].Mid(5,5))/3600.);
		if(Values[12].Left(1)==_T("-")) sgn=-1.0;
		else							sgn=1.0;
		double LON = (atof(Values[12].Left(4))+sgn*atof(Values[12].Mid(4,2))/60.+sgn*atof(Values[12].Mid(6,5))/3600.);
		double TLAT =0;
		double TLON =0;
		if(!Values[18].IsEmpty())
		{
			if(Values[18].Left(1)==_T("-")) sgn=-1.0;
			else							sgn=1.0;
			TLAT=(atof(Values[18].Left(3))+sgn*atof(Values[18].Mid(3,2))/60.+sgn*atof(Values[18].Mid(5,5))/3600.);
			Values[18].Format(_T("%lf"),TLAT);
		}
		if(!Values[19].IsEmpty())
		{
			if(Values[19].Left(1)==_T("-")) sgn=-1.0;
			else							sgn=1.0;
			TLON= (atof(Values[19].Left(4))+sgn*atof(Values[19].Mid(4,2))/60.+sgn*atof(Values[19].Mid(6,5))/3600.);
			Values[19].Format(_T("%lf"),TLON);
		}
		if(m_Action==1) // Add new
		{
			if(BCValidation(Values,Fields))
			{
				CString NewID;
				SQL=_T("Select max(StID)+1 from BCStation");
				RS.Open(CRecordset::dynaset,SQL);
				RS.GetFieldValue((short)0,NewID);
				RS.Close();
				if(NewID.IsEmpty()) NewID=_T("1");
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				SQL.Format(_T("select %s,%ld,'','','%s','%s','%s','%s','%s','%s',%s,%lf,%lf,'%s',%s,%s,'%s','%s',%s,%s,%s,'%s','%s','%s','%s',%d,%d,'%s' "),NewID, 
					pView->GetTreeCtrl().GetItemData(Node),	Values[4], Values[5], Values[6], Values[7], Values[8].Left(2), Values[9], 
					Values[10], LAT,LON, Values[13].Left(Part), (Values[14].IsEmpty()?"0":Values[14]), (Values[15].IsEmpty()?_T("0"):Values[15]), 
					Values[16], Values[17], Values[18].IsEmpty()?_T("NULL"):Values[18], Values[19].IsEmpty()?_T("NULL"):Values[19],
					Values[20].IsEmpty()?_T("NULL"):Values[20],Values[21],Values[22],Values[23],Values[24],
					Values[25].Left(1)==_T("Y")?1:0,Values[26].Left(1)==_T("Y")?1:0,Values[27]);
				SQL=_T("SfnID, CondMet, SignedCommit, NoticeType ) ")+SQL;
				SQL=_T("GeoLat, GeoLon, Country, Radius, HeightASL, Provision, Plan, trgLon, trgLat, PlanEntry, AssignCode, AssocAllotID, AssocAllotSFN, ")+SQL;
				SQL=_T("insert into BCStation (StID,LicID, TerraKey, Assgn_ID,AdmRefID, SiteID, SiteName, CallSign, ClassStation, StType, ITURegion,")+SQL;
				
				DB.ExecuteSQL(SQL);
				Node=pView->GetTreeCtrl().InsertItem(Values[8].Left(2)+_Z(" Station: ")+Values[6],BC,BC,pView->GetTreeCtrl().GetSelectedItem());
				pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
				pView->GetTreeCtrl().Select(Node,TVGN_CARET);
				m_Refresh=false;
				pView->RedrawWindow();
				AddTrail(_Z("Add broadcasting station"),atol((LPCTSTR)NewID),"BCStation");
			}
			else
				result=false;
		}
		else    // Update
		{
			SQL.Format(_T("Select * from BCStation where StID=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(int i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			Values[0]=Fields[0];
			if(BCValidation(Values,Fields))
			{
				SQL1.Format(_T("UPDATE BCStation SET AdmRefID = '%s', SiteID = '%s', SiteName = '%s', "), Values[4], Values[5], Values[6]);
				SQL2=SQL1;
				SQL1.Format(_T("CallSign = '%s', ClassStation = '%s', StType = '%s', "), Values[7], Values[8].Left(2), Values[9]);
				SQL2+=SQL1;
				SQL1.Format(_T("ITURegion = %s, GeoLat = %lf, GeoLon = %lf, Country = '%s', "), Values[10], LAT,LON, Values[13].Left(Part));
				SQL2+=SQL1;
				SQL1.Format(_T("Radius = %s, HeightASL = %s, Provision = '%s', Plan = '%s', trgLon=%s, trgLat=%s, "), 
					(Values[14].IsEmpty()?"0":Values[14]), (Values[15].IsEmpty()?"0":Values[15]), Values[16], Values[17], 
					Values[18].IsEmpty()?_T("NULL"):Values[18], Values[19].IsEmpty()?_T("NULL"):Values[19]);
				SQL2+=SQL1;
				SQL1.Format(_T("PlanEntry= %s, AssignCode = '%s', AssocAllotID = '%s', AssocAllotSFN = '%s', SfnID='%s', CondMet=%d, SignedCommit=%d, NoticeType='%s'"),
					Values[20].IsEmpty()?_T("NULL"):Values[20],Values[21],Values[22],Values[23],Values[24],
					Values[25].Left(1)==_T("Y")?1:0,Values[26].Left(1)==_T("Y")?1:0,Values[27]);
				SQL2+=SQL1;
				SQL1.Format(_T("WHERE StID=%ld"), m_RecID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),Values[8].Left(2)+_Z(" Station: ")+Values[6]);

				AddTrail(_Z("Update broadcasting station"),m_RecID,"BCStation");
				result=true;
			}
			else
				result=false;
		}
	}
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::MobileSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[30], Values[30], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=2;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0xFFFFFF)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	Values[0].Format(_T("%ld"),m_RecID);
	Values[6].MakeUpper();
	Values[11].MakeUpper();
	if(Values[3].IsEmpty())
		Missing= m_Grid->GetTextMatrix(2,0) + ",";
	if(Values[4].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	if(Values[6].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(5,0) + ",";
//	if(Values[7].IsEmpty())
//		Missing+= m_Grid->GetTextMatrix(6,0) + ",";
	if(Values[8].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(8,0) + ",";
	if(Values[13].IsEmpty())
	{
		if(Values[9].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(9,0) + ",";
		if(Values[10].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(10,0) + ",";
	}
	if(Values[11].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(11,0) + ",";
	if(Values[15].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(16,0) + ",";
	if(Values[20].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(22,0) + ",";
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else if(MobileValidation(Values))
	{
		double sgn;
		int Part=Values[11].Find(_T("-"),0)-1;
		if(Part<0)
			Part=3;
		if(m_Action==1) // Add new
		{
			CString NewID;
			SQL=_T("Select max(MobID)+1 from Mobiles");
			RS.Open(CRecordset::dynaset,SQL);
			RS.GetFieldValue((short)0,NewID);
			RS.Close();
			if(NewID.IsEmpty()) NewID=_T("1");
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
			CString LAT=_T("NULL"), LON=_T("NULL");
			if(Values[13].IsEmpty())
			{
				if(Values[9].Left(1)==_T("-")) sgn=-1.0;
				else							sgn=1.0;
				LAT.Format(_T("%lf"),(atof(Values[9].Left(3))+sgn*atof(Values[9].Mid(3,2))/60.+sgn*atof(Values[9].Mid(5,5))/3600.));
				if(Values[10].Left(1)==_T("-")) sgn=-1.0;
				else							sgn=1.0;
				LON.Format(_T("%lf"),(atof(Values[10].Left(4))+sgn*atof(Values[10].Mid(4,2))/60.+sgn*atof(Values[10].Mid(6,5))/3600.));
			}
			else
				Values[12]="";
			SQL.Format(_T("select %s,%ld,'%s','%s','%s','%s','%s','%s',%s,%s,%s,'%s',%s,'%s',%s,'%s','%s','%s','%s','%s','%s' "),NewID, 
				pView->GetTreeCtrl().GetItemData(Node),	Values[2], Values[3], Values[4], Values[5], Values[6].Left(2), Values[7], 
				Values[8], LAT,LON, Values[11].Left(Part), (Values[12].IsEmpty()?"NULL":Values[12]), Values[13].Left(3),(Values[14].IsEmpty()?_T("0"):Values[14]), 
				Values[15], Values[16], Values[17],Values[18],Values[19], Values[20]);
			SQL=_T("insert into Mobiles (MobID,LicID, AdmRefID, MobileID, MobName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, AreaOfTrans, NoSets, Provision, NetID, VehModel, VehPlate, VehColor, NoticeType) ")+SQL;
			DB.ExecuteSQL(SQL);
			Node=pView->GetTreeCtrl().InsertItem(_Z("Mobile: ")+Values[4],MOBILE,MOBILE,pView->GetTreeCtrl().GetSelectedItem());
			pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
			pView->GetTreeCtrl().Select(Node,TVGN_CARET);
			m_Refresh=false;
			pView->RedrawWindow();
			AddTrail(_Z("Add mobile station"),atol((LPCTSTR)NewID),"Mobiles");
		}
		else    // Update
		{
			SQL.Format(_T("Select * from Mobiles where MobID=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(int i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			CString LAT=_T("NULL"), LON=_T("NULL");
			if(Values[13].IsEmpty())
			{
				if(Values[9].Left(1)==_T("-")) sgn=-1.0;
				else							sgn=1.0;
				LAT.Format(_T("%lf"),(atof(Values[9].Left(3))+sgn*atof(Values[9].Mid(3,2))/60.+sgn*atof(Values[9].Mid(5,5))/3600.));
				if(Values[10].Left(1)==_T("-")) sgn=-1.0;
				else							sgn=1.0;
				LON.Format(_T("%lf"),(atof(Values[10].Left(4))+sgn*atof(Values[10].Mid(4,2))/60.+sgn*atof(Values[10].Mid(6,5))/3600.));
			}
			else
				Values[12]="";
			SQL1.Format(_T("UPDATE Mobiles SET AdmRefID = '%s', MobileID = '%s', MobName = '%s', "), Values[2], Values[3], Values[4]);
			SQL2=SQL1;
			SQL1.Format(_T("CallSign = '%s', ClassStation = '%s', StType = '%s', "), Values[5], Values[6].Left(2), Values[7]);
			SQL2+=SQL1;
			SQL1.Format(_T("ITURegion = %s, GeoLat = %s, GeoLon = %s, Country = '%s', "), Values[8], LAT,LON, Values[11].Left(Part));
			SQL2+=SQL1;
			SQL1.Format(_T("Radius = %s, AreaOfTrans='%s',NoSets = %s, Provision = '%s', NetID = '%s', VehModel = '%s', "), 
				(Values[12].IsEmpty()?"NULL":Values[12]), Values[13].Left(3), (Values[14].IsEmpty()?"0":Values[14]), 
				Values[15], Values[16], Values[17]);
			SQL2+=SQL1;
			SQL1.Format(_T("VehPlate = '%s', VehColor = '%s', NoticeType='%s' WHERE MobID=%ld"), Values[18], Values[19], Values[20], m_RecID);
			SQL2+=SQL1;
			DB.ExecuteSQL(SQL2);
						
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Mobile: ")+Values[4]);

			AddTrail(_Z("Update mobile station"),m_RecID,"Mobiles");
			result=true;
		}
	}
	else
		result=false;
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::FrequencySave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL,StClass;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[25], Values[25], Missing,SQL1,SQL2,Prov,NoticeType;
	int j,i;
	for(i=1,j=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()==0x7F7F7F)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem());
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==EQUIPMENT)
	{
		Node=pView->GetTreeCtrl().GetParentItem(Node);
		pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	}
	if(Typ==STATION || Typ==MONITORING)
		SQL.Format(_T("Select ClassStation,provision, NoticeType from station where station.stid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	if(Typ==BC)
		SQL.Format(_T("Select ClassStation,provision, NoticeType from bcstation where bcstation.stid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	if(Typ==MOBILE)
		SQL.Format(_T("Select ClassStation,provision, NoticeType from mobiles where mobiles.mobid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,StClass);
	RS.GetFieldValue((short)1,Prov);
	RS.GetFieldValue((short)2,NoticeType);
	RS.Close();
	StClass=StClass.Left(2);
	if(m_Action==1)
		Node=pView->GetTreeCtrl().GetSelectedItem();
	else
		Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem());
	Values[0].Format(_T("%ld"),pView->GetTreeCtrl().GetItemData(Node));
	if(StClass==_T("BT"))
	{
		if(Values[1].IsEmpty())
			Missing= m_Grid->GetTextMatrix(1,0) + ",";
//		if(Values[2].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(2,0) + ",";
//		if(Values[3].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(3,0) + ",";
		if(Values[4].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(5,0) + ",";
		if(Values[5].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(6,0) + ",";
		//if(Prov.Left(11)==_T("Geneva 2006"))
		if(strstr(_T("DT1 DS1 GT1 GS1 TB2 TB3 TB5"),NoticeType))
		{
			if(Values[16].IsEmpty())
				Missing+= m_Grid->GetTextMatrix(18,0) + ",";
		}
//		if(Values[12].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(13,0) + ",";
		if(Values[12].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(13,0) + ",";
		if(Values[13].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(14,0) + ",";
		if(Values[14].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(16,0) + ",";
	}
	if(StClass==_T("BC"))
	{
		if(Values[1].IsEmpty())
			Missing= m_Grid->GetTextMatrix(1,0) + ",";
		if(Values[2].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(3,0) + ",";
		if(Values[3].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(4,0) + ",";
//		if(Values[9].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(10,0) + ",";
		if(Values[9].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(10,0) + ",";
		if(Values[10].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(11,0) + ",";
		if(Values[11].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(13,0) + ",";
		//if(Prov.Left(11)==_T("Geneva 2006"))
		if(strstr(_T("DT1 DS1 GT1 GS1 TB2 TB3 TB5"),NoticeType))
		{
			if(Values[13].IsEmpty())
				Missing+= m_Grid->GetTextMatrix(15,0) + ",";
		}
	}
	if(StClass==_T("FX") || StClass==_T("ML") || StClass==_T("FB"))
	{
		if(Values[1].IsEmpty())
			Missing= m_Grid->GetTextMatrix(1,0) + ",";
		if(Values[2].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(2,0) + ",";
		if(Values[5].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(6,0) + ",";
		if(Values[6].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(7,0) + ",";
		if(Values[11].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(12,0) + ",";
		if(Values[12].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(13,0) + ",";
		if(Values[13].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(14,0) + ",";
		if(Values[14].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(16,0) + ",";
	}
	if(Typ==MONITORING)
	{
		if(Values[1].IsEmpty())
			Missing= m_Grid->GetTextMatrix(1,0) + ",";
		if(Values[2].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(2,0) + ",";
		if(Values[5].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(6,0) + ",";
		if(Values[6].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(7,0) + ",";
	}

	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else if(FrequencyValidation(Values,StClass))
	{
		if(m_Action==1) // Add new
		{
			CString NewID;
			double Freq, ReFreq, RefFreq;
			Freq=atof((LPCTSTR)Values[1])*GetFreqUnit(m_Grid->GetTextMatrix(1,2));
			SQL=_T("Select max(Freqid)+1 from Frequency");
			RS.Open(CRecordset::dynaset,SQL);
			RS.GetFieldValue((short)0,NewID);
			RS.Close();
			if(NewID.IsEmpty()) NewID=_T("1");
			if(StClass==_T("BT"))
			{
				Values[11]=Values[11].Left(2);
				Values[11].TrimRight();
				SQL1.Format(_T("select %s,%ld,%lf,%s,%s,'%s',%s,%s,'%s',%s,'%s','%s','%s','%s','%s',%s,'%s',%s,'%s',%d "),NewID, pView->GetTreeCtrl().GetItemData(Node),
					Freq, (Values[2].IsEmpty()?_T("NULL"):Values[2]),(Values[3].IsEmpty()?_T("NULL"):Values[3]),
					Values[4], (Values[5].IsEmpty()?_T("NULL"):Values[5]), (Values[6].IsEmpty()?_T("NULL"):Values[6]),Values[7],
					(Values[8].IsEmpty()?_T("NULL"):Values[8]),Values[9],Values[10],Values[11].Left(2),
					Values[12],Values[13],(Values[14].IsEmpty()?_T("NULL"):Values[14]),BWCode(atof((Values[5].IsEmpty()?_T("NULL"):Values[5])))+Values[4],
					(Values[15].IsEmpty()?_T("NULL"):Values[15]),Values[16],atoi(Values[17]));
				SQL1=_T("insert into Frequency (FreqID, EqID, Frequency, FreqVCarr, FreqSCarr, EmissionCl,BandWidth, ChannelSep, TVChan, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee,EmDes,trgFrequency,SpectMask,Offset) ")+SQL1;
			}
			if(StClass==_T("BC"))
			{
				Values[8]=Values[8].Left(3);
				Values[8].TrimRight();
				SQL1.Format(_T("select %s,%ld,%lf,'%s',%s,%s,%s,'%s','%s','%s','%s','%s',%s,'%s',%s,'%s',%d "),NewID, pView->GetTreeCtrl().GetItemData(Node),
					Freq, 
					Values[2], (Values[3].IsEmpty()?_T("NULL"):Values[3]), (Values[4].IsEmpty()?_T("0"):Values[4]),
					(Values[5].IsEmpty()?_T("NULL"):Values[5]),Values[6],Values[7],Values[8].Left(2),Values[9],
					Values[10],(Values[11].IsEmpty()?_T("NULL"):Values[11]),BWCode(atof((Values[3].IsEmpty()?_T("NULL"):Values[3])))+Values[2],
					(Values[12].IsEmpty()?_T("NULL"):Values[12]),Values[13],atoi(Values[14]));
				SQL1=_T("insert into Frequency (FreqID, EqID, Frequency, EmissionCl,BandWidth, ChannelSep, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee,EmDes,trgFrequency,SpectMask,Offset) ")+SQL1;
			}
			if(StClass==_T("FX"))
			{
				Values[11]=Values[11].Left(2);
				Values[11].TrimRight();
				ReFreq=atof((LPCTSTR)Values[2])*GetFreqUnit(m_Grid->GetTextMatrix(2,2));
				RefFreq=atof((LPCTSTR)Values[3])*GetFreqUnit(m_Grid->GetTextMatrix(3,2));
				SQL1.Format(_T("select %s,%ld,%lf,%lf,%lf,%s,'%s',%s,%s,%s,'%s','%s','%s','%s','%s',%s,'%s',%s "),NewID, pView->GetTreeCtrl().GetItemData(Node),
					Freq, ReFreq,RefFreq,(Values[4].IsEmpty()?_T("NULL"):Values[4]),
					Values[5], (Values[6].IsEmpty()?_T("NULL"):Values[6]), (Values[7].IsEmpty()?_T("NULL"):Values[7]),
					(Values[8].IsEmpty()?_T("NULL"):Values[8]),Values[9],Values[10],Values[11].Left(2),Values[12],Values[13],
					(Values[14].IsEmpty()?_T("NULL"):Values[14]),BWCode(atof((Values[6].IsEmpty()?_T("NULL"):Values[6])))+Values[5],
					(Values[15].IsEmpty()?_T("NULL"):Values[15]));
				SQL1=_T("insert into Frequency (FreqID, EqID, Frequency, RespFreq, RefFreq, FreqDev, EmissionCl,BandWidth, ChannelSep, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee,EmDes,trgFrequency) ")+SQL1;
			}
			if(StClass==_T("ML") || StClass==_T("FB"))
			{
				Values[11]=Values[11].Left(2);
				Values[11].TrimRight();
				ReFreq=atof((LPCTSTR)Values[2])*GetFreqUnit(m_Grid->GetTextMatrix(2,2));
				RefFreq=atof((LPCTSTR)Values[3])*GetFreqUnit(m_Grid->GetTextMatrix(3,2));
				SQL1.Format(_T("select %s,%ld,%lf,%lf,%lf,'%s','%s',%s,%s,%s,'%s','%s','%s','%s','%s',%s,'%s',%s "),NewID, pView->GetTreeCtrl().GetItemData(Node),
					Freq, ReFreq,RefFreq,(Values[4].IsEmpty()?_T("NULL"):Values[4]),
					Values[5], (Values[6].IsEmpty()?_T("NULL"):Values[6]), (Values[7].IsEmpty()?_T("NULL"):Values[7]),
					(Values[8].IsEmpty()?_T("NULL"):Values[8]),Values[9],Values[10],Values[11].Left(2),Values[12],Values[13],
					(Values[14].IsEmpty()?_T("NULL"):Values[14]),BWCode(atof((Values[6].IsEmpty()?_T("NULL"):Values[6])))+Values[5],
					(Values[15].IsEmpty()?_T("NULL"):Values[15]));
				SQL1=_T("insert into Frequency (FreqID, EqID, Frequency, RespFreq, RefFreq, FreqRange, EmissionCl,BandWidth, ChannelSep, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee,EmDes,trgFrequency) ")+SQL1;
			}
			if(Typ==MONITORING)
			{
				Values[11]=Values[11].Left(2);
				Values[11].TrimRight();
				ReFreq=atof((LPCTSTR)Values[2])*GetFreqUnit(m_Grid->GetTextMatrix(2,2));
				RefFreq=atof((LPCTSTR)Values[3])*GetFreqUnit(m_Grid->GetTextMatrix(3,2));
				SQL1.Format(_T("select %s,%ld,%lf,%lf,%lf,'%s','%s',%s,%s,'%s' "),NewID, pView->GetTreeCtrl().GetItemData(Node),
					Freq, ReFreq,RefFreq,(Values[4].IsEmpty()?_T("NULL"):Values[4]),
					Values[5], (Values[6].IsEmpty()?_T("NULL"):Values[6]), (Values[7].IsEmpty()?_T("NULL"):Values[7]),
					BWCode(atof((Values[6].IsEmpty()?_T("NULL"):Values[6])))+Values[5]);
				SQL1=_T("insert into Frequency (FreqID, EqID, Frequency, RespFreq, RefFreq, FreqRange, EmissionCl,BandWidth, ChannelSep, EmDes) ")+SQL1;
			}
			DB.ExecuteSQL(SQL1);
			CString FreqStr;
			FreqStr.Format(_T("%f"),Freq/1000000.);
			FreqStr.TrimLeft(_T(" "));
			FreqStr.TrimRight(_T("0"));
			FreqStr+=_T(" MHz");
			Node=pView->GetTreeCtrl().InsertItem(_Z("Frequency: ")+FreqStr,FREQUENCY,FREQUENCY,pView->GetTreeCtrl().GetSelectedItem());
			pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
			pView->GetTreeCtrl().Select(Node,TVGN_CARET);
			m_Refresh=false;
			pView->RedrawWindow();
			AddTrail(_Z("Add frequency"),atol((LPCTSTR)NewID),"Frequency");
		}
		else    // Update
		{
			SQL.Format(_T("Select * from Frequency where FreqID=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(int i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			double Freq, ReFreq, RefFreq;
			Freq=atof((LPCTSTR)Values[1])*GetFreqUnit(m_Grid->GetTextMatrix(1,2));
			ReFreq=atof((LPCTSTR)Values[2])*GetFreqUnit(m_Grid->GetTextMatrix(2,2));
			RefFreq=atof((LPCTSTR)Values[3])*GetFreqUnit(m_Grid->GetTextMatrix(3,2));
			if(ReFreq==0) ReFreq=Freq;

			if(StClass==_T("BT"))
			{
				Values[11]=Values[11].Left(2);
				Values[11].TrimRight();
				SQL1.Format(_T("UPDATE Frequency SET Frequency = %lf, FreqVCarr=%s, FreqSCarr=%s, "),
					Freq,(Values[2].IsEmpty()?_T("0"):Values[2]),(Values[3].IsEmpty()?_T("0"):Values[3]));
				SQL2=SQL1;
				SQL1.Format(_T(" EmissionCl='%s',BandWidth=%s, ChannelSep=%s, TVChan='%s', "), 
					Values[4], (Values[5].IsEmpty()?_T("0"):Values[5]), (Values[6].IsEmpty()?_T("0"):Values[6]),Values[7]);
				SQL2+=SQL1;
				SQL1.Format(_T("Traffic = %s, PeakHour = '%s', Season = '%s', NatServ = '%s', "), 
					(Values[8].IsEmpty()?"0":Values[8]), Values[9], Values[10], Values[11].Left(2));
				SQL2+=SQL1;
				SQL1.Format(_T("HourFrom='%s', HourTo='%s', FreqFee = %s, EmDes='%s', trgFrequency=%s, SpectMask='%s', offset=%d WHERE FreqID=%ld"), 
					Values[12],Values[13],(Values[14].IsEmpty()?"NULL":Values[14]),BWCode(atof((Values[5].IsEmpty()?_T("NULL"):Values[5])))+Values[4],
					(Values[15].IsEmpty()?_T("NULL"):Values[15]), Values[16], atoi(Values[17]), m_RecID);
				SQL2+=SQL1;
			}
			if(StClass==_T("BC"))
			{
				Values[8]=Values[8].Left(2);
				Values[8].TrimRight();
				SQL1.Format(_T("UPDATE Frequency SET Frequency = %lf, "),Freq);
				SQL2=SQL1;
				SQL1.Format(_T(" EmissionCl='%s',BandWidth=%s, ChannelSep=%s, "), 
					Values[2], (Values[3].IsEmpty()?_T("0"):Values[3]), (Values[4].IsEmpty()?_T("0"):Values[4]));
				SQL2+=SQL1;
				SQL1.Format(_T("Traffic = %s, PeakHour = '%s', Season = '%s', NatServ = '%s', "), 
					(Values[5].IsEmpty()?"0":Values[5]), Values[6], Values[7], Values[8].Left(2));
				SQL2+=SQL1;
				SQL1.Format(_T("HourFrom='%s', HourTo='%s', FreqFee = %s, EmDes='%s', trgFrequency=%s, SpectMask='%s', offset=%d WHERE FreqID=%ld"), 
					Values[9],Values[10],(Values[11].IsEmpty()?"0":Values[11]),BWCode(atof((Values[3].IsEmpty()?_T("0"):Values[3])))+Values[2],
					(Values[12].IsEmpty()?_T("NULL"):Values[12]), Values[13], atoi(Values[14]), m_RecID);
				SQL2+=SQL1;
			}
			if(StClass==_T("FX"))
			{
				Values[11]=Values[11].Left(2);
				Values[11].TrimRight();
				SQL1.Format(_T("UPDATE Frequency SET Frequency = %lf, RespFreq = %lf, RefFreq = %lf, "), 
					Freq, ReFreq, RefFreq);
				SQL2=SQL1;
				SQL1.Format(_T("FreqDev = %s, EmissionCl='%s', "),(Values[4].IsEmpty()?"NULL":Values[4]), Values[5]);
				SQL2+=SQL1;
				SQL1.Format(_T(" BandWidth=%s, ChannelSep=%s, "), 
					(Values[6].IsEmpty()?_T("NULL"):Values[6]), (Values[7].IsEmpty()?_T("NULL"):Values[7]));
				SQL2+=SQL1;
				SQL1.Format(_T("Traffic = %s, PeakHour = '%s', Season = '%s', NatServ = '%s', "), 
					(Values[8].IsEmpty()?"NULL":Values[8]), Values[9], Values[10], Values[11].Left(2));
				SQL2+=SQL1;
				SQL1.Format(_T("HourFrom='%s', HourTo='%s', FreqFee = %s, EmDes='%s',trgFrequency=%s WHERE FreqID=%ld"), 
					Values[12],Values[13],(Values[14].IsEmpty()?"NULL":Values[14]),BWCode(atof((Values[6].IsEmpty()?_T("NULL"):Values[6])))+Values[5], 
					(Values[15].IsEmpty()?_T("NULL"):Values[15]),m_RecID);
				SQL2+=SQL1;
			}
			if(StClass==_T("ML") || StClass==_T("FB"))
			{
				Values[11]=Values[11].Left(2);
				Values[11].TrimRight();
				SQL1.Format(_T("UPDATE Frequency SET Frequency = %lf, RespFreq = %lf, RefFreq = %lf, "), 
					Freq, ReFreq, RefFreq);
				SQL2=SQL1;
				SQL1.Format(_T("FreqRange = '%s', EmissionCl='%s', "),	Values[4], Values[5]);
				SQL2+=SQL1;
				SQL1.Format(_T("BandWidth=%s, ChannelSep=%s, "), 
					(Values[6].IsEmpty()?_T("0"):Values[6]), (Values[7].IsEmpty()?_T("0"):Values[7]));
				SQL2+=SQL1;
				SQL1.Format(_T("Traffic = %s, PeakHour = '%s', Season = '%s', NatServ = '%s', "), 
					(Values[8].IsEmpty()?"0":Values[8]), Values[9], Values[10], Values[11].Left(2));
				SQL2+=SQL1;
				SQL1.Format(_T("HourFrom='%s', HourTo='%s', FreqFee = %s, EmDes='%s',trgFrequency=%s WHERE FreqID=%ld"), 
					Values[12],Values[13],(Values[14].IsEmpty()?"NULL":Values[14]),BWCode(atof((Values[6].IsEmpty()?_T("NULL"):Values[6])))+Values[5], 
					(Values[15].IsEmpty()?_T("NULL"):Values[15]),m_RecID);
				SQL2+=SQL1;
			}
			if(Typ==MONITORING)
			{
				SQL1.Format(_T("UPDATE Frequency SET Frequency = %lf, RespFreq = %lf, RefFreq = %lf, "), 
					Freq, ReFreq, RefFreq);
				SQL2=SQL1;
				SQL1.Format(_T("FreqRange = '%s', EmissionCl='%s', "),	Values[4], Values[5]);
				SQL2+=SQL1;
				SQL1.Format(_T("BandWidth=%s, ChannelSep=%s, "), 
					(Values[6].IsEmpty()?_T("0"):Values[6]), (Values[7].IsEmpty()?_T("0"):Values[7]));
				SQL2+=SQL1;
				SQL1.Format(_T("EmDes='%s' WHERE FreqID=%ld"), 
					BWCode(atof((Values[6].IsEmpty()?_T("NULL"):Values[6])))+Values[5],m_RecID);
				SQL2+=SQL1;
			}
			DB.ExecuteSQL(SQL2);

			CString FreqStr;
			FreqStr.Format(_T("%f"),Freq/1000000.);
			FreqStr.TrimLeft(_T(" "));
			FreqStr.TrimRight(_T("0"));
			FreqStr+=_T(" MHz");
						
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Frequency: ")+FreqStr);
			AddTrail(_Z("Update frequency"),m_RecID,"Frequency");

			result=true;
		}
	}
	else
		result=false;
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::EquipmentSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL,StClass;
	CString NewID,CatID;
	double ERP;
	bool result=true;
	int Over=false;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[50], Values[50], Missing,SQL1,SQL2,Prov, Part,NoticeType;
	int j,i;
	for(i=1,j=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0xFFFFFF)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(_T(" "));
		Values[j].TrimRight(_T(" "));
		j++;
	}
	Values[0].Format(_T("%ld"),m_CatID);
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==EQUIPMENT)
	{
		Node=pView->GetTreeCtrl().GetParentItem(Node);
		pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	}
	if(Typ==STATION || Typ==MONITORING)
		SQL.Format(_T("Select ClassStation,provision,NoticeType from station where station.stid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	if(Typ==BC)
		SQL.Format(_T("Select ClassStation,provision,NoticeType from bcstation where bcstation.stid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	if(Typ==MOBILE)
		SQL.Format(_T("Select ClassStation,provision,NoticeType from mobiles where mobiles.mobid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,StClass);
	RS.GetFieldValue((short)1,Prov);
	RS.GetFieldValue((short)2,NoticeType);
	RS.Close();
	StClass=StClass.Left(2);
	if(Values[1].IsEmpty())
		Missing= m_Grid->GetTextMatrix(1,0) + ",";
	if(Values[2].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	if(Values[3].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(4,0) + ",";
	if(Typ==MONITORING)
	{
		if(Values[9].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(12,0) + ",";
	}
	if(StClass==_T("BT"))
	{
		//if(Prov.Left(12)!=_T("Geneva 2006D"))
		if(!strstr(_T("DT1 DS1 GT1 GS1 TB2 TB3 TB5"),NoticeType))
		{
			if(Values[7].IsEmpty() && Values[8].IsEmpty())
			{
				Part.Format(_T("%s ,"),m_Grid->GetTextMatrix(10,0));
				Missing+=Part;
			}
			if(Values[9].IsEmpty() && Values[10].IsEmpty())
			{
				Part.Format(_T("%s ,"),m_Grid->GetTextMatrix(12,0));
				Missing+=Part;
			}
			CString Value=Values[11].Left(2);
			Value.TrimRight();
			if(Value.Left(1)!=_T("T"))
			{
				SQL.Format(_T("select count(ColCode) from ColorSys where ColCode='%s' and ColNameEn='%s'"),Value,Values[12]);
				RS.Open(CRecordset::snapshot,SQL);
				RS.GetFieldValue((short)0,Value);
				if(Value==_T("0"))
				{
					Missing+=_Z("The combination of TV and Color systems is not valid,");
				}
				RS.Close();
				if(Values[11].Left(1)!=_T("T") && (atof(Values[15])>23 || atof(Values[15])<5))
				{
					Missing+=_Z("The power ratio is not correct according to the TV system,");
				}
			}
///			else
///			{
//			if(Values[17].IsEmpty())
//				Missing+= m_Grid->GetTextMatrix(21,0) + ","; // Frequency Stability
///			}

			if(Values[11].IsEmpty())
				Missing+= m_Grid->GetTextMatrix(14,0) + ",";
			if(Values[12].IsEmpty())
				Missing+= m_Grid->GetTextMatrix(15,0) + ",";
		}
		else
		{
			if(Values[18].IsEmpty() && (Values[19].IsEmpty() || Values[20].IsEmpty()))
			{
				Part.Format(_Z("%s or %s and %s ,"),m_Grid->GetTextMatrix(23,0),
					m_Grid->GetTextMatrix(24,0),m_Grid->GetTextMatrix(25,0));
				Missing+= Part;
			}
		}
//		if(Values[13].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(19,0) + ",";
//		if(Values[14].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(20,0) + ",";
	}
	if(StClass==_T("BC"))
	{
		//if(Prov.Left(11)!=_T("Geneva 2006"))
		if(!strstr(_T("DT1 DS1 GT1 GS1 TB2 TB3 TB5"),NoticeType))
		{
			if(Values[7].IsEmpty())
				Missing+= m_Grid->GetTextMatrix(10,0) + ",";
		}
		else
		{
			if(Values[11].IsEmpty())
				Missing+= m_Grid->GetTextMatrix(15,0) + ",";
		}
//		if(Values[8].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(12,0) + ",";
//		if(Values[9].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(13,0) + ",";
	}
	if(StClass==_T("FX"))
	{
		if(Values[9].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(12,0) + ",";
	}
	if(StClass==_T("FX") || StClass==_T("ML") || StClass==_T("FB"))
	{
//		if(Prov.Left(11)==_T("Geneva 2006"))
		if(strstr(_T("G11 G12 G13 G14"),NoticeType))
		{
			if(StClass==_T("FX"))
			{
				if(Values[12].IsEmpty() && Values[13].IsEmpty())
					Missing+=_Z("System Type ,");
			}
			else
			{
				if(Values[9].IsEmpty() && Values[10].IsEmpty())
					Missing+=_Z("System Type ,");
			}
		}
		if(Values[4].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(5,0) + ",";
		if(Values[5].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(6,0) + ",";
	}
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else if(EquipmentValidation(Values,StClass))
	{
		if(m_Action==1) // Add new
		{
			if(m_CatID>-1)
				Over=AfxMessageBox(_Z("Overwrite existing data in library?"),MB_YESNO|MB_ICONWARNING);

			if(m_CatID==-1 || Over==IDNO)
			{
				SQL1=_T("Select max(EqCatID)+1 from EqCat");
				RS.Open(CRecordset::dynaset,SQL1);
				RS.GetFieldValue((short)0,CatID);
				RS.Close();
				if(CatID.IsEmpty()) CatID=_T("1");
				Values[8].MakeUpper();
				if(StClass==_T("BC"))
				{
/*					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,%s,%s,%s "),CatID,
						Values[1], Values[3], Values[5], 
						Values[6], Values[7],	Values[8], 
						(Values[9].Left(1).IsEmpty()?_T("1"):Values[9].Left(1)),
						(Values[10].IsEmpty()?"0":Values[10]), (Values[11].IsEmpty()?"0":Values[11]), 
						(Values[12].IsEmpty()?"0":Values[12]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, TranSys, ERP_h_dbw, ");
					SQL2+=_T("ERP_v_dbw, EU_Ref) ");*/
					if(!Values[8].IsEmpty())    ERP=atof(Values[8]);
					if(!Values[9].IsEmpty())    ERP=atof(Values[9]);
					if(!Values[8].IsEmpty() && !Values[9].IsEmpty())
						ERP=10.*log10( pow(10.,atof(Values[8])/10.) + pow(10.,atof(Values[9])/10.) );
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s',%s,%s,%s,%s,%lf,'%s','%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[4], Values[5],	Values[6], 
						(Values[7].Left(1).IsEmpty()?_T("1"):Values[7].Left(1)),
						(Values[8].IsEmpty()?"NULL":Values[8]), (Values[9].IsEmpty()?"NULL":Values[9]), 
						(Values[10].IsEmpty()?"NULL":Values[10]),ERP,Values[11], Values[12], Values[13], 
						(Values[14].IsEmpty()?"NULL":Values[14]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, TranSys, ERP_h_dbw, ");
					SQL2+=_T("ERP_v_dbw, EU_Ref, ERP_dbw, RefPlanCfg, SysVar, RXMode, MaxPowDens) ");
				}
				if(StClass==_T("BT"))
				{
/*					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,%s,%s,%s,'%s','%s',%s,%s,%s,%s,%s,'%s' "),CatID,
						Values[1], Values[3].Left(1), Values[5].Left(1), 
						Values[6], Values[7], Values[8], 
						(Values[9].IsEmpty()?"0":Values[9]), (Values[10].IsEmpty()?"0":Values[10]),
						(Values[11].IsEmpty()?"0":Values[11]), (Values[12].IsEmpty()?"0":Values[12]), 
						Values[13].Left(2),Values[14],
						(Values[15].IsEmpty()?"0":Values[15]), (Values[16].IsEmpty()?"0":Values[16]), (Values[17].IsEmpty()?"0":Values[17]),
						(Values[18].IsEmpty()?"0":Values[18]), (Values[19].IsEmpty()?"0":Values[19]), Values[20]);
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, OsetV12, OsetV, OsetS12, OsetS, TVSys, ColorSys, ERP_h_dbw, ");
					SQL2+=_T("ERP_v_dbw, ERP_dbw, PwrRatio, EU_Ref, FreqStabl) ");*/
					if(!Values[13].IsEmpty())    ERP=atof(Values[13]);
					if(!Values[14].IsEmpty())    ERP=atof(Values[14]);
					if(!Values[13].IsEmpty() && !Values[14].IsEmpty())
						ERP=10.*log10(pow(10.,atof(Values[13])/10.)+pow(10.,atof(Values[14])/10.));
					Values[11]=Values[11].Left(2);
					Values[11].TrimRight();
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s',%s,%s,%s,%s,'%s','%s',%s,%s,%s,%s,'%s',%lf,'%s','%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[4], Values[5], Values[6],  
						(Values[7].IsEmpty()?"NULL":Values[7]), (Values[8].IsEmpty()?"NULL":Values[8]),
						(Values[9].IsEmpty()?"NULL":Values[9]), (Values[10].IsEmpty()?"NULL":Values[10]), 
						Values[11].Left(2),Values[12],
						(Values[13].IsEmpty()?"NULL":Values[13]), (Values[14].IsEmpty()?"NULL":Values[14]), 
						(Values[15].IsEmpty()?"NULL":Values[15]), (Values[16].IsEmpty()?"NULL":Values[16]), Values[17],ERP,
						Values[18], Values[19], Values[20], (Values[21].IsEmpty()?_T("NULL"):Values[21]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, OsetV12, OsetV, OsetS12, OsetS, TVSys, ColorSys, ERP_h_dbw, ");
					SQL2+=_T("ERP_v_dbw, PwrRatio, EU_Ref, FreqStabl,ERP_dbw, RefPlanCfg, SysVar, RXMode, MaxPowDens) ");
				}
				if(StClass==_T("FX"))
				{
					Values[12]=Values[12].Left(3);
					Values[12].TrimRight();
					Values[13]=Values[13].Left(3);
					Values[13].TrimRight();
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,'%s',%s,'%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1),  
						Values[5].Left(1), Values[6], Values[7], Values[8], 
						(Values[9].IsEmpty()?"NULL":Values[9]), (Values[10].IsEmpty()?_T("NULL"):Values[10]),
						(Values[11].IsEmpty()?_T("NULL"):Values[11]),Values[12].Left(3),Values[13].Left(3),
						(Values[14].IsEmpty()?_T("NULL"):Values[14]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, Sensitivity, EnDisp,NoiseFactor,SystemType1,SystemType2, MaxPowDens) ");
				}
				if(StClass==_T("FB"))
				{
					Values[10]=Values[10].Left(3);
					Values[10].TrimRight();
					Values[11]=Values[11].Left(3);
					Values[11].TrimRight();
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,'%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[5].Left(1), 
						Values[6], Values[7],	Values[8], (Values[9].IsEmpty()?"NULL":Values[9]),Values[10].Left(3),
						Values[11].Left(3),(Values[12].IsEmpty()?_T("NULL"):Values[12]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo,Sensitivity,SystemType1,SystemType2,MaxPowDens) ");
				}
				if(StClass==_T("ML"))
				{
					Values[10]=Values[10].Left(3);
					Values[10].TrimRight();
					Values[11]=Values[11].Left(3);
					Values[11].TrimRight();
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,'%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[5].Left(1), 
						Values[6], Values[7], Values[8], (Values[9].IsEmpty()?"NULL":Values[9]),Values[10].Left(3),
						Values[11].Left(3),(Values[12].IsEmpty()?_T("NULL"):Values[12]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, Sensitivity,SystemType1,SystemType2,MaxPowDens) ");
				}
				if(Typ==MONITORING)
				{
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[5].Left(1), 
						Values[6], Values[7],	Values[8], (Values[9].IsEmpty()?"NULL":Values[9]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo,Sensitivity) ");
				}
				SQL1=SQL2+SQL1;
				DB.ExecuteSQL(SQL1);
			}
			else
			{
//				SQL.Format(_T("Select * from Equipment, EqCat where Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), m_RecID);
//				RS.Open(CRecordset::dynaset,SQL);
//				for(int i=0;i<RS.GetODBCFieldCount();i++)
//					RS.GetFieldValue(i,Fields[i]);
//				RS.Close();
				CatID.Format(_T("%ld"),m_CatID);
				Values[8].MakeUpper();
				if(StClass==_T("BC"))
				{
					if(!Values[8].IsEmpty())    ERP=atof(Values[8]);
					if(!Values[9].IsEmpty())    ERP=atof(Values[9]);
					if(!Values[8].IsEmpty() && !Values[9].IsEmpty())
						ERP=10.*log10(pow(10.,atof(Values[8])/10.)+pow(10.,atof(Values[9])/10.));
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3].Left(1));
					SQL2+=SQL1;
//					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
//						Values[5].Left(1), Values[6], Values[7]);
					SQL1.Format(_T("MadeBy = '%s', Model = '%s', "), Values[4], Values[5]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[6]);
					SQL2+=SQL1;
					SQL1.Format(_T(" TranSys=%s, "), (Values[7].Left(1).IsEmpty()?_T("1"):Values[7].Left(1)));
					SQL2+=SQL1;
					SQL1.Format(_T(" ERP_h_dbw = %s, ERP_v_dbw = %s, ERP_dbw=%lf, "), 
						(Values[8].IsEmpty()?"NULL":Values[8]), (Values[9].IsEmpty()?"NULL":Values[9]),ERP);
					SQL2+=SQL1;
					SQL1.Format(_T("EU_Ref = %s ,RefPlanCfg='%s', SysVar='%s', RXMode='%s', MaxPowDens=%s "), 
						(Values[10].IsEmpty()?"NULL":Values[10]),Values[11],Values[12],Values[13],
						(Values[14].IsEmpty()?"NULL":Values[14]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%ld"),m_CatID);
				}
				if(StClass==_T("BT"))
				{
					if(!Values[13].IsEmpty())    ERP=atof(Values[13]);
					if(!Values[14].IsEmpty())    ERP=atof(Values[14]);
					if(!Values[13].IsEmpty() && !Values[14].IsEmpty())
						ERP=10.*log10(pow(10.,atof(Values[13])/10.)+pow(10.,atof(Values[14])/10.));
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3].Left(1));
					SQL2+=SQL1;
//					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
//						Values[5].Left(1), Values[6], Values[7]);
					SQL1.Format(_T("MadeBy = '%s', Model = '%s', "), Values[4], Values[5]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', OsetV12 =%s, "), 
						Values[6], (Values[7].IsEmpty()?"NULL":Values[7]));
					SQL2+=SQL1;
					Values[11]=Values[11].Left(2);
					Values[11].TrimRight();
					SQL1.Format(_T("OsetV = %s, OsetS12 = %s, OsetS = %s, TVSys = '%s', "), (Values[8].IsEmpty()?"NULL":Values[8]), 
						(Values[9].IsEmpty()?"NULL":Values[9]), (Values[10].IsEmpty()?"NULL":Values[10]), 
						Values[11].Left(2));
					SQL2+=SQL1;
					SQL1.Format(_T("ColorSys = '%s', ERP_h_dbw = %s, ERP_v_dbw = %s, ERP_dbw=%lf, "), Values[12], 
						(Values[13].IsEmpty()?"NULL":Values[13]), (Values[14].IsEmpty()?"NULL":Values[14]),ERP);
					SQL2+=SQL1;
					SQL1.Format(_T("PwrRatio = %s, EU_Ref = %s, "), (Values[15].IsEmpty()?"NULL":Values[15]), 
						(Values[16].IsEmpty()?"NULL":Values[16]));
					SQL2+=SQL1;
					SQL1.Format(_T(" FreqStabl = '%s',RefPlanCfg='%s', SysVar='%s', RXMode='%s', MaxPowDens=%s "), 
						Values[17],Values[18], Values[19], Values[20],(Values[21].IsEmpty()?"NULL":Values[21]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%ld"), m_CatID);
				}
				if(StClass==_T("FX"))
				{
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3]);
					SQL2+=SQL1;
					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
						 Values[5], Values[6], Values[7]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[8]);
					SQL2+=SQL1;
					Values[12]=Values[12].Left(3);
					Values[12].TrimRight();
					Values[13]=Values[13].Left(3);
					Values[13].TrimRight();
					SQL1.Format(_T("Sensitivity = %s, EnDisp = '%s', NoiseFactor=%s ,SystemType1='%s',SystemType2='%s', MaxPowDens=%s "), 
						(Values[9].IsEmpty()?"NULL":Values[9]), Values[10],
						(Values[11].IsEmpty()?_T("NULL"):Values[11]),Values[12].Left(3),Values[13].Left(3),
						(Values[14].IsEmpty()?_T("NULL"):Values[14]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%ld"),m_CatID);
				}
				if(StClass==_T("FB"))
				{
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3]);
					SQL2+=SQL1;
					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
						Values[5], Values[6], Values[7]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[8]);
					SQL2+=SQL1;
					Values[10]=Values[10].Left(3);
					Values[10].TrimRight();
					Values[11]=Values[11].Left(3);
					Values[11].TrimRight();
					SQL1.Format(_T(" Sensitivity = %s,SystemType1='%s',SystemType2='%s',MaxPowDens=%s "), 
						(Values[9].IsEmpty()?"NULL":Values[9]),Values[10].Left(3),Values[11].Left(3),
						(Values[12].IsEmpty()?"NULL":Values[12]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%ld"), m_CatID);
				}
				if(StClass==_T("ML"))
				{
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3]);
					SQL2+=SQL1;
					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
						Values[5], Values[6], Values[7]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[8]);
					SQL2+=SQL1;
					Values[10]=Values[10].Left(3);
					Values[10].TrimRight();
					Values[11]=Values[11].Left(3);
					Values[11].TrimRight();
					SQL1.Format(_T("Sensitivity = %s ,SystemType1='%s',SystemType2='%s',MaxPowDens=%s"), 
						(Values[9].IsEmpty()?"NULL":Values[9]),Values[10].Left(3),Values[11].Left(3),
						(Values[12].IsEmpty()?"NULL":Values[12]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%ld"), m_CatID);
				}
				if(Typ==MONITORING)
				{
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3]);
					SQL2+=SQL1;
					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
						Values[5], Values[6], Values[7]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[8]);
					SQL2+=SQL1;
					SQL1.Format(_T(" Sensitivity = %s "), 
						(Values[9].IsEmpty()?"NULL":Values[9]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%ld"), m_CatID);
				}
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);
			}
		
			SQL=_T("Select max(EqID)+1 from Equipment");
			RS.Open(CRecordset::dynaset,SQL);
			RS.GetFieldValue((short)0,NewID);
			RS.Close();
			if(NewID.IsEmpty()) NewID=_T("1");
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
			int typ;
			pView->GetTreeCtrl().GetItemImage(Node,typ,typ);
			SQL1.Format(_T("select %s,%ld,%s,%s,%s"),NewID,pView->GetTreeCtrl().GetItemData(Node),CatID,
				(Values[2].IsEmpty()?_T("NULL"):Values[2]),(Values[4].IsEmpty()?_T("NULL"):Values[4]));
			if(typ==STATION || typ==MONITORING)
				SQL1=_T("insert into Equipment (EqID,StID,EqCatID,Pwr2Ant,RadPwr) ")+SQL1;
			if(typ==BC)
			{
				SQL1.Format(_T("select %s,%ld,%s,%s,%lf"),NewID,pView->GetTreeCtrl().GetItemData(Node),CatID,
					(Values[2].IsEmpty()?_T("NULL"):Values[2]),pow(10.,ERP/10.));
				SQL1=_T("insert into Equipment (EqID,BCID,EqCatID,Pwr2Ant,RadPwr) ")+SQL1;
			}
			if(typ==MOBILE)
				SQL1=_T("insert into Equipment (EqID,MobID,EqCatID,Pwr2Ant,RadPwr) ")+SQL1;
			DB.ExecuteSQL(SQL1);

			Node=pView->GetTreeCtrl().InsertItem(_Z("Equipment: ")+Values[1],EQUIPMENT,EQUIPMENT,pView->GetTreeCtrl().GetSelectedItem());
			pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
			pView->GetTreeCtrl().Select(Node,TVGN_CARET);
			m_Refresh=false;
			pView->RedrawWindow();
			AddTrail(_Z("Add equipment"),atol((LPCTSTR)NewID),"Equipment");
		}
		else    // Update
		{
			Over=AfxMessageBox(_Z("Overwrite existing data in library?"),MB_YESNO|MB_ICONWARNING);
			if(Over==IDNO)
			{
				SQL1=_T("Select max(EqCatID)+1 from EqCat");
				RS.Open(CRecordset::dynaset,SQL1);
				RS.GetFieldValue((short)0,CatID);
				RS.Close();
				if(CatID.IsEmpty()) CatID=_T("1");
				Values[8].MakeUpper();
				if(StClass==_T("BC"))
				{
/*					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,%s,%s,%s "),CatID,
						Values[1], Values[3], Values[5], 
						Values[6], Values[7],	Values[8], 
						(Values[9].Left(1).IsEmpty()?_T("1"):Values[9].Left(1)),
						(Values[10].IsEmpty()?"0":Values[10]), (Values[11].IsEmpty()?"0":Values[11]), 
						(Values[12].IsEmpty()?"0":Values[12]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, TranSys, ERP_h_dbw, ");
					SQL2+=_T("ERP_v_dbw, EU_Ref) ");*/
					if(!Values[8].IsEmpty())    ERP=atof(Values[8]);
					if(!Values[9].IsEmpty())    ERP=atof(Values[9]);
					if(!Values[8].IsEmpty() && !Values[9].IsEmpty())
						ERP=10.*log10(pow(10.,atof(Values[8])/10.)+pow(10.,atof(Values[9])/10.));
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s',%s,%s,%s,%s,%lf,'%s','%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[4], Values[5],	Values[6], 
						(Values[7].Left(1).IsEmpty()?_T("1"):Values[7].Left(1)),
						(Values[8].IsEmpty()?"NULL":Values[8]), (Values[9].IsEmpty()?"NULL":Values[9]), 
						(Values[10].IsEmpty()?"NULL":Values[10]),ERP,Values[11], 
						Values[12],Values[13],(Values[14].IsEmpty()?"NULL":Values[14]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, TranSys, ERP_h_dbw, ");
					SQL2+=_T("ERP_v_dbw, EU_Ref, ERP_dbw, RefPlanCfg, SysVar, RXMode, MaxPowDens) ");
				}
				if(StClass==_T("BT"))
				{
				/*	SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,%s,%s,%s,'%s','%s',%s,%s,%s,%s,%s,'%s' "),CatID,
						Values[1], Values[3].Left(1), Values[5].Left(1), 
						Values[6], Values[7], Values[8],  
						(Values[9].IsEmpty()?"0":Values[9]), (Values[10].IsEmpty()?"0":Values[10]),
						(Values[11].IsEmpty()?"0":Values[11]), (Values[12].IsEmpty()?"0":Values[12]), 
						Values[13].Left(2),Values[14],
						(Values[15].IsEmpty()?"0":Values[15]), (Values[16].IsEmpty()?"0":Values[16]), (Values[17].IsEmpty()?"0":Values[17]),
						(Values[18].IsEmpty()?"0":Values[18]), (Values[19].IsEmpty()?"0":Values[19]), Values[20]);
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, OsetV12, OsetV, OsetS12, OsetS, TVSys, ColorSys, ERP_h_dbw, ");
					SQL2+=_T("ERP_v_dbw, ERP_dbw, PwrRatio, EU_Ref, FreqStabl) ");*/
					if(!Values[13].IsEmpty())    ERP=atof(Values[13]);
					if(!Values[14].IsEmpty())    ERP=atof(Values[14]);
					if(!Values[13].IsEmpty() && !Values[14].IsEmpty())
						ERP=10.*log10(pow(10.,atof(Values[13])/10.)+pow(10.,atof(Values[14])/10.));
					Values[11]=Values[11].Left(2);
					Values[11].TrimRight();
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s',%s,%s,%s,%s,'%s','%s',%s,%s,%s,%s,'%s',%lf,'%s','%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[4], Values[5], Values[6],  
						(Values[7].IsEmpty()?"NULL":Values[7]), (Values[8].IsEmpty()?"NULL":Values[8]),
						(Values[9].IsEmpty()?"NULL":Values[9]), (Values[10].IsEmpty()?"NULL":Values[10]), 
						Values[11].Left(2),Values[12],
						(Values[13].IsEmpty()?"NULL":Values[13]), (Values[14].IsEmpty()?"NULL":Values[14]), 
						(Values[15].IsEmpty()?"NULL":Values[15]), (Values[16].IsEmpty()?"NULL":Values[16]), Values[17],ERP,
						Values[18], Values[19], Values[20],
						(Values[21].IsEmpty()?"NULL":Values[21]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, OsetV12, OsetV, OsetS12, OsetS, TVSys, ColorSys, ERP_h_dbw, ");
					SQL2+=_T("ERP_v_dbw, PwrRatio, EU_Ref, FreqStabl,ERP_dbw, RefPlanCfg, SysVar, RXMode, MaxPowDens) ");
				}
				if(StClass==_T("FX"))
				{
					Values[12]=Values[12].Left(3);
					Values[12].TrimRight();
					Values[13]=Values[13].Left(3);
					Values[13].TrimRight();
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,'%s',%s,'%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1),  
						Values[5].Left(1), Values[6], Values[7], Values[8], 
						(Values[9].IsEmpty()?"NULL":Values[9]), (Values[10].IsEmpty()?_T("NULL"):Values[10]),
						(Values[11].IsEmpty()?_T("NULL"):Values[11]),Values[12].Left(3),Values[13].Left(3),
						(Values[14].IsEmpty()?_T("NULL"):Values[14]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, Sensitivity, EnDisp,NoiseFactor,SystemType1,SystemType2, MaxPowDens) ");
				}
				if(StClass==_T("FB"))
				{
					Values[10]=Values[10].Left(3);
					Values[10].TrimRight();
					Values[11]=Values[11].Left(3);
					Values[11].TrimRight();
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,'%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[5].Left(1), 
						Values[6], Values[7],	Values[8], (Values[9].IsEmpty()?"NULL":Values[9]),Values[10].Left(3),
						Values[11].Left(3),(Values[12].IsEmpty()?_T("NULL"):Values[12]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo,Sensitivity,SystemType1,SystemType2,MaxPowDens) ");
				}
				if(StClass==_T("ML"))
				{
					Values[10]=Values[10].Left(3);
					Values[10].TrimRight();
					Values[11]=Values[11].Left(3);
					Values[11].TrimRight();
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s,'%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[5].Left(1), 
						Values[6], Values[7], Values[8], (Values[9].IsEmpty()?"NULL":Values[9]),Values[10].Left(3),
						Values[11].Left(3),(Values[12].IsEmpty()?_T("NULL"):Values[12]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo, Sensitivity,SystemType1,SystemType2,MaxPowDens) ");
				}
				if(Typ==MONITORING)
				{
					SQL1.Format(_T("select %s,'%s','%s','%s','%s','%s','%s',%s "),CatID,
						Values[1], Values[3].Left(1), Values[5].Left(1), 
						Values[6], Values[7],	Values[8], (Values[9].IsEmpty()?"NULL":Values[9]));
					SQL2=_T("insert into EqCat (EqCatID, EqName, PowerType, RadPowerType, ");
					SQL2+=_T("MadeBy, Model, SerialNo,Sensitivity) ");
				}
				SQL1=SQL2+SQL1;
				DB.ExecuteSQL(SQL1);

			}
			else
			{
				SQL.Format(_T("Select * from Equipment, EqCat where Equipment.EqCatID=EqCat.EqCatID and EqID=%ld"), m_RecID);
				RS.Open(CRecordset::dynaset,SQL);
				for(int i=0;i<RS.GetODBCFieldCount();i++)
					RS.GetFieldValue(i,Fields[i]);
				RS.Close();
				CatID=Fields[1];
				Values[8].MakeUpper();
				if(StClass==_T("BC"))
				{
					if(!Values[8].IsEmpty())    ERP=atof(Values[8]);
					if(!Values[9].IsEmpty())    ERP=atof(Values[9]);
					if(!Values[8].IsEmpty() && !Values[9].IsEmpty())
						ERP=10.*log10(pow(10.,atof(Values[8])/10.)+pow(10.,atof(Values[9])/10.));
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("MadeBy = '%s', Model = '%s', "), 
						Values[4], Values[5]);
//					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
//						Values[5].Left(1), Values[6], Values[7]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[6]);
					SQL2+=SQL1;
					SQL1.Format(_T(" TranSys=%s, "), (Values[7].Left(1).IsEmpty()?_T("1"):Values[7].Left(1)));
					SQL2+=SQL1;
					SQL1.Format(_T(" ERP_h_dbw = %s, ERP_v_dbw = %s, ERP_dbw=%lf, "), 
						(Values[8].IsEmpty()?"NULL":Values[8]), (Values[9].IsEmpty()?"NULL":Values[9]),ERP);
					SQL2+=SQL1;
					SQL1.Format(_T("EU_Ref = %s ,RefPlanCfg='%s', SysVar='%s', RXMode='%s', MaxPowDens=%s "), 
						(Values[10].IsEmpty()?"NULL":Values[10]),Values[11],Values[12],Values[13],
						(Values[14].IsEmpty()?"NULL":Values[14]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%s"), Fields[1]);
				}
				if(StClass==_T("BT"))
				{
					if(!Values[13].IsEmpty())    ERP=atof(Values[13]);
					if(!Values[14].IsEmpty())    ERP=atof(Values[14]);
					if(!Values[13].IsEmpty() && !Values[14].IsEmpty())
						ERP=10.*log10(pow(10.,atof(Values[13])/10.)+pow(10.,atof(Values[14])/10.));
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3].Left(1));
					SQL2+=SQL1;
//					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
//						Values[5].Left(1), Values[6], Values[7]);
					SQL1.Format(_T("MadeBy = '%s', Model = '%s', "), 
						Values[4], Values[5]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', OsetV12 =%s, "), 
						Values[6], (Values[7].IsEmpty()?"NULL":Values[7]));
					SQL2+=SQL1;
					Values[11]=Values[11].Left(2);
					Values[11].TrimRight();
					SQL1.Format(_T("OsetV = %s, OsetS12 = %s, OsetS = %s, TVSys = '%s', "), (Values[8].IsEmpty()?"NULL":Values[8]), 
						(Values[9].IsEmpty()?"NULL":Values[9]), (Values[10].IsEmpty()?"NULL":Values[10]), 
						Values[11].Left(2));
					SQL2+=SQL1;
					SQL1.Format(_T("ColorSys = '%s', ERP_h_dbw = %s, ERP_v_dbw = %s, ERP_dbw=%lf, "), Values[12], 
						(Values[13].IsEmpty()?"NULL":Values[13]), (Values[14].IsEmpty()?"NULL":Values[14]),ERP);
					SQL2+=SQL1;
					SQL1.Format(_T("PwrRatio = %s, EU_Ref = %s, "), (Values[15].IsEmpty()?"NULL":Values[15]), 
						(Values[16].IsEmpty()?"NULL":Values[16]));
					SQL2+=SQL1;
					SQL1.Format(_T(" FreqStabl = '%s',RefPlanCfg='%s', SysVar='%s', RXMode='%s', MaxPowDens=%s "), 
						Values[17],Values[18], Values[19], Values[20],
						(Values[21].IsEmpty()?"NULL":Values[21]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%s"), Fields[1]);
				}
				if(StClass==_T("FX"))
				{
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3]);
					SQL2+=SQL1;
					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
						 Values[5], Values[6], Values[7]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[8]);
					SQL2+=SQL1;
					Values[12]=Values[12].Left(3);
					Values[12].TrimRight();
					Values[13]=Values[13].Left(3);
					Values[13].TrimRight();
					SQL1.Format(_T("Sensitivity = %s, EnDisp = '%s', NoiseFactor=%s ,SystemType1='%s',SystemType2='%s', MaxPowDens=%s "), 
						(Values[9].IsEmpty()?"NULL":Values[9]), Values[10],
						(Values[11].IsEmpty()?_T("NULL"):Values[11]),Values[12].Left(3),Values[13].Left(3),
						(Values[14].IsEmpty()?_T("NULL"):Values[14]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%s"), Fields[1]);
				}
				if(StClass==_T("FB"))
				{
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3]);
					SQL2+=SQL1;
					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s',SerialNo = '%s', "), 
						(Values[5].IsEmpty()?"NULL":Values[5]), Values[6], Values[7], Values[8]);
					SQL2+=SQL1;
					Values[10]=Values[10].Left(3);
					Values[10].TrimRight();
					Values[11]=Values[11].Left(3);
					Values[11].TrimRight();
					SQL1.Format(_T(" Sensitivity = %s,SystemType1='%s',SystemType2='%s',MaxPowDens=%s "), 
						(Values[9].IsEmpty()?"NULL":Values[9]),Values[10].Left(3),Values[11].Left(3),
						(Values[12].IsEmpty()?"NULL":Values[12]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%s"), Fields[1]);
				}
				if(StClass==_T("ML"))
				{
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3]);
					SQL2+=SQL1;
					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
						Values[5], Values[6], Values[7]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[8]);
					SQL2+=SQL1;
					Values[10]=Values[10].Left(3);
					Values[10].TrimRight();
					Values[11]=Values[11].Left(3);
					Values[11].TrimRight();
					SQL1.Format(_T("Sensitivity = %s ,SystemType1='%s',SystemType2='%s',MaxPowDens=%s"), 
						(Values[9].IsEmpty()?"NULL":Values[9]),Values[10].Left(3),Values[11].Left(3),
						(Values[12].IsEmpty()?"NULL":Values[12]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%s"), Fields[1]);
				}
				if(Typ==MONITORING)
				{
					SQL1.Format(_T("UPDATE EqCat SET EqName = '%s', "), Values[1]);
					SQL2=SQL1;
					SQL1.Format(_T("PowerType = '%s', "), Values[3]);
					SQL2+=SQL1;
					SQL1.Format(_T("RadPowerType = '%s', MadeBy = '%s', Model = '%s', "), 
						Values[5], Values[6], Values[7]);
					SQL2+=SQL1;
					SQL1.Format(_T("SerialNo = '%s', "), Values[8]);
					SQL2+=SQL1;
					SQL1.Format(_T(" Sensitivity = %s "), 
						(Values[9].IsEmpty()?"NULL":Values[9]));
					SQL2+=SQL1;
					SQL1.Format(_T(" WHERE EqCatID=%ld"), m_CatID);
				}
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);
			}
			if(StClass==_T("BC") || StClass==_T("BT"))
				SQL1.Format(_T("Update Equipment set EqCatID=%s, Pwr2Ant=%s, RadPwr=%lf where EqID=%ld"),CatID,
					(Values[2].IsEmpty()?_T("NULL"):Values[2]), pow(10.,ERP/10.),m_RecID);
			else
				SQL1.Format(_T("Update Equipment set EqCatID=%s, Pwr2Ant=%s, RadPwr=%s where EqID=%ld"),CatID,
					(Values[2].IsEmpty()?_T("NULL"):Values[2]),(Values[4].IsEmpty()?_T("NULL"):Values[4]),m_RecID);
			DB.ExecuteSQL(SQL1);
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Equipment: ")+Values[1]);

			AddTrail(_Z("Update equipment"),m_RecID,"Equipment");
			result=true;
		}
	}
	else
		result=false;
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::AntennaSave()
{
	CDatabase DB;
	CRecordset RS;
	CString NewID,CatID;
	CString SQL,StClass, Pol;
	bool result=true;
//	int Over;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[40], Values[40], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=4;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()==0x7F7F7F)
		{
			if(m_CatID==-1 && i>2)
				m_CatID=m_Grid->GetRowData(i);
			continue;
		}
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft(" ");
		Values[j].TrimRight(" ");
		j++;
	}
	Values[0].Format(_T("%ld"),m_CatID);
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem());
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==EQUIPMENT)
	{
		Node=pView->GetTreeCtrl().GetParentItem(Node);
		pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	}
	if(Typ==STATION || Typ==MONITORING)
		SQL.Format(_T("Select ClassStation from station where station.stid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	if(Typ==BC)
		SQL.Format(_T("Select ClassStation from bcstation where bcstation.stid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	if(Typ==MOBILE)
		SQL.Format(_T("Select ClassStation from mobiles where mobiles.mobid=%ld"),pView->GetTreeCtrl().GetItemData(Node));
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,StClass);
	RS.Close();
	StClass=StClass.Left(2);
	Values[11].TrimRight();
	if(StClass==_T("BT") || StClass==_T("BC") || StClass==_T("FB") || StClass==_T("ML"))
	{
		if(Values[4].IsEmpty())
			Missing= m_Grid->GetTextMatrix(2,0) + ",";
		if(Values[5].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(3,0) + ",";
		if(Values[6].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(4,0) + ",";
		if(Values[7].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(6,0) + ",";
		if(Values[8].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(7,0) + ",";
		if(Values[10].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(9,0) + ",";
		if(Values[11].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(10,0) + ",";
		if(Values[13].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(12,0) + ",";
		if(Values[14].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(13,0) + ",";
		Pol=Values[10].Left(1);
		Pol.MakeUpper();
	}
	if(StClass==_T("FX"))
	{
		if(Values[4].IsEmpty())
			Missing= m_Grid->GetTextMatrix(2,0) + ",";
		if(Values[6].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(4,0) + ",";
		if(Values[7].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(5,0) + ",";
		if(Values[8].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(7,0) + ",";
		if(Values[9].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(8,0) + ",";
		if(Values[11].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(10,0) + ",";
		if(Values[12].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(11,0) + ",";
		if(Values[14].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(13,0) + ",";
		if(Values[15].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(14,0) + ",";
		Pol=Values[11].Left(1);
		Pol.MakeUpper();
	}
	if(Typ==MONITORING)
	{
		if(Values[4].IsEmpty())
			Missing= m_Grid->GetTextMatrix(2,0) + ",";
		if(Values[5].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(3,0) + ",";
		if(Values[6].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(4,0) + ",";
		if(Values[7].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(6,0) + ",";
//		if(Values[8].IsEmpty())
//			Missing+= m_Grid->GetTextMatrix(7,0) + ",";
		if(Values[9].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(8,0) + ",";
		if(Values[10].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(9,0) + ",";
		if(Values[12].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(11,0) + ",";
		if(Values[13].IsEmpty())
			Missing+= m_Grid->GetTextMatrix(12,0) + ",";
		Pol=Values[10].Left(1);
		Pol.MakeUpper();
	}
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else if(AntennaValidation(Values,StClass))
	{
		if(m_Action==1) // Add new
		{
//			if(m_CatID>-1)
//				Over=AfxMessageBox(_Z("Overwrite existing data in library?"),MB_YESNO|MB_ICONWARNING);

//			if(m_CatID==-1 || Over==IDNO)
			{
				SQL1=_T("Select max(AntCatID)+1 from AntCat");
				RS.Open(CRecordset::dynaset,SQL1);
				RS.GetFieldValue((short)0,CatID);
				RS.Close();
				if(CatID.IsEmpty()) CatID=_T("1");
				if(StClass==_T("BT") || StClass==_T("BC"))
				{
					SQL1.Format(_T("select %s,'%s','%s','%s','%s',%s,'%s','%s',%s,%s,'%s',%s,%s,%s,%s,%s "),CatID,
						Values[7],Values[8].Left(1),Values[9],Values[10].Left(1),(Values[11].IsEmpty()?_T("NULL"):Values[11]),
						Values[12].Left(1),Values[13].Left(1),
						(Values[14].IsEmpty()?_T("NULL"):Values[14]),(Values[15].IsEmpty()?_T("NULL"):Values[15]),
						Values[16],(Values[17].IsEmpty()?_T("NULL"):Values[17]),
						(Values[18].IsEmpty()?_T("NULL"):Values[18]),
						(Values[19].IsEmpty()?_T("NULL"):Values[19]), (Values[20].IsEmpty()?_T("NULL"):Values[20]),
						(Values[21].IsEmpty()?_T("NULL"):Values[21]));
					SQL2=_T("insert into AntCat (AntCatID, AntName, ClassOfAnt, AntType, Pol, Gain, GainType, AntDir, ");
					SQL2+=_T("BeamWidthH, BeamWidthV, RefAnt, MaxEffHght, FreqFrom, FreqTo, XPD, InsLoss)");
				}
				if(StClass==_T("FB") || StClass==_T("ML"))
				{
					SQL1.Format(_T("select %s,'%s','%s','%s','%s',%s,'%s','%s',%s,%s,'%s',%s,%s,%s,%s "),CatID,
						Values[7],Values[8].Left(1),Values[9],Values[10].Left(1),(Values[11].IsEmpty()?_T("NULL"):Values[11]),
						Values[12].Left(1),Values[13].Left(1),
						(Values[14].IsEmpty()?_T("NULL"):Values[14]),(Values[15].IsEmpty()?_T("NULL"):Values[15]),Values[16],
						(Values[17].IsEmpty()?_T("NULL"):Values[17]),(Values[18].IsEmpty()?_T("NULL"):Values[18]), 
						(Values[19].IsEmpty()?_T("NULL"):Values[19]),(Values[20].IsEmpty()?_T("NULL"):Values[20]));
					SQL2=_T("insert into AntCat (AntCatID, AntName, ClassOfAnt, AntType, Pol, Gain, GainType, AntDir, ");
					SQL2+=_T("BeamWidthH, BeamWidthV, RefAnt, FreqFrom, FreqTo, XPD, InsLoss) ");
				}
				if(StClass==_T("FX"))
				{
					SQL1.Format(_T("select %s,'%s','%s','%s','%s',%s,'%s','%s',%s,%s,'%s',%s,%s,%s,%s "),CatID,
						Values[8],Values[9].Left(1),Values[10],Values[11].Left(1),(Values[12].IsEmpty()?_T("NULL"):Values[12]),
						Values[13].Left(1),Values[14].Left(1),
						(Values[15].IsEmpty()?_T("NULL"):Values[15]),(Values[16].IsEmpty()?_T("NULL"):Values[16]),Values[17],
						(Values[18].IsEmpty()?_T("NULL"):Values[18]),(Values[19].IsEmpty()?_T("NULL"):Values[19]),
						(Values[20].IsEmpty()?_T("NULL"):Values[20]),(Values[21].IsEmpty()?_T("NULL"):Values[21]));
					SQL2=_T("insert into AntCat (AntCatID, AntName, ClassOfAnt, AntType, Pol, Gain, GainType, AntDir, ");
					SQL2+=_T("BeamWidthH, BeamWidthV, RefAnt, FreqFrom, FreqTo, XPD, InsLoss) ");
				}
				if(Typ==MONITORING)
				{
					SQL1.Format(_T("select %s,'%s','%s','%s',%s,'%s','%s',%s,%s,%s,%s "),CatID,
						Values[7],Values[8],Values[9].Left(1),(Values[10].IsEmpty()?_T("NULL"):Values[10]),
						Values[11].Left(1),Values[12].Left(1),
						(Values[13].IsEmpty()?_T("NULL"):Values[13]),(Values[14].IsEmpty()?_T("NULL"):Values[14]),
						(Values[15].IsEmpty()?_T("NULL"):Values[15]),(Values[16].IsEmpty()?_T("NULL"):Values[16]));
					SQL2=_T("insert into AntCat (AntCatID, AntName, AntType, Pol, Gain, GainType, AntDir, ");
					SQL2+=_T("BeamWidthH, BeamWidthV, FreqFrom, FreqTo) ");
				}
				SQL1=SQL2+SQL1;
				DB.ExecuteSQL(SQL1);
//				SQL1.Format(_T("select '%s', Azm, Polar, Attn from AntDiag where AntID=%ld "), CatID, m_CatID);
//				SQL2=_T("insert into AntDiag (AntID, Azm, Polar, Attn)");
//				SQL1=SQL2+SQL1;
//				DB.ExecuteSQL(SQL1);

					CRecordset AntPatt;
					double Patt[2][360]={0.0},Patt2[2][360]={0.0},Azimuth=atof((LPCTSTR)Values[4]);
					int i=0;
					CString FVal;
					AntPatt.m_pDatabase=&DB;
					if(Pol!="V")
					{
						SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%ld order by azm"),m_CatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						while(!AntPatt.IsEOF())
						{
							//double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=atof(FVal);
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=atof(FVal);
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						if(Azimuth>=0)
						{
							i=359;
							while(Patt[0][i]>359-Azimuth && i>=0)
								i--;
							if(i==-1) i=359;
							for(int j=i;j>=0;j--)
								Patt[0][j]+=Azimuth;
							for(j=i+1;j<360;j++)
								Patt[0][j]-=360-Azimuth;
						}
						else
						{
							i=0;
							while(Patt[0][i]<-Azimuth && i<360)
								i++;
							if(i==360) i=0;
							for(int j=i;j<360;j++)
								Patt[0][j]+=Azimuth;
							for(j=0;j<i;j++)
								Patt[0][j]+=360+Azimuth;
						}
						for(j=0;j<360;j++)
						{
							Patt2[0][j]=(double)j;
							Patt2[1][(int)Patt[0][j]]=Patt[1][j];
						}
						SQL.Format(_T("Delete * from AntDiag where Polar='H' and AntID=%s"),CatID);
						DB.ExecuteSQL(SQL);
						for(i=0;i<360;i++)
						{
							SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'H', %lf"),
								CatID, (double)i, Patt2[1][i]);
							DB.ExecuteSQL(SQL);
						}
						if(Pol=="H")
						{
							SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%ld order by azm"),m_CatID);
							AntPatt.Open(CRecordset::snapshot, SQL);
							i=0;
							while(!AntPatt.IsEOF())
							{
								//double azm, attn;
								AntPatt.GetFieldValue(_T("Azm"),FVal);
								Patt[0][i]=atof(FVal);
								AntPatt.GetFieldValue(_T("Attn"),FVal);
								Patt[1][i]=atof(FVal);
								AntPatt.MoveNext();
								i++;
							}
							AntPatt.Close();
							SQL.Format(_T("Delete * from AntDiag where Polar='V' and AntID=%s"),CatID);
							DB.ExecuteSQL(SQL);
							for(i=0;i<360;i++)
							{
								SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'V', %lf"),
									CatID, (double)i, Patt[1][i]);
								DB.ExecuteSQL(SQL);
							}
						}
///						SQL.Format(_T("INSERT into AntDiag (AntID, Azm, Polar, Attn) select %s,Azm,Polar,Attn from AntDiag where AntID=%ld and Polar='%s'"),
///							CatID, m_CatID,Values[11].Left(1)==_T("H")?_T("V"):_T("X"));
///						DB.ExecuteSQL(SQL);
					}
					if(Pol!="H")
					{
						SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%ld order by azm"),m_CatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						i=0;
						while(!AntPatt.IsEOF())
						{
							//double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=atof(FVal);
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=atof(FVal);
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						if(Azimuth>=0)
						{
							i=359;
							while(Patt[0][i]>359-Azimuth && i>=0)
								i--;
							if(i==-1) i=359;
							for(int j=i;j>=0;j--)
								Patt[0][j]+=Azimuth;
							for(j=i+1;j<360;j++)
								Patt[0][j]-=360-Azimuth;
						}
						else
						{
							i=0;
							while(Patt[0][i]<-Azimuth && i<360)
								i++;
							if(i==360) i=0;
							for(int j=i;j<360;j++)
								Patt[0][j]+=Azimuth;
							for(j=0;j<i;j++)
								Patt[0][j]+=360+Azimuth;
						}
						for(j=0;j<360;j++)
						{
							Patt2[0][j]=(double)j;
							Patt2[1][(int)Patt[0][j]]=Patt[1][j];
						}
						SQL.Format(_T("Delete * from AntDiag where Polar='V' and AntID=%s"),CatID);
						DB.ExecuteSQL(SQL);
						for(i=0;i<360;i++)
						{
							SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'V', %lf"),
								CatID, (double)i, Patt2[1][i]);
							DB.ExecuteSQL(SQL);
						}
						if(Pol=="V")
						{
							SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%ld order by azm"),m_CatID);
							AntPatt.Open(CRecordset::snapshot, SQL);
							i=0;
							while(!AntPatt.IsEOF())
							{
								//double azm, attn;
								AntPatt.GetFieldValue(_T("Azm"),FVal);
								Patt[0][i]=atof(FVal);
								AntPatt.GetFieldValue(_T("Attn"),FVal);
								Patt[1][i]=atof(FVal);
								AntPatt.MoveNext();
								i++;
							}
							AntPatt.Close();
							SQL.Format(_T("Delete * from AntDiag where Polar='H' and AntID=%s"),CatID);
							DB.ExecuteSQL(SQL);
							for(i=0;i<360;i++)
							{
								SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'H', %lf"),
									CatID, (double)i, Patt[1][i]);
								DB.ExecuteSQL(SQL);
							}
						}
///						SQL.Format(_T("INSERT into AntDiag (AntID, Azm, Polar, Attn) select %s,Azm,Polar,Attn from AntDiag where AntID=%ld and Polar='%s'"),
///							CatID, m_CatID,Values[11].Left(1)==_T("V")?_T("H"):_T("Y"));
///						DB.ExecuteSQL(SQL);
					}
			
			}
/*			else
			{
				CatID.Format(_T("%ld"),m_CatID);
				if(StClass==_T("BT") || StClass==_T("BC"))
				{
					SQL1.Format(_T("UPDATE AntCat SET AntName = '%s', ClassOfAnt = '%s', AntType = '%s', "), Values[7], Values[8].Left(1), Values[9]);
					SQL2=SQL1;
					SQL1.Format(_T("Pol = '%s', Gain = %s, GainType = '%s', "), Values[10].Left(1),(Values[11].IsEmpty()?"NULL":Values[11]), Values[12].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("AntDir = '%s', "), Values[13].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("BeamWidthH = %s, BeamWidthV = %s, RefAnt = '%s', MaxEffHght =%s, "), 
						(Values[14].IsEmpty()?_T("NULL"):Values[14]), (Values[15].IsEmpty()?_T("NULL"):Values[15]), Values[16], 
						(Values[17].IsEmpty()?_T("NULL"):Values[17]));
					SQL2+=SQL1;
					SQL1.Format(_T("FreqFrom = %s, FreqTo = %s, XPD = %s, "), (Values[18].IsEmpty()?_T("NULL"):Values[18]), 
						(Values[19].IsEmpty()?_T("NULL"):Values[19]), (Values[20].IsEmpty()?_T("NULL"):Values[20]));
					SQL2+=SQL1;
					SQL1.Format(_T("InsLoss = %s "), (Values[21].IsEmpty()?_T("NULL"):Values[21]));
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE AntCatID=%s"), CatID);
					SQL2+=SQL1;
				}
				if(StClass==_T("FB") || StClass==_T("ML"))
				{
					SQL1.Format(_T("UPDATE AntCat SET AntName = '%s', ClassOfAnt = '%s', AntType = '%s', "), Values[7], Values[8].Left(1), Values[9]);
					SQL2=SQL1;
					SQL1.Format(_T("Pol = '%s', Gain = %s, GainType = '%s', "), Values[10].Left(1),(Values[11].IsEmpty()?"NULL":Values[11]), Values[12].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("AntDir = '%s', "), Values[13].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("BeamWidthH = %s, BeamWidthV = %s, RefAnt = '%s', "), 
						(Values[14].IsEmpty()?_T("NULL"):Values[14]), (Values[15].IsEmpty()?_T("NULL"):Values[15]), Values[16]);
					SQL2+=SQL1;
					SQL1.Format(_T("FreqFrom = %s, FreqTo = %s, XPD = %s, "), (Values[17].IsEmpty()?_T("NULL"):Values[17]), 
						(Values[18].IsEmpty()?_T("NULL"):Values[18]), (Values[19].IsEmpty()?_T("NULL"):Values[19]));
					SQL2+=SQL1;
					SQL1.Format(_T("InsLoss = %s "), (Values[20].IsEmpty()?_T("NULL"):Values[20]));
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE AntCatID=%s"), CatID);
					SQL2+=SQL1;
				}
				if(StClass==_T("FX"))
				{
					SQL1.Format(_T("UPDATE AntCat SET AntName = '%s', ClassOfAnt = '%s', AntType = '%s', "), Values[8], Values[9].Left(1), Values[10]);
					SQL2=SQL1;
					SQL1.Format(_T("Pol = '%s', Gain = %s, GainType = '%s', "), Values[11].Left(1),(Values[12].IsEmpty()?"NULL":Values[12]), Values[13].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("AntDir = '%s', "), Values[14].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("BeamWidthH = %s, BeamWidthV = %s, RefAnt = '%s', "), 
						(Values[15].IsEmpty()?_T("NULL"):Values[15]), (Values[16].IsEmpty()?_T("NULL"):Values[16]), Values[17]);
					SQL2+=SQL1;
					SQL1.Format(_T("FreqFrom = %s, FreqTo = %s, XPD = %s, "), (Values[18].IsEmpty()?_T("NULL"):Values[18]), 
						(Values[19].IsEmpty()?_T("NULL"):Values[19]), (Values[20].IsEmpty()?_T("NULL"):Values[20]));
					SQL2+=SQL1;
					SQL1.Format(_T("InsLoss = %s "), (Values[21].IsEmpty()?_T("NULL"):Values[21]));
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE AntCatID=%s"), CatID);
					SQL2+=SQL1;
				}
				DB.ExecuteSQL(SQL2);
			}*/
			SQL=_T("Select max(Antid)+1 from Antenna");
			RS.Open(CRecordset::dynaset,SQL);
			RS.GetFieldValue((short)0,NewID);
			RS.Close();
			if(NewID.IsEmpty()) NewID=_T("1");
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
			if(StClass==_T("BT") || StClass==_T("BC") || StClass==_T("FB") || StClass==_T("ML") || Typ==MONITORING)
			{
				SQL1.Format(_T("select %s,%ld,%s,%s,%s,%s "),NewID,pView->GetTreeCtrl().GetItemData(Node),CatID,
					(Values[4].IsEmpty()?_T("NULL"):Values[4]),
					(Values[5].IsEmpty()?_T("NULL"):Values[5]),(Values[6].IsEmpty()?(StClass==_T("ML")?_T("1.5"):_T("37.5")):Values[6]));
				SQL1=_T("insert into Antenna (AntID,EqID,AntCatID,Azimuth,Elevation,AntHeightAGL) ")+SQL1;
			}
			if(StClass==_T("FX"))
			{
				SQL1.Format(_T("select %s,%ld,%s,%s,%s,%s,%s "),NewID,pView->GetTreeCtrl().GetItemData(Node),CatID,
					(Values[4].IsEmpty()?_T("NULL"):Values[4]),(Values[5].IsEmpty()?_T("NULL"):Values[5]),
					(Values[6].IsEmpty()?_T("NULL"):Values[6]),(Values[7].IsEmpty()?_T("37.5"):Values[7]));
				SQL1=_T("insert into Antenna (AntID,EqID,AntCatID,Azimuth,AzimTo,Elevation,AntHeightAGL) ")+SQL1;
			}
			DB.ExecuteSQL(SQL1);

			if(StClass==_T("FX"))
				Node=pView->GetTreeCtrl().InsertItem(_Z("Antenna: ")+Values[8],ANTENNA,ANTENNA,pView->GetTreeCtrl().GetSelectedItem());
			else
				Node=pView->GetTreeCtrl().InsertItem(_Z("Antenna: ")+Values[7],ANTENNA,ANTENNA,pView->GetTreeCtrl().GetSelectedItem());
			pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
			pView->GetTreeCtrl().Select(Node,TVGN_CARET);
			m_Refresh=false;
			pView->RedrawWindow();
			AddTrail(_Z("Add antenna"),atol((LPCTSTR)NewID),"Antenna");
		}
		else    // Update
		{
			SQL.Format(_T("Select * from Antenna,AntCat where Antenna.AntCatID=AntCat.AntCatID and AntID=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(int i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			CatID=Fields[1];
			if(m_CatID!=atol(CatID))
			{
				CRecordset AntPatt;
				double Patt[2][360]={0.0},Patt2[2][360]={0.0},Azimuth=atof((LPCTSTR)Values[4]);
				int i;
				CString FVal;
				AntPatt.m_pDatabase=&DB;
				if(Pol!="V")
				{
					SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%ld order by azm"),m_CatID);
					AntPatt.Open(CRecordset::snapshot, SQL);
					i=0;
					while(!AntPatt.IsEOF())
					{
						//double azm, attn;
						AntPatt.GetFieldValue(_T("Azm"),FVal);
						Patt[0][i]=atof(FVal);
						AntPatt.GetFieldValue(_T("Attn"),FVal);
						Patt[1][i]=atof(FVal);
						AntPatt.MoveNext();
						i++;
					}
					AntPatt.Close();
					if(Azimuth>=0)
					{
						i=359;
						while(Patt[0][i]>359-Azimuth && i>=0)
							i--;
						if(i==-1) i=359;
						for(int j=i;j>=0;j--)
							Patt[0][j]+=Azimuth;
						for(j=i+1;j<360;j++)
							Patt[0][j]-=360-Azimuth;
					}
					else
					{
						i=0;
						while(Patt[0][i]<-Azimuth && i<360)
							i++;
						if(i==360) i=0;
						for(int j=i;j<360;j++)
							Patt[0][j]+=Azimuth;
						for(j=0;j<i;j++)
							Patt[0][j]+=360+Azimuth;
					}
					for(j=0;j<360;j++)
					{
						Patt2[0][j]=(double)j;
						Patt2[1][(int)Patt[0][j]]=Patt[1][j];
					}
					SQL.Format(_T("Delete * from AntDiag where Polar='H' and AntID=%s"),CatID);
					DB.ExecuteSQL(SQL);
					for(i=0;i<360;i++)
					{
						SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'H', %lf"),
							CatID, (double)i, Patt2[1][i]);
						DB.ExecuteSQL(SQL);
					}
					if(Pol=="H")
					{
						SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%ld order by azm"),m_CatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						i=0;
						while(!AntPatt.IsEOF())
						{
							//double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=atof(FVal);
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=atof(FVal);
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						SQL.Format(_T("Delete * from AntDiag where Polar='V' and AntID=%s"),CatID);
						DB.ExecuteSQL(SQL);
						for(i=0;i<360;i++)
						{
							SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'V', %lf"),
								CatID, (double)i, Patt[1][i]);
							DB.ExecuteSQL(SQL);
						}
					}
//					SQL.Format(_T("INSERT into AntDiag (AntID, Azm, Polar, Attn) select %s,Azm,Polar,Attn from AntDiag where AntID=%ld and Polar='%s'"),
//						CatID, m_CatID,Values[11].Left(1)==_T("H")?_T("V"):_T("X"));
//					AntPatt.m_pDatabase->ExecuteSQL(SQL);
				}
				if(Pol!="H")
				{
					SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%ld order by azm"),m_CatID);
					AntPatt.Open(CRecordset::snapshot, SQL);
					i=0;
					while(!AntPatt.IsEOF())
					{
						//double azm, attn;
						AntPatt.GetFieldValue(_T("Azm"),FVal);
						Patt[0][i]=atof(FVal);
						AntPatt.GetFieldValue(_T("Attn"),FVal);
						Patt[1][i]=atof(FVal);
						AntPatt.MoveNext();
						i++;
					}
					AntPatt.Close();
					if(Azimuth>=0)
					{
						i=359;
						while(Patt[0][i]>359-Azimuth && i>=0)
							i--;
						if(i==-1) i=359;
						for(int j=i;j>=0;j--)
							Patt[0][j]+=Azimuth;
						for(j=i+1;j<360;j++)
							Patt[0][j]-=360-Azimuth;
					}
					else
					{
						i=0;
						while(Patt[0][i]<-Azimuth && i<360)
							i++;
						if(i==360) i=0;
						for(int j=i;j<360;j++)
							Patt[0][j]+=Azimuth;
						for(j=0;j<i;j++)
							Patt[0][j]+=360+Azimuth;
					}
					for(j=0;j<360;j++)
					{
						Patt2[0][j]=(double)j;
						Patt2[1][(int)Patt[0][j]]=Patt[1][j];
					}
					SQL.Format(_T("Delete * from AntDiag where Polar='V' and AntID=%s"),CatID);
					DB.ExecuteSQL(SQL);
					for(i=0;i<360;i++)
					{
						SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'V', %lf"),
							CatID, (double)i, Patt2[1][i]);
						DB.ExecuteSQL(SQL);
					}
					if(Pol=="V")
					{
						SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%ld order by azm"),m_CatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						i=0;
						while(!AntPatt.IsEOF())
						{
							//double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=atof(FVal);
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=atof(FVal);
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						SQL.Format(_T("Delete * from AntDiag where Polar='H' and AntID=%s"),CatID);
						DB.ExecuteSQL(SQL);
						for(i=0;i<360;i++)
						{
							SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'H', %lf"),
								CatID, (double)i, Patt[1][i]);
							DB.ExecuteSQL(SQL);
						}
					}
//					SQL.Format(_T("INSERT into AntDiag (AntID, Azm, Polar, Attn) select %s,Azm,Polar,Attn from AntDiag where AntID=%ld and Polar='%s'"),
//						CatID, m_CatID,Values[11].Left(1)==_T("V")?_T("H"):_T("Y"));
//					AntPatt.m_pDatabase->ExecuteSQL(SQL);
				}
				m_CatID=atol(CatID); 
			}
			else
			{
				CRecordset AntPatt;
				double Patt[2][360]={0.0},Patt2[2][360]={0.0},Azimuth=atof((LPCTSTR)Values[4])-atof((LPCTSTR)Fields[3]);
				int i;
				CString FVal;
				AntPatt.m_pDatabase=&DB;
//				SQL.Format(_T("Delete * from AntDiag where AntID=%s"),CatID);
//				AntPatt.m_pDatabase->ExecuteSQL(SQL);
				if(Pol!="V")
				{
					SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%s order by azm"),CatID);
					AntPatt.Open(CRecordset::snapshot, SQL);
					i=0;
					while(!AntPatt.IsEOF())
					{
						//double azm, attn;
						AntPatt.GetFieldValue(_T("Azm"),FVal);
						Patt[0][i]=atof(FVal);
						AntPatt.GetFieldValue(_T("Attn"),FVal);
						Patt[1][i]=atof(FVal);
						AntPatt.MoveNext();
						i++;
					}
					AntPatt.Close();
/*					i=0;
					while(Patt[0][i]<Azimuth && i<360)
						i++;
					if(i==360) i=359;
					for(int j=i;j<360;j++)
						Patt[0][j]-=Azimuth;
					for(j=0;j<i;j++)
						Patt[0][j]+=359-Azimuth;*/
					if(Azimuth>=0)
					{
						i=359;
						while(Patt[0][i]>359-Azimuth && i>=0)
							i--;
						if(i==-1) i=359;
						for(int j=i;j>=0;j--)
							Patt[0][j]+=Azimuth;
						for(j=i+1;j<360;j++)
							Patt[0][j]-=360-Azimuth;
					}
					else
					{
						i=0;
						while(Patt[0][i]<-Azimuth && i<360)
							i++;
						if(i==360) i=0;
						for(int j=i;j<360;j++)
							Patt[0][j]+=Azimuth;
						for(j=0;j<i;j++)
							Patt[0][j]+=360+Azimuth;
					}
					for(j=0;j<360;j++)
					{
						Patt2[0][j]=(double)j;
						Patt2[1][(int)Patt[0][j]]=Patt[1][j];
					}
					SQL.Format(_T("Delete * from AntDiag where Polar='H' and AntID=%s"),CatID);
					DB.ExecuteSQL(SQL);
					for(i=0;i<360;i++)
					{
						SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'H', %lf"),
							CatID, (double)i, Patt2[1][i]);
						DB.ExecuteSQL(SQL);
					}
					if(Pol=="H")
					{
						SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%ld order by azm"),m_CatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						i=0;
						while(!AntPatt.IsEOF())
						{
							//double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=atof(FVal);
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=atof(FVal);
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						SQL.Format(_T("Delete * from AntDiag where Polar='V' and AntID=%s"),CatID);
						DB.ExecuteSQL(SQL);
						for(i=0;i<360;i++)
						{
							SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'V', %lf"),
								CatID, (double)i, Patt[1][i]);
							DB.ExecuteSQL(SQL);
						}
					}
//					SQL.Format(_T("INSERT into AntDiag (AntID, Azm, Polar, Attn) select %s,Azm,Polar,Attn from AntDiag where AntID=%ld and Polar='%s'"),
//						CatID, m_CatID,Values[11].Left(1)==_T("H")?_T("V"):_T("X"));
//					AntPatt.m_pDatabase->ExecuteSQL(SQL);
				}
				if(Pol!="H")
				{
					SQL.Format(_T("Select * from AntDiag where Polar='V' and AntID=%s order by azm"),CatID);
					AntPatt.Open(CRecordset::snapshot, SQL);
					i=0;
					while(!AntPatt.IsEOF())
					{
						//double azm, attn;
						AntPatt.GetFieldValue(_T("Azm"),FVal);
						Patt[0][i]=atof(FVal);
						AntPatt.GetFieldValue(_T("Attn"),FVal);
						Patt[1][i]=atof(FVal);
						AntPatt.MoveNext();
						i++;
					}
					AntPatt.Close();
					if(Azimuth>=0)
					{
						i=359;
						while(Patt[0][i]>359-Azimuth && i>=0)
							i--;
						if(i==-1) i=359;
						for(int j=i;j>=0;j--)
							Patt[0][j]+=Azimuth;
						for(j=i+1;j<360;j++)
							Patt[0][j]-=360-Azimuth;
					}
					else
					{
						i=0;
						while(Patt[0][i]<-Azimuth && i<360)
							i++;
						if(i==360) i=0;
						for(int j=i;j<360;j++)
							Patt[0][j]+=Azimuth;
						for(j=0;j<i;j++)
							Patt[0][j]+=360+Azimuth;
					}
					for(j=0;j<360;j++)
					{
						Patt2[0][j]=(double)j;
						Patt2[1][(int)Patt[0][j]]=Patt[1][j];
					}
					SQL.Format(_T("Delete * from AntDiag where Polar='V' and AntID=%s"),CatID);
					DB.ExecuteSQL(SQL);
					for(i=0;i<360;i++)
					{
						SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'V', %lf"),
							CatID, (double)i, Patt2[1][i]);
						DB.ExecuteSQL(SQL);
					}
					if(Pol=="V")
					{
						SQL.Format(_T("Select * from AntDiag where Polar='H' and AntID=%ld order by azm"),m_CatID);
						AntPatt.Open(CRecordset::snapshot, SQL);
						i=0;
						while(!AntPatt.IsEOF())
						{
							//double azm, attn;
							AntPatt.GetFieldValue(_T("Azm"),FVal);
							Patt[0][i]=atof(FVal);
							AntPatt.GetFieldValue(_T("Attn"),FVal);
							Patt[1][i]=atof(FVal);
							AntPatt.MoveNext();
							i++;
						}
						AntPatt.Close();
						SQL.Format(_T("Delete * from AntDiag where Polar='H' and AntID=%s"),CatID);
						DB.ExecuteSQL(SQL);
						for(i=0;i<360;i++)
						{
							SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, 'H', %lf"),
								CatID, (double)i, Patt[1][i]);
							DB.ExecuteSQL(SQL);
						}
					}
//					SQL.Format(_T("INSERT into AntDiag (AntID, Azm, Polar, Attn) select %s,Azm,Polar,Attn from AntDiag where AntID=%ld and Polar='%s'"),
//						CatID, m_CatID,Values[11].Left(1)==_T("V")?_T("H"):_T("Y"));
//					AntPatt.m_pDatabase->ExecuteSQL(SQL);
				}
			}
				if(StClass==_T("BT") || StClass==_T("BC"))
				{
					SQL1.Format(_T("UPDATE AntCat SET AntName = '%s', ClassOfAnt = '%s', AntType = '%s', "), Values[7], Values[8].Left(1), Values[9]);
					SQL2=SQL1;
					SQL1.Format(_T("Pol = '%s', Gain = %s, GainType = '%s', "), Values[10].Left(1),(Values[11].IsEmpty()?"NULL":Values[11]), Values[12].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("AntDir = '%s', "), Values[13].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("BeamWidthH = %s, BeamWidthV = %s, RefAnt = '%s', MaxEffHght =%s, "), 
						(Values[14].IsEmpty()?_T("NULL"):Values[14]), (Values[15].IsEmpty()?_T("NULL"):Values[15]), Values[16], 
						(Values[17].IsEmpty()?_T("NULL"):Values[17]));
					SQL2+=SQL1;
					SQL1.Format(_T("FreqFrom = %s, FreqTo = %s, XPD = %s, "), (Values[18].IsEmpty()?_T("NULL"):Values[18]), 
						(Values[19].IsEmpty()?_T("NULL"):Values[19]), (Values[20].IsEmpty()?_T("NULL"):Values[20]));
					SQL2+=SQL1;
					SQL1.Format(_T("InsLoss = %s "), (Values[21].IsEmpty()?_T("NULL"):Values[21]));
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE AntCatID=%ld"), m_CatID);
					SQL2+=SQL1;
				}
				if(StClass==_T("FB") || StClass==_T("ML"))
				{
					SQL1.Format(_T("UPDATE AntCat SET AntName = '%s', ClassOfAnt = '%s', AntType = '%s', "), Values[7], Values[8].Left(1), Values[9]);
					SQL2=SQL1;
					SQL1.Format(_T("Pol = '%s', Gain = %s, GainType = '%s', "), Values[10].Left(1),(Values[11].IsEmpty()?"NULL":Values[11]), Values[12].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("AntDir = '%s', "), Values[13].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("BeamWidthH = %s, BeamWidthV = %s, RefAnt = '%s', "), 
						(Values[14].IsEmpty()?_T("NULL"):Values[14]), (Values[15].IsEmpty()?_T("NULL"):Values[15]), Values[16]);
					SQL2+=SQL1;
					SQL1.Format(_T("FreqFrom = %s, FreqTo = %s, XPD = %s, "), (Values[17].IsEmpty()?_T("NULL"):Values[17]), 
						(Values[18].IsEmpty()?_T("NULL"):Values[18]), (Values[19].IsEmpty()?_T("NULL"):Values[19]));
					SQL2+=SQL1;
					SQL1.Format(_T("InsLoss = %s "), (Values[20].IsEmpty()?_T("NULL"):Values[20]));
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE AntCatID=%ld"), m_CatID);
					SQL2+=SQL1;
				}
				if(StClass==_T("FX"))
				{
					SQL1.Format(_T("UPDATE AntCat SET AntName = '%s', ClassOfAnt = '%s', AntType = '%s', "), Values[8], Values[9].Left(1), Values[10]);
					SQL2=SQL1;
					SQL1.Format(_T("Pol = '%s', Gain = %s, GainType = '%s', "), Values[11].Left(1),(Values[12].IsEmpty()?"NULL":Values[12]), Values[13].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("AntDir = '%s', "), Values[14].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("BeamWidthH = %s, BeamWidthV = %s, RefAnt = '%s', "), 
						(Values[15].IsEmpty()?_T("NULL"):Values[15]), (Values[16].IsEmpty()?_T("NULL"):Values[16]), Values[17]);
					SQL2+=SQL1;
					SQL1.Format(_T("FreqFrom = %s, FreqTo = %s, XPD = %s, "), (Values[18].IsEmpty()?_T("NULL"):Values[18]), 
						(Values[19].IsEmpty()?_T("NULL"):Values[19]), (Values[20].IsEmpty()?_T("NULL"):Values[20]));
					SQL2+=SQL1;
					SQL1.Format(_T("InsLoss = %s "), (Values[21].IsEmpty()?_T("NULL"):Values[21]));
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE AntCatID=%ld"), m_CatID);
					SQL2+=SQL1;
				}
				if(Typ==MONITORING)
				{
					SQL1.Format(_T("UPDATE AntCat SET AntName = '%s', AntType = '%s', "), Values[7], Values[8]);
					SQL2=SQL1;
					SQL1.Format(_T("Pol = '%s', Gain = %s, GainType = '%s', "), Values[9].Left(1),(Values[10].IsEmpty()?"NULL":Values[10]), Values[11].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("AntDir = '%s', "), Values[12].Left(1));
					SQL2+=SQL1;
					SQL1.Format(_T("BeamWidthH = %s, BeamWidthV = %s, "), 
						(Values[13].IsEmpty()?_T("NULL"):Values[13]), (Values[14].IsEmpty()?_T("NULL"):Values[14]));
					SQL2+=SQL1;
					SQL1.Format(_T("FreqFrom = %s, FreqTo = %s "), (Values[15].IsEmpty()?_T("NULL"):Values[15]), 
						(Values[16].IsEmpty()?_T("NULL"):Values[16]));
					SQL2+=SQL1;
					SQL1.Format(_T("WHERE AntCatID=%ld"), m_CatID);
					SQL2+=SQL1;
				}
				DB.ExecuteSQL(SQL2);
			if(StClass==_T("BT") || StClass==_T("BC") || StClass==_T("FB") || StClass==_T("ML") || Typ==MONITORING)
			{
				SQL2.Format(_T("UPDATE Antenna SET Azimuth = %s, Elevation = %s, AntHeightAGL = %s, AntCatID=%ld "), 
					(Values[4].IsEmpty()?_T("NULL"):Values[4]),
					(Values[5].IsEmpty()?_T("NULL"):Values[5]),(Values[6].IsEmpty()?(StClass==_T("ML")?_T("1.5"):_T("37.5")):Values[6])
					, m_CatID);
				SQL1.Format(_T("WHERE AntID=%ld"), m_RecID);
				SQL2+=SQL1;
			}
			if(StClass==_T("FX"))
			{
				SQL2.Format(_T("UPDATE Antenna SET Azimuth = %s, AzimTo = %s, Elevation = %s, AntHeightAGL = %s, AntCatID=%ld "), 
					(Values[4].IsEmpty()?_T("NULL"):Values[4]),(Values[5].IsEmpty()?_T("NULL"):Values[5]),
					(Values[6].IsEmpty()?_T("NULL"):Values[6]),(Values[7].IsEmpty()?_T("37.5"):Values[7]), m_CatID);
				SQL1.Format(_T("WHERE AntID=%ld"), m_RecID);
				SQL2+=SQL1;
			}
			//if(RS.IsOpen()) RS.Close();
			DB.Close();
			DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
			DB.ExecuteSQL(SQL2);
			CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
			CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
			if(StClass==_T("FX"))
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Antenna: ")+Values[8]);
			else
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Antenna: ")+Values[7]);

			AddTrail(_Z("Update antenna"),m_RecID,"Antenna");
			result=true;
		}
	}
	else
		result=false;
//	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

double CTreeviewView::GetFreqUnit(CString Unit)
{
	if(!Unit.Compare(_T("kHz")))		return 1000.;
	if(!Unit.Compare(_T("MHz")))		return 1000000.;
	if(!Unit.Compare(_T("GHz")))		return 1000000000.;
	return 1.;
}

void CTreeviewView::ModifyData()
{
	m_Refresh=true;
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	pView->GetTreeCtrl().EnableWindow(false);

	m_ReadOnly=false;
	m_Action=2;  // Edit
	RedrawWindow();
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ANTENNA))->EnableWindow(true);
}

void CTreeviewView::AddOwner()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	SQL="Select * from Owner where ID=-1";
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Owner information"));
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,2);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,0);
	m_Grid->SetRows(RS.GetODBCFieldCount());
	for(int i=1, j=1;i<RS.GetODBCFieldCount();i++, j++)
	{
		CString Value="",Unit,Format,Srv,Mask;
//		RS.GetFieldValue(i,Value);
		m_Grid->SetTextMatrix(j,1,Value);
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		m_Grid->SetTextMatrix(j,0,GetFieldName(&DB, _T("Owner"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask));
		m_Mask[0][j]=Mask;
		m_Mask[1][j]=Format;
		if(i==4)
			m_Grid->SetRowData(j,1);
		if(i==12)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j,0,_Z("Billing"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(12);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(14);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(15);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
/*	CDBVariant TempVar;
	CString m_Tbl=_T("select * from Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();*/	
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	DB.Close();
	m_Grid->SetFixedRows(1);
}

void CTreeviewView::AddLicense()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	SQL=_T("Select * from License where LicID=-1");
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("License Information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,2);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,0);
	m_Grid->SetRows(RS.GetODBCFieldCount()-3);
	CString FName,Value,Unit,Format,Srv,Mask;
	for(int i=4,j=1;i<RS.GetODBCFieldCount();i++,j++)
	{
		Value=_T("");
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("License"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			m_Grid->SetRows(m_Grid->GetRows()-1);
			j--;
			continue;
		}
		m_Mask[0][j]=Mask;
		m_Mask[1][j]=Format;
		m_Grid->SetTextMatrix(j,0,FName);
//		if(i==5 || i==6)
//		{
//			Value=(i==5?_T("00:00"):_T("23:59"));
//			m_Grid->SetRowData(j+1,8);
//		}
		if(i==5 || i==6)
		{
			CTime Today =CTime::GetCurrentTime();
			Value.Format(_T("%04d/%02d/%02d"),(i==5?Today.GetYear():Today.GetYear()+1),Today.GetMonth(),Today.GetDay());
			m_Grid->SetRowData(j,8);
		}
		m_Grid->SetTextMatrix(j,1,Value);
		if(i==7)
			m_Grid->SetRowData(j,1);
		if(i==8)
			m_Grid->SetRowData(j,2);
		if(i==8)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j,0,_Z("Billing"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==10)
			m_Grid->SetRowData(j,3);
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(7);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	CDBVariant TempVar;
	CString m_Tbl=_T("select StatusEn from LicStatus");
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl.Format(_T("SELECT [SrvID],[SrvType%s] FROM SrvType WHERE [Active]=Yes"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Tbl=_T("SELECT InvPeriodEn FROM InvoicePeriod");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::AddStation()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	SQL=_T("Select Station.*,stSrv from Station,StClass where StClass.StClassID=Left(Station.ClassStation,2) and StID=-1");
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Fixed/Base station information"));
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
//	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
//	Value.TrimRight(" ");
//	m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-4);
	for(int i=4,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
//		RS.GetFieldValue(i,Value);
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("Station"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(i==8)
			m_Grid->SetRowData(j+1,1);
		if(i==9)
			m_Grid->SetRowData(j+1,2);
		if(i==13 || i==17)
			m_Grid->SetRowData(j+1,3);
		if(i==16)
			m_Grid->SetRowData(j+1,4);
		if(i==10)
			m_Grid->SetRowData(j+1,5);
		if(i==21)
			m_Grid->SetRowData(j+1,6);
		if(i==9)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Location"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==15)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(6);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetTextMatrix(6,1,_T("Fixed"));
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	//m_Grid->SetRow(9);
	//m_Grid->SetCellFontBold(true);
	//m_Grid->SetRow(10);
	//m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(13);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(15);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(20);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetTextMatrix(20,1,_T("T11"));
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	CDBVariant TempVar;
	CString m_Tbl;
	if(m_Service==_T("MT"))
	{
		m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
		m_Combo1->ResetContent();
		m_Combo1->AddString(_T(""));
		m_Combo1->AddString(_T("T12"));
		m_Combo1->AddString(_T("T14"));
		m_Combo1->AddString(_T("G12"));
		m_Combo1->AddString(_T("G14"));
		m_Tbl.Format(_T("select StClassID, StClass%s from StClass where StClassID='FB'"),m_Lang);
	}
	else
	{
		m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
		m_Combo1->ResetContent();
		m_Combo1->AddString(_T(""));
		m_Combo1->AddString(_T("T11"));
		m_Combo1->AddString(_T("T14"));
		m_Combo1->AddString(_T("G11"));
		m_Combo1->AddString(_T("G14"));
		m_Tbl.Format(_T("select StClassID, StClass%s from StClass where StSrv='%s'"),m_Lang,m_Service);
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
//	m_Tbl=_T("SELECT * from StType");
//	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
//	while(1)
//	{
//		if(RS.IsEOF()) break;
//		RS.GetFieldValue((short)0,F1);
//		m_Combo1->AddString(F1);
//		RS.MoveNext();
//	}
//	RS.Close();	
	m_Combo1->AddString(_T("Fixed"));
	m_Combo1->AddString(_T("Typical"));	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
/*	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl=_T("SELECT * FROM Provisions");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Grid->SetFixedRows(1);
}

void CTreeviewView::AddBCStation()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	SQL=_T("Select BCStation.*,stSrv from BCStation,StClass where StClass.StClassID=Left(BCStation.ClassStation,2) and StID=-1");
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Broadcasting station information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
//	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
//	Value.TrimRight(" ");
//	m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-5);
	for(int i=4,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
//		RS.GetFieldValue(i,Value);
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("BCStation"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(i==8)
			m_Grid->SetRowData(j+1,1);
		if(i==9)
			m_Grid->SetRowData(j+1,2);
		if(i==13)
			m_Grid->SetRowData(j+1,3);
		if(i==16)
			m_Grid->SetRowData(j+1,4);
		if(i==17)
			m_Grid->SetRowData(j+1,5);
		if(i==10)
			m_Grid->SetRowData(j+1,6);
		if(i==20)
			m_Grid->SetRowData(j+1,7);
		if(i==21)
			m_Grid->SetRowData(j+1,11);
		if(i==25)
			m_Grid->SetRowData(j+1,12);
		if(i==26)
			m_Grid->SetRowData(j+1,12);
		if(i==27)
			m_Grid->SetRowData(j+1,13);
		if(i==9)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Location"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==15)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==19)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Geneva 06"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(6);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetTextMatrix(6,1,_T("Fixed"));
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(9);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(10);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(13);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(15);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(27);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetTextMatrix(27,1,_T("T01"));
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl.Format(_T("select StClassID, StClass%s from StClass where StSrv='%s'"),m_Lang,m_Service);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
//	m_Tbl=_T("SELECT * from StType");
//	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
//	while(1)
//	{
//		if(RS.IsEOF()) break;
//		RS.GetFieldValue((short)0,F1);
//		m_Combo1->AddString(F1);
//		RS.MoveNext();
//	}
//	RS.Close();	
	m_Combo1->AddString(_T("Fixed"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
/*	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl=_T("SELECT * FROM Provisions");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Tbl=_T("SELECT * FROM Plans");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1->AddString(_T("4"));
	m_Combo1->AddString(_T("5"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("C"));
	m_Combo1->AddString(_T("L"));
	m_Combo1->AddString(_T("S"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO9);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("Yes"));
	m_Combo1->AddString(_T("No"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO10);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("GS1"));
	m_Combo1->AddString(_T("GT1"));
	m_Combo1->AddString(_T("G02"));
	m_Combo1->AddString(_T("GB1"));
	m_Combo1->AddString(_T("T01"));
	m_Combo1->AddString(_T("T02"));
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::AddMobile()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	SQL=_T("Select Mobiles.*,stSrv from Mobiles,StClass where StClass.StClassID=Left(Mobiles.ClassStation,2) and MobID=-1");
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Mobile station information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
//	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
//	Value.TrimRight(" ");
//	m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-2);
	for(int i=2,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
//		RS.GetFieldValue(i,Value);
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("Mobiles"), FldInfo.m_strName,_T("En"), &Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(i==6)
			m_Grid->SetRowData(j+1,1);
		if(i==7)
			m_Grid->SetRowData(j+1,2);
		if(i==8)
			m_Grid->SetRowData(j+1,5);
		if(i==11 || i==13)
			m_Grid->SetRowData(j+1,3);
		if(i==15)
			m_Grid->SetRowData(j+1,4);
		if(i==20)
			m_Grid->SetRowData(j+1,6);
		if(i==7)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Location"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==13)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==16)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Vehicle"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(6);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetTextMatrix(6,1,_T("Mounted"));
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(9);
//	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(10);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(16);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(22);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl.Format(_T("select StClassID, StClass%s from StClass where StClassID='ML'"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl=_T("SELECT StTypeEn from StType");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		if(F1!=_T("Fixed") && F1!=_T("Base") && F1!=_T("Typical")) m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
/*	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl=_T("SELECT * FROM Provisions");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("T13"));
	m_Combo1->AddString(_T("G13"));
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::AddEquipment()
{
	CString SQL,StClass,SQL1;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(true);
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==STATION)
	{
		SQL.Format(_T("Select ClassStation from Station where StID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.Close();
		SQL1=_T("SELECT EqName, Pwr2Ant, PowerType, RadPwr, RadPowerType, MadeBy, Model, SerialNo, ");
		SQL1+=_T("OsetV12, OsetV, OsetS12, OsetS, TranSys,TVSys,ColorSys, ERP_h_dbw, ERP_v_dbw, ERP_dbw, PwrRatio,EU_Ref, ");
		SQL1+=_T("Sensitivity, EnDisp, GndCond, RJ81, AdjRatio, FreqStabl, AngSep,NoiseFactor,ClassOp, RefPlanCfg, SysVar, RXMode, ERPTilt, Tilt, SystemType1, SystemType2, MaxPowDens,StSrv,ClassStation ");
		SQL=_T("FROM Equipment,EqCat,Station,StClass where StClass.StClassID=Station.ClassStation and Station.StID=Equipment.StID and Equipment.EqCatID=EqCat.EqCatID and EqID=-1");
		SQL=SQL1+SQL;
	}
	if(Typ==BC)
	{
		SQL.Format(_T("Select ClassStation from BCStation where StID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.Close();
		SQL1=_T("SELECT EqName, Pwr2Ant, PowerType, RadPwr, RadPowerType, MadeBy, Model, SerialNo, ");
		SQL1+=_T("OsetV12, OsetV, OsetS12, OsetS, TranSys,TVSys,ColorSys, ERP_h_dbw, ERP_v_dbw, ERP_dbw, PwrRatio,EU_Ref, ");
		SQL1+=_T("Sensitivity, EnDisp, GndCond, RJ81, AdjRatio, FreqStabl, AngSep,NoiseFactor,ClassOp, RefPlanCfg, SysVar, RXMode, ERPTilt, Tilt, SystemType1, SystemType2, MaxPowDens,StSrv,ClassStation ");
		SQL=_T("FROM Equipment,EqCat,BCStation,StClass where StClass.StClassID=BCStation.ClassStation and BCStation.StID=Equipment.BCID and Equipment.EqCatID=EqCat.EqCatID and EqID=-1");
		SQL=SQL1+SQL;
	}
	if(Typ==MOBILE)
	{
		SQL.Format(_T("Select ClassStation from Mobiles where MobID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.Close();
		SQL1=_T("SELECT EqName, Pwr2Ant, PowerType, RadPwr, RadPowerType, MadeBy, Model, SerialNo, ");
		SQL1+=_T("OsetV12, OsetV, OsetS12, OsetS, TranSys,TVSys,ColorSys, ERP_h_dbw, ERP_v_dbw, ERP_dbw, PwrRatio,EU_Ref, ");
		SQL1+=_T("Sensitivity, EnDisp, GndCond, RJ81, AdjRatio, FreqStabl, AngSep,NoiseFactor,ClassOp, RefPlanCfg, SysVar, RXMode, ERPTilt, Tilt, SystemType1, SystemType2,MaxPowDens,StSrv,ClassStation ");
		SQL=_T("FROM Equipment,EqCat,Mobiles,StClass where StClass.StClassID=Mobiles.ClassStation and Mobiles.MobID=Equipment.MobID and Equipment.EqCatID=EqCat.EqCatID and EqID=-1");
		SQL=SQL1+SQL;
	}
	StClass=StClass.Left(2);
	RS.Open(CRecordset::dynaset,SQL);
	((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Library"));
	//((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowPos(NULL,0,0,80,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Equipment information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
//	m_Grid->SetBackColorBand(0,0xDFDFDF);
	m_Grid->SetCols(0,4);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	int j;
	m_Grid->SetRows(RS.GetODBCFieldCount()-1);
	for(int i=0;i<m_Grid->GetRows();i++)
		m_Grid->SetRowData(i,0);
	Value=_T("");
	for(i=0,j=0;i<RS.GetODBCFieldCount()-2;i++,j++)
	{
//		RS.GetFieldValue(i,Value);
		if(Typ==BC && (i==3 || i==4))
			continue;
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		if(i==1 || i==3)
			FName=GetFieldName(&DB, _T("Equipment"), FldInfo.m_strName,_T("En"), &Unit,&Format,&Srv,&Mask);
		else
			FName=GetFieldName(&DB, _T("EqCat"), FldInfo.m_strName,_T("En"), &Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		m_Grid->SetTextMatrix(j+1,3,Srv);
		if(i==2)
			m_Grid->SetRowData(j+1,1);
		if(i==4)
			m_Grid->SetRowData(j+1,2);
		if(i==12) //13
			m_Grid->SetRowData(j+1,7);
		if(i==13) //14
			m_Grid->SetRowData(j+1,3);
		if(i==14) //15
			m_Grid->SetRowData(j+1,4);
		if(i==25) //26
			m_Grid->SetRowData(j+1,6);
		if((StClass!=_T("BT") && StClass!=_T("BC")) && (i==34 || i==35)) //35 || 36
			m_Grid->SetRowData(j+1,5);
		if(i==29) //30
			m_Grid->SetRowData(j+1,11);
		if(i==30) //31
			m_Grid->SetRowData(j+1,12);
		if(i==31) //32
			m_Grid->SetRowData(j+1,5);

		if(i==0)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Power"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(Typ==BC)
		{
			if(i==2)
			{
				j++;
				m_Grid->SetRows(m_Grid->GetRows()+1);
				m_Grid->SetCol(0);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
				m_Grid->SetCellForeColor(0x00FFFF);
				m_Grid->SetTextMatrix(j+1,0,_Z("Physical"));
				m_Grid->SetCellFontItalic(true);
				m_Grid->SetCol(1);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
				m_Grid->SetCol(2);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
			}
		}
		else
		{
			if(i==4)
			{
				j++;
				m_Grid->SetRows(m_Grid->GetRows()+1);
				m_Grid->SetCol(0);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
				m_Grid->SetCellForeColor(0x00FFFF);
				m_Grid->SetTextMatrix(j+1,0,_Z("Physical"));
				m_Grid->SetCellFontItalic(true);
				m_Grid->SetCol(1);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
				m_Grid->SetCol(2);
				m_Grid->SetRow(j+1);
				m_Grid->SetCellBackColor(0x7F7F7F);
			}
		}
		if(i==7)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Broadcasting"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==19)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==27)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Geneva 06"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
	}
	RS.Close();
	m_Grid->SetRow(1);
	m_Grid->SetCol(0);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	if(StClass==_T("BT"))
	{
///		m_Grid->SetRow(14);
///		m_Grid->SetCellFontBold(true);
///		m_Grid->SetRow(15);
///		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(16);
//		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(17);
//		m_Grid->SetCellFontBold(true);
///		m_Grid->SetRow(21);
///		m_Grid->SetCellFontBold(true);
		m_Grid->SetTextMatrix(21,1,_T("10"));
	}
	if(StClass==_T("BC"))
	{
///		m_Grid->SetRow(10);
///		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(12);
//		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(13);
//		m_Grid->SetCellFontBold(true);
	}
	if(StClass==_T("FX"))
	{
		m_Grid->SetRow(12); //13
		m_Grid->SetCellFontBold(true);
	}
	if(StClass==_T("FX") || StClass==_T("ML") || StClass==_T("FB"))
	{
		m_Grid->SetRow(5);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6);
		m_Grid->SetCellFontBold(true);
	}
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Grid->SetCol(2);
	for(i=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0x7F7F7F)
		{
			CString Val=m_Grid->GetTextMatrix(i,3);
			if(Val.Find(StClass,0)==-1)
			{
				RowDelete(i);
				i--;
			}
		}
		else
		{
			if(StClass!=_T("BT") && StClass!=_T("BC") && m_Grid->GetTextMatrix(i,0)==_Z("Broadcasting"))
				{
					RowDelete(i);
					i--;
				}
			else
				if(StClass==_T("BC") && m_Grid->GetTextMatrix(i,0)==_Z("Misc."))
				{
					RowDelete(i);
					i--;
				}
		}
	}
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl.Format(_T("select LU_DATA, LU_PROMPT_%s from PowerType"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		if(StClass==_T("FX") || StClass==_T("FB") || StClass==_T("ML") ||
			(StClass==_T("BC") && F1==_T("Y")) || (StClass==_T("BT") && (F1==_T("Y") || F1==_T("X"))))
		{
			RS.GetFieldValue((short)1,F2);
			m_Combo1->AddString(F1+_T(" - ")+F2);
		}
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl=_T("SELECT * from RadPowerType");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Tbl.Format(_T("SELECT SysCode, SysName%s FROM TVSys order by SysCode"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl=_T("SELECT distinct ColNameEn FROM ColorSys");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
//		RS.GetFieldValue((short)1,F2);
//		m_Combo1->AddString(F1+_T(" - ")+F2);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Tbl.Format(_T("SELECT Code, Desc%s FROM SysType order by Code"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Tbl=_T("SELECT StabTextEn FROM FreqStab");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
	m_Tbl.Format(_T("SELECT Code, Text%s FROM TranSys"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	if(StClass==_T("BT"))
	{
		m_Combo1->AddString(_T("RPC1"));
		m_Combo1->AddString(_T("RPC2"));
		m_Combo1->AddString(_T("RPC3"));
	}
	else
	{
		m_Combo1->AddString(_T("RPC4"));
		m_Combo1->AddString(_T("RPC5"));
	}
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO9);
	m_Tbl=_T("SELECT * FROM SysVar");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	if(StClass==_T("BT") || StClass==_T("BC"))
	{
		m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
		m_Combo1->ResetContent();
		CString T=_Z("Fixed");
		T="FX - "+T;
		m_Combo1->AddString(T);
		T=_Z("Portable Outdoor");
		T="PO - "+T;
		m_Combo1->AddString(T);
		T=_Z("Portable Indoor");
		T="PI - "+T;
		m_Combo1->AddString(T);
		T=_Z("Mobile Outdoor");
		T="MO - "+T;
		m_Combo1->AddString(T);
	}
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->SetCols(0,3);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::AddFrequency()
{
	CString SQL,StClass,StType;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(false);
	RS.m_pDatabase=&DB;
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem());
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==STATION)
	{
		SQL.Format(_T("Select ClassStation,StType from Station,Equipment where Station.StID=Equipment.StID and Station.StID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.GetFieldValue((short)1,StType);
		RS.Close();
		SQL.Format(_T("Select Frequency.*,StSrv from Frequency,Equipment,Station,StClass where StClass.StClassID=Left(Station.ClassStation,2) and Station.StID=Equipment.StID and Equipment.EqID=Frequency.EqID and FreqID=-1"));
	}
	if(Typ==BC)
	{
		SQL.Format(_T("Select ClassStation,StType from BCStation,Equipment where BCStation.StID=Equipment.BCID and BCStation.StID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.GetFieldValue((short)1,StType);
		RS.Close();
		SQL.Format(_T("Select Frequency.*,StSrv from Frequency,Equipment,BCStation,StClass where StClass.StClassID=Left(BCStation.ClassStation,2) and BCStation.StID=Equipment.BCID and Equipment.EqID=Frequency.EqID and FreqID=-1"));
	}
	if(Typ==MOBILE)
	{
		SQL.Format(_T("Select ClassStation,StType from Mobiles,Equipment where Mobiles.MobID=Equipment.MobID and Mobiles.MobID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.GetFieldValue((short)1,StType);
		RS.Close();
		SQL.Format(_T("Select Frequency.*,StSrv from Frequency,Equipment,Mobiles,StClass where StClass.StClassID=Left(Mobiles.ClassStation,2) and Mobiles.MobID=Equipment.MobID and Equipment.EqID=Frequency.EqID and FreqID=-1"));
	}
	StClass=StClass.Left(2);
	RS.Open(CRecordset::dynaset,SQL);
	//((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowPos(NULL,0,0,80,20 ,SWP_NOMOVE|SWP_NOZORDER);;
//	if(Typ==MOBILE)
//		((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Add transmitter"));
//	else
	if(StType==_T("Typical"))
		((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	else
		((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
//		((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_T("Service area"));
//	else
		((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Add receiver"));
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Frequency information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,4);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	//RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
	//Value.TrimRight(_T(" "));
	//m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-2);	
	Value="";
	for(int i=2,j=0;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
//		RS.GetFieldValue(i,Value);
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("Frequency"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		if(m_Grid->GetTextMatrix(j+1,2).IsEmpty()) m_Grid->SetTextMatrix(j+1,2,Unit);
		m_Grid->SetTextMatrix(j+1,3,Srv);
		//if(i==18 || i==19)
		//{
		//	m_Grid->SetRowData(j+1,9);
		//}
		if(i==2 || i==3 || i==4)
		{
			double Freq=atof(Value),factor=1;
			if(Freq<1000.) m_Grid->SetTextMatrix(j+1,2,_T("Hz"));
			else if(Freq<1000000.) {m_Grid->SetTextMatrix(j+1,2,_T("kHz")); factor=1000.;}
			else if(Freq<1000000000.) {m_Grid->SetTextMatrix(j+1,2,_T("MHz")); factor=1000000.;}
			else {m_Grid->SetTextMatrix(j+1,2,_T("GHz")); factor=1000000000.;}

//			Value.Format(_T("%lf"),Freq/factor);
//			Value.TrimLeft(_T(" "));
//			Value.TrimRight(_T("0"));
			
			m_Grid->SetRowData(j+1,100);
		}
		m_Grid->SetTextMatrix(j+1,1,Value);
		if(m_Grid->GetTextMatrix(j+1,2).IsEmpty()) m_Grid->SetTextMatrix(j+1,2,Unit);
		if(i==17)
			m_Grid->SetRowData(j+1,2);
		if(i==8)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Misc."));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==19)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Fee"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==23)
			m_Grid->SetRowData(j+1,3);
	}
	RS.Close();
	m_Grid->SetCol(0);
	if(StClass==_T("BT"))
	{
		m_Grid->SetRow(1);
		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(2);
//		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(3);
//		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(5);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6);
		m_Grid->SetCellFontBold(true);
//		m_Grid->SetRow(13);
//		m_Grid->SetCellBackColor(0x7F7F7F);
//		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(14);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(16);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetCol(1);
		m_Grid->SetRow(16);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetText(_T("CP"));
	}
	if(StClass==_T("BC"))
	{
		m_Grid->SetRow(1);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(3);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(4);
		m_Grid->SetCellFontBold(true);
//		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(10);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(11);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetCol(1);
		m_Grid->SetRow(16);
		m_Grid->SetCellBackColor(0xDFDFDF);
		m_Grid->SetText(_T("CP"));
	}
	if(StClass==_T("FX") || StClass==_T("ML") || StClass==_T("FB"))
	{
		m_Grid->SetRow(1);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(2);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(7);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(12);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(14);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(16);
		m_Grid->SetCellFontBold(true);
	}
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetCol(2);
	for(i=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0x7F7F7F)
		{
			CString Val=m_Grid->GetTextMatrix(i,3);
			if(Val.Find(StClass,0)==-1)
			{
				RowDelete(i);
				i--;
			}
		}
	}
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl=_T("select * from FreqUnit");
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)1,F1);
		m_Combo1->AddString(F1);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl.Format(_T("SELECT LU_DATA, LU_PROMPT_%s from NatServ"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1->AddString(_T("N"));
	m_Combo1->AddString(_T("S"));
	m_Grid->SetFixedRows(1);
	m_Grid->SetCols(0,3);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::AddAntenna()
{
	CString SQL,StClass;
	CDatabase	DB;
	CRecordset	RS;
	m_CatID=-1;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ATTACH))->EnableWindow(true);
	//((CButton *)GetDlgItem(IDC_ANTENNA))->SetWindowPos(NULL,0,0,80,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	((CButton *)GetDlgItem(IDC_ANTENNA))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_ANTENNA))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ANTENNA))->SetWindowText(_Z("Add to Lib."));
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	int Typ;
	HTREEITEM Node=pView->GetTreeCtrl().GetParentItem(pView->GetTreeCtrl().GetSelectedItem());
	pView->GetTreeCtrl().GetItemImage(Node,Typ,Typ);
	if(Typ==STATION)
	{
		SQL.Format(_T("Select ClassStation from Station,Equipment where Station.StID=Equipment.StID and Station.StID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.Close();
		SQL.Format(_T("Select Antenna.*,AntCat.*,StSrv from Antenna,AntCat,Equipment,Station,StClass where StClass.StClassID=Left(Station.ClassStation,2) and Station.StID=Equipment.StID and Equipment.EqID=Antenna.EqID and Antenna.AntCatID=AntCat.AntCatID and AntID=-1"));
	}
	if(Typ==BC)
	{
		SQL.Format(_T("Select ClassStation from BCStation,Equipment where BCStation.StID=Equipment.BCID and BCStation.StID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.Close();
		SQL.Format(_T("Select Antenna.*,AntCat.*,StSrv from Antenna,AntCat,Equipment,BCStation,StClass where StClass.StClassID=Left(BCStation.ClassStation,2) and BCStation.StID=Equipment.BCID and Equipment.EqID=Antenna.EqID and Antenna.AntCatID=AntCat.AntCatID and AntID=-1"));
	}
	if(Typ==MOBILE)
	{
		SQL.Format(_T("Select ClassStation from Mobiles,Equipment where Mobiles.MobID=Equipment.MobID and Mobiles.MobID=%ld"),pView->GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,StClass);
		RS.Close();
		SQL.Format(_T("Select Antenna.*,AntCat.*,StSrv from Antenna,AntCat,Equipment,Mobiles,StClass where StClass.StClassID=Left(Mobiles.ClassStation,2) and Mobiles.MobID=Equipment.MobID and Equipment.EqID=Antenna.EqID and Antenna.AntCatID=AntCat.AntCatID and AntID=-1"));
	}
	StClass=StClass.Left(2);
	RS.Open(CRecordset::dynaset,SQL);
	//((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowPos(NULL,0,0,50,20 ,SWP_NOMOVE|SWP_NOZORDER);;
	((CButton *)GetDlgItem(IDC_ATTACH))->SetWindowText(_Z("Library"));
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_SHOW);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("Antenna information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
//	m_Grid->SetBackColorBand(0,0xDFDFDF);
	m_Grid->SetCols(0,4);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
//	RS.GetFieldValue(RS.GetODBCFieldCount()-1,Value);
//	Value.TrimRight(_T(" "));
//	m_Service=Value;
	m_Grid->SetRows(RS.GetODBCFieldCount()-4);
	Value=_T("");
	int j=0;
	m_Grid->SetRows(m_Grid->GetRows()+1);
	m_Grid->SetCol(0);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetCellForeColor(0x00FFFF);
	m_Grid->SetTextMatrix(j+1,0,_Z("Installation"));
	m_Grid->SetCellFontItalic(true);
	m_Grid->SetCol(1);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	m_Grid->SetCol(2);
	m_Grid->SetRow(j+1);
	m_Grid->SetCellBackColor(0x7F7F7F);
	j++;
	for(int i=3;i<RS.GetODBCFieldCount()-1;i++,j++)
	{
//		RS.GetFieldValue(i,Value);
		if(i==7) { j--; continue;}
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		if(i>7)
			FName=GetFieldName(&DB, _T("AntCat"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		else
			FName=GetFieldName(&DB, _T("Antenna"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		m_Grid->SetTextMatrix(j+1,3,Srv);
		if(i==5)
			m_Grid->SetTextMatrix(j+1,1,_T("0"));
		if(i==6)
		{
			j++;
			m_Grid->SetRows(m_Grid->GetRows()+1);
			m_Grid->SetCol(0);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCellForeColor(0x00FFFF);
			m_Grid->SetTextMatrix(j+1,0,_Z("Technical"));
			m_Grid->SetCellFontItalic(true);
			m_Grid->SetCol(1);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
			m_Grid->SetCol(2);
			m_Grid->SetRow(j+1);
			m_Grid->SetCellBackColor(0x7F7F7F);
		}
		if(i==9)
			m_Grid->SetRowData(j+1,1);
		if(i==11)
			m_Grid->SetRowData(j+1,2);
		if(i==13)
			m_Grid->SetRowData(j+1,3);
		if(i==14)
			m_Grid->SetRowData(j+1,4);
	}
	RS.Close();
	m_Grid->SetCol(0);
	if(StClass==_T("BT") || StClass==_T("BC") || StClass==_T("FB") || StClass==_T("ML"))
	{
		m_Grid->SetRow(2);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(3);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(4);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(6);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(7);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(9);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(10);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(12);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
	}
	if(StClass==_T("FX"))
	{
		m_Grid->SetRow(2);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(4);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(5);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(7);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(8);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(10);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(11);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(13);
		m_Grid->SetCellFontBold(true);
		m_Grid->SetRow(14);
		m_Grid->SetCellFontBold(true);
	}
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetCol(2);
	for(i=1;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0x7F7F7F)
		{
			CString Val=m_Grid->GetTextMatrix(i,3);
			if(Val.Find(StClass,0)==-1)
			{
				RowDelete(i);
				i--;
			}
		}
	}
	int Factor=-1;
	if(StClass==_T("FX")) Factor=0;
	m_Grid->SetCol(1);
	m_Grid->SetRow(7+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(10+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(11+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(12+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(13+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(14+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(15+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	if(StClass==_T("BC") || StClass==_T("BT"))
		Factor++;
	m_Grid->SetRow(17+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetRow(18+Factor);
	m_Grid->SetCellBackColor(0xDFDFDF);
	CDBVariant TempVar;
	CString m_Tbl;
	m_Tbl.Format(_T("select AntClassID, AntClass%s from AntClass"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	CString F1,F2;
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		if(((StClass==_T("BC") || StClass==_T("BT")) && F1!=("T")))
			RS.MoveNext();
		else
		{
			RS.GetFieldValue((short)1,F2);
			m_Combo1->AddString(F1+_T(" - ")+F2);
			RS.MoveNext();
		}
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Tbl.Format(_T("SELECT PolID, PolText%s from PolType"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Tbl.Format(_T("SELECT GtypeID, GTypeText%s FROM GainType"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Tbl.Format(_T("SELECT AntDirCode, AntDirectivity%s FROM AntDir"),m_Lang);
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->SetCols(0,3);
	m_Grid->ShowWindow(SW_SHOW);
}

void CTreeviewView::OnKillfocusCombo1() 
{
	CString Text;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->GetWindowText(Text);
	m_Grid->SetText(Text);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_OnEdit=false;
}

void CTreeviewView::OnKillfocusCombo2() 
{
	CString Text;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
	m_Combo1->GetWindowText(Text);
	m_Grid->SetText(Text);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_OnEdit=false;	
}

void CTreeviewView::OnKillfocusCombo3() 
{
	CString Text;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Combo1->GetWindowText(Text);
	m_Grid->SetText(Text);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_OnEdit=false;	
}

void CTreeviewView::OnKillfocusCombo4() 
{
	CString Text;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Combo1->GetWindowText(Text);
	m_Grid->SetText(Text);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_OnEdit=false;	
}

void CTreeviewView::OnKillfocusCombo5() 
{
	CString Text;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Combo1->GetWindowText(Text);
	m_Grid->SetText(Text);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_OnEdit=false;	
}

void CTreeviewView::OnKillfocusCombo6() 
{
	CString Text;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Combo1->GetWindowText(Text);
	m_Grid->SetText(Text);
	m_Combo1->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_OnEdit=false;	
}

void CTreeviewView::OnKillfocusDatepicker(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString Text;
	m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_DATEPICKER);
	m_Date->GetWindowText(Text);
	m_Grid->SetText(Text);
	m_Date->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_OnEdit=false;
	*pResult = 0;
}

void CTreeviewView::OnKillfocusTimepicker(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString Text;
	m_Date=(CDateTimeCtrl *)GetDlgItem(IDC_TIMEPICKER);
	m_Date->GetWindowText(Text);
	m_Grid->SetText(Text);
	m_Date->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,SWP_NOSIZE|SWP_HIDEWINDOW);
	m_OnEdit=false;	
	*pResult = 0;
}

CString CTreeviewView::BWCode(double BW)
{
	int i;
	CString Temp;
	BW*=1000;
	char Code;
	if(BW<1000)
	{
		Code='H';
	}
	if(BW>=1000. && BW<1e+6)
	{
		BW/=1000.;
		Code='K';
	}
	if(BW>=1e+6 && BW<1e+9)
	{
		BW/=1e+6;
		Code='M';
	}
	if(BW>=1e+9 && BW<1e+12)
	{
		BW/=1e+9;
		Code='G';
	}
		int IPart=(int)BW;
		double FPart2=BW-IPart;
		char FP[10], tt[20];
		sprintf(FP,"%.3f",FPart2);
		strcpy(tt,FP+2);

		if(IPart)
		{
			if(FPart2)
				Temp.Format("%d%c%s",IPart,Code,tt);
			else
				Temp.Format("%d%c",IPart,Code);
		}
		else
			Temp.Format("%c%s",Code,tt);

	for(i=Temp.GetLength();i<4;i++)
		Temp+="0";
	Temp=Temp.Left(4);
	return Temp;
}

bool CTreeviewView::OwnerValidation(CString Values[])
{
	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	CString SQL,Rep,Value;
	for(int i=0;i<14;i++)
		Values[i].Replace(_T("\'"),_T(" "));
	RS.m_pDatabase=&DB;
	SQL.Format(_T("select ID from owner where admname='%s'"),Values[1]);
	RS.Open(CRecordset::snapshot,SQL);
	if(RS.GetRecordCount()>0)
	{
		RS.GetFieldValue((short)0,Value);
		if(atol(Value)!=atol(Values[0]))
			Rep=_Z("The name of the owner should be unique!");
	}
	RS.Close();
	DB.Close();
	if(Rep.GetLength())
	{
		AfxMessageBox(Rep);
		return false;
	}
	return true;
}

bool CTreeviewView::LicenseValidation(CString Values[], CString Fields[])
{
	bool Res=true;
	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	CString SQL,Rep,Value;
	RS.m_pDatabase=&DB;
	SQL.Format(_T("select LicID from License where LicNo='%s'"),Values[4]);
	RS.Open(CRecordset::snapshot,SQL);
	if(RS.GetRecordCount()>0)
	{
		RS.GetFieldValue((short)0,Value);
		if(atol(Value)!=atol(Values[0]))
			Rep=_Z("The license number should be unique,");
	}
	RS.Close();
	CString Srv2=Fields[8].Left(2);
	Srv2.TrimRight(_T(" "));

	if(!Srv2.IsEmpty() && Srv2!=Values[8])
	{
		bool SrvUnch=false;
		if(Srv2==_T("F") || Srv2==_T("MT"))
			SQL.Format(_T("Select * from station where licid=%s"),Value);
		else if(Srv2==_T("B"))
			SQL.Format(_T("Select * from bcstation where licid=%s"),Value);
		else 
			SQL.Format(_T("Select * from e_stn where licid=%s"),Value);
		RS.Open(CRecordset::snapshot,SQL);
		if(RS.GetRecordCount()>0)
		{
			Rep+=_Z("There are some stations attached to this License and the service type is unchangeable,");
			SrvUnch=true;
		}
		RS.Close();
		if(!SrvUnch && Srv2==_T("MT"))
		{
			SQL.Format(_T("Select * from mobiles where licid=%s"),Value);
			RS.Open(CRecordset::snapshot,SQL);
			if(RS.GetRecordCount()>0)
				Rep+=_Z("There are some stations attached to this License and the service type is unchangeable,");
			RS.Close();
		}
	}
	DB.Close();
	if(Values[5]>=Values[6])
	{
		Rep+=_Z("The expiration date should be after licensing date,");
		Res=false;
	}
	if(Fields[7].IsEmpty())
	{
		if(Values[7].Left(10)!=_T("Data entry") && Values[7].Left(10)!=_T("Entrée des") && Values[7].Left(10)!=_T("Entrada de"))
		{
			Rep+=_Z("The status of this license should be 'Data entry',");
			Res=false;
		}
	}
	else
	{
		if(Values[7]==_Z("Technical investigation") && Fields[7]!=_Z("Data entry complete"))
		{
			Rep+=_Z("Data entry should be completed before this status,");
			Res=false;
		}
		if(Values[7]==_Z("First invoice unpaid") && Fields[7]!=_Z("Technically OK"))
		{
			Rep+=_Z("Technical investigation should be completed before this status,");
			Res=false;
		}
		if(Values[7]==_Z("Granted") && Fields[7]!=_Z("Financially OK"))
		{
			Rep+=_Z("Financial status should be cleared before this status,");
			Res=false;
		}
		if(Values[7]==_Z("Cancelled") && Fields[7]!=_Z("Granted"))
		{
			Rep+=_Z("Please select the appropriate item from \nthe context menu of license for cancellaion,");
			Res=false;
		}
		if(Values[7]==_Z("Financially OK") && Fields[7]!=Values[7])
		{
			bool Payment;
			if(GetBalance(atol(Value),&Payment)<0)
			{
				Rep+=_Z("The licensee has unpaid invoices,");
				Res=false;
			}
			if(!Payment)
			{
				Rep+=_Z("The first invoice for this license is not issued yet,");
				Res=false;
			}
		}
	}
	if(Rep.GetLength())
	{
		Rep.Delete(Rep.GetLength()-1);
		AfxMessageBox(Rep);
		return false;
	}
	return Res;
}

bool CTreeviewView::StationValidation(CString Values[])
{
	bool res=true;
	CString Rep;
	long UNR = 72 ;
	WDBUNIT(&UNR) ;
	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	CString SQL,Value=_T("-1");
	RS.m_pDatabase=&DB;
	SQL.Format(_T("select StID from Station where SiteID='%s'"),Values[5]);
	RS.Open(CRecordset::snapshot,SQL);
	if(RS.GetRecordCount()>0)
	{
		RS.GetFieldValue((short)0,Value);
		if(atol(Value)!=atol(Values[0]))
			Rep=_Z("The ID of the station should be unique,");
	}
	RS.Close();
	DB.Close();
	if(Values[6]==_T("__"))
	{
		Values[8].TrimRight();
		Values[9].TrimRight();
		Values[8].TrimLeft();
		Values[9].TrimLeft();
		if(Values[8].GetLength()<10)
			Rep+=_Z("Latitude is not complete,");
		if(Values[9].GetLength()<11)
			Rep+=_Z("Longitude is not complete,");
		if(Values[8].Left(1)!=_T("-") && Values[8].Left(1)!=_T("+"))
			Rep+=_Z("Latitude should begin with \'+\' or \'-\',");
		if(Values[9].Left(1)!=_T("-") && Values[9].Left(1)!=_T("+"))
			Rep+=_Z("Longitude should begin with \'+\' or \'-\',");
		if(Rep.GetLength()==0) 
		{
			double sgn;
			if(Values[8].Left(1)==_T("-")) sgn=-1.0;
			else							sgn=1.0;
			float RLAT = (float)((atof(Values[8].Left(3))+sgn*atof(Values[8].Mid(3,2))/60.+sgn*atof(Values[8].Mid(5,5))/3600.));
			if(Values[12].Left(1)==_T("-")) sgn=-1.0;
			else							sgn=1.0;
			float RLON = (float)((atof(Values[9].Left(4))+sgn*atof(Values[9].Mid(4,2))/60.+sgn*atof(Values[9].Mid(6,5))/3600.));
			CString cty1("");
			if(RLON<-180. || RLON >180. || RLAT<-90. || RLAT>90.)
				Rep+=_Z("The specified Latitude and Longitude are not in a valid area!");

			if(Rep.GetLength()>0)
				res=false;
		}
		else
			res=false;
		if(!res)
		{
			Rep.Delete(Rep.GetLength()-1);
			AfxMessageBox(Rep);
		}
	}
	else
	{
		Values[11].TrimRight();
		Values[12].TrimRight();
		Values[11].TrimLeft();
		Values[12].TrimLeft();
		if(Values[9]==_T("Typical"))
		{
			if(atol(Values[14])==0)
				Rep+=_Z("Radius of service should be between 0 and 20000,");
		}
		if(Values[9]!=_T("Typical") || Values[17].IsEmpty())
		{
			if(Values[11].GetLength()<10)
				Rep+=_Z("Latitude is not complete,");
			if(Values[12].GetLength()<11)
				Rep+=_Z("Longitude is not complete,");
			if(Values[11].Left(1)!=_T("-") && Values[11].Left(1)!=_T("+"))
				Rep+=_Z("Latitude should begin with \'+\' or \'-\',");
			if(Values[12].Left(1)!=_T("-") && Values[12].Left(1)!=_T("+"))
				Rep+=_Z("Longitude should begin with \'+\' or \'-\',");
			if(Rep.GetLength()==0) 
			{
				double sgn;
		//		long IRGN;
				if(Values[11].Left(1)==_T("-")) sgn=-1.0;
				else							sgn=1.0;
				float RLAT = (float)((atof(Values[11].Left(3))+sgn*atof(Values[11].Mid(3,2))/60.+sgn*atof(Values[11].Mid(5,5))/3600.));
				if(Values[12].Left(1)==_T("-")) sgn=-1.0;
				else							sgn=1.0;
				float RLON = (float)((atof(Values[12].Left(4))+sgn*atof(Values[12].Mid(4,2))/60.+sgn*atof(Values[12].Mid(6,5))/3600.));
				CString cty1("");
				if(RLON<-180. || RLON >180. || RLAT<-90. || RLAT>90.)
					Rep+=_Z("The specified Latitude and Longitude are not in a valid area!");

		/*		GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
				cty1.TrimRight();
				if(cty1.IsEmpty())
					Rep+=_Z("The specified Lat and Long are not in a valid area!");
				if(cty1!=Values[13].Left(cty1.GetLength()))
					Rep+=_Z("Country should be ") + cty1 + _T(",");
				GEORGN(&RLON, &RLAT, &IRGN) ;
				if(IRGN!=atoi(Values[10]))
				{
					CString Rgn;
					Rgn.Format(_Z("Warning: Recommended ITU region is %d."),IRGN);
					Rep+=Rgn;
				}*/
				if(!Values[19].IsEmpty())
				{
					if(Values[19].Left(1)==_T("-")) sgn=-1.0;
					else							sgn=1.0;
					RLAT = (float)((atof(Values[19].Left(3))+sgn*atof(Values[19].Mid(3,2))/60.+sgn*atof(Values[19].Mid(5,5))/3600.));
				}
				if(!Values[20].IsEmpty())
				{
					if(Values[20].Left(1)==_T("-")) sgn=-1.0;
					else							sgn=1.0;
					RLON = (float)((atof(Values[20].Left(4))+sgn*atof(Values[20].Mid(4,2))/60.+sgn*atof(Values[20].Mid(6,5))/3600.));
				}
				if(RLON<-180. || RLON >180. || RLAT<-90. || RLAT>90.)
					Rep+=_Z("The specified target Latitude and Longitude are not in a valid area!");
		/*		GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
				cty1.TrimRight();
				if(cty1.IsEmpty())
					Rep+=_Z("The specified target Lat and Long are not valid!");*/
				if(Rep.GetLength()>0)
					res=false;
			}
			else
				res=false;
			if(!res)
			{
				Rep.Delete(Rep.GetLength()-1);
				AfxMessageBox(Rep);
			}
		}
	}
	return res;
}

bool CTreeviewView::BCValidation(CString Values[],CString Fields[])
{
	bool res=true;
	CString Rep;
	long UNR = 72 ;
	WDBUNIT(&UNR) ;
	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	CString SQL,Value="-1";
	RS.m_pDatabase=&DB;
	SQL.Format(_T("select StID from BCStation where SiteID='%s'"),Values[5]);
	RS.Open(CRecordset::snapshot,SQL);
	if(RS.GetRecordCount()>0)
	{
		RS.GetFieldValue((short)0,Value);
		if(atol(Value)!=atol(Values[0]))
			Rep=_Z("The ID of the station should be unique,");
	}
	RS.Close();
	CString STTP2=Fields[8].Left(2);
	STTP2.TrimRight(_T(" "));

/*	if(!STTP2.IsEmpty() && STTP2!=Values[8].Left(2))
	{
		SQL.Format(_T("Select * from equipment where bcid=%s"),Value);
		RS.Open(CRecordset::snapshot,SQL);
		if(RS.GetRecordCount()>0)
			Rep+=_Z("There are some equipments attached to this stations and the class of station is unchangeable,");
		RS.Close();
	}*/
	DB.Close();
	if((Values[8].Left(2)==_T("BT") && (Values[27]==_T("DS1") || Values[27]==_T("GS1") || Values[27]==_T("T01"))) ||
		(Values[8].Left(2)==_T("BC") && (Values[27]==_T("DT1") || Values[27]==_T("GT1") || Values[27]==_T("G02") || Values[27]==_T("T02"))))
		Rep+=_Z("Notice type is not compatible with class of station,");


	Values[11].TrimRight();
	Values[12].TrimRight();
	Values[11].TrimLeft();
	Values[12].TrimLeft();
	if(Values[11].GetLength()<10)
		Rep+=_Z("Latitude is not complete,");
	if(Values[12].GetLength()<11)
		Rep+=_Z("Longitude is not complete,");
	if(Values[11].Left(1)!=_T("-") && Values[11].Left(1)!=_T("+"))
		Rep+=_Z("Latitude should begin with \'+\' or \'-\',");
	if(Values[12].Left(1)!=_T("-") && Values[12].Left(1)!=_T("+"))
		Rep+=_Z("Longitude should begin with \'+\' or \'-\',");
	if(Rep.GetLength()==0) 
	{
		double sgn;
//		long IRGN;
		if(Values[11].Left(1)==_T("-")) sgn=-1.0;
		else							sgn=1.0;
		float RLAT = (float)((atof(Values[11].Left(3))+sgn*atof(Values[11].Mid(3,2))/60.+sgn*atof(Values[11].Mid(5,5))/3600.));
		if(Values[12].Left(1)==_T("-")) sgn=-1.0;
		else							sgn=1.0;
		float RLON = (float)((atof(Values[12].Left(4))+sgn*atof(Values[12].Mid(4,2))/60.+sgn*atof(Values[12].Mid(6,5))/3600.));
		CString cty1("");
		if(RLON<-180. || RLON >180. || RLAT<-90. || RLAT>90.)
			Rep+=_Z("The specified Lat and Long are not in a valid area!");
/*		GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
		cty1.TrimRight();
		if(cty1.IsEmpty())
			Rep+=_Z("The specified Lat and Long are not in a valid area!");
		if(cty1!=Values[13].Left(cty1.GetLength()))
			Rep+=_Z("Country should be ") + cty1 + _T(",");
		GEORGN(&RLON, &RLAT, &IRGN) ;
		if(IRGN!=atoi(Values[10]))
		{
			CString Rgn;
			Rgn.Format(_Z("Warning: Recommended ITU region is %d."),IRGN);
		}*/
		if(!Values[18].IsEmpty())
		{
			if(Values[18].Left(1)==_T("-")) sgn=-1.0;
			else							sgn=1.0;
			RLAT = (float)((atof(Values[18].Left(3))+sgn*atof(Values[18].Mid(3,2))/60.+sgn*atof(Values[18].Mid(5,5))/3600.));
		}
		if(!Values[19].IsEmpty())
		{
			if(Values[19].Left(1)==_T("-")) sgn=-1.0;
			else							sgn=1.0;
			RLON = (float)((atof(Values[19].Left(4))+sgn*atof(Values[19].Mid(4,2))/60.+sgn*atof(Values[19].Mid(6,5))/3600.));
		}
		if(RLON<-180. || RLON >180. || RLAT<-90. || RLAT>90.)
			Rep+=_Z("The specified target Lat and Long are not in a valid area!");
/*		GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
		cty1.TrimRight();
		if(cty1.IsEmpty())
			Rep+=_Z("The specified target Lat and Long are not valid!");*/
		if(Rep.GetLength()>0)
			res=false;
	}
	else
		res=false;
	if(!res)
	{
		Rep.Delete(Rep.GetLength()-1);
		AfxMessageBox(Rep);
	}
	return res;
}

bool CTreeviewView::MobileValidation(CString Values[])
{
	bool res=true;
	CString Rep;
	long UNR = 72 ;
	WDBUNIT(&UNR) ;

	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	CString SQL,Value=_T("-1");
	RS.m_pDatabase=&DB;
	SQL.Format(_T("select MobID from Mobiles where MobileID='%s'"),Values[3]);
	RS.Open(CRecordset::snapshot,SQL);
	if(RS.GetRecordCount()>0)
	{
		RS.GetFieldValue((short)0,Value);
		if(atol(Value)!=atol(Values[0]))
			Rep=_Z("The ID of the mobile should be unique,");
	}
	RS.Close();
	DB.Close();

	Values[9].TrimRight();
	Values[10].TrimRight();
	Values[9].TrimLeft();
	Values[10].TrimLeft();
	if(Values[13].IsEmpty())
	{
		if(Values[9].GetLength()<10)
			Rep+=_Z("Latitude is not complete,");
		if(Values[10].GetLength()<11)
			Rep+=_Z("Longitude is not complete,");
		if(Values[9].Left(1)!=_T("-") && Values[9].Left(1)!=_T("+"))
			Rep+=_Z("Latitude should begin with \'+\' or \'-\',");
		if(Values[10].Left(1)!=_T("-") && Values[10].Left(1)!=_T("+"))
			Rep+=_Z("Longitude should begin with \'+\' or \'-\',");
		if(Rep.GetLength()==0) 
		{
			double sgn;
	//		long IRGN;
			if(Values[9].Left(1)==_T("-")) sgn=-1.0;
			else							sgn=1.0;
			float RLAT = (float)((atof(Values[9].Left(3))+sgn*atof(Values[9].Mid(3,2))/60.+sgn*atof(Values[9].Mid(5,5))/3600.));
			if(Values[10].Left(1)==_T("-")) sgn=-1.0;
			else							sgn=1.0;
			float RLON = (float)((atof(Values[10].Left(4))+sgn*atof(Values[10].Mid(4,2))/60.+sgn*atof(Values[10].Mid(6,5))/3600.));
			CString cty1("");

			if(RLON<-180. || RLON >180. || RLAT<-90. || RLAT>90.)
				Rep+=_Z("The specified Latitude and Longitude are not in a valid area!");
	/*		GEOPLC(&RLON, &RLAT, (BYTE*)cty1.GetBufferSetLength(3)) ;
			cty1.TrimRight();
			if(cty1.IsEmpty())
				Rep+=_Z("The specified Lat and Long are not in a valid area!");
			if(cty1!=Values[11].Left(cty1.GetLength()))
				Rep+=_Z("Country should be ") + cty1 + _T(",");
			GEORGN(&RLON, &RLAT, &IRGN) ;
			if(IRGN!=atoi(Values[8]))
			{
				CString Rgn;
				Rgn.Format(_Z("Warning: Recommended ITU region is %d."),IRGN);
			}*/
			if(Rep.GetLength()>0)
				res=false;
		}
		else
			res=false;
	}
	if(!res)
	{
		Rep.Delete(Rep.GetLength()-1);
		AfxMessageBox(Rep);
	}
	return res;
}

bool CTreeviewView::ESValidation(CString Values[])
{
	bool res=true;
	CString Rep;

	Values[10].TrimRight();
	Values[11].TrimRight();
	Values[10].TrimLeft();
	Values[11].TrimLeft();
	if(Values[11].GetLength()<10)
		Rep+=_Z("Latitude is not complete,");
	if(Values[10].GetLength()<11)
		Rep+=_Z("Longitude is not complete,");
	if(Values[11].Left(1)!=_T("-") && Values[11].Left(1)!=_T("+"))
		Rep+=_Z("Latitude should begin with \'+\' or \'-\',");
	if(Values[10].Left(1)!=_T("-") && Values[10].Left(1)!=_T("+"))
		Rep+=_Z("Longitude should begin with \'+\' or \'-\',");
	if(Rep.GetLength()==0) 
	{
		double sgn;
//		long IRGN;
		if(Values[11].Left(1)==_T("-")) sgn=-1.0;
		else							sgn=1.0;
		float RLAT = (float)((atof(Values[11].Left(3))+sgn*atof(Values[11].Mid(3,2))/60.+sgn*atof(Values[11].Mid(5,5))/3600.));
		if(Values[10].Left(1)==_T("-")) sgn=-1.0;
		else							sgn=1.0;
		float RLON = (float)((atof(Values[10].Left(4))+sgn*atof(Values[10].Mid(4,2))/60.+sgn*atof(Values[10].Mid(6,5))/3600.));
		CString cty1("");
		if(RLON<-180. || RLON >180. || RLAT<-90. || RLAT>90.)
			Rep+=_Z("The specified Latitude and Longitude are not in a valid area!");

		if(Rep.GetLength()>0)
			res=false;
	}
	else
		res=false;
	if(!res)
	{
		Rep.Delete(Rep.GetLength()-1);
		AfxMessageBox(Rep);
	}
	return res;
}

bool CTreeviewView::EquipmentValidation(CString Values[], CString StClass)
{
	CDatabase DB;
//	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	CString SQL,Rep="",Value;
	CString Part;
//	RS.m_pDatabase=&DB;
//	SQL.Format(_T("select eqcatID from eqcat where eqname='%s'"),Values[1]);
//	RS.Open(CRecordset::snapshot,SQL);
//	if(RS.GetRecordCount()>0)
//	{
//		RS.GetFieldValue((short)0,Value);
//		if(atol(Value)!=atol(Values[0]))
//			Rep=_Z("The name of the equipment should be unique!");
//	}
//	RS.Close();
//	DB.Close();
	if(StClass==_T("BT"))
	{
		if(Values[13].IsEmpty() && Values[14].IsEmpty())
		{
			Part.Format(_Z("At least one of '%s' or '%s' should have a value according to the polarization of the antenna(s),"),
				m_Grid->GetTextMatrix(16,0),m_Grid->GetTextMatrix(17,0));
			Rep+=Part;
		}
		else
		{
			if(!Values[13].IsEmpty())
				if(atof(Values[13])<0. || atof(Values[13])>70.)
				{
					Part.Format(_Z("%s should be between 0-70 dBW,"),m_Grid->GetTextMatrix(16,0));
					Rep+=Part;
				}
			if(!Values[14].IsEmpty())
				if(atof(Values[14])<0. || atof(Values[14])>70.)
				{
					Part.Format(_Z("%s should be between 0-70 dBW,"),m_Grid->GetTextMatrix(17,0));
					Rep+=Part;
				}
		}
/*		if(Values[7].IsEmpty() && Values[8].IsEmpty())
		{
			Part.Format(_Z("%s is missing,"),m_Grid->GetTextMatrix(10,0));
			Rep+=Part;
		}
		if(Values[9].IsEmpty() && Values[10].IsEmpty())
		{
			Part.Format(_Z("%s is missing,"),m_Grid->GetTextMatrix(12,0));
			Rep+=Part;
		}
		DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
		CRecordset RS;
		RS.m_pDatabase=&DB;
		Value=Values[11].Left(2);
		Value.TrimRight();
		if(Value.Left(1)!=_T("T"))
		{
			SQL.Format(_T("select count(ColCode) from ColorSys where ColCode='%s' and ColName='%s'"),Value,Values[12]);
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,Value);
			if(Value==_T("0"))
			{
				Rep+=_Z("The combination of TV and Color systems is not valid,");
			}
			RS.Close();
		}
		DB.Close();*/
	}
	if(StClass==_T("BC"))
	{
		if(Values[8].IsEmpty() && Values[9].IsEmpty())
		{
			CString Part;
			Part.Format(_Z("At least one of '%s' or '%s' should have a value according to the polarization of the antenna(s),"),
				m_Grid->GetTextMatrix(11,0),m_Grid->GetTextMatrix(12,0));
			Rep+=Part;
		}
	}
	if(Rep.GetLength())
	{
		Rep.Delete(Rep.GetLength()-1);
		AfxMessageBox(Rep);
		return false;
	}
	return true;
}

bool CTreeviewView::AntennaValidation(CString Values[],CString StClass)
{
	CDatabase DB;
//	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	int place1=0, place2=0;
	CString SQL,Rep,Value;
//	RS.m_pDatabase=&DB;
//	if(StClass!=_T("FX"))
//		SQL.Format(_T("select AntCatID from antcat where antname='%s'"),Values[7]);
//	else
//		SQL.Format(_T("select AntCatID from antcat where antname='%s'"),Values[8]);
//	RS.Open(CRecordset::snapshot,SQL);
//	if(RS.GetRecordCount()>0)
//	{
//		RS.GetFieldValue((short)0,Value);
//		if(atol(Value)!=atol(Values[0]))
//			Rep=_T("The name of the antenna should be unique!");
//	}
//	RS.Close();
//	DB.Close();
	if(atof(Values[4])>=360. || atof(Values[4])<0.)
		Rep+=_Z("Azimuth should be between 0 and 360,");
	if(StClass==_T("FX")) place1=place2=1;
	if(StClass==_T("__")) place2=-1;
	if(atof(Values[5+place1])>90. || atof(Values[5+place1])<-90.)
			Rep+=_Z("Elevation should be between -90 and 90,");
	if(Values[13+place2].Left(1)==_T("N"))
	{
		if(atof(Values[14+place2])<360)
			Rep+=_Z("Horizontal beam width for nondiectional antenna should be 360 degrees,");
	}
	if(Values[13+place2].Left(1)==_T("D"))
	{
		if(atof(Values[14+place2])==360)
			Rep+=_Z("Horizontal beam width for diectional antenna should not be 360 degrees,");
	}
	
	if(Rep.GetLength())
	{
		AfxMessageBox(Rep);
		return false;
	}
	return true;
}

bool CTreeviewView::FrequencyValidation(CString Values[], CString StClass)
{
	bool res=true;
	CString Rep, Cls;

	if(StClass==_T("__"))
	{
		Cls=Values[5];
		if(atof(Values[6])<0.000001 || atof(Values[6])>1999999999.)
			Rep+=_Z("Bandwidth should be between 0 and 2 GHz,");
	}
	else
	if(StClass==_T("FX") || StClass==_T("ML") || StClass==_T("FB"))
	{
		Cls=Values[5];
		if(Values[12]>=Values[13] || Values[12]>_T("24:00") || Values[13]>_T("24:00") ||
			Values[12].Right(2)>_T("59") || Values[13].Right(2)>_T("59"))
			Rep+=_Z("Operating hours are not OK,");
		//if(!Values[10].IsEmpty() && (Values[10]<Values[13] || Values[10]<Values[14] || Values[10]>_T("24:00") || Values[10].Right(2)>_T("59")))
		//	Rep+=_Z("Peak hour is not OK,");
		if(atof(Values[6])<0.000001 || atof(Values[6])>1999999999.)
			Rep+=_Z("Bandwidth should be between 0 and 2 GHz,");
		if(atof(Values[8])<0 || atof(Values[8])>1440)
			Rep+=_Z("Traffic should be between 0 and 1440,");
	}
	else
		if(StClass==_T("BT"))
		{
			Cls=Values[4];
			if(Values[12]>=Values[13] || Values[12]>_T("24:00") || Values[13]>_T("24:00") ||
				Values[12].Right(2)>_T("59") || Values[13].Right(2)>_T("59"))
				Rep+=_Z("Operating hours are not OK,");
			//if(!Values[10].IsEmpty() && (Values[10]<Values[13] || Values[10]<Values[14] || Values[10]>_T("24:00") || Values[10].Right(2)>_T("59")))
			//	Rep+=_Z("Peak hour is not OK,");
			if(atof(Values[5])<0.000001 || atof(Values[5])>1999999999.)
			{
				Rep+=_Z("Bandwidth should be between 0 and 2 GHz,");
			}
			if(!Values[16].IsEmpty() && Values[16]!=_T("N") && Values[16]!=_T("S"))
				Rep+=_Z("Spectrum Mask is not correct,");
			if(atof(Values[8])<0 || atof(Values[8])>1440)
				Rep+=_Z("Traffic should be between 0 and 1440,");
			CDatabase DB;
			CRecordset RS;
			CString SQL,TV;
			DB.Open(m_CDBSTR,false,false,_T("ODBC;"), false);
			RS.m_pDatabase=&DB;
			SQL.Format(_T("select TVSys from eqcat,equipment,frequency where eqcat.eqcatid=equipment.EqCatID and equipment.eqid=%s"),Values[0]);
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,TV);
			if(!TV.IsEmpty())
			{
				if(TV.Left(1)!=_T("T"))
				{
					if(Values[2].IsEmpty())
						Rep+=_Z("Vision carrier frequency is required,");
					if(Values[3].IsEmpty())
						Rep+=_Z("Sound carrier frequency is required,");
				}
			}
			else
			{
				if(Values[2].IsEmpty())
					Rep+=_Z("Vision carrier frequency is required,");
				if(Values[3].IsEmpty())
					Rep+=_Z("Sound carrier frequency is required,");
			}
			RS.Close();
			DB.Close();
		}
		else if(StClass==_T("BC"))
		{
			Cls=Values[2];
			if(Values[9]>=Values[10] || Values[9]>_T("24:00") || Values[10]>_T("24:00") ||
				Values[9].Right(2)>_T("59") || Values[10].Right(2)>_T("59"))
				Rep+=_Z("Operating hours are not OK,");
			//if(!Values[7].IsEmpty() && (Values[7]<Values[10] || Values[7]<Values[11] || Values[7]>_T("24:00") || Values[7].Right(2)>_T("59")))
			//	Rep+=_T("Peak hour is not OK,");
			if(atof(Values[3])<0.000001 || atof(Values[3])>1999999999.)
			{
				Rep+=_Z("Bandwidth should be between 0 and 2 GHz,");
			}
			if(atof(Values[5])<0 || atof(Values[5])>1440)
				Rep+=_Z("Traffic should be between 0 and 1440,");
			if(!Values[13].IsEmpty() && Values[13]!=_T("1") && Values[13]!=_T("2") && Values[13]!=_T("3"))
				Rep+=_Z("Spectrum Mask is not correct,");
		}

	Cls.TrimRight();
	if(Cls.GetLength()==3)
		Cls+=_T("--");
	if(Cls.GetLength()==4)
		Cls+=_T("-");
	if( Cls.Left(1).FindOneOf(_T("ABCDFGHJKLMNPQRVWX"))==-1 ||
		Cls.Mid(1,1).FindOneOf(_T("0123789X"))==-1 ||
		Cls.Mid(2,1).FindOneOf(_T("ABCDEFNWX"))==-1 ||
		Cls.Mid(3,1).FindOneOf(_T("ABCDEFGHJKLMNWX-"))==-1 ||
		Cls.Mid(4,1).FindOneOf(_T("CFNTWX-"))==-1)
			res=false;
	if(res==false)
		Rep+=_Z("The class of emission is not OK,");
	double freq=0;
	if(Values[1].GetLength()>10)
		Rep+=_Z("Too many digits for frequency,");
	else
		freq=atof((LPCTSTR)Values[1])*GetFreqUnit(m_Grid->GetTextMatrix(1,2));
	if(freq>3000000000000 || freq<3000)
		Rep+=_Z("Assigned frequency is not in range,");
	if(StClass==_T("__") || StClass==_T("FX") || StClass==_T("FB") || StClass==_T("ML"))
	{
		double f=freq;
		freq=0;
		if(Values[2].GetLength()>10)
			Rep+=_Z("Too many digits for frequency,");
		else
			freq=atof((LPCTSTR)Values[2])*GetFreqUnit(m_Grid->GetTextMatrix(2,2));
//		if(freq==0) freq=f;
		if(freq>3000000000000 || freq<3000)
			Rep+=_Z("Response frequency is not in range,");
		freq=0;
		if(Values[1].GetLength()>10)
			Rep+=_Z("Too many digits for frequency,");
		else
			freq=atof((LPCTSTR)Values[3])*GetFreqUnit(m_Grid->GetTextMatrix(3,2));
		if(freq>3000000000000)
			Rep+=_Z("Reference frequency is not in range,");
	}
	if(!Rep.IsEmpty())
	{
		Rep.Delete(Rep.GetLength()-1);
		AfxMessageBox(Rep);
		return false;
	}
	return true;
}

void CTreeviewView::AntAssign()
{
	CString AntFile,AntName,AntGain,AntPat,AntPol,AntBeamWH,AntBeamWV;
	double FreqFrom,FreqTo;
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _Z("Antenna Files (*.ant)|*.ant"), NULL );
	FileDlg.DoModal();
	AntFile=FileDlg.GetPathName();
	if(!AntFile.IsEmpty())
	{
		FILE *fp=fopen(AntFile,"rt");
		if(fp!=NULL)
		{
			double AttnH[360],AttnV[360];
			char buf[150];
			int i;
			CString Sbuf;
			fgets(buf,100,fp);
			Sbuf=buf;
			Sbuf=Sbuf.Left(Sbuf.GetLength()-1);
			AntName=Sbuf.Mid(5);
			AntName.TrimRight();
			fgets(buf,100,fp);
			Sbuf=buf;
			Sbuf=Sbuf.Left(Sbuf.GetLength()-2);
			AntGain=Sbuf.Mid(9);
			fgets(buf,100,fp);
			Sbuf=buf;
			Sbuf=Sbuf.Left(Sbuf.GetLength()-2);
			AntBeamWH=Sbuf.Mid(12);
			fgets(buf,100,fp);
			Sbuf=buf;
			Sbuf=Sbuf.Left(Sbuf.GetLength()-2);
			AntBeamWV=Sbuf.Mid(12);
			fgets(buf,100,fp);
			Sbuf=buf;
			Sbuf=Sbuf.Left(Sbuf.GetLength()-2);
			FreqFrom=atof(Sbuf.Mid(7));
			fgets(buf,100,fp);
			Sbuf=buf;
			Sbuf=Sbuf.Left(Sbuf.GetLength()-2);
			FreqTo=atof(Sbuf.Mid(7));
			fgets(buf,100,fp);
			Sbuf=buf;
			double coef;
			if(Sbuf.Mid(9,3)=="GHz") coef=1000.;
			else if(Sbuf.Mid(9,3)=="MHz") coef=1.;
			else if(Sbuf.Mid(9,3)=="kHz") coef=0.001;
			else coef=0.000001;
			FreqFrom*=coef;
			FreqTo*=coef;
			fgets(buf,100,fp);
			Sbuf=buf;
			AntPol=Sbuf.Mid(13);
			AntPol.Delete(AntPol.GetLength()-1);
			AntPol.TrimRight();
			AntPat=FileDlg.GetPathName();
			
			CDatabase DB;
			CRecordset RS;
			CString NewID;
			RS.m_pDatabase=&DB;
			DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
			CString SQL;
			SQL=_T("select max(antcatid)+1 from antcat");
			RS.Open(CRecordset::snapshot,SQL);
			RS.GetFieldValue((short)0,NewID);
			RS.Close();
			if(NewID.IsEmpty()) NewID=_T("1");
			SQL.Format(_T("select %s,'%s','C','%s',%s,'I','%s',%s,%s,%lf,%lf,1 "),NewID,AntName,AntPol,AntGain,
				(atof(AntBeamWH)>359?_T("N"):_T("D")),AntBeamWH,AntBeamWV,FreqFrom,FreqTo);
			SQL=_T("insert into antcat (AntCatID,AntName,ClassOfAnt,Pol,Gain,GainType,AntDir,BeamWidthH,BeamWidthV,FreqFrom,FreqTo,Lib) ")+SQL;
			DB.ExecuteSQL(SQL);
			fgets(buf,100,fp);
			double Patt[2][360]={0.0},Patt2[2][360]={0.0};
			for(i=0;i<360 && !feof(fp);i++)
			{
				int j,k;
				fgets(buf,100,fp);
				Sbuf=buf;
				j=3;
				while(buf[j]==' ') j++;
				k=j;
				while(buf[j]!=' ') j++;
				AttnH[i]=atof(Sbuf.Mid(k,j-k));
				while(buf[j]==' ') j++;
				k=j;
				Patt[1][i]=AttnV[i]=atof(Sbuf.Mid(k,Sbuf.GetLength()-k));
				//AttnH[i]=atof(Sbuf.Mid(4,5));
				//Patt[1][i]=AttnV[i]=atof(Sbuf.Mid(10,5));;
				Patt[0][i]=i;
			}
			fclose(fp);
	
			i=0;
			while(Patt[0][i]<90 && i<360)
				i++;
			if(i==360) i=0;
			for(int j=i;j<360;j++)
				Patt[0][j]+=-90;
			for(j=0;j<i;j++)
				Patt[0][j]+=360-90;

			for(j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[0][j]]=Patt[1][j];
			}

			CRecordset AntPatt;
			AntPatt.m_pDatabase=&DB;
			SQL.Format("select * from AntDiag where AntID=%s",NewID);
			AntPatt.Open(CRecordset::dynaset,SQL);
			if(AntPatt.GetRecordCount()>0)
			{
				SQL.Format("Delete * from AntDiag where AntID=%s",NewID);
				AntPatt.m_pDatabase->ExecuteSQL(SQL);
				AntPatt.Requery();
			}
			for(i=0;i<360;i++)
			{
				SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, '%s', %lf"),
					NewID, (double)i, AntPol!=_T("V")?_T("H"):_T("V"), AttnH[i]);
				AntPatt.m_pDatabase->ExecuteSQL(SQL);
			}
			for(i=0;i<360;i++)
			{
				SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %s, %lf, '%s', %lf"),
					NewID, (double)i, AntPol!=_T("V")?_T("V"):_T("H"), Patt2[1][359-i]);
				AntPatt.m_pDatabase->ExecuteSQL(SQL);
			}
			AntPatt.Close();
			DB.Close();
			AddTrail(_Z("Assign Antenna"),atol(NewID),"AntDiag");
		}
	}

}

/*void CTreeviewView::DeletePayment()
{
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long LicID=m_Grid->GetRowData(m_Grid->GetRowSel());
	CString BillNo,Table;
	if(m_Grid->GetRowSel()>0)
	{
		BillNo=m_Grid->GetTextMatrix(m_Grid->GetRowSel(),1);
		if(atol(m_Grid->GetTextMatrix(m_Grid->GetRowSel(),4))==0)
		{
			OnPrintReceipt(LicID,BillNo);
		}
		else
		{
			OnPrintInvoice(LicID,BillNo);
		}
	}
	else
		AfxMessageBox(_Z("No row is selected!"));
}*/

void CTreeviewView::PrintBill()
{
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long LicID=m_Grid->GetRowData(m_Grid->GetRowSel());
	CString BillNo,Table;
	if(m_Grid->GetRowSel()>0)
	{
		BillNo=m_Grid->GetTextMatrix(m_Grid->GetRowSel(),1);
		if(atol(m_Grid->GetTextMatrix(m_Grid->GetRowSel(),4))==0 && atol(m_Grid->GetTextMatrix(m_Grid->GetRowSel(),5))!=0)
		{
			OnPrintReceipt(LicID,BillNo);
		}
		else
		{
			OnPrintInvoice(LicID,BillNo);
		}
	}
	else
		AfxMessageBox(_Z("No row is selected!"));
}

void CTreeviewView::OnPrintInvoice(long LicID, CString InvNo) 
{
	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset Header,Stations;
	Header.m_pDatabase=&DB;
	Stations.m_pDatabase=&DB;
	FILE *source, *dest;
	CString RepPath=GetReportPath(), 
		SFile=RepPath+_T("Invoice.htm"), 
		SQL;
		InvNo.TrimLeft();
		InvNo.TrimRight();
//	char temp[300];

	SQL.Format(_T("Debit,Credit,Credit-Debit as TotPay,Months, Description from Invoiceperiod,invoice, license, owner where invoice.InvoiceNo='%s' and "),InvNo);
	SQL=_T("select LicNo,BillName,BillAddress,InvoiceNo,format(InvDate,'yyyy/MM/dd') as InvDt, format(DueDate,'yyyy/MM/dd') as DueDt,")+SQL;
	SQL+=_T(" owner.id=license.admid and license.licid=invoice.licid and invoiceperiod.invperioden=license.invperiod");
	
	Header.Open(CRecordset::snapshot, SQL);

	if(source=fopen(SFile,"rt"))
	{
		CString FName;
		FName.Format(_T("Inv%s.htm"),InvNo);
		RepPath=GetCommandLine();
		int Place=RepPath.ReverseFind('\\')-1;
		RepPath.Delete(0);
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		Place=RepPath.ReverseFind('\\')+1;
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		RepPath+="reports\\";

		FName=RepPath+FName;
		dest=fopen(FName,"wt");
		while(!feof(source))
		{
			int ch;
			ch=fgetc(source);
			if(feof(source)) break;
			if(ch=='{')
			{
				CString FieldName, FValue;
				CString RowBuf, ResStr;
				while(!feof(source))
				{
					ch=fgetc(source);
					if(ch=='}') break;
					FieldName+=ch;
				}//end while
				if(FieldName.IsEmpty())
					fputs(FValue,dest);
				else if(FieldName.GetAt(0)=='\\')
				{
					CString SQL2;
					SQL2=_T("select SiteName,Format([GeoLat],'#.######') as Lat,Format([GeoLon],'#.######') as Lon,Country,RadPwr,Frequency,FreqFee,ClassStation from station,equipment,frequency ");
					SQL.Format(_T("where licid=%ld and station.stid=equipment.stid and equipment.eqid=frequency.eqid union all "),LicID);
					SQL2+=SQL;
					SQL2+=_T("select SiteName,Format([GeoLat],'#.######') as Lat,Format([GeoLon],'#.######') as Lon,Country,RadPwr,Frequency,FreqFee,ClassStation from bcstation,equipment,frequency ");
					SQL.Format(_T("where licid=%ld and bcstation.stid=equipment.bcid and equipment.eqid=frequency.eqid union all "),LicID);
					SQL2+=SQL;
					SQL2+=_T("select Mobname as SiteName,Format([GeoLat],'#.######') as Lat,Format([GeoLon],'#.######') as Lon,Country,RadPwr,Frequency,FreqFee,ClassStation from mobiles,equipment,frequency ");
					SQL.Format(_T("where licid=%ld and mobiles.mobid=equipment.mobid and equipment.eqid=frequency.eqid  union all "),LicID);
					SQL2+=SQL;
					SQL2+=_T("select stn_name as SiteName, Format([lat_dec],'#.######') as Lat,Format([long_dec],'#.######') as Lon,ctry as Country,'---' as RadPwr,freq_mhz*1000000 as Frequency, FreqFee,'---' as ClassStation from e_stn,e_ant,grp,assgn ");
					SQL.Format(_T("where licid=%ld and e_stn.ntc_id=e_ant.ntc_id and e_ant.ntc_id=grp.ntc_id and e_ant.emi_rcp=grp.emi_rcp and e_ant.beam_name=grp.beam_name and grp.grp_id=assgn.grp_id"),LicID);
					SQL2+=SQL;
					Stations.Open(CRecordset::snapshot,SQL2);
					while(!feof(source))
					{
						ch=fgetc(source);
						if(ch=='<') 
						{
							ch=fgetc(source);
							FieldName=ch;
							ch=fgetc(source);
							FieldName+=ch;
							if(FieldName=="tr")
							{
								ch=fgetc(source);
								while(!feof(source))
								{
									ch=fgetc(source);
									if(ch=='<') 
									{
										ch=fgetc(source);
										FieldName=ch;
										ch=fgetc(source);
										FieldName+=ch;
										ch=fgetc(source);
										FieldName+=ch;
										if(FieldName=="/tr")
										{
											ch=fgetc(source);
											while(!Stations.IsEOF())
											{
												ProcessBuf(Stations, RowBuf, ResStr);
												ResStr="<tr>"+ResStr;
												ResStr+="</tr>";
												fputs(ResStr,dest);
												Stations.MoveNext();
											}
											break;
										}
										else
											RowBuf+="<"+FieldName;
									}
									else
										RowBuf+=ch;
								}
								break;
							}
							else
							{
								FieldName="<"+FieldName;
								fputs(FieldName,dest);
							}
						}
						else
						{
							FieldName=ch;
							fputs(FieldName,dest);
						}
					}//end while
					Stations.Close();
				}
				else if(IsFieldValid(FieldName,Header))
				{
					if(FieldName=="Today")
					{
						CTime tm = CTime::GetCurrentTime();
						FValue=tm.Format("%Y/%m/%d");
					}
					else
						Header.GetFieldValue(FieldName,FValue);
					if(FieldName=="Frequency")
					{
						double Freq=atof(FValue);
						FValue.Format("%f",Freq/1000000.);
					}
				}
				else
				{
					FValue=_T("{") + FieldName + _T("}");
				}
				fputs(FValue,dest);
			}//end if
			else
				fputc(ch,dest);
		}//end while
		Header.Close();
		fclose(dest);
		fclose(source);
		ShellExecute(this->m_hWnd,"open",FName,NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		AfxMessageBox(_Z("Invoice template not found!"));
	}
	
}

bool CTreeviewView::IsFieldValid(CString FieldName, CRecordset &ODBCRecs)
{
	for (int FldNo=0;FldNo<ODBCRecs.GetODBCFieldCount();FldNo++)
	{
		CODBCFieldInfo FldInfo;
		ODBCRecs.GetODBCFieldInfo(FldNo,FldInfo);
		if(!FieldName.CompareNoCase(FldInfo.m_strName))
			return true;
	}
	if(FieldName=="Today") return true;
	return false;
}

void CTreeviewView::ProcessBuf(CRecordset &Stations, CString RowBuf, CString &ResStr)
{
	int index=0, place;
	CString FValue;
	ResStr="";
	while(index<RowBuf.GetLength())
	{
		place=RowBuf.Find("{",index);
		if(place==-1) break;
		ResStr+=RowBuf.Mid(index, place-index);
		index=place+1;
		place=RowBuf.Find("}",index);
		if(IsFieldValid(RowBuf.Mid(index,place-index),Stations))
		{
			Stations.GetFieldValue(RowBuf.Mid(index,place-index),FValue);
			if(RowBuf.Mid(index,place-index)=="Frequency")
			{
				double Freq=atof(FValue);
				FValue.Format("%f",Freq/1000000.);
			}
		}
		else
			FValue=RowBuf.Mid(index-1,place-index+2);
		index=place+1;
		ResStr+=FValue;
	}
}

CString CTreeviewView::GetReportPath()
{
	CString Path;
	Path=GetCommandLine();
	int Place=Path.ReverseFind('\\')-1;
	Path.Delete(0);
	Path.Delete(Place,Path.GetLength()-Place);
	Place=Path.ReverseFind('\\')+1;
	Path.Delete(Place,Path.GetLength()-Place);
	Path+="texts\\";
	return Path;
}

void CTreeviewView::OnPrintReceipt(long LicID, CString PayNo) 
{
	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset Header,Stations;
	Header.m_pDatabase=&DB;
	Stations.m_pDatabase=&DB;
	FILE *source, *dest;
	CString RepPath=GetReportPath(), 
		SFile=RepPath+"Receipt.htm", 
		SQL;
	PayNo.TrimLeft();
	PayNo.TrimRight();

	SQL.Format(_T(" from license, payment, owner where Payment.PaymentNo='%s' and "),PayNo);
	SQL=_T("select LicNo,BillName,BillAddress,PaymentNo,format(PayDate,'yyyy/MM/dd') as PayDt, Amount, Description ")+SQL;
	SQL+=_T(" owner.id=license.admid and license.licid=payment.licid");
	
	Header.Open(CRecordset::snapshot, SQL);

	if(source=fopen(SFile,"rt"))
	{
		CString FName;
		FName.Format(_T("Rec%s.htm"),PayNo);
		RepPath=GetCommandLine();
		int Place=RepPath.ReverseFind('\\')-1;
		RepPath.Delete(0);
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		Place=RepPath.ReverseFind('\\')+1;
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		RepPath+="reports\\";

		FName=RepPath+FName;
		dest=fopen(FName,"wt");
		while(!feof(source))
		{
			int ch;
			ch=fgetc(source);
			if(feof(source)) break;
			if(ch=='{')
			{
				CString FieldName, FValue;
				CString RowBuf, ResStr;
				while(!feof(source))
				{
					ch=fgetc(source);
					if(ch=='}') break;
					FieldName+=ch;
				}//end while
				if(FieldName.IsEmpty())
					fputs(FValue,dest);
				else if(FieldName.GetAt(0)=='\\')
				{
					CString SQL2;
					SQL2=_T("select SiteName,GeoLat,GeoLon,Country,RadPwr,Frequency,FreqFee,ClassStation from station,equipment,frequency ");
					SQL.Format(_T("where licid=%ld and station.stid=equipment.stid and equipment.eqid=frequency.eqid union all "),LicID);
					SQL2+=SQL;
					SQL2+=_T("select SiteName,GeoLat,GeoLon,Country,RadPwr,Frequency,FreqFee,ClassStation from bcstation,equipment,frequency ");
					SQL.Format(_T("where licid=%ld and bcstation.stid=equipment.bcid and equipment.eqid=frequency.eqid union all "),LicID);
					SQL2+=SQL;
					SQL2+=_T("select Mobname as SiteName,GeoLat,GeoLon,Country,RadPwr,Frequency,FreqFee,ClassStation from mobiles,equipment,frequency ");
					SQL.Format(_T("where licid=%ld and mobiles.mobid=equipment.mobid and equipment.eqid=frequency.eqid "),LicID);
					SQL2+=SQL;
					Stations.Open(CRecordset::snapshot,SQL2);
					while(!feof(source))
					{
						ch=fgetc(source);
						if(ch=='<') 
						{
							ch=fgetc(source);
							FieldName=ch;
							ch=fgetc(source);
							FieldName+=ch;
							if(FieldName=="tr")
							{
								ch=fgetc(source);
								while(!feof(source))
								{
									ch=fgetc(source);
									if(ch=='<') 
									{
										ch=fgetc(source);
										FieldName=ch;
										ch=fgetc(source);
										FieldName+=ch;
										ch=fgetc(source);
										FieldName+=ch;
										if(FieldName=="/tr")
										{
											ch=fgetc(source);
											while(!Stations.IsEOF())
											{
												ProcessBuf(Stations, RowBuf, ResStr);
												ResStr="<tr>"+ResStr;
												ResStr+="</tr>";
												fputs(ResStr,dest);
												Stations.MoveNext();
											}
											break;
										}
										else
											RowBuf+="<"+FieldName;
									}
									else
										RowBuf+=ch;
								}
								break;
							}
							else
							{
								FieldName="<"+FieldName;
								fputs(FieldName,dest);
							}
						}
						else
						{
							FieldName=ch;
							fputs(FieldName,dest);
						}
					}//end while
					Stations.Close();
				}
				else if(IsFieldValid(FieldName,Header))
				{
					if(FieldName=="Today")
					{
						CTime tm = CTime::GetCurrentTime();
						FValue=tm.Format("%Y/%m/%d");
					}
					else
						Header.GetFieldValue(FieldName,FValue);
					if(FieldName=="Frequency")
					{
						double Freq=atof(FValue);
						FValue.Format("%f",Freq/1000000.);
					}
				}
				else
				{
					FValue=_T("{") + FieldName + _T("}");
				}
				fputs(FValue,dest);
			}//end if
			else
				fputc(ch,dest);
		}//end while
		Header.Close();
		fclose(dest);
		fclose(source);
		ShellExecute(this->m_hWnd,"open",FName,NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		AfxMessageBox(_Z("Receipt template not found!"));
	}	
}

void CTreeviewView::LoadUnpaid()
{
/*	CString SQL1,SQL2;
	CDatabase	DB;
	CRecordset	RS;
	long Balance=0;
	m_Grid->SetCols(0,7);
	m_Grid->SetRows(1);
	m_Grid->SetTextMatrix(0,1,_Z("BillName"));
	m_Grid->SetTextMatrix(0,2,_Z("License no."));
	m_Grid->SetTextMatrix(0,3,_Z("Invoice no."));
	m_Grid->SetTextMatrix(0,4,_Z("Invoice date"));
	m_Grid->SetTextMatrix(0,5,_Z("Due date"));
	m_Grid->SetTextMatrix(0,6,_Z("Amount"));
	DB.Open(((CSMS4DCApp *)AfxGetApp())->m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	SQL1.Format(_T("select invoiceno from invoice,(select max(duedate) as duedt, licid from invoice where licid in (select licid from license where archive=no) group by licid) as qry where invoice.licid=qry.licid and invoice.duedate=qry.duedt "));
	
	SQL1.Format(_T("Select BillName, LicNo, InvoiceNo, format(InvDate,'yyyy/mm/dd') as invdt, format(DueDate,'yyyy/mm/dd') as duedt, Description, (Credit-Debit) as Amount from Invoice,license,owner where owner.id=license.admid and license.licid=invoice.licid and LicID=%ld"), ID);
*/
}

void CTreeviewView::AddTrail(CString Action, long RecordID, CString Table)
{
	//CRecordset m_rs;
	//CDBVariant TempVar;
	CDatabase DB;
	CString UserName=/*((CSMS4DCApp *)AfxGetApp())->*/m_UserName;
	CTime Date=CTime::GetCurrentTime();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CString temp,
		m_Tbl="INSERT INTO Audit ( UserName, [DateTime], [Action], Record, [Table] ) SELECT \'";
	m_Tbl+= UserName +"\' as Expr1, \'";
	m_Tbl+= Date.Format("%c") + "\' AS Expr2, \'";
	m_Tbl+= Action + "\' AS Expr3, ";
	temp.Format("%ld",RecordID);
	m_Tbl+= temp + " AS Expr4, \'";
	m_Tbl+= Table + "\' AS Expr5";
	//m_rs.m_pDatabase=pDB;
	DB.ExecuteSQL(m_Tbl);
	DB.Close();
	//m_rs.Open( CRecordset::dynaset, m_Tbl);
}

long CTreeviewView::GetBalance(long LicID,bool *Payment)
{
	CString SQL1,SQL2;
	CDatabase	DB;
	CRecordset	RS;
	long Balance=0;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	SQL1.Format(_T("Select InvoiceNo, format(InvDate,'yyyy/mm/dd hh:MM:ss') as dt, Description, Debit, Credit, Replaced from Invoice where LicID=%ld"), LicID);
	SQL2.Format(_T("Select PaymentNo, format(PayDate,'yyyy/mm/dd hh:MM:ss') as dt, Description, 0, Amount, '---' from Payment where LicID=%ld"), LicID);
	SQL1=SQL1 + _T(" union all ") + SQL2;
	SQL2=_T("select * from (") + SQL1 + _T(") order by dt");
	RS.Open(CRecordset::dynaset,SQL2);
	if(RS.GetRecordCount()==0)
		*Payment=false;
	else
		*Payment=true;
	for(int k=0;!RS.IsEOF();k++)
	{
		CString Value,Debit,Credit;
		RS.GetFieldValue(5,Value);
		RS.GetFieldValue(3,Debit);
//		m_Grid->SetTextMatrix(k+1,4,Debit);
		RS.GetFieldValue(4,Credit);
//		m_Grid->SetTextMatrix(k+1,5,Credit);
		if( Value!="---")
			Balance=atol(Credit)-atol(Debit);
		else
			Balance+=atol(Credit)-atol(Debit);
		RS.MoveNext();
	}
	RS.Close();
	DB.Close();
	return Balance;
}

void CTreeviewView::AddAllotment()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from rrc_allotment where terrakey=-1"));
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("GE06 Allotment information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	m_Grid->SetRows(RS.GetODBCFieldCount()-2);
	CODBCFieldInfo FldInfo;
/*	RS.GetODBCFieldInfo((short)0,FldInfo);
	FName=GetFieldName(&DB, _T("Notice"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
	m_Grid->SetTextMatrix(1,0,FName);
	RS.GetFieldValue((short)0,Value);
	m_Grid->SetTextMatrix(1,1,Value);
	m_Grid->SetRowData(1,1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);*/
	for(int i=1,j=0;i<RS.GetODBCFieldCount();i++,j++)
	{
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("rrc_allotment"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(j==11)
			m_Grid->SetRowData(j+1,1);
		if(j==1 || j==10)
			m_Grid->SetRowData(j+1,2);
		if(j==12)
			m_Grid->SetRowData(j+1,3);
		if(j==5)
			m_Grid->SetRowData(j+1,4);
		if(j==3)
			m_Grid->SetRowData(j+1,5);
		if(j==7)
			m_Grid->SetRowData(j+1,6);
		if(j==13)
			m_Grid->SetRowData(j+1,7);
		if(j==14)
			m_Grid->SetRowData(j+1,11);
	}
	RS.Close();
	m_Grid->SetCol(1);
	m_Grid->SetRow(3);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(2);
	m_Grid->SetCellBackColor(0xDFDFDF);
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(2);
//	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(3);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(4);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(5);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(6);
	m_Grid->SetCellFontBold(true);
//	m_Grid->SetRow(7);
//	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(8);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(9);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(10);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(11);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(13);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Grid->SetTextMatrix(5,1,_T("GE06D"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("BC"));
	m_Combo1->AddString(_T("BT"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
/*	CDBVariant TempVar;
	CString F1,F2;
	CString m_Tbl;
	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	DB.Close();
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO3);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("H"));
	m_Combo1->AddString(_T("V"));
	m_Combo1->AddString(_T("M"));
	m_Combo1->AddString(_T("U"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO4);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1->AddString(_T("4"));
	m_Combo1->AddString(_T("5"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO5);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("GS2"));
	m_Combo1->AddString(_T("GT2"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO6);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("RPC1"));
	m_Combo1->AddString(_T("RPC2"));
	m_Combo1->AddString(_T("RPC3"));
	m_Combo1->AddString(_T("RPC4"));
	m_Combo1->AddString(_T("RPC5"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO7);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("RN1"));
	m_Combo1->AddString(_T("RN2"));
	m_Combo1->AddString(_T("RN3"));
	m_Combo1->AddString(_T("RN4"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO8);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T(""));
	m_Combo1->AddString(_T("1"));
	m_Combo1->AddString(_T("2"));
	m_Combo1->AddString(_T("3"));
	m_Combo1->AddString(_T("N"));
	m_Combo1->AddString(_T("S"));
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

bool CTreeviewView::AllotSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[20], Values[20], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=2;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
//		if(m_Grid->GetCellBackColor()!=0xFFFFFF)
//			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft();
		Values[j].TrimRight();
		j++;
	}
	if(Values[2].IsEmpty())
		Missing= m_Grid->GetTextMatrix(1,0) + ",";
	if(Values[5].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(4,0) + ",";
	if(Values[6].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(5,0) + ",";
	if(Values[7].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(6,0) + ",";
	if(Values[9].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(8,0) + ",";
	if(Values[10].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(9,0) + ",";
	if(Values[11].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(10,0) + ",";
	if(Values[12].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(11,0) + ",";
	if(Values[14].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(13,0) + ",";
	if(Values[5].Mid(2,1)==_T("T") && Values[15].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(14,0) + ",";
/*	if(Values[16].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(15,0) + ",";*/
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else 
	{
		if(m_Action==1) // Add new
		{
			if(AllotValidation(Values))
			{
				CString NewID;
				SQL=_T("Select max(AllotKey)+1 from rrc_allotment");
				RS.Open(CRecordset::dynaset,SQL);
				RS.GetFieldValue((short)0,NewID);
				RS.Close();
				if(NewID.IsEmpty()) NewID=_T("1");
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				SQL.Format(_T("select %d,%s,'%s','%s',%s,%d,'%s','%s',%s,'%s','%s',%lf,'%s','%s','%s','%s','%s','%s',%s,'%s'  "),
					-1, (LPCTSTR)NewID, Values[2], Values[3].Left(3), Values[4].IsEmpty()?_T("0"):Values[4], -1, Values[5], Values[6], 
					Values[7].IsEmpty()?_T("NULL"):Values[7], Values[8], Values[9], atof(Values[10])*1000000, Values[11],
					Values[12].Left(3), Values[13].Left(2), Values[14].Left(2), Values[15], 
					Values[16], Values[17].IsEmpty()?_T("NULL"):Values[17], Values[18]);
				SQL=_T("SpectMask, Offset, TVChannel ) ")+SQL;
				SQL=_T("PlanEntry, SfnID, RefPlanCfg, Frequency, AdmRefID, Ctry, ClassStation, Polar, TypRefNetwk, ")+SQL;
				SQL=_T("insert into rrc_allotment (terrakey, allotkey, allot_name, geo_area, nb_sub_areas, LicID, NoticeType, Fragment, ")+SQL;
				
				DB.ExecuteSQL(SQL);
				HTREEITEM Root1=pView->GetTreeCtrl().GetChildItem(Node);
				CString label;
				label.Format(_T("%s-%s"),(LPCTSTR)Values[2],NewID);
				Node=pView->GetTreeCtrl().InsertItem(_Z("GE06 Allotment: ")+label,ALLOTMENT,ALLOTMENT,Root1);
				pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID));
				pView->GetTreeCtrl().Select(Node,TVGN_CARET);
				//m_Refresh=false;
				pView->RedrawWindow();
				result=true;
				AddTrail(_Z("Add allotment"),m_RecID,_T("rrc_allotment"));
			}
			else
				result=false;
		}
		else    // Update
		{
			SQL.Format(_T("Select * from rrc_allotment where allotkey=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(int i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			Values[0]=Fields[0];
			Values[1]=Fields[1];
			if(AllotValidation(Values))
			{
				SQL1.Format(_T("UPDATE rrc_allotment SET allot_name='%s', geo_area='%s', nb_sub_areas=%s, "), 
					Values[2], Values[3].Left(3), Values[4].IsEmpty()?_T("0"):Values[4]);
				SQL2=SQL1;
				SQL1.Format(_T("NoticeType = '%s', Fragment = '%s', PlanEntry = %s, SfnID='%s',"), 
					Values[5], Values[6], Values[7].IsEmpty()?_T("NULL"):Values[7], Values[8]);
				SQL2+=SQL1;
				SQL1.Format(_T("RefPlanCfg = '%s', Frequency = %lf, AdmRefID = '%s', Ctry = '%s', "), 
					Values[9], atof(Values[10])*1000000, Values[11], Values[12].Left(3));
				SQL2+=SQL1;
				SQL1.Format(_T("ClassStation = '%s', Polar = '%s', TypRefNetwk = '%s', SpectMask = '%s', "), 
					Values[13].Left(2), Values[14], Values[15], Values[16]);
				SQL2+=SQL1;
				SQL1.Format(_T("Offset= %s, TVChannel = '%s' "),
					Values[17].IsEmpty()?_T("NULL"):Values[17],Values[18]);
				SQL2+=SQL1;
				SQL1.Format(_T("WHERE allotkey=%ld"), m_RecID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				CString label;
				label.Format(_T("%s-%ld"),(LPCTSTR)Values[2],m_RecID);
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("GE06 Allotment: ")+label);

				AddTrail(_Z("Update allotment"),m_RecID,_T("rrc_allotment"));
				result=true;
			}
			else
				result=false;
		}
	}
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

void CTreeviewView::AddContour()
{
	CString SQL;
	CDatabase	DB;
	CRecordset	RS;
	DB.Open(m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_SAVE_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_EDIT_BUTTON))->EnableWindow(false);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_CANCEL_BUTTON))->EnableWindow(true);
	((CButton *)GetDlgItem(IDC_ATTACH))->ShowWindow(SW_HIDE);
	
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select * from rrc_contour where contourkey=-1"));
	RS.Open(CRecordset::dynaset,SQL);
	((CStatic *)GetDlgItem(IDC_GRID_TITLE))->SetWindowText(_Z("GE06 contour information"));
	m_Grid->ShowWindow(SW_HIDE);
	m_Grid->ClearStructure();
	m_Grid->SetCols(0,3);
	m_Grid->SetTextMatrix(0,1,_Z("Value"));
	m_Grid->SetTextMatrix(0,2,_Z("Unit"));
	m_Grid->SetColWidth(0,0,4000);
	m_Grid->SetColWidth(1,0,3000);
	m_Grid->SetColWidth(2,0,2000);
	CString FName,Value,Unit,Format,Srv,Mask;
	m_Grid->SetRows(RS.GetODBCFieldCount()-3);
	CODBCFieldInfo FldInfo;
	for(int i=1,j=0;i<RS.GetODBCFieldCount();i++,j++)
	{
		RS.GetODBCFieldInfo(i,FldInfo);
		FName=GetFieldName(&DB, _T("rrc_contour"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		if(Srv==_T("-"))
		{
			j--;
			continue;
		}
		m_Grid->SetTextMatrix(j+1,0,FName);
		m_Mask[0][j+1]=Mask;
		m_Mask[1][j+1]=Format;
//		RS.GetFieldValue(i,Value);
		/*if(j==4)
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			float s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}*/
/*		if(j==10)
		{
			CString Temp;
			double lat=atof(Value);
			int d=(int)lat,
			m=abs((int)((fabs(lat)-(double)abs(d))*60.));
			double s=fabs(((fabs(lat)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s>59.99)
			{
				s=0;
				m++;
			}
			if(m>59.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+03d%02d%05.2f"),d,m,s);
			Value=Temp;
		}
		if(j==9)
		{
			CString Temp;
			double lon=atof(Value);
			int d=(int)lon,
			m=abs((int)((fabs(lon)-(double)abs(d))*60.));
			double s=fabs(((fabs(lon)-(double)abs(d))*60.-(double)abs(m))*60.);
			if(s==60.)
			{
				s=0;
				m++;
			}
			if(m==60.)
			{
				m=0;
				d++;
			}
			Temp.Format(_T("%+04d%02d%05.2f"),d,m,s);
			Value=Temp;
		}*/
		m_Grid->SetTextMatrix(j+1,1,Value);
		m_Grid->SetTextMatrix(j+1,2,Unit);
		if(j==0 || j==1)
			m_Grid->SetRowData(j+1,2);
	}
	RS.Close();
	m_Grid->SetCol(0);
	m_Grid->SetRow(1);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(2);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetRow(3);
	m_Grid->SetCellFontBold(true);
	m_Grid->SetColSel(1);
	m_Grid->SetCol(1);
	m_Grid->SetRow(1);
	m_Grid->SetRowSel(1);
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO1);
	m_Combo1->ResetContent();
	m_Combo1->AddString(_T("S"));
	m_Combo1->AddString(_T("T"));
	m_Combo1=(CComboBox *)GetDlgItem(IDC_COMBO2);
/*	CDBVariant TempVar;
	CString F1,F2;
	CString m_Tbl;
	m_Tbl=_T("SELECT * FROM Country");
	RS.Open( CRecordset::snapshot, m_Tbl);
	m_Combo1->ResetContent();
	while(1)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,F1);
		RS.GetFieldValue((short)1,F2);
		m_Combo1->AddString(F1+_T(" - ")+F2);
		RS.MoveNext();
	}
	RS.Close();	*/
	CString CTYCOD[300];
	int NOCTY;
	AllCodes_lang(CTYCOD,&NOCTY);
	m_Combo1->ResetContent();
	m_Combo1->AddString("");
	for(i=0;i<NOCTY;i++)
	{
		CString Str=CTYCOD[i];
		Str+=_T(" - ");
		Str+=Code2NameCTY_lang(CTYCOD[i], m_Lang);
		m_Combo1->AddString(Str);
	}
	DB.Close();
	m_Grid->SetFixedRows(1);
	m_Grid->ShowWindow(SW_SHOW);
}

bool CTreeviewView::ContourSave()
{
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	bool result=true;
	m_Grid=(CMSHFlexGrid *)GetDlgItem(IDC_GRID);
	long Row=m_Grid->GetRow(),Col=m_Grid->GetCol();
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	CString Fields[20], Values[20], Missing,SQL1,SQL2;
	int j,i;
	for(i=1,j=2;i<m_Grid->GetRows();i++)
	{
		m_Grid->SetRow(i);
		if(m_Grid->GetCellBackColor()!=0xFFFFFF)
			continue;
		Values[j]=m_Grid->GetTextMatrix(i,1);
		Values[j].TrimLeft();
		Values[j].TrimRight();
		j++;
	}
	if(Values[2].IsEmpty())
		Missing= m_Grid->GetTextMatrix(1,0) + ",";
	if(Values[3].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(2,0) + ",";
	if(Values[4].IsEmpty())
		Missing+= m_Grid->GetTextMatrix(3,0) + ",";
	if(!Missing.IsEmpty())
	{
		Missing.Delete(Missing.GetLength()-1,1);
		MessageBox(_Z("Please provide required information for : ")+Missing);
		result=false;
	}
	else 
	{
		if(m_Action==1) // Add new
		{
			//if(ContourValidation(Values,Fields))
			{
				CString NewID1, NewID2;
				SQL=_T("Select max(contourkey)+1,max(contour_id)+1 from rrc_contour");
				RS.Open(CRecordset::dynaset,SQL);
				RS.GetFieldValue((short)0,NewID1);
				RS.GetFieldValue((short)1,NewID2);
				RS.Close();
				if(NewID1.IsEmpty()) NewID1=_T("1");
				if(NewID2.IsEmpty()) NewID2=_T("1");
				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				HTREEITEM Node=pView->GetTreeCtrl().GetSelectedItem();
				SQL.Format(_T("insert into rrc_sub_area (allotkey, contourkey) select %ld,%s"),
					pView->GetTreeCtrl().GetItemData(Node), NewID1);
				DB.ExecuteSQL(SQL);
				
				SQL.Format(_T("select %s,%s,'%s','%s',%s,'%s' "),
					NewID1, NewID2, Values[2].Left(3), Values[3].Left(3), Values[4].IsEmpty()?_T("NULL"):Values[4], Values[5]);
				SQL=_T("insert into rrc_contour (contourkey, contour_id, adm, ctry, nb_test_pts, remarks) ")+SQL;
				
				DB.ExecuteSQL(SQL);
				SQL.Format(_T("update rrc_allotment set nb_sub_areas=nb_sub_areas+1 where allotkey=%ld"),pView->GetTreeCtrl().GetItemData(Node));
				DB.ExecuteSQL(SQL);
				CString label;
				Node=pView->GetTreeCtrl().InsertItem(_Z("Contour: ")+NewID1,CONTOUR,CONTOUR,pView->GetTreeCtrl().GetSelectedItem());
				pView->GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(NewID2));
				pView->GetTreeCtrl().Select(Node,TVGN_CARET);
				//m_Refresh=false;
				pView->RedrawWindow();
				result=true;
				AddTrail(_Z("Add contour"),m_RecID,_T("rrc_contour"));
			}
			//else
			//	result=false;
		}
		else    // Update
		{
			SQL.Format(_T("Select * from rrc_contour where contourkey=%ld"), m_RecID);
			RS.Open(CRecordset::dynaset,SQL);
			for(int i=0;i<RS.GetODBCFieldCount();i++)
				RS.GetFieldValue(i,Fields[i]);
			RS.Close();
			Values[0]=Fields[0];
			Values[1]=Fields[1];
			//if(ContourValidation(Values,Fields))
			{
				SQL1.Format(_T("UPDATE rrc_contour SET adm='%s', ctry='%s', nb_test_pts=%s, remarks='%s' where contourkey=%ld"),
					Values[2].Left(3), Values[3].Left(3), Values[4].IsEmpty()?_T("NULL"):Values[4], Values[5], m_RecID);
				DB.ExecuteSQL(SQL1);

				CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 0);
				CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
				CString label;
				label.Format(_T("%ld"),m_RecID);
				pView->GetTreeCtrl().SetItemText(pView->GetTreeCtrl().GetSelectedItem(),_Z("Contour: ")+label);

				AddTrail(_Z("Update contour"),m_RecID,_T("rrc_contour"));
				result=true;
			}
			//else
			//	result=false;
		}
	}
	RS.Close();
	DB.Close();
	m_Grid->SetRow(Row);
	m_Grid->SetCol(Col);
	return result;
}

bool CTreeviewView::AllotValidation(CString Values[])
{
	CDatabase DB;
	CRecordset RS;
	CString SQL,Rep="",Value;
	CString Part;
	if((Values[5]==_T("GS2") && Values[16]!=_T("1") && Values[16]!=_T("2") && Values[16]!=_T("3")) ||
	   (Values[5]==_T("GT2") && Values[16]!=_T("N") && Values[16]!=_T("S")))
	{
		Part.Format(_Z("Spectrum Mask and Notice Type values are not compatible,"));
		Rep+=Part;
	}
	if(Values[5]==_T("GT2"))
		if(Values[15].IsEmpty())
			Rep+=_Z("Reference Network is mandatory for this notice type,");

	if(Rep.GetLength())
	{
		Rep.Delete(Rep.GetLength()-1);
		AfxMessageBox(Rep);
		return false;
	}
	return true;
}

void CTreeviewView::ChangeMenuLang() 
{
	if (m_Lang==_T("En"))	return;

	CMenu SharedMenu;
	SharedMenu.LoadMenu(IDR_TREEVITYPE);
	SetMenu(&SharedMenu);
			
	CWnd *pParent = GetParentFrame();
	TranslateMenu(&SharedMenu);	 
	((CChildFrame *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;

	SharedMenu.Detach();
};

void CTreeviewView::TranslateMenu(CMenu *pMenu)
{
    CString strOriginal(_T(""));
	CString strTranslated(_T(""));
	WORD wMenuState;

	if (pMenu == NULL || !::IsMenu(pMenu->m_hMenu))		return;

	int iSize = pMenu->GetMenuItemCount();
    // loop all the menu items in this level
	MENUITEMINFO menuItemInfo;
    for (int i=0; i<iSize; i++)
    {
		wMenuState = (WORD) pMenu->GetMenuState(i, MF_BYPOSITION);
		BOOL bIsPopup = wMenuState & MF_POPUP;

        // Get the menu string
        //pMenu->GetMenuString(i, strOriginal, MF_BYPOSITION);
		ZeroMemory(&menuItemInfo, sizeof(MENUITEMINFO));
		menuItemInfo.cbSize = sizeof(MENUITEMINFO);
		menuItemInfo.fMask = MIIM_TYPE;
		pMenu->GetMenuItemInfo(i, &menuItemInfo, TRUE);
		if (menuItemInfo.cch > 0)
		{
			menuItemInfo.cch++;
			menuItemInfo.dwTypeData = new char [menuItemInfo.cch];
			pMenu->GetMenuItemInfo(i, &menuItemInfo, TRUE);
			strOriginal = CString(menuItemInfo.dwTypeData);
			delete [] menuItemInfo.dwTypeData;
			menuItemInfo.dwTypeData = NULL;
		}
		else	strOriginal = _T("");

		if (!strOriginal.IsEmpty())
		{
			strTranslated = _Z(strOriginal);
			if (!strTranslated.IsEmpty() && strTranslated != strOriginal)
			{
				UINT uiID = 0;
				UINT uiFlags = MF_STRING | MF_BYPOSITION;
				uiID = pMenu->GetMenuItemID(i);
				if (bIsPopup)
				{
					uiFlags |= MF_POPUP;
					HMENU hPopupMenu = pMenu->GetSubMenu(i)->m_hMenu;
					pMenu->ModifyMenu(i, uiFlags, (UINT)hPopupMenu, strTranslated);
				}
				else	pMenu->ModifyMenu(i, uiFlags, uiID, strTranslated);
			}
		}
		if (bIsPopup)
		{
			CMenu *pSubMenu = pMenu->GetSubMenu(i);
			if (pSubMenu != NULL && ::IsMenu(pSubMenu->m_hMenu))	TranslateMenu(pSubMenu);
		}
    }//for
}


CString CTreeviewView::GetTranslatedString(CString strOriginal, CString Lang)
{
	static CString m_Lang;
	if(Lang!=m_Lang && !Lang.IsEmpty()) 
		m_Lang=Lang;
	if(m_Lang==_T("En"))	return strOriginal;
	int ID=-1;
	HMODULE	hMod = LoadLibrary("ResDLLen.dll");
	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			int n=0, nLen = ::LoadString(hMod, 0, szTemp, 1000);
			if(nLen!=0)		n = atoi(szTemp);

			for(int ids=1; ids<=n; ids++)
			{
				nLen = ::LoadString(hMod, ids, szTemp, 1000);
				if(strOriginal==szTemp)
				{
					ID = ids;
					break;
				}
			}
		}
		FreeLibrary(hMod);
	}//hMod

	CString str;
	if		(m_Lang==_T("Fr")) 	hMod = LoadLibrary("ResDLLfr.dll");
	else if	(m_Lang==_T("Es")) 	hMod = LoadLibrary("ResDLLes.dll");
	else if	(m_Lang==_T("Ch")) 	hMod = LoadLibrary("ResDLLch.dll");
	else if	(m_Lang==_T("Ar")) 	hMod = LoadLibrary("ResDLLar.dll");
	else if	(m_Lang==_T("Ru")) 	hMod = LoadLibrary("ResDLLru.dll");

	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			::LoadString(hMod, ID, szTemp, 1000);
			str = szTemp;
		}
		FreeLibrary(hMod);
	}//hMod

	return str;
}


