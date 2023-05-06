#if !defined(AFX_PRO_FREE_POLYGONVIEW_H__A3D0A95A_51B4_4826_9B00_7C0A593DBEA7__INCLUDED_)
#define AFX_PRO_FREE_POLYGONVIEW_H__A3D0A95A_51B4_4826_9B00_7C0A593DBEA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_Free_PolygonView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_PolygonView view

class CPro_Free_PolygonView : public CView
{
protected:
	CPro_Free_PolygonView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_Free_PolygonView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_Free_PolygonView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_Free_PolygonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPro_Free_PolygonView)
	afx_msg void OnRefresh();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnFilePrintPreview();
public:
	int m_AxesT,m_AxesH,m_AxesW,m_AxesL;
	int Np;
	void Plot(CDC* pDC,double *xi, double *yi,int Np,
						double xiMIN,double xiMAX,double yiMIN,double yiMAX,
						int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID,
						int nMode=0,COLORREF flColor=RGB(255,255,255));

	void TextDraw(CDC* pDC,int x, int y,CString str,
							COLORREF FontColor=RGB(0,0,0),
							int Escapement=0,int nHeight=12,int nWidth=0,
							int FontWeight=FW_NORMAL,CString FontName="Arial");

	void LineDraw(CDC* pDC,int x1, int y1,int x2, int y2,
						int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID);

	double Distance_km(double lat1,double lon1,double lat2,double lon2);
	void Xtick(CDC* pDC,double xiMIN,double xiMAX);
	void YtickL(CDC* pDC,double yiMIN,double yiMAX);
	void YtickR(CDC* pDC,double yiMIN,double yiMAX);
	double MinValue(double *xi,int N);
	double MaxValue(double *xi,int N);
	bool m_bLPressed;
	CPoint m_stPoint;
	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU);
	int Round(double x);
	double Interp(double *hi , int Np , double x);

	void PlotPoint(CDC* pDC,double *xi, double *yi,int N,
						double xiMIN,double xiMAX,double yiMIN,double yiMAX,
						int nWidth,COLORREF crColor, int nStyle, int nRadius,COLORREF flColor) ;
	double InterpXY(double *D0,double *E0,double d,int num);
private:
	CRect m_rcPrintRect;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_FREE_POLYGONVIEW_H__A3D0A95A_51B4_4826_9B00_7C0A593DBEA7__INCLUDED_)
