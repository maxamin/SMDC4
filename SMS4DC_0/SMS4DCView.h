// SMS4DCView.h : interface of the CSMS4DCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMS4DCVIEW_H__3ED3AD6C_C9F7_4923_B19E_C8CFE11D743E__INCLUDED_)
#define AFX_SMS4DCVIEW_H__3ED3AD6C_C9F7_4923_B19E_C8CFE11D743E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LegendDLG.h"
#include <afxdb.h>

class CSMS4DCView : public CScrollView
{
protected: // create from serialization only
	CSMS4DCView();
	DECLARE_DYNCREATE(CSMS4DCView)

// Attributes
public:
	CSMS4DCDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMS4DCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSMS4DCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSMS4DCView)
	afx_msg void OnTopo_0();
	afx_msg void OnJet();
	afx_msg void OnGray();
	afx_msg void OnPink();
	afx_msg void OnCopper();
	afx_msg void OnWest();
	afx_msg void OnNorth();
	afx_msg void OnSouth();
	afx_msg void OnEast();
	afx_msg void OnUpdateTopo_0(CCmdUI* pCmdUI);
	afx_msg void OnUpdateJet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePink(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopper(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnGlobeDEM();
	afx_msg void OnUpdateGlobeDEM(CCmdUI* pCmdUI);
	afx_msg void OnTopo1();
	afx_msg void OnUpdateTopo1(CCmdUI* pCmdUI);
	afx_msg void OnGlobe();
	afx_msg void OnUpdateGlobe(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnDrawBox();
	afx_msg void OnUpdateDrawBox(CCmdUI* pCmdUI);
	afx_msg void OnDrawProfile();
	afx_msg void OnCALCULATIONDistanceLine();
	afx_msg void OnCALCULATIONAzimuth();
	afx_msg void OnCALCULATIONElevation();
	afx_msg void OnRefresh();
	afx_msg void OnUpdateDrawProfile(CCmdUI* pCmdUI);
	afx_msg void OnProFreeLine();
	afx_msg void OnDrawVector();
	afx_msg void OnProFreeArea();
	afx_msg void OnUpdateProFreeLine(CCmdUI* pCmdUI);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI* pCmdUI);
	afx_msg void OnArrow();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnProfilePolygon();
	afx_msg void OnUpdateProfilePolygon(CCmdUI* pCmdUI);
	afx_msg void OnCalculationEffectiveheigth();
	afx_msg void OnPropagationmodelsFreespacePolygon();
	afx_msg void OnUpdatePropagationmodelsFreespacePolygon(CCmdUI* pCmdUI);
	afx_msg void OnToolsNormalize();
	afx_msg void OnToolsGrid();
	afx_msg void OnUpdateToolsGrid(CCmdUI* pCmdUI);
	afx_msg void OnToolsGridstep();
	afx_msg void OnUpdateToolsGridstep(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseDisplayselectedstations();
	afx_msg void OnDatabaseStationsindesktop();
	afx_msg void OnDatabaseRemovestationsfromdisplay();
	afx_msg void OnVectorsCircle();
	afx_msg void OnUpdateProFreeArea(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP370Area();
	afx_msg void OnDatabaseSearchstation();
	afx_msg void OnUpdatePropagationmodelsP370Area(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP1546Area();
	afx_msg void OnUpdatePropagationmodelsP1546Area(CCmdUI* pCmdUI);
	afx_msg void OnOverlay();
	afx_msg void OnShowLegend();
	afx_msg void OnUpdateShowLegend(CCmdUI* pCmdUI);
	afx_msg void OnToolsSymbolattribute();
	afx_msg void OnToolsLighten();
	afx_msg void OnToolsDarken();
	afx_msg void OnPropagationmodelsLineofsightArea();
	afx_msg void OnUpdatePropagationmodelsLineofsightArea(CCmdUI* pCmdUI);
	afx_msg void OnUpdateoverlay(CCmdUI* pCmdUI);
	afx_msg void OnFreespaceNetworkprocessorMaximumfieldstrength();
	afx_msg void OnFreespaceNetworkprocessorBestserver();
	afx_msg void OnP370NetworkprocessorMaximumfieldstrength();
	afx_msg void OnP370NetworkprocessorBestserver();
	afx_msg void OnUpdateFreespaceNetworkprocessorMaximumfieldstrength(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFreespaceNetworkprocessorBestserver(CCmdUI* pCmdUI);
	afx_msg void OnUpdateP370NetworkprocessorMaximumfieldstrength(CCmdUI* pCmdUI);
	afx_msg void OnUpdateP370NetworkprocessorBestserver(CCmdUI* pCmdUI);
	afx_msg void OnP1546NetworkprocessorMaximumfieldstrength();
	afx_msg void OnUpdateP1546NetworkprocessorMaximumfieldstrength(CCmdUI* pCmdUI);
	afx_msg void OnP1546NetworkprocessorBestserver();
	afx_msg void OnUpdateP1546NetworkprocessorBestserver(CCmdUI* pCmdUI);
	afx_msg void OnCalculationPowercalculator();
	afx_msg void OnPropagationmodelsP370Line();
	afx_msg void OnUpdatePropagationmodelsP370Line(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP1546Line();
	afx_msg void OnUpdatePropagationmodelsP1546Line(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsLineofsightLine();
	afx_msg void OnUpdatePropagationmodelsLineofsightLine(CCmdUI* pCmdUI);
	afx_msg void OnLineDataBase();
	afx_msg void OnAreaDataBase();
	afx_msg void OnCALCULATIONDistancePolygon();
	afx_msg void OnUpdateCALCULATIONDistancePolygon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCALCULATIONDistanceLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCALCULATIONAzimuth(CCmdUI* pCmdUI);
	afx_msg void OnFrequencyallocationsDrawchart();
	afx_msg void OnPropagationmodelsP370Polygon();
	afx_msg void OnUpdatePropagationmodelsP370Polygon(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP1546Polygon();
	afx_msg void OnUpdatePropagationmodelsP1546Polygon(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsLineofsightPolygon();
	afx_msg void OnUpdatePropagationmodelsLineofsightPolygon(CCmdUI* pCmdUI);
	afx_msg void OnToolsArea3dview();
	afx_msg void OnUpdateToolsArea3dview(CCmdUI* pCmdUI);
	afx_msg void OnToolsAntennaeditor();
	afx_msg void OnCalculationAreakm2();
	afx_msg void OnUpdateCalculationAreakm2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCALCULATIONElevation(CCmdUI* pCmdUI);
	afx_msg void OnTools2dviewcontour();
	afx_msg void OnUpdateTools2dviewcontour(CCmdUI* pCmdUI);
	afx_msg void OnAddStation();
	afx_msg void OnUpdateAddStation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabaseSearchstation(CCmdUI* pCmdUI);
	afx_msg void OnProfileFresnelzone();
	afx_msg void OnUpdateProfileFresnelzone(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP370Link();
	afx_msg void OnPropagationmodelsP1546Link();
	afx_msg void OnPropagationmodelsHataArea();
	afx_msg void OnUpdatePropagationmodelsHataArea(CCmdUI* pCmdUI);
	afx_msg void OnOkumurahataNetworkprocessorMaximumfieldstrength();
	afx_msg void OnUpdateOkumurahataNetworkprocessorMaximumfieldstrength(CCmdUI* pCmdUI);
	afx_msg void OnOkumurahataNetworkprocessorBestserver();
	afx_msg void OnUpdateOkumurahataNetworkprocessorBestserver(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP452Link();
	afx_msg void OnPropagationmodelsP526Link();
	afx_msg void OnCalculationHorizondistance();
	afx_msg void OnCalculationIntermodulation();
	afx_msg void OnCoordinationGe84bc2bc();
	afx_msg void OnCoordinationGe84bc2bt();
	afx_msg void OnCoordinationGe84bc2fx();
	afx_msg void OnCoordinationGe84bc2lm();
	afx_msg void OnCoordinationGe84eu();
	afx_msg void OnPropagationmodelsSmoothearthLink();
	afx_msg void OnCoordinationGe84eui();
	afx_msg void OnPropagationmodelsP370Contour();
	afx_msg void OnVectorsRemovefromdisplay();
	afx_msg void OnCoordinationSt61bc2bc();
	afx_msg void OnPropagationmodelsP1546Contour();
	afx_msg void OnPropagationmodelsP530Link();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMoveStationFlag();
	afx_msg void OnUpdateMoveStationFlag(CCmdUI* pCmdUI);
	afx_msg void OnFrequencyallocationsFrequencyplan();
	afx_msg void OnDatabaseAudittrail();
	afx_msg void OnFrequencyallocationsFplan();
	afx_msg void OnDatabaseBackup();
	afx_msg void OnCalculationUndertestIfic();
	afx_msg void OnDatabaseSearchfrequency();
	afx_msg void OnUpdateDatabaseSearchfrequency(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseList();
	afx_msg void OnUpdateDatabaseList(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP618();
	afx_msg void OnFrequencyallocationsFrequencyassignment();
	afx_msg void OnVectorsCountryborder();
	afx_msg void OnHelpManual();
	afx_msg void OnInterferenceBc2bc();
	afx_msg void OnInterferenceBt2bt();
	afx_msg void OnCoordinationGe89Bt2bt();
	afx_msg void OnCoordinationGe89Eu();
	afx_msg void OnCoordinationGe89Eui();
	afx_msg void OnCoordinationGe89Fx();
	afx_msg void OnCoordinationGe89Lm();
	afx_msg void OnDatabaseLinks();
	afx_msg void OnInterferenceFx2fx();
	afx_msg void OnInterferenceFx2fxi();
	afx_msg void OnCoordinationGe89Fxlm2bt();
	afx_msg void OnInterferenceBt2fx();
	afx_msg void OnInterferenceFxlm2bt();
	afx_msg void OnInterferenceBt2lm();
	afx_msg void OnCoordinationBorder();
	afx_msg void OnDatabaseLicensing();
	afx_msg void OnInterferenceFxmTo();
	afx_msg void OnInterferenceFxmTo2();
	afx_msg void OnInterferenceFxmFrom();
	afx_msg void OnInterferenceFxmFrom2();
	afx_msg void OnInterferenceFx2fxvTo();
	afx_msg void OnInterferenceFx2fxvFrom();
	afx_msg void OnDatabaseUsers();
	afx_msg void OnUpdateDatabaseUsers(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabaseAudittrail(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatabaseBackup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalculationUndertestIfic(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrequencyallocationsFrequencyplan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrequencyallocationsFrequencyassignment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsAntennaeditor(CCmdUI* pCmdUI);
	afx_msg void OnToolsMaplayersUsermap1();
	afx_msg void OnUpdateToolsMaplayersUsermap1(CCmdUI* pCmdUI);
	afx_msg void OnToolsMaplayersUsermap2();
	afx_msg void OnUpdateToolsMaplayersUsermap2(CCmdUI* pCmdUI);
	afx_msg void OnCoordinationAgreements();
	afx_msg void OnInterferenceEsTo();
	afx_msg void OnInterferenceEsFrom();
	afx_msg void OnInterferenceEs2fx();
	afx_msg void OnInterferenceFx2es();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDatabaseDisplayearthstation();
	afx_msg void OnAddESStation();
	afx_msg void OnUpdateAddESStation(CCmdUI* pCmdUI);
	afx_msg void OnMoveESStationFlag();
	afx_msg void OnUpdateMoveESStationFlag(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseEsdesktop();
	afx_msg void OnDatabaseRemovees();
	afx_msg void OnDatabaseImportsrs();
	afx_msg void OnDatabaseSearchesfrq();
	afx_msg void OnUpdateDatabaseSearchesfrq(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseListes();
	afx_msg void OnUpdateDatabaseListes(CCmdUI* pCmdUI);
	afx_msg void OnDatabaseSearchesloc();
	afx_msg void OnUpdateDatabaseSearchesloc(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCoordinationGe06Bcbt2bcbt();
	afx_msg void OnCoordinationGe06Bcbt2fxlm();
	afx_msg void OnDatabaseGeotype();
	afx_msg void OnDatabaseShowallot();
	afx_msg void OnDatabaseDefineallot();
	afx_msg void OnUpdateDatabaseDefineallot(CCmdUI* pCmdUI);
	afx_msg void OnCoordinationGe06Fxlm2bcbtTxfxlm();
	afx_msg void OnCoordinationGe06Fxlm2bcbtRxfxlm();
	afx_msg void OnDatabaseShowsrv();
	afx_msg void OnCoordinationGe06Coveragearea();
	afx_msg void OnCoordinationGe06Servicearea();
	afx_msg void OnDatabaseDisplayge06linked();
	afx_msg void OnDatabaseConverted();
	afx_msg void OnCoordinationGe06InttoBcbt2dbcbt();
	afx_msg void OnCoordinationGe06InttoBcbt2Abt();
	afx_msg void OnCoordinationGe06InttoFxm2dbcbt();
	afx_msg void OnCoordinationGe06InttoFxm2Abt();
	afx_msg void OnCoordinationGe06InttoBcbt2fxm();
	afx_msg void OnDatabaseShowsrvbcbt();
	afx_msg void OnCoordinationGe06IntfromBcbt2dbcbt();
	afx_msg void OnCoordinationGe06IntfromBcbt2abt();
	afx_msg void OnCoordinationGe06IntfromFxm2dbcbt();
	afx_msg void OnCoordinationGe06IntfromFxm2abt();
	afx_msg void OnCoordinationGe06IntfromBcbt2fxm();
	afx_msg void OnToolsGoogleSelectedstations();
	afx_msg void OnToolsGoogleLinks();
	afx_msg void OnToolsGoogleSelectedearthstations();
	afx_msg void OnToolsGoogleReceivingarea();
	afx_msg void OnToolsGoogleServiceareafxm();
	afx_msg void OnToolsGoogleServiceareage06bcbt();
	afx_msg void OnToolsGoogleAllotmentarea();
	afx_msg void OnToolsGoogleGe06planentry();
	afx_msg void OnToolsGoogleConvertedassignments();
	afx_msg void OnToolsGoogleVectors();
	afx_msg void OnFileSave();
	afx_msg void OnVectorsVectorhandling();
	afx_msg void OnUpdateVectorsVectorhandling(CCmdUI* pCmdUI);
	afx_msg void OnCalculationEarthstationhorizonelevation();
	afx_msg void OnCalculationEarthstationAzimuthtogsosatellites();
	afx_msg void OnCalculationEarthstationElevationtogsosatellites();
	afx_msg void OnMonitoringArgusRespondtoorder();
	afx_msg void OnUpdateMonitoringArgusRespondtoorder(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMonitoringArgusGsporder();
	afx_msg void OnMonitoringArgusOrmorder();
	afx_msg void OnMonitoringArgusStoporder();
	afx_msg void OnMonitoringArgusDrawoutput();
	afx_msg void OnMonitoringArgusOrderstatus();
	afx_msg void OnMonitoringThalesViewChecklist();
	afx_msg void OnMonitoringThalesViewOccupancyrate();
	afx_msg void OnMonitoringThalesViewRequests();
	afx_msg void OnMonitoringThalesViewResults();
	afx_msg void OnMonitoringThalesChecklistgenerationMissioncreation();
	afx_msg void OnMonitoringThalesChecklistgenerationRequests();
	afx_msg void OnMonitoringThalesDrawoutput();
	afx_msg void OnMonitoringThalesAtr();
	afx_msg void OnMonitoringThalesChecklistgenerationRequestsautomatic();
	afx_msg void OnUpdateMonitoringThalesChecklistgenerationRequestsautomatic(CCmdUI* pCmdUI);
	afx_msg void OnToolsConvertantennafile();
	afx_msg void OnMonitoringOthersRespondtom2sorder();
	afx_msg void OnUpdateMonitoringOthersRespondtom2sorder(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringOthersS2morder();
	afx_msg void OnMonitoringOthersOrderstatus();
	afx_msg void OnMonitoringOthersStoporder();
	afx_msg void OnMonitoringOthersDrawoutput();
	afx_msg void OnPropagationmodelsP18123Area();
	afx_msg void OnUpdatePropagationmodelsP18123Area(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP18123Fieldstrengthcontour();
	afx_msg void OnPropagationmodelsP18123Line();
	afx_msg void OnUpdatePropagationmodelsP18123Line(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP18123Polyline();
	afx_msg void OnUpdatePropagationmodelsP18123Polyline(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP18123Link();
	afx_msg void OnPropagationmodelsP18123NetworkprocessorMaximumfieldstrength();
	afx_msg void OnUpdatePropagationmodelsP18123NetworkprocessorMaximumFS(CCmdUI* pCmdUI);
	afx_msg void OnPropagationmodelsP18123NetworkprocessorBestserver();
	afx_msg void OnUpdatePropagationmodelsP18123NetworkprocessorBestserver(CCmdUI* pCmdUI);
	afx_msg void OnInterferenceIntermodulation();
	afx_msg void OnCoordinationHcm();
	afx_msg void OnPropagationmodelsP526v14Link();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnToolsColormap3d();
	afx_msg void OnUpdateToolsColormap3d(CCmdUI* pCmdUI);
	afx_msg void OnToolsColormapNegative();
	afx_msg void OnUpdateToolsColormapNegative(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningCoveragezonesP18123();
	afx_msg void OnMonitoringNetworkplanningLocationzoneaoaP18123();
	afx_msg void OnMonitoringNetworkplanningLocationzonetdoaP18123();
	afx_msg void OnMonitoringNetworkplanningRxBsP18123();
	afx_msg void OnMonitoringNetworkplanningRxMfsP18123();
	afx_msg void OnUpdateMonitoringNetworkplanningRxBsP18123(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMonitoringNetworkplanningRxMfsP18123(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMonitoringNetworkplanningCoveragezonesP18123(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMonitoringNetworkplanningLocationzoneaoaP18123(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMonitoringNetworkplanningLocationzonetdoaP18123(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningRxBsP15465();
	afx_msg void OnUpdateMonitoringNetworkplanningRxBsP15465(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningCoveragezonesP15465();
	afx_msg void OnUpdateMonitoringNetworkplanningCoveragezonesP15465(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningLocationzoneaoaP15465();
	afx_msg void OnUpdateMonitoringNetworkplanningLocationzoneaoaP15465(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningLocationzonetdoaP15465();
	afx_msg void OnUpdateMonitoringNetworkplanningLocationzonetdoaP15465(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningRxMfsP15465();
	afx_msg void OnUpdateMonitoringNetworkplanningRxMfsP15465(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningCoveragezonesFreespace();
	afx_msg void OnUpdateMonitoringNetworkplanningCoveragezonesFreespace(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningLocationzoneaoaFreespace();
	afx_msg void OnUpdateMonitoringNetworkplanningLocationzoneaoaFreespace(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningLocationzonetdoaFreespace();
	afx_msg void OnUpdateMonitoringNetworkplanningLocationzonetdoaFreespace(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningRxMFSFreespace();
	afx_msg void OnUpdateMonitoringNetworkplanningRxMFSFreespace(CCmdUI* pCmdUI);
	afx_msg void OnMonitoringNetworkplanningRxBSFreespace();
	afx_msg void OnUpdateMonitoringNetworkplanningRxBSFreespace(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnFilePrintPreview() ;
//private:
/*
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
*/
//	POLYGONvec m_POLY[100];

	int VScrollpos, HScrollpos;
	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU); 

	CPoint m_stLinePoint, m_enLinePoint, m_stBoxPoint, m_enBoxPoint;
	bool m_bLPressed;

	COLORREF m_Color;

	CString m_bToolBarDraw;
	void DrawProfile(BOOL m_DrawFresnel);

	double Distance_km(double lat1,double lon1,double lat2,double lon2);
	double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2);

	void DrawVector(CDC *pDC,CString Vector_filepath,
		int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID,
		int nMode=0,COLORREF flColor=RGB(255,255,255),int alpha=50);

	bool m_DrawVector;

//	int m_POLYnum;

//	CPoint *m_PolyPoint;
	CPoint m_PolyPoint[1000];
	int m_PolyPointNum0,m_PolyPointNum;
	long Round(double x);

	void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg);
	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt);
//	CPoint *m_Point_STcr;
//	CPoint m_Point_STcr[73];
	double m_MinValue,m_MaxValue;
	double m_GridStep;
	int m_MenuBarGrid;
	CString GetFld(CString Src,int N);
	void DrawSymboleStation(CDC* pDC,double lats,double lons,
						COLORREF color1=RGB(0,0,127),int len1=6); 

	double *Lat_ST,*Lon_ST;
	CString *Name_ST;
	long *ID_ST;
	int Num_ST;
	void TextDraw(CDC* pDC,int x, int y,CString str,COLORREF FontColor=RGB(0,0,127),
			int Escapement=0,
			int nHeight=12,int nWidth=0,int FontWeight=FW_BOLD,CString FontName="Arial"); 
	void Point2LatLon(CPoint point1,double *Lat1,double *Lon1) ;

	CLegendDLG *m_pLegendDLGModeless; 
	BOOL m_LegendFlag;

	COLORREF m_SymbolColor , m_SymbolTextColor;
	int m_SymbolSize , m_colorRate;

	void DrawProfilePolygon(); 
	double Point2Hg(CPoint point1); 
	double RoundBUF_Hg(double xps,double yps); 

	double fdd1(double x1,double x0,double y1,double y0);
	double fdd2(double x2,double x1,double x0,double y2,double y1,double y0);
	double fdd3(double x3,double x2,double x1,double x0,double y3,double y2,double y1,double y0);
	double Interp1D(double *D0,double *E0,double d,int num,int type0=1);

	int SignFunction(double x) ;
	double Area_km2(double * lat0,double * lon0,int num0) ;
	int Contour(double y,double MinV,double MaxV,int nL) ;
	void YX2LatLon(double y1,double x1,double *Lat1,double *Lon1) ;

	bool m_bLPressedP;
	void OnAddStationFUC(double lat1,double lon1);
	void AddStation_disp(long ID,double lat1,double lon1,CString name1);
	double atof_kfactor(CString k1);

	int WarmColdSea(double RLON_deg,double RLAT_deg) ;
	void WarmColdCross(double RLON_deg1,double RLAT_deg1,double RLON_deg2,double RLAT_deg2,
							  double *RLON_degcross,double *RLAT_degcross) ;
	void WarmSuperCross(double RLON_deg1,double RLAT_deg1,double RLON_deg2,double RLAT_deg2,
							  double *RLON_degcross,double *RLAT_degcross) ;

	void Rad2Str(float lonRAD,float latRAD,CString *lonSTR,CString *latSTR) ;
	double Interp2(int *D0,double *E0,double d,int num) ;

	void OnDatabaseStationsindesktop(long ID,CString name1,double lat1,double lon1) ;

	void GE84Heff(long terrakey,double eff_hgtmax,double * Heff) ;
	void GE84pattern(long terrakey,double * attnH,double * attnV,CString pol) ;

	double Points2HgAvr1(double lat1 , double lon1,double lat2 , double lon2 , long n = 12000) ;
	double LatLon2Hg(double lat_deg,double lon_deg) ;

	void CoastalArea(double lat01,double lon01,double lat02,double lon02,
							  double *Dland1 ,double *Dsea1 ,double *DseaW1 ); 
//	void CoastalArea(double lat01,double lon01,double lat02,double lon02,
//					 double *Dland1 ,double *Dsea1 ,double *DseaW1 ,double *DseaC1 ,double *Dsuper1) ;
//	int Super(double RLON,double RLAT) ;

	CString OnCoordinationGe84euQx() ;
//	BOOL OnCoordinationGe84euQy(CString assignIDX,double latX, double lonX, double frqX, double Drange, double Frange,BOOL *hef_flag) ;
	BOOL OnCoordinationGe84euQy(long terrakeyX,double latX, double lonX, double frqX, double Drange, double Frange,BOOL *hef_flag) ;
	CString str_rep(CString str,int num);
	void SuperRefract50(double RLAT_deg1,double RLON_deg1,double RLAT_deg2,double RLON_deg2,
								double *dLand,double *dWarm,double *dCold,double *dSuper) ;
	void SuperRefract100(double RLAT_deg1,double RLON_deg1,double RLAT_deg2,double RLON_deg2,
								double *dLand,double *dWarm,double *dCold,double *dSuper) ;


	int LandWarmColdSea(double RLON_deg,double RLAT_deg) ;
	void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) ;
	double D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,
										   double *D_SeaW_km)  ;

	void PathMean(double LeftLong, double LeftLat, double RightLong, double RightLat,
															double *LongM, double *LatM);
	void OnDrawVector(CString sFile,int mode=0);

	bool m_bRPressed;
	long m_IndexMoveST;

	double oldLat,oldLon;
	BOOL DispStationQ(long ID, CString name1) ;

	int OnDatabaseStationsindesktop1() ;

	void MapLayerChange(CString TileInfo,int Tx0,int Ty0) ;
	CString m_AppPath;
	void ColorMap_Function(CString type) ;

	CRect m_rcPrintRect;
	long m_x1,m_y1,m_x2,m_y2;

	void LegendLOC(CDC* pDC) ;

	CString VectorCountry(CString cty) ;

	CString OnInterferenceQx(CString stn_cls) ;
//	BOOL OnInterferenceQy(CString assignIDX,double latX, double lonX, double frqX, double Drange, double Frange,CString stn_cls, BOOL *hef_flag) ;
	BOOL OnInterferenceQy(long assignIDX,double latX, double lonX, double frqX, double Drange, double Frange,CString stn_cls, BOOL *hef_flag) ;
	void OnDatabaseStationsindesktop2(double lat1,double lon1) ;

	int GEZones(int plan,double lon01, double lat01, double lon02, double lat02,double *zDist,CString *z) ;

//	BOOL OnGE89Qy(CString assignIDX,double latX, double lonX, double frqX, double Drange,CString stn_cls, BOOL *hef_flag) ;
	BOOL OnGE89Qy(long assignIDX,double latX, double lonX, double frqX, double Drange,CString stn_cls, BOOL *hef_flag,int tofrom) ;
	CString OnGE89Qx(CString stn_cls) ;

	double Delta_H(double lat0 , double lon0,double az) ;
	double Eff_H(double lat0 , double lon0,double az,double Hagl) ;
	BOOL OnGE89FXMQy(double latX, double lonX, double frqX, double Drange, double Frange,CString stn_cls, BOOL *hef_flag) ;
	void GE89site_name(long geo_key,CString *ctry, CString *site_name) ;


//	void AddSt(CString STname, double STlat_deg, double STlon_deg, long Sth_agl,
//		   double txfreq, double power_eirp, double Azimuth, double Elevation,
//		   double AntGain, double BWh, double BWv, CString Polarization, double InsertionLoss, 
//		   double RxSensitivity, CString STTP, CString Emission, double BandWidth, long HeightASL, CString AntName);

	long AddSt(CString STname, double STlat_deg, double STlon_deg, long Sth_agl,
		   double txfreq, double power_eirp, double Azimuth, double Elevation,
		   double AntGain, double BWh, double BWv, CString Polarization, double InsertionLoss, 
		   double RxSensitivity, CString STTP, CString Emission, double BandWidth, long HeightASL, CString AntPath);

//	CString AssignAntenna(CDatabase *DB,long AntID, CString AntPath, double *FreqFrom, double *FreqTo);
	CString AssignAntenna(CDatabase *DB,long AntID, CString AntPath, double *FreqFrom, double *FreqTo, CString Pol, double Azimuth);

	double Emission2NBW(CString Emission) ;
	CString BWCode(float BW);

	double *Lat_TxLink,*Lon_TxLink , *Lat_RxLink,*Lon_RxLink;
	int Num_Link;
	long *HopID;
	void AddLink_disp(long ID,double lat1,double lon1,double lat2,double lon2) ;
	void DrawSymboleLink(CDC *pDC,double lat1,double lon1,double lat2,double lon2) ;
	BOOL DispLinkQ(long ID) ;
	void ArrowTo(CDC* pDC, CPoint lpTo , int nWidth,float fTheta=0.7f,bool bFill=true);

	long m_IndexMoveLinkTx[200] , m_IndexMoveLinkRx[200] , m_IndexMoveLinkTxN, m_IndexMoveLinkRxN;

	CString OnFX2FXQx() ;
	BOOL OnFX2FXQy(long HopID, long TxID, double latX, double lonX, double frqX, double Drange, double Frange, BOOL *hef_flag) ;
	int LandSeaCoastal(double RLON_deg,double RLAT_deg) ;

	BOOL OnFX2FXQyi(long HopID, long TxID, double latX, double lonX, double frqX, double Drange, double Frange, BOOL *hef_flag) ;

	double AZ_EL(double latT , double lonT , double latR , double lonR, double HtAGL, double HrAGL, double re, double *AZrad) ;
	CString AntID2AntName(long ID) ;

	CString OnFXM2BTQx(BOOL *hef_flag) ;
	BOOL OnFXM2BTQy(double latX, double lonX, double frqX, double Drange, double Frange, BOOL *hef_flag) ;

	BOOL OnBT2FXQy(double latX, double lonX, double frqX, double Drange, double Frange, BOOL *hef_flag) ;

	///////////////////////////////////////////Border //////////////////////////////////////////////////
	BOOL PeekAndPump();
	CString OnBorderQx() ;
	CString OnAgreeMod1LMQ(CString cty,CString srv,double frq) ;

	void BorderCom2Cty(double latst,double lonst,CString ctyI,
								  double **datalat,double **datalon,long *numBorder) ;

	void BorderCBR_Vector(double latst,double lonst,double CBR,CString ctyI,
								  double *Blat,double *Blon,long numBorder,double **CBRlat,double **CBRlon,long *numCBR) ;
	void BorderXKM_Vector(double XKM,CString ctyI,
								  double *Blat,double *Blon,long numBorder,double **XKMlat,double **XKMlon,long *numXKM) ;

	CString BorderM1FX1G(double LatX,double LonX,CString ctyX,double FrqX,CString ctyA,CString TxRx,
									 double h,double cord1,double cord2 , double Dsearch); 

	double TCAcorr1546(double Tdeg,double f_MHz);
	double E_P1546(double latST,double lonST,double lat0,double lon0,
							  double HasglST, double f_MHz,double PtGtSTw, double kfactor,
							  double Pime,double RxH,int ENV,int syst,double Plocation,
							  int P1546Clangle , int P1546landsea, int p);

	CString BorderM2LMFree(double LatX,double LonX,CString ctyX,double FrqX,double FrqX1y,
										CString stn_clsX,double PtGtX,double ERP,CString Ptype,double XKM,
										double PIFS,CString ctyA,double Dsearch,
									double HaglX, double AZ0X, double EL0X, int f0[], double rH[], double rV[], double HaglY, double kfactor);

	CString BorderM2LMP1546(double LatX,double LonX,CString ctyX,double FrqX,double FrqX1y,
										  CString stn_clsX,double PtGtX,double ERP,CString Ptype,double XKM,
										  double PIFS, CString ctyA,double HasglX, double kfactor, double Pime,
										  double RxH, double Plocation,int ENV, int syst,int P1546Clangle ,
										  int P1546landsea, int p,double Dsearch,
									double HaglX, double AZ0X, double EL0X, int f0[], double rH[], double rV[]);

	CString BorderM1LMFree(double LatX,double LonX,CString ctyX,double FrqX,double FrqX1y,
										CString stn_clsX, double PtGtX,double ERP,CString Ptype,
										double CBR,double PIFS,CString ctyA,double Dsearch,
									double HaglX, double AZ0X, double EL0X, int f0[], double rH[], double rV[], double HaglY, double kfactor);
										

	CString BorderM1LMP1546(double LatX,double LonX,CString ctyX,double FrqX,double FrqX1y,
										 CString stn_clsX,double PtGtX,double ERP,CString Ptype,double CBR,
										 double PIFS,CString ctyA,double HasglX, double kfactor, double Pime,
										 double RxH, double Plocation,int ENV, int syst,int P1546Clangle ,
										 int P1546landsea, int p,double Dsearch,
									double HaglX, double AZ0X, double EL0X, int f0[], double rH[], double rV[]);

	BOOL BorderISPrefCountries(CString PrefCountries,CString ctyX) ;

	CString OnFxmQx(BOOL Tx) ;
	BOOL OnFxmQy(long IDX,double latX, double lonX, double frqX, double Drange, double Frange, BOOL Tx) ;

	CString LatLon2Ctry(double lat,double lon) ;

	CString OnFxVQx(BOOL Tx) ;
	BOOL OnFxVQy(long IDX,double latX, double lonX, double frqX, double Drange, double Frange, BOOL Tx) ;

	///////////////////////////////NFD Fixed Service ///////////////////////////////////////
	double NFDfixed_Loss(long ID_Tx,CString Name_Tx,double fMHz_Tx,long ID_Rx,CString Name_Rx,double fMHz_Rx) ;
	double MinValue(double *xi,int N) ;
	double MaxValue(double *xi,int N) ;
	double interwt(double *ft,double *at,int n,double f0) ;
	double subsection(double a,double b,double fc) ;

	BOOL OnGE89FXMQyL(double latX, double lonX, double frqX, double Drange, double Frange,CString stn_cls, BOOL *hef_flag) ;

	long OnESQx(CString * str1, CString TxRx) ;
	long OnESQy(long ntc_id,double latX, double lonX, double frqX, double Drange, double Frange_MHz,CString TxRx,CString * str1) ;
	long OnES2FXQy(long IDX,double latX, double lonX, double frqX, double Drange, double Frange_MHz, BOOL Tx,CString * str1) ;

	BOOL RxSystem_A_D_ES2ES(CString emission) ;
	BOOL RxSystemGRP_A_D_ES2ES(long grpID) ;
	BOOL RxSystem_A_D_ES2FX(CString emission, double timeP) ;
	BOOL RxSystem_A_D_FX2ES(CString emission) ;
	BOOL RxSystemGRP_A_D_FX2ES(long grpID) ;

	CToolTipCtrl *m_pToolTip, *m_pToolTipES;
	CString IDst2Information(long IDst) ;
	CString *m_STinfo, *m_ESTinfo;

	double NFD_FX2ES_Loss(long ID_Tx,CString Name_Tx,double fMHz_Tx,long ID_Grp,CString Name_ES,double fMHz_ES) ;
	double NFD_ES2FX_Loss(long ID_Grp,CString Name_ES,double fMHz_ES,long ID_Rx,CString Name_Rx,double fMHz_Rx) ;
	double NFD_ES2ES_Loss(long ID_Grp1,CString Name_ES1,double fMHz_ES1,long ID_Grp2,CString Name_ES2,double fMHz_ES2) ;

	void DrawSymboleEarthStation(CDC* pDC,double lats,double lons,
						COLORREF color1=RGB(0,0,127),int len1=6); 
	double *Lat_EST,*Lon_EST;
	CString *Name_EST;
	long *ID_EST;
	int Num_EST;
	void AddEarthStation_disp(long ID,double lat1,double lon1,CString name1) ;
	BOOL DispEarthStationQ(long ID, CString name1) ;
	void OnAddESStationFUC(double lat1,double lon1) ;
	long m_IndexMoveEST;
	CString IDstES2Information(long ntc_id) ;

	void BorderCom2CtyD(double latst,double lonst,CString ctyI,double Dsearch,
								  double **datalat,double **datalon,long *numBorder) ;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////GE06//////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	CString QGE06_BCBT_A0(double latContour_deg[],double lonContour_deg[],int nContour,CString cty1, double FStrig, long *Ncty, int mode=0, double hR=10, CString BCBT=_T("")) ;
	long QGE06_BCBT_A1(CString AssocAllotID) ;
	double E_P154606(double latST,double lonST,double lat0,double lon0,double h1,
							  double HasglST, double f_MHz, double kfactor,
							  double Ptime,double RxH,int ENV,int syst,double Plocation,
							  int P1546Clangle);
	long QGE06_BCBT_A2(CString SfnID,CString *GeoLat,CString *GeoLon,
								CString *Frequency,CString *Pol,
								CString *ERP_h_dbw,CString *ERP_v_dbw,
								CString *AntCatID,CString *AntHeightAGL,
								CString *AntID,CString *MaxEffHght , CString *AntDir ,int mode=0) ;

	long QGE06_BCBT_A3_1(long contourkey,long n_tp, CString *lat_tp, CString *lon_tp,double *GRlat , double *GRlon) ;
	long QGE06_BCBT_A3_2(long allotkey , CString *contourkey , CString *nb_test_pts) ;

	double E_P154606AL(double latST,double lonST,double lat0,double lon0,double h1,
						  double f_MHz, double Ptime);

	double E_P154606ALn(double latST,double lonST,double lat0,double lon0,double h1,
						  double f_MHz, double Ptime);

	CString VectorCountry1(CString cty,long *NcontourT) ;
	long QGE06_BCBT_Aux_Border(CString cty, CString *lat_tp, CString *lon_tp,double *GRlat , double *GRlon) ;

	CString QGE06_BCBT_A4_1(CString SfnID) ;
	int GE06_PEC(CString AdmRefID , CString AssocAllotID , CString PlanEntry , CString SfnID , CString STN) ;

	long QGE06_BCBT_A5(CString AssocAllotID,CString *GeoLat,CString *GeoLon,
								CString *Frequency,CString *Pol,
								CString *ERP_h_dbw,CString *ERP_v_dbw,
								CString *AntCatID,CString *AntHeightAGL,
								CString *AntID,CString *MaxEffHght , CString *AntDir) ;

	long QGE06_BCBT_A2_1(CString SfnID,CString IDst,CString *strOUT ,int mode=0) ;
	CString QGE06_BCBT_A4_2(CString SfnID) ;
	CString QGE06_BCBT_A5_2(CString AssocAllotID) ;
	CString QGE06_BCBT_A5_1(CString AdmRefID) ;

	long QGE06_BCBT_B1_FX_POINT (double latC, double lonC, double Drange,double frq_MHz, double BandWidthBS_MHz,double FrqRange,int OverLapFlag , CString sttp , CString cty1, CString NoticeType, CString Fragment,CString RPRstr=_T(""));
	long QGE06_BCBT_B1_FX_MPOINT(double latC, double lonC, double Drange,double frq_MHz, double BandWidthBS_MHz,double FrqRange,int OverLapFlag , CString sttp , CString recType, CString cty1, CString NoticeType,CString Fragment,CString RPRstr=_T("")) ;
	long QGE06_BCBT_B1_ML_SRV(double latC, double lonC, double Drange,double frq_MHz, double BandWidthBS_MHz,double FrqRange,int OverLapFlag , CString cty1, CString NoticeType, CString Fragment,CString RPRstr=_T("")) ;
	long QGE06_BCBT_B1(double latC, double lonC, double Drange,double frq_MHz, double BandWidthBS_MHz,double FrqRange,int OverLapFlag , CString cty1, CString NoticeType, CString Fragment,CString RPRstr=_T("")) ;

	CString QGE06_BCBT_Qx(BOOL *hef_flag) ;
	BOOL QGE06_BCBT_Qy(int TxRx=0) ;

	BOOL QGE06_BCBT_Q0(double latC, double lonC, double Drange, double lat[],double lon[],int N_Mpoint);
	BOOL QGE06_BCBT_Q1(long IDst ,double latC, double lonC, double Drange, double lat[], double lon[],int *n0);
	BOOL QGE06_BCBT_Q2(long IDst ,double latC, double lonC, double Drange,CString *zone);
	BOOL QGE06_BCBT_Q3(long IDst ,double latC, double lonC, double Drange,CString *latci,CString *lonci,CString *Rci); 
	BOOL QGE06_BCBT_Q4(long IDst ,double latC, double lonC, double Drange,CString *latci,CString *lonci,CString *Rci); 
	long QGE06_BCBT_Q5(double FStrig, double hR, double latContour_deg[] ,double lonContour_deg[], int nContour ,CString *outStr) ;
	CString QGE06_BCBT_Q6(long IDst,double fter,CString geoType, double FStrig, double hR,CString sttp) ;

	BOOL InterSection(double lat1[],double lon1[],long n1,double lat2[],double lon2[],long n2) ;

	long Ctry2Point(CString ctry) ;

	CString QGE06_Allot_Qx() ;

	CString QGE06_FXMBCBT_QTx(BOOL *hef_flag) ;
	long QGE06_FXMBCBT_Q1(long IDst,CString *zone) ;
	void QGE06_FXMBCBT_Q2(long n1,CString zone, double *lat,double *lon) ;

	CString QGE06_FXMBCBT_QRx(BOOL *hef_flag) ;
	int QGE06_FXMBCBT_Q3(long IDst ,double *GRlat, double *GRlon) ;
	long QGE06_FXMBCBT_Q4(long IDst ,double *GRlat, double *GRlon) ;
	int QGE06_FXMBCBT_Q5(long IDst ,double *GRlat, double *GRlon) ;
	int QGE06_FXMBCBT_Q6(long IDst, double FrqR, double FrqT, double lat, double lon ,CString sttp,CString BCBT,CString SysType1, CString SysType2,double RPR);

	void Zone2GRpoint(CString zone ,double *GRlat, double *GRlon); 

/////////////////////////////////GE06 Coverage Area/////////////////////////////////////////////////////
	CString QGE06_CArea_Qx(BOOL *hef_flag) ;
	int QGE06_CArea_Qy(CString IDst_W, double GeoLat_W, double GeoLon_W,double SearchRadius,double Freq_W,double FR,
					   int DP,int AP,int OS,int PEC_W, CString SfnID_W,CString AssocAllotID_W,CString Fragment_W) ;

	BOOL QGE06_CArea_Q1(long allotkey,double GeoLat_W, double GeoLon_W,double SearchRadius) ;

	long QGE06_CArea_Q2(CString SfnID,CString *GeoLat,CString *GeoLon,
						CString *Frequency,CString *Pol,
						CString *ERP_h_dbw,CString *ERP_v_dbw,
						CString *AntCatID,CString *AntHeightAGL,
						CString *AntID,CString *MaxEffHght, CString *AntDir, CString *IDst,int mode=0) ;

	double CNFS_Function(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
							double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
							CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
							double latCal,double lonCal,double CF,double  PRC,double  PRT,double  PR,
							int AntDisc, int ENV,double Ti,double kfactor,double A2D=0) ;

	int IDstCompare(CString IDst, CString IDstN,int num);

	double CNFS_FunctionAL(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
							double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,
							double lat_TP[],double lon_TP[],long NcontourT,double CF,double PRC,double PRT,double PR,
							int AntDisc, int ENV,double Ti) ;

	CString QGE06_CArea_Q3(CString AdmRefID); 
	CString QGE06_CArea_Q4(CString AssocAllotID); 
	void Zone2NearPoint(CString zone ,double lat0, double lon0 ,double *Nlat, double *Nlon) ;
	long QGE06_CArea_Q2_1(CString SfnID,CString *GeoLat,CString *GeoLon,
							CString *Frequency,CString *Pol,
							CString *ERP_h_dbw,CString *ERP_v_dbw,
							CString *AntCatID,CString *AntHeightAGL,
							CString *AntID,CString *MaxEffHght, CString *AntDir, CString *IDst,
							CString *NoticeType, CString *RPC, CString *SysVar, CString *RXMode, CString *SpecMask) ;

	void GE06CoverageArea(int EXA = -1, int LNB = -1, int AZstep = 10, int UD = 0) ;

	double GE06UFS(int Nrowy,CString Fragment_W,CString NoticeType_W,double Freq_W,
					  CString TV_SYS_W, CString RPC_W, CString SYS_VAR_W, double freq_vcarr_W,
					  CString TV_COLOR_W, double freq_scarr_W,CString oset_v_12_W,CString oset_v_khz_W,
					  CString TV_ch_W, CString RxMode_W, CString freq_stabl_W, double miu_W, double Sigma_W,
					  double GeoLat_W, double GeoLon_W, CString Pol_W, double latCal, double lonCal,
					  int AntDisc, int ENV, double Ti, double kfactor,double UFSmin) ;

	CString QGE06_Digital_Qx(int flagC); 
	void QGE06_Digital_Qy(CString IDst, int PEC, CString NoticeType, CString SfnID, CString allotkey,CString AdmRefID,CString AssocAllotID,CString STN,int flagC); 
	void GE06ShowAllot(CString allotkey , CString GeoArea) ;
	void GE06linked_Converted(int flagC);

	void CSArea_Table(CString IDst, CString Name,double Lat[],double Lon[],double UFS[],double Em[],int Num) ;
	void CSArea_Table(CString IDst, CString Name,double Lat[],double Lon[],double UFS  ,double Em[],int Num) ;

	//////////////////////////////////////////////GE06 Interference To//////////////////////////////////////////////////////////////////
	CString QGE06_IntTo_Qx(int type=0) ;
	long QGE06_IntTo_Q1(CString IDst0, CString SfnID,CString *IDst,double *GRlat,double *GRlon,CString *strOUT, int mode=0) ;
	void QGE06_IntTo_Q2(CString allotkey,double *GRlat,double *GRlon);
	CString QGE06_IntTo_Q3(CString SfnID) ;
	int QGE06_IntTo_Q4(CString AdmRefID,CString *IDst,CString *GeoLat,CString *GeoLon,CString *Frequency, CString *strOUT);
	BOOL QGE06_IntTo_Q5(CString cty, double GeoLat, double GeoLon,double SearchRadius) ;
	long QGE06_IntTo_Q6(CString IDst,CString *GeoLat,CString *GeoLon, CString *UFS, CString *Em); 
	long QGE06_IntTo_Q7(CString allotkey,CString mode, CString *strOUT) ;

	int QGE06_IntToBCBT2DBCBT_Qy(CString IDst_IT, int nIDst_IT, CString allotkey_IT, int nallotkey_IT, double GRlat, double GRlon, double SR, double Freq_I, double FR);

	double CNFS_Function_Int(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								CString NoticeType_W,CString RXMode_W,CString RPC_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
								double latCal,double lonCal,double CF,double  PR,
								int AntDisc, int ENV,double Ti,double kfactor,double A2D=0); 
	
	double CNFS_FunctionAL_Int(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								CString NoticeType_W,CString RXMode_W,CString RPC_W,
								double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,
								double lat_TP[],double lon_TP[],long NcontourT,double CF,double PR,
								int AntDisc, int ENV,double Ti); 

	double QGE06_IntToBCBT2DBCBT_CNFS(CString Fragment_W,CString NoticeType_W,double Freq_W, CString TV_SYS_W, CString RPC_W, CString RxMode_W, 
							double GeoLat_W, double GeoLon_W, CString Pol_W, double Sigma_W, CString SYS_VAR_W, double miu_W,
							CString Fragment_I,CString NoticeType_I,double Freq_I, CString TV_SYS_I, CString RPC_I, CString RxMode_I,
							double GeoLat_I,double GeoLon_I, CString Pol_I, double Sigma_I, double freq_vcarr_I, CString NET_I,int PEC_I,
							CString AdmRefID_I,	CString AssocAllotID_I, CString SfnID_I, CString allotkey_I, CString Hagl_I, CString AntDir_I,
							CString AntCatID_I, CString ERP_h_dbw_I, CString ERP_v_dbw_I, CString TV_COLOR_I, CString GeoArea_I, CString RN_I,
							double latCal,double lonCal, double CF, double PR0, int AntDisc, int ENV,double Ti,double kfactor);

	int QGE06_IntToBCBT2ABCBT_Qy(CString IDst_I, double GRlat, double GRlon, double SR, double Freq_I, double FR);

	double QGE06_IntToBCBT2ABCBT_CNFS(double Freq_W, CString TV_SYS_W, double GeoLat_W, double GeoLon_W, CString Pol_W,
							CString Fragment_I,CString NoticeType_I,double Freq_I, CString TV_SYS_I, CString RPC_I,
							double GeoLat_I,double GeoLon_I, CString Pol_I, double Sigma_I, double freq_vcarr_I, CString NET_I,int PEC_I,
							CString AdmRefID_I,	CString AssocAllotID_I, CString SfnID_I, CString allotkey_I, CString Hagl_I, CString AntDir_I,
							CString AntCatID_I, CString ERP_h_dbw_I, CString ERP_v_dbw_I, CString TV_COLOR_I, CString GeoArea_I, CString RN_I,
							double latCal,double lonCal, double CF, double PRC, double PRT, int AntDisc, int ENV,double Ti,double kfactor,
							double freq_vcarr_W,double freq_scarr_W,CString TV_ch_W,
							CString TV_COLOR_W,CString oset_v_12_W,CString oset_v_khz_W,CString freq_stabl_W,
							CString SYS_VAR_I,double freq_scarr_I,CString oset_v_12_I,CString oset_v_khz_I,
							CString TV_ch_I,double pwr_ratio_I); 

	double GE06UFS1(int Nrowy,CString Fragment_W,CString NoticeType_W,double Freq_W,
					  CString TV_SYS_W, CString RPC_W, CString SYS_VAR_W, double freq_vcarr_W,
					  CString TV_COLOR_W, double freq_scarr_W,CString oset_v_12_W,CString oset_v_khz_W,
					  CString TV_ch_W, CString RxMode_W, CString freq_stabl_W, double miu_W, double Sigma_W,
					  double GeoLat_W, double GeoLon_W, CString Pol_W, double latCal, double lonCal,
					  int AntDisc, int ENV, double Ti, double kfactor,double UFSmin,int UFScheck,CDatabase *DB1) ;

	void GE06_USFtest1(CString IDst,CString allotkey,double CNFS,double UFSmin,CDatabase *DB1);
	int GE06_USFtest2(CString IDst,CString allotkey,CDatabase *DB1);

	double CNFS_Function1(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
							double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
							CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,CString IDst_I,
							double latCal,double lonCal,double CF,double  PRC,double  PRT,double  PR,
							int AntDisc, int ENV,double Ti,double kfactor,double UFSmin, int UFScheck,CDatabase *DB1,double A2D=0); 

	double CNFS_FunctionAL1(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
							double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,CString allotkey_I,
							double lat_TP[],double lon_TP[],long NcontourT,double CF,double PRC,double PRT,double PR,
							int AntDisc, int ENV,double Ti,double UFSmin, int UFScheck,CDatabase *DB1) ;

	double CNFS_Function_IntA(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								CString NoticeType_W,CString RXMode_W,CString RPC_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
								double latCal,double lonCal,double CF,double  PRC,double  PRT,
								int AntDisc, int ENV,double Ti,double kfactor,double A2D=0); 

	int QGE06_IntToBCBT2FXM_Qy(double GRlat, double GRlon, double SR, double Freq_I, double FR); 
	int QGE06_IntToBCBT2FXM_Q1(long IDst ,double lat[], double lon[]);
	CString QGE06_IntToBCBT2FXM_Q2(long IDst);
	void QGE06_IntToBCBT2FXM_Q3(CString zone0,double *lat,double *lon,long n1); 
	void QGE06_IntToBCBT2FXM_Q4(long IDst , double *latci,double *lonci,double *Rci); 

	double CNFS_Function_FXM(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
								double latCal,double lonCal,double CF,double  PR,
								int AntDisc, int ENV,double Ti,double kfactor,int ant,double hR,
								CString AntDir_W,CString AntCatID_W); 

	double CNFS_FunctionAL_FXM(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,
								double lat_TP[],double lon_TP[],long NcontourT,double CF,double PR,
								int AntDisc, int ENV,double Ti,int ant,double hR,
								CString AntDir_W,CString AntCatID_W); 

	double GE06UFS_FXM(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
						double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
						CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
						double latCal,double lonCal,double CF,double  PR,
						int AntDisc, int ENV,double Ti,double kfactor,int ant,double hR,
						CString NET_I,int PEC_I,CString SFNID_I, CString GeoArea_I, CString allotkey_I,
						CString	RN_I, CString RPC_I,CString AdmRefID_I,CString AntDir_W,CString AntCatID_W,
						CString sttp_W,CString Emission_W,CString SysType1_W,CString SysType2_W,CString Fragment_I,
						int GENERIC);

	double QGE06_XPD(long AntCatID); 
	CString QGE06_Showsrvbcbt(); 

	//////////////////////////////////////////////GE06 Interference From//////////////////////////////////////////////////////////////////
	CString QGE06_IntFrom_Qx(int type=0); 
	int QGE06_IntFromBCBT2DBCBT_Qy(CString IDst_WT, int nIDst_WT, CString allotkey_WT, int nallotkey_WT, double GRlat, double GRlon, double SR, double Freq_W, double FR) ;

	CString QGE06_IntFrom_Q1(CString IDst_I,CString SfnID_I,CString NET_I,int PEC_I,CString allotkey_I, CString AssocAllotID_I, CString AdmRefID_I,
							  CString adm_I,CString ctry_I,CString SiteName_I,
							  CString NoticeType_I,CString AssignCode_I,double Freq_I,CString Pol_I,
							  CString RLONbs,CString RLATbs,CString P_out,
							  CString *IDst_out,int *Nas,CString *allotkey_out,int *Nal);

	long QGE06_IntFrom_Q2(CString SfnID_I,CString IDst_I,CString *IDst,CString *str_out,CString RLONbs,CString RLATbs,CString P_out,int mode=0); 
	CString QGE06_IntFrom_Q3(CString SfnID_I,CString RLONbs,CString RLATbs,CString P_out,CString *str_out); 
	CString QGE06_IntFrom_Q4(CString AdmRefID,CString SfnID_I,CString RLONbs,CString RLATbs,CString P_out,CString *str_out);
	CString QGE06_IntFrom_Q5(CString AssocAllotID,CString RLONbs,CString RLATbs,CString P_out,CString *str_out);
	int QGE06_IntFromFXM2DBCBT_Qy(double GRlat_W, double GRlon_W, double SR, double Freq_W, double FR); 
	CString QGE06_IntFromBCBT2FXM_Qx();

	//////////////////////////////////////////////////////////////////////////////////////////////////
	BOOL CrossPoint(double lat1,double lon1,double lat2,double lon2 , double *latN,double *lonN,long N
								 , double *latC,double *lonC);

	void Vec2NearPoint(double lat[], double lon[] ,long N, double lat0, double lon0 ,
								double *Nlat, double *Nlon) ;

	int GE06Zones(double lat01, double lon01 , double lat02, double lon02,double *zDist);
	void LoadMap_IDWM2p(int plan,double lat01, double lon01 , double lat02, double lon02);
	void LoadMap_IDWMpr(int plan,double lat01, double lon01 , double range);
	double E_P1546_06(double latST,double lonST,double lat0,double lon0,double h1,
							  double HasglST, double f_MHz, double kfactor,
							  double Ptime,double RxH,int ENV,int syst,double Plocation,
							  int P1546Clangle);

	double CNFS_Function_0(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
							double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
							CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
							double latCal,double lonCal,double CF,double  PRC,double  PRT,double  PR,
							int AntDisc, int ENV,double Ti,double kfactor,double A2D=0) ;

	double CNFS_FunctionAL_0(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
							double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,
							double lat_TP[],double lon_TP[],long NcontourT,double CF,double PRC,double PRT,double PR,
							int AntDisc, int ENV,double Ti) ;

	double InterpT(int *D0, double *E0, double d, long num, int LinLog=0);

	double CNFS_Function_Int_0(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								CString NoticeType_W,CString RXMode_W,CString RPC_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
								double latCal,double lonCal,double CF,double  PR,
								int AntDisc, int ENV,double Ti,double kfactor,double A2D=0); 

	double CNFS_FunctionAL_Int_0(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								CString NoticeType_W,CString RXMode_W,CString RPC_W,
								double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,
								double lat_TP[],double lon_TP[],long NcontourT,double CF,double PR,
								int AntDisc, int ENV,double Ti); 

	double CNFS_Function_FXM_0(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								double GeoLat_I,double GeoLon_I,double Freq_I, CString Pol_I, CString Hagl_I,
								CString AntDir_I, CString AntCatID_I, CString ERP_h_dbw_I,CString ERP_v_dbw_I,
								double latCal,double lonCal,double CF,double  PR,
								int AntDisc, int ENV,double Ti,double kfactor,int ant,double hR,
								CString AntDir_W,CString AntCatID_W); 

	double CNFS_FunctionAL_FXM_0(double GeoLat_W,double GeoLon_W,double Freq_W, CString Pol_W, CString Fragment_W,
								double latCal,double lonCal,double Freq_I, CString Pol_I, CString RPC_I,CString RN,
								double lat_TP[],double lon_TP[],long NcontourT,double CF,double PR,
								int AntDisc, int ENV,double Ti,int ant,double hR,
								CString AntDir_W,CString AntCatID_W); 


	void GE84patternT(long AntCatID, CString AntDir, CString Pol,int * az0,double * attH0,double * attV0);

	void GE06pattern(long AntID,double * attnH,double * attnV,CString pol);
	void GE06patternT(long AntCatID, CString AntDir, CString Pol,double * attH0,double * attV0); 

	long QGE06_IntFrom_C(CString SfnID,CString *IDst,CString *AllotC);

	void Vector2OnePoint(CString Vector_filepath,double *CRlat,double *CRlon) ;

	CString Vector2Placemark(CString Vector_filepath); 
	CString GE06ShowAllotGoogle(CString allotkey , CString GeoArea); 
	void QGE06_Digital_QyGoogle(CString IDst, int PEC, CString NoticeType, CString SfnID, CString allotkey,CString AdmRefID,CString AssocAllotID,CString STN,int flagC); 
	void GE06linked_ConvertedGoogle(int flagC); 
	BOOL m_GoogleFlag;
	double E_P154606AL_hR(double latST,double lonST,double lat0,double lon0,double h1,
						  double f_MHz, double Ptime, double RxH,int ENV);


//	void OnOverlay1();
	void OverlayFunction(CDocument *pD, double OverlayFactor, CDC *dc); 
 	CDocument *m_pDocOverlay;
	double	m_OverlayFactor;
	BOOL m_OverlayFlag;

	BOOL strCompare(CString sPath);

	void InvalidateVectorHandling();
	void DrawSymboleCopl(CDC* pDC,double lats,double lons,COLORREF color1,int len1); 
	
	BOOL QGE06_FXMBCBT_Q6Fter(long IDst, double FrqR, double FrqT, CString sttp);
	CString Cty2AdmGE06(CString *cty1);

	void OnDrawVectorCircle(CString sPath,int mode=0);
	CString BorderM2noPF(double LatX,double LonX,CString ctyA,double Dsearch);
	CString m_qCommonFields;
	CString m_qEarthStationAp7_Int;
	CString m_qGE84BC2BC;
	CString m_qGE89BT2BT;
	CString m_qLink_TX;
	CString m_qLink_RX;
	CString m_qQ_Links;
	CString m_qSTtableGE06;
	CString m_qSTtableGE06ASAL;
	CString m_qSTtable;
	void Function_Queries();
	void Set_STtable_Default();

	/////////////////////////////////////
	/////////////Argus///////////////////////
	///////////////////////////////////
	void FindArgusIniFile(CString *PathINBOX, CString *PathOUTBOX);
	CString m_PathINBOX , m_PathOUTBOX;
	BOOL m_ArgusOrder;
	UINT m_nTimerID;
	CMapWordToPtr m_thisList;
	void On_argusO_smsR(HWND hwnd);

	void Find_GSPorder(); 
	CString m_GSPFileName;
	BOOL m_GSPflag;

	UINT m_nTimerID2;
	CMapWordToPtr m_thisList2;

	BOOL m_ThalesOrder;
	UINT m_nTimerID3;
	CMapWordToPtr m_thisList3;
	void FindThalesIniFile(CString *PathINBOX, CString *PathOUTBOX, CString *PathREQUEST);
	CString m_PathINBOXth , m_PathOUTBOXth, m_PathREQUESTth;
	void On_ThalesAuto();

	CString DEG2DMSth(CString type,double x); 

	/////////////////////////////////////
	/////////////Monitoring Others///////////////////////
	///////////////////////////////////
	BOOL m_OthersOrder;
	UINT m_nTimerOthersID;
	CString m_PathINBOXothers , m_PathOUTBOXothers;
	CMapWordToPtr m_thisListOthers;
	void CSMS4DCView::FindOthersIniFile(CString *PathINBOX, CString *PathOUTBOX);
	void CSMS4DCView::On_othersO_smsR(HWND hwnd);



public:	
		CDocument * m_pDocVectors;
//		BOOL m_CircleDraw;
		int m_POLYnum;

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

		void OnRefresh1();
		void OnRefresh2();
		void OnDrawVector1(){OnDrawVector();};
		void VectorDesktop(CString sPath);

		double m_CoplLat, m_CoplLon;

		double BorderAnt(double latX, double lonX, double HaglX,double AZ0X, double EL0X, int f0[], double rH[], double rV[],
							double latY, double lonY, double HaglY,double kfactor);
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};


		void Get_ReqFile(CString Req_filepath); 
		CStringArray m_Grid1_thalesReq, m_Grid2_thalesReq, m_Grid3_thalesReq;
		int m_Num_thalesReq;
		CString OnBUTTONFile_thalesReq(CString mReq_filepath);

		//void OnBUTTONCreateCHK_thalesReq(CString mReq_filepath);
		void OnBUTTONCreateCHK_thalesReq(CString mReq_filepath,
													  double Ptime, double Plocation, double kfactor, double RxH, 
													  int syst, int ENV, int P1546Clangle, int P1546landsea );

		//int FindStationDB(double fmin,double fmax,CString D_Threshold,CString Ant,CString *Sout); 
		int FindStationDB(double fmin,double fmax,CString D_Threshold,CString Ant,CString *Sout,
													  double Ptime, double Plocation, double kfactor, double RxH, 
													  int syst, int ENV, int P1546Clangle, int P1546landsea);
 
		BOOL Thales_MissionType(CString PathFileReq); 
		BOOL ThalesAutoMissions() ;
		int FindMonitoringStation(CString * X, CString * Y);

		int PointInArea(double Lats,double Lons,double Lat1,double Lon1,double Lat2,double Lon2); 
		void SetBoxCorner(); 


		double CSMS4DCView::Interp1I(double *E0,double *D0,double E,int num);


double CSMS4DCView::FieldP1546V5_I0(double Latst,double Lonst,double az,double p,double h1,
								  double f_MHz,double t , double E,
								  double tetamax15_deg ,double h2, int ENV, double ha,
								  double Hgt, int srv, double L); 

double CSMS4DCView::FieldP1546V5_D(double Latst,double Lonst,double az,double pTX, double dist,double h1, double StepRes,
								  double f_MHz,double t,
								  double tetamax15_deg ,double h2, int ENV, double ha,
								  double Hgt, int srv, double L, BOOL P1546Clangle, BOOL P1546landsea);
double CSMS4DCView::LandWarmColdSea_D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,
									   double *D_SeaW_km, int *p2);

void CSMS4DCView::LoadIDWMmap_r(double lat1_deg,double lon1_deg,double r_km); 
	double pi, D2R, R2D;


double CSMS4DCView::FieldP1812V3_D0(double LatST, double LonST, double dist, double az, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone);
double CSMS4DCView::FieldP1812V3_I0(double LatST, double LonST, double E, double az, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone);

double CSMS4DCView::FieldP1812V3_D(double LatST, double LonST, double dist, double az, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone);
int CSMS4DCView::dat_filesDATA(CString dat_fname, float data[121][241]);
double CSMS4DCView::dat_filesDATAout(double LatM,double LongM, float data[121][241]);
int CSMS4DCView::LandSeaCoastal_noMap(double RLON_deg,double RLAT_deg); 

CString CSMS4DCView::LandSeaCoastal_C(double RLON_deg,double RLAT_deg); 

double CSMS4DCView::E_P1546_V05(double latST,double lonST,double lat0,double lon0,
						  double HaglST, double f_MHz,double PtGtSTw, double kfactor,
						  double Ptime,double RxH,int ENV,int syst,double Plocation,
						  int P1546Clangle , int P1546landsea,int p);

CString CSMS4DCView::GetRxDataIntermodulation(); 
BOOL CSMS4DCView::GetTxDataIntermodulation(long IDX,double latX, double lonX,  double Drange); 

///////////////////////////////////////////////////
void CSMS4DCView::OnDraw1(CDC* pDC);
void CSMS4DCView::OnDraw2(CDC* pDC);
void CSMS4DCView::OnDraw_Objects(CDC* pDC);

HBITMAP Draw_hBitmap3D(CSMS4DCDoc* pDoc);
HBITMAP Draw_hBitmap2D(CSMS4DCDoc* pDoc);
HBITMAP Draw_hBitmap(CSMS4DCDoc* pDoc);
void CSMS4DCView::Del_hBitmap(void);

HBITMAP	m_hBitmap;
void CSMS4DCView::UpDate_hBitmap(void);
void CSMS4DCView::UpDate_hBitmap(CSMS4DCDoc* pDoc);
HBITMAP CSMS4DCView::CreateADIBSection(HDC hScrDC,int W, int H);


int CSMS4DCView::chInd(int I, int Npx);	
COLORREF CSMS4DCView::hillshade_new(CSMS4DCDoc* pDoc, int px, int py, int W, int H, COLORREF c);

COLORREF CSMS4DCView::IJ2Color(CSMS4DCDoc* pDoc,int i, int j, _int16 min1, _int16 max1); 
BOOL m_3D;
COLORREF CSMS4DCView::Z2Color(CSMS4DCDoc* pDoc, double z);	
void CSMS4DCView::InvalidateLegend(void);	//97/12/26	
BOOL m_ColorMapNegative;

///////////////////////98/01/06
double CSMS4DCView::FieldP1812V3_Dn(double LatST, double LonST, double dist, double az, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone,
												int Np, double *mD, double *mH, int *mZ);

int CSMS4DCView::FieldP1812V3_profile(double LatST, double LonST, double dist, double az, double StepRes,
									   double *mD, double *mH, int *mZ);

double CSMS4DCView::LatLon2Hg_n(double lat_deg,double lon_deg); 
double CSMS4DCView::RoundBUF_Hg_n(double xps,double yps) ;

//98/01/11
void CSMS4DCView::TransparentBlt_AlphaBlend(CDC* dc,    int Left, int Top, int Width, int Height,
											CDC* MemDC, int rL,   int rT,  int rW,    int rH, 
											const COLORREF Color, BYTE Alpha, int bTA=2);

//98/12/17
void CSMS4DCView::OnPropagationmodelsP18123NPBS();
void CSMS4DCView::OnPropagationmodelsP18123NPMFS();
void CSMS4DCView::OnPropagationmodelsP1546NPBS(); 
void CSMS4DCView::OnPropagationmodelsP1546NPMFS();
void CSMS4DCView::OnFreespaceNPBS();
void CSMS4DCView::OnFreespaceNPMFS();
};

#ifndef _DEBUG  // debug version in SMS4DCView.cpp
inline CSMS4DCDoc* CSMS4DCView::GetDocument()
   { return (CSMS4DCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMS4DCVIEW_H__3ED3AD6C_C9F7_4923_B19E_C8CFE11D743E__INCLUDED_)
