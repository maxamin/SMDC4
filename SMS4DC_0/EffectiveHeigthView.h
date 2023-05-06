#if !defined(AFX_EFFECTIVEHEIGTHVIEW_H__E340557F_D103_4762_BBEA_2BC360F1CB68__INCLUDED_)
#define AFX_EFFECTIVEHEIGTHVIEW_H__E340557F_D103_4762_BBEA_2BC360F1CB68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EffectiveHeigthView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthView view

class CEffectiveHeigthView : public CView
{
protected:
	CEffectiveHeigthView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEffectiveHeigthView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEffectiveHeigthView)
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
	virtual ~CEffectiveHeigthView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CEffectiveHeigthView)
	afx_msg void OnToolsTextcolor();
	afx_msg void OnToolsLinecolor();
	afx_msg void OnTopo0();
	afx_msg void OnUpdateTopo0(CCmdUI* pCmdUI);
	afx_msg void OnTopo1();
	afx_msg void OnUpdateTopo1(CCmdUI* pCmdUI);
	afx_msg void OnJet();
	afx_msg void OnUpdateJet(CCmdUI* pCmdUI);
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnPink();
	afx_msg void OnUpdatePink(CCmdUI* pCmdUI);
	afx_msg void OnCopper();
	afx_msg void OnUpdateCopper(CCmdUI* pCmdUI);
	afx_msg void OnGlobe();
	afx_msg void OnUpdateGlobe(CCmdUI* pCmdUI);
	afx_msg void OnToolsBackground();
	afx_msg void OnUpdateToolsBackground(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnToolsSaveeffectiveheight();
	afx_msg void OnHeffdataSaveheff();
	afx_msg void OnUpdateToolsSaveeffectiveheight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHeffdataSaveheff(CCmdUI* pCmdUI);
	afx_msg void OnToolsTxt();
	afx_msg void OnHeffdataTxt();
	afx_msg void OnToolsEditdatabase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt);
	void TextDraw(CDC* pDC,int x, int y,CString str,
						COLORREF FontColor=RGB(0,0,0),
						int Escapement=0,int nHeight=12,int nWidth=0,
						int FontWeight=FW_NORMAL,CString FontName="Arial") ;
	double Point2Hg(CPoint point1);
	int Round(double x);
	double Points2HgAvr(CPoint point1 , CPoint point2) ;
	COLORREF m_TextColor;
	COLORREF m_LineColor;
	void Point2Stretch(CPoint PointSt1,CPoint *PointSt2); 
	void OnFilePrintPreview();
	void OnFilePrint();

	CRect m_rcPrintRect;
	int m_AxesT,m_AxesH,m_AxesW,m_AxesL;
	bool m_background;
	double *m_Heff_m;
	bool m_printstate;

	void Delete_set(long ID) ;
	int m_step;
	int m_num;

	void Point2Stretch1(CPoint PointSt1,CPoint *PointSt2); 
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EFFECTIVEHEIGTHVIEW_H__E340557F_D103_4762_BBEA_2BC360F1CB68__INCLUDED_)
