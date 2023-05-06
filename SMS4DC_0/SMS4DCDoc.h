// SMS4DCDoc.h : interface of the CSMS4DCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMS4DCDOC_H__135B84A7_FC45_40BF_A025_01999F69E88C__INCLUDED_)
#define AFX_SMS4DCDOC_H__135B84A7_FC45_40BF_A025_01999F69E88C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Tile.h"

class CSMS4DCDoc : public CDocument
{
protected: // create from serialization only
	CSMS4DCDoc();
	DECLARE_DYNCREATE(CSMS4DCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMS4DCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSMS4DCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSMS4DCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
		COLORREF RGBt[256];
		_int16 bufMax  ,   bufMin;
	//	_int16 (*buf)[1200];
		_int16 buf[1200][1200];
		int Width,Height;
		CString TileInfo,colormaptype;
		int TileX,TileY;
		CTile m_tile;
		double m_Lower_left_x;
		double m_Lower_left_y;
		double m_Resolution_x;
		double m_Resolution_y;
		double m_NoData;
		char m_MachineFormat[1];
		void GetData();

		int m_Npx,m_Npy,m_Nod;
		char m_FilesPath[100],		m_FilesPrefix[20];
		void PreGetData();
		int m_Nxmax, m_Nymax;

		BOOL IsMapCircle();
		long Round(double x); 


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMS4DCDOC_H__135B84A7_FC45_40BF_A025_01999F69E88C__INCLUDED_)
