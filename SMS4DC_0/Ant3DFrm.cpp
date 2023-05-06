// Ant3DFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Ant3DFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnt3DFrm

IMPLEMENT_DYNCREATE(CAnt3DFrm, CMDIChildWnd)

CAnt3DFrm::CAnt3DFrm()
{
}

CAnt3DFrm::~CAnt3DFrm()
{
}


BEGIN_MESSAGE_MAP(CAnt3DFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CAnt3DFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnt3DFrm message handlers

void CAnt3DFrm::ActivateFrame(int nCmdShow) 
{
	MoveWindow(0, 0, 800/2 ,   650/2 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CAnt3DFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
