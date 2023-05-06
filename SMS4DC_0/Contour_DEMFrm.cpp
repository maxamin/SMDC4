// Contour_DEMFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Contour_DEMFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMFrm

IMPLEMENT_DYNCREATE(CContour_DEMFrm, CMDIChildWnd)

CContour_DEMFrm::CContour_DEMFrm()
{
}

CContour_DEMFrm::~CContour_DEMFrm()
{
}


BEGIN_MESSAGE_MAP(CContour_DEMFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CContour_DEMFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMFrm message handlers

void CContour_DEMFrm::ActivateFrame(int nCmdShow) 
{
	MoveWindow(0, 0, 800 ,   650 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CContour_DEMFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
