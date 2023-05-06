#if !defined(AFX_INT_BT2BT_FREEVIEW_H__6E35E55B_3B99_4A7B_BF40_F1F3BD5C84E5__INCLUDED_)
#define AFX_INT_BT2BT_FREEVIEW_H__6E35E55B_3B99_4A7B_BF40_F1F3BD5C84E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_BT2BT_FreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_BT2BT_FreeView view

class CInt_BT2BT_FreeView : public CView
{
protected:
	CInt_BT2BT_FreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInt_BT2BT_FreeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_BT2BT_FreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInt_BT2BT_FreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CInt_BT2BT_FreeView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTopo0();
	afx_msg void OnUpdateTopo0(CCmdUI* pCmdUI);
	afx_msg void OnTopo1();
	afx_msg void OnUpdateTopo1(CCmdUI* pCmdUI);
	afx_msg void OnJet();
	afx_msg void OnUpdateJet(CCmdUI* pCmdUI);
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopper(CCmdUI* pCmdUI);
	afx_msg void OnCopper();
	afx_msg void OnGlobe();
	afx_msg void OnUpdateGlobe(CCmdUI* pCmdUI);
	afx_msg void OnPink();
	afx_msg void OnUpdatePink(CCmdUI* pCmdUI);
	afx_msg void OnShowLegend();
	afx_msg void OnUpdateShowLegend(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnToolsEu();
	afx_msg void OnUpdateToolsEu(CCmdUI* pCmdUI);
	afx_msg void OnToolsNormalize();
	afx_msg void OnUpdateToolsNormalize(CCmdUI* pCmdUI);
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
	
	BOOL m_LegendFlag;

	int Contour(double y,double MinV,double MaxV,int nL);
	int m_CoveredPix;

	void LegendLOC(CDC* pDC) ;
	void AreaShow(CDC* pDC) ;
	int m_x1L,m_y1L,m_x0L,m_y0L;
	BOOL m_bLPressed;
	BOOL m_bLSelect;
	CRect m_rcPrintRect;

	CString str_rep(CString str,int num);
	void OnDrawVector(CString sFile) ;
	void DrawVector(CDC *pDC,CString Vector_filepath,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID,
		BOOL nMode=false,COLORREF flColor=RGB(255,255,255),int alpha=50);
	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
	struct POLYGONvec
	{
		CString PathNameVec;
		CString FileNameVec;
		int nWidthVec;
		COLORREF crColorVec;
		int nStyleVec;
		BOOL nModeVec;
		COLORREF flColorVec;
		int alphaVec;
	}m_POLY[100]; 
	int m_POLYnum;

	int m_x1,m_y1,m_x2,m_y2;

	BOOL m_EuFlag;
	void LegendLOCEu(CDC* pDC) ;
	void CaptureDC();
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	int Round(double x) ;
	void OnDraw4(CDC* pDC);		//98/01/25
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_BT2BT_FREEVIEW_H__6E35E55B_3B99_4A7B_BF40_F1F3BD5C84E5__INCLUDED_)
