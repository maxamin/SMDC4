#if !defined(AFX_BASEGLVIEW_H__5F7261BA_35E3_4607_B67A_91C95A06F7F7__INCLUDED_)
#define AFX_BASEGLVIEW_H__5F7261BA_35E3_4607_B67A_91C95A06F7F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseGLView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBaseGLView view

class CBaseGLView : public CView
{
protected:
	CBaseGLView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBaseGLView)

// Attributes
public:

// Operations
public:
	void StartStockDListDef();
	void EndStockListDef();	
	void DrawStockDispLists();
	void ClearStockDispLists();

	void BeginGLCommands();
	void EndGLCommands();

	virtual void OnCreateGL(); 
	virtual void OnSizeGL(int cx, int cy); 
	virtual void OnDrawGL(); 


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseGLView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBaseGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CBaseGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CDC* m_pCDC;
	HGLRC m_hRC;	
	HCURSOR m_hMouseCursor;	
	double m_dAspectRatio;    
	int m_DispListVector[20];
	BOOL m_bInsideDispList;
	BOOL m_bExternGLCall;
	BOOL m_bExternDispListCall;
	BOOL bSetupPixelFormat();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEGLVIEW_H__5F7261BA_35E3_4607_B67A_91C95A06F7F7__INCLUDED_)
