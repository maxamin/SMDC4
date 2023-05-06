#if !defined(AFX_MAINMAPVIEW_H__C7BB56D6_A8EE_4212_ADC1_8F9D060C6A95__INCLUDED_)
#define AFX_MAINMAPVIEW_H__C7BB56D6_A8EE_4212_ADC1_8F9D060C6A95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainMapView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainMapView view

class CMainMapView : public CView
{
protected:
	CMainMapView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMainMapView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainMapView)
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
	virtual ~CMainMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainMapView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCountry();
	afx_msg void OnUpdateCountry(CCmdUI* pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnRefresh();
	afx_msg void OnCountryList();
	afx_msg void OnOptionBorderstyle();
	afx_msg void OnOptionFillmode();
	afx_msg void OnUpdateOptionFillmode(CCmdUI* pCmdUI);
	afx_msg void OnOptionBackgroundmap();
	afx_msg void OnUpdateOptionBackgroundmap(CCmdUI* pCmdUI);
	afx_msg void OnDem();
	afx_msg void OnDrawBox();
	afx_msg void OnUpdateDrawBox(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int rgnI ,conI ,m_LineWidth ,m_LineStyle , HScrollpos,VScrollpos , rgnIndex[286];
	double latO1 ,  latO2 ,lonO1 ,  lonO2;
	double DlatO1 ,  DlatO2 ,DlonO1 ,  DlonO2;
	CRgn rgn[286];
	CString m_bToolBarDraw , country[286] , countryPath[286];
	COLORREF RGBt[286]  , m_LineColor;
	BOOL m_bLPressed,m_CONPressed,m_Backgroundmap , m_FillMode;
	CPoint m_stBoxPoint , m_enBoxPoint,m_stBoxPoint1 , m_enBoxPoint1;
	LPPICTURE gpPicture1;
	CRect m_rcPrintRect;

	double lonlim1[286],lonlim2[286],latlim1[286],latlim2[286];

	void DrawVector(CDC *pDC,CString Vector_filepath,CRgn *rgn1,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID,
		BOOL nMode=false,COLORREF flColor=RGB(255,255,255),int alpha=50);

	void DrawVectorN(CDC *pDC,int Vector_no,CRgn *rgn1,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID,
		BOOL nMode=false,COLORREF flColor=RGB(255,255,255),int alpha=50);


	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt);
		int AxesW,AxesH,AxesT,AxesL;

	void Point2LatLon(CPoint PointSt,double *lat_deg,double *lon_deg) ;

	void LoadPictureFile1(LPCTSTR szFile,LPPICTURE *gpPictureXY1);

	void LoadPictureFile2();

	void RectInRegionVec(double xlatO1 ,double xlatO2 ,double xlonO1 ,double xlonO2) ;
	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) ;

	void OnFilePrintPreview() ;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINMAPVIEW_H__C7BB56D6_A8EE_4212_ADC1_8F9D060C6A95__INCLUDED_)
