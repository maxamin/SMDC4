// Area3DFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Area3DFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArea3DFrm

IMPLEMENT_DYNCREATE(CArea3DFrm, CMDIChildWnd)

CArea3DFrm::CArea3DFrm()
{
}

CArea3DFrm::~CArea3DFrm()
{
}


BEGIN_MESSAGE_MAP(CArea3DFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CArea3DFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArea3DFrm message handlers

void CArea3DFrm::ActivateFrame(int nCmdShow) 
{
	MoveWindow(0, 0, 800/2 ,   650/2 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CArea3DFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
