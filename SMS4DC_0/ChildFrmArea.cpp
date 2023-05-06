// ChildFrmArea.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "ChildFrmArea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrmArea

IMPLEMENT_DYNCREATE(CChildFrmArea, CMDIChildWnd)

CChildFrmArea::CChildFrmArea()
{
}

CChildFrmArea::~CChildFrmArea()
{
}


BEGIN_MESSAGE_MAP(CChildFrmArea, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrmArea)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrmArea message handlers

void CChildFrmArea::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50 ,   1*(((CSMS4DCApp *)AfxGetApp())->yN) +50 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CChildFrmArea::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
