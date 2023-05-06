#if !defined(AFX_PRO_HATA_NETBDOC_H__BEA707AF_C011_44DD_A1AD_F387670FFB72__INCLUDED_)
#define AFX_PRO_HATA_NETBDOC_H__BEA707AF_C011_44DD_A1AD_F387670FFB72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_HATA_NetBDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_NetBDoc document
#include "Tile.h"

class CPro_HATA_NetBDoc : public CDocument
{
protected:
	CPro_HATA_NetBDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_HATA_NetBDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_HATA_NetBDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_HATA_NetBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_HATA_NetBDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		double HATAk,HATARxH;
		int HATAenvironment;

		double HATAlat0,HATAlon0,*HATAlat_ST,*HATAlon_ST,*HATAPtGt_ST,*HATAHagl_ST,*HATAfMHz_ST,*HATAAZ_ST,*HATAEL_ST;
		CString *HATAName_ST,*HATAANT_ST;
		
		int bufAreaW,bufAreaH;
		_int16 *bufArea;
		_int16 *bufAreaHATA;
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
		double Eth;
		BOOL EthFlag;

		void GetData();
		void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
		double Point2Hg(CPoint point1);
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
		double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;
		void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
		double Points2HgAvr(CPoint point1 , CPoint point2) ;
		int Round(double x) ;

		void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV);
		BOOL PeekAndPump();
		double Interp2(int *D0,double *E0,double d,int num); 

		double m_HATAa1,m_HATAa2,m_HATAa3,m_HATAb1,m_HATAb2;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
int TileX;
		double HATAlatmax,HATAlonmax;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_HATA_NETBDOC_H__BEA707AF_C011_44DD_A1AD_F387670FFB72__INCLUDED_)
