#if !defined(AFX_PRO_P452_LINKDOC_H__381BCCFE_2D8A_44FE_A458_3BAB5A4BD2D2__INCLUDED_)
#define AFX_PRO_P452_LINKDOC_H__381BCCFE_2D8A_44FE_A458_3BAB5A4BD2D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P452_LinkDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P452_LinkDoc document

class CPro_P452_LinkDoc : public CDocument
{
protected:
	CPro_P452_LinkDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P452_LinkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P452_LinkDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P452_LinkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P452_LinkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL m_DrawFresnel;
	double m_Gt,m_Gr,Linklat_Rx,Linklon_Rx;

	double Dmin,Dmax,m_Distance,m_FsLoss,Hmin;
	int Np;
	double *m_hi;
	double *m_hikm;
	double *m_di;
	double *m_lati;
	double *m_loni;
	CString *m_zi;

	int m_ReadyDoc,m_path_type;
	double Linklat_ST,Linklon_ST,LinkPtGt_ST,LinkHagl_ST,LinkHasl_ST,LinkfMHz_ST;
	double Linklat0,Linklon0;
	double LinkRxH,Linkk;
	double Linktime,Linkbeta,LinkdN,LinkN0;

	CString LinkName_ST,LinkName_Rx;
	CString m_tit;
	CString m_Loss1L,m_Loss1;
	CString m_Loss2L,m_Loss2;
	CString m_Loss3L,m_Loss3;
	CString m_Loss4L,m_Loss4;
	CString m_Loss5L,m_Loss5;

	int GetData(); 
	CString LandSeaCoastal(double RLON_deg,double RLAT_deg) ;

	long ID_Tx, ID_Rx;
	double interwt(double *ft,double *at,int n,double f0) ;
	double MinValue(double *xi,int N) ;
	double MaxValue(double *xi,int N) ;
	double subsection(double a,double b,double fc) ;
	double NFD_Loss() ;
	double m_NFD_Loss, LinkfMHz_Rx;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	void PathMean(double LeftLong, double LeftLat, double RightLong, double RightLat, double *LongM, double *LatM);
	CString m_PolarizationTx;
	double m_Pressure, m_TempC, m_ha_Clutter, m_dk_Clutter;
	BOOL m_flagAvWo;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P452_LINKDOC_H__381BCCFE_2D8A_44FE_A458_3BAB5A4BD2D2__INCLUDED_)
