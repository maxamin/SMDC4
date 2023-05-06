#if !defined(AFX_EFFECTIVEHEIGTHDOC_H__FD4FC8D1_66DC_4CC4_980A_98E724634437__INCLUDED_)
#define AFX_EFFECTIVEHEIGTHDOC_H__FD4FC8D1_66DC_4CC4_980A_98E724634437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EffectiveHeigthDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthDoc document

#include "Tile.h"

class CEffectiveHeigthDoc : public CDocument
{
protected:
	CEffectiveHeigthDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEffectiveHeigthDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEffectiveHeigthDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEffectiveHeigthDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CEffectiveHeigthDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		int Width,Height;
		_int16 bufMin, bufMax;
		_int16 m_NoData;
		COLORREF RGBt[256];
		CTile m_tile;
		CString TileInfo,colormaptype;
		
		_int16 *bufArea;

		int m_ZoomFactor;
		void GetData();
		double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
		double lat0,lon0,lat_ST,lon_ST,m_Resolution_x,Hagl_ST;
		CString Name_ST;

		int m_W_Heff,m_H_Heff;
		_int16 *bufAreaHeff;
		double bufAreaHeff_lat0,bufAreaHeff_lon0;
		double bufAreaHeff_lat_ST,bufAreaHeff_lon_ST,bufAreaHeff_Hagl_ST;
		CString bufAreaHeff_Name_ST;
		int m_ReadyDoc;
		long m_ID_ST, m_ID_Ant;
		double m_Hasl,m_Heff[73];

		int m_bflag;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EFFECTIVEHEIGTHDOC_H__FD4FC8D1_66DC_4CC4_980A_98E724634437__INCLUDED_)
