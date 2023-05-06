#if !defined(AFX_PRO_P526V14_LINKDOC_H__DDCD87CA_DE08_4C4D_B64B_21EF838D9F5A__INCLUDED_)
#define AFX_PRO_P526V14_LINKDOC_H__DDCD87CA_DE08_4C4D_B64B_21EF838D9F5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P526V14_LinkDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P526V14_LinkDoc document

class CPro_P526V14_LinkDoc : public CDocument
{
protected:
	CPro_P526V14_LinkDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPro_P526V14_LinkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P526V14_LinkDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPro_P526V14_LinkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPro_P526V14_LinkDoc)
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

	int m_ReadyDoc,m_path_type;
	double Linklat_ST,Linklon_ST,LinkPtGt_ST,LinkHagl_ST,LinkHasl_ST,LinkfMHz_ST;
	double Linklat0,Linklon0;
	double LinkRxH,Linkk;
	double Linktime,Linkbeta,LinkdN,LinkN0;

	CString LinkName_ST,LinkName_Rx;
	CString m_tit;
	CString m_Loss1L,m_Loss1;
	CString m_Loss2L,m_Loss2;
	double LinkRxThreshold;

	CString m_kfactor;
	double atof_kfactor(CString k1) ;

	void GetData(); 
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	double m_Lba, m_Lbs, m_Lsph;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P526V14_LINKDOC_H__DDCD87CA_DE08_4C4D_B64B_21EF838D9F5A__INCLUDED_)
