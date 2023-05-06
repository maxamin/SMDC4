// P1812DLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "P1812DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CP1812DLG dialog


CP1812DLG::CP1812DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CP1812DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP1812DLG)
	m_time = 50.0;
	m_Location = 50.0;
	m_RxH = 3.0;
	m_Cvalue = -10.0;
	//}}AFX_DATA_INIT

	m_CvShow = FALSE;	
	m_RxShow = TRUE;

	m_Monitoring = FALSE;			//990428
}


void CP1812DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP1812DLG)
	DDX_Control(pDX, IDC_COMBO_IODoor, m_COMBO_IODoor);
	DDX_Control(pDX, IDC_COMBO_Service, m_COMBO_Service);
	DDX_Control(pDX, IDC_COMBO_Clutter, m_COMBO_Clutter);
	DDX_Text(pDX, IDC_EDIT_time, m_time);
	DDV_MinMaxDouble(pDX, m_time, 1., 50.);
	DDX_Text(pDX, IDC_EDIT_location, m_Location);
	DDV_MinMaxDouble(pDX, m_Location, 1., 99.);
	DDX_Text(pDX, IDC_EDIT_RxH, m_RxH);
	DDX_Text(pDX, IDC_EDIT_Cvalue, m_Cvalue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP1812DLG, CDialog)
	//{{AFX_MSG_MAP(CP1812DLG)
	ON_CBN_SELCHANGE(IDC_COMBO_Clutter, OnSelchangeCOMBOClutter)
	ON_CBN_SELCHANGE(IDC_COMBO_Service, OnSelchangeCOMBOService)
	ON_CBN_SELCHANGE(IDC_COMBO_IODoor, OnSelchangeCOMBOIODoor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP1812DLG message handlers

BOOL CP1812DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_COMBO_Clutter.AddString(_Z("Water/sea"));
	m_COMBO_Clutter.AddString(_Z("Open/rural"));
	m_COMBO_Clutter.AddString(_Z("Suburban"));
	m_COMBO_Clutter.AddString(_Z("Urban/trees/forest"));
	m_COMBO_Clutter.AddString(_Z("Dense urban"));
	m_COMBO_Clutter.SetCurSel(1);
	m_Clutter = 1;

	m_COMBO_Service.AddString(_Z("Mobile"));
	m_COMBO_Service.AddString(_Z("Broadcasting, Digital"));
	m_COMBO_Service.AddString(_Z("Broadcasting, Analogue"));
	m_COMBO_Service.SetCurSel(0);
	m_Service = 0;

	m_COMBO_IODoor.AddString(_Z("InDoor"));
	m_COMBO_IODoor.AddString(_Z("OutDoor"));
	m_COMBO_IODoor.SetCurSel(1);
	m_IODoor = 1;

	if(m_RxShow == TRUE)
	{
		GetDlgItem(IDC_EDIT_RxH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_RxH)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_EDIT_RxH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_RxH)->ShowWindow(SW_HIDE);
	}

	if(m_CvShow == TRUE)
	{
		GetDlgItem(IDC_STATIC_Cvalue)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Cvalue)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC_Cvalue)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Cvalue)->ShowWindow(SW_HIDE);
	}

	if(m_Monitoring == TRUE)
	{
		GetDlgItem(IDC_STATIC_Cvalue)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Cvalue)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_RxH)->SetWindowText(_Z("Transmitter Height(m)"));
		GetDlgItem(IDC_STATIC_Cvalue)->SetWindowText(_Z("Transmitter Power(W)"));
	}

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE; 
}

void CP1812DLG::OnSelchangeCOMBOClutter() 
{
	UpdateData(true);
	m_Clutter = m_COMBO_Clutter.GetCurSel();
	UpdateData(false);
}
void CP1812DLG::OnSelchangeCOMBOService() 
{
	UpdateData(true);
	m_Service = m_COMBO_Service.GetCurSel();
	UpdateData(false);
}
void CP1812DLG::OnSelchangeCOMBOIODoor() 
{
	UpdateData(true);
	m_IODoor = m_COMBO_IODoor.GetCurSel();
	UpdateData(false);
}
