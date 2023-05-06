// EffectiveHeigthFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "EffectiveHeigthFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthFrm

IMPLEMENT_DYNCREATE(CEffectiveHeigthFrm, CMDIChildWnd)

CEffectiveHeigthFrm::CEffectiveHeigthFrm()
{
}

CEffectiveHeigthFrm::~CEffectiveHeigthFrm()
{
}


BEGIN_MESSAGE_MAP(CEffectiveHeigthFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CEffectiveHeigthFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthFrm message handlers

void CEffectiveHeigthFrm::ActivateFrame(int nCmdShow) 
{
//	int W=13*(((CSMS4DCApp *)AfxGetApp())->m_W_Heff+((CSMS4DCApp *)AfxGetApp())->m_H_Heff)/2;
//	int W=13*(((CSMS4DCApp *)AfxGetApp())->xN+((CSMS4DCApp *)AfxGetApp())->yN)/2;
int W=650;
	CMDIChildWnd::MoveWindow(0, 0, W,W);
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}
