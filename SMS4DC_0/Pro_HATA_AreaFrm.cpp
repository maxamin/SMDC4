// Pro_HATA_AreaFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_HATA_AreaFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_AreaFrm

IMPLEMENT_DYNCREATE(CPro_HATA_AreaFrm, CMDIChildWnd)

CPro_HATA_AreaFrm::CPro_HATA_AreaFrm()
{
}

CPro_HATA_AreaFrm::~CPro_HATA_AreaFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_HATA_AreaFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_HATA_AreaFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_AreaFrm message handlers

void CPro_HATA_AreaFrm::ActivateFrame(int nCmdShow) 
{
	int W= 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50;
	int H= 1*(((CSMS4DCApp *)AfxGetApp())->yN) +50;
	CMDIChildWnd::MoveWindow(0, 0, W ,  H );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_HATA_AreaFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
