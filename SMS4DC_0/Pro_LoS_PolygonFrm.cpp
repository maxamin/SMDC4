// Pro_LoS_PolygonFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_LoS_PolygonFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_PolygonFrm

IMPLEMENT_DYNCREATE(CPro_LoS_PolygonFrm, CMDIChildWnd)

CPro_LoS_PolygonFrm::CPro_LoS_PolygonFrm()
{
}

CPro_LoS_PolygonFrm::~CPro_LoS_PolygonFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_LoS_PolygonFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_LoS_PolygonFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_PolygonFrm message handlers

void CPro_LoS_PolygonFrm::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 870,654);
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_LoS_PolygonFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
