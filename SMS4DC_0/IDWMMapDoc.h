#if !defined(AFX_IDWMMAPDOC_H__3789E1BF_47D1_41FC_A30F_71DB4E871B32__INCLUDED_)
#define AFX_IDWMMAPDOC_H__3789E1BF_47D1_41FC_A30F_71DB4E871B32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IDWMMapDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapDoc document

class CIDWMMapDoc : public CDocument
{
protected:
	CIDWMMapDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIDWMMapDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDWMMapDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIDWMMapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CIDWMMapDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDWMMAPDOC_H__3789E1BF_47D1_41FC_A30F_71DB4E871B32__INCLUDED_)
