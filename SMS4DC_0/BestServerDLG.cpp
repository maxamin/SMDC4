// BestServerDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "BestServerDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBestServerDLG dialog


CBestServerDLG::CBestServerDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CBestServerDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBestServerDLG)
	m_Tvalue = 0.0;
	//}}AFX_DATA_INIT
	
	m_title = "Best Server Parameter";			//98/12/27
	m_label = "Threshold Value (dBuV/m) :";		//99/04/28
}


void CBestServerDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBestServerDLG)
	DDX_Text(pDX, IDC_EDIT_Tvalue, m_Tvalue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBestServerDLG, CDialog)
	//{{AFX_MSG_MAP(CBestServerDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBestServerDLG message handlers

BOOL CBestServerDLG::OnInitDialog() 
{
	SetWindowText(m_title);									//98/12/27
	GetDlgItem(IDC_STATICb1)->SetWindowText(m_label);		//99/04/28

	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}
