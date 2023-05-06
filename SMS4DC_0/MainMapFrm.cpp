// MainMapFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "MainMapFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainMapFrm

IMPLEMENT_DYNCREATE(CMainMapFrm, CMDIChildWnd)

CMainMapFrm::CMainMapFrm()
{
}

CMainMapFrm::~CMainMapFrm()
{
}


BEGIN_MESSAGE_MAP(CMainMapFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMainMapFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainMapFrm message handlers

void CMainMapFrm::ActivateFrame(int nCmdShow) 
{
	nCmdShow = SW_MAXIMIZE;		
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}
