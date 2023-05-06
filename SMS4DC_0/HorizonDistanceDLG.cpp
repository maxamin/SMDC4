// HorizonDistanceDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "HorizonDistanceDLG.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHorizonDistanceDLG dialog


CHorizonDistanceDLG::CHorizonDistanceDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CHorizonDistanceDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHorizonDistanceDLG)
	m_HA = 0.0;
	m_HB = 0.0;
	m_K = _T("4/3");
	m_R = 6371.0;
	//}}AFX_DATA_INIT
}


void CHorizonDistanceDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHorizonDistanceDLG)
	DDX_Text(pDX, IDC_EDIT_HA, m_HA);
	DDV_MinMaxDouble(pDX, m_HA, 0., 1000000.);
	DDX_Text(pDX, IDC_EDIT_HB, m_HB);
	DDX_Text(pDX, IDC_EDIT_k, m_K);
	DDX_Text(pDX, IDC_EDIT_R, m_R);
	DDV_MinMaxDouble(pDX, m_R, 0., 1000000.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHorizonDistanceDLG, CDialog)
	//{{AFX_MSG_MAP(CHorizonDistanceDLG)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHorizonDistanceDLG message handlers

double CHorizonDistanceDLG::atof_kfactor(CString k1) 
{
	double k2 = 1.0;
	k1.Remove(' ');
	int n = k1.Find('/');
	if (n != -1)
	{
		int m = k1.GetLength();
		CString ss1 = k1.Left(n);
		CString ss2 = k1.Right(m-n-1);
		k2 = atof(ss1)/atof(ss2);
	}
	else
		k2 = atof(k1);

	return k2;
}

void CHorizonDistanceDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CPen pen(PS_SOLID,3,RGB(0,0,0));
	CPen* OLDpen = dc.SelectObject(&pen);

	int x0 = 176, y0 = 335, r0 = 150;

	dc.Arc(x0-r0,y0-r0,x0+r0,y0+r0, x0+r0,y0-r0,x0-r0,y0-r0);

	dc.MoveTo(x0-r0,y0-r0);
	dc.LineTo(x0,y0);
	dc.LineTo(x0,y0-r0);
	dc.MoveTo(x0,y0);
	dc.LineTo(x0+r0,y0-r0);

	CPen pen1(PS_DOT,1,RGB(255,0,0));
	dc.SelectObject(&pen1);
	dc.MoveTo(x0-r0,y0-r0);
	dc.LineTo(x0+r0,y0-r0);

	dc.SelectObject(OLDpen);
}

void CHorizonDistanceDLG::OnOK() 
{
	UpdateData();
	double re = m_R*1000.0*atof_kfactor(m_K);
	double da = sqrt( pow((re + m_HA),2.0)-pow(re,2.0) )/1000.0;	
	double db = sqrt( pow((re + m_HB),2.0)-pow(re,2.0) )/1000.0;

	CString str;
	str.Format("%0.3f",da); 
	CStatic* xx1 = (CStatic*)GetDlgItem(IDC_STATIC_DA0);
	xx1->SetWindowText(str);
	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_DA);
	xx1->SetWindowText(str);

	str.Format("%0.3f",db); 
	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_DB0);
	xx1->SetWindowText(str);
	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_DB);
	xx1->SetWindowText(str);

	str.Format("%0.3f",da+db); 
	xx1 = (CStatic*)GetDlgItem(IDC_STATIC_DAB);
	xx1->SetWindowText(str);
	UpdateData(false);

//	CDialog::OnOK();
}

BOOL CHorizonDistanceDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
