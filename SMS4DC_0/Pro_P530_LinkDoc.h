#if !defined(AFX_PRO_P530_LINKDOC_H__6F2D0AC1_A781_4FE2_A3C9_6CE6080629D1__INCLUDED_)
#define AFX_PRO_P530_LINKDOC_H__6F2D0AC1_A781_4FE2_A3C9_6CE6080629D1__INCLUDED_




#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P530_LinkDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P530_LinkDoc document


class CPro_P530_LinkDoc : public CDocument
{
protected:
	CPro_P530_LinkDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P530_LinkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P530_LinkDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P530_LinkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P530_LinkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL m_DrawFresnel;
	double m_Gt,m_Gr,Linklat_Rx,Linklon_Rx;

	double Dmin,Dmax,m_Distance,m_FsLoss,Hmin;
	int Np;
	double *m_hi;
	double *m_di;
	double *m_lati;
	double *m_loni;
	int *m_zi;

	int m_ReadyDoc,m_path_type;
	double Linklat_ST,Linklon_ST,LinkPtGt_ST,LinkHagl_ST,LinkHasl_ST,LinkfMHz_ST,LinkfMHz_Rx;
	double Linklat0,Linklon0;
	double LinkRxH,Linkk;

	int Linkatomi;
	double Linkanav,Linkfzn,m_Clearance;
	CString LinkPol;
	double 	h1, h2, LOSDist, LongM, LatM, A0dot01L,m_Sa,m_mK;

	CString LinkName_ST,LinkName_Rx;
	CString m_tit;
	CString m_Loss1L,m_Loss1;
	CString m_Loss2L,m_Loss2;
	CString m_Loss3L,m_Loss3;
	CString m_Loss4L,m_Loss4;
	CString m_Loss5L,m_Loss5;
	double LinkTxInsertionLoss,LinkRxInsertionLoss,LinkRxThreshold;

	int GetData(); 
	int LandSeaCoastal(double RLON_deg,double RLAT_deg) ;

	void PathMean(double LeftLong, double LeftLat, double RightLong, double RightLat, double *LongM, double *LatM);
	double Dist_ke(double d) ;
	double Interp1(double *D0,double *E0,double d,int num) ;

	double fresnel_clearance(double *di,double *hi,long Np, double f_MHz, double re, double Ht, double Hr);

	long ID_Tx, ID_Rx;
	double interwt(double *ft,double *at,int n,double f0) ;
	double MinValue(double *xi,int N) ;
	double MaxValue(double *xi,int N) ;
	double subsection(double a,double b,double fc) ;
	double NFD_Loss() ;
	double m_NFD_Loss ;
		
	BOOL m_flag_WorstMonth;
	int m_iClimate, m_RADIO1_rain;
	BOOL	m_CHECK_Q;
	double m_DeltaG, m_p0, m_rain_py, m_rain_pw;

	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P530_LINKDOC_H__6F2D0AC1_A781_4FE2_A3C9_6CE6080629D1__INCLUDED_)
