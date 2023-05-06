// ThalesDrawView.h : interface of the CThalesDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THALESDRAWVIEW_H__3BC1689D_C03E_4F52_B9E9_6DFD83892A10__INCLUDED_)
#define AFX_THALESDRAWVIEW_H__3BC1689D_C03E_4F52_B9E9_6DFD83892A10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CThalesDrawView : public CView
{
protected: // create from serialization only
	CThalesDrawView();
	DECLARE_DYNCREATE(CThalesDrawView)

// Attributes
public:
	CThalesDrawDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThalesDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThalesDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CThalesDrawView)
	afx_msg void OnFileOpen();
	afx_msg void OnToolsModeBarchart();
	afx_msg void OnUpdateToolsModeBarchart(CCmdUI* pCmdUI);
	afx_msg void OnToolsModeLine();
	afx_msg void OnUpdateToolsModeLine(CCmdUI* pCmdUI);
	afx_msg void OnTools3d();
	afx_msg void OnUpdateTools3d(CCmdUI* pCmdUI);
	afx_msg void OnTools2dfreqvalue();
	afx_msg void OnUpdateTools2dfreqvalue(CCmdUI* pCmdUI);
	afx_msg void OnTools2dtimevalue();
	afx_msg void OnUpdateTools2dtimevalue(CCmdUI* pCmdUI);
	afx_msg void OnTOOLSGrid();
	afx_msg void OnUpdateTOOLSGrid(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONShowLegend();
	afx_msg void OnUpdateBUTTONShowLegend(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONLinewidthP();
	afx_msg void OnUpdateBUTTONLinewidthP(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONLinewidthN();
	afx_msg void OnUpdateBUTTONLinewidthN(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONTimeSelect();
	afx_msg void OnUpdateBUTTONTimeSelect(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONFrqSelect();
	afx_msg void OnUpdateBUTTONFrqSelect(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONpolar();
	afx_msg void OnUpdateBUTTONpolar(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapTopo0();
	afx_msg void OnUpdateToolsColormapTopo0(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapTopo1();
	afx_msg void OnUpdateToolsColormapTopo1(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapJet();
	afx_msg void OnUpdateToolsColormapJet(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapGray();
	afx_msg void OnUpdateToolsColormapGray(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapPink();
	afx_msg void OnUpdateToolsColormapPink(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapCopper();
	afx_msg void OnUpdateToolsColormapCopper(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapGlobe();
	afx_msg void OnUpdateToolsColormapGlobe(CCmdUI* pCmdUI);
	afx_msg void OnToolsBackgroundcolor();
	afx_msg void OnToolsAxiscolor();
	afx_msg void OnToolsTextcolor();
	afx_msg void OnToolsValueOccupancyrate();
	afx_msg void OnUpdateToolsValueOccupancyrate(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueGlobalrate();
	afx_msg void OnUpdateToolsValueGlobalrate(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueMaxlevel();
	afx_msg void OnUpdateToolsValueMaxlevel(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueAvelevel();
	afx_msg void OnUpdateToolsValueAvelevel(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueBearingDirection();
	afx_msg void OnUpdateToolsValueBearingDirection(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueBearingQuality();
	afx_msg void OnUpdateToolsValueBearingQuality(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueBandwidthBetamethod();
	afx_msg void OnUpdateToolsValueBandwidthBetamethod(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueBandwidthXdbmethod();
	afx_msg void OnUpdateToolsValueBandwidthXdbmethod(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueModulationrate();
	afx_msg void OnUpdateToolsValueModulationrate(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueFrequencydrifting();
	afx_msg void OnUpdateToolsValueFrequencydrifting(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueFieldstrength();
	afx_msg void OnUpdateToolsValueFieldstrength(CCmdUI* pCmdUI);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void Get_OccFile(); 

	CStringArray m_data;
	CStringArray m_TimeBracketList;
	CStringArray m_Freq;
	CStringArray m_FreqUniq;

	CArray<double,double>m_OccRate;
	CArray<double,double>m_Time;
	CArray<double,double>m_GlobalRate;
	CArray<double,double>m_AveLevel;
	CArray<double,double>m_MaxLevel;

	double m_Vmin, m_Vmax;
	double m_MaxLevel_min, m_MaxLevel_max;
	double m_Fmin, m_Fmax;	//Frequency
	double m_Tmin, m_Tmax;	//Time

	CArray<double,double>m_AzimRES;
	CArray<double,double>m_DFqRES;
	CArray<double,double>m_BWbRES;
	CArray<double,double>m_BWxRES;
	CArray<double,double>m_ModulationRES;
	CArray<double,double>m_FreDriftRES;
	CArray<double,double>m_FieldStRES;

	double m_AzimRESmin, m_AzimRESmax;
	double m_DFqRESmin, m_DFqRESmax;
	double m_BWbRESmin, m_BWbRESmax;
	double m_BWxRESmin, m_BWxRESmax;
	double m_ModulationRESmin, m_ModulationRESmax;
	double m_FreDriftRESmin, m_FreDriftRESmax;
	double m_FieldStRESmin, m_FieldStRESmax;

	CStringArray m_TimeListRESuniq;
	CStringArray m_TimeListREStotal;

	long m_Row, m_Col;

	CRect m_rcPrintRect , m_rect;
	double pi , Fi , m_dTime;
	int  m_deptX , m_deptY , m_offset;

	CPoint m_pointOf , m_pointRBf, m_pointLTf , m_pointRTf , m_pointOb , m_pointRBb , m_pointRTb , m_pointLTb;
	CPoint m_pointY , m_pointX;

	double Dist2Point(CPoint point1, CPoint point2);

	COLORREF m_BackgroundClr , m_AxisClr , m_TextClt;
	BOOL m_ready;
	int m_ValueType;
	int m_3D2D;
	int m_mode;
	void XY_axis_3D(CDC* pDC);
	void XY_tick_3D(CDC* pDC, int ListType);
	void Draw_Data_3D(CDC* pDC, int ListType, int nStyle, int nWidth, COLORREF crColor , int mode); 
	void Draw_Text(CDC* pDC,int x, int y,CString str,
							COLORREF FontColor=RGB(0,0,0),int Escapement=0,int nHeight=12,int nWidth=0,
							int FontWeight=FW_NORMAL,int bWidth = 140, int bAlin = DT_RIGHT, CString FontName=_T("Arial"),BOOL flag=FALSE);

	void Draw_Line(CDC* pDC,CPoint point1, CPoint point2, int nStyle=PS_SOLID , int nWidth=1,COLORREF crColor=RGB(0,0,0));

	CPoint Point3D(double f,double t,double v);
	BOOL m_grid;
	CString m_Start, m_Stop , m_PathName;

	CPoint Data2Point_3D(int ListType, double freq, double tim, double value) ;
	int Contour(double y,double MinV,double MaxV,int nL); 
	void ColorMap(CString type);
	COLORREF RGBt[256];
	CString m_colormaptype;

	BOOL IsWin2000();
	void Reset_Data();

	void XY_axis_2D(CDC* pDC);
	void XY_tick_2Dtv(CDC* pDC, int ListType);
	void Draw_Data_2Dtv(CDC* pDC,int ListType,
									  int nStyle , int nWidth, COLORREF crColor , int mode) ;
	CPoint Data2Point_2Dtv(int ListType, double tim, double value); 

	void Draw_Data_2Dfv(CDC* pDC, int ListType,	
									  int nStyle , int nWidth, COLORREF crColor , int mode); 
	CPoint Data2Point_2Dfv(int ListType, double freq, double value); 
	void XY_tick_2Dfv(CDC* pDC, int ListType);

	void LegendLOC(CDC* pDC);
	BOOL m_LegendFlag;

	CTime Str2DateTime(CString str);


	CString m_FreqSelect;
	double m_TimeSelect;
	CString m_TimeSelectStart;
	CString m_TimeSelectStop;

	int m_LineWidth;

	CString ListType2Ylable(int ValueType) ;
	void ListType2Value(int ValueType, double *Vmin, double *Vmax);
	double ListType2CurrentIndex(int ListType , int i); 


	BOOL m_OccResFlag;
	void Get_ResFile(); 

	CString m_TimeListREScomp;

	void Draw_Data_3D_RES(CDC* pDC, int ListType, int nStyle , int nWidth, COLORREF crColor , int mode); 

	CTime Str2DateTimeRES(CString str);
	int nTime,nFreq,nAzimRES,nDFqRES,nBWbRES,nBWxRES,nModulationRES,nFreDriftRES,nFieldStRES;
	int Defult_ValueType();

	void SetFrqUniq();

	void Set_MinMaxLimit0(); 
	void Set_MinMaxLimit1(int ListType); 

	void SaveDesktop(CDC *pDC, CString FileName); 
	void CDCToBmp24(CDC *pDC, CString fileOUT);
	CString m_AppPath;
	CString	m_TxName, m_MOlon_degStr, m_MOlat_degStr;

	void TranslateMenu(CMenu *pMenu);
	CString GetTranslatedString(CString strOriginal);
	void ChangeMenuLang(); 
	CString m_Lang;
			
	//CString _Z(CString s){return (((CArgusWFdllApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
	CString _Z(CString s){ return (GetTranslatedString(_T(s))); };

	int DP_LP(CDC* pDC, int nH_DP);	//1400/04/20
	void initDP_LP(CDC * pDC);
	int m_fontH2, m_fontH6, m_fontH12, m_fontH14, m_fontH20, 
		m_fontH24, m_fontH28, m_fontH30, m_fontH40, m_fontH44, m_fontH100, m_fontH150, m_fontH46, m_fontH48
		,m_fontH220, m_fontH350, m_fontH340, m_fontH10, m_fontH460, m_fontH250, m_fontH500, m_fontH600, m_fontH140,
		m_fontH50, m_fontH200, m_fontH421;

};

#ifndef _DEBUG  // debug version in ThalesDrawView.cpp
inline CThalesDrawDoc* CThalesDrawView::GetDocument()
   { return (CThalesDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THALESDRAWVIEW_H__3BC1689D_C03E_4F52_B9E9_6DFD83892A10__INCLUDED_)
