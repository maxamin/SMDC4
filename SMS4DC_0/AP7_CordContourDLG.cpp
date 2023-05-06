// AP7_CordContourDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "AP7_CordContourDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAP7_CordContourDLG dialog


CAP7_CordContourDLG::CAP7_CordContourDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAP7_CordContourDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAP7_CordContourDLG)
	m_M1 = TRUE;
	m_M1_10 = FALSE;
	m_M1_20 = FALSE;
	m_M1_30 = FALSE;
	m_M1_40 = FALSE;
	m_M1_50 = FALSE;
	m_M1_60 = FALSE;
	m_M2 = TRUE;
	m_Data = _T("");
	m_NRow = 0;
	m_NRowsel = 0;
	m_Rows = 0;
	m_All = FALSE;
	//}}AFX_DATA_INIT
}


void CAP7_CordContourDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAP7_CordContourDLG)
	DDX_Check(pDX, IDC_CHECK_M1, m_M1);
	DDX_Check(pDX, IDC_CHECK_M1_10, m_M1_10);
	DDX_Check(pDX, IDC_CHECK_M1_20, m_M1_20);
	DDX_Check(pDX, IDC_CHECK_M1_30, m_M1_30);
	DDX_Check(pDX, IDC_CHECK_M1_40, m_M1_40);
	DDX_Check(pDX, IDC_CHECK_M1_50, m_M1_50);
	DDX_Check(pDX, IDC_CHECK_M1_60, m_M1_60);
	DDX_Check(pDX, IDC_CHECK_M2, m_M2);
	DDX_Text(pDX, IDC_EDIT_data, m_Data);
	DDX_Text(pDX, IDC_EDIT_nrow, m_NRow);
	DDX_Text(pDX, IDC_EDIT_nrowsel, m_NRowsel);
	DDX_Text(pDX, IDC_EDIT_rows, m_Rows);
	DDX_Control(pDX, IDC_MSFLEXGRID3, m_LIST1);
	DDX_Check(pDX, IDC_CHECK_all, m_All);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAP7_CordContourDLG, CDialog)
	//{{AFX_MSG_MAP(CAP7_CordContourDLG)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_all, OnCHECKall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAP7_CordContourDLG message handlers

BOOL CAP7_CordContourDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	m_LIST1.SetCols(15);
	m_LIST1.SetRows(m_Rows+1);	

	m_LIST1.SetRow(0);
	//m_LIST1.SetCol(0);
	m_LIST1.SetColWidth(0,400);
	m_LIST1.SetColWidth(1,600);
	m_LIST1.SetColWidth(3,700);
	m_LIST1.SetColWidth(4,700);
	m_LIST1.SetColWidth(6,1100);
	m_LIST1.SetColWidth(7,1000);
	m_LIST1.SetColWidth(8,1800);
	m_LIST1.SetColWidth(9,1100);
	m_LIST1.SetColWidth(10,2700);

	m_LIST1.SetColAlignment(6,2);

	m_LIST1.SetCol(1);	m_LIST1.SetText(_Z("Admin"));
	m_LIST1.SetCol(2);	m_LIST1.SetText(_Z("ES Name"));
	m_LIST1.SetCol(3);	m_LIST1.SetText(_Z("Country"));
	m_LIST1.SetCol(4);	m_LIST1.SetText(_T("Tx/Rx"));
	m_LIST1.SetCol(5);	m_LIST1.SetText(_Z("Group ID"));
	m_LIST1.SetCol(6);	m_LIST1.SetText(_Z("App7 Method"));
	m_LIST1.SetCol(7);	m_LIST1.SetText(_Z("SAT Name"));
	m_LIST1.SetCol(8);	m_LIST1.SetText(_Z("Coordinates"));
	m_LIST1.SetCol(9);	m_LIST1.SetText(_Z("Service Type"));
	m_LIST1.SetCol(10);	m_LIST1.SetText(_Z("Probably Affected Countries"));
	m_LIST1.SetCol(11);	m_LIST1.SetText(_Z("MinFrq(MHz)"));
	m_LIST1.SetCol(12);	m_LIST1.SetText(_Z("MaxFrq(MHz)"));
	m_LIST1.SetCol(13);	m_LIST1.SetText(_Z("Notice ID"));
	m_LIST1.SetCol(14);	m_LIST1.SetText(_Z("Beam Name"));

	CString PathFileNametemp =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("R1448\\temp7.tmp");
	FILE *fptemp=fopen(PathFileNametemp,"rt");
	char dum1[30],dum2[30],dum3[40];

	CString str,str1,str2;
	int L = (m_Data.GetLength())/m_Rows;
	for(int i=0;i<m_Rows;i++)
	{
		m_LIST1.SetRow(i+1);
		str.Format("%d",i+1);
		m_LIST1.SetCol(0);	m_LIST1.SetText(str);

		m_LIST1.SetCol(1);	m_LIST1.SetText(m_Data.Mid(i*L+0,3));
		str1 = m_Data.Mid(i*L+3,20);		str1.TrimLeft();
		m_LIST1.SetCol(2);	m_LIST1.SetText(str1);
		m_LIST1.SetCol(3);	m_LIST1.SetText(m_Data.Mid(i*L+23,3));
		str1 = m_Data.Mid(i*L+26,1);
		str1 = (str1=="E") ? "Tx" : "Rx";
		m_LIST1.SetCol(4);	m_LIST1.SetText(str1);

//		m_LIST1.SetCol(5);	m_LIST1.SetText(m_Data.Mid(i*L+28,7));

		str2 = m_Data.Mid(i*L+27,1);
		str2 = (str2=="5") ? "" : " ( " + str2 + " ) ";
		str1 = m_Data.Mid(i*L+35,8) ;		//str1.TrimRight();
		str1 = str1 + str2;
		m_LIST1.SetCol(6);	m_LIST1.SetText(str1);
		str1 = m_Data.Mid(i*L+43,20);		str1.TrimLeft();
		m_LIST1.SetCol(7);	m_LIST1.SetText(str1);

//		m_LIST1.SetCol(8);	m_LIST1.SetText(m_Data.Mid(i*L+63,15));
		str1.Format("%s  %s",m_Data.Mid(i*L+63,8),m_Data.Mid(i*L+71,7));
		m_LIST1.SetCol(8);	m_LIST1.SetText(str1);

		m_LIST1.SetCol(10);	m_LIST1.SetText(affected_CTRY[i]);
		m_LIST1.SetCol(9);	m_LIST1.SetText(m_Data.Mid(i*L+79,3));

		m_LIST1.SetCol(11);	m_LIST1.SetText(m_Data.Mid(i*L+82,8));
		m_LIST1.SetCol(12);	m_LIST1.SetText(m_Data.Mid(i*L+90,8));

		fscanf( fptemp, "%s  %s  %s", dum1,dum2,dum3);
		m_LIST1.SetCol(5);	m_LIST1.SetText(dum2);
		m_LIST1.SetCol(13);	m_LIST1.SetText(dum1);
		m_LIST1.SetCol(14);	m_LIST1.SetText(dum3);
	}
		
	fclose(fptemp);

	CFont font ;
    if (!(HFONT)font)
	{
        LOGFONT lf;
		GetFont()->GetObject(sizeof(lf), &lf);
//		lf.lfHeight = 10;
//		lf.lfWeight = FW_BOLD;
		strcpy(lf.lfFaceName , "Times");
        font.CreateFontIndirect(&lf);

		GetDlgItem(IDC_CHECK_M1)   ->SetFont(&font);
		GetDlgItem(IDC_CHECK_M2)   ->SetFont(&font);
		GetDlgItem(IDC_CHECK_M1_10)->SetFont(&font);
		GetDlgItem(IDC_CHECK_M1_20)->SetFont(&font);
		GetDlgItem(IDC_CHECK_M1_30)->SetFont(&font);
		GetDlgItem(IDC_CHECK_M1_40)->SetFont(&font);
		GetDlgItem(IDC_CHECK_M1_50)->SetFont(&font);
		GetDlgItem(IDC_CHECK_M1_60)->SetFont(&font);
		GetDlgItem(IDC_CHECK_all)  ->SetFont(&font);
    }
	font.DeleteObject();

	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

HBRUSH CAP7_CordContourDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (  pWnd->GetDlgCtrlID() == IDC_CHECK_M1		||
		  pWnd->GetDlgCtrlID() == IDC_CHECK_M2		||
		  pWnd->GetDlgCtrlID() == IDC_CHECK_M1_10	||
		  pWnd->GetDlgCtrlID() == IDC_CHECK_M1_20	||
		  pWnd->GetDlgCtrlID() == IDC_CHECK_M1_30	||
		  pWnd->GetDlgCtrlID() == IDC_CHECK_M1_40	||
		  pWnd->GetDlgCtrlID() == IDC_CHECK_M1_50	||
		  pWnd->GetDlgCtrlID() == IDC_CHECK_M1_60	)
	{
		if(!m_All)
		{
			CFont font ;
			if (!(HFONT)font)
			{
				LOGFONT lf;
				GetFont()->GetObject(sizeof(lf), &lf);
				lf.lfHeight = 16;
				lf.lfWeight = FW_BOLD;
				strcpy(lf.lfFaceName , "Times");
				font.CreateFontIndirect(&lf);
			}
			pDC->SelectObject(&font);
			pDC->SetTextColor(RGB(0,0,255));
			font.DeleteObject();
		}
	}

	if (  pWnd->GetDlgCtrlID() == IDC_CHECK_all)
	{
		CFont font ;
		if (!(HFONT)font)
		{
			LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfHeight = 16;
			lf.lfWeight = FW_BOLD;
			strcpy(lf.lfFaceName , "Times");
			font.CreateFontIndirect(&lf);
		}
		pDC->SelectObject(&font);
		font.DeleteObject();
	}

	return hbr;
}

void CAP7_CordContourDLG::OnOK() 
{
	UpdateData();
	m_NRow = m_LIST1.GetRow();
	m_NRowsel = m_LIST1.GetRowSel();
	UpdateData(false);
	
	CDialog::OnOK();
}

void CAP7_CordContourDLG::OnCHECKall() 
{
	UpdateData();

	CButton *xx;
	if(m_All)
	{
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1);		xx->SetCheck(true);	xx->EnableWindow(false);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M2);		xx->SetCheck(true);	xx->EnableWindow(false);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_10);	xx->SetCheck(true);	xx->EnableWindow(false);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_20);	xx->SetCheck(true);	xx->EnableWindow(false);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_30);	xx->SetCheck(true);	xx->EnableWindow(false);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_40);	xx->SetCheck(true);	xx->EnableWindow(false);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_50);	xx->SetCheck(true);	xx->EnableWindow(false);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_60);	xx->SetCheck(true);	xx->EnableWindow(false);
	}
	else
	{
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1);		xx->EnableWindow(true);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M2);		xx->EnableWindow(true);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_10);	xx->EnableWindow(true);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_20);	xx->EnableWindow(true);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_30);	xx->EnableWindow(true);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_40);	xx->EnableWindow(true);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_50);	xx->EnableWindow(true);
		xx = (CButton *)GetDlgItem(IDC_CHECK_M1_60);	xx->EnableWindow(true);
	}
//	UpdateData(false);	
}
