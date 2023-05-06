#if !defined(AFX_PROFILEVIEW_H__B4F84B99_5FD3_424A_B213_B874C03BBA0D__INCLUDED_)
#define AFX_PROFILEVIEW_H__B4F84B99_5FD3_424A_B213_B874C03BBA0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfileView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfileView view
#include "SMS4DCDoc.h"
#include "SMS4DCView.h"

class CProfileView : public CView
{
protected:
	CProfileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProfileView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProfileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CProfileView)
	afx_msg void OnRefresh();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOptionChangekfactor();
	afx_msg void OnOptionChangefresnelzoneparameters();
	afx_msg void OnUpdateOptionChangefresnelzoneparameters(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnFilePrintPreview();
public:
	double *m_hi;
	double *m_di;
	double Hmin;
	int Np;
	void TextDraw(CDC* pDC,int x, int y,CString str,
							COLORREF FontColor=RGB(0,0,0),
							int Escapement=0,int nHeight=12,int nWidth=0,
							int FontWeight=FW_NORMAL,CString FontName="Arial") ;
	void LineDraw(CDC* pDC,int x1, int y1,int x2, int y2,
							int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID) ;
//	double m_kfactor;
	CString m_kfactor;
	bool m_bLPressed;
	CPoint m_stPoint;
	int m_AxesT,m_AxesH,m_AxesW,m_AxesL;

	void Plot(CDC* pDC,double *xi, double *yi,int Np,
		double xiMIN,double xiMAX,double yiMIN,double yiMAX,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID,
		int nMode=0,COLORREF flColor=RGB(255,255,255)) ;

	double m_ytickMIN  ,   m_ytickSTEP  ,  m_ytickMAX;

	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU);
	void YtickL(CDC* pDC,double yiMIN,double yiMAX);
	void Xtick(CDC* pDC,double xiMIN,double xiMAX);
	double MinValue(double *xi,int N); 
	double MaxValue(double *xi,int N); 
	double InterpXY(double *D0,double *E0,double d,int num);


	void DrawAntSymbol(CDC* pDC,double xi, double yi,
		double xiMIN,double xiMAX,double yiMIN,double yiMAX,
		COLORREF crColor=RGB(0,0,0), int nMode=1) ;
	int		m_Fresnel;
	double	m_FrqMHz;
	double	m_RxH;
	double	m_TxH;
	double atof_kfactor(CString k1); 

private:
	CRect m_rcPrintRect;
	CSMS4DCView *m_pView;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	int DP_LP(CDC* pDC, int nH_DP);	//97/10/12
	void initDP_LP(CDC * pDC);
	int m_fontH2, m_fontH6, m_fontH12, m_fontH14, m_fontH20, 
		m_fontH24, m_fontH28, m_fontH30, m_fontH40, m_fontH44, m_fontH100, m_fontH150, m_fontH46;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEVIEW_H__B4F84B99_5FD3_424A_B213_B874C03BBA0D__INCLUDED_)
