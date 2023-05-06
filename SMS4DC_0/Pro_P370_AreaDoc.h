#if !defined(AFX_PRO_P370_AREADOC_H__2EA0FCDB_2D8B_4844_9363_16F680A31AC2__INCLUDED_)
#define AFX_PRO_P370_AREADOC_H__2EA0FCDB_2D8B_4844_9363_16F680A31AC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P370_AreaDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_AreaDoc document

#include "Tile.h"

class CPro_P370_AreaDoc : public CDocument
{
protected:
	CPro_P370_AreaDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P370_AreaDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P370_AreaDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P370_AreaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P370_AreaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		double P370time,P370location,P370k,P370RxH;
		BOOL P370Clangle,P370landsea;
		int P370syst,P370environment;

		double P370lat0,P370lon0,P370lat_ST,P370lon_ST,P370PtGt_ST,P370Hagl_ST,P370fMHz_ST,P370AZ_ST,P370EL_ST;
		int bufAreaW,bufAreaH;
		CString P370Name_ST,P370ANT_ST;
		_int16 *bufArea;
		_int16 *bufAreaP370;
		double m_Resolution_x;

		_int16 bufMin, bufMax;
		_int16 m_NoData;
		COLORREF RGBt[256];
		CTile m_tile;
		CString colormaptype;
		int m_ZoomFactor;
		double *Er;
		double ErMin, ErMax;
		int Width,Height,m_ReadyDoc;
		double m_MinValue , m_MaxValue;
		CString TileInfo;

		void GetData();
		void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
		double Point2Hg(CPoint point1);
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
		double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;
		void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
		double Points2HgAvr(CPoint point1 , CPoint point2) ;
		int Round(double x) ;

		void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) ;
		BOOL PeekAndPump();
		double Interp2(int *D0,double *E0,double d,int num); 
		int m_level;
		BOOL m_bThreshold;
		double m_Threshold;
		double m_AreaTotal;

		int WarmColdSea(double RLON_deg,double RLAT_deg) ;
		int LandWarmColdSea(double RLON_deg,double RLAT_deg) ;
		double D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,double *D_SeaW_km) ;
		void WarmColdCross(double RLON_deg1,double RLAT_deg1,double RLON_deg2,double RLAT_deg2,
								  double *RLON_degcross,double *RLAT_degcross); 

		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
int TileX;
		double P370latmax,P370lonmax;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P370_AREADOC_H__2EA0FCDB_2D8B_4844_9363_16F680A31AC2__INCLUDED_)
