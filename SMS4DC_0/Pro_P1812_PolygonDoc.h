#if !defined(AFX_PRO_P1812_POLYGONDOC_H__02CB8D6E_069F_4167_9CA5_C2116554F25C__INCLUDED_)
#define AFX_PRO_P1812_POLYGONDOC_H__02CB8D6E_069F_4167_9CA5_C2116554F25C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1812_PolygonDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1812_PolygonDoc document

class CPro_P1812_PolygonDoc : public CDocument
{
protected:
	CPro_P1812_PolygonDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P1812_PolygonDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1812_PolygonDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P1812_PolygonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P1812_PolygonDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int Np;
	double *m_hi;
	double *m_di;
	double *m_lati;
	double *m_loni;

	double Dmin,Dmax;

	double *Er;
	
	int m_PolyPointNum;
	int *Npt;
	int m_ReadyDoc;

	double Linelat_ST,Linelon_ST,LinePtGt_ST,LineHagl_ST,LineAZ_ST,LineEL_ST,LineHasl_ST,LinefMHz_ST;
	CString LineName_ST,LineANT_ST;

	_int16 *bufArea;
	_int16 *bufAreaP1812;
	int bufAreaW,bufAreaH;
	int Width,Height,m_ZoomFactor;
	_int16 m_NoData;
	double Linelat0,Linelon0,m_Resolution_x;
	CString TileInfo;
	double Linetime,Linelocation,Linek,LineRxH;
	BOOL LineClangle,Linelandsea;
	int LineSrv,LineClutter,LineIODoor;

	double Distance_km(double lat1,double lon1,double lat2,double lon2);
	void GetData(); 
	void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV);
	double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2);
	double Interp2(int *D0,double *E0,double d,int num);

	void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
	double Points2HgAvr(CPoint point1 , CPoint point2); 
	double Point2Hg(CPoint point1) ;
	double TCAcorr1546(double Tdeg,double f_MHz);
	int Round(double x);

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

	int dat_filesDATA(CString dat_fname, float data[121][241]);
	double dat_filesDATAout(double LatM,double LongM, float data[121][241]);
	CString LinePolarizationTx;
	int LandSeaCoastal(double RLON_deg,double RLAT_deg);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1812_POLYGONDOC_H__02CB8D6E_069F_4167_9CA5_C2116554F25C__INCLUDED_)
