// StationsTableFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "StationsTableFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationsTableFrm

IMPLEMENT_DYNCREATE(CStationsTableFrm, CMDIChildWnd)

CStationsTableFrm::CStationsTableFrm()
{
}

CStationsTableFrm::~CStationsTableFrm()
{
}


BEGIN_MESSAGE_MAP(CStationsTableFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CStationsTableFrm)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStationsTableFrm message handlers

void CStationsTableFrm::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 870,620);
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

// 970710
void CStationsTableFrm::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	((CSMS4DCApp *)AfxGetApp())->ToolBar_Function(6);
}
