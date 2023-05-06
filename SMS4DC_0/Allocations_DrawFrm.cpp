// Allocations_DrawFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Allocations_DrawFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawFrm

IMPLEMENT_DYNCREATE(CAllocations_DrawFrm, CMDIChildWnd)

CAllocations_DrawFrm::CAllocations_DrawFrm()
{
}

CAllocations_DrawFrm::~CAllocations_DrawFrm()
{
}


BEGIN_MESSAGE_MAP(CAllocations_DrawFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CAllocations_DrawFrm)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawFrm message handlers

void CAllocations_DrawFrm::ActivateFrame(int nCmdShow) 
{
	MoveWindow(0, 0, 1000 ,   500 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CAllocations_DrawFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}


// 970710
void CAllocations_DrawFrm::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	((CSMS4DCApp *)AfxGetApp())->ToolBar_Function(3);
}
