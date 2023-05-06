// Pro_Free_NetBFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_Free_NetBFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_NetBFrm

IMPLEMENT_DYNCREATE(CPro_Free_NetBFrm, CMDIChildWnd)

CPro_Free_NetBFrm::CPro_Free_NetBFrm()
{
}

CPro_Free_NetBFrm::~CPro_Free_NetBFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_Free_NetBFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_Free_NetBFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_NetBFrm message handlers

void CPro_Free_NetBFrm::ActivateFrame(int nCmdShow) 
{
	int W= 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50;
	int H= 1*(((CSMS4DCApp *)AfxGetApp())->yN) +50;
	CMDIChildWnd::MoveWindow(0, 0, W ,  H );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_Free_NetBFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
