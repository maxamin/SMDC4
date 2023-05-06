#if !defined(AFX_INT_BT2BT_FREEDOC_H__3E4A36F5_285D_4AA2_BD39_885943106CA9__INCLUDED_)
#define AFX_INT_BT2BT_FREEDOC_H__3E4A36F5_285D_4AA2_BD39_885943106CA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_BT2BT_FreeDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_BT2BT_FreeDoc document
#include "Tile.h"

class CInt_BT2BT_FreeDoc : public CDocument
{
protected:
	CInt_BT2BT_FreeDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInt_BT2BT_FreeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_BT2BT_FreeDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInt_BT2BT_FreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CInt_BT2BT_FreeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		int bufAreaW,bufAreaH;
		_int16 *bufArea;
		_int16 *bufAreaFree;
		double *Er;
		double ErMin, ErMax;

		void GetData();
		int m_ZoomFactor;
		_int16 bufMin, bufMax;
		int Width,Height,m_ReadyDoc;

		double Freelat0,Freelon0,Freelat_ST,Freelon_ST,FreePtGt_ST;
		double m_Resolution_x;

		CString TileInfo;
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
		double m_MinValue , m_MaxValue;
		_int16 m_NoData;
		COLORREF RGBt[256];
		CTile m_tile;
		CString colormaptype;

		int m_level;
		BOOL m_bThreshold;
		double m_Threshold;
		double m_AreaTotal;

		double *m_latY,*m_lonY;
		double m_Fmin;
		int Nrow;

		CString m_SelX;
		CString GetFld(CString Src,int N);
		void GE84pattern(long terrakey,double * attnH,double * attnV,CString pol) ;
		double Interp2(int *D0,double *E0,double d,int num) ;
		double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;
		BOOL PeekAndPump();
		double Dist_km_Az_Deg(double lat1,double lon1,double lat2,double lon2,double *RAZIM) ;

		double *ErU,*ErC;
		double ErUMin, ErUMax,ErCMin, ErCMax;
		double P_Location;
		int methodSUM;
		BOOL m_AntDisc;
		BOOL m_PolDisc;
		double m_EDIT_PolDisc;
		CString FreeName_ST;
		CString *m_nameY;

		double Freelatmax,Freelonmax;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_BT2BT_FREEDOC_H__3E4A36F5_285D_4AA2_BD39_885943106CA9__INCLUDED_)
