// P530RefPointsDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "P530RefPointsDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CP530RefPointsDLG dialog


CP530RefPointsDLG::CP530RefPointsDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CP530RefPointsDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP530RefPointsDLG)
	m_data = _T("");
	m_nROWS = 0;
	//}}AFX_DATA_INIT
}


void CP530RefPointsDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP530RefPointsDLG)
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_List1);
	DDX_Text(pDX, IDC_EDIT_data, m_data);
	DDX_Text(pDX, IDC_EDIT_rows, m_nROWS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP530RefPointsDLG, CDialog)
	//{{AFX_MSG_MAP(CP530RefPointsDLG)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP530RefPointsDLG message handlers

BOOL CP530RefPointsDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int nCOLS = 7;
	m_List1.SetCols(nCOLS);
	m_List1.SetColWidth(0,400);
	m_List1.SetColWidth(1,2000);
	m_List1.SetColWidth(2,1400);
	m_List1.SetColWidth(3,1400);
	m_List1.SetColWidth(4,1400);
	m_List1.SetColWidth(5,1000);
	m_List1.SetColWidth(6,1600);

	m_List1.SetRow(0);
	m_List1.SetCol(0);
	m_List1.SetText("No");
	m_List1.SetCol(1);
	m_List1.SetText(_Z("Coordinates"));
	m_List1.SetCol(2);
	m_List1.SetText(_Z("Distance(km) : d1"));
	m_List1.SetCol(3);
	m_List1.SetText(_Z("Distance(km) : d2"));
	m_List1.SetCol(4);
	m_List1.SetText(_Z("Height_ASL(m)"));
	m_List1.SetCol(5);
	m_List1.SetText(_Z("Delta_R(km)"));
	m_List1.SetCol(6);
	m_List1.SetText(_Z("Grazing Angle(Deg.)"));

	m_List1.SetRows(m_nROWS+1);

	CString ResultSTR;
	int n;

	for(int j=0;j<m_nROWS;j++)
	{
		m_List1.SetRow(j+1);
		m_List1.SetCol(0);
		ResultSTR.Format("%d",j+1);
		m_List1.SetText(ResultSTR);

		for(int i=0;i<nCOLS-1;i++)
		{
			n = m_data.Find(',',0);
			ResultSTR = m_data.Left(n);
			m_data = m_data.Mid(n+1);
			m_List1.SetCol(i+1);
			m_List1.SetText(ResultSTR);
		}
	}
	m_List1.SetColAlignment(0,4);
	m_List1.SetColAlignment(1,4);
	m_List1.SetColAlignment(2,4);
	m_List1.SetColAlignment(3,4);
	m_List1.SetColAlignment(4,4);
	m_List1.SetColAlignment(5,4);
	m_List1.SetColAlignment(6,4);
	
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

HBRUSH CP530RefPointsDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (  pWnd->GetDlgCtrlID() == IDC_EDIT_rows  )
	{
		CFont font ;
        if (!(HFONT)font)
		{
            LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfHeight = 16;
			lf.lfWeight = FW_BOLD;
			strcpy(lf.lfFaceName , "Arial");
            font.CreateFontIndirect(&lf);
        }
        pDC->SelectObject(&font);
		font.DeleteObject();
	}
	return hbr;
}
