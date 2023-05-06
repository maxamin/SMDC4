// CoordinatesDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "CoordinatesDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoordinatesDLG dialog


CCoordinatesDLG::CCoordinatesDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CCoordinatesDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoordinatesDLG)
	m_lat1M = _T("08");
	m_lat1D = _T("35");
	m_lat2D = _T("36");
	m_lat2M = _T("12");
	m_lat1S = _T("23.999");
	m_lat2S = _T("12.666");
	m_lon1D = _T("051");
	m_lon1M = _T("55");
	m_lon1S = _T("34.765");
	m_lon2D = _T("052");
	m_lon2M = _T("34");
	m_lon2S = _T("56.666");
	//}}AFX_DATA_INIT
}


void CCoordinatesDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoordinatesDLG)
	DDX_Control(pDX, IDC_lon2EW, m_lon2EW);
	DDX_Control(pDX, IDC_lat2NS, m_lat2NS);
	DDX_Control(pDX, IDC_lon1EW, m_lon1EW);
	DDX_Control(pDX, IDC_lat1NS, m_lat1NS);
	DDX_Text(pDX, IDC_lat1M, m_lat1M);
	DDV_MaxChars(pDX, m_lat1M, 2);
	DDX_Text(pDX, IDC_lat1D, m_lat1D);
	DDV_MaxChars(pDX, m_lat1D, 2);
	DDX_Text(pDX, IDC_lat2D, m_lat2D);
	DDV_MaxChars(pDX, m_lat2D, 2);
	DDX_Text(pDX, IDC_lat2M, m_lat2M);
	DDV_MaxChars(pDX, m_lat2M, 2);
	DDX_Text(pDX, IDC_lat1S, m_lat1S);
	DDV_MaxChars(pDX, m_lat1S, 6);
	DDX_Text(pDX, IDC_lat2S, m_lat2S);
	DDV_MaxChars(pDX, m_lat2S, 6);
	DDX_Text(pDX, IDC_lon1D, m_lon1D);
	DDV_MaxChars(pDX, m_lon1D, 3);
	DDX_Text(pDX, IDC_lon1M, m_lon1M);
	DDV_MaxChars(pDX, m_lon1M, 2);
	DDX_Text(pDX, IDC_lon1S, m_lon1S);
	DDV_MaxChars(pDX, m_lon1S, 6);
	DDX_Text(pDX, IDC_lon2D, m_lon2D);
	DDV_MaxChars(pDX, m_lon2D, 3);
	DDX_Text(pDX, IDC_lon2M, m_lon2M);
	DDV_MaxChars(pDX, m_lon2M, 2);
	DDX_Text(pDX, IDC_lon2S, m_lon2S);
	DDV_MaxChars(pDX, m_lon2S, 6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCoordinatesDLG, CDialog)
	//{{AFX_MSG_MAP(CCoordinatesDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoordinatesDLG message handlers

BOOL CCoordinatesDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData(true);
m_lat1M.Format("%02d",4);
//m_lon1M.Format("%02d",4);

	UpdateData(false);
	m_lat1NS.AddString("N");
	m_lat1NS.AddString("S");
	m_lat1NS.SetTopIndex(1);
	m_lat1NS.SetCurSel(0);	

	m_lon1EW.AddString("E");
	m_lon1EW.AddString("W");
	m_lon1EW.SetTopIndex(1);
	m_lon1EW.SetCurSel(0);	

	m_lat2NS.AddString("N");
	m_lat2NS.AddString("S");
	m_lat2NS.SetTopIndex(1);
	m_lat2NS.SetCurSel(0);	

	m_lon2EW.AddString("E");
	m_lon2EW.AddString("W");
	m_lon2EW.SetTopIndex(1);
	m_lon2EW.SetCurSel(0);	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
