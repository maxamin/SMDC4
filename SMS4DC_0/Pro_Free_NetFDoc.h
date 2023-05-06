#if !defined(AFX_PRO_FREE_NETFDOC_H__2688F755_529D_414C_A9AE_EEE8559E1D5F__INCLUDED_)
#define AFX_PRO_FREE_NETFDOC_H__2688F755_529D_414C_A9AE_EEE8559E1D5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_Free_NetFDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_NetFDoc document
#include "Tile.h"

class CPro_Free_NetFDoc : public CDocument
{
protected:
	CPro_Free_NetFDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_Free_NetFDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_Free_NetFDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_Free_NetFDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_Free_NetFDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

		double Freelat0,Freelon0,*Freelat_ST,*Freelon_ST,*FreePtGt_ST,*FreeHagl_ST,*FreeAZ_ST,*FreeEL_ST;
		int bufAreaW,bufAreaH;
		double Freek,FreeRxH;
		CString *FreeANT_ST;

		CString *FreeName_ST;
		_int16 *bufArea;
		_int16 *bufAreaFree;
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
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
		int Round(double x) ;

		BOOL PeekAndPump();

		double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;

		void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) ;
		void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
		double Point2Hg(CPoint point1) ;
		double Interp2(int *D0,double *E0,double d,int num); 
		int m_level;
		BOOL m_bThreshold;
		double m_Threshold;
		double m_AreaTotal;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
int TileX;
		double Freelatmax,Freelonmax;

//Monitoring
//////////////////////////
		void CPro_Free_NetFDoc::GetData0();
		void CPro_Free_NetFDoc::GetData1();
		void CPro_Free_NetFDoc::GetData2();
		BOOL CPro_Free_NetFDoc::Test1(double * Erm, int n, double Eth);
		void CPro_Free_NetFDoc::reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg);
		double D2R,R2D,pi;
		double CPro_Free_NetFDoc::Find_Point(double lat_ST1,double lon_ST1,double lat_ST2,double lon_ST2,double lat_j,double lon_i);
		BOOL CPro_Free_NetFDoc::Find_Point2Lines(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);
		BOOL CPro_Free_NetFDoc::Find_Point2Lines_(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);
		BOOL CPro_Free_NetFDoc::Find_Point2Lines__(double lat1,double lon1, double az1, double lat2,double lon2,double az2, double *latC_deg, double *lonC_deg);

		BOOL CPro_Free_NetFDoc::Test2totaln(double * Erm, int n, double Eth, double * lat_ST, double * lon_ST, double lat_j, double lon_i, double *dist1234);

		double m_teta_deg;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_FREE_NETFDOC_H__2688F755_529D_414C_A9AE_EEE8559E1D5F__INCLUDED_)
