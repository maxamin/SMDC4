// KFactor.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "KFactor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKFactor dialog


CKFactor::CKFactor(CWnd* pParent /*=NULL*/)
	: CDialog(CKFactor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKFactor)
	m_kfactorEdit = _T("4/3");
	//}}AFX_DATA_INIT
}


void CKFactor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKFactor)
	DDX_Text(pDX, IDC_kfactor, m_kfactorEdit);
	DDV_MaxChars(pDX, m_kfactorEdit, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKFactor, CDialog)
	//{{AFX_MSG_MAP(CKFactor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKFactor message handlers

BOOL CKFactor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE; 
}
