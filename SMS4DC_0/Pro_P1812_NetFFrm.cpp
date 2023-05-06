// Pro_P1812_NetFFrm.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Pro_P1812_NetFFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_NetFFrm

IMPLEMENT_DYNCREATE(CPro_P1812_NetFFrm, CMDIChildWnd)

CPro_P1812_NetFFrm::CPro_P1812_NetFFrm()
{
}

CPro_P1812_NetFFrm::~CPro_P1812_NetFFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_P1812_NetFFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_P1812_NetFFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_NetFFrm message handlers

void CPro_P1812_NetFFrm::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50 ,   1*(((CSMS4DCApp *)AfxGetApp())->yN) +50 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_P1812_NetFFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
