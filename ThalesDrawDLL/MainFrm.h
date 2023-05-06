// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__7D60F55E_1E5E_40BB_9FC1_119B911354D9__INCLUDED_)
#define AFX_MAINFRM_H__7D60F55E_1E5E_40BB_9FC1_119B911354D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


public:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar    m_ToolBarDATABASE;
	CToolBar    m_ToolBarMainMap;
	CToolBar    m_ToolBarIDWMMap;
	CToolBar    m_ToolBarSRVtable;
	CToolBar    m_ToolBarRGNtable;
	CToolBar    m_ToolBarALLplan;

	BOOL    m_wndToolBar_Flag;
	BOOL    m_ToolBarDATABASE_Flag;
	BOOL    m_ToolBarMainMap_Flag;
	BOOL    m_ToolBarIDWMMap_Flag;
	BOOL    m_ToolBarSRVtable_Flag;
	BOOL    m_ToolBarRGNtable_Flag;
	BOOL    m_ToolBarALLplan_Flag;
	void ToolbarCheck()
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
		;
	void ToolbarSet() 
	{
	ShowControlBar(&m_wndToolBar,		m_wndToolBar_Flag, FALSE);
	ShowControlBar(&m_ToolBarALLplan,	m_ToolBarALLplan_Flag, FALSE);
	ShowControlBar(&m_ToolBarRGNtable,	m_ToolBarRGNtable_Flag, FALSE);
	ShowControlBar(&m_ToolBarSRVtable,	m_ToolBarSRVtable_Flag, FALSE);
	ShowControlBar(&m_ToolBarIDWMMap,	m_ToolBarIDWMMap_Flag, FALSE);
	ShowControlBar(&m_ToolBarMainMap,	m_ToolBarMainMap_Flag, FALSE);
	ShowControlBar(&m_ToolBarDATABASE,	m_ToolBarDATABASE_Flag, FALSE);
	};

	void HideToolBars()
	{
	ShowControlBar(&m_ToolBarALLplan, FALSE, FALSE);
	ShowControlBar(&m_ToolBarRGNtable, FALSE, FALSE);
	ShowControlBar(&m_ToolBarSRVtable, FALSE, FALSE);
	ShowControlBar(&m_ToolBarIDWMMap, FALSE, FALSE);
	ShowControlBar(&m_ToolBarMainMap, FALSE, FALSE);
	ShowControlBar(&m_ToolBarDATABASE, FALSE, FALSE);
}	
		;

	int OnCreateToolBarALLplan();
	CComboBox m_ctlRegion;
	CStatic m_Static_Frq;
	CEdit m_ctlEdit_Flo;
	CEdit m_ctlEdit_Fhi;
	CComboBox m_ctlUnit;
	CComboBox m_ctlScale;
	CButton m_ctlapply;
	CStatic m_Static_S5;
	CComboBox m_ctlS5;

protected:  // control bar embedded members
	//CStatusBar  m_wndStatusBar;
	//CToolBar    m_wndToolBar;
	UINT        m_nTimer;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnToolbarmenuDatabasetoolbar();
	afx_msg void OnUpdateToolbarmenuDatabasetoolbar(CCmdUI* pCmdUI);
	afx_msg void OnToolbarmenuMainmaptoolbar();
	afx_msg void OnUpdateToolbarmenuMainmaptoolbar(CCmdUI* pCmdUI);
	afx_msg void OnToolbarmenuDemtoolbar();
	afx_msg void OnUpdateToolbarmenuDemtoolbar(CCmdUI* pCmdUI);
	afx_msg void OnToolbarmenuIdwmmap();
	afx_msg void OnUpdateToolbarmenuIdwmmap(CCmdUI* pCmdUI);
	afx_msg void OnToolbarmenuService();
	afx_msg void OnUpdateToolbarmenuService(CCmdUI* pCmdUI);
	afx_msg void OnToolbarmenuRegiontoolbar();
	afx_msg void OnUpdateToolbarmenuRegiontoolbar(CCmdUI* pCmdUI);
	afx_msg void OnToolbarmenuAllocationplantoolbar();
	afx_msg void OnUpdateToolbarmenuAllocationplantoolbar(CCmdUI* pCmdUI);
	afx_msg void OnToolbarmenuHidealltoolbars()
		{
	HideToolBars();	
	ShowControlBar(&m_wndToolBar, FALSE, FALSE);
}
		;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7D60F55E_1E5E_40BB_9FC1_119B911354D9__INCLUDED_)
