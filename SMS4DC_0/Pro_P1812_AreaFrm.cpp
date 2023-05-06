// Pro_P1812_AreaFrm.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Pro_P1812_AreaFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_AreaFrm

IMPLEMENT_DYNCREATE(CPro_P1812_AreaFrm, CMDIChildWnd)

CPro_P1812_AreaFrm::CPro_P1812_AreaFrm()
{
}

CPro_P1812_AreaFrm::~CPro_P1812_AreaFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_P1812_AreaFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_P1812_AreaFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_AreaFrm message handlers

void CPro_P1812_AreaFrm::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50 ,   1*(((CSMS4DCApp *)AfxGetApp())->yN) +50 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_P1812_AreaFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
