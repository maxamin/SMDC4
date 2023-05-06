// ArgusView.h : interface of the CArgusView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARGUSVIEW_H__D7A4E89C_FAC5_452B_ADE2_40F50E9C2FF4__INCLUDED_)
#define AFX_ARGUSVIEW_H__D7A4E89C_FAC5_452B_ADE2_40F50E9C2FF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArgusView : public CView
{
protected: // create from serialization only
	CArgusView();
	DECLARE_DYNCREATE(CArgusView)

// Attributes
public:
	CArgusDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArgusView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CArgusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CArgusView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnToolsColormapJet();
	afx_msg void OnUpdateToolsColormapJet(CCmdUI* pCmdUI);
	afx_msg void OnToolsModeLine();
	afx_msg void OnUpdateToolsModeLine(CCmdUI* pCmdUI);
	afx_msg void OnToolsModeBarchart();
	afx_msg void OnUpdateToolsModeBarchart(CCmdUI* pCmdUI);
	afx_msg void OnToolsBackgroundcolor();
	afx_msg void OnToolsAxiscolor();
	afx_msg void OnToolsTextcolor();
	afx_msg void OnTools3d();
	afx_msg void OnUpdateTools3d(CCmdUI* pCmdUI);
	afx_msg void OnTools2dfreqvalue();
	afx_msg void OnUpdateTools2dfreqvalue(CCmdUI* pCmdUI);
	afx_msg void OnTools2dtimevalue();
	afx_msg void OnUpdateTools2dtimevalue(CCmdUI* pCmdUI);
	afx_msg void OnTOOLS2Dwf();
	afx_msg void OnUpdateTOOLS2Dwf(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnTOOLSGrid();
	afx_msg void OnUpdateTOOLSGrid(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapTopo0();
	afx_msg void OnUpdateToolsColormapTopo0(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapTopo1();
	afx_msg void OnUpdateToolsColormapTopo1(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapGray();
	afx_msg void OnUpdateToolsColormapGray(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapPink();
	afx_msg void OnUpdateToolsColormapPink(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapCopper();
	afx_msg void OnUpdateToolsColormapCopper(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapGlobe();
	afx_msg void OnUpdateToolsColormapGlobe(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueOccupancy();
	afx_msg void OnUpdateToolsValueOccupancy(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueFrequencyoffset();
	afx_msg void OnUpdateToolsValueFrequencyoffset(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueDir();
	afx_msg void OnUpdateToolsValueDir(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueQuality();
	afx_msg void OnUpdateToolsValueQuality(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueMeanlevel();
	afx_msg void OnUpdateToolsValueMeanlevel(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueLevel();
	afx_msg void OnUpdateToolsValueLevel(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueNumber();
	afx_msg void OnUpdateToolsValueNumber(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueStandarddeviationlevel();
	afx_msg void OnUpdateToolsValueStandarddeviationlevel(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueMaxlevel();
	afx_msg void OnUpdateToolsValueMaxlevel(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueMinlevel();
	afx_msg void OnUpdateToolsValueMinlevel(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueBandwidth();
	afx_msg void OnUpdateToolsValueBandwidth(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueMeanbandwidth();
	afx_msg void OnUpdateToolsValueMeanbandwidth(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueStandarddeviationbandwidth();
	afx_msg void OnUpdateToolsValueStandarddeviationbandwidth(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueMaxbandwidth();
	afx_msg void OnUpdateToolsValueMaxbandwidth(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueMinbandwidth();
	afx_msg void OnUpdateToolsValueMinbandwidth(CCmdUI* pCmdUI);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnToolsValueModulationValue();
	afx_msg void OnUpdateToolsValueModulationValue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueModulationMeanvalue();
	afx_msg void OnUpdateToolsValueModulationMeanvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueModulationStandarddeviation();
	afx_msg void OnUpdateToolsValueModulationStandarddeviation(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueModulationMaximumvalue();
	afx_msg void OnUpdateToolsValueModulationMaximumvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueModulationMinimumvalue();
	afx_msg void OnUpdateToolsValueModulationMinimumvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueSubaudiotoneValue();
	afx_msg void OnUpdateToolsValueSubaudiotoneValue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueSoundid();
	afx_msg void OnUpdateToolsValueSoundid(CCmdUI* pCmdUI);
	afx_msg void OnTOOLSData();
	afx_msg void OnUpdateTOOLSData(CCmdUI* pCmdUI);
	afx_msg void OnToolsValuePicode();
	afx_msg void OnUpdateToolsValuePicode(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueProgram();
	afx_msg void OnUpdateToolsValueProgram(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueSubaudiotoneMeanvalue();
	afx_msg void OnUpdateToolsValueSubaudiotoneMeanvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueSubaudiotoneStandarddeviation();
	afx_msg void OnUpdateToolsValueSubaudiotoneStandarddeviation(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueSubaudiotoneMaximumvalue();
	afx_msg void OnUpdateToolsValueSubaudiotoneMaximumvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueSubaudiotoneMinimumvalue();
	afx_msg void OnUpdateToolsValueSubaudiotoneMinimumvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueFrequencyoffsetMeanvalue();
	afx_msg void OnUpdateToolsValueFrequencyoffsetMeanvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueFrequencyoffsetStandarddeviation();
	afx_msg void OnUpdateToolsValueFrequencyoffsetStandarddeviation(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueFrequencyoffsetMaxvalue();
	afx_msg void OnUpdateToolsValueFrequencyoffsetMaxvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueFrequencyoffsetMinvalue();
	afx_msg void OnUpdateToolsValueFrequencyoffsetMinvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueDirectionMeanvalue();
	afx_msg void OnUpdateToolsValueDirectionMeanvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueDirectionStandarddeviation();
	afx_msg void OnUpdateToolsValueDirectionStandarddeviation(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueDirectionMaxvalue();
	afx_msg void OnUpdateToolsValueDirectionMaxvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueDirectionMinvalue();
	afx_msg void OnUpdateToolsValueDirectionMinvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueQualityMeanvalue();
	afx_msg void OnUpdateToolsValueQualityMeanvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueQualityStandarddeviation();
	afx_msg void OnUpdateToolsValueQualityStandarddeviation(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueQualityMaxvalue();
	afx_msg void OnUpdateToolsValueQualityMaxvalue(CCmdUI* pCmdUI);
	afx_msg void OnToolsValueQualityMinvalue();
	afx_msg void OnUpdateToolsValueQualityMinvalue(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONpolar();
	afx_msg void OnUpdateBUTTONpolar(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONShowLegend();
	afx_msg void OnUpdateBUTTONShowLegend(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONSetting();
	afx_msg void OnUpdateBUTTONSetting(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONLinewidthP();
	afx_msg void OnUpdateBUTTONLinewidthP(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONLinewidthN();
	afx_msg void OnUpdateBUTTONLinewidthN(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONTimeSelect();
	afx_msg void OnUpdateBUTTONTimeSelect(CCmdUI* pCmdUI);
	afx_msg void OnBUTTONFrqSelect();
	afx_msg void OnUpdateBUTTONFrqSelect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CRect m_rcPrintRect , m_rect;
	double Dist2Point(CPoint point1, CPoint point2);

	double pi , Fi , m_dTime;
	int  m_deptX , m_deptY , m_offset;

	CPoint m_pointOf , m_pointRBf, m_pointLTf , m_pointRTf , m_pointOb , m_pointRBb , m_pointRTb , m_pointLTb;
	CPoint m_pointY , m_pointX;
	CPoint Point3D(double f,double t,double v);

	int m_ValueType;
	CStringArray m_ListDateTime;
	double m_Fmin, m_Fmax;	//Frequency
	double m_Tmin, m_Tmax;	//Time

	void Draw_Text(CDC* pDC,int x, int y,CString str,
							COLORREF FontColor=RGB(0,0,0),int Escapement=0,int nHeight=12,int nWidth=0,
							int FontWeight=FW_NORMAL,int bWidth = 140, int bAlin = DT_RIGHT, CString FontName="Arial");

	void Draw_Line(CDC* pDC,CPoint point1, CPoint point2,
				int nStyle=PS_SOLID , int nWidth=1,COLORREF crColor=RGB(0,0,0));

	void XY_axis_3D(CDC* pDC);
	void XY_axis_2D(CDC* pDC);

	long Np;
	double m_X0;
	BOOL m_ready;
	CString m_Start, m_Stop , m_PathName;

	void ColorMap(CString type);
	int Contour(double y,double MinV,double MaxV,int nL) ;
	COLORREF RGBt[256];
	CString m_colormaptype;
	int m_mode;

	COLORREF m_BackgroundClr , m_AxisClr , m_TextClt;
	BOOL IsWin2000();
	BOOL PeekAndPump();

	int m_3D2D;

	CString m_LEV_U , m_BW_U ,m_FR_OFF_U,  m_SUBORDER_TASK , m_RESULT_TYPE , m_MEAS_DATA_TYPE;
	double Funit2kHz(CString Ustr);

	void Draw_Data_3D(CDC* pDC, int ListType,int nStyle , int nWidth, COLORREF crColor , int mode);
	void XY_tick_3D(CDC* pDC, int ListType);
	CPoint Data2Point_3D(int ListType, double freq, double tim, double value);

	void Draw_Data_2Dfv(CDC* pDC, int ListType, int nStyle , int nWidth, COLORREF crColor , int mode);
	CPoint Data2Point_2Dfv(int ListType, double freq, double value);
	void XY_tick_2Dfv(CDC* pDC, int ListType);

	void Draw_Data_2Dtv(CDC* pDC, int ListType, int nStyle , int nWidth, COLORREF crColor , int mode);
	CPoint Data2Point_2Dtv(int ListType, double tim, double value);
	void XY_tick_2Dtv(CDC* pDC, int ListType);

	long ListType2Value(int ListType, double *Vmin, double *Vmax);
	POSITION ListType2HeadPosition(int ListType);
	double ListType2NextPosition(int ListType , POSITION &posV);
	CString ListType2Ylable(int ListType);

	void XY_tick_2Dft(CDC* pDC, int ListType);
	void Draw_Data_2Dft(CDC* pDC, int ListType, int nStyle , int nWidth, COLORREF crColor , int mode);
	CPoint Data2Point_2Dft( double freq, double Tvalue);
	void Draw_Circle(CDC* pDC,CPoint point1, COLORREF crColor);

	CString str_rep(CString str,int num);
	
	BOOL m_grid;

	void SaveDesktop(CDC *pDC, CString FileName);
	void CDCToBmp24(CDC *pDC, CString fileOUT);
	CString m_AppPath;

	CString m_MOD_U;

	double ListType2CurrentIndex(int ListType , int i);

///////////////////////////////////////////////////////////////
	void LoadFast();

	struct FieldValueD
	{
  		CArray<double, double> List;
   		CArray<long, long> Index;
		double max;
		double min;
		BOOL flag;
	};
	struct FieldValueS
	{
   		CStringArray List;
   		CArray<long, long> Index;
		BOOL flag;
	};
	FieldValueD	m_T;	//Time
	FieldValueD	m_F;	//Frequency
	FieldValueD	m_L;	//Level Value
	FieldValueD	m_B;	//BandWidth Value
	FieldValueD	m_P;	//Occupancy
	FieldValueD	m_O;	//Offset
	FieldValueD	m_D;	//Direction
	FieldValueD	m_Q;	//Quality
	FieldValueD	m_N;	//Number

	FieldValueD	m_LM;	//Level Mean
	FieldValueD	m_LS;	//Level SD
	FieldValueD	m_LX;	//Level Max
	FieldValueD	m_LI;	//Level Min

	FieldValueD	m_BM;	//BandWidth Mean
	FieldValueD	m_BS;	//BandWidth SD
	FieldValueD	m_BX;	//BandWidth Max
	FieldValueD	m_BI;	//BandWidth Min

	FieldValueD	m_MV;	//Modulation Value
	FieldValueD	m_MM;	//Modulation Mean
	FieldValueD	m_MS;	//Modulation SD
	FieldValueD	m_MX;	//Modulation Max
	FieldValueD	m_MI;	//Modulation Min

	FieldValueD	m_SAV;	//SubaudioTone Value
	FieldValueD	m_SAM;	//SubaudioTone Mean
	FieldValueD	m_SAS;	//SubaudioTone SD
	FieldValueD	m_SAX;	//SubaudioTone Max
	FieldValueD	m_SAI;	//SubaudioTone Min

	FieldValueS	m_SI;	//Sound ID
	FieldValueS	m_PI;	//PI Code
	FieldValueS	m_PR;	//Program

	FieldValueD	m_OM;	//Offset Mean
	FieldValueD	m_OS;	//Offset SD
	FieldValueD	m_OX;	//Offset Max
	FieldValueD	m_OI;	//Offset Min

	FieldValueD	m_DM;	//Direction Mean
	FieldValueD	m_DS;	//Direction SD
	FieldValueD	m_DX;	//Direction Max
	FieldValueD	m_DI;	//Direction Min

	FieldValueD	m_QM;	//Quality Mean
	FieldValueD	m_QS;	//Quality SD
	FieldValueD	m_QX;	//Quality Max
	FieldValueD	m_QI;	//Quality Min

	void Set_FieldValue(FieldValueD	*struct_V,double vlaue,long index) ;
	void Set_FieldValue(FieldValueS	*struct_V,CString vlaue,long index) ;
	void Set_FieldDefaultValue(FieldValueD	*struct_V);
	void Set_FieldDefaultValue(FieldValueS	*struct_V);
	void Set_MinMaxLimit(FieldValueD	*struct_V) ;
	void Reset_Data();
	void Set_FieldValueStr(FieldValueD	*struct_V,CString strLine,CString strStart,long index,double U=1); 
	void Set_FieldValueStr(FieldValueS	*struct_V,CString strLine,CString strStart,long index); 

	void Set_FieldValueStrX(CString str,long jj,double BW_U,double FR_OFF_U);
	void Set_m_ValueType();

	int m_LVflag;
	int m_BWflag;
	int m_Modflag;
	int m_SAflag;
	int m_BEflag;
	int m_SIflag;
	int m_PIflag;
	int m_PRflag;
	int m_FOflag;
	int m_LOflag;

	void Out_Fields(FILE *fp , CString sSeparator);
	void Out_Fields(FILE *fp , CString sSeparator , long i) ;

	BOOL m_MD_LOC_VALUES;
	CString m_ACD_ERR;

	CString Find_Field_OneStr(CString &str, CString Field_One);
	BOOL Find_Field_One(CString PathName);

	void LegendLOC(CDC* pDC);
	BOOL m_LegendFlag;

	CString m_EXECUTION_TYPE;
	int Find_AppenedFiles(CString *str2); 

	CString m_Addition;
	void Addition_Setting(CString str);

	int m_LineWidth;
	CString m_TimeSelect;
	double m_FreqSelect;


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

#ifndef _DEBUG  // debug version in ArgusView.cpp
inline CArgusDoc* CArgusView::GetDocument()
   { return (CArgusDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARGUSVIEW_H__D7A4E89C_FAC5_452B_ADE2_40F50E9C2FF4__INCLUDED_)
