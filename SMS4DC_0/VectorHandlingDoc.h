#if !defined(AFX_VECTORHANDLINGDOC_H__13F66E62_D98E_4E1E_9155_2B3563318F8E__INCLUDED_)
#define AFX_VECTORHANDLINGDOC_H__13F66E62_D98E_4E1E_9155_2B3563318F8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VectorHandlingDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingDoc document

class CVectorHandlingDoc : public CDocument
{
protected:
	CVectorHandlingDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVectorHandlingDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVectorHandlingDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVectorHandlingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CVectorHandlingDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VECTORHANDLINGDOC_H__13F66E62_D98E_4E1E_9155_2B3563318F8E__INCLUDED_)
