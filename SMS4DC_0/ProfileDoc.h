#if !defined(AFX_PROFILEDOC_H__F8151DC6_7090_4EE5_8554_4EE0E5C8CD7E__INCLUDED_)
#define AFX_PROFILEDOC_H__F8151DC6_7090_4EE5_8554_4EE0E5C8CD7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfileDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProfileDoc document

class CProfileDoc : public CDocument
{
protected:
	CProfileDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProfileDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProfileDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CProfileDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int Np;
	double *m_hi;
	double *m_di;
	double *m_lati;
	double *m_loni;

	double Hmin,Dmin,Dmax;
	int m_ReadyDoc;
	BOOL m_DrawFresnel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEDOC_H__F8151DC6_7090_4EE5_8554_4EE0E5C8CD7E__INCLUDED_)
