#if !defined(AFX_SRVTABLEDOC_H__FD2CD7CE_C682_46E0_A771_0F24AA856904__INCLUDED_)
#define AFX_SRVTABLEDOC_H__FD2CD7CE_C682_46E0_A771_0F24AA856904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SRVtableDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSRVtableDoc document

class CSRVtableDoc : public CDocument
{
protected:
	CSRVtableDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSRVtableDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRVtableDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSRVtableDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSRVtableDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVTABLEDOC_H__FD2CD7CE_C682_46E0_A771_0F24AA856904__INCLUDED_)
