#if !defined(AFX_PRO_LOS_LINEDOC_H__3F446E5F_1E6C_469B_9530_2CD66FBD4CA6__INCLUDED_)
#define AFX_PRO_LOS_LINEDOC_H__3F446E5F_1E6C_469B_9530_2CD66FBD4CA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_LoS_LineDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineDoc document

class CPro_LoS_LineDoc : public CDocument
{
protected:
	CPro_LoS_LineDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_LoS_LineDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_LoS_LineDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_LoS_LineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_LoS_LineDoc)
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
	int m_ReadyDoc;
	double Linelat_ST,Linelon_ST,LineHagl_ST,LineHasl_ST;
	CString LineName_ST;
	double LineRxH ,   Linek;

	double Distance_km(double lat1,double lon1,double lat2,double lon2);
	void GetData(); 
	double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2);
	void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
	void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt); 
	double Point2Hg(CPoint point1); 


	_int16 *bufArea;
	_int16 *bufAreaLoS;
	int bufAreaW,bufAreaH;
	int Width,Height,m_ZoomFactor;
	double Linelat0,Linelon0,m_Resolution_x;
	CString TileInfo;

	double *Er0,*Er1,Hmin;
int TileX;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_LOS_LINEDOC_H__3F446E5F_1E6C_469B_9530_2CD66FBD4CA6__INCLUDED_)
