#if !defined(AFX_PRO_FREE_POLYGONDOC_H__144B9DAD_2E4E_41AC_90AF_F299B7F453F3__INCLUDED_)
#define AFX_PRO_FREE_POLYGONDOC_H__144B9DAD_2E4E_41AC_90AF_F299B7F453F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_Free_PolygonDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_Free_PolygonDoc document

class CPro_Free_PolygonDoc : public CDocument
{
protected:
	CPro_Free_PolygonDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_Free_PolygonDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_Free_PolygonDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_Free_PolygonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_Free_PolygonDoc)
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

	double Linelat_ST,Linelon_ST,LinePtGt_ST,LineHagl_ST,LineAZ_ST,LineEL_ST,LineHasl_ST;
	CString LineName_ST,LineANT_ST;
	double LineRxH ,   Linek;



	double Distance_km(double lat1,double lon1,double lat2,double lon2);
	void GetData(); 
	void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV);
	double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2);
	double Interp2(int *D0,double *E0,double d,int num);
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_FREE_POLYGONDOC_H__144B9DAD_2E4E_41AC_90AF_F299B7F453F3__INCLUDED_)
