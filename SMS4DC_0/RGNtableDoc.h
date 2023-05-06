#if !defined(AFX_RGNTABLEDOC_H__2234349A_8D39_4BB6_9C16_E5A881128F71__INCLUDED_)
#define AFX_RGNTABLEDOC_H__2234349A_8D39_4BB6_9C16_E5A881128F71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGNtableDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGNtableDoc document

class CRGNtableDoc : public CDocument
{
protected:
	CRGNtableDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRGNtableDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGNtableDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRGNtableDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGNtableDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGNTABLEDOC_H__2234349A_8D39_4BB6_9C16_E5A881128F71__INCLUDED_)
