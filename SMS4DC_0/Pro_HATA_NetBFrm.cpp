// Pro_HATA_NetBFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_HATA_NetBFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_NetBFrm

IMPLEMENT_DYNCREATE(CPro_HATA_NetBFrm, CMDIChildWnd)

CPro_HATA_NetBFrm::CPro_HATA_NetBFrm()
{
}

CPro_HATA_NetBFrm::~CPro_HATA_NetBFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_HATA_NetBFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_HATA_NetBFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_NetBFrm message handlers

void CPro_HATA_NetBFrm::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50 ,   1*(((CSMS4DCApp *)AfxGetApp())->yN) +50 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_HATA_NetBFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
