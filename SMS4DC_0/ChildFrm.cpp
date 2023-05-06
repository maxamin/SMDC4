// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "SMS4DC.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_SETFOCUS()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::ActivateFrame(int nCmdShow) 
{
//	nCmdShow = SW_MAXIMIZE;		

//	CRect myRect;
//	GetClientRect(myRect);
//	CMDIChildWnd::CalcWindowRect(&myRect);
//	CMDIChildWnd::MoveWindow(0, 0, 14*myRect.Width()/10, 21*myRect.Height()/10);

	CMDIChildWnd::MoveWindow(0, 0, 870,634);
	nCmdShow = SW_SHOW   ;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


// 970710
void CChildFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	((CSMS4DCApp *)AfxGetApp())->ToolBar_Function(2);
}

void CChildFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMaxTrackSize.x = 1230;	
	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);
}
