#if !defined(AFX_IDWMMAPVIEW_H__96B63E20_9142_473A_9247_2A9CF25E186F__INCLUDED_)
#define AFX_IDWMMAPVIEW_H__96B63E20_9142_473A_9247_2A9CF25E186F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IDWMMapView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapView view

class CIDWMMapView : public CView
{
protected:
	CIDWMMapView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIDWMMapView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDWMMapView)
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
	virtual ~CIDWMMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CIDWMMapView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnRefresh();
	afx_msg void OnDrawBox();
	afx_msg void OnUpdateDrawBox(CCmdUI* pCmdUI);
	afx_msg void OnCountryList();
	afx_msg void OnDem();
	afx_msg void OnOptionBackgroundcolor();
	afx_msg void OnUpdateOptionBackgroundcolor(CCmdUI* pCmdUI);
	afx_msg void OnOptionBackgroundmap();
	afx_msg void OnUpdateOptionBackgroundmap(CCmdUI* pCmdUI);
	afx_msg void OnOptionBorder();
	afx_msg void OnUpdateOptionBorder(CCmdUI* pCmdUI);
	afx_msg void OnOptionBorderstyle();
	afx_msg void OnUpdateOptionBorderstyle(CCmdUI* pCmdUI);
	afx_msg void OnOptionCoast();
	afx_msg void OnUpdateOptionCoast(CCmdUI* pCmdUI);
	afx_msg void OnOptionCoaststyle();
	afx_msg void OnUpdateOptionCoaststyle(CCmdUI* pCmdUI);
	afx_msg void OnOptionIsland();
	afx_msg void OnUpdateOptionIsland(CCmdUI* pCmdUI);
	afx_msg void OnOptionIslandstyle();
	afx_msg void OnUpdateOptionIslandstyle(CCmdUI* pCmdUI);
	afx_msg void OnOptionLake();
	afx_msg void OnUpdateOptionLake(CCmdUI* pCmdUI);
	afx_msg void OnOptionLakestyle();
	afx_msg void OnUpdateOptionLakestyle(CCmdUI* pCmdUI);
	afx_msg void OnOptionIturegions();
	afx_msg void OnUpdateOptionIturegions(CCmdUI* pCmdUI);
	afx_msg void OnOptionIturegionsstyle();
	afx_msg void OnUpdateOptionIturegionsstyle(CCmdUI* pCmdUI);
	afx_msg void OnOptionCoastzones();
	afx_msg void OnUpdateOptionCoastzones(CCmdUI* pCmdUI);
	afx_msg void OnOptionCoastzonesstyle();
	afx_msg void OnUpdateOptionCoastzonesstyle(CCmdUI* pCmdUI);
	afx_msg void OnOptionPropagationzonesSt61();
	afx_msg void OnUpdateOptionPropagationzonesSt61(CCmdUI* pCmdUI);
	afx_msg void OnOptionPropagationzonesGe84();
	afx_msg void OnUpdateOptionPropagationzonesGe84(CCmdUI* pCmdUI);
	afx_msg void OnOptionPropagationzonesGe89();
	afx_msg void OnUpdateOptionPropagationzonesGe89(CCmdUI* pCmdUI);
	afx_msg void OnOptionPropagationzonesGe2004();
	afx_msg void OnUpdateOptionPropagationzonesGe2004(CCmdUI* pCmdUI);
	afx_msg void OnOptionPropagationzonesClearfromdisplay();
	afx_msg void OnOptionPropagationzonesstyle();
	afx_msg void OnUpdateOptionPropagationzonesstyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionPropagationzonesClearfromdisplay(CCmdUI* pCmdUI);
	afx_msg void OnOptionRrappendix7Earthstationselection();
	afx_msg void OnOptionRrappendix7Drawcontours();
	afx_msg void OnUpdateOptionRrappendix7Drawcontours(CCmdUI* pCmdUI);
	afx_msg void OnOptionRrappendix7Style();
	afx_msg void OnUpdateOptionRrappendix7Style(CCmdUI* pCmdUI);
	afx_msg void OnOptionRrappendix7Viewinputfile();
	afx_msg void OnOptionRrappendix7Viewoutputfile();
	afx_msg void OnOptionRrappendix7Viewoutputfile1();
	afx_msg void OnOptionRrappendix7Savevectors();
	afx_msg void OnUpdateOptionRrappendix7Savevectors(CCmdUI* pCmdUI);
	afx_msg void OnHelpManual();
	afx_msg void OnVectorsDrawfromfile();
	afx_msg void OnVectorsRemovefromdisplay();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnOptionFillcountries();
	afx_msg void OnUpdateOptionFillcountries(CCmdUI* pCmdUI);
	afx_msg void OnOptionRrappendix7gibc();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int HScrollpos,VScrollpos ;
	int m_LineWidthB ,m_LineStyleB ;
	int m_LineWidthC ,m_LineStyleC ;
	int m_LineWidthI ,m_LineStyleI ;
	int m_LineWidthL ,m_LineStyleL ;
	int m_LineWidthR ,m_LineStyleR ;
	int m_LineWidthO ,m_LineStyleO ;
	int m_LineWidthPR ,m_LineStylePR ;
	int m_LinePR;

	double  latO1 ,   latO2 , lonO1 ,   lonO2;
	double DlatO1 ,  DlatO2 ,DlonO1 ,  DlonO2;
	CString m_bToolBarDraw ;

	COLORREF m_LineColorB , m_LineColorC , m_LineColorI , m_LineColorL , m_LineColorR, m_LineColorO, m_LineColorPR , m_BKColor;
	BOOL m_bLPressed,m_CONPressed,m_Backgroundmap , m_FillMode;
	CPoint m_stBoxPoint , m_enBoxPoint,m_stBoxPoint1 , m_enBoxPoint1;
	LPPICTURE gpPicture1;
	CRect m_rcPrintRect;

	void DrawVectorM(CDC *pDC,char m_LineType,float RLONLL, float RLATLL, float RLONUR, float RLATUR,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID);

	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt);
		int AxesW,AxesH,AxesT,AxesL;
	void Point2LatLon(CPoint PointSt,double *lat_deg,double *lon_deg) ;
	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU);

	void LoadPictureFile1(LPCTSTR szFile,LPPICTURE *gpPictureXY1);
	void LoadPictureFile2();

	BOOL m_LineB,m_LineC,m_LineI,m_LineL,m_LineO,m_ITUR;
	CString conS;


	void DrawCoastalZone(CDC *pDC,char m_LineType,float RLONLL, float RLATLL, float RLONUR, float RLATUR,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID);

	int WarmColdSea(double RLON,double RLAT) ;
	void OnFilePrintPreview() ;

	void DrawVectorGE(CDC *pDC,int plan,float RLONLL, float RLATLL, float RLONUR, float RLATUR,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID);

	/////////////////APP7////////////////////
	int AP28_MakeTXT(CString PathFileName) ;

	long AP28_SRShor_elev(long ntc_id,float *azm,float *elev_ang,float *hor_dist) ;
	long AP28_SRSe_ant_elev(long ntc_id,float *elev_ang) ;
	long AP28_SRSfreq(long grp_id,double *freq_min,double *freq_max) ;
	void AP28_MakeUPD(CString FileName) ;
	void AP28_SendString(CString String);
	void AP28_ReadUPD() ;

	bool m_S7;
	long	m_CordDistI[1000][72],		
			m_CordDistII[1000][72],		
			m_CordDistI10[1000][72],	
			m_CordDistI20[1000][72],	
			m_CordDistI30[1000][72],	
			m_CordDistI40[1000][72],	
			m_CordDistI50[1000][72],	
			m_CordDistI60[1000][72],
			m_RowNum,m_ifrom,m_ito;

	CString m_strout,m_strA1[1000],m_strA8[1000];
	BOOL m_M1,m_M2,m_M1_10,m_M1_20,m_M1_30,m_M1_40,m_M1_50,m_M1_60;

	COLORREF m_LineColor7;
	int m_LineWidth7, m_LineStyle7;

	void AP28_DLG() ;
	void AP28_Affected_CTRY(CString *CTRYlist);
	void AP28_Draw(CDC *pDC);
	void AP28_Draw_0(CDC *pDC,CString Name,CString LatLon, long * dist,
					 	    int nWidth=2,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID) ;

	long AP28_SRSsrv_cls(long grp_id,CString *stn_cls) ;
	BOOL AP28_BandOverlap(double Fmin,double Fmax,double F1,double F2) ;
	int AP28_SRV(double Fmin,double Fmax,long grp_id,BOOL Manned,int *SRVtype) ;

	void DrawSymboleStation(CDC* pDC,double lats,double lons,
						COLORREF color1=RGB(0,0,127),int len1=6); 

	int AP28_Write_0(CString Name,CString LatLon, long * dist) ;

//	void VectorCountry(CDC *pDC,CString cty,int nWidth=3,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID) ;
	void VectorCountry(CDC *pDC,CString cty,BOOL mode=1 , COLORREF crColor=RGB(0,0,0), int nWidth=3, int nStyle=PS_SOLID) ;

	int nWidth1,nWidth2,nWidth3,nWidth4,nWidth5,nWidth6,nWidth7,nWidth8;
	COLORREF crColor1,crColor2,crColor3,crColor4,crColor5,crColor6,crColor7,crColor8;
	int nStyle1,nStyle2,nStyle3,nStyle4,nStyle5,nStyle6,nStyle7,nStyle8;

	void TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor=RGB(0,0,127),
			int Escapement=0,
			int nHeight=12,int nWidth=0,int FontWeight=FW_BOLD,CString FontName="Arial"); 

	void Rad2Str(float lonRAD,float latRAD,CString *lonSTR,CString *latSTR) ;

	void OnCountryDefault(CString Dctry,double *DefLat, double *DefLon) ;

	CString m_R1448Path;
	double m_zoomFactor;

	long ESantUser(long ntc_id, CString beam_name, CString emi_rcp, CString *OffAng, CString *AntGain);

/////////////////////////////
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

	void DrawVector(CDC *pDC,CString Vector_filepath,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID,
		int nMode=0,COLORREF flColor=RGB(255,255,255),int alpha=50);

	BOOL strCompare(CString sPath);
	void Vector2OnePoint(CString Vector_filepath);

	void ALLcountry(CDC * pDC);
	COLORREF RGBcountry(int n);
	BOOL m_ALLcountry;

	double m_stLat, m_enLat , m_stLon, m_enLon;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	void VectorsDrawfromfile(CString FilePath);
	double m_LatGIBC, m_LonGIBC;
	CString m_NameGIBC;
	BOOL m_flagGIBC;

	double pi, D2R;
	void CIDWMMapView::OnDraw1(CDC* pDC);
	void CIDWMMapView::OnDraw4(CDC* pDC);

	void CIDWMMapView::Draw_BkRect(CDC* pDC);
	void CIDWMMapView::Draw_printMargin(CDC* pDC);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDWMMAPVIEW_H__96B63E20_9142_473A_9247_2A9CF25E186F__INCLUDED_)
