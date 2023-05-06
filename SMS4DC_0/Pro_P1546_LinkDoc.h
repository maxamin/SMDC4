#if !defined(AFX_PRO_P1546_LINKDOC_H__322A5DAE_C48B_4327_B744_52B2DB4C9D32__INCLUDED_)
#define AFX_PRO_P1546_LINKDOC_H__322A5DAE_C48B_4327_B744_52B2DB4C9D32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1546_LinkDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_LinkDoc document

class CPro_P1546_LinkDoc : public CDocument
{
protected:
	CPro_P1546_LinkDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P1546_LinkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1546_LinkDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P1546_LinkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P1546_LinkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_DrawFresnel;
	double Hmin,m_Gt,m_Gr,Linklat_Rx,Linklon_Rx;
	CString LinkName_Rx;
	double	m_heff,m_Distance,m_FsLoss,m_Loss1546,m_RxCL,m_TxCL,m_TotalLoss;


	int Np;
	double *m_hi;
	double *m_di;
	double *m_lati;
	double *m_loni;

	double Dmin,Dmax;

	double Er;
	int m_ReadyDoc;
	double Linklat_ST,Linklon_ST,LinkPtGt_ST,LinkHagl_ST,LinkAZ_ST,LinkEL_ST,LinkHasl_ST,LinkfMHz_ST;
	CString LinkName_ST,LinkANT_ST;

	int bufAreaW,bufAreaH;
	int Width,Height,m_ZoomFactor;
	_int16 *bufArea;
	_int16 *bufAreaP1546;

	double Linklat0,Linklon0,m_Resolution_x;
	CString TileInfo;
	double Linktime,Linklocation,Linkk,LinkRxH;
	BOOL LinkClangle,Linklandsea;
	int Linksyst,Linkenvironment;
	_int16 m_NoData;

	double Distance_km(double lat1,double lon1,double lat2,double lon2);
	int GetData(); 
	int ReadAntennaData(CString antfile,int *f0,double *rH,double *rV);
	void MissingAntena();

	double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2);
	int Round(double x);
	double Interp2(int *D0,double *E0,double d,int num);

	void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
	double Points2HgAvr(CPoint point1 , CPoint point2); 
	double Point2Hg(CPoint point1) ;
	double TCAcorr1546(double Tdeg,double f_MHz);

	int WarmColdSea(double RLON_deg,double RLAT_deg) ;
	int LandWarmColdSea(double RLON_deg,double RLAT_deg) ;
	double D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,double *D_SeaW_km) ;
	void WarmColdCross(double RLON_deg1,double RLAT_deg1,double RLON_deg2,double RLAT_deg2,
							  double *RLON_degcross,double *RLAT_degcross); 
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
	
	double pi, D2R, R2D;
	void LoadIDWMmap(); 
	double LandWarmColdSea_D_Sea_kmIDWM(double lat1_deg,double lon1_deg,double lat2_deg,double lon2_deg,
									   double *D_SeaW_km, int *p2);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1546_LINKDOC_H__322A5DAE_C48B_4327_B744_52B2DB4C9D32__INCLUDED_)
