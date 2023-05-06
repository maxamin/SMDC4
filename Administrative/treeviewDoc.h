// treeviewDoc.h : interface of the CTreeviewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREEVIEWDOC_H__DDB0F0BE_9FEE_415A_BE55_AD8F676DA41D__INCLUDED_)
#define AFX_TREEVIEWDOC_H__DDB0F0BE_9FEE_415A_BE55_AD8F676DA41D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTreeviewDoc : public CDocument
{
protected: // create from serialization only
	CTreeviewDoc();
	DECLARE_DYNCREATE(CTreeviewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeviewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeviewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeviewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEVIEWDOC_H__DDB0F0BE_9FEE_415A_BE55_AD8F676DA41D__INCLUDED_)
