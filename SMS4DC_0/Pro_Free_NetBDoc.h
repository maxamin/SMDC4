#if !defined(AFX_PRO_FREE_NETBDOC_H__D8ABEFB1_F6E0_4EC8_99ED_9EC39F6227C9__INCLUDED_)
#define AFX_PRO_FREE_NETBDOC_H__D8ABEFB1_F6E0_4EC8_99ED_9EC39F6227C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_Free_NetBDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_NetBDoc document
#include "Tile.h"

class CPro_Free_NetBDoc : public CDocument
{
protected:
	CPro_Free_NetBDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_Free_NetBDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_Free_NetBDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_Free_NetBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_Free_NetBDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		double Freelat0,Freelon0,*Freelat_ST,*Freelon_ST,*FreePtGt_ST,*FreeHagl_ST,*FreeAZ_ST,*FreeEL_ST;
		int bufAreaW,bufAreaH;
		double Freek,FreeRxH;

		CString *FreeName_ST,*FreeANT_ST;
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
		double Eth;
		BOOL EthFlag;

		void GetData();
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
		int Round(double x) ;

		BOOL PeekAndPump();

		double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;

		void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) ;
		void LatLon2Point(double lat_deg,double lon_deg,CPoint *PointSt) ;
		double Point2Hg(CPoint point1) ;
		double Interp2(int *D0,double *E0,double d,int num); 
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
int TileX;
		double Freelatmax,Freelonmax;


//Monitoring
		void CPro_Free_NetBDoc::GetData0();
		void CPro_Free_NetBDoc::GetData1();
		void CPro_Free_NetBDoc::GetData2();
		void CPro_Free_NetBDoc::GetData3();
		BOOL CPro_Free_NetBDoc::Test1(double * Erm, int n, double Eth);
		BOOL CPro_Free_NetBDoc::Test3total(double * Erm, int n, double Eth);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_FREE_NETBDOC_H__D8ABEFB1_F6E0_4EC8_99ED_9EC39F6227C9__INCLUDED_)
