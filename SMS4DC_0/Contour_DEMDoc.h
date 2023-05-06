#if !defined(AFX_CONTOUR_DEMDOC_H__EB7C172D_D5E9_4377_983A_BA4C39FD28DE__INCLUDED_)
#define AFX_CONTOUR_DEMDOC_H__EB7C172D_D5E9_4377_983A_BA4C39FD28DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Contour_DEMDoc.h : header file
//
#include "Tile.h"

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMDoc document

class CContour_DEMDoc : public CDocument
{
protected:
	CContour_DEMDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CContour_DEMDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContour_DEMDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CContour_DEMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CContour_DEMDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

		double Freelat0,Freelon0;
		int bufAreaW,bufAreaH;
		_int16 *bufArea;
		_int16 *bufAreaFree;
		double m_Resolution_x,m_Resolution_y;

		_int16 bufMin, bufMax;
		_int16 m_NoData;
		COLORREF RGBt[256];
		CTile m_tile;
		CString colormaptype;
		int m_ZoomFactor;
		int Width,Height,m_ReadyDoc;
		double m_MinValue , m_MaxValue;

		CString TileInfo;

		void GetData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTOUR_DEMDOC_H__EB7C172D_D5E9_4377_983A_BA4C39FD28DE__INCLUDED_)
