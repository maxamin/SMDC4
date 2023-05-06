#if !defined(AFX_PRO_P1812_AREADOC_H__9158BCFA_6065_4DEE_B880_1B6485554FEB__INCLUDED_)
#define AFX_PRO_P1812_AREADOC_H__9158BCFA_6065_4DEE_B880_1B6485554FEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1812_AreaDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_AreaDoc document

#include "Tile.h"

class CPro_P1812_AreaDoc : public CDocument
{
protected:
	CPro_P1812_AreaDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P1812_AreaDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1812_AreaDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P1812_AreaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P1812_AreaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		double P1812time,P1812location,P1812k,P1812RxH;
		int P1812Service,P1812Clutter, P1812IODoor;

		double P1812lat0,P1812lon0,P1812lat_ST,P1812lon_ST,P1812PtGt_ST,P1812Hagl_ST,P1812fMHz_ST,P1812AZ_ST,P1812EL_ST;
		int bufAreaW,bufAreaH;
		CString P1812Name_ST,P1812ANT_ST;
		_int16 *bufArea;
		_int16 *bufAreaP1812;
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
		CString P1812Polarization_ST;

		void GetData();
		void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
		double Point2Hg(CPoint point1);
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
		double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;
		void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;

		void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) ;
		BOOL PeekAndPump();
		double Interp2(int *D0,double *E0,double d,int num);

		int m_level;
		BOOL m_bThreshold;
		double m_Threshold;
		double m_AreaTotal;

		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
		int TileX;

		double LatLon2Hg(double lat_deg,double lon_deg);
		double pi, D2R, R2D;

		void PathMean(double lon10, double lat10, double lon20, double lat20, double *LongM, double *LatM);
		int LandSeaCoastal(double RLON_deg,double RLAT_deg);

		int dat_filesDATA(CString dat_fname, float data[121][241]);
		double dat_filesDATAout(double LatM,double LongM, float data[121][241]);

		double RoundBUF_Hg(double xps,double yps);
		double LatLon2Hg0(double lat_deg,double lon_deg);
		void LoadIDWMmap();

		double BasicTxLossP1812V3_D(double LatST, double LonST, double lati, double loni, double Hgi, double StepRes,
												float dataDN50[121][241], float dataN050[121][241],
												double pTime, double pLocation, double f_GHz, double Ht, double Hr, 
												int pol, int srv, int InOutDoor, int zone);
		double P1812latmax,P1812lonmax;

		int Round(double x);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1812_AREADOC_H__9158BCFA_6065_4DEE_B880_1B6485554FEB__INCLUDED_)
