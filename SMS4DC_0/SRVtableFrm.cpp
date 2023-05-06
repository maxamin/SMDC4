// SRVtableFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "SRVtableFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSRVtableFrm

IMPLEMENT_DYNCREATE(CSRVtableFrm, CMDIChildWnd)

CSRVtableFrm::CSRVtableFrm()
{
}

CSRVtableFrm::~CSRVtableFrm()
{
}


BEGIN_MESSAGE_MAP(CSRVtableFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSRVtableFrm)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRVtableFrm message handlers

void CSRVtableFrm::ActivateFrame(int nCmdShow) 
{
	int W=615,H=226;
	CMDIChildWnd::MoveWindow(10, 10, W,H);
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

// 970710
void CSRVtableFrm::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	((CSMS4DCApp *)AfxGetApp())->ToolBar_Function(4);
}
