// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SMS4DC.h"

#include "MainFrm.h"

#include "SPROMEPS.h"

#include "childfrm.h"
#include "IDWMMapFrm.h"
#include "ChildFrmArea.h"
#include "Pro_Free_NetFFrm.h"
#include "Pro_Free_NetBFrm.h"
#include "Contour_DEMFrm.h"
#include "Area3DFrm.h"
#include "Ant3DFrm.h"
#include "EffectiveHeigthFrm.h"
#include "Pro_LoS_AreaFrm.h"
#include "Pro_LoS_LineFrm.h"
#include "Pro_LoS_PolygonFrm.h"
#include "Pro_P370_LineFrm.h"
#include "Pro_P370_PolygonFrm.h"
#include "Pro_P370_AreaFrm.h"
#include "Pro_P370_NetFFrm.h"
#include "Pro_P370_NetBFrm.h"
#include "Pro_P370_LinkFrm.h"
#include "Pro_P1546_LineFrm.h"
#include "Pro_P1546_PolygonFrm.h"
#include "Pro_P1546_AreaFrm.h"
#include "Pro_P1546_NetFFrm.h"
#include "Pro_P1546_NetBFrm.h"
#include "Pro_P1546_LinkFrm.h"
#include "Pro_HATA_AreaFrm.h"
#include "Pro_HATA_NetFFrm.h"
#include "Pro_HATA_NetBFrm.h"
#include "Pro_P526_LinkFrm.h"
#include "Pro_Smooth_LinkFrm.h"
#include "Pro_P452_LinkFrm.h"
#include "Pro_P530_LinkFrm.h"
#include "VectorHandlingFrm.h"
#include "Allocations_DrawFrm.h"
#include "RGNtableFrm.h"
#include "SRVtableFrm.h"
#include "Int_BC2BC_FreeFrm.h"
#include "Int_BT2BT_FreeFrm.h"

#include "Pro_P1812_AreaFrm.h"
#include "Pro_P1812_NetFFrm.h"
#include "Pro_P1812_NetBFrm.h"

#include "Pro_P526V14_LinkFrm.h"

#include "AntennaFormFrm.h"		//98/05/06

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_TOOLBARMENU_DATABASETOOLBAR, OnToolbarmenuDatabasetoolbar)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARMENU_DATABASETOOLBAR, OnUpdateToolbarmenuDatabasetoolbar)
	ON_COMMAND(ID_TOOLBARMENU_MAINMAPTOOLBAR, OnToolbarmenuMainmaptoolbar)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARMENU_MAINMAPTOOLBAR, OnUpdateToolbarmenuMainmaptoolbar)
	ON_COMMAND(ID_TOOLBARMENU_DEMTOOLBAR, OnToolbarmenuDemtoolbar)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARMENU_DEMTOOLBAR, OnUpdateToolbarmenuDemtoolbar)
	ON_COMMAND(ID_TOOLBARMENU_IDWMMAP, OnToolbarmenuIdwmmap)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARMENU_IDWMMAP, OnUpdateToolbarmenuIdwmmap)
	ON_COMMAND(ID_TOOLBARMENU_SERVICE, OnToolbarmenuService)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARMENU_SERVICE, OnUpdateToolbarmenuService)
	ON_COMMAND(ID_TOOLBARMENU_REGIONTOOLBAR, OnToolbarmenuRegiontoolbar)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARMENU_REGIONTOOLBAR, OnUpdateToolbarmenuRegiontoolbar)
	ON_COMMAND(ID_TOOLBARMENU_ALLOCATIONPLANTOOLBAR, OnToolbarmenuAllocationplantoolbar)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARMENU_ALLOCATIONPLANTOOLBAR, OnUpdateToolbarmenuAllocationplantoolbar)
	ON_COMMAND(ID_TOOLBARMENU_HIDEALLTOOLBARS, OnToolbarmenuHidealltoolbars)

	// ANSI notification code (for Windows 95)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

	// Unicode notification code (for NT)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_Lat,
	ID_INDICATOR_Lon,
	ID_INDICATOR_Alt,
	ID_INDICATOR_Dist,
	ID_INDICATOR_E,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_Time,

};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

////////////////////////////////////// SMS4DC ToolBar//////////////////////////////////////////////
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	ShowControlBar(&m_wndToolBar, FALSE, FALSE);

////////////////////////////////////// DATABASE ToolBar//////////////////////////////////////////////
	if (!m_ToolBarDATABASE.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBarDATABASE.LoadToolBar(IDR_SMS4DCTYPE5))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_ToolBarDATABASE.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBarDATABASE);
	ShowControlBar(&m_ToolBarDATABASE, FALSE, FALSE);

////////////////////////////////////// MainMap ToolBar//////////////////////////////////////////////
	if (!m_ToolBarMainMap.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBarMainMap.LoadToolBar(IDR_SMS4DCTYPE30))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_ToolBarMainMap.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBarMainMap);
	ShowControlBar(&m_ToolBarMainMap, FALSE, FALSE);

////////////////////////////////////// IDWMMap ToolBar//////////////////////////////////////////////
	if (!m_ToolBarIDWMMap.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBarIDWMMap.LoadToolBar(IDR_SMS4DCTYPE340))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_ToolBarIDWMMap.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBarIDWMMap);
	ShowControlBar(&m_ToolBarIDWMMap, FALSE, FALSE);

////////////////////////////////////// SRVtable ToolBar//////////////////////////////////////////////
	if (!m_ToolBarSRVtable.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBarSRVtable.LoadToolBar(IDR_SMS4DCTYPE35))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_ToolBarSRVtable.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBarSRVtable);
	ShowControlBar(&m_ToolBarSRVtable, FALSE, FALSE);

////////////////////////////////////// RGNtable ToolBar//////////////////////////////////////////////
	if (!m_ToolBarRGNtable.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBarRGNtable.LoadToolBar(IDR_SMS4DCTYPE36))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_ToolBarRGNtable.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBarRGNtable);
	ShowControlBar(&m_ToolBarRGNtable, FALSE, FALSE);

////////////////////////////////////// Allocation ToolBar//////////////////////////////////////////////
	OnCreateToolBarALLplan();
////////////////////////////////////// Status Bar//////////////////////////////////////////////
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_Lat,SBPS_NORMAL,125);
	m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_Lon,SBPS_NORMAL,135);
	m_wndStatusBar.SetPaneInfo(3,ID_INDICATOR_Alt,SBPS_NORMAL,70);
	m_wndStatusBar.SetPaneInfo(4,ID_INDICATOR_Dist,SBPS_NORMAL,100);
	m_wndStatusBar.SetPaneInfo(5,ID_INDICATOR_E,SBPS_NORMAL,165);

	m_wndStatusBar.SetPaneInfo(6,ID_INDICATOR_CAPS,SBPS_NOBORDERS,0);
	m_wndStatusBar.SetPaneInfo(7,ID_INDICATOR_NUM,SBPS_NOBORDERS,0);
	m_wndStatusBar.SetPaneInfo(8,ID_INDICATOR_SCRL,SBPS_NOBORDERS,0);

	m_wndStatusBar.SetPaneInfo(9,ID_INDICATOR_Time,SBPS_POPOUT,75);

	m_nTimer=SetTimer(ID_TIMER,500,NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

cs.style&=~(LONG)FWS_ADDTOTITLE;    // no title

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	CTime time=CTime::GetCurrentTime();
	int nHour=time.GetHour();
	int nMinute=time.GetMinute();
	int nSecond=time.GetSecond();
	CString string;
	string.Format("%02d :%02d :%02d ",nHour,nMinute,nSecond);
	m_wndStatusBar.SetPaneText(9,string);

	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnDestroy() 
{
	CMDIFrameWnd::OnDestroy();
	KillTimer(m_nTimer);	
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_RBUTTONDOWN)
	{
		CWnd* pWnd = CWnd::FromHandlePermanent(pMsg->hwnd);
		CControlBar* pBar = DYNAMIC_DOWNCAST(CControlBar, pWnd);

		if (pBar != NULL)
		 {
			CMenu Menu;
			CPoint pt;

			pt.x = LOWORD(pMsg->lParam);
			pt.y = HIWORD(pMsg->lParam);
			pBar->ClientToScreen(&pt);

			if (Menu.LoadMenu(IDR_ToolBarMENU))
			{
				CMenu* pSubMenu = Menu.GetSubMenu(0);
				if (pSubMenu!=NULL)
					pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
			}
		}
	}

#ifdef _SMS4DC_LockInclude_
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		CWnd* pWnd = CWnd::FromHandlePermanent(pMsg->hwnd);
		CControlBar* pBar = DYNAMIC_DOWNCAST(CControlBar, pWnd);

		if (pBar != NULL)
		{
			if(CheckLock() != SP_SUCCESS)
			{
			   AfxMessageBox(_Z("No Hardware lock found!"));
			   exit(1);
			}
		}
	}
#endif

	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}


void CMainFrame::OnToolbarmenuDatabasetoolbar() 
{
	if(m_ToolBarDATABASE.GetStyle()&WS_VISIBLE)
		ShowControlBar(&m_ToolBarDATABASE, FALSE, FALSE);
	else
		ShowControlBar(&m_ToolBarDATABASE, TRUE, FALSE);
}
void CMainFrame::OnUpdateToolbarmenuDatabasetoolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_ToolBarDATABASE.GetStyle()&WS_VISIBLE );
}

void CMainFrame::OnToolbarmenuMainmaptoolbar() 
{
	if(m_ToolBarMainMap.GetStyle()&WS_VISIBLE)
		ShowControlBar(&m_ToolBarMainMap, FALSE, FALSE);
	else
		ShowControlBar(&m_ToolBarMainMap, TRUE, FALSE);
}
void CMainFrame::OnUpdateToolbarmenuMainmaptoolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_ToolBarMainMap.GetStyle()&WS_VISIBLE );
}

void CMainFrame::OnToolbarmenuDemtoolbar() 
{
	if(m_wndToolBar.GetStyle()&WS_VISIBLE)
		ShowControlBar(&m_wndToolBar, FALSE, FALSE);
	else
		ShowControlBar(&m_wndToolBar, TRUE, FALSE);
}
void CMainFrame::OnUpdateToolbarmenuDemtoolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndToolBar.GetStyle()&WS_VISIBLE );
}


void CMainFrame::OnToolbarmenuIdwmmap() 
{
	if(m_ToolBarIDWMMap.GetStyle()&WS_VISIBLE)
		ShowControlBar(&m_ToolBarIDWMMap, FALSE, FALSE);
	else
		ShowControlBar(&m_ToolBarIDWMMap, TRUE, FALSE);
}
void CMainFrame::OnUpdateToolbarmenuIdwmmap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_ToolBarIDWMMap.GetStyle()&WS_VISIBLE );
	
}

void CMainFrame::OnToolbarmenuService() 
{
	if(m_ToolBarSRVtable.GetStyle()&WS_VISIBLE)
		ShowControlBar(&m_ToolBarSRVtable, FALSE, FALSE);
	else
		ShowControlBar(&m_ToolBarSRVtable, TRUE, FALSE);
}
void CMainFrame::OnUpdateToolbarmenuService(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_ToolBarSRVtable.GetStyle()&WS_VISIBLE );
}

void CMainFrame::OnToolbarmenuRegiontoolbar() 
{
	if(m_ToolBarRGNtable.GetStyle()&WS_VISIBLE)
		ShowControlBar(&m_ToolBarRGNtable, FALSE, FALSE);
	else
		ShowControlBar(&m_ToolBarRGNtable, TRUE, FALSE);
}
void CMainFrame::OnUpdateToolbarmenuRegiontoolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_ToolBarRGNtable.GetStyle()&WS_VISIBLE );
}

void CMainFrame::OnToolbarmenuAllocationplantoolbar() 
{
	if(m_ToolBarALLplan.GetStyle()&WS_VISIBLE)
		ShowControlBar(&m_ToolBarALLplan, FALSE, FALSE);
	else
		ShowControlBar(&m_ToolBarALLplan, TRUE, FALSE);
}
void CMainFrame::OnUpdateToolbarmenuAllocationplantoolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_ToolBarALLplan.GetStyle()&WS_VISIBLE );
}


int CMainFrame::OnCreateToolBarALLplan()
{
	if (!m_ToolBarALLplan.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_ToolBarALLplan.LoadToolBar(IDR_ToolBarALLp))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

//	gSmallFont.CreatePointFont(90, "DEFAULT", NULL); 
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       
	lf.lfHeight = 14; 
	lf.lfWidth = 0;
	lf.lfWeight = FW_BOLD;
	strcpy(lf.lfFaceName, "DEFAULT");
	lf.lfEscapement = 0;
	gSmallFont.CreateFontIndirect(&lf);

	int nH1 = 125;		int nH2 = 22;

	////////////////////////Region//////////////////////////
//	int nWidth = 100;
	int nWidth = 75;
	int nHeight = nH1;
	m_ToolBarALLplan.SetButtonInfo(2,IDC_CBREGION,TBBS_SEPARATOR,nWidth);
	CRect rect;
	m_ToolBarALLplan.GetItemRect(2,&rect);
	rect.bottom = rect.top + nHeight;
	m_ctlRegion.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
					  rect,&m_ToolBarALLplan,IDC_CBREGION);

m_ctlRegion.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  
	////////////////////////lable Frq//////////////////////////
//	int nWidth2 = 80;
	int nWidth2 = 70;
	int nHeight2 = nH2;
	m_ToolBarALLplan.SetButtonInfo(4,IDC_CBSTATIC1,TBBS_SEPARATOR,nWidth2);
	CRect rect2;
	m_ToolBarALLplan.GetItemRect(4,&rect2);
	rect2.bottom = rect2.top + nHeight2;
rect2.top = rect2.top + 3;
	m_Static_Frq.Create(_Z("Frequency : "), WS_CHILD|WS_VISIBLE|SS_CENTER, 
					 rect2, &m_ToolBarALLplan);

m_Static_Frq.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  
	////////////////////////F_LO//////////////////////////
//	int nWidth1 = 100;
	int nWidth1 = 80;
	int nHeight1 = nH2;
	m_ToolBarALLplan.SetButtonInfo(5,IDC_CBFLO,TBBS_SEPARATOR,nWidth1);
	CRect rect1;
	m_ToolBarALLplan.GetItemRect(5,&rect1);
	rect1.bottom = rect1.top + nHeight1;
rect1.top = rect1.top + 1;
	m_ctlEdit_Flo.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
					  rect1,&m_ToolBarALLplan,IDC_CBFLO);

m_ctlEdit_Flo.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  
	////////////////////////F_HI//////////////////////////
//	int nWidth3 = 100;
	int nWidth3 = 80;
	int nHeight3 = nH2;
	m_ToolBarALLplan.SetButtonInfo(6,IDC_CBFHI,TBBS_SEPARATOR,nWidth3);
	CRect rect3;
	m_ToolBarALLplan.GetItemRect(6,&rect3);
	rect3.bottom = rect3.top + nHeight3;
rect3.top = rect3.top + 1;
	m_ctlEdit_Fhi.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
					  rect3,&m_ToolBarALLplan,IDC_CBFHI);

m_ctlEdit_Fhi.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  
	////////////////////////UNIT//////////////////////////
//	int nWidth4 = 60;
	int nWidth4 = 50;
	int nHeight4 = nH1;
	m_ToolBarALLplan.SetButtonInfo(7,IDC_CBUNIT,TBBS_SEPARATOR,nWidth4);
	CRect rect4;
	m_ToolBarALLplan.GetItemRect(7,&rect4);
	rect4.bottom = rect4.top + nHeight4;
	m_ctlUnit.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
					  rect4,&m_ToolBarALLplan,IDC_CBUNIT);

m_ctlUnit.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  
	////////////////////////scale//////////////////////////
	int nWidth5 = 110;
	int nHeight5 = nH1;
	m_ToolBarALLplan.SetButtonInfo(9,IDC_CBSCALE,TBBS_SEPARATOR,nWidth5);
	CRect rect5;
	m_ToolBarALLplan.GetItemRect(9,&rect5);
	rect5.bottom = rect5.top + nHeight5;
	m_ctlScale.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
					  rect5,&m_ToolBarALLplan,IDC_CBSCALE);

m_ctlScale.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  
	////////////////////////apply//////////////////////////
//	int nWidth6 = 45;
	int nWidth6 = 70;
	int nHeight6 = nH2;
	m_ToolBarALLplan.SetButtonInfo(11,IDC_CBAPPLY,TBBS_SEPARATOR,nWidth6);
	CRect rect6;
	m_ToolBarALLplan.GetItemRect(11,&rect6);
	rect6.bottom = rect6.top + nHeight6;
rect6.top = rect6.top + 1;
	m_ctlapply.Create(_Z("Apply"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
				   rect6, &m_ToolBarALLplan, IDC_CBAPPLY);

m_ctlapply.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  
	////////////////////////lable S5//////////////////////////
	int nWidth7 = 90;
	int nHeight7 = nH2;
	m_ToolBarALLplan.SetButtonInfo(13,IDC_CBSTATIC2,TBBS_SEPARATOR,nWidth7);
	CRect rect7;
	m_ToolBarALLplan.GetItemRect(13,&rect7);
	rect7.bottom = rect7.top + nHeight7;
rect7.top = rect7.top + 3;
	m_Static_S5.Create(_Z("RR-Article 5 : "), WS_CHILD|WS_VISIBLE|SS_CENTER, 
					 rect7, &m_ToolBarALLplan);

m_Static_S5.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  
	////////////////////////S5//////////////////////////
//	int nWidth8 = 110;
	int nWidth8 = 100;
	int nHeight8 = nH1;
	m_ToolBarALLplan.SetButtonInfo(14,IDC_CBS5,TBBS_SEPARATOR,nWidth8);
	CRect rect8;
	m_ToolBarALLplan.GetItemRect(14,&rect8);
	rect8.bottom = rect8.top + nHeight8;
	m_ctlS5.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
					  rect8,&m_ToolBarALLplan,IDC_CBS5);

m_ctlS5.SendMessage(WM_SETFONT, (WPARAM)HFONT(gSmallFont),TRUE);  

	m_ToolBarALLplan.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBarALLplan);
	ShowControlBar(&m_ToolBarALLplan, FALSE, FALSE);

	return 0;
}



void CMainFrame::HideToolBars()
{
	ShowControlBar(&m_ToolBarALLplan, FALSE, FALSE);
	ShowControlBar(&m_ToolBarRGNtable, FALSE, FALSE);
	ShowControlBar(&m_ToolBarSRVtable, FALSE, FALSE);
	ShowControlBar(&m_ToolBarIDWMMap, FALSE, FALSE);
	ShowControlBar(&m_ToolBarMainMap, FALSE, FALSE);
	ShowControlBar(&m_ToolBarDATABASE, FALSE, FALSE);
}

void CMainFrame::OnToolbarmenuHidealltoolbars() 
{
	HideToolBars();	
	ShowControlBar(&m_wndToolBar, FALSE, FALSE);
}

void CMainFrame::ToolbarCheck() 
{
	m_wndToolBar_Flag		= m_wndToolBar.IsWindowVisible();
	m_ToolBarALLplan_Flag	= m_ToolBarALLplan.IsWindowVisible();
	m_ToolBarRGNtable_Flag	= m_ToolBarRGNtable.IsWindowVisible();
	m_ToolBarSRVtable_Flag	= m_ToolBarSRVtable.IsWindowVisible();
	m_ToolBarIDWMMap_Flag	= m_ToolBarIDWMMap.IsWindowVisible();
	m_ToolBarMainMap_Flag	= m_ToolBarMainMap.IsWindowVisible();
	m_ToolBarDATABASE_Flag	= m_ToolBarDATABASE.IsWindowVisible();

	OnToolbarmenuHidealltoolbars();
}

void CMainFrame::ToolbarSet() 
{
	ShowControlBar(&m_wndToolBar,		m_wndToolBar_Flag, FALSE);
	ShowControlBar(&m_ToolBarALLplan,	m_ToolBarALLplan_Flag, FALSE);
	ShowControlBar(&m_ToolBarRGNtable,	m_ToolBarRGNtable_Flag, FALSE);
	ShowControlBar(&m_ToolBarSRVtable,	m_ToolBarSRVtable_Flag, FALSE);
	ShowControlBar(&m_ToolBarIDWMMap,	m_ToolBarIDWMMap_Flag, FALSE);
	ShowControlBar(&m_ToolBarMainMap,	m_ToolBarMainMap_Flag, FALSE);
	ShowControlBar(&m_ToolBarDATABASE,	m_ToolBarDATABASE_Flag, FALSE);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void CMainFrame::ChangeMenuLang(UINT ID) 
{
	CString mLang = ((CSMS4DCApp *)AfxGetApp())->m_Lang;
	if (mLang==_T("En"))	return;

	CDocTemplate* pTemplate;
	POSITION pos;

	CString strTarget;
	switch(ID)
	{
		case IDR_SMS4DCTYPE34 :	strTarget = _T("IDWM Map");								break;
		case IDR_SMS4DCTYPE :	strTarget = _T("Main Desktop");							break;
		case IDR_SMS4DCTYPE3 :	strTarget = _T("Area Calculation (Free Space)");		break;
		case IDR_SMS4DCTYPE2 :	strTarget = _T("Line Calculation (Free Space)");		break;
		case IDR_SMS4DCTYPE7 :	strTarget = _T("Polygon Calculation (Free Space)");		break;
		case IDR_SMS4DCTYPE11 :	strTarget = _T("Maximum Field Strength (Free Space)");		break;
		case IDR_SMS4DCTYPE12 :	strTarget = _T("Best Server (Free Space)");		break;
		case IDR_SMS4DCTYPE27 :	strTarget = _T("Contour_DEM");		break;
		case IDR_SMS4DCTYPE26 :	strTarget = _T("Area 3D View");		break;
		case IDR_SMS4DCTYPE25 :	strTarget = _T("Antenna 3D View");		break;
		case IDR_SMS4DCTYPE6 :	strTarget = _T("Effective Height");		break;
		case IDR_SMS4DCTYPE1 :	strTarget = _T("Profile");		break;
		case IDR_SMS4DCTYPE4 :	strTarget = _T("Profile Polygon");		break;
		case IDR_SMS4DCTYPE10 :	strTarget = _T("Area Calculation (Line of Sight)");		break;
		case IDR_SMS4DCTYPE20 :	strTarget = _T("Line Calculation (Line of Sight)");		break;
		case IDR_SMS4DCTYPE24 :	strTarget = _T("Polygon Calculation (Line of Sight)");		break;
		case IDR_SMS4DCTYPE18 :	strTarget = _T("Line Calculation (P370)");		break;
		case IDR_SMS4DCTYPE22 :	strTarget = _T("Polygon Calculation (P370)");		break;
		case IDR_SMS4DCTYPE8 :	strTarget = _T("Area Calculation (P370)");		break;
		case IDR_SMS4DCTYPE13 :	strTarget = _T("Maximum Field Strength (P370)");		break;
		case IDR_SMS4DCTYPE14 :	strTarget = _T("Best Server (P370)");		break;
		case IDR_SMS4DCTYPE28 :	strTarget = _T("Link Calculation (P370)");		break;
		case IDR_SMS4DCTYPE19 :	strTarget = _T("Line Calculation (P1546)");		break;
		case IDR_SMS4DCTYPE23 :	strTarget = _T("Polygon Calculation (P1546)");		break;
		case IDR_SMS4DCTYPE9 :	strTarget = _T("Area Calculation (P1546)");		break;
		case IDR_SMS4DCTYPE15 :	strTarget = _T("Maximum Field Strength (P1546)");		break;
		case IDR_SMS4DCTYPE16 :	strTarget = _T("Best Server (P1546)");		break;
		case IDR_SMS4DCTYPE29 :	strTarget = _T("Link Calculation (P1546)");		break;
		case IDR_SMS4DCTYPE31 :	strTarget = _T("Area Calculation (HATA)");		break;
		case IDR_SMS4DCTYPE32 :	strTarget = _T("Maximum Field Strength (HATA)");		break;
		case IDR_SMS4DCTYPE33 :	strTarget = _T("Best Server (HATA)");		break;
		case IDR_SMS4DCTYPE39 :	strTarget = _T("Link Calculation (P526)");		break;
		case IDR_SMS4DCTYPE40 :	strTarget = _T("Link Calculation (Smooth Earth)");		break;
		case IDR_SMS4DCTYPE38 :	strTarget = _T("Link Calculation (P452)");		break;
		case IDR_SMS4DCTYPE41 :	strTarget = _T("Link Calculation (P530)");		break;
		case IDR_SMS4DCTYPE44 :	strTarget = _T("Vector Handling");		break;
		case IDR_SMS4DCTYPE21 :	strTarget = _T("Frequency Allocations 2D Chart");		break;
		case IDR_SMS4DCTYPE36 :	strTarget = _T("RGNtable");		break;
		case IDR_SMS4DCTYPE35 :	strTarget = _T("SRVtable");		break;
		case IDR_SMS4DCTYPE42 :	strTarget = _T("InterferenceBC2BC (Free Space)");		break;
		case IDR_SMS4DCTYPE43 :	strTarget = _T("InterferenceBT2BT (Free Space)");		break;

		case IDR_SMS4DCTYPE45 :	strTarget = _T("Area Calculation (P1812)");		break;
		case IDR_SMS4DCTYPE49 :	strTarget = _T("Maximum Field Strength (P1812)");		break;
		case IDR_SMS4DCTYPE50 :	strTarget = _T("Best Server (P1812)");		break;
		
		case IDR_SMS4DCTYPE51 :	strTarget = _T("Link Calculation (P526-14)");		break;

		case IDR_SMS4DCTYPE17 :	strTarget = _T("Antenna");		break;	//98/05/06

	}//ID

	#if _MFC_VER>=0x400
		pos = AfxGetApp()->GetFirstDocTemplatePosition();
		ASSERT(pos);
		CString strDocName;
		while (pos != NULL)
		{
			pTemplate =  AfxGetApp()->GetNextDocTemplate(pos);
			pTemplate->GetDocString(strDocName,CDocTemplate::docName);
			if (strDocName == strTarget)	break;
		}
	#else
		pos = m_templateList.GetHeadPosition(); 
		ASSERT(pos);
		pTemplate=(CDocTemplate *)m_templateList.GetNext( pos );
	#endif
	ASSERT(pTemplate);
	ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CMultiDocTemplate)));

	CMenu DefaultMenu,SharedMenu;
	DefaultMenu.LoadMenu(IDR_MAINFRAME);
	SharedMenu.LoadMenu(ID);

	CMenu *pMenu = GetMenu();
	ASSERT(pMenu );

	if (pMenu->m_hMenu==m_hMenuDefault)
		SetMenu(&DefaultMenu);
	else
	{
		SetMenu(&SharedMenu);
		::SendMessage(m_hWndMDIClient, WM_MDISETMENU,NULL, (LPARAM)GetWindowMenuPopup(SharedMenu.m_hMenu));
	}
	::DestroyMenu(m_hMenuDefault);

	ASSERT(((CMultiDocTemplate *)pTemplate)->m_hMenuShared);
	::DestroyMenu(((CMultiDocTemplate *)pTemplate)->m_hMenuShared);

	m_hMenuDefault = DefaultMenu.m_hMenu;
	((CMultiDocTemplate *)pTemplate)->m_hMenuShared = SharedMenu.m_hMenu;        

	POSITION docpos = pTemplate->GetFirstDocPosition( );
	CDocument *pDocument = NULL;
	while (docpos)
	{
		pDocument = pTemplate->GetNextDoc(docpos);
		ASSERT(pDocument);
		POSITION viewpos = pDocument->GetFirstViewPosition();
		CWnd *pParent;
		while (viewpos != NULL)
		{
			CView* pView = pDocument->GetNextView(viewpos);
			if (pView && NULL!=(pParent=pView->GetParentFrame()) )
			{
				((CSMS4DCApp *)AfxGetApp())->TranslateMenu(&SharedMenu);	 
				switch(ID)
				{
					case IDR_SMS4DCTYPE34 :	((CIDWMMapFrm *)pParent)->SharedMenu()		= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE :	((CChildFrame *)pParent)->SharedMenu()		= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE3 :	((CChildFrmArea *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE2 :	((CChildFrame *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE7 :	((CChildFrame *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE11 :	((CPro_Free_NetFFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE12 :	((CPro_Free_NetBFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE27 :	((CContour_DEMFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE26 :	((CArea3DFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE25 :	((CAnt3DFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE6 :	((CEffectiveHeigthFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE1 :	((CChildFrame *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE4 :	((CChildFrame *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE10 :	((CPro_LoS_AreaFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE20 :	((CPro_LoS_LineFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE24 :	((CPro_LoS_PolygonFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE18 :	((CPro_P370_LineFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE22 :	((CPro_P370_PolygonFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE8 :	((CPro_P370_AreaFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE13 :	((CPro_P370_NetFFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE14 :	((CPro_P370_NetBFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE28 :	((CPro_P370_LinkFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE19 :	((CPro_P1546_LineFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE23 :	((CPro_P1546_PolygonFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE9 :	((CPro_P1546_AreaFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE15 :	((CPro_P1546_NetFFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE16 :	((CPro_P1546_NetBFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE29 :	((CPro_P1546_LinkFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE31 :	((CPro_HATA_AreaFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE32 :	((CPro_HATA_NetFFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE33 :	((CPro_HATA_NetBFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE39 :	((CPro_P526_LinkFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE40 :	((CPro_Smooth_LinkFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE38 :	((CPro_P452_LinkFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE41 :	((CPro_P530_LinkFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE44 :	((CVectorHandlingFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE21 :	((CAllocations_DrawFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE36 :	((CRGNtableFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE35 :	((CSRVtableFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE42 :	((CInt_BC2BC_FreeFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE43 :	((CInt_BT2BT_FreeFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;

					case IDR_SMS4DCTYPE45 :	((CPro_P1812_AreaFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE49 :	((CPro_P1812_NetFFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					case IDR_SMS4DCTYPE50 :	((CPro_P1812_NetBFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;

					case IDR_SMS4DCTYPE51 :	((CPro_P526V14_LinkFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;
					
					case IDR_SMS4DCTYPE17 :	((CAntennaFormFrm *)pParent)->SharedMenu()	= SharedMenu.m_hMenu;	break;	//98/05/06
				}//ID
			}//if
		}//while  viewpos 
	}//while  docpos

//    m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));
        //Update the other panes of status bar		
//    SendMessage(WM_SETMESSAGESTRING, (WPARAM)AFX_IDS_IDLEMESSAGE);
//    m_wndStatusBar.UpdateWindow();//Update 1st pane of status bar

	DefaultMenu.Detach();
	SharedMenu.Detach();
	
}



void CMainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
	CFrameWnd::GetMessageString(nID, rMessage);

	CString str = rMessage;
	CString str1 =   (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(str)));
	rMessage = str1;
}

#define _countof(array) (sizeof(array)/sizeof(array[0]))
BOOL CMainFrame::OnToolTipText(UINT nID, NMHDR* pNMHDR,  LRESULT*pResult)
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
