// RightGrid.cpp : implementation file
//

#include "stdafx.h"
#include "Administrative.h"
#include "RightGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRightGrid dialog


CRightGrid::CRightGrid(CWnd* pParent /*=NULL*/)
	: CDialog(CRightGrid::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRightGrid)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRightGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRightGrid)
	DDX_Control(pDX, IDC_DATEPICKER, m_Date1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRightGrid, CDialog)
	//{{AFX_MSG_MAP(CRightGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRightGrid message handlers


