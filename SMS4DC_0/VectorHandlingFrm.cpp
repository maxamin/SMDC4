// VectorHandlingFrm.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "VectorHandlingFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingFrm

IMPLEMENT_DYNCREATE(CVectorHandlingFrm, CMDIChildWnd)

CVectorHandlingFrm::CVectorHandlingFrm()
{
}

CVectorHandlingFrm::~CVectorHandlingFrm()
{
}


BEGIN_MESSAGE_MAP(CVectorHandlingFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CVectorHandlingFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingFrm message handlers

void CVectorHandlingFrm::ActivateFrame(int nCmdShow) 
{
	CWnd *nW = GetParent();
	CRect rect;
	nW->GetWindowRect(rect);
//	CMDIChildWnd::MoveWindow(rect.right-265, 0, 265 ,   265 );
	CMDIChildWnd::MoveWindow(rect.right-265-25, 0, 265+25 ,   265 );
	nCmdShow = SW_SHOW;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}
