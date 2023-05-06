// Int_BT2BT_FreeFrm.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "Int_BT2BT_FreeFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInt_BT2BT_FreeFrm

IMPLEMENT_DYNCREATE(CInt_BT2BT_FreeFrm, CMDIChildWnd)

CInt_BT2BT_FreeFrm::CInt_BT2BT_FreeFrm()
{
}

CInt_BT2BT_FreeFrm::~CInt_BT2BT_FreeFrm()
{
}


BEGIN_MESSAGE_MAP(CInt_BT2BT_FreeFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CInt_BT2BT_FreeFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInt_BT2BT_FreeFrm message handlers

void CInt_BT2BT_FreeFrm::ActivateFrame(int nCmdShow) 
{
	int W= 1*(((CSMS4DCApp *)AfxGetApp())->xN) +50;
	int H= 1*(((CSMS4DCApp *)AfxGetApp())->yN) +50;
	CMDIChildWnd::MoveWindow(0, 0, W ,  H );
	nCmdShow = SW_SHOW   ;	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CInt_BT2BT_FreeFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title
	
	return CMDIChildWnd::PreCreateWindow(cs);
}
