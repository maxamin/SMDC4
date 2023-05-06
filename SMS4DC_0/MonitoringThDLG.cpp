// MonitoringThDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "MonitoringThDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitoringThDLG dialog


CMonitoringThDLG::CMonitoringThDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitoringThDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMonitoringThDLG)
	m_EDIT_mth1 = 20.0;
	m_EDIT_mth2 = 12.0;
	m_EDIT_mth3 =  0.0;
	//}}AFX_DATA_INIT

	m_title  = _Z("Threshold Values");			
	m_label1 = _Z("Direction-Finding Threshold (dBuV/m) :");		
	m_label2 = _Z("Measurement Threshold (dBuV/m) :");		
	m_label3 = _Z("Listening Threshold (dBuV/m) :");
	m_flag = 1;

}


void CMonitoringThDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitoringThDLG)
	DDX_Text(pDX, IDC_EDIT_mth1, m_EDIT_mth1);
	DDX_Text(pDX, IDC_EDIT_mth2, m_EDIT_mth2);
	DDX_Text(pDX, IDC_EDIT_mth3, m_EDIT_mth3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitoringThDLG, CDialog)
	//{{AFX_MSG_MAP(CMonitoringThDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitoringThDLG message handlers

BOOL CMonitoringThDLG::OnInitDialog() 
{
	SetWindowText(m_title);									
	GetDlgItem(IDC_STATIC_mth1)->SetWindowText(m_label1);	
	GetDlgItem(IDC_STATIC_mth2)->SetWindowText(m_label2);	
	GetDlgItem(IDC_STATIC_mth3)->SetWindowText(m_label3);	
	if(m_flag==2)
	{
		GetDlgItem(IDC_STATIC_mth3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_mth3)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_mth3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_mth3)->ShowWindow(SW_SHOW);
	}

	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
