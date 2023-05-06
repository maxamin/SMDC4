#if !defined(AFX_PRO_LOS_AREAVIEW_H__810798D7_5AA6_4293_B1DB_CBB63DA7A486__INCLUDED_)
#define AFX_PRO_LOS_AREAVIEW_H__810798D7_5AA6_4293_B1DB_CBB63DA7A486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_LoS_AreaView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaView view

class CPro_LoS_AreaView : public CView
{
protected:
	CPro_LoS_AreaView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_LoS_AreaView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_LoS_AreaView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_LoS_AreaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_LoS_AreaView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnShowLegend();
	afx_msg void OnUpdateShowLegend(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnToolsGoogle();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnFilePrintPreview();
private:
	int old_cx,old_cy;
	int new_cx,new_cy;
	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) ;
	double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
//	CLegendDLG *m_pLegendDLGModeless; 
//	BOOL m_LegendFlag;

	BOOL m_LegendFlag;
	void LegendLOC(CDC* pDC) ;
	int m_x1L,m_y1L,m_x0L,m_y0L;
	BOOL m_bLPressed;
	BOOL m_bLSelect;
	CRect m_rcPrintRect;
	void CaptureDC();
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

double CPro_LoS_AreaView::RoundBUF_E_A(double xps,double yps, int W, int H, double *E_A);
double CPro_LoS_AreaView::RoundBUF_E_A(double xps,double yps, int W, int H, _int16 *E_A);
int CPro_LoS_AreaView::Round(double x);

	void OnDraw4(CDC* pDC);		//98/01/25
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_LOS_AREAVIEW_H__810798D7_5AA6_4293_B1DB_CBB63DA7A486__INCLUDED_)
