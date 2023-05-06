// P530availabilityDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "P530availabilityDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CP530availabilityDLG dialog


CP530availabilityDLG::CP530availabilityDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CP530availabilityDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP530availabilityDLG)
	m_MultiWMav = _T("");
	m_MultiWMoutS = _T("");
	m_MultiANav = _T("");
	m_MultiANoutM = _T("");
	m_MultiANoutS = _T("");
	m_MultiWMoutM = _T("");
	m_RainANav = _T("");
	m_RainANoutM = _T("");
	m_RainANoutS = _T("");
	m_RainWMav = _T("");
	m_RainWMoutM = _T("");
	m_RainWMoutS = _T("");
	//}}AFX_DATA_INIT
}


void CP530availabilityDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP530availabilityDLG)
	DDX_Text(pDX, IDC_EDIT_MultiWMav, m_MultiWMav);
	DDX_Text(pDX, IDC_EDIT_MultiWMoutS, m_MultiWMoutS);
	DDX_Text(pDX, IDC_EDIT_MultiANav, m_MultiANav);
	DDX_Text(pDX, IDC_EDIT_MultiANoutM, m_MultiANoutM);
	DDX_Text(pDX, IDC_EDIT_MultiANoutS, m_MultiANoutS);
	DDX_Text(pDX, IDC_EDIT_MultiWMoutM, m_MultiWMoutM);
	DDX_Text(pDX, IDC_EDIT_RainANav, m_RainANav);
	DDX_Text(pDX, IDC_EDIT_RainANoutM, m_RainANoutM);
	DDX_Text(pDX, IDC_EDIT_RainANoutS, m_RainANoutS);
	DDX_Text(pDX, IDC_EDIT_RainWMav, m_RainWMav);
	DDX_Text(pDX, IDC_EDIT_RainWMoutM, m_RainWMoutM);
	DDX_Text(pDX, IDC_EDIT_RainWMoutS, m_RainWMoutS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP530availabilityDLG, CDialog)
	//{{AFX_MSG_MAP(CP530availabilityDLG)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP530availabilityDLG message handlers

HBRUSH CP530availabilityDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (  pWnd->GetDlgCtrlID() == IDC_STATIC_Rain		||
		  pWnd->GetDlgCtrlID() == IDC_STATIC_MultiPath	)
	{
		CFont font ;
        if (!(HFONT)font)
		{
            LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfHeight = 18;
			lf.lfWeight = FW_BOLD;
			strcpy(lf.lfFaceName , "Times");
            font.CreateFontIndirect(&lf);
        }
        pDC->SelectObject(&font);
        pDC->SetTextColor(RGB(200,0,0));
		font.DeleteObject();
	}
	
	if (  pWnd->GetDlgCtrlID() == IDC_STATIC_WMM		||
		  pWnd->GetDlgCtrlID() == IDC_STATIC_WMR		||
		  pWnd->GetDlgCtrlID() == IDC_STATIC_ANR		||
		  pWnd->GetDlgCtrlID() == IDC_STATIC_ANM		)
        pDC->SetTextColor(RGB(0,0,255));
		
	if (  pWnd->GetDlgCtrlID() == IDC_EDIT_RainWMav			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_RainWMoutS		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_RainWMoutM		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_RainANav			||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_RainANoutS		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_RainANoutM		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_MultiWMav		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_MultiWMoutS		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_MultiWMoutM		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_MultiANav		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_MultiANoutS		||
		  pWnd->GetDlgCtrlID() == IDC_EDIT_MultiANoutM		)
        pDC->SetBkColor(RGB(255,255,128));
		
	return hbr;
}

BOOL CP530availabilityDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
