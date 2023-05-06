// Pro_P1546_AreaFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P1546_AreaFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_AreaFrm

IMPLEMENT_DYNCREATE(CPro_P1546_AreaFrm, CMDIChildWnd)

CPro_P1546_AreaFrm::CPro_P1546_AreaFrm()
{
}

CPro_P1546_AreaFrm::~CPro_P1546_AreaFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_P1546_AreaFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_P1546_AreaFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_AreaFrm message handlers

void CPro_P1546_AreaFrm::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50 ,   1*(((CSMS4DCApp *)AfxGetApp())->yN) +50 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_P1546_AreaFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
