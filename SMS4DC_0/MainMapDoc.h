#if !defined(AFX_MAINMAPDOC_H__2048A0AD_7E65_4190_A653_86D08CBFE2E9__INCLUDED_)
#define AFX_MAINMAPDOC_H__2048A0AD_7E65_4190_A653_86D08CBFE2E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainMapDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainMapDoc document

class CMainMapDoc : public CDocument
{
protected:
	CMainMapDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMainMapDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainMapDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainMapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainMapDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINMAPDOC_H__2048A0AD_7E65_4190_A653_86D08CBFE2E9__INCLUDED_)
