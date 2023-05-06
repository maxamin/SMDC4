#if !defined(AFX_PROFILEPOLYGONDOC_H__4A8A8F70_5B88_4580_97E3_B61A109C541F__INCLUDED_)
#define AFX_PROFILEPOLYGONDOC_H__4A8A8F70_5B88_4580_97E3_B61A109C541F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfilePolygonDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfilePolygonDoc document

class CProfilePolygonDoc : public CDocument
{
protected:
	CProfilePolygonDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProfilePolygonDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfilePolygonDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProfilePolygonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CProfilePolygonDoc)
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
	int m_PolyPointNum;
	int *Npt;
	int m_ReadyDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEPOLYGONDOC_H__4A8A8F70_5B88_4580_97E3_B61A109C541F__INCLUDED_)
