// Pro_P370_NetBFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P370_NetBFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_NetBFrm

IMPLEMENT_DYNCREATE(CPro_P370_NetBFrm, CMDIChildWnd)

CPro_P370_NetBFrm::CPro_P370_NetBFrm()
{
}

CPro_P370_NetBFrm::~CPro_P370_NetBFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_P370_NetBFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_P370_NetBFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_NetBFrm message handlers

void CPro_P370_NetBFrm::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50 ,   1*(((CSMS4DCApp *)AfxGetApp())->yN) +50 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_P370_NetBFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
