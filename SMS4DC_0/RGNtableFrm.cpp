// RGNtableFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "RGNtableFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGNtableFrm

IMPLEMENT_DYNCREATE(CRGNtableFrm, CMDIChildWnd)

CRGNtableFrm::CRGNtableFrm()
{
}

CRGNtableFrm::~CRGNtableFrm()
{
}


BEGIN_MESSAGE_MAP(CRGNtableFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRGNtableFrm)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRGNtableFrm message handlers

void CRGNtableFrm::ActivateFrame(int nCmdShow) 
{
	int W=765,H=485;
	CMDIChildWnd::MoveWindow(0, 0, W,H);
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

// 970710
void CRGNtableFrm::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	((CSMS4DCApp *)AfxGetApp())->ToolBar_Function(5);
}
