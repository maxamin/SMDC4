// IDWMMapFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "IDWMMapFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapFrm

IMPLEMENT_DYNCREATE(CIDWMMapFrm, CMDIChildWnd)

CIDWMMapFrm::CIDWMMapFrm()
{
}

CIDWMMapFrm::~CIDWMMapFrm()
{
}


BEGIN_MESSAGE_MAP(CIDWMMapFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CIDWMMapFrm)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapFrm message handlers


void CIDWMMapFrm::ActivateFrame(int nCmdShow) 
{
//	nCmdShow = SW_MAXIMIZE;		

	CMDIChildWnd::MoveWindow(0, 0, 970,654);
	nCmdShow = SW_SHOW;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CIDWMMapFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}


// 970710
void CIDWMMapFrm::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	((CSMS4DCApp *)AfxGetApp())->ToolBar_Function(1);

//	CControlBar* pBar = GetControlBar(IDR_SMS4DCTYPE340); 
//	ShowControlBar(pBar, TRUE, FALSE); 
//	ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE) == 0, FALSE); 
}

