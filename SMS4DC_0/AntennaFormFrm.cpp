// AntennaFormFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "AntennaFormFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormFrm

IMPLEMENT_DYNCREATE(CAntennaFormFrm, CMDIChildWnd)

CAntennaFormFrm::CAntennaFormFrm()
{
}

CAntennaFormFrm::~CAntennaFormFrm()
{
}


BEGIN_MESSAGE_MAP(CAntennaFormFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CAntennaFormFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormFrm message handlers

void CAntennaFormFrm::ActivateFrame(int nCmdShow) 
{
	MoveWindow(0, 0, 800 ,   650 );
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}
/*
BOOL CAntennaFormFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
   if( !CMDIChildWnd::PreCreateWindow(cs) )
        return FALSE;

    cs.style &= ~(WS_THICKFRAME);
    cs.style &= ~(WS_MAXIMIZEBOX);
 
    cs.style |= WS_BORDER;

    return TRUE;
}
*/