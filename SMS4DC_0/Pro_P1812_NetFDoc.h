#if !defined(AFX_PRO_P1812_NETFDOC_H__F3B88785_5373_446B_AEBC_51EE34920731__INCLUDED_)
#define AFX_PRO_P1812_NETFDOC_H__F3B88785_5373_446B_AEBC_51EE34920731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1812_NetFDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_NetFDoc document
#include "Tile.h"

class CPro_P1812_NetFDoc : public CDocument
{
protected:
	CPro_P1812_NetFDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P1812_NetFDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1812_NetFDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P1812_NetFDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P1812_NetFDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		double P1812time,P1812location,P1812k,P1812RxH;
		int P1812Service, P1812IODoor, P1812Clutter;

		double P1812lat0,P1812lon0,*P1812lat_ST,*P1812lon_ST,*P1812PtGt_ST,*P1812Hagl_ST,*P1812fGHz_ST,*P1812AZ_ST,*P1812EL_ST;
		int *P1812iPolarization_ST;

		int bufAreaW,bufAreaH;
		CString *P1812Name_ST;
		CString *P1812ANT_ST;
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
		int Nrow;

		void GetData();
		void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
		double Point2Hg(CPoint point1);
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
		double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;
		void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
		double Points2HgAvr(CPoint point1 , CPoint point2) ;
		int Round(double x) ;

		double TCAcorr1546(double Tdeg,double f_MHz);
		void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV);
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

		double pi, D2R, R2D;
		double LatLon2Hg0(double lat_deg,double lon_deg); 
		double LatLon2Hg(double lat_deg,double lon_deg) ;
		double RoundBUF_Hg(double xps,double yps); 
		void LoadIDWMmap(); 
		double LandWarmColdSea_D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,
									   double *D_SeaW_km, int *p2);

		void PathMean(double lon10, double lat10, double lon20, double lat20, double *LongM, double *LatM);
		int LandSeaCoastal(double RLON_deg,double RLAT_deg);

		int dat_filesDATA(CString dat_fname, float data[121][241]);
		double dat_filesDATAout(double LatM,double LongM, float data[121][241]);

		double P1812latmax,P1812lonmax;


//Monitoring
		void CPro_P1812_NetFDoc::GetData0();
		void CPro_P1812_NetFDoc::GetData1();
		void CPro_P1812_NetFDoc::GetData2();
		BOOL CPro_P1812_NetFDoc::Test1(double * Erm, int n, double Eth);
		BOOL CPro_P1812_NetFDoc::Test2totaln(double * Erm, int n, double Eth, double * lat_ST, double * lon_ST, double lat_j, double lon_i, double *dist1234);
		double CPro_P1812_NetFDoc::Find_Point(double lat_ST1,double lon_ST1,double lat_ST2,double lon_ST2,double lat_j,double lon_i);
		BOOL CPro_P1812_NetFDoc::Find_Point2Lines(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);
		BOOL CPro_P1812_NetFDoc::Find_Point2Lines_(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);
		BOOL CPro_P1812_NetFDoc::Find_Point2Lines__(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);

		double m_teta_deg;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1812_NETFDOC_H__F3B88785_5373_446B_AEBC_51EE34920731__INCLUDED_)
