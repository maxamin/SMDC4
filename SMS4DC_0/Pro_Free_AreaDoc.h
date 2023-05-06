#if !defined(AFX_PRO_FREE_AREADOC_H__9A6A8FDD_8C1D_4D28_BA7F_90FFC9E46F45__INCLUDED_)
#define AFX_PRO_FREE_AREADOC_H__9A6A8FDD_8C1D_4D28_BA7F_90FFC9E46F45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_Free_AreaDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_AreaDoc document

#include "Tile.h"

class CPro_Free_AreaDoc : public CDocument
{
protected:
	CPro_Free_AreaDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_Free_AreaDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_Free_AreaDoc)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_Free_AreaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_Free_AreaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

		double Freelat0,Freelon0,Freelat_ST,Freelon_ST,FreePtGt_ST,FreeHagl_ST,FreeAZ_ST,FreeEL_ST;
		int bufAreaW,bufAreaH;
		double Freek,FreeRxH;
		CString FreeName_ST,FreeANT_ST;
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
		void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
int TileX;
		double Freelatmax,Freelonmax;
		double CPro_Free_AreaDoc::LatLon2Hg(double lat_deg,double lon_deg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_FREE_AREADOC_H__9A6A8FDD_8C1D_4D28_BA7F_90FFC9E46F45__INCLUDED_)
