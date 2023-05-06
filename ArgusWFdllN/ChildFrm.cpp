// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "ArgusWFdll.h"

#include "ChildFrm.h"
#include "MainFrm.h"


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
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()

	// ANSI notification code (for Windows 95)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

	// Unicode notification code (for NT)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	m_Lang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_ARGUSTYPE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	ShowControlBar(&m_wndToolBar, TRUE, FALSE);

	return 0;
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	nCmdShow = SW_MAXIMIZE;
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarCheck();
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

void CChildFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CMDIChildWnd::OnShowWindow(bShow, nStatus);

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ToolbarSet();
}

//////////////////////////////
void CChildFrame::GetMessageString(UINT nID, CString& rMessage) const
{
	CFrameWnd::GetMessageString(nID, rMessage);

	CString str = rMessage;
	CString str1 =   (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(str)));
	rMessage = str1;
}

#define _countof(array) (sizeof(array)/sizeof(array[0]))
BOOL CChildFrame::OnToolTipText(UINT nID, NMHDR* pNMHDR,  LRESULT*pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);
	
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	
  	CString strTipText;
	strTipText.LoadString(pNMHDR->idFrom);

	CString str = strTipText;
	int n = str.Find('\n');
	str.Delete(0,n+1);
	strTipText = _Z(str);

//	if ( GetToolText( pNMHDR->idFrom, strTipText ))
	{
#ifndef _UNICODE
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			TRACE1("tooltip: %s", pTTTA->szText);
			lstrcpyn(pTTTA->szText, strTipText, _countof(pTTTA->szText));
		}
		else
		{
			TRACE1("tooltip: %s", pTTTW->szText);
			_mbstowcsz(pTTTW->szText, strTipText, _countof(pTTTW->szText));
		}
#else
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			TRACE1("tooltip: %s", pTTTA->szText);
			_wcstombsz(pTTTA->szText, strTipText, _countof(pTTTA->szText));
		}
		else
		{
			TRACE1("tooltip: %s", pTTTW->szText);
			lstrcpyn(pTTTW->szText, strTipText, _countof(pTTTW->szText));
		}
#endif
		return TRUE;
	}
  
	return CFrameWnd::OnToolTipText( nID, pNMHDR, pResult );
}

