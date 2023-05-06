// RGNtableView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "RGNtableView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGNtableView

IMPLEMENT_DYNCREATE(CRGNtableView, CRecordView)

CRGNtableView::CRGNtableView()
	: CRecordView(CRGNtableView::IDD)
{
	//{{AFX_DATA_INIT(CRGNtableView)
	m_pSet = NULL;
	m_Regions2 = _T("1");
	//}}AFX_DATA_INIT
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarRGNtable), TRUE, FALSE);
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarALLplan), FALSE, FALSE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(2, "");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(3, "");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(4, "");
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(5, "");
}

CRGNtableView::~CRGNtableView()
{
	if (m_pSet)
		delete m_pSet;
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarRGNtable), FALSE, FALSE);
//	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarALLplan), TRUE, FALSE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, "");
}

void CRGNtableView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRGNtableView)
	DDX_Control(pDX, IDC_COMBO_SS6, m_ListSS6);
	DDX_Control(pDX, IDC_COMBO_SS5, m_ListSS5);
	DDX_Control(pDX, IDC_COMBO_SS4, m_ListSS4);
	DDX_Control(pDX, IDC_COMBO_SS3, m_ListSS3);
	DDX_Control(pDX, IDC_COMBO_SS2, m_ListSS2);
	DDX_Control(pDX, IDC_COMBO_SS1, m_ListSS1);
	DDX_Control(pDX, IDC_COMBO_PS5, m_ListPS5);
	DDX_Control(pDX, IDC_COMBO_PS6, m_ListPS6);
	DDX_Control(pDX, IDC_COMBO_PS4, m_ListPS4);
	DDX_Control(pDX, IDC_COMBO_PS3, m_ListPS3);
	DDX_Control(pDX, IDC_COMBO_PS2, m_ListPS2);
	DDX_Control(pDX, IDC_COMBO_PS1, m_ListPS1);
	DDX_FieldText(pDX, IDC_EDIT_FLO, m_pSet->m_FRQ_LO, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_FHI, m_pSet->m_FRQ_HI, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_fot, m_pSet->m_FOT, m_pSet);
	DDX_FieldText(pDX, IDC_FOTP1, m_pSet->m_FOTP1, m_pSet);
	DDX_FieldText(pDX, IDC_FOTP2, m_pSet->m_FOTP2, m_pSet);
	DDX_FieldText(pDX, IDC_FOTP3, m_pSet->m_FOTP3, m_pSet);
	DDX_FieldText(pDX, IDC_FOTP4, m_pSet->m_FOTP4, m_pSet);
	DDX_FieldText(pDX, IDC_FOTP5, m_pSet->m_FOTP5, m_pSet);
	DDX_FieldText(pDX, IDC_FOTP6, m_pSet->m_FOTP6, m_pSet);
	DDX_FieldText(pDX, IDC_FOTS1, m_pSet->m_FOTS1, m_pSet);
	DDX_FieldText(pDX, IDC_FOTS2, m_pSet->m_FOTS2, m_pSet);
	DDX_FieldText(pDX, IDC_FOTS3, m_pSet->m_FOTS3, m_pSet);
	DDX_FieldText(pDX, IDC_FOTS4, m_pSet->m_FOTS4, m_pSet);
	DDX_FieldText(pDX, IDC_FOTS5, m_pSet->m_FOTS5, m_pSet);
	DDX_FieldText(pDX, IDC_FOTS6, m_pSet->m_FOTS6, m_pSet);
	DDX_FieldText(pDX, IDC_PS1, m_pSet->m_PS1, m_pSet);
	DDX_FieldText(pDX, IDC_PS2, m_pSet->m_PS2, m_pSet);
	DDX_FieldText(pDX, IDC_PS3, m_pSet->m_PS3, m_pSet);
	DDX_FieldText(pDX, IDC_PS4, m_pSet->m_PS4, m_pSet);
	DDX_FieldText(pDX, IDC_PS5, m_pSet->m_PS5, m_pSet);
	DDX_FieldText(pDX, IDC_PS6, m_pSet->m_PS6, m_pSet);
	DDX_FieldText(pDX, IDC_Regions, m_pSet->m_REGION, m_pSet);
	DDX_Text(pDX, IDC_Regions2, m_Regions2);
	DDX_FieldText(pDX, IDC_SS1, m_pSet->m_SS1, m_pSet);
	DDX_FieldText(pDX, IDC_SS2, m_pSet->m_SS2, m_pSet);
	DDX_FieldText(pDX, IDC_SS3, m_pSet->m_SS3, m_pSet);
	DDX_FieldText(pDX, IDC_SS4, m_pSet->m_SS4, m_pSet);
	DDX_FieldText(pDX, IDC_SS5, m_pSet->m_SS5, m_pSet);
	DDX_FieldText(pDX, IDC_SS6, m_pSet->m_SS6, m_pSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRGNtableView, CRecordView)
	//{{AFX_MSG_MAP(CRGNtableView)
	ON_CBN_SELCHANGE(IDC_COMBO_PS1, OnSelchangeComboPs1)
	ON_CBN_SELCHANGE(IDC_COMBO_PS2, OnSelchangeComboPs2)
	ON_CBN_SELCHANGE(IDC_COMBO_PS3, OnSelchangeComboPs3)
	ON_CBN_SELCHANGE(IDC_COMBO_PS4, OnSelchangeComboPs4)
	ON_CBN_SELCHANGE(IDC_COMBO_PS5, OnSelchangeComboPs5)
	ON_CBN_SELCHANGE(IDC_COMBO_PS6, OnSelchangeComboPs6)
	ON_CBN_SELCHANGE(IDC_COMBO_SS1, OnSelchangeComboSs1)
	ON_CBN_SELCHANGE(IDC_COMBO_SS2, OnSelchangeComboSs2)
	ON_CBN_SELCHANGE(IDC_COMBO_SS3, OnSelchangeComboSs3)
	ON_CBN_SELCHANGE(IDC_COMBO_SS4, OnSelchangeComboSs4)
	ON_CBN_SELCHANGE(IDC_COMBO_SS5, OnSelchangeComboSs5)
	ON_CBN_SELCHANGE(IDC_COMBO_SS6, OnSelchangeComboSs6)
	ON_COMMAND(ID_RECORD_FIRST, OnRecordFirst)
	ON_COMMAND(ID_RECORD_PREV, OnRecordPrev)
	ON_COMMAND(ID_RECORD_NEXT, OnRecordNext)
	ON_COMMAND(ID_RECORD_LAST, OnRecordLast)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_COMMAND(ID_RECORD_SAVE, OnRecordSave)
	ON_COMMAND(ID_RECORD_ADD, OnRecordAdd)
	ON_COMMAND(ID_RECORD_SUB, OnRecordSub)
	ON_EN_KILLFOCUS(IDC_EDIT_FLO, OnKillfocusEditFlo)
	ON_EN_KILLFOCUS(IDC_EDIT_FHI, OnKillfocusEditFhi)
	ON_EN_KILLFOCUS(IDC_EDIT_fot, OnKillfocusEDITfot)
	ON_EN_KILLFOCUS(IDC_FOTP1, OnKillfocusFotp1)
	ON_EN_KILLFOCUS(IDC_FOTP2, OnKillfocusFotp2)
	ON_EN_KILLFOCUS(IDC_FOTP3, OnKillfocusFotp3)
	ON_EN_KILLFOCUS(IDC_FOTP4, OnKillfocusFotp4)
	ON_EN_KILLFOCUS(IDC_FOTP5, OnKillfocusFotp5)
	ON_EN_KILLFOCUS(IDC_FOTP6, OnKillfocusFotp6)
	ON_EN_KILLFOCUS(IDC_FOTS1, OnKillfocusFots1)
	ON_EN_KILLFOCUS(IDC_FOTS2, OnKillfocusFots2)
	ON_EN_KILLFOCUS(IDC_FOTS3, OnKillfocusFots3)
	ON_EN_KILLFOCUS(IDC_FOTS4, OnKillfocusFots4)
	ON_EN_KILLFOCUS(IDC_FOTS5, OnKillfocusFots5)
	ON_EN_KILLFOCUS(IDC_FOTS6, OnKillfocusFots6)
	ON_COMMAND(ID_BandSort, OnBandSort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRGNtableView diagnostics

#ifdef _DEBUG
void CRGNtableView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CRGNtableView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRGNtableView message handlers

CRecordset* CRGNtableView::OnGetRecordset()
{
	if (m_pSet != NULL)
		return m_pSet;

	m_pSet = new CRGNtableSet(NULL);
	m_pSet->Open();

	return m_pSet;
}

CRGNtableSet* CRGNtableView::GetRecordset()
{
	CRGNtableSet* pData = (CRGNtableSet*) OnGetRecordset();
	ASSERT(pData == NULL || pData->IsKindOf(RUNTIME_CLASS(CRGNtableSet)));
	return pData;
}

void CRGNtableView::OnInitialUpdate()
{
	BeginWaitCursor();
	GetRecordset();
	CRecordView::OnInitialUpdate();
	if (m_pSet->IsOpen())
	{
		CString strTitle = m_pSet->m_pDatabase->GetDatabaseName();
		CString strTable = m_pSet->GetTableName();		strTable.TrimRight();
		if (!strTable.IsEmpty())	strTitle += _T(" : ") + strTable;
		GetDocument()->SetTitle(strTitle);
	}

	m_count=0;
	while (!m_pSet->IsEOF())
	{
		m_count = m_count + 1;
		m_pSet->MoveNext();
	}
	m_pSet->MoveFirst();

	CString str;
	m_num = 1;
	str.Format(_Z("Record")+" : %d   "+ _Z("of") +"   %d",m_num,m_count);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CDatabase m_mydb;
	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		CODBCFieldInfo FldInfo;
		CRecordset m_rs;
//		CString	m_Tbl = "select * from SRVCode_Color_Name ORDER BY ID";
		CString	m_Tbl = "select * from SRVCode_Color_Name ORDER BY SRV_CODE";
		m_rs.m_pDatabase=&m_mydb;
		m_rs.Open( CRecordset::snapshot, m_Tbl);
		CString PS;
		m_rs.MoveFirst();
		while(!m_rs.IsEOF())
		{
			if     (((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("En"))		m_rs.GetFieldValue((short)5, PS);
			else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Fr"))		m_rs.GetFieldValue((short)7, PS);
			else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Es"))		m_rs.GetFieldValue((short)9, PS); //940312
			m_ListPS1.AddString(PS);
			m_ListPS2.AddString(PS);
			m_ListPS3.AddString(PS);
			m_ListPS4.AddString(PS);
			m_ListPS5.AddString(PS);
			m_ListPS6.AddString(PS);

			if     (((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("En"))		m_rs.GetFieldValue((short)6,  PS);
			else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Fr"))		m_rs.GetFieldValue((short)8,  PS);
			else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Es"))		m_rs.GetFieldValue((short)10, PS); //940312
			m_ListSS1.AddString(PS);
			m_ListSS2.AddString(PS);
			m_ListSS3.AddString(PS);
			m_ListSS4.AddString(PS);
			m_ListSS5.AddString(PS);
			m_ListSS6.AddString(PS);
			m_rs.MoveNext();
		}
		m_rs.Close();
		m_mydb.Close();
	}
	SetListsItem();

	if(m_pSet->m_REGION == 4)	m_Regions2 = _Z("National");
	else						m_Regions2.Format("%d",m_pSet->m_REGION);
	UpdateData(false);	

	EndWaitCursor();
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE36);
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog((CDialog *)this);
}


int CRGNtableView::Name2ID(CString name_str,int psFlag)
{
	int i = 0;
	CDBVariant Fld;
	CDatabase m_mydb;
	CRecordset m_rs;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	CString	m_Tbl = _T("select * from SRVCode_Color_Name");
	CString Filter = _T("");

	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		m_rs.m_pDatabase=&m_mydb;

		CString mP = _T("") , mS = _T("");
		if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("En"))
		{
			mP = _T("SRV_NAME_P_en");
			mS = _T("SRV_NAME_S_en");
		}
		else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Fr"))
		{
			mP = _T("SRV_NAME_P_fr");
			mS = _T("SRV_NAME_S_fr");
		}
		else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Es"))  //940312
		{
			mP = _T("SRV_NAME_P_es");
			mS = _T("SRV_NAME_S_es");
		}

		if (name_str.IsEmpty())
		{
			if     (psFlag==1)		Filter.Format("((%s) Is Null)",mP);
			else if(psFlag==2)		Filter.Format("((%s) Is Null)",mS);
		}
		else
		{
			if     (psFlag==1)		Filter.Format("(%s=\'%s\')",mP,name_str);
			else if(psFlag==2)		Filter.Format("(%s=\'%s\')",mS,name_str);
		}

		if(m_Tbl.Find(" where ")==-1)	Filter = m_Tbl + _T(" where ") + Filter;
		else							Filter = m_Tbl + _T(" and ") + Filter;

		m_rs.Open( CRecordset::snapshot, Filter);
		m_rs.MoveFirst();

		m_rs.GetFieldValue((short)0, Fld);
		i = Fld.m_lVal;
	}
	m_rs.Close();
	m_mydb.Close();

	return i;
}


CString CRGNtableView::ID2Name(int ID,int psFlag)
{
	CString m_Tbl, str = _T("") , mPS = _T("");
	CDatabase m_mydb;
	CRecordset m_rs;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;

	if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("En"))
	{
		if     (psFlag==1)	mPS = _T("SRV_NAME_P_en");
		else if(psFlag==2)	mPS = _T("SRV_NAME_S_en");
	}
	else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Fr"))
	{
		if     (psFlag==1)	mPS = _T("SRV_NAME_P_fr");
		else if(psFlag==2)	mPS = _T("SRV_NAME_S_fr");
	}
	else if(((CSMS4DCApp *)AfxGetApp())->m_Lang == _T("Es"))  //940312 
	{
		if     (psFlag==1)	mPS = _T("SRV_NAME_P_es");
		else if(psFlag==2)	mPS = _T("SRV_NAME_S_es");
	}
	m_Tbl.Format("SELECT %s FROM SRVCode_Color_Name WHERE (((ID)=%d));",mPS,ID);

	if (m_mydb.Open(_T(m_DB),FALSE,TRUE, "ODBC;", FALSE))
	{
		m_rs.m_pDatabase = &m_mydb;
		m_rs.Open( CRecordset::snapshot, m_Tbl);
		m_rs.MoveFirst();
		m_rs.GetFieldValue(mPS, str);
	}
	m_rs.Close();
	m_mydb.Close();

	return str;
}





void CRGNtableView::OnSelchangeComboPs1() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListPS1.GetCurSel();
	CString name_str , PSstr;
	m_ListPS1.GetLBText(i,name_str);	
	i = Name2ID(name_str,1);
	PSstr.Format("%d",i);
	m_pSet->m_PS1 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboPs2() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListPS2.GetCurSel();
	CString name_str , PSstr;
	m_ListPS2.GetLBText(i,name_str);	
	i = Name2ID(name_str,1);
	PSstr.Format("%d",i);
	m_pSet->m_PS2 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboPs3() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListPS3.GetCurSel();
	CString name_str , PSstr;
	m_ListPS3.GetLBText(i,name_str);	
	i = Name2ID(name_str,1);
	PSstr.Format("%d",i);
	m_pSet->m_PS3 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboPs4() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListPS4.GetCurSel();
	CString name_str , PSstr;
	m_ListPS4.GetLBText(i,name_str);	
	i = Name2ID(name_str,1);
	PSstr.Format("%d",i);
	m_pSet->m_PS4 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboPs5() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListPS5.GetCurSel();
	CString name_str , PSstr;
	m_ListPS5.GetLBText(i,name_str);	
	i = Name2ID(name_str,1);
	PSstr.Format("%d",i);
	m_pSet->m_PS5 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboPs6() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListPS6.GetCurSel();
	CString name_str , PSstr;
	m_ListPS6.GetLBText(i,name_str);	
	i = Name2ID(name_str,1);
	PSstr.Format("%d",i);
	m_pSet->m_PS6 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboSs1() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListSS1.GetCurSel();
	CString name_str , PSstr;
	m_ListSS1.GetLBText(i,name_str);	
	i = Name2ID(name_str,2);
	PSstr.Format("%d",i);
	m_pSet->m_SS1 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboSs2() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListSS2.GetCurSel();
	CString name_str , PSstr;
	m_ListSS2.GetLBText(i,name_str);	
	i = Name2ID(name_str,2);
	PSstr.Format("%d",i);
	m_pSet->m_SS2 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboSs3() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListSS3.GetCurSel();
	CString name_str , PSstr;
	m_ListSS3.GetLBText(i,name_str);	
	i = Name2ID(name_str,2);
	PSstr.Format("%d",i);
	m_pSet->m_SS3 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboSs4() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListSS4.GetCurSel();
	CString name_str , PSstr;
	m_ListSS4.GetLBText(i,name_str);	
	i = Name2ID(name_str,2);
	PSstr.Format("%d",i);
	m_pSet->m_SS4 = PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboSs5() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListSS5.GetCurSel();
	CString name_str , PSstr;
	m_ListSS5.GetLBText(i,name_str);	
	i = Name2ID(name_str,2);
	PSstr.Format("%d",i);
	m_pSet->m_SS5= PSstr;
	m_pSet->Update();
	UpdateData(false);	
}

void CRGNtableView::OnSelchangeComboSs6() 
{
	UpdateData();
	m_pSet->Edit();

	int i = m_ListSS6.GetCurSel();
	CString name_str , PSstr;
	m_ListSS6.GetLBText(i,name_str);	
	i = Name2ID(name_str,2);
	PSstr.Format("%d",i);
	m_pSet->m_SS6= PSstr;
	m_pSet->Update();
	UpdateData(false);	
}


void CRGNtableView::SetListsItem() 
{
/*
	m_ListPS1.SetCurSel(atoi( m_pSet->m_PS1 ) - 1);	
	m_ListPS2.SetCurSel(atoi( m_pSet->m_PS2 ) - 1);	
	m_ListPS3.SetCurSel(atoi( m_pSet->m_PS3 ) - 1);	
	m_ListPS4.SetCurSel(atoi( m_pSet->m_PS4 ) - 1);	
	m_ListPS5.SetCurSel(atoi( m_pSet->m_PS5 ) - 1);	
	m_ListPS6.SetCurSel(atoi( m_pSet->m_PS6 ) - 1);	

	m_ListSS1.SetCurSel(atoi( m_pSet->m_SS1 ) - 1);	
	m_ListSS2.SetCurSel(atoi( m_pSet->m_SS2 ) - 1);	
	m_ListSS3.SetCurSel(atoi( m_pSet->m_SS3 ) - 1);	
	m_ListSS4.SetCurSel(atoi( m_pSet->m_SS4 ) - 1);	
	m_ListSS5.SetCurSel(atoi( m_pSet->m_SS5 ) - 1);	
	m_ListSS6.SetCurSel(atoi( m_pSet->m_SS6 ) - 1);	
*/
	CString str;	int i;
	str = ID2Name(atoi( m_pSet->m_PS1 )  , 1);	i = (str.IsEmpty()) ? 0 : m_ListPS1.FindStringExact(0,str);	m_ListPS1.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_PS2 )  , 1);	i = (str.IsEmpty()) ? 0 : m_ListPS1.FindStringExact(0,str);	m_ListPS2.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_PS3 )  , 1);	i = (str.IsEmpty()) ? 0 : m_ListPS2.FindStringExact(0,str);	m_ListPS3.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_PS4 )  , 1);	i = (str.IsEmpty()) ? 0 : m_ListPS3.FindStringExact(0,str);	m_ListPS4.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_PS5 )  , 1);	i = (str.IsEmpty()) ? 0 : m_ListPS4.FindStringExact(0,str);	m_ListPS5.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_PS6 )  , 1);	i = (str.IsEmpty()) ? 0 : m_ListPS5.FindStringExact(0,str);	m_ListPS6.SetCurSel(i);

	str = ID2Name(atoi( m_pSet->m_SS1 )  , 2);	i = (str.IsEmpty()) ? 0 : m_ListSS1.FindStringExact(0,str);	m_ListSS1.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_SS2 )  , 2);	i = (str.IsEmpty()) ? 0 : m_ListSS2.FindStringExact(0,str);	m_ListSS2.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_SS3 )  , 2);	i = (str.IsEmpty()) ? 0 : m_ListSS3.FindStringExact(0,str);	m_ListSS3.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_SS4 )  , 2);	i = (str.IsEmpty()) ? 0 : m_ListSS4.FindStringExact(0,str);	m_ListSS4.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_SS5 )  , 2);	i = (str.IsEmpty()) ? 0 : m_ListSS5.FindStringExact(0,str);	m_ListSS5.SetCurSel(i);
	str = ID2Name(atoi( m_pSet->m_SS6 )  , 2);	i = (str.IsEmpty()) ? 0 : m_ListSS6.FindStringExact(0,str);	m_ListSS6.SetCurSel(i);
}

void CRGNtableView::OnRecordFirst() 
{
	if(!m_pSet->IsBOF())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		UpdateData();	
		m_pSet->MoveFirst();

		CString str;
		m_num=1;
		str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

		SetListsItem();

		UpdateData(FALSE);
	}	
}

void CRGNtableView::OnRecordPrev() 
{
	if(!m_pSet->IsBOF())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		UpdateData();	
		m_pSet->MovePrev();

		CString str;
		m_num=m_num-1;
		str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

		SetListsItem();

		UpdateData(FALSE);
	}	
}

void CRGNtableView::OnRecordNext() 
{
	if(!m_pSet->IsEOF())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		UpdateData();	
		m_pSet->MoveNext();

		CString str;
		m_num=min(m_num+1,m_count);
		str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

		SetListsItem();

		UpdateData(FALSE);
	}		
}

void CRGNtableView::OnRecordLast() 
{
	if(!m_pSet->IsEOF())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();

		UpdateData();	
		m_pSet->MoveLast();

		CString str;
		m_num=m_count;
		str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

		SetListsItem();

		UpdateData(FALSE);
	}	
}

void CRGNtableView::OnUpdateRecordNext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_num<m_count);
}
void CRGNtableView::OnUpdateRecordLast(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_num<m_count);
}

void CRGNtableView::OnRecordSave() 
{
	if(m_pSet->CanUpdate() && !m_pSet->IsDeleted())
	{
		m_pSet->Edit();
		if(UpdateData())
		{
			m_pSet->Update();
			SetListsItem();
			UpdateData(false);		
		}
	}
}


void CRGNtableView::OnAppend() 
{
	if(m_pSet->CanUpdate() && !m_pSet->IsDeleted())
	{
		m_pSet->Edit();
		if(!UpdateData()) return;
		m_pSet->Update();
	}
	int REGION = m_pSet->m_REGION;

	m_pSet->MoveLast();
	m_pSet->AddNew();

	m_pSet->m_FRQ_LO = 0;
	m_pSet->m_FRQ_HI = 0;
	m_pSet->m_REGION = REGION;
	m_pSet->m_PS1 = _T("1");
	m_pSet->m_PS2 = _T("1");
	m_pSet->m_PS3 = _T("1");
	m_pSet->m_PS4 = _T("1");
	m_pSet->m_PS5 = _T("1");
	m_pSet->m_PS6 = _T("1");

	m_pSet->m_SS1 = _T("1");
	m_pSet->m_SS2 = _T("1");
	m_pSet->m_SS3 = _T("1");
	m_pSet->m_SS4 = _T("1");
	m_pSet->m_SS5 = _T("1");
	m_pSet->m_SS6 = _T("1");

	m_pSet->Update();
	m_pSet->MoveLast();

	m_count = m_count+1;
	m_num = m_count;

	SetListsItem();
	CString str;
	str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);
	UpdateData(false);
}

void CRGNtableView::OnRecordAdd() 
{
	OnAppend();
}

void CRGNtableView::OnDelete() 
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

	SetListsItem();

	UpdateData(FALSE);	
}

void CRGNtableView::OnRecordSub() 
{
	OnDelete() ;
}



void CRGNtableView::OnRecordSave1() 
{
	if(m_pSet->CanUpdate() && !m_pSet->IsDeleted())
	{
		m_pSet->Edit();
		if(UpdateData())
		{
			m_pSet->Update();
			SetListsItem();
			UpdateData(false);		
		}
	}
}
void CRGNtableView::OnKillfocusEditFlo() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusEditFhi() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusEDITfot() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFotp1() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFotp2() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFotp3() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFotp4() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFotp5() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFotp6() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFots1() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFots2() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFots3() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFots4() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFots5() 
{
	OnRecordSave1() ;	
}
void CRGNtableView::OnKillfocusFots6() 
{
	OnRecordSave1() ;	
}

void CRGNtableView::OnBandSort() 
{
	if(m_pSet->CanUpdate() && !m_pSet->IsDeleted())
	{
		m_pSet->Edit();
		if(UpdateData())
		{
			m_pSet->Update();
			m_pSet->Requery();
			SetListsItem();

			m_num = 1;
			CString str;
			str.Format(_Z("Record") + " : %d   " + _Z("of") + "   %d",m_num,m_count);
			((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndStatusBar.SetPaneText(1, str);

			UpdateData(false);		
		}
	}
}

BOOL CRGNtableView::PreTranslateMessage(MSG* pMsg) 
{
    switch (pMsg->message)
    {
		case WM_KEYDOWN:
			if((pMsg->hwnd == ((CEdit*)GetDlgItem(IDC_EDIT_FLO))->m_hWnd)||
			   (pMsg->hwnd == ((CEdit*)GetDlgItem(IDC_EDIT_FHI))->m_hWnd))
			{
				switch( pMsg->wParam )
				{
					case VK_NEXT:		if(m_num<m_count)	OnRecordNext();		break;
					case VK_PRIOR:		if(m_num>1)			OnRecordPrev();		break;
					default:													break;
				}
			}
		break;
    }
	return CRecordView::PreTranslateMessage(pMsg);
}
