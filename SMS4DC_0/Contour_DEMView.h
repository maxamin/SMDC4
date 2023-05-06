#if !defined(AFX_CONTOUR_DEMVIEW_H__B21B6C3A_4FF4_49C7_81D1_A140804DE037__INCLUDED_)
#define AFX_CONTOUR_DEMVIEW_H__B21B6C3A_4FF4_49C7_81D1_A140804DE037__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Contour_DEMView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMView view
#include "Contour_DEMDoc.h"

class CContour_DEMView : public CView
{
protected:
	CContour_DEMView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CContour_DEMView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContour_DEMView)
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
	virtual ~CContour_DEMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CContour_DEMView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOptionContour();
	afx_msg void OnTopo0();
	afx_msg void OnUpdateTopo0(CCmdUI* pCmdUI);
	afx_msg void OnJet();
	afx_msg void OnUpdateJet(CCmdUI* pCmdUI);
	afx_msg void OnShowLegend();
	afx_msg void OnUpdateShowLegend(CCmdUI* pCmdUI);
	afx_msg void OnTopo1();
	afx_msg void OnUpdateTopo1(CCmdUI* pCmdUI);
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnPink();
	afx_msg void OnUpdatePink(CCmdUI* pCmdUI);
	afx_msg void OnCopper();
	afx_msg void OnUpdateCopper(CCmdUI* pCmdUI);
	afx_msg void OnGlobe();
	afx_msg void OnUpdateGlobe(CCmdUI* pCmdUI);
	afx_msg void OnToolsNormalize();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDatabaseDisplayselectedstations();
	afx_msg void OnToolsSymbolattribute();
	afx_msg void OnDatabaseRemovestationsfromdisplay();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnFilePrintPreview();
private:
	int old_cx,old_cy;
	int new_cx,new_cy;
	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) ;
	int Contour(double y,double MinV,double MaxV,int nL) ;
	int m_level;
	BOOL m_LegendFlag;
	double RoundBUF_Hg(double xps,double yps) ;
	void LegendLOC(CDC* pDC) ;
	int m_x1L,m_y1L,m_x0L,m_y0L;
	BOOL m_bLPressed;
	BOOL m_bLSelect;
	CRect m_rcPrintRect;

	double *Lat_ST,*Lon_ST;
	CString *Name_ST;
	int Num_ST;
	void DrawSymboleStation(CDC* pDC,double lats,double lons,COLORREF color1,int len1);
	COLORREF m_SymbolColor;
	COLORREF m_SymbolTextColor;
	int m_SymbolSize;
	void TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor=RGB(0,0,127),
			int Escapement=0,
			int nHeight=12,int nWidth=0,int FontWeight=FW_BOLD,CString FontName="Arial"); 
	CString GetFld(CString Src,int N);
	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
	BOOL m_IsPrinting;
//	int new_cx1,new_cy1,new_cx2,new_cy2;
	int m_pscale;
	void AddStation_disp(double lat1,double lon1,CString name1);

	int m_x1,m_y1,m_x2,m_y2;

	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	void OnDraw4(CDC* pDC);		//98/01/25
	double RoundBUF_Hg0(double xps,double yps);	//98/01/31 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTOUR_DEMVIEW_H__B21B6C3A_4FF4_49C7_81D1_A140804DE037__INCLUDED_)
