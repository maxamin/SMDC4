// Pro_P370_LineFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P370_LineFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_LineFrm

IMPLEMENT_DYNCREATE(CPro_P370_LineFrm, CMDIChildWnd)

CPro_P370_LineFrm::CPro_P370_LineFrm()
{
}

CPro_P370_LineFrm::~CPro_P370_LineFrm()
{
}


BEGIN_MESSAGE_MAP(CPro_P370_LineFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CPro_P370_LineFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_LineFrm message handlers

void CPro_P370_LineFrm::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::MoveWindow(0, 0, 870,654);
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CPro_P370_LineFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
