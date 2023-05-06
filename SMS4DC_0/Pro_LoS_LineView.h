#if !defined(AFX_PRO_LOS_LINEVIEW_H__1E22ABC5_3B5D_4CF2_B333_0CBF118EF92B__INCLUDED_)
#define AFX_PRO_LOS_LINEVIEW_H__1E22ABC5_3B5D_4CF2_B333_0CBF118EF92B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_LoS_LineView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineView view

class CPro_LoS_LineView : public CView
{
protected:
	CPro_LoS_LineView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_LoS_LineView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_LoS_LineView)
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
	virtual ~CPro_LoS_LineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_LoS_LineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOptionChangeparameters();
	afx_msg void OnRefresh();
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
	double m_ytickMIN  ,   m_ytickSTEP  ,  m_ytickMAX;
	double InterpXY(double *D0,double *E0,double d,int num);

private:
	CRect m_rcPrintRect;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_LOS_LINEVIEW_H__1E22ABC5_3B5D_4CF2_B333_0CBF118EF92B__INCLUDED_)
