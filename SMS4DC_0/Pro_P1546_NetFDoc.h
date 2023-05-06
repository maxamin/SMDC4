#if !defined(AFX_PRO_P1546_NETFDOC_H__9868FB4B_1BFD_45AE_B02F_0C9F4B82F7B9__INCLUDED_)
#define AFX_PRO_P1546_NETFDOC_H__9868FB4B_1BFD_45AE_B02F_0C9F4B82F7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1546_NetFDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_NetFDoc document
#include "Tile.h"

class CPro_P1546_NetFDoc : public CDocument
{
protected:
	CPro_P1546_NetFDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P1546_NetFDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1546_NetFDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P1546_NetFDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P1546_NetFDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		double P1546time,P1546location,P1546k,P1546RxH;
		BOOL P1546Clangle,P1546landsea;
		int P1546syst,P1546environment;

		double P1546lat0,P1546lon0,*P1546lat_ST,*P1546lon_ST,*P1546PtGt_ST,*P1546Hagl_ST,*P1546fMHz_ST,*P1546AZ_ST,*P1546EL_ST;
		int bufAreaW,bufAreaH;
		CString *P1546Name_ST;
		CString *P1546ANT_ST;
		_int16 *bufArea;
		_int16 *bufAreaP1546;
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
		double P1546latmax,P1546lonmax;

		void CPro_P1546_NetFDoc::GetData0();
		void CPro_P1546_NetFDoc::GetData1();
		void CPro_P1546_NetFDoc::GetData2();
		BOOL CPro_P1546_NetFDoc::Test1(double * Erm, int n, double Eth);
		BOOL CPro_P1546_NetFDoc::Test2totaln(double * Erm, int n, double Eth, double * lat_ST, double * lon_ST, double lat_j, double lon_i, double *dist1234);
		BOOL CPro_P1546_NetFDoc::Find_Point2Lines(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);
		BOOL CPro_P1546_NetFDoc::Find_Point2Lines_(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);
		BOOL CPro_P1546_NetFDoc::Find_Point2Lines__(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);
		double CPro_P1546_NetFDoc::Find_Point(double lat_ST1,double lon_ST1,double lat_ST2,double lon_ST2,double lat_j,double lon_i) ;

		double m_teta_deg;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1546_NETFDOC_H__9868FB4B_1BFD_45AE_B02F_0C9F4B82F7B9__INCLUDED_)
