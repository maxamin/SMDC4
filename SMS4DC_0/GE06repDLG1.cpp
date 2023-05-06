// GE06repDLG1.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "GE06repDLG1.h"
#include "HTML_Report.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGE06repDLG1 dialog


CGE06repDLG1::CGE06repDLG1(CWnd* pParent /*=NULL*/)
	: CDialog(CGE06repDLG1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGE06repDLG1)
	m_Google = FALSE;
	//}}AFX_DATA_INIT
	m_rowsX = 2;
	m_title1 = _Z("GE06 BC-BT to BC-BT - Affected Administrations");
	m_title2 = _Z("Assignment/Allotment :");
	m_title3 = _Z("Affected Administrations :");
	m_mode = 0;
	m_Bdisplay = 1;
	m_GoogleFlag = FALSE;
}


void CGE06repDLG1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGE06repDLG1)
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_LIST1);
	DDX_Control(pDX, IDC_MSFLEXGRID2, m_LIST2);
	DDX_Check(pDX, IDC_CHECK_Google, m_Google);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGE06repDLG1, CDialog)
	//{{AFX_MSG_MAP(CGE06repDLG1)
	ON_BN_CLICKED(IDC_Report, OnReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGE06repDLG1 message handlers

BOOL CGE06repDLG1::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(m_title1);
	CStatic* xx1;	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_list1);	xx1->SetWindowText(m_title2);
	CStatic* xx2;	xx2 = (CStatic*)GetDlgItem(IDC_STATIC_list2);	xx2->SetWindowText(m_title3);
	CButton* xx3;	xx3 = (CButton*)GetDlgItem(IDOK);				xx3->ShowWindow(m_Bdisplay);
	CButton* xx4;	xx4 = (CButton*)GetDlgItem(IDC_CHECK_Google);	xx4->ShowWindow(m_GoogleFlag);

	switch( m_mode ) 
	{
	   case 0:{
				int nCOLS = 14;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,800);
				m_LIST1.SetColWidth(2,1300);
				m_LIST1.SetColWidth(3,1300);
				m_LIST1.SetColWidth(4,1200);
				m_LIST1.SetColWidth(5,1400);
				m_LIST1.SetColWidth(6,1200);
				m_LIST1.SetColWidth(7,600);
				m_LIST1.SetColWidth(8,600);
				m_LIST1.SetColWidth(10,1900);
				m_LIST1.SetColWidth(11,1100);
				m_LIST1.SetColWidth(12,2200);
				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(" ");
				m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("AS/AL"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("NoticeType"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("PlanEntryCode"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("AssignCode"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(12);		m_LIST1.SetText(_Z("Associated-Adm-Allot-ID"));
				m_LIST1.SetCol(13);		m_LIST1.SetText(_Z("SFN-ID"));
				m_LIST1.SetRowHeight(0,400);
				m_dataX1 = m_dataX;		m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					if(j==0)		ResultSTR.Format("%s",_T("W"));
					else			ResultSTR.Format("%s",_T("L"));	//		ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
				nCOLS = 4; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(3,2800);
				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Trigger Field Strength (dBuV/m)"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);
				}
			  }break;	//case 0
	   case 1:{
				int nCOLS = 14;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,800);
				m_LIST1.SetColWidth(2,1300);
				m_LIST1.SetColWidth(3,1300);
				m_LIST1.SetColWidth(4,1200);
				m_LIST1.SetColWidth(5,1400);
				m_LIST1.SetColWidth(6,1200);
				m_LIST1.SetColWidth(7,600);
				m_LIST1.SetColWidth(8,600);
				m_LIST1.SetColWidth(10,1900);
				m_LIST1.SetColWidth(11,1100);
				m_LIST1.SetColWidth(12,2200);
				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(" ");
				m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("AS/AL"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("NoticeType"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("PlanEntryCode"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("AssignCode"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(12);		m_LIST1.SetText(_Z("Associated-Adm-Allot-ID"));
				m_LIST1.SetCol(13);		m_LIST1.SetText(_Z("SFN-ID"));
				m_LIST1.SetRowHeight(0,400);
				m_dataX1 = m_dataX;		m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					if(j==0)		ResultSTR.Format("%s",_T("W"));
					else			ResultSTR.Format("%s",_T("L"));	//		ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
				nCOLS = 12 ;
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,1000);
				m_LIST2.SetColWidth(3,600);
				m_LIST2.SetColWidth(4,600);
				m_LIST2.SetColWidth(6,700);
				m_LIST2.SetColWidth(7,1900);
				m_LIST2.SetColWidth(10,2800);
				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("IDst"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("Affected Station"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Freq_terr"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Cls_stn"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Location"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("SysType1"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("SysType2"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Trigger Field Strength (dBuV/m)"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("hR (m)"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
						m_LIST2.SetCol(10);
						m_LIST2.SetCellAlignment(1);
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);
				}
			  }break;	//case 1
	   case 2:{
				int nCOLS = 12;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,1300);
				m_LIST1.SetColWidth(2,1300);
				m_LIST1.SetColWidth(3,1300);
				m_LIST1.SetColWidth(4,1200);
				m_LIST1.SetColWidth(5,600);
				m_LIST1.SetColWidth(6,600);
				m_LIST1.SetColWidth(8,1900);
				m_LIST1.SetColWidth(9,1000);
				m_LIST1.SetColWidth(10,1200);
				m_LIST1.SetColWidth(11,1200);
				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("Stn Class"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Stn Type"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Band Width (kHz)"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Power (dBwERP)"));
				m_LIST1.SetRowHeight(0,400);
				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
				nCOLS = 5; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(3,2800);
				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Trigger Field Strength (dBuV/m)"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("hR (m)"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);
				}
			  }break;	//case 2
	   case 3:{
				int nCOLS = 13;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,1300);
				m_LIST1.SetColWidth(2,1300);
				m_LIST1.SetColWidth(3,1300);
				m_LIST1.SetColWidth(4,1200);
				m_LIST1.SetColWidth(5,600);
				m_LIST1.SetColWidth(6,600);
				m_LIST1.SetColWidth(8,1900);
				m_LIST1.SetColWidth(9,1000);
				m_LIST1.SetColWidth(10,1200);
				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("Stn Class"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Stn Type"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Band Width (kHz)"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Sys Type1"));
				m_LIST1.SetCol(12);		m_LIST1.SetText(_Z("Sys Type2"));
				m_LIST1.SetRowHeight(0,400);
				m_dataX1 = m_dataX;		m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
				nCOLS = 6; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(3,2800);
				m_LIST2.SetColWidth(5,2000);
				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Trigger Field Strength (dBuV/m)"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("hR (m)"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Assumed BC-BT Station"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);
				}
			  }break;	//case 3
	   case 4:{
				int nCOLS = 15;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(11,1900);
				m_LIST1.SetColWidth(12,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_T("W/L"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("AS/AL"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Notice Type"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Plan Entry Code"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Assign Code"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(12);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(13);		m_LIST1.SetText(_Z("Associated-Adm-Allot-ID"));
				m_LIST1.SetCol(14);		m_LIST1.SetText(_Z("SFN-ID"));
				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 17; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(9,1900);
				m_LIST2.SetColWidth(10,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Plan Entry Code"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Assign Code"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("PMmin TP Location"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("SFN-ID"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("EmedW"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("CNFSmax"));
				m_LIST2.SetCol(15);		m_LIST2.SetText(_Z("PMmin"));
				m_LIST2.SetCol(16);		m_LIST2.SetText(_Z("PMlimit"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,15))  <  atof(m_LIST2.GetTextMatrix(j+1,16))  )
						{
							m_LIST2.SetCol(15);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 4
	   case 5:{
				int nCOLS = 15;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(11,1900);
				m_LIST1.SetColWidth(12,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_T("W/L"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("AS/AL"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Notice Type"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Plan Entry Code"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Assign Code"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(12);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(13);		m_LIST1.SetText(_Z("Associated-Adm-Allot-ID"));
				m_LIST1.SetCol(14);		m_LIST1.SetText(_Z("SFN-ID"));
				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 15; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(7,1900);
				m_LIST2.SetColWidth(8,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Margin max TP Location"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("EmW"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("UFS"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("NFS"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("Margin max"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("Margin limit"));

				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,13))  >  atof(m_LIST2.GetTextMatrix(j+1,14))  )
						{
							m_LIST2.SetCol(13);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 5
	   case 6:{
				int nCOLS = 10;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(7,1900);
				m_LIST1.SetColWidth(8,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("IDst"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Cls-stn"));

				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 17; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(9,1900);
				m_LIST2.SetColWidth(10,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Plan Entry Code"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Assign Code"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("PMmin TP Location"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("SFN-ID"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("EmedW"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("CNFSmax"));
				m_LIST2.SetCol(15);		m_LIST2.SetText(_Z("PMmin"));
				m_LIST2.SetCol(16);		m_LIST2.SetText(_Z("PMlimit"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,15))  <  atof(m_LIST2.GetTextMatrix(j+1,16))  )
						{
							m_LIST2.SetCol(15);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 6
	   case 7:{
				int nCOLS = 10;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(7,1900);
				m_LIST1.SetColWidth(8,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("IDst"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Cls-stn"));

				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 15; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(7,1900);
				m_LIST2.SetColWidth(8,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Margin max TP Location"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("EmW"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("UFS"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("NFS"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("Margin max"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("Margin limit"));

				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,13))  >  atof(m_LIST2.GetTextMatrix(j+1,14))  )
						{
							m_LIST2.SetCol(13);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 7
	   case 8:{
				int nCOLS = 15;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(11,1900);
				m_LIST1.SetColWidth(12,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_T("W/L"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("AS/AL"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Notice Type"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Plan Entry Code"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Assign Code"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(12);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(13);		m_LIST1.SetText(_Z("Associated-Adm-Allot-ID"));
				m_LIST1.SetCol(14);		m_LIST1.SetText(_Z("SFN-ID"));
				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 15; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(6,1900);
				m_LIST2.SetColWidth(7,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("PMmin TP Location"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("SysType1"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("SysType2"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("Emin,E"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("NFSmax, INTFSmax"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("PMmin, (E-INTFS)min"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("Limit"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,13))  <  atof(m_LIST2.GetTextMatrix(j+1,14))  )
						{
							m_LIST2.SetCol(13);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 8
	   case 9:{
				int nCOLS = 15;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(11,1900);
				m_LIST1.SetColWidth(12,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_T("W/L"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("AS/AL"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Notice Type"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Plan Entry Code"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Assign Code"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(12);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(13);		m_LIST1.SetText(_Z("Associated-Adm-Allot-ID"));
				m_LIST1.SetCol(14);		m_LIST1.SetText(_Z("SFN-ID"));
				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 19; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(3,600);
				m_LIST2.SetColWidth(4,600);
				m_LIST2.SetColWidth(11,1900);
				m_LIST2.SetColWidth(12,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_T("W/L"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("AS/AL"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Plan Entry Code"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("Assign Code"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("PMmin TP Location"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("SFN-ID"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(15);		m_LIST2.SetText(_Z("EmedW"));
				m_LIST2.SetCol(16);		m_LIST2.SetText(_Z("CNFSmax"));
				m_LIST2.SetCol(17);		m_LIST2.SetText(_Z("PMmin"));
				m_LIST2.SetCol(18);		m_LIST2.SetText(_Z("PMlimit"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,17))  <  atof(m_LIST2.GetTextMatrix(j+1,18))  )
						{
							m_LIST2.SetCol(17);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 9
	   case 10:{
				int nCOLS = 11;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(9,1900);
				m_LIST1.SetColWidth(10,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_T("W/L"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("AS/AL"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Notice Type"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 20; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(3,600);
				m_LIST2.SetColWidth(4,600);
				m_LIST2.SetColWidth(11,1900);
				m_LIST2.SetColWidth(12,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_T("W/L"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("AS/AL"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Plan Entry Code"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("Assign Code"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("Margin max TP Location"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("SFN-ID"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(15);		m_LIST2.SetText(_Z("EmW"));
				m_LIST2.SetCol(16);		m_LIST2.SetText(_Z("UFS"));
				m_LIST2.SetCol(17);		m_LIST2.SetText(_Z("NFS"));
				m_LIST2.SetCol(18);		m_LIST2.SetText(_Z("Margin max"));
				m_LIST2.SetCol(19);		m_LIST2.SetText(_Z("Margin limit"));
				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,18))  >  atof(m_LIST2.GetTextMatrix(j+1,19))  )
						{
							m_LIST2.SetCol(18);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 10
	   case 11:{
				int nCOLS = 15;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(11,1900);
				m_LIST1.SetColWidth(12,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_T("W/L"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("AS/AL"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Notice Type"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Plan Entry Code"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Assign Code"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(12);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(13);		m_LIST1.SetText(_Z("Associated-Adm-Allot-ID"));
				m_LIST1.SetCol(14);		m_LIST1.SetText(_Z("SFN-ID"));
				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 16; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(3,600);
				m_LIST2.SetColWidth(4,600);
				m_LIST2.SetColWidth(9,1900);
				m_LIST2.SetColWidth(10,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("IDst"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Cls-stn"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("PMmin TP Location"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("EmedW"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("CNFSmax"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("PMmin"));
				m_LIST2.SetCol(15);		m_LIST2.SetText(_Z("PMlimit"));

				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,14))  <  atof(m_LIST2.GetTextMatrix(j+1,15))  )
						{
							m_LIST2.SetCol(14);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 11
	   case 12:{
				int nCOLS = 10;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(4,600);
				m_LIST1.SetColWidth(8,1900);
				m_LIST1.SetColWidth(9,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("IDst"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("Notice Type"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 17; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(9,1900);
				m_LIST2.SetColWidth(10,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_Z("IDst"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Cls-stn"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("Margin max TP Location"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("EmW"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("UFS"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("NFS"));
				m_LIST2.SetCol(15);		m_LIST2.SetText(_Z("Margin max"));
				m_LIST2.SetCol(16);		m_LIST2.SetText(_Z("Margin limit"));

				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,15))  >  atof(m_LIST2.GetTextMatrix(j+1,16))  )
						{
							m_LIST2.SetCol(15);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 12
	   case 13:{
				int nCOLS = 12;
				m_LIST1.SetCols(nCOLS);
				m_LIST1.SetColWidth(0,400);
				m_LIST1.SetColWidth(1,600);
				m_LIST1.SetColWidth(2,600);
				m_LIST1.SetColWidth(3,600);
				m_LIST1.SetColWidth(8,1900);
				m_LIST1.SetColWidth(9,1000);

				m_LIST1.SetRow(0);
				m_LIST1.SetCol(0);		m_LIST1.SetText(_Z("No."));
				m_LIST1.SetCol(1);		m_LIST1.SetText(_Z("IDst"));
				m_LIST1.SetCol(2);		m_LIST1.SetText(_Z("ADM"));
				m_LIST1.SetCol(3);		m_LIST1.SetText(_Z("CTRY"));
				m_LIST1.SetCol(4);		m_LIST1.SetText(_Z("Name"));
				m_LIST1.SetCol(5);		m_LIST1.SetText(_T("ADM_REF_ID"));
				m_LIST1.SetCol(6);		m_LIST1.SetText(_Z("Notice Type"));
				m_LIST1.SetCol(7);		m_LIST1.SetText(_Z("Frq(MHz)"));
				m_LIST1.SetCol(8);		m_LIST1.SetText(_Z("Location"));
				m_LIST1.SetCol(9);		m_LIST1.SetText(_Z("Polarization"));
				m_LIST1.SetCol(10);		m_LIST1.SetText(_Z("Sys Type1"));
				m_LIST1.SetCol(11);		m_LIST1.SetText(_Z("Sys Type2"));
				m_LIST1.SetRowHeight(0,400);

				m_dataX1 = m_dataX;			m_dataY1 = m_dataY;
				int n;
				CString ResultSTR;
				m_LIST1.SetRows(m_rowsX);
				for(int j=0;j<m_rowsX-1;j++)
				{
					m_LIST1.SetRow(j+1);
					m_LIST1.SetCol(0);
					ResultSTR.Format("%d",j+1);
					m_LIST1.SetText(ResultSTR);
					for(int i=0;i<nCOLS-1;i++)
					{
						n = m_dataX.Find(',',0);
						ResultSTR = m_dataX.Left(n);
						m_dataX = m_dataX.Mid(n+1);
						m_LIST1.SetCol(i+1);
						m_LIST1.SetText(ResultSTR);
					}
				}
				m_LIST1.SetCol(nCOLS-1);
				m_LIST1.SetText(m_dataX);
			
				nCOLS = 19; 
 				m_LIST2.SetRows(m_rowsY);
				m_LIST2.SetCols(nCOLS);
				m_LIST2.SetColWidth(0,400);
				m_LIST2.SetColWidth(1,600);
				m_LIST2.SetColWidth(2,600);
				m_LIST2.SetColWidth(11,1900);
				m_LIST2.SetColWidth(12,1000);

				m_LIST2.SetRowHeight(0,400);
				m_LIST2.SetRow(0);
				m_LIST2.SetCol(0);		m_LIST2.SetText(_Z("No."));
				m_LIST2.SetCol(1);		m_LIST2.SetText(_T("W/L"));
				m_LIST2.SetCol(2);		m_LIST2.SetText(_Z("AS/AL"));
				m_LIST2.SetCol(3);		m_LIST2.SetText(_Z("ADM"));
				m_LIST2.SetCol(4);		m_LIST2.SetText(_Z("CTRY"));
				m_LIST2.SetCol(5);		m_LIST2.SetText(_Z("Name"));
				m_LIST2.SetCol(6);		m_LIST2.SetText(_T("ADM_REF_ID"));
				m_LIST2.SetCol(7);		m_LIST2.SetText(_Z("Notice Type"));
				m_LIST2.SetCol(8);		m_LIST2.SetText(_Z("Plan Entry Code"));
				m_LIST2.SetCol(9);		m_LIST2.SetText(_Z("Assign Code"));
				m_LIST2.SetCol(10);		m_LIST2.SetText(_Z("Frq(MHz)"));
				m_LIST2.SetCol(11);		m_LIST2.SetText(_Z("PMmin TP Location"));
				m_LIST2.SetCol(12);		m_LIST2.SetText(_Z("Polarization"));
				m_LIST2.SetCol(13);		m_LIST2.SetText(_Z("SFN-ID"));
				m_LIST2.SetCol(14);		m_LIST2.SetText(_Z("L%"));
				m_LIST2.SetCol(15);		m_LIST2.SetText(_Z("Emin,E"));
				m_LIST2.SetCol(16);		m_LIST2.SetText(_Z("NFSmax, INTFSmax"));
				m_LIST2.SetCol(17);		m_LIST2.SetText(_Z("PMmin, (E-INTFS)min"));
				m_LIST2.SetCol(18);		m_LIST2.SetText(_Z("Limit"));

				if(m_rowsY>1)
				{
					for(long j=0;j<m_rowsY-1;j++)
					{
						m_LIST2.SetRow(j+1);
						m_LIST2.SetCol(0);
						ResultSTR.Format("%d",j+1);
						m_LIST2.SetText(ResultSTR);
						for(int i=0;i<nCOLS-1;i++)
						{
							n = m_dataY.Find(',',0);
							ResultSTR = m_dataY.Left(n);
							m_dataY = m_dataY.Mid(n+1);
							m_LIST2.SetCol(i+1);
							m_LIST2.SetText(ResultSTR);
						}
					}
					m_LIST2.SetCol(nCOLS-1);
					m_LIST2.SetText(m_dataY);

					for(j=0;j<m_rowsY-1;j++)
					{
						if(   atof(m_LIST2.GetTextMatrix(j+1,17))  <  atof(m_LIST2.GetTextMatrix(j+1,18))  )
						{
							m_LIST2.SetCol(17);		m_LIST2.SetRow(j+1);
							m_LIST2.SetCellBackColor(RGB(255,150,150));
						}
					}
				}
			 }break;	//case 13

	}//switch
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}


void CGE06repDLG1::OnReport() 
{
	CString m_dataX2 = m_dataX1;
	CString m_dataY2 = m_dataY1;
	switch( m_mode ) 
	{
	   case 0:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[14];

			//		m_dataX1 = m_dataX1 + _T(","); m_dataY1 = m_dataY1 + _T(",");
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 14;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, " ",_Z("AS/AL"),_Z("Name"),_T("ADM_REF_ID"),_Z("NoticeType"),_Z("PlanEntryCode"),_Z("AssignCode"),_Z("CTRY"),_Z("ADM"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Associated-Adm-Allot-ID"),_Z("SFN-ID"));
				
					for( j = 1; iRow>1; j++)
					{
						if(j==1)	ResultSTR.Format("%s",_T("W"));
						else		ResultSTR.Format("%s",_T("L"));		//		ResultSTR.Format("%d",j);

						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 4;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."), _Z("CTRY"),_Z("ADM"), _Z("Trigger Field Strength (dBuV/m)"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3]);
						iRow--;
					}

					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			  }break;	//case 0 
		case 1:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[14];

		//			m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 14;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, " ",_Z("AS/AL"),_Z("Name"),_T("ADM_REF_ID"),_Z("NoticeType"),_Z("PlanEntryCode"),_Z("AssignCode"),_Z("CTRY"),_Z("ADM"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Associated-Adm-Allot-ID"),_Z("SFN-ID"));
				
					for( j = 1; iRow>1; j++)
					{
						if(j==1)		ResultSTR.Format("%s",_T("W"));
						else			ResultSTR.Format("%s",_T("L"));		//		ResultSTR.Format("%d",j);

						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 12;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("IDst"),_Z("Affected Station"), _Z("CTRY"),_Z("ADM"),_Z("Freq_terr"),_Z("Cls_stn"),_Z("Location"),_Z("SysType1"),_Z("SysType2") ,_Z("Trigger Field Strength (dBuV/m)"),_Z("hR (m)"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11]);
						iRow--;
					}

					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 1
		case 2:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[12];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 12;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_Z("Name"),_T("ADM_REF_ID"),_Z("Stn Class"),_Z("Stn Type"),_Z("CTRY"),_Z("ADM"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Band Width (kHz)"),_Z("Power (dBwERP)"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 5;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("CTRY"),_Z("ADM"),_Z("Trigger Field Strength (dBuV/m)"),_Z("hR (m)"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4]);
						iRow--;
					}

					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 2
		case 3:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[13];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 13;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_Z("Name"),_T("ADM_REF_ID"),_Z("Stn Class"),_Z("Stn Type"),_Z("CTRY"),_Z("ADM"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Band Width (kHz)"),_Z("Sys Type1"),_Z("Sys Type2"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 6;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("CTRY"),_Z("ADM"),_Z("Trigger Field Strength (dBuV/m)"),_Z("hR (m)"),_Z("Assumed BC-BT Station"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 3
		case 4:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[17];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 15;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Associated-Adm-Allot-ID"),_Z("SFN-ID"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 17;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("PMmin TP Location"),_Z("Polarization"),_Z("SFN-ID"),_Z("L%"),_Z("EmedW"),_Z("CNFSmax"),_Z("PMmin"),_Z("PMlimit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14], sCELL[15], sCELL[16]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 4
		case 5:{
				CFileDialog oFileDlg(FALSE, _T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[15];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 15;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Associated-Adm-Allot-ID"),_Z("SFN-ID"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 15;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Frq(MHz)"),_Z("Margin max TP Location"),_Z("Polarization"),_Z("L%"),_Z("EmW"),_Z("UFS"),_Z("NFS"),_Z("Margin max"),_Z("Margin limit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 5
		case 6:{
				CFileDialog oFileDlg(FALSE, _T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[17];

		//			m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 10;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_Z("IDst"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Cls-stn"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 17;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("PMmin TP Location"),_Z("Polarization"),_Z("SFN-ID"),_Z("L%"),_Z("EmedW"),_Z("CNFSmax"),_Z("PMmin"),_Z("PMlimit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14], sCELL[15], sCELL[16]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 6
		case 7:{
				CFileDialog oFileDlg(FALSE, _T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[15];

		//			m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 10;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_Z("IDst"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Cls-stn"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 15;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Frq(MHz)"),_Z("Margin max TP Location"),_Z("Polarization"),_Z("L%"),_Z("EmW"),_Z("UFS"),_Z("NFS"),_Z("Margin max"),_Z("Margin limit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 7
		case 8:{
				CFileDialog oFileDlg(FALSE, _T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[15];

		//			m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 15;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Associated-Adm-Allot-ID"),_Z("SFN-ID"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 15;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Frq(MHz)"),_Z("PMmin TP Location"),_Z("Polarization"),_Z("SysType1"),_Z("SysType2"),_Z("L%"),_Z("Emin,E"),_Z("NFSmax, INTFSmax"),_Z("PMmin, (E-INTFS)min"),_Z("Limit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 8
		case 9:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[19];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 15;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Associated-Adm-Allot-ID"),_Z("SFN-ID"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 19;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("PMmin TP Location"),_Z("Polarization"),_Z("SFN-ID"),_Z("L%"),_Z("EmedW"),_Z("CNFSmax"),_Z("PMmin"),_Z("PMlimit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14], sCELL[15], sCELL[16], sCELL[17], sCELL[18]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 9
		case 10:{
				CFileDialog oFileDlg(FALSE, _T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[20];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 11;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 20;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("Margin max TP Location"),_Z("Polarization"),_Z("SFN-ID"),_Z("L%"),_Z("EmW"),_Z("UFS"),_Z("NFS"),_Z("Margin max"),_Z("Margin limit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14], sCELL[15], sCELL[16], sCELL[17], sCELL[18], sCELL[19]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 10
		case 11:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[16];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 15;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Associated-Adm-Allot-ID"),_Z("SFN-ID"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 16;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("IDst"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Cls-stn"),_Z("Frq(MHz)"),_Z("PMmin TP Location"),_Z("Polarization"),_Z("L%"),_Z("EmedW"),_Z("CNFSmax"),_Z("PMmin"),_Z("PMlimit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14], sCELL[15]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 11
		case 12:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[17];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 10;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_Z("IDst"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 17;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_Z("IDst"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Cls-stn"),_Z("Frq(MHz)"),_Z("Margin max TP Location"),_Z("Polarization"),_Z("L%"),_Z("EmW"),_Z("UFS"),_Z("NFS"),_Z("Margin max"),_Z("Margin limit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14], sCELL[15], sCELL[16]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 12
		case 13:{
				CFileDialog oFileDlg(FALSE,	_T("html"), _T("OutPutFile"), 
									OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT, 
									_Z("HTML Files")+" (*.html)|*.html|", this );
				CString str = _Z("Save HTML file as...");
				oFileDlg.m_ofn.lpstrTitle = str;
				if (oFileDlg.DoModal() == IDOK)
				{
					CString sFile, ResultSTR, sCELL[19];

			//		m_dataX1 = m_dataX1+","; m_dataY1 = m_dataY1+",";
					m_dataX2 = m_dataX2 + _T(","); m_dataY2 = m_dataY2 + _T(",");

					int i, j, n , iRow = m_rowsX, iCol = 12;
					sFile = oFileDlg.GetFileName();
					CHTML_Report HtmlReport(FALSE, "OutPut HTML","Behzad Paknahad",m_title2,m_title1);
					HtmlReport.InsertTableHeader(iCol, _Z("No."),_Z("IDst"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Frq(MHz)"),_Z("Location"),_Z("Polarization"),_Z("Sys Type1"),_Z("Sys Type2"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataX2.Find(',',0);
							ResultSTR = m_dataX2.Left(n);
							m_dataX2 = m_dataX2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11]);
						iRow--;
					}
					HtmlReport.WriteHTMLFile(sFile);

					iRow = m_rowsY, iCol = 19;
					CHTML_Report HtmlReport1(TRUE, "OutPut HTML","Behzad Paknahad",m_title3);
					HtmlReport1.InsertTableHeader(iCol, _Z("No."),_T("W/L"),_Z("AS/AL"),_Z("ADM"),_Z("CTRY"),_Z("Name"),_T("ADM_REF_ID"),_Z("Notice Type"),_Z("Plan Entry Code"),_Z("Assign Code"),_Z("Frq(MHz)"),_Z("PMmin TP Location"),_Z("Polarization"),_Z("SFN-ID"),_Z("L%"),_Z("Emin,E"),_Z("NFSmax, INTFSmax"),_Z("PMmin, (E-INTFS)min"),_Z("Limit"));

					for( j = 1; iRow>1; j++)
					{
						ResultSTR.Format("%d",j);
						sCELL[0] = ResultSTR;
						for( i=0;i<iCol-1;i++)
						{
							n = m_dataY2.Find(',',0);
							ResultSTR = m_dataY2.Left(n);
							m_dataY2 = m_dataY2.Mid(n+1);
							sCELL[i+1] = ResultSTR;
						}
						HtmlReport1.InsertTableRow(sCELL[0], sCELL[1], sCELL[2], sCELL[3], sCELL[4], sCELL[5], sCELL[6], sCELL[7], sCELL[8], sCELL[9], sCELL[10], sCELL[11], sCELL[12], sCELL[13], sCELL[14], sCELL[15], sCELL[16], sCELL[17], sCELL[18]);
						iRow--;
					}
					CString FileInfo =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\temp.tmp");
					HtmlReport1.WriteHTMLFile(FileInfo);
					int m_num = HtmlReport1.m_num;

					FILE *stream, *stream1;
					char *list; list = new char[m_num];
					if((stream = fopen(FileInfo, "rt")) != NULL)
					{
						fread( list, sizeof( char ), m_num, stream );
						fclose( stream );
					}
					if((stream1 = fopen(sFile, "at")) != NULL)
					{
						fwrite(list, sizeof(char), m_num, stream1);
						fclose( stream1 );
					}
					delete [] list;

					ShellExecute(m_hWnd, "open", sFile, NULL, NULL, SW_SHOWNORMAL);
				}	
			   }break;	//case 13
	}//switch
}
