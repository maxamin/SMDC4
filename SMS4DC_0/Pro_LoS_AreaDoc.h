#if !defined(AFX_PRO_LOS_AREADOC_H__628298F1_0CEB_401A_B743_547C9F15643B__INCLUDED_)
#define AFX_PRO_LOS_AREADOC_H__628298F1_0CEB_401A_B743_547C9F15643B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_LoS_AreaDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_AreaDoc document

#include "Tile.h"

class CPro_LoS_AreaDoc : public CDocument
{
protected:
	CPro_LoS_AreaDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_LoS_AreaDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_LoS_AreaDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_LoS_AreaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_LoS_AreaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

		double LoSlat0,LoSlon0,LoSlat_ST,LoSlon_ST,LoSHagl_ST,LoSPtGt_ST;
		int bufAreaW,bufAreaH;
		CString LoSName_ST;
		_int16 *bufArea;
		_int16 *bufAreaLoS;
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
		double LoSk,LoSRxH;

		CString TileInfo;

		void GetData();
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
//		int Round(double x) ;
		void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
		double Point2Hg(CPoint point1) ;
		double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;
		void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
		BOOL PeekAndPump();
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
int TileX;
		double LoSlatmax,LoSlonmax;
		double CPro_LoS_AreaDoc::LatLon2Hg(double lat_deg,double lon_deg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_LOS_AREADOC_H__628298F1_0CEB_401A_B743_547C9F15643B__INCLUDED_)
